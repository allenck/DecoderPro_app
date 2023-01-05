#include "transit.h"
#include "transitsection.h"
#include "exceptions.h"
#include "section.h"
#include "block.h"
#include "transitsection.h"
#include "vptr.h"
#include "sensormanager.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"
#include "transitsection.h"
#include "transitsectionaction.h"
#include "jmriexception.h"

//Transit::Transit(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Class providing the basic implementation of a Transit.
 * <P>
 * Transits represent a group of Sections representing a specified path
 *  through a layout.
 * <P>
 * A Transit may have the following states.
 *		IDLE - indicating that it is available for "assignment"
 *      ASSIGNED - linked to a train to form an ActiveTrain
 * <P>
 * When assigned to a Transit, options may be set for the assigned Section.
 *  The Section and its options are kept in a TransitSection object.
 *<P>
 * To accomodate passing sidings and other track features, there may be
 *  alternate Sections connecting two Sections in a Transit.  If so, one
 *  Section is assigned as primary, and other Sections are assigned as
 *  alternates.
 * <P>
 * A Section may be in a Transit more than once, for example if a train is
 *  to make two or more loops around before going elsewhere.
 * <P>
 * A Transit is normally traversed in the forward direction, i.e., the
 *  direction of increasing Section Numbers. When a Transit traversal is
 *  started up, it is always started in the forward direction.  However,
 *  to accommodate point-to-point (back and forth) route designs, the
 *  direction of travel in a Transit may be "reversed".  While
 *  the Transit direction is "reversed", the direction of travel is the
 *  direction of decreasing Section numbers.  Whether a Transit is in the
 *  "reversed" direction is kept in the ActiveTrain using the Transit.
 * <p>
 * Transit system names are always upper case.
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation. See the "COPYING" file for
 * a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Dave Duchamp Copyright (C) 2008-2011
 *
 * @version			$Revision: 17977 $
 */
///*public*/ class Transit extends AbstractNamedBean
//                    implements java.io.Serializable {

/*public*/ Transit::Transit(QString systemName, QString userName, QObject *parent) :AbstractNamedBean(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpperCase(), userName);
    log = new Logger("Transit");
  mState = Transit::IDLE;
  mTransitSectionList = new QList<TransitSection*>();
  mMaxSequence = 0;
  blockSecSeqList = new QList<int>();
  destBlocksSeqList = new QList<int>();
 }

//    /*public*/ Transit(String systemName) {
//        super(systemName.toUpperCase());
//        /*private*/ int mState = Transit.IDLE;
//        /*private*/ QList<TransitSection> mTransitSectionList = new QList<TransitSection>();
//        /*private*/ int mMaxSequence = 0;

//    }



/**
 * Query the state of the Transit
 */
/*public*/ int Transit::getState() { return mState; }

/**
 * Set the state of the Transit
 */
/*public*/ void Transit::setState(int state) {
    if ( (state==Transit::IDLE) || (state==Transit::ASSIGNED) ) {
        int old = mState;
        mState = state;
        firePropertyChange("state", QVariant(old), QVariant(mState));
    }
    else
        log->error("Attempt to set Transit state to illegal value - "+state);
}

/**
 *  Add a TransitSection to the Transit
 *  Section sequence numnbers are set automatically as Sections are added.
 *	Returns "true" if Section was added.  Returns "false" if Section does not connect to
 *		the current Section.
 */
/*public*/ void Transit::addTransitSection(TransitSection* s) {
    mTransitSectionList->append(s);
    mMaxSequence = s->getSequenceNumber();
}

/**
 * Get a copy of this Transit's TransitSection list
 */
/*public*/ QList<TransitSection*> Transit::getTransitSectionList() {
    QList<TransitSection*> list = QList<TransitSection*>();
    for (int i = 0; i<mTransitSectionList->size(); i++)
        list.append(mTransitSectionList->at(i));
    return list;
}

/**
 * Get the maximum sequence number used in this Transit
 */
/*public*/ int Transit::getMaxSequence() {return mMaxSequence;}

/**
 * Remove all TransitSections
 */
