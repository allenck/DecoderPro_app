#ifndef ALLOCATIONPLAN_H
#define ALLOCATIONPLAN_H

#include <QObject>

class Section;
class ActiveTrain;
class AutoAllocate;
class Logger;
class AllocationPlan : public QObject
{
 Q_OBJECT
public:
 //explicit AllocationPlan(QObject *parent = 0);
 /*public*/ AllocationPlan(AutoAllocate* aa, int planNum);
 /*public*/ void dispose();

signals:

public slots:

private:
 Logger* log;
 // instance variables
 /*private*/ AutoAllocate* _autoAllocate;// = null;
 /*private*/ int _planNum ; // = 0;     // Note: _planNum may not be changed. It is the ID of this plan.
 /*private*/ int _planType ; // = NONE;
 /*private*/ ActiveTrain* _atOne ; // = null;
 /*private*/ ActiveTrain* _atTwo ; // = null;
 /*private*/ Section* _tSectionOne ; // = null;
 /*private*/ Section* _tSectionTwo ; // = null;
 /*private*/ int _tSectionOneSeq ; // = 0;
 /*private*/ int _tSectionTwoSeq ; // = 0;


protected:
 enum PLANTYPES
 {
   NONE = 0x00,   // no plan type
   XING_MEET = 0x01,
   PASSING_MEET = 0x02,
   CONTINUING = 0x04
 };
 /*protected*/ int getPlanNum();
 /*protected*/ int getPlanType();
 /*protected*/ void setPlanType(int type);
 /*protected*/ ActiveTrain* getActiveTrain(int i);
 /*protected*/ void setActiveTrain(ActiveTrain* at, int i);
 /*protected*/ Section* getTargetSection(int i);
 /*protected*/ void setTargetSection(Section* s, int seq, int i) ;
 /*protected*/ int getTargetSectionSequenceNum(int i);
 /*protected*/ bool isComplete();

 friend class AutoAllocate;
};

#endif // ALLOCATIONPLAN_H
