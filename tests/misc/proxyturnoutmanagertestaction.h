#ifndef PROXYTURNOUTMANAGERTESTACTION_H
#define PROXYTURNOUTMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProxyTurnoutManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ProxyTurnoutManagerTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // PROXYTURNOUTMANAGERTESTACTION_H
