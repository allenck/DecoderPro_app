#ifndef CONNECTIVITYUTIL_H
#define CONNECTIVITYUTIL_H

#include <QObject>
#include "layouteditor.h"
#include "layoutblock.h"
#include "tracksegment.h"
#include "layoutturnout.h"
#include "tracknode.h"
#include "positionablepoint.h"
#include "../libPr3/Signal/signalhead.h"
#include "levelxing.h"
#include "../libPr3/Signal/signalmast.h"
#include "entrypoint.h"
#include "layoutblockmanager.h"
#include "layouteditorauxtools.h"
#include "layouttrackexpectedstate.h"

//class LayoutTrackExpectedState<LayoutTurnout*>;
class LayoutTurnout;
class LIBLAYOUTEDITORSHARED_EXPORT ConnectivityUtil : public QObject
{
 Q_OBJECT
public:
    explicit ConnectivityUtil(QObject *parent = 0);
    // constructor method
    /*public*/ ConnectivityUtil(LayoutEditor* thePanel);
    /**
     * Provides a list of LayoutTurnouts in a specified Block (block), in order, beginning at the connection
     *   to the specified previous Block (prevBlock) and continuing to the specfied next Block
     *   (nextBlock).
     * Also compiles a companion list of how the turnout should be set for the specified connectivity.
     *	 The companion list can be accessed by "getTurnoutSettingList" immediately after this method
     *	 returns.
     * If both the previous Block or the next Block are specified, follows the connectivity and returns
     *   only those turnouts needed for the transit of this block.  If either are not present (NULL),
     *   returns all turnouts in this block, with settings to enter/exit to whatever block is specified,
     *   and other settings set to CLOSED.
     * Returns an empty list if a connectivity anamoly is discovered--specified blocks are not connected.
     */
    /*public*/ QList<LayoutTrackExpectedState<LayoutTurnout *> *> getTurnoutList(Block* block, Block* prevBlock, Block* nextBlock);
 /*public*/ QList<LayoutTrackExpectedState<LayoutTurnout *> *> getTurnoutList(Block* block, Block* prevBlock, Block* nextBlock, bool suppress);

    /**
     * Returns a list of turnout settings (as Integer Objects) to accomplish the transition through
     *  the Block specified in 'getTurnoutList'.  Settings and Turnouts are in sync by position in
     *  the returned list.
     */
    /*public*/ QVector<int>* getTurnoutSettingList() { return companion; }
    /**
     * Returns a list of all Blocks connected to a specified Block
     */
    /*public*/ QVector<Block*>* getConnectedBlocks(Block* block);
    /**
     * Returns a list of all anchor point boundaries involving the specified Block
     */
    /*public*/ QVector<PositionablePoint*>* getAnchorBoundariesThisBlock(Block* block);
    /**
     * Returns a list of all levelXings involving the specified Block. To be returned, a levelXing must have all its
     *		four connections and all blocks must be assigned.  If any connection is missing, or if a block assignmnet
     *		is missing, an error message is printed and the level crossing is not added to the list.
     */
    /*public*/ QVector<LevelXing*>* getLevelCrossingsThisBlock(Block* block);
    //Need to search through code to find out where this is being used
    /**
     * Returns a list of all layout turnouts involving the specified Block
     */
    /*public*/ QVector<LayoutTurnout*>* getLayoutTurnoutsThisBlock(Block* block);
    /**
     * Returns 'true' if specified Layout Turnout has required signal heads.
     * Returns 'false' if one or more of the required signals are missing.
     */
    /*public*/ bool layoutTurnoutHasRequiredSignals(LayoutTurnout* t);
    /**
     * Returns the Signal Head at the Anchor block boundary
     * If 'facing' is 'true', returns the head that faces toward the specified Block
     * If 'facing' is 'false', returns the head that faces away from the specified Block
     */
    /*public*/ SignalHead* getSignalHeadAtAnchor(PositionablePoint* p, Block* block, bool facing);
    /**
 * Returns the Signal Mast at the Anchor block boundary
 * If 'facing' is 'true', returns the head that faces toward the specified Block
 * If 'facing' is 'false', returns the head that faces away from the specified Block
 */
/*public*/ SignalMast* getSignalMastAtAnchor(PositionablePoint* p, Block* block, bool facing);
    //Signalmasts are only valid or requited on the boundary to a block.
    /*public*/ bool layoutTurnoutHasSignalMasts(LayoutTurnout* t);
    /**
     * Returns the Signal Head at the level crossing
     * If 'facing' is 'true', returns the head that faces toward the specified Block
     * If 'facing' is 'false', returns the head that faces away from the specified Block
     */
    /*public*/ SignalHead* getSignalHeadAtLevelXing(LevelXing* x, Block* block, bool facing);
    /**
     * Returns 'true' if the specified block is internal to the Level Xing, and if all else is OK.
     * Returns 'false' if one of the connecting Track Segments is in the Block, or if there is
     *		a problem with looking for a signal head.
     */
    /*public*/ bool blockInternalToLevelXing(LevelXing* x, Block* block);
    /**
     * Matches the anchor point to an Entry Point, and returns the direction specified in the Entry Point
     *   If no match is found, UNKNOWN is returned, indicating that the block boundary is internal to the
     *		Section.
     */
    /*public*/ int getDirectionFromAnchor(QVector<EntryPoint*>* mForwardEntryPoints, QVector<EntryPoint*>* mReverseEntryPoints,                                           PositionablePoint* p);
    /**
     * Checks if a Level Crossing's AC track and its two connecting Track Segments  are internal to the
     *		specified block.
     *	If the A and C connecting Track Segments are in the Block, and the LevelXing's AC track is in the
     *		block, returns 'true". Otherwise returns 'false', even if one of the tracks of the LevelXing
     *		is in the block.
     * Note; if two connecting track segments are in the block, but the internal connecting
     *		track is not, that is an error in the Layout Editor panel. If found, an error message is
     *		generated and 'false' is returned.
     */
    /*public*/ bool isInternalLevelXingAC(LevelXing* x, Block* block);
    /**
     * Checks if a Level Crossing's BD track and its two connecting Track Segments  are internal to the
     *		specified block.
     *	If the B and D connecting Track Segments are in the Block, and the LevelXing's BD track is in the
     *		block, returns 'true". Otherwise returns 'false', even if one of the tracks of the LevelXing
     *		is in the block.
     * Note; if two connecting track segments are in the block, but the internal connecting
     *		track is not, that is an error in the Layout Editor panel. If found, an error message is
     *		generated and 'false' is returned.
     */
    /*public*/ bool isInternalLevelXingBD(LevelXing* x, Block* block);
    /*
     * Adds the specified sensor ('name') to the SSL for the specified signal head
     * 'name' should be the system name for the sensor.
     * Returns 'true' if the sensor was already in the signal head SSL or if it has been
     *		added successfully.  Returns 'false' and logs an error if not.
     * If the SSL has not been set up yet, the sensor is not added, an error message is output,
     *		and 'false' is returned.
     * Parameters: 'name' - sensor name, 'sh' - signal head, 'where' should be DIVERGING if the sensor
     *		is being added to the diverging (second) part of a facing mode SSL, 'CONTINUING' if
     *		the sensor is being added to the continuing (first) part of a facing mode SSL, OVERALL if
     *		the sensor is being added to the overall sensor list of a facing mode SSL. 'where' is
     *		ignored if not a facing mode SSL.
     */
    /*public*/ bool addSensorToSignalHeadLogic(QString name, SignalHead* sh, int where);
    /*
     * Revoves the specified sensors ('names') from the SSL for the specified signal head if
     *      any of the sensors is currently in the SSL.
     * Returns 'false' if an error was found, and issues a message to the error log.
     * Returns 'true' if no error, whether any sensors were found or not.
     */
    /*public*/ bool removeSensorsFromSignalHeadLogic(QStringList* names, SignalHead* sh);
    /**
     * Returns the next Node following the specified TrackNode
     *<P>
     * If the specified track node can lead to different paths to the next node, for example,
     *       if the specified track node is a turnout entered at its throat, then "cNodeState"
     *       must be specified to choose between the possible paths.
     * Returns a TrackNode if one is reached. Returns NULL if trouble following the track.
     * .
     */
    /*public*/ TrackNode* getNextNode(TrackNode* cNode, int cNodeState);
    /*public*/ TrackNode* getTrackNode(QObject* cNode, int cNodeType, TrackSegment* cTrack, int cNodeState);

