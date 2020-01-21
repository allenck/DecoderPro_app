#include "sensortableaction.h"
#include "jtextfield.h"
#include <QComboBox>
#include <QCheckBox>
#include "addnewhardwaredevicepanel.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include <QVBoxLayout>
#include "connectionnamefromsystemname.h"
#include "jmriuserpreferencesmanager.h"
#include "userpreferencesmanager.h"
#include <QMessageBox>
#include "jframe.h"
#include "flowlayout.h"
#include "beantabledatamodel.h"
#include <QMenu>
#include <QMenuBar>
#include "sensortabledatamodel.h"
#include "beantableframe.h"
#include "jtable.h"
#include <QLabel>
#include "connectionnamefromsystemname.h"
#include "abstracttabletabaction.h"
#include <QPushButton>
#include "joptionpane.h"
#include "colorutil.h"
#include "internalsensormanager.h"

SensorTableAction::SensorTableAction(QObject *parent) :
    AbstractTableAction(tr("Sensor Table"), parent)
{
}
/**
 * Swing action to create and register a
 * SensorTable GUI.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2009
 * @version     $Revision: 20934 $
 */

///*public*/ class SensorTableAction extends AbstractTableAction {

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param actionName
 */
/*public*/ SensorTableAction::SensorTableAction(QString actionName, QObject *parent) : AbstractTableAction(actionName, parent)
{
    //super(actionName);
 addFrame = nullptr;
// if(parent == NULL)
//  return;

 hardwareAddressTextField = new JTextField(40);
 userNameField = new JTextField(40);
 prefixBox = new QComboBox();
 numberToAdd = new JTextField(5);
 numberToAdd->setValidator(new QIntValidator(1,100));
 numberToAddSpinner = new QSpinBox(/*rangeSpinner*/);
 numberToAddSpinner->setMinimum(1);
 numberToAddSpinner->setMaximum(100);
 numberToAddSpinner->setValue(1);
 numberToAddSpinner->setSingleStep(1);
 rangeBox = new QCheckBox(tr("Add a range:"));
 sysNameLabel = new QLabel("Hardware Address:");
 userNameLabel = new QLabel(tr("User Name:"));
 systemSelectionCombo = QString( metaObject()->className())+".SystemSelected";
 userNameError = QString( metaObject()->className())+".DuplicateUserName";
 showDebounceBox = new QCheckBox(tr("Show Sensor Debounce Information"));
 statusBarLabel = new QLabel(tr("Enter a Hardware Address and (optional) User Name.")/*, JLabel.LEADING*/);

 senManager = InstanceManager::sensorManagerInstance();
 enabled = true;
 m = nullptr;
 connectionChoice = "";
 hardwareAddressTextField = new /*CheckedTextField*/JTextField(20);
 statusBar = new QLabel(tr("Enter a Hardware Address and (optional) User Name.")/*, JLabel.LEADING*/);

 // disable ourself if there is no primary sensor manager available
 if (senManager==nullptr)
 {
  setEnabled(false);
 }
}
// /*public*/ SensorTableAction() { this("Sensor Table");}

//@Override
/*public*/ void SensorTableAction::setManager(Manager* man)
{
 senManager = static_cast<SensorManager*>(man);
 if (m!=nullptr)
  m->setManager(senManager);;
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Sensors
 */
//@Override
/*protected*/ void SensorTableAction::createModel()
{
 m = new SensorTableDataModel(senManager,nullptr);
}

//@Override
/*protected*/ void SensorTableAction::setTitle() {
    f->setTitle(tr("Sensor Table"));
}

//@Override
/*protected*/ QString SensorTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SensorTable";
}


