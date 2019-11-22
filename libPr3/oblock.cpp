#include "oblock.h"
#include <QString>
#include "instancemanager.h"
#include "opath.h"
#include "abstractsensor.h"
#include "warrant.h"
#include "portal.h"
#include <QColor>
#include "sensor.h"

//OBlock::OBlock(QObject *parent) :
//    Block(parent)
//{
//}
/**
 * OBlock extends jmri.Block to be used in Logix Conditionals and Warrants. It is the smallest
 * piece of track that can have occupancy detection.  A better name would be Detection Circuit.
 * However, an OBlock can be defined without an occupancy sensor and used to calculate routes.
 *
 * Additional states are defined to indicate status of the track and trains to control panels.
 * A jmri.Block has a PropertyChangeListener on the occupancy sensor and the OBlock will pass
 * state changes of the sensor on to its warrant.
 *
 *<P>
 * Entrances (exits when train moves in opposite direction) to OBlocks have Portals. A
 * Portal object is a pair of OBlocks.  Each OBlock has a list of its Portals.
 *
 *<P>
 * When an OBlock (Detection Circuit) has a Portal whose entrance to the OBlock has a signal,
 * then the OBlock and its chains of adjacent OBlocks up to the next OBlock having an entrance
 * Portal with a signal, can be considered a "Block" in the sense of a prototypical railroad.
 * Preferrably all entrances to the "Block" should have entrance Portals with a signal.
 *
 *
 *<P>
 * A Portal has a list of paths (OPath objects) for each OBlock it separates.  The paths are
 * determined by the turnout settings of the turnouts contained in the block.
 * Paths are contained within the Block boundaries. Names of OPath objects only need be unique
 * within an OBlock.
 *
 *<P>
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 *
 * @version $Revision: 21339 $
 * @author	Pete Cressman (C) 2009
 */
// /*public*/ class OBlock extends jmri.Block implements java.beans.PropertyChangeListener {

//	static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logix.WarrantBundle");

QHash<QString, int> OBlock::initOldStatusMap()
{
 QHash<QString, int> hash;

 hash.insert(tr("unoccupied"), (OBlock::UNOCCUPIED));
 hash.insert(tr("occupied"), (OBlock::OCCUPIED));
 hash.insert(tr("allocated"), (OBlock::ALLOCATED));
 hash.insert(tr("running"), (OBlock::RUNNING));
 hash.insert(tr("outOfService"), (OBlock::OUT_OF_SERVICE));
 hash.insert(tr("dark"), (OBlock::DARK));
 hash.insert(tr("powerError"), (OBlock::TRACK_ERROR));
 return hash;
}

QHash<QString, int> OBlock::initStatusMap()
{
 QHash<QString, int> hash;
 hash.insert("unoccupied", (OBlock::UNOCCUPIED));
 hash.insert("occupied", (OBlock::OCCUPIED));
 hash.insert("allocated", (OBlock::ALLOCATED));
 hash.insert("running", (OBlock::RUNNING));
 hash.insert("outOfService", (OBlock::OUT_OF_SERVICE));
 hash.insert("dark", (OBlock::DARK));
 hash.insert("powerError", (OBlock::TRACK_ERROR));
 return hash;
}
QHash<QString, QString> OBlock::initStatusNameMap()
{
 QHash<QString, QString> hash;
 hash.insert(tr("unoccupied"), "unoccupied");
 hash.insert(tr("occupied"), "occupied");
 hash.insert(tr("allocated"), "allocated");
 hash.insert(tr("running"), "running");
 hash.insert(tr("outOfService"), "outOfService");
 hash.insert(tr("dark"), "dark");
 hash.insert(tr("powerError"), "powerError");
 return hash;
}

/*static*/ /*final*/ QHash<QString, int> OBlock::_oldstatusMap =  initOldStatusMap();
/*static*/ /*final*/ QHash<QString, int> OBlock::_statusMap =  initStatusMap();
/*static*/ /*final*/ QHash<QString, QString> OBlock::_statusNameMap = initStatusNameMap();


