#ifndef DEFAULTTABLECOLUMNMODEL_H
#define DEFAULTTABLECOLUMNMODEL_H
#include "tablecolumnmodel.h"
#include <QVector>
#include <tablecolumn.h>
#include "javaqt_global.h"

class AbstractTableModel;
class TableColumnModelEvent;
class PropertyChangeEvent;
class JAVAQTSHARED_EXPORT DefaultTableColumnModel : public TableColumnModel
{
 Q_OBJECT
public:
 explicit DefaultTableColumnModel(JTable *parent);
 /*public*/ void setSelectionModel(ListSelectionModel* newModel);
 /*public*/ ListSelectionModel* getSelectionModel();
 /*public*/ void setColumnMargin(int newMargin);
 /*public*/ int getColumnCount();
 /*public*/ QListIterator<TableColumn*> getColumns();
 /*public*/ void setColumnSelectionAllowed(bool flag);
 /*public*/ void addColumn(TableColumn* aColumn) ;
 /*public*/ void removeColumn(TableColumn* column);
 /*public*/ TableColumn* getColumn(int columnIndex);
 /*public*/ int getColumnMargin();

signals:
 void firePropertyChange(PropertyChangeEvent*);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ void invalidateWidthCache();

protected:

 //
 // Instance Variables
 //

     /** Array of TableColumn objects in this model */
     /*protected*/ QVector<TableColumn*> tableColumns;

     /** Model for keeping track of column selections */
     /*protected*/ ListSelectionModel* selectionModel;

     /** Width margin between each column */
     /*protected*/ int columnMargin;

     /** List of TableColumnModelListener */
//     /*protected*/ EventListenerList listenerList = new EventListenerList();

     /** Change event (only one needed) */
//     /*transient*/ /*protected*/ ChangeEvent changeEvent = null;

     /** Column selection allowed in this column model */
     /*protected*/ bool columnSelectionAllowed;

     /** A local cache of the combined width of all columns */
     /*protected*/ int totalColumnWidth;
 /*protected*/ ListSelectionModel* createSelectionModel();
 /*protected*/ void fireColumnMarginChanged();
 /*protected*/ void fireColumnAdded(TableColumnModelEvent* e);
 /*protected*/ void fireColumnRemoved(TableColumnModelEvent* e);
 /*protected*/ void fireColumnMoved(TableColumnModelEvent* e);

};

#endif // DEFAULTTABLECOLUMNMODEL_H
