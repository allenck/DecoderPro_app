#include "defaulttreemodel.h"
#include "mutabletreenode.h"
#include "catalogtreenode.h"
#include "treepath.h"
#include <QVector>
#include "vptr.h"
#include "treemodelevent.h"
#include "treemodellistener.h"
#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

DefaultTreeModel::DefaultTreeModel(QObject *parent) :
    TreeModel(parent)
{
}
/**
 * A simple tree data model that uses TreeNodes.
 * For further information and examples that use DefaultTreeModel,
 * see <a href="http://java.sun.com/docs/books/tutorial/uiswing/components/tree.html">How to Use Trees</a>
 * in <em>The Java Tutorial.</em>
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
 * @author Rob Davis
 * @author Ray Ryan
 * @author Scott Violet
 */
// /*public*/ class DefaultTreeModel implements Serializable, TreeModel {


/**
  * Creates a tree in which any node can have children.
  *
  * @param root a TreeNode object that is the root of the tree
  * @see #DefaultTreeModel(TreeNode, boolean)
  */
// //@ConstructorProperties({"root"})
 /*public*/ DefaultTreeModel::DefaultTreeModel(TreeNode* root, QObject *parent) : TreeModel(parent)
{
    //this(root, false);
 this->root = root;
 this->_asksAllowsChildren = false;
 listenerList = new EventListenerList();
}

/**
  * Creates a tree specifying whether any node can have children,
  * or whether only certain nodes can have children.
  *
  * @param root a TreeNode object that is the root of the tree
  * @param _asksAllowsChildren a boolean, false if any node can
  *        have children, true if each node is asked to see if
  *        it can have children
  * @see #asksAllowsChildren
  */
/*public*/ DefaultTreeModel::DefaultTreeModel(TreeNode* root, bool asksAllowsChildren, QObject *parent) : TreeModel(parent){
    //super();
    listenerList = new EventListenerList();
    this->root = root;
    this->_asksAllowsChildren = asksAllowsChildren;
}

/**
  * Sets whether or not to test leafness by asking getAllowsChildren()
  * or isLeaf() to the TreeNodes.  If newvalue is true, getAllowsChildren()
  * is messaged, otherwise isLeaf() is messaged.
  */
/*public*/ void DefaultTreeModel::setAsksAllowsChildren(bool newValue) {
    _asksAllowsChildren = newValue;
}

/**
  * Tells how leaf nodes are determined.
  *
  * @return true if only nodes which do not allow children are
  *         leaf nodes, false if nodes which have no children
  *         (even if allowed) are leaf nodes
  * @see #asksAllowsChildren
  */
/*public*/ bool DefaultTreeModel::asksAllowsChildren() {
    return _asksAllowsChildren;
}

/**
 * Sets the root to <code>root</code>. A NULL <code>root</code> implies
 * the tree is to display nothing, and is legal.
 */
/*public*/ void DefaultTreeModel::setRoot(TreeNode* root) {
    QObject* oldRoot = this->root;
    this->root = root;
    if (root == NULL && oldRoot != NULL) {
        fireTreeStructureChanged((QObject*)this, NULL);
    }
    else {
        nodeStructureChanged(root);
    }
}

/**
 * Returns the root of the tree.  Returns NULL only if the tree has
 * no nodes.
 *
 * @return  the root of the tree
 */
/*public*/ QObject* DefaultTreeModel::getRoot() {
    return root;
}

/**
 * Returns the index of child in parent.
 * If either the parent or child is <code>NULL</code>, returns -1.
 * @param parent a note in the tree, obtained from this data source
 * @param child the node we are interested in
 * @return the index of the child in the parent, or -1
 *    if either the parent or the child is <code>NULL</code>
 */
/*public*/ int DefaultTreeModel::getIndexOfChild(QObject* parent, QObject* child) {
    if(parent == NULL || child == NULL)
        return -1;
    return ((TreeNode*)parent)->getIndex((TreeNode*)child);
}

