#ifndef CONSISTLISTENER_H
#define CONSISTLISTENER_H

#include <QObject>
#include "dcclocoaddress.h"

class ConsistListener //: public QObject
{
    //Q_OBJECT
public:
    //explicit ConsistListener(QObject *parent = 0);
    //~ConsistListener() {}
    /** Receive notification at the end of a consisting operation.
     *
     * @param locoaddress  Address of specific locomotive involved, if
         *                     error is locomotive specific.
     * @param status Denotes the completion code. Note that this is a
     *                    bitwise combination of the various status coded defined
     *                    in this interface.
     */
    virtual /*public*/ void consistReply(DccLocoAddress* locoaddress, int status) =0;
    /** Constant denoting that the request completed correctly. Note this
     *  is a specific value; all others are bitwise combinations
     */
    static const int OK 			= 0;
    /** Constant denoting that the request failed because it requested some
     * unimplemented capability.  Note that this can also result in an
     * exception during the original request; which happens is implementation
     * dependent */
    static const int NotImplemented = 0x01;

    /**
      * the Operation Completed successfully.
      */
    static const int OPERATION_SUCCESS		= 0x02;

    /**
      * An Error Occured.
      */
    static const int CONSIST_ERROR		= 0x04;

    /**
      * All of the slots available for the consist are full
      * Note: This may not be an error.  If the last locomotive added to
      * the consist caused the number of units in the consist to equal the
      * size limit, the value returned to the listeners should be
      * OPERATION_SUCCESS | CONSIST_FULL.  To indicate an error, send
      * CONSIST_ERROR | CONSIST_FULL, and to send an information
      * message, just send CONSIST_FULL
      */
    static const int CONSIST_FULL		= 0x08;

    /**
      * The requseted locomotive has not been oerated by this device,
      * or is currently being operated by another device
      */
    static const int LOCO_NOT_OPERATED = 0x10;

    /**
      * An add request is not valid for this address because
      * the locomotive is already in a consist.
      */
    static const int ALREADY_CONSISTED = 0x20;

    /**
      * A remove request is not valid for this address because
      * the locomotive is not in a consist.
      */
    static const int NOT_CONSISTED = 0x40;

    /**
      * The operation is not valid because the locomotive's
      * speed is not zero.
      */
    static const int NONZERO_SPEED = 0x80;

    /**
      * The operation is not valid because the specified address is
      * not a consist base address
      */
    static const int NOT_CONSIST_ADDR = 0x100;

    /**
      * The operation failed because it is not possible to delete the
      * locomotive
      */
    static const int DELETE_ERROR = 0x200;

    /**
      * The operation failed because the command station stack is full
      */
    static const int STACK_FULL = 0x400;

    virtual QObject* self() =0;
signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(ConsistListener, "ConsistListener")
#endif // CONSISTLISTENER_H
