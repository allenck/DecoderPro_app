#ifndef NMRACONSIST_H
#define NMRACONSIST_H
#include "dccconsist.h"
#include "logger.h"

class CommandStation;
class DccLocoAddress;
class NmraConsist : public DccConsist
{
    Q_OBJECT
public:
    //explicit NmraConsist(QObject *parent = 0);
    /*public*/ NmraConsist(int address, QObject *parent = 0);
    /*public*/ NmraConsist(DccLocoAddress* address, QObject *parent =0);
    /*public*/ NmraConsist(DccLocoAddress* address, CommandStation* commandStation, QObject *parent=0);
signals:

public slots:
private:
    Logger* log;
    CommandStation* commandStation = nullptr;
protected:
    /*protected*/ void addToAdvancedConsist(DccLocoAddress* locoAddress, bool directionNormal);
    /*protected*/ void removeFromAdvancedConsist(DccLocoAddress* locoAddress);
};

#endif // NMRACONSIST_H