/**
 * Returns the child of <I>parent</I> at index <I>index</I> in the parent's
 * child array.  <I>parent</I> must be a node previously obtained from
 * this data source. This should not return NULL if <i>index</i>
 * is a valid index for <i>parent</i> (that is <i>index</i> >= 0 &&
 * <i>index</i> < getChildCount(<i>parent</i>)).
 *
 * @param   parent  a node in the tree, obtained from this data source
 * @return  the child of <I>parent</I> at index <I>index</I>
 */
/*public*/ QObject* DefaultTreeModel::getChild(QObject* parent, int index) {
    return ((TreeNode*)parent)->getChildAt(index);
}

/**
 * Returns the number of children of <I>parent</I>.  Returns 0 if the node
 * is a leaf or if it has no children.  <I>parent</I> must be a node
 * previously obtained from this data source.
 *
 * @param   parent  a node in the tree, obtained from this data source
 * @return  the number of children of the node <I>parent</I>
 */
/*public*/ int DefaultTreeModel::getChildCount(QObject* parent) {
    return ((TreeNode*)parent)->getChildCount();
}

/**
 * Returns whether the specified node is a leaf node.
 * The way the test is performed depends on the
 * <code>askAllowsChildren</code> setting.
 *
 * @param node the node to check
 * @return true if the node is a leaf node
 *
 * @see #asksAllowsChildren
 * @see TreeModel#isLeaf
 */
/*public*/ bool DefaultTreeModel::isLeaf(QObject* node) {
    if(_asksAllowsChildren)
        return !((TreeNode*)node)->getAllowsChildren();
    return ((TreeNode*)node)->isLeaf();
}

/**
 * Invoke this method if you've modified the {@code TreeNode}s upon which
 * this model depends. The model will notify all of its listeners that the
 * model has changed.
 */
/*public*/ void DefaultTreeModel::reload() {
    reload(root);
}

/**
  * This sets the user object of the TreeNode identified by path
  * and posts a node changed.  If you use custom user objects in
  * the TreeModel you're going to need to subclass this and
  * set the user object of the changed node to something meaningful.
  */
/*public*/ void DefaultTreeModel::valueForPathChanged(TreePath* path, QVariant newValue) {
    MutableTreeNode*   aNode = (MutableTreeNode*)path->getLastPathComponent();

    aNode->setUserObject(newValue);
    nodeChanged(aNode);
}

/**
 * Invoked this to insert newChild at location index in parents children.
 * This will then message nodesWereInserted to create the appropriate
 * event. This is the preferred way to add children as it will create
 * the appropriate event.
 */
/*public*/ void DefaultTreeModel::insertNodeInto(MutableTreeNode* newChild,
                           MutableTreeNode* parent, int index){
    parent->insert(newChild, index);

    QList<int>*          newIndexs = new QList<int>();

    newIndexs->append(index);
    nodesWereInserted(parent, newIndexs);
}

/**
 * Message this to remove node from its parent. This will message
 * nodesWereRemoved to create the appropriate event. This is the
 * preferred way to remove a node as it handles the event creation
 * for you.
 */
/*public*/ void DefaultTreeModel::removeNodeFromParent(MutableTreeNode* node) {
    MutableTreeNode*         parent = (MutableTreeNode*)node->getParent();

    if(parent == NULL)
        throw new IllegalArgumentException("node does not have a parent.");

    QList<int>*            childIndex = new QList<int>();
    QList<QObject*>*        removedArray = new QList<QObject*>();

    childIndex->append(parent->getIndex(node));
    parent->remove(childIndex->at(0));
    removedArray->append(node);
    nodesWereRemoved(parent, childIndex, removedArray);
}

/**
  * Invoke this method after you've changed how node is to be
  * represented in the tree.
  */
/*public*/ void DefaultTreeModel::nodeChanged(TreeNode* node) {
    if(/*listenerList != NULL &&*/ node != NULL) {
        TreeNode*         parent = node->getParent();

        if(parent != NULL) {
            int        anIndex = parent->getIndex(node);
            if(anIndex != -1) {
                QList<int>*       cIndexs = new QList<int>();

                cIndexs->append( anIndex);
                nodesChanged(parent, cIndexs);
            }
        }
        else if (node == getRoot()) {
            nodesChanged(node, NULL);
        }
    }
}

