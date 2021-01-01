#include "signaltablemodel.h"
#include "propertychangeevent.h"
#include "portalmanager.h"
#include "portal.h"
#include "instancemanager.h"
#include "decimalformat.h"
#include "oblock.h"
#include "logger.h"
#include "oblockmanager.h"
#include <QMessageBox>
#include <QPushButton>
#include "jtextfield.h"
#include "pushbuttondelegate.h"
#include "jtable.h"
#include "signaleditframe.h"
#include "comparatort.h"

//SignalTableModel::SignalTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
///*public*/ class SignalTableModel extends AbstractTableModel {

    ///*private*/ static final long serialVersionUID = 1150140866074591437L;

#if 1

//static class SignalRow {

//       NamedBean _signal;
//       OBlock _fromBlock;
//       Portal _portal;
//       OBlock _toBlock;
//       float _length;  // adjustment to speed change point
//       bool _isMetric;

SignalTableModel::SignalRow::SignalRow(NamedBean* signal, OBlock* fromBlock, Portal* portal, OBlock* toBlock, float length, bool isMetric)
{
 _signal = signal;
 _fromBlock = fromBlock;
 _portal = portal;
 _toBlock = toBlock;
 _length = length;
 _isMetric = isMetric;
}
void SignalTableModel::SignalRow::setSignal(NamedBean* signal)
{
 _signal = signal;
}
NamedBean* SignalTableModel::SignalRow::getSignal()
{
 return _signal;
}
void SignalTableModel::SignalRow::setFromBlock(OBlock* fromBlock)
{
 _fromBlock = fromBlock;
}
OBlock* SignalTableModel::SignalRow::getFromBlock() {
 return _fromBlock;
}
void SignalTableModel::SignalRow::setPortal(Portal* portal) {
 _portal = portal;
}
Portal* SignalTableModel::SignalRow::getPortal() {
 return _portal;
}
void SignalTableModel::SignalRow::setToBlock(OBlock* toBlock) {
 _toBlock = toBlock;
}
OBlock* SignalTableModel::SignalRow::getToBlock() {
 return _toBlock;
}
void SignalTableModel::SignalRow::setLength(float length) {
 _length = length;
}
float SignalTableModel::SignalRow::getLength() {
 return _length;
}
void SignalTableModel::SignalRow::setMetric(bool isMetric) {
 _isMetric = isMetric;
}
bool SignalTableModel::SignalRow::isMetric() {
 return _isMetric;
}
//   }


/*public*/ SignalTableModel::SignalTableModel(TableFrames* parent) :
  AbstractTableModel(parent)
{
 //super();
 _parent = parent;
 tempRow = QStringList();
 for(int i=0l; i < NUMCOLS; i++) tempRow.append("");
 _tempLen = 0.0f;
 twoDigit = new DecimalFormat("0.00");
 _portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
 log = new Logger("SignalTableModel");
 buttonMap = QList<int>();
}

/*public*/ void SignalTableModel::init()
{
 makeList();
 initTempRow();
}

void SignalTableModel::initTempRow()
{
 for (int i = 0; i < NUMCOLS; i++)
 {
  tempRow.replace(i,NULL);
 }
 tempRow.replace(LENGTHCOL, twoDigit->format(0.0));
 tempRow.replace(UNITSCOL, tr("in"));
 tempRow.replace(DELETE_COL, tr("Clear"));
}

/*private*/ void SignalTableModel::makeList()
{
 QList<SignalRow*> tempList = QList<SignalRow*>();
 // collect signals entered into Portals
 QStringList sysNames = _portalMgr->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++)
 {
  Portal* portal = (Portal*)_portalMgr->getBySystemName(sysNames[i]);
  NamedBean* signal = portal->getFromSignal();
  SignalRow* sr = NULL;
  if (signal != NULL)
  {
   sr = new SignalRow(signal, portal->getFromBlock(), portal, portal->getToBlock(), portal->getFromSignalOffset(), portal->getToBlock()->isMetric());
   addToList(tempList, sr);
  }
  signal = portal->getToSignal();
  if (signal != NULL)
  {
   sr = new SignalRow(signal, portal->getToBlock(), portal, portal->getFromBlock(), portal->getToSignalOffset(), portal->getFromBlock()->isMetric());
   addToList(tempList, sr);
  }
 }
 //_signalList = tempList;

 _signalList = SignalArray(tempList);
 _lastIdx = _signalList.numberOfSignals();
 //log.debug("TempList copied, size = {}", tempList.numberOfSignals());
 //_signalList.sort(new NameSorter());
 qSort(_signalList.begin(), _signalList.end(), NameSorter::compare);
 //log.debug("makeList exit: _signalList size {} items.", _signalList.numberOfSignals());

}

