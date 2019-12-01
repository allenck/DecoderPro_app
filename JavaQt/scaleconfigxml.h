#ifndef SCALECONFIGXML_H
#define SCALECONFIGXML_H

#include <QObject>
#include "xmlfile.h"

class Logger;
class ScaleConfigXML : public QObject
{
 Q_OBJECT
public:
 explicit ScaleConfigXML(QObject *parent = nullptr);
 /*public*/ static bool doStore();
 /*public*/ static bool doLoad();

signals:

public slots:

private:
 static Logger* log;
 friend class ScaleXmlFile;
};

/*private*/ /*static*/ class ScaleXmlFile : public XmlFile {
 Q_OBJECT
    /*private*/ static QString prodPath;// = FileUtil.getProgramPath() + "resources/scales/";  // NOI18N
    /*private*/ static QString userPath;// = FileUtil.getUserFilesPath() + "resources/scales/";  // NOI18N
    /*private*/ static QString fileName;// = "ScaleData.xml";  // NOI18N
public:
    /*public*/ static QString getStoreFileName() ;
    /*public*/ File* getStoreFile();
    /*public*/ File* getLoadFile();
};
#endif // SCALECONFIGXML_H
