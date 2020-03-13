#include "layoutblockconnectivitytools.h"
#include "layoutblock.h"
#include "panelmenu.h"
#include "namedbean.h"
#include "connectivityutil.h"
#include "layouttrackexpectedstate.h"

LayoutBlockConnectivityTools::LayoutBlockConnectivityTools()
{
    log = new Logger("LayoutBlockConnectivityTools");
    lastErrorMessage = "Unknown Error Occured";
}
/**
* These are a series of layout block connectivity tools that can be used
* when the advanced layout block routing has been enabled.
* These tools can determine if a path from a source to destination bean is valid.
* If a route between two layout blocks is usable and free.
*
* @author Kevin Dickerson  Copyright (C) 2011
* @version			$Revision: 19923 $
*/

///*public*/ class LayoutBlockConnectivityTools{

//    /*public*/ LayoutBlockConnectivityTools(){

//    }

/**
 * Determines if a pair of NamedBeans (Signalhead, Signalmast or Sensor) assigned to a
 * block boundary are reachable.
 *
 * @return true if source and destination beans are reachable, or false if they are not
 * @throws Jmri.Exception if no blocks can be found that related to the named beans.
 */
/*public*/ bool LayoutBlockConnectivityTools::checkValidDest(NamedBean* sourceBean, NamedBean* destBean, int pathMethod) throw (JmriException)
{
 LayoutBlock* facingBlock = NULL;
 LayoutBlock* protectingBlock = NULL;
 LayoutBlock* destFacingBlock = NULL;
 LayoutBlock* destProtectBlock = NULL;
 QList<LayoutEditor*>* layout = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
 for(int i = 0; i<layout->size(); i++)
 {
  if(log->isDebugEnabled())
   log->debug("Layout name " + layout->at(i)->getLayoutName());
  if (facingBlock==NULL)
  {
     facingBlock = lbm->getFacingBlockByNamedBean(sourceBean, layout->at(i));
  }
  if (protectingBlock==NULL)
  {
    protectingBlock = lbm->getProtectedBlockByNamedBean(sourceBean, layout->at(i));
  }
  if(destFacingBlock==NULL)
  {
    destFacingBlock = lbm->getFacingBlockByNamedBean(destBean, layout->at(i));
  }
  if(destProtectBlock==NULL)
  {
    destProtectBlock = lbm->getProtectedBlockByNamedBean(destBean, layout->at(i));
   }
   if((destFacingBlock!=NULL) && (facingBlock!=NULL) && (protectingBlock!=NULL))
   {
    /*Destination protecting block is allowed to be NULL, as the destination signalmast
      could be assigned to an end bumper */
    //A simple to check to see if the remote signal is in the correct direction to ours.
    try
    {
     return checkValidDest(facingBlock, protectingBlock, destFacingBlock, destProtectBlock, pathMethod);
     }
     catch (JmriException e)
     {
      throw e;
     }
    }
   else
   {
    log->debug("blocks not found");
   }
  }
  if(log->isDebugEnabled())
    log->debug("No valid route from " + sourceBean->getDisplayName() + " to " + destBean->getDisplayName());
  //throw new JmriException("Blocks Not Found");
  return false;
 }

