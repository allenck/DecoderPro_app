#include "autoallocate.h"
#include "logger.h"
#include "dispatcherframe.h"
#include "layouteditor.h"
#include "activetrain.h"
#include "allocationrequest.h"
#include "allocationplan.h"
#include "signalmast.h"
#include "transit.h"
#include "taskallocaterelease.h"

//AutoAllocate::AutoAllocate(QObject *parent) : QObject(parent)
//{

//}
/**
 * Handles automatic allocation of Sections for Dispatcher
 * <P>
 * AutoAllocate.java is an extension of DispatcherFrame.java.
 * <P>
 * When AutoAllocate is triggered, it scans the list of Allocation Requests, in
 * order of the priorities of ActiveTrains with pending AllocationRequests,
 * testing if a requested allocation can be made. AutoAllocate returns when
 * either: A Section has been allocated -or- All AllocationRequests have been
 * tested, and no allocation is indicated.
 * <P>
 * If AutoAllocate needs to save information related to a plan requiring
 * multiple allocations, an AllocationPlan object is created. When the plan is
 * complete, the AllocationPlan object is disposed of. Multiple AllocationPlan
 * objects may be active at any one time.
 * <P>
 * AutoAllocate is triggered by each of the following events: An
 * AllocatedSection has been released, freeing up a Section. A new
 * AllocationRequest has been entered into the queue of AllocationRequests. A
 * Section has been allocated, either by AutoAllocate or manually by the
 * dispatcher.
 * <P>
 * AutoAllocate requires that AutoRelease is active and that Dispatcher has a
 * LayoutEditor panel.
 * <P>
 * AutoAllocate operates conservatively, that is, if there is any doubt that a
 * Section should be allocated, it will not allocate the Section.
 * <P>
 * AutoAllocate develops plans for meets when multiple ActiveTrains are using
 * the same Sections of track. These plans are automatically created and
 * removed. They are stored in AllocationPlan objects to avoid having to
 * continually recreate them, since the logic to create them is rather
 * complicated.
 * <P>
 * The dispatcher is free to switch AutoAllocate on or off at any tine in
 * DispatcherFrame. When AutoAllocate is switched off, all existing
 * AllocationPlan objects are discarded.
 * <P>
 *
 * <BR>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * </P><P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * </P>
 *
 * @author	Dave Duchamp Copyright (C) 2011
 */
///*public*/ class AutoAllocate {

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");

/*public*/ AutoAllocate::AutoAllocate(DispatcherFrame* d, QList<AllocationRequest*>* inAllocationRequests, QObject* parent)
 : Runnable(parent)
{
 log = new Logger("AutoAllocate");
 // operational variables
 _dispatcher = NULL;
 _conUtil = NULL;
 _planList = new QList<AllocationPlan*>();
 nextPlanNum = 1;
 orderedRequests = new QList<AllocationRequest*>();

    _dispatcher = d;
     allocationRequests = inAllocationRequests;
    if (_dispatcher == NULL) {
        log->error("NULL DispatcherFrame when constructing AutoAllocate");
        return;
    }
    if (_dispatcher->getLayoutEditor() == NULL) {
        log->error("NULL LayoutEditor when constructing AutoAllocate");
        return;
    }
    _conUtil = _dispatcher->getLayoutEditor()->getConnectivityUtil();
}
/**
 * Stops the autoAllocate nicely
 */
/*protected*/ void AutoAllocate::setAbort() {
    abort = true;
    scanAllocationRequests(new TaskAllocateRelease(TaskAllocateRelease::TaskAction::ABORT)); //force queue flush
}

/*
 * return true when the taskList queue is Empty
 */
/*protected*/ bool AutoAllocate::allRequestsDone() {
    return taskList->isEmpty();
}

/*protected*/ void AutoAllocate::scanAllocationRequests(TaskAllocateRelease* task) {
        taskList->append(task);
}
/**
 * This is the entry point to AutoAllocate when it is triggered.
 *
 * Returns 'true' if a Section has been allocated, returns 'false' if not.
 */
