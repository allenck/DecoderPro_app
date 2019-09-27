#include "block.h"
#include "instancemanager.h"
#include <QRegExp>
#include "dcclocoaddress.h"
#include "locoaddress.h"
#include "lnsensor.h"
#include "signalspeedmap.h"
#include "path.h"


///*static*/ const int Block::OCCUPIED = Sensor::ACTIVE;
///*static*/ const int Block::UNOCCUPIED = Sensor::INACTIVE;
//const int Block::UNOCCUPIED = 0x04;
/*static const*/ int Block::NONE = 0x00;
/*static const*/ int Block::GRADUAL = 0x01;
/*static const*/ int Block::TIGHT = 0x02;
/*static const*/ int Block::SEVERE = 0x04;

// this should only be used for debugging...
/*public*/ QString Block::toDebugString() {
    QString result = getDisplayName(NamedBean::DisplayOptions::USERNAME_SYSTEMNAME) + " ";
    switch (getState()) {
        case UNDETECTED: {
            result += "UNDETECTED";
            break;
        }
        case UNOCCUPIED: {
            result += "UNOCCUPIED";
            break;
        }
        case OCCUPIED: {
            result += "OCCUPIED";
            break;
        }
        default: {
            result += "unknown " + getState();
            break;
        }
    }
    return result;
}

/**
 * Represents a particular piece of track, more informally a "Block".
 * As trains move around the layout, a set of Block objects interact to
 * keep track of which train is where, going in which direction.
 * As a result of this, the set of Block objects pass around  "token" (value)
 * Objects representing the trains.  This could be e.g. a Throttle to
 * control the train, or something else.
 * <P>
 * A Block (at least in this implementation) corresponds exactly to the
 * track covered by a single sensor. That should be generalized in the future.
 *
 * <p>
 * Optionally, a Block can be associated with a Reporter. In this case, the
 * Reporter will provide the Block with the "token" (value). This could be e.g
 * an RFID reader reading an ID tag attached to a locomotive. Depending on the
 * specific Reporter implementation, either the current reported value or the
 * last reported value will be relevant - this can be configured
 *<p>
 * Objects of this class are Named Beans, so can be manipulated through tables,
 * have listeners, etc.
 *
 * <p>
 * There is no functional requirement for a type letter in the System Name, but
 * by convention we use 'B' for 'Block'. The default implementation is not
 * system-specific, so a system letter of 'I' is appropriate.  This leads to
 * system names like "IB201".
 *
 *<p>The direction of a Block is set from the direction of the incoming
 * train. When a train is found to be coming in on a particular Path, that
 * Path's getFromBlockDirection becomes the direction of the train in this Block.
 *
 * <P>Issues:
 * <UL>
 * <LI> Doesn't handle a train pulling in behind another well:
 *      <UL>
 *      <LI>When the 2nd train arrives, the Sensor is already active, so the value is unchanged (but the value can only
 *          be a single object anyway)
 *      <LI>When the 1st train leaves, the Sensor stays active, so the value remains that of the 1st train
 *      </UL>
 * <LI> The assumption is that a train will only go through a set turnout.  For example, a train could
 *      come into the turnout block from the main even if the turnout is set to the siding.  (Ignoring those
 *      layouts where this would cause a short; it doesn't do so on all layouts)
 * <LI> Does not handle closely-following trains where there is only one
 *      electrical block per signal.   To do this, it probably needs some type of
 *      "assume a train doesn't back up" logic.  A better solution is to have multiple
 *      sensors and Block objects between each signal head.
 * <li> If a train reverses in a block and goes back the way it came (e.g. b1 to b2 to b1),
 *      the block that's re-entered will get an updated direction, but the direction of this block (b2 in the example)
 *      is not updated.  In other words, we're not noticing that the train must have reversed to go back out.
 *</UL>
 *
 *<P>
 * Do not assume that a Block object uniquely represents a piece of track.
 * To allow independent development, it must be possible for multiple Block objects
 * to take care of a particular section of track.
 *
 *<P>
 * Possible state values:
 *<ul>
 * <li>UNKNOWN - The sensor shows UNKNOWN, so this block doesn't know if it's occupied or not.
 * <li>INCONSISTENT - The sensor shows INCONSISTENT, so this block doesn't know if it's occupied or not.
 * <li>OCCUPIED - This sensor went active. Note that OCCUPIED will be set
 *              even if the logic is unable to figure out which value to take.
 * <li>UNOCCUPIED - No content, because the sensor has determined this block is unoccupied.
 *</ul>
 *
 *<P>
 * Possible Curvature attributes (optional) User can set the curvature if desired.
 *     For use in automatic running of trains, to indicate where slow down is required.
 *<ul>
 * <li>NONE - No curvature in Block track, or Not entered.
 * <li>GRADUAL - Gradual curve - no action by engineer is warranted - full speed OK
 * <li>TIGHT - Tight curve in Block track - Train should slow down some
 * <li>SEVERE - Severe curve in Block track - Train should slow down a lot
 *</ul>
 *
 *<P>
 * The length of the block may also optionally be entered if desired.  This attribute
 *		is for use in automatic running of trains.
 * Length should be the actual length of model railroad track in the block.  It is
 *		always stored here in millimeter units. A length of 0.0 indicates no entry of
 *		length by the user.
 *
 * @author	Bob Jacobsen  Copyright (C) 2006, 2008
 * @author  Dave Duchamp Copywright (C) 2009
 * @version	$Revision: 22571 $
 * GT 10-Aug-2008 - Fixed problem in goingActive() that resulted in a
 * NULL pointer exception when no sensor was associated with the block
 */
