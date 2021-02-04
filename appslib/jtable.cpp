#include "jtable.h"
#include "tablecolumnmodel.h"
#include "propertychangeevent.h"
#include "exceptions.h"
#include "vptr.h"
#include "defaulttablecolumnmodel.h"
#include "defaultlistselectionmodel.h"
#include "defaulttablemodel.h"
//#include "tablemodelevent.h"
#include <QSortFilterProxyModel>
#include "logger.h"
#include <QAbstractItemModel>
#include "defaulttablecolumnmodel.h"
#include <QModelIndexList>
#include "rowsorter.h"
#include <QHeaderView>
#include "rowsorter.h"
#include "rowsorterevent.h"
#include "jtablepersistencemanager.h"
#include "tablemodelevent.h"
#include "vptr.h"
#include "sizesequence.h"
#include "defaulttablecolumnmodel.h"
#include "mysortfilterproxymodel.h"
#include "tablerowsorter.h"
#include "qsortfilterproxymodel.h"
#include <QPen>
#include "beantabledatamodel.h"

//JTable::JTable(QWidget *parent) :
//  QTableView(parent)
//{
//}

/**
 * The <code>JTable</code> is used to display and edit regular two-dimensional tables
 * of cells.
 * See <a href="http://docs.oracle.com/javase/tutorial/uiswing/components/table.html">How to Use Tables</a>
 * in <em>The Java Tutorial</em>
 * for task-oriented documentation and examples of using <code>JTable</code>.
 *
 * <p>
 * The <code>JTable</code> has many
 * facilities that make it possible to customize its rendering and editing
 * but provides defaults for these features so that simple tables can be
 * set up easily.  For example, to set up a table with 10 rows and 10
 * columns of numbers:
 *
 * <pre>
 *      TableModel dataModel = new AbstractTableModel() {
 *          public int getColumnCount() { return 10; }
 *          public int getRowCount() { return 10;}
 *          public Object getValueAt(int row, int col) { return new Integer(row*col); }
 *      };
 *      JTable table = new JTable(dataModel);
 *      JScrollPane scrollpane = new JScrollPane(table);
 * </pre>
 * <p>
 * {@code JTable}s are typically placed inside of a {@code JScrollPane}.  By
 * default, a {@code JTable} will adjust its width such that
 * a horizontal scrollbar is unnecessary.  To allow for a horizontal scrollbar,
 * invoke {@link #setAutoResizeMode} with {@code AUTO_RESIZE_OFF}.
 * Note that if you wish to use a <code>JTable</code> in a standalone
 * view (outside of a <code>JScrollPane</code>) and want the header
 * displayed, you can get it using {@link #getTableHeader} and
 * display it separately.
 * <p>
 * To enable sorting and filtering of rows, use a
 * {@code RowSorter}.
 * You can set up a row sorter in either of two ways:
 * <ul>
 *   <li>Directly set the {@code RowSorter}. For example:
 *        {@code table.setRowSorter(new TableRowSorter(model))}.
 *   <li>Set the {@code autoCreateRowSorter}
 *       property to {@code true}, so that the {@code JTable}
 *       creates a {@code RowSorter} for
 *       you. For example: {@code setAutoCreateRowSorter(true)}.
 * </ul>
 * <p>
 * When designing applications that use the <code>JTable</code> it is worth paying
 * close attention to the data structures that will represent the table's data.
 * The <code>DefaultTableModel</code> is a model implementation that
 * uses a <code>Vector</code> of <code>Vector</code>s of <code>Object</code>s to
 * store the cell values. As well as copying the data from an
 * application into the <code>DefaultTableModel</code>,
 * it is also possible to wrap the data in the methods of the
 * <code>TableModel</code> interface so that the data can be passed to the
 * <code>JTable</code> directly, as in the example above. This often results
 * in more efficient applications because the model is free to choose the
 * internal representation that best suits the data.
 * A good rule of thumb for deciding whether to use the <code>AbstractTableModel</code>
 * or the <code>DefaultTableModel</code> is to use the <code>AbstractTableModel</code>
 * as the base class for creating subclasses and the <code>DefaultTableModel</code>
 * when subclassing is not required.
 * <p>
 * The "TableExample" directory in the demo area of the source distribution
 * gives a number of complete examples of <code>JTable</code> usage,
 * covering how the <code>JTable</code> can be used to provide an
 * editable view of data taken from a database and how to modify
 * the columns in the display to use specialized renderers and editors.
 * <p>
 * The <code>JTable</code> uses integers exclusively to refer to both the rows and the columns
 * of the model that it displays. The <code>JTable</code> simply takes a tabular range of cells
 * and uses <code>getValueAt(int, int)</code> to retrieve the
 * values from the model during painting.  It is important to remember that
 * the column and row indexes returned by various <code>JTable</code> methods
 * are in terms of the <code>JTable</code> (the view) and are not
 * necessarily the same indexes used by the model.
 * <p>
 * By default, columns may be rearranged in the <code>JTable</code> so that the
 * view's columns appear in a different order to the columns in the model.
 * This does not affect the implementation of the model at all: when the
 * columns are reordered, the <code>JTable</code> maintains the new order of the columns
 * internally and converts its column indices before querying the model.
 * <p>
 * So, when writing a <code>TableModel</code>, it is not necessary to listen for column
 * reordering events as the model will be queried in its own coordinate
 * system regardless of what is happening in the view.
 * In the examples area there is a demonstration of a sorting algorithm making
 * use of exactly this technique to interpose yet another coordinate system
 * where the order of the rows is changed, rather than the order of the columns.
 * <p>
 * Similarly when using the sorting and filtering functionality
 * provided by <code>RowSorter</code> the underlying
 * <code>TableModel</code> does not need to know how to do sorting,
 * rather <code>RowSorter</code> will handle it.  Coordinate
 * conversions will be necessary when using the row based methods of
 * <code>JTable</code> with the underlying <code>TableModel</code>.
 * All of <code>JTable</code>s row based methods are in terms of the
 * <code>RowSorter</code>, which is not necessarily the same as that
 * of the underlying <code>TableModel</code>.  For example, the
 * selection is always in terms of <code>JTable</code> so that when
 * using <code>RowSorter</code> you will need to convert using
 * <code>convertRowIndexToView</code> or
 * <code>convertRowIndexToModel</code>.  The following shows how to
 * convert coordinates from <code>JTable</code> to that of the
 * underlying model:
 * <pre>
 *   int[] selection = table.getSelectedRows();
 *   for (int i = 0; i &lt; selection.length; i++) {
 *     selection[i] = table.convertRowIndexToModel(selection[i]);
 *   }
 *   // selection is now in terms of the underlying TableModel
 * </pre>
 * <p>
 * By default if sorting is enabled <code>JTable</code> will persist the
 * selection and variable row heights in terms of the model on
 * sorting.  For example if row 0, in terms of the underlying model,
 * is currently selected, after the sort row 0, in terms of the
 * underlying model will be selected.  Visually the selection may
 * change, but in terms of the underlying model it will remain the
 * same.  The one exception to that is if the model index is no longer
 * visible or was removed.  For example, if row 0 in terms of model
 * was filtered out the selection will be empty after the sort.
 * <p>
 * J2SE 5 adds methods to <code>JTable</code> to provide convenient access to some
 * common printing needs. Simple new {@link #print()} methods allow for quick
 * and easy addition of printing support to your application. In addition, a new
 * {@link #getPrintable} method is available for more advanced printing needs.
 * <p>
 * As for all <code>JComponent</code> classes, you can use
 * {@link InputMap} and {@link ActionMap} to associate an
 * {@link Action} object with a {@link KeyStroke} and execute the
 * action under specified conditions.
 * <p>
 * <strong>Warning:</strong> Swing is not thread safe. For more
 * information see <a
 * href="package-summary.html#threading">Swing's Threading
 * Policy</a>.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 *
 * @beaninfo
 *   attribute: isContainer false
 * description: A component which displays data in a two dimensional grid.
 *
 * @author Philip Milne
 * @author Shannon Hickey (printing support)
 * @see javax.swing.table.DefaultTableModel
 * @see javax.swing.table.TableRowSorter
 */
/* The first versions of the JTable, contained in Swing-0.1 through
 * Swing-0.4, were written by Alan Chung.
 */
///*public*/ class JTable extends JComponent implements TableModelListener, Scrollable,
//    TableColumnModelListener, ListSelectionListener, CellEditorListener,
//    Accessible, RowSorterListener
//{
//
// Static Constants
//

/**
 * @see #getUIClassID
 * @see #readObject
 */
//private static final String uiClassID = "TableUI";
#if 0
/**
 * A subclass of <code>TransferHandler.DropLocation</code> representing
 * a drop location for a <code>JTable</code>.
 *
 * @see #getDropLocation
 * @since 1.6
 */
/*public*/ static final class DropLocation extends TransferHandler.DropLocation {
    private final int row;
    private final int col;
    private final bool isInsertRow;
    private final bool isInsertCol;

    private DropLocation(Point p, int row, int col,
                         bool isInsertRow, bool isInsertCol) {

        super(p);
        this->row = row;
        this->col = col;
        this->isInsertRow = isInsertRow;
        this->isInsertCol = isInsertCol;
    }

    /**
     * Returns the row index where a dropped item should be placed in the
     * table. Interpretation of the value depends on the return of
     * <code>isInsertRow()</code>. If that method returns
     * <code>true</code> this value indicates the index where a new
     * row should be inserted. Otherwise, it represents the value
     * of an existing row on which the data was dropped. This index is
     * in terms of the view.
     * <p>
     * <code>-1</code> indicates that the drop occurred over empty space,
     * and no row could be calculated.
     *
     * @return the drop row
     */
    /*public*/ int getRow() {
        return row;
    }

    /**
     * Returns the column index where a dropped item should be placed in the
     * table. Interpretation of the value depends on the return of
     * <code>isInsertColumn()</code>. If that method returns
     * <code>true</code> this value indicates the index where a new
     * column should be inserted. Otherwise, it represents the value
     * of an existing column on which the data was dropped. This index is
     * in terms of the view.
     * <p>
     * <code>-1</code> indicates that the drop occurred over empty space,
     * and no column could be calculated.
     *
     * @return the drop row
     */
    /*public*/ int getColumn() {
        return col;
    }

    /**
     * Returns whether or not this location represents an insert
     * of a row.
     *
     * @return whether or not this is an insert row
     */
    /*public*/ bool isInsertRow() {
        return isInsertRow;
    }

    /**
     * Returns whether or not this location represents an insert
     * of a column.
     *
     * @return whether or not this is an insert column
     */
    /*public*/ bool isInsertColumn() {
        return isInsertCol;
    }

    /**
     * Returns a string representation of this drop location.
     * This method is intended to be used for debugging purposes,
     * and the content and format of the returned string may vary
     * between implementations.
     *
     * @return a string representation of this drop location
     */
    /*public*/ String toString() {
        return getClass().getName()
               + "[dropPoint=" + getDropPoint() + ","
               + "row=" + row + ","
               + "column=" + col + ","
               + "insertRow=" + isInsertRow + ","
               + "insertColumn=" + isInsertCol + "]";
    }
}; // end class DropLocation
#endif
//
// Constructors
//

/**
 * Constructs a default <code>JTable</code> that is initialized with a default
 * data model, a default column model, and a default selection
 * model.
 *
 * @see #createDefaultDataModel
 * @see #createDefaultColumnModel
 * @see #createDefaultSelectionModel
 */
/*public*/ JTable::JTable(QWidget *parent) :
  QTableView(parent)
{
 common(NULL, NULL, NULL);
}

///*public*/ JTable::JTable(TableModel* dm, QWidget *parent) :
//  QTableView(parent)
//{
// common(dm, NULL, NULL);
//}

/**
 * Constructs a <code>JTable</code> that is initialized with
 * <code>dm</code> as the data model, a default column model,
 * and a default selection model.
 *
 * @param dm        the data model for the table
 * @see #createDefaultColumnModel
 * @see #createDefaultSelectionModel
 */
/*public*/ JTable::JTable(TableModel* dm, QWidget *parent) :
  QTableView(parent)
{
 common(dm, NULL, NULL);
}

/*public*/ JTable::JTable(QAbstractItemModel* dm,QWidget *parent)
{
 common(dm, NULL, NULL);
}


/**
 * Constructs a <code>JTable</code> that is initialized with
 * <code>dm</code> as the data model, <code>cm</code>
 * as the column model, and a default selection model.
 *
 * @param dm        the data model for the table
 * @param cm        the column model for the table
 * @see #createDefaultSelectionModel
 */
/*public*/ JTable::JTable(TableModel* dm, TableColumnModel* cm, QWidget *parent) :
  QTableView(parent)
{
 common(dm, cm, NULL);
}

/**
 * Constructs a <code>JTable</code> that is initialized with
 * <code>dm</code> as the data model, <code>cm</code> as the
 * column model, and <code>sm</code> as the selection model.
 * If any of the parameters are <code>NULL</code> this method
 * will initialize the table with the corresponding default model.
 * The <code>autoCreateColumnsFromModel</code> flag is set to false
 * if <code>cm</code> is non-NULL, otherwise it is set to true
 * and the column model is populated with suitable
 * <code>TableColumns</code> for the columns in <code>dm</code>.
 *
 * @param dm        the data model for the table
 * @param cm        the column model for the table
 * @param sm        the row selection model for the table
 * @see #createDefaultDataModel
 * @see #createDefaultColumnModel
 * @see #createDefaultSelectionModel
 */
/*public*/ JTable::JTable(TableModel* dm, TableColumnModel* cm, DefaultListSelectionModel* sm, QWidget *parent) :
  QTableView(parent)
{
 //super();
 common( dm,  cm,  sm);
}

/*private*/void  JTable::common(QAbstractItemModel *dm, TableColumnModel* cm, DefaultListSelectionModel* sm)
{
 log = new Logger("JTable");
 editorRemover = NULL;
 columnModel = NULL;
//    setLayout(NULL);

//    setFocusTraversalKeys(KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS,
//                       JComponent.getManagingFocusForwardTraversalKeys());
//    setFocusTraversalKeys(KeyboardFocusManager.BACKWARD_TRAVERSAL_KEYS,
//                       JComponent.getManagingFocusBackwardTraversalKeys());
 if (cm == NULL)
 {
  cm = createDefaultColumnModel();
  autoCreateColumnsFromModel = true;
 }
 setColumnModel(cm);

 if (dm == NULL)
 {
  dm = createDefaultDataModel();
 }
 setModel(dm);
 dataModel = dm;

 if (sm == NULL)
 {
  sm = createDefaultSelectionModel();
 }
 setSelectionModel(sm);
 connect(sm, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), sm, SLOT(onSelectionChanged(QItemSelection,QItemSelection)));


// Set the model last, that way if the autoCreatColumnsFromModel has
// been set above, we will automatically populate an empty columnModel
// with suitable columns for the new model. WARNING! QT requires that data model
// be set before selection model can be.


 rowSorter = NULL;
 sortManager = NULL;
 rowModel = NULL;
 //initializeLocalVars();
 //updateUI();

 connect(horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(On_columnResized(int,int,int)));
 connect(horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sectionClicked(int)));
}
#if 0
/**
 * Constructs a <code>JTable</code> with <code>numRows</code>
 * and <code>numColumns</code> of empty cells using
 * <code>DefaultTableModel</code>.  The columns will have
 * names of the form "A", "B", "C", etc.
 *
 * @param numRows           the number of rows the table holds
 * @param numColumns        the number of columns the table holds
 * @see javax.swing.table.DefaultTableModel
 */
/*public*/ JTable::JTable(int numRows, int numColumns, QObject* parent)
 : QTableView(parent)
{
    common(new DefaultTableModel(numRows, numColumns));
}

/**
 * Constructs a <code>JTable</code> to display the values in the
 * <code>Vector</code> of <code>Vectors</code>, <code>rowData</code>,
 * with column names, <code>columnNames</code>.  The
 * <code>Vectors</code> contained in <code>rowData</code>
 * should contain the values for that row. In other words,
 * the value of the cell at row 1, column 5 can be obtained
 * with the following code:
 *
 * <pre>((Vector)rowData.elementAt(1)).elementAt(5);</pre>
 * <p>
 * @param rowData           the data for the new table
 * @param columnNames       names of each column
 */
/*public*/ JTable(Vector rowData, Vector columnNames) {
    this(new DefaultTableModel(rowData, columnNames));
}

/**
 * Constructs a <code>JTable</code> to display the values in the two dimensional array,
 * <code>rowData</code>, with column names, <code>columnNames</code>.
 * <code>rowData</code> is an array of rows, so the value of the cell at row 1,
 * column 5 can be obtained with the following code:
 *
 * <pre> rowData[1][5]; </pre>
 * <p>
 * All rows must ) be of the same length as <code>columnNames</code>.
 * <p>
 * @param rowData           the data for the new table
 * @param columnNames       names of each column
 */
/*public*/ JTable(final Object[][] rowData, final Object[] columnNames) {
    this(new AbstractTableModel() {
        /*public*/ String getColumnName(int column) { return columnNames[column].toString(); }
        /*public*/ int getRowCount() { return rowData.length; }
        /*public*/ int getColumnCount() { return columnNames.length; }
        /*public*/ Object getValueAt(int row, int col) { return rowData[row][col]; }
        /*public*/ bool isCellEditable(int row, int column) { return true; }
        /*public*/ void setValueAt(Object value, int row, int col) {
            rowData[row][col] = value;
            fireTableCellUpdated(row, col);
        }
    });
}
/**
 * Calls the <code>configureEnclosingScrollPane</code> method.
 *
 * @see #configureEnclosingScrollPane
 */
/*public*/ void addNotify() {
    super.addNotify();
    configureEnclosingScrollPane();
}

/**
 * If this <code>JTable</code> is the <code>viewportView</code> of an enclosing <code>JScrollPane</code>
 * (the usual situation), configure this <code>ScrollPane</code> by, amongst other things,
 * installing the table's <code>tableHeader</code> as the <code>columnHeaderView</code> of the scroll pane.
 * When a <code>JTable</code> is added to a <code>JScrollPane</code> in the usual way,
 * using <code>new JScrollPane(myTable)</code>, <code>addNotify</code> is
 * called in the <code>JTable</code> (when the table is added to the viewport).
 * <code>JTable</code>'s <code>addNotify</code> method in turn calls this method,
 * which is protected so that this default installation procedure can
 * be overridden by a subclass.
 *
 * @see #addNotify
 */
/*protected*/ void configureEnclosingScrollPane() {
    Container parent = SwingUtilities.getUnwrappedParent(this);
    if (parent instanceof JViewport) {
        JViewport port = (JViewport) parent;
        Container gp = port.getParent();
        if (gp instanceof JScrollPane) {
            JScrollPane scrollPane = (JScrollPane)gp;
            // Make certain we are the viewPort's view and not, for
            // example, the rowHeaderView of the scrollPane -
            // an implementor of fixed columns might do this->
            JViewport viewport = scrollPane.getViewport();
            if (viewport == NULL ||
                    SwingUtilities.getUnwrappedView(viewport) != this) {
                return;
            }
            scrollPane.setColumnHeaderView(getTableHeader());
            // configure the scrollpane for any LAF dependent settings
            configureEnclosingScrollPaneUI();
        }
    }
}

/**
 * This is a sub-part of configureEnclosingScrollPane() that configures
 * anything on the scrollpane that may change when the look and feel
 * changes. It needed to be split out from configureEnclosingScrollPane() so
 * that it can be called from updateUI() when the LAF changes without
 * causing the regression found in bug 6687962. This was because updateUI()
 * is called from the constructor which then caused
 * configureEnclosingScrollPane() to be called by the constructor which
 * changes its contract for any subclass that overrides it. So by splitting
 * it out in this way configureEnclosingScrollPaneUI() can be called both
 * from configureEnclosingScrollPane() and updateUI() in a safe manor.
 */
private void configureEnclosingScrollPaneUI() {
    Container parent = SwingUtilities.getUnwrappedParent(this);
    if (parent instanceof JViewport) {
        JViewport port = (JViewport) parent;
        Container gp = port.getParent();
        if (gp instanceof JScrollPane) {
            JScrollPane scrollPane = (JScrollPane)gp;
            // Make certain we are the viewPort's view and not, for
            // example, the rowHeaderView of the scrollPane -
            // an implementor of fixed columns might do this->
            JViewport viewport = scrollPane.getViewport();
            if (viewport == NULL ||
                    SwingUtilities.getUnwrappedView(viewport) != this) {
                return;
            }
            //  scrollPane.getViewport().setBackingStoreEnabled(true);
            Border border = scrollPane.getBorder();
            if (border == NULL || border instanceof UIResource) {
                Border scrollPaneBorder =
                    UIManager.getBorder("Table.scrollPaneBorder");
                if (scrollPaneBorder != NULL) {
                    scrollPane.setBorder(scrollPaneBorder);
                }
            }
            // add JScrollBar corner component if available from LAF and not already set by the user
            Component corner =
                    scrollPane.getCorner(JScrollPane.UPPER_TRAILING_CORNER);
            if (corner == NULL || corner instanceof UIResource){
                corner = NULL;
                try {
                    corner = (Component) UIManager.get(
                            "Table.scrollPaneCornerComponent");
                } catch (Exception e) {
                    // just ignore and don't set corner
                }
                scrollPane.setCorner(JScrollPane.UPPER_TRAILING_CORNER,
                        corner);
            }
        }
    }
}

/**
 * Calls the <code>unconfigureEnclosingScrollPane</code> method.
 *
 * @see #unconfigureEnclosingScrollPane
 */
/*public*/ void removeNotify() {
    KeyboardFocusManager.getCurrentKeyboardFocusManager().
        removePropertyChangeListener("permanentFocusOwner", editorRemover);
    editorRemover = NULL;
    unconfigureEnclosingScrollPane();
    super.removeNotify();
}

/**
 * Reverses the effect of <code>configureEnclosingScrollPane</code>
 * by replacing the <code>columnHeaderView</code> of the enclosing
 * scroll pane with <code>NULL</code>. <code>JTable</code>'s
 * <code>removeNotify</code> method calls
 * this method, which is protected so that this default uninstallation
 * procedure can be overridden by a subclass.
 *
 * @see #removeNotify
 * @see #configureEnclosingScrollPane
 * @since 1.3
 */
/*protected*/ void unconfigureEnclosingScrollPane() {
    Container parent = SwingUtilities.getUnwrappedParent(this);
    if (parent instanceof JViewport) {
        JViewport port = (JViewport) parent;
        Container gp = port.getParent();
        if (gp instanceof JScrollPane) {
            JScrollPane scrollPane = (JScrollPane)gp;
            // Make certain we are the viewPort's view and not, for
            // example, the rowHeaderView of the scrollPane -
            // an implementor of fixed columns might do this->
            JViewport viewport = scrollPane.getViewport();
            if (viewport == NULL ||
                    SwingUtilities.getUnwrappedView(viewport) != this) {
                return;
            }
            scrollPane.setColumnHeaderView(NULL);
            // remove ScrollPane corner if one was added by the LAF
            Component corner =
                    scrollPane.getCorner(JScrollPane.UPPER_TRAILING_CORNER);
            if (corner instanceof UIResource){
                scrollPane.setCorner(JScrollPane.UPPER_TRAILING_CORNER,
                        NULL);
            }
        }
    }
}

void setUIProperty(String propertyName, Object value) {
    if (propertyName == "rowHeight") {
        if (!isRowHeightSet) {
            setRowHeight(((Number)value).intValue());
            isRowHeightSet = false;
        }
        return;
    }
    super.setUIProperty(propertyName, value);
}

//
// Static Methods
//

/**
 * Equivalent to <code>new JScrollPane(aTable)</code>.
 *
 * @deprecated As of Swing version 1.0.2,
 * replaced by <code>new JScrollPane(aTable)</code>.
 */
@Deprecated
static /*public*/ JScrollPane createScrollPaneForTable(JTable aTable) {
    return new JScrollPane(aTable);
}

//
// Table Attributes
//

/**
 * Sets the <code>tableHeader</code> working with this <code>JTable</code> to <code>newHeader</code>.
 * It is legal to have a <code>NULL</code> <code>tableHeader</code>.
 *
 * @param   tableHeader                       new tableHeader
 * @see     #getTableHeader
 * @beaninfo
 *  bound: true
 *  description: The JTableHeader instance which renders the column headers.
 */
/*public*/ void setTableHeader(JTableHeader tableHeader) {
    if (this->tableHeader != tableHeader) {
        JTableHeader old = this->tableHeader;
        // Release the old header
        if (old != NULL) {
            old.setTable(NULL);
        }
        this->tableHeader = tableHeader;
        if (tableHeader != NULL) {
            tableHeader.setTable(this);
        }
        firePropertyChange("tableHeader", old, tableHeader);
    }
}
#endif
/**
 * Returns the <code>tableHeader</code> used by this <code>JTable</code>.
 *
 * @return  the <code>tableHeader</code> used by this table
 * @see     #setTableHeader
 */
/*public*/ QHeaderView* JTable::getTableHeader() {
    return horizontalHeader();
}

/**
 * Sets the height, in pixels, of all cells to <code>rowHeight</code>,
 * revalidates, and repaints.
 * The height of the cells will be equal to the row height minus
 * the row margin.
 *
 * @param   rowHeight                       new row height
 * @exception IllegalArgumentException      if <code>rowHeight</code> is
 *                                          less than 1
 * @see     #getRowHeight
 * @beaninfo
 *  bound: true
 *  description: The height of the specified row.
 */
/*public*/ void JTable::setRowHeight(int rowHeight) {
    if (rowHeight <= 0) {
        throw IllegalArgumentException("New row height less than 1");
    }
    int old = this->_rowHeight;
    this->_rowHeight = rowHeight;
    rowModel = NULL;
    if (sortManager != NULL) {
        sortManager->modelRowSizes = NULL;
    }
    isRowHeightSet = true;
//    resizeAndRepaint();
    firePropertyChange("rowHeight", old, rowHeight);
}

  /**
 * Returns the height of a table row, in pixels.
 *
 * @return  the height in pixels of a table row
 * @see     #setRowHeight
 */
/*public*/ int JTable::getRowHeight() {
    return _rowHeight;
}
/**
 * Returns the height of a table row, in pixels.
 *
 * @return  the height in pixels of a table row
 * @see     #setRowHeight
 */
/*public*/ int JTable::getRowHeight(int row) {
 return QTableView::rowHeight(row);
}

/*private*/ SizeSequence* JTable::getRowModel() {
    if (rowModel == NULL) {
        rowModel = new SizeSequence(getRowCount(), getRowHeight());
    }
    return rowModel;
}

/**
 * Sets the height for <code>row</code> to <code>rowHeight</code>,
 * revalidates, and repaints. The height of the cells in this row
 * will be equal to the row height minus the row margin.
 *
 * @param   row                             the row whose height is being
                                            changed
 * @param   rowHeight                       new row height, in pixels
 * @exception IllegalArgumentException      if <code>rowHeight</code> is
 *                                          less than 1
 * @beaninfo
 *  bound: true
 *  description: The height in pixels of the cells in <code>row</code>
 * @since 1.3
 */
/*public*/ void JTable::setRowHeight(int row, int rowHeight) {
    if (rowHeight <= 0) {
        throw IllegalArgumentException("New row height less than 1");
    }
    getRowModel()->setSize(row, rowHeight);
    if (sortManager != NULL) {
        sortManager->setViewRowHeight(row, rowHeight);
    }
    resizeAndRepaint();
}
#if 0
/**
 * Returns the height, in pixels, of the cells in <code>row</code>.
 * @param   row              the row whose height is to be returned
 * @return the height, in pixels, of the cells in the row
 * @since 1.3
 */
/*public*/ int getRowHeight(int row) {
    return (rowModel == NULL) ? getRowHeight() : rowModel.getSize(row);
}
#endif
/**
 * Sets the amount of empty space between cells in adjacent rows.
 *
 * @param  rowMargin  the number of pixels between cells in a row
 * @see     #getRowMargin
 * @beaninfo
 *  bound: true
 *  description: The amount of space between cells.
 */
/*public*/ void JTable::setRowMargin(int rowMargin) {
    int old = this->rowMargin;
    this->rowMargin = rowMargin;
    resizeAndRepaint();
    firePropertyChange("rowMargin", old, rowMargin);
}

/**
 * Gets the amount of empty space, in pixels, between cells. Equivalent to:
 * <code>getIntercellSpacing().height</code>.
 * @return the number of pixels between cells in a row
 *
 * @see     #setRowMargin
 */
/*public*/ int JTable::getRowMargin() {
    return rowMargin;
}

/**
 * Sets the <code>rowMargin</code> and the <code>columnMargin</code> --
 * the height and width of the space between cells -- to
 * <code>intercellSpacing</code>.
 *
 * @param   intercellSpacing        a <code>Dimension</code>
 *                                  specifying the new width
 *                                  and height between cells
 * @see     #getIntercellSpacing
 * @beaninfo
 *  description: The spacing between the cells,
 *               drawn in the background color of the JTable.
 */
/*public*/ void JTable::setIntercellSpacing(QSize intercellSpacing) {
    // Set the rowMargin here and columnMargin in the TableColumnModel
    setRowMargin(intercellSpacing.height());
    getColumnModel()->setColumnMargin(intercellSpacing.width());

    resizeAndRepaint();
}
#if 0
/**
 * Returns the horizontal and vertical space between cells.
 * The default spacing is look and feel dependent.
 *
 * @return  the horizontal and vertical spacing between cells
 * @see     #setIntercellSpacing
 */
/*public*/ Dimension getIntercellSpacing() {
    return new Dimension(getColumnModel().getColumnMargin(), rowMargin);
}
#endif
/**
 * Sets the color used to draw grid lines to <code>gridColor</code> and redisplays.
 * The default color is look and feel dependent.
 *
 * @param   gridColor                       the new color of the grid lines
 * @exception IllegalArgumentException      if <code>gridColor</code> is <code>NULL</code>
 * @see     #getGridColor
 * @beaninfo
 *  bound: true
 *  description: The grid color.
 */
/*public*/ void JTable::setGridColor(QColor gridColor) {
    if (!gridColor.isValid()) {
        throw  IllegalArgumentException("New color is NULL");
    }
    QColor old = this->gridColor;
    this->gridColor = gridColor;
    QTableView::setGridStyle(Qt::SolidLine);
    setStyleSheet(tr("QTableView{gridline-color: rgb(%1, %2, %3);}").arg(gridColor.red()).arg(gridColor.green()).arg(gridColor.blue()));
    firePropertyChange("gridColor", old, gridColor);
    // Redraw
    repaint();
}

/**
 * Returns the color used to draw grid lines.
 * The default color is look and feel dependent.
 *
 * @return  the color used to draw grid lines
 * @see     #setGridColor
 */
/*public*/ QColor JTable::getGridColor() {
    return gridColor;
}

/**
 *  Sets whether the table draws grid lines around cells.
 *  If <code>showGrid</code> is true it does; if it is false it doesn't.
 *  There is no <code>getShowGrid</code> method as this state is held
 *  in two variables -- <code>showHorizontalLines</code> and <code>showVerticalLines</code> --
 *  each of which can be queried independently.
 *
 * @param   showGrid                 true if table view should draw grid lines
 *
 * @see     #setShowVerticalLines
 * @see     #setShowHorizontalLines
 * @beaninfo
 *  description: The color used to draw the grid lines.
 */
/*public*/ void JTable::setShowGrid(bool showGrid) {
    setShowHorizontalLines(showGrid);
    setShowVerticalLines(showGrid);
    QTableView::setShowGrid(showGrid);

    // Redraw
    repaint();
}

/**
 *  Sets whether the table draws horizontal lines between cells.
 *  If <code>showHorizontalLines</code> is true it does; if it is false it doesn't.
 *
 * @param   showHorizontalLines      true if table view should draw horizontal lines
 * @see     #getShowHorizontalLines
 * @see     #setShowGrid
 * @see     #setShowVerticalLines
 * @beaninfo
 *  bound: true
 *  description: Whether horizontal lines should be drawn in between the cells.
 */
/*public*/ void JTable::setShowHorizontalLines(bool showHorizontalLines) {
    bool old = this->showHorizontalLines;
    this->showHorizontalLines = showHorizontalLines;
    firePropertyChange("showHorizontalLines", old, showHorizontalLines);

    // Redraw
    repaint();
}

/**
 *  Sets whether the table draws vertical lines between cells.
 *  If <code>showVerticalLines</code> is true it does; if it is false it doesn't.
 *
 * @param   showVerticalLines              true if table view should draw vertical lines
 * @see     #getShowVerticalLines
 * @see     #setShowGrid
 * @see     #setShowHorizontalLines
 * @beaninfo
 *  bound: true
 *  description: Whether vertical lines should be drawn in between the cells.
 */
/*public*/ void JTable::setShowVerticalLines(bool showVerticalLines) {
    bool old = this->showVerticalLines;
    this->showVerticalLines = showVerticalLines;
    firePropertyChange("showVerticalLines", old, showVerticalLines);
    // Redraw
    repaint();
}

/**
 * Returns true if the table draws horizontal lines between cells, false if it
 * doesn't. The default value is look and feel dependent.
 *
 * @return  true if the table draws horizontal lines between cells, false if it
 *          doesn't
 * @see     #setShowHorizontalLines
 */
/*public*/ bool JTable::getShowHorizontalLines() {
    return showHorizontalLines;
}

/**
 * Returns true if the table draws vertical lines between cells, false if it
 * doesn't. The default value is look and feel dependent.
 *
 * @return  true if the table draws vertical lines between cells, false if it
 *          doesn't
 * @see     #setShowVerticalLines
 */
/*public*/ bool JTable::getShowVerticalLines() {
    return showVerticalLines;
}

/**
 * Sets the table's auto resize mode when the table is resized.  For further
 * information on how the different resize modes work, see
 * {@link #doLayout}.
 *
 * @param   mode One of 5 legal values:
 *                   AUTO_RESIZE_OFF,
 *                   AUTO_RESIZE_NEXT_COLUMN,
 *                   AUTO_RESIZE_SUBSEQUENT_COLUMNS,
 *                   AUTO_RESIZE_LAST_COLUMN,
 *                   AUTO_RESIZE_ALL_COLUMNS
 *
 * @see     #getAutoResizeMode
 * @see     #doLayout
 * @beaninfo
 *  bound: true
 *  description: Whether the columns should adjust themselves automatically.
 *        enum: AUTO_RESIZE_OFF                JTable.AUTO_RESIZE_OFF
 *              AUTO_RESIZE_NEXT_COLUMN        JTable.AUTO_RESIZE_NEXT_COLUMN
 *              AUTO_RESIZE_SUBSEQUENT_COLUMNS JTable.AUTO_RESIZE_SUBSEQUENT_COLUMNS
 *              AUTO_RESIZE_LAST_COLUMN        JTable.AUTO_RESIZE_LAST_COLUMN
 *              AUTO_RESIZE_ALL_COLUMNS        JTable.AUTO_RESIZE_ALL_COLUMNS
 */
/*public*/ void JTable::setAutoResizeMode(int mode) {
    if ((mode == AUTO_RESIZE_OFF) ||
        (mode == AUTO_RESIZE_NEXT_COLUMN) ||
        (mode == AUTO_RESIZE_SUBSEQUENT_COLUMNS) ||
        (mode == AUTO_RESIZE_LAST_COLUMN) ||
        (mode == AUTO_RESIZE_ALL_COLUMNS)) {
        int old = autoResizeMode;
        autoResizeMode = mode;
        resizeAndRepaint();
//        if (tableHeader != NULL) {
//            tableHeader->resizeAndRepaint();
//        }
        firePropertyChange("autoResizeMode", old, autoResizeMode);
    }
}
#if 0
/**
 * Returns the auto resize mode of the table.  The default mode
 * is AUTO_RESIZE_SUBSEQUENT_COLUMNS.
 *
 * @return  the autoResizeMode of the table
 *
 * @see     #setAutoResizeMode
 * @see     #doLayout
 */
/*public*/ int getAutoResizeMode() {
    return autoResizeMode;
}
#endif

/**
 * Sets this table's <code>autoCreateColumnsFromModel</code> flag.
 * This method calls <code>createDefaultColumnsFromModel</code> if
 * <code>autoCreateColumnsFromModel</code> changes from false to true.
 *
 * @param   autoCreateColumnsFromModel   true if <code>JTable</code> should automatically create columns
 * @see     #getAutoCreateColumnsFromModel
 * @see     #createDefaultColumnsFromModel
 * @beaninfo
 *  bound: true
 *  description: Automatically populates the columnModel when a new TableModel is submitted.
 */
