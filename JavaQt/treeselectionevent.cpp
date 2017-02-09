#include "treeselectionevent.h"
#include "treepath.h"

 /**
  * An event that characterizes a change in the current
  * selection.  The change is based on any number of paths.
  * TreeSelectionListeners will generally query the source of
  * the event for the new selected status of each potentially
  * changed row.
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
  * @see TreeSelectionListener
  * @see javax.swing.tree.TreeSelectionModel
  *
  * @author Scott Violet
  */
// /*public*/ class TreeSelectionEvent extends EventObject
// {

/**
  * Represents a change in the selection of a TreeSelectionModel.
  * paths identifies the paths that have been either added or
  * removed from the selection.
  *
  * @param source source of event
  * @param paths the paths that have changed in the selection
  */
/*public*/ TreeSelectionEvent::TreeSelectionEvent(QObject* source, QList<TreePath*>* paths,
                          QList<bool>* areNew, TreePath* oldLeadSelectionPath,
                          TreePath* newLeadSelectionPath)
: QObject(source)
{
    //super(source);
    this->paths = paths;
    this->areNew = areNew;
    this->oldLeadSelectionPath = oldLeadSelectionPath;
    this->newLeadSelectionPath = newLeadSelectionPath;
}

/**
  * Represents a change in the selection of a TreeSelectionModel.
  * path identifies the path that have been either added or
  * removed from the selection.
  *
  * @param source source of event
  * @param path the path that has changed in the selection
  * @param isNew whether or not the path is new to the selection, false
  * means path was removed from the selection.
  */
/*public*/ TreeSelectionEvent::TreeSelectionEvent(QObject* source, TreePath* path, bool isNew,
                          TreePath* oldLeadSelectionPath,
                          TreePath* newLeadSelectionPath)
: QObject(source)
{
    //super(source);
    paths = new QList<TreePath*>(); //[1];
    paths->append(path);
    areNew = new QList<bool>();
    areNew->append(isNew);
    this->oldLeadSelectionPath = oldLeadSelectionPath;
    this->newLeadSelectionPath = newLeadSelectionPath;
}

/**
  * Returns the paths that have been added or removed from the
  * selection.
  */
/*public*/ QList<TreePath*>* TreeSelectionEvent::getPaths()
{
    int                  numPaths;
    QList<TreePath*>*          retPaths;

    numPaths = paths->length();
    retPaths = new QList<TreePath*>();//TreePath[numPaths];
    for(int i=0; i < numPaths; i++) retPaths->append(NULL);
    //System.arraycopy(paths, 0, retPaths, 0, numPaths);
    return retPaths;
}

/**
  * Returns the first path element.
  */
/*public*/ TreePath* TreeSelectionEvent::getPath()
{
    return paths->at(0);
}

/**
 * Returns whether the path identified by {@code getPath} was
 * added to the selection.  A return value of {@code true}
 * indicates the path identified by {@code getPath} was added to
 * the selection. A return value of {@code false} indicates {@code
 * getPath} was selected, but is no longer selected.
 *
 * @return {@code true} if {@code getPath} was added to the selection,
 *         {@code false} otherwise
 */
/*public*/ bool TreeSelectionEvent::isAddedPath() {
    return areNew->at(0);
}

/**
 * Returns whether the specified path was added to the selection.
 * A return value of {@code true} indicates the path identified by
 * {@code path} was added to the selection. A return value of
 * {@code false} indicates {@code path} is no longer selected. This method
 * is only valid for the paths returned from {@code getPaths()}; invoking
 * with a path not included in {@code getPaths()} throws an
 * {@code IllegalArgumentException}.
 *
 * @param path the path to test
 * @return {@code true} if {@code path} was added to the selection,
 *         {@code false} otherwise
 * @throws IllegalArgumentException if {@code path} is not contained
 *         in {@code getPaths}
 * @see #getPaths
 */
/*public*/ bool TreeSelectionEvent::isAddedPath(TreePath* path) {
    for(int counter = paths->length() - 1; counter >= 0; counter--)
        if(paths->at(counter) == (path))
            return areNew->at(counter);
    //throw new IllegalArgumentException("path is not a path identified by the TreeSelectionEvent");
}

/**
 * Returns whether the path at {@code getPaths()[index]} was added
 * to the selection.  A return value of {@code true} indicates the
 * path was added to the selection. A return value of {@code false}
 * indicates the path is no longer selected.
 *
 * @param index the index of the path to test
 * @return {@code true} if the path was added to the selection,
 *         {@code false} otherwise
 * @throws IllegalArgumentException if index is outside the range of
 *         {@code getPaths}
 * @see #getPaths
 *
 * @since 1.3
 */
/*public*/ bool TreeSelectionEvent::isAddedPath(int index) {
    if (paths == NULL || index < 0 || index >= paths->length())
    {
        //throw new IllegalArgumentException("index is beyond range of added paths identified by TreeSelectionEvent");
     Q_ASSERT(false);
    }
    return areNew->at(index);
}

/**
 * Returns the path that was previously the lead path.
 */
/*public*/ TreePath* TreeSelectionEvent::getOldLeadSelectionPath() {
    return oldLeadSelectionPath;
}

/**
 * Returns the current lead path.
 */
/*public*/ TreePath* TreeSelectionEvent::getNewLeadSelectionPath() {
    return newLeadSelectionPath;
}

/**
 * Returns a copy of the receiver, but with the source being newSource.
 */
/*public*/ QObject* TreeSelectionEvent::cloneWithSource(QObject* newSource) {
  // Fix for IE bug - crashing
  return new TreeSelectionEvent(newSource, paths,areNew,
                                oldLeadSelectionPath,
                                newLeadSelectionPath);
}
