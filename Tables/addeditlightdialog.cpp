#include "addeditlightdialog.h"
#include "ui_addeditlightdialog1.h"
#include "abstractlight.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "abstractlightmanager.h"
#include "lighttablewidget.h"
#include "flowlayout.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QSignalMapper>
#include "connectionnamefromsystemname.h"
#include "defaultusermessagepreferences.h"
#include <QMessageBox>

AddEditLightDialog::AddEditLightDialog(AbstractLight* light, QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::AddEditLightDialog1)
{
 ui->setupUi(this);
 addHelpMenu("package.jmri.jmrit.beantable.LightAddEdit", true);
 curLight = light;
 log = new Logger("AddEditLightDialog");
 sensorControl = tr("Sensor Control");
 fastClockControl = tr("Fast Clock Control");
 turnoutStatusControl = tr("Turnout Status Control");
 timedOnControl = tr("Timed On Control");
 twoSensorControl = tr("Two Sensor Control");
 noControl = tr("No Control");
 mgr = (ProxyLightManager*)InstanceManager::lightManagerInstance();
 noWarn = false;
 lightCreatedOrUpdated = false;

 if(light == NULL)
 {
  inEditMode = false;
  setWindowTitle(tr("Add Light"));
  ui->btnUpdate->setVisible(false);
  QList<Manager*> mgrList = mgr->getManagerList();
  for(int i=0; i < mgrList.count(); i++)
  {
   if(((AbstractManager*)mgrList.at(i))->getSystemPrefix() == "I")
    continue;
   if(((AbstractManager*)mgrList.at(i))->getSystemPrefix() == "L")
    ui->prefixBox->addItem("LocoNet");
  }
  controlList = new QList<LightControl*>();
 }
 else
 {
  setWindowTitle("Edit Light");
  setLight(light);
  inEditMode = true;
  }

 lightControlTableModel = new LightControlTableModel(this);
 ui->tableView->setModel(lightControlTableModel);
 ui->tableView->resizeColumnsToContents();
 ui->tableView->setItemDelegateForColumn(LightControlTableModel::EDIT_COLUMN, new PushButtonDelegate(this));
 ui->tableView->setItemDelegateForColumn(LightControlTableModel::REMOVE_COLUMN, new PushButtonDelegate( this));

 lightControlChanged = false;
 inEditControlMode = false;
 addControlFrame = NULL;
 typeBoxLabel = new QLabel( tr("Control Type") );
 defaultControlIndex = 0;
 inEditControlMode = false;
 lc = NULL;
 field1a = new JTextField(10);  // Sensor
 field1a2 = new JTextField(10);  // Sensor 2
 field1b = new JTextField(8);  // Fast Clock
 field1c = new JTextField(10);  // Turnout
 field1d = new JTextField(10);  // Timed ON
 f1Label = new QLabel( tr("Sensor") );
 field2a = new JTextField(8);  // Fast Clock
 field2b = new JTextField(8); // Timed ON
 f2Label = new QLabel( tr("Sense for ON") );

}

AddEditLightDialog::~AddEditLightDialog()
{
    delete ui;
}
int AddEditLightDialog::addr()
{
 QString val = ui->fieldHardwareAddress->text();
 if(val.startsWith("0x",Qt::CaseInsensitive))
  return val.mid(2).toInt(0,16);
 else
  return val.toInt(0,10);
}
QString AddEditLightDialog::system() {return ui->prefixBox->currentText();}
QString AddEditLightDialog::userName() { return ui->userName->text();}
int AddEditLightDialog::numToAdd() { return ui->fieldNumToAdd->value();}
bool AddEditLightDialog::isAddRange() { return ui->addRangeBox->isChecked();}
//void AddEditLightDialog::on_btnCancel_clicked()
//{
// reject();
// close();
//}
//void AddEditLightDialog::on_btnCreate_clicked()
//{
// if(!inEditMode)
// {
//  QString sSystem = system();
//  QString sysName="";
//  int iAddr = addr();
//  QString userName = ui->edUserName->text();
//  int iMgr =mgr->nMgrs()-1;
//  AbstractLightManager* smgr = (AbstractLightManager*)mgr->getMgr(iMgr);
//  QString sPrefix = smgr->getSystemPrefix()+ smgr->typeLetter();
//  if(sSystem != tr("Internal")) iMgr= 0;
//  if(isAddRange())
//  {
//   int count = numToAdd();
//   int address = addr();
//   for(int iAddr = address; iAddr < address + count -1; iAddr++)
//   {
//    sysName = sPrefix+QString("%1").arg(iAddr);
//    light = (AbstractLight*)mgr->newLight(sysName, userName+QString("+%1").arg(iAddr));
//   }
//  }
//  else
//  {
//   sysName = sPrefix+QString("%1").arg(iAddr);
//   light = (AbstractLight*)mgr->newLight(sysName, userName);
//  }
// }
// light->setMinIntensity(ui->sbMin->value());
// light->setMaxIntensity(ui->sbMax->value());
// light->setTransitionTime(ui->sbTransition->value());
// accept();
// close();
//}
/**
 * Responds to the Create button
 */
