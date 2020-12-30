#include "blockpathtablemodel.h"
#include "tableframes.h"
#include "oblock.h"
#include "decimalformat.h"
#include "opath.h"
#include "portal.h"
#include <QMessageBox>
#include <QSignalMapper>
#include "jtable.h"
#include <QPushButton>
#include "instancemanager.h"
#include "portalmanager.h"
#include "portaltablemodel.h"
#include "jtextfield.h"
#include "pushbuttondelegate.h"

//BlockPathTableModel::BlockPathTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}

///*public*/ class BlockPathTableModel extends AbstractTableModel implements PropertyChangeListener {

//    /*private*/ static final long serialVersionUID = -2472819814795605641L;


/*public*/ BlockPathTableModel::BlockPathTableModel(QObject *parent) :
AbstractTableModel(parent)
{
    //super();
common();
}

/*public*/ BlockPathTableModel::BlockPathTableModel(OBlock* block, TableFrames* _parent, QObject *parent) :
AbstractTableModel(parent)
{
 //super();
 common();
 _block = block;
 this->_parent = _parent;
}

void BlockPathTableModel::common()
{
 tempRow = QStringList();
 for(int i = 0; i < NUMCOLS; i++)
  tempRow.append("");
 twoDigit = new DecimalFormat("0.00");
 log = new Logger("BlockPathTableModel");
 buttonMap = QList<int>();
 _tempLen = 0.0;
}

