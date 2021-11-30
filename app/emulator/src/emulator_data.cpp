#include "emulator.hpp"

size_t EmulatorData::GetThrottleSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return throttle_set_value;
}
size_t EmulatorData::GetThrottle() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return throttle;
}
size_t EmulatorData::GetGearSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return gear_set_value;
}
size_t EmulatorData::GetStartSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return start_set_value;
}
size_t EmulatorData::GetGear() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return gear;
}
size_t EmulatorData::GetRpm() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return rpm;
}
size_t EmulatorData::GetSpeed() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return speed;
}
size_t EmulatorData::GetForwardForce() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return forward_force;
}
bool EmulatorData::GetActivateEngine() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return activate_engine;
}
bool EmulatorData::GetPindleNeutral() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return pindle_neutral;
}
bool EmulatorData::GetPindleDrive() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return pindle_drive;
}
bool EmulatorData::GetPindleReverse() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return pindle_reverse;
}
bool EmulatorData::GetParkingFlag() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return parking_flag;
}

void EmulatorData::SetThrottleSetValue(const size_t& throttle_in_set_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  throttle_set_value = throttle_in_set_val;
}
void EmulatorData::SetThrottle(const size_t& throttle_in_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  throttle = throttle_in_val;
}
void EmulatorData::SetGearSetValue(const size_t& gear_in_set_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  gear_set_value = gear_in_set_val;
}
void EmulatorData::SetStartSetValue(const size_t& start_in_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  start_set_value = start_in_val;
}
void EmulatorData::SetGear(const size_t& gear_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  gear = gear_val;
}
void EmulatorData::SetRpm(const size_t& rpm_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  rpm = rpm_val;
}
void EmulatorData::SetSpeed(const size_t& speed_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  speed = speed_val;
}
void EmulatorData::SetForwardForce(const size_t& forward_force_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  forward_force = forward_force_val;
}
void EmulatorData::SetActivateEngine(const bool& activate_engine_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  activate_engine = activate_engine_val;
}
void EmulatorData::SetPindleNeutral(const bool& pindle_neutral_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  pindle_neutral = pindle_neutral_val;
}
void EmulatorData::SetPindleDrive(const bool& pindle_drive_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  pindle_drive = pindle_drive_val;
}
void EmulatorData::SetPindleReverse(const bool& pindle_reverse_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  pindle_reverse = pindle_reverse_val;
}
void EmulatorData::SetParkingFlag(const bool& parking_flag_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  parking_flag = parking_flag_val;
}
