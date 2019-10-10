#ifndef PROXYSENSORMANAGERTESTACTION_H
#define PROXYSENSORMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProxySensorManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ProxySensorManagerTestAction(QObject *parent);
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // PROXYSENSORMANAGERTESTACTION_H
