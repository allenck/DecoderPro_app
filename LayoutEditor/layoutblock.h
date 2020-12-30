#ifndef LAYOUTBLOCK_H
#define LAYOUTBLOCK_H
#include "abstractnamedbean.h"
#include "sensor.h"
#include <QColor>
#include "block.h"
//#include "mylayouteditor.h"
#include "memory.h"
#include "turnout.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include "layoutconnectivity.h"
#include "layoutblockconnectivitytools.h"
#include "liblayouteditor_global.h"
#include "windowlistener.h"
#include <QRunnable>
#include "layouttrackexpectedstate.h"
#include "blockeditaction.h"
#include "beanitempanel.h"
#include "namedbeancombobox.h"
#include "jcolorchooser.h"
#include "splitbuttoncolorchooserpanel.h"
#include "layoutblockmanager.h"
#include "layouteditor.h"
#include "instancemanager.h"
#include "beanedititem.h"

class ConnectivityUtil;
class JActionEvent;
class JmriJFrame;
class RoutingPacket;
class LayoutEditorAuxTools;
class Adjacencies;
class ThroughPaths;
class Routes;
class LayoutTurnout;
class LayoutConnectivity;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutBlock : public AbstractNamedBean
{
    friend class LevelXing;
    friend class LayoutEditor;
    friend class LayoutBlockManager;
    Q_OBJECT
public:
    //explicit LayoutBlock(QObject *parent = 0);
    /*public*/ bool enableAddRouteLogging;// = false;
    /*public*/ bool enableUpdateRouteLogging;// = false;
    /*public*/ bool enableDeleteRouteLogging;// = false;
    /*public*/ bool enableSearchRouteLogging;// = false;
    ///*public*/ int routingMethod = HOPCOUNT;
    /*
     * Creates a LayoutBlock object.
     *
     * Note: initializeLayoutBlock() must be called to complete the process. They are split
     *       so  that loading of panel files will be independent of whether LayoutBlocks or
     *		 Blocks are loaded first.
     */
    /*public*/ LayoutBlock(QString sName, QString uName="",QObject *parent = 0);
    // persistent instances variables (saved between sessions)
    /*public*/ QString blockName;// = "";
    /*public*/ QString lbSystemName;// = "";
    /*public*/ QString occupancySensorName;// = "";
    /*public*/ QString memoryName;// = "";
    /*public*/ int occupiedSense;// = Sensor.ACTIVE;
    /*public*/ QColor blockTrackColor;// = Color.black;
    /*public*/ QColor blockOccupiedColor;// = Color.black;
    /*public*/ QColor blockExtraColor;// = Color.black;
    // constants
    /*public*/ static const int OCCUPIED = Block::OCCUPIED;
    /*public*/ static const int EMPTY = 0x04;//Block::UNOCCUPIED;
    /*public*/ static const int UNKNOWN = /*Sensor::UNKNOWN*/0x01;  // must be a different bit

    /**
     * Accessor methods
     */
    /*public*/ QString getId();
    /*public*/ QColor getBlockTrackColor();
    /*public*/ void setBlockTrackColor(QColor color);
    /*public*/ QColor getBlockOccupiedColor();
    /*public*/ void setBlockOccupiedColor(QColor color);
    /*public*/ QColor getBlockExtraColor();
    /*public*/ void setBlockExtraColor(QColor color);
    /*public*/ bool getUseExtraColor();
    /*public*/ void setUseExtraColor(bool b);
    /*public*/ void incrementUse();
    /*public*/ void decrementUse();
    /*public*/ int getUseCount();
    /**
     *  Keeps track of LayoutEditor panels that are using this LayoutBlock
     */
    /*public*/ void addLayoutEditor(LayoutEditor* panel);
    /*public*/ void deleteLayoutEditor(LayoutEditor* panel);
    /*public*/ bool isOnPanel(LayoutEditor* panel);
    /**
     *  Redraws panels using this layout block
     */
    /*public*/ void redrawLayoutBlockPanels();
    /**
     * Validates that the supplied occupancy sensor name corresponds to an existing sensor
     *   and is unique among all blocks.  If valid, returns the sensor and sets the block
     *   sensor name in the block.  Else returns NULL, and does nothing to the block.
     * This method also converts the sensor name to upper case if it is a system name.
     */
    /*public*/ Sensor*  validateSensor(QString sensorName, /*Component*/ QWidget* openFrame);
    /**
     * Validates that the memory name corresponds to an existing memory.
     *   If valid, returns the memory. Else returns NULL, and notifies the user.
     * This method also converts the memory name to upper case if it is a system name.
     */
    /*public*/ Memory* validateMemory(QString memName, /*Component*/ QWidget* openFrame);
    /**
     * Returns the color for drawing items in this block.  Returns color
     *   based on block occupancy.
     */
    /*public*/ QColor getBlockColor();
    /**
     * Get the jmri.Block corresponding to this LayoutBlock
     */
    /*public*/ Block* getBlock() {return block;}
    /**
     * Returns Memory name
    */
    /*public*/ QString getMemoryName() {return (memoryName);}

