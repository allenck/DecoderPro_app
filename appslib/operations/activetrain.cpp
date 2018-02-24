#include "activetrain.h"
#include "propertychangesupport.h"
#include "transit.h"
#include "rosterentry.h"
#include "roster.h"
#include "logixtableaction.h"
#include "namedbeanhandle.h"
#include "instancemanager.h"
#include "dispatcherframe.h"
#include "autoactivetrain.h"
#include "propertychangesupport.h"
#include "section.h"
#include "allocationrequest.h"
#include "vptr.h"
#include "allocatedsection.h"
#include "layouteditor.h"
#include <QDateTime>

//ActiveTrain::ActiveTrain(QObject *parent) : QObject(parent)
//{

//}
/**
 * This class holds information and options for an ActiveTrain, that is a train
 * that has been linked to a Transit and activated for transit around the
 * layout.
 * <P>
 * An ActiveTrain may be assigned one of the following modes, which specify how
 * the active train will be run through its transit: AUTOMATIC - indicates the
 * ActiveTrain will be run under automatic control of the computer. (Automatic
 * Running) MANUAL - indicates an ActiveTrain running in AUTOMATIC mode has
 * reached a Special Action in its Transit that requires MANUAL operation. When
 * this happens, the status changes to WORKING, and the mode changes to MANUAL.
 * The ActiveTrain will be run by an operator using a throttle. AUTOMATIC
 * running is resumed when the work has been completed. DISPATCHED - indicates
 * the ActiveTrain will be run by an operator using a throttle. A dispatcher
 * will allocate Sections to the ActiveTrain as needed, control optional signals
 * using a CTC panel or computer logic, and arbitrate any conflicts between
 * ActiveTrains. (Human Dispatcher).
 * <P>
 * An ActiveTrain will have one of the following statuses:
 *       RUNNING - Actively running on the layout, according to its mode of operation.
 *       PAUSED - Paused waiting for a user-specified number of fast clock minutes.  The
 *                  Active Train is expected to move to either RUNNING or WAITING once the
 *                  specified number of minutes has elapsed. This is intended for automatic
 *                  station stops. (automatic trains only)
 *       WAITING - Stopped waiting for a Section allocation. This is the state the Active
 *                  Train is in when it is created in Dispatcher.
 *       WORKING - Performing work under control of a human engineer. This is the state an
 *                  Active Train assumes when an engineer is picking up or setting out cars
 *                  at industries. (automatic trains only)
 *       READY - Train has completed WORKING, and is awaiting a restart - dispatcher clearance
 *                  to resume running. (automatic trains only)
 *       STOPPED - Train was stopped by the dispatcher. Dispatcher must resume. (automatic trains only)
 *       DONE -  Train has completed its transit of the layout and is ready to be terminated
 *                  by the dispatcher, or Restart pressed to repeat the automated run.
 * Status is a bound property.
 * <P>
 * The ActiveTrain status should maintained (setStatus) by the running class, or if running
 *       in DISPATCHED mode, by Dispatcher.
 * When an ActiveTrain is WAITING, and the dispatcher allocates a section to it, the status
 *       of the ActiveTrain is automatically set to RUNNING. So an autoRun class can listen
 *       to the status of the ActiveTrain to trigger start up if the train has been waiting
 *       for the dispatcher.
 * Note: There is still more to be programmed here.
 * <P>
 * Train information supplied when the ActiveTrain is created can come from any
 * of the following: ROSTER - The train was selected from the JMRI roster menu
 * OPERATIONS - The train was selected from trains available from JMRI
 * operations USER - Neither menu was used--the user entered a name and DCC
 * address. Train source information is recorded when an ActiveTrain is created,
 * and may be referenced by getTrainSource if it is needed by other objects. The
 * train source should be specified in the Dispatcher Options window prior to
 * creating an ActiveTrain.
 * <P>
 * ActiveTrains are referenced via a list in DispatcherFrame, which serves as a
 * manager for ActiveTrain objects.
 * <P>
 * ActiveTrains are transient, and are not saved to disk. Active Train
 * information can be saved to disk, making set up with the same options, etc
 * very easy.
 * <P>
 * An ActiveTrain runs through its Transit in the FORWARD direction, until a
 * Transit Action reverses the direction of travel in the Transit. When running
 * with its Transit reversed, the Active Train returns to its starting Section.
 * Upon reaching and stopping in its starting Section, the Transit is
 * automatically set back to the forward direction. If AutoRestart is set, the
 * run is repeated. The direction of travel in the Transit is maintained here.
 *
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author	Dave Duchamp Copyright (C) 2008-2011
 */
