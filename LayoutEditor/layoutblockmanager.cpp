#include "layoutblockmanager.h"
//#include "runnable.h"
#include <QMessageBox>
#include "signalmast.h"
#include "layouteditor.h"
#include "signalheadmanager.h"
#include "signalmastmanager.h"
#include "abstractsignalheadmanager.h"
#include "defaultsignalmastmanager.h"
#include "turnoutsignalmast.h"
#include "virtualsignalmast.h"
#include "blockvaluefile.h"
#include "panelmenu.h"
#include "layouteditorfinditems.h"

//LayoutBlockManager* LayoutBlockManager::_instance = NULL;

LayoutBlockManager::LayoutBlockManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("LayoutBlockManager");
 setProperty("JavaClassName", "jmri.jmrit.display.layoutEditor.LayoutBlockManager");
 setProperty("InstanceManagerAutoDefault", "yes");
 blkNum = 1;
 _enableAdvancedRouting = false;
 initialized = false;
 badBeanErrors = 0;
 checking = false;
 stabilised = false;
 thr = NULL;
 namedStabilisedIndicator = NULL;
 lastRoutingChange = 0;
 lbct = new LayoutBlockConnectivityTools();
 warnConnectivity = true;
 registerSelf();
}
/**
 * Implementation of a Manager to handle LayoutBlocks
 * Note: that the same LayoutBlocks may appear in multiple LayoutEditor* panels->
 * <P>
 * This manager does not enforce any particular system naming convention.
 * <P>
 * LayoutBlocks are usually addressed by userName.  The systemName is hidden
 *    from the user for the most part.
 *
 * @author      Dave Duchamp Copyright (C) 2007
 * @version	$Revision: 22528 $
 */
///*public*/ class LayoutBlockManager extends AbstractManager implements jmri.InstanceManagerAutoDefault {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

//    /*public*/ LayoutBlockManager() {
//        super();
//    }

/*public*/ int LayoutBlockManager::getXMLOrder()const{
    return Manager::LAYOUTBLOCKS;
}


/**
 * Method to create a new LayoutBlock if the LayoutBlock does not exist
 *   Returns NULL if a LayoutBlock with the same systemName or userName
 *       already exists, or if there is trouble creating a new LayoutBlock.
 *   Note that since the userName is used to address LayoutBlocks, the
 *       user name must be present.  If the user name is not present,
 *       the new LayoutBlock is not created, and NULL is returned.
 */
/*public*/ LayoutBlock* LayoutBlockManager::createNewLayoutBlock(QString systemName, QString userName)
{
 // Check that LayoutBlock does not already exist
 LayoutBlock* result = NULL;

 if (userName == NULL || userName==(""))
 {
  log.error("Attempt to create a LayoutBlock with no user name");
  return NULL;
 }
 result = (LayoutBlock*)getByUserName(userName);
 if (result!=NULL) return NULL;
 // here if not found under user name
 QString sName = "";
 if (systemName.isEmpty())
 {
  // create a new unique system name
  bool found = true;
  while (found)
  {
   sName = "ILB"+QString("%1").arg(blkNum);
   blkNum++;
   result = (LayoutBlock*)getBySystemName(sName);
   if (result==NULL)
    found = false;
  }
 }
 else
 {
  // try the supplied system name
  result = (LayoutBlock*)getBySystemName((systemName.toUpper()));
  if (result!=NULL) return NULL;
  sName = systemName.toUpper();
 }
 // LayoutBlock does not exist, create a new LayoutBlock
 result = new LayoutBlock(sName,userName);
 // save in the maps
 Register(result);
 return result;
}

/*public*/ LayoutBlock* LayoutBlockManager::createNewLayoutBlock()
{
    bool found = true;
    while (found) {
        QString sName = "ILB"+QString("%1").arg(blkNum);
        LayoutBlock* block = (LayoutBlock*)getBySystemName(sName);
        if (block==NULL){
            found = false;
            QString uName = "AUTOBLK:"+QString("%1").arg(blkNum);
            block = new LayoutBlock(sName,uName);
            Register(block);
            return block;
        }
        blkNum++;
    }
    return NULL;
}

/**
 * Remove an existing LayoutBlock.
 */
/*public*/ void LayoutBlockManager::deleteLayoutBlock(LayoutBlock* block) {
    deregister(block);
}

/**
 * Method to get an existing LayoutBlock.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getLayoutBlock(QString name) {
    LayoutBlock* block = (LayoutBlock*)getByUserName(name);
    if (block!=NULL) return block;
    return (LayoutBlock*)getBySystemName(name);
}

/*public*/ LayoutBlock* LayoutBlockManager::getLayoutBlock(Block* block){
    foreach(NamedBean* nb, getNamedBeanSet())
    {
      if (((LayoutBlock*)nb)->getBlock() == block) return (LayoutBlock*)nb;
    }
    return nullptr;
}

/**
 * Method to find a LayoutBlock with a specified Sensor assigned as its
 *    occupancy sensor.  Returns the block or NULL if no existing LayoutBlock
 *    has the Sensor assigned.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getBlockWithSensorAssigned(Sensor* s)
{
//    java.util.Iterator<QString> iter = getSystemNameList().iterator();
//    while (iter.hasNext()) {
 QStringList systemNameList = getSystemNameList();
 foreach(QString sName, systemNameList)
 {
  //QString sName = iter.next();
  if (sName==NULL)
  {
   log.error("System name NULL during scan of LayoutBlocks");
  }
  else
  {
   LayoutBlock* block = (LayoutBlock*)getBySystemName(sName);
   if (block->getOccupancySensor() == s) return block;
  }
 }
 return NULL;
}

/**
 * Method to find a LayoutBlock with a specified Memory assigned as its
 *    value display.  Returns the block or NULL if no existing LayoutBlock
 *    has the memory assigned.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getBlockWithMemoryAssigned(Memory* m)
{
 QStringListIterator iter(getSystemNameList());
 while (iter.hasNext())
 {
  QString sName = iter.next();
  if (sName.isNull())
  {
   log.error("System name NULL during scan of LayoutBlocks");
  }
  else
  {
   LayoutBlock* block = (LayoutBlock*)getBySystemName(sName);
   if (block->getMemory() == m) return block;
  }
 }
 return NULL;
}

/**
 * Initializes/checks the Paths of all Blocks associated with LayoutBlocks.
 * <P>
 * This routine should be called when loading panels, after all Layout Editor panels have been loaded.
 */
/*public*/ void LayoutBlockManager::initializeLayoutBlockPaths()
{
 // cycle through all LayoutBlocks, completing initialization of associated jmri.Blocks
 QStringListIterator iter(getSystemNameList());
 while (iter.hasNext())
 {
  QString sName = iter.next();
  if (sName.isNull()) log.error("System name NULL during 1st initialization of LayoutBlocks");
  LayoutBlock* b = (LayoutBlock*)getBySystemName(sName);
  b->initializeLayoutBlock();
 }
 // cycle through all LayoutBlocks, updating Paths of associated jmri.Blocks
 badBeanErrors = 0;
 iter = QStringListIterator(getSystemNameList());
 while (iter.hasNext())
 {
  QString sName = iter.next();
  if (sName==NULL) log.error("System name NULL during 2nd initialization of LayoutBlocks");
  log.debug("LayoutBlock initialization - system name = "+sName);
  LayoutBlock* b = (LayoutBlock*)getBySystemName(sName);
  b->updatePaths();
  if (!b->getBlock()->getValue().isNull()) b->getBlock()->setValue(QVariant());
 }
 if (badBeanErrors>0)
 {
//        JOptionPane.showMessageDialog(NULL,""+badBeanErrors+" "+rb.getQString("Warn2"),
//                rb.getQString("WarningTitle"),JOptionPane.ERROR_MESSAGE);
     QMessageBox::warning(0, tr("Warning"), QString::number(badBeanErrors)+" "+tr("Bean Settings needed for Block operation could not be created. Check that all turnouts have been assigned."));
 }
#if 1 // TODO
 try
 {
  BlockValueFile().readBlockValues();
 }
 catch (JDOMException jde)
 {
  log.error("JDOM Exception when retreiving block values "+jde.getMessage());
 }
 catch (IOException ioe)
 {
  log.error("I/O Exception when retreiving block values "+ioe.getMessage());
 }
#endif
 // special tests for getFacingSignalHead method - comment out next three lines unless using LayoutEditorTests
//		LayoutEditorTests layoutEditorTests = new LayoutEditorTests();
//		layoutEditorTests.runClinicTests();
//		layoutEditorTests.runTestPanel3Tests();
 initialized = true;
 initializeLayoutBlockRouting();
}

/*public*/ void LayoutBlockManager::addBadBeanError() {badBeanErrors ++;}

/**
 * Method to return the Signal Head facing into a specified Block from a specified protected Block.
 * <P>
 * This method is primarily designed for use with scripts to get information initially residing in
 *    a Layout Editor panel.
 * If either of the input Blocks is NULL, or if the two blocks do not join at a block boundary, or
 *    if either of the input Blocks are not Layout Editor panel blocks,
 *	  an error message is logged, and "NULL" is returned.
 * If the signal at the block boundary has two heads--is located at the facing point of a turnout--
 *	  the Signal Head that applies for the current setting of turnout (THROWN or CLOSED) is returned.
 *    If the turnout state is UNKNOWN or INCONSISTENT, an error message is logged, and "NULL" is returned.
 * If the signal at the block boundary has three heads--the facing point of a 3-way turnout--the
 *	  Signal Head that applies for the current settings of the two turnouts of the 3-way turnout is returned.
 *	  If the turnout state of either turnout is UNKNOWN or INCONSISTENT, an error is logged and "NULL" is returned.
 * "NULL" is returned if the block boundary is between the two turnouts of a THROAT_TO_THROAT turnout or a 3-way
 *    turnout. "NULL" is returned for block boundaries exiting a THROAT_TO_THROAT turnout block, since there are
 *    no signals that apply there.
 */