/*static*/ /*private*/ void SignalTableModel::addToList(QList<SignalRow*> tempList, SignalRow* sr)
{
 // not in list, for the sort, insert at correct position
 bool add = true;
 for (int j = 0; j < tempList.size(); j++)
 {
  if (sr->getSignal()->getDisplayName().compare(tempList.at(j)->getSignal()->getDisplayName()) < 0)
  {
   tempList.insert(j, sr);
   add = false;
   break;
  }
 }
 if (add)
 {
  tempList.append(sr);
 }
}

/*private*/ QString SignalTableModel::checkSignalRow(SignalRow* sr)
{
 Portal* portal = sr->getPortal();
 OBlock* fromBlock = sr->getFromBlock();
 OBlock* toBlock = sr->getToBlock();
 QString msg = NULL;
 if (portal != NULL)
 {
  if (toBlock == NULL && sr->getFromBlock() == NULL)
  {
   msg = tr("Portal \"%1\" has blocks \"%2\" and \"%3\".\n Which is the Approach block and which is the Protected block?").arg(
      portal->getName()).arg(
      portal->getFromBlock()->getDisplayName()).arg(
      portal->getToBlock()->getDisplayName());
   return msg;
  }
  OBlock* pToBlk = portal->getToBlock();
  OBlock* pFromBlk = portal->getFromBlock();
  if (pToBlk==(toBlock))
  {
   if (fromBlock == NULL)
   {
    sr->setFromBlock(pFromBlk);
    /*    			} else if (!fromBlock==(pFromBlk)) {
 msg = tr("PortalBlockConflict", portal->getName(),
 fromBlock->getDisplayName());    */
   }
  } else if (pFromBlk==(toBlock))
  {
   if (fromBlock == NULL) {
    sr->setFromBlock(pToBlk);
    /*    			} else if (!toBlock==(pToBlk)) {
 msg = tr("PortalBlockConflict", portal->getName(),
 toBlock->getDisplayName()); */
   }
  } else if (pToBlk==(fromBlock))
  {
   if (toBlock == NULL) {
    sr->setToBlock(pFromBlk);
   }
  } else if (pFromBlk==(fromBlock))
  {
   if (toBlock == NULL)
   {
    sr->setToBlock(pToBlk);
   }
  }
  else
  {
   msg = tr("Portal \"%1\" does not connect to block \"%2\".").arg( portal->getName()).arg(
      (toBlock != NULL ? toBlock->getDisplayName() : "(NULL to-block reference)"));
  }
 }
 else if (fromBlock != NULL && toBlock != NULL)
 {
  Portal* p = getPortalwithBlocks(fromBlock, toBlock);
  if (p == NULL)
  {
   msg = tr("There is no Portal between blocks \"%1\" and \"%2\".").arg( fromBlock->getDisplayName()).arg( toBlock->getDisplayName());
  }
  else
  {
   sr->setPortal(p);
  }
 }
 if (msg == NULL && fromBlock != NULL && fromBlock==(toBlock))
 {
  msg = tr("Portal cannot have block \"%1\"\non both sides. (i.e. portal goes nowhere.)").arg( fromBlock->getDisplayName());
 }
 return msg;
}

/*private*/ Portal* SignalTableModel::getPortalwithBlocks(OBlock* fromBlock, OBlock* toBlock)
{
 QStringList sysNames = _portalMgr->getSystemNameArray();
 for (int i = 0; i < sysNames.length(); i++) {
  Portal* portal = (Portal*)_portalMgr->getBySystemName(sysNames[i]);
  if ((portal->getFromBlock()==(fromBlock) || portal->getToBlock()==(fromBlock))
      && (portal->getFromBlock()==(toBlock) || portal->getToBlock()==(toBlock))) {
   return portal;
  }
 }
 return NULL;
}

