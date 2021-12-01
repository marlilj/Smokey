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
#include <stdlib.h>     /* rand */
#include <iostream>
#include <string>
#include <utility>
#include <mutex>  // NOLINT due to unapproved C++11 header
#include <shared_mutex>
#include <atomic>
#include <functional>
#include "canio.hpp"
#include "interface_from_input_handler.hpp"
#include "input_handler.hpp"

// Gear and engine data
#define EMULATOR_IDLE_RPM 800
#define EMULATOR_MAX_RPM 5000

#define EMULATOR_GEAR_RATIO_R 1.0  // Reverse 1:1
#define EMULATOR_GEAR_RATIO_P 0.0   // Parked, no gear
#define EMULATOR_GEAR_RATIO_N 0.0   // Neutral, no gear
#define EMULATOR_GEAR_RATIO_1 3.0  // 3:1
#define EMULATOR_GEAR_RATIO_2 2.0  // 2:1
#define EMULATOR_GEAR_RATIO_3 1.5  // 1.5:1
#define EMULATOR_GEAR_RATIO_4 1.0  // 1:1
#define EMULATOR_GEAR_RATIO_5 1.0   // 0.5:1
#define DRIVE_TRAIN_RATIO 3.460   // 3.460
#define DRIVE_TRAIN_EFFICIENY 0.97
#define PINDLE_PARKING 112  // Pindle parking, dec 112
#define PINDLE_NEUTRAL 110  // Pindle neutral, dec 110
#define PINDLE_DRIVE 100  // Pindle frive, dec 110
#define PINDLE_REVERSE 114  // Pindle reverse, dec 114
#define CAR_START 113  // Car start, dec 113
#define CAR_BREAK 98  // Pindle break, dec 98

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

#define GEAR_HIGH_RPM 3500
#define GEAR_LOW_RPM 1000
#define MAX_SPEED 180.0/3.6

// Emulator calculation data
const float WHEEL_RADIUS = 0.34;  // 225/55R17
const float VEHICLE_MASS = 1700.0;     // kg
const float ROAD_COEFF = 0.011;
const float ROAD_RESISTANCE_FORCE = (VEHICLE_MASS * ROAD_COEFF * 9.82);
const int DT = 100;  // dt delay for calculating speed in mikro seconds

#define AIR_DENSITY 1.202       // kg/m3
#define VEHICLE_FRONTAL_AREA 3.0  // m2
#define VEHICLE_DRAG_COEFF 0.5

typedef struct Values {
    size_t throttle_set_value = 0;
    size_t throttle = 0;
    size_t pindle_set_value = PINDLE_PARKING;
    size_t start_set_value = false;
    size_t break_set_value = CAR_BREAK;
    size_t shutdown_set_value = CAR_START;
    size_t gear = 0;
    float rpm = EMULATOR_IDLE_RPM;
    float speed = 0.0;
    float forward_force = 0.0;
    float engine_torque = 0.0;
    bool activate_engine = false;
    bool pindle_neutral = false;
    bool pindle_drive = false;
    bool pindle_reverse = false;
    bool parking_flag = false;
    bool breaking_flag = false;
    bool shutdown_flag = false;
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
  bool GetBreakingFlag();
  bool GetParkingFlag();
  bool GetShutdownFlag();
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
  void SetBreakingFlag(const bool &);
  void SetParkingFlag(const bool &);
  void SetShutdownFlag(const bool &);
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

const std::pair<int, int> emulator_gear_limits[10] = {
  std::make_pair(0, 1),
  std::make_pair(1, 2),
  std::make_pair(1, 2),
  std::make_pair(1, 3),
  std::make_pair(2, 3),
  std::make_pair(2, 4),
  std::make_pair(2, 4),
  std::make_pair(3, 4),
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

class Emulator {
  EmulatorData_t emulator_data_;
  /* SocketCan socket_; */
  std::string interface_name_{};
 public:
  Emulator(const std::string &); // NOLINT no marking explixit.
  bool Emulate(std::atomic<bool> *exit_flag);
  bool ReadData(Values_t &);
  bool sendCAN(const Values_t &);
// Calculations
  bool UpdateGearAutomatic(Values_t *data);
  bool CalculateRPM(Values_t *data);
  bool CalculateSpeed(Values_t *data);
  bool CalculateForce(Values_t *data);
  bool calculateEngineTorque(Values_t *data);

  // ...
  bool ReadAndSetPindle(std::atomic<bool> *exit_flag);
  bool GracefulShutdown();
};

#endif  // EMULATOR_HPP  // NOLINT
