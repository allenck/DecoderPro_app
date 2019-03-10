#include "connectivityutil.h"
#include "instancemanager.h"
#include "blockbosslogic.h"
#include "abstractsignalhead.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "layouteditorfinditems.h"

ConnectivityUtil::ConnectivityUtil(QObject *parent) :
    QObject(parent)
{
}
/**
 * ConnectivityUtil provides methods supporting use of layout connectivity available
 *	in Layout Editor panels->  These tools allow outside classes to inquire into
 *  connectivity information contained in a specified Layout Editor panel.
 * <P>
 * Connectivity information is stored in the track diagram of a Layout Editor panel. The
 *  "connectivity graph" of the layout consists of nodes (LayoutTurnouts, LevelXings, and
 *  PositionablePoints) connected by lines (TrackSegments). These methods extract information
 *  from the connection graph and make it available. Each instance of ConnectivityUtil is
 *	associated with a specific Layout Editor panel, and is accessed via that LayoutEditor panel's
 *  'getConnectivityUtil' method.
 * <P>
 * The methods in this module do not modify the Layout in any way, or change the state of
 *  items on the layout-> They only provide information to allow other modules to do so as
 *  appropriate. For example, the "getTurnoutList" method provides information about the
 *  turnouts in a block, but does not test the state, or change the state, of any turnout->
 * <P>
 * The methods in this module are accessed via direct calls from the inquiring
 *   method.
 * <P>
 * @author Dave Duchamp Copyright (c) 2009
 * @version $Revision: 21280 $
 */

///*public*/ class ConnectivityUtil
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit->display.layoutEditor->LayoutEditorBundle");


// constructor method
/*public*/ ConnectivityUtil::ConnectivityUtil(LayoutEditor* thePanel)
{
        // operational instance variables
 layoutEditor = nullptr;

 auxTools = nullptr;
 layoutBlockManager = nullptr;
 leTools = nullptr;
 ts = nullptr; // was tr
 prevConnectType = 0;
 prevConnectObject = nullptr;
 turnoutConnectivity = true;

 layoutEditor = thePanel;
 auxTools = new LayoutEditorAuxTools(layoutEditor);
 leTools = layoutEditor->getLETools();
 layoutBlockManager = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"));
}

/**
 * Provide a list of LayoutTurnouts in the specified Block, in order,
 * beginning at the connection to the specified previous Block and
 * continuing to the specified next Block. Also compiles a companion list of
 * how the turnout should be set for the specified connectivity. The
 * companion list can be accessed by "getTurnoutSettingList" immediately
 * after this method returns.
 *
 * @param currBlock the block to list LayoutTurnouts in
 * @param prevBlock the previous block
 * @param nextBlock the following block
 * @return the list of all turnouts in the block if prevBlock or nextBlock
 *         are null or the list of all turnouts required to transit
 *         currBlock between prevBlock and nextBlock; returns an empty list
 *         if prevBlock and nextBlock are not null and are not connected
 */
//@Nonnull
/*public*/ QList<LayoutTrackExpectedState<LayoutTurnout*>* > ConnectivityUtil::getTurnoutList(
        /*@Nullable*/ Block* currBlock,
        /*@Nullable*/ Block* prevBlock,
        /*@Nullable*/ Block* nextBlock) {
    return getTurnoutList(currBlock, prevBlock, nextBlock, false);
}

/**
* Provides a list of LayoutTurnouts in a specified Block (block), in order, beginning at the connection
*   to the specified previous Block (prevBlock) and continuing to the specfied next Block
*   (nextBlock).
* Also compiles a companion list of how the turnout should be set for the specified connectivity.
*	 The companion list can be accessed by "getTurnoutSettingList" immediately after this method
*	 returns.
* If both the previous Block or the next Block are specified, follows the connectivity and returns
*   only those turnouts needed for the transit of this block.  If either are not present (nullptr),
*   returns all turnouts in this block, with settings to enter/exit to whatever block is specified,
*   and other settings set to CLOSED.
* Returns an empty list if a connectivity anamoly is discovered--specified blocks are not connected.
*/
/*public*/ QList<LayoutTrackExpectedState<LayoutTurnout*>* > ConnectivityUtil::getTurnoutList(Block* currBlock, Block* prevBlock, Block* nextBlock, bool suppress)
{
QList<LayoutTrackExpectedState<LayoutTurnout*>* > result = QList<LayoutTrackExpectedState<LayoutTurnout*>* >();

     // initialize
     currLayoutBlock = nullptr;
     QString currUserName = nullptr;
     if (currBlock != nullptr) {
         currUserName = currBlock->getUserName();
         if ((currUserName != "") && !currUserName.isEmpty()) {
             currLayoutBlock = layoutBlockManager->getByUserName(currUserName);
         }
     }

     prevLayoutBlock = nullptr;
     if (prevBlock != nullptr) {
         QString prevUserName = prevBlock->getUserName();
         if ((prevUserName != "") && !prevUserName.isEmpty()) {
             prevLayoutBlock = layoutBlockManager->getByUserName(prevUserName);
         }
     }

     nextLayoutBlock = nullptr;
     if (nextBlock != nullptr) {
         QString nextUserName = nextBlock->getUserName();
         if ((nextUserName != "") && !nextUserName.isEmpty()) {
             nextLayoutBlock = layoutBlockManager->getByUserName(nextUserName);
         }
     }

     turnoutConnectivity = true;
     if ((prevLayoutBlock == nullptr) || (nextLayoutBlock == nullptr)) {
         // special search with partial information - not as good, order not assured
         QVector<LayoutTurnout*>* allTurnouts = getAllTurnoutsThisBlock(currLayoutBlock);
         //allTurnouts.forEach((lt) ->
         foreach(LayoutTurnout* lt, *allTurnouts)
         {
             result.append(new LayoutTrackExpectedState<LayoutTurnout*>(lt, lt->getConnectivityStateForLayoutBlocks(currLayoutBlock, prevLayoutBlock, nextLayoutBlock, suppress)));
         }//); // for (LayoutTurnout* ltx : allTurnouts)
         return result;
     }

     QVector<LayoutConnectivity*>* cList = auxTools->getConnectivityList(currLayoutBlock);
     int cType;
     // initialize the connectivity search, processing a turnout in this block if it is present
     bool notFound = true;
     for (int i = 0; (i < cList->size()) && notFound; i++) {
         LayoutConnectivity* lc = cList->at(i);
         if ((lc->getXover() != nullptr) && (((lc->getBlock1() == currLayoutBlock) && (lc->getBlock2() == prevLayoutBlock))
                 || ((lc->getBlock1() == prevLayoutBlock) && (lc->getBlock2() == currLayoutBlock)))) {
             // have a block boundary in a crossover turnout, add turnout to the List
             LayoutTurnout* xt = lc->getXover();
             int setting = Turnout::THROWN;
             // determine setting and setup track segment if there is one
             _tr = nullptr;
             prevConnectObject = xt;
             switch (lc->getXoverBoundaryType()) {
                 case LayoutConnectivity::XOVER_BOUNDARY_AB:
                     setting = Turnout::CLOSED;
                     if (((TrackSegment*) xt->getConnectA() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectA())->getLayoutBlock())) {
                         // block exits Xover at A
                         _tr = (TrackSegment*) xt->getConnectA();
                         prevConnectType = LayoutTrack::TURNOUT_A;
                     } else if (((TrackSegment*) xt->getConnectB() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectB())->getLayoutBlock())) {
                         // block exits Xover at B
                         _tr = (TrackSegment*) xt->getConnectB();
                         prevConnectType = LayoutTrack::TURNOUT_B;
                     }
                     break;
                 case LayoutConnectivity::XOVER_BOUNDARY_CD:
                     setting = Turnout::CLOSED;
                     if (((TrackSegment*) xt->getConnectC() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectC())->getLayoutBlock())) {
                         // block exits Xover at C
                         _tr = (TrackSegment*) xt->getConnectC();
                         prevConnectType = LayoutTrack::TURNOUT_C;
                     } else if (((TrackSegment*) xt->getConnectD() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectD())->getLayoutBlock())) {
                         // block exits Xover at D
                         _tr = (TrackSegment*) xt->getConnectD();
                         prevConnectType = LayoutTrack::TURNOUT_D;
                     }
                     break;
                 case LayoutConnectivity::XOVER_BOUNDARY_AC:
                     if (((TrackSegment*) xt->getConnectA() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectA())->getLayoutBlock())) {
                         // block exits Xover at A
                         _tr = (TrackSegment*) xt->getConnectA();
                         prevConnectType = LayoutTrack::TURNOUT_A;
                     } else if (((TrackSegment*) xt->getConnectC() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectC())->getLayoutBlock())) {
                         // block exits Xover at C
                         _tr = (TrackSegment*) xt->getConnectC();
                         prevConnectType = LayoutTrack::TURNOUT_C;
                     }
                     break;
                 case LayoutConnectivity::XOVER_BOUNDARY_BD:
                     if (((TrackSegment*) xt->getConnectB() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectB())->getLayoutBlock())) {
                         // block exits Xover at B
                         _tr = (TrackSegment*) xt->getConnectB();
                         prevConnectType = LayoutTrack::TURNOUT_B;
                     } else if (((TrackSegment*) xt->getConnectD() != nullptr) && (currLayoutBlock == ((TrackSegment*) xt->getConnectD())->getLayoutBlock())) {
                         // block exits Xover at D
                         _tr = (TrackSegment*) xt->getConnectD();
                         prevConnectType = LayoutTrack::TURNOUT_D;
                     }
                     break;
                 default:
                     break;
             }
             result.append(new LayoutTrackExpectedState<LayoutTurnout*>(xt, setting));
             notFound = false;
         } else if ((lc->getBlock1() == currLayoutBlock) && (lc->getBlock2() == prevLayoutBlock)) {
             // no turnout  or level crossing at the beginning of this block
             _tr = lc->getTrackSegment();
             if (lc->getConnectedType() == LayoutTrack::TRACK) {
                 prevConnectType = LayoutTrack::POS_POINT;
                 prevConnectObject = lc->getAnchor();
             } else {
                 prevConnectType = lc->getConnectedType();
                 prevConnectObject = lc->getConnectedObject();
             }
             notFound = false;
         } else if ((lc->getBlock2() == currLayoutBlock) && (lc->getBlock1() == prevLayoutBlock)) {
             cType = lc->getConnectedType();
             // check for connection to a track segment
             if (cType == LayoutTrack::TRACK) {
                 _tr = (TrackSegment*) lc->getConnectedObject();
                 prevConnectType = LayoutTrack::POS_POINT;
                 prevConnectObject = lc->getAnchor();
             } // check for a level crossing
             else if ((cType >= LayoutTrack::LEVEL_XING_A) && (cType <= LayoutTrack::LEVEL_XING_D)) {
                 // entering this Block at a level crossing, skip over it an initialize the next
                 //      TrackSegment if there is one in this Block
                 setupOpposingTrackSegment((LevelXing*) lc->getConnectedObject(), cType);
             } // check for turnout
             else if ((cType >= LayoutTrack::TURNOUT_A) && (cType <= LayoutTrack::TURNOUT_D)) {
                 // add turnout to list
                 result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) lc->getConnectedObject(),
                         getTurnoutSetting((LayoutTurnout*) lc->getConnectedObject(), cType, suppress)));
             } else if ((cType >= LayoutTrack::SLIP_A) && (cType <= LayoutTrack::SLIP_D)) {
                 result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) lc->getConnectedObject(),
                         getTurnoutSetting((LayoutTurnout*) lc->getConnectedObject(), cType, suppress)));
             }
             notFound = false;
         }
     }
     if (notFound) {
         if (prevBlock != nullptr) {    // could not initialize the connectivity search
             if (!suppress) {
                 log.error(tr("Could not find connection between Blocks %1 and %2").arg(currUserName).arg( prevBlock->getUserName()));
             }
         } else if (!suppress) {
             log.error(tr("Could not find connection between Blocks %1, prevBock is nullptr!").arg( currUserName));
         }
         return result;
     }
     // search connectivity for turnouts by following TrackSegments to end of Block
     while (_tr != nullptr) {
         LayoutTrack* cObject;
         // identify next connection
         if ((_tr->getConnect1() == prevConnectObject) && (_tr->getType1() == prevConnectType)) {
             cType = _tr->getType2();
             cObject = (LayoutTrack*)_tr->getConnect2();
         } else if ((_tr->getConnect2() == prevConnectObject) && (_tr->getType2() == prevConnectType)) {
             cType = _tr->getType1();
             cObject = (LayoutTrack*)_tr->getConnect1();
         } else {
             if (!suppress) {
                 log.error("Connectivity error when searching turnouts in Block " + currLayoutBlock->getDisplayName());
             }
             _tr = nullptr;
             break;
         }
         if (cType == LayoutTrack::POS_POINT) {
             // reached anchor point or end bumper
             if (((PositionablePoint*) cObject)->getType() == PositionablePoint::END_BUMPER) {
                 // end of line
                 _tr = nullptr;
             } else if (((PositionablePoint*) cObject)->getType() == PositionablePoint::ANCHOR || (((PositionablePoint*) cObject)->getType() == PositionablePoint::EDGE_CONNECTOR)) {
                 // proceed to next track segment if within the same Block
                 if (((PositionablePoint*) cObject)->getConnect1() == _tr) {
                     _tr = ((PositionablePoint*) cObject)->getConnect2();
                 } else {
                     _tr = ((PositionablePoint*) cObject)->getConnect1();
                 }
                 if ((_tr == nullptr) || (_tr->getLayoutBlock() != currLayoutBlock)) {
                     // track segment is not in this block
                     _tr = nullptr;
                 } else {
                     prevConnectType = cType;
                     prevConnectObject = cObject;
                 }
             }
         } else if ((cType >= LayoutTrack::LEVEL_XING_A) && (cType <= LayoutTrack::LEVEL_XING_D)) {
             // reached a level crossing, is it within this block?
             if ((cType == LayoutTrack::LEVEL_XING_A) || (cType == LayoutTrack::LEVEL_XING_C)) {
                 if (((LevelXing*) cObject)->getLayoutBlockAC() != currLayoutBlock) {
                     // outside of block
                     _tr = nullptr;
                 } else {
                     // same block
                     setupOpposingTrackSegment((LevelXing*) cObject, cType);
                 }
             } else {
                 if (((LevelXing*) cObject)->getLayoutBlockBD() != currLayoutBlock) {
                     // outside of block
                     _tr = nullptr;
                 } else {
                     // same block
                     setupOpposingTrackSegment((LevelXing*) cObject, cType);
                 }
             }
         } else if ((cType >= LayoutTrack::TURNOUT_A) && (cType <= LayoutTrack::TURNOUT_D)) {
             // reached a turnout
             LayoutTurnout* lt = (LayoutTurnout*) cObject;
             int tType = lt->getTurnoutType();
             // is this turnout a crossover turnout at least partly within this block?
             if ((tType == LayoutTurnout::DOUBLE_XOVER) || (tType == LayoutTurnout::RH_XOVER)
                     || (tType == LayoutTurnout::LH_XOVER)) {
                 // reached a crossover turnout
                 switch (cType) {
                     case LayoutTrack::TURNOUT_A:
                         if ((lt->getLayoutBlock()) != currLayoutBlock) {
                             // connection is outside of the current block
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockB() == nextLayoutBlock) {
                             // exits Block at B
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = nullptr;
                         } else if ((lt->getLayoutBlockC() == nextLayoutBlock) && (tType != LayoutTurnout::LH_XOVER)) {
                             // exits Block at C, either Double or RH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockB() == currLayoutBlock) {
                             // block continues at B
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = (TrackSegment*) lt->getConnectB();
                             prevConnectType = LayoutTrack::TURNOUT_B;
                             prevConnectObject = cObject;
                         } else if ((lt->getLayoutBlockC() == currLayoutBlock) && (tType != LayoutTurnout::LH_XOVER)) {
                             // block continues at C, either Double or RH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = (TrackSegment*) lt->getConnectC();
                             prevConnectType = LayoutTrack::TURNOUT_C;
                             prevConnectObject = cObject;
                         } else if (lt->getLayoutBlock() == currLayoutBlock && currLayoutBlock == nextLayoutBlock) {
                             //we are at our final destination so not an error such
                             _tr = nullptr;
                         } else {
                             // no legal outcome found, print error
                             if (!suppress) {
                                 log.error("Connectivity mismatch at A in turnout " + lt->getTurnoutName());
                             }
                             _tr = nullptr;
                         }
                         break;
                     case LayoutTrack::TURNOUT_B:
                         if ((lt->getLayoutBlockB()) != currLayoutBlock) {
                             // connection is outside of the current block
                             _tr = nullptr;
                         } else if (lt->getLayoutBlock() == nextLayoutBlock) {
                             // exits Block at A
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = nullptr;
                         } else if ((lt->getLayoutBlockD() == nextLayoutBlock) && (tType != LayoutTurnout::RH_XOVER)) {
                             // exits Block at D, either Double or LH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = nullptr;
                         } else if (lt->getLayoutBlock() == currLayoutBlock) {
                             // block continues at A
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = (TrackSegment*) lt->getConnectA();
                             prevConnectType = LayoutTrack::TURNOUT_A;
                             prevConnectObject = cObject;
                         } else if ((lt->getLayoutBlockD() == currLayoutBlock) && (tType != LayoutTurnout::RH_XOVER)) {
                             // block continues at D, either Double or LH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = (TrackSegment*) lt->getConnectD();
                             prevConnectType = LayoutTrack::TURNOUT_D;
                             prevConnectObject = cObject;
                         } else if (lt->getLayoutBlockB() == currLayoutBlock && currLayoutBlock == nextLayoutBlock) {
                             //we are at our final destination so not an error such
                             _tr = nullptr;
                         } else {
                             // no legal outcome found, print error
                             if (!suppress) {
                                 log.error("Connectivity mismatch at B in turnout " + lt->getTurnoutName());
                             }
                             _tr = nullptr;
                         }
                         break;
                     case LayoutTrack::TURNOUT_C:
                         if ((lt->getLayoutBlockC()) != currLayoutBlock) {
                             // connection is outside of the current block
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockD() == nextLayoutBlock) {
                             // exits Block at D
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = nullptr;
                         } else if ((lt->getLayoutBlock() == nextLayoutBlock) && (tType != LayoutTurnout::LH_XOVER)) {
                             // exits Block at A, either Double or RH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockD() == currLayoutBlock) {
                             // block continues at D
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = (TrackSegment*) lt->getConnectD();
                             prevConnectType = LayoutTrack::TURNOUT_D;
                             prevConnectObject = cObject;
                         } else if ((lt->getLayoutBlock() == currLayoutBlock) && (tType != LayoutTurnout::LH_XOVER)) {
                             // block continues at A, either Double or RH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = (TrackSegment*) lt->getConnectA();
                             prevConnectType = LayoutTrack::TURNOUT_A;
                             prevConnectObject = cObject;
                         } else if (lt->getLayoutBlockC() == currLayoutBlock && currLayoutBlock == nextLayoutBlock) {
                             //we are at our final destination so not an error such
                             _tr = nullptr;
                         } else {
                             // no legal outcome found, print error
                             if (!suppress) {
                                 log.error("Connectivity mismatch at C in turnout " + lt->getTurnoutName());
                             }
                             _tr = nullptr;
                         }
                         break;
                     case LayoutTrack::TURNOUT_D:
                         if ((lt->getLayoutBlockD()) != currLayoutBlock) {
                             // connection is outside of the current block
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockC() == nextLayoutBlock) {
                             // exits Block at C
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = nullptr;
                         } else if ((lt->getLayoutBlockB() == nextLayoutBlock) && (tType != LayoutTurnout::RH_XOVER)) {
                             // exits Block at B, either Double or LH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = nullptr;
                         } else if (lt->getLayoutBlockC() == currLayoutBlock) {
                             // block continues at C
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::CLOSED));
                             _tr = (TrackSegment*) lt->getConnectC();
                             prevConnectType = LayoutTrack::TURNOUT_C;
                             prevConnectObject = cObject;
                         } else if ((lt->getLayoutBlockB() == currLayoutBlock) && (tType != LayoutTurnout::RH_XOVER)) {
                             // block continues at B, either Double or LH
                             result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, Turnout::THROWN));
                             _tr = (TrackSegment*) lt->getConnectB();
                             prevConnectType = LayoutTrack::TURNOUT_B;
                             prevConnectObject = cObject;
                         } else if (lt->getLayoutBlockD() == currLayoutBlock && currLayoutBlock == nextLayoutBlock) {
                             //we are at our final destination so not an error such
                             _tr = nullptr;
                         } else {
                             // no legal outcome found, print error
                             if (!suppress) {
                                 log.error("Connectivity mismatch at D in turnout " + lt->getTurnoutName());
                             }
                             _tr = nullptr;
                         }
                         break;
                     default:
                         log.warn(tr("Unhandled crossover type: %1").arg(cType));
                         break;
                 }
             } else if ((tType == LayoutTurnout::RH_TURNOUT) || (tType == LayoutTurnout::LH_TURNOUT)
                     || (tType == LayoutTurnout::WYE_TURNOUT)) {
                 // reached RH. LH, or WYE turnout, is it in the current Block?
                 if (lt->getLayoutBlock() != currLayoutBlock) {
                     // turnout is outside of current block
                     _tr = nullptr;
                 } else {
                     // turnout is inside current block, add it to the list
                     result.append(new LayoutTrackExpectedState<LayoutTurnout*>((LayoutTurnout*) cObject, getTurnoutSetting(lt, cType, suppress)));
                 }
             }
         } else if ((cType >= LayoutTrack::SLIP_A) && (cType <= LayoutTrack::SLIP_D)) {
             // reached a LayoutSlip
             LayoutSlip* ls = (LayoutSlip*) cObject;
             if (((cType == LayoutTrack::SLIP_A) && (ls->getLayoutBlock() != currLayoutBlock))
                     || ((cType == LayoutTrack::SLIP_B) && (ls->getLayoutBlockB() != currLayoutBlock))
                     || ((cType == LayoutTrack::SLIP_C) && (ls->getLayoutBlockC() != currLayoutBlock))
                     || ((cType == LayoutTrack::SLIP_D) && (ls->getLayoutBlockD() != currLayoutBlock))) {
                 //Slip is outside of the current block
                 _tr = nullptr;
             } else {
                 // turnout is inside current block, add it to the list
                 result.append(new LayoutTrackExpectedState<LayoutTurnout*>(ls, getTurnoutSetting(ls, cType, suppress)));
             }
         }
     }
     return result;
}


