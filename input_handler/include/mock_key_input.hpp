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

#include <chrono>
#include <iostream>
#include <thread>

// #include "../include/input_handler.hpp"
// #include "../include/smokey_data.hpp"

class MockKeyInput {
 private:
  // bool key_input = false;
 public:
  static bool mock_key_input();
};

const bool kSuccess = true;
const bool kFailure = false;
