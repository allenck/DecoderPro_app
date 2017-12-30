#ifndef TABLECOLUMNMODELLISTENER_H
#define TABLECOLUMNMODELLISTENER_H
#include "propertychangelistener.h"

/* TableColumnModelListener defines the interface for an object that listens
* to changes in a TableColumnModel.
*
* @author Alan Chung
* @see TableColumnModelEvent
*/

class TableColumnModelEvent;
class ChangeEvent;
class ListSelectionEvent;
/*public*/ /*interface*/class  TableColumnModelListener : public PropertyChangeListener //extends java.util.EventListener
{
public:
 TableColumnModelListener(QObject* parent = 0) : PropertyChangeListener(parent) {}
   /** Tells listeners that a column was added to the model. */
   /*public*/ virtual void columnAdded(TableColumnModelEvent* /*e*/) {}

   /** Tells listeners that a column was removed from the model. */
   /*public*/ virtual void columnRemoved(TableColumnModelEvent* /*e*/) {}

   /** Tells listeners that a column was repositioned. */
   /*public*/ virtual void columnMoved(TableColumnModelEvent* /*e*/) {}

   /** Tells listeners that a column was moved due to a margin change. */
   /*public*/ virtual void columnMarginChanged(ChangeEvent* /*e*/) {}

   /**
    * Tells listeners that the selection model of the
    * TableColumnModel changed.
    */
   /*public*/ virtual void columnSelectionChanged(ListSelectionEvent* /*e*/) {}
};

#endif // TABLECOLUMNMODELLISTENER_H
