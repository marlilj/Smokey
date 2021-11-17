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

#include "../include/interface_from_input_handler.hpp"

#include <iostream> // NOLINT
#include <string> // NOLINT

int16_t GetNewValues::getNewValues(Payload_t &payload) {
  bool error_code = kFailure;

  std::cout << "GetNewValue function stores throttle value "
                << payload.throttle << " and gear "
                << payload.gear << "\n" << std::endl;
  CanFrame input_can_frame;

  // std::cout << "GetNewValue function stores throttle value " << value_from_input_handler << "\n" << std::endl; // NOLINT
  // Do stuff in the CAN Encoder.
  input_can_frame = GetNewValues::convertCANMessageFromStruct(payload);
  GetNewValues::printCANFrame(input_can_frame);
  bool message_sent = GetNewValues::sendMessageOnCAN(input_can_frame);
  error_code = kSuccess; // NOLINT
  return error_code;
}

CanFrame GetNewValues::convertCANMessageFromStruct(const Payload_t &input_data) {
  CanFrame input_can_frame;
  input_can_frame.id = 1;
  input_can_frame.len = 2;
  input_can_frame.data[0] = input_data.throttle;
  input_can_frame.data[1] = input_data.gear;
  return input_can_frame;
}

bool GetNewValues::sendMessageOnCAN(const CanFrame &frame_to_send) {
  bool return_val = false;
  SocketCan socket_can("vcan0");
  if (socket_can.getStatus() == STATUS_OK) {
    auto write_status = socket_can.write(frame_to_send);
    if (write_status == STATUS_OK) {
      return_val = true;
    }
  }
  return return_val;
}

void GetNewValues::printCANFrame(const CanFrame &frame) {
  printf("len %d byte, id: %d \ndata: ", frame.id, frame.len);
  for ( int i = 0 ; i < frame.len ; i++ ) {
    printf("%02x ", frame.data[i]);
  }
  printf("\n");
}
