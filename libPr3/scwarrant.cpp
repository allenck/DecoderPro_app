#include "scwarrant.h"
#include "loggerfactory.h"
#include "oblock.h"
#include "blockorder.h"
#include "opath.h"
#include "instancemanager.h"
#include "signalhead.h"
#include "signalmast.h"
#include "signalspeedmap.h"
#include "sleeperthread.h"
#include "vptr.h"
#include "propertychangeevent.h"
#include <qmath.h>
#include <QtGlobal>
#include "system.h"
/**
 * An SCWarrant is a warrant that is controlled by the signals on a layout.
 * It will not run unless you have your layout fully covered with sensors and
 * signals.
 *
 * @author  Karl Johan Lisby Copyright (C) 2016
 */
// /*public*/ class SCWarrant extends Warrant {

    /*public*/ /*static final*/ float SCWarrant::SPEED_STOP = 0.0f;
    /*public*/ /*static final*/ float SCWarrant::SPEED_TO_PLATFORM = 0.2f;
    /*public*/ /*static final*/ float SCWarrant::SPEED_UNSIGNALLED = 0.4f;
    /**
     * Create an object with no route defined. The list of BlockOrders is the
     * route from an Origin to a Destination
     */
    /*public*/ SCWarrant::SCWarrant(QString sName, QString uName, long TTP, QObject* parent) : Warrant(sName, uName) {
        //super(sName, uName);
        log->debug("new SCWarrant "+uName+" TTP="+TTP);
        timeToPlatform = TTP;
        _speedMap = (SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap");

    }

    /*public*/ long SCWarrant::getTimeToPlatform() {
        return timeToPlatform;
    }

    /*public*/ void SCWarrant::setTimeToPlatform(long TTP) {
        timeToPlatform = TTP;
    }

    /*public*/ void SCWarrant::setForward(bool set) {
        forward = set;
    }

    /*public*/ bool SCWarrant::getForward() {
        return forward;
    }

    /*public*/ void SCWarrant::setSpeedFactor(float factor) {
        if (factor > 1.0) {
            speedFactor = 1.0f;
        } else if (factor < 0.1) {
            speedFactor = 0.1f;
        } else {
            speedFactor = factor;
        }
    }

    /*public*/ float SCWarrant::getSpeedFactor() {
        return speedFactor;
    }

    float SCWarrant::getMaxBlockLength() {
        return _maxBlockLength;
    }
    void SCWarrant::setMaxBlockLength() {
        float blockLength;
        for (int i=0; i <= getBlockOrders()->size()-1; i++) {
            blockLength = getBlockOrderAt(i)->getBlock()->getLengthCm();
            if (blockLength > _maxBlockLength) {
                _maxBlockLength = blockLength;
            }
        }
    }

    /*private*/ QString SCWarrant::allocateStartBlock() {
        BlockOrder* bo = getBlockOrderAt(0);
        OBlock* block = bo->getBlock();
        QString message = block->allocate(this);
        if (message != "") {
           log->info(tr("%1 START-block allocation failed %2 ").arg(_trainName).arg(message));
           return message;
        }
        message = bo->setPath(this);
        if (message != "") {
           log->info(tr("%1 setting path in START-block failed %2").arg(_trainName).arg(message));
           return message;
        }
        return "";
    }

    /**
     * This method has been overridden in order to avoid allocation of occupied blocks.
     */
    //@Override
     /*public*/ QString SCWarrant::setRoute(bool delay, QList<BlockOrder *> *orders) {
        return allocateStartBlock();
    }

    bool SCWarrant::allTurnoutsSet() {
        for (int i=0; i<getBlockOrders()->size(); i++) {
            OBlock* block_i = getBlockOrderAt(i)->getBlock();
            OPath*  path_i  = getBlockOrderAt(i)->getPath();
            if (!path_i->checkPathSet()) {
                log->debug(tr("%1: turnouts at block %2 are not set yet (in allTurnoutsSet).").arg(_trainName).arg(block_i->getDisplayName()));
                return false;
            }
        }
        return true;
    }

    /*public*/ bool SCWarrant::isRouteFree() {
        for (int i=0; i<getBlockOrders()->size(); i++) {
            OBlock* block_i = getBlockOrderAt(i)->getBlock();
            if ((block_i->getState() & OBlock::ALLOCATED) == OBlock::ALLOCATED) {
                log->debug(tr("%1: block %2 is allocated to %3 (in isRouteFree).").arg(_trainName).arg(block_i->getDisplayName()).arg(block_i->getAllocatingWarrantName()));
                if (!block_i->isAllocatedTo(this)) {
                    return false;
                }
            }
            if ( ((block_i->getState() & OBlock::OCCUPIED) == OBlock::OCCUPIED) && (i>0) ) {
                log->debug(tr("%1: block %2 is not free (in isRouteFree).").arg(_trainName).arg(block_i->getDisplayName()));
                return false;
            }
        }
        return true;
    }

    bool SCWarrant::isRouteAllocated() {
        for (int i=0; i<getBlockOrders()->size(); i++) {
            OBlock* block_i = getBlockOrderAt(i)->getBlock();
            if (!block_i->isAllocatedTo(this)) {
                log->debug(tr("%1: block %2 is not allocated to this warrant (in isRouteAllocated).").arg(_trainName).arg(block_i->getDisplayName()));
                return false;
            }
        }
        return true;
    }

    /**
     * Callback from acquireThrottle() when the throttle has become available.sync
     */
    //@Override
    /*public*/ void SCWarrant::notifyThrottleFound(DccThrottle* throttle) {
        _throttle = throttle;
        if (throttle == nullptr) {
            abortWarrant("notifyThrottleFound: null throttle(?)!");
            firePropertyChange("throttleFail", "", tr("Throttle Manager unavailable or cannot provide throttle. {0}"));
            return;
        }
        if (_runMode == MODE_LEARN) {
            abortWarrant("notifyThrottleFound: No LEARN mode for SCWarrant");
            InstanceManager::throttleManagerInstance()->releaseThrottle(throttle, (ThrottleListener*)this);
            firePropertyChange("throttleFail", "", tr("Throttle Manager unavailable or cannot provide throttle. {0}"));
            return;
        }
        log->debug(tr("%1 notifyThrottleFound address= %2 _runMode= %3").arg(_trainName).arg(throttle->getLocoAddress()->toString()).arg(_runMode));

        startupWarrant();

        firePropertyChange("runMode", (MODE_NONE), (_runMode));
#if 0
        runSignalControlledTrain();
#endif
    }
    /**
     * Generate status message to show in warrant table
     **/
    //@Override
    /*synchronized*/ /*protected*/ QString SCWarrant::getRunningMessage() {
        if (_throttle == nullptr) {
            // The warrant is not active
            return Warrant::getRunningMessage();
        } else if (_runMode != MODE_RUN) {
            return ("Idle");
        } else {
            QString block = getBlockOrderAt(_idxCurrentOrder)->getBlock()->getDisplayName();
            QString signal = "no signal";
            QString aspect = "none";
            if (_nextSignal != nullptr) {
                signal = _nextSignal->getDisplayName();
                if (static_cast<SignalHead*>(_nextSignal->self() ) ) {
                    int appearance = ((SignalHead*) _nextSignal->self())->getAppearance();
                    aspect = "appearance "+ QString::number(appearance);
                } else {
                    aspect = ((SignalMast*) _nextSignal->self())->getAspect();
                }
            }
            return tr("Block: %1 (index %2) Speed: {2,number,#.#} Signal: %3 showing %4").arg(block).arg(_idxCurrentOrder).arg(_throttle->getSpeedSetting()).arg(signal,aspect);
        }
    }
#if 1

    /******************************************************************************************************
     * Use _throttle to control the train.
     *
     * Get notified of signals, block occupancy and take care of block allocation status to determine speed.
     *
     * We have three speeds: Stop == SPEED_STOP
     *                       Normal == SPEED_NORMAL
     *                       Anything else == SPEED_MID (Limited, Medium, Slow, Restricted)
     *
     * If you have blocks large enough to ramp speed nicely up and down and to have further control
     * of speed settings: Use a normal warrant and not a signal controlled one.
     *
     * This is "the main loop" for running a Signal Controlled Warrant
     ******************************************************************************************************/
    /*protected*/ void SCWarrant::runSignalControlledTrain () {
        waitForStartblockToGetOccupied();
        allocateBlocksAndSetTurnouts(0);
        setTrainDirection();
        SCTrainRunner* thread = new SCTrainRunner(this);
        //new Thread(thread)->start();
        thread->start();
    }

    /**
     * wait until there is a train in the start block.
     */
    /*protected*/ bool SCWarrant::isStartBlockOccupied() {
        int blockState = getBlockOrderAt(0)->getBlock()->getState();
        if ((blockState & OBlock::UNOCCUPIED) == OBlock::UNOCCUPIED) {
            return false;
        } else {
            return true;
        }
    }
    /*synchronized*/ /*protected*/ void SCWarrant::waitForStartblockToGetOccupied() {
        while (!isStartBlockOccupied()) {
            log->debug(tr("%1 waiting for start block %2 to become occupied").arg(_trainName).arg(getBlockOrderAt(0)->getBlock()->getDisplayName()));
            try {
                // We will not be woken up by goingActive, since we have not allocated the start block yet.
                // So do a timed wait.
                //wait(2500);
             SleeperThread::msleep(2500);
            } catch (InterruptedException* ie) {
                log->debug(tr("%1 waitForStartblockToGetOccupied InterruptedException %2").arg(_trainName,ie->toString()),ie);
            }
            catch(Exception* e){
                log->debug(tr("%1 waitForStartblockToGetOccupied unexpected exception %2").arg(_trainName,e->toString()),e);
            }
        }
    }
#endif
    /**
     * Set this train to run backwards or forwards as specified in the command list.
     */
    /*public*/ void SCWarrant::setTrainDirection () {
        _throttle->setIsForward(forward);
    }

    /**
     * Is the next block free or occupied, i.e do we risk to crash into an other train, if we proceed?
     * And is it allocated to us?
     */
    /*public*/ bool SCWarrant::isNextBlockFreeAndAllocated() {
        BlockOrder* bo = getBlockOrderAt(_idxCurrentOrder+1);
        if (bo == nullptr) return false;
        int blockState = bo->getBlock()->getState();
        if (blockState == (OBlock::UNOCCUPIED | OBlock::ALLOCATED)) {
            return getBlockOrderAt(_idxCurrentOrder+1)->getBlock()->isAllocatedTo(this);
        } else {
            return false;
        }
    }

    /**
     * Find the next signal along our route and setup subscription for status changes on that signal.
     */
    /*public*/ void SCWarrant::getAndGetNotifiedFromNextSignal() {
        if (_nextSignal != nullptr) {
            log->debug(tr("%1 getAndGetNotifiedFromNextSignal removing property listener for signal %2").arg(_trainName).arg(_nextSignal->getDisplayName()));
            _nextSignal->removePropertyChangeListener((PropertyChangeListener*)this);
            _nextSignal = nullptr;
        }
        for (int i = _idxCurrentOrder+1; i <= getBlockOrders()->size()-1; i++) {
            BlockOrder* bo = getBlockOrderAt(i);
            if (bo == nullptr) {
                log->debug(tr("%1 getAndGetNotifiedFromNextSignal could not find a BlockOrder for index %2").arg(_trainName).arg(i));
            } else if (bo->getEntryName() == ("")) {
                log->debug(tr("%1 getAndGetNotifiedFromNextSignal could not find an entry to Block for index %1").arg(_trainName).arg(i));
            } else {
                log->debug(tr("%1 getAndGetNotifiedFromNextSignal examines block %2 with entryname = %3").arg(_trainName).arg(bo->getBlock()->getDisplayName()).arg(bo->getEntryName()));
                _nextSignal = bo->getSignal();
                if (_nextSignal != nullptr) {
                    log->debug(tr("%1 getAndGetNotifiedFromNextSignal found a new signal to listen to: %2").arg(_trainName).arg(_nextSignal->getDisplayName()));
                    break;
                }
            }
        }
        if (_nextSignal != nullptr) {
            _nextSignal->addPropertyChangeListener((PropertyChangeListener*)this);
        }
    }

    /**
     * Are we still in the start block?
     */
    bool SCWarrant::inStartBlock() {
        if (_idxCurrentOrder == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Are we close to the destination block?
     */
    bool SCWarrant::approchingDestination() {
        float distance = 0;
        float blockLength;
        if (_idxCurrentOrder == getBlockOrders()->size()-2) {
            // We are in the block just before destination
            return true;
        }
        // Calculate the distance to destination
        for (int i = _idxCurrentOrder; i <= getBlockOrders()->size()-2; i++) {
            blockLength = getBlockOrderAt(i)->getBlock()->getLengthCm();
            if (blockLength < 1) {
                // block length not set for at least one block
                return false;
            }
            distance += blockLength;
        }
        if (distance < 1.5*getMaxBlockLength()) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Move the train if _nextSignal permits. If there is no next signal, we will move forward with half speed.
     */
    /*public*/ void SCWarrant::setSpeedFromNextSignal () {
        QString speed = "";
        if (_nextSignal == nullptr) {
            _throttle->setSpeedSetting(speedFactor*SPEED_UNSIGNALLED);
        } else {
            if (static_cast<SignalHead*>(_nextSignal->self())) {
                int appearance = ((SignalHead*) _nextSignal->self())->getAppearance();
                speed = _speedMap->getAppearanceSpeed(((SignalHead*) _nextSignal->self())->getAppearanceName(appearance));
                log->debug(tr("%1 SignalHead %2 shows appearance %3 which maps to speed %4").arg(_trainName).arg(((SignalHead*) _nextSignal->self())->getDisplayName()).arg(appearance).arg(speed));
            } else {
                QString aspect = ((SignalMast*) _nextSignal->self())->getAspect();
                speed = _speedMap->getAspectSpeed(aspect, ((SignalMast*) _nextSignal->self())->getSignalSystem());
                log->debug(tr(" SignalMast %1 shows aspect %2 which maps to speed ").arg(_trainName).arg(((SignalMast*) _nextSignal->self())->getDisplayName()).arg(aspect).arg(speed));
            }
            float speed_f = (float) (_speedMap->getSpeed(speed) / 125.);
            // Ease the speed, if we are approaching the destination block
            if ((approchingDestination() || inStartBlock()) && (speed_f > SPEED_UNSIGNALLED)) {
                speed_f = SPEED_UNSIGNALLED;
            }
            _throttle->setSpeedSetting(speedFactor*speed_f);
        }
    }
#if 1
     /**
     * Do what the title says. But make sure not to set the turnouts if already done, since that
     * would just cause all signals to go to Stop aspects and thus cause a jerky train movement.
     */
    /*protected*/ void SCWarrant::allocateBlocksAndSetTurnouts(int startIndex) {
        log->debug(tr("%1 allocateBlocksAndSetTurnouts startIndex=%2 _orders.size()=%3").arg(_trainName).arg(startIndex).arg(getBlockOrders()->size()));
        for (int i = startIndex; i < getBlockOrders()->size(); i++) {
            log->debug(tr("%1 allocateBlocksAndSetTurnouts for loop #%2").arg(_trainName).arg(i));
            BlockOrder* bo = getBlockOrderAt(i);
            OBlock* block = bo->getBlock();
            QString pathAlreadySet = block->isPathSet(bo->getPathName());
            if (pathAlreadySet == "") {
                QString message = "";
                if ((block->getState() & OBlock::OCCUPIED) != 0) {
                    log->info(tr("%1 block allocation failed %2 not allocated, but Occupied.").arg(_trainName).arg(block->getDisplayName()));
                    message = " block allocation failed ";
                }
                if (message == "") {
                    message = block->allocate(this);
                    if (message != "") {
                        log->info(tr("%1 block allocation failed %2").arg(_trainName).arg(message));
                    }
                }
                if (message == "") {
                    message = bo->setPath(this);
                }
                if (message != "") {
                    log->debug(tr("%1 path setting failed for %2 at block {} %3").arg(_trainName,getDisplayName(),block->getDisplayName(),message));
                    if (_stoppingBlock != nullptr) {
                        _stoppingBlock->removePropertyChangeListener(this);
                    }
                    _stoppingBlock = block;
                    _stoppingBlock->addPropertyChangeListener(this);
                    // This allocation failed. Do not attempt to allocate the rest of the route.allocation
                    // That would potentially lead to deadlock situations where two warrants are competing
                    // and each getting every second block along the same route.
                    return;
                }
            } else if (pathAlreadySet == (this->getDisplayName())) {
                log->debug(tr("%1 Path %2 already set (and thereby block allocated) for %3").arg(_trainName,bo->getPathName(),pathAlreadySet));
            } else {
                log->info(tr("%1 Block allocation failed: Path %2 already set (and thereby block allocated) for %3").arg(_trainName,bo->getPathName(),pathAlreadySet));
                return;
            }
        }
    }

    /**
     * Block in the route going active.
     * Make sure to allocate the rest of the route, update our present location and then tell
     * the main loop to find a new throttle setting.
     */
    //@Override
    //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "NN_NAKED_NOTIFY", justification="NotifyAll call triggers recomputation")
    /*protected*/ void SCWarrant::goingActive(OBlock* block) {
        int activeIdx = getIndexOfBlock(block, _idxCurrentOrder);
        log->debug(tr("%1 **Block \"%2\" goingActive. activeIdx= %3, _idxCurrentOrder= %4 - warrant= %5 _runMode = {%6 _throttle==null: %7").arg(_trainName,block->getDisplayName()).arg(activeIdx,_idxCurrentOrder).arg(getDisplayName(),_runMode).arg((_throttle==nullptr?"true":"false")));
        if (_runMode != MODE_RUN) {
            // if we are not running, we must not think that we are going to the next block - it must be another train
            return;
        }
        if (_throttle == nullptr || _throttle->getSpeedSetting() == SPEED_STOP) {
            // if we are not running, we must not think that we are going to the next block - it must be another train
            return;
        }
        if (activeIdx <= 0) {
            // The block going active is not part of our route ahead
            log->debug(tr("%1 Block going active is not part of this trains route forward").arg(_trainName));
        } else if (activeIdx == _idxCurrentOrder) {
            // Unusual case of current block losing detection, then regaining it.  i.e. dirty track, derail etc.
            log->debug(tr("%1 Current block becoming active - ignored").arg(_trainName));
        } else if (activeIdx == _idxCurrentOrder+1) {
            // not necessary: It is done in the main loop in SCTrainRunner.run:  allocateBlocksAndSetTurnouts(_idxCurrentOrder+1);
            // update our present location
            _idxCurrentOrder++;
            // fire property change (entered new block)
            firePropertyChange("blockChange", VPtr<OBlock>::asQVariant(getBlockAt(_idxCurrentOrder-1)),  VPtr<OBlock>::asQVariant(getBlockAt(_idxCurrentOrder)));
            // now let the main loop adjust speed.
            /*synchronized(this)*/ {
//                notifyAll();
            }
        } else {
            log->debug(tr("%1 Rogue occupation of block.").arg(_trainName));
            // now let the main loop stop for a train that is coming in our immediate way.
            /*synchronized(this)*/ {
//                notifyAll();
            }
        }
    }

    /**
     * Block in the route is going Inactive.
     * Release the blocks that we have left.
     * Check if current block has been left (i.e. we have left our route) and stop the train in that case.
     */
    //@Override
    //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "NN_NAKED_NOTIFY", justification="See comment above notify call")
    /*protected*/ void SCWarrant::goingInactive(OBlock* block) {
        int idx = getIndexOfBlock(block, 0);  // if idx >= 0, it is in this warrant
        log->debug(tr("%1 Block \"%2\" goingInactive. idx= %3, _idxCurrentOrder= %4 - warrant= %5").arg(_trainName,block->getDisplayName()).arg(idx,_idxCurrentOrder).arg(getDisplayName()));
        if (_runMode != MODE_RUN) {
            return;
        }
        if (idx < _idxCurrentOrder) {
            if (_allowShallowAllocation) {
                deallocateUpToBlock(idx);
            }
        } else if (idx == _idxCurrentOrder) {
            // train is lost
            log->debug(tr("%1 LOST TRAIN firePropertyChange(\"blockChange\", %2, null) - warrant= %3").arg(_trainName,block->getDisplayName(),getDisplayName()));
//            firePropertyChange("blockChange", block, null);
//            emergencyStop();
//            controlRunTrain(ABORT);
        }
        // now let the main loop stop our train if this means that the train is now entirely within the last block.
        // Or let the train continue if an other train that was in its way has now moved.
        /*synchronized(this)*/ {
//            notifyAll();
        }
    }

    /**
     * Deallocate all blocks up to and including idx, but only on these conditions in order to ensure that only a consecutive list of blocks are allocated at any time:
     *     1. Only if our train has left not only this block, but also all previous blocks.
     *     2. Only if the block shall not be re-used ahead and all block up until the block are allocated.
     */
    /*protected*/ void SCWarrant::deallocateUpToBlock(int idx) {
        for (int i=0; i<=idx; i++) {
            OBlock* block_i = getBlockOrderAt(i)->getBlock();
            if (block_i->isAllocatedTo(this)) {
                if ((block_i->getState() & OBlock::UNOCCUPIED) != OBlock::UNOCCUPIED) {
                    //Do not deallocate further blocks, since this one is still allocated to us and not free.
                    log->debug(tr("%1 Block %2 occupied. Not de-allocating any further").arg(_trainName,block_i->getDisplayName()));
                    return;
                }
                bool deAllocate = true;
                // look ahead to see if block_i is reused in the remaining part of the route.
                for (int j= _idxCurrentOrder; j<getBlockOrders()->size(); j++) {
                    OBlock* block_j = getBlockOrderAt(j)->getBlock();
                    if (!block_j->isAllocatedTo(this)) {
                        // There is an unallocated block ahead before we have found block_i is re-used. So deallocate block_i
                        deAllocate = true;
                        break;
                    }
                    if (block_i == block_j) {
                        // clock_i is re-used, and we have no "holes" in the string of allocated blocks before it. So do not deallocate.
                        deAllocate = false;
                        break;
                    }
                }
                if (deAllocate) {
                    log->debug(tr("%1 De-allocating block {%2").arg(_trainName,block_i->getDisplayName()));
                    block_i->deAllocate(this);
                }
            }
        }
    }


    /**
     * Something has fired a property change event.
     * React if:
     *     - it is a warrant that we need to synchronize with. And then again: Why?
     *     - it is _nextSignal
     * Do not worry about sensors and blocks. They are handled by goingActive and goingInactive.
     */
//    @edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = {"UW_UNCOND_WAIT", "NN_NAKED_NOTIFY"},
//            justification = "Unconditional wait is give the warrant that now has _stoppingBlock allocated a little time to deallocate it.  This occurs after this method sets _stoppingBlock to null. NotifyAll passing event, not state.")
//    @Override
    /*public*/ void SCWarrant::propertyChange(PropertyChangeEvent* evt) {
        if (!(qobject_cast<NamedBean*>(evt->getSource()))) {
            log->debug(tr("%1 propertyChange \"%2\" old= %3 new= %4").arg(_trainName,evt->getPropertyName(),evt->getOldValue().toString(),evt->getNewValue().toString()));
            return;
        }
        QString property = evt->getPropertyName();
        log->debug(tr("%1 propertyChange \"%2\" new= %3 source= %4 - warrant= %5").arg(_trainName,property,evt->getNewValue().toString(),((NamedBean*)evt->getSource())->getDisplayName(),getDisplayName()));
        if (_nextSignal->self() != nullptr && _nextSignal->self() == evt->getSource()) {
            if (property == ("Aspect") || property == ("Appearance")) {
                // The signal controlling this warrant has changed. Adjust the speed (in runSignalControlledTrain)
                /*synchronized(this)*/ {
//                    notifyAll();
                }
                return;
            }
        }
        /*synchronized(this)*/ {
            if (_stoppingBlock != nullptr) {
                log->debug(tr("%1 CHECKING STOPPINGBLOCKEVENT ((NamedBean) evt.getSource()).getDisplayName() = '%2' evt.getPropertyName() = '%3' evt.getNewValue() = %4 _throttle==null: %6").arg(_trainName,((NamedBean*) evt->getSource())->getDisplayName(),evt->getPropertyName(),evt->getNewValue().toString(),(_throttle==nullptr?"true":"false")));
                if (((NamedBean*) evt->getSource())->getDisplayName() ==(_stoppingBlock->getDisplayName()) &&
                        evt->getPropertyName() == ("state") &&
                        (( evt->getNewValue().toInt()) & OBlock::UNOCCUPIED) == OBlock::UNOCCUPIED) {
                    log->debug(tr("%1 being aware that Block %2 has become free").arg(_trainName,((NamedBean*) evt->getSource())->getDisplayName()));
                    _stoppingBlock->removePropertyChangeListener(this);
                    _stoppingBlock = nullptr;
                    // we might be waiting for this block to become free
                    // Give the warrant that now has _stoppingBlock allocated a little time to deallocate it
                    try {
                        //wait(100);
                     SleeperThread::msleep(100);
                    } catch (InterruptedException* e) {
                    } catch(Exception* e){
                        log->debug(tr("%1 wait unexpected exception %1").arg(_trainName,e->getMessage()),e);
                    }
                    // And then let our main loop continue
//                    notifyAll();
                    return;
                }
                if (((NamedBean*) evt->getSource())->getDisplayName() ==(getBlockOrderAt(0)->getBlock()->getDisplayName()) &&
                        evt->getPropertyName() == ("state") &&
                        (evt->getOldValue().toInt() & OBlock::UNOCCUPIED) == OBlock::UNOCCUPIED &&
                        (evt->getNewValue().toInt() & OBlock::UNOCCUPIED) != OBlock::UNOCCUPIED &&
                        _throttle==nullptr && _runMode==MODE_RUN) {
                    // We are waiting for the train to arrive at the starting block, and that has just happened now.
                    log->debug(tr("%1 has arrived at starting block").arg(_trainName));
                    QString msg = nullptr;
                    msg = acquireThrottle();
                    if (msg != nullptr) {
                        log->warn(tr("propertyChange of \"%1\" has message: %2").arg(property, msg));
                        _message = msg;
                        abortWarrant(msg);
                    }
                }
            }
        }
    }


    /**
     * Make sure to free up additional resources for a running SCWarrant.
     */
    //@Override
    /*synchronized*/ /*public*/ void SCWarrant::stopWarrant(bool abort) {
        if (_nextSignal != nullptr) {
            _nextSignal->removePropertyChangeListener(this);
            _nextSignal = nullptr;
        }
        Warrant::stopWarrant(abort, false);
        _message = "";
    }

    /**
     * If we think we might have a runaway train - take the power of the entire layout.
     */
    /*private*/ void SCWarrant::emergencyStop() {
        PowerManager* manager = (PowerManager*)InstanceManager::getNullableDefault("PowerManager");
        if (manager == nullptr) {
            log->debug(tr("%1 EMERGENCY STOP IMPOSSIBLE: NO POWER MANAGER").arg(_trainName));
            return;
        }
        try {
            manager->setPower(PowerManager::OFF);
        } catch (Exception* e) {
            log->debug(tr("%1 EMERGENCY STOP FAILED WITH EXCEPTION: %2").arg(_trainName,e->getMessage()),e);
        }
        log->debug(tr("%1 EMERGENCY STOP").arg(_trainName));
    }

    /*******************************************************************************************************************************
     * The waiting for event must happen in a separate thread.
     * Therefore the main code of runSignalControlledTrain is put in this class.
     *******************************************************************************************************************************/
    /*static*/ /*LinkedBlockingQueue*/QLinkedList<SCWarrant*> SCWarrant::waitToRunQ = QLinkedList<SCWarrant*>();
//    /*private*/ class SCTrainRunner implements Runnable {
//        SCWarrant _warrant = null;
//        SCTrainRunner(SCWarrant warrant) {
//            _warrant = warrant;
//        }

        /**
         * When not using shallow allocation, warrants will have to wait until the entire route
         * is free and allocated to that particular warrant, before strting to run the train.
         * This method uses the waitToRunQ to ensure that warrants do not just compete about
         * resources, but waits in line until their route is free and unallocated.
         */
        bool SCTrainRunner::isItOurTurn() {
            for (SCWarrant* e : _warrant->waitToRunQ) {
                try { // using another SCWarrant might be dangerous - it might no longer exist
                    _warrant->log->debug(tr("%1 isItOurTurn is checking %2").arg(_warrant->_trainName,e->getDisplayName()));
                    if (e->isRouteFree()) {
                        if (e == _warrant) {
                            _warrant->log->debug(tr("%1 isItOurTurn: We are first in line").arg(_warrant->_trainName));
                            return true;
                        } else {
                            _warrant->log->debug(tr("%1 isItOurTurn: An other warrant is before us").arg(_warrant->_trainName));
                            return false;
                        }
                    } else {
                        if (e == _warrant) {
                            _warrant->log->debug(tr("%1 isItOurTurn: our route is not free - keep waiting").arg(_warrant->_trainName));
                            return false;
                        }
                    }
                } catch (Exception* ex) {
                    _warrant->log->debug(tr("%1 isItOurTurn exception ignored: %2").arg(_warrant->_trainName,ex->getMessage()),ex);
                }
            }
            // we should not reach this point, but if we do, we should try to run
            _warrant->log->debug(tr("%1 isItOurTurn: No warrant with a free route is waiting. Let us try our luck, so that we are not all waiting for each other.").arg(_warrant->_trainName));
            return true;
        }

        //@Override
        /*public*/ void SCTrainRunner::run() {
           /*synchronized(_warrant)*/ {

            // Make sure the entire route is allocated before attemting to start the train
            if (!_warrant->_allowShallowAllocation) {
                bool AllocationDone = false;
                _warrant->log->debug(tr("%1 ENTERING QUEUE ").arg(_warrant->_trainName));
                try {
                    _warrant->waitToRunQ.push_front(_warrant);
                } catch (InterruptedException* ie) {
                    _warrant->log->debug(tr("%1 waitToRunQ.put InterruptedException %2").arg(_warrant->_trainName,ie->getLocalizedMessage()),ie);
                }

                while (!AllocationDone) {
                    _warrant->log->debug(tr("%1 Route is not allocated yet..... ").arg(_warrant->_trainName));
                    while (!isItOurTurn()) {
                        _warrant->deAllocate();
                        _warrant->log->debug(tr("%1 Waiting for route to become free ....").arg(_warrant->_trainName));
                        try {
                            SleeperThread::msleep(2500 + qRound(1000.*qrand()));
                        } catch (InterruptedException* ie) {
                            _warrant->log->debug(tr("%1 _warrant.wait InterruptedException %1").arg(_warrant->_trainName,ie->getMessage()),ie);
                        }
                        catch(Exception* e){
                            _warrant->log->debug(tr("%1 _warrant.wait unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                        }
                    }
                    _warrant->allocateStartBlock();
                    _warrant->allocateBlocksAndSetTurnouts(1);
                    AllocationDone = _warrant->isRouteAllocated();
                    if (!AllocationDone) {
                        _warrant->deAllocate();
                        try {
                            //_warrant.wait(10000 + Math.round(1000*Math.random()));
                         SleeperThread::msleep(2500 + qRound(1000.*qrand()));
                        } catch (InterruptedException* ie) {
                            _warrant->log->debug(tr("%1 _warrant.wait !AllocationDone InterruptedException %1").arg(_warrant->_trainName,ie->getMessage()),ie);
                        }
                        catch(Exception* e){
                            _warrant->log->debug(tr("%1 _warrant.wait !AllocationDone unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                        }
                    }
                }

                _warrant->log->debug(tr("%1 LEAVING QUEUE ").arg(_warrant->_trainName));
                _warrant->waitToRunQ.removeOne(_warrant);

                while (!_warrant->allTurnoutsSet()) {
                    _warrant->log->debug(tr("%1 Waiting for turnouts to settle ....").arg(_warrant->_trainName));
                    try {
                        SleeperThread::msleep(2500);
                    } catch (InterruptedException* ie) {
                        _warrant->log->debug(tr("%1 _warrant.wait InterruptedException %1").arg(_warrant->_trainName,ie->getLocalizedMessage()),ie);
                    }
                    catch(Exception* e){
                        _warrant->log->debug(tr("%1 _warrant.wait unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                    }
                }
                // And then wait another 3 seconds to make the last turnout settle - just in case the command station is not giving correct feedback
                try {
                    SleeperThread::msleep(3000);
                } catch (InterruptedException* ie) {
                    _warrant->log->debug(tr("%1 InterruptedException %2").arg(_warrant->_trainName,ie->getMessage()),ie);
                }
                catch(Exception* e){
                    _warrant->log->debug(tr("%1 wait unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                }
            }

            // Do not include the stopping block in this while loop. It will be handled after the loop.
            QList<BlockOrder*>* orders = _warrant->getBlockOrders();
            while (_warrant->_idxCurrentOrder < orders->size()-1 && _warrant->_runMode == _warrant->MODE_RUN) {
                _warrant->log->debug(tr("%1 runSignalControlledTrain entering while loop. _idxCurrentOrder=%2 _orders.size()=%3").arg(_warrant->_trainName).arg(_warrant->_idxCurrentOrder,orders->size()));
                if (_warrant->_throttle == nullptr) {
                    // We lost our throttle, so we might have a runaway train
                    _warrant->emergencyStop();
                }
                if (_warrant->_allowShallowAllocation) {
                    _warrant->allocateBlocksAndSetTurnouts(_warrant->_idxCurrentOrder);
                }
                if (_warrant->isNextBlockFreeAndAllocated()) {
                    _warrant->getAndGetNotifiedFromNextSignal();
                    _warrant->setSpeedFromNextSignal();
                } else {
                    try {
                        _warrant->_throttle->setSpeedSetting(_warrant->SPEED_STOP);
                        _warrant->getBlockOrderAt(_warrant->_idxCurrentOrder+1)->getBlock()->addPropertyChangeListener(_warrant);
                        _warrant->log->debug(tr("%1 runSignalControlledTrain stops train due to block not free: %2").arg(_warrant->_trainName).arg(_warrant->getBlockOrderAt(_warrant->_idxCurrentOrder+1)->getBlock()->getDisplayName()));
                    } catch (Exception* e) {
                        _warrant->emergencyStop();
                        _warrant->log->debug(tr("%1 exception trying to stop train due to block not free: %1").arg(_warrant->_trainName,e->getMessage()),e);
                    }
                }
                _warrant->log->debug(tr("%1 %2 before wait %3 _idxCurrentOrder: %4 orders.size(): %5").arg(_warrant->_trainName,_warrant->getDisplayName(),_warrant->getRunningMessage()).arg(_warrant->_idxCurrentOrder,orders->size()));
                try {
                    // We do a timed wait for the sake of robustness, even though we will be woken up by all relevant events.
                   SleeperThread::msleep(2000);
                } catch (InterruptedException* ie) {
                    _warrant->log->debug(tr("%1 InterruptedException %2").arg(_warrant->_trainName,ie->getMessage()),ie);
                }
                catch(Exception* e){
                    _warrant->log->debug(tr("%1 wait unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                }
                _warrant->log->debug(tr("%1 %2 after wait %3 _idxCurrentOrder: %4 orders.size(): %5").arg(_warrant->_trainName,_warrant->getDisplayName(),_warrant->getRunningMessage()).arg(_warrant->_idxCurrentOrder,orders->size()));
            }
            // We are now in the stop block. Move forward for half a second with half speed until the block before the stop block is free.
            _warrant->log->debug(tr("%1 runSignalControlledTrain out of while loop, i.e. train entered stop block _idxCurrentOrder=%2" \
                       " orders.size()=%3 waiting for train to clear block %4").arg(
                      _warrant->_trainName).arg(_warrant->_idxCurrentOrder,orders->size()).arg(_warrant->getBlockAt(orders->size()-2)->getDisplayName()));
            if (_warrant->_throttle==nullptr) {
                _warrant->emergencyStop();
                _warrant->log->debug("Throttle lost at stop block");
            } else {
                _warrant->_throttle->setSpeedSetting(_warrant->speedFactor*_warrant->SPEED_TO_PLATFORM);
            }
            while ((_warrant->getBlockAt(orders->size()-2)->getState()&OBlock::OCCUPIED)==OBlock::OCCUPIED && _warrant->getBlockAt(orders->size()-2)->isAllocatedTo(_warrant)) {
                _warrant->log->debug(tr(" runSignalControlledTrain entering wait. Block %1" \
                          "   free: %2   allocated to this warrant: %3").arg(
                          _warrant->_trainName,_warrant->getBlockAt(orders->size()-2)->getDisplayName()).arg(_warrant->getBlockAt(orders->size()-2)->isFree()).arg(_warrant->getBlockAt(orders->size()-2)->isAllocatedTo(_warrant)));
                try {
                    // This does not need to be a timed wait, since we will get interrupted once the block is free
                    // However, the functionality is more robust with a timed wait.
                    SleeperThread::msleep(500);
                } catch (InterruptedException* ie) {
                    _warrant->log->debug(tr("%1 InterruptedException %2").arg(_warrant->_trainName,ie->getMessage()),ie);
                }
                catch(Exception* e){
                    _warrant->log->debug(tr("%1 wait unexpected exception %2").arg(_warrant->_trainName,e->getMessage()),e);
                }
                _warrant->log->debug(tr("%1 runSignalControlledTrain woken after last wait.... _orders.size()=%2").arg(_warrant->_trainName).arg(orders->size()));
            }
            if (_warrant->timeToPlatform > 100) {
                _warrant->log->debug(tr("%1 runSignalControlledTrain is now fully into the stopping block. Proceeding for %2 miliseconds").arg(_warrant->_trainName,_warrant->timeToPlatform));
                long timeWhenDone = /*System::currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() + _warrant->timeToPlatform;
                long remaining;
                while ((remaining = timeWhenDone - /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch()) > 0) {
                    try {
                        _warrant->log->debug(tr("%1 running slowly to platform for %2 miliseconds").arg(_warrant->_trainName).arg(remaining));
                        SleeperThread::msleep(remaining);
                    } catch (InterruptedException* e) {
                        _warrant->log->debug(tr("%1 InterruptedException %2").arg(_warrant->_trainName,e->getMessage()),e);
                    }
                }
            }
            _warrant->log->debug(tr("{} runSignalControlledTrain STOPPING TRAIN IN STOP BLOCK").arg(_warrant->_trainName));
            if (_warrant->_throttle==nullptr) {
                _warrant->emergencyStop();
                _warrant->log->debug("Throttle lost after stop block");
            } else {
                _warrant->_throttle->setSpeedSetting(_warrant->SPEED_STOP);
            }
            _warrant->stopWarrant(false);
        }
    }


    /* What super does currently is fine. But FindBug reports EQ_DOESNT_OVERRIDE_EQUALS
     * FindBug wants us to duplicate and override anyway
     */
    //@Override
    /*public*/ bool SCWarrant::equals(QObject* obj) {
        return Warrant::equals(obj);
    }

    /* What super does currently is fine. But FindBug reports HE_EQUALS_NO_HASHCODE
     * FindBug wants us to duplicate and override anyway
     */
    //@Override
    /*public*/ uint SCWarrant::hashCode() {
        return Warrant::hashCode();
    }
#endif
    /**
     *
     */
    /*private*/ /*final*/ /*static*/ Logger* SCWarrant::log = LoggerFactory::getLogger("SCWarrant");
