#include "optionsmenu.h"
#include "dispatcherframe.h"
#include "loggerfactory.h"
#include "layouteditor.h"
#include "jseparator.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
#include <QComboBox>
#include "joptionpane.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include "optionsfile.h"
#include "panelmenu.h"
#include "scalemanager.h"

/**
 * Sets up and processes items in the Dispatcher Options menu.
 *
 * @author Dave Duchamp Copyright (C) 2008
 */
///*public*/ class OptionsMenu extends JMenu {

/*public*/ OptionsMenu::OptionsMenu(DispatcherFrame* f, QWidget*parent) : QMenu(parent){
    useConnectivityCheckBox = new QCheckBox(tr("UseConnectivity"));
    layoutEditorBox = new QComboBox();
    layoutEditorList = new QList<LayoutEditor*>();
    autoAllocateCheckBox = new QCheckBox(tr("AutoAllocateBox"));
    autoTurnoutsCheckBox = new QCheckBox(tr("AutoTurnoutsBox"));
    trainsFromRoster = new QRadioButton(tr("TrainsFromRoster"));
    trainsFromTrains = new QRadioButton(tr("TrainsFromTrains"));
    trainsFromUser = new QRadioButton(tr("TrainsFromUser"));
    detectionCheckBox = new QCheckBox(tr("DetectionBox"));
    shortNameCheckBox = new QCheckBox(tr("ShortNameBox"));
    nameInBlockCheckBox = new QCheckBox(tr("NameInBlockBox"));
    rosterInBlockCheckBox = new QCheckBox(tr("RosterInBlockBox"));
    extraColorForAllocatedCheckBox = new QCheckBox(tr("ExtraColorForAllocatedBox"));
    nameInAllocatedBlockCheckBox = new QCheckBox(tr("NameInAllocatedBlockBox"));
    supportVSDecoderCheckBox = new QCheckBox(tr("SupportVSDecoder"));
    layoutScaleBox = new QComboBox();
    scaleFeet = new QRadioButton(tr("ScaleFeet"));
    scaleMeters = new QRadioButton(tr("ScaleMeters"));
    openDispatcherWithPanel = new QCheckBox(tr("OpenDispatcherWithPanelBox"));
    minThrottleIntervalSpinner = new QSpinBox(); //new SpinnerNumberModel(100, 20, 1000, 1));
    minThrottleIntervalSpinner->setValue(100);
    minThrottleIntervalSpinner->setMinimum(20);
    minThrottleIntervalSpinner->setMaximum(1000);
    minThrottleIntervalSpinner->setSingleStep(1);
    fullRampTimeSpinner = new QSpinBox(/*new SpinnerNumberModel(5000, 1000, 20000, 1)*/);
    fullRampTimeSpinner->setValue(5000);
    fullRampTimeSpinner->setMinimum(1000);
    fullRampTimeSpinner->setMaximum(20000);
    fullRampTimeSpinner->setSingleStep(1);
    trustKnownTurnoutsCheckBox = new QCheckBox(tr("trustKnownTurnouts"));

    signalTypes = QStringList() <<tr("Signal Heads/SSL")<< tr("Signal Masts/SML");

    dispatcher = f;
    this->setTitle(tr("Options"));
    autoDispatchItem = new QAction(tr("Auto Dispatch"),this);
    autoDispatchItem->setCheckable(true);
    this->addAction(autoDispatchItem);
//    autoDispatchItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            handleAutoDispatch(event);
//        }
//    });
    connect(autoDispatchItem, SIGNAL(triggered()),this, SLOT(handleAutoDispatch()));
    autoTurnoutsItem = new QAction(tr("Auto Set Turnouts"),this);
    autoTurnoutsItem->setCheckable(true);
    this->addAction(autoTurnoutsItem);
//    autoTurnoutsItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            handleAutoTurnouts(event);
//        }
//    });
    connect(autoTurnoutsItem, SIGNAL(triggered()), this, SLOT(handleAutoTurnouts()));
    QAction* optionWindowItem = new QAction(tr("Dispatcher Options") + "...",this);
    this->addAction(optionWindowItem);
//    optionWindowItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            optionWindowRequested(event);
//        }
//    });
    connect(optionWindowItem, SIGNAL(triggered()), this, SLOT(optionWindowRequested()));
    QAction *saveOptionsItem = new QAction(tr("Save Options"),this);
    this->addAction(saveOptionsItem);
//    saveOptionsItem.addActionListener(new ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent event) {
//            saveRequested(event);
//        }
//    });
    connect(saveOptionsItem, SIGNAL(triggered()), this, SLOT(saveRequested()));
    initializeMenu();
}

