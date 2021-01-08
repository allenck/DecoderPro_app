#include "xtablecolumnmodel.h"
#include "exceptions.h"
#include "tablecolumn.h"
#include "jtable.h"

/**
 * Taken from http://www.stephenkelvin.de/XTableColumnModel/
 * <code>XTableColumnModel</code> extends the DefaultTableColumnModel . It
 * provides a comfortable way to hide/show columns. Columns keep their positions
 * when hidden and shown again.
 *
 * In order to work with JTable it cannot add any events to
 * <code>TableColumnModelListener</code>. Therefore hiding a column will result
 * in <code>columnRemoved</code> event and showing it again will notify
 * listeners of a <code>columnAdded</code>, and possibly a
 * <code>columnMoved</code> event. For the same reason the following methods
 * still deal with visible columns only: getColumnCount(), getColumns(),
 * getColumnIndex(), getColumn() There are overloaded versions of these methods
 * that take a parameter <code>onlyVisible</code> which let's you specify wether
 * you want invisible columns taken into account.
 *
 * @version 0.9 04/03/01
 * @version	$Revision: 20525 $
 * @author Stephen Kelvin, mail@StephenKelvin.de
 * @see DefaultTableColumnModel
 */
///*public*/ class XTableColumnModel extends DefaultTableColumnModel {

/**
 *
 */
 //private static final long serialVersionUID = 6890678360829524192L;

/**
 * Creates an extended table column model.
 */
XTableColumnModel::XTableColumnModel(JTable *parent) :
  DefaultTableColumnModel(parent)
{
 allTableColumns =  QVector<TableColumn*>();
}

/**
 * Sets the visibility of the specified TableColumn. The call is ignored if
 * the TableColumn is not found in this column model or its visibility
 * status did not change.
 * <p>
 *
 * @param column  the column to show/hide
 * @param visible its new visibility status
 */
// listeners will receive columnAdded()/columnRemoved() event
/*public*/ void XTableColumnModel::setColumnVisible(TableColumn* column, bool visible)
{
 JTable* table = (JTable*)parent();
 bool visibility = !table->isColumnHidden(column->getModelIndex());
 if(visibility == visible)
  return;
 if(visible)
  table->showColumn(column->getModelIndex());
 else
  table->hideColumn(column->getModelIndex());
 if (!visible)
 {
  DefaultTableColumnModel::removeColumn(column);
 }
 else
 {
  // find the visible index of the column:
  // iterate through both collections of visible and all columns, counting
  // visible columns up to the one that's about to be shown again
  int noVisibleColumns = tableColumns.size();
  int noInvisibleColumns = allTableColumns.size();
  int visibleIndex = 0;

  for (int invisibleIndex = 0; invisibleIndex < noInvisibleColumns; ++invisibleIndex)
  {
   TableColumn* visibleColumn = (visibleIndex < noVisibleColumns ? (TableColumn*) tableColumns.at(visibleIndex) : NULL);
   TableColumn* testColumn = allTableColumns.at(invisibleIndex);

   if (testColumn == column)
   {
    if (visibleColumn != column)
    {
     DefaultTableColumnModel::addColumn(column);
     DefaultTableColumnModel::moveColumn(tableColumns.size() - 1, visibleIndex);
    }
    return; // ####################
   }
   if (testColumn == visibleColumn)
   {
    ++visibleIndex;
   }
  }
 }
}

/**
 * Makes all columns in this model visible
 */
/*public*/ void XTableColumnModel::setAllColumnsVisible()
{
 int noColumns = allTableColumns.size();

 for (int columnIndex = 0; columnIndex < noColumns; ++columnIndex) {
  TableColumn* visibleColumn = (columnIndex < tableColumns.size() ? (TableColumn*) tableColumns.at(columnIndex) : NULL);
  TableColumn* invisibleColumn = allTableColumns.at(columnIndex);

  if (visibleColumn != invisibleColumn)
  {
   DefaultTableColumnModel::addColumn(invisibleColumn);
   DefaultTableColumnModel::moveColumn(tableColumns.size() - 1, columnIndex);
  }
 }
}

