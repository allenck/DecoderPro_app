#include "warrant.h"
#include "signalspeedmap.h"
#include "oblock.h"
#include "throttlesetting.h"
#include "rosterentry.h"
#include "roster.h"
#include "blockorder.h"
#include "engineer.h"
#include "instancemanager.h"
#include "lnthrottlemanager.h"
#include "learnthrottleframe.h"
#include "lnthrottlemanager.h"
#include "loconetthrottle.h"
#include "opath.h"
#include "trackertableaction.h"
#include "sleeperthread.h"
#include "speedutil.h"

//Warrant::Warrant(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * An Warrant contains the operating permissions and directives needed for
 * a train to proceed from an Origin to a Destination
 * <P>
 * Version 1.11 - remove setting of SignalHeads
 *
 * @version $Revision: 21972 $
 * @author	Pete Cressman  Copyright (C) 2009, 2010
 */
///*public*/ class Warrant extends jmri.implementation.AbstractNamedBean
//                    implements ThrottleListener, java.beans.PropertyChangeListener {

//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.logix.WarrantBundle");
// permanent members.
/*private*/ /*static*/ SignalSpeedMap* Warrant::_speedMap = nullptr;

/*public*/ /*static*/ /*final*/ QString Warrant::Stop = "Stop";   // NOI18N
/*public  static final*/ QString Warrant::EStop = "EStop";     // NOI18N
/*public  static final*/ QString Warrant::Normal = "Normal";   // NOI18N
/*public  static final*/ QString Warrant::Clear = "Clear";     // NOI18N

/*protected*/ /*static*/ /*final*/ QStringList Warrant::CNTRL_CMDS = QStringList() << tr("Stop")<< tr("Halt")<< tr("Resume")<< tr("Abort")<< tr("Retry");

/*protected*/ /*static*/ /*final*/ QStringList Warrant::RUN_STATE = QStringList()<< tr("At start in block \"%1\"")<< tr("Halted in block \"%1\"")<< tr("Resume")<< tr("Script aborted in block \"%1\" at Cmd #%2.")<< tr("Move into next block") << tr("Running in block \"%1\"")<< tr("speed restricted in block \"%1\"")<< tr("Waiting in block \"%1\" for clearance ahead")<< tr("Waiting block \"%1\" for sensor")<< tr("In block \"%1\", running late to next block");


/**
 * Create an object with no route defined.
 * The list of BlockOrders is the route from an Origin to a Destination
 */
/*public*/ Warrant::Warrant(QString sName, QString uName, QObject *parent) : AbstractNamedBean(sName.toUpper(), uName, parent)
{
 //super(sName.toUpperCase(), uName);
 log = new Logger("Warrant");
 _savedOrders = new QList <BlockOrder*>();
 _throttleCommands = new QList <ThrottleSetting*>();
 _throttleFactor = 1.0;

 _idxCurrentOrder = 0;
//        _idxTrailingOrder = -1;
 _orders = _savedOrders;
 _runBlind = false;
 _viaOrder = nullptr;
 _avoidOrder = nullptr;
 _dccAddress = nullptr;
 _runMode = 0;
 _stoppingSignal = nullptr;
 _stoppingBlock = nullptr;
 _speedUtil = new SpeedUtil(_orders);

 _debug = log->isDebugEnabled();
}
/*public*/ /*final*/ /*static*/ SignalSpeedMap* Warrant::getSpeedMap() {
    if (_speedMap==nullptr) {
        _speedMap = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"));
    }
    return _speedMap;
}

// _state not used (yet?)
/*public*/ int Warrant::getState()
{
 return UNKNOWN;
}
/*public*/ void Warrant::setState(int /*state*/)
{
}

/*public*/ SpeedUtil* Warrant::getSpeedUtil() {
    return _speedUtil;
}

/*public*/ void Warrant::setSpeedUtil(SpeedUtil* su) {
    _speedUtil = su;
}

/**
* Return permanently saved BlockOrders
*/
/*public*/ QList<BlockOrder*>* Warrant::getBlockOrders()
{
    QList<BlockOrder*>* orders = new QList<BlockOrder*>();
    for (int i = 0; i < _savedOrders->size(); i++) {
        orders->append(new BlockOrder(_savedOrders->at(i)));
    }
    return orders;
}
/**
* Add permanently saved BlockOrder
*/
/*public*/ void Warrant::addBlockOrder(BlockOrder* order) {
    _savedOrders->append(order);
}

/*public*/ void Warrant::setBlockOrders(QList<BlockOrder*>* orders)
{
 _savedOrders->clear();
 for (int i = 0; i < orders->size(); i++) {
     _savedOrders->append(new BlockOrder(orders->at(i)));
 }
}

/*protected*/ void Warrant::setOrders(QList<BlockOrder*>* orders) {
    _orders = orders;
}
/*protected*/ QList<BlockOrder*>* Warrant::getOrders() {
    if (/*_orders!=nullptr &&*/ _orders->size()>0) {
        return _orders;
    }
    return getBlockOrders();
}

/**
* Return permanently saved Origin
*/
/*public*/ BlockOrder* Warrant::getfirstOrder() {
    if (_orders->size()==0) { return nullptr; }
    return new BlockOrder(_orders->at(0));
}

/**
* Return permanently saved Destination
*/
/*public*/ BlockOrder* Warrant::getLastOrder() {
    if (_orders->size()==0) { return nullptr; }
    return new BlockOrder(_orders->at(_savedOrders->size()-1));
}

/**
* Return permanently saved BlockOrder that must be included in the route
*/
/*public*/ BlockOrder* Warrant::getViaOrder() {
    if (_viaOrder==nullptr) { return nullptr; }
    return new BlockOrder(_viaOrder);
}
/*public*/ void Warrant::setViaOrder(BlockOrder* order) { _viaOrder = order; }

/*public*/ BlockOrder* Warrant::getAvoidOrder() {
    if (_avoidOrder==nullptr) { return nullptr; }
    return new BlockOrder(_avoidOrder);
}
/*public*/ void Warrant::setAvoidOrder(BlockOrder* order) { _avoidOrder = order; }

/*protected*/ QString Warrant::getRoutePathInBlock(OBlock* block) {
    QList <BlockOrder*>* orders = _orders;
    if (orders->isEmpty()) {
        orders = _savedOrders;
    }
    for (int i=0; i<orders->size(); i++){
        if (orders->at(i)->getBlock()==(block)) {
            return orders->at(i)->getPathName();
        }
    }
    return "";
}

/**
* Call is only valid when in MODE_LEARN and MODE_RUN
*/
/*public*/ BlockOrder* Warrant::getCurrentBlockOrder() {
    return getBlockOrderAt(_idxCurrentOrder);
}

/*public*/ int Warrant::getCurrentOrderIndex() {
    return _idxCurrentOrder;
}

/**
* Call is only valid when in MODE_LEARN and MODE_RUN
*/
/*protected*/ int Warrant::getIndexOfBlock(OBlock* block, int startIdx) {
    for (int i=startIdx; i<_orders->size(); i++){
        if (_orders->at(i)->getBlock()==(block)) {
            return i;
        }
    }
    return -1;
}
/**
* Call is only valid when in MODE_LEARN and MODE_RUN
* (previously start was i=_idxCurrentOrder)
*/
/*protected*/ int Warrant::getIndexOfBlock(QString name, int startIdx) {
    for (int i=startIdx; i<_orders->size(); i++){
        if (_orders->at(i)->getBlock()->getDisplayName()==(name)) {
            return i;
        }
    }
    return -1;
}
/**
* Call is only valid when in MODE_LEARN and MODE_RUN
*/
/*protected*/ BlockOrder* Warrant::getBlockOrderAt(int index) {
    if (index>=0 && index<_orders->size()) {
        return _orders->at(index);
    }
    return nullptr;
}
/**
* Call is only valid when in MODE_LEARN and MODE_RUN
*/
/*protected*/ OBlock* Warrant::getBlockAt(int idx) {

    BlockOrder* bo = getBlockOrderAt(idx);
    if (bo!=nullptr) {
        return bo->getBlock();
    }
    return nullptr;
}
/**
 * Call is only valid when in MODE_LEARN and MODE_RUN.
 *
 * @return Name of OBlock currently occupied
 */
/*public*/ QString Warrant::getCurrentBlockName() {
    OBlock* block = getBlockAt(_idxCurrentOrder);
    if (block == nullptr) {
        return "";
    } else {
        return block->getDisplayName();
    }
}

/**
* Call is only valid when in MODE_LEARN and MODE_RUN
*/
/*private*/ int Warrant::getBlockStateAt(int idx) {

    OBlock* b = getBlockAt(idx);
    if (b!= nullptr) {
        return b->getState();
    }
    return  OBlock::UNKNOWN;
}

/*public*/ QList <ThrottleSetting*>* Warrant::getThrottleCommands() {
    return _throttleCommands;
}
/*public*/ void Warrant::addThrottleCommand(ThrottleSetting* ts) {
    _throttleCommands->append(ts);
}

/*public*/ void Warrant::setThrottleCommands(QList<ThrottleSetting*> list) {
        _throttleCommands = &list;
    }
/*public*/ QString Warrant::getTrainName() { return _trainName; }
/*public*/ void Warrant::setTrainName(QString name) {
    _trainName = name;
}

/*public*/ QString Warrant::getTrainId() { return _trainId; }
/**
* @param id may be either Roster entry or DCC address
* @return id is valid
*/
/*public*/ bool Warrant::setTrainId(QString id) {
    _trainId = id;
    if (id=="" || id.trimmed().length()==0) {
        return false;
    }
    RosterEntry* train = Roster::getDefault()->entryFromTitle(id);
    if (train != nullptr) {
        _dccAddress = train->getDccLocoAddress();
    } else {
        int index = id.indexOf('(');
        QString numId;
        if (index >= 0) {
            numId = id.mid(0, index);
        } else {
            numId = id;
        }
        QList<RosterEntry*> l = Roster::getDefault()->matchingList(nullptr, nullptr, numId, nullptr, nullptr, nullptr, nullptr );
        if (l.size() > 0) {
            try {
                _dccAddress = l.at(0)->getDccLocoAddress();
            } catch (NumberFormatException e) {
                return false;
            }
        } else {
            bool isLong = true;
            if ((index+1)<id.length() &&
                (id.at(index+1)=='S' || id.at(index+1)=='s')) {
                isLong = false;
            }
            try {
                int num = numId.toInt();
                _dccAddress = new DccLocoAddress(num, isLong);
            } catch (NumberFormatException e) {
                return false;
            }
        }
    }
    return true;
}

/*protected*/ RosterEntry* Warrant::getRosterEntry()
{
 return _train;
}

/*public*/ DccLocoAddress* Warrant::getDccAddress() { return _dccAddress;  }