/*protected*/ void SensorTableAction::addPressed()
{
 p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");

 if (addFrame==nullptr)
 {
  addFrame = new JmriJFrameX(tr("Add Sensor"),false, true);
  addFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  //addFrame.addHelpMenu("package.jmri.jmrit.beantable.SensorAddEdit", true);
  QVBoxLayout* addFrameLayout = (QVBoxLayout*)addFrame->getContentPane()->layout();
  if(addFrameLayout == nullptr)
  {
   QWidget* centralWidget = new QWidget;
   addFrameLayout = new QVBoxLayout(centralWidget);
   addFrame->setCentralWidget(centralWidget);
  }
  //addFrame.getContentPane().setLayout(new BoxLayout(addFrame.getContentPane(), BoxLayout.Y_AXIS));

//        ActionListener listener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    okPressed(e);
//                }
//            };
  STOkButtonActionListener* listener = new STOkButtonActionListener(this);

//        ActionListener rangeListener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    canAddRange(e);
//                }
//            };
  STCancelActionListener* cancelListener = new STCancelActionListener(this);
  STRangeActionListener* rangeListener = new STRangeActionListener(this);
  if (QString(InstanceManager::sensorManagerInstance()->metaObject()->className()).contains("ProxySensorManager"))
  {
   ProxySensorManager* proxy = ((ProxySensorManager*) InstanceManager::sensorManagerInstance());
   QList<Manager*> managerList = proxy->getDisplayOrderManagerList();
   for(int x = 0; x<managerList.size(); x++)
   {
    QString manuName = ConnectionNameFromSystemName::getConnectionName(static_cast<AbstractManager*>(managerList.at(x))->getSystemPrefix());
    bool addToPrefix = true;
    //Simple test not to add a system with a duplicate System prefix
    for (int i = 0; i<prefixBox->count(); i++)
    {
     if(prefixBox->itemText(i)==(manuName))
      addToPrefix=false;
    }
    if (addToPrefix)
     prefixBox->addItem(manuName);
   }
   if(p->getComboBoxLastSelection(systemSelectionCombo)!= "")
     prefixBox->setCurrentIndex(prefixBox->findText(p->getComboBoxLastSelection(systemSelectionCombo)));
  }
  else
  {
   prefixBox->addItem(ConnectionNameFromSystemName::getConnectionName(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSystemPrefix()));
  }
  hardwareAddressTextField->setObjectName("sysName");
  userNameField->setObjectName("userName");
  prefixBox->setObjectName("prefixBox");
  addButton = new QPushButton("Create");
  connect(addButton, SIGNAL(clicked()), this, SLOT(createPressed()));
  // Define PropertyChangeListener
//  colorChangeListener = new PropertyChangeListener()
//  {
//      @Override
//      public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
//          String property = propertyChangeEvent.getPropertyName();
//          if ("background".equals(property)) {
//              if ((Color) propertyChangeEvent.getNewValue() == Color.white) { // valid entry
//                  addButton.setEnabled(true);
//              } else { // invalid
//                  addButton.setEnabled(false);
//              }
//          }
//      }
//  };
  //ColorChangeListener* colorChangeListener = new ColorChangeListener(this);
//  TODO: hardwareAddressTextField->addPropertyChangeListener(colorChangeListener);
  connect(hardwareAddressTextField, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  // create panel
  addFrame->getContentPane()->layout()->addWidget(new AddNewHardwareDevicePanel(hardwareAddressTextField, userNameField, prefixBox,
      numberToAddSpinner, rangeBox, addButton, cancelListener, rangeListener, statusBarLabel));
// tooltip for hwAddressTextField will be assigned later by canAddRange()
  canAddRange();
 }
 hardwareAddressTextField->setValidator(validator = new STAValidator(hardwareAddressTextField,this));

 hardwareAddressTextField->setObjectName("hwAddressTextField"); // for GUI test NOI18N
 hardwareAddressTextField->setBackground(QColor(Qt::yellow));
 addButton->setEnabled(false); // start as disabled (false) until a valid entry is typed in
 addButton->setObjectName("createButton"); // for GUI test NOI18N
 // reset statusBar text
 statusBar->setText(tr("HardwareAddStatusEnter"));
 statusBar->setStyleSheet("QLabel {color: gray}");

 addFrame->pack();
 addFrame->setVisible(true);
}

/*public*/ void SensorTableAction::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
    QString property = propertyChangeEvent->getPropertyName();
    if ("background" == (property)) {
        if ( propertyChangeEvent->getNewValue().value<QColor>() == QColor(Qt::white)) { // valid entry
            addButton->setEnabled(true);
        } else { // invalid
            addButton->setEnabled(false);
        }
    }
}

STOkButtonActionListener::STOkButtonActionListener(SensorTableAction *act)
{
 this->act = act;
}
void STOkButtonActionListener::actionPerformed()
{
 act->createPressed();
}
STCancelActionListener::STCancelActionListener(SensorTableAction *act) { this->act = act;}
void STCancelActionListener::actionPerformed()
{
 act->cancelPressed();
}

