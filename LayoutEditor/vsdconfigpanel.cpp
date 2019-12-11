#include "vsdconfigpanel.h"
#include "vsdecoder.h"
#include "dcclocoaddressselector.h"
#include "rosterentryselectorpanel.h"
#include "vsdecoderpane.h"
#include "vsdecodermanager.h"
#include "vsdmanagerevent.h"
#include <QMessageBox>
#include "instancemanager.h"
#include "busydialog.h"

VSDConfigPanel::VSDConfigPanel(QWidget *parent) :
  JmriPanel(parent)
{
}
#if 0
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
 * @version			$Revision: 28746 $
 */
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import java.text.MessageFormat;
//import java.util.ArrayList;
//import java.util.Iterator;
//import java.util.ResourceBundle;
//import javax.swing.BoxLayout;
//import javax.swing.DefaultComboBoxModel;
//import javax.swing.JOptionPane;
//import javax.swing.QWidget;
//import javax.swing.SwingWorker;
//import jmri.InstanceManager;
//import jmri.Programmer;
//import jmri.jmrit.DccLocoAddressSelector;
//import jmri.jmrit.roster.Roster;
//import jmri.jmrit.roster.RosterEntry;
//import jmri.jmrit.roster.swing.RosterEntrySelectorPanel;
//import jmri.jmrit.symbolicprog.CvTableModel;
//import jmri.jmrit.symbolicprog.IndexedCvTableModel;
//import jmri.jmrit.symbolicprog.VariableTableModel;
//import jmri.util.swing.JmriPanel;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;

//@SuppressWarnings({"serial", "deprecation"})
///*public*/ class VSDConfigPanel extends JmriPanel {

    //private static final ResourceBundle vsdecoderBundle = VSDecoderBundle.bundle();


    // CONSTRUCTORS
    /*public*/ VSDConfigPanel() {
        this(NULL, NULL);
    }
#endif
/*public*/ VSDConfigPanel::VSDConfigPanel(QString dec, VSDecoderPane* dad, QWidget *parent) :
JmriPanel(parent) {
    //super();
log = new Logger("VSDConfigPanel");
    main_pane = dad;
    profile_selected = false;
    decoder_mgr = VSDecoderManager::instance();
    initComponents();
}

/*public*/ void VSDConfigPanel::setMainPane(VSDecoderPane* dad) {
    main_pane = dad;
}

/*public*/ VSDecoderPane* VSDConfigPanel::getMainPane() {
    return (main_pane);
}

/*public*/ void VSDConfigPanel::init() {
}

//@Override
/*public*/ void VSDConfigPanel::initContext(QObject* context) {
    initComponents();
}

// updateAddress()
//
// Read the addressTextBox and broadcast the new address to
// any listeners.
//@SuppressWarnings("cast")
/*protected*/ void VSDConfigPanel::updateAddress()
{
 // Simulates the clicking of the address Set button
 VSDecoder* dec = main_pane->getDecoder();
 if (addressSelector->getAddress() != NULL)
 {
  main_pane->firePropertyChange(VSDecoderPane::ADDRESS_CHANGE,
             VPtr<LocoAddress>::asQVariant(dec->getAddress()), VPtr<DccLocoAddress>::asQVariant(addressSelector->getAddress()));
 }
}

// GUI EVENT HANDLING METHODS
// handleDecoderListChange()
//
// Respond to a change in the VSDecoderManager's profile list.
// Event listener on VSDecoderManager's profile list.
//@SuppressWarnings("unchecked")
/*public*/ void VSDConfigPanel::handleDecoderListChange(VSDManagerEvent* e) {
    log->warn("Handling the decoder list change");
    this->updateProfileList( e->getData().toStringList());
}

