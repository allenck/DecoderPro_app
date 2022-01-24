#include "layouteditorauxtools.h"
#include <qmath.h>
#include "instancemanager.h"
#include "path.h"
#include "tracksegment.h"
#include "layoutturnout.h"
#include "positionablepoint.h"
#include "positionablepointview.h"
#include "layoutturnoutview.h"
#include "tracksegmentview.h"
#include "layouteditorcomponent.h"

//LayoutEditorAuxTools::LayoutEditorAuxTools(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * LayoutEditorAuxTools provides tools making use of layout connectivity available
 *	in Layout Editor panels->  (More tools are in LayoutEditorTools->java.)
 * <P>
 * This module manages block connectivity for its associated LayoutEditor::
 * <P>
 * The tools in this module are accessed via the Tools menu in Layout Editor, or
 *	directly from LayoutEditor or LayoutEditor specific modules.
 * <P>
 * @author Dave Duchamp Copyright (c) 2008
 * @version $Revision: 20370 $
 */

///*public*/ class LayoutEditorAuxTools
//{

//	// Defined text resource
//	ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor->LayoutEditorBundle");

// constants

// operational instance variables

// constructor method
/*public*/ LayoutEditorAuxTools::LayoutEditorAuxTools(LayoutEditor *theModels) {
 log = new Logger("LayoutEditorAuxTools");
 models  = theModels;
 cList = new QVector<LayoutConnectivity*>(); //LayoutConnectivity list
 blockConnectivityChanged = false;  // true if block connectivity may have changed
 initialized = false;

}

// register a change in block connectivity that may require an update of connectivity list
/*public*/ void LayoutEditorAuxTools::setBlockConnectivityChanged() {blockConnectivityChanged = true;}

/**
 * Get Connectivity involving a specific Layout Block
 * <P>
 * This routine returns an QVector of BlockConnectivity objects involving the specified
 *		LayoutBlock.
 */
/*public*/ QVector<LayoutConnectivity*>* LayoutEditorAuxTools::getConnectivityList(LayoutBlock* blk) {
    if (!initialized) initializeBlockConnectivity();
    if (blockConnectivityChanged) {
        updateBlockConnectivity();
    }
    QVector<LayoutConnectivity*>* retList = new QVector<LayoutConnectivity*>();
    for (int i = 0;i<cList->size();i++) {
        LayoutConnectivity* lc = cList->at(i);
        if ( (lc->getBlock1() == blk) || (lc->getBlock2() == blk) ) {
            retList->append(lc);
        }
    }
    return (retList);
}

/**
 * Initializes the block connectivity (block boundaries) for a Layout Editor panel.
 * <P>
 * This routine sets up the LayoutConnectivity objects needed to show the current
 *		connectivity. It gets its information from arrays contained in LayoutEditor::
 * <P>
 * One LayoutConnectivity object is created for each block boundary -- connection
 *		points where two blocks join. Block boundaries can occur whereever a track segment
 *		in one block joins with:
 *		1) a track segment in another block -OR-
 *		2) a connection point in a layout turnout in another block -OR-
 *      3) a connection point in a level crossing in another block.
 * <P>
 * The first block is always a track segment.  The direction set in the LayoutConnectivity
 *		is the direction of the track segment alone for cases 2) and 3) above.  For case 1),
 *		two track segments, the direction reflects an "average" over the two track segments->
 *		See LayoutConnectivity for the allowed values of direction.
 * <P>
 *
 */
/*public*/ void LayoutEditorAuxTools::initializeBlockConnectivity ()
{
 if (initialized)
 {
        log->error("Call to initialize a connectivity list that has already been initialized");  // NOI18N
        return;
    }
    cList = new QVector<LayoutConnectivity*>();
    QList<LayoutConnectivity*> lcs;

    for (LayoutTrackView* ltv : models->getLayoutTrackViews()) {
        if ((qobject_cast<PositionablePointView*>(ltv))
                || (qobject_cast<TrackSegmentView*>(ltv))
                || (qobject_cast<LayoutTurnoutView*>(ltv)))
        { // <== includes LayoutSlips
            lcs = ltv->getLayoutConnectivity();
            //cList->addAll(lcs); // append to list
            foreach(LayoutConnectivity* lc, lcs)
             cList->append(lc);
        }
    }
    initialized = true;
}   // initializeBlockConnectivity

/**
 * Updates the block connectivity (block boundaries) for a Layout Editor panel after changes may have
 *		been made.
 */