STRangeActionListener::STRangeActionListener(SensorTableAction *act)
{
 this->act = act;
}
void STRangeActionListener::actionPerformed()
{
 act->canAddRange();
}

void SensorTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = nullptr;
}

/**
 * Respond to Create new item pressed on Add Sensor pane
 *
 * @param e the click event
 */
void SensorTableAction::createPressed()
{
 /*String user = userName.getText();
 if (user==("")) user=NULL;*/

 int numberOfSensors = 1;

 if(rangeBox->isChecked())
 {
//        try {
  numberOfSensors = numberToAdd->text().toInt();
//        } catch (NumberFormatException ex) {
//            log.error("Unable to convert " + numberToAdd.getText() + " to a number");
//            jmri.InstanceManager.getDefault(jmri.UserPreferencesManager.class).
//                            showInfoMessage("Error","Number to Sensors to Add must be a number!",""+ex, "",true, false, org.apache.log4j.Level.ERROR);
//            return;
//        }
 }
 if (numberOfSensors>=65)
 {
//   if(JOptionPane.showConfirmDialog(addFrame,
//                                             "You are about to add " + numberOfSensors + " Sensors into the configuration\nAre you sure?","Warning",
//                                             JOptionPane.YES_NO_OPTION)==1)
  QMessageBox::warning(addFrame, tr("Warning"),tr("You are about to add ") + QString::number(numberOfSensors) + tr(" Sensors into the configuration\nAre you sure?"));
  return;
 }
 QString sensorPrefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText());

 QString sName = nullptr;
 QString curAddress = hardwareAddressTextField->text();

 // initial check for empty entry
 if (curAddress.length() < 1)
 {
     statusBar->setText(tr("You must provide a Hardware Address to start."));
     statusBar->setStyleSheet("QLabel {color: red}");
     hardwareAddressTextField->setBackground(QColor(Qt::red));
     return;
 } else {
     hardwareAddressTextField->setBackground(QColor(Qt::white));
 }

 QString statusMessage = tr("New %1(s) added:").arg(tr("Sensor"));
 QString errorMessage = "";
 for (int x = 0; x < numberOfSensors; x++)
 {
  try
  {
   curAddress = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getNextValidAddress(curAddress, sensorPrefix);
  }
  catch (JmriException ex)
  {
   ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                 showErrorMessage("Error", "Unable to convert '" + curAddress + "' to a valid Hardware Address",  ex.getMessage(), "", true, false);
   return;
  }
  if (curAddress == "")
  {
   //The next address is already in use, therefore we stop.
   break;
  }

  // Compose the proposed system name from parts:
 sName = sensorPrefix + InstanceManager::sensorManagerInstance()->typeLetter() + curAddress;
 Sensor* s = nullptr;
 try {
     s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(sName);
 } catch (IllegalArgumentException ex) {
     // user input no good
     handleCreateException(sName);
     // Show error message in statusBar
     errorMessage = tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip).");
     statusBar->setText(errorMessage);
     statusBar->setStyleSheet("QLabel {color: gray}");
     return;   // return without creating
 }

 QString user = userNameField->text().trimmed();
 if ((x != 0) && !user.isEmpty()) {
     user = userNameField->text() + ":" + x; // add :x to user name starting with 2nd item
 }
 if (!user.isEmpty() && (InstanceManager::sensorManagerInstance()->getByUserName(user) == nullptr)) {
     s->setUserName(user);
 } else if (!user.isEmpty() && InstanceManager::sensorManagerInstance()->getByUserName(user) != nullptr && !p->getPreferenceState(getClassName(), "duplicateUserName")) {
     static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))->
             showErrorMessage(tr("Error"), tr("The specified user name \"%1\" is already in use and therefore will not be set.").arg(user), getClassName(), "duplicateUserName", false, true);
 }

 // add first and last names to statusMessage user feedback string
 if (x == 0 || x == numberOfSensors - 1) {
     statusMessage = statusMessage + " " + sName + " (" + user + ")";
 }
 if (x == numberOfSensors - 2) {
     statusMessage = statusMessage + " " + tr("up to") + " ";
 }
 // only mention first and last of range added

 // end of for loop creating range of Sensors }
}
 // provide feedback to user
         if (errorMessage == "") {
             statusBar->setText(statusMessage);
             statusBar->setStyleSheet("QLabel {color: gray}");
         } else {
             statusBar->setText(errorMessage);
             // statusBar.setForeground(Color.red); // handled when errorMassage is set to differentiate urgency
         }

         p->setComboBoxLastSelection(systemSelectionCombo,  prefixBox->currentText());
         addFrame->setVisible(false);
         addFrame->dispose();
         addFrame = nullptr;
         //addButton.removePropertyChangeListener(colorChangeListener);
}

