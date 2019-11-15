#ifndef TURNOUTSIGNALMASTTESTACTION_H
#define TURNOUTSIGNALMASTTESTACTION_H
#include "abstractaction.h"

class Logger;
class TurnoutSignalMastTestAction : public AbstractAction
{
 Q_OBJECT
public:
 TurnoutSignalMastTestAction(QObject * parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // TURNOUTSIGNALMASTTESTACTION_H
