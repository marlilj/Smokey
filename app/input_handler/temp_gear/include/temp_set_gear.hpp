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

#ifndef TEMPSETGEAR_HPP  // NOLINT
#define TEMPSETGEAR_HPP

#include <iostream>
#include <string>

#include "../../include/smokey_data.hpp"

class GearInput {
 public:
  const int kNotSet = 2;
  const int kBadValue = 3;
  int error_code = kFailure;
  int gear = -1;
  bool GearIsSet = false;

    int SetGear(int8_t selected_gear);

 private:
};




#endif // TEMPSETGEAR_HPP // NOLINT
