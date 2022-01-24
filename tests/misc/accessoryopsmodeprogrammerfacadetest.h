#ifndef ACCESSORYOPSMODEPROGRAMMERFACADETEST_H
#define ACCESSORYOPSMODEPROGRAMMERFACADETEST_H

#include <QObject>
#include "exceptions.h"
#include "proglistener.h"
#include "progdebugger.h"

class Logger;
class MockCommandStation;
class AccessoryOpsModeProgrammerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit AccessoryOpsModeProgrammerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() throw (Exception);
 Q_INVOKABLE /*public*/ void tearDown() throw (Exception);

signals:

public slots:
 /*public*/ void testCvLimit();
 /*public*/ void testWriteAddr123long1cv234val14delay200signal() throw (ProgrammerException, InterruptedException) ;
 /*public*/ void testWriteAddr3long0cv12val0delay500accessory() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteAddr511long1cv1024val255delay0decoder() throw (ProgrammerException, InterruptedException);

private:
 static Logger* log;
 MockCommandStation* mockCS;
 int readValue = -2;
 bool replied = false;
 /*synchronized*/ void testMethod() throw (ProgrammerException, InterruptedException);
 /*synchronized*/ QStringList itemsFromMethodName(int methodOffset, int groupReps);
 /*synchronized*/ void waitReply() throw (InterruptedException);

 friend class ProgListenerO10;
};

class  ProgListenerO10 :  public QObject, public  ProgListener
{
 Q_OBJECT
 Q_INTERFACES(ProgListener)
 AccessoryOpsModeProgrammerFacadeTest* test;
public:
 ProgListenerO10(AccessoryOpsModeProgrammerFacadeTest* test) {this->test = test;}
 QObject* self() {return (QObject*)this;}
public slots:
 //@Override
 /*public*/ void programmingOpReply(int value, int status);
};

#endif // ACCESSORYOPSMODEPROGRAMMERFACADETEST_H
