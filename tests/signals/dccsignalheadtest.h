#ifndef DCCSIGNALHEADTEST_H
#define DCCSIGNALHEADTEST_H
#include "abstractsignalheadtestbase.h"
#include "exceptions.h"
#include "commandstation.h"

class DccSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 DccSignalHeadTest(QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() throw (Exception);
 Q_INVOKABLE /*public*/ void tearDown() throw (Exception);
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testCtor1();
 /*public*/ void testRedAppearance();
 /*public*/ void testDarkAppearance();
 /*public*/ void testLunarAppearance();
 /*public*/ void testYellowAppearance();
 /*public*/ void testGreenAppearance();
 /*public*/ void testFlashRedAppearance();
 /*public*/ void testFlashLunarAppearance();
 /*public*/ void testFlashYellowAppearance();
 /*public*/ void testFlashGreenAppearance();

private:
 QByteArray lastSentPacket;
 int sentPacketCount;
friend class CommandStationO1;
};

class CommandStationO1 : public CommandStation {
 Q_OBJECT
 DccSignalHeadTest* test;
 public:
 CommandStationO1(DccSignalHeadTest* test) {this->test = test;}
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

#endif // DCCSIGNALHEADTEST_H
