#ifndef DEFAULTCABSIGNALTEST_H
#define DEFAULTCABSIGNALTEST_H

#include <QObject>
#include "../positionables/editorframeoperator.h"
#include "signalmast.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "defaultcabsignal.h"

class Logger;
class DefaultCabSignalTest : public QObject
{
 Q_OBJECT
public:
 explicit DefaultCabSignalTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testSetBlock();
 /*public*/ void testSignalSequence() throw (JmriException);
// /*public*/ void DefaultCabSignalTest::testSignalSequenceIdTag() throw (JmriException);

private:
 static Logger* log;
 /*private*/ void moveBlock(QString startingBlock,QString endingBlock);

protected:
 DefaultCabSignal* cs = nullptr;
 /*protected*/ void runSequence(QVariant initialBlockContents) throw (JmriException);
 /*protected*/ void checkBlock(CabSignal* lcs,QString currentBlock,QString nextBlock,QString mastName);

};

class DefaultCabSignalO1 : public DefaultCabSignal
{
 Q_OBJECT
 DefaultCabSignalTest* test;
public:
 DefaultCabSignalO1(DccLocoAddress* addr, DefaultCabSignalTest* test) : DefaultCabSignal(addr) {this->test = test;}
 //@Override
 /*public*/ SignalMast* getNextMast() override {
    // don't check for signal masts, they aren't setup for this
    // test.
    return nullptr;
 }
};

class ReleaseUntil_dcst1 : public ReleaseUntil
{
 Q_OBJECT
 DefaultCabSignalTest* test;
public:
 ReleaseUntil_dcst1(DefaultCabSignalTest* test) {this->test = test;}
  bool ready() throw (Exception)
 {
  return InstanceManager::sensorManagerInstance()->provideSensor("IS_ROUTING_DONE")->getKnownState() == Sensor::ACTIVE;
 }
};
class ReleaseUntil_dcst2 : public ReleaseUntil
{
 Q_OBJECT
 DefaultCabSignalTest* test;
 DefaultCabSignal* lcs;
public:
 ReleaseUntil_dcst2(CabSignal* lcs, DefaultCabSignalTest* test) {this->test = test;}
  bool ready() throw (Exception)
 {
  return "Clear" == (lcs->getNextMast()->getAspect());
 }
};

#endif // DEFAULTCABSIGNALTEST_H