//public class Block extends jmri.implementation.AbstractNamedBean implements PhysicalLocationReporter {


/*public*/ Block::Block(QString systemName, QString userName,QObject* parent) : AbstractNamedBean(systemName.toUpper(), userName, parent)
{
    log = new Logger("Block");
    //super(systemName.toUpperCase(), userName);
    _current = UNDETECTED; // state
    _sensor = NULL;
    _namedSensor = NULL;
    _sensorListener = NULL;
    _value=QVariant();
    _direction=0;
    _curvature = NONE;
    _length = 0.0f;  // always stored in millimeters
    _reporter = NULL;
    _reporterListener = NULL;
    _reportingCurrent = false;
    paths = new QVector<Path*>();
    blockDenyList = new QVector<NamedBeanHandle<Block*>* >(1);
    _permissiveWorking=false;
    _blockSpeed = "";
    maxInfoMessages = 5;
    infoMessageCount = 0;
    setObjectName(systemName);
}


/*public*/ bool Block::setSensor(QString pName)
{
 bool ret;
  QString oldName = nullptr;
  Sensor* sensor = getSensor();
  if (sensor != nullptr) {
      oldName = sensor->getDisplayName();
  }
  // save the non-sensor states
  int saveState = getState() & ~(UNKNOWN | OCCUPIED | UNOCCUPIED | INCONSISTENT | UNDETECTED);
  if (pName == "" || pName.trimmed().length() == 0) {
      setNamedSensor(nullptr);
      ret = true;
  } else {
      sensor = InstanceManager::sensorManagerInstance()->getByUserName(pName);
      if (sensor == nullptr) {
          sensor = InstanceManager::sensorManagerInstance()->getBySystemName(pName);
      }
      if (sensor == nullptr) {
          if (log->isDebugEnabled()) {
              log->debug(tr("no sensor named \"%1\" exists.").arg(pName));
          }
          ret = false;
      } else {
          setNamedSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
          ret = true;
      }
  }
  setState(getState() | saveState);
  firePropertyChange("OccupancySensorChange", oldName, pName);
  return ret;
}

/*public*/ void Block::setNamedSensor(NamedBeanHandle<Sensor*>* s) {
  if (_namedSensor != nullptr) {
      if (_sensorListener != nullptr) {
          getSensor()->removePropertyChangeListener(_sensorListener);
          disconnect(getSensor(), SIGNAL(propertyChange(PropertyChangeEvent*)), _sensorListener, SLOT(propertyChange(PropertyChangeEvent*)));
          _sensorListener = nullptr;
      }
  }
  _namedSensor = s;

  if (_namedSensor != nullptr) {
//      getSensor()->addPropertyChangeListener(_sensorListener = (PropertyChangeEvent e) -> {
//          handleSensorChange(e);
//      }, s.getName(), "Block Sensor " + getDisplayName());
//      _current = getSensor()->getState();
   BlockSensorListener* _sensorListener = new BlockSensorListener(this);
   getSensor()->addPropertyChangeListener(_sensorListener);
   _current = getSensor()->getState();
  } else {
      _current = UNDETECTED;
  }
}
void BlockSensorListener::propertyChange(PropertyChangeEvent* e)
{
 block->handleSensorChange(e);
}
/*public*/ Sensor* Block::getSensor() {
    if (_namedSensor!=NULL)
        return _namedSensor->getBean();
    return NULL;
}

