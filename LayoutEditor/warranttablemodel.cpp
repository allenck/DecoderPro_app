#include "warranttablemodel.h"
#include "instancemanager.h"
#include "warrantmanager.h"
#include "warrant.h"
#include "QPushButton"
#include "jtextfield.h"
#include "QRadioButton"
#include "QButtonGroup"
#include "blockorder.h"
#include "oblock.h"
#include "namedicon.h"
#include "warranttableframe.h"
#include "rosterentry.h"
#include <QMessageBox>
#include "warranttableaction.h"
#include "warrantframe.h"
#include "oblock.h"
#include <QTableView>
#include <QPushButton>
#include "fileutil.h"

//WarrantTableModel::WarrantTableModel(QObject *parent) :
//  BeanTableDataModel(parent)
//{
//}
/**
 * Table Model for the Warrant List
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Pete Cressman Copyright (C) 2009, 2010
 */

//class WarrantTableModel extends jmri.jmrit.beantable.BeanTableDataModel // AbstractTableModel
                                                                        // implements
                                                                        // PropertyChangeListener
//{
    //private static final long serialVersionUID = 6318203351014416147L;
/**
 * Table Model for the Warrant List
 * <P>
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Pete Cressman Copyright (C) 2009, 2010
 */

//class WarrantTableModel extends jmri.jmrit.beantable.BeanTableDataModel // AbstractTableModel
//                                                                        // implements
//                                                                        // PropertyChangeListener
//{
/*static*/ QColor WarrantTableModel::myGreen =  QColor(0, 100, 0);
/*static*/ QColor WarrantTableModel::myGold =  QColor(200, 100, 0);



/*public*/ WarrantTableModel::WarrantTableModel(WarrantTableFrame* frame, QObject *parent) :
BeanTableDataModel(parent)
{
 //super();
 log = new Logger("WarrantTableModel");
 _frame = frame;
 _manager = (WarrantManager*)InstanceManager
   ::getDefault("WarrantManager");
 // _manager.addPropertyChangeListener(this); // for adds and deletes
 _warList =  QList<Warrant*>();
 _warNX =  QList<Warrant*>();
}

/*public*/ void WarrantTableModel::addHeaderListener(JTable* table) {
//    addMouseListenerToHeader(table);
}

//@Override
/*public*/ Manager* WarrantTableModel::getManager() {
 _manager = (WarrantManager*)InstanceManager::getDefault("WarrantManager");
    return _manager;
}

//@Override
/*public*/ NamedBean* WarrantTableModel::getBySystemName(QString name)  const{
    return _manager->getBySystemName(name);
}

//@Override
/*public*/ QString WarrantTableModel::getValue(QString name) {
    return _manager->getBySystemName(name)->getDisplayName();
}

//@Override
/*public*/ NamedBean* WarrantTableModel::getByUserName(QString name) {
    return _manager->getByUserName(name);
}

//@Override
/*protected*/ QString WarrantTableModel::getBeanType() {
    return "Warrant";
}

//@Override
/*public*/ void WarrantTableModel::clickOn(NamedBean* t) {
}

//@Override
/*protected*/ QString WarrantTableModel::getMasterClassName() {
 return "jmri.jmrit.logix.WarrantTableModel";
}

/**
 * Preserve current listeners so that there is no gap to miss a
 * propertyChange
 */
