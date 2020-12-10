#include "blockbosslogicprovider.h"
#include "instancemanagerautodefault.h"
#include "signalhead.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
#include "configuremanager.h"
#include "blockbosslogic.h"
#include "loggerfactory.h"
/**
 * Provider for {@link BlockBossLogic} objects
 *
 * @author Paul Bender Copyright (C) 2020
 */
// /*public*/ class BlockBossLogicProvider implements Disposable, InstanceManagerAutoDefault {


    /*public*/ BlockBossLogicProvider::BlockBossLogicProvider(QObject *parent) {
        signalHeadManager = (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager");
        headToBlockBossLogicMap = new QMap<SignalHead*,BlockBossLogic*>();
        ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
        if (cm != nullptr) {
            cm->registerConfig(this, Manager::BLOCKBOSS);
        }
    }

    /*public*/ BlockBossLogic* BlockBossLogicProvider::provide(/*@Nonnull*/ QString signalName) {
        SignalHead* signalHead = signalHeadManager->getSignalHead(signalName);
        if (signalHead == nullptr) {
            log->error(tr("SignalHead %1 doesn't exist, BlockBossLogic.getExisting(\"%2\") cannot continue").arg(signalName).arg(signalName));
            throw  IllegalArgumentException("Requested signal head doesn't exist");
        }
        return provide(signalHead);
    }

    /*public*/ BlockBossLogic* BlockBossLogicProvider::provide(/*@Nonnull*/ SignalHead* signalHead){
        if (signalHead == nullptr) {
            log->error("BlockBossLogic requested for null signal head.");
            throw  IllegalArgumentException("BlockBossLogic Requested for null signal head.");
        }
        //return headToBlockBossLogicMap->computeIfAbsent(signalHead,o -> new BlockBossLogic(o.getDisplayName()));
        if(!headToBlockBossLogicMap->contains(signalHead))
         return new BlockBossLogic(signalHead->getDisplayName());
        return nullptr;
    }

    /*public*/ void BlockBossLogicProvider::_register(BlockBossLogic* blockBossLogic){
        headToBlockBossLogicMap->insert(blockBossLogic->driveSignal->getBean(),blockBossLogic);
    }

    /*public*/ void BlockBossLogicProvider::remove(BlockBossLogic* blockBossLogic){
        headToBlockBossLogicMap->remove(blockBossLogic->driveSignal->getBean()/*,blockBossLogic*/);
    }

    /*public*/ QList<BlockBossLogic*> BlockBossLogicProvider::provideAll(){
        return headToBlockBossLogicMap->values();
    }

    /*public*/ void BlockBossLogicProvider::dispose(){
        for (BlockBossLogic* b : headToBlockBossLogicMap->values()) {
            b->stop();
        }
        headToBlockBossLogicMap->clear();
    }

    /*private*/ /*static*/ /*final*/ Logger* BlockBossLogicProvider::log = LoggerFactory::getLogger("BlockBossLogicProvider");