/*public*/ NamedBeanHandle <Sensor*>* Block::getNamedSensor() {
    return _namedSensor;
}

/**
 * Set the Reporter that should provide the data value for this block.
 *
 * @see Reporter
 * @param reporter Reporter object to link, or NULL to clear
 */
/*public*/ void Block::setReporter(Reporter* reporter)
{
 if (_reporter != NULL)
 {
  // remove reporter listener
  if (_reporterListener != NULL)
  {
   _reporter->removePropertyChangeListener(_reporterListener);
   _reporterListener = NULL;
  }
 }
 reporter = reporter;
 if (_reporter != NULL)
 {
  // attach listener
 // _reporter->addPropertyChangeListener(_reporterListener = new PropertyChangeListener());

// #if 0
//  {
//                // TODO:
//            /*public*/ void propertyChange(PropertyChangeEvent e) { handleReporterChange(e); }
//        });

//#endif
  connect(_reporter, SIGNAL(signalPropertyChange(PropertyChangeEvent*)), this, SLOT(handleReporterChange(PropertyChangeEvent*)));
 }
}

/**
 * Retrieve the Reporter that is linked to this Block
 *
 * @see Reporter
 * @return linked Reporter object, or NULL if not linked
 */
/*public*/ Reporter* Block::getReporter() { return _reporter; }

/**
 * Define if the Block's value should be populated from the
 * {@link Reporter#getCurrentReport() current report}
 * or from the {@link Reporter#getLastReport() last report}.
 *
 * @see Reporter
 * @param reportingCurrent
 */
/*public*/ void Block::setReportingCurrent(bool reportingCurrent)
{
 _reportingCurrent = reportingCurrent;
}

/**
 * Determine if the Block's value is being populated from the
 * {@link Reporter#getCurrentReport() current report}
 * or from the {@link Reporter#getLastReport() last report}.
 *
 * @see Reporter
 * @return true if populated by {@link Reporter#getCurrentReport() current report};
 * false if from {@link Reporter#getLastReport() last report}.
 */
/*public*/ bool Block::isReportingCurrent() { return _reportingCurrent; }

/*public*/ int Block::getState() {return _current;}
QString Block::getStateString()
{
 switch(_current)
 {
 case OCCUPIED:
  return tr("Occupied");
 case UNOCCUPIED:
  return tr("Unoccupied");
 default:
 //case NamedBean::UNKNOWN:
  break;
 }
 return tr("Unknown");
}

/*public*/ void Block::addPath(Path* p)
{
 if (p==NULL) throw new IllegalArgumentException("Can't add NULL path");
 paths->append(p);
}

/*public*/ void Block::removePath(Path* p)
{
 int j = -1;
 for (int i = 0; i<paths->size(); i++)
 {
  if (p == paths->at(i))
   j = i;
 }
 if (j>-1) paths->remove(j);
}

/**
 * Get a copy of the list of Paths
 */
/*public*/ QVector<Path*>* Block::getPaths()
{
 QVector<Path*>* l;
 l = new QVector<Path*> (/**paths*/);
 foreach (Path* p, *paths)
 {
  l->append(p);
 }
 return l;
}

/**
 * Provide a general method for updating the report.
 */
/*public*/ void Block::setState(int v)
{
 int old = _current;
 _current = v;
 // notify
 firePropertyChange("state", /*Integer.valueOf*/(old), /*Integer.valueOf*/(_current));
}

/**
 * Set the value retained by this Block.
 * Also used when the Block itself gathers a value from an
 * adjacent Block.  This can be overridden in a subclass if
 * e.g. you want to keep track of Blocks elsewhere, but make
 * sure you also eventually invoke the super.setValue() here.
 * <p>
 * @param value The new Object resident in this block, or NULL if none.
 */
