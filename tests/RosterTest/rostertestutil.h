#ifndef ROSTERTESTUTIL_H
#define ROSTERTESTUTIL_H

#include <QObject>
#include "exceptions.h"

class Logger;
class Roster;
class File;
class DecoderFile;
class RosterEntry;
class VariableTableModel;
class RosterTestUtil : public QObject
{
    Q_OBJECT
public:
    explicit RosterTestUtil(QObject *parent = nullptr);
    /*public*/ static Roster* createTestRoster(File* rosterDir, QString rosterFileName) throw (IOException);
    /*public*/ static void loadDecoderFromLoco(RosterEntry* r, VariableTableModel* varTable);

signals:

public slots:
private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(RosterTestUtil.class);
    /*private*/ static void loadDecoderFile(DecoderFile* df, RosterEntry* re, VariableTableModel* variableModel);

};

#endif // ROSTERTESTUTIL_H
