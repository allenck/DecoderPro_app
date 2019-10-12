#include "turnouttableaction.h"
#include "turnoutmanager.h"
#include "turnout.h"
#include "instancemanager.h"
#include <QComboBox>
#include "signalspeedmap.h"
#include "userpreferencesmanager.h"
#include "../LayoutEditor/beantableframe.h"
#include "jtextfield.h"
#include <QLabel>
#include "jmrijframe.h"
#include <QBoxLayout>
#include "connectionnamefromsystemname.h"
#include "QMessageBox"
#include <QCheckBox>
#include "addnewhardwaredevicepanel.h"
#include <QPushButton>
#include "runnable.h"
#include "jtable.h"
#include "pushbuttondelegate.h" // for PushButtonItemDelegate
#include <QSignalMapper>
#include <QMenu>
#include <QMenuBar>
#include "turnoutoperationframe.h"
#include "abstracttabletabaction.h"
#include "jmrijframe.h"
#include "lnturnoutmanager.h"
#include "abstractsensor.h"
#include "turnoutoperationconfig.h"
#include "inputdialog.h"
#include "xtablecolumnmodel.h"
#include "turnouteditaction.h"
#include "systemnamecomparator.h"
#include <QSpinBox>
#include "colorutil.h"
#include "proxymanager.h"
#include "proxylightmanager.h"

TurnoutTableAction::TurnoutTableAction(QObject *parent) :
    AbstractTableAction("Turnout Table", parent)
{
 common();
}
/**
 * Swing action to create and register a
 * TurnoutTable GUI.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2004, 2007
 * @version     $Revision: 28161 $
 */

// /*public*/ class TurnoutTableAction extends AbstractTableAction {

/**
 *
 */
///*private*/ static /*final*/ long serialVersionUID = -8221584673872246104L;

/**
 * Create an action with a specific title.
 * <P>
 * Note that the argument is the Action title, not the title of the
 * resulting frame.  Perhaps this should be changed?
 * @param actionName
 */
/*public*/ TurnoutTableAction::TurnoutTableAction(QString actionName, QObject *parent)
    : AbstractTableAction(actionName, parent)
{
 //super(actionName);
 common();
}

// /*public*/ TurnoutTableAction() { this("Turnout Table");}

void TurnoutTableAction::common()
{
 setObjectName("TurnoutTableAction");
 useBlockSpeed = "Use Block Speed";
 bothText = "Both";
 cabOnlyText = "Cab only";
 pushbutText = "Pushbutton only";
 noneText = "None";
 lockOperations = QStringList();
 lockOperations  << bothText << cabOnlyText << pushbutText<< noneText;
 speedListClosed =  QVector<QString>();
 speedListThrown =  QVector<QString>();
 turnManager = InstanceManager::turnoutManagerInstance();
 noWarn = false;
 table = NULL;
 if(parent() == NULL)
  return;

 addFrame = NULL;
 userNameTextField = new JTextField(40);
 hardwareAddressTextField = new JTextField(20);
 statusBar = new QLabel(tr("Enter a Hardware Address and (optional) User Name."));


 prefixBox = new QComboBox();
 numberToAddSpinner = new QSpinBox();
 numberToAddSpinner->setMinimum(1);
 numberToAddSpinner->setMaximum(100);
 numberToAddSpinner->setSingleStep(1);
 numberToAddSpinner->setValue(1);
 rangeBox = new QCheckBox("Add a range");
 sysNameLabel = new QLabel("Hardware Address");
 userNameLabel = new QLabel(tr("User Name"));
 systemSelectionCombo = this->getName()+".SystemSelected";
 userNameError = this->getName()+".DuplicateUserName";
 log = new Logger("TurnoutTableAction");

 showFeedbackBox = new QCheckBox("Show feedback information");
 showFeedbackBox->setObjectName("showFeedbackBox");
 showLockBox = new QCheckBox("Show lock information");
 showTurnoutSpeedBox = new QCheckBox("Show Turnout Speed Details");
 doAutomationBox = new QCheckBox("Automatic retry");
 connectionChoice = "";

 p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 // disable ourself if there is no primary turnout manager available
 if (turnManager==NULL) {
     setEnabled(false);
 }

 //This following must contain the word Global for a correct match in the abstract turnout
 if(qobject_cast<ProxyTurnoutManager*>(turnManager)!=NULL)
 {
  defaultThrownSpeedText = ("Use Global " + ((ProxyTurnoutManager*)turnManager)->getDefaultThrownSpeed());
  defaultClosedSpeedText = ("Use Global " + ((ProxyTurnoutManager*)turnManager)->getDefaultClosedSpeed());
 }
 else
 {
  defaultThrownSpeedText = ("Use Global " + turnManager->getDefaultThrownSpeed());
  defaultClosedSpeedText = ("Use Global " + turnManager->getDefaultClosedSpeed());
 }
 //This following must contain the word Block for a correct match in the abstract turnout
 useBlockSpeed = "Use Block Speed";

 speedListClosed.append(defaultClosedSpeedText);
 speedListThrown.append(defaultThrownSpeedText);
 speedListClosed.append(useBlockSpeed);
 speedListThrown.append(useBlockSpeed);
 QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
 for(int i = 0; i<_speedMap.size(); i++)
 {
  if (!speedListClosed.contains(_speedMap.at(i)))
  {
   speedListClosed.append(_speedMap.at(i));
  }
  if (!speedListThrown.contains(_speedMap.at(i)))
  {
   speedListThrown.append(_speedMap.at(i));
  }
 }
}

//@Override
/*public*/ void TurnoutTableAction::setManager(Manager* man)
{
    turnManager = (TurnoutManager*) man;
}

/**
 * Create the JTable DataModel, along with the changes
 * for the specific case of Turnouts
 */
/*protected*/ void TurnoutTableAction::createModel()
{
 // store the terminology
 if(qobject_cast<ProxyManager*>(turnManager)!= NULL)
 {
  closedText = ((ProxyTurnoutManager*)turnManager)->getClosedText();
  thrownText = ((ProxyTurnoutManager*)turnManager)->getThrownText();
 }
 else
 {
  closedText = turnManager->getClosedText();
  thrownText = turnManager->getThrownText();
 }
 // create the data model object that drives the table;
 // note that this is a class creation, and very long
 m = new TurnoutTableDataModel(this);
}

/**
 *
 */
// /*private*/ static /*final*/ long serialVersionUID = -8822546005900067212L;
TurnoutTableDataModel::TurnoutTableDataModel(TurnoutTableAction *self)
    : BeanTableDataModel(self)
{
 this->self = self;
 log = new Logger("TTBeanTableDataModel");
 init();
}

//@Override
/*public*/ int TurnoutTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
    return QUERYCOL+getPropertyColumnCount()+1;
}

//@Override
/*public*/ QVariant TurnoutTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{

 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
    case INVERTCOL: return "Inverted";
    case LOCKCOL: return "Locked";
    case KNOWNCOL: return "Feedback";
    case MODECOL: return "Mode";
    case SENSOR1COL: return "Sensor 1(T)";
    case SENSOR2COL: return "Sensor 2(C)";
    case OPSONOFFCOL: return "Automate";
    case OPSEDITCOL: return "";
    case LOCKOPRCOL: return "Lock Mode";
    case LOCKDECCOL: return "Decoder";
    case DIVERGCOL: return "Thrown Speed";
    case STRAIGHTCOL: return "Closed Speed";
    case FORGETCOL: return "State";
    case QUERYCOL: return "State";
    //case BeanTableDataModel::VALUECOL: return "Cmd";  // override default title
    case EDITCOL: return "";
    default:
      break;
  }
  return BeanTableDataModel::headerData(section,orientation, role);
 }
 return QVariant();
}

////@Override
///*public*/ Class<?> getColumnClass(int col) {
//    if (col==INVERTCOL) return bool.class;
//    case TurnoutTableAction::LOCKCOL) return bool.class;
//    case TurnoutTableAction::KNOWNCOL) return QString.class;
//    case TurnoutTableAction::MODECOL) return JComboBox.class;
//    case TurnoutTableAction::SENSOR1COL) return JComboBox.class;
//    case TurnoutTableAction::SENSOR2COL) return JComboBox.class;
//    case TurnoutTableAction::OPSONOFFCOL) return JComboBox.class;
//    case TurnoutTableAction::OPSEDITCOL) return JButton.class;
//    case TurnoutTableAction::EDITCOL) return JButton.class;
//    case TurnoutTableAction::LOCKOPRCOL)  return JComboBox.class;
//    case TurnoutTableAction::LOCKDECCOL) return JComboBox.class;
//    case TurnoutTableAction::DIVERGCOL) return JComboBox.class;
//    case TurnoutTableAction::STRAIGHTCOL) return JComboBox.class;
//    else return super.getColumnClass(col);
//}

//@Override
/*public*/ int TurnoutTableDataModel::getPreferredWidth(int col)
{
 switch(col)
 {
  case INVERTCOL  : return  JTextField(6).getPreferredSize().width();
  case LOCKCOL    : return  JTextField(6).getPreferredSize().width();
  case LOCKOPRCOL : return  JTextField(10).getPreferredSize().width();
  case LOCKDECCOL : return  JTextField(10).getPreferredSize().width();
  case KNOWNCOL : return  JTextField(10).getPreferredSize().width();
  case MODECOL : return  JTextField(10).getPreferredSize().width();
  case SENSOR1COL : return  JTextField(5).getPreferredSize().width();
  case SENSOR2COL : return  JTextField(5).getPreferredSize().width();
  case OPSONOFFCOL : return  JTextField(14).getPreferredSize().width();
  case OPSEDITCOL : return  JTextField(7).getPreferredSize().width();
  case EDITCOL : return  JTextField(7).getPreferredSize().width();
  case DIVERGCOL : return  JTextField(14).getPreferredSize().width();
  case STRAIGHTCOL : return  JTextField(14).getPreferredSize().width();
  case FORGETCOL: return  QPushButton(tr("Forget")).sizeHint().width();
  case QUERYCOL: return  QPushButton(tr("Query")).sizeHint().width();
 default:
   break;
 }
 return BeanTableDataModel::getPreferredWidth(col);
}