/*public*/ void Block::setValue(QVariant value)
{
  QVariant old = _value;
  _value = value;
  firePropertyChange("value", old, _value);
}

/*public*/ QVariant Block::getValue() { return _value; }

/*public*/ void Block::setDirection(int direction)
{
 int oldDirection = _direction;
 _direction = direction;
 // this is a bound parameter
 firePropertyChange("direction", /*Integer.valueOf*/(oldDirection), /*Integer.valueOf*/(direction));
}

/*public*/ int Block::getDirection() { return _direction; }

/**
* The block deny list, is used by higher level code, to determine if
* traffic/trains should be allowed to enter from an attached block,
* the list only deals with blocks that access should be denied from.
* If we want to prevent traffic from following from this block to another
* then this block must be added to the deny list of the other block.
* By default no block is barred, so traffic flow is bi-directional.
*/
/*public*/ void Block::addBlockDenyList(QString pName)
{
 Block* blk = InstanceManager::blockManagerInstance()->getBlock(pName);
 NamedBeanHandle<Block*>* namedBlock = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, blk);
 Q_ASSERT(namedBlock != NULL);
 if(!blockDenyList->contains(namedBlock))
  blockDenyList->append(namedBlock);
}

/*public*/ void Block::addBlockDenyList(Block* blk)
{
 NamedBeanHandle<Block*>* namedBlock = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(blk->getDisplayName(), blk);
    if(!blockDenyList->contains(namedBlock))
        blockDenyList->append(namedBlock);
}

/*public*/ void Block::removeBlockDenyList(QString blk)
{
 NamedBeanHandle<Block*>* toremove = NULL;
 foreach(NamedBeanHandle<Block*>* bean, *blockDenyList)
 {
  if(bean->getName()==(blk))
   toremove=bean;
 }
 if(toremove!=NULL)
 {
  blockDenyList->remove(blockDenyList->indexOf(toremove));
    }
}

/*public*/ void Block::removeBlockDenyList(Block* blk)
{
 NamedBeanHandle<Block*>* toremove = NULL;
 foreach(NamedBeanHandle<Block*>* bean, *blockDenyList)
 {
  if(bean->getBean()==blk)
   toremove=bean;
 }
 if(toremove!=NULL)
 {
  blockDenyList->remove(blockDenyList->indexOf(toremove));
 }
}

/*public*/ QList<QString>* Block::getDeniedBlocks()
{
 QStringList* list = new QStringList(/*blockDenyList->size()*/);
 foreach(NamedBeanHandle<Block*>* bean, *blockDenyList)
 {
  if(bean != NULL)
   list->append(bean->getName());
 }
 return list;
}

/*public*/ bool Block::isBlockDenied(QString deny)
{
 foreach(NamedBeanHandle<Block*>* bean, *blockDenyList)
 {
  if(bean== NULL) return false;
  if(bean->getName()==(deny))
   return true;
 }
 return false;
}

/*public*/ bool Block::isBlockDenied(Block* deny)
{
 foreach(NamedBeanHandle<Block*>* bean, *blockDenyList)
 {
  if(bean->getBean()==deny)
   return true;
 }
 return false;
}

/*public*/ bool Block::getPermissiveWorking() { return _permissiveWorking; }
/*public*/ void Block::setPermissiveWorking(bool w) { _permissiveWorking=w; }

/*public*/ float Block::getSpeedLimit()
{
 if ((_blockSpeed==NULL) || (_blockSpeed==("")))
  return -1;
 QString speed = _blockSpeed;
 if(_blockSpeed==("Global"))
 {
  speed = InstanceManager::blockManagerInstance()->getDefaultSpeed();
 }

 try
 {
  return /*new*/ /*Float(speed)*/speed.toFloat();
 }
 catch (NumberFormatException nx)
 {
        //considered normal if the speed is not a number.
 }
 try
 {
  //return jmri.implementation.SignalSpeedMap.getMap().getSpeed(speed);
 }
 catch (Exception ex)
 {
  return -1;
 }
 return -1;
}

