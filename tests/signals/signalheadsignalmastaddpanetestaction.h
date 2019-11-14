#ifndef SIGNALHEADSIGNALMASTADDPANETESTACTION_H
#define SIGNALHEADSIGNALMASTADDPANETESTACTION_H
#include "abstractaction.h"

class Logger;
class SignalHeadSignalMastAddPaneTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SignalHeadSignalMastAddPaneTestAction(QObject *parent);
public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // SIGNALHEADSIGNALMASTADDPANETESTACTION_H
