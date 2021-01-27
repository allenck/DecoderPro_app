#include "taskallocaterelease.h"

// /*public*/ class TaskAllocateRelease {

    TaskAllocateRelease::TaskAllocateRelease(TaskAction action, QObject *parent) : QObject(parent) {
        act = action;
    }

    TaskAllocateRelease::TaskAllocateRelease(TaskAction action, QString trainName, QObject *parent) : QObject(parent) {
        act = action;
        this->trainName = trainName;
    }

    TaskAllocateRelease::TaskAllocateRelease(TaskAction action, AllocatedSection* aSection, bool termTrain, QObject *parent) : QObject(parent) {
        act = action;
        allocatedSection = aSection;
        terminateingTrain = termTrain;
    }

    /*public*/ TaskAllocateRelease::TaskAction TaskAllocateRelease::getAction() {
        return act;
    }

    /*public*/ QString TaskAllocateRelease::getTrainName() {
        return trainName;
    }

    /*public*/ AllocatedSection* TaskAllocateRelease::getAllocatedSection() {
        return allocatedSection;
    }

    /*public*/ bool TaskAllocateRelease::getTerminatingTrain() {
        return terminateingTrain;
    }

