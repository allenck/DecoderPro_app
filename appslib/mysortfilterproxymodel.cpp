#include "mysortfilterproxymodel.h"
#include "systemnamecomparator.h"
#include "sortorder.h"
#include "jtable.h"

MySortFilterProxyModel::MySortFilterProxyModel(AbstractTableModel * m )
    : RowSorter()
{
 setObjectName("MySortFilterProxyModel");
 setSourceModel(m);
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    if(left.column() == 0)
    {
     return SystemNameComparator::compare(leftData.toString(), rightData.toString());
    }
     return QSortFilterProxyModel::lessThan(left, right);
}

QList</*? extends*/ SortKey*>* MySortFilterProxyModel::getSortKeys()
{
 int sortCol = sortColumn();
 int order = sortOrder();

 QList<SortKey*>* keys = new QList<SortKey*>();
 for(int i = 0; i < rowCount(); i++)
 {
  SortKey* key = new SortKey(i, i==sortCol?(SortOrder)order:UNSORTED);
  keys->append(key);
 }
 return keys;
}

void MySortFilterProxyModel::setSortKeys(QList<SortKey*>* keys)
{
 if(keys == NULL)
 {
  QAbstractItemModel* model = sourceModel();
  JTable* _table = NULL;

  if(qobject_cast<AbstractTableModel*>(model) != NULL)
  {
   _table = ((AbstractTableModel*)model)->table();
   if(_table != NULL)
    _table->setSortingEnabled(false);

   foreach (SortKey* key, *keys)
   {
    if(key->getSortOrder() != UNSORTED)
    {
     _table->setSortingEnabled(true);
     sort(key->getColumn(), (Qt::SortOrder)key->getSortOrder());
     break;
    }
   }
  }
 }
}
