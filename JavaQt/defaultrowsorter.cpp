#include "defaultrowsorter.h"
#include "exceptions.h"

//DefaultRowSorter::DefaultRowSorter()
//{

//}
/**
 * An implementation of <code>RowSorter</code> that provides sorting and
 * filtering around a grid-based data model.
 * Beyond creating and installing a <code>RowSorter</code>, you very rarely
 * need to interact with one directly.  Refer to
 * {@link javax.swing.table.TableRowSorter TableRowSorter} for a concrete
 * implementation of <code>RowSorter</code> for <code>JTable</code>.
 * <p>
 * Sorting is done based on the current <code>SortKey</code>s, in order.
 * If two objects are equal (the <code>Comparator</code> for the
 * column returns 0) the next <code>SortKey</code> is used.  If no
 * <code>SortKey</code>s remain or the order is <code>UNSORTED</code>, then
 * the order of the rows in the model is used.
 * <p>
 * Sorting of each column is done by way of a <code>Comparator</code>
 * that you can specify using the <code>setComparator</code> method.
 * If a <code>Comparator</code> has not been specified, the
 * <code>Comparator</code> returned by
 * <code>Collator.getInstance()</code> is used on the results of
 * calling <code>toString</code> on the underlying objects.  The
 * <code>Comparator</code> is never passed <code>NULL</code>.  A
 * <code>NULL</code> value is treated as occurring before a
 * non-<code>NULL</code> value, and two <code>NULL</code> values are
 * considered equal.
 * <p>
 * If you specify a <code>Comparator</code> that casts its argument to
 * a type other than that provided by the model, a
 * <code>ClassCastException</code> will be thrown when the data is sorted.
 * <p>
 * In addition to sorting, <code>DefaultRowSorter</code> provides the
 * ability to filter rows.  Filtering is done by way of a
 * <code>RowFilter</code> that is specified using the
 * <code>setRowFilter</code> method.  If no filter has been specified all
 * rows are included.
 * <p>
 * By default, rows are in unsorted order (the same as the model) and
 * every column is sortable. The default <code>Comparator</code>s are
 * documented in the subclasses (for example, {@link
 * javax.swing.table.TableRowSorter TableRowSorter}).
 * <p>
 * If the underlying model structure changes (the
 * <code>modelStructureChanged</code> method is invoked) the following
 * are reset to their default values: <code>Comparator</code>s by
 * column, current sort order, and whether each column is sortable. To
 * find the default <code>Comparator</code>s, see the concrete
 * implementation (for example, {@link
 * javax.swing.table.TableRowSorter TableRowSorter}).  The default
 * sort order is unsorted (the same as the model), and columns are
 * sortable by default.
 * <p>
 * If the underlying model structure changes (the
 * <code>modelStructureChanged</code> method is invoked) the following
 * are reset to their default values: <code>Comparator</code>s by column,
 * current sort order and whether a column is sortable.
 * <p>
 * <code>DefaultRowSorter</code> is an abstract class.  Concrete
 * subclasses must provide access to the underlying data by invoking
 * {@code setModelWrapper}. The {@code setModelWrapper} method
 * <b>must</b> be invoked soon after the constructor is
 * called, ideally from within the subclass's constructor.
 * Undefined behavior will result if you use a {@code
 * DefaultRowSorter} without specifying a {@code ModelWrapper}.
 * <p>
 * <code>DefaultRowSorter</code> has two formal type parameters.  The
 * first type parameter corresponds to the class of the model, for example
 * <code>DefaultTableModel</code>.  The second type parameter
 * corresponds to the class of the identifier passed to the
 * <code>RowFilter</code>.  Refer to <code>TableRowSorter</code> and
 * <code>RowFilter</code> for more details on the type parameters.
 *
 * @param <M> the type of the model
 * @param <I> the type of the identifier passed to the <code>RowFilter</code>
 * @see javax.swing.table.TableRowSorter
 * @see javax.swing.table.DefaultTableModel
 * @see java.text.Collator
 * @since 1.6
 */
// /*public*/ abstract class DefaultRowSorter<M, I> extends RowSorter<M> {


/**
 * Creates an empty <code>DefaultRowSorter</code>.
 */
/*public*/ DefaultRowSorter::DefaultRowSorter() {
    sortKeys = /*Collections.emptyList()*/ new QList<SortKey*>();
    maxSortKeys = 3;
    comparators = NULL;
}

/**
 * Sets the model wrapper providing the data that is being sorted and
 * filtered.
 *
 * @param modelWrapper the model wrapper responsible for providing the
 *         data that gets sorted and filtered
 * @throws IllegalArgumentException if {@code modelWrapper} is
 *         {@code NULL}
 */
/*protected*/ /*final*/ void DefaultRowSorter::setModelWrapper(ModelWrapper* modelWrapper) {
    if (modelWrapper == NULL) {
        throw new IllegalArgumentException(
            "modelWrapper most be non-NULL");
    }
    ModelWrapper* last = this->modelWrapper;
    this->modelWrapper = modelWrapper;
    if (last != NULL) {
        modelStructureChanged();
    } else {
        // If last is NULL, we're in the constructor. If we're in
        // the constructor we don't want to call to overridable methods.
        modelRowCount = getModelWrapper()->getRowCount();
    }
}

