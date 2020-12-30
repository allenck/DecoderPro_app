#ifndef TABLECELLEDITOR_H
#define TABLECELLEDITOR_H
#include <QObject>

class TableCellEditor
{
 public:
  virtual QObject* self() {return nullptr;}
};
Q_DECLARE_INTERFACE(TableCellEditor, "TableCellEditor")
#endif // TABLECELLEDITOR_H