/*private*/ void SensorTableAction::canAddRange()
{
 rangeBox->setEnabled(false);
 rangeBox->setChecked(false);
 connectionChoice =  prefixBox->currentText(); // store in Field for CheckedTextField
 if (connectionChoice == "") {
     // Tab All or first time opening, default tooltip
     connectionChoice = "TBD";
 }
 if(qobject_cast<ProxySensorManager*>(senManager)!=nullptr)
 {
  ProxySensorManager* proxy = (ProxySensorManager*) senManager;
  QList<Manager*> managerList = proxy->getDisplayOrderManagerList();
  QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName(connectionChoice);
  foreach (Manager* mgr, managerList)
  {
   if (mgr->getSystemPrefix() == (systemPrefix))
   {
       rangeBox->setEnabled( ((SensorManager*)mgr)->allowMultipleAdditions(systemPrefix));
       // get tooltip from ProxySensorManager
       addEntryToolTip = mgr->getEntryToolTip();
       log->debug("S add box enabled1");
       break;
   }
  }
 }
 else if (senManager->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName(connectionChoice)))
 {
  rangeBox->setEnabled(true);
  log->debug("S add box enabled2");
  // get tooltip from sensor manager
  addEntryToolTip = senManager->getEntryToolTip();
  log->debug("SensorManager tip");
 }
 // show hwAddressTextField field tooltip in the Add Sensor pane that matches system connection selected from combobox
 hardwareAddressTextField->setToolTip("<html>"
         + tr("For %1 %2 use one of these patterns:").arg(connectionChoice).arg(tr("Sensors"))
         + "<br>" + addEntryToolTip + "</html>");
 hardwareAddressTextField->setBackground(QColor(Qt::yellow)); // reset
 addButton->setEnabled(true); // ambiguous, so start enabled

}

void SensorTableAction::handleCreateException(QString sysName) {
//    javax.swing.JOptionPane.showMessageDialog(addFrame,
//            java.text.MessageFormat.format(
//                tr("ErrorSensorAddFailed"),
//                new Object[] {sysName}),
//            tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(addFrame, tr("Error"), tr("Could not create sensor \"%1\" to add it. Check that number/name is OK.").arg(sysName));
}

