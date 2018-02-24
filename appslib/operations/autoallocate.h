#ifndef AUTOALLOCATE_H
#define AUTOALLOCATE_H

#include <QObject>
#include "section.h"

class ActiveTrain;
class ConnectivityUtil;
class Logger;
class DispatcherFrame;
class AllocationPlan;
class AllocationRequest;
class AutoAllocate : public QObject
{
 Q_OBJECT
public:
 //explicit AutoAllocate(QObject *parent = 0);
 /*public*/ AutoAllocate(DispatcherFrame* d);

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

protected:
 /*protected*/ void scanAllocationRequestList(QList<AllocationRequest*>* list);
 /*protected*/ void clearAllocationPlans();

 friend class DispatcherFrame;
};

#endif // AUTOALLOCATE_H
