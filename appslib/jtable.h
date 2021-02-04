#ifndef JTABLE_H
#define JTABLE_H

#include <QTableView>
#include "tablemodel.h"
#include "javaqt_global.h"
#include "pushbuttondelegate.h"
#include "tabledelegates.h"

class AbstractTableModel;
class DefaultListSelectionModel;
class ModelChange;
class RowSorterEvent;
class ListSelectionEvent;
class SortManager;
class RowSorter;
class PrintService;
class PrintRequestAttributeSet;
class Logger;
class TableModelEvent;
class TableColumn;
class PropertyChangeEvent;
class Throwable;
class QAbstractItemModel;
class DropLocation;
class TableColumnModel;
class ListSelectionModel;
class TableCellEditor;
class PropertyChangeListener;
class SizeSequence;
class DropMode;
class JAVAQTSHARED_EXPORT JTable : public QTableView
{
 Q_OBJECT
public:
 explicit JTable(QWidget *parent = 0);
 enum OPTIONS
 {
  /** Do not adjust column widths automatically; use a horizontal scrollbar instead. */
  AUTO_RESIZE_OFF = 0,

  /** When a column is adjusted in the UI, adjust the next column the opposite way. */
  AUTO_RESIZE_NEXT_COLUMN = 1,

  /** During UI adjustment, change subsequent columns to preserve the total width;
    * this is the default behavior. */
  AUTO_RESIZE_SUBSEQUENT_COLUMNS = 2,

  /** During all resize operations, apply adjustments to the last column only. */
  AUTO_RESIZE_LAST_COLUMN = 3,

