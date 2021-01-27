#ifndef DISPATCHERFRAME_H
#define DISPATCHERFRAME_H

#include "jmrijframe.h"
#include "scale.h"
#include "propertychangelistener.h"
#include "abstracttablemodel.h"
#include "timebase.h"
#include "rosterentry.h"
#include <QComboBox>


class Block;
class HeldMastDetails;
class SignalMast;
class Section;
class QCheckBox;
class QPushButton;
class ActiveTrainsTableModel;
class AllocationRequestTableModel;
class AllocatedSectionTableModel;
class Sensor;
class Timebase;
class AutoTrainsFrame;
class ActivateTrainFrame;
class OptionsMenu;
class AutoAllocate;
class AutoTurnouts;
class AllocatedSection;
class TransitManager;
class AllocationRequest;
class ActiveTrain;
class LayoutEditor;
class DispatcherFrame : public JmriJFrame
{
 Q_OBJECT
public:
 Q_INVOKABLE DispatcherFrame(QWidget* parent = 0);
 static DispatcherFrame* _instance;// = NULL;
 ~DispatcherFrame() {}
 DispatcherFrame(const DispatcherFrame&) :JmriJFrame() {}

 static /*public*/ DispatcherFrame* instance();
 enum SIGNALS
 {
  SIGNALHEAD = 0x00,
  SIGNALMAST = 0x01
 };
 /*public*/ void loadAtStartup();
 /*public*/ void terminateActiveTrain(ActiveTrain* at);
 /*public*/ AllocatedSection* allocateSection(AllocationRequest* ar, Section* ns);
 /*public*/ void releaseAllocatedSection(AllocatedSection* as,  bool terminatingTrain);
 /*public*/ void sectionOccupancyChanged();
 /*public*/ ActivateTrainFrame* getActiveTrainFrame();
 /*public*/  bool getNewTrainActive();
 /*public*/ void setNewTrainActive( bool boo);
 /*public*/  bool isMastHeldByDispatcher(SignalMast* sm, ActiveTrain* at);
 /*public*/ AutoTrainsFrame* getAutoTrainsFrame();
 /*public*/ ActiveTrain* createActiveTrain(QString transitID, QString trainID, int tSource, QString startBlockName,
         int startBlockSectionSequenceNumber, QString endBlockName, int endBlockSectionSequenceNumber,
          bool autoRun, QString dccAddress, int priority,  bool resetWhenDone,  bool reverseAtEnd,  bool allocateAllTheWay,
          bool showErrorMessages, JmriJFrame* frame);
 /*public*/ void allocateNewActiveTrain(ActiveTrain* at);
 /*public*/ void newTrainDone(ActiveTrain* at);
 /*public*/ QList<ActiveTrain*>* getActiveTrainsList();
 /*public*/ ActiveTrain* getActiveTrainForRoster(RosterEntry* re);
 /*public*/ void allocateExtraSection(JActionEvent* e, ActiveTrain* at);
 /*public*/ QString getSectionName(Section* sec);
 /*public*/ QString getClassName();


private:
 Logger* log;
 // Dispatcher options (saved to disk if user requests, and restored if present)
 /*private*/ LayoutEditor* _LE;// = NULL;
 /*private*/ int _SignalType;// = SIGNALHEAD;
 /*private*/ bool _UseConnectivity;// = false;
 /*private*/ bool _HasOccupancyDetection;// = false; // "true" if blocks have occupancy detection
 /*private*/ bool _TrainsFromRoster;// = true;
 /*private*/ bool _TrainsFromTrains;// = false;
 /*private*/ bool _TrainsFromUser;// = false;
 /*private*/ bool _AutoAllocate;// = false;
 /*private*/ bool _AutoRelease = false;
 /*private*/ bool _AutoTurnouts;// = false;
 /*private*/ bool _TrustKnownTurnouts;// = false;
 /*private*/ bool _ShortActiveTrainNames;// = false;
 /*private*/ bool _ShortNameInBlock;// = true;
 /*private*/ bool _RosterEntryInBlock;// = false;
 /*private*/ bool _ExtraColorForAllocated;// = true;
 /*private*/ bool _NameInAllocatedBlock;// = false;
 /*private*/ bool _UseScaleMeters;// = false;  // "true" if scale meters, "false" for scale feet
 /*private*/ Scale* _LayoutScale;// = Scale::HO;
 /*private*/ bool _SupportVSDecoder;// = false;
 /*private*/ int _MinThrottleInterval;// = 100; //default time (in ms) between consecutive throttle commands
 /*private*/ int _FullRampTime;// = 10000; //default time (in ms) for RAMP_FAST to go from 0% to 100%

