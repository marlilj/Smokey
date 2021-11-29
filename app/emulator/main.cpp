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

#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
// #include "smokey_data.hpp"
#include "../../lib/libcanio/include/smokey_data.hpp"
#include "include/emulator.hpp"
// #include decoder.hpp   <--- skaffa input från David.




int main() {
  bool error_code = kFailure;

  Emulator emulator("vcan0");

  std::thread thread1(&Emulator::ReadAndSetPindle, &emulator);
  std::thread thread2(&Emulator::Emulate, &emulator);

  thread1.join();
  thread2.join();

  error_code = emulator.GracefulShutdown();

  return error_code;
}
