#include "acelatrafficcontroller.h"
#include "loggerfactory.h"
#include "acelalistener.h"
/**
 * Converts Stream-based I/O to/from Acela messages.
 * <p>
 * The "SerialInterface" side sends/receives message objects.
 * <p>
 * The connection to an AcelaPortController is via a pair of Streams, which
 * then carry sequences of characters for transmission. Note that this
 * processing is handled in an independent thread.
 * <p>
 * This handles the state transitions, based on the necessary state in each
 * message.
 * <p>
 * Handles initialization, polling, output, and input for multiple Serial Nodes.
 * @see jmri.jmrix.AbstractMRNodeTrafficController
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Bob Jacobsen, Dave Duchamp, multiNode extensions, 2004
 * @author Bob Coleman Copyright (C) 2007. 2008 Based on CMRI serial example,
 * modified to establish Acela support.
 */
///*public*/  class AcelaTrafficController extends AbstractMRNodeTrafficController implements AcelaInterface {

/**
 * Create a new AcelaTrafficController instance.
 */
/*public*/ AcelaTrafficController::AcelaTrafficController(QObject* parent) : AbstractMRNodeTrafficController(parent) {
    //super();

    // entirely poll driven, so reduce Polling interval
    mWaitBeforePoll = 25;  // default = 25
    setAllowUnexpectedReply(true);

    AbstractMRNodeTrafficController::init(0, 1024); // 1024 is an artificial limit but economically reasonable maxNode upper limit

    reallyReadyToPoll = false;           // Need to not start polling until we are ready
    needToPollNodes = true;              // Need to poll and create corresponding nodes
    needToInitAcelaNetwork = true;       // Need to poll and create corresponding nodes
    needToCreateNodesState = 0;          // Need to initialize system and then poll
    acelaTrafficControllerState = false; //  Flag to indicate which state we are in:
                                         //  false == Initializing Acela Network
                                         //  true == Polling Sensors
}

// The methods to implement the AcelaInterface

//@Override
/*public*/  /*synchronized*/ void AcelaTrafficController::addAcelaListener(AcelaListener* l) {
    this->addListener(l);
}

//@Override
/*public*/  /*synchronized*/ void AcelaTrafficController::removeAcelaListener(AcelaListener* l) {
    this->removeListener(l);
}


/**
 * Get minimum address of an Acela node as set on this TrafficController.
 * @return minimum node address.
 */
/*public*/  int AcelaTrafficController::getMinimumNodeAddress() {
    return minNode;
}

/**
 * Get maximum number of Acela nodes as set on this TrafficController.
 * @return max number of nodes.
 */
/*public*/  int AcelaTrafficController::getMaximumNumberOfNodes() {
    return maxNode;
}

/*public*/  bool AcelaTrafficController::getAcelaTrafficControllerState() {
    return acelaTrafficControllerState;
}

/*public*/  void AcelaTrafficController::setAcelaTrafficControllerState(bool newstate) {
    acelaTrafficControllerState = newstate;
}

/*public*/  /*synchronized*/ void AcelaTrafficController::resetStartingAddresses() {
    currentOutputAddress = -1;
    currentSensorAddress = -1;
}

/*public*/  bool AcelaTrafficController::getAcelaSensorsState() {
    return acelaSensorsState;
}

/*public*/  void AcelaTrafficController::setAcelaSensorsState(bool newstate) {
    acelaSensorsState = newstate;
}

/*public*/  void AcelaTrafficController::incrementAcelaSensorInitCount() {
    acelaSensorInitCount++;
    log->debug(tr("Number of Acela sensors initialized: %1").arg(getAcelaSensorInitCount()));
}

/*public*/  int AcelaTrafficController::getAcelaSensorInitCount() {
    return acelaSensorInitCount;
}

/*public*/  /*synchronized*/ bool AcelaTrafficController::getNeedToPollNodes() {
    return needToPollNodes;
}

/*public*/  /*synchronized*/ void AcelaTrafficController::setNeedToPollNodes(bool newstate) {
    needToPollNodes = newstate;
}

/*public*/  bool AcelaTrafficController::getReallyReadyToPoll() {
    return reallyReadyToPoll;
}