/*public*/ void Transit::removeAllSections() {
    mTransitSectionList->clear();
}

/**
 * Test if a Section is in the Transit
 */
/*public*/ bool Transit::containsSection(Section* s) {
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (ts->getSection()==s) return true;
    }
    return false;
}

/**
 * Get a List of Sections with a given sequence number
 */
/*public*/ QList<Section*> Transit::getSectionListBySeq(int seq) {
    QList<Section*> list = QList<Section*>();
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (seq == ts->getSequenceNumber()) {
            list.append(ts->getSection());
        }
    }
    return list;
}

/**
 * Get a List of Transit Sections with a given sequence number
 */
/*public*/ QList<TransitSection*> Transit::getTransitSectionListBySeq(int seq) {
    QList<TransitSection*> list =  QList<TransitSection*>();
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (seq == ts->getSequenceNumber()) {
            list.append(ts);
        }
    }
    return list;
}

/**
 * Get a List of sequence numbers for a given Section
 */
/*public*/ QList<int>* Transit::getSeqListBySection(Section* s) {
    QList<int>* list = new QList<int>();
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (s == ts->getSection()) {
            list->append((ts->getSequenceNumber()));
        }
    }
    return list;
}

/**
 * Test if a Block is in the Transit
 */
/*public*/ bool Transit::containsBlock(Block* b) {
    QList<Block*>* bList = getInternalBlocksList();
    for (int i = 0; i<bList->size(); i++) {
        if (b == bList->at(i)) return true;
    }
    return false;
}

/**
 * Count the number of times a Block is in this Transit
 */
/*public*/ int Transit::getBlockCount(Block* b) {
    QList<Block*>* bList = getInternalBlocksList();
    int count = 0;
    for (int i = 0; i<bList->size(); i++) {
        if (b == bList->at(i)) count++;
    }
    return count;
}
/**
 * Returns a Section from one of its Blocks and its sequence number
 */
/*public*/ Section* Transit::getSectionFromBlockAndSeq(Block* b, int seq) {
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (ts->getSequenceNumber()==seq) {
            Section* s = ts->getSection();
            if (s->containsBlock(b)) return s;
        }
    }
    return NULL;
}
/**
 * Returns a Section from one of its EntryPoint Blocks and its sequence number
 */
/*public*/ Section* Transit::getSectionFromConnectedBlockAndSeq(Block* b, int seq) {
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if (ts->getSequenceNumber()==seq) {
            Section* s = ts->getSection();
            if (s->connectsToBlock(b)) return s;
        }
    }
    return NULL;
}
/**
 * Gets the direction of a Section in the transit from its sequence number
 *    Returns 0 if direction was not found.
 */
/*public*/ int Transit::getDirectionFromSectionAndSeq(Section* s, int seq) {
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if ( (ts->getSection() == s) && (ts->getSequenceNumber() == seq) ) {
            return ts->getDirection();
        }
    }
    return 0;
}
/**
 * Gets a TransitSection in the transit from its Section and Section sequence number
 *    Returns NULL if TransitSection was not found.
 */
/*public*/ TransitSection* Transit::getTransitSectionFromSectionAndSeq(Section* s, int seq) {
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        if ( (ts->getSection() == s) && (ts->getSequenceNumber() == seq) ) {
            return ts;
        }
    }
    return NULL;
}

/**
 * Get a list of all blocks internal to this Transit
 * Since Sections may be present more than once, blocks may be listed more than once.
 * The sequence numbers of the Section the Block was found in are accumulated in a
 *   parallel list, which can be accessed by immediately calling getBlockSeqList().
 */
/*public*/ QList<Block*>* Transit::getInternalBlocksList() {
    QList<Block*>* list = new QList<Block*>();
    blockSecSeqList->clear();
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        QVector<Block*>* bList = ts->getSection()->getBlockList();
        for (int j = 0; j<bList->size(); j++) {
            list->append(bList->at(j));
            blockSecSeqList->append((ts->getSequenceNumber()));
        }
    }
    return list;
}
// The following is mainly for internal use, but is available if requested immediately after
//      getInternalBlocksList or getEntryBlocksList.
/*public*/ QList<int>* Transit::getBlockSeqList() {
    QList<int>* list = new QList<int>();
    for (int i = 0; i<blockSecSeqList->size(); i++) {
        list->append(blockSecSeqList->at(i));
    }
    return list;
}

