#include "jmriclientreporter.h"
#include "jmriclientsystemconnectionmemo.h"
#include "loggerfactory.h"
#include "jmriclienttrafficcontroller.h"
#include "jmriclientlistener.h"
#include "jmriclientmessage.h"
#include "jmriclientreply.h"

/**
 * JMRIClient implementation of the Reporter interface.
 * <P>
 *
 * Description: extend jmri.AbstractReporter for JMRIClient layouts
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 * @author Paul Bender Copyright (C) 2010
  */
///*public*/ class JMRIClientReporter extends AbstractReporter implements JMRIClientListener {

/**
 * JMRIClient reporters use the reporter number on the remote host.
 */
/*public*/ JMRIClientReporter::JMRIClientReporter(int number, JMRIClientSystemConnectionMemo* memo, QObject *parent)
 : AbstractReporter(memo->getSystemPrefix() + "R" + QString::number(number))
{
    //super(memo.getSystemPrefix() + "R" + QString::number(number));
    transmitName = memo->getTransmitPrefix() + "R" + QString::number(number);
    _number = number;
    tc = memo->getJMRIClientTrafficController();
    // At construction, register for messages
    tc->addJMRIClientListener((JMRIClientListener*)this);
    // Then request status.
    requestUpdateFromLayout();
}

/*public*/ int JMRIClientReporter::getNumber() {
    return _number;
}

/*public*/ void JMRIClientReporter::requestUpdateFromLayout() {
    // get the message text
    QString text = "REPORTER " + transmitName + "\n";

    // create and send the message itself
    tc->sendJMRIClientMessage(new JMRIClientMessage(text), (JMRIClientListener*)this);
}

// to listen for status changes from JMRIClient system
//@Override
/*public*/ void JMRIClientReporter::reply(JMRIClientReply* m) {
    QString message = m->toString();
    log->debug(tr("Message Received: ") + m->toString());
    log->debug("length " + message.length());
    if (!message.contains(transmitName + " ") &&
        !message.contains(transmitName + "\n") &&
        !message.contains(transmitName + "\r") ) {
        return; // not for us
    } else {
        QString text = "REPORTER " + transmitName + "\n";
        if (message != (text)) {
            QString report = message.mid(text.length());
            log->debug("setting report to " + report);
            setReport(report);  // this is an update of the report.
        } else {
            log->debug("setting report to null");
            setReport(QVariant()); // this is an update, but it is just
            // telling us the transient current
            // report is no longer valid.
        }
    }
}

//@Override
/*public*/ void JMRIClientReporter::message(JMRIClientMessage* m) {
}


//@Override
/*public*/ void JMRIClientReporter::setState(int s) {
    state = s;
}

//@Override
/*public*/ int JMRIClientReporter::getState() {
    return state;
}

/*private*/ /*final*/ /*static*/ Logger* JMRIClientReporter::log = LoggerFactory::getLogger("JMRIClientReporter");