/*public*/  void AcelaTrafficController::setReallyReadyToPoll(bool newstate) {
    log->debug(tr("setting really ready to poll (nodes): %1").arg(newstate));
    reallyReadyToPoll = newstate;
}

/**
 * Get access to the system connection memo associated with this traffic
 * controller.
 *
 * @return associated systemConnectionMemo object
 */
/*public*/  AcelaSystemConnectionMemo* AcelaTrafficController::getSystemConnectionMemo() {
    return (mMemo);
}

/**
 * Set the system connection memo associated with this traffic controller.
 *
 * @param m associated systemConnectionMemo object
 */
/*public*/  void AcelaTrafficController::setSystemConnectionMemo(AcelaSystemConnectionMemo* m) {
    mMemo = m;
}

/**
 * public  method to register an Acela node->
 * @param node which node to register.
 */
/*public*/  void AcelaTrafficController::registerAcelaNode(AcelaNode* node) {
    /*synchronized (this)*/ {
        AbstractMRNodeTrafficController::registerNode(node);

        // no node validity checking because at this point the node may not be fully defined
        setMustInit(node, false);  // Do not normally need to init Acela nodes.
        if (node->getNumOutputBitsPerCard() == 0) {
            node->setStartingOutputAddress(-1);
            node->setEndingOutputAddress(-1);
        } else {
            if (currentOutputAddress == -1) {  // Need to use -1 to correctly identify bit address 0
                currentOutputAddress = 0;
            }
            node->setStartingOutputAddress(currentOutputAddress);
            currentOutputAddress = currentOutputAddress + node->getNumOutputBitsPerCard() - 1;
            node->setEndingOutputAddress(currentOutputAddress);
            currentOutputAddress = currentOutputAddress + 1;
        }
        if (node->getNumSensorBitsPerCard() == 0) {
            node->setStartingSensorAddress(-1);
            node->setEndingSensorAddress(-1);
        } else {
            if (currentSensorAddress == -1) {  // Need to use -1 to correctly identify bit address 0
                currentSensorAddress = 0;
            }
            node->setStartingSensorAddress(currentSensorAddress);
            currentSensorAddress = currentSensorAddress + node->getNumSensorBitsPerCard() - 1;
            node->setEndingSensorAddress(currentSensorAddress);
            currentSensorAddress = currentSensorAddress + 1;
        }
    }
}

/**
 * public  method to set up for initialization of an Acela node->
 * @param node which node to initialize.
 */
/*public*/  void AcelaTrafficController::initializeAcelaNode(AcelaNode* node) {
    /*synchronized (this)*/ {
        setMustInit(node, true);
        node->initNode();
    }
}

/**
 * public  method to identify an AcelaNode from its bit address.
 * <p>
 * Note: nodeAddress is numbered from 0
 *
 * @param bitAddress address to query.
 * @param isSensor true to use start sensor address, false to use start output address.
 * @return '-1' if an AcelaNode with the specified address was not found
 */
/*public*/  int AcelaTrafficController::lookupAcelaNodeAddress(int bitAddress, bool isSensor) {
    for (int i = 0; i < getNumNodes(); i++) {
        AcelaNode* node = (AcelaNode*) getNode(i);
        if (isSensor) {
            if ((bitAddress >= node->getStartingSensorAddress())
                    && (bitAddress <= node->getEndingSensorAddress())) {
                return (i);
            }
        } else {
            if ((bitAddress >= node->getStartingOutputAddress())
                    && (bitAddress <= node->getEndingOutputAddress())) {
                return (i);
            }
        }
    }
    return (-1);
}

//@Override
/*protected*/ AbstractMRMessage* AcelaTrafficController::enterProgMode() {
    log->warn("enterProgMode does NOT make sense for Acela serial");
    return nullptr;
}

//@Override
/*protected*/ AbstractMRMessage* AcelaTrafficController::enterNormalMode() {
    // can happen during error recovery, null is OK
    return nullptr;
}
#if 0
/**
 * Forward an AcelaMessage to all registered AcelaInterface listeners.
 * {@inheritDoc}
 */
