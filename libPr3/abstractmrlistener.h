#ifndef ABSTRACTMRLISTENER_H
#define ABSTRACTMRLISTENER_H
#include "eventlistener.h"
#include "libPr3_global.h"

/**
 * Interface (perhaps eventually abstract base) for Message/Reply
 * protocol Listeners
 *
 * @author		Bob Jacobsen  Copyright (C) 2003
 * @version             $Revision: 17977 $
 */
/*public interface*/ class LIBPR3SHARED_EXPORT AbstractMRListener : public EventListener
{
 friend class AbstractMRTrafficController;
};
#endif // ABSTRACTMRLISTENER_H