/*public*/ SignalHead* LayoutBlockManager::getFacingSignalHead (Block* facingBlock, Block* protectedBlock) {
    // check input
    if ( (facingBlock == NULL) || (protectedBlock == NULL) ) {
        log.error ("NULL block in call to getFacingSignalHead");
        return NULL;
    }
    // non-NULL - check if input corresponds to Blocks in a Layout Editor panel.
    LayoutBlock* fLayoutBlock = (LayoutBlock*)getByUserName(facingBlock->getUserName());
    LayoutBlock* pLayoutBlock = (LayoutBlock*)getByUserName(protectedBlock->getUserName());
    if ( (fLayoutBlock==NULL) || (pLayoutBlock==NULL) ) {
        if (fLayoutBlock==NULL) log.error("Block "+facingBlock->getSystemName()+"is not on a Layout Editor panel.");
        if (pLayoutBlock==NULL) log.error("Block "+protectedBlock->getSystemName()+"is not on a Layout Editor panel.");
        return NULL;
    }
    // input has corresponding LayoutBlocks - does it correspond to a block boundary?
    LayoutEditor* panel = fLayoutBlock->getMaxConnectedPanel();
    QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(fLayoutBlock);
    LayoutConnectivity* lc = NULL;
    int i = 0;
    bool facingIsBlock1 = true;
    while ((i<c->size()) && (lc==NULL)) {
        LayoutConnectivity* tlc = c->at(i);
        if ( (tlc->getBlock1()==fLayoutBlock) && (tlc->getBlock2()==pLayoutBlock) ) {
            lc = tlc;
        }
        else if ( (tlc->getBlock1()==pLayoutBlock) && (tlc->getBlock2()==fLayoutBlock) ) {
            lc = tlc;
            facingIsBlock1 = false;
        }
        i ++;
    }
    if (lc==NULL) {
        log.error("Block "+facingBlock->getSystemName()+" is not connected to Block "+protectedBlock->getSystemName());
        return NULL;
    }
    // blocks are connected, get connection item types
    LayoutTurnout* lt = NULL;
    TrackSegment* tr = lc->getTrackSegment();
    int cType = 0;
    if (tr==NULL) {
        // this is an internal crossover block boundary
        lt = lc->getXover();
        cType = lc->getXoverBoundaryType();
        switch (cType) {
            case LayoutConnectivity::XOVER_BOUNDARY_AB:
                if (facingIsBlock1)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            case LayoutConnectivity::XOVER_BOUNDARY_CD:
                if (facingIsBlock1)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
            case LayoutConnectivity::XOVER_BOUNDARY_AC:
                if (facingIsBlock1) {
                    if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                        //there is no signal head for diverging (crossed over)
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                    else
                        // there is a diverging (crossed over) signal head, return it
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                }
                else {
                    if ( (lt->getSignalC2Name()==NULL) || (lt->getSignalC2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                }
            case LayoutConnectivity::XOVER_BOUNDARY_BD:
                if (facingIsBlock1) {
                    if ( (lt->getSignalB2Name()==NULL) || (lt->getSignalB2Name()==("")) )
                        //there is no signal head for diverging (crossed over)
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                    else
                        // there is a diverging (crossed over) signal head, return it
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
                }
                else {
                    if ( (lt->getSignalD2Name()==NULL) || (lt->getSignalD2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD2Name()));
                }
        }
        // should never reach here, but ...
        log.error("crossover turnout block boundary not found in getFacingSignal");
        return NULL;
    }
    // not internal crossover block boundary
    QObject* connected = lc->getConnectedObject();
    cType = lc->getConnectedType();
    if(connected==NULL){
        log.error("No connectivity object found between Blocks "+facingBlock->getSystemName()+
                                    ", "+protectedBlock->getSystemName() + " " + cType);
        return NULL;
    }
    if (cType==LayoutEditor::TRACK) {
        // block boundary is at an Anchor Point
        LayoutEditorTools* tools = new LayoutEditorTools(panel);
        PositionablePoint* p = panel->getFinder()->findPositionablePointAtTrackSegments(tr, (TrackSegment*) connected);
        bool block1IsWestEnd = tools->isAtWestEndOfAnchor(tr,p);
        if ( (block1IsWestEnd && facingIsBlock1) || (!block1IsWestEnd && !facingIsBlock1) ) {
            // block1 is on the west (north) end of the block boundary
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getEastBoundSignal()));
        }
        else {
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(p->getWestBoundSignal()));
        }
    }
    if (cType==LayoutEditor::TURNOUT_A) {
        // block boundary is at the facing point of a turnout or A connection of a crossover turnout
        lt = (LayoutTurnout*)connected;
        if (lt->getLinkType()==LayoutTurnout::NO_LINK) {
            // standard turnout or A connection of a crossover turnout
            if (facingIsBlock1) {
                if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                    //there is no signal head for diverging
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                else {
                    // check if track segments at B or C are in protected block (block 2)
                    if ( ((TrackSegment*)(lt->getConnectB()))->getBlockName()==(protectedBlock->getUserName()) ) {
                        // track segment connected at B matches block 2, check C
                        if ( !(((TrackSegment*)lt->getConnectC())->getBlockName()==(protectedBlock->getUserName())) ) {
                            // track segment connected at C is not in block2, return continuing signal head at A
                            if (lt->getContinuingSense()==Turnout::CLOSED)
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                            else
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                        }
                        else {
                            // B and C both in block2, check turnout position to decide which signal head to return
                            int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                            if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                    ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                                // continuing
                                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                            else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                    ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                                // diverging
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                            else {
                                // turnout state is UNKNOWN or INCONSISTENT
                                log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                                return NULL;
                            }
                        }
                    }
                    // track segment connected at B is not in block 2
                    if ( (((TrackSegment*)lt->getConnectC())->getBlockName()==(protectedBlock->getUserName())) ) {
                        // track segment connected at C is in block 2, return diverging signal head
                        if (lt->getContinuingSense()==Turnout::CLOSED)
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                        else
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                    }
                    else {
                        // neither track segment is in block 2 - should never get here unless layout turnout is
                        //      the only item in block 2
                        if (!(lt->getBlockName()==(protectedBlock->getUserName())))
                            log.error("neither signal at A protects block "+protectedBlock->getUserName()+
                                            ", and turnout is not in block either");
                        return NULL;
                    }
                }
            }
            else {
                // check if track segments at B or C are in facing block (block 1)
                if ( ((TrackSegment*)(lt->getConnectB()))->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at B matches block 1, check C
                    if ( !(((TrackSegment*)lt->getConnectC())->getBlockName()==(facingBlock->getUserName())) )
                        // track segment connected at C is not in block 2, return signal head at continuing end
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                    else {
                        // B and C both in block 1, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                    ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                    ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) ) {
                            // diverging, check for second head
                            if ( (lt->getSignalC2Name()==NULL) || (lt->getSignalC2Name()==("")) )
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                            else
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                        }
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                        " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at B is not in block 1
                if ( ((TrackSegment*)lt->getConnectC())->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at C is in block 1, return diverging signal head, check for second head
                    if ( (lt->getSignalC2Name()==NULL) || (lt->getSignalC2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                }
                else {
                    // neither track segment is in block 1 - should never get here unless layout turnout is
                    //    the only item in block 1
                    if (!(lt->getBlockName()==(facingBlock->getUserName())))
                        log.error("no signal faces block "+facingBlock->getUserName()+
                                            ", and turnout is not in block either");
                    return NULL;
                }
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
            //  There are no signals at the throat of a THROAT_TO_THROAT
            //  There should not be a block boundary here
            return NULL;
        }
        else if (lt->getLinkType()==LayoutTurnout::FIRST_3_WAY) {
            // 3-way turnout is in its own block - block boundary is at the throat of the 3-way turnout
            if (!facingIsBlock1) {
                // facing block is within the three-way turnout's block - no signals for exit of the block
                return NULL;
            }
            else {
                // select throat signal according to state of the 3-way turnout
                int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                if (state==Turnout::THROWN) {
                    if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                }
                else if (state==Turnout::CLOSED) {
                    LayoutTurnout* tLinked = panel->getFinder()->findLayoutTurnoutByTurnoutName(lt->getLinkedTurnoutName());
                    state = ((AbstractTurnout*)tLinked->getTurnout())->getKnownState();
                    if (state==Turnout::CLOSED) {
                        if (tLinked->getContinuingSense()==Turnout::CLOSED)
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                        else if ( (lt->getSignalA3Name()==NULL) || (lt->getSignalA3Name()==("")) )
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                        else
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA3Name()));
                    }
                    else if (state==Turnout::THROWN) {
                        if (tLinked->getContinuingSense()==Turnout::THROWN)
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                        else if ( (lt->getSignalA3Name()==NULL) || (lt->getSignalA3Name()==("")) )
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                        else
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA3Name()));
                    }
                    else {
                        // should never get here - linked turnout state is UNKNOWN or INCONSISTENT
                        log.error("Cannot choose 3-way signal head to return because turnout "+((AbstractTurnout*)tLinked->getTurnout())->
                                getSystemName()+" is in an UNKNOWN or INCONSISTENT state.");
                        return NULL;
                    }
                }
                else {
                    // should never get here - linked turnout state is UNKNOWN or INCONSISTENT
                    log.error("Cannot choose 3-way signal head to return because turnout "+((AbstractTurnout*)lt->getTurnout())->
                                getSystemName()+" is in an UNKNOWN or INCONSISTENT state.");
                    return NULL;
                }
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
            // There are no signals at the throat of the SECOND_3_WAY turnout of a 3-way turnout
            // There should not be a block boundary here
            return NULL;
        }
    }
    if (cType==LayoutEditor::TURNOUT_B) {
        // block boundary is at the continuing track of a turnout or B connection of a crossover turnout
        lt = (LayoutTurnout*)connected;
        // check for double crossover or LH crossover
        if ( ((lt->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                    (lt->getTurnoutType()==LayoutTurnout::LH_XOVER)) ) {
            if (facingIsBlock1) {
                if ( (lt->getSignalB2Name()==NULL) || (lt->getSignalB2Name()==("")) )
                // there is only one signal at B, return it
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                // check if track segments at A or D are in protected block (block 2)
                if ( ((TrackSegment*)(lt->getConnectA()))->getBlockName()==(protectedBlock->getUserName()) ) {
                    // track segment connected at A matches block 2, check D
                    if ( !(((TrackSegment*)lt->getConnectD())->getBlockName()==(protectedBlock->getUserName())) ) {
                        // track segment connected at D is not in block2, return continuing signal head at B
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                    }
                    else {
                        // A and D both in block 2, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // diverging (crossed over)
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at A is not in block 2
                if ( (((TrackSegment*)lt->getConnectD())->getBlockName()==(protectedBlock->getUserName())) )
                    // track segment connected at D is in block 2, return diverging signal head
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
                else {
                    // neither track segment is in block 2 - should never get here unless layout turnout is
                    //       only item in block 2
                    if (!(lt->getBlockName()==(protectedBlock->getUserName())))
                        log.error("neither signal at B protects block "+protectedBlock->getUserName()+
                                        ", and turnout is not in block either");
                    return NULL;
                }
            }
            else {
                // check if track segments at A or D are in facing block (block 1)
                if ( ((TrackSegment*)(lt->getConnectA()))->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at A matches block 1, check D
                    if ( !(((TrackSegment*)lt->getConnectD())->getBlockName()==(facingBlock->getUserName())) )
                        // track segment connected at D is not in block 2, return signal head at continuing end
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                    else {
                        // A and D both in block 1, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) ) {
                            // diverging, check for second head
                            if ( (lt->getSignalD2Name()==NULL) || (lt->getSignalD2Name()==("")) )
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                            else
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD2Name()));
                        }
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at A is not in block 1
                if ( ((TrackSegment*)lt->getConnectD())->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at D is in block 1, return diverging signal head, check for second head
                    if ( (lt->getSignalD2Name()==NULL) || (lt->getSignalD2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD2Name()));
                }
                else {
                    // neither track segment is in block 1 - should never get here unless layout turnout is
                    //    the only item in block 1
                    if (!(lt->getBlockName()==(facingBlock->getUserName())))
                        log.error("no signal faces block "+facingBlock->getUserName()+
                                        ", and turnout is not in block either");
                    return NULL;
                }
            }
        }
        // not double crossover or LH crossover
        if (  (lt->getLinkType()==LayoutTurnout::NO_LINK) && (lt->getContinuingSense()==Turnout::CLOSED) ) {
            if (facingIsBlock1)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
        }
        else if (lt->getLinkType()==LayoutTurnout::NO_LINK) {
            if (facingIsBlock1)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            else {
                if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
            if (!facingIsBlock1) {
                //  There are no signals at the throat of a THROAT_TO_THROAT
                return NULL;
            }
            // facing block is outside of the THROAT_TO_THROAT
            if ( (lt->getContinuingSense()==Turnout::CLOSED) && ((lt->getSignalB2Name()==NULL) ||
                                                    (lt->getSignalB2Name()==(""))) )
                // there is only one signal head here - return it
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            else if ( (lt->getContinuingSense()==Turnout::THROWN) && ((lt->getSignalC2Name()==NULL) ||
                                                    (lt->getSignalC2Name()==(""))) )
                // there is only one signal head here - return it
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            // There are two signals here get linked turnout and decide which to return from linked turnout state
            LayoutTurnout* tLinked = panel->getFinder()->findLayoutTurnoutByTurnoutName(lt->getLinkedTurnoutName());
            int state = ((AbstractTurnout*)tLinked->getTurnout())->getKnownState();
            if (state==Turnout::CLOSED) {
                if (lt->getContinuingSense()==Turnout::CLOSED)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            }
            else if (state==Turnout::THROWN) {
                if (lt->getContinuingSense()==Turnout::CLOSED)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
            }
            else
                // should never get here - linked turnout state is UNKNOWN or INCONSISTENT
                log.error("Cannot choose signal head to return because turnout "+((AbstractTurnout*)tLinked->getTurnout())->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                return NULL;
        }
        else if (lt->getLinkType()==LayoutTurnout::FIRST_3_WAY) {
            // there is no signal at the FIRST_3_WAY turnout continuing track of a 3-way turnout
            // there should not be a block boundary here
            return NULL;
        }
        else if (lt->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
            if (facingIsBlock1) {
                if (lt->getContinuingSense()==Turnout::CLOSED) {
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                }
                else {
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                }
            }
            else {
                // signal is at the linked turnout - the throat of the 3-way turnout
                LayoutTurnout* tLinked = panel->getFinder()->findLayoutTurnoutByTurnoutName(lt->getLinkedTurnoutName());
                if (lt->getContinuingSense()==Turnout::CLOSED) {
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA1Name()));
                }
                else {
                    if ( (tLinked->getSignalA3Name()==NULL) || (lt->getSignalA3Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA3Name()));
                }
            }
        }
    }
    if (cType==LayoutEditor::TURNOUT_C) {
        // block boundary is at the diverging track of a turnout or C connection of a crossover turnout
        lt = (LayoutTurnout*)connected;
        // check for double crossover or RH crossover
        if ( (lt->getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
                    (lt->getTurnoutType()==LayoutTurnout::RH_XOVER) ) {
            if (facingIsBlock1) {
                if ( (lt->getSignalC2Name()==NULL) || (lt->getSignalC2Name()==("")) )
                    // there is only one head at C, return it
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                // check if track segments at A or D are in protected block (block 2)
                if ( ((TrackSegment*)(lt->getConnectA()))->getBlockName()==(protectedBlock->getUserName()) ) {
                    // track segment connected at A matches block 2, check D
                    if ( !(((TrackSegment*)lt->getConnectD())->getBlockName()==(protectedBlock->getUserName())) ) {
                        // track segment connected at D is not in block2, return diverging signal head at C
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                    }
                    else {
                        // A and D both in block 2, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // diverging (crossed over)
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at A is not in block 2
                if ( (((TrackSegment*)lt->getConnectD())->getBlockName()==(protectedBlock->getUserName())) )
                    // track segment connected at D is in block 2, return continuing signal head
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                else {
                    // neither track segment is in block 2 - should never get here unless layout turnout is
                    //       only item in block 2
                    if (!(lt->getBlockName()==(protectedBlock->getUserName())))
                        log.error("neither signal at C protects block "+protectedBlock->getUserName()+
                                        ", and turnout is not in block either");
                    return NULL;
                }
            }
            else {
                // check if track segments at D or A are in facing block (block 1)
                if ( ((TrackSegment*)(lt->getConnectD()))->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at D matches block 1, check A
                    if ( !(((TrackSegment*)lt->getConnectA())->getBlockName()==(facingBlock->getUserName())) )
                        // track segment connected at A is not in block 2, return signal head at continuing end
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                    else {
                        // A and D both in block 1, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) ) {
                            // diverging, check for second head
                            if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                            else
                                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                        }
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at D is not in block 1
                if ( ((TrackSegment*)lt->getConnectA())->getBlockName()==(facingBlock->getUserName()) ) {
                    // track segment connected at A is in block 1, return diverging signal head, check for second head
                    if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
                }
                else {
                    // neither track segment is in block 1 - should never get here unless layout turnout is
                    //    the only item in block 1
                    if (!(lt->getBlockName()==(facingBlock->getUserName())))
                        log.error("no signal faces block "+facingBlock->getUserName()+
                                        ", and turnout is not in block either");
                    return NULL;
                }
            }
        }
        // not double crossover or RH crossover
        if ( (lt->getLinkType()==LayoutTurnout::NO_LINK) && (lt->getContinuingSense()==Turnout::CLOSED) ) {
            if (facingIsBlock1)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            else if (lt->getTurnoutType()==LayoutTurnout::LH_XOVER)
                // LH turnout - this is continuing track for D connection
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
            else {
                // RH, LH or WYE turnout, this is diverging track for A connection
                if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                    // there is no signal head at the throat for diverging
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                else
                    // there is a diverging head at the throat, return it
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::NO_LINK) {
            if (facingIsBlock1)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
        }
        else if (lt->getLinkType()==LayoutTurnout::THROAT_TO_THROAT) {
            if (!facingIsBlock1) {
                //  There are no signals at the throat of a THROAT_TO_THROAT
                return NULL;
            }
            // facing block is outside of the THROAT_TO_THROAT
            if ( (lt->getContinuingSense()==Turnout::CLOSED) && ((lt->getSignalC2Name()==NULL) ||
                                                    (lt->getSignalC2Name()==(""))) )
                // there is only one signal head here - return it
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            else if ( (lt->getContinuingSense()==Turnout::THROWN) && ((lt->getSignalB2Name()==NULL) ||
                                                    (lt->getSignalB2Name()==(""))) )
                // there is only one signal head here - return it
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            // There are two signals here get linked turnout and decide which to return from linked turnout state
            LayoutTurnout* tLinked = panel->getFinder()->findLayoutTurnoutByTurnoutName(lt->getLinkedTurnoutName());
            int state = ((AbstractTurnout*)tLinked->getTurnout())->getKnownState();
            if (state==Turnout::CLOSED) {
                if (lt->getContinuingSense()==Turnout::CLOSED)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
            }
            else if (state==Turnout::THROWN) {
                if (lt->getContinuingSense()==Turnout::CLOSED)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC2Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
            }
            else {
                // should never get here - linked turnout state is UNKNOWN or INCONSISTENT
                log.error("Cannot choose signal head to return because turnout "+tLinked->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                return NULL;
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::FIRST_3_WAY) {
            if (facingIsBlock1) {
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
            }
            else {
                if ( (lt->getSignalA2Name()==NULL) || (lt->getSignalA2Name()==("")) )
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalA2Name()));
            }
        }
        else if (lt->getLinkType()==LayoutTurnout::SECOND_3_WAY) {
            if  (facingIsBlock1) {
                if (lt->getContinuingSense()==Turnout::CLOSED) {
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                }
                else {
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                }
            }
            else {
                // signal is at the linked turnout - the throat of the 3-way turnout
                LayoutTurnout* tLinked = panel->getFinder()->findLayoutTurnoutByTurnoutName(lt->getLinkedTurnoutName());
                if (lt->getContinuingSense()==Turnout::CLOSED) {
                    if ( (tLinked->getSignalA3Name()==NULL) || (tLinked->getSignalA3Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA3Name()));
                }
                else {
                    if ( (tLinked->getSignalA2Name()==NULL) || (tLinked->getSignalA2Name()==("")) )
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA1Name()));
                    else
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(tLinked->getSignalA2Name()));
                }
            }
        }
    }
    if (cType==LayoutEditor::TURNOUT_D) {
        // block boundary is at D connectin of a crossover turnout
        lt = (LayoutTurnout*)connected;
        if (lt->getTurnoutType()==LayoutTurnout::RH_XOVER) {
            // no diverging route possible, this is continuing track for C connection
            if (facingIsBlock1)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
        }
        if (facingIsBlock1) {
            if ( (lt->getSignalD2Name()==NULL) || (lt->getSignalD2Name()==("")) )
                //there is no signal head for diverging
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
            else {
                // check if track segments at C or B are in protected block (block 2)
                if ( ((TrackSegment*)(lt->getConnectC()))->getBlockName()==(protectedBlock->getUserName()) ) {
                    // track segment connected at C matches block 2, check B
                    if ( !(((TrackSegment*)lt->getConnectB())->getBlockName()==(protectedBlock->getUserName())) ) {
                        // track segment connected at B is not in block2, return continuing signal head at D
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                    }
                    else {
                        // C and B both in block2, check turnout position to decide which signal head to return
                        int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                        if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // continuing
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD1Name()));
                        else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                            // diverging
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD2Name()));
                        else {
                            // turnout state is UNKNOWN or INCONSISTENT
                            log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                            return NULL;
                        }
                    }
                }
                // track segment connected at C is not in block 2
                if ( (((TrackSegment*)lt->getConnectB())->getBlockName()==(protectedBlock->getUserName())) )
                    // track segment connected at B is in block 2, return diverging signal head
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalD2Name()));
                else {
                    // neither track segment is in block 2 - should never get here unless layout turnout is
                    //      the only item in block 2
                    if (!(lt->getBlockName()==(protectedBlock->getUserName())))
                        log.error("neither signal at D protects block "+protectedBlock->getUserName()+
                                        ", and turnout is not in block either");
                    return NULL;
                }
            }
        }
        else {
            // check if track segments at C or B are in facing block (block 1)
            if ( ((TrackSegment*)(lt->getConnectC()))->getBlockName()==(facingBlock->getUserName()) ) {
                // track segment connected at C matches block 1, check B
                if ( !(((TrackSegment*)lt->getConnectB())->getBlockName()==(facingBlock->getUserName())) )
                    // track segment connected at B is not in block 2, return signal head at continuing end
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                else {
                    // C and B both in block 1, check turnout position to decide which signal head to return
                    int state = ((AbstractTurnout*)lt->getTurnout())->getKnownState();
                    if ( ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::THROWN) ) )
                        // continuing
                        return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalC1Name()));
                    else if ( ( (state==Turnout::THROWN) && (lt->getContinuingSense()==Turnout::CLOSED) ) ||
                                ( (state==Turnout::CLOSED) && (lt->getContinuingSense()==Turnout::THROWN) ) ) {
                        // diverging, check for second head
                        if ( (lt->getSignalB2Name()==NULL) || (lt->getSignalB2Name()==("")) )
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                        else
                            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
                    }
                    else {
                        // turnout state is UNKNOWN or INCONSISTENT
                        log.error("Cannot choose signal head because turnout "+lt->getTurnout()->getSystemName()+
                                    " is in an UNKNOWN or INCONSISTENT state.");
                        return NULL;
                    }
                }
            }
            // track segment connected at C is not in block 1
            if ( ((TrackSegment*)lt->getConnectB())->getBlockName()==(facingBlock->getUserName()) ) {
                // track segment connected at B is in block 1, return diverging signal head, check for second head
                if ( (lt->getSignalB2Name()==NULL) || (lt->getSignalB2Name()==("")) )
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB1Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(lt->getSignalB2Name()));
            }
            else {
                // neither track segment is in block 1 - should never get here unless layout turnout is
                //    the only item in block 1
                if (!(lt->getBlockName()==(facingBlock->getUserName())))
                    log.error("no signal faces block "+facingBlock->getUserName()+
                                        ", and turnout is not in block either");
                return NULL;
            }
        }
    }
    if((cType>=LayoutEditor::SLIP_A) && (cType<=LayoutEditor::SLIP_D)){
        if(!facingIsBlock1)
            return NULL;

        LayoutSlip* ls = (LayoutSlip*)connected;
        if(cType==LayoutEditor::SLIP_A){
            if(ls->getSlipState()==LayoutSlip::STATE_AD)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalA2Name()));
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalA1Name()));
        }
        if(cType==LayoutEditor::SLIP_B){
            if(ls->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                if(ls->getSlipState()==LayoutSlip::STATE_BC)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalB2Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalB1Name()));
            }
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalB1Name()));
        }
        if(cType==LayoutEditor::SLIP_C){
            if(ls->getTurnoutType()==LayoutSlip::DOUBLE_SLIP){
                if(ls->getSlipState()==LayoutSlip::STATE_BC)
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalC2Name()));
                else
                    return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalC1Name()));
            }
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalC1Name()));
        }
        if(cType==LayoutEditor::SLIP_D){
            if(ls->getSlipState()==LayoutSlip::STATE_AD)
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalD2Name()));
            else
                return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(ls->getSignalD1Name()));
        }
    }
    // block boundary must be at a level crossing
    if ( (cType<LayoutEditor::LEVEL_XING_A) || (cType>LayoutEditor::LEVEL_XING_D) ) {
        log.error(cType +  " " + connected->objectName() +" Block Boundary not identified correctly - Blocks "+facingBlock->getSystemName()+ ", "+protectedBlock->getSystemName());
        return NULL;
    }
    LevelXing* xing = (LevelXing*)connected;
    if (cType==LayoutEditor::LEVEL_XING_A) {
        // block boundary is at the A connection of a level crossing
        if (facingIsBlock1)
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalAName()));
        else
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalCName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_B) {
        // block boundary is at the B connection of a level crossing
        if (facingIsBlock1)
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalBName()));
        else
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalDName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_C) {
        // block boundary is at the C connection of a level crossing
        if (facingIsBlock1)
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalCName()));
        else
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalAName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_D) {
        // block boundary is at the D connection of a level crossing
        if (facingIsBlock1)
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalDName()));
        else
            return (((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(xing->getSignalBName()));
    }
    return NULL;
}
///*private*/ LayoutTurnout* LayoutBlockManager::getLayoutTurnoutFromTurnoutName(QString turnoutName,LayoutEditor* panel) {
//    Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(turnoutName);
//    if (t==NULL) return NULL;
//    LayoutTurnout* lt = NULL;
//    for (int i=0; i<panel->turnoutList->size(); i++) {
//        lt = panel->turnoutList->at(i);
//        if (lt->getTurnout()==t) return lt;
//    }
//    return NULL;
//}

