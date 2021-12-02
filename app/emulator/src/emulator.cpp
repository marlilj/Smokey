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


#include <unistd.h>
#include <math.h>
#include <iostream>
#include <chrono>  // NOLINT due to unapproved C++11 header
#include <thread>  // NOLINT due to unapproved C++11 header
#include "emulator.hpp"
#include "engine_pindle_states.hpp"
#include "smokey_data.hpp"
#include "input_handler.hpp"

InputHandler smokeyInputData;

bool Emulator::ReadData(Values_t &data) {
  SocketCan socket_(interface_name_);
  bool retval = false;
  CanFrame fr;
  if (socket_.read(fr) == STATUS_OK) {
    if (fr.id == 1) {  // TODO(Niklas): add macro for CAN frame IDs
      data.throttle_set_value = fr.data[0];
      data.pindle_set_value = fr.data[1];
      data.start_set_value = fr.data[2];
      data.break_set_value = fr.data[3];
      data.shutdown_set_value = fr.data[4];
      retval = true;
    }
  }
  return retval;
}

Emulator::Emulator(const std::string& interface_name) {
  interface_name_ = interface_name;
}

bool Emulator::Emulate(std::atomic<bool> *exit_flag) {
  int error_code = kFailure;
  bool brake_toggle = false;

  while (!exit_flag->load()) {
    Values_t values = emulator_data_.GetAll();
    if (values.activate_engine) {
      if (values.pindle == PindleModes::D
          && (values.throttle > 0 || values.speed > 0)
          && values.gear != 0) {
        if (!values.breaking_flag) {
          // Break is inactive
          if (brake_toggle) {
            // Brake has been released
            brake_toggle = false;
            if (values.speed > 0) {
              values.gear = emulator_gear_limits[values.throttle/10].first;
              values.rpm = throttle_to_RPM_one_gear[values.throttle/10];
            } else {
              values.gear = EMULATOR_GEAR_1;
              values.rpm = 0;
            }
          }
          this->calculateEngineTorque(&values);
          this->CalculateForce(&values);
          this->CalculateSpeed(&values);
        } else if (values.speed > 1) {
          brake_toggle = true;
          values.speed = values.speed - BRAKE_POWER;
        } else if (values.speed < 1) {
          brake_toggle = true;
          values.speed = 0;
        }
      }
      this->CalculateRPM(&values);
      this->UpdateGearAutomatic(&values);
      this->sendCAN(values);
      error_code = emulator_data_.SetAll(values);
    } else {
      this->sendCAN(values);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(DT/100));
  }
  Values_t values = emulator_data_.GetAll();
  values.speed = 0.0;
  values.rpm = 0;
  values.activate_engine = 0;
  values.gear = 0;

  for (size_t i = 0 ; i < 10 ; i++) {
    this->sendCAN(values);
    std::this_thread::sleep_for(std::chrono::milliseconds(DT/100));
  }

  return error_code;
}

bool Emulator::CalculateSpeed(Values_t *data) {
  bool error_code = kFailure;

  if (data->speed < MAX_SPEED) {
    data->speed = data->speed
      + ( (data->forward_force / VEHICLE_MASS) * (DT/1000.0));
    error_code = kSuccess;
  }

  return error_code;
}


bool Emulator::ReadAndSetPindle(std::atomic<bool> *exit_flag) {
  int error_code = kFailure;
  int8_t set_pindle = PINDLE_PARKING;
  bool started = false;
  bool shutdown = false;

  // Read CAN message
  while (!exit_flag->load()) {
    Values_t values = emulator_data_.GetAll();
    if (ReadData(values)) {
      started = values.start_set_value;
      set_pindle = values.pindle_set_value;
      values.throttle = values.throttle_set_value;
      values.breaking_flag = values.break_set_value;
      values.shutdown_flag = values.shutdown_set_value;

      if (values.shutdown_flag) {
        *exit_flag = true;
        std::cout << "Exiting .. " << std::endl;
      }

      if (set_pindle == PINDLE_PARKING && started) {
          values.pindle = PindleModes::P;
          values.activate_engine = true;
      } else if ((values.pindle == PindleModes::P || values.pindle == PindleModes::N) &&  // NOLINT Due to line break making it less readable.
                  set_pindle == PINDLE_DRIVE && started) {
          values.pindle = PindleModes::D;
          started = true;
          values.gear = 1;
      } else if (values.pindle == PindleModes::P && set_pindle == PINDLE_NEUTRAL && started) {  // NOLINT Due to line break making it less readable.
          values.pindle = PindleModes::N;
          started = true;
      } else if ((values.pindle == PindleModes::P || values.pindle == PindleModes::N) &&  // NOLINT Due to line break making it less readable.
                  set_pindle == PINDLE_REVERSE && started) {
          values.pindle = PindleModes::R;
          started = true;
      } else if (set_pindle == PINDLE_PARKING && !started) {
          values.pindle = PindleModes::P;
          values.activate_engine = false;
          values.rpm = 0;
          started = false;
      }
    }
    error_code = emulator_data_.SetAll(values);
    std::this_thread::sleep_for(std::chrono::milliseconds(DT/100));
  }
  return error_code;
}

