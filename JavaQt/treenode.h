#ifndef TREENODE_H
#define TREENODE_H
#include <QObject>
#include <QVector>
#include "javaqt_global.h"
//#include "mutabletreenode.h"

class MutableTreeNode;
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

/*public*/ /*interface*/ class JAVAQTSHARED_EXPORT TreeNode //: public QObject
{
    //Q_OBJECT
public:
    //TreeNode(QObject* oparent) : QObject(oparent){setObjectName("TreeNode");}
    //virtual ~TreeNode() { }
    /**
     * Returns the child <code>TreeNode</code> at index
     * <code>childIndex</code>.
     */
    virtual TreeNode* getChildAt(int /*childIndex*/) =0;//{return NULL;}

    /**
     * Returns the number of children <code>TreeNode</code>s the receiver
     * contains.
     */
    virtual int getChildCount() =0; //{return 0;}

    /**
     * Returns the parent <code>TreeNode</code> of the receiver.
     */
    virtual MutableTreeNode* getParent() =0;//{return NULL;}

    /**
     * Returns the index of <code>node</code> in the receivers children.
     * If the receiver does not contain <code>node</code>, -1 will be
     * returned.
     */
    virtual int getIndex(MutableTreeNode* /*node*/) =0;//{return 0;}

    /**
     * Returns true if the receiver allows children.
     */
    virtual bool getAllowsChildren() =0;//{return false;}

    /**
     * Returns true if the receiver is a leaf.
     */
   virtual  bool isLeaf() =0;//{return false;}

    /**
     * Returns the children of the receiver as an <code>Enumeration</code>.
     */
    //template <class E>
     virtual QVectorIterator<MutableTreeNode*>* children() {return NULL;}

     virtual QObject* tself() =0;
};
Q_DECLARE_INTERFACE(TreeNode, "TreeNode")
#endif // TREENODE_H
