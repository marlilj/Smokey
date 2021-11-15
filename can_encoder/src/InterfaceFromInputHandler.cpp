/**
 * Copyright (C) - Volvo Car Corporation
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
 * This file was generated fri Nov 12 11:07:24 2021
 */

//////////////////////////////////////////////////
// Dependencies

// #include "../include/InterfaceToCANEncoder.hpp"

#include "../include/InterfaceFromInputHandler.hpp"

#include <iostream>
#include <string>
const bool kSuccess = true;
const bool kFailure = false;

bool GetNewValues::getNewValues(std::string value_from_input_handler) {
  bool error_code = kFailure;

  std::cout << "2. in GetNewValue function: " << value_from_input_handler << "\n" << std::endl;
  // Do stuff in the CAN Encoder.

  error_code = kSuccess;
  return error_code;
}