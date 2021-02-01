#ifndef LnDeferProgrammerTest_H
#define LnDeferProgrammerTest_H

#include <QObject>
#include "exceptions.h"
#include "slotmanager.h"
#include "proglistener.h"
#include "junitutil.h"

class Logger;
class LocoNetInterfaceScaffold;
class ProgListener;
class SlotManager;
class LnDeferProgrammerTest : public QObject
{
 Q_OBJECT
public:
 explicit LnDeferProgrammerTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testReadCVPaged() throw (ProgrammerException);
 /*public*/ void testReadCVRegister() throw (ProgrammerException);
 /*public*/ void testReadCVDirect() throw (ProgrammerException);
 /*public*/ void testReadCVOpsModeLong() throw (ProgrammerException);
 /*public*/ void testReadCVOpsModeShort() throw (ProgrammerException);
 /*public*/ void testWriteCVPaged() throw (ProgrammerException);
 /*public*/ void testWriteCVPagedString() throw (ProgrammerException);
 /*public*/ void testWriteCVRegister() throw (ProgrammerException);
 /*public*/ void testWriteCVDirect() throw (ProgrammerException);
 /*public*/ void testWriteCVDirectStringDCS240() throw (ProgrammerException);

private:
 LocoNetInterfaceScaffold* lnis;
 SlotManager* slotmanager;
 int status;
 int value;
 bool startedShortTimer = false;
 bool startedLongTimer = false;
 bool stoppedTimer = false;
 static Logger* log;
 ProgListener* lstn;
 int releaseTestDelay = 150; // probably needs to be at least 150, see SlotManager.postProgDelay

 friend class ProgListenerO4;
 friend class SlotManagerO3;
 friend class ReleaseUntilO10;
 friend class ReleaseUntilO11;
 friend class ReleaseUntilO12;
 friend class ReleaseUntilO13;

};

class SlotManagerO3 : public SlotManager {
 Q_OBJECT
 LnDeferProgrammerTest* test;
public:
 SlotManagerO3(LocoNetInterfaceScaffold* lnis, LnDeferProgrammerTest* test) : SlotManager((LnTrafficController*)lnis)
 {
  this->test = test;
 }
protected:
    //@Override
    /*protected*/ void startLongTimer() {
        SlotManager::startLongTimer();
        test->startedLongTimer = true;
    }
    //@Override
    /*protected*/ void startShortTimer() {
        SlotManager::startShortTimer();
        test->startedShortTimer = true;
    }
    //@Override
    /*protected*/ void stopTimer() {
        SlotManager::stopTimer();
        test->stoppedTimer = true;
    }
};

class ProgListenerO4 : public QObject, public ProgListener{
 Q_OBJECT
  Q_INTERFACES(ProgListener)
 LnDeferProgrammerTest* test;
public:
 ProgListenerO4(LnDeferProgrammerTest* test) { this->test = test;}
    //@Override
    /*public*/ void programmingOpReply(int val, int stat) {
        test->log->debug(tr("   reply val: %1 status: %2").arg(val).arg(stat));
        test->status = stat;
        test->value = val;
    }
 QObject* self() {return (QObject*)this;}
};

class ReleaseUntilO10 : public ReleaseUntil
{
    Q_OBJECT
    LnDeferProgrammerTest* lompt;
public:
    ReleaseUntilO10(LnDeferProgrammerTest* lompt) {this->lompt = lompt;}
    bool ready() throw (Exception) {return lompt->startedShortTimer;}
};

class ReleaseUntilO11 : public ReleaseUntil
{
    Q_OBJECT
    LnDeferProgrammerTest* lompt;
public:
    ReleaseUntilO11(LnDeferProgrammerTest* lompt) {this->lompt = lompt;}
    bool ready() throw (Exception) {return lompt->value == 35;}
};

class ReleaseUntilO12 : public ReleaseUntil
{
    Q_OBJECT
    LnDeferProgrammerTest* lompt;
public:
    ReleaseUntilO12(LnDeferProgrammerTest* lompt) {this->lompt = lompt;}
    bool ready() throw (Exception) {return lompt->startedLongTimer;}
};

class ReleaseUntilO13 : public ReleaseUntil
{
    Q_OBJECT
    LnDeferProgrammerTest* lompt;
public:
    ReleaseUntilO13(LnDeferProgrammerTest* lompt) {this->lompt = lompt;}
    bool ready() throw (Exception) {return (lompt->value == -1);}
};

#endif // LnDeferProgrammerTest_H