void AddEditLightDialog::on_btnCreate_clicked()
{
 //ConnectionNameFromSystemName.getPrefixFromName((String) prefixBox.getSelectedItem())
 QString lightPrefix = ConnectionNameFromSystemName::getPrefixFromName(ui->prefixBox->currentText())+"L";
 QString turnoutPrefix = ConnectionNameFromSystemName::getPrefixFromName(ui->prefixBox->currentText())+"T";
 QString curAddress = ui->fieldHardwareAddress->text();
 if (curAddress.length()<1)
 {
  log->warn("Hardware Address was not entered");
  ui->status1->setText( tr("Error: No Hardware Address was entered.") );
  ui->status2->setVisible(false);
//        addFrame.pack();
  pack();
//        addFrame.setVisible(true);
  setVisible(true);
  return;
 }
 QString suName = lightPrefix+curAddress;
 QString uName = ui->userName->text();
 if (uName==("")) uName="";   // a blank field means no user name

 // Does System Name have a valid format
 if (!((ProxyLightManager*)InstanceManager::lightManagerInstance())->validSystemNameFormat(suName))
 {
  // Invalid System Name format
  log->warn("Invalid Light system name format entered: "+suName);
  ui->status1->setText( tr("Error: System Name has an invalid format.") );
  ui->status2->setText( tr("Please revise System Name and try again.") );
  ui->status2->setVisible(true);
//        addFrame.pack();
  pack();
//        addFrame.setVisible(true);
  setVisible(true);

  return;
 }
 // Format is valid, normalize it
 QString sName = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->normalizeSystemName(suName);
 // check if a Light with this name already exists
 AbstractLight* g = (AbstractLight*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(sName);
 if (g!=NULL)
 {
  // Light already exists
  ui->status1->setText( tr("Error: Light with this System Name already exists.") );
  ui->status2->setText( tr("Press Edit to see User Name and Control information.") );
  ui->status2->setVisible(true);
//  addFrame.pack();
  pack();
//    addFrame.setVisible(true);
  setVisible(true);

  return;
 }
 // check if Light exists under an alternate name if an alternate name exists
 QString altName = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->convertSystemNameToAlternate(suName);
 if (altName != "")
 {
  g = (AbstractLight*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(altName);
  if (g!=NULL)
  {
   // Light already exists
   ui->status1->setText( tr("Error: Light")+" '"+altName+"' "+
                        tr("exists and is the same address.") );
   ui->status2->setVisible(false);
//    addFrame.pack();
   pack();
//    addFrame.setVisible(true);
   setVisible(true);
   return;
  }
 }
 // check if a Light with the same user name exists
 if (uName!="")
 {
  g = (AbstractLight*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->getByUserName(uName);
  if (g!=NULL)
  {
    // Light with this user name already exists
    ui->status1->setText( tr("Error: Light with this User Name already exists.") );
    ui->status2->setText( tr("Please revise User Name and try again.") );
    ui->status2->setVisible(true);
//    addFrame.pack();
    pack();
//    addFrame.setVisible(true);
    setVisible(true);

    return;
  }
 }
 // Does System Name correspond to configured hardware
 if (!((ProxyLightManager*)InstanceManager::lightManagerInstance())->validSystemNameConfig(sName))
 {
  // System Name not in configured hardware
  ui->status1->setText( tr("Error: System Name doesn't refer to configured hardware.") );
  ui->status2->setText( tr("Please revise System Name and try again.") );
  ui->status2->setVisible(true);
//    addFrame.pack();
  pack();
//    addFrame.setVisible(true);
  setVisible(true);

  return;
 }
 // check if requested Light uses the same address as a Turnout
 QString testSN = turnoutPrefix+curAddress;
 Turnout* testT = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                                getBySystemName(testSN);
 if (testT != NULL)
 {
  // Address is already used as a Turnout
  log->warn("Requested Light "+sName+" uses same address as Turnout "+testT->getDisplayName());
  if (!noWarn)
  {
//    int selectedValue = JOptionPane.showOptionDialog(addFrame,
//        tr("LightWarn5")+" "+sName+" "+tr("LightWarn6")+" "+
//        testSN+".\n   "+tr("LightWarn7"),tr("WarningTitle"),
//        JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,null,
//        new Object[]{tr("ButtonYes"),tr("ButtonNo"),
//        tr("ButtonYesPlus")},tr("ButtonNo"));
   QMessageBox* msgBox = new QMessageBox( tr("Warning"), tr("Warning - Requested Light")+" "+sName+" "+tr("uses same address as Turnout")+" "+
                                   testSN+".\n   "+tr("Do you still want to add this Light?"),QMessageBox::Warning, QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel,this);
   //msgBox->setIcon(QMessageBox::Warning);
   QPushButton* buttonYesPlus = new QPushButton(tr("Yes - Stop Warnings"));
   msgBox->addButton(buttonYesPlus,QMessageBox::ActionRole);
   int selectedValue = msgBox->exec();
   if (selectedValue == QMessageBox::No) return;   // return without creating if "No" response
   if (msgBox->clickedButton() == buttonYesPlus)
   {
    // Suppress future warnings, and continue
    noWarn = true;
   }
  }
   // Light with this system name already exists as a turnout
   ui->status2->setText( tr("Warning: New Light refers to address already used by")+" "+testSN+"." );
   ui->status2->setVisible(true);
  }
  // Check multiple Light creation request, if supported
  int numberOfLights = 1;
  int startingAddress = 0;
  if ( (((ProxyLightManager*)InstanceManager::lightManagerInstance())->allowMultipleAdditions(sName)) &&
                    ui->addRangeBox->isChecked() && (ui->fieldNumToAdd->value()>0) )
  {
   // get number requested
//        try {
   numberOfLights = (ui->fieldNumToAdd->value());
//        } catch (NumberFormatException ex) {
//            status1->setText(tr("LightError4"));
//            status2.setVisible(false);
//            addFrame.pack();
//            addFrame.setVisible(true);
//            log.error("Unable to convert " + fieldNumToAdd.getText() + " to a number - Number to add");
//            return;
//        }
        // convert numerical hardware address
//        try {

   startingAddress = ui->fieldHardwareAddress->text().toInt();
//        } catch (NumberFormatException ex) {
//            status1->setText(tr("LightError18"));
//            status2.setVisible(false);
//            addFrame.pack();
//            addFrame.setVisible(true);
//            log.error("Unable to convert " + fieldHardwareAddress.getText() + " to a number.");
//            return;
//        }
   // check that requested address range is available
   int add = startingAddress;
   QString testAdd = "";
   for (int i = 0; i<numberOfLights; i++)
   {
    testAdd = lightPrefix+add;
    if (((ProxyLightManager*)InstanceManager::lightManagerInstance())->getBySystemName(testAdd)!=NULL)
    {
     ui->status1->setText(tr("Error: Requested range of hardware addresses is not free."));
     ui->status2->setVisible(true);
//        addFrame.pack();
     pack();
//        addFrame.setVisible(true);
     setVisible(true);

     log->error("Range not available - "+testAdd+ " already exists.");
     return;
    }
    testAdd = turnoutPrefix+add;
    if (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getBySystemName(testAdd)!=NULL)
    {
        ui->status1->setText(tr("Error: Requested range of hardware addresses is not free."));
        ui->status2->setVisible(true);
        //addFrame.pack();
        //addFrame.setVisible(true);
        setVisible(true);
        log->error("Range not available - "+testAdd+ " already exists.");
        return;
    }
    add++;
   }
  }

  // Create a single new Light, or the first Light of a range
//    try {
  g = (AbstractLight*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->newLight(sName,uName);
//    } catch (IllegalArgumentException ex) {
  if(g == NULL)
  {
   // user input no good
   handleCreateException(sName);
   return; // without creating
  }
  // set control information if any
  setLightControlInformation(g);
  clearLightControls();
  g->activateLight();
  lightCreatedOrUpdated = true;
  QString p;
  p = ui->fieldMinIntensity->text();
  if (p==("")) p = "1.0";
  g->setMinIntensity((p).toDouble()/ 100);

  p = ui->fieldMaxIntensity->text();
  if (p==("")) p = "0.0";
  if(p.toDouble() <= g->getMinIntensity())
  {
   ui->status1->setText(tr("Max intensity must be greater than minimum"));
   handleCreateException(sName);
   return; // without creating
  }
  g->setMaxIntensity(p.toDouble() / 100);

  p = ui->fieldTransitionTime->text();
  if (p==("")) p = "0";
//    try {
        g->setTransitionTime(p.toDouble());
//    } catch (IllegalArgumentException e1) {
//        // set rate to 0.
//        g.setTransitionTime(0.0);
//    }
  // provide feedback to user
  QString feedback = tr("New Light added:")+" "+sName+", "+uName;
  // create additional lights if requested
  if (numberOfLights>1)
  {
   QString sxName = "";
   QString uxName = "";
   if (uName=="") uxName = "";
   for (int i = 1; i<numberOfLights; i++)
   {
    sxName = lightPrefix+(startingAddress+i);
    if (uName!="") uxName = uName+"+"+i;
//            try {
   g = (AbstractLight*)((ProxyLightManager*)InstanceManager::lightManagerInstance())->newLight(sxName,uxName);
//            } catch (IllegalArgumentException ex) {
   if(g == NULL)
   {
    // user input no good
    handleCreateException(sName);
    return; // without creating any more Lights
   }
  }
  feedback = feedback +" - "+sxName+", "+uxName;
 }
 ui->status1->setText(feedback);
 ui->status2->setText( "" );
 ui->status2->setVisible(false);
//    addFrame.pack();
//    addFrame.setVisible(true);
 setVisible(true);
}
void AddEditLightDialog::setLight(AbstractLight* l)
{
 curLight = l;
 QString sysName = l->getSystemName();
 QString prefix = sysName.mid(0,1);
 if(prefix == "I")
  ui->prefixBox->setCurrentIndex(0);
 if(prefix == "L")
  ui->prefixBox->setCurrentIndex(1);
 ui->prefixBox->setDisabled(true);
 QString hardwareAddr = sysName.mid(2);
 ui->fieldHardwareAddress->setText(hardwareAddr);
 ui->fieldHardwareAddress->setReadOnly(true);
 ui->fieldNumToAdd->setVisible(false);
 ui->lblNbrToAdd->setVisible(false);
 ui->addRangeBox->setVisible(false);

 ui->userName->setText(l->getUserName());
 //ui->btnCreate->setText(tr("Update"));
 ui->btnCreate->setVisible(false);

 ui->fieldMinIntensity->setValue(l->getMinIntensity());
 ui->fieldMaxIntensity->setValue(l->getMaxIntensity());
 ui->fieldTransitionTime->setValue(l->getTransitionTime());
 controlList = l->getLightControlList();
 if(controlList->count() == 0) ui->prefixBox->setCurrentIndex(0);

}
/**
 * Table model for Light Controls in the Add/Edit Light window
 */
//public class LightControlTableModel extends javax.swing.table.AbstractTableModel implements
//java.beans.PropertyChangeListener {

//    public static final int TYPE_COLUMN = 0;
//    public static final int DESCRIPTION_COLUMN = 1;
//    public static final int EDIT_COLUMN = 2;
//    public static final int REMOVE_COLUMN = 3;

/*public*/ LightControlTableModel::LightControlTableModel(AddEditLightDialog* dlg) {
    //super();
    this->dlg = dlg;
    this->controlList = dlg->controlList;

}

/*public*/ void LightControlTableModel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("length")) {
        // a new LightControl item is available in the manager
        fireTableDataChanged();
    }
}

//public Class<?> getColumnClass(int c) {
//    if ( c==TYPE_COLUMN ) return String.class;
//    if ( c==DESCRIPTION_COLUMN ) return String.class;
//    if ( c==EDIT_COLUMN )return JButton.class;
//    if ( c==REMOVE_COLUMN )return JButton.class;
//    return String.class;
//}

/*public*/ int LightControlTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return REMOVE_COLUMN+1;
}

/*public*/ int LightControlTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return (controlList->size());
}

