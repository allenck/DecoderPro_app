#ifndef TRAINMANAGERXML_H
#define TRAINMANAGERXML_H
#include "operationsxml.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"


namespace Operations
{
 class APPSLIBSHARED_EXPORT TrainManagerXml : public OperationsXml, public InstanceManagerAutoDefault
 {
  Q_OBJECT
   Q_INTERFACES(InstanceManagerAutoDefault)
 public:
  Q_INVOKABLE explicit TrainManagerXml(QObject *parent = 0);
   ~TrainManagerXml() {}
   TrainManagerXml(const TrainManagerXml&) : OperationsXml() {}
  /*public*/ bool isTrainFileLoaded();
  /*public*/ void writeFile(QString name); //throw FileNotFoundException, IOException
  /*public*/ void readFile(QString name); //throw (JDOMException,IOException)
  /*public*/ File* createTrainManifestFile(QString name);
  /*public*/ File* getTrainManifestFile(QString name);
  /*public*/ File* createTrainBuildReportFile(QString name);
  /*public*/ File* getTrainBuildReportFile(QString name);
  /*public*/ QString defaultBuildReportFilename(QString name);
  /*public*/ void setBuildReportName(QString name);
  /*public*/ File* createSwitchListFile(QString name);
  /*public*/ File* getSwitchListFile(QString name);
  /*public*/ File* createCsvSwitchListFile(QString name);
  /*public*/ File* getCsvSwitchListFile(QString name);
  /*private*/ QString getDefaultCsvSwitchListName(QString name);
  /*public*/ void createDefaultCsvSwitchListDirectory();
  /*public*/ void setTrainSwitchListName(QString name);
  /*public*/ void setOperationsFileName(QString name) ;
  /*public*/ QString getOperationsFileName();
  /*public*/ void dispose();
  /*public*/ File* getTrainCsvManifestFile(QString name);
  /*public*/ File* createTrainCsvManifestFile(QString name);
  /*public*/ void createDefaultCsvManifestDirectory();
  /*public*/ File* getManifestFile(QString name, QString ext);
  /*public*/ File* createManifestFile(QString name, QString ext);
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:
 private:
  /*private*/ bool fileLoaded;// = false;

  /*private*/ QString operationsFileName;// = "OperationsTrainRoster.xml";// NOI18N
  /*private*/ QString buildReportFileName;// = Bundle.getMessage("train") + " (";
  /*private*/ QString manifestFileName;// = Bundle.getMessage("train") + " (";
  /*private*/ QString switchListFileName;// = Bundle.getMessage("location") + " (";
  /*private*/ QString fileType;// = ").txt"; // NOI18N
  /*private*/ QString fileTypeCsv;// = ").csv"; // NOI18N
//  /*private*/ static TrainManagerXml* _instance;// = null;
  Logger* log;
  // the directories under operations
  /*private*/ static /*final*/ QString BUILD_STATUS;// = "buildstatus"; // NOI18N
  /*private*/ static /*final*/ QString MANIFESTS;// = "manifests"; // NOI18N
  /*private*/ static /*final*/ QString SWITCH_LISTS;// = "switchLists"; // NOI18N
  /*private*/ static /*final*/ QString CSV_MANIFESTS;// = "csvManifests"; // NOI18N
  /*private*/ static /*final*/ QString CSV_SWITCH_LISTS;// = "csvSwitchLists"; // NOI18N
  /*private*/ QString getDefaultManifestFilename(QString name);
  /*private*/ QString getDefaultSwitchListName(QString name) ;
  /*private*/ QString defaultCsvSwitchListDirectory;// = OperationsXml.getFileLocation()
//          + OperationsXml.getOperationsDirectoryName() + File.separator + CSV_SWITCH_LISTS + File.separator;
  /*private*/ QString getDefaultCsvManifestFilename(QString name);
  /*private*/ QString defaultCsvManifestDirectory;// = OperationsXml.getFileLocation()
//          + OperationsXml::getOperationsDirectoryName() + File::separator + CSV_MANIFESTS + File.separator;
  /*private*/ QString getDefaultManifestFilename(QString name, QString ext);


 };
}
Q_DECLARE_METATYPE(Operations::TrainManagerXml)
#endif // TRAINMANAGERXML_H
