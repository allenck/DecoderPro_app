#include "portal.h"
#include "opath.h"
#include "oblock.h"
#include "warrant.h"
#include "signalhead.h"
#include "signalmast.h"
#include "abstractsignalhead.h"
#include "abstractsignalmast.h"
#include "instancemanager.h"
#include "defaultsignalmastmanager.h"
#include "abstractsignalheadmanager.h"
#include "signalspeedmap.h"
#include "warranttableaction.h"

//Portal::Portal(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * An Portal is a boundary between two Blocks.
 *
 * <P>
 * A Portal has Lists of the OPaths that connect through it.
 *
 * @author	Pete Cressman  Copyright (C) 2009
 */
// /*public*/ class Portal  {

/*public*/ Portal::Portal(QString sysName, QString userName, QObject *parent) : AbstractNamedBean(sysName, userName, parent)
{
  _fromPaths = new QList <OPath*>();
  _toPaths = new QList <OPath*>();
  log = new Logger("Portal");
 _fromBlock = NULL;
 _toBlock = NULL;
 _fromSignal = NULL;
 _toSignal = NULL;
 _fromSignalDelay = 0;
 _toSignalDelay = 0;
 _toSignalOffset = 0;
 _fromSignalOffset = 0;
}

/**
* Determine which list the Path belongs to and add it to the list
* @return false if Path does not have a matching block for this Portal
*/
/*public*/ bool Portal::addPath(OPath* path)
{
 Block* block = path->getBlock();
 if (block==NULL)
 {
  log->error("Path \""+path->getName()+"\" has no block.");
  return false;
 }
 //if (log->isDebugEnabled()) log->debug("addPath: "+toString());
 if (this!=(path->getFromPortal()) &&
         this!=(path->getToPortal()) )
 {
  return false;
 }
 if (_fromBlock != NULL && _fromBlock==(block))
 {
  if (!_fromPaths->contains(path))
  {
   return addPath(_fromPaths, path);
  }
 }
 else if (_toBlock != NULL && _toBlock==(block))
 {
  if (!_toPaths->contains(path))
  {
   return addPath(_toPaths, path);
  }
 }
 // portal is incomplete or path block not in this portal
 return false;
}

/**
*  Utility for both path lists
*/
/*private*/ bool Portal::addPath(QList <OPath*>* list, OPath* path)
{
 if (list->contains(path))
 {
  return true;    //OK already there
 }
 QString pName = path->getName();
 for (int i = 0; i < list->size(); i++)
 {
  OPath* p = list->at(i);
  if (pName==(p->getName()))
  {
   log->error("Path \"" + path->getName()
           + "\" is duplicate name for another path in Portal \"" + getUserName() + "\".");
   return false;
  }
  if (p->equals(path))
  {
   log->warn("Path \""+path->getName()+"\" is duplicate of path \""+p->getName()+ " in Portal \""+getUserName()+"\".");
   return false;
  }
 }
 list->append(path);
 return true;
}

/*public*/ void Portal::removePath(OPath* path) {
    Block* block = path->getBlock();
    if (block==NULL) {
        log->error("Path \""+path->getName()+"\" has no block.");
        return;
    }
    //if (log->isDebugEnabled()) log->debug("removePath: "+toString());
    if (this!=(path->getFromPortal()) &&
            this!=(path->getToPortal()) ){
        return;
    }
    if (_fromBlock != NULL && _fromBlock==(block)) {
        _fromPaths->removeOne(path);
    } else if (_toBlock != NULL && _toBlock==(block)) {
        _toPaths->removeOne(path);
    }
}

