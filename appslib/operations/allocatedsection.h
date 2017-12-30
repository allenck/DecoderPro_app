#ifndef ALLOCATEDSECTION_H
#define ALLOCATEDSECTION_H

#include <QObject>

class PropertyChangeEvent;
class TransitSection;
class Logger;
class Block;
class EventListenerList;
class Sensor;
class PropertyChangeListener;
class Section;
class ActiveTrain;
class AllocatedSection : public QObject
{
 Q_OBJECT
public:
 //explicit AllocatedSection(QObject *parent = 0);
 /*public*/ AllocatedSection(Section* s, ActiveTrain* at, int seq, Section* next, int nextSeqNo);
 /*public*/ /*synchronized*/ void initializeMonitorBlockOccupancy();
 /*public*/ Section* getSection();
 /*public*/ QString getSectionName();
 /*public*/ ActiveTrain* getActiveTrain();
 /*public*/ QString getActiveTrainName();
 /*public*/ int getSequence() ;
 /*public*/ Section* getNextSection();
 /*public*/ int getNextSectionSequence();
 /*public*/ void setNextSectionSequence(int i);
 /*public*/ bool getEntered();
 /*public*/ bool getExited();
 /*public*/ int getDirection();
 /*public*/ int getLength();
 /*public*/ void reset();
 /*public*/ /*synchronized*/ void dispose();

signals:

public slots:
private:
 Logger* log;
 // instance variables
 /*private*/ Section* mSection;// = NULL;
 /*private*/ ActiveTrain* mActiveTrain;// = NULL;
 /*private*/ int mSequence;// = 0;
 /*private*/ Section* mNextSection;// = NULL;
 /*private*/ int mNextSectionSequence;// = 0;
 /*private*/ PropertyChangeListener* mSectionListener;// = NULL;
 /*private*/ bool mEntered;// = false;
 /*private*/ bool mExited;// = false;
 /*private*/ int mAllocationNumber;// = 0;     // used to keep track of allocation order
 /*private*/ Sensor* mForwardStoppingSensor;// = NULL;
 /*private*/ Sensor* mReverseStoppingSensor;// = NULL;
 /*private*/ EventListenerList* listenerList;


 // instance variables used with automatic running of trains
 /*private*/ int mIndex;// = 0;
 /*private*/ PropertyChangeListener* mExitSignalListener;// = NULL;
 /*private*/ QList<PropertyChangeListener*>* mBlockListeners;// = new QList<PropertyChangeListener*>();
 /*private*/ QVector<Block*>* mBlockList;// = NULL;
 /*private*/ QList<Block*>* mActiveBlockList;// = new ArrayList<jmri.Block>();

private slots:
 /*private*/ /*synchronized*/ void handleBlockChange(int index, PropertyChangeEvent* e);


protected:
 /*protected*/ bool setNextSection(Section* sec, int i);
 /*protected*/ TransitSection* getTransitSection();
 /*protected*/ Block* getExitBlock();
 /*protected*/ Block* getEnterBlock(AllocatedSection* previousAllocatedSection);
 /*protected*/ /*synchronized*/ void addToActiveBlockList(Block* b);
 /*protected*/ /*synchronized*/ void removeFromActiveBlockList(Block* b) ;
 /*protected*/ /*synchronized*/ bool isInActiveBlockList(Block* b);
 /*protected*/ void firePropertyChangeEvent(PropertyChangeEvent* evt);
 /*protected*/ void firePropertyChangeEvent(QString name, QVariant oldVal, QVariant newVal);

 friend class AutoActiveTrain;
};

#endif // ALLOCATEDSECTION_H