/*private*/ QString SignalTableModel::checkDuplicateSignal(NamedBean* signal)
{
 if (signal == NULL) {
 return NULL;
 }
 for (int i = 0; i < _signalList.size(); i++)
 {
  SignalRow* srow = _signalList.at(i);
  if (signal==(srow->getSignal()))
  {
   return tr("Signal \"%1\" is already in use protecting block \"%2\"\nthrough portal \"%3\" from block \"%4\".").arg(
           signal->getDisplayName()).arg( srow->getToBlock()->getDisplayName()).arg(
           srow->getPortal()->getName()).arg( srow->getFromBlock()->getDisplayName());
  }
 }
 return NULL;
}

/*private*/ QString SignalTableModel::checkDuplicateSignal(SignalRow* row)
{
 NamedBean* signal = row->getSignal();
 if (signal == NULL)
 {
  return NULL;
 }
 for (int i = 0; i < _signalList.size(); i++)
 {
  SignalRow* srow = _signalList.at(i);
  if (srow==(row))
  {
   continue;
  }
  if (signal==(srow->getSignal()))
  {
   return tr("Signal \"%1\" is already in use protecting block \"%2\"\nthrough portal \"%3\" from block \"%4\".").arg(
         signal->getDisplayName()).arg( srow->getToBlock()->getDisplayName()).arg(
         srow->getPortal()->getName(), srow->getFromBlock()->getDisplayName());
  }
 }
 return NULL;
}

/*private*/ QString SignalTableModel::checkDuplicateProtection(SignalRow* row)
{
 Portal* portal = row->getPortal();
 OBlock* block = row->getToBlock();
 if (block == NULL || portal == NULL)
 {
  return NULL;
 }
 for (int i = 0; i < _signalList.size(); i++)
 {
  SignalRow* srow = _signalList.at(i);
  if (srow==(row))
  {
   continue;
  }
  if (block==(srow->getToBlock()) && portal==(srow->getPortal()))
  {
   return tr("Block \"%1\" through portal \"%2\" from\nblock \"%3\" is already protected by signal \"%4\".").arg(block->getDisplayName()).arg(portal->getName()).arg(srow->getFromBlock()->getDisplayName()).arg( srow->getSignal()->getDisplayName());
  }
 }
 return NULL;
}

/*public*/ int SignalTableModel::columnCount(const QModelIndex &parent) const
{
return NUMCOLS;
}

/*public*/ int SignalTableModel::rowCount(const QModelIndex &parent) const
{
return _signalList.size() + 1;
}

//@Override
/*public*/ QVariant SignalTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
  case NAME_COLUMN:
   return tr("Signal Name");
  case FROM_BLOCK_COLUMN:
   return tr("From (Approach) Block");
  case PORTAL_COLUMN:
  return tr("(Through) Portal");
  case TO_BLOCK_COLUMN:
   return tr("To (Protected) Block");
  case LENGTHCOL:
   return tr("Offset");
  case UNITSCOL:
   return "  ";
  case EDIT_COL:
   return "  ";
  }
  return "";
 }
 return QVariant();
}

