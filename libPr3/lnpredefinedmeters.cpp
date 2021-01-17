#include "lnpredefinedmeters.h"
#include "loggerfactory.h"
#include "slotmanager.h"
#include "lntrafficcontroller.h"
#include "lnmeterinittask.h"
#include "instancemanager.h"
#include "metermanager.h"
#include "meter.h"
#include "lniplimplementation.h"
#include "defaultmeter.h"
#include "proxymetermanager.h"
/**
 * Provide access to current and voltage meter from some LocoNet command stations
 *
 * @author Steve G           Copyright (C) 2019
 * @author Bob Jacobsen      Copyright (C) 2019
 * @author Egbert Boerse     Copyright (C) 2019
 * @author Daniel Bergqvist  Copyright (C) 2020
 * @author B. Milhaupt       Copyright (C) 2020
 */
// /*public*/ class LnPredefinedMeters implements LocoNetListener {


    /**
     * Create a LnPredefinedMeters object
     *
     * @param scm  connection memo
     */
    /*public*/ LnPredefinedMeters::LnPredefinedMeters(LocoNetSystemConnectionMemo* scm, QObject *parent) {
        this->sm = scm->getSlotManager();
        this->tc = scm->getLnTrafficController();

//        updateTask = new MeterUpdateTask(LnConstants::METER_INTERVAL_MS) {
//            @Override
//            /*public*/ void requestUpdateFromLayout() {
//                sm->sendReadSlot(249);
//            }
//        };
        updateTask = new MeterUpdateTask01(LnConstants::METER_INTERVAL_MS, this);

        tc->addLocoNetListener(~0, this);
        connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));

        updateTask->initTimer();

        // a work-around to ensure that the LocoNet transmit path is established
        // before making an initial query-mode request
        initializationTask = new LnMeterInitTask(sm->tc, 85, this);
        initializationTask->initTimer();
        initializationTask->enable();
    }

    //@Override
    /*public*/ void LnPredefinedMeters::message(LocoNetMessage* msg) {
        if (msg->getNumDataElements() != 21
                || msg->getOpCode() != LnConstants::OPC_EXP_RD_SL_DATA
                || msg->getElement(1) != 21
                || msg->getElement(2) != 1
                || msg->getElement(3) != 0x79) {
            return;
        }
        int srcDeviceType = msg->getElement(16);
        if ((srcDeviceType == LnConstants::RE_IPL_DIGITRAX_HOST_BXP88)
            || (srcDeviceType == LnConstants::RE_IPL_DIGITRAX_HOST_LNWI)
            || (srcDeviceType == LnConstants::RE_IPL_DIGITRAX_HOST_BXPA1)) {
            // these devices support Query Mode but always return 0s for
            // voltage/current data
            return;
        }

        float valAmps = msg->getElement(6)/10.0f;
        float valVolts = msg->getElement(4)*2.0f/10.0f;

        int srcSerNum = msg->getElement(18)+128*msg->getElement(19);

        QString voltSysName = createSystemName(srcDeviceType, srcSerNum, "Voltage"); // NOI18N
        MeterManager* mm = ((MeterManager*)InstanceManager::getDefault("MeterManager"));
//        ((AbstractProxyMeterManager*)mm)->createSystemManager("L");
        Meter* m = (DefaultMeter*)((AbstractMeterManager*)mm)->getBySystemName(voltSysName);
        updateAddMeter(m, voltSysName, valVolts, true);

        QString ampsSysName = createSystemName(srcDeviceType, srcSerNum, "InputCurrent"); // NOI18N
        m = (DefaultMeter*)((AbstractMeterManager*)InstanceManager::getDefault("MeterManager"))->getBySystemName(ampsSysName);
        updateAddMeter(m, ampsSysName, valAmps, false);
    }

    /*public*/ void LnPredefinedMeters::dispose() {
        for (NamedBean* nb: ((MeterManager*)InstanceManager::getDefault("MeterManager"))->getNamedBeanSet()) {
         Meter* m = (Meter*)nb;
            if (((DefaultMeter*)m)->getSystemName().startsWith(sm->getSystemPrefix()+"V")) { // NOI18N
                updateTask->disable(m);
                ((MeterManager*)InstanceManager::getDefault("MeterManager"))->deregister(nb);
                updateTask->dispose(m);
            }
        }
    }

    /*public*/ void LnPredefinedMeters::requestUpdateFromLayout() {
        log->debug("sending request for voltmeter/ammeter information");
        sm->sendReadSlot(249);
    }

    /*private*/ /*final*/ QString LnPredefinedMeters::createSystemName(int device, int sn, QString typeString) {
        QString devName = LnIPLImplementation::getDeviceName(0, device,0,0);
        if (devName.isNull()) {
            devName="["+QString::number(device)+"]"; // NOI18N
        }
        return sm->getSystemPrefix()+"V"+ devName + "(s/n"+QString::number(sn)+")"+typeString; // NOI18N
    }

    /*private*/ void LnPredefinedMeters::updateAddMeter(Meter* m, QString sysName, float value, bool typeVolt ) {
        if (m == nullptr) {
            DefaultMeter* newMeter;
            if (typeVolt) {
                // voltMeter not (yet) registered
                newMeter = new /*DefaultMeter::*/DefaultVoltageMeter(sysName,
                    Meter::Unit::NoPrefix, 0, 25.4, 0.2, updateTask);
            } else {
                            // ammeter not (yet) registered
                newMeter = new /*DefaultMeter::*/DefaultCurrentMeter(sysName,
                    Meter::Unit::NoPrefix, 0, 12.7, 0.1, updateTask);
            }
            try {
                newMeter->setCommandedAnalogValue(value);
            } catch (JmriException e) {
                log->debug(tr("Exception setting %1Meter %2 to value %3: %4").arg(
                        (typeVolt?"volt":"current")).arg( // NOI18N
                        sysName).arg(value).arg(e.getMessage()));
            }
            ((MeterManager*)InstanceManager::getDefault("MeterManager"))->Register(newMeter);
            log->debug(tr("Added new %1Meter %2 with value %3").arg(
                        (typeVolt?"volt":"current")).arg( // NOI18N
                    sysName).arg(value));
        } else {
            try {
             log->debug(tr("meter %1").arg(((DefaultMeter*)m->self())->objectName()));
             ((AnalogIO*)m->self())->setCommandedAnalogValue(value);
            } catch (JmriException e) {
                log->debug(tr("Exception setting %1Meter %2 to value %3: %4").arg(
                        (typeVolt?"volt":"current")).arg( // NOI18N
                        sysName).arg(value).arg(e.getLocalizedMessage()));
            }
            log->debug(tr("Updating currentMeter %1 with value %2").arg(
                    sysName).arg(value));
       }
    }

    /*private*/ /*final*/ /*static*/ Logger* LnPredefinedMeters::log = LoggerFactory::getLogger("LnPredefinedMeters");
