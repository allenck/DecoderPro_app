#include "lroutetableaction.h"
#include "jtextfield.h"
#include "instancemanager.h"
#include "../LayoutEditor/jmrijframe.h"
#include "defaultlogix.h"
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include "defaultconditionalmanager.h"
#include <QMessageBox>
#include "proxyturnoutmanager.h"
#include "sensor.h"
#include "jtable.h"
#include <QMap>
#include "signalhead.h"
#include "abstractlightmanager.h"
#include "abstractsignalheadmanager.h"
#include "proxylightmanager.h"
#include "logix.h"
#include "defaultlogix.h"
#include <QCheckBox>
//#include "../LayoutEditor/systemnamecomparator.h"
#include <QtAlgorithms>
#include <QComboBox>
#include "defaultconditionalmanager.h"
#include "defaultconditional.h"
#include "conditionalaction.h"
#include "conditionalvariable.h"
#include "defaultconditionalaction.h"
#include "defaultlogixmanager.h"
#include "jmriuserpreferencesmanager.h"
//#include "../LayoutEditor/systemnamecomparator.h"
#include <QPushButton>
#include <QLabel>
#include "jfilechooser.h"

/*public*/ /*final*/ /*static*/ QString LRouteTableAction::LOGIX_SYS_NAME = "RTX";
/*public*/ /*final*/ /*static*/ QString LRouteTableAction::LOGIX_INITIALIZER = LRouteTableAction::LOGIX_SYS_NAME+"INITIALIZER";
/*public*/ /*final*/ /*static*/ QString LRouteTableAction::CONDITIONAL_SYS_PREFIX = LRouteTableAction::LOGIX_SYS_NAME+"C";
/*public*/ /*final*/ /*static*/ QString LRouteTableAction::CONDITIONAL_USER_PREFIX = "Route ";


LRouteTableAction::LRouteTableAction(QObject *parent) :
    AbstractTableAction("LRoute Table", parent)
{
    common();
}

/**
 * Swing action to create and register groups of Logix Condtionals
 * to perform a railroad control task.
 *
 * @author Pete Cressman Copyright (C) 2009
 *
 */

///*public*/ class LRouteTableAction extends AbstractTableAction {

//	static final ResourceBundle rbx = ResourceBundle
//			.getBundle("jmri.jmrit.beantable.LRouteTableBundle");

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param s
 */
/*public*/ LRouteTableAction::LRouteTableAction(QString s, QObject *parent) : AbstractTableAction(s, parent)
{
 //super(s);
 common();
 //createModel();
//}
///*public*/ LRouteTableAction() {
//    this(tr("LRoute Table"));
}
LRouteTableAction::LRouteTableAction(const LRouteTableAction & that) : AbstractTableAction(that.text(), that.parent()) {}

void LRouteTableAction::common()
{
 log = new Logger("LRouteTableAction");
 _conditionalManager = NULL;
 _logixManager = NULL;

 if(parent() == NULL)
  return;

 _systemName = new JTextField(15);
  _userName = new JTextField(25);


  _addFrame = NULL;
  _newRouteType = true;
  _initialize = false;

  soundFile = new JTextField(30);
  scriptFile = new JTextField(30);

  createButton = new QPushButton(tr("Add LRoute"));
  deleteButton = new QPushButton(tr("Delete LRoute"));
  updateButton = new QPushButton(tr("Update LRoute"));
  cancelButton = new QPushButton(tr("Cancel"));

  routeDirty = false;  // true to fire reminder to save work
  soundChooser = NULL;
  _logixManager = (LogixManager*)InstanceManager::getNullableDefault("LogixManager");
  _conditionalManager = (ConditionalManager*)InstanceManager::getNullableDefault("ConditionalManager");
  // disable ourself if there is no Logix manager or no Conditional manager available
  if ((_logixManager == NULL) || (_conditionalManager == NULL))
  {
   setEnabled(false);
  }

}


/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Road Condtionals
 */
/*protected*/ void LRouteTableAction::createModel()
{
 m = new LBeanTableDataModel(this);
}

//class LBeanTableDataModel :  BeanTableDataModel
//{
    // overlay the state column with the edit column
/*static*/ /*public*/ /*final*/ int LBeanTableDataModel::ENABLECOL = BeanTableDataModel::VALUECOL;
/*static*/ /*public*/ /*final*/ int LBeanTableDataModel::EDITCOL = BeanTableDataModel::DELETECOL;

LBeanTableDataModel::LBeanTableDataModel(QObject* parent) : BeanTableDataModel(parent)
{
 enabledString = tr("Enabled");
 log = new Logger("LBeanTableDataModel");
 self = (LRouteTableAction*)parent;
 sysNameList = QStringList();
 //updateNameList();
 AbstractManager* abstractManager= (AbstractManager*)self->_logixManager;
 connect(abstractManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 init();
}


/**
*Overide to filter out the LRoutes from the rest of Logix
*/
/*protected*/ /*synchronized*/ void LBeanTableDataModel::updateNameList()
{
 // first, remove listeners from the individual objects
 if (!sysNameList .isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=NULL)
    b->removePropertyChangeListener((PropertyChangeListener*)this);
  }
 }
 Manager* m = getManager();
 QStringList list = ((DefaultLogixManager*)m)->getSystemNameList();
 sysNameList =  QStringList();
 // and add them back in
 for (int i = 0; i< list.size(); i++)
 {
  QString sysName = list.at(i);
  if (sysName.startsWith(LRouteTableAction::LOGIX_SYS_NAME))
  {
   sysNameList.append(sysName);
   getBySystemName(sysName)->addPropertyChangeListener((PropertyChangeListener*)this);
   connect(((AbstractNamedBean*)getBySystemName(sysName))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }
 if(log->isDebugEnabled()) {
     log->debug("updateNameList: sysNameList size= "+QString::number(sysNameList.size()));
 }
}
/*public*/ QVariant LBeanTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
    if (section == EDITCOL)
        return ""; // no heading on "Edit"
    if (section == ENABLECOL)
        return enabledString;
    else
        return BeanTableDataModel::headerData(section, orientation, role);
 }
 return QVariant();
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == EDITCOL)
//        return JButton.class;
//    if (col == ENABLECOL)
//        return Boolean.class;
//    else
//        return super.getColumnClass(col);
//}

///*public*/ int getPreferredWidth(int col) {
//    // override default value for SystemName and UserName columns
//    if (col == SYSNAMECOL)
//        return new JTextField(20).getPreferredSize().width;
//    if (col == USERNAMECOL)
//        return new JTextField(25).getPreferredSize().width;
//    // not actually used due to the configDeleteColumn, setColumnToHoldButton, configureButton
//    if (col == EDITCOL)
//        return new JTextField(10).getPreferredSize().width;
//    // not actually used due to the configValueColumn, setColumnToHoldButton, configureButton
//    if (col == ENABLECOL)
//        return new JTextField(5).getPreferredSize().width;
//    if (col == COMMENTCOL)
//        return new JTextField(25).getPreferredSize().width;
//    else
//        return super.getPreferredWidth(col);
//}

/*public*/ Qt::ItemFlags LBeanTableDataModel::flags(const QModelIndex &index) const
{
 if(!index.isValid()) return Qt::NoItemFlags;
 if (index.column() == EDITCOL)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 if (index.column() == ENABLECOL)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 else
  return BeanTableDataModel::flags(index);
}

/*public*/ QVariant LBeanTableDataModel::data(const QModelIndex &mindex, int role) const
{
 if(!mindex.isValid())
     return QVariant();
 if(role == Qt::DisplayRole /*|| role == Qt::EditRole*/)
 {
  if (mindex.column() == EDITCOL)
  {
   return ("Edit");
  }
  //  else if (index.column() == ENABLECOL)
  //  {
  //   Logix* x = (Logix*)getBySystemName(data(createIndex(index.row(), SYSNAMECOL),role).toString());
//   return ((DefaultLogix*)x)->getEnabled()?Qt::Checked:Qt::Unchecked;
//  }
  else
   return BeanTableDataModel::data(mindex,role);
 }
 else if(role == Qt::CheckStateRole)
 {
  if (mindex.column() == ENABLECOL)
  {
   Logix* x = (Logix*)getBySystemName(data(index(mindex.row(), SYSNAMECOL),Qt::DisplayRole).toString());
   return ((DefaultLogix*)x)->getEnabled()?Qt::Checked:Qt::Unchecked;
  }
 }
 return QVariant();
}

/*public*/ bool LBeanTableDataModel::setData(const QModelIndex &mindex, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  if(!mindex.isValid())
      return false;
  if (mindex.column() == EDITCOL)
  {
   // set up to edit
   QString sName =  data(index(mindex.row(), SYSNAMECOL),role).toString();
   self->editPressed(sName);
  }
//  else if (index.column() == ENABLECOL)
//  {
//   // alternate
//   Logix* x = (Logix*) getBySystemName(data(createIndex(index.row(),
//                SYSNAMECOL),role).toString());
//   bool v = ((DefaultLogix*)x)->getEnabled();
//   ((DefaultLogix*)x)->setEnabled(!v);
//  }
  else
   BeanTableDataModel::setData(mindex, value, role);
 }
 if(role == Qt::CheckStateRole)
 {
  if (mindex.column() == ENABLECOL)
  {
   // alternate
   Logix* x = (Logix*) getBySystemName(data(index(mindex.row(),
                     SYSNAMECOL),Qt::DisplayRole).toString());
   bool v = ((DefaultLogix*)x)->getEnabled();
   ((DefaultLogix*)x)->setEnabled(!v);
   return true;
  }
 }
 return false;
}

/**
 * Delete the bean after all the checking has been done.
 * <P>
 * Deactivate the Logix and remove it's conditionals
 */
void LBeanTableDataModel::doDelete(NamedBean* bean)
{
 if (bean != NULL)
 {
  Logix* l = (Logix*) bean;
  l->deActivateLogix();
  // delete the Logix and all its Conditionals
  self->_logixManager->deleteLogix(l);
 }
}

/*protected*/ bool LBeanTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==(enabledString))
  return true;
 else
  return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ Manager* LBeanTableDataModel::getManager() {
    return self->_logixManager;
}

/*public*/ NamedBean* LBeanTableDataModel::getBySystemName(QString name) const {
    return (NamedBean*)((DefaultLogixManager*)self->_logixManager)->getBySystemName(name);
}

/*public*/ NamedBean* LBeanTableDataModel::getByUserName(QString name) {
    return (NamedBean*)((DefaultLogixManager*)self->_logixManager)->getByUserName(name);
}

/*public int getDisplayDeleteMsg() { return InstanceManager.getDefault(jmri.UserPreferencesManager.class).getMultipleChoiceOption(getClassName(),"delete"); }
public void setDisplayDeleteMsg(int boo) { InstanceManager.getDefault(jmri.UserPreferencesManager.class).setMultipleChoiceOption(getClassName(), "delete", boo); }*/

/*protected*/ QString  LBeanTableDataModel::getMasterClassName()
{
 //return /*getClassName();*/ metaObject()->className();
 return "jmri.jmrit.beantable.LRouteTableAction";
}

#if 1
/*public*/ void LBeanTableDataModel::configureTable(JTable* table)
{
//    table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());
//    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
    BeanTableDataModel::configureTable(table);
}
#endif
// Not needed - here for interface compatibility
/*public*/ void LBeanTableDataModel::clickOn(NamedBean* /*t*/) {
}

/*public*/ QString LBeanTableDataModel::getValue(QString /*s*/) const
{
    return "";
}

// ovewrdife to get right width
/*protected*/ void LBeanTableDataModel::configDeleteColumn(JTable* table) {
 // have the delete column hold a button
 setColumnToHoldButton(table, DELETECOL,
            new QPushButton(tr("Edit")));
}
/*protected*/ void LBeanTableDataModel::configValueColumn(JTable* /*table*/) {
}

/*protected*/ QString LBeanTableDataModel::getBeanType(){
    return "LRoute";
}

//};

/*protected*/ void LRouteTableAction::setTitle()
{
 f->setTitle(tr("LRoute Table"));
}

/*protected*/ QString LRouteTableAction::helpTarget()
{
 return "package.jmri.jmrit.beantable.LRouteTable";
}
///////////////////////////////////// Edit window //////////////////////////////


bool systemNameComparator(LRouteElement* e1, LRouteElement* e2)
{
 QString o1 = e1->getSysName();
 QString o2 = e2->getSysName();
 if (o1.length() <= 3 && o2.length() <= 3)
 {
  return o1 < (o2);
 }
 else if (/*!o1.regionMatches(0,o2,0,2)*/ o1.mid(0,2) != o2.mid(0,2))
 {
  return o1 < (o2);
 }
 else
 {
  // extract length of digits
 QString ch1 = o1.mid(2);
 QString ch2 = o2.mid(2);
 int numDigit1 = 0;
 int numDigit2 = 0;
 for (int i=0; i < ch1.length(); i++)
 {
  //if (Character.isDigit(ch1[i]))
  if(ch1.at(i).isDigit())
  {
   numDigit1++;
  }
  else
  {
   break;
  }
 }
 for (int i=0; i<ch2.length(); i++)
 {
  if (ch2.at(i).isDigit())
  {
   numDigit2++;
  }
  else
  {
   break;
  }
 }
 if (numDigit1==numDigit2)
 {
  try
  {
   //int diff = Integer.parseInt(new String(ch1, 0, numDigit1)) -                              Integer.parseInt(new String(ch2, 0, numDigit2));
   int diff = ch1.mid(0,numDigit1).toInt() - ch1.mid(0,numDigit2).toInt();
   if (diff != 0)
   {
    //return diff;
       if(diff < 0)
           return true;
       else
           return false;
   }
   if (numDigit1==ch1.length() && numDigit2==ch2.length())
   {
    return diff;
   }
   else
   {
    if (numDigit1==ch1.length())
    {
     return -1;
    }
    // both have non-digit chars remaining
//    return new String(ch1, numDigit1, ch1.length-numDigit1) < (
//                    new String(ch2, numDigit2, ch2.length-numDigit2));
    return ch1.mid(numDigit1, ch1.length()-numDigit1) < ch2.mid(numDigit2, ch2.length()-numDigit2);
   }
  }
  catch (NumberFormatException nfe)
  {
    return o1.compare(o2);
  }
   catch (IndexOutOfBoundsException ioob)
   {
     return o1.compare(o2);
   }
  }
  else
  {
   if ((numDigit1 - numDigit2) < 0)
      return true;
   else return false;
  }
 }
}
void LRouteTableAction::buildLists()
{
 //TreeSet <RouteInputElement>inputTS = new TreeSet<RouteInputElement>(new RouteElementComparator());
 //TreeSet <RouteOutputElement>outputTS = new TreeSet<RouteOutputElement>(new RouteElementComparator());
 QList<LRouteInputElement*>* inputTS = new QList<LRouteInputElement*>();
 QList<LRouteOutputElement*>* outputTS = new QList<LRouteOutputElement*>();

 //TreeSet <RouteInputElement>inputTS = new TreeSet<RouteInputElement>();
 //TreeSet <RouteOutputElement>outputTS = new TreeSet<RouteOutputElement>();
 TurnoutManager* tm = InstanceManager::turnoutManagerInstance();
 QStringList systemNameList = ((ProxyTurnoutManager*)tm)->getSystemNameList();
 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
    QString systemName = iter.next();
    QString userName = ((ProxyTurnoutManager*)tm)->getBySystemName(systemName)->getUserName();
    inputTS->append(new LRouteInputTurnout(systemName, userName));
    outputTS->append(new LRouteOutputTurnout(systemName, userName));
 }

 //TreeSet <AlignElement>alignTS = new TreeSet<AlignElement>(new RouteElementComparator());
 QList<LAlignElement*>* alignTS = new QList<LAlignElement*>();
 SensorManager* sm = InstanceManager::sensorManagerInstance();
 systemNameList = ((ProxySensorManager*)sm)->getSystemNameList();
 iter = QStringListIterator(systemNameList);
 while (iter.hasNext())
 {
    QString systemName = iter.next();
    QString userName = ((ProxySensorManager*)sm)->getBySystemName(systemName)->getUserName();
    inputTS->append(new LRouteInputSensor(systemName, userName));
    outputTS->append(new LRouteOutputSensor(systemName, userName));
    alignTS->append(new LAlignElement(systemName, userName));
 }

