#ifndef LNTURNOUTMANAGERTESTACTION_H
#define LNTURNOUTMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class LnTurnoutManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LnTurnoutManagerTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LNTURNOUTMANAGERTESTACTION_H