/**
* Check for duplicate name in either block
* @return return error message, return NULL if name change is OK
*/
/*public*/ QString Portal::setName(QString newName)
{
 if (newName == NULL || newName.length()==0) { return NULL; }
 QString oldName = getUserName();
 if (oldName==(newName)) {
  return "";
 }

 QString msg = checkName(newName, _fromBlock);
 if (msg == NULL) {
     msg = checkName(newName, _toBlock);
 }
 if (msg == NULL)
 {
  setUserName(newName);
  WarrantTableAction::portalNameChange(oldName, newName);
 } else {
     msg = tr("Another portal in OBlock \"%1\" is named \"%2\".").arg( msg).arg( newName);
 }
 return msg;
}
/*private*/ QString Portal::checkName(QString name, OBlock* block) {
    QList<Portal*> list = block->getPortals();
    for (int i=0; i<list.size(); i++) {
        if (name==(list.at(i)->getName())) {
            return list.at(i)->getName();
        }
    }
    return NULL;
}

/*public*/ QString Portal::getName() { return getUserName(); }

/**
* Set block name. Verify that all toPaths are contained in the block.
* @return false if paths are not in the block
*/
/*public*/ bool Portal::setToBlock(OBlock* block, bool changePaths) {
    if ((block!=NULL && block==(_toBlock)) || (block==NULL && _toBlock==NULL)) {
        return true;
    }
    if (changePaths) {
        //Switch paths to new block.  User will need to verify connections
        for (int i=0; i<_toPaths->size(); i++) {
                _toPaths->at(i)->setBlock(block);
        }
    } else if (!verify(_toPaths, block)) {
        return false;
    }
    if (log->isDebugEnabled()) log->debug("setToBlock: oldBlock= \""+getToBlockName()
              +"\" newBlock \""+(block!=NULL ? block->getDisplayName() : NULL)+"\".");
    if (_toBlock!=NULL) { _toBlock->removePortal(this); }
    _toBlock = block;
    if (_toBlock!=NULL) { _toBlock->addPortal(this); }
    return true;
}
/*public*/ OBlock* Portal::getToBlock() { return _toBlock;  }
/*public*/ QString Portal::getToBlockName() { return (_toBlock!=NULL ? _toBlock->getDisplayName() : NULL); }
/*public*/ QList <OPath*>* Portal::getToPaths() { return _toPaths; }

/**
* Set block name. Verify that all fromPaths are contained in the block.
* @return false if paths are not in the block
*/
/*public*/ bool Portal::setFromBlock(OBlock* block, bool changePaths) {
    if ((block!=NULL && block==(_fromBlock)) || (block==NULL && _fromBlock==NULL)) {
        return true;
    }
    if (changePaths) {
        //Switch paths to new block.  User will need to verify connections
        for (int i=0; i<_fromPaths->size(); i++) {
                _fromPaths->at(i)->setBlock(block);
        }
    } else if (!verify(_fromPaths, block)) {
        return false;
    }
    if (log->isDebugEnabled()) log->debug("setFromBlock: oldBlock= \""+getFromBlockName()+
              "\" newBlock \""+(block!=NULL ? block->getDisplayName() : NULL)+"\".");
    if (_fromBlock!=NULL) { _fromBlock->removePortal(this); }
    _fromBlock = block;
    if (_fromBlock!=NULL) { _fromBlock->addPortal(this); }
    return true;
}
/*public*/ OBlock* Portal::getFromBlock() { return _fromBlock;  }
/*public*/ QString Portal::getFromBlockName() { return (_fromBlock!=NULL ? _fromBlock->getDisplayName() : NULL);  }
/*public*/ QList <OPath*>* Portal::getFromPaths() { return _fromPaths;  }

/*public*/ bool Portal::setProtectSignal(NamedBean* signal, long time, OBlock* protectedBlock) {
    if (protectedBlock==NULL) return false;
    if (_fromBlock==(protectedBlock)) {
        _toSignal = signal;
        _toSignalDelay = time;
        return true;
        //log->debug("setSignal: _toSignal= \""+name+", protectedBlock= "+protectedBlock);
    }
    if (_toBlock==(protectedBlock)) {
        _fromSignal = signal;
        _fromSignalDelay = time;
        return true;
        //log->debug("setSignal: _fromSignal= \""+name+", protectedBlock= "+protectedBlock);
    }
    return false;
}

