#include "abstractsignalheadserver.h"
#include "loggerfactory.h"

/**
 * Abstract interface between a JMRI signal head and a network connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
//abstract /*public*/ class AbstractSignalHeadServer {

/*private*/ /*static*/ /*final*/ Logger* AbstractSignalHeadServer::log = LoggerFactory::getLogger("AbstractSignalHeadServer");

/*public*/ AbstractSignalHeadServer::AbstractSignalHeadServer(QObject *parent) : QObject(parent) {
    signalHeads = QMap<QString, ASHSignalHeadListener*>();
}

/*
 * Protocol Specific Abstract Functions
 */
//abstract /*public*/ void sendStatus(String signalHead, int Status) throws IOException;

//abstract /*public*/ void sendErrorStatus(String signalHead) throws IOException;

//abstract /*public*/ void parseStatus(String statusString) throws JmriException, IOException, JsonException;

/*synchronized*/ /*protected*/ void AbstractSignalHeadServer::addSignalHeadToList(QString signalHeadName) {
    if (!signalHeads.contains(signalHeadName)) {
        SignalHead* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if(sh!=nullptr) {
           ASHSignalHeadListener* shl = new ASHSignalHeadListener(signalHeadName, this);
//           sh.addPropertyChangeListener(shl);
           connect(sh->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
           signalHeads.insert(signalHeadName, shl );
           log->debug(tr("Added listener to signalHead %1").arg(signalHeadName));
        }
    }
}

/*synchronized*/ /*protected*/ void AbstractSignalHeadServer::removeSignalHeadFromList(QString signalHeadName) {
    if (signalHeads.contains(signalHeadName)) {
        SignalHead* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if(sh!=nullptr) {
           //sh.removePropertyChangeListener(signalHeads.get(signalHeadName));
         disconnect(sh->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
           signalHeads.remove(signalHeadName);
        }
    }
}

/*public*/ void AbstractSignalHeadServer::setSignalHeadAppearance(QString signalHeadName, QString signalHeadState) {
    this->setSignalHeadAppearance(signalHeadName, this->appearanceForName(signalHeadState));
}

/*protected*/ void AbstractSignalHeadServer::setSignalHeadAppearance(QString signalHeadName, int signalHeadState) {
    SignalHead* signalHead;
    try {
        addSignalHeadToList(signalHeadName);
        signalHead = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
        if (signalHead == nullptr) {
            // only log, since this may be from a remote system
            log->error("SignalHead " + signalHeadName + " is not available.");
        } else {
            if (signalHead->getAppearance() != signalHeadState || signalHead->getHeld()) {
                if (signalHeadState == SignalHead::HELD) {
                    signalHead->setHeld(true);
                } else {
                    if (signalHead->getHeld()) signalHead->setHeld(false);
                    signalHead->setAppearance(signalHeadState);
                }
            } else {
                try {
                    sendStatus(signalHeadName, signalHeadState);
                } catch (IOException ex) {
                    log->error("Error sending appearance", ex);
                }
            }
        }
    } catch (Exception ex) {
        log->error("Exception setting signalHead " + signalHeadName + " appearance:", ex);
    }
}

/*protected*/ QString AbstractSignalHeadServer::nameForAppearance(int appearance) {
    switch (appearance) {
        case SignalHead::DARK:
            return "DARK";
        case SignalHead::RED:
            return "RED";
        case SignalHead::FLASHRED:
            return "FLASHRED";
        case SignalHead::YELLOW:
            return "YELLOW";
        case SignalHead::FLASHYELLOW:
            return "FLASHYELLOW";
        case SignalHead::GREEN:
            return "GREEN";
        case SignalHead::FLASHGREEN:
            return "FLASHGREEN";
        case SignalHead::LUNAR:
            return "LUNAR";
        case SignalHead::FLASHLUNAR:
            return "FLASHLUNAR";
        case SignalHead::HELD:
            return "HELD";
        default:
            return "UNKNOWN";
    }
}

/*protected*/ int AbstractSignalHeadServer::appearanceForName(QString name) {
    if (name == ("DARK")) {
        return SignalHead::DARK;
    } else if (name == ("RED")) {
        return SignalHead::RED;
    } else if (name == ("FLASHRED")) {
        return SignalHead::FLASHRED;
    } else if (name == ("YELLOW")) {
        return SignalHead::YELLOW;
    } else if (name == ("FLASHYELLOW")) {
        return SignalHead::FLASHYELLOW;
    } else if (name == ("GREEN")) {
        return SignalHead::GREEN;
    } else if (name == ("FLASHGREEN")) {
        return SignalHead::FLASHGREEN;
    } else if (name == ("LUNAR")) {
        return SignalHead::LUNAR;
    } else if (name == ("FLASHLUNARDARK")) {
        return SignalHead::DARK;
    } else if (name == ("FLASHLUNAR")) {
        return SignalHead::FLASHLUNAR;
    } else {
        return SignalHead::DARK;
    }
}

/*public*/ void AbstractSignalHeadServer::dispose() {
    //for (Map.Entry<String, SignalHeadListener> signalHead : this.signalHeads.entrySet())
    QMapIterator<QString, ASHSignalHeadListener*> signalHead(signalHeads);
    while(signalHead.hasNext())
    {
     signalHead.next();
        SignalHead* sh = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead.key());
        if(sh != nullptr) {
           //sh.removePropertyChangeListener(SignalHead::getValue());
         disconnect(sh->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
    }
    this->signalHeads.clear();
}

