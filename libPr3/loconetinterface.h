#ifndef LOCONETINTERFACE_H
#define LOCONETINTERFACE_H

#include <QObject>
#include "loconetmessage.h"
#include "loconetlistener.h"

class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LocoNetInterface : public QObject
{
 Q_OBJECT
 public:
    explicit LocoNetInterface(QObject *parent = 0) : QObject(parent) {}
  /*
   * Request a message be sent to the attached LocoNet. Return is immediate,
   * with the message being queued for eventual sending.  If you're interested
   * in a reply, you need to register a LocoNetListener object to watch the
   * message stream.
   */
  virtual void sendLocoNetMessage(LocoNetMessage* /*msg*/) {}

  /**
   * Request notification of things happening on the LocoNet.
   *<P>
   * The same listener
   * can register multiple times with different masks.  (Multiple registrations with
   * a single mask value are equivalent to a single registration)
   * Mask values are defined as class constants.  Note that these are bit masks,
   * and should be OR'd, not added, if multiple values are desired.
   *<P>
   * The event notification contains the received message as source, not this object,
   * so that we can notify of an incoming message to multiple places and then move on.
   *
   * @param mask The OR of the key values of messages to be reported (to reduce traffic,
   *             provide for listeners interested in different things)
   *
   * @param listener Object to be notified of new messages as they arrive.
   *
   */
 virtual void addLocoNetListener(int /*mask*/, const LocoNetListener* /*listener*/){}

    /*
     * Stop notification of things happening on the LocoNet. Note that mask and LocoNetListener
     * must match a previous request exactly.
     */
 virtual void removeLocoNetListener(int /*mask*/, const LocoNetListener* /*listener*/) {}

    /*
     * Check whether an implementation is operational. True indicates OK.
     */
    virtual bool status() { return false;}

    /**
     * Mask value to request notification of all incoming messages
     */
const static int  ALL	=		  ~0;

    /**
     * Mask value to request notification of messages effecting slot status, including the programming slot
     */
const static int   SLOTINFO		=   1;

    /**
     * Mask value to request notification of messages associated with programming
     */
const static int  PROGRAMMING	=	   2;

    /**
     * Mask value to request notification of messages indicating changes in turnout status
     */
const static int   TURNOUTS		=   4;

    /**
     * Mask value to request notification of messages indicating changes in sensor status
     */
const static int   SENSORS		=	   8;

    /**
     * Mask value to request notification of messages associated with layout power
     */
const static int   POWER			=  16;

/**
     * Set the system connection memo associated with this connection.
     *
     * @param m associated systemConnectionMemo object
     */
   /*public*/ virtual void setSystemConnectionMemo(LocoNetSystemConnectionMemo* /*m*/) {}

    /**
     * Get the system connection memo associated with this connection.
     *
     * @return the associated systemConnectionMemo object
     */
    /*public*/ virtual LocoNetSystemConnectionMemo* getSystemConnectionMemo() {return nullptr;}

signals:
 void messageProcessed(LocoNetMessage* msg);
    
public slots:
    
};
Q_DECLARE_INTERFACE(LocoNetInterface, "LocoNet interface")
#endif // LOCONETINTERFACE_H
