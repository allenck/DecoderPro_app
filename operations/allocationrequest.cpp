#include "allocationrequest.h"
#include "block.h"
#include "section.h"
#include "activetrain.h"
#include "dispatcherframe.h"
#include "signalmast.h"
#include "instancemanager.h"

//AllocationRequest::AllocationRequest(QObject *parent) : QObject(parent)
//{

//}
/**
 * This class holds information and options for an AllocationRequestt.
 * <P>
 * An AllocationRequest holds the following information: Section to be allocated
 * Active Train requesting the allocation
 * <P>
 * A AllocationRequests is referenced via a list in DispatcherFrame, which
 * serves as a manager for AllocationRequest objects.
 * <P>
 * AllocationRequests are transient, and are not saved to disk.
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
 * @author	Dave Duchamp Copyright (C) 2008-2010
 */
///*public*/ class AllocationRequest {

/**
 * Main constructor method
 */
/*public*/ AllocationRequest::AllocationRequest(Section* s, int num, int dir, ActiveTrain* at)
{
 mWaitingOnBlock = NULL;
 mSignalMastListener = NULL;
 mWaitingForSignalMast = NULL;
 mWaitingOnBlockListener = NULL;


    mSection = s;
    mActiveTrain = at;
    mSectionSeqNum = num;
    mSectionDirection = dir;
    // listen for changes in Section occupancy
    if (mSection != NULL) {
//        mSection.addPropertyChangeListener(mSectionListener = new java.beans.PropertyChangeListener() {
//            @Override
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                handleSectionChange(e);
//            }
//        });
    }
}

/*public*/ void AllocationRequest::propertyChange(PropertyChangeEvent* e)
{
 // instance variables
 mSection = NULL;
 mActiveTrain = NULL;
 mSectionSeqNum = 0;
 mSectionDirection = Section::UNKNOWN;
 mSectionListener = NULL;
 // instance variables related to automatic allocation of Sections
 mWaitingForTrain = false;
 mMeetingTrainList = new QList<ActiveTrain*>();

 handleSectionChange(e);
}

//static final ResourceBundle rb = ResourceBundle
//        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");


/**
 * Access methods
 */
/*public*/ Section* AllocationRequest::getSection() {
    return mSection;
}

/*public*/ QString AllocationRequest::getSectionName() {
    QString s = mSection->getSystemName();
    QString u = mSection->getUserName();
    if ((u != NULL) && (u != ("") && (u != (s)))) {
        return (s + "(" + u + ")");
    }
    return s;
}

/*protected*/ ActiveTrain* AllocationRequest::getActiveTrain() {
    return mActiveTrain;
}

/*protected*/ QString AllocationRequest::getActiveTrainName() {
    return (mActiveTrain->getTrainName() + "/" + mActiveTrain->getTransitName());
}

/*protected*/ int AllocationRequest::getSectionSeqNumber() {
    return mSectionSeqNum;
}

/*protected*/ int AllocationRequest::getSectionDirection() {
    return mSectionDirection;
}

/*protected*/ QString AllocationRequest::getSectionDirectionName() {
    if (mSectionDirection == Section::FORWARD) {
        return tr("FORWARD");
    }
    if (mSectionDirection == Section::REVERSE) {
        return tr("REVERSE");
    }
    return tr("UNKNOWN");
}

/*protected*/ bool AllocationRequest::getWaitingForTrain() {
    return mWaitingForTrain;
}

/*protected*/ void AllocationRequest::setWaitingForTrain(bool set) {
    mWaitingForTrain = set;
}

/*protected*/ void AllocationRequest::addMeetingTrain(ActiveTrain* at) {
    mMeetingTrainList->append(at);
}

/*protected*/ void AllocationRequest::removeMeetingTrain(ActiveTrain* at) {
    for (int i = 0; i < mMeetingTrainList->size(); i++) {
        if (at == mMeetingTrainList->at(i)) {
            mMeetingTrainList->removeAt(i);
            return;
        }
    }
}

/*protected*/ QList<ActiveTrain*>* AllocationRequest::getMeetingTrainList() {
    return mMeetingTrainList;
}

/**
 * Methods
 */
/*private*/ void AllocationRequest::handleSectionChange(PropertyChangeEvent* e) {
    DispatcherFrame::instance()->sectionOccupancyChanged();
    //This forces us to rescan the allocation list if the section has gone unoccupied, thus this might get re-allocated
    if (e->getPropertyName() == ("occupancy")) {
        if (( e->getNewValue()).toInt() == Section::UNOCCUPIED) {
            ((DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame"))->queueScanOfAllocationRequests();
        }
    }
}

/*public*/ void AllocationRequest::dispose() {
    if ((mSectionListener != NULL) && (mSection != NULL)) {
        mSection->removePropertyChangeListener(mSectionListener);
    }
#if 0
    if ((mSignalMastListener != NULL) && (mWaitingForSignalMast != NULL)) {
        mWaitingForSignalMast.removePropertyChangeListener(mSignalMastListener);
    }

    if ((mWaitingOnBlock != NULL) && (mWaitingOnBlockListener != NULL)) {
        mWaitingOnBlock.removePropertyChangeListener(mWaitingOnBlockListener);
    }
#endif
    mWaitingOnBlock = NULL;
    mWaitingOnBlockListener = NULL;
    mSignalMastListener = NULL;
    mWaitingForSignalMast = NULL;
    mSectionListener = NULL;
    mSection = NULL;
    mActiveTrain = NULL;
}


/*public*/ void AllocationRequest::setWaitingForSignalMast(SignalMast* sm) {
    if (mSignalMastListener == NULL) {
#if 0
        mSignalMastListener = new PropertyChangeListener() {
            //@Override
            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                if (e.getPropertyName() == ("Held")) {
                    if (!((Boolean) e.getNewValue()).booleanValue()) {
                        mWaitingForSignalMast.removePropertyChangeListener(mSignalMastListener);
                        DispatcherFrame::instance().forceScanOfAllocation();
                    }
                }
            }
        };
#endif
    }
#if 0
    if (mWaitingForSignalMast != NULL) {
        mWaitingForSignalMast.removePropertyChangeListener(mSignalMastListener);
    }
    mWaitingForSignalMast = sm;
    if (mWaitingForSignalMast != NULL) {
        mWaitingForSignalMast.addPropertyChangeListener(mSignalMastListener);
    }
#endif
}


/*protected*/ void AllocationRequest::setWaitingOnBlock(Block* b) {
#if 0
    if (mWaitingOnBlockListener == NULL) {
        mWaitingOnBlockListener = new PropertyChangeListener() {
            //@Override
            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
                if (e.getPropertyName() == ("state")) {
                    if (((Integer) e.getNewValue()).intValue() == jmri.Block.UNOCCUPIED) {
                        mWaitingOnBlock.removePropertyChangeListener(mWaitingOnBlockListener);
                        DispatcherFrame.instance().forceScanOfAllocation();
                    }
                }
            }
        };
    }
    if (mWaitingOnBlock != NULL) {
        mWaitingOnBlock.removePropertyChangeListener(mWaitingOnBlockListener);
    }
    mWaitingOnBlock = b;
    if (mWaitingOnBlock != NULL) {
        mWaitingOnBlock.addPropertyChangeListener(mWaitingOnBlockListener);
    }
#endif
}
