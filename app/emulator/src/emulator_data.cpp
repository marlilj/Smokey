#include "emulator.hpp"

size_t EmulatorData::GetThrottleSetValue() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return throttle_set_value;
}
size_t EmulatorData::GetThrottle() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return throttle;
}
size_t EmulatorData::GetGearSetValue() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return gear_set_value;
}
size_t EmulatorData::GetStartSetValue() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return start_set_value;
}
size_t EmulatorData::GetGear() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return gear;
}
size_t EmulatorData::GetRpm() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return rpm;
}
size_t EmulatorData::GetSpeed() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return speed;
}
size_t EmulatorData::GetForwardForce() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return forward_force;
}
bool EmulatorData::GetActivateEngine() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return activate_engine;
}
bool EmulatorData::GetPindleNeutral() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return pindle_neutral;
}
bool EmulatorData::GetPindleDrive() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return pindle_drive;
}
bool EmulatorData::GetPindleReverse() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return pindle_reverse;
}
bool EmulatorData::GetParkingFlag() {
  std::lock_guard<std::recursive_mutex> guard(emulator_data_mutex_);
  return parking_flag;
}