///*public*/ class ActiveTrain {

    /**
     * Main constructor method
     */
    /*public*/ ActiveTrain::ActiveTrain(Transit* t, QString name, int trainSource, QObject *parent) : QObject(parent)
 {
  log = new Logger("ActiveTrain");
  // instance variables
   mTransit = NULL;
   mTrainName = "";
   mTrainSource = ROSTER;
   mRoster = NULL;
   mStatus = WAITING;
   mMode = DISPATCHED;
   mTransitReversed = false;  // true if Transit is running in reverse
   mAllocationReversed = false;  // true if allocating Sections in reverse
   mAutoActiveTrain = NULL;
   mAllocatedSections = new QList<AllocatedSection*>();
   mLastAllocatedSection = NULL;
   mSecondAllocatedSection = NULL;
   mNextAllocationNumber = 1;
   mNextSectionToAllocate = NULL;
   mNextSectionSeqNumber = 0;
   mNextSectionDirection = 0;
   mStartBlock = NULL;
  mStartBlockSectionSequenceNumber = 0;
  mEndBlock = NULL;
  mEndBlockSection = NULL;
  mEndBlockSectionSequenceNumber = 0;
  mPriority = 0;
  mAutoRun = false;
  mDccAddress = "";
  mResetWhenDone = true;
  mReverseAtEnd = false;
  mAllocateAllTheWay = false;
  mDelayedRestart = NODELAY;
  mDelayedStart = NODELAY;
  mDepartureTimeHr = 8;
  mDepartureTimeMin = 0;
  mRestartDelay = 0;
  mStartSensor = NULL; // A Sensor that when changes state to active will trigger the trains start.
  mRestartSensor = NULL; // A Sensor that when changes state to active will trigger the trains start.
  mTrainType = LOCAL_FREIGHT;
  terminateWhenFinished = false;

  restartHr = 0;
  restartMin = 0;

  delaySensorListener = NULL;
  restartSensorListener = NULL;


 // start up instance variables
  mStarted = false;

  restartPoint = false;

  _holdAllocation = false;

  // Property Change Support
  pcs = new PropertyChangeSupport(this);


  mTransit = t;
  mTrainName = name;
  mTrainSource = trainSource;
 }

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");





/**
 * Access methods
 */
/*public*/ bool ActiveTrain::getStarted() {
    return mStarted;
}

/*public*/ void ActiveTrain::setStarted() {
    mStarted = true;
    mStatus = RUNNING;
    setStatus(WAITING);
    if (mAutoActiveTrain != NULL && DispatcherFrame::instance()->getSignalType() == DispatcherFrame::SIGNALMAST) {
        mAutoActiveTrain->setupNewCurrentSignal(NULL);
    }
}

/*public*/ Transit* ActiveTrain::getTransit() {
    return mTransit;
}

/*public*/ QString ActiveTrain::getTransitName() {
    QString s = mTransit->getSystemName();
    QString u = mTransit->getUserName();
    if ((u != NULL) && (u!=("") && (u!=(s)))) {
        return (s + "(" + u + ")");
    }
    return s;
}

/*public*/ QString ActiveTrain::getActiveTrainName() {
    return (mTrainName + "/" + getTransitName());
}

// Note: Transit and Train may not be changed once an ActiveTrain is created.
/*public*/ QString ActiveTrain::getTrainName() {
    return mTrainName;
}

/*public*/ int ActiveTrain::getTrainSource() {
    return mTrainSource;
}

/*public*/ void ActiveTrain::setRosterEntry(RosterEntry* re) {
    mRoster = re;
}

/*public*/ RosterEntry* ActiveTrain::getRosterEntry() {
    if (mRoster == NULL && getTrainSource() == ROSTER) {
        //Try to resolve the roster based upon the train name
        mRoster = Roster::getDefault()->getEntryForId(getTrainName());
    } else if (getTrainSource() != ROSTER) {
        mRoster = NULL;
    }
    return mRoster;
}

/*public*/ int ActiveTrain::getStatus() {
    return mStatus;
}

/*public*/ void ActiveTrain::setStatus(int status) {
    if (restartPoint) {
        return;
    }
    if ((status == RUNNING) || (status == PAUSED) || (status == WAITING) || (status == WORKING)
            || (status == READY) || (status == STOPPED) || (status == DONE)) {
        if (mStatus != status) {
            int old = mStatus;
            mStatus = status;
            firePropertyChange("status", (old), (mStatus));
        }
        if (mStatus == DONE && terminateWhenFinished) {
            DispatcherFrame::instance()->terminateActiveTrain(this);
        }
    } else {
        log->error("Invalid ActiveTrain status - " + status);
    }
}