/**
 * Invoke this method if you've modified the {@code TreeNode}s upon which
 * this model depends. The model will notify all of its listeners that the
 * model has changed below the given node.
 *
 * @param node the node below which the model has changed
 */
/*public*/ void DefaultTreeModel::reload(TreeNode* node) {
    if(node != NULL) {
        fireTreeStructureChanged((QObject*)this, (QList<QObject*>*)getPathToRoot(node), NULL, NULL);
    }
}

/**
  * Invoke this method after you've inserted some TreeNodes into
  * node.  childIndices should be the index of the new elements and
  * must be sorted in ascending order.
  */
/*public*/ void DefaultTreeModel::nodesWereInserted(TreeNode* node, QList<int>* childIndices) {
    if(/*listenerList != NULL &&*/ node != NULL && childIndices != NULL
            && childIndices->length() > 0) {
        int               cCount = childIndices->length();
        QList<QObject*>*          newChildren = new QList<QObject*>();

        for(int counter = 0; counter < cCount; counter++)
            newChildren->append( node->getChildAt(childIndices->at(counter)));
        fireTreeNodesInserted((QObject*)this, (QList<QObject*>*)getPathToRoot(node), childIndices,
                              newChildren);
    }
}

/**
  * Invoke this method after you've removed some TreeNodes from
  * node.  childIndices should be the index of the removed elements and
  * must be sorted in ascending order. And removedChildren should be
  * the array of the children objects that were removed.
  */
/*public*/ void DefaultTreeModel::nodesWereRemoved(TreeNode* node, QList<int>* childIndices,
                             QList<QObject*>* removedChildren) {
    if(node != NULL && childIndices != NULL) {
        fireTreeNodesRemoved((QObject*)this, (QList<QObject*>*)getPathToRoot(node), childIndices,
                             removedChildren);
    }
}

/**
  * Invoke this method after you've changed how the children identified by
  * childIndicies are to be represented in the tree.
  */
/*public*/ void DefaultTreeModel::nodesChanged(TreeNode* node, QList<int>* childIndices) {
    if(node != NULL) {
        if (childIndices != NULL) {
            int            cCount = childIndices->length();

            if(cCount > 0) {
                QList<QObject*>*       cChildren = new QList<QObject*> ;

                for(int counter = 0; counter < cCount; counter++)
                    cChildren->append( node->getChildAt
                        (childIndices->at(counter)));
                fireTreeNodesChanged((QObject*)this, (QList<QObject*>*)getPathToRoot(node),
                                     childIndices, cChildren);
            }
        }
        else if (node == getRoot()) {
            fireTreeNodesChanged((QObject*)this, (QList<QObject*>*)getPathToRoot(node), NULL, NULL);
        }
    }
}

/**
  * Invoke this method if you've totally changed the children of
  * node and its childrens children...  This will post a
  * treeStructureChanged event.
  */
/*public*/ void DefaultTreeModel::nodeStructureChanged(TreeNode* node)
{
 if(node != NULL) {
    fireTreeStructureChanged((QObject*)this, (QList<QObject*>*)getPathToRoot(node), NULL, NULL);
 }
}

/**
 * Builds the parents of node up to and including the root node,
 * where the original node is the last element in the returned array.
 * The length of the returned array gives the node's depth in the
 * tree.
 *
 * @param aNode the TreeNode to get the path for
 */
