#ifndef ABSTRACTMRNODETRAFFICCONTROLLER_H
#define ABSTRACTMRNODETRAFFICCONTROLLER_H

#include <abstractmrtrafficcontroller.h>
#include "abstractnode.h"

class AbstractMRNodeTrafficController : public AbstractMRTrafficController
{
 public:
  explicit AbstractMRNodeTrafficController(QObject *parent = nullptr);
  /*public*/  int getNumNodes();
  /*public*/  void registerNode(AbstractNode* node);
  /*public*/  /*synchronized*/ AbstractNode* getNode(int index);
  /*synchronized*/ /*public*/  AbstractNode* getNodeFromAddress(int addr);
  /*public*/  /*synchronized*/ void deleteNode(int nodeAddress);

 private:
  static Logger* log;
  /*private*/ QVector<bool> mustInit;

 protected:
  /*protected*/ void init(int minNode, int maxNode);
  /*protected*/ int minNode = -1;
  /*protected*/ int maxNode = -1;
  /**
   * Total number of SerialNodes registered with this TrafficController.
   * Incremented as Serial Nodes are created and registered.
   * Corresponds to the next available address in {@link #nodeArray}.
   */
  /*protected*/ volatile int numNodes = 0;
  /*protected*/ QVector<AbstractNode*> nodeArray;
  /*protected*/ bool getMustInit(int i);
  /*protected*/ void setMustInit(int i, bool v);
  /*protected*/ void setMustInit(AbstractNode* node, bool v);
  /**
   * Working variable for keeping track of the active node, if any.
   */
  /*protected*/ int curSerialNodeIndex = 0;

};

#endif // ABSTRACTMRNODETRAFFICCONTROLLER_H
