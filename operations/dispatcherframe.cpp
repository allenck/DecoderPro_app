#include "dispatcherframe.h"
#include "instancemanager.h"
#include "activetrain.h"
#include "proxysensormanager.h"
#include "sensormanager.h"
#include <QPushButton>
#include <qcheckbox.h>
#include <QMenu>
#include <QMenuBar>
#include <QBoxLayout>
#include <flowlayout.h>
#include <QLabel>
//#include "activateTrainframe.h"
#include "jtable.h"
#include <jseparator.h>
#include "jtextfield.h"
#include <QMessageBox>
#include "allocationrequest.h"
#include "allocatedsection.h"
#include "sectionmanager.h"
#include "autoallocate.h"
#include "autoturnouts.h"
#include <QDateTime>
#include "activatetrainframe.h"
#include "signalmast.h"
#include "autotrainsframe.h"
#include "traininfofile.h"
#include "traininfo.h"
#include "layoutblockmanager.h"
#include "transit.h"
#include "autoactivetrain.h"
#include "transitmanager.h"
#include "joptionpane.h"
#include "optionsmenu.h"
#include "scale.h"
#include "scalemanager.h"
#include "optionsfile.h"
#include "taskallocaterelease.h"
#include "threadingutil.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "sleeperthread.h"
#include "autoallocate.h"

/**
 * Dispatcher functionality, working with Sections, Transits and ActiveTrain::
 *
 * <P>
 * Dispatcher serves as the manager for ActiveTrains. All allocation of Sections
 * to ActiveTrains is performed here.
 * <P>
 * Programming Note: public methods may be addressed externally via
 * jmri.jmrit.dispatcher.DispatcherFrame.instance(). ...
 * <P>
 * Dispatcher listens to fast clock minutes to handle all ActiveTrain items tied
 * to fast clock time.
 * <P>
 * Delayed start of manual and automatic trains is enforced by not allocating
 * Sections for trains until the fast clock reaches the departure time.
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
 * @author	Dave Duchamp Copyright (C) 2008-2011
 */
///*public*/ class DispatcherFrame extends jmri.util.JmriJFrame {

/**
 * Get a DispatcherFrame through the instance() method
 */
/*private*/ DispatcherFrame::DispatcherFrame(QWidget* parent)
    : JmriJFrame(false, true, parent)
{
    //super(false, true);
 log = new Logger("DispatcherFrame");
 // Dispatcher options (saved to disk if user requests, and restored if present)
 _LE = NULL;
 _SignalType = SIGNALHEAD;
 _UseConnectivity = false;
 _HasOccupancyDetection = false; // "true" if blocks have occupancy detection
 _TrainsFromRoster = true;
 _TrainsFromTrains = false;
 _TrainsFromUser = false;
 _AutoAllocate = false;
 _AutoTurnouts = false;
 _TrustKnownTurnouts = false;
 _ShortActiveTrainNames = false;
 _ShortNameInBlock = true;
 _RosterEntryInBlock = false;
 _ExtraColorForAllocated = true;
 _NameInAllocatedBlock = false;
 _UseScaleMeters = false;  // "true" if scale meters, "false" for scale feet
 _LayoutScale = ScaleManager::getScale("HO");
 _SupportVSDecoder = false;
 _MinThrottleInterval = 100; //default time (in ms) between consecutive throttle commands
 _FullRampTime = 10000; //default time (in ms) for RAMP_FAST to go from 0% to 100%

 // operational instance variables
 activeTrainsList = new QList<ActiveTrain*>();  // list of ActiveTrain objects
 _atListeners
         = new QList<PropertyChangeListener*>();
 delayedTrains = new QList<ActiveTrain*>();  // list of delayed Active Trains
 restartingTrainsList = new QList<ActiveTrain*>();  // list of Active Trains with restart requests
 transitManager = (TransitManager*)InstanceManager::getDefault("TransitManager");
 allocationRequests = new QList<AllocationRequest*>();  // List of AllocatedRequest objects
 allocatedSections = new QList<AllocatedSection*>();  // List of AllocatedSection objects
 optionsRead = false;
 autoTurnouts = NULL;
 autoAllocate = NULL;
 optionsMenu = NULL;
 atFrame = NULL;
 setProperty("InstanceManagerAutoDefault", "yes");


 _autoTrainsFrame = NULL;
 fastClock = (Timebase*)InstanceManager::getNullableDefault("Timebase");
 fastClockSensor = InstanceManager::sensorManagerInstance()->provideSensor("ISCLOCKRUNNING");
  //minuteChangeListener = NULL;

  // dispatcher window variables
  dispatcherFrame = NULL;
  contentPane = NULL;
  activeTrainsTableModel = NULL;
  addTrainButton = NULL;
  terminateTrainButton = NULL;
  cancelRestartButton = NULL;
  allocateExtraButton = NULL;
  autoReleaseBox = NULL;
  autoAllocateBox = NULL;
  allocationRequestTableModel = NULL;
  allocatedSectionTableModel = NULL;

  nowMinutes = 0;    // last read fast clock minutes
  nowHours = 0;		// last read fast clock hours
  extraFrame = NULL;
  extraPane = NULL;
  atSelectBox = new QComboBox();
  extraBox = new QComboBox();
  extraBoxList = new QList<Section*>();
  atSelectedIndex = -1;


    initializeOptions();
    openDispatcherWindow();

    autoTurnouts = new AutoTurnouts(this);
    ((SectionManager*)InstanceManager::getDefault("SectionManager"))->initializeBlockingSensors();
    getActiveTrainFrame();

    if (fastClock == NULL) {
        log->error("Failed to instantiate a fast clock when constructing Dispatcher");
    } else
    {
//        minuteChangeListener = new PropertyChangeListener() {
//            @Override
//            /*public*/ void propertyChange(PropertyChangeEvent e) {
//                //process change to new minute
//                newFastClockMinute();
//            }
//        };
//        fastClock->addMinuteChangeListener(minuteChangeListener);
    }
}
/*public*/ void DispatcherFrame::minuteChange(PropertyChangeEvent* /*e*/) {
    //process change to new minute
    newFastClockMinute();
}

/*public*/ void DispatcherFrame::loadAtStartup() {
    log->debug("Loading saved trains flagged as LoadAtStartup");
    TrainInfoFile* tif = new TrainInfoFile();
    QStringList names = tif->getTrainInfoFileNames();
     bool pathsInited = false;
#if 1
    if (names.length() > 0) {
        for (int i = 0; i < names.length(); i++) {
            //read xml data from selected filename and move it into the new train dialog box
            TrainInfo* info = NULL;
            //try {
                info = tif->readTrainInfo(names[i]);
//            } catch (java.io.IOException ioe) {
//                log->error("IO Exception when reading train info file {}: {}", names[i], ioe);
//            } catch (org.jdom2.JDOMException jde) {
//                log->error("JDOM Exception when reading train info file {}: {}", names[i], jde);
//            }
            if (info != NULL && info->getLoadAtStartup()) {
                log->debug(tr("restoring train:%1, startblockname:%2, destinationBlockName:%3").arg(info->getTrainName()).arg(info->getStartBlockName()).arg(info->getDestinationBlockName()));
                // create a new Active Train
                int tSource = ActiveTrain::ROSTER;
                if (info->getTrainFromTrains()) {
                    tSource = ActiveTrain::OPERATIONS;
                } else if (info->getTrainFromUser()) {
                    tSource = ActiveTrain::USER;
                }
                //block and seq are stored together, split out for use here
                QString startBlock = info->getStartBlockName().split("-")[0];
                int startBlockSeq = info->getStartBlockName().split("-")[1].toInt();
                QString destinationBlock = info->getDestinationBlockName().split("-")[0];
                int destinationBlockSeq = info->getDestinationBlockName().split("-")[1].toInt();

                if (!pathsInited) { //only init the layoutblockpaths once here
                    log->debug("initializing block paths early"); //TODO: figure out how to prevent the "regular" init
                    ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->initializeLayoutBlockPaths();
                }

                ActiveTrain* at = createActiveTrain(info->getTransitName(), info->getTrainName(), tSource,
                        startBlock, startBlockSeq, destinationBlock, destinationBlockSeq,
                        info->getAutoRun(), info->getDCCAddress(), info->getPriority(),
                        info->getResetWhenDone(), info->getReverseAtEnd(), info->getAllocateAllTheWay(), true, NULL);
                if (at != NULL) {
                    if (tSource == ActiveTrain::ROSTER) {
                        RosterEntry* re = Roster::getDefault()->getEntryForId(info->getTrainName());
                        at->setRosterEntry(re);
                        at->setDccAddress(re->getDccAddress());
                    }
                    at->setDelayedStart(info->getDelayedStart()); //this is a code: NODELAY, TIMEDDELAY, SENSORDELAY
                    at->setDepartureTimeHr(info->getDepartureTimeHr()); // hour of day (fast-clock) to start this train
                    at->setDepartureTimeMin(info->getDepartureTimeMin()); //minute of hour to start this train
                    at->setDelayedReStart(info->getDelayedRestart()); //this is a code: NODELAY, TIMEDDELAY, SENSORDELAY
                    at->setRestartDelay(info->getRestartDelayMin());  //this is number of minutes to delay between runs
                    at->setDelaySensor(info->getDelaySensor());
                    if ((isFastClockTimeGE(at->getDepartureTimeHr(), at->getDepartureTimeMin()) && info->getDelayedStart() != ActiveTrain::SENSORDELAY) ||
                            info->getDelayedStart()==ActiveTrain::NODELAY) {
                        at->setStarted();
                    }
                    at->setRestartSensor(info->getRestartSensor());
                    at->setTrainType(info->getTrainType());
                    at->setTerminateWhenDone(info->getTerminateWhenDone());
                    if (info->getAutoRun()) {
                        AutoActiveTrain* aat = new AutoActiveTrain(at);
                        aat->setSpeedFactor(info->getSpeedFactor());
                        aat->setMaxSpeed(info->getMaxSpeed());
                        aat->setRampRate(AutoActiveTrain::getRampRateFromName(info->getRampRate()));
                        aat->setResistanceWheels(info->getResistanceWheels());
                        aat->setRunInReverse(info->getRunInReverse());
                        aat->setSoundDecoder(info->getSoundDecoder());
                        aat->setMaxTrainLength(info->getMaxTrainLength());
                        if (!aat->initialize()) {
                            log->error(tr("ERROR initializing autorunning for train %1").arg(at->getTrainName()));
//                            JOptionPane.showMessageDialog(dispatcherFrame, Bundle.getMessage(
//                                    "Error27", at->getTrainName()), Bundle.getMessage("InformationTitle"),
//                                    JOptionPane.INFORMATION_MESSAGE);
                            QMessageBox::critical(dispatcherFrame, tr("Error"), tr("Could not initialize automatic running of train \"%1\", changing to manual running.").arg(at->getTrainName()));
                        }
                        getAutoTrainsFrame()->addAutoActiveTrain(aat);
                    }
                    allocateNewActiveTrain(at);
                    newTrainDone(at);

                } else {
                    log->warn(tr("failed to create create Active Train %1").arg(info->getTrainName()));
                }
            }

        }
    }
#endif
}
#if 0
static final ResourceBundle rb = ResourceBundle
        .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");
#endif



/*public*/ ActivateTrainFrame* DispatcherFrame::getActiveTrainFrame() {
    if (atFrame == NULL) {
        atFrame = new ActivateTrainFrame(this);
    }
    return atFrame;
}

/*public*/  bool DispatcherFrame::getNewTrainActive() {
    return newTrainActive;
}

/*public*/ void DispatcherFrame::setNewTrainActive( bool boo) {
    newTrainActive = boo;
}


void DispatcherFrame::initializeOptions() {
    if (optionsRead) {
        return;
    }
#if 1
    optionsRead = true;
    try {
        ((OptionsFile*)InstanceManager::getDefault("OptionsFile"))->readDispatcherOptions(this);
    } catch (JDOMException jde) {
        log->error("JDOM Exception when retreiving dispatcher options " + jde.getMessage());
    } catch (IOException ioe) {
        log->error("I/O Exception when retreiving dispatcher options " + ioe.getMessage());
    }
#endif
}

void DispatcherFrame::openDispatcherWindow() {
    if (dispatcherFrame == NULL) {
        dispatcherFrame = this;
        dispatcherFrame->setTitle(tr("Dispatcher"));
        QMenuBar* menuBar = new QMenuBar();
        optionsMenu = new OptionsMenu(this);
        menuBar->addMenu(optionsMenu);
        setMenuBar(menuBar);
        dispatcherFrame->addHelpMenu("package.jmri.jmrit.dispatcher.Dispatcher", true);
        contentPane = dispatcherFrame->getContentPane();
        //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        QVBoxLayout* contentPaneLayout;
        contentPane->setLayout(contentPaneLayout = new QVBoxLayout());
        // set up active trains table
        QWidget* p11 = new QWidget();
        FlowLayout* p11Layout;
        p11->setLayout(p11Layout=new FlowLayout());
        p11Layout->addWidget(new QLabel(tr("Active Trains")));
        contentPaneLayout->addWidget(p11);
        QWidget* p12 = new QWidget();
        QVBoxLayout* p12Layout;
        p12->setLayout(p12Layout = new QVBoxLayout());
        activeTrainsTableModel = new ActiveTrainsTableModel(this);
        JTable* activeTrainsTable = new JTable(activeTrainsTableModel);
#if 1
        activeTrainsTable->setRowSelectionAllowed(false);
        //activeTrainsTable->setPreferredScrollableViewportSize(QSize(950, 160));
        activeTrainsTable->resize(QSize(950, 160));
        TableColumnModel* activeTrainsColumnModel = activeTrainsTable->getColumnModel();
        TableColumn* transitColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::TRANSIT_COLUMN);
        transitColumn->setResizable(true);
        transitColumn->setMinWidth(140);
        transitColumn->setMaxWidth(220);
        TableColumn* trainColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::TRAIN_COLUMN);
        trainColumn->setResizable(true);
        trainColumn->setMinWidth(90);
        trainColumn->setMaxWidth(160);
        TableColumn* typeColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::TYPE_COLUMN);
        typeColumn->setResizable(true);
        typeColumn->setMinWidth(130);
        typeColumn->setMaxWidth(190);
        TableColumn* statusColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::STATUS_COLUMN);
        statusColumn->setResizable(true);
        statusColumn->setMinWidth(90);
        statusColumn->setMaxWidth(140);
        TableColumn* modeColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::MODE_COLUMN);
        modeColumn->setResizable(true);
        modeColumn->setMinWidth(90);
        modeColumn->setMaxWidth(140);
        TableColumn* allocatedColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::ALLOCATED_COLUMN);
        allocatedColumn->setResizable(true);
        allocatedColumn->setMinWidth(120);
        allocatedColumn->setMaxWidth(200);
        TableColumn* nextSectionColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::NEXTSECTION_COLUMN);
        nextSectionColumn->setResizable(true);
        nextSectionColumn->setMinWidth(120);
        nextSectionColumn->setMaxWidth(200);
        TableColumn* allocateButtonColumn = activeTrainsColumnModel->getColumn(ActiveTrainsTableModel::ALLOCATEBUTTON_COLUMN);
        allocateButtonColumn->setCellEditor(new ButtonEditor(new JButton()));
        allocateButtonColumn->setMinWidth(110);
        allocateButtonColumn->setMaxWidth(190);
        allocateButtonColumn->setResizable(false);
        ButtonRenderer* buttonRenderer = new ButtonRenderer();
        activeTrainsTable->setDefaultRenderer("JButton", buttonRenderer);
