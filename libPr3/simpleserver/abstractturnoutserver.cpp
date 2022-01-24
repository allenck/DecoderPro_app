#include "abstractturnoutserver.h"
#include "loggerfactory.h"
#include "turnoutmanager.h"
#include "turnout.h"
#include "instancemanager.h"


/**
 * Abstract interface between the a JMRI turnout and a network connection
 *
 * @author Paul Bender Copyright (C) 2010-2013
 * @author Randall Wood Copyright (C) 2013
 */
//abstract /*public*/ class AbstractTurnoutServer {

/*private*/ /*final*/ /*static*/ Logger* AbstractTurnoutServer::log = LoggerFactory::getLogger("AbstractTurnoutServer");

/*public*/ AbstractTurnoutServer::AbstractTurnoutServer(QObject *parent) : QObject(parent) {
    turnouts = QMap<QString, SSTurnoutListener*>();
}

/*
 * Protocol Specific Abstract Functions
 */
//abstract /*public*/ void sendStatus(String turnoutName, int Status) throws IOException;

//abstract /*public*/ void sendErrorStatus(String turnoutName) throws IOException;

//abstract /*public*/ void parseStatus(String statusString) throws JmriException, IOException;

/*synchronized*/ /*protected*/ void AbstractTurnoutServer::addTurnoutToList(QString turnoutName) {
    if (!turnouts.contains(turnoutName)) {
        Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        if(t!=nullptr) {
           SSTurnoutListener* tl = new SSTurnoutListener(turnoutName, this);
           //t.addPropertyChangeListener(tl);
           connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), tl, SLOT(propertyChange(PropertyChangeEvent*)));
           turnouts.insert(turnoutName, tl);
        }
    }
}

/*synchronized*/ /*protected*/ void AbstractTurnoutServer::removeTurnoutFromList(QString turnoutName) {
    if (turnouts.contains(turnoutName)) {
        Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        if(t!=nullptr) {
           //t.removePropertyChangeListener(turnouts.get(turnoutName));
         disconnect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)));
           turnouts.remove(turnoutName);
        }
    }
}

/*public*/ Turnout* AbstractTurnoutServer::initTurnout(QString turnoutName) throw (IllegalArgumentException) {
    Turnout* turnout = InstanceManager::turnoutManagerInstance()->provideTurnout(turnoutName);
    this->addTurnoutToList(turnoutName);
    return turnout;
}

/*public*/ void AbstractTurnoutServer::closeTurnout(QString turnoutName) {
    // load address from switchAddrTextField
    try {
        if (!turnouts.contains(turnoutName)) {
            // enforce that initTurnout must be called before moving a
            // turnout
            sendErrorStatus(turnoutName);
            return;
        }
        Turnout* turnout = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        if (turnout == nullptr) {
            log->error(tr("Turnout %1 is not available").arg(turnoutName));
        } else {
            log->debug("about to command CLOSED");
            // and set commanded state to CLOSED
            turnout->setCommandedState(Turnout::CLOSED);
        }
    } catch (IOException* ex) {
        log->error("Error closing turnout", ex);
    }
}

/*public*/ void AbstractTurnoutServer::throwTurnout(QString turnoutName) {
    // load address from switchAddrTextField
    try {
        Turnout* turnout = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        if (!turnouts.contains(turnoutName)) {
            // enforce that initTurnout must be called before moving a
            // turnout
            sendErrorStatus(turnoutName);
            return;
        }

        if (turnout == nullptr) {
            log->error(tr("Turnout %1 is not available").arg(turnoutName));
        } else {
            if (log->isDebugEnabled()) {
                log->debug("about to command THROWN");
            }
            // and set commanded state to THROWN
            turnout->setCommandedState(Turnout::THROWN);
        }
    } catch (IOException* ex) {
        log->error("Error throwing turnout", ex);
    }
}

/*public*/ void AbstractTurnoutServer::dispose() {
    //for (Map.Entry<String, TurnoutListener> turnout : this->turnouts.entrySet())
    QMapIterator<QString, SSTurnoutListener*> turnout(this->turnouts);
    while(turnout.hasNext())
    {
     turnout.next();
        Turnout* t = InstanceManager::turnoutManagerInstance()->getTurnout(turnout.key());
        if(t!=nullptr) {
           //t.removePropertyChangeListener(turnout.value());
           disconnect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)));
        }
    }
    this->turnouts.clear();
}

/*protected*/ SSTurnoutListener* AbstractTurnoutServer::getListener(QString turnoutName) {
    if (!turnouts.contains(turnoutName)) {
       return new SSTurnoutListener(turnoutName, this);
    } else {
       return turnouts.value(turnoutName);
    }
}

//    /*protected*/ class TurnoutListener implements PropertyChangeListener {

    /*protected*/ SSTurnoutListener::SSTurnoutListener(QString turnoutName,AbstractTurnoutServer* abstractTurnoutServer) {
        name = turnoutName;
        turnout = InstanceManager::turnoutManagerInstance()->getTurnout(turnoutName);
        this->abstractTurnoutServer = abstractTurnoutServer;
    }

    // update state as state of turnout changes
    //@Override
    /*public*/ void SSTurnoutListener::propertyChange(PropertyChangeEvent* e) {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName() == ("KnownState")) {
            int now = ( e->getNewValue()).toInt();
            try {
                abstractTurnoutServer->sendStatus(name, now);
            } catch (IOException* ie) {
                abstractTurnoutServer->log->debug("Error Sending Status");
                // if we get an error, de-register
                //turnout.removePropertyChangeListener(this);
                disconnect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                abstractTurnoutServer->removeTurnoutFromList(name);
            }
        }
    }
//    String name = null;
//    Turnout* turnout = null;
//}
