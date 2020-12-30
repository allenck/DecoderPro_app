#ifndef ACTIVATETRAINFRAME_H
#define ACTIVATETRAINFRAME_H

#include <QObject>
#include <QStringList>
#include "actionevent.h"

class JmriBeanComboBox;
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
class ActivateTrainFrame : public QObject
{
 Q_OBJECT
public:
 //explicit ActivateTrainFrame(QObject *parent = 0);
 /*public*/ ActivateTrainFrame(DispatcherFrame* d);
 /*public*/ void showActivateFrame(RosterEntry* re);
 /*public*/ void initiateTrain(JActionEvent* e, RosterEntry* re, Block* b);

signals:

public slots:

private:
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
 /*private*/ QComboBox* transitSelectBox; // =  new QComboBox();
 /*private*/ QList<Transit*>* transitBoxList; // =  new QList<Transit*>();
 /*private*/ QLabel* trainBoxLabel; // =  new JLabel("     " + tr("TrainBoxLabel") + ":");
 /*private*/ QComboBox* trainSelectBox; // =  new QComboBox();
 /*private*/ QList<RosterEntry*>* trainBoxList; // =  new QList<RosterEntry>();
 /*private*/ QLabel* trainFieldLabel; // =  new JLabel(tr("TrainBoxLabel") + ":");
 /*private*/ JTextField* trainNameField; // =  new JTextField(10);
 /*private*/ QLabel* dccAddressFieldLabel; // =  new JLabel("     " + tr("DccAddressFieldLabel") + ":");
 /*private*/ JTextField* dccAddressField; // =  new JTextField(6);
 /*private*/ QCheckBox* inTransitBox; // =  new QCheckBox(tr("TrainInTransit"));
 /*private*/ QComboBox* startingBlockBox; // =  new QComboBox();
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
 /*private*/ QComboBox*delayedStartBox; // =  new QComboBox(delayedStartString);
 /*private*/ QLabel* delayedReStartLabel; // =  new JLabel(tr("DelayRestart"));
 /*private*/ QLabel* delayReStartSensorLabel; // =  new JLabel(tr("RestartSensor"));
 /*private*/ QComboBox*delayedReStartBox; // =  new QComboBox(delayedStartString);
 /*private*/ JmriBeanComboBox* delaySensor; // =  new jmri.util.swing.JmriBeanComboBox(jmri.InstanceManager.sensorManagerInstance());
 /*private*/ JmriBeanComboBox* delayReStartSensor; // =  new jmri.util.swing.JmriBeanComboBox(jmri.InstanceManager.sensorManagerInstance());

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

protected:
 /*protected*/ void showActivateFrame();
 /*protected*/ void initiateTrain(JActionEvent* e = 0);

friend class DispatcherFrame;
};

#endif // ACTIVATETRAINFRAME_H