// Initialize check box items in menu from Dispatcher
/*public*/ void OptionsMenu::initializeMenu() {
    autoDispatchItem->setChecked(dispatcher->getAutoAllocate());
    autoTurnoutsItem->setChecked(dispatcher->getAutoTurnouts());
}

/*private*/ void OptionsMenu::handleAutoDispatch() {
    bool set = autoDispatchItem->isChecked();
    dispatcher->setAutoAllocate(set);
}

/*private*/ void OptionsMenu::handleAutoTurnouts() {
    bool set = autoTurnoutsItem->isChecked();
    dispatcher->setAutoTurnouts(set);
}

/*private*/ void OptionsMenu::optionWindowRequested() {
    if (optionsFrame == nullptr) {
        optionsFrame = new JmriJFrameX(tr("Dispatcher Options"), false, true);
        optionsFrame->addHelpMenu("package.jmri.jmrit.dispatcher->Options", true);
        optionsPane = optionsFrame->getContentPane();
        QVBoxLayout* optionsPaneLayout;
        optionsPane->setLayout(optionsPaneLayout = new QVBoxLayout());//optionsFrame.getContentPane(), BoxLayout.Y_AXIS));
        QWidget* p1 = new QWidget();
        FlowLayout* p1Layout;
        p1->setLayout(p1Layout = new FlowLayout());
        p1Layout->addWidget(useConnectivityCheckBox);
        useConnectivityCheckBox->setToolTip(tr("Select to use the connectivity from the selected Layout Editor panel."));
        p1Layout->addWidget(layoutEditorBox);
        layoutEditorBox->setToolTip(tr("Select Layout Editor panel with best connectivity, if there are more than one."));
        signalTypeBox = new QComboBox(/*signalTypes*/);
        signalTypeBox->addItems(signalTypes);
        p1Layout->addWidget(signalTypeBox);
        signalTypeBox->setToolTip(tr("Select the type of signaling used on the panel and which Dispatcher will follow."));
        optionsPane->layout()->addWidget(p1);
        QWidget* p2 = new QWidget();
        FlowLayout* p2Layout;
        p2->setLayout(p2Layout = new FlowLayout());
        QButtonGroup* trainsGroup = new QButtonGroup();
        QSignalMapper* trainsMapper = new QSignalMapper();
        p2Layout->addWidget(trainsFromRoster);
        trainsFromRoster->setToolTip(tr("Select for Trains to be selected from the JMRI Roster."));
        trainsGroup->addButton(trainsFromRoster);
        trainsMapper->setMapping(trainsFromRoster,trainsFromRoster);

//        ActionListener useRosterEntryListener = new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (trainsFromRoster->isChecked()) {
//                    rosterInBlockCheckBox.setEnabled(true);
//                    if (nameInBlockCheckBox->isChecked() && e.getSource() == nameInBlockCheckBox) {
//                        rosterInBlockCheckBox->setChecked(false);
//                    } else if (rosterInBlockCheckBox->isChecked() && e.getSource() == rosterInBlockCheckBox) {
//                        nameInBlockCheckBox->setChecked(false);
//                    }
//                } else {
//                    rosterInBlockCheckBox.setEnabled(false);
//                }
//            }
//        };
//        trainsFromRoster.addActionListener(useRosterEntryListener);
        connect(trainsFromRoster, SIGNAL(clicked(bool)), trainsMapper, SLOT(map(QObject*)));
        connect(trainsMapper, SIGNAL(mapped(QObject*)), this, SLOT(useRosterEntry_actionPerformed(QObject*)));
        p2Layout->addWidget(new JLabel("     "));
        p2Layout->addWidget(trainsFromTrains);
        trainsFromTrains->setToolTip(tr("Select for Trains to be selected from JMRI trains in Operations."));
        //trainsFromTrainstrainsFromTrains.addActionListener(useRosterEntryListener);
        connect(trainsFromRoster, SIGNAL(clicked(bool)), this, SLOT(useRosterEntry_actionPerformed(JActionEvent*)));
        trainsGroup->addButton(trainsFromTrains);
        p2Layout->addWidget(new JLabel("     "));
        p2Layout->addWidget(trainsFromUser);
        trainsFromUser->setToolTip(tr("Select for Trains information to be entered by the user at creation time."));
        //trainsFromUser.addActionListener(useRosterEntryListener);
        connect(trainsFromUser, SIGNAL(clicked(bool)), this, SLOT(useRosterEntry_actionPerformed(JActionEvent*)));
        trainsGroup->addButton(trainsFromUser);
        optionsPane->layout()->addWidget(p2);
        QWidget* p3 = new QWidget();
        FlowLayout* p3Layout;
        p3->setLayout(p3Layout = new FlowLayout());
        p3Layout->addWidget(detectionCheckBox);
        detectionCheckBox->setToolTip(tr("Select if layout has hardware block occupancy detection for all Blocks in Sections."));
        optionsPane->layout()->addWidget(p3);
        QWidget* p4 = new QWidget();
        FlowLayout* p4Layout;
        p4->setLayout(p4Layout = new FlowLayout());
        p4Layout->addWidget(autoAllocateCheckBox);
        autoAllocateCheckBox->setToolTip(tr("<html>Select if computer is to automatically allocate requested Sections.<br>Uncheck for manual allocation.</html>"));
        optionsPane->layout()->addWidget(p4);
        QWidget* p5 = new QWidget();
        FlowLayout* p5Layout;
        p5->setLayout(p5Layout = new FlowLayout());
        p5Layout->addWidget(autoTurnoutsCheckBox);
        autoTurnoutsCheckBox->setToolTip(tr("Select if computer is to automatically set turnouts when a Section is allocated. Uncheck for manual setting."));
        optionsPane->layout()->addWidget(p5);
        QWidget* p16 = new QWidget();
        FlowLayout* p16Layout;
        p16->setLayout(p16Layout = new FlowLayout());
        p16Layout->addWidget(trustKnownTurnoutsCheckBox);
        trustKnownTurnoutsCheckBox->setToolTip(tr("Trust the current known state of turnouts, and do not repeat command."));
        optionsPane->layout()->addWidget(p16);
        QWidget* p6 = new QWidget();
        FlowLayout* p6Layout;
        p6->setLayout(p6Layout = new FlowLayout());
        p6Layout->addWidget(shortNameCheckBox);
        shortNameCheckBox->setToolTip(tr("<html>Select to use only the Train name as the Active Train name in tables and selection boxes.<br>If unchecked, will also show Train's current Transit User Name.</html>"));
        optionsPane->layout()->addWidget(p6);
        QWidget* p7 = new QWidget();
        FlowLayout* p7Layout;
        p7->setLayout(p7Layout = new FlowLayout());
        p7Layout->addWidget(nameInBlockCheckBox);
        nameInBlockCheckBox->setToolTip(tr("Select to automatically place the name of new Trains in their starting Block value."));
        //nameInBlockCheckBox.addActionListener(useRosterEntryListener);
        connect(nameInBlockCheckBox, SIGNAL(clicked(bool)), this, SLOT(useRosterEntry_actionPerformed(JActionEvent*)));
        optionsPane->layout()->addWidget(p7);
        QWidget* p7b = new QWidget();
        FlowLayout* p7bLayout;
        p7b->setLayout(p7bLayout = new FlowLayout());
        p7bLayout->addWidget(rosterInBlockCheckBox);
        rosterInBlockCheckBox->setToolTip(tr("Select to automatically place the Roster Entry of new Trains in their starting Block value."));
        //rosterInBlockCheckBox.addActionListener(useRosterEntryListener);
        connect(rosterInBlockCheckBox, SIGNAL(clicked(bool)), this, SLOT(useRosterEntry_actionPerformed(JActionEvent*)));
        optionsPane->layout()->addWidget(p7b);

        QWidget* p10 = new QWidget();
        FlowLayout* p10Layout;
        p10->setLayout(p10Layout = new FlowLayout());
        p10Layout->addWidget(extraColorForAllocatedCheckBox);
        extraColorForAllocatedCheckBox->setToolTip(tr("Select to use alternate color for unoccupied Blocks in allocated Sections."));
        optionsPane->layout()->addWidget(p10);
        QWidget* p11 = new QWidget();
        FlowLayout* p11Layout;
        p11->setLayout(p11Layout = new FlowLayout());
        p11Layout->addWidget(nameInAllocatedBlockCheckBox);
        nameInAllocatedBlockCheckBox->setToolTip(tr("Select to automatically place the Train name in Blocks of allocated Sections."));
        optionsPane->layout()->addWidget(p11);
        QWidget* p13 = new QWidget();
        FlowLayout* p13Layout;
        p13->setLayout(p13Layout = new FlowLayout());
        p13Layout->addWidget(supportVSDecoderCheckBox);
        supportVSDecoderCheckBox->setToolTip(tr("Select this option to use Dispatcher to help position train sounds from Virtual Sound Decoder"));
        optionsPane->layout()->addWidget(p13);
        QWidget* p8 = new QWidget();
        FlowLayout* p8Layout;
        initializeScaleCombo();
        p8Layout->addWidget(new JLabel(tr("LayoutScale") + ":"));
        p8Layout->addWidget(layoutScaleBox);
        layoutScaleBox->setToolTip(tr("ScaleBoxHint"));
        optionsPane->layout()->addWidget(p8);
        QWidget* p12 = new QWidget();
        FlowLayout* p12Layout;
        p12->setLayout(p12Layout = new FlowLayout());
        p12Layout->addWidget(new JLabel(tr("Units") + "  "));
        QButtonGroup* scaleGroup = new QButtonGroup();
        p12Layout->addWidget(scaleFeet);
        scaleFeet->setToolTip(tr("Select to use scale feet for Section and Train length."));
        scaleGroup->addButton(scaleFeet);
        p12Layout->addWidget(new JLabel("  "));
        p12Layout->addWidget(scaleMeters);
        scaleMeters->setToolTip(tr("Select to use scale meters for Section and Train length."));
        scaleGroup->addButton(scaleMeters);
        optionsPane->layout()->addWidget(p12);

        QWidget* p15 = new QWidget();
        FlowLayout* p15Layout;
        p15->setLayout(p15Layout = new FlowLayout());
        p15Layout->addWidget(new JLabel(tr("minThrottleInterval") + ":"));
        minThrottleIntervalSpinner->setToolTip(tr("Minimum interval (in milliseconds) between throttle commands. Choose a value from 20 to 1,000 ms"));
        p15Layout->addWidget(minThrottleIntervalSpinner);
        p15Layout->addWidget(new JLabel(tr("ms")));
        optionsPane->layout()->addWidget(p15);

        QWidget* p17 = new QWidget();
        FlowLayout* p17Layout;
        p17->setLayout(p17Layout = new FlowLayout());
        p17Layout->addWidget(new JLabel(tr("fullRampTime") + " :"));
        fullRampTimeSpinner->setToolTip(tr("Time (in ms) for %1 loco to change from 0% to 100%. Choose a value from 1,000 ms to 20,000 ms.").arg(tr("RAMP_FAST")));
        p17Layout->addWidget(fullRampTimeSpinner);
        p17Layout->addWidget(new JLabel(tr("ms")));
        optionsPane->layout()->addWidget(p17);

        QWidget* p14 = new QWidget();
        FlowLayout* p14Layout;
        p14->setLayout(p14Layout = new FlowLayout());
        p14Layout->addWidget(openDispatcherWithPanel);
        openDispatcherWithPanel->setToolTip(tr("<html>Select to automatically open the Dispatcher window when the Panel is loaded<br>(Panel file will need to be saved)</html>"));
        optionsPane->layout()->addWidget(p14);

        optionsPaneLayout->addWidget(new JSeparator());
        QWidget* p9 = new QWidget();
        FlowLayout* p9Layout;
        p9->setLayout(p9Layout = new FlowLayout());
        QPushButton* cancelButton = nullptr;
        p9Layout->addWidget(cancelButton = new QPushButton(tr("Cancel")));
//        cancelButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                cancelOptions(e);
//            }
//        });
        connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(cancelOptions()));
        cancelButton->setToolTip(tr("Click to cancel without changing any options."));
        p9Layout->addWidget(new JLabel("     "));
        QPushButton* applyButton = nullptr;
        p9Layout->addWidget(applyButton = new QPushButton(tr("Apply")));
//        applyButton.addActionListener(new ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                applyOptions(e);
//            }
//        });
        connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(apply()));
        applyButton->setToolTip(tr("Click to apply above options and close this window."));
        optionsPane->layout()->addWidget(p9);
    }
    if (initializeLayoutEditorCombo()) {
        useConnectivityCheckBox->setVisible(true);
        layoutEditorBox->setVisible(true);
    } else {
        useConnectivityCheckBox->setVisible(false);
        layoutEditorBox->setVisible(false);
    }
    useConnectivityCheckBox->setChecked(dispatcher->getUseConnectivity());
    signalTypeBox->setCurrentIndex(dispatcher->getSignalType());
    trainsFromRoster->setChecked(dispatcher->getTrainsFromRoster());
    trainsFromTrains->setChecked(dispatcher->getTrainsFromTrains());
    trainsFromUser->setChecked(dispatcher->getTrainsFromUser());
    detectionCheckBox->setChecked(dispatcher->getHasOccupancyDetection());
    autoAllocateCheckBox->setChecked(dispatcher->getAutoAllocate());
    autoTurnoutsCheckBox->setChecked(dispatcher->getAutoTurnouts());
    trustKnownTurnoutsCheckBox->setChecked(dispatcher->getTrustKnownTurnouts());
    shortNameCheckBox->setChecked(dispatcher->getShortActiveTrainNames());
    nameInBlockCheckBox->setChecked(dispatcher->getShortNameInBlock());
    rosterInBlockCheckBox->setChecked(dispatcher->getRosterEntryInBlock());
    extraColorForAllocatedCheckBox->setChecked(dispatcher->getExtraColorForAllocated());
    nameInAllocatedBlockCheckBox->setChecked(dispatcher->getNameInAllocatedBlock());
    supportVSDecoderCheckBox->setChecked(dispatcher->getSupportVSDecoder());
    scaleMeters->setChecked(dispatcher->getUseScaleMeters());
    scaleFeet->setChecked(!dispatcher->getUseScaleMeters());
    minThrottleIntervalSpinner->setValue(dispatcher->getMinThrottleInterval());
    fullRampTimeSpinner->setValue(dispatcher->getFullRampTime());

    if (dispatcher->getLayoutEditor() != nullptr) {
        openDispatcherWithPanel->setChecked(dispatcher->getLayoutEditor()->getOpenDispatcherOnLoad());
    }
    optionsFrame->pack();
    optionsFrame->setVisible(true);
}

