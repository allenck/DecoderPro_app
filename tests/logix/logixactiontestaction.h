#ifndef LOGIXACTIONTESTACTION_H
#define LOGIXACTIONTESTACTION_H
#include "abstractaction.h"

class Logger;
class LogixActionTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LogixActionTestAction(QObject *parent);

public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LOGIXACTIONTESTACTION_H
