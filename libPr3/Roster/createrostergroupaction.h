#ifndef CREATEROSTERGROUPACTION_H
#define CREATEROSTERGROUPACTION_H

#include "jmriabstractaction.h"
#include "logger.h"
#include "rosterentry.h"
#include "libPr3_global.h"

class JmriPanel;
class JActionEvent;
class QIcon;
//class RosterEntry;
class LIBPR3SHARED_EXPORT CreateRosterGroupAction : public JmriAbstractAction
{
    Q_OBJECT
public:
    explicit CreateRosterGroupAction(QObject *parent = 0);
    /*public*/ CreateRosterGroupAction(QString s, /*WindowInterface* wi,*/ QWidget *parent);
    /*public*/ CreateRosterGroupAction(QString s, QIcon i, /*WindowInterface wi,*/ QWidget *parent);
 ~CreateRosterGroupAction() {}
 CreateRosterGroupAction(const CreateRosterGroupAction& other) : JmriAbstractAction(tr("Create Roster Group"),other.icon(), (WindowInterface*)other.parent()) {}
//    /*public*/ CreateRosterGroupAction(QString s, QWidget* who ) ;
    /*public*/ JmriPanel* makePanel();
    /*public*/ void setParameter(QString key, QObject* value);

signals:

public slots:
        /*public*/ void actionPerformed(ActionEvent* event = 0);
private:
    QWidget* _who;
    QList<RosterEntry*>* rosterEntries;
    Logger* log;
};
Q_DECLARE_METATYPE(CreateRosterGroupAction)
#endif // CREATEROSTERGROUPACTION_H