    /**
     * Returns an "exit block" for the specified track node if there is one, else returns NULL.
     * An "exit block" must be different from the block of the track segment in the node.
     * If the node is a PositionablePoint, it is assumed to be a block boundary anchor point.
     * If an "excludedBlock" is entered, that block will not be returned as the exit block of
     *		a Node of type TURNOUT_x.
     */
    /*public*/ Block* getExitBlockForTrackNode(TrackNode* node, Block* excludedBlock);
    /*
     * Defines where to place sensor in a FACING mode SSL
     */
    /*public*/ static const int OVERALL = 0x00;
    /*public*/ static const int CONTINUING = 0x01;
    /*public*/ static const int DIVERGING = 0x02;
    /**
     * This flag can be checked after performing a getTurnoutList() to check
     *	if the connectivity of the turnouts has been completed in the block
     *	when the getTurnoutList() was called.
     *  Returns 'false' if a turnout conectivity is not complete.
     *  Returns 'true' if the turnout conectivity is complete.
     */
    /*public*/ bool isTurnoutConnectivityComplete() { return turnoutConnectivity; }
    /*public*/ QVector<LayoutTurnout*>* getAllTurnoutsThisBlock(LayoutBlock* lb);

signals:
    
public slots:
private:
    // constants

    // operational instance variables
    /*private*/ LayoutEditor* layoutEditor;// = NULL;
    /*private*/ LayoutEditorAuxTools* auxTools;// = NULL;
    /*private*/ LayoutBlockManager* layoutBlockManager;// = NULL;
    /*private*/ LayoutEditorTools* leTools;// = NULL;
    /*private*/ QVector<int>* companion;// = NULL;
    /*private*/ TrackSegment* ts;// = NULL;
    /*private*/ TrackSegment* _tr = nullptr;
    /*private*/ int prevConnectType;// = 0;
    /*private*/	QObject* prevConnectObject;// = NULL;
    /*private*/ LayoutBlock* currLayoutBlock = nullptr;
    /*private*/ LayoutBlock* nextLayoutBlock = nullptr;
    /*private*/ LayoutBlock* prevLayoutBlock = nullptr;

    /**
     * Initializes the setting (as an object), sets the new track segment (if in Block), and sets the
     *    prevConnectType.
     */
    /*private*/ int getTurnoutSetting(LayoutTurnout* lt, int cType, bool suppress);
    /**
     * This method follows the track from a beginning track segment to its exits
     *	from the current LayoutBlock 'lb' until the track connects to the designated
     *  Block 'nlb' or all exit points have been tested.
     * Returns 'true' if designated Block is connected; returns 'false' if not.
     */
    /*private*/ bool trackSegmentLeadsTo(TrackSegment* tsg, QObject* ob);
    /*private*/ bool turnoutConnectivity;// = true;
    /*private*/ void setupOpposingTrackSegment(LevelXing* x, int cType);
Logger log;
};

#endif // CONNECTIVITYUTIL_H
