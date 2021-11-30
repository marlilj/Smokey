
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

/*
// MOCK CODE
#include <string>
#include "interface_from_input_handler.hpp"
#include "../include/mock_key_input.hpp"
#include "../include/smokey_data.hpp"

MockKeyInput mockKeyInput;
Payload_t payload;
GetNewValues _get_new_values_;
*/

#include "interface_from_input_handler.hpp"
#include "smokey_data.hpp"
#include "input_handler.hpp"


int main(void) {
  bool error_code = kFailure;

  InputHandler SmokeyInput;
  GetNewValues get_new_values;

  SmokeyInput.InitInputHandler();
  SmokeyInput.ReadUserInput(get_new_values);
  SmokeyInput.ExitInputHandler();

  error_code = SmokeyInput.GracefulShutdown();

  return error_code;

// MOCK CODE
/*
if (MockKeyInput::mock_key_input(payload) != 0 &&
  _get_new_values_.getNewValues(payload) != 0) {
  error_code = kSuccess;
}

std::cout << "ErrorCode is: " << error_code << std::endl;
  return error_code;
*/
}
