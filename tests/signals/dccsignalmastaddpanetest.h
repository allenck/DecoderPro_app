#ifndef DCCSIGNALMASTADDPANETEST_H
#define DCCSIGNALMASTADDPANETEST_H
#include "abstractsignalmastaddpanetestbase.h"
#include "commandstation.h"

class SignalHead;
class DccSignalMastAddPaneTest : public AbstractSignalMastAddPaneTestBase
{
 Q_OBJECT
public:
 DccSignalMastAddPaneTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testSetMast();
private:
 QByteArray lastSentPacket;
 int sentPacketCount;


protected:
 //@Override
 /*protected*/ SignalMastAddPane* getOTT();

 friend class CommandStationO2;
};
class CommandStationO2 : public CommandStation {
 Q_OBJECT
 DccSignalMastAddPaneTest* test;
 public:
 CommandStationO2(DccSignalMastAddPaneTest* test) {this->test = test;}
    //@Override
    /*public*/ bool sendPacket(QByteArray packet, int repeats) {
        test->lastSentPacket = packet;
        test->sentPacketCount++;
        return true;
    }

    //@Override
    /*public*/ QString getUserName() {
        return "";
    }

    //@Override
    /*public*/ QString getSystemPrefix() {
        return "I";
    }
};

#endif // DCCSIGNALMASTADDPANETEST_H
