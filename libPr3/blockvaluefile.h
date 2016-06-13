#ifndef BLOCKVALUEFILE_H
#define BLOCKVALUEFILE_H
#include "xmlfile.h"
#include "instancemanager.h"
#include "Roster/rosterentry.h"

class LIBPR3SHARED_EXPORT BlockValueFile : public XmlFile
{
    Q_OBJECT
public:
    explicit BlockValueFile(QObject *parent = 0);
    /*public*/ void readBlockValues() throw (JDOMException, IOException);
    /*public*/ void writeBlockValues() throw (IOException);

signals:

public slots:
private:
    // operational variables
    /*private*/ BlockManager* blockManager;// = null;
    /*private*/ static QString defaultFileName;// = FileUtil.getUserFilesPath()+"blockvalues.xml";
    /*private*/ QDomDocument doc;// = NULL;
    /*private*/ QDomElement root;// = null;
Logger* log;

};
//Q_DECLARE_METATYPE(RosterEntry)


#endif // BLOCKVALUEFILE_H