/*static*/ void OBlock::loadStatusMap()
{
 _statusMap.insert("unoccupied", (UNOCCUPIED));
 _statusMap.insert("occupied", (OCCUPIED));
 _statusMap.insert("allocated", (ALLOCATED));
 _statusMap.insert("running", (RUNNING));
 _statusMap.insert("outOfService", (OUT_OF_SERVICE));
 _statusMap.insert("dark", (DARK));
 _statusMap.insert("powerError", (TRACK_ERROR));
 _oldstatusMap.insert(tr("Unoccupied"), (UNOCCUPIED));
 _oldstatusMap.insert(tr("Occupied"), (OCCUPIED));
 _oldstatusMap.insert(tr("Allocated"), (ALLOCATED));
 _oldstatusMap.insert(tr("Path Occupied"), (RUNNING));
 _oldstatusMap.insert(tr("Out Of Service"), (OUT_OF_SERVICE));
 _oldstatusMap.insert(tr("Dark"), (DARK));
 _oldstatusMap.insert(tr("Power Error"), (TRACK_ERROR));
}

/*static*/ void OBlock::loadStatusNameMap()
{
 _statusNameMap.insert(tr("Unoccupied"), "unoccupied");
 _statusNameMap.insert(tr("Occupied"), "occupied");
 _statusNameMap.insert(tr("Allocated"), "allocated");
 _statusNameMap.insert(tr("Path Occupied"), "running");
 _statusNameMap.insert(tr("Out Of Service"), "outOfService");
 _statusNameMap.insert(tr("Dark"), "dark");
 _statusNameMap.insert(tr("Power Error"), "powerError");
}
/*public*/ /*static*/ QStringList OBlock::getLocalStatusNames()
{
 if (_statusNameMap.size() == 0)
 {
  loadStatusNameMap();
 }

 QStringList keys = _statusNameMap.keys();
 return keys;
}

/*public*/ /*static*/ QString OBlock::getLocalStatusName(QString str) {
//        try {
//            return tr(str);
//        } catch (java.util.MissingResourceException mre) {
//            return str;
//        }
return str;
}

/*public*/ /*static*/ QString OBlock::getSystemStatusName(QString str)
{
 if (_statusNameMap.size() == 0)
 {
  loadStatusNameMap();
 }
return _statusNameMap.value(str);
}
//    /*public*/ OBlock(String systemName) {
//        super(systemName);
//        setState(DARK);
//    }
/*static*/ /*final*/ QColor OBlock::DEFAULT_FILL_COLOR =  QColor(200, 0, 200);

/*public*/ OBlock::OBlock(QString systemName, QString userName, QObject *parent) : Block(systemName, userName, parent)
{
 //super(systemName, userName);
 _portals =  QList <Portal*>();     // portals to this block
 _scaleRatio   = 87.1;
 _metric     = false; // desired display mode
 log = new Logger("OBlock");
 log->setDebugEnabled(true);
 _errNamedSensor = NULL;
 _sharedTO =  QMap<QString, QList<QMap<OBlock*, QList<OPath*> > > >();
 _ownsTOs = false;
 _markerForeground = QColor(Qt::white);
 _markerBackground = DEFAULT_FILL_COLOR;
 _portals = QList<Portal*>();
 _warrant = NULL;

 setState(UNDETECTED);
}

/**
 * {@inheritDoc}
 * <p>
 * Override to only set an existing sensor and to amend state with not
 * UNDETECTED return true if an existing Sensor is set or sensor is to be
 * removed from block.
 */
//@Override
/*public*/ bool OBlock::setSensor(QString pName)
{
 bool ret = false;
 QString oldName = "";
 Sensor* sensor = getSensor();
 if (sensor != NULL)
 {
  oldName = sensor->getDisplayName();
 }
 // save the non-sensor states
 int saveState = getState() & ~(UNKNOWN | OCCUPIED | UNOCCUPIED | INCONSISTENT | UNDETECTED);
 if (pName == "" || pName.trimmed().length() == 0)
 {
  setNamedSensor(NULL);
  ret = true;
 }
 else
 {
  sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(pName);
  if (sensor == NULL)
  {
   sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getBySystemName(pName);
  }
  if (sensor == NULL)
  {
   if (log->isDebugEnabled()) {
       log->debug("no sensor named \"" + pName + "\" exists.");
   }
   ret = false;
  }
  else
  {
   setNamedSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
   ret = true;
  }
 }
 setState(getState() | saveState);

 firePropertyChange("OccupancySensorChange", oldName, pName);
 return ret;
}

// override to determine if not DARK
/*public*/ void OBlock::setNamedSensor(NamedBeanHandle<Sensor*>* namedSensor)
{
 Block::setNamedSensor(namedSensor);
 if(namedSensor!=NULL)
 {
  setState(getSensor()->getState() & ~UNDETECTED);
 }
}

