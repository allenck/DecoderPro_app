#ifndef LAYOUTBLOCKROUTETABLEACTION_H
#define LAYOUTBLOCKROUTETABLEACTION_H

#include "abstractaction.h"

class LayoutBlock;
class LayoutBlockRouteTable;
class JmriJFrame;
class LayoutBlockRouteTableAction : public AbstractAction
{
    Q_OBJECT
public:
    //explicit LayoutBlockRouteTableAction(QObject *parent = 0);
    /*public*/ LayoutBlockRouteTableAction(QString s, LayoutBlock* lBlock,QObject *parent = 0);
    void createModel();

signals:

public slots:
    /*public*/ void actionPerformed(JActionEvent* = 0) override;

private:
    LayoutBlock* lBlock;

     LayoutBlockRouteTable* m;
     //LayoutBlockNeighbourTable mn;
     JmriJFrame* f;
    QString s;
    void setTitle();
    QString helpTarget();

};

#endif // LAYOUTBLOCKROUTETABLEACTION_H
