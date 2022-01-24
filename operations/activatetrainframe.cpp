#include "activatetrainframe.h"
#include "dispatcherframe.h"
#include "instancemanager.h"
#include "transitmanager.h"
#include "jmrijframe.h"
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "jtextfield.h"
#include "jbutton.h"
#include "jmribeancombobox.h"
#include "jtextfield.h"
#include "traininfofile.h"
#include "jmrijframe.h"
#include "jseparator.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "roster.h"
#include "rosterentry.h"
#include "train.h"
#include "trainmanager.h"
#include "instancemanager.h"
#include "traininfo.h"
#include "stringutil.h"
#include "vptr.h"
#include "autotrainsframe.h"

//ActivateTrainFrame::ActivateTrainFrame(QObject *parent) : QObject(parent)
//{

//}
/**
 * Displays the Activate New Train dialog and processes information entered
 * there.
 *
 * <P>
 * This module works with Dispatcher, which initiates the display of the dialog.
 * Dispatcher also creates the ActiveTrain::
 *
 * <P>
 * This file is part of JMRI.
 * <P>
 * JMRI is open source software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published by the
 * Free Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author	Dave Duchamp Copyright (C) 2009
 */
////*public*/ class ActivateTrainFrame {

/*public*/ ActivateTrainFrame::ActivateTrainFrame(DispatcherFrame* d) {
 // operational instance variables
 _dispatcher = NULL;
 _tiFile = NULL;
 _TrainsFromUser = false;
 _TrainsFromRoster = true;
 _TrainsFromTrains = false;
 _ActiveTrainsList = NULL;
 _TransitManager = (TransitManager*)InstanceManager::getDefault("TransitManager");
 _trainInfoName = "";

 // initiate train window variables
 selectedTransit = NULL;
 ///*private*/ String selectedTrain = "";
 initiateFrame = NULL;
 initiatePane = NULL;
 transitSelectBox = new JComboBox();
 transitBoxList = new QList<Transit*>();
 trainBoxLabel = new QLabel("     " + tr("Train") + ":");
 trainSelectBox = new JComboBox();
 trainBoxList = new QList<RosterEntry*>();
 trainFieldLabel = new QLabel(tr("Train") + ":");
 trainNameField = new JTextField(10);
 dccAddressFieldLabel = new QLabel("     " + tr("DCC Address") + ":");
 dccAddressField = new JTextField(6);
 inTransitBox = new QCheckBox(tr("TrainInTransit"));
 startingBlockBox = new JComboBox();
 startingBlockBoxList = new QList<Block*>();
 startingBlockSeqList = new QList<int>();
 destinationBlockBox = new QComboBox();
 destinationBlockBoxList = new QList<Block*>();
 destinationBlockSeqList = new QList<int>();
 addNewTrainButton = NULL;
 loadButton = NULL;
 saveButton = NULL;
 deleteButton = NULL;
 autoRunBox = new QCheckBox(tr("AutoRun"));
 loadAtStartupBox = new QCheckBox(tr("LoadAtStartup"));
 allocateAllTheWayBox = new QCheckBox(tr("AllocateAllTheWay"));
 terminateWhenDoneBox = new QCheckBox(tr("TerminateWhenDone"));
 priorityField = new JTextField(6);
 resetWhenDoneBox = new QCheckBox(tr("ResetWhenDone"));
 reverseAtEndBox = new QCheckBox(tr("ReverseAtEnd"));
 delayedStartInt = QList<int>() << ActiveTrain::NODELAY <<  ActiveTrain::TIMEDDELAY;
 delayedStartString = QStringList() << tr("No Delay") << tr("Timed Delay") << tr("Sensor Delay");
 delayedStartBox = new JComboBox(/*delayedStartString*/);
 delayedStartBox->addItems(delayedStartString);
 delayedReStartLabel = new QLabel(tr("Add Delay"));
 delayReStartSensorLabel = new QLabel(tr("Restart on Sensor"));
 delayedReStartBox = new QComboBox(/*delayedStartString*/);
 delayedReStartBox->addItems(delayedStartString);
 delaySensor = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());
 delayReStartSensor = new NamedBeanComboBox(InstanceManager::sensorManagerInstance());

 departureHrField = new JTextField(2);
 departureMinField = new JTextField(2);
 departureTimeLabel = new QLabel(tr("Departure Time"));
 departureSepLabel = new QLabel(":");

 delayMinField = new JTextField(3);
 delayMinLabel = new QLabel(tr("Time in Minutes to wait"));

 trainTypeBox = new QComboBox();
 // Note: See also items related to automatically running trains near the end of this module

transitsFromSpecificBlock = false;


    _dispatcher = d;
    _tiFile = new TrainInfoFile();
}

//static final ResourceBundle rb = ResourceBundle
//        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");


/**
 * Open up a new train window, for a given roster entry located in a
 * specific block
 */
/*public*/ void ActivateTrainFrame::initiateTrain(JActionEvent* e, RosterEntry* re, Block* b) {
    initiateTrain(e);
    if (_TrainsFromRoster && re != NULL) {
        setComboBox(trainSelectBox, re->getId());
        //Add in some bits of code as some point to filter down the transits that can be used.
    }
    if (b != NULL && selectedTransit != NULL) {
        QList<Transit*> transitList = _TransitManager->getListUsingBlock(b);
        QList<Transit*> transitEntryList = _TransitManager->getListEntryBlock(b);
        for (Transit* t : transitEntryList) {
            if (!transitList.contains(t)) {
                transitList.append(t);
            }
        }
        transitsFromSpecificBlock = true;
        initializeFreeTransitsCombo(transitList);
        QList<Block*>* tmpBlkList = new QList<Block*>();
        if (selectedTransit->getEntryBlocksList()->contains(b)) {
            tmpBlkList = selectedTransit->getEntryBlocksList();
            inTransitBox->setChecked(false);
        } else if (selectedTransit->containsBlock(b)) {
            tmpBlkList = selectedTransit->getInternalBlocksList();
            inTransitBox->setChecked(true);
        }
        QList<int>* tmpSeqList = selectedTransit->getBlockSeqList();
        for (int i = 0; i < tmpBlkList->size(); i++) {
            if (tmpBlkList->at(i) == b) {
                setComboBox(startingBlockBox, getBlockName(b) + "-" + tmpSeqList->at(i));
                break;
            }
        }
    }
}

/**
 * Displays a window that allows a new ActiveTrain to be activated
 *
 * Called by Dispatcher in response to the dispatcher clicking the New Train
 * button
 */
