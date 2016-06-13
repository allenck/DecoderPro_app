#include "ovtablemodel.h"
#include "namedbean.h"

OVTableModel::OVTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
 list = new QList<ItemData>();
 list->clear();
}
void OVTableModel::setData(QList<ItemData>* mapData)
{
 beginResetModel();
 list->clear();
 foreach (ItemData itemData, *mapData)
 {
  list->append(itemData);
 }
 endResetModel();
}

int OVTableModel::rowCount(const QModelIndex &parent) const
{
 Q_UNUSED(parent)
 return list->size();
}

int OVTableModel::columnCount(const QModelIndex &parent) const
{
 Q_UNUSED(parent)
 return 4;
}
QVariant OVTableModel::data(const QModelIndex &index, int role) const
{
 if (!index.isValid())
  return QVariant();

 if (index.row() >= list->size() || index.row() < 0)
  return QVariant();

 if(role == Qt::DisplayRole || role == Qt::EditRole)
 {
   ItemData data = list->at(index.row());
   switch(index.column())
   {
   case 0:
    return data.systemName;
   case 1:
    return data.type;
   case 2:
    return data.userName;
   case 3:
    return data.comment;
   }
 }
 return QVariant();
}
QVariant OVTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if (role != Qt::DisplayRole)
   return QVariant();
 if (orientation == Qt::Horizontal)
 {
  switch (section)
  {
  case 0:
   return "SysName";
  case 1:
   return "Type";
  case 2:
   return "UserName";
  case 3:
   return "Comment";
  }
 }
 return QVariant();
}
