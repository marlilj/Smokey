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

#include "engine_pindle_states.hpp"
#include "smokey_data.hpp"


int16_t PindleModes::OffMode(Values_t &data) {
  data.activate_engine = false;
  data.pindle_neutral = false;
  data.pindle_drive = false;
  data.pindle_reverse = false;
  data.parking_flag = true;

  return 0;
}

int16_t PindleModes::PindleParking(Values_t &data) {
  data.activate_engine = true;
  data.pindle_neutral = false;
  data.pindle_drive = false;
  data.pindle_reverse = false;
  data.pindle_set_value = PINDLE_PARKING;
  data.parking_flag = true;

  return 0;
}

int16_t PindleModes::PindleNeutral(Values_t &data) {
  data.activate_engine = true;
  data.pindle_neutral = true;
  data.pindle_drive = false;
  data.pindle_reverse = false;
  data.parking_flag = false;

  return 0;
}
int16_t PindleModes::PindleDrive(Values_t &data) {
  data.activate_engine = true;
  data.pindle_neutral = false;
  data.pindle_drive = true;
  data.pindle_reverse = false;
  data.parking_flag = false;

  return 0;
}
int16_t PindleModes::PindleReverse(Values_t &data) {
  data.activate_engine = true;
  data.pindle_neutral = false;
  data.pindle_drive = false;
  data.pindle_reverse = true;
  data.parking_flag = false;

  return 0;
}