/*protected*/ void AutoAllocate::scanAllocationRequestList(QList<AllocationRequest*>* list) {
    if (list->size() <= 0) {
        return;
    }

    // copy AllocationRequests in order of priority of ActiveTrain.
    copyAndSortARs(list);
    removeCompletePlans();

    for (int i = 0; i < orderedRequests->size(); i++) {

        //try {
            AllocationRequest* ar = orderedRequests->at(i);
            if (ar == NULL) {
                log->error("error in allocation request list - AllocationRequest is NULL");
                return;
            }
            if (DispatcherFrame::instance()->getSignalType() == DispatcherFrame::SIGNALMAST && isSignalHeldAtStartOfSection(ar)) {
                return;
            }
#if 0
            if (getPlanThisTrain(ar->getActiveTrain()) != NULL) {
                // this train is in an active Allocation Plan, anything to do now?
                if (willAllocatingFollowPlan(ar, getPlanThisTrain(ar->getActiveTrain()))) {
                    if (allocateIfLessThanThreeAhead(ar)) {
                        return;
                    }
                }
            }
            else if (!waitingForStartTime(ar))
            {
                // train isn't waiting, continue only if requested Section is currently free and not occupied
                if ((ar->getSection().getState() == Section::FREE)
                        && (ar->getSection()->getOccupancy() != Section::OCCUPIED)
                        && (_dispatcher->getSignalType() == DispatcherFrame::SIGNALHEAD
                        || (_dispatcher->getSignalType() == DispatcherFrame::SIGNALMAST
                        && _dispatcher->checkBlocksNotInAllocatedSection(ar->getSection(), ar) == NULL))) {
                    // requested Section is currently free and not occupied
                    QList<ActiveTrain*>* activeTrainsList = _dispatcher->getActiveTrainsList();
                    if (activeTrainsList->size() == 1) {
                    // this is the only ActiveTrain
                        if (allocateIfLessThanThreeAhead(ar)) {
                            return;
                        }
                    } else {
                        //check if any other ActiveTrain will need this Section or its alternates, if any
                        bool okToAllocate = true;
                        QList<ActiveTrain*>* neededByTrainList = new QList<ActiveTrain>();
                        for (int j = 0; j < activeTrainsList->size(); j++) {
                            ActiveTrain* at = activeTrainsList->at(j);
                                if (at != ar->getActiveTrain()) {
                                    if (sectionNeeded(ar, at)) {
                                        neededByTrainList.add(at);
                                    }
                                }
                        }
                        if (neededByTrainList.size() <= 0) {
                            // no other ActiveTrain needs this Section, any LevelXings?
                            if (containsLevelXing(ar->getSection())) {
                                // check if allocating this Section might block a higher priority train
                                for (int j = 0; j < activeTrainsList.size(); j++) {
                                    ActiveTrain* at = activeTrainsList->at(j);
                                    if ((at != ar->getActiveTrain())
                                            && (at->getPriority() > ar->getActiveTrain()->getPriority())) {
                                        if (willLevelXingsBlockTrain(at)) {
                                            okToAllocate = false;
                                        }
                                    }
                                }
                            }
                        } else {
                            // requested Section (or alternate) is needed by other active Active Train(s)
                            for (int k = 0; k < neededByTrainList.size(); k++) {
                                // section is also needed by this active train
                                ActiveTrain* nt = neededByTrainList->at(k);
                                // are trains moving in same direction through the requested Section?
                                if (sameDirection(ar, nt)) {
                                    // trains will move in the same direction thru requested section
                                    if (firstTrainLeadsSecond(ar->getActiveTrain(), nt)
                                            && (nt->getPriority() > ar->getActiveTrain().getPriority())) {
                                        // a higher priority train is trailing this train, can we let it pass?
                                        if (checkForPassingPlan(ar, nt, neededByTrainList)) {
                                            // PASSING_MEET plan created
                                            if (!willAllocatingFollowPlan(ar,
                                                    getPlanThisTrain(ar->getActiveTrain()))) {
                                                okToAllocate = false;
                                            }
                                        }
                                    }
                                } else {
                                    // trains will move in opposite directions thru requested section
                                    //   explore possibility of an XING_MEET to avoid gridlock
                                    if (willTrainsCross(ar->getActiveTrain(), nt)) {
                                        if (checkForXingPlan(ar, nt, neededByTrainList)) {
                                            // XING_MEET plan created
                                            if (!willAllocatingFollowPlan(ar,
                                                    getPlanThisTrain(ar->getActiveTrain()))) {
                                                okToAllocate = false;
                                            }
                                        }
                                    }
// djd debugging - add test for a CONTINUING plan here
                                }
                            }
                        }
                        if (okToAllocate) {
                            if (allocateIfLessThanThreeAhead(ar)) {
                                return;
                            }
                        }
                    }
                }
            }
#endif
//        } catch (Exception e) {
//            log->warn("scanAllocationRequestList - maybe the allocationrequest was removed due to a terminating train??"+e.toString());
//            continue;
//        }
    }

}
#if 0
/**
 * Entered to request a choice of Next Section when a Section is being
 * allocated and there are alternate Section choices for the next Section.
 * sList contains the possible next Sections, and ar is the section being
 * allocated when a choice is needed.
 */
/*protected*/ Section autoNextSectionChoice(QList<Section> sList, AllocationRequest ar) {
    // check if AutoAllocate has prepared for this question
    if ((savedAR != NULL) && (savedAR == ar)) {
        for (int j = 0; j < sList.size(); j++) {
            if (savedSection == sList->at(j)) {
                return savedSection;
            }
        }
        log->warn("Failure of prepared choice of next Section in AutoAllocate");
    }
    // Jay Janzen
    // If there is an AP check to see if the AP's target is on the list of choices
    // and if so, return that.
    ActiveTrain at = ar->getActiveTrain();
    AllocationPlan ap = getPlanThisTrain(at);
    Section as = NULL;
    if (ap != NULL) {
        if      (ap.getActiveTrain(1) == at) {
            as = ap.getTargetSection(1);
        }
        else if (ap.getActiveTrain(2) == at) {
            as = ap.getTargetSection(2);
        }
        else {
            return NULL;
        }
        for (int i = 0; i < sList.size(); i++) {
            if (as != NULL && as == sList->at(i)) return as;
        }
    }
    // If our end block section is on the list of choices
    // return that occupied or not. In the list of choices the primary occurs
    // ahead any alternates, so if our end block is an alternate and its
    // primary is unoccupied, the search will select the primary and
    // we wind up skipping right over our end section.
    for (int i = 0; i < sList.size(); i++) {
        if (at.getEndBlockSection().getSystemName().equals(sList->at(i).getSystemName())) {
            return sList->at(i);
        }
    }
    // no prepared choice, or prepared choice failed, is there an unoccupied Section available
    for (int i = 0; i < sList.size(); i++) {
        if ((sList->at(i).getOccupancy() == Section.UNOCCUPIED)
                && (sList->at(i).getState() == Section.FREE)
                && (_dispatcher.getSignalType() == DispatcherFrame.SIGNALHEAD
                || (_dispatcher.getSignalType() == DispatcherFrame.SIGNALMAST
                && _dispatcher.checkBlocksNotInAllocatedSection(sList->at(i), ar) == NULL))) {
            return sList->at(i);
        }
    }
    // no unoccupied Section available, check for Section allocated in same direction as this request
    int dir = ar->getSectionDirection();
    QList<AllocatedSection> allocatedSections = _dispatcher.getAllocatedSectionsList();
    for (int m = 0; m < sList.size(); m++) {
        bool notFound = true;
        for (int k = 0; (k < allocatedSections.size()) && notFound; k++) {
            if (sList->at(m) == allocatedSections->at(k).getSection()) {
                notFound = false;
                if (allocatedSections->at(k).getSection().getState() == dir) {
                    return sList->at(m);
                }
            }
        }
    }
    // if all else fails, return NULL so Dispatcher will ask the dispatcher to choose
    return NULL;
}
/*private*/ AllocationRequest savedAR = NULL;
/*private*/ Section savedSection = NULL;
#endif
// /*private*/ implementation methods
/*private*/ void AutoAllocate::copyAndSortARs(QList<AllocationRequest*>* list) {
    orderedRequests->clear();
    // find highest priority train
    int priority = 0;
    for (int i = 0; i < list->size(); i++) {
        ActiveTrain* at = list->at(i)->getActiveTrain();
        if (at->getPriority() > priority) {
            priority = at->getPriority();
        }
    }
    while ((list->size() > orderedRequests->size()) && (priority > 0)) {
        for (int i = 0; i < list->size(); i++) {
            ActiveTrain* at = list->at(i)->getActiveTrain();
            if (at->getPriority() == priority) {
                orderedRequests->append(list->at(i));
            }
        }
        priority--;
    }
}