/**
 * Returns a list of all Blocks connected to a specified Block
 */
/*public*/ QVector<Block*>* ConnectivityUtil::getConnectedBlocks(Block* block) {
 QVector<Block*>* result = new QVector<Block*>();
 //
 //TODO: Dead-code strip (after 4.9.x)
 // dissusion: lBlock could be used to match against getBlock1 & 2...
 //              instead of matching against block == getBlock()
 //
 //String userName = block.getUserName();
 //LayoutBlock lBlock = null;
 //if ((userName != null) && !userName.isEmpty()) {
 //    lBlock = layoutBlockManager.getByUserName(userName);
 //}
 QVector<LayoutConnectivity*>* cList = auxTools->getConnectivityList(currLayoutBlock);
 for (int i = 0; i < cList->size(); i++) {
     LayoutConnectivity* lc = cList->at(i);
     if (lc->getBlock1()->getBlock() == block) {
         result->append((lc->getBlock2())->getBlock());
     } else if (lc->getBlock2()->getBlock() == block) {
         result->append((lc->getBlock1())->getBlock());
     }
 }
 return result;
}

/**
 * Returns a list of all anchor point boundaries involving the specified Block
 */
/*public*/ QVector<PositionablePoint*>* ConnectivityUtil::getAnchorBoundariesThisBlock(Block* block)
{
 QVector<PositionablePoint*>* list = new QVector<PositionablePoint*>();
 LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
 for (PositionablePoint* p : layoutEditor->getPositionablePoints()) {
        if ((p->getConnect2()!=nullptr) && (p->getConnect1()!=nullptr))
        {
                            if ((p->getConnect2()->getLayoutBlock()!=nullptr) && (p->getConnect1()->getLayoutBlock()!=nullptr)) {
                                if ( (((p->getConnect1())->getLayoutBlock()==lBlock) && ((p->getConnect2())->getLayoutBlock()!=lBlock)) ||
                                        (((p->getConnect1())->getLayoutBlock()!=lBlock) && ((p->getConnect2())->getLayoutBlock()==lBlock)) ) {
                                        list->append(p);
                                }
                            }
        }
    }
    return list;
}

/**
 * Returns a list of all levelXings involving the specified Block. To be returned, a levelXing must have all its
 *		four connections and all blocks must be assigned.  If any connection is missing, or if a block assignmnet
 *		is missing, an error message is printed and the level crossing is not added to the list->
 */
/*public*/ QVector<LevelXing*>* ConnectivityUtil::getLevelCrossingsThisBlock(Block* block) {
    QVector<LevelXing*>* list = new QVector<LevelXing*>();
    LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
    for (LevelXing* x : layoutEditor->getLevelXings()) {
        bool found = false;
        if ( (x->getLayoutBlockAC()==lBlock) || (x->getLayoutBlockBD()==lBlock) ) found = true;
        else if ( (x->getConnectA()!=nullptr) && (((TrackSegment*)x->getConnectA())->getLayoutBlock()==lBlock) )
            found = true;
        else if ( (x->getConnectB()!=nullptr) && (((TrackSegment*)x->getConnectB())->getLayoutBlock()==lBlock) )
            found = true;
        else if ( (x->getConnectC()!=nullptr) && (((TrackSegment*)x->getConnectC())->getLayoutBlock()==lBlock) )
            found = true;
        else if ( (x->getConnectD()!=nullptr) && (((TrackSegment*)x->getConnectD())->getLayoutBlock()==lBlock) )
            found = true;
        if (found) {
            if ( (x->getConnectA()!=nullptr) && (((TrackSegment*)x->getConnectA())->getLayoutBlock()!=nullptr) &&
                    (x->getConnectB()!=nullptr) && (((TrackSegment*)x->getConnectB())->getLayoutBlock()!=nullptr) &&
                    (x->getConnectC()!=nullptr) && (((TrackSegment*)x->getConnectC())->getLayoutBlock()!=nullptr) &&
                    (x->getConnectD()!=nullptr) && (((TrackSegment*)x->getConnectD())->getLayoutBlock()!=nullptr) &&
                    (x->getLayoutBlockAC()!=nullptr) && (x->getLayoutBlockBD()!=nullptr) ) {
                list->append(x);
            }
            else {
                log.error("Missing connection or block assignment at Level Crossing in Block "+block->getUserName());
            }
        }
    }
    return list;
}

//Need to search through code to find out where this is being used
/**
 * Returns a list of all layout turnouts involving the specified Block
 */