/*public*/ void VSDConfigPanel::updateProfileList(QStringList s)
{

 if (s.isEmpty()) {
     return;
 }

 // This is a bit tedious...
 QStringList ce_list = QStringList();
 for (int i = 0; i < profileComboBox->count(); i++) {
     ce_list.append(profileComboBox->itemText(i));
 }

 //Iterator<String> itr = s.iterator();
 QStringListIterator itr(s);
 while (itr.hasNext()) {
     QString st = itr.next();
     if (!ce_list.contains(st)) {
         log->debug("added item " + st);
         profileComboBox->addItem(st);
     }
 }

 if (profileComboBox->count() > 0) {
     profileComboBox->setEnabled(true);
     // Enable the roster save button if roster items are available.
     if (rosterSelector->getSelectedRosterEntries()->length() > 0) {
         rosterSaveButton->setEnabled(true);
     }
 }

 //revalidate();
 repaint();
}

// setProfileList()
//
// Perform the actual work of changing the profileComboBox's contents
//@SuppressWarnings("cast")
/*public*/ void VSDConfigPanel::setProfileList(QStringList s) {
    VSDecoder* vsd;
    bool default_set = false;

    log->warn("updating the profile list.");

    //profileComboBox.setModel(new DefaultComboBoxModel<Object>());
    //Iterator<String> itr = s.iterator();
    QStringListIterator itr(s);
    while (itr.hasNext()) {

        QString st =  itr.next();
        log->debug("added item " + st);
        profileComboBox->addItem(st);
        // A decoder is already selected, and is the default decoder...
        if (((vsd = main_pane->getDecoder()) != NULL) && vsd->isDefault()) {
            log->debug("decoder " + st + " : " + vsd->metaObject()->className());
            log->debug("item is default " + st);
            profileComboBox->setCurrentIndex(profileComboBox->findText(st));
            profileComboBox->removeItem(/*loadProfilePrompt*/0);
            default_set = true;
            profile_selected = true;
            // Imitate a button click.  Don't care the contents of the ActionEvent - the called
            // function doesn't use the contents.

            updateAddress();  // why this? Who's listening?  Profile select doesn't change the address...
        }

    }
    if ((!default_set) && (!profile_selected)) {
        profileComboBox->insertItem(0, "Choose a Profile");
        profileComboBox->setCurrentIndex(0);
    }

    if (profileComboBox->count() > 0) {
        profileComboBox->setEnabled(true);
        // Enable the roster save button if roster items are available.
        if (rosterSelector->getSelectedRosterEntries()->length() > 0) {
            rosterSaveButton->setEnabled(true);
        }
    }

    update();
    repaint();
}