/*public*/ /*synchronized*/ void WarrantTableModel::init() {
    QList<Warrant*> tempList =  QList<Warrant*>();
    QStringList systemNameList = _manager->getSystemNameList();
    QStringListIterator iter(systemNameList);
    // copy over warrants still listed
    while (iter.hasNext()) {
        Warrant* w = (Warrant*)_manager->getBySystemName(iter.next());
        if (!_warList.contains(w))
        { // new warrant
            w->addPropertyChangeListener((PropertyChangeListener*)this);
            //connect(w->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        } else {
            _warList.removeOne(w);
        }
        tempList.append(w); // add old or any new warrants
    }
    // remove listeners from any deleted warrants
    for (int i = 0; i < _warList.size(); i++) {
        Warrant* w = _warList.at(i);
        if (!_warNX.contains(w))
        { // don't touch current running NXWarrant
            w->removePropertyChangeListener((PropertyChangeListener*)this);
//            disconnect(w->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

        }
    }
    // add in current temporary NX warrants
    for (int i = 0; i < _warNX.size(); i++) {
        tempList.append(_warNX.at(i));
    }
    _warList = tempList;
}

/*protected*/ void WarrantTableModel::haltAllTrains()
{
 QListIterator<Warrant*> iter(_warList);
    while (iter.hasNext()) {
        iter.next()->controlRunTrain(Warrant::HALT);
    }
    //iter = _warNX.iterator();
    iter = QListIterator<Warrant*>(_warNX);
    while (iter.hasNext()) {
        iter.next()->controlRunTrain(Warrant::HALT);
    }
    fireTableDataChanged();
}

/*public*/ void WarrantTableModel::addNXWarrant(Warrant* w) {
    _warList.append(w);
    _warNX.append(w);
    w->addPropertyChangeListener((PropertyChangeListener*)this);
    //connect(w->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    fireTableDataChanged();
}

/**
 * Removes any warrant, not just NXWarrant
 *
 * @param w
 */
/*public*/ void WarrantTableModel::removeNXWarrant(Warrant* w)
{
 w->removePropertyChangeListener((PropertyChangeListener*)this);
 //disconnect(w->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    _warList.removeOne(w);
    _warNX.removeOne(w);
    _manager->deregister(w);
    w->dispose();
}

/*public*/ Warrant* WarrantTableModel::getWarrantAt(int index) const
{
    if (index >= _warList.size()) {
        return NULL;
    }
    return _warList.at(index);
}

/*protected*/ Warrant* WarrantTableModel::getWarrant(QString name) {
    if (name==NULL || name.length()==0) {
        return NULL;
    }
    foreach (Warrant* w, _warList) {
        if (name==(w->getUserName()) || name==(w->getSystemName())) {
            return w;
        }
    }
    foreach (Warrant* w, _warNX) {
        if (name==(w->getUserName()) || name==(w->getSystemName())) {
            return w;
        }
    }
    return NULL;
}

//@Override
/*public*/ int WarrantTableModel::rowCount(const QModelIndex &parent) const
{
    return _warList.size();
}

/*private*/ int WarrantTableModel::getRow(Warrant* w) {
    int row = -1;
    QListIterator<Warrant*> iter(_warList);
    while (iter.hasNext()) {
        row++;
        if (iter.next()==(w)) {
            return row;
        }
    }
    return -1;
}

//@Override
/*public*/ int WarrantTableModel::columnCount(const QModelIndex &parent) const
{
    return NUMCOLS;
}

//@Override
/*public*/ QVariant WarrantTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
    case WARRANT_COLUMN:
        return tr("Warrant");
    case ROUTE_COLUMN:
        return tr("Route");
    case TRAIN_NAME_COLUMN:
        return tr("TrainName");
    case ADDRESS_COLUMN:
        return tr("DccAddress");
    case ALLOCATE_COLUMN:
        return tr("Allocate");
    case DEALLOC_COLUMN:
        return tr("Deallocate");
    case SET_COLUMN:
        return tr("SetRoute");
    case AUTO_RUN_COLUMN:
        return tr("ARun");
    case MANUAL_RUN_COLUMN:
        return tr("MRun");
    case CONTROL_COLUMN:
        return tr("Control");
    }
    return "";
 }
 return QVariant();
}