/*public*/ void Warrant::setDccAddress(DccLocoAddress* address) {
    _dccAddress = address;
    QString id = nullptr;
    if (address!=nullptr) {
        id = address->toString();
        if (_trainId!=nullptr) {
            id = _trainId;
        }
    }
    firePropertyChange("trainId", "", id);
}
/**
 * Sets dccAddress and fetches RosterEntry
 * @param id address as a String
 * @return
 */
/*public*/ bool Warrant::setDccAddress(QString id) {
    _train = Roster::getDefault()->entryFromTitle(id);
    if (_train == nullptr) {
        int index = id.indexOf('(');
        QString numId;
        if (index >= 0) {
            numId = id.mid(0, index);
        } else {
            numId = id;
        }
        try {
            QList<RosterEntry*> l = Roster::getDefault()->matchingList(nullptr, nullptr, numId, nullptr, nullptr, nullptr, nullptr);
            if (l.size() > 0) {
                _train = l.at(0);
                _trainId = _train->getId();
            } else {
                _train = nullptr;
                _trainId = "";
                bool isLong = true;
                if ((index + 1) < id.length()
                        && (id.at(index + 1) == 'S' || id.at(index + 1) == 's')) {
                    isLong = false;
                }
                int num = numId.toInt();
                _dccAddress = new DccLocoAddress(num, isLong);
                _trainId = _dccAddress->toString();
           }
        } catch (NumberFormatException e) {
            _dccAddress = nullptr;
            return false;
        }
    } else {
        _trainId = id;
        _dccAddress = _train->getDccLocoAddress();
    }
    return true;
}
/*public*/ /*static*/ QString Warrant::modeName(int i)
{
 switch(i)
 {
 default:
 case MODE_NONE:
  return tr("None");
 case MODE_LEARN :	// Record command list
  return tr("Learn ");
  case MODE_RUN:	// Autorun (playback) command list
  return tr("Running");
  case MODE_MANUAL:	// block detection/reservation for manually run train
  return tr("Manual run");
 }
}

/*public*/ bool Warrant::getRunBlind() {return _runBlind; }
/*public*/ void Warrant::setRunBlind(bool runBlind) { _runBlind = runBlind; }

/*public*/ QString Warrant::setThrottleFactor(QString sFactor) {
    try {
        _throttleFactor =sFactor.toFloat();
    } catch (NumberFormatException nfe) {
        return tr("Throttle adjustment factor must be a decimal number.");
    }
    return nullptr;
}
/*protected*/ DccThrottle* Warrant::getThrottle()
{
 if (_engineer!=nullptr)
 {
     return _engineer->getThrottle();
 }
 return nullptr;
}
///*protected*/ void Warrant::setCalibrater(Calibrater* c) {
//    _calibrater = c;
//}

/**
* Engineer reports its status
*/
/*protected*/ void Warrant::fireRunStatus(QString property, QVariant old, QVariant status) {
    firePropertyChange(property, old, status);
}

/******************************** state queries *****************/
/**
* Listeners are installed for the route
*/
/*public*/ bool Warrant::isAllocated() { return _allocated; }
/*public*/ bool Warrant::isTotalAllocated() { return _totalAllocated; }
/**
* Turnouts are set for the route
*/
/*public*/ bool Warrant::hasRouteSet() { return _routeSet; }

/**
* Test if the permanent saved blocks of this warrant are free
* (unoccupied and unallocated)
*/
/*public*/ bool Warrant::routeIsFree() {
    for (int i=0; i<_savedOrders->size(); i++) {
        OBlock* block = _savedOrders->at(i)->getBlock();
        if (!block->isFree()) { return false; }
    }
    return true;
}

/**
* Test if the permanent saved blocks of this warrant are occupied
*/
/*public*/ bool Warrant::routeIsOccupied() {
    for (int i=1; i<_savedOrders->size(); i++) {
        OBlock* block = _savedOrders->at(i)->getBlock();
        if ((block->getState() & OBlock::OCCUPIED) !=0) {
            return true;
        }
    }
    return false;
}

/*************** Methods for running trains ****************/
/*protected*/ bool Warrant::isWaitingForSignal() {
    return _waitForSignal;
}
/*protected*/ bool Warrant::isWaitingForClear() {
    return _waitForBlock;
}
/*protected*/ bool Warrant::isWaitingForWarrant() {
    return _waitForWarrant;
}
/*protected*/ Warrant* Warrant::getBlockingWarrant() {
    if (_stoppingBlock != nullptr && !this->equals(_stoppingBlock->getWarrant())) {
        return _stoppingBlock->getWarrant();
    }
    if (_otherShareBlock != nullptr) {
        return _otherShareBlock->getWarrant();
    }
    return nullptr;
}
/*public*/ int Warrant::getRunMode() { return _runMode; }

/*protected*/ QString Warrant::getRunModeMessage()
{
 QString modeDesc = nullptr;
 switch (_runMode) {
     case MODE_NONE:
         return tr("Warrant \"%1\" not set for running.").arg( getDisplayName());
     case MODE_LEARN:
         modeDesc = tr("recording an AutoRun script");
         break;
     case MODE_RUN:
         modeDesc = tr("train running an AutoRun script");
         break;
     case MODE_MANUAL:
         modeDesc = tr("train running under Manual control");
         break;
 }
 return tr("Warrant \"%2\" in use, currently %1.").arg(modeDesc).arg( getDisplayName());

}

/*protected*/ QString Warrant::getRunningMessage()
{
 if (_delayStart)
 {
  return tr("Wait for %1 to arrive at starting block %3 of warrant %2. ").arg(_trainName).arg(getDisplayName()).arg(getBlockOrderAt(0)->getBlock()->getDisplayName());
 }
 switch (_runMode)
 {
  case Warrant::MODE_NONE:
   if (getOrders()->size()==0)
   {
    return tr("Blank Warrant");
   }
   if (getDccAddress()==nullptr)
   {
    return tr("Locomotive not Assigned.");
   }
   if (getThrottleCommands()->size() == 0)
   {
//                return java.text.MessageFormat.format(
//                    WarrantTableAction.rb.getString("NoCommands"), getDisplayName());
    return tr("Warrant \"%1\" has no throttle commands.").arg(getDisplayName());
   }
   return tr("Idle");
  case Warrant::MODE_LEARN:
    return tr("Learn Mode in Blk %1.").arg(getCurrentBlockOrder()->getBlock()->getDisplayName());
  case Warrant::MODE_RUN:
  {
   if (_engineer==nullptr) {
       return tr("Engineer and throttle Gone");
   }
   int cmdIdx = _engineer->getCurrentCommandIndex()+1;
   if (cmdIdx>=_commands->size()) {
       cmdIdx =_commands->size()-1;
   }
   cmdIdx++;   // display is 1-based
   OBlock* block = getCurrentBlockOrder()->getBlock();
   if ((block->getState() & (OBlock::OCCUPIED | OBlock::UNDETECTED)) == 0) {
       return tr("Train \"%1\" lost occupancy at block \"%2\".").arg(_trainName).arg(block->getDisplayName());
   }
   QString blockName = block->getDisplayName();
   QString speed = getSpeedMessage(_curSpeedType);

   switch (_engineer->getRunState()) {
   case Warrant::RESUME:
       return tr("Restart in block \"%1\" at Cmd #%2.  Resume speed to %3. ").arg(blockName).arg(cmdIdx).arg(speed);

   case Warrant::RETRY:
       return tr("Unprotected move forced into block \"%1\". Resume speed to %3 - Cmd #%2.").arg(blockName).arg(cmdIdx).arg(speed);

   case Warrant::ABORT:
       if (cmdIdx == _commands->size() - 1)
       {
           _engineer = nullptr;
           return tr("End Of Script for train %1.").arg(_trainName);
       }
       return tr("Script aborted in block \"%1\" at Cmd #%2.").arg(blockName).arg(cmdIdx);

   case Warrant::HALT:
   case Warrant::WAIT_FOR_CLEAR:
   {
       QString s = "";
       if (_waitForSignal) {
           s = tr("Signal");
       } else if (_waitForWarrant) {
           Warrant* w = getBlockingWarrant();
           if (w != nullptr) {
               s = tr("Warrant \"%1\"").arg( w->getDisplayName());
           } else {
               s = tr("Waiting in block %1 for %2 to clear ahead.").arg(blockName).arg((_waitForSignal
                       ? tr("Signal") : tr("Occupancy")));
           }
       } else if (_waitForBlock) {
           s = tr("Occupancy");
       } else {
           return tr("Halted in block \"%1\" at Cmd #%2.").arg(blockName).arg(cmdIdx);
       }
       return tr("Train %1 waiting in Block %2 for %3 to clear ahead.").arg(
               getTrainName()).arg(getCurrentBlockName()).arg(s);
   }
   case Warrant::WAIT_FOR_TRAIN:
   {
       int blkIdx = _idxCurrentOrder + 1;
       if (blkIdx >= _orders->size())
       {
           blkIdx = _orders->size() - 1;
       }
       return tr("Overdue for arrival at block %2. Speed %3 - Cmd #%1.").arg(cmdIdx).arg(
               getBlockOrderAt(blkIdx)->getBlock()->getDisplayName()).arg(speed);
   }
   case Warrant::WAIT_FOR_SENSOR:
       return tr("Wait for event sensor %2 in Block %3. Speed %4 - Cmd #%1.").arg(
               cmdIdx).arg(_engineer->getWaitSensor()->getDisplayName(),
               blockName).arg(speed);

   case Warrant::RUNNING:
   case Warrant::SPEED_RESTRICTED:
   case Warrant::RAMPING_UP:
       return tr("Running in Block %1 at speed %3 - Cmd #%2.").arg(blockName).arg(cmdIdx).arg(speed);

   case Warrant::RAMP_HALT:
       return tr("Speed slowing from %1 in block %2 to halt.").arg(speed).arg(blockName);

   case Warrant::STOP_PENDING:
       return tr("Speed slowing from %1 in block %2 for %3 ahead.").arg(speed).arg(blockName).arg((_waitForSignal
               ? tr("Signal") : (_waitForBlock
                       ? tr("Occupancy") : tr("Warrant"))));

   default:
                return _message;
   }
  }
  case Warrant::MODE_MANUAL:
  {
   BlockOrder* bo = getCurrentBlockOrder();
   if (bo!=nullptr)
   {
    return tr("Manual control in Blk %1.").arg(bo->getBlock()->getDisplayName());
   }
   return tr("Manual run");
  }
   default:
   break;
 }
 return "ERROR mode= "+_runMode;
}

/**
 * Calculates the scale speed of the current throttle setting for display
 * @param speedType name of current speed
 * @return text message
 */
