#ifndef LOCOFILE_H
#define LOCOFILE_H
#include <QtXml>
#include "xmlfile.h"
#include "Roster/cvtablemodel.h"
#include "Roster/indexedcvtablemodel.h"
#include "rosterentry.h"
#include "Roster/variabletablemodel.h"

class RosterEntry;
class LIBPR3SHARED_EXPORT LocoFile : public XmlFile
{
    Q_OBJECT
public:
    explicit LocoFile(QObject *parent = 0);
    /*public*/ QString titleString();
    /*public*/ static void loadCvModel(QDomElement loco, CvTableModel* cvModel, IndexedCvTableModel* iCvModel);
 /*public*/ void writeFile(File* pFile, QDomElement pRootElement, RosterEntry* pEntry);
    /*public*/ void writeFile(QFile* file, CvTableModel* cvModel, IndexedCvTableModel* iCvModel, VariableTableModel* variableModel, RosterEntry* r);
    /*public*/ void writeFile(QFile* pFile, QDomElement pRootElement, RosterEntry* pEntry);
    /*public*/ void writeFile(QFile* pFile, QDomElement existingElement, QDomElement newLocomotive);
    static /*public*/ void setFileLocation(QString loc);
    static /*public*/ QString getFileLocation();

signals:

public slots:
private:
 static /*private*/ QString fileLocation;// = FileUtil::getUserFilesPath()+"roster"+File.separator;
 Logger* log;
};

#endif // LOCOFILE_H