/*protected*/ void SensorTableAction::setDefaultDebounce(JFrame* _who){
    JTextField* activeField = new JTextField(QString::number(((ProxySensorManager*)senManager)->getDefaultSensorDebounceGoingActive()),4);
    activeField->setValidator(new QIntValidator(0,4000));
    JTextField* inActiveField = new JTextField(QString::number(((ProxySensorManager*)senManager)->getDefaultSensorDebounceGoingInActive()),4);
    inActiveField->setValidator(new QIntValidator(0,4000));

    //JPanel active = new JPanel();
    FlowLayout* activeLayout = new FlowLayout;
    activeLayout->addWidget(new QLabel(tr("Debounce Active Timer")));
    activeLayout->addWidget(activeField);

    //JPanel inActive = new JPanel();
    FlowLayout* inActiveLayout = new FlowLayout;
    inActiveLayout->addWidget(new QLabel(tr("Debounce InActive Timer")));
    inActiveLayout->addWidget(inActiveField);

//    int retval = JOptionPane.showOptionDialog(_who,
//                                      tr("SensorGlobalDebounceMessageBox") , tr("SensorGlobalDebounceMessageTitle"),
//                                      0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                      new Object[]{"Cancel", "OK", active, inActive}, nullptr );
    int retval = QMessageBox::information(_who, tr("Sensor Debounce Timer"), tr("Duration is in Milliseconds"), QMessageBox::Cancel | QMessageBox::Ok );
    if (retval != QMessageBox::Yes) {
        return;
    }

    //We will allow the turnout manager to handle checking if the values have changed
//    try {
        long goingActive = activeField->text().toLong();
        ((ProxySensorManager*)senManager)->setDefaultSensorDebounceGoingActive(goingActive);
//    } catch (NumberFormatException ex) {
//        JOptionPane.showMessageDialog(_who, tr("SensorDebounceActError")+"\n" + activeField.getText(), "Input Error", JOptionPane.ERROR_MESSAGE);
//    }

//    try {
        long goingInActive = inActiveField->text().toLong();
        senManager->setDefaultSensorDebounceGoingInActive(goingInActive);
//    } catch (NumberFormatException ex) {
//        JOptionPane.showMessageDialog(_who, tr("SensorDebounceActError")+"\n" + inActiveField.getText(), "Input Error", JOptionPane.ERROR_MESSAGE);
//    }
    m->fireTableDataChanged();
}
/*protected*/ void SensorTableAction::setDefaultState(JFrame* _who)
{
 QStringList sensorStates = QStringList() << tr("Unknown")<< tr("Inactive") << tr("Active")<< tr("Inconsistent");
 QComboBox* stateCombo = new QComboBox();
 stateCombo->addItems(sensorStates);
 switch (InternalSensorManager::getDefaultStateForNewSensors())
 {
  case Sensor::ACTIVE:
      stateCombo->setCurrentIndex(stateCombo->findText(tr("Active")));
      break;
  case Sensor::INACTIVE:
      stateCombo->setCurrentIndex(stateCombo->findText(tr("Inactive")));
      break;
  case Sensor::INCONSISTENT:
      stateCombo->setCurrentIndex(stateCombo->findText(tr("Inconsistent")));
      break;
  default:
      stateCombo->setCurrentIndex(stateCombo->findText(tr("Unknown")));
 }
// int retval = JOptionPane.showOptionDialog(_who,
//         tr("SensorInitialStateMessageBox"), tr("InitialSensorState"),
//         0, JOptionPane.INFORMATION_MESSAGE, null,
//         new Object[]{tr("ButtonCancel"), tr("ButtonOK"), stateCombo}, null);
// if (retval != 1)
 if(QMessageBox::information(_who, tr("Initial Sensor State"),tr("Set the Initial State of Internal Sensors when created or loaded"),QMessageBox::Ok | QMessageBox::Cancel)== QMessageBox::Cancel)
 {
     return;
 }
 int defaultState = Sensor::UNKNOWN;
 QString selectedState =  stateCombo->currentText();
 if (selectedState==(tr("Active")))
 {
     defaultState = Sensor::ACTIVE;
 }
 else if (selectedState==(tr("Inactive")))
 {
     defaultState = Sensor::INACTIVE;
 }
 else if (selectedState==(tr("Inconsistent")))
 {
     defaultState = Sensor::INCONSISTENT;
 }
}

/*public*/ void SensorTableAction::setMenuBar(JmriJFrame* f)
{
    JmriJFrame* finalF = f;			// needed for anonymous ActionListener class
    QMenuBar* menuBar = f->menuBar();

    QMenu* optionsMenu = new QMenu(tr("Debounce"));
    QAction* item = new QAction(tr("Defaults..."),this);
    optionsMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                setDefaultDebounce(finalF);
//        }
//        });
    DebounceActionListener* listener = new DebounceActionListener(finalF, this);
    connect(item, SIGNAL(triggered()), listener, SLOT(actionPerformed()));
    item = new QAction(tr("Initial Sensor State"),this);
    optionsMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            setDefaultState(finalF);
//        }
//    });
    DefaultStateActionListener* dsListener = new DefaultStateActionListener(finalF,this);
    connect(item, SIGNAL(triggered()), dsListener, SLOT(actionPerformed()));
    menuBar->addMenu(optionsMenu);
}

DebounceActionListener::DebounceActionListener(JmriJFrame *finalF, SensorTableAction *act)
{
 this->finalF = finalF;
 this->act = act;
}
void DebounceActionListener::actionPerformed(ActionEvent */*e*/)
{
 act->setDefaultDebounce(finalF);
}
DefaultStateActionListener::DefaultStateActionListener(JmriJFrame *finalF, SensorTableAction *act)
{
 this->finalF = finalF;
 this->act = act;
}

void DefaultStateActionListener::actionPerformed(ActionEvent */*e*/)
{
 act->setDefaultState(finalF);
}

void SensorTableAction::showDebounceChanged(bool bChecked)
{
    SensorTableDataModel* a = (SensorTableDataModel*)m;
    a->showDebounce(/*showDebounceBox->isChecked()*/bChecked);
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setSimplePreferenceState(getClassName()+".SensorTableAction"+".showDebounce", bChecked);
}