/*public*/ Qt::ItemFlags LightControlTableModel::flags(const QModelIndex &index) const
{
 int c = index.column();
    if ( c==TYPE_COLUMN ) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if ( c==DESCRIPTION_COLUMN ) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if ( c==EDIT_COLUMN )return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if ( c==REMOVE_COLUMN )return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return Qt::NoItemFlags;
}

/*public*/ QVariant LightControlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col =section;
  if (col == TYPE_COLUMN)
   return tr("Type");
  else if (col == DESCRIPTION_COLUMN)
   return tr("Description");
 }
 return QVariant();
}

/*public*/ int LightControlTableModel::getPreferredWidth(int col)
{
 switch (col)
 {
  case TYPE_COLUMN:
  return  JTextField(20).getPreferredSize().width();
  case DESCRIPTION_COLUMN:
  return  JTextField(70).getPreferredSize().width();
  case EDIT_COLUMN:
  return  JTextField(8).getPreferredSize().width();
  case REMOVE_COLUMN:
  return  JTextField(8).getPreferredSize().width();
 }
 return  JTextField(8).getPreferredSize().width();
}

/*public*/ QVariant LightControlTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int rx = index.row();
  if (rx > controlList->size())
  {
   return QVariant();
  }
  LightControl* lc = controlList->at(rx);
  switch (index.column())
  {
   case TYPE_COLUMN:
        return (dlg->getControlTypeText(lc->getControlType()));
   case DESCRIPTION_COLUMN:
        return (dlg->getDescriptionText(lc, lc->getControlType()));
   case EDIT_COLUMN:
        return tr("Edit");
   case REMOVE_COLUMN:
        return tr("Delete");
   default:
      break;
  }
 }
 return QVariant();
}

/*public*/ bool LightControlTableModel::setData(const QModelIndex &index, const QVariant &/*value*/, int role)
{
 if(role == Qt::EditRole)
 {
  int col = index.column();
  if (col==EDIT_COLUMN)
  {
        // set up to edit. Use separate Thread so window is created on top
//        class WindowMaker implements Runnable {
//            WindowMaker(int _row){
//                row = _row;
//            }
//            int row;
//            public void run() {
   dlg->editControlAction(index.row());
//                }
//            };
//        WindowMaker t = new WindowMaker(row);
//        javax.swing.SwingUtilities.invokeLater(t);
    }
    if (col==REMOVE_COLUMN) {
        dlg->deleteControlAction(index.row());
    }
 }
 return false;
}
/**
 * Returns text showing the type of Light Control
 */
