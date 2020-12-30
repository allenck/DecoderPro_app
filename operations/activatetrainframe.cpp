#include "activatetrainframe.h"
#include "dispatcherframe.h"
#include "instancemanager.h"
#include "transitmanager.h"
#include "jmrijframe.h"
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include "jtextfield.h"
#include <QPushButton>
#include "jmribeancombobox.h"
#include "jtextfield.h"
#include "activetrain.h"
#include "traininfofile.h"

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
 transitSelectBox = new QComboBox();
 transitBoxList = new QList<Transit*>();
 trainBoxLabel = new QLabel("     " + tr("Train") + ":");
 trainSelectBox = new QComboBox();
 trainBoxList = new QList<RosterEntry*>();
 trainFieldLabel = new QLabel(tr("Train") + ":");
 trainNameField = new JTextField(10);
 dccAddressFieldLabel = new QLabel("     " + tr("DCC Address") + ":");
 dccAddressField = new JTextField(6);
 inTransitBox = new QCheckBox(tr("TrainInTransit"));
 startingBlockBox = new QComboBox();
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
 delayedStartBox = new QComboBox(/*delayedStartString*/);
 delayedStartBox->addItems(delayedStartString);
 delayedReStartLabel = new QLabel(tr("Add Delay"));
 delayReStartSensorLabel = new QLabel(tr("Restart on Sensor"));
 delayedReStartBox = new QComboBox(/*delayedStartString*/);
 delayedReStartBox->addItems(delayedStartString);
 delaySensor = new JmriBeanComboBox(InstanceManager::sensorManagerInstance());
 delayReStartSensor = new JmriBeanComboBox(InstanceManager::sensorManagerInstance());

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
#if 0
    _TrainsFromRoster = _dispatcher.getTrainsFromRoster();
    _TrainsFromTrains = _dispatcher.getTrainsFromTrains();
    _TrainsFromUser = _dispatcher.getTrainsFromUser();
    _ActiveTrainsList = _dispatcher.getActiveTrainsList();
    // create window if needed
    if (initiateFrame == NULL) {
        initiateFrame = new JmriJFrame(tr("AddTrainTitle"), false, true);
        initiateFrame.addHelpMenu("package.jmri.jmrit.dispatcher.NewTrain", true);
        initiatePane = initiateFrame.getContentPane();
        initiatePane.setLayout(new BoxLayout(initiateFrame.getContentPane(), BoxLayout.Y_AXIS));
        // add buttons to load and save train information
        JPanel p0 = new JPanel();
        p0.setLayout(new FlowLayout());
        p0.add(loadButton = new JButton(tr("LoadButton")));
        loadButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                loadTrainInfo(e);
            }
        });
        loadButton.setToolTipText(tr("LoadButtonHint"));
        p0.add(saveButton = new JButton(tr("SaveButton")));
        saveButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                saveTrainInfo(e);
            }
        });
        saveButton.setToolTipText(tr("SaveButtonHint"));
        p0.add(deleteButton = new JButton(tr("ButtonDelete")));
        deleteButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                deleteTrainInfo(e);
            }
        });
        deleteButton.setToolTipText(tr("DeleteButtonHint"));
        initiatePane.add(p0);
        initiatePane.add(new JSeparator());
        // add items relating to both manually run and automatic trains.
        JPanel p1 = new JPanel();
        p1.setLayout(new FlowLayout());
        p1.add(new JLabel(tr("TransitBoxLabel") + " :"));
        p1.add(transitSelectBox);
        transitSelectBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleTransitSelectionChanged(e);
            }
        });
        transitSelectBox.setToolTipText(tr("TransitBoxHint"));
        p1.add(trainBoxLabel);
        p1.add(trainSelectBox);
        trainSelectBox.setToolTipText(tr("TrainBoxHint"));
        initiatePane.add(p1);
        JPanel p1a = new JPanel();
        p1a.setLayout(new FlowLayout());
        p1a.add(trainFieldLabel);
        p1a.add(trainNameField);
        trainNameField.setToolTipText(tr("TrainFieldHint"));
        p1a.add(dccAddressFieldLabel);
        p1a.add(dccAddressField);
        dccAddressField.setToolTipText(tr("DccAddressFieldHint"));
        initiatePane.add(p1a);
        JPanel p2 = new JPanel();
        p2.setLayout(new FlowLayout());
        p2.add(inTransitBox);
        inTransitBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleInTransitClick(e);
            }
        });
        inTransitBox.setToolTipText(tr("InTransitBoxHint"));
        initiatePane.add(p2);
        JPanel p3 = new JPanel();
        p3.setLayout(new FlowLayout());
        p3.add(new JLabel(tr("StartingBlockBoxLabel") + " :"));
        p3.add(startingBlockBox);
        startingBlockBox.setToolTipText(tr("StartingBlockBoxHint"));
        startingBlockBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleStartingBlockSelectionChanged(e);
            }
        });
        initiatePane.add(p3);
        JPanel p4 = new JPanel();
        p4.setLayout(new FlowLayout());
        p4.add(new JLabel(tr("DestinationBlockBoxLabel") + ":"));
        p4.add(destinationBlockBox);
        destinationBlockBox.setToolTipText(tr("DestinationBlockBoxHint"));
        initiatePane.add(p4);
        JPanel p4a = new JPanel();
        p4a.setLayout(new FlowLayout());
        p4a.add(allocateAllTheWayBox);
        allocateAllTheWayBox.setToolTipText(tr("AllocateAllTheWayBoxHint"));
        initiatePane.add(p4a);
        JPanel p6 = new JPanel();
        p6.setLayout(new FlowLayout());
        p6.add(resetWhenDoneBox);
        resetWhenDoneBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleResetWhenDoneClick(e);
            }
        });
        resetWhenDoneBox.setToolTipText(tr("ResetWhenDoneBoxHint"));
        initiatePane.add(p6);
        JPanel p6a = new JPanel();
        p6a.setLayout(new FlowLayout());
        ((FlowLayout) p6a.getLayout()).setVgap(1);
        p6a.add(delayedReStartLabel);
        p6a.add(delayedReStartBox);
        delayedReStartBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleResetWhenDoneClick(e);
            }
        });
        delayedReStartBox.setToolTipText(tr("DelayedReStartHint"));
        initiatePane.add(p6a);

        JPanel p6b = new JPanel();
        p6b.setLayout(new FlowLayout());
        ((FlowLayout) p6b.getLayout()).setVgap(1);
        p6b.add(delayMinLabel);
        p6b.add(delayMinField);
        delayMinField.setText("0");
        delayMinField.setToolTipText(tr("RestartTimedHint"));
        p6b.add(delayReStartSensorLabel);
        p6b.add(delayReStartSensor);
        delayReStartSensor.setFirstItemBlank(true);
        handleResetWhenDoneClick(NULL);
        initiatePane.add(p6b);

        JPanel p10 = new JPanel();
        p10.setLayout(new FlowLayout());
        p10.add(reverseAtEndBox);
        reverseAtEndBox.setToolTipText(tr("ReverseAtEndBoxHint"));
        initiatePane.add(p10);
        reverseAtEndBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleReverseAtEndBoxClick(e);
            }
        });
        JPanel p10a = new JPanel();
        p10a.setLayout(new FlowLayout());
        p10a.add(terminateWhenDoneBox);
        initiatePane.add(p10a);

        JPanel p8 = new JPanel();
        p8.setLayout(new FlowLayout());
        p8.add(new JLabel(tr("PriorityLabel") + " :"));
        p8.add(priorityField);
        priorityField.setToolTipText(tr("PriorityHint"));
        priorityField.setText("5");
        p8.add(new JLabel("     "));
        p8.add(new JLabel(tr("TrainTypeBoxLabel")));
        initializeTrainTypeBox();
        p8.add(trainTypeBox);
        trainTypeBox.setSelectedIndex(1);
        trainTypeBox.setToolTipText(tr("TrainTypeBoxHint"));
        initiatePane.add(p8);
        JPanel p9 = new JPanel();
        p9.setLayout(new FlowLayout());
        p9.add(new JLabel(tr("DelayedStart")));
        p9.add(delayedStartBox);
        delayedStartBox.setToolTipText(tr("DelayedStartHint"));
        delayedStartBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleDelayStartClick(e);
            }
        });
        p9.add(departureTimeLabel);
        p9.add(departureHrField);
        departureHrField.setText("08");
        departureHrField.setToolTipText(tr("DepartureTimeHrHint"));
        p9.add(departureSepLabel);
        p9.add(departureMinField);
        departureMinField.setText("00");
        departureMinField.setToolTipText(tr("DepartureTimeMinHint"));
        p9.add(delaySensor);
        delaySensor.setFirstItemBlank(true);
        handleDelayStartClick(NULL);
        initiatePane.add(p9);

        JPanel p11 = new JPanel();
        p11.setLayout(new FlowLayout());
        p11.add(loadAtStartupBox);
        loadAtStartupBox.setToolTipText(tr("LoadAtStartupBoxHint"));
        loadAtStartupBox.setSelected(false);
        initiatePane.add(p11);

        initiatePane.add(new JSeparator());
        JPanel p5 = new JPanel();
        p5.setLayout(new FlowLayout());
        p5.add(autoRunBox);
        autoRunBox.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                handleAutoRunClick(e);
            }
        });
        autoRunBox.setToolTipText(tr("AutoRunBoxHint"));
        autoRunBox.setSelected(false);
        initiatePane.add(p5);

        initializeAutoRunItems();
        initiatePane.add(new JSeparator());
        JPanel p7 = new JPanel();
        p7.setLayout(new FlowLayout());
        QPushButton* cancelButton = NULL;
        p7.add(cancelButton = new JButton(tr("ButtonCancel")));
        cancelButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                cancelInitiateTrain(e);
            }
        });
        cancelButton.setToolTipText(tr("CancelButtonHint"));
        p7.add(addNewTrainButton = new JButton(tr("AddNewTrainButton")));
        addNewTrainButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                addNewTrain(e);
            }
        });
        addNewTrainButton.setToolTipText(tr("AddNewTrainButtonHint"));
        initiatePane.add(p7);
    }
    if (_TrainsFromRoster || _TrainsFromTrains) {
        trainBoxLabel.setVisible(true);
        trainSelectBox.setVisible(true);
        trainFieldLabel.setVisible(false);
        trainNameField.setVisible(false);
        dccAddressFieldLabel.setVisible(false);
        dccAddressField.setVisible(false);
    } else if (_TrainsFromUser) {
        trainNameField.setText("");
        trainBoxLabel.setVisible(false);
        trainSelectBox.setVisible(false);
        trainFieldLabel.setVisible(true);
        trainNameField.setVisible(true);
        dccAddressFieldLabel.setVisible(true);
        dccAddressField.setVisible(true);
    }
    setAutoRunDefaults();
    autoRunBox.setSelected(false);
    loadAtStartupBox.setSelected(false);
    allocateAllTheWayBox.setSelected(false);
    initializeFreeTransitsCombo(new QList<Transit>());
    initializeFreeTrainsCombo();
    initiateFrame.pack();
    initiateFrame.setVisible(true);