/**
 * Method to return the named bean of either a Sensor or signalmast facing into a specified Block from a specified protected Block.
 * <P>
 * @param facingBlock
 * @param panel
 * @return The assigned sensor or signal mast as a named bean
 */
//@CheckReturnValue
//@CheckForNull
/*public*/ NamedBean* LayoutBlockManager::getNamedBeanAtEndBumper(
        /*@CheckForNull*/ Block* facingBlock,
        /*@CheckForNull*/ LayoutEditor* panel)
{
 NamedBean* bean = getSignalMastAtEndBumper(facingBlock, panel);
 if(bean != nullptr)
     return bean;
 else return getSensorAtEndBumper(facingBlock, panel);
}

/**
 * Method to return a Signal Mast that is assigned to a block which has an
 * end bumper at one end.
*/
/*public*/ SignalMast* LayoutBlockManager::getSignalMastAtEndBumper(Block* facingBlock, LayoutEditor* panel){
    if (facingBlock==NULL){
        log.error ("NULL block in call to getFacingSignalMast");
        return NULL;
    }
    LayoutBlock* fLayoutBlock = (LayoutBlock*)getByUserName(facingBlock->getUserName());
    if (fLayoutBlock==NULL){
        log.error("Block "+facingBlock->getSystemName()+"is not on a Layout Editor panel.");
        return NULL;
    }
    if(panel==NULL)
        panel = fLayoutBlock->getMaxConnectedPanel();

    for (TrackSegment* t : panel->getTrackSegments()) {
        if(t->getLayoutBlock()==fLayoutBlock){
            PositionablePoint* p = NULL;
            if(t->getType1()==LayoutEditor::POS_POINT){
                p = (PositionablePoint*) t->getConnect1();
                    if(p->getType()==PositionablePoint::END_BUMPER){
                        if(p->getEastBoundSignalMastName()!=(""))
                            return ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getEastBoundSignalMastName());
                        if(p->getWestBoundSignalMastName()!=(""))
                            return ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getWestBoundSignalMastName());
                    }

            }
            if (t->getType2()==LayoutEditor::POS_POINT){
                p = (PositionablePoint*) t->getConnect2();
                    if(p->getType()==PositionablePoint::END_BUMPER){
                        if(p->getEastBoundSignalMastName()!=(""))
                            return ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getEastBoundSignalMastName());
                        if(p->getWestBoundSignalMastName()!=(""))
                            return ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(p->getWestBoundSignalMastName());
                    }
            }
        }
    }
    return NULL;
}

