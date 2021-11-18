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

#ifndef MOCKKEYINPUT_HPP // NOLINT
#define MOCKKEYINPUT_HPP

#include <iostream>

#include "smokey_data.hpp"

class MockKeyInput {
 private:
 public:
  static int16_t mock_key_input(Payload_t& payload); // NOLINT
};

#endif // MOCKKEYINPUT_HPP // NOLINT
