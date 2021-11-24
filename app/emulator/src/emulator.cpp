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

#include "emulator.hpp"

InputHandler smokeyInputData;

Emulator::Emulator(const std::string& interface_name)
: socket_(interface_name) {}
// Data init
// this->emulator_data.rpm = EMULATOR_IDLE_RPM;
// }

bool Emulator::ReadData() {
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    this->emulator_data_.throttle_set_value = fr.data[0];
    this->emulator_data_.gear_set_value = fr.data[1];
    this->emulator_data_.start_set_value = fr.data[2];
    return true;
  } else {
    return false;
  }
}

bool Emulator::Emulate() {
  bool error_code = kFailure;
  int8_t set_gear = 'P';
  bool set_start = false;
  int set_throttle = 0;

  // Read CAN message
  if(ReadData()) {
    // std::cout << "Throttle set value: " << this->emulator_data_.throttle_set_value << " Gear set value: " << this->emulator_data_.gear_set_value << std::endl;
    set_start = this->emulator_data_.start_set_value;
    
    this->emulator_data_.throttle = this->emulator_data_.throttle_set_value;
    this->emulator_data_.rpm = throttle_to_RPM_one_gear[(this->emulator_data_.throttle)/10];
    // Ugly print...
    // std::cout << "                                                         \r" << std::flush;
    // std::cout << "Throttle: " << this->emulator_data_.throttle << " RPM: " << this->emulator_data_.rpm << "\r" << std::flush;
    
    if (this->emulator_data_.start_set_value == 115
        && this->emulator_data_.gear_set_value == 112 && set_start == false) {
      set_start = true;
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
      smokeyInputData.SmokeyInputData.gear = 112-32;
      set_gear = smokeyInputData.SmokeyInputData.gear;
    } else if (this->emulator_data_.gear_set_value == 100
              && set_start == true) {
      set_gear = 'D';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 100
              && set_start != true) {
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
      smokeyInputData.SmokeyInputData.gear = 112-32;
      set_gear = smokeyInputData.SmokeyInputData.gear;
    } else if (this->emulator_data_.gear_set_value == 112
              && set_start == true) {
      set_gear = 'P';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 112
              && set_start != true) {
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
      smokeyInputData.SmokeyInputData.gear = 112-32;
      set_gear = smokeyInputData.SmokeyInputData.gear;
    } else if (this->emulator_data_.gear_set_value == 110
              && set_start == true) {
      set_gear = 'N';
      set_throttle = this->emulator_data_.throttle_set_value;
    } else if (this->emulator_data_.gear_set_value == 110
              && set_start != true) {
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
      smokeyInputData.SmokeyInputData.gear = 112-32;
      set_gear = smokeyInputData.SmokeyInputData.gear;
    } else if (this->emulator_data_.gear_set_value == 114
              && set_start == true) {
      set_gear = 'R';
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
    } else if (this->emulator_data_.gear_set_value == 114
              && set_start != true) {
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
      smokeyInputData.SmokeyInputData.gear = 112-32;
      set_gear = smokeyInputData.SmokeyInputData.gear;
    } else {
      set_start = this->emulator_data_.start_set_value;
      set_gear = 'P';
      smokeyInputData.SmokeyInputData.throttle = 0;
      set_throttle = smokeyInputData.SmokeyInputData.throttle;
    }
    this->sendCAN();
    // std::cout << "Throttle: " << set_throttle << " Gear: "
    // << set_gear << " Start: " << set_start << std::endl;
  }
  usleep(5);

  error_code = kSuccess;

  return error_code;
}

bool Emulator::sendCAN() {
  // Construct the data to be sent
  EmulatorOutput_t data_to_send;
  data_to_send.speed = static_cast<uint8_t>(this->emulator_data_.speed);
  data_to_send.gear = static_cast<uint8_t>(this->emulator_data_.gear);
  data_to_send.rpm = static_cast<uint16_t>(this->emulator_data_.rpm);

  // Construct obejct from libcanencoder
  GetNewValues gnv;
  CanFrame frame_to_send = gnv.convertCANMessageFromStruct(data_to_send);
  bool return_value = gnv.sendMessageOnCAN(frame_to_send);
  return return_value;
}
