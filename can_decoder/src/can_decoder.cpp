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

#include "../include/can_decoder.hpp"

#include "../../input_handler/include/smokey_data.hpp"

bool DummyCanDecoderClass::DummyCanDecoderFunction() {
  int error_code = kFailure;
  // Do nothing!
  error_code = kSuccess;
  return error_code;
}