/*public*/ QVector<LayoutTurnout*>* ConnectivityUtil::getLayoutTurnoutsThisBlock(Block* block) {
    QVector<LayoutTurnout*>* list = new QVector<LayoutTurnout*>();
    LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
    QString lBlockName = block->getUserName();
    for (LayoutTurnout* t : layoutEditor->getLayoutTurnouts()) {
        if ( (t->getBlockName()==(lBlockName)) || (t->getBlockBName()==(lBlockName)) ||
                (t->getBlockCName()==(lBlockName)) || (t->getBlockDName()==(lBlockName)) ) list->append(t);
        else if ( (t->getConnectA()!=nullptr) && (((TrackSegment*)t->getConnectA())->getLayoutBlock()==lBlock) )
            list->append(t);
        else if ( (t->getConnectB()!=nullptr) && (((TrackSegment*)t->getConnectB())->getLayoutBlock()==lBlock) )
            list->append(t);
        else if ( (t->getConnectC()!=nullptr) && (((TrackSegment*)t->getConnectC())->getLayoutBlock()==lBlock) )
            list->append(t);
        else if ( (t->getConnectD()!=nullptr) && (((TrackSegment*)t->getConnectD())->getLayoutBlock()==lBlock) )
            list->append(t);
    }
//    for(LayoutSlip* ls:layoutEditor->slipList){
//        if(ls->getBlockName()==(lBlockName)){
//            list->append(ls);
//        } else if ( (ls->getConnectA()!=nullptr) && (((TrackSegment*)ls->getConnectA())->getLayoutBlock()==lBlock) )
//            list->append(ls);
//        else if ( (ls->getConnectB()!=nullptr) && (((TrackSegment*)ls->getConnectB())->getLayoutBlock()==lBlock) )
//            list->append(ls);
//        else if ( (ls->getConnectC()!=nullptr) && (((TrackSegment*)ls->getConnectC())->getLayoutBlock()==lBlock) )
//            list->append(ls);
//        else if ( (ls->getConnectD()!=nullptr) && (((TrackSegment*)ls->getConnectD())->getLayoutBlock()==lBlock) )
//            list->append(ls);
//    }
// djd debugging - lists turnouts for a block
// debugging code - comment out when not debugging something involving this method
//		String txt = "Turnouts for Block "+block.getUserName()+" - ";
//		for (int k = 0; k<list->size(); k++) {
//			if (k>0) txt = txt+", ";
//			if ( (list->get(k)).getTurnout()!=nullptr)
//				txt = txt+(list->get(k)).getTurnout().getSystemName();
//			else txt = txt+"???";
//		}
//		log.error(txt);
// end debugging code
    return list;
}

/**
 * Returns 'true' if specified Layout Turnout has required signal heads.
 * Returns 'false' if one or more of the required signals are missing.
 */
/*public*/ bool ConnectivityUtil::layoutTurnoutHasRequiredSignals(LayoutTurnout* t) {
    if (t->getLinkType()==LayoutTurnout::NO_LINK) {
        if ( (t->getTurnoutType()==LayoutTurnout::RH_TURNOUT) || (t->getTurnoutType()==LayoutTurnout::LH_TURNOUT) ||
                                (t->getTurnoutType()==LayoutTurnout::WYE_TURNOUT) ) {
            if ( (t->getSignalA1Name()!=nullptr) && (t->getSignalA1Name()!=("")) &&
                    (t->getSignalB1Name()!=nullptr) && (t->getSignalB1Name()!=("")) &&
                            (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) )
                return true;
            else return false;
        }
        else if (t->getTurnoutType()==LayoutTurnout::SINGLE_SLIP || t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP){
            if ((t->getSignalA1Name()!=nullptr) && (t->getSignalA1Name()!=("")) &&
                 (t->getSignalA2Name()!=nullptr) && (t->getSignalA2Name()!=("")) &&
                   (t->getSignalB1Name()!=nullptr) && (t->getSignalB1Name()!=("")) &&
                    (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) &&
                     (t->getSignalD1Name()!=nullptr) && (t->getSignalD1Name()!=("")) &&
                      (t->getSignalD2Name()!=nullptr) && (t->getSignalD2Name()!=(""))) {

                        if(t->getTurnoutType()==LayoutTurnout::SINGLE_SLIP){
                            return true;
                        }
                        if(t->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP){
                            if((t->getSignalB2Name()!=nullptr) && (t->getSignalB2Name()!=("")) &&
                                (t->getSignalC2Name()!=nullptr) && (t->getSignalC2Name()!=("")) ){
                                    return true;
                            }
                        }
            }
            return false;
        }
        else {
            if ( (t->getSignalA1Name()!=nullptr) && (t->getSignalA1Name()!=("")) &&
                    (t->getSignalB1Name()!=nullptr) && (t->getSignalB1Name()!=("")) &&
                        (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) &&
                                (t->getSignalD1Name()!=nullptr) && (t->getSignalD1Name()!=("")) )
                return true;
            else return false;
        }
    }
    else if (t->getLinkType()==LayoutTurnout::FIRST_3_WAY) {
        if ( (t->getSignalA1Name()!=nullptr) && (t->getSignalA1Name()!=("")) &&
                    (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) )
            return true;
        else return false;
    }
    else if (t->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
        if ( (t->getSignalB1Name()!=nullptr) && (t->getSignalB1Name()!=("")) &&
                    (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) )
            return true;
        else return false;
    }
    else if (t->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
        if ( (t->getSignalB1Name()!=nullptr) && (t->getSignalB1Name()!=("")) &&
                    (t->getSignalC1Name()!=nullptr) && (t->getSignalC1Name()!=("")) )
            return true;
        else return false;
    }
    return false;
}

/**
 * Returns the Signal Head at the Anchor block boundary
 * If 'facing' is 'true', returns the head that faces toward the specified Block
 * If 'facing' is 'false', returns the head that faces away from the specified Block
 */
/*public*/ SignalHead* ConnectivityUtil::getSignalHeadAtAnchor(PositionablePoint* p, Block* block, bool facing)
{
 if ( (p==nullptr) || (block==nullptr) )
 {
  log.error("nullptr arguments in call to getSignalHeadAtAnchor");
  return nullptr;
 }
 LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
#if 1
 if (((p->getConnect1())->getLayoutBlock()==lBlock) && ((p->getConnect2())->getLayoutBlock()!=lBlock))
 {
  if ( (leTools->isAtWestEndOfAnchor(p->getConnect2(), p) && facing) ||((!leTools->isAtWestEndOfAnchor(p->getConnect2(), p)) && (!facing)) )
   return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getWestBoundSignal());
  else
   return (((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getEastBoundSignal()));
 }
 else if (((p->getConnect1())->getLayoutBlock()!=lBlock) && ((p->getConnect2())->getLayoutBlock()==lBlock))
 {
  if ( (leTools->isAtWestEndOfAnchor(p->getConnect1(), p) && facing) || ((!leTools->isAtWestEndOfAnchor(p->getConnect1(), p)) && (!facing)) )
   return (((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getWestBoundSignal()));
  else
   return (((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getEastBoundSignal()));
 }
 else
 {
  // should never happen
  return nullptr;
 }
#endif
}

    /**
 * Returns the Signal Mast at the Anchor block boundary
 * If 'facing' is 'true', returns the head that faces toward the specified Block
 * If 'facing' is 'false', returns the head that faces away from the specified Block
 */
/*public*/ SignalMast* ConnectivityUtil::getSignalMastAtAnchor(PositionablePoint* p, Block* block, bool facing)
{
 if ( (p==nullptr) || (block==nullptr) )
 {
  log.error("nullptr arguments in call to getSignalHeadAtAnchor");
  return nullptr;
 }
 LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
 if (((p->getConnect1())->getLayoutBlock()==lBlock) && ((p->getConnect2())->getLayoutBlock()!=lBlock))
 {
  if ( (leTools->isAtWestEndOfAnchor(p->getConnect2(), p) && facing) || ((!leTools->isAtWestEndOfAnchor(p->getConnect2(), p)) && (!facing)) )
   return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getWestBoundSignalMastName());
  else
   return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getEastBoundSignalMastName());
 }
 else if (((p->getConnect1())->getLayoutBlock()!=lBlock) && ((p->getConnect2())->getLayoutBlock()==lBlock))
 {
  if ( (leTools->isAtWestEndOfAnchor(p->getConnect1(), p) && facing) || ((!leTools->isAtWestEndOfAnchor(p->getConnect1(), p)) && (!facing)) )
   return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getWestBoundSignalMastName());
  else
   return static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getEastBoundSignalMastName());
 }
 else
 {
  // should never happen
  return nullptr;
 }
}


//Signalmasts are only valid or requited on the boundary to a block.
/*public*/ bool ConnectivityUtil::layoutTurnoutHasSignalMasts(LayoutTurnout* t) {
    QStringList turnoutBlocks = t->getBlockBoundaries();
    bool valid = true;
    if(turnoutBlocks.at(0)!=nullptr && (t->getSignalAMast()==nullptr  || t->getSignalAMastName()==("")))
        valid = false;
    if(turnoutBlocks.at(1) !=nullptr && (t->getSignalBMast()==nullptr  || t->getSignalBMastName()==("")))
        valid = false;
    if(turnoutBlocks.at(2) !=nullptr && (t->getSignalCMast()==nullptr  || t->getSignalCMastName()==("")))
        valid = false;
    if(turnoutBlocks.at(3) !=nullptr && (t->getSignalDMast()==nullptr  || t->getSignalDMastName()==("")))
        valid = false;
    return valid;
}

/**
 * Returns the Signal Head at the level crossing
 * If 'facing' is 'true', returns the head that faces toward the specified Block
 * If 'facing' is 'false', returns the head that faces away from the specified Block
 */
/*public*/ SignalHead* ConnectivityUtil::getSignalHeadAtLevelXing(LevelXing* x, Block* block, bool facing)
{
 if ( (x==nullptr) || (block==nullptr) )
 {
  log.error("nullptr arguments in call to getSignalHeadAtLevelXing");
  return nullptr;
 }
 LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
 if ( (x->getConnectA()==nullptr) || (x->getConnectB()==nullptr) ||
                                        (x->getConnectC()==nullptr) || (x->getConnectD()==nullptr) )
 {
  log.error("Missing track around level crossing near Block "+block->getUserName());
  return nullptr;
 }
 if (((TrackSegment*)x->getConnectA())->getLayoutBlock()==lBlock)
 {
  if (facing)
   return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalCName());
  else
   return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalAName());
 }
 if (((TrackSegment*)x->getConnectB())->getLayoutBlock()==lBlock)
 {
  if (facing)
    return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalDName());
   else
    return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalBName());
  }
  if (((TrackSegment*)x->getConnectC())->getLayoutBlock()==lBlock)
  {
   if (facing)
    return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalAName());
   else
    return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalCName());
  }
  if (((TrackSegment*)x->getConnectD())->getLayoutBlock()==lBlock)
  {
  if (facing)
   return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalBName());
  else
   return ((SignalHeadManager*)InstanceManager::InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(x->getSignalDName());
 }
 return nullptr;
}

/**
 * Returns 'true' if the specified block is internal to the Level Xing, and if all else is OK.
 * Returns 'false' if one of the connecting Track Segments is in the Block, or if there is
 *		a problem with looking for a signal head.
 */
/*public*/ bool ConnectivityUtil::blockInternalToLevelXing(LevelXing* x, Block* block) {
    if ( (x==nullptr) || (block==nullptr) ) return false;
    LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
    if (lBlock==nullptr) return false;
    if ( (x->getConnectA()==nullptr) || (x->getConnectB()==nullptr) ||
                    (x->getConnectC()==nullptr) || (x->getConnectD()==nullptr) ) return false;
    if ( (x->getLayoutBlockAC()!=lBlock) && (x->getLayoutBlockBD()!=lBlock) ) return false;
    if (((TrackSegment*)x->getConnectA())->getLayoutBlock()==lBlock) return false;
    if (((TrackSegment*)x->getConnectB())->getLayoutBlock()==lBlock) return false;
    if (((TrackSegment*)x->getConnectC())->getLayoutBlock()==lBlock) return false;
    if (((TrackSegment*)x->getConnectD())->getLayoutBlock()==lBlock) return false;
    return true;
}

/**
 * Matches the anchor point to an Entry Point, and returns the direction specified in the Entry Point
 *   If no match is found, UNKNOWN is returned, indicating that the block boundary is internal to the
 *		Section.
 */
/*public*/ int ConnectivityUtil::getDirectionFromAnchor(QVector<EntryPoint*>* mForwardEntryPoints, QVector<EntryPoint*>* mReverseEntryPoints,                                           PositionablePoint* p) {
    Block* block1 = p->getConnect1()->getLayoutBlock()->getBlock();
    Block* block2 = p->getConnect2()->getLayoutBlock()->getBlock();
    for (int i = 0; i<mForwardEntryPoints->size(); i++) {
        EntryPoint* ep = mForwardEntryPoints->at(i);
        if ( ((ep->getBlock()==block1) && (ep->getFromBlock()==block2)) ||
                ((ep->getBlock()==block2) && (ep->getFromBlock()==block1)) )
            return EntryPoint::FORWARD;
    }
    for (int j = 0; j<mReverseEntryPoints->size(); j++) {
        EntryPoint* ep = mReverseEntryPoints->at(j);
        if ( ((ep->getBlock()==block1) && (ep->getFromBlock()==block2)) ||
                ((ep->getBlock()==block2) && (ep->getFromBlock()==block1)) )
            return EntryPoint::REVERSE;
    }
    return EntryPoint::UNKNOWN;
}

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
/*public*/ bool ConnectivityUtil::isInternalLevelXingAC(LevelXing* x, Block* block) {
    LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
    if ( (((TrackSegment*)x->getConnectA())->getLayoutBlock()==lBlock) &&
            (((TrackSegment*)x->getConnectC())->getLayoutBlock()==lBlock) ) {
        if (x->getLayoutBlockAC()==lBlock) {
            return true;
        }
        else {
            log.error("Panel blocking error at AC of Level Crossing in Block "+block->getUserName());
            return false;
        }
    }
    return false;
}

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
/*public*/ bool ConnectivityUtil::isInternalLevelXingBD(LevelXing* x, Block* block) {
    LayoutBlock* lBlock = layoutBlockManager->getByUserName(block->getUserName());
    if ( (((TrackSegment*)x->getConnectB())->getLayoutBlock()==lBlock) &&
            (((TrackSegment*)x->getConnectD())->getLayoutBlock()==lBlock) ) {
        if (x->getLayoutBlockBD()==lBlock) {
            return true;
        }
        else {
            log.error("Panel blocking error at BD of Level Crossing in Block "+block->getUserName());
            return false;
        }
    }
    return false;
}


