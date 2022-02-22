#ifndef DEFAULTTABLECOLUMNMODEL_H
#define DEFAULTTABLECOLUMNMODEL_H
#include "tablecolumnmodel.h"
#include <QVector>
#include <tablecolumn.h>
#include "javaqt_global.h"
#include "propertychangelistener.h"
#include "eventlistenerlist.h"
#include "listselectionlistener.h"
class AbstractTableModel;
class TableColumnModelEvent;
class PropertyChangeEvent;
class JAVAQTSHARED_EXPORT DefaultTableColumnModel : public QObject, public TableColumnModel,
  public PropertyChangeListener, public ListSelectionListener
{
 Q_INTERFACES(PropertyChangeListener TableColumnModel ListSelectionListener)
 Q_OBJECT
public:
 explicit DefaultTableColumnModel(JTable *parent);
 /*public*/ void setSelectionModel(ListSelectionModel* newModel) override;
 /*public*/ ListSelectionModel* getSelectionModel() override;
 /*public*/ void setColumnMargin(int newMargin) override;
 /*public*/ int getColumnCount() override;
 /*public*/ QListIterator<TableColumn*> getColumns() override;
 /*public*/ void setColumnSelectionAllowed(bool flag) override;
 /*public*/ void addColumn(TableColumn* aColumn)  override;
 /*public*/ void removeColumn(TableColumn* column) override;
 /*public*/ TableColumn* getColumn(int columnIndex) override;
 /*public*/ int getColumnMargin() override;
  QObject* self() override {return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}
 /*public*/ void addColumnModelListener(TableColumnModelListener* x)override;
 /*public*/ void removeColumnModelListener(TableColumnModelListener* x) override;
 /*public*/ QVector<EventListener *> getColumnModelListeners();

signals:
 void firePropertyChange(PropertyChangeEvent*);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;

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
 /*protected*/ EventListenerList* listenerList = new EventListenerList();

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
