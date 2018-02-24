#ifndef TREESELECTIONLISTENER_H
#define TREESELECTIONLISTENER_H
#include "treeselectionevent.h"
#include "eventlistener.h"

/**
 * The listener that's notified when the selection in a TreeSelectionModel
 * changes.
 * For more information and examples see
 * <a
 href="https://docs.oracle.com/javase/tutorial/uiswing/events/treeselectionlistener.html">How to Write a Tree Selection Listener</a>,
 * a section in <em>The Java Tutorial.</em>
 *
 * @see javax.swing.tree.TreeSelectionModel
 * @see javax.swing.JTree
 *
 * @author Scott Violet
 */
/*public*/ class TreeSelectionListener  : public EventListener //extends EventListener
{
 Q_OBJECT
public:
 TreeSelectionListener() : EventListener() {}
 ~TreeSelectionListener() {}
 TreeSelectionListener(const TreeSelectionListener&): EventListener() {}
public slots:
    /**
      * Called whenever the value of the selection changes.
      * @param e the event that characterizes the change.
      */
    virtual void valueChanged(TreeSelectionEvent* /*e*/) {}
};
Q_DECLARE_METATYPE(TreeSelectionListener)
#endif // TREESELECTIONLISTENER_H