/*public*/ QString AddEditLightDialog::getControlTypeText(int type)
{
 switch (type)
 {
  case Light::SENSOR_CONTROL:
    return sensorControl;
  case Light::FAST_CLOCK_CONTROL:
    return fastClockControl;
  case Light::TURNOUT_STATUS_CONTROL:
    return turnoutStatusControl;
  case Light::TIMED_ON_CONTROL:
    return timedOnControl;
  case Light::TWO_SENSOR_CONTROL:
    return twoSensorControl;
  case Light::NO_CONTROL:
    return noControl;
  default:
    return noControl;
 }
}
//};
/**
 * Returns text showing the type of Light Control
 */
/*public*/ QString AddEditLightDialog::getDescriptionText(LightControl* lc, int type)
{
 switch (type)
 {
  case Light::SENSOR_CONTROL:
    return tr("ON when %1 is %2.").arg(lc->getControlSensorName()).arg(getControlSensorSenseText(lc));
  case Light::FAST_CLOCK_CONTROL:
   return tr("ON at %1, OFF at %2.").arg(formatTime(lc->getFastClockOnHour(),lc->getFastClockOnMin())).arg(formatTime(lc->getFastClockOffHour(),lc->getFastClockOffMin()));
  case Light::TURNOUT_STATUS_CONTROL:
    return tr("ON when %1 is %2.").arg(lc->getControlTurnoutName()).arg(getControlTurnoutStateText(lc));
  case Light::TIMED_ON_CONTROL:
   return tr("ON for %1 msec. when %2 goes %3.").arg(lc->getTimedOnDuration()).arg(lc->getControlTimedOnSensorName()).arg( getControlSensorSenseText(lc));
  case Light::TWO_SENSOR_CONTROL:
   return tr("ON when either %1 or %2 is %3.").arg(lc->getControlSensorName()).arg(lc->getControlSensor2Name()).arg(getControlSensorSenseText(lc));
  default:
    return "";
 }
}
/*private*/ QString AddEditLightDialog::getControlSensorSenseText (LightControl* lc)
{
    int s = lc->getControlSensorSense();
    if (s == Sensor::ACTIVE) return tr("Active");
    return tr("Inactive");
}
/*private*/ QString AddEditLightDialog::getControlTurnoutStateText (LightControl* lc) {
    int s = lc->getControlTurnoutState();
    if (s == Turnout::CLOSED) return ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
    return ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
}


/**
 * Retrieve control information from window and update Light Control
 *    Returns 'true' if no errors or warnings.
 */
