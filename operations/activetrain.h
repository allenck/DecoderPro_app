#ifndef ACTIVETRAIN_H
#define ACTIVETRAIN_H

#include <QObject>
#include "logger.h"
#include "namedbeanhandle.h"

class AllocationRequest;
class PropertyChangeSupport;
class Transit;
class RosterEntry;
class Block;
class Section;
class AutoActiveTrain;
class AllocatedSection;
class Sensor;
class PropertyChangeListener;
class ActiveTrain : public QObject
{
 Q_OBJECT
public:
 //explicit ActiveTrain(QObject *parent = 0);
 /*public*/ ActiveTrain(Transit* t, QString name, int trainSource, QObject *parent = 0);
  /*public*/ void terminate();
  /*public*/ void dispose();
  /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);

 /**
  * Constants representing the Status of this ActiveTrain When created, the
  * Status of an Active Train is always WAITING,
  */
 enum STATUS
 {
 RUNNING = 0x01,   // running on the layout
 PAUSED = 0x02,    // paused for a number of fast minutes
 WAITING = 0x04,   // waiting for a section allocation
 WORKING = 0x08,   // actively working
 READY = 0x10,	  // completed work, waiting for restart
 STOPPED = 0x20,   // stopped by the dispatcher (auto trains only)
 DONE = 0x40	  // completed its transit
 };
 /**
  * Constants representing Type of ActiveTrains.
  */
 enum TYPE
 {
 NONE = 0x00,               // no train type defined
 LOCAL_PASSENGER = 0x01,    // low priority local passenger train
 LOCAL_FREIGHT = 0x02,      // low priority freight train performing local tasks
 THROUGH_PASSENGER = 0x03,  // normal priority through passenger train
 THROUGH_FREIGHT = 0x04,    // normal priority through freight train
 EXPRESS_PASSENGER = 0x05,  // high priority passenger train
 EXPRESS_FREIGHT = 0x06,    // high priority freight train
 MOW = 0x07			       // low priority maintenance of way train
};
 /**
  * Constants representing the mode of running of the Active Train The mode
  * is set when the Active Train is created. The mode may be switched during
  * a run.
  */
 enum MODE
 {
 AUTOMATIC = 0x02,   // requires mAutoRun to be "true" (auto trains only)
 MANUAL = 0x04,    // requires mAutoRun to be "true" (auto trains only)
 DISPATCHED = 0x08
};
 /**
  * Constants representing the source of the train information
  */
 enum SOURCE
 {
 ROSTER = 0x01,
 OPERATIONS = 0x02,
 USER = 0x04
 };

 enum DELAY
 {
   NODELAY = 0x00,
   TIMEDDELAY = 0x01,
   SENSORDELAY = 0x02
 };
 /*public*/ bool getStarted();
 /*public*/ void setStarted();
 /*public*/ Transit* getTransit();
 /*public*/ QString getTransitName();
 /*public*/ QString getActiveTrainName();
 /*public*/ QString getTrainName();
 /*public*/ int getTrainSource();
 /*public*/ void setRosterEntry(RosterEntry* re);
 /*public*/ RosterEntry* getRosterEntry();
 /*public*/ int getStatus();
 /*public*/ void setStatus(int status);
 /*public*/ QString getStatusText();
 /*public*/ bool isTransitReversed();
 /*public*/ void setTransitReversed(bool set);
 /*public*/ bool isAllocationReversed() ;
 /*public*/ void setAllocationReversed(bool set);
 /*public*/ int getDelayedStart();
 /*public*/ void setDelayedStart(int delay);
 /*public*/ int getDelayedRestart();
 /*public*/ void setDelayedReStart(int delay);
 /*public*/ int getDepartureTimeHr();
 /*public*/ void setDepartureTimeHr(int hr);
 /*public*/ int getDepartureTimeMin();
 /*public*/ void setDepartureTimeMin(int min);
 /*public*/ void setRestartDelay(int min);
 /*public*/ int getRestartDelay();
 /*public*/ int getRestartDepartHr();
 /*public*/ int getRestartDepartMin();
 /*public*/ void setTerminateWhenDone(bool boo);
 /*public*/ Sensor* getDelaySensor();
 /*public*/ QString getDelaySensorName();
 /*public*/ void setDelaySensor(Sensor* s);
 /*public*/ Sensor* getRestartSensor();
  /*public*/ QString getRestartSensorName();
  /*public*/ void setRestartSensor(Sensor* s);
 /*public*/ void initializeDelaySensor();
 /*public*/ void setAutoActiveTrain(AutoActiveTrain* aat);
 /*public*/ AutoActiveTrain* getAutoActiveTrain();
 /*public*/ void setTrainType(int type);
 /*public*/ void setTrainType(QString sType);
 /*public*/ int getTrainType();
 /*public*/ QString getTrainTypeText();
 /*public*/ int getMode();
 /*public*/ void setMode(int mode);
 /*public*/ QString getModeText();
 /*public*/ Section* getLastAllocatedSection();
 /*public*/ QString getLastAllocatedSectionName();
 /*public*/ Section* getNextSectionToAllocate() ;
 /*public*/ int getNextSectionSeqNumber() ;
 /*public*/ QString getNextSectionToAllocateName();
 /*public*/ int getAllocationDirectionFromSectionAndSeq(Section* s, int seqNo);
 /*public*/ int getPriority();
 /*public*/ void setPriority(int priority);
 /*public*/ bool getAutoRun();
 /*public*/ void setAutoRun(bool autoRun) ;
 /*public*/ QString getDccAddress();
 /*public*/ void setDccAddress(QString dccAddress);
 /*public*/ bool getResetWhenDone();
 /*public*/ void setResetWhenDone(bool s);
 /*public*/ bool getReverseAtEnd();
 /*public*/ void setReverseAtEnd(bool s) ;
 /*public*/ bool getAllocateAllTheWay();
 /*public*/ void setAllocateAllTheWay(bool s);
 /*public*/ void initializeRestartSensor();
 /*public*/ Block* getStartBlock();
 /*public*/ void setStartBlock(Block* sBlock);
 /*public*/ int getStartBlockSectionSequenceNumber() ;
 /*public*/ void setStartBlockSectionSequenceNumber(int sBlockSeqNum) ;
 /*public*/ Block* getEndBlock();
 /*public*/ void setEndBlock(Block* eBlock);
 /*public*/ Section* getEndBlockSection();
 /*public*/ void setEndBlockSection(Section* eSection);
 /*public*/ int getEndBlockSectionSequenceNumber();
 /*public*/ void setEndBlockSectionSequenceNumber(int eBlockSeqNum);
 /*public*/ QList<AllocatedSection *> getAllocatedSectionList();
 /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
 /*public*/ AllocationRequest* initializeFirstAllocation();
 /*public*/ void removeAllocatedSection(AllocatedSection* as);
 /*public*/ void allocateAFresh();
 /*public*/ void clearAllocations();
 /*public*/ void addAllocatedSection(AllocatedSection* as);
 /*public*/ QList<Block*> getBlockList();