/**
 * Returns the model wrapper providing the data that is being sorted and
 * filtered.
 *
 * @return the model wrapper responsible for providing the data that
 *         gets sorted and filtered
 */
//template<class M, typename I>
/*protected*/ /*final*/ ModelWrapper* DefaultRowSorter::getModelWrapper() {
    return modelWrapper;
}
#if 0
/**
 * Returns the underlying model.
 *
 * @return the underlying model
 */
/*public*/ final M getModel() {
    return getModelWrapper().getModel();
}
#endif
/**
 * Sets whether or not the specified column is sortable.  The specified
 * value is only checked when <code>toggleSortOrder</code> is invoked.
 * It is still possible to sort on a column that has been marked as
 * unsortable by directly setting the sort keys.  The default is
 * true.
 *
 * @param column the column to enable or disable sorting on, in terms
 *        of the underlying model
 * @param sortable whether or not the specified column is sortable
 * @throws IndexOutOfBoundsException if <code>column</code> is outside
 *         the range of the model
 * @see #toggleSortOrder
 * @see #setSortKeys
 */
/*public*/ void DefaultRowSorter::setSortable(int column, bool sortable) {
    checkColumn(column);
    if (_isSortable == NULL) {
        _isSortable = new QVector<bool>(getModelWrapper()->getColumnCount());
        for (int i = _isSortable->length() - 1; i >= 0; i--) {
            _isSortable->replace(i, true);
        }
    }
    _isSortable->replace(column, sortable);
}

/**
 * Returns true if the specified column is sortable; otherwise, false.
 *
 * @param column the column to check sorting for, in terms of the
 *        underlying model
 * @return true if the column is sortable
 * @throws IndexOutOfBoundsException if column is outside
 *         the range of the underlying model
 */
/*public*/ bool DefaultRowSorter::isSortable(int column) {
    checkColumn(column);
    return (_isSortable == NULL) ? true : _isSortable->at(column);
}
#if 0
/**
 * Sets the sort keys. This creates a copy of the supplied
 * {@code List}; subsequent changes to the supplied
 * {@code List} do not effect this {@code DefaultRowSorter}.
 * If the sort keys have changed this triggers a sort.
 *
 * @param sortKeys the new <code>SortKeys</code>; <code>NULL</code>
 *        is a shorthand for specifying an empty list,
 *        indicating that the view should be unsorted
 * @throws IllegalArgumentException if any of the values in
 *         <code>sortKeys</code> are NULL or have a column index outside
 *         the range of the model
 */
/*public*/ void setSortKeys(List<? extends SortKey> sortKeys) {
    List<SortKey> old = this.sortKeys;
    if (sortKeys != NULL && sortKeys.size() > 0) {
        int max = getModelWrapper().getColumnCount();
        for (SortKey key : sortKeys) {
            if (key == NULL || key.getColumn() < 0 ||
                    key.getColumn() >= max) {
                throw new IllegalArgumentException("Invalid SortKey");
            }
        }
        this.sortKeys = Collections.unmodifiableList(
                new ArrayList<SortKey>(sortKeys));
    }
    else {
        this.sortKeys = Collections.emptyList();
    }
    if (!this.sortKeys.equals(old)) {
        fireSortOrderChanged();
        if (viewToModel == NULL) {
            // Currently unsorted, use sort so that internal fields
            // are correctly set.
            sort();
        } else {
            sortExistingData();
        }
    }
}
#endif
/**
 * Returns the current sort keys.  This returns an unmodifiable
 * {@code non-NULL List}. If you need to change the sort keys,
 * make a copy of the returned {@code List}, mutate the copy
 * and invoke {@code setSortKeys} with the new list.
 *
 * @return the current sort order
 */
/*public*/ QList</*? extends*/ SortKey*>* DefaultRowSorter::getSortKeys() {
    return sortKeys;
}

/**
 * Sets the maximum number of sort keys.  The number of sort keys
 * determines how equal values are resolved when sorting.  For
 * example, assume a table row sorter is created and
 * <code>setMaxSortKeys(2)</code> is invoked on it. The user
 * clicks the header for column 1, causing the table rows to be
 * sorted based on the items in column 1.  Next, the user clicks
 * the header for column 2, causing the table to be sorted based
 * on the items in column 2; if any items in column 2 are equal,
 * then those particular rows are ordered based on the items in
 * column 1. In this case, we say that the rows are primarily
 * sorted on column 2, and secondarily on column 1.  If the user
 * then clicks the header for column 3, then the items are
 * primarily sorted on column 3 and secondarily sorted on column
 * 2.  Because the maximum number of sort keys has been set to 2
 * with <code>setMaxSortKeys</code>, column 1 no longer has an
 * effect on the order.
 * <p>
 * The maximum number of sort keys is enforced by
 * <code>toggleSortOrder</code>.  You can specify more sort
 * keys by invoking <code>setSortKeys</code> directly and they will
 * all be honored.  However if <code>toggleSortOrder</code> is subsequently
 * invoked the maximum number of sort keys will be enforced.
 * The default value is 3.
 *
 * @param max the maximum number of sort keys
 * @throws IllegalArgumentException if <code>max</code> &lt; 1
 */
