#ifndef DEFAULTROWSORTER_H
#define DEFAULTROWSORTER_H
#include "rowsorter.h"
#include "comparator.h"
#include "comparable.h"
#include "rowfilter.h"

class FilterEntry;
class Row;
class ModelWrapper;
//template< typename I>
class DefaultRowSorter : public RowSorter
{
public:
 DefaultRowSorter();
 /*private*/ void allChanged();
 /*public*/ void modelStructureChanged();
 /*public*/ void setComparator(int column, Comparator* comparator);
 /*public*/ Comparator* getComparator(int column);
 /*public*/ int convertRowIndexToModel(int index);
 /*public*/ int getViewRowCount();
 /*public*/ int getModelRowCount();
 /*public*/ void setSortable(int column, bool sortable);
 /*public*/ QList</*? extends*/ SortKey*>* getSortKeys();
 /*public*/ void setMaxSortKeys(int max);
 /*public*/ void setSortsOnUpdates(bool sortsOnUpdates);
 /*public*/ bool getSortsOnUpdates();
 /*public*/ void setRowFilter(RowFilter/*<? super M,? super I>*/* filter);
 /*public*/ void toggleSortOrder(int column);
 /*public*/ int getMaxSortKeys();
 /*public*/ bool isSortable(int column);
 /*public*/ int convertRowIndexToView(int index);


private:
 /**
  * Whether or not we resort on TableModelEvent.UPDATEs.
  */
 /*private*/ bool sortsOnUpdates;

 /**
  * View (JTable) -> model.
  */
 /*private*/ QVector<Row*>* viewToModel;

 /**
  * model -> view (JTable)
  */
 /*private*/ QVector<int>* modelToView;

 /**
  * Comparators specified by column.
  */
 /*private*/ QVector<Comparator*>* comparators;

 /**
  * Whether or not the specified column is sortable, by column.
  */
 /*private*/ QVector<bool>* _isSortable;

 /**
  * Cached SortKeys for the current sort.
  */
 /*private*/ QVector<SortKey*>* cachedSortKeys;

 /**
  * Cached comparators for the current sort
  */
 /*private*/ QVector<Comparator*>* sortComparators;

 /**
  * Developer supplied Filter.
  */
 /*private*/ RowFilter/*<? super M, ? super I>*/* filter;

 /**
  * Value passed to the filter.  The same instance is passed to the
  * filter for different rows.
  */
 /*private*/ FilterEntry* filterEntry;

 /**
  * The sort keys.
  */
 /*private*/ QList<SortKey*>* sortKeys;

 /**
  * Whether or not to use getStringValueAt.  This is indexed by column.
  */
 /*private*/ QVector<bool>* useToString;

 /**
  * Indicates the contents are sorted.  This is used if
  * getSortsOnUpdates is false and an update event is received.
  */
 /*private*/ bool sorted;

 /**
  * Maximum number of sort keys.
  */
 /*private*/ int maxSortKeys;

 /**
  * Provides access to the data we're sorting/filtering.
  */
 /*private*/ ModelWrapper* modelWrapper;

 /**
  * Size of the model. This is used to enforce error checking within
  * the table changed notification methods (such as rowsInserted).
  */
 /*private*/ int modelRowCount;
 /*private*/ int compare(int model1, int model2);
 /*private*/ bool isTransformed();
 /*private*/ bool isUnsorted();
 /*private*/ void checkColumn(int column);
 /*private*/ SortKey* toggle(SortKey* key);


protected:
 /*protected*/ /*final*/ ModelWrapper* getModelWrapper();
 /*protected*/ /*final*/ void setModelWrapper(ModelWrapper* modelWrapper);

 friend class FilterEntry;
 friend class Row;
};

//template<typename I>
/*protected*/ /*abstract*/ /*static*/ class ModelWrapper
{
protected:
    /**
     * Creates a new <code>ModelWrapper</code>.
     */
    /*protected*/ ModelWrapper();
public:
    /**
     * Returns the underlying model that this <code>Model</code> is
     * wrapping.
     *
     * @return the underlying model
     */
    /*public*/ /*abstract*/ virtual QAbstractItemModel* getModel();

    /**
     * Returns the number of columns in the model.
     *
     * @return the number of columns in the model
     */
    /*public*/ /*abstract*/ virtual int getColumnCount();

    /**
     * Returns the number of rows in the model.
     *
     * @return the number of rows in the model
     */
    /*public*/ /*abstract*/ virtual int getRowCount();

    /**
     * Returns the value at the specified index.
     *
     * @param row the row index
     * @param column the column index
     * @return the value at the specified index
     * @throws IndexOutOfBoundsException if the indices are outside
     *         the range of the model
     */
    /*public*/ /*abstract*/ virtual QVariant getValueAt(int row, int column);

    /**
     * Returns the value as a <code>String</code> at the specified
     * index.  This implementation uses <code>toString</code> on
     * the result from <code>getValueAt</code> (making sure
     * to return an empty string for null values).  Subclasses that
     * override this method should never return null.
     *
     * @param row the row index
     * @param column the column index
     * @return the value at the specified index as a <code>String</code>
     * @throws IndexOutOfBoundsException if the indices are outside
     *         the range of the model
     */
    /*public*/ QString getStringValueAt(int row, int column);

    /**
     * Returns the identifier for the specified row.  The return value
     * of this is used as the identifier for the
     * <code>RowFilter.Entry</code> that is passed to the
     * <code>RowFilter</code>.
     *
     * @param row the row to return the identifier for, in terms of
     *            the underlying model
     * @return the identifier
     * @see RowFilter.Entry#getIdentifier
     */
    /*public*/ /*abstract*/virtual  int getIdentifier(int row);
};


/**
 * RowFilter.Entry implementation that delegates to the ModelWrapper.
 * getFilterEntry(int) creates the single instance of this that is
 * passed to the Filter.  Only call getFilterEntry(int) to get
 * the instance.
 */
//template<typename I>
/*private*/ class FilterEntry : public RowFilter/*<I>*///extends RowFilter.Entry<M,I>
{
    /**
     * The index into the model, set in getFilterEntry
     */
    int modelIndex;
    DefaultRowSorter* drs;
public:
    FilterEntry(DefaultRowSorter* drs);
    /*public*/ QAbstractItemModel* getModel();
    /*public*/ int getValueCount();
    /*public*/ QVariant getValue(int index);
    /*public*/ QString getStringValue(int index);
    /*public*/ int getIdentifier();
};

/**
 * Row is used to handle the actual sorting by way of Comparable.  It
 * will use the sortKeys to do the actual comparison.
 */
// NOTE: this class is static so that it can be placed in an array


/*private*/ /*static*/ class Row: public Comparable<Row>//implements Comparable<Row>
{

 /*private*/ DefaultRowSorter* sorter;
    int modelIndex;
public:
    /*public*/ Row(DefaultRowSorter* sorter, int index);
    /*public*/ int compareTo(Row o);

 friend class DefaultRowSorter;
};

#endif // DEFAULTROWSORTER_H
