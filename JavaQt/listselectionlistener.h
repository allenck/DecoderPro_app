#ifndef LISTSELECTIONLISTENER_H
#define LISTSELECTIONLISTENER_H
#include "eventlistener.h"
#include "listselectionevent.h"

/**
 * The listener that's notified when a lists selection value
 * changes.
 *
 * @see javax.swing.ListSelectionModel
 *
 * @author Hans Muller
 */

/*public*/ class ListSelectionListener : public EventListener
{
 Q_OBJECT
public:
 ListSelectionListener(QObject* parent = 0) {}
public slots:
/**
 * Called whenever the value of the selection changes.
 * @param e the event that characterizes the change.
 */
 virtual void valueChanged(ListSelectionEvent* /*e*/) {}
};
Q_DECLARE_INTERFACE(ListSelectionListener, "ListSelectionListener")
#endif // LISTSELECTIONLISTENER_H
