#ifndef THROTTLECONTROLLERLISTENER_H
#define THROTTLECONTROLLERLISTENER_H
#include "eventlistener.h"
/**
 *
 * @author Brett
 */
class ThrottleController;
/*public*/ /*interface*/ class ThrottleControllerListener : public QObject, public EventListener {
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 QObject* self() {return (QObject*)this;}
public slots:

    /*public*/ virtual void notifyControllerAddressFound(ThrottleController* TC) {}

    /*public*/ virtual void notifyControllerAddressReleased(ThrottleController* TC) {}

};
#endif // THROTTLECONTROLLERLISTENER_H
