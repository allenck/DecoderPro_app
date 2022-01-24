#include "abstractcabsignalmanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "blockmanager.h"

/**
 * Abstract implementation of the {@link jmri.CabSignalManager} interface.
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Paul Bender Copyright (C) 2019
 */
//abstract public class AbstractCabSignalManager implements CabSignalManager {



    /*public*/ AbstractCabSignalManager::AbstractCabSignalManager(QObject* parent) : QObject(){
         signalList = QHash<LocoAddress*, CabSignal*>();
         listListeners = QList<CabSignalListListener*>();
         mBlockListeners = QList<PropertyChangeListener*>();
    }

    /**
     * Find a CabSignal with the given address, and return it. If the CabSignal
     * doesn't exit, create it.
     *
     * @param address the cab signal for the address
     * @return an existing or new cab signal
     */
    //@Override
    /*public*/ CabSignal* AbstractCabSignalManager::getCabSignal(LocoAddress* address){
        if(!blockInit) {
           initBlocks();
        }
        bool contains = false;
        foreach (LocoAddress* addr, signalList.keys()) {
         if(addr->equals(address))
          contains=true;
         break;
        }
        if(!contains){
           signalList.insert(address, createCabSignal(address));
           notifyCabSignalListChanged();
        }
        return signalList.value(address);
    }

    /**
     * Create a new cab signal with the given address.
     *
     * @param address the address the cba signal is for
     * @return a new cab signal
     */
    //abstract /*protected*/ CabSignal createCabSignal(LocoAddress address);

    /**
     * Remove an old CabSignal.
     *
     * @param address the address associated with the cab signal
     */
    //@Override
    /*public*/ void AbstractCabSignalManager::delCabSignal(LocoAddress* address){
       if(signalList.contains(address)){
          signalList.remove(address);
          notifyCabSignalListChanged();
       }
    }

    /**
     * Get a list of known cab signal addresses.
     *
     * @return list of cab signal addresses
     */
    //@Override
    /*public*/ QSet<LocoAddress*> AbstractCabSignalManager::getCabSignalList(){
       return signalList.keys().toSet();
    }

    /**
     * Get an array of known cab signals.
     *
     * @return array of cab signals
     */
    //@Override
    /*public*/ QVector<CabSignal*> AbstractCabSignalManager::getCabSignalArray(){
       return signalList.values().toVector();//.toArray(new CabSignal[1]);
    }

    /**
     * Register a CabSignalListListener object with this CabSignalManager
     *
     * @param listener a CabSignal List Listener object.
     */
    //@Override
    /*public*/ void AbstractCabSignalManager::addCabSignalListListener(CabSignalListListener* listener){
       if(!listListeners.contains(listener)){
          listListeners.append(listener);
       }
    }

    /**
     * Remove a CabSignalListListener object with this CabSignalManager
     *
     * @param listener a CabSignal List Listener object.
     */
    //@Override
    /*public*/ void AbstractCabSignalManager::removeCabSignalListListener(CabSignalListListener* listener){
       if(listListeners.contains(listener)){
          listListeners.removeOne(listener);
       }
    }

    /**
     * Notify the registered CabSignalListListener objects that the CabSignalList
     * has changed.
     */
    //@Override
    /*public*/ void AbstractCabSignalManager::notifyCabSignalListChanged(){
       for(CabSignalListListener* l : listListeners){
           l->notifyCabSignalListChanged();
       }
    }

    // Adds changelistener to blocks
    /*private*/ void AbstractCabSignalManager::initBlocks(){
        blockInit = true;
        BlockManager* bmgr = (BlockManager*)InstanceManager::getDefault("BlockManager");
        QSet</*Block*/NamedBean*> blockSet = bmgr->AbstractManager::getNamedBeanSet();
        for (/*Block*/NamedBean* nb : blockSet)
        {
         Block*b = (Block*)nb;
//            PropertyChangeListener* listener = (PropertyChangeEvent e) -> {
//                handleBlockChange(e);
//            };
         PropertyChangeListener* listener = new ACMPropertyChangeListener(this);
         b->addPropertyChangeListener(listener);
         mBlockListeners.append(listener);
        }
    }

    /**
     * Handle tasks when block contents change.
     * @param e propChgEvent
     */
  /*private*/ void AbstractCabSignalManager::handleBlockChange(PropertyChangeEvent* e) {
        log->debug(tr("property %1 new value %2 old value %3").arg(e->getPropertyName()).arg(e->getNewValue().toString()).arg(e->getOldValue().toString()));
        if (e->getPropertyName() == ("value")){
           if(e->getOldValue().isNull() && !e->getNewValue().isNull()){
              for(CabSignal* c : signalList.values()){
                 if(c->getBlock() == nullptr){
                    c->setBlock(); // cause this cab signal to look for a block.
                 }
              }
           }
        }
   }

    /*private*/ /*final*/ /*static*/ Logger* AbstractCabSignalManager::log = LoggerFactory::getLogger("AbstractCabSignalManager");

