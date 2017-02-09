#ifndef MUTABLETREENODE_H
#define MUTABLETREENODE_H
#include <QObject>
#include "treenode.h"
#include <QVariant>
#include "javaqt_global.h"

/**
 * Defines the requirements for a tree node object that can change --
 * by adding or removing child nodes, or by changing the contents
 * of a user object stored in the node.
 *
 * @see DefaultMutableTreeNode
 * @see javax.swing.JTree
 *
 * @author Rob Davis
 * @author Scott Violet
 */

/*public*/ /*interface*/ class JAVAQTSHARED_EXPORT MutableTreeNode : public TreeNode
{
    Q_OBJECT
public:
    MutableTreeNode(QObject* oparent ) : TreeNode(oparent) {}
    virtual ~MutableTreeNode() {}
    /**
     * Adds <code>child</code> to the receiver at <code>index</code>.
     * <code>child</code> will be messaged with <code>setParent</code>.
     */
    virtual void insert(MutableTreeNode* /*child*/, int /*index*/) {}

    /**
     * Removes the child at <code>index</code> from the receiver.
     */
    virtual void remove(int /*index*/) {}

    /**
     * Removes <code>node</code> from the receiver. <code>setParent</code>
     * will be messaged on <code>node</code>.
     */
    virtual void remove(MutableTreeNode* /*node*/) {}

    /**
     * Resets the user object of the receiver to <code>object</code>.
     */
    virtual void setUserObject(QVariant /*object*/){}

    /**
     * Removes the receiver from its parent.
     */
    virtual void removeFromParent() {}

    /**
     * Sets the parent of the receiver to <code>newParent</code>.
     */
    virtual void setParent(MutableTreeNode* /*newParent*/) {}
};

#endif // MUTABLETREENODE_H
