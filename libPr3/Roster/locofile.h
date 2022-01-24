#ifndef LOCOFILE_H
#define LOCOFILE_H
#include <QtXml>
#include "xmlfile.h"
#include "Roster/cvtablemodel.h"
#include "rosterentry.h"
#include "Roster/variabletablemodel.h"

class RosterEntry;
class LIBPR3SHARED_EXPORT LocoFile : public XmlFile
{
    Q_OBJECT
public:
 enum MessageResponse
 {
  IGNORE,
  REPORT
 };
    explicit LocoFile(QObject *parent = 0);
    /*public*/ QString titleString();
    /*public*/ static void loadCvModel(QDomElement loco, CvTableModel* cvModel, QString family);
    /*public*/ static void loadVariableModel(QDomElement loco, VariableTableModel* varModel);
    /*public*/ void writeFile(File* pFile, QDomElement pRootElement, RosterEntry* pEntry);
    /*public*/ void writeFile(QFile* file, CvTableModel* cvModel, VariableTableModel* variableModel, RosterEntry* r);
    /*public*/ void writeFile(QFile* pFile, QDomElement pRootElement, RosterEntry* pEntry);
    /*public*/ void writeFile(QFile* pFile, QDomElement existingElement, QDomElement newLocomotive);
    static /*public*/ QString getFileLocation();

signals:

public slots:
private:
 static Logger* log;

protected:
 /*protected*/ static MessageResponse selectMissingVarResponse(QString var);
friend class RosterEntry;
};

#endif // LOCOFILE_H
