#ifndef NETWORKTOPOLOGYLISTENER_H
#define NETWORKTOPOLOGYLISTENER_H
#include "eventlistener.h"
#include "networktopologyevent.h"

/*public*/ /*interface*/ class NetworkTopologyListener : public EventListener {

    /*public*/ virtual void inetAddressAdded(NetworkTopologyEvent* nte) = 0;

    /*public*/ virtual void inetAddressRemoved(NetworkTopologyEvent* nte) =0;
};
Q_DECLARE_INTERFACE(NetworkTopologyListener, "NetworkTopologyListener")
#endif // NETWORKTOPOLOGYLISTENER_H