    /**
     * Returns Memory
    */
    /*public*/ Memory* getMemory() {return (memory);}

    /**
     * Add Memory by name
     */
    /*public*/ void setMemoryName(QString name);
    /*public*/ void setMemory(Memory* m, QString name);

    /**
     * Returns occupancy Sensor name
    */
    /*public*/ QString getOccupancySensorName();
    /**
     * Returns occupancy Sensor
    */
    /*public*/ Sensor* getOccupancySensor();
    /**
     * Add occupancy sensor by name
     */
    /*public*/ void setOccupancySensorName(QString name);

    /**
     * Check/Update Path objects for the attached jmri.Block
     * <P>
     * If multiple panels are present, Paths are set according to the panel with
     *		the highest connectivity (most LayoutConnectivity objects);
     */
    /*public*/ void updatePaths();


    /*public*/ int getState();
    // dummy for completion of NamedBean interface
    /*public*/ void setState(int i) override;

    LayoutBlock* getLayoutBlock();
    static QVector<int>* updateReferences;// = new QVector<int>();
    /**
     * Get/Set occupied sense
     */
    /*public*/ int getOccupiedSense();
    /*public*/ void setOccupiedSense(int sense);
    /**
     * Test block occupancy
     */
    /*public*/ int getOccupancy();
    /**
     * Get the Layout Editor panel with the highest connectivity to this Layout Block
     */
    /*public*/ LayoutEditor* getMaxConnectedPanel();
    /**
     * Check/Update Path objects for the attached jmri.Block using the
     *		connectivity in the specified Layout Editor panel.
     */
    //@SuppressWarnings("NULL")
    /*public*/ void updatePathsUsingPanel(LayoutEditor* panel);
    /**
     * Sets/resets update of memory name when block goes from occupied to unoccupied or vice versa.
     * If set is true, name update is suppressed.
     * If set is false, name update works normally.
     */
    /*public*/ void setSuppressNameUpdate(bool set);
    /*public*/ void enableDeleteRouteLog();
    /*public*/ void disableDeleteRouteLog();
    /*public*/ static const int RESERVED = 0x08;

    void stateUpdate();
    static long time;//=0;
    /**
     * Removes this object from display and persistance
     */
    void remove();
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive();
    /*public*/ bool useDefaultMetric();
    /*public*/ void useDefaultMetric(bool boo);
    /**
    * Sets a metric cost against a block, this is used in the calculation of a
    * path between two location on the layout, a lower path cost is always preferred
    * For Layout blocks defined as Mainline the default metric is 50.
    * For Layout blocks defined as a Siding the default metric is 200.
    */
    /*public*/ void setBlockMetric(int m);
    /**
    * Returns the layout block metric cost
    */
    /*public*/ int getBlockMetric();

