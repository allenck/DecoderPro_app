#include "meterframemanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "configuremanager.h"

/**
 * Default implementation of a MeterFrameManager.
 * This class is only used by jmri.jmrit.swing.meter.MeterFrame and
 * jmri.jmrit.swing.meter.configurexml.MeterFrameManagerXml so no need to store
 * it in the InstanceManager.
 *
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ class MeterFrameManager {

    /*private*/ /*final*/ /*static*/ Logger* MeterFrameManager::log = LoggerFactory::getLogger("MeterFrameManager");

    /*private*/ /*static*/ /*final*/ MeterFrameManager* MeterFrameManager::_instance = new MeterFrameManager();


    /**
     * Get the instance of MeterFrameManager.
     * @return the MeterFrameManager instance
     */
    //@CheckReturnValue
    /*public*/ /*static*/ MeterFrameManager* MeterFrameManager::getInstance() {
        return _instance;
    }

    /**
     * Create a new MeterFrameManager instance.
     */
    /*private*/ MeterFrameManager::MeterFrameManager(QObject* parent) : QObject(parent)
    {
        log->debug(tr("registerSelf for config of type %1").arg(/*getClass()*/metaObject()->className()));
        ConfigureManager* cm = nullptr;
        if(cm = ((ConfigureManager*)InstanceManager::getOptionalDefault("ConfigureManager"))){
            cm->registerConfig(this, getXMLOrder());
            log->debug(tr("registering for config of type %1").arg(/*getClass()*/metaObject()->className()));
        }//);
    }

    /**
     * Determine the order that types should be written when storing panel
     * files. Uses one of the constants defined in this class.
     * <p>
     * Yes, that's an overly-centralized methodology, but it works for now.
     *
     * @return write order for this Manager; larger is later.
     */
    //@CheckReturnValue
    /*public*/ int MeterFrameManager::getXMLOrder() {
        return Manager::METERFRAMES;
    }

    /*public*/ void MeterFrameManager::_register(/*@Nonnull*/ MeterFrame* frame) {
        _meterFrameList.insert(frame->getUUID(), frame);
    }

    /*public*/ void MeterFrameManager::deregister(/*@Nonnul*/ MeterFrame* frame) {
        _meterFrameList.remove(frame->getUUID());
    }

    /*public*/ MeterFrame* MeterFrameManager::getByUUID(/*@Nonnull*/ QUuid uuid) {
        return _meterFrameList.value(uuid);
    }

    /*public*/ QList<MeterFrame*> MeterFrameManager::getMeterFrames() {
        //return Collections.unmodifiableCollection(_meterFrameList.values());
     return _meterFrameList.values();
    }