/*public*/ bool OBlock::setErrorSensor(QString pName)
{
 if (getErrorSensor() != NULL)
 {
  getErrorSensor()->removePropertyChangeListener((PropertyChangeListener*)this);
 }
 if (pName == "" || pName.trimmed().length() == 0)
 {
  setState(getState() & ~TRACK_ERROR);
  _errNamedSensor = NULL;
  return true;
 }
 Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getByUserName(pName);
 if (sensor == NULL)
 {
  sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getBySystemName(pName);
 }
 if (sensor == NULL)
 {
  setState(getState() & ~TRACK_ERROR);
  if (log->isDebugEnabled()) {
   log->debug(tr("no sensor named \"%1\" exists.").arg(pName));
  }
 }

 sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(pName);
 if (sensor != NULL)
 {
  _errNamedSensor = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor);
  getErrorSensor()->addPropertyChangeListener((PropertyChangeListener*)this, _errNamedSensor->getName(), "OBlock Error Sensor " + getDisplayName());
  if (sensor->getState() == Sensor::ACTIVE) {
      setState(getState() | TRACK_ERROR);
  } else {
      setState(getState() & ~TRACK_ERROR);
  }
  return true;
 }
 return false;
}

/*public*/ Sensor* OBlock::getErrorSensor()
{
 if (_errNamedSensor==NULL)
 {
  return NULL;
 }
 return _errNamedSensor->getBean();
}

/*public*/ NamedBeanHandle<Sensor*>* OBlock::getNamedErrorSensor() {
    return _errNamedSensor;
}

/*public*/ void OBlock::propertyChange(PropertyChangeEvent* evt)
{
 if (log->isDebugEnabled())
  log->debug("property change: " + getDisplayName() + " property " + evt->getPropertyName() + " is now "
                + evt->getNewValue().toString()+" from "+evt->getSource()->metaObject()->className());
 if ((getErrorSensor()!=NULL) && (evt->getSource()==(getErrorSensor())))
 {
  if (evt->getPropertyName()==("KnownState"))
  {
   int errState = (evt->getNewValue()).toInt();
   int oldState = getState();
   if (errState==Sensor::ACTIVE)
   {
    setState(oldState | TRACK_ERROR);
   }
   else
   {
    setState(oldState & ~TRACK_ERROR);
   }
   firePropertyChange("path", QVariant(oldState), QVariant(getState()));
  }
 }
}

/**
 * This block shares a turnout (e.g. a crossover) with another block.
 * Typically one JMRI turnout driving two switches where each switch is in a
 * different block.
 *
 * @param key   a path in this block
 * @param block another block
 * @param path  a path in that block sharing a turnout with key
 */
/*public*/ bool OBlock::addSharedTurnout(OPath* key, OBlock* block, OPath* path)
{
 if (log->isDebugEnabled())
 {
  log->debug("Path " + key->getName() + " in block \"" + getDisplayName()
            + "\" has turnouts shared with path " + path->getName() + " in block " + block->getDisplayName());
 }
 QList<QMap<OBlock*, QList<OPath*> > > blockList = _sharedTO.value(key->getName());
 if (!blockList.isEmpty())
 {
  QListIterator<QMap<OBlock*, QList<OPath*> > > iter( blockList/*.iterator()*/);
  while (iter.hasNext())
  {
   QMap<OBlock*, QList<OPath*> > map = iter.next();
   QMapIterator<OBlock*, QList<OPath*> >  it( map/*.iterator()*/);
   while (it.hasNext())
   {
    QList<OPath*>  entry = it.next().value();
    OBlock* b = it.next().key();
    if (b==(block))
    {
     QList<OPath*> pathList = entry;
     if (pathList.contains(path))
     {
      return false;
     }
     else
     {
      pathList.append(path);
      return true;
     }
    }
    else
    {
     QList<OPath*> pathList =  QList<OPath*>();
     pathList.append(path);
     map.insert(block, pathList);
     return true;
    }
   }
  }
  QMap<OBlock*, QList<OPath*> > map =  QMap<OBlock*, QList<OPath*> >();
  QList<OPath*> pathList = QList<OPath*>();
  pathList.append(path);
  map.insert(block, pathList);
  blockList.append(map);
  return true;
 }
 else
 {
  QList<OPath*> pathList = QList<OPath*>();
  pathList.append(path);
  QMap<OBlock*, QList<OPath*> > map =  QMap<OBlock*, QList<OPath*> >();
  map.insert(block, pathList);
  blockList =  QList<QMap<OBlock*, QList<OPath*> > >();
  blockList.append(map);
  _sharedTO.insert(key->getName(), blockList);
  return true;
 }
}

