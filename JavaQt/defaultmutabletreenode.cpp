#include "defaultmutabletreenode.h"
#include "exceptions.h"
#include "logger.h"

/**NULL
 * A <code>DefaultMutableTreeNode</code> is a general-purpose node in a tree data
 * structure.
 * For examples of using default mutable tree nodes, see
 * <a
 href="http://java.sun.com/docs/books/tutorial/uiswing/components/tree.html">How to Use Trees</a>
 * in <em>The Java Tutorial.</em>
 *
 * <p>
 *
 * A tree node may have at most one parent and 0 or more children.
 * <code>DefaultMutableTreeNode</code> provides operations for examining and modifying a
 * node's parent and children and also operations for examining the tree that
 * the node is a part of.  A node's tree is the set of all nodes that can be
 * reached by starting at the node and following all the possible links to
 * parents and children.  A node with no parent is the root of its tree; a
 * node with no children is a leaf.  A tree may consist of many subtrees,
 * each node acting as the root for its own subtree.
 * <p>
 * This class provides enumerations for efficiently traversing a tree or
 * subtree in various orders or for following the path between two nodes.
 * A <code>DefaultMutableTreeNode</code> may also hold a reference to a user object, the
 * use of which is left to the user.  Asking a <code>DefaultMutableTreeNode</code> for its
 * string representation with <code>toString()</code> returns the string
 * representation of its user object.
 * <p>
 * <b>This is not a thread safe class.</b>If you intend to use
 * a DefaultMutableTreeNode (or a tree of TreeNodes) in more than one thread, you
 * need to do your own synchronizing. A good convention to adopt is
 * synchronizing on the root node of a tree.
 * <p>
 * While DefaultMutableTreeNode implements the MutableTreeNode interface and
 * will allow you to add in any implementation of MutableTreeNode not all
 * of the methods in DefaultMutableTreeNode will be applicable to all
 * MutableTreeNodes implementations. Especially with some of the enumerations
 * that are provided, using some of these methods assumes the
 * DefaultMutableTreeNode contains only DefaultMutableNode instances. All
 * of the TreeNode/MutableTreeNode methods will behave as defined no
 * matter what implementations are added.
 *
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @see MutableTreeNode
 *
 * @author Rob Davis
 */
///*public*/ class DefaultMutableTreeNode implements Cloneable,
//       MutableTreeNode, Serializable
//{
    //private static final long serialVersionUID = -4298474751201349152L;



    /**
     * Creates a tree node that has no parent and no children, but which
     * allows children.
     */
DefaultMutableTreeNode::DefaultMutableTreeNode(QObject *oparent)
    : MutableTreeNode(oparent)
{
 common(QVariant(), true);
}

/*static*/ /*public*/ /*final*/ QVectorIterator<MutableTreeNode*>* DefaultMutableTreeNode::EMPTY_ENUMERATION = new QVectorIterator<MutableTreeNode*>(QVector<MutableTreeNode*>());

/**
 * Creates a tree node with no parent, no children, but which allows
 * children, and initializes it with the specified user object.
 *
 * @param userObject an Object provided by the user that constitutes
 *                   the node's data
 */
/*public*/ DefaultMutableTreeNode::DefaultMutableTreeNode(QVariant userObject, QObject* oparent)
: MutableTreeNode(oparent)
{
 //this(userObject, true);
 common(userObject, true);
}

/**
 * Creates a tree node with no parent, no children, initialized with
 * the specified user object, and that allows children only if
 * specified.
 *
 * @param userObject an Object provided by the user that constitutes
 *        the node's data
 * @param allowsChildren if true, the node is allowed to have child
 *        nodes -- otherwise, it is always a leaf node
 */
/*public*/ DefaultMutableTreeNode::DefaultMutableTreeNode(QVariant userObject, bool allowsChildren,QObject *oparent)
: MutableTreeNode(oparent)
{
    //super();
 common(userObject, allowsChildren);
}

void DefaultMutableTreeNode::common(QVariant userObject, bool allowsChildren)
{
 log = new Logger("DefaultMutableTreeNode");
 setObjectName("DefaultMutableTreeNode");
 this->allowsChildren = allowsChildren;
 this->userObject = userObject;
 if(!userObject.isValid())
  log->warn(tr("invalid QVariant"));
}

//
//  Primitives
//

/**
 * Removes <code>newChild</code> from its present parent (if it has a
 * parent), sets the child's parent to this node, and then adds the child
 * to this node's child array at index <code>childIndex</code>.
 * <code>newChild</code> must not be NULL and must not be an ancestor of
 * this node.
 *
 * @param   newChild        the MutableTreeNode to insert under this node
 * @param   childIndex      the index in this node's child array
 *                          where this node is to be inserted
 * @exception       ArrayIndexOutOfBoundsException  if
 *                          <code>childIndex</code> is out of bounds
 * @exception       IllegalArgumentException        if
 *                          <code>newChild</code> is NULL or is an
 *                          ancestor of this node
 * @exception       IllegalStateException   if this node does not allow
 *                                          children
 * @see     #isNodeDescendant
 */
/*public*/ void DefaultMutableTreeNode::insert(MutableTreeNode* newChild, int childIndex)
{
 if (!allowsChildren)
 {
  throw new IllegalStateException("node does not allow children");
 }
 else if (newChild == NULL)
 {
  throw new IllegalArgumentException("new child is NULL");
 }
 else if (isNodeAncestor(newChild))
 {
  throw new IllegalArgumentException("new child is an ancestor");
 }

 MutableTreeNode* oldParent = (MutableTreeNode*)((DefaultMutableTreeNode*)newChild)->getParent();

 if (oldParent != NULL)
 {
  oldParent->remove(newChild);
 }
 newChild->setParent(this);
 if (_children == NULL)
 {
  //_children = (QVector<TreeNode*>*) new QVector<CatalogTreeNode*>();
  _children = new QVector<MutableTreeNode*>();
 }
 _children->insert(childIndex, newChild);
}