//@Override
/*public*/ Qt::ItemFlags TurnoutTableDataModel::flags(const QModelIndex &index) const
{
 int row = index.row();
 int col = index.column();
 if(row < 0)
     return 0;
 QString name = sysNameList.at(row);
 TurnoutManager* manager = self->turnManager;
 AbstractTurnout* t;
 if(qobject_cast<ProxyManager*>(manager))
  t = (AbstractTurnout*)((AbstractProxyTurnoutManager*)manager)->getBeanBySystemName(name);
 else
  t =(AbstractTurnout*) ((AbstractTurnoutManager*)manager)->getBySystemName(name);

 Qt::ItemFlags editable = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 Qt::ItemFlags noteditable = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

 switch(col)
 {
  case INVERTCOL: return t->canInvert()?editable|Qt::ItemIsUserCheckable:Qt::NoItemFlags;
  case LOCKCOL:
     return t->canLock(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT)?Qt::ItemIsEnabled|Qt::ItemIsUserCheckable:Qt::NoItemFlags;
  case KNOWNCOL: return noteditable;
  case MODECOL: return editable;
  case SENSOR1COL: return editable;
  case SENSOR2COL: return editable;
  case OPSONOFFCOL: return editable;
  case OPSEDITCOL: return (t->getTurnoutOperation()!=NULL)?editable:noteditable;
  case LOCKOPRCOL:   return editable;
  case LOCKDECCOL:   return editable;
  case DIVERGCOL: return editable;
  case STRAIGHTCOL: return editable;
  case EDITCOL: return editable;
  case FORGETCOL: return editable;
  case QUERYCOL: return editable;
  default:
     return BeanTableDataModel::flags(index);
 }
}

//@Override
/*public*/ QVariant TurnoutTableDataModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 QString name = sysNameList.at(row);
 TurnoutManager* manager = self->turnManager;
 AbstractTurnout* t;
 if(qobject_cast<AbstractProxyTurnoutManager*>(manager))
  t = (AbstractTurnout*)((AbstractProxyTurnoutManager*)manager)->getBeanBySystemName(name);
 else
  t = (AbstractTurnout*)((AbstractTurnoutManager*)manager)->getBySystemName(name);
 if (t == NULL)
 {
  log->debug("error NULL turnout!");
  return "error";
 }
 if(qobject_cast<AbstractTurnout*>(t) == NULL)
  return QVariant();
 if(role == Qt::CheckStateRole)
 {
  switch (index.column())
  {
   case INVERTCOL:
    return t->getInverted()?Qt::Checked:Qt::Unchecked;
   case LOCKCOL:
    return t->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT)?Qt::Checked:Qt::Unchecked;
  }
 }
 if(role == Qt::DisplayRole)
 {
  // some error checking
  if (row >= sysNameList.size())
  {
   log->debug("row is greater than name list");
   return "error";
  }
  switch (index.column())
  {
//   case INVERTCOL:
//   {
//    bool val = t->getInverted();
//    return (val);
//   }
//   case LOCKCOL:
//   {
//    bool val = t->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT);
//    return (val);
//   }
   case KNOWNCOL:
   {
    if (t->getKnownState()==Turnout::CLOSED) return self->closedText;
    if (t->getKnownState()==Turnout::THROWN) return self->thrownText;
    if (t->getKnownState()==Turnout::INCONSISTENT) return "Inconsistent";
    else return "Unknown";
   }
   case MODECOL:
   {

//    QComboBox* c = new QComboBox();
//    c->addItems(t->getValidFeedbackNames());
//    c->setCurrentIndex(c->findText(t->getFeedbackModeName()));
//        c.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                comboBoxAction(e);
//            }
//        });

      //     return c;
     modeColDelegate->setItems( t->getValidFeedbackNames().toList(), t->getFeedbackModeName());
     return t->getFeedbackModeName();
    }
    case SENSOR1COL:
    {
     if(t->getFirstSensor() != NULL)
      return ((AbstractSensor*)t->getFirstSensor())->getDisplayName();
     break;
    }
    case SENSOR2COL:
    {
     if(t->getSecondNamedSensor() != NULL)
      return ((AbstractSensor*)t->getSecondSensor())->getDisplayName();
     break;
    }
    case OPSONOFFCOL:
    {
     //return self->makeAutomationBox(t);
     if(_table->itemDelegate(index) == nullptr || qobject_cast<TTComboBoxDelegate*>(_table->itemDelegate(index))== nullptr)
          _table->setItemDelegate(new TTComboBoxDelegate(QStringList(), self));
     QVector<QString> automationList = self->makeAutomationBox(t, index);
     QString currValue;
     if (t->getInhibitOperation() || t->getTurnoutOperation() == nullptr)
     {
      currValue = automationList.at(0);
     }
     else if (t->getTurnoutOperation() == NULL)
     {
      currValue = automationList.at(1);
     }
     else if (t->getTurnoutOperation()->isNonce())
     {
      currValue = automationList.at(2);
     }
     else
     {
      currValue = t->getTurnoutOperation()->getName();
     }

     ((TTComboBoxDelegate*)_table->itemDelegate(index))-> setItems(automationList.toList(), currValue);
     return currValue;
    }
    case OPSEDITCOL:
    {
     return tr("Edit Ops");
    }
    case EDITCOL:
    {
     return tr("Edit");
    }
    case  LOCKDECCOL:
    {
//        QComboBox* c = new QComboBox();
//        c->addItems(t->getValidDecoderNames());
//        c->setCurrentIndex(c->findText( t->getDecoderName()));
//        c.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                comboBoxAction(e);
//            }
//        });
//        return c;
      lockDecColDelegate->setItems(t->getValidDecoderNames(), t->getDecoderName());
      return t->getDecoderName();
    }
    case   LOCKOPRCOL:
    {
//        QComboBox* c = new QComboBox();
//        c->addItems(self->lockOperations);
     if (t->canLock(Turnout::CABLOCKOUT) && t->canLock(Turnout::PUSHBUTTONLOCKOUT))
     {
//            c->setCurrentIndex(c->findText(self->bothText));
      return self->bothText;
     }
     else if (t->canLock(Turnout::PUSHBUTTONLOCKOUT))
     {
//            c->setCurrentIndex( c->findText(self->pushbutText));
      return self->pushbutText;

     }
     else if (t->canLock(Turnout::CABLOCKOUT))
     {
//            c->setCurrentIndex( c->findText(self->cabOnlyText));
      return self->cabOnlyText;
     }
     else
     {
//            c->setCurrentIndex(c->findText(self->noneText));
      return self->noneText;
//        c.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                comboBoxAction(e);
     }
//        });
//        return c;
   }
   case STRAIGHTCOL:
  {

//        QString speed = t->getStraightSpeed();
//        if(!self->speedListClosed.contains(speed)){
//            self->speedListClosed.append(speed);
//        }
//        QComboBox* c = new QComboBox();
//        c->addItems(self->speedListClosed.toList());
//        c->setEditable(true);
//        c->setCurrentIndex(c->findText(speed));

//        return c;
      return t->getStraightSpeed();
   }
   case DIVERGCOL:
   {

//        QString speed = t->getDivergingSpeed();
//        if(!self->speedListThrown.contains(speed)){
//            self->speedListThrown.append(speed);
//        }
//        QComboBox* c = new QComboBox();
//        c->addItems(self->speedListThrown.toList());
//        c->setEditable(true);
//     c->setCurrentIndex(c->findText(speed));
//     return c;
      return t->getDivergingSpeed();
   }
  case FORGETCOL:
   return "Forget";
  case QUERYCOL:
   return "Query";
   default:
   {
    break;
   }
  }
 }
 return BeanTableDataModel::data(index, role);
}