/**
 * Called from setPath. looking for other warrants that may have allocated
 * blocks that share TO's with this block.
 *
 * @return
 */
/*private*/ QString OBlock::checkSharedTO()
{
 QList<QMap<OBlock*, QList<OPath*> > > blockList = _sharedTO.value(_pathName);
 if (!blockList.isEmpty())
 {
  QListIterator<QMap<OBlock*, QList<OPath*> > > iter(blockList/*.iterator()*/);
  if (log->isDebugEnabled())
  {
   log->debug("Path " + _pathName + " in block \"" + getDisplayName()
              + "\" has turnouts thrown from " + blockList.size() + " other blocks");
  }
  while (iter.hasNext())
  {
   QMap<OBlock*, QList<OPath*> > map = iter.next();
   QMapIterator<OBlock*, QList<OPath*> >  it( map/*.iterator()*/);
   while (it.hasNext())
   {
    QList<OPath*> entry = it.next().value();
    OBlock* block = it.next().key();
    QListIterator<OPath*> i(entry/*.iterator()*/);
    while (i.hasNext())
    {
     OPath* path = i.next();
     if (log->isDebugEnabled()) {
         log->debug("Path " + _pathName + " in block \"" + getDisplayName()
                 + "\" has turnouts shared with path " + path->getName() + " in block " + block->getDisplayName());
     }
     // call sharing block to check for conflict
     QString name = block->isPathSet(path->getName());
     if (name != "")
     {
      _warrant->setShareTOBlock(block);
      return tr("Path \"%1\" of block \"%2\" in warrant \"%3\" must wait until path \"%4\" of block \"%5\" in warrant \"%6\" clears.").arg(_pathName).arg(getDisplayName().arg(
              _warrant->getDisplayName()).arg(path->getName()).arg(
              block->getDisplayName()).arg(name));
     }
     else
     {
      _ownsTOs = true;
     }
    }
   }
  }
 }
 return NULL;
}

/*protected*/ bool OBlock::ownsTOs() {
    return _ownsTOs;
}
/**
 * Another block sharing a turnout with this block queries whether turnout
 * is in use.
 *
 * @param path that uses a common shared turnout
 * @return If warrant exists and path==pathname, return warrant display
 *         name, else null.
 */
/*protected*/ QString OBlock::isPathSet(QString path)
{
 QString msg = "";
 if (_warrant != NULL)
 {
  if (path==(_pathName))
  {
   msg = _warrant->getDisplayName();
  }
 }
 if (log->isDebugEnabled())
 {
  log->debug("Path \"" + path + "\" set in block \"" + getDisplayName()
             + "\"= " + (msg != "") + ". _pathName= " + _pathName);
 }
 return msg;
}

/*protected*/ Warrant* OBlock::getWarrant() { return _warrant; }

/*public*/ bool OBlock::isAllocatedTo(Warrant* warrant) {
    if (warrant == nullptr) {
        return false;
    }
    return warrant->equals(_warrant);
}

/*public*/ QString OBlock::getAllocatedPathName() { return _pathName; }

/*public*/ float OBlock::getLengthScaleFeet() {
    return getLengthIn()/12*_scaleRatio;
}
/*public*/ float OBlock::getLengthMeters() {
    return getLengthMm()/1000*_scaleRatio;
}

/*public*/ void OBlock::setMetricUnits(bool type) {
    _metric = type;
}
/*public*/ bool OBlock::isMetric() {
    return _metric;
}

/*public*/ void OBlock::setMarkerForeground(QColor c) {
    _markerForeground = c;
}

/*public*/ QColor OBlock::getMarkerForeground() {
    return _markerForeground;
}

/*public*/ void OBlock::setMarkerBackground(QColor c) {
    _markerBackground = c;
}

/*public*/ QColor OBlock::getMarkerBackground() {
    return _markerBackground;
}

/*public*/ void OBlock::setMarkerFont(QFont f) {
    _markerFont = f;
}

/*public*/ QFont OBlock::getMarkerFont() {
    return _markerFont;
}
/**
 * override
 *
 */