/**
 * Get a list of all entry blocks to this Transit.
 * These are Blocks that a train might enter from and be going in the
 *   Transit's direction.
 * The sequence numbers of the Section the Block will enter are accumulated in a
 *   parallel list, which can be accessed by immediately calling getBlockSeqList().
 */
/*public*/ QList<Block*>* Transit::getEntryBlocksList() {
    QList<Block*>* list = new QList<Block*>();
    QList<Block*>* internalBlocks = getInternalBlocksList();
    blockSecSeqList->clear();
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        TransitSection* ts = mTransitSectionList->at(i);
        QList<EntryPoint*>* ePointList = NULL;
        if (ts->getDirection()==Section::FORWARD)
            ePointList = ts->getSection()->getForwardEntryPointList();
        else
            ePointList = ts->getSection()->getReverseEntryPointList();
        for (int j=0; j<ePointList->size(); j++) {
            Block* b = (ePointList->at(j))->getFromBlock();
            bool isInternal = false;
            for (int k = 0; k<internalBlocks->size(); k++) {
                if (b==internalBlocks->at(k)) isInternal = true;
            }
            if (!isInternal) {
                // not an internal Block, keep it
                list->append(b);
                blockSecSeqList->append((ts->getSequenceNumber()));
            }
        }
    }
    return list;
}

/**
 * Get a list of all destination blocks that can be reached from a
 *   specified starting block, "startBlock". "startInTransit" should be set "true" if
 *   "startBlock" is in the Transit, and "false" otherwise.
 * The sequence numbers of the Section the Block was found in are accumulated in a
 *   parallel list, which can be accessed by immediately calling getDestBlocksSeqList().
 * Note: A train may not terminate in the same Section in which it starts!
 * Note: A train must terminate in a block within the transit!
 */
/*public*/ QList<Block*>* Transit::getDestinationBlocksList(Block* startBlock, bool startInTransit) {
    QList<Block*>* list = new QList<Block*>();
    destBlocksSeqList->clear();
    if (startBlock==NULL) return list;
    // get the sequence number of the Section of the starting Block
    int startSeq = -1;
    QList<Block*>* startBlocks = NULL;
    if (startInTransit) {
        startBlocks = getInternalBlocksList();
    }
    else {
        startBlocks = getEntryBlocksList();
    }
    // programming note: the above calls initialize blockSecSeqList->
    for (int k = 0; ((k<startBlocks->size()) && (startSeq==-1)); k++) {
        if (startBlock==startBlocks->at(k)) {
            startSeq = (blockSecSeqList->at(k));
        }
    }
    QList<Block*>* internalBlocks = getInternalBlocksList();
    for (int i = internalBlocks->size(); i>0; i--) {
        if ( ((blockSecSeqList->at(i-1)) ) > startSeq) {
            // could stop in this block, keep it
            list->append(internalBlocks->at(i-1));
            destBlocksSeqList->append(blockSecSeqList->at(i-1));
        }
    }
    return list;
}
/*public*/ QList<int>* Transit::getDestBlocksSeqList() {
    QList<int>* list = new QList<int>();
    for (int i = 0; i<destBlocksSeqList->size(); i++) {
        list->append(destBlocksSeqList->at(i));
    }
    return list;
}

/**
 * Determines whether this Transit is capable of continuous running.  That is, after an
 *	   Active Train completes the Transit, can it automatically be set up to start again?
 *  To be resetable, the first Section and the last Section must be the same Section, and
 *	   the first and last Sections must be defined to run in the same direction.
 *  If the last Section is an alternate Section, the previous Section is tested. However,
 *	   if the Active Train does not complete it's Transit in the same Section it started
 *     in, the restart will not take place.
 * Returns 'true' if continuous running is possible, returns 'false' otherwise.
 */