/**
 * Method to return a Sensor facing into a specific Block.
 * This is used for blocks that have an end bumper at one end
*/
/*public*/ Sensor* LayoutBlockManager::getSensorAtEndBumper(Block* facingBlock, LayoutEditor* panel)
{
 if (facingBlock==NULL)
 {
  log.error ("NULL block in call to getFacingSensor");
  return NULL;
 }
 LayoutBlock* fLayoutBlock = (LayoutBlock*)getByUserName(facingBlock->getUserName());
 if (fLayoutBlock==NULL)
 {
  log.error("Block "+facingBlock->getSystemName()+"is not on a Layout Editor panel.");
  return NULL;
 }
 if(panel==NULL)
  panel = fLayoutBlock->getMaxConnectedPanel();
 for (TrackSegment* t : panel->getTrackSegments())
 {
  if(t->getLayoutBlock()==fLayoutBlock)
  {
   PositionablePoint* p = NULL;
   if(t->getType1()==LayoutEditor::POS_POINT)
   {
    p = (PositionablePoint*) t->getConnect1();
    if(p->getType()==PositionablePoint::END_BUMPER)
    {
     if(p->getEastBoundSensorName()!=(""))
      return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getEastBoundSensorName());
     if(p->getWestBoundSensorName()!=(""))
      return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getWestBoundSensorName());
    }

   }
   if (t->getType2()==LayoutEditor::POS_POINT)
   {
    p = (PositionablePoint*) t->getConnect2();
    if(p->getType()==PositionablePoint::END_BUMPER)
    {
     if(p->getEastBoundSensorName()!=(""))
      return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getEastBoundSensorName());
     if(p->getWestBoundSensorName()!=(""))
      return ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getWestBoundSensorName());
    }
   }
  }
 }
 return NULL;
}

/**
 * Method to return the named bean of either a Sensor or signalmast facing into a specified Block from a specified protected Block.
 * <P>
 * @param facingBlock
 * @param protectedBlock
 * @return The assigned sensor or signal mast as a named bean
 */
/*public*/ NamedBean* LayoutBlockManager::getFacingNamedBean(Block* facingBlock, Block* protectedBlock, LayoutEditor* panel){
    NamedBean* bean = getFacingSignalMast(facingBlock, protectedBlock, panel);
    if(bean!=NULL)
        return bean;
    else return getFacingSensor(facingBlock, protectedBlock, panel);
}

/*public*/ SignalMast* LayoutBlockManager::getFacingSignalMast(Block* facingBlock, Block* protectedBlock){
    return getFacingSignalMast(facingBlock, protectedBlock, NULL);
}

/**
 * Method to return the Signal Mast facing into a specified Block from a specified protected Block.
 * <P>
 * @param facingBlock
 * @param protectedBlock
 * @return The assigned signalMast.
 */