/*private*/ void OptionsMenu::applyOptions(/*ActionEvent e*/) {
    if (layoutEditorList->size() > 0) {
        int index = layoutEditorBox->currentIndex();
        dispatcher->setLayoutEditor(layoutEditorList->at(index));
        dispatcher->setUseConnectivity(useConnectivityCheckBox->isChecked());
    }
    dispatcher->setTrainsFromRoster(trainsFromRoster->isChecked());
    dispatcher->setTrainsFromTrains(trainsFromTrains->isChecked());
    dispatcher->setTrainsFromUser(trainsFromUser->isChecked());
    dispatcher->setHasOccupancyDetection(detectionCheckBox->isChecked());
    dispatcher->setAutoAllocate(autoAllocateCheckBox->isChecked());
    autoDispatchItem->setChecked(autoAllocateCheckBox->isChecked());
    dispatcher->setAutoTurnouts(autoTurnoutsCheckBox->isChecked());
    autoTurnoutsItem->setChecked(autoTurnoutsCheckBox->isChecked());
    dispatcher->setTrustKnownTurnouts(trustKnownTurnoutsCheckBox->isChecked());
    dispatcher->setSignalType(signalTypeBox->currentIndex());
    if (autoTurnoutsCheckBox->isChecked() && ((layoutEditorList->size() == 0)
            || (!useConnectivityCheckBox->isChecked()))) {
        JOptionPane::showMessageDialog(optionsFrame, tr(
                "Without connectivity from a Layout Editor panel, all turnouts\nmay not be set correctly. Please check when allocating."), tr("Warning"), JOptionPane::WARNING_MESSAGE);
    }
    dispatcher->setShortActiveTrainNames(shortNameCheckBox->isChecked());
    dispatcher->setShortNameInBlock(nameInBlockCheckBox->isChecked());
    dispatcher->setExtraColorForAllocated(extraColorForAllocatedCheckBox->isChecked());
    dispatcher->setNameInAllocatedBlock(nameInAllocatedBlockCheckBox->isChecked());
    dispatcher->setRosterEntryInBlock(rosterInBlockCheckBox->isChecked());
    dispatcher->setSupportVSDecoder(supportVSDecoderCheckBox->isChecked());
    dispatcher->setScale(VPtr<Scale>::asPtr(layoutScaleBox->currentData()));
    dispatcher->setUseScaleMeters(scaleMeters->isChecked());
    dispatcher->setMinThrottleInterval((int) minThrottleIntervalSpinner->value());
    dispatcher->setFullRampTime((int) fullRampTimeSpinner->value());
    dispatcher->getLayoutEditor()->setOpenDispatcherOnLoad(openDispatcherWithPanel->isChecked());
    optionsFrame->setVisible(false);
    optionsFrame->dispose(); // prevent this window from being listed in the Window menu.
    optionsFrame = nullptr;
    // save options reminder
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
            showInfoMessage(tr("Reminder"), tr("<html>Remember to save your Dispatcher Options settings to disk.<br>(choose Save Options from the Options menu)</html>"),
                    "OptionsMenu"/*.class.getName()*/,
                    "remindSaveDispatcherOptions"); // NOI18N
    initializeMenu();
}

