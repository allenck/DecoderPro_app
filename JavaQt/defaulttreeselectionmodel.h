#ifndef DEFAULTTREESELECTIONMODEL_H
#define DEFAULTTREESELECTIONMODEL_H
#include "treeselectionmodel.h"
#include "javaqt_global.h"
#include "defaultlistselectionmodel.h"

class EventListenerList;
class PropertyChangeSupport;
class RowMapper;
class JAVAQTSHARED_EXPORT DefaultTreeSelectionModel : public TreeSelectionModel
{
 Q_OBJECT
public:
 DefaultTreeSelectionModel();
 /*public*/ TreePath* getSelectionPath();
 /*public*/ QVector<TreePath*> getSelectionPaths();
 /** Property name for selectionMode. */
 /*public*/ static /*final*/ QString          SELECTION_MODE_PROPERTY;// = "selectionMode";
 /*public*/ void setSelectionMode(int mode);
 /*public*/ int getSelectionMode();
 /*public*/ void setSelectionPath(TreePath* path);
 /*public*/ void setSelectionPaths(QVector<TreePath*> pPaths);
 /*public*/ int getSelectionCount();
 /*public*/ bool isPathSelected(TreePath* path);
 /*public*/ bool isSelectionEmpty();
 /*public*/ void clearSelection();
 /*public*/ void addTreeSelectionListener(TreeSelectionListener* x);
 /*public*/ void removeTreeSelectionListener(TreeSelectionListener* x);
 /*public*/ QVector<TreeSelectionListener*> getTreeSelectionListeners();
 /*public*/ QVector<int> getSelectionRows();
 /*public*/ int getMinSelectionRow();
 /*public*/ int getMaxSelectionRow();
 /*public*/ bool isRowSelected(int row);
 /*public*/ void resetRowSelection();
 /*public*/ int getLeadSelectionRow();
 /*public*/ /*synchronized*/ void addPropertyChangeListener( PropertyChangeListener* listener);
 /*public*/ /*synchronized*/ void removePropertyChangeListener( PropertyChangeListener* listener);
 /*public*/ QList<PropertyChangeListener*>* getPropertyChangeListeners();
 /*public*/ QString toString();
 /*public*/ QObject* clone() throw (CloneNotSupportedException);
// template<class T>
// /*public*/ /*<T extends EventListener>*/ QVector<T*> getListeners(QString listenerType);
 /*public*/ TreePath* getLeadSelectionPath();


private:
 /** Used to make sure the paths are unique, will contain all the paths
  * in <code>selection</code>.
  */
 /*private*/ QHash<TreePath*, bool>*    uniquePaths;
 /*private*/ QHash<TreePath*, bool>*    lastPaths;
 /*private*/ QVector<TreePath*>                      tempPaths;

protected:

 /** Used to messaged registered listeners. */
 /*protected*/ PropertyChangeSupport*     changeSupport;

 /** Paths that are currently selected.  Will be null if nothing is
   * currently selected. */
 /*protected*/ QVector<TreePath*>                selection;

 /** Event listener list. */
 /*protected*/ EventListenerList*   listenerList;// = new EventListenerList();

 /** Provides a row for a given path. */
 /*transient*/ /*protected*/ RowMapper* rowMapper;

 /** Handles maintaining the list selection model. The RowMapper is used
  * to map from a TreePath to a row, and the value is then placed here. */
 /*protected*/ DefaultListSelectionModel*     listSelectionModel;

 /** Mode for the selection, will be either SINGLE_TREE_SELECTION,
  * CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
  */
 /*protected*/ int selectionMode;

 /** Last path that was added. */
 /*protected*/ TreePath* leadPath;
 /** Index of the lead path in selection. */
 /*protected*/ int leadIndex;
 /** Lead row. */
 /*protected*/ int                           leadRow;
 /*protected*/ bool arePathsContiguous(QVector<TreePath*> paths);
 /*protected*/ void fireValueChanged(TreeSelectionEvent* e);
 /*protected*/ void insureRowContinuity();
 /*protected*/ bool canPathsBeAdded(QVector<TreePath*> paths);
 /*protected*/ bool canPathsBeRemoved(QVector<TreePath*> paths);
 /*protected*/ void updateLeadIndex();
 /*protected*/ void insureUniqueness();

};
class PathPlaceHolder
{
protected:
/*protected*/ bool             isNew;
/*protected*/ TreePath*           path;

PathPlaceHolder(TreePath* path, bool isNew) {
    this->path = path;
    this->isNew = isNew;
 }
};
#endif // DEFAULTTREESELECTIONMODEL_H
