#ifndef ABSTRACTSIGNALHEADSERVER_H
#define ABSTRACTSIGNALHEADSERVER_H

#include <QObject>
#include "propertychangelistener.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "jsonexception.h"

class ASHSignalHeadListener;
class SignalHead;
class AbstractSignalHeadServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractSignalHeadServer(QObject *parent = nullptr);
 /*abstract*/ /*public*/ virtual void sendStatus(QString signalHead, int Status) throw (IOException) {}
 /*abstract*/ /*public*/ virtual void sendErrorStatus(QString signalHead) throw (IOException) {}
 /*abstract*/ /*public*/ virtual void parseStatus(QString statusString) throw (JmriException, IOException, JsonException);
 /*public*/ void setSignalHeadAppearance(QString signalHeadName, QString signalHeadState);
 /*public*/ void dispose();

signals:

public slots:

private:
 static Logger* log;
 /*private*/ /*final*/ QMap<QString, ASHSignalHeadListener*> signalHeads;
protected:
 /*synchronized*/ /*protected*/ void addSignalHeadToList(QString signalHeadName);
 /*synchronized*/ /*protected*/ void removeSignalHeadFromList(QString signalHeadName);
 /*protected*/ void setSignalHeadAppearance(QString signalHeadName, int signalHeadState);
 /*protected*/ QString nameForAppearance(int appearance);
 /*protected*/ int appearanceForName(QString name);
friend class ASHSignalHeadListener;
};

class ASHSignalHeadListener : public PropertyChangeListener {
Q_OBJECT
    QString name = "";
    SignalHead* signalHead = nullptr;
    AbstractSignalHeadServer* ashs;
public:
    ASHSignalHeadListener(QString signalHeadName, AbstractSignalHeadServer* ashs) {
        name = signalHeadName;
        signalHead = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHeadName);
    }
public slots:
    // update state as state of signalHead changes
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName() == ("Appearance") || e->getPropertyName() == ("Held")) {
            SignalHead* sh = (SignalHead*) e->getSource();
            int state = sh->getAppearance();
            if (sh->getHeld()) {
                state = SignalHead::HELD;
            }
            try {
                ashs->sendStatus(name, state);
            } catch (IOException ie) {
                // if we get an error, de-register
                if (ashs->log->isDebugEnabled()) {
                    ashs->log->debug("Unable to send status, removing listener from signalHead " + name);
                }
//                signalHead->removePropertyChangeListener(this);
                disconnect(signalHead->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                ashs->removeSignalHeadFromList(name);
            }
        }
    }
};
#endif // ABSTRACTSIGNALHEADSERVER_H
