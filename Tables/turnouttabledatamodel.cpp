#include "turnouttabledatamodel.h"
#include "beantabledatamodel.h"
#include "turnoutmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "signalspeedmap.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "abstractsensor.h"
#include "joptionpane.h"
#include "turnoutoperationeditordialog.h"
#include "jcombobox.h"
#include "turnouttableaction.h"
#include "imageio.h"
#include "xtablecolumnmodel.h"
#include <QHeaderView>
#include "turnouteditaction.h"
#include "file.h"
#include "bufferedimage.h"
#include "guilafpreferencesmanager.h"
#include "fileutil.h"
#include "jmriexception.h"

/**
 *
 */
// /*private*/ static /*final*/ long serialVersionUID = -8822546005900067212L;
TurnoutTableDataModel::TurnoutTableDataModel(QObject *parent)
    : BeanTableDataModel(parent)
{
// this->turnoutTableAction = self;
 common();
 setObjectName("TurnoutTableDataModel");
 init();
}

/*private*/ void TurnoutTableDataModel:: common()
{
 setObjectName("TurnoutTableDataModel");
 rootPath = FileUtil::getProgramPath() + "resources/icons/misc/switchboard/"; // also used in display.switchboardEditor
 beanTypeChar = 'T'; // for Turnout
 onIconPath = rootPath + beanTypeChar + "-on-s.png";
 offIconPath = rootPath + beanTypeChar + "-off-s.png";
}

/*public*/ TurnoutTableDataModel::TurnoutTableDataModel(Manager* mgr, QObject* parent) : BeanTableDataModel(parent){
    //super();
 common();
 setObjectName(QString("TurnoutTableDataModel") + " " + mgr->mself()->metaObject()->className());
 saveManager = mgr;
 setManager(mgr);
 init();
 initTable();
 //updateNameList();
}

/*private*/ void TurnoutTableDataModel::initTable() {

    // load graphic state column display preference
    _graphicState = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isGraphicTableState();

    QObject* o = turnoutManager->mself();
    //if(qobject_cast<AbstractManager*>(turnoutManager->self()) != nullptr)
    if(QString(o->metaObject()->className())== "ProxyTurnoutManager")
 //    return (Turnout*)((AbstractManager*)turnoutManager->self())->getBySystemName(name);
    {
     closedText = ((ProxyTurnoutManager*)o)->getClosedText();
     thrownText = ((ProxyTurnoutManager*)o)->getThrownText();

     //This following must contain the word Global for a correct match in the abstract turnout
     defaultThrownSpeedText = (tr("Use %1").arg("Global") + " " + ((ProxyTurnoutManager*)o)->getDefaultThrownSpeed());
     defaultClosedSpeedText = (tr("Use %1").arg("Global") + " " + ((ProxyTurnoutManager*)o)->getDefaultClosedSpeed());
    }
    else
    {
     closedText = ((AbstractTurnoutManager*)o)->getClosedText();
     thrownText = ((AbstractTurnoutManager*)o)->getThrownText();

     //This following must contain the word Global for a correct match in the abstract turnout
     defaultThrownSpeedText = (tr("Use %1").arg("Global") + " " + ((AbstractTurnoutManager*)o)->getDefaultThrownSpeed());
     defaultClosedSpeedText = (tr("Use %1").arg("Global") + " " + ((AbstractTurnoutManager*)o)->getDefaultClosedSpeed());

    }
    //This following must contain the word Block for a correct match in the abstract turnout
    useBlockSpeed = tr("Use %1").arg("Block Speed");

    speedListClosed.append(defaultClosedSpeedText);
    speedListThrown.append(defaultThrownSpeedText);
    speedListClosed.append(useBlockSpeed);
    speedListThrown.append(useBlockSpeed);
    QVector<QString> _speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getValidSpeedNames();
    for (QString s : _speedMap) {
        if (!speedListClosed.contains(s)) {
            speedListClosed.append(s);
        }
        if (!speedListThrown.contains(s)) {
            speedListThrown.append(s);
        }
    }

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
    case SENSOR1COL: return "Sensor1";
    case SENSOR2COL: return "Sensor2";
    case OPSONOFFCOL: return "Automate";
    case OPSEDITCOL: return "";
    case LOCKOPRCOL: return "Lock Mode";
    case LOCKDECCOL: return "Decoder";
    case DIVERGCOL: return "Thrown Speed";
    case STRAIGHTCOL: return "Closed Speed";
    case FORGETCOL: return "Forget";
    case QUERYCOL: return "Query";
    case EDITCOL: return "";
    default:
      break;
  }
 }
 return BeanTableDataModel::headerData(section,orientation, role);
}