/*public*/ void JTable::setAutoCreateColumnsFromModel(bool autoCreateColumnsFromModel)
{
 if (this->autoCreateColumnsFromModel != autoCreateColumnsFromModel)
 {
  bool old = this->autoCreateColumnsFromModel;
  this->autoCreateColumnsFromModel = autoCreateColumnsFromModel;
  if (autoCreateColumnsFromModel)
  {
   createDefaultColumnsFromModel();
  }
  firePropertyChange("autoCreateColumnsFromModel", old, autoCreateColumnsFromModel);
 }
}

/**
 * Determines whether the table will create default columns from the model.
 * If true, <code>setModel</code> will clear any existing columns and
 * create new columns from the new model.  Also, if the event in
 * the <code>tableChanged</code> notification specifies that the
 * entire table changed, then the columns will be rebuilt.
 * The default is true.
 *
 * @return  the autoCreateColumnsFromModel of the table
 * @see     #setAutoCreateColumnsFromModel
 * @see     #createDefaultColumnsFromModel
 */
/*public*/ bool JTable::getAutoCreateColumnsFromModel()
{
 return autoCreateColumnsFromModel;
}

/**
 * Creates default columns for the table from
 * the data model using the <code>getColumnCount</code> method
 * defined in the <code>TableModel</code> interface.
 * <p>
 * Clears any existing columns before creating the
 * new columns based on information from the model.
 *
 * @see     #getAutoCreateColumnsFromModel
 */
/*public*/ void JTable::createDefaultColumnsFromModel()
{
 QAbstractItemModel* m = getModel();
 if (m != NULL)
 {
  if(m == nullptr)
   return;
  // Remove any current columns
  TableColumnModel* cm = getColumnModel();
  while (cm->getColumnCount() > 0)
  {
   cm->removeColumn(cm->getColumn(0));
  }

  // Create new columns from the data model info
  log->debug(QString("Table %3 contains %1 rows and %2 columns").arg(m->rowCount()).arg(m->columnCount()).arg(objectName()));
  //for (int i = 0; i < m->columnCount(QModelIndex()); i++)
  for(int i = 0; i < m->columnCount(/*QModelIndex()*/); i++)
  {
   TableColumn* newColumn = new TableColumn(i);
   newColumn->setHeaderValue(m->headerData(i,Qt::Horizontal));
   cm->addColumn(newColumn);
  }
  log->debug(QString("Column model contains %1 columns.").arg(cm->getColumnCount()));
 }
}
#if 0
/**
 * Sets a default cell renderer to be used if no renderer has been set in
 * a <code>TableColumn</code>. If renderer is <code>NULL</code>,
 * removes the default renderer for this column class.
 *
 * @param  columnClass     set the default cell renderer for this columnClass
 * @param  renderer        default cell renderer to be used for this
 *                         columnClass
 * @see     #getDefaultRenderer
 * @see     #setDefaultEditor
 */
/*public*/ void setDefaultRenderer(Class<?> columnClass, TableCellRenderer renderer) {
    if (renderer != NULL) {
        defaultRenderersByColumnClass.put(columnClass, renderer);
    }
    else {
        defaultRenderersByColumnClass.remove(columnClass);
    }
}

/**
 * Returns the cell renderer to be used when no renderer has been set in
 * a <code>TableColumn</code>. During the rendering of cells the renderer is fetched from
 * a <code>Hashtable</code> of entries according to the class of the cells in the column. If
 * there is no entry for this <code>columnClass</code> the method returns
 * the entry for the most specific superclass. The <code>JTable</code> installs entries
 * for <code>Object</code>, <code>Number</code>, and <code>Boolean</code>, all of which can be modified
 * or replaced.
 *
 * @param   columnClass   return the default cell renderer
 *                        for this columnClass
 * @return  the renderer for this columnClass
 * @see     #setDefaultRenderer
 * @see     #getColumnClass
 */
/*public*/ TableCellRenderer getDefaultRenderer(Class<?> columnClass) {
    if (columnClass == NULL) {
        return NULL;
    }
    else {
        Object renderer = defaultRenderersByColumnClass.get(columnClass);
        if (renderer != NULL) {
            return (TableCellRenderer)renderer;
        }
        else {
            Class c = columnClass.getSuperclass();
            if (c == NULL && columnClass != Object.class) {
                c = Object.class;
            }
            return getDefaultRenderer(c);
        }
    }
}
#endif
/**
 * Sets a default cell editor to be used if no editor has been set in
 * a <code>TableColumn</code>. If no editing is required in a table, or a
 * particular column in a table, uses the <code>isCellEditable</code>
 * method in the <code>TableModel</code> interface to ensure that this
 * <code>JTable</code> will not start an editor in these columns.
 * If editor is <code>NULL</code>, removes the default editor for this
 * column class.
 *
 * @param  columnClass  set the default cell editor for this columnClass
 * @param  editor   default cell editor to be used for this columnClass
 * @see     TableModel#isCellEditable
 * @see     #getDefaultEditor
 * @see     #setDefaultRenderer
 */
/*public*/ void JTable::setDefaultEditor(QString columnClass, QStyledItemDelegate* editor) {
//    if (editor != NULL) {
//        defaultEditorsByColumnClass.put(columnClass, editor);
//    }
//    else {
//        defaultEditorsByColumnClass.remove(columnClass);
//    }
    defaultItemDelegate = editor;
    for(int i = 0; i < getColumnCount(); i++)
    {
        if(qobject_cast<BeanTableDataModel*>(getModel()))
        {
           if(columnClass == ((BeanTableDataModel*) getModel())->getColumnClass(i))
           {
               if(((BeanTableDataModel*) getModel())->getColumnClass(i) == "JButton")
                ((BeanTableDataModel*) getModel())->setColumnToHoldDelegate(this, i, editor);
               if(((BeanTableDataModel*) getModel())->getColumnClass(i) == "JToggleButton")
                ((BeanTableDataModel*) getModel())->setColumnToHoldDelegate(this, i, editor);
               if(((BeanTableDataModel*) getModel())->getColumnClass(i) == "JComboBox")
                ((BeanTableDataModel*) getModel())->setColumnToHoldDelegate(this, i, editor);
           }
        }
    }
}
#if 0
/**
 * Returns the editor to be used when no editor has been set in
 * a <code>TableColumn</code>. During the editing of cells the editor is fetched from
 * a <code>Hashtable</code> of entries according to the class of the cells in the column. If
 * there is no entry for this <code>columnClass</code> the method returns
 * the entry for the most specific superclass. The <code>JTable</code> installs entries
 * for <code>Object</code>, <code>Number</code>, and <code>Boolean</code>, all of which can be modified
 * or replaced.
 *
 * @param   columnClass  return the default cell editor for this columnClass
 * @return the default cell editor to be used for this columnClass
 * @see     #setDefaultEditor
 * @see     #getColumnClass
 */
/*public*/ TableCellEditor getDefaultEditor(Class<?> columnClass) {
    if (columnClass == NULL) {
        return NULL;
    }
    else {
        Object editor = defaultEditorsByColumnClass.get(columnClass);
        if (editor != NULL) {
            return (TableCellEditor)editor;
        }
        else {
            return getDefaultEditor(columnClass.getSuperclass());
        }
    }
}

/**
 * Turns on or off automatic drag handling. In order to enable automatic
 * drag handling, this property should be set to {@code true}, and the
 * table's {@code TransferHandler} needs to be {@code non-NULL}.
 * The default value of the {@code dragEnabled} property is {@code false}.
 * <p>
 * The job of honoring this property, and recognizing a user drag gesture,
 * lies with the look and feel implementation, and in particular, the table's
 * {@code TableUI}. When automatic drag handling is enabled, most look and
 * feels (including those that subclass {@code BasicLookAndFeel}) begin a
 * drag and drop operation whenever the user presses the mouse button over
 * an item (in single selection mode) or a selection (in other selection
 * modes) and then moves the mouse a few pixels. Setting this property to
 * {@code true} can therefore have a subtle effect on how selections behave.
 * <p>
 * If a look and feel is used that ignores this property, you can still
 * begin a drag and drop operation by calling {@code exportAsDrag} on the
 * table's {@code TransferHandler}.
 *
 * @param b whether or not to enable automatic drag handling
 * @exception HeadlessException if
 *            <code>b</code> is <code>true</code> and
 *            <code>GraphicsEnvironment.isHeadless()</code>
 *            returns <code>true</code>
 * @see java.awt.GraphicsEnvironment#isHeadless
 * @see #getDragEnabled
 * @see #setTransferHandler
 * @see TransferHandler
 * @since 1.4
 *
 * @beaninfo
 *  description: determines whether automatic drag handling is enabled
 *        bound: false
 */
/*public*/ void setDragEnabled(bool b) {
    if (b && GraphicsEnvironment.isHeadless()) {
        throw new HeadlessException();
    }
    dragEnabled = b;
}

/**
 * Returns whether or not automatic drag handling is enabled.
 *
 * @return the value of the {@code dragEnabled} property
 * @see #setDragEnabled
 * @since 1.4
 */
/*public*/ bool getDragEnabled() {
    return dragEnabled;
}

/**
 * Sets the drop mode for this component. For backward compatibility,
 * the default for this property is <code>DropMode.USE_SELECTION</code>.
 * Usage of one of the other modes is recommended, however, for an
 * improved user experience. <code>DropMode.ON</code>, for instance,
 * offers similar behavior of showing items as selected, but does so without
 * affecting the actual selection in the table.
 * <p>
 * <code>JTable</code> supports the following drop modes:
 * <ul>
 *    <li><code>DropMode.USE_SELECTION</code></li>
 *    <li><code>DropMode.ON</code></li>
 *    <li><code>DropMode.INSERT</code></li>
 *    <li><code>DropMode.INSERT_ROWS</code></li>
 *    <li><code>DropMode.INSERT_COLS</code></li>
 *    <li><code>DropMode.ON_OR_INSERT</code></li>
 *    <li><code>DropMode.ON_OR_INSERT_ROWS</code></li>
 *    <li><code>DropMode.ON_OR_INSERT_COLS</code></li>
 * </ul>
 * <p>
 * The drop mode is only meaningful if this component has a
 * <code>TransferHandler</code> that accepts drops.
 *
 * @param dropMode the drop mode to use
 * @throws IllegalArgumentException if the drop mode is unsupported
 *         or <code>NULL</code>
 * @see #getDropMode
 * @see #getDropLocation
 * @see #setTransferHandler
 * @see TransferHandler
 * @since 1.6
 */
/*public*/ final void setDropMode(DropMode dropMode) {
    if (dropMode != NULL) {
        switch (dropMode) {
            case USE_SELECTION:
            case ON:
            case INSERT:
            case INSERT_ROWS:
            case INSERT_COLS:
            case ON_OR_INSERT:
            case ON_OR_INSERT_ROWS:
            case ON_OR_INSERT_COLS:
                this->dropMode = dropMode;
                return;
        }
    }

    throw new IllegalArgumentException(dropMode + ": Unsupported drop mode for table");
}

/**
 * Returns the drop mode for this component.
 *
 * @return the drop mode for this component
 * @see #setDropMode
 * @since 1.6
 */
/*public*/ final DropMode getDropMode() {
    return dropMode;
}

/**
 * Calculates a drop location in this component, representing where a
 * drop at the given point should insert data.
 *
 * @param p the point to calculate a drop location for
 * @return the drop location, or <code>NULL</code>
 */
DropLocation dropLocationForPoint(Point p) {
    DropLocation location = NULL;

    int row = rowAtPoint(p);
    int col = columnAtPoint(p);
    bool outside = Boolean.TRUE == getClientProperty("Table.isFileList")
                      && SwingUtilities2.pointOutsidePrefSize(this, row, col, p);

    Rectangle rect = getCellRect(row, col, true);
    Section xSection, ySection;
    bool between = false;
    bool ltr = getComponentOrientation().isLeftToRight();

    switch(dropMode) {
        case USE_SELECTION:
        case ON:
            if (row == -1 || col == -1 || outside) {
                location = new DropLocation(p, -1, -1, false, false);
            } else {
                location = new DropLocation(p, row, col, false, false);
            }
            break;
        case INSERT:
            if (row == -1 && col == -1) {
                location = new DropLocation(p, 0, 0, true, true);
                break;
            }

            xSection = SwingUtilities2.liesInHorizontal(rect, p, ltr, true);

            if (row == -1) {
                if (xSection == LEADING) {
                    location = new DropLocation(p, getRowCount(), col, true, true);
                } else if (xSection == TRAILING) {
                    location = new DropLocation(p, getRowCount(), col + 1, true, true);
                } else {
                    location = new DropLocation(p, getRowCount(), col, true, false);
                }
            } else if (xSection == LEADING || xSection == TRAILING) {
                ySection = SwingUtilities2.liesInVertical(rect, p, true);
                if (ySection == LEADING) {
                    between = true;
                } else if (ySection == TRAILING) {
                    row++;
                    between = true;
                }

                location = new DropLocation(p, row,
                                            xSection == TRAILING ? col + 1 : col,
                                            between, true);
            } else {
                if (SwingUtilities2.liesInVertical(rect, p, false) == TRAILING) {
                    row++;
                }

                location = new DropLocation(p, row, col, true, false);
            }

            break;
        case INSERT_ROWS:
            if (row == -1 && col == -1) {
                location = new DropLocation(p, -1, -1, false, false);
                break;
            }

            if (row == -1) {
                location = new DropLocation(p, getRowCount(), col, true, false);
                break;
            }

            if (SwingUtilities2.liesInVertical(rect, p, false) == TRAILING) {
                row++;
            }

            location = new DropLocation(p, row, col, true, false);
            break;
        case ON_OR_INSERT_ROWS:
            if (row == -1 && col == -1) {
                location = new DropLocation(p, -1, -1, false, false);
                break;
            }

            if (row == -1) {
                location = new DropLocation(p, getRowCount(), col, true, false);
                break;
            }

            ySection = SwingUtilities2.liesInVertical(rect, p, true);
            if (ySection == LEADING) {
                between = true;
            } else if (ySection == TRAILING) {
                row++;
                between = true;
            }

            location = new DropLocation(p, row, col, between, false);
            break;
        case INSERT_COLS:
            if (row == -1) {
                location = new DropLocation(p, -1, -1, false, false);
                break;
            }

            if (col == -1) {
                location = new DropLocation(p, getColumnCount(), col, false, true);
                break;
            }

            if (SwingUtilities2.liesInHorizontal(rect, p, ltr, false) == TRAILING) {
                col++;
            }

            location = new DropLocation(p, row, col, false, true);
            break;
        case ON_OR_INSERT_COLS:
            if (row == -1) {
                location = new DropLocation(p, -1, -1, false, false);
                break;
            }

            if (col == -1) {
                location = new DropLocation(p, row, getColumnCount(), false, true);
                break;
            }

            xSection = SwingUtilities2.liesInHorizontal(rect, p, ltr, true);
            if (xSection == LEADING) {
                between = true;
            } else if (xSection == TRAILING) {
                col++;
                between = true;
            }

            location = new DropLocation(p, row, col, false, between);
            break;
        case ON_OR_INSERT:
            if (row == -1 && col == -1) {
                location = new DropLocation(p, 0, 0, true, true);
                break;
            }

            xSection = SwingUtilities2.liesInHorizontal(rect, p, ltr, true);

            if (row == -1) {
                if (xSection == LEADING) {
                    location = new DropLocation(p, getRowCount(), col, true, true);
                } else if (xSection == TRAILING) {
                    location = new DropLocation(p, getRowCount(), col + 1, true, true);
                } else {
                    location = new DropLocation(p, getRowCount(), col, true, false);
                }

                break;
            }

            ySection = SwingUtilities2.liesInVertical(rect, p, true);
            if (ySection == LEADING) {
                between = true;
            } else if (ySection == TRAILING) {
                row++;
                between = true;
            }

            location = new DropLocation(p, row,
                                        xSection == TRAILING ? col + 1 : col,
                                        between,
                                        xSection != MIDDLE);

            break;
        default:
            assert false : "Unexpected drop mode";
    }

    return location;
}

/**
 * Called to set or clear the drop location during a DnD operation.
 * In some cases, the component may need to use it's internal selection
 * temporarily to indicate the drop location. To help facilitate this,
 * this method returns and accepts as a parameter a state object.
 * This state object can be used to store, and later restore, the selection
 * state. Whatever this method returns will be passed back to it in
 * future calls, as the state parameter. If it wants the DnD system to
 * continue storing the same state, it must pass it back every time.
 * Here's how this is used:
 * <p>
 * Let's say that on the first call to this method the component decides
 * to save some state (because it is about to use the selection to show
 * a drop index). It can return a state object to the caller encapsulating
 * any saved selection state. On a second call, let's say the drop location
 * is being changed to something else. The component doesn't need to
 * restore anything yet, so it simply passes back the same state object
 * to have the DnD system continue storing it. Finally, let's say this
 * method is messaged with <code>NULL</code>. This means DnD
 * is finished with this component for now, meaning it should restore
 * state. At this point, it can use the state parameter to restore
 * said state, and of course return <code>NULL</code> since there's
 * no longer anything to store.
 *
 * @param location the drop location (as calculated by
 *        <code>dropLocationForPoint</code>) or <code>NULL</code>
 *        if there's no longer a valid drop location
 * @param state the state object saved earlier for this component,
 *        or <code>NULL</code>
 * @param forDrop whether or not the method is being called because an
 *        actual drop occurred
 * @return any saved state for this component, or <code>NULL</code> if none
 */
Object setDropLocation(TransferHandler.DropLocation location,
                       Object state,
                       bool forDrop) {

    Object retVal = NULL;
    DropLocation tableLocation = (DropLocation)location;

    if (dropMode == DropMode.USE_SELECTION) {
        if (tableLocation == NULL) {
            if (!forDrop && state != NULL) {
                clearSelection();

                int[] rows = ((int[][])state)[0];
                int[] cols = ((int[][])state)[1];
                int[] anchleads = ((int[][])state)[2];

                for (int row : rows) {
                    addRowSelectionInterval(row, row);
                }

                for (int col : cols) {
                    addColumnSelectionInterval(col, col);
                }

                SwingUtilities2.setLeadAnchorWithoutSelection(
                        getSelectionModel(), anchleads[1], anchleads[0]);

                SwingUtilities2.setLeadAnchorWithoutSelection(
                        getColumnModel().getSelectionModel(),
                        anchleads[3], anchleads[2]);
            }
        } else {
            if (dropLocation == NULL) {
                retVal = new int[][]{
                    getSelectedRows(),
                    getSelectedColumns(),
                    {getAdjustedIndex(getSelectionModel()
                         .getAnchorSelectionIndex(), true),
                     getAdjustedIndex(getSelectionModel()
                         .getLeadSelectionIndex(), true),
                     getAdjustedIndex(getColumnModel().getSelectionModel()
                         .getAnchorSelectionIndex(), false),
                     getAdjustedIndex(getColumnModel().getSelectionModel()
                         .getLeadSelectionIndex(), false)}};
            } else {
                retVal = state;
            }

            if (tableLocation.getRow() == -1) {
                clearSelectionAndLeadAnchor();
            } else {
                setRowSelectionInterval(tableLocation.getRow(),
                                        tableLocation.getRow());
                setColumnSelectionInterval(tableLocation.getColumn(),
                                           tableLocation.getColumn());
            }
        }
    }

    DropLocation old = dropLocation;
    dropLocation = tableLocation;
    firePropertyChange("dropLocation", old, dropLocation);

    return retVal;
}

/**
 * Returns the location that this component should visually indicate
 * as the drop location during a DnD operation over the component,
 * or {@code NULL} if no location is to currently be shown.
 * <p>
 * This method is not meant for querying the drop location
 * from a {@code TransferHandler}, as the drop location is only
 * set after the {@code TransferHandler}'s <code>canImport</code>
 * has returned and has allowed for the location to be shown.
 * <p>
 * When this property changes, a property change event with
 * name "dropLocation" is fired by the component.
 *
 * @return the drop location
 * @see #setDropMode
 * @see TransferHandler#canImport(TransferHandler.TransferSupport)
 * @since 1.6
 */
/*public*/ final DropLocation getDropLocation() {
    return dropLocation;
}

/**
 * Specifies whether a {@code RowSorter} should be created for the
 * table whenever its model changes.
 * <p>
 * When {@code setAutoCreateRowSorter(true)} is invoked, a {@code
 * TableRowSorter} is immediately created and installed on the
 * table.  While the {@code autoCreateRowSorter} property remains
 * {@code true}, every time the model is changed, a new {@code
 * TableRowSorter} is created and set as the table's row sorter.
 * The default value for the {@code autoCreateRowSorter}
 * property is {@code false}.
 *
 * @param autoCreateRowSorter whether or not a {@code RowSorter}
 *        should be automatically created
 * @see javax.swing.table.TableRowSorter
 * @beaninfo
 *        bound: true
 *    preferred: true
 *  description: Whether or not to turn on sorting by default.
 * @since 1.6
 */
/*public*/ void setAutoCreateRowSorter(bool autoCreateRowSorter) {
    bool oldValue = this->autoCreateRowSorter;
    this->autoCreateRowSorter = autoCreateRowSorter;
    if (autoCreateRowSorter) {
        setRowSorter(new TableRowSorter<TableModel>(getModel()));
    }
    firePropertyChange("autoCreateRowSorter", oldValue,
                       autoCreateRowSorter);
}

/**
 * Returns {@code true} if whenever the model changes, a new
 * {@code RowSorter} should be created and installed
 * as the table's sorter; otherwise, returns {@code false}.
 *
 * @return true if a {@code RowSorter} should be created when
 *         the model changes
 * @since 1.6
 */
/*public*/ bool getAutoCreateRowSorter() {
    return autoCreateRowSorter;
}

/**
 * Specifies whether the selection should be updated after sorting.
 * If true, on sorting the selection is reset such that
 * the same rows, in terms of the model, remain selected.  The default
 * is true.
 *
 * @param update whether or not to update the selection on sorting
 * @beaninfo
 *        bound: true
 *       expert: true
 *  description: Whether or not to update the selection on sorting
 * @since 1.6
 */
/*public*/ void setUpdateSelectionOnSort(bool update) {
    if (updateSelectionOnSort != update) {
        updateSelectionOnSort = update;
        firePropertyChange("updateSelectionOnSort", !update, update);
    }
}

/**
 * Returns true if the selection should be updated after sorting.
 *
 * @return whether to update the selection on a sort
 * @since 1.6
 */
/*public*/ bool getUpdateSelectionOnSort() {
    return updateSelectionOnSort;
}

/**
 * Sets the <code>RowSorter</code>.  <code>RowSorter</code> is used
 * to provide sorting and filtering to a <code>JTable</code>.
 * <p>
 * This method clears the selection and resets any variable row heights.
 * <p>
 * This method fires a <code>PropertyChangeEvent</code> when appropriate,
 * with the property name <code>"rowSorter"</code>.  For
 * backward-compatibility, this method fires an additional event with the
 * property name <code>"sorter"</code>.
 * <p>
 * If the underlying model of the <code>RowSorter</code> differs from
 * that of this <code>JTable</code> undefined behavior will result.
 *
 * @param sorter the <code>RowSorter</code>; <code>NULL</code> turns
 *        sorting off
 * @see javax.swing.table.TableRowSorter
 * @beaninfo
 *        bound: true
 *  description: The table's RowSorter
 * @since 1.6
 */
/*public*/ void setRowSorter(RowSorter<? extends TableModel> sorter) {
    RowSorter<? extends TableModel> oldRowSorter = NULL;
    if (sortManager != NULL) {
        oldRowSorter = sortManager.sorter;
        sortManager.dispose();
        sortManager = NULL;
    }
    rowModel = NULL;
    clearSelectionAndLeadAnchor();
    if (sorter != NULL) {
        sortManager = new SortManager(sorter);
    }
    resizeAndRepaint();
    firePropertyChange("rowSorter", oldRowSorter, sorter);
    firePropertyChange("sorter", oldRowSorter, sorter);
}

/**
 * Returns the object responsible for sorting.
 *
 * @return the object responsible for sorting
 * @since 1.6
 */
/*public*/ RowSorter<? extends TableModel> getRowSorter() {
    return (sortManager != NULL) ? sortManager.sorter : NULL;
}
#endif
//
// Selection methods
//
/**
 * Sets the table's selection mode to allow only single selections, a single
 * contiguous interval, or multiple intervals.
 * <P>
 * <b>Note:</b>
 * <code>JTable</code> provides all the methods for handling
 * column and row selection.  When setting states,
 * such as <code>setSelectionMode</code>, it not only
 * updates the mode for the row selection model but also sets similar
 * values in the selection model of the <code>columnModel</code>.
 * If you want to have the row and column selection models operating
 * in different modes, set them both directly.
 * <p>
 * Both the row and column selection models for <code>JTable</code>
 * default to using a <code>DefaultListSelectionModel</code>
 * so that <code>JTable</code> works the same way as the
 * <code>JList</code>. See the <code>setSelectionMode</code> method
 * in <code>JList</code> for details about the modes.
 *
 * @see JList#setSelectionMode
 * @beaninfo
 * description: The selection mode used by the row and column selection models.
 *        enum: SINGLE_SELECTION            ListSelectionModel.SINGLE_SELECTION
 *              SINGLE_INTERVAL_SELECTION   ListSelectionModel.SINGLE_INTERVAL_SELECTION
 *              MULTIPLE_INTERVAL_SELECTION ListSelectionModel.MULTIPLE_INTERVAL_SELECTION
 */
/*public*/ void JTable::setSelectionMode(int selectionMode) {
//    clearSelection();
//    getSelectionModel().setSelectionMode(selectionMode);
//    getColumnModel().getSelectionModel().setSelectionMode(selectionMode);
 QTableView::setSelectionMode((QAbstractItemView::SelectionMode)selectionMode)   ;
}

/**
 * Sets whether the rows in this model can be selected.
 *
 * @param rowSelectionAllowed   true if this model will allow row selection
 * @see #getRowSelectionAllowed
 * @beaninfo
 *  bound: true
 *    attribute: visualUpdate true
 *  description: If true, an entire row is selected for each selected cell.
 */
/*public*/ void JTable::setRowSelectionAllowed(bool rowSelectionAllowed) {
    bool old = this->rowSelectionAllowed;
    this->rowSelectionAllowed = rowSelectionAllowed;
    setSelectionBehavior(rowSelectionAllowed?QAbstractItemView::SelectRows:QAbstractItemView::SelectItems);
    if (old != rowSelectionAllowed) {
        repaint();
    }
    firePropertyChange("rowSelectionAllowed", old, rowSelectionAllowed);
}

/**
 * Returns true if rows can be selected.
 *
 * @return true if rows can be selected, otherwise false
 * @see #setRowSelectionAllowed
 */
/*public*/ bool JTable::getRowSelectionAllowed() {
    return rowSelectionAllowed;
}
#if 0
/**
 * Sets whether the columns in this model can be selected.
 *
 * @param columnSelectionAllowed   true if this model will allow column selection
 * @see #getColumnSelectionAllowed
 * @beaninfo
 *  bound: true
 *    attribute: visualUpdate true
 *  description: If true, an entire column is selected for each selected cell.
 */
/*public*/ void setColumnSelectionAllowed(bool columnSelectionAllowed) {
    bool old = columnModel.getColumnSelectionAllowed();
    columnModel.setColumnSelectionAllowed(columnSelectionAllowed);
    if (old != columnSelectionAllowed) {
        repaint();
    }
    firePropertyChange("columnSelectionAllowed", old, columnSelectionAllowed);
}

/**
 * Returns true if columns can be selected.
 *
 * @return true if columns can be selected, otherwise false
 * @see #setColumnSelectionAllowed
 */
/*public*/ bool getColumnSelectionAllowed() {
    return columnModel.getColumnSelectionAllowed();
}

/**
 * Sets whether this table allows both a column selection and a
 * row selection to exist simultaneously. When set,
 * the table treats the intersection of the row and column selection
 * models as the selected cells. Override <code>isCellSelected</code> to
 * change this default behavior. This method is equivalent to setting
 * both the <code>rowSelectionAllowed</code> property and
 * <code>columnSelectionAllowed</code> property of the
 * <code>columnModel</code> to the supplied value.
 *
 * @param  cellSelectionEnabled     true if simultaneous row and column
 *                                  selection is allowed
 * @see #getCellSelectionEnabled
 * @see #isCellSelected
 * @beaninfo
 *  bound: true
 *    attribute: visualUpdate true
 *  description: Select a rectangular region of cells rather than
 *               rows or columns.
 */
/*public*/ void setCellSelectionEnabled(bool cellSelectionEnabled) {
    setRowSelectionAllowed(cellSelectionEnabled);
    setColumnSelectionAllowed(cellSelectionEnabled);
    bool old = this->cellSelectionEnabled;
    this->cellSelectionEnabled = cellSelectionEnabled;
    firePropertyChange("cellSelectionEnabled", old, cellSelectionEnabled);
}

/**
 * Returns true if both row and column selection models are enabled.
 * Equivalent to <code>getRowSelectionAllowed() &amp;&amp;
 * getColumnSelectionAllowed()</code>.
 *
 * @return true if both row and column selection models are enabled
 *
 * @see #setCellSelectionEnabled
 */
/*public*/ bool getCellSelectionEnabled() {
    return getRowSelectionAllowed() && getColumnSelectionAllowed();
}

/**
 *  Selects all rows, columns, and cells in the table.
 */
/*public*/ void selectAll() {
    // If I'm currently editing, then I should stop editing
    if (isEditing()) {
        removeEditor();
    }
    if (getRowCount() > 0 && getColumnCount() > 0) {
        int oldLead;
        int oldAnchor;
        ListSelectionModel selModel;

        selModel = selectionModel;
        selModel.setValueIsAdjusting(true);
        oldLead = getAdjustedIndex(selModel.getLeadSelectionIndex(), true);
        oldAnchor = getAdjustedIndex(selModel.getAnchorSelectionIndex(), true);

        setRowSelectionInterval(0, getRowCount()-1);

        // this is done to restore the anchor and lead
        SwingUtilities2.setLeadAnchorWithoutSelection(selModel, oldLead, oldAnchor);

        selModel.setValueIsAdjusting(false);

        selModel = columnModel.getSelectionModel();
        selModel.setValueIsAdjusting(true);
        oldLead = getAdjustedIndex(selModel.getLeadSelectionIndex(), false);
        oldAnchor = getAdjustedIndex(selModel.getAnchorSelectionIndex(), false);

        setColumnSelectionInterval(0, getColumnCount()-1);

        // this is done to restore the anchor and lead
        SwingUtilities2.setLeadAnchorWithoutSelection(selModel, oldLead, oldAnchor);

        selModel.setValueIsAdjusting(false);
    }
}
#endif
/**
 * Deselects all selected columns and rows.
 */
/*public*/ void JTable::clearSelection() {
    _selectionModel->clearSelection();
    columnModel->getSelectionModel()->clearSelection();
    QAbstractItemView::clearSelection();
}

/*private*/ void JTable::clearSelectionAndLeadAnchor() {
    _selectionModel->setValueIsAdjusting(true);
    columnModel->getSelectionModel()->setValueIsAdjusting(true);

    clearSelection();

     _selectionModel->setAnchorSelectionIndex(-1);
     _selectionModel->setLeadSelectionIndex(-1);
    columnModel->getSelectionModel()->setAnchorSelectionIndex(-1);
    columnModel->getSelectionModel()->setLeadSelectionIndex(-1);

     _selectionModel->setValueIsAdjusting(false);
    columnModel->getSelectionModel()->setValueIsAdjusting(false);
}
#if 0
private int getAdjustedIndex(int index, bool row) {
    int compare = row ? getRowCount() : getColumnCount();
    return index < compare ? index : -1;
}

private int boundRow(int row) throws IllegalArgumentException {
    if (row < 0 || row >= getRowCount()) {
        throw new IllegalArgumentException("Row index out of range");
    }
    return row;
}

private int boundColumn(int col) {
    if (col< 0 || col >= getColumnCount()) {
        throw new IllegalArgumentException("Column index out of range");
    }
    return col;
}

/**
 * Selects the rows from <code>index0</code> to <code>index1</code>,
 * inclusive.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getRowCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void setRowSelectionInterval(int index0, int index1) {
    selectionModel.setSelectionInterval(boundRow(index0), boundRow(index1));
}

/**
 * Selects the columns from <code>index0</code> to <code>index1</code>,
 * inclusive.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getColumnCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void setColumnSelectionInterval(int index0, int index1) {
    columnModel.getSelectionModel().setSelectionInterval(boundColumn(index0), boundColumn(index1));
}

/**
 * Adds the rows from <code>index0</code> to <code>index1</code>, inclusive, to
 * the current selection.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or <code>index1</code>
 *                                          lie outside [0, <code>getRowCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void addRowSelectionInterval(int index0, int index1) {
    selectionModel.addSelectionInterval(boundRow(index0), boundRow(index1));
}

/**
 * Adds the columns from <code>index0</code> to <code>index1</code>,
 * inclusive, to the current selection.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getColumnCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void addColumnSelectionInterval(int index0, int index1) {
    columnModel.getSelectionModel().addSelectionInterval(boundColumn(index0), boundColumn(index1));
}

/**
 * Deselects the rows from <code>index0</code> to <code>index1</code>, inclusive.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getRowCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void removeRowSelectionInterval(int index0, int index1) {
    selectionModel.removeSelectionInterval(boundRow(index0), boundRow(index1));
}

/**
 * Deselects the columns from <code>index0</code> to <code>index1</code>, inclusive.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getColumnCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void removeColumnSelectionInterval(int index0, int index1) {
    columnModel.getSelectionModel().removeSelectionInterval(boundColumn(index0), boundColumn(index1));
}

/**
 * Returns the index of the first selected row, -1 if no row is selected.
 * @return the index of the first selected row
 */
/*public*/ int getSelectedRow() {
    return selectionModel.getMinSelectionIndex();
}

/**
 * Returns the index of the first selected column,
 * -1 if no column is selected.
 * @return the index of the first selected column
 */
/*public*/ int getSelectedColumn() {
    return columnModel.getSelectionModel().getMinSelectionIndex();
}

/**
 * Returns the indices of all selected rows.
 *
 * @return an array of integers containing the indices of all selected rows,
 *         or an empty array if no row is selected
 * @see #getSelectedRow
 */
/*public*/ int[] getSelectedRows() {
    int iMin = selectionModel.getMinSelectionIndex();
    int iMax = selectionModel.getMaxSelectionIndex();

    if ((iMin == -1) || (iMax == -1)) {
        return new int[0];
    }

    int[] rvTmp = new int[1+ (iMax - iMin)];
    int n = 0;
    for(int i = iMin; i <= iMax; i++) {
        if (selectionModel.isSelectedIndex(i)) {
            rvTmp[n++] = i;
        }
    }
    int[] rv = new int[n];
    System.arraycopy(rvTmp, 0, rv, 0, n);
    return rv;
}

/**
 * Returns the indices of all selected columns.
 *
 * @return an array of integers containing the indices of all selected columns,
 *         or an empty array if no column is selected
 * @see #getSelectedColumn
 */
/*public*/ int[] getSelectedColumns() {
    return columnModel.getSelectedColumns();
}

/**
 * Returns the number of selected rows.
 *
 * @return the number of selected rows, 0 if no rows are selected
 */
/*public*/ int getSelectedRowCount() {
    int iMin = selectionModel.getMinSelectionIndex();
    int iMax = selectionModel.getMaxSelectionIndex();
    int count = 0;

    for(int i = iMin; i <= iMax; i++) {
        if (selectionModel.isSelectedIndex(i)) {
            count++;
        }
    }
    return count;
}

/**
 * Returns the number of selected columns.
 *
 * @return the number of selected columns, 0 if no columns are selected
 */
/*public*/ int getSelectedColumnCount() {
    return columnModel.getSelectedColumnCount();
}

/**
 * Returns true if the specified index is in the valid range of rows,
 * and the row at that index is selected.
 *
 * @return true if <code>row</code> is a valid index and the row at
 *              that index is selected (where 0 is the first row)
 */
/*public*/ bool isRowSelected(int row) {
    return selectionModel.isSelectedIndex(row);
}

/**
 * Returns true if the specified index is in the valid range of columns,
 * and the column at that index is selected.
 *
 * @param   column   the column in the column model
 * @return true if <code>column</code> is a valid index and the column at
 *              that index is selected (where 0 is the first column)
 */
/*public*/ bool isColumnSelected(int column) {
    return columnModel.getSelectionModel().isSelectedIndex(column);
}

/**
 * Returns true if the specified indices are in the valid range of rows
 * and columns and the cell at the specified position is selected.
 * @param row   the row being queried
 * @param column  the column being queried
 *
 * @return true if <code>row</code> and <code>column</code> are valid indices
 *              and the cell at index <code>(row, column)</code> is selected,
 *              where the first row and first column are at index 0
 */