bool Emulator::CalculateForce(Values_t *data) {
  bool error_code = kFailure;


  float f_t = (data->engine_torque
    * emulator_gear_ratio[data->gear-1]
    * DRIVE_TRAIN_RATIO
    * DRIVE_TRAIN_EFFICIENY )
    / WHEEL_RADIUS;

  float f_a = 0.5 * (AIR_DENSITY * VEHICLE_FRONTAL_AREA * VEHICLE_DRAG_COEFF
        * ((data->speed)*(data->speed)) );

  data->forward_force = f_t - f_a - ROAD_RESISTANCE_FORCE;

  error_code = kSuccess;

  return error_code;
}


bool Emulator::calculateEngineTorque(Values_t *data) {
  bool error_code = kSuccess;
  double torque = 0;

  if (data->rpm < EMULATOR_IDLE_RPM) {
      // Engine not running
      torque = RPM_Torque[0].second;  // Set to torque for idle rpm
  } else {
    for (size_t i = 0; i < RPM_TORQUE_DATA_LENGTH-1; i++) {
      if (data->rpm == RPM_Torque[i].first) {
        torque = RPM_Torque[i].second;
        break;
      } else if (data->rpm < RPM_Torque[i+1].first) {
        // Interpolate
        torque = RPM_Torque[i].second +
          (data->rpm-RPM_Torque[i].first)*
          ((RPM_Torque[i+1].second-RPM_Torque[i].second)/
          (RPM_Torque[i+1].first-RPM_Torque[i].first));
          break;
      } else {
        torque = RPM_Torque[i+1].second;
        // break;
      }
    }
  }

  data->engine_torque = (torque
    * data->throttle * 0.01);

  return error_code;
}

bool Emulator::UpdateGearAutomatic(Values_t *data) {
  bool error_code = kFailure;

  if ((data->rpm > GEAR_HIGH_RPM)
      && (emulator_gear_limits[(data->throttle)/10].second
      > data->gear) ) {
    // Switch up to next gear
    switch (data->gear) {
      case EMULATOR_GEAR_1:
        data->gear = EMULATOR_GEAR_2;
        data->rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_2:
        data->gear = EMULATOR_GEAR_3;
        data->rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_3:
        data->gear = EMULATOR_GEAR_4;
        data->rpm = GEAR_LOW_RPM;
        break;
      case EMULATOR_GEAR_4:
        data->gear = EMULATOR_GEAR_5;
        data->rpm = GEAR_LOW_RPM;
        break;
      default:  // EMULATOR_GEAR_5
        break;
    }
    error_code = kSuccess;
  } else if ((data->rpm < GEAR_LOW_RPM)
      && (emulator_gear_limits[(data->throttle)/10].first <
      data->gear)) {
    // Switch gear down
    switch (data->gear) {
      case EMULATOR_GEAR_2:
        data->gear = EMULATOR_GEAR_1;
        data->rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_3:
        data->gear = EMULATOR_GEAR_2;
        data->rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_4:
        data->gear = EMULATOR_GEAR_3;
        data->rpm = GEAR_HIGH_RPM;
        break;
      case EMULATOR_GEAR_5:
        data->gear = EMULATOR_GEAR_4;
        data->rpm = GEAR_HIGH_RPM;
        break;
      default:  // EMULATOR_GEAR_1
        break;
    }
    error_code = kSuccess;
  }

  return error_code;
}

bool Emulator::CalculateRPM(Values_t *data) {
  if (data->speed >= 0) {
    data->rpm = (30/3.14)
      * (data->speed / WHEEL_RADIUS)
      * DRIVE_TRAIN_RATIO * emulator_gear_ratio[data->gear-1];
  }

  if (data->rpm <= EMULATOR_IDLE_RPM) {
    data->rpm = EMULATOR_IDLE_RPM - std::rand()%50;
  } else if (data->rpm >= EMULATOR_MAX_RPM) {
    data->rpm = EMULATOR_MAX_RPM + std::rand()%50;
  }
  return true;
}


bool Emulator::sendCAN(const Values_t &data) {
  // Construct the data to be sent
  EmulatorOutput_t data_to_send;
  data_to_send.speed = static_cast<uint8_t>(data.speed*3.6);
  data_to_send.gear = static_cast<uint8_t>(data.gear);
  data_to_send.rpm = static_cast<uint16_t>(data.rpm);
  data_to_send.pindle = static_cast<uint8_t>(data.pindle);

  // Construct obejct from libcanencoder
  GetNewValues gnv;
  CanFrame frame_to_send = gnv.convertCANMessageFromStruct(data_to_send);
  bool return_value = gnv.sendMessageOnCAN(frame_to_send);
  return return_value;
}

bool Emulator::GracefulShutdown() {
  bool error_code = kFailure;
  // Delete stuff!
  error_code = kSuccess;
  return error_code;
}

