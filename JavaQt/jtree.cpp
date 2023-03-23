#include "jtree.h"
#include "treemodel.h"
#include "treeselectionmodel.h"
#include "treeselectionevent.h"
#include "swingpropertychangesupport.h"
#include "defaultmutabletreenode.h"
#include "vptr.h"
#include <QDebug>
#include <treepath.h>
#include "treeselectionlistener.h"
#include "treeexpansionlistener.h"
#include "eventlistenerlist.h"
#include "defaulttreemodel.h"

/** Bound property name for selectionModel. */
//
    // Bound property names
    //
    /** Bound property name for <code>cellRenderer</code>. */
    /*public*/ /*final static*/ QString JTree::       CELL_RENDERER_PROPERTY = "cellRenderer";
    /** Bound property name for <code>treeModel</code>. */
    /*public*/ /*final static*/ QString JTree::       TREE_MODEL_PROPERTY = "model";
    /** Bound property name for <code>rootVisible</code>. */
    /*public*/ /*final static*/ QString JTree::       ROOT_VISIBLE_PROPERTY = "rootVisible";
    /** Bound property name for <code>showsRootHandles</code>. */
    /*public*/ /*final static*/ QString JTree::       SHOWS_ROOT_HANDLES_PROPERTY = "showsRootHandles";
    /** Bound property name for <code>rowHeight</code>. */
    /*public*/ /*final static*/ QString JTree::       ROW_HEIGHT_PROPERTY = "rowHeight";
    /** Bound property name for <code>cellEditor</code>. */
    /*public*/ /*final static*/ QString JTree::       CELL_EDITOR_PROPERTY = "cellEditor";
    /** Bound property name for <code>editable</code>. */
    /*public*/ /*final static*/ QString JTree::       EDITABLE_PROPERTY = "editable";
    /** Bound property name for <code>largeModel</code>. */
    /*public*/ /*final static*/ QString JTree::       LARGE_MODEL_PROPERTY = "largeModel";
    /** Bound property name for selectionModel. */
    /*public*/ /*final static*/ QString JTree::       SELECTION_MODEL_PROPERTY = "selectionModel";
    /** Bound property name for <code>visibleRowCount</code>. */
    /*public*/ /*final static*/ QString JTree::       VISIBLE_ROW_COUNT_PROPERTY = "visibleRowCount";
    /** Bound property name for <code>messagesStopCellEditing</code>. */
    /*public*/ /*final static*/ QString JTree::       INVOKES_STOP_CELL_EDITING_PROPERTY = "invokesStopCellEditing";
    /** Bound property name for <code>scrollsOnExpand</code>. */
    /*public*/ /*final static*/ QString JTree::       SCROLLS_ON_EXPAND_PROPERTY = "scrollsOnExpand";
    /** Bound property name for <code>toggleClickCount</code>. */
    /*public*/ /*final static*/ QString JTree::       TOGGLE_CLICK_COUNT_PROPERTY = "toggleClickCount";
    /** Bound property name for <code>leadSelectionPath</code>.
     * @since 1.3 */
    /*public*/ /*final static*/ QString JTree::       LEAD_SELECTION_PATH_PROPERTY = "leadSelectionPath";
    /** Bound property name for anchor selection path.
     * @since 1.3 */
    /*public*/ /*final static*/ QString JTree::       ANCHOR_SELECTION_PATH_PROPERTY = "anchorSelectionPath";
    /** Bound property name for expands selected paths property
     * @since 1.3 */
    /*public*/ /*final static*/ QString JTree::       EXPANDS_SELECTED_PATHS_PROPERTY = "expandsSelectedPaths";
/**
 * Max number of stacks to keep around.
 */
/*private*/ /*static*/ int JTree::TEMP_STACK_SIZE = 11;

JTree::JTree(QWidget *parent) :
  QTreeView(parent)
{
 common();
}

