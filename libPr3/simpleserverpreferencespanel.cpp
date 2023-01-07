#include "simpleserverpreferencespanel.h"
#include "simpleserverpreferences.h"
#include "simpleservermanager.h"
#include <QBoxLayout>
#include "jtitledseparator.h"
#include "box.h"
#include "jspinner.h"
#include "joptionpane.h"
#include "jframe.h"

/**
 * @author Randall Wood Copyright (C) 2012
 */
//@ServiceProvider(service = PreferencesPanel.class)
// /*public*/  class SimpleServerPreferencesPanel extends JPanel implements PreferencesPanel {


/*public*/ SimpleServerPreferencesPanel::SimpleServerPreferencesPanel(JPanel *parent) : JPanel(parent){
 common();
}
void SimpleServerPreferencesPanel::common()
{
    this->preferences = new SimpleServerPreferences();
    this->preferences->apply(SimpleServerManager::getSimpleServerPreferences());
    initGUI();
    setGUI();
}

/*public*/  SimpleServerPreferencesPanel::SimpleServerPreferencesPanel(JFrame* f) {
    //this();
    common();
    parentFrame = f;
}

/*private*/ void SimpleServerPreferencesPanel::initGUI() {
    this->setLayout(new QVBoxLayout());//this, BoxLayout.PAGE_AXIS));
    this->layout()->addWidget(new JTitledSeparator(tr("ServerSectionTitle")));
    this->layout()->addWidget(portPanel());
    this->layout()->addWidget(new JTitledSeparator(tr("SimpleServerSectionTitle")));
    this->layout()->addWidget(Box::createVerticalGlue());
}

/*private*/ void SimpleServerPreferencesPanel::setGUI() {
    port->setValue(preferences->getPort());
}

/**
 * set the local prefs to match the GUI Local prefs are independent from the
 * singleton instance prefs.
 *
 * @return true if set, false if values are unacceptable.
 */
/*private*/ bool SimpleServerPreferencesPanel::setValues() {
    bool didSet = true;
    int portNum;
    try {
     bool ok;
        portNum = port->getValue();
        if(!ok) throw new NumberFormatException();
    } catch (NumberFormatException* NFE) { //  Not a number
        portNum = 0;
    }
    if ((portNum < 1) || (portNum > 65535)) { //  Invalid port value
        JOptionPane::showMessageDialog(this,
                tr("InvalidPortWarningMessage"),
                tr("InvalidPortWarningTitle"),
                JOptionPane::WARNING_MESSAGE);
        didSet = false;
    } else {
        preferences->setPort(portNum);
    }
    return didSet;
}

/**
 * Update the singleton instance of prefs, then mark (isDirty) that the
 * values have changed and needs to save to xml file.
 */
/*protected*/ void SimpleServerPreferencesPanel::applyValues() {
    this->setValues();
}

/*protected*/ void SimpleServerPreferencesPanel::cancelValues() {
    //java.awt.Container ancestor = getTopLevelAncestor();
//    if (ancestor instanceof JFrame) {
 if(qobject_cast<JFrame*>(window())) {
        ((JFrame*) window())->setVisible(false);
    }
}

/*private*/ JPanel* SimpleServerPreferencesPanel::portPanel() {
    JPanel* panel = new JPanel(new FlowLayout());
    port = new JSpinner(new SpinnerNumberModel(preferences->getPort(), 1, 65535, 1));
//    ((JSpinner.DefaultEditor) port.getEditor()).getTextField().setEditable(true);
//    port.setEditor(new JSpinner.NumberEditor(port, "#"));
//    this.port.addChangeListener((ChangeEvent e) -> this.setValues());
    this->port->setToolTip(tr("PortToolTip"));
    panel->layout()->addWidget(port);
    panel->layout()->addWidget(new JLabel(tr("Port")));
    return panel;
}

//@Override
/*public*/  QString SimpleServerPreferencesPanel::getPreferencesItem() {
    return tr("PreferencesItem");
}

//@Override
/*public*/  QString SimpleServerPreferencesPanel::getPreferencesItemText() {
    return tr("PreferencesItemTitle");
}

//@Override
/*public*/  QString SimpleServerPreferencesPanel::getTabbedPreferencesTitle() {
    return tr("PreferencesTabTitle");
}

//@Override
/*public*/  QString SimpleServerPreferencesPanel::getLabelKey() {
    return QString();
}

//@Override
/*public*/  QWidget* SimpleServerPreferencesPanel::getPreferencesComponent() {
    return this;
}

//@Override
/*public*/  bool SimpleServerPreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/  QString SimpleServerPreferencesPanel::getPreferencesTooltip() {
    return tr("PreferencesTooltip");
}

//@Override
/*public*/  void SimpleServerPreferencesPanel::savePreferences() {
    if (this->setValues()) {
        SimpleServerManager::getSimpleServerPreferences()->apply(this->preferences);
        SimpleServerManager::getSimpleServerPreferences()->save();
        if (this->parentFrame != nullptr) {
            this->parentFrame->dispose();
        }
    }
}

//@Override
/*public*/  bool SimpleServerPreferencesPanel::isDirty() {
    return this->preferences->compareValuesDifferent(SimpleServerManager::getSimpleServerPreferences())
            || SimpleServerManager::getSimpleServerPreferences()->isDirty();
}

//@Override
/*public*/  bool SimpleServerPreferencesPanel::isRestartRequired() {
    return SimpleServerManager::getSimpleServerPreferences()->isRestartRequired();
}

/**
 * Indicate that the preferences are valid.
 *
 * @return true if the preferences are valid, false otherwise
 */
//@Override
/*public*/  bool SimpleServerPreferencesPanel::isPreferencesValid() {
    return true;
}

/*public*/ QString SimpleServerPreferencesPanel::className()
{
 return "jmri.jmrix.simpleserver.SimpleServerPreferencesPanel";
}
