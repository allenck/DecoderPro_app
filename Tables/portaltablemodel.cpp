#include "portaltablemodel.h"
#include "portal.h"
#include "portalmanager.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "oblock.h"
#include <QMessageBox>
#include "jtextfield.h"
#include "QPushButton"
#include "tableframes.h"
#include "guilafpreferencesmanager.h"
#include "portaleditframe.h"
#include "loggerfactory.h"

//PortalTableModel::PortalTableModel(QObject *parent) :
//  BeanTableDataModel(parent)
//{
//}
/**
 * GUI to define OBlocks
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
 * @author	Pete Cressman (C) 2010
 * @version $Revision: 29180 $
 */

///*public*/ class PortalTableModel extends jmri.jmrit.beantable.BeanTableDataModel {


/*public*/ PortalTableModel::PortalTableModel(TableFrames* _parent, QObject *parent) :
  BeanTableDataModel(parent)
{
 //super();
 _parent = _parent;
 _tabbed = ((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isOblockEditTabbed();
 _manager = (PortalManager*)InstanceManager::getDefault("PortalManager");
 _manager->addPropertyChangeListener((PropertyChangeListener*)this);
 if (!_tabbed) {
     // specific stuff for _desktop
     initTempRow();
 }
 for(int i = 0; i < NUMCOLS; i++)
  tempRow.append("");
 log = new Logger("PortalTableModel");
 updateNameList();
}

/*public*/ void PortalTableModel::init() {
    initTempRow();
}

void PortalTableModel::initTempRow()
{
 for (int i = 0; i < NUMCOLS; i++)
 {
  tempRow.replace(i, NULL);
 }
 tempRow.replace(DELETE_COL, tr("Clear"));
}

//@Override
/*public*/ Manager* PortalTableModel::getManager() {
 _manager = (PortalManager*)InstanceManager::getDefault("PortalManager");
    return _manager;
}

//@Override
/*public*/ NamedBean* PortalTableModel::getBySystemName(QString name) const {
    return (NamedBean*)_manager->getBySystemName(name);
}

//@Override
/*public*/ NamedBean *PortalTableModel::getByUserName(QString name) const {
    return (NamedBean*)_manager->getByUserName(name);
}

//@Override
/*protected*/ QString PortalTableModel::getBeanType() {
    return "Portal";
}

//@Override
/*public*/ QString PortalTableModel::getValue(QString name) {
    return name;
}

//@Override
/*public*/ void PortalTableModel::clickOn(NamedBean* t) {
}

//@Override
/*protected*/ QString PortalTableModel::getMasterClassName() {
 return "jmri.jmrit.beantable.PortalTableModel";
}

//@Override
/*public*/ int PortalTableModel::columnCount(const QModelIndex &parent) const{
    return NUMCOLS;
}

//@Override
/*public*/ int PortalTableModel::rowCount(const QModelIndex &parent) const
{
 return BeanTableDataModel::rowCount(QModelIndex()) + 1;
}

//@Override
/*public*/ QVariant PortalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
   case FROM_BLOCK_COLUMN:
       return tr("Block Name");
   case NAME_COLUMN:
       return tr("Portal Name");
   case TO_BLOCK_COLUMN:
       return tr("Block Name");
   case EDIT_COL:
       return "  ";
  }
  return "";
 }
 return QVariant();
}

//@Override
/*public*/ QVariant PortalTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  if (rowCount(QModelIndex()) == row)
  {
   return tempRow[col];
  }
  Portal* portal = _manager->getPortal(row);
  if (portal == nullptr) {
      if (col == DELETE_COL) {
          return tr("Clear");
      }
      return tempRow[col];
  }
  else
  {
   switch (col) {
       case FROM_BLOCK_COLUMN:
           return portal->getFromBlockName();
       case NAME_COLUMN:
           return portal->getName();
       case TO_BLOCK_COLUMN:
           return portal->getToBlockName();
       case DELETE_COL:
           return tr("Delete");
       case EDIT_COL:
           return tr("Edit");default:
           // fall through
           break;
   }
  }
  return "";
 }
 return QVariant();
}

