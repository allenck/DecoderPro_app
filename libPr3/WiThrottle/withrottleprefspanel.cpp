#include "withrottleprefspanel.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QRadioButton>
#include "withrottlepreferences.h"
#include "jframe.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "jtitledseparator.h"
#include "joptionpane.h"
#include "spinnernumbermodel.h"
#include <QLabel>
#include <QButtonGroup>
#include <QBoxLayout>
#include "startupactionsmanager.h"

/**
 * @author Brett Hoffman Copyright (C) 2010
 */
///*public*/ class WiThrottlePrefsPanel extends QWidget* implements PreferencesPanel {


/*public*/ WiThrottlePrefsPanel::WiThrottlePrefsPanel(QWidget* parent) : QWidget(parent)
{
 common();
}
void WiThrottlePrefsPanel::common()
{
 startupActionPosition = -1;
 parentFrame = NULL;

    if (InstanceManager::getNullableDefault("WiThrottlePreferences") == NULL) {
        InstanceManager::store(new WiThrottlePreferences(FileUtil::getUserFilesPath() + "throttle" + File::separator + "WiThrottlePreferences.xml"), "WiThrottlePreferences");
    }
    localPrefs = (WiThrottlePreferences*)InstanceManager::getDefault("WiThrottlePreferences");
    initGUI();
    setGUI();
}

/*public*/ WiThrottlePrefsPanel::WiThrottlePrefsPanel(JFrame* f, QWidget* parent) : QWidget(parent) {
    //this();
 common();
    parentFrame = f;
}

/*public*/ void WiThrottlePrefsPanel::initGUI() {
 QVBoxLayout* thisLayout;
    setLayout(thisLayout = new QVBoxLayout()); //this, BoxLayout.PAGE_AXIS));
    thisLayout->addWidget(new JTitledSeparator(tr("eStop")));
    thisLayout->addWidget(eStopDelayPanel());
    thisLayout->addWidget(new JTitledSeparator(tr("Function Buttons")));
    thisLayout->addWidget(functionsPanel());
    thisLayout->addWidget(new JTitledSeparator(tr("Network")));
    thisLayout->addWidget(socketPortPanel());
    thisLayout->addWidget(new JTitledSeparator(tr("Allowed Controls")));
    thisLayout->addWidget(allowedControllers());
}

/*private*/ void WiThrottlePrefsPanel::setGUI() {
    eStopCB->setChecked(localPrefs->isUseEStop());
    delaySpinner->setValue(localPrefs->getEStopDelay());

    momF2CB->setChecked(localPrefs->isUseMomF2());

    port->setValue(localPrefs->getPort());
    powerCB->setChecked(localPrefs->isAllowTrackPower());
    turnoutCB->setChecked(localPrefs->isAllowTurnout());
    routeCB->setChecked(localPrefs->isAllowRoute());
    consistCB->setChecked(localPrefs->isAllowConsist());
//    InstanceManager::getDefault("StartupActionsManager")->PropertyChangeSupport::addPropertyChangeListener((PropertyChangeEvent* evt) -> {
//        startupCB->setChecked(isStartUpAction());
//    });
    wifiRB->setChecked(localPrefs->isUseWiFiConsist());
    dccRB->setChecked(!localPrefs->isUseWiFiConsist());
}

/**
 * set the local prefs to match the GUI Local prefs are independant from the
 * singleton instance prefs.
 *
 * @return true if set, false if values are unacceptable.
 */
/*private*/ bool WiThrottlePrefsPanel::setValues() {
    bool didSet = true;
    localPrefs->setUseEStop(eStopCB->isChecked());
    localPrefs->setEStopDelay( delaySpinner->value());

    localPrefs->setUseMomF2(momF2CB->isChecked());

    int portNum;
    try {
        portNum = (int) port->value();
    } catch (NumberFormatException* NFE) { //  Not a number
        portNum = 0;
    }
    if ((portNum < 1) || (portNum > 65535)) { //  Invalid port value
        JOptionPane::showMessageDialog(this,
                tr("WarningInvalidPort"),
                tr("TitlePortWarningDialog"),
                JOptionPane::WARNING_MESSAGE);
        didSet = false;
    } else {
        localPrefs->setPort((int) port->value());
    }

    localPrefs->setAllowTrackPower(powerCB->isChecked());
    localPrefs->setAllowTurnout(turnoutCB->isChecked());
    localPrefs->setAllowRoute(routeCB->isChecked());
    localPrefs->setAllowConsist(consistCB->isChecked());
    localPrefs->setUseWiFiConsist(wifiRB->isChecked());

    return didSet;
}

