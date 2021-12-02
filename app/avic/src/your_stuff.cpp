#include <thread>  // NOLINT Due to we don't care!
#include <iostream>  // NOLINT Due to we don't care!
#include "your_stuff.h"
#include "smokey_data.hpp"
uint8_t fuel = 0;
uint8_t temp = 0;
uint8_t oil = 0;
void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    /* const unsigned short *rpm = reinterpret_cast<const unsigned short*>(_frame->data);
    this->InstrumentCluster.setRPM(*rpm);
    std::cout << "Recieved frame with " << *rpm << std::endl; */

    if (_frame->can_id == k_FrameIdUserInput) {
       const Payload_t *ui = reinterpret_cast<const Payload_t*>(_frame->data);



    } else if (_frame->can_id == k_FrameIdEmulator) {
        const EmulatorOutput_t *em = reinterpret_cast<const EmulatorOutput_t*>(_frame->data);  // NOLINT Due to line break decreasing readability.
        this->InstrumentCluster.setRPM(em->rpm);
        this->InstrumentCluster.setSpeed(em->speed);
        this->InstrumentCluster.setGear(em->gear);
        this->InstrumentCluster.setGearPindle_int(em->pindle);
        this->InstrumentCluster.ignite(em->start);


        if (em->start) {
            fuel = (fuel >= 255 - 10) ? 255 : fuel += 10;
             temp = (temp >= 128 - 5) ? 128 : temp += 5;
            oil = (oil >= 128 - 5) ? 128 : oil += 5;


            this->InstrumentCluster.setTXT("SMOKEY");
            this->InstrumentCluster.setFuelGauges(fuel);
            this->InstrumentCluster.setTemperatureGauges(temp);
            this->InstrumentCluster.setOilTemperatureGauges(oil);
        } else {
            fuel = fuel <= 0 + 10 ? 0 : fuel -= 10;
            temp = temp <= 0 + 5 ? 0 : temp -= 5;
            oil = oil <= 0 + 5 ? 0 : oil -= 5;
            this->InstrumentCluster.setTXT("");
            this->InstrumentCluster.setFuelGauges(fuel);
            this->InstrumentCluster.setTemperatureGauges(temp);
            this->InstrumentCluster.setOilTemperatureGauges(oil);
        }
    }
}

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();  // NOLINT Due to we don't care!

    this->InstrumentCluster.init(_vs);

    this->startTimer(1);
}

bool yourStuff::run() {
    bool ret = true;
    CANOpener::ReadStatus status; /* = CANOpener::ReadStatus::OK; */
    canfd_frame frame;
    status = this->CANReader.read(&frame);
    /*while*/if (status == CANOpener::ReadStatus::OK) {
        this->YouHaveJustRecievedACANFrame(&frame);
    }
    if (status == CANOpener::ReadStatus::ERROR) { ret = false;
  } else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) {
               this->Counter++;
  }
    // else   this->Counter = 0;
    if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run()); { // NOLINT Due to we don't care!
    } else {
        exit(-1);
    }
}
