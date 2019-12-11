#ifndef SIGNALMASTICONTESTACTION_H
#define SIGNALMASTICONTESTACTION_H
#include "abstractaction.h"

class Logger;
class SignalMastIconTestAction : public AbstractAction
{
 Q_OBJECT
public:
 SignalMastIconTestAction(QObject *parent);

public slots:
 void actionPerformed();

private:
 static Logger* log;
};

#endif // SIGNALMASTICONTESTACTION_H
