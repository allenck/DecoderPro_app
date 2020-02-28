#ifndef ENTRYEXITPAIRSTESTACTION_H
#define ENTRYEXITPAIRSTESTACTION_H
#include "abstractaction.h"

class Logger;
class EntryExitPairsTestAction : public AbstractAction
{
 Q_OBJECT
public:
 EntryExitPairsTestAction(QObject* parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // ENTRYEXITPAIRSTESTACTION_H