/*public*/ QString ActiveTrain::getStatusText() {
    if (mStatus == RUNNING) {
        return ("RUNNING");
    } else if (mStatus == PAUSED) {
        return ("PAUSED");
    } else if (mStatus == WAITING) {
        if (!mStarted) {
            if (mDelayedStart == TIMEDDELAY) {
                return LogixTableAction::formatTime(mDepartureTimeHr,
                        mDepartureTimeMin) + " " + ("START");
            } else if (mDelayedStart == SENSORDELAY) {
                //return (Bundle.getMessage("BeanNameSensor") + " " + getDelaySensorName());
             return tr("Sensor") + " " + getDelaySensorName();
            }
        }
        return ("WAITING");
    } else if (mStatus == WORKING) {
        return ("WORKING");
    } else if (mStatus == READY) {
        if (restartPoint && getDelayedRestart() == TIMEDDELAY) {
            return LogixTableAction::formatTime(restartHr,
                    restartMin) + " " + ("START");
        } else if (restartPoint && getDelayedRestart() == SENSORDELAY) {
            //return (Bundle.getMessage("BeanNameSensor") + " " + getRestartSensorName());
         return tr("Sensor")  + " " + getRestartSensorName();
        }
        return ("READY");
    } else if (mStatus == STOPPED) {
        return ("STOPPED");
    } else if (mStatus == DONE) {
        return ("DONE");
    }
    return ("");
}

/*public*/ bool ActiveTrain::isTransitReversed() {
    return mTransitReversed;
}

/*public*/ void ActiveTrain::setTransitReversed(bool set) {
    mTransitReversed = set;
}

/*public*/ bool ActiveTrain::isAllocationReversed() {
    return mAllocationReversed;
}

/*public*/ void ActiveTrain::setAllocationReversed(bool set) {
    mAllocationReversed = set;
}

/*public*/ int ActiveTrain::getDelayedStart() {
    return mDelayedStart;
}

/*public*/ void ActiveTrain::setDelayedStart(int delay) {
    mDelayedStart = delay;
}

/*public*/ int ActiveTrain::getDelayedRestart() {
    return mDelayedRestart;
}

/*public*/ void ActiveTrain::setDelayedReStart(int delay) {
    mDelayedRestart = delay;
}

/*public*/ int ActiveTrain::getDepartureTimeHr() {
    return mDepartureTimeHr;
}

/*public*/ void ActiveTrain::setDepartureTimeHr(int hr) {
    mDepartureTimeHr = hr;
}

/*public*/ int ActiveTrain::getDepartureTimeMin() {
    return mDepartureTimeMin;
}

/*public*/ void ActiveTrain::setDepartureTimeMin(int min) {
    mDepartureTimeMin = min;
}

/*public*/ void ActiveTrain::setRestartDelay(int min) {
    mRestartDelay = min;
}

/*public*/ int ActiveTrain::getRestartDelay() {
    return mRestartDelay;
}
//int restartHr = 0;
//int restartMin = 0;

/*public*/ int ActiveTrain::getRestartDepartHr() {
    return restartHr;
}

/*public*/ int ActiveTrain::getRestartDepartMin() {
    return restartMin;
}

/*public*/ void ActiveTrain::setTerminateWhenDone(bool boo) {
    terminateWhenFinished = boo;
}

/*public*/ Sensor* ActiveTrain::getDelaySensor() {
    if (mStartSensor == NULL) {
        return NULL;
    }
    return mStartSensor->getBean();
}

/*public*/ QString ActiveTrain::getDelaySensorName() {
    if (mStartSensor == NULL) {
        return NULL;
    }
    return mStartSensor->getName();
}

/*public*/ void ActiveTrain::setDelaySensor(Sensor* s) {
    if (s == NULL) {
        mStartSensor = NULL;
        return;
    }
    mStartSensor = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(s->getDisplayName(), s);
}

/*public*/ Sensor* ActiveTrain::getRestartSensor() {
    if (mRestartSensor == NULL) {
        return NULL;
    }
    return mRestartSensor->getBean();
}

/*public*/ QString ActiveTrain::getRestartSensorName() {
    if (mRestartSensor == NULL) {
        return NULL;
    }
    return mRestartSensor->getName();
}

/*public*/ void ActiveTrain::setRestartSensor(Sensor* s) {
    if (s == NULL) {
        mRestartSensor = NULL;
        return;
    }
    mRestartSensor =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(s->getDisplayName(), s);
}


/*public*/ void ActiveTrain::initializeDelaySensor() {
    if (mStartSensor == NULL) {
        log->error("Call to initialise delay on start sensor, but none specified");
        return;
    }
#if 0
    if (delaySensorListener == NULL) {
        /*final*/ ActiveTrain at = this;
        delaySensorListener = new PropertyChangeListener() {
            //@Override
            /*public*/ void propertyChange(PropertyChangeEvent e) {
                if (e.getPropertyName() == ("KnownState")) {
                    if (((Integer) e.getNewValue()).intValue() == jmri.Sensor.ACTIVE) {
                        getDelaySensor().removePropertyChangeListener(delaySensorListener);
                        DispatcherFrame.instance().removeDelayedTrain(at);
                        setStarted();
                        DispatcherFrame.instance().forceScanOfAllocation();
                        try {
                            getDelaySensor().setKnownState(jmri.Sensor.INACTIVE);
                        } catch (jmri.JmriException ex) {
                            log.error("Error reseting start sensor back to in active");
                        }
                    }
                }
            }
        };
    }
    getDelaySensor().addPropertyChangeListener(delaySensorListener);
#endif
}

