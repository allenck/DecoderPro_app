#ifndef ACCESSORYOPSMODEPROGRAMMERFACADETEST_H
#define ACCESSORYOPSMODEPROGRAMMERFACADETEST_H

#include <QObject>
#include "exceptions.h"
#include "proglistener.h"

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
 /*public*/ void testCvLimit() {
     ProgDebugger* dp = new ProgDebugger(true, 123);
     dp->setTestReadLimit(1024);
     dp->setTestWriteLimit(1024);

     Programmer* p = new AccessoryOpsModeProgrammerFacade(dp, "", 0, dp);

     Assert::assertTrue("CV limit read OK", p.getCanRead("1024"), __FILE__, __LINE__);
     Assert::assertTrue("CV limit write OK", p.getCanWrite("1024"), __FILE__, __LINE__);
     Assert::assertTrue("CV limit read fail", !p.getCanRead("1025"), __FILE__, __LINE__);
     Assert::assertTrue("CV limit write fail", !p.getCanWrite("1025"), __FILE__, __LINE__);
 }

 //@Test
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

};

class  ProgListenerO10 :  public  ProgListener
{
 Q_OBJECT
 AccessoryOpsModeProgrammerFacadeTest* test;
public:
 ProgListenerO10(AccessoryOpsModeProgrammerFacadeTest* test) {this->test = test;}
public slots:
 //@Override
 /*public*/ void programmingOpReply(int value, int status);
};

#endif // ACCESSORYOPSMODEPROGRAMMERFACADETEST_H
