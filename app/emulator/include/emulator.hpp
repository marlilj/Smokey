/*
 * Copyright (C) 2021 - Volvo Car Corporation
 *
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

#ifndef EMULATOR_HPP // NOLINT
#define EMULATOR_HPP

#include <unistd.h>
#include <iostream>
#include <string>
#include "canio.hpp"
#include "interface_from_input_handler.hpp"
#include "input_handler.hpp"
#include <utility>
#include <mutex>
#include <shared_mutex>

// Gear and engine data
#define EMULATOR_IDLE_RPM 800
#define EMULATOR_MAX_RPM 4000

#define EMULATOR_GEAR_RATIO_R 10  // Reverse 1:1
#define EMULATOR_GEAR_RATIO_P 0   // Parked, no gear
#define EMULATOR_GEAR_RATIO_N 0   // Neutral, no gear
#define EMULATOR_GEAR_RATIO_1 30  // 3:1
#define EMULATOR_GEAR_RATIO_2 20  // 2:1
#define EMULATOR_GEAR_RATIO_3 15  // 1.5:1
#define EMULATOR_GEAR_RATIO_4 10  // 1:1
#define EMULATOR_GEAR_RATIO_5 5   // 0.5:1
#define DRIVE_TRAIN_RATIO 3.460   // 3.460
#define PINDLE_PARKING 112  // Gear parking, dec 112
#define PINDLE_NEUTRAL 110  // Gear parking, dec 112
#define PINDLE_DRIVE 100  // Gear parking, dec 112
#define PINDLE_REVERSE 114  // Gear parking, dec 112


#define EMULATOR_GEAR_0 0
#define EMULATOR_GEAR_1 1
#define EMULATOR_GEAR_2 2
#define EMULATOR_GEAR_3 3
#define EMULATOR_GEAR_4 4
#define EMULATOR_GEAR_5 5

#define GEAR_HIGH_RPM 2500
#define GEAR_LOW_RPM 1000

// Emulator calculation data
#define WHEEL_RADIUS 33.909   // 225/55R17
#define VEHICLE_MASS 1700     // kg
#define DT 1000000              // dt delay for calculating speed, TODO use system timer instead.

#define AIR_DENSITY 1.202       // kg/m3
#define VEHICLE_FRONTAL_AREA 3  // m3
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

// CHANGE Gear ratio!?
// 1 4.171
// 2 2.340
// 3 1.521
// 4 1.143
// 5 0.867
// 6 0.691
// Final drive 3.460



typedef struct Values {
    size_t throttle_set_value = 0;
    size_t throttle;
    size_t pindle_set_value = PINDLE_PARKING;
    size_t start_set_value = false;
    size_t gear;
    size_t rpm;
    size_t speed;
    size_t forward_force = 0;
    bool activate_engine = false;
    bool pindle_neutral = false;
    bool pindle_drive = false;
    bool pindle_reverse = false;
    bool parking_flag = false;
  } Values_t;

class EmulatorData {
 private:
  Values_t values;
  std::shared_mutex emulator_data_mutex_;

 public:
  size_t GetThrottleSetValue();
  size_t GetThrottle();
  size_t GetGearSetValue();
  size_t GetStartSetValue();
  size_t GetGear();
  size_t GetRpm();
  size_t GetSpeed();
  size_t GetForwardForce();
  bool GetActivateEngine();
  bool GetPindleNeutral();
  bool GetPindleDrive();
  bool GetPindleReverse();
  bool GetParkingFlag();
  Values GetAll();

  void SetThrottleSetValue(const size_t &);
  void SetThrottle(const size_t &);
  void SetGearSetValue(const size_t &);
  void SetStartSetValue(const size_t &);
  void SetPindleDrive(const size_t &);
  void SetGear(const size_t &);
  void SetRpm(const size_t &);
  void SetSpeed(const size_t &);
  void SetForwardForce(const size_t &);
  void SetActivateEngine(const bool &);
  void SetPindleNeutral(const bool &);
  void SetPindleDrive(const bool &);
  void SetPindleReverse(const bool &);
  void SetParkingFlag(const bool &);
  bool SetAll(const Values &);
};

typedef EmulatorData EmulatorData_t;

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

class Emulator {
  EmulatorData_t emulator_data_;
  /* SocketCan socket_; */
 public:
  Emulator(const std::string &); // NOLINT
  bool Emulate();
  bool ReadData(Values_t &);
  bool sendCAN(const Values_t &);
// Calculations
  bool UpdateGearAutomatic();
  bool SetRPM(size_t _rpm);
  bool SetGear(size_t _gear);
  bool CalculateSpeed();
  bool CalculateForce();
  size_t GetEngineTorque();
  size_t GetAirResistance();

  // ...
  bool FancyEmulation(Values_t &);
  bool ReadAndSetPindle();
  bool GracefulShutdown();
};

#endif  // EMULATOR_HPP  // NOLINT