//@Override
/*public*/ QString TurnoutTableDataModel::getColumnClass(int col) const {
    if (col==TurnoutTableDataModel::INVERTCOL) return "Boolean";
    if (col==TurnoutTableDataModel::LOCKCOL) return "Boolean";
    if (col==TurnoutTableDataModel::KNOWNCOL) return "String";
    if (col==TurnoutTableDataModel::MODECOL) return "JComboBox";
    if (col==TurnoutTableDataModel::SENSOR1COL) return "JComboBox";
    if (col==TurnoutTableDataModel::SENSOR2COL) return "JComboBox";
    if (col==TurnoutTableDataModel::OPSONOFFCOL) return "JComboBox";
    if (col==TurnoutTableDataModel::OPSEDITCOL) return "JButton";
    if (col==TurnoutTableDataModel::EDITCOL) return "JButton";
    if (col==TurnoutTableDataModel::LOCKOPRCOL)  return "JComboBox";
    if (col==TurnoutTableDataModel::LOCKDECCOL) return "JComboBox";
    if (col==TurnoutTableDataModel::DIVERGCOL) return "JComboBox";
    if (col==TurnoutTableDataModel::STRAIGHTCOL) return "JComboBox";
    if (col == FORGETCOL) return "JButton";
    if (col == QUERYCOL) return "JButton";
    if (col == VALUECOL && _graphicState) return "JLabel"; // use an image to show turnout state
    return BeanTableDataModel::getColumnClass(col);
}

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
  case FORGETCOL: return  JButton(tr("Forget")).sizeHint().width();
  case QUERYCOL: return JButton(tr("Query")).sizeHint().width();
  case VALUECOL:
  {
   if(_graphicState)
   {
    return JTextField(22).getPreferredSize().width() + offIcon.width();
   }
  }
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
     return Qt::ItemFlag::NoItemFlags;
 Turnout* t = (Turnout*)turnoutManager->getBySystemName(sysNameList.at(row))->self();
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
// //TurnoutManager* manager = turnoutManager;
// QObject* tto = turnoutManager->self();
// Turnout* t = (Turnout*)turnoutManager->getBySystemName(name);
 Turnout* t = getBySystemName(name);
 if (t == NULL)
 {
  log->debug("error NULL turnout!");
  return "error";
 }
