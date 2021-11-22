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

 */
#ifndef EMULATOR_HPP // NOLINT
#define EMULATOR_HPP

#include <iostream>
#include "../../libcanio/include/canio.hpp"

#define EMULATOR_IDLE_RPM 800
#define EMULATOR_MAX_RPM 4000

#define EMULATOR_GEAR_RATIO_1 30  // 3:1
#define EMULATOR_GEAR_RATIO_2 20  // 2:1
#define EMULATOR_GEAR_RATIO_3 15  // 1.5:1
#define EMULATOR_GEAR_RATIO_4 10  // 1:1
#define EMULATOR_GEAR_RATIO_5 5   // 0.5:1


typedef struct EmulatorData {
  size_t throttle_set_value;
  size_t throttle;
  size_t gear_set_value;
  size_t start_set_value;
  size_t gear;
  size_t rpm;
  size_t speed;
}EmulatorData_T;


class Emulator{
  EmulatorData_T emulator_data_;
  SocketCan socket_;
 public:
  Emulator(const std::string &);
  bool Emulate();
  bool ReadData();
};



#endif  // EMULATOR_HPP NOLINT