 // operational instance variables
 /*private*/ QThread* autoAllocateThread ;
 /*private*/ QList<ActiveTrain*>* activeTrainsList;// = new ArrayList<ActiveTrain>();  // list of ActiveTrain objects
 /*private*/ QList<PropertyChangeListener*>* _atListeners;// = new ArrayList<java.beans.PropertyChangeListener>();
 /*private*/ QList<ActiveTrain*>* delayedTrains;// = new ArrayList<ActiveTrain>();  // list of delayed Active Trains
 /*private*/ QList<ActiveTrain*>* restartingTrainsList;// = new QList<ActiveTrain*>();  // list of Active Trains with restart requests
 /*private*/ TransitManager* transitManager;// = InstanceManager.getDefault(jmri.TransitManager.class);
 /*private*/ QList<AllocationRequest*>* allocationRequests;// = new ArrayList<AllocationRequest>();  // List of AllocatedRequest objects
 /*private*/ QList<AllocatedSection*>* allocatedSections;// = new ArrayList<AllocatedSection>();  // List of AllocatedSection objects
 /*private*/ bool optionsRead;// = false;
 /*private*/ AutoTurnouts* autoTurnouts;// = NULL;
 /*private*/ AutoAllocate* autoAllocate;// = NULL;
 /*private*/ OptionsMenu* optionsMenu;// = NULL;
 /*private*/ ActivateTrainFrame* atFrame;// = NULL;

 /*private*/ AutoTrainsFrame* _autoTrainsFrame;// = NULL;
 /*private*/ Timebase* fastClock;// = InstanceManager.getNullableDefault("Timebase");
 /*private*/ Sensor* fastClockSensor;// = InstanceManager.sensorManagerInstance().provideSensor("ISCLOCKRUNNING");
 ///*private*/ /*transient*/ PropertyChangeListener* minuteChangeListener;// = NULL;

 // dispatcher window variables
 /*private*/ QWidget* contentPane;// = NULL;
 /*private*/ ActiveTrainsTableModel* activeTrainsTableModel;// = NULL;
 /*private*/ QPushButton* addTrainButton;// = NULL;
 /*private*/ QPushButton* terminateTrainButton;// = NULL;
 /*private*/ QPushButton* cancelRestartButton;// = NULL;
 /*private*/ QPushButton* allocateExtraButton;// = NULL;
 /*private*/ QCheckBox* autoReleaseBox;// = NULL;
 /*private*/ QCheckBox* autoAllocateBox;// = NULL;
 /*private*/ AllocationRequestTableModel* allocationRequestTableModel;// = NULL;
 /*private*/ AllocatedSectionTableModel* allocatedSectionTableModel;// = NULL;
 void allocateNextRequested(int index);

