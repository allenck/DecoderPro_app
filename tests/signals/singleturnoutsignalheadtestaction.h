#ifndef SINGLETURNOUTSIGNALHEADTESTACTION_H
#define SINGLETURNOUTSIGNALHEADTESTACTION_H
#include "abstractaction.h"

class Logger;
class SingleTurnoutSignalHeadTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SingleTurnoutSignalHeadTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // SINGLETURNOUTSIGNALHEADTESTACTION_H