    //re work this so that is makes beter us of existing code.
    //This is no longer required currently, but might be used at a later date.
    /*public*/ void addAllThroughPaths();
    /**
    * Get the number of routes that the block has registered.
    */
    /*public*/ int getNumberOfRoutes();
    /**
    * Get the direction of route i.
    */
    /*public*/ int getRouteDirectionAtIndex(int i);
    /**
    * Get the destination block at route i
    */
    /*public*/ Block* getRouteDestBlockAtIndex(int i);
    /**
    * Get the next block at route i
    */
    /*public*/ Block* getRouteNextBlockAtIndex(int i);
    /**
    * Get the hop count of route i.<br>
    * The Hop count is the number of other blocks that we traverse to get to the destination
    */
    /*public*/ int getRouteHopCountAtIndex(int i);
    /**
    * Get the length of route i.<br>
    * The length is the combined length of all the blocks that we traverse to get to the destination
    */
    /*public*/ float getRouteLengthAtIndex(int i);
    /**
    * Get the metric/cost at route i
    */
    /*public*/ int getRouteMetric(int i);
    /**
    * Gets the state (Occupied, unoccupied) of the destination layout block at index i
    */
    /*public*/ int getRouteState(int i);
    /**
    * Is the route to the destination potentially valid from our block.
    */
    /*public*/ bool getRouteValid(int i);
    /**
    * Gets the state of the destination layout block at index i as a string
    */
    /*public*/ QString getRouteStateAsString(int i);
    int getRouteIndex(Routes* r);
    /**
    * Returns the number of layout blocks to our desintation block going from the
    * next directly connected block.  If the destination block and nextblock are
    * the same and the block is also registered as a neighbour then 1 is returned.
    * If no valid route to the destination block can be found via the next block
    * then -1 is returned.  If more than one route exists to the destination then
    * the route with the lowest count is returned.
    */
    /*public*/ int getBlockHopCount(Block* destination, Block* nextBlock);
    /**
    * Returns the metric to our desintation block going from the
    * next directly connected block.  If the destination block and nextblock are
    * the same and the block is also registered as a neighbour then 1 is returned.
    * If no valid route to the destination block can be found via the next block
    * then -1 is returned.  If more than one route exists to the destination then
    * the route with the lowest count is returned.
    */
    /*public*/ int getBlockMetric(Block* destination, Block* nextBlock);
    /**
    * Returns the distance to our desintation block going from the
    * next directly connected block.  If the destination block and nextblock are
    * the same and the block is also registered as a neighbour then 1 is returned.
    * If no valid route to the destination block can be found via the next block
    * then -1 is returned.  If more than one route exists to the destination then
    * the route with the lowest count is returned.
    */
    /*public*/ float getBlockLength(Block* destination, Block* nextBlock);
    /**
    * Returns the number of valid through paths on this block.
    */
    /*public*/ int getNumberOfThroughPaths();
    /**
    * Returns the source block at index i
    */
    /*public*/ Block* getThroughPathSource(int i);
    /**
    * Returns the destination block at index i
    */
    /*public*/ Block* getThroughPathDestination(int i);
    /**
    * Is the through path at index i active
    */
    /*public*/ bool isThroughPathActive(int i);

    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
    ///*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    void updateNeighbourPacketFlow(Block* neighbour, int flow);
    Adjacencies* getAdjacency(Block* blk);
    void notifyNeighboursOfRemoval(QVector<Routes*>* routesToRemove, Block* notifyingblk);
    void addNeighbour(Block* addBlock, int direction, int workingDirection);
    bool informNeighbourOfAttachment(LayoutBlock* lBlock, Block* block, int workingDirection);
    int determineAdjPacketFlow(int our, int neigh);
    void informNeighbourOfValidRoutes(Block* newblock);
    void removeAdjacency(Path* removedPath);
    void removeAdjacency(LayoutBlock* layoutBlock);
    void removeRouteFromNeighbour(LayoutBlock* src, RoutingPacket* update);
    /*public*/ void printValidThroughPaths();
    /*public*/ void printAdjacencies();
    /*public*/ void printRoutes();
    /*public*/ void printRoutes(QString blockName);
    /*public*/ Block* getNextBlock(Block* destBlock, int direction);
    /*public*/ Block* getNextBlock(Block* previousBlock, Block* destBlock);
    /*public*/ int getConnectedBlockRouteIndex(Block* destBlock, int direction);
    /*public*/ int getNextBlockByIndex(Block* destBlock, int direction, int offSet);
    /*public*/ int getNextBlockByIndex(Block* previousBlock, Block* destBlock, int offSet);
    /*public*/ int getNextBestBlock(Block* previousBlock, Block* destBlock, QList<int> excludeBlock, int routingMethod);
    Routes* getRouteByDestBlock(Block* blk);
    QVector<Routes*>* getRouteByNeighbour(Block* blk);
    int getAdjacencyPacketFlow(Block* blk);
    Routes* getValidRoute(Block* nxtBlock, Block* dstBlock);
    /*public*/ bool isRouteToDestValid(Block* protecting, Block* destination);
    /*public*/ QVector<Block*>* getActiveNextBlocks(Block* source);
    /*public*/ Path* getThroughPathSourcePathAtIndex(int i);
    /*public*/ Path* getThroughPathDestinationPathAtIndex(int i);
    /*public*/ bool validThroughPath(Block* sourceBlock, Block* destinationBlock);
    /*public*/ int getThroughPathIndex(Block* sourceBlock, Block* destinationBlock);
    QVector<Routes*>* getDestRoutes(Block* dstBlock);
    QVector<Routes*>* getNextRoutes(Block* nxtBlock);
    void updateRoutingInfo(LayoutBlock* src, RoutingPacket* update);
    Routes* getBestRoute(Block* dest);
    /*public*/ int getNeighbourDirection(LayoutBlock* neigh);
    /*public*/ int getNeighbourDirection(Block* neighbourBlock);
    void addRouteFromNeighbour(LayoutBlock* src, RoutingPacket* update);
    QVector<Routes*>* removeRouteRecievedFromNeighbour(Block* removedBlock);
    void notifiedNeighbourNoLongerMutual(LayoutBlock* srcBlock);
    int getBlockStatus();
    void updateRoutesToNeighbours(QVector<Block*>* messageRecipients, Routes* ro, RoutingPacket* update);
    void addRouteToNeighbours(Routes* ro);