//@Override
/*public*/ bool TurnoutTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 QString name = sysNameList.at(row);
 TurnoutManager* manager = self->turnManager;
 AbstractTurnout* t;
 if(qobject_cast<ProxyTurnoutManager*>(manager)!= NULL)
  t = (AbstractTurnout*)((ProxyTurnoutManager*)manager)->getBySystemName(name);
 else
  t = (AbstractTurnout*)((AbstractTurnoutManager*) manager)->getBySystemName(name);

 if(role == Qt::CheckStateRole)
 {
  switch(index.column())
  {
   case INVERTCOL:
   {
    if (t->canInvert())
    {
     bool b =  value.toBool();
     t->setInverted(b);
    }
    fireTableRowsUpdated(row,row);
    fireTableDataChanged();
    return true;

   }
   case LOCKCOL:
   {
    bool b = value.toBool();
    t->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT,	b);
    fireTableRowsUpdated(row,row);
    return true;
   }
  }
 }
 if(role == Qt::EditRole)
 {
  switch(index.column())
  {
   case COMMENTCOL:
   {
    getBySystemName(sysNameList.at(row))->setComment(value.toString());
    fireTableRowsUpdated(row, row);
    return true;
   }
   case MODECOL:
   {
//    QString modeName = ((QComboBox*)value)->currentText();
    t->setFeedbackMode(value.toString());
    fireTableRowsUpdated(row,row);
    return true;
   }
   case SENSOR1COL:
   {
    try
    {
     t->provideFirstFeedbackSensor(value.toString());
    }
    catch (JmriException e)
    {
     //JOptionPane.showMessageDialog(NULL, e.toString());
     QMessageBox::warning(NULL, tr("Warning"), e.getMessage());
    }
    fireTableRowsUpdated(row, row);
    return true;
   }
   case SENSOR2COL:
   {
    try
    {
     t->provideSecondFeedbackSensor(value.toString());
    }
    catch (JmriException e)
    {
     //JOptionPane.showMessageDialog(NULL, e.toString());
     QMessageBox::warning(NULL, tr("Warning"), e.getMessage());
    }
   fireTableRowsUpdated(row,row);
   return true;
   }
   case OPSONOFFCOL:
   {
    // do nothing as this is handled by the combo box listener
    break;
   }
   case OPSEDITCOL :
   {
    t->setInhibitOperation(false);
//    //@SuppressWarnings("unchecked") // cast to QComboBox* required in OPSEDITCOL
//    QComboBox* cb = (QComboBox*)getValueAt(row,TurnoutTableAction::OPSONOFFCOL);
   //QComboBox* cb = self->makeAutomationBox(t);
   self->editTurnoutOperation(t, value.toString());
   fireTableRowsUpdated(row,row);
   return true;

   }
   case EDITCOL :
   {
#if 0
        class WindowMaker : public Runnable
        {
            Turnout* t;
            WindowMaker(Turnout* t){
                this.t = t;
            }
            /*public*/ void run() {
                    editButton(t);
                }
            };
        WindowMaker w = new WindowMaker(t);
        javax.swing.SwingUtilities.invokeLater(w);
#endif
        self->editButton(t, index);
        fireTableRowsUpdated(row,row);
        return true;
    }
    case LOCKOPRCOL:
    {
//     QString lockOpName =  ((QComboBox*) value)
//            ->getSelectedItem();
     QString lockOpName = value.toString();
     if (lockOpName==(self->bothText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
     }
     if (lockOpName==(self->cabOnlyText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT, true);
      t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, false);
     }
     if (lockOpName==(self->pushbutText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT, false);
      t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, true);
     }
     fireTableRowsUpdated(row,row);
     return true;
    }
    case LOCKDECCOL:
    {
//        QString decoderName = ((QComboBox*)value)->currentText();
//        t->setDecoderName(decoderName);
     t->setDecoderName(value.toString());
     fireTableRowsUpdated(row,row);
     return true;
    }
    case STRAIGHTCOL:
    {
//        QString speed = ((QComboBox*)value)->currentText();
//        try {
     t->setStraightSpeed(value.toString());
//        } catch (JmriException ex) {
//            //JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
//            QMessageBox::warning(NULL, tr("Warning"), ex.getMessage()+ "\n" + speed);
//            return;
//        }
     QString speed = value.toString();
     if ((!self->speedListClosed.contains(speed)) && !speed.contains("Global"))
     {
      self->speedListClosed.append(speed);
     }

     fireTableRowsUpdated(row,row);
     return true;
    }
    case DIVERGCOL:
    {

//    QString speed = ((QComboBox*)value)->currentText();
//    try
//    {
     t->setDivergingSpeed(value.toString());
//    }
//    catch (JmriException ex)
//    {
//     //JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + speed);
//        QMessageBox::warning(NULL, tr("Warning"), ex.getMessage()+ "\n" + speed);
//     return false;
//    }
     QString speed = value.toString();
    if ((!self->speedListThrown.contains(speed)) && !speed.contains("Global"))
    {
     self->speedListThrown.append(speed);
    }
    fireTableRowsUpdated(row,row);
    return true;
   }
  case FORGETCOL:
   t->setCommandedState(Turnout::UNKNOWN);
   break;
  case QUERYCOL:
   t->setCommandedState(Turnout::UNKNOWN);
   t->requestUpdateFromLayout();
   break;
  case VALUECOL:
   clickOn(t);
   fireTableRowsUpdated(row,row);
   break;
   default:
    break;
  }
 }
 return BeanTableDataModel::setData(index, value, role);
}

/*public*/ QString TurnoutTableDataModel::getValue(QString name) const
{
 TurnoutManager* manager = self->turnManager;
 Turnout* t;
 if(qobject_cast<AbstractProxyTurnoutManager*>(manager)!= NULL)
  t= ((ProxyTurnoutManager*)manager)->getBySystemName(name);
 else
  t= ((AbstractTurnoutManager*)manager)->getBySystemName(name);

 int val = t->getCommandedState();
 switch (val)
 {
  case Turnout::CLOSED: return self->closedText;
  case Turnout::THROWN: return self->thrownText;
  case Turnout::UNKNOWN: return tr("Unknown");
  case Turnout::INCONSISTENT: return tr("Inconsistent");
  default: return "Unexpected value: "+val;
 }
}
/*public*/ Manager* TurnoutTableDataModel::getManager() { return self->turnManager; }

/*public*/ NamedBean* TurnoutTableDataModel::getBySystemName(QString name) const
 {
  if(qobject_cast<AbstractProxyTurnoutManager*>(self->turnManager)!= NULL)
   return ((ProxyTurnoutManager*)self->turnManager)->getBySystemName(name);
  else
   return ((AbstractTurnoutManager*)self->turnManager)->getBySystemName(name);
 }

/*public*/ NamedBean* TurnoutTableDataModel::getByUserName(QString name)
 {
  if(qobject_cast<AbstractProxyTurnoutManager*>(self->turnManager)!= NULL)
     return ((ProxyTurnoutManager*)self->turnManager)->getByUserName(name);
  else
  return ((AbstractTurnoutManager*)self->turnManager)->getByUserName(name);
 }

/*protected*/ QString TurnoutTableDataModel::getMasterClassName() { return self->getClassName(); }


/*public*/ void TurnoutTableDataModel::clickOn(NamedBean* t)
{
 int state = ((Turnout*)t)->getCommandedState();
 if (state==Turnout::CLOSED) ((Turnout*)t)->setCommandedState(Turnout::THROWN);
 else ((Turnout*)t)->setCommandedState(Turnout::CLOSED);
}

