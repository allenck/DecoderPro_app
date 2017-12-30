#ifndef TRACKPOWERCONTROLLER_H
#define TRACKPOWERCONTROLLER_H
#include "abstractcontroller.h"

class PropertyChangeEvent;
class PowerManager;
class Logger;
class TrackPowerController : public AbstractController
{
 Q_OBJECT
public:
 TrackPowerController();
 /*public*/ bool verifyCreation();
 /*public*/ void handleMessage(QString message);
 /*private*/ void setTrackPowerOn();
 /*private*/ void setTrackPowerOff();
 /*public*/ void sendCurrentState();
 /*public*/ void _register();
 /*public*/ void deregister();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TrackPowerController.class.getName());
 /*private*/ PowerManager* pwrMgr;// = null;

};

#endif // TRACKPOWERCONTROLLER_H