/*public*/ bool isCellSelected(int row, int column) {
    if (!getRowSelectionAllowed() && !getColumnSelectionAllowed()) {
        return false;
    }
    return (!getRowSelectionAllowed() || isRowSelected(row)) &&
           (!getColumnSelectionAllowed() || isColumnSelected(column));
}

private void changeSelectionModel(ListSelectionModel sm, int index,
                                  bool toggle, bool extend, bool selected,
                                  int anchor, bool anchorSelected) {
    if (extend) {
        if (toggle) {
            if (anchorSelected) {
                sm.addSelectionInterval(anchor, index);
            } else {
                sm.removeSelectionInterval(anchor, index);
                // this is a Windows-only behavior that we want for file lists
                if (Boolean.TRUE == getClientProperty("Table.isFileList")) {
                    sm.addSelectionInterval(index, index);
                    sm.setAnchorSelectionIndex(anchor);
                }
            }
        }
        else {
            sm.setSelectionInterval(anchor, index);
        }
    }
    else {
        if (toggle) {
            if (selected) {
                sm.removeSelectionInterval(index, index);
            }
            else {
                sm.addSelectionInterval(index, index);
            }
        }
        else {
            sm.setSelectionInterval(index, index);
        }
    }
}

/**
 * Updates the selection models of the table, depending on the state of the
 * two flags: <code>toggle</code> and <code>extend</code>. Most changes
 * to the selection that are the result of keyboard or mouse events received
 * by the UI are channeled through this method so that the behavior may be
 * overridden by a subclass. Some UIs may need more functionality than
 * this method provides, such as when manipulating the lead for discontiguous
 * selection, and may not call into this method for some selection changes.
 * <p>
 * This implementation uses the following conventions:
 * <ul>
 * <li> <code>toggle</code>: <em>false</em>, <code>extend</code>: <em>false</em>.
 *      Clear the previous selection and ensure the new cell is selected.
 * <li> <code>toggle</code>: <em>false</em>, <code>extend</code>: <em>true</em>.
 *      Extend the previous selection from the anchor to the specified cell,
 *      clearing all other selections.
 * <li> <code>toggle</code>: <em>true</em>, <code>extend</code>: <em>false</em>.
 *      If the specified cell is selected, deselect it. If it is not selected, select it.
 * <li> <code>toggle</code>: <em>true</em>, <code>extend</code>: <em>true</em>.
 *      Apply the selection state of the anchor to all cells between it and the
 *      specified cell.
 * </ul>
 * @param  rowIndex   affects the selection at <code>row</code>
 * @param  columnIndex  affects the selection at <code>column</code>
 * @param  toggle  see description above
 * @param  extend  if true, extend the current selection
 *
 * @since 1.3
 */
/*public*/ void changeSelection(int rowIndex, int columnIndex, bool toggle, bool extend) {
    ListSelectionModel rsm = getSelectionModel();
    ListSelectionModel csm = getColumnModel().getSelectionModel();

    int anchorRow = getAdjustedIndex(rsm.getAnchorSelectionIndex(), true);
    int anchorCol = getAdjustedIndex(csm.getAnchorSelectionIndex(), false);

    bool anchorSelected = true;

    if (anchorRow == -1) {
        if (getRowCount() > 0) {
            anchorRow = 0;
        }
        anchorSelected = false;
    }

    if (anchorCol == -1) {
        if (getColumnCount() > 0) {
            anchorCol = 0;
        }
        anchorSelected = false;
    }

    // Check the selection here rather than in each selection model.
    // This is significant in cell selection mode if we are supposed
    // to be toggling the selection. In this case it is better to
    // ensure that the cell's selection state will indeed be changed.
    // If this were done in the code for the selection model it
    // might leave a cell in selection state if the row was
    // selected but the column was not - as it would toggle them both.
    bool selected = isCellSelected(rowIndex, columnIndex);
    anchorSelected = anchorSelected && isCellSelected(anchorRow, anchorCol);

    changeSelectionModel(csm, columnIndex, toggle, extend, selected,
                         anchorCol, anchorSelected);
    changeSelectionModel(rsm, rowIndex, toggle, extend, selected,
                         anchorRow, anchorSelected);

    // Scroll after changing the selection as blit scrolling is immediate,
    // so that if we cause the repaint after the scroll we end up painting
    // everything!
    if (getAutoscrolls()) {
        Rectangle cellRect = getCellRect(rowIndex, columnIndex, false);
        if (cellRect != NULL) {
            scrollRectToVisible(cellRect);
        }
    }
}

/**
 * Returns the foreground color for selected cells.
 *
 * @return the <code>Color</code> object for the foreground property
 * @see #setSelectionForeground
 * @see #setSelectionBackground
 */
/*public*/ Color getSelectionForeground() {
    return selectionForeground;
}

/**
 * Sets the foreground color for selected cells.  Cell renderers
 * can use this color to render text and graphics for selected
 * cells.
 * <p>
 * The default value of this property is defined by the look
 * and feel implementation.
 * <p>
 * This is a <a href="http://docs.oracle.com/javase/tutorial/javabeans/writing/properties.html">JavaBeans</a> bound property.
 *
 * @param selectionForeground  the <code>Color</code> to use in the foreground
 *                             for selected list items
 * @see #getSelectionForeground
 * @see #setSelectionBackground
 * @see #setForeground
 * @see #setBackground
 * @see #setFont
 * @beaninfo
 *       bound: true
 * description: A default foreground color for selected cells.
 */
/*public*/ void setSelectionForeground(Color selectionForeground) {
    Color old = this->selectionForeground;
    this->selectionForeground = selectionForeground;
    firePropertyChange("selectionForeground", old, selectionForeground);
    repaint();
}

/**
 * Returns the background color for selected cells.
 *
 * @return the <code>Color</code> used for the background of selected list items
 * @see #setSelectionBackground
 * @see #setSelectionForeground
 */
/*public*/ Color getSelectionBackground() {
    return selectionBackground;
}

/**
 * Sets the background color for selected cells.  Cell renderers
 * can use this color to the fill selected cells.
 * <p>
 * The default value of this property is defined by the look
 * and feel implementation.
 * <p>
 * This is a <a href="http://docs.oracle.com/javase/tutorial/javabeans/writing/properties.html">JavaBeans</a> bound property.
 *
 * @param selectionBackground  the <code>Color</code> to use for the background
 *                             of selected cells
 * @see #getSelectionBackground
 * @see #setSelectionForeground
 * @see #setForeground
 * @see #setBackground
 * @see #setFont
 * @beaninfo
 *       bound: true
 * description: A default background color for selected cells.
 */
/*public*/ void setSelectionBackground(Color selectionBackground) {
    Color old = this->selectionBackground;
    this->selectionBackground = selectionBackground;
    firePropertyChange("selectionBackground", old, selectionBackground);
    repaint();
}

/**
 * Returns the <code>TableColumn</code> object for the column in the table
 * whose identifier is equal to <code>identifier</code>, when compared using
 * <code>equals</code>.
 *
 * @return  the <code>TableColumn</code> object that matches the identifier
 * @exception IllegalArgumentException      if <code>identifier</code> is <code>NULL</code> or no <code>TableColumn</code> has this identifier
 *
 * @param   identifier                      the identifier object
 */
/*public*/ TableColumn getColumn(Object identifier) {
    TableColumnModel cm = getColumnModel();
    int columnIndex = cm.getColumnIndex(identifier);
    return cm.getColumn(columnIndex);
}
#endif
//
// Informally implement the TableModel interface.
//

/**
 * Maps the index of the column in the view at
 * <code>viewColumnIndex</code> to the index of the column
 * in the table model.  Returns the index of the corresponding
 * column in the model.  If <code>viewColumnIndex</code>
 * is less than zero, returns <code>viewColumnIndex</code>.
 *
 * @param   viewColumnIndex     the index of the column in the view
 * @return  the index of the corresponding column in the model
 *
 * @see #convertColumnIndexToView
 */
/*public*/ int JTable::convertColumnIndexToModel(int viewColumnIndex) {
//    return SwingUtilities2.convertColumnIndexToModel(
//            getColumnModel(), viewColumnIndex);
     // TODO
     return viewColumnIndex;
}

/**
 * Maps the index of the column in the table model at
 * <code>modelColumnIndex</code> to the index of the column
 * in the view.  Returns the index of the
 * corresponding column in the view; returns -1 if this column is not
 * being displayed.  If <code>modelColumnIndex</code> is less than zero,
 * returns <code>modelColumnIndex</code>.
 *
 * @param   modelColumnIndex     the index of the column in the model
 * @return   the index of the corresponding column in the view
 *
 * @see #convertColumnIndexToModel
 */
/*public*/ int JTable::convertColumnIndexToView(int modelColumnIndex) {
//    return SwingUtilities2.convertColumnIndexToView(
//            getColumnModel(), modelColumnIndex);
     // TODO
     return modelColumnIndex;
}

/**
 * Maps the index of the row in terms of the
 * <code>TableModel</code> to the view.  If the contents of the
 * model are not sorted the model and view indices are the same.
 *
 * @param modelRowIndex the index of the row in terms of the model
 * @return the index of the corresponding row in the view, or -1 if
 *         the row isn't visible
 * @throws IndexOutOfBoundsException if sorting is enabled and passed an
 *         index outside the number of rows of the <code>TableModel</code>
 * @see javax.swing.table.TableRowSorter
 * @since 1.6
 */
/*public*/ int JTable::convertRowIndexToView(int modelRowIndex) {
    RowSorter* sorter = getRowSorter();
    if (sorter != NULL) {
        return sorter->convertRowIndexToView(modelRowIndex);
    }
    return modelRowIndex;
}
#if 0
/**
 * Maps the index of the row in terms of the view to the
 * underlying <code>TableModel</code>.  If the contents of the
 * model are not sorted the model and view indices are the same.
 *
 * @param viewRowIndex the index of the row in the view
 * @return the index of the corresponding row in the model
 * @throws IndexOutOfBoundsException if sorting is enabled and passed an
 *         index outside the range of the <code>JTable</code> as
 *         determined by the method <code>getRowCount</code>
 * @see javax.swing.table.TableRowSorter
 * @see #getRowCount
 * @since 1.6
 */
/*public*/ int JTable::convertRowIndexToModel(int viewRowIndex) {
    RowSorter* sorter = getRowSorter();
    if (sorter != NULL) {
        return sorter->convertRowIndexToModel(viewRowIndex);
    }
    return viewRowIndex;
}
#endif
/**
 * Returns the number of rows that can be shown in the
 * <code>JTable</code>, given unlimited space.  If a
 * <code>RowSorter</code> with a filter has been specified, the
 * number of rows returned may differ from that of the underlying
 * <code>TableModel</code>.
 *
 * @return the number of rows shown in the <code>JTable</code>
 * @see #getColumnCount
 */
/*public*/ int JTable::getRowCount() {
    RowSorter* sorter = getRowSorter();
    if (sorter != NULL) {
        return sorter->getViewRowCount();
    }
    return getModel()->rowCount();
}

/**
 * Returns the number of columns in the column model. Note that this may
 * be different from the number of columns in the table model.
 *
 * @return  the number of columns in the table
 * @see #getRowCount
 * @see #removeColumn
 */
/*public*/ int JTable::getColumnCount() {
    return getColumnModel()->getColumnCount();
}

/**
 * Returns the name of the column appearing in the view at
 * column position <code>column</code>.
 *
 * @param  column    the column in the view being queried
 * @return the name of the column at position <code>column</code>
                    in the view where the first column is column 0
 */
/*public*/ QString JTable::getColumnName(int column) {
    AbstractTableModel* model =  (AbstractTableModel*)getModel();
    if(qobject_cast<QSortFilterProxyModel*>(model))
    {
     QSortFilterProxyModel* sorter =((QSortFilterProxyModel*)model);
     return ((AbstractTableModel*)sorter->sourceModel())->getColumnName(convertColumnIndexToModel(column));
    }
    return ((AbstractTableModel*)getModel())->getColumnName(convertColumnIndexToModel(column));
}
#if 0
/**
 * Returns the type of the column appearing in the view at
 * column position <code>column</code>.
 *
 * @param   column   the column in the view being queried
 * @return the type of the column at position <code>column</code>
 *          in the view where the first column is column 0
 */
/*public*/ Class<?> getColumnClass(int column) {
    return getModel().getColumnClass(convertColumnIndexToModel(column));
}
#endif
/**
 * Returns the cell value at <code>row</code> and <code>column</code>.
 * <p>
 * <b>Note</b>: The column is specified in the table view's display
 *              order, and not in the <code>TableModel</code>'s column
 *              order.  This is an important distinction because as the
 *              user rearranges the columns in the table,
 *              the column at a given index in the view will change->
 *              Meanwhile the user's actions never affect the model's
 *              column ordering.
 *
 * @param   row             the row whose value is to be queried
 * @param   column          the column whose value is to be queried
 * @return  the Object at the specified cell
 */
/*public*/ QVariant JTable::getValueAt(int row, int column) {
    return getModel()->data(getModel()->index(convertRowIndexToModel(row),
                                 convertColumnIndexToModel(column),QModelIndex()));
}
#if 0
/**
 * Sets the value for the cell in the table model at <code>row</code>
 * and <code>column</code>.
 * <p>
 * <b>Note</b>: The column is specified in the table view's display
 *              order, and not in the <code>TableModel</code>'s column
 *              order.  This is an important distinction because as the
 *              user rearranges the columns in the table,
 *              the column at a given index in the view will change->
 *              Meanwhile the user's actions never affect the model's
 *              column ordering.
 *
 * <code>aValue</code> is the new value.
 *
 * @param   aValue          the new value
 * @param   row             the row of the cell to be changed
 * @param   column          the column of the cell to be changed
 * @see #getValueAt
 */
/*public*/ void setValueAt(Object aValue, int row, int column) {
    getModel().setValueAt(aValue, convertRowIndexToModel(row),
                          convertColumnIndexToModel(column));
}

/**
 * Returns true if the cell at <code>row</code> and <code>column</code>
 * is editable.  Otherwise, invoking <code>setValueAt</code> on the cell
 * will have no effect.
 * <p>
 * <b>Note</b>: The column is specified in the table view's display
 *              order, and not in the <code>TableModel</code>'s column
 *              order.  This is an important distinction because as the
 *              user rearranges the columns in the table,
 *              the column at a given index in the view will change->
 *              Meanwhile the user's actions never affect the model's
 *              column ordering.
 *
 *
 * @param   row      the row whose value is to be queried
 * @param   column   the column whose value is to be queried
 * @return  true if the cell is editable
 * @see #setValueAt
 */
/*public*/ bool isCellEditable(int row, int column) {
    return getModel().isCellEditable(convertRowIndexToModel(row),
                                     convertColumnIndexToModel(column));
}
#endif
//
// Adding and removing columns in the view
//

/**
 *  Appends <code>aColumn</code> to the end of the array of columns held by
 *  this <code>JTable</code>'s column model.
 *  If the column name of <code>aColumn</code> is <code>NULL</code>,
 *  sets the column name of <code>aColumn</code> to the name
 *  returned by <code>getModel().getColumnName()</code>.
 *  <p>
 *  To add a column to this <code>JTable</code> to display the
 *  <code>modelColumn</code>'th column of data in the model with a
 *  given <code>width</code>, <code>cellRenderer</code>,
 *  and <code>cellEditor</code> you can use:
 *  <pre>
 *
 *      addColumn(new TableColumn(modelColumn, width, cellRenderer, cellEditor));
 *
 *  </pre>
 *  [Any of the <code>TableColumn</code> constructors can be used
 *  instead of this one.]
 *  The model column number is stored inside the <code>TableColumn</code>
 *  and is used during rendering and editing to locate the appropriates
 *  data values in the model. The model column number does not change
 *  when columns are reordered in the view.
 *
 *  @param  aColumn         the <code>TableColumn</code> to be added
 *  @see    #removeColumn
 */
/*public*/ void JTable::addColumn(TableColumn* aColumn)
{
 if (aColumn->getHeaderValue() == QVariant())
 {
  int modelColumn = aColumn->getModelIndex();
  QString columnName = getModel()->/*getColumnName(modelColumn)*/headerData(modelColumn, Qt::Horizontal, Qt::DisplayRole).toString();
  aColumn->setHeaderValue(columnName);
 }
 getColumnModel()->addColumn(aColumn);
}

/**
 *  Removes <code>aColumn</code> from this <code>JTable</code>'s
 *  array of columns.  Note: this method does not remove the column
 *  of data from the model; it just removes the <code>TableColumn</code>
 *  that was responsible for displaying it.
 *
 *  @param  aColumn         the <code>TableColumn</code> to be removed
 *  @see    #addColumn
 */
/*public*/ void JTable::removeColumn(TableColumn* aColumn)
{
 getColumnModel()->removeColumn(aColumn);
}

/**
 * Moves the column <code>column</code> to the position currently
 * occupied by the column <code>targetColumn</code> in the view.
 * The old column at <code>targetColumn</code> is
 * shifted left or right to make room.
 *
 * @param   column                  the index of column to be moved
 * @param   targetColumn            the new index of the column
 */
/*public*/ void JTable::moveColumn(int column, int targetColumn)
{
 getColumnModel()->moveColumn(column, targetColumn);
}
#if 0
//
// Cover methods for various models and helper methods
//

/**
 * Returns the index of the column that <code>point</code> lies in,
 * or -1 if the result is not in the range
 * [0, <code>getColumnCount()</code>-1].
 *
 * @param   point   the location of interest
 * @return  the index of the column that <code>point</code> lies in,
 *          or -1 if the result is not in the range
 *          [0, <code>getColumnCount()</code>-1]
 * @see     #rowAtPoint
 */
/*public*/ int columnAtPoint(Point point) {
    int x = point.x;
    if( !getComponentOrientation().isLeftToRight() ) {
        x = getWidth() - x - 1;
    }
    return getColumnModel().getColumnIndexAtX(x);
}
#endif
/**
 * Returns the index of the row that <code>point</code> lies in,
 * or -1 if the result is not in the range
 * [0, <code>getRowCount()</code>-1].
 *
 * @param   point   the location of interest
 * @return  the index of the row that <code>point</code> lies in,
 *          or -1 if the result is not in the range
 *          [0, <code>getRowCount()</code>-1]
 * @see     #columnAtPoint
 */
/*public*/ int JTable::rowAtPoint(QPoint point) {
//    int y = point.y;
//    int result = (rowModel == NULL) ?  y/getRowHeight() : rowModel.getIndex(y);
//    if (result < 0) {
//        return -1;
//    }
//    else if (result >= getRowCount()) {
//        return -1;
//    }
//    else {
//        return result;
//    }
 if(model() != NULL)
 {
  QModelIndex index = indexAt(point);
  if(index.isValid())
   return index.row();
 }
 return  -1;
}
#if 0
/**
 * Returns a rectangle for the cell that lies at the intersection of
 * <code>row</code> and <code>column</code>.
 * If <code>includeSpacing</code> is true then the value returned
 * has the full height and width of the row and column
 * specified. If it is false, the returned rectangle is inset by the
 * intercell spacing to return the true bounds of the rendering or
 * editing component as it will be set during rendering.
 * <p>
 * If the column index is valid but the row index is less
 * than zero the method returns a rectangle with the
 * <code>y</code> and <code>height</code> values set appropriately
 * and the <code>x</code> and <code>width</code> values both set
 * to zero. In general, when either the row or column indices indicate a
 * cell outside the appropriate range, the method returns a rectangle
 * depicting the closest edge of the closest cell that is within
 * the table's range. When both row and column indices are out
 * of range the returned rectangle covers the closest
 * point of the closest cell.
 * <p>
 * In all cases, calculations that use this method to calculate
 * results along one axis will not fail because of anomalies in
 * calculations along the other axis. When the cell is not valid
 * the <code>includeSpacing</code> parameter is ignored.
 *
 * @param   row                   the row index where the desired cell
 *                                is located
 * @param   column                the column index where the desired cell
 *                                is located in the display; this is not
 *                                necessarily the same as the column index
 *                                in the data model for the table; the
 *                                {@link #convertColumnIndexToView(int)}
 *                                method may be used to convert a data
 *                                model column index to a display
 *                                column index
 * @param   includeSpacing        if false, return the true cell bounds -
 *                                computed by subtracting the intercell
 *                                spacing from the height and widths of
 *                                the column and row models
 *
 * @return  the rectangle containing the cell at location
 *          <code>row</code>,<code>column</code>
 * @see #getIntercellSpacing
 */
/*public*/ Rectangle getCellRect(int row, int column, bool includeSpacing) {
    Rectangle r = new Rectangle();
    bool valid = true;
    if (row < 0) {
        // y = height = 0;
        valid = false;
    }
    else if (row >= getRowCount()) {
        r.y = getHeight();
        valid = false;
    }
    else {
        r.height = getRowHeight(row);
        r.y = (rowModel == NULL) ? row * r.height : rowModel.getPosition(row);
    }

    if (column < 0) {
        if( !getComponentOrientation().isLeftToRight() ) {
            r.x = getWidth();
        }
        // otherwise, x = width = 0;
        valid = false;
    }
    else if (column >= getColumnCount()) {
        if( getComponentOrientation().isLeftToRight() ) {
            r.x = getWidth();
        }
        // otherwise, x = width = 0;
        valid = false;
    }
    else {
        TableColumnModel cm = getColumnModel();
        if( getComponentOrientation().isLeftToRight() ) {
            for(int i = 0; i < column; i++) {
                r.x += cm.getColumn(i).getWidth();
            }
        } else {
            for(int i = cm.getColumnCount()-1; i > column; i--) {
                r.x += cm.getColumn(i).getWidth();
            }
        }
        r.width = cm.getColumn(column).getWidth();
    }

    if (valid && !includeSpacing) {
        // Bound the margins by their associated dimensions to prevent
        // returning bounds with negative dimensions.
        int rm = Math.min(getRowMargin(), r.height);
        int cm = Math.min(getColumnModel().getColumnMargin(), r.width);
        // This is not the same as grow(), it rounds differently.
        r.setBounds(r.x + cm/2, r.y + rm/2, r.width - cm, r.height - rm);
    }
    return r;
}

private int viewIndexForColumn(TableColumn aColumn) {
    TableColumnModel cm = getColumnModel();
    for (int column = 0; column < cm.getColumnCount(); column++) {
        if (cm.getColumn(column) == aColumn) {
            return column;
        }
    }
    return -1;
}

/**
 * Causes this table to lay out its rows and columns.  Overridden so
 * that columns can be resized to accommodate a change in the size of
 * a containing parent.
 * Resizes one or more of the columns in the table
 * so that the total width of all of this <code>JTable</code>'s
 * columns is equal to the width of the table.
 * <p>
 * Before the layout begins the method gets the
 * <code>resizingColumn</code> of the <code>tableHeader</code>.
 * When the method is called as a result of the resizing of an enclosing window,
 * the <code>resizingColumn</code> is <code>NULL</code>. This means that resizing
 * has taken place "outside" the <code>JTable</code> and the change -
 * or "delta" - should be distributed to all of the columns regardless
 * of this <code>JTable</code>'s automatic resize mode.
 * <p>
 * If the <code>resizingColumn</code> is not <code>NULL</code>, it is one of
 * the columns in the table that has changed size rather than
 * the table itself. In this case the auto-resize modes govern
 * the way the extra (or deficit) space is distributed
 * amongst the available columns.
 * <p>
 * The modes are:
 * <ul>
 * <li>  AUTO_RESIZE_OFF: Don't automatically adjust the column's
 * widths at all. Use a horizontal scrollbar to accommodate the
 * columns when their sum exceeds the width of the
 * <code>Viewport</code>.  If the <code>JTable</code> is not
 * enclosed in a <code>JScrollPane</code> this may
 * leave parts of the table invisible.
 * <li>  AUTO_RESIZE_NEXT_COLUMN: Use just the column after the
 * resizing column. This results in the "boundary" or divider
 * between adjacent cells being independently adjustable.
 * <li>  AUTO_RESIZE_SUBSEQUENT_COLUMNS: Use all columns after the
 * one being adjusted to absorb the changes.  This is the
 * default behavior.
 * <li>  AUTO_RESIZE_LAST_COLUMN: Automatically adjust the
 * size of the last column only. If the bounds of the last column
 * prevent the desired size from being allocated, set the
 * width of the last column to the appropriate limit and make
 * no further adjustments.
 * <li>  AUTO_RESIZE_ALL_COLUMNS: Spread the delta amongst all the columns
 * in the <code>JTable</code>, including the one that is being
 * adjusted.
 * </ul>
 * <p>
 * <b>Note:</b> When a <code>JTable</code> makes adjustments
 *   to the widths of the columns it respects their minimum and
 *   maximum values absolutely.  It is therefore possible that,
 *   even after this method is called, the total width of the columns
 *   is still not equal to the width of the table. When this happens
 *   the <code>JTable</code> does not put itself
 *   in AUTO_RESIZE_OFF mode to bring up a scroll bar, or break other
 *   commitments of its current auto-resize mode -- instead it
 *   allows its bounds to be set larger (or smaller) than the total of the
 *   column minimum or maximum, meaning, either that there
 *   will not be enough room to display all of the columns, or that the
 *   columns will not fill the <code>JTable</code>'s bounds.
 *   These respectively, result in the clipping of some columns
 *   or an area being painted in the <code>JTable</code>'s
 *   background color during painting.
 * <p>
 *   The mechanism for distributing the delta amongst the available
 *   columns is provided in a private method in the <code>JTable</code>
 *   class:
 * <pre>
 *   adjustSizes(long targetSize, final Resizable3 r, bool inverse)
 * </pre>
 *   an explanation of which is provided in the following section.
 *   <code>Resizable3</code> is a private
 *   interface that allows any data structure containing a collection
 *   of elements with a size, preferred size, maximum size and minimum size
 *   to have its elements manipulated by the algorithm.
 *
 * <H3> Distributing the delta </H3>
 *
 * <H4> Overview </H4>
 * <P>
 * Call "DELTA" the difference between the target size and the
 * sum of the preferred sizes of the elements in r. The individual
 * sizes are calculated by taking the original preferred
 * sizes and adding a share of the DELTA - that share being based on
 * how far each preferred size is from its limiting bound (minimum or
 * maximum).
 *
 * <H4>Definition</H4>
 * <P>
 * Call the individual constraints min[i], max[i], and pref[i].
 * <p>
 * Call their respective sums: MIN, MAX, and PREF.
 * <p>
 * Each new size will be calculated using:
 *
 * <pre>
 *          size[i] = pref[i] + delta[i]
 * </pre>
 * where each individual delta[i] is calculated according to:
 * <p>
 * If (DELTA &lt; 0) we are in shrink mode where:
 *
 * <PRE>
 *                        DELTA
 *          delta[i] = ------------ * (pref[i] - min[i])
 *                     (PREF - MIN)
 * </PRE>
 * If (DELTA &gt; 0) we are in expand mode where:
 *
 * <PRE>
 *                        DELTA
 *          delta[i] = ------------ * (max[i] - pref[i])
 *                      (MAX - PREF)
 * </PRE>
 * <P>
 * The overall effect is that the total size moves that same percentage,
 * k, towards the total minimum or maximum and that percentage guarantees
 * accommodation of the required space, DELTA.
 *
 * <H4>Details</H4>
 * <P>
 * Naive evaluation of the formulae presented here would be subject to
 * the aggregated rounding errors caused by doing this operation in finite
 * precision (using ints). To deal with this, the multiplying factor above,
 * is constantly recalculated and this takes account of the rounding
 * errors in the previous iterations. The result is an algorithm that
 * produces a set of integers whose values exactly sum to the supplied
 * <code>targetSize</code>, and does so by spreading the rounding
 * errors evenly over the given elements.
 *
 * <H4>When the MAX and MIN bounds are hit</H4>
 * <P>
 * When <code>targetSize</code> is outside the [MIN, MAX] range,
 * the algorithm sets all sizes to their appropriate limiting value
 * (maximum or minimum).
 *
 */
/*public*/ void doLayout() {
    TableColumn resizingColumn = getResizingColumn();
    if (resizingColumn == NULL) {
        setWidthsFromPreferredWidths(false);
    }
    else {
        // JTable behaves like a layout manger - but one in which the
        // user can come along and dictate how big one of the children
        // (columns) is supposed to be.

        // A column has been resized and JTable may need to distribute
        // any overall delta to other columns, according to the resize mode.
        int columnIndex = viewIndexForColumn(resizingColumn);
        int delta = getWidth() - getColumnModel().getTotalColumnWidth();
        accommodateDelta(columnIndex, delta);
        delta = getWidth() - getColumnModel().getTotalColumnWidth();

        // If the delta cannot be completely accomodated, then the
        // resizing column will have to take any remainder. This means
        // that the column is not being allowed to take the requested
        // width. This happens under many circumstances: For example,
        // AUTO_RESIZE_NEXT_COLUMN specifies that any delta be distributed
        // to the column after the resizing column. If one were to attempt
        // to resize the last column of the table, there would be no
        // columns after it, and hence nowhere to distribute the delta.
        // It would then be given entirely back to the resizing column,
        // preventing it from changing size.
        if (delta != 0) {
            resizingColumn.setWidth(resizingColumn.getWidth() + delta);
        }

        // At this point the JTable has to work out what preferred sizes
        // would have resulted in the layout the user has chosen.
        // Thereafter, during window resizing etc. it has to work off
        // the preferred sizes as usual - the idea being that, whatever
        // the user does, everything stays in synch and things don't jump
        // around.
        setWidthsFromPreferredWidths(true);
    }

    super.doLayout();
}

private TableColumn getResizingColumn() {
    return (tableHeader == NULL) ? NULL
                                 : tableHeader.getResizingColumn();
}

/**
 * Sizes the table columns to fit the available space.
 * @deprecated As of Swing version 1.0.3,
 * replaced by <code>doLayout()</code>.
 * @see #doLayout
 */
@Deprecated
/*public*/ void sizeColumnsToFit(bool lastColumnOnly) {
    int oldAutoResizeMode = autoResizeMode;
    setAutoResizeMode(lastColumnOnly ? AUTO_RESIZE_LAST_COLUMN
                                     : AUTO_RESIZE_ALL_COLUMNS);
    sizeColumnsToFit(-1);
    setAutoResizeMode(oldAutoResizeMode);
}

/**
 * Obsolete as of Java 2 platform v1.4.  Please use the
 * <code>doLayout()</code> method instead.
 * @param resizingColumn    the column whose resizing made this adjustment
 *                          necessary or -1 if there is no such column
 * @see  #doLayout
 */
/*public*/ void sizeColumnsToFit(int resizingColumn) {
    if (resizingColumn == -1) {
        setWidthsFromPreferredWidths(false);
    }
    else {
        if (autoResizeMode == AUTO_RESIZE_OFF) {
            TableColumn aColumn = getColumnModel().getColumn(resizingColumn);
            aColumn.setPreferredWidth(aColumn.getWidth());
        }
        else {
            int delta = getWidth() - getColumnModel().getTotalColumnWidth();
            accommodateDelta(resizingColumn, delta);
            setWidthsFromPreferredWidths(true);
        }
    }
}

private void setWidthsFromPreferredWidths(final bool inverse) {
    int totalWidth     = getWidth();
    int totalPreferred = getPreferredSize().width;
    int target = !inverse ? totalWidth : totalPreferred;

    final TableColumnModel cm = columnModel;
    Resizable3 r = new Resizable3() {
        /*public*/ int  getElementCount()      { return cm.getColumnCount(); }
        /*public*/ int  getLowerBoundAt(int i) { return cm.getColumn(i).getMinWidth(); }
        /*public*/ int  getUpperBoundAt(int i) { return cm.getColumn(i).getMaxWidth(); }
        /*public*/ int  getMidPointAt(int i)  {
            if (!inverse) {
                return cm.getColumn(i).getPreferredWidth();
            }
            else {
                return cm.getColumn(i).getWidth();
            }
        }
        /*public*/ void setSizeAt(int s, int i) {
            if (!inverse) {
                cm.getColumn(i).setWidth(s);
            }
            else {
                cm.getColumn(i).setPreferredWidth(s);
            }
        }
    };

    adjustSizes(target, r, inverse);
}


// Distribute delta over columns, as indicated by the autoresize mode.
private void accommodateDelta(int resizingColumnIndex, int delta) {
    int columnCount = getColumnCount();
    int from = resizingColumnIndex;
    int to;

    // Use the mode to determine how to absorb the changes.
    switch(autoResizeMode) {
        case AUTO_RESIZE_NEXT_COLUMN:
            from = from + 1;
            to = Math.min(from + 1, columnCount); break;
        case AUTO_RESIZE_SUBSEQUENT_COLUMNS:
            from = from + 1;
            to = columnCount; break;
        case AUTO_RESIZE_LAST_COLUMN:
            from = columnCount - 1;
            to = from + 1; break;
        case AUTO_RESIZE_ALL_COLUMNS:
            from = 0;
            to = columnCount; break;
        default:
            return;
    }

    final int start = from;
    final int end = to;
    final TableColumnModel cm = columnModel;
    Resizable3 r = new Resizable3() {
        /*public*/ int  getElementCount()       { return end-start; }
        /*public*/ int  getLowerBoundAt(int i)  { return cm.getColumn(i+start).getMinWidth(); }
        /*public*/ int  getUpperBoundAt(int i)  { return cm.getColumn(i+start).getMaxWidth(); }
        /*public*/ int  getMidPointAt(int i)    { return cm.getColumn(i+start).getWidth(); }
        /*public*/ void setSizeAt(int s, int i) {        cm.getColumn(i+start).setWidth(s); }
    };

    int totalWidth = 0;
    for(int i = from; i < to; i++) {
        TableColumn aColumn = columnModel.getColumn(i);
        int input = aColumn.getWidth();
        totalWidth = totalWidth + input;
    }

    adjustSizes(totalWidth + delta, r, false);
}

private interface Resizable2 {
    /*public*/ int  getElementCount();
    /*public*/ int  getLowerBoundAt(int i);
    /*public*/ int  getUpperBoundAt(int i);
    /*public*/ void setSizeAt(int newSize, int i);
}

private interface Resizable3 extends Resizable2 {
    /*public*/ int  getMidPointAt(int i);
}


private void adjustSizes(long target, final Resizable3 r, bool inverse) {
    int N = r.getElementCount();
    long totalPreferred = 0;
    for(int i = 0; i < N; i++) {
        totalPreferred += r.getMidPointAt(i);
    }
    Resizable2 s;
    if ((target < totalPreferred) == !inverse) {
        s = new Resizable2() {
            /*public*/ int  getElementCount()      { return r.getElementCount(); }
            /*public*/ int  getLowerBoundAt(int i) { return r.getLowerBoundAt(i); }
            /*public*/ int  getUpperBoundAt(int i) { return r.getMidPointAt(i); }
            /*public*/ void setSizeAt(int newSize, int i) { r.setSizeAt(newSize, i); }

        };
    }
    else {
        s = new Resizable2() {
            /*public*/ int  getElementCount()      { return r.getElementCount(); }
            /*public*/ int  getLowerBoundAt(int i) { return r.getMidPointAt(i); }
            /*public*/ int  getUpperBoundAt(int i) { return r.getUpperBoundAt(i); }
            /*public*/ void setSizeAt(int newSize, int i) { r.setSizeAt(newSize, i); }

        };
    }
    adjustSizes(target, s, !inverse);
}

private void adjustSizes(long target, Resizable2 r, bool limitToRange) {
    long totalLowerBound = 0;
    long totalUpperBound = 0;
    for(int i = 0; i < r.getElementCount(); i++) {
        totalLowerBound += r.getLowerBoundAt(i);
        totalUpperBound += r.getUpperBoundAt(i);
    }

    if (limitToRange) {
        target = Math.min(Math.max(totalLowerBound, target), totalUpperBound);
    }

    for(int i = 0; i < r.getElementCount(); i++) {
        int lowerBound = r.getLowerBoundAt(i);
        int upperBound = r.getUpperBoundAt(i);
        // Check for zero. This happens when the distribution of the delta
        // finishes early due to a series of "fixed" entries at the end.
        // In this case, lowerBound == upperBound, for all subsequent terms.
        int newSize;
        if (totalLowerBound == totalUpperBound) {
            newSize = lowerBound;
        }
        else {
            double f = (double)(target - totalLowerBound)/(totalUpperBound - totalLowerBound);
            newSize = (int)Math.round(lowerBound+f*(upperBound - lowerBound));
            // We'd need to round manually in an all integer version.
            // size[i] = (int)(((totalUpperBound - target) * lowerBound +
            //     (target - totalLowerBound) * upperBound)/(totalUpperBound-totalLowerBound));
        }
        r.setSizeAt(newSize, i);
        target -= newSize;
        totalLowerBound -= lowerBound;
        totalUpperBound -= upperBound;
    }
}

