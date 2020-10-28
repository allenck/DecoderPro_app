#include "ltfcontrolpanel.h"
#include "jslider.h"
#include "jspinner.h"
#include "spinnernumbermodel.h"
#include "speedstepmode.h"
#include "loggerfactory.h"
#include "learnthrottleframe.h"
#include "throttle.h"
#include <QButtonGroup>
#include "instancemanager.h"
#include "borderlayout.h"
#include <QVariant>
/**
 * A JInternalFrame that contains a JSlider to control loco speed, and buttons
 * for forward, reverse and STOP.
 * <p>
 * TODO: fix speed increments (14, 28)
 *
 * @author glen Copyright (C) 2002
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Ken Cameron Copyright (C) 2008
 *
 */
///*public*/ class ControlPanel extends JInternalFrame implements java.beans.PropertyChangeListener {



    /**
     * Constructor.
     * @param ltf the main learn throttle frame.
     */
    /*public*/ LTFControlPanel::LTFControlPanel(LearnThrottleFrame* ltf) : JInternalFrame("Speed"){
        //super("Speed");
        _throttleFrame = ltf;
        speedSlider = new JSlider(0, MAX_SPEED);
        speedSlider->setValue(0);
//        speedSlider->setFocusable(false);
#if 0
        // add mouse-wheel support
        speedSlider->addMouseWheelListener((MouseWheelEvent e) -> {
                if (e.getWheelRotation() > 0) {
                    decelerate1();
                } else {
                    accelerate1();
                }
        });
#endif
        speedSpinner = new JSpinner();

        speedSpinnerModel = new SpinnerNumberModel(0, 0, MAX_SPEED, 1);
        speedSpinner->setModel(speedSpinnerModel);
//        speedSpinner.setFocusable(false);

        speedStep128Button = new QRadioButton(/*SpeedStepMode::NMRA_DCC_128.description*/"128");
        speedStep28Button = new QRadioButton(/*SpeedStepMode::NMRA_DCC_28.description*/"28");
        speedStep27Button = new QRadioButton(/*SpeedStepMode::NMRA_DCC_27.description*/"27");
        speedStep14Button = new QRadioButton(/*SpeedStepMode::NMRA_DCC_14.description*/"14");

        initGUI();
        pack();
    }

    /**
     * Get notification that a throttle has been found as we requested.
     *
     * @param t An instantiation of the DccThrottle with the address requested.
     */
    /*public*/ void LTFControlPanel::notifyThrottleFound(DccThrottle* t) {
        if (log->isDebugEnabled()) {
            log->debug("control panel received new throttle");
        }
        _throttle = t;
        this->setEnabled(true);
        this->setSpeedValues((int) t->getSpeedIncrement(),
                (int) t->getSpeedSetting());
        this->setSpeedSteps(t->getSpeedStepMode());
        _throttle->addPropertyChangeListener((PropertyChangeListener*)this);
    }

    //@Override
    /*public*/ void LTFControlPanel::dispose() {
        if (_throttle != nullptr) {
            _throttle->removePropertyChangeListener((PropertyChangeListener*)this);
            _throttle = nullptr;
        }
        JInternalFrame::dispose();
    }

    // update the state of this panel if any of the properties change
    //@Override
    /*public*/ void LTFControlPanel::propertyChange(PropertyChangeEvent* e) {
        if (log->isDebugEnabled()) {
            log->debug(tr("propertyChange: %1, newValue= %2").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
        }
        if (e->getPropertyName() == (Throttle::SPEEDSETTING)) {
            internalAdjust = true;
            float speed = (/*(Float)*/ e->getNewValue()).toFloat();
            _throttleFrame->setSpeedSetting(speed);
        } else if (e->getPropertyName() == (Throttle::SPEEDSTEPS)) {
            SpeedStepMode* steps = /*(SpeedStepMode)*/VPtr<SpeedStepMode>::asPtr(e->getNewValue());
            setSpeedSteps(steps);
            _throttleFrame->setSpeedStepMode(steps->mode);
        } else if (e->getPropertyName() == (Throttle::ISFORWARD)) {
            bool Forward = (/*(Boolean)*/ e->getNewValue()).toBool();
            _throttleFrame->setButtonForward(Forward);
        }
    }

    /**
     * Enable/Disable all buttons and slider.
     *
     * @param isEnabled True if the buttons/slider should be enabled, false
     *                  otherwise.
     */
    //@Override
    /*public*/ void LTFControlPanel::setEnabled(bool isEnabled) {
        speedStep128Button->setEnabled(isEnabled);
        speedStep28Button->setEnabled(isEnabled);
        speedStep27Button->setEnabled(isEnabled);
        speedStep14Button->setEnabled(isEnabled);
        if (isEnabled) {
            configureAvailableSpeedStepModes();
        }
        speedControllerEnable = isEnabled;
        if (_displaySlider) {
            speedSpinner->setEnabled(false);
            speedSlider->setEnabled(isEnabled);
        } else {
            speedSpinner->setEnabled(isEnabled);
            speedSlider->setEnabled(false);
        }
        JInternalFrame::setEnabled(isEnabled);
    }

    /**
     * Set the GUI to match the speed steps of the current address.
     *
     * @param steps Desired number of speed steps. One of 14,27,28,or 128.
     *              Defaults to 128 step mode
     */
    /*public*/ void LTFControlPanel::setSpeedSteps(SpeedStepMode* steps) {
        // Save the old speed as a float
        float oldSpeed = (speedSlider->getValue() / (MAX_SPEED * 1.0f));

        if ((int)steps->mode == SpeedStepMode::NMRA_DCC_14) {
            speedStep14Button->setChecked(true);
            speedStep27Button->setChecked(false);
            speedStep28Button->setChecked(false);
            speedStep128Button->setChecked(false);
            MAX_SPEED = 14;
        } else if (steps->mode == SpeedStepMode::NMRA_DCC_27) {
            speedStep14Button->setChecked(false);
            speedStep27Button->setChecked(true);
            speedStep28Button->setChecked(false);
            speedStep128Button->setChecked(false);
            MAX_SPEED = 27;
        } else if (steps->mode == SpeedStepMode::NMRA_DCC_28) {
            speedStep14Button->setChecked(false);
            speedStep27Button->setChecked(false);
            speedStep28Button->setChecked(true);
            speedStep128Button->setChecked(false);
            MAX_SPEED = 28;
        } else {
            speedStep14Button->setChecked(false);
            speedStep27Button->setChecked(false);
            speedStep28Button->setChecked(false);
            speedStep128Button->setChecked(true);
            MAX_SPEED = 126;
        }

        // rescale the speed slider to match the new speed step mode
        internalAdjust = true;
        speedSlider->setMaximum(MAX_SPEED);
        speedSlider->setValue((int) (oldSpeed * MAX_SPEED));
//        speedSlider->setMajorTickSpacing(MAX_SPEED / 2);
#if 0
        java.util.Hashtable<Integer, JLabel> labelTable = new java.util.Hashtable<>();
        labelTable.put(Integer.valueOf(MAX_SPEED / 2), new JLabel("50%"));
        labelTable.put(Integer.valueOf(MAX_SPEED), new JLabel("100%"));
        labelTable.put(Integer.valueOf(0), new JLabel(Bundle.getMessage("ButtonStop")));
        speedSlider->setLabelTable(labelTable);
        speedSlider->setPaintTicks(true);
        speedSlider->setPaintLabels(true);
#endif
        speedSpinnerModel->setMaximum(/*Integer.valueOf*/(MAX_SPEED));
        speedSpinnerModel->setMinimum(/*Integer.valueOf*/(0));
        // rescale the speed value to match the new speed step mode
        speedSpinnerModel->setValue(/*Integer.valueOf*/(speedSlider->getValue()));
    }

    /**
     * Set the Speed Control selection method
     *
     * @param displaySlider integer value. possible values: SLIDERDISPLAY = use
     *                      speed slider display STEPDISPLAY = use speed step
     *                      display
     */
    /*public*/ void LTFControlPanel::setSpeedController(bool displaySlider) {
        if (displaySlider) {
            sliderPanel->setVisible(true);
            speedSlider->setEnabled(speedControllerEnable);
            spinnerPanel->setVisible(false);
            if (speedSpinner != nullptr) {
                speedSpinner->setEnabled(false);
            }
        } else {
            sliderPanel->setVisible(false);
            speedSlider->setEnabled(false);
            spinnerPanel->setVisible(true);
            speedSpinner->setEnabled(speedControllerEnable);
        }
        _displaySlider = displaySlider;
    }

    /**
     * Set the GUI to match that the loco speed.
     *
     * @param speedIncrement : TODO
     * @param speed          The speed value of the loco.
     */
    /*public*/ void LTFControlPanel::setSpeedValues(int speedIncrement, int speed) {
        speedSlider->setValue(speed * speedIncrement);
        // Spinner Speed should be the raw integer speed value
        if (speedSpinner != nullptr) {
            speedSpinnerModel->setValue(/*Integer.valueOf*/(speed));
        }
    }

    /**
     * Create, initialize and place GUI components.
     */
    /*private*/ void LTFControlPanel::initGUI() {
        JPanel* mainPanel = new JPanel();
        this->setContentPane(mainPanel);
        mainPanel->setLayout(new BorderLayout());
        this->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);

        JPanel* speedControlPanel = new JPanel();
        speedControlPanel->setLayout(new QHBoxLayout());//speedControlPanel, BoxLayout.X_AXIS));
        ((BorderLayout*)this->getContentPane()->layout())->addWidget(speedControlPanel, BorderLayout::Center);
        sliderPanel = new JPanel();
        GridBagLayout* sliderPanelLayout;
        sliderPanel->setLayout(sliderPanelLayout = new GridBagLayout());

        GridBagConstraints constraints = GridBagConstraints();
        constraints.anchor = GridBagConstraints::CENTER;
        constraints.fill = GridBagConstraints::BOTH;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.ipadx = 0;
        constraints.ipady = 0;
        Insets* insets = new Insets(2, 2, 2, 2);
        constraints.insets = insets;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.gridx = 0;
        constraints.gridy = 0;

        sliderPanelLayout->addWidget(speedSlider, constraints);
        speedControlPanel->layout()->addWidget(sliderPanel);
        speedSlider->setOrientation(Qt::Vertical);
#if 0
        speedSlider->setMajorTickSpacing(MAX_SPEED / 2);
        java.util.Hashtable<Integer, JLabel> labelTable = new java.util.Hashtable<>();
        labelTable.put(Integer.valueOf(MAX_SPEED / 2), new JLabel("50%"));
        labelTable.put(Integer.valueOf(MAX_SPEED), new JLabel("100%"));
        labelTable.put(Integer.valueOf(0), new JLabel(Bundle.getMessage("ButtonStop")));
        speedSlider.setLabelTable(labelTable);
        speedSlider.setPaintTicks(true);
        speedSlider.setPaintLabels(true);
#endif
        // remove old actions
        //speedSlider.addChangeListener((ChangeEvent e)-> {
        connect(speedSlider, &JSlider::valueChanged, [=]{
                if (!internalAdjust) {
                    bool doIt = false;
                    if (!speedSlider->getValueIsAdjusting()) {
                        doIt = true;
                    } else if (/*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() - lastTrackedSliderMovementTime >= trackSliderMinInterval) {
                        doIt = true;
                        lastTrackedSliderMovementTime = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch();
                    }
                    if (doIt) {
                        float newSpeed = (speedSlider->getValue() / (MAX_SPEED * 1.0f));
                        if (log->isDebugEnabled()) {
                            log->debug(tr("stateChanged: slider pos: %1 speed: %2").arg(speedSlider->getValue()).arg(newSpeed));
                        }
                        _throttle->setSpeedSetting(newSpeed);
                        if (speedSpinner != nullptr) {
                            speedSpinnerModel->setValue(/*Integer.valueOf*/(speedSlider->getValue()));
                        }
                    }
                } else {
                    internalAdjust = false;
                }
        });

        spinnerPanel = new JPanel();
        GridBagLayout* spinnerPanelLayout;
        spinnerPanel->setLayout(spinnerPanelLayout = new GridBagLayout());

        if (speedSpinner != nullptr) {
            spinnerPanelLayout->addWidget(speedSpinner, constraints);
        }
        speedControlPanel->layout()->addWidget(spinnerPanel);
        // remove old actions
        if (speedSpinner != nullptr) {
//            speedSpinner.addChangeListener((ChangeEvent e) -> {
         connect(speedSpinner, static_cast<void (QSpinBox::*)(int)>(&JSpinner::valueChanged), [=]{
                    if (!internalAdjust) {
                        float newSpeed = (/*(Integer)*/ speedSpinner->getValue()) / (MAX_SPEED * 1.0f);
                        if (log->isDebugEnabled()) {
                            log->debug(tr("stateChanged: spinner pos: %1 speed: %2").arg(speedSpinner->getValue()).arg(newSpeed));
                        }
                        _throttle->setSpeedSetting(newSpeed);
                        speedSlider->setValue((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/);
                    } else {
                        internalAdjust = false;
                    }
            });
        }

        QButtonGroup* speedStepButtons = new QButtonGroup();
        speedStepButtons->addButton(speedStep128Button);
        speedStepButtons->addButton(speedStep28Button);
        speedStepButtons->addButton(speedStep27Button);
        speedStepButtons->addButton(speedStep14Button);
        constraints.fill = GridBagConstraints::NONE;
        constraints.gridy = 1;
        spinnerPanelLayout->addWidget(speedStep128Button, constraints);
        constraints.gridy = 2;
        spinnerPanelLayout->addWidget(speedStep28Button, constraints);
        constraints.gridy = 3;
        spinnerPanelLayout->addWidget(speedStep27Button, constraints);
        constraints.gridy = 4;
        spinnerPanelLayout->addWidget(speedStep14Button, constraints);

        //speedStep14Button.addActionListener((ActionEvent e) -> {
        connect(speedStep14Button, &QRadioButton::clicked, [=]{
                setSpeedSteps(new SpeedStepMode(SpeedStepMode::NMRA_DCC_14));
                _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_14);
        });

        //speedStep27Button.addActionListener((ActionEvent e) -> {
        connect(speedStep27Button, &QRadioButton::clicked, [=]{
                setSpeedSteps(new SpeedStepMode(SpeedStepMode::NMRA_DCC_27));
                _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_27);
        });

        //speedStep28Button.addActionListener((ActionEvent e) -> {
        connect(speedStep28Button, &QRadioButton::clicked, [=]{
                setSpeedSteps(new SpeedStepMode(SpeedStepMode::NMRA_DCC_28));
                _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_28);
        });

