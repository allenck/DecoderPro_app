#ifndef SIGNALHEADSIGNALMASTTESTACTION_H
#define SIGNALHEADSIGNALMASTTESTACTION_H
#include"abstractaction.h"

class Logger;
class SignalHeadSignalMastTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SignalHeadSignalMastTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // SIGNALHEADSIGNALMASTTESTACTION_H
