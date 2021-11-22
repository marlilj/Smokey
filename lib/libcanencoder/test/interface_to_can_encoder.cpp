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

#include "smokey_data.hpp"

#include <iostream> // NOLINT
#include <string> // NOLINT

#include "../include/interface_from_input_handler.hpp"

GetNewValues get_new_values;

// Payload_t payload_;


// int16_t SendNewValues::sendNewValues() {
//   bool signal_received = false;
//   // signal_received = true;
//   // signal_received = get_new_values.getNewValues(value_to_can_encoder);
//   signal_received = get_new_values.getNewValues(payload);
//   // Do stuff with the bool value "signal received".
//   std::cout << "1.Signal sent through SendNewValues function: " << value_to_can_encoder << "\n" << std::endl; // NOLINT
//   std::cout << "1.Signal received returned from GetNewValue function: " << signal_received << "\n" << std::endl; // NOLINT
//   return value_to_can_encoder;
// }