/**
* The is used in conjunction with the layout block routing protocol, to discover
* a clear path from a source layout block through to a destination layout block.
* By specifying the sourceLayoutBlock and protectingLayoutBlock or sourceLayoutBlock+1,
* a direction of travel can then be termined, eg east to west, south to north etc.
* <p>
* @param sourceBean - The source bean (SignalHead, SignalMast or Sensor) assigned to a
*                      block boundary that we are starting from.
* @param destBean - The destination bean.
* @param validateOnly - When set false, the system will not use layout blocks
*                       that are set as either reserved(useExtraColor set) or occupied, if it
*                       finds any then it will try to find an alternative path
*                       When set false, no block state checking is performed.
* @param pathMethod - Performs a check to see if any signal heads/masts are
*                     in the path, if there are then the system will try to find
*                     an alternative path.  If set to NONE, then no checking is performed.
* @return an QList of all the layoutblocks in the path.
* @throws jmri.JmriException if it can not find a valid path or the routing
*                            has not been enabled.
*/
/*public*/ QList<LayoutBlock*> LayoutBlockConnectivityTools::getLayoutBlocks(NamedBean* sourceBean, NamedBean* destBean,
                                                                             bool validateOnly, int pathMethod) throw (JmriException)
{
 QList<LayoutEditor*>* layout = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
 LayoutBlock* facingBlock = NULL;
 LayoutBlock* protectingBlock = NULL;
 LayoutBlock* destFacingBlock = NULL;
 for(int i = 0; i<layout->size(); i++)
 {
  if(log->isDebugEnabled())
      log->debug("Layout name " + layout->at(i)->getLayoutName());
  if (facingBlock==NULL){
      facingBlock = lbm->getFacingBlockByNamedBean(sourceBean, layout->at(i));
  }
  if (protectingBlock==NULL){
      protectingBlock = lbm->getProtectedBlockByNamedBean(sourceBean, layout->at(i));
  }
  if(destFacingBlock==NULL){
      destFacingBlock = lbm->getFacingBlockByNamedBean(destBean, layout->at(i));
  }
  if((destFacingBlock!=NULL) && (facingBlock!=NULL) && (protectingBlock!=NULL)){
      try{
          return getLayoutBlocks(facingBlock, destFacingBlock, protectingBlock, validateOnly, pathMethod);
      } catch (JmriException e){
          throw e;
      }
  } else {
      log->debug("blocks not found");
  }
 }
 if(log->isDebugEnabled())
     log->debug("No valid route from " + sourceBean->getDisplayName() + " to " + destBean->getDisplayName());
 throw JmriException("Blocks Not Found");
}
#if 0  // done, see below!

    /**
    * Returns a list of NamedBeans (Signalhead, Signalmast or Sensor) that are assinged to block boundaries
    * in a given list
    * @param blocklist The list of block in order that need to be checked.
    * @param panel (Optional) panel that the blocks need to be checked against
    * @param T (Optional) the class that we want to check against, either Sensor, SignalMast or SignalHead, set NULL will return any.
    */
    /*public*/ List<NamedBean> getBeansInPath(List<LayoutBlock> blocklist, LayoutEditor panel, Class<?> T){
        QList<NamedBean> beansInPath = new QList<NamedBean>();
        if(blocklist.size()>=2){
            LayoutBlockManager lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
            for(int x = 1; x<blocklist.size(); x++){
                LayoutBlock facingBlock = blocklist.get(x-1);
                LayoutBlock protectingBlock = blocklist.get(x);
                NamedBean nb = NULL;
                if(T==NULL){
                    nb = lbm->getFacingNamedBean(facingBlock.getBlock(), protectingBlock.getBlock(), panel);
                } else if(T==(jmri.SignalMast.class)){
                    nb = lbm->getFacingSignalMast(facingBlock.getBlock(), protectingBlock.getBlock(), panel);
                } else if (T==(jmri.Sensor.class)){
                    nb = lbm->getFacingSensor(facingBlock.getBlock(), protectingBlock.getBlock(), panel);
                } else if (T==(jmri.SignalHead.class)){
                    nb = lbm->getFacingSignalHead(facingBlock.getBlock(), protectingBlock.getBlock());
                }
                if(nb!=NULL)
                    beansInPath.add(nb);
            }
        }
        return beansInPath;
    }
#endif

/**
 * Returns a list of NamedBeans (Signalhead, Signalmast or Sensor) that are
 * assinged to block boundaries in a given list
 *
 * @param blocklist The list of block in order that need to be checked.
 * @param panel     (Optional) panel that the blocks need to be checked
 *                  against
 * @param T         (Optional) the class that we want to check against,
 *                  either Sensor, SignalMast or SignalHead, set null will
 *                  return any.
 */
/*public*/ QList<NamedBean*> LayoutBlockConnectivityTools::getBeansInPath(QList<LayoutBlock*> blocklist, LayoutEditor* panel, QString T) {
    QList<NamedBean*> beansInPath = QList<NamedBean*>();
    if (blocklist.size() >= 2) {
        LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
        for (int x = 1; x < blocklist.size(); x++) {
            LayoutBlock* facingBlock = blocklist.at(x - 1);
            LayoutBlock* protectingBlock = blocklist.at(x);
            NamedBean* nb = nullptr;
            if (T == "") {
                nb = lbm->getFacingNamedBean(facingBlock->getBlock(), protectingBlock->getBlock(), panel);
            } else if (T == ("SignalMast")) {
                nb = (NamedBean*)lbm->getFacingSignalMast(facingBlock->getBlock(), protectingBlock->getBlock(), panel);
            } else if (T == ("Sensor")) {
                nb = lbm->getFacingSensor(facingBlock->getBlock(), protectingBlock->getBlock(), panel);
            } else if (T == ("SignalHead")) {
                nb = lbm->getFacingSignalHead(facingBlock->getBlock(), protectingBlock->getBlock());
            }
            if (nb != nullptr) {
                beansInPath.append(nb);
            }
        }
    }
    return beansInPath;
}