/*protected*/ void ActivateTrainFrame::initiateTrain(JActionEvent* /*e*/) {
    // set Dispatcher defaults
#if 1
    _TrainsFromRoster = _dispatcher->getTrainsFromRoster();
    _TrainsFromTrains = _dispatcher->getTrainsFromTrains();
    _TrainsFromUser = _dispatcher->getTrainsFromUser();
    _ActiveTrainsList = _dispatcher->getActiveTrainsList();
    // create window if needed
    if (initiateFrame == NULL) {
        initiateFrame = new JmriJFrameX(tr("Add Train"), false, true);
        initiateFrame->addHelpMenu("package.jmri.jmrit.dispatcher.NewTrain", true);
        initiatePane = initiateFrame->getContentPane();
        initiatePane->setLayout(new QVBoxLayout());//initiateFrame->getContentPane(), BoxLayout.Y_AXIS));
        // add buttons to load and save train information
        JPanel* p0 = new JPanel();
        p0->setLayout(new FlowLayout());
        p0->layout()->addWidget(loadButton = new JButton(tr("Load")));
//        loadButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e)
        connect(loadButton, &JButton::clicked, [=]{
                loadTrainInfo(/*e*/);
//            }
        });
        loadButton->setToolTip(tr("Click to load previously saved Train information (optional)."));
        p0->layout()->addWidget(saveButton = new JButton(tr("Save")));
//        saveButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(saveButton, &JButton::clicked, [=]{
                saveTrainInfo(/*e*/);
//            }
        });
        saveButton->setToolTip(tr("Click to save Train information from this pane (optional)."));
        p0->layout()->addWidget(deleteButton = new JButton(tr("Delete")));
//        deleteButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(deleteButton, &JButton::clicked, [=]{
                deleteTrainInfo(/*e*/);
//            }
        });
        deleteButton->setToolTip(tr("DeleteBuClick to delete a previously saved Train information file.ttonHint"));
        initiatePane->layout()->addWidget(p0);
        initiatePane->layout()->addWidget(new JSeparator());
        // add items relating to both manually run and automatic trains.
        JPanel* p1 = new JPanel();
        p1->setLayout(new FlowLayout());
        p1->layout()->addWidget(new JLabel(tr("Transit") + " :"));
        p1->layout()->addWidget(transitSelectBox);
//        transitSelectBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(transitSelectBox, &JComboBox::currentIndexChanged, [=]{
                handleTransitSelectionChanged(/*e*/);
//            }
        });
        transitSelectBox->setToolTip(tr("TransitBoxHint"));
        p1->layout()->addWidget(trainBoxLabel);
        p1->layout()->addWidget(trainSelectBox);
        trainSelectBox->setToolTip(tr("TrainBoxHint"));
        initiatePane->layout()->addWidget(p1);
        JPanel* p1a = new JPanel();
        p1a->setLayout(new FlowLayout());
        p1a->layout()->addWidget(trainFieldLabel);
        p1a->layout()->addWidget(trainNameField);
        trainNameField->setToolTip(tr("Enter a Train name (short 5 - 15 letter description)."));
        p1a->layout()->addWidget(dccAddressFieldLabel);
        p1a->layout()->addWidget(dccAddressField);
        dccAddressField->setToolTip(tr("Enter the DCC Address of the Train; needed for Automatic Running."));
        initiatePane->layout()->addWidget(p1a);
        JPanel* p2 = new JPanel();
        p2->setLayout(new FlowLayout());
        p2->layout()->addWidget(inTransitBox);
//        inTransitBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(inTransitBox, &QCheckBox::toggled, [=]{
                handleInTransitClick(/*e*/);
//            }
        });
        inTransitBox->setToolTip(tr("InTransitBoxHint"));
        initiatePane->layout()->addWidget(p2);
        JPanel* p3 = new JPanel();
        p3->setLayout(new FlowLayout());
        p3->layout()->addWidget(new JLabel(tr("StartingBlockBoxLabel") + " :"));
        p3->layout()->addWidget(startingBlockBox);
        startingBlockBox->setToolTip(tr("StartingBlockBoxHint"));
//        startingBlockBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(startingBlockBox, &JComboBox::currentIndexChanged, [=]{
                handleStartingBlockSelectionChanged(/*e*/);
//            }
        });
        initiatePane->layout()->addWidget(p3);
        JPanel* p4 = new JPanel();
        p4->setLayout(new FlowLayout());
        p4->layout()->addWidget(new JLabel(tr("Destination Location of Train") + ":"));
        p4->layout()->addWidget(destinationBlockBox);
        destinationBlockBox->setToolTip(tr("Select the Block where the Train will be located when Transit ends."));
        initiatePane->layout()->addWidget(p4);
        JPanel* p4a = new JPanel();
        p4a->setLayout(new FlowLayout());
        p4a->layout()->addWidget(allocateAllTheWayBox);
        allocateAllTheWayBox->setToolTip(tr("AllocateAllTheWayBoxHint"));
        initiatePane->layout()->addWidget(p4a);
        JPanel* p6 = new JPanel();
        p6->setLayout(new FlowLayout());
        p6->layout()->addWidget(resetWhenDoneBox);
//        resetWhenDoneBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(resetWhenDoneBox, &QCheckBox::toggled, [=]{
                handleResetWhenDoneClick(/*e*/);
//            }
        });
        resetWhenDoneBox->setToolTip(tr("ResetWhenDoneBoxHint"));
        initiatePane->layout()->addWidget(p6);
        JPanel* p6a = new JPanel();
        p6a->setLayout(new FlowLayout());
//        ((FlowLayout) p6a->getLayout())->setVgap(1);
        p6a->layout()->addWidget(delayedReStartLabel);
        p6a->layout()->addWidget(delayedReStartBox);
//        delayedReStartBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(delayedStartBox, &JComboBox::currentIndexChanged, [=]{
                handleResetWhenDoneClick(/*e*/);
//            }
        });
        delayedReStartBox->setToolTip(tr("Add a delay between the circuits, when running continuously"));
        initiatePane->layout()->addWidget(p6a);

        JPanel* p6b = new JPanel();
        p6b->setLayout(new FlowLayout());
//        ((FlowLayout) p6b.getLayout())->setVgap(1);
        p6b->layout()->addWidget(delayMinLabel);
        p6b->layout()->addWidget(delayMinField);
        delayMinField->setText("0");
        delayMinField->setToolTip(tr("RestartTimedHint"));
        p6b->layout()->addWidget(delayReStartSensorLabel);
        p6b->layout()->addWidget(delayReStartSensor);
        delayReStartSensor->setAllowNull(true);
        handleResetWhenDoneClick(/*NULL*/);
        initiatePane->layout()->addWidget(p6b);

        JPanel* p10 = new JPanel();
        p10->setLayout(new FlowLayout());
        p10->layout()->addWidget(reverseAtEndBox);
        reverseAtEndBox->setToolTip(tr("ReverseAtEndBoxHint"));
        initiatePane->layout()->addWidget(p10);
//        reverseAtEndBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(reverseAtEndBox, &QCheckBox::toggled, [=]{
                handleReverseAtEndBoxClick(/*e*/);