// initComponents()
//
// Build the GUI components and initialize them.
//@Override
/*public*/ void VSDConfigPanel::initComponents() {

    // Connect to the VSDecoderManager, so we know when the Profile list changes.
//        VSDecoderManager.instance().addEventListener(new VSDManagerListener() {
//            /*public*/ void eventAction(VSDManagerEvent e) {
//                if (e.getType() == VSDManagerEvent.EventType.PROFILE_LIST_CHANGE) {
//                    log->debug("Received Decoder List Change Event");
//                    handleDecoderListChange(e);
//                }
//            }
//        });
connect(VSDecoderManager::instance(), SIGNAL(fireEvent(VSDManagerEvent*)), this, SLOT(eventAction(VSDManagerEvent*)));
    // Build the GUI.
    //setLayout(new BorderLayout(10, 10));
QVBoxLayout* thisLayout = new QVBoxLayout();
    setLayout(/*new BoxLayout(this, BoxLayout.PAGE_AXIS)*/thisLayout);

    rosterPanel = new QWidget();
    QHBoxLayout* rosterPanelLayout = new QHBoxLayout;
    rosterPanel->setLayout(/*new BoxLayout(rosterPanel, BoxLayout.LINE_AXIS*/rosterPanelLayout);
    profilePanel = new QWidget();
    QHBoxLayout* profilePanelLayout = new QHBoxLayout;
    profilePanel->setLayout(/*new BoxLayout(profilePanel, BoxLayout.LINE_AXIS)*/profilePanelLayout);
    addressPanel = new QWidget();
    QHBoxLayout* addressPanelLayout = new QHBoxLayout;
    addressPanel->setLayout(/*new BoxLayout(addressPanel, BoxLayout.LINE_AXIS)*/addressPanelLayout);
    //this.add(profilePanel, BorderLayout.PAGE_START);
    //this.add(addressPanel, BorderLayout.CENTER);
    //this.add(rosterPanel, BorderLayout.PAGE_END);
    thisLayout->addWidget(profilePanel);
    thisLayout->addWidget(addressPanel);
    thisLayout->addWidget(rosterPanel);

    rosterSelector = new RosterEntrySelectorPanel();
    rosterSelector->setNonSelectedItem("No Loco Selected");
    //rosterComboBox.setToolTipText("tool tip for roster box");
//        rosterSelector.addPropertyChangeListener("selectedRosterEntries", new PropertyChangeListener() {

//            @Override
//            /*public*/ void propertyChange(PropertyChangeEvent pce) {
//                rosterItemSelectAction(NULL);
//            }
//        });
    rosterSelector->addPropertyChangeListener("selectedRosterEntries",(PropertyChangeListener*)this);
    //connect(rosterSelector, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
    rosterPanelLayout->addWidget(rosterSelector);
    rosterLabel = new QLabel();
    rosterLabel->setText("Roster");
    rosterPanelLayout->addWidget(rosterLabel);

    rosterSaveButton = new QPushButton();
    rosterSaveButton->setText("Save");
//        rosterSaveButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                rosterSaveButtonAction(e);
//            }
//        });
    connect(rosterSaveButton, SIGNAL(clicked()), this, SLOT(rosterSaveButtonAction()));
    rosterSaveButton->setEnabled(false); // temporarily disable this until we update the RosterEntry
    rosterSaveButton->setToolTip(tr("Save the current configuration to the selected Roster Entry."));
    rosterPanelLayout->addWidget(rosterSaveButton);

    addressLabel = new QLabel();
    addressSetButton = new QPushButton();
    addressSelector = new DccLocoAddressSelector();

    profileComboBox = new QComboBox();
    profileLabel = new QLabel();

    //profileComboBox.setModel(new javax.swing.DefaultComboBoxModel<Object>());
    // Add any already-loaded profile names
    QStringList sl = VSDecoderManager::instance()->getVSDProfileNames();
    if (sl.isEmpty()) {
        profileComboBox->setEnabled(false);
    } else {
        profileComboBox->setEnabled(true);
    }
    updateProfileList(sl);
    profileComboBox->addItem(/*loadProfilePrompt = new NullProfileBoxItem()*/"Select a profile");
    profileComboBox->setCurrentIndex(profileComboBox->findText(/*loadProfilePrompt*/"Select a profile"));
    profile_selected = false;
//        profileComboBox.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                profileComboBoxActionPerformed(evt);
//            }
//        });
    connect(profileComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(profileComboBoxActionPerformed()));
    profilePanelLayout->addWidget(profileComboBox);

    profileLabel->setText("Sound Profile");
    profilePanelLayout->addWidget(profileLabel);

    addressLabel->setText("Address");
    //addressLabel.setMaximumSize(addressLabel.getPreferredSize());

    addressSetButton->setText("Set");
//        addressSetButton.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                addressSetButtonActionPerformed(evt);
//            }
//        });
    connect(addressSetButton, SIGNAL(clicked()), this, SLOT(addressSetButtonActionPerformed()));
    addressSetButton->setEnabled(false);
    addressSetButton->setToolTip("Set the decoder address.");
    addressPanelLayout->addWidget(addressSelector->getCombinedJPanel());
    addressPanelLayout->addWidget(addressSetButton);
    addressPanelLayout->addWidget(addressLabel);

}

void /*public*/ VSDConfigPanel::eventAction(VSDManagerEvent* e) {
if (e->getType() == VSDManagerEvent::PROFILE_LIST_CHANGE) {
 log->debug("Received Decoder List Change Event");
 handleDecoderListChange(e);
}
}

void /*public*/ VSDConfigPanel::propertyChange(PropertyChangeEvent*)
{
rosterItemSelectAction(NULL);
}


