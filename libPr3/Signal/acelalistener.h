#ifndef ACELALISTENER_H
#define ACELALISTENER_H
#include "abstractmrlistener.h"
#include "acelamessage.h"
#include "acelareply.h"
/**
 * Listener interface to be notified about Acela traffic
 *
 * @author Bob Jacobsen Copyright (C) 2001
  *
 * @author Bob Coleman Copyright (C) 2007, 2008 Based on CMRI serial example,
 * modified to establish Acela support.
 */
/*public*/  class AcelaListener : public AbstractMRListener {

 Q_INTERFACES(AbstractMRListener)
    /*public*/ virtual void message(AcelaMessage* m)=0;

    /*public*/ virtual void reply(AcelaReply* m) =0;
};
#endif // ACELALISTENER_H
