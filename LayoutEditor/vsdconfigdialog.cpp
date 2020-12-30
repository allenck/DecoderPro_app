#include "vsdconfigdialog.h"
#include "vsdecodermanager.h"
#include <QBoxLayout>
#include <QTabWidget>
#include "rosterentryselectorpanel.h"
#include "dcclocoaddressselector.h"
#include "vsdmanagerevent.h"
#include "vsdconfig.h"
#include "loadvsdfileaction.h"
#include "propertychangeevent.h"
#include <QMessageBox>
#include "instancemanager.h"
#include "globalprogrammermanager.h"
#include "defaultprogrammermanager.h"


//VSDConfigDialog::VSDConfigDialog(QWidget *parent) :
//  JDialog(parent)
//{
//}
#if 0
/**
 * class VSDConfigDialog
 *
 * Configuration dialog for setting up a new VSDecoder
 */

/*
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @author			Mark Underwood Copyright (C) 2011
 * @version			$Revision: 21510 $
 */
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import java.awt.event.KeyEvent;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import java.text.MessageFormat;
//import java.util.ArrayList;
//import java.util.HashMap;
//import java.util.Iterator;
//import java.util.Map;
//import java.util.ResourceBundle;
//import javax.swing.BorderFactory;
//import javax.swing.BoxLayout;
//import javax.swing.JButton;
//import javax.swing.JDialog;
//import javax.swing.JOptionPane;
//import javax.swing.QWidget;
//import javax.swing.JTabbedPane;
//import javax.swing.SwingUtilities;
//import javax.swing.border.TitledBorder;
//import jmri.InstanceManager;
//import jmri.Programmer;
//import jmri.jmrit.DccLocoAddressSelector;
//import jmri.jmrit.roster.Roster;
//import jmri.jmrit.roster.RosterEntry;
//import jmri.jmrit.roster.swing.RosterEntrySelectorPanel;
//import jmri.jmrit.symbolicprog.CvTableModel;
//import jmri.jmrit.symbolicprog.IndexedCvTableModel;
//import jmri.jmrit.symbolicprog.VariableTableModel;
//import jmri.jmrit.vsdecoder.LoadVSDFileAction;
//import jmri.jmrit.vsdecoder.VSDConfig;
//import jmri.jmrit.vsdecoder.VSDManagerEvent;
//import jmri.jmrit.vsdecoder.VSDManagerListener;
//import jmri.jmrit.vsdecoder.VSDecoderManager;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//@SuppressWarnings("deprecation")
// /*public*/ class VSDConfigDialog extends JDialog {

    /**
     *
     */
    /*private*/ static final long serialVersionUID = -3891269629328182031L;

    /*private*/ static /*final*/ ResourceBundle rb = VSDSwingBundle.bundle();
#endif
    /*public*/ /*static*/ /*final*/ QString VSDConfigDialog::CONFIG_PROPERTY = "Config";

    // Map of Mnemonic KeyEvent values to GUI Components
    /*private*/ /*static*/ /*final*/ QMap<QString, int> VSDConfigDialog::Mnemonics =  QMap<QString, int>();
#if 0
    static {
        Mnemonics.put("RosterTab", KeyEvent.VK_R);
        Mnemonics.put("ManualTab", KeyEvent.VK_M);
        Mnemonics.put("AddressSet", KeyEvent.VK_T);
        Mnemonics.put("ProfileLoad", KeyEvent.VK_L);
        Mnemonics.put("RosterSave", KeyEvent.VK_S);
        Mnemonics.put("CloseButton", KeyEvent.VK_O);
        Mnemonics.put("CancelButton", KeyEvent.VK_C);
    }

#endif
/**
 * Constructor
 *
 * @param parent Ancestor panel
 * @param title  title for the dialog
 * @param c      Config object to be set by the dialog
 */
/*public*/ VSDConfigDialog::VSDConfigDialog(QWidget* parent, QString title, VSDConfig* c) :
  JDialog(parent, title, false)
 {
  //super(SwingUtilities.getWindowAncestor(parent), title);
  config = c;
  log = new Logger("VSDConfigDialog");
  nullProfileName = tr("Select a profile");
  nullRosterSelected = tr("No Roster Entry Selected");
#if 1
//        VSDecoderManager::instance().addEventListener(new VSDManagerListener() {
//            /*public*/ void eventAction(VSDManagerEvent evt) {
//                vsdecoderManagerEventAction(evt);
//            }
//        });
 connect(VSDecoderManager::instance(), SIGNAL(fireEvent(VSDManagerEvent*)),  this,SLOT(vsdecoderManagerEventAction(VSDManagerEvent*)));
 initComponents();
#endif
}