LightManager* lm = InstanceManager::lightManagerInstance();
systemNameList = ((ProxyLightManager*)lm)->getSystemNameList();
iter = QStringListIterator(systemNameList);
while (iter.hasNext()) {
    QString systemName = iter.next();
    QString userName = ((ProxyLightManager*)lm)->getBySystemName(systemName)->getUserName();
    inputTS->append(new LRouteInputLight(systemName, userName));
    outputTS->append(new LRouteOutputLight(systemName, userName));
}
SignalHeadManager* shm = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
systemNameList = ((AbstractSignalHeadManager*)shm)->getSystemNameList();
iter = QStringListIterator(systemNameList);
while (iter.hasNext()) {
    QString systemName = iter.next();
    QString userName = ((AbstractSignalHeadManager*)shm)->getBySystemName(systemName)->getUserName();
    inputTS->append(new LRouteInputSignal(systemName, userName));
    outputTS->append(new LRouteOutputSignal(systemName, userName));
}

  _includedInputList = new QList <LRouteInputElement*>();
  _includedOutputList = new QList <LRouteOutputElement*>();
  _inputList = new QList <LRouteInputElement*> (/*inputTS.size()*/);
  _outputList = new QList <LRouteOutputElement*> (/*outputTS.size()*/);
  _inputMap = new QMap <QString, LRouteInputElement*> (/*inputTS.size()*/);
  _outputMap = new QMap <QString, LRouteOutputElement*>(/*outputTS.size()*/);
  _inputUserMap = new QMap <QString, LRouteInputElement*> ();
  _outputUserMap = new QMap <QString, LRouteOutputElement*> ();
  QListIterator<LRouteInputElement*> it(*inputTS);
   while(it.hasNext())
   {
    LRouteInputElement* elt = it.next();
    _inputList->append(elt);
    QString key = elt->getType()+elt->getSysName();
    _inputMap->insert(key, elt);
    QString user = elt->getUserName();
    if (user != NULL) {
        key = elt->getType()+user;
        _inputUserMap->insert(key, elt);
    }
   }
   QListIterator<LRouteOutputElement*> itOut(*outputTS);
   while(itOut.hasNext())
   {
    LRouteOutputElement* elt = itOut.next();
    _outputList->append(elt);
    QString key = elt->getType()+elt->getSysName();
    _outputMap->insert(key, elt);
    QString user = elt->getUserName();
    if (user != NULL) {
        key = elt->getType()+user;
        _outputUserMap->insert(key, elt);
   }
  }
  _includedAlignList = new QList <LAlignElement*> ();
  _alignList = new QList <LAlignElement*> (/*alignTS.size()*/);
  _alignMap = new QMap <QString, LAlignElement*>(/*alignTS.size()*/);
  _alignUserMap = new QMap <QString, LAlignElement*>();
  QListIterator<LAlignElement*> itAlign(*alignTS);
  while(itAlign.hasNext())
  {
    LAlignElement* elt = itAlign.next();
    _alignList->append(elt);
    QString key = elt->getType()+elt->getSysName();
    _alignMap->insert(key, elt);
    QString user = elt->getUserName();
    if (user != NULL) {
        key = elt->getType()+user;
        _alignUserMap->insert(key, elt);
  }
 }
  qSort(_inputList->begin(), _inputList->end(), systemNameComparator);
  qSort(_outputList->begin(), _outputList->end(), systemNameComparator);
  qSort(_alignList->begin(), _alignList->end(), systemNameComparator);
}

/**
*   Edit button in Logix Route table pressed
*/
void LRouteTableAction::editPressed(QString sName) {
#if 1
// Logix was found, initialize for edit
Logix* logix = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
if (logix == NULL) {
    log->error("Logix \""+sName+"\" not Found.");
    return;
}

// deactivate this Logix
_systemName->setText(sName);
// create the Edit Logix Window
// Use separate Thread so window is created on top
//Runnable t = new Runnable() {
//        /*public*/ void run() {
//            //Thread.yield();
//            setupEdit(NULL);
//            _addFrame.setVisible(true);
//            }
//        };
//javax.swing.SwingUtilities.invokeLater(t);

            setupEdit(NULL);
            _addFrame->setVisible(true);

#endif
}
#if 1
/**
* Interprets the conditionals from the Logix that was selected for editing
* and attempts to reconstruct the window entries.
*/
void LRouteTableAction::setupEdit(ActionEvent* /*e*/)
{
 makeEditWindow();
 Logix* logix = checkNamesOK();
 if (logix == NULL)
 {
    return;
 }

 ((DefaultLogix*)logix)->deActivateLogix();
 // get information for this route
 _systemName->setEnabled(false);
 _userName->setEnabled(false);
 _systemName->setText(((DefaultLogix*)logix)->getSystemName());
 _userName->setText(((DefaultLogix*)logix)->getUserName());
 QString logixSysName = ((DefaultLogix*)logix)->getSystemName();
 int numConditionals = ((DefaultLogix*)logix)->getNumConditionals();
 if(log->isDebugEnabled())
 {
  log->debug("setupEdit: logixSysName= "+logixSysName+", numConditionals= "+numConditionals);
 }
 for (int i=0; i<numConditionals; i++)
 {
  QString cSysName = ((DefaultLogix*)logix)->getConditionalByNumberOrder(i);

    switch (getRouteConditionalType(logixSysName, cSysName))
    {
        case 'T':
            getControlsAndActions(cSysName);
            break;
        case 'A':
            getAlignmentSensors(cSysName);
            break;
        case 'L':
            getLockConditions(cSysName);
            break;
    }

 }
 // set up buttons and notes
 deleteButton->setVisible(true);
 cancelButton->setVisible(true);
 updateButton->setVisible(true);
 _typePanel->setVisible(false);
 _initialize = LOGIX_INITIALIZER==(logixSysName);
 if (_initialize)
 {
  //_initializeButton>doClick();
  initializePressed();
 }
 else
 {
  //_newRouteButton->doClick();
  newRoutePressed();
 }
 createButton->setVisible(false);
}   // setupEdit
#endif
 void LRouteTableAction::initializePressed()
 {
  _initialize = true;
  _newRouteType = true;
  _systemName->setEnabled(false);
  _systemName->setText(LOGIX_INITIALIZER);
 }
void LRouteTableAction::newRoutePressed()
{
 _newRouteType = true;
 _systemName->setEnabled(true);
}


/**
* Return the type letter from the possible LRoute conditional.
*/
char LRouteTableAction::getRouteConditionalType(QString logixSysName, QString cSysName)
{
 if (cSysName.startsWith(logixSysName))
 {
  QByteArray chNum = cSysName.mid(logixSysName.length()).toLatin1();
  QString str = cSysName.mid(logixSysName.length());
    int i = 0;
    while (str.at(i).isDigit()) {
            i++;
    }
    return chNum.at(i);
 }
 return 0;
}

/**
* Extract the Control (input) and Action (output) elements and their states
*/
void LRouteTableAction::getControlsAndActions(QString cSysName)
{
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cSysName);
if (c != NULL)
{
 QList <ConditionalAction*>* actionList = ((DefaultConditional*)c)->getCopyOfActions();
 bool onChange = false;
 for (int k=0; k<actionList->size(); k++)
 {
  ConditionalAction* action = actionList->at(k);
  int type = 0;
  switch (action->getType())
  {
    case Conditional::ACTION_SET_SENSOR:
        type = SENSOR_TYPE;
        break;
    case Conditional::ACTION_SET_TURNOUT:
        type = TURNOUT_TYPE;
        break;
    case Conditional::ACTION_SET_LIGHT:
        type = LIGHT_TYPE;
        break;
    case Conditional::ACTION_SET_SIGNAL_APPEARANCE:
    case Conditional::ACTION_SET_SIGNAL_HELD:
    case Conditional::ACTION_CLEAR_SIGNAL_HELD:
    case Conditional::ACTION_SET_SIGNAL_DARK:
    case Conditional::ACTION_SET_SIGNAL_LIT:
        type = SIGNAL_TYPE;
        break;
    case Conditional::ACTION_RUN_SCRIPT:
        scriptFile->setText(action->getActionString());
        continue;
    case Conditional::ACTION_PLAY_SOUND:
        soundFile->setText(action->getActionString());
        continue;
    default:
//        JOptionPane.showMessageDialog(
//                        _addFrame, java.text.MessageFormat.format(tr("TypeWarn"),
//                            new Object [] {action.toString(), c.getSystemName()}),
//                         rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Edit Action item \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(((DefaultConditionalAction*)action)->getActionString()).arg(((DefaultConditional*)c)->getSystemName()));
       continue;
  }
  QString name = action->getDeviceName();
  QString key = type+name;
  LRouteOutputElement* elt = _outputUserMap->value(key);
  if (elt == NULL)
  { // try in system name map
   elt = _outputMap->value(key);
  }
  if (elt == NULL)
  {
//   javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, java.text.MessageFormat.format(tr("TypeWarn"),
//                    new Object [] {action.toString(), c.getSystemName()}),
//                 rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Edit Action item \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(((DefaultConditionalAction*)action)->getActionString()).arg(((DefaultConditional*)c)->getSystemName()));

  }
  else
  {
   elt->setIncluded(true);
   elt->setState(action->getActionData());
   bool change = (action->getOption() == Conditional::ACTION_OPTION_ON_CHANGE);
   if ( k==0 )
   {
    onChange = change;
   }
   else if (change != onChange)
   {
//    javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, java.text.MessageFormat.format(tr("OnChangeWarn"),
//                        new Object [] {action.toString(), c.getSystemName()}),
//                     rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
       QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Action item \"%1\" is triggered differently from the other actions on conditional \"%2\".").arg(action->getActionString()).arg(((DefaultConditional*)c)->getSystemName()));
   }
  }
 }
 QList <ConditionalVariable*>* varList = ((DefaultConditional*)c)->getCopyOfStateVariables();
 for (int k=0; k<varList->size(); k++)
 {
  ConditionalVariable* variable = varList->at(k);
  int testState = variable->getType();
  //boolean negated = variable.isNegated();
  int type = 0;
  switch (testState)
  {
    case Conditional::TYPE_SENSOR_ACTIVE:
        type = SENSOR_TYPE;
        //if (negated) testState = Conditional::TYPE_SENSOR_INACTIVE;
        break;
    case Conditional::TYPE_SENSOR_INACTIVE:
        type = SENSOR_TYPE;
        //if (negated) testState = Conditional::TYPE_SENSOR_ACTIVE;
        break;
    case Conditional::TYPE_TURNOUT_CLOSED:
        type = TURNOUT_TYPE;
        //if (negated) testState = Conditional::TYPE_TURNOUT_THROWN;
        break;
    case Conditional::TYPE_TURNOUT_THROWN:
        type = TURNOUT_TYPE;
        //if (negated) testState = Conditional::TYPE_TURNOUT_CLOSED;
        break;
    case Conditional::TYPE_LIGHT_ON:
        type = LIGHT_TYPE;
        //if (negated) testState = Conditional::TYPE_LIGHT_OFF;
        break;
    case Conditional::TYPE_LIGHT_OFF:
        type = LIGHT_TYPE;
        //if (negated) testState = Conditional::TYPE_LIGHT_ON;
        break;
    case Conditional::TYPE_SIGNAL_HEAD_LIT:
    case Conditional::TYPE_SIGNAL_HEAD_RED:
    case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
    case Conditional::TYPE_SIGNAL_HEAD_GREEN:
    case Conditional::TYPE_SIGNAL_HEAD_DARK:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
    case Conditional::TYPE_SIGNAL_HEAD_HELD:
        type = SIGNAL_TYPE;
        break;
    default:
        if (LOGIX_INITIALIZER!=(variable->getName()))
        {
//            javax.swing.JOptionPane.showMessageDialog(
//                            _addFrame, java.text.MessageFormat.format(tr("TypeWarnVar"),
//                                new Object [] {variable.toString(), c.getSystemName()}),
//                             rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
            QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("State Variable \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(variable->toString()).arg(((DefaultConditional*)c)->getSystemName()));
        }
        continue;
       }
       int opern = variable->getOpern();
        if (k!= 0 && (opern==Conditional::OPERATOR_AND || opern==Conditional::OPERATOR_AND_NOT)) {
            // guess this is a VETO
            testState += VETO;
        } else if (onChange) {
            testState = Route::ONCHANGE;
        }
        QString name = variable->getName();
        QString key = type+name;
        LRouteInputElement* elt = _inputUserMap->value(key);
        if (elt == NULL) { // try in system name map
            elt = _inputMap->value(key);
     }
    if (elt == NULL)
    {
     if (LOGIX_INITIALIZER!=(name))
     {
//                javax.swing.JOptionPane.showMessageDialog(
//                        _addFrame, java.text.MessageFormat.format(tr("TypeWarnVar"),
//                            new Object [] {variable.toString(), c.getSystemName()}),
//                         rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("State Variable \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(variable->toString()).arg(((DefaultConditional*)c)->getSystemName()));

    }
   }
   else
   {
    elt->setIncluded(true);
    elt->setState(testState);
   }
  }
 }
}   // getControlsAndActions

/**
* Extract the Alignment Sensors and their types
*/
void LRouteTableAction::getAlignmentSensors(QString cSysName)
{
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cSysName);
 if (c != NULL)
 {
  LAlignElement* element = NULL;
  QString name = NULL;
 QList <ConditionalAction*>* actionList =   ((DefaultConditional*)c)->getCopyOfActions();
 for (int k=0; k<actionList->size(); k++)
 {
  ConditionalAction* action = actionList->at(k);
  if (action->getType() != Conditional::ACTION_SET_SENSOR)
  {
//   javax.swing.JOptionPane.showMessageDialog(
//                    _addFrame, java.text.MessageFormat.format(tr("AlignWarn1"),
//                        new Object [] {action.toString(), c.getSystemName()}),
//                     rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Alignment action item \"%1\" on Conditional \"%2\" has an action type that cannot be edited.").arg(((DefaultConditionalAction*)action)->getActionString()).arg(((DefaultConditional*)c)->getSystemName()));
  }
  else
  {
   name = action->getDeviceName();
   QString key = SENSOR_TYPE+name;
    element = _alignUserMap->value(key);
    if (element == NULL) { // try in system name map
        element = _alignMap->value(key);
  }
  if (element == NULL)
  {
//        javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, java.text.MessageFormat.format(tr("TypeWarn"),
//                    new Object [] {action.toString(), c.getSystemName()}),
//                 rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("State Variable \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(((DefaultConditionalAction*)action)->getActionString()).arg(((DefaultConditional*)c)->getSystemName()));


  }
  else if (name!=(action->getDeviceName()))
  {
  //        javax.swing.JOptionPane.showMessageDialog(
  //                        _addFrame,   java.text.MessageFormat.format(tr("AlignWarn2"),
  //                            new Object [] {action.toString(), action.getDeviceName(), c.getSystemName()}),
  //                         rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Sensors \"%1\" and \"%2\" on Conditional \"%3\" are both used for the same Alignment.").arg(((DefaultConditionalAction*)action)->getActionString()).arg(action->getDeviceName()).arg(((DefaultConditional*)c)->getSystemName()));

  }
  else
  {
   element->setIncluded(true);
  }
 }
}
// the action elements are identified in getControlsAndActions().
//  Just identify the type of sensing
QList <ConditionalVariable*>* varList = ((DefaultConditional*)c)->getCopyOfStateVariables();
int atype = 0;
for (int k=0; k<varList->size(); k++)
{
 ConditionalVariable* variable = varList->at(k);
 int testState = variable->getType();
 int type = 0;
 switch (testState) {
    case Conditional::TYPE_SENSOR_ACTIVE:
    case Conditional::TYPE_SENSOR_INACTIVE:
        type = SENSOR_TYPE;
        break;
    case Conditional::TYPE_TURNOUT_CLOSED:
    case Conditional::TYPE_TURNOUT_THROWN:
        type = TURNOUT_TYPE;
        break;
    case Conditional::TYPE_LIGHT_ON:
    case Conditional::TYPE_LIGHT_OFF:
        type = LIGHT_TYPE;
        break;
    case Conditional::TYPE_SIGNAL_HEAD_LIT:
    case Conditional::TYPE_SIGNAL_HEAD_RED:
    case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
    case Conditional::TYPE_SIGNAL_HEAD_GREEN:
    case Conditional::TYPE_SIGNAL_HEAD_DARK:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
    case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
    case Conditional::TYPE_SIGNAL_HEAD_HELD:
        type = SIGNAL_TYPE;
        break;
    default:
        if (LOGIX_INITIALIZER!=(variable->getName()))
        {
//                    javax.swing.JOptionPane.showMessageDialog(
//                            _addFrame, java.text.MessageFormat.format(tr("TypeWarnVar"),
//                                new Object [] {variable.toString(), c.getSystemName()}),
//                             rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("State Variable \"%1\" on Conditional \"%2\" cannot be edited in LRoute.").arg(variable->toString()).arg(((DefaultConditional*)c)->getSystemName()));
     }
     continue;
    }
    if ( k==0 )
    {
     atype = type;
    }
    else if (atype != type)
    {
      // more than one type. therefor, ALL
      atype = ALL_TYPE;
      break;
    }
   }
  if (element != NULL)
  {
   element->setState(atype);
  }
 }
}


