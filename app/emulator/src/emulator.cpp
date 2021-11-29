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
#include <thread>
#include <math.h>
#include "smokey_data.hpp"
#include "input_handler.hpp"

InputHandler smokeyInputData;

bool Emulator::ReadData() {
  SocketCan socket_("vcan0");
  bool retval = false;
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    if (fr.id == 1) {  // TODO(Niklas): add macro for CAN frame IDs
      this->emulator_data_.throttle_set_value = fr.data[0];
      this->emulator_data_.gear_set_value = fr.data[1];
      this->emulator_data_.start_set_value = fr.data[2];
      retval = true;
    }
  }
  return retval;
}

Emulator::Emulator(const std::string& interface_name) {
/* : socket_(interface_name)  {} */
  // Emulator::ReadAndSetPindle();
  // Emulator::ReadData();
}

bool Emulator::Emulate() {
  int error_code = kFailure;
while(true) {
  if (this->emulator_data_.activate_engine) {
    if (this->emulator_data_.gear_drive) {
      this->FancyEmulation();
      this->sendCAN();
      // Postponed functionality
//      this->UpdateGearAutomatic();
//      this->CalculateSpeed();
      }
    }
  

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
  // usleep(1000);
//  usleep(DT);
  error_code = kSuccess;

  return error_code;
}

bool Emulator::ReadAndSetPindle() {
  int error_code = kFailure;
  int8_t set_gear = PINDLE_PARKING;
  int8_t print_set_gear = '.';
  bool set_start = false;

  // Read CAN message
  while(true) {
  if (ReadData()) {
//    std::cout << "Data has been read." << std::endl;
    set_start = this->emulator_data_.start_set_value;
    set_gear = this->emulator_data_.gear_set_value;
    this->emulator_data_.throttle = this->emulator_data_.throttle_set_value;
    // this->emulator_data_.rpm =
    // throttle_to_RPM_one_gear[(this->emulator_data_.throttle)/10];

    if (set_gear == PINDLE_PARKING && set_start) {
      PindleModes::PindleParking(emulator_data_);
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
    } else if (set_gear == PINDLE_PARKING && !set_start) {
        PindleModes::OffMode(emulator_data_);
        print_set_gear = '.';  // .
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_DRIVE
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleDrive(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // D
        set_start = true;
    } else if (set_gear == PINDLE_DRIVE && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // P
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_NEUTRAL
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleNeutral(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // N
        set_start = true;
    } else if (set_gear == PINDLE_NEUTRAL && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // P
        set_start = false;
    } else if (emulator_data_.parking_flag && set_gear == PINDLE_REVERSE
              && !emulator_data_.gear_neutral && !emulator_data_.gear_drive
              && !emulator_data_.gear_reverse && set_start) {
        PindleModes::PindleReverse(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // R
        set_start = true;
    } else if (set_gear == PINDLE_REVERSE && !set_start) {
        PindleModes::PindleParking(emulator_data_);
        print_set_gear = this->emulator_data_.gear_set_value-32;  // P
        set_start = false;
      }
    }
  }
  return error_code;
}

bool Emulator::FancyEmulation() {
  bool error_code = kFailure;
  switch (this->emulator_data_.throttle) {
    case 10:
      emulator_data_.gear = FE_GEAR_AT_10;
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
      this->emulator_data_.gear = FE_GEAR_AT_0;
      this->emulator_data_.rpm = FE_RPM_AT_0;
      this->emulator_data_.speed = FE_VELOCITY_AT_0;
      break;
  }
  error_code = kSuccess;

  std::cout << " gear: " << this->emulator_data_.gear << "\n"  // NOLINT
    << " rpm: " << this->emulator_data_.rpm << "\n"<< " trottle: " << this->emulator_data_.throttle << std::endl;  // NOLINT

  return error_code;
}

bool Emulator::UpdateGearAutomatic() {
  bool error_code = kFailure;
  size_t new_gear = 0;
  size_t new_rpm = 0;

//  if (this->emulator_data_.gear < this->emulator_data_.gear_set_value) {  // TODO: byt till automatiskt istället... NOLINT

  if (this->emulator_data_.rpm >= GEAR_HIGH_RPM) {
    // Switch up to next gear
    new_rpm = GEAR_LOW_RPM;
    switch (this->emulator_data_.gear) {
      case EMULATOR_GEAR_1:
        new_gear = EMULATOR_GEAR_2;
        break;
      case EMULATOR_GEAR_2:
        new_gear = EMULATOR_GEAR_3;
        break;
      case EMULATOR_GEAR_3:
        new_gear = EMULATOR_GEAR_4;
        break;
      case EMULATOR_GEAR_4:
        new_gear = EMULATOR_GEAR_5;
        break;
      default:  // EMULATOR_GEAR_5
        break;
    }
//  } else if (this->emulator_data_.gear < this->emulator_data_.gear_set_value) {
  } else if (this->emulator_data_.rpm <= GEAR_LOW_RPM) {
    // Switch gear down
    new_rpm = GEAR_HIGH_RPM;
    switch (this->emulator_data_.gear) {
      case EMULATOR_GEAR_2:
        new_gear = EMULATOR_GEAR_1;
        break;
      case EMULATOR_GEAR_3:
        new_gear = EMULATOR_GEAR_2;
        break;
      case EMULATOR_GEAR_4:
        new_gear = EMULATOR_GEAR_3;
        break;
      case EMULATOR_GEAR_5:
        new_gear = EMULATOR_GEAR_4;
        break;
      default:  // EMULATOR_GEAR_1
        break;
    }
  }

  if (this->SetRPM(new_rpm)) {
    error_code = kSuccess;
  }
  if (this->SetGear(new_gear)) {
    error_code = kSuccess;
  }

  return error_code;
}

bool Emulator::SetRPM(size_t _rpm) {
  this->emulator_data_.rpm = _rpm;
  return true;
}

bool Emulator::SetGear(size_t _gear) {
  this->emulator_data_.gear = _gear;
  return true;
}

bool Emulator::CalculateSpeed() {
  bool error_code = kFailure;

  CalculateForce();

  this->emulator_data_.speed = this->emulator_data_.speed + ( (this->emulator_data_.forward_force / VEHICLE_MASS) * DT);  // NOLINT

//  std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
//  this->emulator_data.speed = this->emulator_data.speed + ( (forward_force / VEHICLE_MASS) * (since(start).count())));
//  static auto start = std::chrono::steady_clock::now();

  error_code = kSuccess;

  return error_code;
}

bool Emulator::CalculateForce() {
  bool error_code = kFailure;

  this->emulator_data_.forward_force = (DRIVE_TRAIN_RATIO
      * this->emulator_data_.gear
      * this->GetEngineTorque() / WHEEL_RADIUS )
      - this->GetAirResistance();  // TODO: Add road resistance etc... NOLINT

  error_code = kSuccess;

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

size_t Emulator::GetEngineTorque() {
  double torque = 0;

  for (size_t i = 0; i < RPM_TORQUE_DATA_LENGTH; i++) {
    if (this->emulator_data_.rpm == RPM_Torque[i].first) {
      torque = RPM_Torque[i].second;
      break;
    } else if (this->emulator_data_.rpm < EMULATOR_IDLE_RPM) {
      // Engine not running
      break;
    } else if (this->emulator_data_.rpm < RPM_Torque[i].first) {
      // Interpolate
      torque = RPM_Torque[i-1].second +
        (RPM_Torque[i].first-RPM_Torque[i-1].first)*
        ((RPM_Torque[i].second-RPM_Torque[i-1].second)/
        (RPM_Torque[i].first-RPM_Torque[i-1].first));
        break;
    } else {
      torque = RPM_Torque[i].second;
    }
  }
  return static_cast<size_t>(torque);
}

size_t Emulator::GetAirResistance() {
  return (AIR_DENSITY * VEHICLE_FRONTAL_AREA * VEHICLE_DRAG_COEFF
        * (std::pow((this->emulator_data_.speed / 3.6), 2))) / 2;
}

bool Emulator::GracefulShutdown() {
  bool error_code = kFailure;
  // Delete stuff!
  error_code = kSuccess;
  return error_code;
}
