#include "picklistmodel.h"
#include "manager.h"
#include "sensormanager.h"
#include "turnoutmanager.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "abstractsignalheadmanager.h"
#include "proxysensormanager.h"
#include "defaultsignalmastmanager.h"
#include "abstractmemorymanager.h"
#include "abstractreportermanager.h"
#include "abstractlightmanager.h"
//#include "treeset.h"
#include "namedbeancomparator.h"
#include "signalmastmanager.h"
//#include "picklisttablemodel.h"
#include "comparator.h"
#include "defaultmemorymanager.h"
#include "proxyreportermanager.h"
#include "proxylightmanager.h"
#include "defaultconditionalmanager.h"
#include "oblockmanager.h"
#include "warrantmanager.h"
#include <QDrag>
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "lnsensormanager.h"
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include "block.h"
#include "blockmanager.h"
#include "logixmanager.h"
#include "defaultlistselectionmodel.h"
#include "vptr.h"

//PickListModel::PickListModel(QObject *parent) :
//    QAbstractTableModel(parent)
//{
//}
/**
 * Abstract class to make pick lists for NamedBeans.
 * <P>
 * Concrete pick list classe for many beans are include at the end of
 * this file.  This class also has instantiation methods serve as a factory
 * for those classes.
 * <P>
 * Note: Extensions of this class must call init() after instantiation.
 *
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
 * @author      Pete Cressman Copyright (C) 2009, 2010
 * @version
 */
/**
* Table model for pick lists in IconAdder
*/
///*public*/ abstract class PickListModel extends AbstractTableModel implements PropertyChangeListener {

