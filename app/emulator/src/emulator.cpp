/*
 * Copyright (C) 2021 - Volvo Car Corporation
 *
 * All Rights Reserved
 *
 * LEGAL NOTICE:  All information (including intellectual and technical concepts) contained herein
 * is, and remains the property of or licensed to Volvo Car Corporation.
 * This information is proprietary to Volvo Car Corporation and may be covered by patents or patent
 * applications. This information is protected by trade secret or copyright law. Dissemination of
 * this information or reproduction of this material is strictly forbidden unless prior written
 * permission is obtained from Volvo Car Corporation.
 *
 */

#include <unistd.h>
#include <iostream>

#include "emulator.hpp"
#include "engine_pindle_states.hpp"
#include <chrono>
#include <math.h> 
#include "smokey_data.hpp"
#include "input_handler.hpp"

InputHandler smokeyInputData;

Emulator::Emulator(const std::string& interface_name)
/* : socket_(interface_name) */ {}


bool Emulator::ReadData() {
  SocketCan socket_("vcan0");
  bool retval = false;
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    if (fr.id==1) {  // TODO: add macro for CAN frame IDs
      this->emulator_data_.throttle_set_value = fr.data[0];
      this->emulator_data_.pindle_set_value = fr.data[1];
      this->emulator_data_.start_set_value = fr.data[2];
      retval = true;
    }
  }
  return retval;
}

