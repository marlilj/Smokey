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

// InputHandler smokeyInputData;

EmulatorData emulatorData;

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
  int8_t print_set_gear = 112;
  bool set_start = false;

  // Read CAN message
  if (ReadData()) {
    set_start = this->emulator_data_.start_set_value;

    this->emulator_data_.throttle = this->emulator_data_.throttle_set_value;
    this->emulator_data_.rpm =
    throttle_to_RPM_one_gear[(this->emulator_data_.throttle)/10];


      emulatorData.activate_engine = true;
      emulatorData.gear_neutral = true;
      emulatorData.gear_drive = true;
      emulatorData.gear_reverse = true;

      bool test1 = emulatorData.activate_engine;
      bool test2 = emulatorData.gear_neutral;
      bool test3 = emulatorData.gear_drive;
      bool test4 = emulatorData.gear_reverse;


    std::cout << "print_set_gear: " << this->emulator_data_.start_set_value << "\n"  // NOLINT
    << " activate_engine: " << test1 << "\n"  // NOLINT
    << " gear_neutral: " << test2 << "\n"  // NOLINT
    << " gear_drive: " << test3 << "\n"  // NOLINT
    << " gear_reverse: " << test4 << "\n" << std::endl;  // NOLINT

      emulatorData.activate_engine = false;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;

      test1 = emulatorData.activate_engine;
      test2 = emulatorData.gear_neutral;
      test3 = emulatorData.gear_drive;
      test4 = emulatorData.gear_reverse;


    std::cout << "print_set_gear: " << this->emulator_data_.gear_set_value << "\n"  // NOLINT
    << " activate_engine: " << test1 << "\n"  // NOLINT
    << " gear_neutral: " << test2 << "\n"  // NOLINT
    << " gear_drive: " << test3 << "\n"  // NOLINT
    << " gear_reverse: " << test4 << "\n" << std::endl;  // NOLINT



/*     if (this->emulator_data_.start_set_value == 115
        && this->emulator_data_.gear_set_value == 112 && set_start == false) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
      emulatorData.activate_engine = true;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = true;
    } else if (this->emulator_data_.start_set_value == 115
        && this->emulator_data_.gear_set_value == 0 && set_start == false) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
      emulatorData.activate_engine = true;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;true
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = true;
      emulatorData.gear_reverse = false;
      set_start = true;
    } else if (this->emulator_data_.gear_set_value == 100
              && set_start != true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
      emulatorData.activate_engine = false;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = false;
    } else if (this->emulator_data_.gear_set_value == 112
              && set_start != true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
      emulatorData.activate_engine = false;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = false;
    } else if (this->emulator_data_.gear_set_value == 110
              && set_start == true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // N
      emulatorData.activate_engine = true;
      emulatorData.gear_neutral = true;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = true;
    } else if (this->emulator_data_.gear_set_value == 110
              && set_start != true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // N
      emulatorData.activate_engine = false;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = false;
    } else if (this->emulator_data_.gear_set_value == 114
              && set_start == true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // R
      emulatorData.activate_engine = true;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = true;
      set_start = true;
    } else if (this->emulator_data_.gear_set_value == 114
              && set_start != true) {
      print_set_gear = this->emulator_data_.gear_set_value-32;  // P
      emulatorData.activate_engine = false;
      emulatorData.gear_neutral = false;
      emulatorData.gear_drive = false;
      emulatorData.gear_reverse = false;
      set_start = false;
    } else {
      set_start = this->emulator_data_.start_set_value;
      print_set_gear = this->emulator_data_.gear_set_value;  // p
      // emulatorData.activate_engine = false;
      // emulatorData.gear_neutral = false;
      // emulatorData.gear_drive = false;
      // emulatorData.gear_reverse = false;
    }


    std::cout << "print_set_gear: " << this->emulator_data_.gear_set_value << "\n"  // NOLINT
    << " activate_engine: " << this->emulator_data_.activate_engine << "\n"  // NOLINT
    << " gear_neutral: " << this->emulator_data_.gear_neutral << "\n"  // NOLINT
    << " gear_drive: " << this->emulator_data_.gear_drive << "\n"  // NOLINT
    << " gear_reverse: " << this->emulator_data_.gear_reverse << "\n" << std::endl;  // NOLINT
    // std::cout << "Throttle: " << this->emulator_data_.throttle_set_value
    // << " Gear: " << print_set_gear << " Start: " << set_start << std::endl;
      // smokeyInputData.SmokeyInputData.throttle = 0;
      // smokeyInputData.SmokeyInputData.gear = 112; */
  }
  usleep(5);


  error_code = kSuccess;

  return error_code;
}
