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
#include "logix/learnthrottleframe.h"
#include "lnthrottlemanager.h"
#include "loconetthrottle.h"
#include "opath.h"
#include "trackertableaction.h"
#include "sleeperthread.h"
#include "speedutil.h"
#include <QMetaEnum>
#include "signalhead.h"
#include "signalmast.h"
#include "scwarrant.h"

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

/*protected*/ /*static*/ /*final*/ QStringList Warrant::RUN_STATE = QStringList()
            << "HaltStart"<<"atHalt"<<"Resumed"<<"Aborts"<<"Retried"<<
            "EStop"<<"Ramp"<<"Running"<<"RestrictSpeed"<<"WaitingForClear"<<"WaitingForSensor"<<
            "RunningLate"<<"WaitingForStart"<<"RecordingScript"<<"StopPending"<<"RampingUp";
/*public*/ /*static*/ /*final*/ QStringList Warrant::MODES = QStringList() << "none"<< "LearnMode"<< "RunAuto"<< "RunManual";

/**
 * Create an object with no route defined.
 * The list of BlockOrders is the route from an Origin to a Destination
 */
/*public*/ Warrant::Warrant(QString sName, QString uName, QObject *parent) : AbstractNamedBean(sName.toUpper(), uName, parent)
{
 //super(sName.toUpperCase(), uName);
 log = new Logger("Warrant");
 _savedOrders = new QList<BlockOrder*>();
 _throttleFactor = 1.0;
 _commands = new QList<ThrottleSetting*>();
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
 _self = this;

 log->setDebugEnabled(true);
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
 int size = _orders->size();
 if (size < 2) {
     return nullptr;
 }
 return new BlockOrder(_orders->at(size - 1));
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
        if (_orders->at(i)->getBlock()->equals(block)) {
            return i;
        }
    }
    return -1;
}
/**
 * Find block BEFORE endIdx.
 *
 * @param endIdx index of block order
 * @param block used by the warrant
 * @return index of block ahead of block order index, -1 if not found
 */
