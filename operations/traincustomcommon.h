#ifndef TRAINCUSTOMCOMMON_H
#define TRAINCUSTOMCOMMON_H

#include <QObject>
#include <QtXml>

class File;
class Logger;
class Process;
namespace Operations {

class TrainCustomCommon : public QObject
{
 Q_OBJECT
public:
 explicit TrainCustomCommon(QObject *parent = nullptr);
 /*public*/ QString getFileName();
 /*public*/ void setFileName(QString name);
 /*public*/ QString getCommonFileName() ;
 /*public*/ void setCommonFileName(QString name);
 /*public*/ int getFileCount();
 /*abstract*/ virtual /*public*/ QString getDirectoryName();
 /*abstract*/ virtual /*public*/ void setDirectoryName(QString name);
 /*public*/ void load(QDomElement mc);
 /*public*/ void store(QDomElement mc);
 /*public*/ void addCVSFile(File* csvFile);
 /*public*/ bool excelFileExists();
 /*public*/ bool process();

signals:

public slots:

private:
 /*private*/ QString mcAppName;// = "MC4JMRI.xls"; // NOI18N
 /*private*/ /*final*/ QString mcAppArg;// = ""; // NOI18N
 /*private*/ QString csvNamesFileName;// = "CSVFilesFile.txt"; // NOI18N
 /*private*/ int fileCount;// = 0;
 /*private*/ int waitTimeSeconds;// = 0;
 /*private*/ Process* _process;
 /*private*/ bool alive;// = false;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("TrainCustomCommon");
 QDomDocument doc;

friend class Train;
friend class TrainCustomManifest;
};
}
#endif // TRAINCUSTOMCOMMON_H