    /*public*/ static QString colorToString(QColor color);
    /*public*/ static QColor stringToColor(QString string);

    /*public*/ int getNumberOfNeighbours();
    /*public*/ Block* getNeighbourAtIndex(int i);
    /*public*/ int getNeighbourDirection(int i);
    /*public*/ int getNeighbourMetric(int i);
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);

signals:
    
public slots:
    /**
     * Handle tasks when block changes
     */
    void handleBlockChange(PropertyChangeEvent* e);
    void handleBlockChange(QString pName, int o, int val);
#if 0
    void sensorDebounceGlobalCheck_clicked();
    void blockEditCancelPressed(ActionEvent* a = 0);
    void blockEditDonePressed(ActionEvent* a = 0);
#endif
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    //static bool InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() = true;
    QStringList working;// = {"Bi-Directional", "Receive Only", "Send Only"};

    QVector<JComboBox*> neighbourDir;
    LayoutEditorAuxTools* auxTool;//=NULL;
    ConnectivityUtil* connection;//=NULL;
    bool layoutConnectivity;// = true;
    void addThroughPath(Adjacencies* adj);
    QVector<Adjacencies*>* neighbours;// = new QVector<Adjacencies>();

    //We keep a track of what is paths are active, only so that we can easily mark
    //which routes are also potentially valid
    QVector <ThroughPaths*>* activePaths;
    QVector<ThroughPaths*>* throughPaths;// = new QVector<ThroughPaths>();
    // A sub class that holds valid routes through the block.
    //Possibly want to store the path direction in here as well.
    // or we store the ref to the path, so we can get the directions.
    QVector<Routes*>* routes;// = new QVector<Routes>();
    QString decodePacketFlow(int value);
    /*adds a path between two blocks, but without spec a panel*/
    void addThroughPath(Block* srcBlock, Block* dstBlock);
    void addThroughPath(Block* srcBlock, Block* dstBlock, LayoutEditor* panel);
    /*private*/ void addThroughPathPostChecks(Block* srcBlock, Block* dstBlock, QList<LayoutTrackExpectedState<LayoutTurnout *> *> stod);
    bool isValidNeighbour(Block* blk);
    //We keep this vector list so that we only keep one instance of a registered listener
    /*protected*/ QVector<PropertyChangeListener*>* listeners;// = new QVector<PropertyChangeListener*>();
    QMutex mutex;
    Logger* log;
    // operational instance variables (not saved to disk)
    /*private*/ int useCount = 0;
    /*private*/ NamedBeanHandle<Sensor*>* occupancyNamedSensor; //NULL;
    /*private*/ NamedBeanHandle<Memory*>* namedMemory = nullptr;

    friend class CreateEditBlock;
    /*private*/ Memory* memory; //NULL;
    /*private*/ Block* block; //NULL;
    ///*private*/ int maxBlockNumber; //0;
    /*private*/ QVector<LayoutEditor*>* panels; //new QVector<LayoutEditor*>();  // panels using this block
    /*private*/ PropertyChangeListener* mBlockListener; //NULL;
    /*private*/	int jmriblknum; //1;
    /*private*/ bool useExtraColor; //false;
    /*private*/ bool suppressNameUpdate; //false;
    /*private*/ void updateBlockPaths(QVector<LayoutConnectivity*>* c, LayoutEditor* panel);
    /*private*/ bool compareConnectivity(QVector<LayoutConnectivity*>* main, QVector<LayoutConnectivity*>* test);
    /**
     * Deactivate block listener for redraw of panels and update of memories on
     *	change of state
     */
    /*private*/ void deactivateBlock();

    // variables for Edit Layout Block pane
    /*JmriJFrame*/ QMainWindow* editLayoutBlockFrame; //NULL;
    /*Component*/ QWidget* callingPane;
    /*JTextField*/ QLineEdit* sensorNameField; //new /*JTextField*/ QLineEdit(16);
    /*JTextField*/ QLineEdit* sensorDebounceInactiveField; //new /*JTextField*/ QLineEdit(5);
    /*JTextField*/ QLineEdit* sensorDebounceActiveField; //new /*JTextField*/ QLineEdit(5);
    /*JCheckBox*/ QCheckBox* sensorDebounceGlobalCheck; //new /*JCheckBox*/ QCheckBox(rb.getQString("OccupancySensorUseGlobal"));
    /*JTextField*/ QLineEdit* memoryNameField; //new /*JTextField*/ QLineEdit(16);
    /*JTextField*/ QLineEdit* metricField; //new /*JTextField*/ QLineEdit(10);
    /*JComboBox*/ QComboBox* senseBox; //new /*JComboBox*/ QComboBox();
    /*JCheckBox*/ QCheckBox* permissiveCheck; //new /*JCheckBox*/ QCheckBox("Permissive Working Allowed");
    /*private*/ /*final*/ NamedBeanComboBox/*<Memory*>*/* memoryComboBox = nullptr;// = new NamedBeanComboBox<>(
    //InstanceManager.getDefault(MemoryManager.class), null, DisplayOptions.DISPLAYNAME);

    int senseActiveIndex;
    int senseInactiveIndex;
    /*private*/ JColorChooser* trackColorChooser = nullptr;
    /*private*/ JColorChooser* occupiedColorChooser = nullptr;
    /*private*/ JColorChooser* extraColorChooser = nullptr;
    /*JComboBox*/ QComboBox* trackColorBox; //new /*JComboBox*/ QComboBox();
    /*JComboBox*/ QComboBox* occupiedColorBox; //new /*JComboBox*/ QComboBox();
    /*JComboBox*/ QComboBox* extraColorBox; //new /*JComboBox*/ QComboBox();
    /*JComboBox*/ QComboBox* blockSpeedBox; //new /*JComboBox*/ QComboBox();
    /*JLabel*/ QLabel* blockUseLabel;//= new /*JLabel*/ QLabel();
    /*JButton*/ QPushButton* blockEditDone;
    /*JButton*/ QPushButton* blockEditCancel;
    bool editOpen; //false;
    /*JComboBox*/ QComboBox* attachedBlocks; //new /*JComboBox*/ QComboBox();
    //might want to use the jmri ordered hashtable, so that we can add at the top
    // and remove at the bottom.
    QVector<int>* actedUponUpdates;// = new QVector<int>();
    bool pathActive;
    /**
     *  The code below relates to the layout block routing protocol
     */
    bool active;// = true;

    /**
    * Used to set the block metric based upon the track segment that the block is
    * associated with if the (200 if Side, 50 if Main).  If the block is assigned
    * against multiple track segments all with different types then the highest
    * type will be used.
    * In theory no reason why it couldn't be a compromise!
    */
    void setBlockMetric();
    //This works out our direction of route flow correctly
    void addAdjacency(Path* addPath);
    bool defaultMetric;// = true;
    /*final*/ const static int ADDITION = 0x00;
    const static int UPDATE = 0x02;
    const static int REMOVAL = 0x04;

    const static int RXTX = 0x00;
    const static int RXONLY = 0x02;
    const static int TXONLY = 0x04;
    const static int NONE = 0x08;
    int metric; //= 100
    int getNextPacketID();
    bool updatePacketActedUpon(int packetID);