/**
 * Removes the child at the specified index from this node's children
 * and sets that node's parent to NULL. The child node to remove
 * must be a <code>MutableTreeNode</code>.
 *
 * @param   childIndex      the index in this node's child array
 *                          of the child to remove
 * @exception       ArrayIndexOutOfBoundsException  if
 *                          <code>childIndex</code> is out of bounds
 */
/*public*/ void DefaultMutableTreeNode::remove(int childIndex)
{
 MutableTreeNode* child = (MutableTreeNode*)getChildAt(childIndex);
 _children->remove(childIndex);
 child->setParent(NULL);
}

/**
 * Sets this node's parent to <code>newParent</code> but does not
 * change the parent's child array.  This method is called from
 * <code>insert()</code> and <code>remove()</code> to
 * reassign a child's parent, it should not be messaged from anywhere
 * else.
 *
 * @param   newParent       this node's new parent
 */
/*public*/ void DefaultMutableTreeNode::setParent(MutableTreeNode* newParent)
{
 _parent = newParent;
}

/**
 * Returns this node's parent or NULL if this node has no parent.
 *
 * @return  this node's parent TreeNode, or NULL if this node has no parent
 */
/*public*/ MutableTreeNode* DefaultMutableTreeNode::getParent()
{
 return _parent;
}

/**
 * Returns the child at the specified index in this node's child array.
 *
 * @param   index   an index into this node's child array
 * @exception       ArrayIndexOutOfBoundsException  if <code>index</code>
 *                                          is out of bounds
 * @return  the TreeNode in this node's child array at  the specified index
 */
/*public*/ MutableTreeNode *DefaultMutableTreeNode::getChildAt(int index)
{
 if (_children == NULL || _children->isEmpty())
 {
  log->error("node has no children");
  return NULL;
  //throw new ArrayIndexOutOfBoundsException("node has no children");
 }
 return (MutableTreeNode*)_children->at(index);
}

/**
 * Returns the number of children of this node.
 *
 * @return  an int giving the number of children of this node
 */
/*public*/ int DefaultMutableTreeNode::getChildCount()
{
 if (_children == NULL)
 {
  return 0;
 }
 else
 {
  return _children->size();
 }
}

/**
 * Returns the index of the specified child in this node's child array.
 * If the specified node is not a child of this node, returns
 * <code>-1</code>.  This method performs a linear search and is O(n)
 * where n is the number of children.
 *
 * @param   aChild  the TreeNode to search for among this node's children
 * @exception       IllegalArgumentException        if <code>aChild</code>
 *                                                  is NULL
 * @return  an int giving the index of the node in this node's child
 *          array, or <code>-1</code> if the specified node is a not
 *          a child of this node
 */
/*public*/ int DefaultMutableTreeNode::getIndex(MutableTreeNode* aChild)
{
    if (aChild == NULL)
    {
        throw new IllegalArgumentException("argument is NULL");
    }

    if (!isNodeChild(aChild))
    {
        return -1;
    }
    return _children->indexOf(aChild);        // linear search
}

/**
 * Creates and returns a forward-order enumeration of this node's
 * children.  Modifying this node's child array invalidates any child
 * enumerations created before the modification.
 *
 * @return  an Enumeration of this node's children
 */
/*public*/ QVectorIterator<MutableTreeNode*>* DefaultMutableTreeNode::children()
{
 if (_children == NULL)
 {
  return DefaultMutableTreeNode::EMPTY_ENUMERATION;
 }
 else
 {
  //return _children->elements();
  return new QVectorIterator<MutableTreeNode*> (*_children);
 }
}

/**
 * Determines whether or not this node is allowed to have children.
 * If <code>allows</code> is false, all of this node's children are
 * removed.
 * <p>
 * Note: By default, a node allows children.
 *
 * @param   allows  true if this node is allowed to have children
 */
/*public*/ void DefaultMutableTreeNode::setAllowsChildren(bool allows)
{
 if (allows != allowsChildren)
 {
  allowsChildren = allows;
  if (!allowsChildren)
  {
   removeAllChildren();
  }
 }
}

/**
 * Returns true if this node is allowed to have children.
 *
 * @return  true if this node allows children, else false
 */
/*public*/ bool DefaultMutableTreeNode::getAllowsChildren()
{
 return allowsChildren;
}

/**
 * Sets the user object for this node to <code>userObject</code>.
 *
 * @param   userObject      the Object that constitutes this node's
 *                          user-specified data
 * @see     #getUserObject
 * @see     #toString
 */
/*public*/ void DefaultMutableTreeNode::setUserObject(QVariant userObject)
{
 this->userObject = userObject;
}

/**
 * Returns this node's user object.
 *
 * @return  the Object stored at this node by the user
 * @see     #setUserObject
 * @see     #toString
 */
/*public*/ QVariant DefaultMutableTreeNode::getUserObject()
{
 return userObject;
}


//
//  Derived methods
//

/**
 * Removes the subtree rooted at this node from the tree, giving this
 * node a NULL parent.  Does nothing if this node is the root of its
 * tree.
 */
/*public*/ void DefaultMutableTreeNode::removeFromParent()
{
    MutableTreeNode* parent = (MutableTreeNode*)getParent();
    if (parent != NULL) {
        parent->remove(this);
    }
}

/**
 * Removes <code>aChild</code> from this node's child array, giving it a
 * NULL parent.
 *
 * @param   aChild  a child of this node to remove
 * @exception       IllegalArgumentException        if <code>aChild</code>
 *                                  is NULL or is not a child of this node
 */