/*public*/ QList<TreeNode*>* DefaultTreeModel::getPathToRoot(TreeNode* aNode) {
    return getPathToRoot(aNode, 0);
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
/*protected*/ QList<TreeNode*>* DefaultTreeModel::getPathToRoot(TreeNode* aNode, int depth)
{
  QList<TreeNode*>*            retNodes;
  // This method recurses, traversing towards the root in order
  // size the array. On the way back, it fills in the nodes,
  // starting from the root and working back to the original node.

  /* Check for NULL, in case someone passed in a NULL node, or
     they passed in an element that isn't rooted at root. */
  if(aNode == NULL)
  {
      if(depth == 0)
          return NULL;
      else
      {
          //retNodes = new QVector<TreeNode*>(depth);
          retNodes = new QList<TreeNode*>();
          for(int i=0; i < depth; i++)
           retNodes->append(NULL);
      }
  }
  else
  {
      depth++;
      if(aNode == root)
      {
          //retNodes = new QVector<TreeNode*>(depth);
          retNodes = new QList<TreeNode*>();
          for(int i=0; i < depth; i++)
           retNodes->append(NULL);
      }

      else
          retNodes = getPathToRoot(aNode->getParent(), depth);
      retNodes->replace(retNodes->size() - depth, aNode);
  }
  return retNodes;
}

//
//  Events
//

/**
 * Adds a listener for the TreeModelEvent posted after the tree changes.
 *
 * @see     #removeTreeModelListener
 * @param   l       the listener to add
 */
/*public*/ void DefaultTreeModel::addTreeModelListener(TreeModelListener* l) {
    listenerList->add("TreeModelListener", l);
    //connect()
    connect(this, SIGNAL(treeStructureChanged(TreeModelEvent*)), l, SLOT(treeStructureChanged(TreeModelEvent*)));
}

/**
 * Removes a listener previously added with <B>addTreeModelListener()</B>.
 *
 * @see     #addTreeModelListener
 * @param   l       the listener to remove
 */
/*public*/ void DefaultTreeModel::removeTreeModelListener(TreeModelListener* l) {
//    listenerList->remove("TreeModelListener", l);
}

/**
 * Returns an array of all the tree model listeners
 * registered on this model.
 *
 * @return all of this model's <code>TreeModelListener</code>s
 *         or an empty
 *         array if no tree model listeners are currently registered
 *
 * @see #addTreeModelListener
 * @see #removeTreeModelListener
 *
 * @since 1.4
 */
/*public*/ QList<TreeModelListener*> DefaultTreeModel::getTreeModelListeners() {
    //return listenerList->getListeners("TreeModelListener");
 QVector<QObject*> list =  listenerList->getListenerList();
 QList<TreeModelListener*> listenerList = QList<TreeModelListener*>();
 foreach (QObject* listener, list) {
  if(listener->objectName() == "TreeModelListener")
   listenerList.append((TreeModelListener*)listener);
 }
 return listenerList;
}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the parameters passed into
 * the fire method.
 *
 * @param source the source of the {@code TreeModelEvent};
 *               typically {@code this}
 * @param path the path to the parent of the nodes that changed; use
 *             {@code NULL} to identify the root has changed
 * @param childIndices the indices of the changed elements
 * @param children the changed elements
 */
/*protected*/ void DefaultTreeModel::fireTreeNodesChanged(QObject* source, QList<QObject*>* path,
                                    QList<int>* childIndices,
                                    QList<QObject*>* children)
{
#if 0
    // Guaranteed to return a non-NULL array
    QList<QObject*> listeners = listenerList.getListenerList();
    TreeModelEvent e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length-2; i>=0; i-=2) {
        if (listeners[i]==TreeModelListener.class) {
            // Lazily create the event:
            if (e == NULL)
                e = new TreeModelEvent(source, path,
                                       childIndices, children);
            ((TreeModelListener)listeners[i+1]).treeNodesChanged(e);
        }
    }
#endif
    emit treeNodesChanged(source,path,childIndices,children);
}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the parameters passed into
 * the fire method.
 *
 * @param source the source of the {@code TreeModelEvent};
 *               typically {@code this}
 * @param path the path to the parent the nodes were added to
 * @param childIndices the indices of the new elements
 * @param children the new elements
 */
/*protected*/ void DefaultTreeModel::fireTreeNodesInserted(QObject* source, QList<QObject*>* path,
                                    QList<int>* childIndices,
                                    QList<QObject*>* children)
{
#if 0
    // Guaranteed to return a non-NULL array
    Object[] listeners = listenerList.getListenerList();
    TreeModelEvent e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length-2; i>=0; i-=2) {
        if (listeners[i]==TreeModelListener.class) {
            // Lazily create the event:
            if (e == NULL)
                e = new TreeModelEvent(source, path,
                                       childIndices, children);
            ((TreeModelListener)listeners[i+1]).treeNodesInserted(e);
        }
    }