 void initializeOptions();
 void openDispatcherWindow();
 /*private*/ int nowMinutes;// = 0;    // last read fast clock minutes
 /*private*/ int nowHours;// = 0;		// last read fast clock hours
 /*private*/ void cancelAllocationRequest(int index);
 /*private*/ void allocateRequested(int index);
 void releaseAllocatedSectionFromTable(int index);
 /*private*/ void checkAutoRelease();
 bool newTrainActive;// = false;
 QList<HeldMastDetails*>* heldMasts;// = new QList<HeldMastDetails*>();
 /*private*/ void removeHeldMast(SignalMast* sm, ActiveTrain* at);
 /*private*/ bool isInAllocatedSection(Block* b);
 /*private*/ void fastClockWarn( bool wMess);
 /*private*/ JmriJFrame* extraFrame;// = NULL;
 /*private*/ QWidget* extraPane;// = NULL;
 /*private*/ QComboBox* atSelectBox;// = new JComboBox<String>();
 /*private*/ QComboBox* extraBox;// = new JComboBox<String>();
 /*private*/ QList<Section*>* extraBoxList;// = new QList<Section>();
 /*private*/ int atSelectedIndex;// = -1;
 /*private*/ void initializeATComboBox();
 /*private*/ void initializeExtraComboBox();
 /*private*/ bool connected(Section* s1, Section* s2);
 QString _StoppingSpeedName;

private slots:
 void on_addTrainButton();
 void on_cancelRestartButton();
 void on_terminateTrainButton();
 void minuteChange(PropertyChangeEvent*);
 /*private*/ void handleActiveTrainChange(PropertyChangeEvent* e);
 /*private*/ void allocateExtraSection(/*ActionEvent* e*/);
 /*private*/ void handleAutoReleaseChanged(JActionEvent* e = 0);
 /*private*/ void handleATSelectionChanged(JActionEvent* e = 0);
 /*private*/ void handleAutoAllocateChanged(JActionEvent* e = 0);
 void terminateTrain(JActionEvent* e = 0);

protected:
 /*protected*/ int getSignalType();
 /*protected*/ void setStoppingSpeedName(QString speedName);
 /*protected*/ QString getStoppingSpeedName();
 /*protected*/ bool requestAllocation(ActiveTrain* activeTrain, Section* section, int direction, int seqNumber, bool showErrorMessages, JmriJFrame* frame);
 /*protected*/ AllocationRequest* findAllocationRequestInQueue(Section* s, int seq, int dir, ActiveTrain* at);
 /*protected*/ void addDelayedTrain(ActiveTrain* at);
 /*protected*/ JmriJFrame* dispatcherFrame;// = NULL;
 /*protected*/ void newFastClockMinute();
 /*protected*/ void queueScanOfAllocationRequests();
 /*protected*/ void queueReleaseOfReservedSections(QString trainName);
 /*protected*/ void queueWaitForEmpty();
 /*protected*/ void queueReleaseOfCompletedAllocations();
 /*protected*/ void stopStartAutoAllocateRelease();

 /*protected*/  bool isFastClockTimeGE(int hr, int min);

 // option access methods
 /*protected*/ LayoutEditor* getLayoutEditor();
 /*protected*/ void setLayoutEditor(LayoutEditor* editor);
 /*protected*/  bool getUseConnectivity();
 /*protected*/ void setUseConnectivity( bool set);
 /*protected*/ void setSignalType(int type);
 /*protected*/  bool getShortNameInBlock() ;
 /*protected*/ void setShortNameInBlock( bool set) ;
 /*protected*/  bool getRosterEntryInBlock() ;
 /*protected*/ void setRosterEntryInBlock( bool set);
 /*protected*/  bool getExtraColorForAllocated();
 /*protected*/ void setExtraColorForAllocated( bool set);
 /*protected*/  bool getNameInAllocatedBlock();
 /*protected*/ void setNameInAllocatedBlock( bool set);
 /*protected*/ Scale *getScale();
 /*protected*/ void setScale(Scale* sc);
 /*protected*/ void removeDelayedTrain(ActiveTrain* at);
 /*protected*/  bool getTrainsFromRoster();
 /*protected*/ void setTrainsFromRoster( bool set);
 /*protected*/  bool getTrainsFromTrains();
 /*protected*/ void setTrainsFromTrains( bool set);
 /*protected*/  bool getTrainsFromUser();
 /*protected*/ void setTrainsFromUser( bool set) ;
 /*protected*/  bool getAutoAllocate();
 /*protected*/ void setAutoAllocate( bool set) ;
 /*protected*/  bool getAutoTurnouts() ;
 /*protected*/ void setAutoTurnouts( bool set) ;
 /*protected*/  bool getTrustKnownTurnouts();
 /*protected*/ void setTrustKnownTurnouts( bool set);
 /*protected*/ int getMinThrottleInterval();
 /*protected*/ void setMinThrottleInterval(int set);
 /*protected*/ int getFullRampTime() ;
 /*protected*/ void setFullRampTime(int set);
 /*protected*/  bool getHasOccupancyDetection() ;
 /*protected*/ void setHasOccupancyDetection( bool set);
 /*protected*/  bool getUseScaleMeters();
 /*protected*/ void setUseScaleMeters( bool set);
 /*protected*/  bool getShortActiveTrainNames();
 /*protected*/ void setShortActiveTrainNames( bool set);
 /*protected*/  bool getSupportVSDecoder();
 /*protected*/ void setSupportVSDecoder( bool set);
 /*protected*/ QList<AllocatedSection*>* getAllocatedSectionsList();