/**
     * Determines if one set of blocks is reachable from another set of blocks
     * based upon the directions of the set of blocks.
     * <ul>
     * <li>Called by {@link jmri.implementation.DefaultSignalMastLogic} using MASTTOMAST.</li>
     * <li>Called by {@link jmri.jmrit.entryexit.DestinationPoints} using SENSORTOSENSOR.</li>
     * <li>Called by {@link jmri.jmrit.entryexit.EntryExitPairs} using SENSORTOSENSOR.</li>
     * </ul>
     * Convert the destination protected block to an array list.
     * Call the 3 block+list version of checkValidDest() to finish the checks.
     * <p>
     * @param currentBlock The facing layout block for the source signal or sensor.
     * @param nextBlock    The protected layout block for the source signal or sensor.
     * @param destBlock    The facing layout block for the destination signal mast or sensor.
     * @param destProBlock The protected destination block.
     * @param pathMethod   Indicates the type of path:  Signal head, signal mast or sensor.
     * @return true if a path to the destination is valid.
     * @throws jmri.JmriException if any Block is null;
     */
    /*public*/ bool LayoutBlockConnectivityTools::checkValidDest(LayoutBlock* currentBlock, LayoutBlock* nextBlock, LayoutBlock* destBlock, LayoutBlock* destProBlock, int pathMethod) throw (JmriException) {

        QList<LayoutBlock*> destList = QList<LayoutBlock*>();
        if (destProBlock != nullptr) {
            destList.append(destProBlock);
        }
        try {
            return checkValidDest(currentBlock, nextBlock, destBlock, destList, pathMethod);
        } catch (JmriException e) {
            throw e;
        }

    }


/**
 * Determines if one set of blocks is reachable from another set of blocks
 * based upon the directions of the set of blocks.
 * <p>
 * This is used to help with identifying items such as signalmasts located
 * at positionable points or turnouts are facing in the same direction as
 * other given signalmasts.
 * <p>
 * Given the current block and the next block we can work out the direction
 * of travel.
 * Given the destBlock and the next block on, we can determine the whether
 * the destBlock comes before the destBlock+1.
 * @return true if destBlock comes before destBlock+1 or
 * false if destBlock comes after destBlock+1
 * @throws Jmri.Exception if any Block is NULL;
 */
/*public*/ bool LayoutBlockConnectivityTools::checkValidDest(LayoutBlock* currentBlock, LayoutBlock* nextBlock, LayoutBlock* destBlock, QList<LayoutBlock*> destBlockn1, int pathMethod) throw (JmriException)
{
 LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
 if (!lbm->isAdvancedRoutingEnabled())
 {
  log->info("Advanced routing has not been enabled therefore we cannot use this function");
  throw JmriException("Advanced routing has not been enabled therefore we cannot use this function");
 }
 if(log->isDebugEnabled())
 {
  try
  {
   log->debug("faci " + currentBlock->getDisplayName());
   log->debug("next " + nextBlock->getDisplayName());
   log->debug("dest " + destBlock->getDisplayName());
   for (LayoutBlock* dp : destBlockn1)
   {
    log->debug(tr("dest + 1 %1").arg(dp->getDisplayName()));
   }
  }
  catch (NullPointerException e)
  {
  }
 }

 if((destBlock!=NULL) && (currentBlock!=NULL) && (nextBlock!=NULL)){
 if(!currentBlock->isRouteToDestValid(nextBlock->getBlock(), destBlock->getBlock())){
  log->debug("Route to dest not valid");
  return false;
 }
 if(log->isDebugEnabled()){
  log->debug("dest " + destBlock->getDisplayName());
 //                if(!destBlockn1.isEmpty())
 //                    log->debug("remote prot " + destBlockn1->getDisplayName());
 }
 //Do a simple test to see if one is reachable from the other.
 int proCount = 0;
 int desCount = 0;
 if(!destBlockn1.isEmpty()){
  desCount = currentBlock->getBlockHopCount(destBlock->getBlock(), nextBlock->getBlock());
  proCount = currentBlock->getBlockHopCount(destBlockn1.at(0)->getBlock(), nextBlock->getBlock());
  log->debug("dest " + QString::number(desCount) + " protecting " + QString::number(proCount));
 }
 if (proCount > desCount && (proCount - 1) == desCount)
 {
       // The block that we are protecting should be one hop greater than the destination count.
       log->debug("Protecting is one hop away from destination and therefore valid.");
       return true;
 }

  /*Need to do a more advanced check in this case as the destBlockn1
   could be reached via a different route and therefore have a smaller
   hop count we need to therefore step through each block until we reach
   the end.
   The advanced check also covers cases where the route table is inconsistent.
   We also need to perform a more advanced check if the destBlockn1
   is null as this indicates that the destination signal mast is assigned
   on an end bumper*/

  if (pathMethod == SENSORTOSENSOR && destBlockn1.size() == 0) {
      // Change the pathMethod to accept the NX sensor at the end bumper.
      pathMethod = NONE;
  }

  QList<LayoutBlock*> blockList = getLayoutBlocks(currentBlock, destBlock, nextBlock, true, pathMethod); //Was MASTTOMAST
  if (log->isDebugEnabled()) {
      log->debug(tr("checkValidDest blockList for %1").arg(destBlock->getDisplayName()));
      //blockList.forEach(blk -> log.debug("  block = {}", blk.getDisplayName()));
      foreach(LayoutBlock* blk, blockList)
       log->debug(tr("  block = %1").arg(blk->getDisplayName()));
  }
  for (LayoutBlock* dp : destBlockn1) {
      log->debug(tr("dp = %1").arg(dp->getDisplayName()));
      if (blockList.contains(dp) && currentBlock != dp) {
          log->debug("Signal mast in the wrong direction");
          return false;
      }
  }
      /*Work on the basis that if you get the blocks from source to dest
       then the dest+1 block should not be included*/
  log->debug("Signal mast in the correct direction");
  return true;

 } else if (destBlock == nullptr) {
     throw JmriException("Block in Destination Field returns as invalid");
 } else if (currentBlock == nullptr) {
     throw JmriException("Block in Facing Field returns as invalid");
 } else if (nextBlock == nullptr) {
     throw JmriException("Block in Protecting Field returns as invalid");
 }
 throw JmriException("BlockIsNull");
}