/**
 * Init the GUI components
 */
/*protected*/ void VSDConfigDialog::initComponents()
{
 QVBoxLayout* thisLayout = new QVBoxLayout();
 this->setLayout(/*new BoxLayout(this.getContentPane(), BoxLayout.PAGE_AXIS)*/thisLayout);

 // Tabbed pane for loco select (Roster or Manual)
 locoSelectPanel = new QTabWidget();
//        TitledBorder title = BorderFactory.createTitledBorder(BorderFactory.createLoweredBevelBorder(),
//                tr("LocoTabbedPaneTitle"));
//        title.setTitlePosition(TitledBorder.DEFAULT_POSITION);
//        locoSelectPanel.setBorder(title);

 // Roster Tab and Address Tab
 rosterPanel = new QWidget();
 QHBoxLayout* rosterPanelLayout = new QHBoxLayout();
 rosterPanel->setLayout(/*new BoxLayout(rosterPanel, BoxLayout.LINE_AXIS)*/rosterPanelLayout);
 addressPanel = new QWidget();
 QHBoxLayout* addressPanelLayout = new QHBoxLayout();
 addressPanel->setLayout(/*new BoxLayout(addressPanel, BoxLayout.LINE_AXIS)*/addressPanelLayout);
 locoSelectPanel->addTab( rosterPanel, tr("Roster"));
 locoSelectPanel->addTab( addressPanel, tr("Manual"));
 //NOTE: There appears to be a bug in Swing that doesn't let Mnemonics work on a JTabbedPane when a sibling component
 // has the focus.  Oh well.
 //try {
     locoSelectPanel->setTabToolTip(locoSelectPanel->indexOf( rosterPanel), tr("Use this tab to select a locomotive from the Roster"));
     //locoSelectPanel->setMnemonicAt(locoSelectPanel.indexOfTab(tr("LocoTabbedPaneRosterTab")), Mnemonics.get("RosterTab"));
     locoSelectPanel->setTabToolTip(locoSelectPanel->indexOf(addressPanel), tr("Use this tab to manually set a locomotive address"));
    //locoSelectPanel.setMnemonicAt(locoSelectPanel.indexOfTab(tr("LocoTabbedPaneManualTab")), Mnemonics.get("ManualTab"));
//        } catch (IndexOutOfBoundsException iobe) {
//            log.debug("Index out of bounds setting up tabbed Pane: " + iobe);
//            // Ignore out-of-bounds exception.  We just won't have mnemonics or tool tips this go round.
//        }
 // Roster Tab components
 rosterSelector = new RosterEntrySelectorPanel();
 rosterSelector->setNonSelectedItem(tr("No Roster Entry Selected"));
 rosterSelector->setToolTip(tr("Choose a locomotive from the roster. Use the left chooser to filter available locomotives."));
 //rosterComboBox.setToolTipText("tool tip for roster box");
//        rosterSelector.addPropertyChangeListener("selectedRosterEntries", new PropertyChangeListener() {
//            @Override
//            /*public*/ void propertyChange(PropertyChangeEvent pce) {
//                rosterItemSelectAction(NULL);
//            }
//        });
 connect(rosterSelector, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(rosterItemSelectAction()));
 rosterPanelLayout->addWidget(rosterSelector);
 rosterLabel = new QLabel();
 rosterLabel->setText(tr("Roster"));

 // Address Tab Components
 addressLabel = new QLabel();
 addressSelector = new DccLocoAddressSelector();
 addressSelector->setToolTip(tr("Enter a locomotive address here, then click \"Set\""));
 addressSetButton = new QPushButton();
 addressSetButton->setText(tr("Set"));
 addressSetButton->setEnabled(true);
 addressSetButton->setToolTip(tr("Click here to set the loco address."));
 //addressSetButton.setMnemonic(Mnemonics.get("AddressSet"));
//        addressSetButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                addressSetButtonActionPerformed(evt);
//            }
//        });
 connect(addressSetButton, SIGNAL(clicked()), this, SLOT(addressSetButtonActionPerformed()));
 addressPanelLayout->addWidget(addressSelector->getCombinedJPanel());
 addressPanelLayout->addWidget(addressSetButton);
 addressPanelLayout->addWidget(addressLabel);

 // Profile select Pane
 profilePanel = new QWidget();
 QVBoxLayout* profilePanelLayout = new QVBoxLayout;
 profilePanel->setLayout(/*new BoxLayout(profilePanel, BoxLayout.PAGE_AXIS)*/profilePanelLayout);
 profileComboBox = new QComboBox();
 profileComboBox->setToolTip(tr("Choose a Sound Profile from this list."));
 profileLabel = new QLabel();
 profileLoadButton = new QPushButton(tr("Load VSD File"));
 profileLoadButton->setToolTip(tr("Load a new VSD file to add more Profiles"));
 //profileLoadButton.setMnemonic(Mnemonics.get("ProfileLoad"));
 profileLoadButton->setEnabled(true);
//        TitledBorder title2 = BorderFactory.createTitledBorder(BorderFactory.createLoweredBevelBorder(),
//                tr("ProfileSelectorPaneTitle"));
//        title.setTitlePosition(TitledBorder.DEFAULT_POSITION);
//        profilePanel.setBorder(title2);

 //profileComboBox.setModel(new javax.swing.DefaultComboBoxModel<Object>());
 // Add any already-loaded profile names
 QStringList sl = VSDecoderManager::instance()->getVSDProfileNames();
 if (sl.isEmpty()) {
     profileComboBox->setEnabled(false);
 } else {
     profileComboBox->setEnabled(true);
 }
 updateProfileList(sl);
 profileComboBox->addItem(/*loadProfilePrompt = new NullProfileBoxItem()*/nullProfileName);
 profileComboBox->setCurrentIndex(profileComboBox->findText(/*loadProfilePrompt*/nullProfileName));
//        profileComboBox.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                profileComboBoxActionPerformed(evt);
//            }
//        });
 connect(profileComboBox, SIGNAL(currentIndexChanged(int)), SLOT(profileComboBoxActionPerformed()));
 profilePanelLayout->addWidget(profileComboBox);
 profilePanelLayout->addWidget(profileLoadButton);
//        profileLoadButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                profileLoadButtonActionPerformed(evt);
//            }
//        });
 connect(profileLoadButton, SIGNAL(clicked()), this, SLOT(profileLoadButtonActionPerformed()));

 profileLabel->setText(tr("Sound Profile"));

 rosterSaveButton = new QPushButton();
 rosterSaveButton->setText(tr("Save to Roster"));
//        rosterSaveButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                rosterSaveButtonAction(e);
//            }
//        });
 connect(rosterSaveButton, SIGNAL(clicked()), this, SLOT(rosterSaveButtonAction()));
 rosterSaveButton->setEnabled(false); // temporarily disable this until we update the RosterEntry
 rosterSaveButton->setToolTip(tr("Save the current configuration to the selected Roster Entry."));
 //rosterSaveButton.setMnemonic(Mnemonics.get("RosterSave"));

 QWidget* cbPanel = new QWidget();
 QHBoxLayout* cbPanelLayout = new QHBoxLayout(cbPanel);
 closeButton = new QPushButton(tr("OK"));
 closeButton->setEnabled(false);
 closeButton->setToolTip(tr("Save these settings and create a VSDecoder."));
 //closeButton.setMnemonic(Mnemonics.get("CloseButton"));
//        closeButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                closeButtonActionPerformed(e);
//            }
//        });
 connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButtonActionPerformed()));

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
 cancelButton->setToolTip(tr("Cancel this configuration."));
 //cancelButton.setMnemonic(Mnemonics.get("CancelButton"));
