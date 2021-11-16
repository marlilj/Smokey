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
#include <string>

#include "../include/interface_from_input_handler.hpp"

int16_t value_to_can_encoder_;

GetNewValues get_new_values_;

int main() {
  int returnValue = false;

  value_to_can_encoder_ = get_new_values_.getNewValues();
  std::cout << "1. In main calling GetNewValue: " << value_to_can_encoder_ << "\n" << std::endl; // NOLINT
  returnValue = true;

  return returnValue;
}