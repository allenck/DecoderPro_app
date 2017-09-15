#include "jlist.h"

JList::JList(QWidget* parent) : QListView(parent)
{

}

JList::JList(QList<QString> list, QWidget *parent) : QListView(parent)
{
 setModel(new JListTableModel(list));
}

QModelIndexList JList::getSelectedValues()
{
 QModelIndexList list = QListView::selectedIndexes();
 return list;
}

JListTableModel::JListTableModel(QList<QString> list)
{
 this->list = list;

}

int JListTableModel::columnCount(const QModelIndex &parent) const
{
 return 1;
}

int JListTableModel::rowCount(const QModelIndex &parent) const
{
 return list.count();
}

QVariant JListTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 return QVariant();
}

Qt::ItemFlags JListTableModel::flags(const QModelIndex &index) const
{
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant JListTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
  return list.at(index.row());
 return QVariant();
}

QModelIndex JList::locationToIndex(QPoint p)
{
 return indexAt(p);
}

/*public*/ int JList::getSelectedIndex()
{
 QModelIndexList list = QListView::selectedIndexes();
 if(list.isEmpty()) return -1;
 return list.at(0).row();
}

/*private*/ void JList::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

}
