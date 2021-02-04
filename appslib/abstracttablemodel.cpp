#include "abstracttablemodel.h"
//#include "tablemodelevent.h"
#include "jtable.h"
#include "pushbuttondelegate.h"
#include "buttoncolumndelegate.h"
#include <QPushButton>

AbstractTableModel::AbstractTableModel(QObject *parent) :
    TableModel(parent)
{
 listenerList = new QList<EventListener*>();
// buttonMap = QList<int>();
 //_table = NULL;
}
/**
 *  This abstract class provides default implementations for most of
 *  the methods in the <code>TableModel</code> interface. It takes care of
 *  the management of listeners and provides some conveniences for generating
 *  <code>TableModelEvents</code> and dispatching them to the listeners.
 *  To create a concrete <code>TableModel</code> as a subclass of
 *  <code>AbstractTableModel</code> you need only provide implementations
 *  for the following three methods:
 *
 *  <pre>
 *  public int getRowCount();
 *  public int getColumnCount();
 *  public Object getValueAt(int row, int column);
 *  </pre>
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Alan Chung
 * @author Philip Milne
 */
//public abstract class AbstractTableModel implements TableModel, Serializable
//{
//
// Instance Variables
//

//
// Default Implementation of the Interface
//

/**
 *  Returns a default name for the column using spreadsheet conventions:
 *  A, B, C, ... Z, AA, AB, etc.  If <code>column</code> cannot be found,
 *  returns an empty string.
 *
 * @param column  the column being queried
 * @return a string containing the default name of <code>column</code>
 */
/*public*/ QString AbstractTableModel::getColumnName(int column) const
{
    QString result = "";
    for (; column >= 0; column = column / 26 - 1) {
        result = (char)((char)(column%26)+'A') + result;
    }
    return result;
}
/*private*/ QVariant AbstractTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
   return getColumnName(section) ;
  }
  return QVariant();
}
/**
 * Returns a column given its name.
 * Implementation is naive so this should be overridden if
 * this method is to be called often. This method is not
 * in the <code>TableModel</code> interface and is not used by the
 * <code>JTable</code>.
 *
 * @param columnName string containing name of column to be located
 * @return the column with <code>columnName</code>, or -1 if not found
 */
/*public*/ int AbstractTableModel::findColumn(QString columnName) {
    for (int i = 0; i < columnCount(QModelIndex()); i++) {
        if (columnName==(getColumnName(i))) {
            return i;
        }
    }
    return -1;
}

/**
 *  Returns <code>Object.class</code> regardless of <code>columnIndex</code>.
 *
 *  @param columnIndex  the column being queried
 *  @return the Object.class
 */
///*public*/ Class<?> getColumnClass(int columnIndex) {
//    return Object.class;
//}

/**
 *  Returns false.  This is the default implementation for all cells.
 *
 *  @param  rowIndex  the row being queried
 *  @param  columnIndex the column being queried
 *  @return false
 */
/*public*/ bool AbstractTableModel::isCellEditable(int /*rowIndex*/, int /*columnIndex*/) const
{
    return false;
}

/*private*/ Qt::ItemFlags AbstractTableModel::flags(const QModelIndex &index) const
{
 if(isCellEditable(index.row(), index.column()))
 {
  if(getColumnClass(index.column()) == "Boolean")
   return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
  else
   return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 }
 else
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/**
 *  This empty implementation is provided so users don't have to implement
 *  this method if their data model is not editable.
 *
 *  @param  aValue   value to assign to cell
 *  @param  rowIndex   row of cell
 *  @param  columnIndex  column of cell
 */
/*public*/ void AbstractTableModel::setValueAt(QVariant aValue, int rowIndex, int columnIndex) {
 setData(index(rowIndex, columnIndex), aValue, Qt::EditRole);
}

/*private*/ bool AbstractTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  setValueAt(value, index.row(), index.column());
  return true;
 }
 return false;
}

int AbstractTableModel::rowCount(const QModelIndex &parent) const
{
 return this->getRowCount();
}
int AbstractTableModel::columnCount(const QModelIndex &parent) const
{
 return this->getColumnCount();
}

//
//  Managing Listeners
//

/**
 * Adds a listener to the list that's notified each time a change
 * to the data model occurs.
 *
 * @param   l               the TableModelListener
 */
/*public*/ void AbstractTableModel::addTableModelListener(TableModelListener* /*l*/) {
//    listenerList.add(TableModelListener.class, l);
}

/**
 * Removes a listener from the list that's notified each time a
 * change to the data model occurs.
 *
 * @param   l               the TableModelListener
 */
/*public*/ void AbstractTableModel::removeTableModelListener(TableModelListener* l) {
//    listenerList.remove(TableModelListener.class, l);
}