//@Override
/*public*/ void OBlock::setValue(QVariant o)
{
 Block::setValue(o);
 if (o == QVariant())
 {
  _markerForeground = QColor(Qt::white);
  _markerBackground = DEFAULT_FILL_COLOR;
  _markerFont = QFont();
 }
}

/*public*/ void OBlock::setScaleRatio(float sr) {
    _scaleRatio = sr;
}
/*public*/ float OBlock::getScaleRatio() {
    return _scaleRatio;
}

/*
*  From the universal name for block status, check if it is the current status
*/
/*public*/ bool OBlock::statusIs(QString statusName) {
    int i = _statusMap.value(statusName);
    if (i==0) {
        i = _oldstatusMap.value(statusName);
    }
    if (i!=0) {
        return ((getState() & i) != 0);
    }
    log->error("\""+statusName+
                "\" resource not found.  Please update Conditional State Variable testing OBlock \""
                +getDisplayName()+"\" status.");
    return false;
}

/**
*  Test that block is not occupied and and not allocated
*/
/*public*/ bool OBlock::isFree() {
    int state = getState();
    return ((state & ALLOCATED)==0 && (state & OCCUPIED)==0);
}

/**
* Allocate (reserves) the block for the Warrant that is the 'value' object
* Note the block may be OCCUPIED by a non-warranted train, but the allocation is permitted.
* @param warrant
* @return name of block if block is already allocated to another warrant
*/
/*protected*/ QString OBlock::allocate(Warrant* warrant) {
    if (log->isDebugEnabled()) log->debug("Allocate block \""+getDisplayName()+
                                "\" to warrant \""+warrant->getDisplayName()+"\"");
    if (warrant==NULL) {
        return "ERROR! allocate called with NULL warrant in block \""+getDisplayName()+"\"!";
    }
    if (_warrant!=NULL && warrant!=(_warrant)) {
        // allocated to another warrant
        //return java.text.MessageFormat.format(tr("AllocatedToWarrant"),
//                                              _warrant.getDisplayName(), getDisplayName());
        return tr("Warrant \"%1\" has reserved block \"%2\".").arg(_warrant->getDisplayName()).arg(getDisplayName());
    }
    int state = getState();
    if ((state & OUT_OF_SERVICE) !=0) {
//        return java.text.MessageFormat.format(tr("BlockOutOfService"),
//                                                getDisplayName());
        return tr("Block \"%1\" is Out Of Service and canot be allocated.").arg(getDisplayName());
    }
    QString path = warrant->getRoutePathInBlock(this);
    if (_pathName==NULL)
    {
     _pathName = path;
    }
    _warrant = warrant;
    // firePropertyChange signaled in super.setState()
    setState(getState() | ALLOCATED);
    return NULL;
}

/**
     * Note path name may be set if block is not allocated to a warrant. For use
     * by Circuitbuilder Only.
* @return error message
*/
/*public*/ QString OBlock::allocate(QString pathName) {
    if (log->isDebugEnabled()) log->debug("Allocate OBlock path \""+pathName+"\" in block \""
                                        +getSystemName()+"\", state= "+QString::number(getState()));
    if (pathName==NULL) {
        log->error("allocate called with NULL pathName in block \""+getDisplayName()+"\"!");
        return NULL;
    } else if (_warrant!=NULL) {
        // allocated to another warrant
//        return java.text.MessageFormat.format(tr("AllocatedToWarrant"),
//                                              _warrant.getDisplayName(), getDisplayName());
        return tr("Warrant \"%1\" has reserved block \"%2\".").arg(_warrant->getDisplayName()).arg(getDisplayName());
    }
    if (_pathName!=NULL && _pathName!=(pathName)) {
//        return java.text.MessageFormat.format(tr("AllocatedToPath"),
//                                      pathName, getDisplayName(), _pathName);
        return tr("Cannot allocate Path \"%1\" in block \"%2\". Block is allocated with path \"%3\"").arg(pathName).arg( getDisplayName()).arg(_pathName);
    }
    _pathName = pathName;
//        setState(getState() | ALLOCATED);  DO NOT ALLOCATE
    return NULL;
}

/*public*/ QString OBlock::getAllocatingWarrantName() {
    if (_warrant == nullptr) {
        return ("no warrant");
    } else {
        return _warrant->getDisplayName();
    }
}