//            }
        });
        JPanel* p10a = new JPanel();
        p10a->setLayout(new FlowLayout());
        p10a->layout()->addWidget(terminateWhenDoneBox);
        initiatePane->layout()->addWidget(p10a);

        JPanel* p8 = new JPanel();
        p8->setLayout(new FlowLayout());
        p8->layout()->addWidget(new JLabel(tr("Priority") + " :"));
        p8->layout()->addWidget(priorityField);
        priorityField->setToolTip(tr("Enter priority: larger number = higher priority."));
        priorityField->setText("5");
        p8->layout()->addWidget(new JLabel("     "));
        p8->layout()->addWidget(new JLabel(tr("TrainTypeBoxLabel")));
        initializeTrainTypeBox();
        p8->layout()->addWidget(trainTypeBox);
        trainTypeBox->setCurrentIndex(1);
        trainTypeBox->setToolTip(tr("TrainTypeBoxHint"));
        initiatePane->layout()->addWidget(p8);
        JPanel* p9 = new JPanel();
        p9->setLayout(new FlowLayout());
        p9->layout()->addWidget(new JLabel(tr("DelayedStart")));
        p9->layout()->addWidget(delayedStartBox);
        delayedStartBox->setToolTip(tr("DelayedStartHint"));
//        delayedStartBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(delayedStartBox, &JComboBox::currentIndexChanged, [=]{
                handleDelayStartClick(/*e*/);
//            }
        });
        p9->layout()->addWidget(departureTimeLabel);
        p9->layout()->addWidget(departureHrField);
        departureHrField->setText("08");
        departureHrField->setToolTip(tr("Enter fast clock departure time hours (24-hour clock: 00-23)."));
        p9->layout()->addWidget(departureSepLabel);
        p9->layout()->addWidget(departureMinField);
        departureMinField->setText("00");
        departureMinField->setToolTip(tr("Enter fast clock departure time hours (24-hour clock: 00-23)."));
        p9->layout()->addWidget(delaySensor);
        delaySensor->setAllowNull(true);
        handleDelayStartClick(/*NULL*/);
        initiatePane->layout()->addWidget(p9);

        JPanel* p11 = new JPanel();
        p11->setLayout(new FlowLayout());
        p11->layout()->addWidget(loadAtStartupBox);
        loadAtStartupBox->setToolTip(tr("Select for Train to be loaded when Dispatcher starts. Press [Create]/[Update Train] to take effect."));
        loadAtStartupBox->setChecked(false);
        initiatePane->layout()->addWidget(p11);

        initiatePane->layout()->addWidget(new JSeparator());
        JPanel* p5 = new JPanel();
        p5->setLayout(new FlowLayout());
        p5->layout()->addWidget(autoRunBox);
//        autoRunBox->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(autoRunBox, &QCheckBox::toggled, [=]{
                handleAutoRunClick(/*e*/);
//            }
        });
        autoRunBox->setToolTip(tr("Select to request this Train be run automatically by JMRI Dispatcher."));
        autoRunBox->setChecked(false);
        initiatePane->layout()->addWidget(p5);

        initializeAutoRunItems();
        initiatePane->layout()->addWidget(new JSeparator());
        JPanel* p7 = new JPanel();
        p7->setLayout(new FlowLayout());
        QPushButton* cancelButton = NULL;
        p7->layout()->addWidget(cancelButton = new JButton(tr("Cancel")));
//        cancelButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(cancelButton, &QPushButton::clicked, [=]{
                cancelInitiateTrain(/*e*/);
//            }
        });
        cancelButton->setToolTip(tr("Click to cancel without activating a new Train."));
        p7->layout()->addWidget(addNewTrainButton = new JButton(tr("Add New Train")));
//        addNewTrainButton->addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(addNewTrainButton, &QPushButton::clicked, [=]{
                addNewTrain(/*e*/);
//            }
        });
        addNewTrainButton->setToolTip(tr("AddNewTrainButtonHint"));
        initiatePane->layout()->addWidget(p7);
    }
    if (_TrainsFromRoster || _TrainsFromTrains) {
        trainBoxLabel->setVisible(true);
        trainSelectBox->setVisible(true);
        trainFieldLabel->setVisible(false);
        trainNameField->setVisible(false);
        dccAddressFieldLabel->setVisible(false);
        dccAddressField->setVisible(false);
    } else if (_TrainsFromUser) {
        trainNameField->setText("");
        trainBoxLabel->setVisible(false);
        trainSelectBox->setVisible(false);
        trainFieldLabel->setVisible(true);
        trainNameField->setVisible(true);
        dccAddressFieldLabel->setVisible(true);
        dccAddressField->setVisible(true);
    }
    setAutoRunDefaults();
    autoRunBox->setChecked(false);
    loadAtStartupBox->setChecked(false);
    allocateAllTheWayBox->setChecked(false);
    initializeFreeTransitsCombo( QList<Transit*>());
    initializeFreeTrainsCombo();
    initiateFrame->pack();
    initiateFrame->setVisible(true);
#endif
}
#if 1
/*private*/ void ActivateTrainFrame::initializeTrainTypeBox() {
    trainTypeBox->clear();
    trainTypeBox->addItem("<" + tr("None").toLower() + ">"); // <none>
    trainTypeBox->addItem(tr("LOCAL_PASSENGER"));
    trainTypeBox->addItem(tr("LOCAL_FREIGHT"));
    trainTypeBox->addItem(tr("THROUGH_PASSENGER"));
    trainTypeBox->addItem(tr("THROUGH_FREIGHT"));
    trainTypeBox->addItem(tr("EXPRESS_PASSENGER"));
    trainTypeBox->addItem(tr("EXPRESS_FREIGHT"));
    trainTypeBox->addItem(tr("MOW"));
    // NOTE: The above must correspond in order and name to definitions in ActiveTrain::java.
}

/*private*/ void ActivateTrainFrame::handleTransitSelectionChanged(/*ActionEvent e*/) {
    int index = transitSelectBox->currentIndex();
    if (index < 0) {
        return;
    }
    Transit* t = transitBoxList->value(index);
    if ((t != NULL) && (t != selectedTransit)) {
        selectedTransit = t;
        initializeStartingBlockCombo();
        initializeDestinationBlockCombo();
        initiateFrame->pack();
    }
}

/*private*/ void ActivateTrainFrame::handleInTransitClick(/*ActionEvent e*/) {
    if (!inTransitBox->isChecked() &&  selectedTransit->getEntryBlocksList()->isEmpty()) {
        JOptionPane::showMessageDialog(initiateFrame, tr("The Selected Transit doesn't have any Entry Blocks"), tr("Information"),
                JOptionPane::INFORMATION_MESSAGE);
        inTransitBox->setChecked(true);
    }
    initializeStartingBlockCombo();
    initializeDestinationBlockCombo();
    initiateFrame->pack();
}

/*private*/ bool ActivateTrainFrame::checkResetWhenDone() {
    if ((!reverseAtEndBox->isChecked()) && resetWhenDoneBox->isChecked()
            && (!selectedTransit->canBeResetWhenDone())) {
        resetWhenDoneBox->setChecked(false);
        JOptionPane::showMessageDialog(initiateFrame, tr("Sorry, the selected Transit is not set up for continuous running.\nSee Transit Table help for more information."), tr("Information"),
                JOptionPane::INFORMATION_MESSAGE);
        return false;
    }
    return true;
}

