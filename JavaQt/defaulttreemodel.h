#ifndef DEFAULTTREEMODEL_H
#define DEFAULTTREEMODEL_H
#include "treemodel.h"
#include "javaqt_global.h"
#include "catalogtree.h"

class TreeNode;
//class EventListenerList;
class MutableTreeNode;
class JAVAQTSHARED_EXPORT DefaultTreeModel : public CatalogTree//TreeModel
{
    Q_OBJECT
public:
    //explicit DefaultTreeModel(QObject *parent = 0);
    /*public*/ DefaultTreeModel(TreeNode* root, bool asksAllowsChildren = false, QObject *parent = 0);
    /*public*/ void setAsksAllowsChildren(bool newValue);
    /*public*/ bool asksAllowsChildren();
    /*public*/ void setRoot(TreeNode* root);
    /*public*/ QObject* getRoot() ;
    /*public*/ int getIndexOfChild(QObject* parent, QObject* child) ;
    /*public*/ QObject* getChild(QObject* parent, int index);
    /*public*/ int getChildCount(QObject* parent);
    /*public*/ bool isLeaf(QObject* node) ;
    /*public*/ void reload() ;
    /*public*/ void valueForPathChanged(TreePath* path, QVariant newValue);
    /*public*/ void insertNodeInto(MutableTreeNode* newChild,
                               MutableTreeNode* parent, int index);
    /*public*/ void removeNodeFromParent(MutableTreeNode* node);
    /*public*/ void nodeChanged(TreeNode* node) ;
    /*public*/ void reload(TreeNode* node) ;
    /*public*/ void nodesWereInserted(TreeNode* node, QList<int>* childIndices);
    /*public*/ void nodesWereRemoved(TreeNode* node, QList<int>* childIndices,
                                 QList<QObject*>* removedChildren) ;
    /*public*/ void nodesChanged(TreeNode* node, QList<int>* childIndices) ;
    /*public*/ void nodeStructureChanged(TreeNode* node);
    /*public*/ QList<TreeNode*>* getPathToRoot(TreeNode* aNode);
//    /*public*/ void addTreeModelListener(TreeModelListener* l);
//    /*public*/ void removeTreeModelListener(TreeModelListener* l);
//    /*public*/ QList<TreeModelListener*> getTreeModelListeners();
     void setState(int /*s*/){}
     int getState(){return 0;}

     QModelIndex index(int row, int column, const QModelIndex &parent) const;
     QModelIndex parent(const QModelIndex &child) const;
     int columnCount(const QModelIndex &parent) const;
     int rowCount(const QModelIndex &parent) const;
     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation, int role) const;
signals:
    void treeStructureChanged(QObject* source, TreePath* path);
    void treeNodesChanged(QObject* source, QList<QObject*>* path,
                          QList<int>* childIndices,
                          QList<QObject*>* children);
    void treeNodesInserted(QObject* source, QList<QObject*>* path,
                          QList<int>* childIndices,
                          QList<QObject*>* children);
    void treeNodesRemoved(QObject* source, QList<QObject*>* path,
                          QList<int>* childIndices,
                          QList<QObject*>* children);
    void treeStructureChanged(QObject* source, QList<QObject*>* path,
                          QList<int>* childIndices,
                          QList<QObject*>* children);

public slots:
private:
    /*private*/ void fireTreeStructureChanged(QObject* source, TreePath* path);
    bool _asksAllowsChildren;
protected:
    /** Root of the tree. */
    /*protected*/ TreeNode* root;
    /** Listeners. */
//    /*protected*/ EventListenerList* listenerList = new EventListenerList();
    /**
      * Determines how the <code>isLeaf</code> method figures
      * out if a node is a leaf node. If true, a node is a leaf
      * node if it does not allow children. (If it allows
      * children, it is not a leaf node, even if no children
      * are present.) That lets you distinguish between <i>folder</i>
      * nodes and <i>file</i> nodes in a file system, for example.
      * <p>
      * If this value is false, then any node which has no
      * children is a leaf node, and any node may acquire
      * children.
      *
      * @see TreeNode#getAllowsChildren
      * @see TreeModel#isLeaf
      * @see #setAsksAllowsChildren
      */
//    /*protected*/ bool asksAllowsChildren;
    /*protected*/ QList<TreeNode*>* getPathToRoot(TreeNode* aNode, int depth);
    /*protected*/ void fireTreeNodesChanged(QObject* source, QList<QObject*>* path,
                                            QList<int>* childIndices,
                                            QList<QObject*>* children);
    /*protected*/ void fireTreeNodesInserted(QObject* source, QList<QObject*>* path,
                                        QList<int>* childIndices,
                                        QList<QObject*>* children);
    /*protected*/ void fireTreeNodesRemoved(QObject* source, QList<QObject*>* path,
                                        QList<int>* childIndices,
                                        QList<QObject*>* children);
    /*protected*/ void fireTreeStructureChanged(QObject* source, QList<QObject*>* path,
                                        QList<int>* childIndices,
                                        QList<QObject*>* children);

};
//Q_DECLARE_METATYPE(QList<int>*)
//Q_DECLARE_METATYPE(QList<QObject*>*)
#endif // DEFAULTTREEMODEL_H
