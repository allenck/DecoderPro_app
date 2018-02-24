#ifndef TREEEXPANSIONEVENT_H
#define TREEEXPANSIONEVENT_H
#include "eventobject.h"
#include "treepath.h"

/**
 * An event used to identify a single path in a tree.  The source
 * returned by <b>getSource</b> will be an instance of JTree.
 * <p>
 * For further documentation and examples see
 * the following sections in <em>The Java Tutorial</em>:
 * <a href="https://docs.oracle.com/javase/tutorial/uiswing/events/treeexpansionlistener.html">How to Write a Tree Expansion Listener</a> and
 * <a href="https://docs.oracle.com/javase/tutorial/uiswing/events/treewillexpandlistener.html">How to Write a Tree-Will-Expand Listener</a>.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Scott Violet
 */
/*public*/ class TreeExpansionEvent : public EventObject
{
protected:
    /**
      * Path to the value this event represents.
      */
    /*protected*/ TreePath*              path;
public:
    /**
     * Constructs a TreeExpansionEvent object.
     *
     * @param source  the Object that originated the event
     *                (typically <code>this</code>)
     * @param path    a TreePath object identifying the newly expanded
     *                node
     */
 /*public*/ TreeExpansionEvent(QObject* source, TreePath* path, QObject* parent = 0) :  EventObject(source, parent)
    {
        //super(source);
        this->path = path;
    }

    /**
      * Returns the path to the value that has been expanded/collapsed.
      */
    /*public*/ virtual TreePath* getPath() { return path; }
};

#endif // TREEEXPANSIONEVENT_H
