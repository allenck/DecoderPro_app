#include "jmriclientreply.h"
#include "loggerfactory.h"

/**
 * Carries the reply to an JMRIClientMessage.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2004, 2008
 */
// /*public*/ class JMRIClientReply extends jmri.jmrix.AbstractMRReply {

// create a new one
/*public*/ JMRIClientReply::JMRIClientReply() {
    //super();
}

/*public*/ JMRIClientReply::JMRIClientReply(QString s)  : AbstractMRReply(s){
    //super(s);
}

/*public*/ JMRIClientReply::JMRIClientReply(JMRIClientReply* l) : AbstractMRReply(l) {
    //super(l);
}

/*public*/ bool JMRIClientReply::isResponseOK() {
    return getResponseCode().at(0) == '1' || getResponseCode().at(0) == '2';
}

/*public*/ QString JMRIClientReply::getResponseCode() {
    // split into 3 parts {TIMESTAMP, ResponseCode, Rest}
    // and use the second one (ResponseCode)
    QStringList part = toString().split("\\s"/*, 3*/);
    return part[1];
}

//@Override
/*protected*/ int JMRIClientReply::skipPrefix(int index) {
    // start at index, passing any whitespace & control characters at the start of the buffer
    while (index < getNumDataElements() - 1
            && ((char) getElement(index) <= ' ')) {
        index++;
    }
    return index;
}

/**
 * Extracts Read-CV returned value from a message. Returns -1 if message
 * can't be parsed. Expects a message of the form 1264343601.156 100 INFO 1
 * SM -1 CV 8 99
 */
//@Override
/*public*/ int JMRIClientReply::value() {
    QString s = toString();
    QStringList part = s.split("\\s"/*, 10*/);
    int val = -1;

    bool bok;
        int tmp = part[8].toInt(&bok);
        val = tmp;  // don't do this assign until now in case the conversion throws
    if(!bok) {
        log->error("Unable to get number from reply: \"" + s + "\"");
    }
    return val;
}

//@Override
/*public*/ bool JMRIClientReply::isUnsolicited() {
    QString s = toString();
    // Split in 7 is enough for initial handshake
    QStringList part = s.split("\\s"/*, 7*/);
    // Test for initial handshake message with key "JMRIClient".
    if (part[2] == ("JMRIClient")) {
        setUnsolicited();
        return true;
    } else {
        return false;
    }
}

/*private*/ /*final*/ /*static*/ Logger* JMRIClientReply::log = LoggerFactory::getLogger("JMRIClientReply");

