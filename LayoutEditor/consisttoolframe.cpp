#include "consisttoolframe.h"
#include "instancemanager.h"
#include "consistmanager.h"
#include "consistfile.h"
#include <QLabel>
#include "dcclocoaddressselector.h"
#include <QRadioButton>
#include "consist.h"
#include "QPushButton"
#include "joptionpane.h"
#include "globalrosterentrycombobox.h"
#include "rosterentry.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include "flowlayout.h"
#include <QScrollArea>
#include "consistdatamodel.h"
#include "dcclocoaddress.h"
#include "vptr.h"
#include "throttlewindow.h"
#include "throttleframemanager.h"
#include "jtable.h"
#include "loggerfactory.h"
#include "jlabel.h"
#include <QMenuBar>
#include <QMenu>
#include "abstractaction.h"

#if 1  //TODO:
/**
 * Frame object for manipulating consists.
 *
 * @author Paul Bender Copyright (C) 2003-2008
 * @version $Revision: 28746 $
 */
// /*public*/ class ConsistToolFrame extends jmri.util.JmriJFrame implements jmri.ConsistListener, jmri.ConsistListListener {

/**
 *
 */
//private static final long serialVersionUID = 7572352658600799471L;
//final java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("jmri.jmrit.consisttool.ConsistTool");

/*public*/ ConsistToolFrame::ConsistToolFrame(QWidget *parent) :
  JmriJFrame(parent)
{
    //super();
    // GUI member declarations
    log->setDebugEnabled(true);
    textAdrLabel = new JLabel();
    adrSelector = new DccLocoAddressSelector();
    consistAdrBox = new QComboBox();
    isAdvancedConsist = new QRadioButton(tr("Advanced Consist"));
    isCSConsist = new QRadioButton(tr("Command Station Consist"));
    deleteButton = new QPushButton();
    deleteButton->setObjectName("deleteButton");
    throttleButton = new QPushButton();
    throttleButton->setObjectName("throttleButton");
    reverseButton = new QPushButton();
    reverseButton->setObjectName("reverseButton");
    restoreButton = new QPushButton();
    restoreButton->setObjectName("restoreButton");
    textLocoLabel = new JLabel();
    locoSelector = new DccLocoAddressSelector();
    addLocoButton = new QPushButton();
    addLocoButton->setObjectName("addLocoButton");
    resetLocoButton = new QPushButton();
    resetLocoButton->setObjectName("resetLocoButton");
    locoDirectionNormal = new QCheckBox(tr("Direction Normal"));
    locoDirectionNormal->setObjectName("locoDirectionNormal");
    consistModel = new ConsistDataModel();
    consistTable = new JTable(consistModel);
    consistManager = NULL;
    _status = new QLabel(tr("Ready"));
    _Consist_Type = Consist::ADVANCED_CONSIST;
    consistFile = NULL;

    consistManager = qobject_cast<AbstractConsistManager*>(InstanceManager::getDefault("ConsistManager"));

    consistFile = new ConsistFile();
    try {
        consistFile->readFile();
    } catch (Exception e) {
        log->warn("error reading consist file: " + e.getMessage());
    }

    // register to be notified if the consist list changes.
    consistManager-> addConsistListListener((ConsistListListener*)this);

    // request an update from the layout.
    consistManager->requestUpdateFromLayout();

    // configure items for GUI
    textAdrLabel->setText(tr("Consist:"));
    textAdrLabel->setVisible(true);

    adrSelector->setVisible(false);
    adrSelector->setToolTip(tr("Consist being created or deleted"));
    textAdrLabel->setLabelFor(adrSelector);

    initializeConsistBox();

//    consistAdrBox.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            consistSelected();
//        }
//    });
    connect(consistAdrBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(consistSelected()));

    consistAdrBox->setToolTip(tr("Select an existing Consist"));

    isAdvancedConsist->setChecked(true);
    isAdvancedConsist->setVisible(true);
    isAdvancedConsist->setEnabled(false);
//    isAdvancedConsist.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            isAdvancedConsist.setSelected(true);
//            isCSConsist.setSelected(false);
//            _Consist_Type = Consist.ADVANCED_CONSIST;
//            adrSelector.setEnabled(true);
//        }
//    });
    connect(isAdvancedConsist, SIGNAL(clicked(bool)), this, SLOT(on_isAdvancedConsist_checked(bool)));
    isCSConsist->setChecked(false);
    isCSConsist->setVisible(true);
    isCSConsist->setEnabled(false);
//    isCSConsist.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            isAdvancedConsist.setSelected(false);
//            isCSConsist.setSelected(true);
//            _Consist_Type = Consist.CS_CONSIST;
//            if (consistMan->csConsistNeedsSeperateAddress()) {
//                adrSelector.setEnabled(false);
//            } else {
//                adrSelector.setEnabled(true);
//            }
//        }
//    });

    if (consistManager->isCommandStationConsistPossible()) {
        isAdvancedConsist->setEnabled(true);
        isCSConsist->setEnabled(true);
    }

    deleteButton->setText(tr("Delete"));
    deleteButton->setVisible(true);
    deleteButton->setToolTip(tr("Delete the Consist/remove all locomotives"));
//    deleteButton.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            deleteButtonActionPerformed(e);
//        }
//    });
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteButtonActionPerformed()));

    throttleButton->setText(tr("Throttle"));
    throttleButton->setVisible(true);
    throttleButton->setToolTip(tr("Create the Consist AND Start a Throttle for it"));
