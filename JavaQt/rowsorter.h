#ifndef ROWSORTER_H
#define ROWSORTER_H

#include <QSortFilterProxyModel>
#include "sortorder.h"
#include "tablemodel.h"

class SortKey;
class RowSorterListener;
class QAbstractItemModel;
//template<class M>
class RowSorter : public QSortFilterProxyModel
{
 Q_OBJECT
public:

 explicit RowSorter(QObject *parent = 0);
 /*public*/ /*abstract*/  QAbstractItemModel* getModel();
 /*public*/ /*abstract*/ virtual void toggleSortOrder(int column);
 /*public*/ void addRowSorterListener(RowSorterListener* l);
 /*public*/ void removeRowSorterListener(RowSorterListener* l);
 /*public*/ /*abstract*/ virtual void setSortKeys(QList</*? extends*/ SortKey*>* keys);
 /*public*/ /*abstract*/ virtual QList</*? extends*/ SortKey*>* getSortKeys();
 /*public*/ /*abstract*/ virtual int convertRowIndexToModel(int index);
 /*public*/ /*abstract*/ virtual int convertRowIndexToView(int index);
 /*public*/ /*abstract*/ virtual int getViewRowCount();
 /*public*/ /*abstract*/ virtual int getModelRowCount();
 /*public*/ /*abstract*/ virtual  void modelStructureChanged();

 /**
  * Invoked when the contents of the underlying model have
  * completely changed. The structure of the table is the same,
  * only the contents have changed. This is typically sent when it
  * is too expensive to characterize the change in terms of the
  * other methods.
  * <p>
  * You normally do not call this method.  This method is public
  * to allow view classes to call it.
  */
 /*public*/ /*abstract*/ virtual void allRowsChanged();

 /**
  * Invoked when rows have been inserted into the underlying model
  * in the specified range (inclusive).
  * <p>
  * The arguments give the indices of the effected range.
  * The first argument is in terms of the model before the change, and
  * must be less than or equal to the size of the model before the change.
  * The second argument is in terms of the model after the change and must
  * be less than the size of the model after the change. For example,
  * if you have a 5-row model and add 3 items to the end of the model
  * the indices are 5, 7.
  * <p>
  * You normally do not call this method.  This method is public
  * to allow view classes to call it.
  *
  * @param firstRow the first row
  * @param endRow the last row
  * @throws IndexOutOfBoundsException if either argument is invalid, or
  *         <code>firstRow</code> &gt; <code>endRow</code>
  */
 /*public*/ /*abstract*/ virtual void rowsInserted(int firstRow, int endRow);

 /**
  * Invoked when rows have been deleted from the underlying model
  * in the specified range (inclusive).
  * <p>
  * The arguments give the indices of the effected range and
  * are in terms of the model <b>before</b> the change.
  * For example, if you have a 5-row model and delete 3 items from the end
  * of the model the indices are 2, 4.
  * <p>
  * You normally do not call this method.  This method is public
  * to allow view classes to call it.
  *
  * @param firstRow the first row
  * @param endRow the last row
  * @throws IndexOutOfBoundsException if either argument is outside
  *         the range of the model before the change, or
  *         <code>firstRow</code> &gt; <code>endRow</code>
  */
 /*public*/ /*abstract*/ virtual void rowsDeleted(int firstRow, int endRow);

 /**
  * Invoked when rows have been changed in the underlying model
  * between the specified range (inclusive).
  * <p>
  * You normally do not call this method.  This method is public
  * to allow view classes to call it.
  *
  * @param firstRow the first row, in terms of the underlying model
  * @param endRow the last row, in terms of the underlying model
  * @throws IndexOutOfBoundsException if either argument is outside
  *         the range of the underlying model, or
  *         <code>firstRow</code> &gt; <code>endRow</code>
  */
 /*public*/ /*abstract*/ virtual void rowsUpdated(int firstRow, int endRow);

 /**
  * Invoked when the column in the rows have been updated in
  * the underlying model between the specified range.
  * <p>
  * You normally do not call this method.  This method is public
  * to allow view classes to call it.
  *
  * @param firstRow the first row, in terms of the underlying model
  * @param endRow the last row, in terms of the underlying model
  * @param column the column that has changed, in terms of the underlying
  *        model
  * @throws IndexOutOfBoundsException if either argument is outside
  *         the range of the underlying model after the change,
  *         <code>firstRow</code> &gt; <code>endRow</code>, or
  *         <code>column</code> is outside the range of the underlying
  *          model
  */
 /*public*/ /*abstract*/ virtual void rowsUpdated(int firstRow, int endRow, int column);

signals:

public slots:
};

/**
 * SortKey describes the sort order for a particular column.  The
 * column index is in terms of the underlying model, which may differ
 * from that of the view.
 *
 * @since 1.6
 */
/*public*/ /*static*/ class SortKey : public QObject
{
 Q_OBJECT
    /*private*/ int column;
    /*private*/ SortOrder sortOrder;

public:
    /**
     * Creates a <code>SortKey</code> for the specified column with
     * the specified sort order.
     *
     * @param column index of the column, in terms of the model
     * @param sortOrder the sorter order
     * @throws IllegalArgumentException if <code>sortOrder</code> is
     *         <code>null</code>
     */
    /*public*/ SortKey(int column, SortOrder sortOrder);
    /*public*/ /*final*/ int getColumn() ;
    /*public*/ /*final*/ SortOrder getSortOrder() ;
//    /*public*/ int hashCode();
    /*public*/ bool equals(QObject* o);

};
#endif // ROWSORTER_H
