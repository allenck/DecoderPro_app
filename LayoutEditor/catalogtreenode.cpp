#include "catalogtreenode.h"
#include "namedicon.h"
#include "catalogtreeleaf.h"

//CatalogTreeNode::CatalogTreeNode(QObject *parent) :
//    DefaultMutableTreeNode(parent)
//{
//}
/**
 * Node of a CatalogTree.
 * <P>
 * Name for the node
 * Path is info needed for leaves.
 *
 * @author			Pete Cressman  Copyright 2009
 *
 */
///*public*/ class CatalogTreeNode extends DefaultMutableTreeNode {


/*public*/ CatalogTreeNode::CatalogTreeNode(QString name, QObject *parent) : DefaultMutableTreeNode(name, parent)
{
 //super(name);
 _leaves = new QVector<CatalogTreeLeaf*>();
}

/**
*  Append leaf to the end of the leaves list
*/
/*public*/ void CatalogTreeNode::addLeaf(CatalogTreeLeaf* leaf) {
    _leaves->append(leaf);
}

/**
* Insert leaf according to height.
*/
/*public*/ void CatalogTreeNode::addLeaf(QString name, QString path) {
   // check path
   NamedIcon* icon = NamedIcon::getIconByName(path);
   if (icon == NULL){
       log->warn("path \""+path+"\" is not a NamedIcon.");
       return;
   }
   int h = icon->getIconHeight();
   for (int i=0; i<_leaves->size(); i++) {
       CatalogTreeLeaf* leaf = _leaves->at(i);
       if (h < leaf->getSize()) {
           _leaves->replace(i+1, new CatalogTreeLeaf(name, path, h));
           return;
       }
   }
   _leaves->append(new CatalogTreeLeaf(name, path, h));
}
/** Leaves can be used for many-to-many relations
*/
/*public*/ void CatalogTreeNode::deleteLeaves(QString name) {
   for (int i=0; i<_leaves->size(); i++) {
       CatalogTreeLeaf* leaf = _leaves->at(i);
       if (name==(leaf->getName())) {
           _leaves->remove(i);
       }
   }
}
/*public*/ void CatalogTreeNode::deleteLeaf(QString name, QString path) {
   for (int i=0; i<_leaves->size(); i++) {
       CatalogTreeLeaf* leaf = _leaves->at(i);
       if (name==(leaf->getName()) && path==(leaf->getPath())) {
           _leaves->remove(i);
           return;
       }
   }
}
/*public*/ CatalogTreeLeaf* CatalogTreeNode::getLeaf(QString name, QString path) {
   for (int i=0; i<_leaves->size(); i++) {
       CatalogTreeLeaf* leaf = _leaves->at(i);
       if (name==(leaf->getName()) && path==(leaf->getPath())) {
           return leaf;
       }
   }
   return NULL;
}
/** Leaves can be used for many-to-many relations
*/
/*public*/ QVector <CatalogTreeLeaf*>* CatalogTreeNode::getLeaves(QString name) {
   QVector <CatalogTreeLeaf*>* leaves = new QVector <CatalogTreeLeaf*>();
   for (int i=0; i<_leaves->size(); i++) {
       CatalogTreeLeaf* leaf = _leaves->at(i);
       if (name==(leaf->getName())) {
           leaves->append(leaf);
       }
   }
   return leaves;
}
/*public*/ QVector <CatalogTreeLeaf*>* CatalogTreeNode::getLeaves() {
   return _leaves;
}
/*public*/ int CatalogTreeNode::getNumLeaves() {
   return _leaves->size();
}
/*public*/ void CatalogTreeNode::setLeaves(QVector <CatalogTreeLeaf*>* leaves) {
   _leaves = leaves;
}

//   static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(CatalogTreeNode.class.getName());
//}
