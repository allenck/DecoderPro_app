#ifndef PROGLISTENER_H
#define PROGLISTENER_H

#include <QObject>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT ProgListener //: public QObject
{
    //Q_OBJECT
    Q_ENUMS(status)
public:
    //explicit ProgListener(QObject *parent = 0);

    /** Constant denoting that the request completed correctly. Note this
     *  is a specific value; all others are bitwise combinations
     */
    enum status
    {
     OK 			= 0,

    /** Constant denoting the request failed, but no specific reason is known */
    UnknownError 	= 1,

    /** Constant denoting that no decoder was detected on the programming track */
    NoLocoDetected = 2,

    /** Constant denoting that the request failed because the decoding hardware
     * was already busy */
    ProgrammerBusy = 4,

    /** Constant denoting that the request failed because it requested some
     * unimplemented capability.  Note that this can also result in an
     * exception during the original request; which happens is implementation
     * dependent */
    NotImplemented = 8,

    /** Constant denoting that the user (human or software) aborted the request
     * before completion */
    UserAborted    = 0x10,

    /** Constant denoting there was no acknowledge from the locomotive, so
     *  the CV may or may not have been written on a write.  No value was read. */
    NoAck		= 0x20,

    /** Constant denoting that confirm failed, likely due to another value being present */
    ConfirmFailed  = 0x40,

    /** Constant denoting that the programming operation timed out */
    FailedTimeout  = 0x80,

    /** Constant denoting that a short circuit occured while programming */
    ProgrammingShort  = 0x100,

    /** Constant denoting that there was an error with the programming
         *  sequence (e.g. early exit) */
    SequenceError  = 0x200,

    /** Constant denoting that a communications error occured between
         * the command station and the PC durring programming */
    CommError  = 0x400
    };
    //Q_ENUM(status)

    static QString statusString(ProgListener::status type);

signals:
    
public slots:
    /** Receive a callback at the end of a programming operation.
     *
     * @param value  Value from a read operation, or value written on a write
     * @param status Denotes the completion code. Note that this is a
     *                    bitwise combination of the various status coded defined
     *                    in this interface.
     */
    virtual void programmingOpReply(int value, int status) = 0;

    virtual QObject* self() =0;

};
Q_DECLARE_INTERFACE(ProgListener, "ProgListener")
#endif // PROGLISTENER_H