/**
* Remove allocation state
* Remove listener regardless of ownership
*/
/*public*/ QString OBlock::deAllocate(Warrant* warrant) {
    if (log->isDebugEnabled()) log->debug("deAllocate block \""+getDisplayName()+
                    "\" from warrant \""+warrant->getDisplayName()+"\"");
    if (_warrant!=NULL) {
        if (_warrant!=(warrant)) {
            return "cannot deAllocate. warrant \""+_warrant->getDisplayName()+
                        "\" owns block \""+getDisplayName()+"\"!";
        }
        removePropertyChangeListener((PropertyChangeListener*)_warrant);
    }
    if (_pathName!=NULL) {
        OPath* path = getPathByName(_pathName);
        if (path!=NULL) {
            int lockState = Turnout::CABLOCKOUT & Turnout::PUSHBUTTONLOCKOUT;
            path->setTurnouts(0, false, lockState, false);
        }
    }
    _warrant = NULL;
    _pathName = "";
    setValue(QVariant());
    setState(getState() & ~(ALLOCATED | RUNNING));  // unset allocated and running bits
    return NULL;
}

/*public*/ void OBlock::setOutOfService(bool set) {
    if (set) {
        setState(getState() | OUT_OF_SERVICE);  // set OoS bit
    } else {
        setState(getState() & ~OUT_OF_SERVICE);  // unset OoS bit
    }
}

/*public*/ void OBlock::setError(bool set) {
    if (set) {
        setState(getState() | TRACK_ERROR);  // set err bit
    } else {
        setState(getState() & ~TRACK_ERROR);  // unset err bit
    }
}

/**
* Enforce unique portal names.  Portals are not managed beans and multiple
* configuration loads will create multiple Portal Objects that are "duplicates".
*/
/*public*/ void OBlock::addPortal(Portal* portal)
{
 QString name = getDisplayName();
 if (name!=(portal->getFromBlockName()) && name!=(portal->getToBlockName()))
 {
  log->warn(portal->toString()+" not in block "+getDisplayName());
  return;
 }
 QString pName = portal->getName();
 if (pName!=NULL)
 {  // pName may be NULL if called from Portal ctor
  for (int i=0; i<_portals.size(); i++)
  {
   if (pName==(_portals.at(i)->getName())) {
       return;
   }
  }
 }
 int oldSize = _portals.size();
 _portals.append(portal);
 if (log->isDebugEnabled()) log->debug("addPortal: portal= \""+portal->getName()+
                                     "\", to Block= \""+getDisplayName()+"\"." );
 firePropertyChange("portalCount", QVariant(oldSize), QVariant(_portals.size()));
}

/**
* Remove portal from block and stub all paths using this portal to
* be dead end spurs.
*/
/*public*/ void OBlock::removePortal(Portal* portal)
{
 int oldSize = _portals.size();
 int oldPathSize = getPaths()->size();
 if (portal != NULL)
 {
  //String name = portal.getName();
  QVectorIterator <Path*> iter(*getPaths());
  while (iter.hasNext())
  {
   OPath* path = (OPath*)iter.next();
   if (portal==(path->getFromPortal()))
   {
    path->setFromPortal(NULL);
    if (log->isDebugEnabled()) log->debug("removed Portal "+portal->getName()+" from Path "+
              path->getName()+" in block "+getSystemName());
   }
   if (portal==(path->getToPortal()))
   {
    path->setToPortal(NULL);
    if (log->isDebugEnabled()) log->debug("removed Portal "+portal->getName()+" from Path "+
              path->getName()+" in block "+getSystemName());
   }
   if (path->getFromPortal()==NULL && path->getToPortal()==NULL)
   {
    removePath(path);
    if (log->isDebugEnabled()) log->debug("removed Path "+
                              path->getName()+" in block "+getSystemName());
   }
  }
  //_portals.remove(portal);
  for (int i=0; i < _portals.size(); i++)
  {
   if (portal==(_portals.at(i)))
   {
    _portals.removeAt(i);
    log->debug("removed portal "+portal->getName()+" from block "+getSystemName());
    i--;
   }
  }
 }
 log->debug("removePortal: block "+getSystemName()+" portals decreased from "
           +QString::number(oldSize)+" to "+QString::number(_portals.size())+" - paths decreased from "+
           QString::number(oldPathSize)+" to "+QString::number(getPaths()->size()));
 firePropertyChange("portalCount", QVariant(oldSize), QVariant(_portals.size()));
}