@Override
protected void forwardMessage(AbstractMRListener client, AbstractMRMessage m) {
    ((AcelaListener) client).message((AcelaMessage) m);
}

/**
 * Forward an AcelaReply to all registered AcelaInterface listeners.
 * {@inheritDoc}
 */
@Override
protected void forwardReply(AbstractMRListener client, AbstractMRReply m) {
    ((AcelaListener) client).reply((AcelaReply) m);
}

AcelaSensorManager mSensorManager = null;

/*public*/  void setSensorManager(AcelaSensorManager m) {
    mSensorManager = m;
}

AcelaTurnoutManager mTurnoutManager = null;

/*public*/  void setTurnoutManager(AcelaTurnoutManager m) {
    mTurnoutManager = m;
}

/**
 * Handle initialization, output and polling for Acela Nodes from within
 * the running thread.
 */
@Override
protected synchronized AbstractMRMessage pollMessage() {
    // Need to wait until we have read config file
    if (!reallyReadyToPoll) {
        return null;
    }

    if (needToInitAcelaNetwork) {
        if (needToCreateNodesState == 0) {
            if (needToPollNodes) {
                new AcelaNode(0, Acelanode->AC,this);
                log.info("Created a new Acela Node [0] in order to poll Acela network: " + Acelanode->AC);
            }
            curAcelaNodeIndex = SPECIALNODE;
            AcelaMessage m = AcelaMessage.getAcelaResetMsg();
            log.debug("send Acela reset (init step 1) message: {}", m);
            m.setTimeout(1000);  // wait for init to finish (milliseconds)
            mCurrentMode = NORMALMODE;
            needToCreateNodesState++;
            return m;
        }
        if (needToCreateNodesState == 1) {
            AcelaMessage m = AcelaMessage.getAcelaOnlineMsg();
            log.debug("send Acela Online (init step 2) message: {}", m);
            m.setTimeout(1000);  // wait for init to finish (milliseconds)
            mCurrentMode = NORMALMODE;
            needToCreateNodesState++;
            return m;
        }
        if (needToPollNodes) {
            if (needToCreateNodesState == 2) {
                AcelaMessage m = AcelaMessage.getAcelaPollNodesMsg();
                log.debug("send Acela poll nodes message: {}", m);
                m.setTimeout(100);  // wait for init to finish (milliseconds)
                mCurrentMode = NORMALMODE;
                needToInitAcelaNetwork = false;
                needToPollNodes = false;
                return m;
            }
        } else {
            needToInitAcelaNetwork = false;
            setAcelaTrafficControllerState(true);
        }
    }

    // ensure validity of call
    if (getNumNodes() <= 0) {
        return null;
    }

    // move to a new node
    curAcelaNodeIndex++;
    if (curAcelaNodeIndex >= getNumNodes()) {
        curAcelaNodeIndex = 0;
    }

    // ensure that each node is initialized
    AcelaNode node = (AcelaNode) getNode(curAcelaNodeIndex);
    if (node->hasActiveSensors) {
        for (int s = 0; s < node->sensorbitsPerCard; s++) {
            if (node->sensorNeedInit[s] && !node->sensorHasBeenInit[s]) {
                AcelaMessage m = AcelaMessage.getAcelaConfigSensorMsg();
                int tempiaddr = s + node->getStartingSensorAddress();
                byte tempbaddr = (byte) (tempiaddr);
                m.setElement(2, tempbaddr);
                m.setElement(3, node->sensorConfigArray[s]);
                log.debug("send Acela Config Sensor message: {}", m);
                incrementAcelaSensorInitCount();
                m.setTimeout(100);  // wait for init to finish (milliseconds)
                mCurrentMode = NORMALMODE;
                node->sensorHasBeenInit[s] = true;
                node->sensorNeedInit[s] = false;
                return m;
            }
        }
    }

    // send Output packet if needed
    if (getNode(curAcelaNodeIndex).mustSend()) {
        getNode(curAcelaNodeIndex).resetMustSend();
        AbstractMRMessage m = getNode(curAcelaNodeIndex).createOutPacket();
        m.setTimeout(100);  // no need to wait for output to answer
        log.debug("request write command to send: {}", m);
        mCurrentMode = NORMALMODE;
        return m;
    }

    // Trying to serialize Acela initialization so system is stable
    // So we will not poll sensors or send om/off commands until we have
    // initialized all of the sensor modules -- this can take several seconds
    // during a cold system startup.
    if ((currentSensorAddress == 0) || (currentSensorAddress != getAcelaSensorInitCount())) {
        return null;
    }

    if (acelaSensorsState) {    //  Flag to indicate whether we have an active sensor and therefore need to poll
        AcelaMessage m = AcelaMessage.getAcelaPollSensorsMsg();
        log.debug("send Acela poll sensors message: {}", m);
        m.setTimeout(100);  // wait for init to finish (milliseconds)
        mCurrentMode = NORMALMODE;
        return m;
    } else {
        // no Sensors (inputs) are active for this node
        return null;
    }
}

