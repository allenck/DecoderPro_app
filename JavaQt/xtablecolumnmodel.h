#ifndef XTABLECOLUMNMODEL_H
#define XTABLECOLUMNMODEL_H
#include "defaulttablecolumnmodel.h"
#include "javaqt_global.h"
#include "propertychangelistener.h"

class JAVAQTSHARED_EXPORT XTableColumnModel : public DefaultTableColumnModel
{
 Q_OBJECT
public:
 explicit XTableColumnModel(JTable *parent);
 /*public*/ void setColumnVisible(TableColumn* column, bool visible);
 /*public*/ void setAllColumnsVisible();
 /*public*/ TableColumn* getColumnByModelIndex(int modelColumnIndex);
 /*public*/ bool isColumnVisible(TableColumn* aColumn);
 /*public*/ void addColumn(TableColumn* column)override;
 /*public*/ void removeColumn(TableColumn* column)override;
 /*public*/ void moveColumn(int oldIndex, int newIndex)override;
 /*public*/ void moveColumn(int columnIndex, int newIndex, bool onlyVisible);
 /*public*/ int getColumnCount(bool onlyVisible);
 /*public*/ QListIterator<TableColumn*> getColumns(bool onlyVisible);
 /*public*/ int getColumnIndex(QVariant identifier, bool onlyVisible);
 /*public*/ TableColumn* getColumn(int columnIndex, bool onlyVisible = true);
  QObject* self() override {return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

signals:

public slots:

 private:
  /*private*/ QVector<TableColumn*> getColumnList(bool onlyVisible);

protected:
 /**
  * Array of TableColumn objects in this model. Holds all column objects,
  * regardless of their visibility
  */
 /*protected*/ QVector<TableColumn*> allTableColumns = QVector<TableColumn*>();

};

#endif // XTABLECOLUMNMODEL_H