/*private*/ void ActivateTrainFrame::handleDelayStartClick(/*ActionEvent e*/) {
    departureHrField->setVisible(false);
    departureMinField->setVisible(false);
    departureTimeLabel->setVisible(false);
    departureSepLabel->setVisible(false);
    delaySensor->setVisible(false);
    if (delayedStartBox->currentText() ==(tr("Timed Delay"))) {
        departureHrField->setVisible(true);
        departureMinField->setVisible(true);
        departureTimeLabel->setVisible(true);
        departureSepLabel->setVisible(true);
    } else if (delayedStartBox->currentText() == (tr("Sensor Delay"))) {
        delaySensor->setVisible(true);
    }
}

/*private*/ void ActivateTrainFrame::handleResetWhenDoneClick(/*ActionEvent e*/) {
    delayMinField->setVisible(false);
    delayMinLabel->setVisible(false);
    delayedReStartLabel->setVisible(false);
    delayedReStartBox->setVisible(false);
    delayReStartSensorLabel->setVisible(false);
    delayReStartSensor->setVisible(false);
    if (resetWhenDoneBox->isChecked()) {
        delayedReStartLabel->setVisible(true);
        delayedReStartBox->setVisible(true);
        if (delayedReStartBox->currentText() == (tr("Timed Delay"))) {
            delayMinField->setVisible(true);
            delayMinLabel->setVisible(true);
        } else if (delayedReStartBox->currentText() == (tr("Sensor Delay"))) {
            delayReStartSensor->setVisible(true);
            delayReStartSensorLabel->setVisible(true);
        }
    }
    handleReverseAtEndBoxClick(/*e*/);
    initiateFrame->pack();
}

/*private*/ void ActivateTrainFrame::handleReverseAtEndBoxClick(/*ActionEvent e*/) {
    if (reverseAtEndBox->isChecked() || resetWhenDoneBox->isChecked()) {
        terminateWhenDoneBox->setChecked(false);
        terminateWhenDoneBox->setEnabled(false);
    } else {
        terminateWhenDoneBox->setEnabled(true);
    }
}

/*private*/ void ActivateTrainFrame::handleAutoRunClick(/*ActionEvent e*/) {
    if (autoRunBox->isChecked()) {
        showAutoRunItems();
    } else {
        hideAutoRunItems();
    }
    initiateFrame->pack();
}

/*private*/ void ActivateTrainFrame::handleStartingBlockSelectionChanged(/*ActionEvent e*/) {
    initializeDestinationBlockCombo();
    initiateFrame->pack();
}

/*private*/ void ActivateTrainFrame::cancelInitiateTrain(/*ActionEvent e*/) {
    initiateFrame->setVisible(false);
    initiateFrame->dispose();  // prevent this window from being listed in the Window menu.
    initiateFrame = NULL;
    _dispatcher->newTrainDone(NULL);
}

/**
 * Handles press of "Add New Train" button by edit-checking populated values
 *  then (if no errors) creating an ActiveTrain and (optionally) an AutoActiveTrain
 */
/*private*/ void ActivateTrainFrame::addNewTrain(/*ActionEvent e*/) {
    // get information
    if (selectedTransit == NULL) {
        // no transits available
        JOptionPane::showMessageDialog(initiateFrame, tr("No Transits are available.\nCannot create a new Active Train."),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        cancelInitiateTrain(/*NULL*/);
        return;
    }
    QString transitName = selectedTransit->getSystemName();
    QString trainName = "";
    int index = startingBlockBox->currentIndex();
    if (index < 0) {
        return;
    }
    QString startBlockName = startingBlockBoxList->value(index)->getSystemName();
    int startBlockSeq = startingBlockSeqList->at(index);
    index = destinationBlockBox->currentIndex();
    if (index < 0) {
        return;
    }
    QString endBlockName = destinationBlockBoxList->value(index)->getSystemName();
    int endBlockSeq = destinationBlockSeqList->at(index);
    bool autoRun = autoRunBox->isChecked();
    if (!checkResetWhenDone()) {
        return;
    }
    bool resetWhenDone = resetWhenDoneBox->isChecked();
    bool reverseAtEnd = reverseAtEndBox->isChecked();
    bool allocateAllTheWay = allocateAllTheWayBox->isChecked();
    int delayedStart = delayModeFromBox(delayedStartBox);
    int delayedReStart = delayModeFromBox(delayedReStartBox);
    int departureTimeHours = 8;
    bool ok;
        departureTimeHours = departureHrField->text().toInt(&ok);
        if ((departureTimeHours < 0) || (departureTimeHours > 23)) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "BadEntry3").arg(departureHrField->text()),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            log->warn("Range error in Departure Time Hours field");
            return;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "BadEntry2").arg(departureHrField->text()),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        log->warn("Conversion exception in departure time hours field");
        return;
    }
    int departureTimeMinutes = 8;
    //bool ok;
        departureTimeMinutes = departureMinField->text().toInt(&ok);
        if ((departureTimeMinutes < 0) || (departureTimeMinutes > 59)) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "BadEntry3").arg(departureMinField->text()),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            log->warn("Range error in Departure Time Minutes field");
            return;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "BadEntry2").arg(departureMinField->text()),
                tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);
        log->warn("Conversion exception in departure time minutes field");
        return;
    }
    int delayRestartMinutes = 0;