/*public*/ NamedBean* Portal::getFromSignal() {
    return _fromSignal;
}
/*public*/ QString Portal::getFromSignalName() {
    return (_fromSignal!=NULL ? _fromSignal->getDisplayName() : NULL);
}

/*public*/ float Portal::getFromSignalOffset()
{
 return _fromSignalOffset;
}

/*public*/ NamedBean* Portal::getToSignal() {
    return _toSignal;
}
/*public*/ QString Portal::getToSignalName() {
    return (_toSignal!=NULL ? _toSignal->getDisplayName() : NULL);
}

/*public*/ float Portal::getToSignalOffset()
{
 return _toSignalOffset;
}

/*public*/ void Portal::deleteSignal(NamedBean* signal) {
    if (signal==(_toSignal)) {
        _toSignal = NULL;
    } else if (signal==(_fromSignal)) {
        _fromSignal = NULL;
    }
}

/*static*/ /*public*/ NamedBean* Portal::getSignal(QString name) {
    NamedBean* signal = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
    if (signal==NULL) {
        signal = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
    }
    return signal;
}

/**
* Get the paths to the portal within the connected Block
* i.e. the paths in this (the param) block through the Portal
* @param block
* @return NULL if portal does not connect to block
*/
/*public*/ QList <OPath*>* Portal::getPathsWithinBlock(OBlock* block) {
    if (block == NULL) { return NULL; }
    if (block==(_fromBlock)) {
        return _fromPaths;
    } else if (block==(_toBlock)) {
        return _toPaths;
    }
    return NULL;
}

/**
* Return the block on the other side of the portal
* from this (the param) block
*/
/*public*/ OBlock* Portal::getOpposingBlock(OBlock* block) {
    if (block==(_fromBlock)) {
        return _toBlock;
    } else if (block==(_toBlock)) {
        return _fromBlock;
    }
    return NULL;
}

/**
* Get the paths from the portal in the next connected Block
* i.e. paths in the block on the other side of the portal
* from this (the param) block
* @param block
* @return NULL if portal does not connect to block
*/
/*public*/ QList <OPath*>* Portal::getPathsFromOpposingBlock(OBlock* block) {
    if (block==(_fromBlock)) {
        return _toPaths;
    } else if (block==(_toBlock)) {
        return _fromPaths;
    }
    return NULL;
}

/**
* @param block is the direction of entry
* @return signal protecting block
*/
/*public*/ NamedBean* Portal::getSignalProtectingBlock(OBlock* block) {
    if (block==(_toBlock)) {
        return _fromSignal;
    } else if (block==(_fromBlock)) {
        return _toSignal;
    }
    return NULL;
}

/**
* Check signals, if any, for speed into the block. The signal that protects the
* "to" block is the signal facing the "from" Block, i.e. the "from" signal.
* (and vice-versa)
* @param block is the direction of entry, "from" block
* @return permissible speed, NULL if no signal
*/
/*public*/ QString Portal::getPermissibleEntranceSpeed(OBlock* block)
{
 QString speed = NULL;
 QString blockName = block->getDisplayName();
 if (block==(_toBlock))
 {
  if (_fromSignal!=NULL)
  {
   //if (_fromSignal instanceof SignalHead)
   if(qobject_cast<SignalHead*>(_fromSignal)!=NULL)
   {
    speed = getPermissibleSignalEntranceSpeed((SignalHead*)_fromSignal);
   }
   else
   {
    speed = getPermissibleSignalEntranceSpeed((SignalMast*)_fromSignal);
   }
  }
 }
 else if (block==(_fromBlock))
 {
  if (_toSignal!=NULL)
  {
   //if (_toSignal instanceof SignalHead)
   if(qobject_cast<SignalHead*>(_toSignal)!=NULL)
   {
    speed = getPermissibleSignalEntranceSpeed((SignalHead*)_toSignal);
   }
   else
   {
    speed = getPermissibleSignalEntranceSpeed((SignalMast*)_toSignal);
   }
  }
 }
 else
 {
  log->error("Block \""+blockName+"\" is not in Portal \""+getUserName()+"\".");
 }
 if (log->isDebugEnabled() && speed != NULL)
 {
     log->debug("Portal \"" + getUserName() + "\","
             + " has ENTRANCE speed= " + speed + " into \"" + blockName + "\" from signal.");
 }
 // no signals, proceed at recorded speed
 return speed;
}