/*private*/ void LayoutEditorAuxTools::updateBlockConnectivity() {
 int sz = cList->size();
 QVector<bool> found = QVector<bool>(sz,false);
 //Arrays.fill(found, false);

 QList<LayoutConnectivity*> lcs;

 // Check for block boundaries at positionable points.
 for (PositionablePoint* p : models->getPositionablePoints()) {
     lcs = p->getLayoutConnectivity();
     for (LayoutConnectivity* lc : lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // Check for block boundaries at layout turnouts and level crossings
 for (TrackSegment* ts : models->getTrackSegments()) {
     lcs = ts->getLayoutConnectivity();
     for (LayoutConnectivity* lc : lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // check for block boundaries internal to crossover turnouts
 for (LayoutTrack* lt : models->getLayoutTurnouts()) {
     lcs = lt->getLayoutConnectivity();
     for (LayoutConnectivity* lc : lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // check for block boundaries internal to slips
 for (LayoutSlip* ls : models->getLayoutSlips()) {
     lcs = ls->getLayoutConnectivity();
     for (LayoutConnectivity* lc : lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // delete any LayoutConnectivity objects no longer needed
 for (int i = sz - 1; i >= 0; i--) {
     if (!found[i]) {
         // djd debugging - message to list connectivity being removed
         //    LayoutConnectivity xx = (LayoutConnectivity)cList.get(i);
         //    log->error("  Deleting Layout Connectivity - " + xx.getBlock1().getId() + ", " + xx.getBlock2().getId());
         // end debugging
         cList->remove(i);
     }
 }
 blockConnectivityChanged = false;
}   // updateBlockConnectivity

//
/*private*/ void LayoutEditorAuxTools::checkConnectivity(LayoutConnectivity* c,QVector<bool> found) {
    // initialize input LayoutConnectivity components
    LayoutBlock* blk1 = c->getBlock1();
    LayoutBlock* blk2 = c->getBlock2();
    int dir = c->getDirection();
    int rDir = c->getReverseDirection();
    TrackSegment* track = c->getTrackSegment();
    QObject* connected = c->getConnectedObject();
    HitPointType::TYPES type = c->getConnectedType();
    LayoutTurnout* xOver = c->getXover();
    int xOverType = c->getXoverBoundaryType();
    // loop over connectivity list, looking for this layout connectivity
    bool looking = true;
    for (int i = 0;(i<cList->size()) && looking;i++) {
        LayoutConnectivity* lc = cList->at(i);
        // compare input LayoutConnectivity with LayoutConnectivity from the list
        if (xOver==nullptr) {
            // not a crossover block boundary
            if ( (blk1==lc->getBlock1()) && (blk2==lc->getBlock2()) && (track==lc->getTrackSegment()) &&
                    (connected==lc->getConnectedObject()) && (type==lc->getConnectedType()) &&
                        (dir==lc->getDirection()) ) {
                looking = false;
                found[i] = true;
            }
        }
        else {
            // boundary is in a crossover turnout
            if ( (xOver==lc->getXover()) && (xOverType==lc->getXoverBoundaryType()) ) {
                if ((blk1==lc->getBlock1()) && (blk2==lc->getBlock2()) && (dir==lc->getDirection()) ) {
                    looking = false;
                    found[i] = true;
                }
                else if ((blk2==lc->getBlock1()) && (blk1==lc->getBlock2()) && (rDir==lc->getDirection()) ) {
                    looking = false;
                    found[i] = true;
                }
            }
        }
    }
    // if not found in list, add it
    if (looking) {
        cList->append(c);
    }
}

// compute direction of vector from p1 to p2
/*private*/ int LayoutEditorAuxTools::computeDirection(QPointF p1, QPointF p2) {
    double dh = p2.x() - p1.x();
    double dv = p2.y() - p1.y();
    int dir = Path::NORTH;
    double tanA;
    if (dv!=0.0) tanA = qAbs(dh)/qAbs(dv);
    else tanA = 10.0;
    if (tanA<0.38268) {
        // track is mostly vertical
        if (dv<0.0) dir = Path::NORTH;
        else dir = Path::SOUTH;
    }
    else if (tanA>2.4142) {
        // track is mostly horizontal
        if (dh>0.0) dir = Path::EAST;
        else dir = Path::WEST;
    }
    else {
        // track is between horizontal and vertical
        if ( (dv>0.0) && (dh>0.0) ) dir = Path::SOUTH + Path::EAST;
        else if ( (dv>0.0) && (dh<0.0) ) dir = Path::SOUTH + Path::WEST;
        else if ( (dv<0.0) && (dh<0.0) ) dir = Path::NORTH + Path::WEST;
        else dir = Path::NORTH + Path::EAST;
    }
    return dir;
}

/**
 * Searches for and adds BeanSetting's to a Path as needed.
 * <P>
 * This method starts at the entry point to the LayoutBlock given in the Path at
 *		the block boundary specified in the LayoutConnectivity:: It follows the track
 *		looking for turnout settings that are required for a train entering on this
 *		block boundary point to exit the block. If a required turnout setting is found,
 *		the turnout and its required state are used to create a BeanSetting, which is
 *		added to the Path:: Such a setting can occur, for example, if a track enters
 *		a right-handed turnout from either the diverging track or the continuing track.
 * <P>
 * If the track branches into two tracks (for example, by entering a right-handed turnout
 *		via the throat track), the search is stopped. The search is also stopped when
 *		the track reaches a different block (or an undefined block), or reaches an end
 *		bumper.
 */
/*public*/ void LayoutEditorAuxTools::addBeanSettings(Path* p, LayoutConnectivity* lc, LayoutBlock* layoutBlock)
{
 p->clearSettings();
 LayoutTrack* curConnection = nullptr;
 LayoutTrack* prevConnection = nullptr;
 HitPointType::TYPES typeCurConnection = HitPointType::NONE;
 BeanSetting* bs = nullptr;
 LayoutTurnout* lt = nullptr;
 QMetaEnum mehp = QMetaEnum::fromType<HitPointType::TYPES>();
 QMetaEnum mett = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
 // process track at block boundary
 if (lc->getBlock1() == layoutBlock) {    // block1 is this LayoutBlock
     curConnection = lc->getTrackSegment();
     if (curConnection != nullptr) {        // connected track in this block is a track segment
         prevConnection = lc->getConnectedObject();
         typeCurConnection = HitPointType::TRACK;
         // is this Track Segment connected to a RH, LH, or WYE turnout at the continuing or diverging track?
         if ((lc->getConnectedType() == HitPointType::TURNOUT_B
                 || lc->getConnectedType() == HitPointType::TURNOUT_C)
                 && ((LayoutTurnout*) prevConnection)->getTurnoutType() != LayoutTurnout::TurnoutType::NONE
                 && LayoutTurnout::hasEnteringSingleTrack(((LayoutTurnout*) prevConnection)->getTurnoutType())) {
             LayoutTurnout* ltx = (LayoutTurnout*) prevConnection;
             // Track Segment connected to continuing track of turnout?
             if (lc->getConnectedType() == HitPointType::TURNOUT_B) {
                 Turnout* ltxto = ltx->getTurnout();
                 if ( ltxto != nullptr) {
                     bs = new BeanSetting(ltxto, ltx->getTurnoutName(), ltx->getContinuingSense());
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (A): LTO = %1, blk = %2").arg(ltx->getName(), ltx->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
             } else if (lc->getConnectedType() == HitPointType::TURNOUT_C) {
                 // is Track Segment connected to diverging track of turnout?
                 Turnout* ltxto = ltx->getTurnout();
                 if (ltxto != nullptr) {
                     if (ltx->getContinuingSense() == Turnout::CLOSED) {
                         bs = new BeanSetting(ltxto, ltx->getTurnoutName(), Turnout::THROWN);
                     } else {
                         bs = new BeanSetting(ltxto, ltx->getTurnoutName(), Turnout::CLOSED);
                     }
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (B): LTO = %1, blk = %2").arg(ltx->getName(), ltx->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
             } else {
                 log->warn(tr("Did not decode lc->getConnectedType() of %1").arg(mehp.valueToKey(lc->getConnectedType())));  // NOI18N
             }
         } // is this Track Segment connected to the continuing track of a RH_XOVER or LH_XOVER?
         else if (HitPointType::isTurnoutHitType(lc->getConnectedType())
                 && ((((LayoutTurnout*) prevConnection)->getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
                 || (((LayoutTurnout*) prevConnection)->getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER))) {
             LayoutTurnout* ltz = (LayoutTurnout*) prevConnection;
             if (((ltz->getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
                     && ((lc->getConnectedType() == HitPointType::TURNOUT_B)
                     || (lc->getConnectedType() == HitPointType::TURNOUT_D)))
                     || ((ltz->getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)
                     && ((lc->getConnectedType() == HitPointType::TURNOUT_A)
                     || (lc->getConnectedType() == HitPointType::TURNOUT_C)))) {

                 Turnout* ltzto = ltz->getTurnout();
                 if (ltzto != nullptr) {
                     bs = new BeanSetting(ltzto, ltz->getTurnoutName(), Turnout::CLOSED);
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (C): LTO = %1, blk = %2, TO type = %3, conn type = %4").arg( // NOI18N
                             ltz->getName(), ltz->getLayoutBlock()->getDisplayName(), mett.valueToKey(ltz->getTurnoutType()), mehp.valueToKey(lc->getConnectedType())));
                 }
             }
         } // is this track section is connected to a slip?
         else if (HitPointType::isSlipHitType(lc->getConnectedType())) {
             LayoutSlip* lsz = (LayoutSlip*) prevConnection;
             if (lsz->getSlipType() == LayoutSlip::TurnoutType::SINGLE_SLIP) {
                 if (lc->getConnectedType() == HitPointType::SLIP_C) {
                     Turnout* lszto = lsz->getTurnout();
                     if (lszto != nullptr) {
                         bs = new BeanSetting(lszto, lsz->getTurnoutName(), lsz->getTurnoutState(LayoutTurnout::STATE_AC));
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnout (D): LTO = %1, blk = %2").arg(lsz->getName(), lsz->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }
                     Turnout* lsztob = lsz->getTurnoutB();
                     if (lsztob != nullptr) {
                         bs = new BeanSetting(lsztob, lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutTurnout::STATE_AC));
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnoutB (E): LTO = %1, blk = %2").arg(lsz->getName(), lsz->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }
                 } else if (lc->getConnectedType() == HitPointType::SLIP_B) {
                     Turnout* lszto = lsz->getTurnout();
                     if (lszto != nullptr) {
                         bs = new BeanSetting(lszto, lsz->getTurnoutName(), lsz->getTurnoutState(LayoutTurnout::STATE_BD));
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnout (F): LTO = %1, blk = %2").arg(lsz->getName(), lsz->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }

                     Turnout* lsztob = lsz->getTurnoutB();
                     if (lsztob != nullptr) {
                         bs = new BeanSetting(lsztob, lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutTurnout::STATE_BD));
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnoutB (G): LTO = %1, blk = %2").arg(lsz->getName(), lsz->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }
                 } else if (lc->getConnectedType() == HitPointType::SLIP_A) {
                     log->debug("At connection A of a single slip which could go in two different directions");  // NOI18N
                 } else if (lc->getConnectedType() == HitPointType::SLIP_D) {
                     log->debug("At connection D of a single slip which could go in two different directions");  // NOI18N
                 }
             } else {
                 //note: I'm adding these logs as a prequel to adding the correct code for double slips
                 if (lc->getConnectedType() == HitPointType::SLIP_A) {
                     log->debug("At connection A of a double slip which could go in two different directions");  // NOI18N
                 } else if (lc->getConnectedType() == HitPointType::SLIP_B) {
                     log->debug("At connection B of a double slip which could go in two different directions");  // NOI18N
                 } else if (lc->getConnectedType() == HitPointType::SLIP_C) {
                     log->debug("At connection C of a double slip which could go in two different directions");  // NOI18N
                 } else if (lc->getConnectedType() == HitPointType::SLIP_D) {
                     log->debug("At connection D of a double slip which could go in two different directions");  // NOI18N
                 } else {    // this should NEVER happen (it should always be SLIP_A, _B, _C or _D.
                     log->info("At a double slip we could go in two different directions");  // NOI18N
                 }
             }
         }
     } else {
         // block boundary is internal to a crossover turnout
         lt = lc->getXover();
         prevConnection = lt;
         if ((lt != nullptr) && (lt->getTurnout() != nullptr)) {
             int type = lc->getXoverBoundaryType();
             // bs is known to be nullptr at this point
             if (lt->getTurnout() != nullptr) {
                 if (type == LayoutConnectivity::XOVER_BOUNDARY_AB) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     curConnection = lt->getConnectA();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_CD) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     curConnection = lt->getConnectC();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_AC) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                     curConnection = lt->getConnectA();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_BD) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                     curConnection = lt->getConnectB();
                 } else {
                     log->warn(tr("failed to decode lc->getXoverBoundaryType() of %1 (A)").arg(lc->getXoverBoundaryType()));  // NOI18N
                 }
             }
             typeCurConnection = HitPointType::TRACK;
             if (bs != nullptr) {
                 p->addSetting(bs);
             } else {
                 log->error(tr("No assigned turnout (H): LTO = %1, blk = %2, type = %3").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName(), QString::number(type)));  // NOI18N
             }
         }
     }
 } else if (lc->getXover() != nullptr) {
     // first Block is not in a Track Segment, must be block boundary internal to a crossover turnout
     lt = lc->getXover();
     if ((lt != nullptr) && (lt->getTurnout() != nullptr)) {
         int type = lc->getXoverBoundaryType();
         // bs is known to be nullptr at this point
         if (lt->getTurnout() != nullptr) {
             if (type == LayoutConnectivity::XOVER_BOUNDARY_AB) {
                 bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                 curConnection = lt->getConnectB();
             } else if (type == LayoutConnectivity::XOVER_BOUNDARY_CD) {
                 bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                 curConnection = lt->getConnectD();
             } else if (type == LayoutConnectivity::XOVER_BOUNDARY_AC) {
                 bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                 curConnection = lt->getConnectC();
             } else if (type == LayoutConnectivity::XOVER_BOUNDARY_BD) {
                 bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                 curConnection = lt->getConnectD();
             } else {
                 log->warn(tr("failed to decode lc->getXoverBoundaryType() of %1 (B)").arg(lc->getXoverBoundaryType()));  // NOI18N
             }
         }
         typeCurConnection = HitPointType::TRACK;
         if (bs != nullptr) {
             p->addSetting(bs);
         } else {
             log->error(tr("No assigned turnout (I): LTO = %1, blk = %2, type = %3").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName(), mehp.valueToKey(type)));  // NOI18N
         }
     }
 } else {
     // block2 is this LayoutBlock, and block1 is in a track segment
     if (lc->getConnectedObject() != nullptr) {
         // connected object in this block is a turnout or levelxing
         curConnection = lc->getConnectedObject();
         prevConnection = lc->getTrackSegment();
         typeCurConnection = lc->getConnectedType();
         if (HitPointType::isTurnoutHitType(typeCurConnection)) {
             // connected object is a turnout
             LayoutTurnout::TurnoutType turnoutType = ((LayoutTurnout*) curConnection)->getTurnoutType();
             if (LayoutTurnout::hasEnteringDoubleTrack(turnoutType)) {
                 // have crossover turnout
                 if ((turnoutType == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
                         || ((turnoutType == LayoutTurnout::TurnoutType::RH_XOVER) && ((typeCurConnection == HitPointType::TURNOUT_A) || (typeCurConnection == HitPointType::TURNOUT_C)))
                         || ((turnoutType == LayoutTurnout::TurnoutType::LH_XOVER) && ((typeCurConnection == HitPointType::TURNOUT_B) || (typeCurConnection == HitPointType::TURNOUT_D)))) {
                     // entering turnout at a throat, cannot follow path any further
                     curConnection = nullptr;
                 } else {
                     // entering turnout at continuing track
                     if (((LayoutTurnout*) curConnection)->getTurnout() != nullptr) {
                         bs = new BeanSetting(((LayoutTurnout*) curConnection)->getTurnout(), ((LayoutTurnout*) curConnection)->getTurnoutName(), Turnout::CLOSED);
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnout (J): LTO = %1, blk = %2").arg( // NOI18N
                                 ((LayoutTurnout*) curConnection)->getName(), ((LayoutTurnout*) curConnection)->getLayoutBlock()->getDisplayName()));
                     }
                     prevConnection = curConnection;
                     if (typeCurConnection == HitPointType::TURNOUT_A) {
                         curConnection = ((LayoutTurnout*) curConnection)->getConnectB();
                     } else if (typeCurConnection == HitPointType::TURNOUT_B) {
                         curConnection = ((LayoutTurnout*) curConnection)->getConnectA();
                     } else if (typeCurConnection == HitPointType::TURNOUT_C) {
                         curConnection = ((LayoutTurnout*) curConnection)->getConnectD();
                     } else { // typeCurConnection == LayoutEditor.HitPointTypes.TURNOUT_D per if statement 3 levels up
                         curConnection = ((LayoutTurnout*) curConnection)->getConnectC();
                     }
                     typeCurConnection = HitPointType::TRACK;
                 }
             } // must be RH, LH, or WYE turnout
             else if (typeCurConnection == HitPointType::TURNOUT_A) {
                 // turnout throat, no bean setting needed and cannot follow Path any further
                 log->debug("At connection A of a turnout which could go in two different directions");  // NOI18N
                 curConnection = nullptr;
             } else if (typeCurConnection == HitPointType::TURNOUT_B) {
                 // continuing track of turnout
                 if (((LayoutTurnout*) curConnection)->getTurnout() != nullptr) {
                     if (((LayoutTurnout*) curConnection)->getContinuingSense() == Turnout::CLOSED) {
                         bs = new BeanSetting(((LayoutTurnout*) curConnection)->getTurnout(), ((LayoutTurnout*) curConnection)->getTurnoutName(), Turnout::CLOSED);
                     } else {
                         bs = new BeanSetting(((LayoutTurnout*) curConnection)->getTurnout(), ((LayoutTurnout*) curConnection)->getTurnoutName(), Turnout::THROWN);
                     }
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (K): LTO = %1, blk = %2").arg( // NOI18N
                             ((LayoutTurnout*) curConnection)->getName(), ((LayoutTurnout*) curConnection)->getLayoutBlock()->getDisplayName()));
                 }
                 prevConnection = curConnection;
                 curConnection = ((LayoutTurnout*) curConnection)->getConnectA();
                 typeCurConnection = HitPointType::TRACK;
             } else if (typeCurConnection == HitPointType::TURNOUT_C) {
                 // diverging track of turnout
                 if (((LayoutTurnout*) curConnection)->getTurnout() != nullptr) {
                     if (((LayoutTurnout*) curConnection)->getContinuingSense() == Turnout::CLOSED) {
                         bs = new BeanSetting(((LayoutTurnout*) curConnection)->getTurnout(), ((LayoutTurnout*) curConnection)->getTurnoutName(), Turnout::THROWN);
                     } else {
                         bs = new BeanSetting(((LayoutTurnout*) curConnection)->getTurnout(), ((LayoutTurnout*) curConnection)->getTurnoutName(), Turnout::CLOSED);
                     }
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (L): LTO = %1, blk = %2").arg( // NOI18N
                             ((LayoutTurnout*) curConnection)->getName(), ((LayoutTurnout*) curConnection)->getLayoutBlock()->getDisplayName()));
                 }
                 prevConnection = curConnection;
                 curConnection = ((LayoutTurnout*) curConnection)->getConnectA();
                 typeCurConnection = HitPointType::TRACK;
             }
         } // if level crossing, skip to the connected track segment on opposite side
         else if (typeCurConnection == HitPointType::LEVEL_XING_A) {
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectC();
             typeCurConnection = HitPointType::TRACK;
         } else if (typeCurConnection == HitPointType::LEVEL_XING_C) {
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectA();
             typeCurConnection = HitPointType::TRACK;
         } else if (typeCurConnection == HitPointType::LEVEL_XING_B) {
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectD();
             typeCurConnection = HitPointType::TRACK;
         } else if (typeCurConnection == HitPointType::LEVEL_XING_D) {
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectB();
             typeCurConnection = HitPointType::TRACK;
         }
     } else {
         // block boundary is internal to a crossover turnout
         lt = lc->getXover();
         prevConnection = lt;
         if ((lt != nullptr) && (lt->getTurnout() != nullptr)) {
             int type = lc->getXoverBoundaryType();
             // bs is known to be nullptr at this point
             if (lt->getTurnout() != nullptr) {
                 if (type == LayoutConnectivity::XOVER_BOUNDARY_AB) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     curConnection = lt->getConnectB();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_CD) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     curConnection = lt->getConnectD();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_AC) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                     curConnection = lt->getConnectC();
                 } else if (type == LayoutConnectivity::XOVER_BOUNDARY_BD) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                     curConnection = lt->getConnectD();
                 }
             }
             typeCurConnection = HitPointType::TRACK;
             if (bs != nullptr) {
                 p->addSetting(bs);
             } else {
                 log->error(tr("No assigned turnout (Q): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
             }
         }
     }
 }
 // follow path through this block - done when reaching another block, or a branching of Path
 while (curConnection != nullptr) {
     if (typeCurConnection == HitPointType::TRACK) {
         TrackSegment* curTS = (TrackSegment*) curConnection;
         // track segment is current connection
         if (curTS->getLayoutBlock() != layoutBlock) {
             curConnection = nullptr;
         } else {
             // skip over to other end of Track Segment
             if (curTS->getConnect1() == prevConnection) {
                 prevConnection = curConnection;
                 typeCurConnection = curTS->getType2();
                 curConnection = curTS->getConnect2();
             } else {
                 prevConnection = curConnection;
                 typeCurConnection = curTS->getType1();
                 curConnection = curTS->getConnect1();
             }
             // skip further if positionable point (possible anchor point)
             if (typeCurConnection == HitPointType::POS_POINT) {
                 PositionablePoint* pt = (PositionablePoint*) curConnection;
                 if (pt->getType() == PositionablePoint::PointType::END_BUMPER) {
                     // reached end of track
                     curConnection = nullptr;
                 } else {
                     // at an anchor point, find track segment on other side
                     TrackSegment* track = nullptr;
                     if (pt->getConnect1() == prevConnection) {
                         track = pt->getConnect2();
                     } else {
                         track = pt->getConnect1();
                     }
                     // check for block boundary
                     if ((track == nullptr) || (track->getLayoutBlock() != layoutBlock)) {
                         // moved outside of block - anchor point was a block boundary -OR-
                         //  reached the end of the defined track
                         curConnection = nullptr;
                     } else {
                         prevConnection = curConnection;
                         curConnection = track;
                         typeCurConnection = HitPointType::TRACK;
                     }
                 }
             }
         }
     } else if (HitPointType::isTurnoutHitType(typeCurConnection)) {
         lt = (LayoutTurnout*) curConnection;
         // test for crossover turnout
         if (lt->hasEnteringSingleTrack()) {
             // have RH, LH, or WYE turnout

             if (lt->getLayoutBlock() != layoutBlock) {
                 curConnection = nullptr;
             } else {
                 // turnout is in current block, test connection point
                 if (typeCurConnection == HitPointType::TURNOUT_A) {
                     // turnout throat, no bean setting needed and cannot follow possible path any further
                     curConnection = nullptr;
                 } else if (typeCurConnection == HitPointType::TURNOUT_B) {
                     // continuing track of turnout, add a bean setting
                     if (lt->getTurnout() != nullptr) {
                         if (lt->getContinuingSense() == Turnout::CLOSED) {
                             bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                         } else {
                             bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                         }
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnout (R): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }
                     if (lt->getLayoutBlock() != layoutBlock) {
                         curConnection = nullptr;
                     } else {
                         prevConnection = curConnection;
                         curConnection = lt->getConnectA();
                         typeCurConnection = HitPointType::TRACK;
                     }
                 } else if (typeCurConnection == HitPointType::TURNOUT_C) {
                     // diverging track of turnout
                     if (lt->getTurnout() != nullptr) {
                         if (lt->getContinuingSense() == Turnout::CLOSED) {
                             bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
                         } else {
                             bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                         }
                         p->addSetting(bs);
                     } else {
                         log->error(tr("No assigned turnout (S): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                     }
                     if (lt->getLayoutBlock() != layoutBlock) {
                         curConnection = nullptr;
                     } else {
                         prevConnection = curConnection;
                         curConnection = lt->getConnectA();
                         typeCurConnection = HitPointType::TRACK;
                     }
                 }
             }
         } else if (lt->getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
             // have a double crossover turnout, cannot follow possible path any further
             curConnection = nullptr;
         } else if (lt->getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
             // have a right-handed crossover turnout
             if ((typeCurConnection == HitPointType::TURNOUT_A)
                     || (typeCurConnection == HitPointType::TURNOUT_C)) {
                 // entry is at turnout throat, cannot follow possible path any further
                 curConnection = nullptr;
             } else if (typeCurConnection == HitPointType::TURNOUT_B) {
                 // entry is at continuing track of turnout
                 if (lt->getLayoutBlockB() != layoutBlock) {
                     // cross-over block different, end of current block
                     break;
                 }
                 if (lt->getTurnout() != nullptr) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (T): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 if (lt->getLayoutBlock() != layoutBlock) {
                     // left current block
                     curConnection = nullptr;
                 } else {
                     prevConnection = curConnection;
                     curConnection = lt->getConnectA();
                     typeCurConnection = HitPointType::TRACK;
                 }
             } else { // typeCurConnection == LayoutEditor.HitPointTypes.TURNOUT_D
                 // entry is at continuing track of turnout
                 if (lt->getLayoutBlockD() != layoutBlock) {
                     // cross-over block different, end of current block
                     break;
                 }
                 if (lt->getTurnout() != nullptr) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (U): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 if (lt->getLayoutBlockC() != layoutBlock) {
                     // left current block
                     curConnection = nullptr;
                 } else {
                     prevConnection = curConnection;
                     curConnection = lt->getConnectC();
                     typeCurConnection = HitPointType::TRACK;
                 }
             }
         } else if (lt->getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
             // have a left-handed crossover turnout
             if ((typeCurConnection == HitPointType::TURNOUT_B)
                     || (typeCurConnection == HitPointType::TURNOUT_D)) {
                 // entry is at turnout throat, cannot follow possible path any further
                 curConnection = nullptr;
             } else if (typeCurConnection == HitPointType::TURNOUT_A) {
                 // entry is at continuing track of turnout
                 if (lt->getLayoutBlock() != layoutBlock) {
                     // cross-over block different, end of current block
                     break;
                 }
                 if (lt->getTurnout() != nullptr) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (V): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 if (lt->getLayoutBlockB() != layoutBlock) {
                     // left current block
                     curConnection = nullptr;
                 } else {
                     prevConnection = curConnection;
                     curConnection = lt->getConnectB();
                     typeCurConnection = HitPointType::TRACK;
                 }
             } else { // typeCurConnection == LayoutEditor.HitPointTypes.TURNOUT_C per if statement 2 levels up
                 // entry is at continuing track of turnout
                 if (lt->getLayoutBlockC() != layoutBlock) {
                     // cross-over block different, end of current block
                     break;
                 }
                 if (lt->getTurnout() != nullptr) {
                     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
                     p->addSetting(bs);
                 } else {
                  log->error(tr("No assigned turnout (W): LTO = %1, blk = %2").arg(lt->getName(), lt->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 if (lt->getLayoutBlockD() != layoutBlock) {
                     // left current block
                     curConnection = nullptr;
                 } else {
                     prevConnection = curConnection;
                     curConnection = lt->getConnectD();
                     typeCurConnection = HitPointType::TRACK;
                 }
             }
         }
     } else if (typeCurConnection == HitPointType::LEVEL_XING_A) {
         // have a level crossing connected at A
         if (((LevelXing*) curConnection)->getLayoutBlockAC() != layoutBlock) {
             // moved outside of this block
             curConnection = nullptr;
         } else {
             // move to other end of this section of this level crossing track
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectC();
             typeCurConnection = HitPointType::TRACK;
         }
     } else if (typeCurConnection == HitPointType::LEVEL_XING_B) {
         // have a level crossing connected at B
         if (((LevelXing*) curConnection)->getLayoutBlockBD() != layoutBlock) {
             // moved outside of this block
             curConnection = nullptr;
         } else {
             // move to other end of this section of this level crossing track
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectD();
             typeCurConnection = HitPointType::TRACK;
         }
     } else if (typeCurConnection == HitPointType::LEVEL_XING_C) {
         // have a level crossing connected at C
         if (((LevelXing*) curConnection)->getLayoutBlockAC() != layoutBlock) {
             // moved outside of this block
             curConnection = nullptr;
         } else {
             // move to other end of this section of this level crossing track
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectA();
             typeCurConnection = HitPointType::TRACK;
         }
     } else if (typeCurConnection == HitPointType::LEVEL_XING_D) {
         // have a level crossing connected at D
         if (((LevelXing*) curConnection)->getLayoutBlockBD() != layoutBlock) {
             // moved outside of this block
             curConnection = nullptr;
         } else {
             // move to other end of this section of this level crossing track
             prevConnection = curConnection;
             curConnection = ((LevelXing*) curConnection)->getConnectB();
             typeCurConnection = HitPointType::TRACK;
         }
     } else if (HitPointType::isSlipHitType(typeCurConnection)) {
         LayoutSlip* ls = (LayoutSlip*) curConnection;
         if (ls->getLayoutBlock() != layoutBlock) {
             curConnection = nullptr;
         } else if (ls->getSlipType() == LayoutSlip::TurnoutType::SINGLE_SLIP) {
             if (typeCurConnection == HitPointType::SLIP_C) {
                 if (ls->getTurnout() != nullptr) {
                     bs = new BeanSetting(ls->getTurnout(), ls->getTurnoutName(), ls->getTurnoutState(LayoutTurnout::STATE_AC));
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (X): LTO = %1, blk = %2").arg(ls->getName(), ls->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 if (ls->getTurnoutB() != nullptr) {
                     bs = new BeanSetting(ls->getTurnoutB(), ls->getTurnoutBName(), ls->getTurnoutBState(LayoutTurnout::STATE_AC));
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnoutB (Y): LTO = %1, blk = %2").arg(ls->getName(), ls->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 prevConnection = curConnection;
                 curConnection = ((LayoutSlip*) curConnection)->getConnectC();
                 typeCurConnection = HitPointType::TRACK;
             } else if (typeCurConnection == HitPointType::SLIP_B) {
                 if (ls->getTurnout() != nullptr) {
                     bs = new BeanSetting(ls->getTurnout(), ls->getTurnoutName(), ls->getTurnoutState(LayoutTurnout::STATE_BD));
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnout (Z): LTO = %1, blk = %2").arg(ls->getName(), ls->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }

                 if (ls->getTurnoutB() != nullptr) {
                     bs = new BeanSetting(ls->getTurnoutB(), ls->getTurnoutBName(), ls->getTurnoutBState(LayoutTurnout::STATE_BD));
                     p->addSetting(bs);
                 } else {
                     log->error(tr("No assigned turnoutB (1): LTO = %1, blk = %2").arg(ls->getName(), ls->getLayoutBlock()->getDisplayName()));  // NOI18N
                 }
                 prevConnection = curConnection;
                 curConnection = ((LayoutSlip*) curConnection)->getConnectB();
                 typeCurConnection = HitPointType::TRACK;
             } else {
                 //Else could be going in the slip direction
                 curConnection = nullptr;
             }

         } else {
             //At double slip, can not follow any further
             curConnection = nullptr;
         }
     } else if (HitPointType::isTurntableRayHitType(typeCurConnection)) {
         if (log->isDebugEnabled()) {
             log->debug(tr("Layout Block: %1, found track type: %2, to Block: %3, is potentially assigned to turntable ray").arg( // NOI18N
                     layoutBlock->getDisplayName(),
                     mehp.valueToKey(typeCurConnection),
                     p->getBlock()->getDisplayName()
             ));
         }
         curConnection = nullptr;
     } else {
         // catch when some new type got added
         log->error(tr("Layout Block: %1 found unknown track type:%2 to Block: %2").arg(
                 layoutBlock->getDisplayName(),
                 mehp.valueToKey(typeCurConnection),
                 p->getBlock()->getDisplayName()
         ));
         break;
     }
 }
 models->layoutEditorComponent->initialized = true;
 models->layoutEditorComponent->paintTargetPanel(/*g2*/models->editScene);
}

// initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutEditorAuxTools->class.getName());
//}
