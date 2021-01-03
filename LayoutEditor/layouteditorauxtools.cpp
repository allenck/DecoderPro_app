#include "layouteditorauxtools.h"
#include <qmath.h>
#include "instancemanager.h"
#include "path.h"
#include "tracksegment.h"
#include "layoutturnout.h"

//LayoutEditorAuxTools::LayoutEditorAuxTools(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * LayoutEditorAuxTools provides tools making use of layout connectivity available
 *	in Layout Editor panels.  (More tools are in LayoutEditorTools.java.)
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
/*public*/ LayoutEditorAuxTools::LayoutEditorAuxTools(LayoutEditor* thePanel) {
 log = new Logger("LayoutEditorAuxTools");
 layoutEditor = NULL;
 cList = new QVector<LayoutConnectivity*>(); //LayoutConnectivity list
 blockConnectivityChanged = false;  // true if block connectivity may have changed
 initialized = false;

 layoutEditor = thePanel;
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
    QList<LayoutConnectivity*>* lcs;

    for (LayoutTrack* lt : *layoutEditor->getLayoutTracks()) {
        if ((qobject_cast<PositionablePoint*>(lt))
                || (qobject_cast<TrackSegment*>(lt))
                || (qobject_cast<LayoutTurnout*>(lt)))
        { // <== includes LayoutSlips
            lcs = lt->getLayoutConnectivity();
            //cList->addAll(lcs); // append to list
            foreach(LayoutConnectivity* lc, *lcs)
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

 QList<LayoutConnectivity*>* lcs;

 // Check for block boundaries at positionable points.
 for (PositionablePoint* p : layoutEditor->getPositionablePoints()) {
     lcs = p->getLayoutConnectivity();
     for (LayoutConnectivity* lc : *lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // Check for block boundaries at layout turnouts and level crossings
 for (TrackSegment* ts : layoutEditor->getTrackSegments()) {
     lcs = ts->getLayoutConnectivity();
     for (LayoutConnectivity* lc : *lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // check for block boundaries internal to crossover turnouts
 for (LayoutTrack* lt : layoutEditor->getLayoutTurnouts()) {
     lcs = lt->getLayoutConnectivity();
     for (LayoutConnectivity* lc : *lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // check for block boundaries internal to slips
 for (LayoutSlip* ls : layoutEditor->getLayoutSlips()) {
     lcs = ls->getLayoutConnectivity();
     for (LayoutConnectivity* lc : *lcs) {
         // add to list, if not already present
         checkConnectivity(lc, found);
     }
 }

 // delete any LayoutConnectivity objects no longer needed
 for (int i = sz - 1; i >= 0; i--) {
     if (!found[i]) {
         // djd debugging - message to list connectivity being removed
         //    LayoutConnectivity xx = (LayoutConnectivity)cList.get(i);
         //    log.error("  Deleting Layout Connectivity - " + xx.getBlock1().getId() + ", " + xx.getBlock2().getId());
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
    int type = c->getConnectedType();
    LayoutTurnout* xOver = c->getXover();
    int xOverType = c->getXoverBoundaryType();
    // loop over connectivity list, looking for this layout connectivity
    bool looking = true;
    for (int i = 0;(i<cList->size()) && looking;i++) {
        LayoutConnectivity* lc = cList->at(i);
        // compare input LayoutConnectivity with LayoutConnectivity from the list
        if (xOver==NULL) {
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
 QObject* curConnection = NULL;
 QObject* prevConnection = NULL;
 int typeCurConnection = 0;
 BeanSetting* bs = NULL;
 LayoutTurnout* lt = NULL;
 // process object at block boundary
 if (lc->getBlock1()==layoutBlock)
 {
  // block1 is this LayoutBlock
  if (lc->getTrackSegment()!=NULL)
  {
   // connected object in this block is a track segment
   curConnection = lc->getTrackSegment();
   prevConnection = lc->getConnectedObject();
   typeCurConnection = LayoutEditor::TRACK;
   // is this Track Segment connected to a RH, LH, or WYE turnout at the continuing or diverging track
   if ( ( (lc->getConnectedType()==LayoutEditor::TURNOUT_B) ||
               (lc->getConnectedType()==LayoutEditor::TURNOUT_C) ) &&
               ( (((LayoutTurnout*)prevConnection)->getTurnoutType()>=LayoutTurnout::RH_TURNOUT) &&
               (((LayoutTurnout*)prevConnection)->getTurnoutType()<=LayoutTurnout::WYE_TURNOUT) ) )
   {
    LayoutTurnout* ltx = (LayoutTurnout*)prevConnection;
    if (lc->getConnectedType()==LayoutEditor::TURNOUT_B)
    {
     // Track Segment connected to continuing track of turnout
     if (ltx->getContinuingSense()==Turnout::CLOSED)
         bs = new BeanSetting(ltx->getTurnout(), ltx->getTurnoutName(), Turnout::CLOSED);
     else
         bs = new BeanSetting(ltx->getTurnout(), ltx->getTurnoutName(),Turnout::THROWN);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else
     {
//                        static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")).addBadBeanError();
      log->error("BadBeanError: " + ltx->getName() + " " + ltx->getLayoutBlock()->getDisplayName());
     }
    }
    else if (lc->getConnectedType()==LayoutEditor::TURNOUT_C)
    {
     // Track Segment connected to diverging track of turnout
     if (ltx->getContinuingSense()==Turnout::CLOSED)
      bs = new BeanSetting(ltx->getTurnout(), ltx->getTurnoutName() ,Turnout::THROWN);
     else
      bs = new BeanSetting(ltx->getTurnout(), ltx->getTurnoutName(),Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else
     {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
      log->error("BadBeanError: " + ltx->getName() + " " + ltx->getLayoutBlock()->getDisplayName());
     }
    }
   }
   // is this Track Segment connected to the continuing track of a RH_XOVER or LH_XOVER
   else if ( ( (lc->getConnectedType()>=LayoutEditor::TURNOUT_A) &&
            (lc->getConnectedType()<=LayoutEditor::TURNOUT_D) ) &&
            ( (((LayoutTurnout*)prevConnection)->getTurnoutType()==LayoutTurnout::RH_XOVER) ||
            (((LayoutTurnout*)prevConnection)->getTurnoutType()==LayoutTurnout::LH_XOVER) ) )
   {
    LayoutTurnout* ltz = (LayoutTurnout*)prevConnection;
    if ( ( (ltz->getTurnoutType()==LayoutTurnout::RH_XOVER) &&
            ( (lc->getConnectedType()==LayoutEditor::TURNOUT_B) ||
            (lc->getConnectedType()==LayoutEditor::TURNOUT_D)	) ) ||
            ( (ltz->getTurnoutType()==LayoutTurnout::LH_XOVER) &&
            ( (lc->getConnectedType()==LayoutEditor::TURNOUT_A) ||
            (lc->getConnectedType()==LayoutEditor::TURNOUT_C)	) ) )
    {
     bs = new BeanSetting(ltz->getTurnout(), ltz->getTurnoutName(),Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else
     {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
      log->error("BadBeanError: " + ltz->getName() + " " + ltz->getLayoutBlock()->getDisplayName());
     }
    }
   }
   //This track section is connected to a slip
   else if( lc->getConnectedType()>=LayoutEditor::SLIP_A &&
           lc->getConnectedType()<=LayoutEditor::SLIP_D)
   {
    LayoutSlip* lsz = (LayoutSlip*)prevConnection;
    if(lsz->getSlipType()==LayoutSlip::SINGLE_SLIP)
    {
     if(lc->getConnectedType()==LayoutEditor::SLIP_C)
     {
      bs = new BeanSetting(lsz->getTurnout(), lsz->getTurnoutName(), lsz->getTurnoutState(LayoutSlip::STATE_AC));
      if (bs->getBean() != NULL)
       p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
          log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
      bs = new BeanSetting(lsz->getTurnoutB(), lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutSlip::STATE_AC));
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
     }
     else if (lc->getConnectedType()==LayoutEditor::SLIP_B)
     {
      bs = new BeanSetting(lsz->getTurnout(), lsz->getTurnoutName(), lsz->getTurnoutState(LayoutSlip::STATE_BD));
      if (bs->getBean() != NULL)
       p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }

      bs = new BeanSetting(lsz->getTurnoutB(), lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutSlip::STATE_BD));
      if (bs->getBean() != NULL)
       p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
          log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
     }
     else if (lc->getConnectedType()==LayoutEditor::SLIP_A)
     {
      //As connection A of a single slip which could go in two different directions
     }
     else if (lc->getConnectedType()==LayoutEditor::SLIP_D)
     {
      //As connection D of a single slip which could go in two different directions
     }
    }
    else
    {
     //At a double slip we could go in two different directions
    }
   }
  }
  else
  {
   // block boundary is internal to a crossover turnout
   lt = lc->getXover();
   prevConnection = lt;
   if ( (lt!=NULL) && (lt->getTurnout()!=NULL) )
   {
    int type = lc->getXoverBoundaryType();
    if (type==LayoutConnectivity::XOVER_BOUNDARY_AB)
    {
        bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
        curConnection = lt->getConnectA();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_CD)
    {
        bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::CLOSED);
        curConnection = lt->getConnectC();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_AC)
    {
        bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::THROWN);
        curConnection = lt->getConnectA();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_BD)
    {
        bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::THROWN);
        curConnection = lt->getConnectB();
    }
    typeCurConnection = LayoutEditor::TRACK;
    if ( (bs != NULL) && (bs->getBean() != NULL) )
        p->addSetting(bs);
    else
    {
//                    InstanceManager.layoutBlockManagerInstance().addBadBeanError();
     log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
    }
   }
  }
 }
 else if (lc->getXover()!=NULL)
 {
  // first Block is not in a Track Segment, must be block boundary internal to a crossover turnout
  lt = lc->getXover();
  if ( (lt!=NULL) && (lt->getTurnout()!=NULL) )
  {
   int type = lc->getXoverBoundaryType();
   if (type==LayoutConnectivity::XOVER_BOUNDARY_AB)
   {
    bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::CLOSED);
    curConnection = lt->getConnectB();
   }
   else if (type==LayoutConnectivity::XOVER_BOUNDARY_CD)
   {
    bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::CLOSED);
    curConnection = lt->getConnectD();
   }
   else if (type==LayoutConnectivity::XOVER_BOUNDARY_AC)
   {
    bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::THROWN);
    curConnection = lt->getConnectC();
   }
   else if (type==LayoutConnectivity::XOVER_BOUNDARY_BD)
   {
    bs = new BeanSetting(lt->getTurnout(),lt->getTurnoutName(),Turnout::THROWN);
    curConnection = lt->getConnectD();
   }
   typeCurConnection = LayoutEditor::TRACK;
   if ( (bs != NULL) && (bs->getBean() != NULL) )
    p->addSetting(bs);
   else
   {
//                static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")).addBadBeanError();
    log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
   }
  }
 }
 else
 {
  // block2 is this LayoutBlock, and block1 is in a track segment
  if (lc->getConnectedObject()!=NULL)
  {
   // connected object in this block is a turnout or levelxing
   curConnection = lc->getConnectedObject();
   prevConnection = lc->getTrackSegment();
   typeCurConnection = lc->getConnectedType();
   if ( (typeCurConnection>=LayoutEditor::TURNOUT_A) && (typeCurConnection<=LayoutEditor::TURNOUT_D) )
   {
    // connected object is a turnout
    int turnoutType = ((LayoutTurnout*)curConnection)->getTurnoutType();
    if (turnoutType>LayoutTurnout::WYE_TURNOUT)
    {
     // have crossover turnout
     if ( (turnoutType==LayoutTurnout::DOUBLE_XOVER) || ((turnoutType==LayoutTurnout::RH_XOVER) &&
         ( (typeCurConnection==LayoutEditor::TURNOUT_A) ||
             (typeCurConnection==LayoutEditor::TURNOUT_C) )) ||
             ((turnoutType==LayoutTurnout::LH_XOVER) &&
                 ( (typeCurConnection==LayoutEditor::TURNOUT_B) ||
                     (typeCurConnection==LayoutEditor::TURNOUT_D) )) )
     {
      // entering turnout at a throat, cannot follow path any further
      curConnection=NULL;
     }
     else
     {
      // entering turnout at continuing track
      bs = new BeanSetting(((LayoutTurnout*)curConnection)->getTurnout(),((LayoutTurnout*)curConnection)->getTurnoutName(),Turnout::CLOSED);
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
//                            InstanceManager.layoutBlockManagerInstance().addBadBeanError();
       log->error("BadBeanError: " + ((LayoutTurnout*)curConnection)->getName() + " " + ((LayoutTurnout*)curConnection)->getLayoutBlock()->getDisplayName());
      }
      prevConnection = curConnection;
      if (typeCurConnection==LayoutEditor::TURNOUT_A)
      {
       curConnection = ((LayoutTurnout*)curConnection)->getConnectB();
      }
      else if (typeCurConnection==LayoutEditor::TURNOUT_B)
      {
       curConnection = ((LayoutTurnout*)curConnection)->getConnectA();
      }
      else if (typeCurConnection==LayoutEditor::TURNOUT_C)
      {
       curConnection = ((LayoutTurnout*)curConnection)->getConnectD();
      }
      else if (typeCurConnection==LayoutEditor::TURNOUT_D)
      {
       curConnection = ((LayoutTurnout*)curConnection)->getConnectC();
      }
      typeCurConnection = LayoutEditor::TRACK;
     }
    }
    // must be RH, LH, or WYE turnout
    else if (typeCurConnection==LayoutEditor::TURNOUT_A)
    {
     // turnout throat, no bean setting needed and cannot follow Path any further
     curConnection=NULL;
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_B)
    {
     // continuing track of turnout
     if (((LayoutTurnout*)curConnection)->getContinuingSense()==Turnout::CLOSED)
      bs = new BeanSetting(((LayoutTurnout*)curConnection)->getTurnout(),((LayoutTurnout*)curConnection)->getTurnoutName(), Turnout::CLOSED);
     else
      bs = new BeanSetting(((LayoutTurnout*)curConnection)->getTurnout(),((LayoutTurnout*)curConnection)->getTurnoutName(), Turnout::THROWN);
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
      log->error("BadBeanError: " + ((LayoutTurnout*)curConnection)->getName() + " " + ((LayoutTurnout*)curConnection)->getLayoutBlock()->getDisplayName());
     }
     prevConnection = curConnection;
     curConnection = ((LayoutTurnout*)curConnection)->getConnectA();
     typeCurConnection = LayoutEditor::TRACK;
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_C)
    {
     // diverging track of turnout
     if (((LayoutTurnout*)curConnection)->getContinuingSense()==Turnout::CLOSED)
         bs = new BeanSetting(((LayoutTurnout*)curConnection)->getTurnout(), ((LayoutTurnout*)curConnection)->getTurnoutName(), Turnout::THROWN);
     else
         bs = new BeanSetting(((LayoutTurnout*)curConnection)->getTurnout(), ((LayoutTurnout*)curConnection)->getTurnoutName(), Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else
     {
//                        static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")).addBadBeanError();
      log->error("BadBeanError: " + ((LayoutTurnout*)curConnection)->getName() + " " + ((LayoutTurnout*)curConnection)->getLayoutBlock()->getDisplayName());
     }
     prevConnection = curConnection;
     curConnection = ((LayoutTurnout*)curConnection)->getConnectA();
     typeCurConnection = LayoutEditor::TRACK;
    }
   }
   // if level crossing, skip to the connected track segment on opposite side
   else if (typeCurConnection==LayoutEditor::LEVEL_XING_A)
   {
       prevConnection = curConnection;
       curConnection = ((LevelXing*)curConnection)->getConnectC();
       typeCurConnection = LayoutEditor::TRACK;
   }
   else if (typeCurConnection==LayoutEditor::LEVEL_XING_C)
   {
       prevConnection = curConnection;
       curConnection = ((LevelXing*)curConnection)->getConnectA();
       typeCurConnection = LayoutEditor::TRACK;
   }
   else if (typeCurConnection==LayoutEditor::LEVEL_XING_B)
   {
       prevConnection = curConnection;
       curConnection = ((LevelXing*)curConnection)->getConnectD();
       typeCurConnection = LayoutEditor::TRACK;
   }
   else if (typeCurConnection==LayoutEditor::LEVEL_XING_D)
   {
       prevConnection = curConnection;
       curConnection = ((LevelXing*)curConnection)->getConnectB();
       typeCurConnection = LayoutEditor::TRACK;
   }
   else if (typeCurConnection>=LayoutEditor::SLIP_A && typeCurConnection==LayoutEditor::SLIP_D)
   {
    LayoutSlip* lsz = (LayoutSlip*)curConnection;
    if(lsz->getSlipType()==LayoutSlip::SINGLE_SLIP)
    {
     if(typeCurConnection==LayoutEditor::SLIP_C)
     {
      prevConnection = curConnection;
      curConnection = ((LayoutSlip*)curConnection)->getConnectC();
      typeCurConnection = LayoutEditor::TRACK;
      bs = new BeanSetting(lsz->getTurnout(), lsz->getTurnoutName(), lsz->getTurnoutState(LayoutSlip::STATE_AC));
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else {
          static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
          log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
      bs = new BeanSetting(lsz->getTurnoutB(), lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutSlip::STATE_AC));
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else {
          static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
          log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
     }
     else if (typeCurConnection==LayoutEditor::SLIP_B)
     {
      prevConnection = curConnection;
      curConnection = ((LayoutSlip*)curConnection)->getConnectB();
      typeCurConnection = LayoutEditor::TRACK;
      bs = new BeanSetting(lsz->getTurnout(), lsz->getTurnoutName(), lsz->getTurnoutState(LayoutSlip::STATE_BD));
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }

      bs = new BeanSetting(lsz->getTurnoutB(), lsz->getTurnoutBName(), lsz->getTurnoutBState(LayoutSlip::STATE_BD));
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lsz->getName() + " " + lsz->getLayoutBlock()->getDisplayName());
      }
     }
     else
     {
      //Else could be going in the slip direction
      curConnection = NULL;
     }
    }
    else
    {
     //A double slip has effectively two seperate directions that it could take, therefore can not follow path any further.
     curConnection=NULL;
    }
   }
  }
  else
  {
   // block boundary is internal to a crossover turnout
   lt = lc->getXover();
   prevConnection = lt;
   if ( (lt!=NULL) && (lt->getTurnout()!=NULL) )
   {
    int type = lc->getXoverBoundaryType();
    if (type==LayoutConnectivity::XOVER_BOUNDARY_AB)
    {
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
     curConnection = lt->getConnectB();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_CD)
    {
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(),Turnout::CLOSED);
     curConnection = lt->getConnectD();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_AC)
    {
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(),Turnout::THROWN);
     curConnection = lt->getConnectC();
    }
    else if (type==LayoutConnectivity::XOVER_BOUNDARY_BD)
    {
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(),Turnout::THROWN);
     curConnection = lt->getConnectD();
    }
    typeCurConnection = LayoutEditor::TRACK;
    if ( (bs != NULL) && (bs->getBean() != NULL) )
        p->addSetting(bs);
    else
    {
     static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
     log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
       }
   }
  }
 }
 // follow path through this block - done when reaching another block, or a branching of Path
 while (curConnection!=NULL)
 {
  if (typeCurConnection == LayoutEditor::TRACK)
  {
   // track segment is current connection
   if (((TrackSegment*)curConnection)->getLayoutBlock()!=layoutBlock)
   {
    curConnection = NULL;
   }
   else
   {
    // skip over to other end of Track Segment
    if (((TrackSegment*)curConnection)->getConnect1()==prevConnection)
    {
     prevConnection = curConnection;
     typeCurConnection = ((TrackSegment*)curConnection)->getType2();
     curConnection = ((TrackSegment*)curConnection)->getConnect2();
    }
    else
    {
     prevConnection = curConnection;
     typeCurConnection = ((TrackSegment*)curConnection)->getType1();
     curConnection = ((TrackSegment*)curConnection)->getConnect1();
    }
    // skip further if positionable point (possible anchor point)
    if (typeCurConnection ==  LayoutEditor::POS_POINT)
    {
     PositionablePoint* pt = (PositionablePoint*)curConnection;
     if (pt->getType() == PositionablePoint::END_BUMPER)
     {
      // reached end of track
      curConnection = NULL;
     }
     else
     {
      // at an anchor point, find track segment on other side
      TrackSegment* track = NULL;
      if (pt->getConnect1() == prevConnection) track = pt->getConnect2();
      else track = pt->getConnect1();
      // check for block boundary
      if ( (track==NULL) || (track->getLayoutBlock()!=layoutBlock) )
      {
       // moved outside of block - anchor point was a block boundary -OR-
       //		reached the end of the defined track
       curConnection = NULL;
      }
      else
      {
       prevConnection = curConnection;
       curConnection = track;
       typeCurConnection = LayoutEditor::TRACK;
      }
     }
    }
   }
  }
  else if ( (typeCurConnection >= LayoutEditor::TURNOUT_A) &&
                                  (typeCurConnection <= LayoutEditor::TURNOUT_D) )
  {
   lt = (LayoutTurnout*)curConnection;
   // test for crossover turnout
   if (lt->getTurnoutType() <= LayoutTurnout::WYE_TURNOUT)
   {
    // have RH, LH, or WYE turnout

    if (lt->getLayoutBlock()!=layoutBlock)
    {
     curConnection = NULL;
    }
    else
    {
     // turnout is in current block, test connection point
     if (typeCurConnection == LayoutEditor::TURNOUT_A)
     {
      // turnout throat, no bean setting needed and cannot follow possible path any further
      curConnection=NULL;
     }
     else if (typeCurConnection==LayoutEditor::TURNOUT_B)
     {
      // continuing track of turnout, add a bean setting
      if (lt->getContinuingSense()==Turnout::CLOSED)
          bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName() ,Turnout::CLOSED);
      else
          bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName() ,Turnout::THROWN);
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
      }
      if (lt->getLayoutBlock()!=layoutBlock)
      {
       curConnection = NULL;
      }
      else
      {
       prevConnection = curConnection;
       curConnection = lt->getConnectA();
       typeCurConnection = LayoutEditor::TRACK;
      }
     }
     else if (typeCurConnection==LayoutEditor::TURNOUT_C)
     {
      // diverging track of turnout
      if (lt->getContinuingSense()==Turnout::CLOSED)
          bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::THROWN);
      else
          bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
      if (bs->getBean() != NULL)
          p->addSetting(bs);
      else
      {
       static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
       log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
      }
      if (lt->getLayoutBlock()!=layoutBlock)
      {
       curConnection = NULL;
      }
      else
      {
       prevConnection = curConnection;
       curConnection = lt->getConnectA();
       typeCurConnection = LayoutEditor::TRACK;
      }
     }
    }
   }
   else if (lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
   {
    // have a double crossover turnout, cannot follow possible path any further
    curConnection = NULL;
   }
   else if (lt->getTurnoutType() == LayoutTurnout::RH_XOVER)
   {
    // have a right-handed crossover turnout
    if ( (typeCurConnection==LayoutEditor::TURNOUT_A) ||
            (typeCurConnection==LayoutEditor::TURNOUT_C) )
    {
        // entry is at turnout throat, cannot follow possible path any further
     curConnection = NULL;
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_B)
    {
     // entry is at continuing track of turnout
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
      log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
     }
     if (lt->getLayoutBlock()!=layoutBlock)
     {
      // left current block
      curConnection = NULL;
     }
     else
     {
      prevConnection = curConnection;
      curConnection = lt->getConnectA();
      typeCurConnection = LayoutEditor::TRACK;
     }
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_D)
    {
     // entry is at continuing track of turnout
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName() ,Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else
     {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
         log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getSystemName());
     }
     if (lt->getLayoutBlockC()!=layoutBlock)
     {
         // left current block
         curConnection = NULL;
     }
     else {
         prevConnection = curConnection;
         curConnection = lt->getConnectC();
         typeCurConnection = LayoutEditor::TRACK;
     }
    }
   }
   else if (lt->getTurnoutType() == LayoutTurnout::LH_XOVER)
   {
    // have a left-handed crossover turnout
    if ( (typeCurConnection==LayoutEditor::TURNOUT_B) ||
            (typeCurConnection==LayoutEditor::TURNOUT_D) )
    {
     // entry is at turnout throat, cannot follow possible path any further
     curConnection = NULL;
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_A)
    {
     // entry is at continuing track of turnout
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(), Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
         log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
     }
     if (lt->getLayoutBlockB()!=layoutBlock) {
         // left current block
         curConnection = NULL;
     }
     else {
         prevConnection = curConnection;
         curConnection = lt->getConnectB();
         typeCurConnection = LayoutEditor::TRACK;
     }
    }
    else if (typeCurConnection==LayoutEditor::TURNOUT_C)
    {
     // entry is at continuing track of turnout
     bs = new BeanSetting(lt->getTurnout(), lt->getTurnoutName(),Turnout::CLOSED);
     if (bs->getBean() != NULL)
         p->addSetting(bs);
     else {
//                        InstanceManager.layoutBlockManagerInstance().addBadBeanError();
         log->error("BadBeanError: " + lt->getName() + " " + lt->getLayoutBlock()->getDisplayName());
     }
     if (lt->getLayoutBlockD()!=layoutBlock) {
         // left current block
         curConnection = NULL;
     }
     else {
         prevConnection = curConnection;
         curConnection = lt->getConnectD();
         typeCurConnection = LayoutEditor::TRACK;
     }
    }
   }
  }
  else if (typeCurConnection==LayoutEditor::LEVEL_XING_A)
  {
   // have a level crossing connected at A
   if (((LevelXing*)curConnection)->getLayoutBlockAC()!=layoutBlock)
   {
    // moved outside of this block
    curConnection = NULL;
   }
   else
   {
    // move to other end of this section of this level crossing track
    prevConnection = curConnection;
    curConnection = ((LevelXing*)curConnection)->getConnectC();
    typeCurConnection = LayoutEditor::TRACK;
   }
  }
  else if (typeCurConnection==LayoutEditor::LEVEL_XING_B)
  {
   // have a level crossing connected at B
   if (((LevelXing*)curConnection)->getLayoutBlockBD()!=layoutBlock)
   {
    // moved outside of this block
    curConnection = NULL;
   }
   else
   {
       // move to other end of this section of this level crossing track
    prevConnection = curConnection;
    curConnection = ((LevelXing*)curConnection)->getConnectD();
    typeCurConnection = LayoutEditor::TRACK;
   }
  }
  else if (typeCurConnection==LayoutEditor::LEVEL_XING_C)
  {
   // have a level crossing connected at C
   if (((LevelXing*)curConnection)->getLayoutBlockAC()!=layoutBlock)
   {
    // moved outside of this block
    curConnection = NULL;
   }
   else
   {
    // move to other end of this section of this level crossing track
    prevConnection = curConnection;
    curConnection = ((LevelXing*)curConnection)->getConnectA();
    typeCurConnection = LayoutEditor::TRACK;
   }
  }
  else if (typeCurConnection==LayoutEditor::LEVEL_XING_D)
  {
   // have a level crossing connected at D
   if (((LevelXing*)curConnection)->getLayoutBlockBD()!=layoutBlock)
   {
    // moved outside of this block
    curConnection = NULL;
   }
   else
   {
    // move to other end of this section of this level crossing track
    prevConnection = curConnection;
    curConnection = ((LevelXing*)curConnection)->getConnectB();
    typeCurConnection = LayoutEditor::TRACK;
   }
  }
  else if(typeCurConnection >= LayoutEditor::SLIP_A && typeCurConnection <=LayoutEditor::SLIP_D)
  {
   LayoutSlip* ls = (LayoutSlip*)curConnection;
   if (ls->getLayoutBlock()!=layoutBlock)
   {
    curConnection = NULL;
   }
   else if(ls->getSlipType()==LayoutSlip::SINGLE_SLIP)
   {
    if(typeCurConnection==LayoutEditor::SLIP_C)
    {
     bs = new BeanSetting(ls->getTurnout(), ls->getTurnoutName(), ls->getTurnoutState(LayoutSlip::STATE_AC));
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
      log->error("BadBeanError: " + ls->getName() + " " + ls->getLayoutBlock()->getDisplayName());
     }
     bs = new BeanSetting(ls->getTurnoutB(), ls->getTurnoutBName(), ls->getTurnoutBState(LayoutSlip::STATE_AC));
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
      log->error("BadBeanError: " + ls->getName() + " " + ls->getLayoutBlock()->getDisplayName());
     }
     prevConnection = curConnection;
     curConnection = ((LayoutSlip*)curConnection)->getConnectC();
     typeCurConnection = LayoutEditor::TRACK;
    }
    else if (typeCurConnection==LayoutEditor::SLIP_B)
    {
     bs = new BeanSetting(ls->getTurnout(), ls->getTurnoutName(), ls->getTurnoutState(LayoutSlip::STATE_BD));
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
      log->error("BadBeanError: " + ls->getName() + " " + ls->getLayoutBlock()->getDisplayName());
     }

     bs = new BeanSetting(ls->getTurnoutB(), ls->getTurnoutBName(), ls->getTurnoutBState(LayoutSlip::STATE_BD));
     if (bs->getBean() != NULL)
      p->addSetting(bs);
     else
     {
      static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->addBadBeanError();
      log->error("BadBeanError: " + ls->getName() + " " + ls->getLayoutBlock()->getDisplayName());
     }
     prevConnection = curConnection;
     curConnection = ((LayoutSlip*)curConnection)->getConnectB();
     typeCurConnection = LayoutEditor::TRACK;
    }
    else
    {
     //Else could be going in the slip direction
     curConnection = NULL;
    }
   }
   else
   {
    //At double slip, can not follow any further
    curConnection = NULL;
   }
  }
  else if (typeCurConnection>=50) // Turnout ray
  {
   if(log->isDebugEnabled())
       log->debug("Layout Block: " + layoutBlock->getDisplayName() + " found track type: " + typeCurConnection + " to Block: " + p->getBlock()->getDisplayName() + " Is potentially assigned to turntable ray");
   curConnection = NULL;
  }
  else
  {
   // catch when some new type got added
   log->error("Layout Block: " + layoutBlock->getDisplayName() + " found unknown track type: " + QString::number(typeCurConnection) + " to Block: " + p->getBlock()->getDisplayName());
   break;
  }
 }
}

// initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutEditorAuxTools.class.getName());
//}
