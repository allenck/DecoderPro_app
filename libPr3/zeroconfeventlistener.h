#ifndef ZEROCONFEVENTLISTENER_H
#define ZEROCONFEVENTLISTENER_H
#include "eventlistener.h"
#include "zeroconfserviceevent.h"

/**
 * Provide an interface for listening to ZeroConfServices.
 *
 * @author rhwood
 */
/*public*/ /*interface*/class ZeroConfServiceListener : public QObject, public EventListener {
Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 QObject* self() {return (QObject*)this;}
public slots:
 /*public*/ virtual void serviceQueued(ZeroConfServiceEvent* /*se*/) {}

 /*public*/ virtual void servicePublished(ZeroConfServiceEvent* /*se*/) {}

 /*public*/ virtual void serviceUnpublished(ZeroConfServiceEvent* /*se*/) {}

};
Q_DECLARE_INTERFACE(ZeroConfServiceListener, "ZeroConfServiceListener")
#endif // ZEROCONFEVENTLISTENER_H