/*private*/ AllocationPlan* AutoAllocate::getPlanThisTrain(ActiveTrain* at) {
    for (int i = 0; i < _planList->size(); i++) {
        AllocationPlan* ap = _planList->at(i);
        for (int j = 1; j < 3; j++) {
            if (ap->getActiveTrain(j) == at) {
                return ap;
            }
        }
    }
    // train not in an AllocationPlan
    return NULL;
}
#if 0
/*private*/ bool willAllocatingFollowPlan(AllocationRequest ar, AllocationPlan ap) {
    // return 'true' if this AllocationRequest is consistent with specified plan,
    //     returns 'false' otherwise
    ActiveTrain at = ar->getActiveTrain();
    int cTrainNum = 0;
    if (ap.getActiveTrain(1) == at) {
        cTrainNum = 1;
    } else if (ap.getActiveTrain(2) == at) {
        cTrainNum = 2;
    } else {
        log->error("Requesting train not in Allocation Plan");
        return false;
    }
    if (!at.isAllocationReversed()) {
        if (ap.getTargetSectionSequenceNum(cTrainNum) >= ar->getSectionSeqNumber()) {
            if ((ar->getSection().getState() == Section.FREE)
                    && (ar->getSection().getOccupancy() != Section.OCCUPIED)) {
                return true;
            }
        }
    } else {
        if (ap.getTargetSectionSequenceNum(cTrainNum) <= ar->getSectionSeqNumber()) {
            if ((ar->getSection().getState() == Section.FREE)
                    && (ar->getSection().getOccupancy() != Section.OCCUPIED)) {
                return true;
            }
        }
    }
    return false;
}
#endif
/*private*/ void AutoAllocate::removeCompletePlans() {
    bool foundCompletePlan = true;
    while (foundCompletePlan) {
        foundCompletePlan = false;
        for (int i = 0; (!foundCompletePlan) && (i < _planList->size()); i++) {
            // remove if all planned allocations have been made
            foundCompletePlan = _planList->at(i)->isComplete();
            if (foundCompletePlan) {
                _planList->at(i)->dispose();
                _planList->removeAt(i);
            }
        }
    }
}

/*protected*/ void AutoAllocate::clearAllocationPlans() {
    for (int i = _planList->size() - 1; i >= 0; i--) {
        AllocationPlan* ap = _planList->at(i);
        _planList->removeAt(i);
        ap->dispose();
    }
}
#if 0
// test to see how far ahead allocations have already been made
// and go no farther than three unless the "all the way" attribute
// for the train is true then always allocate the request
/*private*/ bool allocateIfLessThanThreeAhead(AllocationRequest ar) {
    if (ar->getActiveTrain().getAllocateAllTheWay()) {
        _dispatcher.allocateSection(ar, NULL);
        return true;
    }
    // test how far ahead of occupied track this requested section is
    QList<AllocatedSection> aSectionList = ar->getActiveTrain().getAllocatedSectionList();
    if (aSectionList.size() >= 4) {
        int curSeq = ar->getSectionSeqNumber() - 1;
        if ((curSeq == 1) && ar->getActiveTrain().getResetWhenDone()) {
            curSeq = ar->getActiveTrain().getTransit().getMaxSequence();
        }
        AllocatedSection curAS = NULL;
        for (int i = aSectionList.size() - 1; i >= 0; i--) {
            AllocatedSection as = aSectionList->at(i);
            if ((as != NULL) && (as.getSequence() == curSeq)) {
                curAS = as;
            }
        }
        if ((curAS != NULL) && (curAS.getSection().getOccupancy() != jmri.Section.OCCUPIED)) {
            //last allocated section exists and is not occupied, test previous one
            curSeq = curSeq - 1;
            if ((curSeq == 1) && ar->getActiveTrain().getResetWhenDone()) {
                curSeq = ar->getActiveTrain().getTransit().getMaxSequence();
            }
            curAS = NULL;
            for (int i = aSectionList.size() - 1; i >= 0; i--) {
                AllocatedSection as = aSectionList->at(i);
                if ((as != NULL) && (as.getSequence() == curSeq)) {
                    curAS = as;
                }
            }
            if ((curAS != NULL) && (curAS.getSection().getOccupancy() != jmri.Section.OCCUPIED)) {
                //previous allocated section exists and is not occupied, test previous one
                curSeq = curSeq - 1;
                if ((curSeq == 1) && ar->getActiveTrain().getResetWhenDone()) {
                    curSeq = ar->getActiveTrain().getTransit().getMaxSequence();
                }
                curAS = NULL;
                for (int i = aSectionList.size() - 1; i >= 0; i--) {
                    AllocatedSection as = aSectionList->at(i);
                    if ((as != NULL) && (as.getSequence() == curSeq)) {
                        curAS = as;
                    }
                }
                if ((curAS != NULL) && (curAS.getSection().getOccupancy() != jmri.Section.OCCUPIED)) {
                    // the last two AllocatedSections are not OCCUPIED, don't allocate any more yet
                    return false;
                }
            }
        }
    }
    log->debug("{}: auto allocating Section {}", ar->getActiveTrain().getTrainName(),
            ar->getSectionName());
    _dispatcher.allocateSection(ar, NULL);
    return true;
}

