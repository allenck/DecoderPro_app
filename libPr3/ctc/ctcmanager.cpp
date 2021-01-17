#include "ctcmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "configuremanager.h"
#include "programproperties.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"
#include "turnoutmanager.h"
#include "blockmanager.h"
#include "vptr.h"
#include "ctcserialdata.h"

/**
 * Start the CtcManager and register with the instance and configuration managers.
 * <ul>
 *   <li>Create/provide the ProgramProperties instance</li>
 *   <li>Create/provide the CTCSerialData instance</li>
 *   <li>Provide the OtherData instance</li>
 *   <li>Provide hash maps of beans used by CTC</li>
 *   <li>Veto deletes for beans used by CTC</li>
 * </ul>
 *
 * @author Dave Sand Copyright (C) 2020
 */
// /*public*/ class CtcManager implements InstanceManagerAutoDefault, java.beans.VetoableChangeListener {



/*public*/ CtcManager::CtcManager(QObject *parent) : QObject(parent){
    InstanceManager::setDefault("CtcManager", this);
    //InstanceManager.getOptionalDefault(ConfigureManager.class).ifPresent(cm -> {
    ConfigureManager* cm = (ConfigureManager*)InstanceManager::getDefault("ConfigureManager");
    if(cm)
        cm->registerConfig(this, getXMLOrder());
//        });
    ((SensorManager*)InstanceManager::getDefault("SensorManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    ((BlockManager*)InstanceManager::getDefault("BlockManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    log->debug("CtcManager started");
}

/*public*/ ProgramProperties* CtcManager::getProgramProperties() {
    if (programProperties == nullptr) {
        programProperties = new ProgramProperties();
    }
    return programProperties;
}

/*public*/ ProgramProperties* CtcManager::newProgramProperties() {
    programProperties = new ProgramProperties();
    return programProperties;
}

/*public*/ CTCSerialData* CtcManager::getCTCSerialData() {
    if (ctcSerialData == nullptr) {
        ctcSerialData = new CTCSerialData();
    }
    return ctcSerialData;
}

/*public*/ CTCSerialData* CtcManager::newCTCSerialData() {
    ctcSerialData = new CTCSerialData();

    nbhSensors.clear();
    nbhSignals.clear();
    nbhTurnouts.clear();
    blocks.clear();

    return ctcSerialData;
}

/*public*/ OtherData* CtcManager::getOtherData() {
    if (ctcSerialData == nullptr) {
        ctcSerialData = getCTCSerialData();
    }
    return ctcSerialData->getOtherData();
}

/*public*/ NBHSensor* CtcManager::getNBHSensor(QString name) {
    // check for new names
    return nbhSensors.value(name);
}

/*public*/ void CtcManager::putNBHSensor(QString name, NBHSensor* nbh) {
    //NBHSensor* oldSensor = nbhSensors.insert(name, nbh);
    NBHSensor* oldSensor = nbhSensors.value(name);
    nbhSensors.insert(name, nbh);
    log->debug(tr("sensor put = %1 -- %2").arg(name).arg(nbh->getHandleName()));
    if (oldSensor != nullptr) {
        log->debug(tr("---- duplicate sensor: %1 -- %2").arg(name).arg(nbh->getHandleName()));
        // cleanup after replace an existing sensor may have a different name
    }
}

/*public*/ NBHSignal* CtcManager::getNBHSignal(QString name) {
    // check for new names
    return nbhSignals.value(name);
}

/*public*/ void CtcManager::putNBHSignal(QString name, NBHSignal* nbh) {
    //NBHSignal* oldSignal = nbhSignals.insert(name, nbh);
    NBHSignal* oldSignal = nbhSignals.value(name);
    nbhSignals.insert(name, nbh);
    log->debug(tr("signal put = %1 -- %2").arg(name).arg(nbh->getDisplayName()));
    if (oldSignal != nullptr) {
        log->debug(tr("---- duplicate signal: %1 -- %2").arg(name).arg(nbh->getDisplayName()));
        // cleanup after replace
    }
}

/*public*/ NBHTurnout* CtcManager::getNBHTurnout(QString name) {
    // check for new names
    return nbhTurnouts.value(name);
}

/*public*/ void CtcManager::putNBHTurnout(QString name, NBHTurnout* nbh) {
    //NBHTurnout* oldTurnout = nbhTurnouts.insert(name, nbh);
     NBHTurnout* oldTurnout = nbhTurnouts.value(name);
     nbhTurnouts.insert(name, nbh);
    log->debug(tr("turnout put = %1 -- %2").arg(name).arg(nbh->getBean()->getDisplayName()));
    if (oldTurnout != nullptr) {
        log->debug(tr("---- duplicate turnout: %1 -- %2").arg(name).arg(nbh->getBean()->getDisplayName()));
        // cleanup after replace
    }
}

/*public*/ NamedBeanHandle<Block*>* CtcManager::getBlock(QString name) {
    // check for new names
    return blocks.value(name);
}

/*public*/ void CtcManager::putBlock(QString name, NamedBeanHandle<Block*>* block) {
//        NamedBeanHandle<Block*>* oldBlock = blocks.insert(name, block);
    NamedBeanHandle<Block*>* oldBlock = blocks.value(name);
    blocks.insert(name, block);
    log->debug(tr("block put = %1 -- %2").arg(name).arg(block->getName()));
    if (oldBlock != nullptr) {
        log->debug(tr("---- duplicate block: %1 -- %2").arg(name).arg(block->getName()));
        // cleanup after replace
    }
}

/*public*/ int CtcManager::getXMLOrder() {
    return Manager::CTCDATA;
}

/*public*/ void CtcManager::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) {
    NamedBean* nb =  VPtr<NamedBean>::asPtr(evt->getOldValue());
    bool found = false;
    if ("CanDelete" == (evt->getPropertyName())) { // NOI18N

        if (qobject_cast<Sensor*>(nb)) {
            for (NBHSensor* sensor : nbhSensors.values()) {
                if (nb->equals(sensor->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (qobject_cast<SignalHead*>(nb) || qobject_cast<SignalMast*>(nb)) {
            for (NBHSignal* signal : nbhSignals.values()) {
                if (nb->equals(signal->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (qobject_cast<Turnout*>(nb)) {
            for (NBHTurnout* turnout : nbhTurnouts.values()) {
                if (nb->equals(turnout->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (qobject_cast<Block*>(nb)) {
            for (NamedBeanHandle<Block*>* block : blocks.values()) {
                if (nb->equals(block->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (found) {
            PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());  // NOI18N
            throw PropertyVetoException(tr("%1 is in use by CTC").arg(nb->getBeanType()), e);   // NOI18N
        }
    }
}

/*private*/ /*static*/ /*final*/ Logger* CtcManager::log = LoggerFactory::getLogger("CtcManager");