 friend class ActiveTrain;
 friend class ActiveTrainsTableModel;
 friend class AllocationRequestTableModel;
 friend class AllocatedSectionTableModel;
 friend class AllocationRequest;
 friend class AutoTurnouts;
 friend class AutoAllocate;
 friend class AutoActiveTrain;
 friend class AutoEngineer;
 friend class AllocatedSection;
 friend class OptionsMenu;
 friend class OptionsFile;
 friend class OptionsMenuTest;
};

/**
 * Table model for Active Trains Table in Dispatcher window
 */
/*public*/ class ActiveTrainsTableModel : public AbstractTableModel // implements
//        java.beans.PropertyChangeListener
{
 Q_OBJECT
 DispatcherFrame* frame;
public:
 enum COLUMNS
 {
     TRANSIT_COLUMN = 0,
     TRAIN_COLUMN = 1,
     TYPE_COLUMN = 2,
     STATUS_COLUMN = 3,
     MODE_COLUMN = 4,
     ALLOCATED_COLUMN = 5,
     NEXTSECTION_COLUMN = 6,
     ALLOCATEBUTTON_COLUMN = 7
 };

    /*public*/ ActiveTrainsTableModel(DispatcherFrame* frame);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
public:
    ///*public*/ Class<?> getColumnClass(int c);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*public*/ int getRowCount() {return rowCount(QModelIndex());}
    /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

};

/**
 * Table model for Allocation Request Table in Dispatcher window
 */
/*public*/ class AllocationRequestTableModel : public AbstractTableModel //implements
        //java.beans.PropertyChangeListener
{
 Q_OBJECT
 DispatcherFrame* frame;
 public:
 enum COLUMNS
 {
     ACTIVE_COLUMN = 0,
     PRIORITY_COLUMN = 1,
     TRAINTYPE_COLUMN = 2,
     SECTION_COLUMN = 3,
     STATUS_COLUMN = 4,
     OCCUPANCY_COLUMN = 5,
     SECTIONLENGTH_COLUMN = 6,
     ALLOCATEBUTTON_COLUMN = 7,
     CANCELBUTTON_COLUMN = 8
 };
    /*public*/ AllocationRequestTableModel(DispatcherFrame* frame);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/**
 * Table model for Allocated Section Table
 */
/*public*/ class AllocatedSectionTableModel : public AbstractTableModel //implements
        //java.beans.PropertyChangeListener {
{
 Q_OBJECT
 DispatcherFrame* frame;
public:
 enum COLUMNS
 {
     ACTIVE_COLUMN = 0,
     SECTION_COLUMN = 1,
     OCCUPANCY_COLUMN = 2,
     USESTATUS_COLUMN = 3,

     RELEASEBUTTON_COLUMN = 4
 };

    /*public*/ AllocatedSectionTableModel(DispatcherFrame* frame);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ int columnCount(const QModelIndex &parent) const;
    /*public*/ int rowCount(const QModelIndex &parent) const;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    /*public*/ int getPreferredWidth(int col);
    /*public*/ QVariant data(const QModelIndex &index, int role) const;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
};

/*static*/ class HeldMastDetails  {

    SignalMast* mast;// = NULL;
    ActiveTrain* at;// = NULL;
public:
    HeldMastDetails(SignalMast* sm, ActiveTrain* a);
    ActiveTrain* getActiveTrain() ;
    SignalMast* getMast();
};
Q_DECLARE_METATYPE(DispatcherFrame)
#endif // DISPATCHERFRAME_H