#endif
}
#if 0
/*private*/ void initializeTrainTypeBox() {
    trainTypeBox.removeAllItems();
    trainTypeBox.addItem("<" + tr("None").toLowerCase() + ">"); // <none>
    trainTypeBox.addItem(tr("LOCAL_PASSENGER"));
    trainTypeBox.addItem(tr("LOCAL_FREIGHT"));
    trainTypeBox.addItem(tr("THROUGH_PASSENGER"));
    trainTypeBox.addItem(tr("THROUGH_FREIGHT"));
    trainTypeBox.addItem(tr("EXPRESS_PASSENGER"));
    trainTypeBox.addItem(tr("EXPRESS_FREIGHT"));
    trainTypeBox.addItem(tr("MOW"));
    // NOTE: The above must correspond in order and name to definitions in ActiveTrain::java.
}

/*private*/ void handleTransitSelectionChanged(ActionEvent e) {
    int index = transitSelectBox.getSelectedIndex();
    if (index < 0) {
        return;
    }
    Transit t = transitBoxList.get(index);
    if ((t != NULL) && (t != selectedTransit)) {
        selectedTransit = t;
        initializeStartingBlockCombo();
        initializeDestinationBlockCombo();
        initiateFrame.pack();
    }
}

/*private*/ void handleInTransitClick(ActionEvent e) {
    if (!inTransitBox.isSelected() && selectedTransit.getEntryBlocksList().isEmpty()) {
        javax.swing.JOptionPane.showMessageDialog(initiateFrame, Bundle
                .getMessage("NoEntryBlocks"), tr("InformationTitle"),
                javax.swing.JOptionPane.INFORMATION_MESSAGE);
        inTransitBox.setSelected(true);
    }
    initializeStartingBlockCombo();
    initializeDestinationBlockCombo();
    initiateFrame.pack();
}

