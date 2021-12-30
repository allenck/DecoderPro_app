#include "acelamessage.h"
#include "stringutil.h"

/**
 * Contains the data payload of an Acela packet.
 *
 * @author Bob Jacobsen Copyright (C) 2001,2003
 * @author Bob Coleman Copyright (C) 2007, 2008 Based on CMRI serial example,
 * modified to establish Acela support.
 */
// public*/ class AcelaMessage : public AbstractMRMessage {
    // is this logically an abstract class?


/*public*/ AcelaMessage::AcelaMessage(QObject* parent) : AbstractMRMessage(parent){
    //super();
}

// create a new one
/*public*/ AcelaMessage::AcelaMessage(int i, QObject* parent): AbstractMRMessage(i, parent){
    //super(i);
}

// copy one
/*public*/ AcelaMessage::AcelaMessage(AcelaMessage* m, QObject* parent) :  AbstractMRMessage(m,parent){
    //super(m);
}

/**
 * This ctor interprets the String as the exact sequence to send,
 * byte-for-byte.
 *
 * @param m string form of message.
 */
/*public*/ AcelaMessage::AcelaMessage(QString m, QObject* parent)  :  AbstractMRMessage(m, parent){
    //super(m);
}

#if 0
/**
 * This ctor interprets the byte array as a sequence of characters to send.
 *
 * @param a Array of bytes to send
 */
/*public*/ AcelaMessage(QVector<qint8> a, QObject* parent) {
    super(String.valueOf(a));
}
#endif
//@Override
/*public*/ QString AcelaMessage::toString() {
    QString s;// = new StringBuilder();
    for (int i = 0; i < getNumDataElements(); i++) {
        if (i != 0) {
            s.append(" ");
        }
        s.append(StringUtil::twoHexFromInt(getElement(i)));
    }
    return s/*.toString()*/;
}

// static methods to return a formatted message
// used within AcelaTrafficController to initialize Acela system
/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaVersionMsg() {
    AcelaMessage* m = new AcelaMessage(1);
    m->setBinary(true);
    m->setElement(0, 0x19);
    return m;
}

/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaResetMsg() {
    // create an Acela message and add initialization bytes
    AcelaMessage* m = new AcelaMessage(1);
    m->setBinary(true);
    m->setElement(0, 0x15);  //  Acela command to reset Acela network
    return m;
}

/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaOnlineMsg() {
    // create an Acela message and add initialization bytes
    AcelaMessage* m = new AcelaMessage(1);
    m->setBinary(true);
    m->setElement(0, 0x16);  //  Acela command to put Acela network ONLINE
    return m;
}

/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaPollNodesMsg() {
    // create an Acela message and add initialization bytes
    AcelaMessage* m = new AcelaMessage(1);
    m->setBinary(true);
    m->setElement(0, 0x18);  // Acela command to poll Acela network nodes
    return m;
}

/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaPollSensorsMsg() {
    // create an Acela message and add initialization bytes
    AcelaMessage* m = new AcelaMessage(1);
    m->setBinary(true);
    m->setElement(0, 0x14);  // Acela command to poll all sensors
    return m;
}

/*static*/ /*public*/ AcelaMessage* AcelaMessage::getAcelaConfigSensorMsg() {
    // create an Acela message and add initialization bytes
    AcelaMessage* m = new AcelaMessage(4);
    m->setBinary(true);
    m->setElement(0, 0x10);  // Acela command to configure one sensor
    m->setElement(1, 0x00);  // Address
    m->setElement(2, 0x00);  // Address
    m->setElement(3, 0x25);  // ending bits[2,1] == 10 means IR
    // ending bit[0] == 1 means invert output
    // bits [15,3] == sensitivity so 0010 0 is low
    return m;
    }