#endif
    emit treeNodesInserted(source,path,childIndices,children);

}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the parameters passed into
 * the fire method.
 *
 * @param source the source of the {@code TreeModelEvent};
 *               typically {@code this}
 * @param path the path to the parent the nodes were removed from
 * @param childIndices the indices of the removed elements
 * @param children the removed elements
 */
/*protected*/ void DefaultTreeModel::fireTreeNodesRemoved(QObject* source, QList<QObject*>* path,
                                    QList<int>* childIndices,
                                    QList<QObject*>* children) {
#if 0
    // Guaranteed to return a non-NULL array
    Object[] listeners = listenerList.getListenerList();
    TreeModelEvent e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length-2; i>=0; i-=2) {
        if (listeners[i]==TreeModelListener.class) {
            // Lazily create the event:
            if (e == NULL)
                e = new TreeModelEvent(source, path,
                                       childIndices, children);
            ((TreeModelListener)listeners[i+1]).treeNodesRemoved(e);
        }
    }
#endif
    emit treeNodesRemoved(source,path,childIndices,children);

}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the parameters passed into
 * the fire method.
 *
 * @param source the source of the {@code TreeModelEvent};
 *               typically {@code this}
 * @param path the path to the parent of the structure that has changed;
 *             use {@code NULL} to identify the root has changed
 * @param childIndices the indices of the affected elements
 * @param children the affected elements
 */
/*protected*/ void DefaultTreeModel::fireTreeStructureChanged(QObject* source, QList<QObject*>* path,
                                    QList<int>* childIndices,
                                    QList<QObject*>* children) {
#if 0
    // Guaranteed to return a non-NULL array
    Object[] listeners = listenerList.getListenerList();
    TreeModelEvent e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length-2; i>=0; i-=2) {
        if (listeners[i]==TreeModelListener.class) {
            // Lazily create the event:
            if (e == NULL)
                e = new TreeModelEvent(source, path,
                                       childIndices, children);
            ((TreeModelListener)listeners[i+1]).treeStructureChanged(e);
        }
    }
#endif
    emit treeStructureChanged(source,path,childIndices,children);

}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the parameters passed into
 * the fire method.
 *
 * @param source the source of the {@code TreeModelEvent};
 *               typically {@code this}
 * @param path the path to the parent of the structure that has changed;
 *             use {@code NULL} to identify the root has changed
 */
/*private*/ void DefaultTreeModel::fireTreeStructureChanged(QObject* source, TreePath* path) {
#if 1
    // Guaranteed to return a non-NULL array
    QVector<QObject*> listeners = listenerList->getListenerList();
    TreeModelEvent* e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
//    for (int i = listeners.length-2; i>=0; i-=2) {
//        if (listeners[i]==TreeModelListener.class) {
//            // Lazily create the event:
//            if (e == NULL)
                e = new TreeModelEvent(source, path);
//            ((TreeModelListener)listeners[i+1]).treeStructureChanged(e);
//        }
//    }
#endif
  emit treeStructureChanged(e);
}

/**
 * Returns an array of all the objects currently registered
 * as <code><em>Foo</em>Listener</code>s
 * upon this model.
 * <code><em>Foo</em>Listener</code>s are registered using the
 * <code>add<em>Foo</em>Listener</code> method.
 *
 * <p>
 *
 * You can specify the <code>listenerType</code> argument
 * with a class literal,
 * such as
 * <code><em>Foo</em>Listener.class</code>.
 * For example, you can query a
 * <code>DefaultTreeModel</code> <code>m</code>
 * for its tree model listeners with the following code:
 *
 * <pre>TreeModelListener[] tmls = (TreeModelListener[])(m.getListeners(TreeModelListener.class));</pre>
 *
 * If no such listeners exist, this method returns an empty array.
 *
 * @param listenerType the type of listeners requested; this parameter
 *          should specify an interface that descends from
 *          <code>java.util.EventListener</code>
 * @return an array of all objects registered as
 *          <code><em>Foo</em>Listener</code>s on this component,
 *          or an empty array if no such
 *          listeners have been added
 * @exception ClassCastException if <code>listenerType</code>
 *          doesn't specify a class or interface that implements
 *          <code>java.util.EventListener</code>
 *
 * @see #getTreeModelListeners
 *
 * @since 1.3
 */
