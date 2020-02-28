#ifndef SECTION_H
#define SECTION_H
#include "abstractnamedbean.h"
#include "logger.h"
#include "block.h"
#include "sensor.h"
#include "namedbeanhandle.h"
#include "namedbeanhandlemanager.h"
#include "exceptions.h"
#include "entrypoint.h"
#include "memory.h"
#include "liblayouteditor_global.h"

class Scale;
class JmriJFrame;
class SignalHead;
class TrackNode;
class LayoutBlock;
class LayoutSlip;
class LayoutTurnout;
class ConnectivityUtil;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT Section : public AbstractNamedBean
{
    Q_OBJECT
public:
    explicit Section(QObject *parent = 0);
    /*public*/ Section(QString systemName, QString userName="", QObject *parent = 0);
    ///*public*/ Section(QString systemName);
    /**
     * Constants representing the state of the Section.
     * A Section can be either FREE - available for allocation, FORWARD - allocated
     *	 for travel in the forward direction, or REVERSE - allocated for travel in
     *   the REVERSE direction.
     */
    /*public*/ /*const*/ static /*final*/ int UNKNOWN;// = 0x01;
    /*public*/ /*const*/ static /*final*/ int FREE;// = 0x02;
    /*public*/ /*const*/ static /*final*/ int FORWARD;// = 0x04;*
    /*public*/ /*const*/ static /*final*/ int REVERSE;// = 0X08;

    /*final*/ /*public*/ static int USERDEFINED;// = 0x01; //Default Save all the information
     /*final*/ /*public*/ static int SIGNALMASTLOGIC;// = 0x02; //Save only the name, blocks will be added by the signalmast logic
     /*final*/ /*public*/ static int DYNAMICADHOC;// = 0x00;  //created on an as required basis, not to be saved.



    /**
     * Constants representing the occupancy of the Section.
     * A Section is OCCUPIED if any of its Blocks are OCCUPIED. If all of its Blocks
     *   are UNOCCUPIED, a Section is UNOCCUPIED.
     */
    /*public*/ const static /*final*/ int OCCUPIED = Block::OCCUPIED;
    /*public*/ const static /*final*/ int UNOCCUPIED;// = Block::UNOCCUPIED;
    /**
     * Query the state of the Section
     */
    /*public*/ int getState();
    /**
     * Set the state of the Section
     */
    /*public*/ void setState(int state);

    /**
     * Query the occupancy of a section
     */
    /*public*/ int getOccupancy();
    /**
     * Access methods for forward and reverse blocking sensors
     *	The set methods return a Sensor object if successful, or else they
     *		return "null";
     */
    /*public*/ QString getForwardBlockingSensorName();
    /*public*/ Sensor* getForwardBlockingSensor();
    /*public*/ Sensor* setForwardBlockingSensorName(QString forwardSensor);
    /*public*/ void delayedSetForwardBlockingSensorName(QString forwardSensor);
    /*public*/ QString getReverseBlockingSensorName();
    /*public*/ Sensor* setReverseBlockingSensorName(QString reverseSensor);
    /*public*/ void delayedSetReverseBlockingSensorName(QString reverseSensor);
    /*public*/ Sensor* getReverseBlockingSensor();
    /**
     * Access methods for forward and reverse stopping sensors
     *	The set methods return a Sensor object if successful, or else they
     *		return "NULL";
     */
    /*public*/ QString getForwardStoppingSensorName();
    /*public*/ Sensor* getForwardStoppingSensor();
    /*public*/ Sensor* setForwardStoppingSensorName(QString forwardSensor);
    /*public*/ void delayedSetForwardStoppingSensorName(QString forwardSensor);
    /*public*/ QString getReverseStoppingSensorName();
    /*public*/ Sensor* setReverseStoppingSensorName(QString reverseSensor);
    /*public*/ void delayedSetReverseStoppingSensorName(QString reverseSensor);
    /*public*/ Sensor* getReverseStoppingSensor();
    /**
     *  Add a Block to the Section
     *  Block and sequence number must be unique within the Section.
     *  Block sequence numnbers are set automatically as blocks are added.
     *	Returns "true" if Block was added.  Returns "false" if Block does not connect to
     *		the current Block, or the Block is not unique.
     */
    /*public*/ bool addBlock( Block* b );
    /*public*/ void delayedAddBlock(QString blockName);
    /*private*/ void initializeBlocks();
//    /**
//     * Handle change in occupancy of a Block in the Section
//     */
//    void handleBlockChange(PropertyChangeEvent* e);
    /**
     * Get a Copy of this Section's Block List
     */
    /*public*/ QVector<Block*>* getBlockList();
    /**
     * Gets the number of Blocks in this Section
     */
    /*public*/ int getNumBlocks();
    /**
     * Gets length of Section in scale feet or scale meters.
     *    Length of the Section is calculated by summing the lengths of
     *        all Blocks in the section.  If all Block lengths have not been
     *        entered, length will not be correct.
     *    If meters = true, units of returned length is scale meters
     *    If meters = false, units of returned length is scale feet
     *	  scale = layout scale according to definitions in jmri.Scale.java
     */
    /*public*/ float getLengthF(bool meters, Scale *scale);
    /*public*/ int getLengthI(bool meters, Scale *scale);
    /*public*/ int getActualLength();