#if 0
    /*private*/ void setColorCombo(QComboBox* colorCombo,QColor color);
    /*private*/ QColor getSelectedColor(QComboBox* colorCombo);
    /**
     * Methods and data to support initialization of color Combo box
     */
    QStringList colorText;// = {"Black","DarkGray","Gray",
//            "LightGray","White","Red","Pink","Orange",
//            "Yellow","Green","Blue","Magenta","Cyan"};
    QList<QColor> colorCode;// = {Color->black,Color->darkGray,Color->gray,
//            Color->lightGray,Color->white,Color->red,Color->pink,Color->orange,
//            Color->yellow,Color->green,Color->blue,Color->magenta,Color->cyan};
    int numColors;// = 13;  // number of entries in the above arrays
    /*private*/ void initializeColorCombo(QComboBox* colorCombo, QColor c);
#endif
    /*public*/ QString getNeighbourPacketFlowAsString(int i);
    /*public*/ bool isNeighbourMutual(int i);
    int getNeighbourIndex(Adjacencies* adj);
    //When a route is created this will check to see if the through path that this
    //route relates to is active
    bool checkIsRouteOnValidThroughPath(Routes* r);
    //A procedure that will go through all the routes and refresh the valid flag
    /*public*/ void refreshValidRoutes();
    void updateActiveThroughPaths(ThroughPaths* tp, bool active);
    //Sets the valid flag for routes that are on a valid through path.
    void setRoutesValid(Block* nxtHopActive, bool state);
    void firePropertyChange(QString propertyName, QVariant oldVal, QVariant newVal);
    QVector<Block*>* getThroughPathSourceByDestination(Block* dest);
    QVector<Block*>* getThroughPathDestinationBySource(Block* source);
    const QIcon* getColourIcon(QColor color);

