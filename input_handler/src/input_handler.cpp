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

#include "../include/interface_to_can_encoder.hpp"
#include "../include/mock_key_input.hpp"
#include "../include/smokey_data.hpp"

MockKeyInput mockKeyInput;

std::string values_to_can_encoder_ = "String_to_CAN_encoder from InputHandler";  // NOLINT

SendNewValues send_new_values_;

Payload_t payload_;

int main() {
  int returnValue = kFailure;

  // std::thread mock_thread_object(MockKeyInput());

  send_new_values_.sendNewValues(payload_.throttle);
  std::cout << "3. " << values_to_can_encoder_ << "\n" << std::endl;
  for (size_t i = 0; i < 5; i++) {
    returnValue = MockKeyInput::mock_key_input();
    if (returnValue) {
      returnValue = kSuccess;
    }
  }

  std::cout << "returnValue is " << returnValue << std::endl;
  // mock_thread_object.join();

  return returnValue;
}