/**
* This uses the layout editor to check if the destination location is
* reachable from the source location
*
* @param facing Layout Block that is considered our first block
* @param protecting Layout Block that is considered first block +1
* @param dest Layout Block that we want to get to
* @return true if valid, false if not valid.
*/

/*public*/ bool LayoutBlockConnectivityTools::checkValidDest(LayoutBlock* facing, LayoutBlock* protecting, FacingProtecting* dest, int pathMethod) throw (JmriException){
        if(facing==NULL || protecting==NULL || dest == NULL){
            return false;
        }
        try{
            return checkValidDest(facing, protecting, static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(dest->getFacing()), static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(dest->getProtecting()), pathMethod);
        } catch (JmriException e){
            throw e;
        }
    }
   /**
    * The is used in conjunction with the layout block routing protocol, to discover
    * a clear path from a source layout block through to a destination layout block.
    * By specifying the sourceLayoutBlock and protectingLayoutBlock or sourceLayoutBlock+1,
    * a direction of travel can then be termined, eg east to west, south to north etc.
    * <p>
    * @param sourceLayoutBlock - The layout block that we are starting from,
    *                    can also be considered as the block facing a signal.
    * @param destinationLayoutBlock - The layout block that we want to get to
    * @param protectingLayoutBlock - The next layout block connected to the source
    *                 block, this can also be considered as the block being protected by a signal
    * @param validateOnly - When set false, the system will not use layout blocks
    *                       that are set as either reserved(useExtraColor set) or occupied, if it
    *                       finds any then it will try to find an alternative path
    *                       When set false, no block state checking is performed.
    * @param pathMethod - Performs a check to see if any signal heads/masts are
    *                     in the path, if there are then the system will try to find
    *                     an alternative path.  If set to NONE, then no checking is performed.
    * @return an QList of all the layoutblocks in the path.
    * @throws jmri.JmriException if it can not find a valid path or the routing
    *                            has not been enabled.
    */
