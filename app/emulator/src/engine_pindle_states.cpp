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


int16_t PindleModes::OffMode(EmulatorData_t &emulator_data_) {
  emulator_data_.SetActivateEngine(false);
  emulator_data_.SetPindleNeutral(false);
  emulator_data_.SetPindleDrive(false);
  emulator_data_.SetPindleReverse(false);
  emulator_data_.SetParkingFlag(true);

  return 0;
}

int16_t PindleModes::PindleParking(EmulatorData_t &emulator_data_) {
  emulator_data_.SetActivateEngine(true);
  emulator_data_.SetPindleNeutral(false);
  emulator_data_.SetPindleDrive(false);
  emulator_data_.SetPindleReverse(false);
  emulator_data_.SetGearSetValue(PINDLE_PARKING);
  emulator_data_.SetParkingFlag(true);

  return 0;
}

int16_t PindleModes::PindleNeutral(EmulatorData_t &emulator_data_) {
  emulator_data_.SetActivateEngine(true);
  emulator_data_.SetPindleNeutral(true);
  emulator_data_.SetPindleDrive(false);
  emulator_data_.SetPindleReverse(false);
  emulator_data_.SetParkingFlag(false);

  return 0;
}
int16_t PindleModes::PindleDrive(EmulatorData_t &emulator_data_) {
  emulator_data_.SetActivateEngine(true);
  emulator_data_.SetPindleNeutral(false);
  emulator_data_.SetPindleDrive(true);
  emulator_data_.SetPindleReverse(false);
  emulator_data_.SetParkingFlag(false);

  return 0;
}
int16_t PindleModes::PindleReverse(EmulatorData_t &emulator_data_) {
  emulator_data_.SetActivateEngine(true);
  emulator_data_.SetPindleNeutral(false);
  emulator_data_.SetPindleDrive(false);
  emulator_data_.SetPindleReverse(true);
  emulator_data_.SetParkingFlag(false);

  return 0;
}