/*public*/ void DefaultRowSorter::setMaxSortKeys(int max) {
    if (max < 1) {
        throw new IllegalArgumentException("Invalid max");
    }
    maxSortKeys = max;
}

/**
 * Returns the maximum number of sort keys.
 *
 * @return the maximum number of sort keys
 */
/*public*/ int DefaultRowSorter::getMaxSortKeys() {
    return maxSortKeys;
}

/**
 * If true, specifies that a sort should happen when the underlying
 * model is updated (<code>rowsUpdated</code> is invoked).  For
 * example, if this is true and the user edits an entry the
 * location of that item in the view may change.  The default is
 * false.
 *
 * @param sortsOnUpdates whether or not to sort on update events
 */
/*public*/ void DefaultRowSorter::setSortsOnUpdates(bool sortsOnUpdates) {
    this->sortsOnUpdates = sortsOnUpdates;
}

/**
 * Returns true if  a sort should happen when the underlying
 * model is updated; otherwise, returns false.
 *
 * @return whether or not to sort when the model is updated
 */
/*public*/ bool DefaultRowSorter::getSortsOnUpdates() {
    return sortsOnUpdates;
}

/**
 * Sets the filter that determines which rows, if any, should be
 * hidden from the view.  The filter is applied before sorting.  A value
 * of <code>NULL</code> indicates all values from the model should be
 * included.
 * <p>
 * <code>RowFilter</code>'s <code>include</code> method is passed an
 * <code>Entry</code> that wraps the underlying model.  The number
 * of columns in the <code>Entry</code> corresponds to the
 * number of columns in the <code>ModelWrapper</code>.  The identifier
 * comes from the <code>ModelWrapper</code> as well.
 * <p>
 * This method triggers a sort.
 *
 * @param filter the filter used to determine what entries should be
 *        included
 */
/*public*/ void DefaultRowSorter::setRowFilter(RowFilter/*<? super M,? super I>*/* filter) {
    this->filter = filter;
#if 0 // TODO: ??
    sort();
#endif
}
#if 0
/**
 * Returns the filter that determines which rows, if any, should
 * be hidden from view.
 *
 * @return the filter
 */
/*public*/ RowFilter<? super M,? super I> getRowFilter() {
    return filter;
}
#endif
/**
 * Reverses the sort order from ascending to descending (or
 * descending to ascending) if the specified column is already the
 * primary sorted column; otherwise, makes the specified column
 * the primary sorted column, with an ascending sort order.  If
 * the specified column is not sortable, this method has no
 * effect.
 *
 * @param column index of the column to make the primary sorted column,
 *        in terms of the underlying model
 * @throws IndexOutOfBoundsException {@inheritDoc}
 * @see #setSortable(int,bool)
 * @see #setMaxSortKeys(int)
 */
/*public*/ void DefaultRowSorter::toggleSortOrder(int column)
{
 checkColumn(column);
 if (isSortable(column))
 {
  QList<SortKey*> keys = QList<SortKey*>(*getSortKeys());
  SortKey* sortKey;
  int sortIndex;
  for (sortIndex = keys.size() - 1; sortIndex >= 0; sortIndex--)
  {
   if (keys.value(sortIndex)->getColumn() == column) {
       break;
   }
  }
  if (sortIndex == -1)
  {
      // Key doesn't exist
      sortKey = new SortKey(column, ASCENDING);
      keys.insert(0, sortKey);
  }
  else if (sortIndex == 0) {
      // It's the primary sorting key, toggle it
      keys.replace(0, toggle(keys.value(0)));
  }
  else {
      // It's not the first, but was sorted on, remove old
      // entry, insert as first with ascending.
      keys.removeAt(sortIndex);
      keys.insert(0, new SortKey(column, ASCENDING));
  }
  if (keys.size() > getMaxSortKeys())
  {
      keys = keys.mid(0, getMaxSortKeys());
  }
  setSortKeys(&keys);
 }
}