/*public*/ void BlockPathTableModel::init()
{
 initTempRow();
 //_block->addPropertyChangeListener(this);
 connect(_block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void BlockPathTableModel::removeListener()
{
 if (_block == NULL) {
     return;
 }
//    try {
//        _block->removePropertyChangeListener(this);
//    } catch (NullPointerException npe) { // OK when block is removed
//    }
 disconnect(_block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ OBlock* BlockPathTableModel::getBlock()
{
 return _block;
}

void BlockPathTableModel::initTempRow()
{
 for (int i = 0; i < NUMCOLS; i++)
 {
  tempRow.replace(i, NULL);
 }
 tempRow[LENGTHCOL] = twoDigit->format(0.0);
 if (_block->isMetric())
 {
  tempRow.replace(UNITSCOL, tr("cm"));
 }
 else
 {
  tempRow.replace(UNITSCOL,  tr("in"));
 }
 tempRow.replace(DELETE_COL, tr("Clear"));

 _units = QList<bool>();
 for(int i=0; i<=_block->getPaths()->size(); i++)
 {
  _units.append((_block->isMetric()));
 }
}

/*public*/ int BlockPathTableModel::columnCount(const QModelIndex &parent) const{
    return NUMCOLS;
}

/*public*/ int BlockPathTableModel::rowCount(const QModelIndex &parent) const
{
    return _block->getPaths()->size() + 1;
}

//@Override
/*public*/ QVariant BlockPathTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
   case FROM_PORTAL_COLUMN:
       return tr("From Portal");
   case NAME_COLUMN:
       return tr("Path Name");
   case TO_PORTAL_COLUMN:
       return tr("To Portal");
   case LENGTHCOL:
       return tr("Length");
   case UNITSCOL:
       return "  ";
  }
  return "";
 }
 return QVariant();
}

/*public*/ QVariant BlockPathTableModel::data(const QModelIndex &index, int role) const
{
 int rowIndex = index.row();
 int columnIndex = index.column();
 OPath* path = NULL;
 if (rowIndex < _block->getPaths()->size()) {
     path = (OPath*) _block->getPaths()->at(rowIndex);
 }
 if(role == Qt::DisplayRole)
 {
 switch (columnIndex)
 {
  case FROM_PORTAL_COLUMN:
   if (path !=NULL)
   {
    Portal* portal = path->getFromPortal();
    if (portal == NULL) {
        return "";
    }
    return portal->getName();
   }
   else
   {
    return tempRow[columnIndex];
   }
  case NAME_COLUMN:
   if (path !=NULL) {
       return path->getName();
   } else {
       return tempRow[columnIndex];
   }
  case TO_PORTAL_COLUMN:
   if (path !=NULL)
   {
    Portal* portal = path->getToPortal();
    if (portal == NULL) {
        return "";
    }
    return portal->getName();
   } else {
       return tempRow[columnIndex];
   }
  case LENGTHCOL:
   if (path !=NULL)
   {
    if (_units.at(rowIndex))
    {
     return (twoDigit->format(path->getLengthCm()));
    }
    else
    {
     return (twoDigit->format(path->getLengthIn()));
    }
   }
   else
   {
    if (_units.at(rowIndex)) {
        return (twoDigit->format(_tempLen/10));
    } else {
        return (twoDigit->format(_tempLen/25.4f));
    }
   }
  case UNITSCOL:
   return _units.at(rowIndex)?"cm":"in";
  case EDIT_COL:
   if (path != NULL)
   {
    return tr("Turnouts");
   }
   else
   {
    return "";
   }
  case DELETE_COL:
   if (path != NULL)
   {
    return tr("Delete");
   }
   else
   {
    return tr("Clear");
   }
  }
  return "";
 }
 return QVariant();
}

//@Override
/*public*/ bool BlockPathTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int col = index.column();
 int row = index.row();
 if(role == Qt::EditRole)
 {
  QString msg = NULL;
  if (_block->getPaths()->size() == row)
  {
   switch (col)
   {
    case NAME_COLUMN:
    {
     QString strValue = value.toString();
     if (_block->getPathByName(strValue) != NULL)
     {
      msg = tr("Duplicate name, Path \"%1\" has been defined.").arg(strValue);
      tempRow.replace(col, strValue);
     }
     else
     {
      Portal* fromPortal = _block->getPortalByName(tempRow[FROM_PORTAL_COLUMN]);
      Portal* toPortal = _block->getPortalByName(tempRow[TO_PORTAL_COLUMN]);
      if (fromPortal !=NULL || toPortal!= NULL)
      {
       OPath* path = new OPath(strValue, _block, fromPortal, toPortal, QList<BeanSetting*>());
       float len = 0.0f;
       bool bok;
       len = tempRow[LENGTHCOL].toFloat(&bok);
       if(!bok)
       {
//                 JOptionPane.showMessageDialog(NULL, tr("BadNumber", tempRow[LENGTHCOL]),
//                         tr("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(NULL, tr("Warning"), tr("%1 is not a number.").arg(tempRow[LENGTHCOL]));
       }
       if (tempRow[UNITSCOL]==((tr("cm"))))
       {
           path->setLength(len * 10.0f);
       } else {
           path->setLength(len * 25.4f);
       }

       if (!_block->addPath(path))
       {
           msg = tr("Failed to add Path %1").arg(strValue);
           tempRow[NAME_COLUMN] = strValue;
       } else
       {
        initTempRow();
        _parent->updateOBlockTablesMenu();
        fireTableDataChanged();
       }
      }
      else
      {
          tempRow[NAME_COLUMN] = strValue;
      }
     }
     break;
    }
    case LENGTHCOL:
    {
     bool bok;
     _tempLen = value.toFloat(&bok);
     if (tempRow[UNITSCOL]==(tr("cm")))
     {
        _tempLen *= 10.;
     }
     else
     {
        _tempLen *= 25.4;
     }
     if(!bok)
     {
//            JOptionPane.showMessageDialog(NULL, tr("BadNumber", tempRow[LENGTHCOL]),
//                    tr("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
      QMessageBox::warning(NULL, tr("Warning"), tr("%1 is not a number.").arg(tempRow[LENGTHCOL]));
     }
     return true;
    }
    case UNITSCOL:
   {
    _units.replace(row, value.toBool());
        fireTableRowsUpdated(row, row);
        return true;
   }
    case DELETE_COL:
    {
     initTempRow();
     fireTableRowsUpdated(row, row);
     break;
    }
   }
   tempRow.replace(col, value.toString());
   if (msg != NULL)
   {
//       JOptionPane.showMessageDialog(NULL, msg,
//               tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(NULL, tr("Warning"), msg);
   }
   return true;
  }

  OPath* path = (OPath*) _block->getPaths()->at(row);
  QString strValue;
  switch (col)
  {
   case FROM_PORTAL_COLUMN:
   {
    strValue = value.toString();
    if (strValue != NULL)
    {
     Portal* portal = _block->getPortalByName(strValue);
     PortalManager* portalMgr = (PortalManager*) InstanceManager::getDefault("PortalManager");
     if (portal == NULL || portalMgr->getPortal(strValue) == NULL)
     {
 //               int response = JOptionPane.showConfirmDialog(NULL,
 //                       tr("BlockPortalConflict", value, _block->getDisplayName()),
 //                       tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
 //                       JOptionPane.WARNING_MESSAGE);
 //               if (response == JOptionPane.NO_OPTION)
      if(QMessageBox::warning(NULL, tr("Warning"), tr("No Portal named \"%1\" is found in Block \"%2\".  Do you want to\n create a new portal called \"%1\" for Block \"%2\"?").arg(value.toString()).arg(_block->getDisplayName())) ==QMessageBox::No)

      {
       break;
      }
      portal = portalMgr->providePortal(strValue);
      if (portal == NULL)
      {
       msg = tr("There is no Portal named \"%1\".").arg( strValue);
       break;
      }
      else
      {
       if (!portal->setFromBlock(_block, false))
       {
 //                response = JOptionPane.showConfirmDialog(NULL,
 //                        tr("BlockPathsConflict", value, portal.getFromBlockName()),
 //                        tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
 //                        JOptionPane.WARNING_MESSAGE);
 //                if (response == JOptionPane.NO_OPTION)
        if(QMessageBox::warning(NULL, tr("Warning"), tr("Paths using this Portal traverse to block \"%2\". If the Block is changed\nto \"%1\", the paths in Block \"%2\" using this portal will become spurs.\nIf you make this change, please verify path connections in blocks %1 and %2. ").arg(value.toString()).arg(portal->getFromBlockName()),QMessageBox::Yes | QMessageBox::No)== QMessageBox::No)
        {
         break;
        }
       }
       portal->setFromBlock(_block, true);
       _parent->getPortalTableModel()->fireTableDataChanged();
      }
     }
     path->setFromPortal(portal);
     if (!portal->addPath(path))
     {
      msg = tr("Failed to add Path %1").arg(strValue);
     }
    }
    else
    {
     path->setFromPortal(NULL);
    }
    fireTableRowsUpdated(row, row);
    break;
   }
   case NAME_COLUMN:
   {
    strValue = value.toString();
    if (strValue != NULL)
    {
     if (_block->getPathByName(strValue) != NULL)
     {
      msg = tr("Duplicate name, Path \"%1\" has been defined.").arg( strValue);
     }
     path->setName(strValue);
     fireTableRowsUpdated(row, row);
    }
    break;
   }
   case TO_PORTAL_COLUMN:
   {
    strValue = value.toString();
    if (strValue != NULL)
    {
     PortalManager* portalMgr =(PortalManager*) InstanceManager::getDefault("PortalManager");
     Portal* portal = _block->getPortalByName(strValue);
     if (portal == NULL || portalMgr->getPortal(strValue) == NULL)
     {
 //               int response = JOptionPane.showConfirmDialog(NULL,
 //                       tr("BlockPortalConflict", value, _block->getDisplayName()),
 //                       tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
 //                       JOptionPane.WARNING_MESSAGE);
 //               if (response == JOptionPane.NO_OPTION)
      if(QMessageBox::warning(NULL,tr("Warning"),tr("No Portal named \"%1\" is found in Block \"%2\".  Do you want to\ncreate a new portal called \"%1\" for Block \"%2\"?").arg(value.toString()).arg(_block->getDisplayName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
      {
       break;
      }
      portal = portalMgr->providePortal(strValue);
      if (portal == NULL)
      {
       msg = tr("There is no Portal named \"%1\".").arg(strValue);
       break;
      }
      else
      {
       if (!portal->setToBlock(_block, false))
       {
 //                       response = JOptionPane.showConfirmDialog(NULL,
 //                               tr("BlockPathsConflict", value, portal.getToBlockName()),
 //                               tr("WarningTitle"), JOptionPane.YES_NO_OPTION,
 //                               JOptionPane.WARNING_MESSAGE);
 //                       if (response == JOptionPane.NO_OPTION)
        if(QMessageBox::warning(NULL, tr("Warning"),tr("Paths using this Portal traverse to block \"%2\". If the Block is changed\nto \"%1\", the paths in Block \"%2\" using this portal will become spurs.\nIf you make this change, please verify path connections in blocks %1 and %2. ").arg(value.toString()).arg(portal->getToBlockName()),QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
        {
            break;
        }
       }
       portal->setToBlock(_block, true);
       _parent->getPortalTableModel()->fireTableDataChanged();
      }
     }
     path->setToPortal(portal);
     if (!portal->addPath(path))
     {
      msg = tr("Failed to add Path %1").arg(strValue);
     }
    }
    else
    {
     path->setToPortal(NULL);
    }
    fireTableRowsUpdated(row, row);
    break;
   }
   case LENGTHCOL:
   {
    bool bok;
    float len = value.toFloat(&bok);
    if (_units.at(row)) {
        path->setLength(len * 10.0f);
    } else {
        path->setLength(len * 25.4f);
    }
    fireTableRowsUpdated(row, row);
    if(!bok)
    {
     //              JOptionPane.showMessageDialog(NULL, tr("BadNumber", value),
     //                      tr("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(NULL, tr("Warning"), tr("%1 is not a number.").arg(value.toString()));
    }
    return true;
   }
   case UNITSCOL:
   {
    _units.replace(row, value.toBool());
    fireTableRowsUpdated(row, row);
    return true;
   }
   case EDIT_COL:
   {
    _parent->openPathTurnoutFrame(_parent->makePathTurnoutName(
                _block->getSystemName(), path->getName()));
    break;
   }
   case DELETE_COL:
   {
    if (deletePath(path))
    {
     _units.removeOne(row);
     fireTableDataChanged();
    }
   }
  }
  if (msg != "")
  {
//      JOptionPane.showMessageDialog(NULL, msg,
//              tr("WarningTitle"), JOptionPane.WARNING_MESSAGE);
   QMessageBox::warning(NULL, tr("Warning"), msg);
  }
 }
 return false;
}

bool BlockPathTableModel::deletePath(OPath* path)
{
//    if (JOptionPane.showConfirmDialog(NULL, tr("DeletePathConfirm",
//            path->getName()), tr("WarningTitle"),
//            JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE)
//            == JOptionPane.YES_OPTION)
 if(QMessageBox::warning(NULL, tr("Warning"), tr("Do you want to delete path \"%1\"?").arg(path->getName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
 {
  _block->removeOPath(path);
  return true;
 }
 return false;
}

//@Override
/*public*/ Qt::ItemFlags BlockPathTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt:: ItemIsEditable;
}

//@Override
//    /*public*/ Class<?> getColumnClass(int col) {
//        if (col == DELETE_COL || col == EDIT_COL) {
//            return JButton.class;
//        } else if (col == UNITSCOL) {
//            return Boolean.class;
//        }
//        return String.class;
//    }

/*public*/ int BlockPathTableModel::getPreferredWidth(int col) {
    switch (col) {
        case FROM_PORTAL_COLUMN:
        case NAME_COLUMN:
        case TO_PORTAL_COLUMN:
            return  JTextField(18).sizeHint().width();
        case LENGTHCOL:
            return  JTextField(5).sizeHint().width();
        case UNITSCOL:
            return  JTextField(2).sizeHint().width();
        case EDIT_COL:
            return  QPushButton("TURNOUT").sizeHint().width();
        case DELETE_COL:
            return  QPushButton("DELETE").sizeHint().width();
    }
    return 5;
}

/*public*/ void BlockPathTableModel::propertyChange(PropertyChangeEvent* e) {
    if (_block==(e->getSource())) {
        QString property = e->getPropertyName();
        if (log->isDebugEnabled()) {
            log->debug("propertyChange \"" + property + "\".  source= " + e->getSource()->metaObject()->className());
        }
        if (property==("portalCount") || property==("pathCount")) {
            fireTableDataChanged();
        }
    }
}
/*protected*/ void BlockPathTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
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
 table->setItemDelegateForColumn(column, new PushButtonDelegate());
 for(int i = 0; i < rowCount(QModelIndex()); i ++)
  table->openPersistentEditor(index(i, column, QModelIndex()) );
}

void BlockPathTableModel::setPersistentButtons()
{
 for(int row = 0; row < rowCount(QModelIndex()); row ++)
 {
  foreach (int col, buttonMap)
  {
   table->openPersistentEditor(index(row, col, QModelIndex()) );
  }
 }
}
void BlockPathTableModel::OnButtonClicked(QObject * obj)
{
 setData(*(QModelIndex*)obj, QVariant(), Qt::EditRole);
}

void BlockPathTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}

void BlockPathTableModel::fireTableRowsUpdated(int, int)
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}
