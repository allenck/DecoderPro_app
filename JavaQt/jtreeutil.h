#ifndef JTREEUTIL_H
#define JTREEUTIL_H

#include "qframe.h"
#include "guiutilbase.h"

class DefaultMutableTreeNode;
class JTreeUtil : public GuiUtilBase
{
    Q_OBJECT
public:
    explicit JTreeUtil(QObject *parent = nullptr);
    static /*public*/ DefaultMutableTreeNode *loadTree(QString name, WindowInterface* wi, QObject* context);
    static DefaultMutableTreeNode* treeFromElement(QDomElement main, WindowInterface* wi, QObject* context) ;

signals:

};

#endif // JTREEUTIL_H
