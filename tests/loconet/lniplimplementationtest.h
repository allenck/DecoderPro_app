#ifndef LNIPLIMPLEMENTATIONTEST_H
#define LNIPLIMPLEMENTATIONTEST_H

#include <QObject>
#include "propertychangelistener.h"
#include "junitutil.h"

class LocoNetMessage;
class LnIPLImplementation;
class LnTrafficController;
class LocoNetSystemConnectionMemo;
class LnIplImplementationTest : public QObject
{
  Q_OBJECT
 public:
  explicit LnIplImplementationTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE /*public*/ void tearDown();
 signals:

 public slots:
  /*public*/ void testCtor();
  /*public*/ void testCreateQueryAllIplDevices();
  /*public*/ void testCreateQueryHostDevices();
  /*public*/ void testCreateQuerySlaveDevices();
  /*public*/ void testCreateQueryHostSlaveDevices();
  /*public*/ void checkSpecificDeviceTypeQueryMessages();
  /*public*/ void checkIplIdentityReportMethods();
  /*public*/ void decodingTest();
  /*public*/ void checkInterpretHostManufacturerDevice();
  /*public*/ void checkInterpretSlaveManufacturerDevice();
  /*public*/ void testExtractIplReportInfo();
  /*public*/ void testConnectMethod();
  /*public*/ void checkDispose();

 private:
  LocoNetSystemConnectionMemo* memo;
  LnTrafficController* lnis;
  LnIPLImplementation* iplImplementation;
  LocoNetMessage* m;
  bool propChangeQueryFlag;
  bool propChangeReportFlag;
  bool propChangeFlag;

  friend class LNIPLI_PropertyChangeListener;
  friend class LNIPLI_ReleaseUntil;
};

class LNIPLI_PropertyChangeListener : public PropertyChangeListener
{
  Q_OBJECT
  LnIplImplementationTest* test;
 public:
  LNIPLI_PropertyChangeListener(LnIplImplementationTest* test) { this->test = test;}
 public slots:
  //@Override
  /*public*/ void propertyChange(PropertyChangeEvent* e) override {
      if ((e->getPropertyName() == ("IplDeviceTypeQuery"))) {
          test->propChangeQueryFlag = true;
      } else if (e->getPropertyName() == ("IplDeviceTypeReport")) {
          test->propChangeReportFlag = true;
      }
      test->propChangeFlag = true;
  }
};

class LNIPLI_ReleaseUntil : public ReleaseUntil
{
  Q_OBJECT
  LnIplImplementationTest* test;
 public:
  LNIPLI_ReleaseUntil(LnIplImplementationTest* test) {this->test = test;}
  bool ready() throw (Exception)
  {
   return test->propChangeFlag == true;
  }
};
#endif // LNIPLIMPLEMENTATIONTEST_H