/**
 * Returns an array of all the table model listeners
 * registered on this model.
 *
 * @return all of this model's <code>TableModelListener</code>s
 *         or an empty
 *         array if no table model listeners are currently registered
 *
 * @see #addTableModelListener
 * @see #removeTableModelListener
 *
 * @since 1.4
 */
/*public*/ QList<TableModelListener*>* AbstractTableModel::getTableModelListeners() {
//    return listenerList->getListeners(TableModelListener.class);
    return NULL;
}

//
//  Fire methods
//

/**
 * Notifies all listeners that all cell values in the table's
 * rows may have changed. The number of rows may also have changed
 * and the <code>JTable</code> should redraw the
 * table from scratch. The structure of the table (as in the order of the
 * columns) is assumed to be the same.
 *
 * @see TableModelEvent
 * @see EventListenerList
 * @see javax.swing.JTable#tableChanged(TableModelEvent)
 */
/*public*/ void AbstractTableModel::fireTableDataChanged()
{
 //fireTableChanged(new TableModelEvent(this));
 beginResetModel();
 endResetModel();
 //setPersistentButtons();
}

/**
 * Notifies all listeners that the table's structure has changed.
 * The number of columns in the table, and the names and types of
 * the new columns may be different from the previous state.
 * If the <code>JTable</code> receives this event and its
 * <code>autoCreateColumnsFromModel</code>
 * flag is set it discards any table columns that it had and reallocates
 * default columns in the order they appear in the model. This is the
 * same as calling <code>setModel(TableModel)</code> on the
 * <code>JTable</code>.
 *
 * @see TableModelEvent
 * @see EventListenerList
 */
/*public*/ void AbstractTableModel::fireTableStructureChanged()
{
 //fireTableChanged(new TableModelEvent(this, TableModelEvent::HEADER_ROW));
 beginResetModel();
 endResetModel();
}

/**
 * Notifies all listeners that rows in the range
 * <code>[firstRow, lastRow]</code>, inclusive, have been inserted.
 *
 * @param  firstRow  the first row
 * @param  lastRow   the last row
 *
 * @see TableModelEvent
 * @see EventListenerList
 *
 */
/*public*/ void AbstractTableModel::fireTableRowsInserted(int firstRow, int lastRow) {
    //fireTableChanged(new TableModelEvent(this, firstRow, lastRow,
//                         TableModelEvent::ALL_COLUMNS, TableModelEvent::INSERT));
 int rows = rowCount(QModelIndex());
 Q_ASSERT(lastRow < rows);
 beginInsertRows(QModelIndex(), firstRow, lastRow);
 endInsertRows();
 //setPersistentButtons();
}

/**
 * Notifies all listeners that rows in the range
 * <code>[firstRow, lastRow]</code>, inclusive, have been updated.
 *
 * @param firstRow  the first row
 * @param lastRow   the last row
 *
 * @see TableModelEvent
 * @see EventListenerList
 */
/*public*/ void AbstractTableModel::fireTableRowsUpdated(int firstRow, int lastRow) {
//    fireTableChanged(new TableModelEvent(this, firstRow, lastRow,
//                         TableModelEvent::ALL_COLUMNS, TableModelEvent::UPDATE));
 int rows = rowCount(QModelIndex());
 Q_ASSERT(lastRow < rows);
// beginInsertRows(QModelIndex(), firstRow, lastRow);
// endInsertRows();
 //setPersistentButtons();
}

/**
 * Notifies all listeners that rows in the range
 * <code>[firstRow, lastRow]</code>, inclusive, have been deleted.
 *
 * @param firstRow  the first row
 * @param lastRow   the last row
 *
 * @see TableModelEvent
 * @see EventListenerList
 */
/*public*/ void AbstractTableModel::fireTableRowsDeleted(int firstRow, int lastRow) {
//    fireTableChanged(new TableModelEvent(this, firstRow, lastRow,
//                         TableModelEvent::ALL_COLUMNS, TableModelEvent::DELETE));
    beginInsertRows(QModelIndex(), firstRow, lastRow);
    endInsertRows();
    //setPersistentButtons();
}

/**
 * Notifies all listeners that the value of the cell at
 * <code>[row, column]</code> has been updated.
 *
 * @param row  row of cell which has been updated
 * @param column  column of cell which has been updated
 * @see TableModelEvent
 * @see EventListenerList
 *
 *
 */
/*public*/ void AbstractTableModel::fireTableCellUpdated(int row, int column)
{
 //fireTableChanged(new TableModelEvent(this, row, row, column));
 beginResetModel();
 endResetModel();
}

