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
#include "../include/interface_to_can_encoder.hpp"
#include "../include/mock_key_input.hpp"
#include "../include/smokey_data.hpp"

MockKeyInput mockKeyInput;

SendNewValues send_new_values_;

Payload_t payload;

GetNewValues _get_new_values_;

int main() {
  int16_t returnValue = kFailure;
  int16_t returnValue2 = kFailure;

  // std::thread mock_thread_object(MockKeyInput());

  std::cout << "payload.throttle is set to: " << payload.throttle << " by default.\n" << std::endl;  // NOLINT
  returnValue = MockKeyInput::mock_key_input(payload);

  returnValue2 = _get_new_values_.getNewValues(payload);

  std::cout << "Return value from MockKeyInput is " << returnValue << "\n" << std::endl;  // NOLINT

  std::cout << "Return value from GetNewValues is " << returnValue2 << "\n" << std::endl;  // NOLINT
  // mock_thread_object.join();

  std::cout << "payload_.throttle is set to " << payload.throttle << "\n" << std::endl;  // NOLINT

  return returnValue;
}