#ifndef LOCONETINTERFACESTATSLISTENER_H
#define LOCONETINTERFACESTATSLISTENER_H
#include "eventlistener.h"

/**
 * Interface for objects that want to be notified when a
 * {@link jmri.jmrix.loconet.LocoNetSlot} is modified.

 * @author Bob Milhaupt
 */
/*public*/ /*interface*/class  LocoNetInterfaceStatsListener : public EventListener {
public:
    /*public*/ virtual void notifyChangedInterfaceStatus(QObject* s) =0;

};
Q_DECLARE_INTERFACE(LocoNetInterfaceStatsListener, "LocoNetInterfaceStatsListener")
#endif // LOCONETINTERFACESTATSLISTENER_H
