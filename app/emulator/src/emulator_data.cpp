#include "emulator.hpp"


Values EmulatorData::GetAll() {
  std::shared_lock lock_s(emulator_data_mutex_);
  return values;
}

bool EmulatorData::SetAll(const Values_t &values) {
  int error_code = kFailure;
  std::unique_lock lock_u(emulator_data_mutex_);
  this->values = values;
  error_code = kSuccess;
  return error_code;
}

