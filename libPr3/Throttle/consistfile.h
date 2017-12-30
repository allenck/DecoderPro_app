#ifndef CONSISTFILE_H
#define CONSISTFILE_H
#include "xmlfile.h"
#include "consist.h"

class DccLocoAddress;
class ConsistManager;
class ConsistFile : public XmlFile
{
public:
 ConsistFile();
 /*public*/ void readFile() throw (JDOMException, IOException);
 /*public*/ void readFile(QString fileName) throw (JDOMException, IOException);
 /*public*/ void writeFile(QList<DccLocoAddress*>* consistList) throw (IOException);
 /*public*/ void writeFile(QList<DccLocoAddress*>* consistList, QString fileName) throw (IOException);
 static /*public*/ QString getFileLocation();
 static /*public*/ void setFileLocation(QString loc);
 /*public*/ static QString defaultConsistFilename();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ConsistFile");
 static /*private*/ QString fileLocation;// = FileUtil::getUserFilesPath() + "roster" + File.separator + "consist";
 /*private*/ QDomElement consistToXml(Consist* consist);

protected:
 /*protected*/ ConsistManager* consistMan;// = null;

};

#endif // CONSISTFILE_H