JTree::JTree(TreeModel* tree,QWidget *parent) :
  QTreeView(parent)
{
 common();
 this->tree = tree;
 QTreeView::setModel((QAbstractItemModel*)tree);
}

void JTree::common()
{
 selectionModel = new DefaultTreeSelectionModel();
 tree = NULL;
 rootVisible = true;
 setRootIsDecorated(true);
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 expandedStack =  QStack<QStack<TreePath*> >();
 expandedState = QHash<TreePath*, bool>();
 listenerList = new EventListenerList();

// connect(this, SIGNAL(collapsed(QModelIndex)), this, SLOT(rowCollapsed(QModelIndex)));
// connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(rowExpanded(QModelIndex)));
 connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));

}

void JTree::setShowsRootHandles(bool )
{

}

void JTree::setScrollsOnExpand(bool)
{

}

void JTree::setExpandsSelectedPaths(bool newValue )
{
 bool oldValue = expandsSelectedPaths;

 expandsSelectedPaths = newValue;
 pcs->firePropertyChange(EXPANDS_SELECTED_PATHS_PROPERTY, oldValue, newValue);
}

/**
 * Sets the expanded state of this <code>JTree</code>.
 * If <code>state</code> is
 * true, all parents of <code>path</code> and path are marked as
 * expanded. If <code>state</code> is false, all parents of
 * <code>path</code> are marked EXPANDED, but <code>path</code> itself
 * is marked collapsed.<p>
 * This will fail if a <code>TreeWillExpandListener</code> vetos it.
 */
/*protected*/ void JTree::setExpandedState(TreePath* path, bool state)
{
 if(path != NULL)
 {
  // Make sure all parents of path are expanded.
  QStack<TreePath*> stack;
  TreePath* parentPath = path->getParentPath();

  if (expandedStack.size() == 0)
  {
   stack = QStack<TreePath*>();
  }
  else {
   stack = expandedStack.pop();
  }

  try
  {
   while(parentPath != NULL) {
       if(isExpanded(parentPath)) {
           parentPath = NULL;
       }
       else {
           stack.push(parentPath);
           parentPath = parentPath->getParentPath();
       }
   }
   for(int counter = stack.size() - 1; counter >= 0; counter--)
   {
    parentPath = stack.pop();
    if(!isExpanded(parentPath))
    {
     try
     {
      fireTreeWillExpand(parentPath);
     }
     catch (ExpandVetoException* eve) {
      // Expand vetoed!
      return;
     }
     expandedState.insert(parentPath, true);
     fireTreeExpanded(parentPath);
//     if (accessibleContext != NULL) {
//         ((AccessibleJTree)accessibleContext).
//                           fireVisibleDataPropertyChange();
//     }
    }
   }
  }
  catch(Exception* ex) {}
  /*finally*/ {
      if (expandedStack.size() < TEMP_STACK_SIZE) {
          stack.clear();
          expandedStack.push(stack);
      }
  }
  if(!state) {
      // collapse last path.
      QVariant          cValue = expandedState.value(path);

      if(cValue != QVariant() && cValue.toBool()) {
          try {
              fireTreeWillCollapse(path);
          }
          catch (ExpandVetoException* eve) {
              return;
          }
          expandedState.insert(path, false);
          fireTreeCollapsed(path);
          if (removeDescendantSelectedPaths(path, false) &&
              !isPathSelected(path)) {
              // A descendant was selected, select the parent.
              addSelectionPath(path);
          }
//          if (accessibleContext != NULL) {
//              ((AccessibleJTree)accessibleContext).
//                          fireVisibleDataPropertyChange();
//          }
      }
  }
  else {
      // Expand last path.
      QVariant          cValue = expandedState.value(path);

      if(cValue == QVariant() || !cValue.toBool()) {
          try {
              fireTreeWillExpand(path);
          }
          catch (ExpandVetoException* eve) {
              return;
          }
          expandedState.insert(path, true);
          fireTreeExpanded(path);
//          if (accessibleContext != NULL) {
//              ((AccessibleJTree)accessibleContext).
//                                fireVisibleDataPropertyChange();
//          }
      }
  }
 }
}