//@Override
/*public*/ void TurnoutTableDataModel::configureTable(JTable* tbl) {
    _table = tbl; //??
    self->table = tbl;

//    table.setDefaultRenderer(bool.class, new EnablingCheckboxRenderer());
//    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
//    setColumnToHoldButton(table,TurnoutTableAction::OPSEDITCOL,editButton());
//    setColumnToHoldButton(table,TurnoutTableAction::EDITCOL,editButton());
    //Hide the following columns by default
    XTableColumnModel* columnModel = (XTableColumnModel*)_table->getColumnModel();
    _table->createDefaultColumnsFromModel();
    TableColumn* column  = columnModel->getColumnByModelIndex(STRAIGHTCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(DIVERGCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(KNOWNCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(MODECOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(SENSOR1COL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(SENSOR2COL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(OPSONOFFCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(OPSEDITCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(LOCKOPRCOL);
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(LOCKDECCOL);
    columnModel->setColumnVisible(column, false);
    setColumnToHoldButton(_table, EDITCOL);
    setColumnToHoldDelegate(_table, MODECOL, modeColDelegate = new TTComboBoxDelegate(QStringList(), self));
    sensorsColDelegate = new TTEditDelegate(self);
    setColumnToHoldDelegate(_table, SENSOR1COL, sensorsColDelegate);
    setColumnToHoldDelegate(_table, SENSOR2COL, sensorsColDelegate);
    //setColumnToHoldDelegate(_table, OPSONOFFCOL, opsOnOffColDelegate =  new TTComboBoxDelegate(QStringList(), self)); Each row needs it's own instance
    setColumnToHoldDelegate(_table, LOCKDECCOL, lockDecColDelegate = new TTComboBoxDelegate(QStringList(), self));
    setColumnToHoldDelegate(_table, LOCKOPRCOL, new TTComboBoxDelegate(self->lockOperations, self));
    setColumnToHoldDelegate(_table, STRAIGHTCOL, new TTComboBoxDelegate(self->speedListClosed.toList(), self,true));
    setColumnToHoldDelegate(_table, DIVERGCOL, new TTComboBoxDelegate(self->speedListClosed.toList(), self, true));
    setColumnToHoldDelegate(_table, OPSEDITCOL, opsEditColDelegate = new TTComboBoxDelegate(QStringList(),self)); // ?? shuld be button?
    setColumnToHoldButton(_table, FORGETCOL);
    setColumnToHoldButton(_table, QUERYCOL);
  //self->showFeedbackChanged();
  //self->showLockChanged();
  //self->showTurnoutSpeedChanged();
  //self->On_doAutomationBox_toggled(false);

  BeanTableDataModel::configureTable(_table);
}

// update table if turnout lock or feedback changes
//@Override
/*protected*/ bool TurnoutTableDataModel::matchPropertyName(PropertyChangeEvent* e)
 {
  if(e->getPropertyName() == "inverted") return true;
    if (e->getPropertyName()==("locked")) return true;
    if (e->getPropertyName()==("feedbackchange")) return true;
    if (e->getPropertyName()==("TurnoutDivergingSpeedChange")) return true;
    if (e->getPropertyName()==("TurnoutStraightSpeedChange")) return true;
    if (e->getPropertyName()==("KnownState")) return true;
    if (e->getPropertyName()==("CommandedState")) return true;
    else return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ void TurnoutTableDataModel::comboBoxAction(ActionEvent* /*e*/){
    if(log->isDebugEnabled()) log->debug("Combobox change");
//    if(table!=NULL && table->getCellEditor()!=NULL){
//        table->getCellEditor().stopCellEditing();
//    }
}

//@Override
/*public*/ void TurnoutTableDataModel::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("DefaultTurnoutClosedSpeedChange"))
 {
  self->updateClosedList();
 }
 else if (e->getPropertyName()==("DefaultTurnoutThrownSpeedChange"))
 {
  self->updateThrownList();
 }
 else
 {
   BeanTableDataModel::propertyChange(e);
 }
}

/*protected*/ QString TurnoutTableDataModel::getBeanType(){
    return tr("Turnout");
}

#if 0
TableSorter sorter;

/*public*/ JTable makeJTable(TableSorter srtr) {
    this.sorter = srtr;
    JTable table = new JTable(srtr)  {

        /**
         *
         */
        /*private*/ static /*final*/ long serialVersionUID = -3082196412648458792L;

        /*public*/ TableCellRenderer getCellRenderer(int row, int column) {
            //Convert the displayed index to the model index, rather than the displayed index
            int modelColumn = getColumnModel().getColumn(column).getModelIndex();
            if (modelColumn == SENSOR1COL || modelColumn == SENSOR2COL) {
                return getRenderer(row, modelColumn);
            } else
                return super.getCellRenderer(row, column);
        }
        /*public*/ TableCellEditor getCellEditor(int row, int column) {
            //Convert the displayed index to the model index, rather than the displayed index
            int modelColumn = getColumnModel().getColumn(column).getModelIndex();
            if (modelColumn == SENSOR1COL || modelColumn == SENSOR2COL) {
                return getEditor(row, modelColumn);
            } else
                return super.getCellEditor(row, column);
        }

        TableCellRenderer getRenderer(int row, int column) {
            TableCellRenderer retval = NULL;
            if(column==SENSOR1COL){
                retval = rendererMapSensor1.get(sorter.getValueAt(row,SYSNAMECOL));
            }
            else if (column==SENSOR2COL){
                retval = rendererMapSensor2.get(sorter.getValueAt(row,SYSNAMECOL));
            } else {
                return NULL;
            }

            if (retval == NULL) {
                Turnout* t = turnManager->getBySystemName(sorter.getValueAt(row,SYSNAMECOL));
                retval = new BeanBoxRenderer();
                if(column==SENSOR1COL){
                    ((JmriBeanComboBox)retval).setSelectedBean(t.getFirstSensor());
                    rendererMapSensor1.put(sorter.getValueAt(row,SYSNAMECOL), retval);
                }
                else {
                    ((JmriBeanComboBox)retval).setSelectedBean(t.getSecondSensor());
                    rendererMapSensor2.put(sorter.getValueAt(row,SYSNAMECOL), retval);
                }
            }
            return retval;
        }
        Hashtable<Object, TableCellRenderer> rendererMapSensor1 = new Hashtable<Object, TableCellRenderer>();
        Hashtable<Object, TableCellRenderer> rendererMapSensor2 = new Hashtable<Object, TableCellRenderer>();

        TableCellEditor getEditor(int row, int column) {
            TableCellEditor retval = NULL;
            if(column==SENSOR1COL)
                retval=editorMapSensor1.get(sorter.getValueAt(row,SYSNAMECOL));
            else if(column==SENSOR2COL)
                retval=editorMapSensor2.get(sorter.getValueAt(row,SYSNAMECOL));
            else
                return NULL;
            if (retval == NULL) {
                Turnout* t = turnManager->getBySystemName(sorter.getValueAt(row,SYSNAMECOL));

                JmriBeanComboBox c;

                if(column==SENSOR1COL){
                    c = new JmriBeanComboBox(InstanceManager::sensorManagerInstance(),t.getFirstSensor(), JmriBeanComboBox.DISPLAYNAME);
                    retval = new BeanComboBoxEditor(c);
                    editorMapSensor1.put(sorter.getValueAt(row,SYSNAMECOL), retval);
                }
                else { //Must be two
                    c = new JmriBeanComboBox(InstanceManager::sensorManagerInstance(),t.getSecondSensor(), JmriBeanComboBox.DISPLAYNAME);
                    retval = new BeanComboBoxEditor(c);
                    editorMapSensor2.put(sorter.getValueAt(row,SYSNAMECOL), retval);
                }
                c.setFirstItemBlank(true);
            }
            return retval;
        }
        Hashtable<Object, TableCellEditor> editorMapSensor1 = new Hashtable<Object, TableCellEditor>();
        Hashtable<Object, TableCellEditor> editorMapSensor2 = new Hashtable<Object, TableCellEditor>();
    };
    table.getTableHeader().setReorderingAllowed(true);
    table.setColumnModel(new XTableColumnModel());
    table.createDefaultColumnsFromModel();

    addMouseListenerToHeader(table);
    return table;
}
#endif
//};  // end of custom data model
//}

/*private*/ void TurnoutTableAction::updateClosedList(){
    speedListClosed.remove(speedListClosed.indexOf(defaultClosedSpeedText));
    defaultClosedSpeedText = ("Use Global " + turnManager->getDefaultClosedSpeed());
    speedListClosed.insert(0, defaultClosedSpeedText);
    m->fireTableDataChanged();
}

/*private*/ void TurnoutTableAction::updateThrownList(){
    speedListThrown.remove(speedListThrown.indexOf(defaultThrownSpeedText));
    defaultThrownSpeedText = ("Use Global " + turnManager->getDefaultThrownSpeed());
    speedListThrown.insert(0, defaultThrownSpeedText);
    m->fireTableDataChanged();
}

/*protected*/ void TurnoutTableAction::setTitle() {
    f->setTitle(f->tr("Turnout Table"));
}

//@Override
/*protected*/ QString TurnoutTableAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TurnoutTable";
}

/*protected*/ void TurnoutTableAction::addPressed(ActionEvent* /*e*/)
{
 //p = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");

 if (addFrame==NULL)
 {
  addFrame = new JmriJFrame(tr("Add Turnout"), false, true);
  addFrame->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
  addFrame->addHelpMenu("package.jmri.jmrit.beantable.TurnoutAddEdit", true);
  QWidget* centralWidget = new QWidget;
  centralWidget->resize(600,300);
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  addFrame->setCentralWidget(centralWidget);

//        ActionListener listener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    okPressed(e);
//                }
//            };
  OkListener* listener = new OkListener(this);
  ToCancelActionListener* cancelListener = new ToCancelActionListener(this);

//        ActionListener rangeListener = new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    canAddRange(e);
//                }
//            };
  RangeListener* rangeListener = new RangeListener(this);

  /* We use the proxy manager in this instance so that we can deal with
  duplicate usernames in multiple classes */
  //if (InstanceManager::turnoutManagerInstance() instanceof jmri.managers.AbstractProxyManager)
  if(qobject_cast<AbstractProxyTurnoutManager*>(InstanceManager::turnoutManagerInstance()) != NULL)
  {
   ProxyTurnoutManager* proxy = (ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance();
   QList<Manager*> managerList = proxy->getManagerList();
   for(int x = 0; x<managerList.size(); x++)
   {
    QString manuName = ConnectionNameFromSystemName::getConnectionName(managerList.at(x)->getSystemPrefix());
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
   prefixBox->addItem(ConnectionNameFromSystemName::getConnectionName(turnManager->getSystemPrefix()));
  }
  hardwareAddressTextField->setName("sysName");
  userNameTextField->setName("userName");
  prefixBox->setObjectName("prefixBox");
  addButton = new QPushButton(tr("Create"));
  connect(addButton, SIGNAL(clicked(bool)), this, SLOT(createPressed()));
  connect(hardwareAddressTextField, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  centralWidgetLayout->addWidget(new AddNewHardwareDevicePanel(hardwareAddressTextField, userNameTextField, prefixBox, numberToAddSpinner, rangeBox, addButton, cancelListener, rangeListener, statusBar));

  canAddRange(NULL);
 }
 hardwareAddressTextField->setValidator(validator=new TTAValidator(hardwareAddressTextField, this));

 addFrame->adjustSize();
 addFrame->setVisible(true);
}

/*public*/ void TurnoutTableAction::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
 QString property = propertyChangeEvent->getPropertyName();
 if ("background"==(property))
 {
  if ( propertyChangeEvent->getNewValue().value<QColor>() == QColor(Qt::white)) { // valid entry
      addButton->setEnabled(true);
  } else { // invalid
      addButton->setEnabled(false);
  }
 }
}


OkListener::OkListener(TurnoutTableAction *self)
{
 this->self = self;
}
void OkListener::actionPerformed(ActionEvent */*e*/)
{
 self->createPressed();
}
ToCancelActionListener::ToCancelActionListener(TurnoutTableAction *self) { this->self = self;}
void ToCancelActionListener::actionPerformed(ActionEvent *e)
{
 self->cancelPressed();
}

RangeListener::RangeListener(TurnoutTableAction *self)
{
 this->self = self;
}
void RangeListener::actionPerformed(ActionEvent */*e*/)
{
 self->canAddRange();
}

/**
 * Create a QComboBox* containing all the options for turnout automation parameters for
 * this turnout
 * @param t	the turnout
 * @return	the JComboBox
 */
/*protected*/ /*QComboBox**/QVector<QString>TurnoutTableAction::makeAutomationBox(Turnout* t, QModelIndex index) {
    QVector<QString> str = QVector<QString>();
    str << "empty";

//    /*final*/ QComboBox* cb = new QComboBox();
//    cb->addItems(str);
    /*final*/ Turnout* myTurnout = t;
    TurnoutTableAction::updateAutomationBox(t, str, index);
//TODO:
//    cb.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                setTurnoutOperation(myTurnout, cb);
//                cb.removeActionListener(this);		// avoid recursion
//                updateAutomationBox(myTurnout, cb);
//                cb.addActionListener(this);
//        }
//        });
//    CBActionListener* cbActionListener = new CBActionListener(cb,t, this);
//    connect(cb, SIGNAL(currentIndexChanged(int)), cbActionListener, SLOT(actionPerformed()));
//    return cb;
    return str;
}
//CBActionListener::CBActionListener(QComboBox *cb, Turnout* myTurnout, TurnoutTableAction *self)
//{
// this->cb = cb;
// this->self = self;
// this->myTurnout = myTurnout;
//}

//void CBActionListener::actionPerformed(ActionEvent *)
//{
//    self->setTurnoutOperation(myTurnout, cb);
//    //cb->removeActionListener(this);		// avoid recursion
//    disconnect(cb);
//    TurnoutTableAction::updateAutomationBox(myTurnout, cb);
//    //cb.addActionListener(this);
//    connect(cb, SIGNAL(currentIndexChanged(int)), this, SLOT(actionPerformed()));
//}

///**
// * Create a JButton to edit a turnout operation.
// * @return	the JButton
// */
///*protected*/ QPushButton* TurnoutTableAction::editButton() {
//    QPushButton* editButton = new QPushButton(tr("Edit Turnout Operation"));
//    return(editButton);
//}

/**
 * Add the content and make the appropriate selection to a combox box for a turnout's
 * automation choices
 * @param t	turnout
 * @param cb	the JComboBox
 */
/*public*/ /*static*/ void TurnoutTableAction::updateAutomationBox(Turnout* t, /*QComboBox* cb*/ QVector<QString> str, QModelIndex index)
{
 Logger* log = new Logger("TurnoutTableAction");
 QList<TurnoutOperation*> ops = TurnoutOperationManager::getInstance()->getTurnoutOperations();
 str.clear();
 QVector<QString> strings =  QVector<QString>(/*20*/);
 QVector<QString> defStrings =  QVector<QString>(/*20*/);

 if(log->isDebugEnabled()) log->debug("start "+QString::number(ops.length()));
 for (int i=0; i<ops.length(); ++i)
 {
  if(log->isDebugEnabled()) log->debug(QString("isDef ")+(ops[i]->isDefinitive()?"true":"false")+ " mFMM "+(ops[i]->matchFeedbackMode(t->getFeedbackMode())?"true":"false")+ " isNonce "+(ops[i]->isNonce()?"true":"false"));
  if (!ops[i]->isDefinitive()
            && ops[i]->matchFeedbackMode(t->getFeedbackMode())
            && !ops[i]->isNonce())
  {
   strings.append(ops[i]->getName());
  }
 }
 if(log->isDebugEnabled()) log->debug("end");
 for (int i=0; i<ops.length(); ++i)
 {
  if (ops[i]->isDefinitive()
            && ops[i]->matchFeedbackMode(t->getFeedbackMode())) {
            defStrings.append(ops[i]->getName());
        }
    }
//    java.util.Collections.sort(strings);
//    java.util.Collections.sort(defStrings);
    strings.insert(0, tr("Off"));
    strings.insert(1,tr("Use Global Default "));
    for (int i=0; i<defStrings.size(); ++i) {
        try {
            strings.insert(i+2,defStrings.at(i));
        } catch(ArrayIndexOutOfBoundsException obe){
            //	           strings.insertElementAt(defStrings.elementAt(i),i+2);
        }
    }
    for (int i=0; i<strings.size(); ++i)
    {
//        cb->addItem(strings.at(i));
     str.append(strings.at(i));
    }
    int row;

    TTComboBoxDelegate* delegate = (TTComboBoxDelegate*)((TurnoutTableDataModel*)index.model())->table()->itemDelegate(index);
    QString currTxt;
//    if (t->getInhibitOperation()) {
//        cb->setCurrentIndex(0);
    if(t->getInhibitOperation())
        currTxt = strings.at(0);
//    } else if (t->getTurnoutOperation() == NULL) {
//        cb->setCurrentIndex(1);
    else if(t->getTurnoutOperation() == nullptr)
        currTxt = strings.at(1);
//    } else if (t->getTurnoutOperation()->isNonce()) {
//        cb->setCurrentIndex(2);
    else if (t->getTurnoutOperation()->isNonce()) {
        currTxt= strings.at(2);
    }
//    } else {
//        cb->setCurrentIndex(cb->findText(t->getTurnoutOperation()->getName()));
//    }
    else
    {
        currTxt = t->getTurnoutOperation()->getName();
    }
    ((TTComboBoxDelegate*)delegate)->setItems(strings.toList(), currTxt);

}

/**
 * set the turnout's operation info based on the contents of the combo box
 * @param t	turnout
 * @param cb JComboBox
 */
/*protected*/ void TurnoutTableAction::setTurnoutOperation(Turnout* t,/* QComboBox* cb*/QString val)
{
// switch (cb->currentIndex())
// {
//  case 0:			// Off
 if(val == tr("Off"))
 {
   t->setInhibitOperation(true);
   t->setTurnoutOperation(NULL);
 }
//   break;
//  case 1:			// Default
 else
 if(val == tr("Use GlobalDefault"))
 {
   t->setInhibitOperation(false);
   t->setTurnoutOperation(NULL);
 }
//   break;
//  default:		// named operation
 else
 {
   t->setInhibitOperation(false);
   t->setTurnoutOperation(TurnoutOperationManager::getInstance()->
                         getOperation((/*cb->currentText()*/val )));
//   break;
 }
}

void TurnoutTableAction::editButton(Turnout* t, QModelIndex index){
    TurnoutEditAction* beanEdit = new TurnoutEditAction(index);
    beanEdit->setBean(t);
    beanEdit->actionPerformed(NULL);
}

/**
 * pop up a TurnoutOperationConfig for the turnout
 * @param t turnout
 * @param box JComboBox that triggered the edit
 */
/*protected*/ void TurnoutTableAction::editTurnoutOperation(Turnout* t, /*QComboBox* box*/QString val)
{
 TurnoutOperation* op = t->getTurnoutOperation();
 if (op==NULL)
 {
  TurnoutOperation* proto = TurnoutOperationManager::getInstance()->getMatchingOperationAlways(t);
  if (proto != NULL)
  {
   op = proto->makeNonce(t);
   t->setTurnoutOperation(op);
  }
 }

 if (op != NULL)
 {
  if (!op->isNonce()) op = op->makeNonce(t);
  // make and show edit dialog
  TurnoutOperationEditor* dialog = new TurnoutOperationEditor(this, f, op, t, val);
  dialog->setVisible(true);
 }
 else
 {
  //JOptionPane.showMessageDialog(f, "There is no operation type suitable for this turnout","No operation type", JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(f, tr("No operation type"), tr( "There is no operation type suitable for this turnout"));
 }
}
///*protected*/ static class TurnoutOperationEditor extends JDialog {
//    /**
//     *
//     */
//    /*private*/ static /*final*/ long serialVersionUID = 3523604197678096714L;
//    TurnoutOperationConfig config;
//    TurnoutOperation myOp;
//    Turnout* myTurnout;

TurnoutOperationEditor::TurnoutOperationEditor(TurnoutTableAction* /*tta*/, JFrame* parent, TurnoutOperation* op, Turnout* t, /*QComboBox* box*/QString /*val*/ ) : JDialog(parent)
{
 //super(parent);
 ///*final*/ TurnoutOperationEditor* self = this;
 myOp = op;
// myOp.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent evt) {
//                if (evt.getPropertyName()==("Deleted")) {
//                    setVisible(false);
//                }
//            }
//    });
 connect(myOp, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 myTurnout = t;
 config = TurnoutOperationConfig::getConfigPanel(op);
 setTitle();
 if (config != NULL)
 {
  //Box outerBox = Box.createVerticalBox();
  QFrame* outerBox = new QFrame;
  QVBoxLayout*outerBoxLayout = new QVBoxLayout;
  outerBox->setLayout(outerBoxLayout);
  outerBoxLayout->addWidget(config);
  //Box buttonBox = Box.createHorizontalBox();
  QFrame* buttonBox = new QFrame;
  QHBoxLayout* buttonBoxLayout = new QHBoxLayout;
  buttonBox->setLayout(buttonBoxLayout);
  QPushButton* nameButton = new QPushButton("Give name to this setting");
//        nameButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    QString newName = JOptionPane.showInputDialog("New name for this parameter setting:");
//                    if (newName != NULL && !newName==("")) {
//                        if (!myOp.rename(newName)) {
//                            JOptionPane.showMessageDialog(self, "This name is already in use",
//                                                          "Name already in use", JOptionPane.ERROR_MESSAGE);
//                        }
//                        setTitle();
//                        myTurnout::setTurnoutOperation(NULL);
//                        myTurnout::setTurnoutOperation(myOp);	// no-op but updates display - have to <i>change</i> value
//                    }
//                }
//            });
  connect(nameButton, SIGNAL(clicked()),this, SLOT(On_nameButton_clicked()));
  QPushButton* okButton = new QPushButton("OK");
//        okButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    config.endConfigure();
//                    if (myOp.isNonce() && myOp.equivalentTo(myOp.getDefinitive())) {
//                        myTurnout::setTurnoutOperation(NULL);
//                        myOp.dispose();
//                        myOp = NULL;
//                    }
//                    self.setVisible(false);
//                }
//            });
  connect(okButton, SIGNAL(clicked()), this, SLOT(On_okButton_clicked()));
  QPushButton* cancelButton = new QPushButton("Cancel");
//        cancelButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    self.setVisible(false);
//                }
//            });
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(On_cancelButton_clicked()));
  //buttonBox.add(Box.createHorizontalGlue());
  if (!op->isDefinitive())
  {
   buttonBoxLayout->addWidget(nameButton);
  }
  buttonBoxLayout->addWidget(okButton);
  buttonBoxLayout->addWidget(cancelButton);
  outerBoxLayout->addWidget(buttonBox);
  //getContentPane().add(outerBox);
  QVBoxLayout* thisLayout;
  setLayout(thisLayout = new QVBoxLayout);
  thisLayout->addWidget(outerBox);
 }
 adjustSize();
}
/*private*/ void TurnoutOperationEditor::setTitle()
{
 QString title = "Turnout Operation \"" + myOp->getName() + "\"";
 if (myOp->isNonce())
 {
  title = "Turnout operation for turnout " + myTurnout->getSystemName();
 }
 setWindowTitle(title);
}

void TurnoutOperationEditor::On_nameButton_clicked()
{
 //QString newName = JOptionPane.showInputDialog("New name for this parameter setting:");
 QString newName;
 InputDialog* dlg = new InputDialog("New name for this parameter setting:", " ");
 if(dlg->exec() == QDialog::Accepted)
 {
  newName = dlg->value();

  if (newName != "" )
  {
   if (!myOp->rename(newName))
   {
//    JOptionPane.showMessageDialog(self, "This name is already in use",
//                                                          "Name already in use", JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(this, tr("Name already in use"), tr("This name is already in use"));
   }
   setTitle();
   myTurnout->setTurnoutOperation(NULL);
   myTurnout->setTurnoutOperation(myOp);	// no-op but updates display - have to <i>change</i> value
  }
 }
}
void TurnoutOperationEditor::On_okButton_clicked()
{
 config->endConfigure();
 if (myOp->isNonce() && myOp->equivalentTo(myOp->getDefinitive()))
 {
  myTurnout->setTurnoutOperation(NULL);
  myOp->dispose();
  myOp = NULL;
 }
 setVisible(false);
}

void TurnoutOperationEditor::On_cancelButton_clicked()
{
 this->setVisible(false);
}
void TurnoutOperationEditor::propertyChange(PropertyChangeEvent *evt)
{
 if (evt->getPropertyName()==("Deleted"))
 {
  setVisible(false);
 }
}

//};

/*protected*/ void TurnoutTableAction::setDefaultSpeeds(JFrame* _who)
{
    QComboBox* thrownCombo = new QComboBox();
    thrownCombo->addItems(speedListThrown.toList());
    QComboBox* closedCombo = new QComboBox();
    closedCombo->addItems(speedListClosed.toList());
    thrownCombo->setEditable(true);
    closedCombo->setEditable(true);

    QWidget* thrown = new QWidget();
    QHBoxLayout* thrownLayout = new QHBoxLayout;
    thrown->setLayout(thrownLayout);
    thrownLayout->addWidget(new QLabel("Thrown Speed"));
    thrownLayout->addWidget(thrownCombo);

    QWidget* closed = new QWidget();
    QHBoxLayout* closedLayout = new QHBoxLayout;
    closed->setLayout(closedLayout);
    closedLayout->addWidget(new QLabel("Closed Speed"));
    closedLayout->addWidget(closedCombo);

    thrownCombo->removeItem(thrownCombo->findText(defaultThrownSpeedText));
    closedCombo->removeItem(closedCombo->findText(defaultClosedSpeedText));

    thrownCombo->setCurrentIndex(thrownCombo->findText(turnManager->getDefaultThrownSpeed()));
    closedCombo->setCurrentIndex(closedCombo->findText(turnManager->getDefaultClosedSpeed()));

//    int retval = JOptionPane.showOptionDialog(_who,
//                                      tr("TurnoutGlobalSpeedMessage") , tr("TurnoutGlobalSpeedMessageTitle"),
//                                      0, JOptionPane.INFORMATION_MESSAGE, NULL,
//                                      new Object[]{"Cancel", "OK", thrown, closed}, NULL );
//    if (retval != 1) {
//        return;
//    }
    QMessageBox* box = new QMessageBox(QMessageBox::Information, tr("Turnout Speeds"),tr("Select the default values for the speed through the turnout"),QMessageBox::Cancel | QMessageBox::Ok,_who);
    box->layout()->addWidget(thrown);
    box->layout()->addWidget(closed);
    int retval = box->exec();
    if(retval != QMessageBox::Ok)
     return;

    QString closedValue =  closedCombo->currentText();
    QString thrownValue =  thrownCombo->currentText();
    //We will allow the turnout manager to handle checking if the values have changed
    try {
        turnManager->setDefaultThrownSpeed(thrownValue);
    } catch (JmriException ex) {
//        JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + thrownValue);
    }

    try {
        turnManager->setDefaultClosedSpeed(closedValue);
    } catch (JmriException ex) {
//        JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + closedValue);
    }
}

/**
 * Add the check box and Operations menu item
 */
//@Override
/*public*/ void TurnoutTableAction::addToFrame(BeanTableFrame* f)
{
 f->addToBottomBox(showFeedbackBox, /*this.getClass().getName()*/ this->metaObject()->className());
 showFeedbackBox->setToolTip(tr("Show extra columns for configuring turnout feedback?"));
//    showFeedbackBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                showFeedbackChanged();
//            }
//        });
 showFeedbackBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showFeedback"));
 showFeedbackChanged();
 connect(showFeedbackBox, SIGNAL(toggled(bool)), this, SLOT(showFeedbackChanged()));
 f->addToBottomBox(showLockBox, /*this.getClass().getName()*/metaObject()->className());
 showLockBox->setToolTip(tr("Show extra columns for configuring turnout lock?"));
//    showLockBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                showLockChanged();
//            }
//        });
 showLockBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showLockBox"));
 showLockChanged();
 connect(showLockBox, SIGNAL(toggled(bool)), this, SLOT(showLockChanged()));
 showLockBox->setChecked(false);
 f->addToBottomBox(doAutomationBox, /*this.getClass().getName()*/metaObject()->className());
 //doAutomationBox->setChecked(TurnoutOperationManager::getInstance()->getDoOperations());

//    doAutomationBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                TurnoutOperationManager.getInstance().setDoOperations(doAutomationBox.isSelected());
//        }
//        });
 doAutomationBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".doAutomation"));
 On_doAutomationBox_toggled(doAutomationBox->isChecked());
 connect(doAutomationBox, SIGNAL(toggled(bool)), this, SLOT(On_doAutomationBox_toggled(bool)));
 //doAutomationBox->setChecked(false);
 f->addToBottomBox(showTurnoutSpeedBox, /*this.getClass().getName()*/metaObject()->className());
 showTurnoutSpeedBox->setToolTip(tr("Show extra columns for configuring turnout Speeds, when used with Signaling?"));
//    showTurnoutSpeedBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                showTurnoutSpeedChanged();
//            }
//        });
 showTurnoutSpeedBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showTurnoutSpeed"));
    connect(showTurnoutSpeedBox, SIGNAL(toggled(bool)), this, SLOT(showTurnoutSpeedChanged()));
    showTurnoutSpeedBox->setChecked(false);
}

//@Override
/*public*/ void TurnoutTableAction::addToPanel(AbstractTableTabAction* f)
{
 QString systemPrefix = ConnectionNameFromSystemName::getConnectionName(turnManager->getSystemPrefix());

 if (QString(turnManager->metaObject()->className()).contains("ProxyTurnoutManager"))
  systemPrefix = "All";
 f->addToBottomBox(showFeedbackBox, systemPrefix);
 showFeedbackBox->setToolTip(tr("Show extra columns for configuring turnout feedback?"));
//    showFeedbackBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                showFeedbackChanged();
//            }
//        });
 showFeedbackBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showFeedback"));
 showFeedbackChanged();
 connect(showFeedbackBox, SIGNAL(toggled(bool)), this, SLOT(showFeedbackChanged()));
 f->addToBottomBox(showLockBox, systemPrefix);
 showLockBox->setToolTip(tr("Show extra columns for configuring turnout lock?"));
 //    showLockBox.addActionListener(new ActionListener() {
 //            /*public*/ void actionPerformed(ActionEvent e) {
 //                showLockChanged();
 //            }
 //        });
 showLockBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showLockBox"));
 showLockChanged();
 connect(showLockBox, SIGNAL(toggled(bool)), this, SLOT(showLockChanged()));
 f->addToBottomBox(doAutomationBox, systemPrefix);
 //doAutomationBox->setChecked(TurnoutOperationManager::getInstance()->getDoOperations());
//    doAutomationBox.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                TurnoutOperationManager.getInstance().setDoOperations(doAutomationBox.isSelected());
//        }
//    });
 doAutomationBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".doAutomation"));
 On_doAutomationBox_toggled(doAutomationBox->isChecked());
 connect(doAutomationBox, SIGNAL(toggled(bool)), this, SLOT(On_doAutomationBox_toggled(bool)));
 f->addToBottomBox(showTurnoutSpeedBox, systemPrefix);
 showTurnoutSpeedBox->setToolTip(tr("Show extra columns for configuring turnout Speeds, when used with Signalling?"));
//    showTurnoutSpeedBox.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                showTurnoutSpeedChanged();
//            }
//        });
 showTurnoutSpeedBox->setChecked(p->getSimplePreferenceState(this->getClassName()+".showTurnoutSpeed"));
   showTurnoutSpeedChanged();
 connect(showTurnoutSpeedBox, SIGNAL(toggled(bool)), this, SLOT(showTurnoutSpeedChanged()));
}

void TurnoutTableAction::On_doAutomationBox_toggled(bool b)
{
 TurnoutOperationManager::getInstance()->setDoOperations(doAutomationBox->isChecked());
 p->setSimplePreferenceState(this->getClassName()+".doAutomation", b);
}

void TurnoutTableAction::showFeedbackChanged()
{
 bool showFeedback = showFeedbackBox->isChecked();
    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
//    TableColumn* column  = columnModel->getColumnByModelIndex(TurnoutTableDataModel::KNOWNCOL);
//    columnModel->setColumnVisible(column, showFeedback);
//    column  = columnModel->getColumnByModelIndex(MODECOL);
 table->setColumnHidden(TurnoutTableDataModel::MODECOL, !showFeedback);
//    columnModel->setColumnVisible(column, showFeedback);
//    column  = columnModel->getColumnByModelIndex(SENSOR1COL);
 table->setColumnHidden(TurnoutTableDataModel::SENSOR1COL, !showFeedback);
//    columnModel->setColumnVisible(column, showFeedback);
//    column  = columnModel->getColumnByModelIndex(SENSOR2COL);
 table->setColumnHidden(TurnoutTableDataModel::SENSOR2COL, !showFeedback);
//    columnModel->setColumnVisible(column, showFeedback);
//    column  = columnModel->getColumnByModelIndex(OPSONOFFCOL);
 table->setColumnHidden(TurnoutTableDataModel::OPSONOFFCOL, !showFeedback);
//    columnModel->setColumnVisible(column, showFeedback);
//    column  = columnModel->getColumnByModelIndex(OPSEDITCOL);
 table->setColumnHidden(TurnoutTableDataModel::OPSEDITCOL, !showFeedback);
//    columnModel->setColumnVisible(column, showFeedback);
 p->setSimplePreferenceState(this->getClassName()+".showFeedback", showFeedback);

}

void TurnoutTableAction::showLockChanged()
{
 bool showLock = showLockBox->isChecked();
    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
    TableColumn* column  = ((XTableColumnModel*)table->getColumnModel())->getColumnByModelIndex(TurnoutTableDataModel::LOCKDECCOL);
    table->setColumnHidden(TurnoutTableDataModel::LOCKDECCOL, !showLock);
//    columnModel->setColumnVisible(column, showLock);
//    column  = columnModel->getColumnByModelIndex(LOCKOPRCOL);
    table->setColumnHidden(TurnoutTableDataModel::LOCKOPRCOL, !showLock);
//    columnModel->setColumnVisible(column, showLock);
    p->setSimplePreferenceState(this->getClassName()+".showLockBox", showLock);
}

//bool showTurnoutSpeed = false;
/*public*/ void TurnoutTableAction::showTurnoutSpeedChanged()
{
    bool showTurnoutSpeed = showTurnoutSpeedBox->isChecked();
    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
    TableColumn* column  = ((XTableColumnModel*)table->getColumnModel())->getColumnByModelIndex(TurnoutTableDataModel::STRAIGHTCOL);
    table->setColumnHidden(TurnoutTableDataModel::STRAIGHTCOL, !showTurnoutSpeed);
//    columnModel->setColumnVisible(column, showTurnoutSpeed);
//    column  = columnModel->getColumnByModelIndex(DIVERGCOL);
    table->setColumnHidden(TurnoutTableDataModel::DIVERGCOL, !showTurnoutSpeed);
//    columnModel->setColumnVisible(column, showTurnoutSpeed);
    p->setSimplePreferenceState(this->getClassName()+".showTurnoutSpeed", showTurnoutSpeed);
}

//@Override
/*public*/ void TurnoutTableAction::setMenuBar(BeanTableFrame* f)
{
 /*final*/ JmriJFrame* /*final*/F = f;			// needed for anonymous ActionListener class
 QMenuBar* menuBar = f->menuBar();
 QList<QAction*> ol = menuBar->actions();
 QMenu* opsMenu = NULL;
 QMenu* speedMenu = NULL;
 for(int i=0; i < ol.count(); i++)
 {
  if(qobject_cast<QAction*>(ol.at(i))!= NULL )
  {
   QString title = ol.at(i)->text();
   QMenu* m = (QMenu*)ol.at(i);
   if(title == tr("Automation"))
   {
    opsMenu = ol.at(i)->menu();
    opsMenu->clear();
   }
   if(title == tr("Speeds"))
   {
    speedMenu = ol.at(i)->menu();
    speedMenu->clear();
   }
  }
 }
 if(opsMenu == NULL)
 {
  opsMenu = new QMenu(tr("Automation"));
  menuBar->addMenu(opsMenu);
 }
 QAction* item = new QAction("Edit...", this);
 opsMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//               new Tur noutOperationFrame(/*final*/F);
//        }
//        });
 ItemListener1* itemListener = new ItemListener1(F);
 connect(item, SIGNAL(triggered()), itemListener, SLOT(actionPerformed()));
 menuBar->addMenu(opsMenu);

 if(speedMenu == NULL)
 {
  speedMenu = new QMenu(tr("Speeds"));
  menuBar->addMenu(speedMenu);
 }
 item = new QAction("Defaults...", this);
 speedMenu->addAction(item);
//    item.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//                setDefaultSpeeds(/*final*/F);
//        }
//        });
 ItemListener2* itemListener2 = new ItemListener2(F,this);
 connect(item, SIGNAL(triggered()), itemListener2, SLOT(actionPerformed()));
}

ItemListener1::ItemListener1(JmriJFrame *F)
{
 this->F = F;
}

void ItemListener1::actionPerformed(ActionEvent */*e*/)
{
   new TurnoutOperationFrame(/*final*/F);
}
ItemListener2::ItemListener2(JmriJFrame *F, TurnoutTableAction* self)
{
 this->F = F;
 this->self = self;
}
void ItemListener2::actionPerformed(ActionEvent */*e*/)
{
 self->setDefaultSpeeds(/*final*/F);
}

void TurnoutTableAction::cancelPressed(ActionEvent* /*e*/) {
    addFrame->setVisible(false);
    addFrame->dispose();
    addFrame = NULL;
}

void TurnoutTableAction::createPressed(ActionEvent* /*e*/)
{
 // Test if bit already in use as a light
 //int iName=0;
 int numberOfTurnouts = 1;

 if(rangeBox->isChecked())
 {
  try
  {
   numberOfTurnouts = numberToAddSpinner->value();
  }
  catch (NumberFormatException ex)
  {
   log->error(QString("Unable to convert ") + QString::number(numberToAddSpinner->value()) + " to a number");
   ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showErrorMessage("Error","Number to turnouts to Add must be a number!",""+ex.getMessage(), "",true, false);
   return;
  }
 }
 if (numberOfTurnouts>=65)
 {
//        if(JOptionPane.showConfirmDialog(addFrame, "You are about to add " + numberOfTurnouts + " Turnouts into the configuration\nAre you sure?","Warning", JOptionPane.YES_NO_OPTION)==1)
  if(QMessageBox::warning(addFrame, tr("Warning"), "You are about to add " + QString::number(numberOfTurnouts) + " Turnouts into the configuration\nAre you sure?",QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
   return;
 }

 QString sName = NULL;
 QString curAddress = hardwareAddressTextField->text().trimmed();
 // initial check for empty entry
 if (curAddress.length() < 1)
 {
   statusBar->setText(tr("You must provide a Hardware Address to start."));
   statusBar->setStyleSheet("QLabel { color: red}");
   hardwareAddressTextField->setStyleSheet("QLabel { background-color: red}");
   addButton->setEnabled(false);
   return;
 }
 else
 {
  hardwareAddressTextField->setStyleSheet("QLabel { background-color: white}");
  addButton->setEnabled(true);
 }

 // Add some entry pattern checking, before assembling sName and handing it to the turnoutManager
 QString statusMessage = tr("New %1(s) added:").arg(tr("Turnout"));
 QString errorMessage = "";
 QString lastSuccessfulAddress = tr("NONE");
 int iType = 0;
 int iNum=1;
 bool useLastBit = false;
 bool useLastType = false;
 QString prefix = ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText());
 for (int x = 0; x < numberOfTurnouts; x++)
 {
  try
  {
   curAddress = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getNextValidAddress(curAddress, prefix);
  }
  catch (JmriException ex)
  {
   ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
                   showErrorMessage("Error","Unable to convert '" + curAddress + "' to a valid Hardware Address",""+ex.getMessage(), "",true, false);
   // directly add to statusBar (but never called?)
   statusBar->setText(tr("Error Converting HW address %1").arg(curAddress));
   statusBar->setStyleSheet("QLabel { color: red}");
   return;
  }
  if (curAddress=="")
  {
   //The next address is already in use, therefore we stop.
   log->debug(tr("Error converting HW or getNextValidAddress"));
   errorMessage = (tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip)."));
   statusBar->setStyleSheet("QLabel { color: red}");
   // The next address returned an error, therefore we stop this attempt and go to the next address.
   break;
  }
  //We have found another turnout with the same address, therefore we need to go onto the next address.
  sName=prefix+InstanceManager::turnoutManagerInstance()->typeLetter()+curAddress;
  QString testSN = prefix+"L"+curAddress;
  Light* testLight = ((ProxyLightManager*)InstanceManager::lightManagerInstance())->
          getBySystemName(testSN);
  if (testLight != NULL)
  {
   // Address is already used as a Light
   log->warn("Requested Turnout "+sName+" uses same address as Light "+testSN);
   if (!noWarn)
   {
//                int selectedValue = JOptionPane.showOptionDialog(addFrame,
//                                                tr("TurnoutWarn1")+" "+sName+" "+tr("TurnoutWarn2")+" "+
//                                                testSN+".\n   "+tr("TurnoutWarn3"),tr("WarningTitle"),
//                                                JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE,NULL,
//                                                new Object[]{tr("ButtonYes"),tr("ButtonNo"),
//                                                            tr("ButtonYesPlus")},tr("ButtonNo"));
    QMessageBox* msgBox = new QMessageBox(tr("Warning"), tr("Warning - Requested Turnout")+" "+sName+" "+tr("uses same address as Light")+" "+ testSN+".\n   " +tr("Do you still want to add this Turnout?"),QMessageBox::Warning,QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    QPushButton* buttonYesPlus = new QPushButton(tr("Yes - Stop Warnings"));
    msgBox->addButton(buttonYesPlus, QMessageBox::ActionRole);
    int selectedValue= msgBox->exec();
    if (selectedValue == QMessageBox::No)
    {
     // Show error message in statusBar
     errorMessage = tr("Turnout \"%1\" not created as name matched a Light").arg(sName);
     statusBar->setText(errorMessage);
     statusBar->setStyleSheet("QLabel { color: gray}");
     return;   // return without creating if "No" response
    }
    if (msgBox->clickedButton() == buttonYesPlus)
    {
     // Suppress future warnings, and continue
     noWarn = true;
    }
   }
  }
  // Ask about two bit turnout control if appropriate

  if(!useLastBit)
  {
   iNum = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->askNumControlBits(sName);
   if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isNumControlBitsSupported(sName)) && (rangeBox->isChecked()))
   {
//                if(JOptionPane.showConfirmDialog(addFrame,
//                                             "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
//                                             JOptionPane.YES_NO_OPTION)==0)
       if(QMessageBox::question(addFrame, tr("Use Setting"), tr("Do you want to use the last setting for all turnouts in this range?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
           useLastBit=true;
       // Add a pop up here asking if the user wishes to use the same value for all
   }
   else
   {
   //as isNumControlBits is not supported, then we will always use the same value.
       useLastBit=true;
   }
  }
  if (iNum==0)
  {
   // User specified more bits, but bits are not available - return without creating
   // Display message in statusBar
   errorMessage = tr("2 Bits requested but not supported. Stopped after \"%1\".").arg( lastSuccessfulAddress);
   statusBar->setText(errorMessage);
   statusBar->setStyleSheet("QLabel { color: red}");
   return;
  }
  else
  {
   // Create the new turnout
   Turnout* t;
   try
   {
    t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(sName);
   }
   catch (IllegalArgumentException ex)
   {
    // user input no good
    handleCreateException(sName);
    // add to statusBar as well
    errorMessage = tr("Requested Turnout(s) were not created. Check your entry against pattern (see ToolTip).");
    statusBar->setText(errorMessage);
    statusBar->setStyleSheet("QLabel { color: red}");
    return; // without creating
   }

   if (t != NULL)
   {
    QString user = userNameTextField->text();
    if ((x!=0) && user != NULL && user!=(""))
     user = user+":"+x;
    if (user != NULL && user!=("") && (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getByUserName(user)==NULL)) t->setUserName(user);

    else if (((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getByUserName(user)!=NULL && !p->getPreferenceState(getClassName(), "duplicateUserName"))
    {
     ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->
     showErrorMessage("Duplicate UserName","The username " + user + " specified is already in use and therefore will not be set", getClassName(), "duplicateUserName", false, true);
     //p.showErrorMessage("Duplicate UserName", "The username " + user + " specified is already in use and therefore will not be set", userNameError, "", false, true);
    }
    t->setNumberOutputBits(iNum);
    // Ask about the type of turnout control if appropriate
    if(!useLastType)
    {
     iType = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->askControlType(sName);
     if((((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->isControlTypeSupported(sName)) && (rangeBox->isChecked()))
     {
//                        if (JOptionPane.showConfirmDialog(addFrame,
//                                             "Do you want to use the last setting for all turnouts in this range? ","Use Setting",
//                                             JOptionPane.YES_NO_OPTION)==0)// Add a pop up here asking if the user wishes to use the same value for all
      if(QMessageBox::question(addFrame, tr("Use Setting"), tr("Do you want to use the last setting for all turnouts in this range?"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
       useLastType=true;
     }
     else
     {
      useLastType = true;
     }
    }
    t->setControlType(iType);
   }
  }
 }
 // provide feedback to user
 if (errorMessage == "") {
     statusBar->setText(statusMessage);
     statusBar->setStyleSheet("QLabel { color: gray}");
 }
 else
 {
  statusBar->setText(errorMessage);
     // statusBar.setForeground(Color.red); // handled when errorMassage is set, to differentiate in urgency
 }
 p->addComboBoxLastSelection(systemSelectionCombo,  prefixBox->currentText());
 addFrame->setVisible(false);
 addFrame->dispose();
 addFrame = nullptr;
 //addButton.removePropertyChangeListener(colorChangeListener);
}

/*private*/ void TurnoutTableAction::canAddRange(ActionEvent* /*e*/){
    rangeBox->setEnabled(false);
    rangeBox->setChecked(false);
    connectionChoice = prefixBox->currentText(); // store in Field for CheckedTextField
    if (connectionChoice == "") {
        // Tab All or first time opening, use default tooltip
        connectionChoice = "TBD";
    }
    if (QString(turnManager->metaObject()->className()).contains("ProxyTurnoutManager"))
    {
        ProxyTurnoutManager* proxy = (ProxyTurnoutManager*) turnManager;
        QList<Manager*> managerList = proxy->getManagerList();
        QString systemPrefix = ConnectionNameFromSystemName::getPrefixFromName( connectionChoice);
        for(int x = 0; x<managerList.size(); x++){
            TurnoutManager* mgr = (TurnoutManager*) managerList.at(x);
            if (mgr->getSystemPrefix()==(systemPrefix) && mgr->allowMultipleAdditions(systemPrefix)){
                rangeBox->setEnabled(true);
                return;
            }
        }
    }
    else if (turnManager->allowMultipleAdditions(ConnectionNameFromSystemName::getPrefixFromName( prefixBox->currentText())))
    {
     rangeBox->setEnabled(true);
     log->debug("T Add box enabled2");
     // get tooltip from turnout manager
     addEntryToolTip = turnManager->getEntryToolTip();
     log->debug("TurnoutManager tip");
    }
    // show sysName (HW address) field tooltip in the Add Turnout pane that matches system connection selected from combobox
    hardwareAddressTextField->setToolTip("<html>"
            + tr("For %1 %2 use one of these patterns:").arg(connectionChoice).arg(tr("Turnouts"))
            + "<br>" + addEntryToolTip + "</html>");
    hardwareAddressTextField->setBackground(QColor(Qt::yellow)); // reset
    addButton->setEnabled(true); // ambiguous, so start enabled
}

void TurnoutTableAction::handleCreateException(QString sysName)
{
//    JOptionPane.showMessageDialog(addFrame,
//            java.text.MessageFormat.format(
//                tr("ErrorTurnoutAddFailed"),
//                new Object[] {sysName}),
//            tr("ErrorTitle"),
//            javax.swing.JOptionPane.ERROR_MESSAGE);
    QMessageBox::critical(addFrame, tr("Error"), tr("Could not create turnout \"%1\" to add it. Check that number/name is OK.").arg(sysName));
}


/*protected*/ QString TurnoutTableAction::getClassName() { return "jmri.jmrit.beantable.TurnoutTableAction"; }

//@Override
/*public*/ void TurnoutTableAction::setMessagePreferencesDetails()
{
    ((UserPreferencesManager*)   InstanceManager::getDefault("UserPreferencesManager"))->preferenceItemDetails(getClassName(), "duplicateUserName", tr("Hide Duplicate User Name Warning Message"));
    AbstractTableAction::setMessagePreferencesDetails();
}

//@Override
/*public*/ QString TurnoutTableAction::getClassDescription() { return tr("Turnout Table"); }
#if 0
static class BeanBoxRenderer extends JmriBeanComboBox implements TableCellRenderer {
    /**
     *
     */
    /*private*/ static /*final*/ long serialVersionUID = 7351045146446284915L;

    /*public*/ BeanBoxRenderer() {
        super(InstanceManager::sensorManagerInstance());
        setFirstItemBlank(true);
    }

    /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
        bool isSelected, bool hasFocus, int row, int column) {
        if (isSelected) {
            setForeground(table.getSelectionForeground());
            super.setBackground(table.getSelectionBackground());
        } else {
            setForeground(table.getForeground());
            setBackground(table.getBackground());
        }
        if(value instanceof NamedBean)
            setSelectedBean((NamedBean)value);
        else
            setSelectedBean(NULL);
        return this;
    }
}

static class BeanComboBoxEditor extends DefaultCellEditor {
    /**
     *
     */
    /*private*/ static /*final*/ long serialVersionUID = 1705620352249335223L;

    /*public*/ BeanComboBoxEditor(JmriBeanComboBox beanBox) {
        super(beanBox);
    }
}
#endif
QString TurnoutTableAction::getName() { return "jmri.jmrit.beantable.TurnoutTableAction";}

TTComboBoxDelegate::TTComboBoxDelegate(QStringList items, TurnoutTableAction *self, bool editable, QObject */*parent*/)
{
 this->items  = items;
 this->self = self;
 this->editable = editable;

}
QWidget* TTComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
 QComboBox* editor = new QComboBox(parent);
 editor->setEditable(editable);
 editor->addItems(items);
 return editor;
}
void TTComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
 QComboBox *comboBox = static_cast<QComboBox*>(editor);
 int value = index.model()->data(index, Qt::EditRole).toUInt();
 comboBox->setCurrentIndex(value);
}
void TTComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QComboBox *comboBox = static_cast<QComboBox*>(editor);
  model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void TTComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

void TTComboBoxDelegate::setItems(QStringList items, QString /*current*/)
{
 this->items = items;
}

TTEditDelegate::TTEditDelegate(TurnoutTableAction *self)
{
 this->self = self;
}
QWidget* TTEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
 QStringList sensors = InstanceManager::sensorManagerInstance()->getSystemNameList();
 qSort(sensors.begin(), sensors.end(), SystemNameComparator::compare);

 QLineEdit* editor = new QLineEdit(parent);
 QCompleter* completer = new QCompleter(sensors);
 completer->setCaseSensitivity(Qt::CaseInsensitive);
 editor->setCompleter(completer);
 return editor;
}
void TTEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
 QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
 QString value = index.model()->data(index, Qt::EditRole).toString();
 //comboBox->setCurrentIndex(value);
 lineEdit->setText(value);
}
void TTEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
  model->setData(index, lineEdit->text(), Qt::EditRole);
}

void TTEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}
TTAValidator::TTAValidator(JTextField *fld, TurnoutTableAction *act)
{
 this->fld = fld;
 this->act = act;
 connect(act->prefixBox, SIGNAL(currentTextChanged(QString)), this, SLOT(prefixBoxChanged(QString)));
 prefix = ConnectionNameFromSystemName::getPrefixFromName(act->connectionChoice);
 mark = ColorUtil::stringToColor("orange");
}

QValidator::State TTAValidator::validate(QString& s, int& pos) const
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
  fld->setBackground(mark);
  return QValidator::Invalid;
 }
}

void TTAValidator::setPrefix(QString prefix) { this->prefix = prefix;}

void TTAValidator::prefixBoxChanged(QString txt)
{
 prefix = ConnectionNameFromSystemName::getPrefixFromName(txt);
}