/*public*/ bool Transit::canBeResetWhenDone() {
    TransitSection* firstTS = mTransitSectionList->at(0);
    int lastIndex = mTransitSectionList->size()-1;
    TransitSection* lastTS = mTransitSectionList->at(lastIndex);
    bool OK = false;
    while (!OK) {
        if (firstTS->getSection() != lastTS->getSection()) {
            if ( lastTS->isAlternate() && (lastIndex>1) ) {
                lastIndex --;
                lastTS = mTransitSectionList->at(lastIndex);
            }
            else {
                log->warn("Section mismatch "+(firstTS->getSection())->getSystemName()+" "+
                    (lastTS->getSection())->getSystemName());
                return false;
            }
        }
        OK = true;
    }
    // same Section, check direction
    if (firstTS->getDirection() != lastTS->getDirection()) {
        log->warn("Direction mismatch "+(firstTS->getSection())->getSystemName()+" "+
                    (lastTS->getSection())->getSystemName());
        return false;
    }
    return true;
}

/**
 * Checks that exit Signal Heads are in place for all Sections in this Transit and for
 *		block boundaries at turnouts or level crossings within Sections of the Transit for
 *		the direction defined in this Transit.
 * Signal Heads are not required at anchor point block boundaries where both blocks are
 *		within the same Section, and for turnouts with two or more connections in the same Section.
 * Returns "true" if everything is OK. Sends message to the user if a signal head is missing,
 *		and returns 'false'. Quits looking after finding the first missing signal head.
 */
/*public*/ int Transit::checkSignals(LayoutEditor* panel) {
    if (panel==NULL) {
        log->error("checkSignals called with a NULL LayoutEditor panel");
        return -1;
    }
    int numErrors = 0;
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        int n = mTransitSectionList->at(i)->getSection()->placeDirectionSensors(panel);
        numErrors = numErrors + n;
    }
    return numErrors;
}

/**
 * Validates connectivity through the Transit.
 * Returns the number of errors found. Sends log messages detailing the errors if break
 *      in connectivity is detected. Checks all Sections before quitting.
 */
/*public*/ int Transit::validateConnectivity(LayoutEditor* panel) {
    if (panel==NULL) {
        log->error("validateConnectivity called with a NULL LayoutEditor panel");
        return -1;
    }
    int numErrors = 0;
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        QString s = mTransitSectionList->at(i)->getSection()->validate(panel);
        if (s!=("")) {
            log->error(s);
            numErrors ++;
        }
    }
    return numErrors;
}

/**
 * Initializes blocking sensors for Sections in this Transit
 *    This should be done before any Sections are allocated for this Transit.
 *    Only Sections that are FREE are initialized, so as not to interfere with running
 *			active trains.
 *    If any Section does not have blocking sensors, warning messages are logged.
 *	  Returns 0 if no errors, number of errors otherwise.
 */
/*public*/ int Transit::initializeBlockingSensors() {
    int numErrors = 0;
    for (int i = 0; i<mTransitSectionList->size(); i++) {
        Section* s = mTransitSectionList->at(i)->getSection();
        try {
            if (s->getForwardBlockingSensor()!=NULL) {
                if (s->getState() == Section::FREE) {
                    s->getForwardBlockingSensor()->setState(Sensor::ACTIVE);
                }
            }
            else {
                log->warn("Missing forward blocking sensor for section "+s->getSystemName());
                numErrors ++;
            }
        } catch (JmriException* reason) {
            log->error ("Exception when initializing forward blocking Sensor for Section "+s->getSystemName());
            numErrors ++;
        }
        try {
            if (s->getReverseBlockingSensor()!=NULL) {
                if (s->getState() == Section::FREE) {
                    s->getReverseBlockingSensor()->setState(Sensor::ACTIVE);
                }
            }
            else {
                log->warn("Missing reverse blocking sensor for section "+s->getSystemName());
                numErrors ++;
            }
        } catch (JmriException* reason) {
            log->error ("Exception when initializing reverse blocking Sensor for Section "+s->getSystemName());
            numErrors ++;
        }
    }
    return numErrors;
}