protected:
    /*
     * Completes the creation of a LayoutBlock object by adding a Block to it
     */
    /*protected*/ void initializeLayoutBlock();
    /*protected*/ void initializeLayoutBlockRouting();
    /**
     * Edit a Layout Block
     */
    /*protected*/ void editLayoutBlock(/*Component*/ QWidget* callingPane);
    /*protected*/ void updateNeighbourPacketFlow(Adjacencies* neighbour, /*final*/ int flow);

    friend class LoadXml;
    //friend class EditTurnout;
    friend class Adjacencies;
    friend class LayoutBlockNeighbourTableModel;
    friend class Routes;
    friend class ThroughPaths;
    friend class LayoutBlockRouteTableModel;
    friend class LayoutTurnout;
    friend class LBWindowListener;
    friend class JsonLayoutBlockSocketService;
    friend class LayoutBlockListener;
//    friend class LayoutTrackEditors;
    friend class LayoutBlockEditAction;
    friend class RoutingSetSaveItemListener;
    friend class RoutingSetResetItemListener;
    friend class LayoutSetSaveItemListener;
    friend class LayoutSetResetItemListener;
    friend class LayoutSlipEditor;
    friend class LayoutTurnoutEditor;
    friend class TrackSegmentEditor;
    friend class LevelXingEditor;
    friend class LayoutTurntableEditor;

}; // end class LayoutBlock

class Routes : public QObject
{
 Q_OBJECT
 LayoutBlock* block;
public:
    /*public*/ Routes(Block* dstBlock, Block* nxtBlock, int hop, int dir, int met, float len, LayoutBlock* block);
    /*public*/ Block* getDestBlock();
    /*public*/ Block* getNextBlock();
    /*public*/ int getHopCount();
    /*public*/ int getDirection();
    /*public*/ int getMetric();
    /*public*/ float getLength();
    /*public*/ void setMetric(int met);
    /*public*/ void setHopCount(int hop);
    /*public*/ void setLength(float len);
    //This state change is only here for the routing table view
    void stateChange();
    int getState();
    void setValidCurrentRoute(bool boo);
    bool isRouteCurrentlyValid();
    //Misc flags is not used in general routing, but is used for determining route removals
    void setMiscFlags(int f);
    int getMiscFlags();
    /**
    * Get the number of routes that the block has registered.
    */
    /*public*/ int getNumberOfRoutes();
    /**
    * Get the direction of route i.
    */
    /*public*/ int getRouteDirectionAtIndex(int i);
    /**
    * Get the destination block at route i
    */
    /*public*/ Block* getRouteDestBlockAtIndex(int i);
    /**
    * Get the next block at route i
    */
    /*public*/ Block* getRouteNextBlockAtIndex(int i);

