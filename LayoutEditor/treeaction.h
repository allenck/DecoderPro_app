#ifndef TREEACTION_H
#define TREEACTION_H
#include "jmrijframeaction.h"

class TreeAction : public JmriJFrameAction
{
 Q_OBJECT
public:
 TreeAction(QObject* parent = 0);
 /*public*/ TreeAction(QString s, QObject* parent);
 ~TreeAction() {}
 TreeAction(const TreeAction&) : JmriJFrameAction() {}
 /*public*/ QString getName();

};
Q_DECLARE_METATYPE(TreeAction)
#endif // TREEACTION_H