/*private*/ bool AddEditLightDialog::setControlInformation(LightControl* g)
{
 // Get control information
 if (sensorControl==(typeBox->currentText()))
 {
  // Set type of control
  g->setControlType(Light::SENSOR_CONTROL);
  // Get sensor control information
  QString sensorName = field1a->text().trimmed();
  Sensor* s = NULL;
  if (sensorName.length() < 1)
  {
   // no sensor name entered
   g->setControlType(Light::NO_CONTROL);
  }
  else
  {
   // name was entered, check for user name first
   s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                               getByUserName(sensorName);
   if (s==NULL)
   {
    // not user name, try system name
    s =  ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                        getBySystemName(sensorName);
    if (s!=NULL)
    {
     // update sensor system name in case it changed
     sensorName = s->getSystemName();
     field1a->setText(sensorName);
    }
   }
  }
  int sState = Sensor::ACTIVE;
  if ( stateBox->currentText()==(tr("Inactive")) )
  {
   sState = Sensor::INACTIVE;
  }
  g->setControlSensorName(sensorName);
  g->setControlSensorSense(sState);
  if (s==NULL)
  {
   ui->status1->setText( tr("Error: Sensor could not be provided. Light Control not created.") );
   return (false);
  }
 }
 else if (fastClockControl==(typeBox->currentText()))
 {
  // Set type of control
  g->setControlType(Light::FAST_CLOCK_CONTROL);
  // read and parse the hours and minutes in the two fields
  bool error = false;
  int onHour = 0;
  int onMin = 0;
  int offHour = 0;
  int offMin = 0;
  bool bOk;
  QString s = field1b->text();
  if ( (s.length() != 5) || (s.at(2) != ':') )
  {
   ui->status1->setText( tr("Format error in time entry, please reenter as hh:mm.") );
   error = true;
  }
  if (!error)
  {
//   try
//   {
   onHour = s.mid(0,2).toInt(&bOk);
   if ( (onHour < 0) || (onHour > 24) )
   {
    ui->status1->setText( tr("Number out of range in time entry, please reenter as hh:mm.") );
    error = true;
   }
//   }
//   catch (Exception e)
   if(!bOk)
   {
    ui->status1->setText( tr("Bad character in time field, please reenter as hh:mm.") );
    error = true;
   }
  }
  if (!error)
  {
//    try {
   onMin = s.mid(3,5).toInt(&bOk);
   if ( (onMin < 0) || (onMin > 59) )
   {
    ui->status1->setText( tr("Number out of range in time entry, please reenter as hh:mm.") );
    error = true;
   }
//  }
//    catch (Exception e)
  if(!bOk)
  {
   ui->status1->setText( tr("Bad character in time field, please reenter as hh:mm.") );
   error = true;
  }
 }
 s = field2a->text();
 if ( (s.length() != 5) || (s.at(2) != ':') )
 {
  ui->status1->setText( tr("Format error in time entry, please reenter as hh:mm.") );
  error = true;
 }
 if (!error)
 {
//    try {
  offHour = s.mid(0,2).toInt(&bOk);
  if ( (offHour < 0) || (offHour > 24) )
  {
   ui->status1->setText( tr("Number out of range in time entry, please reenter as hh:mm.") );
   error = true;
  }
// }
//    catch (Exception e)
 if(!bOk)
 {
  ui->status1->setText( tr("Bad character in time field, please reenter as hh:mm.") );
  error = true;
 }
}
if (!error)
{
//    try {
 offMin = s.mid(3,5).toInt(&bOk);
 if ( (offMin < 0) || (offMin > 59) )
 {
  ui->status1->setText( tr("Number out of range in time entry, please reenter as hh:mm.") );
  error = true;
 }
//    }
//    catch (Exception e)
 if(!bOk)
 {
  ui->status1->setText( tr("Bad character in time field, please reenter as hh:mm.") );
  error = true;
 }
}

if (error) {
    return (false);
}
g->setFastClockControlSchedule(onHour,onMin,offHour,offMin);
}
 else if (turnoutStatusControl==(typeBox->currentText()))
 {
  bool error = false;

  Turnout* t = NULL;
  // Set type of control
  g->setControlType(Light::TURNOUT_STATUS_CONTROL);
  // Get turnout control information
  QString turnoutName = field1c->text().trimmed();
  if (turnoutName.length() < 1)
  {
   // valid turnout system name was not entered
   g->setControlType(Light::NO_CONTROL);
  }
  else
  {
   // Ensure that this Turnout is not already a Light
   if (turnoutName.at(1)=='T')
   {
    // must be a standard format name (not just a number)
    QString testSN = turnoutName.mid(0,1)+"L"+
                    turnoutName.mid(2,turnoutName.length());
    Light* testLight = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->
                                    getBySystemName(testSN);
    if (testLight != NULL)
    {
     // Requested turnout bit is already assigned to a Light
     ui->status2->setText( tr("Warning: Requested Turnout uses the same address as Light:")+" "+testSN+"." );
     ui->status2->setVisible(true);
     error = true;
    }
   }
   if (!error)
   {
    // Requested turnout bit is not assigned to a Light
    t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                getByUserName(turnoutName);
    if (t==NULL)
    {
     // not user name, try system name
     t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                getBySystemName(turnoutName.toUpper());
     if (t!=NULL)
     {
      // update turnout system name in case it changed
      turnoutName = t->getSystemName();
      field1c->setText(turnoutName);
     }
    }
   }
  }
  // Initialize the requested Turnout State
  int tState = Turnout::CLOSED;
  if ( stateBox->currentText()==(((ProxyTurnoutManager*)InstanceManager::
            turnoutManagerInstance())->getThrownText()) )
  {
   tState = Turnout::THROWN;
  }
  g->setControlTurnout(turnoutName);
  g->setControlTurnoutState(tState);
  if (t==NULL)
  {
   ui->status1->setText( tr("Error: Turnout could not be provided. Light Control not created.") );
   return (false);
  }
 }
 else if (timedOnControl==(typeBox->currentText()))
 {
  // Set type of control
  g->setControlType(Light::TIMED_ON_CONTROL);
  // Get trigger sensor control information
  Sensor* s = NULL;
  QString triggerSensorName = field1d->text();
  if (triggerSensorName.length() < 1)
  {
   // Trigger sensor not entered, or invalidly entered
   g->setControlType(Light::NO_CONTROL);
  }
  else
  {
   // name entered, try user name first
   s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                getByUserName(triggerSensorName);
   if (s==NULL)
   {
    // not user name, try system name
    s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                    getBySystemName(triggerSensorName);
    if (s!=NULL)
    {
     // update sensor system name in case it changed
     triggerSensorName = s->getSystemName();
     field1d->setText(triggerSensorName);
    }
   }
  }
  g->setControlTimedOnSensorName(triggerSensorName);
  int dur = 0;
  bool bOk;
//try
//{
  dur = field2b->text().toInt(&bOk);
//}
//catch (Exception e)
  if(!bOk)
  {
   if (s!=NULL)
   {
    ui->status1->setText(tr("Error: Duration entry had invalid format. Light Control not created.") );
    return (false);
   }
  }
  g->setTimedOnDuration(dur);
  if (s==NULL)
  {
   ui->status1->setText( tr("Error: Trigger Sensor has invalid name. Light Control not created.") );
   return (false);
  }
 }
 else if (twoSensorControl==(typeBox->currentText()))
 {
  // Set type of control
  g->setControlType(Light::TWO_SENSOR_CONTROL);
  // Get sensor control information
  QString sensorName = field1a->text().trimmed();
  Sensor* s = NULL;
  QString sensor2Name = field1a2->text().trimmed();
  Sensor* s2 = NULL;
  if ( (sensorName.length() < 1) || (sensor2Name.length() <1) )
  {
   // no sensor name entered
   g->setControlType(Light::NO_CONTROL);
  }
  else
  {
   // name was entered, check for user name first
   s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                       getByUserName(sensorName);
   if (s==NULL)
   {
    // not user name, try system name
    s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                getBySystemName(sensorName);
    if (s!=NULL)
    {
     // update sensor system name in case it changed
     sensorName = s->getSystemName();
     field1a->setText(sensorName);
    }
   }
   s2 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                       getByUserName(sensor2Name);
   if (s2==NULL)
   {
    // not user name, try system name
    s2 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
            getBySystemName(sensor2Name);
    if (s2!=NULL)
    {
     // update sensor system name in case it changed
     sensor2Name = s2->getSystemName();
     field1a2->setText(sensor2Name);
    }
   }
  }
  int sState = Sensor::ACTIVE;
  if ( stateBox->currentText()==(tr("Inactive")) )
  {
   sState = Sensor::INACTIVE;
  }
  g->setControlSensorName(sensorName);
  g->setControlSensor2Name(sensor2Name);
  g->setControlSensorSense(sState);
  if (s==NULL)
  {
   ui->status1->setText( tr("Error: Sensor could not be provided. Light Control not created.") );
   return (false);
  }
 }
 else if (noControl==(typeBox->currentText()))
 {
  // Set type of control
  g->setControlType(Light::NO_CONTROL);
 }
 else
 {
  log->error("Unexpected control type: "+typeBox->currentText());
 }
 return (true);
}
/**
 *  Formats time to hh:mm given integer hour and minute
 */
QString AddEditLightDialog::formatTime (int hour,int minute)
{
 QString s = "";
 QString t = QString::number(hour);
 if (t.length() == 2)
 {
  s = t + ":";
 }
 else if (t.length() == 1)
 {
  s = "0" + t + ":";
 }
 t = QString::number(minute);
 if (t.length() == 2)
 {
  s = s + t;
 }
 else if (t.length() == 1)
 {
  s = s + "0" + t;
 }
 if (s.length() != 5)
 {
  // input error
  s = "00:00";
 }
 return s;
}
/**
 * Responds to Delete button on row in the Light Control Table
 */
/*protected*/ void AddEditLightDialog::deleteControlAction(int row) {
    controlList->removeAt(row);
    lightControlTableModel->fireTableDataChanged();
    lightControlChanged = true;
}

bool AddEditLightDialog::isUpdate() { return inEditMode;}

void AddEditLightDialog::on_addControl_clicked()
{
    if (inEditControlMode) {
        // cancel Edit and reactivate the edited light
        cancelControlPressed(NULL);
    }
    addEditControlWindow();
}
/**
 * Creates the Add/Edit control window
 */
