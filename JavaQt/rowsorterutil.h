#ifndef ROWSORTERUTIL_H
#define ROWSORTERUTIL_H
#include <QObject>
#include "sortorder.h"

class RowSorter;
class RowSorterUtil : public QObject
{
 Q_OBJECT
public:
 explicit RowSorterUtil(QObject *parent = 0);
 /*public*/ static SortOrder getSortOrder(/*@Nonnull*/ RowSorter */*<? extends TableModel>*/ rowSorter, int column);
 /*public*/ static void setSortOrder(/*@Nonnull*/ RowSorter/*<? extends TableModel>*/* rowSorter, int column, /*@Nonnull*/ SortOrder sortOrder);

signals:

public slots:
};

#endif // ROWSORTERUTIL_H
