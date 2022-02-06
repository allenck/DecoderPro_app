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
#include "warrantmanager.h"
#include "portalmanager.h"
#include "loggerfactory.h"

//Portal::Portal(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A Portal is a boundary between two Blocks.
 *
 * <P>
 * A Portal has Lists of the OPaths that connect through it. The direction of
 * trains passing through the portal is managed from the BlockOrders of the
 * Warrant the train is running under. The Portal fires a PropertyChangeEvent
 * that a PortIcon can listen for to set direction arrows for a given route.
 *
 * The Portal also supplies speed information from any signals set at its
 * location that the Warrant passes on the Engineer.
 *
 * @author  Pete Cressman Copyright (C) 2009
 */
// /*public*/ class Portal  {
/*private*/ /*static*/ /*final*/ QString Portal::NAME_CHANGE = "NameChange";
/*private*/ /*static*/ /*final*/ QString Portal::SIGNAL_CHANGE = "signalChange";
/*private*/ /*static*/ /*final*/ QString Portal::ENTRANCE = "entrance";


/*public*/ Portal::Portal( QString uName, QObject *parent) : QObject(parent)
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

 _name = uName;
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
 QString pName = path->getName();
 for (OPath* p : *list)
 {
  if (p->equals(path)) {
      if (pName == (p->getName())) {
          return true;    // OK, everything equal
      } else {
          log->warn(tr("Path \"%1\" is duplicate of path \"%2\" in Portal \"%3\" from block %4.").arg(path->getName()).arg(p->getName()).arg(_name).arg(path->getBlock()->getDisplayName()));
          return false;
      }
  } else if (pName == (p->getName())) {
      log->warn(tr("Path \"%1\" is duplicate name for another path in Portal \"%2\" from block %3.").arg(path->getName()).arg(_name).arg(path->getBlock()->getDisplayName()));
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
 if (newName == "" || newName.length() == 0) {
     return "";
 }
 QString oldName = _name;
 if (newName == (oldName)) {
     return "";
 }
 Portal* p = ((PortalManager*)InstanceManager::getDefault("PortalManager"))->getPortal(newName);
 if (p != nullptr) {
     return tr("Cannot change name \"%1\" to %2.").arg(oldName).arg(p->getDescription());
 }
 _name = newName;
 ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->portalNameChange(oldName, newName);

 // for some unknown reason, PortalManager firePropertyChange is not read by PortalTableModel
 // so let OBlock do it
 if (_toBlock != nullptr) {
     _toBlock->pseudoPropertyChange(NAME_CHANGE, oldName, _name);
 } else if (_fromBlock != nullptr) {
     _fromBlock->pseudoPropertyChange(NAME_CHANGE, oldName, _name);
 }
 // CircuitBuilder PortalList needs this property change
 pcs->firePropertyChange(NAME_CHANGE, oldName, newName);
 return "";
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

/*public*/ QString Portal::getName() { return _name; }

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

/**
 * Get the block protected by a signal.
 *
 * @param signal is the signal, either a SignalMast or a SignalHead
 * @return Protected OBlock, if it is protected, otherwise null.
 */
/*public*/ OBlock* Portal::getProtectedBlock(NamedBean* signal) {
    if (signal == nullptr) {
        return nullptr;
    }
    if (signal->equals(_fromSignal->self())) {
        return _toBlock;
    } else if (signal->equals(_toSignal->self())) {
        return _fromBlock;
    }
    return nullptr;
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
        signal = qobject_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
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
 * Call is from BlockOrder when setting the path.
 *
 * @param block OBlock
 */
/*protected*/ void Portal::setEntryState(OBlock* block) {
    if (block == nullptr) {
        _state = UNKNOWN;
    } else if (block->equals(_fromBlock)) {
        setState(ENTER_FROM_BLOCK);
    } else if (block->equals(_toBlock)) {
        setState(ENTER_TO_BLOCK);
    }
}

/*public*/ void Portal::setState(int s) {
    int old = _state;
    _state = s;
    pcs->firePropertyChange("Direction", old, _state);
}

/*public*/ int Portal::getState() {
    return _state;
}

//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void Portal::addPropertyChangeListener(PropertyChangeListener* listener) {
    pcs->SwingPropertyChangeSupport::addPropertyChangeListener(listener);
}

//@OverridingMethodsMustInvokeSuper
/*public*/ /*synchronized*/ void Portal::removePropertyChangeListener(PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(listener);
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
 return getPermissibleSpeed(block, true);

}

/**
 * Set the distance (plus or minus) in millimeters from the portal gap
 * where the speed change indicated by the signal should be completed.
 *
 * @param block a protected OBlock
 * @param distance length in millimeters
 */
/*public*/ void Portal::setEntranceSpaceForBlock(/*@Nonnull*/ OBlock* block, float distance) {
    if (block->equals(_toBlock)) {
        if (_fromSignal != nullptr) {
            _fromSignalOffset = distance;
        }
    } else if (block->equals(_fromBlock)) {
        if (_toSignal != nullptr) {
            _toSignalOffset = distance;
        }
    }
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
 return getPermissibleSpeed(block, false);
}

/**
 * Check signals, if any, for speed into/out of a given block. The signal that protects
 * the "to" block is the signal facing the "from" Block, i.e. the "from"
 * signal. (and vice-versa)
 *
 * @param block is the direction of entry, "from" block
 * @param entrance true for EntranceSpeed, false for ExitSpeed
 * @return permissible speed, null if no signal
 */
/*public*/ QString Portal::getPermissibleSpeed(/*@Nonnull*/ OBlock* block, bool entrance) {
    QString speed = "";
    QString blockName = block->getDisplayName();
    if (block->equals(_toBlock)) {
        if (_fromSignal != nullptr) {
            if (static_cast<SignalHead*>(_fromSignal)) {
                speed = getPermissibleSignalSpeed((SignalHead*) _fromSignal, entrance);
            } else {
                speed = getPermissibleSignalSpeed((SignalMast*) _fromSignal, entrance);
            }
        }
    } else if (block->equals(_fromBlock)) {
        if (_toSignal != nullptr) {
            if (static_cast<SignalHead*>(_toSignal)) {
                speed = getPermissibleSignalSpeed((SignalHead*) _toSignal, entrance);
            } else {
                speed = getPermissibleSignalSpeed((SignalMast*) _toSignal, entrance);
            }
        }
    } else {
        log->error(tr("Block \"%1\" is not in Portal \"%2\".").arg(blockName).arg(_name));
    }
    if (log->isDebugEnabled()) {
        if (speed != nullptr) {
            log->debug(tr("Portal \"%1\" has %2 speed= %3 into \"%4\" from signal.").arg(
                    _name).arg((entrance ? "ENTRANCE" : "EXIT")).arg(speed).arg(blockName));
        }
    }
    // no signals, proceed at recorded speed
    return speed;
}

/**
 * Get entrance or exit speed set on signal head.
 *
 * @param signal signal head to query
 * @param entrance true for EntranceSpeed, false for ExitSpeed
 * @return permissible speed, Restricted if no speed set on signal
 */
/*private*/ /*static*/ /*@Nonnull*/ QString Portal::getPermissibleSignalSpeed(/*@Nonnull */SignalHead* signal, bool entrance) {
 int appearance = signal->getAppearance();
 QString speed = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getAppearanceSpeed(signal->getAppearanceName(appearance));
 // on head, speed is the same for entry and exit
 if (speed == "") {
     log->error(tr("SignalHead \"%1\" has no %2 speed specified for appearance \"%3\"! - Restricting Movement!").arg(
             signal->getDisplayName()).arg((entrance ? ENTRANCE : "exit")).arg(signal->getAppearanceName(appearance)));
     speed = "Restricted";
 } log->debug(tr("SignalMast \"%1\" has %2 speed notch= %3 from aspect \"%4\"").arg(
       signal->getDisplayName()).arg((entrance ? ENTRANCE : "exit")).arg(speed).arg(signal->getAppearanceName(appearance)));
    return speed;
}

/**
 * Get entrance or exit speed set on signal mast.
 *
 * @param signal signal mast to query
 * @param entrance true for EntranceSpeed, false for ExitSpeed
 * @return permissible speed, Restricted if no speed set on signal
 */
/*private*/ /*static*/ /*@Nonnull*/ QString Portal::getPermissibleSignalSpeed(/*@Nonnull*/ SignalMast* signal, bool entrance) {
    QString aspect = signal->getAspect();
    QString speed;
    if (entrance) {
        speed = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getAspectSpeed(aspect, signal->getSignalSystem());
    } else {
        speed = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getAspectExitSpeed(aspect, signal->getSignalSystem());
    }
    if (speed == nullptr) {
        log->error(tr("SignalMast \"%1\" has no %2 speed specified for aspect \"%3\"! - Restricting Movement!").arg(
                signal->getDisplayName()).arg((entrance ? ENTRANCE : "exit")).arg(aspect));
        speed = "Restricted";
    }
    log->debug(tr("SignalMast \"%1\" has %2 speed notch= %3 from aspect \"%4\"").arg(
            signal->getDisplayName()).arg((entrance ? ENTRANCE : "exit")).arg(speed).arg(aspect));
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

//@OverridingMethodsMustInvokeSuper
/*public*/ bool Portal::dispose() {
 if (!((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->okToRemovePortal(this)) {
     return false;
 }
 if (_toBlock != nullptr) {
     _toBlock->removePortal(this);
 } else if (_fromBlock != nullptr) {
     _fromBlock->removePortal(this);
 }
 pcs->firePropertyChange("portalDelete", true, false);
 QVector<PropertyChangeListener*> listeners = pcs->getPropertyChangeListeners();
 for (PropertyChangeListener* l : listeners) {
     pcs->removePropertyChangeListener(l);
 }
 return true;
}

/*public*/QString Portal::getDescription() {
//    return java.text.MessageFormat.format(WarrantTableAction.rb.getString("PortalDescription"),
//                    _portalName, getFromBlockName(), getToBlockName());
    return tr("\"%1\" between OBlocks \"%2\" and \"%3\"").arg(_name).arg(getFromBlockName()).arg(getToBlockName());
}

/*public*/ QString Portal::toString() {
    return ("Portal \""+_name+"\" from block \""+getFromBlockName()+"\" to block \""+getToBlockName()+"\"");
}

/*private*/ /*static*/ /*final*/ Logger* Portal::log = LoggerFactory::getLogger("Portal");


