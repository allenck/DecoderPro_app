#ifndef TURNOUTCONTROLLER_H
#define TURNOUTCONTROLLER_H
#include "abstractcontroller.h"

class Turnout;
class PropertyChangeEvent;
class Logger;
class ProxyTurnoutManager;
class TurnoutController : public AbstractController
{
 Q_OBJECT
public:
 TurnoutController();
 /*public*/ void filterList();
 /*public*/ void sendTitles();
 /*public*/ void sendList();
 /*public*/ void sendTurnoutState(Turnout* t);
 /*public*/ void _register();
 /*public*/ void deregister();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent*evt);

private:
 /*private*/ ProxyTurnoutManager* manager;// = null;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("TurnoutController");
 bool verifyCreation();
 void handleMessage(QString message);
friend class DeviceServer;
};

#endif // TURNOUTCONTROLLER_H