/*public*/ QString Block::getBlockSpeed()
{
 if(_blockSpeed==("Global"))
  return ("Use Global " + InstanceManager::blockManagerInstance()->getDefaultSpeed());
 return _blockSpeed;
}

 /*public*/ void Block::setBlockSpeed(QString s) throw (JmriException)
{
 if((s==NULL) || (_blockSpeed==(s)))
  return;
 if(s.contains("Global"))
  s = "Global";
 else
 {
//  try
//  {
//            Float.parseFloat(s);
   bool bOk=false;
   float f = s.toFloat(&bOk);
   Q_UNUSED(f);
   if(!bOk)
   {
    f = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(s);
    if(f == 0.0)
     log->error(tr("Block %1 has invalid speed '%2'").arg(getDisplayName()).arg(s));
   }
   //  }
//  catch (NumberFormatException nx)
//  {
//   try
//   {
////                SignalSpeedMap.getMap().getSpeed(s);
//    }
//    catch (Exception ex)
//    {
//     throw new JmriException("Value of requested block speed is not valid");
//    }
//   }
  }
  QString oldSpeed = _blockSpeed;
  _blockSpeed=s;
  firePropertyChange("BlockSpeedChange", oldSpeed, s);
}
/*public*/ void Block::setBlockSpeedName(QString s)
{
    if(s==NULL) {
        _blockSpeed = "";
    } else {
        _blockSpeed = s;
    }
}
/*public*/ void Block::setCurvature(int c) { _curvature = c; }
/*public*/ int Block::getCurvature() { return _curvature; }
/*public*/ void Block::setLength(float l) { _length = l; }  // l must be in millimeters
/*public*/ float Block::getLengthMm() { return _length; } // return length in millimeters
/*public*/ float Block::getLengthCm() { return (_length/10.0f); }  // return length in centimeters
/*public*/ float Block::getLengthIn() { return (_length/25.4f); }  // return length in inches

/**
 * Note: this has to make choices about identity values (always the same)
 * and operation values (can change as the block works). Might be missing
 * some identity values.
 */
//@Override
/*public*/ bool Block::equals(QObject* obj) {
    if (obj == this) {
        return true;
    }
    if (obj == nullptr) {
        return false;
    }

    if (!(metaObject()->className() == obj->metaObject()->className())) {
        return false;
    } else {
        Block* b = (Block*) obj;

        if (!(b->getSystemName() == (this->getSystemName()))) {
            return false;
        }
    }
    return true;
}

/** Handle change in sensor state.
 * <P>
 * Defers real work to goingActive, goingInactive methods
 */
void Block::handleSensorChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  int state = getSensor()->getState();
  if (state == Sensor::ACTIVE) goingActive(); // 0x02
  else if (state == Sensor::INACTIVE) goingInactive(); // 0x04
  else if (state == Sensor::UNKNOWN)
  {
      setValue(QVariant());
   setState(Sensor::UNKNOWN);
  }
  else
  {
      setValue(QVariant());
   setState(INCONSISTENT);
  }
 }
}
void Block::handleSensorChange(QString propertyName, int /*o*/, int /*n*/)
{
 if (propertyName==("KnownState"))
 {
  int state = getSensor()->getState();
  if (state == Sensor::ACTIVE) goingActive();
  else if (state == Sensor::INACTIVE) goingInactive();
  else if (state == Sensor::UNKNOWN)
  {
   setValue(QVariant());
   setState(Sensor::UNKNOWN);
  }
  else
  {
   setValue(QVariant());
   setState(INCONSISTENT);
  }
 }
}

/**
 * Handle change in Reporter value.
 *
 * @param e PropertyChangeEvent
 */
void Block::handleReporterChange(PropertyChangeEvent* e)
{
 if ((_reportingCurrent &&e->getPropertyName()==("currentReport"))
            || (!_reportingCurrent && e->getPropertyName()==("lastReport")))
 {
  setValue(e->getNewValue());
 }
}

/**
 * Handles Block sensor going INACTIVE: this block is empty
 */
/*public*/ void Block::goingInactive() {
    if (log->isDebugEnabled()) log->debug("Block "+getSystemName()+" goes UNOCCUPIED");
    setValue(QVariant());
    setDirection(Path::NONE);
    setState(UNOCCUPIED);
}