/*static*/ QMap<QString,int>* PickListModel::_listMap = new QMap<QString,int>();
#if 0
bool systemNameComparator(QString o1, QString o2)
{
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
#endif

/*static*/ /*public*/ int PickListModel::getNumInstances(QString type)
{
 Logger* log = new Logger("PickListModel");
 int num = _listMap->value(type.toLower());
 if (log->isDebugEnabled()) log->debug("getNumInstances of "+type+" num= "+QString::number(num));
 if (num!=0)
 {
  return num;
 }
 return 0;
}

/**
* Default constructor makes a table sorted by System Name.
*/
/*public*/ PickListModel::PickListModel(QObject *parent) : /*AbstractNamedBean*/BeanTableDataModel(parent)
{
    //super();
 log = new Logger("PickListModel");
 _table = NULL;
 _listMap = new QMap<QString,int>();
 //_tableModel = new PickListModel;
 _pickList = NULL;
 init();
}

/**
 * No longer needed. Now done in BeanTableDataModel.
 *
 * @deprecated since Jan 1, 2014, marked as such May 1, 2017
 */
//@Deprecated
/*public*/ void PickListModel::init()
{

    //log->debug("manager "+getManager());
  //getManager()->addPropertyChangeListener(this);   // for adds and deletes
 Manager* m = getManager();
 if(m == NULL) return;

//    if(qobject_cast<AbstractManager*>(m) != NULL)
//    {
  AbstractManager* mgr = (AbstractManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//    }
 if(qobject_cast<ProxyTurnoutManager*>(m) != NULL)
 {
  ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<ProxySensorManager*>(m) != NULL)
 {
  ProxySensorManager* mgr = (ProxySensorManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<AbstractSignalHeadManager*>(m) != NULL)
 {
  AbstractSignalHeadManager* mgr = (AbstractSignalHeadManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<DefaultSignalMastManager*>(m) != NULL)
 {
  DefaultSignalMastManager* mgr = (DefaultSignalMastManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<DefaultMemoryManager*>(m) != NULL)
 {
  DefaultMemoryManager* mgr = (DefaultMemoryManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<ProxyReporterManager*>(m) != NULL)
 {
  ProxyReporterManager* mgr = (ProxyReporterManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<ProxyLightManager*>(m) != NULL)
 {
  ProxyLightManager* mgr = (ProxyLightManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<DefaultConditionalManager*>(m) != NULL)
 {
  DefaultConditionalManager* mgr = (DefaultConditionalManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<WarrantManager*>(m) != NULL)
 {
  WarrantManager* mgr = (WarrantManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<OBlockManager*>(m) != NULL)
 {
  OBlockManager* mgr = (OBlockManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<EntryExitPairs*>(m) != NULL)
 {
  EntryExitPairs* mgr = (EntryExitPairs*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else if(qobject_cast<BlockManager*>(m) != NULL)
 {
  BlockManager* mgr = (BlockManager*)m;
  connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 else
 {
  log->error(tr("no PickListModel manager for %1").arg(m->metaObject()->className()));
  Q_ASSERT(false);
 }
 makePickList();


}

/**
 * If table has been sorted table row no longer is the same as array index
 * @param index = row of table
 */
/*public*/ NamedBean* PickListModel::getBeanAt(int index)
{
 //    index = _sorter.modelIndex(index);
 if (index >=_pickList->size())
 {
  return NULL;
 }
 return _pickList->at(index);
}

/*public*/ int PickListModel::getIndexOf(NamedBean* bean)
{
 for (int i=0; i<_pickList->size(); i++)
 {
  if (_pickList->at(i)==(bean))
  {
   return i;
  }
 }
 return -1;
}

/*public*/ QList <NamedBean*>* PickListModel::getBeanList() {
    return _pickList;
}

/**
 * override BeanTableDataModel only lists SystemName
 */
//@Override
/*protected*/ /*synchronized*/ void PickListModel::updateNameList() {
    makePickList();
}

/*private*/ void PickListModel::makePickList()
{
 // Don't know who is added or deleted so remove all name change listeners
 if (_pickList != NULL)
 {
  for (int i=0; i<_pickList->size(); i++)
  {
   _pickList->value(i)->removePropertyChangeListener((PropertyChangeListener*)this);
  }
 }
 QList <QString> systemNameList = getManager()->getSystemNameList();
    //TreeSet<NamedBean*>* ts =  new TreeSet<NamedBean*>(  /*NamedBeanComparator()*/);
 QList<NamedBean*>* ts = new QList<NamedBean*>();

 qSort(systemNameList.begin(), systemNameList.end(), SystemNameComparator::compare);

 QStringListIterator iter(systemNameList);
 while (iter.hasNext())
 {
  Manager* manager = getManager();
  if(qobject_cast<ProxySensorManager*>(manager)!= NULL)
   ts->append(((ProxySensorManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<ProxyTurnoutManager*>(manager)!= NULL)
   ts->append(((ProxyTurnoutManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<ProxyReporterManager*>(manager)!= NULL)
   ts->append(((ProxyReporterManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<AbstractSignalHeadManager*>(manager)!= NULL)
   ts->append(((AbstractSignalHeadManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<DefaultSignalMastManager*>(manager)!= NULL)
   ts->append(((DefaultSignalMastManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<DefaultConditionalManager*>(manager)!= NULL)
   ts->append(((DefaultConditionalManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<ProxyLightManager*>(manager)!= NULL)
   ts->append(((ProxyLightManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<DefaultMemoryManager*>(manager)!= NULL)
   ts->append(((DefaultMemoryManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<OBlockManager*>(manager)!= NULL)
   ts->append((NamedBean*)((OBlockManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<WarrantManager*>(manager)!= NULL)
   ts->append((NamedBean*)((WarrantManager*)manager)->getBySystemName(iter.next()));
  else if(qobject_cast<BlockManager*>(manager)!= NULL)
   ts->append((NamedBean*)((BlockManager*)manager)->getBySystemName(iter.next()));
  else Q_ASSERT(false);
 }
 _pickList = new QList <NamedBean*> ();//systemNameList.size());

 QListIterator <NamedBean*> it(*ts);
 while(it.hasNext())
 {
  NamedBean* elt = it.next();
  _pickList->append(elt);
 }
 // add name change listeners
 for (int i=0; i<_pickList->size(); i++) {
  _pickList->at(i)->addPropertyChangeListener((PropertyChangeListener*)this);
  AbstractNamedBean* b = (AbstractNamedBean*)_pickList->at(i);
  //connect(b->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 if (log->isDebugEnabled()) log->debug("_pickList has "+QString::number(_pickList->size())+" beans");
}

//abstract /*public*/ Manager getManager();
//abstract /*public*/ NamedBean getBySystemName(String name);

/**
* Return bean with name given in parameter.  Create if needed and possible
*/
//abstract /*public*/ NamedBean addBean(String name);
//abstract /*public*/ NamedBean addBean(String sysName, String userName);
/**
* Return true if model can create beans
*/
//abstract /*public*/ boolean canAddBean();

///*public*/ Class<?> getColumnClass(int c) {
//        return String.class;
//}

/*public*/ int PickListModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

/*public*/ QVariant PickListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  if (section == SNAME_COLUMN)
  {
   return tr("System Name");
  }
  else if (section == UNAME_COLUMN)
  {
   return tr("User Name");
  }
  else if(section == POSITION_COL)
  {
   return tr("Position");
  }
 }
 return QVariant();
}

/*public*/Qt::ItemFlags PickListModel::flags(const QModelIndex &index) const
{
 Qt::ItemFlags defaultFlags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

 if (index.isValid())
  return Qt::ItemIsDragEnabled /*| Qt::ItemIsDropEnabled*/ | defaultFlags;
 else
  return /*Qt::ItemIsDropEnabled |*/ defaultFlags;}

/*public*/ int PickListModel::rowCount(const QModelIndex &/*parent*/) const
{
 return _pickList->size();
}

/*public*/ QVariant PickListModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int r = index.row();
  int c = index.column();
  // some error checking
  if (r >= _pickList->size())
  {
   log->debug("row is greater than picklist size");
   return QVariant();
  }
  if (c == SNAME_COLUMN)
  {
   return _pickList->value(r)->getSystemName();
  }
  else if (c == UNAME_COLUMN)
  {
   return _pickList->value(r)->getUserName();
  }
 }
 return QVariant();
}
/*public*/ bool PickListModel::setData(const QModelIndex &/*index*/, const QVariant &/*value*/, int /*role*/)
{
 return false;
}

/*public*/ QString PickListModel::getName() {
    return _name;
}

/*public*/ void PickListModel::propertyChange(PropertyChangeEvent* e)
{
 if(log->isDebugEnabled()) log->debug(tr("property name = %1").arg(e->getPropertyName()));

 if (e->getPropertyName()==("length"))
 {
  // a NamedBean added or deleted
  makePickList();
  fireTableDataChanged();
 }
 //  ACK added
 if(e->getPropertyName() == "beans")
 {
  // a value changed.  Find it, to avoid complete redraw
  NamedBean* bean = VPtr<NamedBean>::asPtr(e->getNewValue());
  for (int i=0; i<_pickList->size(); i++)
  {
   if (bean->equals(_pickList->at(i)))
   {
    fireTableRowsUpdated(i, i);
   }
  }
 }
 else if (qobject_cast< NamedBean*>(e->getSource())) {
  // a value changed.  Find it, to avoid complete redraw
  NamedBean* bean = (NamedBean*)e->getSource();
  for (int i=0; i<_pickList->size(); i++)
  {
   if (bean->equals(_pickList->at(i)))
   {
    fireTableRowsUpdated(i, i);
   }
  }
 }
 if (log->isDebugEnabled()) log->debug("propertyChange of \""+e->getPropertyName()+
                                        "\" for "+e->getSource()->metaObject()->className());
}

//void PickListModel::fireTableDataChanged()
//{
// //_tableModel->fireTableDataChanged();

//}
//void PickListModel::fireTableRowsUpdated(int r1, int r2)
//{
// _tableModel->fireTableRowsUpdated(r1, r2);
//}
//PickListModel* PickListModel::model() { return _tableModel;}
/**
* Make pick table, DND enabled
*/
/*public*/ JTable* PickListModel::makePickTable() {
    this->init();
//    try {   // following might fail due to a missing method on Mac Classic
//        _sorter = new TableSorter(this);
//        _table = jmri.util.JTableUtil.sortableDataModel(_sorter);
//        _sorter.setTableHeader(_table.getTableHeader());
//        _sorter.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
//        _table.setModel(_sorter);
//    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
//        log->error("makePickTable: Unexpected error: "+e);
//        _table = new JTable(this);
//    }
//    _table = new QTableView();
//    _table->setModel(this);
 _sorter = new QSortFilterProxyModel();
 _sorter->setSourceModel(this);
 _table = new JTable(_sorter);
 _table->setSortingEnabled(true);
    _table->horizontalHeader()->setStretchLastSection(true);
//    connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(tableClicked(QModelIndex)));
    fireTableDataChanged();

//    _table.setRowSelectionAllowed(true);
    _table->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
    _table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //_table->setSelectionMode(QAbstractItemView::SingleSelection);
//    _table.setPreferredScrollableViewportSize(new java.awt.Dimension(250,_table.getRowHeight()*7));
    _table->setDragEnabled(true);
//    _table.setTransferHandler(new jmri.util.DnDTableExportHandler());
//    TableColumnModel columnModel = _table.getColumnModel();

//    TableColumn sNameColumnT = columnModel.getColumn(SNAME_COLUMN);
//    sNameColumnT.setResizable(true);
//    sNameColumnT.setMinWidth(50);
//    //sNameColumnT.setMaxWidth(200);

//    TableColumn uNameColumnT = columnModel.getColumn(UNAME_COLUMN);
//    uNameColumnT.setResizable(true);
//    uNameColumnT.setMinWidth(100);
//    //uNameColumnT.setMaxWidth(300);
    //connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(tableClicked(QModelIndex)));
    return _table;
}

/*public*/ void PickListModel::makeSorter(JTable* /*table*/) {
#if 0
    try {   // following might fail due to a missing method on Mac Classic
        _sorter = new TableSorter(this);
        _sorter.setTableHeader(table.getTableHeader());
        _sorter.setColumnComparator(String.class, new jmri.util.SystemNameComparator());
        table.setModel(_sorter);
    } catch (Throwable e) { // NoSuchMethodError, NoClassDefFoundError and others on early JVMs
        log->error("makeSorter: Unexpected error: "+e);
    }
#endif
}

/*public*/ JTable* PickListModel::getTable() {
    return _table;
}


/*public*/ void PickListModel::dispose()
{
//    getManager().removePropertyChangeListener(this);
}
QStringList PickListModel::mimeTypes() const
 {
     QStringList types;
     types << "application/vnd.text.list";
     return types;
 }
QMimeData* PickListModel::mimeData(const QModelIndexList &indexes) const
 {
     QMimeData *mimeData = new QMimeData();
//     QByteArray encodedData;

//     QDataStream stream(&encodedData, QIODevice::WriteOnly);

//     foreach (QModelIndex index, indexes) {
//         if (index.isValid()) {
//             QString text = data(index, Qt::DisplayRole).toString();
//             stream << text;
//         }
//     }

//     mimeData->setData("application/vnd.text.list", encodedData);
     QString text = indexes.at(0).data().toString();
     mimeData->setText(text);
     return mimeData;
 }

/*public*/ /*static*/ PickListModel* PickListModel::turnoutPickModelInstance() {
    int num = _listMap->value("turnout");
    if (num!=0) {
        _listMap->insert("turnout", (num+1));
    } else {
        _listMap->insert("turnout", (1));
    }
    return new TurnoutPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::sensorPickModelInstance() {
    int num = _listMap->value("sensor");
    if (num!=0) {
        _listMap->insert("sensor", num +1);
    } else {
        _listMap->insert("sensor", (1));
    }
    return new SensorPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::multiSensorPickModelInstance() {
    int num = _listMap->value("multisensor");
    if (num!=0) {
        _listMap->insert("multisensor", num+1);
    } else {
        _listMap->insert("multisensor", (1));
    }
    return new MultiSensorPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::signalHeadPickModelInstance() {
    int num = _listMap->value("sensor");
    if (num!=0) {
        _listMap->insert("signalhead", (num+1));
    } else {
        _listMap->insert("signalhead", (1));
    }
    return new SignalHeadPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::signalMastPickModelInstance() {
    int num = _listMap->value("signalmast");
    if (num!=0) {
        _listMap->insert("signalmast", num+1);
    } else {
        _listMap->insert("signalmast", (1));
    }
    return new SignalMastPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::memoryPickModelInstance() {
    int num = _listMap->value("memory");
    if (num!=0) {
        _listMap->insert("memory", num+1);
    } else {
        _listMap->insert("memory", (1));
    }
    return new MemoryPickModel();
}

//@Nonnull
/*public*/ /*static*/ PickListModel* PickListModel::blockPickModelInstance() {
    int num = _listMap->value("block");
    if (num != 0) {
        _listMap->insert("block", num + 1);
    } else {
        _listMap->insert("block", 1);
    }
    return new BlockPickModel();
}

/*public*/ /*static*/ PickListModel* PickListModel::reporterPickModelInstance() {
    int num = _listMap->value("reporter");
    if (num!=0) {
        _listMap->insert("reporter", num+1);
    } else {
        _listMap->insert("reporter", (1));
    }
    return new ReporterPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::lightPickModelInstance() {
    int num = _listMap->value("light");
    if (num!=0) {
        _listMap->insert("light", num+1);
    } else {
        _listMap->insert("light", (1));
    }
    return new LightPickModel();
}
#if 1
/*public*/ /*static*/ PickListModel* PickListModel::oBlockPickModelInstance() {
    int num = _listMap->value("oBlock");
    if (num!=0) {
        _listMap->insert("oBlock", num+1);
    } else {
        _listMap->insert("oBlock", (1));
    }
    return new OBlockPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::warrantPickModelInstance() {
    int num = _listMap->value("warrant");
    if (num!=0) {
        _listMap->insert("warrant", num+1);
    } else {
        _listMap->insert("warrant", (1));
    }
    return new WarrantPickModel();
}
#endif
/*public*/ /*static*/ PickListModel* PickListModel::conditionalPickModelInstance() {
    int num = _listMap->value("conditional");
    if (num!=0) {
        _listMap->insert("conditional", num+1);
    } else {
        _listMap->insert("conditional", (1));
    }
    return new ConditionalPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::entryExitPickModelInstance() {
    int num = _listMap->value("entryExit");
    if (num!=0) {
        _listMap->insert("entryExit", num+1);
    } else {
        _listMap->insert("entryExit", (1));
    }
    return new EntryExitPickModel();
}
/*public*/ /*static*/ PickListModel* PickListModel::logixPickModelInstance() {
    int num = _listMap->value("logix");
    if (num!=0) {
        _listMap->insert("logix", num+1);
    } else {
        _listMap->insert("logix", (1));
    }
    return new LogixPickModel();
}

//static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PickListModel.class.getName());
//}

//class TurnoutPickModel extends PickListModel {
TurnoutPickModel::TurnoutPickModel (QObject *parent) : PickListModel(parent)
{
 manager = InstanceManager::turnoutManagerInstance();
 _name = tr("Turnout Table");
// QList<Manager*> list = ((ProxyTurnoutManager*)manager)->getManagerList();
// foreach(Manager*m, list)
// {
//  AbstractTurnoutManager* mgr = (AbstractTurnoutManager*)m;
//  connect(mgr, SIGNAL(newTurnoutCreated(AbstractTurnoutManager*,Turnout*)), this, SLOT(newTurnoutCreated(AbstractTurnoutManager*,Turnout*)));
// }
}
/*public*/ Manager* TurnoutPickModel::getManager() {
 manager = InstanceManager::turnoutManagerInstance();
    return manager;
}
/*public*/ NamedBean* TurnoutPickModel::getBySystemName(QString name) {
    return manager->getBySystemName(name);
}
/*public*/ NamedBean* TurnoutPickModel::addBean(QString name) {
    return ((ProxyTurnoutManager*)manager)->provideTurnout(name);
}
/*public*/ NamedBean* TurnoutPickModel::addBean(QString sysName, QString userName) {
    return ((ProxyTurnoutManager*)manager)->newTurnout(sysName, userName);
}
/*public*/ bool TurnoutPickModel::canAddBean() {
    return true;
}
void TurnoutPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";TurnoutIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void TurnoutPickModel::newTurnoutCreated(AbstractTurnoutManager *, Turnout *t)
{
 makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}

//;}

//class SensorPickModel extends PickListModel {
SensorPickModel::SensorPickModel (QObject *parent) : PickListModel(parent)
{
 manager = InstanceManager::sensorManagerInstance();
 _name = tr("Sensor Table");
// QList<Manager*> list = ((ProxySensorManager*)manager)->getManagerList();
// foreach(Manager*m, list)
// {
//  AbstractSensorManager* mgr = (AbstractSensorManager*)m;
//  connect(mgr, SIGNAL(beanCreated(NamedBean*)), this, SLOT(newSensorCreated(NamedBean*)));
// }
}
/*public*/ Manager* SensorPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* SensorPickModel::getBySystemName(QString name) {
    return ((ProxySensorManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* SensorPickModel::addBean(QString name) {
    return ((ProxySensorManager*)manager)->provideSensor(name);
}
/*public*/ NamedBean* SensorPickModel::addBean(QString sysName, QString userName) {
    return ((ProxySensorManager*)manager)->newSensor(sysName, userName);
}
/*public*/ bool SensorPickModel::canAddBean()
{
    return true;
}
void SensorPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";SensorIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void SensorPickModel::newSensorCreated( NamedBean *t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};

//class MultiSensorPickModel extends SensorPickModel {
MultiSensorPickModel::MultiSensorPickModel (QObject *parent) : SensorPickModel(parent)
{
 //super();
_position = new QMap <int, QString> ();

}
/*public*/ QVariant MultiSensorPickModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
  int c = index.column();
  int r = index.row();
  if (c==POSITION_COL)
  {
   return _position->value(r);
  }
  return SensorPickModel::data(index,role);
 }
 return QVariant();
}

/*public*/ bool  MultiSensorPickModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
     int c = index.column();
     int r = index.row();
    if (c==POSITION_COL) {
        _position->insert( r , value.toString());
    }
 }
 return true;
}

void MultiSensorPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";MultiSensorIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
//};

//class SignalHeadPickModel extends PickListModel {
SignalHeadPickModel::SignalHeadPickModel (QObject *parent) : PickListModel(parent)
{
 manager = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"));
 _name = tr("Signal Table");
 AbstractSignalHeadManager* mgr = (AbstractSignalHeadManager*)manager;
 connect(mgr, SIGNAL(beanCreated(NamedBean*)),this, SLOT(newSignalHeadCreated(NamedBean*)));
}
/*public*/ Manager* SignalHeadPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* SignalHeadPickModel::getBySystemName(QString name) {
    return ((AbstractSignalHeadManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* SignalHeadPickModel::addBean(QString name) {
    return ((AbstractSignalHeadManager*)manager)->getSignalHead(name);
}
/*public*/ NamedBean* SignalHeadPickModel::addBean(QString sysName,QString userName) {
    SignalHead* sh = manager->getSignalHead(userName);
    if (sh==NULL) {
        sh = ((AbstractSignalHeadManager*)manager)->getSignalHead(sysName);
    }
    return sh;
}
/*public*/ bool SignalHeadPickModel::canAddBean() {
    return false;
}
void SignalHeadPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";SignalHeadIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void SignalHeadPickModel::newSignalHeadCreated(NamedBean *t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};

//class SignalMastPickModel extends PickListModel {
SignalMastPickModel::SignalMastPickModel (QObject *parent) :PickListModel(parent)
{
 manager = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"));
 _name = tr("Signal Mast Table");
 DefaultSignalMastManager* mgr = (DefaultSignalMastManager*)manager;
 connect(mgr, SIGNAL(beanCreated(NamedBean*)), this, SLOT(newSignalMastCreated(NamedBean*)));
}
/*public*/ Manager* SignalMastPickModel::getManager() {
    return (Manager*)manager;
}
/*public*/ NamedBean* SignalMastPickModel::getBySystemName(QString name) {
    return (NamedBean*)((DefaultSignalMastManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* SignalMastPickModel::addBean(QString name) {
    return (NamedBean*)((DefaultSignalMastManager*)manager)->provideSignalMast(name);
}
/*public*/ NamedBean* SignalMastPickModel::addBean(QString sysName, QString userName) {
    SignalMast* sm = ((DefaultSignalMastManager*)manager)->getSignalMast(userName);
    if (sm==NULL) {
        sm = ((DefaultSignalMastManager*)manager)->provideSignalMast(sysName);
    }
    return (NamedBean*)sm;
}
/*public*/ bool SignalMastPickModel::canAddBean() {
    return false;
}
void SignalMastPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";SignalMastIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void SignalMastPickModel::newSignalMastCreated(NamedBean* t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};

//class MemoryPickModel extends PickListModel {
MemoryPickModel::MemoryPickModel (QObject *parent) : PickListModel(parent) {
    manager = InstanceManager::memoryManagerInstance();
    _name = tr("Memory Table");
    AbstractMemoryManager* mgr = (AbstractMemoryManager*)manager;
    connect(mgr, SIGNAL(newMemoryCreated(Memory*)), this, SLOT(newMemoryCreated(Memory*)));
}
/*public*/ Manager*  MemoryPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* MemoryPickModel::getBySystemName(QString name) {
    return ((AbstractMemoryManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* MemoryPickModel::addBean(QString name) {
    return ((AbstractMemoryManager*)manager)->provideMemory(name);
}
/*public*/ NamedBean* MemoryPickModel::addBean(QString sysName, QString userName) {
    return ((AbstractMemoryManager*)manager)->newMemory(sysName, userName);
}
/*public*/ bool MemoryPickModel::canAddBean() {
    return true;
}
void MemoryPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";MemoryIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void MemoryPickModel::newMemoryCreated(Memory*t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};

//class ReporterPickModel extends PickListModel {
ReporterPickModel::ReporterPickModel (QObject *parent) : PickListModel(parent)
{
 manager = (ReporterManager*)InstanceManager::getDefault("ReporterManager");
 _name = tr("Reporter Table");
 ProxyReporterManager* mgr = (ProxyReporterManager*)manager;
 QList<Manager*> mgrList = mgr->getManagerList();
 for( int i=0; i< mgrList.count(); i++)
 {
  AbstractReporterManager* rMgr = (AbstractReporterManager*)mgrList.at(i);
  connect(rMgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 //??
//    connect(mgr, SIGNAL(beanCreated(NamedBean*)), this, SLOT(newReporterCreated(NamedBean*)));
//    connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

//static class BlockPickModel extends PickListModel<Block> {

//    BlockManager manager = InstanceManager.getDefault(BlockManager.class);

    BlockPickModel::BlockPickModel() {
        _name = tr("Block Table");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Manager* BlockPickModel::getManager()
    {
     manager = (BlockManager*)InstanceManager::getDefault("BlockManager");
        return manager;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* BlockPickModel::addBean(QString name) throw (IllegalArgumentException) {
        return manager->provideBlock(name);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* BlockPickModel::addBean(QString sysName, QString userName) {
        return manager->createNewBlock(sysName, userName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool BlockPickModel::canAddBean() {
        return true;
    }
//};

/*public*/ Manager* ReporterPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* ReporterPickModel::getBySystemName(QString name) {
    return ((AbstractReporterManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* ReporterPickModel::addBean(QString name) {
    return((AbstractReporterManager*)manager)->provideReporter(name);
}
/*public*/ NamedBean* ReporterPickModel::addBean(QString sysName, QString userName) {
    return ((ProxyReporterManager*)manager)->newReporter(sysName, userName);
}
/*public*/ bool ReporterPickModel::canAddBean() {
    return true;
}
void ReporterPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";ReporterIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void ReporterPickModel::newReporterCreated(NamedBean *t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};

//class LightPickModel extends PickListModel {
LightPickModel::LightPickModel (QObject *parent) : PickListModel(parent)
{
 manager = InstanceManager::lightManagerInstance();
 _name = tr("Light Table");
 QList<Manager*> list = ((ProxyLightManager*)manager)->getManagerList();
 foreach(Manager*m, list)
 {
  AbstractLightManager* mgr = (AbstractLightManager*)m;
  connect(mgr->pcs, SIGNAL(beanCreated(NamedBean*)), this, SLOT(newLightCreated(NamedBean*)));
 }
}
/*public*/ Manager* LightPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* LightPickModel::getBySystemName(QString name) {
    return (NamedBean*)((AbstractLightManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* LightPickModel::addBean(QString name) {
    return ((AbstractLightManager*)manager)->provideLight(name);
}
/*public*/ NamedBean* LightPickModel::addBean(QString sysName, QString userName) {
    return ((AbstractLightManager*)manager)->newLight(sysName, userName);
}
/*public*/ bool LightPickModel::canAddBean() {
    return true;
}
void LightPickModel::tableClicked(QModelIndex index)
{
 QString name = index.data().toString();
 QDrag* dr = new QDrag(getTable());
 QMimeData *data = new QMimeData;
 data->setText(name+";LightIcon");
 // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}
void LightPickModel::newLightCreated(NamedBean*t)
{
 //makePickList();
 _pickList->append((NamedBean*)t);
 fireTableRowsInserted(_pickList->count()-1,_pickList->count()-1);
}
//};
#if 1
//class OBlockPickModel extends PickListModel {
//    OBlockManager* manager;
OBlockPickModel::OBlockPickModel (QObject *parent) : PickListModel(parent)
{
 //manager = InstanceManager::oBlockManagerInstance();
 manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 _name = tr("Block Table");
}
/*public*/ Manager* OBlockPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* OBlockPickModel::getBySystemName(QString name) {
    return (NamedBean*)manager->getBySystemName(name);
}
/*public*/ NamedBean* OBlockPickModel::addBean(QString name) {
    return (NamedBean*)manager->provideOBlock(name);
}
/*public*/ NamedBean* OBlockPickModel::addBean(QString sysName, QString userName) {
    return (NamedBean*)manager->createNewOBlock(sysName, userName);
}
/*public*/ bool OBlockPickModel::canAddBean() {
    return true;
}
//};

//class WarrantPickModel extends PickListModel {
//WarrantManager* manager;
WarrantPickModel::WarrantPickModel (QObject *parent) : PickListModel(parent)
{
 //manager = InstanceManager::warrantManagerInstance();
 manager = (WarrantManager*)InstanceManager::getDefault("WarrantManager");
 _name = tr("Warrant Table");
}
/*public*/ Manager* WarrantPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* WarrantPickModel::getBySystemName(QString name) {
    return (NamedBean*)manager->getBySystemName(name);
}
/*public*/ NamedBean* WarrantPickModel::addBean(QString name) {
    return (NamedBean*) manager->provideWarrant(name);
}
/*public*/ NamedBean* WarrantPickModel::addBean(QString sysName, QString userName) {
    return (NamedBean*)manager->createNewWarrant(sysName, userName,false, 0);
}
/*public*/ bool WarrantPickModel::canAddBean() {
    return false;
}
//};
#endif
//class ConditionalPickModel extends PickListModel {
ConditionalPickModel::ConditionalPickModel (QObject* parent) : PickListModel(parent)
{
 manager = static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"));
 _name = tr("Conditional Table");
}
/*public*/ Manager* ConditionalPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* ConditionalPickModel::getBySystemName(QString name) {
    return ((DefaultConditionalManager*)manager)->getBySystemName(name);
}
/*public*/ NamedBean* ConditionalPickModel::addBean(QString name) {
    return ((DefaultConditionalManager*)manager)->createNewConditional(name, NULL);
}
/*public*/ NamedBean* ConditionalPickModel::addBean(QString sysName, QString userName) {
    return ((DefaultConditionalManager*)manager)->createNewConditional(sysName, userName);
}
/*public*/ bool ConditionalPickModel::canAddBean() {
    return false;
}
#if 0
/*public*/ JTable makePickTable() {
    JTable table = super.makePickTable();
    TableColumn column = new TableColumn(PickListModel.POSITION_COL);
    column.setResizable(true);
    column.setMinWidth(100);
    column.setHeaderValue("Logix");
    table.addColumn(column);
    return table;
}

/*public*/ Object getValueAt (int r, int c) {
    if (c==POSITION_COL) {
        jmri.Logix l = manager.getParentLogix(_pickList->get(r).getSystemName());
        if (l!=NULL) {
            return l.getDisplayName();
        }
    }
    return super.getValueAt(r, c);
}
//}
#endif
//class EntryExitPickModel extends PickListModel {

EntryExitPickModel::EntryExitPickModel (QObject* parent): PickListModel(parent) {
    manager = (EntryExitPairs*) InstanceManager::getDefault("EntryExitPairs");
    _name = tr("Entry Exit Table");
}
/*public*/ Manager* EntryExitPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* EntryExitPickModel::getBySystemName(QString name) {
    return (NamedBean*)manager->getBySystemName(name);
}

/*public*/ NamedBean* EntryExitPickModel::addBean(QString /*name*/) {
    return NULL;
}
/*public*/ NamedBean* EntryExitPickModel::addBean(QString /*sysName*/, QString /*userName*/) {
    return NULL;
}
/*public*/ bool EntryExitPickModel::canAddBean() {
    return false;
}

/*public*/ QVariant EntryExitPickModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  if (section == SNAME_COLUMN)
  {
   return "Unique Id";
  }
  else if (section == UNAME_COLUMN)
  {
   return tr("User Name");
  }
 }
 return QVariant();
}
//};

LogixPickModel::LogixPickModel (QObject* parent): PickListModel(parent) {
    manager = (LogixManager*) InstanceManager::getDefault("LogixManager");
    _name = tr("Logix Table");
}
/*public*/ Manager* LogixPickModel::getManager() {
    return manager;
}
/*public*/ NamedBean* LogixPickModel::getBySystemName(QString name) {
    return (NamedBean*)manager->getBySystemName(name);
}

/*public*/ NamedBean* LogixPickModel::addBean(QString /*name*/) {
    return NULL;
}
/*public*/ NamedBean* LogixPickModel::addBean(QString /*sysName*/, QString /*userName*/) {
    return NULL;
}
/*public*/ bool LogixPickModel::canAddBean() {
    return false;

}/*public*/ QVariant LogixPickModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  if (section == SNAME_COLUMN)
  {
   return "Unique Id";
  }
  else if (section == UNAME_COLUMN)
  {
   return tr("User Name");
  }
 }
 return QVariant();
}

