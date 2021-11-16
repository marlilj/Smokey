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

#include "../include/InterfaceToCANEncoder.hpp"

#include <iostream>
#include <string>

#include "../../can_encoder/include/interface_from_input_handler.hpp"

GetNewValues get_new_values;

bool SendNewValues::sendNewValues(std::string value_to_can_encoder) {
  bool signal_received = false;
  // signal_received = true;
  signal_received = get_new_values.getNewValues(value_to_can_encoder);
  // Do stuff with the bool value "signal received".
  std::cout << "1.Signal received returned from GetNewValue function: " << signal_received << "\n" << std::endl;
  return signal_received;
}