  /** During all resize operations, proportionately resize all columns. */
  AUTO_RESIZE_ALL_COLUMNS = 4

 };
 Q_ENUM(OPTIONS)
 /**
  * Printing modes, used in printing <code>JTable</code>s.
  *
  * @see #print(JTable.PrintMode, MessageFormat, MessageFormat,
  *             bool, PrintRequestAttributeSet, bool)
  * @see #getPrintable
  * @since 1.5
  */
 /*public*/ enum PrintMode {

     /**
      * Printing mode that prints the table at its current size,
      * spreading both columns and rows across multiple pages if necessary.
      */
     NORMAL,

     /**
      * Printing mode that scales the output smaller, if necessary,
      * to fit the table's entire width (and thereby all columns) on each page;
      * Rows are spread across multiple pages as necessary.
      */
     FIT_WIDTH
 };
 Q_ENUM(PrintMode)
 /*public*/ JTable(TableModel* dm, QWidget *parent = 0);
 /*public*/ JTable(QAbstractItemModel* dm, QWidget *parent = 0);
 /*public*/ JTable(TableModel* dm, TableColumnModel* cm, QWidget *parent = 0);
 /*public*/ JTable(TableModel* dm, TableColumnModel* cm, DefaultListSelectionModel *sm, QWidget *parent);
// /*public*/ JTable(int numRows, int numColumns, QObject* parent);
 /*public*/ void setAutoCreateColumnsFromModel(bool autoCreateColumnsFromModel);
 /*public*/ bool getAutoCreateColumnsFromModel();
 /*public*/ void createDefaultColumnsFromModel();
 /*public*/ TableColumnModel* getColumnModel();
 /*public*/ void setModel(QAbstractItemModel *dataModel);
 /*public*/ QAbstractItemModel *getModel();
 /*public*/ void setColumnModel(TableColumnModel* columnModel);
 /*public*/ void setSelectionModel(QItemSelectionModel *newModel);
 /*public*/ DefaultListSelectionModel* getSelectionModel();
 /*public*/ void addColumn(TableColumn* aColumn);
 /*public*/ void removeColumn(TableColumn* aColumn) ;
 /*public*/ void moveColumn(int column, int targetColumn);
 /*public*/ void tableChanged(TableModelEvent* e);
 /*public*/ bool print(PrintMode printMode,
                      QString headerFormat,
                       QString footerFormat); //throw (PrinterException)
 /*public*/ bool print(PrintMode printMode,
                      QString headerFormat,
                      QString footerFormat,
                      bool showPrintDialog,
                      PrintRequestAttributeSet* attr,
                      bool interactive); /*throws PrinterException,
                                                  HeadlessException*/
/*public*/ bool print(PrintMode printMode,
                     QString headerFormat,
                     QString footerFormat,
                     bool showPrintDialog,
                     PrintRequestAttributeSet* attr,
                     bool interactive,
                     PrintService* service); /*throws PrinterException,
                                                  HeadlessException*/
 /*public*/ int getRowHeight();
 /*public*/ int getRowHeight(int);
 /*public*/ int getSelectedRow();
 /*public*/ int getSelectedColumn();
 /*public*/ QVector<int>* getSelectedRows();
 /*public*/ void setRowSelectionInterval(int index0, int index1);
 /*public*/ int rowAtPoint(QPoint point);
 void setName(QString name);
 QString getName();
 /*public*/ QString getColumnName(int column);
 /*public*/ TableColumn* getColumn(QString name);
 /*public*/ void setRowSorter(RowSorter/*<? extends TableModel>*/* sorter);
 RowSorter* getRowSorter();
 /*public*/ void setUpdateSelectionOnSort(bool update);
 /*public*/ bool getUpdateSelectionOnSort();
 /*public*/ int convertRowIndexToModel(int viewRowIndex);
 /*public*/ int getRowCount();
 /*public*/ int getColumnCount();
 /*public*/ int convertColumnIndexToModel(int viewColumnIndex) ;
 /*public*/ int convertColumnIndexToView(int modelColumnIndex);
 /*public*/ int convertRowIndexToView(int modelRowIndex);
 /*public*/ void setRowHeight(int rowHeight);
 /*public*/ void setAutoResizeMode(int mode);
 /*public*/ void setIntercellSpacing(QSize intercellSpacing);
 /*public*/ void setRowMargin(int rowMargin);
 /*public*/ int getRowMargin();
 /*public*/ void setRowHeight(int row, int rowHeight);
 /*public*/ QVariant getValueAt(int row, int column);
 /*public*/ int rowHeight();
 /*public*/ QHeaderView* getTableHeader();
 /*public*/ void setSelectionMode(int selectionMode);
 /*public*/ void setRowSelectionAllowed(bool);
 /*public*/ bool getRowSelectionAllowed();
 /*public*/ void setGridColor(QColor gridColor);
 /*public*/ QColor getGridColor();
 /*public*/ void setShowGrid(bool showGrid);
 /*public*/ void setShowHorizontalLines(bool showHorizontalLines) ;
 /*public*/ void setShowVerticalLines(bool showVerticalLines);
 /*public*/ bool getShowHorizontalLines();
 /*public*/ bool getShowVerticalLines();
 /*public*/ void setDefaultRenderer(QString, QObject*);
 /*public*/ void setDefaultEditor(QString, QStyledItemDelegate *);
 /*public*/ void doLayout();
 /*public*/ int columnAtPoint(QPoint);
 /*public*/ QAbstractItemDelegate *getCellRenderer(int row, int column);
 /*public*/ QAbstractItemDelegate* getCellEditor(int row, int column);
 /*public*/ void clearSelection();

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
 void On_columnsAboutToBeInserted(QModelIndex, int, int);
 /*public*/void onPropertyChange(PropertyChangeEvent* evt);

private:
 //
 // Private state
 //

 // WARNING: If you directly access this field you should also change the
 // SortManager.modelRowSizes field as well.
 /*private*/ SizeSequence* rowModel;
 /*private*/ bool dragEnabled;
 /*private*/ bool surrendersFocusOnKeystroke;
 /*private*/ PropertyChangeListener* editorRemover;// = null;
 /**
  * The last value of getValueIsAdjusting from the column selection models
  * columnSelectionChanged notification. Used to test if a repaint is
  * needed.
  */
 /*private*/ bool columnSelectionAdjusting;
 /**
  * The last value of getValueIsAdjusting from the row selection models
  * valueChanged notification. Used to test if a repaint is needed.
  */
 /*private*/ bool rowSelectionAdjusting;

 /**
  * To communicate errors between threads during printing.
  */
 /*private*/ Throwable* printError;

 /**
  * True when setRowHeight(int) has been invoked.
  */
 /*private*/ bool isRowHeightSet;

