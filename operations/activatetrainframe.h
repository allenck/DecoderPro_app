#ifndef ACTIVATETRAINFRAME_H
#define ACTIVATETRAINFRAME_H

#include <QObject>
#include <QStringList>
#include "actionevent.h"
#include "activetrain.h"
#include "jmrijframe.h"
#include "jpanel.h"
#include "jlabel.h"
#include "jcheckbox.h"
#include "autoactivetrain.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "namedbeancombobox.h"

class TrainInfo;
class ActionListener;
class Logger;
class Block;
class RosterEntry;
class QCheckBox;
class JmriJFrame;
class Transit;
class TransitManager;
class JTextField;
class QComboBox;
class QLabel;
class QPushButton;
class ActiveTrain;
class TrainInfoFile;
class DispatcherFrame;
class ActivateTrainFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit ActivateTrainFrame(QObject *parent = 0);
 /*public*/ ActivateTrainFrame(DispatcherFrame* d);
 /*public*/ void showActivateFrame(RosterEntry* re);
 /*public*/ void initiateTrain(JActionEvent* e, RosterEntry* re, Block* b);
 /*public*/ QString getClassName() override {return "jmri.jmrit.dispatcher.ActivateTrainFrame";}

signals:

public slots:

private:
  static Logger* log;
 // operational instance variables
 /*private*/ DispatcherFrame* _dispatcher; // = NULL;
 /*private*/ TrainInfoFile* _tiFile; // =  NULL;
 /*private*/ bool _TrainsFromUser; // =  false;
 /*private*/ bool _TrainsFromRoster; // =  true;
 /*private*/ bool _TrainsFromTrains; // =  false;
 /*private*/ QList<ActiveTrain*>* _ActiveTrainsList; // =  NULL;
 /*private*/ TransitManager* _TransitManager; // =  InstanceManager.getDefault("TransitManager");
 /*private*/ QString _trainInfoName; // =  "";

 // initiate train window variables
 /*private*/ Transit* selectedTransit; // =  NULL;
 ///*private*/ String selectedTrain; // =  "";
 /*private*/ JmriJFrame* initiateFrame; // =  NULL;
 /*private*/ QWidget* initiatePane; // =  NULL;
 /*private*/ JComboBox* transitSelectBox; // =  new QComboBox();
 /*private*/ QList<Transit*>* transitBoxList; // =  new QList<Transit*>();
 /*private*/ QLabel* trainBoxLabel; // =  new JLabel("     " + tr("TrainBoxLabel") + ":");
 /*private*/ JComboBox* trainSelectBox; // =  new QComboBox();
 /*private*/ QList<RosterEntry*>* trainBoxList; // =  new QList<RosterEntry>();
 /*private*/ QLabel* trainFieldLabel; // =  new JLabel(tr("TrainBoxLabel") + ":");
 /*private*/ JTextField* trainNameField; // =  new JTextField(10);
 /*private*/ QLabel* dccAddressFieldLabel; // =  new JLabel("     " + tr("DccAddressFieldLabel") + ":");
 /*private*/ JTextField* dccAddressField; // =  new JTextField(6);
 /*private*/ QCheckBox* inTransitBox; // =  new QCheckBox(tr("TrainInTransit"));
 /*private*/ JComboBox* startingBlockBox; // =  new QComboBox();
 /*private*/ QList<Block*>* startingBlockBoxList; // =  new QList<Block*>();
 /*private*/ QList<int>* startingBlockSeqList; // =  new QList<int>();
 /*private*/ QComboBox* destinationBlockBox; // =  new QComboBox();
 /*private*/ QList<Block*>* destinationBlockBoxList; // =  new QList<Block*>();
 /*private*/ QList<int>* destinationBlockSeqList; // =  new QList<Integer*>();
 /*private*/ QPushButton* addNewTrainButton; // =  NULL;
 /*private*/ QPushButton* loadButton; // =  NULL;
 /*private*/ QPushButton* saveButton; // =  NULL;
 /*private*/ QPushButton* deleteButton; // =  NULL;
 /*private*/ QCheckBox* autoRunBox; // =  new QCheckBox(tr("AutoRun"));
 /*private*/ QCheckBox* loadAtStartupBox; // =  new QCheckBox(tr("LoadAtStartup"));
 /*private*/ QCheckBox* allocateAllTheWayBox; // =  new QCheckBox(tr("AllocateAllTheWay"));
 /*private*/ QCheckBox* terminateWhenDoneBox; // =  new QCheckBox(tr("TerminateWhenDone"));
 /*private*/ JTextField* priorityField; // =  new JTextField(6);
 /*private*/ QCheckBox* resetWhenDoneBox; // =  new QCheckBox(tr("ResetWhenDone"));
 /*private*/ QCheckBox* reverseAtEndBox; // =  new QCheckBox(tr("ReverseAtEnd"));
 QList<int> delayedStartInt; // =  new int[]{ActiveTrain::NODELAY, ActiveTrain::TIMEDDELAY, ActiveTrain::SENSORDELAY};
 QStringList delayedStartString; // =  QStringList() << tr("DelayedStartNone") << tr("DelayedStartTimed") << tr("DelayedStartSensor");
 /*private*/ JComboBox*delayedStartBox; // =  new QComboBox(delayedStartString);
 /*private*/ QLabel* delayedReStartLabel; // =  new JLabel(tr("DelayRestart"));
 /*private*/ QLabel* delayReStartSensorLabel; // =  new JLabel(tr("RestartSensor"));
 /*private*/ QComboBox*delayedReStartBox; // =  new QComboBox(delayedStartString);
 /*private*/ NamedBeanComboBox* delaySensor; // =  new jmri.util.swing.JmriBeanComboBox(jmri.InstanceManager.sensorManagerInstance());
 /*private*/ NamedBeanComboBox* delayReStartSensor; // =  new jmri.util.swing.JmriBeanComboBox(jmri.InstanceManager.sensorManagerInstance());

 /*private*/ JTextField* departureHrField; // =  new JTextField(2);
 /*private*/ JTextField* departureMinField; // =  new JTextField(2);
 /*private*/ QLabel* departureTimeLabel; // =  new JLabel(tr("DepartureTime"));
 /*private*/ QLabel* departureSepLabel; // =  new JLabel(":");

 /*private*/ JTextField* delayMinField; // =  new JTextField(3);
 /*private*/ QLabel* delayMinLabel; // =  new JLabel(tr("RestartTimed"));

 /*private*/ QComboBox*trainTypeBox; // =  new QComboBox();
 // Note: See also items related to automatically running trains near the end of this module
 /*private*/ bool setComboBox(QComboBox*box, QString txt);

 bool transitsFromSpecificBlock; // =  false;
 /*private*/ void initializeFreeTransitsCombo(QList<Transit*> transitList);
 /*private*/ QString getBlockName(Block* b);
 /*private*/ void initializeTrainTypeBox();
 /*private*/ bool checkResetWhenDone();
 ActionListener* trainSelectBoxListener = NULL;
 /*private*/ void initializeFreeTrainsCombo();
 /*private*/ bool isTrainFree(QString rName);
 /*private*/ bool isAddressFree(int addr);
 /*private*/ void initializeStartingBlockCombo();
 /*private*/ void initializeDestinationBlockCombo();
 /*private*/ void trainInfoToDialog(TrainInfo* info);
 /*private*/ TrainInfo* dialogToTrainInfo();
 /*private*/ QString normalizeXmlFileName(QString name);
 int delayModeFromBox(QComboBox* box);
 void setDelayModeBox(int mode, QComboBox*box);
 /**
  * The following are for items that are only for automatic running of
  * ActiveTrains They are isolated here to simplify changing them in the
  * future initializeAutoRunItems - initializes the display of auto run items
  * in this window initializeAutoRunValues - initializes the values of auto
  * run items from values in a saved train info file hideAutoRunItems - hides
  * all auto run items in this window showAutoRunItems - shows all auto run
  * items in this window autoTrainInfoToDialog - gets auto run items from a
  * train info, puts values in items, and initializes auto run dialog items
  * autoTrainItemsToTrainInfo - copies values of auto run items to train info
  * for saving to a file readAutoRunItems - reads and checks values of all
  * auto run items. returns true if OK, sends appropriate messages and
  * returns false if not OK setAutoRunItems - sets the user entered auto run
  * items in the new AutoActiveTrain
  */
 // auto run items in ActivateTrainFrame
 /*private*/ JPanel* pa1 = new JPanel();
 /*private*/ JLabel* speedFactorLabel = new JLabel(tr("SpeedFactorLabel"));
 /*private*/ JTextField* speedFactorField = new JTextField(5);
 /*private*/ QLabel* maxSpeedLabel = new JLabel(tr("MaxSpeedLabel"));
 /*private*/ JTextField* maxSpeedField = new JTextField(5);
 /*private*/ JPanel* pa2 = new JPanel();
 /*private*/ QLabel* rampRateLabel = new JLabel(tr("RampRateBoxLabel"));
 /*private*/ QComboBox* rampRateBox = new QComboBox();
 /*private*/ JPanel* pa3 = new JPanel();
 /*private*/ /*final*/ JCheckBox* soundDecoderBox = new JCheckBox(tr("SoundDecoder"));
 /*private*/ /*final*/ JCheckBox* runInReverseBox = new JCheckBox(tr("RunInReverse"));
 /*private*/ JPanel* pa4 = new JPanel();
 /*private*/ /*final*/ JCheckBox*  resistanceWheelsBox = new JCheckBox(tr("ResistanceWheels"));
 /*private*/ QLabel* trainLengthLabel = new JLabel(tr("MaxTrainLengthLabel"));
 /*private*/ JTextField* maxTrainLengthField = new JTextField(5);
 // auto run variables
 float _speedFactor = 1.0f;
 float _maxSpeed = 0.6f;
 int _rampRate = AutoActiveTrain::RAMP_NONE;
 bool _resistanceWheels = true;
 bool _runInReverse = false;
 bool _soundDecoder = false;
 float _maxTrainLength = 200.0f;
 /*private*/ void hideAutoRunItems();

 private slots:
 /*private*/ void handleTransitSelectionChanged(/*ActionEvent e*/);
 /*private*/ void handleInTransitClick(/*ActionEvent e*/);
 /*private*/ void handleDelayStartClick(/*ActionEvent e*/);
 /*private*/ void handleResetWhenDoneClick(/*ActionEvent e*/);
 /*private*/ void handleReverseAtEndBoxClick(/*ActionEvent e*/);
 /*private*/ void handleAutoRunClick(/*ActionEvent e*/);
 /*private*/ void handleStartingBlockSelectionChanged(/*ActionEvent e*/);
 /*private*/ void cancelInitiateTrain(/*ActionEvent e*/);
 /*private*/ void addNewTrain(/*ActionEvent e*/);
 /*private*/ void loadTrainInfo(/*ActionEvent e*/);
 /*private*/ void saveTrainInfo(/*ActionEvent e*/);
 /*private*/ void deleteTrainInfo(/*ActionEvent e*/);
 /*private*/ void setAutoRunDefaults();
 /*private*/ void initializeAutoRunItems();
 /*private*/ void initializeAutoRunValues();
 /*private*/ void showAutoRunItems();
 /*private*/ void autoTrainInfoToDialog(TrainInfo* info);
 /*private*/ void autoRunItemsToTrainInfo(TrainInfo* info);
 /*private*/ bool readAutoRunItems();
 /*private*/ void setAutoRunItems(AutoActiveTrain* aaf);
 /*private*/ void initializeRampCombo();


protected:
 /*protected*/ void showActivateFrame();
 /*protected*/ void initiateTrain(JActionEvent* e = 0);

friend class DispatcherFrame;
};

#endif // ACTIVATETRAINFRAME_H