/*public*/ void ActiveTrain::initializeRestartSensor() {
    if (mRestartSensor == NULL) {
        log->error("Call to initialise delay on start sensor, but none specified");
        return;
    }
#if 0
    if (restartSensorListener == NULL) {
        final ActiveTrain at = this;
        restartSensorListener = new PropertyChangeListener() {
            //@Override
            /*public*/ void propertyChange(PropertyChangeEvent e) {
                if (e.getPropertyName() == ("KnownState")) {
                    if (((Integer) e.getNewValue()).intValue() == jmri.Sensor.ACTIVE) {
                        getRestartSensor().removePropertyChangeListener(restartSensorListener);
                        restartSensorListener = NULL;
                        DispatcherFrame.instance().removeDelayedTrain(at);
                        restart();
                        DispatcherFrame.instance().forceScanOfAllocation();
                        try {
                            getRestartSensor().setKnownState(jmri.Sensor.INACTIVE);
                        } catch (jmri.JmriException ex) {
                            log.error("Error reseting start sensor back to in active");
                        }
                    }
                }
            }
        };
    }
    getRestartSensor().addPropertyChangeListener(restartSensorListener);
#endif
}

/*public*/ void ActiveTrain::setTrainType(int type) {
    mTrainType = type;
}

/** set train type using localized string name as stored
 *
 * @param sType - name, such as "LOCAL_PASSENGER"
 */
/*public*/ void ActiveTrain::setTrainType(QString sType) {
    if (sType == (("LOCAL_FREIGHT"))) {
        setTrainType(LOCAL_FREIGHT);
    } else if (sType == (("LOCAL_PASSENGER"))) {
        setTrainType(LOCAL_PASSENGER);
    } else if (sType == (("THROUGH_FREIGHT"))) {
        setTrainType(THROUGH_FREIGHT);
    } else if (sType == (("THROUGH_PASSENGER"))) {
        setTrainType(THROUGH_PASSENGER);
    } else if (sType == (("EXPRESS_FREIGHT"))) {
        setTrainType(EXPRESS_FREIGHT);
    } else if (sType == (("EXPRESS_PASSENGER"))) {
        setTrainType(EXPRESS_PASSENGER);
    } else if (sType == (("MOW"))) {
        setTrainType(MOW);
    }
}

/*public*/ int ActiveTrain::getTrainType() {
    return mTrainType;
}

/*public*/ QString ActiveTrain::getTrainTypeText() {
    if (mTrainType == LOCAL_FREIGHT) {
        return ("LOCAL_FREIGHT");
    } else if (mTrainType == LOCAL_PASSENGER) {
        return ("LOCAL_PASSENGER");
    } else if (mTrainType == THROUGH_FREIGHT) {
        return ("THROUGH_FREIGHT");
    } else if (mTrainType == THROUGH_PASSENGER) {
        return ("THROUGH_PASSENGER");
    } else if (mTrainType == EXPRESS_FREIGHT) {
        return ("EXPRESS_FREIGHT");
    } else if (mTrainType == EXPRESS_PASSENGER) {
        return ("EXPRESS_PASSENGER");
    } else if (mTrainType == MOW) {
        return ("MOW");
    }
    return ("");
}

/*public*/ int ActiveTrain::getMode() {
    return mMode;
}

/*public*/ void ActiveTrain::setMode(int mode) {
    if ((mode == AUTOMATIC) || (mode == MANUAL)
            || (mode == DISPATCHED)) {
        int old = mMode;
        mMode = mode;
        firePropertyChange("mode", (old), (mMode));
    } else {
        log->error("Attempt to set ActiveTrain mode to illegal value - " + QString::number(mode));
    }
}

/*public*/ QString ActiveTrain::getModeText() {
    if (mMode == AUTOMATIC) {
        return ("AUTOMATIC");
    } else if (mMode == MANUAL) {
        return ("MANUAL");
    } else if (mMode == DISPATCHED) {
        return ("DISPATCHED");
    }
    return ("");
}

/*public*/ void ActiveTrain::setAutoActiveTrain(AutoActiveTrain* aat) {
    mAutoActiveTrain = aat;
}

