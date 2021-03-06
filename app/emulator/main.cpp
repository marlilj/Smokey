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
#include <atomic>
#include <functional>
#include "smokey_data.hpp"
#include "emulator.hpp"
// #include decoder.hpp   <--- skaffa input från David.




int main(int argc, char ** argv) {
  std::string interface_name;
  bool error_code = kFailure;

  if (argc == 1) {
    interface_name = "vcan0";
  } else if (argc == 2) {
    interface_name = argv[1];
  }

  std::atomic<bool> exit_flag(false);
  Emulator emulator(interface_name);

  std::thread thread1(&Emulator::ReadAndSetPindle, &emulator, &exit_flag);
  std::thread thread2(&Emulator::Emulate, &emulator, &exit_flag);

  thread1.join();
  thread2.join();

  error_code = emulator.GracefulShutdown();

  return error_code;
}