/**
* Extract the Lock expression.  For now, same as action control expression
*/
void LRouteTableAction::getLockConditions(QString cSysName)
{
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cSysName);
if (c != NULL) {
    _lock = true;
    // Verify conditional is what we think it is
    QList <LRouteOutputElement*>* tList = makeTurnoutLockList();
    QList <ConditionalAction*>* actionList = ((DefaultConditional*)c)->getCopyOfActions();
    if (actionList->size() != tList->size())
    {
//        javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, java.text.MessageFormat.format(tr("LockWarn1"),
//                    new Object [] {Integer.toString(tList.size()), c.getSystemName(),
//                        Integer.toString(actionList.size())}),
//                 rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_addFrame, tr("Edit Difference"), tr("Expected \"%1\" turnouts to lock on Conditional \"%2\", but it has %3 action items.").arg(tList->size()).arg(((DefaultConditional*)c)->getSystemName()).arg(actionList->size()));
    }
    for (int k=0; k<actionList->size(); k++)
    {
        ConditionalAction* action = actionList->value(k);
        if (((DefaultConditionalAction*)action)->getType() != Conditional::ACTION_LOCK_TURNOUT) {
//            javax.swing.JOptionPane.showMessageDialog(
//                    _addFrame, java.text.MessageFormat.format(tr("LockWarn2"),
//                        new Object [] {action.getDeviceName(), c.getSystemName()}),
//                     rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
            QMessageBox::warning(_addFrame, tr("Edit Differences"), tr("Action item \"%1\" on Conditional \"%2\" has an action type that cannot be edited (set Lock expected).").arg(((DefaultConditionalAction*)action)->getDeviceName()).arg(((DefaultConditional*)c)->getSystemName()));
        } else {
            QString name = ((DefaultConditionalAction*)action)->getDeviceName();
            bool found = false;
           QList <LRouteOutputElement*>* lockList = makeTurnoutLockList();
            for (int j=0; j<lockList->size(); j++) {
                LRouteOutputElement* elt = lockList->value(j);
                if (name==(elt->getUserName()) || name==(elt->getSysName())) {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
//                javax.swing.JOptionPane.showMessageDialog(
//                        _addFrame, java.text.MessageFormat.format(tr("LockWarn3"),
//                            new Object [] {name, c.getSystemName()}),
//                         rbx .getString("EditDiff"), javax.swing.JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(_addFrame, tr("Edit Differences"), tr("Turnout \"%1\" on Conditional \"%2\" not expected to be locked.").arg(name).arg(((DefaultConditional*)c)->getSystemName()));
    }
   }
  }
 }
}

/**
* Responds to the Cancel button
*/
void LRouteTableAction::cancelPressed(ActionEvent* /*e*/)
{
 Logix* logix = checkNamesOK();
 if (logix != NULL)
 {
    ((DefaultLogix*)logix)->activateLogix();
 }
 clearPage();
}

/*protected*/ void LRouteTableAction::addPressed(ActionEvent* /*e*/) {
 makeEditWindow();
 createButton->setVisible(true);
 cancelButton->setVisible(true);
 _typePanel->setVisible(true);
 _addFrame->setVisible(true);
 _systemName->setEnabled(true);
 _userName->setEnabled(true);
}

// Set up window
void LRouteTableAction::makeEditWindow()
{
 if (_addFrame==NULL)
 {
   buildLists();
    _addFrame = new JmriJFrameX(tr("Add/Edit LRoute"), false, false);
    _addFrame->addHelpMenu("package.jmri.jmrit.beantable.LRouteAddEdit", true);
    _addFrame->setLocation(100,30);

    QTabWidget* tabbedPane = new QTabWidget();

    //////////////////////////////////// Tab 1 /////////////////////////////
    QWidget* tab1 = new QWidget();
    tab1->setLayout(new QVBoxLayout(tab1/*, BoxLayout.Y_AXIS*/));
    //tab1.add(Box.createVerticalStrut(10));
    // add system name
    QWidget* p = new QWidget();
    p->setLayout(new QHBoxLayout());
    p->layout()->addWidget(new QLabel(tr("SystemName")));
    p->layout()->addWidget(_systemName);
    _systemName->setToolTip(tr("SystemNameHint"));
    tab1->layout()->addWidget(p);
    // add user name
    p = new QWidget();
    p->setLayout(new QHBoxLayout());
    p->layout()->addWidget(new QLabel(tr("UserName")));
    p->layout()->addWidget(_userName);
    _userName->setToolTip(tr("UserNameHint"));
    tab1->layout()->addWidget(p);

    QWidget* pa = new QWidget();
    pa->setLayout(new QVBoxLayout());
    p = new QWidget();
    p->setLayout(new QVBoxLayout(p/*, BoxLayout.Y_AXIS*/));
    p->layout()->addWidget(new QLabel(tr("Tab1: Name the LRoute, select parameters from other tabs, then return here and use buttons at the bottom.")));
    p->layout()->addWidget(new QLabel(tr("Tab2: Select the devices you want to control and the actions you want them to perform.")));
    p->layout()->addWidget(new QLabel(tr("Tab3: Select the devices you want to use as triggers and their states to trigger the above Tab2 actions.")));
    p->layout()->addWidget(new QLabel(tr("Tab4: Other LRoute parameters - Alignment sensors, scripts and sound files, locks, etc.  ")));
    pa->layout()->addWidget(p);
    tab1->layout()->addWidget(pa);

    _newRouteButton = new QRadioButton(tr("New")/*,true*/);
    QRadioButton* oldRoute = new QRadioButton(tr("Old")/*,false*/);
    _initializeButton = new QRadioButton(tr("Initialize")/*,false*/);
    _initializeButton->setChecked(false);
    _newRouteButton->setToolTip(tr("All triggers and vetoes enabled in a single Conditional:: "));
//    _newRouteButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _newRouteType = true;
//                _systemName.setEnabled(true);
//            }
//        });
    connect(_newRouteButton, SIGNAL(clicked()), this, SLOT(newRoutePressed()));
    oldRoute->setToolTip(tr("OldRouteHint"));
//    oldRoute::addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _newRouteType = false;
//                _systemName.setEnabled(true);
//            }
//        });
    _initializeButton->setToolTip(tr("Defines a Logix that executes before all other Logixs to initialize devices at load time. "));
//    _initializeButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                _initialize = true;
//                _newRouteType = true;
//                _systemName.setEnabled(false);
//                _systemName.setText(LOGIX_INITIALIZER);
//            }
//        });
    connect(_initializeButton, SIGNAL(clicked()), this, SLOT(initializePressed()));
    _typePanel = makeShowButtons(_newRouteButton, oldRoute, _initializeButton, "LRouteType");
    //_typePanel.setBorder(BorderFactory.createEtchedBorder());
    _typePanel->setFrameStyle(QFrame::Box | QFrame::Raised);
    _typePanel->setLineWidth(2);
    tab1->layout()->addWidget(_typePanel);
    //tab1.add(Box.createVerticalGlue());

    // add buttons - Add Route button
    QWidget* pb = new QWidget();
    pb->setLayout(new QHBoxLayout());
    pb->layout()->addWidget(createButton);
//    createButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            createPressed(e);
//        }
//    });
    connect(createButton, SIGNAL(clicked()), this, SLOT(createPressed()));
    createButton->setToolTip(tr("Add a new LRoute using data entered above"));
    createButton->setObjectName("Add LRoute");

    // Delete Route button
    pb->layout()->addWidget(deleteButton);
//    deleteButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            deletePressed(e);
//        }
//    });
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
    deleteButton->setToolTip(tr("DeleteHint"));
    // Update Route button
    pb->layout()->addWidget(updateButton);
//    updateButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            updatePressed();
//        }
//    });
    connect(updateButton, SIGNAL(clicked()), this, SLOT(updatePressed()));
    updateButton->setToolTip(tr("UpdateHint"));
    updateButton->setObjectName("UpdateButton");

    // Cancel button
    pb->layout()->addWidget(cancelButton);
//    cancelButton.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            cancelPressed(e);
//        }
//    });
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
    cancelButton->setToolTip(tr("Leave Edit mode without changing the LRoute"));
    cancelButton->setObjectName("CancelButton");

    // Show the initial buttons, and hide the others
    cancelButton->setVisible(true);
    updateButton->setVisible(false);
    createButton->setVisible(false);
    deleteButton->setVisible(false);
    tab1->layout()->addWidget(pb);

    tab1->setVisible(true);
    tabbedPane->addTab(tab1, tr("Basic LRoute")); //NULL, tab1, tr("BasicTabHint"));
    tab1->setToolTip(tr("Enter names for this LRoute"));

    //////////////////////////////////// Tab 2 /////////////////////////////
    QWidget* tab2 = new QWidget();
    tab2->setLayout(new QVBoxLayout(tab2/*, BoxLayout.Y_AXIS*/));
    tab2->layout()->addWidget(new QLabel(tr("Select the Output Action states to set for this LRoute")));
    _outputAllButton = new QRadioButton(tr("All"))/*,true)*/;
    _outputAllButton->setChecked(true);
    QRadioButton* includedOutputButton = new QRadioButton(tr("Included")/*,false*/);
    includedOutputButton->setChecked(false);
    tab2->layout()->addWidget(makeShowButtons(_outputAllButton, includedOutputButton, NULL, "Show"));
//    _outputAllButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                if (!_showAllOutput) {
//                    _showAllOutput = true;
//                    _outputModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(_outputAllButton, SIGNAL(clicked()), this, SLOT(outputAllButtonPressed()));
//    includedOutputButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of included Turnouts only, if needed
//                if (_showAllOutput) {
//                    _showAllOutput = false;
//                    initializeIncludedOutputList();
//                    _outputModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(includedOutputButton, SIGNAL(clicked()), this, SLOT(includedOutputButtonPressed()));
    tab2->layout()->addWidget(new QLabel(tr("Choose Sensors, Turnouts, Lights and/or Signals for actions to set")));

    _outputModel = new RouteOutputModelX(this);
    JTable* routeOutputTable = new JTable();
    routeOutputTable->setModel(_outputModel);
    routeOutputTable->resizeColumnsToContents();
    //_outputScrollPane = makeColumns(routeOutputTable, _setStateCombo, true);
    routeOutputTable->setItemDelegateForColumn(RouteElementModel::STATE_COLUMN, new LComboBoxDelegate(_outputModel, this));
    tab2->layout()->addWidget(routeOutputTable/*,BorderLayout.CENTER*/);
    tab2->setVisible(true);
    //tabbedPane.addTab(tr("Actions (output)"), NULL, tab2, tr("Select Actions to include for this LRoute"));
    tabbedPane->addTab(tab2, tr("Actions (output)"));
    tab2->setToolTip(tr("Select Actions to include for this LRoute"));

    //////////////////////////////////// Tab 3 /////////////////////////////
    QWidget* tab3 = new QWidget();
    tab3->setLayout(new QVBoxLayout(tab3/*, BoxLayout.Y_AXIS*/));
    tab3->layout()->addWidget(new QLabel(tr("Select the Input Trigger states for this LRoute")));
    _inputAllButton = new QRadioButton(tr("All")/*,true*/);
    _inputAllButton->setChecked(true);
    QRadioButton* includedInputButton = new QRadioButton(tr("Included")/*,false*/);
    includedInputButton->setChecked(false);
    tab3->layout()->addWidget(makeShowButtons(_inputAllButton, includedInputButton, NULL, "Show"));
//    _inputAllButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                if (!_showAllInput) {
//                    _showAllInput = true;
//                    _inputModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(_inputAllButton, SIGNAL(clicked()), this, SLOT(inputAllButtonPressed()));
//    includedInputButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of included Turnouts only, if needed
//                if (_showAllInput) {
//                    _showAllInput = false;
//                    initializeIncludedInputList();
//                    _inputModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(includedInputButton, SIGNAL(clicked()), this, SLOT(includedInputButtonPressed()));
    tab3->layout()->addWidget(new QLabel(tr("PickInput")));

    _inputModel = new RouteInputModel(this);
    JTable* routeInputTable = new JTable();
    routeInputTable->setModel(_inputModel);
    routeInputTable->resizeColumnsToContents();
    //ROW_HEIGHT = routeInputTable.getRowHeight();
    //_inputScrollPane = makeColumns(routeInputTable, _testStateCombo, true);
    routeInputTable->setItemDelegateForColumn(RouteInputModel::STATE_COLUMN, new LComboBoxDelegate(_inputModel, this));
    // TODO: add _testStateCombo
    tab3->layout()->addWidget(routeInputTable/*,BorderLayout.CENTER*/);
    tab3->setVisible(true);
    //tabbedPane.addTab(tr("TriggerTab"), NULL, tab3, tr("TriggerTabHint"));
    tabbedPane->addTab(tab3, tr("Triggers/Controls (input)"));
    tab3->setToolTip(tr("Select triggers to include for this LRoute"));

    ////////////////////// Tab 4 /////////////////
    QWidget* tab4 = new QWidget();
    tab4->setLayout(new QVBoxLayout(tab4/*, BoxLayout.Y_AXIS*/));
    tab4->layout()->addWidget(new QLabel(tr("Additional LRoute Actions")));
    // Enter filenames for sound, script
    QWidget* p25 = new QWidget();
    p25->setLayout(new QHBoxLayout());
    p25->layout()->addWidget(new QLabel(tr("Play sound file:")));
    QPushButton* ss = new QPushButton(tr("Set"));
//    ss.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setSoundPressed();
//        }
//    });
    p25->layout()->addWidget(ss);
    p25->layout()->addWidget(soundFile);
    tab4->layout()->addWidget(p25);

    p25 = new QWidget();
    p25->setLayout(new QHBoxLayout());
    p25->layout()->addWidget(new QLabel(tr("RunScript")));
    ss = new QPushButton(tr("Set"));
//    ss.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setScriptPressed();
//        }
//    });
    p25->layout()->addWidget(ss);
    p25->layout()->addWidget(scriptFile);
    tab4->layout()->addWidget(p25);

    p25 = new QWidget();
    p25->setLayout(new QHBoxLayout());
    p25->layout()->addWidget(new QLabel(tr("Set Locks")));
    _lockCheckBox = new QCheckBox(tr("Lock")/*,true*/);
    _lockCheckBox->setChecked(true);
//    _lockCheckBox.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                _lock =_lockCheckBox.isSelected();
//            }
//        });
    p25->layout()->addWidget(_lockCheckBox);
    tab4->layout()->addWidget(p25);

    _alignAllButton = new QRadioButton(tr("All")/*,true*/);
    _alignAllButton->setChecked(true);
    QRadioButton* includedAlignButton = new QRadioButton(tr("Included")/*,false*/);
    includedAlignButton->setChecked(false);
    tab4->layout()->addWidget(makeShowButtons(_alignAllButton, includedAlignButton, NULL, "Show"));
//    _alignAllButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of all Turnouts, if needed
//                if (!_showAllAlign) {
//                    _showAllAlign = true;
//                    _alignModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(_alignAllButton, SIGNAL(clicked()), this, SLOT(alignAllButtonPressed()));
//    includedAlignButton.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                // Setup for display of included Turnouts only, if needed
//                if (_showAllAlign) {
//                    _showAllAlign = false;
//                    initializeIncludedAlignList();
//                    _alignModel.fireTableDataChanged();
//                }
//            }
//        });
    connect(includedAlignButton, SIGNAL(clicked()), this, SLOT(includedAlignButtonPressed()));
    tab4->layout()->addWidget(new QLabel(tr("PickAlign")));
    _alignModel = new AlignmentModel(this);
    JTable* alignTable = new JTable();
    alignTable->setModel(_alignModel);
    alignTable->resizeColumnsToContents();
    alignTable->setItemDelegateForColumn(RouteInputModel::STATE_COLUMN, new LComboBoxDelegate(_alignModel, this));

    _alignCombo = new QComboBox();
    for (int i=0; i<ALIGNMENT_STATES.length(); i++) {
        _alignCombo->addItem(ALIGNMENT_STATES.at(i));
    }
    //JScrollPane alignScrollPane = makeColumns(alignTable, _alignCombo, false);
    //alignTable.setPreferredScrollableViewportSize(new java.awt.Dimension(250,200));
    _alignCombo = new QComboBox();
    for (int i=0; i<ALIGNMENT_STATES.length(); i++) {
        _alignCombo->addItem(ALIGNMENT_STATES.at(i));
    }
    tab4->layout()->addWidget(alignTable/*,BorderLayout.CENTER*/);
    tab4->setVisible(true);
    //tabbedPane.addTab(tr("MiscTab"), NULL, tab4, tr("MiscTabHint"));
    tabbedPane->addTab(tab4, tr("Alignment/Locks/etc"));
    tab4->setToolTip(tr("elect script and sound files, alignment sensors, other parameters"));

    if(_addFrame->centralWidget() == NULL)
    {
     QWidget* centralWidget = new QWidget();
     centralWidget->setLayout(new QVBoxLayout);
     _addFrame->setCentralWidget(centralWidget);
    }
    QWidget* contentPane = _addFrame->centralWidget();
    //tabbedPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

    ///////////////////////////////////
    QWidget* pt = new QWidget();
    pt->setLayout(new QVBoxLayout());
    pt->layout()->addWidget(tabbedPane);
    contentPane->layout()->addWidget(pt);

    // set listener for window closing
    //    _addFrame.addWindowListener(new java.awt.event.WindowAdapter() {
    //            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
    //                // remind to save, if Route was created or edited
    //                if (routeDirty) {
    //                    InstanceManager.getDefault(jmri.UserPreferencesManager.class).
    //                        showInfoMessage("Reminder","Remember to save your LRoute information.",getClassName(), "remindSaveRoute");
    //                    routeDirty = false;
    //                }
    //                clearPage();
    //                _addFrame.setVisible(false);
    //                _inputModel.dispose();
    //                _outputModel.dispose();
    //                routeDirty = false;
    //            }
    //        });
    _addFrame->addWindowListener(addFrameWindowListener = new AddFrameWindowListener(this));
    _addFrame->pack();
#if 1
    //_inputAllButton.doClick();
    inputAllButtonPressed();
    //_outputAllButton.doClick();
    outputAllButtonPressed();
    //_alignAllButton.doClick();
    alignAllButtonPressed();
    //_newRouteButton.doClick();
    newRoutePressed();
    if (_initialize)
    {
     //_initializeButton.doClick();
     initializePressed();
    }
#endif
  }
 else
 {
  _addFrame->setVisible(true);
 }
}   // addPressed
AddFrameWindowListener::AddFrameWindowListener(LRouteTableAction *self)
{
 this->self = self;
}
void AddFrameWindowListener::windowClosing(QCloseEvent */*e*/)
{
 // remind to save, if Route was created or edited
 if (self->routeDirty)
 {
  ((UserPreferencesManager*)  InstanceManager::getDefault("UserPreferencesManager"))->
        showInfoMessage("Reminder","Remember to save your LRoute information.",self->getClassName(), "remindSaveRoute");
  self->routeDirty = false;
 }
 self->clearPage();
 self->_inputModel->dispose();
 self->_outputModel->dispose();
 self-> routeDirty = false;
}

