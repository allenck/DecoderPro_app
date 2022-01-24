#ifndef ROWSORTERLISTENER_H
#define ROWSORTERLISTENER_H
#include "tablecolumnmodellistener.h"
#include "rowsorterevent.h"
/**
 * <code>RowSorterListener</code>s are notified of changes to a
 * <code>RowSorter</code>.
 *
 * @see javax.swing.RowSorter
 * @since 1.6
 */
/*public*/ /*interface*/ class RowSorterListener : public TableColumnModelListener {
public:
    /**
     * Notification that the <code>RowSorter</code> has changed.  The event
     * describes the scope of the change.
     *
     * @param e the event, will not be null
     */
    /*public*/ virtual void sorterChanged(RowSorterEvent* /*e*/) {}
};
Q_DECLARE_INTERFACE(RowSorterListener, "RowSorterListener")
#endif // ROWSORTERLISTENER_H