/*public*/ SignalMast* LayoutBlockManager::getFacingSignalMast(Block* facingBlock, Block* protectedBlock, LayoutEditor* panel){
    // check input
    if ( (facingBlock == NULL) || (protectedBlock == NULL) ) {
        log.error ("NULL block in call to getFacingSignalMast");
        return NULL;
    }
    // non-NULL - check if input corresponds to Blocks in a Layout Editor panel.
    LayoutBlock* fLayoutBlock = (LayoutBlock*)getByUserName(facingBlock->getUserName());
    LayoutBlock* pLayoutBlock = (LayoutBlock*)getByUserName(protectedBlock->getUserName());
    if ( (fLayoutBlock==NULL) || (pLayoutBlock==NULL) ) {
        if (fLayoutBlock==NULL) log.error("Block "+facingBlock->getSystemName()+" is not on a Layout Editor panel.");
        if (pLayoutBlock==NULL) log.error("Block "+protectedBlock->getSystemName()+" is not on a Layout Editor panel.");
        return NULL;
    }
    // input has corresponding LayoutBlocks - does it correspond to a block boundary?
    if(panel==NULL){
        panel = fLayoutBlock->getMaxConnectedPanel();
    }
    QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(fLayoutBlock);
    LayoutConnectivity* lc = NULL;
    int i = 0;
    bool facingIsBlock1 = true;
    while ((i<c->size()) && (lc==NULL)) {
        LayoutConnectivity* tlc = c->at(i);
        if ( (tlc->getBlock1()==fLayoutBlock) && (tlc->getBlock2()==pLayoutBlock) ) {
            lc = tlc;
        }
        else if ( (tlc->getBlock1()==pLayoutBlock) && (tlc->getBlock2()==fLayoutBlock) ) {
            lc = tlc;
            facingIsBlock1 = false;
        }
        i ++;
    }
    if (lc==NULL) {
        log.error("Block "+facingBlock->getSystemName()+" is not connected to Block "+protectedBlock->getSystemName());
        return NULL;
    }
    LayoutTurnout* lt = NULL;
    QObject* connected = lc->getConnectedObject();

    TrackSegment* tr = lc->getTrackSegment();
    int cType = lc->getConnectedType();
    if(connected==NULL){
        if(lc->getXover()!=NULL){
            if(lc->getXoverBoundaryType()==LayoutConnectivity::XOVER_BOUNDARY_AB) {
                if(fLayoutBlock==lc->getXover()->getLayoutBlock()){
                    cType=LayoutEditor::TURNOUT_A;
                } else {
                    cType=LayoutEditor::TURNOUT_B;
                }
                connected = lc->getXover();
            }
            else if(lc->getXoverBoundaryType()==LayoutConnectivity::XOVER_BOUNDARY_CD){
                if(fLayoutBlock==lc->getXover()->getLayoutBlockC()){
                    cType=LayoutEditor::TURNOUT_C;
                } else {
                    cType=LayoutEditor::TURNOUT_D;
                }
                connected = lc->getXover();
            }
        }
    }
    if (connected == NULL) {
        log.error("No connectivity object found between Blocks "+facingBlock->getSystemName()+
                                    ", "+protectedBlock->getSystemName()  + " " + cType);
        return NULL;
    }
    if (cType==LayoutEditor::TRACK) {
        // block boundary is at an Anchor Point
        LayoutEditorTools* tools = new LayoutEditorTools(panel);
        PositionablePoint* p = panel->getFinder()->findPositionablePointAtTrackSegments(tr, (TrackSegment*) connected);
        bool block1IsWestEnd = tools->isAtWestEndOfAnchor(tr,p);
        if ( (block1IsWestEnd && facingIsBlock1) || (!block1IsWestEnd && !facingIsBlock1) ) {
            // block1 is on the west (north) end of the block boundary
            return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(p->getEastBoundSignalMastName()));
        }
        else {
            return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(p->getWestBoundSignalMastName()));
        }
    }
    if(!facingIsBlock1)
        return NULL;
    if (cType==LayoutEditor::TURNOUT_A) {
        lt = (LayoutTurnout*)connected;
        if ((lt->getLinkType()==LayoutTurnout::NO_LINK) || (lt->getLinkType()==LayoutTurnout::FIRST_3_WAY)){
            if ( (lt->getSignalAMast()!=NULL) || (lt->getSignalAMastName()!=("")) ){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(lt->getSignalAMastName()));
            }
            // we only allow signal masts inbound to the turnout.
            return NULL;
        }
        else {
            return NULL;
        }
    }

    if (cType==LayoutEditor::TURNOUT_B) {
        lt = (LayoutTurnout*)connected;
        if ( (lt->getSignalBMast()!=NULL) || (lt->getSignalBMastName()!=("")) ){
            return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(lt->getSignalBMastName()));
        }
        return NULL;
    }
    if (cType==LayoutEditor::TURNOUT_C) {
        lt = (LayoutTurnout*)connected;
        if ( (lt->getSignalCMast()!=NULL) || (lt->getSignalCMastName()!=("")) ){
            return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(lt->getSignalCMastName()));
        }
        return NULL;
    }

    if (cType==LayoutEditor::TURNOUT_D) {
        lt = (LayoutTurnout*)connected;
            if ( (lt->getSignalDMast()!=NULL) || (lt->getSignalDMastName()!=("")) ){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(lt->getSignalDMastName()));
            }
        return NULL;
    }

    if((cType>=LayoutEditor::SLIP_A) && (cType<=LayoutEditor::SLIP_D)){
        LayoutSlip* ls = (LayoutSlip*)connected;
        if(cType==LayoutEditor::SLIP_A){
            if((ls->getSignalAMast()!=NULL) || (ls->getSignalAMastName()!=(""))){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(ls->getSignalAMastName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_B){
            if((ls->getSignalBMast()!=NULL) || (ls->getSignalBMastName()!=(""))){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(ls->getSignalBMastName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_C){
            if((ls->getSignalCMast()!=NULL) || (ls->getSignalCMastName()!=(""))){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(ls->getSignalCMastName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_D){
            if((ls->getSignalDMast()!=NULL) || (ls->getSignalDMastName()!=(""))){
                return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(ls->getSignalDMastName()));
            }
            return NULL;
        }
    }

    if ( (cType<LayoutEditor::LEVEL_XING_A) || (cType>LayoutEditor::LEVEL_XING_D) ) {
        log.error("Block Boundary not identified correctly - Blocks "+facingBlock->getSystemName()+
                                    ", "+protectedBlock->getSystemName());
        return NULL;
    }
    /*We don't allow signal masts on the block outward facing from the level
    xing, nor do we consider the signal mast, that is protecting the in block on the xing*/
    LevelXing* xing = (LevelXing*)connected;
    if (cType==LayoutEditor::LEVEL_XING_A) {
        // block boundary is at the A connection of a level crossing
        return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(xing->getSignalAMastName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_B) {
         // block boundary is at the B connection of a level crossing
        return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(xing->getSignalBMastName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_C) {
        // block boundary is at the C connection of a level crossing
        return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(xing->getSignalCMastName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_D) {
        // block boundary is at the D connection of a level crossing
        return (((DefaultSignalMastManager*)((SignalMastManager*)InstanceManager::getDefault("SignalMastManager")))->getSignalMast(xing->getSignalDMastName()));
    }
    return NULL;
}

/**
 * Method to return the Sensor facing into a specified Block from a specified protected Block.
 * <P>
 * @param facingBlock
 * @param protectedBlock
 * @return The assigned sensor.
 */
/*public*/ Sensor* LayoutBlockManager::getFacingSensor (Block* facingBlock, Block* protectedBlock, LayoutEditor* panel){
    // check input
    if ( (facingBlock == NULL) || (protectedBlock == NULL) ) {
        log.error ("NULL block in call to getFacingSignal");
        return NULL;
    }
    // non-NULL - check if input corresponds to Blocks in a Layout Editor panel.
    LayoutBlock* fLayoutBlock = (LayoutBlock*)getByUserName(facingBlock->getUserName());
    LayoutBlock* pLayoutBlock = (LayoutBlock*)getByUserName(protectedBlock->getUserName());
    if ( (fLayoutBlock==NULL) || (pLayoutBlock==NULL) ) {
        if (fLayoutBlock==NULL) log.error("Block "+facingBlock->getSystemName()+"is not on a Layout Editor panel.");
        if (pLayoutBlock==NULL) log.error("Block "+protectedBlock->getSystemName()+"is not on a Layout Editor panel.");
        return NULL;
    }
    // input has corresponding LayoutBlocks - does it correspond to a block boundary?
    if(panel==NULL){
        panel = fLayoutBlock->getMaxConnectedPanel();
    }
    QVector<LayoutConnectivity*>* c = panel->auxTools->getConnectivityList(fLayoutBlock);
    LayoutConnectivity* lc = NULL;
    int i = 0;
    bool facingIsBlock1 = true;
    while ((i<c->size()) && (lc==NULL)) {
        LayoutConnectivity* tlc = c->at(i);
        if ( (tlc->getBlock1()==fLayoutBlock) && (tlc->getBlock2()==pLayoutBlock) ) {
            lc = tlc;
        }
        else if ( (tlc->getBlock1()==pLayoutBlock) && (tlc->getBlock2()==fLayoutBlock) ) {
            lc = tlc;
            facingIsBlock1 = false;
        }
        i ++;
    }
    if (lc==NULL) {
        log.error("Block "+facingBlock->getSystemName()+" is not connected to Block "+protectedBlock->getSystemName());
        return NULL;
    }
    LayoutTurnout* lt = NULL;
    QObject* connected = lc->getConnectedObject();
    TrackSegment* tr = lc->getTrackSegment();
    int cType = lc->getConnectedType();
    if(connected==NULL){
        if(lc->getXover()!=NULL){
            if(lc->getXoverBoundaryType()==LayoutConnectivity::XOVER_BOUNDARY_AB) {
                if(fLayoutBlock==lc->getXover()->getLayoutBlock()){
                    cType=LayoutEditor::TURNOUT_A;
                } else {
                    cType=LayoutEditor::TURNOUT_B;
                }
                connected = lc->getXover();
            }
            else if(lc->getXoverBoundaryType()==LayoutConnectivity::XOVER_BOUNDARY_CD){
                if(fLayoutBlock==lc->getXover()->getLayoutBlockC()){
                    cType=LayoutEditor::TURNOUT_C;
                } else {
                    cType=LayoutEditor::TURNOUT_D;
                }
                connected = lc->getXover();
            }
        }
    }
    if(connected==NULL){
        log.error("No connectivity object found between Blocks "+facingBlock->getSystemName()+
                                    ", "+protectedBlock->getSystemName()  + " " + cType);
        return NULL;
    }

    if (cType==LayoutEditor::TRACK) {
        // block boundary is at an Anchor Point
        LayoutEditorTools* tools = new LayoutEditorTools(panel);
        PositionablePoint* p = panel->getFinder()->findPositionablePointAtTrackSegments(tr, (TrackSegment*) connected);
        bool block1IsWestEnd = tools->isAtWestEndOfAnchor(tr,p);
        if ( (block1IsWestEnd && facingIsBlock1) || (!block1IsWestEnd && !facingIsBlock1) ) {
            // block1 is on the west (north) end of the block boundary
            return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getEastBoundSensorName()));
        }
        else {
            return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(p->getWestBoundSensorName()));
        }
    }
    if(!facingIsBlock1)
        return NULL;
    if (cType==LayoutEditor::TURNOUT_A) {
        lt = (LayoutTurnout*)connected;
        if ((lt->getLinkType()==LayoutTurnout::NO_LINK) || (lt->getLinkType()==LayoutTurnout::FIRST_3_WAY)){
            if ( (lt->getSensorA()!=NULL) || (lt->getSensorAName()!=("")) ){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(lt->getSensorAName()));
            }
            // we only allow signal s inbound to the turnout.
            return NULL;
        }
        else {
            return NULL;
        }
    }

    if (cType==LayoutEditor::TURNOUT_B) {
        lt = (LayoutTurnout*)connected;
        if ( (lt->getSensorB()!=NULL) || (lt->getSensorBName()!=("")) ){
            return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(lt->getSensorBName()));
        }
        return NULL;
    }
    if (cType==LayoutEditor::TURNOUT_C) {
        lt = (LayoutTurnout*)connected;
        if ( (lt->getSensorC()!=NULL) || (lt->getSensorCName()!=("")) ){
            return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(lt->getSensorCName()));
        }
        return NULL;
    }

    if (cType==LayoutEditor::TURNOUT_D) {
        lt = (LayoutTurnout*)connected;
            if ( (lt->getSensorD()!=NULL) || (lt->getSensorDName()!=("")) ){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(lt->getSensorDName()));
            }
        return NULL;
    }
    if((cType>=LayoutEditor::SLIP_A) && (cType<=LayoutEditor::SLIP_D)){
        LayoutSlip* ls = (LayoutSlip*)connected;
        if(cType==LayoutEditor::SLIP_A){
            if((ls->getSensorA()!=NULL) || (ls->getSensorAName()!=(""))){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(ls->getSensorAName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_B){
            if((ls->getSensorB()!=NULL) || (ls->getSensorBName()!=(""))){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(ls->getSensorBName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_C){
            if((ls->getSensorC()!=NULL) || (ls->getSensorCName()!=(""))){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(ls->getSensorCName()));
            }
            return NULL;
        }
        if(cType==LayoutEditor::SLIP_D){
            if((ls->getSensorD()!=NULL) || (ls->getSensorDName()!=(""))){
                return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(ls->getSensorDName()));
            }
            return NULL;
        }
    }
    if ( (cType<LayoutEditor::LEVEL_XING_A) || (cType>LayoutEditor::LEVEL_XING_D) ) {
        log.error(QString::number(cType) +  " " + connected->objectName() +" Block Boundary not identified correctly - Blocks "+facingBlock->getSystemName()+
                                    ", "+protectedBlock->getSystemName());
        return NULL;
    }
    /*We don't allow signal s on the block outward facing from the level
    xing, nor do we consider the signal , that is protecting the in block on the xing*/
    LevelXing* xing = (LevelXing*)connected;
    if (cType==LayoutEditor::LEVEL_XING_A) {
        // block boundary is at the A connection of a level crossing
        return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(xing->getSensorAName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_B) {
         // block boundary is at the B connection of a level crossing
        return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(xing->getSensorBName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_C) {
        // block boundary is at the C connection of a level crossing
        return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(xing->getSensorCName()));
    }
    if (cType==LayoutEditor::LEVEL_XING_D) {
        // block boundary is at the D connection of a level crossing
        return (((AbstractSensorManager*)InstanceManager::sensorManagerInstance())->getSensor(xing->getSensorDName()));
    }
    return NULL;
}

/**
 * Returns in the first instance a Signal Mast or if none exists a Signal Head
 * for a given facing block and protected block combination.
 * see getFacingSignalMast and getFacingSignalHead as to how they deal with
 * what they each return.
 * <p>
 * @param facingBlock
 * @param protectedBlock
 * @return either a signalMast or signalHead
 */
/*public*/ QObject* LayoutBlockManager::getFacingSignalObject(Block* facingBlock, Block* protectedBlock){
    QObject* sig = getFacingSignalMast(facingBlock, protectedBlock, NULL);
    if (sig!=NULL)
        return sig;
    sig = getFacingSignalHead(facingBlock, protectedBlock);
    return sig;
}


 /**
 * Method to return the block that a given bean object (Sensor, SignalMast or SignalHead) is protecting
 * <P>
 * @param nb NamedBean
 * @param panel - panel that this bean is on
 * @return The block that the bean object is facing
 */
/*public*/ LayoutBlock* LayoutBlockManager::getProtectedBlockByNamedBean(
        /*@CheckForNull*/ NamedBean*nb,
        /*@CheckForNull*/ LayoutEditor* panel)
{
 if(nb == nullptr)
  throw NullPointerException("nb is marked @nonnull but is null");
 if(panel == nullptr)
  throw NullPointerException("panel is marked @nonnull but is null");

 if (qobject_cast<SignalHead*>(nb)) {
     return getProtectedBlock((SignalHead*) nb, panel);
 }
 QList<LayoutBlock*> proBlocks = getProtectingBlocksByBean(nb, panel);

 if (proBlocks.isEmpty()) {
     return nullptr;
 }
 return proBlocks.at(0);
}	//getProtectedBlockByNamedBean

//@CheckReturnValue
//@Nullable
/*public*/ QList<LayoutBlock*> LayoutBlockManager::getProtectingBlocksByNamedBean(
        /*@CheckForNull*/ NamedBean* nb,
        /*@CheckForNull*/ LayoutEditor* panel) {
 if(nb == nullptr)
  throw NullPointerException("nb is marked @nonnull but is null");
// if(panel == nullptr)
//  throw NullPointerException("panel is marked @nonnull but is null");

 QList<LayoutBlock*> ret = QList<LayoutBlock*>();

 //if (nb instanceof SignalHead)
 if(qobject_cast<SignalHead*>(nb))
 {
  ret.append(getProtectedBlock((SignalHead*) nb, panel));
  return ret;
 }
 return getProtectingBlocksByBean(nb, panel);
}

/**
 * If the panel variable is null, search all LE panels.
 * This was added to support multi panel entry/exit.
 * <p>
 * @param bean  The sensor, mast or head to be located.
 * @param panel The panel to search. If null, search all LE panels.
 * @return a list of protected layout blocks.
 */
//@Nonnull
/*private*/ QList<LayoutBlock*> LayoutBlockManager::getProtectingBlocksByBean(
        /*@CheckForNull*/ NamedBean* bean,
        /*@CheckForNull*/ LayoutEditor* panel)
{
 if(bean == nullptr)
  throw NullPointerException("bean is marked @nonnull but is null");
// if(panel == nullptr)
//  throw NullPointerException("panel is marked @nonnull but is null");

 if (panel == nullptr)
 {
  QList<LayoutEditor*>* panels = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->
          getLayoutEditorPanelList();
  QList<LayoutBlock*> protectingBlocks = QList<LayoutBlock*>();
  for (LayoutEditor* p : *panels)
  {
   protectingBlocks = getProtectingBlocksByBeanByPanel(bean, p);
   if (!protectingBlocks.isEmpty()) {
       break;
   }
  }
  return protectingBlocks;
 }
 else {
     return getProtectingBlocksByBeanByPanel(bean, panel);
 }
}
//@Nonnull
/*private*/ QList<LayoutBlock*> LayoutBlockManager::getProtectingBlocksByBeanByPanel(
        /*@CheckForNull*/ NamedBean* bean,
        /*@CheckForNull*/ LayoutEditor* panel)
{
 if(bean == nullptr)
  throw NullPointerException("bean is marked @nonnull but is null");
 if(panel == nullptr)
  throw NullPointerException("panel is marked @nonnull but is null");

 QList<LayoutBlock*> protectingBlocks = QList<LayoutBlock*>();

 //if (!(bean instanceof SignalMast) && !(bean instanceof Sensor))
 if(qobject_cast<SignalMast*>(bean) == nullptr && qobject_cast<Sensor*>(bean)== nullptr)
 {
  log.error("Incorrect class type called, must be either SignalMast or Sensor");
  return protectingBlocks;
 }

 PositionablePoint* pp = panel->getFinder()->findPositionablePointByEastBoundBean(bean);
 TrackSegment* tr = nullptr;
 bool east = true;

 if (pp == nullptr) {
     pp = panel->getFinder()->findPositionablePointByWestBoundBean(bean);
     east = false;
 }

 if (pp != nullptr)
 {
//            LayoutEditorTools tools = panel.getLETools(); //TODO: Dead-code strip this

  if (east)
  {
   if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
       tr = pp->getConnect2();
   } else {
       tr = pp->getConnect1();
   }
  }
  else {
   if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
       tr = pp->getConnect1();
   } else {
       tr = pp->getConnect2();
   }
  }

  if (tr != nullptr)
  {
   protectingBlocks.append(tr->getLayoutBlock());

   return protectingBlocks;
  }
 }

 LevelXing* l = panel->getFinder()->findLevelXingByBean(bean);

 if (l != nullptr)
 {
     //if (bean instanceof SignalMast)
  if(qobject_cast<SignalMast*>(bean))
  {
      if (l->getSignalAMast() == bean) {
          protectingBlocks.append(l->getLayoutBlockAC());
      } else if (l->getSignalBMast() == bean) {
          protectingBlocks.append(l->getLayoutBlockBD());
      } else if (l->getSignalCMast() == bean) {
          protectingBlocks.append(l->getLayoutBlockAC());
      } else {
          protectingBlocks.append(l->getLayoutBlockBD());
      }
  }
  //else if (bean instanceof Sensor)
  else if(qobject_cast<Sensor*>(bean))
  {
      if (l->getSensorA() == bean) {
          protectingBlocks.append(l->getLayoutBlockAC());
      } else if (l->getSensorB() == bean) {
          protectingBlocks.append(l->getLayoutBlockBD());
      } else if (l->getSensorC() == bean) {
          protectingBlocks.append(l->getLayoutBlockAC());
      } else {
          protectingBlocks.append(l->getLayoutBlockBD());
      }
  }
  return protectingBlocks;
 }

 LayoutSlip* ls = panel->getFinder()->findLayoutSlipByBean(bean);

 if (ls != nullptr)
 {
  protectingBlocks.append(ls->getLayoutBlock());

  return protectingBlocks;
 }

 LayoutTurnout* t = panel->getFinder()->findLayoutTurnoutByBean(bean);

 if (t != nullptr) {
     return t->getProtectedBlocks(bean);
 }
 return protectingBlocks;
}	//getProtectingBlocksByBean


/**
 * Method to return the LayoutBlock that a given signal is protecting.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getProtectedBlockByMast(SignalMast* signalMast, LayoutEditor* panel){
 QList<LayoutBlock*> proBlocks = getProtectingBlocksByBean(signalMast, panel);

 if (proBlocks.isEmpty()) {
     return nullptr;
 }
 return proBlocks.at(0);
}

/**
 * Get the LayoutBlock that a given sensor is protecting.
 */
//@CheckReturnValue
//@CheckForNull
/*public*/ LayoutBlock* LayoutBlockManager::getProtectedBlockBySensor(
        /*@CheckForNull*/ Sensor* sensor, /*@CheckForNull*/ LayoutEditor* panel)
{
 if(sensor == nullptr)
  throw NullPointerException("sensor is marked @nonnull but is null");
 if(panel == nullptr)
  throw NullPointerException("panel is marked @nonnull but is null");

 QList<LayoutBlock*> proBlocks = getProtectingBlocksByBean(sensor, panel);

 if (proBlocks.isEmpty()) {
     return nullptr;
 }
 return proBlocks.at(0);
}

//@Nonnull
/*public*/ QList<LayoutBlock*> LayoutBlockManager::getProtectingBlocksBySensor(
        /*@CheckForNull*/ Sensor* sensor, /*@CheckForNull*/ LayoutEditor* panel)
{
 if(sensor == nullptr)
  throw NullPointerException("sensor is marked @nonnull but is null");
 if(panel == nullptr)
  throw NullPointerException("panel is marked @nonnull but is null");

 return getProtectingBlocksByBean(sensor, panel);
}

//@Nonnull
/*public*/ QList<LayoutBlock*> LayoutBlockManager::getProtectingBlocksBySensorOld(
        /*@CheckForNull*/ Sensor* sensor, /*@Nonnull*/ LayoutEditor* panel) {
    QList<LayoutBlock*> result = QList<LayoutBlock*>();
    PositionablePoint* pp = panel->getFinder()->findPositionablePointByEastBoundBean(sensor);
    TrackSegment* tr;
    bool east = true;

    if (pp == nullptr) {
        pp = panel->getFinder()->findPositionablePointByWestBoundBean(sensor);
        east = false;
    }

    if (pp != nullptr) {
        //            LayoutEditorTools tools = panel.getLETools(); //TODO: Dead-code strip this

        if (east) {
            if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
                tr = pp->getConnect2();
            } else {
                tr = pp->getConnect1();
            }
        } else {
            if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
                tr = pp->getConnect1();
            } else {
                tr = pp->getConnect2();
            }
        }

        if (tr != nullptr) {
            result.append(tr->getLayoutBlock());

            return result;
        }
    }

    LevelXing* l = panel->getFinder()->findLevelXingByBean(sensor);

    if (l != nullptr) {
        if (l->getSensorA() == sensor) {
            result.append(l->getLayoutBlockAC());
        } else if (l->getSensorB() == sensor) {
            result.append(l->getLayoutBlockBD());
        } else if (l->getSensorC() == sensor) {
            result.append(l->getLayoutBlockAC());
        } else {
            result.append(l->getLayoutBlockBD());
        }
        return result;
    }
    LayoutSlip* ls = panel->getFinder()->findLayoutSlipByBean(sensor);

    if (ls != nullptr) {
        result.append(ls->getLayoutBlock());

        return result;
    }
    LayoutTurnout* t = panel->getFinder()->findLayoutTurnoutByBean(sensor);

    if (t != nullptr) {
        return t->getProtectedBlocks(sensor);
    }
    return result;
}	//getProtectingBlocksBySensorOld