//    throttleButton.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            throttleButtonActionPerformed(e);
//        }
//    });
    connect(throttleButton, SIGNAL(clicked(bool)), this, SLOT(throttleButtonActionPerformed()));

    reverseButton->setText(tr("Reverse"));
    reverseButton->setVisible(true);
    reverseButton->setToolTip(tr("Reverse Consist order and flip consist direction bits"));
//    reverseButton.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            reverseButtonActionPerformed(e);
//        }
//    });
    connect(reverseButton, SIGNAL(clicked(bool)), this, SLOT(reverseButtonActionPerformed()));

    restoreButton->setText(tr("Restore"));
    restoreButton->setVisible(true);
    restoreButton->setToolTip(tr("Recreate the Consist through the Command Station."));
    //restoreButton.addActionListener(this::restoreButtonActionPerformed);
    connect(restoreButton, SIGNAL(clicked(bool)), this, SLOT(restoreButtonActionPerformed()));


    // Set up the controls for the First Locomotive in the consist.
    textLocoLabel->setText(tr("New Locomotive:"));
    textLocoLabel->setVisible(true);

    locoSelector->setToolTip(tr("Address of a new Locomotive to add to the Consist"));
    locoSelector->setVisible(false);
    textLocoLabel->setLabelFor(locoSelector);

    locoRosterBox = new GlobalRosterEntryComboBox();
    locoRosterBox->setNonSelectedItem("");
    locoRosterBox->setCurrentIndex(0);

//    locoRosterBox.addPropertyChangeListener("selectedRosterEntries", new PropertyChangeListener() {

//        @Override
//        /*public*/ void propertyChange(PropertyChangeEvent pce) {
//            locoSelected();
//        }
//    });
    connect(locoRosterBox, SIGNAL(currentIndexChanged(int)), this, SLOT(locoSelected()));

    locoRosterBox->setVisible(true);

    locoDirectionNormal->setToolTip(tr("Consist Forward is Forward for this locomotive if checked"));

    locoDirectionNormal->setChecked(true);
    locoDirectionNormal->setVisible(true);
    locoDirectionNormal->setEnabled(false);

    addLocoButton->setText(tr("Add"));
    addLocoButton->setVisible(true);
    addLocoButton->setToolTip(tr("Add Loco"));
//    addLocoButton.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            addLocoButtonActionPerformed(e);
//        }
//    });
    connect(addLocoButton, SIGNAL(clicked(bool)), this, SLOT(addLocoButtonActionPerformed()));

    resetLocoButton->setText(tr("Reset"));
    resetLocoButton->setVisible(true);
    resetLocoButton->setToolTip(tr("Reset locomotive information"));