signals:

public slots:

private:
 Logger* log;
 // instance variables
 /*private*/ Transit* mTransit;// = NULL;
 /*private*/ QString mTrainName;// = "";
 /*private*/ int mTrainSource;// = ROSTER;
 /*private*/ RosterEntry* mRoster;// = NULL;
 /*private*/ int mStatus;// = WAITING;
 /*private*/ int mMode;// = DISPATCHED;
 /*private*/ bool mTransitReversed;// = false;  // true if Transit is running in reverse
 /*private*/ bool mAllocationReversed;// = false;  // true if allocating Sections in reverse
 /*private*/ AutoActiveTrain* mAutoActiveTrain;// = NULL;
 /*private*/ QList<AllocatedSection*>* mAllocatedSections;// = new ArrayList<AllocatedSection>();
 /*private*/ Section* mLastAllocatedSection;// = NULL;
 /*private*/ Section* mSecondAllocatedSection;// = NULL;
 /*private*/ int mNextAllocationNumber;// = 1;
 /*private*/ Section* mNextSectionToAllocate;// = NULL;
 /*private*/ int mNextSectionSeqNumber;// = 0;
 /*private*/ int mNextSectionDirection;// = 0;
 /*private*/ Block* mStartBlock;// = NULL;
 /*private*/ int mStartBlockSectionSequenceNumber;// = 0;
 /*private*/ Block* mEndBlock;// = NULL;
 /*private*/ Section* mEndBlockSection;// = NULL;
 /*private*/ int mEndBlockSectionSequenceNumber;// = 0;
 /*private*/ int mPriority;// = 0;
 /*private*/ bool mAutoRun;// = false;
 /*private*/ QString mDccAddress;// = "";
 /*private*/ bool mResetWhenDone;// = true;
 /*private*/ bool mReverseAtEnd;// = false;
 /*private*/ bool mAllocateAllTheWay;// = false;

 /*private*/ int mDelayedRestart;// = NODELAY;
 /*private*/ int mDelayedStart;// = NODELAY;