//        cancelButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                cancelButtonActionPerformed(evt);
//            }
//        });
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonActionPerformed()));
 cbPanelLayout->addWidget(cancelButton);
 cbPanelLayout->addWidget(rosterSaveButton);
 cbPanelLayout->addWidget(closeButton);

 thisLayout->addWidget(locoSelectPanel);
 thisLayout->addWidget(profilePanel);
 //this.add(rosterSaveButton);
 thisLayout->addWidget(cbPanel);
 //this->pack();
 adjustSize();
 this->setVisible(true);

}

/*public*/ void VSDConfigDialog::cancelButtonActionPerformed(JActionEvent* ae) {
    //dispose();
 deleteLater();
}

/**
 * Handle the "Close" (or "OK") button action
 */
/*public*/ void VSDConfigDialog::closeButtonActionPerformed(JActionEvent* ae)
{
 QString profileName = profileComboBox->currentText();
 if (profileComboBox->currentText() != "" && profileComboBox->currentText() != nullProfileName) {
    config->setProfileName(profileName);
 } else {
    config->setProfileName("");
 }
 config->setLocoAddress(addressSelector->getAddress());
 if (rosterSelector->getSelectedRosterEntries()->length() > 0) {
    config->setRosterEntry(rosterSelector->getSelectedRosterEntries()->at(0));
 } else {
    config->setRosterEntry(NULL);
 }

 //firePropertyChange(CONFIG_PROPERTY, QVariant(), config);
 emit propertyChange(new PropertyChangeEvent(this,CONFIG_PROPERTY, QVariant(), VPtr<VSDConfig>::asQVariant(config)));
 //dispose();
}
#if 0
    // class NullComboBoxItem
    //
    // little object to insert into profileComboBox when it's empty
    static class NullProfileBoxItem {

        @Override
        /*public*/ QString toString() {
            return (tr("NoLocoSelectedText"));
        }
    }
