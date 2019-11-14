#ifndef SIGNALHEADSIGNALMASTTEST_H
#define SIGNALHEADSIGNALMASTTEST_H

#include <QObject>
#include "defaultsignalhead.h"

class SignalHeadSignalMastTest : public QObject
{
 Q_OBJECT
public:
 explicit SignalHeadSignalMastTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testSetup();
 /*public*/ void testTwoNameOneHeadCtorOK();
 /*public*/ void testHeld();
 /*public*/ void testLit();
 /*public*/ void testTwoNameSe8cHeadCtorOK();
 /*public*/ void testOneNameOneHeadCtorOK();
 /*public*/ void testOldTwoNameCtorOK();
 /*public*/ void testOldOneNameCtorOK();
 /*public*/ void testOldOneNameCtorFailNoSystem();
 /*public*/ void testAspects();
 /*public*/ void testAspectAttributes();
 /*public*/ void testAspectNotSet();
 /*public*/ void testAspectFail();
 /*public*/ void testConfigureOneSearchLight();
 /*public*/ void testConfigureTwoSearchLight();
 /*public*/ void testOneSearchLightViaManager();
 /*public*/ void testSignalSystemLink();
};

class DefaultSignalHead1 : public DefaultSignalHead
{
 Q_OBJECT
 SignalHeadSignalMastTest* test;
public:
 DefaultSignalHead1(QString systemName, SignalHeadSignalMastTest* test) : DefaultSignalHead(systemName){this->test = test;}
protected:
 //@Override
 /*protected*/ void updateOutput() {
 }
};
#endif // SIGNALHEADSIGNALMASTTEST_H
