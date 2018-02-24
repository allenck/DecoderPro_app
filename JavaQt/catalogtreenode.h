#ifndef CATALOGTREENODE_H
#define CATALOGTREENODE_H
#include "defaultmutabletreenode.h"
#include "logger.h"

class CatalogTreeLeaf;
class CatalogTreeNode : public DefaultMutableTreeNode
{
    Q_OBJECT
public:
    //explicit CatalogTreeNode(QObject *parent = 0);
    /*public*/ CatalogTreeNode(QString name, QObject *parent = 0);
    /*public*/ void addLeaf(CatalogTreeLeaf* leaf);
    /*public*/ void addLeaf(QString name, QString path) ;
    /*public*/ void deleteLeaves(QString name) ;
    /*public*/ void deleteLeaf(QString name, QString path);
    /*public*/ CatalogTreeLeaf* getLeaf(QString name, QString path);
    /*public*/ QVector <CatalogTreeLeaf*>* getLeaves(QString name);
    /*public*/ QVector <CatalogTreeLeaf*>* getLeaves();
    /*public*/ int getNumLeaves() ;
    /*public*/ void setLeaves(QVector <CatalogTreeLeaf*>* leaves);

signals:

public slots:
private:
 /*private*/ /*final*/ /*static*/ Logger* log;// = LoggerFactory.getLogger(CatalogTreeNode.class);
 // Sorted by height for ease of display in CatalogPanel
 /*private*/ QVector <CatalogTreeLeaf*>* _leafs;// = new QList<CatalogTreeLeaf*>();

};

#endif // CATALOGTREENODE_H