/*
 * Adds the specified sensor ('name') to the SSL for the specified signal head
 * 'name' should be the system name for the sensor.
 * Returns 'true' if the sensor was already in the signal head SSL or if it has been
 *		added successfully.  Returns 'false' and logs an error if not->
 * If the SSL has not been set up yet, the sensor is not added, an error message is output,
 *		and 'false' is returned.
 * Parameters: 'name' - sensor name, 'sh' - signal head, 'where' should be DIVERGING if the sensor
 *		is being added to the diverging (second) part of a facing mode SSL, 'CONTINUING' if
 *		the sensor is being added to the continuing (first) part of a facing mode SSL, OVERALL if
 *		the sensor is being added to the overall sensor list of a facing mode SSL. 'where' is
 *		ignored if not a facing mode SSL.
 */
/*public*/ bool ConnectivityUtil::addSensorToSignalHeadLogic(QString name, SignalHead* sh, int where) {
    if (sh==nullptr) {
        log.error("Null signal head on entry to addSensorToSignalHeadLogic");
        return false;
    }
    if ( (name==nullptr) || name==("") ) {
        log.error("Null string for sensor name on entry to addSensorToSignalHeadLogic");
        return false;
    }
    BlockBossLogic* bbLogic = BlockBossLogic::getStoppedObject(((AbstractSignalHead*)sh)->getSystemName());
    if (bbLogic==nullptr) {
        log.error("Trouble opening BlockBossLogic for "+((AbstractSignalHead*)sh)->getSystemName());
        return false;
    }
    int mode = bbLogic->getMode();
    if ( ((mode==BlockBossLogic::SINGLEBLOCK) || (mode==BlockBossLogic::TRAILINGMAIN) ||
                (mode==BlockBossLogic::TRAILINGDIVERGING)) || ((mode==BlockBossLogic::FACING) &&
                    (where==OVERALL)) ) {
        if ( ( (bbLogic->getSensor1()!=nullptr) && (bbLogic->getSensor1())==(name) ) ||
                ( (bbLogic->getSensor2()!=nullptr) && (bbLogic->getSensor2())==(name) ) ||
                ( (bbLogic->getSensor3()!=nullptr) && (bbLogic->getSensor3())==(name) ) ||
                ( (bbLogic->getSensor4()!=nullptr) && (bbLogic->getSensor4())==(name) ) ||
                ( (bbLogic->getSensor5()!=nullptr) && (bbLogic->getSensor5())==(name) ) ) {
            bbLogic->retain();
            bbLogic->start();
            return true;
        }
        if (bbLogic->getSensor1()==nullptr) bbLogic->setSensor1(name);
        else if (bbLogic->getSensor2()==nullptr) bbLogic->setSensor2(name);
        else if (bbLogic->getSensor3()==nullptr) bbLogic->setSensor3(name);
        else if (bbLogic->getSensor4()==nullptr) bbLogic->setSensor4(name);
        else if (bbLogic->getSensor5()==nullptr) bbLogic->setSensor5(name);
        else {
            log.error("Error - could not add sensor to SSL for signal head "+((AbstractSignalHead*)sh)->getSystemName()+
                                    " because there is no room in the SSL.");
            bbLogic->retain();
            bbLogic->start();
            return false;
        }
    }
    else if (mode==BlockBossLogic::FACING) {
        if (where==DIVERGING) {
            if ( ( (bbLogic->getWatchedSensor2()!=nullptr) && (bbLogic->getWatchedSensor2())==(name) ) ||
                    ( (bbLogic->getWatchedSensor2Alt()!=nullptr) && (bbLogic->getWatchedSensor2Alt())==(name) ) ) {
                bbLogic->retain();
                bbLogic->start();
                return true;
            }
            if (bbLogic->getWatchedSensor2()==nullptr) bbLogic->setWatchedSensor2(name);
            else if (bbLogic->getWatchedSensor2Alt()==nullptr) bbLogic->setWatchedSensor2Alt(name);
            else {
                log.error("Error - could not add watched sensor to SSL for signal head "+((AbstractSignalHead*)sh)->getSystemName()+
                                    " because there is no room in the facing SSL diverging part->");
                bbLogic->retain();
                bbLogic->start();
                return false;
            }
        }
        else if (where==CONTINUING) {
            if ( ( (bbLogic->getWatchedSensor1()!=nullptr) && (bbLogic->getWatchedSensor1())==(name) ) ||
                    ( (bbLogic->getWatchedSensor1Alt()!=nullptr) && (bbLogic->getWatchedSensor1Alt())==(name) ) ) {
                bbLogic->retain();
                bbLogic->start();
                return true;
            }
            if (bbLogic->getWatchedSensor1()==nullptr) bbLogic->setWatchedSensor1(name);
            else if (bbLogic->getWatchedSensor1Alt()==nullptr) bbLogic->setWatchedSensor1Alt(name);
            else {
                log.error("Error - could not add watched sensor to SSL for signal head "+((AbstractSignalHead*)sh)->getSystemName()+
                                    " because there is no room in the facing SSL continuing part->");
                bbLogic->retain();
                bbLogic->start();
                return false;
            }
        }
        else {
            log.error("Error - could not add watched sensor to SSL for signal head "+((AbstractSignalHead*)sh)->getSystemName()+
                                    "because 'where' to place the sensor was not correctly designated.");
            bbLogic->retain();
            bbLogic->start();
            return false;
        }
    }
    else {
        log.error("SSL has not been set up for signal head "+((AbstractSignalHead*)sh)->getSystemName()+
                            ". Could not add sensor - "+name+".");
        return false;
    }
    bbLogic->retain();
    bbLogic->start();
    return true;
}

/*
 * Revoves the specified sensors ('names') from the SSL for the specified signal head if
 *      any of the sensors is currently in the SSL.
 * Returns 'false' if an error was found, and issues a message to the error log.
 * Returns 'true' if no error, whether any sensors were found or not->
 */
/*public*/ bool ConnectivityUtil::removeSensorsFromSignalHeadLogic(QStringList* names, SignalHead* sh) {
    if (sh==nullptr) {
        log.error("Null signal head on entry to removeSensorsFromSignalHeadLogic");
        return false;
    }
    if (names==nullptr) {
        log.error("Null QVector of sensor names on entry to removeSensorsFromSignalHeadLogic");
        return false;
    }
    BlockBossLogic* bbLogic = BlockBossLogic::getStoppedObject(((AbstractSignalHead*)sh)->getSystemName());
    if (bbLogic==nullptr)
    {
     log.error("Trouble opening BlockBossLogic for "+((AbstractSignalHead*)sh)->getSystemName());
        return false;
    }
    for (int i = 0; i<names->size(); i++)
    {
     QString name = names->at(i);
     if ( (bbLogic->getSensor1()!=nullptr) && (bbLogic->getSensor1())==(name) )
            bbLogic->setSensor1(nullptr);
     if ( (bbLogic->getSensor2()!=nullptr) && (bbLogic->getSensor2())==(name) )
            bbLogic->setSensor2(nullptr);
     if ( (bbLogic->getSensor3()!=nullptr) && (bbLogic->getSensor3())==(name) )
            bbLogic->setSensor3(nullptr);
     if ( (bbLogic->getSensor4()!=nullptr) && (bbLogic->getSensor4())==(name) )
            bbLogic->setSensor4(nullptr);
     if ( (bbLogic->getSensor5()!=nullptr) && (bbLogic->getSensor5())==(name) )
            bbLogic->setSensor5(nullptr);
     if (bbLogic->getMode()==BlockBossLogic::FACING)
     {
      if ( (bbLogic->getWatchedSensor1()!=nullptr) && (bbLogic->getWatchedSensor1())==(name) )
       bbLogic->setWatchedSensor1(nullptr);
      if ( (bbLogic->getWatchedSensor1Alt()!=nullptr) && (bbLogic->getWatchedSensor1Alt())==(name) )
                bbLogic->setWatchedSensor1Alt(nullptr);
      if ( (bbLogic->getWatchedSensor2()!=nullptr) && (bbLogic->getWatchedSensor2())==(name) )
                bbLogic->setWatchedSensor2(nullptr);
      if ( (bbLogic->getWatchedSensor2Alt()!=nullptr) && (bbLogic->getWatchedSensor2Alt())==(name) )
                bbLogic->setWatchedSensor2Alt(nullptr);
     }
    }
    if (bbLogic->getMode()==0) {
        // this to avoid Unexpected mode ERROR message at startup
        bbLogic->setMode(BlockBossLogic::SINGLEBLOCK);
    }
    bbLogic->retain();
    bbLogic->start();
    return true;
}

/**
 * Returns the next Node following the specified TrackNode
 *<P>
 * If the specified track node can lead to different paths to the next node, for example,
 *       if the specified track node is a turnout entered at its throat, then "cNodeState"
 *       must be specified to choose between the possible paths.
 * Returns a TrackNode if one is reached. Returns nullptr if trouble following the track.
 * .
 */
/*public*/ TrackNode* ConnectivityUtil::getNextNode(TrackNode* cNode, int cNodeState) {
    if (cNode==nullptr) {
        log.error("getNextNode called with a nullptr Track Node");
        return nullptr;
    }
    if (cNode->reachedEndOfTrack()) {
        log.error("getNextNode - attempt to search past endBumper");
        return nullptr;
    }
    return (getTrackNode(cNode->getNode(), cNode->getNodeType(), cNode->getTrackSegment(), cNodeState));
}

/**
 * Returns the next Node following the node specified by "cNode" and "cNodeType", assuming that cNode was
 *       reached via the specified TrackSegment->
 *<P>
 * If the specified track node can lead to different paths to the next node, for example,
 *       if the specified track node is a turnout entered at its throat, then "cNodeState"
 *       must be specified to choose between the possible paths. If cNodeState = 0, the search
 *		 will follow the 'continuing' track; if cNodeState = 1, the search will follow the
 *		 'diverging' track; if cNodeState = 2 (3-way turnouts only), the search will follow
 *		 the second 'diverging' track.
 *<P>
 * In determining which track is the 'continuing' track for RH, LH, and WYE turnouts, this search
 *		 routine uses the layout turnout's 'continuingState'.
 *<P>
 * When following track, this method skips over anchor points that are not block boundaries.
 *<P>
 * When following track, this method treats a modelled 3-way turnout as a single turnout-> It also
 *		treats two THROAT_TO_THROAT turnouts as a single turnout, but with each turnout having a
 *		continuing sense.
 *<P>
 * Returns a TrackNode if a node or end_of-track is reached. Returns nullptr if trouble following the track.
 */
