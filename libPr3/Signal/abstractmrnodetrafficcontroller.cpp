#include "abstractmrnodetrafficcontroller.h"
#include "loggerfactory.h"
/**
 * Abstract Traffic Controller base class for those implementations that track a
 * set of nodes.
 * <p>
 * The nodes are descendents of {@link jmri.jmrix.AbstractNode}. Provides node
 * management services, but no additional protocol.
 *
 * @author Bob Jacobsen Copyright (C) 2008
 */
///*public*/  abstract class AbstractMRNodeTrafficController extends AbstractMRTrafficController {

/**
 * Create a new unnamed MRNodeTrafficController instance.
 */
/*public*/ AbstractMRNodeTrafficController:: AbstractMRNodeTrafficController(QObject* parent)
 : AbstractMRTrafficController(parent)
{
}

/**
 * Initialize based on number of first and last nodes.
 * @param minNode lowest node number, usually 0
 * @param maxNode highest node number
 */
/*protected*/ void AbstractMRNodeTrafficController::init(int minNode, int maxNode) {
    this->minNode = minNode;
    this->maxNode = maxNode;

    nodeArray = QVector<AbstractNode*>(this->maxNode + 1); // numbering from 0
    mustInit =  QVector<bool>(this->maxNode + 1);

    // initialize content
    for (int i = 0; i <= this->maxNode; i++) {
        mustInit[i] = true;
    }
}



/**
 * Does a given node need to have initialization data sent?
 *
 * @param i the node address (number)
 * @return true if initialization data is required
 */
/*protected*/ bool AbstractMRNodeTrafficController::getMustInit(int i) {
    return mustInit[i];
}

/**
 * Mark whether a given node needs to have initialization data sent.
 *
 * @param i the node index
 * @param v true if set to require sending initialization data
 */
/*protected*/ void AbstractMRNodeTrafficController::setMustInit(int i, bool v) {
    mustInit[i] = v;
}

/*protected*/ void AbstractMRNodeTrafficController::setMustInit(AbstractNode* node, bool v) {
    for (int i = 0; i < numNodes; i++) {
        if (nodeArray[i] == node) {
            // found node - set up for initialization
            mustInit[i] = v;
            return;
        }
    }
}

/**
 * Get the total number of currently registered nodes.
 *
 * @return the number of registerd nodes on this connection
 */
/*public*/  int AbstractMRNodeTrafficController::getNumNodes() {
    return numNodes;
}

/**
 * Register a Serial node on this TrafficController.
 *
 * @param node the node object to register
 */
//@SuppressFBWarnings(value = "VO_VOLATILE_INCREMENT", justification = "Method itself is synchronized to protect numNodes")
/*public*/  void AbstractMRNodeTrafficController::registerNode(AbstractNode* node) {
   /* synchronized (this)*/ {
        // no validity checking because at this point the node may not be fully defined
        nodeArray[numNodes] = node;
        mustInit[numNodes] = true;
        numNodes++;
    }
}

/**
 * Get the Serial node for a given index as registered with this
 * TrafficController.
 *
 * @param index the index number of the node. To cycle through all nodes,
 *          begin with index=0, and increment your index at each call.
 * @return the node at index, 'null' when index exceeds the number of defined nodes
 */
/*public*/  /*synchronized*/ AbstractNode* AbstractMRNodeTrafficController::getNode(int index) {
    if (index >= numNodes) {
        return nullptr;
    }
    return nodeArray[index];
}

/**
 * Identify a SerialNode from its node address.
 *
 * @param addr the node address, numbered from 0
 * @return the node at node address, 'null' if a SerialNode with the
 * specified address was not found
 */
/*synchronized*/ /*public*/  AbstractNode* AbstractMRNodeTrafficController::getNodeFromAddress(int addr) {
    for (int i = 0; i < numNodes; i++) {
        if (getNode(i)->getNodeAddress() == addr) {
            return (getNode(i));
        }
    }
    return (nullptr);
}


/**
 * Delete a SerialNode by node address.
 *
 * @param nodeAddress address number for the node to be deleted
 */
//@SuppressFBWarnings(value = "VO_VOLATILE_INCREMENT", justification = "Method itself is synchronized to protect numNodes")
/*public*/  /*synchronized*/ void AbstractMRNodeTrafficController::deleteNode(int nodeAddress) {
    // find the serial node
    int index = 0;
    for (int i = 0; i < numNodes; i++) {
        if (nodeArray[i]->getNodeAddress() == nodeAddress) {
            index = i;
        }
    }
    if (index == curSerialNodeIndex) {
        log->warn("Deleting the serial node active in the polling loop");
        // just a warning, unlikely event and probably OK in any case.
    }
    // delete the node from the node list
    numNodes--;
    if (index < numNodes) {
        // did not delete the last node, shift
        for (int j = index; j < numNodes; j++) {
            nodeArray[j] = nodeArray[j + 1];
        }
    }
    nodeArray[numNodes] = nullptr;
}

/*private*/ /*final*/ /*static*/ Logger* AbstractMRNodeTrafficController::log = LoggerFactory::getLogger("AbstractMRNodeTrafficController");
