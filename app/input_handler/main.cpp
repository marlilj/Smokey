
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

#include "input_handler.hpp"


int main(void) {
  bool error_code = kFailure;

  InputHandler SmokeyInput;
  GetNewValues get_new_values;

  error_code = SmokeyInput.InitInputHandler();
  if (error_code == kSuccess) {
    error_code = SmokeyInput.ReadUserInput(get_new_values);
  }
  if (error_code == kSuccess) {
    error_code = SmokeyInput.ExitInputHandler();
  }
  if (error_code == kSuccess) {
    error_code = SmokeyInput.GracefulShutdown();
  } else {
    error_code = kFailure;
  }

  return error_code;
}
