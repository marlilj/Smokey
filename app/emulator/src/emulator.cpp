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
#include <math.h>
#include <iostream>
#include <chrono>  // NOLINT due to unapproved C++11 header
#include <thread>  // NOLINT due to unapproved C++11 header
#include "emulator.hpp"
#include "engine_pindle_states.hpp"
#include "smokey_data.hpp"
#include "input_handler.hpp"

InputHandler smokeyInputData;

bool Emulator::ReadData(Values_t &data) {
  SocketCan socket_("vcan0");
  bool retval = false;
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    if (fr.id == 1) {  // TODO(Niklas): add macro for CAN frame IDs
      data.throttle_set_value = fr.data[0];
      data.pindle_set_value = fr.data[1];
      data.start_set_value = fr.data[2];
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
  Values_t values = emulator_data_.GetAll();
  if (values.activate_engine) {
    if (values.pindle_drive) {
      this->FancyEmulation(values);
      this->sendCAN(values);
      error_code = emulator_data_.SetAll(values);
      // Postponed functionality
      // this->UpdateGearAutomatic();
      // this->CalculateSpeed();
      }
    }

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

  return error_code;
}

bool Emulator::ReadAndSetPindle() {
  int error_code = kFailure;
  int8_t set_pindle = PINDLE_PARKING;
  bool set_start = false;

  // Read CAN message
  while (true) {
    Values_t values = emulator_data_.GetAll();
  if (ReadData(values)) {
    set_start = values.start_set_value;
    set_pindle = values.pindle_set_value;
    values.throttle = values.throttle_set_value;

    if (set_pindle == PINDLE_PARKING && set_start) {
        PindleModes::PindleParking(values);  // P
    } else if (values.parking_flag && set_pindle == PINDLE_DRIVE && set_start) {
        PindleModes::PindleDrive(values);  // D
        set_start = true;
    } else if (values.parking_flag && set_pindle == PINDLE_NEUTRAL && set_start) {  // NOLINT Due to line break making it less readable.
        PindleModes::PindleNeutral(values);  // N
        set_start = true;
    } else if (values.parking_flag && set_pindle == PINDLE_REVERSE && set_start) {  // NOLINT Due to line break making it less readable.
        PindleModes::PindleReverse(values);  // R
        set_start = true;
    } else if (set_pindle == PINDLE_PARKING && !set_start) {
        PindleModes::PindleParking(values);  // P
        set_start = false;
      }
    }
    error_code = emulator_data_.SetAll(values);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  return error_code;
}

bool Emulator::FancyEmulation(Values_t &data) {
  bool error_code = kFailure;
  switch (data.throttle) {
    case 10:
      data.gear = FE_GEAR_AT_10;
      data.rpm = FE_RPM_AT_10;
      data.speed = FE_VELOCITY_AT_10;

      break;
    case 20:
      data.gear = FE_GEAR_AT_20;
      data.rpm = FE_RPM_AT_20;
      data.speed = FE_VELOCITY_AT_20;

      break;
    case 30:
      data.gear = FE_GEAR_AT_30;
      data.rpm = FE_RPM_AT_30;
      data.speed = FE_VELOCITY_AT_30;
      break;
    case 40:
      data.gear = FE_GEAR_AT_40;
      data.rpm = FE_RPM_AT_40;
      data.speed = FE_VELOCITY_AT_40;
      break;
    case 50:
      data.gear = FE_GEAR_AT_50;
      data.rpm = FE_RPM_AT_50;
      data.speed = FE_VELOCITY_AT_50;
      break;
    case 60:
      data.gear = FE_GEAR_AT_60;
      data.rpm = FE_RPM_AT_60;
      data.speed = FE_VELOCITY_AT_60;
      break;
    case 70:
      data.gear = FE_GEAR_AT_70;
      data.rpm = FE_RPM_AT_70;
      data.speed = FE_VELOCITY_AT_70;
      break;
    case 80:
      data.gear = FE_GEAR_AT_80;
      data.rpm = FE_RPM_AT_80;
      data.speed = FE_VELOCITY_AT_80;

      break;
    case 90:
      data.gear = FE_GEAR_AT_90;
      data.rpm = FE_RPM_AT_90;
      data.speed = FE_VELOCITY_AT_90;
      break;
    case 100:
      data.gear = FE_GEAR_AT_100;
      data.rpm = FE_RPM_AT_100;
      data.speed = FE_VELOCITY_AT_100;
      break;
    default:
      data.gear = FE_GEAR_AT_0;
      data.rpm = FE_RPM_AT_0;
      data.speed = FE_VELOCITY_AT_0;
      break;
  }

  error_code = kSuccess;

  std::cout << " gear: " << data.gear << "\n"  // NOLINT
    << " rpm: " << data.rpm << "\n"<< " trottle: " << data.throttle << std::endl;  // NOLINT

  return error_code;
}

bool Emulator::UpdateGearAutomatic() {
  bool error_code = kFailure;
  size_t new_gear = 0;
  size_t new_rpm = 0;

//  if (this->emulator_data_.gear < this->emulator_data_.GetGearSetValue()) {  // TODO: byt till automatiskt istället... NOLINT

  if (this->emulator_data_.GetRpm() >= GEAR_HIGH_RPM) {
    // Switch up to next gear
    new_rpm = GEAR_LOW_RPM;
    switch (this->emulator_data_.GetGear()) {
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
//  } else if (this->emulator_data_.gear < this->emulator_data_.GetGearSetValue()) {
  } else if (this->emulator_data_.GetRpm() <= GEAR_LOW_RPM) {
    // Switch gear down
    new_rpm = GEAR_HIGH_RPM;
    switch (this->emulator_data_.GetGear()) {
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
  this->emulator_data_.SetRpm(_rpm);
  return true;
}

bool Emulator::SetGear(size_t _gear) {
  this->emulator_data_.SetGear(_gear);
  return true;
}

bool Emulator::CalculateSpeed() {
  bool error_code = kFailure;

  CalculateForce();

  this->emulator_data_.SetSpeed(this->emulator_data_.GetSpeed() + ( (this->emulator_data_.GetForwardForce() / VEHICLE_MASS) * DT));  // NOLINT

//  std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
//  this->emulator_data.speed = this->emulator_data.speed + ( (forward_force / VEHICLE_MASS) * (since(start).count())));
//  static auto start = std::chrono::steady_clock::now();

  error_code = kSuccess;

  return error_code;
}

bool Emulator::CalculateForce() {
  bool error_code = kFailure;

  this->emulator_data_.SetForwardForce((DRIVE_TRAIN_RATIO
      * this->emulator_data_.GetGear()
      * this->GetEngineTorque() / WHEEL_RADIUS )
      - this->GetAirResistance());  // TODO: Add road resistance etc... NOLINT

  error_code = kSuccess;

  return error_code;
}

bool Emulator::sendCAN(const Values_t &data) {
  // Construct the data to be sent
  EmulatorOutput_t data_to_send;
  data_to_send.speed = static_cast<uint8_t>(data.speed);
  data_to_send.gear = static_cast<uint8_t>(data.gear);
  data_to_send.rpm = static_cast<uint16_t>(data.rpm);

  // Construct obejct from libcanencoder
  GetNewValues gnv;
  CanFrame frame_to_send = gnv.convertCANMessageFromStruct(data_to_send);
  bool return_value = gnv.sendMessageOnCAN(frame_to_send);
  return return_value;
}

size_t Emulator::GetEngineTorque() {
  double torque = 0;

  for (size_t i = 0; i < RPM_TORQUE_DATA_LENGTH; i++) {
    if (this->emulator_data_.GetRpm() == RPM_Torque[i].first) {
      torque = RPM_Torque[i].second;
      break;
    } else if (this->emulator_data_.GetRpm() < EMULATOR_IDLE_RPM) {
      // Engine not running
      break;
    } else if (this->emulator_data_.GetRpm() < RPM_Torque[i].first) {
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
        * (std::pow((this->emulator_data_.GetSpeed() / 3.6), 2))) / 2;
}

bool Emulator::GracefulShutdown() {
  bool error_code = kFailure;
  // Delete stuff!
  error_code = kSuccess;
  return error_code;
}