//@Override
/*public*/ bool PortalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();

  QString msg = NULL;
  if (BeanTableDataModel::rowCount(QModelIndex()) == row)
  {
   if (col == DELETE_COL)
   {
    initTempRow();
    fireTableRowsUpdated(row, row);
    return true;
   }
   else
   {
    QString str = value.toString();
    if (str == NULL || str.trimmed().length() == 0)
    {
     tempRow.replace(col, "NULL");
     return true;
   }
   else
   {
       tempRow.replace(col, str.trimmed());
   }
  }
  OBlockManager* OBlockMgr = (OBlockManager*) InstanceManager::getDefault("OBlockManager");
  OBlock* fromBlock = NULL;
  OBlock* toBlock = NULL;
  if (tempRow[FROM_BLOCK_COLUMN] != NULL)
  {
   fromBlock = OBlockMgr->getOBlock(tempRow[FROM_BLOCK_COLUMN]);
   if (fromBlock == NULL) {
       msg = tr("There is no Block named \"%1\".").arg(tempRow[FROM_BLOCK_COLUMN]);
   }
  }
  if (msg==NULL && tempRow[TO_BLOCK_COLUMN] != NULL)
  {
   toBlock = OBlockMgr->getOBlock(tempRow[TO_BLOCK_COLUMN]);
   if (toBlock==NULL) {
       msg = tr("There is no Block named \"%1\".").arg(tempRow[TO_BLOCK_COLUMN]);
   }
  }
  if (msg==NULL && tempRow[NAME_COLUMN] != NULL)
  {
   if (fromBlock == NULL || toBlock==NULL )
   {
       msg = tr("Portal \"%1\" needs to have a Block specified on each side.").arg( tempRow[NAME_COLUMN]);
   } else if (fromBlock==(toBlock)){
       msg = tr("Portal cannot have block \"%1\"\non both sides. (i.e. portal goes nowhere.)").arg(fromBlock->getDisplayName());
   }
   if (msg==NULL) {
       Portal* portal = _manager->createNewPortal( tempRow[NAME_COLUMN]);
       if (portal != NULL) {
           portal->setToBlock(toBlock, false);
           portal->setFromBlock(fromBlock, false);
           initTempRow();
           fireTableDataChanged();
       } else {
        msg = tr("Duplicate name, Portal \"%1\" has been defined.").arg(value.toString());
       }
   }
  }
  if (msg != NULL) {
//      JOptionPane.showMessageDialog(NULL, msg,
//              tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::question(NULL, tr("Warning"), msg,QMessageBox::Yes | QMessageBox::No);
  }
  return true;
 }

 QString name = sysNameList.at(row);
 Portal* portal = (Portal*)_manager->getBySystemName(name);
 if (portal == NULL) {
     log->error("Portal NULL, getValueAt row= " + QString::number(row) + ", col= " + QString::number(col) + ", "
                + "portalListSize= " + QString::number(_manager->getSystemNameArray().length()));
     return true;
 }

 OBlock* block;
 switch (col)
 {
  case FROM_BLOCK_COLUMN:
  {
   block = ((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->getOBlock( value.toString());
   if (block == NULL)
   {
       msg = tr("There is no Block named \"%1\".").arg(value.toString());
       break;
   }
   if (block==(portal->getToBlock())) {
       msg = tr("Portal cannot have block \"%1\"\non both sides. (i.e. portal goes nowhere.)").arg(block->getDisplayName());
       break;
   }
   if (!portal->setFromBlock(block, false))
   {
//       int response = JOptionPane.showConfirmDialog(NULL,
//               tr("BlockPathsConflict", value, portal.getFromBlockName()),
//               tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
//               JOptionPane.WARNING_MESSAGE);
//       if (response == JOptionPane.NO_OPTION)
    if(QMessageBox::question(NULL, tr("Warning"), tr("Paths using this Portal traverse to block \"%2\". If the Block is changed\nto \"%1\", the paths in Block \"%2\" using this portal will become spurs.\nIf you make this change, please verify path connections in blocks %1 and %2. ").arg(value.toString()).arg(portal->getToBlockName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
    {
     break;
    }
   }
   portal->setFromBlock(block, true);
   fireTableRowsUpdated(row, row);
   break;
  }
  case NAME_COLUMN:
  {
   if (_manager->getPortal(value.toString()) != NULL) {
    msg = tr("Duplicate name, Portal \"%1\" has been defined.").arg(  value.toString());
       break;
   }
   if (_manager->getPortal(value.toString()) != NULL) {
       msg = tr("Portal \"%1\" cannot be changed since it is in use\nby Paths and Blocks. Use delete and add new Portal.").arg(value.toString());
   } else {
       portal->setName( value.toString());
       fireTableRowsUpdated(row, row);
   }
   break;
  }
  case TO_BLOCK_COLUMN:
  {
   block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock( value.toString());
   if (block == NULL)
   {
    msg = tr("There is no Block named \"%1\".").arg(value.toString());
    break;
   }
   if (block==(portal->getFromBlock()))
   {
    msg = tr("Portal cannot have block \"%1\"\non both sides. (i.e. portal goes nowhere.)").arg(block->getDisplayName());
    break;
   }
   if (!portal->setToBlock(block, false))
   {
//             int response = JOptionPane.showConfirmDialog(NULL,
//                     tr("BlockPathsConflict", value, portal.getToBlockName()),
//                     tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
//                     JOptionPane.WARNING_MESSAGE);
//             if (response == JOptionPane.NO_OPTION)
     if(QMessageBox::question(NULL, tr("Warning"), tr("Paths using this Portal traverse to block \"%2\". If the Block is changed\nto \"%1\", the paths in Block \"%2\" using this portal will become spurs.\nIf you make this change, please verify path connections in blocks %1 and %2. ").arg(value.toString()).arg(portal->getToBlockName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
     {
         break;
     }
    }
    portal->setToBlock(block, true);
    fireTableRowsUpdated(row, row);
    break;
   }
   case DELETE_COL:
   {
    if (deletePortal(portal)) {
        fireTableDataChanged();
    }
    break;
   }
   case EDIT_COL:
   {
    editPortal(portal);
    break;
   }
   default:
   {
    log->warn(tr("Unhandled column: %1").arg(col));
    break;
   }
  }
  if (msg != NULL) {
//        JOptionPane.showMessageDialog(NULL, msg,
//                tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::question(NULL, tr("Warning"), msg);
  }
 }
    return false;
}

/*private*/ /*static*/ bool PortalTableModel::deletePortal(Portal* portal)
{
// if (JOptionPane.showConfirmDialog(NULL,
//         tr("DeletePortalConfirm",
//                 portal.getName()), tr("WarningTitle"),
//         JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE)
//         == JOptionPane.YES_OPTION)
 if(QMessageBox::question(NULL, tr("Warning"), tr("Deleting a portal will also delete all Paths\nusing the portal. Do you want to delete \"%1\"?").arg(portal->getName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
 {
  OBlockManager* OBlockMgr = (OBlockManager*) InstanceManager::getDefault("OBlockManager");
     QStringList sysNames = OBlockMgr->getSystemNameArray();
     for (int i = 0; i < sysNames.length(); i++) {
         ((OBlock*)OBlockMgr->getBySystemName(sysNames[i]))->removePortal(portal);
     }
     portal->dispose();
     return true;
 }
 return false;
}

/*private*/ void PortalTableModel::editPortal(Portal* portal) {
    if (_tabbed) {
        // open PortalEditFrame
        PortalEditFrame* portalFrame = new PortalEditFrame(tr("Edit Portal %1").arg(portal->getName()), portal, this);
        portalFrame->setVisible(true);
    }
}
//@Override
/*public*/ Qt::ItemFlags PortalTableModel::flags(const QModelIndex &index) const
{
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

//@Override
/*public*/ QString PortalTableModel::getColumnClass(int col) {
 switch (col) {
     case DELETE_COL:
     case EDIT_COL:
         return "JButton";
     default:
         return "String";
 }
}

//@Override
/*public*/ int PortalTableModel::getPreferredWidth(int col) {
    switch (col) {
        case FROM_BLOCK_COLUMN:
        case TO_BLOCK_COLUMN:
     return  JTextField(20).sizeHint().width();
        case NAME_COLUMN:
     return  JTextField(20).sizeHint().width();
        case DELETE_COL:
     return  QPushButton("DELETE").sizeHint().width();
    }
    return 5;
}

/*protected*/ int PortalTableModel::verifyWarning(QString message) {
    return (_parent->verifyWarning(message));
}

/*private*/ /*final*/ /*static*/ Logger* PortalTableModel::log = LoggerFactory::getLogger("PortalTableModel");
