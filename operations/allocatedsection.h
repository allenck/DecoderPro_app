#ifndef ALLOCATEDSECTION_H
#define ALLOCATEDSECTION_H

#include <QObject>
#include "propertychangelistener.h"
#include "runnable.h"

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
 /*public*/ int getAllocationNumber();
 /*public*/ void setAllocationNumber(int n);
 /*public*/ Sensor* getForwardStoppingSensor();
 /*public*/ Sensor* getReverseStoppingSensor();
 /*public*/ void setIndex(int i);
 /*public*/ int getIndex();
 /*public*/ void setExitSignalListener(PropertyChangeListener* xSigListener);
 /*public*/ PropertyChangeListener* getExitSignalListener();
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);

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
 /*private*/ PropertyChangeListener* mSectionListener = NULL;
 /*private*/ bool mEntered;// = false;
 /*private*/ bool mExited;// = false;
 /*private*/ int mAllocationNumber;// = 0;     // used to keep track of allocation order
 /*private*/ Sensor* mForwardStoppingSensor;// = NULL;
 /*private*/ Sensor* mReverseStoppingSensor;// = NULL;
 /*private*/ EventListenerList* listenerList;
 /*private*/ /*synchronized*/ void handleSectionChange(PropertyChangeEvent* e);


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
 /*protected*/ void setStoppingSensors();

 friend class AutoActiveTrain;
 friend class ActiveTrain;
 friend class ASSPropertyChangeListener;
 friend class ASBPropertyChangeListener;
 friend class RespondToBlockStateChange;
};

class ASSPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AllocatedSection* as;
 public:
  ASSPropertyChangeListener(AllocatedSection* as) {this->as = as;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent* e) override{
   as->handleSectionChange(e);
  }
};

class ASBPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
  AllocatedSection* as;
  int index;
 public:
  ASBPropertyChangeListener(AllocatedSection* as, int index) {this->as = as; this->index = index;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent* e) override{
   as->handleBlockChange(index, e);
  }
};

class RespondToBlockStateChange : public  Runnable {
Q_OBJECT
 public:
    /*public*/ RespondToBlockStateChange(Block* b, int occ, AllocatedSection* as);
    /*public*/ void run() override;
 private:
    /*private*/ int _delay = 250;
    /*private*/ Block* _block = NULL;
    /*private*/ int _occ = 0;
    /*private*/ AllocatedSection* _aSection = NULL;
};

#endif // ALLOCATEDSECTION_H