/**
 * Selects the node identified by the specified path. If any
 * component of the path is hidden (under a collapsed node), and
 * <code>getExpandsSelectedPaths</code> is true it is
 * exposed (made viewable).
 *
 * @param path the <code>TreePath</code> specifying the node to select
 */
/*public*/ void JTree::setSelectionPath(TreePath* path) {
    getSelectionModel()->setSelectionPath(path);
}

/**
 * Returns the path to the first selected node.
 *
 * @return the <code>TreePath</code> for the first selected node,
 *          or <code>NULL</code> if nothing is currently selected
 */
/*public*/ TreePath* JTree::getSelectionPath() {
    return getSelectionModel()->getSelectionPath();
}
/**
 * Sets the tree's selection model. When a <code>NULL</code> value is
 * specified an empty
 * <code>selectionModel</code> is used, which does not allow selections.
 * <p>
 * This is a bound property.
 *
 * @param selectionModel the <code>TreeSelectionModel</code> to use,
 *          or <code>NULL</code> to disable selections
 * @see TreeSelectionModel
 * @beaninfo
 *        bound: true
 *  description: The tree's selection model.
 */
/*public*/ void JTree::setSelectionModel(TreeSelectionModel* selectionModel) {
//    if(selectionModel == NULL)
//        selectionModel = EmptySelectionModel::sharedInstance();

    TreeSelectionModel*         oldValue = this->selectionModel;

//    if (this->selectionModel != NULL && selectionRedirector != NULL) {
//        this->selectionModel.removeTreeSelectionListener
//                            (selectionRedirector);
//    }
//    if (accessibleContext != NULL) {
//       this.selectionModel.removeTreeSelectionListener((TreeSelectionListener)accessibleContext);
//       selectionModel.addTreeSelectionListener((TreeSelectionListener)accessibleContext);
//    }

    this->selectionModel = selectionModel;
//    if (selectionRedirector != NULL) {
//        this.selectionModel.addTreeSelectionListener(selectionRedirector);
//    }
    pcs->firePropertyChange(SELECTION_MODEL_PROPERTY, oldValue,
                       this->selectionModel);

//    if (accessibleContext != NULL) {
//        accessibleContext.firePropertyChange(
//                AccessibleContext.ACCESSIBLE_SELECTION_PROPERTY,
//                Boolean.valueOf(false), Boolean.valueOf(true));
//    }
}
/**
 * Returns the model for selections. This should always return a
 * non-<code>NULL</code> value. If you don't want to allow anything
 * to be selected
 * set the selection model to <code>NULL</code>, which forces an empty
 * selection model to be used.
 *
 * @see #setSelectionModel
 */
/*public*/ TreeSelectionModel* JTree::getSelectionModel() {
    return selectionModel;
}

/**
 * Adds a listener for <code>TreeSelection</code> events.
 *
 * @param tsl the <code>TreeSelectionListener</code> that will be notified
 *            when a node is selected or deselected (a "negative
 *            selection")
 */
/*public*/ void JTree::addTreeSelectionListener(TreeSelectionListener* tsl)
{
 //_TSL = tsl;
 //listenerList->add("TreeSelectionListener",tsl);
 connect(this, SIGNAL(treeSelected(TreeSelectionEvent*)), tsl, SLOT(valueChanged(TreeSelectionEvent*)));
}

void JTree::on_clicked(QModelIndex index)
{
 QString v = index.data().toString();
 TreeSelectionEvent* evt = NULL;
 //DefaultMutableTreeNode* node = VPtr<DefaultMutableTreeNode>::asPtr(index.data(Qt::UserRole));
 DefaultMutableTreeNode* node = static_cast<DefaultMutableTreeNode*>(index.internalPointer());

 QVector<MutableTreeNode*>* p = node->getPath();

 QVector<QObject*>* pp = new QVector<QObject*>();
 foreach(MutableTreeNode* n, *p)
  pp->append((QObject*)n);
 TreePath* tp = new TreePath(pp);
 pp->removeAt(0); // hack
 getSelectionModel()->setSelectionPath(tp);
 setSelectionPath(tp);
   qDebug() << "(JTree) " << node->toString();

 evt = new TreeSelectionEvent(this, tp,false, NULL, tp);
 //_TSL->valueChanged(evt);
 emit treeSelected(evt);
}