//    try {
        delayRestartMinutes = delayMinField->text().toInt();
        if ((delayRestartMinutes < 0)) {
            JOptionPane::showMessageDialog(initiateFrame, delayMinField->text(),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            log->warn("Range error in Delay Restart Time Minutes field");
            return;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "BadEntry2").arg(delayMinField->text()),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        log->warn("Conversion exception in restart delay minutes field");
        return;
    }
    int tSource = 0;
    QString dccAddress = "unknown";
    if (_TrainsFromRoster) {
        index = trainSelectBox->currentIndex();
        if (index < 0) {
            // no trains available
            JOptionPane::showMessageDialog(initiateFrame, tr("Error14"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            cancelInitiateTrain(/*NULL*/);
            return;
        }
        trainName =  trainSelectBox->currentText();
        RosterEntry* r = trainBoxList->at(index);
        dccAddress = r->getDccAddress();
        if (!isAddressFree(r->getDccLocoAddress()->getNumber())) {
            // DCC address is already in use by an Active Train
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error40").arg(dccAddress), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }

        tSource = ActiveTrain::ROSTER;

        if (trainTypeBox->currentIndex() != 0
                && (r->getAttribute("DisptacherTrainType") == NULL
                || r->getAttribute("DispatcherTrainType")!=("" + trainTypeBox->currentText()))) {
            r->putAttribute("DispatcherTrainType", "" + trainTypeBox->currentText());
            r->updateFile();
            Roster::getDefault()->writeRoster();
        }
    } else if (_TrainsFromTrains) {
        tSource = ActiveTrain::OPERATIONS;
        index = trainSelectBox->currentIndex();
        if (index < 0) {
            // no trains available
            JOptionPane::showMessageDialog(initiateFrame, tr("Error14"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            cancelInitiateTrain(/*NULL*/);
            return;
        }
        trainName =  trainSelectBox->currentIndex();
    } else if (_TrainsFromUser) {
        trainName = trainNameField->text();
        if ((trainName == NULL) || trainName == ("")) {
            // no train name entered
            JOptionPane::showMessageDialog(initiateFrame, tr("Error14"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            return;
        }
        if (!isTrainFree(trainName)) {
            // train name is already in use by an Active Train
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error24").arg(trainName), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        dccAddress = dccAddressField->text();
        int address = -1;
        try {
            address = dccAddress.toInt();
        } catch (NumberFormatException* ex) {
            JOptionPane::showMessageDialog(initiateFrame, tr("Error23"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            log->error("Conversion exception in dccAddress field");
            return;
        }
        if ((address < 1) || (address > 9999)) {
            JOptionPane::showMessageDialog(initiateFrame, tr("Error23"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            return;
        }
        if (!isAddressFree(address)) {
            // DCC address is already in use by an Active Train
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error40").arg(address), tr("ErrorTitle"),
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        tSource = ActiveTrain::USER;
    }
    int priority = 5;
    //bool ok;
        priority = priorityField->text().toInt(&ok);
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "BadEntry").arg(priorityField->text()), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        log->error("Conversion exception in priority field");
        return;
    }
    int trainType = trainTypeBox->currentIndex();
    if (autoRunBox->isChecked()) {
        if (!readAutoRunItems()) {
            return;
        }
    }

    // create a new Active Train
    ActiveTrain* at = _dispatcher->createActiveTrain(transitName, trainName, tSource, startBlockName,
            startBlockSeq, endBlockName, endBlockSeq, autoRun, dccAddress, priority,
            resetWhenDone, reverseAtEnd, allocateAllTheWay, true, initiateFrame);
    if (at == NULL) {
        return;  // error message sent by createActiveTrain
    }
    if (tSource == ActiveTrain::ROSTER) {
        at->setRosterEntry(trainBoxList->at(trainSelectBox->currentIndex()));
    }
    at->setDelayedStart(delayedStart);
    at->setDelayedReStart(delayedReStart);
    at->setDepartureTimeHr(departureTimeHours);
    at->setDepartureTimeMin(departureTimeMinutes);
    at->setRestartDelay(delayRestartMinutes);
    at->setDelaySensor(VPtr<Sensor>::asPtr(delaySensor->currentData()));
    if ((_dispatcher->isFastClockTimeGE(departureTimeHours, departureTimeMinutes) && delayedStart != ActiveTrain::SENSORDELAY) ||
            delayedStart==ActiveTrain::NODELAY) {
        at->setStarted();
    }
    at->setRestartSensor(VPtr<Sensor>::asPtr(delayReStartSensor->currentData()));
    at->setTrainType(trainType);
    at->setTerminateWhenDone(terminateWhenDoneBox->isChecked());
    if (autoRunBox->isChecked()) {
        AutoActiveTrain* aat = new AutoActiveTrain(at);
        setAutoRunItems(aat);
        if (!aat->initialize()) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error27").arg(at->getTrainName()), tr("Information"),
                    JOptionPane::INFORMATION_MESSAGE);
        }
        _dispatcher->getAutoTrainsFrame()->addAutoActiveTrain(aat);
    }
    _dispatcher->allocateNewActiveTrain(at);
    initiateFrame->setVisible(false);
    initiateFrame->dispose();  // prevent this window from being listed in the Window menu.
    initiateFrame = NULL;
    _dispatcher->newTrainDone(at);
}
#endif
/*private*/ void ActivateTrainFrame::initializeFreeTransitsCombo(QList<Transit*> transitList) {
    QList<QString> allTransits =  _TransitManager->getSystemNameList();
    transitSelectBox->clear();
    transitBoxList->clear();
    if (transitList.isEmpty()) {
        for (int i = 0; i < allTransits.size(); i++) {
            QString tName = allTransits.at(i);
            Transit* t = _TransitManager->getBySystemName(tName);
            transitList.append(t);
        }

    }
    for (Transit* t : transitList) {
        bool free = true;
        for (int j = 0; j < _ActiveTrainsList->size(); j++) {
            ActiveTrain* at = _ActiveTrainsList->value(j);
            if (t == at->getTransit()) {
                free = false;
            }
        }
        if (free) {
            QString tName = t->getSystemName();
            transitBoxList->append(t);
            QString uname = t->getUserName();
            if ((uname != NULL) && ( uname != ("")) && (uname!=(tName))) {
                tName = tName + "(" + uname + ")";
            }
            transitSelectBox->addItem(tName);
        }
    }
    if (transitBoxList->size() > 0) {
        transitSelectBox->setCurrentIndex(0);
        selectedTransit = transitBoxList->value(0);
    } else {
        selectedTransit = NULL;
    }
}
#if 1

/*private*/ void ActivateTrainFrame::initializeFreeTrainsCombo() {
#if 1
    //trainSelectBox->removeActionListener(trainSelectBoxListener);
    disconnect(trainSelectBox, SIGNAL(currentIndexChanged()));
    trainSelectBox->clear();
    trainBoxList->clear();
    if (_TrainsFromRoster) {
        // initialize free trains from roster
        QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if (l.size() > 0) {
            for (int i = 0; i < l.size(); i++) {
                RosterEntry* r = l.at(i);
                QString rName = r->titleString();
                int rAddr = r->getDccLocoAddress()->getNumber();
                if (isTrainFree(rName) && isAddressFree(rAddr)) {
                    trainBoxList->append(r);
                    trainSelectBox->addItem(rName);
                }
            }
        }
        if (trainSelectBoxListener == NULL) {
//            trainSelectBoxListener = new ActionListener() {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
         connect(trainSelectBox, &JComboBox::currentIndexChanged, [=]{
                    RosterEntry* r = trainBoxList->at(trainSelectBox->getSelectedIndex());
                    if (transitsFromSpecificBlock) {
                        //resets the transit box if required
                        transitsFromSpecificBlock = false;
                        initializeFreeTransitsCombo( QList<Transit*>());
                    }
                    if (r->getAttribute("DispatcherTrainType") != NULL && r->getAttribute("DispatcherTrainType") !=("")) {
                        trainTypeBox->setCurrentText(r->getAttribute("DispatcherTrainType"));
                    }
//                }
            });
        }
//        trainSelectBox->addActionListener(trainSelectBoxListener);
    } else if (_TrainsFromTrains) {
        // initialize free trains from operations
        QList<Operations::Train*> trains = ((Operations::TrainManager*)InstanceManager::getDefault("Operations::TrainManager"))->getTrainsByNameList();
        if (trains.size() > 0) {
            for (int i = 0; i < trains.size(); i++) {
                Operations::Train* t = trains.at(i);
                if (t != NULL) {
                    QString tName = t->getName();
                    if (isTrainFree(tName)) {
                        trainSelectBox->addItem(tName);
                    }
                }
            }
        }
    }
    if (trainBoxList->size() > 0) {
        trainSelectBox->setCurrentIndex(0);
    }
#endif
}

/*private*/ bool ActivateTrainFrame::isTrainFree(QString rName) {
    for (int j = 0; j < _ActiveTrainsList->size(); j++) {
        ActiveTrain* at = _ActiveTrainsList->at(j);
        if (rName == (at->getTrainName())) {
            return false;
        }
    }
    return true;
}

/*private*/ bool ActivateTrainFrame::isAddressFree(int addr) {
    for (int j = 0; j < _ActiveTrainsList->size(); j++) {
        ActiveTrain* at = _ActiveTrainsList->at(j);
        if (addr == at->getDccAddress().toInt()) {
            return false;
        }
    }
    return true;
}

/*private*/ void ActivateTrainFrame::initializeStartingBlockCombo() {
    startingBlockBox->clear();
    startingBlockBoxList->clear();
    if (!inTransitBox->isChecked() &&  selectedTransit->getEntryBlocksList()->isEmpty()) {
        inTransitBox->setChecked(true);
    }
    if (inTransitBox->isChecked()) {
        startingBlockBoxList =  selectedTransit->getInternalBlocksList();
    } else {
        startingBlockBoxList =  selectedTransit->getEntryBlocksList();
    }
    startingBlockSeqList =  selectedTransit->getBlockSeqList();
    bool found = false;
    for (int i = 0; i < startingBlockBoxList->size(); i++) {
        Block* b = startingBlockBoxList->at(i);
        int seq = startingBlockSeqList->at(i);
        startingBlockBox->addItem(getBlockName(b) + "-" + seq);
        if (!found && b->getState() == Block::OCCUPIED) {
            startingBlockBox->setCurrentText(getBlockName(b) + "-" + QString::number(seq));
            found = true;
        }
    }
}

/*private*/ void ActivateTrainFrame::initializeDestinationBlockCombo() {
    destinationBlockBox->clear();
    destinationBlockBoxList->clear();
    int index = startingBlockBox->currentIndex();
    if (index < 0) {
        return;
    }
    Block* startBlock = startingBlockBoxList->at(index);
    destinationBlockBoxList =  selectedTransit->getDestinationBlocksList(
            startBlock, inTransitBox->isChecked());
    destinationBlockSeqList =  selectedTransit->getDestBlocksSeqList();
    for (int i = 0; i < destinationBlockBoxList->size(); i++) {
        Block* b = destinationBlockBoxList->at(i);
        QString bName = getBlockName(b);
        if ( selectedTransit->getBlockCount(b) > 1) {
            int seq = destinationBlockSeqList->at(i);
            bName = bName + "-" + seq;
        }
        destinationBlockBox->addItem(bName);
    }
}
#endif
/*private*/ QString ActivateTrainFrame::getBlockName(Block* b) {
    if (b != NULL) {
        QString sName = b->getSystemName();
        QString uName = b->getUserName();
        if ((uName != NULL) && (uName!=("")) && (uName != (sName))) {
            return (sName + "(" + uName + ")");
        }
        return sName;
    }
    return " ";
}

/*protected*/ void ActivateTrainFrame::showActivateFrame() {
    if (initiateFrame != NULL) {
        initializeFreeTransitsCombo( QList<Transit*>());
        initiateFrame->setVisible(true);
    } else {
        _dispatcher->newTrainDone(NULL);
    }
}

/*public*/ void ActivateTrainFrame::showActivateFrame(RosterEntry* /*re*/) {
    showActivateFrame();
}
#if 1
/*private*/ void ActivateTrainFrame::loadTrainInfo(/*ActionEvent e*/) {
    QStringList names = _tiFile->getTrainInfoFileNames();
    QList<QVariant> variantlist;
    foreach(QString s, names){
      variantlist << s;
    }
    TrainInfo* info = NULL;
    if (names.length() > 0) {
        //prompt user to select a single train info filename from directory list
        QVariant selName = JOptionPane::showInputDialog(initiateFrame,
                tr("LoadTrainChoice"), tr("Load Train"),
                JOptionPane::QUESTION_MESSAGE, QIcon(), (variantlist), names[0]);
        if ((selName == QVariant()) || (( selName)==(""))) {
            return;
        }
        //read xml data from selected filename and move it into the new train dialog box
        _trainInfoName =  selName.toString();
        try {
            info = _tiFile->readTrainInfo( selName.toString());
            if (info != NULL) {
                // process the information just read
                trainInfoToDialog(info);
            }
        } catch (IOException* ioe) {
            log->error("IO Exception when reading train info file " + ioe->getMessage());
        } catch (JDOMException* jde) {
            log->error("JDOM Exception when reading train info file " + jde->getMessage());
        }
    }
    handleDelayStartClick(/*NULL*/);
    handleReverseAtEndBoxClick(/*NULL*/);
}

/*private*/ void ActivateTrainFrame::saveTrainInfo(/*ActionEvent e*/) {
    TrainInfo* info = dialogToTrainInfo();

    // get file name
    QString eName = "";
    eName = JOptionPane::showInputDialog(initiateFrame,
            tr("EnterFileName") + " :", _trainInfoName);
    if (eName == NULL) {  //Cancel pressed
        return;
    }
    if (eName.length() < 1) {
        JOptionPane::showMessageDialog(initiateFrame, tr("Error25"),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        return;
    }
    QString fileName = normalizeXmlFileName(eName);
    _trainInfoName = fileName;
    // check if train info file name is in use
    QStringList names = _tiFile->getTrainInfoFileNames();
    if (names.length() > 0) {
        bool found = false;
        for (int i = 0; i < names.length(); i++) {
            if (fileName ==(names[i])) {
                found = true;
            }
        }
        if (found) {
            // file by that name is already present
            int selectedValue = JOptionPane::showOptionDialog(initiateFrame,
                    tr("Question3").arg(fileName),
                    tr("Warning"), JOptionPane::YES_NO_OPTION,
                    JOptionPane::QUESTION_MESSAGE, QIcon(), QVariantList{tr("FileYes"),
                        tr("FileNo")}, tr("FileNo"));
            if (selectedValue == 1) {
                return;   // return without writing if "No" response
            }
        }
    }
    // write the Train Info file
    try {
        _tiFile->writeTrainInfo(info, fileName);
    } //catch (org.jdom2.JDOMException jde) {
    //	log.error("JDOM exception writing Train Info: "+jde);
    //}
    catch (IOException* ioe) {
        log->error("IO exception writing Train Info: " + ioe->getMessage());
    }
}

/*private*/ void ActivateTrainFrame::deleteTrainInfo(/*ActionEvent e*/) {
    QList<QString> names = _tiFile->getTrainInfoFileNames();
    QList<QVariant> variantlist;
    foreach(QString s, names){
      variantlist << s;
    }
    if (names.length() > 0) {
        QVariant selName = JOptionPane::showInputDialog(initiateFrame,
                tr("Please select a Train Info file to delete."), tr("Delete Train"),
                JOptionPane::QUESTION_MESSAGE, QIcon(), (variantlist), names[0]);
        if ((selName == QVariant()) || (( selName)==(""))) {
            return;
        }
        _tiFile->deleteTrainInfoFile( selName.toString());
    }
}

/*private*/ void ActivateTrainFrame::trainInfoToDialog(TrainInfo* info) {
    if (!setComboBox(transitSelectBox, info->getTransitName())) {
        log->warn("Transit " +  info->getTransitName() + " from file not in Transit menu");
        JOptionPane::showMessageDialog(initiateFrame,
                tr("Transit name from file - \"%1\" is not available for selection.").arg( info->getTransitName()),
                NULL, JOptionPane::WARNING_MESSAGE);
    }
    _TrainsFromRoster =  info->getTrainFromRoster();
    _TrainsFromTrains =  info->getTrainFromTrains();
    _TrainsFromUser =  info->getTrainFromUser();
    if (_TrainsFromRoster || _TrainsFromTrains) {
        initializeFreeTrainsCombo();
        if (!setComboBox(trainSelectBox,  info->getTrainName())) {
            log->warn("Train " +  info->getTrainName() + " from file not in Train menu");
            JOptionPane::showMessageDialog(initiateFrame,
                    tr("Transit name from file - \"%1\" is not available for selection.").arg(info->getTrainName()),
                    NULL, JOptionPane::WARNING_MESSAGE);
        }
    } else if (_TrainsFromUser) {
        trainNameField->setText( info->getTrainName());
        dccAddressField->setText( info->getDCCAddress());
    }
    inTransitBox->setChecked( info->getTrainInTransit());
    initializeStartingBlockCombo();
    initializeDestinationBlockCombo();
    setComboBox(startingBlockBox,  info->getStartBlockName());
    setComboBox(destinationBlockBox,  info->getDestinationBlockName());
    priorityField->setText(QString::number( info->getPriority()));
    resetWhenDoneBox->setChecked( info->getResetWhenDone());
    reverseAtEndBox->setChecked( info->getReverseAtEnd());
    setDelayModeBox( info->getDelayedStart(), delayedStartBox);
    //delayedStartBox->setChecked( info->getDelayedStart());
    departureHrField->setText(QString::number( info->getDepartureTimeHr()));
    departureMinField->setText(QString::number( info->getDepartureTimeMin()));
    delaySensor->setCurrentText(info->getDelaySensorName());

    setDelayModeBox( info->getDelayedRestart(), delayedReStartBox);
    delayMinField->setText(QString::number( info->getRestartDelayMin()));
    delayReStartSensor->setCurrentText(info->getRestartSensorName());
    terminateWhenDoneBox->setChecked( info->getTerminateWhenDone());
    setComboBox(trainTypeBox,  info->getTrainType());
    autoRunBox->setChecked( info->getAutoRun());
    loadAtStartupBox->setChecked( info->getLoadAtStartup());
    allocateAllTheWayBox->setChecked( info->getAllocateAllTheWay());
    autoTrainInfoToDialog(info);
}

/*private*/ TrainInfo* ActivateTrainFrame::dialogToTrainInfo() {
    TrainInfo* info = new TrainInfo();
    info->setTransitName( transitSelectBox->currentText());
    if (_TrainsFromRoster || _TrainsFromTrains) {
        info->setTrainName( trainSelectBox->currentText());
        info->setDCCAddress(" ");
    } else if (_TrainsFromUser) {
        info->setTrainName(trainNameField->text());
        info->setDCCAddress(dccAddressField->text());
    }
    info->setTrainInTransit(inTransitBox->isChecked());
    info->setStartBlockName( startingBlockBox->currentText());
    info->setDestinationBlockName( destinationBlockBox->currentText());
    info->setTrainFromRoster(_TrainsFromRoster);
    info->setTrainFromTrains(_TrainsFromTrains);
    info->setTrainFromUser(_TrainsFromUser);
    info->setPriority(priorityField->text().toUInt());
    info->setResetWhenDone(resetWhenDoneBox->isChecked());
    info->setReverseAtEnd(reverseAtEndBox->isChecked());
    info->setDelayedStart(delayModeFromBox(delayedStartBox));
    info->setDelaySensorName(delaySensor->getSelectedItemDisplayName());
    info->setDepartureTimeHr(departureHrField->text().toUInt());
    info->setDepartureTimeMin(departureMinField->text().toUInt());
    info->setTrainType( trainTypeBox->currentText());
    info->setAutoRun(autoRunBox->isChecked());
    info->setLoadAtStartup(loadAtStartupBox->isChecked());
    info->setAllocateAllTheWay(allocateAllTheWayBox->isChecked());
    info->setDelayedRestart(delayModeFromBox(delayedReStartBox));
    info->setRestartSensorName(delayReStartSensor->getSelectedItemDisplayName());
    info->setRestartDelayMin(delayMinField->text().toInt());
    info->setTerminateWhenDone(terminateWhenDoneBox->isChecked());
    autoRunItemsToTrainInfo(info);
    return info;
}

// Normalizes a suggested xml file name.  Returns NULL string if a valid name cannot be assembled
/*private*/ QString ActivateTrainFrame::normalizeXmlFileName(QString name) {
    if (name.length() < 1) {
        return "";
    }
    QString newName = name;
    // strip off .xml or .XML if present
    if ((name.endsWith(".xml")) || (name.endsWith(".XML"))) {
        newName = name.mid(0, name.length() - 4);
        if (newName.length() < 1) {
            return "";
        }
    }
    // replace all non-alphanumeric characters with underscore
    newName = newName.replace("[\\W]", "_");
    return (newName + ".xml");
}
#endif
/*private*/ bool ActivateTrainFrame::setComboBox(QComboBox*box, QString txt) {
    bool found = false;
    for (int i = 0; i < box->count(); i++) {
        if (txt == box->itemText(i)) {
            box->setCurrentIndex(i);
            found = true;
        }
    }
    if (!found) {
        box->setCurrentIndex(0);
    }
    return found;
}
#if 1
int ActivateTrainFrame::delayModeFromBox(QComboBox* box) {
    QString mode =  box->currentText();
    int result = StringUtil::getStateFromName(mode, delayedStartInt.toVector(), delayedStartString.toVector());

    if (result < 0) {
        log->warn("unexpected mode string in turnoutMode: " + mode);
        throw  IllegalArgumentException();
    }
    return result;
}

void ActivateTrainFrame::setDelayModeBox(int mode, QComboBox*box) {
    QString result = StringUtil::getNameFromState(mode, delayedStartInt.toVector(), delayedStartString);
    box->setCurrentText(result);
}



/*private*/ void ActivateTrainFrame::setAutoRunDefaults() {
    _speedFactor = 1.0f;
    _maxSpeed = 0.6f;
    _rampRate = AutoActiveTrain::RAMP_NONE;
    _resistanceWheels = true;
    _runInReverse = false;
    _soundDecoder = false;
    _maxTrainLength = 100.0f;
}

/*private*/ void ActivateTrainFrame::initializeAutoRunItems() {
    initializeRampCombo();
    pa1->setLayout(new FlowLayout());
    pa1->layout()->addWidget(speedFactorLabel);
    pa1->layout()->addWidget(speedFactorField);
    speedFactorField->setToolTip(tr("SpeedFactorHint"));
    pa1->layout()->addWidget(new JLabel("   "));
    pa1->layout()->addWidget(maxSpeedLabel);
    pa1->layout()->addWidget(maxSpeedField);
    maxSpeedField->setToolTip(tr("MaxSpeedHint"));
    initiatePane->layout()->addWidget(pa1);
    pa2->setLayout(new FlowLayout());
    pa2->layout()->addWidget(rampRateLabel);
    pa2->layout()->addWidget(rampRateBox);
    rampRateBox->setToolTip(tr("RampRateBoxHint"));
    initiatePane->layout()->addWidget(pa2);
    pa3->setLayout(new FlowLayout());
    pa3->layout()->addWidget(soundDecoderBox);
    soundDecoderBox->setToolTip(tr("SoundDecoderBoxHint"));
    pa3->layout()->addWidget(new JLabel("   "));
    pa3->layout()->addWidget(runInReverseBox);
    runInReverseBox->setToolTip(tr("RunInReverseBoxHint"));
    initiatePane->layout()->addWidget(pa3);
    pa4->setLayout(new FlowLayout());
    pa4->layout()->addWidget(resistanceWheelsBox);
    resistanceWheelsBox->setToolTip(tr("ResistanceWheelsBoxHint"));
    pa4->layout()->addWidget(new JLabel("   "));
    pa4->layout()->addWidget(trainLengthLabel);
    pa4->layout()->addWidget(maxTrainLengthField);
    maxTrainLengthField->setToolTip(tr("MaxTrainLengthHint"));
    initiatePane->layout()->addWidget(pa4);
    hideAutoRunItems();   // initialize with auto run items hidden
    initializeAutoRunValues();
}

/*private*/ void ActivateTrainFrame::initializeAutoRunValues() {
    speedFactorField->setText("" + QString::number(_speedFactor));
    maxSpeedField->setText("" + QString::number(_maxSpeed));
    rampRateBox->setCurrentIndex(_rampRate);
    resistanceWheelsBox->setChecked(_resistanceWheels);
    soundDecoderBox->setChecked(_soundDecoder);
    runInReverseBox->setChecked(_runInReverse);
    maxTrainLengthField->setText("" + QString::number(_maxTrainLength));
}

/*private*/ void ActivateTrainFrame::hideAutoRunItems() {
    pa1->setVisible(false);
    pa2->setVisible(false);
    pa3->setVisible(false);
    pa4->setVisible(false);
}

/*private*/ void ActivateTrainFrame::showAutoRunItems() {
    pa1->setVisible(true);
    pa2->setVisible(true);
    pa3->setVisible(true);
    pa4->setVisible(true);
}

/*private*/ void ActivateTrainFrame::autoTrainInfoToDialog(TrainInfo* info) {
    speedFactorField->setText( QString::number(info->getSpeedFactor()));
    maxSpeedField->setText(QString::number(info->getMaxSpeed()));
    setComboBox(rampRateBox,  info->getRampRate());
    resistanceWheelsBox->setChecked( info->getResistanceWheels());
    runInReverseBox->setChecked( info->getRunInReverse());
    soundDecoderBox->setChecked( info->getSoundDecoder());
    maxTrainLengthField->setText(QString::number(info->getMaxTrainLength()));
    if (autoRunBox->isChecked()) {
        showAutoRunItems();
    } else {
        hideAutoRunItems();
    }
    initiateFrame->pack();
}

/*private*/ void ActivateTrainFrame::autoRunItemsToTrainInfo(TrainInfo* info) {
    info->setSpeedFactor(speedFactorField->text().toFloat());
    info->setMaxSpeed(maxSpeedField->text().toFloat());
    info->setRampRate( rampRateBox->currentText());
    info->setResistanceWheels(resistanceWheelsBox->isChecked());
    info->setRunInReverse(runInReverseBox->isChecked());
    info->setSoundDecoder(soundDecoderBox->isChecked());
    info->setMaxTrainLength(maxTrainLengthField->text().toFloat());
}

/*private*/ bool ActivateTrainFrame::readAutoRunItems() {
    bool success = true;
    float factor = 1.0f;
    bool ok;
        factor = speedFactorField->text().toFloat(&ok);
        if ((factor < 0.1f) || (factor > 1.5f)) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error29").arg(speedFactorField->text()), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            speedFactorField->setText("1.0");
            return false;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "Error30").arg(speedFactorField->text()), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        speedFactorField->setText("1.0");
        return false;
    }
    _speedFactor = factor;
    float max = 0.6f;
    //bool ok;
        max = maxSpeedField->text().toFloat(&ok);
        if ((max < 0.1f) || (max > 1.5f)) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error37").arg(maxSpeedField->text()), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            speedFactorField->setText("0.6");
            return false;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "Error38").arg(maxSpeedField->text()), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        speedFactorField->setText("0.6");
        return false;
    }
    _maxSpeed = max;
    _rampRate = rampRateBox->currentIndex();
    _resistanceWheels = resistanceWheelsBox->isChecked();
    _runInReverse = runInReverseBox->isChecked();
    _soundDecoder = soundDecoderBox->isChecked();
    //bool ok;
        factor = maxTrainLengthField->text().toFloat(&ok);
        if ((factor < 0.0f) || (factor > 10000.0f)) {
            JOptionPane::showMessageDialog(initiateFrame, tr(
                    "Error31").arg(maxTrainLengthField->text()), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
            maxTrainLengthField->setText("18.0");
            return false;
        }
    if(!ok) {
        JOptionPane::showMessageDialog(initiateFrame, tr(
                "Error32").arg(maxTrainLengthField->text()), tr("Error"),
                JOptionPane::ERROR_MESSAGE);
        maxTrainLengthField->setText("18.0");
        return false;
    }
    _maxTrainLength = factor;
    return success;
}

/*private*/ void ActivateTrainFrame::setAutoRunItems(AutoActiveTrain* aaf) {
    aaf->setSpeedFactor(_speedFactor);
    aaf->setMaxSpeed(_maxSpeed);
    aaf->setRampRate(_rampRate);
    aaf->setResistanceWheels(_resistanceWheels);
    aaf->setRunInReverse(_runInReverse);
    aaf->setSoundDecoder(_soundDecoder);
    aaf->setMaxTrainLength(_maxTrainLength);
}

/*private*/ void ActivateTrainFrame::initializeRampCombo() {
    rampRateBox->clear();
    rampRateBox->addItem(tr("RAMP_NONE"));
    rampRateBox->addItem(tr("RAMP_FAST"));
    rampRateBox->addItem(tr("RAMP_MEDIUM"));
    rampRateBox->addItem(tr("RAMP_MED_SLOW"));
    rampRateBox->addItem(tr("RAMP_SLOW"));
    // Note: the order above must correspond to the numbers in AutoActiveTrain::java
}
#endif
/*private*/ /*final*/ /*static*/ Logger* ActivateTrainFrame::log = LoggerFactory::getLogger("ActivateTrainFrame");