/*public*/ void SensorTableAction::addToFrame(BeanTableFrame* f)
{
    f->addToBottomBox(showDebounceBox, "SensorTableAction");
    showDebounceBox->setToolTip(tr("Show extra columns for configuring sensor debounce timers"));
//    showDebounceBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            showDebounceChanged();
//        }
//    });
    showDebounceBox->setChecked(((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->getSimplePreferenceState(getClassName()+".SensorTableAction"+".showDebounce"));
    connect(showDebounceBox, SIGNAL(clicked(bool)), this, SLOT(showDebounceChanged(bool)) );
}

/*public*/ void SensorTableAction::addToPanel(AbstractTableTabAction* f) {
    QString systemPrefix = ConnectionNameFromSystemName::getConnectionName(senManager->getSystemPrefix());

    if (QString(senManager->metaObject()->className()).contains("ProxySensorManager"))
        systemPrefix = "All";
    f->addToBottomBox(showDebounceBox, systemPrefix);
    showDebounceBox->setToolTip(tr("Show extra columns for configuring sensor debounce timers"));
//    showDebounceBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            showDebounceChanged();
//        }
//    });
    connect(showDebounceBox, SIGNAL(clicked(bool)), this, SLOT(showDebounceChanged(bool)));
}

/*public*/ void SensorTableAction::setMessagePreferencesDetails(){
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setPreferenceItemDetails(getClassName(), "duplicateUserName",  tr("Hide Duplicate User Name Warning Message"));
AbstractTableAction::setMessagePreferencesDetails();
}

/*protected*/ QString SensorTableAction::getClassName() { return "jmri.jmrit.beantable.SensorTableAction"; }

/*public*/ QString SensorTableAction::getClassDescription() { return tr("Sensor Table"); }

//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SensorTableAction.class.getName());
//}
#if 0
/**
 * Sets whether the {@code Action} is enabled. The default is {@code true}.
 *
 * @param newValue  {@code true} to enable the action, {@code false} to
 *                  disable it
 * @see Action#setEnabled
 */
/*public*/ void SensorTableAction::setEnabled(bool newValue)
{
 bool oldValue = this->enabled;

 if (oldValue != newValue)
 {
  this->enabled = newValue;
  //firePropertyChange("enabled",
//                           (oldValue),(newValue));
  emit propertyChange(new PropertyChangeEvent(this,"enabled", (oldValue),(newValue) ));
 }
}
#endif
QString SensorTableAction::getName()
{
 return "jmri.jmrit.beantable.SensorTableAction";
}

STAValidator::STAValidator(JTextField *fld, SensorTableAction *act)
{
 this->fld = fld;
 this->act = act;
 connect(act->prefixBox, SIGNAL(currentTextChanged(QString)), this, SLOT(prefixBoxChanged(QString)));
 prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
 mark = ColorUtil::stringToColor("orange");
}

QValidator::State STAValidator::validate(QString& s, int& pos) const
{
 QString value = s.trimmed();
 if ((value.length() < 1) && (allow0Length == false)) {
     return QValidator::Invalid;
 } else if ((allow0Length == true) && (value.length() == 0)) {
     return QValidator::Acceptable;
 } else {
  bool bok;
  int num = s.toInt(&bok);
  if(!bok )
   return QValidator::Invalid;
  else if(num == 0)
   return QValidator::Intermediate;
  else if(!(num > 0 && num <= 2047 ))
   return QValidator::Invalid;
 }
// if(prefix == "")
// {
//  QString txt = act->prefixBox->currentText();
//  this->prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
// }
 bool validFormat = false;
 // try {
 validFormat = static_cast<LightManager*>(InstanceManager::getDefault("LightManager"))->validSystemNameFormat(prefix + "L" + value) == Manager::NameValidity::VALID;
 // } catch (jmri.JmriException e) {
 // use it for the status bar?
 // }
 if (validFormat) {
  act->addButton->setEnabled(true); // directly update Create button
  fld->setBackground(QColor(Qt::white));
  return QValidator::Acceptable;
 } else {
  act->addButton->setEnabled(false); // directly update Create button
  fld->setBackground(QColor(mark));
  return QValidator::Invalid;
 }
}

void STAValidator::setPrefix(QString prefix) { this->prefix = prefix;}

void STAValidator::prefixBoxChanged(QString txt)
{
 prefix = ConnectionNameFromSystemName::getPrefixFromName(txt);
}
