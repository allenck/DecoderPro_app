#ifndef DEFAULTTREESELECTIONMODEL_H
#define DEFAULTTREESELECTIONMODEL_H
#include "treeselectionmodel.h"
#include "javaqt_global.h"

class PropertyChangeSupport;
class RowMapper;
class JAVAQTSHARED_EXPORT DefaultTreeSelectionModel : public TreeSelectionModel
{
 Q_OBJECT
public:
 DefaultTreeSelectionModel();
 /*public*/ TreePath* getSelectionPath();
 /*public*/ QList<TreePath*>* getSelectionPaths();
 /*public*/ void setSelectionMode(int mode);
 /*public*/ int getSelectionMode();
 /*public*/ void setSelectionPath(TreePath* path);
 /*public*/ void setSelectionPaths(QList<TreePath*>* pPaths);
 /*public*/ int getSelectionCount();
 /*public*/ bool isPathSelected(TreePath* path);
 /*public*/ bool isSelectionEmpty();

private:
 /** Used to make sure the paths are unique, will contain all the paths
  * in <code>selection</code>.
  */
 /*private*/ QHash<TreePath*, bool>*    uniquePaths;
 /*private*/ QHash<TreePath, bool>*    lastPaths;
 /*private*/ QList<TreePath*>*                      tempPaths;

protected:
 /** Property name for selectionMode. */
 /*public*/ static /*final*/ QString          SELECTION_MODE_PROPERTY;// = "selectionMode";

 /** Used to messaged registered listeners. */
 /*protected*/ PropertyChangeSupport*     changeSupport;

 /** Paths that are currently selected.  Will be null if nothing is
   * currently selected. */
 /*protected*/ QList<TreePath*>*                selection;

 /** Event listener list. */
 ///*protected*/ EventListenerList   listenerList = new EventListenerList();

 /** Provides a row for a given path. */
 /*transient*/ /*protected*/ RowMapper*               rowMapper;

 /** Handles maintaining the list selection model. The RowMapper is used
  * to map from a TreePath to a row, and the value is then placed here. */
 // /*protected*/ DefaultListSelectionModel     listSelectionModel;

 /** Mode for the selection, will be either SINGLE_TREE_SELECTION,
  * CONTIGUOUS_TREE_SELECTION or DISCONTIGUOUS_TREE_SELECTION.
  */
 /*protected*/ int                           selectionMode;

 /** Last path that was added. */
 /*protected*/ TreePath*                      leadPath;
 /** Index of the lead path in selection. */
 /*protected*/ int                           leadIndex;
 /** Lead row. */
 /*protected*/ int                           leadRow;
 /*protected*/ bool arePathsContiguous(QList<TreePath*>* paths);

};

#endif // DEFAULTTREESELECTIONMODEL_H
