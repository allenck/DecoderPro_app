#ifndef TURNOUTSIGNALMASTADDPANETESTACTION_H
#define TURNOUTSIGNALMASTADDPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class TurnoutSignalMastAddPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 TurnoutSignalMastAddPaneTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // TURNOUTSIGNALMASTADDPANETESTACTION_H
