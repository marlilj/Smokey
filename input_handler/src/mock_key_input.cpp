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

#include <iostream>
#include <chrono>
#include <thread>

#include "../include/input_handler.hpp"

    class MockKeyInput {
     private:
  bool key_input = false;
  bool mock_key_input();

     public:
    };


bool MockKeyInput::mock_key_input() {
  int8_t keypress = 0;
  while (MockKeyInput::key_input == true) {
    if (keypress < 100) {
      keypress + 10;
      // InputHandler.key_press(MockKeyInput::keypress);
      std::cout << "Sent " << keypress << " to InputHandler.key_press.\n" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } else if (keypress >= 100 && keypress >= 0) {
      keypress - 10;
      // InputHandler.key_press(MockKeyInput::keypress);
      std::cout << "Sent " << keypress << " to InputHandler.key_press.\n" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }
  return true;
}


// Move to input_handler main function:

// MockKeyInput mockKeyInput;

// std::thread mock_thread_object(MockKeyInput(), void);

// mock_thread_object.join();
