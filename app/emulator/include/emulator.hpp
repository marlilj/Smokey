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
#include <string>
#include "../../../lib/libcanio/include/canio.hpp"

#define EMULATOR_IDLE_RPM 800
#define EMULATOR_MAX_RPM 4000

#define EMULATOR_GEAR_RATIO_1 30  // 3:1
#define EMULATOR_GEAR_RATIO_2 20  // 2:1
#define EMULATOR_GEAR_RATIO_3 15  // 1.5:1
#define EMULATOR_GEAR_RATIO_4 10  // 1:1
#define EMULATOR_GEAR_RATIO_5 5   // 0.5:1
#define PINDLE_PARKING 112  // Gear parking, dec 112
#define PINDLE_NEUTRAL 110  // Gear parking, dec 112
#define PINDLE_DRIVE 100  // Gear parking, dec 112
#define PINDLE_REVERSE 114  // Gear parking, dec 112


typedef struct EmulatorData {
  size_t throttle_set_value = 0;
  size_t throttle;
  size_t gear_set_value = PINDLE_PARKING;
  size_t start_set_value = false;
  size_t gear;
  size_t rpm;
  size_t speed;
  bool activate_engine = false;
  bool gear_neutral = false;
  bool gear_drive = false;
  bool gear_reverse = false;
  bool parking_flag = false;
}EmulatorData_T;

// Simple RPM curve
const int throttle_to_RPM_one_gear[10] = {
  EMULATOR_IDLE_RPM,
  EMULATOR_IDLE_RPM + 400,
  EMULATOR_IDLE_RPM + 800,
  EMULATOR_IDLE_RPM + 1200,
  EMULATOR_IDLE_RPM + 1600,
  EMULATOR_IDLE_RPM + 2000,
  EMULATOR_IDLE_RPM + 2400,
  EMULATOR_IDLE_RPM + 2800,
  EMULATOR_IDLE_RPM + 3000,
  EMULATOR_MAX_RPM};

class Emulator{
  EmulatorData_T emulator_data_;
  SocketCan socket_;
 public:
  Emulator(const std::string &); // NOLINT
  bool Emulate();
  bool ReadData();
};



#endif  // EMULATOR_HPP NOLINT