/*public*/ QList<LayoutBlock*> LayoutBlockConnectivityTools::getLayoutBlocks(LayoutBlock* sourceLayoutBlock, LayoutBlock* destinationLayoutBlock, LayoutBlock* protectingLayoutBlock, bool validateOnly, int pathMethod) throw (JmriException){
        lastErrorMessage= "Unknown Error Occured";
        LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
        if (!lbm->isAdvancedRoutingEnabled()){
            log->info("Advanced routing has not been enabled therefore we cannot use this function");
            throw  JmriException("Advanced routing has not been enabled therefore we cannot use this function");
        }

        int directionOfTravel = sourceLayoutBlock->getNeighbourDirection(protectingLayoutBlock);
        Block* currentBlock = sourceLayoutBlock->getBlock();

        Block* destBlock = destinationLayoutBlock->getBlock();
        if(log->isDebugEnabled()) log->debug("Destination Block " + destinationLayoutBlock->getDisplayName() + " " + destBlock->getDisplayName());
        Block* nextBlock = protectingLayoutBlock->getBlock();
        if(log->isDebugEnabled()){
            log->debug("s:" + sourceLayoutBlock->getDisplayName() + " p:" + protectingLayoutBlock->getDisplayName() + " d:" + destinationLayoutBlock->getDisplayName());
        }
        QList<BlocksTested*> blocksInRoute =  QList<BlocksTested*>();
        blocksInRoute.append(new BlocksTested(sourceLayoutBlock));

        if(!validateOnly){
            if (canLBlockBeUsed(protectingLayoutBlock)){
                blocksInRoute.append(new BlocksTested(protectingLayoutBlock));
            } else {
                lastErrorMessage = "Block we are protecting is already occupied or reserved";
                log->debug(lastErrorMessage);
                throw  JmriException(lastErrorMessage);
            }
            if (!canLBlockBeUsed(destinationLayoutBlock)){
                lastErrorMessage = "Destination Block is already occupied or reserved";
                log->debug(lastErrorMessage);
                throw  JmriException(lastErrorMessage);
            }
        } else {
            blocksInRoute.append(new BlocksTested(protectingLayoutBlock));
        }
        if (destinationLayoutBlock==protectingLayoutBlock){
            QList<LayoutBlock*> returnBlocks =  QList<LayoutBlock*>();
            for (int i =0; i<blocksInRoute.size(); i++){
                returnBlocks.append(blocksInRoute.at(i)->getBlock());
            }
            return returnBlocks;
        }
        LayoutBlock* currentLBlock = protectingLayoutBlock;

        BlocksTested* bt = blocksInRoute.at(blocksInRoute.size()-1);

        int ttl=1;
        QList<int> offSet=  QList<int>();
        while (ttl <ttlSize){ //value should be higher but low for test!
            log->debug("===== Ttl value = " + QString::number(ttl) + " ======\nLooking for next block");
            int nextBlockIndex = findBestHop(currentBlock, nextBlock, destBlock, directionOfTravel, offSet, validateOnly, pathMethod);
            if (nextBlockIndex!=-1){
                bt->addIndex(nextBlockIndex);
                if(log->isDebugEnabled()) log->debug("block index returned " + QString::number(nextBlockIndex) + " Blocks in route size " + QString::number(blocksInRoute.size()));
                //Sets the old next block to be our current block.
                currentLBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(nextBlock);

                offSet =  QList<int>();

                directionOfTravel = currentLBlock->getRouteDirectionAtIndex(nextBlockIndex);

                currentBlock = nextBlock;
                nextBlock = currentLBlock->getRouteNextBlockAtIndex(nextBlockIndex);
                LayoutBlock* nextLBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(nextBlock);
                if(log->isDebugEnabled()){
                    log->debug("Blocks in route size " + blocksInRoute.size());
                    log->debug(nextBlock->getDisplayName() + " " + destBlock->getDisplayName());
                }
                if (nextBlock==currentBlock){
                    nextBlock = currentLBlock->getRouteDestBlockAtIndex(nextBlockIndex);
                    log->debug("the next block to our destination we are looking for is directly connected to this one");
                } else if(protectingLayoutBlock!=nextLBlock){
                    log->debug("Add block " + nextLBlock->getDisplayName());
                    bt = new BlocksTested(nextLBlock);
                    blocksInRoute.append(bt);
                }
                if (nextBlock==destBlock){
                    QList<LayoutBlock*> returnBlocks =  QList<LayoutBlock*>();
                    for (int i =0; i<blocksInRoute.size(); i++){
                        returnBlocks.append(blocksInRoute.at(i)->getBlock());
                    }
                    returnBlocks.append(destinationLayoutBlock);
                    if(log->isDebugEnabled()){
                        log->debug("Adding destination Block " + destinationLayoutBlock->getDisplayName());
                        log->debug("arrived at destination block");
                        log->debug(sourceLayoutBlock->getDisplayName() + " Return as Long");
                        for (int i =0; i<returnBlocks.size(); i++){
                            log->debug(returnBlocks.at(i)->getDisplayName());
                        }
                        log->debug("Finished List");
                    }
                    return returnBlocks;
                }
            }
            else {
            //-1 is returned when there are no more valid besthop valids found
                //Block index is -1, so we need to go back a block and find another way.

                //So we have gone back as far as our starting block so we better return.
                int birSize = blocksInRoute.size();
                log->debug("block in route size " + birSize);
                if (birSize<=2) {
                    log->debug("drop out here with ttl");
                    ttl=ttlSize+1;
                }
                else {
                    if(log->isDebugEnabled()){
                        for (int t = 0; t<blocksInRoute.size(); t++){
                            log->debug("index " + QString::number(t) + " block " + blocksInRoute.at(t)->getBlock()->getDisplayName());
                        }
                        log->debug("To remove last block " + blocksInRoute.at(birSize-1)->getBlock()->getDisplayName());
                    }

                    currentBlock = blocksInRoute.at(birSize-3)->getBlock()->getBlock();
                    nextBlock = blocksInRoute.at(birSize-2)->getBlock()->getBlock();
                    offSet = blocksInRoute.at(birSize-2)->getTestedIndexes();
                    bt = blocksInRoute.at(birSize-2);
                    blocksInRoute.removeAt(birSize-1);
                    ttl--;
                }
            }
            ttl++;
        }
        if(ttl==ttlSize){
            lastErrorMessage = "ttlExpired";
        }
        //we exited the loop without either finding the destination or we had error.
        throw JmriException(lastErrorMessage);
    }