#endif
/*private*/ void VSDConfigDialog::enableProfileStuff(bool t) {
    closeButton->setEnabled(t);
    profileComboBox->setEnabled(t);
    profileLoadButton->setEnabled(t);
    rosterSaveButton->setEnabled(t);
}

/**
 * rosterItemSelectAction()
 *
 * ActionEventListener function for rosterSelector Chooses a RosterEntry
 * from the list and loads its relevant info.
 */
/*private*/ void VSDConfigDialog::rosterItemSelectAction(JActionEvent* /*e*/)
{
 if (rosterSelector->getSelectedRosterEntries()->length() != 0)
 {
  log->debug("Roster Entry selected...");
  setRosterEntry(rosterSelector->getSelectedRosterEntries()->at(0));
  enableProfileStuff(true);
  // undo the close button enable if there's no profile selected
  // (this would be when selecting a RosterEntry that doesn't have
  // predefined VSD info.
  if ((profileComboBox->currentIndex() == -1)
          //|| (profileComboBox.getSelectedItem() instanceof NullProfileBoxItem)) {
      || profileComboBox->currentText() == "Select a Profile" )
  {
   closeButton->setEnabled(false);
  }
 }
}

/**
 * rosterSaveButtonAction()
 *
 * ActionEventListener method for rosterSaveButton Writes VSDecoder info to
 * the RosterEntry.
 */
/*private*/ void VSDConfigDialog::rosterSaveButtonAction(JActionEvent* /*e*/) {
    log->debug("rosterSaveButton pressed");
    if (rosterSelector->getSelectedRosterEntries()->length() != 0) {
        RosterEntry* r = rosterSelector->getSelectedRosterEntries()->at(0);
        QString profile = profileComboBox->currentText();
        QString path = VSDecoderManager::instance()->getProfilePath(profile);
        if ((path == NULL) || (profile == NULL)) {
            log->debug("Path and/or Profile not selected.  Ignore Save button press.");
            return;
        } else {
            r->setOpen(true);
            r->putAttribute("VSDecoder_Path", path);
            r->putAttribute("VSDecoder_Profile", profile);
//                int value = JOptionPane.showConfirmDialog(NULL,
//                        MessageFormat.format(tr("UpdateRoster"),
//                                new Object[]{r.titleString()}),
//                        tr("SaveRoster?"), JOptionPane.YES_NO_OPTION);
//                if (value == JOptionPane.YES_OPTION) {
            if(QMessageBox::question(NULL, r->titleString(), tr("SaveRoster"), QMessageBox::Yes | QMessageBox::No)== QMessageBox::Yes)
            {
                storeFile(r);
            }
            r->setOpen(false);
        }

        // Need to write RosterEntry to file.
    }
}

/*private*/ void VSDConfigDialog::profileComboBoxActionPerformed(JActionEvent* evt)
{
 // if there's also an Address entered, then enable the OK button.
 if (addressSelector->getAddress() != NULL && profileComboBox->currentText() != nullProfileName)
 {
  closeButton->setEnabled(true);
 }
 else
  closeButton->setEnabled(false);
}

/*private*/ void VSDConfigDialog::profileLoadButtonActionPerformed(JActionEvent* evt) {
    LoadVSDFileAction* vfa = new LoadVSDFileAction();
    vfa->actionPerformed();
    // Note: This will trigger a PROFILE_LIST_CHANGE event from VSDecoderManager
}

/**
 * handle the address "Set" button.
 */
/*private*/ void VSDConfigDialog::addressSetButtonActionPerformed(JActionEvent* evt) {
    // If there's also a Profile selected, enable the OK button.
    if ((profileComboBox->currentIndex() != -1)
            //&& (!(profileComboBox.getSelectedItem() instanceof NullProfileBoxItem)))
        && profileComboBox->currentText() != nullProfileName)
    {
        closeButton->setEnabled(true);
    }
}

/**
 * handle profile list changes from the VSDecoderManager
 */
