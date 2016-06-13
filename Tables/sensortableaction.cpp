#include "sensortableaction.h"
#include "jtextfield.h"
#include <QComboBox>
#include <QCheckBox>
#include "addnewhardwaredevicepanel.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include <QVBoxLayout>
#include "connectionnamefromsystemname.h"
#include "defaultusermessagepreferences.h"
#include "userpreferencesmanager.h"
#include <QMessageBox>
#include "jframe.h"
#include "flowlayout.h"
#include "../LayoutEditor/beantabledatamodel.h"
#include <QMenu>
#include <QMenuBar>
#include "../LayoutEditor/sensortabledatamodel.h"
#include "../LayoutEditor/beantableframe.h"
#include "jtable.h"
#include <QLabel>

//SensorTableAction::SensorTableAction(QObject *parent) :
//    QObject(parent)
//{
//}
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
 addFrame = NULL;
 if(parent == NULL)
  return;

 sysName = new JTextField(40);
 userName = new JTextField(40);
 prefixBox = new QComboBox();
 numberToAdd = new JTextField(5);
 numberToAdd->setValidator(new QIntValidator(1,100));
 range = new QCheckBox(tr("Add a range:"));
 sysNameLabel = new QLabel("Hardware Address:");
 userNameLabel = new QLabel(tr("User Name:"));
 systemSelectionCombo = QString( metaObject()->className())+".SystemSelected";
 userNameError = QString( metaObject()->className())+".DuplicateUserName";
 showDebounceBox = new QCheckBox(tr("Show Sensor Debounce Information"));
 senManager = NULL;
 enabled = true;
 m = NULL;

 // disable ourself if there is no primary sensor manager available
 if (senManager==NULL)
 {
  setEnabled(false);
 }
}
// /*public*/ SensorTableAction() { this("Sensor Table");}

/*public*/ void SensorTableAction::setManager(Manager* man)
{
 senManager = (ProxySensorManager*)man;
 if (m!=NULL)
  ((SensorTableDataModel*)m)->setManager((Manager*)senManager);
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Sensors
 */
/*protected*/ void SensorTableAction::createModel(JTable* table)
{
 m = new SensorTableDataModel(senManager);
 ((SensorTableDataModel*)m)->table = table;
 table->setModel(m);
}

/*protected*/ void SensorTableAction::setTitle() {
    f->setTitle(tr("Sensor Table"));
}

/*protected*/ QString SensorTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SensorTable";
}


