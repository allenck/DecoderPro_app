#ifndef LISTSELECTIONLISTENER_H
#define LISTSELECTIONLISTENER_H
#include "eventlistener.h"
#include "listselectionevent.h"
#include "runtimeexception.h"
/**
 * The listener that's notified when a lists selection value
 * changes.
 *
 * @see javax.swing.ListSelectionModel
 *
 * @author Hans Muller
 */

/*public*/ class ListSelectionListener : /*public QObject,*/ public EventListener
{
 //Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 //ListSelectionListener(QObject* /*parent*/ = 0) {}
public slots:
/**
 * Called whenever the value of the selection changes.
 * @param e the event that characterizes the change.
 */
 virtual void valueChanged(ListSelectionEvent* /*e*/)
  {
   throw new RuntimeException("unimplemented method");

  }
};
Q_DECLARE_INTERFACE(ListSelectionListener, "ListSelectionListener")
#endif // LISTSELECTIONLISTENER_H