/*
* Utility for addPressed
*/
QFrame*  LRouteTableAction::makeShowButtons(QRadioButton* allButton, QRadioButton* includeButton,
                   QRadioButton* extraButton, QString msg)
{
QFrame* panel = new QFrame();
panel->setLayout(new QHBoxLayout());
panel->layout()->addWidget(new QLabel(msg));
panel->layout()->addWidget(allButton);
panel->layout()->addWidget(includeButton);
QButtonGroup* selGroup = new QButtonGroup();
selGroup->addButton(allButton);
selGroup->addButton(includeButton);
if (extraButton!=NULL) {
    panel->layout()->addWidget(extraButton);
    selGroup->addButton(extraButton);
}
return panel;
}
void LRouteTableAction::includedInputButtonPressed()
{
 // Setup for display of included Turnouts only, if needed
 if (_showAllInput)
 {
  _showAllInput = false;
  initializeIncludedInputList();
  _inputModel->fireTableDataChanged();
 }
}
void LRouteTableAction::outputAllButtonPressed()
{
 //Setup for display of all Turnouts, if needed
 if (!_showAllOutput)
 {
  _showAllOutput = true;
  _outputModel->fireTableDataChanged();
 }
}
void LRouteTableAction::alignAllButtonPressed()
{
 // Setup for display of all Turnouts, if needed
 if (!_showAllAlign)
 {
  _showAllAlign = true;
  _alignModel->fireTableDataChanged();
 }
}
void LRouteTableAction::includedAlignButtonPressed()
{
 // Setup for display of included Turnouts only, if needed
 if (_showAllAlign)
 {
  _showAllAlign = false;
  initializeIncludedAlignList();
  _alignModel->fireTableDataChanged();
 }
}
void LRouteTableAction::includedOutputButtonPressed()
{
 // Setup for display of included Turnouts only, if needed
 if (_showAllOutput)
 {
    _showAllOutput = false;
    initializeIncludedOutputList();
    _outputModel->fireTableDataChanged();
 }
}
#if 0
/*
* Utility for addPressed
*/
JScrollPane makeColumns(JTable table, JComboBox box, boolean specialBox) {
table.setRowSelectionAllowed(false);
//table.setPreferredScrollableViewportSize(new java.awt.Dimension(250,450));
TableColumnModel columnModel = table.getColumnModel();

TableColumn sNameColumnT = columnModel.getColumn(RouteElementModel.SNAME_COLUMN);
sNameColumnT.setResizable(true);
sNameColumnT.setMinWidth(75);
//sNameColumnT.setMaxWidth(110);

TableColumn uNameColumnT = columnModel.getColumn(RouteElementModel.UNAME_COLUMN);
uNameColumnT.setResizable(true);
uNameColumnT.setMinWidth(75);
//uNameColumnT.setMaxWidth(260);

TableColumn typeColumnT = columnModel.getColumn(RouteElementModel.TYPE_COLUMN);
typeColumnT.setResizable(true);
typeColumnT.setMinWidth(50);
//typeColumnT.setMaxWidth(110);

TableColumn includeColumnT = columnModel.getColumn(RouteElementModel.INCLUDE_COLUMN);
includeColumnT.setResizable(false);
includeColumnT.setMinWidth(30);
includeColumnT.setMaxWidth(60);

TableColumn stateColumnT = columnModel.getColumn(RouteElementModel.STATE_COLUMN);
if (specialBox) {
    box = new JComboBox();
    stateColumnT.setCellEditor(new ComboBoxCellEditor(box));
} else {
    stateColumnT.setCellEditor(new DefaultCellEditor(box));
}
stateColumnT.setResizable(false);
stateColumnT.setMinWidth(75);
//stateColumnT.setMaxWidth(1310);

return new JScrollPane(table);
}
#endif
/**
* Initialize list of included input elements
*/
void LRouteTableAction::initializeIncludedInputList()
{
 _includedInputList = new QList <LRouteInputElement*> ();
 for (int i=0; i<_inputList->size(); i++)
 {
  if (_inputList->at(i)->isIncluded())
  {
   _includedInputList->append(_inputList->at(i));
  }
 }
}
/**
* Initialize list of included input elements
*/
void LRouteTableAction::initializeIncludedOutputList()
{
 _includedOutputList = new QList <LRouteOutputElement*> ();
 for (int i=0; i<_outputList->size(); i++)
 {
  if (_outputList->at(i)->isIncluded())
  {
   _includedOutputList->append(_outputList->at(i));
  }
 }
}
/**
* Initialize list of included alignment sensors
*/
void  LRouteTableAction::initializeIncludedAlignList()
{
 _includedAlignList = new QList <LAlignElement*> ();
 for (int i=0; i<_alignList->size(); i++)
 {
  if (_alignList->at(i)->isIncluded())
  {
   _includedAlignList->append(_alignList->at(i));
  }
 }
}

QList <LRouteOutputElement*>* LRouteTableAction::makeTurnoutLockList()
{
 QList <LRouteOutputElement*>* list = new QList <LRouteOutputElement*>();
 for (int i=0; i<_outputList->size(); i++)
 {
  if (_outputList->at(i)->isIncluded())
  {
   LRouteOutputElement* elt = _outputList->at(i);
   if ((elt->getType() == TURNOUT_TYPE) && (elt->getState() != Route::TOGGLE))
   {
    list->append(elt);
   }
  }
 }
 return list;
}

void LRouteTableAction::showMessage(QString msg) {

//javax.swing.JOptionPane.showMessageDialog(
//        _addFrame, tr(msg), rbx .getString("Warn"),
//        javax.swing.JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(_addFrame, tr("Warning"), msg);
}

bool LRouteTableAction::checkNewNamesOK()
{
 // Get system name and user name
 QString sName = _systemName->text();
 if (sName.length()==0 || sName==(LOGIX_SYS_NAME))
 {
    showMessage(tr("Please enter a system name and user name."));
    return false;
 }
 if (!sName.startsWith(LOGIX_SYS_NAME)) {
    sName = LOGIX_SYS_NAME + sName;
 }
 // check if a Route with this system name already exists
 if (((DefaultLogixManager*)_logixManager)->getBySystemName(sName)!=NULL)
 {
    // Route already exists
    showMessage("A Logix with this system name already exists.");
    updateButton->setVisible(true);
    return false;
 }
 QString uName = _userName->text();
 // check if a Route with the same user name exists
 if (uName!=(""))
 {
    if (((DefaultLogixManager*)_logixManager)->getByUserName(uName)!=NULL) {
        // Route with this user name already exists
        showMessage("A Logix with this user name already exists.");
        updateButton->setVisible(true);
        return false;
    }
    else {
        return true;
    }
}
_systemName->setText(sName);
return true;
}


Logix* LRouteTableAction::checkNamesOK()
{
 // Get system name and user name
 QString sName = _systemName->text();
 if (sName.length()==0)
 {
  showMessage("EnterNames");
    return NULL;
 }
 Logix* logix = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
 if (!sName.startsWith(LOGIX_SYS_NAME))
 {
  sName = LOGIX_SYS_NAME + sName;
 }
 if (logix == NULL)
 {
  logix = (Logix*)((DefaultLogixManager*)_logixManager)->getBySystemName(sName);
 }
 else
 {
  return logix;
 }
 QString uName = _userName->text();
 if (uName.length()!=0)
 {
  logix = (Logix*)((DefaultLogixManager*)_logixManager)->getByUserName(uName);
  if (logix != NULL)
  {
   return logix;
  }
 }
 logix = ((DefaultLogixManager*)_logixManager)->createNewLogix(sName, uName);
 if (logix==NULL)
 {
  // should never get here
  log->error("Unknown failure to create Route with System Name: "+sName);
 }
 return logix;
}
#if 0

/**
* Set the sound file
*/
void setSoundPressed() {
if (soundChooser == NULL) {
    soundChooser = new JFileChooser(FileUtil.getUserFilesPath());
    soundChooser.setFileFilter(new jmri.util.NoArchiveFileFilter());
}
soundChooser.rescanCurrentDirectory();
int retVal = soundChooser.showOpenDialog(NULL);
// handle selection or cancel
if (retVal == JFileChooser.APPROVE_OPTION) {
    try {
        soundFile.setText(soundChooser.getSelectedFile().getCanonicalPath());
    } catch (java.io.IOException e) {
        log->error("exception setting sound file: "+e);
    }
}
}

JFileChooser scriptChooser = NULL;

/**
* Set the script file
*/
void setScriptPressed() {
if (scriptChooser == NULL) {
    scriptChooser = jmri.jmrit.XmlFile.userFileChooser("Python script files", "py");
}
scriptChooser.rescanCurrentDirectory();
int retVal = scriptChooser.showOpenDialog(NULL);
// handle selection or cancel
if (retVal == JFileChooser.APPROVE_OPTION) {
    try {
        scriptFile.setText(scriptChooser.getSelectedFile().getCanonicalPath());
    } catch (java.io.IOException e) {
        log->error("exception setting script file: "+e);
    }
}
}
#endif
/**
* Responds to the Add Route button
*/
void LRouteTableAction::createPressed(ActionEvent* /*e*/)
{
 if (!checkNewNamesOK())
 {
    return;
 }
 updatePressed();
}

/**
* Responds to the Delete button
*/
void LRouteTableAction::deletePressed(ActionEvent* /*e*/)
{
 Logix* l = checkNamesOK();
 if (l != NULL) {
    ((DefaultLogix*)l)->deActivateLogix();
    // delete the Logix and all its Conditionals
    ((DefaultLogixManager*)_logixManager)->deleteLogix(l);
 }
 finishUpdate();
}