// class NullComboBoxItem
//
// little object to insert into profileComboBox when it's empty
//static class NullProfileBoxItem {

    //@Override
    /*public*/ QString NullProfileBoxItem::toString() {
        //return rb.getString("NoLocoSelected");
        return ("Select a profile");
    }
//};

// setRosterEntry()
//
// Respond to the user choosing an entry from the rosterSelector
/*public*/ void VSDConfigPanel::setRosterEntry(RosterEntry* entry) {
    QString vsd_path;
    QString vsd_profile;
    VSDecoder* dec;

    // Update the roster entry local var.
    rosterEntry = entry;

    // Get VSD info from Roster.
    vsd_path = rosterEntry->getAttribute("VSDecoder_Path");
    vsd_profile = rosterEntry->getAttribute("VSDecoder_Profile");

    log->debug("Roster entry: profile = " + vsd_profile + " path = " + vsd_path);

    // If the roster entry has VSD info stored, load it.
    if ((vsd_path != NULL) && (vsd_profile != NULL)) {
        // Load the indicated VSDecoder Profile and update the Profile combo box
        dec = VSDecoderManager::instance()->getVSDecoder(vsd_profile, vsd_path);
        if (dec != NULL) {
            log->debug("VSDecoder loaded from file: " + dec->getProfileName());
            dec->setAddress(rosterEntry->getDccLocoAddress());
            dec->enable();
            main_pane->setDecoder(dec);
            QStringList sl = VSDecoderManager::instance()->getVSDProfileNames();
            updateProfileList(sl);
            profileComboBox->setCurrentIndex(profileComboBox->findText(dec->getProfileName()));
            profileComboBox->setEnabled(true);
            profile_selected = true;
        }
    }

    // Set the Address box from the Roster entry
    // Do this after the VSDecoder create, so it will see the change.
    main_pane->setAddress(entry->getDccLocoAddress());
    addressSelector->setAddress(entry->getDccLocoAddress());
    addressSelector->setEnabled(true);
    addressSetButton->setEnabled(true);

}

// rosterItemSelectAction()
//
// ActionEventListener function for rosterSelector
// Chooses a RosterEntry from the list and loads its relevant info.
/*private*/ void VSDConfigPanel::rosterItemSelectAction(ActionEvent* /*e*/) {
if (rosterSelector->getSelectedRosterEntries()->length() != 0) {
        log->debug("Roster Entry selected...");
        setRosterEntry(rosterSelector->getSelectedRosterEntries()->at(0));
        rosterSaveButton->setEnabled(true);
    }
}