#endif
//        QPushButton* sampleButton = new QPushButton(tr("Allocate Next"));
//        activeTrainsTable.setRowHeight(sampleButton.getPreferredSize().height);
//        allocateButtonColumn.setPreferredWidth((sampleButton.getPreferredSize().width) + 2);
        //JScrollPane activeTrainsTableScrollPane = new JScrollPane(activeTrainsTable);
        p12Layout->addWidget(/*activeTrainsTableScrollPane, BorderLayout.CENTER*/activeTrainsTable, 0, Qt::AlignCenter);
        contentPaneLayout->addWidget(p12);
        QWidget* p13 = new QWidget();
        FlowLayout* p13Layout;
        p13->setLayout(p13Layout = new FlowLayout());
        p13Layout->addWidget(addTrainButton = new QPushButton(tr("New Train") + "..."));
//        addTrainButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!newTrainActive) {
//                    atFrame.initiateTrain(e);
//                    newTrainActive = true;
//                } else {
//                    atFrame.showActivateFrame();
//                }
//            }
//        });
        connect(addTrainButton, SIGNAL(clicked(bool)), this, SLOT(on_addTrainButton()));
        addTrainButton->setToolTip(tr("Press to bring up a window for starting up a new train."));
        p13Layout->addWidget(new QLabel("   "));
        p13Layout->addWidget(new QLabel("   "));
        p13Layout->addWidget(allocateExtraButton = new QPushButton(tr("Allocate Extra") + "..."));
//        allocateExtraButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                allocateExtraSection(e);
//            }
//        });
        connect(allocateExtraButton, SIGNAL(clicked(bool)), this, SLOT(allocateExtraSection()));
        allocateExtraButton->setToolTip(tr("Press to bring up a window allowing allocation of an extra Section to an Active Train."));
        p13Layout->addWidget(new QLabel("   "));
        p13Layout->addWidget(cancelRestartButton = new QPushButton(tr("Cancel Auto Restart") + "..."));
//        cancelRestartButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!newTrainActive) {
//                    cancelRestart(e);
//                } else if (restartingTrainsList.size() > 0) {
//                    atFrame.showActivateFrame();
//                    JOptionPane.showMessageDialog(dispatcherFrame, tr("Message2"),
//                            tr("MessageTitle"), JOptionPane.INFORMATION_MESSAGE);
//                } else {
//                    atFrame.showActivateFrame();
//                }
//            }
//        });
        connect(cancelRestartButton, SIGNAL(clicked(bool)), this, SLOT(on_cancelRestartButton()));
        cancelRestartButton->setToolTip(tr("Press to bring up a window to cancel automatic restart of an Active Train."));
        p13Layout->addWidget(new QLabel("   "));
        p13Layout->addWidget(terminateTrainButton = new QPushButton(tr("Terminate Train") + "..."));
//        terminateTrainButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (!newTrainActive) {
//                    terminateTrain(e);
//                } else if (activeTrainsList.size() > 0) {
//                    atFrame.showActivateFrame();
//                    JOptionPane.showMessageDialog(dispatcherFrame, tr("Message1"),
//                            tr("MessageTitle"), JOptionPane.INFORMATION_MESSAGE);
//                } else {
//                    atFrame.showActivateFrame();
//                }
//            }
//        });
        connect(terminateTrainButton, SIGNAL(clicked(bool)), this, SLOT(on_terminateTrainButton()));
        terminateTrainButton->setToolTip(tr("Press to bring up a window for terminating an Active Train."));
        contentPaneLayout->addWidget(p13);
        // set up pending allocations table
        contentPaneLayout->addWidget(new JSeparator());
        QWidget* p21 = new QWidget();
        FlowLayout* p21Layout;
        p21->setLayout(p21Layout = new FlowLayout());
        p21Layout->addWidget(new QLabel(tr("Requested Allocations waiting for Dispatch")));
        contentPaneLayout->addWidget(p21);
        QWidget* p22 = new QWidget();
        QVBoxLayout* p22Layout;
        p22->setLayout(p22Layout = new QVBoxLayout());
        allocationRequestTableModel = new AllocationRequestTableModel(this);
        JTable* allocationRequestTable = new JTable(allocationRequestTableModel);
#if 0
        allocationRequestTable.setRowSelectionAllowed(false);
        allocationRequestTable.setPreferredScrollableViewportSize(QSize(950, 100));
        TableColumnModel allocationRequestColumnModel = allocationRequestTable.getColumnModel();
        TableColumn activeColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.ACTIVE_COLUMN);
        activeColumn.setResizable(true);
        activeColumn.setMinWidth(210);
        activeColumn.setMaxWidth(260);
        TableColumn priorityColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.PRIORITY_COLUMN);
        priorityColumn.setResizable(true);
        priorityColumn.setMinWidth(40);
        priorityColumn.setMaxWidth(60);
        TableColumn trainTypColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.TRAINTYPE_COLUMN);
        trainTypColumn.setResizable(true);
        trainTypColumn.setMinWidth(130);
        trainTypColumn.setMaxWidth(190);
        TableColumn sectionColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.SECTION_COLUMN);
        sectionColumn.setResizable(true);
        sectionColumn.setMinWidth(140);
        sectionColumn.setMaxWidth(210);
        TableColumn secStatusColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.STATUS_COLUMN);
        secStatusColumn.setResizable(true);
        secStatusColumn.setMinWidth(90);
        secStatusColumn.setMaxWidth(150);
        TableColumn occupancyColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.OCCUPANCY_COLUMN);
        occupancyColumn.setResizable(true);
        occupancyColumn.setMinWidth(80);
        occupancyColumn.setMaxWidth(130);
        TableColumn secLengthColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.SECTIONLENGTH_COLUMN);
        secLengthColumn.setResizable(true);
        secLengthColumn.setMinWidth(40);
        secLengthColumn.setMaxWidth(60);
        TableColumn allocateColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.ALLOCATEBUTTON_COLUMN);
        allocateColumn.setCellEditor(new ButtonEditor(new JButton()));
        allocateColumn.setMinWidth(90);
        allocateColumn.setMaxWidth(170);
        allocateColumn.setResizable(false);
        allocationRequestTable.setDefaultRenderer(JButton.class, buttonRenderer);
        sampleButton = new JButton(tr("AllocateButton"));
        allocationRequestTable.setRowHeight(sampleButton.getPreferredSize().height);
        allocateColumn.setPreferredWidth((sampleButton.getPreferredSize().width) + 2);
        TableColumn cancelButtonColumn = allocationRequestColumnModel.getColumn(AllocationRequestTableModel.CANCELBUTTON_COLUMN);
        cancelButtonColumn.setCellEditor(new ButtonEditor(new JButton()));
        cancelButtonColumn.setMinWidth(75);
        cancelButtonColumn.setMaxWidth(170);
        cancelButtonColumn.setResizable(false);
        cancelButtonColumn.setPreferredWidth((sampleButton.getPreferredSize().width) + 2);
        JScrollPane allocationRequestTableScrollPane = new JScrollPane(allocationRequestTable);
#endif
        p22Layout->addWidget(/*allocationRequestTableScrollPane, BorderLayout.CENTER*/allocationRequestTable, 0, Qt::AlignCenter);
        contentPaneLayout->addWidget(p22);
        // set up allocated sections table
        contentPaneLayout->addWidget(new JSeparator());
        QWidget* p30 = new QWidget();
        FlowLayout* p30Layout;
        p30->setLayout(p30Layout = new FlowLayout());
        p30Layout->addWidget(new QLabel(tr("Allocated Sections") + "    "));
        autoReleaseBox = new QCheckBox(tr("Auto Release"));
        p30Layout->addWidget(autoReleaseBox);
        autoReleaseBox->setToolTip(tr("Check to automatically release allocated sections that show exited."));
//        autoReleaseBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                handleAutoReleaseChanged(e);
//            }
//        });
        connect(autoReleaseBox, SIGNAL(clicked(bool)), this, SLOT(handleAutoReleaseChanged()));
        autoReleaseBox->setChecked(_AutoAllocate);  // initiallize autoRelease to match autoAllocate
        autoAllocateBox = new QCheckBox(tr("Auto Allocate"));
        p30Layout->addWidget(autoAllocateBox);
        autoAllocateBox->setToolTip(tr("Check if computer is to automatically allocated requested sections. Uncheck for manual allocation."));
//        autoAllocateBox.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                handleAutoAllocateChanged(e);
//            }
//        });
        connect(autoAllocateBox, SIGNAL(clicked(bool)), this, SLOT(handleAutoAllocateChanged()));
        contentPaneLayout->addWidget(p30);
        autoAllocateBox->setChecked(_AutoAllocate);
        QWidget* p31 = new QWidget();
        QVBoxLayout* p31Layout;
        p31->setLayout(p31Layout = new QVBoxLayout());
        allocatedSectionTableModel = new AllocatedSectionTableModel(this);
        JTable* allocatedSectionTable = new JTable(allocatedSectionTableModel);
#if 0
        allocatedSectionTable.setRowSelectionAllowed(false);
        allocatedSectionTable.setPreferredScrollableViewportSize(QSize(730, 200));
        TableColumnModel allocatedSectionColumnModel = allocatedSectionTable.getColumnModel();
        TableColumn activeAColumn = allocatedSectionColumnModel.getColumn(AllocatedSectionTableModel.ACTIVE_COLUMN);
        activeAColumn.setResizable(true);
        activeAColumn.setMinWidth(250);
        activeAColumn.setMaxWidth(350);
        TableColumn sectionAColumn = allocatedSectionColumnModel.getColumn(AllocatedSectionTableModel.SECTION_COLUMN);
        sectionAColumn.setResizable(true);
        sectionAColumn.setMinWidth(200);
        sectionAColumn.setMaxWidth(350);
        TableColumn occupancyAColumn = allocatedSectionColumnModel.getColumn(AllocatedSectionTableModel.OCCUPANCY_COLUMN);
        occupancyAColumn.setResizable(true);
        occupancyAColumn.setMinWidth(80);
        occupancyAColumn.setMaxWidth(140);
        TableColumn useStatusColumn = allocatedSectionColumnModel.getColumn(AllocatedSectionTableModel.USESTATUS_COLUMN);
        useStatusColumn.setResizable(true);
        useStatusColumn.setMinWidth(90);
        useStatusColumn.setMaxWidth(150);
        TableColumn releaseColumn = allocatedSectionColumnModel.getColumn(AllocatedSectionTableModel.RELEASEBUTTON_COLUMN);
        releaseColumn.setCellEditor(new ButtonEditor(new JButton()));
        releaseColumn.setMinWidth(90);
        releaseColumn.setMaxWidth(170);
        releaseColumn.setResizable(false);
        allocatedSectionTable.setDefaultRenderer(JButton.class, buttonRenderer);
        JButton sampleAButton = new JButton(tr("ReleaseButton"));
        allocatedSectionTable.setRowHeight(sampleAButton.getPreferredSize().height);
        releaseColumn.setPreferredWidth((sampleAButton.getPreferredSize().width) + 2);
        JScrollPane allocatedSectionTableScrollPane = new JScrollPane(allocatedSectionTable);
#endif
        p31Layout->addWidget(/*allocatedSectionTableScrollPane, BorderLayout.CENTER*/allocatedSectionTable);
        contentPaneLayout->addWidget(p31, 0, Qt::AlignCenter);
    }
    dispatcherFrame->pack();
    dispatcherFrame->setVisible(true);
}

void DispatcherFrame::on_addTrainButton()
{
#if 0
 if (!newTrainActive) {
     atFrame.initiateTrain(e);
     newTrainActive = true;
 } else {
     atFrame.showActivateFrame();
 }
#endif
}

void DispatcherFrame::on_cancelRestartButton()
{
#if 0
 if (!newTrainActive) {
     cancelRestart(e);
 } else if (restartingTrainsList.size() > 0) {
     atFrame.showActivateFrame();
     JOptionPane.showMessageDialog(dispatcherFrame, tr("Message2"),
             tr("MessageTitle"), JOptionPane.INFORMATION_MESSAGE);
 } else {
     atFrame.showActivateFrame();
 }
#endif
}

void DispatcherFrame::on_terminateTrainButton()
{
#if 1
 if (!newTrainActive) {
     terminateTrain(/*e*/);
 } else if (activeTrainsList->size() > 0) {
     atFrame->showActivateFrame();
     JOptionPane::showMessageDialog(dispatcherFrame, tr("Complete or cancel Activate New Train pane before Terminating an ActiveTrain."),
             tr("MessageTitle"), JOptionPane::INFORMATION_MESSAGE);
 } else {
     atFrame->showActivateFrame();
 }
 #endif
}






void DispatcherFrame::releaseAllocatedSectionFromTable(int index) {
    AllocatedSection* as = allocatedSections->at(index);
    releaseAllocatedSection(as, false);
}

// allocate extra window variables

/*public*/ void DispatcherFrame::allocateExtraSection(JActionEvent* /*e*/, ActiveTrain* at) {
    allocateExtraSection(/*e*/);
    if (_ShortActiveTrainNames) {
        atSelectBox->setCurrentText(at->getTrainName());
    } else {
        atSelectBox->setCurrentText(at->getActiveTrainName());
    }
}

