#ifndef SLOTMANAGERTEST_H
#define SLOTMANAGERTEST_H

#include <QObject>
#include "slotmanager.h"
#include "proglistener.h"
#include "junitutil.h"

class LocoNetSlot;
class LocoNetInterfaceScaffold;
class SlotManagerO1;
class SlotManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit SlotManagerTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

public slots:
    /*public*/ void testGetDirectFunctionAddressOK();
    /*public*/ void testGetDirectDccPacketOK();
    /*public*/ void testGetSlotSend();
    /*public*/ void testGetSlotRcv();
    /*public*/ void testReadCVPaged() throw (ProgrammerException);
    /*public*/ void testReadCVRegister() throw (ProgrammerException);
    /*public*/ void testReadCVDirect() throw (ProgrammerException);
    /*public*/ void testReadCVOpsModeLong() throw (ProgrammerException);
    /*public*/ void testReadCVOpsModeShort() throw (ProgrammerException);
    /*public*/ void testWriteCVPaged() throw (ProgrammerException);
    /*public*/ void testWriteCVRegister() throw (ProgrammerException);
    /*public*/ void testWriteCVDirect() throw (ProgrammerException);
    /*public*/ void testWriteCVDirectStringDCS240() throw (ProgrammerException);
    /*public*/ void testLackLogic();
    /*public*/ void testWriteCVDirectStringDCS240Interrupted() throw (ProgrammerException);
    /*public*/ void testWriteCVOpsLongAddr() throw (ProgrammerException);
    /*public*/ void testWriteCVOpsShortAddr() throw (ProgrammerException);
    /*public*/ void testWriteThroughFacade() throw (ProgrammerException);
    /*public*/ void testReadThroughFacade() throw (ProgrammerException);
    /*public*/ void testReadThroughFacadeFail() throw (ProgrammerException);
    /*public*/ void testGetProgrammingModes();
    /*public*/ void testSendPacket();




signals:

public slots:
private:
    /**
     * Local member to recall when a SlotListener has been invoked.
     */
    /*private*/ LocoNetSlot* testSlot;
    // The minimal setup for log4J
    LocoNetInterfaceScaffold* lnis;
    SlotManager* slotmanager;
    int status;
    int value;
    bool startedShortTimer = false;
    bool startedLongTimer = false;
    bool stoppedTimer = false;

    ProgListener* lstn;
    int releaseTestDelay = 150; // probably needs to be at least 150, see SlotManager.postProgDelay
    static Logger* log;
    friend class SlotManagerO1;
    friend class ProgListenerO1;
    friend class SlotListenerO1;
    friend class ReleaseUntil01;
    friend class ReleaseUntil02;
    friend class ReleaseUntil03;
    friend class ReleaseUntil04;
};

class SlotManagerO1 : public SlotManager
{
    Q_OBJECT
    SlotManagerTest* smt;
public:
    SlotManagerO1(LocoNetInterfaceScaffold* lnis, SlotManagerTest* smt) : SlotManager((LnTrafficController*)lnis) {this->smt = smt;}
protected:
    //@Override
    /*protected*/ void startLongTimer();
    /*protected*/ void startShortTimer();
    /*protected*/ void stopTimer();
};

class ProgListenerO1 : public QObject, public ProgListener
{
    Q_OBJECT
  Q_INTERFACES(ProgListener)
    SlotManagerTest* smt;
public:
    ProgListenerO1(SlotManagerTest* smt) {this->smt = smt;}
    QObject* self() {return (QObject*)this;}
public slots:
    //@Override
    /*public*/ void programmingOpReply(int val, int stat);
};

class SlotListenerO1 : public QObject, public SlotListener
{
    Q_OBJECT
    Q_INTERFACES(SlotListener)
    SlotManagerTest* smt;
public:
    SlotListenerO1(SlotManagerTest* smt) {this->smt = smt;}
public:
    //@Override
    /*public*/ void notifyChangedSlot(LocoNetSlot* l);
};

class ReleaseUntil01 : public ReleaseUntil
{
    Q_OBJECT
    SlotManagerTest* smt;
public:
    ReleaseUntil01(SlotManagerTest* smt) {this->smt = smt;}
    bool ready() throw (Exception) {return smt->startedLongTimer;}
};

class ReleaseUntil02 : public ReleaseUntil
{
    Q_OBJECT
    SlotManagerTest* smt;
public:
    ReleaseUntil02(SlotManagerTest* smt) {this->smt = smt;}
    bool ready() throw (Exception)
    {
     return (smt->value == 35);
    }
};

class ReleaseUntil03 : public ReleaseUntil
{
    Q_OBJECT
    SlotManagerTest* smt;
public:
    ReleaseUntil03(SlotManagerTest* smt) {this->smt = smt;}
    bool ready() throw (Exception) {return smt->startedShortTimer;}
};

class ReleaseUntil04 : public ReleaseUntil
{
    Q_OBJECT
    SlotManagerTest* smt;
public:
    ReleaseUntil04(SlotManagerTest* smt) {this->smt = smt;}
    bool ready() throw (Exception) {return smt->value == -1;}
};

#endif // SLOTMANAGERTEST_H