/*public*/ void DefaultMutableTreeNode::remove(MutableTreeNode* aChild)
{
    if (aChild == NULL)
    {
        throw new IllegalArgumentException("argument is NULL");
    }

    if (!isNodeChild(aChild))
    {
        throw new IllegalArgumentException("argument is not a child");
    }
    remove(getIndex(aChild));       // linear search
}

/**
 * Removes all of this node's children, setting their parents to NULL.
 * If this node has no children, this method does nothing.
 */
/*public*/ void DefaultMutableTreeNode::removeAllChildren()
{
 for (int i = getChildCount()-1; i >= 0; i--)
 {
  remove(i);
 }
}

/**
 * Removes <code>newChild</code> from its parent and makes it a child of
 * this node by adding it to the end of this node's child array.
 *
 * @see             #insert
 * @param   newChild        node to add as a child of this node
 * @exception       IllegalArgumentException    if <code>newChild</code>
 *                                          is NULL
 * @exception       IllegalStateException   if this node does not allow
 *                                          children
 */
/*public*/ void DefaultMutableTreeNode::add(MutableTreeNode* newChild)
{
    if(newChild != NULL && newChild->getParent() == this)
        insert(newChild, getChildCount() - 1);
    else
        insert(newChild, getChildCount());
}



//
//  Tree Queries
//

/**
 * Returns true if <code>anotherNode</code> is an ancestor of this node
 * -- if it is this node, this node's parent, or an ancestor of this
 * node's parent.  (Note that a node is considered an ancestor of itself.)
 * If <code>anotherNode</code> is NULL, this method returns false.  This
 * operation is at worst O(h) where h is the distance from the root to
 * this node.
 *
 * @see             #isNodeDescendant
 * @see             #getSharedAncestor
 * @param   anotherNode     node to test as an ancestor of this node
 * @return  true if this node is a descendant of <code>anotherNode</code>
 */
/*public*/ bool DefaultMutableTreeNode::isNodeAncestor(MutableTreeNode* anotherNode)
{
 if (anotherNode == NULL)
 {
  return false;
 }

 TreeNode* ancestor = this;

 do
 {
  if (ancestor == anotherNode)
  {
   return true;
  }
 } while((ancestor = ancestor->getParent()) != NULL);

 return false;
}

/**
 * Returns true if <code>anotherNode</code> is a descendant of this node
 * -- if it is this node, one of this node's children, or a descendant of
 * one of this node's children.  Note that a node is considered a
 * descendant of itself.  If <code>anotherNode</code> is NULL, returns
 * false.  This operation is at worst O(h) where h is the distance from the
 * root to <code>anotherNode</code>.
 *
 * @see     #isNodeAncestor
 * @see     #getSharedAncestor
 * @param   anotherNode     node to test as descendant of this node
 * @return  true if this node is an ancestor of <code>anotherNode</code>
 */
/*public*/ bool DefaultMutableTreeNode::isNodeDescendant(DefaultMutableTreeNode* anotherNode)
{
    if (anotherNode == NULL)
        return false;

    return anotherNode->isNodeAncestor(this);
}

/**
 * Returns the nearest common ancestor to this node and <code>aNode</code>.
 * Returns NULL, if no such ancestor exists -- if this node and
 * <code>aNode</code> are in different trees or if <code>aNode</code> is
 * NULL.  A node is considered an ancestor of itself.
 *
 * @see     #isNodeAncestor
 * @see     #isNodeDescendant
 * @param   aNode   node to find common ancestor with
 * @return  nearest ancestor common to this node and <code>aNode</code>,
 *          or NULL if none
 */
/*public*/ TreeNode* DefaultMutableTreeNode::getSharedAncestor(DefaultMutableTreeNode* aNode)
{
    if (aNode == this)
    {
        return this;
    } else if (aNode == NULL)
    {
        return NULL;
    }

    int             level1, level2, diff;
    TreeNode        *node1, *node2;

    level1 = getLevel();
    level2 = aNode->getLevel();

    if (level2 > level1)
    {
        diff = level2 - level1;
        node1 = aNode;
        node2 = this;
    }
    else
    {
        diff = level1 - level2;
        node1 = this;
        node2 = aNode;
    }

    // Go up the tree until the nodes are at the same level
    while (diff > 0)
    {
        node1 = node1->getParent();
        diff--;
    }

    // Move up the tree until we find a common ancestor.  Since we know
    // that both nodes are at the same level, we won't cross paths
    // unknowingly (if there is a common ancestor, both nodes hit it in
    // the same iteration).

    do {
        if (node1 == node2)
        {
            return node1;
        }
        node1 = node1->getParent();
        node2 = node2->getParent();
    } while (node1 != NULL);// only need to check one -- they're at the
    // same level so if one is NULL, the other is

    if (node1 != NULL || node2 != NULL)
    {
        throw new Error ("nodes should be NULL");
    }

    return NULL;
}


/**
 * Returns true if and only if <code>aNode</code> is in the same tree
 * as this node.  Returns false if <code>aNode</code> is NULL.
 *
 * @see     #getSharedAncestor
 * @see     #getRoot
 * @return  true if <code>aNode</code> is in the same tree as this node;
 *          false if <code>aNode</code> is NULL
 */
/*public*/ bool DefaultMutableTreeNode::isNodeRelated(DefaultMutableTreeNode* aNode)
{
    return (aNode != NULL) && (getRoot() == aNode->getRoot());
}


/**
 * Returns the depth of the tree rooted at this node -- the longest
 * distance from this node to a leaf.  If this node has no children,
 * returns 0.  This operation is much more expensive than
 * <code>getLevel()</code> because it must effectively traverse the entire
 * tree rooted at this node.
 *
 * @see     #getLevel
 * @return  the depth of the tree whose root is this node
 */