/*private*/ void OptionsMenu::cancelOptions(/*ActionEvent e*/) {
    optionsFrame->setVisible(false);
    optionsFrame->dispose();  // prevent this window from being listed in the Window menu.
    optionsFrame = nullptr;
}

/*private*/ void OptionsMenu::saveRequested() {
    try {
        ((OptionsFile*)InstanceManager::getDefault("OptionsFile"))->writeDispatcherOptions(dispatcher);
    } catch (IOException ioe) {
        log->error("Exception writing Dispatcher options: " + ioe.getMessage());
    }
}

/*private*/ bool OptionsMenu::initializeLayoutEditorCombo() {
    // get list of Layout Editor panels
    layoutEditorList = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
    if (layoutEditorList->size() == 0) {
        return false;
    }
    layoutEditorBox->clear();
    for (int i = 0; i < layoutEditorList->size(); i++) {
        layoutEditorBox->addItem(layoutEditorList->at(i)->getTitle());
    }
    if (layoutEditorList->size() > 1) {
        LayoutEditor* le = dispatcher->getLayoutEditor();
        for (int j = 0; j < layoutEditorList->size(); j++) {
            if (le == layoutEditorList->at(j)) {
                layoutEditorBox->setCurrentIndex(j);
            }
        }
    } else {
        layoutEditorBox->setCurrentIndex(0);
    }
    return true;
}

