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

InputHandler smokeyInputData;

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
  bool set_start = false;
  int set_throttle = 0;

  // Read CAN message
  if (ReadData()) {
    set_throttle = this->emulator_data_.throttle_set_value;
    set_start = this->emulator_data_.start_set_value;
    set_gear = this->emulator_data_.gear_set_value;
    if (this->emulator_data_.start_set_value == 115
        && set_gear == 112 && set_start == false) {
      set_start = true;
      set_throttle = 0;
      set_gear = 112-32;  // P
    } else if (set_gear == 100 && set_start == true) {
      set_gear = 100-32;  // D
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (set_gear == 100 && set_start != true) {
      set_throttle = 0;
      set_gear = 112-32;  // P
    } else if (set_gear == 112 && set_start == true) {
      set_throttle = this->emulator_data_.throttle_set_value;
      set_gear = 112-32;  // P
    } else if (set_gear == 112 && set_start != true) {
      set_throttle = 0;
      set_gear = 112-32;  // P
    } else if (set_gear == 110 && set_start == true) {
      set_gear = 110-32;  // N
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (set_gear == 110 && set_start != true) {
      set_gear = 112-32;  // P
      set_throttle = 0;
    } else if (set_gear == 114 && set_start == true) {
      set_gear = 114-32;  // R
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (set_gear == 114 && set_start != true) {
      set_gear = 112-32;  // P
      set_throttle = 0;
    } else {
      set_start = this->emulator_data_.start_set_value;
    }
    std::cout << "Throttle: " << set_throttle << " Gear: "
    << set_gear << " Start: " << set_start << std::endl;
      // smokeyInputData.SmokeyInputData.gear = 112;
  }
  usleep(5);

  error_code = kSuccess;

  return error_code;
}