/*public*/ int DefaultMutableTreeNode::getDepth()
{
    QObject*  last = NULL;
    QVectorIterator<TreeNode*>*     enum_ = breadthFirstEnumeration();

    while (enum_->hasNext())
    {
        last = enum_->next()->tself();
    }

    if (last == NULL)
    {
        throw new Error ("nodes should be NULL");
    }

    return ((DefaultMutableTreeNode*)last)->getLevel() - getLevel();
}



/**
 * Returns the number of levels above this node -- the distance from
 * the root to this node.  If this node is the root, returns 0.
 *
 * @see     #getDepth
 * @return  the number of levels above this node
 */
/*public*/ int DefaultMutableTreeNode::getLevel()
{
    TreeNode* ancestor;
    int levels = 0;

    ancestor = this;
    while((ancestor = ancestor->getParent()) != NULL)
    {
        levels++;
    }

    return levels;
}


/**
  * Returns the path from the root, to get to this node.  The last
  * element in the path is this node.
  *
  * @return an array of TreeNode objects giving the path, where the
  *         first element in the path is the root and the last
  *         element is this node.
  */
/*public*/ QVector<MutableTreeNode*>* DefaultMutableTreeNode::getPath()
{
 return getPathToRoot(this, 0);
}

/**
 * Builds the parents of node up to and including the root node,
 * where the original node is the last element in the returned array.
 * The length of the returned array gives the node's depth in the
 * tree.
 *
 * @param aNode  the TreeNode to get the path for
 * @param depth  an int giving the number of steps already taken towards
 *        the root (on recursive calls), used to size the returned array
 * @return an array of TreeNodes giving the path from the root to the
 *         specified node
 */
/*protected*/ QVector<MutableTreeNode *> *DefaultMutableTreeNode::getPathToRoot(MutableTreeNode* aNode, int depth)
{
 QVector<MutableTreeNode*>* retNodes;

 /* Check for NULL, in case someone passed in a NULL node, or
       they passed in an element that isn't rooted at root. */
 if(aNode == NULL)
 {
  if(depth == 0)
   return NULL;
  else
   retNodes = new QVector<MutableTreeNode*>(depth);
 }
 else
 {
  depth++;
  retNodes = getPathToRoot(aNode->getParent(), depth);
  retNodes->replace((retNodes->size() - depth), aNode);
 }
 return retNodes;
}

/**
  * Returns the user object path, from the root, to get to this node.
  * If some of the TreeNodes in the path have NULL user objects, the
  * returned path will contain NULLs.
  */
/*public*/ QVector<QVariant>* DefaultMutableTreeNode::getUserObjectPath()
{
 QVector<MutableTreeNode*>*         realPath = getPath();
 QVector<QVariant>*           retPath = new QVector<QVariant>(realPath->size());

 for(int counter = 0; counter < realPath->size(); counter++)
  retPath->replace(counter, ((DefaultMutableTreeNode*)realPath->at(counter))
                           ->getUserObject());
 return retPath;
}

/**
 * Returns the root of the tree that contains this node.  The root is
 * the ancestor with a NULL parent.
 *
 * @see     #isNodeAncestor
 * @return  the root of the tree that contains this node
 */
/*public*/ MutableTreeNode *DefaultMutableTreeNode::getRoot()
{
 MutableTreeNode* ancestor = this;
 MutableTreeNode* previous;

 do
 {
        previous = ancestor;
        ancestor = ancestor->getParent();
 } while (ancestor != NULL);

 return previous;
}


/**
 * Returns true if this node is the root of the tree.  The root is
 * the only node in the tree with a NULL parent; every tree has exactly
 * one root.
 *
 * @return  true if this node is the root of its tree
 */
/*public*/ bool DefaultMutableTreeNode::isRoot()
{
    return getParent() == NULL;
}


/**
 * Returns the node that follows this node in a preorder traversal of this
 * node's tree.  Returns NULL if this node is the last node of the
 * traversal.  This is an inefficient way to traverse the entire tree; use
 * an enumeration, instead.
 *
 * @see     #preorderEnumeration
 * @return  the node that follows this node in a preorder traversal, or
 *          NULL if this node is last
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getNextNode()
{
    if (getChildCount() == 0)
    {
        // No children, so look for nextSibling
        DefaultMutableTreeNode* nextSibling = getNextSibling();

        if (nextSibling == NULL)
        {
            DefaultMutableTreeNode* aNode = (DefaultMutableTreeNode*)getParent();

            do {
                if (aNode == NULL)
                {
                    return NULL;
                }

                nextSibling = aNode->getNextSibling();
                if (nextSibling != NULL) {
                    return nextSibling;
                }

                aNode = (DefaultMutableTreeNode*)aNode->getParent();
            } while(true);
        }
        else
        {
            return nextSibling;
        }
    }
 else
 {
  return (DefaultMutableTreeNode*)getChildAt(0);
 }
}


/**
 * Returns the node that precedes this node in a preorder traversal of
 * this node's tree.  Returns <code>NULL</code> if this node is the
 * first node of the traversal -- the root of the tree.
 * This is an inefficient way to
 * traverse the entire tree; use an enumeration, instead.
 *
 * @see     #preorderEnumeration
 * @return  the node that precedes this node in a preorder traversal, or
 *          NULL if this node is the first
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousNode()
{
    DefaultMutableTreeNode* previousSibling;
    DefaultMutableTreeNode* myParent = (DefaultMutableTreeNode*)getParent();

    if (myParent == NULL)
    {
        return NULL;
    }

    previousSibling = getPreviousSibling();

    if (previousSibling != NULL)
    {
        if (previousSibling->getChildCount() == 0)
            return previousSibling;
        else
            return previousSibling->getLastLeaf();
    }
    else
    {
        return myParent;
    }
}

/**
 * Creates and returns an enumeration that traverses the subtree rooted at
 * this node in preorder.  The first node returned by the enumeration's
 * <code>nextElement()</code> method is this node.<P>
 *
 * Modifying the tree by inserting, removing, or moving a node invalidates
 * any enumerations created before the modification.
 *
 * @see     #postorderEnumeration
 * @return  an enumeration for traversing the tree in preorder
 */