/*public*/ long Portal::getEntranceSpeedChangeWaitForBlock(OBlock* block) {
    if (block==(_toBlock)) {
        if (_fromSignal!=NULL) {
            return _fromSignalDelay;
        }
    } else if (block==(_fromBlock)) {
        if (_toSignal!=NULL) {
            return _toSignalDelay;
        }
    }
    return 0;
}
/*
 * +/- distance in millimeters for speed change point of signal
 */
/*public*/ float Portal::getEntranceSpaceForBlock(OBlock* block) {
    if (block==(_toBlock)) {
        if (_fromSignal != NULL) {
            return _fromSignalOffset;
        }
    } else if (block==(_fromBlock)) {
        if (_toSignal != NULL) {
            return _toSignalOffset;
        }
    }
    return 0;
}
/**
* Check signals, if any, for speed out of the block. The signal that protects the
* "to" block is the signal facing the "from" Block, i.e. the "from" signal.
* (and vice-versa)
* @param block is the direction of entry, "from" block
* @return permissible speed, NULL if no signal
*/
/*public*/ QString Portal::getPermissibleExitSpeed(OBlock* block)
{
 QString speed = NULL;
 if (block==(_toBlock))
 {
  if (_fromSignal!=NULL)
  {
   //if (_fromSignal instanceof SignalHead)
   if(qobject_cast<SignalHead*>(_fromSignal)!=NULL)
   {
    speed = getPermissibleSignalExitSpeed((SignalHead*)_fromSignal);
   }
   else
   {
    speed = getPermissibleSignalExitSpeed((SignalMast*)_fromSignal);
   }
  }
 }
 else if (block==(_fromBlock))
 {
  if (_toSignal!=NULL)
  {
   //if (_toSignal instanceof SignalHead)
   if(qobject_cast<SignalHead*>(_toSignal)!=NULL)
   {
    speed = getPermissibleSignalExitSpeed((SignalHead*)_toSignal);
   }
   else
   {
    speed = getPermissibleSignalExitSpeed((SignalMast*)_toSignal);
   }
  }
 }
 else
 {
  log->error("Block \""+block->getDisplayName()+"\" is not in Portal \""+getUserName()+"\".");
 }
 // no signals, proceed at recorded speed
 return speed;
}


/*private*/ QString Portal::getPermissibleSignalEntranceSpeed(SignalHead* signal) {
    int appearance = ((AbstractSignalHead*)signal)->getAppearance();
    QString speed = Warrant::getSpeedMap()->getAppearanceSpeed(((AbstractSignalHead*)signal)->getAppearanceName(appearance));
    if (speed==NULL) {
        log->error("SignalHead \""+ ((AbstractSignalHead*)signal)->getDisplayName()+"\" has no speed specified for appearance \""+
                        ((AbstractSignalHead*)signal)->getAppearanceName(appearance)+"\"! - Restricting Movement!");
        speed = "Restricted";
    }
    if (log->isDebugEnabled()) log->debug(((AbstractSignalHead*)signal)->getDisplayName()+" has speed notch= "+speed+" from appearance \""+
                                            ((AbstractSignalHead*)signal)->getAppearanceName(appearance)+"\"");
    return speed;
}