//@Override
/*public*/ Qt::ItemFlags WarrantTableModel::flags(const QModelIndex &index) const
{
 int col = index.column();
    switch (col)
    {
    case WARRANT_COLUMN:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    case TRAIN_NAME_COLUMN:
    case ADDRESS_COLUMN:
    case ROUTE_COLUMN:
    case ALLOCATE_COLUMN:
    case DEALLOC_COLUMN:
    case SET_COLUMN:
    case AUTO_RUN_COLUMN:
    case MANUAL_RUN_COLUMN:
    case CONTROL_COLUMN:
    case EDIT_COLUMN:
    case DELETE_COLUMN:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

//@Override
/*public*/ QString WarrantTableModel::getColumnClass(int col) {
    switch (col) {
    case WARRANT_COLUMN:
        return "String";
    case ROUTE_COLUMN:
        return "String"; // JComboBox.class;
    case TRAIN_NAME_COLUMN:
        return "String";
    case ADDRESS_COLUMN:
        return "String";
    case ALLOCATE_COLUMN:
        return "JButton";
    case DEALLOC_COLUMN:
        return "JButton";
    case SET_COLUMN:
        return "JButton";
    case AUTO_RUN_COLUMN:
        return "JButton";
    case MANUAL_RUN_COLUMN:
        return "JButton";
    case CONTROL_COLUMN:
        return "String"; // JComboBox.class;
    case EDIT_COLUMN:
        return "JButton";
    case DELETE_COLUMN:
        return "JButton";
    }
    return "String";
}

//@Override
/*public*/ int WarrantTableModel::getPreferredWidth(int col) {
    switch (col) {
    case WARRANT_COLUMN:
    case TRAIN_NAME_COLUMN:
        return  JTextField(13).sizeHint().width();
    case ROUTE_COLUMN:
        return  JTextField(25).sizeHint().width();
    case ADDRESS_COLUMN:
        return  JTextField(7).sizeHint().width();
    case ALLOCATE_COLUMN:
    case DEALLOC_COLUMN:
    case SET_COLUMN:
    case AUTO_RUN_COLUMN:
    case MANUAL_RUN_COLUMN:
        return  QPushButton("Xxxx").sizeHint().width();
    case CONTROL_COLUMN:
        return  JTextField(45).sizeHint().width();
    case EDIT_COLUMN:
    case DELETE_COLUMN:
        return  QPushButton("DELETE").sizeHint().width();
    }
    return  JTextField(10).sizeHint().width();
}

//@Override
/*public*/ QVariant WarrantTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int col = index.column();
  int row = index.row();
  // if (log->isDebugEnabled())
  // log->debug("getValueAt: row= "+row+", column= "+col);
  Warrant* w = getWarrantAt(row);
  // some error checking
  if (w == NULL) {
      log->warn("getValueAt row= " + QString::number(row) + " Warrant is NULL!");
      return "";
  }
  QRadioButton* allocButton = new QRadioButton();
  QRadioButton* deallocButton = new QRadioButton();
  QButtonGroup* group = new QButtonGroup();
  group->addButton(allocButton);
  group->addButton(deallocButton);
  switch (col)
  {
   case WARRANT_COLUMN:
       return w->getDisplayName();
   case ROUTE_COLUMN:
   {
    BlockOrder* bo = w->getfirstOrder();
    if (bo != NULL)
    {
     return tr("Origin: %1").arg( bo->getBlock()
                ->getDisplayName());
    }
    break;
   }
   case TRAIN_NAME_COLUMN:
    return w->getTrainName();
   case ADDRESS_COLUMN:
   {
    if (w->getDccAddress() != NULL)
    {
     return w->getDccAddress()->toString();
    }
    break;
   }
   case ALLOCATE_COLUMN:
   {
    if (w->isTotalAllocated())
    {
//         return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                 "resources/icons/smallschematics/tracksegments/circuit-green.gif",
//                 "occupied"));
     return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-green.gif");
//         return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                 "resources/icons/smallschematics/tracksegments/circuit-occupied.gif",
//                 "occupied"));
     return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");

    }
    else
    {
//         return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                 "resources/icons/smallschematics/tracksegments/circuit-empty.gif",
//                 "off"));
     return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");

    }
   }
   case DEALLOC_COLUMN:
    if (w->isAllocated())
    {
//            return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                    "resources/icons/smallschematics/tracksegments/circuit-empty.gif",
//                    "off"));
     return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
    }
//        return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                "resources/icons/smallschematics/tracksegments/circuit-occupied.gif",
//                "occupied"));
    return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif");
   case SET_COLUMN:
   {
    //NamedIcon* icon;
    QString path;
    QString name;
    if (w->hasRouteSet() && w->isTotalAllocated())
    {
//         return VPtr<NamedIcon>::asQVariant(new NamedIcon(
     path  =    ":/resources/icons/smallschematics/tracksegments/circuit-green.gif";
     name =      "off";
    }
    else if (w->hasRouteSet() && w->isAllocated())
    {
//         return  VPtr<NamedIcon>::asQVariant(
     //icon =new NamedIcon(
     path  =         ":/resources/icons/smallschematics/tracksegments/circuit-occupied.gif";
     name =         "occupied";
    }
    else
    {
//         return VPtr<NamedIcon>::asQVariant(
       //icon =    new NamedIcon(
     path  =        ":/resources/icons/smallschematics/tracksegments/circuit-empty.gif";
     name =        "occupied";
    }
    return QIcon(path);
   }
    case AUTO_RUN_COLUMN:
    {
     if (w->getRunMode() == Warrant::MODE_RUN)
     {
//            return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                    "resources/icons/smallschematics/tracksegments/circuit-error.gif",
//                    "red"));
      return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
     }
//        return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                "resources/icons/smallschematics/tracksegments/circuit-empty.gif",
//                "off"));
     return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
  }
  case MANUAL_RUN_COLUMN:
  {
   if (w->getRunMode() == Warrant::MODE_MANUAL)
   {
//            return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                    "resources/icons/smallschematics/tracksegments/circuit-error.gif",
//                    "red"));
    return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-error.gif");
   }
//        return VPtr<NamedIcon>::asQVariant(new NamedIcon(
//                "resources/icons/smallschematics/tracksegments/circuit-empty.gif",
//                "off"));
   return QIcon(":/resources/icons/smallschematics/tracksegments/circuit-empty.gif");
  }
  case CONTROL_COLUMN:
  {
   QString msg = w->getRunningMessage();
   return msg;
  }
  case EDIT_COLUMN:
  {
   return tr("Edit");
  }
  case DELETE_COLUMN:
  {
   return tr("Delete");
  }
  return "";
  }
 }
 return QVariant();
}