// if(qobject_cast<AbstractTurnout*>(t->self()) == NULL)
//  return QVariant();
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
   case VALUECOL:
   {
    switch(t->getKnownState())
    {
     case Turnout::CLOSED:
     return tr("Closed");
    case Turnout::THROWN:
     return tr("Thrown");
    case Turnout::UNKNOWN:
     return tr("Unknown");
    case Turnout::INCONSISTENT:
    default:
     return tr("Inconsistent");
    }
   }
   case KNOWNCOL:
   {
    if (t->getKnownState()==Turnout::CLOSED) return closedText;
    if (t->getKnownState()==Turnout::THROWN) return thrownText;
    if (t->getKnownState()==Turnout::INCONSISTENT) return "Inconsistent";
    else return "Unknown";
   }
   case MODECOL:
   {

//    JComboBox* c = new JComboBox();
//    c->addItems(t->getValidFeedbackNames());
//    c->setCurrentIndex(c->findText(t->getFeedbackModeName()));
//        c.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                comboBoxAction(e);
//            }
//        });

      //     return c;
     //modeColDelegate->setItems( t->getValidFeedbackNames().toList(), t->getFeedbackModeName());
//     QAbstractItemDelegate* delegate = _table->itemDelegate(index);
//     if(qobject_cast<TTComboBoxDelegate*>(delegate) != nullptr)
//      ((TTComboBoxDelegate*)delegate)->setItems( t->getValidFeedbackNames().toList(), t->getFeedbackModeName());
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
      if(t->getTurnoutOperation() == nullptr)
       return QString();
      QString currValue = t->getTurnoutOperation()->getName();
     return currValue;
    }
    case OPSEDITCOL:
    {
     return tr("Edit Auto");
    }
    case EDITCOL:
    {
     return tr("Edit");
    }
    case  LOCKDECCOL:
    {
//        JComboBox* c = new JComboBox();
//        c->addItems(t->getValidDecoderNames());
//        c->setCurrentIndex(c->findText( t->getDecoderName()));
//        c.addActionListener(new ActionListener(){
//            /*public*/ void actionPerformed(ActionEvent e) {
//                comboBoxAction(e);
//            }
//        });
//        return c;
      //lockDecColDelegate->setItems(t->getValidDecoderNames(), t->getDecoderName());
      return t->getDecoderName();
    }
    case   LOCKOPRCOL:
    {
//        JComboBox* c = new JComboBox();
//        c->addItems(self->lockOperations);
   if(table)
   {
     JComboBoxEditor* delegate = (JComboBoxEditor*)table->getCellEditor(row, index.column());
     QVector<QString> lockOperations = QVector<QString>();  // Vector is a JComboBox ctor; List is not
     int modes = t->getPossibleLockModes();
     if ((modes & Turnout::CABLOCKOUT) != 0 && (modes & Turnout::PUSHBUTTONLOCKOUT) != 0) {
         lockOperations.append(bothText);
     }
     if ((modes & Turnout::CABLOCKOUT) != 0) {
         lockOperations.append(cabOnlyText);
     }
     if ((modes & Turnout::PUSHBUTTONLOCKOUT) != 0) {
         lockOperations.append(pushbutText);
     }
     lockOperations.append(noneText);

     delegate->setValues(lockOperations.toList());
    }
    if (t->canLock(Turnout::CABLOCKOUT) && t->canLock(Turnout::PUSHBUTTONLOCKOUT))
    {
 //            c->setCurrentIndex(c->findText(self->bothText));
     return bothText;
    }
    else if (t->canLock(Turnout::PUSHBUTTONLOCKOUT))
    {
 //            c->setCurrentIndex( c->findText(self->pushbutText));
     return pushbutText;

    }
    else if (t->canLock(Turnout::CABLOCKOUT))
    {
 //            c->setCurrentIndex( c->findText(self->cabOnlyText));
     return cabOnlyText;
    }
    else
    {
 //            c->setCurrentIndex(c->findText(self->noneText));
     return noneText;
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
//        JComboBox* c = new JComboBox();
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
//        JComboBox* c = new JComboBox();
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
 if(_graphicState && role == Qt::DecorationRole)
 {
  int col = index.column();

  if(col == VALUECOL)
  {
   switch (t->getState()) {
   case Turnout::THROWN:
    return offIcon;
   case Turnout::CLOSED:
    return onIcon;
   case Turnout::INCONSISTENT:
   break;
   default:
    return QColor(Qt::red);
    //break;
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
 TurnoutManager* manager = turnoutManager;
 AbstractTurnout* t;
 if(qobject_cast<ProxyTurnoutManager*>(manager->mself())!= NULL)
  t = (AbstractTurnout*)((ProxyTurnoutManager*)manager)->AbstractProxyManager::getBySystemName(name)->self();
 else
  t = (AbstractTurnout*)((AbstractTurnoutManager*) manager)->getBySystemName(name)->self();

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
//    QString modeName = ((JComboBox*)value)->currentText();
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
    catch (JmriException* e)
    {
     JOptionPane::showMessageDialog(NULL, e->toString());
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
    catch (JmriException* e)
    {
     JOptionPane::showMessageDialog(NULL, e->toString());
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
//    //@SuppressWarnings("unchecked") // cast to JComboBox* required in OPSEDITCOL
//    JComboBox* cb = (JComboBox*)getValueAt(row,TurnoutTableAction::OPSONOFFCOL);
   //JComboBox* cb = self->makeAutomationBox(t);
//   editTurnoutOperation(t, value);
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
        editButton(t/*, index*/);
        fireTableRowsUpdated(row,row);
        return true;
    }
    case LOCKOPRCOL:
    {
//     QString lockOpName =  ((JComboBox*) value)
//            ->getSelectedItem();
     QString lockOpName = value.toString();
     if (lockOpName==(bothText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
     }
     if (lockOpName==(cabOnlyText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT, true);
      t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, false);
     }
     if (lockOpName==(pushbutText))
     {
      t->enableLockOperation(Turnout::CABLOCKOUT, false);
      t->enableLockOperation(Turnout::PUSHBUTTONLOCKOUT, true);
     }
     fireTableRowsUpdated(row,row);
     return true;
    }
    case LOCKDECCOL:
    {
//        QString decoderName = ((JComboBox*)value)->currentText();
//        t->setDecoderName(decoderName);
     t->setDecoderName(value.toString());
     fireTableRowsUpdated(row,row);
     return true;
    }
    case STRAIGHTCOL:
    {
//        QString speed = ((JComboBox*)value)->currentText();
//        try {
     t->setStraightSpeed(value.toString());
//        } catch (JmriException* ex) {
//            //JOptionPane.showMessageDialog(NULL, ex->getMessage() + "\n" + speed);
//            QMessageBox::warning(NULL, tr("Warning"), ex->getMessage()+ "\n" + speed);
//            return;
//        }
     QString speed = value.toString();
     if ((!speedListClosed.contains(speed)) && !speed.contains("Global"))
     {
      speedListClosed.append(speed);
     }

     fireTableRowsUpdated(row,row);
     return true;
    }
    case DIVERGCOL:
    {

//    QString speed = ((JComboBox*)value)->currentText();
//    try
//    {
     t->setDivergingSpeed(value.toString());
//    }
//    catch (JmriException* ex)
//    {
//     //JOptionPane.showMessageDialog(NULL, ex->getMessage() + "\n" + speed);
//        QMessageBox::warning(NULL, tr("Warning"), ex->getMessage()+ "\n" + speed);
//     return false;
//    }
     QString speed = value.toString();
    if ((!speedListThrown.contains(speed)) && !speed.contains("Global"))
    {
     speedListThrown.append(speed);
    }
    fireTableRowsUpdated(row,row);
    return true;
   }
  case FORGETCOL:
   t->setCommandedState(Turnout::UNKNOWN);
   fireTableRowsUpdated(row,row);
   break;
  case QUERYCOL:
   t->setCommandedState(Turnout::UNKNOWN);
   t->requestUpdateFromLayout();
   fireTableRowsUpdated(row,row);
   break;
  case VALUECOL:
   if (_graphicState) { // respond to clicking on ImageIconRenderer CellEditor
    clickOn(t);
   fireTableRowsUpdated(row,row);
   break;
   }
   default:
   return BeanTableDataModel::setData(index, value, role);
  }
 }
 return true;
}

/*public*/ QString TurnoutTableDataModel::getValue(QString name) const
{
 TurnoutManager* manager = turnoutManager;
 Turnout* t;
 if(qobject_cast<AbstractProxyManager*>(manager->mself())!= NULL)
  t= (Turnout*)((ProxyTurnoutManager*)manager->mself())->AbstractProxyManager::getBySystemName(name)->self();
 else
  t= (Turnout*)((AbstractTurnoutManager*)manager)->getBySystemName(name)->self();

 int val = t->getCommandedState();
 switch (val)
 {
  case Turnout::CLOSED: return closedText;
  case Turnout::THROWN: return thrownText;
  case Turnout::UNKNOWN: return tr("Unknown");
  case Turnout::INCONSISTENT: return tr("Inconsistent");
 default: return "Unexpected value: "+QString::number(val);
 }
}

/*public*/ TurnoutManager *TurnoutTableDataModel::getManager() {
 if (turnoutManager == nullptr) {
     turnoutManager = (ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager");
 }
 return turnoutManager;
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ /*final*/ void TurnoutTableDataModel::setManager(/*@Nonnull*/ Manager *manager) {
    if (!(qobject_cast<TurnoutManager*>(manager->mself()))) {
        return;
    }
    getManager()->removePropertyChangeListener(this);
    if (!sysNameList.isEmpty()) {
        for (int i = 0; i < sysNameList.size(); i++) {
            // if object has been deleted, it's not here; ignore it
            NamedBean* b = getBySystemName(sysNameList.at(i));
            if (b != nullptr) {
                b->removePropertyChangeListener(this);
            }
        }
    }
    QObject* o = manager->mself();
    if(QString(o->metaObject()->className())== "ProxyTurnoutManager")
     turnoutManager = (ProxyTurnoutManager*)o;
    else
     turnoutManager =  (AbstractTurnoutManager*)o;
    getManager()->addPropertyChangeListener(this);
    updateNameList();
}

/*public*/ Turnout* TurnoutTableDataModel::getBySystemName(QString name) const
{
 QObject* o = turnoutManager->mself();
 if(QString(o->metaObject()->className()) == "ProxyTurnoutManager")
  return (Turnout*)((ProxyTurnoutManager*)o)->getBySystemName(name)->self();
 else
  return (Turnout*) ((AbstractManager*)o)->getBySystemName(name)->self();

// if(qobject_cast<AbstractManager*>(turnoutManager->self()) != nullptr)
//  return (Turnout*)((AbstractManager*)turnoutManager->self())->getBySystemName(name);
// else
// return ((TurnoutManager*)turnoutManager)->getBySystemName(name);
}

/*public*/ NamedBean* TurnoutTableDataModel::getByUserName(QString name)
{
 return ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getByUserName(name);
}

/*protected*/ QString TurnoutTableDataModel::getMasterClassName() { return getClassName(); }

/*protected*/ QString TurnoutTableDataModel::getClassName() {
    return "jmri.jmrit.beantable.TurnoutTableAction";
}

/*public*/ void TurnoutTableDataModel::clickOn(NamedBean* t)
{
 int state = ((Turnout*)t->self())->getCommandedState();
 if (state==Turnout::CLOSED) ((Turnout*)t->self())->setCommandedState(Turnout::THROWN);
 else ((Turnout*)t->self())->setCommandedState(Turnout::CLOSED);
}

//@Override
/*public*/ void TurnoutTableDataModel::configureTable(JTable* table) {
this->table = table;
//    table.setDefaultRenderer(bool.class, new EnablingCheckboxRenderer());
//    table.setDefaultRenderer(JComboBox.class, new jmri.jmrit.symbolicprog.ValueRenderer());
//    table.setDefaultEditor(JComboBox.class, new jmri.jmrit.symbolicprog.ValueEditor());
//    setColumnToHoldButton(table,TurnoutTableAction::OPSEDITCOL,editButton());
//    setColumnToHoldButton(table,TurnoutTableAction::EDITCOL,editButton());
 setColumnToHoldButton(table,OPSEDITCOL);
 setColumnToHoldButton(table, EDITCOL);
 setColumnToHoldDelegate(table, MODECOL,  new TTComboBoxDelegate());
 //sensorsColDelegate = new TTEditDelegate(turnoutTableAction);
 setColumnToHoldDelegate(table, SENSOR1COL, new TTEditDelegate());
 setColumnToHoldDelegate(table, SENSOR2COL, new TTEditDelegate());
 setColumnToHoldDelegate(table, OPSONOFFCOL, new TTComboBoxDelegate()); //Each row needs it's own instance
 setColumnToHoldDelegate(table, LOCKDECCOL, new TTComboBoxDelegate());
 QStringList lockOperations = {"Undefined"};
 setColumnToHoldDelegate(table, LOCKOPRCOL, new JComboBoxEditor(lockOperations, true));
 setColumnToHoldDelegate(table, STRAIGHTCOL, new JComboBoxEditor(speedListClosed.toList(),false));
 setColumnToHoldDelegate(table, DIVERGCOL, new JComboBoxEditor(speedListClosed.toList(), false));
 setColumnToHoldButton(table, FORGETCOL);
 setColumnToHoldButton(table, QUERYCOL);  //Hide the following columns by default
    XTableColumnModel* columnModel = (XTableColumnModel*)table->getColumnModel();
    table->createDefaultColumnsFromModel();
    TableColumn* column;
    column  = columnModel->getColumnByModelIndex(DIVERGCOL);   // 18
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(STRAIGHTCOL); // 16
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(LOCKDECCOL);  // 15
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(LOCKOPRCOL);  // 14
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(OPSEDITCOL);  // 13
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(OPSONOFFCOL); // 12
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(SENSOR2COL);  // 11
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(SENSOR1COL);  // 10
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(MODECOL);     // 9
    columnModel->setColumnVisible(column, false);
    column  = columnModel->getColumnByModelIndex(KNOWNCOL);    // 8
    columnModel->setColumnVisible(column, false);

  //self->showFeedbackChanged();
  //self->showLockChanged();
  //self->showTurnoutSpeedChanged();
  //self->On_doAutomationBox_toggled(false);

  BeanTableDataModel::configureTable(table);
  table->resizeRowsToContents();
  table->resizeColumnsToContents();
  table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

// update table if turnout lock or feedback changes
//@Override
/*protected*/ bool TurnoutTableDataModel::matchPropertyName(PropertyChangeEvent* e)
 {
  //if(e->getPropertyName() == "inverted") return true;
  if (e->getPropertyName()==("locked")) return true;
  if (e->getPropertyName()==("feedbackchange")) return true;
  if (e->getPropertyName()==("TurnoutDivergingSpeedChange")) return true;
  if (e->getPropertyName()==("TurnoutStraightSpeedChange")) return true;
  //if (e->getPropertyName()==("KnownState")) return true;
  //if (e->getPropertyName()==("CommandedState")) return true;
  else return BeanTableDataModel::matchPropertyName(e);
}

/*public*/ void TurnoutTableDataModel::comboBoxAction(JActionEvent* /*e*/){
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
  updateClosedList();
 }
 else if (e->getPropertyName()==("DefaultTurnoutThrownSpeedChange"))
 {
  updateThrownList();
 }
 else
 {
   BeanTableDataModel::propertyChange(e);
 }
}

/*protected*/ QString TurnoutTableDataModel::getBeanType(){
    return tr("Turnout");
}
/**
 * Customize the turnout table Value (State) column to show an
 * appropriate graphic for the turnout state if _graphicState =
 * true, or (default) just show the localized state text when the
 * TableDataModel is being called from ListedTableAction.
 *
 * @param table a JTable of Turnouts
 */
//@Override
/*protected*/ void TurnoutTableDataModel::configValueColumn(JTable* table) {
    // have the value column hold a JPanel (icon)
    //setColumnToHoldButton(table, VALUECOL, new JLabel("12345678")); // for larger, wide round icon, but cannot be converted to JButton
    // add extras, override BeanTableDataModel
    log->debug(tr("Turnout configValueColumn (I am %1)").arg(BeanTableDataModel::toString()));
    if (_graphicState) { // load icons, only once
     loadIcons();
//        table->setDefaultEditor("JLabel", new ImageIconRenderer()); // editor
//        table->setDefaultRenderer("JLabel", new ImageIconRenderer()); // item class copied from SwitchboardEditor panel
    } else
    {
        BeanTableDataModel::configValueColumn(table); // classic text style state indication
    }
}

//@Override
/*public*/ JTable* TurnoutTableDataModel::makeJTable(/*@Nonnull*/ QString name, /*@Nonnull*/ TableModel* model, /*@CheckForNull*/ RowSorter/*<? extends TableModel>*/* sorter) {
 if (!(qobject_cast<TurnoutTableDataModel*>(model))){
     throw new IllegalArgumentException("Model is not a TurnoutTableDataModel");
 }
 //return configureJTable(name, new /*TurnoutTableJTable*/TTJTable((TurnoutTableDataModel*)model), sorter);
return configureJTable(name, new /*TurnoutTableJTable*/JTable((TurnoutTableDataModel*)model), sorter);}

///*private*/ JTable* TurnoutTableDataModel::makeJTable(TableModel* model) {
//    return new TTJTable(model);
//}
//    {

//@Override
/*protected*/ void TurnoutTableDataModel::setColumnIdentities(JTable* table) {
    BeanTableDataModel::setColumnIdentities(table);
#if 1
    //java.util.Enumeration<TableColumn> columns;
    QListIterator<TableColumn*> columns = table->getColumnModel()->getColumns();
    if (static_cast<XTableColumnModel*>(table->getColumnModel())) {
    } else {
        columns = table->getColumnModel()->getColumns();
    }
    while (columns.hasNext()) {
        TableColumn* column = columns.next();
        switch (column->getModelIndex()) {
            case FORGETCOL:
                column->setIdentifier("ForgetState");
                break;
            case QUERYCOL:
                column->setIdentifier("QueryState");
                break;
            default:
            // use existing value
         break;
        }
    }
#endif
}

/**
 * Pop up a TurnoutOperationConfig for the turnout.
 *
 * @param t   turnout
 * @param box JComboBox that triggered the edit
 */
/*protected*/ void TurnoutTableDataModel::editTurnoutOperation(Turnout* t, JComboBox* box) {
//    if (!editingOps->getAndSet(true)) { // don't open a second edit ops pane
        TurnoutOperation* op = t->getTurnoutOperation();
        if (op == nullptr) {
            TurnoutOperation* proto = ((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->getMatchingOperationAlways(t);
            if (proto != nullptr) {
                op = proto->makeNonce(t);
                t->setTurnoutOperation(op);
            }
        }
        if (op != nullptr) {
            if (!op->isNonce()) {
                op = op->makeNonce(t);
            }
            // make and show edit dialog
            log->debug("TurnoutOpsEditDialog starting");
            TurnoutOperationEditorDialog* dialog = new TurnoutOperationEditorDialog(op, t, box);
            dialog->setVisible(true);
        } else {
            JOptionPane::showMessageDialog(box, tr("There is no operation type suitable for this turnout"),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
        }
//    }
}

/**
 * Create a {@literal JComboBox<String>} containing all the options for
 * turnout automation parameters for this turnout.
 *
 * @param t the turnout
 * @return the JComboBox
 */
/*protected*/ JComboBox* TurnoutTableDataModel::makeAutomationBox(Turnout* t)const {
    QStringList str = {"empty"};
    /*final*/ JComboBox* cb = new JComboBox(str);
    /*final*/ Turnout* myTurnout = t;
    TurnoutTableAction::updateAutomationBox(t, cb);
//    cb.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent e) {
    connect(cb, &JComboBox::currentIndexChanged, [=]{
            setTurnoutOperation(myTurnout, cb);
//            cb.removeActionListener(this);  // avoid recursion
            TurnoutTableAction::updateAutomationBox(myTurnout, cb);
//            cb.addActionListener(this);
//        }
    });
    return cb;
}

/**
 * Set the turnout's operation info based on the contents of the combo box.
 *
 * @param t  turnout being configured
 * @param cb JComboBox for ops for t in the TurnoutTable
 */
/*protected*/ void TurnoutTableDataModel::setTurnoutOperation(Turnout* t, JComboBox* cb) const {
    switch (cb->getSelectedIndex()) {
        case 0:   // Off
            t->setInhibitOperation(true);
            t->setTurnoutOperation(nullptr);
            break;
        case 1:   // Default
            t->setInhibitOperation(false);
            t->setTurnoutOperation(nullptr);
            break;
        default:  // named operation
            t->setInhibitOperation(false);
            t->setTurnoutOperation(((TurnoutOperationManager*)InstanceManager::getDefault("TurnoutOperationManager"))->
                    getOperation( (cb->getSelectedItem())));
            break;
    }
}

/**
 * Create action to edit a turnout in Edit pane. (also used in windowTest)
 *
 * @param t the turnout to be edited
 */
void TurnoutTableDataModel::editButton(Turnout* t) {
    TurnoutEditAction* beanEdit = new TurnoutEditAction(QModelIndex());
    beanEdit->setBean(t);
    beanEdit->actionPerformed(/*null*/);
}

/**
 * Create a JButton to edit a turnout's operation.
 *
 * @return the JButton
 */
/*protected*/ JButton* TurnoutTableDataModel::editButton() {
    return new JButton(tr("Edit Auto"));
}

/*private*/ void TurnoutTableDataModel::updateClosedList() {
    speedListClosed.removeOne(defaultClosedSpeedText);
    defaultClosedSpeedText = (tr("Use %1").arg("Global") + " " + turnoutManager->getDefaultClosedSpeed());
    speedListClosed.insert(0, defaultClosedSpeedText);
    fireTableDataChanged();
}

/*private*/ void TurnoutTableDataModel::updateThrownList() {
    speedListThrown.removeOne(defaultThrownSpeedText);
    defaultThrownSpeedText = (tr("Use %1").arg("Global") + " " + turnoutManager->getDefaultThrownSpeed());
    speedListThrown.insert(0, defaultThrownSpeedText);
    fireTableDataChanged();
}

/*public*/ void TurnoutTableDataModel::showFeedbackChanged(bool visible, JTable* table ) {
   XTableColumnModel* columnModel = (XTableColumnModel*) table->getColumnModel();
   TableColumn* column = columnModel->getColumnByModelIndex(KNOWNCOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(MODECOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(SENSOR1COL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(SENSOR2COL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(OPSONOFFCOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(OPSEDITCOL);
   columnModel->setColumnVisible(column, visible);
}

/*public*/ void TurnoutTableDataModel::showLockChanged(bool visible, JTable* table) {
   XTableColumnModel* columnModel = (XTableColumnModel*) table->getColumnModel();
   TableColumn* column = ((XTableColumnModel*) table->getColumnModel())->getColumnByModelIndex(LOCKDECCOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(LOCKOPRCOL);
   columnModel->setColumnVisible(column, visible);
}

/*public*/ void TurnoutTableDataModel::showTurnoutSpeedChanged(bool visible, JTable* table) {
   XTableColumnModel* columnModel = (XTableColumnModel*) table->getColumnModel();
   TableColumn* column = ((XTableColumnModel*) table->getColumnModel())->getColumnByModelIndex(STRAIGHTCOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(DIVERGCOL);
   columnModel->setColumnVisible(column, visible);
}

/*public*/ void TurnoutTableDataModel::showStateForgetAndQueryChanged(bool visible, JTable* table) {
   XTableColumnModel* columnModel = (XTableColumnModel*) table->getColumnModel();
   TableColumn* column = columnModel->getColumnByModelIndex(FORGETCOL);
   columnModel->setColumnVisible(column, visible);
   column = columnModel->getColumnByModelIndex(QUERYCOL);
   columnModel->setColumnVisible(column, visible);
}

TTComboBoxDelegate::TTComboBoxDelegate( bool editable, QObject * parent) : QStyledItemDelegate(parent)
{
 this->editable = editable;
}

QWidget* TTComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const
{
 JComboBox* editor = new JComboBox(parent);
 editor->setEditable(editable);

 AbstractTurnout* t;
 int row = index.row();
 TurnoutManager* manager = (TurnoutManager*)InstanceManager::getDefault("TurnoutManager");
 QString name = ((TurnoutTableDataModel*)index.model())->sysNameList.at(row);
 if(qobject_cast<AbstractProxyManager*>(manager->mself()))
  t = (AbstractTurnout*)((AbstractProxyManager*)manager->mself())->getBeanBySystemName(name)->self();
 else
  t = (AbstractTurnout*)((AbstractTurnoutManager*)manager->mself())->getBySystemName(name)->self();
 if (t == NULL)
 {
  TurnoutTableAction::log->debug("error NULL turnout!");
  throw new NullPointerException();
 }
 switch(index.column())
 {
 case TurnoutTableDataModel::MODECOL:
   editor->addItems( t->getValidFeedbackNames().toList());
   break;
 case TurnoutTableDataModel::OPSONOFFCOL:
 {
   turnoutTableAction->updateAutomationBox(t, editor);
   break;
 }
 case TurnoutTableDataModel::LOCKDECCOL:
   editor->addItems( t->getValidDecoderNames());
   break;
 }
 return editor;
}

void TTComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
 JComboBox *comboBox = static_cast<JComboBox*>(editor);
 QString value = index.model()->data(index, Qt::DisplayRole).toString();
 comboBox->setCurrentText(value);
}

void TTComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
  JComboBox *comboBox = static_cast<JComboBox*>(editor);
  if(index.column() == TurnoutTableDataModel::OPSONOFFCOL)
  {
   AbstractTurnout* t;
   int row = index.row();
   TurnoutManager* manager = (TurnoutManager*)InstanceManager::getDefault("TurnoutManager");
   QString name = ((TurnoutTableDataModel*)index.model())->sysNameList.at(row);
   if(qobject_cast<AbstractProxyManager*>(manager->mself()))
    t = (AbstractTurnout*)((AbstractProxyManager*)manager->mself())->getBeanBySystemName(name)->self();
   else
    t = (AbstractTurnout*)((AbstractTurnoutManager*)manager->mself())->getBySystemName(name)->self();

   ((TurnoutTableDataModel*)index.model())->setTurnoutOperation(t, comboBox);
   ((TurnoutTableDataModel*)index.model())->fireTableRowsUpdated(row,row);
  }
  else
   model->setData(index, comboBox->currentText(), Qt::EditRole);
}

void TTComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

void TTComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 JComboBox* widget = new JComboBox();
 widget->setEditable(true);
 QString value = index.model()->data(index, Qt::DisplayRole).toString();
 widget->setCurrentText(value);

 widget->resize(option.rect.size());
 QPixmap pixmap(option.rect.size());
 widget->render(&pixmap);
 painter->drawPixmap(option.rect,pixmap);
}

//@Override
/*public*/ QAbstractItemDelegate* TTJTable::getCellRenderer(int row, int column) {
    // Convert the displayed index to the model index, rather than the displayed index
    int modelColumn = this->convertColumnIndexToModel(column);
    if (modelColumn == TurnoutTableDataModel::SENSOR1COL || modelColumn == TurnoutTableDataModel::SENSOR2COL) {
        return (QAbstractItemDelegate*)getRenderer(row, modelColumn);
    } else {
        return JTable::getCellRenderer(row, column);
    }
}

//@Override
/*public*/ QAbstractItemDelegate* TTJTable::getCellEditor(int row, int column) {
    //Convert the displayed index to the model index, rather than the displayed index
    int modelColumn = this->convertColumnIndexToModel(column);
    if (modelColumn == TurnoutTableDataModel::SENSOR1COL || modelColumn == TurnoutTableDataModel::SENSOR2COL) {
        return (QAbstractItemDelegate*)getEditor(row, modelColumn);
    } else {
        return JTable::getCellEditor(row, column);
    }
}

TableCellRenderer* TTJTable::getRenderer(int row, int column) {
    TableCellRenderer* retval = nullptr;
    Turnout* t = VPtr<Turnout>::asPtr(((TurnoutTableDataModel*)getModel())->getValueAt(row, TurnoutTableDataModel::SYSNAMECOL));
    //java.util.Objects.requireNonNull(t, "SYSNAMECOL column content must be nonnull");
    if (column == TurnoutTableDataModel::SENSOR1COL) {
        retval = rendererMapSensor1->value(t);
    } else if (column == TurnoutTableDataModel::SENSOR2COL) {
        retval = rendererMapSensor2->value(t);
    } else {
        return nullptr;
    }

    if (retval == nullptr) {
        if (column == TurnoutTableDataModel::SENSOR1COL) {
            loadRenderEditMaps(rendererMapSensor1, editorMapSensor1, t, t->getFirstSensor());
            retval = rendererMapSensor1->value(t);
        } else {
            loadRenderEditMaps(rendererMapSensor2, editorMapSensor2, t, t->getSecondSensor());
            retval = rendererMapSensor1->value(t);
        }
    }
    log->debug(tr("fetched for Turnout \"%1\" renderer %2").arg(t->getDisplayName()).arg(retval->self()->metaObject()->className()));
    return retval;
}

TableCellEditor* TTJTable::getEditor(int row, int column) {
    TableCellEditor* retval = nullptr;
    Turnout* t = VPtr<Turnout>::asPtr( ((TurnoutTableDataModel*)getModel())->getValueAt(row, TurnoutTableDataModel::SYSNAMECOL));
    //java.util.Objects.requireNonNull(t, "SYSNAMECOL column content must be nonnull");
    switch (column) {
        case TurnoutTableDataModel::SENSOR1COL:
            retval = editorMapSensor1->value(t);
            break;
        case TurnoutTableDataModel::SENSOR2COL:
            retval = editorMapSensor2->value(t);
            break;
        default:
            return nullptr;
    }
    if (retval == nullptr) {
        if (column == TurnoutTableDataModel::SENSOR1COL) {
            loadRenderEditMaps(rendererMapSensor1, editorMapSensor1, t, t->getFirstSensor());
            retval = editorMapSensor1->value(t);
        } else { //Must be two
            loadRenderEditMaps(rendererMapSensor2, editorMapSensor2, t, t->getSecondSensor());
            retval = editorMapSensor2->value(t);
        }
    }
    log->debug(tr("fetched for Turnout \"%1\" editor %2").arg(t->getDisplayName()).arg(retval->self()->metaObject()->className()));
    return retval;
}

/*protected*/ void TTJTable::loadRenderEditMaps(QHash<Turnout*, TableCellRenderer*>* r, QHash<Turnout*, TableCellEditor*>* e,
        Turnout* t, Sensor* s) {
    NamedBeanComboBox/*<Sensor>*/* c = new NamedBeanComboBox((SensorManager*)InstanceManager::getDefault("SensorManager"), s, NamedBean::DisplayOptions::DISPLAYNAME);
    c->setAllowNull(true);

    BeanBoxRenderer* renderer = new BeanBoxRenderer(c);
    //renderer->setSelectedItem(s);
    r->insert(t, renderer);

    TableCellEditor* editor = new BeanComboBoxEditor(c);
    e->insert(t, editor);
    log->debug(tr("initialize for Turnout \"%1\" Sensor \"%2\"").arg(t->getDisplayName()).arg(s->getDisplayName()));
}

//        Hashtable<Turnout, TableCellRenderer> rendererMapSensor1 = new Hashtable<>();
//        Hashtable<Turnout, TableCellEditor> editorMapSensor1 = new Hashtable<>();

//        Hashtable<Turnout, TableCellRenderer> rendererMapSensor2 = new Hashtable<>();
//        Hashtable<Turnout, TableCellEditor> editorMapSensor2 = new Hashtable<>();
//    };
//}
/**
 * Read and buffer graphics. Only called once for this table.
 *
 * @see #getTableCellEditorComponent(JTable, Object, boolean, int, int)
 */
/*protected*/ void TurnoutTableDataModel::loadIcons() {
    try {
        onImage = ImageIO::read(new File(onIconPath));
        offImage = ImageIO::read(new File(offIconPath));
    } catch (IOException* ex) {
        log->error(tr("error reading image from %1 or %2").arg(onIconPath).arg(offIconPath), ex);
    }
    log->debug("Success reading images");
    int imageWidth = onImage->width();
    int imageHeight = onImage->height();
    // scale icons 50% to fit in table rows
    QImage smallOnImage = onImage->getScaledInstance(imageWidth / 2, imageHeight / 2,0/*, Image.SCALE_DEFAULT*/);
    QImage smallOffImage = offImage->getScaledInstance(imageWidth / 2, imageHeight / 2, 0/*, Image.SCALE_DEFAULT*/);
//        onIcon = new ImageIcon(smallOnImage);
    onIcon = QPixmap::fromImage(smallOnImage);
//        offIcon = new ImageIcon(smallOffImage);
    offIcon = QPixmap::fromImage(smallOffImage);
    iconHeight = onIcon.height();
}
//};  // end of custom data model
TTEditDelegate::TTEditDelegate()
{
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
 QString value = index.model()->data(index, Qt::DisplayRole).toString();
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

void TTEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 QLineEdit* widget = new QLineEdit();
 QString value = index.model()->data(index, Qt::DisplayRole).toString();
 widget->setText(value);
 widget->resize(option.rect.size());
 QPixmap pixmap(option.rect.size());
 widget->render(&pixmap);
 painter->drawPixmap(option.rect,pixmap);

}

/*private*/ /*final*/ /*static*/ Logger* TurnoutTableDataModel::log = LoggerFactory::getLogger("TurnoutTableDataModel");