@Override
protected synchronized void handleTimeout(AbstractMRMessage m, AbstractMRListener l) {
    // don't use super behavior, as timeout to init, transmit message is normal
    // inform node, and if it resets then reinitialize
    if (getNode(curAcelaNodeIndex).handleTimeout(m, l)) {
        setMustInit(curAcelaNodeIndex, true);
    }
}

@Override
protected synchronized void resetTimeout(AbstractMRMessage m) {
    // don't use super behavior, as timeout to init, transmit message is normal
    // and inform node
    getNode(curAcelaNodeIndex).resetTimeout(m);
}

@Override
protected AbstractMRListener pollReplyHandler() {
    return mSensorManager;
}

/**
 * Forward a pre-formatted message to the actual interface.
 * {@inheritDoc}
 */
@Override
/*public*/  void sendAcelaMessage(AcelaMessage m, AcelaListener reply) {
    sendMessage(m, reply);
}

@Override
protected AbstractMRReply newReply() {
    return new AcelaReply();
}

@Override
protected bool endOfMessage(AbstractMRReply msg) {
    // our version of loadChars doesn't invoke this, so it shouldn't be called
    return true;
}

@Override
protected void loadChars(AbstractMRReply msg, DataInputStream istream) throws java.io.IOException {
    int char1 = readByteProtected(istream)&0xFF;
    if (char1 == 0x00) {  // 0x00 means command processed OK.
        msg.setElement(0, char1);
        //  0x01 means that the Acela network is offline
        //  0x02 means that an illegal address was sent
        //  0x03 means that an illegal command was sent
        //  For now we are not going to check for these
        //  three conditions since they will only catch
        //  programming errors (versus runtime errors)
        //  and the checking may mess up the polling replies.

    } else {
        if ((char1 == 0x81) || (char1 == 0x82)) {
            //  0x81 means that a sensor has changed.
            //  0x82 means that communications has been lost
            //  For now we will check for these two
            //  conditions since they do represent
            //  runtime errors at the risk that in a very very
            //  large Acela network the checking may mess
            //  up the polling replies.
            msg.setElement(0, char1);
        } else {
            //  We have a reply to a poll (either pollnodes
            //  or pollsensors).  The first byte will be the
            //  length of the reply followed by the
            //  indicated number of bytes.
            //
            //  For now we will send the reply to the sensor
            //  manager.  In the future we should really have
            //  an Acela Network Manager and an Acela Sensor
            //  Manager -- but, for now, we 'know' which state
            //  we are in.
            for (int i = 0; i < char1; i++) {
                byte charn = readByteProtected(istream);
                msg.setElement(i, charn);
            }
        }
    }
}

@Override
protected void waitForStartOfReply(DataInputStream istream) throws java.io.IOException {
    // Just return
}

/**
 * For each sensor node call markChanges.
 * @param r reply to use in sensor update.
 */
/*public*/  void updateSensorsFromPoll(AcelaReply r) {
    for (int i = 0; i < getNumNodes(); i++) {
        AcelaNode node = (AcelaNode) getNode(i);
        if (node->getSensorBitsPerCard() > 0) {
            node->markChanges(r);
        }
    }
}
#endif
/*private*/ /*final*/ /*static*/ Logger* AcelaTrafficController::log = LoggerFactory::getLogger("AcelaTrafficController");
