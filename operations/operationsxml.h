#ifndef OPERATIONSXML_H
#define OPERATIONSXML_H
#include "xmlfile.h"
#include "logger.h"
#include "operations_global.h"

class OPERATIONSSHARED_EXPORT OperationsXml : public XmlFile
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit OperationsXml(QObject *parent = 0);
  ~OperationsXml() {}
  OperationsXml(const OperationsXml&) : XmlFile() {}
 /*public*/ void writeOperationsFile();
 /*abstract*/ /*public*/ virtual void readFile(QString filename);// throw (JDOMException, IOException);
 /*public*/ void setDirty(bool b);
 /*public*/ bool isDirty();
 /*public*/ void writeFileIfDirty();
 /*public*/ QString getDefaultOperationsFilename() ;
 /*public*/ static void setOperationsDirectoryName(QString name);
 /*public*/ static QString getOperationsDirectoryName() ;
 /*public*/ virtual void setOperationsFileName(QString name);
 /*public*/ virtual QString getOperationsFileName();
 /*public*/ static QString getFileLocation();
 /*public*/ static void setFileLocation(QString location);
 /*public*/ Q_DECL_DEPRECATED static QString convertToXmlComment(QString comment);
 /*public*/ Q_DECL_DEPRECATED static QString convertFromXmlComment(QString comment);
 /*public*/ static void save();
 /*public*/ static bool areFilesDirty();
 /*public*/ static bool checkFileName(QString name);

signals:

public slots:
private:
 /*private*/ bool dirty = false;
 /*private*/ static QString operationsDirectoryName;// = "operations"; // NOI18N
 /*private*/ QString operationsFileName = "DefaultOperations.xml"; // NOI18N should be overridden

 /*private*/ static QString fileLocation;// = FileUtil.getUserFilesPath();
 Logger* log;
protected:
 /*protected*/ void load() /*throw (Exception)*/;
 /*protected*/ File* createFile(QString fullPathName, bool backupFile);
 /*protected*/ virtual void writeFile(QString filename);// throw (FileNotFoundException, IOException);
 friend class CarManagerXml;
};
Q_DECLARE_METATYPE(OperationsXml)
#endif // OPERATIONSXML_H
