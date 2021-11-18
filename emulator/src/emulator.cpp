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

#include <iostream>
#include <unistd.h>
#include "../../input_handler/include/smokey_data.hpp"
#include "../include/emulator.hpp"
// #include decoder.hpp   <--- skaffa input från David.

Emulator::Emulator(const std::string &interface_name)
: socket_(interface_name) {}
  // Data init
  // this->emulator_data.rpm = EMULATOR_IDLE_RPM;
// }

bool Emulator::ReadData() {
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
  this->emulator_data_.throttle_set_value = fr.data[0];
  this->emulator_data_.gear_set_value = fr.data[1];
  return true;
  } else {
  return false;
  }
}

bool Emulator::Emulate() {
  bool error_code = kFailure;

  // Read CAN message
  if(ReadData()) {
    std::cout << "Throttle: " << this->emulator_data_.throttle_set_value << " Gear: " << this->emulator_data_.gear_set_value << std::endl;
  }
  usleep(5);

  error_code = kSuccess;


  return error_code;
}
