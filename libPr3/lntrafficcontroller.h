#ifndef LNTRAFFICCONTROLLER_H
#define LNTRAFFICCONTROLLER_H

#include "loconetinterface.h"
#include "logger.h"

class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnTrafficController : public LocoNetInterface
{
 Q_OBJECT
public:
 LnTrafficController(QObject* parent = nullptr);
 /*public*/ LnTrafficController(LocoNetSystemConnectionMemo* memo, QObject *parent= nullptr);

 // Abstract methods for the LocoNetInterface
 /*public*/ void setSystemConnectionMemo(LocoNetSystemConnectionMemo* m);
 /*public*/ LocoNetSystemConnectionMemo* getSystemConnectionMemo();

 /*abstract public*/ virtual bool status() {return false;}

 /**
  * Forward a preformatted LocoNetMessage to the actual interface.
  *<P>
  * Implementations should update the transmit count statistic.
  *
  * @param m Message to send; will be updated with CRC
  */
  /*abstract public*/ virtual void sendLocoNetMessage(LocoNetMessage* /*m*/) {}

  // The methods to implement adding and removing listeners

  void virtual addLocoNetListener(int mask,  LocoNetListener* l);

  void virtual removeLocoNetListener(int mask,  LocoNetListener* l);

 /**
  * Forward a LocoNetMessage to all registered listeners.
  * <P>
  * this needs to have public access, as
  * {@link jmri.jmrix.loconet.loconetovertcp.LnOverTcpPacketizer}
  * and
  * {@link jmri.jmrix.loconet.Intellibox.IBLnPacketizer} invoke it,
  * but don't inherit from it
  * @param m Message to forward. Listeners should not modify it!
  */
 //        @SuppressWarnings("unchecked")
 void notify(LocoNetMessage*  m);

 /**
  * Is there a backlog of information for the outbound link?
  * This includes both in the program (e.g. the outbound queue)
  * and in the command station interface (e.g. flow control from the port)
  * @return true if busy, false if nothing waiting to send
  */
 /*virtual*/ virtual bool isXmtBusy();

 /**
  * Reset statistics (received message count, transmitted message count,
  * received byte count)
  */
  void resetStatistics();

 /**
  * Monitor the number of LocoNet messaages received across the interface.
  * This includes the messages this client has sent.
  */
  int getReceivedMsgCount();

 /**
  * Monitor the number of bytes in LocoNet messaages received across the interface.
  * This includes the messages this client has sent.
  */
 int getReceivedByteCount();

 /**
  * Monitor the number of LocoNet messaages transmitted across the interface.
  */
  int getTransmittedMsgCount();

  /*public*/ void dispose();

public slots:
//  void notify(LocoNetMessage*  m);


signals:
  void messageProcessed(LocoNetMessage* msg);
  //void notifyMessage(LocoNetMessage*);

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnTrafficController.class.getName());
//    }
private:
  static Logger* log;
  LocoNetSystemConnectionMemo* memo = nullptr;
 protected:
  QVector<LocoNetListener*> listeners;
  int transmittedMsgCount;
  int receivedMsgCount;
  int receivedByteCount;
protected:

  friend class LnTrafficRouter;
  friend class LnPowerManagerTest;
  friend class LnPowerManager;
};

#endif // LNTRAFFICCONTROLLER_H