/*private*/ void AddEditLightDialog::addEditControlWindow()
{
 if (addControlFrame==NULL)
 {
  addControlFrame = new JmriJFrame( tr("Add/Edit Light Control"), false, true );
  addControlFrame->addHelpMenu("package.jmri.jmrit.beantable.LightAddEdit", true);
  //addControlFrame.setLocation(120,40);
  QWidget* contentPane = addControlFrame->getContentPane();
  QVBoxLayout* contentPaneLayout;
  if(contentPane == NULL)
  {
   contentPaneLayout = new QVBoxLayout;
    contentPane->setLayout(contentPaneLayout);
  }
  else
   contentPaneLayout = (QVBoxLayout*)contentPane->layout();
  QVBoxLayout* panel3Layout;
  QFrame* panel3 = new QFrame();
  panel3->setLayout(panel3Layout = new QVBoxLayout(panel3/*, BoxLayout.Y_AXIS*/));

//    JPanel panel31 = new JPanel();
//    panel31.setLayout(new FlowLayout());
  FlowLayout* panel31Layout = new FlowLayout();
  panel31Layout->addWidget(typeBoxLabel);
  panel31Layout->addWidget(typeBox = new QComboBox());
  panel31Layout->setAlignment(panel3Layout,Qt::AlignCenter);
  QStringList cbList = QStringList() << noControl <<
        sensorControl<<fastClockControl<<turnoutStatusControl<<timedOnControl<<twoSensorControl;
  typeBox->addItems(cbList);
  connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(controlTypeChanged()));
  noControlIndex = 0;
  sensorControlIndex = 1;
  fastClockControlIndex = 2;
  turnoutStatusControlIndex = 3;
  timedOnControlIndex = 4;
  twoSensorControlIndex = 5;
//    typeBox.addActionListener(new ActionListener(){
//        public void actionPerformed(ActionEvent e) {
//            controlTypeChanged();
//        }
//    });
  connect(typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(controlTypeChanged()));
  typeBox->setToolTip( tr("Select how the new Light is to be controlled") );
//    JPanel panel32 = new JPanel();
//    panel32.setLayout(new FlowLayout());
  FlowLayout* panel32Layout = new FlowLayout;
  panel32Layout->setAlignment(panel3Layout,Qt::AlignCenter);
    panel32Layout->addWidget(f1Label);
    panel32Layout->addWidget(field1a);
    panel32Layout->addWidget(field1a2);
    panel32Layout->addWidget(field1b);
    panel32Layout->addWidget(field1c);
    panel32Layout->addWidget(field1d);
    field1a->setText("");
    field1a2->setText("");
    field1b->setText("00:00");
    field1c->setText("");
    field1d->setText("");
    field1b->setVisible(false);
    field1c->setVisible(false);
    field1d->setVisible(false);
    field1a->setToolTip( tr("Enter name of Sensor controlling this Light") );
    field1a2->setToolTip( tr("Enter name of both Sensors controlling this Light") );
//    JPanel panel33 = new JPanel();
//    panel33.setLayout(new FlowLayout());
    FlowLayout* panel33Layout = new FlowLayout;
    panel33Layout->addWidget(f2Label);
    panel33Layout->addWidget(stateBox = new QComboBox());
    panel33Layout->setAlignment(panel3Layout,Qt::AlignCenter);
    stateBox->addItem(tr("Active"));
    stateBox->addItem(tr("Inactive"));
    stateBox->setToolTip( tr("Select Sensor state corresponding to Light ON") );
    panel33Layout->addWidget(field2a);
    panel33Layout->addWidget(field2b);
    field2a->setText("00:00");
    field2a->setVisible(false);
    field2b->setText("0");
    field2b->setVisible(false);
    panel3Layout->addLayout(panel31Layout);
    panel3Layout->addLayout(panel32Layout);
    panel3Layout->addLayout(panel33Layout);
    //Border panel3Border = BorderFactory.createEtchedBorder();
    //panel3.setBorder(panel3Border);
    panel3->setFrameStyle(QFrame::StyledPanel );
    panel3->setFrameShadow(QFrame::Raised);
    panel3->setLineWidth(2);
    contentPaneLayout->addWidget(panel3);
//    JPanel panel5 = new JPanel();
//    panel5.setLayout(new FlowLayout());
    FlowLayout* panel5Layout = new FlowLayout;
    panel5Layout->addWidget(createControl = new QPushButton(tr("Create")));
//    createControl.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            createControlPressed(e);
//        }
//    });
  connect(createControl, SIGNAL(clicked()), this, SLOT(createControlPressed()));
  createControl->setToolTip( tr("Press Create to create a new Light Control") );
  panel5Layout->addWidget(updateControl = new QPushButton(tr("Update")));
//    updateControl.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            updateControlPressed(e);
//        }
//    });
  connect(updateControl, SIGNAL(clicked()), this, SLOT(updateControlPressed()));
  updateControl->setToolTip( tr("Press Update to change the Light Control") );
  panel5Layout->addWidget(cancelControl = new QPushButton(tr("Cancel")));
//    cancelControl.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent e) {
//            cancelControlPressed(e);
//        }
//    });
  connect(cancelControl, SIGNAL(clicked()),this, SLOT(cancelControlPressed()));
  cancelControl->setToolTip( tr("Press Cancel to leave unchanged") );
  cancelControl->setVisible(true);
  updateControl->setVisible(false);
  createControl->setVisible(true);
  contentPaneLayout->addLayout(panel5Layout);
//    addControlFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//        public void windowClosing(java.awt.event.WindowEvent e) {
//            cancelControlPressed(NULL);
//        }
//    });
 }
 typeBox->setCurrentIndex(defaultControlIndex);  // force GUI status consistent
 addControlFrame->pack();
 addControlFrame->setVisible(true);
 addControlFrame->toFront();
}