/*private*/ QString Portal::getPermissibleSignalEntranceSpeed(SignalMast* signal) {
    QString aspect = ((AbstractSignalMast*)signal)->getAspect();
    QString speed = Warrant::getSpeedMap()->getAspectSpeed(aspect, ((AbstractSignalMast*)signal)->getSignalSystem());
    if (speed==NULL) {
        log->error("SignalMast \""+ ((AbstractSignalMast*)signal)->getDisplayName()+"\" has no speed specified for aspect \""+
                                            aspect+"\"! - Restricting Movement!");
        speed = "Restricted";
    }
    if (log->isDebugEnabled()) log->debug(((AbstractSignalMast*)signal)->getDisplayName()+" has speed notch= "+speed+
                " from aspect \""+aspect+"\"");
    return speed;
}

/*private*/ QString Portal::getPermissibleSignalExitSpeed(SignalHead* signal) {
    int appearance = ((AbstractSignalHead*)signal)->getAppearance();
    QString speed = Warrant::getSpeedMap()->getAppearanceSpeed(((AbstractSignalHead*)signal)->getAppearanceName(appearance));
    if (speed=="") {
        log->error("SignalHead \""+ ((AbstractSignalHead*)signal)->getDisplayName()+"\" has no (exit) speed specified for appearance \""+
                        ((AbstractSignalHead*)signal)->getAppearanceName(appearance)+"\"! - Restricting Movement!");
        speed = "Restricted";
    }
    if (log->isDebugEnabled()) log->debug(((AbstractSignalHead*)signal)->getDisplayName()+" has exit speed notch= "+speed+
            " from appearance \""+((AbstractSignalHead*)signal)->getAppearanceName(appearance)+"\"");
    return speed;
}

/*private*/ QString Portal::getPermissibleSignalExitSpeed(SignalMast* signal) {
    QString aspect = ((AbstractSignalMast*)signal)->getAspect();
    QString speed = Warrant::getSpeedMap()->getAspectExitSpeed(aspect, ((AbstractSignalMast*)signal)->getSignalSystem());
    if (speed==NULL) {
        log->error("SignalMast \""+ ((AbstractSignalMast*)signal)->getDisplayName()+"\" has no exit speed specified for aspect \""+
                                            aspect+"\"! - Restricting Movement!");
        speed = "Restricted";
    }
    if (log->isDebugEnabled()) log->debug(((AbstractSignalMast*)signal)->getDisplayName()+" has exit speed notch= "+
                    speed+" from aspect \""+aspect+"\"");
    return speed;
}

/*private*/ bool Portal::verify(QList <OPath*>* paths, OBlock* block) {
    if (block==NULL) {
        if (paths->size()==0) {
            return true;
        } else {
            return false;
        }
    }
    QString name = block->getSystemName();
    for (int i=0; i<paths->size(); i++) {
        QString pathName = paths->at(i)->getBlock()->getSystemName();
        if (pathName!=(name)) {
            return false;
        }
    }
    return true;
}

/**
 * Check if path connects to Portal
 *
 * @param path
 */
/*public*/ bool Portal::isValidPath(OPath* path)
{
 QString name = path->getName();
 for (int i = 0; i < _toPaths->size(); i++)
 {
  if (_toPaths->at(i)->getName()==(name))
  {
      return true;
  }
 }
 for (int i = 0; i < _fromPaths->size(); i++)
 {
  if (_fromPaths->at(i)->getName()==(name))
  {
      return true;
  }
 }
 return false;
}

/*public*/ bool Portal::isValid() {
    return (_fromBlock!=NULL && _toBlock!=NULL);
}

/*public*/ void Portal::dispose() {
    if (_fromBlock!=NULL) _fromBlock->removePortal(this);
    if (_toBlock!=NULL) _toBlock->removePortal(this);
}

/*public*/QString Portal::getDescription() {
//    return java.text.MessageFormat.format(WarrantTableAction.rb.getString("PortalDescription"),
//                    _portalName, getFromBlockName(), getToBlockName());
    return tr("\"%1\" between OBlocks \"%2\" and \"%3\"").arg(getUserName()).arg(getFromBlockName()).arg(getToBlockName());
}

/*public*/ QString Portal::toString() {
    return ("Portal \""+getUserName()+"\" from block \""+getFromBlockName()+"\" to block \""+getToBlockName()+"\"");
}
