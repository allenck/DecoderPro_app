#include "addeditsinglelightcontrolframe.h"
#include "loggerfactory.h"
#include "borderfactory.h"
#include "defaultlightcontrol.h"
#include "threadingutil.h"

/**
 * Frame to add or edit a single Light Control.
 * Code originally within LightTableAction.
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
///*public*/ class AddEditSingleLightControlFrame extends jmri.util.JmriJFrame {


/**
 * Create a new Frame to Add or Edit a Light Control.
 *
 * @param pane Light Control Pane which instigated the action.
 * @param ctrl If LightControl is null, is a Add Control Window.
 *              If LightControl specified, is an Edit Control window.
 */
/*public*/ AddEditSingleLightControlFrame::AddEditSingleLightControlFrame(/*@Nonnull*/ LightControlPane* pane, LightControl* ctrl) : JmriJFrame(tr("Add Light Control"), false, true)
{
    //super(tr("TitleAddLightControl"), false, true);
    lc = ctrl;
    lcp = pane;
    init();
}

/*private*/ void AddEditSingleLightControlFrame::init(){

    addHelpMenu("package.jmri.jmrit.beantable.LightAddEdit", true);

    QWidget* contentPane = getContentPane();
    contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

    JPanel* mainContentPanel = new JPanel();
    mainContentPanel->setLayout(new QVBoxLayout());//mainContentPanel, BoxLayout.Y_AXIS));

    JPanel* controlTypePanel = new JPanel();
    controlTypePanel->setLayout(new FlowLayout());
    controlTypePanel->layout()->addWidget(new JLabel(tr("Controller Type:")));
    typeBox = new JComboBox(LightControlTableModel::controlTypes.toList());
//    ComboBoxToolTipRenderer* typeBoxToolTipRenderer = new ComboBoxToolTipRenderer();
//    typeBoxToolTipRenderer->setTooltips(LightControlTableModel.getControlTypeTips());
//    typeBox->setRenderer(typeBoxToolTipRenderer);

    //typeBox.addActionListener((ActionEvent e) -> setUpControlType(typeBox.getSelectedIndex()));
    connect(typeBox, &JComboBox::currentIndexChanged, [=]{typeBox->getSelectedIndex();});
    typeBox->setToolTip(tr("Select how the new Light is to be controlled"));

    controlTypePanel->layout()->addWidget(typeBox);

    JPanel* mainOptionsPanel = new JPanel();
    mainOptionsPanel->setLayout(new FlowLayout());
    mainOptionsPanel->layout()->addWidget(f1Label);
    mainOptionsPanel->layout()->addWidget(sensor1Box);

    // set up number formatting
    JSpinner::NumberEditor* ne1b = new JSpinner::NumberEditor(fastHourSpinner1, "00"); // 2 digits "01" format
    fastHourSpinner1->setEditor(ne1b);
    mainOptionsPanel->layout()->addWidget(fastHourSpinner1);  // hours ON
    mainOptionsPanel->layout()->addWidget(clockSep1);
    JSpinner::NumberEditor* ne1b1 = new JSpinner::NumberEditor(fastMinuteSpinner1, "00"); // 2 digits "01" format
    fastMinuteSpinner1->setEditor(ne1b1);
    mainOptionsPanel->layout()->addWidget(fastMinuteSpinner1); // minutes ON
    mainOptionsPanel->layout()->addWidget(turnoutBox);
    mainOptionsPanel->layout()->addWidget(sensorOnBox);

    sensor1Box->setAllowNull(true);
    sensor1Box->setToolTip(tr("Select the Sensor controlling this Light"));

    sensor2Box->setAllowNull(true);
    sensor2Box->setToolTip(tr("Select the two Sensors controlling this Light"));

    fastHourSpinner1->setValue(0);  // reset needed
    fastHourSpinner1->setVisible(false);
    fastMinuteSpinner1->setValue(0); // reset needed
    fastMinuteSpinner1->setVisible(false);

    sensorOnBox->setAllowNull(true);
    sensorOnBox->setVisible(false);
    clockSep1->setVisible(false);

    turnoutBox->setAllowNull(true);
    turnoutBox->setVisible(false);

    sensorTwoPanel = new JPanel();
    sensorTwoPanel->setLayout(new FlowLayout());
    sensorTwoPanel->layout()->addWidget(f1aLabel);
    sensorTwoPanel->layout()->addWidget(sensor2Box);

    JPanel* panel33 = new JPanel();
    panel33->setLayout(new FlowLayout());


    panel33->layout()->addWidget(f2Label);

    stateBox = new JComboBox(QStringList{
        tr("Active"), tr("Inactive")});
    stateBox->setToolTip(tr("Select Sensor state corresponding to Light ON"));
//    stateBoxToolTipRenderer = new ComboBoxToolTipRenderer();
//    stateBox->setRenderer(stateBoxToolTipRenderer);
    panel33->layout()->addWidget(stateBox);

    JSpinner::NumberEditor* ne2a = new JSpinner::NumberEditor(fastHourSpinner2, "00"); // 2 digits "01" format
    fastHourSpinner2->setEditor(ne2a);
    panel33->layout()->addWidget(fastHourSpinner2);  // hours OFF
    panel33->layout()->addWidget(clockSep2);

    JSpinner::NumberEditor* ne2a1 = new JSpinner::NumberEditor(fastMinuteSpinner2, "00"); // 2 digits "01" format
    fastMinuteSpinner2->setEditor(ne2a1);
    panel33->layout()->addWidget(fastMinuteSpinner2); // minutes OFF
    panel33->layout()->addWidget(timedOnSpinner);

    fastHourSpinner2->setValue(0);  // reset needed
    fastHourSpinner2->setVisible(false);
    fastMinuteSpinner2->setValue(0); // reset needed
    fastMinuteSpinner2->setVisible(false);

    timedOnSpinner->setValue(5000);  // reset needed, default to 5,000 ms
    timedOnSpinner->setVisible(false);
    clockSep2->setVisible(false);

    mainContentPanel->layout()->addWidget(controlTypePanel);
    mainContentPanel->layout()->addWidget(mainOptionsPanel);
    mainContentPanel->layout()->addWidget(sensorTwoPanel);
    mainContentPanel->layout()->addWidget(panel33);
    mainContentPanel->setBorder(BorderFactory::createEtchedBorder());
    contentPane->layout()->addWidget(mainContentPanel);
    contentPane->layout()->addWidget(getButtonPanel());

    JPanel* statusPanel = new JPanel();
    statusPanel->layout()->addWidget(status1);
    contentPane->layout()->addWidget(statusPanel);

//    addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            cancelControlPressed(null);
//        }
//    });
    addWindowListener(new AESLCF_windowListener(this));
    typeBox->setSelectedIndex(lcp->getLastSelectedControlIndex()); // force GUI status consistent

    if (lc!=nullptr){
        setTitle(tr("Edit Light Controller"));
        setFrameToControl(lc);
    }

}

/*private*/ JPanel* AddEditSingleLightControlFrame::getButtonPanel(){

    JPanel* buttonPanel = new JPanel();
    buttonPanel->setLayout(new FlowLayout());//FlowLayout.TRAILING));
    cancelControl = new JButton(tr("Cancel"));
    buttonPanel->layout()->addWidget(cancelControl);
    //cancelControl.addActionListener(this::cancelControlPressed);
    connect(cancelControl, &JButton::clicked, [=]{cancelControlPressed(nullptr);});
    cancelControl->setToolTip(tr("Click to leave unchanged"));
    createControl = new JButton(tr("Create"));
    buttonPanel->layout()->addWidget(createControl);
    //createControl.addActionListener(this::createControlPressed);
    connect(createControl, &JButton::clicked, [=]{createControlPressed(nullptr);});
    createControl->setToolTip(tr("Click to create a new Light Controller"));
    updateControl = new JButton(tr("ButtonUpdate"));
    buttonPanel->layout()->addWidget(updateControl);
    //updateControl.addActionListener(this::updateControlPressed);
    connect(updateControl, &JButton::clicked, [=]{updateControlPressed(nullptr);});
    updateControl->setToolTip(tr("Click to change the Light Controller"));

    cancelControl->setVisible(true);
    updateControl->setVisible(lc!=nullptr);
    createControl->setVisible(lc==nullptr);

    return buttonPanel;
}

/**
 * Set the Control Information according to control type.
 *
 * @param ctype the control type
 */
/*private*/ void AddEditSingleLightControlFrame::setUpControlType(int ctype) {
    // set everything non-visible by default
    clockSep1->setVisible(false);
    clockSep2->setVisible(false);
    fastHourSpinner1->setVisible(false);
    fastHourSpinner2->setVisible(false);
    fastMinuteSpinner1->setVisible(false);
    fastMinuteSpinner2->setVisible(false);
    f1aLabel->setVisible(false);
    sensorOnBox->setVisible(false);
    sensor1Box->setVisible(false);
    sensor2Box->setVisible(false);
    stateBox->setVisible(false);
    timedOnSpinner->setVisible(false);
    turnoutBox->setVisible(false);
    sensorTwoPanel->setVisible(false);
    typeBox->setSelectedIndex(ctype);
    createControl->setEnabled(true);
    updateControl->setEnabled(true);

    lcp->setLastSelectedControlIndex(ctype);

    QList<QString> stateTooltips;

    switch (ctype) {
        case Light::SENSOR_CONTROL:
            // set up panel for sensor control
            f1Label->setText(tr("Controller Sensor{%1").arg(tr("%1:").arg(""))); // insert nothing before colon
            sensor1Box->setToolTip(tr("Select the Sensor controlling this Light"));
            f2Label->setText(tr("LightSensorSense"));
            stateBox->clear();
            stateBox->addItem(tr("Active"));
            stateBox->addItem(tr("Inactive"));
            stateTooltips = QStringList();
            stateTooltips.append(tr("<html>Light ON when Sensor changes to Active<br>Light OFF when Sensor changes to Inactive</html>"));
            stateTooltips.append(tr("LightSensorSenseInactivTip"));
//            stateBoxToolTipRenderer->setTooltips(stateTooltips);
            stateBox->setToolTip(tr("Select Sensor state corresponding to Light ON"));
            f2Label->setVisible(true);
            sensor1Box->setVisible(true);
            stateBox->setVisible(true);

            break;
        case Light::FAST_CLOCK_CONTROL:
            // set up panel for fast clock control
            f1Label->setText(tr("LightScheduleOn"));
            fastHourSpinner1->setToolTip(tr("Enter hours as for a 24-hour clock"));
            fastMinuteSpinner1->setToolTip(tr("Enter the minutes"));
            f2Label->setText(tr("LightScheduleOff"));
            fastHourSpinner2->setToolTip(tr("Enter hours as for a 24-hour clock"));
            fastMinuteSpinner2->setToolTip(tr("Enter the minutes"));
            clockSep1->setVisible(true);
            clockSep2->setVisible(true);
            fastHourSpinner1->setVisible(true);
            fastHourSpinner2->setVisible(true);
            fastMinuteSpinner1->setVisible(true);
            fastMinuteSpinner2->setVisible(true);
            f2Label->setVisible(true);

            break;
        case Light::TURNOUT_STATUS_CONTROL:
            // set up panel for turnout status control
            f1Label->setText(tr("Controller Turnout:"));
            turnoutBox->setToolTip(tr("Select the Turnout that drives the Light"));
            f2Label->setText(tr("Status for ON:"));

            stateBox->clear();
            stateBox->addItem(InstanceManager::turnoutManagerInstance()->getClosedText());
            stateBox->addItem(InstanceManager::turnoutManagerInstance()->getThrownText());
            stateBox->setToolTip(tr("Select Turnout state corresponding to Light ON"));

            stateTooltips = QStringList();
            stateTooltips.append(tr("<html>Light ON when Turnout changes to %1<br>Light OFF when Turnout changes to %2</html>").arg(
                    InstanceManager::turnoutManagerInstance()->getClosedText(),
                    InstanceManager::turnoutManagerInstance()->getThrownText()));

            stateTooltips.append(tr("LightConToClosedOrThrownTip").arg(
                    InstanceManager::turnoutManagerInstance()->getThrownText(),
                    InstanceManager::turnoutManagerInstance()->getClosedText()));
//            stateBoxToolTipRenderer->setTooltips(stateTooltips);


            f2Label->setVisible(true);
            turnoutBox->setVisible(true);
            stateBox->setVisible(true);

            break;
        case Light::TIMED_ON_CONTROL:
            // set up panel for sensor control
            f1Label->setText(tr("LightTimedSensor"));
            sensorOnBox->setToolTip(tr("Select the Sensor triggering Timed ON"));
            f2Label->setText(tr("LightTimedDurationOn"));
            timedOnSpinner->setToolTip(tr("Enter duration of Timed ON in milliseconds"));
            f2Label->setVisible(true);
            sensorOnBox->setVisible(true);
            timedOnSpinner->setVisible(true);

            break;
        case Light::TWO_SENSOR_CONTROL:
            // set up panel for two sensor control
            sensorTwoPanel->setVisible(true);
            f1Label->setText(tr("Controller Sensor%1").arg(" " + tr("%1:").arg("1"))); // for 2-sensor use, insert number "1" before colon
            f1aLabel->setVisible(true);
            sensor1Box->setToolTip(tr("Select the Sensor controlling this Light"));
            f2Label->setText(tr("LightSensorSense"));

            stateBox->clear();
            stateBox->addItem(tr("SensorStateActive"));
            stateBox->addItem(tr("SensorStateInactive"));
            stateBox->setToolTip(tr("Select Sensor state corresponding to Light ON"));

            stateTooltips = QStringList();
            stateTooltips.append(tr("<html>Light ON when either Sensor changes Active<br>Light OFF when both Sensors Inactive</html>"));
            stateTooltips.append(tr("<html>Light ON when either Sensor changes Inactive<br>Light OFF when both Sensors Active</html>"));
//            stateBoxToolTipRenderer->setTooltips(stateTooltips);

            f2Label->setVisible(true);
            sensor1Box->setVisible(true);
            sensor2Box->setVisible(true);
            sensor1Box->setToolTip(tr("Select the two Sensors controlling this Light"));
            stateBox->setVisible(true);

            break;
        case Light::NO_CONTROL:
            // set up panel for no control
            f1Label->setText(tr("LightNoneSelected"));
            f2Label->setVisible(false);
            createControl->setEnabled(false);
            updateControl->setEnabled(false);
            break;
        default:
            log->error(tr("Unexpected control type in controlTypeChanged: %1").arg(ctype));
            break;
    }
    pack();
    setVisible(true);
}

/*protected*/ void AddEditSingleLightControlFrame::cancelControlPressed(JActionEvent* e) {
    lcp->closeEditControlWindow();
}

/*private*/ void AddEditSingleLightControlFrame::commitEdits(){
    try {
        fastHourSpinner1->commitEdit();
        fastHourSpinner2->commitEdit();
        fastMinuteSpinner1->commitEdit();
        fastMinuteSpinner2->commitEdit();
        timedOnSpinner->commitEdit();
    } catch (ParseException pe) {
        // unlikely to be thrown as values set to original if incorrect on commitEdit()
    }
}

/*protected*/ void AddEditSingleLightControlFrame::updateControlPressed(JActionEvent* e) {
    commitEdits();
    LightControl* newLc = new DefaultLightControl();
    QList<LightControl*> withoutExistingLc = QList<LightControl*>(lcp->getControlList());
    withoutExistingLc.removeOne(lc);
    if (setControlInformation(newLc,withoutExistingLc)) {
        lcp->updateControlPressed(lc,newLc);
        cancelControlPressed(e);
    } else {
        pack();
        setVisible(true);
    }
}

/*protected*/ void AddEditSingleLightControlFrame::createControlPressed(JActionEvent* e) {
    //if (Objects.equals(typeBox->getSelectedItem(), LightControlTableModel::noControl))
    if(typeBox->getSelectedItem() == LightControlTableModel::noControl)
    {
        return;
    }

    commitEdits();
    LightControl* newLc = new DefaultLightControl();
    if (setControlInformation(newLc,lcp->getControlList())) {
        lcp->addControlToTable(newLc);
        cancelControlPressed(e);
    } else {
        pack();
        setVisible(true);
    }
}

/*private*/ void AddEditSingleLightControlFrame::notifyUser(QString message, QColor color){
    status1->setText(message);
    status1->setForeground(color);
//    ThreadingUtil::runOnGUIDelayed( ()->{
        status1->setText(" ");
//    },5000);

}

/**
 * Retrieve control information from pane and update Light Control.
 *
 * @param g LightControl to set to User Settings.
 * @param currentList current Light Control List, used to check that Fast Clock Times are OK.
 * @return 'true' if no errors or warnings
 */
/*private*/ bool AddEditSingleLightControlFrame::setControlInformation(LightControl* g, QList<LightControl*> currentList) {
    // Get control information
    if (LightControlTableModel::sensorControl == (typeBox->getSelectedItem())) {
        // Set type of control
        g->setControlType(Light::SENSOR_CONTROL);
        // Get sensor control information
        Sensor* s = nullptr;
        QString sensorName = sensor1Box->getSelectedItemDisplayName();
        if (sensorName == nullptr) {
            // no sensor selected
            g->setControlType(Light::NO_CONTROL);
            notifyUser(tr("Error: Trigger Sensor could not be provided. Light Control not created."),Qt::gray);
        } else {
            // name was selected, check for user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensorName);
            if (s == nullptr) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensorName);
                if (s != nullptr) {
                    // update sensor system name in case it changed
                    sensorName = s->getSystemName();
                    sensor1Box->setSelectedItem(s);
                }
            }
        }
        int sState =  ( tr("SensorStateInactive") == (stateBox->getSelectedItem())
            ? Sensor::INACTIVE : Sensor::ACTIVE);
        g->setControlSensorName(sensorName);
        g->setControlSensorSense(sState);
        if (s == nullptr) {
            notifyUser(tr("LightWarn1"),Qt::red);
            return false;
        }
    } else if (LightControlTableModel::fastClockControl == (typeBox->getSelectedItem())) {
        // Set type of control
        g->setControlType(Light::FAST_CLOCK_CONTROL);
        // read and parse the hours and minutes in the 2 x 2 spinners
        int onHour =  fastHourSpinner1->getValue();  // hours
        int onMin =  fastMinuteSpinner1->getValue();  // minutes
        int offHour =  fastHourSpinner2->getValue(); // hours
        int offMin =  fastMinuteSpinner2->getValue(); // minutes

        g->setFastClockControlSchedule(onHour, onMin, offHour, offMin);

        if (g->onOffTimesFaulty()) {
            notifyUser(tr("LightWarn11"),Qt::red);
            return false;
        }

        if (g->areFollowerTimesFaulty(currentList)) {
            notifyUser(tr("LightWarn12"),Qt::red);
            return false;
        }

    } else if (LightControlTableModel::turnoutStatusControl == typeBox->getSelectedItem()) {
        bool error = false;
        Turnout* t = nullptr;
        // Set type of control
        g->setControlType(Light::TURNOUT_STATUS_CONTROL);
        // Get turnout control information
        QString turnoutName = turnoutBox->getSelectedItemSystemName();
        if (turnoutName == "") {
            // no turnout selected
            g->setControlType(Light::NO_CONTROL);
            notifyUser(tr("LightWarn10"),Qt::gray);
        } else {

            // TODO : Remove Turnouts which are actually lights ( ???? )
            // from the JComboBox list, not after the user has selected one.

            // Ensure that this Turnout is not already a Light
            // String prefix = Objects.requireNonNull(prefixBox.getSelectedItem()).getSystemPrefix();
            QString prefix = ((LightManager*)InstanceManager::getDefault("LightManager"))->getSystemPrefix();
            if (turnoutName.at(prefix.length()) == 'T') {
                // must be a standard format name (not just a number)
                QString testSN = prefix + "L"
                        + turnoutName.mid(prefix.length() + 1);
                Light* testLight = (Light*)((LightManager*)InstanceManager::getDefault("LightManager"))->
                        getBySystemName(testSN);
                if (testLight != nullptr) {
                    // Requested turnout bit is already assigned to a Light
                    notifyUser(tr("LightWarn3") + " " + testSN + ".",Qt::red);
                    error = true;
                }
            }
            if (!error) {
                // Requested turnout bit is not assigned to a Light
                t = InstanceManager::turnoutManagerInstance()->
                        getByUserName(turnoutName);
                if (t == nullptr) {
                    // not user name, try system name
                    t = InstanceManager::turnoutManagerInstance()->
                            getBySystemName(turnoutName);
                    if (t != nullptr) {
                        // update turnout system name in case it changed
                        turnoutName = t->getSystemName();
                        turnoutBox->setSelectedItem(t);
                    }
                }
            }
        }
        // Initialize the requested Turnout State
        int tState = Turnout::CLOSED;
//        if (Objects.equals(stateBox->getSelectedItem(), InstanceManager::
//                turnoutManagerInstance()->getThrownText())) {
        if(stateBox->getSelectedItem() == InstanceManager::turnoutManagerInstance()->getThrownText())
        {
            tState = Turnout::THROWN;
        }
        g->setControlTurnout(turnoutName);
        g->setControlTurnoutState(tState);
        if (t == nullptr) {
            notifyUser(tr("Error: Turnout could not be provided. Light Control not created."),Qt::red);
            return false;
        }
    } else if (LightControlTableModel::timedOnControl == (typeBox->getSelectedItem())) {
        Sensor* s = nullptr;
        // Set type of control
        g->setControlType(Light::TIMED_ON_CONTROL);
        // Get trigger sensor control information
        QString triggerSensorName = sensorOnBox->getSelectedItemDisplayName();
        if (triggerSensorName == "") {
            // Trigger sensor not selected
            g->setControlType(Light::NO_CONTROL);
            notifyUser(tr("Error: Trigger Sensor could not be provided. Light Control not created."),Qt::gray);
        } else {
            // sensor was selected, try user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->getByUserName(triggerSensorName);
            if (s == nullptr) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(triggerSensorName);
                if (s != nullptr) {
                    // update sensor system name in case it changed
                    triggerSensorName = s->getSystemName();
                    sensorOnBox->setSelectedItem(s);
                }
            }
        }
        g->setControlTimedOnSensorName(triggerSensorName);
        int dur =  timedOnSpinner->getValue();
        g->setTimedOnDuration(dur);
        if (s == nullptr) {
            notifyUser(tr("Error: Trigger Sensor could not be provided. Light Control not created."),Qt::red);
            return false;
        }
    } else if (LightControlTableModel::twoSensorControl == (typeBox->getSelectedItem())) {
        Sensor* s = nullptr;
        Sensor* s2;
        // Set type of control
        g->setControlType(Light::TWO_SENSOR_CONTROL);
        // Get sensor control information
        QString sensorName = sensor1Box->getSelectedItemDisplayName();
        QString sensor2Name = sensor2Box->getSelectedItemDisplayName();
        if (sensorName == nullptr || sensor2Name == nullptr) {
            // no sensor(s) selected
            g->setControlType(Light::NO_CONTROL);
            notifyUser(tr("Error: Trigger Sensor could not be provided. Light Control not created."),Qt::gray);
        } else {
            // name was selected, check for user name first
            s = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensorName);
            if (s == nullptr) {
                // not user name, try system name
                s = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensorName);
                if (s != nullptr) {
                    // update sensor system name in case it changed
                    sensorName = s->getSystemName();
                    sensor1Box->setSelectedItem(s);
                }
            }
            s2 = (Sensor*)InstanceManager::sensorManagerInstance()->
                    getByUserName(sensor2Name);
            if (s2 == nullptr) {
                // not user name, try system name
                s2 = (Sensor*)InstanceManager::sensorManagerInstance()->
                        getBySystemName(sensor2Name);
                if (s2 != nullptr) {
                    // update sensor system name in case it changed
                    sensor2Name = s2->getSystemName();
                    sensor2Box->setSelectedItem(s2);
                }
            }
        }
        int sState = Sensor::ACTIVE;
        //if (Objects.equals(stateBox->getSelectedItem(), tr("Inactive")))
        if(stateBox->getSelectedItem() == tr("Inactive"))
        {
            sState = Sensor::INACTIVE;
        }
        g->setControlSensorName(sensorName);
        g->setControlSensor2Name(sensor2Name);
        g->setControlSensorSense(sState);
        if (s == nullptr) {
            notifyUser(tr("Error: Sensor could not be provided. Light Control not created."),Qt::red);
            return false;
        }
    } else if (LightControlTableModel::noControl == (typeBox->getSelectedItem())) {
        // Set type of control
        g->setControlType(Light::NO_CONTROL);
    } else {
        log->error(tr("Unexpected control type: %1").arg(typeBox->getSelectedItem()));
    }
    return (true);
}