 /**
  * If true, on a sort the selection is reset.
  */
 /*private*/ bool updateSelectionOnSort;

 /**
  * Information used in sorting.
  */
 /*private*/ /*transient*/ SortManager* sortManager;

 /**
  * If true, when sorterChanged is invoked it's value is ignored.
  */
 /*private*/ bool ignoreSortChange;

 /**
  * Whether or not sorterChanged has been invoked.
  */
 /*private*/ bool sorterChanged;

 /**
  * If true, any time the model changes a new RowSorter is set.
  */
 /*private*/ bool autoCreateRowSorter;

 /**
  * Whether or not the table always fills the viewport height.
  * @see #setFillsViewportHeight
  * @see #getScrollableTracksViewportHeight
  */
 /*private*/ bool fillsViewportHeight;

 /**
  * The drop mode for this component.
  */
 /*private*/ DropMode* dropMode;// = DropMode::USE_SELECTION;

 /**
  * The drop location.
  */
 /*private*/ /*transient*/ DropLocation* dropLocation;
 void common(QAbstractItemModel *dm, TableColumnModel* cm, DefaultListSelectionModel *sm);
 void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
 /*private*/ void clearSelectionAndLeadAnchor();
 Logger * log;
 QString name;
 RowSorter* rowSorter;
 /*private*/ int convertRowIndexToModel(RowSorterEvent* e, int viewIndex);
 /*private*/ QVector<int>* convertSelectionToModel(RowSorterEvent* e);
 /*private*/ void restoreSortingSelection(QVector<int>* selection, int lead,
                                          ModelChange* change);
 /*private*/ void restoreSortingEditingRow(int editingRow);
 /*private*/ int convertRowIndexToView(int modelIndex, ModelChange *change);
 /*private*/ void notifySorter(ModelChange* change);
 /*private*/ SizeSequence* getRowModel();
 /*private*/ QObject* defaultItemDelegate;

private slots:
 void On_columnResized(int col, int oldWidth, int newWidth);
 /*private*/ void sectionClicked(int logicalindex); // SLOT


protected:
 //
 // Instance Variables
 //

 /** The <code>TableModel</code> of the table. */
 /*protected*/ QAbstractItemModel*        dataModel;

 /** The <code>TableColumnModel</code> of the table. */
 /*protected*/ TableColumnModel*  columnModel = nullptr;

 /** The <code>ListSelectionModel</code> of the table, used to keep track of row selections. */
 /*protected*/ DefaultListSelectionModel* _selectionModel;

 /** The <code>TableHeader</code> working with the table. */
 /*protected*/ QHeaderView*      tableHeader;

 /** The height in pixels of each row in the table. */
 /*protected*/ int               _rowHeight;

 /** The height in pixels of the margin between the cells in each row. */
 /*protected*/ int               rowMargin;

 /** The color of the grid. */
 /*protected*/ QColor             gridColor;

 /** The table draws horizontal lines between cells if <code>showHorizontalLines</code> is true. */
 /*protected*/ bool           showHorizontalLines;

 /** The table draws vertical lines between cells if <code>showVerticalLines</code> is true. */
 /*protected*/ bool           showVerticalLines;

 /**
  *  Determines if the table automatically resizes the
  *  width of the table's columns to take up the entire width of the
  *  table, and how it does the resizing.
  */
 /*protected*/ int               autoResizeMode;

 /**
  *  The table will query the <code>TableModel</code> to build the default
  *  set of columns if this is true.
  */
 /*protected*/ bool           autoCreateColumnsFromModel;

 /** Used by the <code>Scrollable</code> interface to determine the initial visible area. */
 /*protected*/ QSize         preferredViewportSize;

 /** True if row selection is allowed in this table. */
 /*protected*/ bool           rowSelectionAllowed;

 /**
  * Obsolete as of Java 2 platform v1.3.  Please use the
  * <code>rowSelectionAllowed</code> property and the
  * <code>columnSelectionAllowed</code> property of the
  * <code>columnModel</code> instead. Or use the
  * method <code>getCellSelectionEnabled</code>.
  */
 /*
  * If true, both a row selection and a column selection
  * can be non-empty at the same time, the selected cells are the
  * the cells whose row and column are both selected.
  */
 /*protected*/ bool           cellSelectionEnabled;

