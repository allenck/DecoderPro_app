#ifndef AUTOALLOCATE_H
#define AUTOALLOCATE_H

#include "section.h"
#include "runnable.h"
#include "levelxing.h"

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
 /*private*/ QList<AllocationPlan*> _planList = QList<AllocationPlan*>();
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
 /*private*/ AllocationRequest* savedAR = NULL;
 /*private*/ Section* savedSection = NULL;
 /*private*/ bool willAllocatingFollowPlan(AllocationRequest* ar, AllocationPlan* ap);
 /*private*/ bool allocateIfLessThanThreeAhead(AllocationRequest* ar);
 /*private*/ bool checkForXingPlan(AllocationRequest* ar, ActiveTrain* nt,
                                   QList<ActiveTrain*> neededByTrainList);
 /*private*/ bool checkForPassingPlan(AllocationRequest* ar, ActiveTrain* nt,
                                      QList<ActiveTrain*> neededByTrainList);
 /*private*/ bool isThereConflictingPlan(ActiveTrain* at, Section* aSec, int aSecSeq,
         ActiveTrain* nt, Section* nSec, int nSecSeq, int type);
 /*private*/ Section* getBestOtherSection(QList<Section*> sList, Section* aSec);
 /*private*/ int findPassingSection(ActiveTrain* at, int aSeq);
 /*private*/ bool sectionNeeded(AllocationRequest* ar, ActiveTrain* at);
 /*private*/ bool sameDirection(AllocationRequest* ar, ActiveTrain* at);
 /*private*/ bool firstTrainLeadsSecond(ActiveTrain* at, ActiveTrain* nt);
 /*private*/ bool willTrainsCross(ActiveTrain* at, ActiveTrain* nt);
 /*private*/ bool areTrainsAdjacent(ActiveTrain* at, ActiveTrain* nt);
 /*private*/ int getCurrentSequenceNumber(ActiveTrain* at);
 Section* curSection = NULL;
 /*private*/ Section* getCurSection();
 /*private*/ bool isSectionAllocatedToTrain(Section* s, int seq, ActiveTrain* at);
 /*private*/ bool waitingForStartTime(AllocationRequest* ar);
 /*private*/ bool willLevelXingsBlockTrain(ActiveTrain* at);
 /*private*/ bool containsLevelXing(Section* s);
 QList<LevelXing*> _levelXingList =  QList<LevelXing*>();

protected:
 /*protected*/ void scanAllocationRequestList(QList<AllocationRequest*>* list);
 /*protected*/ void clearAllocationPlans();
 /*protected*/ void setAbort();
 /*protected*/ bool allRequestsDone();
 /*protected*/ void scanAllocationRequests(TaskAllocateRelease* task);
 /*protected*/ Section* autoNextSectionChoice(QList<Section*> sList, AllocationRequest* ar);

 friend class DispatcherFrame;
};

#endif // AUTOALLOCATE_H