    /**
     * Get Block by its Sequence number in the Block list
     *  Blocks are numbered 0 to size-1;
     */
    /*public*/ Block* getBlockBySequenceNumber (int seqNumber);
    /**
     * Get the sequence number of a Block
     * Returns -1 if Block is not in the Section
     */
    /*public*/ int getBlockSequenceNumber(Block* b);
    /**
     * Remove all Blocks, Block Listeners,  and Entry Points
     */
    /*public*/ void removeAllBlocksFromSection ();
    /**
     * Gets Blocks in order
     *	If state is FREE or FORWARD, returns Blocks in forward order
     *  If state is REVERSE, returns Blocks in reverse order
     *	First call getEntryBlock, then call getNextBlock until NULL is returned.
     */
    /*public*/ Block* getEntryBlock();
    /*public*/ Block* getNextBlock();
    /*public*/ bool containsBlock(Block* b);
    /*public*/ bool connectsToBlock(Block* b);
    /**
     * Access methods for beginning and ending block names
     */
    /*public*/ QString getBeginBlockName();
    /*public*/ QString getEndBlockName();
    /**
     * Access methods for EntryPoints within the Section
     */
    /*public*/ void addToForwardList(EntryPoint* ep);
    /*public*/ void addToReverseList(EntryPoint* ep);
    /*public*/ void removeEntryPoint(EntryPoint* ep);
    /*public*/ QList<EntryPoint*>* getForwardEntryPointList();
    /*public*/ QList<EntryPoint*>* getReverseEntryPointList();
    /*public*/ QList<EntryPoint*>* getEntryPointList();
    /*public*/ bool isForwardEntryPoint(EntryPoint* ep);
    /*public*/ bool isReverseEntryPoint(EntryPoint* ep);
    /**
     * Returns the EntryPoint for entry from specified Section for travel in specified direction
     *   Returns 'NULL' if not found.
     */
    /*public*/ EntryPoint* getEntryPointFromSection(Section* s, int dir);
    /**
     * Returns the EntryPoint for exit to specified Section for travel in specified direction
     *   Returns 'NULL' if not found.
     */
    /*public*/ EntryPoint* getExitPointToSection(Section* s, int dir);
    /**
     * Returns the EntryPoint for entry from specified Block for travel in specified direction
     *   Returns 'NULL' if not found.
     */
    /*public*/ EntryPoint* getEntryPointFromBlock(Block* b, int dir);
    /**
     * Returns the EntryPoint for exit to specified Block for travel in specified direction
     *   Returns 'NULL' if not found.
     */
    /*public*/ EntryPoint* getExitPointToBlock(Block* b, int dir);
 /**
  * Places direction sensors in SSL for all Signal Heads in this Section if the Sensors
  *		are not already present in the SSL.
  * Only anchor point block boundaries that have assigned signals are considered.
  * Only turnouts that have assigned signals are considered.
  * Only level crossings that have assigned signals are considered.
  * Turnouts and anchor points without signals are counted, and reported in warning messages
  *		during this procedure, if there are any missing signals.
  * If this method has trouble, an error message is placed in the log describing the trouble.
  * If a direction sensor has not been defined for this Section, a message to that
  *		effect is issued to the log, and an error count of 1 is returned.
  * Returns an an error count of 0, if no errors occurred.
  */