/*private*/ bool checkForXingPlan(AllocationRequest ar, ActiveTrain nt,
        QList<ActiveTrain> neededByTrainList) {
    // returns 'true' if an AllocationPlan has been set up, returns 'false' otherwise
    Section nSec = NULL;
    Section aSec = NULL;
    int nSecSeq = 0;
    int aSecSeq = 0;
    ActiveTrain at = ar->getActiveTrain();
    AllocationPlan apx = getPlanThisTrain(nt);
    if (apx != NULL) {
        if (apx.getPlanType() != AllocationPlan.XING_MEET) {
            return false;
        }
        // already in a XING_MEET Allocation Plan - find target Section and sequence
        if (apx.getActiveTrain(1) == nt) {
            nSecSeq = apx.getTargetSectionSequenceNum(1);
            nSec = apx.getTargetSection(1);
        } else {
            nSecSeq = apx.getTargetSectionSequenceNum(2);
            nSec = apx.getTargetSection(2);
        }
        QList<Section> nSections = nt.getTransit().getSectionListBySeq(nSecSeq);
        if (nSections.size() <= 1) {
            return false;
        }
        // is a passing siding, find a suitable track
        aSec = getBestOtherSection(nSections, nSec);
        if (aSec == NULL) {
            return false;
        }
        aSecSeq = willTraverse(aSec, at, getCurrentSequenceNumber(at));
        if (aSecSeq == 0) {
            return false;
        }
    } else {
        // neither train is in an AllocationPlan currently, check for suitable passing siding
        int aSeq = ar->getSectionSeqNumber();
        // is an alternate Section available here or ahead
        aSecSeq = findPassingSection(at, aSeq);
        if (aSecSeq == 0) {
            // none in at's Transit, is there one in nt's Transit
            int nCurrentSeq = getCurrentSequenceNumber(nt);
            nSecSeq = findPassingSection(nt, nCurrentSeq);
            if (nSecSeq > 0) {
                // has passing section ahead, will this train traverse a Section in it
                QList<Section> nSections = nt.getTransit().getSectionListBySeq(nSecSeq);
                for (int i = 0; (i < nSections.size()) && (aSec == NULL); i++) {
                    aSecSeq = willTraverse(nSections->at(i), at, aSeq);
                    if (aSecSeq > 0) {
                        aSec = at.getTransit().getSectionListBySeq(aSecSeq)->at(0);
                    }
                }
                if (aSec != NULL) {
                    // found passing Section that should work out
                    nSec = getBestOtherSection(nSections, aSec);
                }
            }
        } else {
            // will other train go through any of these alternate sections
            QList<Section> aSections = at.getTransit().getSectionListBySeq(aSecSeq);
            int nCurrentSeq = getCurrentSequenceNumber(nt);
            for (int i = 0; (i < aSections.size()) && (aSec == NULL); i++) {
                nSecSeq = willTraverse(aSections->at(i), nt, nCurrentSeq);
                if (nSecSeq > 0) {
                    nSec = aSections->at(i);
                    aSec = getBestOtherSection(aSections, nSec);
                }
            }
        }
        // if could not find a suitable siding for a crossing meet, return
        if ((aSec == NULL) || (nSec == NULL)) {
            return false;
        }
    }
    // check for conflicting train or conflicting plan that could cause gridlock
    if (neededByTrainList.size() > 2) {
        // is there another train between these two
        if (!areTrainsAdjacent(at, nt)) {
            return false;
        }
        if (isThereConflictingPlan(at, aSec, aSecSeq, nt, nSec, nSecSeq,
                AllocationPlan.XING_MEET)) {
            return false;
        }
    }
    // set up allocation plan
    AllocationPlan ap = new AllocationPlan(this, nextPlanNum);
    nextPlanNum++;
    ap.setPlanType(AllocationPlan.XING_MEET);
    ap.setActiveTrain(at, 1);
    ap.setTargetSection(aSec, aSecSeq, 1);
    ap.setActiveTrain(nt, 2);
    ap.setTargetSection(nSec, nSecSeq, 2);
    _planList.add(ap);
    return true;
}

