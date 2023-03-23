#ifndef CTCMANAGER_H
#define CTCMANAGER_H

#include <QObject>
#include "instancemanagerautodefault.h"
#include "vetoablechangelistener.h"
#include "nbhsensor.h"
#include "block.h"
#include "nbhsignal.h"
#include "nbhturnout.h"

class TrafficLockingData;
class CodeButtonHandlerData;
class OtherData;
class CTCSerialData;
class ProgramProperties;
class CtcManager : public QObject, public InstanceManagerAutoDefault, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault VetoableChangeListener)
 public:
  Q_INVOKABLE explicit CtcManager(QObject *parent = nullptr);
  ~CtcManager() {}
  CtcManager(const CtcManager&): QObject(){}
  /*public*/ ProgramProperties* getProgramProperties();
  /*public*/ ProgramProperties* newProgramProperties();
  /*public*/ CTCSerialData* getCTCSerialData();
  /*public*/ CTCSerialData* newCTCSerialData();
  /*public*/ OtherData* getOtherData();
  /*public*/ NBHSensor* getNBHSensor(QString name);
  /*public*/ void putNBHSensor(QString name, NBHSensor* nbh);
  /*public*/ NBHSignal* getNBHSignal(QString name);
  /*public*/ void putNBHSignal(QString name, NBHSignal* nbh);
  /*public*/ NBHTurnout* getNBHTurnout(QString name);
  /*public*/ void putNBHTurnout(QString name, NBHTurnout* nbh);
  /*public*/ NamedBeanHandle<Block*>* getBlock(QString name);
  /*public*/ void putBlock(QString name, NamedBeanHandle<Block*>* block);
  /*public*/ int getXMLOrder();
  /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean *bean);

  QObject* self() override {return this;}

 signals:

 public slots:
  /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/;

 private:
  static Logger* log;
  ProgramProperties* programProperties = nullptr;
  CTCSerialData* ctcSerialData = nullptr;
  QMap<QString, NBHSensor*> nbhSensors = QMap<QString, NBHSensor*>();
  QMap<QString, NBHSignal*> nbhSignals = QMap<QString, NBHSignal*>();
  QMap<QString, NBHTurnout*> nbhTurnouts = QMap<QString, NBHTurnout*>();

  QMap<QString, NamedBeanHandle<Block*>*> blocks = QMap<QString, NamedBeanHandle<Block*>*>();
  QString getVetoDetails(NamedBean* nb);
  bool findNBHforBean(NamedBean* nb);
  // Search results
  NBHSensor*  foundSensor;
  NBHSignal*  foundSignal;
  NBHTurnout* foundTurnout;
  Block*      foundBlock;

  QList<NamedBeanUsageReport*> usageReport;

  void getCodeButtonHandleDataUsage(CodeButtonHandlerData* cbhd);
  void callOnDataUsage(CodeButtonHandlerData* cbhd, QString osName);
  void traffficLockingDataUsage(CodeButtonHandlerData* cbhd, QString osName);
  void traffficLockingRuleDataUsage(TrafficLockingData* rule, QString osName);

};
Q_DECLARE_METATYPE(CtcManager)
#endif // CTCMANAGER_H
