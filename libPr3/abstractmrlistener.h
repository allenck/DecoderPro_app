#ifndef ABSTRACTMRLISTENER_H
#define ABSTRACTMRLISTENER_H
#include "eventlistener.h"
#include "libPr3_global.h"
#include "abstractmrmessage.h"

/**
 * Interface (perhaps eventually abstract base) for Message/Reply
 * protocol Listeners
 *
 * @author		Bob Jacobsen  Copyright (C) 2003
 * @version             $Revision: 17977 $
 */
/*public interface*/ class LIBPR3SHARED_EXPORT AbstractMRListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 QObject* self() {return (QObject*)this;}
public slots:
 /*public*/ virtual void message(AbstractMRMessage* /*m*/) {}

 /*public*/ virtual void reply(AbstractMRMessage* /*m*/, AbstractMRListener*) {}

 friend class AbstractMRTrafficController;
};
#endif // ABSTRACTMRLISTENER_H
