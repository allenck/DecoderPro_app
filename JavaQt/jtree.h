#ifndef JTREE_H
#define JTREE_H

#include <QTreeView>
#include "javaqt_global.h"
#include "treepath.h"
#include "defaulttreeselectionmodel.h"
#include "propertychangelistener.h"
#include "treeexpansionevent.h"
#include <QStack>
#include "exceptions.h"
#include "treeexpansionlistener.h"
#include "treeselectionlistener.h"

class JAVAQTSHARED_EXPORT ExpandVetoException : public Exception
{
public:
   ExpandVetoException(QString s = "");
   ~ExpandVetoException() throw() {}
};

//class EmptySelectionModel;
class TreeSelectionListener;
class PropertyChangeSupport;
class TreeSelectionModel;
class TreeModel;
class JAVAQTSHARED_EXPORT JTree : public QTreeView //, public TreeSelectionListener, public TreeExpansionListener
{
 Q_OBJECT
 //Q_INTERFACES(TreeSelectionListener TreeExpansionListener)
public:
 explicit JTree(QWidget *parent = 0);
 JTree(TreeModel* tree,QWidget *parent = 0);
 void setShowsRootHandles(bool b);
 void setScrollsOnExpand(bool b);
 void setExpandsSelectedPaths(bool );
 /*public*/ TreePath* getSelectionPath();
 /*public*/ TreeSelectionModel* getSelectionModel();
 /*public*/ void setSelectionModel(TreeSelectionModel* selectionModel);
 //
 // Bound property names
 //
 /** Bound property name for <code>cellRenderer</code>. */
 /*public*/ /*final*/ static QString        CELL_RENDERER_PROPERTY;// = "cellRenderer";
 /** Bound property name for <code>treeModel</code>. */
 /*public*/ /*final*/ static QString        TREE_MODEL_PROPERTY;// = "model";
 /** Bound property name for <code>rootVisible</code>. */
 /*public*/ /*final*/ static QString        ROOT_VISIBLE_PROPERTY;// = "rootVisible";
 /** Bound property name for <code>showsRootHandles</code>. */
 /*public*/ /*final*/ static QString        SHOWS_ROOT_HANDLES_PROPERTY;// = "showsRootHandles";
 /** Bound property name for <code>rowHeight</code>. */
 /*public*/ /*final*/ static QString        ROW_HEIGHT_PROPERTY;// = "rowHeight";
 /** Bound property name for <code>cellEditor</code>. */
 /*public*/ /*final*/ static QString        CELL_EDITOR_PROPERTY;// = "cellEditor";
 /** Bound property name for <code>editable</code>. */
 /*public*/ /*final*/ static QString        EDITABLE_PROPERTY;// = "editable";
 /** Bound property name for <code>largeModel</code>. */
 /*public*/ /*final*/ static QString        LARGE_MODEL_PROPERTY;// = "largeModel";
 /** Bound property name for selectionModel. */
 /*public*/ /*final*/ static QString        SELECTION_MODEL_PROPERTY;// = "selectionModel";
 /** Bound property name for <code>visibleRowCount</code>. */
 /*public*/ /*final*/ static QString        VISIBLE_ROW_COUNT_PROPERTY;// = "visibleRowCount";
 /** Bound property name for <code>messagesStopCellEditing</code>. */
 /*public*/ /*final*/ static QString        INVOKES_STOP_CELL_EDITING_PROPERTY;// = "invokesStopCellEditing";
 /** Bound property name for <code>scrollsOnExpand</code>. */
 /*public*/ /*final*/ static QString        SCROLLS_ON_EXPAND_PROPERTY;// = "scrollsOnExpand";
 /** Bound property name for <code>toggleClickCount</code>. */
 /*public*/ /*final*/ static QString        TOGGLE_CLICK_COUNT_PROPERTY;// = "toggleClickCount";
 /** Bound property name for <code>leadSelectionPath</code>.
  * @since 1.3 */
 /*public*/ /*final*/ static QString        LEAD_SELECTION_PATH_PROPERTY;// = "leadSelectionPath";
 /** Bound property name for anchor selection path.
  * @since 1.3 */
 /*public*/ /*final*/ static QString        ANCHOR_SELECTION_PATH_PROPERTY;// = "anchorSelectionPath";
 /** Bound property name for expands selected paths property
  * @since 1.3 */
 /*public*/ /*final*/ static QString        EXPANDS_SELECTED_PATHS_PROPERTY;// = "expandsSelectedPaths";PropertyChangeSupport* pcs;

