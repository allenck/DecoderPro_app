#ifndef ABSTRACTROSTERITEMACTION_H
#define ABSTRACTROSTERITEMACTION_H

#include "jmriabstractaction.h"
#include "logger.h"
#include "libPr3_global.h"

class QFileInfo;
class JmriPanel;
class JFileChooser;
class File;
class RosterEntry;
class WindowInterface;
class LIBPR3SHARED_EXPORT AbstractRosterItemAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit AbstractRosterItemAction(QObject *parent = 0);
    /*public*/ AbstractRosterItemAction(QString pName, QWidget* pWho);
    /*public*/ AbstractRosterItemAction(QString s, WindowInterface* wi);
    /*public*/ AbstractRosterItemAction(QString s, QIcon i, WindowInterface* wi);
 ~AbstractRosterItemAction() {}
 AbstractRosterItemAction(const AbstractRosterItemAction& other) : JmriAbstractAction(other.text(), other.icon(), (WindowInterface*)other.parent()) {}
    /*public*/ void setExistingEntry(RosterEntry* mFromEntry);
    /*public*/ virtual JmriPanel* makePanel();

signals:

public slots:
    /*public*/ Q_INVOKABLE void actionPerformed(ActionEvent* event = 0);

private:
    QWidget* mParent;
    void updateRoster();
    void common();
    // variables to communicate the "from" entry, file, etc
    QString mFromID;// = null;
    RosterEntry* mFromEntry;// = null;
    File* mFromFile;// = null;
    QString mFromFilename;// = null;
    QString mFullFromFilename;// = null;  // includes path to preferences

    // variables to communicate the "to" entry, file, etc.
    QString mToID;// = null;
    RosterEntry* mToEntry;// = null;
    File* mToFile;// = null;
    QString mToFilename;// = null;
    QString mFullToFilename;// = null;  // includes path to preferences
    bool selectExistingFromEntry();
    Logger* log;
    bool selectNewToEntryID();
    JFileChooser* fileChooser;
    bool selectNewToFile();
    void addToEntryToRoster();
    bool selectNewFromFile();
    QFileInfo* fileInfo;

protected:
    /*protected*/ /*abstract*/ virtual bool selectFrom() {return false;}
    /*abstract*/ virtual bool selectTo() {return false;}
    /*abstract*/ virtual bool doTransfer() {return false;}
friend class CopyRosterItemAction;
friend class ImportRosterItemAction;
friend class ExportRosterItemAction;
friend class FullBackupImportAction;
};
Q_DECLARE_METATYPE(AbstractRosterItemAction)
#endif // ABSTRACTROSTERITEMACTION_H