/*public*/ QVectorIterator<TreeNode*>* DefaultMutableTreeNode::preorderEnumeration()
{
 return (QVectorIterator<TreeNode*>*)new PreorderEnumeration(this);
}

/**
 * Creates and returns an enumeration that traverses the subtree rooted at
 * this node in postorder.  The first node returned by the enumeration's
 * <code>nextElement()</code> method is the leftmost leaf.  This is the
 * same as a depth-first traversal.<P>
 *
 * Modifying the tree by inserting, removing, or moving a node invalidates
 * any enumerations created before the modification.
 *
 * @see     #depthFirstEnumeration
 * @see     #preorderEnumeration
 * @return  an enumeration for traversing the tree in postorder
 */
/*public*/ QVectorIterator<TreeNode*>* DefaultMutableTreeNode::postorderEnumeration()
{
 return (QVectorIterator<TreeNode*>*)new PostorderEnumeration(this);
}

/**
 * Creates and returns an enumeration that traverses the subtree rooted at
 * this node in breadth-first order.  The first node returned by the
 * enumeration's <code>nextElement()</code> method is this node.<P>
 *
 * Modifying the tree by inserting, removing, or moving a node invalidates
 * any enumerations created before the modification.
 *
 * @see     #depthFirstEnumeration
 * @return  an enumeration for traversing the tree in breadth-first order
 */
/*public*/ QVectorIterator<TreeNode*>* DefaultMutableTreeNode::breadthFirstEnumeration()
{
 return (QVectorIterator<TreeNode*>*)new BreadthFirstEnumeration(this);
}

/**
 * Creates and returns an enumeration that traverses the subtree rooted at
 * this node in depth-first order.  The first node returned by the
 * enumeration's <code>nextElement()</code> method is the leftmost leaf.
 * This is the same as a postorder traversal.<P>
 *
 * Modifying the tree by inserting, removing, or moving a node invalidates
 * any enumerations created before the modification.
 *
 * @see     #breadthFirstEnumeration
 * @see     #postorderEnumeration
 * @return  an enumeration for traversing the tree in depth-first order
 */
/*public*/ QVectorIterator<TreeNode*>* DefaultMutableTreeNode::depthFirstEnumeration()
{
    return postorderEnumeration();
}

/**
 * Creates and returns an enumeration that follows the path from
 * <code>ancestor</code> to this node.  The enumeration's
 * <code>nextElement()</code> method first returns <code>ancestor</code>,
 * then the child of <code>ancestor</code> that is an ancestor of this
 * node, and so on, and finally returns this node.  Creation of the
 * enumeration is O(m) where m is the number of nodes between this node
 * and <code>ancestor</code>, inclusive.  Each <code>nextElement()</code>
 * message is O(1).<P>
 *
 * Modifying the tree by inserting, removing, or moving a node invalidates
 * any enumerations created before the modification.
 *
 * @see             #isNodeAncestor
 * @see             #isNodeDescendant
 * @exception       IllegalArgumentException if <code>ancestor</code> is
 *                                          not an ancestor of this node
 * @return  an enumeration for following the path from an ancestor of
 *          this node to this one
 */
/*public*/ QVectorIterator<TreeNode*>* DefaultMutableTreeNode::pathFromAncestorEnumeration(TreeNode* ancestor)
{
    return (QVectorIterator<TreeNode*>*) new PathBetweenNodesEnumeration(ancestor, this);
}


//
//  Child Queries
//

/**
 * Returns true if <code>aNode</code> is a child of this node.  If
 * <code>aNode</code> is NULL, this method returns false.
 *
 * @return  true if <code>aNode</code> is a child of this node; false if
 *                  <code>aNode</code> is NULL
 */
/*public*/ bool DefaultMutableTreeNode::isNodeChild(TreeNode* aNode) {
    bool retval;

    if (aNode == NULL) {
        retval = false;
    } else {
        if (getChildCount() == 0) {
            retval = false;
        } else {
            retval = (((DefaultMutableTreeNode*)aNode)->getParent() == this);
        }
    }

    return retval;
}


/**
 * Returns this node's first child.  If this node has no children,
 * throws NoSuchElementException.
 *
 * @return  the first child of this node
 * @exception       NoSuchElementException  if this node has no children
 */
/*public*/ MutableTreeNode *DefaultMutableTreeNode::getFirstChild() {
    if (getChildCount() == 0) {
        throw new NoSuchElementException("node has no children");
    }
    return getChildAt(0);
}


/**
 * Returns this node's last child.  If this node has no children,
 * throws NoSuchElementException.
 *
 * @return  the last child of this node
 * @exception       NoSuchElementException  if this node has no children
 */
/*public*/ MutableTreeNode* DefaultMutableTreeNode::getLastChild() {
    if (getChildCount() == 0) {
        throw new NoSuchElementException("node has no children");
    }
    return getChildAt(getChildCount()-1);
}


/**
 * Returns the child in this node's child array that immediately
 * follows <code>aChild</code>, which must be a child of this node.  If
 * <code>aChild</code> is the last child, returns NULL.  This method
 * performs a linear search of this node's children for
 * <code>aChild</code> and is O(n) where n is the number of children; to
 * traverse the entire array of children, use an enumeration instead.
 *
 * @see             #children
 * @exception       IllegalArgumentException if <code>aChild</code> is
 *                                  NULL or is not a child of this node
 * @return  the child of this node that immediately follows
 *          <code>aChild</code>
 */
