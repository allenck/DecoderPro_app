#ifndef THROTTLECONTROLLERLISTENER_H
#define THROTTLECONTROLLERLISTENER_H
#include "eventlistener.h"
/**
 *
 * @author Brett
 */
class ThrottleController;
/*public*/ /*interface*/ class ThrottleControllerListener : public EventListener {
 Q_OBJECT
public slots:

    /*public*/ virtual void notifyControllerAddressFound(ThrottleController* TC) {}

    /*public*/ virtual void notifyControllerAddressReleased(ThrottleController* TC) {}

};
#endif // THROTTLECONTROLLERLISTENER_H