/**
 * Maps the index of the column in the table model at
 * <code>modelColumnIndex</code> to the TableColumn object. There may me
 * multiple TableColumn objects showing the same model column, though this
 * is uncommon. This method will always return the first visible or else the
 * first invisible column with the specified index.
 *
 * @param modelColumnIndex index of column in table model
 * @return table column object or NULL if no such column in this column
 *         model
 */
/*public*/ TableColumn* XTableColumnModel::getColumnByModelIndex(int modelColumnIndex)
{
 for (int columnIndex = 0; columnIndex < allTableColumns.size(); ++columnIndex)
 {
  TableColumn* column = allTableColumns.at(columnIndex);
  if (column->getModelIndex() == modelColumnIndex)
  {
   return column;
  }
 }
 return NULL;
}

/**
 * Checks wether the specified column is currently visible.
 *
 * @param aColumn column to check
 * @return visibility of specified column (false if there is no such column
 *         at all. [It's not visible, right?])
 */
/*public*/ bool XTableColumnModel::isColumnVisible(TableColumn* aColumn) {
    return (tableColumns.indexOf(aColumn) >= 0);
}

/**
 * Append <code>column</code> to the right of exisiting columns. Posts
 * <code>columnAdded</code> event.
 *
 * @param column The column to be added
 * @see #removeColumn
 * @exception IllegalArgumentException if <code>column</code> is
 *                                     <code>NULL</code>
 */
/*public*/ void XTableColumnModel::addColumn(TableColumn* column)
{
 allTableColumns.append(column);
 DefaultTableColumnModel::addColumn(column);
}

/**
 * Removes <code>column</code> from this column model. Posts
 * <code>columnRemoved</code> event. Will do nothing if the column is not in
 * this model.
 *
 * @param column the column to be added
 * @see #addColumn
 */
/*public*/ void XTableColumnModel::removeColumn(TableColumn* column)
{
 int allColumnsIndex = allTableColumns.indexOf(column);
 if (allColumnsIndex != -1)
 {
  allTableColumns.remove(allColumnsIndex);
 }
 DefaultTableColumnModel::removeColumn(column);
}

/**
 * Moves the column from <code>oldIndex</code> to <code>newIndex</code>.
 * Posts  <code>columnMoved</code> event. Will not move any columns if
 * <code>oldIndex</code> equals <code>newIndex</code>.
 *
 * @param	oldIndex	index of column to be moved
 * @param	newIndex	new index of the column
 * @exception IllegalArgumentException	if either <code>oldIndex</code> or
 *                                     <code>newIndex</code> are not in [0,
 *                                     getColumnCount() - 1]
 */
//@Override
/*public*/ void XTableColumnModel::moveColumn(int columnIndex, int newIndex) {
    moveColumn(columnIndex, newIndex, true);
}

/**
 * Moves the column from {@code columnIndex} to {@code newIndex}. Posts
 * {@code columnMoved} event. Will not move any columns if
 * {@code columnIndex} equals {@code newIndex}. This method also posts a
 * {@code columnMoved} event to its listeners if a visible column moves.
 *
 * @param columnIndex index of column to be moved
 * @param newIndex    new index of the column
 * @param onlyVisible true if this should only move a visible column; false
 *                    to move any column
 * @exception IllegalArgumentException if either {@code oldIndex} or
 *                                     {@code newIndex} are not in [0,
 *                                     getColumnCount(onlyVisible) - 1]
 */