/**
 * Handles Block sensor going ACTIVE: this block is now occupied,
 * figure out from who and copy their value.
 */
/*public*/ void Block::goingActive()
{
 if (log->isDebugEnabled()) log->debug("Block "+getSystemName()+" goes OCCUPIED");
 // index through the paths, counting
 int count = 0;
 Path* next = NULL;
 // get statuses of everything once
 int currPathCnt = paths->size();
 QList<Path*>* pList = new QList<Path*>(/*currPathCnt*/);
 QList<bool>* isSet = new QList<bool>(/*currPathCnt*/);
 QList<Sensor*>* pSensor = new QList<Sensor*>()/*[currPathCnt]*/;
 QList<bool>* isActive = new QList<bool>();
 QList<int>* pDir = new QList<int>()/*[currPathCnt]*/;
 QList<int>* pFromDir = new QList<int>()/*[currPathCnt]*/;
 for (int i = 0; i < currPathCnt; i++)
 {
  pList->append(paths->value(i));
  isSet->append(pList->at(i)->checkPathSet());
  Block* b = pList->at(i)->getBlock();
  if (b != NULL)
  {
   pSensor->append(b->getSensor());
   if (pSensor->at(i) != NULL)
   {
    isActive->append( pSensor->at(i)->getState() == Sensor::ACTIVE);
   }
   else
   {
     isActive->append(false);
   }
   pDir->append(b->getDirection());
  }
  else
  {
   pSensor->append( NULL);
   isActive->append(false);
   pDir->append(-1);
  }
  pFromDir->append( pList->at(i)->getFromBlockDirection());
  if (isSet->at(i) && pSensor->at(i) != NULL && isActive->at(i))
  {
   count++;
   next = pList->at(i);
  }
 }
 // sort on number of neighbors
 if (count == 0)
 {
  if (infoMessageCount < maxInfoMessages)
  {
   log->info("Sensor ACTIVE came out of nowhere, no neighbors active for block "+getSystemName()+". Value not set.");
   infoMessageCount ++;
  }
 }
 else if (count == 1)
 { // simple case

  if ((next != NULL) && (next->getBlock() != NULL))
  {
   // normal case, transfer value object
   setValue(next->getBlock()->getValue());
   setDirection(next->getFromBlockDirection());
   if (log->isDebugEnabled())
    log->debug("Block "+getSystemName()+" gets new value from "+next->getBlock()->getSystemName()+", direction="+Path::decodeDirection(getDirection()));
  }
  else if (next == NULL)
   log->error("unexpected next==NULL processing signal in block "+getSystemName());
  else if (next->getBlock() == NULL) log->error("unexpected next.getBlock()=NULL processing signal in block "+getSystemName());
 }
 else
 {  // count > 1, check for one with proper direction
  // this time, count ones with proper direction
  if (log->isDebugEnabled()) log->debug ("Block "+getSystemName()+"- count of active linked blocks = "+QString("%1").arg(count));
  next = NULL;
  count = 0;
  for (int i = 0; i < currPathCnt; i++)
  {
   if (isSet->at(i) && pSensor->at(i) != NULL && isActive->at(i) && (pDir->at(i) == pFromDir->at(i)))
   {
    count++;
    next = pList->at(i);
   }
  }
  if (next == NULL)
   if (log->isDebugEnabled()) log->debug("next is NULL!");
  if (next != NULL && count == 1)
  {
   // found one block with proper direction, assume that
   setValue(next->getBlock()->getValue());
   setDirection(next->getFromBlockDirection());
   if (log->isDebugEnabled()) log->debug("Block "+getSystemName()+" with direction "+Path::decodeDirection(getDirection())+" gets new value from "+next->getBlock()->getSystemName()+", direction="+Path::decodeDirection(getDirection()));
  }
  else
  {
   // no unique path with correct direction - this happens frequently from noise in block detectors!!
   log->warn("count of " + QString("%1").arg(count) + " ACTIVE neighbors with proper direction can't be handled for block " + getSystemName());
  }
 }
 // in any case, go OCCUPIED
 setState(OCCUPIED);
}

/**
 * Find which path this Block became Active, without actually
 * modifying the state of this block.
 *
 * (this is largely a copy of the 'Search' part of the logic
 * from goingActive())
 */
