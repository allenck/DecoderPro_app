#ifndef DOUBLETURNOUTSIGNALHEADTESTACTION_H
#define DOUBLETURNOUTSIGNALHEADTESTACTION_H
#include "abstractaction.h"

class Logger;
class DoubleTurnoutSignalHeadTestAction : public AbstractAction
{
 Q_OBJECT
public:
 DoubleTurnoutSignalHeadTestAction(QObject *parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // DOUBLETURNOUTSIGNALHEADTESTACTION_H