/*public*/ MutableTreeNode* DefaultMutableTreeNode::getChildAfter(MutableTreeNode* aChild) {
    if (aChild == NULL) {
        throw new IllegalArgumentException("argument is NULL");
    }

    int index = getIndex(aChild);           // linear search

    if (index == -1) {
        throw new IllegalArgumentException("node is not a child");
    }

    if (index < getChildCount() - 1) {
        return getChildAt(index + 1);
    } else {
        return NULL;
    }
}


/**
 * Returns the child in this node's child array that immediately
 * precedes <code>aChild</code>, which must be a child of this node.  If
 * <code>aChild</code> is the first child, returns NULL.  This method
 * performs a linear search of this node's children for <code>aChild</code>
 * and is O(n) where n is the number of children.
 *
 * @exception       IllegalArgumentException if <code>aChild</code> is NULL
 *                                          or is not a child of this node
 * @return  the child of this node that immediately precedes
 *          <code>aChild</code>
 */
/*public*/ MutableTreeNode* DefaultMutableTreeNode::getChildBefore(MutableTreeNode* aChild) {
    if (aChild == NULL) {
        throw new IllegalArgumentException("argument is NULL");
    }

    int index = getIndex(aChild);           // linear search

    if (index == -1) {
        throw new IllegalArgumentException("argument is not a child");
    }

    if (index > 0) {
        return getChildAt(index - 1);
    } else {
        return NULL;
    }
}


//
//  Sibling Queries
//


/**
 * Returns true if <code>anotherNode</code> is a sibling of (has the
 * same parent as) this node.  A node is its own sibling.  If
 * <code>anotherNode</code> is NULL, returns false.
 *
 * @param   anotherNode     node to test as sibling of this node
 * @return  true if <code>anotherNode</code> is a sibling of this node
 */
/*public*/ bool DefaultMutableTreeNode::isNodeSibling(TreeNode* anotherNode) {
    bool retval;

    if (anotherNode == NULL) {
        retval = false;
    } else if (anotherNode == this) {
        retval = true;
    } else {
        TreeNode*  myParent = getParent();
        retval = (myParent != NULL && myParent ==((DefaultMutableTreeNode*) anotherNode)->getParent());

        if (retval && !((DefaultMutableTreeNode*)getParent())
                       ->isNodeChild(anotherNode)) {
            throw new Error("sibling has different parent");
        }
    }

    return retval;
}


/**
 * Returns the number of siblings of this node.  A node is its own sibling
 * (if it has no parent or no siblings, this method returns
 * <code>1</code>).
 *
 * @return  the number of siblings of this node
 */
/*public*/ int DefaultMutableTreeNode::getSiblingCount() {
    TreeNode* myParent = getParent();

    if (myParent == NULL) {
        return 1;
    } else {
        return ((DefaultMutableTreeNode*)myParent)->getChildCount();
    }
}


/**
 * Returns the next sibling of this node in the parent's children array.
 * Returns NULL if this node has no parent or is the parent's last child.
 * This method performs a linear search that is O(n) where n is the number
 * of children; to traverse the entire array, use the parent's child
 * enumeration instead.
 *
 * @see     #children
 * @return  the sibling of this node that immediately follows this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getNextSibling() {
    DefaultMutableTreeNode* retval;

    DefaultMutableTreeNode* myParent = (DefaultMutableTreeNode*)getParent();

    if (myParent == NULL) {
        retval = NULL;
    } else {
        retval = (DefaultMutableTreeNode*)myParent->getChildAfter(this);      // linear search
    }

    if (retval != NULL && !isNodeSibling(retval)) {
        throw new Error("child of parent is not a sibling");
    }

    return retval;
}


/**
 * Returns the previous sibling of this node in the parent's children
 * array.  Returns NULL if this node has no parent or is the parent's
 * first child.  This method performs a linear search that is O(n) where n
 * is the number of children.
 *
 * @return  the sibling of this node that immediately precedes this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousSibling() {
    DefaultMutableTreeNode* retval;

    DefaultMutableTreeNode* myParent = (DefaultMutableTreeNode*)getParent();

    if (myParent == NULL) {
        retval = NULL;
    } else {
        retval = (DefaultMutableTreeNode*)myParent->getChildBefore(this);     // linear search
    }

    if (retval != NULL && !isNodeSibling(retval)) {
        throw new Error("child of parent is not a sibling");
    }

    return retval;
}



//
//  Leaf Queries
//

/**
 * Returns true if this node has no children.  To distinguish between
 * nodes that have no children and nodes that <i>cannot</i> have
 * children (e.g. to distinguish files from empty directories), use this
 * method in conjunction with <code>getAllowsChildren</code>
 *
 * @see     #getAllowsChildren
 * @return  true if this node has no children
 */
/*public*/ bool DefaultMutableTreeNode::isLeaf() {
    return (getChildCount() == 0);
}