 /*public*/ int placeDirectionSensors(LayoutEditor* panel);
 /**
  * Checks that there are Signal Heads at all Entry Points to this Section.
  * This method will warn if it finds unsignalled internal turnouts, but will continue
  *		checking.  Unsignalled entry points except for those at unsignalled internal
  *		turnouts will be considered errors, and will be reported to the user.  This
  *		method stops searching when it find the first missing Signal Head.
  * Returns 'true' if successful, 'false' otherwise.
  */
 /*public*/ bool checkSignals(JmriJFrame* frame, LayoutEditor* panel);
    /**
     * Validate the Section.
     * This checks block connectivity, warns of redundant EntryPoints,
     *		and otherwise checks internal consistency of the Section.
     * An appropriate error message is logged if a problem is found.
     * This method assumes that Block Paths are correctly initialized.
     * If a Layout Editor panel is available, lePanel!=NULL, the initialization
     *		of Blocks is checked.
     * Returns an empty string "", if everything checks out.  Returns
     *		a string describing the error if an error is found.
     */
    /*public*/ QString validate(LayoutEditor* lePanel);

    /**
     * This function sets/resets the display to use alternate color for unoccupied blocks in this section.
     *    If 'set' is true, the alternate unoccupied color will be used.
     *    If 'set' is false, the unoccupied color will be used.
     *    If Layout Editor panel is not present, Layout Blocks will not be present, and nothing will be set.
     */
    /*public*/ void setAlternateColor(bool set);
    /*public*/ void setAlternateColorFromActiveBlock(bool set);

    /**
     * This function sets a string in the memories associated with blocks in this section.
     *    If Layout Editor panel is not present, Layout Blocks will not be present, and nothing will be set.
     */
    /*public*/ void setNameInBlocks(QString name);
    /*public*/ void setNameInBlocks(QVariant value);
    /*public*/ void setNameFromActiveBlock(QVariant value);

    /**
     * This function clears the string in the memories associated with unoccupied blocks in this section.
     *    If Layout Editor panel is not present, Layout Blocks will not be present, and nothing will be set.
     */
    /*public*/ void clearNameInUnoccupiedBlocks();
    /**
     * This function suppresses the update of a memory variable when a block goes to unoccupied, so the
     *	text set above doesn't get wiped out.
     */
    /*public*/ void suppressNameUpdate(bool set);
    /*public*/ void setSectionType(int type);
    /*public*/ int getSectionType();
    /*public*/ QString getBeanType()  override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) override;
 /*public*/ Block* getLastBlock();

signals:
    
public slots:
    /**
     * Handle change in occupancy of a Block in the Section
     */
    void propertyChange(PropertyChangeEvent* e);

