#include "allocatedsection.h"
#include "section.h"
#include "activetrain.h"
#include "dispatcherframe.h"
#include "logger.h"
#include "transitsection.h"
#include "transit.h"
#include "eventlistenerlist.h"
#include "instancemanager.h"
#include "autoactivetrain.h"
#include "sleeperthread.h"

//AllocatedSection::AllocatedSection(QObject *parent) : QObject(parent)
//{

//}
/**
 * This class holds information and options for an AllocatedSection, a Section
 * that is currently allocated to an ActiveTrain.
 * <P>
 * AllocatedSections are referenced via a list in DispatcherFrame, which serves
 * as a manager for AllocatedSection objects. Each ActiveTrain also maintains a
 * list of AllocatedSections currently assigned to it.
 * <P>
 * AllocatedSections are transient, and are not saved to disk.
 * <P>
 * AllocatedSections keep track of whether they have been entered and exited.
 * <P>
 * If the Active Train this Section is assigned to is being run automatically,
 * support is provided for monitoring Section changes and changes for Blocks
 * within the Section.
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
 *
 * @author	Dave Duchamp Copyright (C) 2008-2011
 */
///*public*/ class AllocatedSection {

/**
 * Main constructor method
 *
 * @param s cannot be NULL
 */
/*public*/ AllocatedSection::AllocatedSection(Section* s, ActiveTrain* at, int seq, Section* next, int nextSeqNo) {
 log = new Logger("AllocatedSection");
 // instance variables
 mSection = NULL;
 mActiveTrain = NULL;
 mSequence = 0;
 mNextSection = NULL;
 mNextSectionSequence = 0;
 mSectionListener = NULL;
 mEntered = false;
 mExited = false;
 mAllocationNumber = 0;     // used to keep track of allocation order
 mForwardStoppingSensor = NULL;
  mReverseStoppingSensor = NULL;


  // instance variables used with automatic running of trains
  mIndex = 0;
  mExitSignalListener = NULL;
  mBlockListeners
          = new QList<PropertyChangeListener*>();
  mBlockList = NULL;
  mActiveBlockList = new QList<Block*>();

    mSection = s;
    mActiveTrain = at;
    mSequence = seq;
    mNextSection = next;
    mNextSectionSequence = nextSeqNo;
    if (mSection->getOccupancy() == Section::OCCUPIED) {
        mEntered = true;
    }
    // listen for changes in Section occupancy
#if 1
    mSection->addPropertyChangeListener(mSectionListener = new ASSPropertyChangeListener(this));
//    {
//        @Override
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            handleSectionChange(e);
//        }
//    });

    setStoppingSensors();
    if ((mActiveTrain->getAutoActiveTrain() == NULL) && !((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSupportVSDecoder())
    {
        // for manual running, monitor block occupancy for selected Blocks only
        if (mActiveTrain->getReverseAtEnd()
                && ((mSequence == mActiveTrain->getEndBlockSectionSequenceNumber())
                || (mActiveTrain->getResetWhenDone()
                && (mSequence == mActiveTrain->getStartBlockSectionSequenceNumber())))) {
            initializeMonitorBlockOccupancy();
        }
    } else {
        // monitor block occupancy for all Sections of automatially running trains
        initializeMonitorBlockOccupancy();
    }
    listenerList = new EventListenerList();
#endif
}

//static final ResourceBundle rb = ResourceBundle
//        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");


/**
 * Access methods
 */
/*public*/ Section* AllocatedSection::getSection() {
    return mSection;
}

/*public*/ QString AllocatedSection::getSectionName() {
    QString s = mSection->getSystemName();
    QString u = mSection->getUserName();
    if ((u != NULL) && (u != ("") && (u !=(s)))) {
        return (s + "(" + u + ")");
    }
    return s;
}

/*public*/ ActiveTrain* AllocatedSection::getActiveTrain() {
    return mActiveTrain;
}

/*public*/ QString AllocatedSection::getActiveTrainName() {
    return (mActiveTrain->getTrainName() + "/" + mActiveTrain->getTransitName());
}

/*public*/ int AllocatedSection::getSequence() {
    return mSequence;
}

/*public*/ Section* AllocatedSection::getNextSection() {
    return mNextSection;
}

/*public*/ int AllocatedSection::getNextSectionSequence() {
    return mNextSectionSequence;
}

 /*protected*/ bool AllocatedSection::setNextSection(Section* sec, int i) {
    if (sec == NULL) {
        mNextSection = NULL;
        mNextSectionSequence = i;
        return true;
    }
    if (mNextSection != NULL) {
        log->error("Next section is already set");
        return false;
    }
    mNextSection = sec;
    return true;
}

/*public*/ void AllocatedSection::setNextSectionSequence(int i) {
    mNextSectionSequence = i;
}

/*public*/ bool AllocatedSection::getEntered() {
    return mEntered;
}

/*public*/ bool AllocatedSection::getExited() {
    return mExited;
}

/*public*/ int AllocatedSection::getAllocationNumber() {
    return mAllocationNumber;
}

/*public*/ void AllocatedSection::setAllocationNumber(int n) {
    mAllocationNumber = n;
}

/*public*/ Sensor* AllocatedSection::getForwardStoppingSensor() {
    return mForwardStoppingSensor;
}

/*public*/ Sensor* AllocatedSection::getReverseStoppingSensor() {
    return mReverseStoppingSensor;
}

/**
 * Access methods for automatic running instance variables
 */
/*public*/ void AllocatedSection::setIndex(int i) {
    mIndex = i;
}

/*public*/ int AllocatedSection::getIndex() {
    return mIndex;
}

/*public*/ void AllocatedSection::setExitSignalListener(PropertyChangeListener* xSigListener) {
    mExitSignalListener = xSigListener;
}

/*public*/ PropertyChangeListener* AllocatedSection::getExitSignalListener() {
    return mExitSignalListener;
}

/**
 * Methods
 */
 /*protected*/ void AllocatedSection::setStoppingSensors() {
    if (mSection->getState() == Section::FORWARD) {
        mForwardStoppingSensor = mSection->getForwardStoppingSensor();
        mReverseStoppingSensor = mSection->getReverseStoppingSensor();
    } else {
        mForwardStoppingSensor = mSection->getReverseStoppingSensor();
        mReverseStoppingSensor = mSection->getForwardStoppingSensor();
    }
}

 /*protected*/ TransitSection* AllocatedSection::getTransitSection() {
    return (mActiveTrain->getTransit()->getTransitSectionFromSectionAndSeq(mSection, mSequence));
}

/*public*/ int AllocatedSection::getDirection() {
    return mSection->getState();
}

/*public*/ int AllocatedSection::getLength() {
    return mSection->getLengthI(((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getUseScaleMeters(),
            ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getScale());
}

/*public*/ void AllocatedSection::reset() {
    mExited = false;
    mEntered = false;
    if (mSection->getOccupancy() == Section::OCCUPIED) {
        mEntered = true;
    }
}
#if 1
/*private*/ /*synchronized*/ void AllocatedSection::handleSectionChange(PropertyChangeEvent* e) {
    if (mSection->getOccupancy() == Section::OCCUPIED) {
        mEntered = true;
    } else if (mSection->getOccupancy() == Section::UNOCCUPIED) {
        if (mEntered) {
            mExited = true;
        }
    }
    if (mActiveTrain->getAutoActiveTrain() != NULL) {
        if (e->getPropertyName() == ("state")) {
            mActiveTrain->getAutoActiveTrain()->handleSectionStateChange(this);
        } else if (e->getPropertyName() == ("occupancy")) {
            mActiveTrain->getAutoActiveTrain()->handleSectionOccupancyChange(this);
        }
    }

//       if (mEntered && !mExited && mActiveTrain.getResetWhenDone() && mActiveTrain.getDelayedRestart() != ActiveTrain.NODELAY) {
//           if (getSequence() == mActiveTrain.getEndBlockSectionSequenceNumber()) {
//               mActiveTrain.setRestart();
//           }
//       }

    ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->sectionOccupancyChanged();
}
#endif
/*public*/ /*synchronized*/ void AllocatedSection::initializeMonitorBlockOccupancy() {
    if (mBlockList != NULL) {
        return;
    }
    mBlockList = mSection->getBlockList();
#if 1
    for (int i = 0; i < mBlockList->size(); i++) {
        PropertyChangeListener* listener = NULL;
        Block* b = mBlockList->at(i);
        if (b != NULL) {
            /*final*/ int index = i;  // block index
            b->addPropertyChangeListener(listener = new ASBPropertyChangeListener(this, index));
//            {
//                @Override
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    handleBlockChange(index, e);
//                }
//            });
            mBlockListeners->append(listener);
        }
    }
#endif
}

/*private*/ /*synchronized*/ void AllocatedSection::handleBlockChange(int index, PropertyChangeEvent* e) {
    if (e->getPropertyName()==("state")) {
        if (mBlockList == NULL) {
            mBlockList = mSection->getBlockList();
        }

        Block* b = mBlockList->at(index);
        if (!isInActiveBlockList(b)) {
            int occ = b->getState();
#if 1
            Runnable* handleBlockChange = new RespondToBlockStateChange(b, occ, this);
            Thread* tBlockChange = new Thread(handleBlockChange, "Allocated Section Block Change on " + b->getDisplayName());
            tBlockChange->start();
#endif
            addToActiveBlockList(b);
            if (((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->getSupportVSDecoder()) {
                firePropertyChangeEvent("BlockStateChange", QVariant(), b->getSystemName()); // NOI18N
            }
        }
    }
}

 /*protected*/ Block* AllocatedSection::getExitBlock() {
    if (mNextSection == NULL) {
        return NULL;
    }
    EntryPoint* ep = mSection->getExitPointToSection(mNextSection, mSection->getState());
    if (ep != NULL) {
        return ep->getBlock();
    }
    return NULL;
}

 /*protected*/ Block* AllocatedSection::getEnterBlock(AllocatedSection* previousAllocatedSection) {
    if (previousAllocatedSection == NULL) {
        return NULL;
    }
    Section* sPrev = previousAllocatedSection->getSection();
    EntryPoint* ep = mSection->getEntryPointFromSection(sPrev, mSection->getState());
    if (ep != NULL) {
        return ep->getBlock();
    }
    return NULL;
}

 /*protected*/ /*synchronized*/ void AllocatedSection::addToActiveBlockList(Block* b) {
    if (b != NULL) {
        mActiveBlockList->append(b);
    }
}

 /*protected*/ /*synchronized*/ void AllocatedSection::removeFromActiveBlockList(Block* b) {
    if (b != NULL) {
        for (int i = 0; i < mActiveBlockList->size(); i++) {
            if (b == mActiveBlockList->at(i)) {
                mActiveBlockList->removeAt(i);
                return;
            }
        }
    }
}

 /*protected*/ /*synchronized*/ bool AllocatedSection::isInActiveBlockList(Block* b) {
    if (b != NULL) {
        for (int i = 0; i < mActiveBlockList->size(); i++) {
            if (b == mActiveBlockList->at(i)) {
                return true;
            }
        }
    }
    return false;
}

/*public*/ /*synchronized*/ void AllocatedSection::dispose() {
    if ((mSectionListener != NULL) && (mSection != NULL)) {
        mSection->removePropertyChangeListener(mSectionListener);
    }
    mSectionListener = NULL;
    for (int i = mBlockListeners->size(); i > 0; i--) {
        Block* b = mBlockList->at(i - 1);
        b->removePropertyChangeListener(mBlockListeners->at(i - 1));
    }
}
#if 1
// _________________________________________________________________________________________
// This class responds to Block state change in a separate thread
//class RespondToBlockStateChange implements Runnable {

    /*public*/ RespondToBlockStateChange::RespondToBlockStateChange(Block* b, int occ, AllocatedSection* as) {
        _block = b;
        _aSection = as;
        _occ = occ;
    }

    //@Override
    /*public*/ void RespondToBlockStateChange::run() {
        // delay to insure that change is not a short spike
        try {
            SleeperThread::msleep(_delay);
        } catch (InterruptedException exc) {
            // ignore this exception
        }
        if (_occ == _block->getState()) {
            // occupancy has not changed, must be OK
            if (_aSection->mActiveTrain->getAutoActiveTrain() != NULL) {
                // automatically running train
                _aSection->mActiveTrain->getAutoActiveTrain()->handleBlockStateChange(_aSection, _block);
            } else if (_occ == Block::OCCUPIED) {
                // manual running train - block newly occupied
                if ((_block == _aSection->mActiveTrain->getEndBlock()) && _aSection->mActiveTrain->getReverseAtEnd()) {
                    // reverse direction of Allocated Sections
                    _aSection->mActiveTrain->reverseAllAllocatedSections();
                } else if ((_block == _aSection->mActiveTrain->getStartBlock()) && _aSection->mActiveTrain->getResetWhenDone()) {
                    // reset the direction of Allocated Sections
                    _aSection->mActiveTrain->resetAllAllocatedSections();
                }
            }
        }
        // remove from lists
        _aSection->removeFromActiveBlockList(_block);
    }
//    /*private*/ int _delay = 250;
//    /*private*/ jmri.Block _block = NULL;
//    /*private*/ int _occ = 0;
//    /*private*/ AllocatedSection _aSection = NULL;
//};

/*public*/ void AllocatedSection::addPropertyChangeListener(PropertyChangeListener* listener) {
    log->debug(QString("Adding listener ") + listener->pself()->metaObject()->className() + " to " + this->metaObject()->className());
    listenerList->add("PropertyChangeListener", (EventListener*)listener);
}

/*public*/ void AllocatedSection::removePropertyChangeListener(PropertyChangeListener* listener) {
    listenerList->remove("PropertyChangeListener", (EventListener*)listener);
}
#endif
 /*protected*/ void AllocatedSection::firePropertyChangeEvent(PropertyChangeEvent* evt) {
    //Object[] listeners = listenerList.getListenerList();

//    foreach (PropertyChangeListener* l, listenerList->getListeners("PropertyChangeListener")) {
//        l->propertyChange(evt);
//    }
}

 /*protected*/ void AllocatedSection::firePropertyChangeEvent(QString name, QVariant oldVal, QVariant newVal) {
    log->debug("Firing property change: " + name + " " + newVal.toString());
    firePropertyChangeEvent(new PropertyChangeEvent(this, name, oldVal, newVal));
}

