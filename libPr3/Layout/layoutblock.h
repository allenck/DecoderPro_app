#ifndef LAYOUTBLOCK_H
#define LAYOUTBLOCK_H
#include "abstractnamedbean.h"
#include "sensor.h"
#include <QColor>
#include "block.h"
#include "layouteditor.h"
#include "../libPr3/memory.h"
#include "turnout.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include "layoutconnectivity.h"

class LayoutEditor;
class LayoutBlock : public AbstractNamedBean
{
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
    /*public*/ static const int EMPTY = Block::UNOCCUPIED;
    /*public*/ static const int UNKNOWN = Sensor::UNKNOWN;  // must be a different bit
    /**
     * Accessor methods
     */
    /*public*/ QString getID() {return blockName;}
    /*public*/ QColor getBlockTrackColor() {return blockTrackColor;}
    /*public*/ void setBlockTrackColor(QColor color) {blockTrackColor = color;}
    /*public*/ QColor getBlockOccupiedColor() {return blockOccupiedColor;}
    /*public*/ void setBlockOccupiedColor(QColor color) {blockOccupiedColor = color;}
    /*public*/ QColor getBlockExtraColor() {return blockExtraColor;}
    /*public*/ void setBlockExtraColor(QColor color) {blockExtraColor = color;}
    /*public*/ bool getUseExtraColor() {return useExtraColor;}
    /*public*/ void setUseExtraColor(bool b);
    /*public*/ void incrementUse() {useCount ++;}
    /*public*/ void decrementUse();
    /*public*/ int getUseCount() {return useCount;}
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
    /*public*/ void setState(int i);

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

signals:
    
public slots:
    /**
     * Handle tasks when block changes
     */
    void handleBlockChange(PropertyChangeEvent* e);
private:
    //static bool InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() = true;

    /*private*/ LayoutBlock* _instance;// = null;
    // operational instance variables (not saved to disk)
    /*private*/ int useCount; //0;
    /*private*/ NamedBeanHandle<Sensor*>* occupancyNamedSensor; //NULL;
    /*private*/ Memory* memory; //NULL;
    /*private*/ Block* block; //NULL;
    ///*private*/ int maxBlockNumber; //0;
    /*private*/ QVector<LayoutEditor*> panels; //new QVector<LayoutEditor*>();  // panels using this block
    /*private*/ PropertyChangeListener* mBlockListener; //NULL;
    /*private*/	int jmriblknum; //1;
    /*private*/ bool useExtraColor; //false;
    /*private*/ bool suppressNameUpdate; //false;
    /*private*/ void updateBlockPaths(QVector<LayoutConnectivity*> c, LayoutEditor* panel);
    /*private*/ bool compareConnectivity(QVector<LayoutConnectivity*>* main, QVector<LayoutConnectivity*>* test);
    /**
     * Deactivate block listener for redraw of panels and update of memories on
     *	change of state
     */
    /*private*/ void deactivateBlock();

    // variables for Edit Layout Block pane
    /*JmriJFrame*/ QDialog* editLayoutBlockFrame; //NULL;
    /*Component*/ QWidget* callingPane;
    /*JTextField*/ QLineEdit* sensorNameField; //new /*JTextField*/ QLineEdit(16);
    /*JTextField*/ QLineEdit* sensorDebounceInactiveField; //new /*JTextField*/ QLineEdit(5);
    /*JTextField*/ QLineEdit* sensorDebounceActiveField; //new /*JTextField*/ QLineEdit(5);
    /*JCheckBox*/ QCheckBox* sensorDebounceGlobalCheck; //new /*JCheckBox*/ QCheckBox(rb.getQString("OccupancySensorUseGlobal"));
    /*JTextField*/ QLineEdit* memoryNameField; //new /*JTextField*/ QLineEdit(16);
    /*JTextField*/ QLineEdit* metricField; //new /*JTextField*/ QLineEdit(10);
    /*JComboBox*/ QComboBox* senseBox; //new /*JComboBox*/ QComboBox();
    /*JCheckBox*/ QCheckBox* permissiveCheck; //new /*JCheckBox*/ QCheckBox("Permissive Working Allowed");
    int senseActiveIndex;
    int senseInactiveIndex;
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

    
};
class Routes
{
public:
    /*public*/ Routes(Block* dstBlock, Block* nxtBlock, int hop, int dir, int met, float len);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public*/ Block getDestBlock();
    /*public*/ Block getNextBlock();
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
};

class Adjacencies
{
public:
 Adjacencies(Block* block, int dir, int packetFlow);
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

};

class ThroughPaths
{
public:
    ThroughPaths(Block* srcBlock, Path srcPath, Block* destBlock, Path dstPath);
    Block* getSourceBlock();
    Block* getDestinationBlock();
    Path* getSourcePath();
    Path* getDestinationPath();
    bool isPathActive();
    void setTurnoutList(QVector<LayoutTurnout*>* turnouts, QVector<int>* turnoutSettings);
    /*/*public*/ QHash<Turnout*, int>* getTurnoutList();
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    QVector<Block*> getThroughPathSourceByDestination(Block* dest);
    //When a route is created this will check to see if the through path that this
    //route relates to is active
    bool checkIsRouteOnValidThroughPath(Routes* r);
    //A procedure that will go through all the routes and refresh the valid flag
    /*public*/ void refreshValidRoutes();
    void updateActiveThroughPaths(ThroughPaths* tp, bool active);
    //Sets the valid flag for routes that are on a valid through path.
    void setRoutesValid(Block* nxtHopActive, bool state);

private:
    Block* sourceBlock;
    Block* destinationBlock;
    Path* sourcePath;
    Path* destinationPath;

    bool pathActive;// = false;

    QHash <Turnout*, int>* _turnouts;// =new QHash<Turnout*, int>();
    //We keep a track of what is paths are active, only so that we can easily mark
    //which routes are also potentially valid
    QVector <ThroughPaths> activePaths;


};

#endif // LAYOUTBLOCK_H