/**
 * Overrides <code>JComponent</code>'s <code>getToolTipText</code>
 * method in order to allow the renderer's tips to be used
 * if it has text set.
 * <p>
 * <b>Note:</b> For <code>JTable</code> to properly display
 * tooltips of its renderers
 * <code>JTable</code> must be a registered component with the
 * <code>ToolTipManager</code>.
 * This is done automatically in <code>initializeLocalVars</code>,
 * but if at a later point <code>JTable</code> is told
 * <code>setToolTipText(NULL)</code> it will unregister the table
 * component, and no tips from renderers will display anymore.
 *
 * @see JComponent#getToolTipText
 */
/*public*/ String getToolTipText(MouseEvent event) {
    String tip = NULL;
    Point p = event.getPoint();

    // Locate the renderer under the event location
    int hitColumnIndex = columnAtPoint(p);
    int hitRowIndex = rowAtPoint(p);

    if ((hitColumnIndex != -1) && (hitRowIndex != -1)) {
        TableCellRenderer renderer = getCellRenderer(hitRowIndex, hitColumnIndex);
        Component component = prepareRenderer(renderer, hitRowIndex, hitColumnIndex);

        // Now have to see if the component is a JComponent before
        // getting the tip
        if (component instanceof JComponent) {
            // Convert the event to the renderer's coordinate system
            Rectangle cellRect = getCellRect(hitRowIndex, hitColumnIndex, false);
            p.translate(-cellRect.x, -cellRect.y);
            MouseEvent newEvent = new MouseEvent(component, event.getID(),
                                      event.getWhen(), event.getModifiers(),
                                      p.x, p.y,
                                      event.getXOnScreen(),
                                      event.getYOnScreen(),
                                      event.getClickCount(),
                                      event.isPopupTrigger(),
                                      MouseEvent.NOBUTTON);

            tip = ((JComponent)component).getToolTipText(newEvent);
        }
    }

    // No tip from the renderer get our own tip
    if (tip == NULL)
        tip = getToolTipText();

    return tip;
}

//
// Editing Support
//

/**
 * Sets whether editors in this JTable get the keyboard focus
 * when an editor is activated as a result of the JTable
 * forwarding keyboard events for a cell.
 * By default, this property is false, and the JTable
 * retains the focus unless the cell is clicked.
 *
 * @param surrendersFocusOnKeystroke true if the editor should get the focus
 *          when keystrokes cause the editor to be
 *          activated
 *
 *
 * @see #getSurrendersFocusOnKeystroke
 * @since 1.4
 */
/*public*/ void setSurrendersFocusOnKeystroke(bool surrendersFocusOnKeystroke) {
    this->surrendersFocusOnKeystroke = surrendersFocusOnKeystroke;
}

/**
 * Returns true if the editor should get the focus
 * when keystrokes cause the editor to be activated
 *
 * @return  true if the editor should get the focus
 *          when keystrokes cause the editor to be
 *          activated
 *
 * @see #setSurrendersFocusOnKeystroke
 * @since 1.4
 */
/*public*/ bool getSurrendersFocusOnKeystroke() {
    return surrendersFocusOnKeystroke;
}

/**
 * Programmatically starts editing the cell at <code>row</code> and
 * <code>column</code>, if those indices are in the valid range, and
 * the cell at those indices is editable.
 * Note that this is a convenience method for
 * <code>editCellAt(int, int, NULL)</code>.
 *
 * @param   row                             the row to be edited
 * @param   column                          the column to be edited
 * @return  false if for any reason the cell cannot be edited,
 *                or if the indices are invalid
 */
/*public*/ bool editCellAt(int row, int column) {
    return editCellAt(row, column, NULL);
}

/**
 * Programmatically starts editing the cell at <code>row</code> and
 * <code>column</code>, if those indices are in the valid range, and
 * the cell at those indices is editable.
 * To prevent the <code>JTable</code> from
 * editing a particular table, column or cell value, return false from
 * the <code>isCellEditable</code> method in the <code>TableModel</code>
 * interface.
 *
 * @param   row     the row to be edited
 * @param   column  the column to be edited
 * @param   e       event to pass into <code>shouldSelectCell</code>;
 *                  note that as of Java 2 platform v1.2, the call to
 *                  <code>shouldSelectCell</code> is no longer made
 * @return  false if for any reason the cell cannot be edited,
 *                or if the indices are invalid
 */
/*public*/ bool editCellAt(int row, int column, EventObject e){
    if (cellEditor != NULL && !cellEditor.stopCellEditing()) {
        return false;
    }

    if (row < 0 || row >= getRowCount() ||
        column < 0 || column >= getColumnCount()) {
        return false;
    }

    if (!isCellEditable(row, column))
        return false;

    if (editorRemover == NULL) {
        KeyboardFocusManager fm =
            KeyboardFocusManager.getCurrentKeyboardFocusManager();
        editorRemover = new CellEditorRemover(fm);
        fm.addPropertyChangeListener("permanentFocusOwner", editorRemover);
    }

    TableCellEditor editor = getCellEditor(row, column);
    if (editor != NULL && editor.isCellEditable(e)) {
        editorComp = prepareEditor(editor, row, column);
        if (editorComp == NULL) {
            removeEditor();
            return false;
        }
        editorComp.setBounds(getCellRect(row, column, false));
        add(editorComp);
        editorComp.validate();
        editorComp.repaint();

        setCellEditor(editor);
        setEditingRow(row);
        setEditingColumn(column);
        editor.addCellEditorListener(this);

        return true;
    }
    return false;
}

/**
 * Returns true if a cell is being edited.
 *
 * @return  true if the table is editing a cell
 * @see     #editingColumn
 * @see     #editingRow
 */
/*public*/ bool isEditing() {
    return cellEditor != NULL;
}

/**
 * Returns the component that is handling the editing session.
 * If nothing is being edited, returns NULL.
 *
 * @return  Component handling editing session
 */
/*public*/ Component getEditorComponent() {
    return editorComp;
}

/**
 * Returns the index of the column that contains the cell currently
 * being edited.  If nothing is being edited, returns -1.
 *
 * @return  the index of the column that contains the cell currently
 *          being edited; returns -1 if nothing being edited
 * @see #editingRow
 */
/*public*/ int getEditingColumn() {
    return editingColumn;
}

/**
 * Returns the index of the row that contains the cell currently
 * being edited.  If nothing is being edited, returns -1.
 *
 * @return  the index of the row that contains the cell currently
 *          being edited; returns -1 if nothing being edited
 * @see #editingColumn
 */
/*public*/ int getEditingRow() {
    return editingRow;
}

//
// Managing TableUI
//

/**
 * Returns the L&amp;F object that renders this component.
 *
 * @return the <code>TableUI</code> object that renders this component
 */
/*public*/ TableUI getUI() {
    return (TableUI)ui;
}

/**
 * Sets the L&amp;F object that renders this component and repaints.
 *
 * @param ui  the TableUI L&amp;F object
 * @see UIDefaults#getUI
 * @beaninfo
 *        bound: true
 *       hidden: true
 *    attribute: visualUpdate true
 *  description: The UI object that implements the Component's LookAndFeel.
 */
/*public*/ void setUI(TableUI ui) {
    if (this->ui != ui) {
        super.setUI(ui);
        repaint();
    }
}

/**
 * Notification from the <code>UIManager</code> that the L&amp;F has changed.
 * Replaces the current UI object with the latest version from the
 * <code>UIManager</code>.
 *
 * @see JComponent#updateUI
 */
/*public*/ void updateUI() {
    // Update the UIs of the cell renderers, cell editors and header renderers.
    TableColumnModel cm = getColumnModel();
    for(int column = 0; column < cm.getColumnCount(); column++) {
        TableColumn aColumn = cm.getColumn(column);
        SwingUtilities.updateRendererOrEditorUI(aColumn.getCellRenderer());
        SwingUtilities.updateRendererOrEditorUI(aColumn.getCellEditor());
        SwingUtilities.updateRendererOrEditorUI(aColumn.getHeaderRenderer());
    }

    // Update the UIs of all the default renderers.
    Enumeration defaultRenderers = defaultRenderersByColumnClass.elements();
    while (defaultRenderers.hasMoreElements()) {
        SwingUtilities.updateRendererOrEditorUI(defaultRenderers.nextElement());
    }

    // Update the UIs of all the default editors.
    Enumeration defaultEditors = defaultEditorsByColumnClass.elements();
    while (defaultEditors.hasMoreElements()) {
        SwingUtilities.updateRendererOrEditorUI(defaultEditors.nextElement());
    }

    // Update the UI of the table header
    if (tableHeader != NULL && tableHeader.getParent() == NULL) {
        tableHeader.updateUI();
    }

    // Update UI applied to parent ScrollPane
    configureEnclosingScrollPaneUI();

    setUI((TableUI)UIManager.getUI(this));
}

/**
 * Returns the suffix used to construct the name of the L&amp;F class used to
 * render this component.
 *
 * @return the string "TableUI"
 * @see JComponent#getUIClassID
 * @see UIDefaults#getUI
 */
/*public*/ String getUIClassID() {
    return uiClassID;
}

#endif
//
// Managing models
//

/**
 * Sets the data model for this table to <code>newModel</code> and registers
 * with it for listener notifications from the new data model.
 *
 * @param   dataModel        the new data source for this table
 * @exception IllegalArgumentException      if <code>newModel</code> is <code>NULL</code>
 * @see     #getModel
 * @beaninfo
 *  bound: true
 *  description: The model that is the source of the data for this view.
 */