/*private*/ void OptionsMenu::initializeScaleCombo() {
 layoutScaleBox->clear();
 for (Scale* scale : ScaleManager::getScales()) {
     if (scale->getScaleName() ==("CUSTOM")) {  // No custom support yet, don't show.
         continue;
     }
     layoutScaleBox->addItem(scale->getScaleName(), VPtr<Scale>::asQVariant(scale));
 }
 //JComboBoxUtil.setupComboBoxMaxRows(layoutScaleBox);
 layoutScaleBox->setCurrentIndex(layoutScaleBox->findData(VPtr<Scale>::asQVariant(dispatcher->getScale())));
}

/*public*/ void OptionsMenu::useRosterEntry_actionPerformed(QObject* e) {
    if (trainsFromRoster->isChecked()) {
        rosterInBlockCheckBox->setEnabled(true);
        if (nameInBlockCheckBox->isChecked() && (QCheckBox*)e == nameInBlockCheckBox) {
            rosterInBlockCheckBox->setChecked(false);
        } else if (rosterInBlockCheckBox->isChecked() && (QCheckBox*)e == rosterInBlockCheckBox) {
            nameInBlockCheckBox->setChecked(false);
        }
    } else {
        rosterInBlockCheckBox->setEnabled(false);
    }
}

/*private*/ /*final*/ /*static*/ Logger* OptionsMenu::log = LoggerFactory::getLogger("OptionsMenu");
