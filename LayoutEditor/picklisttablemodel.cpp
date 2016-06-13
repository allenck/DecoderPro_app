#include "picklisttablemodel.h"

PickListTableModel::PickListTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

void PickListTableModel::fireTableDataChanged()
{
    beginResetModel();
    endResetModel();
}
int PickListTableModel::rowCount(const QModelIndex &parent) const
{
  return 0;
}
int PickListTableModel::columnCount(const QModelIndex &parent) const
{
  return 0;
}
QVariant PickListTableModel::data(const QModelIndex &index, int role) const
{
 return QVariant();
}
void PickListTableModel::fireTableRowsUpdated(int r1, int r2)
{
 beginResetModel();
 endResetModel();
}