/*public*/ void XTableColumnModel::moveColumn(int columnIndex, int newIndex, bool onlyVisible) {
    if ((columnIndex < 0) || (columnIndex >= getColumnCount(onlyVisible))
            || (newIndex < 0) || (newIndex >= getColumnCount(onlyVisible))) {
        throw  IllegalArgumentException("moveColumn() - Index out of range");
    }

    if (onlyVisible) {
        if (columnIndex != newIndex) {
            // columnIndex and newIndex are indexes of visible columns, so need
            // to get index of column in list of all columns
            int allColumnsColumnIndex = allTableColumns.indexOf(tableColumns.value(columnIndex));
            int allColumnsNewIndex = allTableColumns.indexOf(tableColumns.value(newIndex));

            TableColumn* column = allTableColumns.at(allColumnsColumnIndex);
            allTableColumns.remove(allColumnsColumnIndex);
            allTableColumns.insert(allColumnsNewIndex, column);
        }

        DefaultTableColumnModel::moveColumn(columnIndex, newIndex);
    } else {
        if (columnIndex != newIndex) {
            // columnIndex and newIndex are indexes of all columns, so need
            // to get index of column in list of visible columns
            int visibleColumnIndex = tableColumns.indexOf(allTableColumns.value(columnIndex));
            int visibleNewIndex = tableColumns.indexOf(allTableColumns.value(newIndex));

            TableColumn* column = allTableColumns.at(columnIndex);
            allTableColumns.remove(columnIndex);
            allTableColumns.insert(newIndex, column);
            // call super moveColumn if both indexes are visible
            if (visibleColumnIndex != -1 && visibleNewIndex != -1) {
                DefaultTableColumnModel::moveColumn(visibleColumnIndex, visibleNewIndex);
            }
        }

    }
}

/**
 * Returns the total number of columns in this model.
 *
 * @param onlyVisible if set only visible columns will be counted
 * @return	the number of columns in the <code>tableColumns</code> array
 * @see	#getColumns
 */
/*public*/ int XTableColumnModel::getColumnCount(bool onlyVisible) {
    return getColumnList(onlyVisible).size();
}

/**
 * Returns an <code>Enumeration</code> of all the columns in the model.
 *
 * @param onlyVisible if set all invisible columns will be missing from the
 *                    enumeration.
 * @return an <code>Enumeration</code> of the columns in the model
 */
/*public*/ QListIterator<TableColumn *> XTableColumnModel::getColumns(bool onlyVisible)
{
 return QListIterator<TableColumn*>(getColumnList(onlyVisible).toList());
}

/**
 * Returns the position of the first column whose identifier equals
 * <code>identifier</code>. Position is the the index in all visible columns
 * if <code>onlyVisible</code> is true or else the index in all columns.
 *
 * @param	identifier  the identifier object to search for
 * @param	onlyVisible if set searches only visible columns
 *
 * @return	the index of the first column whose identifier equals
 *         <code>identifier</code>
 *
 * @exception IllegalArgumentException if <code>identifier</code> is
 *                                     <code>NULL</code>, or if no
 *                                     <code>TableColumn</code> has this
 *                                     <code>identifier</code>
 * @see	#getColumn
 */
/*public*/ int XTableColumnModel::getColumnIndex(QVariant identifier, bool onlyVisible)
{
 if (identifier == QVariant())
 {
  throw IllegalArgumentException("Identifier is NULL");
 }

 QVector<TableColumn*> columns = getColumnList(onlyVisible);
 int noColumns = columns.size();
 TableColumn* column;

 for (int columnIndex = 0; columnIndex < noColumns; ++columnIndex)
 {
  column = columns.at(columnIndex);

  if (identifier==(column->getIdentifier()))
  {
   return columnIndex;
  }
 }

 throw new IllegalArgumentException("Identifier not found");
}

/**
 * Returns the <code>TableColumn</code> object for the column at
 * <code>columnIndex</code>.
 *
 * @param	columnIndex	the index of the column desired
 * @param	onlyVisible	if set columnIndex is meant to be relative to all
 *                    visible columns only else it is the index in all
 *                    columns
 *
 * @return	the <code>TableColumn</code> object for the column at
 *         <code>columnIndex</code>
 */
/*public*/ TableColumn* XTableColumnModel::getColumn(int columnIndex, bool onlyVisible) {
    return getColumnList(onlyVisible).at(columnIndex);
}

/**
 * Get the list of columns. This list may be only the visible columns or may
 * be the list of all columns.
 *
 * @param onlyVisible true if the list should only contain visible columns;
 *                    false otherwise
 * @return the list of columns
 */
/*private*/ QVector<TableColumn*> XTableColumnModel::getColumnList(bool onlyVisible) {
    return (onlyVisible ? tableColumns : allTableColumns);
}
