#ifndef ROSTERENTRYPANETESTACTION_H
#define ROSTERENTRYPANETESTACTION_H
#include "abstractaction.h"

class RosterEntryPaneTestAction : public AbstractAction
{
    Q_OBJECT
public:
    RosterEntryPaneTestAction(QString text, QObject *parent);
public slots:
    void actionPerformed();

};

#endif // ROSTERENTRYPANETESTACTION_H
