#ifndef ACELATRAFFICCONTROLLER_H
#define ACELATRAFFICCONTROLLER_H
#include "abstractmrnodetrafficcontroller.h"
#include "acelanode.h"
#include "acelasystemconnectionmemo.h"
#include "acelalistener.h"

class AcelaTrafficController : public AbstractMRNodeTrafficController
{
  Q_OBJECT
 public:
  AcelaTrafficController(QObject* parent = nullptr);
  /*public*/  /*synchronized*/ void addAcelaListener(AcelaListener* l);
  /*public*/  /*synchronized*/ void removeAcelaListener(AcelaListener* l);
  /*public*/  int getMinimumNodeAddress();
  /*public*/  int getMaximumNumberOfNodes();
  /*public*/  bool getAcelaTrafficControllerState();
  /*public*/  void setAcelaTrafficControllerState(bool newstate);
  /*public*/  /*synchronized*/ void resetStartingAddresses();
  /*public*/  bool getAcelaSensorsState();
  /*public*/  void setAcelaSensorsState(bool newstate) ;
  /*public*/  void incrementAcelaSensorInitCount();
  /*public*/  int getAcelaSensorInitCount();
  /*public*/  /*synchronized*/ bool getNeedToPollNodes() ;
  /*public*/  /*synchronized*/ void setNeedToPollNodes(bool newstate);
  /*public*/  bool getReallyReadyToPoll();
  /*public*/  void setReallyReadyToPoll(bool newstate);
  /*public*/  AcelaSystemConnectionMemo* getSystemConnectionMemo();
  /*public*/  void setSystemConnectionMemo(AcelaSystemConnectionMemo* m);
  /*public*/  void registerAcelaNode(AcelaNode* node);
  /*public*/  void initializeAcelaNode(AcelaNode* node);
  /*public*/  int lookupAcelaNodeAddress(int bitAddress, bool isSensor);

 private:
  static Logger* log;
  /**
   * Reference to the system connection memo.
   */
  AcelaSystemConnectionMemo* mMemo = nullptr;

  /*transient*/ int curAcelaNodeIndex = -1;   // cycles over defined nodes when pollMessage is called

  /*transient*/ /*private*/ int currentOutputAddress = -1;   // Incremented as Acela Nodes are created and registered
  // Corresponds to next available output address in nodeArray
  // Start at -1 to avoid issues with bit address 0
  /*transient*/ /*private*/ int currentSensorAddress = -1;   // Incremented as Acela Nodes are created and registered
  // Corresponds to next available sensor address in nodeArray
  // Start at -1 to avoid issues with bit address 0

  /*private*/ bool acelaTrafficControllerState = false;    //  Flag to indicate which state we are in:
  //  false == Initializing Acela Network
  //  true == Polling Sensors
  /*private*/ bool reallyReadyToPoll = false;   //  Flag to indicate that we are really ready to poll nodes
  /*transient*/ /*private*/ bool needToPollNodes = true;   //  Flag to indicate that nodes have not yet been created
  /*private*/ bool needToInitAcelaNetwork = true;   //  Flag to indicate that Acela network must be initialized
  /*private*/ int needToCreateNodesState = 0;     //  Need to do a few things:
  //      Reset Acela Network
  //      Set Acela Network Online
  //      Poll for Acela Nodes (and create and register the nodes)

  /*private*/ bool acelaSensorsState = false;    //  Flag to indicate whether we have an active sensor and therefore need to poll:
  //  false == No active sensor
  //  true == Active sensor, need to poll sensors

  /*private*/ int acelaSensorInitCount = 0;     //  Need to count sensors initialized so we know when we can poll them

  /*private*/ static const int SPECIALNODE = 0;         //  Needed to initialize system

 protected:
  /*protected*/ AbstractMRMessage* enterProgMode();
  /*protected*/ AbstractMRMessage* enterNormalMode();

};

#endif // ACELATRAFFICCONTROLLER_H
