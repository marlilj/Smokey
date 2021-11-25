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

#include "interface_from_input_handler.hpp"

#include <thread>  // NOLINT

#include "../include/input_handler.hpp"
#include "../include/smokey_data.hpp"

GetNewValues getNewValues_;

int16_t mock_keypress = 0;

int16_t MockKeyInput::mock_key_input(Payload_t& payload) {
  payload.gear = 0;
  if (mock_keypress <= 90) {
    for (mock_keypress; mock_keypress < 100; mock_keypress = mock_keypress + 10) {  // NOLINT
      payload.throttle = mock_keypress;
      payload.gear++;  // NOLINT
      getNewValues_.getNewValues(payload);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }
  if (mock_keypress > 90) {
    payload.gear = 10;
    for (mock_keypress; mock_keypress > 0; mock_keypress = mock_keypress - 10) {  // NOLINT
      payload.throttle = mock_keypress;
      payload.gear--;  // NOLINT
      getNewValues_.getNewValues(payload);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }
  return payload.throttle;
}
