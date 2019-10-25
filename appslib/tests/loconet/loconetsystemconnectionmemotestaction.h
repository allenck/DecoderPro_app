#ifndef LOCONETSYSTEMCONNECTIONMEMOTESTACTION_H
#define LOCONETSYSTEMCONNECTIONMEMOTESTACTION_H
#include "abstractaction.h"

class Logger;
class LoconetSystemConnectionMemoTestAction : public AbstractAction
{
 Q_OBJECT
public:
 LoconetSystemConnectionMemoTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // LOCONETSYSTEMCONNECTIONMEMOTESTACTION_H