/**
* Responds to the Update button - update to Route Table
*/
void LRouteTableAction::updatePressed()
{
 Logix* logix = checkNamesOK();
 if (logix == NULL)
 {
  log->error("No Logix found!");
  return;
 }
 QString sName = ((DefaultLogix*)logix)->getSystemName();
 // Check if the User Name has been changed
 QString uName = _userName->text();
 ((DefaultLogix*)logix)->setUserName(uName);

 initializeIncludedInputList();
 initializeIncludedOutputList();
 initializeIncludedAlignList();
 if(log->isDebugEnabled())
 {
  log->debug("updatePressed: _includedInputList.size()= "+QString::number(_includedInputList->size())+
          ", _includedOutputList.size()= "+QString::number(_includedOutputList->size())+
          ", _includedAlignList.size()= "+QString::number(_includedAlignList->size()));
 }
 ////// Construct output actions for trigger conditionals ///////////
 QList <ConditionalAction*>* actionList = new QList<ConditionalAction*>();
 for (int i=0; i<_includedOutputList->size(); i++)
 {
  LRouteOutputElement* elt = _includedOutputList->at(i);
  QString name = elt->getUserName();
  if (name == NULL || name.length() == 0)
  {
   name = elt->getSysName();
  }
  int state = elt->getState();    // actionData
  int actionType = 0;
  QString params = "";
  switch (elt->getType())
  {
        case SENSOR_TYPE:
            actionType = Conditional::ACTION_SET_SENSOR;
            break;
        case TURNOUT_TYPE:
            actionType = Conditional::ACTION_SET_TURNOUT;
            break;
        case LIGHT_TYPE:
            actionType = Conditional::ACTION_SET_LIGHT;
            break;
        case SIGNAL_TYPE:
            actionType = Conditional::ACTION_SET_SIGNAL_APPEARANCE;
            if (state > OFFSET) {
                actionType = state & ~OFFSET;
            }
            break;
        default:
            log->debug("updatePressed: Unknown action type "+QString::number(elt->getType()));
   }
   actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                          actionType, name, state, params));
  }
  QString file = scriptFile->text();
  if (file.length() > 0) {
   actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                          Conditional::ACTION_RUN_SCRIPT, "", -1, file));
 }
 file = soundFile->text();
 if (file.length() > 0)
 {
  actionList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                          Conditional::ACTION_PLAY_SOUND, "", -1, file));
 }
 QList <ConditionalAction*>* onChangeList = cloneActionList(actionList, Conditional::ACTION_OPTION_ON_CHANGE);

 /////// Construct 'AND' clause from 'VETO' controls ////////
 QList <ConditionalVariable*>* vetoList = new QList<ConditionalVariable*>();
 if (!_initialize)
 {
  for (int i=0; i<_includedInputList->size(); i++)
  {
   LRouteInputElement* elt = _includedInputList->at(i);
   QString name = elt->getUserName();
   if (name == NULL || name.length() == 0)
   {
    name = elt->getSysName();
   }
   //int opern = newRouteType ? Conditional::OPERATOR_AND : Conditional::OPERATOR_OR;
   int opern = Conditional::OPERATOR_AND;
   if (i==0)
   {
    opern = Conditional::OPERATOR_NONE;
   }
   int state = elt->getState();
   if (VETO < state)
   {
     vetoList->append(new ConditionalVariable(true, opern, (state&~VETO), name, _newRouteType));
   }
  }
 }

 ///////////////// Make Trigger Conditional Controls /////////////////
 QList <ConditionalVariable*>* oneTriggerList = new QList<ConditionalVariable*>();
 QList <ConditionalVariable*>* twoTriggerList = new QList<ConditionalVariable*>();
 if (!_initialize)
 {
  for (int i=0; i<_includedInputList->size(); i++)
  {
        LRouteInputElement* elt = _includedInputList->at(i);
        QString name = elt->getUserName();
        if (name == NULL || name.length() == 0) {
             name = elt->getSysName();
        }
        int opern = _newRouteType ? Conditional::OPERATOR_OR : Conditional::OPERATOR_AND;
        if (i == 0) {
            opern = Conditional::OPERATOR_NONE;
        }
        int type = elt->getState();
        if (VETO > type) {
            if (Route::ONCHANGE == type) {
                switch (elt->getType()) {
                    case SENSOR_TYPE:
                        type = Conditional::TYPE_SENSOR_ACTIVE;
                        break;
                    case TURNOUT_TYPE:
                        type = Conditional::TYPE_TURNOUT_CLOSED;
                        break;
                    case LIGHT_TYPE:
                        type = Conditional::TYPE_LIGHT_ON;
                        break;
                    case SIGNAL_TYPE:
                        type = Conditional::TYPE_SIGNAL_HEAD_LIT;
                        break;
                    default:
                        log->debug("updatePressed: Unknown state variable type "+QString::number(elt->getType()));
                }
                twoTriggerList->append(new ConditionalVariable(false, opern, type, name, true));
            } else {
                oneTriggerList->append(new ConditionalVariable(false, opern, type, name, true));
            }
        }
  }
  if (actionList->size() == 0)
  {
//        javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, tr("noAction"),
//                 rbx .getString("addErr"), javax.swing.JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(_addFrame, tr("LRoute not possible"), tr("No unvetoed Action items are selected. Go to 'Actions' Tab."));
        return;
  }
 }
 else
 {
  oneTriggerList->append(new ConditionalVariable(false, Conditional::OPERATOR_NONE,
                                               Conditional::TYPE_NONE, LOGIX_INITIALIZER, true));
 }
 if(log->isDebugEnabled())
 {
    log->debug("actionList.size()= "+QString::number(actionList->size())+", oneTriggerList.size()= "+QString::number(oneTriggerList->size())+
          ", twoTriggerList.size()= "+QString::number(twoTriggerList->size())+
          ", onChangeList.size()= "+QString::number(onChangeList->size())+", vetoList.size()= "+QString::number(vetoList->size()));
 }
 ((DefaultLogix*)logix)->deActivateLogix();

 // remove old Conditionals for actions (ver 2.5.2 only -remove a bad idea)
 QByteArray ch = sName.toLatin1();
 int hash= 0;
 for (int i=0; i<ch.length(); i++)
 {
    hash += ch.at(i);
 }
 QString cSystemName = CONDITIONAL_SYS_PREFIX+"T"+hash;
 removeConditionals(cSystemName, logix);
 cSystemName = CONDITIONAL_SYS_PREFIX+"F"+hash;
 removeConditionals(cSystemName, logix);
 cSystemName = CONDITIONAL_SYS_PREFIX+"A"+hash;
 removeConditionals(cSystemName, logix);
 cSystemName = CONDITIONAL_SYS_PREFIX+"L"+hash;
 removeConditionals(cSystemName, logix);
 int n=0;
 do {
    n++;
    cSystemName = sName+n+"A";
 } while (removeConditionals(cSystemName, logix));
 n = 0;
 do {
    n++;
    cSystemName = sName+n+"T";
 } while (removeConditionals(cSystemName, logix));
 cSystemName = sName+"L";
 removeConditionals(cSystemName, logix);

 //String cUserName = NULL;
 int numConds = 1;
 if (_newRouteType) {
    numConds = makeRouteConditional(numConds, /*false,*/ actionList, oneTriggerList,
                                       vetoList, logix, sName, uName, "T");
    if (!_initialize && twoTriggerList->size()>0) {
        numConds = makeRouteConditional(numConds, /*true, actionList,*/ onChangeList, twoTriggerList,
                                           NULL, logix, sName, uName, "T");
    }
 }
 else
 {
    for (int i=0; i<oneTriggerList->size(); i++) {
        QList<ConditionalVariable*>* vList = new QList<ConditionalVariable*>();
        vList->append(oneTriggerList->at(i));
        numConds = makeRouteConditional(numConds, /*false,*/ actionList, vList,
                                           vetoList, logix, sName, uName, "T");
    }
    for (int i=0; i<twoTriggerList->size(); i++) {
        QList<ConditionalVariable*>* vList = new QList<ConditionalVariable*>();
        vList->append(twoTriggerList->at(i));
        numConds = makeRouteConditional(numConds, /*true, actionList,*/ onChangeList, vList,
                                           vetoList, logix, sName, uName, "T");
    }
 }
 if (numConds == 1) {
//    javax.swing.JOptionPane.showMessageDialog(
//            _addFrame, tr("noVars"),
//             rbx .getString("addErr"), javax.swing.JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(_addFrame, tr("Error"), tr("No control items are selected. Go to 'Triggers' Tab."));
    return;
 }

 ///////////////// Make Alignment Conditionals //////////////////////////
 numConds = 1;
 for (int i=0; i<_includedAlignList->size(); i++)
 {
    QList<ConditionalVariable*>* vList = new QList<ConditionalVariable*>();
    QList<ConditionalAction*>* aList = new QList<ConditionalAction*>();
    LAlignElement* sensor = _includedAlignList->at(i);
    QString name = sensor->getUserName();
    if (name == NULL || name.length() == 0) {
         name = sensor->getSysName();
    }
    aList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                                    Conditional::ACTION_SET_SENSOR, name, Sensor::ACTIVE, ""));
    aList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE,
                                    Conditional::ACTION_SET_SENSOR, name, Sensor::INACTIVE, ""));
    int alignType = sensor->getState();
    for (int k=0; k<_includedOutputList->size(); k++)
    {
        LRouteOutputElement* elt = _includedOutputList->at(k);
        int varType = 0;
        bool add = (ALL_TYPE == alignType);
        switch (elt->getType()) {
            case SENSOR_TYPE:
                if (alignType == SENSOR_TYPE) {
                    add = true;
                }
                switch (elt->getState()){
                    case Sensor::INACTIVE:
                        varType = Conditional::TYPE_SENSOR_INACTIVE;
                        break;
                    case Sensor::ACTIVE:
                        varType = Conditional::TYPE_SENSOR_ACTIVE;
                        break;
                    case Route::TOGGLE:
                        add = false;
                        break;
                }
                break;
            case TURNOUT_TYPE:
                if (alignType == TURNOUT_TYPE) {
                    add = true;
                }
                switch (elt->getState()){
                    case Turnout::CLOSED:
                        varType = Conditional::TYPE_TURNOUT_CLOSED;
                        break;
                    case Turnout::THROWN:
                        varType = Conditional::TYPE_TURNOUT_THROWN;
                        break;
                    case Route::TOGGLE:
                        add = false;
                        break;
                }
                break;
            case LIGHT_TYPE:
                if (alignType == LIGHT_TYPE) {
                    add = true;
                }
                switch (elt->getState()){
                    case Light::ON:
                        varType = Conditional::TYPE_LIGHT_ON;
                        break;
                    case Light::OFF:
                        varType = Conditional::TYPE_LIGHT_OFF;
                        break;
                    case Route::TOGGLE:
                        add = false;
                        break;
                }
                break;
            case SIGNAL_TYPE:
                if (alignType == SIGNAL_TYPE) {
                    add = true;
                }
                switch (elt->getState()){
                    case SignalHead::DARK:
                        varType = Conditional::TYPE_SIGNAL_HEAD_DARK;
                        break;
                    case SignalHead::RED:
                        varType = Conditional::TYPE_SIGNAL_HEAD_RED;
                        break;
                    case SignalHead::FLASHRED:
                        varType = Conditional::TYPE_SIGNAL_HEAD_FLASHRED;
                        break;
                    case SignalHead::YELLOW:
                        varType = Conditional::TYPE_SIGNAL_HEAD_YELLOW;
                        break;
                    case SignalHead::FLASHYELLOW:
                        varType = Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW;
                        break;
                    case SignalHead::GREEN:
                        varType = Conditional::TYPE_SIGNAL_HEAD_GREEN;
                        break;
                    case SignalHead::FLASHGREEN:
                        varType = Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN;
                        break;
                default:
                    if(elt->getState() ==  SET_SIGNAL_HELD)
                        varType = Conditional::TYPE_SIGNAL_HEAD_HELD;
//                        break;
                    if(elt->getState() ==  CLEAR_SIGNAL_HELD)
                        add = false;    // don't know how to test for this
//                        break;
                    if(elt->getState() ==  SET_SIGNAL_DARK)
                        varType = Conditional::TYPE_SIGNAL_HEAD_DARK;
//                        break;
                    if(elt->getState() ==   SET_SIGNAL_LIT)
                        varType = Conditional::TYPE_SIGNAL_HEAD_LIT;
                        break;
                }
                break;
            default:
                log->debug("updatePressed: Unknown Alignment state variable type "+QString::number(elt->getType()));
        }
        if (add && !_initialize) {
            QString eltName = elt->getUserName();
            if (eltName == NULL || eltName.length() == 0) {
                 eltName = elt->getSysName();
            }
            vList->append(new ConditionalVariable(false, Conditional::OPERATOR_AND,
                          varType, eltName, true));
        }
    }
    if (vList->size() > 0) {
        numConds = makeAlignConditional(numConds, aList, vList,logix, sName, uName);
    } else {
//        javax.swing.JOptionPane.showMessageDialog(
//                _addFrame, java.text.MessageFormat.format(tr("NoAlign"),
//                    new Object [] {name, sensor.getAlignType()}),
//                 rbx .getString("Warn"), javax.swing.JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(_addFrame, tr("Warning"), tr("There are no outputs selected for alignment sensor %1 to indicate %2.").arg(name).arg(sensor->getAlignType()));
    }
   }
   ///////////////// Make Lock Conditional //////////////////////////
   numConds = 1;
   if (_lock)
   {
    QList<ConditionalAction*>* aList = new QList<ConditionalAction*>();
    for (int k=0; k<_includedOutputList->size(); k++)
    {
     LRouteOutputElement* elt = _includedOutputList->at(k);
        if (elt->getType() != TURNOUT_TYPE) {
            continue;
        }
        if (elt->getState() == Route::TOGGLE) {
            continue;
        }
        QString eltName = elt->getUserName();
        if (eltName == NULL || eltName.length() == 0) {
             eltName = elt->getSysName();
        }
        aList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE,
                                             Conditional::ACTION_LOCK_TURNOUT,
                                             eltName, Turnout::LOCKED, ""));
        aList->append(new DefaultConditionalAction(Conditional::ACTION_OPTION_ON_CHANGE_TO_FALSE,
                                             Conditional::ACTION_LOCK_TURNOUT,
                                             eltName, Turnout::UNLOCKED, ""));
  }
  numConds = makeRouteConditional(numConds, /*false,*/ aList, oneTriggerList,
                                       vetoList, logix, sName, uName, "L");
 }
 log->debug("Conditionals added= "+QString::number(((DefaultLogix*)logix)->getNumConditionals()));
 for (int i=0; i<((DefaultLogix*)logix)->getNumConditionals(); i++)
 {
  log->debug("Conditional SysName= \""+((DefaultLogix*)logix)->getConditionalByNumberOrder(i)+"\"");
 }
 ((DefaultLogix*)logix)->activateLogix();
 log->debug("Conditionals added= "+QString::number(((DefaultLogix*)logix)->getNumConditionals()));
 for (int i=0; i<((DefaultLogix*)logix)->getNumConditionals(); i++)
 {
  log->debug("Conditional SysName= \""+((DefaultLogix*)logix)->getConditionalByNumberOrder(i)+"\"");
 }
 finishUpdate();
} //updatePressed


bool LRouteTableAction::removeConditionals(QString cSystemName, Logix* logix)
{
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->getBySystemName(cSystemName);
 if (c != NULL)
 {
    ((DefaultLogix*)logix)->deleteConditional(cSystemName);
    ((DefaultConditionalManager*)_conditionalManager)->deleteConditional(c);
    return true;
 }
 return false;
}

int LRouteTableAction::makeRouteConditional(int numConds, /*boolean onChange,*/ QList<ConditionalAction*>* actionList, QList<ConditionalVariable*>* triggerList, QList<ConditionalVariable*>* vetoList, Logix* logix, QString sName, QString uName, QString type)
{
 if(log->isDebugEnabled())
 {
  log->debug("makeRouteConditional: numConds= "+QString::number(numConds)+", triggerList.size()= "+QString::number(triggerList->size()));
 }
 if (triggerList->size()==0 && (vetoList==NULL || vetoList->size()==0)) {
    return numConds;
 }
 QString antecedent;
 QList <ConditionalVariable*>* varList = new QList<ConditionalVariable*>();

 int tSize = triggerList->size();
 if (tSize > 0)
 {
    if (tSize > 1) {
        antecedent.append("(");
    }
    antecedent.append("R1");
    for (int i=1; i<tSize; i++) {
        antecedent.append(" OR R"+(i+1));
    }
    if (tSize > 1) {
        antecedent.append(")");
    }
    for ( int i=0; i<triggerList->size(); i++) {
        //varList.add(cloneVariable(triggerList.get(i)));
        varList->append(triggerList->at(i));
    }
 }
 else
 {
 }
 if (vetoList!=NULL && vetoList->size()>0)
 {
    int vSize = vetoList->size();
    if (tSize > 0) {
        antecedent.append(" AND ");
    }
    if (vSize > 1) {
        antecedent.append("(");
    }
    antecedent.append("NOT R"+(1+tSize));
    for (int i=1; i<vSize; i++) {
        antecedent.append(" AND NOT R"+(i+1+tSize));
    }
    if (vSize > 1) {
        antecedent.append(")");
    }
    for ( int i=0; i<vetoList->size(); i++) {
        //varList.add(cloneVariable(vetoList.get(i)));
        varList->append(vetoList->at(i));
    }
 }
 QString cSystemName = sName+numConds+type;
 QString cUserName = CONDITIONAL_USER_PREFIX+numConds+"C "+uName;
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->createNewConditional(cSystemName, cUserName);
 ((DefaultConditional*)c)->setStateVariables(varList);
 //int option = onChange ? Conditional::ACTION_OPTION_ON_CHANGE :  Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE;
 //c.setAction(cloneActionList(actionList, option));
 ((DefaultConditional*)c)->setAction(actionList);
 int logicType = _newRouteType ? Conditional::MIXED : Conditional::ALL_AND;
 ((DefaultConditional*)c)->setLogicType(logicType, antecedent);
 ((DefaultLogix*)logix)->addConditional(cSystemName, 0);
 log->debug("Conditional added: SysName= \""+cSystemName+"\"");
 ((DefaultConditional*)c)->calculate(true, NULL);
 numConds++;

 return numConds;
}

