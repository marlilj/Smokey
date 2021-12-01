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

#ifndef INTERFACEFROMINPUTHANDLER_HPP  // NOLINT
#define INTERFACEFROMINPUTHANDLER_HPP

#include <ncurses.h>
#include <string.h>

#include <string>
#include <iostream>

#include "smokey_data.hpp"
#include "canio.hpp"


class GetNewValues {
 private:
 public:
  int16_t getNewValues(Payload_t &payload); // NOLINT

  CanFrame convertCANMessageFromStruct(const Payload_t &input_data);
  CanFrame convertCANMessageFromStruct(const EmulatorOutput_t &input_data);

  void printCANFrame(const CanFrame &frame);
  bool sendMessageOnCAN(const CanFrame &frame_to_send);
};

#endif  // INTERFACEFROMINPUTHANDLER_HPP // NOLINT