 /*public*/ void setSelectionPath(TreePath* path);
 /*public*/ void addTreeSelectionListener(TreeSelectionListener* tsl);
 /*public*/ void removeTreeSelectionListener(TreeSelectionListener* tsl);
 /*public*/ bool isSelectionEmpty();
 /*public*/ int getSelectionCount();
 /*public*/ void expandPath(TreePath* path);
 /*public*/ bool isRootVisible();
 /*public*/ void setRootVisible(bool rootVisible);
 /*public*/ void fireTreeCollapsed(TreePath* path);
 /*public*/ void fireTreeExpanded(TreePath* path);
 /*public*/ void fireTreeWillCollapse(TreePath* path) throw (ExpandVetoException);
 /*public*/ void fireTreeWillExpand(TreePath* path) throw (ExpandVetoException);
 /*public*/ void expandRow(int row);
 /*public*/ void collapsePath(TreePath* path);
 /*public*/ void collapseRow(int row);
 /*public*/ bool isExpanded(int row);
 /*public*/ bool isExpanded(TreePath* path);
 /*public*/ bool isPathSelected(TreePath* path);
 /*public*/ void addSelectionPath(TreePath* path);
 /*public*/ TreePath* getPathForRow(int row);
 /*public*/ void removeSelectionPaths(QVector<TreePath*> paths);
 /*public*/ void addTreeExpansionListener(TreeExpansionListener* tel);


signals:
 void treeCollapsed(TreeExpansionEvent*);
 void treeExpanded(TreeExpansionEvent*);
 void treeWillExpand(TreeExpansionEvent*);
 void treeWillCollapse(TreeExpansionEvent*);
 void treeSelected(TreeSelectionEvent*);

public slots:

private:
 void common();
 TreeModel* tree;
 TreeSelectionModel* selectionModel;
 //TreeSelectionListener* _TSL; // note: only one listener supported at this time.
 PropertyChangeSupport* pcs;
 /*private*/ static int                TEMP_STACK_SIZE;// = 11;

 /**
  * True if paths in the selection should be expanded.
  */
 /*private*/ bool expandsSelectedPaths;
 /**
  * Used when <code>setExpandedState</code> is invoked,
  * will be a <code>Stack</code> of <code>Stack</code>s.
  */
 /*transient*/ /*private*/ QStack<QStack<TreePath*> > expandedStack;
 /*private*/ QVector<TreePath*> getDescendantSelectedPaths(TreePath* path,
                                               bool includePath);

protected:
 /**
  * True if the root node is displayed, false if its children are
  * the highest visible nodes.
  */
 /*protected*/ bool rootVisible;
 /*protected*/ void setExpandedState(TreePath* path, bool state);
 QHash<TreePath*, bool> expandedState;
 /*protected*/ bool removeDescendantSelectedPaths(TreePath* path, bool includePath);
 /** A list of event listeners for this component. */
 /*protected*/ EventListenerList* listenerList;// = new EventListenerList();

protected slots:
 void rowCollapsed(const QModelIndex index);
 void rowExpanded(const QModelIndex index);
 void on_clicked(QModelIndex);

};
#if 0
/**
 * <code>EmptySelectionModel</code> is a <code>TreeSelectionModel</code>
 * that does not allow anything to be selected.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 */
//@SuppressWarnings("serial")
/*protected*/ /*static*/ class EmptySelectionModel : public
          DefaultTreeSelectionModel
{
 Q_OBJECT
protected:
    /**
     * The single instance of {@code EmptySelectionModel}.
     */
    /*protected*/ static /*final*/ EmptySelectionModel* sharedInstance =
        new EmptySelectionModel();
public:
 EmptySelectionModel() : DefaultTreeSelectionModel(){}
    /**
     * Returns the single instance of {@code EmptySelectionModel}.
     *
     * @return single instance of {@code EmptySelectionModel}
     */
    static /*public*/ EmptySelectionModel* sharedInstance() {
        return sharedInstance;
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param paths the paths to select; this is ignored
     */
    /*public*/  void setSelectionPaths(QVector<TreePath*> /*paths*/) {}

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param paths the paths to add to the selection; this is ignored
     */
    /*public*/ void addSelectionPaths(QVector<TreePath*>  /*paths*/) {}

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param paths the paths to remove; this is ignored
     */
    /*public*/ void removeSelectionPaths(QVector<TreePath*> /*paths*/) {}

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param mode the selection mode; this is ignored
     * @since 1.7
     */
    /*public*/ void setSelectionMode(int /*mode*/) {
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param mapper the {@code RowMapper} instance; this is ignored
     * @since 1.7
     */
    /*public*/ void setRowMapper(RowMapper* /*mapper*/) {
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param listener the listener to add; this is ignored
     * @since 1.7
     */
    /*public*/ void addTreeSelectionListener(TreeSelectionListener* /*listener*/) {
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param listener the listener to remove; this is ignored
     * @since 1.7
     */
    /*public*/ void removeTreeSelectionListener(
            TreeSelectionListener* /*listener*/) {
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param listener the listener to add; this is ignored
     * @since 1.7
     */
    /*public*/ void addPropertyChangeListener(
                            PropertyChangeListener* /*listener*/) {
    }

    /**
     * This is overriden to do nothing; {@code EmptySelectionModel}
     * does not allow a selection.
     *
     * @param listener the listener to remove; this is ignored
     * @since 1.7
     */
    /*public*/ void removePropertyChangeListener(
                            PropertyChangeListener* /*listener*/) {
    }
};
#endif

#endif // JTREE_H