/*public*/ Portal* OBlock::getPortalByName(QString name)
{
 //if (log->isDebugEnabled()) log->debug("getPortalByName: name= \""+name+"\"." );
 for (int i=0; i<_portals.size(); i++)
 {
  if (_portals.at(i)->getName()==(name))
  {
      return _portals.at(i);
  }
 }
 return NULL;
}

/*public*/ QList <Portal*> OBlock::getPortals() {
    return _portals;
}

/*public*/ OPath* OBlock::getPathByName(QString name)
{
 QVectorIterator <Path*> iter(*getPaths());
 while (iter.hasNext())
 {
  OPath* path = (OPath*)iter.next();
  if (path->getName()==(name))
  {
   return path;
  }
 }
 return NULL;
}

/**
 * Enforce unique path names within block, but allow a duplicate path to be
 * checked if it is also in one of the block's portals
 */
/*public*/ bool OBlock::addPath(OPath* path)
{
 QString pName = path->getName();
 if (log->isDebugEnabled()) log->debug("addPath \""+pName+"\" to OBlock "+getSystemName());

 QVector <Path*>* list = getPaths();
 for (int i=0; i<list->size(); i++)
 {
  if (((OPath*) list->at(i))->equals(path))
  {
   log->warn("Path \"" + pName + "\" duplicated in OBlock " + getSystemName());
   return false;
  }
  if (pName == (((OPath*)list->at(i))->getName()))
  {
   log->warn("Path named \"" + pName + "\" already exists in OBlock " + getSystemName());
   return false;
  }
 }
 path->setBlock(this);
 Portal* portal = path->getFromPortal();
 if (portal!=NULL)
 {
  if (!portal->addPath(path))
  {
   log->warn("Path \"" + pName + "\" rejected by portal  " + portal->getName());
   return false;
  }
 }
 portal = path->getToPortal();
 if (portal!=NULL)
 {
  if (!portal->addPath(path))
  {
   log->warn("Path \"" + pName + "\" rejected by portal  " + portal->getName());
   return false;
  }
 }
 int oldSize = list->size();
 Block::addPath(path);
 firePropertyChange("pathCount", QVariant(oldSize), QVariant(getPaths()->size()));
 return true;
}

/*public*/ void OBlock::removePath(Path* path)
{
 if (getSystemName()!=(path->getBlock()->getSystemName()))
 {
  return;
 }
//        if (log->isDebugEnabled()) log->debug("Path "+((OPath)path).getName()+" removed from "+getSystemName());
 path->clearSettings();
 int oldSize = getPaths()->size();
 Block::removePath(path);
 //if (path instanceof OPath)
 if(qobject_cast<OPath*>(path)!= NULL)
 {
     ((OPath*)path)->dispose();
 }
 firePropertyChange("pathCount", QVariant(oldSize), QVariant(getPaths()->size()));
}

/**
* Set Turnouts for the path
* Called by warrants to set turnouts for a train it is able to run.  The warrant parameter
* is verifies that the block is indeed allocated to the warrant,  If the block is unwarranted
* then the block is allocated to the calling warrant.  A logix conditional may also call this
* method with a NULL warrant parameter for manual logix control.  However, if the block is
* under a warrant the call will be rejected.
* @param pathName name of the path
* @param warrant warrant the block is allocated to
* @return error message if the call fails.  NULL if the call succeeds
*/
/*public*/ QString OBlock::setPath(QString pathName, Warrant* warrant) {
    if (log->isDebugEnabled()) log->debug("setPath: on OBlock \""+getSystemName()+" path to \""+
                                        pathName+"\" for warrant "+warrant->getDisplayName());
    QString msg = NULL;
    if (_warrant!=NULL && _warrant!=(warrant)) {
//        msg = java.text.MessageFormat.format(tr("AllocatedToWarrant"),
//                                              _warrant.getDisplayName(), getDisplayName());
        msg = tr("Warrant \"%1\" has reserved block \"%2\".").arg(_warrant->getDisplayName()).arg(getDisplayName());
        return msg;
    }
    pathName = pathName.trimmed();
    _warrant = warrant;
    OPath* path = getPathByName(pathName);
    if (path==NULL) {
       // msg = java.text.MessageFormat.format(tr("PathNotFound"), pathName, getDisplayName());
        msg = tr("Path \"%1\" not found in Block \"%2\".").arg(pathName).arg(getDisplayName());
    } else {
        if (_warrant!=NULL) {
            // Sanity check
            QString p = warrant->getRoutePathInBlock(this);
            if (pathName!=(p)) {
                log->error("path \""+pathName+"\" for block \""+getDisplayName()+
                        "\" does not agree with path \""+p+"\" in route of warrant \""+
                        warrant->getDisplayName()+"\".");
            }
        }
        _pathName = pathName;
        int lockState = Turnout::CABLOCKOUT & Turnout::PUSHBUTTONLOCKOUT;
        path->setTurnouts(0, true, lockState, true);
        firePropertyChange("path",QVariant(0), QVariant(getState()));
    }
    return msg;
}

