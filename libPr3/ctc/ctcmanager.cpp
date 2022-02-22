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
#include "trafficlockingdata.h"
#include "codebuttonhandlerdata.h"
#include "otherdata.h"

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
    ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->VetoableChangeSupport::addVetoableChangeListener((VetoableChangeListener*)this);
    ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->addVetoableChangeListener((VetoableChangeListener*)this);
    ((BlockManager*)InstanceManager::getDefault("BlockManager"))->VetoableChangeSupport::addVetoableChangeListener((VetoableChangeListener*)this);
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

/*public*/ void CtcManager::vetoableChange(PropertyChangeEvent* evt) /*throw new (PropertyVetoException)*/ {
    NamedBean* nb =  VPtr<NamedBean>::asPtr(evt->getOldValue());
    bool found = false;
    if ("CanDelete" == (evt->getPropertyName())) { // NOI18N

        if (static_cast<Sensor*>(nb->self())) {
            for (NBHSensor* sensor : nbhSensors.values()) {
                if (nb->equals(sensor->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (static_cast<SignalHead*>(nb->self()) || static_cast<SignalMast*>(nb->self())) {
            for (NBHSignal* signal : nbhSignals.values()) {
                if (nb->equals(signal->getBean()->self())) {
                    found = true;
                    break;
                }
            }
        }

        if (static_cast<Turnout*>(nb->self())) {
            for (NBHTurnout* turnout : nbhTurnouts.values()) {
                if (nb->equals(turnout->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (static_cast<Block*>(nb->self())) {
            for (NamedBeanHandle<Block*>* block : blocks.values()) {
                if (nb->equals(block->getBean())) {
                    found = true;
                    break;
                }
            }
        }

        if (found) {
            PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());  // NOI18N
            throw new PropertyVetoException(tr("%1 is in use by CTC").arg(nb->getBeanType()), e);   // NOI18N
        }
    }
}

QString CtcManager::getVetoDetails(NamedBean* nb) {
    QString sb;// = new StringBuilder();
    sb.append(tr("%1 is in use by CTC").arg(nb->getBeanType()));  // NOI18N
    for (NamedBeanUsageReport* report : getUsageReport(nb)) {
        sb.append(tr("\n\t- %1").arg(report->usageData));    // NOI18N
    }
    return sb/*.toString()*/;
}

bool CtcManager::findNBHforBean(NamedBean* nb) {
    if (nb == nullptr) return false;
    bool found = false;
    foundSensor = nullptr;
    foundSignal = nullptr;
    foundTurnout = nullptr;
    foundBlock = nullptr;

    if (static_cast<Sensor*>(nb->self())) {
        for (NBHSensor* sensor : nbhSensors.values()) {
            if (nb->equals(sensor->getBean())) {
                foundSensor = sensor;
                found = true;
                break;
            }
        }
    }

    if (static_cast<SignalHead*>(nb->self()) || static_cast<SignalMast*>(nb->self())) {
        for (NBHSignal* signal : nbhSignals.values()) {
            if (nb->equals(signal->getBean()->self())) {
                foundSignal = signal;
                found = true;
                break;
            }
        }
    }

    if (static_cast<Turnout*>(nb->self())) {
        for (NBHTurnout* turnout : nbhTurnouts.values()) {
            if (nb->equals(turnout->getBean())) {
                foundTurnout = turnout;
                found = true;
                break;
            }
        }
    }

    if (static_cast<Block*>(nb->self())) {
        for (NamedBeanHandle<Block*>* block : blocks.values()) {
            if (nb->equals(block->getBean())) {
                foundBlock = block->getBean();
                found = true;
                break;
            }
        }
    }
    return found;
}

/*public*/ QList<NamedBeanUsageReport*> CtcManager::getUsageReport(NamedBean* bean) {
    usageReport = QList<NamedBeanUsageReport*>();
    if (findNBHforBean(bean)) {
        // Other data
        if (getOtherData()->_mFleetingToggleInternalSensor == (foundSensor) ||
                getOtherData()->_mCTCDebugSystemReloadInternalSensor ==(foundSensor) ||
                getOtherData()->_mCTCDebug_TrafficLockingRuleTriggeredDisplayInternalSensor ==(foundSensor)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedOther", tr("WhereUsedOther")));  // NOI18N
        }

        // O.S. Sections
        //getCTCSerialData().getCodeButtonHandlerDataArrayList().forEach(cbhd ->
        for(CodeButtonHandlerData* cbhd : getCTCSerialData()->getCodeButtonHandlerDataArrayList())
        {
            getCodeButtonHandleDataUsage(cbhd);
        }//);
    }
    return usageReport;
}

void CtcManager::getCodeButtonHandleDataUsage(CodeButtonHandlerData* cbhd) {
    QString osName = cbhd->myShortStringNoComma();

    // CB Sensors
    if (cbhd->_mCodeButtonInternalSensor == (foundSensor) ||
            cbhd->_mOSSectionOccupiedExternalSensor == (foundSensor) ||
            cbhd->_mOSSectionOccupiedExternalSensor2 == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "CB")));  // NOI18N
    }

    // SIDI Sensors
    if (cbhd->_mSIDI_LeftInternalSensor == (foundSensor) ||
            cbhd->_mSIDI_NormalInternalSensor == (foundSensor) ||
            cbhd->_mSIDI_RightInternalSensor == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "SIDI")));  // NOI18N
    }

    // SIDI Signals
    //cbhd->_mSIDI_LeftRightTrafficSignals.forEach(signal ->
    for(NBHSignal* signal : *cbhd->_mSIDI_LeftRightTrafficSignals)
    {
        if (signal == (foundSignal)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Signal").arg(osName, "SIDI")));  // NOI18N
        }
    }//);
    //cbhd->_mSIDI_RightLeftTrafficSignals.forEach(signal ->
    for(NBHSignal* signal : *cbhd->_mSIDI_RightLeftTrafficSignals)
    {
        if (signal ==(foundSignal)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Signal").arg(osName, "SIDI")));  // NOI18N
        }
    }//);

    // SIDL Sensors
    if (cbhd->_mSIDL_LeftInternalSensor == (foundSensor) ||
            cbhd->_mSIDL_NormalInternalSensor == (foundSensor) ||
            cbhd->_mSIDL_RightInternalSensor == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "SIDL")));  // NOI18N
    }

    // SWDI Sensors
    if (cbhd->_mSWDI_NormalInternalSensor == (foundSensor) ||
            cbhd->_mSWDI_ReversedInternalSensor == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "SWDI")));  // NOI18N
    }

    // SWDI Turnout
    if (cbhd->_mSWDI_ExternalTurnout == (foundTurnout)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Turnout").arg(osName, "SWDI")));  // NOI18N
    }

    // SWDL Sensor
    if (cbhd->_mSWDL_InternalSensor == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "SWDL")));  // NOI18N
    }

    callOnDataUsage(cbhd, osName);
    traffficLockingDataUsage(cbhd, osName);

    // TUL Sensors
    if (cbhd->_mTUL_DispatcherInternalSensorLockToggle == (foundSensor) ||
            cbhd->_mTUL_DispatcherInternalSensorUnlockedIndicator == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "TUL")));  // NOI18N
    }

    // TUL Turnouts
    if (cbhd->_mTUL_ExternalTurnout == (foundTurnout) ||
            cbhd->_mTUL_AdditionalExternalTurnout1 == (foundTurnout) ||
            cbhd->_mTUL_AdditionalExternalTurnout2 == (foundTurnout) ||
            cbhd->_mTUL_AdditionalExternalTurnout3 == (foundTurnout)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Turnout").arg(osName, "TUL")));  // NOI18N
    }

    // IL Signals
    //cbhd->_mIL_Signals.forEach(signal ->
    for(NBHSignal* signal : *cbhd->_mIL_Signals)
    {
        if (signal == (foundSignal)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Signal").arg(osName, "IL")));  // NOI18N
        }
    }//);
}

