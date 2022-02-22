#include "defaultcabsignal.h"
#include "loggerfactory.h"
#include "blockmanager.h"
#include "instancemanager.h"
#include "vptr.h"
#include "addressedidtag.h"
#include "path.h"
#include "layoutblockmanager.h"
#include "abstractidtag.h"

/**
 * Default implementation of a Cab Signal Object, describing the state of the
 * track ahead relative to a locomotive with a given address.  This is
 * effectively a mobile signal mast.
 *
 * @author Steve Young Copyright (C) 2018
 * @author Paul Bender Copyright (C) 2019
 */
// /*public*/ class DefaultCabSignal implements CabSignal, PropertyChangeListener {


/*public*/ DefaultCabSignal::DefaultCabSignal(LocoAddress* address, QObject *parent) : QObject(parent){
   _address = address;
   pcs = new SwingPropertyChangeSupport(this, nullptr);

}

/**
 * A method for cleaning up the cab signal
 */
//@Override
/*public*/ void DefaultCabSignal::dispose(){
    if (_nextMast != nullptr) {
        _nextMast->removePropertyChangeListener(_cconSignalMastListener);
    }
   _address = nullptr;
   _currentBlock = nullptr;
   _nextBlock = nullptr;
   _nextMast = nullptr;
   _cabSignalActive = true;
   _masterPausedButtonActive = false;
}

/**
 * Get the LocoAddress associated with the consist
 *
 * @return the cab signal address
 */
//@Override
/*public*/ LocoAddress* DefaultCabSignal::getCabSignalAddress(){
    return _address;
}

/**
 * Set the Block of the locomotive
 *
 * @param position is a Block the locomotive is in.
 */
//@Override
/*synchronized*/ /*public*/ void DefaultCabSignal::setBlock(Block* position){
    log->debug(tr("CabSignal for %1 set block %2").arg(getCabSignalAddress()->toString()).arg(position->toDebugString()));
    Block* oldCurrentBlock = _currentBlock;

    if(_currentBlock!=nullptr){
       _currentBlock->removePropertyChangeListener((PropertyChangeListener*)this);
    }
    _currentBlock = position;

    if(_currentBlock!=nullptr) {
       _currentBlock->addPropertyChangeListener((PropertyChangeListener*)this);
       if(_currentBlock != (oldCurrentBlock)) {
          firePropertyChange("CurrentBlock",VPtr<Block>::asQVariant(_currentBlock),VPtr<Block>::asQVariant(oldCurrentBlock));

       }

   } else {
       // currentblock is null, notify if old block was not.
       if(oldCurrentBlock!=nullptr){
          firePropertyChange("CurrentBlock",VPtr<Block>::asQVariant(_currentBlock),VPtr<Block>::asQVariant(oldCurrentBlock));
       }
   }
   getNextBlock(); // calculate the next block and fire an appropriate property change.
   // calculate the next mast and fire an appropriate property change.
   forwardCabSignalToLayout();
}

/**
 * Set the Block of the locomotive by searching the block list.
 */
//@Override
/*synchronized*/ /*public*/ void DefaultCabSignal::setBlock()
{
    BlockManager* bmgr = (BlockManager*)InstanceManager::getDefault("BlockManager");
    QSet</*Block*/NamedBean*> blockSet = bmgr->AbstractManager::getNamedBeanSet();
    LocoAddress* addr = getCabSignalAddress();
    for (/*Block*/NamedBean* bv : blockSet) {
     Block* blockVal = (Block*)bv->self();
        if ( !blockVal->getValue().isNull() ) {
            QVariant val = blockVal->getValue();
            log->debug(tr("CabSignal for %1 searching block %2 value %3").arg(
                       addr->toString()).arg(blockVal->toDebugString()).arg(val.toString()));
            //if (val instanceof AddressedIdTag)
            if(VPtr<AddressedIdTag>::asPtr(val))
            {
             AddressedIdTag* obj = VPtr<AddressedIdTag>::asPtr(val);
                if( (((DccLocoAddress*)obj)->toString() ==
                     (addr->toString())))
                {
                   setBlock(blockVal);
                   return;
                }
            } else if (VPtr<LocoAddress>::asPtr(blockVal->getValue())->equals(addr) ||
                blockVal->getValue().toString() == (addr->toString()) ||
                blockVal->getValue().toString() == ("" + addr->getNumber())) {
                setBlock(blockVal);
                return;
            }
        }
    }
    // address not found in any block, set block to null
    setBlock(nullptr);
}

/**
 * Get the Block position of the locomotive associated with the cab signal.
 *
 * @return The current Block position
 */
//@Override
/*synchronized*/ /*public*/ Block* DefaultCabSignal::getBlock(){
    return _currentBlock;
}

