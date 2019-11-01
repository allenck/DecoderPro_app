#ifndef TRAININFOFILE_H
#define TRAININFOFILE_H
#include "xmlfile.h"

class TrainInfo;
class TrainInfoFile : public XmlFile
{
public:
 TrainInfoFile();
 /*public*/ void setFileLocation(QString testLocation);
 /*public*/ QStringList getTrainInfoFileNames();
 /*public*/ void deleteTrainInfoFile(QString name);
 /*public*/ TrainInfo* readTrainInfo(QString name); //throws org.jdom2.JDOMException, java.io.IOException {
 /*public*/ void writeTrainInfo(TrainInfo* tf, QString name); //throws java.io.IOException

private:
 Logger* log;
 // operational variables
 /*private*/ QString fileLocation;// = FileUtil.getUserFilesPath()
//         + "dispatcher" + File.separator + "traininfo" + File.separator;

 /*private*/ QDomDocument doc;// = null;
 /*private*/ QDomElement root;// = null;


};

#endif // TRAININFOFILE_H
