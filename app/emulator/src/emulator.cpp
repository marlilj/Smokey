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

Emulator::Emulator(const std::string& interface_name)
: socket_(interface_name) {}
// Data init
// this->emulator_data.rpm = EMULATOR_IDLE_RPM;
// }

bool Emulator::ReadData() {
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    this->emulator_data_.throttle_set_value = fr.data[0];
    this->emulator_data_.gear_set_value = fr.data[1];
    this->emulator_data_.start_set_value = fr.data[2];
    return true;
  } else {
    return false;
  }
}

bool Emulator::Emulate() {
  int error_code = kFailure;
  int8_t set_gear = PINDLE_PARKING;
  int8_t print_set_gear = '.';
  bool set_start = false;

  // Read CAN message
  if (ReadData()) {
    set_start = this->emulator_data_.start_set_value;
    set_gear = this->emulator_data_.gear_set_value;
    this->emulator_data_.throttle = this->emulator_data_.throttle_set_value;
    this->emulator_data_.rpm =
    throttle_to_RPM_one_gear[(this->emulator_data_.throttle)/10];

    if (set_gear == PINDLE_PARKING && set_start) {
      PindleModes::PindleParking(emulator_data_);
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
    } else if (set_gear == PINDLE_PARKING && !set_start) {
        PindleModes::OffMode(emulator_data_);
        print_set_gear = '.';  // P
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
    std::cout << " print_set_gear: " << print_set_gear << "\n"  // NOLINT
    << " set_start: " << set_start << "\n"<< std::endl;  // NOLINT

    this->sendCAN();
  }
  usleep(5);

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
