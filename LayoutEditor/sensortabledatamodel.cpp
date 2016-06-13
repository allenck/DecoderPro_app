#include "sensortabledatamodel.h"
#include "proxysensormanager.h"
#include "instancemanager.h"
#include "abstractsensor.h"
#include "jtextfield.h"
#include "jtable.h"
#include "abstractsensormanager.h"
#include "../Tables/logixtableaction.h" // for PushButtonItemDelegate
#include <QSignalMapper>
#include "systemnamecomparator.h"

SensorTableDataModel::SensorTableDataModel(QObject *parent) :
    BeanTableDataModel(parent)
{
 common();
}
/**
 * Data model for a SensorTable
 *
 * @author	Bob Jacobsen    Copyright (C) 2003, 2009
 * @version     $Revision: 20803 $
 */

///*public*/ class SensorTableDataModel extends BeanTableDataModel {


//    /*public*/ SensorTableDataModel() {
//        super();
//    }
void SensorTableDataModel::common()
{
 senManager = (AbstractSensorManager*)InstanceManager::sensorManagerInstance();
 setObjectName("SensorTableDataModel");
 log = new Logger("SensorDataModel");
 deleteMapper = new QSignalMapper();
 table = NULL;
 init();
}

/*public*/ SensorTableDataModel::SensorTableDataModel(SensorManager* manager, QObject *parent) : BeanTableDataModel(parent)
{
 //super();
 common();
 senManager = (SensorManager*)manager;
 ProxySensorManager* proxy = NULL;
 AbstractSensorManager* mgr = NULL;
 if(qobject_cast<ProxySensorManager*>(senManager) != NULL)
 {
  proxy = (ProxySensorManager*)senManager;
  proxy->removePropertyChangeListener((PropertyChangeListener*) this);
  disconnect(proxy->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else
 {
  mgr = (AbstractSensorManager*)senManager;
  mgr->removePropertyChangeListener((PropertyChangeListener*) this);
  disconnect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

// getManager()->removePropertyChangeListener((PropertyChangeListener*)this);
// AbstractSensorManager* mgr = (AbstractSensorManager*)getManager();
// disconnect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=NULL)
   {
    b->removePropertyChangeListener((PropertyChangeListener*)this);
    AbstractNamedBean* anb = (AbstractNamedBean*)b;
    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 senManager = (SensorManager*)manager;
// getManager()->addPropertyChangeListener((PropertyChangeListener*)this);
// //ProxySensorManager* mgr = (ProxySensorManager*)getManager();
// connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if(proxy != NULL)
 {
  proxy->addPropertyChangeListener((PropertyChangeListener*) this);
  connect(proxy->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 if(mgr != NULL)
 {
  mgr->addPropertyChangeListener((PropertyChangeListener*) this);
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //connect(aMgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 updateNameList();
}

/*public*/ QString SensorTableDataModel::getValue(QString name) const
{
 Sensor* sen;
 if(qobject_cast<ProxySensorManager*>(senManager)!= NULL)
  sen = ((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  sen = (Sensor*)senManager->getBeanBySystemName(name);
 int val = sen->getKnownState();
 switch (val) {
 case Sensor::ACTIVE: return tr("Active");
 case Sensor::INACTIVE: return tr("Inactive");
 case Sensor::UNKNOWN: return tr("Unknown");
 case Sensor::INCONSISTENT: return tr("Inconsistent");
 default: return "Unexpected value: "+val;
 }
}
/*protected*/ void SensorTableDataModel::setManager(Manager* manager)
{
 //((AbstractManager*)getManager())->removePropertyChangeListener((PropertyChangeListener*)this);
 ProxySensorManager* mgr = (ProxySensorManager*)getManager();
 disconnect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 if (!sysNameList.isEmpty())
 {
  for (int i = 0; i< sysNameList.size(); i++)
  {
   // if object has been deleted, it's not here; ignore it
   NamedBean* b = getBySystemName(sysNameList.at(i));
   if (b!=NULL)
   {
    b->removePropertyChangeListener((PropertyChangeListener*)this);
    AbstractNamedBean* anb = (AbstractNamedBean*)b;
    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }
 senManager = (SensorManager*)manager;
 getManager()->addPropertyChangeListener((PropertyChangeListener*)this);
 //ProxySensorManager* mgr = (ProxySensorManager*)getManager();
 connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 updateNameList();
}
/*protected*/ Manager* SensorTableDataModel::getManager()
{
 if (senManager==NULL)
  senManager=(ProxySensorManager*)InstanceManager::sensorManagerInstance();
 return senManager;
}
/*protected*/ NamedBean* SensorTableDataModel::getBySystemName(QString name) const
{
 if(qobject_cast<ProxySensorManager*>(senManager) != NULL)
  return ((ProxySensorManager*)senManager)->getBeanBySystemName(name);
 else
  return ((SensorManager*)senManager)->getBySystemName(name);
}
/*protected*/ NamedBean* SensorTableDataModel::getByUserName(QString name) { return ((ProxySensorManager*)senManager)->getByUserName(name);}

/*protected*/ QString SensorTableDataModel::getMasterClassName() { return getClassName(); }
/*protected*/ void SensorTableDataModel::clickOn(NamedBean* t)
{
 try {
        int state = ((AbstractSensor*)t)->getKnownState();
        if (state==Sensor::INACTIVE) ((AbstractSensor*)t)->setKnownState(Sensor::ACTIVE);
        else ((AbstractSensor*)t)->setKnownState(Sensor::INACTIVE);
    } catch (JmriException e) { log->warn("Error setting state: "+e.getMessage()); }
}

/*public*/ int SensorTableDataModel::columnCount(const QModelIndex &/*parent*/) const
{
    return INACTIVEDELAY+1;
}

/*public*/ QVariant SensorTableDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  int col = section;
    if(col==INVERTCOL) return tr("Inverted");
    if(col==USEGLOBALDELAY) return tr("Use Global Delay");
    if(col==ACTIVEDELAY) return tr("Active Delay");
    if(col==INACTIVEDELAY) return tr("InActive Delay");
 }
 return BeanTableDataModel::headerData(section, orientation, role);
}
///*public*/ Class<?> getColumnClass(int col) {
//    if (col==INVERTCOL) return Boolean.class;
//    if(col==USEGLOBALDELAY) return Boolean.class;
//    if(col==ACTIVEDELAY) return String.class;
//    if(col==INACTIVEDELAY) return String.class;
//    else return super.getColumnClass(col);
//}
/*public*/ int SensorTableDataModel::getPreferredWidth(int col) {
    if (col==INVERTCOL) return  JTextField(4).getPreferredSize().width();
    if(col==USEGLOBALDELAY || col==ACTIVEDELAY || col==INACTIVEDELAY){
        return  JTextField(8).getPreferredSize().width();
    }
    else return BeanTableDataModel::getPreferredWidth(col);
}
/*public*/ Qt::ItemFlags SensorTableDataModel::flags(const QModelIndex &index) const
{
 int col = index.column();
 int row = index.row();
 if (col==INVERTCOL) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
 if(col==USEGLOBALDELAY) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
 //Need to do something here to make it disable
 if(col==ACTIVEDELAY||col==INACTIVEDELAY)
 {
  QString name = sysNameList.at(row);
  Sensor* s;
  if(qobject_cast<ProxySensorManager*>(senManager)!= NULL)
   s= ((ProxySensorManager*)senManager)->getBySystemName(name);
  else
   s = ((AbstractSensorManager*)senManager)->getBySystemName(name);
  if(((AbstractSensor*)s)->useDefaultTimerSettings())
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable ;
  else
   return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
 }
 else return BeanTableDataModel::flags(index);
}

/*public*/ QVariant SensorTableDataModel::data(const QModelIndex &index, int role) const
{
 QString name = sysNameList.at(index.row());
 AbstractSensor* s;
 if(qobject_cast<ProxySensorManager*>(senManager) != 0)
  s = (AbstractSensor*)((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  s = (AbstractSensor*)((AbstractSensorManager*)senManager)->getBySystemName(name);

 if(role == Qt::CheckStateRole)
 {
  switch(index.column())
  {
   case INVERTCOL:
    return s->getInverted()?Qt::Checked:Qt::Unchecked;
   case USEGLOBALDELAY:
    return s->useDefaultTimerSettings()?Qt::Checked:Qt::Unchecked;
   default:
    break;
  }
 }
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  if (row >= sysNameList.size())
  {
   log->debug("row is greater than name list");
   return "";
  }
  if (s == NULL)
  {
   log->debug("error NULL sensor!");
   return "error";
  }
//  if (col==INVERTCOL) {
//        boolean val = s.getInverted();
//        return Boolean.valueOf(val);
//    }
//    else if(col==USEGLOBALDELAY){
//        boolean val = s.useDefaultTimerSettings();
//        return Boolean.valueOf(val);
//    }
  if(col==ACTIVEDELAY)
  {
   return (int)s->getSensorDebounceGoingActiveTimer();
  }
  else if(col==INACTIVEDELAY)
  {
   return (int)s->getSensorDebounceGoingInActiveTimer();
  }
  else if (col == INVERTCOL || col == USEGLOBALDELAY)
   return "";
 }
 return BeanTableDataModel::data(index, role);
}

/*public*/ bool SensorTableDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 if (row >= sysNameList.size())
 {
  log->debug("row is greater than name list");
  return false;
 }
 QString name = sysNameList.at(row);
 AbstractSensor* s;
 if(qobject_cast<ProxySensorManager*>(senManager) != 0)
  s = (AbstractSensor*)((ProxySensorManager*)senManager)->getBySystemName(name);
 else
  s = (AbstractSensor*)((AbstractSensorManager*)senManager)->getBySystemName(name);

 if (s == NULL)
 {
  log->debug("error NULL sensor!");
  return false;
 }
 if(role == Qt::CheckStateRole)
 {
  if (col==INVERTCOL)
  {
//        boolean b = ((Boolean)value).booleanValue();
   s->setInverted(value.toBool());
   return true;
  }
  else if(col==USEGLOBALDELAY)
  {
//        boolean b = ((Boolean)value).booleanValue();
   s->useDefaultTimerSettings(value.toBool());
   return true;
  }
 }
 if(role == Qt::EditRole)
 {
  if(col==ACTIVEDELAY)
  {
//        String val = (String)value;
//        long goingActive = Long.valueOf(val);
   s->setSensorDebounceGoingActiveTimer(value.toInt());
   return true;
  }
  else if(col==INACTIVEDELAY)
  {
//        String val = (String)value;
//        long goingInActive = Long.valueOf(val);
   s->setSensorDebounceGoingInActiveTimer(value.toInt());
   return true;
  }
 }
 return BeanTableDataModel::setData(index, value, role);
}

/*protected*/ QString SensorTableDataModel::getBeanType()
{
 return tr("Sensor");
}

/*protected*/ bool SensorTableDataModel::matchPropertyName(PropertyChangeEvent* e)
{
 if ((e->getPropertyName().indexOf("inverted")>=0) || (e->getPropertyName().indexOf("GlobalTimer")>=0) ||
        (e->getPropertyName().indexOf("ActiveTimer")>=0) || (e->getPropertyName().indexOf("InActiveTimer")>=0)){
  return true;
 }
 else return BeanTableDataModel::matchPropertyName(e);
}

//@Override
/*public*/ void SensorTableDataModel::configureTable(JTable* table)
{
 this->table = table;
 showDebounce(false);
// this->table->setItemDelegateForColumn(DELETECOL, new PushButtonDelegate(deleteMapper));
 BeanTableDataModel::configureTable(table);
// connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(OnDelete(int)));
}


/*public*/ void SensorTableDataModel::showDebounce(bool show)
{
 if(table == NULL) return;
//    XTableColumnModel columnModel = (XTableColumnModel)table.getColumnModel();
//    TableColumn column  = columnModel.getColumnByModelIndex(USEGLOBALDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(USEGLOBALDELAY, !show);
//    column  = columnModel.getColumnByModelIndex(ACTIVEDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(ACTIVEDELAY, !show);
//    column  = columnModel.getColumnByModelIndex(INACTIVEDELAY);
//    columnModel.setColumnVisible(column, show);
 table->setColumnHidden(INACTIVEDELAY, !show);
}

/*protected*/ QString SensorTableDataModel::getClassName() { return "SensorTableAction"; }

// /*public*/ static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.beantable.BeanTableBundle");
/*public*/ QString SensorTableDataModel::getClassDescription() { return tr("Sensor Table"); }

// /*protected*/ /*synchronized*/ void SensorTableDataModel::updateNameList()
//{
// //Manager* mgr = getManager();
// Manager* mgr = senManager;

// // first, remove listeners from the individual objects
// if (!sysNameList.isEmpty())
// {
//  for (int i = 0; i< sysNameList.size(); i++)
//  {
//   // if object has been deleted, it's not here; ignore it
//   NamedBean* b = getBySystemName(sysNameList.at(i));
//   if (b!=NULL)
//   {
//    b->removePropertyChangeListener((PropertyChangeListener*)this);
//    AbstractNamedBean* anb = (AbstractNamedBean*)b;
//    disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

//   }
//  }
// }
// if(qobject_cast<ProxySensorManager*>(mgr) != NULL)
//  sysNameList = ((ProxySensorManager*)mgr)->getSystemNameList();
// else
//  sysNameList = ((AbstractSensorManager*)mgr)->getSystemNameList();
// qSort(sysNameList.begin(), sysNameList.end(), SystemNameComparator::compare);
// // and add them back in
// for (int i = 0; i< sysNameList.size(); i++)
// {
//  //getBySystemName(sysNameList.at(i))->addPropertyChangeListener((PropertyChangeListener*)this, NULL, "Table View");
////  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  NamedBean* b = getBySystemName(sysNameList.at(i));
//  if (b!=NULL)
//  {
//   b->addPropertyChangeListener((PropertyChangeListener*)this, NULL, "Table View");
//   AbstractNamedBean* anb = (AbstractNamedBean*)b;
//   connect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//  }
// }
//}
void SensorTableDataModel::OnDelete(int row)
{
 QString name = sysNameList.at(row);
 ProxySensorManager* mgr = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
 NamedBean* bean = mgr->getBeanBySystemName(name);
 if(bean != NULL)
 {
  mgr->deregister(bean);
  sysNameList.removeAt(row);
  fireTableDataChanged();
 }
}
