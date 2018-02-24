#include "treepath.h"
#include "exceptions.h"
#include <QVector>
#include <QVariant>
#include "defaultmutabletreenode.h"
//TreePath::TreePath(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * {@code TreePath} represents an array of objects that uniquely
 * identify the path to a node in a tree. The elements of the array
 * are ordered with the root as the first element of the array. For
 * example, a file on the file system is uniquely identified based on
 * the array of parent directories and the name of the file. The path
 * {@code /tmp/foo/bar} could be represented by a {@code TreePath} as
 * {@code new TreePath(new Object[] {"tmp", "foo", "bar"})}.
 * <p>
 * {@code TreePath} is used extensively by {@code JTree} and related classes.
 * For example, {@code JTree} represents the selection as an array of
 * {@code TreePath}s. When used with {@code JTree}, the elements of the
 * path are the objects returned from the {@code TreeModel}. When {@code JTree}
 * is paired with {@code DefaultTreeModel}, the elements of the
 * path are {@code TreeNode}s. The following example illustrates extracting
 * the user object from the selection of a {@code JTree}:
 * <pre>
 *   DefaultMutableTreeNode root = ...;
 *   DefaultTreeModel model = new DefaultTreeModel(root);
 *   JTree tree = new JTree(model);
 *   ...
 *   TreePath selectedPath = tree.getSelectionPath();
 *   DefaultMutableTreeNode selectedNode =
 *       ((DefaultMutableTreeNode)selectedPath.getLastPathComponent()).
 *       getUserObject();
 * </pre>
 * Subclasses typically need override only {@code
 * getLastPathComponent}, and {@code getParentPath}. As {@code JTree}
 * internally creates {@code TreePath}s at various points, it's
 * generally not useful to subclass {@code TreePath} and use with
 * {@code JTree}.
 * <p>
 * While {@code TreePath} is serializable, a {@code
 * NotSerializableException} is thrown if any elements of the path are
 * not serializable.
 * <p>
 * For further information and examples of using tree paths,
 * see <a
 href="http://java.sun.com/docs/books/tutorial/uiswing/components/tree.html">How to Use Trees</a>
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
 * @author Scott Violet
 * @author Philip Milne
 */
// /*public*/  class TreePath extends Object implements Serializable {

/**
 * Creates a {@code TreePath} from an array. The array uniquely
 * identifies the path to a node.
 *
 * @param path an array of objects representing the path to a node
 * @throws IllegalArgumentException if {@code path} is {@code NULL},
 *         empty, or contains a {@code NULL} value
 */
//@ConstructorProperties({"path"})
/*public*/  TreePath::TreePath(QVector<QObject*>* path, QObject* parent) : QObject(parent)
{
 common();

 if(path == NULL || path->length() == 0)
  throw new IllegalArgumentException("path in TreePath must be non NULL and not empty.");
 lastPathComponent = path->at(path->length() - 1);
 if (lastPathComponent == NULL)
 {
  throw new IllegalArgumentException("Last path component must be non-NULL");
 }
 if(path->length() > 1)
  parentPath = new TreePath(path, path->length() - 1);
}

/**
 * Creates a {@code TreePath} containing a single element. This is
 * used to construct a {@code TreePath} identifying the root.
 *
 * @param lastPathComponent the root
 * @see #TreePath(Object[])
 * @throws IllegalArgumentException if {@code lastPathComponent} is
 *         {@code NULL}
 */
/*public*/  TreePath::TreePath(TreeNode* lastPathComponent, QObject* parent) : QObject(parent)
{
 common();
 if(lastPathComponent == NULL)
  throw new IllegalArgumentException("path in TreePath must be non NULL.");
 this->lastPathComponent = (QObject*)lastPathComponent;
 parentPath = NULL;
}

/**
 * Creates a {@code TreePath} with the specified parent and element.
 *
 * @param parent the path to the parent, or {@code NULL} to indicate
 *        the root
 * @param lastPathComponent the last path element
 * @throws IllegalArgumentException if {@code lastPathComponent} is
 *         {@code NULL}
 */
/*protected*/ TreePath::TreePath(TreePath* parentPath, QObject* lastPathComponent, QObject* parent) : QObject(parent)
{
 common();
 if(lastPathComponent == NULL)
  throw new IllegalArgumentException("path in TreePath must be non NULL.");
 this->parentPath = parentPath;
 this->lastPathComponent = lastPathComponent;
}

/**
 * Creates a {@code TreePath} from an array. The returned
 * {@code TreePath} represents the elements of the array from
 * {@code 0} to {@code length - 1}.
 * <p>
 * This constructor is used internally, and generally not useful outside
 * of subclasses.
 *
 * @param path the array to create the {@code TreePath} from
 * @param length identifies the number of elements in {@code path} to
 *        create the {@code TreePath} from
 * @throws NullPointerException if {@code path} is {@code NULL}
 * @throws ArrayIndexOutOfBoundsException if {@code length - 1} is
 *         outside the range of the array
 * @throws IllegalArgumentException if any of the elements from
 *         {@code 0} to {@code length - 1} are {@code NULL}
 */
/*protected*/ TreePath::TreePath(QVector<QObject*>* path, int length, QObject* parent) : QObject(parent)
{
 common();
 lastPathComponent = path->at(length-1);
 if (lastPathComponent == NULL)
 {
  throw new IllegalArgumentException("Path elements must be non-NULL");
 }
 if(length > 1)
  parentPath = new TreePath(path, length - 1);
}

/**
 * Creates an empty {@code TreePath}.  This is provided for
 * subclasses that represent paths in a different
 * manner. Subclasses that use this constructor must override
 * {@code getLastPathComponent}, and {@code getParentPath}.
 */