/*public*/ void JTable::setModel(QAbstractItemModel* dataModel)
{
 if (dataModel == NULL)
 {
  throw IllegalArgumentException("Cannot set a NULL TableModel");
 }
 if (this->dataModel != dataModel)
 {
  QAbstractItemModel* old = this->dataModel;
//  if (old != NULL)
//  {
//   old.removeTableModelListener(this);
//  }
  this->dataModel = dataModel;
  QTableView::setModel(dataModel);
  //dataModel.addTableModelListener(this);
  connect(this->dataModel, SIGNAL(columnsAboutToBeInserted(QModelIndex, int, int)),this, SLOT(On_columnsAboutToBeInserted(QModelIndex, int, int)));
//  TableModelEvent* evt;
//  tableChanged(evt = new TableModelEvent((TableModel*)dataModel, TableModelEvent::HEADER_ROW, TableModelEvent::HEADER_ROW));

  firePropertyChange("model", VPtr<QAbstractItemModel>::asQVariant(old), VPtr<QAbstractItemModel>::asQVariant(dataModel));

//  if (getAutoCreateRowSorter())
//  {
//   setRowSorter(new TableRowSorter<TableModel>(dataModel));
//  }
  if(dataModel->columnCount(QModelIndex()) >  columnModel->getColumnCount() )
  {
   for(int i = columnModel->getColumnCount(); i < dataModel->columnCount(QModelIndex()); i++)
    columnModel->addColumn(new TableColumn(i));
  }
  connect((DefaultTableColumnModel*)columnModel, SIGNAL(firePropertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
 }
}

void JTable::On_columnsAboutToBeInserted(QModelIndex, int from, int to)
{
log->debug(QString("Columns about to be inserted %1 %2 ").arg(from).arg(to));
}

/**
 * Returns the <code>TableModel</code> that provides the data displayed by this
 * <code>JTable</code>.
 *
 * @return  the <code>TableModel</code> that provides the data displayed by this <code>JTable</code>
 * @see     #setModel
 */
/*public*/ QAbstractItemModel* JTable::getModel()
{
 return dataModel;
}

/**
 * Sets the column model for this table to <code>newModel</code> and registers
 * for listener notifications from the new column model. Also sets
 * the column model of the <code>JTableHeader</code> to <code>columnModel</code>.
 *
 * @param   columnModel        the new data source for this table
 * @exception IllegalArgumentException      if <code>columnModel</code> is <code>NULL</code>
 * @see     #getColumnModel
 * @beaninfo
 *  bound: true
 *  description: The object governing the way columns appear in the view.
 */
/*public*/ void JTable::setColumnModel(TableColumnModel* columnModel)
{
 if (columnModel == NULL)
 {
  throw IllegalArgumentException("Cannot set a NULL ColumnModel");
 }
 TableColumnModel* old = this->columnModel;
 if (columnModel != old)
 {
  if (old != NULL)
  {
//   old.removeColumnModelListener(this);
  }
  this->columnModel = columnModel;
  connect((DefaultTableColumnModel*)columnModel, SIGNAL(firePropertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
//  columnModel.addColumnModelListener(this);

//  // Set the column model of the header as well.
//  if (tableHeader != NULL)
//  {
//   tableHeader.setColumnModel(columnModel);
//  }

  firePropertyChange("columnModel", VPtr<TableColumnModel>::asQVariant(old), VPtr<TableColumnModel>::asQVariant(columnModel));
        resizeAndRepaint();
 }
}

/**
 * Returns the <code>TableColumnModel</code> that contains all column information
 * of this table.
 *
 * @return  the object that provides the column state of the table
 * @see     #setColumnModel
 */
/*public*/ TableColumnModel* JTable::getColumnModel()
{
 return columnModel;
}

/*protected*/ void JTable::columnResized(int column, int oldWidth, int newWidth)
{
 if(columnModel)
 {
  TableColumn* tc = columnModel->getColumn(column);
  tc->setWidth(newWidth);
 }
}

/**
 * Sets the row selection model for this table to <code>newModel</code>
 * and registers for listener notifications from the new selection model.
 *
 * @param   newModel        the new selection model
 * @exception IllegalArgumentException      if <code>newModel</code> is <code>NULL</code>
 * @see     #getSelectionModel
 * @beaninfo
 *      bound: true
 *      description: The selection model for rows.
 */
/*public*/ void JTable::setSelectionModel(QItemSelectionModel* newModel) // QItemSelectionModel
{
 if (newModel == NULL)
 {
  throw  IllegalArgumentException("Cannot set a NULL SelectionModel");
 }
 if(!qobject_cast<DefaultListSelectionModel*>(newModel))
 {
  QTableView::setSelectionModel(newModel);
  return;
 }
 DefaultListSelectionModel* oldModel = _selectionModel;

 if (newModel != oldModel)
 {
  if (oldModel != NULL)
  {
//    oldModel.removeListSelectionListener(this);
  }

  _selectionModel = (DefaultListSelectionModel*)newModel;
//    newModel.addListSelectionListener(this);

  firePropertyChange("selectionModel", VPtr<QItemSelectionModel>::asQVariant(oldModel), VPtr<QItemSelectionModel>::asQVariant(newModel));
  update();
 }
}

/**
 * Returns the <code>ListSelectionModel</code> that is used to maintain row
 * selection state.
 *
 * @return  the object that provides row selection state, <code>NULL</code>
 *          if row selection is not allowed
 * @see     #setSelectionModel
 */
/*public*/ DefaultListSelectionModel *JTable::getSelectionModel() {
    return _selectionModel;
}
#if 0
//
// RowSorterListener
//

/**
 * <code>RowSorterListener</code> notification that the
 * <code>RowSorter</code> has changed in some way.
 *
 * @param e the <code>RowSorterEvent</code> describing the change
 * @throws NullPointerException if <code>e</code> is <code>NULL</code>
 * @since 1.6
 */
/*public*/ void sorterChanged(RowSorterEvent e) {
    if (e.getType() == RowSorterEvent.Type.SORT_ORDER_CHANGED) {
        JTableHeader header = getTableHeader();
        if (header != NULL) {
            header.repaint();
        }
    }
    else if (e.getType() == RowSorterEvent.Type.SORTED) {
        sorterChanged = true;
        if (!ignoreSortChange) {
            sortedTableChanged(e, NULL);
        }
    }
}

#endif
 /**
 * SortManager provides support for managing the selection and variable
 * row heights when sorting is enabled. This information is encapsulated
 * into a class to avoid bulking up JTable.
 */
 ///*private*/ /*final*/ class SortManager
 //{
 // RowSorter/*<? extends TableModel>*/* sorter;

 //// Selection, in terms of the model. This is lazily created
 //// as needed.
 //private ListSelectionModel modelSelection;
 //private int modelLeadIndex;
 //// Set to true while in the process of changing the selection.
 //// If this is true the selection change is ignored.
 //private boolean syncingSelection;
 //// Temporary cache of selection, in terms of model. This is only used
 //// if we don't need the full weight of modelSelection.
 //private int[] lastModelSelection;

 //// Heights of the rows in terms of the model.
 //private SizeSequence modelRowSizes;


 SortManager::SortManager(RowSorter/*<? extends TableModel>*/* sorter, JTable* jt) {
     this->sorter = sorter;
  this->jt  = jt;
  modelRowSizes = NULL;

     sorter->addRowSorterListener((RowSorterListener*)jt);
 }

 /**
  * Disposes any resources used by this SortManager.
  */
 /*public*/ void SortManager::dispose() {
     if (sorter != NULL) {
         sorter->removeRowSorterListener((RowSorterListener*)jt);
     }
 }

 /**
  * Sets the height for a row at a specified index.
  */
 /*public*/ void SortManager::setViewRowHeight(int viewIndex, int rowHeight)
 {
 #if 1
  if (modelRowSizes == NULL) {
      modelRowSizes = new SizeSequence(jt->getModel()->rowCount(),
                                       jt->getRowHeight(0));
  }
  modelRowSizes->setSize(jt->convertRowIndexToModel(viewIndex),rowHeight);
 #endif
 }

 /**
  * Invoked when the underlying model has completely changed.
  */
 /*public*/ void SortManager::allChanged() {
     modelLeadIndex = -1;
     modelSelection = NULL;
     modelRowSizes = NULL;
 }

 /**
  * Invoked when the selection, on the view, has changed.
  */
 /*public*/ void SortManager::viewSelectionChanged(ListSelectionEvent* /*e*/) {
     if (!syncingSelection && modelSelection != NULL) {
         modelSelection = NULL;
     }
 }

 /**
  * Invoked when either the table model has changed, or the RowSorter
  * has changed. This is invoked prior to notifying the sorter of the
  * change->
  */
 /*public*/ void SortManager::prepareForChange(RowSorterEvent* sortEvent,
                              ModelChange* change) {
     if (jt->getUpdateSelectionOnSort()) {
         cacheSelection(sortEvent, change);
     }
 }
/**
 * Updates the internal cache of the selection based on the change->
 */
/*private*/ void SortManager::cacheSelection(RowSorterEvent* sortEvent,
                            ModelChange* change) {
    if (sortEvent != NULL) {
        // sort order changed. If modelSelection is NULL and filtering
        // is enabled we need to cache the selection in terms of the
        // underlying model, this will allow us to correctly restore
        // the selection even if rows are filtered out.
        if (modelSelection == NULL &&
                sorter->getViewRowCount() != jt->getModel()->rowCount()) {
            modelSelection = new DefaultListSelectionModel((AbstractTableModel*)jt->getModel());
            DefaultListSelectionModel* viewSelection = (DefaultListSelectionModel*)jt->getSelectionModel();
            int min = viewSelection->getMinSelectionIndex();
            int max = viewSelection->getMaxSelectionIndex();
            int modelIndex;
            for (int viewIndex = min; viewIndex <= max; viewIndex++) {
                if (viewSelection->isSelectedIndex(viewIndex)) {
                    modelIndex = jt->convertRowIndexToModel(
                            sortEvent, viewIndex);
                    if (modelIndex != -1) {
                        modelSelection->addSelectionInterval(
                            modelIndex, modelIndex);
                    }
                }
            }
            modelIndex = jt->convertRowIndexToModel(sortEvent,
                    viewSelection->getLeadSelectionIndex());
//            SwingUtilities2.setLeadAnchorWithoutSelection(
//                    modelSelection, modelIndex, modelIndex);
        } else if (modelSelection == NULL) {
            // Sorting changed, haven't cached selection in terms
            // of model and no filtering. Temporarily cache selection.
            cacheModelSelection(sortEvent);
        }
    } else if (change->allRowsChanged) {
        // All the rows have changed, chuck any cached selection.
        modelSelection = NULL;
    } else if (modelSelection != NULL) {
        // Table changed, reflect changes in cached selection model.
        switch(change->type) {
        case /*TableModelEvent::DELETE*/-1:
            modelSelection->removeIndexInterval(change->startModelIndex,
                                               change->endModelIndex);
            break;
        case /*TableModelEvent::INSERT*/1:
            modelSelection->insertIndexInterval(change->startModelIndex,
                                               change->length,
                                               true);
            break;
        default:
            break;
        }
    } else {
        // table changed, but haven't cached rows, temporarily
        // cache them.
        cacheModelSelection(NULL);
    }
}
 /*private*/ void SortManager::cacheModelSelection(RowSorterEvent* sortEvent) {
     lastModelSelection = jt->convertSelectionToModel(sortEvent);
     modelLeadIndex = jt->convertRowIndexToModel(sortEvent,
                 ((DefaultListSelectionModel*)jt->_selectionModel)->getLeadSelectionIndex());
 }

 /**
  * Inovked when either the table has changed or the sorter has changed
  * and after the sorter has been notified. If necessary this will
  * reapply the selection and variable row heights.
  */
 /*public*/ void SortManager::processChange(RowSorterEvent* sortEvent,
                           ModelChange* change,
                           bool sorterChanged) {
     if (change != NULL) {
         if (change->allRowsChanged) {
             modelRowSizes = NULL;
             jt->rowModel = NULL;
         } else if (modelRowSizes != NULL) {
             if (change->type == TableModelEvent::INSERT) {
                 modelRowSizes->insertEntries(change->startModelIndex,
                                             change->endModelIndex -
                                             change->startModelIndex + 1,
                                             jt->getRowHeight());
             } else if (change->type == TableModelEvent::DELETE) {
                 modelRowSizes->removeEntries(change->startModelIndex,
                                             change->endModelIndex -
                                             change->startModelIndex +1 );
             }
         }
     }
     if (sorterChanged) {
         setViewRowHeightsFromModel();
         restoreSelection(change);
     }
 }

 /**
  * Resets the variable row heights in terms of the view from
  * that of the variable row heights in terms of the model.
  */
 /*private*/ void SortManager::setViewRowHeightsFromModel() {
     if (modelRowSizes != NULL) {
         jt->rowModel->setSizes(jt->getRowCount(), jt->getRowHeight());
         for (int viewIndex = jt->getRowCount() - 1; viewIndex >= 0;
                  viewIndex--) {
             int modelIndex = jt->convertRowIndexToModel(viewIndex);
             jt->rowModel->setSize(viewIndex,
                              modelRowSizes->getSize(modelIndex));
         }
     }
 }

 /**
  * Restores the selection from that in terms of the model.
  */
 /*private*/ void SortManager::restoreSelection(ModelChange* change) {
     syncingSelection = true;
     if (lastModelSelection != NULL) {
         jt->restoreSortingSelection(lastModelSelection,
                                 modelLeadIndex, change);
         lastModelSelection = NULL;
     } else if (modelSelection != NULL) {
         DefaultListSelectionModel* viewSelection = (DefaultListSelectionModel*)jt->getSelectionModel();
         viewSelection->setValueIsAdjusting(true);
         viewSelection->clearSelection();
         int min = modelSelection->getMinSelectionIndex();
         int max = modelSelection->getMaxSelectionIndex();
         int viewIndex;
         for (int modelIndex = min; modelIndex <= max; modelIndex++) {
             if (modelSelection->isSelectedIndex(modelIndex)) {
                 viewIndex = jt->convertRowIndexToView(modelIndex);
                 if (viewIndex != -1) {
                     viewSelection->addSelectionInterval(viewIndex,
                                                        viewIndex);
                 }
             }
         }
         // Restore the lead
         int viewLeadIndex = modelSelection->getLeadSelectionIndex();
         if (viewLeadIndex != -1 && !modelSelection->isSelectionEmpty()) {
             viewLeadIndex = jt->convertRowIndexToView(viewLeadIndex);
         }
 //  TODO        SwingUtilities2.setLeadAnchorWithoutSelection(
 //                viewSelection, viewLeadIndex, viewLeadIndex);
         viewSelection->setValueIsAdjusting(false);
     }
     syncingSelection = false;
 }
#if 0
#endif
 /**
   * ModelChange is used when sorting to restore state, it corresponds
   * to data from a TableModelEvent.  The values are precalculated as
   * they are used extensively.
   */
 // /*private*/ /*final*/ class ModelChange {
 //     // Starting index of the change, in terms of the model
 //     int startModelIndex;

 //     // Ending index of the change, in terms of the model
 //     int endModelIndex;

 //     // Type of change
 //     int type;

 //     // Number of rows in the model
 //     int modelRowCount;

 //     // The event that triggered this.
 //     TableModelEvent event;

 //     // Length of the change (end - start + 1)
 //     int length;

 //     // True if the event indicates all the contents have changed
 //     boolean allRowsChanged;

      ModelChange::ModelChange(TableModelEvent* e, JTable* jt) {
       this->jt = jt;
          startModelIndex = qMax(0, e->getFirstRow());
          endModelIndex = e->getLastRow();
          modelRowCount = jt->getModel()->rowCount();
          if (endModelIndex < 0) {
              endModelIndex = qMax(0, modelRowCount - 1);
          }
          length = endModelIndex - startModelIndex + 1;
          type = e->getType();
          event = e;
          allRowsChanged = (e->getLastRow() == INT_MAX);
      }
  //};
#if 0
/**
 * Invoked when <code>sorterChanged</code> is invoked, or
 * when <code>tableChanged</code> is invoked and sorting is enabled.
 */
private void sortedTableChanged(RowSorterEvent sortedEvent,
                                TableModelEvent e) {
    int editingModelIndex = -1;
    ModelChange change = (e != NULL) ? new ModelChange(e) : NULL;

    if ((change == NULL || !change->allRowsChanged) &&
            this->editingRow != -1) {
        editingModelIndex = convertRowIndexToModel(sortedEvent,
                                                   this->editingRow);
    }

    sortManager.prepareForChange(sortedEvent, change);

    if (e != NULL) {
        if (change->type == TableModelEvent.UPDATE) {
            repaintSortedRows(change);
        }
        notifySorter(change);
        if (change->type != TableModelEvent.UPDATE) {
            // If the Sorter is unsorted we will not have received
            // notification, force treating insert/delete as a change->
            sorterChanged = true;
        }
    }
    else {
        sorterChanged = true;
    }

    sortManager.processChange(sortedEvent, change, sorterChanged);

    if (sorterChanged) {
        // Update the editing row
        if (this->editingRow != -1) {
            int newIndex = (editingModelIndex == -1) ? -1 :
                    convertRowIndexToView(editingModelIndex,change);
            restoreSortingEditingRow(newIndex);
        }

        // And handle the appropriate repainting.
        if (e == NULL || change->type != TableModelEvent.UPDATE) {
            resizeAndRepaint();
        }
    }

    // Check if lead/anchor need to be reset.
    if (change != NULL && change->allRowsChanged) {
        clearSelectionAndLeadAnchor();
        resizeAndRepaint();
    }
}

/**
 * Repaints the sort of sorted rows in response to a TableModelEvent.
 */
private void repaintSortedRows(ModelChange change) {
    if (change->startModelIndex > change->endModelIndex ||
            change->startModelIndex + 10 < change->endModelIndex) {
        // Too much has changed, punt
        repaint();
        return;
    }
    int eventColumn = change->event.getColumn();
    int columnViewIndex = eventColumn;
    if (columnViewIndex == TableModelEvent.ALL_COLUMNS) {
        columnViewIndex = 0;
    }
    else {
        columnViewIndex = convertColumnIndexToView(columnViewIndex);
        if (columnViewIndex == -1) {
            return;
        }
    }
    int modelIndex = change->startModelIndex;
    while (modelIndex <= change->endModelIndex) {
        int viewIndex = convertRowIndexToView(modelIndex++);
        if (viewIndex != -1) {
            Rectangle dirty = getCellRect(viewIndex, columnViewIndex,
                                          false);
            int x = dirty.x;
            int w = dirty.width;
            if (eventColumn == TableModelEvent.ALL_COLUMNS) {
                x = 0;
                w = getWidth();
            }
            repaint(x, dirty.y, w, dirty.height);
        }
    }
}
#endif
/**
 * Restores the selection after a model event/sort order changes.
 * All coordinates are in terms of the model.
 */
/*private*/ void JTable::restoreSortingSelection(QVector<int>* selection, int lead,
        ModelChange* change) {
    // Convert the selection from model to view
    for (int i = selection->length() - 1; i >= 0; i--) {
        selection->replace(i, convertRowIndexToView(selection->at(i), change));
    }
    lead = convertRowIndexToView(lead, change);

    // Check for the common case of no change in selection for 1 row
    if (selection->length() == 0 ||
        (selection->length() == 1 && selection->at(0) == getSelectedRow())) {
        return;
    }

    // And apply the new selection
    _selectionModel->setValueIsAdjusting(true);
    _selectionModel->clearSelection();
    for (int i = selection->length() - 1; i >= 0; i--) {
        if (selection->at(i) != -1) {
            _selectionModel->addSelectionInterval(selection->at(i),
                                                selection->at(i));
        }
    }
//    SwingUtilities2.setLeadAnchorWithoutSelection(
//            selectionModel, lead, lead);
    _selectionModel->setValueIsAdjusting(false);
}

/**
 * Restores the editing row after a model event/sort order change->
 *
 * @param editingRow new index of the editingRow, in terms of the view
 */
/*private*/ void JTable::restoreSortingEditingRow(int editingRow) {
    if (editingRow == -1) {
#if 0
        // Editing row no longer being shown, cancel editing
        TableCellEditor* editor = getCellEditor();
        if (editor != NULL) {
            // First try and cancel
            editor.cancelCellEditing();
            if (getCellEditor() != NULL) {
                // CellEditor didn't cede control, forcefully
                // remove it
                removeEditor();
            }
        }
#endif
    }
    else {
        // Repositioning handled in BasicTableUI
        this->editingRow = editingRow;
        update();
    }
}

/**
 * Notifies the sorter of a change in the underlying model.
 */
/*private*/ void JTable::notifySorter(ModelChange* change) {
    //try {
        ignoreSortChange = true;
        sorterChanged = false;
        switch(change->type) {
        case /*TableModelEvent::UPDATE*/ 0:
            if (change->event->getLastRow() == INT_MAX) {
                sortManager->sorter->allRowsChanged();
            } else if (change->event->getColumn() ==
                       TableModelEvent::ALL_COLUMNS) {
                sortManager->sorter->rowsUpdated(change->startModelIndex,
                                   change->endModelIndex);
            } else {
                sortManager->sorter->rowsUpdated(change->startModelIndex,
                                   change->endModelIndex,
                                   change->event->getColumn());
            }
            break;
        case /*TableModelEvent::INSERT*/1:
            sortManager->sorter->rowsInserted(change->startModelIndex,
                                change->endModelIndex);
            break;
        case /*TableModelEvent::DELETE*/-1:
            sortManager->sorter->rowsDeleted(change->startModelIndex,
                               change->endModelIndex);
            break;
//        }
//    } finally {
        ignoreSortChange = false;
    }
}

/**
 * Converts a model index to view index.  This is called when the
 * sorter or model changes and sorting is enabled.
 *
 * @param change describes the TableModelEvent that initiated the change;
 *        will be NULL if called as the result of a sort
 */
/*private*/ int JTable::convertRowIndexToView(int modelIndex, ModelChange *change) {
    if (modelIndex < 0) {
        return -1;
    }
    if (change != NULL && modelIndex >= change->startModelIndex) {
        if (change->type == TableModelEvent::INSERT) {
            if (modelIndex + change->length >= change->modelRowCount) {
                return -1;
            }
            return sortManager->sorter->convertRowIndexToView(
                    modelIndex + change->length);
        }
        else if (change->type == TableModelEvent::DELETE) {
            if (modelIndex <= change->endModelIndex) {
                // deleted
                return -1;
            }
            else {
                if (modelIndex - change->length >= change->modelRowCount) {
                    return -1;
                }
                return sortManager->sorter->convertRowIndexToView(
                        modelIndex - change->length);
            }
        }
        // else, updated
    }
    if (modelIndex >= ((TableModel*)getModel())->getRowCount()) {
        return -1;
    }
    return sortManager->sorter->convertRowIndexToView(modelIndex);
}

/**
 * Converts the selection to model coordinates.  This is used when
 * the model changes or the sorter changes.
 */
/*private*/ QVector<int>* JTable::convertSelectionToModel(RowSorterEvent* e) {
    QVector<int>* selection = getSelectedRows();
    for (int i = selection->length() - 1; i >= 0; i--) {
        selection->replace(i, convertRowIndexToModel(e, selection->at(i)));
    }
    return selection;
}

/*private*/ int JTable::convertRowIndexToModel(RowSorterEvent* e, int viewIndex) {
    if (e != NULL) {
        if (e->getPreviousRowCount() == 0) {
            return viewIndex;
        }
        // range checking handled by RowSorterEvent
        return e->convertPreviousRowIndexToModel(viewIndex);
    }
    // Make sure the viewIndex is valid
    if (viewIndex < 0 || viewIndex >= getRowCount()) {
        return -1;
    }
    return convertRowIndexToModel(viewIndex);
}

//
// Implementing TableModelListener interface
//

/**
 * Invoked when this table's <code>TableModel</code> generates
 * a <code>TableModelEvent</code>.
 * The <code>TableModelEvent</code> should be constructed in the
 * coordinate system of the model; the appropriate mapping to the
 * view coordinate system is performed by this <code>JTable</code>
 * when it receives the event.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by <code>JTable</code>.
 * <p>
 * Note that as of 1.3, this method clears the selection, if any.
 */
/*public*/ void JTable::tableChanged(TableModelEvent* e)
{
#if 0
 if (e == NULL || e->getFirstRow() == TableModelEvent::HEADER_ROW)
 {
  // The whole thing changed
  clearSelectionAndLeadAnchor();

//  rowModel = NULL;

//  if (sortManager != NULL)
//  {
//   try
//   {
//    ignoreSortChange = true;
//    sortManager.sorter.modelStructureChanged();
//   }
//   finally
//   {
//    ignoreSortChange = false;
//   }
//   sortManager.allChanged();
//  }

  if (getAutoCreateColumnsFromModel())
  {
   // This will effect invalidation of the JTable and JTableHeader.
   createDefaultColumnsFromModel();
   return;
  }

//  resizeAndRepaint();
  return;
 }

// if (sortManager != NULL)
// {
//  sortedTableChanged(NULL, e);
//  return;
// }

 // The totalRowHeight calculated below will be incorrect if
 // there are variable height rows. Repaint the visible region,
 // but don't return as a revalidate may be necessary as well.
 if (rowModel != NULL)
 {
     repaint();
 }
#if 0
 if (e->getType() == TableModelEvent::INSERT) {
     tableRowsInserted(e);
     return;
 }

 if (e->getType() == TableModelEvent::DELETE) {
     tableRowsDeleted(e);
     return;
 }
#endif
 int modelColumn = e->getColumn();
 int start = e->getFirstRow();
 int end = e->getLastRow();
#if 0
 QRect dirtyRegion;
 if (modelColumn == TableModelEvent::ALL_COLUMNS)
 {
  // 1 or more rows changed
  dirtyRegion = QRect(0, start * getRowHeight(), getColumnModel()->getTotalColumnWidth(), 0);
 }
 else
 {
  // A cell or column of cells has changed.
  // Unlike the rest of the methods in the JTable, the TableModelEvent
  // uses the coordinate system of the model instead of the view.
  // This is the only place in the JTable where this "reverse mapping"
  // is used.
  int column = convertColumnIndexToView(modelColumn);
  dirtyRegion = getCellRect(start, column, false);
 }

 // Now adjust the height of the dirty region according to the value of "end".
 // Check for Integer.MAX_VALUE as this will cause an overflow.
 if (end != /*Integer.MAX_VALUE*/65535)
 {
  dirtyRegion.setHeight((end-start+1)*getRowHeight());
  repaint(dirtyRegion.x, dirtyRegion.y, dirtyRegion.width, dirtyRegion.height);
 }
 // In fact, if the end is Integer.MAX_VALUE we need to revalidate anyway
 // because the scrollbar may need repainting.
 else
 {
  clearSelectionAndLeadAnchor();
  resizeAndRepaint();
  rowModel = NULL;
 }
#endif
#endif
}
#if 0
/*
 * Invoked when rows have been inserted into the table.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param e the TableModelEvent encapsulating the insertion
 */
private void tableRowsInserted(TableModelEvent e) {
    int start = e.getFirstRow();
    int end = e.getLastRow();
    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = getRowCount()-1;
    }

    // Adjust the selection to account for the new rows.
    int length = end - start + 1;
    selectionModel.insertIndexInterval(start, length, true);

    // If we have variable height rows, adjust the row model.
    if (rowModel != NULL) {
        rowModel.insertEntries(start, length, getRowHeight());
    }
    int rh = getRowHeight() ;
    Rectangle drawRect = new Rectangle(0, start * rh,
                                    getColumnModel().getTotalColumnWidth(),
                                       (getRowCount()-start) * rh);

    revalidate();
    // PENDING(milne) revalidate calls repaint() if parent is a ScrollPane
    // repaint still required in the unusual case where there is no ScrollPane
    repaint(drawRect);
}

/*
 * Invoked when rows have been removed from the table.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param e the TableModelEvent encapsulating the deletion
 */
private void tableRowsDeleted(TableModelEvent e) {
    int start = e.getFirstRow();
    int end = e.getLastRow();
    if (start < 0) {
        start = 0;
    }
    if (end < 0) {
        end = getRowCount()-1;
    }

    int deletedCount = end - start + 1;
    int previousRowCount = getRowCount() + deletedCount;
    // Adjust the selection to account for the new rows
    selectionModel.removeIndexInterval(start, end);

    // If we have variable height rows, adjust the row model.
    if (rowModel != NULL) {
        rowModel.removeEntries(start, deletedCount);
    }

    int rh = getRowHeight();
    Rectangle drawRect = new Rectangle(0, start * rh,
                                    getColumnModel().getTotalColumnWidth(),
                                    (previousRowCount - start) * rh);

    revalidate();
    // PENDING(milne) revalidate calls repaint() if parent is a ScrollPane
    // repaint still required in the unusual case where there is no ScrollPane
    repaint(drawRect);
}

//
// Implementing TableColumnModelListener interface
//

/**
 * Invoked when a column is added to the table column model.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @see TableColumnModelListener
 */
/*public*/ void columnAdded(TableColumnModelEvent e) {
    // If I'm currently editing, then I should stop editing
    if (isEditing()) {
        removeEditor();
    }
    resizeAndRepaint();
}

/**
 * Invoked when a column is removed from the table column model.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @see TableColumnModelListener
 */
/*public*/ void columnRemoved(TableColumnModelEvent e) {
    // If I'm currently editing, then I should stop editing
    if (isEditing()) {
        removeEditor();
    }
    resizeAndRepaint();
}

/**
 * Invoked when a column is repositioned. If a cell is being
 * edited, then editing is stopped and the cell is redrawn.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param e   the event received
 * @see TableColumnModelListener
 */
/*public*/ void columnMoved(TableColumnModelEvent e) {
    if (isEditing() && !getCellEditor().stopCellEditing()) {
        getCellEditor().cancelCellEditing();
    }
    repaint();
}

/**
 * Invoked when a column is moved due to a margin change->
 * If a cell is being edited, then editing is stopped and the cell
 * is redrawn.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param  e    the event received
 * @see TableColumnModelListener
 */
/*public*/ void columnMarginChanged(ChangeEvent e) {
    if (isEditing() && !getCellEditor().stopCellEditing()) {
        getCellEditor().cancelCellEditing();
    }
    TableColumn resizingColumn = getResizingColumn();
    // Need to do this here, before the parent's
    // layout manager calls getPreferredSize().
    if (resizingColumn != NULL && autoResizeMode == AUTO_RESIZE_OFF) {
        resizingColumn.setPreferredWidth(resizingColumn.getWidth());
    }
    resizeAndRepaint();
}

private int limit(int i, int a, int b) {
    return Math.min(b, Math.max(i, a));
}

/**
 * Invoked when the selection model of the <code>TableColumnModel</code>
 * is changed.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param  e  the event received
 * @see TableColumnModelListener
 */
/*public*/ void columnSelectionChanged(ListSelectionEvent e) {
    bool isAdjusting = e.getValueIsAdjusting();
    if (columnSelectionAdjusting && !isAdjusting) {
        // The assumption is that when the model is no longer adjusting
        // we will have already gotten all the changes, and therefore
        // don't need to do an additional paint.
        columnSelectionAdjusting = false;
        return;
    }
    columnSelectionAdjusting = isAdjusting;
    // The getCellRect() call will fail unless there is at least one row.
    if (getRowCount() <= 0 || getColumnCount() <= 0) {
        return;
    }
    int firstIndex = limit(e.getFirstIndex(), 0, getColumnCount()-1);
    int lastIndex = limit(e.getLastIndex(), 0, getColumnCount()-1);
    int minRow = 0;
    int maxRow = getRowCount() - 1;
    if (getRowSelectionAllowed()) {
        minRow = selectionModel.getMinSelectionIndex();
        maxRow = selectionModel.getMaxSelectionIndex();
        int leadRow = getAdjustedIndex(selectionModel.getLeadSelectionIndex(), true);

        if (minRow == -1 || maxRow == -1) {
            if (leadRow == -1) {
                // nothing to repaint, return
                return;
            }

            // only thing to repaint is the lead
            minRow = maxRow = leadRow;
        } else {
            // We need to consider more than just the range between
            // the min and max selected index. The lead row, which could
            // be outside this range, should be considered also.
            if (leadRow != -1) {
                minRow = Math.min(minRow, leadRow);
                maxRow = Math.max(maxRow, leadRow);
            }
        }
    }
    Rectangle firstColumnRect = getCellRect(minRow, firstIndex, false);
    Rectangle lastColumnRect = getCellRect(maxRow, lastIndex, false);
    Rectangle dirtyRegion = firstColumnRect.union(lastColumnRect);
    repaint(dirtyRegion);
}

//
// Implementing ListSelectionListener interface
//

/**
 * Invoked when the row selection changes -- repaints to show the new
 * selection.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param e   the event received
 * @see ListSelectionListener
 */
/*public*/ void valueChanged(ListSelectionEvent* e) {
    if (sortManager != NULL) {
        sortManager.viewSelectionChanged(e);
    }
    bool isAdjusting = e.getValueIsAdjusting();
    if (rowSelectionAdjusting && !isAdjusting) {
        // The assumption is that when the model is no longer adjusting
        // we will have already gotten all the changes, and therefore
        // don't need to do an additional paint.
        rowSelectionAdjusting = false;
        return;
    }
    rowSelectionAdjusting = isAdjusting;
    // The getCellRect() calls will fail unless there is at least one column.
    if (getRowCount() <= 0 || getColumnCount() <= 0) {
        return;
    }
    int firstIndex = limit(e.getFirstIndex(), 0, getRowCount()-1);
    int lastIndex = limit(e.getLastIndex(), 0, getRowCount()-1);
    Rectangle firstRowRect = getCellRect(firstIndex, 0, false);
    Rectangle lastRowRect = getCellRect(lastIndex, getColumnCount()-1, false);
    Rectangle dirtyRegion = firstRowRect.union(lastRowRect);
    repaint(dirtyRegion);
}

//
// Implementing the CellEditorListener interface
//

/**
 * Invoked when editing is finished. The changes are saved and the
 * editor is discarded.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param  e  the event received
 * @see CellEditorListener
 */
/*public*/ void editingStopped(ChangeEvent e) {
    // Take in the new value
    TableCellEditor editor = getCellEditor();
    if (editor != NULL) {
        Object value = editor.getCellEditorValue();
        setValueAt(value, editingRow, editingColumn);
        removeEditor();
    }
}

/**
 * Invoked when editing is canceled. The editor object is discarded
 * and the cell is rendered once again.
 * <p>
 * Application code will not use these methods explicitly, they
 * are used internally by JTable.
 *
 * @param  e  the event received
 * @see CellEditorListener
 */
/*public*/ void editingCanceled(ChangeEvent e) {
    removeEditor();
}

//
// Implementing the Scrollable interface
//

/**
 * Sets the preferred size of the viewport for this table.
 *
 * @param size  a <code>Dimension</code> object specifying the <code>preferredSize</code> of a
 *              <code>JViewport</code> whose view is this table
 * @see Scrollable#getPreferredScrollableViewportSize
 * @beaninfo
 * description: The preferred size of the viewport.
 */
/*public*/ void setPreferredScrollableViewportSize(Dimension size) {
    preferredViewportSize = size;
}

/**
 * Returns the preferred size of the viewport for this table.
 *
 * @return a <code>Dimension</code> object containing the <code>preferredSize</code> of the <code>JViewport</code>
 *         which displays this table
 * @see Scrollable#getPreferredScrollableViewportSize
 */
/*public*/ Dimension getPreferredScrollableViewportSize() {
    return preferredViewportSize;
}

/**
 * Returns the scroll increment (in pixels) that completely exposes one new
 * row or column (depending on the orientation).
 * <p>
 * This method is called each time the user requests a unit scroll.
 *
 * @param visibleRect the view area visible within the viewport
 * @param orientation either <code>SwingConstants.VERTICAL</code>
 *                  or <code>SwingConstants.HORIZONTAL</code>
 * @param direction less than zero to scroll up/left,
 *                  greater than zero for down/right
 * @return the "unit" increment for scrolling in the specified direction
 * @see Scrollable#getScrollableUnitIncrement
 */
/*public*/ int getScrollableUnitIncrement(Rectangle visibleRect,
                                      int orientation,
                                      int direction) {
    int leadingRow;
    int leadingCol;
    Rectangle leadingCellRect;

    int leadingVisibleEdge;
    int leadingCellEdge;
    int leadingCellSize;

    leadingRow = getLeadingRow(visibleRect);
    leadingCol = getLeadingCol(visibleRect);
    if (orientation == SwingConstants.VERTICAL && leadingRow < 0) {
        // Couldn't find leading row - return some default value
        return getRowHeight();
    }
    else if (orientation == SwingConstants.HORIZONTAL && leadingCol < 0) {
        // Couldn't find leading col - return some default value
        return 100;
    }

    // Note that it's possible for one of leadingCol or leadingRow to be
    // -1, depending on the orientation.  This is okay, as getCellRect()
    // still provides enough information to calculate the unit increment.
    leadingCellRect = getCellRect(leadingRow, leadingCol, true);
    leadingVisibleEdge = leadingEdge(visibleRect, orientation);
    leadingCellEdge = leadingEdge(leadingCellRect, orientation);

    if (orientation == SwingConstants.VERTICAL) {
        leadingCellSize = leadingCellRect.height;

    }
    else {
        leadingCellSize = leadingCellRect.width;
    }

    // 4 cases:
    // #1: Leading cell fully visible, reveal next cell
    // #2: Leading cell fully visible, hide leading cell
    // #3: Leading cell partially visible, hide rest of leading cell
    // #4: Leading cell partially visible, reveal rest of leading cell

    if (leadingVisibleEdge == leadingCellEdge) { // Leading cell is fully
                                                 // visible
        // Case #1: Reveal previous cell
        if (direction < 0) {
            int retVal = 0;

            if (orientation == SwingConstants.VERTICAL) {
                // Loop past any zero-height rows
                while (--leadingRow >= 0) {
                    retVal = getRowHeight(leadingRow);
                    if (retVal != 0) {
                        break;
                    }
                }
            }
            else { // HORIZONTAL
                // Loop past any zero-width cols
                while (--leadingCol >= 0) {
                    retVal = getCellRect(leadingRow, leadingCol, true).width;
                    if (retVal != 0) {
                        break;
                    }
                }
            }
            return retVal;
        }
        else { // Case #2: hide leading cell
            return leadingCellSize;
        }
    }
    else { // Leading cell is partially hidden
        // Compute visible, hidden portions
        int hiddenAmt = Math.abs(leadingVisibleEdge - leadingCellEdge);
        int visibleAmt = leadingCellSize - hiddenAmt;

        if (direction > 0) {
            // Case #3: hide showing portion of leading cell
            return visibleAmt;
        }
        else { // Case #4: reveal hidden portion of leading cell
            return hiddenAmt;
        }
    }
}

/**
 * Returns <code>visibleRect.height</code> or
 * <code>visibleRect.width</code>,
 * depending on this table's orientation.  Note that as of Swing 1.1.1
 * (Java 2 v 1.2.2) the value
 * returned will ensure that the viewport is cleanly aligned on
 * a row boundary.
 *
 * @return <code>visibleRect.height</code> or
 *                                  <code>visibleRect.width</code>
 *                                  per the orientation
 * @see Scrollable#getScrollableBlockIncrement
 */
/*public*/ int getScrollableBlockIncrement(Rectangle visibleRect,
        int orientation, int direction) {

    if (getRowCount() == 0) {
        // Short-circuit empty table model
        if (SwingConstants.VERTICAL == orientation) {
            int rh = getRowHeight();
            return (rh > 0) ? Math.max(rh, (visibleRect.height / rh) * rh) :
                              visibleRect.height;
        }
        else {
            return visibleRect.width;
        }
    }
    // Shortcut for vertical scrolling of a table w/ uniform row height
    if (NULL == rowModel && SwingConstants.VERTICAL == orientation) {
        int row = rowAtPoint(visibleRect.getLocation());
        assert row != -1;
        int col = columnAtPoint(visibleRect.getLocation());
        Rectangle cellRect = getCellRect(row, col, true);

        if (cellRect.y == visibleRect.y) {
            int rh = getRowHeight();
            assert rh > 0;
            return Math.max(rh, (visibleRect.height / rh) * rh);
        }
    }
    if (direction < 0) {
        return getPreviousBlockIncrement(visibleRect, orientation);
    }
    else {
        return getNextBlockIncrement(visibleRect, orientation);
    }
}

/**
 * Called to get the block increment for upward scrolling in cases of
 * horizontal scrolling, or for vertical scrolling of a table with
 * variable row heights.
 */
private int getPreviousBlockIncrement(Rectangle visibleRect,
                                      int orientation) {
    // Measure back from visible leading edge
    // If we hit the cell on its leading edge, it becomes the leading cell.
    // Else, use following cell

    int row;
    int col;

    int   newEdge;
    Point newCellLoc;

    int visibleLeadingEdge = leadingEdge(visibleRect, orientation);
    bool leftToRight = getComponentOrientation().isLeftToRight();
    int newLeadingEdge;

    // Roughly determine the new leading edge by measuring back from the
    // leading visible edge by the size of the visible rect, and find the
    // cell there.
    if (orientation == SwingConstants.VERTICAL) {
        newEdge = visibleLeadingEdge - visibleRect.height;
        int x = visibleRect.x + (leftToRight ? 0 : visibleRect.width);
        newCellLoc = new Point(x, newEdge);
    }
    else if (leftToRight) {
        newEdge = visibleLeadingEdge - visibleRect.width;
        newCellLoc = new Point(newEdge, visibleRect.y);
    }
    else { // Horizontal, right-to-left
        newEdge = visibleLeadingEdge + visibleRect.width;
        newCellLoc = new Point(newEdge - 1, visibleRect.y);
    }
    row = rowAtPoint(newCellLoc);
    col = columnAtPoint(newCellLoc);

    // If we're measuring past the beginning of the table, we get an invalid
    // cell.  Just go to the beginning of the table in this case.
    if (orientation == SwingConstants.VERTICAL & row < 0) {
        newLeadingEdge = 0;
    }
    else if (orientation == SwingConstants.HORIZONTAL & col < 0) {
        if (leftToRight) {
            newLeadingEdge = 0;
        }
        else {
            newLeadingEdge = getWidth();
        }
    }
    else {
        // Refine our measurement
        Rectangle newCellRect = getCellRect(row, col, true);
        int newCellLeadingEdge = leadingEdge(newCellRect, orientation);
        int newCellTrailingEdge = trailingEdge(newCellRect, orientation);

        // Usually, we hit in the middle of newCell, and want to scroll to
        // the beginning of the cell after newCell.  But there are a
        // couple corner cases where we want to scroll to the beginning of
        // newCell itself.  These cases are:
        // 1) newCell is so large that it ends at or extends into the
        //    visibleRect (newCell is the leading cell, or is adjacent to
        //    the leading cell)
        // 2) newEdge happens to fall right on the beginning of a cell

        // Case 1
        if ((orientation == SwingConstants.VERTICAL || leftToRight) &&
            (newCellTrailingEdge >= visibleLeadingEdge)) {
            newLeadingEdge = newCellLeadingEdge;
        }
        else if (orientation == SwingConstants.HORIZONTAL &&
                 !leftToRight &&
                 newCellTrailingEdge <= visibleLeadingEdge) {
            newLeadingEdge = newCellLeadingEdge;
        }
        // Case 2:
        else if (newEdge == newCellLeadingEdge) {
            newLeadingEdge = newCellLeadingEdge;
        }
        // Common case: scroll to cell after newCell
        else {
            newLeadingEdge = newCellTrailingEdge;
        }
    }
    return Math.abs(visibleLeadingEdge - newLeadingEdge);
}

/**
 * Called to get the block increment for downward scrolling in cases of
 * horizontal scrolling, or for vertical scrolling of a table with
 * variable row heights.
 */
private int getNextBlockIncrement(Rectangle visibleRect,
                                  int orientation) {
    // Find the cell at the trailing edge.  Return the distance to put
    // that cell at the leading edge.
    int trailingRow = getTrailingRow(visibleRect);
    int trailingCol = getTrailingCol(visibleRect);

    Rectangle cellRect;
    bool cellFillsVis;

    int cellLeadingEdge;
    int cellTrailingEdge;
    int newLeadingEdge;
    int visibleLeadingEdge = leadingEdge(visibleRect, orientation);

    // If we couldn't find trailing cell, just return the size of the
    // visibleRect.  Note that, for instance, we don't need the
    // trailingCol to proceed if we're scrolling vertically, because
    // cellRect will still fill in the required dimensions.  This would
    // happen if we're scrolling vertically, and the table is not wide
    // enough to fill the visibleRect.
    if (orientation == SwingConstants.VERTICAL && trailingRow < 0) {
        return visibleRect.height;
    }
    else if (orientation == SwingConstants.HORIZONTAL && trailingCol < 0) {
        return visibleRect.width;
    }
    cellRect = getCellRect(trailingRow, trailingCol, true);
    cellLeadingEdge = leadingEdge(cellRect, orientation);
    cellTrailingEdge = trailingEdge(cellRect, orientation);

    if (orientation == SwingConstants.VERTICAL ||
        getComponentOrientation().isLeftToRight()) {
        cellFillsVis = cellLeadingEdge <= visibleLeadingEdge;
    }
    else { // Horizontal, right-to-left
        cellFillsVis = cellLeadingEdge >= visibleLeadingEdge;
    }

    if (cellFillsVis) {
        // The visibleRect contains a single large cell.  Scroll to the end
        // of this cell, so the following cell is the first cell.
        newLeadingEdge = cellTrailingEdge;
    }
    else if (cellTrailingEdge == trailingEdge(visibleRect, orientation)) {
        // The trailing cell happens to end right at the end of the
        // visibleRect.  Again, scroll to the beginning of the next cell.
        newLeadingEdge = cellTrailingEdge;
    }
    else {
        // Common case: the trailing cell is partially visible, and isn't
        // big enough to take up the entire visibleRect.  Scroll so it
        // becomes the leading cell.
        newLeadingEdge = cellLeadingEdge;
    }
    return Math.abs(newLeadingEdge - visibleLeadingEdge);
}

/*
 * Return the row at the top of the visibleRect
 *
 * May return -1
 */
private int getLeadingRow(Rectangle visibleRect) {
    Point leadingPoint;

    if (getComponentOrientation().isLeftToRight()) {
        leadingPoint = new Point(visibleRect.x, visibleRect.y);
    }
    else {
        leadingPoint = new Point(visibleRect.x + visibleRect.width - 1,
                                 visibleRect.y);
    }
    return rowAtPoint(leadingPoint);
}

/*
 * Return the column at the leading edge of the visibleRect.
 *
 * May return -1
 */
private int getLeadingCol(Rectangle visibleRect) {
    Point leadingPoint;

    if (getComponentOrientation().isLeftToRight()) {
        leadingPoint = new Point(visibleRect.x, visibleRect.y);
    }
    else {
        leadingPoint = new Point(visibleRect.x + visibleRect.width - 1,
                                 visibleRect.y);
    }
    return columnAtPoint(leadingPoint);
}

/*
 * Return the row at the bottom of the visibleRect.
 *
 * May return -1
 */
private int getTrailingRow(Rectangle visibleRect) {
    Point trailingPoint;

    if (getComponentOrientation().isLeftToRight()) {
        trailingPoint = new Point(visibleRect.x,
                                  visibleRect.y + visibleRect.height - 1);
    }
    else {
        trailingPoint = new Point(visibleRect.x + visibleRect.width - 1,
                                  visibleRect.y + visibleRect.height - 1);
    }
    return rowAtPoint(trailingPoint);
}

/*
 * Return the column at the trailing edge of the visibleRect.
 *
 * May return -1
 */
private int getTrailingCol(Rectangle visibleRect) {
    Point trailingPoint;

    if (getComponentOrientation().isLeftToRight()) {
        trailingPoint = new Point(visibleRect.x + visibleRect.width - 1,
                                  visibleRect.y);
    }
    else {
        trailingPoint = new Point(visibleRect.x, visibleRect.y);
    }
    return columnAtPoint(trailingPoint);
}

/*
 * Returns the leading edge ("beginning") of the given Rectangle.
 * For VERTICAL, this is the top, for left-to-right, the left side, and for
 * right-to-left, the right side.
 */
private int leadingEdge(Rectangle rect, int orientation) {
    if (orientation == SwingConstants.VERTICAL) {
        return rect.y;
    }
    else if (getComponentOrientation().isLeftToRight()) {
        return rect.x;
    }
    else { // Horizontal, right-to-left
        return rect.x + rect.width;
    }
}

/*
 * Returns the trailing edge ("end") of the given Rectangle.
 * For VERTICAL, this is the bottom, for left-to-right, the right side, and
 * for right-to-left, the left side.
 */
private int trailingEdge(Rectangle rect, int orientation) {
    if (orientation == SwingConstants.VERTICAL) {
        return rect.y + rect.height;
    }
    else if (getComponentOrientation().isLeftToRight()) {
        return rect.x + rect.width;
    }
    else { // Horizontal, right-to-left
        return rect.x;
    }
}

/**
 * Returns false if <code>autoResizeMode</code> is set to
 * <code>AUTO_RESIZE_OFF</code>, which indicates that the
 * width of the viewport does not determine the width
 * of the table.  Otherwise returns true.
 *
 * @return false if <code>autoResizeMode</code> is set
 *   to <code>AUTO_RESIZE_OFF</code>, otherwise returns true
 * @see Scrollable#getScrollableTracksViewportWidth
 */
/*public*/ bool getScrollableTracksViewportWidth() {
    return !(autoResizeMode == AUTO_RESIZE_OFF);
}

/**
 * Returns {@code false} to indicate that the height of the viewport does
 * not determine the height of the table, unless
 * {@code getFillsViewportHeight} is {@code true} and the preferred height
 * of the table is smaller than the viewport's height.
 *
 * @return {@code false} unless {@code getFillsViewportHeight} is
 *         {@code true} and the table needs to be stretched to fill
 *         the viewport
 * @see Scrollable#getScrollableTracksViewportHeight
 * @see #setFillsViewportHeight
 * @see #getFillsViewportHeight
 */
/*public*/ bool getScrollableTracksViewportHeight() {
    Container parent = SwingUtilities.getUnwrappedParent(this);
    return getFillsViewportHeight()
           && parent instanceof JViewport
           && parent.getHeight() > getPreferredSize().height;
}

/**
 * Sets whether or not this table is always made large enough
 * to fill the height of an enclosing viewport. If the preferred
 * height of the table is smaller than the viewport, then the table
 * will be stretched to fill the viewport. In other words, this
 * ensures the table is never smaller than the viewport.
 * The default for this property is {@code false}.
 *
 * @param fillsViewportHeight whether or not this table is always
 *        made large enough to fill the height of an enclosing
 *        viewport
 * @see #getFillsViewportHeight
 * @see #getScrollableTracksViewportHeight
 * @since 1.6
 * @beaninfo
 *      bound: true
 *      description: Whether or not this table is always made large enough
 *                   to fill the height of an enclosing viewport
 */
/*public*/ void setFillsViewportHeight(bool fillsViewportHeight) {
    bool old = this->fillsViewportHeight;
    this->fillsViewportHeight = fillsViewportHeight;
    resizeAndRepaint();
    firePropertyChange("fillsViewportHeight", old, fillsViewportHeight);
}

/**
 * Returns whether or not this table is always made large enough
 * to fill the height of an enclosing viewport.
 *
 * @return whether or not this table is always made large enough
 *         to fill the height of an enclosing viewport
 * @see #setFillsViewportHeight
 * @since 1.6
 */
/*public*/ bool getFillsViewportHeight() {
    return fillsViewportHeight;
}

//
// Protected Methods
//

/*protected*/ bool processKeyBinding(KeyStroke ks, KeyEvent e,
                                    int condition, bool pressed) {
    bool retValue = super.processKeyBinding(ks, e, condition, pressed);

    // Start editing when a key is typed. UI classes can disable this behavior
    // by setting the client property JTable.autoStartsEdit to Boolean.FALSE.
    if (!retValue && condition == WHEN_ANCESTOR_OF_FOCUSED_COMPONENT &&
        isFocusOwner() &&
        !Boolean.FALSE.equals(getClientProperty("JTable.autoStartsEdit"))) {
        // We do not have a binding for the event.
        Component editorComponent = getEditorComponent();
        if (editorComponent == NULL) {
            // Only attempt to install the editor on a KEY_PRESSED,
            if (e == NULL || e.getID() != KeyEvent.KEY_PRESSED) {
                return false;
            }
            // Don't start when just a modifier is pressed
            int code = e.getKeyCode();
            if (code == KeyEvent.VK_SHIFT || code == KeyEvent.VK_CONTROL ||
                code == KeyEvent.VK_ALT) {
                return false;
            }
            // Try to install the editor
            int leadRow = getSelectionModel().getLeadSelectionIndex();
            int leadColumn = getColumnModel().getSelectionModel().
                               getLeadSelectionIndex();
            if (leadRow != -1 && leadColumn != -1 && !isEditing()) {
                if (!editCellAt(leadRow, leadColumn, e)) {
                    return false;
                }
            }
            editorComponent = getEditorComponent();
            if (editorComponent == NULL) {
                return false;
            }
        }
        // If the editorComponent is a JComponent, pass the event to it.
        if (editorComponent instanceof JComponent) {
            retValue = ((JComponent)editorComponent).processKeyBinding
                                    (ks, e, WHEN_FOCUSED, pressed);
            // If we have started an editor as a result of the user
            // pressing a key and the surrendersFocusOnKeystroke property
            // is true, give the focus to the new editor.
            if (getSurrendersFocusOnKeystroke()) {
                editorComponent.requestFocus();
            }
        }
    }
    return retValue;
}

private void setLazyValue(Hashtable h, Class c, String s) {
    h.put(c, new SwingLazyValue(s));
}

private void setLazyRenderer(Class c, String s) {
    setLazyValue(defaultRenderersByColumnClass, c, s);
}

/**
 * Creates default cell renderers for objects, numbers, doubles, dates,
 * bools, and icons.
 * @see javax.swing.table.DefaultTableCellRenderer
 *
 */
/*protected*/ void createDefaultRenderers() {
    defaultRenderersByColumnClass = new UIDefaults(8, 0.75f);

    // Objects
    setLazyRenderer(Object.class, "javax.swing.table.DefaultTableCellRenderer$UIResource");

    // Numbers
    setLazyRenderer(Number.class, "javax.swing.JTable$NumberRenderer");

    // Doubles and Floats
    setLazyRenderer(Float.class, "javax.swing.JTable$DoubleRenderer");
    setLazyRenderer(Double.class, "javax.swing.JTable$DoubleRenderer");

    // Dates
    setLazyRenderer(Date.class, "javax.swing.JTable$DateRenderer");

    // Icons and ImageIcons
    setLazyRenderer(Icon.class, "javax.swing.JTable$IconRenderer");
    setLazyRenderer(ImageIcon.class, "javax.swing.JTable$IconRenderer");

    // Booleans
    setLazyRenderer(Boolean.class, "javax.swing.JTable$BooleanRenderer");
}

/**
 * Default Renderers
 **/
static class NumberRenderer extends DefaultTableCellRenderer.UIResource {
    /*public*/ NumberRenderer() {
        super();
        setHorizontalAlignment(JLabel.RIGHT);
    }
}

static class DoubleRenderer extends NumberRenderer {
    NumberFormat formatter;
    /*public*/ DoubleRenderer() { super(); }

    /*public*/ void setValue(Object value) {
        if (formatter == NULL) {
            formatter = NumberFormat.getInstance();
        }
        setText((value == NULL) ? "" : formatter.format(value));
    }
}

static class DateRenderer extends DefaultTableCellRenderer.UIResource {
    DateFormat formatter;
    /*public*/ DateRenderer() { super(); }

    /*public*/ void setValue(Object value) {
        if (formatter==NULL) {
            formatter = DateFormat.getDateInstance();
        }
        setText((value == NULL) ? "" : formatter.format(value));
    }
}

static class IconRenderer extends DefaultTableCellRenderer.UIResource {
    /*public*/ IconRenderer() {
        super();
        setHorizontalAlignment(JLabel.CENTER);
    }
    /*public*/ void setValue(Object value) { setIcon((value instanceof Icon) ? (Icon)value : NULL); }
}


static class BooleanRenderer extends JCheckBox implements TableCellRenderer, UIResource
{
    private static final Border noFocusBorder = new EmptyBorder(1, 1, 1, 1);

    /*public*/ BooleanRenderer() {
        super();
        setHorizontalAlignment(JLabel.CENTER);
        setBorderPainted(true);
    }

    /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
                                                   bool isSelected, bool hasFocus, int row, int column) {
        if (isSelected) {
            setForeground(table.getSelectionForeground());
            super.setBackground(table.getSelectionBackground());
        }
        else {
            setForeground(table.getForeground());
            setBackground(table.getBackground());
        }
        setSelected((value != NULL && ((Boolean)value).boolValue()));

        if (hasFocus) {
            setBorder(UIManager.getBorder("Table.focusCellHighlightBorder"));
        } else {
            setBorder(noFocusBorder);
        }

        return this;
    }
}

private void setLazyEditor(Class c, String s) {
    setLazyValue(defaultEditorsByColumnClass, c, s);
}

/**
 * Creates default cell editors for objects, numbers, and bool values.
 * @see DefaultCellEditor
 */
/*protected*/ void createDefaultEditors() {
    defaultEditorsByColumnClass = new UIDefaults(3, 0.75f);

    // Objects
    setLazyEditor(Object.class, "javax.swing.JTable$GenericEditor");

    // Numbers
    setLazyEditor(Number.class, "javax.swing.JTable$NumberEditor");

    // Booleans
    setLazyEditor(Boolean.class, "javax.swing.JTable$BooleanEditor");
}

/**
 * Default Editors
 */
static class GenericEditor extends DefaultCellEditor {

    Class[] argTypes = new Class[]{String.class};
    java.lang.reflect.Constructor constructor;
    Object value;

    /*public*/ GenericEditor() {
        super(new JTextField());
        getComponent().setName("Table.editor");
    }

    /*public*/ bool stopCellEditing() {
        String s = (String)super.getCellEditorValue();
        // Here we are dealing with the case where a user
        // has deleted the string value in a cell, possibly
        // after a failed validation. Return NULL, so that
        // they have the option to replace the value with
        // NULL or use escape to restore the original.
        // For Strings, return "" for backward compatibility.
        try {
            if ("".equals(s)) {
                if (constructor.getDeclaringClass() == String.class) {
                    value = s;
                }
                return super.stopCellEditing();
            }

            SwingUtilities2.checkAccess(constructor.getModifiers());
            value = constructor.newInstance(new Object[]{s});
        }
        catch (Exception e) {
            ((JComponent)getComponent()).setBorder(new LineBorder(Color.red));
            return false;
        }
        return super.stopCellEditing();
    }

    /*public*/ Component getTableCellEditorComponent(JTable table, Object value,
                                             bool isSelected,
                                             int row, int column) {
        this->value = NULL;
        ((JComponent)getComponent()).setBorder(new LineBorder(Color.black));
        try {
            Class<?> type = table.getColumnClass(column);
            // Since our obligation is to produce a value which is
            // assignable for the required type it is OK to use the
            // String constructor for columns which are declared
            // to contain Objects. A String is an Object.
            if (type == Object.class) {
                type = String.class;
            }
            ReflectUtil.checkPackageAccess(type);
            SwingUtilities2.checkAccess(type.getModifiers());
            constructor = type.getConstructor(argTypes);
        }
        catch (Exception e) {
            return NULL;
        }
        return super.getTableCellEditorComponent(table, value, isSelected, row, column);
    }

    /*public*/ Object getCellEditorValue() {
        return value;
    }
}

static class NumberEditor extends GenericEditor {

    /*public*/ NumberEditor() {
        ((JTextField)getComponent()).setHorizontalAlignment(JTextField.RIGHT);
    }
}

static class BooleanEditor extends DefaultCellEditor {
    /*public*/ BooleanEditor() {
        super(new JCheckBox());
        JCheckBox checkBox = (JCheckBox)getComponent();
        checkBox.setHorizontalAlignment(JCheckBox.CENTER);
    }
}

/**
 * Initializes table properties to their default values.
 */
/*protected*/ void initializeLocalVars() {
    updateSelectionOnSort = true;
    setOpaque(true);
    createDefaultRenderers();
    createDefaultEditors();

    setTableHeader(createDefaultTableHeader());

    setShowGrid(true);
    setAutoResizeMode(AUTO_RESIZE_SUBSEQUENT_COLUMNS);
    setRowHeight(16);
    isRowHeightSet = false;
    setRowMargin(1);
    setRowSelectionAllowed(true);
    setCellEditor(NULL);
    setEditingColumn(-1);
    setEditingRow(-1);
    setSurrendersFocusOnKeystroke(false);
    setPreferredScrollableViewportSize(new Dimension(450, 400));

    // I'm registered to do tool tips so we can draw tips for the renderers
    ToolTipManager toolTipManager = ToolTipManager.sharedInstance();
    toolTipManager.registerComponent(this);

    setAutoscrolls(true);
}
#endif
/**
 * Returns the default table model object, which is
 * a <code>DefaultTableModel</code>.  A subclass can override this
 * method to return a different table model object.
 *
 * @return the default table model object
 * @see javax.swing.table.DefaultTableModel
 */
/*protected*/ TableModel* JTable::createDefaultDataModel() {
    return new DefaultTableModel();
}

/**
 * Returns the default column model object, which is
 * a <code>DefaultTableColumnModel</code>.  A subclass can override this
 * method to return a different column model object.
 *
 * @return the default column model object
 * @see javax.swing.table.DefaultTableColumnModel
 */
/*protected*/ TableColumnModel* JTable::createDefaultColumnModel() {
 return new DefaultTableColumnModel(/*(AbstractTableModel*)model()*/this);
}

/**
 * Returns the default selection model object, which is
 * a <code>DefaultListSelectionModel</code>.  A subclass can override this
 * method to return a different selection model object.
 *
 * @return the default selection model object
 * @see javax.swing.DefaultListSelectionModel
 */
/*protected*/ DefaultListSelectionModel* JTable::createDefaultSelectionModel() {
 DefaultListSelectionModel* m = new DefaultListSelectionModel((AbstractTableModel*)model());
 QItemSelectionModel* itemSelectionModel;
 QAbstractItemModel* _model = dataModel;
// if(qobject_cast<QSortFilterProxyModel*>(_model))
//  itemSelectionModel = new QItemSelectionModel(((QSortFilterProxyModel*)_model)->sourceModel());
// else
  itemSelectionModel = new QItemSelectionModel(_model);
 QTableView::setSelectionModel(itemSelectionModel);
 QItemSelectionModel* rslt = QAbstractItemView::selectionModel();
 if(rslt != itemSelectionModel)
  log->error(tr("setting selection mdel failed"));
 return m;
}
#if 0
/**
 * Returns the default table header object, which is
 * a <code>JTableHeader</code>.  A subclass can override this
 * method to return a different table header object.
 *
 * @return the default table header object
 * @see javax.swing.table.JTableHeader
 */
/*protected*/ JTableHeader createDefaultTableHeader() {
    return new JTableHeader(columnModel);
}
#endif
/**
 * Equivalent to <code>revalidate</code> followed by <code>repaint</code>.
 */
/*protected*/ void JTable::resizeAndRepaint() {
    //revalidate();
    update();
}
#if 0
/**
 * Returns the active cell editor, which is {@code NULL} if the table
 * is not currently editing.
 *
 * @return the {@code TableCellEditor} that does the editing,
 *         or {@code NULL} if the table is not currently editing.
 * @see #cellEditor
 * @see #getCellEditor(int, int)
 */
/*public*/ TableCellEditor getCellEditor() {
    return cellEditor;
}

/**
 * Sets the active cell editor.
 *
 * @param anEditor the active cell editor
 * @see #cellEditor
 * @beaninfo
 *  bound: true
 *  description: The table's active cell editor.
 */
/*public*/ void setCellEditor(TableCellEditor anEditor) {
    TableCellEditor oldEditor = cellEditor;
    cellEditor = anEditor;
    firePropertyChange("tableCellEditor", oldEditor, anEditor);
}

/**
 * Sets the <code>editingColumn</code> variable.
 * @param aColumn  the column of the cell to be edited
 *
 * @see #editingColumn
 */
/*public*/ void setEditingColumn(int aColumn) {
    editingColumn = aColumn;
}

/**
 * Sets the <code>editingRow</code> variable.
 * @param aRow  the row of the cell to be edited
 *
 * @see #editingRow
 */
/*public*/ void setEditingRow(int aRow) {
    editingRow = aRow;
}

/**
 * Returns an appropriate renderer for the cell specified by this row and
 * column. If the <code>TableColumn</code> for this column has a non-NULL
 * renderer, returns that.  If not, finds the class of the data in
 * this column (using <code>getColumnClass</code>)
 * and returns the default renderer for this type of data.
 * <p>
 * <b>Note:</b>
 * Throughout the table package, the internal implementations always
 * use this method to provide renderers so that this default behavior
 * can be safely overridden by a subclass.
 *
 * @param row       the row of the cell to render, where 0 is the first row
 * @param column    the column of the cell to render,
 *                  where 0 is the first column
 * @return the assigned renderer; if <code>NULL</code>
 *                  returns the default renderer
 *                  for this type of object
 * @see javax.swing.table.DefaultTableCellRenderer
 * @see javax.swing.table.TableColumn#setCellRenderer
 * @see #setDefaultRenderer
 */
/*public*/ TableCellRenderer getCellRenderer(int row, int column) {
    TableColumn tableColumn = getColumnModel().getColumn(column);
    TableCellRenderer renderer = tableColumn.getCellRenderer();
    if (renderer == NULL) {
        renderer = getDefaultRenderer(getColumnClass(column));
    }
    return renderer;
}

/**
 * Prepares the renderer by querying the data model for the
 * value and selection state
 * of the cell at <code>row</code>, <code>column</code>.
 * Returns the component (may be a <code>Component</code>
 * or a <code>JComponent</code>) under the event location.
 * <p>
 * During a printing operation, this method will configure the
 * renderer without indicating selection or focus, to prevent
 * them from appearing in the printed output. To do other
 * customizations based on whether or not the table is being
 * printed, you can check the value of
 * {@link javax.swing.JComponent#isPaintingForPrint()}, either here
 * or within custom renderers.
 * <p>
 * <b>Note:</b>
 * Throughout the table package, the internal implementations always
 * use this method to prepare renderers so that this default behavior
 * can be safely overridden by a subclass.
 *
 * @param renderer  the <code>TableCellRenderer</code> to prepare
 * @param row       the row of the cell to render, where 0 is the first row
 * @param column    the column of the cell to render,
 *                  where 0 is the first column
 * @return          the <code>Component</code> under the event location
 */
/*public*/ Component prepareRenderer(TableCellRenderer renderer, int row, int column) {
    Object value = getValueAt(row, column);

    bool isSelected = false;
    bool hasFocus = false;

    // Only indicate the selection and focused cell if not printing
    if (!isPaintingForPrint()) {
        isSelected = isCellSelected(row, column);

        bool rowIsLead =
            (selectionModel.getLeadSelectionIndex() == row);
        bool colIsLead =
            (columnModel.getSelectionModel().getLeadSelectionIndex() == column);

        hasFocus = (rowIsLead && colIsLead) && isFocusOwner();
    }

    return renderer.getTableCellRendererComponent(this, value,
                                                  isSelected, hasFocus,
                                                  row, column);
}

/**
 * Returns an appropriate editor for the cell specified by
 * <code>row</code> and <code>column</code>. If the
 * <code>TableColumn</code> for this column has a non-NULL editor,
 * returns that.  If not, finds the class of the data in this
 * column (using <code>getColumnClass</code>)
 * and returns the default editor for this type of data.
 * <p>
 * <b>Note:</b>
 * Throughout the table package, the internal implementations always
 * use this method to provide editors so that this default behavior
 * can be safely overridden by a subclass.
 *
 * @param row       the row of the cell to edit, where 0 is the first row
 * @param column    the column of the cell to edit,
 *                  where 0 is the first column
 * @return          the editor for this cell;
 *                  if <code>NULL</code> return the default editor for
 *                  this type of cell
 * @see DefaultCellEditor
 */
/*public*/ TableCellEditor getCellEditor(int row, int column) {
    TableColumn tableColumn = getColumnModel().getColumn(column);
    TableCellEditor editor = tableColumn.getCellEditor();
    if (editor == NULL) {
        editor = getDefaultEditor(getColumnClass(column));
    }
    return editor;
}


/**
 * Prepares the editor by querying the data model for the value and
 * selection state of the cell at <code>row</code>, <code>column</code>.
 * <p>
 * <b>Note:</b>
 * Throughout the table package, the internal implementations always
 * use this method to prepare editors so that this default behavior
 * can be safely overridden by a subclass.
 *
 * @param editor  the <code>TableCellEditor</code> to set up
 * @param row     the row of the cell to edit,
 *                where 0 is the first row
 * @param column  the column of the cell to edit,
 *                where 0 is the first column
 * @return the <code>Component</code> being edited
 */
/*public*/ Component prepareEditor(TableCellEditor editor, int row, int column) {
    Object value = getValueAt(row, column);
    bool isSelected = isCellSelected(row, column);
    Component comp = editor.getTableCellEditorComponent(this, value, isSelected,
                                              row, column);
    if (comp instanceof JComponent) {
        JComponent jComp = (JComponent)comp;
        if (jComp.getNextFocusableComponent() == NULL) {
            jComp.setNextFocusableComponent(this);
        }
    }
    return comp;
}

/**
 * Discards the editor object and frees the real estate it used for
 * cell rendering.
 */
/*public*/ void removeEditor() {
    KeyboardFocusManager.getCurrentKeyboardFocusManager().
        removePropertyChangeListener("permanentFocusOwner", editorRemover);
    editorRemover = NULL;

    TableCellEditor editor = getCellEditor();
    if(editor != NULL) {
        editor.removeCellEditorListener(this);
        if (editorComp != NULL) {
            Component focusOwner =
                    KeyboardFocusManager.getCurrentKeyboardFocusManager().getFocusOwner();
            bool isFocusOwnerInTheTable = focusOwner != NULL?
                    SwingUtilities.isDescendingFrom(focusOwner, this):false;
            remove(editorComp);
            if(isFocusOwnerInTheTable) {
                requestFocusInWindow();
            }
        }

        Rectangle cellRect = getCellRect(editingRow, editingColumn, false);

        setCellEditor(NULL);
        setEditingColumn(-1);
        setEditingRow(-1);
        editorComp = NULL;

        repaint(cellRect);
    }
}

//
// Serialization
//

/**
 * See readObject() and writeObject() in JComponent for more
 * information about serialization in Swing.
 */
private void writeObject(ObjectOutputStream s) throws IOException {
    s.defaultWriteObject();
    if (getUIClassID().equals(uiClassID)) {
        byte count = JComponent.getWriteObjCounter(this);
        JComponent.setWriteObjCounter(this, --count);
        if (count == 0 && ui != NULL) {
            ui.installUI(this);
        }
    }
}

private void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException
{
    s.defaultReadObject();
    if ((ui != NULL) && (getUIClassID().equals(uiClassID))) {
        ui.installUI(this);
    }
    createDefaultRenderers();
    createDefaultEditors();

    // If ToolTipText != NULL, then the tooltip has already been
    // registered by JComponent.readObject() and we don't want
    // to re-register here
    if (getToolTipText() == NULL) {
        ToolTipManager.sharedInstance().registerComponent(this);
     }
}

/* Called from the JComponent's EnableSerializationFocusListener to
 * do any Swing-specific pre-serialization configuration.
 */
void compWriteObjectNotify() {
    super.compWriteObjectNotify();
    // If ToolTipText != NULL, then the tooltip has already been
    // unregistered by JComponent.compWriteObjectNotify()
    if (getToolTipText() == NULL) {
        ToolTipManager.sharedInstance().unregisterComponent(this);
    }
}

/**
 * Returns a string representation of this table. This method
 * is intended to be used only for debugging purposes, and the
 * content and format of the returned string may vary between
 * implementations. The returned string may be empty but may not
 * be <code>NULL</code>.
 *
 * @return  a string representation of this table
 */
/*protected*/ String paramString() {
    String gridColorString = (gridColor != NULL ?
                              gridColor.toString() : "");
    String showHorizontalLinesString = (showHorizontalLines ?
                                        "true" : "false");
    String showVerticalLinesString = (showVerticalLines ?
                                      "true" : "false");
    String autoResizeModeString;
    if (autoResizeMode == AUTO_RESIZE_OFF) {
        autoResizeModeString = "AUTO_RESIZE_OFF";
    } else if (autoResizeMode == AUTO_RESIZE_NEXT_COLUMN) {
        autoResizeModeString = "AUTO_RESIZE_NEXT_COLUMN";
    } else if (autoResizeMode == AUTO_RESIZE_SUBSEQUENT_COLUMNS) {
        autoResizeModeString = "AUTO_RESIZE_SUBSEQUENT_COLUMNS";
    } else if (autoResizeMode == AUTO_RESIZE_LAST_COLUMN) {
        autoResizeModeString = "AUTO_RESIZE_LAST_COLUMN";
    } else if (autoResizeMode == AUTO_RESIZE_ALL_COLUMNS)  {
        autoResizeModeString = "AUTO_RESIZE_ALL_COLUMNS";
    } else autoResizeModeString = "";
    String autoCreateColumnsFromModelString = (autoCreateColumnsFromModel ?
                                               "true" : "false");
    String preferredViewportSizeString = (preferredViewportSize != NULL ?
                                          preferredViewportSize.toString()
                                          : "");
    String rowSelectionAllowedString = (rowSelectionAllowed ?
                                        "true" : "false");
    String cellSelectionEnabledString = (cellSelectionEnabled ?
                                        "true" : "false");
    String selectionForegroundString = (selectionForeground != NULL ?
                                        selectionForeground.toString() :
                                        "");
    String selectionBackgroundString = (selectionBackground != NULL ?
                                        selectionBackground.toString() :
                                        "");

    return super.paramString() +
    ",autoCreateColumnsFromModel=" + autoCreateColumnsFromModelString +
    ",autoResizeMode=" + autoResizeModeString +
    ",cellSelectionEnabled=" + cellSelectionEnabledString +
    ",editingColumn=" + editingColumn +
    ",editingRow=" + editingRow +
    ",gridColor=" + gridColorString +
    ",preferredViewportSize=" + preferredViewportSizeString +
    ",rowHeight=" + rowHeight +
    ",rowMargin=" + rowMargin +
    ",rowSelectionAllowed=" + rowSelectionAllowedString +
    ",selectionBackground=" + selectionBackgroundString +
    ",selectionForeground=" + selectionForegroundString +
    ",showHorizontalLines=" + showHorizontalLinesString +
    ",showVerticalLines=" + showVerticalLinesString;
}

// This class tracks changes in the keyboard focus state. It is used
// when the JTable is editing to determine when to cancel the edit.
// If focus switches to a component outside of the jtable, but in the
// same window, this will cancel editing.
class CellEditorRemover implements PropertyChangeListener {
    KeyboardFocusManager focusManager;

    /*public*/ CellEditorRemover(KeyboardFocusManager fm) {
        this->focusManager = fm;
    }

    /*public*/ void propertyChange(PropertyChangeEvent ev) {
        if (!isEditing() || getClientProperty("terminateEditOnFocusLost") != Boolean.TRUE) {
            return;
        }

        Component c = focusManager.getPermanentFocusOwner();
        while (c != NULL) {
            if (c == jt) {
                // focus remains inside the table
                return;
            } else if ((c instanceof Window) ||
                       (c instanceof Applet && c.getParent() == NULL)) {
                if (c == SwingUtilities.getRoot(jt)) {
                    if (!getCellEditor().stopCellEditing()) {
                        getCellEditor().cancelCellEditing();
                    }
                }
                break;
            }
            c = c.getParent();
        }
    }
}

/////////////////
// Printing Support
/////////////////

/**
 * A convenience method that displays a printing dialog, and then prints
 * this <code>JTable</code> in mode <code>PrintMode.FIT_WIDTH</code>,
 * with no header or footer text. A modal progress dialog, with an abort
 * option, will be shown for the duration of printing.
 * <p>
 * Note: In headless mode, no dialogs are shown and printing
 * occurs on the default printer.
 *
 * @return true, unless printing is cancelled by the user
 * @throws SecurityException if this thread is not allowed to
 *                           initiate a print job request
 * @throws PrinterException if an error in the print system causes the job
 *                          to be aborted
 * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
 *             bool, PrintRequestAttributeSet, bool, PrintService)
 * @see #getPrintable
 *
 * @since 1.5
 */
/*public*/ bool print() throws PrinterException {

    return print(PrintMode.FIT_WIDTH);
}

/**
 * A convenience method that displays a printing dialog, and then prints
 * this <code>JTable</code> in the given printing mode,
 * with no header or footer text. A modal progress dialog, with an abort
 * option, will be shown for the duration of printing.
 * <p>
 * Note: In headless mode, no dialogs are shown and printing
 * occurs on the default printer.
 *
 * @param  printMode        the printing mode that the printable should use
 * @return true, unless printing is cancelled by the user
 * @throws SecurityException if this thread is not allowed to
 *                           initiate a print job request
 * @throws PrinterException if an error in the print system causes the job
 *                          to be aborted
 * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
 *             bool, PrintRequestAttributeSet, bool, PrintService)
 * @see #getPrintable
 *
 * @since 1.5
 */
/*public*/ bool print(PrintMode printMode) throws PrinterException {

    return print(printMode, NULL, NULL);
}
#endif
/**
 * A convenience method that displays a printing dialog, and then prints
 * this <code>JTable</code> in the given printing mode,
 * with the specified header and footer text. A modal progress dialog,
 * with an abort option, will be shown for the duration of printing.
 * <p>
 * Note: In headless mode, no dialogs are shown and printing
 * occurs on the default printer.
 *
 * @param  printMode        the printing mode that the printable should use
 * @param  headerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a header,
 *                          or NULL for none
 * @param  footerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a footer,
 *                          or NULL for none
 * @return true, unless printing is cancelled by the user
 * @throws SecurityException if this thread is not allowed to
 *                           initiate a print job request
 * @throws PrinterException if an error in the print system causes the job
 *                          to be aborted
 * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
 *             bool, PrintRequestAttributeSet, bool, PrintService)
 * @see #getPrintable
 *
 * @since 1.5
 */
/*public*/ bool JTable::print(PrintMode printMode,
                     QString headerFormat,
                     QString  footerFormat) /*throws PrinterException*/
{

 bool showDialogs = /*!GraphicsEnvironment.isHeadless()*/ true;
 return print(printMode, headerFormat, footerFormat,
              showDialogs, NULL, showDialogs);
}

/**
 * Prints this table, as specified by the fully featured
 * {@link #print(JTable.PrintMode, MessageFormat, MessageFormat,
 * bool, PrintRequestAttributeSet, bool, PrintService) print}
 * method, with the default printer specified as the print service.
 *
 * @param  printMode        the printing mode that the printable should use
 * @param  headerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a header,
 *                          or <code>NULL</code> for none
 * @param  footerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a footer,
 *                          or <code>NULL</code> for none
 * @param  showPrintDialog  whether or not to display a print dialog
 * @param  attr             a <code>PrintRequestAttributeSet</code>
 *                          specifying any printing attributes,
 *                          or <code>NULL</code> for none
 * @param  interactive      whether or not to print in an interactive mode
 * @return true, unless printing is cancelled by the user
 * @throws HeadlessException if the method is asked to show a printing
 *                           dialog or run interactively, and
 *                           <code>GraphicsEnvironment.isHeadless</code>
 *                           returns <code>true</code>
 * @throws SecurityException if this thread is not allowed to
 *                           initiate a print job request
 * @throws PrinterException if an error in the print system causes the job
 *                          to be aborted
 * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
 *             bool, PrintRequestAttributeSet, bool, PrintService)
 * @see #getPrintable
 *
 * @since 1.5
 */
/*public*/ bool JTable::print(PrintMode printMode,
                     QString headerFormat,
                     QString footerFormat,
                     bool showPrintDialog,
                     PrintRequestAttributeSet* attr,
                     bool interactive) /*throws PrinterException,
                                                 HeadlessException*/
{

    return print(printMode,
                 headerFormat,
                 footerFormat,
                 showPrintDialog,
                 attr,
                 interactive,
                 NULL);
}

/**
 * Prints this <code>JTable</code>. Takes steps that the majority of
 * developers would take in order to print a <code>JTable</code>.
 * In short, it prepares the table, calls <code>getPrintable</code> to
 * fetch an appropriate <code>Printable</code>, and then sends it to the
 * printer.
 * <p>
 * A <code>bool</code> parameter allows you to specify whether or not
 * a printing dialog is displayed to the user. When it is, the user may
 * use the dialog to change the destination printer or printing attributes,
 * or even to cancel the print. Another two parameters allow for a
 * <code>PrintService</code> and printing attributes to be specified.
 * These parameters can be used either to provide initial values for the
 * print dialog, or to specify values when the dialog is not shown.
 * <p>
 * A second <code>bool</code> parameter allows you to specify whether
 * or not to perform printing in an interactive mode. If <code>true</code>,
 * a modal progress dialog, with an abort option, is displayed for the
 * duration of printing . This dialog also prevents any user action which
 * may affect the table. However, it can not prevent the table from being
 * modified by code (for example, another thread that posts updates using
 * <code>SwingUtilities.invokeLater</code>). It is therefore the
 * responsibility of the developer to ensure that no other code modifies
 * the table in any way during printing (invalid modifications include
 * changes in: size, renderers, or underlying data). Printing behavior is
 * undefined when the table is changed during printing.
 * <p>
 * If <code>false</code> is specified for this parameter, no dialog will
 * be displayed and printing will begin immediately on the event-dispatch
 * thread. This blocks any other events, including repaints, from being
 * processed until printing is complete. Although this effectively prevents
 * the table from being changed, it doesn't provide a good user experience.
 * For this reason, specifying <code>false</code> is only recommended when
 * printing from an application with no visible GUI.
 * <p>
 * Note: Attempting to show the printing dialog or run interactively, while
 * in headless mode, will result in a <code>HeadlessException</code>.
 * <p>
 * Before fetching the printable, this method will gracefully terminate
 * editing, if necessary, to prevent an editor from showing in the printed
 * result. Additionally, <code>JTable</code> will prepare its renderers
 * during printing such that selection and focus are not indicated.
 * As far as customizing further how the table looks in the printout,
 * developers can provide custom renderers or paint code that conditionalize
 * on the value of {@link javax.swing.JComponent#isPaintingForPrint()}.
 * <p>
 * See {@link #getPrintable} for more description on how the table is
 * printed.
 *
 * @param  printMode        the printing mode that the printable should use
 * @param  headerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a header,
 *                          or <code>NULL</code> for none
 * @param  footerFormat     a <code>MessageFormat</code> specifying the text
 *                          to be used in printing a footer,
 *                          or <code>NULL</code> for none
 * @param  showPrintDialog  whether or not to display a print dialog
 * @param  attr             a <code>PrintRequestAttributeSet</code>
 *                          specifying any printing attributes,
 *                          or <code>NULL</code> for none
 * @param  interactive      whether or not to print in an interactive mode
 * @param  service          the destination <code>PrintService</code>,
 *                          or <code>NULL</code> to use the default printer
 * @return true, unless printing is cancelled by the user
 * @throws HeadlessException if the method is asked to show a printing
 *                           dialog or run interactively, and
 *                           <code>GraphicsEnvironment.isHeadless</code>
 *                           returns <code>true</code>
 * @throws  SecurityException if a security manager exists and its
 *          {@link java.lang.SecurityManager#checkPrintJobAccess}
 *          method disallows this thread from creating a print job request
 * @throws PrinterException if an error in the print system causes the job
 *                          to be aborted
 * @see #getPrintable
 * @see java.awt.GraphicsEnvironment#isHeadless
 *
 * @since 1.6
 */
/*public*/ bool JTable::print(PrintMode /*printMode*/,
                     QString /*headerFormat*/,
                     QString /*footerFormat*/,
                     bool showPrintDialog,
                     PrintRequestAttributeSet* /*attr*/,
                     bool interactive,
                     PrintService* /*service*/) /*throws PrinterException,
                                                  HeadlessException*/
{

 // complain early if an invalid parameter is specified for headless mode
 bool isHeadless = /*GraphicsEnvironment.isHeadless()*/ false;
 if (isHeadless)
 {
  if (showPrintDialog)
  {
   throw HeadlessException("Can't show print dialog.");
  }

  if (interactive)
  {
   throw HeadlessException("Can't run interactively.");
  }
 }
#if 0
    // Get a PrinterJob.
    // Do this before anything with side-effects since it may throw a
    // security exception - in which case we don't want to do anything else.
    /*final*/ PrinterJob job = PrinterJob.getPrinterJob();

    if (isEditing()) {
        // try to stop cell editing, and failing that, cancel it
        if (!getCellEditor().stopCellEditing()) {
            getCellEditor().cancelCellEditing();
        }
    }

    if (attr == NULL) {
        attr = new HashPrintRequestAttributeSet();
    }

    final PrintingStatus printingStatus;

     // fetch the Printable
    Printable printable =
         getPrintable(printMode, headerFormat, footerFormat);

    if (interactive) {
        // wrap the Printable so that we can print on another thread
        printable = new ThreadSafePrintable(printable);
        printingStatus = PrintingStatus.createPrintingStatus(this, job);
        printable = printingStatus.createNotificationPrintable(printable);
    } else {
        // to please compiler
        printingStatus = NULL;
    }

    // set the printable on the PrinterJob
    job.setPrintable(printable);

    // if specified, set the PrintService on the PrinterJob
    if (service != NULL) {
        job.setPrintService(service);
    }

    // if requested, show the print dialog
    if (showPrintDialog && !job.printDialog(attr)) {
        // the user cancelled the print dialog
        return false;
    }

    // if not interactive, just print on this thread (no dialog)
    if (!interactive) {
        // do the printing
        job.print(attr);

        // we're done
        return true;
    }

    // make sure this is clear since we'll check it after
    printError = NULL;

    // to synchronize on
    final Object lock = new Object();

    // copied so we can access from the inner class
    final PrintRequestAttributeSet copyAttr = attr;

    // this runnable will be used to do the printing
    // (and save any throwables) on another thread
    Runnable runnable = new Runnable() {
        /*public*/ void run() {
            try {
                // do the printing
                job.print(copyAttr);
            } catch (Throwable t) {
                // save any Throwable to be rethrown
                synchronized(lock) {
                    printError = t;
                }
            } finally {
                // we're finished - hide the dialog
                printingStatus.dispose();
            }
        }
    };

    // start printing on another thread
    Thread th = new Thread(runnable);
    th.start();

    printingStatus.showModal(true);

    // look for any error that the printing may have generated
    Throwable pe;
    synchronized(lock) {
        pe = printError;
        printError = NULL;
    }

    // check the type of error and handle it
    if (pe != NULL) {
        // a subclass of PrinterException meaning the job was aborted,
        // in this case, by the user
        if (pe instanceof PrinterAbortException) {
            return false;
        } else if (pe instanceof PrinterException) {
            throw (PrinterException)pe;
        } else if (pe instanceof RuntimeException) {
            throw (RuntimeException)pe;
        } else if (pe instanceof Error) {
            throw (Error)pe;
        }

        // can not happen
        throw new AssertionError(pe);
    }
#endif
 return true;
}
#if 0
/**
 * Return a <code>Printable</code> for use in printing this JTable.
 * <p>
 * This method is meant for those wishing to customize the default
 * <code>Printable</code> implementation used by <code>JTable</code>'s
 * <code>print</code> methods. Developers wanting simply to print the table
 * should use one of those methods directly.
 * <p>
 * The <code>Printable</code> can be requested in one of two printing modes.
 * In both modes, it spreads table rows naturally in sequence across
 * multiple pages, fitting as many rows as possible per page.
 * <code>PrintMode.NORMAL</code> specifies that the table be
 * printed at its current size. In this mode, there may be a need to spread
 * columns across pages in a similar manner to that of the rows. When the
 * need arises, columns are distributed in an order consistent with the
 * table's <code>ComponentOrientation</code>.
 * <code>PrintMode.FIT_WIDTH</code> specifies that the output be
 * scaled smaller, if necessary, to fit the table's entire width
 * (and thereby all columns) on each page. Width and height are scaled
 * equally, maintaining the aspect ratio of the output.
 * <p>
 * The <code>Printable</code> heads the portion of table on each page
 * with the appropriate section from the table's <code>JTableHeader</code>,
 * if it has one.
 * <p>
 * Header and footer text can be added to the output by providing
 * <code>MessageFormat</code> arguments. The printing code requests
 * Strings from the formats, providing a single item which may be included
 * in the formatted string: an <code>Integer</code> representing the current
 * page number.
 * <p>
 * You are encouraged to read the documentation for
 * <code>MessageFormat</code> as some characters, such as single-quote,
 * are special and need to be escaped.
 * <p>
 * Here's an example of creating a <code>MessageFormat</code> that can be
 * used to print "Duke's Table: Page - " and the current page number:
 *
 * <pre>
 *     // notice the escaping of the single quote
 *     // notice how the page number is included with "{0}"
 *     MessageFormat format = new MessageFormat("Duke''s Table: Page - {0}");
 * </pre>
 * <p>
 * The <code>Printable</code> constrains what it draws to the printable
 * area of each page that it prints. Under certain circumstances, it may
 * find it impossible to fit all of a page's content into that area. In
 * these cases the output may be clipped, but the implementation
 * makes an effort to do something reasonable. Here are a few situations
 * where this is known to occur, and how they may be handled by this
 * particular implementation:
 * <ul>
 *   <li>In any mode, when the header or footer text is too wide to fit
 *       completely in the printable area -- print as much of the text as
 *       possible starting from the beginning, as determined by the table's
 *       <code>ComponentOrientation</code>.
 *   <li>In any mode, when a row is too tall to fit in the
 *       printable area -- print the upper-most portion of the row
 *       and paint no lower border on the table.
 *   <li>In <code>PrintMode.NORMAL</code> when a column
 *       is too wide to fit in the printable area -- print the center
 *       portion of the column and leave the left and right borders
 *       off the table.
 * </ul>
 * <p>
 * It is entirely valid for this <code>Printable</code> to be wrapped
 * inside another in order to create complex reports and documents. You may
 * even request that different pages be rendered into different sized
 * printable areas. The implementation must be prepared to handle this
 * (possibly by doing its layout calculations on the fly). However,
 * providing different heights to each page will likely not work well
 * with <code>PrintMode.NORMAL</code> when it has to spread columns
 * across pages.
 * <p>
 * As far as customizing how the table looks in the printed result,
 * <code>JTable</code> itself will take care of hiding the selection
 * and focus during printing. For additional customizations, your
 * renderers or painting code can customize the look based on the value
 * of {@link javax.swing.JComponent#isPaintingForPrint()}
 * <p>
 * Also, <i>before</i> calling this method you may wish to <i>first</i>
 * modify the state of the table, such as to cancel cell editing or
 * have the user size the table appropriately. However, you must not
 * modify the state of the table <i>after</i> this <code>Printable</code>
 * has been fetched (invalid modifications include changes in size or
 * underlying data). The behavior of the returned <code>Printable</code>
 * is undefined once the table has been changed.
 *
 * @param  printMode     the printing mode that the printable should use
 * @param  headerFormat  a <code>MessageFormat</code> specifying the text to
 *                       be used in printing a header, or NULL for none
 * @param  footerFormat  a <code>MessageFormat</code> specifying the text to
 *                       be used in printing a footer, or NULL for none
 * @return a <code>Printable</code> for printing this JTable
 * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
 *             bool, PrintRequestAttributeSet, bool)
 * @see Printable
 * @see PrinterJob
 *
 * @since 1.5
 */
/*public*/ Printable getPrintable(PrintMode printMode,
                              MessageFormat headerFormat,
                              MessageFormat footerFormat) {

    return new TablePrintable(this, printMode, headerFormat, footerFormat);
}


/**
 * A <code>Printable</code> implementation that wraps another
 * <code>Printable</code>, making it safe for printing on another thread.
 */
private class ThreadSafePrintable implements Printable {

    /** The delegate <code>Printable</code>. */
    private Printable printDelegate;

    /**
     * To communicate any return value when delegating.
     */
    private int retVal;

    /**
     * To communicate any <code>Throwable</code> when delegating.
     */
    private Throwable retThrowable;

    /**
     * Construct a <code>ThreadSafePrintable</code> around the given
     * delegate.
     *
     * @param printDelegate the <code>Printable</code> to delegate to
     */
    /*public*/ ThreadSafePrintable(Printable printDelegate) {
        this->printDelegate = printDelegate;
    }

    /**
     * Prints the specified page into the given {@link Graphics}
     * context, in the specified format.
     * <p>
     * Regardless of what thread this method is called on, all calls into
     * the delegate will be done on the event-dispatch thread.
     *
     * @param   graphics    the context into which the page is drawn
     * @param   pageFormat  the size and orientation of the page being drawn
     * @param   pageIndex   the zero based index of the page to be drawn
     * @return  PAGE_EXISTS if the page is rendered successfully, or
     *          NO_SUCH_PAGE if a non-existent page index is specified
     * @throws  PrinterException if an error causes printing to be aborted
     */
    /*public*/ int print(final Graphics graphics,
                     final PageFormat pageFormat,
                     final int pageIndex) throws PrinterException {

        // We'll use this Runnable
        Runnable runnable = new Runnable() {
            /*public*/ synchronized void run() {
                try {
                    // call into the delegate and save the return value
                    retVal = printDelegate.print(graphics, pageFormat, pageIndex);
                } catch (Throwable throwable) {
                    // save any Throwable to be rethrown
                    retThrowable = throwable;
                } finally {
                    // notify the caller that we're done
                    notifyAll();
                }
            }
        };

        synchronized(runnable) {
            // make sure these are initialized
            retVal = -1;
            retThrowable = NULL;

            // call into the EDT
            SwingUtilities.invokeLater(runnable);

            // wait for the runnable to finish
            while (retVal == -1 && retThrowable == NULL) {
                try {
                    runnable.wait();
                } catch (InterruptedException ie) {
                    // short process, safe to ignore interrupts
                }
            }

            // if the delegate threw a throwable, rethrow it here
            if (retThrowable != NULL) {
                if (retThrowable instanceof PrinterException) {
                    throw (PrinterException)retThrowable;
                } else if (retThrowable instanceof RuntimeException) {
                    throw (RuntimeException)retThrowable;
                } else if (retThrowable instanceof Error) {
                    throw (Error)retThrowable;
                }

                // can not happen
                throw new AssertionError(retThrowable);
            }

            return retVal;
        }
    }
}


/////////////////
// Accessibility support
////////////////

/**
 * Gets the AccessibleContext associated with this JTable.
 * For tables, the AccessibleContext takes the form of an
 * AccessibleJTable.
 * A new AccessibleJTable instance is created if necessary.
 *
 * @return an AccessibleJTable that serves as the
 *         AccessibleContext of this JTable
 */
/*public*/ AccessibleContext getAccessibleContext() {
    if (accessibleContext == NULL) {
        accessibleContext = new AccessibleJTable();
    }
    return accessibleContext;
}

//
// *** should also implement AccessibleSelection?
// *** and what's up with keyboard navigation/manipulation?
//
/**
 * This class implements accessibility support for the
 * <code>JTable</code> class.  It provides an implementation of the
 * Java Accessibility API appropriate to table user-interface elements.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
/*protected*/ class AccessibleJTable extends AccessibleJComponent
implements AccessibleSelection, ListSelectionListener, TableModelListener,
TableColumnModelListener, CellEditorListener, PropertyChangeListener,
AccessibleExtendedTable {

    int lastSelectedRow;
    int lastSelectedCol;

    /**
     * AccessibleJTable constructor
     *
     * @since 1.5
     */
    /*protected*/ AccessibleJTable() {
        super();
        jt->addPropertyChangeListener(this);
        jt->getSelectionModel().addListSelectionListener(this);
        TableColumnModel tcm = jt->getColumnModel();
        tcm.addColumnModelListener(this);
        tcm.getSelectionModel().addListSelectionListener(this);
        jt->getModel().addTableModelListener(this);
        lastSelectedRow = jt->getSelectedRow();
        lastSelectedCol = jt->getSelectedColumn();
    }

// Listeners to track model, etc. changes to as to re-place the other
// listeners

    /**
     * Track changes to selection model, column model, etc. so as to
     * be able to re-place listeners on those in order to pass on
     * information to the Accessibility PropertyChange mechanism
     */
    /*public*/ void propertyChange(PropertyChangeEvent e) {
        String name = e.getPropertyName();
        Object oldValue = e.getOldValue();
        Object newValue = e.getNewValue();

            // re-set tableModel listeners
        if (name.compareTo("model") == 0) {

            if (oldValue != NULL && oldValue instanceof TableModel) {
                ((TableModel) oldValue).removeTableModelListener(this);
            }
            if (newValue != NULL && newValue instanceof TableModel) {
                ((TableModel) newValue).addTableModelListener(this);
            }

            // re-set selectionModel listeners
        } else if (name.compareTo("selectionModel") == 0) {

            Object source = e.getSource();
            if (source == jt) {    // row selection model

                if (oldValue != NULL &&
                    oldValue instanceof ListSelectionModel) {
                    ((ListSelectionModel) oldValue).removeListSelectionListener(this);
                }
                if (newValue != NULL &&
                    newValue instanceof ListSelectionModel) {
                    ((ListSelectionModel) newValue).addListSelectionListener(this);
                }

            } else if (source == jt->getColumnModel()) {

                if (oldValue != NULL &&
                    oldValue instanceof ListSelectionModel) {
                    ((ListSelectionModel) oldValue).removeListSelectionListener(this);
                }
                if (newValue != NULL &&
                    newValue instanceof ListSelectionModel) {
                    ((ListSelectionModel) newValue).addListSelectionListener(this);
                }

            } else {
              //        System.out.println("!!! Bug in source of selectionModel propertyChangeEvent");
            }

            // re-set columnModel listeners
            // and column's selection property listener as well
        } else if (name.compareTo("columnModel") == 0) {

            if (oldValue != NULL && oldValue instanceof TableColumnModel) {
                TableColumnModel tcm = (TableColumnModel) oldValue;
                tcm.removeColumnModelListener(this);
                tcm.getSelectionModel().removeListSelectionListener(this);
            }
            if (newValue != NULL && newValue instanceof TableColumnModel) {
                TableColumnModel tcm = (TableColumnModel) newValue;
                tcm.addColumnModelListener(this);
                tcm.getSelectionModel().addListSelectionListener(this);
            }

            // re-se cellEditor listeners
        } else if (name.compareTo("tableCellEditor") == 0) {

            if (oldValue != NULL && oldValue instanceof TableCellEditor) {
                ((TableCellEditor) oldValue).removeCellEditorListener(this);
            }
            if (newValue != NULL && newValue instanceof TableCellEditor) {
                ((TableCellEditor) newValue).addCellEditorListener(this);
            }
        }
    }


// Listeners to echo changes to the AccessiblePropertyChange mechanism

    /*
     * Describes a change in the accessible table model.
     */
    /*protected*/ class AccessibleJTableModelChange
        implements AccessibleTableModelChange {

        /*protected*/ int type;
        /*protected*/ int firstRow;
        /*protected*/ int lastRow;
        /*protected*/ int firstColumn;
        /*protected*/ int lastColumn;

        /*protected*/ AccessibleJTableModelChange(int type, int firstRow,
                                              int lastRow, int firstColumn,
                                              int lastColumn) {
            this->type = type;
            this->firstRow = firstRow;
            this->lastRow = lastRow;
            this->firstColumn = firstColumn;
            this->lastColumn = lastColumn;
        }

        /*public*/ int getType() {
            return type;
        }

        /*public*/ int getFirstRow() {
            return firstRow;
        }

        /*public*/ int getLastRow() {
            return lastRow;
        }

        /*public*/ int getFirstColumn() {
            return firstColumn;
        }

        /*public*/ int getLastColumn() {
            return lastColumn;
        }
    }

    /**
     * Track changes to the table contents
     */
    /*public*/ void tableChanged(TableModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);
       if (e != NULL) {
           int firstColumn = e.getColumn();
           int lastColumn = e.getColumn();
           if (firstColumn == TableModelEvent.ALL_COLUMNS) {
               firstColumn = 0;
               lastColumn = getColumnCount() - 1;
           }

           // Fire a property change event indicating the table model
           // has changed.
           AccessibleJTableModelChange change =
               new AccessibleJTableModelChange(e.getType(),
                                               e.getFirstRow(),
                                               e.getLastRow(),
                                               firstColumn,
                                               lastColumn);
           firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                              NULL, change);
        }
    }

    /**
     * Track changes to the table contents (row insertions)
     */
    /*public*/ void tableRowsInserted(TableModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);

       // Fire a property change event indicating the table model
       // has changed.
       int firstColumn = e.getColumn();
       int lastColumn = e.getColumn();
       if (firstColumn == TableModelEvent.ALL_COLUMNS) {
           firstColumn = 0;
           lastColumn = getColumnCount() - 1;
       }
       AccessibleJTableModelChange change =
           new AccessibleJTableModelChange(e.getType(),
                                           e.getFirstRow(),
                                           e.getLastRow(),
                                           firstColumn,
                                           lastColumn);
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change);
    }

    /**
     * Track changes to the table contents (row deletions)
     */
    /*public*/ void tableRowsDeleted(TableModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);

       // Fire a property change event indicating the table model
       // has changed.
       int firstColumn = e.getColumn();
       int lastColumn = e.getColumn();
       if (firstColumn == TableModelEvent.ALL_COLUMNS) {
           firstColumn = 0;
           lastColumn = getColumnCount() - 1;
       }
       AccessibleJTableModelChange change =
           new AccessibleJTableModelChange(e.getType(),
                                           e.getFirstRow(),
                                           e.getLastRow(),
                                           firstColumn,
                                           lastColumn);
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change);
    }

    /**
     * Track changes to the table contents (column insertions)
     */
    /*public*/ void columnAdded(TableColumnModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);

       // Fire a property change event indicating the table model
       // has changed.
       int type = AccessibleTableModelChange.INSERT;
       AccessibleJTableModelChange change =
           new AccessibleJTableModelChange(type,
                                           0,
                                           0,
                                           e.getFromIndex(),
                                           e.getToIndex());
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change);
    }

    /**
     * Track changes to the table contents (column deletions)
     */
    /*public*/ void columnRemoved(TableColumnModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);
       // Fire a property change event indicating the table model
       // has changed.
       int type = AccessibleTableModelChange.DELETE;
       AccessibleJTableModelChange change =
           new AccessibleJTableModelChange(type,
                                           0,
                                           0,
                                           e.getFromIndex(),
                                           e.getToIndex());
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change);
    }

    /**
     * Track changes of a column repositioning.
     *
     * @see TableColumnModelListener
     */
    /*public*/ void columnMoved(TableColumnModelEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);

       // Fire property change events indicating the table model
       // has changed.
       int type = AccessibleTableModelChange.DELETE;
       AccessibleJTableModelChange change =
           new AccessibleJTableModelChange(type,
                                           0,
                                           0,
                                           e.getFromIndex(),
                                           e.getFromIndex());
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change);

       int type2 = AccessibleTableModelChange.INSERT;
       AccessibleJTableModelChange change2 =
           new AccessibleJTableModelChange(type2,
                                           0,
                                           0,
                                           e.getToIndex(),
                                           e.getToIndex());
       firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_MODEL_CHANGED,
                          NULL, change2);
    }

    /**
     * Track changes of a column moving due to margin changes.
     *
     * @see TableColumnModelListener
     */
    /*public*/ void columnMarginChanged(ChangeEvent e) {
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);
    }

    /**
     * Track that the selection model of the TableColumnModel changed.
     *
     * @see TableColumnModelListener
     */
    /*public*/ void columnSelectionChanged(ListSelectionEvent e) {
        // we should now re-place our TableColumn listener
    }

    /**
     * Track changes to a cell's contents.
     *
     * Invoked when editing is finished. The changes are saved, the
     * editor object is discarded, and the cell is rendered once again.
     *
     * @see CellEditorListener
     */
    /*public*/ void editingStopped(ChangeEvent e) {
       // it'd be great if we could figure out which cell, and pass that
       // somehow as a parameter
       firePropertyChange(AccessibleContext.ACCESSIBLE_VISIBLE_DATA_PROPERTY,
                          NULL, NULL);
    }

    /**
     * Invoked when editing is canceled. The editor object is discarded
     * and the cell is rendered once again.
     *
     * @see CellEditorListener
     */
    /*public*/ void editingCanceled(ChangeEvent e) {
        // nothing to report, 'cause nothing changed
    }

    /**
     * Track changes to table cell selections
     */
    /*public*/ void valueChanged(ListSelectionEvent e) {
        firePropertyChange(AccessibleContext.ACCESSIBLE_SELECTION_PROPERTY,
                           Boolean.valueOf(false), Boolean.valueOf(true));

        int selectedRow = jt->getSelectedRow();
        int selectedCol = jt->getSelectedColumn();
        if (selectedRow != lastSelectedRow ||
            selectedCol != lastSelectedCol) {
            Accessible oldA = getAccessibleAt(lastSelectedRow,
                                              lastSelectedCol);
            Accessible newA = getAccessibleAt(selectedRow, selectedCol);
            firePropertyChange(AccessibleContext.ACCESSIBLE_ACTIVE_DESCENDANT_PROPERTY,
                               oldA, newA);
             lastSelectedRow = selectedRow;
             lastSelectedCol = selectedCol;
         }
    }




