#include "abstractsensorserver.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "jmriexception.h"

/**
 * Abstract interface between the a JMRI sensor and a network connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
//abstract public class AbstractSensorServer {


/*public*/ AbstractSensorServer::AbstractSensorServer(QObject *parent) : QObject(parent) {
    sensors = QMap<QString, SSSensorListener*>();
}

/*
 * Protocol Specific Abstract Functions
 */
//abstract public void sendStatus(QString sensor, int Status) /*throw (IOException)*/;

//abstract public void sendErrorStatus(QString sensor) throws IOException;

//abstract public void parseStatus(String statusString) throws JmriException, IOException;

/*synchronized*/ /*protected*/ void AbstractSensorServer::addSensorToList(QString sensorName) {
    if (!sensors.contains(sensorName)) {
        Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
        if(s!=nullptr) {
           SSSensorListener* sl = new SSSensorListener(sensorName, this);
           //s.addPropertyChangeListener(sl);
           connect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), sl, SLOT(propertyChange(PropertyChangeEvent*)));
           sensors.insert(sensorName, sl );
        }
    }
}

/*synchronized*/ /*protected*/ void AbstractSensorServer::removeSensorFromList(QString sensorName) {
    if (sensors.contains(sensorName)) {
        Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
        if(s!=nullptr) {
           //s.removePropertyChangeListener(sensors.get(sensorName));
         disconnect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)));
           sensors.remove(sensorName);
        }
    }
}

/*public*/ Sensor* AbstractSensorServer::initSensor(QString sensorName)  {
    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    this->addSensorToList(sensorName);
    return sensor;
}

/*public*/ void AbstractSensorServer::setSensorActive(QString sensorName) {
    Sensor* sensor;
    // load address from sensorAddrTextField
    try {
        addSensorToList(sensorName);
        sensor = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
        if (sensor == nullptr) {
            log->error(tr("Sensor %1 is not available").arg(sensorName));
        } else {
            if (sensor->getKnownState() != Sensor::ACTIVE) {
                // set state to ACTIVE
                log->debug(tr("changing sensor '%1' to Active (%2->%3)").arg(sensorName).arg(sensor->getKnownState()).arg(Sensor::ACTIVE));
                sensor->setKnownState(Sensor::ACTIVE);
            } else {
                // just notify the client.
                log->debug(tr("not changing sensor '%1', already Active (%1)").arg(sensorName).arg(sensor->getKnownState()));
                try {
                    sendStatus(sensorName, Sensor::ACTIVE);
                } catch (IOException* ie) {
                    log->error("Error Sending Status");
                }
            }
        }
    } catch (JmriException* ex) {
        log->error("set sensor active", ex);
    }
}

/*public*/ void AbstractSensorServer::dispose() {
    //for (Map.Entry<String, SensorListener> sensor : this.sensors.entrySet())
 QMapIterator<QString, SSSensorListener*> sensor(this->sensors);
 while (sensor.hasNext())
    {
  sensor.next();
        Sensor* s = InstanceManager::sensorManagerInstance()->getSensor(sensor.key());
        if(s!=nullptr) {
           //s.removePropertyChangeListener(sensor.getValue());
         disconnect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), sensor.value(), SLOT(propertyChange(PropertyChangeEvent*)));
        }
    }
    this->sensors.clear();
}

/*public*/ void AbstractSensorServer::setSensorInactive(QString sensorName) {
    Sensor* sensor;
    try {
        addSensorToList(sensorName);
        sensor = InstanceManager::sensorManagerInstance()->getSensor(sensorName);

        if (sensor == nullptr) {
            log->error("Sensor " + sensorName
                    + " is not available");
        } else {
            if (sensor->getKnownState() != Sensor::INACTIVE) {
                // set state to INACTIVE
                log->debug(tr("changing sensor '%1' to InActive (%2->%3)").arg(sensorName).arg(sensor->getKnownState()).arg(Sensor::INACTIVE));
                sensor->setKnownState(Sensor::INACTIVE);
            } else {
                // just notify the client.
                log->debug(tr("not changing sensor '%1', already InActive (%2)").arg(sensorName).arg(sensor->getKnownState()));
                try {
                    sendStatus(sensorName, Sensor::INACTIVE);
                } catch (IOException* ie) {
                    log->error("Error Sending Status");
                }
            }
        }
    } catch (JmriException* ex) {
        log->error("set sensor inactive" + ex->getMessage());
    }
}

//    class SensorListener implements PropertyChangeListener {

    SSSensorListener::SSSensorListener(QString sensorName, AbstractSensorServer *abstractSensorServer) {
        name = sensorName;
        sensor = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
        this->abstractSensorServer = abstractSensorServer;
    }

    // update state as state of sensor changes
    //@Override
    /*public*/ void SSSensorListener::propertyChange(PropertyChangeEvent* e) {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName()==("KnownState")) {
            int now = ( e->getNewValue()).toInt();
            try {
                abstractSensorServer->sendStatus(name, now);
            } catch (IOException* ie) {
                abstractSensorServer->log->debug("Error Sending Status");
                // if we get an error, de-register
                sensor->removePropertyChangeListener(this);
                abstractSensorServer->removeSensorFromList(name);
            }
        }
    }
//        String name = null;
//        Sensor sensor = null;
//    }
    /*private*/ /*final*/ /*static*/ Logger* AbstractSensorServer::log = LoggerFactory::getLogger("AbstractSensorServer");
