#ifndef ALLOCATIONREQUEST_H
#define ALLOCATIONREQUEST_H

#include <QObject>

class SignalMast;
class PropertyChangeListener;
class PropertyChangeEvent;
class Block;
class Section;
class ActiveTrain;
class AllocationRequest : public QObject
{
 Q_OBJECT
public:
 //explicit AllocationRequest(QObject *parent = 0);
 /*public*/ AllocationRequest(Section* s, int num, int dir, ActiveTrain* at);
 /*public*/ Section* getSection();
 /*public*/ QString getSectionName();
 /*public*/ void dispose();
 /*public*/ void setWaitingForSignalMast(SignalMast* sm);

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
 Block* mWaitingOnBlock;// = null;
 // instance variables
 /*private*/ Section* mSection;// = NULL;
 /*private*/ ActiveTrain* mActiveTrain;// = NULL;
 /*private*/ int mSectionSeqNum;// = 0;
 /*private*/ int mSectionDirection;// = Section::UNKNOWN;
 /*private*/ PropertyChangeListener* mSectionListener;// = NULL;
 // instance variables related to automatic allocation of Sections
 /*private*/ bool mWaitingForTrain;// = false;
 /*private*/ QList<ActiveTrain*>* mMeetingTrainList;// = new QList<ActiveTrain*>();
 /*private*/ PropertyChangeListener* mSignalMastListener;// = NULL;
 /*private*/ SignalMast* mWaitingForSignalMast;// = NULL;
 /*private*/ PropertyChangeListener* mWaitingOnBlockListener;// = NULL;

private slots:
 /*private*/ void handleSectionChange(PropertyChangeEvent* e);


protected:
 /*protected*/ ActiveTrain* getActiveTrain();
 /*protected*/ QString getActiveTrainName();
 /*protected*/ int getSectionSeqNumber();
 /*protected*/ int getSectionDirection();
 /*protected*/ QString getSectionDirectionName();
 /*protected*/ bool getWaitingForTrain();
 /*protected*/ void setWaitingForTrain(bool set);
 /*protected*/ void addMeetingTrain(ActiveTrain* at);
 /*protected*/ void removeMeetingTrain(ActiveTrain* at);
 /*protected*/ QList<ActiveTrain*>* getMeetingTrainList();
 /*protected*/ void setWaitingOnBlock(Block* b);

 friend class DispatcherFrame;
 friend class AllocationRequestTableModel;
 friend class AutoAllocate;
};

#endif // ALLOCATIONREQUEST_H