/*public*/ TrackNode* ConnectivityUtil::getTrackNode(LayoutTrack* cNode, int cNodeType, TrackSegment* /*cTrack*/, int cNodeState)
{
 // initialize
 LayoutTrack* node = nullptr;
 int nodeType = LayoutEditor::NONE;
 TrackSegment* track = nullptr;
 bool hitEnd = false;
 //@SuppressWarnings("unused")
 int pType = cNodeType;
 LayoutTrack* pObject = cNode;
 TrackSegment* tTrack = nullptr;
 switch (cNodeType)
 {
  case LayoutEditor::POS_POINT:
   if (qobject_cast<PositionablePoint*>( cNode))
   {
    PositionablePoint* p = (PositionablePoint*)cNode;
    if (p->getType()==PositionablePoint::END_BUMPER)
    {
     log.error("Attempt to search beyond end of track");
     return nullptr;
    }
    if (p->getConnect1()==tTrack)
    {
     tTrack = p->getConnect2();
    }
    else
    {
     tTrack = p->getConnect1();
    }
   }
   else
   {
     log.warn("cNodeType wrong for cNode");
   }
   break;
  case LayoutTrack::TURNOUT_A:
  {
   if (qobject_cast<LayoutTurnout*>(cNode))
   {
    LayoutTurnout* lt = (LayoutTurnout*) cNode;
    if ((lt->getTurnoutType() == LayoutTurnout::RH_TURNOUT)
            || (lt->getTurnoutType() == LayoutTurnout::LH_TURNOUT)
            || (lt->getTurnoutType() == LayoutTurnout::WYE_TURNOUT))
    {
     if ((lt->getLinkedTurnoutName() == "")
            || (lt->getLinkedTurnoutName().isEmpty()))
     {
      if (lt->getContinuingSense() == Turnout::CLOSED)
      {
       switch (cNodeState)
       {
        case 0:
            tTrack = (TrackSegment*) lt->getConnectB();
            pType = LayoutTrack::TURNOUT_B;
            break;
        case 1:
            tTrack = (TrackSegment*) lt->getConnectC();
            pType = LayoutTrack::TURNOUT_C;
            break;
        default:
            log.error("Bad cNodeState argument when searching track-std. normal");
            return nullptr;
       }
      }
      else
      {
       switch(cNodeState)
       {
       case 0:
              tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectC();
              pType = LayoutEditor::TURNOUT_C;
       case 1:
              tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectB();
              pType = LayoutEditor::TURNOUT_B;
       default:
              log.error("Bad cNodeState argument when searching track-std reversed");
              return nullptr;
       }
      }
     }
     else
     {
      // linked turnout - node type A
      LayoutTurnout* lto = layoutEditor->getFinder()->findLayoutTurnoutByName(lt->getLinkedTurnoutName());
      if (((LayoutTurnout*)cNode)->getLinkType()==LayoutTurnout::THROAT_TO_THROAT)
      {
       switch(cNodeState)
       {
       case 0:
        if (lto->getContinuingSense()==Turnout::CLOSED) {
            tTrack = (TrackSegment*)lto->getConnectB();
            pType = LayoutEditor::TURNOUT_B;
        }
        else {
            tTrack = (TrackSegment*)lto->getConnectC();
            pType = LayoutEditor::TURNOUT_C;
        }
        pObject = lto;
        break;
       case 1:
        if (lto->getContinuingSense()==Turnout::CLOSED) {
            tTrack = (TrackSegment*)lto->getConnectC();
            pType = LayoutEditor::TURNOUT_C;
        }
        else {
            tTrack = (TrackSegment*)lto->getConnectB();
            pType = LayoutEditor::TURNOUT_B;
        }
        break;
       case 2:
        if (lto->getContinuingSense() == Turnout::CLOSED) {
            tTrack = (TrackSegment*) lto->getConnectC();
            pType = LayoutTrack::TURNOUT_C;
        } else {
            tTrack = (TrackSegment*) lto->getConnectB();
            pType = LayoutTrack::TURNOUT_B;
        }
        pObject = lto;
        break;
       default:
        log.error("Bad cNodeState argument when searching track - THROAT_TO_THROAT");
        return nullptr;
       }
       pObject = lto;
      }
      else if (((LayoutTurnout*)cNode)->getLinkType()==LayoutTurnout::FIRST_3_WAY)
      {
       switch (cNodeState)
       {
       case 0:
        if (lto->getContinuingSense()==Turnout::CLOSED) {
            tTrack = (TrackSegment*)lto->getConnectB();
            pType = LayoutEditor::TURNOUT_B;
        }
        else {
            tTrack = (TrackSegment*)lto->getConnectC();
            pType = LayoutEditor::TURNOUT_C;
        }
        pObject = lto;
        break;
       case 1:
        if (((LayoutTurnout*)cNode)->getContinuingSense()==Turnout::CLOSED)
        {
            tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectC();
            pType = LayoutEditor::TURNOUT_C;
        }
        else {
            tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectB();
            pType = LayoutEditor::TURNOUT_B;
        }
        break;
       case 2:
        if (lto->getContinuingSense()==Turnout::CLOSED) {
            tTrack = (TrackSegment*)lto->getConnectC();
            pType = LayoutEditor::TURNOUT_C;
        }
        else {
            tTrack = (TrackSegment*)lto->getConnectB();
            pType = LayoutEditor::TURNOUT_B;
        }
        pObject = lto;
        break;
       default:
        log.error("Bad cNodeState argument when searching track - FIRST_3_WAY");
        return nullptr;
       }
      }
     }
    }
    else if ( (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
             (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
             (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) )
    {
     // crossover turnout - node type A
     switch(cNodeState)
     {
     case 0:
      tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectB();
      pType = LayoutEditor::TURNOUT_B;
      break;
     case 1:
      if ( (cNodeType==LayoutEditor::TURNOUT_A) &&
                  (!(((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_XOVER)) )
      {
          tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectC();
          pType = LayoutEditor::TURNOUT_C;
      }
      else
      {
          log.error("Request to follow not allowed switch setting at LH_XOVER or RH_OVER");
          return nullptr;
      }
      break;
     default:
      log.error("Bad cNodeState argument when searching track- XOVER A");
      return nullptr;
     }
    }
   }
   else
   {
    log.error("cNodeType wrong for cNode");
   }
   break;
  }
  case LayoutTrack::TURNOUT_B:
  case LayoutTrack::TURNOUT_C:
  {
         if ( (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_TURNOUT) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_TURNOUT) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::WYE_TURNOUT) ) {
             if ( (((LayoutTurnout*)cNode)->getLinkedTurnoutName()==nullptr) ||
                         (((LayoutTurnout*)cNode)->getLinkedTurnoutName()==("")) ||
                             (((LayoutTurnout*)cNode)->getLinkType()==LayoutTurnout::FIRST_3_WAY) ) {
                 tTrack = (TrackSegment*)(((LayoutTurnout*)cNode)->getConnectA());
                 pType = LayoutEditor::TURNOUT_A;
             }
             else {
                 LayoutTurnout* lto = layoutEditor->getFinder()->findLayoutTurnoutByName(((LayoutTurnout*)cNode)->getLinkedTurnoutName());
                 if (((LayoutTurnout*)cNode)->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
                     tTrack = (TrackSegment*)(lto->getConnectA());
                     pType = LayoutEditor::TURNOUT_A;
                 }
                 else if (((LayoutTurnout*)cNode)->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
                     if (cNodeState==0) {
                             if (lto->getContinuingSense()==Turnout::CLOSED) {
                             tTrack = (TrackSegment*)lto->getConnectB();
                             pType = LayoutEditor::TURNOUT_B;
                         }
                         else {
                             tTrack = (TrackSegment*)lto->getConnectC();
                             pType = LayoutEditor::TURNOUT_C;
                         }
                     }
                     else if (cNodeState==1) {
                         if (lto->getContinuingSense()==Turnout::CLOSED) {
                             tTrack = (TrackSegment*)lto->getConnectC();
                             pType = LayoutEditor::TURNOUT_C;
                         }
                         else {
                             tTrack = (TrackSegment*)lto->getConnectB();
                             pType = LayoutEditor::TURNOUT_B;
                         }
                     }
                     else {
                         log.error("Bad cNodeState argument when searching track - THROAT_TO_THROAT - 2");
                         return nullptr;
                     }
                 }
                 pObject = lto;
             }
         }
         else if ( (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ) {
             if (cNodeState==0) {
                 if (cNodeType==LayoutEditor::TURNOUT_B) {
                     tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectA();
                     pType = LayoutEditor::TURNOUT_A;
                 }
                 else if (cNodeType==LayoutEditor::TURNOUT_C) {
                     tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectD();
                     pType = LayoutEditor::TURNOUT_D;
                 }
             }
             else if (cNodeState==1) {
                 if ( (cNodeType==LayoutEditor::TURNOUT_C) &&
                             (!(((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_XOVER)) ) {
                     tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectA();
                     pType = LayoutEditor::TURNOUT_A;
                 }
                 else if ( (cNodeType==LayoutEditor::TURNOUT_B) &&
                             (!(((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_XOVER)) ){
                     tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectD();
                     pType = LayoutEditor::TURNOUT_D;
                 }
                 else {
                     log.error("Request to follow not allowed switch setting at LH_XOVER or RH_OVER");
                     return nullptr;
                 }
             }
             else {
                 log.error("Bad cNodeState argument when searching track - XOVER B or C");
                 return nullptr;
             }
         }
         break;
 }
     case LayoutTrack::TURNOUT_D:
 {
         if ( (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                 (((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ) {
             if (cNodeState==0) {
                 tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectC();
                 pType = LayoutEditor::TURNOUT_C;
             }
             else if (cNodeState==1) {
                 if (!(((LayoutTurnout*)cNode)->getTurnoutType()==LayoutTurnout::RH_XOVER)) {
                     tTrack = (TrackSegment*)((LayoutTurnout*)cNode)->getConnectB();
                     pType = LayoutEditor::TURNOUT_B;
                 }
                 else {
                     log.error("Request to follow not allowed switch setting at LH_XOVER or RH_OVER");
                     return nullptr;
                 }
             }
             else {
                 log.error("Bad cNodeState argument when searching track - XOVER D");
                 return nullptr;
             }
         }
         else {
             log.error ("Bad traak node type - TURNOUT_D, but not a crossover turnout");
             return nullptr;
         }
         break;
 }
     case LayoutEditor::LEVEL_XING_A :

         tTrack = (TrackSegment*)((LevelXing*)cNode)->getConnectC();
         pType = LayoutEditor::LEVEL_XING_C;
         break;
     case LayoutEditor::LEVEL_XING_B :
         tTrack = (TrackSegment*)((LevelXing*)cNode)->getConnectD();
         pType = LayoutEditor::LEVEL_XING_D;
         break;
     case LayoutEditor::LEVEL_XING_C:
         tTrack = (TrackSegment*)((LevelXing*)cNode)->getConnectA();
         pType = LayoutEditor::LEVEL_XING_A;
         break;
     case LayoutEditor::LEVEL_XING_D:
         tTrack = (TrackSegment*)((LevelXing*)cNode)->getConnectB();
         pType = LayoutEditor::LEVEL_XING_B;
         break;
     case LayoutEditor::SLIP_A :
         if(cNodeState==0){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectC();
             pType = LayoutEditor::SLIP_C;
         } else if (cNodeState ==1){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectD();
             pType = LayoutEditor::SLIP_D;
         }
         break;
     case LayoutEditor::SLIP_B :
         if(cNodeState==0){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectD();
             pType = LayoutEditor::SLIP_D;
         } else if (cNodeState==1 && (((LayoutSlip*)cNode)->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP)){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectC();
             pType = LayoutEditor::SLIP_C;
         } else {
             log.error("Request to follow not allowed on a single slip");
             return nullptr;
         }
         break;
     case LayoutEditor::SLIP_C:
         if(cNodeState==0){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectA();
             pType = LayoutEditor::SLIP_A;
         } else if (cNodeState==1 && (((LayoutSlip*)cNode)->getTurnoutType()==LayoutTurnout::DOUBLE_SLIP)){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectB();
             pType = LayoutEditor::SLIP_B;
         } else {
             log.error("Request to follow not allowed on a single slip");
             return nullptr;
         }
         break;
     case LayoutEditor::SLIP_D:
         if(cNodeState==0){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectB();
             pType = LayoutEditor::SLIP_B;
         } else if (cNodeState ==1){
             tTrack = (TrackSegment*)((LayoutSlip*)cNode)->getConnectA();
             pType = LayoutEditor::SLIP_A;
         }
         break;
     default:
         log.error("Unable to initiate 'getTrackNode'.  Probably bad input Track Node.");
         return nullptr;
 }

 // follow track to anchor block boundary, turnout, or level crossing
 bool hasNode = false;
 LayoutTrack* tObject = nullptr;
 int tType = 0;
 if (tTrack==nullptr){
     log.error("Error tTrack is nullptr!");
     return nullptr;
 }
 while (!hasNode) {
     if (tTrack->getConnect1()==pObject) {
         tObject = tTrack->getConnect2();
         tType = tTrack->getType2();
     }
     else {
         tObject = tTrack->getConnect1();
         tType = tTrack->getType1();
     }
     if (tObject==nullptr) {
         log.error("Error while following track looking for next node");
         return nullptr;
     }
     if (tType!=LayoutEditor::POS_POINT) {
         node = tObject;
         nodeType = tType;
         track = tTrack;
         hasNode = true;
     }
     else {
         PositionablePoint* p = (PositionablePoint*)tObject;
         if (p->getType()==PositionablePoint::END_BUMPER) {
             hitEnd = true;
             hasNode = true;
         }
         else {
             TrackSegment* con1 = p->getConnect1();
             TrackSegment* con2 = p->getConnect2();
             if ( (con1==nullptr) || (con2==nullptr) ) {
                 log.error("Error - Breakin connectivity at Anchor Point when searching for track node");
                 return nullptr;
             }
             if (con1->getLayoutBlock()!=con2->getLayoutBlock()) {
                 node = tObject;
                 nodeType = LayoutEditor::POS_POINT;
                 track = tTrack;
                 hasNode = true;
             }
             else {
                 if (con1==tTrack)
                     tTrack = con2;
                 else
                     tTrack = con1;
                 pObject = tObject;
             }
         }
     }
 }
 return (new TrackNode(node, nodeType, track, hitEnd, cNodeState));
}

/**
 * Returns an "exit block" for the specified track node if there is one, else returns nullptr.
 * An "exit block" must be different from the block of the track segment in the node.
 * If the node is a PositionablePoint, it is assumed to be a block boundary anchor point->
 * If an "excludedBlock" is entered, that block will not be returned as the exit block of
 *		a Node of type TURNOUT_x->
 */
/*public*/ Block* ConnectivityUtil::getExitBlockForTrackNode(TrackNode* node, Block* excludedBlock) {
    if ( (node==nullptr) || node->reachedEndOfTrack() ) return nullptr;
    Block* block = nullptr;
    Block* tBlock = nullptr;
    LayoutTurnout* lt = nullptr;
    LevelXing* x = nullptr;
    switch (node->getNodeType())
    {
    case LayoutEditor::POS_POINT:
    {
      PositionablePoint* p = (PositionablePoint*)node->getNode();
      block = p->getConnect1()->getLayoutBlock()->getBlock();
      if (block==node->getTrackSegment()->getLayoutBlock()->getBlock())
      block = p->getConnect2()->getLayoutBlock()->getBlock();
      break;
    }
    case LayoutEditor::TURNOUT_A:
      lt = (LayoutTurnout*)node->getNode();
      tBlock = ((TrackSegment*)lt->getConnectB())->getLayoutBlock()->getBlock();
      if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                    (tBlock!=excludedBlock) ) block = tBlock;
      else if (lt->getTurnoutType()!=LayoutTurnout::LH_XOVER)
      {
       tBlock = ((TrackSegment*)lt->getConnectC())->getLayoutBlock()->getBlock();
       if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
     }
      break;
    case LayoutEditor::TURNOUT_B:
      lt = (LayoutTurnout*)node->getNode();
      tBlock = ((TrackSegment*)lt->getConnectA())->getLayoutBlock()->getBlock();
      if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                    (tBlock!=excludedBlock) ) block = tBlock;
      else if ( (lt->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                        (lt->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) )
      {
       tBlock = ((TrackSegment*)lt->getConnectD())->getLayoutBlock()->getBlock();
       if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
      }
      break;
    case LayoutEditor::TURNOUT_C:
     lt = (LayoutTurnout*)node->getNode();
     if (lt->getTurnoutType()!=LayoutTurnout::LH_XOVER)
     {
       tBlock = ((TrackSegment*)lt->getConnectA())->getLayoutBlock()->getBlock();
        if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                (tBlock!=excludedBlock) ) block = tBlock;
     }
     if ( (block==nullptr) && ((lt->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                (lt->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER)) )
     {
        tBlock = ((TrackSegment*)lt->getConnectD())->getLayoutBlock()->getBlock();
        if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                (tBlock!=excludedBlock) ) block = tBlock;
     }
     break;
    case LayoutEditor::TURNOUT_D:
            lt = (LayoutTurnout*)node->getNode();
            if ( (lt->getTurnoutType()==LayoutTurnout::LH_XOVER) ||
                        (lt->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ) {
                tBlock = ((TrackSegment*)lt->getConnectB())->getLayoutBlock()->getBlock();
                if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
            }
            break;
    case LayoutEditor::LEVEL_XING_A:
            x = (LevelXing*)node->getNode();
            tBlock = ((TrackSegment*)x->getConnectC())->getLayoutBlock()->getBlock();
            if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
    case LayoutEditor::LEVEL_XING_B:
            x = (LevelXing*)node->getNode();
            tBlock = ((TrackSegment*)x->getConnectD())->getLayoutBlock()->getBlock();
            if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
            break;
    case LayoutEditor::LEVEL_XING_C:
            x = (LevelXing*)node->getNode();
            tBlock = ((TrackSegment*)x->getConnectA())->getLayoutBlock()->getBlock();
            if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
            break;
    case LayoutEditor::LEVEL_XING_D:
            x = (LevelXing*)node->getNode();
            tBlock = ((TrackSegment*)x->getConnectB())->getLayoutBlock()->getBlock();
            if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
            break;
    case LayoutEditor::SLIP_A:
    {
            LayoutSlip* ls = (LayoutSlip*)node->getNode();
            tBlock = ((TrackSegment*)ls->getConnectC())->getLayoutBlock()->getBlock();
            if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                    (tBlock!=excludedBlock) ) block = tBlock;
            else {
                tBlock = ((TrackSegment*)ls->getConnectD())->getLayoutBlock()->getBlock();
                if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
            }
            break;
    }
    case LayoutEditor::SLIP_B:
    {
     LayoutSlip*        ls = (LayoutSlip*)node->getNode();
            tBlock = ((TrackSegment*)ls->getConnectD())->getLayoutBlock()->getBlock();
            if(ls->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                //Double slip
                if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
                else {
                    tBlock = ((TrackSegment*)ls->getConnectC())->getLayoutBlock()->getBlock();
                    if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                            (tBlock!=excludedBlock) ) block = tBlock;
                }
            } else{
                if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
            }
            break;
    }
    case LayoutEditor::SLIP_C:
    {
     LayoutSlip* ls = (LayoutSlip*)node->getNode();
            tBlock = ((TrackSegment*)ls->getConnectA())->getLayoutBlock()->getBlock();
            if(ls->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
                else {
                    tBlock = ((TrackSegment*)ls->getConnectB())->getLayoutBlock()->getBlock();
                    if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                            (tBlock!=excludedBlock) ) block = tBlock;
     }
    }
    else
    {
     if (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) block = tBlock;
    }
    break;
  }
  case LayoutEditor::SLIP_D:
  {
   LayoutSlip* ls = (LayoutSlip*)node->getNode();
   tBlock = ((TrackSegment*)ls->getConnectB())->getLayoutBlock()->getBlock();
   if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                    (tBlock!=excludedBlock) ) block = tBlock;
   else
   {
    tBlock = ((TrackSegment*)ls->getConnectA())->getLayoutBlock()->getBlock();
    if ( (tBlock!=node->getTrackSegment()->getLayoutBlock()->getBlock()) &&
                        (tBlock!=excludedBlock) ) block = tBlock;
   }
   break;
  }
  default : break;
 }
 return block;
}

// support methods

/**
 * Initializes the setting (as an object), sets the new track segment (if in Block), and sets the
 *    prevConnectType.
 */
/*private*/ int ConnectivityUtil::getTurnoutSetting(LayoutTurnout* lt, int cType, bool suppress) {
    prevConnectObject = lt;
    int setting = Turnout::THROWN;
    int tType = lt->getTurnoutType();
#if 1 //TODO
    if(qobject_cast<LayoutSlip*>(lt))
    {
     setting = LayoutSlip::UNKNOWN;
     LayoutSlip* ls = (LayoutSlip*)lt;
     int tType = ls->getTurnoutType();
     switch(cType)
     {
      case LayoutEditor::SLIP_A :
       if(nextLayoutBlock==((TrackSegment*)ls->getConnectC())->getLayoutBlock())
       {
        // exiting block at C
        prevConnectType= LayoutEditor::SLIP_A;
        setting = LayoutSlip::STATE_AC;
        ts = (TrackSegment*)ls->getConnectC();
       } else if (nextLayoutBlock==((TrackSegment*)ls->getConnectD())->getLayoutBlock())
       {

         // exiting block at D
         prevConnectType= LayoutEditor::SLIP_A;
         setting = LayoutSlip::STATE_AD;
         ts = (TrackSegment*)ls->getConnectD();
       } else if (currLayoutBlock==((TrackSegment*)ls->getConnectC())->getLayoutBlock() &&
             currLayoutBlock!=((TrackSegment*)ls->getConnectD())->getLayoutBlock())
       {
         // block continues at C only
         ts = (TrackSegment*)lt->getConnectC();
         setting = LayoutSlip::STATE_AC;
         prevConnectType = LayoutEditor::SLIP_A;

       } else if (currLayoutBlock==((TrackSegment*)ls->getConnectD())->getLayoutBlock() &&
             currLayoutBlock!=((TrackSegment*)ls->getConnectC())->getLayoutBlock()) {
         // block continues at D only
         setting = LayoutSlip::STATE_AD;
         ts = (TrackSegment*)lt->getConnectD();
         prevConnectType = LayoutEditor::SLIP_A;
     } else {
         if((ls->getConnectC()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectC(), (QObject*)ls)){
             prevConnectType = LayoutEditor::SLIP_C;
             setting = LayoutSlip::STATE_AC;
             ts = (TrackSegment*)lt->getConnectC();
         } else if((ls->getConnectD()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectD(), (QObject*)ls)){
             prevConnectType = LayoutEditor::SLIP_D;
             setting = LayoutSlip::STATE_AD;
             ts = (TrackSegment*)lt->getConnectD();
         }
         else {
             log.error("Error - Neither branch at track node leads to requested Block.(LS1)");
             _tr=nullptr;
         }
     }
     break;
    case LayoutEditor::SLIP_B :  if(nextLayoutBlock==((TrackSegment*)ls->getConnectD())->getLayoutBlock())
      {
       // exiting block at D
       prevConnectType= LayoutEditor::SLIP_D;
       setting = LayoutSlip::STATE_BD;
       ts = (TrackSegment*)ls->getConnectD();
      } else if (nextLayoutBlock==((TrackSegment*)ls->getConnectC())->getLayoutBlock() &&
      tType == LayoutSlip::DOUBLE_SLIP)
      {
       // exiting block at C
       prevConnectType= LayoutEditor::SLIP_C;
       setting = LayoutSlip::STATE_BC;
       ts = (TrackSegment*)ls->getConnectC();
      }
      else
      {
      if(tType == LayoutSlip::DOUBLE_SLIP)
      {
          if(currLayoutBlock==((TrackSegment*)ls->getConnectD())->getLayoutBlock() &&
              currLayoutBlock!=((TrackSegment*)ls->getConnectC())->getLayoutBlock()){
              //Found continuing at D only
              ts = (TrackSegment*)lt->getConnectD();
              setting = LayoutSlip::STATE_BD;
              prevConnectType = LayoutEditor::SLIP_D;


          } else if(currLayoutBlock==((TrackSegment*)ls->getConnectC())->getLayoutBlock() &&
              currLayoutBlock!=((TrackSegment*)ls->getConnectD())->getLayoutBlock()){
              //Found continuing at C only
              ts = (TrackSegment*)lt->getConnectC();
              setting = LayoutSlip::STATE_BC;
              prevConnectType = LayoutEditor::SLIP_B;
          } else {
              if((ls->getConnectD()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectD(), (QObject*)ls)){
                  prevConnectType = LayoutEditor::SLIP_D;
                  setting = LayoutSlip::STATE_BD;
                  ts = (TrackSegment*)lt->getConnectD();
              } else if((ls->getConnectC()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectC(), (QObject*)ls)){
                  prevConnectType = LayoutEditor::SLIP_C;
                  setting = LayoutSlip::STATE_BC;
                  ts = (TrackSegment*)lt->getConnectC();
              }
              else {
                  log.error("Error - Neither branch at track node leads to requested Block.(LS2)");
                  _tr=nullptr;
              }


          }
      } else {
          if(currLayoutBlock==((TrackSegment*)ls->getConnectD())->getLayoutBlock()){
              //Found continuing at D only
              ts = (TrackSegment*)lt->getConnectD();
              setting = LayoutSlip::STATE_BD;
              prevConnectType = LayoutEditor::SLIP_D;
          } else {
              _tr=nullptr;
          }
      }
  }
  break;
            case LayoutEditor::SLIP_C :  if(nextLayoutBlock==((TrackSegment*)ls->getConnectA())->getLayoutBlock()){
                 // exiting block at A
                 prevConnectType= LayoutEditor::SLIP_A;
                 setting = LayoutSlip::STATE_AC;
                 ts = (TrackSegment*)ls->getConnectA();
             } else if (nextLayoutBlock==((TrackSegment*)ls->getConnectB())->getLayoutBlock() &&
                 tType == LayoutSlip::DOUBLE_SLIP){
                 // exiting block at B
                 prevConnectType= LayoutEditor::SLIP_B;
                 setting = LayoutSlip::STATE_BC;
                 ts = (TrackSegment*)ls->getConnectB();
             } else {
                 if(tType == LayoutSlip::DOUBLE_SLIP){
                     if(currLayoutBlock==((TrackSegment*)ls->getConnectA())->getLayoutBlock() &&
                         currLayoutBlock!=((TrackSegment*)ls->getConnectB())->getLayoutBlock()){
                         //Found continuing at A only
                         ts = (TrackSegment*)lt->getConnectA();
                         setting = LayoutSlip::STATE_AC;
                         prevConnectType = LayoutEditor::SLIP_A;


                     } else if(currLayoutBlock==((TrackSegment*)ls->getConnectB())->getLayoutBlock() &&
                         currLayoutBlock!=((TrackSegment*)ls->getConnectA())->getLayoutBlock()){
                         //Found continuing at B only
                         ts = (TrackSegment*)lt->getConnectB();
                         setting = LayoutSlip::STATE_BC;
                         prevConnectType = LayoutEditor::SLIP_B;


                     } else {
                         if((ls->getConnectA()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectA(), (QObject*)ls)){
                             prevConnectType = LayoutEditor::SLIP_A;
                             setting = LayoutSlip::STATE_AC;
                             ts = (TrackSegment*)lt->getConnectA();
                         } else if((ls->getConnectB()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectB(), (QObject*)ls)){
                             prevConnectType = LayoutEditor::SLIP_B;
                             setting = LayoutSlip::STATE_BC;
                             ts = (TrackSegment*)lt->getConnectB();
                         }
                         else {
                             log.error("Error - Neither branch at track node leads to requested Block.(LS3)");
                             _tr=nullptr;
                         }
                     }
                 } else {
                     if(currLayoutBlock==((TrackSegment*)ls->getConnectA())->getLayoutBlock()){
                         //Found continuing at A only
                         ts = (TrackSegment*)lt->getConnectA();
                         setting = LayoutSlip::STATE_AC;
                         prevConnectType = LayoutEditor::SLIP_A;
                     } else {
                         _tr=nullptr;
                     }
                 }
             }
             break;
            case LayoutEditor::SLIP_D : if(nextLayoutBlock==((TrackSegment*)ls->getConnectB())->getLayoutBlock()){
                 // exiting block at B
                 prevConnectType= LayoutEditor::SLIP_B;
                 setting = LayoutSlip::STATE_BD;
                 ts = (TrackSegment*)ls->getConnectB();
             } else if (nextLayoutBlock==((TrackSegment*)ls->getConnectA())->getLayoutBlock()){
                 // exiting block at B
                 prevConnectType= LayoutEditor::SLIP_A;
                 setting = LayoutSlip::STATE_AD;
                 ts = (TrackSegment*)ls->getConnectA();
             } else if (currLayoutBlock==((TrackSegment*)ls->getConnectB())->getLayoutBlock() &&
                 currLayoutBlock!=((TrackSegment*)ls->getConnectA())->getLayoutBlock()){
                 //Found continuing at B only
                 ts = (TrackSegment*)lt->getConnectB();
                 setting = LayoutSlip::STATE_BD;
                 prevConnectType = LayoutEditor::SLIP_B;

             } else if (currLayoutBlock==((TrackSegment*)ls->getConnectA())->getLayoutBlock() &&
                 currLayoutBlock!=((TrackSegment*)ls->getConnectB())->getLayoutBlock()) {
                 //Found continuing at A only
                 setting = LayoutSlip::STATE_AD;
                 ts = (TrackSegment*)lt->getConnectA();
                 prevConnectType = LayoutEditor::SLIP_A;
             } else {
                 if((ls->getConnectA()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectA(), (QObject*)ls)){
                     prevConnectType = LayoutEditor::SLIP_A;
                     setting = LayoutSlip::STATE_AD;
                     ts = (TrackSegment*)lt->getConnectA();
                 } else if((ls->getConnectB()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)ls->getConnectB(), (QObject*)ls)){
                     prevConnectType = LayoutEditor::SLIP_B;
                     setting = LayoutSlip::STATE_BD;
                     ts = (TrackSegment*)lt->getConnectB();
                 }
                 else {
                     log.error("Error - Neither branch at track node leads to requested Block.(LS4)");
                     _tr=nullptr;
                 }
             }
             break;
            default : break;
        }
        if ( (_tr!=nullptr) && (ts->getLayoutBlock() != currLayoutBlock) ) {
            // continuing track segment is not in this block
            ts = nullptr;
        }
        else if (tr==nullptr) {
            log.error("Connectivity not complete at Slip "+ls->getDisplayName());
                        turnoutConnectivity = false;
        }
    }
    else
#endif

    {
        switch (cType) {
            case LayoutEditor::TURNOUT_A:
                // check for left-handed crossover
                if (tType == LayoutTurnout::LH_XOVER) {
                    // entering at a continuing track of a left-handed crossover
                    prevConnectType = LayoutEditor::TURNOUT_B;
                    setting = Turnout::CLOSED;
                    ts = (TrackSegment*)lt->getConnectB();
                }
                // entering at a throat, determine exit by checking block of connected track segment
                else if ( (nextLayoutBlock==lt->getLayoutBlockB()) || ((lt->getConnectB()!=nullptr) &&
                            (nextLayoutBlock==((TrackSegment*)lt->getConnectB())->getLayoutBlock())) ) {
                    // exiting block at continuing track
                    prevConnectType = LayoutEditor::TURNOUT_B;
                    setting = Turnout::CLOSED;
                    ts = (TrackSegment*)lt->getConnectB();
                }
                else if ( (nextLayoutBlock==lt->getLayoutBlockC()) || ((lt->getConnectC()!=nullptr) &&
                            (nextLayoutBlock==((TrackSegment*)lt->getConnectC())->getLayoutBlock())) ) {
                    // exiting block at diverging track
                    prevConnectType = LayoutEditor::TURNOUT_C;
                    ts = (TrackSegment*)lt->getConnectC();
                }
                // must stay in block after turnout - check if only one track continues in block
                else if ((lt->getConnectB()!=nullptr) &&  (currLayoutBlock==((TrackSegment*)lt->getConnectB())->getLayoutBlock()) &&
                        (lt->getConnectC()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectC())->getLayoutBlock())) {
                    // continuing in block on continuing track only
                    prevConnectType = LayoutEditor::TURNOUT_B;
                    setting = Turnout::CLOSED;
                    ts = (TrackSegment*)lt->getConnectB();
                }
                else if ((lt->getConnectC()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectC())->getLayoutBlock()) &&
                        (lt->getConnectB()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectB())->getLayoutBlock())) {
                    // continuing in block on diverging track only
                    prevConnectType = LayoutEditor::TURNOUT_C;
                    ts = (TrackSegment*)lt->getConnectC();
                }
                // both connecting track segments continue in current block, must search further
                else {
                    // check if continuing track leads to the next block
                    if ((lt->getConnectB()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectB(),(QObject*)lt)) {
                        prevConnectType = LayoutEditor::TURNOUT_B;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectB();
                    }
                    // check if diverging track leads to the next block
                    else if ((lt->getConnectC()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectC(),(QObject*)lt)) {
                        prevConnectType = LayoutEditor::TURNOUT_C;
                        ts = (TrackSegment*)lt->getConnectC();
                    }
                    else {
                        log.error("Error - Neither branch at track node leads to requested Block.(1)");
                        ts = nullptr;
                    }
                }
                break;
            case LayoutEditor::TURNOUT_B:
                if ( (tType==LayoutTurnout::LH_XOVER) || (tType==LayoutTurnout::DOUBLE_XOVER) ) {
                    // entering at a throat of a double crossover or a left-handed crossover
                    if ( (nextLayoutBlock==lt->getLayoutBlock()) || ((lt->getConnectA()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectA())->getLayoutBlock())) ) {
                        // exiting block at continuing track
                        prevConnectType = LayoutEditor::TURNOUT_A;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectB();
                    }
                    else if ( (nextLayoutBlock==lt->getLayoutBlockD()) || ((lt->getConnectD()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectD())->getLayoutBlock())) ) {
                        // exiting block at diverging track
                        prevConnectType = LayoutEditor::TURNOUT_D;
                        ts = (TrackSegment*)lt->getConnectD();
                    }
                    // must stay in block after turnout
                    else if ( ((lt->getConnectA()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectA())->getLayoutBlock())) &&
                                ((lt->getConnectD()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectD())->getLayoutBlock())) ) {
                        // continuing in block on continuing track only
                        prevConnectType = LayoutEditor::TURNOUT_A;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectA();
                    }
                    else if ( ((lt->getConnectD()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectD())->getLayoutBlock())) &&
                                ((lt->getConnectA()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectA())->getLayoutBlock())) ) {
                        // continuing in block on diverging track only
                        prevConnectType = LayoutEditor::TURNOUT_D;
                        ts = (TrackSegment*)lt->getConnectD();
                    }
                    // both connecting track segments continue in current block, must search further
                    else {
                        // check if continuing track leads to the next block
                        if ((lt->getConnectA()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectA(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_A;
                            setting = Turnout::CLOSED;
                            ts = (TrackSegment*)lt->getConnectA();
                        }
                        // check if diverging track leads to the next block
                        else if ((lt->getConnectD()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectD(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_D;
                            ts = (TrackSegment*)lt->getConnectD();
                        }
                        else {
                            log.error("Error - Neither branch at track node leads to requested Block.(2)");
                            ts = nullptr;
                        }
                    }
                }
                else {
                    // entering at continuing track, must exit at throat
                    prevConnectType = LayoutEditor::TURNOUT_A;
                    setting = Turnout::CLOSED;
                    ts = (TrackSegment*)lt->getConnectA();
                }
                break;
            case LayoutEditor::TURNOUT_C:
                if ( (tType==LayoutTurnout::RH_XOVER) || (tType==LayoutTurnout::DOUBLE_XOVER) ) {
                    // entering at a throat of a double crossover or a right-handed crossover
                    if ( (nextLayoutBlock==lt->getLayoutBlockD()) || ((lt->getConnectD()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectD())->getLayoutBlock())) ) {
                        // exiting block at continuing track
                        prevConnectType = LayoutEditor::TURNOUT_D;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectD();
                    }
                    else if ( (nextLayoutBlock==lt->getLayoutBlock()) || ((lt->getConnectA()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectA())->getLayoutBlock())) ) {
                        // exiting block at diverging track
                        prevConnectType = LayoutEditor::TURNOUT_A;
                        ts = (TrackSegment*)lt->getConnectA();
                    }
                    // must stay in block after turnout
                    else if ( ((lt->getConnectD()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectD())->getLayoutBlock())) &&
                                ((lt->getConnectA()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectA())->getLayoutBlock())) ) {
                        // continuing in block on continuing track
                        prevConnectType = LayoutEditor::TURNOUT_D;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectD();
                    }
                    else if ( ((lt->getConnectA()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectA())->getLayoutBlock())) &&
                                ((lt->getConnectD()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectD())->getLayoutBlock())) ) {
                        // continuing in block on diverging track
                        prevConnectType = LayoutEditor::TURNOUT_A;
                        ts = (TrackSegment*)lt->getConnectA();
                    }
                    // both connecting track segments continue in current block, must search further
                    else {
                        // check if continuing track leads to the next block
                        if ((lt->getConnectD()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectD(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_D;
                            setting = Turnout::CLOSED;
                            ts = (TrackSegment*)lt->getConnectD();
                        }
                        // check if diverging track leads to the next block
                        else if ((lt->getConnectA()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectA(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_A;
                            ts = (TrackSegment*)lt->getConnectA();
                        }
                        else {
                            log.error("Error - Neither branch at track node leads to requested Block.(3)");
                            ts = nullptr;
                        }
                    }
                }
                else {
                    // entering at diverging track, must exit at throat
                    prevConnectType = LayoutEditor::TURNOUT_A;
                    ts = (TrackSegment*)lt->getConnectA();
                }
                break;
            case LayoutEditor::TURNOUT_D:
                if ( (tType==LayoutTurnout::LH_XOVER) || (tType==LayoutTurnout::DOUBLE_XOVER) ) {
                    // entering at a throat of a double crossover or a left-handed crossover
                    if ( (nextLayoutBlock==lt->getLayoutBlockC()) || ((lt->getConnectC()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectC())->getLayoutBlock())) ) {
                        // exiting block at continuing track
                        prevConnectType = LayoutEditor::TURNOUT_C;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectC();
                    }
                    else if ( (nextLayoutBlock==lt->getLayoutBlockB()) || ((lt->getConnectB()!=nullptr) &&
                                (nextLayoutBlock==((TrackSegment*)lt->getConnectB())->getLayoutBlock())) ) {
                        // exiting block at diverging track
                        prevConnectType = LayoutEditor::TURNOUT_B;
                        ts = (TrackSegment*)lt->getConnectB();
                    }
                    // must stay in block after turnout
                    else if ( ((lt->getConnectC()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectC())->getLayoutBlock())) &&
                                ((lt->getConnectB()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectB())->getLayoutBlock())) ) {
                        // continuing in block on continuing track
                        prevConnectType = LayoutEditor::TURNOUT_C;
                        setting = Turnout::CLOSED;
                        ts = (TrackSegment*)lt->getConnectC();
                    }
                    else if ( ((lt->getConnectB()!=nullptr) && (currLayoutBlock==((TrackSegment*)lt->getConnectB())->getLayoutBlock())) &&
                                ((lt->getConnectC()!=nullptr) && (currLayoutBlock!=((TrackSegment*)lt->getConnectC())->getLayoutBlock())) ) {
                        // continuing in block on diverging track
                        prevConnectType = LayoutEditor::TURNOUT_B;
                        ts = (TrackSegment*)lt->getConnectB();
                    }
                    // both connecting track segments continue in current block, must search further
                    else {
                        // check if continuing track leads to the next block
                        if ((lt->getConnectC()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectC(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_C;
                            setting = Turnout::CLOSED;
                            ts = (TrackSegment*)lt->getConnectC();
                        }
                        // check if diverging track leads to the next block
                        else if ((lt->getConnectB()!=nullptr) && trackSegmentLeadsTo((TrackSegment*)lt->getConnectB(),(QObject*)lt)) {
                            prevConnectType = LayoutEditor::TURNOUT_B;
                            ts = (TrackSegment*)lt->getConnectB();
                        }
                        else {
                            log.error("Error - Neither branch at track node leads to requested Block.(2)");
                            ts = nullptr;
                        }
                    }
                }
                else {
                // entering at diverging track of a right-handed crossover, must exit at throat
                    prevConnectType = LayoutEditor::TURNOUT_A;
                    ts = (TrackSegment*)lt->getConnectA();
                }
                break;
        }
        if ( (ts!=nullptr) && (ts->getLayoutBlock() != currLayoutBlock) ) {
            // continuing track segment is not in this block
            ts = nullptr;
        }
        else if (ts==nullptr) {
            log.error("Connectivity not complete at turnout "+lt->getTurnoutName());
                        turnoutConnectivity = false;
        }
        if (lt->getContinuingSense() != Turnout::CLOSED) {
            if (setting == Turnout::THROWN) setting = Turnout::CLOSED;
            else if (setting == Turnout::CLOSED) setting = Turnout::THROWN;
        }
    }
    return ((setting));
}