#if 1

    /*private*/ bool LayoutBlockConnectivityTools::canLBlockBeUsed(LayoutBlock* lBlock){
        if (lBlock->getBlock()->getPermissiveWorking())
            return true;
        if (lBlock->getState()==Block::OCCUPIED)
            return false;
        if (lBlock->getUseExtraColor())
            return false;
        return true;
    }

    //We need to take into account if the returned block has a signalmast attached.
    int LayoutBlockConnectivityTools::findBestHop(/*final*/ Block* preBlock, /*final*/ Block* currentBlock, Block* destBlock, int direction, QList<int> offSet, bool validateOnly, int pathMethod)
    {
//        Logger* lBlockManLog = org.apache.log4j.Logger.getLogger(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager")).getClass().getName());
//        org.apache.log4j.Level currentLevel = lBlockManLog.getLevel();
        int blockindex = 0;
        Block* block;
        LayoutBlock* currentLBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(currentBlock);
        QVector<int> blkIndexTested =  QVector<int>(5);
        if(log->isDebugEnabled())
            log->debug("In find best hop current " + currentLBlock->getDisplayName() + " previous " + preBlock->getDisplayName());
        while(blockindex!=-1){
            if (currentBlock==preBlock){
                //Basically looking for the connected block, which there should only be one of!
                blockindex = currentLBlock->getConnectedBlockRouteIndex(destBlock, direction);
            } else {
                blockindex = currentLBlock->getNextBestBlock(preBlock, destBlock, offSet, METRIC);
            }
            if (blockindex!=-1){
                block = currentLBlock->getRouteNextBlockAtIndex(blockindex);
                LayoutBlock* lBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getLayoutBlock(block);
                if ((block == currentBlock) && (currentLBlock->getThroughPathIndex(preBlock, destBlock)==-1)){
                    lastErrorMessage="block " + block->getDisplayName() + " is directly attached, however the route to the destination block " + destBlock->getDisplayName() + " can not be directly used";
                    log->debug(lastErrorMessage);
                }
                else if ((validateOnly) || (canLBlockBeUsed(lBlock))){
                    if(log->isDebugEnabled()){
                        log->debug(block->getDisplayName() + " not occupied & not reserved but we need to check if the anchor point between the two contains a signal or not");
                        log->debug(currentBlock->getDisplayName() + " " + block->getDisplayName());
                    }
                    Block* blocktoCheck = block;
                    if (block == currentBlock){
                        log->debug("current block matches returned block therefore the next block is directly connected");
                        blocktoCheck=destBlock;
                    }
                    NamedBean* signal = NULL;
                    /* We change the logging level to fatal in the layout block manager as we are testing to make sure that no signalhead/mast exists
                       this would generate an error message that is expected.*/
//                    lBlockManLog.setLevel(org.apache.log4j.Level.FATAL);
                    switch(pathMethod){
                        case MASTTOMAST :
                        signal = (NamedBean*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getFacingSignalMast(currentBlock, blocktoCheck); break;
                        case HEADTOHEAD :
                        signal = (NamedBean*)static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getFacingSignalHead(currentBlock, blocktoCheck); break;
                        default :
                        signal = (NamedBean*) static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->getFacingSignalObject(currentBlock, blocktoCheck); break;
                    }
//                    lBlockManLog.setLevel(currentLevel);
                    if (signal==NULL){
                        log->debug("No object found so okay to return");
                        return blockindex;
                    } else {
                        lastErrorMessage ="Signal " + signal->getDisplayName() + " already exists between blocks " + currentBlock->getDisplayName() + " and " + blocktoCheck->getDisplayName() + " in the same direction on this path";
                        log->debug(lastErrorMessage);
                    }
                } else {
                    lastErrorMessage="block " + block->getDisplayName() + " found not to be not usable";
                    log->debug(lastErrorMessage);
                }
                if(blkIndexTested.contains(blockindex)){
                    lastErrorMessage=("No valid free path found");
                    return -1;
                }
                blkIndexTested.append(blockindex);
                offSet.append(blockindex);
            } else {
                log->debug("At this point the getNextBextBlock() has returned a -1");
            }
        }
        return -1;
    }

    /*private*/ bool LayoutBlockConnectivityTools::checkForDoubleCrossover(Block* prevBlock, LayoutBlock* curBlock, Block* nextBlock) {
            LayoutEditor* le = curBlock->getMaxConnectedPanel();
            ConnectivityUtil* ct = le->getConnectivityUtil();
            QList<LayoutTrackExpectedState<LayoutTurnout*>*> turnoutList = ct->getTurnoutList(curBlock->getBlock(), prevBlock, nextBlock);
            for (int i = 0; i < turnoutList.size(); i++) {
                LayoutTurnout* lt = turnoutList.at(i)->getObject();
                if (lt->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER) {
                    if (turnoutList.at(i)->getExpectedState() == Turnout::THROWN) {
                        Turnout* t = lt->getTurnout();
                        if (t->getKnownState() == Turnout::THROWN) {
                            if (lt->getLayoutBlock() == curBlock || lt->getLayoutBlockC() == curBlock) {
                                if (!canLBlockBeUsed(lt->getLayoutBlockB()) && !canLBlockBeUsed(lt->getLayoutBlockD())) {
                                    return false;
                                }
                            } else if (lt->getLayoutBlockB() == curBlock || lt->getLayoutBlockD() == curBlock) {
                                if (!canLBlockBeUsed(lt->getLayoutBlock()) && !canLBlockBeUsed(lt->getLayoutBlockC())) {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
            return true;
        }

        /*private*/ bool LayoutBlockConnectivityTools::checkForLevelCrossing(LayoutBlock* curBlock) {
            LayoutEditor* lay = curBlock->getMaxConnectedPanel();
            for (LayoutTrack* lt : lay->getLevelXings()) {
             LevelXing* lx = (LevelXing*)lt;
                if (lx->getLayoutBlockAC() == curBlock
                        || lx->getLayoutBlockBD() == curBlock) {
                    if ((lx->getLayoutBlockAC() != nullptr)
                            && (lx->getLayoutBlockBD() != nullptr)
                            && (lx->getLayoutBlockAC() != lx->getLayoutBlockBD())) {
                        if (lx->getLayoutBlockAC() == curBlock) {
                            return canLBlockBeUsed(lx->getLayoutBlockBD());
                        } else if (lx->getLayoutBlockBD() == curBlock) {
                            return canLBlockBeUsed(lx->getLayoutBlockAC());
                        }
                    }
                }
            }
            return true;
        }

    /**
    *   Discovers valid pairs of beans type T assigned to a layout editor.
    *   If no bean type is provided, then either SignalMasts or Sensors are discovered
    *   If no editor is provided, then all editors are considered
    */
    /*public*/ QHash<NamedBean*, QList<NamedBean*> > LayoutBlockConnectivityTools::discoverValidBeanPairs(LayoutEditor* editor, QString T, int pathMethod){
        LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
        QHash<NamedBean*, QList<NamedBean*> > retPairs =  QHash<NamedBean*, QList<NamedBean*> >();
        QList<FacingProtecting*> beanList = generateBlocksWithBeans(editor, T);
        for(int i = 0; i<beanList.size(); i++){
            if(log->isDebugEnabled())
                try{
                    log->debug("\nSource " + beanList.at(i)->getBean()->getDisplayName());
                    log->debug("facing " + beanList.at(i)->getFacing()->getDisplayName());
                    log->debug("protecting " + beanList.at(i)->getProtecting()->getDisplayName());
                } catch (NullPointerException e){
                    //Can be considered normal if the signalmast is assigned to an end bumper.
                }
            Block* facing = beanList.at(i)->getFacing();
            LayoutBlock* lFacing = lbm->getLayoutBlock(facing);
            Block* protecting = beanList.at(i)->getProtecting();
            LayoutBlock* lProtecting = lbm->getLayoutBlock(protecting);
            NamedBean* source = beanList.at(i)->getBean();
            try {
                retPairs.insert(source, discoverPairDest(source, lProtecting, lFacing, beanList, pathMethod));
            } catch (JmriException ex){
                log->error(ex.toString());
            }
        }
        return retPairs;
    }

   /**
    *   Returns a list of valid destination beans reachable from a given source bean.
    * @param source Either a SignalMast or Sensor
    * @param editor The layout editor that the source is located on, if NULL, then all editors are considered
    * @param T The class of the remote destination, if NULL, then both SignalMasts and Sensors are considered
    * @return A list of all reachable NamedBeans
    */
    /*public*/ QList<NamedBean*> LayoutBlockConnectivityTools::discoverPairDest(NamedBean* source, LayoutEditor* editor, QString T, int pathMethod) throw (JmriException)
    {
     LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
     LayoutBlock* lFacing = lbm->getFacingBlockByNamedBean(source, editor);
     QList<LayoutBlock*> lProtecting = lbm->getProtectingBlocksByNamedBean(source, editor);
     QList<NamedBean*> ret = QList<NamedBean*>();
     QList<FacingProtecting*> beanList = generateBlocksWithBeans(editor, T);
     try {
         for (LayoutBlock* lb : lProtecting) {
             //ret.addAll(discoverPairDest(source, lb, lFacing, beanList, pathMethod));
          QList<NamedBean*> l = discoverPairDest(source, lb, lFacing, beanList, pathMethod);
          foreach (NamedBean*bean, l) {
          ret.append(bean);
          }
         }
     } catch (JmriException e) {
         throw e;
     }
     return ret;
    }

    QList<NamedBean*> LayoutBlockConnectivityTools::discoverPairDest(NamedBean* source, LayoutBlock* lProtecting, LayoutBlock* lFacing, QList<FacingProtecting*> blockList, int pathMethod) throw (JmriException)
    {
     LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
     if(!lbm->isAdvancedRoutingEnabled())
     {
      throw  JmriException("advanced routing not enabled");
     }
     if(!lbm->routingStablised())
     {
      log->error(("routing not stablised"));
      throw JmriException("routing not stablised");

     }
     QList<NamedBean*> validDestBean =  QList<NamedBean*>();
     for (int j = 0; j<blockList.size(); j++)
     {
      if (blockList.at(j)->getBean()!=source)
      {
//               boolean alreadyExist = false;
          NamedBean* destObj = blockList.at(j)->getBean();
          if(log->isDebugEnabled())
              log->debug("looking for pair " + source->getDisplayName() + " " + destObj->getDisplayName());
          try {
              if(checkValidDest(lFacing, lProtecting, blockList.at(j),pathMethod)){
                  if(log->isDebugEnabled())
                      log->debug("Valid pair " + source->getDisplayName() + " " + destObj->getDisplayName());
                  LayoutBlock* ldstBlock = lbm->getLayoutBlock(blockList.at(j)->getFacing());
                  try {
                      QList<LayoutBlock*> lblks = getLayoutBlocks(lFacing, ldstBlock, lProtecting, true, MASTTOMAST);
                      if(log->isDebugEnabled())
                          log->debug("Adding block " + destObj->getDisplayName() + " to paths, current size " + lblks.size());
                      validDestBean.append(destObj);
         }
         catch (JmriException e)
         {  // Considered normal if route not found.
          log->debug("not a valid route through " + source->getDisplayName() + " - " + destObj->getDisplayName());
         }
        }
       }
       catch (JmriException ex)
       {
         log->debug(ex.toString());
       }
      }
     }
     return validDestBean;
    }


    QList<FacingProtecting*> LayoutBlockConnectivityTools::generateBlocksWithBeans(LayoutEditor* editor, QString T){
        LayoutBlockManager* lbm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"));
        QList<FacingProtecting*> beanList =  QList<FacingProtecting*>();

        QStringList lblksSysName = lbm->getSystemNameList();
        for(int i = 0; i<lblksSysName.size(); i++){
            LayoutBlock* curLblk = lbm->getLayoutBlock(lblksSysName.at(i));
            Block* curBlk = curLblk->getBlock();
            if(curBlk!=NULL){
                int noNeigh = curLblk->getNumberOfNeighbours();
                for(int x = 0; x<noNeigh; x++){
                    Block* blk = curLblk->getNeighbourAtIndex(x);

                    if(T=="") {
                        NamedBean* sourceBean = lbm->getFacingNamedBean(curBlk, blk, editor);
                        if(sourceBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, blk, sourceBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                        }
                    } else if (T==("SignalMast")){
                        NamedBean* sourceBean = (NamedBean*)lbm->getFacingSignalMast(curBlk, blk, editor);
                        if(sourceBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, blk, sourceBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                        }
                    } else if (T==("Sensor")){
                        NamedBean* sourceBean = lbm->getFacingSensor(curBlk, blk, editor);
                        if(sourceBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, blk, sourceBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                        }
                    }  else {
                        log->error("Past bean type is unknown " + T);
                    }
                }
                if (noNeigh==1){
                    if(log->isDebugEnabled())
                        log->debug("We have a dead end " + curBlk->getDisplayName());
                    if(T==NULL){
                        NamedBean* destBean = lbm->getNamedBeanAtEndBumper(curBlk, editor);
                        if(destBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, NULL, destBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                            if(log->isDebugEnabled())
                                log->debug("We have found dest bean " + destBean->getDisplayName());
                        }
                    } else if (T==("SignalMast")){
                        NamedBean* destBean = (NamedBean*)lbm->getSignalMastAtEndBumper(curBlk, editor);
                        if(destBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, NULL, destBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                            if(log->isDebugEnabled())
                                log->debug("We have found dest bean " + destBean->getDisplayName());
                        }
                    } else if (T==("Sensor")){
                        NamedBean* sourceBean = lbm->getSensorAtEndBumper(curBlk, editor);
                        if(sourceBean!=NULL){
                            FacingProtecting* toadd = new FacingProtecting(curBlk, NULL, sourceBean);
                            if(!beanList.contains(toadd)){
                                beanList.append(toadd);
                            }
                        }
                    } else {
                        log->error("Past bean type is unknown " + T);
                    }
                }
            }
        }
        return beanList;
    }


//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutBlockConnectivityTools.class.getName());

//}
#endif
