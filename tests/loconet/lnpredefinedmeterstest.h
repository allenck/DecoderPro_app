#ifndef LNPREDEFINEDMETERSTEST_H
#define LNPREDEFINEDMETERSTEST_H

#include <QObject>

class LnPredefinedMeters;
class LocoNetInterfaceScaffold;
class SlotManager;
class LocoNetSystemConnectionMemo;
class LnPredefinedMetersTest : public QObject
{
  Q_OBJECT
 public:
  explicit LnPredefinedMetersTest(QObject *parent = nullptr);
  Q_INVOKABLE void setUp();
  Q_INVOKABLE void tearDown();
  /*public*/ double getBeanValue(LnPredefinedMeters *lm, QString meterName);

 signals:

 public slots:
  /*public*/ void testLnMeter();
  /*public*/ void testSN();
  /*public*/ void testAmps();
  /*public*/ void testVolts();
  /*public*/ void testSlotNum();

 private:
  LocoNetInterfaceScaffold* lnis;
  SlotManager* slotmanager;
  LocoNetSystemConnectionMemo* memo;

};

#endif // LNPREDEFINEDMETERSTEST_H
