#ifndef TABLECELLRENDERER_H
#define TABLECELLRENDERER_H
#include <qobject.h>

class TableCellRenderer
{
 public:
  virtual QObject* self() {return nullptr;}
};
Q_DECLARE_INTERFACE(TableCellRenderer, "TableCellRenderer")
#endif // TABLECELLRENDERER_H