/**
 * Finds and returns the first leaf that is a descendant of this node --
 * either this node or its first child's first leaf.
 * Returns this node if it is a leaf.
 *
 * @see     #isLeaf
 * @see     #isNodeDescendant
 * @return  the first leaf in the subtree rooted at this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getFirstLeaf() {
    DefaultMutableTreeNode* node = this;

    while (!node->isLeaf()) {
        node = (DefaultMutableTreeNode*)node->getFirstChild();
    }

    return node;
}


/**
 * Finds and returns the last leaf that is a descendant of this node --
 * either this node or its last child's last leaf.
 * Returns this node if it is a leaf.
 *
 * @see     #isLeaf
 * @see     #isNodeDescendant
 * @return  the last leaf in the subtree rooted at this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getLastLeaf() {
    DefaultMutableTreeNode* node = this;

    while (!node->isLeaf()) {
        node = (DefaultMutableTreeNode*)node->getLastChild();
    }

    return node;
}


/**
 * Returns the leaf after this node or NULL if this node is the
 * last leaf in the tree.
 * <p>
 * In this implementation of the <code>MutableNode</code> interface,
 * this operation is very inefficient. In order to determine the
 * next node, this method first performs a linear search in the
 * parent's child-list in order to find the current node.
 * <p>
 * That implementation makes the operation suitable for short
 * traversals from a known position. But to traverse all of the
 * leaves in the tree, you should use <code>depthFirstEnumeration</code>
 * to enumerate the nodes in the tree and use <code>isLeaf</code>
 * on each node to determine which are leaves.
 *
 * @see     #depthFirstEnumeration
 * @see     #isLeaf
 * @return  returns the next leaf past this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getNextLeaf() {
    DefaultMutableTreeNode* nextSibling;
    DefaultMutableTreeNode* myParent = (DefaultMutableTreeNode*)getParent();

    if (myParent == NULL)
        return NULL;

    nextSibling = getNextSibling(); // linear search

    if (nextSibling != NULL)
        return nextSibling->getFirstLeaf();

    return myParent->getNextLeaf();  // tail recursion
}


/**
 * Returns the leaf before this node or NULL if this node is the
 * first leaf in the tree.
 * <p>
 * In this implementation of the <code>MutableNode</code> interface,
 * this operation is very inefficient. In order to determine the
 * previous node, this method first performs a linear search in the
 * parent's child-list in order to find the current node.
 * <p>
 * That implementation makes the operation suitable for short
 * traversals from a known position. But to traverse all of the
 * leaves in the tree, you should use <code>depthFirstEnumeration</code>
 * to enumerate the nodes in the tree and use <code>isLeaf</code>
 * on each node to determine which are leaves.
 *
 * @see             #depthFirstEnumeration
 * @see             #isLeaf
 * @return  returns the leaf before this node
 */
/*public*/ DefaultMutableTreeNode* DefaultMutableTreeNode::getPreviousLeaf() {
    DefaultMutableTreeNode* previousSibling;
    DefaultMutableTreeNode* myParent = (DefaultMutableTreeNode*)getParent();

    if (myParent == NULL)
        return NULL;

    previousSibling = getPreviousSibling(); // linear search

    if (previousSibling != NULL)
        return previousSibling->getLastLeaf();

    return myParent->getPreviousLeaf();              // tail recursion
}


/**
 * Returns the total number of leaves that are descendants of this node.
 * If this node is a leaf, returns <code>1</code>.  This method is O(n)
 * where n is the number of descendants of this node.
 *
 * @see     #isNodeAncestor
 * @return  the number of leaves beneath this node
 */
/*public*/ int DefaultMutableTreeNode::getLeafCount() {
    int count = 0;

    TreeNode* node;
    QVectorIterator<TreeNode*>* enum_ = breadthFirstEnumeration(); // order matters not

    while (enum_->hasNext()) {
        node = (TreeNode*)enum_->next();
        if (((DefaultMutableTreeNode*)node)->isLeaf()) {
            count++;
        }
    }

    if (count < 1) {
        throw new Error("tree has zero leaves");
    }

    return count;
}


//
//  Overrides
//

/**
 * Returns the result of sending <code>toString()</code> to this node's
 * user object, or the empty string if the node has no user object.
 *
 * @see     #getUserObject
 */
/*public*/ QString DefaultMutableTreeNode::toString() {
if (userObject == QVariant()) {
        return "";
    } else {
        return userObject.toString();
    }
}

/**
 * Overridden to make clone public.  Returns a shallow copy of this node;
 * the new node has no parent or children and has a reference to the same
 * user object, if any.
 *
 * @return  a copy of this node
 */
/*public*/ QObject* DefaultMutableTreeNode::clone() {
    DefaultMutableTreeNode* newNode = NULL;
#if 1
    try {
        //newNode = (DefaultMutableTreeNode*)MutableTreeNode::clone();
        newNode = new DefaultMutableTreeNode(this);

        // shallow copy -- the new node has no parent or children
        newNode->_children = NULL;
        newNode->_parent = NULL;

    } catch (CloneNotSupportedException* e) {
        // Won't happen because we implement Cloneable
        throw new Error(e->getMessage());
    }
#endif
    return newNode;
}
#if 0

// Serialization support.
private void writeObject(ObjectOutputStream s) throws IOException {
    Object[]             tValues;

    s.defaultWriteObject();
    // Save the userObject, if its Serializable.
    if(userObject != NULL && userObject instanceof Serializable) {
        tValues = new Object[2];
        tValues[0] = "userObject";
        tValues[1] = userObject;
    }
    else
        tValues = new Object[0];
    s.writeObject(tValues);
}

private void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException {
    Object[]      tValues;

    s.defaultReadObject();

    tValues = (Object[])s.readObject();

    if(tValues.length > 0 && tValues[0].equals("userObject"))
        userObject = tValues[1];
}
#endif
///*private*/ /*final*/ class PreorderEnumeration : public QObject
//{
//    Q_OBJECT
//    /*private*/ /*final*/ QStack< QVectorIterator<TreeNode*>* >* stack;// = new Stack<QList<CatalogTreeNode*>*>();
//public:
/*public*/ PreorderEnumeration::PreorderEnumeration(MutableTreeNode* rootNode)
{
    //super();
    stack = new QStack<QVectorIterator<MutableTreeNode*>*  >();
    QVector<MutableTreeNode*> v =   QVector<MutableTreeNode*>(1);
    v.append(rootNode);     // PENDING: don't really need a vector
    stack->push( new QVectorIterator<MutableTreeNode*>(v));
}