/*public*/ AutoActiveTrain* ActiveTrain::getAutoActiveTrain() {
    return mAutoActiveTrain;
}
#if 0
/*public*/ int getRunningDirectionFromSectionAndSeq(Section* s, int seqNo) {
    int dir = mTransit.getDirectionFromSectionAndSeq(s, seqNo);
    if (mTransitReversed) {
        if (dir == jmri.Section.FORWARD) {
            dir = jmri.Section.REVERSE;
        } else {
            dir = jmri.Section.FORWARD;
        }
    }
    return dir;
}
#endif
/*public*/ int ActiveTrain::getAllocationDirectionFromSectionAndSeq(Section* s, int seqNo) {
    int dir = mTransit->getDirectionFromSectionAndSeq(s, seqNo);
    if (mAllocationReversed) {
        if (dir == Section::FORWARD) {
            dir = Section::REVERSE;
        } else {
            dir = Section::FORWARD;
        }
    }
    return dir;
}
#if 1
/*public*/ void ActiveTrain::addAllocatedSection(AllocatedSection* as) {
    if (as != NULL) {
        mAllocatedSections->append(as);
        if (as->getSection() == mNextSectionToAllocate) {
            // this  is the next Section in the Transit, update pointers
            mLastAllocatedSection = as->getSection();
            mNextSectionToAllocate = as->getNextSection();
            mNextSectionSeqNumber = as->getNextSectionSequence();
            mNextSectionDirection = getAllocationDirectionFromSectionAndSeq(
                    mNextSectionToAllocate, mNextSectionSeqNumber);
            as->setAllocationNumber(mNextAllocationNumber);
            mNextAllocationNumber++;
        } else {
            // this is an extra allocated Section
            as->setAllocationNumber(-1);
        }
        if ((mStatus == WAITING) && mStarted) {
            setStatus(RUNNING);
        }
        if (as->getSequence() == 2) {
            mSecondAllocatedSection = as->getSection();
        }
        if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getNameInAllocatedBlock())
        {
         if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getRosterEntryInBlock() && getRosterEntry() != NULL) {
             as->getSection()->setNameFromActiveBlock(VPtr<RosterEntry>::asQVariant(getRosterEntry()));
         } else {
             as->getSection()->setNameInBlocks(mTrainName);
         }
         as->getSection()->suppressNameUpdate(true);
        }
        if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getExtraColorForAllocated()) {
            as->getSection()->setAlternateColorFromActiveBlock(true);
        }
        refreshPanel();
    } else {
        log->error("Null Allocated Section reference in addAllocatedSection of ActiveTrain");
    }
}
#endif
/*private*/ void ActiveTrain::refreshPanel() {
    if (DispatcherFrame::instance()->getLayoutEditor() != NULL) {
        DispatcherFrame::instance()->getLayoutEditor()->redrawPanel();
    }
}

/*public*/ void ActiveTrain::removeAllocatedSection(AllocatedSection* as) {
    if (as == NULL) {
        log->error("Null AllocatedSection reference in removeAllocatedSection of ActiveTrain");
        return;
    }
    int index = -1;
    for (int i = 0; i < mAllocatedSections->size(); i++) {
        if (as == mAllocatedSections->value(i)) {
            index = i;
        }
    }
    if (index < 0) {
        log->error("Attempt to remove an unallocated Section " + as->getSectionName());
        return;
    }
    mAllocatedSections->removeAt(index);
    if (mAutoRun) {
        mAutoActiveTrain->removeAllocatedSection(as);
    }
    if (DispatcherFrame::instance()->getNameInAllocatedBlock()) {
        as->getSection()->clearNameInUnoccupiedBlocks();
        as->getSection()->suppressNameUpdate(false);
    }
    as->getSection()->setAlternateColor(false);
    refreshPanel();
    if (as->getSection() == mLastAllocatedSection) {
        mLastAllocatedSection = NULL;
        if (mAllocatedSections->size() > 0) {
            mLastAllocatedSection = mAllocatedSections->value(
                    mAllocatedSections->size() - 1)->getSection();
        }
    }
}

/**
 * This resets the state of the ActiveTrain so that it can be reallocated.
 */
/*public*/ void ActiveTrain::allocateAFresh() {
    setStatus(WAITING);
    setTransitReversed(false);
    QList<AllocatedSection*>* sectionsToRelease = new QList<AllocatedSection*>();
    for (AllocatedSection* as : *DispatcherFrame::instance()->getAllocatedSectionsList()) {
        if (as->getActiveTrain() == this) {
            sectionsToRelease->append(as);
        }
    }
    for (AllocatedSection* as : *sectionsToRelease) {
        DispatcherFrame::instance()->releaseAllocatedSection(as, true); // need to find Allocated Section
        as->getSection()->setState(Section::FREE);
    }
    if (mLastAllocatedSection != NULL) {
        mLastAllocatedSection->setState(Section::FREE);
    }
    resetAllAllocatedSections();
    clearAllocations();
    if (mAutoRun) {
        mAutoActiveTrain->allocateAFresh();
    }
    DispatcherFrame::instance()->allocateNewActiveTrain(this);
}

