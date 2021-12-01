
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

#ifndef ENGINEPINDLESTATES_HPP  // NOLINT
#define ENGINEPINDLESTATES_HPP


#include "emulator.hpp"

enum class PindleModes {
  P,
  N,
  R,
  D
};
/* class PindleModes {
 public:
  static int16_t OffMode(Values_t &emulator_data_);  // NOLINT
  static int16_t PindleParking(Values_t &emulator_data_);  // NOLINT
  static int16_t PindleNeutral(Values_t &emulator_data_);  // NOLINT
  static int16_t PindleDrive(Values_t &emulator_data_);  // NOLINT
  static int16_t PindleReverse(Values_t &emulator_data_);  // NOLINT
}; */


#endif // ENGINEPINDLESTATES_HPP  // NOLINT