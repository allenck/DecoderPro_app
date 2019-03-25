#include "jmriclienttrafficcontroller.h"
#include "jmriclientlistener.h"
#include "jmriclientmessage.h"
#include "jmriclientreply.h"

/**
 * Converts Stream-based I/O to/from JMRIClient messages. The
 * "JMRIClientInterface" side sends/receives message objects.
 * <p>
 * The connection to a JMRIClientPortController is via a pair of *Streams, which
 * then carry sequences of characters for transmission. Note that this
 * processing is handled in an independent thread.
 * <p>
 * This handles the state transitions, based on the necessary state in each
 * message.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 */
// /*public*/ class JMRIClientTrafficController extends AbstractMRTrafficController
//        implements JMRIClientInterface {

/**
 * Create a new JMRIClientTrafficController instance.
 */
/*public*/ JMRIClientTrafficController::JMRIClientTrafficController(QObject *parent)
 : AbstractMRTrafficController(parent){
    //super();
    setAllowUnexpectedReply(true);
}

// The methods to implement the JMRIClientInterface
//@Override
/*public*/ /*synchronized*/ void JMRIClientTrafficController::addJMRIClientListener(JMRIClientListener* l) {
    this->addListener(l);
}

//@Override
/*public*/ /*synchronized*/ void JMRIClientTrafficController::removeJMRIClientListener(JMRIClientListener* l) {
    this->removeListener(l);
}

/**
 * Forward a JMRIClientMessage to all registered JMRIClientInterface
 * listeners.
 */
//@Override
/*protected*/ void JMRIClientTrafficController::forwardMessage(AbstractMRListener* client, AbstractMRMessage* m) {
    ((JMRIClientListener*) client)->message((JMRIClientMessage*) m);
}

/**
 * Forward a JMRIClientReply to all registered JMRIClientInterface
 * listeners.
 */
//@Override
/*protected*/ void JMRIClientTrafficController::forwardReply(AbstractMRListener* client, AbstractMRReply* m) {
    ((JMRIClientListener*) client)->reply((AbstractMRMessage*) m);
}

//@Override
/*protected*/ AbstractMRMessage* JMRIClientTrafficController::pollMessage() {
    return nullptr;
}

//@Override
/*protected*/ AbstractMRListener* JMRIClientTrafficController::pollReplyHandler() {
    return nullptr;
}

/**
 * Forward a preformatted message to the actual interface.
 */
//@Override
/*public*/ void JMRIClientTrafficController::sendJMRIClientMessage(JMRIClientMessage* m, JMRIClientListener* reply) {
    sendMessage(m, reply);
}

//@Override
/*protected*/ AbstractMRMessage* JMRIClientTrafficController::enterProgMode() {
    return JMRIClientMessage::getProgMode();
}

//@Override
/*protected*/ AbstractMRMessage* JMRIClientTrafficController::enterNormalMode() {
    return JMRIClientMessage::getExitProgMode();
}

//@Override
/*protected*/ AbstractMRReply* JMRIClientTrafficController::newReply() {
    return new JMRIClientReply();
}

//@Override
/*protected*/ bool JMRIClientTrafficController::endOfMessage(AbstractMRReply* msg) {
    int index = msg->getNumDataElements() - 1;
    if (msg->getElement(index) == 0x0D) {
        return true;
    }
    if (msg->getElement(index) == 0x0A) {
        return true;
    } else {
        return false;
    }
}

