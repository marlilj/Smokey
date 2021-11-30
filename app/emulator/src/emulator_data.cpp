#include "emulator.hpp"

size_t EmulatorData::GetThrottleSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.throttle_set_value;
}
size_t EmulatorData::GetThrottle() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.throttle;
}
size_t EmulatorData::GetGearSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.pindle_set_value;
}
size_t EmulatorData::GetStartSetValue() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.start_set_value;
}
size_t EmulatorData::GetGear() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.gear;
}
size_t EmulatorData::GetRpm() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.rpm;
}
size_t EmulatorData::GetSpeed() {
  const std::shared_lock lock_s(emulator_data_mutex_);
  return values.speed;
}
size_t EmulatorData::GetForwardForce() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.forward_force;
}
bool EmulatorData::GetActivateEngine() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.activate_engine;
}
bool EmulatorData::GetPindleNeutral() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.pindle_neutral;
}
bool EmulatorData::GetPindleDrive() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.pindle_drive;
}
bool EmulatorData::GetPindleReverse() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.pindle_reverse;
}
bool EmulatorData::GetParkingFlag() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values.parking_flag;
}

void EmulatorData::SetThrottleSetValue(const size_t& throttle_in_set_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.throttle_set_value = throttle_in_set_val;
}
void EmulatorData::SetThrottle(const size_t& throttle_in_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.throttle = throttle_in_val;
}
void EmulatorData::SetGearSetValue(const size_t& gear_in_set_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.pindle_set_value = gear_in_set_val;
}
void EmulatorData::SetStartSetValue(const size_t& start_in_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.start_set_value = start_in_val;
}
void EmulatorData::SetGear(const size_t& gear_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.gear = gear_val;
}
void EmulatorData::SetRpm(const size_t& rpm_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.rpm = rpm_val;
}
void EmulatorData::SetSpeed(const size_t& speed_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.speed = speed_val;
}
void EmulatorData::SetForwardForce(const size_t& forward_force_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.forward_force = forward_force_val;
}
void EmulatorData::SetActivateEngine(const bool& activate_engine_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.activate_engine = activate_engine_val;
}
void EmulatorData::SetPindleNeutral(const bool& pindle_neutral_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.pindle_neutral = pindle_neutral_val;
}
void EmulatorData::SetPindleDrive(const bool& pindle_drive_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.pindle_drive = pindle_drive_val;
}
void EmulatorData::SetPindleReverse(const bool& pindle_reverse_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.pindle_reverse = pindle_reverse_val;
}
void EmulatorData::SetParkingFlag(const bool& parking_flag_val) {
  std::unique_lock lock_u(emulator_data_mutex_);
  values.parking_flag = parking_flag_val;
}

Values EmulatorData::GetAll() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values;
}

bool EmulatorData::SetAll(const Values_t &values) {
  std::unique_lock lock_u(emulator_data_mutex_);
  this->values = values;
  return false;
}