//    resetLocoButton.addActionListener(new ActionListener() {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            resetLocoButtonActionPerformed(e);
//        }
//    });
    connect(resetLocoButton, SIGNAL(clicked(bool)), this, SLOT(resetLocoButtonActionPerformed()));

    // general GUI config
    setTitle(tr("Consist Control"));
    //getContentPane().setLayout(new GridLayout(4,1));
    getContentPane()->setLayout(new QVBoxLayout());//getContentPane(), BoxLayout.Y_AXIS));

    QMenuBar* menuBar = new QMenuBar();
    menuBar->setObjectName("menubar");
    setMenuBar(menuBar);

    // add a "File" menu
    QMenu* fileMenu = new QMenu(tr("File"));
    fileMenu->setObjectName("fileMenu");
    menuBar->addMenu(fileMenu);

    // Add a save item
    AbstractAction* act;
    fileMenu->addAction(act = new AbstractAction(tr("Scan Roster for Consists"), this));
//    {
//        //@Override
//        public void actionPerformed(ActionEvent e) {
//            scanRoster();
//            initializeConsistBox();
//            consistModel.fireTableDataChanged();
//            resetLocoButtonActionPerformed(e);
//        }
//    });
      connect(act, SIGNAL(toggled(bool)), this, SLOT(on_scanConsists()));

    // install items in GUI
    // The address and related buttons are installed in a single pane
    QWidget* addressPanel = new QWidget();
    addressPanel->setLayout(new FlowLayout());

    addressPanel->layout()->addWidget(textAdrLabel);
    addressPanel->layout()->addWidget(adrSelector->getCombinedJPanel());
    addressPanel->layout()->addWidget(consistAdrBox);
    addressPanel->layout()->addWidget(isAdvancedConsist);
    addressPanel->layout()->addWidget(isCSConsist);

    getContentPane()->layout()->addWidget(addressPanel);

    // The address and related buttons for each Locomotive
    // are installed in a single pane
    // New Locomotive
    QWidget* locoPanel = new QWidget();
    locoPanel->setLayout(new FlowLayout());

    locoPanel->layout()->addWidget(textLocoLabel);

    locoPanel->layout()->addWidget(locoSelector->getCombinedJPanel());

    locoPanel->layout()->addWidget(locoRosterBox);
    locoPanel->layout()->addWidget(locoDirectionNormal);

    locoPanel->layout()->addWidget(addLocoButton);
    locoPanel->layout()->addWidget(resetLocoButton);

    getContentPane()->layout()->addWidget(locoPanel);

    // Set up the jtable in a Scroll Pane..
//    QScrollArea* consistPane = new QScrollArea(/*consistTable*/);
//    consistPane->setWidget(consistTable);
//    consistPane->setWidgetResizable(true);
    //consistPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
    consistModel->initTable(consistTable);
    getContentPane()->layout()->addWidget(/*consistPane*/consistTable);

    // Set up the Control Button panel
    QWidget* controlPanel = new QWidget();
    controlPanel->setLayout(new FlowLayout());

    controlPanel->layout()->addWidget(deleteButton);
    controlPanel->layout()->addWidget(throttleButton);
    controlPanel->layout()->addWidget(reverseButton);
    controlPanel->layout()->addWidget(restoreButton);

    getContentPane()->layout()->addWidget(controlPanel);

    // add the status line directly to the bottom of the ContentPane.
    QWidget* statusPanel = new QWidget();
    statusPanel->setLayout(new FlowLayout());
    statusPanel->layout()->addWidget(_status);
    getContentPane()->layout()->addWidget(statusPanel);

    addHelpMenu("package.jmri.jmrit.consisttool.ConsistToolFrame", true);
    pack();

}

void ConsistToolFrame::on_scanConsists()
{
 scanRoster();
 initializeConsistBox();
 consistModel->fireTableDataChanged();
 resetLocoButtonActionPerformed(/*e*/);

}
void ConsistToolFrame::on_isAdvancedConsist_checked(bool)
{
//            isAdvancedConsist.setSelected(true);
   isCSConsist->setChecked(false);
   _Consist_Type = Consist::ADVANCED_CONSIST;
   adrSelector->setEnabled(true);
}

void ConsistToolFrame::on_isCSConsist_checked(bool)
{
    isAdvancedConsist->setChecked(false);
    //isCSConsist.setSelected(true);
    _Consist_Type = Consist::CS_CONSIST;
    if (consistManager->csConsistNeedsSeparateAddress()) {
        adrSelector->setEnabled(false);
    } else {
        adrSelector->setEnabled(true);
    }
}



