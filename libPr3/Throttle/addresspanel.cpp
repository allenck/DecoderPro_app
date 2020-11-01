#include "addresspanel.h"
#include "ui_addresspanel.h"
#include "dcclocoaddressselector.h"
#include "dcclocoaddress.h"
#include "dccthrottle.h"
#include "instancemanager.h"
#include "addresslistener.h"
#include "rosterentryselectorpanel.h"
#include <QMessageBox>
#include "throttleframemanager.h"
#include "throttlespreferences.h"
#include "jframe.h"
#include "paneopsprogframe.h"
#include "abstractthrottle.h"
#include "nceconsistrosterentry.h"
#include "nceconsistroster.h"
#include "throttlewindow.h"
#include "progdefault.h"
#include "addressedprogrammermanager.h"
#include "windowpreferences.h"
#include "locoaddressxml.h"
#include "joptionpane.h"
#include "backgroundpanel.h"
#include "defaultprogrammermanager.h"


AddressPanel::AddressPanel(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::AddressPanel)
{
 ui->setupUi(this);
 setObjectName("AddressPanel");
 throttle = NULL;
 consistThrottle = NULL;
 addrSelector = new DccLocoAddressSelector(NULL,ui->edAddress);
 currentAddress = NULL;
 consistAddress = NULL;
 listeners = NULL;
 rosterEntry = NULL;
 log = new Logger("AddressPanel");
 log->setDebugEnabled(true);

// rosterBox = new RosterEntrySelectorPanel();
// ui->rosterBoxLayout->removeWidget(ui->conRosterBox);
// ui->rosterBoxLayout->removeWidget(ui->cbRoster);
// ui->verticalLayout->removeItem(ui->rosterBoxLayout);
// ui->verticalLayout->addWidget(rosterBox);

 connect(ui->setButton, SIGNAL(clicked()), this, SLOT(OnSetButton_clicked()));
 connect(ui->rosterBox, SIGNAL(propertyChange(PropertyChangeEvent*)), this,SLOT(rosterItemSelected()));
 //connect(ui->conRosterBox, SIGNAL(currentIndexChanged(int)), this, SLOT(consistRosterSelected()));

 if (InstanceManager::throttleManagerInstance()->hasDispatchFunction()) {
     ui->dispatchButton->setEnabled(true);
 }
 else
  ui->dispatchButton->setEnabled(false);
 connect(ui->dispatchButton, SIGNAL(clicked()), this, SLOT(dispatchAddress()));
 connect(ui->releaseButton, SIGNAL(clicked()), this, SLOT(releaseAddress()));
 connect(ui->progButton, SIGNAL(clicked()),this, SLOT(openProgrammer()));
}

AddressPanel::~AddressPanel()
{
    delete ui;
}

/**
 * A JInternalFrame that provides a way for the user to enter a decoder address.
 * This class also store AddressListeners and notifies them when the user enters
 * a new address.
 *
 * @author glen Copyright (C) 2002
 * @author Daniel Boudreau Copyright (C) 2008 (add consist feature)
 * @version $Revision: 22216 $
 */
#if 0
// /*public*/ class AddressPanel extends JInternalFrame implements ThrottleListener, PropertyChangeListener {


    /**
     * Constructor
     */
    /*public*/ AddressPanel() {
        initGUI();
    }
#endif
/*public*/ void AddressPanel::destroy()
{ // Handle disposing of the throttle
    if (throttle != NULL) {
        DccLocoAddress* l = (DccLocoAddress*) throttle->getLocoAddress();
        throttle->removePropertyChangeListener((PropertyChangeListener*)this);
        InstanceManager::throttleManagerInstance()->cancelThrottleRequest(l->getNumber(), (ThrottleListener*)this);
        InstanceManager::throttleManagerInstance()->releaseThrottle(throttle, (ThrottleListener*)this);
        notifyListenersOfThrottleRelease();
        throttle = NULL;
    }
    if (consistThrottle != NULL)
    {
        InstanceManager::throttleManagerInstance()->releaseThrottle(consistThrottle, (ThrottleListener*)this);
        notifyListenersOfThrottleRelease();
        consistThrottle = NULL;
    }
}

