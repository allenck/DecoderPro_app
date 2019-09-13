#ifndef ROSTERENTRYTESTACTION_H
#define ROSTERENTRYTESTACTION_H
#include "abstractaction.h"

class RosterEntryTestAction : public AbstractAction
{
 Q_OBJECT
public:
 RosterEntryTestAction(QString text, QObject* parent);
public slots:
    void actionPerformed();
};

#endif // ROSTERENTRYTESTACTION_H
