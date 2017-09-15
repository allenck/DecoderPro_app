#ifndef TRAININFOFILE_H
#define TRAININFOFILE_H
#include "xmlfile.h"

class TrainInfoFile : public XmlFile
{
public:
 TrainInfoFile();
 /*public*/ void setFileLocation(QString testLocation);

private:
 // operational variables
 /*private*/ QString fileLocation;// = FileUtil.getUserFilesPath()
//         + "dispatcher" + File.separator + "traininfo" + File.separator;

 //private Document doc = null;
 //private Element root = null;


};

#endif // TRAININFOFILE_H