int LRouteTableAction::makeAlignConditional(int numConds, QList<ConditionalAction*>* actionList,
                        QList<ConditionalVariable*>* triggerList,
                        Logix* logix, QString sName, QString uName)
{
 if (triggerList->size() == 0)
 {
    return numConds;
 }
 QString cSystemName = sName+numConds+"A";
 QString cUserName = CONDITIONAL_USER_PREFIX+numConds+"A "+uName;
 Conditional* c = ((DefaultConditionalManager*)_conditionalManager)->createNewConditional(cSystemName, cUserName);
 ((DefaultConditional*)c)->setStateVariables(triggerList);
 //c.setAction(cloneActionList(actionList, Conditional::ACTION_OPTION_ON_CHANGE_TO_TRUE));
 ((DefaultConditional*)c)->setAction(actionList);
 ((DefaultConditional*)c)->setLogicType(Conditional::ALL_AND, "");
 ((DefaultLogix*)logix)->addConditional(cSystemName, 0);
 log->debug("Conditional added: SysName= \""+cSystemName+"\"");
 ((DefaultConditional*)c)->calculate(true, NULL);
 numConds++;
 return numConds;
}

QList<ConditionalAction*>* LRouteTableAction::cloneActionList(QList<ConditionalAction*>* actionList, int option)
{
 QList <ConditionalAction*>* list = new QList <ConditionalAction*> ();
 for (int i = 0; i<actionList->size(); i++)
 {
    ConditionalAction* action = actionList->at(i);
    ConditionalAction* clone = new DefaultConditionalAction();
    ((DefaultConditionalAction*)clone)->setType(((DefaultConditionalAction*)action)->getType());
    ((DefaultConditionalAction*)clone)->setOption(option);
    ((DefaultConditionalAction*)clone)->setDeviceName(((DefaultConditionalAction*)action)->getDeviceName());
   ((DefaultConditionalAction*) clone)->setActionData(((DefaultConditionalAction*)action)->getActionData());
    ((DefaultConditionalAction*)clone)->setActionString(((DefaultConditionalAction*)action)->getActionString());
    list->append(clone);
 }
 return list;
}

void LRouteTableAction::finishUpdate()
{
 routeDirty = true;
 clearPage();
}

void LRouteTableAction::clearPage() {
// move to show all turnouts if not there
cancelIncludedOnly();
deleteButton->setVisible(false);
cancelButton->setVisible(false);
updateButton->setVisible(false);
createButton->setVisible(false);
_systemName->setText("");
_userName->setText("");
soundFile->setText("");
scriptFile->setText("");
for (int i=_inputList->size()-1; i>=0; i--) {
    _inputList->at(i)->setIncluded(false);
}
for (int i=_outputList->size()-1; i>=0; i--) {
    _outputList->at(i)->setIncluded(false);
}
for (int i=_alignList->size()-1; i>=0; i--) {
    _alignList->at(i)->setIncluded(false);
 }
 _lock = false;
 _newRouteType = true;
 //_newRouteButton.doClick();
 newRoutePressed();
 _lockCheckBox->setChecked(_lock);
 _addFrame->setVisible(false);
}

/**
* Cancels included only option
*/
void LRouteTableAction::cancelIncludedOnly() {
if (!_showAllInput) {
    //_inputAllButton.doClick();
    inputAllButtonPressed();
}
if (!_showAllOutput) {
    //_outputAllButton.doClick();
    outputAllButtonPressed();
}
if (!_showAllAlign) {
    //_alignAllButton.doClick();
    alignAllButtonPressed();
}
}
void LRouteTableAction::inputAllButtonPressed()
{
    // Setup for display of all Turnouts, if needed
    if (!_showAllInput) {
        _showAllInput = true;
        _inputModel->fireTableDataChanged();
    }
}
/*private*/ QStringList LRouteTableAction::getInputComboBoxItems(int type) {
switch (type) {
    case SENSOR_TYPE:
        return INPUT_SENSOR_STATES;
    case TURNOUT_TYPE:
        return INPUT_TURNOUT_STATES;
    case LIGHT_TYPE:
        return INPUT_LIGHT_STATES;
    case SIGNAL_TYPE:
        return INPUT_SIGNAL_STATES;
}
return QStringList();
}

/*private*/ QStringList LRouteTableAction::getOutputComboBoxItems(int type) {
switch (type) {
    case SENSOR_TYPE:
        return OUTPUT_SENSOR_STATES;
    case TURNOUT_TYPE:
        return OUTPUT_TURNOUT_STATES;
    case LIGHT_TYPE:
        return OUTPUT_LIGHT_STATES;
    case SIGNAL_TYPE:
        return OUTPUT_SIGNAL_STATES;
}
return QStringList();
}
#if 0
////////////////////////////// Internal Utility Classes ////////////////////////////////

/*public*/ class ComboBoxCellEditor extends DefaultCellEditor
{
ComboBoxCellEditor() {
    super(new JComboBox());
}
ComboBoxCellEditor(JComboBox comboBox) {
    super(comboBox);
}
/*public*/ Component getTableCellEditorComponent(JTable table, Object value,
                                 boolean isSelected, int row, int column)
{
    //RouteElementModel model = (RouteElementModel)((jmri.util.com.sun.TableSorter)table.getModel()).getTableModel();
    RouteElementModel model = (RouteElementModel)table.getModel();
    //ArrayList <RouteElement> elementList = NULL;
    //int type = 0;
    RouteElement elt = NULL;
    String[] items = NULL;
    if (model.isInput())
    {
        if (_showAllInput) {
            elt = _inputList.get(row);
        }
        else {
            elt = _includedInputList.get(row);
        }
        items = getInputComboBoxItems(elt.getType());
    } else {
        if (_showAllOutput) {
            elt = _outputList.get(row);
        }
        else {
            elt = _includedOutputList.get(row);
        }
        items = getOutputComboBoxItems(elt.getType());
    }
    JComboBox comboBox = (JComboBox)getComponent();
    comboBox.removeAllItems();
    for (int i=0; i<items.length; i++) {
        comboBox.addItem(items[i]);
    }
    return super.getTableCellEditorComponent(table, value, isSelected, row, column);
}
}
#endif
/**
* Base Table model for selecting Route elements
*/
///*public*/ abstract class RouteElementModel extends AbstractTableModel implements PropertyChangeListener
//{
RouteElementModel::RouteElementModel(LRouteTableAction *self)
{
    this->self = self;
    log = new Logger("RouteElementModel");
}
/*abstract*/ /*public*/ bool RouteElementModel::isInput(){return false;}

///*public*/ Class<?> getColumnClass(int c) {
//    if (c == INCLUDE_COLUMN) {
//        return Boolean.class;
//    }
//    else {
//        return String.class;
//    }
//}

/*public*/ int RouteElementModel::columnCount(const QModelIndex &/*parent*/) const{return 5;}

/*public*/ QVariant RouteElementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case SNAME_COLUMN:
            return tr("System Name");
        case UNAME_COLUMN:
            return tr("User Name");
        case TYPE_COLUMN:
            return tr("Type");
        case INCLUDE_COLUMN:
            return tr("Include");
    }
 }
 return QVariant();
}
/*public*/ Qt::ItemFlags RouteElementModel::flags(const QModelIndex &index) const
{
 int c = index.column();
 if(c==INCLUDE_COLUMN )
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
 if( c==STATE_COLUMN)
  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*public*/ void RouteElementModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("length"))
 {
  // a new NamedBean is available in the manager
  fireTableDataChanged();
 }
}

/*public*/ void RouteElementModel::dispose()
{
 ProxyTurnoutManager* mgr = (ProxyTurnoutManager* )InstanceManager::turnoutManagerInstance();
 disconnect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}
void RouteElementModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
}
//};

/**
* Table model for selecting input variables
*/
//class RouteInputModel extends RouteElementModel
//{
RouteInputModel::RouteInputModel(LRouteTableAction* self) : RouteElementModel(self)
{
}
/*public*/ bool RouteInputModel::isInput() {
    return true;
}
/*public*/ QVariant  RouteInputModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (section == STATE_COLUMN) {
        return tr("Set Trigger");
    }
    return RouteElementModel::headerData(section, orientation, role);
 }
 return QVariant();
}
/*public*/ int RouteInputModel::rowCount(const QModelIndex &/*parent*/) const
{
    if (self->_showAllInput)
        return self->_inputList->size();
    else
        return self->_includedInputList->size();
}
/*public*/ QVariant RouteInputModel::data(const QModelIndex &index, int role) const
{
 QList <LRouteInputElement*>* inputList = NULL;
 if (self->_showAllInput)
 {
  inputList = self->_inputList;
 }
 else
 {
  inputList = self->_includedInputList;
 }
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int r = index.row();
    // some error checking
    if (r >= inputList->size()){
        log->debug("row out of range");
        return QVariant();
    }
    switch (index.column()) {
        case SNAME_COLUMN:
            return inputList->at(r)->getSysName();
        case UNAME_COLUMN:
            return inputList->at(r)->getUserName();
        case TYPE_COLUMN:
            return inputList->at(r)->getTypeString();
//        case INCLUDE_COLUMN:
//        return inputList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
        case STATE_COLUMN:
            return inputList->at(r)->getTestState();
        default:
        return QVariant();
    }
 }
 else if(role == Qt::CheckStateRole)
 {
     if(index.column() == INCLUDE_COLUMN)
      return inputList->at(index.row())->isIncluded()?Qt::Checked:Qt::Unchecked;
 }
 return QVariant();
}
/*public*/ bool RouteInputModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 QList <LRouteInputElement*>* inputList = NULL;
 if (self->_showAllInput)
 {
  inputList = self->_inputList;
 }
 else
 {
  inputList = self->_includedInputList;
 }
 if(role == Qt::EditRole)
 {
  switch (index.column())
  {
//        case INCLUDE_COLUMN:
//        inputList->at(index.row())->setIncluded(value.toBool());
//            break;
        case STATE_COLUMN:
        inputList->at(index.row())->setTestState(value.toString());
            break;
  }
  return true;
 }
 else if(role == Qt::CheckStateRole)
 {
  if(index.column() == INCLUDE_COLUMN)
  {
   inputList->at(index.row())->setIncluded(value.toBool());
   return true;
  }
 }
 return false;
}
//};

/**
* Table model for selecting output variables
*/
//class RouteOutputModel extends RouteElementModel
//{
RouteOutputModelX::RouteOutputModelX(LRouteTableAction *self) : RouteElementModel(self)
{
}
/*public*/ bool RouteOutputModelX::isInput() {
    return false;
}
/*public*/ QVariant RouteOutputModelX::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (section == STATE_COLUMN) {
        return tr("Set Action");
    }
    return RouteElementModel::headerData(section,orientation, role);
 }
 return QVariant();
}
 /*public*/ int RouteOutputModelX::rowCount(const QModelIndex &/*parent*/) const
{
 if (self->_showAllOutput)
        return self->_outputList->size();
    else
        return self->_includedOutputList->size();
}
/*public*/ QVariant RouteOutputModelX::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int r = index.row();
  QList<LRouteOutputElement*>* outputList = NULL;
  if (self->_showAllOutput)
  {
   outputList = self->_outputList;
  }
  else
  {
   outputList = self->_includedOutputList;
  }
    // some error checking
    if (r >= outputList->size())
    {
        log->debug("row out of range");
        return QVariant();
    }
    switch (index.column())
    {
        case SNAME_COLUMN:  // slot number
            return outputList->at(r)->getSysName();
        case UNAME_COLUMN:  //
            return outputList->at(r)->getUserName();
        case INCLUDE_COLUMN:
            return outputList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
        case TYPE_COLUMN:
            return outputList->at(r)->getTypeString();
        case STATE_COLUMN:  //
            return outputList->at(r)->getSetToState();
        default:
        return QVariant();
  }
 }
 return QVariant();
}
/*public*/ bool  RouteOutputModelX::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int r = index.row();
  QList <LRouteOutputElement*>* outputList = NULL;
    if (self->_showAllOutput) {
        outputList = self->_outputList;
    }
    else {
        outputList = self->_includedOutputList;
    }
    switch (index.column()) {
        case INCLUDE_COLUMN:
            outputList->at(r)->setIncluded(value.toBool());
            break;
        case STATE_COLUMN:
            outputList->at(r)->setSetToState(value.toString());
            break;
    }
    return true;
 }
 return false;
}
//};

/**
* Table model for selecting output variables
*/
//class AlignmentModel extends RouteElementModel
//{
AlignmentModel::AlignmentModel(LRouteTableAction *self) : RouteElementModel(self)
{}
/*public*/ bool AlignmentModel::isInput() {
    return false;
}
/*public*/ QVariant AlignmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    if (section == STATE_COLUMN) {
        return tr("Alignment");
    }
    return RouteElementModel::headerData(section, orientation, role);
 }
 return QVariant();
}
/*public*/ int AlignmentModel::rowCount(const QModelIndex &/*parent*/) const
{
    if (self->_showAllAlign)
        return self->_alignList->size();
    else
        return self->_includedAlignList->size();
}
/*public*/ QVariant AlignmentModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int r = index.row();
  QList <LAlignElement*>* alignList = NULL;
  if (self->_showAllAlign) {
        alignList = self->_alignList;
    }
    else {
        alignList = self->_includedAlignList;
    }
    // some error checking
    if (r >= alignList->size()){
        log->debug("row out of range");
        return QVariant();
    }
    switch (index.column()) {
        case SNAME_COLUMN:  // slot number
            return alignList->at(r)->getSysName();
        case UNAME_COLUMN:  //
            return alignList->at(r)->getUserName();
        case INCLUDE_COLUMN:
            return alignList->at(r)->isIncluded()?Qt::Checked:Qt::Unchecked;
        case TYPE_COLUMN:
            return tr("Sensor");
        case STATE_COLUMN:  //
            return alignList->at(r)->getAlignType();
        default:
           break;
    }
 }
 return QVariant();
}
/*public*/ bool AlignmentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int r = index.row();
  QList <LAlignElement*>* alignList = NULL;
    if (self->_showAllAlign) {
        alignList = self->_alignList;
    }
    else {
        alignList = self->_includedAlignList;
    }
    switch (index.column()) {
        case INCLUDE_COLUMN:
            alignList->at(r)->setIncluded(value.toBool());
            break;
        case STATE_COLUMN:
            alignList->at(r)->setAlignType(value.toString());
            break;
    }
    return true;
 }
 return false;
};


// Should not conflict with state variable types
/*public*/ /*final*/ /*static*/ int LRouteTableAction::VETO            = 0x80;
// due to the unecessary bit assignments in SignalHead for appearances,
// offset the following
/*public*/ /*static*/ /*final*/ int LRouteTableAction::OFFSET  = 0x30;
/*public*/ /*static*/ /*final*/ int LRouteTableAction::SET_SIGNAL_HELD = Conditional::ACTION_SET_SIGNAL_HELD + LRouteTableAction::OFFSET;
/*public*/ /*static*/ /*final*/ int LRouteTableAction::CLEAR_SIGNAL_HELD = Conditional::ACTION_CLEAR_SIGNAL_HELD + LRouteTableAction::OFFSET;
/*public*/ /*static*/ /*final*/ int LRouteTableAction::SET_SIGNAL_DARK = Conditional::ACTION_SET_SIGNAL_DARK + LRouteTableAction::OFFSET;
/*public*/ /*static*/ /*final*/ int LRouteTableAction::SET_SIGNAL_LIT  = Conditional::ACTION_SET_SIGNAL_LIT + LRouteTableAction::OFFSET;

//private /*static*/ int ROW_HEIGHT;