/*public*/ QVariant  SignalTableModel::data(const QModelIndex &index, int role) const
{
 int rowIndex = index.row();
 int columnIndex = index.column();
 if (_signalList.size() == rowIndex)
 {
  if (columnIndex==LENGTHCOL)
  {
   if (tempRow[UNITSCOL]==(tr("cm")))
   {
    return (twoDigit->format(_tempLen/10));
   }
   return (twoDigit->format(_tempLen/25.4f));
  }
  if (columnIndex==UNITSCOL)
  {
   return (tempRow[UNITSCOL]==(tr("cm")));
  }
  return tempRow[columnIndex];
 }
 SignalRow* signalRow = _signalList.at(rowIndex);

 if(role == Qt::DisplayRole)
 {
  //if (log.isDebugEnabled()) log.debug("getValueAt rowIndex= "+rowIndex+" _lastIdx= "+_lastIdx);
  switch (columnIndex)
  {
  case NAME_COLUMN:
   if (signalRow->getSignal() != NULL) {
    return signalRow->getSignal()->getDisplayName();
   }
   break;
  case FROM_BLOCK_COLUMN:
   if (signalRow->getFromBlock() != NULL) {
    return signalRow->getFromBlock()->getDisplayName();
   }
   break;
  case PORTAL_COLUMN:
   if (signalRow->getPortal() != NULL) {
    return signalRow->getPortal()->getName();
   }
   break;
  case TO_BLOCK_COLUMN:
   if (signalRow->getToBlock() != NULL) {
    return signalRow->getToBlock()->getDisplayName();
   }
   break;
  case LENGTHCOL:
   if (signalRow->isMetric()) {
    return (twoDigit->format(signalRow->getLength()/10));
   }
   return (twoDigit->format(signalRow->getLength()/25.4f));
  case UNITSCOL:
   return signalRow->isMetric()?"cm":"in";
  case DELETE_COL:
   return tr("Delete");
  case EDIT_COL:
   return tr("Edit");}
  return "";
 }
 return QVariant();
}

