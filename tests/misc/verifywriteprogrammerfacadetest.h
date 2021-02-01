#ifndef VERIFYWRITEPROGRAMMERFACADETEST_H
#define VERIFYWRITEPROGRAMMERFACADETEST_H

#include <QObject>
#include "exceptions.h"
#include "progdebugger.h"
#include "proglistener.h"

class Logger;
class VerifyWriteProgrammerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit VerifyWriteProgrammerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testWriteReadDirect() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadVerify() throw (ProgrammerException, InterruptedException);
 /*public*/ void testCvLimit();

private:
 static Logger* log;
 int readValue = -2;
 int readCount = 0;
 bool replied = false;
 /*synchronized*/ void waitReply() throw (InterruptedException);


 friend class ProgDebuggerO1;
 friend class ProgListenerO8;
};

class ProgDebuggerO1 : public ProgDebugger {
 Q_OBJECT
 VerifyWriteProgrammerFacadeTest* test;
public:
 ProgDebuggerO1(VerifyWriteProgrammerFacadeTest* test) {this->test = test;}
    //@Override
    /*public*/ bool getCanRead(QString cv) { return false; }
    //@Override
    /*public*/ bool getCanRead() { return false; }
    //@Override
    /*public*/ void readCV(QString cv, ProgListener* p) throw (ProgrammerException) { test->readCount++; ProgDebugger::readCV(cv, p); }
};

class ProgListenerO8 : public QObject, public ProgListener {
 Q_OBJECT
 Q_INTERFACES(ProgListener)
 VerifyWriteProgrammerFacadeTest* test;
public:
ProgListenerO8(VerifyWriteProgrammerFacadeTest* test) {this->test = test;}
QObject* self() {return (QObject*)this;}
public slots:
    //@Override
    /*public*/ void programmingOpReply(int value, int status);
};

#endif // VERIFYWRITEPROGRAMMERFACADETEST_H