// AccessibleContext support

    /**
     * Get the AccessibleSelection associated with this object.  In the
     * implementation of the Java Accessibility API for this class,
     * return this object, which is responsible for implementing the
     * AccessibleSelection interface on behalf of itself.
     *
     * @return this object
     */
    /*public*/ AccessibleSelection getAccessibleSelection() {
        return this;
    }

    /**
     * Gets the role of this object.
     *
     * @return an instance of AccessibleRole describing the role of the
     * object
     * @see AccessibleRole
     */
    /*public*/ AccessibleRole getAccessibleRole() {
        return AccessibleRole.TABLE;
    }

    /**
     * Returns the <code>Accessible</code> child, if one exists,
     * contained at the local coordinate <code>Point</code>.
     *
     * @param p the point defining the top-left corner of the
     *    <code>Accessible</code>, given in the coordinate space
     *    of the object's parent
     * @return the <code>Accessible</code>, if it exists,
     *    at the specified location; else <code>NULL</code>
     */
    /*public*/ Accessible getAccessibleAt(Point p) {
        int column = columnAtPoint(p);
        int row = rowAtPoint(p);

        if ((column != -1) && (row != -1)) {
            TableColumn aColumn = getColumnModel().getColumn(column);
            TableCellRenderer renderer = aColumn.getCellRenderer();
            if (renderer == NULL) {
                Class<?> columnClass = getColumnClass(column);
                renderer = getDefaultRenderer(columnClass);
            }
            Component component = renderer.getTableCellRendererComponent(
                              jt, NULL, false, false,
                              row, column);
            return new AccessibleJTableCell(jt, row, column,
                  getAccessibleIndexAt(row, column));
        }
        return NULL;
    }

    /**
     * Returns the number of accessible children in the object.  If all
     * of the children of this object implement <code>Accessible</code>,
     * then this method should return the number of children of this object.
     *
     * @return the number of accessible children in the object
     */
    /*public*/ int getAccessibleChildrenCount() {
        return (jt->getColumnCount() * jt->getRowCount());
    }

    /**
     * Returns the nth <code>Accessible</code> child of the object.
     *
     * @param i zero-based index of child
     * @return the nth Accessible child of the object
     */
    /*public*/ Accessible getAccessibleChild(int i) {
        if (i < 0 || i >= getAccessibleChildrenCount()) {
            return NULL;
        } else {
            // children increase across, and then down, for tables
            // (arbitrary decision)
            int column = getAccessibleColumnAtIndex(i);
            int row = getAccessibleRowAtIndex(i);

            TableColumn aColumn = getColumnModel().getColumn(column);
            TableCellRenderer renderer = aColumn.getCellRenderer();
            if (renderer == NULL) {
                Class<?> columnClass = getColumnClass(column);
                renderer = getDefaultRenderer(columnClass);
            }
            Component component = renderer.getTableCellRendererComponent(
                              jt, NULL, false, false,
                              row, column);
            return new AccessibleJTableCell(jt, row, column,
                  getAccessibleIndexAt(row, column));
        }
    }