/*private*/ void ConsistToolFrame::initializeConsistBox()
{
 QList<DccLocoAddress*>* existingConsists = consistManager->getConsistList()->toList();
 if (!existingConsists->isEmpty())
 {
  consistAdrBox->clear();
  for (int i = 0; i < existingConsists->size(); i++) {
      consistAdrBox->insertItem(i, existingConsists->at(i)->toString(), VPtr<DccLocoAddress>::asQVariant(existingConsists->at(i)));
  }
  consistAdrBox->setEnabled(true);
  consistAdrBox->insertItem(0,"");
  consistAdrBox->setCurrentIndex(consistAdrBox->findText( adrSelector->getAddress()->toString()));
  if (adrSelector->getAddress() != NULL) {
      if (consistModel->getConsist() != NULL) {
          consistModel->getConsist()->removeConsistListener((ConsistListener*)this);
          _status->setText("Ready");
      }
      consistModel->setConsist(adrSelector->getAddress());
      consistModel->getConsist()->addConsistListener(this);
      adrSelector->setEnabled(false);
  } else {
      if (consistModel->getConsist() != NULL) {
          consistModel->getConsist()->removeConsistListener((ConsistListener*)this);
          _status->setText("Ready");
      }
      consistModel->setConsist((Consist*) NULL);
      adrSelector->setEnabled(true);
  }
 }
 else {
  consistAdrBox->setEnabled(false);
  consistAdrBox->clear();
  consistAdrBox->insertItem(0, "");
  consistAdrBox->setCurrentIndex(0);
  if (consistModel->getConsist() != NULL) {
      consistModel->getConsist()->removeConsistListener((ConsistListener*)this);
      _status->setText("Ready");
  }
  consistModel->setConsist((Consist*) NULL);
  adrSelector->setEnabled(true);
 }
}

/*public*/ void ConsistToolFrame::deleteButtonActionPerformed(/*ActionEvent e*/)
{
 if (adrSelector->getAddress() == NULL)
 {
  JOptionPane::showMessageDialog(this,
          tr("No Consist Address Selected."));
  return;
 }
 DccLocoAddress* address = adrSelector->getAddress();
 consistManager->getConsist(address);
 // confirm delete
 if (JOptionPane::showConfirmDialog(this, tr("Delete consist \"%1\"").arg(address->toString()),
         tr("Question"), JOptionPane::YES_NO_OPTION,
         JOptionPane::QUESTION_MESSAGE) == JOptionPane::NO_OPTION) {
     return; // do not delete
 }
 try {
     consistManager->delConsist(address);
 } catch (Exception ex) {
     log->error(tr("Error deleting consist %1").arg(address->toString()), ex);
 }
 adrSelector->reset();
 adrSelector->setEnabled(true);
 initializeConsistBox();
 try
 {
  consistFile->writeFile(consistManager->getConsistList()->toList());
 }
 catch (IOException ex)
 {
  log->warn("error writing consist file: " + ex.getMessage());
 }
 resetLocoButtonActionPerformed(/*e*/);
 canAdd();
}

/*public*/ void ConsistToolFrame::throttleButtonActionPerformed() {
    if (adrSelector->getAddress() == NULL) {
        JOptionPane::showMessageDialog(this,
                tr("NoConsistSelectedError"));
        return;
    }
    // make sure any new locomotives are added to the consist.
    addLocoButtonActionPerformed(/*e*/);
    // Create a throttle object with the
    //ThrottleFrame tf
    ThrottleWindow* tf
            = ThrottleFrameManager::instance()->createThrottleFrame();
    DccLocoAddress* address = adrSelector->getAddress();

    /*
     * get the lead locomotive from the list of locomotives so we can
     * register function button bindings in the throttle.
     */
    Consist* tempConsist = consistManager->getConsist(address);
    QList<DccLocoAddress*> addressList = tempConsist->getConsistList();
    DccLocoAddress* locoaddress = addressList.at(0);
    if (address != locoaddress) {
        if (log->isDebugEnabled()) {
            log->debug("Consist Address "
                    + address->toString()
                    + ", Lead Locomoitve  "
                    + locoaddress->toString());
        }
        // the consist address and the lead locomotive address differ,
        // register so the function buttons trigger the lead locomotive
        tf->getAddressPanel()->setCurrentAddress(locoaddress);
    }
    // Notify the throttle of the selected consist address
    tf->getAddressPanel()->setConsistAddress(address);
    tf->toFront();
}