/*private*/ QString Warrant::getSpeedMessage(QString speedType) {
    float speed = 0;
    QString units;
    SignalSpeedMap* speedMap = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"));
    switch (speedMap->getInterpretation()) {
        case SignalSpeedMap::PERCENT_NORMAL:
/*                units = Bundle.getMessage("percentNormal");
            if (_idxCurrentOrder == _orders.size() - 1
                    || _engineer.getCurrentCommandIndex() >= _commands.size() - 1) {
                speed = _speedInfo.get(_idxCurrentOrder).getEntranceSpeed();
            } else {
                for (int idx = _engineer.getCurrentCommandIndex(); idx >=0; idx--) {
                    ThrottleSetting ts = _commands.get(idx);
                    if ("SPEED".equals(ts.getCommand().toUpperCase())) {
                        speed = Float.parseFloat(ts.getValue());
                        break;
                    }
                }
            }
            speed = (_engineer.getSpeedSetting() / speed) * 100;
            break;*/
        case SignalSpeedMap::PERCENT_THROTTLE:
            units = tr("% Throttle");
            speed = _engineer->getSpeedSetting() * 100;
            break;
        case SignalSpeedMap::SPEED_MPH:
            units = "Mph";
            speed = _speedUtil->getTrackSpeed(_engineer->getSpeedSetting()) * speedMap->getLayoutScale();
            speed = speed * 2.2369363f;
            break;
        case SignalSpeedMap::SPEED_KMPH:
            units = "Kmph";
            speed = _speedUtil->getTrackSpeed(_engineer->getSpeedSetting()) * speedMap->getLayoutScale();
            speed = speed * 3.6f;
            break;
        default:
            log->error(tr("Unknown speed interpretation %1").arg(speedMap->getInterpretation()));
            throw IllegalArgumentException("Unknown speed interpretation " + QString::number(speedMap->getInterpretation()));
    }
    return tr("%1 (%2%3)").arg(speedType).arg(qRound(speed)).arg(units);
}

/*protected*/ void Warrant::startTracker() {
    TrackerTableAction::markNewTracker(getCurrentBlockOrder()->getBlock(), _trainName);
}