// AccessibleSelection support

    /**
     * Returns the number of <code>Accessible</code> children
     * currently selected.
     * If no children are selected, the return value will be 0.
     *
     * @return the number of items currently selected
     */
    /*public*/ int getAccessibleSelectionCount() {
        int rowsSel = jt->getSelectedRowCount();
        int colsSel = jt->getSelectedColumnCount();

        if (jt->cellSelectionEnabled) { // a contiguous block
            return rowsSel * colsSel;

        } else {
            // a column swath and a row swath, with a shared block
            if (jt->getRowSelectionAllowed() &&
                jt->getColumnSelectionAllowed()) {
                return rowsSel * jt->getColumnCount() +
                       colsSel * jt->getRowCount() -
                       rowsSel * colsSel;

            // just one or more rows in selection
            } else if (jt->getRowSelectionAllowed()) {
                return rowsSel * jt->getColumnCount();

            // just one or more rows in selection
            } else if (jt->getColumnSelectionAllowed()) {
                return colsSel * jt->getRowCount();

            } else {
                return 0;    // JTable doesn't allow selections
            }
        }
    }

    /**
     * Returns an <code>Accessible</code> representing the
     * specified selected child in the object.  If there
     * isn't a selection, or there are fewer children selected
     * than the integer passed in, the return
     * value will be <code>NULL</code>.
     * <p>Note that the index represents the i-th selected child, which
     * is different from the i-th child.
     *
     * @param i the zero-based index of selected children
     * @return the i-th selected child
     * @see #getAccessibleSelectionCount
     */
    /*public*/ Accessible getAccessibleSelection(int i) {
        if (i < 0 || i > getAccessibleSelectionCount()) {
            return NULL;
        }

        int rowsSel = jt->getSelectedRowCount();
        int colsSel = jt->getSelectedColumnCount();
        int rowIndicies[] = getSelectedRows();
        int colIndicies[] = getSelectedColumns();
        int ttlCols = jt->getColumnCount();
        int ttlRows = jt->getRowCount();
        int r;
        int c;

        if (jt->cellSelectionEnabled) { // a contiguous block
            r = rowIndicies[i / colsSel];
            c = colIndicies[i % colsSel];
            return getAccessibleChild((r * ttlCols) + c);
        } else {

            // a column swath and a row swath, with a shared block
            if (jt->getRowSelectionAllowed() &&
                jt->getColumnSelectionAllowed()) {

                // Situation:
                //   We have a table, like the 6x3 table below,
                //   wherein three colums and one row selected
                //   (selected cells marked with "*", unselected "0"):
                //
                //            0 * 0 * * 0
                //            * * * * * *
                //            0 * 0 * * 0
                //

                // State machine below walks through the array of
                // selected rows in two states: in a selected row,
                // and not in one; continuing until we are in a row
                // in which the ith selection exists.  Then we return
                // the appropriate cell.  In the state machine, we
                // always do rows above the "current" selected row first,
                // then the cells in the selected row.  If we're done
                // with the state machine before finding the requested
                // selected child, we handle the rows below the last
                // selected row at the end.
                //
                int curIndex = i;
                final int IN_ROW = 0;
                final int NOT_IN_ROW = 1;
                int state = (rowIndicies[0] == 0 ? IN_ROW : NOT_IN_ROW);
                int j = 0;
                int prevRow = -1;
                while (j < rowIndicies.length) {
                    switch (state) {

                    case IN_ROW:   // on individual row full of selections
                        if (curIndex < ttlCols) { // it's here!
                            c = curIndex % ttlCols;
                            r = rowIndicies[j];
                            return getAccessibleChild((r * ttlCols) + c);
                        } else {                               // not here
                            curIndex -= ttlCols;
                        }
                        // is the next row in table selected or not?
                        if (j + 1 == rowIndicies.length ||
                            rowIndicies[j] != rowIndicies[j+1] - 1) {
                            state = NOT_IN_ROW;
                            prevRow = rowIndicies[j];
                        }
                        j++;  // we didn't return earlier, so go to next row
                        break;

                    case NOT_IN_ROW:  // sparse bunch of rows of selections
                        if (curIndex <
                            (colsSel * (rowIndicies[j] -
                            (prevRow == -1 ? 0 : (prevRow + 1))))) {

                            // it's here!
                            c = colIndicies[curIndex % colsSel];
                            r = (j > 0 ? rowIndicies[j-1] + 1 : 0)
                                + curIndex / colsSel;
                            return getAccessibleChild((r * ttlCols) + c);
                        } else {                               // not here
                            curIndex -= colsSel * (rowIndicies[j] -
                            (prevRow == -1 ? 0 : (prevRow + 1)));
                        }
                        state = IN_ROW;
                        break;
                    }
                }
                // we got here, so we didn't find it yet; find it in
                // the last sparse bunch of rows
                if (curIndex <
                    (colsSel * (ttlRows -
                    (prevRow == -1 ? 0 : (prevRow + 1))))) { // it's here!
                    c = colIndicies[curIndex % colsSel];
                    r = rowIndicies[j-1] + curIndex / colsSel + 1;
                    return getAccessibleChild((r * ttlCols) + c);
                } else {                               // not here
                    // we shouldn't get to this spot in the code!
//                      System.out.println("Bug in AccessibleJTable.getAccessibleSelection()");
                }

            // one or more rows selected
            } else if (jt->getRowSelectionAllowed()) {
                c = i % ttlCols;
                r = rowIndicies[i / ttlCols];
                return getAccessibleChild((r * ttlCols) + c);

            // one or more columns selected
            } else if (jt->getColumnSelectionAllowed()) {
                c = colIndicies[i % colsSel];
                r = i / colsSel;
                return getAccessibleChild((r * ttlCols) + c);
            }
        }
        return NULL;
    }

    /**
     * Determines if the current child of this object is selected.
     *
     * @param i the zero-based index of the child in this
     *    <code>Accessible</code> object
     * @return true if the current child of this object is selected
     * @see AccessibleContext#getAccessibleChild
     */
    /*public*/ bool isAccessibleChildSelected(int i) {
        int column = getAccessibleColumnAtIndex(i);
        int row = getAccessibleRowAtIndex(i);
        return jt->isCellSelected(row, column);
    }

    /**
     * Adds the specified <code>Accessible</code> child of the
     * object to the object's selection.  If the object supports
     * multiple selections, the specified child is added to
     * any existing selection, otherwise
     * it replaces any existing selection in the object.  If the
     * specified child is already selected, this method has no effect.
     * <p>
     * This method only works on <code>JTable</code>s which have
     * individual cell selection enabled.
     *
     * @param i the zero-based index of the child
     * @see AccessibleContext#getAccessibleChild
     */
    /*public*/ void addAccessibleSelection(int i) {
        // TIGER - 4495286
        int column = getAccessibleColumnAtIndex(i);
        int row = getAccessibleRowAtIndex(i);
        jt->changeSelection(row, column, true, false);
    }

    /**
     * Removes the specified child of the object from the object's
     * selection.  If the specified item isn't currently selected, this
     * method has no effect.
     * <p>
     * This method only works on <code>JTables</code> which have
     * individual cell selection enabled.
     *
     * @param i the zero-based index of the child
     * @see AccessibleContext#getAccessibleChild
     */
    /*public*/ void removeAccessibleSelection(int i) {
        if (jt->cellSelectionEnabled) {
            int column = getAccessibleColumnAtIndex(i);
            int row = getAccessibleRowAtIndex(i);
            jt->removeRowSelectionInterval(row, row);
            jt->removeColumnSelectionInterval(column, column);
        }
    }

    /**
     * Clears the selection in the object, so that no children in the
     * object are selected.
     */
    /*public*/ void clearAccessibleSelection() {
        jt->clearSelection();
    }

    /**
     * Causes every child of the object to be selected, but only
     * if the <code>JTable</code> supports multiple selections,
     * and if individual cell selection is enabled.
     */
    /*public*/ void selectAllAccessibleSelection() {
        if (jt->cellSelectionEnabled) {
            jt->selectAll();
        }
    }

    // begin AccessibleExtendedTable implementation -------------

    /**
     * Returns the row number of an index in the table.
     *
     * @param index the zero-based index in the table
     * @return the zero-based row of the table if one exists;
     * otherwise -1.
     * @since 1.4
     */
    /*public*/ int getAccessibleRow(int index) {
        return getAccessibleRowAtIndex(index);
    }

    /**
     * Returns the column number of an index in the table.
     *
     * @param index the zero-based index in the table
     * @return the zero-based column of the table if one exists;
     * otherwise -1.
     * @since 1.4
     */
    /*public*/ int getAccessibleColumn(int index) {
        return getAccessibleColumnAtIndex(index);
    }

    /**
     * Returns the index at a row and column in the table.
     *
     * @param r zero-based row of the table
     * @param c zero-based column of the table
     * @return the zero-based index in the table if one exists;
     * otherwise -1.
     * @since 1.4
     */
    /*public*/ int getAccessibleIndex(int r, int c) {
        return getAccessibleIndexAt(r, c);
    }

    // end of AccessibleExtendedTable implementation ------------

    // start of AccessibleTable implementation ------------------

    private Accessible caption;
    private Accessible summary;
    private Accessible [] rowDescription;
    private Accessible [] columnDescription;

    /**
     * Gets the <code>AccessibleTable</code> associated with this
     * object.  In the implementation of the Java Accessibility
     * API for this class, return this object, which is responsible
     * for implementing the <code>AccessibleTables</code> interface
     * on behalf of itself.
     *
     * @return this object
     * @since 1.3
     */
    /*public*/ AccessibleTable getAccessibleTable() {
        return this;
    }

    /**
     * Returns the caption for the table.
     *
     * @return the caption for the table
     * @since 1.3
     */
    /*public*/ Accessible getAccessibleCaption() {
        return this->caption;
    }

    /**
     * Sets the caption for the table.
     *
     * @param a the caption for the table
     * @since 1.3
     */
    /*public*/ void setAccessibleCaption(Accessible a) {
        Accessible oldCaption = caption;
        this->caption = a;
        firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_CAPTION_CHANGED,
                           oldCaption, this->caption);
    }

    /**
     * Returns the summary description of the table.
     *
     * @return the summary description of the table
     * @since 1.3
     */
    /*public*/ Accessible getAccessibleSummary() {
        return this->summary;
    }

    /**
     * Sets the summary description of the table.
     *
     * @param a the summary description of the table
     * @since 1.3
     */
    /*public*/ void setAccessibleSummary(Accessible a) {
        Accessible oldSummary = summary;
        this->summary = a;
        firePropertyChange(AccessibleContext.ACCESSIBLE_TABLE_SUMMARY_CHANGED,
                           oldSummary, this->summary);
    }

    /*
     * Returns the total number of rows in this table.
     *
     * @return the total number of rows in this table
     */
    /*public*/ int getAccessibleRowCount() {
        return jt->getRowCount();
    }

    /*
     * Returns the total number of columns in the table.
     *
     * @return the total number of columns in the table
     */
    /*public*/ int getAccessibleColumnCount() {
        return jt->getColumnCount();
    }

    /*
     * Returns the <code>Accessible</code> at a specified row
     * and column in the table.
     *
     * @param r zero-based row of the table
     * @param c zero-based column of the table
     * @return the <code>Accessible</code> at the specified row and column
     * in the table
     */
    /*public*/ Accessible getAccessibleAt(int r, int c) {
        return getAccessibleChild((r * getAccessibleColumnCount()) + c);
    }

    /**
     * Returns the number of rows occupied by the <code>Accessible</code>
     * at a specified row and column in the table.
     *
     * @return the number of rows occupied by the <code>Accessible</code>
     *     at a specified row and column in the table
     * @since 1.3
     */
    /*public*/ int getAccessibleRowExtentAt(int r, int c) {
        return 1;
    }

    /**
     * Returns the number of columns occupied by the
     * <code>Accessible</code> at a given (row, column).
     *
     * @return the number of columns occupied by the <code>Accessible</code>
     *     at a specified row and column in the table
     * @since 1.3
     */
    /*public*/ int getAccessibleColumnExtentAt(int r, int c) {
        return 1;
    }

    /**
     * Returns the row headers as an <code>AccessibleTable</code>.
     *
     * @return an <code>AccessibleTable</code> representing the row
     * headers
     * @since 1.3
     */
    /*public*/ AccessibleTable getAccessibleRowHeader() {
        // row headers are not supported
        return NULL;
    }

    /**
     * Sets the row headers as an <code>AccessibleTable</code>.
     *
     * @param a an <code>AccessibleTable</code> representing the row
     *  headers
     * @since 1.3
     */
    /*public*/ void setAccessibleRowHeader(AccessibleTable a) {
        // row headers are not supported
    }

    /**
     * Returns the column headers as an <code>AccessibleTable</code>.
     *
     *  @return an <code>AccessibleTable</code> representing the column
     *          headers, or <code>NULL</code> if the table header is
     *          <code>NULL</code>
     * @since 1.3
     */
    /*public*/ AccessibleTable getAccessibleColumnHeader() {
        JTableHeader header = jt->getTableHeader();
        return header == NULL ? NULL : new AccessibleTableHeader(header);
    }

    /*
     * Private class representing a table column header
     */
    private class AccessibleTableHeader implements AccessibleTable {
        private JTableHeader header;
        private TableColumnModel headerModel;

        AccessibleTableHeader(JTableHeader header) {
            this->header = header;
            this->headerModel = header.getColumnModel();
        }

        /**
         * Returns the caption for the table.
         *
         * @return the caption for the table
         */
        /*public*/ Accessible getAccessibleCaption() { return NULL; }


        /**
         * Sets the caption for the table.
         *
         * @param a the caption for the table
         */
        /*public*/ void setAccessibleCaption(Accessible a) {}

        /**
         * Returns the summary description of the table.
         *
         * @return the summary description of the table
         */
        /*public*/ Accessible getAccessibleSummary() { return NULL; }

        /**
         * Sets the summary description of the table
         *
         * @param a the summary description of the table
         */
        /*public*/ void setAccessibleSummary(Accessible a) {}

        /**
         * Returns the number of rows in the table.
         *
         * @return the number of rows in the table
         */
        /*public*/ int getAccessibleRowCount() { return 1; }

        /**
         * Returns the number of columns in the table.
         *
         * @return the number of columns in the table
         */
        /*public*/ int getAccessibleColumnCount() {
            return headerModel.getColumnCount();
        }

        /**
         * Returns the Accessible at a specified row and column
         * in the table.
         *
         * @param row zero-based row of the table
         * @param column zero-based column of the table
         * @return the Accessible at the specified row and column
         */
        /*public*/ Accessible getAccessibleAt(int row, int column) {


            // TIGER - 4715503
            TableColumn aColumn = headerModel.getColumn(column);
            TableCellRenderer renderer = aColumn.getHeaderRenderer();
            if (renderer == NULL) {
                renderer = header.getDefaultRenderer();
            }
            Component component = renderer.getTableCellRendererComponent(
                              header.getTable(),
                              aColumn.getHeaderValue(), false, false,
                              -1, column);

            return new AccessibleJTableHeaderCell(row, column,
                                                  jt->getTableHeader(),
                                                  component);
        }

        /**
         * Returns the number of rows occupied by the Accessible at
         * a specified row and column in the table.
         *
         * @return the number of rows occupied by the Accessible at a
         * given specified (row, column)
         */
        /*public*/ int getAccessibleRowExtentAt(int r, int c) { return 1; }

        /**
         * Returns the number of columns occupied by the Accessible at
         * a specified row and column in the table.
         *
         * @return the number of columns occupied by the Accessible at a
         * given specified row and column
         */
        /*public*/ int getAccessibleColumnExtentAt(int r, int c) { return 1; }

        /**
         * Returns the row headers as an AccessibleTable.
         *
         * @return an AccessibleTable representing the row
         * headers
         */
        /*public*/ AccessibleTable getAccessibleRowHeader() { return NULL; }

        /**
         * Sets the row headers.
         *
         * @param table an AccessibleTable representing the
         * row headers
         */
        /*public*/ void setAccessibleRowHeader(AccessibleTable table) {}

        /**
         * Returns the column headers as an AccessibleTable.
         *
         * @return an AccessibleTable representing the column
         * headers
         */
        /*public*/ AccessibleTable getAccessibleColumnHeader() { return NULL; }

        /**
         * Sets the column headers.
         *
         * @param table an AccessibleTable representing the
         * column headers
         * @since 1.3
         */
        /*public*/ void setAccessibleColumnHeader(AccessibleTable table) {}

        /**
         * Returns the description of the specified row in the table.
         *
         * @param r zero-based row of the table
         * @return the description of the row
         * @since 1.3
         */
        /*public*/ Accessible getAccessibleRowDescription(int r) { return NULL; }

        /**
         * Sets the description text of the specified row of the table.
         *
         * @param r zero-based row of the table
         * @param a the description of the row
         * @since 1.3
         */
        /*public*/ void setAccessibleRowDescription(int r, Accessible a) {}

        /**
         * Returns the description text of the specified column in the table.
         *
         * @param c zero-based column of the table
         * @return the text description of the column
         * @since 1.3
         */
        /*public*/ Accessible getAccessibleColumnDescription(int c) { return NULL; }

        /**
         * Sets the description text of the specified column in the table.
         *
         * @param c zero-based column of the table
         * @param a the text description of the column
         * @since 1.3
         */
        /*public*/ void setAccessibleColumnDescription(int c, Accessible a) {}

        /**
         * Returns a bool value indicating whether the accessible at
         * a specified row and column is selected.
         *
         * @param r zero-based row of the table
         * @param c zero-based column of the table
         * @return the bool value true if the accessible at the
         * row and column is selected. Otherwise, the bool value
         * false
         * @since 1.3
         */
        /*public*/ bool isAccessibleSelected(int r, int c) { return false; }

        /**
         * Returns a bool value indicating whether the specified row
         * is selected.
         *
         * @param r zero-based row of the table
         * @return the bool value true if the specified row is selected.
         * Otherwise, false.
         * @since 1.3
         */
        /*public*/ bool isAccessibleRowSelected(int r) { return false; }

        /**
         * Returns a bool value indicating whether the specified column
         * is selected.
         *
         * @param c zero-based column of the table
         * @return the bool value true if the specified column is selected.
         * Otherwise, false.
         * @since 1.3
         */
        /*public*/ bool isAccessibleColumnSelected(int c) { return false; }

        /**
         * Returns the selected rows in a table.
         *
         * @return an array of selected rows where each element is a
         * zero-based row of the table
         * @since 1.3
         */
        /*public*/ int [] getSelectedAccessibleRows() { return new int[0]; }

        /**
         * Returns the selected columns in a table.
         *
         * @return an array of selected columns where each element is a
         * zero-based column of the table
         * @since 1.3
         */
        /*public*/ int [] getSelectedAccessibleColumns() { return new int[0]; }
    }


    /**
     * Sets the column headers as an <code>AccessibleTable</code>.
     *
     * @param a an <code>AccessibleTable</code> representing the
     * column headers
     * @since 1.3
     */
    /*public*/ void setAccessibleColumnHeader(AccessibleTable a) {
        // XXX not implemented
    }

    /**
     * Returns the description of the specified row in the table.
     *
     * @param r zero-based row of the table
     * @return the description of the row
     * @since 1.3
     */
    /*public*/ Accessible getAccessibleRowDescription(int r) {
        if (r < 0 || r >= getAccessibleRowCount()) {
            throw new IllegalArgumentException(Integer.toString(r));
        }
        if (rowDescription == NULL) {
            return NULL;
        } else {
            return rowDescription[r];
        }
    }

    /**
     * Sets the description text of the specified row of the table.
     *
     * @param r zero-based row of the table
     * @param a the description of the row
     * @since 1.3
     */
    /*public*/ void setAccessibleRowDescription(int r, Accessible a) {
        if (r < 0 || r >= getAccessibleRowCount()) {
            throw new IllegalArgumentException(Integer.toString(r));
        }
        if (rowDescription == NULL) {
            int numRows = getAccessibleRowCount();
            rowDescription = new Accessible[numRows];
        }
        rowDescription[r] = a;
    }

    /**
     * Returns the description of the specified column in the table.
     *
     * @param c zero-based column of the table
     * @return the description of the column
     * @since 1.3
     */
    /*public*/ Accessible getAccessibleColumnDescription(int c) {
        if (c < 0 || c >= getAccessibleColumnCount()) {
            throw new IllegalArgumentException(Integer.toString(c));
        }
        if (columnDescription == NULL) {
            return NULL;
        } else {
            return columnDescription[c];
        }
    }

    /**
     * Sets the description text of the specified column of the table.
     *
     * @param c zero-based column of the table
     * @param a the description of the column
     * @since 1.3
     */
    /*public*/ void setAccessibleColumnDescription(int c, Accessible a) {
        if (c < 0 || c >= getAccessibleColumnCount()) {
            throw new IllegalArgumentException(Integer.toString(c));
        }
        if (columnDescription == NULL) {
            int numColumns = getAccessibleColumnCount();
            columnDescription = new Accessible[numColumns];
        }
        columnDescription[c] = a;
    }

    /**
     * Returns a bool value indicating whether the accessible at a
     * given (row, column) is selected.
     *
     * @param r zero-based row of the table
     * @param c zero-based column of the table
     * @return the bool value true if the accessible at (row, column)
     *     is selected; otherwise, the bool value false
     * @since 1.3
     */
    /*public*/ bool isAccessibleSelected(int r, int c) {
        return jt->isCellSelected(r, c);
    }

    /**
     * Returns a bool value indicating whether the specified row
     * is selected.
     *
     * @param r zero-based row of the table
     * @return the bool value true if the specified row is selected;
     *     otherwise, false
     * @since 1.3
     */
    /*public*/ bool isAccessibleRowSelected(int r) {
        return jt->isRowSelected(r);
    }

    /**
     * Returns a bool value indicating whether the specified column
     * is selected.
     *
     * @param c zero-based column of the table
     * @return the bool value true if the specified column is selected;
     *     otherwise, false
     * @since 1.3
     */
    /*public*/ bool isAccessibleColumnSelected(int c) {
        return jt->isColumnSelected(c);
    }

    /**
     * Returns the selected rows in a table.
     *
     * @return an array of selected rows where each element is a
     *     zero-based row of the table
     * @since 1.3
     */
    /*public*/ int [] getSelectedAccessibleRows() {
        return jt->getSelectedRows();
    }

    /**
     * Returns the selected columns in a table.
     *
     * @return an array of selected columns where each element is a
     *     zero-based column of the table
     * @since 1.3
     */
    /*public*/ int [] getSelectedAccessibleColumns() {
        return jt->getSelectedColumns();
    }

    /**
     * Returns the row at a given index into the table.
     *
     * @param i zero-based index into the table
     * @return the row at a given index
     * @since 1.3
     */
    /*public*/ int getAccessibleRowAtIndex(int i) {
        int columnCount = getAccessibleColumnCount();
        if (columnCount == 0) {
            return -1;
        } else {
            return (i / columnCount);
        }
    }

    /**
     * Returns the column at a given index into the table.
     *
     * @param i zero-based index into the table
     * @return the column at a given index
     * @since 1.3
     */
    /*public*/ int getAccessibleColumnAtIndex(int i) {
        int columnCount = getAccessibleColumnCount();
        if (columnCount == 0) {
            return -1;
        } else {
            return (i % columnCount);
        }
    }

    /**
     * Returns the index at a given (row, column) in the table.
     *
     * @param r zero-based row of the table
     * @param c zero-based column of the table
     * @return the index into the table
     * @since 1.3
     */
    /*public*/ int getAccessibleIndexAt(int r, int c) {
        return ((r * getAccessibleColumnCount()) + c);
    }

    // end of AccessibleTable implementation --------------------

    /**
     * The class provides an implementation of the Java Accessibility
     * API appropriate to table cells.
     */
    /*protected*/ class AccessibleJTableCell extends AccessibleContext
        implements Accessible, AccessibleComponent {

        private JTable parent;
        private int row;
        private int column;
        private int index;

        /**
         *  Constructs an <code>AccessibleJTableHeaderEntry</code>.
         * @since 1.4
         */
        /*public*/ AccessibleJTableCell(JTable t, int r, int c, int i) {
            parent = t;
            row = r;
            column = c;
            index = i;
            this->setAccessibleParent(parent);
        }

        /**
         * Gets the <code>AccessibleContext</code> associated with this
         * component. In the implementation of the Java Accessibility
         * API for this class, return this object, which is its own
         * <code>AccessibleContext</code>.
         *
         * @return this object
         */
        /*public*/ AccessibleContext getAccessibleContext() {
            return this;
        }

        /**
         * Gets the AccessibleContext for the table cell renderer.
         *
         * @return the <code>AccessibleContext</code> for the table
         * cell renderer if one exists;
         * otherwise, returns <code>NULL</code>.
         * @since 1.6
         */
        /*protected*/ AccessibleContext getCurrentAccessibleContext() {
            TableColumn aColumn = getColumnModel().getColumn(column);
            TableCellRenderer renderer = aColumn.getCellRenderer();
            if (renderer == NULL) {
                Class<?> columnClass = getColumnClass(column);
                renderer = getDefaultRenderer(columnClass);
            }
            Component component = renderer.getTableCellRendererComponent(
                              jt, getValueAt(row, column),
                              false, false, row, column);
            if (component instanceof Accessible) {
                return component.getAccessibleContext();
            } else {
                return NULL;
            }
        }

        /**
         * Gets the table cell renderer component.
         *
         * @return the table cell renderer component if one exists;
         * otherwise, returns <code>NULL</code>.
         * @since 1.6
         */
        /*protected*/ Component getCurrentComponent() {
            TableColumn aColumn = getColumnModel().getColumn(column);
            TableCellRenderer renderer = aColumn.getCellRenderer();
            if (renderer == NULL) {
                Class<?> columnClass = getColumnClass(column);
                renderer = getDefaultRenderer(columnClass);
            }
            return renderer.getTableCellRendererComponent(
                              jt, NULL, false, false,
                              row, column);
        }

    // AccessibleContext methods

        /**
         * Gets the accessible name of this object.
         *
         * @return the localized name of the object; <code>NULL</code>
         *     if this object does not have a name
         */
        /*public*/ String getAccessibleName() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                String name = ac.getAccessibleName();
                if ((name != NULL) && (name != "")) {
                    // return the cell renderer's AccessibleName
                    return name;
                }
            }
            if ((accessibleName != NULL) && (accessibleName != "")) {
                return accessibleName;
            } else {
                // fall back to the client property
                return (String)getClientProperty(AccessibleContext.ACCESSIBLE_NAME_PROPERTY);
            }
        }

        /**
         * Sets the localized accessible name of this object.
         *
         * @param s the new localized name of the object
         */
        /*public*/ void setAccessibleName(String s) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.setAccessibleName(s);
            } else {
                super.setAccessibleName(s);
            }
        }

        //
        // *** should check toolTip text for desc. (needs MouseEvent)
        //
        /**
         * Gets the accessible description of this object.
         *
         * @return the localized description of the object;
         *     <code>NULL</code> if this object does not have
         *     a description
         */
        /*public*/ String getAccessibleDescription() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleDescription();
            } else {
                return super.getAccessibleDescription();
            }
        }

        /**
         * Sets the accessible description of this object.
         *
         * @param s the new localized description of the object
         */
        /*public*/ void setAccessibleDescription(String s) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.setAccessibleDescription(s);
            } else {
                super.setAccessibleDescription(s);
            }
        }

        /**
         * Gets the role of this object.
         *
         * @return an instance of <code>AccessibleRole</code>
         *      describing the role of the object
         * @see AccessibleRole
         */
        /*public*/ AccessibleRole getAccessibleRole() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleRole();
            } else {
                return AccessibleRole.UNKNOWN;
            }
        }

        /**
         * Gets the state set of this object.
         *
         * @return an instance of <code>AccessibleStateSet</code>
         *     containing the current state set of the object
         * @see AccessibleState
         */
        /*public*/ AccessibleStateSet getAccessibleStateSet() {
            AccessibleContext ac = getCurrentAccessibleContext();
            AccessibleStateSet as = NULL;

            if (ac != NULL) {
                as = ac.getAccessibleStateSet();
            }
            if (as == NULL) {
                as = new AccessibleStateSet();
            }
            Rectangle rjt = jt->getVisibleRect();
            Rectangle rcell = jt->getCellRect(row, column, false);
            if (rjt.intersects(rcell)) {
                as.add(AccessibleState.SHOWING);
            } else {
                if (as.contains(AccessibleState.SHOWING)) {
                     as.remove(AccessibleState.SHOWING);
                }
            }
            if (parent.isCellSelected(row, column)) {
                as.add(AccessibleState.SELECTED);
            } else if (as.contains(AccessibleState.SELECTED)) {
                as.remove(AccessibleState.SELECTED);
            }
            if ((row == getSelectedRow()) && (column == getSelectedColumn())) {
                as.add(AccessibleState.ACTIVE);
            }
            as.add(AccessibleState.TRANSIENT);
            return as;
        }

        /**
         * Gets the <code>Accessible</code> parent of this object.
         *
         * @return the Accessible parent of this object;
         *     <code>NULL</code> if this object does not
         *     have an <code>Accessible</code> parent
         */
        /*public*/ Accessible getAccessibleParent() {
            return parent;
        }

        /**
         * Gets the index of this object in its accessible parent.
         *
         * @return the index of this object in its parent; -1 if this
         *     object does not have an accessible parent
         * @see #getAccessibleParent
         */
        /*public*/ int getAccessibleIndexInParent() {
            return index;
        }

        /**
         * Returns the number of accessible children in the object.
         *
         * @return the number of accessible children in the object
         */
        /*public*/ int getAccessibleChildrenCount() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleChildrenCount();
            } else {
                return 0;
            }
        }

        /**
         * Returns the specified <code>Accessible</code> child of the
         * object.
         *
         * @param i zero-based index of child
         * @return the <code>Accessible</code> child of the object
         */
        /*public*/ Accessible getAccessibleChild(int i) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                Accessible accessibleChild = ac.getAccessibleChild(i);
                ac.setAccessibleParent(this);
                return accessibleChild;
            } else {
                return NULL;
            }
        }

        /**
         * Gets the locale of the component. If the component
         * does not have a locale, then the locale of its parent
         * is returned.
         *
         * @return this component's locale; if this component does
         *    not have a locale, the locale of its parent is returned
         * @exception IllegalComponentStateException if the
         *    <code>Component</code> does not have its own locale
         *    and has not yet been added to a containment hierarchy
         *    such that the locale can be determined from the
         *    containing parent
         * @see #setLocale
         */
        /*public*/ Locale getLocale() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getLocale();
            } else {
                return NULL;
            }
        }

        /**
         * Adds a <code>PropertyChangeListener</code> to the listener list.
         * The listener is registered for all properties.
         *
         * @param l  the <code>PropertyChangeListener</code>
         *     to be added
         */
        /*public*/ void addPropertyChangeListener(PropertyChangeListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.addPropertyChangeListener(l);
            } else {
                super.addPropertyChangeListener(l);
            }
        }

        /**
         * Removes a <code>PropertyChangeListener</code> from the
         * listener list. This removes a <code>PropertyChangeListener</code>
         * that was registered for all properties.
         *
         * @param l  the <code>PropertyChangeListener</code>
         *    to be removed
         */
        /*public*/ void removePropertyChangeListener(PropertyChangeListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.removePropertyChangeListener(l);
            } else {
                super.removePropertyChangeListener(l);
            }
        }

        /**
         * Gets the <code>AccessibleAction</code> associated with this
         * object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleAction</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleAction getAccessibleAction() {
            return getCurrentAccessibleContext().getAccessibleAction();
        }

        /**
         * Gets the <code>AccessibleComponent</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleComponent</code>, or
         *    <code>NULL</code>
         */
        /*public*/ AccessibleComponent getAccessibleComponent() {
            return this; // to override getBounds()
        }

        /**
         * Gets the <code>AccessibleSelection</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleSelection</code>, or
         *    <code>NULL</code>
         */
        /*public*/ AccessibleSelection getAccessibleSelection() {
            return getCurrentAccessibleContext().getAccessibleSelection();
        }

        /**
         * Gets the <code>AccessibleText</code> associated with this
         * object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleText</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleText getAccessibleText() {
            return getCurrentAccessibleContext().getAccessibleText();
        }

        /**
         * Gets the <code>AccessibleValue</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleValue</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleValue getAccessibleValue() {
            return getCurrentAccessibleContext().getAccessibleValue();
        }


    // AccessibleComponent methods

        /**
         * Gets the background color of this object.
         *
         * @return the background color, if supported, of the object;
         *     otherwise, <code>NULL</code>
         */
        /*public*/ Color getBackground() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getBackground();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getBackground();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the background color of this object.
         *
         * @param c the new <code>Color</code> for the background
         */
        /*public*/ void setBackground(Color c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setBackground(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setBackground(c);
                }
            }
        }

        /**
         * Gets the foreground color of this object.
         *
         * @return the foreground color, if supported, of the object;
         *     otherwise, <code>NULL</code>
         */
        /*public*/ Color getForeground() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getForeground();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getForeground();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the foreground color of this object.
         *
         * @param c the new <code>Color</code> for the foreground
         */
        /*public*/ void setForeground(Color c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setForeground(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setForeground(c);
                }
            }
        }

        /**
         * Gets the <code>Cursor</code> of this object.
         *
         * @return the <code>Cursor</code>, if supported,
         *    of the object; otherwise, <code>NULL</code>
         */
        /*public*/ Cursor getCursor() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getCursor();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getCursor();
                } else {
                    Accessible ap = getAccessibleParent();
                    if (ap instanceof AccessibleComponent) {
                        return ((AccessibleComponent) ap).getCursor();
                    } else {
                        return NULL;
                    }
                }
            }
        }

        /**
         * Sets the <code>Cursor</code> of this object.
         *
         * @param c the new <code>Cursor</code> for the object
         */
        /*public*/ void setCursor(Cursor c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setCursor(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setCursor(c);
                }
            }
        }

        /**
         * Gets the <code>Font</code> of this object.
         *
         * @return the <code>Font</code>,if supported,
         *   for the object; otherwise, <code>NULL</code>
         */
        /*public*/ Font getFont() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getFont();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getFont();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the <code>Font</code> of this object.
         *
         * @param f the new <code>Font</code> for the object
         */
        /*public*/ void setFont(Font f) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setFont(f);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setFont(f);
                }
            }
        }

        /**
         * Gets the <code>FontMetrics</code> of this object.
         *
         * @param f the <code>Font</code>
         * @return the <code>FontMetrics</code> object, if supported;
         *    otherwise <code>NULL</code>
         * @see #getFont
         */
        /*public*/ FontMetrics getFontMetrics(Font f) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getFontMetrics(f);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getFontMetrics(f);
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Determines if the object is enabled.
         *
         * @return true if object is enabled; otherwise, false
         */
        /*public*/ bool isEnabled() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isEnabled();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isEnabled();
                } else {
                    return false;
                }
            }
        }

        /**
         * Sets the enabled state of the object.
         *
         * @param b if true, enables this object; otherwise, disables it
         */
        /*public*/ void setEnabled(bool b) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setEnabled(b);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setEnabled(b);
                }
            }
        }

        /**
         * Determines if this object is visible.  Note: this means that the
         * object intends to be visible; however, it may not in fact be
         * showing on the screen because one of the objects that this object
         * is contained by is not visible.  To determine if an object is
         * showing on the screen, use <code>isShowing</code>.
         *
         * @return true if object is visible; otherwise, false
         */
        /*public*/ bool isVisible() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isVisible();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isVisible();
                } else {
                    return false;
                }
            }
        }

        /**
         * Sets the visible state of the object.
         *
         * @param b if true, shows this object; otherwise, hides it
         */
        /*public*/ void setVisible(bool b) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setVisible(b);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setVisible(b);
                }
            }
        }

        /**
         * Determines if the object is showing.  This is determined
         * by checking the visibility of the object and ancestors
         * of the object.  Note: this will return true even if the
         * object is obscured by another (for example,
         * it happens to be underneath a menu that was pulled down).
         *
         * @return true if the object is showing; otherwise, false
         */
        /*public*/ bool isShowing() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                if (ac.getAccessibleParent() != NULL) {
                    return ((AccessibleComponent) ac).isShowing();
                } else {
                    // Fixes 4529616 - AccessibleJTableCell.isShowing()
                    // returns false when the cell on the screen
                    // if no parent
                    return isVisible();
                }
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isShowing();
                } else {
                    return false;
                }
            }
        }

        /**
         * Checks whether the specified point is within this
         * object's bounds, where the point's x and y coordinates
         * are defined to be relative to the coordinate system of
         * the object.
         *
         * @param p the <code>Point</code> relative to the
         *    coordinate system of the object
         * @return true if object contains <code>Point</code>;
         *    otherwise false
         */
        /*public*/ bool contains(Point p) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                Rectangle r = ((AccessibleComponent) ac).getBounds();
                return r.contains(p);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    Rectangle r = c.getBounds();
                    return r.contains(p);
                } else {
                    return getBounds().contains(p);
                }
            }
        }

        /**
         * Returns the location of the object on the screen.
         *
         * @return location of object on screen -- can be
         *    <code>NULL</code> if this object is not on the screen
         */
        /*public*/ Point getLocationOnScreen() {
            if (parent != NULL && parent.isShowing()) {
                Point parentLocation = parent.getLocationOnScreen();
                Point componentLocation = getLocation();
                componentLocation.translate(parentLocation.x, parentLocation.y);
                return componentLocation;
            } else {
                return NULL;
            }
        }

        /**
         * Gets the location of the object relative to the parent
         * in the form of a point specifying the object's
         * top-left corner in the screen's coordinate space.
         *
         * @return an instance of <code>Point</code> representing
         *    the top-left corner of the object's bounds in the
         *    coordinate space of the screen; <code>NULL</code> if
         *    this object or its parent are not on the screen
         */
        /*public*/ Point getLocation() {
            if (parent != NULL) {
                Rectangle r = parent.getCellRect(row, column, false);
                if (r != NULL) {
                    return r.getLocation();
                }
            }
            return NULL;
        }

        /**
         * Sets the location of the object relative to the parent.
         */
        /*public*/ void setLocation(Point p) {
//              if ((parent != NULL)  && (parent.contains(p))) {
//                  ensureIndexIsVisible(indexInParent);
//              }
        }

        /*public*/ Rectangle getBounds() {
            if (parent != NULL) {
                return parent.getCellRect(row, column, false);
            } else {
                return NULL;
            }
        }

        /*public*/ void setBounds(Rectangle r) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setBounds(r);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setBounds(r);
                }
            }
        }

        /*public*/ Dimension getSize() {
            if (parent != NULL) {
                Rectangle r = parent.getCellRect(row, column, false);
                if (r != NULL) {
                    return r.getSize();
                }
            }
            return NULL;
        }

        /*public*/ void setSize (Dimension d) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setSize(d);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setSize(d);
                }
            }
        }

        /*public*/ Accessible getAccessibleAt(Point p) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getAccessibleAt(p);
            } else {
                return NULL;
            }
        }

        /*public*/ bool isFocusTraversable() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isFocusTraversable();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isFocusTraversable();
                } else {
                    return false;
                }
            }
        }

        /*public*/ void requestFocus() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).requestFocus();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.requestFocus();
                }
            }
        }

        /*public*/ void addFocusListener(FocusListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).addFocusListener(l);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.addFocusListener(l);
                }
            }
        }

        /*public*/ void removeFocusListener(FocusListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).removeFocusListener(l);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.removeFocusListener(l);
                }
            }
        }

    } // inner class AccessibleJTableCell

    // Begin AccessibleJTableHeader ========== // TIGER - 4715503

    /**
     * This class implements accessibility for JTable header cells.
     */
    private class AccessibleJTableHeaderCell extends AccessibleContext
        implements Accessible, AccessibleComponent {

        private int row;
        private int column;
        private JTableHeader parent;
        private Component rendererComponent;

        /**
         * Constructs an <code>AccessibleJTableHeaderEntry</code> instance.
         *
         * @param row header cell row index
         * @param column header cell column index
         * @param parent header cell parent
         * @param rendererComponent component that renders the header cell
         */
        /*public*/ AccessibleJTableHeaderCell(int row, int column,
                                          JTableHeader parent,
                                          Component rendererComponent) {
            this->row = row;
            this->column = column;
            this->parent = parent;
            this->rendererComponent = rendererComponent;
            this->setAccessibleParent(parent);
        }

        /**
         * Gets the <code>AccessibleContext</code> associated with this
         * component. In the implementation of the Java Accessibility
         * API for this class, return this object, which is its own
         * <code>AccessibleContext</code>.
         *
         * @return this object
         */
        /*public*/ AccessibleContext getAccessibleContext() {
            return this;
        }

        /*
         * Returns the AccessibleContext for the header cell
         * renderer.
         */
        private AccessibleContext getCurrentAccessibleContext() {
            return rendererComponent.getAccessibleContext();
        }

        /*
         * Returns the component that renders the header cell.
         */
        private Component getCurrentComponent() {
            return rendererComponent;
        }

        // AccessibleContext methods ==========

        /**
         * Gets the accessible name of this object.
         *
         * @return the localized name of the object; <code>NULL</code>
         *     if this object does not have a name
         */
        /*public*/ String getAccessibleName() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                String name = ac.getAccessibleName();
                if ((name != NULL) && (name != "")) {
                    return ac.getAccessibleName();
                }
            }
            if ((accessibleName != NULL) && (accessibleName != "")) {
                return accessibleName;
            } else {
                return NULL;
            }
        }

        /**
         * Sets the localized accessible name of this object.
         *
         * @param s the new localized name of the object
         */
        /*public*/ void setAccessibleName(String s) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.setAccessibleName(s);
            } else {
                super.setAccessibleName(s);
            }
        }

        /**
         * Gets the accessible description of this object.
         *
         * @return the localized description of the object;
         *     <code>NULL</code> if this object does not have
         *     a description
         */
        /*public*/ String getAccessibleDescription() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleDescription();
            } else {
                return super.getAccessibleDescription();
            }
        }

        /**
         * Sets the accessible description of this object.
         *
         * @param s the new localized description of the object
         */
        /*public*/ void setAccessibleDescription(String s) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.setAccessibleDescription(s);
            } else {
                super.setAccessibleDescription(s);
            }
        }

        /**
         * Gets the role of this object.
         *
         * @return an instance of <code>AccessibleRole</code>
         *      describing the role of the object
         * @see AccessibleRole
         */
        /*public*/ AccessibleRole getAccessibleRole() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleRole();
            } else {
                return AccessibleRole.UNKNOWN;
            }
        }

        /**
         * Gets the state set of this object.
         *
         * @return an instance of <code>AccessibleStateSet</code>
         *     containing the current state set of the object
         * @see AccessibleState
         */
        /*public*/ AccessibleStateSet getAccessibleStateSet() {
            AccessibleContext ac = getCurrentAccessibleContext();
            AccessibleStateSet as = NULL;

            if (ac != NULL) {
                as = ac.getAccessibleStateSet();
            }
            if (as == NULL) {
                as = new AccessibleStateSet();
            }
            Rectangle rjt = jt->getVisibleRect();
            Rectangle rcell = jt->getCellRect(row, column, false);
            if (rjt.intersects(rcell)) {
                as.add(AccessibleState.SHOWING);
            } else {
                if (as.contains(AccessibleState.SHOWING)) {
                     as.remove(AccessibleState.SHOWING);
                }
            }
            if (jt->isCellSelected(row, column)) {
                as.add(AccessibleState.SELECTED);
            } else if (as.contains(AccessibleState.SELECTED)) {
                as.remove(AccessibleState.SELECTED);
            }
            if ((row == getSelectedRow()) && (column == getSelectedColumn())) {
                as.add(AccessibleState.ACTIVE);
            }
            as.add(AccessibleState.TRANSIENT);
            return as;
        }

        /**
         * Gets the <code>Accessible</code> parent of this object.
         *
         * @return the Accessible parent of this object;
         *     <code>NULL</code> if this object does not
         *     have an <code>Accessible</code> parent
         */
        /*public*/ Accessible getAccessibleParent() {
            return parent;
        }

        /**
         * Gets the index of this object in its accessible parent.
         *
         * @return the index of this object in its parent; -1 if this
         *     object does not have an accessible parent
         * @see #getAccessibleParent
         */
        /*public*/ int getAccessibleIndexInParent() {
            return column;
        }

        /**
         * Returns the number of accessible children in the object.
         *
         * @return the number of accessible children in the object
         */
        /*public*/ int getAccessibleChildrenCount() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getAccessibleChildrenCount();
            } else {
                return 0;
            }
        }

        /**
         * Returns the specified <code>Accessible</code> child of the
         * object.
         *
         * @param i zero-based index of child
         * @return the <code>Accessible</code> child of the object
         */
        /*public*/ Accessible getAccessibleChild(int i) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                Accessible accessibleChild = ac.getAccessibleChild(i);
                ac.setAccessibleParent(this);
                return accessibleChild;
            } else {
                return NULL;
            }
        }

        /**
         * Gets the locale of the component. If the component
         * does not have a locale, then the locale of its parent
         * is returned.
         *
         * @return this component's locale; if this component does
         *    not have a locale, the locale of its parent is returned
         * @exception IllegalComponentStateException if the
         *    <code>Component</code> does not have its own locale
         *    and has not yet been added to a containment hierarchy
         *    such that the locale can be determined from the
         *    containing parent
         * @see #setLocale
         */
        /*public*/ Locale getLocale() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                return ac.getLocale();
            } else {
                return NULL;
            }
        }

        /**
         * Adds a <code>PropertyChangeListener</code> to the listener list.
         * The listener is registered for all properties.
         *
         * @param l  the <code>PropertyChangeListener</code>
         *     to be added
         */
        /*public*/ void addPropertyChangeListener(PropertyChangeListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.addPropertyChangeListener(l);
            } else {
                super.addPropertyChangeListener(l);
            }
        }

        /**
         * Removes a <code>PropertyChangeListener</code> from the
         * listener list. This removes a <code>PropertyChangeListener</code>
         * that was registered for all properties.
         *
         * @param l  the <code>PropertyChangeListener</code>
         *    to be removed
         */
        /*public*/ void removePropertyChangeListener(PropertyChangeListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac != NULL) {
                ac.removePropertyChangeListener(l);
            } else {
                super.removePropertyChangeListener(l);
            }
        }

        /**
         * Gets the <code>AccessibleAction</code> associated with this
         * object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleAction</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleAction getAccessibleAction() {
            return getCurrentAccessibleContext().getAccessibleAction();
        }

        /**
         * Gets the <code>AccessibleComponent</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleComponent</code>, or
         *    <code>NULL</code>
         */
        /*public*/ AccessibleComponent getAccessibleComponent() {
            return this; // to override getBounds()
        }

        /**
         * Gets the <code>AccessibleSelection</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleSelection</code>, or
         *    <code>NULL</code>
         */
        /*public*/ AccessibleSelection getAccessibleSelection() {
            return getCurrentAccessibleContext().getAccessibleSelection();
        }

        /**
         * Gets the <code>AccessibleText</code> associated with this
         * object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleText</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleText getAccessibleText() {
            return getCurrentAccessibleContext().getAccessibleText();
        }

        /**
         * Gets the <code>AccessibleValue</code> associated with
         * this object if one exists.  Otherwise returns <code>NULL</code>.
         *
         * @return the <code>AccessibleValue</code>, or <code>NULL</code>
         */
        /*public*/ AccessibleValue getAccessibleValue() {
            return getCurrentAccessibleContext().getAccessibleValue();
        }


        // AccessibleComponent methods ==========

        /**
         * Gets the background color of this object.
         *
         * @return the background color, if supported, of the object;
         *     otherwise, <code>NULL</code>
         */
        /*public*/ Color getBackground() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getBackground();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getBackground();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the background color of this object.
         *
         * @param c the new <code>Color</code> for the background
         */
        /*public*/ void setBackground(Color c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setBackground(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setBackground(c);
                }
            }
        }

        /**
         * Gets the foreground color of this object.
         *
         * @return the foreground color, if supported, of the object;
         *     otherwise, <code>NULL</code>
         */
        /*public*/ Color getForeground() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getForeground();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getForeground();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the foreground color of this object.
         *
         * @param c the new <code>Color</code> for the foreground
         */
        /*public*/ void setForeground(Color c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setForeground(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setForeground(c);
                }
            }
        }

        /**
         * Gets the <code>Cursor</code> of this object.
         *
         * @return the <code>Cursor</code>, if supported,
         *    of the object; otherwise, <code>NULL</code>
         */
        /*public*/ Cursor getCursor() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getCursor();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getCursor();
                } else {
                    Accessible ap = getAccessibleParent();
                    if (ap instanceof AccessibleComponent) {
                        return ((AccessibleComponent) ap).getCursor();
                    } else {
                        return NULL;
                    }
                }
            }
        }

        /**
         * Sets the <code>Cursor</code> of this object.
         *
         * @param c the new <code>Cursor</code> for the object
         */
        /*public*/ void setCursor(Cursor c) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setCursor(c);
            } else {
                Component cp = getCurrentComponent();
                if (cp != NULL) {
                    cp.setCursor(c);
                }
            }
        }

        /**
         * Gets the <code>Font</code> of this object.
         *
         * @return the <code>Font</code>,if supported,
         *   for the object; otherwise, <code>NULL</code>
         */
        /*public*/ Font getFont() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getFont();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getFont();
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Sets the <code>Font</code> of this object.
         *
         * @param f the new <code>Font</code> for the object
         */
        /*public*/ void setFont(Font f) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setFont(f);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setFont(f);
                }
            }
        }

        /**
         * Gets the <code>FontMetrics</code> of this object.
         *
         * @param f the <code>Font</code>
         * @return the <code>FontMetrics</code> object, if supported;
         *    otherwise <code>NULL</code>
         * @see #getFont
         */
        /*public*/ FontMetrics getFontMetrics(Font f) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getFontMetrics(f);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.getFontMetrics(f);
                } else {
                    return NULL;
                }
            }
        }

        /**
         * Determines if the object is enabled.
         *
         * @return true if object is enabled; otherwise, false
         */
        /*public*/ bool isEnabled() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isEnabled();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isEnabled();
                } else {
                    return false;
                }
            }
        }

        /**
         * Sets the enabled state of the object.
         *
         * @param b if true, enables this object; otherwise, disables it
         */
        /*public*/ void setEnabled(bool b) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setEnabled(b);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setEnabled(b);
                }
            }
        }

        /**
         * Determines if this object is visible.  Note: this means that the
         * object intends to be visible; however, it may not in fact be
         * showing on the screen because one of the objects that this object
         * is contained by is not visible.  To determine if an object is
         * showing on the screen, use <code>isShowing</code>.
         *
         * @return true if object is visible; otherwise, false
         */
        /*public*/ bool isVisible() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isVisible();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isVisible();
                } else {
                    return false;
                }
            }
        }

        /**
         * Sets the visible state of the object.
         *
         * @param b if true, shows this object; otherwise, hides it
         */
        /*public*/ void setVisible(bool b) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setVisible(b);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setVisible(b);
                }
            }
        }

        /**
         * Determines if the object is showing.  This is determined
         * by checking the visibility of the object and ancestors
         * of the object.  Note: this will return true even if the
         * object is obscured by another (for example,
         * it happens to be underneath a menu that was pulled down).
         *
         * @return true if the object is showing; otherwise, false
         */
        /*public*/ bool isShowing() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                if (ac.getAccessibleParent() != NULL) {
                    return ((AccessibleComponent) ac).isShowing();
                } else {
                    // Fixes 4529616 - AccessibleJTableCell.isShowing()
                    // returns false when the cell on the screen
                    // if no parent
                    return isVisible();
                }
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isShowing();
                } else {
                    return false;
                }
            }
        }

        /**
         * Checks whether the specified point is within this
         * object's bounds, where the point's x and y coordinates
         * are defined to be relative to the coordinate system of
         * the object.
         *
         * @param p the <code>Point</code> relative to the
         *    coordinate system of the object
         * @return true if object contains <code>Point</code>;
         *    otherwise false
         */
        /*public*/ bool contains(Point p) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                Rectangle r = ((AccessibleComponent) ac).getBounds();
                return r.contains(p);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    Rectangle r = c.getBounds();
                    return r.contains(p);
                } else {
                    return getBounds().contains(p);
                }
            }
        }

        /**
         * Returns the location of the object on the screen.
         *
         * @return location of object on screen -- can be
         *    <code>NULL</code> if this object is not on the screen
         */
        /*public*/ Point getLocationOnScreen() {
            if (parent != NULL && parent.isShowing()) {
                Point parentLocation = parent.getLocationOnScreen();
                Point componentLocation = getLocation();
                componentLocation.translate(parentLocation.x, parentLocation.y);
                return componentLocation;
            } else {
                return NULL;
            }
        }

        /**
         * Gets the location of the object relative to the parent
         * in the form of a point specifying the object's
         * top-left corner in the screen's coordinate space.
         *
         * @return an instance of <code>Point</code> representing
         *    the top-left corner of the object's bounds in the
         *    coordinate space of the screen; <code>NULL</code> if
         *    this object or its parent are not on the screen
         */
        /*public*/ Point getLocation() {
            if (parent != NULL) {
                Rectangle r = parent.getHeaderRect(column);
                if (r != NULL) {
                    return r.getLocation();
                }
            }
            return NULL;
        }

        /**
         * Sets the location of the object relative to the parent.
         * @param p the new position for the top-left corner
         * @see #getLocation
         */
        /*public*/ void setLocation(Point p) {
        }

        /**
         * Gets the bounds of this object in the form of a Rectangle object.
         * The bounds specify this object's width, height, and location
         * relative to its parent.
         *
         * @return A rectangle indicating this component's bounds; NULL if
         * this object is not on the screen.
         * @see #contains
         */
        /*public*/ Rectangle getBounds() {
            if (parent != NULL) {
                return parent.getHeaderRect(column);
            } else {
                return NULL;
            }
        }

        /**
         * Sets the bounds of this object in the form of a Rectangle object.
         * The bounds specify this object's width, height, and location
         * relative to its parent.
         *
         * @param r rectangle indicating this component's bounds
         * @see #getBounds
         */
        /*public*/ void setBounds(Rectangle r) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setBounds(r);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setBounds(r);
                }
            }
        }

        /**
         * Returns the size of this object in the form of a Dimension object.
         * The height field of the Dimension object contains this object's
         * height, and the width field of the Dimension object contains this
         * object's width.
         *
         * @return A Dimension object that indicates the size of this component;
         * NULL if this object is not on the screen
         * @see #setSize
         */
        /*public*/ Dimension getSize() {
            if (parent != NULL) {
                Rectangle r = parent.getHeaderRect(column);
                if (r != NULL) {
                    return r.getSize();
                }
            }
            return NULL;
        }

        /**
         * Resizes this object so that it has width and height.
         *
         * @param d The dimension specifying the new size of the object.
         * @see #getSize
         */
        /*public*/ void setSize (Dimension d) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).setSize(d);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.setSize(d);
                }
            }
        }

        /**
         * Returns the Accessible child, if one exists, contained at the local
         * coordinate Point.
         *
         * @param p The point relative to the coordinate system of this object.
         * @return the Accessible, if it exists, at the specified location;
         * otherwise NULL
         */
        /*public*/ Accessible getAccessibleAt(Point p) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).getAccessibleAt(p);
            } else {
                return NULL;
            }
        }

        /**
         * Returns whether this object can accept focus or not.   Objects that
         * can accept focus will also have the AccessibleState.FOCUSABLE state
         * set in their AccessibleStateSets.
         *
         * @return true if object can accept focus; otherwise false
         * @see AccessibleContext#getAccessibleStateSet
         * @see AccessibleState#FOCUSABLE
         * @see AccessibleState#FOCUSED
         * @see AccessibleStateSet
         */
        /*public*/ bool isFocusTraversable() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                return ((AccessibleComponent) ac).isFocusTraversable();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    return c.isFocusTraversable();
                } else {
                    return false;
                }
            }
        }

        /**
         * Requests focus for this object.  If this object cannot accept focus,
         * nothing will happen.  Otherwise, the object will attempt to take
         * focus.
         * @see #isFocusTraversable
         */
        /*public*/ void requestFocus() {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).requestFocus();
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.requestFocus();
                }
            }
        }

        /**
         * Adds the specified focus listener to receive focus events from this
         * component.
         *
         * @param l the focus listener
         * @see #removeFocusListener
         */
        /*public*/ void addFocusListener(FocusListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).addFocusListener(l);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.addFocusListener(l);
                }
            }
        }

        /**
         * Removes the specified focus listener so it no longer receives focus
         * events from this component.
         *
         * @param l the focus listener
         * @see #addFocusListener
         */
        /*public*/ void removeFocusListener(FocusListener l) {
            AccessibleContext ac = getCurrentAccessibleContext();
            if (ac instanceof AccessibleComponent) {
                ((AccessibleComponent) ac).removeFocusListener(l);
            } else {
                Component c = getCurrentComponent();
                if (c != NULL) {
                    c.removeFocusListener(l);
                }
            }
        }

    } // inner class AccessibleJTableHeaderCell

}  // inner class AccessibleJTable