/*private*/ bool checkResetWhenDone() {
    if ((!reverseAtEndBox.isSelected()) && resetWhenDoneBox.isSelected()
            && (!selectedTransit.canBeResetWhenDone())) {
        resetWhenDoneBox.setSelected(false);
        javax.swing.JOptionPane.showMessageDialog(initiateFrame, rb
                .getString("NoResetMessage"), tr("InformationTitle"),
                javax.swing.JOptionPane.INFORMATION_MESSAGE);
        return false;
    }
    return true;
}

/*private*/ void handleDelayStartClick(ActionEvent e) {
    departureHrField.setVisible(false);
    departureMinField.setVisible(false);
    departureTimeLabel.setVisible(false);
    departureSepLabel.setVisible(false);
    delaySensor.setVisible(false);
    if (delayedStartBox.getSelectedItem().equals(tr("DelayedStartTimed"))) {
        departureHrField.setVisible(true);
        departureMinField.setVisible(true);
        departureTimeLabel.setVisible(true);
        departureSepLabel.setVisible(true);
    } else if (delayedStartBox.getSelectedItem().equals(tr("DelayedStartSensor"))) {
        delaySensor.setVisible(true);
    }
}

/*private*/ void handleResetWhenDoneClick(ActionEvent e) {
    delayMinField.setVisible(false);
    delayMinLabel.setVisible(false);
    delayedReStartLabel.setVisible(false);
    delayedReStartBox.setVisible(false);
    delayReStartSensorLabel.setVisible(false);
    delayReStartSensor.setVisible(false);
    if (resetWhenDoneBox.isSelected()) {
        delayedReStartLabel.setVisible(true);
        delayedReStartBox.setVisible(true);
        if (delayedReStartBox.getSelectedItem().equals(tr("DelayedStartTimed"))) {
            delayMinField.setVisible(true);
            delayMinLabel.setVisible(true);
        } else if (delayedReStartBox.getSelectedItem().equals(tr("DelayedStartSensor"))) {
            delayReStartSensor.setVisible(true);
            delayReStartSensorLabel.setVisible(true);
        }
    }
    handleReverseAtEndBoxClick(e);
    initiateFrame.pack();
}

/*private*/ void handleReverseAtEndBoxClick(ActionEvent e) {
    if (reverseAtEndBox.isSelected() || resetWhenDoneBox.isSelected()) {
        terminateWhenDoneBox.setSelected(false);
        terminateWhenDoneBox.setEnabled(false);
    } else {
        terminateWhenDoneBox.setEnabled(true);
    }
}

/*private*/ void handleAutoRunClick(ActionEvent e) {
    if (autoRunBox.isSelected()) {
        showAutoRunItems();
    } else {
        hideAutoRunItems();
    }
    initiateFrame.pack();
}

/*private*/ void handleStartingBlockSelectionChanged(ActionEvent e) {
    initializeDestinationBlockCombo();
    initiateFrame.pack();
}

/*private*/ void cancelInitiateTrain(ActionEvent e) {
    initiateFrame.setVisible(false);
    initiateFrame.dispose();  // prevent this window from being listed in the Window menu.
    initiateFrame = NULL;
    _dispatcher.newTrainDone(NULL);
}

/**
 * Handles press of "Add New Train" button by edit-checking populated values
 *  then (if no errors) creating an ActiveTrain and (optionally) an AutoActiveTrain
 */
