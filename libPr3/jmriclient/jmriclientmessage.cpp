#include "jmriclientmessage.h"

/**
 * Encodes a message to an JMRIClient server. The JMRIClientReply class handles
 * the response from the server.
 * <P>
 * The {@link JMRIClientReply} class handles the response from the server.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2004, 2008
 * @author Paul Bender Copyright (C) 2010
  */
// /*public*/ class JMRIClientMessage extends jmri.jmrix.AbstractMRMessage {

/*public*/ JMRIClientMessage::JMRIClientMessage() {
    //super();
}

// create a new one
/*public*/ JMRIClientMessage::JMRIClientMessage(int i) : AbstractMRMessage(i) {
    //super(i);
}

// copy one
/*public*/ JMRIClientMessage::JMRIClientMessage(JMRIClientMessage* m) : AbstractMRMessage(m) {
    //super(m);
}

// from String
/*public*/ JMRIClientMessage::JMRIClientMessage(QString m) : AbstractMRMessage(m) {
    //super(m);
}

// diagnose format
/*public*/ bool JMRIClientMessage::isKillMain() {
    QString s = toString();
    return s.contains("POWER OFF");
}

/*public*/ bool JMRIClientMessage::isEnableMain() {
    QString s = toString();
    return s.contains("POWER ON");
}

// static methods to return a formatted message
/*static*/ /*public*/ JMRIClientMessage* JMRIClientMessage::getEnableMain() {
    JMRIClientMessage* m = new JMRIClientMessage("POWER ON\n");
    m->setBinary(false);
    return m;
}

/*static*/ /*public*/ JMRIClientMessage* JMRIClientMessage::getKillMain() {
    JMRIClientMessage* m = new JMRIClientMessage("POWER OFF\n");
    m->setBinary(false);
    return m;
}

/*static*/ /*public*/ JMRIClientMessage* JMRIClientMessage::getProgMode() {
    return nullptr;
}

/*static*/ /*public*/ JMRIClientMessage* JMRIClientMessage::getExitProgMode() {
    return nullptr;
}

/*final*/ /*static*/ /*protected*/ int JMRIClientMessage::LONG_TIMEOUT = 180000;  // e.g. for programming options