//@Override
/*public*/ bool SignalTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();

  QString msg = NULL;
  if (_signalList.size() == row)
  {
   if (col == DELETE_COL)
   {
    initTempRow();
    fireTableRowsUpdated(row, row);
    return true;
   }
   else if (col == UNITSCOL)
   {
    if (value.toBool())
    {
     tempRow[UNITSCOL] = tr("cm");
    }
    else
    {
     tempRow[UNITSCOL] = tr("in");
    }
    fireTableRowsUpdated(row, row);
    return true;
   }
   else if (col == LENGTHCOL)
   {
    bool bok;
    _tempLen = value.toFloat(&bok);
    if (tempRow[UNITSCOL]==(tr("cm")))
    {
     _tempLen *= 10.0;
    }
    else
    {
     _tempLen *= 25.4;
    }
    if(!bok)
    {
     //            JOptionPane.showMessageDialog(NULL, tr("BadNumber", tempRow[LENGTHCOL]),
     //                    tr("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::critical(NULL, tr("Error"), tr("%1 is not a number.").arg(tempRow[LENGTHCOL]));
    }
    return true;
   }
   QString str =  value.toString();
   if (str == NULL || str.trimmed().length() == 0)
   {
    tempRow.replace(col, NULL);
    return true;
   }
   tempRow.replace(col, str.trimmed());
   OBlock* fromBlock = NULL;
   OBlock* toBlock = NULL;
   Portal* portal = NULL;
   NamedBean* signal = NULL;
   OBlockManager* OBlockMgr = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
   if (tempRow[FROM_BLOCK_COLUMN] != NULL)
   {
    fromBlock = OBlockMgr->getOBlock(tempRow[FROM_BLOCK_COLUMN]);
    if (fromBlock == NULL)
    {
     msg = tr("There is no Block named \"%1\".").arg(tempRow[FROM_BLOCK_COLUMN]);
    }
   }
   if (msg == NULL && tempRow[TO_BLOCK_COLUMN] != NULL)
   {
    toBlock = OBlockMgr->getOBlock(tempRow[TO_BLOCK_COLUMN]);
    if (toBlock == NULL)
    {
     msg = tr("There is no Block named \"%1\".").arg(tempRow[TO_BLOCK_COLUMN]);
    }
   }
   if (msg == NULL)
   {
    if (tempRow[PORTAL_COLUMN] != NULL)
    {
     portal = _portalMgr->getPortal(tempRow[PORTAL_COLUMN]);
     if (portal == NULL) {
      msg = tr("There is no Portal named \"%1\".").arg(tempRow[PORTAL_COLUMN]);
     }
    }
    else
    {
     if (fromBlock != NULL && toBlock != NULL)
     {
      portal = getPortalwithBlocks(fromBlock, toBlock);
      if (portal == NULL)
      {
       msg = tr("There is no Portal between blocks \%1\" and \"%2\".").arg( tempRow[FROM_BLOCK_COLUMN]).arg( tempRow[TO_BLOCK_COLUMN]);
      }
      else
      {
       tempRow[PORTAL_COLUMN] = portal->getName();
      }
     }
    }
   }
   if (msg == NULL && tempRow[NAME_COLUMN] != NULL)
   {
    signal = Portal::getSignal(tempRow[NAME_COLUMN]);
    if (signal == NULL)
    {
     msg = tr("There is no Signal Head or Signal Mast named \"%1\".").arg( tempRow[NAME_COLUMN]);
    }
    else
    {
     msg = checkDuplicateSignal(signal);
    }
    if (msg==NULL) {
     if (fromBlock != NULL && toBlock != NULL)
     {
      portal = getPortalwithBlocks(fromBlock, toBlock);
      if (portal == NULL) {
       msg = tr("There is no Portal between blocks \"%1\" and \"%2\".").arg( tempRow[FROM_BLOCK_COLUMN]).arg( tempRow[TO_BLOCK_COLUMN]);
      }
      else
      {
       tempRow[PORTAL_COLUMN] = portal->getName();
      }
     }
     else
     {
      return true;
     }
    }
    if (msg == NULL)
    {
     float length = 0.0;
     bool isMetric = tempRow[UNITSCOL]==(tr("cm"));
     bool bok;
     length = tempRow[LENGTHCOL].toFloat(&bok);
     if (isMetric)
     {
      length *= 10.0;
     } else {
      length *= 25.4;
     }
     if(!bok)
     {
      msg = tr("%1 is not a number.").arg( tempRow[LENGTHCOL]);
     }
     if (isMetric)
     {
      tempRow[UNITSCOL] = tr("cm");
     }
     else
     {
      tempRow[UNITSCOL] = tr("in");
     }
     if (msg == NULL)
     {
      SignalRow* signalRow = new SignalRow(signal, fromBlock, portal, toBlock, length, isMetric);
      msg = setSignal(signalRow, false);
      if (msg==NULL)
      {
       _signalList.append(signalRow);
      }
      initTempRow();
      fireTableDataChanged();
     }
    }
   }
  }
  else
  {	// Editing existing signal configurations
   SignalRow* signalRow = _signalList.at(row);
   Portal* portal;
   OBlock* block;
   OBlockManager* OBlockMgr = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
   switch (col)
   {
    case NAME_COLUMN:
    {
     NamedBean* signal = Portal::getSignal( value.toString());
     if (signal == NULL)
     {
      msg = tr("There is no Signal Head or Signal Mast named \"%1\".").arg( value.toString());
      //                        signalRow->setSignal(NULL);
      break;
     }
     portal = signalRow->getPortal();
     if (portal != NULL && signalRow->getToBlock() != NULL)
     {
      NamedBean* oldSignal = signalRow->getSignal();
      signalRow->setSignal(signal);
      msg = checkDuplicateSignal(signalRow);
      if (msg == NULL)
      {
       deleteSignal(signalRow);    // delete old
       msg = setSignal(signalRow, false);
       fireTableRowsUpdated(row, row);
      }
      else
      {
       signalRow->setSignal(oldSignal);
      }
     }
     break;
    }
    case FROM_BLOCK_COLUMN:
    {
     block = OBlockMgr->getOBlock( value.toString());
     if (block == NULL) {
      msg = tr("There is no Block named \"%1\".").arg( value.toString());
      break;
     }
     if (block==(signalRow->getFromBlock())) {
      break;      // no change
     }
     deleteSignal(signalRow);    // delete old
     signalRow->setFromBlock(block);
     portal = signalRow->getPortal();
     if (checkPortalBlock(portal, block)) {
      signalRow->setToBlock(NULL);
     } else {
      // get new portal
      portal = getPortalwithBlocks(block, signalRow->getToBlock());
      signalRow->setPortal(portal);
     }
     msg = checkSignalRow(signalRow);
     if (msg == NULL) {
      msg = checkDuplicateProtection(signalRow);
     } else {
      signalRow->setPortal(NULL);
      break;
     }
     if (msg == NULL && signalRow->getPortal() != NULL) {
      msg = setSignal(signalRow, true);
     } else {
      signalRow->setPortal(NULL);
     }
     fireTableRowsUpdated(row, row);
     break;
    }
    case PORTAL_COLUMN:
    {
     portal = _portalMgr->getPortal( value.toString());
     if (portal == NULL) {
      msg = tr("There is no Portal named \"%1\".").arg(value.toString());
      break;
     }
     deleteSignal(signalRow);    // delete old
     signalRow->setPortal(portal);
     block = signalRow->getToBlock();
     if (checkPortalBlock(portal, block)) {
      signalRow->setFromBlock(NULL);
     } else {
      block = signalRow->getFromBlock();
      if (checkPortalBlock(portal, block)) {
       signalRow->setToBlock(NULL);
      }
     }
     msg = checkSignalRow(signalRow);
     if (msg == NULL) {
      msg = checkDuplicateProtection(signalRow);
     } else {
      signalRow->setToBlock(NULL);
      break;
     }
     if (msg == NULL) {
      signalRow->setPortal(portal);
      msg = setSignal(signalRow, false);
      fireTableRowsUpdated(row, row);
     }
     break;
    }
    case TO_BLOCK_COLUMN:
    {
     block = OBlockMgr->getOBlock( value.toString());
     if (block == NULL) {
      msg = tr("There is no Block named \"%1\".").arg( value.toString());
      break;
     }
     if (block==(signalRow->getToBlock())) {
      break;      // no change
     }
     deleteSignal(signalRow);    // delete old
     signalRow->setToBlock(block);
     portal = signalRow->getPortal();
     if (checkPortalBlock(portal, block)) {
      signalRow->setFromBlock(NULL);
     } else {
      // get new portal
      portal = getPortalwithBlocks(signalRow->getFromBlock(), block);
      signalRow->setPortal(portal);
     }
     msg = checkSignalRow(signalRow);
     if (msg == NULL) {
      msg = checkDuplicateProtection(signalRow);
     } else {
      signalRow->setPortal(NULL);
      break;
     }
     if (msg == NULL && signalRow->getPortal() != NULL) {
      msg = setSignal(signalRow, true);
     } else {
      signalRow->setPortal(NULL);
     }
     fireTableRowsUpdated(row, row);
     break;
    }
    case LENGTHCOL:
    {
     bool bok;
     float len = value.toFloat(&bok);
     if (signalRow->isMetric()) {
      signalRow->setLength(len * 10.0f);
     } else {
      signalRow->setLength(len * 25.4f);
     }
     fireTableRowsUpdated(row, row);
     if(!bok) {
      msg = tr("%1 is not a number.").arg(value.toString());
     }
     if (msg == NULL && signalRow->getPortal() != NULL) {
      msg = setSignal(signalRow, false);
     } else {
      signalRow->setPortal(NULL);
     }
     fireTableRowsUpdated(row, row);
     break;
    }
    case UNITSCOL:
    {
     signalRow->setMetric(value.toBool());
     fireTableRowsUpdated(row, row);
     break;
    }
    case DELETE_COL:
    {
     deleteSignal(signalRow);
     _signalList.removeOne(signalRow);
     fireTableDataChanged();
    }
    case EDIT_COL:
    {
     editSignal(Portal::getSignal(signalRow->getSignal()->getDisplayName()), signalRow);
     break;
    }
   }
  }

  if (msg != "")
  {
   //    JOptionPane.showMessageDialog(NULL, msg,
   //            tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(NULL, tr("Warning"), msg);
  }
 }
 return false;
}

