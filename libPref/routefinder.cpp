#include "routefinder.h"
#include "blockorder.h"
#include "warrantroute.h"
#include "portal.h"
#include "oblock.h"
#include "opath.h"
#include "logger.h"
#include "defaulttreemodel.h"
#include "rosterentry.h"

//RouteFinder::RouteFinder(QObject *parent) :
//  QObject(parent)
//{
//}
///*public*/ class RouteFinder implements Runnable {

//    java.beans.SwingPropertyChangeSupport _pcs = new java.beans.SwingPropertyChangeSupport(this,this);

/*protected*/ RouteFinder::RouteFinder(WarrantRoute* f, BlockOrder* origin, BlockOrder* dest,
        BlockOrder* via, BlockOrder* avoid, int maxB, QObject *parent) :
QObject(parent)
{
_quit = false;
    _caller = f;
//        _pcs.addPropertyChangeListener(_caller);
 _originBlockOrder = origin;
 _destBlockOrder = dest;
 _viaBlockOrder = via;
 _avoidBlockOrder = avoid;
 _maxBlocks = maxB;
 log = new Logger("RouteFinder");
}

/*protected*/ void RouteFinder::quit() {
    _quit = true;
}

//static class RouteNode extends DefaultMutableTreeNode {

//    /**
//     *
//     */
//    private static final long serialVersionUID = -5651237533899902323L;
//    bool _needsViaAncestor = false;

RouteNode:: RouteNode(QObject* userObject) : DefaultMutableTreeNode(userObject) {
        //super(userObject);
 _needsViaAncestor = false;
    }

RouteNode::RouteNode(QObject* userObject, bool needsViaAncestor) : DefaultMutableTreeNode(userObject){
        //super(userObject);
        _needsViaAncestor = needsViaAncestor;
    }

    void  RouteNode::hasViaAncestor(bool hasViaAncestor) {
        _needsViaAncestor = !hasViaAncestor;
    }

    bool  RouteNode::needsViaAncestor() {
        return _needsViaAncestor;
    }

//}

/*public*/ void RouteFinder::process() {
    _destBlock = _destBlockOrder->getBlock();
    _dPathName = _destBlockOrder->getPathName();
    _dEntryName = _destBlockOrder->getEntryName();
    _viaBlock = NULL;
    _vPathName = "";
    if (_viaBlockOrder != NULL) {
        _vPathName = _viaBlockOrder->getPathName();
        _viaBlock = _viaBlockOrder->getBlock();
    }
    _avoidBlock = NULL;
    _aPathName = "NULL";
    if (_avoidBlockOrder != NULL) {
        _aPathName = _avoidBlockOrder->getPathName();
        _avoidBlock = _avoidBlockOrder->getBlock();
    }

    _destNodes = new QList<DefaultMutableTreeNode*>();
    _quit = false;
    int level = 0;
    RouteNode* root = new RouteNode(_originBlockOrder, (_viaBlockOrder != NULL));
    _tree = new DefaultTreeModel(root);
    QList<RouteNode*> nodes =  QList<RouteNode*>();
    nodes.append(root);
    while (level < _maxBlocks && !_quit) {
        nodes = makeLevel(nodes, level);
        level++;
//            _pcs.firePropertyChange("RouteSearch", Integer.valueOf(level), Integer.valueOf(_destNodes.size()));
    }
    if (_destNodes->size() == 0) {
        _caller->debugRoute(_tree, _originBlockOrder, _destBlockOrder);
    } else {
        _caller->pickRoute(_destNodes, _tree);
    }
//        _pcs.removePropertyChangeListener(_caller);
}

/**
 * Examines list of nodes at a given level for the destination node and
 * makes a list of nodes of the next level.
 */
QList<RouteNode*> RouteFinder::makeLevel(QList<RouteNode*> nodes, int level) {

    QList<RouteNode*> children = QList<RouteNode*>();
    for (int i = 0; i < nodes.size(); i++) {
        RouteNode* node = nodes.at(i);
        BlockOrder* pOrder = VPtr<BlockOrder>::asPtr(node->getUserObject());
        OBlock* pBlock = pOrder->getBlock();
        QString pName = pOrder->getExitName();    // is entryName of next block
        Portal* exitPortal = pBlock->getPortalByName(pName);
        if (exitPortal != NULL) {
            OBlock* nextBlock = exitPortal->getOpposingBlock(pBlock);
            QList<OPath*>* paths = exitPortal->getPathsFromOpposingBlock(pBlock);
            if (log->isDebugEnabled()) {
                log->debug("makeLevel " + QString::number(level) + " block= " + pBlock->getDisplayName()
                        + ", path= " + pOrder->getPathName() + " meets " + QString::number(paths->size()) + " portal paths");
            }
            if (paths->size() == 0) {
                log->error("Portal \"" + pName + "\" " + (exitPortal->getOpposingBlock(pBlock) == NULL
                        ? "is malformed! Only one block!" : "does not have any paths into the next block!"));
            }
            // walk all paths
            for (int k = 0; k < paths->size(); k++) {
                OPath* path = paths->at(k);
                if (_avoidBlock != NULL && _avoidBlock==(nextBlock)) {
                    if (_aPathName==(path->getName())) {
                        continue;
                    }
                }
                QString exitName = path->getOppositePortalName(pName);
                BlockOrder* nOrder = new BlockOrder((OBlock*) path->getBlock(), path->getName(), pName, exitName);
                RouteNode* child = new RouteNode(nOrder, node->needsViaAncestor());
                _tree->insertNodeInto(child, node, node->getChildCount());
                if (_viaBlock != NULL && _viaBlock==(nextBlock)) {
                    if (_vPathName==(path->getName())) {
                        child->hasViaAncestor(true);
                    }
                }
                if (!node->needsViaAncestor()) {
                    if (_destBlock == nOrder->getBlock() && _dPathName==(path->getName())
                            && _dEntryName==(pName)) {
                        _destNodes->append(child);
                    } else {
                        children.append(child);
                    }
                } else {
                    children.append(child);
                }
            }
//                _pcs.firePropertyChange("RouteSearch", Integer.valueOf(level), Integer.valueOf(_destNodes.size()));
        } else {
            if (log->isDebugEnabled()) {
                log->debug("Dead branch: block= " + pBlock->getDisplayName()
                        + " has no exit portal");
            }
        }
        if (_quit) {
            break;
        }
    }
    return children;
}
