#ifndef CTCMANAGER_H
#define CTCMANAGER_H

#include <QObject>
#include "instancemanagerautodefault.h"
#include "vetoablechangelistener.h"
#include "nbhsensor.h"
#include "block.h"

class CTCSerialData;
class ProgramProperties;
class CtcManager : public QObject, public InstanceManagerAutoDefault/*, public VetoableChangeListener*/
{
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault /*VetoableChangeListener*/)
 public:
  explicit CtcManager(QObject *parent = nullptr);

  /*public*/ void putNBHSensor(QString name, NBHSensor* nbh);

  /*public*/ int getXMLOrder();

 signals:

 public slots:

 private:
  static Logger* log;
  ProgramProperties* programProperties = nullptr;
  CTCSerialData* ctcSerialData = nullptr;
  QMap<QString, NBHSensor*> nbhSensors = QMap<QString, NBHSensor*>();
#if 0
  HashMap<String, NBHSignal*> nbhSignals = new HashMap<>();
  HashMap<String, NBHTurnout*> nbhTurnouts = new HashMap<>();
#endif
  QMap<QString, NamedBeanHandle<Block*>*> blocks = QMap<QString, NamedBeanHandle<Block*>*>();

};

#endif // CTCMANAGER_H
