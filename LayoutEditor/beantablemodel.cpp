#include "beantablemodel.h"
#include "logger.h"
#include "manager.h"

BeanTableModel::BeanTableModel(QObject *parent) :
  AbstractTableModel(parent)
{
 log = new Logger("BeanTableModel");
}
/**
 * Abstract base for simple bean tables for insertion in other GUI elements
 *
 * @author Bob Jacobsen Copyright (C) 2007
 *
 * @version $Revision: 28746 $
 */
///*public*/ abstract class BeanTableModel extends AbstractTableModel {

/**
 *
 */
//private static final long serialVersionUID = 8121523528465367528L;

/*public*/ QString BeanTableModel::getColumnClass(int c) {
    if (c == INCLUDE_COLUMN) {
        return "Boolean";
    } else {
        return "String";
    }
}

/*public*/ /*abstract*/ Manager* BeanTableModel::getManager() const {}

/*public*/ int BeanTableModel::columnCount(const QModelIndex &parent) const
{
    return INCLUDE_COLUMN + 1;
}

/*public*/ int BeanTableModel::rowCount(const QModelIndex &parent) const
{
 return getManager()->getSystemNameList().size();
}

/*public*/ Qt::ItemFlags BeanTableModel::flags(const QModelIndex &index) const
{
    //return (c == INCLUDE_COLUMN);
 if(index.column() == INCLUDE_COLUMN)
  return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
 else
  return Qt::ItemIsSelectable | Qt::ItemIsEnabled;

}

/*public*/ QVariant  BeanTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {

    switch (section) {
        case SNAME_COLUMN:
            return "System Name";
        case UNAME_COLUMN:
            return "User Name";
        case INCLUDE_COLUMN:
            return "Included";
        default:
            return "";
    }
 }
 return QVariant();
}

/**
 * User name column must be handled by subclass
 */
/*public*/ QVariant BeanTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int c = index.column();
  int r = index.row();
  switch (c)
  {
   case SNAME_COLUMN:  // slot number
    return getManager()->getSystemNameList().at(r);
   default:
    log->warn("getValueAt should not have been asked about c=" + QString::number(c));
//            return ;
  }
 }
 return QVariant();
}
