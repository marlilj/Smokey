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

#include "../include/emulator.hpp"

#include <unistd.h>

#include <iostream>

#include "../../input_handler/include/smokey_data.hpp"
#include "../../input_handler/include/input_handler.hpp"
// #include decoder.hpp   <--- skaffa input från David.

SmokeyPayload smokeyPayload;


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
  bool error_code = kFailure;
  int8_t set_gear = 'P';
  int set_throttle = 0;
  bool set_start = false;

  // Read CAN message
  if (ReadData()) {
    set_start = this->emulator_data_.start_set_value;
    if (this->emulator_data_.start_set_value == 115 && !set_start) {
        set_start = true;
      // smokeyPayload.throttle = 0;
      // smokeyPayload.gear = 112;
      // set_gear = 'P';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.start_set_value == 115 &&
              set_start) {
      set_start = false;
      smokeyPayload.throttle = 0;
      smokeyPayload.gear = 112;
      set_gear = 'P';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 100 &&
              set_start == true) {
      set_gear = 'D';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 112 &&
              set_start == true) {
      set_gear = 'P';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 110 &&
              set_start == true) {
      set_gear = 'N';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 114 &&
              set_start == true) {
      set_gear = 'R';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else {
      // this->emulator_data_.throttle_set_value = 0;
      this->emulator_data_.gear_set_value = 112;
      set_start = this->emulator_data_.start_set_value;
      set_gear = 'P';
      set_throttle = this->emulator_data_.throttle_set_value;
    }
    std::cout << "Throttle: " << set_throttle <<
    " Gear: " << set_gear << " Start: " << set_start << std::endl;
  }
  usleep(5);

  error_code = kSuccess;

  return error_code;
}
