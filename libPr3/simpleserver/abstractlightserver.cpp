#include "abstractlightserver.h"
#include "loggerfactory.h"
/**
 * Abstract interface between the a JMRI Light and a network connection
 *
 * @author Paul Bender Copyright (C) 2010
 * @author Randall Wood Copyright (C) 2013, 2014
 */
//abstract /*public*/ class AbstractLightServer {

/*private*/ /*final*/ /*static*/ Logger* AbstractLightServer::log = LoggerFactory::getLogger("AbstractLightServer");

/*public*/ AbstractLightServer::AbstractLightServer(QObject *parent) : QObject(parent) {
    lights = QMap<QString, ALSLightListener*>();
}

/*
 * Protocol Specific Abstract Functions
 */
//abstract /*public*/ void sendStatus(String lightName, int Status) throws IOException;

//abstract /*public*/ void sendErrorStatus(String lightName) throws IOException;

//abstract /*public*/ void parseStatus(String statusString) throws JmriException, IOException;

/*synchronized*/ /*protected*/ void AbstractLightServer::addLightToList(QString lightName) {
    if (!lights.contains(lightName)) {
        Light* li = InstanceManager::lightManagerInstance()->getLight(lightName);
        if (li != nullptr) {
            lights.insert(lightName, new ALSLightListener(lightName, this));
            //li.addPropertyChangeListener(lights.get(lightName));
            connect(li->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        } else {
            log->error(tr("Failed to get light %1").arg(lightName));
        }
    }
}

/*synchronized*/ /*protected*/ void AbstractLightServer::removeLightFromList(QString lightName) {
    if (lights.contains(lightName)) {
        Light* li = InstanceManager::lightManagerInstance()->getLight(lightName);
        if (li != nullptr) {
            //li.removePropertyChangeListener(lights.get(lightName));
            disconnect(li->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            lights.remove(lightName);
        } else {
            log->error(tr("Failed to get light %1").arg(lightName));
        }
    }
}

/*public*/ Light* AbstractLightServer::initLight(QString lightName)  throw (IllegalArgumentException) {
    Light* light = InstanceManager::lightManagerInstance()->provideLight(lightName);
    this->addLightToList(lightName);
    return light;
}

/*public*/ void AbstractLightServer::lightOff(QString lightName) {
    Light* light;
    // load address from switchAddrTextField
    try {

        addLightToList(lightName);
        light = InstanceManager::lightManagerInstance()->getLight(lightName);
        if (light == nullptr) {
            log->error(tr("Light %1 is not available").arg(lightName));
        } else {
            log->debug("about to command OFF");
            // and set state to OFF
            light->setState(Light::OFF);
        }
    } catch (Exception ex) {
        log->error("light off", ex);
    }
}

/*public*/ void AbstractLightServer::lightOn(QString lightName) {
    Light* light;
    // load address from switchAddrTextField
    try {
        addLightToList(lightName);
        light = InstanceManager::lightManagerInstance()->getLight(lightName);

        if (light == nullptr) {
            log->error(tr("Light %1 is not available").arg(lightName));
        } else {
            log->debug("about to command ON");
            // and set state to ON
            light->setState(Light::ON);
        }
    } catch (Exception ex) {
        log->error("light on", ex);
    }
}

/*public*/ void AbstractLightServer::dispose() {
    //for (Map.Entry<String, LightListener> light : this.lights.entrySet())
 QMapIterator<QString, ALSLightListener*> light(lights);
 while(light.hasNext())
    {
  light.next();
        Light* li = InstanceManager::lightManagerInstance()->getLight(light.key());
        if (li != nullptr) {
            //li.removePropertyChangeListener(light.value());
         disconnect(li, SIGNAL(propertyChange(PropertyChangeEvent*)), light.value(), SLOT(propertyChange(PropertyChangeEvent*)));
        }
    }
    this->lights.clear();
}