/*public*/ void ConsistToolFrame::reverseButtonActionPerformed(/*ActionEvent e*/) {
    if (adrSelector->getAddress() == NULL) {
        JOptionPane::showMessageDialog(this,
                tr("NoConsistSelectedError"));
        return;
    }
    // make sure any new locomotives are added to the consist.
    addLocoButtonActionPerformed(/*e*/);

    /*
     * get the array list of the locomotives in the consist
     */
    DccLocoAddress* address = adrSelector->getAddress();
    Consist* tempConsist = consistManager->getConsist(address);
    tempConsist->reverse();
}

/*public*/ void ConsistToolFrame::restoreButtonActionPerformed(/*ActionEvent e*/) {
    if (adrSelector->getAddress() == nullptr) {
        reportNoConsistSeletected();
        return;
    }
    // make sure any new locomotives are added to the consist.
    addLocoButtonActionPerformed(/*e*/);

    /*
     * get the array list of the locomotives in the consist
     */
    DccLocoAddress* address = adrSelector->getAddress();
    Consist* tempConsist = consistManager->getConsist(address);
    tempConsist->restore();
}

/*public*/ void ConsistToolFrame::consistSelected() {
    if (log->isDebugEnabled()) {
        log->debug("Consist Selected");
    }
    if (consistAdrBox->currentIndex() == -1 && !(adrSelector->getAddress() == NULL)) {
        if (log->isDebugEnabled()) {
            log->debug("No Consist Selected");
        }
        adrSelector->setEnabled(false);
        recallConsist();
    } else if (consistAdrBox->currentIndex() == -1
            || consistAdrBox->currentText() == ("")) {
        if (log->isDebugEnabled()) {
            log->debug("Null Consist Selected");
        }
        adrSelector->reset();
        adrSelector->setEnabled(true);
        recallConsist();
    } else if (((DccLocoAddress*) VPtr<DccLocoAddress>::asPtr(consistAdrBox->currentData())) != adrSelector->getAddress()) {
        if (log->isDebugEnabled()) {
            log->debug("Consist " + consistAdrBox->currentText() + " Selected");
        }
        adrSelector->setEnabled(false);
        adrSelector->setAddress((DccLocoAddress*) VPtr<DccLocoAddress>::asPtr(consistAdrBox->currentData()));
        recallConsist();
    }
}

// Recall the consist
/*private*/ void ConsistToolFrame::recallConsist() {
    if (adrSelector->getAddress() == NULL) {
        // Clear any consist information that was present
        locoSelector->reset();
        locoRosterBox->setCurrentIndex(0);
        if (consistModel->getConsist() != NULL) {
            consistModel->getConsist()->removeConsistListener((ConsistListener*)this);
            _status->setText("Ready");
        }
        consistModel->setConsist((Consist*) NULL);

        canAdd();

        return;
    }
    DccLocoAddress* address = adrSelector->getAddress();
    if (consistModel->getConsist() != NULL) {
        consistModel->getConsist()->removeConsistListener((ConsistListener*)this);
        _status->setText("Ready");
    }
    Consist* selectedConsist = consistManager->getConsist(address);
    consistModel->setConsist(selectedConsist);
    selectedConsist->addConsistListener((ConsistListener*)this);

    // reset the editable locomotive information.
    locoSelector->reset();
    locoRosterBox->setCurrentIndex(0);
    locoDirectionNormal->setChecked(true);

    // if there aren't any locomotives in the consist, don't let
    // the user change the direction
    if (consistModel->getRowCount() == 0) {
        locoDirectionNormal->setEnabled(false);
    } else {
        locoDirectionNormal->setEnabled(true);
    }

    if (log->isDebugEnabled()) {
        log->debug("Recall Consist " + address->toString());
    }

    // What type of consist is this?
    if (selectedConsist->getConsistType() == Consist::ADVANCED_CONSIST) {
        log->debug("Consist type is Advanced Consist ");
        isAdvancedConsist->setChecked(true);
        isCSConsist->setChecked(false);
        _Consist_Type = Consist::ADVANCED_CONSIST;
    } else {
        // This must be a CS Consist.
        log->debug("Consist type is Command Station Consist ");
        isAdvancedConsist->setChecked(false);
        isCSConsist->setChecked(true);
        _Consist_Type = Consist::CS_CONSIST;
    }

    canAdd();
}

