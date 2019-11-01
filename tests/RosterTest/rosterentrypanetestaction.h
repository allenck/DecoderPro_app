#ifndef ROSTERENTRYPANETESTACTION_H
#define ROSTERENTRYPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class RosterEntryPaneTestAction : public AbstractAction
{
    Q_OBJECT
public:
    RosterEntryPaneTestAction(QString text, QObject *parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;

};

#endif // ROSTERENTRYPANETESTACTION_H