//@SuppressWarnings("unchecked")
/*private*/ void VSDConfigDialog::vsdecoderManagerEventAction(VSDManagerEvent* evt)
{
 if (evt->getType() == VSDManagerEvent::PROFILE_LIST_CHANGE)
 {
  log->debug("Received Profile List Change Event");
  updateProfileList(evt->getData().toStringList());
 }
}

/**
 * Update the profile combo box
 */
/*private*/ void VSDConfigDialog::updateProfileList(QStringList s) {
    // There's got to be a more efficient way to do this.
    // Most of this is about merging the new array list with
    // the entries already in the ComboBox.

 if (s.isEmpty()) {
        return;
    }

    // This is a bit tedious...
    // Pull all of the existing names from the Profile ComboBox
    QStringList ce_list =  QStringList();
    for (int i = 0; i < profileComboBox->count(); i++) {
        ce_list.append(profileComboBox->itemText(i));
    }

    // Cycle through the list provided as "s" and add only
    // those profiles that aren't already there.
    //Iterator<String> itr = s.iterator();
    QStringListIterator itr(s);
    while (itr.hasNext()) {
        QString st = itr.next();
        if (!ce_list.contains(st)) {
            log->debug("added item " + st);
            profileComboBox->addItem(st);
        }
    }

    // If the combo box isn't empty, enable it and enable the
    // Roster Save button.
    if (profileComboBox->count() > 0) {
        profileComboBox->setEnabled(true);
        // Enable the roster save button if roster items are available.
        if (rosterSelector->getSelectedRosterEntries()->length() > 0) {
         RosterEntry* r = rosterSelector->getSelectedRosterEntries()->at(0);
            QString profile = r->getAttribute("VSDecoder_Profile");
            log->debug("Trying to set the ProfileComboBox to this Profile: " + profile);
            if (profile != NULL) {
                profileComboBox->setCurrentIndex(profileComboBox->findText(profile));
            }
            rosterSaveButton->setEnabled(true);
        }
    }
}

/**
 * setRosterEntry()
 *
 * Respond to the user choosing an entry from the rosterSelector
 */
/*public*/ void VSDConfigDialog::setRosterEntry(RosterEntry* entry) {
    QString vsd_path;
    QString vsd_profile;

    // Update the roster entry local var.
    rosterEntry = entry;

    // Get VSD info from Roster.
    vsd_path = rosterEntry->getAttribute("VSDecoder_Path");
    vsd_profile = rosterEntry->getAttribute("VSDecoder_Profile");

    log->debug("Roster entry: profile = " + vsd_profile + " path = " + vsd_path);

    // If the roster entry has VSD info stored, load it.
    if ((vsd_path != NULL) && (vsd_profile != NULL)) {
        // Load the indicated VSDecoder Profile and update the Profile combo box
        // This will trigger a PROFILE_LIST_CHANGE event from the VSDecoderManager.
        VSDecoderManager::instance()->loadProfiles(vsd_path);
    }

    // Set the Address box from the Roster entry
    // Do this after the VSDecoder create, so it will see the change.
    addressSelector->setAddress(entry->getDccLocoAddress());
    addressSelector->setEnabled(true);
    addressSetButton->setEnabled(true);
}

/**
 * Write roster settings to the Roster file
 */
/*protected*/ bool VSDConfigDialog::storeFile(RosterEntry* _rosterEntry) {
    log->debug("storeFile starts");
    // We need to create a programmer, a cvTableModel, an iCvTableModel, and a variableTableModel.
    // Doesn't matter which, so we'll use the LocoNet programmer.
    Programmer* p = (Programmer*)((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
    CvTableModel* cvModel = new CvTableModel(NULL, p);
    //IndexedCvTableModel* iCvModel = new IndexedCvTableModel(NULL, p);
    QStringList items = QStringList() << "Name" << "Value";
    VariableTableModel* variableModel = new VariableTableModel(NULL, items, cvModel/*, iCvModel*/);

    // Now, in theory we can call _rosterEntry.writeFile...
    if (_rosterEntry->getFileName() != NULL) {
        // set the loco file name in the roster entry
        _rosterEntry->readFile();  // read, but don't yet process
        _rosterEntry->loadCvModel(variableModel, cvModel);
    }

    // id has to be set!
    if (_rosterEntry->getId()==("")) {
        log->debug("storeFile without a filename; issued dialog");
        return false;
    }

    // if there isn't a filename, store using the id
    _rosterEntry->ensureFilenameExists();

    // create the RosterEntry to its file
    _rosterEntry->writeFile(cvModel, /*iCvModel,*/ variableModel); // where to get the models???

    // mark this as a success
    variableModel->setFileDirty(false);

    // and store an updated roster file
    Roster::getDefault()->writeRoster();

    return true;
}