/*public*/ void WiThrottlePrefsPanel::storeValues() {
    if (setValues()) {
        this->localPrefs->save();

        if (parentFrame != NULL) {
            parentFrame->dispose();
        }
    }

}

/*protected*/ void WiThrottlePrefsPanel::cancelValues() {
    if (window() != NULL) {
        ((JFrame*) window())->setVisible(false);
    }
}

/*private*/ QWidget* WiThrottlePrefsPanel::eStopDelayPanel() {
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    eStopCB = new QCheckBox(tr("Use eStop"));
    eStopCB->setToolTip(tr("On to stop selected loco, if connection is lost"));
    SpinnerNumberModel* spinMod = new SpinnerNumberModel(10, 4, 60, 2);
    delaySpinner = new QSpinBox(/*spinMod*/);
    delaySpinner->setMinimum(spinMod->getMinimum().toInt());
    delaySpinner->setMaximum(spinMod->getMaximum().toInt());
    delaySpinner->setSingleStep(spinMod->getStepSize().toInt());
    delaySpinner->setValue(spinMod->getValue().toInt());

//    ((JSpinner.DefaultEditor) delaySpinner.getEditor()).getTextField().setEditable(false);
    panelLayout->addWidget(eStopCB);
    panelLayout->addWidget(delaySpinner);
    panelLayout->addWidget(new QLabel(tr("Seconds until eStop")));
    return panel;
}

/*private*/ QWidget* WiThrottlePrefsPanel::functionsPanel() {
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);

    momF2CB = new QCheckBox(tr("F2 always momentary"));
    momF2CB->setToolTip(tr("Off sets F2 to follow \"lock\" action set in each roster entry's function labels"));
    panelLayout->addWidget(momF2CB);
    return panel;
}

/*private*/ QWidget* WiThrottlePrefsPanel::socketPortPanel() {
    QWidget* SPPanel = new QWidget();
    QHBoxLayout* SPPanelLayout = new QHBoxLayout(SPPanel);

    port = new QSpinBox(); //new SpinnerNumberModel(localPrefs->getPort(), 1, 65535, 1));
    port->setMinimum(1);
    port->setMaximum(65535);
    port->setSingleStep(1);
    port->setValue(localPrefs->getPort());
    port->setToolTip(tr("<html>The port to listen for new connections on.<br>The port must be between 1 and 65535, and cannot be used by another application or service.</html>"));
//    port->setEditor(new JSpinner.NumberEditor(port, "#"));
    QLabel* label = new QLabel(tr("Port Number"));
    label->setToolTip(port->toolTip());
    SPPanelLayout->addWidget(port);
    SPPanelLayout->addWidget(label);
    startupCB = new QCheckBox(tr("Start automatically with application")); //, isStartUpAction());
    startupCB->setChecked(isStartUpAction());
#if 0
    startupItemListener = (ItemEvent e) -> {
        this->startupCB.removeItemListener(this->startupItemListener);
        StartupActionsManager manager = InstanceManager.getDefault(StartupActionsManager.class);
        if (this->startupCB->isChecked()) {
            PerformActionModel model = new PerformActionModel();
            model.setClassName(WiThrottleCreationAction.class.getName());
            if (this->startupActionPosition == -1 || this->startupActionPosition >= manager.getActions().length) {
                manager.addAction(model);
            } else {
                manager.setActions(this->startupActionPosition, model);
            }
        } else {
            manager.getActions(PerformActionModel.class).stream().filter((model) -> (WiThrottleCreationAction.class.getName().equals(model.getClassName()))).forEach((model) -> {
                this->startupActionPosition = Arrays.asList(manager.getActions()).indexOf(model);
                manager.removeAction(model);
            });
        }
        this->startupCB.addItemListener(this->startupItemListener);
    };

    this->startupCB.addItemListener(this->startupItemListener);
#endif
    SPPanelLayout->addWidget(startupCB);
    return SPPanel;
}

