#ifndef TREEACTION_H
#define TREEACTION_H
#include "jmrijframeaction.h"

class TreeAction : public JmriJFrameAction
{
 Q_OBJECT
public:
 TreeAction(QObject* parent);
 /*public*/ TreeAction(QString s, QObject* parent);
 /*public*/ QString getName();

};

#endif // TREEACTION_H