/*private*/ void SignalTableModel::deleteSignal(SignalRow* signalRow)
{
 Portal* portal = signalRow->getPortal();
 if (portal == NULL)
 {
  portal = getPortalwithBlocks(signalRow->getFromBlock(), signalRow->getToBlock());
 }
 if (portal != NULL) {
  // remove signal from previous portal
  portal->deleteSignal(signalRow->getSignal());
 }
}

/*private*/ void SignalTableModel::editSignal(NamedBean* signal, SignalRow* sr) {
    if (_tabbed && signal != nullptr && !inEditMode) {
        inEditMode = true;
        // open SignalEditFrame
        SignalEditFrame* sef = new SignalEditFrame(tr("Edit Signal \"%1\"").arg(sr->getSignal()->getDisplayName()),
                signal, sr, this);
        // TODO run on separate thread?
        sef->setVisible(true);
    }
}

/*static*/ /*private*/ QString SignalTableModel::setSignal(SignalRow* signalRow, bool deletePortal)
{
 Portal* portal = signalRow->getPortal();
 float length = signalRow->getLength();
 if (portal->setProtectSignal(signalRow->getSignal(), length, signalRow->getToBlock())) {
  if (signalRow->getFromBlock() == NULL) {
   signalRow->setFromBlock(portal->getOpposingBlock(signalRow->getToBlock()));
  }
 }
 else
 {
  if (deletePortal) {
   signalRow->setPortal(NULL);
  } else {
   signalRow->setToBlock(NULL);
  }
  return tr("Portal \"%1\" does not connect to block \"%2\".").arg(portal->getName()).arg(
     signalRow->getToBlock()->getDisplayName());
 }
 return NULL;
}