//@Override
/*public*/ bool WarrantTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();

  if (log->isDebugEnabled())
      log->debug("setValueAt: row= " + QString::number(row) + ", column= " + QString::number(col) + ", value= " + QString(value.typeName()));
  Warrant* w = getWarrantAt(row);
  if (w == NULL) {
      log->warn("setValueAt row= " + QString::number(row) + " Warrant is NULL!");
      return false;
  }
  QString msg = NULL;
  switch (col)
  {
    case WARRANT_COLUMN:
    case ROUTE_COLUMN:
        return true;
    case TRAIN_NAME_COLUMN:
     w->setTrainName( value.toString());
        break;
    case ADDRESS_COLUMN:
    {
     QString addr = value.toString();
     if (!w->setDccAddress(addr))
     {
      msg = tr("\"%1\" is not a valid DCC address.").arg( addr);
     }
     break;
    }
    case ALLOCATE_COLUMN:
    {
     msg = w->allocateRoute(true, NULL);
     if (msg == NULL)
     {
      _frame->setStatusText(
              tr("Warrant \"%1\" allocated.").arg(
          w->getDisplayName()),myGreen,false);
     }
     else
     {
      _frame->setStatusText(msg, myGold, false);
      msg = "";
     }
     break;
    }
    case DEALLOC_COLUMN:
    {
     if (w->getRunMode() == Warrant::MODE_NONE)
     {
         w->deAllocate();
         _frame->setStatusText("", myGreen, false);
     } else {
         _frame->setStatusText(w->getRunModeMessage(), myGold, false);
     }
     break;
    }
    case SET_COLUMN:
    {
     msg = w->setRoute(0, NULL);
     if (msg == NULL) {
         _frame->setStatusText(
                 tr("Warrant \"%1\" allocated blocks have paths set.").arg( w->getDisplayName()), myGreen, false);
     }
     else
     {
      w->deAllocate();
      _frame->setStatusText(msg, myGold, false);
         msg = "";
     }
     break;
    }
    case AUTO_RUN_COLUMN:
    {
     msg = _frame->runTrain(w, Warrant::MODE_RUN);
     break;
    }
    case MANUAL_RUN_COLUMN:
    {
     if (w->getRunMode() == Warrant::MODE_NONE)
     {
      if (w->getBlockOrders()->size() == 0)
      {
          msg = tr("EmptyRoute");
          break;
      }
      msg = w->setRoute(0, NULL);
      if (msg == NULL)
      {
       msg = w->setRunMode(Warrant::MODE_MANUAL, NULL, NULL, NULL,
                  false);
      }
      if (msg != NULL)
      {
       w->deAllocate();
      }
      else
      {
       msg = w->checkStartBlock(Warrant::MODE_RUN); // notify first block occupied by
       // this train
       if (msg != NULL)
       {
        _frame->setStatusText(msg, WarrantTableModel::myGold,
                   false);
       }
      }
      if (log->isDebugEnabled())
          log->debug("w->runManualTrain= " + msg);
     } else {
         msg = w->getRunModeMessage();
     }
     break;
    }
    case CONTROL_COLUMN:
    {
     // Message is set when propertyChangeEvent (below) is received from
     // a warrant
     // change. fireTableRows then causes getValueAt() which calls
     // getRunningMessage()
     int mode = w->getRunMode();
     if (mode == Warrant::MODE_LEARN)
     {
      tr("Learn Mode in Block %1.").arg( w->getCurrentBlockOrder()
                 ->getBlock()->getDisplayName());
     }
     else
     {
      QString setting =  value.toString();
      if (mode == Warrant::MODE_RUN || mode == Warrant::MODE_MANUAL)
      {
       int s = -1;
       if (setting==(WarrantTableFrame::halt))
       {
           s = Warrant::HALT;
       } else if (setting==(WarrantTableFrame::resume))
       {
           s = Warrant::RESUME;
       } else if (setting==(WarrantTableFrame::retry))
       {
           s = Warrant::RETRY;
       } else if (setting==(WarrantTableFrame::abort))
       {
           s = Warrant::ABORT;
       }
       w->controlRunTrain(s);
      } else if (setting==(WarrantTableFrame::abort))
      {
          w->deAllocate();
      } else if (mode == Warrant::MODE_NONE)
      {
       msg = tr("Warrant \"%1\" not set for running.").arg( w->getDisplayName());
      }
      else
      {
       //getValueAt(row, col);
       index.data();
      }
     }
     break;
    }
    case EDIT_COLUMN:
    {
     openWarrantFrame(w);
     break;
    }
    case DELETE_COLUMN:
    {
     if (w->getRunMode() == Warrant::MODE_NONE)
     {
      removeNXWarrant(w); // removes any warrant
     }
     else
     {
      w->controlRunTrain(Warrant::ABORT);
      if (_warNX.contains(w))
      { // don't remove regular warrants
       removeNXWarrant(w);
      }
     }
     break;
    }
   }
   if (msg != NULL)
   {
//        JOptionPane.showMessageDialog(NULL, msg,
//                tr("WarningTitle"),
//                JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(NULL, tr("Warning"), msg);
   _frame->setStatusText(msg, QColor(Qt::red), true);
  }
  fireTableRowsUpdated(row, row);
  return true;
 }
 return false;
}

