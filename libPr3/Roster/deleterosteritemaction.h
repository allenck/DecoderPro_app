#ifndef DELETEROSTERITEMACTION_H
#define DELETEROSTERITEMACTION_H

#include <QAction>
#include "logger.h"

class JmriPanel;
class RosterEntry;
class WindowInterface;
class DeleteRosterItemAction : public QAction
{
    Q_OBJECT
public:
    //explicit DeleteRosterItemAction(QObject *parent = 0);
    /*public*/ DeleteRosterItemAction(QString s, WindowInterface* wi);
    /*public*/ DeleteRosterItemAction(QString s, QIcon i, WindowInterface* wi);
    /*public*/ DeleteRosterItemAction(QString s, QWidget* who);
    /*public*/ JmriPanel* makePanel();

signals:
public slots:
    /*public*/ void actionPerformed(ActionEvent* event = 0);
private:
    QWidget* _who;
    Logger* log;
    bool userOK(QString entry, QString filename, QString fullFileName);
protected:
    /*protected*/ QList<RosterEntry*>* selectRosterEntry(QString rosterGroup);

};

#endif // DELETEROSTERITEMACTION_H