/**
 * Method to return the block facing a given bean object (Sensor, SignalMast or SignalHead).
 * <P>
 * @param nb NamedBean
 * @param panel - panel that this bean is on
 * @return The block that the bean object is facing
 */
/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlockByNamedBean(NamedBean* nb, LayoutEditor* panel){
    if(qobject_cast<TurnoutSignalMast*>(nb)!= NULL){
        return getFacingBlockByMast((SignalMast*)nb, panel);
    }
    if(qobject_cast<VirtualSignalMast*>(nb)!= NULL){
        return getFacingBlockByMast((SignalMast*)nb, panel);
    }
    if(qobject_cast<SignalMast*>(nb)!= NULL){
        return getFacingBlockByMast((SignalMast*)nb, panel);
    }
    if(qobject_cast<SignalHead*>(nb)!= NULL){
        return getFacingBlock((SignalHead*)nb, panel);
    }
    if(qobject_cast<Sensor*>(nb)!= NULL){
        return getFacingBlockBySensor((Sensor*)nb, panel);
    }
    return NULL;
}

/**
 * Method to return the LayoutBlock that a given sensor is facing.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlockBySensor(QString sensorName, LayoutEditor* panel){
 Sensor* sensor = InstanceManager::sensorManagerInstance()->getSensor(sensorName);
 return (sensor == nullptr) ? nullptr : getFacingBlockBySensor(sensor, panel);

}

/**
 * Method to return the LayoutBlock that a given signal is facing.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlockByMast(SignalMast* signalMast, LayoutEditor* panel)
{
 return getFacingBlockByBean(signalMast, panel);
}

/**
 * If the panel variable is null, search all LE panels.
 * This was added to support multi panel entry/exit.
 * @param bean  The sensor, mast or head to be located.
 * @param panel The panel to search. Search all LE panels if null.
 * @return the facing layout block.
 */
