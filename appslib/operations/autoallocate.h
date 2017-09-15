#ifndef AUTOALLOCATE_H
#define AUTOALLOCATE_H

#include <QObject>

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

protected:
 /*protected*/ void scanAllocationRequestList(QList<AllocationRequest*>* list);

 friend class DispatcherFrame;
};

#endif // AUTOALLOCATE_H