// allocate an extra Section to an Active Train
/*private*/ void DispatcherFrame::allocateExtraSection(/*ActionEvent* e*/) {
    if (extraFrame == NULL) {
        extraFrame = new JmriJFrameX(tr("Allocate Extra"));
        extraFrame->addHelpMenu("package.jmri.jmrit.dispatcher.AllocateExtra", true);
        extraPane = extraFrame->getContentPane();
        QVBoxLayout* extraPaneLayout;
        extraPane->setLayout(extraPaneLayout = new QVBoxLayout()); //(extraFrame.getContentPane(), BoxLayout.Y_AXIS));
        QWidget* p1 = new QWidget();
        FlowLayout* p1Layout;
        p1->setLayout(p1Layout = new FlowLayout());
        p1Layout->addWidget(new QLabel(tr("Active Train") + ":"));
        p1Layout->addWidget(atSelectBox);
//        atSelectBox.addActionListener(new ActionListener() {
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                handleATSelectionChanged(e);
//            }
//        });
        connect(atSelectBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleATSelectionChanged()));
        atSelectBox->setToolTip(tr("Select an Active Train to allocate the extra Section to."));
        extraPaneLayout->addWidget(p1);
        QWidget* p2 = new QWidget();
        FlowLayout* p2Layout;
        p2->setLayout(p2Layout = new FlowLayout());
        p2Layout->addWidget(new QLabel(tr("Section to Allocate") + ":"));
        p2Layout->addWidget(extraBox);
        extraBox->setToolTip(tr("Select a connected Section to allocate."));
        extraPaneLayout->addWidget(p2);
        QWidget* p7 = new QWidget();
        FlowLayout* p7Layout;
        p7->setLayout(p7Layout = new FlowLayout());
        QPushButton* cancelButton = NULL;
        p7Layout->addWidget(cancelButton = new QPushButton(tr("Cancel")));
//        cancelButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelExtraRequested(e);
//            }
//        });
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelExtraRequested()));
        cancelButton->setToolTip(tr("Click to cancel without allocating an extra Section."));
        p7Layout->addWidget(new QLabel("    "));
        QPushButton* aExtraButton = NULL;
        p7Layout->addWidget(aExtraButton = new QPushButton(tr("Allocate")));
//        aExtraButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                addExtraRequested(e);
//            }
//        });
        connect(aExtraButton, SIGNAL(clicked(bool)), this, SLOT(addExtraRequested()));
        aExtraButton->setToolTip(tr("Click to allocate selected Section to Active Train."));
        extraPaneLayout->addWidget(p7);
    }
    initializeATComboBox();
    initializeExtraComboBox();
    extraFrame->pack();
    extraFrame->setVisible(true);
}

/*private*/ void DispatcherFrame::handleAutoAllocateChanged(JActionEvent* /*e*/) {
    setAutoAllocate(autoAllocateBox->isChecked());
    stopStartAutoAllocateRelease();
    if (autoAllocateBox != nullptr) {
        autoAllocateBox->setChecked(_AutoAllocate);
    }

    if (optionsMenu != NULL) {
        optionsMenu->initializeMenu();
    }
    if (_AutoAllocate) {
     queueScanOfAllocationRequests();
    }
}

/*
 * Queue a scan
 */
/*protected*/ void DispatcherFrame::queueScanOfAllocationRequests() {
    if (_AutoAllocate) {
        autoAllocate->scanAllocationRequests(new TaskAllocateRelease(TaskAllocateRelease::TaskAction::SCAN_REQUESTS));
    }
}

/*
 * Queue a release all reserved sections for a train.
 */
/*protected*/ void DispatcherFrame::queueReleaseOfReservedSections(QString trainName) {
    if (_AutoRelease || _AutoAllocate) {
        autoAllocate->scanAllocationRequests(new TaskAllocateRelease(TaskAllocateRelease::TaskAction::RELEASE_RESERVED, trainName));
    }
}

/*
 * Wait for the queue to empty
 */
/*protected*/ void DispatcherFrame::queueWaitForEmpty() {
    if (_AutoAllocate) {
        while (!autoAllocate->allRequestsDone()) {
            try {
                SleeperThread::msleep(10);
            } catch (InterruptedException iex) {
                // we closing do done
                return;
            }
        }
    }
    return;
}

/*
 * Queue a general release of completed sections
 */
/*protected*/ void DispatcherFrame::queueReleaseOfCompletedAllocations() {
    if (_AutoRelease) {
        autoAllocate->scanAllocationRequests(new TaskAllocateRelease(TaskAllocateRelease::TaskAction::AUTO_RELEASE));
    }
}

/*private*/ void DispatcherFrame::handleAutoReleaseChanged(JActionEvent* /*e*/) {
    if (autoReleaseBox->isChecked()) {
        checkAutoRelease();
    }
}

/*private*/ void DispatcherFrame::handleATSelectionChanged(JActionEvent* /*e*/) {
    atSelectedIndex = atSelectBox->currentIndex();
    initializeExtraComboBox();
    extraFrame->adjustSize();
    extraFrame->setVisible(true);
}

/*private*/ void DispatcherFrame::initializeATComboBox() {
    atSelectedIndex = -1;
    atSelectBox->clear();
    for (int i = 0; i < activeTrainsList->size(); i++) {
        ActiveTrain* at = activeTrainsList->value(i);
        if (_ShortActiveTrainNames) {
            atSelectBox->addItem(at->getTrainName());
        } else {
            atSelectBox->addItem(at->getActiveTrainName());
        }
    }
    if (activeTrainsList->size() > 0) {
        atSelectBox->setCurrentIndex(0);
        atSelectedIndex = 0;
    }
}

/*private*/ void DispatcherFrame::initializeExtraComboBox() {
    extraBox->clear();
    extraBoxList->clear();
    if (atSelectedIndex < 0) {
        return;
    }
    ActiveTrain* at = activeTrainsList->value(atSelectedIndex);
    //Transit t = at->getTransit();
    QList<AllocatedSection*>* allocatedSectionList = at->getAllocatedSectionList();
    QList<QString> allSections = ((SectionManager*) InstanceManager::getDefault("SectionManager"))->getSystemNameList();
    for (int j = 0; j < allSections.size(); j++) {
        Section* s =((SectionManager*) InstanceManager::getDefault("SectionManager"))->getSection(allSections.value(j));
        if (s->getState() == Section::FREE) {
            // not already allocated, check connectivity to this train's allocated sections
             bool _connected = false;
            for (int k = 0; k < allocatedSectionList->size(); k++) {
                if (connected(s, allocatedSectionList->value(k)->getSection())) {
                    _connected = true;
                }
            }
            if (_connected) {
                // add to the combo box, not allocated and connected to allocated
                extraBoxList->append(s);
                extraBox->addItem(getSectionName(s));
            }
        }
    }
    if (extraBoxList->size() > 0) {
        extraBox->setCurrentIndex(0);
    }
}

/*private*/ bool DispatcherFrame::connected(Section* s1, Section* s2) {
    if ((s1 != NULL) && (s2 != NULL)) {
        QList<EntryPoint*>* s1Entries =  s1->getEntryPointList();
        QList<EntryPoint*>* s2Entries =  s2->getEntryPointList();
        for (int i = 0; i < s1Entries->size(); i++) {
            Block* b = s1Entries->value(i)->getFromBlock();
            for (int j = 0; j < s2Entries->size(); j++) {
                if (b == s2Entries->value(j)->getBlock()) {
                    return true;
                }
            }
        }
    }
    return false;
}

/*public*/ QString DispatcherFrame::getSectionName(Section* sec) {
    QString s = sec->getSystemName();
    QString u = sec->getUserName();
    if ((!u.isNull()) && (u  != ("") && (u  != (s)))) {
        return (s + "(" + u + ")");
    }
    return s;
}
#if 0
/*private*/ void cancelExtraRequested(ActionEvent e) {
    extraFrame.setVisible(false);
    extraFrame.dispose();   // prevent listing in the Window menu.
    extraFrame = NULL;
}

/*private*/ void addExtraRequested(ActionEvent e) {
    int index = extraBox.getSelectedIndex();
    if ((atSelectedIndex < 0) || (index < 0)) {
        cancelExtraRequested(e);
        return;
    }
    ActiveTrain at = activeTrainsList.get(atSelectedIndex);
    Transit t = at->getTransit();
    Section s = extraBoxList.get(index);
    //Section ns = NULL;
    AllocationRequest ar = NULL;
     bool requested = false;
    if (t.containsSection(s)) {
        if (s == at->getNextSectionToAllocate()) {
            // this is a request that the next section in the transit be allocated
            allocateNextRequested(atSelectedIndex);
            return;
        } else {
            // requesting allocation of a section in the Transit, but not the next Section
            int seq = -99;
            QList<Integer> seqList = t.getSeqListBySection(s);
            if (seqList.size() > 0) {
                seq = seqList.get(0).intValue();
            }
            if (seqList.size() > 1) {
                // this section is in the Transit multiple times
                int test = at->getNextSectionSeqNumber() - 1;
                int diff = java.lang.Math.abs(seq - test);
                for (int i = 1; i < seqList.size(); i++) {
                    if (diff > java.lang.Math.abs(test - seqList.get(i).intValue())) {
                        seq = seqList.get(i).intValue();
                        diff = java.lang.Math.abs(seq - test);
                    }
                }
            }
            requested = requestAllocation(at, s, at->getAllocationDirectionFromSectionAndSeq(s, seq),
                    seq, true, extraFrame);
            ar = findAllocationRequestInQueue(s, seq,
                    at->getAllocationDirectionFromSectionAndSeq(s, seq), at);
        }
    } else {
        // requesting allocation of a section outside of the Transit, direction set arbitrary
        requested = requestAllocation(at, s, Section.FORWARD, -99, true, extraFrame);
        ar = findAllocationRequestInQueue(s, -99, Section.FORWARD, at);
    }
    // if allocation request is OK, allocate the Section, if not already allocated
    if (requested && (ar != NULL)) {
        allocateSection(ar, NULL);
    }
    if (extraFrame != NULL) {
        extraFrame.setVisible(false);
        extraFrame.dispose();   // prevent listing in the Window menu.
        extraFrame = NULL;
    }
}

/**
 * This method is for use to extend the allocation of a section to a active
 * train Its use is to allow a dispatcher to manually route a train to its
 * final destination
 */
/*public*/  bool extendActiveTrainsPath(Section s, ActiveTrain at, JmriJFrame jFrame) {
    if (s.getEntryPointFromSection(at->getEndBlockSection(), Section.FORWARD) != NULL
            && at->getNextSectionToAllocate() == NULL) {

        int seq = at->getEndBlockSectionSequenceNumber() + 1;
        if (!at->addEndSection(s, seq)) {
            return false;
        }
        jmri.TransitSection ts = new jmri.TransitSection(s, seq, Section.FORWARD);
        ts.setTemporary(true);
        at->getTransit().addTransitSection(ts);

        // requesting allocation of a section outside of the Transit, direction set arbitrary
         bool requested = requestAllocation(at, s, Section.FORWARD, seq, true, jFrame);

        AllocationRequest ar = findAllocationRequestInQueue(s, seq, Section.FORWARD, at);
        // if allocation request is OK, force an allocation the Section so that the dispatcher can then allocate futher paths through
        if (requested && (ar != NULL)) {
            allocateSection(ar, NULL);
            return true;
        }
    }
    return false;
}

/*public*/  bool removeFromActiveTrainPath(Section s, ActiveTrain at, JmriJFrame jFrame) {
    if (s == NULL || at == NULL) {
        return false;
    }
    if (at->getEndBlockSection() != s) {
        log->error("Active trains end section " + at->getEndBlockSection().getDisplayName() + " is not the same as the requested section to remove " + s.getDisplayName());
        return false;
    }
    if (!at->getTransit().removeLastTemporarySection(s)) {
        return false;
    }

    //Need to find allocation and remove from list.
    for (int k = allocatedSections.size(); k > 0; k--) {
        if (at == allocatedSections.get(k - 1).getActiveTrain()
                && allocatedSections.get(k - 1).getSection() == s) {
            releaseAllocatedSection(allocatedSections.get(k - 1), true);
        }
    }
    at->removeLastAllocatedSection();
    return true;
}

// cancel the automatic restart request of an Active Train from the button in the Dispatcher window
void cancelRestart(ActionEvent e) {
    ActiveTrain at = NULL;
    if (restartingTrainsList.size() == 1) {
        at = restartingTrainsList.get(0);
    } else if (restartingTrainsList.size() > 1) {
        Object choices[] = new Object[restartingTrainsList.size()];
        for (int i = 0; i < restartingTrainsList.size(); i++) {
            if (_ShortActiveTrainNames) {
                choices[i] = restartingTrainsList.get(i).getTrainName();
            } else {
                choices[i] = restartingTrainsList.get(i).getActiveTrainName();
            }
        }
        Object selName = JOptionPane.showInputDialog(dispatcherFrame,
                tr("CancelRestartChoice"),
                tr("CancelRestartTitle"), JOptionPane.QUESTION_MESSAGE, NULL, choices, choices[0]);
        if (selName == NULL) {
            return;
        }
        for (int j = 0; j < restartingTrainsList.size(); j++) {
            if (selName  == (choices[j])) {
                at = restartingTrainsList.get(j);
            }
        }
    }
    if (at != NULL) {
        at->setResetWhenDone(false);
        for (int j = restartingTrainsList.size(); j > 0; j--) {
            if (restartingTrainsList.get(j - 1) == at) {
                restartingTrainsList.remove(j - 1);
                return;
            }
        }
    }
}
#endif
// terminate an Active Train from the button in the Dispatcher window
void DispatcherFrame::terminateTrain(JActionEvent* /*e*/) {
    ActiveTrain* at = NULL;
    if (activeTrainsList->size() == 1) {
        at = activeTrainsList->at(0);
    } else if (activeTrainsList->size() > 1) {
        //Object choices[] = new Object[activeTrainsList->size()];
     QVector<QVariant> choices = QVector<QVariant>(activeTrainsList->size());
        for (int i = 0; i < activeTrainsList->size(); i++) {
            if (_ShortActiveTrainNames) {
                choices.replace(i, activeTrainsList->value(i)->getTrainName());
            } else {
                choices.replace(i, activeTrainsList->value(i)->getActiveTrainName());
            }
        }
        QVariant selName = JOptionPane::showInputDialog(dispatcherFrame,
                tr("Please select an Active Train to Terminate."),
                tr("Terminate Train"), JOptionPane::QUESTION_MESSAGE, QIcon(), choices.toList(), choices.at(0));
        if (selName == QVariant()) {
            return;
        }
        for (int j = 0; j < activeTrainsList->size(); j++) {
            if (selName  == (choices.at(j))) {
                at = activeTrainsList->value(j);
            }
        }
    }
    if (at != NULL) {
        terminateActiveTrain(at);
    }
}

// allocate the next section for an ActiveTrain at dispatcher's request
void DispatcherFrame::allocateNextRequested(int index) {
    // set up an Allocation Request
    ActiveTrain* at = activeTrainsList->at(index);
    Section* next = at->getNextSectionToAllocate();
    if (next == NULL) {
        return;
    }
    int seqNext = at->getNextSectionSeqNumber();
    int dirNext = at->getAllocationDirectionFromSectionAndSeq(next, seqNext);
    if (requestAllocation(at, next, dirNext, seqNext, true, dispatcherFrame)) {
        AllocationRequest* ar = findAllocationRequestInQueue(next, seqNext, dirNext, at);
        if (ar == NULL) {
            return;
        }
        // attempt to allocate
        allocateSection(ar, NULL);
    }
}

