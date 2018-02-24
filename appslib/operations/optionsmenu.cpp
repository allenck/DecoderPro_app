#include "optionsmenu.h"
#include "dispatcherframe.h"
#include "loggerfactory.h"
/**
 * Sets up and processes items in the Dispatcher Options menu.
 *
 * @author Dave Duchamp Copyright (C) 2008
 */
///*public*/ class OptionsMenu extends JMenu {

/*public*/ OptionsMenu::OptionsMenu(DispatcherFrame* f, QWidget*parent) : QMenu(parent){
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

/*private*/ void OptionsMenu::handleAutoDispatch(ActionEvent* /*e*/) {
    bool set = autoDispatchItem->isChecked();
    dispatcher->setAutoAllocate(set);
}

/*private*/ void OptionsMenu::handleAutoTurnouts(ActionEvent* /*e*/) {
    bool set = autoTurnoutsItem->isChecked();
    dispatcher->setAutoTurnouts(set);
}
#if 0
// options window items
JmriJFrame optionsFrame = null;
Container optionsPane = null;
JCheckBox useConnectivityCheckBox = new JCheckBox(tr("UseConnectivity"));
JComboBox<String> layoutEditorBox = new JComboBox<String>();
ArrayList<LayoutEditor> layoutEditorList = new ArrayList<LayoutEditor>();
JCheckBox autoAllocateCheckBox = new JCheckBox(tr("AutoAllocateBox"));
JCheckBox autoTurnoutsCheckBox = new JCheckBox(tr("AutoTurnoutsBox"));
JRadioButton trainsFromRoster = new JRadioButton(tr("TrainsFromRoster"));
JRadioButton trainsFromTrains = new JRadioButton(tr("TrainsFromTrains"));
JRadioButton trainsFromUser = new JRadioButton(tr("TrainsFromUser"));
JComboBox<String> signalTypeBox;
JCheckBox detectionCheckBox = new JCheckBox(tr("DetectionBox"));
JCheckBox shortNameCheckBox = new JCheckBox(tr("ShortNameBox"));
JCheckBox nameInBlockCheckBox = new JCheckBox(tr("NameInBlockBox"));
JCheckBox rosterInBlockCheckBox = new JCheckBox(tr("RosterInBlockBox"));
JCheckBox extraColorForAllocatedCheckBox = new JCheckBox(tr("ExtraColorForAllocatedBox"));
JCheckBox nameInAllocatedBlockCheckBox = new JCheckBox(tr("NameInAllocatedBlockBox"));
JCheckBox supportVSDecoderCheckBox = new JCheckBox(tr("SupportVSDecoder"));
JComboBox<String> layoutScaleBox = new JComboBox<String>();
JRadioButton scaleFeet = new JRadioButton(tr("ScaleFeet"));
JRadioButton scaleMeters = new JRadioButton(tr("ScaleMeters"));
JCheckBox openDispatcherWithPanel = new JCheckBox(tr("OpenDispatcherWithPanelBox"));
JSpinner minThrottleIntervalSpinner = new JSpinner(new SpinnerNumberModel(100, 20, 1000, 1));
JSpinner fullRampTimeSpinner = new JSpinner(new SpinnerNumberModel(5000, 1000, 20000, 1));
JCheckBox trustKnownTurnoutsCheckBox = new JCheckBox(tr("trustKnownTurnouts"));

String[] signalTypes = {tr("SignalType1"), tr("SignalType2")};

/*private*/ void optionWindowRequested(ActionEvent e) {
    if (optionsFrame == null) {
        optionsFrame = new JmriJFrame(tr("OptionWindowItem"), false, true);
        optionsFrame.addHelpMenu("package.jmri.jmrit.dispatcher.Options", true);
        optionsPane = optionsFrame.getContentPane();
        optionsPane.setLayout(new BoxLayout(optionsFrame.getContentPane(), BoxLayout.Y_AXIS));
        JPanel p1 = new JPanel();
        p1.setLayout(new FlowLayout());
        p1.add(useConnectivityCheckBox);
        useConnectivityCheckBox.setToolTipText(tr("UseConnectivityHint"));
        p1.add(layoutEditorBox);
        layoutEditorBox.setToolTipText(tr("LayoutEditorHint"));
        signalTypeBox = new JComboBox<String>(signalTypes);
        p1.add(signalTypeBox);
        signalTypeBox.setToolTipText(tr("SignalTypeHint"));
        optionsPane.add(p1);
        JPanel p2 = new JPanel();
        p2.setLayout(new FlowLayout());
        ButtonGroup trainsGroup = new ButtonGroup();
        p2.add(trainsFromRoster);
        trainsFromRoster.setToolTipText(tr("TrainsFromRosterHint"));
        trainsGroup.add(trainsFromRoster);

        ActionListener useRosterEntryListener = new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                if (trainsFromRoster.isSelected()) {
                    rosterInBlockCheckBox.setEnabled(true);
                    if (nameInBlockCheckBox.isSelected() && e.getSource() == nameInBlockCheckBox) {
                        rosterInBlockCheckBox.setSelected(false);
                    } else if (rosterInBlockCheckBox.isSelected() && e.getSource() == rosterInBlockCheckBox) {
                        nameInBlockCheckBox.setSelected(false);
                    }
                } else {
                    rosterInBlockCheckBox.setEnabled(false);
                }
            }
        };
        trainsFromRoster.addActionListener(useRosterEntryListener);
        p2.add(new JLabel("     "));
        p2.add(trainsFromTrains);
        trainsFromTrains.setToolTipText(tr("TrainsFromTrainsHint"));
        trainsFromTrains.addActionListener(useRosterEntryListener);
        trainsGroup.add(trainsFromTrains);
        p2.add(new JLabel("     "));
        p2.add(trainsFromUser);
        trainsFromUser.setToolTipText(tr("TrainsFromUserHint"));
        trainsFromUser.addActionListener(useRosterEntryListener);
        trainsGroup.add(trainsFromUser);
        optionsPane.add(p2);
        JPanel p3 = new JPanel();
        p3.setLayout(new FlowLayout());
        p3.add(detectionCheckBox);
        detectionCheckBox.setToolTipText(tr("DetectionBoxHint"));
        optionsPane.add(p3);
        JPanel p4 = new JPanel();
        p4.setLayout(new FlowLayout());
        p4.add(autoAllocateCheckBox);
        autoAllocateCheckBox.setToolTipText(tr("AutoAllocateBoxHint"));
        optionsPane.add(p4);
        JPanel p5 = new JPanel();
        p5.setLayout(new FlowLayout());
        p5.add(autoTurnoutsCheckBox);
        autoTurnoutsCheckBox.setToolTipText(tr("AutoTurnoutsBoxHint"));
        optionsPane.add(p5);
        JPanel p16 = new JPanel();
        p16.setLayout(new FlowLayout());
        p16.add(trustKnownTurnoutsCheckBox);
        trustKnownTurnoutsCheckBox.setToolTipText(tr("trustKnownTurnoutsHint"));
        optionsPane.add(p16);
        JPanel p6 = new JPanel();
        p6.setLayout(new FlowLayout());
        p6.add(shortNameCheckBox);
        shortNameCheckBox.setToolTipText(tr("ShortNameBoxHint"));
        optionsPane.add(p6);
        JPanel p7 = new JPanel();
        p7.setLayout(new FlowLayout());
        p7.add(nameInBlockCheckBox);
        nameInBlockCheckBox.setToolTipText(tr("NameInBlockBoxHint"));
        nameInBlockCheckBox.addActionListener(useRosterEntryListener);
        optionsPane.add(p7);
        JPanel p7b = new JPanel();
        p7b.setLayout(new FlowLayout());
        p7b.add(rosterInBlockCheckBox);
        rosterInBlockCheckBox.setToolTipText(tr("RosterInBlockBoxHint"));
        rosterInBlockCheckBox.addActionListener(useRosterEntryListener);
        optionsPane.add(p7b);

        JPanel p10 = new JPanel();
        p10.setLayout(new FlowLayout());
        p10.add(extraColorForAllocatedCheckBox);
        extraColorForAllocatedCheckBox.setToolTipText(tr("ExtraColorForAllocatedBoxHint"));
        optionsPane.add(p10);
        JPanel p11 = new JPanel();
        p11.setLayout(new FlowLayout());
        p11.add(nameInAllocatedBlockCheckBox);
        nameInAllocatedBlockCheckBox.setToolTipText(tr("NameInAllocatedBlockBoxHint"));
        optionsPane.add(p11);
        JPanel p13 = new JPanel();
        p13.setLayout(new FlowLayout());
        p13.add(supportVSDecoderCheckBox);
        supportVSDecoderCheckBox.setToolTipText(tr("SupportVSDecoderBoxHint"));
        optionsPane.add(p13);
        JPanel p8 = new JPanel();
        initializeScaleCombo();
        p8.add(new JLabel(tr("LayoutScale") + ":"));
        p8.add(layoutScaleBox);
        layoutScaleBox.setToolTipText(tr("ScaleBoxHint"));
        optionsPane.add(p8);
        JPanel p12 = new JPanel();
        p12.setLayout(new FlowLayout());
        p12.add(new JLabel(tr("Units") + "  "));
        ButtonGroup scaleGroup = new ButtonGroup();
        p12.add(scaleFeet);
        scaleFeet.setToolTipText(tr("ScaleFeetHint"));
        scaleGroup.add(scaleFeet);
        p12.add(new JLabel("  "));
        p12.add(scaleMeters);
        scaleMeters.setToolTipText(tr("ScaleMetersHint"));
        scaleGroup.add(scaleMeters);
        optionsPane.add(p12);

        JPanel p15 = new JPanel();
        p15.setLayout(new FlowLayout());
        p15.add(new JLabel(tr("minThrottleInterval") + ":"));
        minThrottleIntervalSpinner.setToolTipText(tr("minThrottleIntervalHint"));
        p15.add(minThrottleIntervalSpinner);
        p15.add(new JLabel(tr("ms")));
        optionsPane.add(p15);

        JPanel p17 = new JPanel();
        p17.setLayout(new FlowLayout());
        p17.add(new JLabel(tr("fullRampTime") + " :"));
        fullRampTimeSpinner.setToolTipText(tr("fullRampTimeHint", tr("RAMP_FAST")));
        p17.add(fullRampTimeSpinner);
        p17.add(new JLabel(tr("ms")));
        optionsPane.add(p17);

        JPanel p14 = new JPanel();
        p14.setLayout(new FlowLayout());
        p14.add(openDispatcherWithPanel);
        openDispatcherWithPanel.setToolTipText(tr("OpenDispatcherWithPanelBoxHint"));
        optionsPane.add(p14);

        optionsPane.add(new JSeparator());
        JPanel p9 = new JPanel();
        p9.setLayout(new FlowLayout());
        JButton cancelButton = null;
        p9.add(cancelButton = new JButton(tr("ButtonCancel")));
        cancelButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                cancelOptions(e);
            }
        });
        cancelButton.setToolTipText(tr("CancelButtonHint2"));
        p9.add(new JLabel("     "));
        JButton applyButton = null;
        p9.add(applyButton = new JButton(tr("ButtonApply")));
        applyButton.addActionListener(new ActionListener() {
            @Override
            /*public*/ void actionPerformed(ActionEvent e) {
                applyOptions(e);
            }
        });
        applyButton.setToolTipText(tr("ApplyButtonHint"));
        optionsPane.add(p9);
    }
    if (initializeLayoutEditorCombo()) {
        useConnectivityCheckBox.setVisible(true);
        layoutEditorBox.setVisible(true);
    } else {
        useConnectivityCheckBox.setVisible(false);
        layoutEditorBox.setVisible(false);
    }
    useConnectivityCheckBox.setSelected(dispatcher.getUseConnectivity());
    signalTypeBox.setSelectedIndex(dispatcher.getSignalType());
    trainsFromRoster.setSelected(dispatcher.getTrainsFromRoster());
    trainsFromTrains.setSelected(dispatcher.getTrainsFromTrains());
    trainsFromUser.setSelected(dispatcher.getTrainsFromUser());
    detectionCheckBox.setSelected(dispatcher.getHasOccupancyDetection());
    autoAllocateCheckBox.setSelected(dispatcher.getAutoAllocate());
    autoTurnoutsCheckBox.setSelected(dispatcher.getAutoTurnouts());
    trustKnownTurnoutsCheckBox.setSelected(dispatcher.getTrustKnownTurnouts());
    shortNameCheckBox.setSelected(dispatcher.getShortActiveTrainNames());
    nameInBlockCheckBox.setSelected(dispatcher.getShortNameInBlock());
    rosterInBlockCheckBox.setSelected(dispatcher.getRosterEntryInBlock());
    extraColorForAllocatedCheckBox.setSelected(dispatcher.getExtraColorForAllocated());
    nameInAllocatedBlockCheckBox.setSelected(dispatcher.getNameInAllocatedBlock());
    supportVSDecoderCheckBox.setSelected(dispatcher.getSupportVSDecoder());
    scaleMeters.setSelected(dispatcher.getUseScaleMeters());
    scaleFeet.setSelected(!dispatcher.getUseScaleMeters());
    minThrottleIntervalSpinner.setValue(dispatcher.getMinThrottleInterval());
    fullRampTimeSpinner.setValue(dispatcher.getFullRampTime());

    if (dispatcher.getLayoutEditor() != null) {
        openDispatcherWithPanel.setSelected(dispatcher.getLayoutEditor().getOpenDispatcherOnLoad());
    }
    optionsFrame.pack();
    optionsFrame.setVisible(true);
}