/*private*/ bool checkForPassingPlan(AllocationRequest ar, ActiveTrain nt,
        QList<ActiveTrain> neededByTrainList) {
    // returns 'true' if an AllocationPlan has been set up, returns 'false' otherwise
    Section nSec = NULL;
    Section aSec = NULL;
    int nSecSeq = 0;
    int aSecSeq = 0;
    ActiveTrain at = ar->getActiveTrain();
    AllocationPlan apx = getPlanThisTrain(nt);
    if (apx != NULL) {
        if (apx.getPlanType() != AllocationPlan.PASSING_MEET) {
            return false;
        }
        // already in a PASSING_MEET Allocation Plan - find target Section and sequence
        Section oSection = NULL;
//            ActiveTrain oTrain = NULL;
        if (apx.getActiveTrain(1) == nt) {
            nSecSeq = apx.getTargetSectionSequenceNum(1);
            nSec = apx.getTargetSection(1);
            oSection = apx.getTargetSection(2);
//                oTrain = apx.getActiveTrain(2);
        } else {
            nSecSeq = apx.getTargetSectionSequenceNum(2);
            nSec = apx.getTargetSection(2);
            oSection = apx.getTargetSection(1);
//                oTrain = apx.getActiveTrain(1);
        }
        int aCurrentSeq = getCurrentSequenceNumber(at);
        aSecSeq = willTraverse(nSec, at, aCurrentSeq);
        if (aSecSeq == 0) {
            return false;
        }
//            int tnSecSeq = nSecSeq;
//            if (nt.getPriority() > oTrain.getPriority()) {
//                if (!nt.isAllocationReversed()) {
//                    tnSecSeq--;
//                    if (tnSecSeq <= 0) {
//                        tnSecSeq = nSecSeq;
//                    }
//                } else {
//                    tnSecSeq++;
//                    if (tnSecSeq > nt.getTransit().getMaxSequence()) {
//                        tnSecSeq = nSecSeq;
//                    }
//                }
//            }
        QList<Section> nSections = nt.getTransit().getSectionListBySeq(nSecSeq);
        if (nSections.size() <= 1) {
            return false;
        }
        // is a passing siding, find a suitable track
        for (int i = 0; (i < nSections.size()) && (aSec == NULL); i++) {
            if (nSections->at(i) == oSection) {
                aSecSeq = willTraverse(nSections->at(i), at, aCurrentSeq);
                if (aSecSeq > 0) {
                    aSec = nSections->at(i);
                }
            }
        }
        if (aSec == NULL) {
            for (int i = 0; (i < nSections.size()) && (aSec == NULL); i++) {
                if (nSections->at(i) != nSec) {
                    aSecSeq = willTraverse(nSections->at(i), at, aCurrentSeq);
                    if (aSecSeq > 0) {
                        aSec = nSections->at(i);
                    }
                }
            }
        }
        if (aSec == NULL) {
            return false;
        }
    } else {
        // both trains are not in Allocation plans
        int aSeq = ar->getSectionSeqNumber();
        // is an alternate Section available here or ahead
        aSecSeq = findPassingSection(at, aSeq);
        if (aSecSeq == 0) {
            // does higher priority train have a passing section ahead
            int nCurrentSeq = getCurrentSequenceNumber(nt);
            nSecSeq = findPassingSection(nt, nCurrentSeq);
            if (nSecSeq > 0) {
                // has passing section ahead, will this train traverse a Section in it
                QList<Section> nSections = nt.getTransit().getSectionListBySeq(nSecSeq);
                for (int i = 0; (i < nSections.size()) && (aSec == NULL); i++) {
                    aSecSeq = willTraverse(nSections->at(i), at, aSeq);
                    if (aSecSeq > 0) {
                        aSec = at.getTransit().getSectionListBySeq(aSecSeq)->at(0);
                    }
                }
                if (aSec != NULL) {
                    // found passing Section that should work out
                    nSec = getBestOtherSection(nSections, aSec);
                }
            }
        } else {
            // will the higher priority train go through any of these alternate sections
            QList<Section> aSections = at.getTransit().getSectionListBySeq(aSecSeq);
            int nCurrentSeq = getCurrentSequenceNumber(nt);
            for (int i = 0; (i < aSections.size()) && (aSec == NULL); i++) {
                nSecSeq = willTraverse(aSections->at(i), nt, nCurrentSeq);
                if (nSecSeq > 0) {
                    nSec = aSections->at(i);
                    aSec = getBestOtherSection(aSections, nSec);
                }
            }
        }
        // if could not find a suitable passing siding, return
        if ((aSec == NULL) || (nSec == NULL)) {
            return false;
        }
        //     push higher priority train one section further, if possible
        if (!nt.isAllocationReversed()) {
            if (nSecSeq < nt.getTransit().getMaxSequence()) {
                nSecSeq++;
                nSec = nt.getTransit().getSectionListBySeq(nSecSeq)->at(0);
            }
        } else {
            if (nSecSeq > 1) {
                nSecSeq--;
                nSec = nt.getTransit().getSectionListBySeq(nSecSeq)->at(0);
            }
        }
    }
    // is there another train trying to let this high priority train pass
    if (neededByTrainList.size() > 2) {
        // Note: e.g. Two lower priority trains ahead of a high priority train could cause gridlock
        //    if both try to set up a PASSING_PLAN meet at the same place, so we exclude that case.
        // is there another train between these two
        if (!areTrainsAdjacent(at, nt)) {
            return false;
        }
        if (isThereConflictingPlan(at, aSec, aSecSeq, nt, nSec, nSecSeq,
                AllocationPlan.PASSING_MEET)) {
            return false;
        }
    }
    // set up allocation plan
    AllocationPlan ap = new AllocationPlan(this, nextPlanNum);
    nextPlanNum++;
    ap.setPlanType(AllocationPlan.PASSING_MEET);
    ap.setActiveTrain(at, 1);
    ap.setTargetSection(aSec, aSecSeq, 1);
    ap.setActiveTrain(nt, 2);
    ap.setTargetSection(nSec, nSecSeq, 2);
    _planList.add(ap);
    return true;
}

/*private*/ bool isThereConflictingPlan(ActiveTrain at, Section aSec, int aSecSeq,
        ActiveTrain nt, Section nSec, int nSecSeq, int type) {
    // returns 'true' if there is a conflicting	plan that may result in gridlock
    //    if this plan is set up, return 'false' if not.
    // Note: may have to add other tests to this method in the future to prevent gridlock
    //	  situations not currently tested for.
    if (_planList.size() == 0) {
        return false;
    }
    for (int i = 0; i < _planList.size(); i++) {
        AllocationPlan ap = _planList->at(i);
        // check if this plan involves the second train (it'll never involve the first)
        int trainNum = 0;
        if (ap.getActiveTrain(1) == nt) {
            trainNum = 1;
        } else if (ap.getActiveTrain(2) == nt) {
            trainNum = 2;
        }
        if (trainNum > 0) {
            // check consistency - same type, section, and sequence number
            if ((ap.getPlanType() != type) || (ap.getTargetSection(trainNum) != nSec)
                    || (ap.getTargetSectionSequenceNum(trainNum) != nSecSeq)) {
                return true;
            }
        } else {
            // different trains, does this plan use the same Passing Section?
            QList<Section> aSections = at.getTransit().getSectionListBySeq(aSecSeq);
            for (int j = 0; j < aSections.size(); j++) {
                if ((aSections->at(j) == ap.getTargetSection(1))
                        || (aSections->at(j) == ap.getTargetSection(2))) {
                    return true;
                }
            }
        }
    }
    // passes all tests
    return false;
}

/*private*/ Section getBestOtherSection(QList<Section> sList, Section aSec) {
    // returns the best Section from the list that is not aSec, or else return NULL
    for (int i = 0; i < sList.size(); i++) {
        if ((sList->at(i) != aSec) && (sList->at(i).getState() == Section.FREE)
                && (sList->at(i).getOccupancy() != Section.OCCUPIED)) {
            return sList->at(i);
        }
    }
    for (int i = 0; i < sList.size(); i++) {
        if ((sList->at(i) != aSec) && (sList->at(i).getOccupancy() != Section.OCCUPIED)) {
            return sList->at(i);
        }
    }
    for (int i = 0; i < sList.size(); i++) {
        if (sList->at(i) != aSec) {
            return sList->at(i);
        }
    }
    return NULL;
}

