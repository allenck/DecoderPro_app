#ifndef CTCMANAGERXML_H
#define CTCMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "ctcmanager.h"
#include "instancemanager.h"
#include "trafficlockingdata.h"

class CodeButtonHandlerData;
class CallOnData;
class TrafficLockingData;
class Logger;
class CtcManagerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE CtcManagerXml(QObject* parent = nullptr);
  ~CtcManagerXml() {}
  CtcManagerXml(const CtcManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
 private:
  static Logger* log;
  CtcManager* cm = (CtcManager*)InstanceManager::getDefault("CtcManager");
  /*public*/ QDomElement store(QObject o);
  /*public*/ void load( QDomElement element, QObject* o) throw (JmriConfigureXmlException);
  /*public*/ bool load( QDomElement sharedCtcData,  QDomElement perNodeCtcData);
  /*public*/ void setStoreElementClass( QDomElement ctcdata);
  /*public*/ int loadOrder();

 private:
  void loadProperties(CtcManager* cm, QDomElement el);
  QDomElement storeProperties(CtcManager* cm);
  QDomElement storeOtherData(CtcManager* cm);
  QDomElement storeString(QString elementName, QString elementValue);
  QDomElement storeInt(QString elementName, int elementValue);
  QDomElement storeBoolean(QString elementName, bool elementValue);
  QDomElement storeSensor(QString elementName, NBHSensor* sensor);
  QDomElement storeSignal(QString elementName, NBHSignal* signal);
  QDomElement storeTurnout(QString elementName, NBHTurnout* turnout);
  QDomElement storeBlock(QString elementName, NamedBeanHandle<Block*>* block);
  QDomElement storeSensorList(QString elementName, QList<NBHSensor*>* sensors);
  QDomElement storeSignalList(QString elementName, QList<NBHSignal*>* _signals);
  QDomElement storeCallOnList(QString elementName, QList<CallOnData *> *callOnList);
  QDomElement storeTRLRules(QString elementName, QList<TrafficLockingData*>* trlList);
  QDomElement storeTRLSwitches(QString elementName, QList<TrafficLockingData::TRLSwitch*>* trlSwitches);
  QDomElement storeTULAdditionalTurnouts(QString elementName, CodeButtonHandlerData* cbhd);
  QDomElement createAdditionalTurnoutEntry(NBHTurnout* turnout, bool turnoutFeedback);
  void loadOtherData(CtcManager* cm,  QDomElement el);
  QString loadString( QDomElement element);
  int loadInt( QDomElement element);
  bool loadBoolean( QDomElement element);
  NBHSensor* loadSensor( QDomElement element, bool isInternal);
  NBHSignal* loadSignal( QDomElement element);
  NBHTurnout* loadTurnout( QDomElement element,  QDomElement feedback);
  NamedBeanHandle<Block*>* loadBlock( QDomElement element);
  QList<NBHSensor*>* getSensorList( QDomElement element);
  QList<NBHSignal *>* getSignalList( QDomElement element);
  QList<CallOnData*>* getCallOnList( QDomElement element);
  QList<QString> getCallOnSensorNames( QDomElement element);
  void convertCallOnSensorNamesToNBHSensors(CtcManager* cm);
  QList<TrafficLockingData*>* getTrafficLocking( QDomElement element);
  QList<TrafficLockingData::TRLSwitch*>* getTRLSwitchList( QDomElement element);
  void loadAdditionalTurnouts( QDomElement element, CodeButtonHandlerData* cbhd);      // TUL_AdditionalExternalTurnouts

};
Q_DECLARE_METATYPE(CtcManagerXml)
#endif // CTCMANAGERXML_H