/**
 * Creates a new ActiveTrain, and registers it with Dispatcher
 * <P>
 * Required input entries:
 * transitID - system or user name of a Transit in the Transit Table
 * trainID - any text that identifies the train
 * tSource - either ROSTER, OPERATIONS, or USER (see ActiveTrain::java)
 * startBlockName - system or user name of Block where train currently resides
 * startBlockSectionSequenceNumber - sequence number in the Transit of the
 *   Section containing the startBlock (if the startBlock is within the
 *   Transit) , or of the Section the train will enter from the startBlock (if
 *   the startBlock is outside the Transit).
 * endBlockName - system or user name of Block where train will end up after its transit
 * endBlockSectionSequenceNumber - sequence number in the Transit of the
 *   Section containing the endBlock.
 * autoRun - set to "true" if computer is to run the train automatically, otherwise "false"
 * dccAddress - required if "autoRun" is "true", set to NULL otherwise
 * priority - any integer, higher number is higher priority. Used to arbitrate
 *   allocation request conflicts
 * resetWhenDone - set to "true" if the Active Train is capable of continuous running
 *   and the user has requested that it be automatically reset for another run thru its
 *   Transit each time it completes running through its Transit::
 * allocateAllTheWay - set to "true" to allow Auto Allocate to allocate as many sections
 *   as possible between the start section and the end section. Set to false Auto Allocate
 *   allocates no more than three sections ahead.
 * showErrorMessages - "true" if error message dialogs are to be displayed for
 *   detected errors Set to "false" to suppress error message dialogs from this method.
 *   frame - window request is from, or "NULL" if not from a window
 * <P>
 * Returns an ActiveTrain object if successful, returns "NULL" otherwise
 */
/*public*/ ActiveTrain* DispatcherFrame::createActiveTrain(QString transitID, QString trainID, int tSource, QString startBlockName,
        int startBlockSectionSequenceNumber, QString endBlockName, int endBlockSectionSequenceNumber,
         bool autoRun, QString dccAddress, int priority,  bool resetWhenDone,  bool reverseAtEnd,  bool allocateAllTheWay,
         bool showErrorMessages, JmriJFrame* frame) {
//        log->debug("trainID:{}, tSource:{}, startBlockName:{}, startBlockSectionSequenceNumber:{}, endBlockName:{}, endBlockSectionSequenceNumber:{}",
//                trainID,tSource,startBlockName,startBlockSectionSequenceNumber,endBlockName,endBlockSectionSequenceNumber);
    // validate input
    Transit* t = transitManager->getTransit(transitID);
    if (t == NULL) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error1"), new Object[]{transitID}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
         QMessageBox:: critical(frame, tr("Error"), tr("The name \"{%1\" does not match an existing Transit:: Please correct or create as required, and try again.").arg(transitID));
        }
        log->error("Bad Transit name '" + transitID + "' when attempting to create an Active Train");
        return NULL;
    }
    if (t->getState() != Transit::IDLE) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text->MessageFormat->format(tr(
//                    "Error2"), new Object[]{transitID}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
         QMessageBox:: critical(frame, tr("Error"), tr("Transit \"%1\" is in use with another Active Train. Please wait until it''s IDLE, or use a duplicate.").arg(transitID));
        }
        log->error("Transit '" + transitID + "' not IDLE, cannot create an Active Train");
        return NULL;
    }
    if ((trainID == NULL) || trainID  == ("")) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, tr("Error3"),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);

        }QMessageBox:: critical(frame, tr("Error"), tr("TrainID is missing from request to create an Active Train. Please add trainID and try again."));
        log->error("TrainID string not provided, cannot create an Active Train");
        return NULL;
    }
    if ((tSource != ActiveTrain::ROSTER) && (tSource != ActiveTrain::OPERATIONS)
            && (tSource != ActiveTrain::USER)) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, tr("Error21"),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
       QMessageBox:: critical(frame, tr("Error"), tr("Illegal train source identifier provided. Please correct the train source identifier and try again."));
       }
        log->error("Train source is invalid - " + QString::number(tSource) + " - cannot create an Active Train");
        return NULL;
    }
    Block* startBlock = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(startBlockName);
    if (startBlock == NULL) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error4"), new Object[]{startBlockName}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(frame, tr("Error"), tr("The name \"%1\" does not match an allowed starting block. Please correct and try again.").arg(startBlockName));
        }
        log->error("Bad startBlockName '" + startBlockName + "' when attempting to create an Active Train");
        return NULL;
    }
    if (isInAllocatedSection(startBlock)) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error5"), new Object[]{startBlock.getDisplayName()}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
         QMessageBox:: critical(frame, tr("Error"), tr("Requested starting block \"%1\" is a Section allocated to a different Active Train. Please correct and try again.").arg(startBlock->getDisplayName()));
        }
        log->error("Start block '" + startBlockName + "' in allocated Section, cannot create an Active Train");
        return NULL;
    }
    if (_HasOccupancyDetection && (!(startBlock->getState() == Block::OCCUPIED))) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error6"), new Object[]{startBlock.getDisplayName()}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
         QMessageBox:: critical(frame, tr("Error"), tr("No train detected in requested starting block \"%1\". Please correct and try again.").arg(startBlock->getDisplayName()));
        }
        log->error("No train in start block '" + startBlockName + "', cannot create an Active Train");
        return NULL;
    }
    if (startBlockSectionSequenceNumber <= 0) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, tr("Error12"),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE); sequence number was provided. Please correct, and try again."));
        }
    } else if (startBlockSectionSequenceNumber > t->getMaxSequence()) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error13"), new Object[]{"" + startBlockSectionSequenceNumber}),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
       QMessageBox:: critical(frame, tr("Error"), tr("Invalid start Block Section sequence number \"%1\". Please correct and try again.").arg(startBlockSectionSequenceNumber));
       }
        log->error("Invalid sequence number '" + QString::number(startBlockSectionSequenceNumber) + "' when attempting to create an Active Train");
        return NULL;
    }
    Block* endBlock = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(endBlockName);
    if ((endBlock == NULL) || (!t->containsBlock(endBlock))) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error7"), new Object[]{endBlockName}), Bundle.getMessage("ErrorTitle"),
//                    JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("The name \"%1\" does not match an existing Block in the requested Transit. Please correct, and try again.").arg(endBlockName));
        }
        log->error("Bad endBlockName '" + endBlockName + "' when attempting to create an Active Train");
        return NULL;
    }
    if ((endBlockSectionSequenceNumber <= 0) && (t->getBlockCount(endBlock) > 1)) {
//        JOptionPane.showMessageDialog(frame, tr("Error8"),
//                Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("End Block is in requested Transit, but no Sectionsequence number was provided. Please correct, and try again."));
    } else if (endBlockSectionSequenceNumber > t->getMaxSequence()) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error9"), new Object[]{"" + endBlockSectionSequenceNumber}),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("Invalid end Block Section sequence number \"%1\". Please correct and try again."));
        }
        log->error("Invalid sequence number '" + QString::number(endBlockSectionSequenceNumber) + "' when attempting to create an Active Train");
        return NULL;
    }
    if ((!reverseAtEnd) && resetWhenDone && (!t->canBeResetWhenDone())) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                    "Error26"), new Object[]{(t->getSystemName() + "(" + t->getUserName() + ")")}),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("Request for Reset When Done, but Transit, \"%1\",  is not set up correctly. Cannot create a new Active Train. "));
        }
        log->error("Incompatible Transit set up and request to Reset When Done when attempting to create an Active Train");
        return NULL;
    }
    if (autoRun && ((dccAddress == NULL) || dccAddress  == (""))) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, tr("Error10"),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("Automatic running requested, but no dcc address was provided. Please provide dcc address and try again."));
        }
        log->error("AutoRun requested without a dccAddress when attempting to create an Active Train");
        return NULL;
    }
    if (autoRun) {
        if (_autoTrainsFrame == NULL) {
            // This is the first automatic active train--check if all required options are present
            //   for automatic running.  First check for layout editor panel
            if (!_UseConnectivity || (_LE == NULL)) {
                if (showErrorMessages) {
//                    JOptionPane.showMessageDialog(frame, tr("Error33"),
//                            Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("Automatic running requested, but no Layout Editor panel was specified in the Options window. Please try again."));
                    log->error("AutoRun requested without a LayoutEditor panel for connectivity.");
                    return NULL;
                }
            }
            if (!_HasOccupancyDetection) {
                if (showErrorMessages) {
//                    JOptionPane.showMessageDialog(frame, tr("Error35"),
//                            Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("Automatic running requested, but occupancy detection   was not specified in the Options window. Please try again."));
                    log->error("AutoRun requested without occupancy detection.");
                    return NULL;
                }
            }
        }
        // check/set Transit specific items for automatic running
        // validate connectivity for all Sections in this transit
        int numErrors = t->validateConnectivity(_LE);
        if (numErrors != 0) {
            if (showErrorMessages) {
//                JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                        "Error34"), new Object[]{("" + numErrors)}),
//                        Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("\"%1\" errors found when checking connectivity of Sections  in this Transit. Check message log for details.").arg(numErrors));
            }
            return NULL;
        }
        // check/set direction sensors in signal logic for all Sections in this Transit::
        if (getSignalType() == SIGNALHEAD) {
            numErrors = t->checkSignals(_LE);
            if (numErrors == 0) {
                t->initializeBlockingSensors();
            }
            if (numErrors != 0) {
                if (showErrorMessages) {
//                    JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                            "Error36"), new Object[]{("" + numErrors)}),
//                            Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("\"%1\" errors found when checking/setting direction sensors in  signal logic for this Transit. Check message log for details.").arg(numErrors));
                }
                return NULL;
            }
        }
        //TODO: Need to check signalMasts as well
        // this train is OK, activate the AutoTrains window, if needed
        if (_autoTrainsFrame == NULL) {
            _autoTrainsFrame = new AutoTrainsFrame(_instance);
        } else {
            _autoTrainsFrame->setVisible(true);
        }
    } else if (_UseConnectivity && (_LE != NULL)) {
        // not auto run, set up direction sensors in signals since use connectivity was requested
        if (getSignalType() == SIGNALHEAD) {
            int numErrors = t->checkSignals(_LE);
            if (numErrors == 0) {
                t->initializeBlockingSensors();
            }
            if (numErrors != 0) {
                if (showErrorMessages) {
//                    JOptionPane.showMessageDialog(frame, java.text.MessageFormat->format(tr(
//                            "Error36"), new Object[]{("" + numErrors)}),
//                            Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
      QMessageBox:: critical(frame, tr("Error"), tr("\"%1\" errors found when checking/setting direction sensors in signal logic for this Transit. Check message log for details.").arg(numErrors));
                }
                return NULL;
            }
        }
    }
    // all information checks out - create
    ActiveTrain* at = new ActiveTrain(t, trainID, tSource);
    //if (at==NULL) {
    //	if (showErrorMessages) {
    //		JOptionPane.showMessageDialog(frame,java.text.MessageFormat->format(tr(
    //				"Error11"),new Object[] { transitID, trainID }), Bundle.getMessage("ErrorTitle"),
    //					JOptionPane.ERROR_MESSAGE);
    //	}
    //	log->error("Creating Active Train failed, Transit - "+transitID+", train - "+trainID);
    //	return NULL;
    //}
    activeTrainsList->append(at);
//    PropertyChangeListener* listener = NULL;
//    at->addPropertyChangeListener(listener = new PropertyChangeListener() {
//        @Override
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            handleActiveTrainChange(e);
//        }
//    });
//    _atListeners.add(listener);
    connect(at->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(handleActiveTrainChange()));
    t->setState(Transit::ASSIGNED);
    at->setStartBlock(startBlock);
    at->setStartBlockSectionSequenceNumber(startBlockSectionSequenceNumber);
    at->setEndBlock(endBlock);
    at->setEndBlockSection(t->getSectionFromBlockAndSeq(endBlock, endBlockSectionSequenceNumber));
    at->setEndBlockSectionSequenceNumber(endBlockSectionSequenceNumber);
    at->setResetWhenDone(resetWhenDone);
    if (resetWhenDone) {
        restartingTrainsList->append(at);
    }
    at->setReverseAtEnd(reverseAtEnd);
    at->setAllocateAllTheWay(allocateAllTheWay);
    at->setPriority(priority);
    at->setDccAddress(dccAddress);
    at->setAutoRun(autoRun);
    return at;
}

/*public*/ void DispatcherFrame::allocateNewActiveTrain(ActiveTrain* at) {
    if (at->getDelayedStart() == ActiveTrain::SENSORDELAY && at->getDelaySensor() != NULL) {
        if (at->getDelaySensor()->getState() != Sensor::ACTIVE) {
            at->initializeDelaySensor();
        }
    }
    AllocationRequest* ar = at->initializeFirstAllocation();
    if (ar != NULL) {
        if (( ar->getSection())->containsBlock(at->getStartBlock())) {
            // Active Train is in the first Section, go ahead and allocate it
            AllocatedSection* als = allocateSection(ar, NULL);
            if (als == NULL) {
                log->error("Problem allocating the first Section of the Active Train - " + at->getActiveTrainName());
            }
        }
    }
    activeTrainsTableModel->fireTableDataChanged();
    if (allocatedSectionTableModel != NULL) {
        allocatedSectionTableModel->fireTableDataChanged();
    }
}

/*private*/ void DispatcherFrame::handleActiveTrainChange(PropertyChangeEvent* /*e*/) {
    activeTrainsTableModel->fireTableDataChanged();
}

/*private*/ bool DispatcherFrame::isInAllocatedSection(Block* b) {
    for (int i = 0; i < allocatedSections->size(); i++) {
        Section* s = allocatedSections->at(i)->getSection();
        if (s->containsBlock(b)) {
            return true;
        }
    }
    return false;
}

/**
 * Terminates an Active Train and removes it from the Dispatcher The
 * ActiveTrain object should not be used again after this method is called
 */