/*private*/ QWidget* WiThrottlePrefsPanel::allowedControllers() {
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);

    powerCB = new QCheckBox(tr("Track Power"));
    powerCB->setToolTip(tr("Allow Wi-Fi devices to control track power"));
    panelLayout->addWidget(powerCB);

    turnoutCB = new QCheckBox(tr("Turnouts"));
    turnoutCB->setToolTip(tr("Allow Wi-Fi devices to control turnouts"));
    panelLayout->addWidget(turnoutCB);

    routeCB = new QCheckBox(tr("Routes"));
    routeCB->setToolTip(tr("Allow Wi-Fi devices to control routes"));
    panelLayout->addWidget(routeCB);

    consistCB = new QCheckBox(tr("Consists"));
    consistCB->setToolTip(tr("ToolTipConsist"));
    panelLayout->addWidget(consistCB);

    QWidget* conPanel = new QWidget();
    QVBoxLayout* conPanelLayout;
    conPanel->setLayout(conPanelLayout = new QVBoxLayout()); //(conPanel, BoxLayout.Y_AXIS));
    wifiRB = new QRadioButton(tr("NMRA Format"));
    wifiRB->setToolTip(tr("Consists perform better on WiFi throttles"));
    dccRB = new QRadioButton(tr("DCC Brand-Specific"));
    dccRB->setToolTip(tr("Consists perform better on DCC manufacturer's throttles"));

    QButtonGroup* group = new QButtonGroup();
    group->addButton(wifiRB);
    group->addButton(dccRB);
    conPanelLayout->addWidget(wifiRB);
    conPanelLayout->addWidget(dccRB);
    panelLayout->addWidget(conPanel);

    return panel;
}

///*private*/ final static Logger log = LoggerFactory.getLogger(WiThrottlePrefsPanel.class.getName());
//@Override
/*public*/ QString WiThrottlePrefsPanel::getPreferencesItem() {
    return "WITHROTTLE"; // NOI18N
}

//@Override
/*public*/ QString WiThrottlePrefsPanel::getPreferencesItemText() {
    // TODO: migrate to local resource bundle
    return tr("WiThrottle"); // NOI18N
}

//@Override
/*public*/ QString WiThrottlePrefsPanel::getTabbedPreferencesTitle() {
    return NULL;
}

//@Override
/*public*/ QString WiThrottlePrefsPanel::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* WiThrottlePrefsPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool WiThrottlePrefsPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString WiThrottlePrefsPanel::getPreferencesTooltip() {
    return NULL;
}

//@Override
/*public*/ void WiThrottlePrefsPanel::savePreferences() {
    this->storeValues();
}

//@Override
/*public*/ bool WiThrottlePrefsPanel::isDirty() {
    return this->localPrefs->isDirty();
}

//@Override
/*public*/ bool WiThrottlePrefsPanel::isRestartRequired() {
    return this->localPrefs->isRestartRequired();
}

//@Override
/*public*/ bool WiThrottlePrefsPanel::isPreferencesValid() {
    return true; // no validity checking performed
}

/*private*/ bool WiThrottlePrefsPanel::isStartUpAction()
{
//    return ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->getActions("PerformActionModel").stream()
//            .anyMatch((model) -> ("WiThrottleCreationAction" ==(model.getClassName())));

//        for (PerformActionModel model : InstanceManager.getDefault(StartupActionsManager.class).getActions(PerformActionModel.class)) {
//            if (WiThrottleCreationAction.class.getName().equals(model.getClassName()))) {
//                return true;
//            }
//        }
        return false;
}

/*public*/ QString WiThrottlePrefsPanel::className() {return "jmri.jmrit.throttle.WiThrottlePrefsPanel";}
