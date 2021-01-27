#ifndef AUTOALLOCATE_H
#define AUTOALLOCATE_H

#include "section.h"
#include "runnable.h"

class TaskAllocateRelease;
class ActiveTrain;
class ConnectivityUtil;
class Logger;
class DispatcherFrame;
class AllocationPlan;
class AllocationRequest;
class AutoAllocate : public Runnable
{
 Q_OBJECT
public:
 //explicit AutoAllocate(QObject *parent = 0);
 /*public*/ AutoAllocate(DispatcherFrame* d, QList<AllocationRequest *>* inAllocationRequests, QObject *parent = 0);

signals:

public slots:

private:
 Logger* log;
 // operational variables
 /*private*/ DispatcherFrame* _dispatcher;// = NULL;
 /*private*/ ConnectivityUtil* _conUtil;// = NULL;
 /*private*/ QList<AllocationPlan*>* _planList;// = new ArrayList<AllocationPlan>();
 /*private*/ int nextPlanNum;// = 1;
 /*private*/ QList<AllocationRequest*>* orderedRequests;// = new ArrayList<AllocationRequest>();
 /*private*/ void copyAndSortARs(QList<AllocationRequest*>* list);
 /*private*/ void removeCompletePlans();
 /*private*/ bool isSignalHeldAtStartOfSection(AllocationRequest* ar);
 /*private*/ AllocationPlan* getPlanThisTrain(ActiveTrain* at);
 /*private*/ int willTraverse(Section* s, ActiveTrain* at, int seq);
 /*private*/ bool abort = false;
 /*private*/ QList<AllocationRequest*>* allocationRequests = nullptr;
 QLinkedList<TaskAllocateRelease*>* taskList =nullptr;

protected:
 /*protected*/ void scanAllocationRequestList(QList<AllocationRequest*>* list);
 /*protected*/ void clearAllocationPlans();
 /*protected*/ void setAbort();
 /*protected*/ bool allRequestsDone();
 /*protected*/ void scanAllocationRequests(TaskAllocateRelease* task);

 friend class DispatcherFrame;
};

#endif // AUTOALLOCATE_H
