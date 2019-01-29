#ifndef TREEEXPANSIONLISTENER_H
#define TREEEXPANSIONLISTENER_H
#include "eventlistener.h"
#include "treeexpansionevent.h"

/**
  * The listener that's notified when a tree expands or collapses
  * a node.
  * For further documentation and examples see
  * <a
  href="https://docs.oracle.com/javase/tutorial/uiswing/events/treeexpansionlistener.html">How to Write a Tree Expansion Listener</a>,
  * a section in <em>The Java Tutorial.</em>
  *
  * @author Scott Violet
  */

/*public*/ /*interface*/class TreeExpansionListener : public EventListener
{
 Q_OBJECT
public:
 TreeExpansionListener() : EventListener()
 {
  //setObjectName("TreeExpansionListener");
 }
public slots:
    /**
      * Called whenever an item in the tree has been expanded.
      */
 /*public*/ virtual void treeExpanded(TreeExpansionEvent* /*event*/) {}

    /**
      * Called whenever an item in the tree has been collapsed.
      */
 /*public*/ virtual void treeCollapsed(TreeExpansionEvent* /*event*/) {}
};
Q_DECLARE_INTERFACE(TreeExpansionListener, "TreeExpansionListener")
#endif // TREEEXPANSIONLISTENER_H
