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

#include <string>

#include "../../can_encoder/include/interface_from_input_handler.hpp"
#include "../include/mock_key_input.hpp"
#include "../include/smokey_data.hpp"

MockKeyInput mockKeyInput;
Payload_t payload;
GetNewValues _get_new_values_;

int main() {
  bool error_code = kFailure;

if (MockKeyInput::mock_key_input(payload) != 0 &&
  _get_new_values_.getNewValues(payload) != 0) {
  error_code = kSuccess;
}

std::cout << "ErrorCode is: " << error_code << std::endl;
  return error_code;
}