/*private static*/ QString LRouteTableAction::ALIGN_SENSOR      = tr("AlignSensor");
/*private static*/ QString LRouteTableAction::ALIGN_TURNOUT     = tr("AlignTurnout");
/*private static*/ QString LRouteTableAction::ALIGN_LIGHT       = tr("AlignLight");
/*private static*/ QString LRouteTableAction::ALIGN_SIGNAL      = tr("AlignSignal");
/*private static*/ QString LRouteTableAction::ALIGN_ALL         = tr("AlignAll");

/*private static*/ QString LRouteTableAction::ON_CHANGE         = tr("OnChange");
/*private static*/ QString LRouteTableAction::ON_ACTIVE         = tr("OnActive");
/*private static*/ QString LRouteTableAction::ON_INACTIVE       = tr("OnInactive");
/*private static*/ QString LRouteTableAction::VETO_ON_ACTIVE    = tr("VetoActive");
/*private static*/ QString LRouteTableAction::VETO_ON_INACTIVE  = tr("VetoInactive");
/*private static*/ QString LRouteTableAction::ON_THROWN         = tr("OnThrown");
/*private static*/ QString LRouteTableAction::ON_CLOSED         = tr("OnClosed");
/*private static*/ QString LRouteTableAction::VETO_ON_THROWN    = tr("VetoThrown");
/*private static*/ QString LRouteTableAction::VETO_ON_CLOSED    = tr("VetoClosed");
/*private static*/ QString LRouteTableAction::ON_LIT            = tr("OnLit");
/*private static*/ QString LRouteTableAction::ON_UNLIT          = tr("OnUnLit");
/*private static*/ QString LRouteTableAction::VETO_ON_LIT       = tr("VetoLit");
/*private static*/ QString LRouteTableAction::VETO_ON_UNLIT     = tr("VetoUnLit");
/*private static*/ QString LRouteTableAction::ON_RED            = tr("OnRed");
/*private static*/ QString LRouteTableAction::ON_FLASHRED       = tr("OnFlashRed");
/*private static*/ QString LRouteTableAction::ON_YELLOW         = tr("OnYellow");
/*private static*/ QString LRouteTableAction::ON_FLASHYELLOW    = tr("OnFlashYellow");
/*private static*/ QString LRouteTableAction::ON_GREEN          = tr("OnGreen");
/*private static*/ QString LRouteTableAction::ON_FLASHGREEN     = tr("OnFlashGreen");
/*private static*/ QString LRouteTableAction::ON_DARK           = tr("OnDark");
/*private static*/ QString LRouteTableAction::ON_SIGNAL_LIT     = tr("OnLit");
/*private static*/ QString LRouteTableAction::ON_SIGNAL_HELD    = tr("OnHeld");
/*private static*/ QString LRouteTableAction::VETO_ON_RED       = tr("VetoOnRed");
/*private static*/ QString LRouteTableAction::VETO_ON_FLASHRED  = tr("VetoOnFlashRed");
/*private static*/ QString LRouteTableAction::VETO_ON_YELLOW    = tr("VetoOnYellow");
/*private static*/ QString LRouteTableAction::VETO_ON_FLASHYELLOW = tr("VetoOnFlashYellow");
/*private static*/ QString LRouteTableAction::VETO_ON_GREEN       = tr("VetoOnGreen");
/*private static*/ QString LRouteTableAction::VETO_ON_FLASHGREEN  = tr("VetoOnFlashGreen");
/*private static*/ QString LRouteTableAction::VETO_ON_DARK        = tr("VetoOnDark");
/*private static*/ QString LRouteTableAction::VETO_ON_SIGNAL_LIT  = tr("VetoOnLit");
/*private static*/ QString LRouteTableAction::VETO_ON_SIGNAL_HELD = tr("VetoOnHeld");

/*private static*/ QString LRouteTableAction::SET_TO_ACTIVE     = tr("SetActive");
/*private static*/ QString LRouteTableAction::SET_TO_INACTIVE   = tr("SetInactive");
/*private static*/ QString LRouteTableAction::SET_TO_CLOSED     = tr("SetClosed");
/*private static*/ QString LRouteTableAction::SET_TO_THROWN     = tr("SetThrown");
/*private static*/ QString LRouteTableAction::SET_TO_TOGGLE     = tr("SetToggle");
/*private static*/ QString LRouteTableAction::SET_TO_ON         = tr("SetLightOn");
/*private static*/ QString LRouteTableAction::SET_TO_OFF        = tr("SetLightOff");
/*private static*/ QString LRouteTableAction::SET_TO_DARK       = tr("SetDark");
/*private static*/ QString LRouteTableAction::SET_TO_LIT        = tr("SetLit");
/*private static*/ QString LRouteTableAction::SET_TO_HELD       = tr("SetHeld");
/*private static*/ QString LRouteTableAction::SET_TO_CLEAR      = tr("SetClear");
/*private static*/ QString LRouteTableAction::SET_TO_RED        = tr("SetRed");
/*private static*/ QString LRouteTableAction::SET_TO_FLASHRED   = tr("SetFlashRed");
/*private static*/ QString LRouteTableAction::SET_TO_YELLOW     = tr("SetYellow");
/*private static*/ QString LRouteTableAction::SET_TO_FLASHYELLOW = tr("SetFlashYellow");
/*private static*/ QString LRouteTableAction::SET_TO_GREEN      = tr("SetGreen");
/*private static*/ QString LRouteTableAction::SET_TO_FLASHGREEN = tr("SetFlashGreen");

/*private static*/ QStringList LRouteTableAction::ALIGNMENT_STATES    = QStringList() << LRouteTableAction::ALIGN_SENSOR << LRouteTableAction::ALIGN_TURNOUT << LRouteTableAction::ALIGN_LIGHT<< LRouteTableAction::ALIGN_SIGNAL << LRouteTableAction::ALIGN_ALL;
/*private static*/ QStringList LRouteTableAction::INPUT_SENSOR_STATES = QStringList() << LRouteTableAction::ON_ACTIVE<< LRouteTableAction::ON_INACTIVE<< LRouteTableAction::ON_CHANGE<< LRouteTableAction::VETO_ON_ACTIVE<< LRouteTableAction::VETO_ON_INACTIVE;
/*private static*/ QStringList LRouteTableAction::INPUT_TURNOUT_STATES= QStringList() << LRouteTableAction::ON_THROWN << LRouteTableAction::ON_CLOSED<< LRouteTableAction::ON_CHANGE<< LRouteTableAction::VETO_ON_THROWN<< LRouteTableAction::VETO_ON_CLOSED;
/*private static*/ QStringList LRouteTableAction::INPUT_LIGHT_STATES  = QStringList() << LRouteTableAction::ON_LIT<< LRouteTableAction::ON_UNLIT<< LRouteTableAction::ON_CHANGE<< LRouteTableAction::VETO_ON_LIT<< LRouteTableAction::VETO_ON_UNLIT;
/*private static*/ QStringList LRouteTableAction::INPUT_SIGNAL_STATES = QStringList() << LRouteTableAction::ON_RED<< LRouteTableAction::ON_FLASHRED << LRouteTableAction::ON_YELLOW<< LRouteTableAction::ON_FLASHYELLOW<< LRouteTableAction::ON_GREEN << LRouteTableAction::ON_FLASHGREEN<< LRouteTableAction::ON_DARK<< LRouteTableAction::ON_SIGNAL_LIT<< LRouteTableAction::ON_SIGNAL_HELD<< LRouteTableAction::VETO_ON_RED << LRouteTableAction::VETO_ON_FLASHRED<< LRouteTableAction::VETO_ON_YELLOW<< LRouteTableAction::VETO_ON_FLASHYELLOW<< LRouteTableAction::VETO_ON_GREEN << LRouteTableAction::                                       VETO_ON_FLASHGREEN<< LRouteTableAction::VETO_ON_DARK<< LRouteTableAction::VETO_ON_SIGNAL_LIT<< LRouteTableAction::VETO_ON_SIGNAL_HELD;
/*private static*/ QStringList LRouteTableAction::OUTPUT_SENSOR_STATES  = QStringList() << LRouteTableAction::SET_TO_ACTIVE<< LRouteTableAction::SET_TO_INACTIVE<< LRouteTableAction::SET_TO_TOGGLE;
/*private static*/ QStringList LRouteTableAction::OUTPUT_TURNOUT_STATES = QStringList() << LRouteTableAction::SET_TO_CLOSED<< LRouteTableAction::SET_TO_THROWN<< LRouteTableAction::SET_TO_TOGGLE;
/*private static*/ QStringList LRouteTableAction::OUTPUT_LIGHT_STATES   = QStringList() << LRouteTableAction::SET_TO_ON<< LRouteTableAction::SET_TO_OFF<< LRouteTableAction::SET_TO_TOGGLE;
/*private static*/ QStringList LRouteTableAction::OUTPUT_SIGNAL_STATES = QStringList() << LRouteTableAction::SET_TO_DARK<< LRouteTableAction::SET_TO_LIT<< LRouteTableAction::SET_TO_HELD<< LRouteTableAction::SET_TO_CLEAR << LRouteTableAction::                                                    SET_TO_RED<< LRouteTableAction::SET_TO_FLASHRED<< LRouteTableAction::SET_TO_YELLOW << LRouteTableAction::
                                                    SET_TO_FLASHYELLOW<< LRouteTableAction::SET_TO_GREEN<< LRouteTableAction::SET_TO_FLASHGREEN;

#if 0
/**
* Sorts RouteElement
*/
/*public*/ static class RouteElementComparator extends SystemNameComparator {
RouteElementComparator() {
}
/*public*/ int compare(Object o1, Object o2) {
    return super.compare( ((RouteElement)o1).getSysName(), ((RouteElement)o2).getSysName());
}
}
#endif
/**
* Base class for all the output (ConditionalAction)
* and input (ConditionalVariable) elements
*/
//class RouteElement {

LRouteElement::LRouteElement(QString sysName, QString userName, int type, QObject* parent ) : QObject(parent)
{
    _sysName = sysName;
    _userName = userName;
    _type = type;
    _included = false;
    switch (type) {
        case LRouteTableAction::SENSOR_TYPE:
            _typeString = tr("Sensor");
            break;
        case LRouteTableAction::TURNOUT_TYPE:
            _typeString = tr("Turnout");
            break;
        case LRouteTableAction::LIGHT_TYPE:
            _typeString = tr("Light");
            break;
        case LRouteTableAction::SIGNAL_TYPE:
            _typeString = tr("Signal");
            break;
        case LRouteTableAction::CONDITIONAL_TYPE:
            _typeString = tr("Conditional");
            break;
    }
}
QString LRouteElement::getSysName() {
    return _sysName;
}
QString LRouteElement::getUserName() {
    return _userName;
}
int LRouteElement::getType() {
    return _type;
}
QString LRouteElement::getTypeString() {
    return _typeString;
}
bool LRouteElement::isIncluded() {
    return _included;
}
void LRouteElement::setIncluded(bool include) {
    _included = include;
}

int LRouteElement::getState() {
    return _state;
}
void LRouteElement::setState(int state) {
    _state = state;
}
//};

//abstract class RouteInputElement extends RouteElement {
LRouteInputElement::LRouteInputElement(QString sysName, QString userName, int type, QObject* parent) :LRouteElement(sysName, userName, type, parent)
{
    //super(sysName, userName, type);
}
/*abstract*/ QString LRouteInputElement::getTestState(){return "";}
/*abstract*/ void LRouteInputElement::setTestState(QString /*state*/) {}
//};

//class RouteInputSensor extends RouteInputElement {
LRouteInputSensor::LRouteInputSensor (QString sysName, QString userName, QObject* parent) : LRouteInputElement(sysName, userName, LRouteTableAction::SENSOR_TYPE, parent)
{
    //super(sysName, userName, SENSOR_TYPE );
    setState(Conditional::TYPE_SENSOR_ACTIVE);
}
QString LRouteInputSensor::getTestState() {
    switch (_state) {
        case Conditional::TYPE_SENSOR_INACTIVE:
            return LRouteTableAction::ON_INACTIVE;
        case Conditional::TYPE_SENSOR_ACTIVE:
            return LRouteTableAction::ON_ACTIVE;
        case Route::ONCHANGE:
            return LRouteTableAction::ON_CHANGE;
        default:
        if(_state==LRouteTableAction::VETO+Conditional::TYPE_SENSOR_INACTIVE)
            return LRouteTableAction::VETO_ON_INACTIVE;
        if(_state ==LRouteTableAction::VETO+Conditional::TYPE_SENSOR_ACTIVE)
            return LRouteTableAction::VETO_ON_ACTIVE;
    }
    return "";
}
void LRouteInputSensor::setTestState(QString state) {
    if (LRouteTableAction::ON_INACTIVE==(state)) {
        _state = Conditional::TYPE_SENSOR_INACTIVE;
    } else if (LRouteTableAction::ON_ACTIVE==(state)) {
        _state = Conditional::TYPE_SENSOR_ACTIVE;
    } else if (LRouteTableAction::ON_CHANGE==(state)) {
        _state = Route::ONCHANGE;
    } else if (LRouteTableAction::VETO_ON_INACTIVE==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SENSOR_INACTIVE;
    } else if (LRouteTableAction::VETO_ON_ACTIVE==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SENSOR_ACTIVE;
    }
}
//};

//class RouteInputTurnout extends RouteInputElement {
LRouteInputTurnout::LRouteInputTurnout (QString sysName, QString userName, QObject* parent)
    : LRouteInputElement(sysName, userName, LRouteTableAction::TURNOUT_TYPE, parent)
{
    //super(sysName, userName, TURNOUT_TYPE );
    setState(Conditional::TYPE_TURNOUT_CLOSED);
}
 QString LRouteInputTurnout::getTestState() {
    switch (_state) {
        case Conditional::TYPE_TURNOUT_CLOSED:
            return LRouteTableAction::ON_CLOSED;
        case Conditional::TYPE_TURNOUT_THROWN:
            return LRouteTableAction::ON_THROWN;
        case Route::ONCHANGE:
            return LRouteTableAction::ON_CHANGE;
    default:
        if( LRouteTableAction::VETO+Conditional::TYPE_TURNOUT_CLOSED)
            return LRouteTableAction::VETO_ON_CLOSED;
        if(LRouteTableAction::VETO+Conditional::TYPE_TURNOUT_THROWN)
            return LRouteTableAction::VETO_ON_THROWN;
    }
    return "";
}
void LRouteInputTurnout::setTestState(QString state) {
    if (LRouteTableAction::ON_CLOSED==(state)) {
        _state = Conditional::TYPE_TURNOUT_CLOSED;
    } else if (LRouteTableAction::ON_THROWN==(state)) {
        _state = Conditional::TYPE_TURNOUT_THROWN;
    } else if (LRouteTableAction::ON_CHANGE==(state)) {
        _state = Route::ONCHANGE;
    } else if (LRouteTableAction::VETO_ON_CLOSED==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_TURNOUT_CLOSED;
    } else if (LRouteTableAction::VETO_ON_THROWN==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_TURNOUT_THROWN;
    }
}
//};

//class RouteInputLight extends RouteInputElement {
LRouteInputLight::LRouteInputLight (QString sysName, QString userName, QObject* parent) : LRouteInputElement(sysName, userName, LRouteTableAction::LIGHT_TYPE , parent) {
    //super(sysName, userName, LRouteTableAction::LIGHT_TYPE );
    setState(Conditional::TYPE_LIGHT_OFF);
}
QString LRouteInputLight::getTestState() {
    switch (_state) {
        case Conditional::TYPE_LIGHT_OFF:
            return LRouteTableAction::ON_UNLIT;
        case Conditional::TYPE_LIGHT_ON:
            return LRouteTableAction::ON_LIT;
        case Route::ONCHANGE:
            return LRouteTableAction::ON_CHANGE;
    default:
        if(_state== LRouteTableAction::VETO+Conditional::TYPE_LIGHT_OFF)
            return LRouteTableAction::VETO_ON_UNLIT;
        if(_state== LRouteTableAction::VETO+Conditional::TYPE_LIGHT_ON)
            return LRouteTableAction::VETO_ON_LIT;
    }
    return "";
}
void LRouteInputLight::setTestState(QString state) {
    if (LRouteTableAction::ON_UNLIT==(state)) {
        _state = Conditional::TYPE_LIGHT_OFF;
    } else if (LRouteTableAction::ON_LIT==(state)) {
        _state = Conditional::TYPE_LIGHT_ON;
    } else if (LRouteTableAction::ON_CHANGE==(state)) {
        _state = Route::ONCHANGE;
    } else if (LRouteTableAction::VETO_ON_UNLIT==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_LIGHT_OFF;
    } else if (LRouteTableAction::VETO_ON_LIT==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_LIGHT_ON;
    }
}
//}