bool Emulator::Emulate() {
  int error_code = kFailure;
  int8_t set_gear = PINDLE_PARKING;
  int8_t print_set_gear = '.';
  bool set_start = false;

  // TODO: Move to separate function
  // Read CAN message
  if (ReadData()) {
//    std::cout << "Data has been read." << std::endl;
    set_start = this->emulator_data_.start_set_value;
    set_gear = this->emulator_data_.pindle_set_value;
 

    this->emulator_data_.throttle = this->emulator_data_.throttle_set_value;
    // this->emulator_data_.rpm =
    // throttle_to_RPM_one_gear[(this->emulator_data_.throttle)/10];

    if (set_gear == PINDLE_PARKING && set_start) {
      PindleModes::PindleParking(emulator_data_);
      print_set_gear = this->emulator_data_.pindle_set_value-32;  // P
    } else if (set_gear == PINDLE_PARKING && !set_start) {
        PindleModes::OffMode(emulator_data_);
        print_set_gear = '.';  // P
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_DRIVE
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleDrive(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // D
        set_start = true;
    } else if (set_gear == PINDLE_DRIVE && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // P
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_NEUTRAL
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleNeutral(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // N
        set_start = true;
    } else if (set_gear == PINDLE_NEUTRAL && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // P
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_REVERSE
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleReverse(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // R
        set_start = true;
    } else if (set_gear == PINDLE_REVERSE && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.pindle_set_value-32;  // P
        set_start = false;
    }

  }
  if (this->emulator_data_.activate_engine) {
    if (this->emulator_data_.gear_drive && this->emulator_data_.gear != 0) {
//      this->FancyEmulation();

      this->GetEngineTorque();
      this->CalculateForce();
      this->CalculateSpeed();
      this->CalculateRPM();

      this->UpdateGearAutomatic();
      this->sendCAN();
    }
  }

  usleep(DT);
  error_code = kSuccess;

  return error_code;
}

bool Emulator::CalculateSpeed() {
  bool error_code = kFailure;

  if (this->emulator_data_.speed < MAX_SPEED) {
    this->emulator_data_.speed = this->emulator_data_.speed
      + ( (this->emulator_data_.forward_force / VEHICLE_MASS) * (DT/1000.0));  // NOLINT
  }
  error_code = kSuccess;

  return error_code;
}

bool Emulator::CalculateForce() {
  bool error_code = kFailure;


  float f_t = (this->emulator_data_.engine_torque
    * emulator_gear_ratio[this->emulator_data_.gear-1]
    * DRIVE_TRAIN_RATIO
    * DRIVE_TRAIN_EFFICIENY )
    / WHEEL_RADIUS;

  if (this->emulator_data_.speed == 0) this->emulator_data_.speed = 1;

  float f_a = ( AIR_DENSITY * VEHICLE_FRONTAL_AREA * VEHICLE_DRAG_COEFF
        * ((this->emulator_data_.speed / 3.6)*(this->emulator_data_.speed / 3.6)) ) / 2.0;
//        * (std::pow((this->emulator_data_.speed / 3.6), 2))) / 2;

  this->emulator_data_.forward_force = f_t - f_a - ROAD_RESISTANCE_FORCE;

  error_code = kSuccess;

  return error_code;
}


bool Emulator::GetEngineTorque() {
  bool error_code = kFailure;
  double torque = 0;

  if (this->emulator_data_.rpm < EMULATOR_IDLE_RPM) {
      // Engine not running
      torque = RPM_Torque[0].second;  // Set to torque for idle rpm
  } else {
    for (size_t i = 0; i < RPM_TORQUE_DATA_LENGTH; i++) {
      if (this->emulator_data_.rpm == RPM_Torque[i].first) {
        torque = RPM_Torque[i].second;
        break;
      } else if (this->emulator_data_.rpm < RPM_Torque[i].first) {
        // Interpolate
        torque = RPM_Torque[i-1].second +
          (this->emulator_data_.rpm-RPM_Torque[i-1].first)*
          ((RPM_Torque[i].second-RPM_Torque[i-1].second)/
          (RPM_Torque[i].first-RPM_Torque[i-1].first));
          break;
      } else {
        torque = RPM_Torque[i].second;
      }
    }
  }

  this->emulator_data_.engine_torque = torque * this->emulator_data_.throttle * 0.01;
  error_code = kSuccess;
  return error_code;
}




bool Emulator::UpdateGearAutomatic() {
  bool error_code = kFailure;

  if ((this->emulator_data_.rpm >= GEAR_HIGH_RPM)
      && (emulator_gear_limits[(this->emulator_data_.throttle)/10].second > this->emulator_data_.gear) ) {
    // Switch up to next gear
    switch (this->emulator_data_.gear) {
      case EMULATOR_GEAR_1:
        this->emulator_data_.gear = EMULATOR_GEAR_2;
        this->emulator_data_.rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_2:
        this->emulator_data_.gear = EMULATOR_GEAR_3;
        this->emulator_data_.rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_3:
        this->emulator_data_.gear = EMULATOR_GEAR_4;
        this->emulator_data_.rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_4:
        this->emulator_data_.gear = EMULATOR_GEAR_5;
        this->emulator_data_.rpm = GEAR_LOW_RPM;
        break;
      default:  // EMULATOR_GEAR_5
        break;
    }
    error_code = kSuccess;
  } else if ((this->emulator_data_.rpm <= GEAR_LOW_RPM)
      && (emulator_gear_limits[(this->emulator_data_.throttle)/10].first < this->emulator_data_.gear)) {
    // Switch gear down
    switch (this->emulator_data_.gear) {
      case EMULATOR_GEAR_2:
        this->emulator_data_.gear = EMULATOR_GEAR_1;
        this->emulator_data_.rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_3:
        this->emulator_data_.gear = EMULATOR_GEAR_2;
        this->emulator_data_.rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_4:
        this->emulator_data_.gear = EMULATOR_GEAR_3;
        this->emulator_data_.rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_5:
        this->emulator_data_.gear = EMULATOR_GEAR_4;
        this->emulator_data_.rpm = GEAR_HIGH_RPM;
        break;
      default:  // EMULATOR_GEAR_1
        break;
    }
    error_code = kSuccess;
  } else {
    // RPM and gear are unchanged
    error_code = kFailure;  // TODO: Error handling... NOLINT error_code = kSuccess;
  }

  return error_code;
}

bool Emulator::CalculateRPM() {
  this->emulator_data_.rpm = (30/3.14) * (this->emulator_data_.speed / WHEEL_RADIUS)
    * DRIVE_TRAIN_RATIO * emulator_gear_ratio[this->emulator_data_.gear-1];

  if (this->emulator_data_.rpm < EMULATOR_IDLE_RPM) {
    this->emulator_data_.rpm = EMULATOR_IDLE_RPM;
  } else if (this->emulator_data_.rpm > EMULATOR_MAX_RPM) {
    this->emulator_data_.rpm = EMULATOR_MAX_RPM;
  }
  return true;
}



bool Emulator::FancyEmulation() {
  bool error_code = kFailure;
  switch (this->emulator_data_.throttle) {
    case 10:
      this->emulator_data_.gear = FE_GEAR_AT_10;
      this->emulator_data_.rpm = FE_RPM_AT_10;
      this->emulator_data_.speed = FE_VELOCITY_AT_10;
      break;
    case 20:
      this->emulator_data_.gear = FE_GEAR_AT_20;
      this->emulator_data_.rpm = FE_RPM_AT_20;
      this->emulator_data_.speed = FE_VELOCITY_AT_20;
      break;
    case 30:
      this->emulator_data_.gear = FE_GEAR_AT_30;
      this->emulator_data_.rpm = FE_RPM_AT_30;
      this->emulator_data_.speed = FE_VELOCITY_AT_30;
      break;
    case 40:
      this->emulator_data_.gear = FE_GEAR_AT_40;
      this->emulator_data_.rpm = FE_RPM_AT_40;
      this->emulator_data_.speed = FE_VELOCITY_AT_40;
      break;
    case 50:
      this->emulator_data_.gear = FE_GEAR_AT_50;
      this->emulator_data_.rpm = FE_RPM_AT_50;
      this->emulator_data_.speed = FE_VELOCITY_AT_50;
      break;
    case 60:
      this->emulator_data_.gear = FE_GEAR_AT_60;
      this->emulator_data_.rpm = FE_RPM_AT_60;
      this->emulator_data_.speed = FE_VELOCITY_AT_60;
      break;
    case 70:
      this->emulator_data_.gear = FE_GEAR_AT_70;
      this->emulator_data_.rpm = FE_RPM_AT_70;
      this->emulator_data_.speed = FE_VELOCITY_AT_70;
      break;
    case 80:
      this->emulator_data_.gear = FE_GEAR_AT_80;
      this->emulator_data_.rpm = FE_RPM_AT_80;
      this->emulator_data_.speed = FE_VELOCITY_AT_80;
      break;
    case 90:
      this->emulator_data_.gear = FE_GEAR_AT_90;
      this->emulator_data_.rpm = FE_RPM_AT_90;
      this->emulator_data_.speed = FE_VELOCITY_AT_90;
      break;
    case 100:
      this->emulator_data_.gear = FE_GEAR_AT_100;
      this->emulator_data_.rpm = FE_RPM_AT_100;
      this->emulator_data_.speed = FE_VELOCITY_AT_100;
      break;
    default:
// TODO      this->emulator_data_.gear = FE_GEAR_AT_0;
      this->emulator_data_.rpm = FE_RPM_AT_0;
      this->emulator_data_.speed = FE_VELOCITY_AT_0;
      break;
  }
  error_code = kSuccess;

  std::cout << " gear: " << this->emulator_data_.gear << "\n"  // NOLINT
    << " rpm: " << this->emulator_data_.rpm << "\n"<< " trottle: " << this->emulator_data_.throttle << std::endl;  // NOLINT

  return error_code;
}


bool Emulator::sendCAN() {
  // Construct the data to be sent
  EmulatorOutput_t data_to_send;
  data_to_send.speed = static_cast<uint8_t>(this->emulator_data_.speed);
  data_to_send.gear = static_cast<uint8_t>(this->emulator_data_.gear);
  data_to_send.rpm = static_cast<uint16_t>(this->emulator_data_.rpm);

  // Construct obejct from libcanencoder
  GetNewValues gnv;
  CanFrame frame_to_send = gnv.convertCANMessageFromStruct(data_to_send);
  bool return_value = gnv.sendMessageOnCAN(frame_to_send);
  return return_value;
}
