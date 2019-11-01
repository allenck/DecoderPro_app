#ifndef PROXYLIGHTMANAGERTESTACTION_H
#define PROXYLIGHTMANAGERTESTACTION_H
#include "abstractaction.h"

class Logger;
class ProxyLightManagerTestAction : public AbstractAction
{
 Q_OBJECT
public:
 ProxyLightManagerTestAction(QObject* parent );
public slots:
 void actionPerformed();
private:
 static Logger* log;
};

#endif // PROXYLIGHTMANAGERTESTACTION_H