    /**
    * Get the hop count of route i.<br>
    * The Hop count is the number of other blocks that we traverse to get to the destination
    */
    /*public*/ int getRouteHopCountAtIndex(int i);
    /**
    * Get the length of route i.<br>
    * The length is the combined length of all the blocks that we traverse to get to the destination
    */
    /*public*/ float getRouteLengthAtIndex(int i);

    /**
    * Get the metric/cost at route i
    */
    /*public*/ int getRouteMetric(int i);
    /**
    * Gets the state (Occupied, unoccupied) of the destination layout block at index i
    */
    /*public*/ int getRouteState(int i);
    /**
    * Is the route to the destination potentially valid from our block.
    */
    /*public*/ bool getRouteValid(int i);
    /**
    * Gets the state of the destination layout block at index i as a string
    */
    /*public*/ QString getRouteStateAsString(int i);
    int getRouteIndex(Routes* r);
    /**
    * Returns the number of layout blocks to our desintation block going from the
    * next directly connected block.  If the destination block and nextblock are
    * the same and the block is also registered as a neighbour then 1 is returned.
    * If no valid route to the destination block can be found via the next block
    * then -1 is returned.  If more than one route exists to the destination then
    * the route with the lowest count is returned.
    */
    /*public*/ int getBlockHopCount(Block* destination, Block* nextBlock);
public slots:
    /*public*/ void on_propertyChange(PropertyChangeEvent* e);
signals:
    void propertyChange(PropertyChangeEvent*);

private:
    int direction;
    Block* destBlock;
    Block* nextBlock;
    int hopCount;
    int routeMetric;
    float length;
    //int state =-1;
    int miscflags;// =0x00;
    bool validCurrentRoute;//=false;
    Logger* log;
    void firePropertyChange(QString, QVariant, QVariant);
 friend class LayoutBlock;
};

class Adjacencies
{
 LayoutBlock* thisBlock;
public:
 Adjacencies(Block* block, int dir, int packetFlow, LayoutBlock* thisBlock);
 Block* getBlock();
 LayoutBlock* getLayoutBlock();
 int getDirection();
 //If a set true on mutual, then we could go through the list of what to send out to neighbour
 void setMutual(bool mut);
 bool isMutual();
 int getPacketFlow();
 void setPacketFlow(int flow);
 //The metric could just be read directly from the neighbour as we have no need to specifically keep a copy of it here this is here just to fire off the change
 void setMetric(int met);
 int getMetric();
 void setLength(float len);
 float getLength();
 void removeRouteAdvertisedToNeighbour(Routes* removeRoute);
 void removeRouteAdvertisedToNeighbour(Block* block);
 void addRouteAdvertisedToNeighbour(Routes* addedRoute);
 bool advertiseRouteToNeighbour(Routes* routeToAdd);
 bool updatePacketActedUpon(int packetID);
 void addPacketRecievedFromNeighbour(int packetID);
 void dispose();
 /*final*/ static const int ADDITION = 0x00;
 /*final*/ static const int UPDATE = 0x02;
 /*final*/ static const int REMOVAL = 0x04;

 /*final*/ static const int RXTX = 0x00;
 /*final*/ static const int RXONLY = 0x02;
 /*final*/ static const int TXONLY = 0x04;
 /*final*/ static const int NONE = 0x08;
 int metric;// = 100;

private:
 Block* adjBlock;
 LayoutBlock* adjLayoutBlock;
 int direction;
 int packetFlow;//= RXTX;
 bool mutualAdjacency;//=false;

 QHash<Block*, Routes*>* adjDestRoutes;// = new Hashtable<Block*, Routes*>();
 QVector<int>* actedUponUpdates;// = new QVector<int>();
 Logger* log;

};

class ThroughPaths : public QObject
{
 Q_OBJECT
    LayoutBlock* parent;
public:
    ThroughPaths(Block* srcBlock, Path* srcPath, Block* destBlock, Path* dstPath, LayoutBlock * parent);
    Block* getSourceBlock();
    Block* getDestinationBlock();
    Path* getSourcePath();
    Path* getDestinationPath();
    bool isPathActive();
    void setTurnoutList(QList<LayoutTrackExpectedState<LayoutTurnout*>*> turnouts);
    /*/*public*/ QHash<Turnout*, int> getTurnoutList();

public slots:
    void handlePropertyChange(QString propertyName, Turnout* source, int newVal);
    /*public*/ void propertyChange(PropertyChangeEvent* e);

private:
    Block* sourceBlock;
    Block* destinationBlock;
    Path* sourcePath;
    Path* destinationPath;