//class RouteInputSignal extends RouteInputElement {
LRouteInputSignal::LRouteInputSignal (QString sysName, QString userName, QObject* parent) : LRouteInputElement(sysName, userName, LRouteTableAction::SIGNAL_TYPE, parent ) {
        //super(sysName, userName, SIGNAL_TYPE );
        setState(Conditional::TYPE_SIGNAL_HEAD_LIT);
}
QString LRouteInputSignal::getTestState() {
    switch (_state) {
        case Conditional::TYPE_SIGNAL_HEAD_RED:
            return LRouteTableAction::ON_RED;
        case Conditional::TYPE_SIGNAL_HEAD_FLASHRED:
            return LRouteTableAction::ON_FLASHRED;
        case Conditional::TYPE_SIGNAL_HEAD_YELLOW:
            return LRouteTableAction::ON_YELLOW;
        case Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW:
            return LRouteTableAction::ON_FLASHYELLOW;
        case Conditional::TYPE_SIGNAL_HEAD_GREEN:
            return LRouteTableAction::ON_GREEN;
        case Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN:
            return LRouteTableAction::ON_FLASHGREEN;
        case Conditional::TYPE_SIGNAL_HEAD_DARK:
            return LRouteTableAction::ON_DARK;
        case Conditional::TYPE_SIGNAL_HEAD_LIT:
            return LRouteTableAction::ON_SIGNAL_LIT;
        case Conditional::TYPE_SIGNAL_HEAD_HELD:
            return LRouteTableAction::ON_SIGNAL_HELD;
    default:
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_RED)
            return LRouteTableAction::VETO_ON_RED;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHRED)
            return LRouteTableAction::VETO_ON_FLASHRED;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_YELLOW)
            return LRouteTableAction::VETO_ON_YELLOW;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW)
            return LRouteTableAction::VETO_ON_FLASHYELLOW;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_GREEN)
            return LRouteTableAction::VETO_ON_GREEN;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN)
            return LRouteTableAction::VETO_ON_FLASHGREEN;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_DARK)
            return LRouteTableAction::VETO_ON_DARK;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_LIT)
            return LRouteTableAction::VETO_ON_SIGNAL_LIT;
        if(_state==  LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_HELD)
            return LRouteTableAction::VETO_ON_SIGNAL_HELD;
    }
    return "";
}
void LRouteInputSignal::setTestState(QString state) {
    if (LRouteTableAction::ON_RED==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_RED;
    } else if (LRouteTableAction::ON_FLASHRED==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_FLASHRED;
    } else if (LRouteTableAction::ON_YELLOW==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_YELLOW;
    } else if (LRouteTableAction::ON_FLASHYELLOW==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW;
    } else if (LRouteTableAction::ON_GREEN==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_GREEN;
    } else if (LRouteTableAction::ON_FLASHGREEN==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN;
    } else if (LRouteTableAction::ON_DARK==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_DARK;
    } else if (LRouteTableAction::ON_SIGNAL_LIT==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_LIT;
    } else if (LRouteTableAction::ON_SIGNAL_HELD==(state)) {
        _state = Conditional::TYPE_SIGNAL_HEAD_HELD;
    } else if (LRouteTableAction::VETO_ON_RED==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_RED;
    } else if (LRouteTableAction::VETO_ON_FLASHRED==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHRED;
    } else if (LRouteTableAction::VETO_ON_YELLOW==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_YELLOW;
    } else if (LRouteTableAction::VETO_ON_FLASHYELLOW==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHYELLOW;
    } else if (LRouteTableAction::VETO_ON_GREEN==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_GREEN;
    } else if (LRouteTableAction::VETO_ON_FLASHGREEN==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_FLASHGREEN;
    } else if (LRouteTableAction::VETO_ON_DARK==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_DARK;
    } else if (LRouteTableAction::VETO_ON_SIGNAL_LIT==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_LIT;
    } else if (LRouteTableAction::VETO_ON_SIGNAL_HELD==(state)) {
        _state = LRouteTableAction::VETO+Conditional::TYPE_SIGNAL_HEAD_HELD;
    }
}
//}

//abstract class RouteOutputElement extends RouteElement {
LRouteOutputElement::LRouteOutputElement(QString sysName, QString userName, int type, QObject* parent)
    : LRouteElement(sysName, userName, type, parent)
{
    //super(sysName, userName, type);
}
/*abstract*/ QString LRouteOutputElement::getSetToState() {return "";}
/*abstract*/ void LRouteOutputElement::setSetToState(QString /*state*/){}
//};

//class RouteOutputSensor extends RouteOutputElement {
LRouteOutputSensor::LRouteOutputSensor (QString sysName, QString userName, QObject* parent) : LRouteOutputElement(sysName, userName, LRouteTableAction::SENSOR_TYPE, parent)
{
    //super(sysName, userName, SENSOR_TYPE );
    setState(Sensor::ACTIVE);
}
QString LRouteOutputSensor::getSetToState() {
    switch (_state) {
        case Sensor::INACTIVE:
            return LRouteTableAction::SET_TO_INACTIVE;
        case Sensor::ACTIVE:
            return LRouteTableAction::SET_TO_ACTIVE;
        case Route::TOGGLE:
            return LRouteTableAction::SET_TO_TOGGLE;
    }
    return "";
}
void LRouteOutputSensor::setSetToState(QString state) {
    if (LRouteTableAction::SET_TO_INACTIVE==(state)) {
        _state = Sensor::INACTIVE;
    } else if (LRouteTableAction::SET_TO_ACTIVE==(state)) {
        _state = Sensor::ACTIVE;
    } else if (LRouteTableAction::SET_TO_TOGGLE==(state)) {
        _state = Route::TOGGLE;
    }
}
//};

//class RouteOutputTurnout extends RouteOutputElement {
LRouteOutputTurnout::LRouteOutputTurnout(QString sysName, QString userName, QObject* parent) : LRouteOutputElement(sysName, userName, LRouteTableAction::TURNOUT_TYPE, parent){
    //super(sysName, userName, TURNOUT_TYPE);
    setState(Turnout::CLOSED);
}
QString LRouteOutputTurnout::getSetToState() {
    switch (_state) {
        case Turnout::CLOSED:
            return LRouteTableAction::SET_TO_CLOSED;
        case Turnout::THROWN:
            return LRouteTableAction::SET_TO_THROWN;
        case Route::TOGGLE:
            return LRouteTableAction::SET_TO_TOGGLE;
    }
    return "";
}
void LRouteOutputTurnout::setSetToState(QString state) {
    if (LRouteTableAction::SET_TO_CLOSED==(state)) {
        _state = Turnout::CLOSED;
    } else if (LRouteTableAction::SET_TO_THROWN==(state)) {
        _state = Turnout::THROWN;
    } else if (LRouteTableAction::SET_TO_TOGGLE==(state)) {
        _state = Route::TOGGLE;
    }
}
//};

//class RouteOutputLight extends RouteOutputElement {
LRouteOutputLight::LRouteOutputLight(QString sysName, QString userName, QObject* parent) : LRouteOutputElement(sysName, userName, LRouteTableAction::LIGHT_TYPE, parent)
{
    //super(sysName, userName, LIGHT_TYPE);
    setState(Light::ON);
}
QString LRouteOutputLight::getSetToState() {
    switch (_state) {
        case Light::ON:
            return LRouteTableAction::SET_TO_ON;
        case Light::OFF:
            return LRouteTableAction::SET_TO_OFF;
        case Route::TOGGLE:
            return LRouteTableAction::SET_TO_TOGGLE;
    }
    return "";
}
void LRouteOutputLight::setSetToState(QString state) {
    if (LRouteTableAction::SET_TO_ON==(state)) {
        _state = Light::ON;
    } else if (LRouteTableAction::SET_TO_OFF==(state)) {
        _state = Light::OFF;
    } else if (LRouteTableAction::SET_TO_TOGGLE==(state)) {
        _state = Route::TOGGLE;
    }
}
//}

//class RouteOutputSignal extends RouteOutputElement {
LRouteOutputSignal::LRouteOutputSignal(QString sysName, QString userName, QObject* parent) : LRouteOutputElement(sysName, userName, LRouteTableAction::SIGNAL_TYPE, parent) {
    //super(sysName, userName, LRouteTableAction::SIGNAL_TYPE);
    setState(SignalHead::RED);
}
QString LRouteOutputSignal::getSetToState() {
    switch (_state) {
        case SignalHead::DARK:
            return LRouteTableAction::SET_TO_DARK;
        case SignalHead::RED:
            return LRouteTableAction::SET_TO_RED;
        case SignalHead::FLASHRED:
            return LRouteTableAction::SET_TO_FLASHRED;
        case SignalHead::YELLOW:
            return LRouteTableAction::SET_TO_YELLOW;
        case SignalHead::FLASHYELLOW:
            return LRouteTableAction::SET_TO_FLASHYELLOW;
        case SignalHead::GREEN:
            return LRouteTableAction::SET_TO_GREEN;
        case SignalHead::FLASHGREEN:
            return LRouteTableAction::SET_TO_FLASHGREEN;
    default:
        if(_state== LRouteTableAction::CLEAR_SIGNAL_HELD)
            return LRouteTableAction::SET_TO_CLEAR;
        if(_state==  LRouteTableAction::SET_SIGNAL_LIT)
            return LRouteTableAction::SET_TO_LIT;
        if(_state== LRouteTableAction::SET_SIGNAL_HELD)
            return LRouteTableAction::SET_TO_HELD;
    }
    return "";
}
void LRouteOutputSignal::setSetToState(QString state) {
    if (LRouteTableAction::SET_TO_DARK==(state)) {
        _state = SignalHead::DARK;
    } else if (LRouteTableAction::SET_TO_RED==(state)) {
        _state = SignalHead::RED;
    } else if (LRouteTableAction::SET_TO_FLASHRED==(state)) {
        _state = SignalHead::FLASHRED;
    } else if (LRouteTableAction::SET_TO_YELLOW==(state)) {
        _state = SignalHead::YELLOW;
    } else if (LRouteTableAction::SET_TO_FLASHYELLOW==(state)) {
        _state = SignalHead::FLASHYELLOW;
    } else if (LRouteTableAction::SET_TO_GREEN==(state)) {
        _state = SignalHead::GREEN;
    } else if (LRouteTableAction::SET_TO_FLASHGREEN==(state)) {
        _state = SignalHead::FLASHGREEN;
    } else if (LRouteTableAction::SET_TO_CLEAR==(state)) {
        _state = LRouteTableAction::CLEAR_SIGNAL_HELD;
    } else if (LRouteTableAction::SET_TO_LIT==(state)) {
        _state = LRouteTableAction::SET_SIGNAL_LIT;
    } else if (LRouteTableAction::SET_TO_HELD==(state)) {
        _state = LRouteTableAction::SET_SIGNAL_HELD;
    }
}
//};

//class AlignElement : public RouteElement {
LAlignElement::LAlignElement(QString sysName, QString userName, QObject* parent)
    : LRouteElement(sysName, userName, LRouteTableAction::SENSOR_TYPE, parent){
    //super(sysName, userName, SENSOR_TYPE);
    setState(LRouteTableAction::TURNOUT_TYPE);
}
QString LAlignElement::getAlignType() {
    switch (_state) {
        case LRouteTableAction::SENSOR_TYPE:
            return LRouteTableAction::ALIGN_SENSOR;
        case LRouteTableAction::TURNOUT_TYPE:
            return LRouteTableAction::ALIGN_TURNOUT;
        case LRouteTableAction::LIGHT_TYPE:
            return LRouteTableAction::ALIGN_LIGHT;
        case LRouteTableAction::SIGNAL_TYPE:
            return LRouteTableAction::ALIGN_SIGNAL;
        case LRouteTableAction::ALL_TYPE:
            return LRouteTableAction::ALIGN_ALL;
    }
    return "";
}
void LAlignElement::setAlignType(QString state) {
    if (LRouteTableAction::ALIGN_SENSOR==(state)) {
        _state = LRouteTableAction::SENSOR_TYPE;
    } else if (LRouteTableAction::ALIGN_TURNOUT==(state)) {
        _state = LRouteTableAction::TURNOUT_TYPE;
    } else if (LRouteTableAction::ALIGN_LIGHT==(state)) {
        _state = LRouteTableAction::LIGHT_TYPE;
    } else if (LRouteTableAction::ALIGN_SIGNAL==(state)) {
        _state = LRouteTableAction::SIGNAL_TYPE;
    } else if (LRouteTableAction::ALIGN_ALL==(state)) {
        _state = LRouteTableAction::ALL_TYPE;
    }
}
//};

/*public*/ void LRouteTableAction::setMessagePreferencesDetails()
{
 ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->setPreferenceItemDetails(getClassName(), "remindSaveRoute", tr("Hide Save Message Reminder"));
AbstractTableAction::setMessagePreferencesDetails();
}

/*protected*/ QString LRouteTableAction::getClassName() { return "jmri.jmrit.beantable.LRouteTableAction"; }
/*public*/ QString LRouteTableAction::getClassDescription() { return tr("LRoute Table"); }

//static final org.apache.log4j.Logger log = org.apache.log4j.Logger
//    .getLogger(LRouteTableAction.class.getName());
//}
/* @(#)RouteTableAction.java */

/**
* Sets whether the {@code Action} is enabled. The default is {@code true}.
*
* @param newValue  {@code true} to enable the action, {@code false} to
*                  disable it
* @see Action#setEnabled
*/
/*public*/ void LRouteTableAction::setEnabled(bool newValue)
{
 bool oldValue = this->enabled;

 if (oldValue != newValue)
 {
  this->enabled = newValue;
  //  firePropertyChange("enabled", QVariant(oldValue), QVariant(newValue));
 }
}
LComboBoxDelegate::LComboBoxDelegate(RouteElementModel* model, LRouteTableAction* self, QObject *parent)
: JComboBoxEditor(parent)
{
 this->model  = model;
 this->self = self;
}


QWidget *LComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index ) const
{
 QComboBox* editor = new QComboBox(parent);
 LRouteElement* elt = NULL;
 QStringList items;
 if (model->isInput())
  {
   if (self->_showAllInput) {
       elt = self->_inputList->at(index.row());
      }
      else {
          elt = self->_includedInputList->at(index.row());
      }
      items = self->getInputComboBoxItems(elt->getType());
  } else {
      if (self->_showAllOutput) {
          elt = self->_outputList->at(index.row());
      }
      else {
          elt = self->_includedOutputList->at(index.row());
      }
      items = self->getOutputComboBoxItems(elt->getType());
  }
  editor->addItems(items);
  return editor;
}

//void LComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//  QComboBox *comboBox = static_cast<QComboBox*>(editor);
//  int value = index.model()->data(index, Qt::EditRole).toUInt();
//  comboBox->setCurrentIndex(value);
//}

//void LComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
//  QComboBox *comboBox = static_cast<QComboBox*>(editor);
//  model->setData(index, comboBox->currentText(), Qt::EditRole);
//}

//void LComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//  editor->setGeometry(option.rect);
//}

//void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
// //bool state = index.data().toString() == this->on;
// JComboBox* widget = new JComboBox(values);
// widget->setEditable(true);
// widget->setCurrentText(index.model()->data(index, Qt::DisplayRole).toString());
// widget->resize(option.rect.size());
// QPixmap pixmap(option.rect.size());
// widget->render(&pixmap);
// painter->drawPixmap(option.rect,pixmap);
//}

QString LRouteTableAction::getName()
{
 return "jmri.jmrit.beantable.LRouteTableAction";
}