/*public*/ void DispatcherFrame::terminateActiveTrain(ActiveTrain* at) {
    // ensure there is a train to terminate
    if (at == NULL) {
        log->error("Null ActiveTrain pointer when attempting to terminate an ActiveTrain");
        return;
    }
#if 0
    // terminate the train - remove any allocation requests
    for (int k = allocationRequests->size(); k > 0; k--) {
        if (at == allocationRequests->at(k - 1)->getActiveTrain()) {
            allocationRequests->at(k - 1)->dispose();
            allocationRequests->removeAt(k - 1);
        }
    }
    // remove any allocated sections
    for (int k = allocatedSections->size(); k > 0; k--) {
//        try {
            if (at == allocatedSections->at(k - 1)->getActiveTrain()) {
                releaseAllocatedSection(allocatedSections->at(k - 1), true);
            }
//        } catch (Exception e) {
//            log->warn("releaseAllocatedSection failed - maybe the AllocatedSection was removed due to a terminating train??",e.toString());
//            continue;
//        }
    }
    // remove from restarting trains list, if present
    for (int j = restartingTrainsList->size(); j > 0; j--) {
        if (at == restartingTrainsList->at(j - 1)) {
            restartingTrainsList->removeAt(j - 1);
        }
    }
    // terminate the train
    for (int m = activeTrainsList->size(); m > 0; m--) {
        if (at == activeTrainsList->at(m - 1)) {
            activeTrainsList->removeAt(m - 1);
            at->removePropertyChangeListener(_atListeners->at(m - 1));
            _atListeners->removeAt(m - 1);
        }
    }
    if (at->getAutoRun()) {
        AutoActiveTrain aat = at->getAutoActiveTrain();
        _autoTrainsFrame.removeAutoActiveTrain(aat);
        aat->terminate();
        aat->dispose();
    }
    removeHeldMast(NULL, at);
    at->terminate();
    at->dispose();
    activeTrainsTableModel.fireTableDataChanged();
    if (allocatedSectionTableModel != NULL) {
        allocatedSectionTableModel.fireTableDataChanged();
    }
    allocationRequestTableModel.fireTableDataChanged();
   #endif
}

/**
 * Creates an Allocation Request, and registers it with Dispatcher
 * <P>
 * Required input entries: activeTrain - ActiveTrain requesting the
 * allocation section - Section to be allocated direction - direction of
 * travel in the allocated Section seqNumber - sequence number of the
 * Section in the Transit of the ActiveTrain:: If the requested Section is
 * not in the Transit, a sequence number of -99 should be entered.
 * showErrorMessages - "true" if error message dialogs are to be displayed
 * for detected errors Set to "false" to suppress error message dialogs from
 * this method. frame - window request is from, or "NULL" if not from a
 * window
 */
/*protected*/ bool DispatcherFrame::requestAllocation(ActiveTrain* activeTrain, Section* section, int direction,
        int seqNumber, bool showErrorMessages, JmriJFrame* frame) {
    // check input entries
    if (activeTrain == NULL) {
        if (showErrorMessages) {
//            JOptionPane.showMessageDialog(frame, tr("Error16"),
//                    Bundle.getMessage("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(frame, tr("Error"), tr("No ActiveTrain specified in request for allocation of a section. Cannot process the request."));
        }
        log->error("Missing ActiveTrain specification");
        return false;
    }
#if 1
    if (section == NULL) {
        if (showErrorMessages) {
            JOptionPane::showMessageDialog(frame, tr(
                    "No Section specified in Allocation Request from Active\nTrain \"%1\". Cannot process the request.").arg(activeTrain->getActiveTrainName()), tr("Error"),
                    JOptionPane::ERROR_MESSAGE);
        }
        log->error("Missing Section specification in allocation request from " + activeTrain->getActiveTrainName());
        return false;
    }
    if (((seqNumber <= 0) || (seqNumber > (activeTrain->getTransit()->getMaxSequence()))) && (seqNumber != -99)) {
        if (showErrorMessages) {
            JOptionPane::showMessageDialog(frame, tr(
                    "Out-of-range sequence order number \"%1\" in Allocation Request from\nActive Train \"%2\". Cannot process the request.").arg(seqNumber).arg( activeTrain->getActiveTrainName()), tr("Error"),JOptionPane::ERROR_MESSAGE);
        }
        log->error("Out-of-range sequence number *" + QString::number(seqNumber) + "* in allocation request");
        return false;
    }
    if ((direction != Section::FORWARD) && (direction != Section::REVERSE)) {
        if (showErrorMessages) {
            JOptionPane::showMessageDialog(frame, tr(
                    "Invalid direction \"%1\" in allocation request from Active\nTrain \"%2\". Cannot process the request.").arg(direction).arg(activeTrain->getActiveTrainName()), tr("Error"), JOptionPane::ERROR_MESSAGE);
        }
        log->error("Invalid direction '" + QString::number(direction) + "' specification in allocation request");
        return false;
    }
    // check if this allocation has already been requested
    AllocationRequest* ar = findAllocationRequestInQueue(section, seqNumber, direction, activeTrain);
    if (ar == NULL) {
        ar = new AllocationRequest(section, seqNumber, direction, activeTrain);
        allocationRequests->append(ar);
        if (_AutoAllocate) {
            autoAllocate->scanAllocationRequestList(allocationRequests);
        }
    }
#endif
    activeTrainsTableModel->fireTableDataChanged();
    allocationRequestTableModel->fireTableDataChanged();
    return true;
}

// ensures there will not be any duplicate allocation requests
/*protected*/ AllocationRequest* DispatcherFrame::findAllocationRequestInQueue(Section* s, int seq, int dir, ActiveTrain* at) {
    for (int i = 0; i < allocationRequests->size(); i++) {
        AllocationRequest* ar = allocationRequests->at(i);
        if (( ar->getActiveTrain() == at) && ( ar->getSection() == s) && ( ar->getSectionSeqNumber() == seq)
                && ( ar->getSectionDirection() == dir)) {
            return ar;
        }
    }
    return NULL;
}

/*private*/ void DispatcherFrame::cancelAllocationRequest(int index) {
    AllocationRequest* ar = allocationRequests->at(index);
    allocationRequests->removeAt(index);
     ar->dispose();
    allocationRequestTableModel->fireTableDataChanged();
}

/*private*/ void DispatcherFrame::allocateRequested(int index) {
    AllocationRequest* ar = allocationRequests->at(index);
    allocateSection(ar, NULL);
}

/*protected*/ void DispatcherFrame::addDelayedTrain(ActiveTrain* at) {
    if (at->getDelayedRestart() == ActiveTrain::TIMEDDELAY) {
        if (!delayedTrains->contains(at)) {
            delayedTrains->append(at);
        }
    } else if (at->getDelayedRestart() == ActiveTrain::SENSORDELAY) {
        if (at->getRestartSensor() != NULL) {
            at->initializeRestartSensor();
        }
    }
}

/**
 * Allocates a Section to an Active Train according to the information in an
 * AllocationRequest If successful, returns an AllocatedSection and removes
 * the AllocationRequest from the queue. If not successful, returns NULL and
 * leaves the AllocationRequest in the queue. To be allocatable, a Section
 * must be FREE and UNOCCUPIED. If a Section is OCCUPIED, the allocation is
 * rejected unless the dispatcher chooses to override this restriction. To
 * be allocatable, the Active Train must not be waiting for its start time.
 * If the start time has not been reached, the allocation is rejected,
 * unless the dispatcher chooses to override the start time. The user may
 * choose to specify the next Section by entering "ns". If this method is to
 * determine the next Section, or if the next section is the last section,
 * NULL should be entered for ns. Null should also be entered for ns if
 * allocating an Extra Section that is not the Next Section.
 */
/*public*/ AllocatedSection* DispatcherFrame::allocateSection(AllocationRequest* ar, Section* /*ns*/) {
    AllocatedSection* as = NULL;
//    Section* nextSection = NULL;
//    int nextSectionSeqNo = 0;
    if (ar != NULL) {
        ActiveTrain* at =  ar->getActiveTrain();
        if (at->holdAllocation() || at->reachedRestartPoint()) {
            return NULL;
        }
        Section* s =  ar->getSection();
        if (s->getState() != Section::FREE) {
            return NULL;
        }
        // skip occupancy check if this is the first allocation and the train is occupying the Section
//         bool checkOccupancy = true;
#if 0 // TODO:
        if ((at->getLastAllocatedSection() == NULL) && (s->containsBlock(at->getStartBlock()))) {
            checkOccupancy = false;
        }
        // check if section is occupied
        if (checkOccupancy && (s->getOccupancy() == Section::OCCUPIED)) {
            if (_AutoAllocate) {
                return NULL;  // autoAllocate never overrides occupancy
            }
            int selectedValue = JOptionPane.showOptionDialog(dispatcherFrame,
                    tr("Question1"), Bundle.getMessage("WarningTitle"),
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, NULL,
                    new Object[]{tr("ButtonYes"), tr("ButtonNo")}, tr("ButtonNo"));
            if (selectedValue == 1) {
                return NULL;   // return without allocating if "No" response
            }
        }
        // check if train has reached its start time if delayed start
        if (checkOccupancy && (!at->getStarted()) && at->getDelayedStart() != ActiveTrain::NODELAY) {
            if (_AutoAllocate) {
                return NULL;  // autoAllocate never overrides start time
            }
            int selectedValue = JOptionPane.showOptionDialog(dispatcherFrame,
                    tr("Question4"), Bundle.getMessage("WarningTitle"),
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, NULL,
                    new Object[]{tr("ButtonYes"), tr("ButtonNo")}, tr("ButtonNo"));
            if (selectedValue == 1) {
                return NULL;
            } else {
                at->setStarted();
                for (int i = delayedTrains.size() - 1; i >= 0; i--) {
                    if (delayedTrains.get(i) == at) {
                        delayedTrains.remove(i);
                    }
                }
            }

        }
        //check here to see if block is already assigned to an allocated section;
        if (getSignalType() == SIGNALMAST && checkBlocksNotInAllocatedSection(s, ar) != NULL) {
            return NULL;
        }
        // Programming Note: if ns is not NULL, the program will not check for end Block, but will use ns. Calling
        //		code must do all validity checks on a non-NULL ns.
        if (ns != NULL) {
            nextSection = ns;
        } else if (( ar->getSectionSeqNumber() != -99) && (at->getNextSectionSeqNumber() ==  ar->getSectionSeqNumber())
                && (!((s == at->getEndBlockSection()) && ( ar->getSectionSeqNumber() == at->getEndBlockSectionSequenceNumber())))
                && (!(at->isAllocationReversed() && ( ar->getSectionSeqNumber() == 1)))) {
            // not at either end - determine the next section
            int seqNum =  ar->getSectionSeqNumber();
            if (at->isAllocationReversed()) {
                seqNum -= 1;
            } else {
                seqNum += 1;
            }
            QList<Section> secList = at->getTransit().getSectionListBySeq(seqNum);
            if (secList.size() == 1) {
                nextSection = secList.get(0);

            } else if (secList.size() > 1) {
                if (_AutoAllocate) {
                    nextSection = autoChoice(secList, ar);
                } else {
                    nextSection = dispatcherChoice(secList, ar);
                }
            }
            nextSectionSeqNo = seqNum;
        } else if (at->getReverseAtEnd() && (!at->isAllocationReversed()) && (s == at->getEndBlockSection())
                && ( ar->getSectionSeqNumber() == at->getEndBlockSectionSequenceNumber())) {
            // need to reverse Transit direction when train is in the last Section, set next section.
            nextSectionSeqNo = at->getEndBlockSectionSequenceNumber() - 1;
            at->setAllocationReversed(true);
            QList<Section> secList = at->getTransit().getSectionListBySeq(nextSectionSeqNo);
            if (secList.size() == 1) {
                nextSection = secList.get(0);
            } else if (secList.size() > 1) {
                if (_AutoAllocate) {
                    nextSection = autoChoice(secList, ar);
                } else {
                    nextSection = dispatcherChoice(secList, ar);
                }
            }
        } else if (((!at->isAllocationReversed()) && (s == at->getEndBlockSection())
                && ( ar->getSectionSeqNumber() == at->getEndBlockSectionSequenceNumber()))
                || (at->isAllocationReversed() && ( ar->getSectionSeqNumber() == 1))) {
            // request to allocate the last block in the Transit, or the Transit is reversed and
            //      has reached the beginning of the Transit--check for automatic restart
            if (at->getResetWhenDone()) {
                if (at->getDelayedRestart() != ActiveTrain::NODELAY) {
                    at->holdAllocation(true);
                }
                nextSection = at->getSecondAllocatedSection();
                nextSectionSeqNo = 2;
                at->setAllocationReversed(false);
            }
        }

        //This might be the location to check to see if we have an intermediate section that we then need to perform extra checks on.
        //Working on the basis that if the nextsection is not NULL, then we are not at the end of the transit.
        QList<Section> intermediateSections = new QList<Section>();
        Section mastHeldAtSection = NULL;
        if (nextSection != NULL &&  ar->getSection().getProperty("intermediateSection") != NULL && ((Boolean)  ar->getSection().getProperty("intermediateSection")). boolValue()) {
            String property = "forwardMast";
            if (at->isAllocationReversed()) {
                property = "reverseMast";
            }
            if ( ar->getSection().getProperty(property) != NULL) {
                SignalMast endMast = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast( ar->getSection().getProperty(property).toString());
                if (endMast != NULL) {
                    if (endMast.getHeld()) {
                        mastHeldAtSection =  ar->getSection();
                    }
                }
            }
            QList<TransitSection> tsList =  ar->getActiveTrain().getTransit().getTransitSectionList();
             bool found = false;
            if (at->isAllocationReversed()) {
                for (int i = tsList.size() - 1; i > 0; i--) {
                    TransitSection ts = tsList.get(i);
                    if (ts.getSection() ==  ar->getSection() && ts.getSequenceNumber() ==  ar->getSectionSeqNumber()) {
                        found = true;
                    } else if (found) {
                        if (ts.getSection().getProperty("intermediateSection") != NULL && ((Boolean) ts.getSection().getProperty("intermediateSection")). boolValue()) {
                            intermediateSections.add(ts.getSection());
                        } else {
                            //we add the section after the last intermediate in, so that the last allocation request can be built correctly
                            intermediateSections.add(ts.getSection());
                            break;
                        }
                    }
                }
            } else {
                for (int i = 0; i <= tsList.size() - 1; i++) {
                    TransitSection ts = tsList.get(i);
                    if (ts.getSection() ==  ar->getSection() && ts.getSequenceNumber() ==  ar->getSectionSeqNumber()) {
                        found = true;
                    } else if (found) {
                        if (ts.getSection().getProperty("intermediateSection") != NULL && ((Boolean) ts.getSection().getProperty("intermediateSection")). boolValue()) {
                            intermediateSections.add(ts.getSection());
                        } else {
                            //we add the section after the last intermediate in, so that the last allocation request can be built correctly
                            intermediateSections.add(ts.getSection());
                            break;
                        }
                    }
                }
            }
             bool intermediatesOccupied = false;

            for (int i = 0; i < intermediateSections.size() - 1; i++) {  // ie do not check last section which is not an intermediate section
                Section se = intermediateSections.get(i);
                if (se.getState() == Section.FREE) {
                    //If the section state is free, we need to look to see if any of the blocks are used else where
                    Section conflict = checkBlocksNotInAllocatedSection(se, NULL);
                    if (conflict != NULL) {
                        //We have a conflicting path
                        //We might need to find out if the section which the block is allocated to is one in our transit, and if so is it running in the same direction.
                        return NULL;
                    } else {
                        if (mastHeldAtSection == NULL) {
                            if (se.getProperty(property) != NULL) {
                                SignalMast endMast = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast(se.getProperty(property).toString());
                                if (endMast != NULL && endMast.getHeld()) {
                                    mastHeldAtSection = se;
                                }
                            }
                        }
                    }
                } else if (at->getLastAllocatedSection() != NULL && se.getState() != at->getLastAllocatedSection().getState()) {
                    //Last allocated section and the checking section direction are not the same
                    return NULL;
                } else {
                    intermediatesOccupied = true;
                }
            }
            //If the intermediate sections are already occupied or allocated then we clear the intermediate list and only allocate the original request.
            if (intermediatesOccupied) {
                intermediateSections = new QList<Section>();
            }
        }

        // check/set turnouts if requested or if autorun
        // Note: If "Use Connectivity..." is specified in the Options window, turnouts are checked. If
        //			turnouts are not set correctly, allocation will not proceed without dispatcher override.
        //		 If in addition Auto setting of turnouts is requested, the turnouts are set automatically
        //			if not in the correct position.
        // Note: Turnout checking and/or setting is not performed when allocating an extra section.
        if ((_UseConnectivity) && ( ar->getSectionSeqNumber() != -99)) {
            if (!checkTurnoutStates(s,  ar->getSectionSeqNumber(), nextSection, at, at->getLastAllocatedSection())) {
                return NULL;
            }
            Section preSec = s;
            Section tmpcur = nextSection;
            int tmpSeqNo = nextSectionSeqNo;
            //The first section in the list will be the same as the nextSection, so we skip that->
            for (int i = 1; i < intermediateSections.size(); i++) {
                Section se = intermediateSections.get(i);
                if (preSec == mastHeldAtSection) {
                    log->debug("Section is beyond held mast do not set turnouts " + (tmpcur != NULL ? tmpcur.getDisplayName() : "NULL"));
                    break;
                }
                if (!checkTurnoutStates(tmpcur, tmpSeqNo, se, at, preSec)) {
                    return NULL;
                }
                preSec = tmpcur;
                tmpcur = se;
                if (at->isAllocationReversed()) {
                    tmpSeqNo -= 1;
                } else {
                    tmpSeqNo += 1;
                }
            }
        }

        as = allocateSection(at, s,  ar->getSectionSeqNumber(), nextSection, nextSectionSeqNo,  ar->getSectionDirection());
        if (intermediateSections.size() > 1 && mastHeldAtSection != s) {
            Section tmpcur = nextSection;
            int tmpSeqNo = nextSectionSeqNo;
            int tmpNxtSeqNo = tmpSeqNo;
            if (at->isAllocationReversed()) {
                tmpNxtSeqNo -= 1;
            } else {
                tmpNxtSeqNo += 1;
            }
            //The first section in the list will be the same as the nextSection, so we skip that->
            for (int i = 1; i < intermediateSections.size(); i++) {
                if (tmpcur == mastHeldAtSection) {
                    log->debug("Section is beyond held mast do not allocate any more sections " + (tmpcur != NULL ? tmpcur.getDisplayName() : "NULL"));
                    break;
                }
                Section se = intermediateSections.get(i);
                as = allocateSection(at, tmpcur, tmpSeqNo, se, tmpNxtSeqNo,  ar->getSectionDirection());
                tmpcur = se;
                if (at->isAllocationReversed()) {
                    tmpSeqNo -= 1;
                    tmpNxtSeqNo -= 1;
                } else {
                    tmpSeqNo += 1;
                    tmpNxtSeqNo += 1;
                }
            }
        }
        int ix = -1;
        for (int i = 0; i < allocationRequests.size(); i++) {
            if (ar == allocationRequests.get(i)) {
                ix = i;
            }
        }
        allocationRequests.remove(ix);
         ar->dispose();
        allocationRequestTableModel.fireTableDataChanged();
        activeTrainsTableModel.fireTableDataChanged();
        if (allocatedSectionTableModel != NULL) {
            allocatedSectionTableModel.fireTableDataChanged();
        }
        if (extraFrame != NULL) {
            cancelExtraRequested(NULL);
        }
        if (_AutoAllocate) {
            requestNextAllocation(at);
            autoAllocate.scanAllocationRequestList(allocationRequests);
        }
#endif
    } else {
        log->error("Null Allocation Request provided in request to allocate a section");
    }
    return as;
}

