#ifndef LNPREDEFINEDMETERS_H
#define LNPREDEFINEDMETERS_H

#include <QObject>
#include "meterupdatetask.h"
#include "slotmanager.h"

class LocoNetMessage;
class SlotManager;
class LnTrafficController;
class LnMeterInitTask;
class LocoNetSystemConnectionMemo;
class LnPredefinedMeters : public QObject
{
  Q_OBJECT
 public:
  explicit LnPredefinedMeters(LocoNetSystemConnectionMemo* scm, QObject *parent = nullptr);
  /*public*/ void message(LocoNetMessage* msg);
  /*public*/ void dispose();
  /*public*/ void requestUpdateFromLayout();

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ SlotManager* sm = nullptr;
  /*private*/ LnTrafficController* tc = nullptr;
  /*private*/ /*final*/ MeterUpdateTask* updateTask;
  /*private*/ /*final*/ LnMeterInitTask* initializationTask;
  /*private*/ /*final*/ QString createSystemName(int device, int sn, QString typeString);
  /*private*/ void updateAddMeter(Meter* m, QString sysName, float value, bool typeVolt );

  friend class MeterUpdateTask01;
  friend class LnPredefinedMeters;
};

class MeterUpdateTask01 : public MeterUpdateTask
{
  Q_OBJECT
  LnPredefinedMeters* lnpm;
 public:
  MeterUpdateTask01(int interval, LnPredefinedMeters* lnpm) : MeterUpdateTask(interval) {this->lnpm = lnpm;}
  //@Override
  /*public*/ void requestUpdateFromLayout() {
      lnpm->sm->sendReadSlot(249);
  }
};
#endif // LNPREDEFINEDMETERS_H