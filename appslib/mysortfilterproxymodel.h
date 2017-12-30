#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H
#include "rowsorter.h"
#include "abstracttablemodel.h"
class MySortFilterProxyModel : public RowSorter
{
public:
 MySortFilterProxyModel(AbstractTableModel* =0);
 bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
 QList</*? extends*/ SortKey*>* getSortKeys();
 void setSortKeys(QList<SortKey*>* keys);
};

#endif // MYSORTFILTERPROXYMODEL_H