/*public*/ void ConsistToolFrame::resetLocoButtonActionPerformed(/*ActionEvent e*/) {
    locoSelector->reset();
    locoRosterBox->setCurrentIndex(0);
    locoDirectionNormal->setChecked(true);
    // if there aren't any locomotives in the consist, don't let
    // the user change the direction
    if (consistModel->getRowCount() == 0) {
        locoDirectionNormal->setEnabled(false);
    } else {
        locoDirectionNormal->setEnabled(true);
    }
}

// Check to see if a consist address is selected, and if it
//	is, dissable the "add button" if the maximum consist size is reached
/*public*/ void ConsistToolFrame::canAdd() {
    // If a consist address is selected, dissable the "add button"
    // if the maximum size is reached
    if (adrSelector->getAddress() != NULL) {
        DccLocoAddress* address = adrSelector->getAddress();
        if (consistModel->getRowCount() == consistManager->getConsist(address)->sizeLimit()) {
            locoSelector->setEnabled(false);
            locoRosterBox->setEnabled(false);
            addLocoButton->setEnabled(false);
            resetLocoButton->setEnabled(false);
            locoDirectionNormal->setEnabled(false);
        } else {
            locoSelector->setEnabled(true);
            locoRosterBox->setEnabled(true);
            addLocoButton->setEnabled(true);
            resetLocoButton->setEnabled(true);
            locoDirectionNormal->setEnabled(false);
            // if there aren't any locomotives in the consist,
            // don't let the user change the direction
            if (consistModel->getRowCount() == 0) {
                locoDirectionNormal->setEnabled(false);
            } else {
                locoDirectionNormal->setEnabled(true);
            }
        }
    } else {
        locoSelector->setEnabled(true);
        locoRosterBox->setEnabled(true);
        addLocoButton->setEnabled(true);
        resetLocoButton->setEnabled(true);
        locoDirectionNormal->setEnabled(false);
        // if there aren't any locomotives in the consist, don't let
        // the user change the direction
        if (consistModel->getRowCount() == 0) {
            locoDirectionNormal->setEnabled(false);
        } else {
            locoDirectionNormal->setEnabled(true);
        }
    }
}

/*public*/ void ConsistToolFrame::addLocoButtonActionPerformed(/*ActionEvent e*/)
{
 if (locoSelector->getAddress() == NULL) {
     return;
 }
 if (_Consist_Type == Consist::ADVANCED_CONSIST && adrSelector->getAddress() == NULL)
 {
  JOptionPane::showMessageDialog(this,
          tr("No Consist Address Selected."));
  return;
 }
 else if (_Consist_Type == Consist::ADVANCED_CONSIST
         && adrSelector->getAddress()->isLongAddress())
 {
  JOptionPane::showMessageDialog(this,
          tr("Advanced Consist requires Short Consist Address."));
  return;
 }
 else if (_Consist_Type == Consist::CS_CONSIST && adrSelector->getAddress() == NULL)
 {
  if (consistManager->csConsistNeedsSeparateAddress())
  {
   JOptionPane::showMessageDialog(this,
           tr("No Consist Address Selected."));
   return;
  }
  else
  {
   // We need to set an identifier so we can recall the
   // consist.  We're going to use the lead locomotive number
   // for this.
   adrSelector->setAddress(locoSelector->getAddress());
  }
 }
 DccLocoAddress* address = adrSelector->getAddress();
 /*
  * Make sure the marked consist type matches the consist type stored for
  * this consist
  */
 if (_Consist_Type != consistManager->getConsist(address)->getConsistType())
 {
  if (log->isDebugEnabled())
  {
   if (_Consist_Type == Consist::ADVANCED_CONSIST) {
       log->debug("Setting Consist Type to Advanced Consist");
   } else if (_Consist_Type == Consist::CS_CONSIST) {
       log->debug("Setting Consist Type to Command Station Assisted Consist");
   }
  }
  consistManager->getConsist(address)->setConsistType(_Consist_Type);
 }

 DccLocoAddress* locoaddress = locoSelector->getAddress();

 // Make sure the Address in question is allowed for this type of
 // consist, and add it to the consist if it is
 if (!consistManager->getConsist(address)->isAddressAllowed(locoaddress))
 {
  JOptionPane::showMessageDialog(this,
          tr("Selected Address not allowed in this Consist."));
 }
 else
 {
  if (consistManager->getConsist(address)->contains(locoaddress))
  {
   JOptionPane::showMessageDialog(this,
           tr("Address is already in selected Consist."));
  }
  else
  {
   consistManager->getConsist(address)->add(locoaddress, locoDirectionNormal->isChecked());
  }
  if (consistAdrBox->currentText() != adrSelector->getAddress()->toString()) {
      initializeConsistBox();
  }
  consistModel->fireTableDataChanged();
  resetLocoButtonActionPerformed(/*e*/);
 }
}