/*protected*/ void AddEditLightDialog::createControlPressed(ActionEvent* )
{
 if (typeBox->currentText()==(noControl))
 {
  return;
 }
 lc = new LightControl ();
 if (setControlInformation(lc))
 {
  controlList->append(lc);
  lightControlChanged = true;
  lightControlTableModel->fireTableDataChanged();
  cancelControlPressed(NULL);
 }
 else
 {
            //addFrame.pack();
  addControlFrame->setVisible(true);
 }
}
/*protected*/ void AddEditLightDialog::updateControlPressed(ActionEvent* )
{
 if (setControlInformation(lc))
 {
  lightControlChanged = true;
  lightControlTableModel->fireTableDataChanged();
  cancelControlPressed(NULL);
 }
 else
 {
//            addFrame.pack();
  addControlFrame->setVisible(true);
 }
}
/*protected*/ void AddEditLightDialog::cancelControlPressed(ActionEvent* )
{
 if (inEditControlMode)
 {
  inEditControlMode = false;
 }
 if (inEditMode) ui->status1->setText( tr("Change data and press Update, or press Cancel.") );
 else ui->status1->setText( tr("Select or enter data, then press Create for a new Light, or press Cancel.") );
 ui->status2->setText( "" );
 ui->status2->setVisible(false);
//		addFrame.pack();
//		addFrame->setVisible(true);
 setVisible(true);
 addControlFrame->setVisible(false);
 addControlFrame->dispose();
 addControlFrame = NULL;
}
/**
 * Responds to Edit button on row in the Light Control Table
 */
/*protected*/ void AddEditLightDialog::editControlAction(int row)
{
 lc = controlList->at(row);
 if (lc==NULL)
 {
  log->error("Invalid light control edit specified");
  return;
 }
 inEditControlMode = true;
 addEditControlWindow();
 int ctType = lc->getControlType();
 switch (ctType)
 {
  case Light::SENSOR_CONTROL:
    setUpControlType(sensorControl);
    typeBox->setCurrentIndex(sensorControlIndex);
    field1a->setText(lc->getControlSensorName());
    stateBox->setCurrentIndex(sensorActiveIndex);
    if (lc->getControlSensorSense()==Sensor::INACTIVE)
    {
        stateBox->setCurrentIndex(sensorInactiveIndex);
    }
    break;
  case Light::FAST_CLOCK_CONTROL:
  {
    setUpControlType(fastClockControl);
    typeBox->setCurrentIndex(fastClockControlIndex);
    int onHour = lc->getFastClockOnHour();
    int onMin = lc->getFastClockOnMin();
    int offHour = lc->getFastClockOffHour();
    int offMin = lc->getFastClockOffMin();
    field1b->setText(formatTime(onHour,onMin));
    field2a->setText(formatTime(offHour,offMin));
    break;
  }
  case Light::TURNOUT_STATUS_CONTROL:
  {
    setUpControlType(turnoutStatusControl);
    typeBox->setCurrentIndex(turnoutStatusControlIndex);
    field1c->setText(lc->getControlTurnoutName());
    stateBox->setCurrentIndex(turnoutClosedIndex);
    if (lc->getControlTurnoutState()==Turnout::THROWN) {
        stateBox->setCurrentIndex(turnoutThrownIndex);
    }
    break;
  }
  case Light::TIMED_ON_CONTROL:
  {
    setUpControlType(timedOnControl);
    typeBox->setCurrentIndex(timedOnControlIndex);
    int duration = lc->getTimedOnDuration();
    field1d->setText(lc->getControlTimedOnSensorName());
    field2b->setText(QString::number(duration));
    break;
  }
  case Light::TWO_SENSOR_CONTROL:
  {
    setUpControlType(twoSensorControl);
    typeBox->setCurrentIndex(twoSensorControlIndex);
    field1a->setText(lc->getControlSensorName());
    field1a2->setText(lc->getControlSensor2Name());
    stateBox->setCurrentIndex(sensorActiveIndex);
    if (lc->getControlSensorSense()==Sensor::INACTIVE) {
        stateBox->setCurrentIndex(sensorInactiveIndex);
   }
   break;
  }
  case Light::NO_CONTROL:
  {
   // Set up as "None"
   setUpControlType(noControl);
   typeBox->setCurrentIndex(noControlIndex);
   field1a->setText("");
   stateBox->setCurrentIndex(sensorActiveIndex);
   break;
  }
 }
 updateControl->setVisible(true);
 createControl->setVisible(false);
 addControlFrame->pack();
 addControlFrame->setVisible(true);
}
/**
 * Reacts to a control type change
 */
void AddEditLightDialog::controlTypeChanged()
{
 setUpControlType( typeBox->currentText() ); // SLOT[]
}

/**
 * Sets the Control Information according to control type
 */
