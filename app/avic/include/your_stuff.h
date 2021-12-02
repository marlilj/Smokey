#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H

#include "can_opener.h"  // NOLINT Due to we don't care!
#include "cluster_updater.h"
#include <string>  // NOLINT Due to we don't care!

struct EngineData {
    unsigned short rpm;  // NOLINT Due to we don't care!
    unsigned char speed;
};
class yourStuff : public QObject {
    Q_OBJECT
 public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);

 private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame * const _frame);
    void timerEvent(QTimerEvent*) override;
    size_t Counter = 0;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;

};

#endif // YOUR_STUFF_H  // NOLINT Due to we don't care!