/*private*/ void WarrantTableModel::openWarrantFrame(Warrant* warrant)
{
 if (WarrantTableAction::_openFrame != NULL)
 {
  WarrantTableAction::_openFrame->dispose();
 }
 WarrantTableAction::_openFrame = NULL;
 for (int i = 0; i < _warList.size(); i++)
 {
  if (warrant==(_warList.at(i)))
  {
   WarrantTableAction::_openFrame = new WarrantFrame(warrant);
   break;
  }
 }
 if (WarrantTableAction::_openFrame == NULL)
 {
  for (int i = 0; i < _warNX.size(); i++)
  {
   if (warrant==(_warList.at(i)))
   {
    WarrantTableAction::_openFrame = new WarrantFrame(warrant);
    break;
   }
  }
  if (WarrantTableAction::_openFrame != NULL)
  {
   WarrantTableAction::_openFrame->setVisible(true);
   WarrantTableAction::_openFrame->toFront();
  }
 }
}

//@Override
/*public*/ void WarrantTableModel::propertyChange(PropertyChangeEvent* e)
{
 QString property = e->getPropertyName();
 if (property==("length"))
 {
  // a NamedBean added or deleted
  init();
  fireTableDataChanged();
 }
 //else if (e->getSource() instanceof Warrant)
 else if(qobject_cast<Warrant*>(e->getSource()))
 {
  // a value changed. Find it, to avoid complete redraw
  Warrant* bean = (Warrant*) e->getSource();
  for (int i = 0; i < _warList.size(); i++) {
      if (bean==(_warList.at(i))) {

          if (_warNX.contains(bean)
                  && ((property==("runMode") && e->getNewValue().toInt() == Warrant::MODE_NONE)) || (property
                          ==("controlChange") && e->getNewValue().toInt() == Warrant::ABORT)) {
              //fireTableRowsDeleted(i, i);
           beginRemoveRows(QModelIndex(), i,i);
/*                        try { // TableSorter needs time to get its row count updated
                  Thread.sleep(50);
              } catch (InterruptedException ie) {
              }*/
              removeNXWarrant(bean);
              endRemoveRows();
          } else {
              fireTableRowsUpdated(i, i);
          }
          break;
      }
  }
  if (e->getPropertyName()==("blockChange")) {
      OBlock* oldBlock = (OBlock*) VPtr<OBlock>::asPtr(e->getOldValue());
      OBlock* newBlock = (OBlock*) VPtr<OBlock>::asPtr(e->getNewValue());
      if (newBlock == NULL) {
          _frame->setStatusText(
                  tr("Warrant %1 Location of \"%3\" unknown. Train left route at block \"%2\".").arg(
                          bean->getDisplayName()).arg(
                          oldBlock->getDisplayName()).arg(
                          bean->getTrainName()), QColor(Qt::red), true);
      } else {
          _frame->setStatusText(
                  tr("Train \"%1\" entering block \"%2\".").arg(
                          bean->getTrainName()).arg(
                          newBlock->getDisplayName()), myGreen, true);
      }
  } else if (e->getPropertyName()==("blockRelease")) {
      OBlock* block = (OBlock*) VPtr<OBlock>::asPtr(e->getNewValue());
      long et = (QDateTime::currentMSecsSinceEpoch() - block->_entryTime) / 1000;
      _frame->setStatusText(tr("Train \"%1\" leaving block \"%2\". Occupied block for %3 minutes %4 seconds.").arg(
              bean->getTrainName()).arg(block->getDisplayName()).arg(et / 60,
              et % 60),myGreen, true);
  } else if (e->getPropertyName()==("SpeedRestriction")) {
      _frame->setStatusText(tr("Train \"%1\" speed set to %3 in block \"%2\".").arg(
              bean->getTrainName()).arg(bean->getCurrentBlockOrder()
                      ->getBlock()->getDisplayName()).arg(e->getNewValue().toString()),
              myGold, true);
  } else if (e->getPropertyName()==("SpeedChange")) {
      int row = getRow(bean);
      if (row>=0) {
          fireTableRowsUpdated(row, row);
//                    _frame->setStatusText(bean->getRunningMessage(), myGreen, true);
      }
  } else if (e->getPropertyName()==("runMode")) {
      int oldMode =  e->getOldValue().toInt();
      int newMode =  e->getNewValue().toInt();
      if (oldMode == Warrant::MODE_NONE) {
          if (newMode != Warrant::MODE_NONE) {
              _frame->setStatusText(tr("Warrant %2 started for train \"%1\" in block \"%3\" in %4 mode.").arg( bean->getTrainName()).arg(bean->getDisplayName()).arg( bean->getCurrentBlockOrder()->getBlock()
                                                                                          ->getDisplayName()).arg(
                      Warrant::modeName(newMode)),
                      myGreen, true);
          }
      } else if (newMode == Warrant::MODE_NONE) {
          if (oldMode != Warrant::MODE_NONE) {
              OBlock* block = bean->getCurrentBlockOrder()->getBlock();
              int state = block->getState();
              if ((state & OBlock::OCCUPIED) > 0
                      || (state & OBlock::DARK) > 0) {
                  _frame->setStatusText(
                          tr("Warrant %2 ended for train \"%1\". Now occupying block \"%3\".").arg(
                                  bean->getTrainName()).arg(
                                  bean->getDisplayName()).arg(
                                  block->getDisplayName()), myGreen,
                          true);
              } else {
                  _frame->setStatusText(
                          tr("Train \"%1\" ABORTED. (warrant %2)").arg(
                                  bean->getTrainName()).arg(
                                  bean->getDisplayName()), myGreen,
                          true);
              }
          }
      } else {
          _frame->setStatusText(tr("Train \"%1\" mode change from %3 to %4. (warrant %2)").arg(
                  bean->getTrainName()).arg(bean->getDisplayName()).arg(
                  Warrant::modeName(oldMode)).arg(
                  Warrant::modeName(newMode)), myGold,
                  true);
      }
  } else if (e->getPropertyName()==("controlChange")) {
      int runState = e->getOldValue().toInt();
      int newCntrl =  e->getNewValue().toInt();
      QString stateStr = NULL;
      if (runState < 0) {
          stateStr = Warrant::modeName(-runState);
      } else {
//          stateStr = tr(Warrant::RUN_STATE[runState],
//                  bean->getCurrentBlockOrder()->getBlock()
//                          ->getDisplayName());
       QString str = Warrant::RUN_STATE[runState];
       if(str.contains("%1"))
        stateStr = str.replace("%2", bean->getCurrentBlockOrder()->getBlock()
                                                         ->getDisplayName());
      }
      _frame->setStatusText(tr("Control set to %3 on train \"%1\" from state %2").arg(
              bean->getTrainName()).arg( stateStr).arg(
              (Warrant::CNTRL_CMDS[newCntrl])),
              myGold, true);
  } else if (e->getPropertyName()==("throttleFail")) {
      _frame->setStatusText(tr("No throttle for train %1 due to %2").arg(
              bean->getTrainName()).arg(e->getNewValue().toString()), QColor(Qt::red), true);
  }
 }
 if (log->isDebugEnabled())
     log->debug("propertyChange of \"" + e->getPropertyName() + "\" for "
             + e->getSource()->metaObject()->className());
}
void WarrantTableModel::on_buttonClicked(QModelIndex* index, QString name)
{
 setData(*index, QVariant(), Qt::EditRole);
}