//}  // End of Class JTable
#endif
void JTable::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue)
{
 emit propertyChange(new PropertyChangeEvent(this, propertyName, oldValue, newValue));
}
/*public*/ int JTable::getSelectedRow()
{
 return currentIndex().row();
}

 /*public*/ int JTable::getSelectedColumn()
 {
  return currentIndex().column();
 }

/*public*/ QVector<int>* JTable::getSelectedRows()
{
 QList<QModelIndex> list = selectedIndexes();
 QVector<int>* out = new QVector<int>();
 QListIterator<QModelIndex> it(list);
 while(it.hasNext())
  out->append(it.next().row());
 return out;
}

/**
 * Selects the rows from <code>index0</code> to <code>index1</code>,
 * inclusive.
 *
 * @exception IllegalArgumentException      if <code>index0</code> or
 *                                          <code>index1</code> lie outside
 *                                          [0, <code>getRowCount()</code>-1]
 * @param   index0 one end of the interval
 * @param   index1 the other end of the interval
 */
/*public*/ void JTable::setRowSelectionInterval(int /*index0*/, int index1) {
   // selectionModel.setSelectionInterval(boundRow(index0), boundRow(index1));
}


/*public*/ void JTable::onPropertyChange(PropertyChangeEvent* evt)
{
 if(qobject_cast<TableColumn*>(evt->source) != NULL )
 {
  QString name = evt->getPropertyName();
  if(name == "width" || name == "preferredWidth")
  {
   TableColumn* tc = qobject_cast<TableColumn*>(evt->source);
   if(name == "width")
   {
     setColumnWidth(tc->getModelIndex(), tc->getWidth());
   }
   if(name == "preferredWidth")
   {
    setColumnWidth(tc->getModelIndex(), tc->getPreferredWidth());
   }
  }
 }
}

 void JTable::setName(QString name) { this->name = name;}
 QString JTable::getName() { return name;}


/**
 * Specifies whether the selection should be updated after sorting.
 * If true, on sorting the selection is reset such that
 * the same rows, in terms of the model, remain selected.  The default
 * is true.
 *
 * @param update whether or not to update the selection on sorting
 * @beaninfo
 *        bound: true
 *       expert: true
 *  description: Whether or not to update the selection on sorting
 * @since 1.6
 */
/*public*/ void JTable::setUpdateSelectionOnSort(bool update) {
    if (updateSelectionOnSort != update) {
        updateSelectionOnSort = update;
        firePropertyChange("updateSelectionOnSort", !update, update);
    }
}

/**
 * Returns true if the selection should be updated after sorting.
 *
 * @return whether to update the selection on a sort
 * @since 1.6
 */
/*public*/ bool JTable::getUpdateSelectionOnSort() {
    return updateSelectionOnSort;
}
/**
 * Sets the <code>RowSorter</code>.  <code>RowSorter</code> is used
 * to provide sorting and filtering to a <code>JTable</code>.
 * <p>
 * This method clears the selection and resets any variable row heights.
 * <p>
 * This method fires a <code>PropertyChangeEvent</code> when appropriate,
 * with the property name <code>"rowSorter"</code>.  For
 * backward-compatibility, this method fires an additional event with the
 * property name <code>"sorter"</code>.
 * <p>
 * If the underlying model of the <code>RowSorter</code> differs from
 * that of this <code>JTable</code> undefined behavior will result.
 *
 * @param sorter the <code>RowSorter</code>; <code>NULL</code> turns
 *        sorting off
 * @see javax.swing.table.TableRowSorter
 * @beaninfo
 *        bound: true
 *  description: The table's RowSorter
 * @since 1.6
 */
/*public*/ void JTable::setRowSorter(RowSorter/*<? extends TableModel>*/* sorter) {
    RowSorter/*<? extends TableModel>*/* oldRowSorter = NULL;
    if (sortManager != NULL) {
        oldRowSorter = sortManager->sorter;
        sortManager->dispose();
        sortManager = NULL;
    }
    rowModel = NULL;
    clearSelectionAndLeadAnchor();
    if (sorter != NULL) {
        sortManager = new SortManager(sorter, this);
    }
//         resizeAndRepaint();
    firePropertyChange("rowSorter", VPtr<RowSorter>::asQVariant(oldRowSorter), VPtr<RowSorter>::asQVariant(sorter));
    firePropertyChange("sorter", VPtr<RowSorter>::asQVariant(oldRowSorter), VPtr<RowSorter>::asQVariant(sorter));
}

/**
 * Returns the object responsible for sorting.
 *
 * @return the object responsible for sorting
 * @since 1.6
 */
/*public*/ RowSorter/*<? extends TableModel>*/* JTable::getRowSorter() {
    return (sortManager != NULL) ? sortManager->sorter : NULL;
}

/*private*/ void JTable::On_columnResized(int col, int oldWidth, int newWidth)
{
 TableColumnModel* tm = getColumnModel();
 if(col > tm->getColumnCount()) return;
 TableColumn* tc = tm->getColumn(col);
 if(tc == nullptr)
  return;
 tc->firePropertyChange("preferredWidth", oldWidth, newWidth);
 emit propertyChange(new PropertyChangeEvent(tc, "preferredWidth", oldWidth, newWidth));
}

/*private*/ void JTable::sectionClicked(int logicalindex) // SLOT
{
 if(qobject_cast<QAbstractProxyModel*>(model()) != NULL && isSortingEnabled())
 {

 }
}
/**
 * Maps the index of the row in terms of the view to the
 * underlying <code>TableModel</code>.  If the contents of the
 * model are not sorted the model and view indices are the same.
 *
 * @param viewRowIndex the index of the row in the view
 * @return the index of the corresponding row in the model
 * @throws IndexOutOfBoundsException if sorting is enabled and passed an
 *         index outside the range of the <code>JTable</code> as
 *         determined by the method <code>getRowCount</code>
 * @see javax.swing.table.TableRowSorter
 * @see #getRowCount
 * @since 1.6
 */
/*public*/ int JTable::convertRowIndexToModel(int viewRowIndex) {
 QAbstractItemModel* model = this->model();
    RowSorter* sorter = getRowSorter();
    if (sorter != NULL) {
        return sorter->convertRowIndexToModel(viewRowIndex);
    }
    return viewRowIndex;
}

/*public*/ int JTable::rowHeight()
{
 if(this->model() && this->model()->rowCount()>0)
 {
  _rowHeight = QTableView::rowHeight(0);
  return _rowHeight;
 }
 return 10;
}


/*public*/ void JTable::setDefaultRenderer(QString, QObject *)
{

}


/*public*/ int JTable::columnAtPoint(QPoint p)
{
    return columnAt(p.x());
}

/*public*/ void JTable::doLayout()
{
 for (int i = 0; i < getModel()->columnCount(); i++)
 {

    TableCellEditor* editor = getColumnModel()->getColumn(i)->getCellEditor();
    if(editor)
    {
     QItemDelegate* delegate = qobject_cast<QItemDelegate*>(editor->self());
     if(delegate != itemDelegateForColumn(i))
     {
       setItemDelegateForColumn(i, delegate);
     }
    }
 }
}

/*public*/ TableColumn* JTable::getColumn(QString name)
{
 for(int i =0; i < getColumnCount(); i++)
 {
  if(getColumnName(i) == name)
  {
   return getColumnModel()->getColumn(i);
  }
 }
 return nullptr;
}

/*public*/ QAbstractItemDelegate* JTable::getCellRenderer(int row, int column){
    return itemDelegate(model()->index(row, column));
}

/*public*/ QAbstractItemDelegate *JTable::getCellEditor(int row, int column){
    return itemDelegate(model()->index(row, column));
}

