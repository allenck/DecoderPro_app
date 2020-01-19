#include "jsonserverpreferencespanel.h"
#include "jsonserverpreferences.h"
#include <QSpinBox>
#include <QPushButton>
#include "jframe.h"
#include "jtitledseparator.h"
#include <QBoxLayout>
#include "box.h"
#include <QLabel>
/**
 * @author Randall Wood Copyright (C) 2012, 2015
 */
// /*public*/ class JsonServerPreferencesPanel extends JPanel implements PreferencesPanel {

/*public*/ /*static*/ /*final*/ int JsonServerPreferencesPanel::MAX_HEARTBEAT_INTERVAL = 3600;
/*public*/ /*static*/ /*final*/ int JsonServerPreferencesPanel::MIN_HEARTBEAT_INTERVAL = 1;

/*public*/JsonServerPreferencesPanel:: JsonServerPreferencesPanel(QWidget* parent) : QWidget(parent)
{
 parentFrame = NULL;
    this->preferences = new JsonServerPreferences();
    this->preferences->apply(JsonServerPreferences::getDefault());
    initGUI();
    setGUI();
}

/*public*/ JsonServerPreferencesPanel::JsonServerPreferencesPanel(JFrame* f, QWidget* parent) : QWidget(parent)
 {
    //this();
    parentFrame = f;
}

/*private*/ void JsonServerPreferencesPanel::initGUI() {
 QVBoxLayout* thisLayout;
    this->setLayout(thisLayout = new QVBoxLayout()); //this, BoxLayout.PAGE_AXIS));
    thisLayout->addWidget(new JTitledSeparator(tr("Server")));
    thisLayout->addWidget(portPanel());
    thisLayout->addWidget(new JTitledSeparator(tr("JSON")));
    thisLayout->addWidget(heartbeatPanel());
    thisLayout->addWidget(Box::createVerticalGlue());
}

/*private*/ void JsonServerPreferencesPanel::setGUI() {
    heartbeatIntervalSpinner->setValue(preferences->getHeartbeatInterval() / 1000); // convert from milliseconds to seconds
    port->setValue(preferences->getPort());
}

/**
 * Show the save and cancel buttons if displayed in its own frame.
 */
/*public*/ void JsonServerPreferencesPanel::enableSave() {
    btnSave->setVisible(true);
    btnCancel->setVisible(true);
}

/**
 * set the local prefs to match the GUI Local prefs are independent from the
 * singleton instance prefs.
 *
 * @return true if set, false if values are unacceptable.
 */
/*private*/ bool JsonServerPreferencesPanel::setValues() {
    bool didSet = true;
    preferences->setHeartbeatInterval((int) heartbeatIntervalSpinner->value() * 1000); // convert to milliseconds from seconds
    preferences->setPort((int) port->value());
    return didSet;
}

/**
 * Update the singleton instance of prefs, then mark (isDirty) that the
 * values have changed and needs to save to xml file.
 */
/*protected*/ void JsonServerPreferencesPanel::applyValues() {
    this->setValues();
}

/*protected*/ void JsonServerPreferencesPanel::cancelValues() {
    if (window() != NULL) {
        ((JFrame*) window())->setVisible(false);
    }
}

/*private*/ QWidget* JsonServerPreferencesPanel::heartbeatPanel() {
    QWidget* panel = new QWidget();
    QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    heartbeatIntervalSpinner = new QSpinBox(/*new SpinnerNumberModel(15, MIN_HEARTBEAT_INTERVAL, MAX_HEARTBEAT_INTERVAL, 1)*/);
    heartbeatIntervalSpinner->setMinimum(MIN_HEARTBEAT_INTERVAL);
    heartbeatIntervalSpinner->setMaximum(MAX_HEARTBEAT_INTERVAL);
    heartbeatIntervalSpinner->setSingleStep(1);
    heartbeatIntervalSpinner->setValue(15);
//    ((JSpinner.DefaultEditor) heartbeatIntervalSpinner.getEditor()).getTextField().setEditable(true);
//    this->heartbeatIntervalSpinner.addChangeListener((ChangeEvent e) ->
//    {
//        this->setValues();
//    });
    connect(heartbeatIntervalSpinner, SIGNAL(valueChanged(int)), this, SLOT(setValues()));
    this->heartbeatIntervalSpinner->setToolTip(tr("<html>The number of seconds between keep-alive messages.<br>The heartbeat interval must be between %1 and %2 seconds.</html>").arg(MIN_HEARTBEAT_INTERVAL).arg( MAX_HEARTBEAT_INTERVAL));
    panelLayout->addWidget(heartbeatIntervalSpinner);
    QLabel* label = new QLabel(tr("Heartbeat Interval"));
    label->setToolTip(this->heartbeatIntervalSpinner->toolTip());
    panelLayout->addWidget(label);
    return panel;
}

/*private*/ QWidget* JsonServerPreferencesPanel::portPanel() {
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
    port = new QSpinBox(/*new SpinnerNumberModel(JsonServerPreferences::DEFAULT_PORT, 1, 65535, 1)*/);
    port->setMinimum(1);
    port->setMaximum(65535);
    port->setSingleStep(1);
    port->setValue(JsonServerPreferences::DEFAULT_PORT);
//    ((JSpinner.DefaultEditor) port.getEditor()).getTextField().setEditable(true);
//    port.setEditor(new JSpinner.NumberEditor(port, "#"));
//    this->port.addChangeListener((ChangeEvent e) -> {
//        this->setValues();
//    });
    connect(port, SIGNAL(valueChanged(int)), this, SLOT(setValues()));
    this->port->setToolTip(tr("<html>The port to listen for new connections on.<br>The port must be between 1 and 65535, and cannot be used by another application or service.</html>"));
    panelLayout->addWidget(port);
    QLabel* label = new QLabel(tr("Port Number"));
    label->setToolTip(this->port->toolTip());
    panelLayout->addWidget(label);
    return panel;
}

//@Override
/*public*/ QString JsonServerPreferencesPanel::getPreferencesItem() {
    return tr("NETWORKSERVICES");
}

//@Override
/*public*/ QString JsonServerPreferencesPanel::getPreferencesItemText() {
    return tr("JSON");
}

//@Override
/*public*/ QString JsonServerPreferencesPanel::getTabbedPreferencesTitle() {
    return tr("JSON Server");
}

//@Override
/*public*/ QString JsonServerPreferencesPanel::getLabelKey() {
    return NULL;
}

//@Override
/*public*/ QWidget* JsonServerPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/ bool JsonServerPreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString JsonServerPreferencesPanel::getPreferencesTooltip() {
    return tr("Set preferences for the JSON Server");
}

//@Override
/*public*/ void JsonServerPreferencesPanel::savePreferences() {
    if (this->setValues()) {
        JsonServerPreferences::getDefault()->apply(this->preferences);
        JsonServerPreferences::getDefault()->save();
        if (this->parentFrame != NULL) {
            this->parentFrame->dispose();
        }
    }
}

//@Override
/*public*/ bool JsonServerPreferencesPanel::isDirty() {
    return this->preferences->compareValuesDifferent(JsonServerPreferences::getDefault())
            || JsonServerPreferences::getDefault()->isDirty();
}

//@Override
/*public*/ bool JsonServerPreferencesPanel::isRestartRequired() {
    return JsonServerPreferences::getDefault()->isRestartRequired();
}

//@Override
/*public*/ bool JsonServerPreferencesPanel::isPreferencesValid() {
    return true; // no validity checking performed
}

/*public*/ QString JsonServerPreferencesPanel::className() {return "jmri.server.json.JsonServerPreferencesPanel";}