#if 0
AllocatedSection allocateSection(ActiveTrain at, Section s, int seqNum, Section nextSection, int nextSectionSeqNo, int direction) {
    AllocatedSection as = NULL;
    // allocate the section
    as = new AllocatedSection(s, at, seqNum, nextSection, nextSectionSeqNo);
    if (_SupportVSDecoder) {
        as.addPropertyChangeListener(InstanceManager.getDefault(jmri.jmrit.vsdecoder.VSDecoderManager.class));
    }

    s.setState(direction/* ar->getSectionDirection()*/);
    if (getSignalType() == SIGNALMAST) {
        String property = "forwardMast";
        if (s.getState() == Section.REVERSE) {
            property = "reverseMast";
        }
        if (s.getProperty(property) != NULL) {
            SignalMast toHold = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast(s.getProperty(property).toString());
            if (toHold != NULL) {
                if (!toHold.getHeld()) {
                    heldMasts.add(new HeldMastDetails(toHold, at));
                    toHold.setHeld(true);
                }
            }

        }

        if (at->getLastAllocatedSection() != NULL && at->getLastAllocatedSection().getProperty(property) != NULL) {
            SignalMast toRelease = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast(at->getLastAllocatedSection().getProperty(property).toString());
            if (toRelease != NULL && isMastHeldByDispatcher(toRelease, at)) {
                removeHeldMast(toRelease, at);
                //heldMasts.remove(toRelease);
                toRelease.setHeld(false);
            }
        }
    }
    at->addAllocatedSection(as);
    allocatedSections.add(as);
    return as;
}

 bool checkTurnoutStates(Section s, int sSeqNum, Section nextSection, ActiveTrain at, Section prevSection) {
     bool turnoutsOK = true;
    if (_AutoTurnouts || at->getAutoRun()) {
        // automatically set the turnouts for this section before allocation
        turnoutsOK = autoTurnouts.setTurnoutsInSection(s, sSeqNum, nextSection,
                at, _LE, _TrustKnownTurnouts, prevSection);
    } else {
        // check that turnouts are correctly set before allowing allocation to proceed
        turnoutsOK = autoTurnouts.checkTurnoutsInSection(s, sSeqNum, nextSection,
                at, _LE, prevSection);
    }
    if (!turnoutsOK) {
        if (_AutoAllocate) {
            return false;
        } else {
            // give the manual dispatcher a chance to override turnouts not OK
            int selectedValue = JOptionPane.showOptionDialog(dispatcherFrame,
                    tr("Question2"), Bundle.getMessage("WarningTitle"),
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, NULL,
                    new Object[]{tr("ButtonYes"), tr("ButtonNo")}, tr("ButtonNo"));
            if (selectedValue == 1) {
                return false;   // return without allocating if "No" response
            }
        }
    }
    return true;
}

#endif
//static class HeldMastDetails {

//    SignalMast* mast = NULL;
//    ActiveTrain* at = NULL;

    HeldMastDetails::HeldMastDetails(SignalMast* sm, ActiveTrain* a) {
        mast = sm;
        at = a;
    }

    ActiveTrain* HeldMastDetails::getActiveTrain() {
        return at;
    }

    SignalMast* HeldMastDetails::getMast() {
        return mast;
    }
//};

/*public*/  bool DispatcherFrame::isMastHeldByDispatcher(SignalMast* sm, ActiveTrain* at) {

    foreach (HeldMastDetails* hmd, *heldMasts) {
        if (hmd->getMast() == sm && hmd->getActiveTrain() == at) {
            return true;
        }
    }

    return false;
}

/*private*/ void DispatcherFrame::removeHeldMast(SignalMast* sm, ActiveTrain* at) {
    QList<HeldMastDetails*>* toRemove = new QList<HeldMastDetails*>();
    foreach (HeldMastDetails* hmd, *heldMasts) {
        if (hmd->getActiveTrain() == at) {
            if (sm == NULL) {
                toRemove->append(hmd);
            } else if (sm == hmd->getMast()) {
                toRemove->append(hmd);
            }
        }
    }
    foreach (HeldMastDetails* hmd, *toRemove) {
        hmd->getMast()->setHeld(false);
        heldMasts->removeOne(hmd);
    }
}
#if 0
/*
 * This is used to determine if the blocks in a section we want to allocate are already allocated to a section, or if they are now free.
 */
/*protected*/ Section checkBlocksNotInAllocatedSection(Section s, AllocationRequest ar) {
    for (AllocatedSection as : allocatedSections) {
        if (as.getSection() != s) {
            QList<Block> blas = as.getSection().getBlockList();
            for (Block b : s.getBlockList()) {
                if (blas.contains(b)) {
                    if (as.getSection().getOccupancy() == Block.OCCUPIED) {
                        //The next check looks to see if the block has already been passed or not and therefore ready for allocation.
                        if (as.getSection().getState() == Section.FORWARD) {
                            for (int i = 0; i < blas.size(); i++) {
                                //The block we get to is occupied therefore the subsequent blocks have not been entered
                                if (blas.get(i).getState() == Block.OCCUPIED) {
                                    if (ar != NULL) {
                                         ar->setWaitingOnBlock(b);
                                    }
                                    return as.getSection();
                                } else if (blas.get(i) == b) {
                                    break;
                                }
                            }
                        } else {
                            for (int i = blas.size(); i >= 0; i--) {
                                //The block we get to is occupied therefore the subsequent blocks have not been entered
                                if (blas.get(i).getState() == Block.OCCUPIED) {
                                    if (ar != NULL) {
                                         ar->setWaitingOnBlock(b);
                                    }
                                    return as.getSection();
                                } else if (blas.get(i) == b) {
                                    break;
                                }
                            }
                        }
                    } else if (as.getSection().getOccupancy() != Section.FREE) {
                        if (ar != NULL) {
                             ar->setWaitingOnBlock(b);
                        }
                        return as.getSection();
                    }
                }
            }
        }
    }
    return NULL;
}

// automatically make a choice of next section
/*private*/ Section autoChoice(QList<Section> sList, AllocationRequest ar) {
    Section tSection = autoAllocate.autoNextSectionChoice(sList, ar);
    if (tSection != NULL) {
        return tSection;
    }
    // if automatic choice failed, ask the dispatcher
    return dispatcherChoice(sList, ar);
}

// manually make a choice of next section
/*private*/ Section dispatcherChoice(QList<Section> sList, AllocationRequest ar) {
    Object choices[] = new Object[sList.size()];
    for (int i = 0; i < sList.size(); i++) {
        Section s = sList.get(i);
        String txt = s.getSystemName();
        String user = s.getUserName();
        if ((user != NULL) && (!user  == ("")) && (!user  == (txt))) {
            txt = txt + "(" + user + ")";
        }
        choices[i] = txt;
    }
    Object secName = JOptionPane.showInputDialog(dispatcherFrame,
            tr("ExplainChoice") + " " +  ar->getSectionName() + ".",
            tr("ChoiceFrameTitle"), JOptionPane.QUESTION_MESSAGE, NULL, choices, choices[0]);
    if (secName == NULL) {
        JOptionPane.showMessageDialog(dispatcherFrame, tr("WarnCancel"));
        return sList.get(0);
    }
    for (int j = 0; j < sList.size(); j++) {
        if (secName  == (choices[j])) {
            return sList.get(j);
        }
    }
    return sList.get(0);
}

// submit an AllocationRequest for the next Section of an ActiveTrain
/*private*/ void requestNextAllocation(ActiveTrain at) {
    // set up an Allocation Request
    Section next = at->getNextSectionToAllocate();
    if (next == NULL) {
        return;
    }
    int seqNext = at->getNextSectionSeqNumber();
    int dirNext = at->getAllocationDirectionFromSectionAndSeq(next, seqNext);
    requestAllocation(at, next, dirNext, seqNext, true, dispatcherFrame);
}
#endif
/**
 * Check if any allocation requests need to be allocated, or if any
 * allocated sections need to be released
 */
/*private*/ void DispatcherFrame::checkAutoRelease() {
#if 0
    if ((autoReleaseBox != NULL) && (autoReleaseBox->isChecked())) {
        // Auto release of exited sections has been requested - because of possible noise in block detection
        //    hardware, allocated sections are automatically released in the order they were allocated only
        // Only unoccupied sections that have been exited are tested.
        // The next allocated section must be assigned to the same train, and it must have been entered for
        //    the exited Section to be released.
        // Extra allocated sections are not automatically released (allocation number = -1).
         bool foundOne = true;
        while ((allocatedSections.size() > 0) && foundOne) {
            try {
                foundOne = false;
                AllocatedSection as = NULL;
                for (int i = 0; (i < allocatedSections.size()) && !foundOne; i++) {
                    as = allocatedSections.get(i);
                    if (as.getExited() && (as.getSection().getOccupancy() != Section.OCCUPIED)
                            && (as.getAllocationNumber() != -1)) {
                        // possible candidate for deallocation - check order
                        foundOne = true;
                        for (int j = 0; (j < allocatedSections.size()) && foundOne; j++) {
                            if (j != i) {
                                AllocatedSection asx = allocatedSections.get(j);
                                if ((asx.getActiveTrain() == as.getActiveTrain())
                                        && (asx.getAllocationNumber() != -1)
                                        && (asx.getAllocationNumber() < as.getAllocationNumber())) {
                                    foundOne = false;
                                }
                            }
                        }
                        if (foundOne) {
                            // check if the next section is allocated to the same train and has been entered
                            ActiveTrain at = as.getActiveTrain();
                            Section ns = as.getNextSection();
                            AllocatedSection nas = NULL;
                            for (int k = 0; (k < allocatedSections.size()) && (nas == NULL); k++) {
                                if (allocatedSections.get(k).getSection() == ns) {
                                    nas = allocatedSections.get(k);
                                }
                            }
                            if ((nas == NULL) || (at->getStatus() == ActiveTrain::WORKING)
                                    || (at->getStatus() == ActiveTrain::STOPPED)
                                    || (at->getStatus() == ActiveTrain::READY)
                                    || (at->getMode() == ActiveTrain::MANUAL)) {
                                // do not autorelease allocated sections from an Active Train that is
                                //    STOPPED, READY, or WORKING, or is in MANUAL mode.
                                foundOne = false;
                                //But do so if the active train has reached its restart point
                                if (at->reachedRestartPoint()) {
                                    foundOne = true;
                                }
                            } else {
                                if ((nas.getActiveTrain() != as.getActiveTrain()) || (!nas.getEntered())) {
                                    foundOne = false;
                                }
                            }
                            if (foundOne) {
                                // have section to release - delay before release
                                try {
                                    Thread.sleep(500);
                                } catch (InterruptedException e) {
                                    // ignore this exception
                                }
                                // if section is still allocated, release it
                                foundOne = false;
                                for (int m = 0; m < allocatedSections.size(); m++) {
                                    if ((allocatedSections.get(m) == as) && (as.getActiveTrain() == at)) {
                                        foundOne = true;
                                    }
                                }
                                if (foundOne) {
                                    log->debug("{}: releasing {}", at->getTrainName(), as.getSectionName());
                                    releaseAllocatedSection(as, false);
                                }
                            }
                        }
                    }
                }
            } catch (Exception e) {
                log->warn("checkAutoRelease failed  - maybe the AllocatedSection was removed due to a terminating train?? "+e.toString());
                continue;
            }
        }
    }
#endif
}

