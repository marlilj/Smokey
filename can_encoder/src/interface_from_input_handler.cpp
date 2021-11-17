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

#include "../include/interface_from_input_handler.hpp"
#include "../../input_handler/include/smokey_data.hpp"

#include <iostream> // NOLINT
#include <string> // NOLINT
const bool kSuccess = true;
const bool kFailure = false;


int16_t GetNewValues::getNewValues(Payload_t &payload) {
  bool error_code = kFailure;

  std::cout << "GetNewValue function stores throttle value "
                << payload.throttle << " and gear "
                << payload.gear << "\n" << std::endl;
  // Do stuff in the CAN Encoder.

  error_code = kSuccess; // NOLINT
  return error_code;
}