void AddEditLightDialog::setUpControlType(QString ctype)
{
 if ( sensorControl==(ctype) )
 {
    // set up window for sensor control
    f1Label->setText( tr("Sensor Name") );
    field1a->setToolTip( tr("Enter name of Sensor controlling this Light") );
    f2Label->setText( tr("Sense for ON") );
    stateBox->clear();
    stateBox->addItem( tr("Active") );
    sensorActiveIndex = 0;
    stateBox->addItem( tr("Inactive") );
    sensorInactiveIndex = 1;
    stateBox->setToolTip( tr("Select Sensor state corresponding to Light ON") );
    f2Label->setVisible(true);
    field1a->setVisible(true);
    field1a2->setVisible(false);
    field1a->setToolTip( tr("Enter name of Sensor controlling this Light") );
    field1b->setVisible(false);
    field1c->setVisible(false);
    field1d->setVisible(false);
    field2a->setVisible(false);
    field2b->setVisible(false);
    stateBox->setVisible(true);
    defaultControlIndex = sensorControlIndex;
 }
 else if (fastClockControl==(ctype) )
 {
    // set up window for fast clock control
    f1Label->setText( tr("LightScheduleOn") );
    field1b->setToolTip( tr("LightScheduleHint") );
    f2Label->setText( tr("LightScheduleOff") );
    field2a->setToolTip( tr("LightScheduleHint") );
    f2Label->setVisible(true);
    field1a->setVisible(false);
    field1a2->setVisible(false);
    field1b->setVisible(true);
    field1c->setVisible(false);
    field1d->setVisible(false);
    field2a->setVisible(true);
    field2b->setVisible(false);
    stateBox->setVisible(false);
    defaultControlIndex = fastClockControlIndex;
 }
 else if (turnoutStatusControl==(ctype) )
 {
    // set up window for turnout status control
    f1Label->setText( tr("Turnout Name") );
    field1c->setToolTip( tr("Enter name of Turnout whose status is shown in new Light") );
    f2Label->setText( tr("Status for ON") );
    stateBox->clear();
    stateBox->addItem(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText());
    turnoutClosedIndex = 0;
    stateBox->addItem(((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText());
    turnoutThrownIndex = 1;
    stateBox->setToolTip( tr("LightTurnoutSenseHint") );
    f2Label->setVisible(true);
    field1a->setVisible(false);
    field1a2->setVisible(false);
    field1b->setVisible(false);
    field1c->setVisible(true);
    field1d->setVisible(false);
    field2a->setVisible(false);
    field2b->setVisible(false);
    stateBox->setVisible(true);
    defaultControlIndex = turnoutStatusControlIndex;
 }
 else if ( timedOnControl==(ctype) )
 {
    // set up window for sensor control
    f1Label->setText( tr("Trigger Sensor Name") );
    field1d->setToolTip( tr("Duration ON (msec)") );
    f2Label->setText( tr("LightTimedDurationOn") );
    field2b->setToolTip( tr("Enter duration of Timed ON in milliseconds") );
    f2Label->setVisible(true);
    field1a->setVisible(false);
    field1a2->setVisible(false);
    field1b->setVisible(false);
    field1c->setVisible(false);
    field1d->setVisible(true);
    field2a->setVisible(false);
    field2b->setVisible(true);
    stateBox->setVisible(false);
    defaultControlIndex = timedOnControlIndex;
 }
 else if ( twoSensorControl==(ctype) )
 {
    // set up window for two sensor control
    f1Label->setText( tr("LightSensor") );
    field1a->setToolTip( tr("LightSensorHint") );
    f2Label->setText( tr("LightSensorSense") );
    stateBox->clear();
    stateBox->addItem( tr("Active") );
    sensorActiveIndex = 0;
    stateBox->addItem( tr("Inactive") );
    sensorInactiveIndex = 1;
    stateBox->setToolTip( tr("Select Sensor state corresponding to Light ON") );
    f2Label->setVisible(true);
    field1a->setVisible(true);
    field1a2->setVisible(true);
    field1a->setToolTip( tr("Enter name of both Sensors controlling this Light") );
    field1b->setVisible(false);
    field1c->setVisible(false);
    field1d->setVisible(false);
    field2a->setVisible(false);
    field2b->setVisible(false);
    stateBox->setVisible(true);
    defaultControlIndex = twoSensorControlIndex;
 }
 else if (noControl==(ctype) )
 {
    // set up window for no control
    f1Label->setText( tr("No Automated Control Selected") );
    f2Label->setVisible(false);
    field1a->setVisible(false);
    field1a2->setVisible(false);
    field1b->setVisible(false);
    field1c->setVisible(false);
    field1d->setVisible(false);
    field2a->setVisible(false);
    field2b->setVisible(false);
    stateBox->setVisible(false);
    defaultControlIndex = noControlIndex;
 }
 else log->error("Unexpected control type in controlTypeChanged: "+ctype);
 addControlFrame->pack();
 addControlFrame->setVisible(true);
}
/**
 * Responds to the Update button
 */
void AddEditLightDialog::on_btnUpdate_clicked()
{
 AbstractLight* g = curLight;
 // Check if the User Name has been changed
 QString uName = ui->userName->text();
 if (uName==("")) uName="";   // a blank field means no user name
 QString prevUName = g->getUserName();
 if ( (uName!="") && !(uName==(prevUName)) )
 {
  // user name has changed - check if already in use
  Light* p = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->getByUserName(uName);
  if (p!=NULL)
  {
   // Light with this user name already exists
   ui->status1->setText( tr("Error: Light with this User Name already exists.") );
   ui->status2->setText( tr("Please revise User Name and try again.") );
   ui->status2->setVisible(true);
   return;
  }
  // user name is unique, change it
  g->setUserName(uName);
 }
 else if ( (uName=="") && (prevUName!="") )
 {
  // user name has been cleared
  g->setUserName("");
 }
 setLightControlInformation(g);
 // Variable intensity, transitions
 if (((AbstractLight*)g)->isIntensityVariable())
 {
  ((AbstractLight*)g)->setMinIntensity(ui->fieldMinIntensity->value() / 100);
  ((AbstractLight*)g)->setMaxIntensity(ui->fieldMaxIntensity->value() / 100);
  if (((AbstractLight*)g)->isTransitionAvailable())
  {
   ((AbstractLight*)g)->setTransitionTime(ui->fieldTransitionTime->value());
  }
 }
 ((AbstractLight*)g)->activateLight();
 lightCreatedOrUpdated = true;
 on_btnCancel_clicked();
}
/**
 * Responds to the Cancel button
 */
void AddEditLightDialog::on_btnCancel_clicked()
{
 if (inEditMode)
 {
  // if in Edit mode, cancel the Edit and reactivate the Light
  ui->status1->setText( tr("Select or enter data, then press Create for a new Light, or press Cancel.") );
  ui->btnUpdate->setVisible(false);
  ui->btnCreate->setVisible(true);
//  ui->fixedSystemName->setVisible(false);
  ui->prefixBox->setVisible(true);
//  ui->systemNameLabel.setVisible(false);
//  ui->systemLabel.setVisible(true);
//  panel1a.setVisible(true);
  // reactivate the light
  ((AbstractLight*)curLight)->activateLight();
  inEditMode = false;
 }
 // remind to save, if Light was created or edited
 if (lightCreatedOrUpdated)
 {
  ((DefaultUserMessagePreferences*) InstanceManager::getDefault("UserPreferencesManager"))->
                showInfoMessage("Reminder","Remember to save your Light information.","LightTableAction", "remindSaveLight");
 }
 lightCreatedOrUpdated = false;
 // get rid of the add/edit Frame
 clearLightControls();
 ui->status2->setText( "" );
 setVisible(false);
//    addFrame.dispose();
//    addFrame = null;
 close();
}
/*private*/ void AddEditLightDialog::clearLightControls()
{
 for (int i = controlList->size(); i>0; i--)
 {
  controlList->removeAt(i-1);
 }
 lightControlTableModel->fireTableDataChanged();
}
void AddEditLightDialog::handleCreateException(QString sysName)
{
//        javax.swing.JOptionPane.showMessageDialog(addFrame,
//                java.text.MessageFormat.format(
//                    rb.getString("ErrorLightAddFailed"),
//                    new Object[] {sysName}),
//                rb.getString("ErrorTitle"),
//                javax.swing.JOptionPane.ERROR_MESSAGE);
 QMessageBox::critical(this, tr("Error"), tr("Could not create light \"%1\" to add it. Check that number/name is OK.").arg(sysName));
}
/*private*/ void AddEditLightDialog::setLightControlInformation(AbstractLight* g)
{
 if (inEditMode && !lightControlChanged)
 {
  return;
 }
 g->clearLightControls();
 for (int i =0; i<controlList->size(); i++)
 {
  LightControl* lc = controlList->at(i);
  lc->setParentLight((Light*)g);
  g->addLightControl(lc);
 }
}