/**
 * Add an AddressListener. AddressListeners are notified when the user
 * selects a new address and when a Throttle is acquired for that address
 *
 * @param l
 */
/*public*/ void AddressPanel::addAddressListener(AddressListener* l)
{
 if (listeners == NULL)
     listeners = new QList<AddressListener*>(/*2*/);
 if (!listeners->contains(l))
     listeners->append(l);
}

/**
 * Remove an AddressListener.
 *
 * @param l
 */
/*public*/ void AddressPanel::removeAddressListener(AddressListener* l) {
    if (listeners == NULL)
        return;
    if (listeners->contains(l))
        listeners->removeAt(listeners->indexOf(l));
}


/**
 * Gets the selected index of the roster combo box. Implemented to support
 * xboxThrottle.py
 * @return the selected index of the roster combo box
 */
/*public*/ int AddressPanel::getRosterSelectedIndex() {
    return getRosterEntrySelector()->getRosterEntryComboBox()->currentIndex();
}

/**
 * Sets the selected index of the roster combo box. Implemented to support
 * xboxThrottle.py
 * This method temporarily disables roster box actions so it can change the
 * selected index without triggering a cascade of events.
 * @param index the index to select in the combo box
 */
/*public*/ void AddressPanel::setRosterSelectedIndex(int index) {
    if (getRosterEntrySelector()->isEnabled() && index >= 0 && index < getRosterEntrySelector()->getRosterEntryComboBox()->count()) {
        getRosterEntrySelector()->getRosterEntryComboBox()->setCurrentIndex(index);
    }
    if ((backgroundPanel != NULL) && (!(rosterBox->getSelectedRosterEntries()->length() != 0))) {
        backgroundPanel->setImagePath(NULL);
        QString rosterEntryTitle = getRosterEntrySelector()->getSelectedRosterEntries()->at(0)->titleString();
        RosterEntry* re = Roster::getDefault()->entryFromTitle(rosterEntryTitle);
        if ((re != NULL) && (re->getImagePath()!=NULL)){
            backgroundPanel->setImagePath(re->getImagePath());
        }
    }
}

/*public*/ void AddressPanel::setBackgroundPanel(BackgroundPanel* bp) {
    backgroundPanel = bp;
}

/**
 * "Sets" the current roster entry. Equivalent to the user pressing the "Set"
 * button.
 * Implemented to support xboxThrottle.py
 */
/*public*/ void AddressPanel::selectRosterEntry() {
    rosterItemSelected();
}

/**
 * Get notification that a throttle has been found as we requested.
 *
 * @param t
 *            An instantiation of the DccThrottle with the address
 *            requested.
 */