/*public*/ void Warrant::stopWarrant(bool abort)
{
    _delayStart = false;
    if (_stoppingSignal != nullptr) {
        log->error("signal " + _stoppingSignal->getSystemName());
        //_stoppingSignal.removePropertyChangeListener(this);
        AbstractNamedBean* ass = (AbstractNamedBean*)_stoppingSignal;
        disconnect(ass->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        _stoppingSignal = nullptr;
    }
    if (_stoppingBlock != nullptr) {
        //_stoppingBlock.removePropertyChangeListener(this);
     disconnect(_stoppingBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        _stoppingBlock = nullptr;
    }
    if (_shareTOBlock != nullptr) {
        //_shareTOBlock.removePropertyChangeListener(this);
     disconnect(_shareTOBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        _shareTOBlock = nullptr;
    }
    if (_student != nullptr) {
        _student->dispose();     // releases throttle
        _student = nullptr;
    }
//    _calibrater = nullptr;
    if (_engineer != nullptr) {
        if (abort) {
            _engineer->abort();
            log->info(getDisplayName() + " Aborted.");
        }
        _engineer->releaseThrottle();
        _engineer = nullptr;
    }
    deAllocate();
    int oldMode = _runMode;
    _runMode = MODE_NONE;
    firePropertyChange("runMode", oldMode, _runMode);
    if (_debug) {
        log->debug("stopWarrant() " + getDisplayName() + ". prev mode= " + oldMode);
    }
}

/*public*/ int Warrant::getCurrentCommandIndex() {
    if (_engineer!=nullptr) {
        return _engineer->getCurrentCommandIndex();
    }
    return 0;
}

/**
* Sets up recording and playing back throttle commands - also cleans up afterwards.
*  MODE_LEARN and MODE_RUN sessions must end by calling again with MODE_NONE.  It is
* important that the route be deAllocated (remove listeners).
* <p>
* Rule for (auto) MODE_RUN:
* 1. At least the Origin block must be owned (allocated) by this warrant.
* (block._warrant == this)  and path set for Run Mode
* Rule for (auto) LEARN_RUN:
* 2. Entire Route must be allocated and Route Set for Learn Mode.
* i.e. this warrant has listeners on all block sensors in the route.
* Rule for MODE_MANUAL
* The Origin block must be allocated to this warrant and path set for the route
*/
/*public*/ QString Warrant::setRunMode(int mode, DccLocoAddress* address,
                             LearnThrottleFrame* student,
                             QList <ThrottleSetting*>* commands, bool runBlind)
{
 if(_debug) log->debug("setRunMode("+QString::number(mode)+")  _runMode= "+QString::number(_runMode)+" for warrant= "+getDisplayName());
 QString msg = nullptr;
 int oldMode = _runMode;
 if (mode == MODE_NONE)
 {
  _delayStart = false;
  if (_stoppingSignal!=nullptr)
  {
   log->error("signal "+_stoppingSignal->getSystemName());
   //_stoppingSignal.removePropertyChangeListener(this);
   AbstractNamedBean* abstractStoppingSignal = (AbstractNamedBean*)_stoppingSignal;
   disconnect(abstractStoppingSignal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
            _stoppingSignal = nullptr;
  }
  if (_stoppingBlock!=nullptr)
  {
   //_stoppingBlock->removePropertyChangeListener(this);
   disconnect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));

   _stoppingBlock = nullptr;
  }
  if (_student !=nullptr)
  {
   _student->dispose();
            _student = nullptr;
  }
  if (_engineer!=nullptr && _engineer->getRunState() != Warrant::ABORT)
  {
            _engineer->abort();
            _engineer = nullptr;
        }
        deAllocate();
        _runMode = mode;
        _idxCurrentOrder = 0;
        _orders = _savedOrders;
    } else if (_runMode!=MODE_NONE) {
        QString modeDesc = nullptr;
        switch (_runMode) {
            case MODE_LEARN:
                modeDesc = tr("Recording");
                break;
            case MODE_RUN:
                modeDesc = tr("recording an AutoRun script");
                break;
            case MODE_MANUAL:
                modeDesc = tr("train running under Manual control");
                break;
        }
        //msg = java.text.MessageFormat.format(rb.getString("WarrantInUse"), modeDesc);
        msg = tr("Warrant in use, currently %1.").arg(modeDesc);
        log->error(msg);
        return msg;
    } else {
        _delayStart = false;
        if (!_routeSet && runBlind) {
            //msg = java.text.MessageFormat.format(rb.getString("BlindRouteNotSet"),getDisplayName());
            msg = tr("Warrant \"%1\" cannot run without block detection when the route is not completely set.").arg(getDisplayName());
            return nullptr;
        }
        if (mode == MODE_LEARN) {
            // start is OK if block 0 is occupied (or dark - in which case user is responsible)
            if (!runBlind && (getBlockStateAt(0) & (OBlock::OCCUPIED|OBlock::DARK))==0) {
                //msg = java.text.MessageFormat.format(rb.getString("badStart"),getDisplayName());
                msg = tr("Train does not occupy the starting block of Warrant \"%1\".").arg(getDisplayName());
                log->error("Block "+getBlockAt(0)->getDisplayName()+", state= "+getBlockStateAt(0)+" err="+msg);
                return msg;
            } else if (student == nullptr) {
                //msg = java.text.MessageFormat.format(rb.getString("noLearnThrottle"), getDisplayName());
                msg = tr("No learning throttle for \"{0}\" in learning mode.").arg(getDisplayName());
                log->error(msg);
                return msg;
            }
            _student = student;
            _currentSpeed = "Normal";
            _exitSpeed = "Normal";
         } else if (mode == MODE_RUN) {
             if (commands->isEmpty() || commands->size()== 0) {
                 _commands = _throttleCommands;
             } else {
                 _commands = commands;

             }
             // start is OK if block 0 is occupied (or dark - in which case user is responsible)
             if (!runBlind && (getBlockStateAt(0) & (OBlock::OCCUPIED|OBlock::DARK))==0) {
                 // continuing with no occupation of starting block
                 _stoppingBlock = getBlockAt(0);
                 //_stoppingBlock->addPropertyChangeListener(this);
                 connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
                 _delayStart = true;
                 log->info(tr("Abort the run if you cannot guarantee %1\nwill be the first train to occupy %2.").arg(_trainName).arg(_stoppingBlock->getDisplayName()));
             }
         }
        _runMode = mode;	// set mode before callback to notifyThrottleFound is called
        if (mode!=MODE_MANUAL) {
             _tempRunBlind = runBlind;
             if (!_delayStart) {
                 if (address==nullptr) {
                     address = _dccAddress;
                 }
                 msg = acquireThrottle(address);
                 if (msg!=nullptr){
                     return msg;
                 }
             }
        }
    }
    _runMode = mode;
    firePropertyChange("runMode", QVariant(oldMode), QVariant(_runMode));
    if(_debug) log->debug("Exit setRunMode()  _runMode= "+QString::number(_runMode)+", msg= "+msg);
    return msg;
}

/*private*/ QString Warrant::acquireThrottle(DccLocoAddress* address) {
    QString msg = nullptr;
    if (address == nullptr)  {
        //msg = java.text.MessageFormat.format(rb.getString("NoAddress"),getDisplayName());
        msg = tr("Warrant \"%1\" has no train address.").arg(getDisplayName());
        log->error(msg);
        return msg;
    }
    if (InstanceManager::throttleManagerInstance()==nullptr) {
        msg = tr("Throttle Manager not available.");
        log->error(msg);
        return msg;
    }
    if (!((LnThrottleManager*)InstanceManager::throttleManagerInstance())->
        requestThrottle(address->getNumber(), address->isLongAddress(),(ThrottleListener*)this)) {
        //msg = java.text.MessageFormat.format(rb.getString("trainInUse"), address.getNumber());
        msg = tr("Address invalid, (Address %1) or train in use on another throttle.").arg(address->getNumber());
        log->error(msg);
        return msg;
    }
    _delayStart = false;	// script should start - no more delay
    return msg;
}

/**
* Pause and resume auto-running train or abort any allocation state
* _engineer->abort() calls setRunMode(MODE_NONE,...) which calls deallocate all.
*/
/*public*/ bool Warrant::controlRunTrain(int idx) {
    if(_debug) log->debug("controlRunTrain= "+QString::number(idx)+" runMode= "+QString::number(_runMode)+" for warrant= "+getDisplayName());
    bool ret = true;
    int oldIndex = MODE_MANUAL;
    if (_engineer == nullptr) {
        switch (idx) {
            case HALT:
            case RESUME:
                ret = false;
                break;
            case ABORT:
                if (_runMode==Warrant::MODE_LEARN) {
                    // let WarrantFrame do the abort
                    firePropertyChange("abortLearn", QVariant(oldIndex), QVariant(_idxCurrentOrder));
                } else {
                    QString msg = setRunMode(Warrant::MODE_NONE, nullptr, nullptr, nullptr, false);
                }
                break;
        }
    } else {
        /*synchronized(_engineer)*/ {
            oldIndex = _engineer->getRunState();
            switch (idx) {
                case HALT:
                    _engineer->setHalt(true);
                    break;
                case RESUME:
                    _engineer->setHalt(false);
                    break;
                case ABORT:
                    _engineer->abort();
                    break;
            }
        }
    }
    firePropertyChange("controlChange", QVariant(oldIndex), QVariant(idx));
    return ret;
}

/*public*/ void Warrant::notifyThrottleFound(DccThrottle* throttle)
{
    if (throttle == nullptr) {
        log->warn("notifyThrottleFound: nullptr throttle(?)!");
        return;
    }

    if(_debug) {
       log->debug("notifyThrottleFound address= " +((DccLocoAddress*)((LocoNetThrottle*)throttle)->getLocoAddress())->toString()+" _runMode= "+QString::number(_runMode));
    }
    _idxCurrentOrder = 0;

    if (_runMode == MODE_LEARN) {
        _student->notifyThrottleFound(throttle);
    } else {
        getSpeedMap();      // initialize speedMap for getPermissibleEntranceSpeed() calls
        _engineer = new Engineer(this, throttle);
        startupWarrant();
        /*new*/ QThread(_engineer).start();
    }
}

/*protected*/ void Warrant::startupWarrant() {
    _idxCurrentOrder = 0;
    // set block state to show our train occupies the block
    BlockOrder* bo = getBlockOrderAt(0);
    OBlock* b = bo->getBlock();
    b->setValue(_trainName);
    b->setState(b->getState() | OBlock::RUNNING);
    // getNextSpeed() calls allocateNextBlock() who will set _stoppingBlock, if necessary
    // do before starting throttle commands in engineer
    _currentSpeed = getNextSpeed();		// will modify _currentSpeed, if necessary
    _engineer->rampSpeedTo(_currentSpeed, 0);
}

/*public*/ void Warrant::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason) {
    log->error("notifyFailedThrottleRequest address= " +address->toString()+" _runMode= "+QString::number(_runMode)+
            " due to "+reason);
}

/**
* Allocate the current saved blocks of this warrant.
* Installs listeners for the entire route.  Sets this warrant into
* @return error message, if any
*/
/*public*/ QString Warrant::allocateRoute(QList <BlockOrder*>* orders) {
    if (_totalAllocated) {
        return nullptr;
    }
    if (orders==nullptr) {
        _orders = _savedOrders;
    } else {
        _orders = orders;
    }
    _allocated = false;
    _totalAllocated = true;
    OBlock* block = nullptr;
    QString msg = "";
    // Check route is in usable
    for (int i=0; i<_orders->size(); i++) {
        BlockOrder* bo = _orders->at(i);
        block = bo->getBlock();
        if ((block->getState() & OBlock::OUT_OF_SERVICE) !=0) {
            _orders->at(0)->getBlock()->deAllocate(this);
//            msg = java.text.MessageFormat.format(rb.getString("UnableToAllocate"), getDisplayName()) +
//                java.text.MessageFormat.format(rb.getString("BlockOutOfService"),block.getDisplayName());
            msg = tr("Unable to allocate Warrant \"%1\" -").arg(getDisplayName()) + tr("Block \"%1\" is Out Of Service and canot be allocated.").arg(block->getDisplayName());
            _totalAllocated = false;
            break;
        }
    }
    // allocate all possible, report unoccupied blocks - changed 9/30/12
    // Only allocate up to occupied block (if any)
    for (int i=0; i<_orders->size(); i++) {
        BlockOrder* bo = _orders->at(i);
        block = bo->getBlock();
        int state = block->getState();
        msg = block->allocate(this);
        if (msg!=nullptr) {
            _totalAllocated = false;
            break;
        } else {
            _allocated = true;		// partial allocation
        }
        if ((state & OBlock::OCCUPIED) > 0 && this!=(block->getWarrant())) {
//            msg = java.text.MessageFormat.format(rb.getString("BlockRougeOccupied"),
//                    block.getWarrant().getDisplayName(), block.getDisplayName());
            msg = tr("Warrant \"%1\" partially allocated but Block \"%2\" occupied by unknown train.").arg(block->getWarrant()->getDisplayName()).arg(block->getDisplayName());
            _totalAllocated = false;
            break;
        }
    }

    if(_debug) log->debug("allocateRoute for warrant \""+getDisplayName()+"\"  _allocated= "+_allocated);
    firePropertyChange("allocate", QVariant(false), QVariant(_allocated));
   return msg;
}

/**
* Deallocates blocks from the current BlockOrder list
*/
/*public*/ void Warrant::deAllocate()
{
 for (int i=0; i<_orders->size(); i++)
 {
  OBlock* block = _orders->at(i)->getBlock();
  block->deAllocate(this);
 }
 bool old = _allocated;
 _allocated = false;
 _totalAllocated = false;
 _routeSet = false;
 if(_debug) log->debug("deallocated Route for warrant \""+getDisplayName()+"\".");
//        firePropertyChange("deallocate", Boolean.valueOf(old), Boolean.valueOf(false));
//    emit propertyChange(new PropertyChangeEvent(this, "deallocate", old, _allocated));
 firePropertyChange("deallocate", old, _allocated);
}

/**
* Set the route paths and turnouts for the warrant.  Returns the name
* of the first block that failed allocation to this warrant.  When running with
* block detection, only the first block must be allocated and have its path set.
* @param delay - delay in seconds, between setting signals and throwing turnouts
* @param orders - BlockOrder list of route.  If nullptr, use permanent warrant copy.
* @return message of block that failed allocation to this warrant or nullptr
*/
/*public*/ QString Warrant::setRoute(int /*delay*/, QList <BlockOrder*>* /*orders*/)
{
 // we assume our train is occupying the first block
 _routeSet = true;
 QString msg = allocateRoute(_orders);
 OBlock* startBlock = _orders->at(0)->getBlock();
 for (int i=0; i<_orders->size(); i++)
 {
  BlockOrder* bo = _orders->at(i);
  OBlock* block = bo->getBlock();
  if (i!=0 && (block->getState() & OBlock::OCCUPIED)>0 && startBlock!=(block))
  {
//            msg = java.text.MessageFormat.format(rb.getString("BlockRougeOccupied"),
//                            getDisplayName(), block.getDisplayName());
   msg = tr("Warrant \"%1\" partially allocated but Block \"%2\" occupied by unknown train.").arg(getDisplayName()).arg(block->getDisplayName());
   _routeSet = false;  // don't throw switches under a rouge train
   break;
  }
  else
  {
   msg = bo->setPath(this);
   if (msg!=nullptr)
   {
    if (i==0) { _routeSet = false; }
    break;
   }
  }
 }
 firePropertyChange("setRoute", QVariant(false), QVariant(_routeSet));
 if(_debug) log->debug("setRoute for warrant \""+getDisplayName()+"\"  _routeSet= "+(_routeSet?"true":"false"));
 return msg;
}   // setRoute

/**
 * Set the route paths and turnouts for the warrant. Returns the name of the
 * first block that failed allocation to this warrant. When running with
 * block detection, only the first block must be allocated and have its path
 * set.
 *
 * @param delay - delay in seconds, between setting signals and throwing
 * turnouts
 * @param orders - BlockOrder list of route. If NULL, use permanent warrant
 * copy.
 * @return message of block that failed allocation to this warrant or NULL
 */
/*public*/ QString Warrant::setRoute(int delay, QList<BlockOrder*> orders) {
    // we assume our train is occupying the first block
    _routeSet = true;
    _message = allocateRoute(&orders);
    if (_message != nullptr) {
        _routeSet = false;
        return _message;
    }
    _allocated = true;
    _totalAllocated = true;
    BlockOrder* bo = _orders->at(0);
    _message = bo->setPath(this);
    if (_message != nullptr) {
        return _message;
    }
    for (int i = 1; i < _orders->size(); i++) {
        bo = _orders->at(i);
        OBlock* block = bo->getBlock();
        if ((block->getState() & OBlock::OCCUPIED) > 0) {
            _message = tr("route allocated but Block \"%1\" occupied by unknown train.").arg(block->getDisplayName());
            break;
        }
        _message = bo->setPath(this);
        if (_message != nullptr) {
            _routeSet = false;
            break;
        }
    }
//        firePropertyChange("setRoute", Boolean.valueOf(false), Boolean.valueOf(_routeSet));
    if (_message != nullptr) {
        log->info("Paths for route of warrant \"" + getDisplayName() + "\" not set at " + _message);
    }
    return nullptr;
}   // setRoute

/**
 * Check start block for occupied for start of run
 */
/*protected*/ QString Warrant::checkStartBlock() {
    BlockOrder* bo = _orders->at(0);
    OBlock* block = bo->getBlock();
    QString msg = block->allocate(this);
    if (msg!="") {
        return msg;
    }
    msg = bo->setPath(this);
    if (msg!=nullptr) {
        return msg;
    }
    int state = block->getState();
    if ((state & OBlock::DARK) != 0) {
//        msg = java.text.MessageFormat.format(rb.getString("BlockDark"),
//                                            block.getDisplayName());
        msg = tr("Block \"%1\" is dark, cannot guarantee route is set or clear.").arg(block->getDisplayName());
     } else if ((state & OBlock::OCCUPIED) == 0) {
//        msg = java.text.MessageFormat.format(rb.getString("badStart"),
//                                            block.getDisplayName());
        msg = tr("Train does not occupy the starting block of Warrant \"%1\".").arg(block->getDisplayName());
    }
    return msg;
}

/**
 * Check start block for occupied for start of run
 */
/*public*/ QString Warrant::checkStartBlock(int mode)
{
 if(_debug) log->debug("checkStartBlock for warrant \""+getDisplayName()+"\".");
 BlockOrder* bo = _orders->at(0);
 OBlock* block = bo->getBlock();
 QString msg = block->allocate(this);
 if (msg!=nullptr) {
     return msg;
 }
 msg = bo->setPath(this);
 if (msg!=nullptr) {
     return msg;
 }
 int state = block->getState();
 if ((state & OBlock::DARK) != 0 || _tempRunBlind) {
     msg = tr("Block \"%1\" is dark or running without block protection, cannot guarantee route is clear.").arg( block->getDisplayName());
 } else if ((state & OBlock::OCCUPIED) == 0) {
     if (mode==MODE_LEARN) {
      msg = tr("Train %1 does not occupy the starting block, %2.").arg(getTrainName()).arg(block->getDisplayName());
     } else{
         msg = tr("Abort the run if you cannot guarantee %1\nwill be the first train to occupy %2.").arg(getTrainName()).arg(block->getDisplayName());
     }
     //msg = tr(msg, getTrainName(), block->getDisplayName());
 } else {
     // check if tracker is on this train
     TrackerTableAction::stopTrackerIn(block);
 }
 return msg;
}

/**
 * Report any occupied blocks in the route
 */
/*public*/ QString Warrant::checkRoute() {
    QString msg ="";
    OBlock* startBlock = _orders->at(0)->getBlock();
    for (int i=1; i<_orders->size(); i++) {
        OBlock* block = _orders->at(i)->getBlock();
        if ((block->getState() & OBlock::OCCUPIED)>0 && startBlock!=(block)) {
//            msg = java.text.MessageFormat.format(rb.getString("BlockRougeOccupied"),
//                    getDisplayName(), block.getDisplayName());
            msg= tr("\"%1\" partially allocated but Block \"%2\" occupied by unknown train.").arg(getDisplayName()).arg(block->getDisplayName());
            _totalAllocated = false;
        }
    }
    return msg;
}
/*public*/ QString Warrant::checkForContinuation() {
    Warrant* w = getfirstOrder()->getBlock()->getWarrant();
    if (this==(w)) {
        return nullptr;
    }
    // another warrant has the starting block
    if (w->getLastOrder()->getBlock()==(getfirstOrder()->getBlock())
            && _dccAddress==(w->getDccAddress()) ) {
        return nullptr;
    }
    //return java.text.MessageFormat.format(rb.getString("OriginBlockNotSet"), w.getDisplayName());
    return tr("Unable to allocate originating block.\n\"%1\".").arg(w->getDisplayName());
}

/*public*/ void Warrant::propertyChange(PropertyChangeEvent* evt) {
    //if (!(evt->getSource() instanceof NamedBean))
    if(qobject_cast<NamedBean*>(evt->getSource())!= 0)
    {
//            if (_debug) log->debug("propertyChange \""+evt.getPropertyName()+
//                                                "\" old= "+evt.getOldValue()+" new= "+evt.getNewValue());
        return;
    }
    QString property = evt->getPropertyName();
    QString msg = nullptr;
    if (_debug) log->debug("propertyChange \""+property+"\" new= "+evt->getNewValue().toString()+
                                        " source= "+((NamedBean*)evt->getSource())->getDisplayName()
                                        +" for warrant= "+getDisplayName());
    if (_stoppingSignal != nullptr && _stoppingSignal==evt->getSource()) {
        if (property==("Aspect") || property==("Appearance")) {
            // signal blocking warrant has changed. Should (MUST) be the next block.
            //_stoppingSignal.removePropertyChangeListener(this);
            AbstractNamedBean* signal = (AbstractNamedBean*)_stoppingSignal;
            disconnect(signal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            _stoppingSignal = nullptr;
            if (_engineer!=nullptr) {
                _engineer->synchNotify(getBlockAt(_idxCurrentOrder)); // notify engineer of control point
                _engineer->rampSpeedTo(getCurrentSpeedAt(_idxCurrentOrder) ,0);
            }
            return;
        }
    } else if (property==("state") && _stoppingBlock!=nullptr && _stoppingBlock==evt->getSource()) {
        // starting block is allocated but not occupied
        if (_delayStart) {	// wait for arrival of train to begin the run
            if ( ((evt->getNewValue()).toInt() & OBlock::OCCUPIED) != 0 ) {
                // train arrived at starting block
                Warrant* w = _stoppingBlock->getWarrant();
                if (this==(w) || w==nullptr) {
                    if (checkStoppingBlock()) {
                        msg = acquireThrottle(_dccAddress);
                        if (msg!=nullptr){
                            log->error("Abort warrant \""+ getDisplayName()+"\" "+msg);
                            if (_engineer!=nullptr) {
                                _engineer->abort();
                            }
                        }
                    }
                } else {
                    // starting block allocated to another warrant for the same engine
                    // which has just arrived at the starting block for this warrant
                    // However, we must wait for the other warrant to finish
                    //w->addPropertyChangeListener(this);
                    connect(w,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
                }
            }
        } else if (((evt->getNewValue()).toInt() & OBlock::UNOCCUPIED) != 0) {
            // normal wait for a train underway but blocked ahead by occupation
            //  blocking occupation has left the stopping block
            if (checkStoppingBlock()) {
            }
        }
    } else if (_delayStart && property==("runMode") &&
                        (evt->getNewValue()).toInt()==MODE_NONE)  {
        // Starting block was owned by another warrant for this engine
        // Engine has arrived and Blocking Warrant has finished
        Warrant* w = (Warrant*)evt->getSource();
        //((Warrant*)evt->getSource()).removePropertyChangeListener(this);
        disconnect(w,SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
        if (checkStoppingBlock()) {
            msg = acquireThrottle(_dccAddress);
            if (msg!=nullptr) {
                log->error("Abort warrant \""+ getDisplayName()+"\" "+msg);
                if (_engineer!=nullptr) {
                    _engineer->abort();
                }
            }
        }
    }
    if (msg!=nullptr) {
        log->error(msg);
    }
 }

/*private*/ bool Warrant::checkStoppingBlock() {
    //_stoppingBlock->removePropertyChangeListener(this);
    disconnect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
    QString msg = _stoppingBlock->allocate(this);
    if (_debug) log->debug("checkStoppingBlock for _stoppingBlock= "+_stoppingBlock->getDisplayName()+
            " allocate msg= "+msg);
    if (msg=="") {
        int idx = getIndexOfBlock(_stoppingBlock, 0);
        msg = _orders->at(idx)->setPath(this);
        if (msg!=nullptr) {
            log->warn("StoppingBlock path warrant \""+ getDisplayName()+"\" "+msg);
        } else {
            if (idx==_idxCurrentOrder) {
                _stoppingBlock->setValue(_trainName);
                _stoppingBlock->setState(_stoppingBlock->getState() | OBlock::RUNNING);
            }
            if (_engineer!=nullptr) {
                _engineer->synchNotify(_stoppingBlock); // notify engineer of control point
                _engineer->rampSpeedTo(getNextSpeed(), 0);

            } else {
                _stoppingBlock = nullptr;
            }
             return true;
        }
 }
 else
 {
        // allocation failed, continue to wait
        //_stoppingBlock->addPropertyChangeListener(this);
  connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
 }
 return false;
}

/**
 * block (nextBlock) sharing a turnout with _shareTOBlock is already
 * allocated.
 */
/*private*/ void Warrant::checkShareTOBlock()
{
 _shareTOBlock->removePropertyChangeListener((PropertyChangeListener*)this);

 if (_debug) log->debug("_shareTOBlock= "+_shareTOBlock->getDisplayName()+" Cleared.");
 _shareTOBlock = nullptr;
 QString msg = _orders->at(_idxCurrentOrder+1)->setPath(this);
 if (msg=="")
 {
  restart();
  moveIntoNextBlock(END);
 }
 else
 {
  // another block is sharing a turnout. and is set by callback
  log->info("Warrant \"" + getDisplayName() + "\" shares a turnout. " + msg);
 }
}

/**
 * Callback from trying to setPath() for this warrant. This warrant's Oblock
 * notices that another warrant has its path set and uses a turnout also
 * used by the current path of this. Rights to the turnout must be
 * negotiated, otherwise warrants will deadlock.
 *
 * @param block of other warrant that has a path set
 */
/*protected*/ void Warrant::setShareTOBlock(OBlock* block)
{
 if (_debug) {
     log->debug("Warrant " + getDisplayName() + " setShareTOBlock for block= "
             + block->getDisplayName() + ". current block= " + getBlockAt(_idxCurrentOrder)->getDisplayName());
 }
 _shareTOBlock = block;
 _shareTOBlock->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(_shareTOBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT());
 log->info("Warrant \"" + getDisplayName() + "\" sets _shareTOBlock= \""
         + _shareTOBlock->getDisplayName() + "\". current block= " + getBlockAt(_idxCurrentOrder)->getDisplayName());
}

/**
 * Stopping block only used in MODE_RUN _stoppingBlock is an occupied OBlock
 * preventing the train from continuing the route
 *
 * @param block
 */
/*private*/ void Warrant::setStoppingBlock(OBlock* block) {
    if (_runMode != MODE_RUN) {
        return;
    }
    _stoppingBlock = block;
    _stoppingBlock->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(_stoppingBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT());
    log->info("Warrant \"" + getDisplayName() + "\" sets _stoppingBlock= \""
            + _stoppingBlock->getDisplayName() + "\"");
}

/**
* Block in the route is going active.
* check if this is the next block of the train moving under the warrant
* Learn mode assumes route is set and clear
*/
/*protected*/ void Warrant::goingActive(OBlock* block) {
    if (_runMode==MODE_NONE) {
        return;
    }
    int oldIndex = _idxCurrentOrder;
    int activeIdx = getIndexOfBlock(block, _idxCurrentOrder);
    bool rougeEntry = false;
    if (_debug) log->debug("Block "+block->getDisplayName()+" goingActive. activeIdx= "+
                                        QString::number(activeIdx)+", _idxCurrentOrder= "+QString::number(_idxCurrentOrder)+
                                        " _orders->size()= "+QString::number(_orders->size())
                                        +" for warrant= "+getDisplayName());
    if (activeIdx<=0) {
        // Not found or starting block, in which case 0 is handled as the _stoppingBlock
        return;
    }
    // skip over dark blocks
    if ((getBlockAt(_idxCurrentOrder)->getState() & OBlock::DARK) > 0) {
        firePropertyChange("blockChange", QVariant(_idxCurrentOrder), QVariant(_idxCurrentOrder+1));
    }
    if (activeIdx == _idxCurrentOrder+1) {
        if (_engineer!=nullptr && _engineer->getRunState()==WAIT_FOR_CLEAR) {
            // Ordinarily block just occupied would be this train, but train is stopped! - must be a rouge entry.
            rougeEntry = true;
            log->warn("Rouge entering next Block "+block->getDisplayName());
        } else {
            if (_debug) log->debug("Train entering Block "+block->getDisplayName()
                                        +" for warrant= "+getDisplayName());
            // we assume it is our train entering the block - cannot guarantee it, but what else?
            _idxCurrentOrder = activeIdx;
            // set block state to show our train occupies the block
            block->setValue(_trainName);
            block->setState(block->getState() | OBlock::RUNNING);
        }
    } else if (activeIdx > _idxCurrentOrder+1) {
        // rouge train invaded route ahead.
        rougeEntry = true;
    } else if (_idxCurrentOrder > 0) {
        log->error("activeIdx ("+QString::number(activeIdx)+") < _idxCurrentOrder ("+QString::number(_idxCurrentOrder)+")!");
    }

    if (rougeEntry) {
        log->warn("Rouge train ahead at block \""+block->getDisplayName()+"\"!");
    }

    QString currentSpeed = "Stop";
    if (_idxCurrentOrder == _orders->size()-1) {
        // must be in destination block, No 'next block' for last BlockOrder
        // If Auto running, let script finish according to recorded times.
        // End of script will deallocate warrant.
        currentSpeed = getCurrentSpeedAt(_idxCurrentOrder);
        if (_engineer!=nullptr) {
            _engineer->synchNotify(block); // notify engineer of control point
            _engineer->rampSpeedTo(currentSpeed, 0);
        }

        if (_runMode==MODE_MANUAL) {
            QString msg = setRunMode(Warrant::MODE_NONE, nullptr, nullptr, nullptr, false);
            if (msg!=nullptr) {
                deAllocate();
            }
        }
    } else {
        if (allocateNextBlock(getBlockAt(_idxCurrentOrder+1))) {
            currentSpeed = getNextSpeed();
        }
        if (_engineer!=nullptr) {
            _engineer->synchNotify(block); // notify engineer of control point
            _engineer->rampSpeedTo(currentSpeed, 0);
        }

        if (_idxCurrentOrder==activeIdx && (_runMode==MODE_LEARN || _tempRunBlind)) {
            // recording must done with signals and occupancy clear.
            if (currentSpeed==("Stop")) {
                firePropertyChange("abortLearn", QVariant(oldIndex), QVariant(_idxCurrentOrder));
            }
        }

        // attempt to allocate remaining blocks in the route up to next occupation
        for (int i=_idxCurrentOrder+2; i<_orders->size(); i++) {
            BlockOrder* bo = _orders->at(i);
            OBlock* b = bo->getBlock();
            b->allocate(this);
            bo->setPath(this);
            if (i!=0 && (b->getState() & OBlock::OCCUPIED) > 0) {
                 break;
            }
       }
    }

    if (_idxCurrentOrder==activeIdx) {
        // fire notification last so engineer's state can be documented in whatever GUI is listening.
        firePropertyChange("blockChange", QVariant(oldIndex), QVariant(_idxCurrentOrder));
    }
}

/**
* Block in the route is going Inactive
*/
/*protected*/ void Warrant::goingInactive(OBlock* block) {
    if (_runMode==MODE_NONE)  { return; }

    int idx = getIndexOfBlock(block, 0);  // if idx >= 0, it is in this warrant
    if (_debug) log->debug("Block "+block->getDisplayName()+" goingInactive. idx= "+
                                        QString::number(idx)+", _idxCurrentOrder= "+QString::number(_idxCurrentOrder)
                                        +" for warrant= "+getDisplayName());
    if (idx < _idxCurrentOrder) {
        // block is behind train.  Assume we have left.
        // block.deAllocate(this);
        for (int i=idx; i>-1; i--) {
            OBlock* prevBlock = getBlockAt(i);
            if ((prevBlock->getState() & OBlock::DARK) > 0) {
                prevBlock->deAllocate(this);
            }
        }
    } else if (idx==_idxCurrentOrder) {
        // Train not visible if current block goes inactive
        // skip over dark blocks
        OBlock* nextBlock = getBlockAt(_idxCurrentOrder+1);
        while (_idxCurrentOrder+1 < _orders->size() && (nextBlock->getState() & OBlock::DARK) > 0) {
            block->setValue(QVariant());
            block->deAllocate(this);
            int oldIndex = _idxCurrentOrder;
            _idxCurrentOrder++;
            firePropertyChange("blockChange", QVariant(oldIndex), QVariant(_idxCurrentOrder));
            block = nextBlock;
            nextBlock = getBlockAt(_idxCurrentOrder+1);
        }
        if (_runMode==MODE_RUN || _runMode==MODE_MANUAL) {
            //  at last block
            if (_engineer!=nullptr) {
                block->setValue(_trainName);
                block->setState(block->getState() | OBlock::RUNNING);
                _engineer->synchNotify(block); // notify engineer of control point
                _engineer->rampSpeedTo(getCurrentSpeedAt(_idxCurrentOrder), 0);
            } else if (_idxCurrentOrder+1 == _orders->size()){
                // this would be a very weird case
                setRunMode(Warrant::MODE_NONE, nullptr, nullptr, nullptr, false);
            }
       }
    } else if (idx==_idxCurrentOrder+1) {
        // Assume Rouge train has left this block
        // Since it is the next block ahead of the train, we can move.
        // Presumably we have stopped at the exit of the current block.
        if (_runMode==MODE_RUN) {
            if (_engineer!=nullptr && allocateNextBlock(block)) {
                _engineer->synchNotify(block); // notify engineer of control point
                _engineer->rampSpeedTo(getCurrentSpeedAt(_idxCurrentOrder+1), 0);
            }
        }
    } else {
        // Assume Rouge train has left this block
        block->allocate(this);
    }
}
// called when stopping or signal listeners fire.  Also error condition restarts
/*private*/ void Warrant::restart()
{
 if (_engineer==nullptr)
 {
     controlRunTrain(ABORT);
     return;
 }
 BlockOrder* bo = getBlockOrderAt(_idxCurrentOrder);
//        enterBlock(bo.getBlock().getState());
 if (_stoppingBlock==nullptr && _stoppingSignal==nullptr && _shareTOBlock==nullptr)
 {
  if (_engineer!=nullptr)
  {
   _engineer->setWaitforClear(false);
  }
 }

 // check signal
 QString nextSpeed = getPermissibleSpeedAt(bo);
 // does next block belong to us
 bo = getBlockOrderAt(_idxCurrentOrder+1);
 QString nextNextSpeed;
 if (bo!=nullptr)
 {
  if (!allocateNextBlock(bo))
  {
   nextSpeed = Stop;
  }
  nextNextSpeed = getPermissibleSpeedAt(bo);
 } else {    // at last block
     nextNextSpeed = _curSpeedType;
 }
 nextSpeed = _engineer->minSpeedType(nextSpeed, _curSpeedType);
 nextSpeed = _engineer->minSpeedType(nextSpeed, nextNextSpeed);
 if(_debug) log->debug("restart: at speed= "+nextSpeed+" CurrentSpeed= "+_curSpeedType);
 _engineer->rampSpeedTo(nextSpeed);
}

// utility for moveIntoNextBlock()
/*private*/ float Warrant::getLength(BlockOrder* blkOrder) {
    float len = blkOrder->getPath()->getLengthMm();
    if (len <= 0) {
        //a rampLen guess - half throttle for 7 sec.
        len = _engineer->getDistanceTraveled(0.5f, Normal, 7000);
    }
    return len;
}

// utility for moveIntoNextBlock()
/*private*/ QString Warrant::getMinSpeedType(BlockOrder* blkOrder, QString nextSpeedType)
{
 QString speedType;
 if (!allocateNextBlock(blkOrder))
 {
     // next block occupied. stop before entering
     speedType = Stop;
 } else {
     // speed type for entering next block
     speedType = getPermissibleSpeedAt(blkOrder);
     speedType = _engineer->minSpeedType(nextSpeedType, speedType);
 }
 if (speedType=="") {
     speedType = _curSpeedType;
 }
 return speedType;
}

/**
 *  if next block is allocated, set the path. If there are no
 * occupation problems get the permitted speed from the signals and make
 * the speed change.  Call assumes train is capable of movement.
 * Called from goingActive() when train is confirmed as entering nextBlock
 * Called from controlRunTrain() from "resume" command
 * Looks ahead for a speed change.
 * Notifies Engineer of speed to run
 * Block is at the _idxCurrentOrder
 * @param position - estimate of train's position in block at _idxCurrentOrder
 * @return true if a speed change is requested
 */
/*private*/ bool Warrant::moveIntoNextBlock(int position) {
    if (_runMode != Warrant::MODE_RUN || _idxCurrentOrder==_orders->size()-1) {
        return true;
    }
    if (_engineer==nullptr) {
        controlRunTrain(ABORT);
        return false;
    }
    BlockOrder* blkOrder = getBlockOrderAt(_idxCurrentOrder);
    OBlock* curBlock = blkOrder->getBlock();
    // verify we occupy current block
    if ((curBlock->getState() & (OBlock::OCCUPIED | OBlock::DARK))==0 && !_tempRunBlind)
    {
     _engineer->setHalt(true);        // immediate setspeed = 0
     // should not happen, but...what if...
     log->error("checkCurrentBlock, block \""+curBlock->getDisplayName()+"\" not occupied! warrant "+getDisplayName());
     return true;
    }
    // An estimate for how far to look ahead for a possible speed change
    float availDist;
    float curLen = getLength(blkOrder);
    BlockSpeedInfo* blkSpeedInfo = _speedTimeMap.value(curBlock->getDisplayName());
    float maxSpeed = blkSpeedInfo->getMaxSpeed();
    switch (position) {
        case BEG:      // entering a new block
            availDist = curLen;
//                enterBlock(curBlock.getState());
            break;
        case MID:      // halted or startup
            availDist = curLen/2;
            break;
        case END:      // stopped for signal or occupancy
            availDist = curLen/20;
            break;
        default:
            availDist = 0.0f;
    }
    // speed type for entering current block
    QString nextSpeedType = getPermissibleSpeedAt(blkOrder);
    // look ahead to next block. Get slowest type compared to current type
    blkOrder = getBlockOrderAt(_idxCurrentOrder+1);
    nextSpeedType = getMinSpeedType(blkOrder, nextSpeedType);

    if(_debug) log->debug("moveIntoNextBlock("+QString::number(position)+"): \""+curBlock->getDisplayName()+
            "\" availDist= "+QString::number(availDist)+" _curSpeedType= "+_curSpeedType+". Change to speedType= "+nextSpeedType);

    // need to know exit speed of previous block for an immediate speed change
    // otherwise need to know some(?) speed of this block when speed is to be changed

    if (_curSpeedType!=(nextSpeedType)) {

        if (_engineer->secondGreaterThanFirst(_curSpeedType, nextSpeedType) || position==END) {
            if(_debug) log->debug("Immediate Speed change from "+_curSpeedType+" to "+nextSpeedType+
                    "in \""+curBlock->getDisplayName()+"\"");
            _engineer->rampSpeedTo(nextSpeedType);   // should be increase speed
            _idxSpeedChange = _idxCurrentOrder;
            return true;
        } else if (_idxSpeedChange < _idxCurrentOrder) {
            // first estimate of distance needed for ramp
            float distAdj =  blkOrder->getEntranceSpace();
            float lookAheadLen = _engineer->rampLengthForSpeedChange(maxSpeed, _curSpeedType, nextSpeedType) + distAdj;
            if(_debug) log->debug("Change speed for \""+blkOrder->getBlock()->getDisplayName()+
                    "\" with maxSpeed= "+QString::number(maxSpeed)+",  available distance= "+QString::number(availDist)+", lookAheadLen= "+QString::number(lookAheadLen));

            // Revise lookAheadLen estimate to get a more accurate waitTime, if possible
            float speed = blkSpeedInfo->getEntranceSpeed();
            float waitSpeed = _engineer->modifySpeed(speed, _curSpeedType);
            float timeRatio;
            if (_curSpeedType!=(Normal)) {
                timeRatio = speed/waitSpeed;
            } else {
                timeRatio = 1.0f;
            }
            long waitTime = 0;
            long speedTime = 0;     // time running at a given speed
            bool hasSpeed = (speed>0.0001f);
            float dist = availDist;
            float rampLen = 0.0f;
            int startIdx = blkSpeedInfo->getFirstIndex();
            int endIdx = blkSpeedInfo->getLastIndex();
            for (int i=startIdx; i<endIdx; i++) {
                ThrottleSetting* ts = _commands->at(i);
                QString cmd = ts->getCommand().toUpper();
                if (hasSpeed) {
                    speedTime += ts->getTime()*timeRatio;
                } else if (dist>=rampLen && cmd!=("NOOP")) {
                    waitTime += ts->getTime()*timeRatio;
                }
                if (cmd==("SPEED")) {
                 float nextSpeed = (ts->getValue().toFloat());
                    if (hasSpeed) { // get distance for previous speed
                        // available distance left at this speed change point
                        dist -= _engineer->getDistanceTraveled(speed, _curSpeedType, speedTime);
                        rampLen = _engineer->rampLengthForSpeedChange(speed, _curSpeedType, nextSpeedType)+distAdj;
                        if (dist>=rampLen) {
                            lookAheadLen = rampLen;
                            availDist = dist;
                            waitSpeed = _engineer->modifySpeed(speed, _curSpeedType);
                            waitTime += speedTime;
                        }
                    }
                    speed = _engineer->modifySpeed(nextSpeed, _curSpeedType);
                    if (_curSpeedType!=(Normal)) {
                        timeRatio = nextSpeed/speed;
                    } else {
                        timeRatio = 1.0f;
                    }
                    speed = nextSpeed;
                    hasSpeed = (speed>0.0001f);
                    speedTime = 0;
                }
            }
            waitTime += _engineer->getTimeForDistance(waitSpeed, availDist-lookAheadLen);

            if(_debug) log->debug("waitSpeed= "+QString::number(waitSpeed)+", waitTime= "+QString::number(waitTime)+",  available distance= "+QString::number(availDist)+",lookAheadLen= "+QString::number(lookAheadLen));
            if (availDist<=lookAheadLen) {
                if(_debug) log->debug("!!Immediate Speed decrease!! from "+_curSpeedType+" to "+nextSpeedType+
                        " in \""+curBlock->getDisplayName()+"\"");
                _engineer->rampSpeedTo(nextSpeedType);
                _engineer->setCurrentCommandIndex(blkSpeedInfo->getLastIndex());
                _idxSpeedChange = _idxCurrentOrder;
                return true;
            }
            CommandDelay* worker = new CommandDelay(nextSpeedType, waitTime, blkSpeedInfo->getLastIndex(), this);
            //new Thread(thread).start();
            QThread* thread = new QThread();
            connect(thread, SIGNAL(started()), worker, SLOT(process()));
            connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
            connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            thread->start();
            _idxSpeedChange = _idxCurrentOrder;
            return true;
        }
    } else {
        // do following blocks need help for their speed change
        int index = _idxCurrentOrder+1;
        float len = getLength(blkOrder);

        blkSpeedInfo = _speedTimeMap.value(blkOrder->getBlock()->getDisplayName());
        maxSpeed = blkSpeedInfo->getMaxSpeed();
        nextSpeedType = getPermissibleSpeedAt(blkOrder);
        BlockOrder* nextBlkOrder = getBlockOrderAt(index+1);
        if (nextBlkOrder!=nullptr) {
            nextSpeedType = getMinSpeedType(nextBlkOrder, nextSpeedType);

            float distAdj =  nextBlkOrder->getEntranceSpace();
            float lookAheadLen = _engineer->rampLengthForSpeedChange(maxSpeed, _curSpeedType, nextSpeedType)+distAdj;

            if (len<lookAheadLen && _curSpeedType!=(nextSpeedType)) {
                availDist += len;
                if (_engineer->secondGreaterThanFirst(_curSpeedType, nextSpeedType)) {
                    if(_debug) log->debug("Speed increase noted ahead from "+_curSpeedType+" to "+nextSpeedType+
                            " in \""+blkOrder->getBlock()->getDisplayName()+"\" from "+curBlock->getDisplayName());
                    return false;
                } else if (_idxSpeedChange < _idxCurrentOrder) {
                    // first estimate of distance needed for ramp
                    if(_debug) log->debug("Change speed for \""+nextBlkOrder->getBlock()->getDisplayName()+
                            "\" with maxSpeed= "+QString::number(maxSpeed)+",  available distance= "+QString::number(availDist)+", lookAheadLen= "+QString::number(lookAheadLen));

                    BlockSpeedInfo* nextBlkSpeedInfo = _speedTimeMap.value(blkOrder->getBlock()->getDisplayName());
                    // Revise lookAheadLen estimate to get a more accurate waitTime, if possible
                    float speed = blkSpeedInfo->getEntranceSpeed();
                    float waitSpeed = _engineer->modifySpeed(speed, _curSpeedType);
                    float timeRatio;
                    if (_curSpeedType!=(Normal)) {
                        timeRatio = speed/waitSpeed;
                    } else {
                        timeRatio = 1.0f;
                    }
                    long waitTime = 0;
                    long speedTime = 0;     // time running at a given speed
                    bool hasSpeed = (speed>0.0001f);
                    float dist = availDist;
                    float rampLen = 0.0f;
                    int startIdx = blkSpeedInfo->getFirstIndex();
                    int endIdx = blkSpeedInfo->getLastIndex();
                    for (int i=startIdx; i<endIdx; i++) {
                        ThrottleSetting* ts = _commands->at(i);
                        QString cmd = ts->getCommand().toUpper();
                        if (hasSpeed) {
                            speedTime += ts->getTime()*timeRatio;
                        } else if (dist>=rampLen && cmd!=("NOOP")) {
                            waitTime += ts->getTime()*timeRatio;
                        }
                        if (cmd==("SPEED"))
                        {
                            float nextSpeed = (ts->getValue().toFloat());
                            if (hasSpeed) { // get distance for previous speed
                                // available distance left at this speed change point
                                dist -= _engineer->getDistanceTraveled(speed, _curSpeedType, speedTime);
                                rampLen = _engineer->rampLengthForSpeedChange(speed, _curSpeedType, nextSpeedType)+distAdj;
                                if (dist>=rampLen) {
                                    lookAheadLen = rampLen;
                                    availDist = dist;
                                    waitSpeed = _engineer->modifySpeed(speed, _curSpeedType);
                                    waitTime += speedTime;
                                }
                            }
                            speed = _engineer->modifySpeed(nextSpeed, _curSpeedType);
                            if (_curSpeedType!=(Normal)) {
                                timeRatio = nextSpeed/speed;
                            } else {
                                timeRatio = 1.0f;
                            }
                            speed = nextSpeed;
                            hasSpeed = (speed>0.0001f);
                            speedTime = 0;
                        }
                    }
                    waitTime += _engineer->getTimeForDistance(waitSpeed, availDist-lookAheadLen);

                    if(_debug) log->debug("waitSpeed= "+QString::number(waitSpeed)+", waitTime= "+QString::number(waitTime)+",  available distance= "+QString::number(availDist)+",lookAheadLen= "+QString::number(lookAheadLen));
                    if (availDist<=lookAheadLen) {
                        if(_debug) log->debug("!!Immediate Speed decrease!! from "+_curSpeedType+" to "+nextSpeedType+
                                " in \""+curBlock->getDisplayName()+"\"");
                        _engineer->rampSpeedTo(nextSpeedType);
                        _engineer->setCurrentCommandIndex(nextBlkSpeedInfo->getLastIndex());
                        _idxSpeedChange = index;
                        return true;
                    }
                    CommandDelay* worker = new CommandDelay(nextSpeedType, waitTime, nextBlkSpeedInfo->getLastIndex(),this);
                    //new Thread(thread).start();
                    QThread* thread = new QThread();
                    connect(thread, SIGNAL(started()), worker, SLOT(process()));
                    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
                    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
                    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
                    thread->start();
                    _idxSpeedChange = index;
                    return true;
                }
            }

        }
    }
    if(_debug) log->debug("moveIntoNextBlock with no speed change from block \""+
            curBlock->getDisplayName()+"\" - Warrant "+getDisplayName());

    return false;
}

/**
 * build map of BlockSpeedInfo's for the route.
 *
 * @return max speed and time in block's first occurrence after current command index
 */
/*private*/ void Warrant::getBlockSpeedTimes() {
    _speedTimeMap =   QMap<QString, BlockSpeedInfo*>();
    QString blkName = nullptr;
    float firstSpeed = 0.0f;    // used for entrance
    float maxSpeed = 0.0f;
    float lastSpeed = 0.0f;
    long blkTime = 0;
    int firstIdx = 0;
    bool hasSpeedChange = false;
    for (int i=0; i<_commands->size(); i++) {
        ThrottleSetting* ts = _commands->at(i);
        QString cmd = ts->getCommand().toUpper();
        if (cmd==("NOOP")) {
            // make map entry
            blkTime += ts->getTime();
            _speedTimeMap.insert(blkName, new BlockSpeedInfo(firstSpeed, maxSpeed, lastSpeed, blkTime, firstIdx, i));
            if(_debug) log->debug("block: "+blkName+" entrance= "+QString::number(firstSpeed)+" max= "+QString::number(maxSpeed)+" exit= "+
                    QString::number(lastSpeed)+" time= "+QString::number(blkTime)+" from "+QString::number(firstIdx)+" to "+QString::number(i));
            blkName = ts->getBeanDisplayName();
            blkTime = 0;
            firstSpeed = lastSpeed;
            maxSpeed = lastSpeed;
            hasSpeedChange = false;
            firstIdx = i;
        } else {        // collect block info
            blkName = ts->getBeanDisplayName();
            blkTime += ts->getTime();
            if (cmd==("SPEED")) {
                lastSpeed = (ts->getValue().toFloat());
                if (hasSpeedChange) {
                    if (lastSpeed>maxSpeed) {
                        maxSpeed = lastSpeed;
                    }
                } else {
                    hasSpeedChange = true;
                }
            }
        }
    }
    _speedTimeMap.insert(blkName, new BlockSpeedInfo(firstSpeed, maxSpeed, lastSpeed, blkTime, firstIdx, _commands->size()-1));
    if(_debug) log->debug("block: "+blkName+" entrance= "+QString::number(firstSpeed)+" max= "+QString::number(maxSpeed)+" exit= "+QString::number(lastSpeed)+
            " time= "+QString::number(blkTime)+" from "+QString::number(firstIdx)+" to "+QString::number(_commands->size()-1));
}
/**
 * Set a delay on when the speed change for a signal should occur.
 * @param index
 * @return
 */
/*private*/ long Warrant::getSpeedChangeWait(int index) {
    BlockOrder* bo = getBlockOrderAt(index);
    return bo->getEntranceSpeedChangeWait();
}

/**
 * Warrant already owns the block, get permissible speed from
 * the signals.
 * Called by:
 * 	propertyChange -when _stoppingSignal clears
 * 	goingActive -when at current block
 * 	goingInactive -when next block clears from rouge train or at last block
 * @param index
 * @return
 */
/*private*/ QString Warrant::getCurrentSpeedAt(int index) {
    if (index==0) {
        index++;	//use entrance speed of next block for starting up
    }
    BlockOrder* bo = getBlockOrderAt(index);
    bo->setPath(this);
    QString speed = bo->getPermissibleEntranceSpeed();
    QString exitSpeed = bo->getPermissibleExitSpeed();
    long speedOffset = 1000*getSpeedChangeWait(_idxCurrentOrder);
    if (speed!=nullptr) {
        // speed change from signals
        if (speed==("Stop")) {
            _stoppingSignal = bo->getSignal();
            //_stoppingSignal.addPropertyChangeListener(this);
            connect(_stoppingSignal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
        }
        if(_debug) log->debug("signal indicates \""+speed+"\" entrance speed and \""+exitSpeed+
                "\" exit speed on Warrant \""+getDisplayName()+
                "\".\n Set speed change Delay to "+speedOffset+"ms for entrance into "+
                getBlockOrderAt(index)->getBlock()->getDisplayName()+
                (_stoppingSignal==nullptr ? ".": " _stoppingSignal= \""+_stoppingSignal->getDisplayName()+"\""));
    } else {
        if (_exitSpeed!=nullptr) {
            // saved exit speed from last block
            speed = _exitSpeed;
        } else {
            // continue as before
            speed = _currentSpeed;
        }
    }
    _exitSpeed = exitSpeed;
    if(_debug) log->debug("getCurrentSpeedAt("+QString::number(index)+"): speed= \""+speed+"\" for warrant= "+getDisplayName());
    return speed;
}

/**
 * If block cannot be allocated, will set a listener on the block.
 * @param block is the next block from some current location
 * @return
 */
/*private*/ bool Warrant::allocateNextBlock(OBlock* block) {
    if (block==nullptr) {
        return false;
    }
    QString blockMsg = block->allocate(this);
    if ( blockMsg != nullptr || (block->getState() & OBlock::OCCUPIED)>0) {
        _stoppingBlock = block;
        //_stoppingBlock->addPropertyChangeListener(this);
        connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
        log->info((blockMsg!=nullptr ? blockMsg : (block->getDisplayName()+" Occupied."))+" Warrant \""+getDisplayName()+
                "\" sets _stoppingBlock= \""+_stoppingBlock->getDisplayName()+"\"");
        return false;
    }
    return true;
}
/**
 *  Finds speed change in advance of move into the next block.
 *  Called by:
 *      restart()
 *      moveIntoNextBlock() to get max speed permitted
 * @return a speed type or nullptr for continue at current type
 */
/*private*/ QString Warrant::getPermissibleSpeedAt(BlockOrder* bo) {
    OBlock* nextBlock = bo->getBlock();
    QString nextSpeed = bo->getPermissibleEntranceSpeed();
//        String exitSpeed = bo.getPermissibleExitSpeed();
    if (nextSpeed!="" )
    {
        if (nextSpeed==(Stop))
        {
            _stoppingSignal = bo->getSignal();
            _stoppingSignal->addPropertyChangeListener((PropertyChangeListener*)this);
            connect(_stoppingSignal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
    } else {    //  if signal is configured, ignore block
        nextSpeed = nextBlock->getBlockSpeed();
        if (nextSpeed=="") {
         nextSpeed = "";
        }
     }
    /*      or should we do alternate?
    String blkSpeed = nextBlock.getBlockSpeed();
    if (blkSpeed=="") {
        blkSpeed = nullptr;
    }
    nextSpeed = _engineer.minSpeedType(nextSpeed, blkSpeed);
    */
    if(_debug) log->debug("getPermissibleSpeedAt(): \""+nextBlock->getDisplayName()+"\" Speed= "+
                            nextSpeed+" - warrant= "+getDisplayName());
    return nextSpeed;
}
/**
 * If block cannot be allocated, will set a listener on the block.
 * @param block is the next block from some current location
 * @return true if block is allocated to this warrant
 */
/*private*/ bool Warrant::allocateNextBlock(BlockOrder* bo) {
    if (bo == nullptr) {
        log->info("allocateNextBlock: BlockOrder nullptr");
        return false;
    }
    OBlock* block = bo->getBlock();
    QString blockMsg = block->allocate(this);
    if (blockMsg != "" || (block->getState() & OBlock::OCCUPIED) > 0) {
        setStoppingBlock(block);
        log->info("allocateNextBlock "+(blockMsg != "" ? blockMsg : (block->getDisplayName() + " allocated, but Occupied.")));
        return false;
    }
    blockMsg = bo->setPath(this);
    if (blockMsg != "") {
        // _shareTOBlock is set by callback from setPath()
        log->info("allocateNextBlock: Warrant \"" + getDisplayName() + "\" shares a turnout. " + blockMsg);
        return false;
    }
    return true;
}

/**
 *  if next block is allocated, set the path. If there are no
 *  occupation problems get the permitted speed from the signals
 *  Sets adlay speed change in advance of the next block
 *  Called by:
 *  	startWarrant at start
 *  	checkStoppingBlock when stopping block has cleared
 * @return an "occupied" (Stop or continue) speed change
 */
/*private*/ QString Warrant::getNextSpeed() {
    QString nextSpeed = "";
    QString exitSpeed = "";
    BlockOrder* bo = getBlockOrderAt(_idxCurrentOrder+1);
    OBlock* nextBlock = bo->getBlock();
    if (allocateNextBlock(nextBlock)) {
        bo->setPath(this);
        nextSpeed = bo->getPermissibleEntranceSpeed();
        exitSpeed = bo->getPermissibleExitSpeed();
        long speedOffset = 1000*getSpeedChangeWait(_idxCurrentOrder+1);
        if (nextSpeed==nullptr) {
            bo = getBlockOrderAt(_idxCurrentOrder);
            nextSpeed = bo->getPermissibleExitSpeed();
            speedOffset = 1000*getSpeedChangeWait(_idxCurrentOrder);
       }
        if (nextSpeed!=nullptr ) {
            if (nextSpeed==("Stop")) {
                _stoppingSignal = bo->getSignal();
                //_stoppingSignal.addPropertyChangeListener(this);
                connect(_stoppingSignal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
            }
            if(_debug) log->debug("signal indicates \""+nextSpeed+"\" entrance speed and \""+exitSpeed+
                    "\" exit speed on Warrant \""+getDisplayName()+"\".\n Set change speed Delay to "+
                    QString::number(speedOffset)+"ms for entrance into "+nextBlock->getDisplayName()+
                    (_stoppingSignal==nullptr ? ".": " _stoppingSignal= \""+_stoppingSignal->getDisplayName()+"\""));
        } else if ((nextBlock->getState() & OBlock::OCCUPIED) != 0) {
            // Rule 292 - "visible" obstacle ahead. no signals or they didn't detect it.
            nextSpeed = "Stop";
        }
        // If next block is dark, check blocks beyond for occupancy
        if ((nextBlock->getState() & OBlock::DARK) != 0) {
            for (int idx=_idxCurrentOrder+2; idx < _orders->size(); idx++) {
                bo = getBlockOrderAt(idx);
                if ((bo->getBlock()->getState() & OBlock::OCCUPIED) != 0) {
                    _stoppingBlock = bo->getBlock();
                    //_stoppingBlock->addPropertyChangeListener(this);
                    connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                    nextSpeed = "Stop";
                    if(_debug) log->debug("Block Occupied. Warrant \""+getDisplayName()+
                            "\" sets _stoppingBlock= \""+_stoppingBlock->getDisplayName()+"\"");
                    break;
                }

            }
        }
    } else {
        _stoppingBlock = bo->getBlock();
        //_stoppingBlock->addPropertyChangeListener(this);
        connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));nextSpeed = "Stop";
        log->info("Block can't be allocated. Warrant \""+getDisplayName()+
                "\" sets _stoppingBlock= \""+_stoppingBlock->getDisplayName()+"\"");
    }
    if (nextSpeed!=nullptr) {
        if ("Stop"!=(nextSpeed)) {
            _currentSpeed = nextSpeed;
        }
    } else {
        if (_exitSpeed!=nullptr) {
            // saved exit speed from last block
            nextSpeed = _exitSpeed;
        } else {
            // continue as before
            nextSpeed = _currentSpeed;
        }
    }
    _exitSpeed = exitSpeed;
    if(_debug) log->debug("getNextSpeed(): Entrance speed for \""+nextBlock->getDisplayName()+"\"= \""+
                            nextSpeed+"\" for warrant= "+getDisplayName());
    return nextSpeed;
}

CommandDelay::CommandDelay(QString speedType, long startWait, int cmdIndex, Warrant* warrant)
{
 log = new Logger("CommandDelay");
 this->warrant = warrant;
 nextSpeedType = speedType;
 if (startWait>0)
 {
  _startWait = startWait;
 }
 else
  _startWait = 0;
 _cmdIndex = cmdIndex;
 if(warrant->_debug) log->debug("CommandDelay: will wait "+QString::number(startWait)+" ms, then Ramp to "+speedType);
}
/*public*/ void CommandDelay::process()
{
    /*synchronized(this)*/ {
        if (_startWait>0.0) {
            try {
#if QT_VERSION < 0x050000
                wait(_startWait);
#else
                SleeperThread::sleep(_startWait);
#endif
            } catch (InterruptedException ie) {
                log->error("InterruptedException "+ie.getMessage());
            }
        }
        if(warrant->_debug) log->debug("CommandDelay: after wait of "+QString::number(_startWait)+" ms, did Ramp to "+nextSpeedType);
        warrant->_engineer->rampSpeedTo(nextSpeedType);
        warrant->_engineer->setCurrentCommandIndex(_cmdIndex);
    }
 emit finished();
}
