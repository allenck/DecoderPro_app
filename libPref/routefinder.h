#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H

#include <QObject>
#include <QList>
#include "defaultmutabletreenode.h"
#include "libpref_global.h"

class Logger;
class RouteNode;
class DefaultTreeModel;
class DefaultMutableTreeNode;
class WarrantRoute;
class BlockOrder;
class OBlock;
class LIBPREFSHARED_EXPORT RouteFinder : public QObject
{
 Q_OBJECT
public:
 //explicit RouteFinder(QObject *parent = 0);

signals:
 void finished();
public slots:
 void process();

private:
 WarrantRoute* _caller;
 BlockOrder* _originBlockOrder;
 BlockOrder* _destBlockOrder;
 BlockOrder* _viaBlockOrder;
 BlockOrder* _avoidBlockOrder;
 QList<DefaultMutableTreeNode*>* _destNodes;
 DefaultTreeModel* _tree;

 OBlock* _destBlock;
 QString _dPathName;
 QString _dEntryName;
 OBlock* _viaBlock;
 QString _vPathName;
 OBlock* _avoidBlock;
 QString _aPathName;

 int _maxBlocks;
 bool _quit;// = false;
 QList<RouteNode*> makeLevel(QList<RouteNode*> nodes, int level);
 Logger* log;
protected:
 /*protected*/ RouteFinder(WarrantRoute* f, BlockOrder* origin, BlockOrder* dest,
         BlockOrder* via, BlockOrder* avoid, int maxB, QObject *parent = 0);
 /*protected*/ void quit();
friend class WarrantRoute;
};

class RouteNode : public DefaultMutableTreeNode
{
 Q_OBJECT

    /**
     *
     */
    //private static final long serialVersionUID = -5651237533899902323L;
    bool _needsViaAncestor;// = false;
public:
    RouteNode(QObject* userObject);
    RouteNode(QObject* userObject, bool needsViaAncestor) ;
    void hasViaAncestor(bool hasViaAncestor) ;
    bool needsViaAncestor() ;

};
#endif // ROUTEFINDER_H
