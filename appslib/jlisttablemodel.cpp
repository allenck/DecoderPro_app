#include "jlisttablemodel.h"

JListTableModel::JListTableModel(QStringList list, QObject* parent) :AbstractListModel(parent)
{
 this->list = list;
}

int JListTableModel::rowCount(const QModelIndex &parent) const
{
 return list.count();
}

QVariant JListTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
  return list.at(index.row());
 return QVariant();
}
