//#include <chrono>
#include <thread>
#include <iostream>
#include "your_stuff.h"
#include "smokey_data.hpp"
//#include "canio/can_common.h"

void yourStuff::YouHaveJustRecievedACANFrame(const canfd_frame * const _frame) {
    /* const unsigned short *rpm = reinterpret_cast<const unsigned short*>(_frame->data);
    this->InstrumentCluster.setRPM(*rpm);
    std::cout << "Recieved frame with " << *rpm << std::endl; */

    if (_frame->can_id == k_FrameIdUserInput) {
       const Payload_t *ui = reinterpret_cast<const Payload_t*>(_frame->data);
       this->InstrumentCluster.ignite(ui->start);
       this->InstrumentCluster.setGearPindle_int(ui->gear);
        
    } else if (_frame->can_id == k_FrameIdEmulator) { 
        const EmulatorOutput_t *em = reinterpret_cast<const EmulatorOutput_t*>(_frame->data);
        this->InstrumentCluster.setRPM(em->rpm);
        this->InstrumentCluster.setSpeed(em->speed);
        this->InstrumentCluster.setGear(em->gear);
    }

    /* const unsigned short rpm = _frame->data[0] * 100;
    const unsigned short spd = _frame->data[0];
    this->InstrumentCluster.setRPM(rpm);
    this->InstrumentCluster.setSpeed(spd);
    if (_frame->data[0] != 0) {
        this->InstrumentCluster.ignite(true);
    } else {
        this->InstrumentCluster.ignite(false);
    }
    const unsigned char gear = _frame->data[0]/10;
    this->InstrumentCluster.setGear(gear);
    this->InstrumentCluster.setOilTemperatureGauges(128);
    this->InstrumentCluster.setTemperatureGauges(128);
    this->InstrumentCluster.setFuelGauges(200); */



    /* const struct EngineData *eng = reinterpret_cast<const struct EngineData*>(_frame->data);
    this->InstrumentCluster.setRPM(eng->rpm);
    this->InstrumentCluster.setSpeed(eng->speed); */


   /*  switch (_frame->can_id) {
    case CAN::MSG::GAUGES_ID: {
        const struct CAN::MSG::Gauges_t::_inner* s =
                reinterpret_cast<const struct CAN::MSG::Gauges_t::_inner* >((_frame->data));
        this->InstrumentCluster.setFuelGauges(s->G_FUEL);
        this->InstrumentCluster.setTemperatureGauges(s->G_TEMP);
        this->InstrumentCluster.setOilTemperatureGauges(s->G_OILT);
        break;
    }
    case CAN::MSG::ICONSS_ID:
        struct _icons  p;// = reinterpret_cast<struct _icons * >((_frame->data));
        static bool once = false;

        if (!once) {
            p.hazard = 1;
            once = true;
        } else
            p.hazard = 0;
        this->InstrumentCluster.setIcon(&p);
        break;
//    case CAN::MSG::USERIN_ID: {
//       // const struct CAN::MSG::_userin *d = reinterpret_cast<const struct CAN::MSG::_userin * >((_frame->data));
//       // this->InstrumentCluster.ignite(d->IGNT);
//    }
//        break;

    case CAN::MSG::GEARBX_ID: {
        const struct CAN::MSG::Gearbx_t::_bits *d = reinterpret_cast<const struct CAN::MSG::Gearbx_t::_bits * >((_frame->data));
        this->InstrumentCluster.setGearPindle_int(d->GEAR_P);
        this->InstrumentCluster.setGear(d->GEAR_N);
    }
        break;
    case CAN::MSG::ENGINE_ID: {
        const struct CAN::MSG::_engine *d = reinterpret_cast<const struct CAN::MSG::_engine * >((_frame->data));
        this->InstrumentCluster.ignite(d->RUN);
        this->InstrumentCluster.setRPM(d->RPM);
        this->InstrumentCluster.setSpeed(d->SPD);

    }
        break;
    default:
        break;
    }
 */
}

/******************************* ANYTHING BELOW THIS LINE IS JUST BORING STUFF *******************************/

yourStuff::yourStuff(const std::string &_ifName, QObject *_vs) {
    if(!(this->CANReader.open(_ifName))) exit(-1);//emit die();

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
    if (status == CANOpener::ReadStatus::ERROR) ret = false;
    else if (status == CANOpener::ReadStatus::NAVAL ||
             status == CANOpener::ReadStatus::ENDOF) this->Counter++;
    else   this->Counter = 0;
    //if (this->Counter > 200) ret = false;
    return ret;
}

void yourStuff::timerEvent(QTimerEvent*) {
    if(this->run());
    else {
//    emit this->die();
        exit(-1);
    }

}