//        speedStep128Button.addActionListener((ActionEvent e) -> {
        connect(speedStep128Button, &QRadioButton::clicked, [=]{
                setSpeedSteps(new SpeedStepMode(SpeedStepMode::NMRA_DCC_128));
                _throttle->setSpeedStepMode(SpeedStepMode::NMRA_DCC_128);
        });
        // set by default which speed selection method is on top
        setSpeedController(_displaySlider);
    }

    /*public*/ void LTFControlPanel::accelerate1() {
        if (speedSlider->isEnabled()) {
            if (speedSlider->getValue() != speedSlider->maximum()) {
                speedSlider->setValue(speedSlider->getValue() + 1);
            }
        } else if (speedSpinner != nullptr && speedSpinner->isEnabled()) {
            if ((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ < (/*(Integer)*/ speedSpinnerModel->getMaximum().toInt())
                    && (/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ >= (/*(Integer)*/ speedSpinnerModel->getMinimum().toInt())) {
                speedSpinner->setValue(/*Integer.valueOf*/((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ + 1));
            }
        }
    }

    /*public*/ void LTFControlPanel::accelerate10() {
        if (speedSlider->isEnabled()) {
            if (speedSlider->getValue() != speedSlider->maximum()) {
                speedSlider->setValue(speedSlider->getValue() + 10);
            }
        } else if (speedSpinner != nullptr && speedSpinner->isEnabled()) {
            if ((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ < (/*(Integer)*/ speedSpinnerModel->getMaximum().toInt())
                    && (/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ >= (/*(Integer) */speedSpinnerModel->getMinimum().toInt())) {
                int speedvalue = /*Integer.valueOf*/((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ + 10);
                if (speedvalue/*.intValue()*/ < (/*(Integer)*/ speedSpinnerModel->getMaximum().toInt())) {
                    speedSpinner->setValue(speedvalue);
                } else {
                    speedSpinner->setValue(speedSpinnerModel->getMaximum().toInt());
                }
            }
        }
    }

    /*public*/ void LTFControlPanel::decelerate1() {
        if (speedSlider->isEnabled()) {
            if (speedSlider->getValue() != speedSlider->minimum()) {
                speedSlider->setValue(speedSlider->getValue() - 1);
            }
        } else if (speedSpinner != nullptr && speedSpinner->isEnabled()) {
            if ((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ <= (/*(Integer)*/ speedSpinnerModel->getMaximum().toInt())
                    && (/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ > (/*(Integer)*/ speedSpinnerModel->getMinimum().toInt()))
            {
                speedSpinner->setValue(/*Integer.valueOf*/((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ - 1));
            }
        }
    }

    /*public*/ void LTFControlPanel::decelerate10() {
        if (speedSlider->isEnabled()) {
            if (speedSlider->getValue() != speedSlider->minimum()) {
                speedSlider->setValue(speedSlider->getValue() - 10);
            }
        } else if (speedSpinner != nullptr && speedSpinner->isEnabled()) {
            if ((/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ <= (/*(Integer)*/ speedSpinnerModel->getMaximum().toInt())
                    && (/*(Integer)*/ speedSpinner->getValue())/*.intValue()*/ > (/*(Integer)*/ speedSpinnerModel->getMinimum().toInt())) {
                int speedvalue = /*Integer.valueOf*/((/*(Integer)*/ speedSpinner->getValue())/*.intValue() */- 10);
                if (speedvalue/*.intValue()*/ > (/*(Integer) */speedSpinnerModel->getMinimum().toInt())) {
                    speedSpinner->setValue(speedvalue);
                } else {
                    speedSpinner->setValue(speedSpinnerModel->getMinimum().toInt());
                }
            }
        }
    }

    /**
     * Configure the active Speed Step modes based on what is supported by the
     * DCC system
     */
    /*private*/ void LTFControlPanel::configureAvailableSpeedStepModes() {
        //EnumSet<SpeedStepMode> modes = InstanceManager::throttleManagerInstance()->supportedSpeedModes();
 int modes = InstanceManager::throttleManagerInstance()->supportedSpeedModes();
            speedStep128Button->setEnabled(modes&(SpeedStepMode::NMRA_DCC_128));
            speedStep28Button->setEnabled(modes&(SpeedStepMode::NMRA_DCC_28));
            speedStep27Button->setEnabled(modes&(SpeedStepMode::NMRA_DCC_27));
            speedStep14Button->setEnabled(modes&(SpeedStepMode::NMRA_DCC_14));
    }

    // initialize logging
    /*private*/ /*static*/ /*final*/ Logger* LTFControlPanel::log = LoggerFactory::getLogger("ControlPanel");
