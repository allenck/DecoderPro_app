#include "catalogtreenode.h"
#include "../LayoutEditor/namedicon.h"
#include "catalogtreeleaf.h"
#include "loggerfactory.h"

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
 log = new Logger("CatalogTreeNode");
 _leafs = new QVector<CatalogTreeLeaf*>();
}

/**
*  Append leaf to the end of the leaves list
*/
/*public*/ void CatalogTreeNode::addLeaf(CatalogTreeLeaf* leaf) {
 _leafs->append(leaf);
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
   for (int i=0; i<_leafs->size(); i++) {
       CatalogTreeLeaf* leaf = _leafs->at(i);
       if (h < leaf->getSize()) {
           _leafs->insert(i+1, new CatalogTreeLeaf(name, path, h));
           return;
       }
   }
   _leafs->append(new CatalogTreeLeaf(name, path, h));
}
/** Leaves can be used for many-to-many relations
*/
/*public*/ void CatalogTreeNode::deleteLeaves(QString name) {
   for (int i=0; i<_leafs->size(); i++) {
       CatalogTreeLeaf* leaf = _leafs->at(i);
       if (name==(leaf->getName())) {
           _leafs->remove(i);
       }
   }
}
/*public*/ void CatalogTreeNode::deleteLeaf(QString name, QString path) {
   for (int i=0; i<_leafs->size(); i++) {
       CatalogTreeLeaf* leaf = _leafs->at(i);
       if (name==(leaf->getName()) && path==(leaf->getPath())) {
           _leafs->remove(i);
           return;
       }
   }
}
/*public*/ CatalogTreeLeaf* CatalogTreeNode::getLeaf(QString name, QString path) {
   for (int i=0; i<_leafs->size(); i++) {
       CatalogTreeLeaf* leaf = _leafs->at(i);
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
   for (int i=0; i<_leafs->size(); i++) {
       CatalogTreeLeaf* leaf = _leafs->at(i);
       if (name==(leaf->getName())) {
           leaves->append(leaf);
       }
   }
   return leaves;
}
/*public*/ QVector <CatalogTreeLeaf*>* CatalogTreeNode::getLeaves() {
   return _leafs;
}
/*public*/ int CatalogTreeNode::getNumLeaves() {
   return _leafs->size();
}
/*public*/ void CatalogTreeNode::setLeaves(QVector <CatalogTreeLeaf*>* leaves) {
   _leafs = leaves;
}

// /*private*/ /*final*/ /*static*/ Logger* CatalogTreeNode::log = LoggerFactory::getLogger("CatalogTreeNode");
//}