//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "UC_USELESS_OBJECT",
//            justification = "SpotBugs doesn't see that toBeRemoved is being read by the forEach clause")
/*public*/ void Transit::removeTemporarySections() {
    QList<TransitSection*> toBeRemoved = QList<TransitSection*>();
    for (TransitSection* ts : *mTransitSectionList) {
        if (ts->isTemporary()) {
            toBeRemoved.append(ts);
        }
    }
    //toBeRemoved.forEach((ts) -> {
    foreach(TransitSection* ts, toBeRemoved)
    {
     mTransitSectionList->removeOne(ts);

    }//);
}

/*public*/ bool Transit::removeLastTemporarySection(Section* s) {
    TransitSection* last = mTransitSectionList->at(mTransitSectionList->size() - 1);
    if (last->getSection() != s) {
        log->info("Section asked to be removed is not the last one");
        return false;
    }
    if (!last->isTemporary()) {
        log->info("Section asked to be removed is not a temporary section");
        return false;
    }
    mTransitSectionList->removeOne(last);
    return true;

}

//@Override
/*public*/ QString Transit::getBeanType() {
    return tr("Transit");
}

//@Override
/*public*/ void Transit::vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // NOI18N
        NamedBean* nb =  VPtr<NamedBean>::asPtr(evt->getOldValue());
        if (static_cast<Section*>(nb->self())) {
            if (containsSection((Section*) nb->self())) {
                throw new PropertyVetoException(tr("Is in use with Transit %1").arg(getDisplayName()), evt);
            }
        }
    }
    // we ignore the property setConfigureManager
}
//@Override
/*public*/ QList<NamedBeanUsageReport *> *Transit::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*>* report = new QList<NamedBeanUsageReport*>();
    SensorManager* sm = (SensorManager*)InstanceManager::getDefault("SensorManager");
    SignalHeadManager* head = (SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager");
    SignalMastManager* mast = (SignalMastManager*)InstanceManager::getDefault("SignalMastManager");
    if (bean != nullptr) {
        //getTransitSectionList().forEach((transitSection) ->
          for(TransitSection* transitSection : getTransitSectionList())
        {
            if (bean->equals(transitSection->getSection())) {
                report->append(new NamedBeanUsageReport("TransitSection"));
            }
            if (bean->equals(sm->getSensor(transitSection->getStopAllocatingSensor()))) {
                report->append(new NamedBeanUsageReport("TransitSensorStopAllocation"));
            }
            // Process actions
            //transitSection->getTransitSectionActionList().forEach((action) ->
            for(TransitSectionAction* action : *transitSection->getTransitSectionActionList())
            {
                int whenCode = action->getWhenCode();
                int whatCode = action->getWhatCode();
                if (whenCode == TransitSectionAction::SENSORACTIVE || whenCode == TransitSectionAction::SENSORINACTIVE) {
                    if (bean->equals(sm->getSensor(action->getStringWhen()))) {
                        report->append(new NamedBeanUsageReport("TransitActionSensorWhen", transitSection->getSection()));
                    }
                }
                if (whatCode == TransitSectionAction::SETSENSORACTIVE || whatCode == TransitSectionAction::SETSENSORINACTIVE) {
                    if (bean->equals(sm->getSensor(action->getStringWhat()))) {
                        report->append(new NamedBeanUsageReport("TransitActionSensorWhat", transitSection->getSection()));
                    }
                }
                if (whatCode == TransitSectionAction::HOLDSIGNAL || whatCode == TransitSectionAction::RELEASESIGNAL) {
                    // Could be a signal head or a signal mast.
                    if (bean->equals(head->getSignalHead(action->getStringWhat()))) {
                        report->append(new NamedBeanUsageReport("TransitActionSignalHeadWhat", transitSection->getSection()));
                    }
                    if (bean->equals(mast->getSignalMast(action->getStringWhat()))) {
                        report->append(new NamedBeanUsageReport("TransitActionSignalMastWhat", transitSection->getSection()));
                    }
                }
            }//);
        }//);
    }
    return report;
}

//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(Transit.class.getName());

