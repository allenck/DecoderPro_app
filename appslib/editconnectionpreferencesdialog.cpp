#include "editconnectionpreferencesdialog.h"
#include "editconnectionpreferences.h"
#include "tabbedpreferences.h"
#include "instancemanager.h"
#include <QBoxLayout>
#include "jframe.h"
#include "preferencespanel.h"
#include "joptionpane.h"

//EditConnectionPreferencesDialog::EditConnectionPreferencesDialog(QWidget *parent)
//{

//}
/**
 * Provide a preferences dialog.
 *
 * @author Kevin Dickerson Copyright 2010
 */
// /*public*/ /*final*/ class EditConnectionPreferencesDialog extends JDialog implements WindowListener {


//@Override
/*public*/ QString EditConnectionPreferencesDialog::getTitle() {
    return editConnectionPreferences->getTitle();
}

/*public*/ bool EditConnectionPreferencesDialog::isMultipleInstances() {
    return true;
}

/**
 * Displays a dialog for editing the conenctions.
 * @return true if the program should restart, false if the program should quit.
 */
/*public*/ /*static*/ bool EditConnectionPreferencesDialog::showDialog() {
    try {
        while (static_cast<TabbedPreferences*>(InstanceManager::getDefault("TabbedPreferences"))->init() != TabbedPreferences::INITIALISED) {
#if 0
            /*final*/ Object waiter = new Object();
            synchronized (waiter) {
                waiter.wait(50);
            }
#endif
        }

        EditConnectionPreferencesDialog* dialog = new EditConnectionPreferencesDialog();
//        SwingUtilities.updateComponentTreeUI(dialog);

        dialog->pack();
        dialog->setVisible(true);
        return dialog->restartProgram;
    } catch (InterruptedException ex) {
//        Thread.currentThread().interrupt();
        return false;
    }
}

/*public*/ EditConnectionPreferencesDialog::EditConnectionPreferencesDialog(QWidget *parent)  : JDialog(parent){
    //super();
    setModal(true);
    setLayout(new QVBoxLayout());
    editConnectionPreferences = new EditConnectionPreferences(this);
    editConnectionPreferences->init();
    layout()->addWidget(editConnectionPreferences);
//        addHelpMenu("package.apps.TabbedPreferences", true); // NOI18N
    setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    addWindowListener((WindowListener*)this);
}

/*public*/ void EditConnectionPreferencesDialog::gotoPreferenceItem(QString item, QString sub) {
    editConnectionPreferences->gotoPreferenceItem(item, sub);
}

//@Override
/*public*/ void EditConnectionPreferencesDialog::windowClosing(QCloseEvent* e) {
    ShutDownManager* sdm = static_cast<ShutDownManager*>(InstanceManager::getNullableDefault("ShutDownManager"));
    if (!editConnectionPreferences->isPreferencesValid() && (sdm == nullptr || !sdm->isShuttingDown())) {
        for (PreferencesPanel* panel : editConnectionPreferences->getPreferencesPanels()->values()) {
            if (!panel->isPreferencesValid()) {
                switch (JOptionPane::showConfirmDialog(this,
                        tr("<html><b>The %1 preferences are invalid.</b><br>Do you want to correct them?</html>").arg(panel->getTabbedPreferencesTitle()),
                        tr("Invalid Preferences"),
                        JOptionPane::YES_NO_OPTION,
                        JOptionPane::ERROR_MESSAGE)) {
                    case JOptionPane::YES_OPTION:
                        // abort window closing and return to broken preferences
                        editConnectionPreferences->gotoPreferenceItem(panel->getPreferencesItem(), panel->getTabbedPreferencesTitle());
                        return;
                    default:
                        // do nothing
                        break;
                }
            }
        }
    }
    if (editConnectionPreferences->isDirty()) {
        switch (JOptionPane::showConfirmDialog(this,
                tr("UnsavedChangesMessage %1").arg(editConnectionPreferences->getTitle()), // NOI18N
                tr("Unsaved Changes"), // NOI18N
                JOptionPane::YES_NO_CANCEL_OPTION,
                JOptionPane::QUESTION_MESSAGE) )
        {
            case JOptionPane::YES_OPTION:
                // save preferences
                editConnectionPreferences->savePressed(editConnectionPreferences->invokeSaveOptions());
                break;
            case JOptionPane::NO_OPTION:
                // do nothing
                break;
            case JOptionPane::CANCEL_OPTION:
            default:
                // abort window closing
                return;
        }
    }
    this->setVisible(false);
}
#if 0
@Override
/*public*/ void windowOpened(WindowEvent e) {
}

@Override
/*public*/ void windowClosed(WindowEvent e) {
}

@Override
/*public*/ void windowIconified(WindowEvent e) {
}

@Override
/*public*/ void windowDeiconified(WindowEvent e) {
}

@Override
/*public*/ void windowActivated(WindowEvent e) {
}

@Override
/*public*/ void windowDeactivated(WindowEvent e) {
}
}
#endif
