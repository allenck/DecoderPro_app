#include "abstractnode.h"
#include "loggerfactory.h"

/**
 * Basic implementation of a node for JMRI protocol support.
 * <p>
 * Integrated with {@link AbstractMRNodeTrafficController}.
 *
 * @author Bob Jacobsen Copyright 2008
 */
// /*public*/  /*abstract*/ class AbstractNode  {


    /**
     * Create a new instance of AbstractNode.
     */
    /*public*/  AbstractNode::AbstractNode(QObject* parent) : QObject(parent){
    }


    /**
     * public  method to return the node address.
     *
     * @return node address number
     */
    /*public*/  int AbstractNode::getNodeAddress() {
        return (nodeAddress);
    }

    /**
     * public  method to set the node address. Address range is checked in
     * subclasses.
     *
     * @param address address index to set in node
     * @throws IllegalArgumentException if out of range
     */
    /*public*/  void AbstractNode::setNodeAddress(int address) {
        if (checkNodeAddress(address)) {
            nodeAddress = address;
        } else {
            log->error(tr("illegal node address: %1").arg(address));
            nodeAddress = 0;
            throw new IllegalArgumentException("Attempt to set address to invalid value: " + QString::number(address));
        }
    }

    /**
     * Check for valid address with respect to range, etc.
     *
     * @param address node number to check.
     * @return true if valid
     */
//    abstract protected bool checkNodeAddress(int address);

    /**
     * Create the needed Initialization packet (AbstractMRMessage) for this
     * node.
     *
     * @return the packet, or 'null' if not needed
     */
//    abstract /*public*/  AbstractMRMessage createInitPacket();

    /**
     * Create a Transmit packet (AbstractMRMessage) to send current state.
     * @return packet to send current node state.
     */
//    abstract /*public*/  AbstractMRMessage createOutPacket();

    /**
     * Are any sensors present, and hence will this node need to be polled?
     *
     * @return 'true' if at least one sensor is active for this node
     */
//    abstract /*public*/  bool getSensorsActive();

    /**
     * Deal with a timeout in the transmission controller.
     *
     * @param m message that didn't receive a reply
     * @param l listener that sent the message
     * @return true if initialization is required
     */
//    abstract /*public*/  bool handleTimeout(AbstractMRMessage m, AbstractMRListener l);

    /**
     * A reply was received, so there was no timeout, do any needed processing.
     *
     * @param m message received that has reset the timeout and is waiting to be handled
     */
//    abstract /*public*/  void resetTimeout(AbstractMRMessage m);

    /**
     * Get Must Send state.
     * @return state of needSend flag.
     */
    /*public*/  bool AbstractNode::mustSend() {
        return needSend;
    }

    /**
     * public  to reset state of needSend flag. Subclasses may override to
     * enforce conditions.
     */
    /*public*/  void AbstractNode::resetMustSend() {
        needSend = false;
    }

    /**
     * public  to set state of needSend flag.
     */
    /*public*/  void AbstractNode::setMustSend() {
        needSend = true;
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractNode::log = LoggerFactory::getLogger("AbstractNode");
