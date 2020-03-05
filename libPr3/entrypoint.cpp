#include "entrypoint.h"
#include "instancemanager.h"

/**
 * Represent an EntryPoint to a Section of track.
 * Specifies a Block within the Section, and a Path of that Block.
 * <P>
 * An EntryPoint can be "forward" or "reverse" type, depending on if
 *  a train entering the Section at this entry point will be travelling
 *  in the forward direction or the reverse direction.
 * <P>
 * An EntryPoint is referenced via lists in its parent Section, and is
 *	stored on disk when its parent section is stored.
 * <P>
 * This module delays initialization of Blocks until first reference after
 *  an Entry Point is loaded from a configuration file.
 *
 * @author	Dave Duchamp  Copyright (C) 2008
 * @version	$Revision: 17977 $
 */
///*public*/ class EntryPoint {

/*public*/ EntryPoint::EntryPoint(Block* b, Block* pb, QString fbDir, QObject *parent) : QObject(parent){
    common();
    mBlock = b;
    mFromBlock = pb;
    mFromBlockDirection = fbDir;    // direction from Path that triggered entry point
}

// special constructor for delayed initialization
/*public*/ EntryPoint::EntryPoint(QString bName, QString fbName, QString fbDir, QObject *parent) : QObject(parent){
    common();
    needsInitialize = true;
    blockName = bName;
    fromBlockName = fbName;
    mFromBlockDirection = fbDir;    // direction from Path that triggered entry point

}
void EntryPoint::common()
{
    // instance variables
    mBlock = NULL;
    mFromBlock = NULL;
    mDirection = UNKNOWN;
     mFixed = false;
    mFromBlockDirection = "";

    // temporary instance variables
    needsInitialize = false;
    blockName = "";
    fromBlockName = "";

}

/*private*/ void EntryPoint::initialize() {
    mBlock =(Block*) ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(blockName);
    if (mBlock==NULL)
        log.error("Missing block - "+blockName+" - when initializing entry point");
    mFromBlock = (Block*)((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBySystemName(fromBlockName);
    if (mFromBlock==NULL)
        log.error("Missing block - "+fromBlockName+" - when initializing entry point");
    needsInitialize = false;
}

/**
 * Access methods
 */
/*public*/ Block* EntryPoint::getBlock() {
    if (needsInitialize) initialize();
    return mBlock;
}
/*public*/ QString EntryPoint::getFromBlockName() {
    if (needsInitialize) initialize();
    QString s = mFromBlock->getSystemName();
    QString u = mFromBlock->getUserName();
    if ( (u!=NULL) && (u!=("")) ) {
        s = s+"( "+u+" )";
    }
    if ( (mFromBlockDirection!=NULL) && (mFromBlockDirection!=("")) ) {
        s = s+"( "+mFromBlockDirection+" )";
    }
    return s;
}
/*public*/ Block* EntryPoint::getFromBlock() {
    if (needsInitialize) initialize();
    return mFromBlock;
}
/*public*/ void EntryPoint::setTypeForward() { mDirection = FORWARD; }
/*public*/ void EntryPoint::setTypeReverse() { mDirection = REVERSE; }
/*public*/ void EntryPoint::setTypeUnknown() { mDirection = UNKNOWN; }
/*public*/ bool EntryPoint::isForwardType() {
    if (mDirection == FORWARD) return true;
    return false;
}
/*public*/ bool EntryPoint::isReverseType() {
    if (mDirection == REVERSE) return true;
    return false;
}
/*public*/ bool EntryPoint::isUnknownType() {
    if (mDirection == UNKNOWN) return true;
    return false;
}
/*public*/ int EntryPoint::getDirection() { return mDirection; }
/*public*/ void EntryPoint::setDirection(int dir) { mDirection = dir; }

/*public*/ void EntryPoint::setFixed( bool f ) { mFixed = f; }
/*public*/ bool EntryPoint::isFixed() { return mFixed; }

/*public*/ QString EntryPoint::getFromBlockDirection() { return mFromBlockDirection; }


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(EntryPoint.class.getName());