/**
* Call for Circuit Builder to make icon color changes for its GUI
*/
/*public*/ void OBlock::pseudoPropertyChange(QString propName, QVariant old, QVariant n) {
    if (log->isDebugEnabled()) log->debug("pseudoPropertyChange: Block \""+getSystemName()+" property \""+
                                        propName+"\" new value= "+n.toString());
    firePropertyChange(propName, old, n);
}

/**
 * (Override)  Handles Block sensor going INACTIVE: this block is empty.
 * Called by handleSensorChange
 */
/*public*/ void OBlock::goingInactive() {
    if (log->isDebugEnabled()) log->debug("Allocated OBlock \""+getSystemName()+
                                        "\" goes UNOCCUPIED. from state= "+QString::number(getState()));
    if (_warrant!=NULL) {
        setValue(QVariant());
        _warrant->goingInactive(this);
    }
    // preserve the non-sensor states
    // non-UNOCCUPIED sensor states are removed (also cannot be RUNNING there if being UNOCCUPIED)
    setState((getState() & ~(UNKNOWN | OCCUPIED | INCONSISTENT | RUNNING)) | UNOCCUPIED);
    setValue(QVariant());
    if (_warrant != nullptr) {
//        ThreadingUtil.runOnLayout(() -> {
            _warrant->goingInactive(this);
//        });
    }
}

 /**
 * (Override) Handles Block sensor going ACTIVE: this block is now occupied,
 * figure out from who and copy their value. Called by handleSensorChange
 */
/*public*/ void OBlock::goingActive()
{
 if (log->isDebugEnabled()) {
     log->debug(tr("OBlock \"%1\" going OCCUPIED with path \"%2\" from state= %3").arg(
             getDisplayName()).arg(_pathName).arg(getState()));
 }
 // preserve the non-sensor states when being OCCUPIED and remove non-OCCUPIED sensor states
 setState((getState() & ~(UNKNOWN | UNOCCUPIED | INCONSISTENT)) | OCCUPIED);
//        if (log->isDebugEnabled()) log->debug("Allocated OBlock \""+getSystemName()+
//                                            "\" goes OCCUPIED. state= "+getState());
 if (_warrant!=NULL) {
     _warrant->goingActive(this);
 }
}

//@Override
/*public*/ void OBlock::goingUnknown() {
    if (log->isDebugEnabled()) {
        log->debug(tr("OBlock \"%1\" going UNKNOWN from state= %2").arg(getDisplayName()).arg(getState()));
    }
    setState((getState() & ~(UNOCCUPIED | OCCUPIED | INCONSISTENT)) | UNKNOWN);
}

//@Override
/*public*/ void OBlock::goingInconsistent() {
    if (log->isDebugEnabled()) {
        log->debug(tr("OBlock \"%1\" going INCONSISTENT from state= %2").arg(getDisplayName()).arg(getState()));
    }
    setState((getState() & ~(UNKNOWN | UNOCCUPIED | OCCUPIED)) | INCONSISTENT);
}

/*public*/ void OBlock::dispose() {

   QList <Portal*> list = getPortals();
    for (int i=0; i<list.size(); i++) {
        Portal* portal = list.at(i);
        OBlock* opBlock = portal->getOpposingBlock(this);
        // remove portal and stub paths through portal in opposing block
        opBlock->removePortal(portal);
    }
    QVector <Path*>* pathList = getPaths();
    for (int i=0; i<pathList->size(); i++) {
        removePath(pathList->at(i));
    }
    //InstanceManager::oBlockManagerInstance().deregister(this);
    Block::dispose();
}

/*public*/ QString OBlock::getDescription() {
//    return java.text.MessageFormat.format(
//        WarrantTableAction.tr("BlockDescription"), getDisplayName());
    return tr("OBlock \"%1\"").arg(getDisplayName());
}
