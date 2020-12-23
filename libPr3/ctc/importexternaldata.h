#ifndef IMPORTEXTERNALDATA_H
#define IMPORTEXTERNALDATA_H

#include <QObject>
#include "importotherdata.h"
#include "importcodebuttonhandlerdata.h"
#include "trafficlockingdata.h"
#include "namedbeanhandle.h"
#include "callonentry.h"
#include "xmlfile.h"

class TrafficLockingEntry;
class CallOnData;
class Block;
class NBHTurnout;
class NBHSignal;
class NBHSensor;
class Logger;
class CtcManager;
class ImportExternalData : public XmlFile
{
  Q_OBJECT
 public:
  explicit ImportExternalData(QObject *parent = nullptr) : XmlFile(parent){}
  /*public*/ static void loadExternalData();
  /*public*/ static bool loadCTCSystemContent();


 signals:

 public slots:

 private:
  static /*final*/ CtcManager* cm;// = (CtcManager*)InstanceManager::getDefault("CtcManager");
  static ImportOtherData* _mImportOtherData;
  static QList<ImportCodeButtonHandlerData*> _mImportCodeButtonHandlerDataArrayList;// = QList<ImportCodeButtonHandlerData>();

  /*private*/ static /*final*/ QString CTC_FILE_NAME;// = "CTCSystem.xml";        // NOI18N
  /*private*/ static /*final*/ QString PROG_PROPS;// = "ProgramProperties.xml";   // NOI18N
  /*private*/ static /*final*/ QString TEMPORARY_EXTENSION;// = ".xmlTMP";        // NOI18N
  /*private*/ static /*final*/ QString SAVED_PREFIX;// = "V1_Save_";              // NOI18N
  static Logger* log;
  static /*private*/ void convertClassNameReferences(QString fileName) throw (Exception);
  static /*private*/ void writeLine(QTextStream* bufferedWriter, QString aLine) throw (IOException);
  static void doDataLoading();
  static void loadCodeButtonHandlerData(ImportCodeButtonHandlerData* oldCBHD);
  static void loadOtherData();
  static int loadInt(QString value);
  static NBHSensor* loadSensor(QString value, bool isInternal);
  static NBHSignal* loadSignal(QString signalName);
  static NBHTurnout* loadTurnout(QString value, bool feedback);
  static NamedBeanHandle<Block*>* loadBlock(QString value);
  static QList<NBHSignal *>* getSignalList(QString value);
  static QList<CallOnData*>* getCallOnList(QString value);
  static QList<QString> getCallOnSensorNames(CallOnEntry* entry);
  static void convertCallOnSensorNamesToNBHSensors();
  static QList<TrafficLockingData*>* getTrafficLocking(QString value);
  static QList<TrafficLockingData::TRLSwitch *>* getTRLSwitchList(TrafficLockingEntry* entry);
  static TrafficLockingData::TRLSwitch* createTRLSwitch(QString text, QString alignment, QString id);
  static QList<NBHSensor*>* getTRLSensorList(TrafficLockingEntry* entry, bool occupancy);

  /*private*/ static QList<ImportCodeButtonHandlerData*> readFile(QString fileName);
};

#endif // IMPORTEXTERNALDATA_H
