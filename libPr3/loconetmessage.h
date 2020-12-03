#ifndef LOCONETMESSAGE_H
#define LOCONETMESSAGE_H

#include <QObject>
#include <QtCore>
#include "lnconstants.h"
#include "logger.h"
#include "abstractmessage.h"

/**
 * Represents a single command or response on the LocoNet.
 *<P>
 * Content is represented with ints to avoid the problems with
 * sign-extension that bytes have, and because a Java char is
 * actually a variable number of bytes in Unicode.
 *<P>
 * Note that this class does not manage the upper bit of
 * the message.  By convention, most LocoNet messages have
 * the upper bit set on the first byte, and on no other byte;
 * but not all of them do, and that must be managed elsewhere.
 *<P>
 * Note that many specific message types are created elsewhere.
 * In general, if more than one tool will need to use a particular
 * format, it's useful to refactor it to here.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 *
 * @author			Bob Jacobsen  Copyright (C) 2001
 * @version			$Revision: 17977 $
 * @see             jmri.jmrix.nce.NceMessage
 *
 */

class LIBPR3SHARED_EXPORT LocoNetMessage : public AbstractMessage
{
 Q_OBJECT
public:
 explicit LocoNetMessage(int len, QObject *parent = 0);
 /*public*/ LocoNetMessage();
 /*public*/ LocoNetMessage(QString s);
 /*public*/ LocoNetMessage(LocoNetMessage* original);

 ~LocoNetMessage();
 /**
  * Create a message with specified contents
  * @param contents The array of contents for the message. The error
  * check word must be present, e.g. a 4-byte message must have
  * four values in the array
  */
 LocoNetMessage(QVector<int> contents, QObject *parent = 0);
 LocoNetMessage(QVector<char> contents, QObject *parent = 0);
 LocoNetMessage(const LocoNetMessage& original, QObject *parent = 0);
 /** Get a String representation of the entire message in hex */
 QString toString();
 void setOpCode(int i);
 int getOpCode();
 /** Get a String representation of the op code in hex */
 QString getOpCodeHex();

 int getNumDataElements();
 int getElement(int n);
 void setElement(int n, int v);
 void setParity();
 bool checkParity();
 /** Get a QVector representing the entire message */
 QVector<char> toCharArray();
 /** Get a QByteArray representing the entire message */
 QByteArray toByteArray();

 /**
  * Get the 8 data bytes from an OPC_PEER_XFR message
  * @return int[8] data bytes
  */
 /*public*/ QVector<int> getPeerXfrData();
 /**
  * Two messages are the same if their entire data content
  * is the same.  We ignore the error-check byte to ease
  * comparisons before a message is transmitted.
  * @return true if objects contain the same message contents
  */
 /*public*/ bool equals(QObject* o);
 /*public*/ int hashCode();
 /*public*/ QString toMonitorString();
 /*public*/ QString toMonitorString(/*@Nonnull*/ QString prefix);
 /**
  * Return a newly created OPC_PEER_XFR message.
  * @param src Source address
  * @param dst Destination address
  * @param d   int[8] for the data contents or null
  * @param code The instruction code placed in the pcxt1 pcxt2 bytes
  * @return    The formatted message
  */
 static /*public*/ LocoNetMessage* makePeerXfr(int src, int dst, QVector<int> d, int code);
 static /*public*/ LocoNetMessage* makePeerXfr2(int src, int dsth, int dstl, int svAdrh, int svAdrl, QVector<int> d, int code);

 /**
  * Sensor-format 0-n address
  * @return 0 to n-1 address
  */
 /*public*/ int sensorAddr();
 /**
  * If this is an OPC_INPUT_REP, return the 0-n address, else -1
  * @return 0 to n-1 address
  */
 /*public*/ int inputRepAddr();
 /**
  * Return the 1-N turnout address
  * @return 1-N address
  */
 /*public*/ int turnoutAddr();

 //QVector<int> _dataChars;

    
signals:
    
public slots:
private:
 //int _nDataChars;
 static Logger* log;
protected:
    /**
     * Check if a high bit is set, usually used to store it in some
     * other location (LocoNet does not allow the high bit to be set
     * in data bytes)
     * @param val
     * @return True if the argument has the high bit set
     */
    static /*protected*/ bool highBit(int val);
    static /*protected*/ int lowByte(int val);
    static /*protected*/ int highByte(int val);
 friend class LocoNetMessageTest;
};
//Q_DECLARE_METATYPE(LocoNetMessage)
#endif // LOCONETMESSAGE_H