///*public*/ <T extends EventListener> T[] getListeners(Class<T> listenerType) {
//    return listenerList.getListeners(listenerType);
//}
#if 0
// Serialization support.
private void writeObject(ObjectOutputStream s) throws IOException {
    Vector<Object> values = new Vector<Object>();

    s.defaultWriteObject();
    // Save the root, if its Serializable.
    if(root != NULL && root instanceof Serializable) {
        values.addElement("root");
        values.addElement(root);
    }
    s.writeObject(values);
}

private void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException {
    s.defaultReadObject();

    Vector          values = (Vector)s.readObject();
    int             indexCounter = 0;
    int             maxCounter = values.size();

    if(indexCounter < maxCounter && values.elementAt(indexCounter).
       equals("root")) {
        root = (TreeNode*)values.elementAt(++indexCounter);
        indexCounter++;
    }
}
#endif
QModelIndex DefaultTreeModel::index(int row, int column, const QModelIndex &parent) const
{
// if (!hasIndex(row,column,parent))
//  return QModelIndex();
 DefaultMutableTreeNode* parentItem;
 DefaultMutableTreeNode *childItem;
 if (!parent.isValid())
  parentItem = (DefaultMutableTreeNode*)root;
 else
  parentItem = static_cast<DefaultMutableTreeNode*>(parent.internalPointer());
 try
 {
  int childCount = parentItem->getChildCount();
  if((row >= childCount) || (row < 0))
  {
   return QModelIndex();
  }
  childItem = (DefaultMutableTreeNode*)parentItem->getChildAt(row);
 }
 catch (NoSuchElementException ex)
 {
  return QModelIndex();
 }
 if (childItem)
 {
  qDebug() << "Parent has " << parentItem->getChildCount() << " children, Child Level "  << childItem->getLevel() << childItem->toString();
  return createIndex(row,column,childItem);
 }
 else
  return QModelIndex();
}

QModelIndex DefaultTreeModel::parent(const QModelIndex &index) const
{
 if (!index.isValid())
  return QModelIndex();
 DefaultMutableTreeNode *childItem = static_cast<DefaultMutableTreeNode*>(index.internalPointer());
 DefaultMutableTreeNode* parentItem = (DefaultMutableTreeNode*)childItem->getParent();
 if (parentItem == root )
  return QModelIndex();
 return createIndex(index.row(), 0, parentItem);
}

int DefaultTreeModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 1;
}

int DefaultTreeModel::rowCount(const QModelIndex &parent) const
{
// if(QString(metaObject()->className()) == "DefaultTreeModel")
// {
  TreeNode* parentItem;
  if (parent.column() > 0)
   return 0;
  if (!parent.isValid())
   parentItem = root;
  else
   parentItem = static_cast<DefaultMutableTreeNode*>(parent.internalPointer());
  return parentItem->getChildCount();
}


QVariant DefaultTreeModel::data(const QModelIndex &index, int role) const
{
 //DefaultMutableTreeNode* node = (DefaultMutableTreeNode*)root->getChildAt(0)->getChildAt(index.row());
 DefaultMutableTreeNode* node = static_cast<DefaultMutableTreeNode*>(index.internalPointer());

 if(role == Qt::DisplayRole)
 {
  return node->toString();
 }
 if(role == Qt::DecorationRole)
 {
  if(node->isLeaf())
  return QApplication::desktop()->style()->standardIcon(QStyle::SP_FileIcon).pixmap(QSize(24,24));
  else
   return QApplication::desktop()->style()->standardIcon(QStyle::SP_DirIcon).pixmap(QSize(24,24));
 }
 if(role == Qt::UserRole)
 {
  return VPtr<DefaultMutableTreeNode>::asQVariant(node);
 }
 return QVariant();
}

Qt::ItemFlags DefaultTreeModel::flags(const QModelIndex &/*index*/) const
{
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant DefaultTreeModel::headerData(int /*section*/, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole &&  orientation == Qt::Horizontal)
 {
 return tr("Roster Groups");
 }
 return QVariant();
}