/*protected*/ void SensorTableAction::addPressed()
{
 p = (DefaultUserMessagePreferences*) InstanceManager::getDefault("UserPreferencesManager");

 if (addFrame==NULL)
 {
  addFrame = new JmriJFrame(tr("Add Sensor"));
  //addFrame.addHelpMenu("package.jmri.jmrit.beantable.SensorAddEdit", true);
  QVBoxLayout* addFrameLayout = (QVBoxLayout*)addFrame->getContentPane()->layout();
  if(addFrameLayout == NULL)
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
  STRangeActionListener* rangeListener = new STRangeActionListener(this);
  if (QString(InstanceManager::sensorManagerInstance()->metaObject()->className()).contains("ProxySensorManager"))
  {
   ProxySensorManager* proxy = (ProxySensorManager*) InstanceManager::sensorManagerInstance();
   QList<Manager*> managerList = proxy->getManagerList();
   for(int x = 0; x<managerList.size(); x++)
   {
    QString manuName = ConnectionNameFromSystemName::getConnectionName(((AbstractManager*)managerList.at(x))->getSystemPrefix());
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
    if(p->getComboBoxLastSelection(systemSelectionCombo)!=NULL)
     prefixBox->setCurrentIndex(prefixBox->findText(p->getComboBoxLastSelection(systemSelectionCombo)));
   }
   else
  {
   prefixBox->addItem(ConnectionNameFromSystemName::getConnectionName(((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSystemPrefix()));
  }
  sysName->setObjectName("sysName");
  userName->setObjectName("userName");
  prefixBox->setObjectName("prefixBox");
  addFrameLayout->addWidget(new AddNewHardwareDevicePanel(sysName, userName, prefixBox, numberToAdd, range, "OK", listener, rangeListener));
  canAddRange();
 }
 addFrame->pack();
 addFrame->setVisible(true);
}
STOkButtonActionListener::STOkButtonActionListener(SensorTableAction *act)
{
 this->act = act;
}
void STOkButtonActionListener::actionPerformed()
{
 act->okPressed();
}
STRangeActionListener::STRangeActionListener(SensorTableAction *act)
{
 this->act = act;
}
void STRangeActionListener::actionPerformed()
{
 act->canAddRange();
}

void SensorTableAction::okPressed()
{
 /*String user = userName.getText();
 if (user==("")) user=NULL;*/

 int numberOfSensors = 1;

 if(range->isChecked())
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

 QString sName = NULL;
 QString curAddress = sysName->text();

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
  //We have found another turnout with the same address, therefore we need to go onto the next address.
  sName = sensorPrefix + InstanceManager::sensorManagerInstance()->typeLetter() + curAddress;
  Sensor* s = NULL;
  try
  {
   s =((ProxySensorManager*) InstanceManager::sensorManagerInstance())->provideSensor(sName);
  } catch (IllegalArgumentException ex)
  {
   // user input no good
   handleCreateException(sName);
   return; // without creating
  }
  if (s != NULL)
  {
   QString user = userName->text();
   if ((x != 0) && user != "" && user!=(""))
   {
    user = userName->text() + ":" + QString::number(x);
   }
   if (user != "" && user!=("") && (((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(user) == NULL))
   {
    s->setUserName(user);
   }
   else if (((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(user) != NULL && !p->getPreferenceState(getClassName(), "duplicateUserName"))
   {
    ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
               showErrorMessage("Duplicate UserName", "The username " + user + " specified is already in use and therefore will not be set", getClassName(), "duplicateUserName", false, true);
   }
  }
  int addr = curAddress.toInt();
  addr ++;
  curAddress = QString::number(addr);
 }
 p->addComboBoxLastSelection(systemSelectionCombo,  prefixBox->currentText());
}

/*private*/ void SensorTableAction::canAddRange()
{
 range->setEnabled(false);
 range->setChecked(false);
 if(senManager == NULL)
     senManager = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 //if (QString(senManager->metaObject()->className()).contains("ProxySensorManager"))
 if(qobject_cast<ProxySensorManager*>(senManager)!=NULL)
 {
  ProxySensorManager* proxy = (ProxySensorManager*) senManager;
  QList<Manager*> managerList = proxy->getManagerList();
  QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName(prefixBox->currentText());
  for(int x = 0; x<managerList.size(); x++)
  {
   AbstractSensorManager* mgr = (AbstractSensorManager*) managerList.at(x);
   if (mgr->getSystemPrefix()==(systemPrefix) && mgr->allowMultipleAdditions(systemPrefix))
   {
    range->setEnabled(true);
    return;
   }
  }
 }
 else if (((ProxySensorManager*)senManager)->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText())))
 {
  range->setEnabled(true);
 }
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
//                                      new Object[]{"Cancel", "OK", active, inActive}, NULL );
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

void DefaultStateActionListener::actionPerformed(ActionEvent *e)
{
 act->setDefaultState(finalF);
}

void SensorTableAction::showDebounceChanged(bool bChecked)
{
    SensorTableDataModel* a = (SensorTableDataModel*)m;
    a->showDebounce(/*showDebounceBox->isChecked()*/bChecked);
}


/*public*/ void SensorTableAction::addToFrame(BeanTableFrame* f) {
    f->addToBottomBox(showDebounceBox, "SensorTableAction");
    showDebounceBox->setToolTip(tr("Show extra columns for configuring sensor debounce timers"));
//    showDebounceBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            showDebounceChanged();
//        }
//    });
    connect(showDebounceBox, SIGNAL(clicked()), this, SLOT(showDebounceChanged()) );
}
#if 0
/*public*/ void addToPanel(AbstractTableTabAction f) {
    String systemPrefix = ConnectionNameFromSystemName.getConnectionName(senManager.getSystemPrefix());

    if (senManager.getClass().getName().contains("ProxySensorManager"))
        systemPrefix = "All";
    f.addToBottomBox(showDebounceBox, systemPrefix);
    showDebounceBox.setToolTipText(tr("SensorDebounceToolTip"));
    showDebounceBox.addActionListener(new ActionListener() {
        /*public*/ void actionPerformed(ActionEvent e) {
            showDebounceChanged();
        }
    });
}
#endif

/*public*/ void SensorTableAction::setMessagePreferencesDetails(){
    ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->preferenceItemDetails(getClassName(), "duplicateUserName",  tr("Hide Duplicate User Name Warning Message"));
AbstractTableAction::setMessagePreferencesDetails();
}

/*protected*/ QString SensorTableAction::getClassName() { return "jmri.jmrit.beantable.SensorTableAction"; }

/*public*/ QString SensorTableAction::getClassDescription() { return tr("Sensor Table"); }

//    static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SensorTableAction.class.getName());
//}
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
QString SensorTableAction::getName()
{
 return "jmri.jmrit.beantable.SensorTableAction";
}