/*private*/ SortKey* DefaultRowSorter::toggle(SortKey* key) {
    if (key->getSortOrder() == ASCENDING) {
        return new SortKey(key->getColumn(), DESCENDING);
    }
    return new SortKey(key->getColumn(), ASCENDING);
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ int DefaultRowSorter::convertRowIndexToView(int index) {
    if (modelToView == NULL) {
        if (index < 0 || index >= getModelWrapper()->getRowCount()) {
            throw new IndexOutOfBoundsException("Invalid index");
        }
        return index;
    }
    return modelToView->at(index);
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ int DefaultRowSorter::convertRowIndexToModel(int index) {
    if (viewToModel == NULL) {
        if (index < 0 || index >= getModelWrapper()->getRowCount()) {
            throw new IndexOutOfBoundsException("Invalid index");
        }
        return index;
    }
    return viewToModel->at(index)->modelIndex;
}


/*private*/ bool DefaultRowSorter::isUnsorted() {
    QList</*? extends */SortKey*>* keys = getSortKeys();
    int keySize = keys->size();
    return (keySize == 0 || keys->value(0)->getSortOrder() ==
            UNSORTED);
}
#if 0
/**
 * Sorts the existing filtered data.  This should only be used if
 * the filter hasn't changed.
 */
/*private*/ void sortExistingData() {
    int[] lastViewToModel = getViewToModelAsInts(viewToModel);

    updateUseToString();
    cacheSortKeys(getSortKeys());

    if (isUnsorted()) {
        if (getRowFilter() == NULL) {
            viewToModel = NULL;
            modelToView = NULL;
        } else {
            int included = 0;
            for (int i = 0; i < modelToView.length; i++) {
                if (modelToView[i] != -1) {
                    viewToModel[included].modelIndex = i;
                    modelToView[i] = included++;
                }
            }
        }
    } else {
        // sort the data
        Arrays.sort(viewToModel);

        // Update the modelToView array
        setModelToViewFromViewToModel(false);
    }
    fireRowSorterChanged(lastViewToModel);
}

/**
 * Sorts and filters the rows in the view based on the sort keys
 * of the columns currently being sorted and the filter, if any,
 * associated with this sorter.  An empty <code>sortKeys</code> list
 * indicates that the view should unsorted, the same as the model.
 *
 * @see #setRowFilter
 * @see #setSortKeys
 */
/*public*/ void sort() {
    sorted = true;
    int[] lastViewToModel = getViewToModelAsInts(viewToModel);
    updateUseToString();
    if (isUnsorted()) {
        // Unsorted
        cachedSortKeys = new SortKey[0];
        if (getRowFilter() == NULL) {
            // No filter & unsorted
            if (viewToModel != NULL) {
                // sorted -> unsorted
                viewToModel = NULL;
                modelToView = NULL;
            }
            else {
                // unsorted -> unsorted
                // No need to do anything.
                return;
            }
        }
        else {
            // There is filter, reset mappings
            initializeFilteredMapping();
        }
    }
    else {
        cacheSortKeys(getSortKeys());

        if (getRowFilter() != NULL) {
            initializeFilteredMapping();
        }
        else {
            createModelToView(getModelWrapper().getRowCount());
            createViewToModel(getModelWrapper().getRowCount());
        }

        // sort them
        Arrays.sort(viewToModel);

        // Update the modelToView array
        setModelToViewFromViewToModel(false);
    }
    fireRowSorterChanged(lastViewToModel);
}

/**
 * Updates the useToString mapping before a sort.
 */
/*private*/ void updateUseToString() {
    int i = getModelWrapper().getColumnCount();
    if (useToString == NULL || useToString.length != i) {
        useToString = new bool[i];
    }
    for (--i; i >= 0; i--) {
        useToString[i] = useToString(i);
    }
}

/**
 * Resets the viewToModel and modelToView mappings based on
 * the current Filter.
 */
/*private*/ void initializeFilteredMapping() {
    int rowCount = getModelWrapper().getRowCount();
    int i, j;
    int excludedCount = 0;

    // Update model -> view
    createModelToView(rowCount);
    for (i = 0; i < rowCount; i++) {
        if (include(i)) {
            modelToView[i] = i - excludedCount;
        }
        else {
            modelToView[i] = -1;
            excludedCount++;
        }
    }

    // Update view -> model
    createViewToModel(rowCount - excludedCount);
    for (i = 0, j = 0; i < rowCount; i++) {
        if (modelToView[i] != -1) {
            viewToModel[j++].modelIndex = i;
        }
    }
}

/**
 * Makes sure the modelToView array is of size rowCount.
 */
/*private*/ void createModelToView(int rowCount) {
    if (modelToView == NULL || modelToView.length != rowCount) {
        modelToView = new int[rowCount];
    }
}

/**
 * Resets the viewToModel array to be of size rowCount.
 */
/*private*/ void createViewToModel(int rowCount) {
    int recreateFrom = 0;
    if (viewToModel != NULL) {
        recreateFrom = Math.min(rowCount, viewToModel.length);
        if (viewToModel.length != rowCount) {
            Row[] oldViewToModel = viewToModel;
            viewToModel = new Row[rowCount];
            System.arraycopy(oldViewToModel, 0, viewToModel,
                             0, recreateFrom);
        }
    }
    else {
        viewToModel = new Row[rowCount];
    }
    int i;
    for (i = 0; i < recreateFrom; i++) {
        viewToModel[i].modelIndex = i;
    }
    for (i = recreateFrom; i < rowCount; i++) {
        viewToModel[i] = new Row(this, i);
    }
}

/**
 * Caches the sort keys before a sort.
 */
/*private*/ void cacheSortKeys(List<? extends SortKey> keys) {
    int keySize = keys.size();
    sortComparators = new Comparator[keySize];
    for (int i = 0; i < keySize; i++) {
        sortComparators[i] = getComparator0(keys.get(i).getColumn());
    }
    cachedSortKeys = keys.toArray(new SortKey[keySize]);
}

/**
 * Returns whether or not to convert the value to a string before
 * doing comparisons when sorting.  If true
 * <code>ModelWrapper.getStringValueAt</code> will be used, otherwise
 * <code>ModelWrapper.getValueAt</code> will be used.  It is up to
 * subclasses, such as <code>TableRowSorter</code>, to honor this value
 * in their <code>ModelWrapper</code> implementation.
 *
 * @param column the index of the column to test, in terms of the
 *        underlying model
 * @throws IndexOutOfBoundsException if <code>column</code> is not valid
 */
protected bool useToString(int column) {
    return (getComparator(column) == NULL);
}

/**
 * Refreshes the modelToView mapping from that of viewToModel.
 * If <code>unsetFirst</code> is true, all indices in modelToView are
 * first set to -1.
 */
/*private*/ void setModelToViewFromViewToModel(bool unsetFirst) {
    int i;
    if (unsetFirst) {
        for (i = modelToView.length - 1; i >= 0; i--) {
            modelToView[i] = -1;
        }
    }
    for (i = viewToModel.length - 1; i >= 0; i--) {
        modelToView[viewToModel[i].modelIndex] = i;
    }
}

/*private*/ int[] getViewToModelAsInts(Row[] viewToModel) {
    if (viewToModel != NULL) {
        int[] viewToModelI = new int[viewToModel.length];
        for (int i = viewToModel.length - 1; i >= 0; i--) {
            viewToModelI[i] = viewToModel[i].modelIndex;
        }
        return viewToModelI;
    }
    return new int[0];
}
#endif
/**
 * Sets the <code>Comparator</code> to use when sorting the specified
 * column.  This does not trigger a sort.  If you want to sort after
 * setting the comparator you need to explicitly invoke <code>sort</code>.
 *
 * @param column the index of the column the <code>Comparator</code> is
 *        to be used for, in terms of the underlying model
 * @param comparator the <code>Comparator</code> to use
 * @throws IndexOutOfBoundsException if <code>column</code> is outside
 *         the range of the underlying model
 */
/*public*/ void DefaultRowSorter::setComparator(int column, Comparator* comparator) {
    checkColumn(column);
    if (comparators == NULL) {
        comparators = new QVector<Comparator*>(getModelWrapper()->getColumnCount());
    }
    comparators->replace(column, comparator);
}

/**
 * Returns the <code>Comparator</code> for the specified
 * column.  This will return <code>NULL</code> if a <code>Comparator</code>
 * has not been specified for the column.
 *
 * @param column the column to fetch the <code>Comparator</code> for, in
 *        terms of the underlying model
 * @return the <code>Comparator</code> for the specified column
 * @throws IndexOutOfBoundsException if column is outside
 *         the range of the underlying model
 */
/*public*/ Comparator* DefaultRowSorter::getComparator(int column) {
    checkColumn(column);
    if (comparators != NULL) {
        return comparators->at(column);
    }
    return NULL;
}
#if 0
// Returns the Comparator to use during sorting.  Where as
// getComparator() may return NULL, this will never return NULL.
/*private*/ Comparator getComparator0(int column) {
    Comparator comparator = getComparator(column);
    if (comparator != NULL) {
        return comparator;
    }
    // This should be ok as useToString(column) should have returned
    // true in this case.
    return Collator.getInstance();
}

/*private*/ RowFilter.Entry<M,I> getFilterEntry(int modelIndex) {
    if (filterEntry == NULL) {
        filterEntry = new FilterEntry();
    }
    filterEntry.modelIndex = modelIndex;
    return filterEntry;
}
#endif
/**
 * {@inheritDoc}
 */
/*public*/ int DefaultRowSorter::getViewRowCount() {
    if (viewToModel != NULL) {
        // When filtering this may differ from getModelWrapper().getRowCount()
        return viewToModel->length();
    }
    return getModelWrapper()->getRowCount();
}

/**
 * {@inheritDoc}
 */
/*public*/ int DefaultRowSorter::getModelRowCount() {
    return getModelWrapper()->getRowCount();
}

/*private*/ void DefaultRowSorter::allChanged() {
    modelToView = NULL;
    viewToModel = NULL;
    comparators = NULL;
    _isSortable = NULL;
    if (isUnsorted()) {
        // Keys are already empty, to force a resort we have to
        // call sort
//        sort();
    } else {
        setSortKeys(NULL);
    }
}

/**
 * {@inheritDoc}
 */
/*public*/ void DefaultRowSorter::modelStructureChanged() {
    allChanged();
    modelRowCount = getModelWrapper()->getRowCount();
}
#if 0
/**
 * {@inheritDoc}
 */
/*public*/ void allRowsChanged() {
    modelRowCount = getModelWrapper().getRowCount();
    sort();
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ void rowsInserted(int firstRow, int endRow) {
    checkAgainstModel(firstRow, endRow);
    int newModelRowCount = getModelWrapper().getRowCount();
    if (endRow >= newModelRowCount) {
        throw new IndexOutOfBoundsException("Invalid range");
    }
    modelRowCount = newModelRowCount;
    if (shouldOptimizeChange(firstRow, endRow)) {
        rowsInserted0(firstRow, endRow);
    }
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ void rowsDeleted(int firstRow, int endRow) {
    checkAgainstModel(firstRow, endRow);
    if (firstRow >= modelRowCount || endRow >= modelRowCount) {
        throw new IndexOutOfBoundsException("Invalid range");
    }
    modelRowCount = getModelWrapper().getRowCount();
    if (shouldOptimizeChange(firstRow, endRow)) {
        rowsDeleted0(firstRow, endRow);
    }
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ void rowsUpdated(int firstRow, int endRow) {
    checkAgainstModel(firstRow, endRow);
    if (firstRow >= modelRowCount || endRow >= modelRowCount) {
        throw new IndexOutOfBoundsException("Invalid range");
    }
    if (getSortsOnUpdates()) {
        if (shouldOptimizeChange(firstRow, endRow)) {
            rowsUpdated0(firstRow, endRow);
        }
    }
    else {
        sorted = false;
    }
}

/**
 * {@inheritDoc}
 *
 * @throws IndexOutOfBoundsException {@inheritDoc}
 */
/*public*/ void rowsUpdated(int firstRow, int endRow, int column) {
    checkColumn(column);
    rowsUpdated(firstRow, endRow);
}

/*private*/ void checkAgainstModel(int firstRow, int endRow) {
    if (firstRow > endRow || firstRow < 0 || endRow < 0 ||
            firstRow > modelRowCount) {
        throw new IndexOutOfBoundsException("Invalid range");
    }
}

/**
 * Returns true if the specified row should be included.
 */
/*private*/ bool include(int row) {
    RowFilter<? super M, ? super I> filter = getRowFilter();
    if (filter != NULL) {
        return filter.include(getFilterEntry(row));
    }
    // NULL filter, always include the row.
    return true;
}
#endif
//@SuppressWarnings("unchecked")
/*private*/ int DefaultRowSorter::compare(int model1, int model2) {
    int column;
    SortOrder sortOrder;
    QVariant v1, v2;
    int result;

    for (int counter = 0; counter < cachedSortKeys->length(); counter++) {
        column = cachedSortKeys->at(counter)->getColumn();
        sortOrder = cachedSortKeys->at(counter)->getSortOrder();
        if (sortOrder == UNSORTED) {
            result = model1 - model2;
        } else {
            // v1 != NULL && v2 != NULL
            if (useToString->at(column)) {
                v1 = getModelWrapper()->getStringValueAt(model1, column);
                v2 = getModelWrapper()->getStringValueAt(model2, column);
            } else {
                v1 = getModelWrapper()->getValueAt(model1, column);
                v2 = getModelWrapper()->getValueAt(model2, column);
            }
            // Treat NULLs as < then non-NULL
            if (v1 == QVariant()) {
                if (v2 == QVariant()) {
                    result = 0;
                } else {
                    result = -1;
                }
            } else if (v2 == QVariant()) {
                result = 1;
            } else {
                result = sortComparators->at(counter)->compare(v1, v2);
            }
            if (sortOrder == DESCENDING) {
                result *= -1;
            }
        }
        if (result != 0) {
            return result;
        }
    }
    // If we get here, they're equal. Fallback to model order.
    return model1 - model2;
}

/**
 * Whether not we are filtering/sorting.
 */
/*private*/ bool DefaultRowSorter::isTransformed() {
    return (viewToModel != NULL);
}
#if 0
/**
 * Insets new set of entries.
 *
 * @param toAdd the Rows to add, sorted
 * @param current the array to insert the items into
 */
/*private*/ void insertInOrder(List<Row> toAdd, Row[] current) {
    int last = 0;
    int index;
    int max = toAdd.size();
    for (int i = 0; i < max; i++) {
        index = Arrays.binarySearch(current, toAdd.get(i));
        if (index < 0) {
            index = -1 - index;
        }
        System.arraycopy(current, last,
                         viewToModel, last + i, index - last);
        viewToModel[index + i] = toAdd.get(i);
        last = index;
    }
    System.arraycopy(current, last, viewToModel, last + max,
                     current.length - last);
}

/**
 * Returns true if we should try and optimize the processing of the
 * <code>TableModelEvent</code>.  If this returns false, assume the
 * event was dealt with and no further processing needs to happen.
 */
/*private*/ bool shouldOptimizeChange(int firstRow, int lastRow) {
    if (!isTransformed()) {
        // Not transformed, nothing to do.
        return false;
    }
    if (!sorted || (lastRow - firstRow) > viewToModel.length / 10) {
        // We either weren't sorted, or to much changed, sort it all
        sort();
        return false;
    }
    return true;
}

/*private*/ void rowsInserted0(int firstRow, int lastRow) {
    int[] oldViewToModel = getViewToModelAsInts(viewToModel);
    int i;
    int delta = (lastRow - firstRow) + 1;
    List<Row> added = new ArrayList<Row>(delta);

    // Build the list of Rows to add into added
    for (i = firstRow; i <= lastRow; i++) {
        if (include(i)) {
            added.add(new Row(this, i));
        }
    }

    // Adjust the model index of rows after the effected region
    int viewIndex;
    for (i = modelToView.length - 1; i >= firstRow; i--) {
        viewIndex = modelToView[i];
        if (viewIndex != -1) {
            viewToModel[viewIndex].modelIndex += delta;
        }
    }

    // Insert newly added rows into viewToModel
    if (added.size() > 0) {
        Collections.sort(added);
        Row[] lastViewToModel = viewToModel;
        viewToModel = new Row[viewToModel.length + added.size()];
        insertInOrder(added, lastViewToModel);
    }

    // Update modelToView
    createModelToView(getModelWrapper().getRowCount());
    setModelToViewFromViewToModel(true);

    // Notify of change
    fireRowSorterChanged(oldViewToModel);
}

/*private*/ void rowsDeleted0(int firstRow, int lastRow) {
    int[] oldViewToModel = getViewToModelAsInts(viewToModel);
    int removedFromView = 0;
    int i;
    int viewIndex;

    // Figure out how many visible rows are going to be effected.
    for (i = firstRow; i <= lastRow; i++) {
        viewIndex = modelToView[i];
        if (viewIndex != -1) {
            removedFromView++;
            viewToModel[viewIndex] = NULL;
        }
    }

    // Update the model index of rows after the effected region
    int delta = lastRow - firstRow + 1;
    for (i = modelToView.length - 1; i > lastRow; i--) {
        viewIndex = modelToView[i];
        if (viewIndex != -1) {
            viewToModel[viewIndex].modelIndex -= delta;
        }
    }

    // Then patch up the viewToModel array
    if (removedFromView > 0) {
        Row[] newViewToModel = new Row[viewToModel.length -
                                       removedFromView];
        int newIndex = 0;
        int last = 0;
        for (i = 0; i < viewToModel.length; i++) {
            if (viewToModel[i] == NULL) {
                System.arraycopy(viewToModel, last,
                                 newViewToModel, newIndex, i - last);
                newIndex += (i - last);
                last = i + 1;
            }
        }
        System.arraycopy(viewToModel, last,
                newViewToModel, newIndex, viewToModel.length - last);
        viewToModel = newViewToModel;
    }

    // Update the modelToView mapping
    createModelToView(getModelWrapper().getRowCount());
    setModelToViewFromViewToModel(true);

    // And notify of change
    fireRowSorterChanged(oldViewToModel);
}

/*private*/ void rowsUpdated0(int firstRow, int lastRow) {
    int[] oldViewToModel = getViewToModelAsInts(viewToModel);
    int i, j;
    int delta = lastRow - firstRow + 1;
    int modelIndex;
    int last;
    int index;

    if (getRowFilter() == NULL) {
        // Sorting only:

        // Remove the effected rows
        Row[] updated = new Row[delta];
        for (j = 0, i = firstRow; i <= lastRow; i++, j++) {
            updated[j] = viewToModel[modelToView[i]];
        }

        // Sort the update rows
        Arrays.sort(updated);

        // Build the intermediary array: the array of
        // viewToModel without the effected rows.
        Row[] intermediary = new Row[viewToModel.length - delta];
        for (i = 0, j = 0; i < viewToModel.length; i++) {
            modelIndex = viewToModel[i].modelIndex;
            if (modelIndex < firstRow || modelIndex > lastRow) {
                intermediary[j++] = viewToModel[i];
            }
        }

        // Build the new viewToModel
        insertInOrder(Arrays.asList(updated), intermediary);

        // Update modelToView
        setModelToViewFromViewToModel(false);
    }
    else {
        // Sorting & filtering.

        // Remove the effected rows, adding them to updated and setting
        // modelToView to -2 for any rows that were not filtered out
        List<Row> updated = new ArrayList<Row>(delta);
        int newlyVisible = 0;
        int newlyHidden = 0;
        int effected = 0;
        for (i = firstRow; i <= lastRow; i++) {
            if (modelToView[i] == -1) {
                // This row was filtered out
                if (include(i)) {
                    // No longer filtered
                    updated.add(new Row(this, i));
                    newlyVisible++;
                }
            }
            else {
                // This row was visible, make sure it should still be
                // visible.
                if (!include(i)) {
                    newlyHidden++;
                }
                else {
                    updated.add(viewToModel[modelToView[i]]);
                }
                modelToView[i] = -2;
                effected++;
            }
        }

        // Sort the updated rows
        Collections.sort(updated);

        // Build the intermediary array: the array of
        // viewToModel without the updated rows.
        Row[] intermediary = new Row[viewToModel.length - effected];
        for (i = 0, j = 0; i < viewToModel.length; i++) {
            modelIndex = viewToModel[i].modelIndex;
            if (modelToView[modelIndex] != -2) {
                intermediary[j++] = viewToModel[i];
            }
        }

        // Recreate viewToModel, if necessary
        if (newlyVisible != newlyHidden) {
            viewToModel = new Row[viewToModel.length + newlyVisible -
                                  newlyHidden];
        }

        // Rebuild the new viewToModel array
        insertInOrder(updated, intermediary);

        // Update modelToView
        setModelToViewFromViewToModel(true);
    }
    // And finally fire a sort event.
    fireRowSorterChanged(oldViewToModel);
}
#endif
/*private*/ void DefaultRowSorter::checkColumn(int column) {
    if (column < 0 || column >= getModelWrapper()->getColumnCount()) {
        throw new IndexOutOfBoundsException(
                "column beyond range of TableModel");
    }
}


/**
 * <code>DefaultRowSorter.ModelWrapper</code> is responsible for providing
 * the data that gets sorted by <code>DefaultRowSorter</code>.  You
 * normally do not interact directly with <code>ModelWrapper</code>.
 * Subclasses of <code>DefaultRowSorter</code> provide an
 * implementation of <code>ModelWrapper</code> wrapping another model.
 * For example,
 * <code>TableRowSorter</code> provides a <code>ModelWrapper</code> that
 * wraps a <code>TableModel</code>.
 * <p>
 * <code>ModelWrapper</code> makes a distinction between values as
 * <code>Object</code>s and <code>String</code>s.  This allows
 * implementations to provide a custom string
 * converter to be used instead of invoking <code>toString</code> on the
 * object.
 *
 * @param <M> the type of the underlying model
 * @param <I> the identifier supplied to the filter
 * @since 1.6
 * @see RowFilter
 * @see RowFilter.Entry
 */
//protected abstract static class ModelWrapper<M,I> {
    /**
     * Creates a new <code>ModelWrapper</code>.
     */
    /*protected*/ ModelWrapper::ModelWrapper() {
    }

    /**
     * Returns the underlying model that this <code>Model</code> is
     * wrapping.
     *
     * @return the underlying model
     */
        //template<class M>
    /*public*/ /*abstract*/ QAbstractItemModel* ModelWrapper::getModel() {return NULL;}
    /**
     * Returns the number of columns in the model.
     *
     * @return the number of columns in the model
     */
    /*public*/ /*abstract*/ int ModelWrapper::getColumnCount() {return 0;}

    /**
     * Returns the number of rows in the model.
     *
     * @return the number of rows in the model
     */
    /*public*/ /*abstract*/ int ModelWrapper::getRowCount() {return 0;}

    /**
     * Returns the value at the specified index.
     *
     * @param row the row index
     * @param column the column index
     * @return the value at the specified index
     * @throws IndexOutOfBoundsException if the indices are outside
     *         the range of the model
     */
    /*public*/ /*abstract*/ QVariant ModelWrapper::getValueAt(int row, int column) {return QVariant();}

    /**
     * Returns the value as a <code>String</code> at the specified
     * index.  This implementation uses <code>toString</code> on
     * the result from <code>getValueAt</code> (making sure
     * to return an empty string for NULL values).  Subclasses that
     * override this method should never return NULL.
     *
     * @param row the row index
     * @param column the column index
     * @return the value at the specified index as a <code>String</code>
     * @throws IndexOutOfBoundsException if the indices are outside
     *         the range of the model
     */
    /*public*/ QString ModelWrapper::getStringValueAt(int row, int column) {
        QVariant o = getValueAt(row, column);
        if (o == QVariant()) {
            return "";
        }
        QString string = o.toString();
        if (string == "") {
            return "";
        }
        return string;
    }

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
        //template<typename I>
    /*public*/ /*abstract*/ int ModelWrapper::getIdentifier(int row) {}
//}


/**
 * RowFilter.Entry implementation that delegates to the ModelWrapper.
 * getFilterEntry(int) creates the single instance of this that is
 * passed to the Filter.  Only call getFilterEntry(int) to get
 * the instance.
 */
// /*private*/ class FilterEntry extends RowFilter.Entry<M,I> {
    /**
     * The index into the model, set in getFilterEntry
     */
//    int modelIndex;
        FilterEntry::FilterEntry(DefaultRowSorter *drs) { this->drs = drs;}
//template<class M>
    /*public*/ QAbstractItemModel* FilterEntry::getModel() {
        return drs->getModelWrapper()->getModel();
    }

    /*public*/ int FilterEntry::getValueCount() {
        return drs->getModelWrapper()->getColumnCount();
    }

    /*public*/ QVariant FilterEntry::getValue(int index) {
        return drs->getModelWrapper()->getValueAt(modelIndex, index);
    }

    /*public*/ QString FilterEntry::getStringValue(int index) {
        return drs->getModelWrapper()->getStringValueAt(modelIndex, index);
    }

        //template<typename I>
    /*public*/ int FilterEntry::getIdentifier() {
        return drs->getModelWrapper()->getIdentifier(modelIndex);
    }
//};


/**
 * Row is used to handle the actual sorting by way of Comparable.  It
 * will use the sortKeys to do the actual comparison.
 */
// NOTE: this class is static so that it can be placed in an array
// /*private*/ static class Row implements Comparable<Row> {
//    /*private*/ DefaultRowSorter sorter;
//    int modelIndex;

    /*public*/ Row::Row(DefaultRowSorter* sorter, int index) {
        this->sorter = sorter;
        modelIndex = index;
    }

    /*public*/ int Row::compareTo(Row o) {
        return sorter->compare(modelIndex, o.modelIndex);
    }
//};

