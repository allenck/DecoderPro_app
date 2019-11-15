#ifndef TRIPLETURNOUTSIGNALHEADTESTACTION_H
#define TRIPLETURNOUTSIGNALHEADTESTACTION_H
#include"abstractaction.h"

class Logger;
class TripleTurnoutSignalHeadTestAction : public AbstractAction
{
 Q_OBJECT
public:
 TripleTurnoutSignalHeadTestAction(QObject* parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // TRIPLETURNOUTSIGNALHEADTESTACTION_H