/*protected*/ int Warrant::getIndexOfBlockBefore(int endIdx, OBlock* block) {
    for (int i = endIdx; i >= 0; i--) {
        if (_orders->value(i)->getBlock()->equals(block)) {
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

/*public*/ QList<ThrottleSetting *>* Warrant::getThrottleCommands() {
    return _commands;
}
/*public*/ void Warrant::addThrottleCommand(ThrottleSetting* ts) {
    _commands->append(ts);
}

/*public*/ void Warrant::setThrottleCommands(QList<ThrottleSetting*>* list) {
    _commands = list;
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
   if (_speedUtil->getAddress() == nullptr)
   {
       return tr("Locomotive not Assigned.");
   }
   //if (!(this->instanceof SCWarrant) && _commands.size() <= _orders.size())
   if(qobject_cast<SCWarrant*>(this) && _commands->size() <= _orders->size())
   {
       return tr("Warrant \"%1\" has incomplete throttle commands.").arg(getDisplayName());
   }
   if (_message == "") {
       return tr("Idle");
   }
   if (_idxCurrentOrder != 0 && _idxLastOrder == _idxCurrentOrder) {
       return tr("Warrant aborted. Location of \"%1\" unknown. Not found at \"%2\". -").arg(_trainName).arg(getCurrentBlockName()) + _message;
   }
   return tr("Idle - %1").arg(_message);
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
                    if ("SPEED" == (ts.getCommand().toUpperCase())) {
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

/*synchronized*/ /*public*/ void Warrant::stopWarrant(bool abort) {
    stopWarrant(abort, true);
}
/*synchronized*/ /*public*/ void Warrant::stopWarrant(bool abort, bool turnOffFunctions) {
    _delayStart = false;
    if (_protectSignal != nullptr) {
        _protectSignal->removePropertyChangeListener((PropertyChangeListener*)this);
        _protectSignal = nullptr;
        _idxProtectSignal = -1;
    }
    if (_stoppingBlock != nullptr) {
        _stoppingBlock->removePropertyChangeListener((PropertyChangeListener*)this);
        _stoppingBlock = nullptr;
    }
    if (_otherShareBlock != nullptr) {
        _otherShareBlock->removePropertyChangeListener((PropertyChangeListener*)this);
        _otherShareBlock = nullptr;
        _myShareBlock = nullptr;
    }
    deAllocate();
    int oldMode = _runMode;
    _runMode = MODE_NONE;

    if (_student != nullptr) {
        _student->dispose(); // releases throttle
        _student = nullptr;
    }
    if (_engineer != nullptr) {
        _speedUtil->stopRun(!abort); // don't write speed profile measurements
        _engineer->stopRun(abort, turnOffFunctions); // release throttle
        _engineer = nullptr;
    }
    if (abort) {
        fireRunStatus("runMode", oldMode, MODE_ABORT);
    } else {
        fireRunStatus("runMode", oldMode, _runMode);
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("Warrant \"%1\" terminated %2.").arg(getDisplayName()).arg((abort == true ? "- aborted!" : "normally")));
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
* (block->_warrant == this)  and path set for Run Mode
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
 if (log->isDebugEnabled()) {
  QMetaEnum metaEnum = QMetaEnum::fromType<Warrant::MODEVALS>();
     log->debug(tr("setRunMode(%1) (%2) called with _runMode= %3. warrant= %4").arg(
             mode).arg(QString(metaEnum.valueToKey(mode))).arg(QString(metaEnum.valueToKey(_runMode))).arg(getDisplayName()));
 }
 _message = "";
 if (_runMode != MODE_NONE) {
     _message = getRunModeMessage();
     log->error(_message);
     return _message;
 }
 _idxLastOrder = 0;
 _delayStart = false;
 _curSpeedType = Normal;
 _waitForSignal = false;
 _waitForBlock = false;
 _waitForWarrant = false;
 if (address != nullptr) {
     _speedUtil->setDccAddress(address);
 }
 if (mode == MODE_LEARN) {
     // Cannot record if block 0 is not occupied or not dark. If dark, user is responsible for occupation
     if (student == nullptr) {
         _message = tr("No learning throttle for \"%1\" in learning mode.").arg(getDisplayName());
         log->error(_message);
         return _message;
     }
     /*synchronized (this)*/ {
         _student = student;
     }
     // set mode before notifyThrottleFound is called
     _runMode = mode;
     }
     else if (mode == MODE_RUN || mode == MODE_MANUAL)
     {
      if ( commands != nullptr && commands->size() > _orders->size()) {
          _commands = commands;
      }
      // set mode before setStoppingBlock and callback to notifyThrottleFound are called
      _idxCurrentOrder = 0;
      _runMode = mode;
      // Delayed start is OK if block 0 is not occupied. Note can't delay start if block is dark
      if (!runBlind) {
          int state = getBlockStateAt(0);
          if ((state & (OBlock::OCCUPIED | OBlock::UNDETECTED)) == 0) {
              // continuing with no occupation of starting block
              setStoppingBlock(getBlockAt(0));
              _delayStart = true;
          }
      }
     } else {
         stopWarrant(true);
     }
     getBlockAt(0)->_entryTime = QDateTime::currentMSecsSinceEpoch();//System.currentTimeMillis();
     if (_runBlind) {
         _tempRunBlind = _runBlind;
     } else {
         _tempRunBlind = runBlind;
     }
     if (!_delayStart) {
         if (mode != MODE_MANUAL) {
             _message = acquireThrottle();
         } else {
             startupWarrant(); // assuming manual operator will go to start block
         }
     }
     fireRunStatus("runMode", MODE_NONE, _runMode);
     if (log->isDebugEnabled()) {
      QMetaEnum metaEnum = QMetaEnum::fromType<Warrant::MODEVALS>();

         log->debug(tr("Exit setRunMode()  _runMode= %1, msg= %2").arg(metaEnum.valueToKey( _runMode)).arg(_message));
     }
     return _message;
} // end setRunMode

/**
 * @return error message if any
 */
/*protected*/ QString Warrant::acquireThrottle() {
    QString msg = "";
    DccLocoAddress* dccAddress = _speedUtil->getDccAddress();
    if (log->isDebugEnabled()) {
        log->debug(tr("acquireThrottle request at %1 for warrant %2").arg(
                dccAddress->toString()).arg(getDisplayName()));
    }
    if (dccAddress == nullptr) {
        msg = tr("Warrant \"%1\" has no train address.").arg(getDisplayName());
    } else {
        ThrottleManager* tm = (ThrottleManager*)InstanceManager::getNullableDefault("ThrottleManager");
        if (tm == nullptr) {
            msg = tr("Throttle Manager unavailable or cannot provide throttle. %1").arg(_speedUtil->getDccAddress()->getNumber());
        } else {
            if (!tm->requestThrottle(dccAddress, (ThrottleListener*)this, false)) {
                return tr("Address invalid, (Address %1) or train in use on another throttle.").arg(dccAddress->getNumber());
            }
        }
    }
    if (msg != "") {
        abortWarrant(msg);
        fireRunStatus("throttleFail", "", msg);
        return msg;
    }
    return "";
}

/**
 * Pause and resume auto-running train or abort any allocation state User
 * issued overriding commands during run time of warrant _engineer.abort()
 * calls setRunMode(MODE_NONE,...) which calls deallocate all.
 *
 * @param idx index of control command
 * @return false if command cannot be given
 */
/*public*/ bool Warrant::controlRunTrain(int idx)
{
 if (idx < 0) {
     return false;
 }
 bool ret = false;
 if (_engineer == nullptr) {
     if (log->isDebugEnabled()) {
         log->debug(tr("controlRunTrain(%1)= \"%2\" for train %3 runMode= %4. warrant %5").arg(
                 idx).arg(CNTRL_CMDS[idx]).arg(getTrainName()).arg(MODES[_runMode]).arg(getDisplayName()));
     }
     switch (idx) {
         case HALT:
         case RESUME:
         case RETRY:
         case RAMP_HALT:
             fireRunStatus("SpeedChange", 0, idx);
             break;
         case STOP:
         case ABORT:
             if (_runMode == Warrant::MODE_LEARN) {
                 // let WarrantFrame do the abort. (WarrantFrame listens for "abortLearn")
                 fireRunStatus("abortLearn", -MODE_LEARN, _idxCurrentOrder);
             } else {
                 fireRunStatus("controlChange", MODE_RUN, ABORT);
                 stopWarrant(true);
             }
             break;
         case DEBUG:
             ret = debugInfo();
             fireRunStatus("SpeedChange", 0, idx);
             break;
         default:
             break;
     }
     return ret;
 }
 int runState = _engineer->getRunState();
 if (log->isDebugEnabled()) {
     log->debug(tr("controlRunTrain(%1)= \"%2\" for train %3 runstate= %4, in block %5. warrant %6").arg(
             idx).arg(CNTRL_CMDS[idx]).arg(getTrainName()).arg(RUN_STATE[runState]).arg(
             getBlockAt(_idxCurrentOrder)->getDisplayName()).arg(getDisplayName()));
 }
 /*synchronized (_engineer)*/ {
   BlockOrder* bo;
   OBlock* block;
     switch (idx) {
         case RAMP_HALT:
             cancelDelayRamp();
             _engineer->rampSpeedTo(Warrant::Stop, 0, false);  // immediate ramp down
             _engineer->setHalt(true);
//                    setMovement(MID);
             ret = true;
             break;
         case RESUME:
             bo = getBlockOrderAt(_idxCurrentOrder);
             block = bo->getBlock();
             if ((block->getState() & (OBlock::OCCUPIED | OBlock::UNDETECTED)) != 0) {
                 // we assume this occupation is this train. user should know
                 if (runState == WAIT_FOR_CLEAR || runState == HALT) {
                     // However user knows if condition may have cleared due to overrun.
                     _message = allocateFromIndex(false, true, _idxCurrentOrder + 1);
                     // This is user's decision to reset and override wait flags
                     ThrottleRamp* ramp = _engineer->getRamp();
                     if (ramp == nullptr || ramp->ready) {   // do not change flags when ramping
                         // recheck flags
                         if (_idxCurrentOrder < _orders->size() - 1 &&
                           Stop == (getSpeedTypeForBlock(_idxCurrentOrder + 1))) {
                          break;	// cannot overide flags
                         }
                      if (_idxCurrentOrder == 0) {
                             _engineer->setHalt(false);
                      }
                         _waitForSignal = false;
                         _waitForBlock = false;
                         _waitForWarrant = false;
//                                _engineer.setWaitforClear(false);
                         // engineer will clear its flags when ramp completes
                         _engineer->rampSpeedTo(_curSpeedType, 0, false);
                     }
                 } else if (runState == WAIT_FOR_TRAIN || runState == SPEED_RESTRICTED) {
                     // user wants to increase throttle of stalled train slowly
                     float speedSetting = _engineer->getSpeedSetting();
                     _engineer->setSpeed(speedSetting + _speedUtil->getRampThrottleIncrement());
                 } else {    // last resort from user to get on script
                     _engineer->setSpeed(_speedUtil->modifySpeed(_engineer->getScriptSpeed(), _curSpeedType));
                 }
                 ret = true;
             } else {    // train must be lost.
                 // user wants to increase throttle of stalled train slowly
                 float speedSetting = _engineer->getSpeedSetting();
                 _engineer->setSpeed(speedSetting + _speedUtil->getRampThrottleIncrement());
             }
             break;
         case RETRY: // Force move into next block, which was seen as rogue occupied
             bo = getBlockOrderAt(_idxCurrentOrder + 1);
             // if block belongs to this warrant, then move unconditionally into block
             if (bo != nullptr) {
                 block = bo->getBlock();
                 if (block->allocate(this) == nullptr && (block->getState() & OBlock::OCCUPIED) != 0) {
                     _idxCurrentOrder++;
                     if (block->equals(_stoppingBlock)) {
                         clearStoppingBlock();
                     }
                     QString msg = bo->setPath(this);
                     if (msg != nullptr) {
                         log->warn(tr("Cannot clear path for warrant \"%1\" at block \"%2\" - msg = %3").arg(
                                 getDisplayName()).arg(block->getDisplayName()).arg(msg));
                     }
                     goingActive(block);
                     ret = true;
                 }
             }
             break;
         case ABORT:
             stopWarrant(true);
             ret = true;
             break;
         case HALT:
         case STOP:
             cancelDelayRamp();
             _engineer->setStop(false, true); // sets _halt
             ret = true;
             break;
         case ESTOP:
             cancelDelayRamp();
             _engineer->setStop(true, true); // E-stop & halt
             ret = true;
             break;
         case DEBUG:
             ret = debugInfo();
             fireRunStatus("SpeedChange", 0, idx);
             return ret;
         default:
             return false;
     }
 }
 int state = runState;
 if ( state == Warrant::HALT) {
  if (_waitForSignal || _waitForBlock || _waitForWarrant) {
   state = WAIT_FOR_CLEAR;
  }
 }
 if (ret) {
     fireRunStatus("controlChange", state, idx);
 } else {
     fireRunStatus("controlFailed", state, idx);
 }
 return ret;
}

/*protected*/ bool Warrant::debugInfo() {
    QString info;// = new StringBuffer("\nWarrant ");
    info.append(getDisplayName()); info.append(", ");
    info.append("Current BlockOrder idx= "); info.append(_idxCurrentOrder);
    info.append(",  Block \""); info.append(getBlockAt(_idxCurrentOrder)->getDisplayName()); info.append("\"");
    info.append("\n\tWarrant flags: _waitForSignal= ");
    info.append(_waitForSignal); info.append(", _waitForBlock= ");
    info.append(_waitForBlock); info.append(", _waitForWarrant= ");
    info.append(_waitForWarrant); info.append("\n\t");
    if (_engineer != nullptr) {
        info.append("Engineer runstate= ");
        info.append(RUN_STATE[_engineer->getRunState()]); info.append(", ");
        info.append("speed setting= ");
        info.append(QString::number(_engineer->getSpeedSetting())); info.append(", ");
        info.append("scriptSpeed= ");
        info.append(QString::number(_engineer->getScriptSpeed())); info.append("\n\t");
        int cmdIdx = _engineer->getCurrentCommandIndex();
        info.append("current Cmd Index #");
        // Note: command indexes biased from 0 to 1 to match Warrant's 1-based display of commands.
        info.append(cmdIdx + 1); info.append(", Command: ");
        info.append(getThrottleCommands()->value(cmdIdx)->toString()); info.append("\n\t");
        info.append(_engineer->getFlags()); info.append("\n\t\t");
//            for (StackTraceElement elem :_engineer.getStackTrace()) {
//                info.append(elem.getClassName()); info.append(".");
//                info.append(elem.getMethodName()); info.append(", line ");
//                info.append(elem.getLineNumber()); info.append("\n\t\t");
//            }
        info.append("\tEngineer Thread.State= ");
//        info.append(QString::number(getState())); info.append("\n\t");
        ThrottleRamp* ramp = _engineer->getRamp();
        if (ramp != nullptr) {
//            info.append("Ramp Thread.State= "); info.append(ramp->getState());
            info.append(", ready= "); info.append(ramp->ready); info.append("\n\t\t");
//                for (StackTraceElement elem : ramp.getStackTrace()) {
//                    info.append(elem.getClassName()); info.append(".");
//                    info.append(elem.getMethodName()); info.append(", line ");
//                    info.append(elem.getLineNumber()); info.append("\n\t\t");
//                }
        } else {
            info.append("No ramp");
        }
    } else {
        info.append("No engineer");
    }
    log->info(info/*.toString()*/);
    return true;
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
    _speedUtil->setThrottle(throttle);
    _speedUtil->setOrders(_orders);
    startupWarrant();
    runWarrant(throttle);
}

/*protected*/ void Warrant::startupWarrant() {
 _idxCurrentOrder = 0;
 _idxLastOrder = 0;
 _curSpeedType = Normal;
 // set block state to show our train occupies the block
 BlockOrder* bo = getBlockOrderAt(0);
 OBlock* b = bo->getBlock();
 b->setValue(_trainName);
 b->setState(b->getState() | OBlock::RUNNING);
}

/*private*/ void Warrant::runWarrant(DccThrottle* throttle) {
    if (_runMode == MODE_LEARN) {
        /*synchronized (this)*/ {
            _student->notifyThrottleFound(throttle);
        }
    } else {
         _engineer = new Engineer(this, throttle);
        if (_tempRunBlind) {
            _engineer->setRunOnET(true);
        }
        if (_delayStart) {
            _engineer->setHalt(true);    // throttle already at 0
        }
        // if there may be speed changes due to signals or rogue occupation.
        if (_noRamp) { // make immediate speed changes
            _speedInfo = QList<BlockSpeedInfo*>();
        } else { // make smooth speed changes by ramping
            getBlockSpeedTimes();
        }
        QThread* thread = new QThread();
        _engineer->moveToThread(thread);
        connect(thread, SIGNAL(started()), _engineer, SLOT(process()));
        connect(_engineer, SIGNAL(finished()), thread, SLOT(quit()));
        connect(_engineer, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();

        if (_delayStart) {
            // user must explicitly start train (resume) in a dark block
            fireRunStatus("ReadyToRun", -1, 0);   // ready to start msg
        }
        if (_engineer->getRunState() == Warrant::RUNNING) {
            setMovement(MID);
        }
        _delayStart = false; // script should start when user resumes - no more delay
    }
}

/*public*/ void Warrant::notifyFailedThrottleRequest(LocoAddress *address, QString reason) {
    log->error("notifyFailedThrottleRequest address= " +address->toString()+" _runMode= "+QString::number(_runMode)+
            " due to "+reason);
}
/**
 * No steal or share decisions made locally
 * <p>
 * {@inheritDoc}
 */
//@Override
///*public*/ void notifyDecisionRequired(LocoAddress* address, DecisionType question) {
//}

/*protected*/ void Warrant::releaseThrottle(DccThrottle* throttle) {
    if (throttle != nullptr) {
        ThrottleManager* tm =  (ThrottleManager*)InstanceManager::getNullableDefault("ThrottleManager");
        if (tm != nullptr) {
            tm->releaseThrottle(throttle, this);
        } else {
            log->error(tr("Throttle Manager unavailable or cannot provide throttle. %1").arg(throttle->getLocoAddress()->toString()));
        }
    }
}

/*protected*/ void Warrant::abortWarrant(QString msg) {
    log->error(tr("Abort warrant \"%1\" - %2 ").arg(getDisplayName()).arg(msg));
    stopWarrant(true);
}
/**
 * Allocate as many blocks as possible from the start of the warrant.
 * The first block must be allocated and all blocks of the route must
 * be in service. Otherwise partial success is OK.
 * Installs listeners for the entire route.
 * If occupation by another train is detected, a message will be
 * posted to the Warrant List Window. Note that warrants sharing their
 * clearance only allocate and set paths one block in advance.
 *
 * @param orders list of block orders
 * @param show (for use ONLY to display a temporary route) continues to
 *  allocate skipping over blocks occupied or owned by another warrant.
 * @return error message, if unable to allocate first block or if any block
 *         is OUT_OF_SERVICE
 */
/*public*/ QString Warrant::allocateRoute(bool show, QList<BlockOrder*>* orders) {
    if (_totalAllocated) {
        return "";
    }
    if (orders != nullptr) {
        _orders = orders;
    }
    _allocated = false;
    OBlock* block = getBlockAt(0);
    _message = block->allocate(this);
    if (_message != "") {
        return _message;
    }

    _allocated = true; // start block allocated
    QString msg = allocateFromIndex(show, false, 1);
    if (msg != "") {
        _message = msg;
    } else if (_partialAllocate) {
        _message = tr("Shared route (not fully allocated).");
    }
    if (show) {
        return _message;
    }
    return "";
}

/*
 * Allocate and set path
 * Only return a message if allocation of first index block fails.
 * @param show true when displaying a temporary route.  N.B. Allocates beyond clearance issues.
 * when false does not allocate beyond a clearance issue.
 * @param set only allocates and sets path in one block, the 'index' block
 * show the entire route but do not set any turnouts in occupied blocks
 */
/*private*/ QString Warrant::allocateFromIndex(bool show, bool set, int index) {
    int limit;
    if (_partialAllocate || set) {
        limit = qMin(index + 1, _orders->size());
    } else {
        limit = _orders->size();
    }
    OBlock* currentBlock = getBlockOrderAt(_idxCurrentOrder)->getBlock();
    if (log->isDebugEnabled()) {
        log->debug(tr("allocateFromIndex(%1) block= %2 _partialAllocate= %3 for warrant \"%4\".").arg(
                index).arg(currentBlock->getDisplayName()).arg(_partialAllocate).arg(getDisplayName()));
    }
    _message = "";
    bool passageDenied = false;  // cannot allocate beyond this point
    for (int i = index; i < limit; i++) {
        BlockOrder* bo = _orders->at(i);
        OBlock* block = bo->getBlock();
        QString msg = block->allocate(this);
        if (msg != "" && _message == "") {
            _message = msg;
            if (!this->equals(block->getWarrant())) {
                _waitForWarrant = true;
            } else {
                _waitForBlock = true;
            }
            passageDenied = true;
        }
        if (!passageDenied) {
            // loop back routes may enter a block a second time
            // Do not make current block a stopping block
            if (!currentBlock->equals(block)) {
                if ((block->getState() & OBlock::OCCUPIED) != 0) {  // (!block->isAllocatedTo(this) || ) removed 7/1/18
                    if (_message == "") {
                        _message = tr("Block \"%1\" occupied by unknown train.").arg(block->getDisplayName());
                    }
                    passageDenied = true;
                }
                if (!passageDenied && Warrant::Stop ==(getPermissibleSpeedAt(bo))) {
                    if (_message == "") {
                        _message = tr("Cannot set route beyond block \"%1\". Signal at Stop aspect.").arg(block->getDisplayName());
                    }
                    passageDenied = true;
                }
            }
            if (!passageDenied && set) {
                msg = bo->setPath(this);
                if (msg != "") {
                    if (_message == "") {
                        _message = msg;
                    }
                    passageDenied = true;
                }
            }
        }
    }
    if (!passageDenied && limit == _orders->size()) {
        _totalAllocated = true;
    }
    return _message;
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
#if 0
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
//                            getDisplayName(), block->getDisplayName());
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
#endif
/**
 * Convenience routine to use from Python to start a warrant.
 *
 * @param mode run mode
 */
/*public*/ void Warrant::runWarrant(int mode) {
    if (_partialAllocate) {
        deAllocate();   // allow route to be shared with another warrant
    }
    setRoute(false, nullptr);
    setRunMode(mode, nullptr, nullptr, nullptr, false);
}

/**
 * Set the route paths and turnouts for the warrant. Only the first block
 * must be allocated and have its path set. Partial success is OK.
 * A message of the first subsequent block that fails allocation
 * or path setting is written to a field that is
 * displayed in the Warrant List window. When running with block
 * detection, occupation by another train or block 'not in use' or
 * Signals denying movement are reasons
 * for such a message, otherwise only allocation to another warrant
 * prevents total success. Note that warrants sharing their clearance
 * only allocate and set paths one block in advance.
 *
 * @param show  value==1 will ignore _partialAllocate (to show route only)
 *            parm name delay of turnout steting deprecated
 * @param orders  BlockOrder list of route. If null, use permanent warrant
 *            copy.
 * @return message if the first block fails allocation, otherwise null
 */
/*public*/ QString Warrant::setRoute(bool show, QList<BlockOrder *> *orders) {
    // we assume our train is occupying the first block
    _routeSet = false;
    QString msg = allocateRoute(show, orders);
    if (msg != "") {
        _message = msg;
        return _message;
    }
    _allocated = true;
    BlockOrder* bo = _orders->at(0);
    msg = bo->setPath(this);
    if (msg != "") {
        _message = msg;
        return _message;
    }
    _routeSet = true;   // partially set OK
    if (!_partialAllocate) {
        for (int i = 1; i < _orders->size(); i++) {
            bo = _orders->at(i);
            OBlock* block = bo->getBlock();
            if ((block->getState() & OBlock::OCCUPIED) != 0) {
                if (_message != "") {
                    _message = tr("Block \"%1\" occupied by unknown train.").arg(block->getDisplayName());
                }
                break; // OK. warning status is posted with _message
            }
            if (Warrant::Stop == (getPermissibleSpeedAt(bo))) {
                if (_message != "") {
                    _message = tr("Cannot set route beyond block \"%1\". Signal at Stop aspect.").arg(block->getDisplayName());
                }
                break; // OK. warning status is posted with _message
            }
            msg = bo->setPath(this);
            if (msg != "" && _message == "") {
                _message = msg;
                break; // OK. warning status is posted with _message
            }
        }
    }
    _routeSet = true;
    return "";
} // setRoute

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
//                                            block->getDisplayName());
        msg = tr("Block \"%1\" is dark, cannot guarantee route is set or clear.").arg(block->getDisplayName());
     } else if ((state & OBlock::OCCUPIED) == 0) {
//        msg = java.text.MessageFormat.format(rb.getString("badStart"),
//                                            block->getDisplayName());
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
//                    getDisplayName(), block->getDisplayName());
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
    return tr("Unable to allocate originating block->\n\"%1\".").arg(w->getDisplayName());
}

/*public*/ void Warrant::propertyChange(PropertyChangeEvent* evt)
{
 if(qobject_cast<NamedBean*>(evt->getSource())!= 0)
 {
//            if (_debug) log->debug("propertyChange \""+evt.getPropertyName()+
//                                                "\" old= "+evt.getOldValue()+" new= "+evt.getNewValue());
     return;
 }
 QString property = evt->getPropertyName();
 if (log->isDebugEnabled())
 {
   log->debug(tr("propertyChange \"%1\" new= %2 source= %3 - warrant= %4").arg(
           property).arg(evt->getNewValue().toString()).arg(((NamedBean*) evt->getSource())->getDisplayName()).arg(getDisplayName()));
 }

  if (_protectSignal != nullptr && _protectSignal == evt->getSource()) {
      if (property == ("Aspect") || property == ("Appearance")) {
          // signal controlling warrant has changed.
          readStoppingSignal();
      }
  } else if (property ==("state")) {
      if (_stoppingBlock != nullptr && _stoppingBlock == (evt->getSource())) {
          // starting block is allocated but not occupied
          if (_delayStart) { // wait for arrival of train to begin the run
              if ((( evt->getNewValue().toInt()) & OBlock::OCCUPIED) != 0) {
                  // train arrived at starting block
                  Warrant* w = _stoppingBlock->getWarrant();
                  if (this == (w) || w == nullptr) {
                      if (clearStoppingBlock()) {
                          OBlock* block = getBlockAt(_idxCurrentOrder);
                          if (_runMode == MODE_RUN) {
                              acquireThrottle();
                          } else if (_runMode == MODE_MANUAL) {
                              fireRunStatus("ReadyToRun", -1, 0);   // ready to start msg
                              _delayStart = false;
                          } else {
                              _delayStart = false;
                              log->error(tr("StoppingBlock \"%1\" set with mode &2").arg(block->getDisplayName()).arg(
                                      /*MODES[_runMode]*/_runMode));
                          }
                          block->_entryTime = QDateTime::currentMSecsSinceEpoch();//System.currentTimeMillis();
                          block->setValue(_trainName);
                          block->setState(block->getState() | OBlock::RUNNING);
                      }
                  }
              }
          } else if (( evt->getNewValue().toInt() & OBlock::UNOCCUPIED) != 0) {
              // normal wait for a train underway but blocked ahead by occupation
              //  blocking occupation has left the stopping block
              int idx = getIndexOfBlock(_stoppingBlock, _idxLastOrder);
              if (idx >= 0) {
                  // Wait to allow departing rogue train to clear turnouts before re-allocation
                  // of this warrant resets the path. Rogue may leave on a conflicting path
                  // whose turnout control is shared with this path
//                  ThreadingUtil.runOnGUIDelayed(() -> {
                      clearStoppingBlock();
//                  }, 7000);   // 7 seconds

              }
          }
      } else if (_otherShareBlock != nullptr && _otherShareBlock == evt->getSource()) {
          if ((( evt->getNewValue()).toInt() & OBlock::UNOCCUPIED) != 0) {
              clearShareTOBlock();
          }
      }
  } else if (_delayStart && property == ("runMode") && ( evt->getNewValue()).toInt() == MODE_NONE) {
      // Starting block was owned by another warrant for this engine
      // Engine has arrived and Blocking Warrant has finished
      ((Warrant*) evt->getSource())->removePropertyChangeListener((PropertyChangeListener*)this);
      if (clearStoppingBlock()) {
          acquireThrottle();
      }
  }
 }
/*private*/ bool Warrant::readStoppingSignal() {
    QString speedType;
    if (qobject_cast<SignalHead*>(_protectSignal)) {
        SignalHead* head = (SignalHead*) _protectSignal;
        int appearance = head->getAppearance();
        speedType = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))
                ->getAppearanceSpeed(head->getAppearanceName(appearance));
        if (log->isDebugEnabled()) {
            log->debug(tr("SignalHead %1 sets appearance speed to %2 - warrant= %3").arg(
                    _protectSignal->getDisplayName()).arg(speedType).arg(getDisplayName()));
        }
    } else {
        SignalMast* mast = (SignalMast*) _protectSignal;
        QString aspect = mast->getAspect();
        speedType = ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getAspectSpeed(aspect,
                mast->getSignalSystem());
        if (log->isDebugEnabled()) {
            log->debug(tr("SignalMast %1 sets aspect speed to %2 - warrant= %3").arg(
                    _protectSignal->getDisplayName()).arg(speedType).arg(getDisplayName()));
        }
    }
    if (speedType == nullptr) {
        return false; // dark or no specified speed
    } else if (speedType == (Warrant::Stop)) {
        _waitForSignal = true;
        return true;
    } else {
        _curSpeedType = speedType;
        _waitForSignal = false;
        if (!_waitForBlock && !_waitForWarrant && _engineer != nullptr) {
            allocateFromIndex(false, true, _idxCurrentOrder + 1);
         // engineer will clear its flags when ramp completes
            _engineer->rampSpeedTo(speedType, 0, false);
//                setMovement(END);
            return true;
        }
        fireRunStatus("SpeedChange", _idxCurrentOrder - 1, _idxCurrentOrder);
        return false;
    }
}

/*private*/ bool Warrant::doStoppingBlockClear() {
    if (_stoppingBlock == nullptr) {
        return true;
    }
    QString blockName = _stoppingBlock->getDisplayName();
    _stoppingBlock->removePropertyChangeListener((PropertyChangeListener*)_self);
    _stoppingBlock = nullptr;
    if (log->isDebugEnabled())
        log->debug(tr("Warrant \"%1\" Cleared _stoppingBlock= \"%2\".").arg(getDisplayName()).arg(blockName));
    return restoreRunning();
}

/**
 * Called when a rogue train has left a block-> Allows the warrant to continue to run.
 * Also called from propertyChange() to allow warrant to acquire a throttle
 * and launch an engineer. Also called by retry control command to help user
 * work out of an error condition.
 */
/*private*/ bool Warrant::clearStoppingBlock() {
    if (_stoppingBlock == nullptr) {
        return false;
    }
    QString blockName = _stoppingBlock->getDisplayName();
    if (log->isDebugEnabled())
        log->debug(tr("Warrant \"%1\" clearing _stoppingBlock= \"%2\".").arg(
            getDisplayName()).arg(blockName));

    QString msg = allocateFromIndex(false, true, _idxCurrentOrder + 1);
    if (msg == "" && doStoppingBlockClear()) {
        return true;
    }

    if (log->isDebugEnabled())
        log->debug(tr("Warrant \"%1\" allocation failed. %2. runState= %3").arg(
            getDisplayName()).arg(msg).arg((_engineer!=nullptr?RUN_STATE[_engineer->getRunState()]:"NoEngineer")));
    // If this warrant is waiting for the block that another
    // warrant has occupied, and now the latter warrant leaves
    // the block - there are notifications to each warrant "simultaneously".
    // The latter warrant's deallocation may not have happened yet and
    // this has prevented allocation to this warrant.  For this case,
    // wait until leaving warrant's deallocation is seen and completed.
    //@SuppressFBWarnings(value = "UW_UNCOND_WAIT", justification="false postive, guarded by while statement")
#if 0 //TODO:
    /*final*/ Runnable* allocateBlocks = new Runnable() {
        @Override
        public void run() {
            long time = 0;
            String msg = null;
            try {
                while (time < 200) {
                    msg = allocateFromIndex(false, true, _idxCurrentOrder + 1);
                    if (msg == null && doStoppingBlockClear()) {
                        break;
                    }
                    synchronized (this) {
                        wait(20);
                        time += 20;
                    }
                }
                if (msg != null) {
                     log->warn("Warrant \"{}\" unable to clear StoppingBlock message= \"{}\" time= {}", getDisplayName(), msg, time);
                }
                _message = msg;
            }
            catch (InterruptedException ie) {
                 log->warn("Warrant \"{}\" InterruptedException message= \"{}\" time= {}", getDisplayName(), ie.toString(), time);
                Thread.currentThread().interrupt();
            }
            if ( log->isDebugEnabled())
                 log->debug("Warrant \"{}\" waited {}ms for clearStoppingBlock to allocateFrom {}",
                       getDisplayName(), time, getBlockAt(_idxCurrentOrder + 1).getDisplayName());
        }
    };
#endif
    AllocateBlocks* allocateBlocks = new AllocateBlocks(this);

    /*synchronized (allocateBlocks)*/ {
//        Thread doit = new Thread() {
//            @Override
//            public void run() {
//                try {
//                    javax.swing.SwingUtilities.invokeAndWait(allocateBlocks);
//                }
//                catch (Exception e) {
//                    e.printStackTrace();
//                }
//            }
//        };
     DoitThread* doit = new DoitThread(allocateBlocks);
        doit->start();
    }

    return true;
}
/*public*/ void AllocateBlocks::process() {
    long time = 0;
    QString msg = nullptr;
    try {
        while (time < 200) {
            msg = _warrant->allocateFromIndex(false, true, _warrant->_idxCurrentOrder + 1);
            if (msg == "" && _warrant->doStoppingBlockClear()) {
                break;
            }
            /*synchronized (this)*/ {
               // wait(20);
             SleeperThread::msleep(20);
                time += 20;
            }
        }
        if (msg != "") {
             _warrant->log->warn(tr("Warrant \"%1\" unable to clear StoppingBlock message= \"%2\" time= %3").arg(_warrant->getDisplayName()).arg(msg).arg(time));
        }
        _warrant->_message = msg;
    }
    catch (InterruptedException ie) {
         _warrant->log->warn(tr("Warrant \"%1\" InterruptedException message= \"%2\" time= %3").arg(_warrant->getDisplayName()).arg(ie.toString()).arg(time));
        //Thread.currentThread().interrupt();
         thread()->quit();
    }
    if ( _warrant->log->isDebugEnabled())
         _warrant->log->debug(tr("Warrant \"%1\" waited %2ms for clearStoppingBlock to allocateFrom %3").arg(
               _warrant->getDisplayName()).arg(time).arg(_warrant->getBlockAt(_warrant->_idxCurrentOrder + 1)->getDisplayName()));
}

/*public*/ void DoitThread::run() {
    try {
        //javax.swing.SwingUtilities.invokeAndWait(allocateBlocks);
     QMetaObject::invokeMethod(allocateBlocks, "run", Qt::QueuedConnection);
    }
    catch (Exception e) {
//        e.printStackTrace();
    }
}

/*private*/ bool Warrant::restoreRunning() {
    int runState = -1;
    if (_engineer != nullptr) {
        runState = _engineer->getRunState();
        if (log->isDebugEnabled()) {
            log->debug(tr("restoreRunning(): rampSpeedTo to \"%1\". runState= %2. warrant= %3").arg(
                    _curSpeedType).arg(RUN_STATE[runState]).arg(getDisplayName()));
        }
        if (runState == HALT || runState == RAMP_HALT) {
            _waitForBlock = true;
        } else {
            _waitForBlock = false;
            _waitForWarrant = false;
        }
        if (!_waitForSignal && !_waitForBlock && !_waitForWarrant) {
            getBlockOrderAt(_idxCurrentOrder)->setPath(this);
            _engineer->rampSpeedTo(_curSpeedType, 0, false);
            //setMovement(MID);
        }
        return true;
    }
    return false;
}

/**
 * block (nextBlock) sharing a turnout with _shareTOBlock is already
 * allocated.
 */
/*private*/ void Warrant::clearShareTOBlock() {
    if (_otherShareBlock == nullptr) {
        return;
    }
    _otherShareBlock->removePropertyChangeListener((PropertyChangeListener*)this);
    QString msg = _orders->value(getIndexOfBlock(_myShareBlock, _idxCurrentOrder))->setPath(this);
    if (log->isDebugEnabled()) {
        log->debug(tr("_otherShareBlock= \"%1\" Cleared. %2").arg(
                _otherShareBlock->getDisplayName()).arg(msg));
    }
    _otherShareBlock = nullptr;
    _myShareBlock = nullptr;
    if (_waitForWarrant) {
        _waitForWarrant = false;
        restoreRunning();
    }
}
#if 0
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
        _stoppingBlock->addPropertyChangeListener((PropertyChangeListener*)this);
  //connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
 }
 return false;
}
#endif
/**
 * block (nextBlock) sharing a turnout with _shareTOBlock is already
 * allocated.
 */
/*private*/ void Warrant::checkShareTOBlock()
{
 if (_otherShareBlock == nullptr) {
     return;
 }
 _otherShareBlock->removePropertyChangeListener((PropertyChangeListener*)this);
 QString msg = _orders->value(getIndexOfBlock(_myShareBlock, _idxCurrentOrder))->setPath(this);
 if (log->isDebugEnabled()) {
     log->debug(tr("_otherShareBlock= \"%1\" Cleared. %2").arg(
             _otherShareBlock->getDisplayName()).arg((msg==nullptr?"":"msg")));
 }
 _otherShareBlock = nullptr;
 _myShareBlock = nullptr;
 if (_waitForWarrant) {
     _waitForWarrant = false;
     restoreRunning();
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

/*private*/ void Warrant::setStoppingSignal(int idx) {
    BlockOrder* blkOrder = getBlockOrderAt(idx);
    NamedBean* signal = blkOrder->getSignal();

    NamedBean* prevSignal = _protectSignal;
    if (_protectSignal != nullptr) {
        if (_protectSignal->equals(signal)) {
            // Must be the route coming back to the same block
            if (_idxProtectSignal < idx && idx >= 0) {
                _idxProtectSignal = idx;
            }
            return;
        } else {
            if (_idxProtectSignal <= _idxCurrentOrder && !_waitForSignal) {
                _protectSignal->removePropertyChangeListener((PropertyChangeListener*)this);
                _protectSignal = nullptr;
                _idxProtectSignal = -1;
            }
        }
    }

    if (signal != nullptr) {
        _protectSignal = signal;
        _idxProtectSignal = idx;
        _protectSignal->addPropertyChangeListener((PropertyChangeListener*)this);
    }
    if (log->isDebugEnabled()) {
        if (signal == nullptr && prevSignal == nullptr) {
            return;
        }
        QString msg = "Block \"%1\" Warrant \"%2\"";
        if (signal != nullptr) {
            msg = msg + " sets _protectSignal= \"" + _protectSignal->getDisplayName() + "\"";
        }
        if (prevSignal != nullptr) {
            msg = msg + ", removes signal= \"" + prevSignal->getDisplayName() + "\"";
        }
        log->debug(QString(msg).arg(blkOrder->getBlock()->getDisplayName()).arg(getDisplayName()));
    }
}
/**
 * Check if this is the next block of the train moving under the warrant
 * Learn mode assumes route is set and clear. Run mode update conditions.
 * <p>
 * Must be called on Layout thread.
 *
 * @param block Block in the route is going active.
 */
//@jmri.InvokeOnLayoutThread
/*protected*/ void Warrant::goingActive(OBlock* block) {
    // error if not on Layout thread
//    if (!ThreadingUtil.isLayoutThread()) {
//         log->error("invoked on wrong thread", new Exception("traceback"));
//    }

    if (_runMode == MODE_NONE) {
        return;
    }
    int activeIdx = getIndexOfBlock(block, _idxCurrentOrder);
    if ( log->isDebugEnabled()) {
         log->debug(tr("**Block \"%1\" goingActive. activeIdx= %2, _idxCurrentOrder= %3. warrant= %4").arg(
                block->getDisplayName()).arg(activeIdx).arg(_idxCurrentOrder).arg(getDisplayName()));
    }
    if (activeIdx <= 0) {
        // Not found or starting block, in which case 0 is handled as the _stoppingBlock
        if (activeIdx == 0 && _idxCurrentOrder == 0) {
            getBlockOrderAt(activeIdx)->setPath(this);
        }
        return;
    }
    int runState = -1;
    if (_engineer != nullptr) {
        runState = _engineer->getRunState();
    }
    if (activeIdx == _idxCurrentOrder) {
        // Unusual case of current block losing detection, then regaining it.  i.e. dirty track, derail etc.
        // Also, can force train to move into occupied block with "Move into next Block" command.
        // This is an unprotected move.
        if (_engineer != nullptr && runState != WAIT_FOR_CLEAR && runState != HALT) {
            // Ordinarily block just occupied would be this train, but train is stopped! - could be user's retry.
             log->info(tr("Train %1 regained detection at Block= %2").arg(getTrainName()).arg(block->getDisplayName()));
            _engineer->rampSpeedTo(_curSpeedType, 0, false); // maybe let setMovement() do this?
        }
    } else if (activeIdx == _idxCurrentOrder + 1) {
        if (_delayStart || (runState == HALT && _engineer->getSpeedSetting() > 0.0f)) {
             log->warn(tr("Rogue entered Block \"%1\" ahead of %2.").arg(block->getDisplayName()).arg(getTrainName()));
            _message = tr("Block \"%1\" occupied by unknown train.").arg(block->getDisplayName());
            return;
        }
        // be sure path is set for train in this block
        QString msg = getBlockOrderAt(activeIdx)->setPath(this);
        if (msg != "") {
             log->error(tr("goingActive setPath fails: %1").arg(msg));
        }
        if (_engineer != nullptr && _engineer->getSpeedSetting() <= 0.0f) {
            // Train can still be moving after throttle set to 0. Block
            // boundaries can be crossed.  This is due to momentum 'gliding'
            // for any nonE-Stop or by choosing ramping to a stop.
            // spotbugs knows runState != HALT here
            if (runState != WAIT_FOR_CLEAR && runState != STOP_PENDING && runState != RAMP_HALT) {
                // Apparently NOT already stopped or just about to be.
                // Therefore, assume a Rogue has just entered.
                setStoppingBlock(block);
                _engineer->setWaitforClear(true);
                _engineer->setSpeedToType(Warrant::Stop);     // for safety
                return;
            }
        }
        // Since we are moving we assume it is our train entering the block
        // continue on.
        _idxLastOrder = _idxCurrentOrder;
        _idxCurrentOrder = activeIdx;
    } else if (activeIdx > _idxCurrentOrder + 1) {
        if (_runMode == MODE_LEARN) {
             log->error(tr("Block \"%1\" became occupied before block \"%2\". ABORT recording.").arg(
                    block->getDisplayName()).arg(getBlockAt(_idxCurrentOrder + 1)->getDisplayName()));
            fireRunStatus("abortLearn", activeIdx, _idxCurrentOrder);
            return;
        }
        // if previous blocks are dark, this could be for our train
        // check from current block to this just activated block
        for (int idx = _idxCurrentOrder + 1; idx < activeIdx; idx++) {
            OBlock* preBlock = getBlockAt(idx);
            if ((preBlock->getState() & OBlock::UNDETECTED) == 0) {
                // not dark, therefore not our train
                setStoppingBlock(block);
                if ( log->isDebugEnabled()) {
                    OBlock* curBlock = getBlockAt(_idxCurrentOrder);
                     log->debug(tr("Rogue train entered block \"%1\" ahead of train %2 currently in block \"%3\"!").arg(
                            block->getDisplayName()).arg(_trainName).arg(curBlock->getDisplayName()));
                }
                return;
            }
            // we assume this is our train entering block
        }
        // previous blocks were checked as UNDETECTED above
        // Indicate the previous dark block was entered
        OBlock* prevBlock = getBlockAt(activeIdx - 1);
        prevBlock->_entryTime = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() - 500; // arbitrarily say
        prevBlock->setValue(_trainName);
        prevBlock->setState(prevBlock->getState() | OBlock::RUNNING);
        if ( log->isDebugEnabled()) {
             log->debug(tr("Train leaving UNDETECTED block \"%1\" now entering block\"%2\". warrant %3").arg(
                    prevBlock->getDisplayName()).arg(block->getDisplayName()).arg(getDisplayName()));
        }
        // Since we are moving we assume it is our train entering the block
        // continue on.
    } else if (_idxCurrentOrder > activeIdx) {
         log->error(tr("Mystifying ERROR goingActive: activeIdx = %1).arg( _idxCurrentOrder = %2!").arg(
                activeIdx).arg(_idxCurrentOrder));
        return;
    }
    setHeadOfTrain(block);
    fireRunStatus("blockChange", VPtr<OBlock>::asQVariant(getBlockAt(activeIdx - 1)), VPtr<OBlock>::asQVariant(block));
    if (_engineer != nullptr) {
        _engineer->clearWaitForSync(); // Sync commands if train is faster than ET
    }
    // _idxCurrentOrder has been incremented. Warranted train has entered this block->
    // Do signals, speed etc.
    if (_idxCurrentOrder < _orders->size() - 1) {
        allocateFromIndex(false, true, _idxCurrentOrder + 1);
        if (_engineer != nullptr) {
            BlockOrder* bo = _orders->value(_idxCurrentOrder + 1);
            if ((bo->getBlock()->getState() & OBlock::UNDETECTED) != 0) {
                // can't detect next block, use ET
                _engineer->setRunOnET(true);
            } else if (!_tempRunBlind) {
                _engineer->setRunOnET(false);
            }
        }
    } else { // train is in last block-> past all signals
        if (_protectSignal != nullptr) {
            _protectSignal->removePropertyChangeListener((PropertyChangeListener*)this);
            _protectSignal = nullptr;
            _idxProtectSignal = -1;
        }
        if (_runMode == MODE_MANUAL) { // no script, so terminate warrant run
            stopWarrant(false);
        }
    }
    if ( log->isTraceEnabled()) {
         log->debug(tr("end of goingActive. leaving \"%1\" entered \"%2\". warrant %3").arg(
                getBlockAt(activeIdx - 1)->getDisplayName()).arg(block->getDisplayName()).arg(getDisplayName()));
    }
    setMovement(BEG);
} //end goingActive

/*private*/ void Warrant::setHeadOfTrain(OBlock* block ) {
        block->setValue(_trainName);
        block->setState(block->getState() | OBlock::RUNNING);
        block->_entryTime = QDateTime::currentMSecsSinceEpoch();//System.currentTimeMillis();
        if (_runMode == MODE_RUN) {
            _speedUtil->enteredBlock(_idxLastOrder, _idxCurrentOrder);
        }
    }
/**
 * @param block Block in the route is going Inactive
 */
//@jmri.InvokeOnLayoutThread
/*protected*/ void Warrant::goingInactive(OBlock* block) {
    if (_runMode == MODE_NONE) {
        return;
    }

    // error if not on Layout thread
//    if (!ThreadingUtil.isLayoutThread()) {
//        log.error("invoked on wrong thread", new Exception("traceback"));
//    }

    int idx = getIndexOfBlockBefore(_idxCurrentOrder, block); // if idx >= 0, it is in this warrant
    if (log->isDebugEnabled()) {
        log->debug(tr("*Block \"%1\" goingInactive. idx= %2, _idxCurrentOrder= %3. warrant= %4").arg(
                block->getDisplayName()).arg(idx).arg(_idxCurrentOrder).arg(getDisplayName()));
    }
    if (idx < _idxCurrentOrder) {
        releaseBlock(block, idx);
    } else if (idx == _idxCurrentOrder) {
        // Train not visible if current block goes inactive
        if (_idxCurrentOrder + 1 < _orders->size()) {
            OBlock* nextBlock = getBlockAt(_idxCurrentOrder + 1);
            if ((nextBlock->getState() & OBlock::UNDETECTED) != 0) {
                if (_engineer != nullptr) {
                    goingActive(nextBlock); // fake occupancy for dark block
                    releaseBlock(block, idx);
                } else {
                    if (_runMode == MODE_LEARN) {
                        _idxCurrentOrder++; // assume train has moved into the dark block
                        fireRunStatus("blockChange", VPtr<OBlock>::asQVariant(block), VPtr<OBlock>::asQVariant(nextBlock));
                    } else if (_runMode == MODE_RUN) {
                        controlRunTrain(ABORT);
                    }
                }
            } else {
                if ((nextBlock->getState() & OBlock::OCCUPIED) != 0 && (_waitForBlock || _waitForWarrant)) {
                    // assume train rolled into occupied ahead block.
                    // Should _idxCurrentOrder & _idxLastOrder be incremented? Better to let user take control?
                    releaseBlock(block, idx);
                    setHeadOfTrain(nextBlock);
                    fireRunStatus("blockChange", VPtr<OBlock>::asQVariant(block), VPtr<OBlock>::asQVariant(nextBlock));
                    log->warn(tr("block \"%1\" goingInactive. train has entered rogue occupied block %2! warrant %3").arg(
                            block->getDisplayName()).arg(nextBlock->getDisplayName()).arg(getDisplayName()));
               } else {
                   bool lost = true;
                   if (_idxCurrentOrder > 0) {
                       OBlock* prevBlock = getBlockAt(_idxCurrentOrder - 1);
                       if ((prevBlock->getState() & OBlock::OCCUPIED) != 0 && this->equals(prevBlock->getWarrant())) {
                           // assume nosed into block, then lost contact
                           _idxCurrentOrder -= 1;  // set head to previous BlockOrder
                           lost = false;
                       }
                   }
                   if (lost) {
                       log->warn(tr("block \"%1\" goingInactive. train is lost! warrant %2").arg(
                                   block->getDisplayName()).arg(getDisplayName()));
                       fireRunStatus("blockChange", VPtr<OBlock>::asQVariant( block), QVariant());
                       if (_engineer != nullptr) {
                           _engineer->setStop(false, true);   // halt and set 0 throttle
                           if (_idxCurrentOrder == 0) {
                               setStoppingBlock(block);
                               _delayStart = true;
                           }
                       }
                   }
               }
            }
        } else {    // at last block
             OBlock* prevBlock = getBlockAt(_idxCurrentOrder - 1);
            if ((prevBlock->getState() & OBlock::OCCUPIED) != 0 && this->equals(prevBlock->getWarrant())) {
                // assume nosed into block, then lost contact
                _idxCurrentOrder -= 1;  // set head to previous BlockOrder
            } else {
                log->warn(tr("block \"%1\" Last Block goingInactive. train is lost! warrant %2").arg(
                        block->getDisplayName()).arg(getDisplayName()));
                if (_engineer != nullptr) {
                    _engineer->setStop(false, false);   // set 0 throttle
                }
            }
        }
    }
} // end goingInactive

/**
 * Deallocates all blocks prior to and including block
 */
/*private*/ void Warrant::releaseBlock(OBlock* block, int idx) {
    /*
     * Only deallocate block if train will not use the block again. Blocks
     * ahead could loop back over blocks previously traversed. That is,
     * don't disturb re-allocation of blocks ahead. Previous Dark blocks do
     * need deallocation
     */
    for (int i = idx; i > -1; i--) {
        bool dealloc = true;
        OBlock* prevBlock = getBlockAt(i);
        for (int j = i + 1; j < _orders->size(); j++) {
            if (prevBlock->equals(getBlockAt(j))) {
                dealloc = false;
            }
        }
        if (dealloc && prevBlock->isAllocatedTo(this)) {
            prevBlock->setValue(QVariant());
            prevBlock->deAllocate(this);
            _totalAllocated = false;
            fireRunStatus("blockRelease", QVariant(), VPtr<OBlock>::asQVariant(block));
        }
    }
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
            _stoppingSignal->addPropertyChangeListener((PropertyChangeListener*)this);
            //connect(_stoppingSignal, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
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
 * If block cannot be allocated, will set a listener on the block->
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
        _stoppingBlock->addPropertyChangeListener((PropertyChangeListener*)this);
        //connect(_stoppingBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent)));
        log->info((blockMsg!=nullptr ? blockMsg : (block->getDisplayName()+" Occupied."))+" Warrant \""+getDisplayName()+
                "\" sets _stoppingBlock= \""+_stoppingBlock->getDisplayName()+"\"");
        return false;
    }
    return true;
}
/**
 *  Finds speed change in advance of move into the next block->
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
    String blkSpeed = nextblock->getBlockSpeed();
    if (blkSpeed=="") {
        blkSpeed = nullptr;
    }
    nextSpeed = _engineer.minSpeedType(nextSpeed, blkSpeed);
    */
    if(_debug) log->debug("getPermissibleSpeedAt(): \""+nextBlock->getDisplayName()+"\" Speed= "+
                            nextSpeed+" - warrant= "+getDisplayName());
    return nextSpeed;
}
/*synchronized*/ /*private*/ void Warrant::cancelDelayRamp() {
        if (_delayCommand != nullptr) {
            _delayCommand->quit = true;;
            log->debug(tr("cancelDelayRamp called on warrant %1").arg(getDisplayName()));
            _delayCommand = nullptr;
        }
    }

/*synchronized*/ /*private*/ void Warrant::rampDelayDone() {
    _delayCommand = nullptr;
}

//@Override
/*public*/ void Warrant::dispose() {
    stopWarrant(false);
    AbstractNamedBean::dispose();
}


/**
 * If block cannot be allocated, will set a listener on the block->
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
//private class CommandDelay extends Thread {
//String nextSpeedType;
//        long _startTime = 0;
//        long _waitTime = 0;
//        boolean quit = false;
//        int _endBlockIdx;
//        boolean _useIndex;

CommandDelay::CommandDelay(QString speedType, long startWait, int endBlockIdx, bool useIndex, Warrant* _warrant) {
 this->_warrant = _warrant;
    nextSpeedType = speedType;
    if (startWait > 0) {
        _waitTime = startWait;
    }
    _endBlockIdx = endBlockIdx;
    _useIndex = useIndex;
    setObjectName("CommandDelay(" + _warrant->getTrainName() +")");
    if (_warrant->log->isDebugEnabled()) {
        _warrant->log->debug(tr("CommandDelay: will wait %1ms, then Ramp to %2 in block %3. warrant %4").arg(
                startWait).arg(speedType).arg(_warrant->getBlockAt(endBlockIdx)->getDisplayName()).arg(_warrant->getDisplayName()));
    }
}

// check if request for a duplicate CommandDelay can be cancelled
bool CommandDelay::doNotCancel(QString speedType, long startWait, int endBlockIdx) {
    if (endBlockIdx == _endBlockIdx && speedType==(nextSpeedType) &&
            (_waitTime - (/*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() - _startTime)) < startWait) {
        return true;
    }
    return false;   // not a duplicate or shortens time wait.
}

//        @Override
//        @SuppressFBWarnings(value = "WA_NOT_IN_LOOP", justification = "notify never called on this thread")
/*public*/ void CommandDelay::process() {
    _startTime = QDateTime::currentMSecsSinceEpoch();//System.currentTimeMillis();
    /*synchronized (this)*/ {
        if (_waitTime > 0.0) {
            try {
                //wait(_waitTime);
          SleeperThread::msleep(_waitTime);
            } catch (InterruptedException ie) {
                if (_warrant->log->isDebugEnabled()) {
                    _warrant->log->debug(tr("CommandDelay interrupt.  Ramp to %1 not done. warrant %2").arg(
                            nextSpeedType).arg(_warrant->getDisplayName()));
                }
                quit = true;
            }
        }
        if (!quit && _warrant->_engineer != nullptr) {
            if (_warrant->log->isDebugEnabled()) {
                _warrant->log->debug(tr("CommandDelay: after wait of %1ms, start Ramp to %2. warrant %3").arg(
                        _waitTime).arg(nextSpeedType).arg(_warrant->getDisplayName()));
            }
            _warrant->_engineer->rampSpeedTo(nextSpeedType, _endBlockIdx, _useIndex);
            // start ramp first
            if (nextSpeedType == (_warrant->Stop) || nextSpeedType == (_warrant->EStop)) {
                _warrant->_engineer->setWaitforClear(true);
            } else {
                _warrant->_curSpeedType = nextSpeedType;
            }
        }
    }
    _warrant->rampDelayDone();
}

 /**
 * Orders are parsed to get any speed restrictions
 * @param idxBlockOrder index of Orders
 * @return Speed type name
 */
/*private*/ QString Warrant::getSpeedTypeForBlock(int idxBlockOrder) {
    BlockOrder* blkOrder = getBlockOrderAt(idxBlockOrder);
    OBlock* block = blkOrder->getBlock();

    QString speedType = getPermissibleSpeedAt(blkOrder);
    setStoppingSignal(idxBlockOrder);
    if (speedType == nullptr) {
        speedType = _curSpeedType;
    } else {
        if (speedType == (Warrant::Stop)) {
            // block speed cannot be Stop, so OK to assume signal
            _waitForSignal = true;
            speedType = Warrant::Stop;
        }
    }

    QString msg = block->allocate(this);
    if (msg != nullptr) {
        if (!this->equals(block->getWarrant())) {
            _waitForWarrant = true;
        } else {
            _waitForBlock = true;
        }
        setStoppingBlock(block);
        speedType = Warrant::Stop;
    } else if ((block->getState() & OBlock::OCCUPIED) != 0) {
        if (idxBlockOrder > _idxCurrentOrder) {
            setStoppingBlock(block);
            _waitForBlock = true;
            speedType = Warrant::Stop;
        }
    } else {
        msg = blkOrder->setPath(this);
        if (msg != nullptr) {
            // when setPath fails, it calls setShareTOBlock
            _waitForWarrant = true;
            speedType = Warrant::Stop;
            _message = msg;
            log->warn(msg);
        }
    }

    if (log->isDebugEnabled()) {
        if (_waitForSignal || _waitForBlock || _waitForWarrant) {
            log->debug (tr("Found \"%1\" speed change of type \"%2\" needed to enter block \"%3\".").arg(
                    (_waitForSignal?"Signal":(_waitForWarrant?"Warrant":"Block"))).arg(speedType).arg(block->getDisplayName()));
        }
    }
    return speedType;
}


/*private*/ float Warrant::getPathLength(BlockOrder* bo) {
    float len = bo->getPath()->getLengthMm();
    if (len < 1.0f) {
        log->warn(tr("Path %1 in block %2 has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.").arg(bo->getPathName()).arg(bo->getBlock()->getDisplayName()));
        len = 100;
    }
    return len;
}

/*
 * position only applies to current block otherwise full path length is available
 */
/*private*/ float Warrant::getAvailableDistance(int idxBlockOrder, int position) {
    BlockOrder* blkOrder = getBlockOrderAt(idxBlockOrder);
    float distAvail;
    float pathLength = getPathLength(blkOrder);
    distAvail = pathLength - _speedUtil->getDistanceTravelled();
    if (log->isDebugEnabled()) {
        log->debug(tr("getAvailableDistance(): from %1 in block \"%2\" distAvail= %3 warrant= %4").arg(
                position).arg(blkOrder->getBlock()->getDisplayName()).arg(distAvail).arg(getDisplayName()));
    }
    return distAvail;
}

/**
 * Get ramp length needed to change speed using the WarrantPreference deltas for
 * throttle increment and time increment.  This should only be used for ramping down.
 * @param idxBlockOrder index of BlockOrder
 * @param toSpeedType Speed type change
 * @return distance in millimeters
 */
/*private*/ float Warrant::rampLengthOfEntrance(int idxBlockOrder, QString toSpeedType) {
/*        if (_curSpeedType.equals(toSpeedType)) {
        return 0.0f;
    }*/
    BlockSpeedInfo* blkSpeedInfo = _speedInfo.at(idxBlockOrder);
    float throttleSetting = blkSpeedInfo->getEntranceSpeed();
    float rampLen = _speedUtil->rampLengthForRampDown(throttleSetting, _curSpeedType, toSpeedType);
    if (_waitForBlock || _waitForWarrant) {    // occupied or foreign track ahead.
        rampLen *= RAMP_ADJUST;    // provide more space to avoid collisions
    } else if (_waitForSignal) {        // signal restricting speed
        rampLen += getBlockOrderAt(idxBlockOrder)->getEntranceSpace(); // signal's adjustment
    }
    return rampLen;
}

/*private*/ /*static*/ float Warrant::RAMP_ADJUST = 1.05f;

/**
 * Called to set the correct speed for the train when the scripted speed
 * must be modified due to a track condition (signaled speed or rogue
 * occupation). Also called to return to the scripted speed after the
 * condition is cleared. Assumes the train occupies the block of the current
 * block order.
 * <p>
 * Looks for speed requirements of this block and takes immediate action if
 * found. Otherwise looks ahead for future speed change needs. If speed
 * restriction changes are required to begin in this block, but the change
 * is not immediate, then determine the proper time delay to start the speed
 * change.
 *
 * @param position estimated position of train inn the block
 * @return false on errors
 */
/*private*/ bool Warrant::setMovement(int position) {
    if (_runMode != Warrant::MODE_RUN || _idxCurrentOrder > _orders->size() - 1) {
        return false;
    }
    if (_engineer == nullptr) {
        controlRunTrain(ABORT);
        return false;
    }
    int runState = _engineer->getRunState();
    BlockOrder* blkOrder = getBlockOrderAt(_idxCurrentOrder);
    OBlock* curBlock = blkOrder->getBlock();
    if (log->isDebugEnabled()) {
        log->debug(tr("!-setMovement(%1) Block\"%2\" runState= %3 current speedType= %4 %5 warrant %6.").arg(
                position).arg(curBlock->getDisplayName()).arg(RUN_STATE[runState]).arg(_curSpeedType,
                (_partialAllocate ? "ShareRoute" : "")).arg(getDisplayName()));
    }

    QString msg = blkOrder->setPath(this);
    if (msg != "") {
        log->error(tr("Train %1 in block \"%2\" but path cannot be set! msg= %3, warrant= %4").arg(
                getTrainName()).arg(curBlock->getDisplayName()).arg(msg).arg(getDisplayName()));
        _engineer->setStop(false, true);   // speed set to 0.0 (not E-top) User must restart
        return false;
    }

    if ((curBlock->getState() & (OBlock::OCCUPIED | OBlock::UNDETECTED)) == 0) {
        log->error(tr("Train %1 expected in block \"%2\" but block is unoccupied! warrant= %3").arg(
                getTrainName()).arg(curBlock->getDisplayName()).arg(getDisplayName()));
        _engineer->setStop(false, true); // user needs to see what happened and restart
        return false;
    }
    // Error checking done.

    // checking situation for the current block
    // _curSpeedType is the speed type train is currently running
    // currentType is the required speed limit for this block
    QString currentType = getPermissibleSpeedAt(blkOrder);
    if (currentType == "") {
        currentType = _curSpeedType;
    }

    float speedSetting = _engineer->getSpeedSetting();
    if (log->isDebugEnabled()) {
        log->debug(tr("Stopping flags: _waitForBlock=%1, _waitForSignal=%2, _waitForWarrant=%3 runState= %4, speedSetting= %5, SpeedType= %6. warrant %7").arg(
                _waitForBlock).arg(_waitForSignal).arg(_waitForWarrant).arg(RUN_STATE[runState]).arg(speedSetting).arg(currentType).arg(getDisplayName()));
    }

    if (_noRamp || _speedInfo.isEmpty()) {
        if (_idxCurrentOrder < _orders->size() - 1) {
            currentType = getSpeedTypeForBlock(_idxCurrentOrder + 1);
            if (_speedUtil->secondGreaterThanFirst(currentType, _curSpeedType)) {
                if (log->isDebugEnabled()) {
                    log->debug(tr("No ramp speed change of \"%1\" from \"%2\" in block \"%3\" warrant= %4").arg(
                            currentType).arg(_curSpeedType).arg(curBlock->getDisplayName()).arg(getDisplayName()));
                }
                _engineer->setSpeedToType(currentType);
                if (currentType != (Stop) && currentType!=(EStop)) {
                    _curSpeedType = currentType;
                }
            }
        }
        if (log->isDebugEnabled()) {
            log->debug(tr("Exit setMovement due to no ramping. warrant= %1").arg(getDisplayName()));
        }
        return true;
    }

    if (currentType != (_curSpeedType)) {
        if (_speedUtil->secondGreaterThanFirst(currentType, _curSpeedType)) {
            // currentType Speed violation!
            // Cancel any delayed speed changes currently in progress.
            cancelDelayRamp();
            NamedBean* signal = blkOrder->getSignal();
            QString name;
            if (signal != nullptr) {
                name = signal->getDisplayName();
            } else {
                name = curBlock->getDisplayName();
            }
            if (currentType ==(Stop) || currentType==(EStop)) {
                _engineer->setStop(currentType == (EStop), false);   // sets speed 0
                log->info(tr("Train missed Stop signal %1 in block \"%2\". warrant= %3").arg(
                            name).arg(curBlock->getDisplayName()).arg(getDisplayName()));
                fireRunStatus("SpeedRestriction", name, currentType); // message of speed violation
                return true; // don't do anything else until stopping condition cleared
            } else {
                _curSpeedType = currentType;
                _engineer->setSpeedToType(currentType); // immediate decrease
                if (log->isDebugEnabled()) {
                    log->debug(tr(
                    "Train %1 moved past required speed of \"%1\" at speed \"%1\" in block \"%1\"! Set speed to %1. warrant= %1").arg(
                            getTrainName()).arg(currentType).arg(_curSpeedType).arg(curBlock->getDisplayName()).arg(currentType,
                            getDisplayName()));
                }
                fireRunStatus("SpeedRestriction", name, currentType); // message of speed violation
             }
        } else {    // speed increases types currentType >_curSpeedType
            // Cancel any delayed speed changes currently in progress.
            cancelDelayRamp();
            if (log->isTraceEnabled()) {
                log->trace(tr("Increasing speed to \"%1\" from \"%2\" in block \"%3\" warrant= %4").arg(
                        currentType).arg(_curSpeedType).arg(curBlock->getDisplayName()).arg(getDisplayName()));
            }
            _curSpeedType = currentType; // cannot be Stop or EStop
            _engineer->rampSpeedTo(currentType, 0, false);
        }
        // continue, there may be blocks ahead that need a speed decrease to begin in this block
    } else {
        if (runState == WAIT_FOR_CLEAR || runState == HALT) {
            // trust that STOP_PENDING or RAMP_HALT makes hard stop unnecessary
            cancelDelayRamp();
            _engineer->setStop(false, false);
            if (log->isDebugEnabled()) {
                log->debug(tr("Set Stop to hold train at block \"%1\" runState= %2, speedSetting= %3.warrant %4").arg(
                        curBlock->getDisplayName()).arg(RUN_STATE[runState]).arg(speedSetting).arg(getDisplayName()));
            }
            fireRunStatus("SpeedChange", _idxCurrentOrder - 1, _idxCurrentOrder); // message reason for hold
            return true;
        } else if (runState == STOP_PENDING || runState == RAMP_HALT) {
            if (log->isDebugEnabled()) {
                log->debug(tr("Hold train at block \"%1\" runState= %2, speedSetting= %3.warrant %4").arg(
                        curBlock->getDisplayName()).arg(RUN_STATE[runState]).arg(speedSetting).arg(getDisplayName()));
            }
            fireRunStatus("SpeedChange", _idxCurrentOrder - 1, _idxCurrentOrder); // message reason for hold
            return true;
        }
        // Continue, look ahead for possible speed modification decrease.
    }

    //look ahead for a speed change slower than the current speed
    // Note: blkOrder still is blkOrder = getBlockOrderAt(_idxCurrentOrder);
    // Do while speedType >= currentType
    int idxBlockOrder = _idxCurrentOrder;
    QString speedType = _curSpeedType;
    float availDist = getAvailableDistance(idxBlockOrder, position);
    // getSpeedTypeForBlock() sets flags if speed change is detected
    while (!_speedUtil->secondGreaterThanFirst(speedType, _curSpeedType) && idxBlockOrder < _orders->size() - 1) {
        speedType = getSpeedTypeForBlock(++idxBlockOrder);  // speed for entry into next block
        availDist += getPathLength(getBlockOrderAt(idxBlockOrder));
    }

    if (idxBlockOrder == _orders->size() - 1) {
        // went through remaining BlockOrders,
        if (!_speedUtil->secondGreaterThanFirst(speedType, _curSpeedType)) {
            // found no speed decreases, except for possibly the last
            float curSpeedRampLen = _speedUtil->rampLengthForRampDown(speedSetting, _curSpeedType, Stop);
            if (log->isDebugEnabled()) {
                if (_curSpeedType == (speedType)) {
                    log->debug(tr("No speed modifications for runState= %1 from %2 found after block \"%3\". RampLen = %4 warrant %5").arg(
                            RUN_STATE[runState]).arg(_curSpeedType).arg(curBlock->getDisplayName()).arg(curSpeedRampLen).arg(getDisplayName()));
                }
            }
            if (curSpeedRampLen > availDist) {
                log->info(tr("Throttle at %1 needs %2mm to ramp to Stop but only %2mm available. May Overrun. Warrant %2").arg(
                        speedSetting).arg(curSpeedRampLen).arg(availDist).arg(getDisplayName()));
                if (runState == STOP_PENDING || runState == RAMP_HALT) {
                    // ramp to stop in progress - no need for further stop calls
                     return true;
                }
            } // else {Space exceeded when ramping down over several blocks is not catastrophic - let it be}
            _waitForBlock = false;
            _waitForSignal = false;
            _waitForWarrant = false;
            return true;
        }
    }

    // blkOrder.getBlock() is the block that must be entered at a speed modified by speedType.
    blkOrder = getBlockOrderAt(idxBlockOrder);
    if (log->isDebugEnabled()) {
        log->debug(tr("Speed decrease to %1 from %2 needed before entering block \"%3\" warrant %4").arg(
                speedType).arg(_curSpeedType).arg(blkOrder->getBlock()->getDisplayName()).arg(getDisplayName()));
    }
    // There is a speed decrease needed before entering the above block
    // From this block, check if there is enough room to make the change
    // using the exit speed of the block. Walk back using previous
    // blocks, if necessary.
    float rampLen = rampLengthOfEntrance(idxBlockOrder, speedType);
    availDist = 0.0f;
    int endBlockIdx = idxBlockOrder - 1;    // index of block where ramp ends

    while (idxBlockOrder > _idxCurrentOrder && rampLen > availDist) {
        // start at block before the block with slower speed type and walk
        // back to current block. Get availDist to cover rampLen
        idxBlockOrder--;
        if (idxBlockOrder == 0) {
            availDist += getAvailableDistance(0, MID);
        } else {
            availDist += getPathLength(getBlockOrderAt(idxBlockOrder));
        }
        rampLen = rampLengthOfEntrance(idxBlockOrder, speedType);
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("availDist= %1, at Block \"%2\" for rampLen= %3. warrant %4").arg(
                availDist).arg(getBlockOrderAt(idxBlockOrder)->getBlock()->getDisplayName()).arg(rampLen).arg(getDisplayName()));
    }

    if (idxBlockOrder > _idxCurrentOrder && rampLen <= availDist) {
        // sufficient ramp room was found before walking all the way back to current block
        // therefore no speed change needed yet.
        if (log->isDebugEnabled()) {
            log->debug(tr("Will decrease speed for runState= %1 to %2 from %3 later at block \"%4\", warrant %5").arg(
                    RUN_STATE[runState]).arg(speedType).arg(_curSpeedType).arg(blkOrder->getBlock()->getDisplayName(),
                    getDisplayName()));
        }
        _waitForBlock = false;
        _waitForWarrant = false;
        _waitForSignal = false;
        return true; // change speed later
    }

    // Need to start a ramp down in the block of _idxCurrentOrder
    blkOrder = getBlockOrderAt(_idxCurrentOrder);
    if (log->isDebugEnabled()) {
        log->debug(tr("Schedule speed change to %1 in block \"%2\" availDist=%3, warrant= %4").arg(
                speedType).arg(blkOrder->getBlock()->getDisplayName()).arg(availDist).arg(getDisplayName()));
    }
    float signalDistAdj = blkOrder->getEntranceSpace() + 50.f; // signal's adjustment plus ~2"
    // find the time when ramp should start in this block, then use thread CommandDelay
    // ramp length to change to modified speed from current speed.

    runState = _engineer->getRunState();
    if (runState == RAMPING_UP) {
        // Interrupt ramp up with ramp down in time to reach 0 speed.
        float endSpeed = _speedUtil->modifySpeed(_engineer->getScriptSpeed(), speedType);
        speedSetting = _engineer->getSpeedSetting();
        RampData* rampdata = _engineer->getRamp()->getRampData();
        QListIterator<float> iter = rampdata->speedIterator(true);
        while (iter.hasNext() && iter.next() < speedSetting) {}

        int timeIncrement = rampdata->getRampTimeIncrement();
        float topSpeed = speedSetting;
        float rampUpDist = 0.0f;
        // Get distances that match where speed changes
        float rampDownDist = _speedUtil->getRampForSpeedChange(topSpeed, endSpeed)->getRampLength();
        long time = 0;
        // continue to ramp up while building the ramp down until distances exceed availDist
        while ((rampDownDist + rampUpDist) <= availDist) {
            time += timeIncrement;
            if (iter.hasNext()) {
                topSpeed = iter.next();
            } else {
                break;
            }
            rampUpDist = _speedUtil->getRampForSpeedChange(speedSetting, topSpeed)->getRampLength();
            rampDownDist = _speedUtil->getRampForSpeedChange(topSpeed, endSpeed)->getRampLength();
            if (_waitForSignal) {
                rampDownDist += signalDistAdj; // signal's adjustment
            }
        }
        if (log->isDebugEnabled()) {
            log->debug(tr("rampDown delayTime= %1, availDist= %2 rampUpDist= %3, from= %4 to %5, rampDownDist= %6, down to %7").arg(
                    time).arg(availDist).arg(rampUpDist).arg(speedSetting).arg(topSpeed).arg(rampDownDist).arg(endSpeed));
        }
        rampSpeedDelay(time, speedType, endBlockIdx);
        fireRunStatus("SpeedChange", _idxCurrentOrder - 1, _idxCurrentOrder);
        return true;
   } else if (rampLen >= availDist) { // not enough room (shouldn't happen) so do ramp/stop immediately
        log->warn(tr("No room for Train %1 ramp to speed \"%2\" in block \"%2\", warrant= %3").arg(
                getTrainName()).arg(speedType).arg(curBlock->getDisplayName()).arg(getDisplayName()));
        _engineer->setSpeedToType(speedType);
        if (speedType!=(Stop) && speedType!=(EStop)) {
            _curSpeedType = speedType;
        }
        fireRunStatus("SpeedChange", _idxCurrentOrder - 1, _idxCurrentOrder);
        return true;
    }

    // otherwise, figure out time to ramp down from script
    // waitSpeed is throttleSpeed when ramp is started. Start with it being at the entrance to the block.
    float waitSpeed = 0;
    long waitTime = 0; // time to wait after entering the block before starting ramp
    // availDist - rampLen = waitDist == waitSpeed * waitTime
    // currently rampLen is rampLengthOfEntrance and availDist is distance to block that has speedType requirement

    // set throttleSpeed to what it is at the start of the block
    bool hasSpeed = false;
    BlockSpeedInfo* blkSpeedInfo = _speedInfo.value(_idxCurrentOrder);
    float throttleSetting;
    if (idxBlockOrder == 0) {
        throttleSetting = 0.0f;
    } else {
        throttleSetting = blkSpeedInfo->getEntranceSpeed();
        waitSpeed = _speedUtil->getTrackSpeed(_speedUtil->modifySpeed(throttleSetting, _curSpeedType));
        waitTime = qRound((availDist - rampLen) / waitSpeed);
        hasSpeed = true;
    }
    float timeRatio; // time adjustment for current speed type.
    if (qAbs(throttleSetting - waitSpeed) > .0001f) {
        timeRatio = throttleSetting / waitSpeed;
    } else {
        timeRatio = 1.0f;
    }

    long speedTime = 0; // time running at a given speed until next speed change
    int startIdx = blkSpeedInfo->getFirstIndex();
    int endIdx = blkSpeedInfo->getLastIndex();
    for (int i = startIdx; i <= endIdx; i++) {
        ThrottleSetting* ts = _commands->value(i);
        if (hasSpeed) {
            speedTime += ts->getTime() * timeRatio;
            if (speedTime >= waitTime) {
                break;
            }
        }
        QString cmd = ts->getCommand().toUpper();
        if (cmd == ("SPEED")) {
            throttleSetting = (ts->getValue().toFloat()); // new speed
            if (throttleSetting > .0001f) {
                hasSpeed = true;
                waitSpeed = _speedUtil->getTrackSpeed(_speedUtil->modifySpeed(throttleSetting, _curSpeedType));
                rampLen = _speedUtil->rampLengthForRampDown(throttleSetting, _curSpeedType, speedType);
                long nextWait = qRound((availDist - rampLen) / waitSpeed);
                if (speedTime >= nextWait) {
                    waitTime = nextWait;
                    break;
                }
            } else {
                hasSpeed = false;
            }
        }
    }

    if (log->isDebugEnabled()) {
        log->debug(tr(" waitTime= %1, availDist= %2 waitSpeed= %3, rampLen= %4, ramp start speed= %5").arg(
                waitTime).arg(availDist).arg(waitSpeed).arg(rampLen));
    }
    rampSpeedDelay(waitTime, speedType, endBlockIdx);
    return true;
}

/*private*/ void Warrant::rampSpeedDelay (long waitTime, QString speedType, int endBlockIdx) {
    /*synchronized(this)*/ {
       if (_delayCommand != nullptr) {
           if (_delayCommand->doNotCancel(speedType, waitTime, endBlockIdx)) {
               return;
           }
           cancelDelayRamp();
       }
    }
    if (waitTime <= 0) {
        _engineer->rampSpeedTo(speedType, endBlockIdx, true);
        if (speedType ==(Stop) || speedType ==(EStop)) {
            _engineer->setWaitforClear(true);
        } else {
            _curSpeedType = speedType;
        }
    } else {    // cancelDelayRamp has been called
        /*synchronized(this) */{
            _delayCommand = new CommandDelay(speedType, waitTime, endBlockIdx, true, this);
            QThread* thread = new QThread();
            connect(thread, SIGNAL(started()), _delayCommand, SLOT(process()));
            connect(_delayCommand, SIGNAL(finished()),thread, SLOT(quit()));
            connect(_delayCommand, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            _delayCommand->moveToThread(thread);
            thread->start();
        }
    }
}
/**
 * {@inheritDoc}
 * <p>
 * This implementation tests that
 * {@link jmri.NamedBean#getSystemName()}
 * is equal for this and obj.
 * To allow a warrant to run with sections, DccLocoAddress is included to test equality
 *
 * @param obj the reference object with which to compare.
 * @return {@code true} if this object is the same as the obj argument;
 *         {@code false} otherwise.
 */
//@Override
/*public*/ bool Warrant::equals(QObject* obj) {
    if (obj == nullptr) return false; // by contract

    if (qobject_cast< Warrant*>(obj)) {  // NamedBeans are not equal to things of other types
        Warrant* b = (Warrant*) obj;
        DccLocoAddress* addr = this->_speedUtil->getDccAddress();
        if (addr == nullptr) {
            if (b->_speedUtil->getDccAddress() != nullptr) {
                return false;
            }
            return (this->getSystemName() == (b->getSystemName()));
        }
        return (this->getSystemName() == (b->getSystemName()) && addr == (b->_speedUtil->getDccAddress()));
    }
    return false;
}

/**
 * {@inheritDoc}
 *
 * @return hash code value is based on the system name and DccLocoAddress.
 */
//@Override
/*public*/ uint Warrant::hashCode() {
    //return (getSystemName().concat(_speedUtil->getDccAddress()->toString())).hashCode();
 return qHash(mSystemName+_speedUtil->getDccAddress()->toString(),qGlobalQHashSeed());
}