/**
 * Get the Next Block the locomotive is expected to enter.
 * This value is calculated from the current block and direction
 * of travel.
 *
 * @return The next Block position
 */
//@Override
/*public*/ Block* DefaultCabSignal::getNextBlock(){
    Block* oldNextBlock = _nextBlock;
    if(getBlock()==nullptr){
       _nextBlock = nullptr; // no current block, so can't have a next block.
    } else {
      _nextBlock = nextBlockOnPath(getBlock(),getBlock()->getDirection());
    }

    if(_nextBlock!=nullptr) {
        if(!_nextBlock->equals(oldNextBlock)) {
           firePropertyChange("NextBlock",VPtr<Block>::asQVariant(_nextBlock),VPtr<Block>::asQVariant(oldNextBlock));
        }
    } else {
        // currentNextBlock is null, notify if old next block was not.
        if(oldNextBlock!=nullptr){
           firePropertyChange("NextBlock",VPtr<Block>::asQVariant(_nextBlock),VPtr<Block>::asQVariant(oldNextBlock));
        }
    }
    return _nextBlock;
}

/*private*/ Block* DefaultCabSignal::nextBlockOnPath(Block* current, int fromdirection){
    QVector<Path*>* thispaths = current->getPaths();
    for (/*final*/ Path* testpath : *thispaths) {
        if (testpath->checkPathSet()) {
            Block* blockTest = testpath->getBlock();
            int dirftTest = testpath->getFromBlockDirection();
            int dirtoTest = testpath->getToBlockDirection();
            if ((((fromdirection & Path::NORTH) != 0) && ((dirtoTest & Path::NORTH) != 0)) ||
                (((fromdirection & Path::SOUTH) != 0) && ((dirtoTest & Path::SOUTH) != 0)) ||
                (((fromdirection & Path::EAST) != 0) && ((dirtoTest & Path::EAST) != 0)) ||
                (((fromdirection & Path::WEST) != 0) && ((dirtoTest & Path::WEST) != 0)) ||
                (((fromdirection & Path::CW) != 0) && ((dirtoTest & Path::CW) != 0)) ||
                (((fromdirection & Path::CCW) != 0) && ((dirtoTest & Path::CCW) != 0)) ||
                (((fromdirection & Path::LEFT) != 0) && ((dirtoTest & Path::LEFT) != 0)) ||
                (((fromdirection & Path::RIGHT) != 0) && ((dirtoTest & Path::RIGHT) != 0)) ||
                (((fromdirection & Path::UP) != 0) && ((dirtoTest & Path::UP) != 0)) ||
                (((fromdirection & Path::DOWN) != 0) && ((dirtoTest & Path::DOWN) != 0)))
            { // most reliable
                blockTest->setDirection(dirtoTest);
                return blockTest;
            }
            if ((fromdirection & dirftTest) == 0) { // less reliable
                blockTest->setDirection(dirtoTest);
                return blockTest;
            }
            if ((fromdirection != dirftTest)){ // least reliable but copes with 180 degrees
                blockTest->setDirection(dirtoTest);
                return blockTest;
            }
        }
    }
  return nullptr;
}

/**
 * Get the Next Signal Mast the locomotive is expected to pass.
 * This value is calculated from the current block and direction
 * of travel.
 *
 * @return The next SignalMast position
 */
//@Override
/*public*/ SignalMast* DefaultCabSignal::getNextMast(){
    SignalMast* oldNextMast = _nextMast;
    if (_nextMast != nullptr) {
        _nextMast->removePropertyChangeListener(_cconSignalMastListener);
    }
    _nextMast=nullptr;
    if(getBlock()!=nullptr){
       LayoutBlockManager* lbm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");

        Block* b = getBlock();
        Block* nB = getNextBlock();
        while(_nextMast == nullptr && nB !=nullptr ) {
            _nextMast = lbm->getFacingSignalMast(b, nB);
            b = nB;
            nB = nextBlockOnPath(b,b->getDirection());
        }
        if ( _nextMast == nullptr) {
            // use block b which is the last non-null block in the path
            _nextMast = lbm->getSignalMastAtEndBumper(b,nullptr);
        }

        if ( _nextMast != nullptr)
        {
            // add signal changelistener
//                _nextMast->SwingPropertyChangeSupport::addPropertyChangeListener(_cconSignalMastListener = (PropertyChangeEvent e) -> {
            // aspect changed?, need to notify
//                firePropertyChange("MastChanged",e.getNewValue(),e.getOldValue());
//                forwardCabSignalToLayout();
//                });
         _nextMast->addPropertyChangeListener((PropertyChangeListener*)this);
        }
    }
    if(_nextMast!=nullptr) {
        if(!_nextMast->equals(oldNextMast)) {
            firePropertyChange("NextMast",VPtr<SignalMast>::asQVariant(_nextMast),VPtr<SignalMast>::asQVariant(oldNextMast));
        }
    } else {
        // currentNextMast is null, notify if old next mast was not.
        if(oldNextMast!=nullptr){
           firePropertyChange("NextMast",VPtr<SignalMast>::asQVariant(_nextMast),VPtr<SignalMast>::asQVariant(oldNextMast));
        }
    }
    return _nextMast;
}