/*public*/ void ActiveTrain::clearAllocations() {
    for (AllocatedSection* as : *getAllocatedSectionList()) {
        removeAllocatedSection(as);
    }
}

/*public*/ QList<AllocatedSection*>* ActiveTrain::getAllocatedSectionList() {
    QList<AllocatedSection*>* list = new QList<AllocatedSection*>();
    for (int i = 0; i < mAllocatedSections->size(); i++) {
        list->append(mAllocatedSections->at(i));
    }
    return list;
}
#if 0
/**
 * Returns list of all Blocks occupied by or allocated to this train.
 * They are in order from the tail of the train to the head
 * of the train then on to the forward-most allocated block.
 * Note that unoccupied blocks can exist before and after the occupied
 * blocks.
 * TODO: doesn't handle reversing of adjacent mult-block sections well
 */
/*public*/ java.util.ArrayList<Block> getBlockList() {
    ArrayList<Block> list = new ArrayList<Block>();
    for (int i = 0; i < mAllocatedSections.size(); i++) { // loop thru allocated sections, then all blocks for each section
        Section s = mAllocatedSections.get(i).getSection();
        ArrayList<Block> bl = s.getBlockList();
        if (bl.size() > 1) { //sections with multiple blocks need extra logic

            bool blocksConnected = true;
            //determine if blocks should be added in forward or reverse order based on connectivity
            if (i==0) { //for first section, compare last block to first of next section
                if (mAllocatedSections.size() > 1 &&  //only one section, assume forward
                        !connected(bl.get(bl.size()-1), mAllocatedSections.get(i+1).getSection().getBlockList().get(0))) {
                    blocksConnected = false;
                }
            } else { //not first section, check for connectivity between last block in list, and first block in this section
                if (!connected(list.get(list.size()-1), bl.get(0))) { //last block is not connected to first block, add reverse
                    blocksConnected = false;
                }
            }
            if (blocksConnected) { //blocks were connected, so add to outgoing in forward order
                for (int j = 0; j < bl.size();j++) {
                    Block b = bl.get(j);
                    list.add(b);
                    log.trace("block {} ({}) added to list for Section {} (fwd)", b.getDisplayName(),
                            (b.getState()==Block.OCCUPIED?"OCCUPIED":"UNOCCUPIED"),
                            s.getDisplayName());
                }
            } else { //not connected, add in reverse order
                for (int j = bl.size()-1; j >= 0;j--) {
                    Block b = bl.get(j);
                    list.add(b);
                    log.trace("block {} ({}) added to list for Section {} (rev)", b.getDisplayName(),
                            (b.getState()==Block.OCCUPIED?"OCCUPIED":"UNOCCUPIED"),
                            s.getDisplayName());
                }
            }

        } else { //single block sections are simply added to the outgoing list
            Block b = bl.get(0);
            list.add(b);
            log.trace("block {} ({}) added to list for Section {} (one)", b.getDisplayName(),
                    (b.getState()==Block.OCCUPIED?"OCCUPIED":"UNOCCUPIED"),
                    s.getDisplayName());
        }
    }
    return list;
}

/* copied from Section.java */
/*private*/ bool connected(Block b1, Block b2) {
    if ((b1 != NULL) && (b2 != NULL)) {
        List<Path> paths = b1.getPaths();
        for (int i = 0; i < paths.size(); i++) {
            if (paths.get(i).getBlock() == b2) {
                return true;
            }
        }
    }
    return false;
}
#endif

/*public*/ Section* ActiveTrain::getLastAllocatedSection() {
    return mLastAllocatedSection;
}

/*public*/ QString ActiveTrain::getLastAllocatedSectionName() {
    if (mLastAllocatedSection == NULL) {
        return "<" + tr("None").toLower() + ">"; // <none>
    }
    return getSectionName(mLastAllocatedSection);
}

/*public*/ Section* ActiveTrain::getNextSectionToAllocate() {
    return mNextSectionToAllocate;
}

/*public*/ int ActiveTrain::getNextSectionSeqNumber() {
    return mNextSectionSeqNumber;
}

/*public*/ QString ActiveTrain::getNextSectionToAllocateName() {
    if (mNextSectionToAllocate == NULL) {
        return "<" + tr("None").toLower() + ">"; // <none>
    }
    return getSectionName(mNextSectionToAllocate);
}

/*private*/ QString ActiveTrain::getSectionName(Section* sc) {
    QString s = sc->getSystemName();
    QString u = sc->getUserName();
    if ((u != NULL) && (u != ("") && (u != (s)))) {
        return (s + "(" + u + ")");
    }
    return s;
}