/*protected*/ TreePath::TreePath(QObject* parent) : QObject(parent) {
 common();
}
void TreePath::common()
{
 setObjectName("TreePath");
 parentPath = NULL;
 lastPathComponent = NULL;
}

/**
 * Returns an ordered array of the elements of this {@code TreePath}.
 * The first element is the root.
 *
 * @return an array of the elements in this {@code TreePath}
 */
/*public*/  QList<QObject*>* TreePath::getPath() {
    int            i = getPathCount();
    QVector<QObject*>*      result = new QVector<QObject*>(i--) ;//[i--];

    for(TreePath* path = this; path != NULL; path = path->getParentPath()) {
        result->replace(i--, path->getLastPathComponent());
    }
    QList<QObject*> list = result->toList();
    return &list;
}

/**
 * Returns the last element of this path.
 *
 * @return the last element in the path
 */
/*public*/  QObject* TreePath::getLastPathComponent() {
    return lastPathComponent;
}

/**
 * Returns the number of elements in the path.
 *
 * @return the number of elements in the path
 */
/*public*/  int TreePath::getPathCount() {
    int        result = 0;
    for(TreePath* path = this; path != NULL; path = path->getParentPath()) {
        result++;
    }
    return result;
}

/**
 * Returns the path element at the specified index.
 *
 * @param index the index of the element requested
 * @return the element at the specified index
 * @throws IllegalArgumentException if the index is outside the
 *         range of this path
 */
/*public*/  QObject* TreePath::getPathComponent(int index) {
    int          pathLength = getPathCount();

    if(index < 0 || index >= pathLength)
        throw new IllegalArgumentException("Index " + QString::number(index) +
                                       " is out of the specified range");

    TreePath*         path = this;

    for(int i = pathLength-1; i != index; i--) {
        path = path->getParentPath();
    }
    return path->getLastPathComponent();
}

/**
 * Compares this {@code TreePath} to the specified object. This returns
 * {@code true} if {@code o} is a {@code TreePath} with the exact
 * same elements (as determined by using {@code equals} on each
 * element of the path).
 *
 * @param o the object to compare
 */
/*public*/  bool TreePath::equals(QObject* o) {
    if(o == this)
        return true;
    if(qobject_cast<TreePath*>(o)!=NULL) {
        TreePath*            oTreePath = (TreePath*)o;

        if(getPathCount() != oTreePath->getPathCount())
            return false;
        for(TreePath* path = this; path != NULL;
                path = path->getParentPath()) {
            if (!(path->getLastPathComponent() ==
                  (oTreePath->getLastPathComponent()))) {
                return false;
            }
            oTreePath = oTreePath->getParentPath();
        }
        return true;
    }
    return false;
}

/**
 * Returns the hash code of this {@code TreePath}. The hash code of a
 * {@code TreePath} is the hash code of the last element in the path.
 *
 * @return the hashCode for the object
 */
/*public*/  int TreePath::hashCode() {
//        return getLastPathComponent()->hashCode();
}

/**
 * Returns true if <code>aTreePath</code> is a
 * descendant of this
 * {@code TreePath}. A {@code TreePath} {@code P1} is a descendant of a
 * {@code TreePath} {@code P2}
 * if {@code P1} contains all of the elements that make up
 * {@code P2's} path.
 * For example, if this object has the path {@code [a, b]},
 * and <code>aTreePath</code> has the path {@code [a, b, c]},
 * then <code>aTreePath</code> is a descendant of this object.
 * However, if <code>aTreePath</code> has the path {@code [a]},
 * then it is not a descendant of this object.  By this definition
 * a {@code TreePath} is always considered a descendant of itself.
 * That is, <code>aTreePath.isDescendant(aTreePath)</code> returns
 * {@code true}.
 *
 * @param aTreePath the {@code TreePath} to check
 * @return true if <code>aTreePath</code> is a descendant of this path
 */
/*public*/  bool TreePath::isDescendant(TreePath* aTreePath) {
    if(aTreePath == this)
        return true;

    if(aTreePath != NULL) {
        int                 pathLength = getPathCount();
        int                 oPathLength = aTreePath->getPathCount();

        if(oPathLength < pathLength)
            // Can't be a descendant, has fewer components in the path.
            return false;
        while(oPathLength-- > pathLength)
            aTreePath = aTreePath->getParentPath();
        return equals(aTreePath);
    }
    return false;
}

/**
 * Returns a new path containing all the elements of this path
 * plus <code>child</code>. <code>child</code> is the last element
 * of the newly created {@code TreePath}.
 *
 * @param child the path element to add
 * @throws NullPointerException if {@code child} is {@code NULL}
 */
/*public*/  TreePath* TreePath::pathByAddingChild(QObject* child) {
    if(child == NULL)
        throw new NullPointerException("Null child not allowed");

    return new TreePath(this, child);
}

/**
 * Returns the {@code TreePath} of the parent. A return value of
 * {@code NULL} indicates this is the root node.
 *
 * @return the parent path
 */
/*public*/  TreePath* TreePath::getParentPath() {
    return parentPath;
}

/**
 * Returns a string that displays and identifies this
 * object's properties.
 *
 * @return a String representation of this object
 */
/*public*/  QString TreePath::toString() {
    QString tempSpot = "[";

    for(int counter = 0, maxCounter = getPathCount();counter < maxCounter;
        counter++) {
        if(counter > 0)
            tempSpot.append(", ");
        QObject* o = getPathComponent(counter);
        if(qobject_cast<TreeNode*>(o)!=NULL)
        {
         DefaultMutableTreeNode* v = (DefaultMutableTreeNode*)o;
         tempSpot.append(v->toString());
        }
    }
    tempSpot.append("]");
    return tempSpot;
}
//}