//@CheckReturnValue
//@Nullable
/*private*/ LayoutBlock* LayoutBlockManager::getFacingBlockByBean(
        /*@Nonnull*/ NamedBean* bean,
        LayoutEditor* panel)
{
 if(bean == nullptr)
  throw NullPointerException("bean is marked @Nonnull but is null");

 if (panel == nullptr)
 {
  QList<LayoutEditor*>* panels = static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->
          getLayoutEditorPanelList();
  LayoutBlock* returnBlock = nullptr;
  for (LayoutEditor* p : *panels)
  {
   returnBlock = getFacingBlockByBeanByPanel(bean, p);
   if (returnBlock != nullptr) {
       break;
   }
  }
  return returnBlock;
 } else {
     return getFacingBlockByBeanByPanel(bean, panel);
 }
}
//@CheckReturnValue
//@Nullable
/*private*/ LayoutBlock* LayoutBlockManager::getFacingBlockByBeanByPanel(
        /*@Nonnull*/ NamedBean* bean,
        /*@Nonnull */LayoutEditor* panel) {
    PositionablePoint* pp = panel->getFinder()->findPositionablePointByEastBoundBean(bean);
    TrackSegment* tr = nullptr;
    bool east = true;

    //Don't think that the logic for this is the right way round
    if (pp == nullptr) {
        pp = panel->getFinder()->findPositionablePointByWestBoundBean(bean);
        east = false;
    }

    if (pp != nullptr) {
//            LayoutEditorTools tools = panel.getLETools(); //TODO: Dead-code strip this

        if (east) {
            if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
                tr = pp->getConnect1();
            } else {
                tr = pp->getConnect2();
            }
        } else {
            if (LayoutEditorTools::isAtWestEndOfAnchor(pp->getConnect1(), pp)) {
                tr = pp->getConnect2();
            } else {
                tr = pp->getConnect1();
            }
        }

        if (tr != nullptr) {
            log.debug("found facing block by positionable point");

            return tr->getLayoutBlock();
        }
    }
    LayoutTurnout* t = panel->getFinder()->findLayoutTurnoutByBean(bean);

    if (t != nullptr) {
        log.debug("found signalmast at turnout " + t->getTurnout()->getDisplayName());
        QObject* connect = nullptr;

        if (qobject_cast<SignalMast*>(bean)) {
            if (t->getSignalAMast() == bean) {
                connect = t->getConnectA();
            } else if (t->getSignalBMast() == bean) {
                connect = t->getConnectB();
            } else if (t->getSignalCMast() == bean) {
                connect = t->getConnectC();
            } else {
                connect = t->getConnectD();
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            if (t->getSensorA() == bean) {
                connect = t->getConnectA();
            } else if (t->getSensorB() == bean) {
                connect = t->getConnectB();
            } else if (t->getSensorC() == bean) {
                connect = t->getConnectC();
            } else {
                connect = t->getConnectD();
            }
        }

        if (qobject_cast<TrackSegment*>(connect)) {
            tr = (TrackSegment*) connect;
            log.debug("return block " + tr->getLayoutBlock()->getDisplayName());

            return tr->getLayoutBlock();
        }
    }

    LevelXing* l = panel->getFinder()->findLevelXingByBean(bean);

    if (l != nullptr) {
        QObject* connect = nullptr;

        if (qobject_cast<SignalMast*>(bean)) {
            if (l->getSignalAMast() == bean) {
                connect = l->getConnectA();
            } else if (l->getSignalBMast() == bean) {
                connect = l->getConnectB();
            } else if (l->getSignalCMast() == bean) {
                connect = l->getConnectC();
            } else {
                connect = l->getConnectD();
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            if (l->getSensorA() == bean) {
                connect = l->getConnectA();
            } else if (l->getSensorB() == bean) {
                connect = l->getConnectB();
            } else if (l->getSensorC() == bean) {
                connect = l->getConnectC();
            } else {
                connect = l->getConnectD();
            }
        }

        if (qobject_cast<TrackSegment*>(connect)) {
            tr = (TrackSegment*) connect;
            log.debug("return block " + tr->getLayoutBlock()->getDisplayName());

            return tr->getLayoutBlock();
        }
    }

    LayoutSlip* ls = panel->getFinder()->findLayoutSlipByBean(bean);

    if (ls != nullptr) {
        QObject* connect = nullptr;

        if (qobject_cast<SignalMast*>(bean)) {
            if (ls->getSignalAMast() == bean) {
                connect = ls->getConnectA();
            } else if (ls->getSignalBMast() == bean) {
                connect = ls->getConnectB();
            } else if (ls->getSignalCMast() == bean) {
                connect = ls->getConnectC();
            } else {
                connect = ls->getConnectD();
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            if (ls->getSensorA() == bean) {
                connect = ls->getConnectA();
            } else if (ls->getSensorB() == bean) {
                connect = ls->getConnectB();
            } else if (ls->getSensorC() == bean) {
                connect = ls->getConnectC();
            } else {
                connect = ls->getConnectD();
            }
        }

        if (qobject_cast<TrackSegment*>(connect)) {
            tr = (TrackSegment*) connect;
            log.debug("return block " + tr->getLayoutBlock()->getDisplayName());

            return tr->getLayoutBlock();
        }
    }
    return nullptr;
}	//getFacingblockByBean

/**
 * Method to return the LayoutBlock that a given sensor is facing.
 */
/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlockBySensor(Sensor* sensor, LayoutEditor* panel){
 return getFacingBlockByBean(sensor, panel);
}


/*public*/ LayoutBlock* LayoutBlockManager::getProtectedBlock(SignalHead* signalHead, LayoutEditor* panel){
    LayoutBlock* protect = getProtectedBlock(signalHead->getUserName(), panel);
    if(protect == NULL)
        protect = getProtectedBlock(signalHead->getSystemName(), panel);
    return protect;
}

/**
 * Method to return the LayoutBlock that a given signal is protecting.
 */
 /* @TODO This needs to be expanded to cover turnouts and level crossings. */
/*public*/ LayoutBlock* LayoutBlockManager::getProtectedBlock(QString signalName, LayoutEditor* panel){
    PositionablePoint* pp = panel->getFinder()->findPositionablePointByEastBoundSignal(signalName);
    TrackSegment* tr;
    if (pp==NULL) {
        pp = panel->getFinder()->findPositionablePointByWestBoundSignal(signalName);
        if (pp==NULL)
            return NULL;
        tr = pp->getConnect1();
    } else {
        tr = pp->getConnect2();
    }
    //tr = pp->getConnect2();
    if (tr==NULL)
        return NULL;
    return tr->getLayoutBlock();
}

/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlock(SignalHead* signalHead, LayoutEditor* panel){
    LayoutBlock* facing = getFacingBlock(signalHead->getUserName(), panel);
    if(facing == NULL)
        facing = getFacingBlock(signalHead->getSystemName(), panel);
    return facing;
}

/**
 * Method to return the LayoutBlock that a given signal is facing.
 */
 /* @TODO This needs to be expanded to cover turnouts and level crossings. */
/*public*/ LayoutBlock* LayoutBlockManager::getFacingBlock(QString signalName, LayoutEditor* panel){
    PositionablePoint* pp = panel->getFinder()->findPositionablePointByWestBoundSignal(signalName);
    TrackSegment* tr;
    if (pp==NULL) {
        pp = panel->getFinder()->findPositionablePointByWestBoundSignal(signalName);
        if (pp==NULL)
            return NULL;
        tr = pp->getConnect1();
    } else {
        tr = pp->getConnect2();
    }
    if (tr==NULL)
        return NULL;
    return tr->getLayoutBlock();
}

/**
 * Controls switching off incompatible block connectivity messages
 * <P>
 * Warnings are always on when program starts up. Once stopped by the user, these messages may not
 *	be switched on again until program restarts.
 */
/*public*/ bool LayoutBlockManager::warn() {return warnConnectivity;}
/*public*/ void LayoutBlockManager::turnOffWarning() {warnConnectivity = false;}


/**
* returns true if advanced layout block routing has been enabled.
*/
/*public*/ bool LayoutBlockManager::isAdvancedRoutingEnabled() { return _enableAdvancedRouting; }

/**
* Enables the advanced layout block routing protocol
* <p>
* The block routing protocol enables each layout block to build up a list of
* all reachable blocks, along with how far away they are, which direction they
* are in and which of the connected blocks they are reachable from.
*/
/*public*/ void LayoutBlockManager::enableAdvancedRouting(bool boo) {
 if (boo==_enableAdvancedRouting)
  return;
 _enableAdvancedRouting = boo;
 if (boo && initialized)
 {
  initializeLayoutBlockRouting();
 }
 firePropertyChange("advancedRoutingEnabled", (!_enableAdvancedRouting), (_enableAdvancedRouting));
}

/*private*/ void LayoutBlockManager::initializeLayoutBlockRouting() {
 if(!_enableAdvancedRouting || !initialized)
  return;
 // cycle through all LayoutBlocks, completing initialization of the layout block routing
 //java.util.Enumeration<NamedBean*> en = _tsys.elements();
 QHashIterator<QString, NamedBean*> en(*_tsys);
 while (en.hasNext())
 {
  en.next();
  ((LayoutBlock*)en.value())->initializeLayoutBlockRouting();
 }
}

/*public*/ LayoutBlockConnectivityTools* LayoutBlockManager::getLayoutBlockConnectivityTools(){
    return lbct;
}

void LayoutBlockManager::setLastRoutingChange()
{
 lastRoutingChange = QDateTime::currentMSecsSinceEpoch();
 stabilised = false;
 setRoutingStabilised();
}

/*private*/ void LayoutBlockManager::setRoutingStabilised()
{
 if (checking)
 {
  return;
 }
 log.debug("routing table change has been initiated");
 checking=true;
 if(namedStabilisedIndicator!=NULL)
 {
  try
  {
   namedStabilisedIndicator->getBean()->setState(Sensor::INACTIVE);
  }
  catch (JmriException ex)
  {
   log.debug("Error setting stability indicator sensor");
  }
 }
//    Runnable* r = new Runnable(thr);
 MyRunnable* r = new MyRunnable(NULL, this);
//    {
//      /*public*/ void run() {
//        try {
//          firePropertyChange("topology", true, false);
//          long oldvalue = lastRoutingChange;
//          while (!stabilised) {
//            Thread.sleep(2000L);
//            if(oldvalue==lastRoutingChange){
//                log.debug("routing table has now been stable for 2 seconds");
//                checking=false;
//                stabilised=true;
//                firePropertyChange("topology", false, true);
//                if(namedStabilisedIndicator!=NULL){
//                    namedStabilisedIndicator.getBean().setState(Sensor.ACTIVE);
//                }
//            }
//            oldvalue = lastRoutingChange;
//          }
//        } catch (InterruptedException ex) {
//            Thread.currentThread().interrupt();
//            checking=false;
//        } catch (jmri.JmriException ex){
//            log.debug("Error setting stability indicator sensor");
//        }
//      }
//    };
 // TODO: why is this here?
 connect(r, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(passPropertyChange(PropertyChangeEvent*)));
 thr = new QThread(r);
 connect(thr, SIGNAL(started()), r, SLOT(run()));
 connect(r, SIGNAL(finished()), thr, SLOT(quit()));
 thr->start();
}
MyRunnable::MyRunnable(QObject *as, LayoutBlockManager *self) : Runnable(as)
{
 this->self = self;
 log = new Logger("MyRunnable");
}
void MyRunnable::run()
{
 try
 {
  self->firePropertyChange("topology", true, false);
  //emit propertyChange(new PropertyChangeEvent((QObject*)this, "topology", true, false));
  long oldvalue = self->lastRoutingChange;
  while (!self->stabilised)
  {
   QThread::msleep(2000L);
   if(oldvalue==self->lastRoutingChange)
   {
    log->debug("routing table has now been stable for 2 seconds");
    self->checking=false;
    self->stabilised=true;
    self->firePropertyChange("topology", false, true);
    //emit propertyChange(new PropertyChangeEvent((QObject*)this, "topology", false, true));
    if(self->namedStabilisedIndicator!=NULL)
    {
     self->namedStabilisedIndicator->getBean()->setState(Sensor::ACTIVE);
    }
   }
   oldvalue = self->lastRoutingChange;
  }
 }
 catch (InterruptedException ex)
 {
  QThread::currentThread()->exit(0);
  self->checking=false;
 }
 catch (JmriException ex)
 {
  log->debug("Error setting stability indicator sensor");
 }
}

void LayoutBlockManager::passPropertyChange(PropertyChangeEvent *e)
{
 emit propertyChange(e);
}

/**
* Assign a sensor to the routing protocol, that changes state dependant upon
* if the routing protocol has stabilised or is under going a change.
*/
/*public*/ void LayoutBlockManager::setStabilisedSensor(QString pName) throw (JmriException)
{
 if (InstanceManager::sensorManagerInstance()!=NULL)
 {
  Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(pName);
  if (sensor != NULL)
  {
   namedStabilisedIndicator =((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor);
  }
  else
  {
   log.error("Sensor '"+pName+"' not available");
   throw new JmriException("Sensor '"+pName+"' not available");
  }
  try
  {
   if(stabilised)
    sensor->setState(Sensor::ACTIVE);
   else
    sensor->setState(Sensor::INACTIVE);
  }
  catch (JmriException ex)
  {
   log.error("Error setting stablilty indicator sensor");
  }
 }
 else
 {
  log.error("No SensorManager for this protocol");
  throw new JmriException("No Sensor Manager Found");
 }
}

/**
* Return the sensor used to indicate if the routing protocol has stabilised or not
*/
/*public*/ Sensor* LayoutBlockManager::getStabilisedSensor()
{
 if(namedStabilisedIndicator==NULL)
  return NULL;
 return namedStabilisedIndicator->getBean();
}

/**
*   Get the sensor used for the stability indication
*/
/*public*/ NamedBeanHandle <Sensor*>* LayoutBlockManager::getNamedStabilisedSensor()
{
 return namedStabilisedIndicator;
}

/**
* Returns true if the layout block routing protocol has stabilised
*/
/*public*/ bool LayoutBlockManager::routingStablised()
{
 return stabilised;
}

/**
* returns the time when the last routing change was made, recorded as System.nanoTime()
*/
/*public*/ long LayoutBlockManager::getLastRoutingChange()
{
 return lastRoutingChange;
}

//@Override
//@Nonnull
/*public*/ QString LayoutBlockManager::getBeanTypeHandled(bool plural)const {
    return tr(plural ? "LayoutBlocks" : "LayoutBlock");
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutBlockManager.class.getName());
//}

///* @(#)LayoutBlockManager.java */
QCompleter* LayoutBlockManager::getCompleter(QString text, bool bIncludeUserNames )
{
 if(text.length()>1)
 {
  QStringList nameList = getSystemNameList();
  QStringList completerList;
  foreach(QString systemName, nameList)
  {
   LayoutBlock* b = (LayoutBlock*)getBySystemName(systemName);
   if(systemName.toUpper().startsWith(text.toUpper()))
    completerList.append(b->getUserName());
   else if(bIncludeUserNames)
   {
    if(b->getUserName().toUpper().startsWith(text.toUpper()))
     completerList.append(b->getUserName());
   }
  }
  if(completerList.size() > 0)
  {
   QCompleter* completer = new QCompleter(completerList, this);
    return completer;
  }
 }
 return NULL;
}
/*public*/ LayoutBlock *LayoutBlockManager::getBySystemName(QString name) const {
    if (name==NULL || name.trimmed().length()==0) { return NULL; }
    QString key = name.toUpper();
    return (LayoutBlock*)_tsys->value(key);
}

/*public*/ LayoutBlock *LayoutBlockManager::getByUserName(QString key)const  {
    if (key==NULL || key.trimmed().length()==0) { return NULL; }
    return (LayoutBlock*)_tuser->value(key);
}