/*public*/ Block* ActiveTrain::getStartBlock() {
    return mStartBlock;
}

/*public*/ void ActiveTrain::setStartBlock(Block* sBlock) {
    mStartBlock = sBlock;
}

/*public*/ int ActiveTrain::getStartBlockSectionSequenceNumber() {
    return mStartBlockSectionSequenceNumber;
}

/*public*/ void ActiveTrain::setStartBlockSectionSequenceNumber(int sBlockSeqNum) {
    mStartBlockSectionSequenceNumber = sBlockSeqNum;
}

/*public*/ Block* ActiveTrain::getEndBlock() {
    return mEndBlock;
}

/*public*/ void ActiveTrain::setEndBlock(Block* eBlock) {
    mEndBlock = eBlock;
}

/*public*/ Section* ActiveTrain::getEndBlockSection() {
    return mEndBlockSection;
}

/*public*/ void ActiveTrain::setEndBlockSection(Section* eSection) {
    mEndBlockSection = eSection;
}

/*public*/ int ActiveTrain::getEndBlockSectionSequenceNumber() {
    return mEndBlockSectionSequenceNumber;
}

/*public*/ void ActiveTrain::setEndBlockSectionSequenceNumber(int eBlockSeqNum) {
    mEndBlockSectionSequenceNumber = eBlockSeqNum;
}

/*public*/ int ActiveTrain::getPriority() {
    return mPriority;
}

/*public*/ void ActiveTrain::setPriority(int priority) {
    mPriority = priority;
}

/*public*/ bool ActiveTrain::getAutoRun() {
    return mAutoRun;
}

/*public*/ void ActiveTrain::setAutoRun(bool autoRun) {
    mAutoRun = autoRun;
}

/*public*/ QString ActiveTrain::getDccAddress() {
    return mDccAddress;
}

/*public*/ void ActiveTrain::setDccAddress(QString dccAddress) {
    mDccAddress = dccAddress;
}

/*public*/ bool ActiveTrain::getResetWhenDone() {
    return mResetWhenDone;
}

/*public*/ void ActiveTrain::setResetWhenDone(bool s) {
    mResetWhenDone = s;
}

/*public*/ bool ActiveTrain::getReverseAtEnd() {
    return mReverseAtEnd;
}

/*public*/ void ActiveTrain::setReverseAtEnd(bool s) {
    mReverseAtEnd = s;
}

/*public*/ bool ActiveTrain::getAllocateAllTheWay() {
    return mAllocateAllTheWay;
}

/*public*/ void ActiveTrain::setAllocateAllTheWay(bool s) {
    mAllocateAllTheWay = s;
}
#if 0
protected Section* getSecondAllocatedSection() {
    return mSecondAllocatedSection;
}
#endif
/**
 * Operating methods
 */
/*public*/ AllocationRequest* ActiveTrain::initializeFirstAllocation() {
    if (mAllocatedSections->size() > 0) {
        log->error("ERROR - Request to initialize first allocation, when allocations already present");
        return NULL;
    }
    if ((mStartBlockSectionSequenceNumber > 0) && (mStartBlock != NULL)) {
        mNextSectionToAllocate = mTransit->getSectionFromBlockAndSeq(mStartBlock,
                mStartBlockSectionSequenceNumber);
        if (mNextSectionToAllocate == NULL) {
            mNextSectionToAllocate = mTransit->getSectionFromConnectedBlockAndSeq(mStartBlock,
                    mStartBlockSectionSequenceNumber);
            if (mNextSectionToAllocate == NULL) {
                log->error("ERROR - Cannot find Section for first allocation of ActiveTrain"
                        + getActiveTrainName());
                return NULL;
            }
        }
        mNextSectionSeqNumber = mStartBlockSectionSequenceNumber;
        mNextSectionDirection = getAllocationDirectionFromSectionAndSeq(mNextSectionToAllocate,
                mNextSectionSeqNumber);
    } else {
        log->error("ERROR - Insufficient information to initialize first allocation");
        return NULL;
    }
    if (!DispatcherFrame::instance()->requestAllocation(this,
            mNextSectionToAllocate, mNextSectionDirection, mNextSectionSeqNumber, true, NULL)) {
        log->error("Allocation request failed for first allocation of " + getActiveTrainName());
    }
    if (DispatcherFrame::instance()->getRosterEntryInBlock() && getRosterEntry() != NULL) {
        mStartBlock->setValue(VPtr<RosterEntry>::asQVariant(getRosterEntry()));
     //mStartBlock->setValue(QVariant(getRosterEntry()));
    } else if (DispatcherFrame::instance()->getShortNameInBlock()) {
        mStartBlock->setValue(mTrainName);
    }
    AllocationRequest* ar = DispatcherFrame::instance()->findAllocationRequestInQueue(mNextSectionToAllocate,
            mNextSectionSeqNumber, mNextSectionDirection, this);
    return ar;
}
#if 0
protected bool addEndSection(Section* s, int seq) {
    AllocatedSection as = mAllocatedSections.get(mAllocatedSections.size() - 1);
    if (!as->setNextSection(s, seq)) {
        return false;
    }
    setEndBlockSection(s);
    setEndBlockSectionSequenceNumber(seq);
    //At this stage the section direction hasn't been set, by default the exit block returned is the reverse if the section is free
    setEndBlock(s.getExitBlock());
    mNextSectionSeqNumber = seq;
    mNextSectionToAllocate = s;
    return true;
}

