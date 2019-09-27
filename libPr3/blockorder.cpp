#include "blockorder.h"
#include "oblock.h"
#include "portal.h"
#include "opath.h"

//BlockOrder::BlockOrder(QObject *parent) :
//    QObject(parent)
//{
//}
///*public*/ class BlockOrder  {


/*public*/ BlockOrder::BlockOrder(OBlock* block, QObject *parent) : QObject(parent)
{
 _block = block;
}

/**
 * Create BlockOrder.
 *@param block
 *@param path MUST be a path in the blocK
 *@param entry MUST be a name of a Portal to the path
 *@param exit MUST be a name of a Portal to the path
 */
/*public*/ BlockOrder::BlockOrder(OBlock* block, QString path, QString entry, QString exit, QObject *parent) : QObject(parent){
   // this(block);
    _block = block;
    _pathName = path;
    _entryName = entry;
    _exitName = exit;
    //if (log.isDebugEnabled()) log.debug("ctor1: "+this.toString());
}

// for use by WarrantTableFrame
/*protected*/ BlockOrder::BlockOrder(BlockOrder* bo, QObject *parent) : QObject(parent){
    _block = bo->_block;      // shallow copy OK. WarrantTableFrame doesn't write to block
    _pathName = bo->_pathName;
    _entryName = bo->_entryName;
    _exitName = bo->_exitName;
    //if (log.isDebugEnabled()) log.debug("ctor2: "+this.toString());
}

/*protected*/ void BlockOrder::setEntryName(QString name) { _entryName = name; }
/*public*/ QString BlockOrder::getEntryName() { return _entryName; }


/*protected*/ void BlockOrder::setExitName(QString name) { _exitName = name; }
/*public*/ QString BlockOrder::getExitName() { return _exitName; }

/*protected*/ bool BlockOrder::validateOrder() {
    return true;
}

/**
* Set Path. Note that the Path's 'fromPortal' and 'toPortal' have no bearing on
* the BlockOrder's entryPortal and exitPortal.
*/
/*protected*/ void BlockOrder::setPathName(QString path) {
    _pathName = path;
}
/*public*/ QString BlockOrder::getPathName() { return _pathName; }

/*protected*/ OPath* BlockOrder::getPath() { return _block->getPathByName(_pathName); }

/*protected*/ QString BlockOrder::setPath(Warrant* warrant) {
    return _block->setPath(getPathName(), warrant);
}

/*protected*/ void BlockOrder::setBlock(OBlock* block) { _block = block; }

/*public*/ OBlock* BlockOrder::getBlock() { return _block; }

/*protected*/ Portal* BlockOrder::getEntryPortal() {
    if (_entryName==NULL) { return NULL; }
    return _block->getPortalByName(_entryName);
}

/*protected*/ Portal* BlockOrder::getExitPortal() {
    if (_exitName==NULL) { return NULL; }
    return _block->getPortalByName(_exitName);
}

/**
*  Check signals for entrance into next block.
* @return speed
*/
/*protected*/ QString BlockOrder::getPermissibleEntranceSpeed() {
    Portal* portal = _block->getPortalByName(getEntryName());
    if (portal!=NULL) {
        return portal->getPermissibleEntranceSpeed(_block);
    }
    // OK if this is first block
    //log.warn("getPermissibleEntranceSpeed, no entry portal! "+this.toString());
    return NULL;
}
/*protected*/ float BlockOrder::getEntranceSpace()
{
 Portal* portal = _block->getPortalByName(getEntryName());
 if (portal != NULL) {
     return portal->getEntranceSpaceForBlock(_block);
 }
 return 0;
}
/*protected*/ long BlockOrder::getEntranceSpeedChangeWait() {
    Portal* portal = _block->getPortalByName(getEntryName());
    if (portal!=NULL) {
        return portal->getEntranceSpeedChangeWaitForBlock(_block);
    }
    return 0;
}

/*protected*/ QString BlockOrder::getPermissibleExitSpeed() {
    Portal* portal = _block->getPortalByName(getEntryName());
    if (portal!=NULL) {
        return portal->getPermissibleExitSpeed(_block);
    }
    // OK if this is first block
//        log.warn("getPermissibleExitSpeed, no entry portal! "+this.toString());
    return NULL;
}


/*protected*/ NamedBean* BlockOrder::getSignal() {
    return _block->getPortalByName(getEntryName())->getSignalProtectingBlock(_block);
}

/*protected*/ QString BlockOrder::hash() {
    return _block->getDisplayName()+_pathName+_entryName+_exitName;
}

/*public*/ QString BlockOrder::toString() {
    return ("BlockOrder: Block \""+_block->getDisplayName()+"\" has Path \""+_pathName+
            "\" with Portals \""+_entryName+"\" and \""+_exitName+"\"");
}
