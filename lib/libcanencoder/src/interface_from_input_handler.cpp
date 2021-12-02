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


#include "include/interface_from_input_handler.hpp"


int16_t GetNewValues::getNewValues(Payload_t &payload) {
  bool error_code = kFailure;

  CanFrame input_can_frame;

  input_can_frame = GetNewValues::convertCANMessageFromStruct(payload);

  bool message_sent = GetNewValues::sendMessageOnCAN(input_can_frame);
  error_code = kSuccess; // NOLINT
  return error_code;
}

CanFrame GetNewValues::convertCANMessageFromStruct(
                                          const Payload_t &input_data) {
  CanFrame input_can_frame;
  input_can_frame.id = 1;
  input_can_frame.len = 5;
  input_can_frame.data[0] = input_data.throttle;
  input_can_frame.data[1] = input_data.gear;
  input_can_frame.data[2] = input_data.start;
  input_can_frame.data[3] = input_data.breaking;
  input_can_frame.data[4] = input_data.shutdown;
  return input_can_frame;
}

CanFrame GetNewValues::convertCANMessageFromStruct(
                                          const EmulatorOutput_t &input_data) {
  CanFrame input_can_frame;
  input_can_frame.id = 2;
  input_can_frame.len = sizeof(EmulatorOutput_t);
  // Copying in little endian format
  memcpy(input_can_frame.data, &input_data, sizeof(input_data));
  return input_can_frame;
}

bool GetNewValues::sendMessageOnCAN(const CanFrame &frame_to_send) {
  bool return_val = false;
  SocketCan socket_can(this->interface_name);
  if (socket_can.getStatus() == STATUS_OK) {
    auto write_status = socket_can.write(frame_to_send);
    if (write_status == STATUS_OK) {
      return_val = true;
    }
  }
  return return_val;
}