/**
 * Forward the current cab signal value to the layout.
 */
//@Override
/*public*/ void DefaultCabSignal::forwardCabSignalToLayout() {
    if (!isCabSignalActive() ) {
        return;
    }
    if (_masterPausedButtonActive) {
        return;
    }

    LocoAddress* locoaddr = getCabSignalAddress();
    SignalMast* mast = getNextMast();

    if (mast != nullptr) {
        log->debug(tr("cab %1 aspect %2").arg(locoaddr->toString()).arg(mast->getAspect()));
    }
    // and forward the message on to the layout.
    forwardAspectToLayout();
}

/**
 * Forward the command to the layout that sets the displayed signal
 * aspect for this address
 */
/*protected*/ void DefaultCabSignal::forwardAspectToLayout(){
    // this method is to be over-written by subclasses that actually
    // talk to layout hardware.
}


/*
 * get whether this cab signal is on or off
 *
 * @return true if on, false if off
 */
//@Override
/*public*/ bool DefaultCabSignal::isCabSignalActive(){
    return _cabSignalActive;
}

/*
 * set whether this cab signal is on or off
 *
 * @param active true if on, false if off
 */
//@Override
/*public*/ void DefaultCabSignal::setCabSignalActive(bool active){
    _cabSignalActive = active;
    if(_cabSignalActive) {
       getNextMast(); // refreshes block, mast, and sends if master button not paused
    }
    else {
        resetLayoutCabSignal(); // send data invalid to layout
    }
}

/*
 * Set when initialised and when Master PAUSED button is toggled
 *
 * @param active true if paused, false if resumed
 */
//@Override
/*public*/ void DefaultCabSignal::setMasterCabSigPauseActive (bool active) {
    _masterPausedButtonActive = active;
    if ( !isCabSignalActive() ){
        return; // if cabsig has already been disabled no action needed
    }
    if ( _masterPausedButtonActive ) {
        log->debug("master paused");
        resetLayoutCabSignal(); // send data invalid to layout
    }
    else {
        log->debug("master not paused");
        getNextMast(); // refreshes block, mast, and sends if single cabsig enabled
    }
}

/**
 * Forward the command to the layout that clears any displayed signal
 * for this address
 */
/*protected*/ void DefaultCabSignal::resetLayoutCabSignal(){
    // this method is to be over-written by subclasses that actually
    // talk to layout hardware.
}


/**
 * Add a listener for consist events
 *
 * @param l is a PropertyChangeListener object
 */
//@Override
/*public*/ /*synchronized*/ void DefaultCabSignal::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->SwingPropertyChangeSupport::addPropertyChangeListener(l);
}

/**
 * Remove a listener for cab signal events
 *
 * @param l is a PropertyChangeListener object
 */
//@Override
/*public*/ /*synchronized*/ void DefaultCabSignal::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

/*protected*/ void DefaultCabSignal::firePropertyChange(QString p, QVariant old, QVariant n) {
    log->debug(tr("sending property %1 new value %2 old value %3").arg(p).arg(old.toString()).arg(n.toString()));
    pcs->firePropertyChange(p, old, n);
}

//PropertyChangeListener interface
//@Override
/*public*/ void DefaultCabSignal::propertyChange(PropertyChangeEvent* event){
   if(qobject_cast<Block*>(event->getSource()))
   {
    if (event->getPropertyName() == ("value"))
    {
      setBlock(); // change the block.
    }

    // block value is changed before direction is set
    if ((event->getPropertyName() == ("state")) || (event->getPropertyName() == ("direction"))) {
       // update internal state to cascade changes.
       getNextBlock();
       forwardCabSignalToLayout();
    }
   } else if(qobject_cast<SignalMast*>(event->getSource())) {
       // update internal state to cascade changes.
       forwardCabSignalToLayout();
   }
   if(qobject_cast<SignalMast*>(event->getSource()))
   {
    //_nextMast->SwingPropertyChangeSupport::addPropertyChangeListener(_cconSignalMastListener = (PropertyChangeEvent e) -> {
    // aspect changed?, need to notify
    firePropertyChange("MastChanged",event->getNewValue(),event->getOldValue());
    forwardCabSignalToLayout();
   }
}

/*private*/ /*static*/ /*final*/ Logger* DefaultCabSignal::log = LoggerFactory::getLogger("DefaultCabSignal");

