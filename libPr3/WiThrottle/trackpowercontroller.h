#ifndef TRACKPOWERCONTROLLER_H
#define TRACKPOWERCONTROLLER_H
#include "abstractcontroller.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class PowerManager;
class Logger;
class TrackPowerController : public AbstractController, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 TrackPowerController();
 /*public*/ bool verifyCreation();
 /*public*/ void handleMessage(QString message);
 /*private*/ void setTrackPowerOn();
 /*private*/ void setTrackPowerOff();
 /*public*/ void sendCurrentState();
 /*public*/ void _register();
 /*public*/ void deregister();

 QObject* pself() override {return (QObject*)this;}
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(TrackPowerController.class.getName());
 /*private*/ PowerManager* pwrMgr;// = null;

};

#endif // TRACKPOWERCONTROLLER_H