/*private*/ void addNewTrain(ActionEvent e) {
    // get information
    if (selectedTransit == NULL) {
        // no transits available
        JOptionPane.showMessageDialog(initiateFrame, tr("Error15"),
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        cancelInitiateTrain(NULL);
        return;
    }
    String transitName = selectedTransit.getSystemName();
    String trainName = "";
    int index = startingBlockBox.getSelectedIndex();
    if (index < 0) {
        return;
    }
    String startBlockName = startingBlockBoxList.get(index).getSystemName();
    int startBlockSeq = startingBlockSeqList.get(index).intValue();
    index = destinationBlockBox.getSelectedIndex();
    if (index < 0) {
        return;
    }
    String endBlockName = destinationBlockBoxList.get(index).getSystemName();
    int endBlockSeq = destinationBlockSeqList.get(index).intValue();
    bool autoRun = autoRunBox.isSelected();
    if (!checkResetWhenDone()) {
        return;
    }
    bool resetWhenDone = resetWhenDoneBox.isSelected();
    bool reverseAtEnd = reverseAtEndBox.isSelected();
    bool allocateAllTheWay = allocateAllTheWayBox.isSelected();
    int delayedStart = delayModeFromBox(delayedStartBox);
    int delayedReStart = delayModeFromBox(delayedReStartBox);
    int departureTimeHours = 8;
    try {
        departureTimeHours = Integer.parseInt(departureHrField.getText());
        if ((departureTimeHours < 0) || (departureTimeHours > 23)) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "BadEntry3", departureHrField.getText()),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            log.warn("Range error in Departure Time Hours field");
            return;
        }
    } catch (NumberFormatException ehr) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "BadEntry2", departureHrField.getText()),
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        log.warn("Conversion exception in departure time hours field");
        return;
    }
    int departureTimeMinutes = 8;
    try {
        departureTimeMinutes = Integer.parseInt(departureMinField.getText());
        if ((departureTimeMinutes < 0) || (departureTimeMinutes > 59)) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "BadEntry3", departureMinField.getText()),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            log.warn("Range error in Departure Time Minutes field");
            return;
        }
    } catch (NumberFormatException emn) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "BadEntry2", departureMinField.getText()),
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        log.warn("Conversion exception in departure time minutes field");
        return;
    }
    int delayRestartMinutes = 0;
    try {
        delayRestartMinutes = Integer.parseInt(delayMinField.getText());
        if ((delayRestartMinutes < 0)) {
            JOptionPane.showMessageDialog(initiateFrame, delayMinField.getText(),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            log.warn("Range error in Delay Restart Time Minutes field");
            return;
        }
    } catch (NumberFormatException emn) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "BadEntry2", delayMinField.getText()),
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        log.warn("Conversion exception in restart delay minutes field");
        return;
    }
    int tSource = 0;
    String dccAddress = "unknown";
    if (_TrainsFromRoster) {
        index = trainSelectBox.getSelectedIndex();
        if (index < 0) {
            // no trains available
            JOptionPane.showMessageDialog(initiateFrame, tr("Error14"),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            cancelInitiateTrain(NULL);
            return;
        }
        trainName = (String) trainSelectBox.getSelectedItem();
        RosterEntry r = trainBoxList.get(index);
        dccAddress = r.getDccAddress();
        if (!isAddressFree(r.getDccLocoAddress().getNumber())) {
            // DCC address is already in use by an Active Train
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error40", dccAddress), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }

        tSource = ActiveTrain::ROSTER;

        if (trainTypeBox.getSelectedIndex() != 0
                && (r.getAttribute("DisptacherTrainType") == NULL
                || !r.getAttribute("DispatcherTrainType").equals("" + trainTypeBox.getSelectedItem()))) {
            r.putAttribute("DispatcherTrainType", "" + trainTypeBox.getSelectedItem());
            r.updateFile();
            Roster.getDefault().writeRoster();
        }
    } else if (_TrainsFromTrains) {
        tSource = ActiveTrain::OPERATIONS;
        index = trainSelectBox.getSelectedIndex();
        if (index < 0) {
            // no trains available
            JOptionPane.showMessageDialog(initiateFrame, tr("Error14"),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            cancelInitiateTrain(NULL);
            return;
        }
        trainName = (String) trainSelectBox.getSelectedItem();
    } else if (_TrainsFromUser) {
        trainName = trainNameField.getText();
        if ((trainName == NULL) || trainName.equals("")) {
            // no train name entered
            JOptionPane.showMessageDialog(initiateFrame, tr("Error14"),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isTrainFree(trainName)) {
            // train name is already in use by an Active Train
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error24", trainName), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        dccAddress = dccAddressField.getText();
        int address = -1;
        try {
            address = Integer.parseInt(dccAddress);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(initiateFrame, tr("Error23"),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            log.error("Conversion exception in dccAddress field");
            return;
        }
        if ((address < 1) || (address > 9999)) {
            JOptionPane.showMessageDialog(initiateFrame, tr("Error23"),
                    tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
            return;
        }
        if (!isAddressFree(address)) {
            // DCC address is already in use by an Active Train
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error40", address), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        tSource = ActiveTrain::USER;
    }
    int priority = 5;
    try {
        priority = Integer.parseInt(priorityField.getText());
    } catch (NumberFormatException ex) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "BadEntry", priorityField.getText()), tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);
        log.error("Conversion exception in priority field");
        return;
    }
    int trainType = trainTypeBox.getSelectedIndex();
    if (autoRunBox.isSelected()) {
        if (!readAutoRunItems()) {
            return;
        }
    }

    // create a new Active Train
    ActiveTrain at = _dispatcher.createActiveTrain(transitName, trainName, tSource, startBlockName,
            startBlockSeq, endBlockName, endBlockSeq, autoRun, dccAddress, priority,
            resetWhenDone, reverseAtEnd, allocateAllTheWay, true, initiateFrame);
    if (at == NULL) {
        return;  // error message sent by createActiveTrain
    }
    if (tSource == ActiveTrain::ROSTER) {
        at.setRosterEntry(trainBoxList.get(trainSelectBox.getSelectedIndex()));
    }
    at.setDelayedStart(delayedStart);
    at.setDelayedReStart(delayedReStart);
    at.setDepartureTimeHr(departureTimeHours);
    at.setDepartureTimeMin(departureTimeMinutes);
    at.setRestartDelay(delayRestartMinutes);
    at.setDelaySensor((jmri.Sensor) delaySensor.getSelectedBean());
    if ((_dispatcher.isFastClockTimeGE(departureTimeHours, departureTimeMinutes) && delayedStart != ActiveTrain::SENSORDELAY) ||
            delayedStart==ActiveTrain::NODELAY) {
        at.setStarted();
    }
    at.setRestartSensor((jmri.Sensor) delayReStartSensor.getSelectedBean());
    at.setTrainType(trainType);
    at.setTerminateWhenDone(terminateWhenDoneBox.isSelected());
    if (autoRunBox.isSelected()) {
        AutoActiveTrain aat = new AutoActiveTrain(at);
        setAutoRunItems(aat);
        if (!aat.initialize()) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error27", at.getTrainName()), tr("InformationTitle"),
                    JOptionPane.INFORMATION_MESSAGE);
        }
        _dispatcher.getAutoTrainsFrame().addAutoActiveTrain(aat);
    }
    _dispatcher.allocateNewActiveTrain(at);
    initiateFrame.setVisible(false);
    initiateFrame.dispose();  // prevent this window from being listed in the Window menu.
    initiateFrame = NULL;
    _dispatcher.newTrainDone(at);
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
#if 0
ActionListener trainSelectBoxListener = NULL;

/*private*/ void initializeFreeTrainsCombo() {
    trainSelectBox.removeActionListener(trainSelectBoxListener);
    trainSelectBox.removeAllItems();
    trainBoxList.clear();
    if (_TrainsFromRoster) {
        // initialize free trains from roster
        List<RosterEntry> l = Roster.getDefault().matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        if (l.size() > 0) {
            for (int i = 0; i < l.size(); i++) {
                RosterEntry r = l.get(i);
                String rName = r.titleString();
                int rAddr = r.getDccLocoAddress().getNumber();
                if (isTrainFree(rName) && isAddressFree(rAddr)) {
                    trainBoxList.add(r);
                    trainSelectBox.addItem(rName);
                }
            }
        }
        if (trainSelectBoxListener == NULL) {
            trainSelectBoxListener = new ActionListener() {
                @Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    RosterEntry r = trainBoxList.get(trainSelectBox.getSelectedIndex());
                    if (transitsFromSpecificBlock) {
                        //resets the transit box if required
                        transitsFromSpecificBlock = false;
                        initializeFreeTransitsCombo(new QList<Transit>());
                    }
                    if (r.getAttribute("DispatcherTrainType") != NULL && !r.getAttribute("DispatcherTrainType").equals("")) {
                        trainTypeBox.setSelectedItem(r.getAttribute("DispatcherTrainType"));
                    }
                }
            };
        }
        trainSelectBox.addActionListener(trainSelectBoxListener);
    } else if (_TrainsFromTrains) {
        // initialize free trains from operations
        List<Train> trains = TrainManager.instance().getTrainsByNameList();
        if (trains.size() > 0) {
            for (int i = 0; i < trains.size(); i++) {
                Train t = trains.get(i);
                if (t != NULL) {
                    String tName = t.getName();
                    if (isTrainFree(tName)) {
                        trainSelectBox.addItem(tName);
                    }
                }
            }
        }
    }
    if (trainBoxList.size() > 0) {
        trainSelectBox.setSelectedIndex(0);
    }
}

/*private*/ bool isTrainFree(String rName) {
    for (int j = 0; j < _ActiveTrainsList.size(); j++) {
        ActiveTrain at = _ActiveTrainsList.get(j);
        if (rName.equals(at.getTrainName())) {
            return false;
        }
    }
    return true;
}

/*private*/ bool isAddressFree(int addr) {
    for (int j = 0; j < _ActiveTrainsList.size(); j++) {
        ActiveTrain at = _ActiveTrainsList.get(j);
        if (addr == Integer.parseInt(at.getDccAddress())) {
            return false;
        }
    }
    return true;
}

/*private*/ void initializeStartingBlockCombo() {
    startingBlockBox.removeAllItems();
    startingBlockBoxList.clear();
    if (!inTransitBox.isSelected() && selectedTransit.getEntryBlocksList().isEmpty()) {
        inTransitBox.setSelected(true);
    }
    if (inTransitBox.isSelected()) {
        startingBlockBoxList = selectedTransit.getInternalBlocksList();
    } else {
        startingBlockBoxList = selectedTransit.getEntryBlocksList();
    }
    startingBlockSeqList = selectedTransit.getBlockSeqList();
    bool found = false;
    for (int i = 0; i < startingBlockBoxList.size(); i++) {
        Block b = startingBlockBoxList.get(i);
        int seq = startingBlockSeqList.get(i).intValue();
        startingBlockBox.addItem(getBlockName(b) + "-" + seq);
        if (!found && b.getState() == Block.OCCUPIED) {
            startingBlockBox.setSelectedItem(getBlockName(b) + "-" + seq);
            found = true;
        }
    }
}

/*private*/ void initializeDestinationBlockCombo() {
    destinationBlockBox.removeAllItems();
    destinationBlockBoxList.clear();
    int index = startingBlockBox.getSelectedIndex();
    if (index < 0) {
        return;
    }
    Block startBlock = startingBlockBoxList.get(index);
    destinationBlockBoxList = selectedTransit.getDestinationBlocksList(
            startBlock, inTransitBox.isSelected());
    destinationBlockSeqList = selectedTransit.getDestBlocksSeqList();
    for (int i = 0; i < destinationBlockBoxList.size(); i++) {
        Block b = destinationBlockBoxList.get(i);
        String bName = getBlockName(b);
        if (selectedTransit.getBlockCount(b) > 1) {
            int seq = destinationBlockSeqList.get(i).intValue();
            bName = bName + "-" + seq;
        }
        destinationBlockBox.addItem(bName);
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
#if 0
/*private*/ void loadTrainInfo(ActionEvent e) {
    String[] names = _tiFile.getTrainInfoFileNames();
    TrainInfo info = NULL;
    if (names.length > 0) {
        //prompt user to select a single train info filename from directory list
        Object selName = JOptionPane.showInputDialog(initiateFrame,
                tr("LoadTrainChoice"), tr("LoadTrainTitle"),
                JOptionPane.QUESTION_MESSAGE, NULL, names, names[0]);
        if ((selName == NULL) || (((String) selName).equals(""))) {
            return;
        }
        //read xml data from selected filename and move it into the new train dialog box
        _trainInfoName = (String) selName;
        try {
            info = _tiFile.readTrainInfo((String) selName);
            if (info != NULL) {
                // process the information just read
                trainInfoToDialog(info);
            }
        } catch (java.io.IOException ioe) {
            log.error("IO Exception when reading train info file " + ioe);
        } catch (org.jdom2.JDOMException jde) {
            log.error("JDOM Exception when reading train info file " + jde);
        }
    }
    handleDelayStartClick(NULL);
    handleReverseAtEndBoxClick(NULL);
}

/*private*/ void saveTrainInfo(ActionEvent e) {
    TrainInfo info = dialogToTrainInfo();

    // get file name
    String eName = "";
    eName = JOptionPane.showInputDialog(initiateFrame,
            tr("EnterFileName") + " :", _trainInfoName);
    if (eName == NULL) {  //Cancel pressed
        return;
    }
    if (eName.length() < 1) {
        JOptionPane.showMessageDialog(initiateFrame, tr("Error25"),
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
        return;
    }
    String fileName = normalizeXmlFileName(eName);
    _trainInfoName = fileName;
    // check if train info file name is in use
    String[] names = _tiFile.getTrainInfoFileNames();
    if (names.length > 0) {
        bool found = false;
        for (int i = 0; i < names.length; i++) {
            if (fileName.equals(names[i])) {
                found = true;
            }
        }
        if (found) {
            // file by that name is already present
            int selectedValue = JOptionPane.showOptionDialog(initiateFrame,
                    tr("Question3", fileName),
                    tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE, NULL, new Object[]{tr("FileYes"),
                        tr("FileNo")}, tr("FileNo"));
            if (selectedValue == 1) {
                return;   // return without writing if "No" response
            }
        }
    }
    // write the Train Info file
    try {
        _tiFile.writeTrainInfo(info, fileName);
    } //catch (org.jdom2.JDOMException jde) {
    //	log.error("JDOM exception writing Train Info: "+jde);
    //}
    catch (java.io.IOException ioe) {
        log.error("IO exception writing Train Info: " + ioe);
    }
}

/*private*/ void deleteTrainInfo(ActionEvent e) {
    String[] names = _tiFile.getTrainInfoFileNames();
    if (names.length > 0) {
        Object selName = JOptionPane.showInputDialog(initiateFrame,
                tr("DeleteTrainChoice"), tr("DeleteTrainTitle"),
                JOptionPane.QUESTION_MESSAGE, NULL, names, names[0]);
        if ((selName == NULL) || (((String) selName).equals(""))) {
            return;
        }
        _tiFile.deleteTrainInfoFile((String) selName);
    }
}

/*private*/ void trainInfoToDialog(TrainInfo info) {
    if (!setComboBox(transitSelectBox, info.getTransitName())) {
        log.warn("Transit " + info.getTransitName() + " from file not in Transit menu");
        JOptionPane.showMessageDialog(initiateFrame,
                tr("TransitWarn", info.getTransitName()),
                NULL, JOptionPane.WARNING_MESSAGE);
    }
    _TrainsFromRoster = info.getTrainFromRoster();
    _TrainsFromTrains = info.getTrainFromTrains();
    _TrainsFromUser = info.getTrainFromUser();
    if (_TrainsFromRoster || _TrainsFromTrains) {
        initializeFreeTrainsCombo();
        if (!setComboBox(trainSelectBox, info.getTrainName())) {
            log.warn("Train " + info.getTrainName() + " from file not in Train menu");
            JOptionPane.showMessageDialog(initiateFrame,
                    tr("TrainWarn", info.getTrainName()),
                    NULL, JOptionPane.WARNING_MESSAGE);
        }
    } else if (_TrainsFromUser) {
        trainNameField.setText(info.getTrainName());
        dccAddressField.setText(info.getDCCAddress());
    }
    inTransitBox.setSelected(info.getTrainInTransit());
    initializeStartingBlockCombo();
    initializeDestinationBlockCombo();
    setComboBox(startingBlockBox, info.getStartBlockName());
    setComboBox(destinationBlockBox, info.getDestinationBlockName());
    priorityField.setText(Integer.toString(info.getPriority()));
    resetWhenDoneBox.setSelected(info.getResetWhenDone());
    reverseAtEndBox.setSelected(info.getReverseAtEnd());
    setDelayModeBox(info.getDelayedStart(), delayedStartBox);
    //delayedStartBox.setSelected(info.getDelayedStart());
    departureHrField.setText(Integer.toString(info.getDepartureTimeHr()));
    departureMinField.setText(Integer.toString(info.getDepartureTimeMin()));
    delaySensor.setSelectedBeanByName(info.getDelaySensorName());

    setDelayModeBox(info.getDelayedRestart(), delayedReStartBox);
    delayMinField.setText(Integer.toString(info.getRestartDelayMin()));
    delayReStartSensor.setSelectedBeanByName(info.getRestartSensorName());
    terminateWhenDoneBox.setSelected(info.getTerminateWhenDone());
    setComboBox(trainTypeBox, info.getTrainType());
    autoRunBox.setSelected(info.getAutoRun());
    loadAtStartupBox.setSelected(info.getLoadAtStartup());
    allocateAllTheWayBox.setSelected(info.getAllocateAllTheWay());
    autoTrainInfoToDialog(info);
}

/*private*/ TrainInfo dialogToTrainInfo() {
    TrainInfo info = new TrainInfo();
    info.setTransitName((String) transitSelectBox.getSelectedItem());
    if (_TrainsFromRoster || _TrainsFromTrains) {
        info.setTrainName((String) trainSelectBox.getSelectedItem());
        info.setDCCAddress(" ");
    } else if (_TrainsFromUser) {
        info.setTrainName(trainNameField.getText());
        info.setDCCAddress(dccAddressField.getText());
    }
    info.setTrainInTransit(inTransitBox.isSelected());
    info.setStartBlockName((String) startingBlockBox.getSelectedItem());
    info.setDestinationBlockName((String) destinationBlockBox.getSelectedItem());
    info.setTrainFromRoster(_TrainsFromRoster);
    info.setTrainFromTrains(_TrainsFromTrains);
    info.setTrainFromUser(_TrainsFromUser);
    info.setPriority(Integer.parseInt(priorityField.getText()));
    info.setResetWhenDone(resetWhenDoneBox.isSelected());
    info.setReverseAtEnd(reverseAtEndBox.isSelected());
    info.setDelayedStart(delayModeFromBox(delayedStartBox));
    info.setDelaySensorName(delaySensor.getSelectedDisplayName());
    info.setDepartureTimeHr(Integer.parseInt(departureHrField.getText()));
    info.setDepartureTimeMin(Integer.parseInt(departureMinField.getText()));
    info.setTrainType((String) trainTypeBox.getSelectedItem());
    info.setAutoRun(autoRunBox.isSelected());
    info.setLoadAtStartup(loadAtStartupBox.isSelected());
    info.setAllocateAllTheWay(allocateAllTheWayBox.isSelected());
    info.setDelayedRestart(delayModeFromBox(delayedReStartBox));
    info.setRestartSensorName(delayReStartSensor.getSelectedDisplayName());
    info.setRestartDelayMin(Integer.parseInt(delayMinField.getText()));
    info.setTerminateWhenDone(terminateWhenDoneBox.isSelected());
    autoRunItemsToTrainInfo(info);
    return info;
}

// Normalizes a suggested xml file name.  Returns NULL string if a valid name cannot be assembled
/*private*/ String normalizeXmlFileName(String name) {
    if (name.length() < 1) {
        return "";
    }
    String newName = name;
    // strip off .xml or .XML if present
    if ((name.endsWith(".xml")) || (name.endsWith(".XML"))) {
        newName = name.substring(0, name.length() - 4);
        if (newName.length() < 1) {
            return "";
        }
    }
    // replace all non-alphanumeric characters with underscore
    newName = newName.replaceAll("[\\W]", "_");
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
#if 0
int delayModeFromBox(QComboBox*box) {
    String mode = (String) box.getSelectedItem();
    int result = jmri.util.StringUtil.getStateFromName(mode, delayedStartInt, delayedStartString);

    if (result < 0) {
        log.warn("unexpected mode string in turnoutMode: " + mode);
        throw new IllegalArgumentException();
    }
    return result;
}

void setDelayModeBox(int mode, QComboBox*box) {
    String result = jmri.util.StringUtil.getNameFromState(mode, delayedStartInt, delayedStartString);
    box.setSelectedItem(result);
}

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
/*private*/ JPanel pa1 = new JPanel();
/*private*/ QLabel* speedFactorLabel = new JLabel(tr("SpeedFactorLabel"));
/*private*/ JTextField speedFactorField = new JTextField(5);
/*private*/ QLabel* maxSpeedLabel = new JLabel(tr("MaxSpeedLabel"));
/*private*/ JTextField maxSpeedField = new JTextField(5);
/*private*/ JPanel pa2 = new JPanel();
/*private*/ QLabel* rampRateLabel = new JLabel(tr("RampRateBoxLabel"));
/*private*/ QComboBox*rampRateBox = new QComboBox();
/*private*/ JPanel pa3 = new JPanel();
 soundDecoderBox = new QCheckBox(tr("SoundDecoder"));
 runInReverseBox = new QCheckBox(tr("RunInReverse"));
/*private*/ JPanel pa4 = new JPanel();
 resistanceWheelsBox = new QCheckBox(tr("ResistanceWheels"));
/*private*/ QLabel* trainLengthLabel = new JLabel(tr("MaxTrainLengthLabel"));
/*private*/ JTextField maxTrainLengthField = new JTextField(5);
// auto run variables
float _speedFactor = 1.0f;
float _maxSpeed = 0.6f;
int _rampRate = AutoActiveTrain::RAMP_NONE;
bool _resistanceWheels = true;
bool _runInReverse = false;
bool _soundDecoder = false;
float _maxTrainLength = 200.0f;

/*private*/ void setAutoRunDefaults() {
    _speedFactor = 1.0f;
    _maxSpeed = 0.6f;
    _rampRate = AutoActiveTrain::RAMP_NONE;
    _resistanceWheels = true;
    _runInReverse = false;
    _soundDecoder = false;
    _maxTrainLength = 100.0f;
}

/*private*/ void initializeAutoRunItems() {
    initializeRampCombo();
    pa1.setLayout(new FlowLayout());
    pa1.add(speedFactorLabel);
    pa1.add(speedFactorField);
    speedFactorField.setToolTipText(tr("SpeedFactorHint"));
    pa1.add(new JLabel("   "));
    pa1.add(maxSpeedLabel);
    pa1.add(maxSpeedField);
    maxSpeedField.setToolTipText(tr("MaxSpeedHint"));
    initiatePane.add(pa1);
    pa2.setLayout(new FlowLayout());
    pa2.add(rampRateLabel);
    pa2.add(rampRateBox);
    rampRateBox.setToolTipText(tr("RampRateBoxHint"));
    initiatePane.add(pa2);
    pa3.setLayout(new FlowLayout());
    pa3.add(soundDecoderBox);
    soundDecoderBox.setToolTipText(tr("SoundDecoderBoxHint"));
    pa3.add(new JLabel("   "));
    pa3.add(runInReverseBox);
    runInReverseBox.setToolTipText(tr("RunInReverseBoxHint"));
    initiatePane.add(pa3);
    pa4.setLayout(new FlowLayout());
    pa4.add(resistanceWheelsBox);
    resistanceWheelsBox.setToolTipText(tr("ResistanceWheelsBoxHint"));
    pa4.add(new JLabel("   "));
    pa4.add(trainLengthLabel);
    pa4.add(maxTrainLengthField);
    maxTrainLengthField.setToolTipText(tr("MaxTrainLengthHint"));
    initiatePane.add(pa4);
    hideAutoRunItems();   // initialize with auto run items hidden
    initializeAutoRunValues();
}

/*private*/ void initializeAutoRunValues() {
    speedFactorField.setText("" + _speedFactor);
    maxSpeedField.setText("" + _maxSpeed);
    rampRateBox.setSelectedIndex(_rampRate);
    resistanceWheelsBox.setSelected(_resistanceWheels);
    soundDecoderBox.setSelected(_soundDecoder);
    runInReverseBox.setSelected(_runInReverse);
    maxTrainLengthField.setText("" + _maxTrainLength);
}

/*private*/ void hideAutoRunItems() {
    pa1.setVisible(false);
    pa2.setVisible(false);
    pa3.setVisible(false);
    pa4.setVisible(false);
}

/*private*/ void showAutoRunItems() {
    pa1.setVisible(true);
    pa2.setVisible(true);
    pa3.setVisible(true);
    pa4.setVisible(true);
}

/*private*/ void autoTrainInfoToDialog(TrainInfo info) {
    speedFactorField.setText(Float.toString(info.getSpeedFactor()));
    maxSpeedField.setText(Float.toString(info.getMaxSpeed()));
    setComboBox(rampRateBox, info.getRampRate());
    resistanceWheelsBox.setSelected(info.getResistanceWheels());
    runInReverseBox.setSelected(info.getRunInReverse());
    soundDecoderBox.setSelected(info.getSoundDecoder());
    maxTrainLengthField.setText(Float.toString(info.getMaxTrainLength()));
    if (autoRunBox.isSelected()) {
        showAutoRunItems();
    } else {
        hideAutoRunItems();
    }
    initiateFrame.pack();
}

/*private*/ void autoRunItemsToTrainInfo(TrainInfo info) {
    info.setSpeedFactor(Float.parseFloat(speedFactorField.getText()));
    info.setMaxSpeed(Float.parseFloat(maxSpeedField.getText()));
    info.setRampRate((String) rampRateBox.getSelectedItem());
    info.setResistanceWheels(resistanceWheelsBox.isSelected());
    info.setRunInReverse(runInReverseBox.isSelected());
    info.setSoundDecoder(soundDecoderBox.isSelected());
    info.setMaxTrainLength(Float.parseFloat(maxTrainLengthField.getText()));
}

/*private*/ bool readAutoRunItems() {
    bool success = true;
    float factor = 1.0f;
    try {
        factor = Float.parseFloat(speedFactorField.getText());
        if ((factor < 0.1f) || (factor > 1.5f)) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error29", speedFactorField.getText()), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            speedFactorField.setText("1.0");
            return false;
        }
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "Error30", speedFactorField.getText()), tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);
        speedFactorField.setText("1.0");
        return false;
    }
    _speedFactor = factor;
    float max = 0.6f;
    try {
        max = Float.parseFloat(maxSpeedField.getText());
        if ((max < 0.1f) || (max > 1.5f)) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error37", maxSpeedField.getText()), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            speedFactorField.setText("0.6");
            return false;
        }
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "Error38", maxSpeedField.getText()), tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);
        speedFactorField.setText("0.6");
        return false;
    }
    _maxSpeed = max;
    _rampRate = rampRateBox.getSelectedIndex();
    _resistanceWheels = resistanceWheelsBox.isSelected();
    _runInReverse = runInReverseBox.isSelected();
    _soundDecoder = soundDecoderBox.isSelected();
    try {
        factor = Float.parseFloat(maxTrainLengthField.getText());
        if ((factor < 0.0f) || (factor > 10000.0f)) {
            JOptionPane.showMessageDialog(initiateFrame, tr(
                    "Error31", maxTrainLengthField.getText()), tr("ErrorTitle"),
                    JOptionPane.ERROR_MESSAGE);
            maxTrainLengthField.setText("18.0");
            return false;
        }
    } catch (NumberFormatException e) {
        JOptionPane.showMessageDialog(initiateFrame, tr(
                "Error32", maxTrainLengthField.getText()), tr("ErrorTitle"),
                JOptionPane.ERROR_MESSAGE);
        maxTrainLengthField.setText("18.0");
        return false;
    }
    _maxTrainLength = factor;
    return success;
}

/*private*/ void setAutoRunItems(AutoActiveTrain aaf) {
    aaf.setSpeedFactor(_speedFactor);
    aaf.setMaxSpeed(_maxSpeed);
    aaf.setRampRate(_rampRate);
    aaf.setResistanceWheels(_resistanceWheels);
    aaf.setRunInReverse(_runInReverse);
    aaf.setSoundDecoder(_soundDecoder);
    aaf.setMaxTrainLength(_maxTrainLength);
}

/*private*/ void initializeRampCombo() {
    rampRateBox.removeAllItems();
    rampRateBox.addItem(tr("RAMP_NONE"));
    rampRateBox.addItem(tr("RAMP_FAST"));
    rampRateBox.addItem(tr("RAMP_MEDIUM"));
    rampRateBox.addItem(tr("RAMP_MED_SLOW"));
    rampRateBox.addItem(tr("RAMP_SLOW"));
    // Note: the order above must correspond to the numbers in AutoActiveTrain::java
}
#endif