/*static*/ /*private*/ bool SignalTableModel::checkPortalBlock(Portal* portal, OBlock* block)
{
 if (block==NULL) {
  return false;
 }
 return (block==(portal->getToBlock()) || block==(portal->getFromBlock()));
}

//@Override
/*public*/ Qt::ItemFlags SignalTableModel::flags(const QModelIndex &index) const
{
 if(index.column() == UNITSCOL)
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/*static*/ /*public*/ int SignalTableModel::getPreferredWidth(int col) {
 switch (col) {
 case NAME_COLUMN:
  return  JTextField(18).sizeHint().width();
 case FROM_BLOCK_COLUMN:
  return  JTextField(18).sizeHint().width();
 case PORTAL_COLUMN:
  return  JTextField(18).sizeHint().width();
 case TO_BLOCK_COLUMN:
  return  JTextField(18).sizeHint().width();
 case LENGTHCOL:
  return  JTextField(5).sizeHint().width();
 case UNITSCOL:
  return  JTextField(2).sizeHint().width();
 case DELETE_COL:
  return  QPushButton("DELETE").sizeHint().width();
 }
 return 5;
}
#endif
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString SignalTableModel::getColumnClass(int col) {
    switch (col) {
    case DELETE_COL:
    case EDIT_COL:
        return "JButton";
    case UNITSCOL:
        return "JToggleButton";
    case NAME_COLUMN:
    default:
        return "String";
    }
}

/*public*/ bool SignalTableModel::editMode() {
    return inEditMode;
}

/*public*/ void SignalTableModel::setEditMode(bool editing) {
    inEditMode = editing;
}

/*public*/ void SignalTableModel::propertyChange(PropertyChangeEvent* e)
{
 QString property = e->getPropertyName();
 if (property==("length") || property==("portalCount")
     || property==("UserName"))
 {
#if 0 // TODO:
  makeList();
#endif
  fireTableDataChanged();
 }
}

/*protected*/ void SignalTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
{ // TODO:
 // install a button renderer & editor
 //    ButtonRenderer buttonRenderer = new ButtonRenderer();
 //    table.setDefaultRenderer(JButton.class,buttonRenderer);
 //    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
 //    table.setDefaultEditor(JButton.class,buttonEditor);
 //    // ensure the table rows, columns have enough room for buttons
 //    table.setRowHeight(sample.getPreferredSize().height);
 //    table.getColumnModel().getColumn(column)
 //        .setPreferredWidth((sample.getPreferredSize().width)+4);
 this->table = table;
 buttonMap.append(column);
 // table->setItemDelegateForColumn(column, new PBDelegate(buttonMap->value(column)));
 table->setItemDelegateForColumn(column, new PushButtonDelegate());
 for(int i = 0; i < rowCount(QModelIndex()); i ++)
  table->openPersistentEditor(index(i, column, QModelIndex()) );
}

void SignalTableModel::setPersistentButtons()
{
 for(int row = 0; row < rowCount(QModelIndex()); row ++)
 {
  foreach (int col, buttonMap)
  {
   table->openPersistentEditor(index(row, col, QModelIndex()) );
  }
 }
}

void SignalTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}

void SignalTableModel::fireTableRowsUpdated(int, int)
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}
