#ifndef METERFRAMETEST_H
#define METERFRAMETEST_H
#include "jmrijframetestbase.h"
#include "defaultmeter.h"
#include "meterupdatetask.h"


class MeterFrameTest : public JmriJFrameTestBase
{
 public:
  MeterFrameTest(QObject* parent);
  Q_INVOKABLE /*public*/ void setUp();
  Q_INVOKABLE     /*public*/ void tearDown();

 public slots:

 private:

};

class MFT_DefaultVoltageMeter : public DefaultVoltageMeter
{
  Q_OBJECT
  MeterFrameTest* test;
 public:
  /*public*/ MFT_DefaultVoltageMeter(/*@Nonnull*/ QString sys, Unit unit, double min, double max, double resolution, MeterUpdateTask* updateTask, MeterFrameTest* test)
   : DefaultVoltageMeter(sys, unit, min, max, resolution, updateTask)
  {
   this->test = test;
  }

  //@Override
  /*public*/ void requestUpdateFromLayout() override {
      // Do nothing
  }

};
class MFT_DefaultCurrentMeter : public DefaultCurrentMeter
{
  Q_OBJECT
  MeterFrameTest* test;
  /*public*/ MFT_DefaultCurrentMeter(/*@Nonnull*/ QString sys, Unit unit, double min, double max, double resolution, MeterUpdateTask* updateTask, MeterFrameTest* test)
   : DefaultCurrentMeter(sys, unit, min, max, resolution, updateTask)
  {
   this->test = test;
  }
  //@Override
  /*public*/ void requestUpdateFromLayout() {
      // Do nothing
  }

};

#endif // METERFRAMETEST_H