/**
 * This method follows the track from a beginning track segment to its exits
 *	from the current LayoutBlock 'lb' until the track connects to the designated
 *  Block 'nextLayoutBlock' or all exit points have been tested.
 * Returns 'true' if designated Block is connected; returns 'false' if not->
 */
/*private*/ bool ConnectivityUtil::trackSegmentLeadsTo(TrackSegment* tsg, QObject* ob) {
    if ( (tsg==nullptr) || (ob==nullptr) ) {
        log.error("Null argument on entry to trackSegmentLeadsTo");
        return false;
    }
    TrackSegment* curTS = tsg;
    QObject* curObj = ob;
    QVector<TrackSegment*>* posTS = new QVector<TrackSegment*>();
    QVector<QObject*>* posOB = new QVector<QObject*>();
    int conType = 0;
    QObject* conObj = nullptr;
    // follow track to all exit points outside this block
    while (curTS!=nullptr) {
        if (curTS->getLayoutBlock()==nextLayoutBlock) return true;
        if (curTS->getLayoutBlock()==currLayoutBlock) {
            // identify next destination along track
            if (curTS->getConnect1() == curObj) {
                // entered through 1, leaving through 2
                conType = curTS->getType2();
                conObj = curTS->getConnect2();
            }
            else if (curTS->getConnect2() == curObj) {
                // entered through 2, leaving through 1
                conType = curTS->getType1();
                conObj = curTS->getConnect1();
            }
            else {
                log.error("Connectivity error when following track in Block "+currLayoutBlock->getUserName());
                return false;
            }
            // follow track according to next destination type
            if (conType==LayoutEditor::POS_POINT) {
                // reached anchor point or end bumper
                if (((PositionablePoint*)conObj)->getType() == PositionablePoint::END_BUMPER) {
                    // end of line without reaching 'nextLayoutBlock'
                    curTS = nullptr;
                }
                else if (((PositionablePoint*)conObj)->getType() == PositionablePoint::ANCHOR) {
                    // proceed to next track segment if within the same Block
                    if (((PositionablePoint*)conObj)->getConnect1() == curTS) {
                        curTS = (((PositionablePoint*)conObj)->getConnect2());
                    }
                    else {
                        curTS = (((PositionablePoint*)conObj)->getConnect1());
                    }
                    curObj = conObj;
                }
            }
            else if ( (conType>=LayoutEditor::LEVEL_XING_A) && (conType<=LayoutEditor::LEVEL_XING_D) ) {
                // reached a level crossing
                if ( (conType==LayoutEditor::LEVEL_XING_A) || (conType==LayoutEditor::LEVEL_XING_C) ) {
                    if (((LevelXing*)conObj)->getLayoutBlockAC()!=currLayoutBlock) {
                        if (((LevelXing*)conObj)->getLayoutBlockAC()==nextLayoutBlock) return true;
                        else curTS = nullptr;
                    }
                    else if (conType==LayoutEditor::LEVEL_XING_A) {
                        curTS = (TrackSegment*)((LevelXing*)conObj)->getConnectC();
                    }
                    else {
                        curTS = (TrackSegment*)((LevelXing*)conObj)->getConnectA();
                    }
                }
                else {
                    if (((LevelXing*)conObj)->getLayoutBlockBD()!=currLayoutBlock) {
                        if (((LevelXing*)conObj)->getLayoutBlockBD()==nextLayoutBlock) return true;
                        else curTS = nullptr;
                    }
                    else if (conType==LayoutEditor::LEVEL_XING_B) {
                        curTS = (TrackSegment*)((LevelXing*)conObj)->getConnectD();
                    }
                    else {
                        curTS = (TrackSegment*)((LevelXing*)conObj)->getConnectB();
                    }
                }
                curObj = conObj;
            }
            else if ( (conType>=LayoutEditor::TURNOUT_A) && (conType<=LayoutEditor::TURNOUT_D) ) {
                // reached a turnout
                LayoutTurnout* lt = (LayoutTurnout*)conObj;
                int tType = lt->getTurnoutType();
                if ( (tType==LayoutTurnout::DOUBLE_XOVER) || (tType==LayoutTurnout::RH_XOVER) ||
                        (tType==LayoutTurnout::LH_XOVER) ) {
                    // reached a crossover turnout
                    switch (conType) {
                        case LayoutEditor::TURNOUT_A:
                            if ((lt->getLayoutBlock())!=currLayoutBlock) {
                                if (lt->getLayoutBlock()==nextLayoutBlock) return true;
                                else curTS = nullptr;
                            }
                            else if ( (lt->getLayoutBlockB()==nextLayoutBlock) || ( (tType!=LayoutTurnout::LH_XOVER) &&
                                                        (lt->getLayoutBlockC()==nextLayoutBlock) ) )return true;
                            else if (lt->getLayoutBlockB()==currLayoutBlock) {
                                curTS = (TrackSegment*)lt->getConnectB();
                                if ( (tType!=LayoutTurnout::LH_XOVER) && (lt->getLayoutBlockC()==currLayoutBlock) ) {
                                    //if (posTS != nullptr) {
                                        posTS->append((TrackSegment*)lt->getConnectC());
                                    //}
                                    posOB->append(conObj);
                                }
                            }
                            else if ( (tType!=LayoutTurnout::LH_XOVER) && (lt->getLayoutBlockC()==currLayoutBlock) ) {
                                curTS = (TrackSegment*)lt->getConnectC();
                            }
                            else curTS = nullptr;
                            curObj = conObj;
                            break;
                        case LayoutEditor::TURNOUT_B:
                            if ((lt->getLayoutBlockB())!=currLayoutBlock) {
                                if (lt->getLayoutBlockB()==nextLayoutBlock) return true;
                                else curTS = nullptr;
                            }
                            else if ( (lt->getLayoutBlock()==nextLayoutBlock) || ( (tType!=LayoutTurnout::RH_XOVER) &&
                                                                      (lt->getLayoutBlockD()==nextLayoutBlock) ) ) return true;
                            else if (lt->getLayoutBlock()==currLayoutBlock) {
                                curTS = (TrackSegment*)lt->getConnectA();
                                if ( (tType!=LayoutTurnout::RH_XOVER) && (lt->getLayoutBlockD()==currLayoutBlock) ) {
                                    //if (posTS != nullptr) {
                                        posTS->append((TrackSegment*)lt->getConnectD());
                                    //}
                                    posOB->append(conObj);
                                }
                            }
                            else if ( (tType!=LayoutTurnout::RH_XOVER) && (lt->getLayoutBlockD()==currLayoutBlock) ) {
                                curTS = (TrackSegment*)lt->getConnectD();
                            }
                            else curTS = nullptr;
                            curObj = conObj;
                            break;
                        case LayoutEditor::TURNOUT_C:
                            if ((lt->getLayoutBlockC())!=currLayoutBlock) {
                                if (lt->getLayoutBlockC()==nextLayoutBlock) return true;
                                else curTS = nullptr;
                            }
                            else if ( (lt->getLayoutBlockD()==nextLayoutBlock) || ( (tType!=LayoutTurnout::LH_XOVER) &&
                                                                      (lt->getLayoutBlock()==nextLayoutBlock) ) )return true;
                            else if (lt->getLayoutBlockD()==currLayoutBlock) {
                                curTS = (TrackSegment*)lt->getConnectD();
                                if ( (tType!=LayoutTurnout::LH_XOVER) && (lt->getLayoutBlock()==currLayoutBlock) ) {
                                    //if (posTS != nullptr) {
                                        posTS->append((TrackSegment*)lt->getConnectA());
                                    //}
                                    posOB->append(conObj);
                                }
                            }
                            else if ( (tType!=LayoutTurnout::LH_XOVER) && (lt->getLayoutBlock()==currLayoutBlock) ) {
                                curTS = (TrackSegment*)lt->getConnectA();
                            }
                            else curTS = nullptr;
                            curObj = conObj;
                            break;
                        case LayoutEditor::TURNOUT_D:
                            if ((lt->getLayoutBlockD())!=currLayoutBlock) {
                                if (lt->getLayoutBlockD()==nextLayoutBlock) return true;
                                else curTS = nullptr;
                            }
                            else if ( (lt->getLayoutBlockC()==nextLayoutBlock) || ( (tType!=LayoutTurnout::RH_XOVER) &&
                                                                      (lt->getLayoutBlockB()==nextLayoutBlock) ) )return true;
                            else if (lt->getLayoutBlockC()==currLayoutBlock) {
                                curTS = (TrackSegment*)lt->getConnectC();
                                if ( (tType!=LayoutTurnout::RH_XOVER) && (lt->getLayoutBlockB()==currLayoutBlock) ) {
                                    //if (posTS != nullptr) {
                                        posTS->append((TrackSegment*)lt->getConnectB());
                                    //}
                                    posOB->append(conObj);
                                }
                            }
                            else if ( (tType!=LayoutTurnout::RH_XOVER) && (lt->getLayoutBlockB()==currLayoutBlock) ) {
                                curTS = (TrackSegment*)lt->getConnectB();
                            }
                            else curTS = nullptr;
                            curObj = conObj;
                            break;
                        default : break;
                    }
                }
                else if ( (tType==LayoutTurnout::RH_TURNOUT) || (tType==LayoutTurnout::LH_TURNOUT) ||
                         (tType==LayoutTurnout::WYE_TURNOUT) ) {
                    // reached RH. LH, or WYE turnout
                    if (lt->getLayoutBlock()!=currLayoutBlock) {
                        if (lt->getLayoutBlock()==nextLayoutBlock) return true;
                        else curTS = nullptr;
                    }
                    else {
                        if (conType==LayoutEditor::TURNOUT_A) {
                            if ( (((TrackSegment*)lt->getConnectB())->getLayoutBlock()==nextLayoutBlock) ||
                                (((TrackSegment*)lt->getConnectC())->getLayoutBlock()==nextLayoutBlock) ) return true;
                            else if (((TrackSegment*)lt->getConnectB())->getLayoutBlock()==currLayoutBlock) {
                                curTS = (TrackSegment*)lt->getConnectB();
                                if (((TrackSegment*)lt->getConnectC())->getLayoutBlock()==currLayoutBlock) {
                                    //if (posTS != nullptr) {
                                        posTS->append((TrackSegment*)lt->getConnectC());
                                    //}
                                    posOB->append(conObj);
                                }
                            }
                            else curTS = (TrackSegment*)lt->getConnectC();
                        }
                        else curTS = (TrackSegment*)lt->getConnectA();
                        curObj = conObj;
                    }
                }
            }
#if 1 // TODO:
            else if(conType>=LayoutEditor::SLIP_A && conType<=LayoutEditor::SLIP_D){
                LayoutSlip* ls = (LayoutSlip*)conObj;
                int tType = ls->getTurnoutType();
                if (ls->getLayoutBlock()!=currLayoutBlock){
                    if(ls->getLayoutBlock()==nextLayoutBlock) return true;
                    else curTS = nullptr;
                } else {
                    switch (conType){
                            case LayoutEditor::SLIP_A:
                                                 if(((TrackSegment*)ls->getConnectC())->getLayoutBlock()==nextLayoutBlock) {
                                                    //Leg A-D has next lb
                                                    return true;
                                                 }
                                                 if(((TrackSegment*)ls->getConnectD())->getLayoutBlock()==nextLayoutBlock){
                                                    //Leg A-C has next lb
                                                    return true;
                                                 }
                                                 if (((TrackSegment*)ls->getConnectC())->getLayoutBlock()==currLayoutBlock){
                                                    curTS = (TrackSegment*)ls->getConnectC();
                                                    if (((TrackSegment*)ls->getConnectD())->getLayoutBlock()==currLayoutBlock) {
                                                        //if (posTS != nullptr) {
                                                            posTS->append((TrackSegment*)ls->getConnectD());
                                                        //}
                                                        posOB->append(conObj);
                                                    }
                                                 } else {
                                                    curTS = (TrackSegment*)ls->getConnectD();
                                                 }
                                                 break;
                            case LayoutEditor::SLIP_B:
                                                    if(tType==LayoutSlip::SINGLE_SLIP){
                                                        curTS = (TrackSegment*)ls->getConnectD();
                                                        break;
                                                    }
                                                    if(((TrackSegment*)ls->getConnectC())->getLayoutBlock()==nextLayoutBlock) {
                                                        //Leg B-C has next lb
                                                        return true;
                                                    }
                                                    if(((TrackSegment*)ls->getConnectB())->getLayoutBlock()==nextLayoutBlock){
                                                        //Leg D-B has next lb
                                                        return true;
                                                    }
                                                    if (((TrackSegment*)ls->getConnectC())->getLayoutBlock()==currLayoutBlock){
                                                        curTS = (TrackSegment*)ls->getConnectC();
                                                        if (((TrackSegment*)ls->getConnectD())->getLayoutBlock()==currLayoutBlock) {
                                                            //if (posTS != nullptr) {
                                                                posTS->append((TrackSegment*)ls->getConnectD());
                                                            //}
                                                            posOB->append(conObj);
                                                        }
                                                    } else {
                                                        curTS = (TrackSegment*)ls->getConnectD();
                                                    }
                                                    break;
                            case LayoutEditor::SLIP_C:
                                                    if(tType==LayoutSlip::SINGLE_SLIP){
                                                        curTS = (TrackSegment*)ls->getConnectA();
                                                        break;
                                                    }
                                                    if(((TrackSegment*)ls->getConnectA())->getLayoutBlock()==nextLayoutBlock) {
                                                        //Leg A-C has next lb
                                                        return true;
                                                    }
                                                    if(((TrackSegment*)ls->getConnectB())->getLayoutBlock()==nextLayoutBlock){
                                                        //Leg B-C has next lb
                                                        return true;
                                                    }
                                                    if (((TrackSegment*)ls->getConnectB())->getLayoutBlock()==currLayoutBlock){
                                                        curTS = (TrackSegment*)ls->getConnectB();
                                                        if (((TrackSegment*)ls->getConnectA())->getLayoutBlock()==currLayoutBlock) {
                                                            //if (posTS != nullptr) {
                                                                posTS->append((TrackSegment*)ls->getConnectA());
                                                            //}
                                                            posOB->append(conObj);
                                                        }
                                                    } else {
                                                        curTS = (TrackSegment*)ls->getConnectA();
                                                    }
                                                    break;
                            case LayoutEditor::SLIP_D:
                                                    if(((TrackSegment*)ls->getConnectA())->getLayoutBlock()==nextLayoutBlock) {
                                                        //Leg D-A has next currLayoutBlock
                                                        return true;
                                                    }
                                                    if(((TrackSegment*)ls->getConnectB())->getLayoutBlock()==nextLayoutBlock){
                                                        //Leg D-B has next currLayoutBlock
                                                        return true;
                                                    }
                                                    if (((TrackSegment*)ls->getConnectB())->getLayoutBlock()==currLayoutBlock){
                                                        curTS = (TrackSegment*)ls->getConnectB();
                                                        if (((TrackSegment*)ls->getConnectA())->getLayoutBlock()==currLayoutBlock) {
                                                            //if (posTS != nullptr) {
                                                                posTS->append((TrackSegment*)ls->getConnectA());
                                                            //}
                                                            posOB->append(conObj);
                                                        }
                                                    } else {
                                                        curTS = (TrackSegment*)ls->getConnectA();
                                                    }
                                                    break;
                    }
                }
            }
#endif

        }
        else curTS = nullptr;

        if (curTS==nullptr) {
            // reached an end point outside this block that was not 'nextLayoutBlock' - any other paths to follow?
            //if ( (posTS!=nullptr) && (posTS.size()>0) ) {
            if (posTS->size()>0) {
                // paths remain, initialize the next one
                curTS = posTS->at(0);
                curObj = posOB->at(0);
                // remove it from the list of unexplored paths
                posTS->remove(0);
                posOB->remove(0);
            }
        }
    }
    // searched all possible paths in this block, 'currLayoutBlock', without finding the desired exit block, 'nextLayoutBlock'
    return false;
}

