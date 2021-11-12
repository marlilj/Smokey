#ifndef INTERFACETOCANENCODER_HPP
#define INTERFACETOCANENCODER_HPP

#include <ncurses.h>

#include <iostream>



class SignalNewValue {

private:
  int fetchNewThrottleValue();
  int fetchNewGearValue();
  int fetchNewBrakeValue();
  int fetchNewFuelValue();

public:
  int signalNewValue(int signal_new_value);
  // bool signalNewThrottleValue;
  // bool signalNewGearValue;
  // bool signalNewBrakeValue;
  // bool signalNewFuelValue;
};




#endif // INTERFACETOCANENCODER_HPP