/*public*/ bool PreorderEnumeration::hasMoreElements() {
    return (!stack->isEmpty() && stack->top()->hasNext());
}

/*public*/ MutableTreeNode *PreorderEnumeration::nextElement() {
    QVectorIterator<MutableTreeNode*>* enumer = stack->top();
    MutableTreeNode*    node = enumer->next();
    QVectorIterator<MutableTreeNode*>* children = node->TreeNode::children();

    if (!enumer->hasNext()) {
        stack->pop();
    }
    if (children->hasNext()) {
        stack->push(children);
    }
    return node;
}

//};  // End of class PreorderEnumeration



///*final*/ class PostorderEnumeration : public QObject
//{
//    Q_OBJECT
//protected:
//    /*protected*/ TreeNode* root;
//    /*protected*/ QVectorIterator<TreeNode*>* children;
//    /*protected*/ QVectorIterator<TreeNode*>* subtree;
//public:
/*public*/ PostorderEnumeration::PostorderEnumeration(MutableTreeNode* rootNode) {
    //super();
    root = rootNode;
    children = root->children();
    subtree = DefaultMutableTreeNode::EMPTY_ENUMERATION;
}

/*public*/ bool PostorderEnumeration::hasMoreElements() {
    return root != NULL;
}

/*public*/ TreeNode* PostorderEnumeration::nextElement() {
    TreeNode* retval;

    if (subtree->hasNext()) {
        retval = subtree->next();
    } else if (children->hasNext()) {
        subtree = (QVectorIterator<MutableTreeNode*>*) new PostorderEnumeration(children->next());
        retval = subtree->next();
    } else {
        retval = root;
        root = NULL;
    }

    return retval;
}

//};  // End of class PostorderEnumeration



///*final*/ class BreadthFirstEnumeration : public QObject
//{
//    Q_OBJECT
//public:
//    // A simple queue with a linked list data structure.
//    /*final*/ class Queue {

//        /*final*/ class QNode {
//            /*public*/ QObject*   object;
//            /*public*/ QNode*    next;   // NULL if end
//            /*public*/ QNode(QObject* object, QNode* next)
//            {
//                this->object = object;
//                this->next = next;
//            }
//            friend class Queue;
//        };

//        /*public*/ void enqueue(QObject* anObject) {
//            if (head == NULL) {
//                head = tail = new QNode(anObject, NULL);
//            } else {
//                tail->next = new QNode(anObject, NULL);
//                tail = tail->next;
//            }
//        }

//        /*public*/ QObject* dequeue() {
//            if (head == NULL) {
//                throw new NoSuchElementException("No more elements");
//            }

//            QObject* retval = head->object;
//            QNode* oldHead = head;
//            head = head->next;
//            if (head == NULL) {
//                tail = NULL;
//            } else {
//                oldHead->next = NULL;
//            }
//            return retval;
//        }

//        /*public*/ QObject* firstObject() {
//            if (head == NULL) {
//                throw new NoSuchElementException("No more elements");
//            }

//            return head->object;
//        }

//        /*public*/ bool isEmpty() {
//            return head == NULL;
//        }
//        QNode* head; // NULL if empty
//        QNode* tail;
//     friend class QNode;
//     friend class BreadthFirstEnumeration;
//    }; // End of class Queue

/*public*/ BreadthFirstEnumeration::BreadthFirstEnumeration(MutableTreeNode* rootNode) {
    //super();
    QVector<MutableTreeNode*> v =  QVector<MutableTreeNode*>(1);
    v.append(rootNode);     // PENDING: don't really need a vector
    queue = new QQueue<QVectorIterator<MutableTreeNode*>*>();
    queue->enqueue(new QVectorIterator<MutableTreeNode*>(v));
}

/*public*/ bool BreadthFirstEnumeration::hasMoreElements() {
    return (!queue->isEmpty() &&
            ((QVectorIterator<TreeNode*>*)queue->head())->hasNext());
}

/*public*/ MutableTreeNode* BreadthFirstEnumeration::nextElement() {
    QVectorIterator<MutableTreeNode*>* enumer = (QVectorIterator<MutableTreeNode*>*)queue->head();
    MutableTreeNode*    node = (MutableTreeNode*)enumer->next();
    QVectorIterator<MutableTreeNode*>* children = node->TreeNode::children();

    if (!enumer->hasNext()) {
        queue->dequeue();
    }
    if (children->hasNext()) {
        queue->enqueue(children);
    }
    return node;
}

//protected: Queue* queue;



//};  // End of class BreadthFirstEnumeration



///*final*/ class PathBetweenNodesEnumeration : public QObject
//{
//    Q_OBJECT
//protected: QStack<TreeNode*>* stack;
//public:
/*public*/ PathBetweenNodesEnumeration::PathBetweenNodesEnumeration(TreeNode* ancestor,
                                   TreeNode* descendant)
{
    //super();

    if (ancestor == NULL || descendant == NULL) {
        throw new IllegalArgumentException("argument is NULL");
    }

    TreeNode* current;

    stack = new QStack<TreeNode*>();
    stack->push(descendant);

    current = descendant;
    while (current != ancestor) {
        current = current->getParent();
        if (current == NULL && descendant != ancestor) {
            throw new IllegalArgumentException(QString("node ") + ancestor->tself()->objectName() +
                        QString(" is not an ancestor of ") + descendant->tself()->objectName());
        }
        stack->push(current);
    }
}

/*public*/ bool PathBetweenNodesEnumeration::hasMoreElements() {
    return stack->size() > 0;
}

/*public*/ TreeNode* PathBetweenNodesEnumeration::nextElement() {
        try {
            return stack->pop();
        } catch (EmptyStackException e) {
            throw new NoSuchElementException("No more elements");
        }
    }

//    }; // End of class PathBetweenNodesEnumeration

