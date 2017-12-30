#ifndef ROWSORTEREVENT_H
#define ROWSORTEREVENT_H
#include "eventobject.h"
#include "rowsorter.h"

class RowSorterEvent : public EventObject
{
public:
 RowSorterEvent(RowSorter* source);
 /*public*/ enum Type {
     /**
      * Indicates the sort order has changed.
      */
     SORT_ORDER_CHANGED,

     /**
      * Indicates the contents have been newly sorted or
      * transformed in some way.
      */
     SORTED
 };
 /*public*/ RowSorterEvent(RowSorter* source, Type type,
                       QVector<int>* previousRowIndexToModel);
 /*public*/ RowSorter* getSource();
 /*public*/ Type getType();
 /*public*/ int convertPreviousRowIndexToModel(int index);
 /*public*/ int getPreviousRowCount();

private:
 /*private*/ Type type;
 /*private*/ QVector<int>* oldViewToModel;

};

#endif // ROWSORTEREVENT_H