/*private*/ void applyOptions(ActionEvent e) {
    if (layoutEditorList.size() > 0) {
        int index = layoutEditorBox.getSelectedIndex();
        dispatcher.setLayoutEditor(layoutEditorList.get(index));
        dispatcher.setUseConnectivity(useConnectivityCheckBox.isSelected());
    }
    dispatcher.setTrainsFromRoster(trainsFromRoster.isSelected());
    dispatcher.setTrainsFromTrains(trainsFromTrains.isSelected());
    dispatcher.setTrainsFromUser(trainsFromUser.isSelected());
    dispatcher.setHasOccupancyDetection(detectionCheckBox.isSelected());
    dispatcher.setAutoAllocate(autoAllocateCheckBox.isSelected());
    autoDispatchItem.setSelected(autoAllocateCheckBox.isSelected());
    dispatcher.setAutoTurnouts(autoTurnoutsCheckBox.isSelected());
    autoTurnoutsItem.setSelected(autoTurnoutsCheckBox.isSelected());
    dispatcher.setTrustKnownTurnouts(trustKnownTurnoutsCheckBox.isSelected());
    dispatcher.setSignalType(signalTypeBox.getSelectedIndex());
    if (autoTurnoutsCheckBox.isSelected() && ((layoutEditorList.size() == 0)
            || (!useConnectivityCheckBox.isSelected()))) {
        JOptionPane.showMessageDialog(optionsFrame, tr(
                "AutoTurnoutsWarn"), tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
    }
    dispatcher.setShortActiveTrainNames(shortNameCheckBox.isSelected());
    dispatcher.setShortNameInBlock(nameInBlockCheckBox.isSelected());
    dispatcher.setExtraColorForAllocated(extraColorForAllocatedCheckBox.isSelected());
    dispatcher.setNameInAllocatedBlock(nameInAllocatedBlockCheckBox.isSelected());
    dispatcher.setRosterEntryInBlock(rosterInBlockCheckBox.isSelected());
    dispatcher.setSupportVSDecoder(supportVSDecoderCheckBox.isSelected());
    dispatcher.setScale(layoutScaleBox.getSelectedIndex() + 1);
    dispatcher.setUseScaleMeters(scaleMeters.isSelected());
    dispatcher.setMinThrottleInterval((int) minThrottleIntervalSpinner.getValue());
    dispatcher.setFullRampTime((int) fullRampTimeSpinner.getValue());
    dispatcher.getLayoutEditor().setOpenDispatcherOnLoad(openDispatcherWithPanel.isSelected());
    optionsFrame.setVisible(false);
    optionsFrame.dispose(); // prevent this window from being listed in the Window menu.
    optionsFrame = null;
    // save options reminder
    InstanceManager.getDefault(jmri.UserPreferencesManager.class).
            showInfoMessage(tr("ReminderTitle"), tr("ReminderSaveOptions"),
                    OptionsMenu.class.getName(),
                    "remindSaveDispatcherOptions"); // NOI18N
    initializeMenu();
}

/*private*/ void cancelOptions(ActionEvent e) {
    optionsFrame.setVisible(false);
    optionsFrame.dispose();  // prevent this window from being listed in the Window menu.
    optionsFrame = null;
}

/*private*/ void saveRequested(ActionEvent e) {
    try {
        InstanceManager.getDefault(OptionsFile.class).writeDispatcherOptions(dispatcher);
    } catch (java.io.IOException ioe) {
        log.error("Exception writing Dispatcher options: " + ioe);
    }
}

/*private*/ boolean initializeLayoutEditorCombo() {
    // get list of Layout Editor panels
    layoutEditorList = InstanceManager.getDefault(PanelMenu.class).getLayoutEditorPanelList();
    if (layoutEditorList.size() == 0) {
        return false;
    }
    layoutEditorBox.removeAllItems();
    for (int i = 0; i < layoutEditorList.size(); i++) {
        layoutEditorBox.addItem(layoutEditorList.get(i).getTitle());
    }
    if (layoutEditorList.size() > 1) {
        LayoutEditor le = dispatcher.getLayoutEditor();
        for (int j = 0; j < layoutEditorList.size(); j++) {
            if (le == layoutEditorList.get(j)) {
                layoutEditorBox.setSelectedIndex(j);
            }
        }
    } else {
        layoutEditorBox.setSelectedIndex(0);
    }
    return true;
}

/*private*/ void initializeScaleCombo() {
    layoutScaleBox.removeAllItems();
    for (int i = 0; i < Scale.NUM_SCALES; i++) {
        layoutScaleBox.addItem(Scale.getScaleID(i + 1));
    }
    layoutScaleBox.setSelectedIndex(dispatcher.getScale() - 1);
}
#endif
/*private*/ /*final*/ /*static*/ Logger* OptionsMenu::log = LoggerFactory::getLogger("OptionsMenu");