/*public*/ void ConsistToolFrame::locoSelected()
{
 if (locoRosterBox->getSelectedRosterEntries()->length() == 1)
 {
     locoSelector->setAddress(locoRosterBox->getSelectedRosterEntries()->at(0)->getDccLocoAddress());
 }
}

/*
 * we're registering as a listener for Consist events, so we need to
 * implement the interface
 */
//@Override
/*public*/ void ConsistToolFrame::consistReply(DccLocoAddress* locoaddress, int status)
{
    if (log->isDebugEnabled()) {
        log->debug("Consist Reply received for Locomotive " + locoaddress->toString() + " with status " + status);
    }
    _status->setText(consistManager->decodeErrorCode(status));
    // For some status codes, we want to trigger specific actions
    //if((status & jmri.ConsistListener.CONSIST_FULL)!=0) {
    //	canAdd();
    //} else {
    canAdd();
    //}
    consistModel->fireTableDataChanged();
    try
    {
     consistFile->writeFile(consistManager->getConsistList()->toList());
    }
    catch (Exception e) {
        log->warn("error writing consist file: " + e.getMessage());
    }
}

/*public*/ void ConsistToolFrame:: dispose() {
    JmriJFrame::dispose();
    // de-register to be notified if the consist list changes.
    consistManager->removeConsistListListener((ConsistListListener*)this);
}


// ConsistListListener interface
/*public*/ void ConsistToolFrame::notifyConsistListChanged() {
    if (_readConsistFile) {
        // read the consist file after the consist manager has
        // finished loading consists on startup.
        try {
            consistFile->readFile();
        } catch (Exception e) {
            log->warn("error reading consist file: " + e.getMessage());
        }
        _readConsistFile = false;
    }
    // update the consist list.
    initializeConsistBox();
}
#endif

/*public*/ QString ConsistToolFrame::getClassName()
{
 return "jmri.jmrit.consisttool.ConsistToolFrame";
}
/*
 * private method to scan the roster for consists
 */
/*private*/ void ConsistToolFrame::scanRoster(){
   QList<RosterEntry*> roster = Roster::getDefault()->getAllEntries();
   for(RosterEntry* entry:roster){
        DccLocoAddress* address = entry->getDccLocoAddress();
        CvTableModel*  cvTable = new CvTableModel(_status, nullptr);  // will hold CV objects
        entry->readFile();  // read, but don't yet process

        entry->loadCvModel(nullptr, cvTable);
        CvValue* cv19Value = cvTable->getCvByNumber("19");
        if(cv19Value!=nullptr && (cv19Value->getValue() & 0x7F)!=0){
            bool direction = ((cv19Value->getValue()&0x80)==0);
            DccLocoAddress* consistAddress = new DccLocoAddress((cv19Value->getValue()&0x7f),false);
            /*
             * Make sure the marked consist type is an advanced consist.
             * this consist
              */
            Consist* consist = consistManager->getConsist(consistAddress);
            if (Consist::ADVANCED_CONSIST != consist->getConsistType()) {
                consist->setConsistType(Consist::ADVANCED_CONSIST);
            }

            if (!consist->contains(address)) {
               consist->add(address, direction );
               consist->setRosterId(address, entry->titleString());
            }
        }
   }
}

/*private*/ void ConsistToolFrame::reportNoConsistSeletected(){
    JOptionPane::showMessageDialog(this,
            tr("No Consist Address Selected."));

}

/*public*/ void ConsistToolFrame::setDefaultStatus() {
    _status->setText(tr("Ready"));
}

/*private*/ /*static*/ /*final*/ Logger* ConsistToolFrame::log = LoggerFactory::getLogger("ConsistToolFrame");