/*public*/ void AddressPanel::notifyThrottleFound(DccThrottle* t)
{
 log->info("Asked for "+QString::number(currentAddress->getNumber())+" got "+ QString::number(t->getLocoAddress()->getNumber()) );
 if ( consistAddress!=NULL &&
                ((DccLocoAddress*)t->getLocoAddress())->getNumber() == consistAddress->getNumber())
 {
  // notify the listeners that a throttle was found
  // for the consist address.
  notifyConsistThrottleFound(t);
  return;
 }
 if ( ((DccLocoAddress*)t->getLocoAddress())->getNumber() != currentAddress->getNumber())
 {
  log->warn("Not correct address, asked for "+QString::number(currentAddress->getNumber())+" got "+ t->getLocoAddress()->getNumber()+", requesting again..." );
  bool requestOK =
            InstanceManager::throttleManagerInstance()->requestThrottle(currentAddress->getNumber(), currentAddress->isLongAddress(), (ThrottleListener*)this);
  if (!requestOK)
  {
   JOptionPane::showMessageDialog(mainPanel, tr("Address in use by another throttle."));
  }
  return;
 }

 throttle = t;
 ui->releaseButton->setEnabled(true);
 currentAddress = (DccLocoAddress*) t->getLocoAddress();
 addrSelector->setAddress(currentAddress);
 throttle->addPropertyChangeListener((PropertyChangeListener*)this);
 //connect((AbstractThrottle*)throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 //AbstractThrottle* at = (AbstractThrottle*)throttle;
 //connect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 // can we find a roster entry?
 if ((rosterEntry == NULL) &&
            (ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()) &&
            (ThrottleFrameManager::instance()->getThrottlesPreferences()->isEnablingRosterSearch()) &&
            addrSelector->getAddress() != NULL )
 {
  QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, QString::number(addrSelector->getAddress()->getNumber()), NULL, NULL, NULL, NULL);
  if (l.size()>0)
  {
   rosterEntry = l.at(0);
  }
 }

 // update GUI
 ui->setButton->setEnabled(false);
 addrSelector->setEnabled(false);
 getRosterEntrySelector()->setEnabled(false);
 //ui->conRosterBox->setEnabled(false);
 if (InstanceManager::throttleManagerInstance()->hasDispatchFunction())
  ui->dispatchButton->setEnabled(true);
 // enable program button if programmer available
 // for ops-mode programming
 if ((rosterEntry!=NULL) && (ProgDefault::getDefaultProgFile() != "")
     && (InstanceManager::getNullableDefault("AddressedProgrammerManager") != nullptr)
     && (((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->isAddressedModePossible()))
 {
  ui->progButton->setEnabled(true);
 }
 // send notification of new address
 for (int i = 0; i < listeners->size(); i++)
 {
  AddressListener* l = listeners->at(i);
  if (log->isDebugEnabled())
  {
   log->debug("Notify address listener of throttle acquired " + QString(l->self()->metaObject()->className()));
  }
  if (currentAddress != NULL)
  {
//   ((ThrottleWindow*)l)->notifyAddressThrottleFound((DccThrottle*)throttle);
//   connect(this, SIGNAL(notifyAddressThrottleFound(DccThrottle*)), l, SLOT(notifyAddressThrottleFound(DccThrottle*)));
//   emit notifyAddressThrottleFound(throttle);
//   disconnect(this, SIGNAL(notifyAddressThrottleFound(DccThrottle*)), l, SLOT(notifyAddressThrottleFound(DccThrottle*)));
   l->notifyAddressThrottleFound(throttle);
  }
 }
}

/*public*/ void AddressPanel::notifyFailedThrottleRequest(DccLocoAddress* /*address*/, QString reason){
    JOptionPane::showMessageDialog(NULL,reason,tr("Failed to create Throttle"),JOptionPane::WARNING_MESSAGE);
}

void AddressPanel::OnSetButton_clicked()
{
 consistAddress = NULL;
 changeOfAddress();
}

/**
 * Get notification that a consist throttle has been found as we requested.
 *
 * @param t
 *            An instantiation of the DccThrottle with the address
 *            requested.
 */
/*public*/ void AddressPanel::notifyConsistThrottleFound(DccThrottle* t)
 {
  this->consistThrottle = t;
  for (int i = 0; i < listeners->size(); i++)
  {
   AddressListener* l = listeners->at(i);
   if (log->isDebugEnabled())
    log->debug("Notify address listener of address change " + QString(l->self()->metaObject()->className()));
  l->notifyConsistAddressThrottleFound(t);
//   connect(this, SIGNAL(notifyConsistAddressThrottleFound(DccThrottle*)), l, SLOT(notifyConsistAddressThrottleFound(DccThrottle*)));
//   emit notifyConsistAddressThrottleFound(t);
//   disconnect(this, SIGNAL(notifyConsistAddressThrottleFound(DccThrottle*)), l, SLOT(notifyConsistAddressThrottleFound(DccThrottle*)));

 }
}

/**
 * Receive notification that an address has been release or dispatched.
 */
/*public*/ void AddressPanel::notifyThrottleDisposed() {
    log->debug("notifyThrottleDisposed");
    ui->dispatchButton->setEnabled(false);
    ui->releaseButton->setEnabled(false);
    ui->progButton->setEnabled(false);
    ui->setButton->setEnabled(true);
    addrSelector->setEnabled(true);
    getRosterEntrySelector()->setEnabled(true);
    //ui->conRosterBox->setEnabled(true);
    if (throttle != NULL)
    {
     throttle->removePropertyChangeListener((PropertyChangeListener*)this);
     AbstractThrottle* at = (AbstractThrottle*)throttle;
     disconnect(at, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    throttle = NULL;
    rosterEntry = NULL;
    notifyListenersOfThrottleRelease();
}

/**
 * Get the RosterEntry if there's one for this throttle.
 * @return RosterEntry or NULL
 */
/*public*/ RosterEntry* AddressPanel::getRosterEntry(){
    return rosterEntry;
}

/**
 * Set the RosterEntry for this throttle.
 */
/*public*/ void AddressPanel::setRosterEntry(RosterEntry* entry)
{
 if(entry == NULL)
  return;
 getRosterEntrySelector()->setSelectedRosterEntry(entry);
 addrSelector->setAddress(entry->getDccLocoAddress());
 if(entry != rosterEntry)
 {
  rosterEntry = entry;
  changeOfAddress();
 }
}
#if 0
/**
 * Create, initialize and place the GUI objects.
 */
/*private*/ void initGUI() {
    mainPanel = new JPanel();
    this->setContentPane(mainPanel);
    this->setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

    mainPanel.setLayout(new GridBagLayout());
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.anchor = GridBagConstraints.CENTER;
    constraints.fill = GridBagConstraints.HORIZONTAL;
    constraints.insets = new Insets(2, 2, 2, 2);
    constraints.weightx = 1;
    constraints.weighty = 0;
    constraints.gridx = 0;
    constraints.gridy = 0;

    constraints.ipadx = -16;
            if (jmri.util.SystemType.isLinux())
                constraints.ipady = 0;
            else
                constraints.ipady = -16;
    addrSelector.setVariableSize(true);
    mainPanel.add(addrSelector.getCombinedJPanel(), constraints);

    setButton = new JButton(Bundle.getMessage("ButtonSet"));
    constraints.gridx = GridBagConstraints.RELATIVE;
    constraints.fill = GridBagConstraints.NONE;
    constraints.weightx = 0;
    constraints.ipadx = constraints.ipady = 0;
    mainPanel.add(setButton, constraints);

    setButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            consistAddress = NULL;
            changeOfAddress();
        }
    });

    rosterBox = new RosterEntrySelectorPanel();
    getRosterEntrySelector().setNonSelectedItem(Bundle.getMessage("NoLocoSelected"));
    getRosterEntrySelector().setToolTipText(Bundle.getMessage("SelectLocoFromRosterTT"));
    getRosterEntrySelector().addPropertyChangeListener("selectedRosterEntries", new PropertyChangeListener() {

        @Override
        /*public*/ void propertyChange(PropertyChangeEvent pce) {
            rosterItemSelected();
        }
    });

    constraints.gridx = 0;
    constraints.gridy = GridBagConstraints.RELATIVE;
    constraints.fill = GridBagConstraints.HORIZONTAL;
    constraints.weightx = 1;
    constraints.weighty = 0;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    mainPanel.add(getRosterEntrySelector(), constraints);

    conRosterBox = NceConsistRoster.instance().fullRosterComboBox();
    if (NceConsistRoster.instance().numEntries() > 0) {
        conRosterBox.insertItemAt(new NULLComboBoxConsist(), 0);
        conRosterBox.setSelectedIndex(0);
        conRosterBox.setToolTipText(Bundle.getMessage("SelectConsistFromRosterTT"));
        conRosterBox.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                consistRosterSelected();
            }
        });
        constraints.gridx = 0;
        constraints.gridy = GridBagConstraints.RELATIVE;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.weightx = 1;
        constraints.weighty = 0;
        mainPanel.add(conRosterBox, constraints);
    }

    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new FlowLayout());
    dispatchButton = new JButton(Bundle.getMessage("ButtonDispatch"));
    buttonPanel.add(dispatchButton);
    dispatchButton.setEnabled(false);
    dispatchButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            dispatchAddress();
        }
    });

    releaseButton = new JButton(Bundle.getMessage("ButtonRelease"));
    buttonPanel.add(releaseButton);
    releaseButton.setEnabled(false);
    releaseButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            releaseAddress();
        }
    });

    progButton = new JButton(Bundle.getMessage("ButtonProgram"));
    buttonPanel.add(progButton);
    progButton.setEnabled(false);
    progButton.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            openProgrammer();
        }
    });

    constraints.gridx = 0;
    constraints.gridy = GridBagConstraints.RELATIVE;
    constraints.gridwidth = 2;
    constraints.weighty = 0;
    constraints.insets = new Insets(0, 0, 0, 0);
    mainPanel.add(buttonPanel, constraints);

    pack();
}
#endif
/*private*/ void AddressPanel::rosterItemSelected()
{
 if (getRosterEntrySelector()->getSelectedRosterEntries()->length() != 0)
 {
  setRosterEntry(getRosterEntrySelector()->getSelectedRosterEntries()->at(0));
  consistAddress = NULL;
 }
}