/**
 * Forwards the given notification event to all
 * <code>TableModelListeners</code> that registered
 * themselves as listeners for this table model.
 *
 * @param e  the event to be forwarded
 *
 * @see #addTableModelListener
 * @see TableModelEvent
 * @see EventListenerList
 */
/*public*/ void AbstractTableModel::fireTableChanged(TableModelEvent* e)
{
#if 0
    // Guaranteed to return a non-null array
    QList<EventListener*>* listeners = listenerList->getListenerList();
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners->length-2; i>=0; i-=2) {
        if (listeners[i]==TableModelListener.class) {
            ((TableModelListener)listeners[i+1]).tableChanged(e);
        }
    }
#endif
}

/**
 * Returns an array of all the objects currently registered
 * as <code><em>Foo</em>Listener</code>s
 * upon this <code>AbstractTableModel</code>.
 * <code><em>Foo</em>Listener</code>s are registered using the
 * <code>add<em>Foo</em>Listener</code> method.
 *
 * <p>
 *
 * You can specify the <code>listenerType</code> argument
 * with a class literal,
 * such as
 * <code><em>Foo</em>Listener.class</code>.
 * For example, you can query a
 * model <code>m</code>
 * for its table model listeners with the following code:
 *
 * <pre>TableModelListener[] tmls = (TableModelListener[])(m.getListeners(TableModelListener.class));</pre>
 *
 * If no such listeners exist, this method returns an empty array.
 *
 * @param listenerType the type of listeners requested; this parameter
 *          should specify an interface that descends from
 *          <code>java.util.EventListener</code>
 * @return an array of all objects registered as
 *          <code><em>Foo</em>Listener</code>s on this component,
 *          or an empty array if no such
 *          listeners have been added
 * @exception ClassCastException if <code>listenerType</code>
 *          doesn't specify a class or interface that implements
 *          <code>java.util.EventListener</code>
 *
 * @see #getTableModelListeners
 *
 * @since 1.3
 */
#if 0
/*public*/ <T extends EventListener> T[] getListeners(Class<T> listenerType) {
    return listenerList.getListeners(listenerType);
}
#endif
/*protected*/ void AbstractTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* sample)
{ // TODO:
 // install a button renderer & editor
//    ButtonRenderer buttonRenderer = new ButtonRenderer();
//    table.setDefaultRenderer(JButton.class,buttonRenderer);
//    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//    table.setDefaultEditor(JButton.class,buttonEditor);
//    // ensure the table rows, columns have enough room for buttons
//    table.setRowHeight(sample.getPreferredSize().height);
//    table.getColumnModel().getColumn(column)
//        .setPreferredWidth((sample.getPreferredSize().width)+4);
 this->_table = table;
 MyDelegate* delegate;
 table->setItemDelegateForColumn(column, delegate = new MyDelegate());
 if(sample != NULL)
  delegate->setText(sample->text());
// if(!buttonMap.contains(column))
//  buttonMap.append(column);
// setHeaderData(column, Qt::Horizontal, 1, Qt::UserRole);
// ButtonColumnDelegate* delegate = new ButtonColumnDelegate(table);
// table->setItemDelegate(delegate);
 //setPersistentButtons();
}

void AbstractTableModel::setColumnToHoldDelegate(JTable *table, int column, QStyledItemDelegate *delegate)
{
 this->_table = table;
 table->setItemDelegateForColumn(column, delegate);
// if(!buttonMap.contains(column))
//  buttonMap.append(column);
}

//void AbstractTableModel::setPersistentButtons()
//{
// int rows = rowCount(QModelIndex());
// for(int row = 0; row < rows; row ++)
// {
//  foreach(int col, buttonMap)
//  {
//   QModelIndex ix = index(row, col);
//   if((flags(ix) & Qt::ItemIsEnabled) != 0 )
//   {
//    _table->openPersistentEditor(ix);
//   }
//  }
// }
//}

void AbstractTableModel::setTable(JTable * t)
{
 _table = t;
}

JTable* AbstractTableModel::table() { return _table;}

/*public*/ QVariant AbstractTableModel::getValueAt(int row, int col) const
{
 return data(index(row, col), Qt::DisplayRole);
}

QVariant AbstractTableModel::data(const QModelIndex &index, int role) const
{
 if((getColumnClass(index.column()) == "Boolean") && (role == Qt::CheckStateRole))
 {
  return getValueAt(index.row(), index.column()).toBool()?Qt::Checked:Qt::Unchecked;
 }
 if(role == Qt::ToolTipRole)
 {
  return getToolTip(index.column());
 }
 if(role == Qt::DisplayRole)
 {
  return getValueAt(index.row(), index.column());
 }
 return QVariant();
}

/*public*/ QString AbstractTableModel::getColumnClass(int col) const
{
 return "";
}