/*private*/ int findPassingSection(ActiveTrain at, int aSeq) {
    // returns the sequence number of first area having alternate sections
    Transit t = at.getTransit();
    if (!at.isTransitReversed()) {
        for (int i = aSeq; i <= t.getMaxSequence(); i++) {
            if (t.getSectionListBySeq(i).size() > 1) {
                return i;
            }
        }
    } else {
        for (int i = aSeq; i >= 0; i--) {
            if (t.getSectionListBySeq(i).size() > 1) {
                return i;
            }
        }
    }
    return 0;
}
#endif
/*private*/ int AutoAllocate::willTraverse(Section* s, ActiveTrain* at, int seq) {
    Transit* t = at->getTransit();
    if (!at->isTransitReversed()) {
        for (int i = seq; i < t->getMaxSequence(); i++) {
            for (int j = 0; j < t->getSectionListBySeq(i)->size(); j++) {
                if (t->getSectionListBySeq(i)->at(j) == s) {
                    return i;
                }
            }
        }
    } else {
        for (int i = seq; i >= 0; i--) {
            for (int j = 0; j < t->getSectionListBySeq(i)->size(); j++) {
                if (t->getSectionListBySeq(i)->at(j) == s) {
                    return i;
                }
            }
        }
    }
    return 0;
}
#if 0
/*private*/ bool sectionNeeded(AllocationRequest ar, ActiveTrain at) {
    // returns 'true' if request section, or its alternates, will be needed by specified train
    if ((ar == NULL) || (at == NULL)) {
        log->error("NULL argument on entry to 'sectionNeeded'");
        return false;
    }
    QList<Section> aSectionList = ar->getActiveTrain().getTransit().getSectionListBySeq(
            ar->getSectionSeqNumber());
    bool found = false;
    for (int i = 0; i < aSectionList.size(); i++) {
        if (!(at.getTransit().containsSection(aSectionList->at(i)))) {
            found = true;
        }
    }
    if (!found) {
        return false;
    } else if ((at.getResetWhenDone()) || (at.getReverseAtEnd()
            && (!at.isAllocationReversed()))) {
        return true;
    }
    // this train may need this Section, has it already passed this Section?
    QList<TransitSection> tsList = at.getTransit().getTransitSectionList();
    int curSeq = getCurrentSequenceNumber(at);
    if (!at.isAllocationReversed()) {
        for (int i = 0; i < tsList.size(); i++) {
            if (tsList->at(i).getSequenceNumber() > curSeq) {
                for (int j = 0; j < aSectionList.size(); j++) {
                    if (tsList->at(i).getSection() == aSectionList->at(j)) {
                        return true;
                    }
                }
            }
        }
    } else {
        for (int i = tsList.size() - 1; i >= 0; i--) {
            if (tsList->at(i).getSequenceNumber() < curSeq) {
                for (int j = 0; j < aSectionList.size(); j++) {
                    if (tsList->at(i).getSection() == aSectionList->at(j)) {
                        return true;
                    }
                }
            }
        }
    }
    if (DispatcherFrame.instance().getSignalType() == DispatcherFrame.SIGNALMAST) {
        if (!at.isAllocationReversed()) {
            for (int i = 0; i < tsList.size(); i++) {
                if (tsList->at(i).getSequenceNumber() > curSeq) {
                    for (int j = 0; j < aSectionList.size(); j++) {
                        if (tsList->at(i).getSection() == aSectionList->at(j)) {
                            return true;
                        }
                    }
                }
            }
        } else {
            for (int i = tsList.size() - 1; i >= 0; i--) {
                if (tsList->at(i).getSequenceNumber() < curSeq) {
                    for (int j = 0; j < aSectionList.size(); j++) {
                        if (tsList->at(i).getSection() == aSectionList->at(j)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

/*private*/ bool sameDirection(AllocationRequest ar, ActiveTrain at) {
    // returns 'true' if both trains will move thru the requested section in the same direction
    if ((ar == NULL) || (at == NULL)) {
        log->error("NULL argument on entry to 'sameDirection'");
        return false;
    }
    QList<TransitSection> tsList = at.getTransit().getTransitSectionList();
    QList<TransitSection> rtsList = ar->getActiveTrain().getTransit().getTransitSectionListBySeq(
            ar->getSectionSeqNumber());
    int curSeq = getCurrentSequenceNumber(at);
    if (!at.isAllocationReversed()) {
        for (int i = 0; i < tsList.size(); i++) {
            if (tsList->at(i).getSequenceNumber() > curSeq) {
                for (int k = 0; k < rtsList.size(); k++) {
                    if ((tsList->at(i).getSection() == rtsList->at(k).getSection())
                            && (tsList->at(i).getDirection() == rtsList->at(k).getDirection())) {
                        return true;
                    }
                }
            }
        }
    } else {
        for (int i = tsList.size() - 1; i >= 0; i--) {
            if (tsList->at(i).getSequenceNumber() < curSeq) {
                for (int k = 0; k < rtsList.size(); k++) {
                    if ((tsList->at(i).getSection() == rtsList->at(k).getSection())
                            && (tsList->at(i).getDirection() == rtsList->at(k).getDirection())) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/*private*/ bool firstTrainLeadsSecond(ActiveTrain at, ActiveTrain nt) {
    int aSeq = getCurrentSequenceNumber(at);
    Section aSec = getCurSection();
    int nSeq = getCurrentSequenceNumber(nt);
    Section nSec = getCurSection();
    QList<TransitSection> atsList = at.getTransit().getTransitSectionList();
    if (!at.isTransitReversed()) {
        for (int i = 0; i < atsList.size(); i++) {
            if (atsList->at(i).getSequenceNumber() > aSeq) {
                if (atsList->at(i).getSection() == nSec) {
                    // first train has not yet reached second train position
                    return false;
                }
            }
        }
    } else {
        for (int i = atsList.size() - 1; i <= 0; i--) {
            if (atsList->at(i).getSequenceNumber() < aSeq) {
                if (atsList->at(i).getSection() == nSec) {
                    // first train has not yet reached second train position
                    return false;
                }
            }
        }
    }
    QList<TransitSection> ntsList = nt.getTransit().getTransitSectionList();
    if (!nt.isTransitReversed()) {
        for (int i = 0; i < ntsList.size(); i++) {
            if (ntsList->at(i).getSequenceNumber() > nSeq) {
                if (ntsList->at(i).getSection() == aSec) {
                    // second train has found first train in its on coming Sections
                    return true;
                }
            }
        }
    } else {
        for (int i = ntsList.size() - 1; i <= 0; i--) {
            if (ntsList->at(i).getSequenceNumber() < nSeq) {
                if (ntsList->at(i).getSection() == aSec) {
                    // second train has found first train in its on coming Sections
                    return true;
                }
            }
        }
    }
    return false;
}

/*private*/ bool willTrainsCross(ActiveTrain at, ActiveTrain nt) {
    // returns true if both trains will eventually reach the others position
    int aSeq = getCurrentSequenceNumber(at);
    Section aSec = getCurSection();
    int nSeq = getCurrentSequenceNumber(nt);
    Section nSec = getCurSection();
    QList<TransitSection> atsList = at.getTransit().getTransitSectionList();
    bool found = false;
    if (!at.isTransitReversed()) {
        for (int i = 0; (i < atsList.size()) && (!found); i++) {
            if (atsList->at(i).getSequenceNumber() > aSeq) {
                if (atsList->at(i).getSection() == nSec) {
                    // first train has reached second train position
                    found = true;
                }
            }
        }
    } else {
        for (int i = atsList.size() - 1; (i <= 0) && (!found); i--) {
            if (atsList->at(i).getSequenceNumber() < aSeq) {
                if (atsList->at(i).getSection() == nSec) {
                    // first train has reached second train position
                    found = true;
                }
            }
        }
    }
    if (!found) {
        return false;
    }
    QList<TransitSection> ntsList = nt.getTransit().getTransitSectionList();
    if (!nt.isTransitReversed()) {
        for (int i = 0; i < ntsList.size(); i++) {
            if (ntsList->at(i).getSequenceNumber() > nSeq) {
                if (ntsList->at(i).getSection() == aSec) {
                    // second train has found first train in its on coming Sections
                    return true;
                }
            }
        }
    } else {
        for (int i = ntsList.size() - 1; i <= 0; i--) {
            if (ntsList->at(i).getSequenceNumber() < nSeq) {
                if (ntsList->at(i).getSection() == aSec) {
                    // second train has found first train in its on coming Sections
                    return true;
                }
            }
        }
    }
    return false;
}

/*private*/ bool areTrainsAdjacent(ActiveTrain at, ActiveTrain nt) {
    // returns 'false' if a different ActiveTrain has allocated track between the
    //      two trains, returns 'true' otherwise
    QList<AllocatedSection> allocatedSections = _dispatcher.getAllocatedSectionsList();
    QList<TransitSection> atsList = at.getTransit().getTransitSectionList();
    int aSeq = getCurrentSequenceNumber(at);
    Section nSec = getCurSection();
    if (willTraverse(nSec, at, aSeq) != 0) {
        // at is moving toward nt
        if (!at.isTransitReversed()) {
            for (int i = 0; i < atsList.size(); i++) {
                if (atsList->at(i).getSequenceNumber() > aSeq) {
                    Section tSec = atsList->at(i).getSection();
                    if (tSec == nSec) {
                        // reached second train position, no train in between
                        return true;
                    } else {
                        for (int j = 0; j < allocatedSections.size(); j++) {
                            if (allocatedSections->at(j).getSection() == tSec) {
                                if ((allocatedSections->at(j).getActiveTrain() != at)
                                        && (allocatedSections->at(j).getActiveTrain() != nt)) {
                                    // allocated to a third train, trains not adjacent
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            for (int i = atsList.size() - 1; i <= 0; i--) {
                if (atsList->at(i).getSequenceNumber() < aSeq) {
                    Section tSec = atsList->at(i).getSection();
                    if (tSec == nSec) {
                        // reached second train position, no train in between
                        return true;
                    } else {
                        for (int j = 0; j < allocatedSections.size(); j++) {
                            if (allocatedSections->at(j).getSection() == tSec) {
                                if ((allocatedSections->at(j).getActiveTrain() != at)
                                        && (allocatedSections->at(j).getActiveTrain() != nt)) {
                                    // allocated to a third train, trains not adjacent
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        // at is moving away from nt, so backtrack
        if (at.isTransitReversed()) {
            for (int i = 0; i < atsList.size(); i++) {
                if (atsList->at(i).getSequenceNumber() > aSeq) {
                    Section tSec = atsList->at(i).getSection();
                    if (tSec == nSec) {
                        // reached second train position, no train in between
                        return true;
                    } else {
                        for (int j = 0; j < allocatedSections.size(); j++) {
                            if (allocatedSections->at(j).getSection() == tSec) {
                                if ((allocatedSections->at(j).getActiveTrain() != at)
                                        && (allocatedSections->at(j).getActiveTrain() != nt)) {
                                    // allocated to a third train, trains not adjacent
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            for (int i = atsList.size() - 1; i <= 0; i--) {
                if (atsList->at(i).getSequenceNumber() < aSeq) {
                    Section tSec = atsList->at(i).getSection();
                    if (tSec == nSec) {
                        // reached second train position, no train in between
                        return true;
                    } else {
                        for (int j = 0; j < allocatedSections.size(); j++) {
                            if (allocatedSections->at(j).getSection() == tSec) {
                                if ((allocatedSections->at(j).getActiveTrain() != at)
                                        && (allocatedSections->at(j).getActiveTrain() != nt)) {
                                    // allocated to a third train, trains not adjacent
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

/*private*/ int getCurrentSequenceNumber(ActiveTrain at) {
    // finds the current position of the head of the ActiveTrain in its Transit
    // returns sequence number of current position. getCurSection() returns Section.
    int seq = 0;
    curSection = NULL;
    if (at == NULL) {
        log->error("NULL argument on entry to 'getCurrentSeqNumber'");
        return seq;
    }
    Section temSection = NULL;
    QList<TransitSection> tsList = at.getTransit().getTransitSectionList();
    if (!at.isTransitReversed()) {
        // find the highest numbered occupied section
        for (int i = 0; i < tsList.size(); i++) {
            if ((tsList->at(i).getSection().getOccupancy() == Section.OCCUPIED)
                    && isSectionAllocatedToTrain(tsList->at(i).getSection(),
                            tsList->at(i).getSequenceNumber(), at)) {
                seq = tsList->at(i).getSequenceNumber();
                temSection = tsList->at(i).getSection();
            }
        }
        if (seq == at.getTransit().getMaxSequence()) {
            if (at.getResetWhenDone()) {
                // train may have passed the last Section during continuous running
                bool further = true;
                for (int j = 0; (j < tsList.size()) && further; j++) {
                    if ((tsList->at(j).getSection().getOccupancy() == Section.OCCUPIED)
                            && isSectionAllocatedToTrain(tsList->at(j).getSection(),
                                    tsList->at(j).getSequenceNumber(), at)) {
                        seq = tsList->at(j).getSequenceNumber();
                        temSection = tsList->at(j).getSection();
                    } else {
                        further = false;
                    }
                }
            }
        }
    } else {
        // transit is running in reverse
        for (int i = tsList.size() - 1; i >= 0; i--) {
            if ((tsList->at(i).getSection().getOccupancy() == Section.OCCUPIED)
                    && isSectionAllocatedToTrain(tsList->at(i).getSection(),
                            tsList->at(i).getSequenceNumber(), at)) {
                seq = tsList->at(i).getSequenceNumber();
                temSection = tsList->at(i).getSection();
            }
        }
    }
    if (seq == 0) {
        if (at.getMode() != ActiveTrain.MANUAL) {
            log->error("{}: ActiveTrain has no occupied Section. Halting immediately to avoid runaway.", at.getTrainName());
            at.getAutoActiveTrain().getAutoEngineer().setHalt(true);
        } else {
            log->debug("{}: ActiveTrain has no occupied Section, running in Manual mode.", at.getTrainName());
        }
    } else {
        curSection = temSection;
    }
    return seq;
}
Section curSection = NULL;

// Returns the Section with the sequence number returned by last call to getCurrentSequenceNumber
/*private*/ Section getCurSection() {
    return curSection;
}

/*private*/ bool isSectionAllocatedToTrain(Section s, int seq, ActiveTrain at) {
    if ((s == NULL) || (at == NULL)) {
        log->error("NULL argument to isSectionAllocatedToTrain");
        return false;
    }
    QList<AllocatedSection> asList = at.getAllocatedSectionList();
    for (int i = 0; i < asList.size(); i++) {
        if ((asList->at(i).getSection() == s) && asList->at(i).getSequence() == seq) {
            return true;
        }
    }
    return false;
}

/*private*/ bool waitingForStartTime(AllocationRequest ar) {
    if (ar != NULL) {
        ActiveTrain at = ar->getActiveTrain();
        if (at == NULL) {
            return false;
        }
        if ((!at.getStarted()) && at.getDelayedStart() != ActiveTrain.NODELAY || at.reachedRestartPoint()) {
            return true;
        }
    }
    return false;
}

/*private*/ bool willLevelXingsBlockTrain(ActiveTrain at) {
    // returns true if any LevelXings in _levelXingList will block the specified train
    if (at == NULL) {
        log->error("NULL argument on entry to 'willLevelXingsBlockTrain'");
        return true;  // returns true to be safe
    }
    if (_levelXingList.size() <= 0) {
        return false;
    }
    for (int i = 0; i < _levelXingList.size(); i++) {
        LevelXing lx = _levelXingList->at(i);
        Block bAC = lx.getLayoutBlockAC().getBlock();
        Block bBD = lx.getLayoutBlockBD().getBlock();
        if (at.getTransit().containsBlock(bAC) || at.getTransit().containsBlock(bBD)) {
            return true;
        }
    }
    return false;
}

/*private*/ bool containsLevelXing(Section s) {
    // returns true if Section contains one or more level crossings
    // NOTE: changes _levelXingList!
    _levelXingList.clear();
    if (s == NULL) {
        log->error("NULL argument to 'containsLevelCrossing'");
        return false;
    }
    QList<LevelXing> temLevelXingList = NULL;
    QList<Block> blockList = s.getBlockList();
    for (int i = 0; i < blockList.size(); i++) {
        temLevelXingList = _conUtil.getLevelCrossingsThisBlock(blockList->at(i));
        if (temLevelXingList.size() > 0) {
            for (int j = 0; j < temLevelXingList.size(); j++) {
                _levelXingList.add(temLevelXingList->at(j));
            }
        }
    }
    if (_levelXingList.size() > 0) {
        return true;
    }
    return false;
}
QList<LevelXing> _levelXingList = new QList<LevelXing>();
#endif
/*private*/ bool AutoAllocate::isSignalHeldAtStartOfSection(AllocationRequest* ar) {

    if (ar == NULL) {
        return false;
    }

    Section* sec = ar->getSection();
    ActiveTrain* mActiveTrain = ar->getActiveTrain();

    if (sec == NULL || mActiveTrain == NULL) {
        return false;
    }

    Section* lastSec = mActiveTrain->getLastAllocatedSection();

    if (lastSec == NULL) {
        return false;
    }

    if (sec!=(mActiveTrain->getNextSectionToAllocate())) {
        log->error("Allocation request section does not match active train next section to allocate");
        log->error("Section to allocate " + sec->getDisplayName());
        if (mActiveTrain->getNextSectionToAllocate() != NULL) {
            log->error("Active Train expected " + mActiveTrain->getNextSectionToAllocate()->getDisplayName());
        }
        return false;
    }

    Block* facingBlock;
    Block* protectingBlock;
    if (ar->getSectionDirection() == Section::FORWARD) {
        protectingBlock = sec->getBlockBySequenceNumber(0);
        facingBlock = lastSec->getBlockBySequenceNumber(lastSec->getNumBlocks() - 1);
    } else {
        //Reverse
        protectingBlock = sec->getBlockBySequenceNumber(sec->getNumBlocks() - 1);
        facingBlock = lastSec->getBlockBySequenceNumber(0);
    }
    if (protectingBlock == NULL || facingBlock == NULL) {
        return false;
    }

    SignalMast* sm =  ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getFacingSignalMast(facingBlock, protectingBlock);
    if (sm != NULL && sm->getHeld() && !_dispatcher->isMastHeldByDispatcher(sm, mActiveTrain)) {
        ar->setWaitingForSignalMast(sm);
        return true;
    }
    return false;
}