/**
 * Releases an allocated Section, and removes it from the Dispatcher Input
 * consists of the AllocatedSection object (returned by "allocateSection")
 * and whether this release is from a Terminate Train.
 */
/*public*/ void DispatcherFrame::releaseAllocatedSection(AllocatedSection* as,  bool terminatingTrain) {
#if 1
    // check that section is not occupied if not terminating train
    if (!terminatingTrain && (as->getSection()->getOccupancy() == Section::OCCUPIED)) {
        // warn the manual dispatcher that Allocated Section is occupied
     QVariantList options = QVariantList(); options << tr("ButtonYesX") << tr("ButtonNoX");
        int selectedValue = JOptionPane::showOptionDialog(dispatcherFrame,
                tr("The Allocated Section \"%1\" is OCCUPIED. Do you want to release it? This could cause a collision.").arg(as->getSectionName()), tr("Warning"),
                JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                options,
                tr("ButtonNoX"));
        if (selectedValue == 1) {
            return;   // return without releasing if "No" response
        }
    }
    // release the Allocated Section
    for (int i = allocatedSections->size(); i > 0; i--) {
        if (as == allocatedSections->value(i - 1)) {
            allocatedSections->removeAt(i - 1);
        }
    }
    as->getSection()->setState(Section::FREE);
    as->getActiveTrain()->removeAllocatedSection(as);
    as->dispose();
    if (allocatedSectionTableModel != NULL) {
        allocatedSectionTableModel->fireTableDataChanged();
    }
    allocationRequestTableModel->fireTableDataChanged();
    activeTrainsTableModel->fireTableDataChanged();
    if (_AutoAllocate) {
        autoAllocate->scanAllocationRequestList(allocationRequests);
    }
#endif
}

/**
 * Updates display when occupancy of an allocated section changes Also
 * drives auto release if it is selected
 */
/*public*/ void DispatcherFrame::sectionOccupancyChanged() {
    checkAutoRelease();
    if (allocatedSectionTableModel != NULL) {
        allocatedSectionTableModel->fireTableDataChanged();
    }
    allocationRequestTableModel->fireTableDataChanged();
}

/**
 * Handle activity that is triggered by the fast clock
 */
/*protected*/ void DispatcherFrame::newFastClockMinute() {
    for (int i = delayedTrains->size() - 1; i >= 0; i--) {
        ActiveTrain* at = delayedTrains->at(i);
        // check if this Active Train is waiting to start
        if ((!at->getStarted()) && at->getDelayedStart() != ActiveTrain::NODELAY) {
            // is it time to start?
            if (at->getDelayedStart() == ActiveTrain::TIMEDDELAY) {
                if (isFastClockTimeGE(at->getDepartureTimeHr(), at->getDepartureTimeMin())) {
                    // allow this train to start
                    at->setStarted();
                    delayedTrains->removeAt(i);
                    if (_AutoAllocate) {
                        autoAllocate->scanAllocationRequestList(allocationRequests);
                    }
                }
            }
        } else if (at->getStarted() && at->getStatus() == ActiveTrain::READY && at->reachedRestartPoint()) {
            if (isFastClockTimeGE(at->getRestartDepartHr(), at->getRestartDepartMin())) {
                at->restart();
                delayedTrains->removeAt(i);
                if (_AutoAllocate) {
                    autoAllocate->scanAllocationRequestList(allocationRequests);
                }
            }
        }
    }
}

/**
 * This method tests time assuming both times are on the same day (ignoring
 * midnight) It also sets nowMinutes and nowHours to the latest fast clock
 * values
 */
//@SuppressWarnings("deprecation")
/*protected*/  bool DispatcherFrame::isFastClockTimeGE(int hr, int min) {
    QDateTime now = fastClock->getTime();
    nowHours = now.time().hour();
    nowMinutes = now.time().minute();
    if (((nowHours * 60) + nowMinutes) >= ((hr * 60) + min)) {
        return true;
    }
    return false;
}

// option access methods
/*protected*/ LayoutEditor* DispatcherFrame::getLayoutEditor() {
    return _LE;
}

/*protected*/ void DispatcherFrame::setLayoutEditor(LayoutEditor* editor) {
    _LE = editor;
}

/*protected*/  bool DispatcherFrame::getUseConnectivity() {
    return _UseConnectivity;
}

/*protected*/ void DispatcherFrame::setUseConnectivity( bool set) {
    _UseConnectivity = set;
}

/*protected*/ void DispatcherFrame::setSignalType(int type) {
    _SignalType = type;
}

/*protected*/ int DispatcherFrame::getSignalType() {
    return _SignalType;
}

/*protected*/ void DispatcherFrame::setStoppingSpeedName(QString speedName) {
    _StoppingSpeedName = speedName;
}

/*protected*/ QString DispatcherFrame::getStoppingSpeedName() {
    return _StoppingSpeedName;
}

/*protected*/  bool DispatcherFrame::getTrainsFromRoster() {
    return _TrainsFromRoster;
}

/*protected*/ void DispatcherFrame::setTrainsFromRoster( bool set) {
    _TrainsFromRoster = set;
}

/*protected*/  bool DispatcherFrame::getTrainsFromTrains() {
    return _TrainsFromTrains;
}

/*protected*/ void DispatcherFrame::setTrainsFromTrains( bool set) {
    _TrainsFromTrains = set;
}

/*protected*/  bool DispatcherFrame::getTrainsFromUser() {
    return _TrainsFromUser;
}

/*protected*/ void DispatcherFrame::setTrainsFromUser( bool set) {
    _TrainsFromUser = set;
}

/*protected*/  bool DispatcherFrame::getAutoAllocate() {
    return _AutoAllocate;
}

/*protected*/ void DispatcherFrame::stopStartAutoAllocateRelease() {
    if (_AutoAllocate || _AutoRelease) {
        if (_LE != nullptr) {
            if (autoAllocate == nullptr) {
                autoAllocate = new AutoAllocate(this, allocationRequests);
                autoAllocateThread = ThreadingUtil::newThread(autoAllocate, "Auto Allocator ");
                autoAllocateThread->start();
            }
        } else {
            JOptionPane::showMessageDialog(dispatcherFrame, tr("was specified in the Dispatcher Options."),
                    tr("Message"), JOptionPane::INFORMATION_MESSAGE);
            _AutoAllocate = false;
            if (autoAllocateBox != nullptr) {
                autoAllocateBox->setChecked(_AutoAllocate);
            }
            return;
        }
    } else {
        //no need for autoallocateRelease
        if (autoAllocate != nullptr) {
            autoAllocate->setAbort();
            autoAllocate = nullptr;
        }
    }

}

/*protected*/ void DispatcherFrame::setAutoAllocate( bool set) {
     _AutoAllocate = set;
     stopStartAutoAllocateRelease();
     if (autoAllocateBox != nullptr) {
         autoAllocateBox->setChecked(_AutoAllocate);
     }
}

/*protected*/  bool DispatcherFrame::getAutoTurnouts() {
    return _AutoTurnouts;
}
/*protected*/ void DispatcherFrame::setAutoTurnouts( bool set) {
    _AutoTurnouts = set;
}

/*protected*/  bool DispatcherFrame::getTrustKnownTurnouts() {
    return _TrustKnownTurnouts;
}
/*protected*/ void DispatcherFrame::setTrustKnownTurnouts( bool set) {
    _TrustKnownTurnouts = set;
}

/*protected*/ int DispatcherFrame::getMinThrottleInterval() {
    return _MinThrottleInterval;
}
/*protected*/ void DispatcherFrame::setMinThrottleInterval(int set) {
    _MinThrottleInterval = set;
}

/*protected*/ int DispatcherFrame::getFullRampTime() {
    return _FullRampTime;
}
/*protected*/ void DispatcherFrame::setFullRampTime(int set) {
    _FullRampTime = set;
}

/*protected*/  bool DispatcherFrame::getHasOccupancyDetection() {
    return _HasOccupancyDetection;
}
/*protected*/ void DispatcherFrame::setHasOccupancyDetection( bool set) {
    _HasOccupancyDetection = set;
}

/*protected*/  bool DispatcherFrame::getUseScaleMeters() {
    return _UseScaleMeters;
}
/*protected*/ void DispatcherFrame::setUseScaleMeters( bool set) {
    _UseScaleMeters = set;
}

/*protected*/  bool DispatcherFrame::getShortActiveTrainNames() {
    return _ShortActiveTrainNames;
}
/*protected*/ void DispatcherFrame::setShortActiveTrainNames( bool set) {
    _ShortActiveTrainNames = set;
    if (allocatedSectionTableModel != NULL) {
        allocatedSectionTableModel->fireTableDataChanged();
    }
    if (allocationRequestTableModel != NULL) {
        allocationRequestTableModel->fireTableDataChanged();
    }
}

/*protected*/  bool DispatcherFrame::getShortNameInBlock() {
    return _ShortNameInBlock;
}
/*protected*/ void DispatcherFrame::setShortNameInBlock( bool set) {
    _ShortNameInBlock = set;
}

/*protected*/  bool DispatcherFrame::getRosterEntryInBlock() {
    return _RosterEntryInBlock;
}
/*protected*/ void DispatcherFrame::setRosterEntryInBlock( bool set) {
    _RosterEntryInBlock = set;
}

/*protected*/  bool DispatcherFrame::getExtraColorForAllocated() {
    return _ExtraColorForAllocated;
}
/*protected*/ void DispatcherFrame::setExtraColorForAllocated( bool set) {
    _ExtraColorForAllocated = set;
}

/*protected*/  bool DispatcherFrame::getNameInAllocatedBlock() {
    return _NameInAllocatedBlock;
}
/*protected*/ void DispatcherFrame::setNameInAllocatedBlock( bool set) {
    _NameInAllocatedBlock = set;
}

/*protected*/ Scale* DispatcherFrame::getScale() {
    return _LayoutScale;
}
/*protected*/ void DispatcherFrame::setScale(Scale* sc) {
    _LayoutScale = sc;
}
#if 1
/*public*/ QList<ActiveTrain*>* DispatcherFrame::getActiveTrainsList() {
    return activeTrainsList;
}
/*protected*/ QList<AllocatedSection*>* DispatcherFrame::getAllocatedSectionsList() {
    return allocatedSections;
}

/*public*/ ActiveTrain* DispatcherFrame::getActiveTrainForRoster(RosterEntry* re) {
    if (!_TrainsFromRoster) {
        return NULL;
    }
    for (ActiveTrain* at : *activeTrainsList) {
        if (at->getRosterEntry()  == (re)) {
            return at;
        }
    }
    return NULL;

}
#endif
/*protected*/  bool DispatcherFrame::getSupportVSDecoder() {
    return _SupportVSDecoder;
}
/*protected*/ void DispatcherFrame::setSupportVSDecoder( bool set) {
    _SupportVSDecoder = set;
}

// called by ActivateTrainFrame after a new train is all set up
//      Dispatcher side of activating a new train should be completed here
// Jay Janzen protection changed to /*public*/ for access via scripting
/*public*/ void DispatcherFrame::newTrainDone(ActiveTrain* at) {
    if (at != NULL) {
        // a new active train was created, check for delayed start
        if (at->getDelayedStart() != ActiveTrain::NODELAY && (!at->getStarted())) {
            delayedTrains->append(at);
            fastClockWarn(true);
        }
// djd needs work here
        // check for delayed restart
        else if (at->getDelayedRestart() == ActiveTrain::TIMEDDELAY) {
            fastClockWarn(false);
        }
    }
    newTrainActive = false;
}

/*protected*/ void DispatcherFrame::removeDelayedTrain(ActiveTrain* at) {
    delayedTrains->removeOne(at);
}

/*private*/ void DispatcherFrame::fastClockWarn( bool wMess) {
    if (fastClockSensor->getState() == Sensor::ACTIVE) {
        return;
    }
    // warn that the fast clock is not running
    QString mess = "";
    if (wMess) {
        mess = tr("At least one Active Train is waiting \non the fast clock, but it is not running. \n Do you want to start the fast clock?");
    }
    else {
        mess = tr("At least one Active Train needs the \nfast clock for restart, but it is not running. \nDo you want to start the fast clock?");
    }
//    int selectedValue = JOptionPane.showOptionDialog(dispatcherFrame,
//            mess, Bundle.getMessage("WarningTitle"),
//            JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, NULL,
//            new Object[]{tr("ButtonYesStart"), tr("ButtonNo")},
//            tr("ButtonNo"));
//    if (selectedValue == 0) {
    int selectedValue = QMessageBox::question(dispatcherFrame, tr("Warning"), mess, QMessageBox::Yes | QMessageBox::No);
    if(selectedValue == QMessageBox::Yes)
    {
        try {
            fastClockSensor->setState(Sensor::ACTIVE);
        } catch (JmriException reason) {
            log->error("Exception when setting fast clock sensor");
        }
    }
}

// Jay Janzen
// Protection changed to /*public*/ to allow access via scripting
/*public*/ AutoTrainsFrame* DispatcherFrame::getAutoTrainsFrame() {
    return _autoTrainsFrame;
}

/*static*/ DispatcherFrame* DispatcherFrame::_instance = NULL;

/*static*/ /*public*/ DispatcherFrame* DispatcherFrame::instance() {
    if (_instance == NULL) {
        _instance = new DispatcherFrame();
        InstanceManager::store(_instance, "DispatcherFrame");
    }
    return (_instance);
}

