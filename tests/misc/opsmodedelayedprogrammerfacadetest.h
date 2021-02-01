#ifndef OPSMODEDELAYEDPROGRAMMERFACADETEST_H
#define OPSMODEDELAYEDPROGRAMMERFACADETEST_H

#include <QObject>
#include "exceptions.h"
#include "proglistener.h"

class Logger;
class OpsModeDelayedProgrammerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit OpsModeDelayedProgrammerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() throw (Exception);
 Q_INVOKABLE /*public*/ void tearDown() throw (Exception);

signals:

public slots:
 /*public*/ void testWrite4Val12Delay0() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWrite37Val102Delay1000() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWrite1024Val255Delay2000() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWrite0Val23Delay100() throw (ProgrammerException, InterruptedException);
 /*public*/ void testCvLimit();


private:
 static Logger* log;
 int facProgRetValue = -2;
 int facProgRetStatus = -2;
 int facProgRetDelay = 0;
 /*transient*/ /*volatile*/ bool facProgReplied = false;
 /*synchronized*/ void testMethod(int addr, bool addrType) throw (ProgrammerException, InterruptedException);
 /*synchronized*/ void facProgWaitReply() throw (InterruptedException);
 /*synchronized*/ QList<QString> itemsFromMethodName(int methodOffset, int groupReps);

  friend class ProgListenerO7;
};

class ProgListenerO7 : public OpsModeDelayedProgrammerFacadeTest, public ProgListener {
 Q_OBJECT
 Q_INTERFACES(ProgListener)
  OpsModeDelayedProgrammerFacadeTest* test;
public:
 ProgListenerO7(OpsModeDelayedProgrammerFacadeTest* test) : OpsModeDelayedProgrammerFacadeTest() { this->test = test;}
    //@Override
    /*public*/ void programmingOpReply(int value, int status);
 QObject* self() {return (QObject*)this;}
};


#endif // OPSMODEDELAYEDPROGRAMMERFACADETEST_H