// rosterSaveButtonAction()
//
// ActionEventListener method for rosterSaveButton
// Writes VSDecoder info to the RosterEntry.
/*private*/ void VSDConfigPanel::rosterSaveButtonAction(ActionEvent* /*e*/) {
    log->debug("rosterSaveButton pressed");
    if (rosterSelector->getSelectedRosterEntries()->length() != 0) {
        RosterEntry* r = rosterSelector->getSelectedRosterEntries()->at(0);
        QString path = main_pane->getDecoder()->getVSDFilePath();
        QString profile = profileComboBox->currentText();
        if ((path == NULL) || (profile == NULL)) {
            log->debug("Path and/or Profile not selected.  Ignore Save button press.");
            return;
        } else {
            r->setOpen(true);
            r->putAttribute("VSDecoder_Path", main_pane->getDecoder()->getVSDFilePath());
            r->putAttribute("VSDecoder_Profile", profileComboBox->currentText());
//                int value = JOptionPane.showConfirmDialog(NULL,
//                        MessageFormat.format(vsdecoderBundle.getString("UpdateRoster"),
//                                new Object[]{r.titleString()}),
//                        vsdecoderBundle.getString("SaveRoster?"), JOptionPane.YES_NO_OPTION);
//                if (value == JOptionPane.YES_OPTION) {
            if(QMessageBox::question(NULL, r->titleString(),tr("Do you want to save these changes to your Roster file?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
            {
                storeFile(r);
            }
            r->setOpen(false);
        }

        // Need to write RosterEntry to file.
    }
}

/*protected*/ bool VSDConfigPanel::storeFile(RosterEntry* _rosterEntry) {
    log->debug("storeFile starts");
    // We need to create a programmer, a cvTableModel, an iCvTableModel, and a variableTableModel.
    // Doesn't matter which, so we'll use the LocoNet programmer.
    Programmer* p = InstanceManager::programmerManagerInstance()->getGlobalProgrammer();
    CvTableModel* cvModel = new CvTableModel(NULL, p);
    IndexedCvTableModel* iCvModel = new IndexedCvTableModel(NULL, p);
    QStringList sl = QStringList() << "Name" << "Value";
    VariableTableModel* variableModel = new VariableTableModel(NULL, /*new String[]{"Name", "Value"}*/sl, cvModel, iCvModel);

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

// profileComboBoxActionPerformed()
//
// User chose a Profile from the profileComboBox.
/*private*/ void VSDConfigPanel::profileComboBoxActionPerformed(ActionEvent* evt)
{
 VSDecoder* dec;
 log->debug("Profile selected "+ profileComboBox->currentText());
 int ix = profileComboBox->currentIndex();
 // If the user selected an item, remove the load prompt item
 if (!profile_selected)
 {
  if (profileComboBox->currentText() == loadProfilePrompt->toString())
  {
   // User has selected the "Choose" entry, which doesn't exist
   return;
  }
  else
  {
   // User has chosen a profile for the first time.
profile_selected = true;
   profileComboBox->removeItem(/*loadProfilePrompt*/0);  // remove the "choose" thing.
   profileComboBox->setCurrentIndex(ix-1);
  }
 }

 // Get the existing decoder from the main pane...
 dec = main_pane->getDecoder();
 log->debug("Profile selected. New = " + profileComboBox->
            currentText() + "Decoder = " /*+ QString::number(dec)*/);
 if (dec != NULL)
 {
  dec->shutdown();
  dec->disable();  // disable the previous decoder
 }
 log->debug("Getting selected decoder from VSDecoderManager.");

 // Setup the progress monitor, in case this takes a while
 //dec = main_pane.getDecoder(profileComboBox.getSelectedItem().toString());
 dec = getNewDecoder();
 main_pane->setDecoder(dec);
 //bd.kill();
 log->debug(tr("Decoder = ") + dec->metaObject()->className());
 if (dec != NULL)
 {
  log->debug("Decoder name: " + dec->getProfileName());
  updateAddress();
  // Either way, enable the address text box and set button.
  addressSetButton->setEnabled(true);
  // Do something.
 }
 else
 {
  log->warn("NULL POINTER returned from VSDecoderManager.");
 }
}

/*protected*/ VSDecoder* VSDConfigPanel::getNewDecoder() {
    VSDecoder* rv;

    busy_dialog = new BusyDialog((JFrame*)this->main_pane->getFrame(), "Loading VSD Profile...", false);
    // This takes a little while... so we'll use a SwingWorker
#if 0
    SwingWorker<VSDecoder, Object> sw = new SwingWorker<VSDecoder, Object>() {
        //@Override
        /*public*/ VSDecoder doInBackground() {
            return (main_pane.getDecoder(profileComboBox.getSelectedItem().toString()));
        }

        protected void done() {
            busy_dialog->finish();
        }
    };
    sw.execute();
    busy_dialog->start();
    try {
        rv = sw.get();
    } catch (Exception e) {
        // Way too loose  Should be more specific about exceptions caught.
        rv = NULL;
    }
#endif
    rv = main_pane->getDecoder(profileComboBox->currentText());
    return (rv);
}

// addressBoxActionPerformed()
//
// ActionEventListener for addressSetButton
// Does nothing.
//private void addressBoxActionPerformed(java.awt.event.ActionEvent evt) {
// Don't do anything just yet...
// Probably don't do anything ever...
//}
// addressSetButtonActionPerformed()
//
// ActionEventListener for addressSetButton
// User just pressed "set" on a new address.
/*private*/ void VSDConfigPanel::addressSetButtonActionPerformed(ActionEvent* evt) {
    updateAddress();
}

