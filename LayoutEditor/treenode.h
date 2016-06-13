#ifndef TREENODE_H
#define TREENODE_H
#include <QObject>
#include <QVector>
#include "liblayouteditor_global.h"

/**
 * Defines the requirements for an object that can be used as a
 * tree node in a JTree.
 * <p>
 * Implementations of <code>TreeNode</code> that override <code>equals</code>
 * will typically need to override <code>hashCode</code> as well.  Refer
 * to {@link javax.swing.tree.TreeModel} for more information.
 *
 * For further information and examples of using tree nodes,
 * see <a
 href="http://java.sun.com/docs/books/tutorial/uiswing/components/tree.html">How to Use Tree Nodes</a>
 * in <em>The Java Tutorial.</em>
 *
 * @author Rob Davis
 * @author Scott Violet
 */

/*public*/ /*interface*/ class LIBLAYOUTEDITORSHARED_EXPORT TreeNode : public QObject
{
    Q_OBJECT
public:
    TreeNode(QObject* oparent) : QObject(oparent){}
    virtual ~TreeNode() { }
    /**
     * Returns the child <code>TreeNode</code> at index
     * <code>childIndex</code>.
     */
    virtual TreeNode* getChildAt(int /*childIndex*/) {return NULL;}

    /**
     * Returns the number of children <code>TreeNode</code>s the receiver
     * contains.
     */
    virtual int getChildCount() {return 0;}

    /**
     * Returns the parent <code>TreeNode</code> of the receiver.
     */
    virtual TreeNode* getParent() {return NULL;}

    /**
     * Returns the index of <code>node</code> in the receivers children.
     * If the receiver does not contain <code>node</code>, -1 will be
     * returned.
     */
    virtual int getIndex(TreeNode* /*node*/) {return 0;}

    /**
     * Returns true if the receiver allows children.
     */
    virtual bool getAllowsChildren() {return false;}

    /**
     * Returns true if the receiver is a leaf.
     */
   virtual  bool isLeaf() {return false;}

    /**
     * Returns the children of the receiver as an <code>Enumeration</code>.
     */
    //template <class E>
     virtual QVectorIterator<TreeNode*>* children() {return NULL;}
};
#endif // TREENODE_H