/**
 * Removes a <code>TreeSelection</code> listener.
 *
 * @param tsl the <code>TreeSelectionListener</code> to remove
 */
/*public*/ void JTree::removeTreeSelectionListener(TreeSelectionListener* /*tsl*/)
{
//    listenerList.remove(TreeSelectionListener.class,tsl);
//    if(listenerList.getListenerCount(TreeSelectionListener.class) == 0
//       && selectionRedirector != NULL) {
//        selectionModel.removeTreeSelectionListener
//            (selectionRedirector);
//        selectionRedirector = NULL;
//    }
 disconnect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
}

/**
 * Returns true if the selection is currently empty.
 *
 * @return true if the selection is currently empty
 */
/*public*/ bool JTree::isSelectionEmpty() {
    return getSelectionModel()->isSelectionEmpty();
}

/**
 * Adds a listener for <code>TreeExpansion</code> events.
 *
 * @param tel a TreeExpansionListener that will be notified when
 *            a tree node is expanded or collapsed (a "negative
 *            expansion")
 */
/*public*/ void JTree::addTreeExpansionListener(TreeExpansionListener* tel) {
//    if (settingUI) {
//        uiTreeExpansionListener = tel;
//    }
  listenerList->add("TreeExpansionListener", tel);
  connect(this, SIGNAL(treeExpanded(TreeExpansionEvent*)), tel, SLOT(treeExpanded(TreeExpansionEvent*)));
  connect(this, SIGNAL(treeCollapsed(TreeExpansionEvent*)), tel, SLOT(treeCollapsed(TreeExpansionEvent*)));

}

/*public*/ int JTree::getSelectionCount()
{
 return selectedIndexes().count();
}
/**
 * Returns true if the root node of the tree is displayed.
 *
 * @return true if the root node of the tree is displayed
 * @see #rootVisible
 */
/*public*/ bool JTree::isRootVisible() {
    return rootVisible;
}

/**
 * Determines whether or not the root node from
 * the <code>TreeModel</code> is visible.
 * <p>
 * This is a bound property.
 *
 * @param rootVisible true if the root node of the tree is to be displayed
 * @see #rootVisible
 * @beaninfo
 *        bound: true
 *  description: Whether or not the root node
 *               from the TreeModel is visible.
 */
/*public*/ void JTree::setRootVisible(bool rootVisible) {
    bool                oldValue = this->rootVisible;

    this->rootVisible = rootVisible;
    pcs->firePropertyChange(ROOT_VISIBLE_PROPERTY, oldValue, this->rootVisible);
//    if (accessibleContext != NULL) {
//        ((AccessibleJTree)accessibleContext).fireVisibleDataPropertyChange();
//    }
}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>path</code> parameter.
 *
 * @param path the <code>TreePath</code> indicating the node that was
 *          expanded
 * @see EventListenerList
 */
 /*public*/ void JTree::fireTreeExpanded(TreePath* path) {
    // Guaranteed to return a non-NULL array
    //Object[] listeners = listenerList.getListenerList();
    TreeExpansionEvent* e = NULL;
//    if (uiTreeExpansionListener != NULL) {
        e = new TreeExpansionEvent(this, path);
//        uiTreeExpansionListener.treeExpanded(e);
//    }
    // Process the listeners last to first, notifying
    // those that are interested in this event
//    for (int i = listeners.length-2; i>=0; i-=2) {
//        if (listeners[i]==TreeExpansionListener.class &&
//            listeners[i + 1] != uiTreeExpansionListener) {
//            // Lazily create the event:
//            if (e == NULL)
//                e = new TreeExpansionEvent(this, path);
//            ((TreeExpansionListener)listeners[i+1]).
//                treeExpanded(e);
//        }
//    }
  emit treeExpanded(e);
}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>path</code> parameter.
 *
 * @param path the <code>TreePath</code> indicating the node that was
 *          collapsed
 * @see EventListenerList
 */
