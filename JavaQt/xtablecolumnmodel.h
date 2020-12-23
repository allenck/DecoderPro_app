#ifndef XTABLECOLUMNMODEL_H
#define XTABLECOLUMNMODEL_H
#include "defaulttablecolumnmodel.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT XTableColumnModel : public DefaultTableColumnModel
{
 Q_OBJECT
public:
 explicit XTableColumnModel(QObject *parent = 0);
 /*public*/ void setColumnVisible(TableColumn* column, bool visible);
 /*public*/ void setAllColumnsVisible();
 /*public*/ TableColumn* getColumnByModelIndex(int modelColumnIndex);
 /*public*/ bool isColumnVisible(TableColumn* aColumn);
 /*public*/ void addColumn(TableColumn* column);
 /*public*/ void removeColumn(TableColumn* column);
 /*public*/ void moveColumn(int oldIndex, int newIndex);
 /*public*/ void moveColumn(int columnIndex, int newIndex, bool onlyVisible);
 /*public*/ int getColumnCount(bool onlyVisible = false);
 /*public*/ QListIterator<TableColumn*> getColumns(bool onlyVisible);
 /*public*/ int getColumnIndex(QVariant identifier, bool onlyVisible);
 /*public*/ TableColumn* getColumn(int columnIndex, bool onlyVisible = true);

signals:

public slots:
protected:
 /**
  * Array of TableColumn objects in this model. Holds all column objects,
  * regardless of their visibility
  */
 /*protected*/ QVector<TableColumn*> allTableColumns;// = new Vector<TableColumn>();

};

#endif // XTABLECOLUMNMODEL_H