void CtcManager::callOnDataUsage(CodeButtonHandlerData* cbhd, QString osName) {
    // CO Sensor
    if (cbhd->_mCO_CallOnToggleInternalSensor == (foundSensor)) {
        usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "CO")));  // NOI18N
    }
    //cbhd->_mCO_GroupingsList.forEach(row ->
    for(CallOnData* row : *cbhd->_mCO_GroupingsList)
    {
        // Sensor
        if (row->_mCalledOnExternalSensor == (foundSensor)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "CO")));  // NOI18N
        }

        // Signal
        if (row->_mExternalSignal ==(foundSignal)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Signal").arg(osName, "CO")));  // NOI18N
        }

        // Block
        if (row->_mExternalBlock != nullptr && row->_mExternalBlock->getBean()->equals(foundBlock)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Block").arg(osName, "CO")));  // NOI18N
        }

        // Switch indicator sensors
        //row->_mSwitchIndicators.forEach(sw ->
        for(NBHSensor* sw : *row->_mSwitchIndicators)
        {
            if (sw == (foundSensor)) {
                usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "CO")));  // NOI18N
            }
        }//);
    }//);
}

void CtcManager::traffficLockingDataUsage(CodeButtonHandlerData* cbhd, QString osName) {
    //cbhd->_mTRL_LeftTrafficLockingRules.forEach(rule ->
    for(TrafficLockingData* rule : *cbhd->_mTRL_LeftTrafficLockingRules)
    {
        traffficLockingRuleDataUsage(rule, osName);
    }//);

    //cbhd->_mTRL_RightTrafficLockingRules.forEach(rule ->
    for(TrafficLockingData* rule : *cbhd->_mTRL_RightTrafficLockingRules)
    {
        traffficLockingRuleDataUsage(rule, osName);
    }//);
}

void CtcManager::traffficLockingRuleDataUsage(TrafficLockingData* rule, QString osName) {
    // Signal -- _mDestinationSignalOrComment
    if (foundSignal != nullptr) {
        if (rule->_mDestinationSignalOrComment == (foundSignal->getHandleName())) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Signal").arg(osName, "TRL")));  // NOI18N
        }
    }

    // Occupancy sensors
    for (NBHSensor* sensor : *rule->_mOccupancyExternalSensors) {
        if (sensor ==(foundSensor)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "TRL")));  // NOI18N
            break;
        }
    }

    // Optional sensors
    for (NBHSensor* sensor : *rule->_mOptionalExternalSensors) {
        if (sensor == (foundSensor)) {
            usageReport.append(new NamedBeanUsageReport("CtcWhereUsedCBHD", tr("%1 : %2 Sensor").arg(osName, "TRL")));  // NOI18N
            break;
        }
    }
}

/*private*/ /*static*/ /*final*/ Logger* CtcManager::log = LoggerFactory::getLogger("CtcManager");
