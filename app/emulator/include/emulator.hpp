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
#ifndef EMULATOR_HPP // NOLINT
#define EMULATOR_HPP

#include <unistd.h>
#include <iostream>
#include <string>
#include "canio.hpp"
#include "interface_from_input_handler.hpp"
#include "smokey_data.hpp"
#include "input_handler.hpp"
#include <utility>

// Gear and engine data
#define EMULATOR_IDLE_RPM 800
#define EMULATOR_MAX_RPM 5000

#define EMULATOR_GEAR_RATIO_R 1  // Reverse 1:1
#define EMULATOR_GEAR_RATIO_P 0   // Parked, no gear
#define EMULATOR_GEAR_RATIO_N 0   // Neutral, no gear
#define EMULATOR_GEAR_RATIO_1 3  // 3:1
#define EMULATOR_GEAR_RATIO_2 2  // 2:1
#define EMULATOR_GEAR_RATIO_3 1.5  // 1.5:1
#define EMULATOR_GEAR_RATIO_4 1  // 1:1
#define EMULATOR_GEAR_RATIO_5 5   // 0.5:1
#define DRIVE_TRAIN_RATIO 3.460   // 3.460
#define DRIVE_TRAIN_EFFICIENY 0.97 
#define PINDLE_PARKING 112  // Gear parking, dec 112
#define PINDLE_NEUTRAL 110  // Gear parking, dec 112
#define PINDLE_DRIVE 100  // Gear parking, dec 112
#define PINDLE_REVERSE 114  // Gear parking, dec 112

const float emulator_gear_ratio[5] = {
  EMULATOR_GEAR_RATIO_1,
  EMULATOR_GEAR_RATIO_2,
  EMULATOR_GEAR_RATIO_3,
  EMULATOR_GEAR_RATIO_4,
  EMULATOR_GEAR_RATIO_5};

// CHANGE Gear ratio!?
// 1 4.171
// 2 2.340
// 3 1.521
// 4 1.143
// 5 0.867
// 6 0.691
// Final drive 3.460

#define EMULATOR_GEAR_0 0
#define EMULATOR_GEAR_1 1
#define EMULATOR_GEAR_2 2
#define EMULATOR_GEAR_3 3
#define EMULATOR_GEAR_4 4
#define EMULATOR_GEAR_5 5

#define GEAR_HIGH_RPM 4000
#define GEAR_LOW_RPM 1000
#define MAX_SPEED 180.0

// Emulator calculation data
#define WHEEL_RADIUS 0.34   // 225/55R17
#define VEHICLE_MASS 1700.0     // kg
#define ROAD_COEFF 0.011
#define ROAD_RESISTANCE_FORCE (VEHICLE_MASS * ROAD_COEFF * 9.82)
#define DT 10              // dt delay for calculating speed, TODO use system timer instead.

#define AIR_DENSITY 1.202       // kg/m3
#define VEHICLE_FRONTAL_AREA 3.0  // m2
#define VEHICLE_DRAG_COEFF 0.5



// Fancy Emulation data
#define FE_VELOCITY_AT_0 0
#define FE_VELOCITY_AT_10 30
#define FE_VELOCITY_AT_20 50
#define FE_VELOCITY_AT_30 60
#define FE_VELOCITY_AT_40 70
#define FE_VELOCITY_AT_50 90
#define FE_VELOCITY_AT_60 100
#define FE_VELOCITY_AT_70 120
#define FE_VELOCITY_AT_80 140
#define FE_VELOCITY_AT_90 160
#define FE_VELOCITY_AT_100 180

#define FE_RPM_AT_0 EMULATOR_IDLE_RPM
#define FE_RPM_AT_10 1200
#define FE_RPM_AT_20 1600
#define FE_RPM_AT_30 3000
#define FE_RPM_AT_40 2000
#define FE_RPM_AT_50 3200
#define FE_RPM_AT_60 2200
#define FE_RPM_AT_70 3200
#define FE_RPM_AT_80 2100
#define FE_RPM_AT_90 3200
#define FE_RPM_AT_100 4000

#define FE_GEAR_AT_0 EMULATOR_GEAR_0
#define FE_GEAR_AT_10 EMULATOR_GEAR_1
#define FE_GEAR_AT_20 EMULATOR_GEAR_2
#define FE_GEAR_AT_30 EMULATOR_GEAR_2
#define FE_GEAR_AT_40 EMULATOR_GEAR_3
#define FE_GEAR_AT_50 EMULATOR_GEAR_3
#define FE_GEAR_AT_60 EMULATOR_GEAR_4
#define FE_GEAR_AT_70 EMULATOR_GEAR_4
#define FE_GEAR_AT_80 EMULATOR_GEAR_5
#define FE_GEAR_AT_90 EMULATOR_GEAR_5
#define FE_GEAR_AT_100 EMULATOR_GEAR_5

typedef struct EmulatorData {
  size_t throttle_set_value = 0;
  size_t throttle = 0;
  size_t pindle_set_value = PINDLE_PARKING;
  size_t start_set_value = false;
  size_t gear = 0;
  size_t rpm = 0;
  double speed = 0.0;
  double engine_torque = 0.0;
  double forward_force = 0;
  bool activate_engine = false;
  bool gear_neutral = false;
  bool gear_drive = false;
  bool gear_reverse = false;
  bool parking_flag = false;
} EmulatorData_t;

#define RPM_TORQUE_DATA_LENGTH 9
const std::pair<double, double> RPM_Torque[RPM_TORQUE_DATA_LENGTH] = {
  std::make_pair(800, 116),
  std::make_pair(1312, 135),
  std::make_pair(1800, 148),
  std::make_pair(2276, 157),
  std::make_pair(2800, 165),
  std::make_pair(3316, 172),
  std::make_pair(3806, 178),
  std::make_pair(4300, 184),
  std::make_pair(4770, 188)};

const std::pair<int, int> emulator_gear_limits[10] = {
  std::make_pair(0, 1),
  std::make_pair(1, 3),
  std::make_pair(1, 3),
  std::make_pair(1, 3),
  std::make_pair(2, 4),
  std::make_pair(2, 4),
  std::make_pair(2, 5),
  std::make_pair(3, 5),
  std::make_pair(3, 5),
  std::make_pair(3, 5)};

// Simple RPM curve
const int throttle_to_RPM_one_gear[10] = {
  EMULATOR_IDLE_RPM,
  EMULATOR_IDLE_RPM + 400,
  EMULATOR_IDLE_RPM + 800,
  EMULATOR_IDLE_RPM + 1200,
  EMULATOR_IDLE_RPM + 1600,
  EMULATOR_IDLE_RPM + 2000,
  EMULATOR_IDLE_RPM + 2400,
  EMULATOR_IDLE_RPM + 2800,
  EMULATOR_IDLE_RPM + 3000,
  EMULATOR_MAX_RPM};

class Emulator{
  EmulatorData_t emulator_data_;
  /* SocketCan socket_; */
 public:
  Emulator(const std::string &); // NOLINT
  bool Emulate();
  bool ReadData();
  bool sendCAN();
// Calculations
  bool UpdateGearAutomatic();
  bool CalculateRPM();
  bool CalculateSpeed();
  bool CalculateForce();
  bool GetEngineTorque();

  // ...
  bool FancyEmulation();
};

#endif  // EMULATOR_HPP  // NOLINT
