#ifndef ABSTRACTLIGHTSERVER_H
#define ABSTRACTLIGHTSERVER_H

#include <QObject>
#include "propertychangelistener.h"
#include "instancemanager.h"

class ALSLightListener;
class Logger;
class AbstractLightServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractLightServer(QObject *parent = nullptr);
 /*abstract*/ virtual /*public*/ void sendStatus(QString lightName, int Status) throw (IOException) {}
 /*abstract*/ virtual /*public*/ void sendErrorStatus(QString lightName) throw (IOException) {}
 /*abstract*/ virtual /*public*/ void parseStatus(QString statusString) throw (JmriException, IOException);
 /*public*/ Light* initLight(QString lightName)  throw (IllegalArgumentException);
 /*public*/ void lightOff(QString lightName);
 /*public*/ void lightOn(QString lightName);
 /*public*/ void dispose();

signals:

public slots:

private:
 static Logger* log;
 /*private*/ /*final*/ QMap<QString, ALSLightListener*> lights;


protected:
 /*synchronized*/ /*protected*/ void addLightToList(QString lightName);
 /*synchronized*/ /*protected*/ void removeLightFromList(QString lightName);

 friend class ALSLightListener;
};

class ALSLightListener : public PropertyChangeListener {
 AbstractLightServer* asl;
Q_OBJECT
public:
    ALSLightListener(QString lightName, AbstractLightServer* asl) {
     this->asl = asl;
        name = lightName;
        light = InstanceManager::lightManagerInstance()->getLight(lightName);
    }

    // update state as state of light changes
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName()==("KnownState")) {
            int now = ( e->getNewValue()).toInt();
            try {
                asl->sendStatus(name, now);
            } catch (IOException ie) {
                asl->log->debug("Error Sending Status");
                // if we get an error, de-register
//                light.removePropertyChangeListener(this);
                disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                asl->removeLightFromList(name);
            }
        }
    }
private:
    Light* light = nullptr;
    QString name = "";
};
#endif // ABSTRACTLIGHTSERVER_H
