#include "jtree.h"

JTree::JTree(QWidget *parent) :
  QTreeView(parent)
{
 tree = NULL;
}

JTree::JTree(DefaultTreeModel* tree,QWidget *parent) :
  QTreeView(parent)
{
 this->tree = tree;
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