    bool pathActive;// = false;

    QHash <Turnout*, int> _turnouts;// =new QHash<Turnout*, int>();
Logger* log;

};

/*private*/ /*static*/ class RoutingPacket
{
 int packetType;
 Block* block;
 int hopCount;// = -1;
 int packetMetric;// = -1;
 int blockstate;// = -1;
 float length;// = -1;
 int packetRef;// = -1;
public:
 RoutingPacket(int packetType, Block* blk, int hopCount, int packetMetric, float length, int blockstate, int  packetRef)
 {
  this->hopCount = -1;
  this->packetMetric = -1;
  this->blockstate = -1;
  this->length = -1;
  this->packetRef = -1;
  this->packetType = packetType;
  this->block = blk;
  this->hopCount = hopCount;
  this->packetMetric = packetMetric;
  this->blockstate = blockstate;
  this->packetRef = packetRef;
  this->length = length;
}

int getPacketType() { return packetType; }

Block* getBlock() { return block; }

int getHopCount() { return hopCount; }

int getMetric() { return packetMetric; }

int getBlockState() { return blockstate; }

float getLength() { return length; }

int getPacketId() { return packetRef; }
friend class LoadXml;
};

class HandleBlockChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 public:
    HandleBlockChangeListener(LayoutBlock* parent)
    {
     this->parent = parent;
    }
public slots:
    void propertyChange(PropertyChangeEvent *e) override
    {
     this->parent->handleBlockChange(e);
    }
  private:
   LayoutBlock* parent;
};
#if 0
class LBWindowListener : public WindowListener
{
 Q_OBJECT
 LayoutBlock* parent;
public:
 LBWindowListener(LayoutBlock* parent) { this->parent = parent;}
 void windowClosing(QCloseEvent */*e*/)
 {
  parent->blockEditCancelPressed();
 }
};
#endif
class LBRunnable : public QRunnable
{
 //Q_OBJECT
 LayoutBlock* layoutblock;
 LayoutBlock* neighLBlock;
 Block* block;
 int flow;
public:
 LBRunnable(LayoutBlock* neighLBlock, Block* block, int flow, LayoutBlock* layoutblock);
 void run();
};

/*protected*/ class LayoutBlockEditAction : public BlockEditAction
{
 Q_OBJECT
 LayoutBlock* lb = nullptr;
public:
 LayoutBlockEditAction(LayoutBlock* lb) {this->lb = lb;}
    //@Override
    /*public*/ QString helpTarget() {
        return "package.jmri.jmrit.display.EditLayoutBlock";
    }  //IN18N
public slots:
//    void on_setSaveItem();
//    void on_setResetItem();

protected:
    //@Override
    /*protected*/ void initPanels() override;
private:
    BeanItemPanel* layoutDetails();
    BeanItemPanel* blockRoutingDetails() ;
    friend class RoutingSetSaveItemListener;
    friend class RoutingSetResetItemListener;
};
class LayoutSetSaveItemListener : public ActionListener
{
 Q_OBJECT
 LayoutBlock* lb;
 LayoutSetSaveItemListener(LayoutBlock* lb) {this->lb = lb;}
public slots:
 void actionPerformed();
};

class LayoutSetResetItemListener : public ActionListener
{
 Q_OBJECT
 LayoutBlock* lb;
 LayoutSetResetItemListener(LayoutBlock* lb) {this->lb = lb;}
public slots:
 void actionPerformed();
};

class RoutingSetSaveItemListener : public AbstractAction
{
 Q_OBJECT
 LayoutBlock* lb;
 RoutingSetSaveItemListener(LayoutBlock* lb) {this->lb = lb;}
public slots:
 void actionPerformed();
 friend class LayoutBlockEditAction;
};

class RoutingSetResetItemListener : public ActionListener
{
 Q_OBJECT
 LayoutBlock* lb;
 RoutingSetResetItemListener(LayoutBlock* lb) {this->lb = lb;}
public slots:
 void actionPerformed();
 friend class LayoutBlockEditAction;
};

#endif // LAYOUTBLOCK_H
