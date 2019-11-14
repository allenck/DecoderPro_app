#ifndef SIGNALHEADSIGNALMASTADDPANETEST_H
#define SIGNALHEADSIGNALMASTADDPANETEST_H
#include "abstractsignalmastaddpanetestbase.h"
#include "defaultsignalhead.h"

class SignalHeadSignalMastAddPaneTest : public AbstractSignalMastAddPaneTestBase
{
 Q_OBJECT
public:
 SignalHeadSignalMastAddPaneTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testSetMast();

protected:
 /*protected*/ SignalMastAddPane* getOTT();


};
class DefaultSignalHead2 : public DefaultSignalHead
{
 Q_OBJECT
 SignalHeadSignalMastAddPaneTest* test;
public:
 DefaultSignalHead2(QString systemName, SignalHeadSignalMastAddPaneTest* test) : DefaultSignalHead(systemName){this->test = test;}
protected:
 //@Override
 /*protected*/ void updateOutput() {
 }
};

#endif // SIGNALHEADSIGNALMASTADDPANETEST_H