/*private*/ int mDepartureTimeHr;// = 8;
/*private*/ int mDepartureTimeMin;// = 0;
 /*private*/ int mRestartDelay;// = 0;
/*private*/ NamedBeanHandle<Sensor*>* mStartSensor;// = NULL; // A Sensor that when changes state to active will trigger the trains start.
/*private*/ NamedBeanHandle<Sensor*>* mRestartSensor;// = NULL; // A Sensor that when changes state to active will trigger the trains start.
/*private*/ int mTrainType;// = LOCAL_FREIGHT;
 /*private*/ bool terminateWhenFinished;// = false;

// start up instance variables
/*private*/ bool mStarted;// = false;

 int restartHr;// = 0;
 int restartMin;// = 0;

 /*private*/ PropertyChangeListener* delaySensorListener;// = NULL;
 /*private*/ PropertyChangeListener* restartSensorListener;// = NULL;

 bool restartPoint;// = false;

 bool _holdAllocation;// = false;

 // Property Change Support
 PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
 /*private*/ QString getSectionName(Section* sc);
 /*private*/ void refreshPanel();
 /*private*/ bool connected(Block* b1, Block* b2);


protected:
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
 /*protected*/ void holdAllocation(bool boo);
 /*protected*/ bool holdAllocation();
 /*protected*/ bool reachedRestartPoint();
 /*protected*/ void restart();
 /*protected*/ void resetAllAllocatedSections();
 /*protected*/ void setRestart();
 /*protected*/ Section* getSecondAllocatedSection();
 /*protected*/ bool addEndSection(Section* s, int seq);
 /*protected*/ void removeLastAllocatedSection();
 /*protected*/ AllocatedSection* reverseAllAllocatedSections();

 friend class DispatcherFrame;
 friend class AutoTrainsFrame;
 friend class DSLPropertyChangeListener;
 friend class RSLPropertyChangeListener;
 friend class RespondToBlockStateChange;
 friend class AutoActiveTrain;
 friend class AutoAllocate;
};

class DSLPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  ActiveTrain* at;
 public:
  DSLPropertyChangeListener(ActiveTrain* at) {this->at = at;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent*) override;
};

class RSLPropertyChangeListener : public QObject, public PropertyChangeListener
{
  Q_OBJECT
  ActiveTrain* at;
 public:
  RSLPropertyChangeListener(ActiveTrain* at) {this->at = at;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void propertyChange(PropertyChangeEvent*) override;
};

#endif // ACTIVETRAIN_H
