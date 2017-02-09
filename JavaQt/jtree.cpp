#include "jtree.h"
#include "treemodel.h"
#include "treeselectionmodel.h"
#include "treeselectionevent.h"
#include "propertychangesupport.h"
#include "defaultmutabletreenode.h"
#include "vptr.h"
#include <QDebug>
#include <treepath.h>
#include "treeselectionlistener.h"

/** Bound property name for selectionModel. */
    /*public*/ /*final*/ /*static*/ QString        JTree::SELECTION_MODEL_PROPERTY = "selectionModel";
JTree::JTree(QWidget *parent) :
  QTreeView(parent)
{
 tree = NULL;
 selectionModel = NULL;
 pcs = new PropertyChangeSupport(this);
}

JTree::JTree(TreeModel* tree,QWidget *parent) :
  QTreeView(parent)
{
 this->tree = tree;
 setModel((QAbstractItemModel*)tree);
 pcs = new PropertyChangeSupport(this);
}
void JTree::setShowsRootHandles(bool )
{

}

void JTree::setScrollsOnExpand(bool)
{

}

void JTree::setExpandsSelectedPaths(bool )
{

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
 *          or <code>null</code> if nothing is currently selected
 */
/*public*/ TreePath* JTree::getSelectionPath() {
    return getSelectionModel()->getSelectionPath();
}
/**
 * Sets the tree's selection model. When a <code>null</code> value is
 * specified an empty
 * <code>selectionModel</code> is used, which does not allow selections.
 * <p>
 * This is a bound property.
 *
 * @param selectionModel the <code>TreeSelectionModel</code> to use,
 *          or <code>null</code> to disable selections
 * @see TreeSelectionModel
 * @beaninfo
 *        bound: true
 *  description: The tree's selection model.
 */
/*public*/ void JTree::setSelectionModel(TreeSelectionModel* selectionModel) {
//    if(selectionModel == NULL)
//        selectionModel = EmptySelectionModel.sharedInstance();

    TreeSelectionModel*         oldValue = this->selectionModel;

//    if (this->selectionModel != NULL && selectionRedirector != NULL) {
//        this->selectionModel.removeTreeSelectionListener
//                            (selectionRedirector);
//    }
//    if (accessibleContext != null) {
//       this.selectionModel.removeTreeSelectionListener((TreeSelectionListener)accessibleContext);
//       selectionModel.addTreeSelectionListener((TreeSelectionListener)accessibleContext);
//    }

    this->selectionModel = selectionModel;
//    if (selectionRedirector != null) {
//        this.selectionModel.addTreeSelectionListener(selectionRedirector);
//    }
    pcs->firePropertyChange(SELECTION_MODEL_PROPERTY, oldValue,
                       this->selectionModel);

//    if (accessibleContext != null) {
//        accessibleContext.firePropertyChange(
//                AccessibleContext.ACCESSIBLE_SELECTION_PROPERTY,
//                Boolean.valueOf(false), Boolean.valueOf(true));
//    }
}
/**
 * Returns the model for selections. This should always return a
 * non-<code>null</code> value. If you don't want to allow anything
 * to be selected
 * set the selection model to <code>null</code>, which forces an empty
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
 _TSL = tsl;
 connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
}

void JTree::on_clicked(QModelIndex index)
{
 QString v = index.data().toString();
 TreeSelectionEvent* evt = NULL;
 DefaultMutableTreeNode* node = VPtr<DefaultMutableTreeNode>::asPtr(index.data(Qt::UserRole));

 QVector<TreeNode*>* p = node->getPath();

 QList<QObject*>* pp = new QList<QObject*>();
 foreach(TreeNode* n, *p)
  pp->append(n);
 TreePath* tp = new TreePath(pp);
 pp->removeAt(0); // hack
 getSelectionModel()->setSelectionPath(tp);
 setSelectionPath(tp);
   qDebug() << "(JTree) " << node->toString();

 evt = new TreeSelectionEvent(this, tp,false, NULL, tp);
 _TSL->valueChanged(evt);
}
/**
 * Removes a <code>TreeSelection</code> listener.
 *
 * @param tsl the <code>TreeSelectionListener</code> to remove
 */
/*public*/ void JTree::removeTreeSelectionListener(TreeSelectionListener* tsl)
{
//    listenerList.remove(TreeSelectionListener.class,tsl);
//    if(listenerList.getListenerCount(TreeSelectionListener.class) == 0
//       && selectionRedirector != null) {
//        selectionModel.removeTreeSelectionListener
//            (selectionRedirector);
//        selectionRedirector = null;
//    }
 disconnect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(on_clicked(QModelIndex)));
}

