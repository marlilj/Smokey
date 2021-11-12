#include "../include/InterfaceToCANEncoder.hpp"

// #include <iostream>

int SignalNewValue::fetchNewThrottleValue() {
  bool signal_new_tvalue = false;
    // Fetch new throttle value from input handler.
  signal_new_tvalue = true;
}

int SignalNewValue::fetchNewGearValue() {
  bool signal_new_gvalue = false;
    // Fetch new gear value from input handler.
  signal_new_gvalue = true;
}

int SignalNewValue::fetchNewBrakeValue() {
  bool signal_new_bvalue = false;
    // Fetch new brake value from input handler.
  signal_new_bvalue = true;
}

int SignalNewValue::fetchNewFuelValue() {
  bool signal_new_fvalue = false;
    // Fetch new fuel value from input handler.
  signal_new_fvalue = true;
}

int SignalNewValue::signalNewValue(uint8_t signal_new_value) {
  bool signal_received = false;
  switch (signal_new_value) {
    case 01:
      SignalNewValue::fetchNewThrottleValue();
      signal_received = true;
      break;

    case 02:
      SignalNewValue::fetchNewGearValue();
      signal_received = true;
      break;
    case 03:
      signal_received = true;
      SignalNewValue::fetchNewBrakeValue();
      signal_received = true;
      break;
    case 04:
      signal_received = true;
      SignalNewValue::fetchNewFuelValue();
      signal_received = true;
      break;
    default: signal_received = false; break;
  }

  return signal_received;
}