/*public*/ void JTree::fireTreeCollapsed(TreePath* path) {
    // Guaranteed to return a non-NULL array
    //Object[] listeners = listenerList.getListenerList();
    TreeExpansionEvent* e = NULL;
//    if (uiTreeExpansionListener != NULL) {
        e = new TreeExpansionEvent(this, path);
//        uiTreeExpansionListener.treeCollapsed(e);
//    }
    // Process the listeners last to first, notifying
    // those that are interested in this event
//    for (int i = listeners.length-2; i>=0; i-=2) {
//        if (listeners[i]==TreeExpansionListener.class &&
//            listeners[i + 1] != uiTreeExpansionListener) {
//            // Lazily create the event:
//            if (e == NULL)
//                e = new TreeExpansionEvent(this, path);
//            ((TreeExpansionListener)listeners[i+1]).
//                treeCollapsed(e);
//        }
//    }
    emit treeCollapsed(e);
}
/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>path</code> parameter.
 *
 * @param path the <code>TreePath</code> indicating the node that was
 *          expanded
 * @see EventListenerList
 */
/*public*/ void JTree::fireTreeWillCollapse(TreePath* path) /*throw (ExpandVetoException)*/
{
    // Guaranteed to return a non-NULL array
    //Object[] listeners = listenerList.getListenerList();
    TreeExpansionEvent* e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
//    for (int i = listeners.length-2; i>=0; i-=2) {
//        if (listeners[i]==TreeWillExpandListener.class) {
//            // Lazily create the event:
//            if (e == NULL)
                e = new TreeExpansionEvent(this, path);
//            ((TreeWillExpandListener)listeners[i+1]).
//                treeWillCollapse(e);
//        }
//    }
    emit treeWillCollapse(e);
}
/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>path</code> parameter.
 *
 * @param path the <code>TreePath</code> indicating the node that was
 *          expanded
 * @see EventListenerList
 */
 /*public*/ void JTree::fireTreeWillExpand(TreePath* path) /*throw (ExpandVetoException)*/ {
    // Guaranteed to return a non-NULL array
    //Object[] listeners = listenerList.getListenerList();
    TreeExpansionEvent* e = NULL;
    // Process the listeners last to first, notifying
    // those that are interested in this event
//    for (int i = listeners.length-2; i>=0; i-=2) {
//        if (listeners[i]==TreeWillExpandListener.class) {
//            // Lazily create the event:
//            if (e == NULL)
                e = new TreeExpansionEvent(this, path);
//            ((TreeWillExpandListener)listeners[i+1]).
//                treeWillExpand(e);
//        }
//    }
    emit treeWillExpand(e);
}

/**
 * Ensures that the node identified by the specified path is
 * expanded and viewable. If the last item in the path is a
 * leaf, this will have no effect.
 *
 * @param path  the <code>TreePath</code> identifying a node
 */
/*public*/ void JTree::expandPath(TreePath* path) {
    // Only expand if not leaf!
    TreeModel* _model = qobject_cast<TreeModel*>(model());

    if(path != NULL && _model != NULL &&
       !_model->isLeaf(path->getLastPathComponent())) {
        setExpandedState(path, true);
    }
}

/**
 * Ensures that the node identified by the specified path is
 * collapsed and viewable.
 *
 * @param path  the <code>TreePath</code> identifying a node
  */
/*public*/ void JTree::collapsePath(TreePath* path) {
    setExpandedState(path, false);
}