private:
 Logger log;
 /**
  *  Persistant instance variables (saved between runs)
  */
 /*private*/ QString mForwardBlockingSensorName;// = "";
 /*private*/ QString mReverseBlockingSensorName;// = "";
 /*private*/ QString mForwardStoppingSensorName;// = "";
 /*private*/ QString mReverseStoppingSensorName;// = "";
 /*private*/ QList<Block*>* mBlockEntries; //= new ArrayList<Block>();
 /*private*/ QVector<EntryPoint*>* mForwardEntryPoints;// = new ArrayList<EntryPoint>();
 /*private*/ QVector<EntryPoint*>* mReverseEntryPoints; // = new ArrayList<EntryPoint>();

 /**
  *  Operational instance variables (not saved between runs)
  */
 /*private*/ int mState;// = FREE;
 /*private*/ int mOccupancy;// = UNOCCUPIED;
 /*private*/ bool mOccupancyInitialized;// = false;
 /*private*/ Block* mFirstBlock;// = NULL;
 /*private*/ Block* mLastBlock;// = NULL;

 /*private*/ NamedBeanHandle<Sensor*>* mForwardBlockingNamedSensor;// = null;
 /*private*/ NamedBeanHandle<Sensor*>* mReverseBlockingNamedSensor;// = null;
 /*private*/ NamedBeanHandle<Sensor*>* mForwardStoppingNamedSensor;// = null;
 /*private*/ NamedBeanHandle<Sensor*>* mReverseStoppingNamedSensor;// = null;

 /*private*/ QList<PropertyChangeListener*>* mBlockListeners;// = new ArrayList<PropertyChangeListener>();
 QString tempSensorName;// = "";
 /*private*/ Sensor* validateSensor();
 PropertyChangeListener* listener;// = NULL;
 /*private*/ bool initializationNeeded;// = false;
 /*private*/ QVector<QString>* blockNameList;// = new QVector<QString>();
 /*private*/ void setOccupancy(int occupancy);
 /*private*/ int blockIndex;// = 0;  // index of last block returned

 /**
  * Returns EntryPoint::FORWARD if proceeding from A to B (or D to C) is movement in the forward
  *	direction.  Returns EntryPoint::REVERSE if proceeding from A to B (or D to C)  is movement in
  *  the reverse direction.
  * Returns EntryPoint::UNKNOWN if cannot determine direction. This should only happen if blocks are not
  *	set up correctly--if all connections go to the same Block, or not all Blocks set.
  * An error message is logged if EntryPoint::UNKNOWN is returned.
  */

 /*private*/ int getDirectionXoverTurnout(LayoutTurnout* t, ConnectivityUtil* cUtil);
 /**
  * Returns EntryPoint.FORWARD if proceeding from the throat to the other end is movement in the forward
  *	direction.  Returns EntryPoint.REVERSE if proceeding from the throat to the other end is movement in
  *  the reverse direction.
  * Returns EntryPoint.UNKNOWN if cannot determine direction. This should only happen if blocks are not
  *	set up correctly--if all connections go to the same Block, or not all Blocks set.
  * An error message is logged if EntryPoint.UNKNOWN is returned.
  */
 /*private*/ int getDirectionStandardTurnout(LayoutTurnout* t, ConnectivityUtil* cUtil);
 /**
  * Returns EntryPoint::FORWARD if proceeding from A to C or D (or B to D or C) is movement in the forward
  *	direction.  Returns EntryPoint::REVERSE if proceeding from C or D to A (or D or C to B)  is movement in
  *  the reverse direction.
  * Returns EntryPoint::UNKNOWN if cannot determine direction. This should only happen if blocks are not
  *	set up correctly--if all connections go to the same Block, or not all Blocks set.
  * An error message is logged if EntryPoint::UNKNOWN is returned.
  */

 /*private*/ int getDirectionSlip(LayoutSlip* t, ConnectivityUtil* cUtil);

 /*private*/ bool placeSensorInCrossover(QString b1Name, QString b2Name, QString c1Name, QString c2Name,
                     int direction, ConnectivityUtil* cUtil);
 /*private*/ int checkLists (QVector<EntryPoint*>* forwardList, QVector<EntryPoint*>* reverseList, LayoutBlock* lBlock) ;
 /*private*/ Block* checkDualDirection(LayoutBlock* aBlock, LayoutBlock* bBlock, LayoutBlock* cBlock);
 /**
  * Returns the direction for proceeding from LayoutBlock b to LayoutBlock a.  LayoutBlock a must be
  *		in the Section. LayoutBlock b may be in this Section or may be an Entry Point to the Section.
  */
 /*private*/ int getDirectionForBlocks(LayoutBlock* a, LayoutBlock* b);
 /*
  * Returns 'true' if successfully checked direction sensor by follow connectivity from specified
  *		track node.  Returns 'false' if an error occurred.
  */
 /*private*/ bool setDirectionSensorByConnectivity(TrackNode* tNode, TrackNode* altNode, SignalHead* sh,
                             Block* cBlock, ConnectivityUtil* cUtil);
 /*private*/ bool checkDirectionSensor(SignalHead* sh, int direction, int where,
                                                             ConnectivityUtil* cUtil);
 /*private*/ LayoutTurnout* getLayoutTurnoutFromTurnoutName(QString turnoutName, LayoutEditor* panel);

 /*private*/ QVector<EntryPoint*>* getListOfForwardBlockEntryPoints(Block* b);
 /*private*/ bool connected(Block* b1, Block* b2);
 int sectionType;// = USERDEFINED;

protected:
 /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager::getDefault(NamedBeanHandleManager.class);

};

#endif // SECTION_H
