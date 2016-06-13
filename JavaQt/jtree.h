#ifndef JTREE_H
#define JTREE_H

#include <QTreeView>
#include "javaqt_global.h"

class DefaultTreeModel;
class JAVAQTSHARED_EXPORT JTree : public QTreeView
{
 Q_OBJECT
public:
 explicit JTree(QWidget *parent = 0);
 JTree(DefaultTreeModel* tree,QWidget *parent = 0);
 void setShowsRootHandles(bool b);
 void setScrollsOnExpand(bool b);
 void setExpandsSelectedPaths(bool );


signals:

public slots:
private:
 DefaultTreeModel* tree;
};

#endif // JTREE_H