/**
 * Table model for Active Trains Table in Dispatcher window
 */

    /*public*/ ActiveTrainsTableModel::ActiveTrainsTableModel(DispatcherFrame* frame) {
        //super();
 this->frame = frame;
    }

   // @Override
    /*public*/ void ActiveTrainsTableModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()  == ("length")) {
            fireTableDataChanged();
        }
    }

//    @Override
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == ALLOCATEBUTTON_COLUMN) {
//            return JButton.class;
//        }
//        return String.class;
//    }


   /*public*/ int ActiveTrainsTableModel::columnCount(const QModelIndex &/*parent*/) const
   {
            return ALLOCATEBUTTON_COLUMN + 1;
   }

    //@Override
    /*public*/ int ActiveTrainsTableModel::rowCount(const QModelIndex &/*parent*/) const {
        return (frame->activeTrainsList->size());
    }

    //@Override
    /*public*/ Qt::ItemFlags ActiveTrainsTableModel::flags(const QModelIndex &index) const
    {
        if (index.column() == ALLOCATEBUTTON_COLUMN) {
            return (Qt::ItemIsEnabled | Qt::ItemIsEditable);
        }
        return (Qt::ItemIsEnabled);
    }

    //@Override
    /*public*/ QVariant ActiveTrainsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section)
        {
            case TRANSIT_COLUMN:
                return tr("Transit");
            case TRAIN_COLUMN:
                return tr("Train");
            case TYPE_COLUMN:
                return tr("Train Type");
            case STATUS_COLUMN:
                return tr("Train Status");
            case MODE_COLUMN:
                return tr("Train Mode");
            case ALLOCATED_COLUMN:
                return tr("Allocated Sectione");
            case NEXTSECTION_COLUMN:
                return tr("Next Section");
            case ALLOCATEBUTTON_COLUMN:
                return (" "); // button columns have no names
            default:
                return "";
        }
     }
     return QVariant();
    }

    /*public*/ int ActiveTrainsTableModel::getPreferredWidth(int col) {
        switch (col) {
            case TRANSIT_COLUMN:
                return  JTextField(17).sizeHint().width();
            case TRAIN_COLUMN:
                return  JTextField(17).sizeHint().width();
            case TYPE_COLUMN:
                return  JTextField(16).sizeHint().width();
            case STATUS_COLUMN:
                return  JTextField(8).sizeHint().width();
            case MODE_COLUMN:
                return  JTextField(11).sizeHint().width();
            case ALLOCATED_COLUMN:
                return  JTextField(17).sizeHint().width();
            case NEXTSECTION_COLUMN:
                return  JTextField(17).sizeHint().width();
            case ALLOCATEBUTTON_COLUMN:
                return  JTextField(12).sizeHint().width();
        }
        return  JTextField(5).sizeHint().width();
    }

    //@Override
    /*public*/ QVariant ActiveTrainsTableModel::data(const QModelIndex &index, int role) const
    {
 if(role == Qt::DisplayRole)
 {
        int rx = index.row();
        if (rx >= frame->activeTrainsList->size()) {
            return QVariant();
        }
        ActiveTrain* at = frame->activeTrainsList->at(rx);
        switch (index.column()) {
            case TRANSIT_COLUMN:
                return (at->getTransitName());
            case TRAIN_COLUMN:
                return (at->getTrainName());
            case TYPE_COLUMN:
                return (at->getTrainTypeText());
            case STATUS_COLUMN:
                return (at->getStatusText());
            case MODE_COLUMN:
                return (at->getModeText());
            case ALLOCATED_COLUMN:
                return (at->getLastAllocatedSectionName());
            case NEXTSECTION_COLUMN:
                return (at->getNextSectionToAllocateName());
            case ALLOCATEBUTTON_COLUMN:
                return tr("Allocate Next");
            default:
                return (" ");
        }
     }
     return QVariant();
    }

    //@Override
    /*public*/ bool ActiveTrainsTableModel::setData(const QModelIndex &index, const QVariant &/*value*/, int role)
    {
     if(role == Qt::EditRole)
     {
      int col = index.column();
        if (col == ALLOCATEBUTTON_COLUMN) {
            // open an allocate window
            frame->allocateNextRequested(index.row());
            return true;
        }
    }
     return false;
   }

/**
 * Table model for Allocation Request Table in Dispatcher window
 */
///*public*/ class AllocationRequestTableModel extends javax.swing.table.AbstractTableModel implements
//        PropertyChangeListener {

//    /*public*/ static final int ACTIVE_COLUMN = 0;
//    /*public*/ static final int PRIORITY_COLUMN = 1;
//    /*public*/ static final int TRAINTYPE_COLUMN = 2;
//    /*public*/ static final int SECTION_COLUMN = 3;
//    /*public*/ static final int STATUS_COLUMN = 4;
//    /*public*/ static final int OCCUPANCY_COLUMN = 5;
//    /*public*/ static final int SECTIONLENGTH_COLUMN = 6;
//    /*public*/ static final int ALLOCATEBUTTON_COLUMN = 7;
//    /*public*/ static final int CANCELBUTTON_COLUMN = 8;

    /*public*/ AllocationRequestTableModel::AllocationRequestTableModel(DispatcherFrame* frame) {
        //super();
 this->frame = frame;
    }

    //@Override
    /*public*/ void AllocationRequestTableModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()  == ("length")) {
            fireTableDataChanged();
        }
    }

//    @Override
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == CANCELBUTTON_COLUMN) {
//            return JButton.class;
//        }
//        if (c == ALLOCATEBUTTON_COLUMN) {
//            return JButton.class;
//        }
//        return String.class;
//    }

    //@Override
    /*public*/ int AllocationRequestTableModel::columnCount(const QModelIndex &/*parent*/) const
    {
        return CANCELBUTTON_COLUMN + 1;
    }

   // @Override
    /*public*/ int AllocationRequestTableModel::rowCount(const QModelIndex &/*parent*/) const
    {
        return (frame->allocationRequests->size());
    }

    //@Override
    /*public*/ Qt::ItemFlags AllocationRequestTableModel::flags(const QModelIndex &index) const
    {
     int c = index.column();
        if (c == CANCELBUTTON_COLUMN) {
            return (Qt::ItemIsEnabled | Qt::ItemIsEditable);
        }
        if (c == ALLOCATEBUTTON_COLUMN) {
            return (Qt::ItemIsEnabled);
        }
        return 0;
    }

    //@Override
    /*public*/ QVariant AllocationRequestTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section) {
            case ACTIVE_COLUMN:
                return tr("Active");
            case PRIORITY_COLUMN:
                return tr("Priority");
            case TRAINTYPE_COLUMN:
                return tr("Train Type");
            case SECTION_COLUMN:
                return tr("Section");
            case STATUS_COLUMN:
                return tr("Status");
            case OCCUPANCY_COLUMN:
                return tr("Occupancy");
            case SECTIONLENGTH_COLUMN:
                return tr("Section Length");
            case ALLOCATEBUTTON_COLUMN:
                return (" "); // button columns have no names
            case CANCELBUTTON_COLUMN:
                return (" "); // button columns have no names
            default:
                return "";
        }
     }
     return QVariant();
    }

    /*public*/ int AllocationRequestTableModel::getPreferredWidth(int col) {
        switch (col) {
            case ACTIVE_COLUMN:
                return  JTextField(30).sizeHint().width();
            case PRIORITY_COLUMN:
                return  JTextField(8).sizeHint().width();
            case TRAINTYPE_COLUMN:
                return  JTextField(15).sizeHint().width();
            case SECTION_COLUMN:
                return  JTextField(25).sizeHint().width();
            case STATUS_COLUMN:
                return  JTextField(15).sizeHint().width();
            case OCCUPANCY_COLUMN:
                return  JTextField(10).sizeHint().width();
            case SECTIONLENGTH_COLUMN:
                return  JTextField(8).sizeHint().width();
            case ALLOCATEBUTTON_COLUMN:
                return  JTextField(12).sizeHint().width();
            case CANCELBUTTON_COLUMN:
                return  JTextField(10).sizeHint().width();
        }
        return  JTextField(5).sizeHint().width();
    }

    //@Override
    /*public*/ QVariant AllocationRequestTableModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
        int rx = index.row();
        if (rx >= frame->allocationRequests->size()) {
            return QVariant();
        }
        AllocationRequest* ar = frame->allocationRequests->at(rx);
        switch (index.column()) {
            case ACTIVE_COLUMN:
                if (frame->_ShortActiveTrainNames) {
                    return (ar->getActiveTrain()->getTrainName());
                }
                return ( ar->getActiveTrainName());
            case PRIORITY_COLUMN:
                return ("   " +  ar->getActiveTrain()->getPriority());
            case TRAINTYPE_COLUMN:
                return ( ar->getActiveTrain()->getTrainTypeText());
            case SECTION_COLUMN:
                return ( ar->getSectionName());
            case STATUS_COLUMN:
                if ( ar->getSection()->getState() == Section::FREE) {
                    return tr("FREE");
                }
                return tr("ALLOCATED");
            case OCCUPANCY_COLUMN:
                if (!frame->_HasOccupancyDetection) {
                    return tr("UNKNOWN");
                }
                if ( ar->getSection()->getOccupancy() == Section::OCCUPIED) {
                    return tr("OCCUPIED");
                }
                return tr("UNOCCUPIED");
            case SECTIONLENGTH_COLUMN:
                return ("  " + ar->getSection()->getLengthI(frame->_UseScaleMeters, frame->_LayoutScale));
            case ALLOCATEBUTTON_COLUMN:
                return tr("Allocate");
            case CANCELBUTTON_COLUMN:
                return tr("Cancel");
            default:
                return (" ");
        }
     }
     return QVariant();
    }

    //@Override
    /*public*/ bool AllocationRequestTableModel::setData(const QModelIndex &index, const QVariant &/*value*/, int role)
    {
     if(role == Qt::EditRole)
     {
 int col = index.column();
 int row = index.row();
        if (col == ALLOCATEBUTTON_COLUMN) {
            // open an allocate window
            frame->allocateRequested(row);
            return true;
        }
        if (col == CANCELBUTTON_COLUMN) {
            // open an allocate window
            frame->cancelAllocationRequest(row);
            return true;
        }
     }
     return false;
    }
//}

/**
 * Table model for Allocated Section Table
 */
///*public*/ class AllocatedSectionTableModel extends javax.swing.table.AbstractTableModel implements
//        PropertyChangeListener {

//    /*public*/ static final int ACTIVE_COLUMN = 0;
//    /*public*/ static final int SECTION_COLUMN = 1;
//    /*public*/ static final int OCCUPANCY_COLUMN = 2;
//    /*public*/ static final int USESTATUS_COLUMN = 3;

//    /*public*/ static final int RELEASEBUTTON_COLUMN = 4;

    /*public*/ AllocatedSectionTableModel::AllocatedSectionTableModel(DispatcherFrame* frame) {
        //super();
                      this->frame = frame;
    }

    //@Override
    /*public*/ void AllocatedSectionTableModel::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()  == ("length")) {
            fireTableDataChanged();
        }
    }

    //@Override
//    /*public*/ Class<?> getColumnClass(int c) {
//        if (c == RELEASEBUTTON_COLUMN) {
//            return JButton.class;
//        }
//        return String.class;
//    }

    //@Override
    /*public*/ int AllocatedSectionTableModel::columnCount(const QModelIndex &/*parent*/) const
    {
        return RELEASEBUTTON_COLUMN + 1;
    }

    //@Override
    /*public*/ int AllocatedSectionTableModel::rowCount(const QModelIndex &/*parent*/) const
    {
        return (frame->allocatedSections->size());
    }

    //@Override
    /*public*/ Qt::ItemFlags AllocatedSectionTableModel::flags(const QModelIndex &index) const
    {
        if (index.column() == RELEASEBUTTON_COLUMN) {
            return (Qt::ItemIsEnabled | Qt::ItemIsEditable);
        }
        return (Qt::ItemIsEnabled);
    }

    //@Override
    /*public*/ QVariant AllocatedSectionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        switch (section) {
            case ACTIVE_COLUMN:
                return tr("Active");
            case SECTION_COLUMN:
                return tr("Allocated Section");
            case OCCUPANCY_COLUMN:
                return tr("Occupancy");
            case USESTATUS_COLUMN:
                return tr("Use Status");
            case RELEASEBUTTON_COLUMN:
                return (" "); // button columns have no names
            default:
                return "";
        }
     }
     return QVariant();
    }

    /*public*/ int AllocatedSectionTableModel::getPreferredWidth(int col) {
        switch (col) {
            case ACTIVE_COLUMN:
                return  JTextField(30).sizeHint().width();
            case SECTION_COLUMN:
                return  JTextField(25).sizeHint().width();
            case OCCUPANCY_COLUMN:
                return  JTextField(10).sizeHint().width();
            case USESTATUS_COLUMN:
                return  JTextField(15).sizeHint().width();
            case RELEASEBUTTON_COLUMN:
                return  JTextField(12).sizeHint().width();
        }
        return  JTextField(5).sizeHint().width();
    }

    //@Override
    /*public*/ QVariant AllocatedSectionTableModel::data(const QModelIndex &index, int role) const
    {
     if(role == Qt::DisplayRole)
     {
        int rx = index.row();
        if (rx >= frame->allocatedSections->size()) {
            return QVariant();
        }
        AllocatedSection* as = frame->allocatedSections->at(rx);
        switch (index.column()) {
            case ACTIVE_COLUMN:
                if (frame->_ShortActiveTrainNames) {
                    return (as->getActiveTrain()->getTrainName());
                }
                return (as->getActiveTrainName());
            case SECTION_COLUMN:
                return (as->getSectionName());
            case OCCUPANCY_COLUMN:
                if (!frame->_HasOccupancyDetection) {
                    return tr("UNKNOWN");
                }
                if (as->getSection()->getOccupancy() == Section::OCCUPIED) {
                    return tr("OCCUPIED");
                }
                return tr("UNOCCUPIED");
            case USESTATUS_COLUMN:
                if (!as->getEntered()) {
                    return tr("Not Entered");
                }
                if (as->getExited()) {
                    return tr("Exited");
                }
                return tr("Entered");
            case RELEASEBUTTON_COLUMN:
                return tr("Release");
            default:
                return (" ");
        }
     }
     return QVariant();
    }

    //@Override
    /*public*/ bool AllocatedSectionTableModel::setData(const QModelIndex &index, const QVariant &/*value*/, int role)
    {
     if(role == Qt::EditRole)
     {
        if (index.column() == RELEASEBUTTON_COLUMN) {
            frame->releaseAllocatedSectionFromTable(index.row());
            return true;
        }
     }
     return false;
    }
//}
    /*public*/ QString DispatcherFrame::getClassName()
    {
     return "jmri.jmrit.dispatcher.DispatcherFrame";
    }

