#ifndef NETWORKTOPOLOGYEVENT_H
#define NETWORKTOPOLOGYEVENT_H
#include "eventobject.h"
#include "jmdns.h"

/*public*/ /*abstract*/ class NetworkTopologyEvent : public EventObject {
//Q_OBJECT
    //private static final long serialVersionUID = -8630033521752540987L;

protected:
    /*protected*/ NetworkTopologyEvent(QObject* eventSource, QObject *parent) : EventObject(eventSource, parent) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: invokespecial java/util/EventObject."<init>":(Ljava/lang/Object;)V
         * 5: return
         *  */
        // </editor-fold>
    }
public:
    /*public*/ /*abstract*/virtual JmDNS* getDNS() = 0;

    /*public*/ /*abstract*/ virtual InetAddress* getInetAddress() = 0;
};

#endif // NETWORKTOPOLOGYEVENT_H
