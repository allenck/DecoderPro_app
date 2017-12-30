#include "allocationplan.h"
#include "autoallocate.h"
#include "activetrain.h"
#include "section.h"
#include "logger.h"
#include "allocatedsection.h"

//AllocationPlan::AllocationPlan(QObject *parent) : QObject(parent)
//{

//}
/**
 * Handle planning information for AutoAllocate
 * <P>
 * An Allocation Plan involves a planned meet of two ActiveTrains in a specified
 * area of the layout.
 * <P>
 * AllocationPlan objects are transient (not saved between runs).
 * <P>
 * AllocationPlan objects are created and disposed by AutoAllocate as needed.
 * AutoAllocate serves as the manager of AllocationPlan objects.
 * <P>
 * An ActiveTrain may be in more than one AllocationPlan of the same type,
 * provided its target Section in all active AllocationPlans is the same.
 * <P>
 * An AllocationPlan is "complete" when both Active Trains have been allocated
 * their target Sections.
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
 * @author	Dave Duchamp Copyright (C) 2011
 */
///*public*/ class AllocationPlan {

/*public*/ AllocationPlan::AllocationPlan(AutoAllocate* aa, int planNum) {
 log = new Logger("AllocationPlan");
 // instance variables
 _autoAllocate = NULL;
 _planNum = 0;     // Note: _planNum may not be changed. It is the ID of this plan.
 _planType = NONE;
 _atOne = NULL;
 _atTwo = NULL;
 _tSectionOne = NULL;
 _tSectionTwo = NULL;
 _tSectionOneSeq = 0;
 _tSectionTwoSeq = 0;

    _autoAllocate = aa;
    if (_autoAllocate == NULL) {
        log->error("NULL AutoAllocate when constructing an AllocationPlan");
    }
    _planNum = planNum;
}

/**
 * Constants representing the type of AllocationPlan
 */


/**
 * Access methods
 */
/*protected*/ int AllocationPlan::getPlanNum() {
    return _planNum;
}

/*protected*/ int AllocationPlan::getPlanType() {
    return _planType;
}

/*protected*/ void AllocationPlan::setPlanType(int type) {
    _planType = type;
}

/*protected*/ ActiveTrain* AllocationPlan::getActiveTrain(int i) {
    if (i == 1) {
        return _atOne;
    } else if (i == 2) {
        return _atTwo;
    }
    return NULL;
}

/*protected*/ void AllocationPlan::setActiveTrain(ActiveTrain* at, int i) {
    if (i == 1) {
        _atOne = at;
    } else if (i == 2) {
        _atTwo = at;
    } else {
        log->error("out of range index argument in call to 'setActiveTrain'");
    }
}

/*protected*/ Section* AllocationPlan::getTargetSection(int i) {
    if (i == 1) {
        return _tSectionOne;
    } else if (i == 2) {
        return _tSectionTwo;
    }
    return NULL;
}

/*protected*/ void AllocationPlan::setTargetSection(Section* s, int seq, int i) {
    if (i == 1) {
        _tSectionOne = s;
        _tSectionOneSeq = seq;
    } else if (i == 2) {
        _tSectionTwo = s;
        _tSectionTwoSeq = seq;
    } else {
        log->error("out of range index argument in call to 'setTargetSection'");
    }
}

/*protected*/ int AllocationPlan::getTargetSectionSequenceNum(int i) {
    if (i == 1) {
        return _tSectionOneSeq;
    } else if (i == 2) {
        return _tSectionTwoSeq;
    }
    return 0;
}

/**
 * Other Methods
 */
/*protected*/ bool AllocationPlan::isComplete() {
    if ((_atOne == NULL) || (_atTwo == NULL)) {
        return false;
    }
    QList<AllocatedSection*>* aSections = _atOne->getAllocatedSectionList();
    bool complete = false;
    for (int i = 0; i < aSections->size(); i++) {
        if ((aSections->at(i)->getSection() == _tSectionOne)
                && (aSections->at(i)->getSequence() == _tSectionOneSeq)) {
            complete = true;
        }
    }
    if (!complete) {
        return false;
    }
    complete = false;
    aSections = _atTwo->getAllocatedSectionList();
    for (int j = 0; j < aSections->size(); j++) {
        if ((aSections->at(j)->getSection() == _tSectionTwo)
                && (aSections->at(j)->getSequence() == _tSectionTwoSeq)) {
            complete = true;
        }
    }
    return complete;
}

/*public*/ void AllocationPlan::dispose() {
    // does nothing for now
}
