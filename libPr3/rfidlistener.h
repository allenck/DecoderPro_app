#ifndef RFIDLISTENER_H
#define RFIDLISTENER_H
#include "abstractmrlistener.h"

/**
 * Listener interface to be notified about serial traffic
 *
 * @author      Bob Jacobsen  Copyright (C) 2001, 2006, 2007, 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
class RfidMessage;
class RfidReply;

/*public interface*/ class RfidListener : public AbstractMRListener
{
    /*public*/ virtual void message(RfidMessage* m);
    /*public*/ virtual void reply(RfidReply m);
};

#endif // RFIDLISTENER_H
