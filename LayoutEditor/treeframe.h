#ifndef TREEFRAME_H
#define TREEFRAME_H
#include "jmrijframe.h"

class TreeFrame : public JmriJFrame
{
 Q_OBJECT
public:
 TreeFrame(QWidget* parent = 0);
 ~TreeFrame() {}
 TreeFrame(const TreeFrame&): JmriJFrame() {}
 /*public*/ void initComponents(); //throws Exception
 /*public*/ QString getClassName();

};
Q_DECLARE_METATYPE(TreeFrame)
#endif // TREEFRAME_H
