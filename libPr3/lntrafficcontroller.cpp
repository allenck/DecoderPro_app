#include "lntrafficcontroller.h"
#include <QMutex>
#include "loconetsystemconnectionmemo.h"
#include "loggerfactory.h"

LnTrafficController::LnTrafficController(QObject *parent) : LocoNetInterface(parent)
{
 resetStatistics();
// listeners.clear();
 setObjectName("LnTrafficController");
}


/**
 * Constructor. Gets a reference to the LocoNetSystemConnectionMemo.
 *
 * @param memo connection's memo
 */
/*public*/ LnTrafficController::LnTrafficController(LocoNetSystemConnectionMemo* memo, QObject *parent)
: LocoNetInterface(parent)
{
    //super();
    this->memo = memo;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LnTrafficController::setSystemConnectionMemo(LocoNetSystemConnectionMemo* m) {
    log->debug(tr("LnTrafficController set memo to $1").arg(m->getUserName()));
    memo = m;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ LocoNetSystemConnectionMemo* LnTrafficController::getSystemConnectionMemo() {
    log->debug(tr("getSystemConnectionMemo %1 called in LnTC").arg(memo->getUserName()));
    return memo;
}

// Abstract methods for the LocoNetInterface
//@Override
// /*abstract*/ public boolean status();


void LnTrafficController::addLocoNetListener(int mask,  LocoNetListener* l)
{
 Q_UNUSED(mask)
 // add only if not already registered
 //if (l == NULL) throw new java.lang.NullPointerException();
 Q_ASSERT(l != NULL);
 if (!listeners.contains(l))
 {
  listeners.append(l);
 }
}
void LnTrafficController::removeLocoNetListener(int mask,  LocoNetListener* l)
{
 Q_UNUSED(mask)
 if (listeners.contains(l))
 {
  listeners.remove(listeners.indexOf(l));
 }
}

#if 1 // not necessary; replaced by signal/slots logic
void LnTrafficController::notify(LocoNetMessage* m)
{
   // record statistics
   receivedMsgCount++;
   receivedByteCount += m->getNumDataElements();

   // make a copy of the listener vector to synchronized not needed for transmit
//   QVector<LocoNetListener*>* v;
//   QMutex mutex1;
////   synchronized(this)
//   {
////    v = (QVector<LocoNetListener>) listeners.clone();
//    mutex1.lock();
//    v = new QVector<LocoNetListener*>(listeners);
//    mutex1.unlock();
//   }
//   if (log.isDebugEnabled()) log.debug("notify of incoming LocoNet packet: "+m->toString());
//   // forward to all listeners
//   int cnt = v->size();
//   for (int i=0; i < cnt; i++)
//   {
//    LocoNetListener* client = listeners.at(i);
//    client->message(m);
//   }
   //emit notifyMessage( m);
   emit messageProcessed(m);
}
#endif
void LnTrafficController::resetStatistics()
{
   receivedMsgCount = 0;
   transmittedMsgCount = 0;
   receivedByteCount = 0;
}

/**
 * Clean up any resources, particularly threads.
 * <p>
 * The object can't be used after this.
 */
/*public*/ void LnTrafficController::dispose() {}

/**
 * Monitor the number of LocoNet messaages received across the interface.
 * This includes the messages this client has sent.
 */
 int LnTrafficController::getReceivedMsgCount() { return receivedMsgCount;}

/**
 * Monitor the number of bytes in LocoNet messaages received across the interface.
 * This includes the messages this client has sent.
 */
int LnTrafficController::getReceivedByteCount() {
   return receivedByteCount;
}

/**
 * Monitor the number of LocoNet messaages transmitted across the interface.
 */
 int LnTrafficController::getTransmittedMsgCount() {
   return transmittedMsgCount;
}
// TODO: For now, return false.
bool LnTrafficController::isXmtBusy() { return false;}

/*private*/ /*final*/ /*static*/ Logger* LnTrafficController::log = LoggerFactory::getLogger("LnTrafficController");
