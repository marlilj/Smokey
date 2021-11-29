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

#include "../include/engine_pindle_states.hpp"

#include "smokey_data.hpp"
#include <mutex>


 std::recursive_mutex thread1_mutex;


int16_t PindleModes::OffMode(EmulatorData_t &emulator_data_) {
 std::lock_guard<std::recursive_mutex> guard(thread1_mutex);
  emulator_data_.activate_engine = false;
  emulator_data_.gear_neutral = false;
  emulator_data_.gear_drive = false;
  emulator_data_.gear_reverse = false;
  emulator_data_.parking_flag = true;
  std::lock_guard<std::recursive_mutex> unlock(thread1_mutex);
  return 0;
}

int16_t PindleModes::PindleParking(EmulatorData_t &emulator_data_) {
  std::lock_guard<std::recursive_mutex> guard(thread1_mutex);
  emulator_data_.activate_engine = true;
  emulator_data_.gear_neutral = false;
  emulator_data_.gear_drive = false;
  emulator_data_.gear_reverse = false;
  emulator_data_.gear_set_value = PINDLE_PARKING;
  emulator_data_.parking_flag = true;
  std::lock_guard<std::recursive_mutex> unlock(thread1_mutex);

  return 0;
}

int16_t PindleModes::PindleNeutral(EmulatorData_t &emulator_data_) {
  std::lock_guard<std::recursive_mutex> guard(thread1_mutex);
  emulator_data_.activate_engine = true;
  emulator_data_.gear_neutral = true;
  emulator_data_.gear_drive = false;
  emulator_data_.gear_reverse = false;
  emulator_data_.parking_flag = false;
  std::lock_guard<std::recursive_mutex> unlock(thread1_mutex);

  return 0;
}
int16_t PindleModes::PindleDrive(EmulatorData_t &emulator_data_) {
  std::lock_guard<std::recursive_mutex> guard(thread1_mutex);
  emulator_data_.activate_engine = true;
  emulator_data_.gear_neutral = false;
  emulator_data_.gear_drive = true;
  emulator_data_.gear_reverse = false;
  emulator_data_.parking_flag = false;
  std::lock_guard<std::recursive_mutex> unlock(thread1_mutex);

  return 0;
}
int16_t PindleModes::PindleReverse(EmulatorData_t &emulator_data_) {
  std::lock_guard<std::recursive_mutex> guard(thread1_mutex);
  emulator_data_.activate_engine = true;
  emulator_data_.gear_neutral = false;
  emulator_data_.gear_drive = false;
  emulator_data_.gear_reverse = true;
  emulator_data_.parking_flag = false;
  std::lock_guard<std::recursive_mutex> unlock(thread1_mutex);

  return 0;
}
