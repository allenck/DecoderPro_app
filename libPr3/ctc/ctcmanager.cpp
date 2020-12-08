#include "ctcmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "configuremanager.h"

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
        ConfigureManager* cm = (ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager");
        if(cm)
            cm->registerConfig(this, getXMLOrder());
//        });
        ((SensorManager*)InstanceManager::getDefault("SensorManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
#if 0
        InstanceManager.getDefault(jmri.SignalHeadManager.class).addVetoableChangeListener(this);
        InstanceManager.getDefault(jmri.SignalMastManager.class).addVetoableChangeListener(this);
        InstanceManager.getDefault(jmri.TurnoutManager.class).addVetoableChangeListener(this);
        InstanceManager.getDefault(jmri.BlockManager.class).addVetoableChangeListener(this);
#endif
        log->debug("CtcManager started");
    }
#if 0
    /*public*/ ProgramProperties getProgramProperties() {
        if (programProperties == null) {
            programProperties = new ProgramProperties();
        }
        return programProperties;
    }

    /*public*/ ProgramProperties newProgramProperties() {
        programProperties = new ProgramProperties();
        return programProperties;
    }

    /*public*/ CTCSerialData getCTCSerialData() {
        if (ctcSerialData == null) {
            ctcSerialData = new CTCSerialData();
        }
        return ctcSerialData;
    }

    /*public*/ CTCSerialData newCTCSerialData() {
        ctcSerialData = new CTCSerialData();

        nbhSensors.clear();
        nbhSignals.clear();
        nbhTurnouts.clear();
        blocks.clear();

        return ctcSerialData;
    }

    /*public*/ OtherData getOtherData() {
        if (ctcSerialData == null) {
            ctcSerialData = getCTCSerialData();
        }
        return ctcSerialData.getOtherData();
    }

    /*public*/ NBHSensor getNBHSensor(String name) {
        // check for new names
        return nbhSensors.get(name);
    }
#endif
    /*public*/ void CtcManager::putNBHSensor(QString name, NBHSensor* nbh) {
#if 0
        NBHSensor* oldSensor = nbhSensors.insert(name, nbh);
        log->debug(tr("sensor put = %1 -- %2").arg(name).arg(nbh->getHandleName()));
        if (oldSensor != nullptr) {
            log->debug(tr("---- duplicate sensor: %1 -- %2").arg(name).arg(nbh->getHandleName()));
            // cleanup after replace an existing sensor may have a different name
        }
//         nbh.getBean().addPropertyChangeListener(this, nbh.getHandleName(), "somethng");
//                         _turnout.getBean().addPropertyChangeListener(this, getName(), "Route " + getDisplayName() + " Output Turnout");
#endif
    }
#if 0
    /*public*/ NBHSignal getNBHSignal(String name) {
        // check for new names
        return nbhSignals.get(name);
    }

    /*public*/ void putNBHSignal(String name, NBHSignal nbh) {
        NBHSignal oldSignal = nbhSignals.put(name, nbh);
        log.debug("signal put = {} -- {}", name, nbh);
        if (oldSignal != null) {
            log.debug("---- duplicate signal: {} -- {}", name, nbh);
            // cleanup after replace
        }
    }

    /*public*/ NBHTurnout getNBHTurnout(String name) {
        // check for new names
        return nbhTurnouts.get(name);
    }

    /*public*/ void putNBHTurnout(String name, NBHTurnout nbh) {
        NBHTurnout oldTurnout = nbhTurnouts.put(name, nbh);
        log.debug("turnout put = {} -- {}", name, nbh);
        if (oldTurnout != null) {
            log.debug("---- duplicate turnout: {} -- {}", name, nbh);
            // cleanup after replace
        }
    }

    /*public*/ NamedBeanHandle<Block> getBlock(String name) {
        // check for new names
        return blocks.get(name);
    }

    /*public*/ void putBlock(String name, NamedBeanHandle<Block> block) {
        NamedBeanHandle<Block> oldBlock = blocks.put(name, block);
        log.debug("block put = {} -- {}", name, block);
        if (oldBlock != null) {
            log.debug("---- duplicate block: {} -- {}", name, block);
            // cleanup after replace
        }
    }
#endif
    /*public*/ int CtcManager::getXMLOrder() {
        return Manager::CTCDATA;
    }
#if 0
    /*public*/ void vetoableChange(java.beans.PropertyChangeEvent evt) throws java.beans.PropertyVetoException {
        jmri.NamedBean nb = (jmri.NamedBean) evt.getOldValue();
        boolean found = false;
        if ("CanDelete".equals(evt.getPropertyName())) { // NOI18N

            if (nb instanceof jmri.Sensor) {
                for (NBHSensor sensor : nbhSensors.values()) {
                    if (nb.equals(sensor.getBean())) {
                        found = true;
                        break;
                    }
                }
            }

            if (nb instanceof jmri.SignalHead || nb instanceof jmri.SignalMast) {
                for (NBHSignal signal : nbhSignals.values()) {
                    if (nb.equals(signal.getBean())) {
                        found = true;
                        break;
                    }
                }
            }

            if (nb instanceof jmri.Turnout) {
                for (NBHTurnout turnout : nbhTurnouts.values()) {
                    if (nb.equals(turnout.getBean())) {
                        found = true;
                        break;
                    }
                }
            }

            if (nb instanceof Block) {
                for (NamedBeanHandle<Block> block : blocks.values()) {
                    if (nb.equals(block.getBean())) {
                        found = true;
                        break;
                    }
                }
            }

            if (found) {
                java.beans.PropertyChangeEvent e = new java.beans.PropertyChangeEvent(this, "DoNotDelete", null, null);  // NOI18N
                throw new java.beans.PropertyVetoException(Bundle.getMessage("CtcManagerDeleteVetoed", nb.getBeanType()), e);   // NOI18N
            }
        }
    }
#endif
    /*private*/ /*static*/ /*final*/ Logger* CtcManager::log = LoggerFactory::getLogger("CtcManager");
