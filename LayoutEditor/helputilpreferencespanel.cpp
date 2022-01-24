#include "helputilpreferencespanel.h"
#include "instancemanager.h"
#include <QGridLayout>

/**
 * Preferences panel for HelpUtil
 *
 * @author Daniel Bergqvist Copyright 2021
 */
//@ServiceProvider(service = PreferencesPanel.class)
///*public*/ class HelpUtilPreferencesPanel extends JPanel implements PreferencesPanel {


    /*public*/ HelpUtilPreferencesPanel::HelpUtilPreferencesPanel(QWidget *parent) : JPanel(parent)
    {
        _preferences = (HelpUtilPreferences*)InstanceManager::getDefault("HelpUtilPreferences");
        initGUI();
    }

    /*private*/ void HelpUtilPreferencesPanel::initGUI() {
        setLayout(new QVBoxLayout());//this, BoxLayout.PAGE_AXIS));
        layout()->addWidget(getHelpPanel());
    }

    /**
     * set the local prefs to match the GUI Local prefs are independent from the
     * singleton instance prefs.
     *
     * @return true if set, false if values are unacceptable.
     */
    /*private*/ bool HelpUtilPreferencesPanel::setValues() {
        bool didSet = true;
        _preferences->setOpenHelpOnFile(_openHelpOnFileRadioButton->isChecked());
        _preferences->setOpenHelpOnline(_openHelpOnlineRadioButton->isChecked());
        _preferences->setOpenHelpOnJMRIWebServer(_openHelpOnJMRIWebServerRadioButton->isChecked());
        return didSet;
    }

    /*private*/ JPanel* HelpUtilPreferencesPanel::getHelpPanel() {
        JPanel* panel = new JPanel();

        _openHelpButtonGroup = new QButtonGroup();

        _openHelpOnFileRadioButton = new QRadioButton(tr("Open help pages locally"));
        _openHelpOnFileRadioButton->setToolTip(tr("This works without an Internet connection"));
        _openHelpButtonGroup->addButton(_openHelpOnFileRadioButton);

        _openHelpOnlineRadioButton = new QRadioButton(tr("Open help pages online"));
        _openHelpOnlineRadioButton->setToolTip(tr("This requires Internet access"));
        _openHelpButtonGroup->addButton(_openHelpOnlineRadioButton);

        _openHelpOnJMRIWebServerRadioButton = new QRadioButton(tr("Open help pages using the web server in JMRI (Experimental. Not recommended)"));
        _openHelpOnJMRIWebServerRadioButton->setToolTip(tr("This option is for developers only."));
        _openHelpButtonGroup->addButton(_openHelpOnJMRIWebServerRadioButton);

        JPanel* gridPanel = new JPanel(new QGridLayout(/*0, 1*/));

        gridPanel->layout()->addWidget(_openHelpOnFileRadioButton);
        gridPanel->layout()->addWidget(_openHelpOnlineRadioButton);
        gridPanel->layout()->addWidget(_openHelpOnJMRIWebServerRadioButton);

        _openHelpOnFileRadioButton->setChecked(_preferences->getOpenHelpOnFile());
        _openHelpOnlineRadioButton->setChecked(_preferences->getOpenHelpOnline());
        _openHelpOnJMRIWebServerRadioButton->setChecked(_preferences->getOpenHelpOnJMRIWebServer());

        panel->setLayout(new FlowLayout());//FlowLayout.CENTER, 40, 0));
        panel->layout()->addWidget(gridPanel);

        return panel;
    }

    //@Override
    /*public*/ QString HelpUtilPreferencesPanel::getPreferencesItem() {
        return "HELP"; // NOI18N
    }

    //@Override
    /*public*/ QString HelpUtilPreferencesPanel::getPreferencesItemText() {
        return tr("Help"); // NOI18N
    }

    //@Override
    /*public*/ QString HelpUtilPreferencesPanel::getTabbedPreferencesTitle() {
        return getPreferencesItemText();
    }

    //@Override
    /*public*/ QString HelpUtilPreferencesPanel::getLabelKey() {
        return QString();
    }

    //@Override
    /*public*/ QWidget* HelpUtilPreferencesPanel::getPreferencesComponent() {
        return this;
    }

    //@Override
    /*public*/ bool HelpUtilPreferencesPanel::isPersistant() {
        return false;
    }

    //@Override
    /*public*/ QString HelpUtilPreferencesPanel::getPreferencesTooltip() {
        return QString();
    }

    //@Override
    /*public*/ void HelpUtilPreferencesPanel::savePreferences() {
        if (setValues()) {
            _preferences->save();
        }
    }

    //@Override
    /*public*/ bool HelpUtilPreferencesPanel::isDirty() {
        return _preferences->isDirty();
    }

    //@Override
    /*public*/ bool HelpUtilPreferencesPanel::isRestartRequired() {
        return _preferences->isRestartRequired();
    }

    //@Override
    /*public*/ bool HelpUtilPreferencesPanel::isPreferencesValid() {
        return true; // no validity checking performed
    }