 /** If editing, the <code>Component</code> that is handling the editing. */
 /*transient*/ /*protected*/ QWidget*       editorComp;

 /**
  * The active cell editor object, that overwrites the screen real estate
  * occupied by the current cell and allows the user to change its contents.
  * {@code null} if the table isn't currently editing.
  */
 /*transient*/ /*protected*/ TableCellEditor* cellEditor;

 /** Identifies the column of the cell being edited. */
 /*transient*/ /*protected*/ int             editingColumn;

 /** Identifies the row of the cell being edited. */
 /*transient*/ /*protected*/ int             editingRow;

 /**
  * A table of objects that display the contents of a cell,
  * indexed by class as declared in <code>getColumnClass</code>
  * in the <code>TableModel</code> interface.
  */
// /*transient*/ /*protected*/ Hashtable defaultRenderersByColumnClass;

 /**
  * A table of objects that display and edit the contents of a cell,
  * indexed by class as declared in <code>getColumnClass</code>
  * in the <code>TableModel</code> interface.
  */
// /*transient*/ /*protected*/ Hashtable defaultEditorsByColumnClass;

 /** The foreground color of selected cells. */
 /*protected*/ QColor selectionForeground;

 /** The background color of selected cells. */
 /*protected*/ QColor selectionBackground;
 /*protected*/ TableColumnModel* createDefaultColumnModel();
 /*protected*/ DefaultListSelectionModel* createDefaultSelectionModel();
 /*protected*/ TableModel* createDefaultDataModel();
 /*protected*/ void resizeAndRepaint();
 /*protected*/ void columnResized(int column, int oldWidth, int newWidth);

friend class TableFrames;
friend class WarrantPreferencesPanel;
friend class SortManager;
friend class LocationsTableModel;
friend class MultiSensorItemPanel;
friend class TTJTable;
};

/**
* SortManager provides support for managing the selection and variable
* row heights when sorting is enabled. This information is encapsulated
* into a class to avoid bulking up JTable.
*/
/*private*/ /*final*/ class SortManager {
RowSorter/*<? extends TableModel>*/* sorter;

// Selection, in terms of the model. This is lazily created
// as needed.
/*private*/ ListSelectionModel* modelSelection;
/*private*/ int modelLeadIndex;
// Set to true while in the process of changing the selection.
// If this is true the selection change is ignored.
/*private*/ bool syncingSelection;
// Temporary cache of selection, in terms of model. This is only used
// if we don't need the full weight of modelSelection.
/*private*/ QVector<int>* lastModelSelection;

// Heights of the rows in terms of the model.
/*private*/ SizeSequence* modelRowSizes;

JTable* jt;
public:
SortManager(RowSorter/*<? extends TableModel>*/* sorter, JTable* jt);
/*public*/ void dispose();
/*public*/ void setViewRowHeight(int viewIndex, int rowHeight);
/*public*/ void allChanged();
/*public*/ void viewSelectionChanged(ListSelectionEvent* e);
/*public*/ void prepareForChange(RowSorterEvent* sortEvent,
                             ModelChange* change);
private:
/*private*/ void cacheSelection(RowSorterEvent* sortEvent,
                            ModelChange* change);
/*private*/ void cacheModelSelection(RowSorterEvent* sortEvent);
        /*public*/ void processChange(RowSorterEvent* sortEvent,
                                  ModelChange* change,
                                  bool sorterChanged);
 /*private*/ void setViewRowHeightsFromModel();
 /*private*/ void restoreSelection(ModelChange* change);
friend class JTable;
};

/*private*/ /*final*/ class ModelChange
{
    // Starting index of the change, in terms of the model
    int startModelIndex;

    // Ending index of the change, in terms of the model
    int endModelIndex;

    // Type of change
    int type;

    // Number of rows in the model
    int modelRowCount;

    // The event that triggered this.
    TableModelEvent* event;

    // Length of the change (end - start + 1)
    int length;

    // True if the event indicates all the contents have changed
    bool allRowsChanged;
    JTable* jt;
public:
    ModelChange(TableModelEvent* e, JTable* jt);
    friend class JTable;
    friend class SortManager;

};



#endif // JTABLE_H
