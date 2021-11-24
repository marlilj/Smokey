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

#include "../include/temp_set_gear.hpp"

#include <iostream>
#include <string>

#include "../../include/smokey_data.hpp"

GearInput gearInput;

int GearInput::SetGear(int8_t input_selected_gear) {
  if (input_selected_gear <= 0 && gearInput.GearIsSet == false) {
    std::cout << "No gear selected" << std::endl;
    gearInput.gear = -1;
    gearInput.GearIsSet = false;
    error_code = kNotSet;
    std::cout << "Return error_code ";
  } else if (input_selected_gear == 1 && gearInput.GearIsSet == false) {
    std::cout << "'P' selected" << std::endl;
    gearInput.gear = 1;
    gearInput.GearIsSet = true;
    error_code = kSuccess;
    std::cout << "Return error_code ";
  } else if (input_selected_gear == 2 && gearInput.GearIsSet == false) {
    std::cout << "'N' selected" << std::endl;
    gearInput.gear = 2;
    gearInput.GearIsSet = true;
    error_code = kSuccess;
    std::cout << "Return error_code ";
  } else if (input_selected_gear == 3 && gearInput.GearIsSet == false) {
    std::cout << "'D' selected" << std::endl;
    gearInput.gear = 3;
    gearInput.GearIsSet = true;
    error_code = kSuccess;
    std::cout << "Return error_code ";
  } else if (input_selected_gear == 4 && gearInput.GearIsSet == false) {
    std::cout << "'R' selected" << std::endl;
    gearInput.gear = 4;
    gearInput.GearIsSet = true;
    error_code = kSuccess;
    std::cout << "Return error_code ";
  } else {
    std::cout << "Bad value" << std::endl;
    gearInput.gear = -1;
    gearInput.GearIsSet = false;
    error_code = kBadValue;
    std::cout << "Return error_code ";
  }
  gearInput.GearIsSet = false;
  return error_code;
}

int main() {
  int _input_gear_ = -1;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 0;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 1;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 2;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 3;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 4;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;
  _input_gear_ = 5;

  std::cout << gearInput.SetGear(_input_gear_);
  std::cout << ".\n" << std::endl;

  return 0;
}