/**
 * Ensures that the node in the specified row is collapsed.
 * <p>
 * If <code>row</code> is &lt; 0 or &gt;= <code>getRowCount</code> this
 * will have no effect.
 *
 * @param row  an integer specifying a display row, where 0 is the
 *             first row in the display
  */
/*public*/ void JTree::collapseRow(int row) {
    collapsePath(getPathForRow(row));
}

/**
 * Returns true if the node at the specified display row is currently
 * expanded.
 *
 * @param row  the row to check, where 0 is the first row in the
 *             display
 * @return true if the node is currently expanded, otherwise false
 */
/*public*/ bool JTree::isExpanded(int row) {
#if 0
    TreeUI                  tree = getUI();

    if(tree != NULL) {
        TreePath         path = tree.getPathForRow(this, row);
#endif
        TreePath* path = getPathForRow(row);
        if(path != NULL) {
            bool value = expandedState.value(path);

            //return (value != NULL && value.toBoo);
            return value;
        }
    return false;
}

/**
 * Returns true if the node identified by the path is currently expanded,
 *
 * @param path  the <code>TreePath</code> specifying the node to check
 * @return false if any of the nodes in the node's path are collapsed,
 *               true if all nodes in the path are expanded
 */
/*public*/ bool JTree::isExpanded(TreePath* path) {

    if(path == NULL)
        return false;
    QVariant  value;

    do{
        value = expandedState.value(path);
        if(value == QVariant() || !(value).toBool())
            return false;
    } while( (path=path->getParentPath())!=NULL );

    return true;
}

/**
 * Removes any paths in the selection that are descendants of
 * <code>path</code>. If <code>includePath</code> is true and
 * <code>path</code> is selected, it will be removed from the selection.
 *
 * @return true if a descendant was selected
 * @since 1.3
 */
/*protected*/ bool JTree::removeDescendantSelectedPaths(TreePath* path,
                                                bool includePath) {
    QVector<TreePath*> toRemove = getDescendantSelectedPaths(path, includePath);

    if (!toRemove.isEmpty()) {
        getSelectionModel()->removeSelectionPaths(toRemove);
        return true;
    }
    return false;
}
/**
 * Returns an array of paths in the selection that are descendants of
 * <code>path</code>. The returned array may contain <code>NULL</code>s.
 */
/*private*/ QVector<TreePath*> JTree::getDescendantSelectedPaths(TreePath* path,
                                              bool includePath) {
    TreeSelectionModel*   sm = getSelectionModel();
    QVector<TreePath*>           selPaths = (sm != NULL) ? sm->getSelectionPaths() :
                                    QVector<TreePath*>();

    if(!selPaths.isEmpty()) {
        bool        shouldRemove = false;

        for(int counter = selPaths.length() - 1; counter >= 0; counter--) {
            if(selPaths[counter] != NULL &&
               path->isDescendant(selPaths[counter]) &&
               (path != (selPaths[counter]) || includePath))
                shouldRemove = true;
            else
                selPaths[counter] = NULL;
        }
        if(!shouldRemove) {
            selPaths = QVector<TreePath*>();
        }
        return selPaths;
    }
    return QVector<TreePath*>();
}
/**
 * Returns true if the item identified by the path is currently selected.
 *
 * @param path a <code>TreePath</code> identifying a node
 * @return true if the node is selected
 */
/*public*/ bool JTree::isPathSelected(TreePath* path) {
    return getSelectionModel()->isPathSelected(path);
}

/**
 * Adds the node identified by the specified <code>TreePath</code>
 * to the current selection. If any component of the path isn't
 * viewable, and <code>getExpandsSelectedPaths</code> is true it is
 * made viewable.
 * <p>
 * Note that <code>JTree</code> does not allow duplicate nodes to
 * exist as children under the same parent -- each sibling must be
 * a unique object.
 *
 * @param path the <code>TreePath</code> to add
 */
/*public*/ void JTree::addSelectionPath(TreePath* path) {
    getSelectionModel()->addSelectionPath(path);
}

/**
 * Returns the path for the specified row.  If <code>row</code> is
 * not visible, or a {@code TreeUI} has not been set, <code>NULL</code>
 * is returned.
 *
 * @param row  an integer specifying a row
 * @return the <code>TreePath</code> to the specified node,
 *          <code>NULL</code> if <code>row &lt; 0</code>
 *          or <code>row &gt;= getRowCount()</code>
 */
/*public*/ TreePath* JTree::getPathForRow(int row) {
#if 0
    TreeUI                  tree = getUI();

    if(tree != NULL)
        return tree.getPathForRow(this, row);
    return NULL;

#else
 DefaultMutableTreeNode* node = VPtr<DefaultMutableTreeNode>::asPtr(((DefaultTreeModel*)model())->data(model()->index(row,0),Qt::UserRole));
 QList<MutableTreeNode*>* path = ((DefaultTreeModel*)model())->getPathToRoot(node);
 QVector<QObject*>* ol = new  QVector<QObject*>();
 foreach(TreeNode* node, *path)
  ol->append(node->tself());
 return new TreePath(ol);
#endif
}

/**
 * Removes the nodes identified by the specified paths from the
 * current selection.
 *
 * @param paths an array of <code>TreePath</code> objects that
 *              specifies the nodes to remove
 */
/*public*/ void JTree::removeSelectionPaths(QVector<TreePath*> paths) {
    this->getSelectionModel()->removeSelectionPaths(paths);
}
ExpandVetoException::ExpandVetoException(QString s) {msg = s;}

void JTree::rowCollapsed(const QModelIndex index)
{
 qDebug() << "row collapsing" << index << index.data().toString() << " rows: " << index.model()->rowCount();
 if(QString(index.model()->metaObject()->className()) != "DefaultTreeModel") return;

 DefaultMutableTreeNode* node = VPtr<DefaultMutableTreeNode>::asPtr(index.data(Qt::UserRole));

 QList<MutableTreeNode*>* path = ((DefaultTreeModel*)index.model())->getPathToRoot(node);
 QVector<QObject*>* ol = new  QVector<QObject*>();
 foreach(MutableTreeNode* node, *path)
  ol->append((QObject*)node);
 TreeExpansionEvent* tee = new TreeExpansionEvent((QObject*)this, new TreePath(ol));
 emit treeCollapsed(tee);

}
void JTree::rowExpanded(const QModelIndex index)
{

 qDebug() << "row expanding" << index << index.data().toString() << index.model()->rowCount();
 if(QString(index.model()->metaObject()->className()) != "DefaultTreeModel") return;

 DefaultMutableTreeNode* node = VPtr<DefaultMutableTreeNode>::asPtr(index.data(Qt::UserRole));

 QList<MutableTreeNode*>* path = ((DefaultTreeModel*)index.model())->getPathToRoot(node);
 QVector<QObject*>* ol = new  QVector<QObject*>();
 foreach(MutableTreeNode* node, *path)
  ol->append((QObject*)node);
 TreeExpansionEvent* tee = new TreeExpansionEvent((QObject*)this, new TreePath(ol));
 emit treeExpanded(tee);
}

/*public*/ int  JTree::getRowCount(){
    TreeModel* dm = nullptr;
    int c = 0;
    TreeModel* m =  model();
    if(qobject_cast<DefaultTreeModel*>(m))
    {
        dm = (DefaultTreeModel*)m;
        c = dm->rowCount(QModelIndex());
        return c;}
    c = m->rowCount(QModelIndex());
    return c;
}

/*public*/ void JTree::setCellRenderer(TreeCellRenderer* r)
{
 _treeCellRenderer = r;
}

/*public*/ void JTree::setModel(TreeModel* m)
{
 QTreeView::setModel(m);
 if(qobject_cast<DefaultTreeModel*>(m))
     tree = (DefaultTreeModel*)m;
}

/*public*/ TreeModel *JTree::model()
{
  if(tree)
      return tree;
  return nullptr;
}
