#include "rowsorterutil.h"
#include "rowsorter.h"
#include "tablemodel.h"
RowSorterUtil::RowSorterUtil(QObject *parent) : QObject(parent)
{

}
/**
 * Utilities for handling JTable row sorting, assuming only a single column
 * influences the table sort order.
 * <p>
 * Multi-column sorting should be controlled by directly manipulating the
 * {@link javax.swing.RowSorter.SortKey}s returned by
 * {@link javax.swing.RowSorter#getSortKeys()}.
 *
 * @author Randall Wood
 */
// /*public*/ final class RowSorterUtil {

/**
 * Get the sort order for a column given a RowSorter for the TableModel
 * containing the column.
 *
 * @param rowSorter the sorter
 * @param column    the column index in the model, not the view
 * @return the sort order or {@link javax.swing.SortOrder#UNSORTED}.
 */
///*@Nonnull*/
/*public*/ /*static*/ SortOrder RowSorterUtil::getSortOrder(/*@Nonnull*/ RowSorter*/*<? extends TableModel>*/ rowSorter, int column) {
    foreach (SortKey* key, *rowSorter->getSortKeys()) {
        if (key->getColumn() == column) {
            return key->getSortOrder();
        }
    }
    return UNSORTED;
}

/**
 * Set the sort order for a table using the specified column given a
 * RowSorter for the TableModel containing the column.
 * <p>
 * This makes all other columns unsorted, even if the specified column is
 * also specified to be unsorted.
 *
 * @param rowSorter the sorter
 * @param column    the column index in the model, not the view
 * @param sortOrder the sort order
 */
/*public*/ /*static*/ void RowSorterUtil::setSortOrder(/*@Nonnull*/ RowSorter/*<? extends TableModel>*/* rowSorter, int column, /*@Nonnull*/ SortOrder sortOrder) {
    QList<SortKey*>* keys = new QList<SortKey*>();
    if (!sortOrder==(UNSORTED)) {
        keys->append(new SortKey(column, sortOrder));
    }
    rowSorter->setSortKeys(keys);
}
#if 0
/**
 * Add a RowSorterListener to the rowSorter that prevents multiple columns
 * from being considered while sorting.
 *
 * @param rowSorter the sorter to add the listener to
 * @return the added listener
 * @throws NullPointerException if rowSorter is null
 */
/*public*/ static RowSorterListener addSingleSortableColumnListener(/*@Nonnull*/ RowSorter<? extends TableModel> rowSorter) {
    Objects.requireNonNull(rowSorter, "rowSorter must be nonnull.");
    RowSorterListener listener = new RowSorterListener() {
        List<? extends SortKey> priorSortKeys = new ArrayList<>();

        @Override
        /*public*/ void sorterChanged(RowSorterEvent e) {
            if (e.getType().equals(RowSorterEvent.Type.SORT_ORDER_CHANGED)) {
                List<? extends SortKey> newSortKeys = new ArrayList<>(e.getSource().getSortKeys());
                newSortKeys.removeAll(priorSortKeys);
                if (!newSortKeys.isEmpty()) {
                    priorSortKeys = newSortKeys;
                    e.getSource().setSortKeys(priorSortKeys);
                    e.getSource().allRowsChanged();
                }
            }
        }
    };
    rowSorter.addRowSorterListener(listener);
    return listener;
}
#endif