/*public*/ Path* Block::findFromPath()
{
    // index through the paths, counting
    int count = 0;
    Path* next = NULL;
    // get statuses of everything once
    int currPathCnt = paths->size();
    QList<Path*>* pList = new QList<Path*>(/*currPathCnt*/);
    QList<bool>* isSet = new QList<bool>(/*currPathCnt*/);
    QList<Sensor*>* pSensor = new QList<Sensor*>()/*[currPathCnt]*/;
    QList<bool>* isActive = new QList<bool>();
    QList<int>* pDir = new QList<int>()/*[currPathCnt]*/;
    QList<int>* pFromDir = new QList<int>()/*[currPathCnt]*/;
    for (int i = 0; i < currPathCnt; i++)
    {
     pList->append(paths->value(i));
     isSet->append(pList->at(i)->checkPathSet());
     Block* b = pList->at(i)->getBlock();
     if (b != NULL)
     {
      pSensor->append(b->getSensor());
      if (pSensor->at(i) != NULL)
      {
       isActive->append(pSensor->at(i)->getState() == Sensor::ACTIVE);
      }
      else
      {
       isActive->append(false);
      }
      pDir->append(b->getDirection());
     }
     else
     {
      pSensor->append(NULL);
      isActive->append(false);
      pDir->append(-1);
     }
     pFromDir->append(pList->at(i)->getFromBlockDirection());
     if (isSet->at(i) && pSensor->at(i) != NULL && isActive->at(i))
     {
      count++;
      next = pList->at(i);
     }
    }
    // sort on number of neighbors
    if ((count == 0) || (count == 1))
    {
    // do nothing.  OK to return NULL from this function.  "next" is already set.
    }
    else
    {
     // count > 1, check for one with proper direction
     // this time, count ones with proper direction
     if (log->isDebugEnabled())
         log->debug ("Block "+getSystemName()+"- count of active linked blocks = "+count);
     next = NULL;
     count = 0;
     for (int i = 0; i < currPathCnt; i++)
     {
      if (isSet->at(i) && pSensor->at(i) != NULL && isActive->at(i) && (pDir->at(i) == pFromDir->at(i)))
      {
       count++;
       next = pList->at(i);
      }
     }
     if (next == NULL)
      if (log->isDebugEnabled()) log->debug("next is NULL!");
     if (next != NULL && count == 1)
     {
            // found one block with proper direction, assume that
     }
     else
     {
      // no unique path with correct direction - this happens frequently from noise in block detectors!!
      log->warn("count of " + QString("%1").arg(count) + " ACTIVE neightbors with proper direction can't be handled for block " + getSystemName());
     }
    }
    // in any case, go OCCUPIED
    if (log->isDebugEnabled())
      log->debug("Block "+getSystemName()+" with direction "+Path::decodeDirection(getDirection())+" gets new value from "+next->getBlock()->getSystemName() + "(informational. No state change)");
return(next);
}

// Methods to implmement PhysicalLocationReporter Interface
//
// If we have a Reporter that is also a PhysicalLocationReporter,
// we will defer to that Reporter's methods.
// Else we will assume a LocoNet style message to be parsed.

/** Parse a given string and return the LocoAddress value that is presumed stored
 * within it based on this object's protocol.
 * The Class Block implementationd defers to its associated Reporter, if it exists.
 *
 * @param rep String to be parsed
 * @return LocoAddress address parsed from string, or NULL if this Block isn't associated
 *         with a Reporter, or is associated with a Reporter that is not also a
 *         PhysicalLocationReporter
 */
