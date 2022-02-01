#ifndef TREECELLRENDERER_H
#define TREECELLRENDERER_H
#include <QtCore>

class JTree;
/*public*/ /*interface*/ class TreeCellRenderer {

/*public*/ virtual QWidget* getTreeCellRendererComponent(JTree* jtree, QVariant o, bool bln, bool bln1, bool bln2, int i, bool bln3)=0;
};
Q_DECLARE_INTERFACE(TreeCellRenderer, "TreeCellRenderer")
#endif // TREECELLRENDERER_H