/**
 * This flag can be checked after performing a getTurnoutList() to check
 *	if the connectivity of the turnouts has been completed in the block
 *	when the getTurnoutList() was called.
 *  Returns 'false' if a turnout conectivity is not complete.
 *  Returns 'true' if the turnout conectivity is complete.
 */
///*public*/ bool isTurnoutConnectivityComplete() { return turnoutConnectivity; }

/*private*/ void ConnectivityUtil::setupOpposingTrackSegment(LevelXing* x, int cType) {
    switch (cType) {
        case LayoutEditor::LEVEL_XING_A:
            ts = (TrackSegment*)x->getConnectC();
            prevConnectType = LayoutEditor::LEVEL_XING_C;
            break;
        case LayoutEditor::LEVEL_XING_B:
            ts = (TrackSegment*)x->getConnectD();
            prevConnectType = LayoutEditor::LEVEL_XING_D;
            break;
        case LayoutEditor::LEVEL_XING_C:
            ts = (TrackSegment*)x->getConnectA();
            prevConnectType = LayoutEditor::LEVEL_XING_A;
            break;
        case LayoutEditor::LEVEL_XING_D:
            ts = (TrackSegment*)x->getConnectB();
            prevConnectType = LayoutEditor::LEVEL_XING_B;
            break;
        default : break;
    }
    if (ts->getLayoutBlock() != currLayoutBlock) {
        // track segment is not in this block
        ts = nullptr;
    }
    else {
        // track segment is in this block
        prevConnectObject = x;
    }
}
/*public*/ QVector<LayoutTurnout*>* ConnectivityUtil::getAllTurnoutsThisBlock(LayoutBlock* lb) {
    QVector<LayoutTurnout*>* list = new QVector<LayoutTurnout*>();
    for (int i = 0; i < layoutEditor->getLayoutTracks()->size(); i++)
    {
     if(qobject_cast<LayoutTurnout*>(layoutEditor->getLayoutTracks()->at(i)))
     {
        LayoutTurnout* lt = (LayoutTurnout*)layoutEditor->getLayoutTracks()->at(i);
        if ( (lt->getLayoutBlock()==lb) || (lt->getLayoutBlockB()==lb) ||
                (lt->getLayoutBlockC()==lb) || (lt->getLayoutBlockD()==lb) ) {
            list->append(lt);
        }
     }
    }
    return list;
}


// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ConnectivityUtil.class.getName());
//}