/*public*/ LocoAddress* Block::getLocoAddress(QString rep)
{
 // Defer parsing to our associated Reporter if we can.
 if (rep == NULL)
 {
  log->warn("String input is NULL!");
  return(NULL);
 }
// if ((this->getReporter() != NULL) && (this->getReporter() instanceof PhysicalLocationReporter))
 if((this->getReporter() != NULL) /*&& dynamic_cast<PhysicalLocationReporter*> (this->getReporter()) != NULL*/)
 {
    return(((PhysicalLocationReporter*)this->getReporter())->getLocoAddress(rep));
 }
 else
 {
  // Assume a LocoNet-style report.  This is (nascent) support for handling of Faller cars
  // for Dave Merrill's project.
  log->debug("report string: " + rep);
  // NOTE: This pattern is based on the one defined in jmri.jmrix.loconet.LnReporter
//  Pattern* ln_p = Pattern.compile("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.
//  Matcher m = ln_p.matcher(rep);
//  if ((m != NULL) && m.find())
  QRegExp regExp("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");
  QStringList sl = rep.split(" ");
  if(regExp.exactMatch(rep) && sl.count() ==2)
  {
   //log->debug("Parsed address: " + m.group(1));
      log->debug("Parsed address: " + sl.at(1));
   //return(new DccLocoAddress(Integer.parseInt(m.group(1)), LocoAddress.Protocol.DCC));
   return new DccLocoAddress(sl.at(0).toInt(), LocoAddress::DCC);
  }
   else
   {
    return(NULL);
   }
 }
}

/** Parses out a (possibly old) LnReporter-generated report string to extract the direction from
 * within it based on this object's protocol.
 * The Class Block implementationd defers to its associated Reporter, if it exists.
 *
 * @param rep String to be parsed
 * @return PhysicalLocationReporter.Direction direction parsed from string, or NULL if
 *         this Block isn't associated with a Reporter, or is associated with a Reporter
 *         that is not also a PhysicalLocationReporter
 */
/*public*/ PhysicalLocationReporter::Direction Block::getDirection(QString rep)
{
 if (rep == NULL)
 {
  log->warn("String input is NULL!");
  return(PhysicalLocationReporter::UNKNOWN);
 }

 // Defer parsing to our associated Reporter if we can.
 //if ((this->getReporter() != NULL) && (this->getReporter() instanceof PhysicalLocationReporter))
 if((this->getReporter() != NULL) /*&& dynamic_cast<PhysicalLocationReporter*> (this->getReporter()) != NULL*/)
 {
  return(((PhysicalLocationReporter*)this->getReporter())->getDirection(rep));
 }
 else
 {
  log->debug("report string: " + rep);
  // NOTE: This pattern is based on the one defined in jmri.jmrix.loconet.LnReporter
//  Pattern ln_p = Pattern.compile("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.
//  Matcher m = ln_p.matcher(rep);
//  if (m.find())
  QRegExp regExp("(\\d+) (enter|exits|seen)\\s*(northbound|southbound)?");  // Match a number followed by the word "enter".  This is the LocoNet pattern.
  QStringList sl = rep.split(" ");
  if(regExp.exactMatch(rep) && sl.count() == 2)
  {
      log->debug("Parsed direction: " + /*m.group(2)*/ sl.at(2));
   if(/*m.group(2).equals*/sl.at(2) == "enter")
   {
    // LocoNet Enter message
    return(PhysicalLocationReporter::ENTER);
   }
   else if (/*m.group(2).equals*/sl.at(2) ==("seen"))
   {
    // Lissy message.  Treat them all as "entry" messages.
    return(PhysicalLocationReporter::ENTER);
   }
   else
   {
    return(PhysicalLocationReporter::EXIT);
   }
  }
  else
  {
   return(PhysicalLocationReporter::UNKNOWN);
  }
 }
}

/** Return this Block's physical location, if it exists.
 * Defers actual work to the helper methods in class PhysicalLocation
 *
 * @return PhysicalLocation : this Block's location.
 */
/*public*/ PhysicalLocation* Block::getPhysicalLocation() {
// We have our won PhysicalLocation. That's the point.  No need to defer to the Reporter.
return(PhysicalLocation::getBeanPhysicalLocation(this));
}

/** Return this Block's physical location, if it exists.
 * Does not use the parameter s
 * Defers actual work to the helper methods in class PhysicalLocation
 *
 * @param s (this parameter is ignored)
 * @return PhysicalLocation : this Block's location.
 */
/*public*/ PhysicalLocation* Block::getPhysicalLocation(QString s)
{
 Q_UNUSED(s)
// We have our won PhysicalLocation. That's the point.  No need to defer to the Reporter.
// Intentionally ignore the String s
return(PhysicalLocation::getBeanPhysicalLocation(this));
}

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(Block.class.getName());