/*private*/ void AddEditSingleLightControlFrame::setFrameToControl(LightControl* lc){

    int ctType = lc->getControlType();
    switch (ctType) {
        case Light::SENSOR_CONTROL:
            setUpControlType(Light::SENSOR_CONTROL);
            sensor1Box->setSelectedItemByName(lc->getControlSensorName());
            stateBox->setSelectedIndex( (lc->getControlSensorSense() == Sensor::ACTIVE)? sensorActiveIndex : sensorInactiveIndex);
            break;
        case Light::FAST_CLOCK_CONTROL:
            setUpControlType(Light::FAST_CLOCK_CONTROL);
            fastHourSpinner1->setValue(lc->getFastClockOnHour());
            fastMinuteSpinner1->setValue(lc->getFastClockOnMin());
            fastHourSpinner2->setValue(lc->getFastClockOffHour());
            fastMinuteSpinner2->setValue(lc->getFastClockOffMin());
            break;
        case Light::TURNOUT_STATUS_CONTROL:
            setUpControlType(Light::TURNOUT_STATUS_CONTROL);
            turnoutBox->setSelectedItemByName(lc->getControlTurnoutName());
            stateBox->setSelectedIndex( (lc->getControlTurnoutState() == Turnout::THROWN)? turnoutThrownIndex : turnoutClosedIndex);
            break;
        case Light::TIMED_ON_CONTROL:
            setUpControlType(Light::TIMED_ON_CONTROL);
            sensorOnBox->setSelectedItemByName(lc->getControlTimedOnSensorName());
            timedOnSpinner->setValue(lc->getTimedOnDuration());
            break;
        case Light::TWO_SENSOR_CONTROL:
            setUpControlType(Light::TWO_SENSOR_CONTROL);
            sensor1Box->setSelectedItemByName(lc->getControlSensorName());
            sensor2Box->setSelectedItemByName(lc->getControlSensor2Name());
            stateBox->setSelectedIndex( (lc->getControlSensorSense() == Sensor::ACTIVE)? sensorActiveIndex : sensorInactiveIndex);
            break;
        case Light::NO_CONTROL:
            setUpControlType(Light::NO_CONTROL);
            break;
        default:
            log->error("Unhandled light control type: {}", ctType);
            break;
    }

}

/*private*/ /*final*/ /*static*/ Logger* AddEditSingleLightControlFrame::log = LoggerFactory::getLogger("AddEditSingleLightControlFrame");
