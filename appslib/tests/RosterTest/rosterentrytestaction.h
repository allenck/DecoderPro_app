#ifndef ROSTERENTRYTESTACTION_H
#define ROSTERENTRYTESTACTION_H
#include "abstractaction.h"

class Logger;
class RosterEntryTestAction : public AbstractAction
{
 Q_OBJECT
public:
 RosterEntryTestAction(QString text, QObject* parent);
public slots:
    void actionPerformed();
private:
    static Logger* log;
};

#endif // ROSTERENTRYTESTACTION_H
