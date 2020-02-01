#ifndef CONSISTFILE_H
#define CONSISTFILE_H
#include "xmlfile.h"
#include "dccconsist.h"

class AbstractConsistManager;
class PropertyChangeEvent;
class DccLocoAddress;
class ConsistManager;
class ConsistFile : public XmlFile
{
 Q_OBJECT
public:
 ConsistFile();
 /*public*/ void readFile() throw (JDOMException, IOException);
 /*public*/ void readFile(QString fileName) throw (JDOMException, IOException);
 /*public*/ void writeFile(QList<DccLocoAddress*>* consistList) throw (IOException);
 /*public*/ void writeFile(QList<DccLocoAddress *> *consistList, QString fileName) throw (IOException);
 static /*public*/ QString getFileLocation();
 static /*public*/ void setFileLocation(QString loc);
 /*public*/ static QString defaultConsistFilename();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConsistFile");
 static /*private*/ QString fileLocation;// = FileUtil::getUserFilesPath() + "roster" + File.separator + "consist";
 /*private*/ QDomElement consistToXml(DccConsist *consistIn);

protected:
 /*protected*/ AbstractConsistManager* consistMan;// = null;

};

#endif // CONSISTFILE_H