/*private*/ void AddressPanel::consistRosterSelected()
{
 //if (!(conRosterBox.getSelectedItem() instanceof NULLComboBoxConsist))
 //if(ui->conRosterBox->currentText() != NULLComboBoxConsist::toString())
 {
#if 1
    QString rosterEntryTitle = ui->rosterBox->getRosterEntryComboBox()->currentText();
    NceConsistRosterEntry* cre = static_cast<NceConsistRoster*>(InstanceManager::getDefault("NceConsistRoster"))
            ->entryFromTitle(rosterEntryTitle);

    DccLocoAddress* a = new DccLocoAddress(cre->getLoco1DccAddress().toInt(), cre->isLoco1LongAddress());
    addrSelector->setAddress(a);
    consistAddress = NULL;
    int cA = 0;
    try {
        cA = cre->getConsistNumber().toInt();
    } catch (NumberFormatException e) {

    }
    if (0 < cA && cA < 128) {
        consistAddress = new DccLocoAddress(cA, false);
    } else {
        log->warn("consist number missing " + cre->getLoco1DccAddress());
//        JOptionPane.showMessageDialog(mainPanel,
//                Bundle.getMessage("ConsistNumberHasNotBeenAssigned"),
//                Bundle.getMessage("NeedsConsistNumber"),
//                JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(mainPanel, tr("Error"), tr("Consist Number Has Not Been Assigned"));
        return;
    }
//    if (JOptionPane.showConfirmDialog(mainPanel,
//            Bundle.getMessage("SendFunctionToLead"), Bundle.getMessage("NCEconsistThrottle"),
//            JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION)
    if(QMessageBox::question(mainPanel, tr("Send Function to Lead"), tr("NCEconsistThrottle"),QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
    {
        addrSelector->setAddress(consistAddress);
        consistAddress = NULL;
    }
    changeOfAddress();
#endif
 }
}

/**
 * The user has selected a new address. Notify all listeners->
 */
/*private*/ void AddressPanel::changeOfAddress()
{
 currentAddress = addrSelector->getAddress();
 if (currentAddress == NULL)
  return;	// no address
 // send notification of new address
 for (int i = 0; i < listeners->size(); i++)
 {
  AddressListener* l = listeners->at(i);
  if (log->isDebugEnabled())
   log->debug("Notify address listener of address change " + QString(l->self()->metaObject()->className()));
  //connect(this, SIGNAL(notifyAddressChosen(LocoAddress*)), l, SLOT(notifyAddressChosen(LocoAddress*)));
  //emit notifyAddressChosen(currentAddress);
  //disconnect(this, SIGNAL(notifyAddressChosen(LocoAddress*)), l, SLOT(notifyAddressChosen(LocoAddress*)));
  l->notifyAddressChosen(currentAddress);
 }

 log->debug("Requesting new slot for address "+currentAddress->toString());
 bool requestOK;
 if (rosterEntry == nullptr) {
     requestOK = InstanceManager::throttleManagerInstance()->requestThrottle(currentAddress, this, true);
 }
 else {
     requestOK = InstanceManager::throttleManagerInstance()->requestThrottle(rosterEntry, this, true);
 }
 if (!requestOK)
  JOptionPane::showMessageDialog(mainPanel, tr("Address in use by another throttle."));
}

/*private*/ void AddressPanel::changeOfConsistAddress()
{
 if (consistAddress == NULL)
  return;	// no address
 // send notification of new address
 for (int i = 0; i < listeners->size(); i++)
 {
  AddressListener* l = listeners->at(i);
  if (log->isDebugEnabled())
      log->debug("Notify address listener of address change " + QString(l->self()->metaObject()->className()));
  //l->notifyConsistAddressChosen(consistAddress->getNumber(), consistAddress->isLongAddress());
//  connect(this, SIGNAL(notifyConsistAddressChosen(DccLocoAddress*)), l, SLOT(notifyConsistAddressChosen(int,bool)));
//  emit notifyConsistAddressChosen(consistAddress->getNumber(), consistAddress->isLongAddress());
//  disconnect(this, SIGNAL(notifyConsistAddressChosen(DccLocoAddress*)), l, SLOT(notifyConsistAddressChosen(int,bool)));
  l->notifyConsistAddressChosen(consistAddress->getNumber(), consistAddress->isLongAddress());
 }

 bool requestOK =
     InstanceManager::throttleManagerInstance()->requestThrottle(consistAddress->getNumber(), consistAddress->isLongAddress(), (ThrottleListener*)this);
 if (!requestOK)
     //JOptionPane.showMessageDialog(mainPanel, Bundle.getMessage("AddressInUse"));
     QMessageBox::warning(mainPanel, tr("Warning"), tr("Address in use by another throttle."));
}

/**
 * Open a programmer for this address
 */
/*protected*/ void AddressPanel::openProgrammer()
{
 if (rosterEntry == NULL)
  return;
 //java.util.ResourceBundle rbt = java.util.ResourceBundle.getBundle("jmri.jmrit.symbolicprog.SymbolicProgBundle");
 QString title = tr("Program %1 in Operations Mode (Main Track)").arg(rosterEntry->getId());
 // find the ops-mode programmer
 int address = rosterEntry->getDccAddress().toInt();
 bool longAddr = true;
 if (address<100) longAddr = false;
 Programmer* programmer = (Programmer*)((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager"))->getAddressedProgrammer(longAddr, address);
 // and created the frame
 JFrame* p = new PaneOpsProgFrame(NULL, rosterEntry,
                                     title, "programmers"+QString(QDir::separator())+ProgDefault::getDefaultProgFile()+".xml",
                                     programmer);
 p->pack();
 p->setVisible(true);
}

/**
 * Dispatch the current address for use by other throttles
 */
/*public*/ void AddressPanel::dispatchAddress()
{
 if (throttle != NULL)
 {
  InstanceManager::throttleManagerInstance()->dispatchThrottle(throttle, (ThrottleListener*)this);
  if (consistThrottle != NULL)
  {
   InstanceManager::throttleManagerInstance()->dispatchThrottle(consistThrottle, (ThrottleListener*)this);
   consistThrottle = NULL;
  }
  notifyThrottleDisposed();
 }
}

/**
 * Release the current address.
 */
/*public*/ void AddressPanel::releaseAddress() {
    InstanceManager::throttleManagerInstance()->releaseThrottle(throttle, (ThrottleListener*)this);
    if (consistThrottle != NULL) {
        InstanceManager::throttleManagerInstance()->releaseThrottle(consistThrottle, (ThrottleListener*)this);
        consistThrottle = NULL;
    }
    notifyThrottleDisposed();
}

/*private*/ void AddressPanel::notifyListenersOfThrottleRelease()
{
 if (listeners != NULL)
 {
  for (int i = 0; i < listeners->size(); i++)
  {
   AddressListener* l = listeners->at(i);
   if (log->isDebugEnabled()) {
       log->debug("Notify address listener of release " + QString(l->self()->metaObject()->className()));
   }
//   connect(this, SIGNAL(notifyAddressReleased(LocoAddress*)), l, SLOT(notifyAddressReleased(LocoAddress*)));
//   emit notifyAddressReleased(currentAddress);
   l->notifyAddressReleased(currentAddress);
//   disconnect(this, SIGNAL(notifyAddressReleased(LocoAddress*)), l, SLOT(notifyAddressReleased(LocoAddress*)));

  }
 }
}
#if 1
/**
 * Create an QDomElementof this object's preferences.
 * <ul>
 * <li> Window Preferences
 * <li> Address value
 * </ul>
 *
 * @return org.jdom.QDomElementfor this objects preferences. Defined in
 *         DTD/throttle-config
 */
/*public*/ QDomElement AddressPanel::getXml() {
 QDomDocument doc = QDomDocument();
    QDomElement me = doc.createElement("AddressPanel");
    //QDomElementwindow = doc.createElement("window");
//    java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);
//    children.add(WindowPreferences.getPreferences(this));
    QDomElement elem = WindowPreferences::getPreferences(this);
    me.appendChild(elem);
//    children.add((new jmri.configurexml.LocoAddressXml())
//            .store(addrSelector.getAddress()));
    elem = (new LocoAddressXml())->store(addrSelector->getAddress());
    me.appendChild(elem);
//    children.add((new jmri.configurexml.LocoAddressXml())
//            .store(consistAddress));
    elem = (new LocoAddressXml())->store(consistAddress);
    me.appendChild(elem);
//    me.setContent(children);
    return me;
}

/**
 * Use the QDomElementpassed to initialize based on user prefs.
 *
 * @param e
 *            The QDomElementcontaining prefs as defined in DTD/throttle-config
 */
//@SuppressWarnings("unchecked")
/*public*/ void AddressPanel::setXml(QDomElement e)
{
 QDomElement window = e.firstChildElement("window");
 WindowPreferences::setPreferences(this, window);

 QDomElement addressElement= e.firstChildElement("address");
 if ((addressElement!= QDomElement()) && ( this->getRosterEntry() == NULL))
 {
     QString address = addressElement.attribute("value");
     addrSelector->setAddress(new DccLocoAddress(address.toInt(), false)); // guess at the short/long
     consistAddress = NULL;
     changeOfAddress();
 }

 QDomNodeList elementList = e.elementsByTagName("locoaddress");
 if ((elementList.size() > 0) && (getThrottle() == NULL))
 {
     log->debug("found " + QString::number(elementList.size()) +" locoaddress");
     addrSelector->setAddress((DccLocoAddress*) (new LocoAddressXml())
             ->getAddress(elementList.at(0).toElement()));
     consistAddress = NULL;
     // if there are two locoaddress, the second is the consist address
     if (elementList.size() > 1){
         consistAddress = ((DccLocoAddress*) (new LocoAddressXml())
                 ->getAddress(elementList.at(1).toElement()));
     }
     changeOfAddress();
 }
}
#endif
/**
 * @return the RosterEntrySelectorPanel
 */
/*public*/ RosterEntrySelectorPanel* AddressPanel::getRosterEntrySelector() {
    return ui->rosterBox;
}

//static class NULLComboBoxConsist {
//    @Override
//    /*public*/ String toString() {
//        return Bundle.getMessage("NoConsistSelected");
//    }
//};

/*public*/ DccThrottle* AddressPanel::getThrottle() {
    return throttle;
}

/*public*/ DccLocoAddress* AddressPanel::getCurrentAddress() {
    return currentAddress;
}

/*public*/ void AddressPanel::setCurrentAddress(DccLocoAddress* currentAddress) {
            if(log->isDebugEnabled()) log->debug("Setting CurrentAddress to " + currentAddress->toString());
    this->addrSelector->setAddress(currentAddress);
    changeOfAddress();
}


/*public*/ void AddressPanel::setAddress(int consistNumber, bool b) {
    setCurrentAddress(new DccLocoAddress(consistNumber,b));
}

/*public*/ DccLocoAddress* AddressPanel::getConsistAddress() {
    return consistAddress;
}

/*public*/ void AddressPanel::setConsistAddress(DccLocoAddress* consistAddress) {
            if(log->isDebugEnabled()) log->debug("Setting Consist Address to " + consistAddress->toString());
    this->consistAddress = consistAddress;
    changeOfConsistAddress();

}

//	static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AddressPanel.class.getName());

/*public*/ void AddressPanel::propertyChange(PropertyChangeEvent* evt)
{
 if (evt == NULL) return;
 if ("ThrottleConnected"== (evt->getPropertyName()))
 {
  if ( ( true == evt->getOldValue().toBool()) && ( false ==  evt->getNewValue().toBool()) )
  {
   log->debug("propertyChange: ThrottleConnected to false");
   notifyThrottleDisposed();
  }
 }
}


