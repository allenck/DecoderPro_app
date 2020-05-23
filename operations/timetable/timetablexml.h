#ifndef TIMETABLEXML_H
#define TIMETABLEXML_H

#include <QObject>
#include "xmlfile.h"

namespace TimeTable
{

class TimeTableXmlFile;
class TimeTableXml : public QObject
{
 Q_OBJECT
public:
 explicit TimeTableXml(QObject *parent = nullptr);
 /*public*/ static bool doStore();
 /*public*/ static bool doLoad();
 /*public*/ /*static*/ QString getDefaultFileName() ;
 /*public*/ File* getFile(bool store);
 /*public*/ static QString getFileName();
 /*public*/ static QString getFileLocation();

signals:

public slots:

private:
 static Logger* log;
 friend class TimeTableXmlFile;
};

/*public*/ /*static*/ class TimeTableXmlFile : public XmlFile {
 Q_OBJECT
    /*private*/ static QString fileLocation;// = FileUtil.getUserFilesPath() + "timetable/";  // NOI18N
    /*private*/ static QString demoLocation;// = FileUtil.getProgramPath() + "xml/demoTimetable/";  // NOI18N
    /*private*/ static QString baseFileName;// = "TimeTableData.xml";  // NOI18N
public:
    /*public*/ static QString getDefaultFileName();
    /*public*/ File* getFile(bool store);
    /*public*/ static QString getFileName() ;
    /*public*/ static QString getFileLocation();
private:
 static Logger* log;
};
}
#endif // TIMETABLEXML_H