/*This is for use where the transit has been extended, then the last section has been cancelled no
 checks are performed, these should be done by a higher level code*/
protected void removeLastAllocatedSection() {
    AllocatedSection as = mAllocatedSections.get(mAllocatedSections.size() - 1);
    //Set the end block using the AllocatedSections exit block before clearing the next section in the allocatedsection
    setEndBlock(as->getExitBlock());

    as->setNextSection(NULL, 0);
    setEndBlockSection(as->getSection());

    setEndBlockSectionSequenceNumber(getEndBlockSectionSequenceNumber() - 1);
    // In theory the following values should have already been set if there are no more sections to allocate.
    mNextSectionSeqNumber = 0;
    mNextSectionToAllocate = NULL;
}

protected AllocatedSection reverseAllAllocatedSections() {
    AllocatedSection aSec = NULL;
    for (int i = 0; i < mAllocatedSections.size(); i++) {
        aSec = mAllocatedSections.get(i);
        int dir = mTransit.getDirectionFromSectionAndSeq(aSec.getSection(), aSec.getSequence());
        if (dir == jmri.Section.FORWARD) {
            aSec.getSection().setState(jmri.Section.REVERSE);
        } else {
            aSec.getSection().setState(jmri.Section.FORWARD);
        }
        aSec.setStoppingSensors();
    }
    return aSec;
}
#endif
/*protected*/ void ActiveTrain::resetAllAllocatedSections() {
    for (int i = 0; i < mAllocatedSections->size(); i++) {
        AllocatedSection* aSec = mAllocatedSections->value(i);
        int dir = mTransit->getDirectionFromSectionAndSeq(aSec->getSection(), aSec->getSequence());
        aSec->getSection()->setState(dir);
        aSec->setStoppingSensors();
    }
}

/*protected*/ void ActiveTrain::setRestart() {
    if (getDelayedRestart() == NODELAY) {
        return;
    }

    setStatus(READY);
    restartPoint = true;
    if (getDelayedRestart() == TIMEDDELAY) {
        QDateTime now = ((Timebase*)InstanceManager::getDefault("Timebase"))->getTime();
        //@SuppressWarnings("deprecation")
        int nowHours = now.time().hour();
        //@SuppressWarnings("deprecation")
        int nowMinutes = now.time().minute();
        int hours = getRestartDelay() / 60;
        int minutes = getRestartDelay() % 60;
        restartHr = nowHours + hours + ((nowMinutes + minutes) / 60);
        restartMin = ((nowMinutes + minutes) % 60);
    }
    DispatcherFrame::instance()->addDelayedTrain(this);
}

/*protected*/ void ActiveTrain::holdAllocation(bool boo) {
    _holdAllocation = boo;
}

/*protected*/ bool ActiveTrain::holdAllocation() {
    return _holdAllocation;
}

/*protected*/ bool ActiveTrain::reachedRestartPoint() {
    return restartPoint;
}

/*protected*/ void ActiveTrain::restart() {
    restartPoint = false;
    _holdAllocation = false;
    setStatus(WAITING);
    if (mAutoActiveTrain != NULL) {
        mAutoActiveTrain->setupNewCurrentSignal(NULL);
    }
}
#if 0
/*public*/ void terminate() {
    DispatcherFrame.instance().removeDelayedTrain(this);
    if (getDelaySensor() != NULL && delaySensorListener != NULL) {
        getDelaySensor().removePropertyChangeListener(delaySensorListener);
    }
    if (getRestartSensor() != NULL && restartSensorListener != NULL) {
        getRestartSensor().removePropertyChangeListener(restartSensorListener);
    }
    mTransit.setState(jmri.Transit.IDLE);
}

/*public*/ void dispose() {
    getTransit().removeTemporarySections();
}


/*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener l) {
    pcs.addPropertyChangeListener(l);
}
#endif
/*protected*/ void ActiveTrain::firePropertyChange(QString p, QVariant old, QVariant n) {
    pcs->firePropertyChange(p, old, n);
}
/*public*/ /*synchronized*/ void ActiveTrain::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

