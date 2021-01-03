#include "destinationpoints.h"
#include "source.h"
#include "pointdetails.h"
#include "entryexitpairs.h"
#include "instancemanager.h"
#include <QUuid>
#include "../LayoutEditor/layoutblockmanager.h"
#include "signalmastlogic.h"
#include "defaultsignalmastlogic.h"
#include "abstractsignalmast.h"
#include "abstractsignalmast.h"
#include <QMessageBox>
#include "joptionpane.h"
#include "../operations/activetrain.h"
#include "../operations/dispatcherframe.h"
#include "layoutblock.h"
#include "connectivityutil.h"
#include <QPushButton>
#include "jlabel.h"
#include "jpanel.h"
#include <QStyle>
#include "sleeperthread.h"
#include "signalmastlogicmanager.h"
#include "runtimeexception.h"
#include "signalmast.h"
#include "signalhead.h"

//DestinationPoints::DestinationPoints(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/*final*/ /*static*/ int DestinationPoints::NXMESSAGEBOXCLEARTIMEOUT = 30;

///*public*/ class DestinationPoints extends jmri.implementation.AbstractNamedBean{


bool DestinationPoints::isEnabled(){
    return enabled;
}

void DestinationPoints::setEnabled(bool boo){
    //bool oldEnabled = enabled;
    //Need to do other bits when enabling
    enabled = boo;

    // Modify source signal mast held state
    Sensor* sourceSensor = src->getPoint()->getSensor();
    if (sourceSensor == nullptr) {
        return;
    }
    SignalMast* sourceMast = src->getPoint()->getSignalMast();
    if (sourceMast == nullptr) {
        return;
    }
    if (enabled) {
        sourceMast->setHeld(true);
    } else {
        // All destinations for the source must be disabled before the mast hold can be released
        for (PointDetails* pd : src->getDestinationPoints()) {
            if (src->getDestForPoint(pd)->isEnabled()) {
                return;
            }
        }
        sourceMast->setHeld(false);
    }
}


DestinationPoints::DestinationPoints(PointDetails* point, QString id, Source* src, QObject *parent)
 : AbstractNamedBean(id, parent)
{
    //super(id);
    entryExitType = EntryExitPairs::SETUPTURNOUTSONLY;//SETUPSIGNALMASTLOGIC;
    uniDirection = true;
    enabled = true;
    activeEntryExit = false;
    routeDetails =  QList<LayoutBlock*>();
    disposed = false;
    uniqueId = "";
    manager = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");
    threadAutoClearFrame = NULL;
    log = new Logger("DestinationPoints");
    jButton_Stack = new QPushButton(tr("Stack"));  // NOI18N

    this->src = src;
    this->point=point;
    if(id==NULL){
        //uniqueId = UUID.randomUUID().toString();
        uniqueId = "IN:"+ QUuid::createUuid().toString(QUuid::WithoutBraces);
        mSystemName = uniqueId;
    } else {
        uniqueId = id;
    }
    mUserName = (src->getPoint()->getDisplayName() + " to " + this->point->getDisplayName());

//    propertyBlockListener = new PropertyChangeListener() {
//        /*public*/ void propertyChange(PropertyChangeEvent e) {
//            blockStateUpdated(e);
//        }
//    };
    setObjectName(mSystemName);
}
void DestinationPoints::propertyBlockListener(PropertyChangeEvent* e) // SLOT[]
{
 blockStateUpdated(e);
}

/*public*/ QString DestinationPoints::getDisplayName(){
    return mSystemName;
}

QString DestinationPoints::getUniqueId(){
    return uniqueId;
}

PointDetails* DestinationPoints::getDestPoint(){
    return point;
}

/**
 * @since 4.17.4
 * Making the source object available for scripting in Jython.
 */
/*public*/ Source* DestinationPoints::getSource() {
    return src ;
}

bool DestinationPoints::getUniDirection(){
    return uniDirection;
}

void DestinationPoints::setUniDirection(bool uni){
    uniDirection = uni;
}

NamedBean* DestinationPoints::getSignal(){
    return point->getSignal();
}

void DestinationPoints::setRouteTo(bool set) {
    if(set && getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
        point->setRouteTo(true);
        point->setNXButtonState( EntryExitPairs::NXBUTTONACTIVE);
    } else {
        point->setRouteTo(false);
        point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
    }
}

void DestinationPoints::setRouteFrom(bool set){
    if(set && getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
        src->pd->setRouteFrom(true);
        src->pd->setNXButtonState(EntryExitPairs::NXBUTTONACTIVE);
    } else {
        src->pd->setRouteFrom(false);
        src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
    }
}

bool DestinationPoints::isRouteToPointSet()
{
 return point->isRouteToPointSet();
}

LayoutBlock* DestinationPoints::getFacing()
{
 return point->getFacing();
}

QList<LayoutBlock*> DestinationPoints::getProtecting()
{
 return point->getProtecting();
}

int DestinationPoints::getEntryExitType(){
    return entryExitType;
}

void DestinationPoints::setEntryExitType(int type){
    entryExitType = type;
    if((type!=EntryExitPairs::SETUPTURNOUTSONLY) && (getSignal()!=NULL) && point->getSignal()!=NULL)
        uniDirection = true;
}
#if 1
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SE_TRANSIENT_FIELD_NOT_RESTORED",
//                                                    justification="No auto serialization")
// /*transient*/ /*protected*/ PropertyChangeListener propertyBlockListener;

/* = new PropertyChangeListener() {*/
    /*public*/ void DestinationPoints::propertyChangeListener(PropertyChangeEvent* e)
{
        Block* blk = (Block*) e->getSource();
        if (e->getPropertyName()==("state")) {
            if (log->isDebugEnabled()) log->debug(mUserName + "  We have a change of state on the block " + blk->getDisplayName());
            int now =  e->getNewValue().toInt();

            if (now==Block::OCCUPIED){
                LayoutBlock* lBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(blk);
                //If the block was previously active or inactive then we will
                //reset the useExtraColor, but not if it was previously unknown or inconsistent.
                lBlock->setUseExtraColor(false);
                //blk.removePropertyChangeListener(propertyBlockListener); //was this
                disconnect(lBlock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
                removeBlockFromRoute(lBlock);
            } else {
                if (log->isDebugEnabled()) log->debug("state was " + QString::number(now) + " and did not go through reset");
            }
        }
    }
//};*/
#endif

/*protected*/ void DestinationPoints::blockStateUpdated(PropertyChangeEvent* e)
{
 Block* blk = (Block*) e->getSource();
 if (e->getPropertyName()==("state"))
 {
  if (log->isDebugEnabled()) log->debug(mUserName + "  We have a change of state on the block " + blk->getDisplayName());
  int now =  e->getNewValue().toInt();

  if (now == Block::OCCUPIED)
  {
   LayoutBlock* lBlock = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(blk);
   //If the block was previously active or inactive then we will
   //reset the useExtraColor, but not if it was previously unknown or inconsistent.
   lBlock->setUseExtraColor(false);
   //blk->removePropertyChangeListener(propertyBlockListener); //was this
   disconnect(blk, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
   removeBlockFromRoute(lBlock);
  } else {
      if (log->isDebugEnabled())
       log->debug("state was " + QString::number(now) + " and did not go through reset");
  }
 }
}


/*synchronized*/ void DestinationPoints::removeBlockFromRoute(LayoutBlock* lBlock)
{
 if (!routeDetails.isEmpty())
 {
  if(routeDetails.indexOf(lBlock)==-1)
  {
   if(src->getStart() == lBlock)
   {
    log->debug("Start block went active");
    lastSeenActiveBlockObject = src->getStart()->getBlock()->getValue();
    //lBlock->getBlock().removePropertyChangeListener(propertyBlockListener);
    Block* blk = lBlock->getBlock();
    disconnect(blk, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
    return;
   }
   else {
       log->error("Block " + lBlock->getDisplayName() + " went active but it is not part of our NX path");
   }
  }
  if(routeDetails.indexOf(lBlock)!=0)
  {
   log->debug("A block has been skipped will set the value of the active block to that of the original one");
   lBlock->getBlock()->setValue(lastSeenActiveBlockObject);
   if(routeDetails.indexOf(lBlock)!=-1)
   {
    while(routeDetails.indexOf(lBlock)!=0)
    {
     LayoutBlock* tbr = routeDetails.at(0);
     log->debug("Block skipped " + tbr->getDisplayName() + " and removed from list");
     //tbr->getBlock().removePropertyChangeListener(propertyBlockListener);
     Block* b = tbr->getBlock();
     disconnect(b, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
     tbr->setUseExtraColor(false);
     routeDetails.removeAt(0);
    }
   }
  }
  if(routeDetails.contains(lBlock))
  {
   routeDetails.removeOne(lBlock);
   setRouteFrom(false);
   src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
   if(sml!=NULL && getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
       ((AbstractSignalMast*)((DefaultSignalMastLogic*)sml)->getSourceMast())->setHeld(true);
       SignalMast* mast = (SignalMast*) getSignal();
       if (((DefaultSignalMastLogic*)sml)->getStoreState(mast)==SignalMastLogic::STORENONE)
           ((DefaultSignalMastLogic*)sml)->removeDestination(mast);
   }
  } else {
      log->error("Block " + lBlock->getDisplayName() + " that went Occupied was not in the routeDetails list");
  }
  if (log->isDebugEnabled()){
      log->debug("Route details contents " + QString::number(routeDetails.size()));
      for(int i = 0; i<routeDetails.size(); i++){
          log->debug("      " + routeDetails.at(i)->getDisplayName());
      }
  }
  if((routeDetails.size()==1) && (routeDetails.contains(destination)))
  {
      //routeDetails.at(0)->getBlock().removePropertyChangeListener(propertyBlockListener);  // was set against block sensor
      Block* b = routeDetails.at(0)->getBlock();
      disconnect(b, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
      routeDetails.removeOne(destination);
  }
 }
 lastSeenActiveBlockObject = lBlock->getBlock()->getValue();

 if((routeDetails.isEmpty())||(routeDetails.size()==0)){
     //At this point the route has cleared down/the last remaining block are now active.
     routeDetails=QList<LayoutBlock*>();
     setRouteTo(false);
     setRouteFrom(false);
     setActiveEntryExit(false);
     lastSeenActiveBlockObject = QVariant();
 }
}

//For a clear down we need to add a message, if it is a cancel, manual clear down or I didn't mean it.
void DestinationPoints::setRoute(bool state){
 if (log->isDebugEnabled()) {
     log->debug("Set route " + src->getPoint()->getDisplayName());  // NOI18N
 }
 if(disposed){
     log->error("Set route called even though interlock has been disposed of");
     return;
 }

 if(routeDetails.isEmpty())
 {
  log->error ("No route to set or clear down");
  setActiveEntryExit(false);
  setRouteTo(false);
  setRouteFrom(false);
  //if((getSignal() instanceof SignalMast) && (getEntryExitType()!=EntryExitPairs::FULLINTERLOCK))
  if(qobject_cast<SignalMast*>(getSignal())!= NULL && (getEntryExitType()!=EntryExitPairs::FULLINTERLOCK))
  {
   SignalMast* mast = (SignalMast*) getSignal();
         ((AbstractSignalMast*)mast)->setHeld(false);
     }
     /*synchronized(this)*/{
         QMutexLocker locker(&mutex);
         destination=NULL;
     }
     return;
 }
 if(!state)
 {
     switch(manager->getClearDownOption())
     {
      case EntryExitPairs::PROMPTUSER : cancelClearOptionBox(); break;
      case EntryExitPairs::AUTOCANCEL : cancelClearInterlock(EntryExitPairs::CANCELROUTE); break;
      case EntryExitPairs::AUTOCLEAR  : cancelClearInterlock(EntryExitPairs::CLEARROUTE); break;
      case EntryExitPairs::AUTOSTACK:
       cancelClearInterlock(EntryExitPairs::STACKROUTE);
       break;
      default         : cancelClearOptionBox(); break;
     }
     if (log->isDebugEnabled())
     {
      log->debug("Exit " + src->getPoint()->getDisplayName());
     }
     return;
 }
 if (manager->isRouteStacked(this, false)) {
     manager->cancelStackedRoute(this, false);
 }
 /*We put the setting of the route into a seperate thread and put a glass pane infront of the layout editor,
 the swing thread for flash the icons to carry on as without interuption */
 /*final*/ QList<QColor> realColorStd = QList<QColor>();
 /*final*/ QList<QColor> realColorXtra = QList<QColor>();
 /*final*/ QList<LayoutBlock*> routeBlocks = QList<LayoutBlock*>();
 if (manager->useDifferentColorWhenSetting()) {
     bool first = true;
     for (LayoutBlock* lbk : routeDetails) {
         if (first) {
             // Don't change the color for the facing block
             first = false;
             continue;
         }
         routeBlocks.append(lbk);
         realColorXtra.append(lbk->getBlockExtraColor());
         realColorStd.append(lbk->getBlockTrackColor());
         lbk->setBlockExtraColor(manager->getSettingRouteColor());
         lbk->setBlockTrackColor(manager->getSettingRouteColor());
     }
     //Force a redraw, to reflect color change
     src->getPoint()->getPanel()->redrawPanel();
 }
 ActiveTrain* tmpat = nullptr;
 if (manager->getDispatcherIntegration() &&  InstanceManager::getNullableDefault("DispatcherFrame") != nullptr) {
     DispatcherFrame* df = static_cast<DispatcherFrame*>(InstanceManager::getDefault("DispatcherFrame"));
     for (ActiveTrain* atl : *df->getActiveTrainsList()) {
         if (atl->getEndBlock() == src->getStart()->getBlock()) {
             if (atl->getLastAllocatedSection() == atl->getEndBlockSection()) {
                 if (!atl->getReverseAtEnd() && !atl->getResetWhenDone()) {
                     tmpat = atl;
                     break;
                 }
                 log->warn("Interlock will not be added to existing Active Train as it is set for back and forth operation");  // NOI18N
             }
         }
     }
  }
  /*final*/ ActiveTrain* at = tmpat;
  DPRunnable* setRouteRun = new DPRunnable(this);
  QThread* thrMain = new QThread(setRouteRun);
  thrMain->setObjectName( "Entry Exit Set Route");
  thrMain->start();
 }
 //Runnable setRouteRun = new Runnable() {
 DPRunnable::DPRunnable(DestinationPoints *p)
 {
     this->p = p;
 }
 /*public*/ void DPRunnable::run()
 {
 // TODO:
 #if 1
  p->src->getPoint()->getPanel()->getGlassPane()->setVisible(true);
  try
  {
   QHash<Turnout*, int> turnoutSettings = QHash<Turnout*, int>();

   ConnectivityUtil* connection = new ConnectivityUtil(p->point->getPanel());

   //This for loop was after the if statement
   //Last block in the route is the one that we are protecting at the last sensor/signalmast
   for (int i = 0; i<p->routeDetails.size(); i++)
   {
    if (i>0) {
        QList<LayoutTrackExpectedState<LayoutTurnout*>* > turnoutlist;
        int nxtBlk = i+1;
        int preBlk = i-1;
        /*if (i==routeDetails.size()-1){
            nxtBlk = i;
        } else*/ if (i==0){
            preBlk=i;
        }
        if(i<p->routeDetails.size()-1){
            //log->info(routeDetails.get(i).getBlock().getDisplayName() + " " + routeDetails.get(preBlk).getBlock().getDisplayName() + " " + routeDetails.get(nxtBlk).getBlock().getDisplayName());
            turnoutlist=connection->getTurnoutList(p->routeDetails.at(i)->getBlock(), p->routeDetails.at(preBlk)->getBlock(), p->routeDetails.at(nxtBlk)->getBlock());
            QVector<int>* throwlist = connection->getTurnoutSettingList();
            for (int x=0; x<turnoutlist.size(); x++)
            {
                if(qobject_cast<LayoutSlip*>(turnoutlist.at(x)->getObject())){
                    int slipState = throwlist->at(x);
                    LayoutSlip* ls = (LayoutSlip*)turnoutlist.at(x)->getObject();
                    int taState = ls->getTurnoutState(slipState);
                    ls->getTurnout()->setCommandedState(taState);
                    turnoutSettings.insert(ls->getTurnout(), taState);
//                    Runnable r = new Runnable() {
//                      /*public*/ void run() {
//                        try {
//                            Thread.sleep(250 + manager.turnoutSetDelay);
//                        } catch (InterruptedException ex) {
//                            Thread.currentThread().interrupt();
//                        }
//                      }
//                    };
//                    Thread thr = new Thread(r, "Entry Exit Route, turnout setting");
//                    thr.start();
//                    try{
//                        thr.join();
//                    } catch (InterruptedException ex) {
//            //            log->info("interrupted at join " + ex);
//                    }
                    SleeperThread::msleep(250 + p->manager->turnoutSetDelay);
                    int tbState = ls->getTurnoutBState(slipState);
                    ls->getTurnoutB()->setCommandedState(tbState);
                    turnoutSettings.insert(ls->getTurnoutB(), tbState);
                } else {
                    QString t = turnoutlist.at(x)->getObject()->getTurnoutName();
                    Turnout* turnout = InstanceManager::turnoutManagerInstance()->getTurnout(t);
                    turnout->setCommandedState(throwlist->at(x));
                    turnoutSettings.insert(turnout, throwlist->at(x));
                }
//                Runnable r = new Runnable() {
//                  /*public*/ void run() {
//                    try {
//                        Thread.sleep(250 + manager.turnoutSetDelay);
//                    } catch (InterruptedException ex) {
//                        Thread.currentThread().interrupt();
//                    }
//                  }
//                };
//                Thread thr = new Thread(r, "Entry Exit Route, turnout setting");
//                thr.start();
//                try{
//                    thr.join();
//                } catch (InterruptedException ex) {
//        //            log->info("interrupted at join " + ex);
//                }
                SleeperThread::msleep(250 + p->manager->turnoutSetDelay);
            }
        }
        if(p->getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
            p->routeDetails.at(i)->setUseExtraColor(true);
        }
    }
    if ((p->getEntryExitType()==EntryExitPairs::FULLINTERLOCK)){
            //p->routeDetails.at(i)->getBlock().addPropertyChangeListener(propertyBlockListener); // was set against occupancy sensor
     connect(p->routeDetails.at(i)->getBlock()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), p, SLOT(propertyBlockListener(PropertyChangeEvent*)));
    } else {
        //routeDetails.get(i).getBlock().removePropertyChangeListener(propertyBlockListener); // was set against occupancy sensor
     disconnect(p->routeDetails.at(i)->getBlock()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), p, SLOT(propertyBlockListener(PropertyChangeEvent*)));

    }
 }

 //Force a redraw
 p->src->getPoint()->getPanel()->redrawPanel();
 if (p->getEntryExitType()!=EntryExitPairs::SETUPTURNOUTSONLY){
    if(p->getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
        //If our start block is already active we will set it as our lastSeenActiveBlock.
        if(p->src->getStart()->getState()==Block::OCCUPIED){
            //p->src->getStart().removePropertyChangeListener(p->propertyBlockListener);
         disconnect(p->src->getStart()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), p, SLOT(propertyChangeListener(PropertyChangeEvent*)));
            p->lastSeenActiveBlockObject = p->src->getStart()->getBlock()->getValue();
            p->log->debug("Last seen value " + p->lastSeenActiveBlockObject.toString());
        }
    }
    //if((src->sourceSignal instanceof SignalMast) && (getSignal() instanceof SignalMast))
    if(qobject_cast<SignalMast*>(p->src->sourceSignal) && qobject_cast<SignalMast*>(p->getSignal()))
    {
        SignalMast* smSource = (SignalMast*) p->src->sourceSignal;
        SignalMast* smDest = (SignalMast*) p->getSignal();
        /*synchronized(this)*/{
            p->sml = ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->newSignalMastLogic(smSource);
            if(!p->sml->isDestinationValid(smDest)){
                //if no signalmastlogic existed then created it, but set it not to be stored.
                p->sml->setDestinationMast(smDest);
                p->sml->setStore(SignalMastLogic::STORENONE, smDest);
            }
        }
        //LinkedHashMap<Block, Integer> blks = new LinkedHashMap<Block, Integer>();
        QMap<Block*, int> blks = QMap<Block*, int>();
        //Remove the first block as it is our start block
        p->routeDetails.removeAt(0);
        for(int i = 0; i<p->routeDetails.size(); i++){
            if (p->routeDetails.at(i)->getBlock()->getState()==Block::UNKNOWN)
                p->routeDetails.at(i)->getBlock()->setState(Block::UNOCCUPIED);
            blks.insert(p->routeDetails.at(i)->getBlock(), Block::UNOCCUPIED);
        }
        /*synchronized(this)*/{
            smSource->setHeld(false);
            p->sml->setAutoBlocks(blks, smDest);
            p->sml->setAutoTurnouts(turnoutSettings, smDest);
            p->sml->initialise(smDest);
        }
//        smSource.addPropertyChangeListener( new PropertyChangeListener() {
//            /*public*/ void propertyChange(PropertyChangeEvent e) {
//                SignalMast source = (SignalMast)e.getSource();
//                source.removePropertyChangeListener(this);
//                setRouteFrom(true);
//                setRouteTo(true);
//            }
//        });
        connect(smSource->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChangeListener(PropertyChangeEvent*)));

        p->src->pd->extendedtime=true;
        p->point->extendedtime=true;
    } else {
        if (qobject_cast<SignalMast*>(p->src->sourceSignal)){
            SignalMast* mast = (SignalMast*) p->src->sourceSignal;
            mast->setHeld(false);
        }
        //else if (src->sourceSignal instanceof SignalHead){
        else if (qobject_cast<SignalHead*>(p->src->sourceSignal)){
    SignalHead* head = (SignalHead*) p->src->sourceSignal;
            head->setHeld(false);
        }
        p->setRouteFrom(true);
        p->setRouteTo(true);
    }
  } else {
      p->src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
      p->point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
  }
 } catch (RuntimeException ex) {
  p->log->error("An error occured while setting the route");
//  ex.printStackTrace();
  p->src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
  p->point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
 }
 p->src->getPoint()->getPanel()->getGlassPane()->setVisible(false);
 p->src->setMenuEnabled(true);
#endif
}
//};

 /*public*/ void DestinationPoints::propertyChange(PropertyChangeEvent* e) {
     SignalMast* source = (SignalMast*)e->getSource();
     //source.removePropertyChangeListener(this);
     disconnect(source->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChangeListener(PropertyChangeEvent*)));
     setRouteFrom(true);
     setRouteTo(true);
 }
#if 0
 /**
      * Remove the hold on the mast when all of the turnouts have completed moving.
      * This only applies to turnouts using ONESENSOR feedback.  TWOSENSOR has an
      * intermediate inconsistent state which prevents erroneous signal aspects.
      * The maximum wait time is 10 seconds.
      *
      * @since 4.11.1
      * @param mast The signal mast that will be released.
      * @param turnoutSettings The turnouts that are being set for the current NX route.
      */
     private void releaseMast(SignalMast mast, Hashtable<Turnout, Integer> turnoutSettings) {
         Hashtable<Turnout, Integer> turnoutList = new Hashtable<>(turnoutSettings);
         Runnable r = new Runnable() {
             @Override
             public void run() {
                 try {
                     for (int i = 20; i > 0; i--) {
                         int active = 0;
                         for (Map.Entry< Turnout, Integer> entry : turnoutList.entrySet()) {
                             Turnout tout = entry.getKey();
                             if (tout.getFeedbackMode() == Turnout.ONESENSOR) {
                                 // Check state
                                 if (tout.getKnownState() != tout.getCommandedState()) {
                                     active += 1;
                                 }
                             }
                         }
                         if (active == 0) {
                             break;
                         }
                         Thread.sleep(500);
                     }
                     log.debug("Release mast: {}", mast.getDisplayName());
                     mast.setHeld(false);
                 } catch (InterruptedException ex) {
                     Thread.currentThread().interrupt();
                 }
             }
         };
         Thread thr = new Thread(r, "Entry Exit Route: Release Mast");  // NOI18N
         thr.start();
     }

     private boolean isSignalLogicDynamic() {
         if ((src.sourceSignal instanceof SignalMast) && (getSignal() instanceof SignalMast)) {
             SignalMast smSource = (SignalMast) src.sourceSignal;
             SignalMast smDest = (SignalMast) getSignal();
             if (InstanceManager.getDefault(jmri.SignalMastLogicManager.class).getSignalMastLogic(smSource) != null
                     && InstanceManager.getDefault(jmri.SignalMastLogicManager.class).getSignalMastLogic(smSource).getStoreState(smDest) != jmri.SignalMastLogic.STORENONE) {
                 return false;
             }
         }
         return true;

     }
#endif
void DestinationPoints::cancelClearOptionBox()
{
    if(cancelClearFrame==NULL){
        QPushButton* jButton_Clear = new QPushButton("Clear Down");
        QPushButton* jButton_Cancel = new QPushButton("Cancel");
        QPushButton* jButton_Exit = new QPushButton("Exit");
        QLabel* jLabel = new QLabel("What would you like to do with this interlock?");
        QLabel* jIcon = new QLabel(); //cancelClearFrame->style()->standardIcon(QStyle::SP_MessageBoxQuestion)); //javax.swing.UIManager.getIcon("OptionPane.questionIcon"));
        QIcon icon = cancelClearFrame->style()->standardIcon(QStyle::SP_MessageBoxQuestion);
        QSize iconSize = icon.actualSize(QSize(64,64));
        jIcon->setPixmap(icon.pixmap(iconSize));
        cancelClearFrame = new JFrame("Interlock");
        QWidget* cont = cancelClearFrame->getContentPane();
        QVBoxLayout* contLayout = new QVBoxLayout(cont);
        JPanel* qPanel = new JPanel();
        QHBoxLayout* qPanelLayout = new QHBoxLayout(qPanel);
        qPanelLayout->addWidget(jIcon);
        qPanelLayout->addWidget(jLabel);
        contLayout->addWidget(qPanel,0, Qt::AlignCenter); //BorderLayout.CENTER);
        JPanel* buttonsPanel = new JPanel();
        FlowLayout* buttonsPanelLayout = new FlowLayout(buttonsPanel);
        buttonsPanelLayout->addWidget(jButton_Cancel);
        buttonsPanelLayout->addWidget(jButton_Clear);
        buttonsPanelLayout->addWidget(jButton_Exit);
        contLayout->addWidget(buttonsPanel,0, Qt::AlignBottom);// BorderLayout.SOUTH);
        cancelClearFrame->pack();

//        jButton_Clear.addActionListener( new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        cancelClearFrame.setVisible(false);
//                        threadAutoClearFrame.interrupt();
//                        cancelClearInterlock(EntryExitPairs::CLEARROUTE);
//                    }
//                });
//        jButton_Cancel.addActionListener( new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        cancelClearFrame.setVisible(false);
//                        threadAutoClearFrame.interrupt();
//                        cancelClearInterlock(EntryExitPairs::CANCELROUTE);
//                    }
//                });
//        jButton_Exit.addActionListener( new ActionListener() {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        cancelClearFrame.setVisible(false);
//                        threadAutoClearFrame.interrupt();
//                        cancelClearInterlock(EntryExitPairs::EXITROUTE);
//                    }
//                });
        src->getPoint()->getPanel()->setGlassPane(manager->getGlassPane());
    }
    cancelClearFrame->setTitle(getUserName());
    if (manager->isRouteStacked(this, false)) {
        jButton_Stack->setEnabled(false);
    } else {
        jButton_Stack->setEnabled(true);
    }

    if(cancelClearFrame->isVisible()){
     return;
    }
    src->pd->extendedtime=true;
    point->extendedtime =true;

    MessageTimeOut* mt = new MessageTimeOut(this);
//    threadAutoClearFrame = new Thread(mt, "NX Button Clear Message Timeout ");
//    threadAutoClearFrame->start();
    mt->start();
    cancelClearFrame->setAlwaysOnTop(true);
    src->getPoint()->getPanel()->getGlassPane()->setVisible(true);
    int w = cancelClearFrame->size().width();
    int h = cancelClearFrame->size().height();
    int x = (int)src->getPoint()->getPanel()->getLocation().x()+((src->getPoint()->getPanel()->size().width()-w)/2);
    int y = (int)src->getPoint()->getPanel()->getLocation().y()+((src->getPoint()->getPanel()->size().height()-h)/2);
    cancelClearFrame->setLocation(x, y);
    cancelClearFrame->setVisible(true);
}

void DestinationPoints::on_jButton_Clear()
{
 cancelClearFrame->setVisible(false);
 threadAutoClearFrame->terminate();//interrupt();
 cancelClearInterlock(EntryExitPairs::CLEARROUTE);
}

void DestinationPoints::on_jButton_Cancel() {
 cancelClearFrame->setVisible(false);
 threadAutoClearFrame->terminate(); //interrupt();
 cancelClearInterlock(EntryExitPairs::CANCELROUTE);
}

void DestinationPoints::on_jButton_Exit() {
    cancelClearFrame->setVisible(false);
    threadAutoClearFrame->terminate(); //interrupt();
    cancelClearInterlock(EntryExitPairs::EXITROUTE);
}

void DestinationPoints::cancelClearInterlock(int cancelClear)
{

 if (cancelClear==EntryExitPairs::EXITROUTE || (cancelClear == EntryExitPairs::STACKROUTE))
 {
  src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
  point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
//  src->getPoint()->getPanel()->getGlassPane().setVisible(false);
  if (cancelClear == EntryExitPairs::STACKROUTE) {
      manager->stackNXRoute(this, false);
  }
  return;
 }
 src->setMenuEnabled(false);
 //if (src->sourceSignal instanceof SignalMast){
 if(qobject_cast<SignalMast*>(src->sourceSignal)  != NULL)
 {
  SignalMast* mast = (SignalMast*) src->sourceSignal;
  mast->setAspect(mast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER));
  mast->setHeld(true);
 }
 //else if (src->sourceSignal instanceof SignalHead){
 else if(qobject_cast<SignalHead*>(src->sourceSignal)!= NULL)
 {
  SignalHead* head = (SignalHead*) src->sourceSignal;
  head->setHeld(true);
 }
 else
 {
  log->debug("No signal found");
 }

 //Get rid of the signal mast logic to the destination mast.
// synchronized(this)
 {
  //if((getSignal() instanceof SignalMast) && (sml!=NULL)){
  if(qobject_cast<SignalMast*>(getSignal())!= NULL)
  {
   SignalMast* mast = (SignalMast*) getSignal();
   if (sml->getStoreState(mast)==SignalMastLogic::STORENONE)
    sml->removeDestination(mast);
  }
  sml = NULL;
 }

 if(routeDetails.isEmpty())
 {
  return;
 }

 foreach(LayoutBlock* blk, routeDetails)
 {
  if((getEntryExitType()==EntryExitPairs::FULLINTERLOCK))
  {
   blk->setUseExtraColor(false);
  }
//  blk->getBlock()->removePropertyChangeListener((PropertyChangeListener*)propertyBlockListener); // was set against occupancy sensor
 }

 if (cancelClear == EntryExitPairs::CLEARROUTE)
 {
  if (routeDetails.size()==0)
  {
   if (log->isDebugEnabled()) log->debug(mUserName + "  all blocks have automatically been cleared down");
  }
  else
  {
   if (log->isDebugEnabled()) log->debug(mUserName + "  No blocks were cleared down " + QString::number(routeDetails.size()));
   try{
    if (log->isDebugEnabled()) log->debug(mUserName + "  set first block as active so that we can manually clear this down " + routeDetails.at(0)->getBlock()->getSensor()->getDisplayName());
    if(routeDetails.at(0)->getBlock()->getSensor()!=NULL)
     routeDetails.at(0)->getBlock()->getSensor()->setState(Sensor::ACTIVE);
    if(src->getStart()->getBlock()->getSensor()!=NULL)
     src->getStart()->getBlock()->getSensor()->setState(Sensor::INACTIVE);
    }
   catch (NullPointerException e)
   {
    log->error("error in clear route A " + e.getMessage());
   }
   catch (JmriException e)
   {
    log->error("error in clear route A " + e.getMessage());
   }
   if (log->isDebugEnabled())
   {
    log->debug(mUserName + "  Going to clear routeDetails down " + QString::number(routeDetails.size()));
    for(int i = 0; i<routeDetails.size(); i++)
    {
     log->debug("Block at " + QString::number(i) + " " + routeDetails.at(i)->getDisplayName());
    }
   }
   if(routeDetails.size()>1)
   {
    //We will remove the propertychange listeners on the sensors as we will now manually clear things down.
    //Should we just be usrc->pdating the block status and not the sensor
    for (int i = 1; i <routeDetails.size()-1; i++)
    {
     if (log->isDebugEnabled()) log->debug(mUserName + " in loop Set active " + routeDetails.at(i)->getDisplayName() + " " + routeDetails.at(i)->getBlock()->getSystemName());
     try{
      if(routeDetails.at(i)->getOccupancySensor()!=NULL)
       routeDetails.at(i)->getOccupancySensor()->setState(Sensor::ACTIVE); //was getBlock().getSensor()
      routeDetails.at(i)->getBlock()->goingActive();

     if (log->isDebugEnabled()) log->debug(mUserName + " in loop Set inactive " + routeDetails.at(i-1)->getDisplayName() + " " + routeDetails.at(i-1)->getBlock()->getSystemName());
     if(routeDetails.at(i-1)->getOccupancySensor()!=NULL)
      routeDetails.at(i-1)->getOccupancySensor()->setState(Sensor::INACTIVE); //was getBlock().getSensor()
     routeDetails.at(i-1)->getBlock()->goingInactive();
    }
     catch (NullPointerException e)
     {
      log->error("error in clear route b " + e.getMessage());
      //e.printStackTrace();
     }
     catch (JmriException e)
     {
      log->error("error in clear route b " + e.getMessage());
     }
    }
    try{
     if (log->isDebugEnabled()) log->debug(mUserName + " out of loop Set active " + routeDetails.at(routeDetails.size()-1)->getDisplayName() + " " + routeDetails.at(routeDetails.size()-1)->getBlock()->getSystemName());
     //Get the last block an set it active.
     if(routeDetails.at(routeDetails.size()-1)->getOccupancySensor()!=NULL)
      routeDetails.at(routeDetails.size()-1)->getOccupancySensor()->setState(Sensor::ACTIVE);
     if (log->isDebugEnabled()) log->debug(mUserName + " out of loop Set inactive " + routeDetails.at(routeDetails.size()-2)->getUserName() + " " + routeDetails.at(routeDetails.size()-2)->getBlock()->getSystemName());
     if(routeDetails.at(routeDetails.size()-2)->getOccupancySensor()!=NULL)
      routeDetails.at(routeDetails.size()-2)->getOccupancySensor()->setState(Sensor::INACTIVE);
     }
    catch (NullPointerException e)
    {
     log->error("error in clear route c " +e.getMessage());
    }
    catch (ArrayIndexOutOfBoundsException e)
    {
     log->error("error in clear route c " +e.getMessage());
    }
    catch (JmriException e)
    {
     log->error("error in clear route c " +e.getMessage());
    }
   }
  }
 }
 setActiveEntryExit(false);
 setRouteFrom(false);
 setRouteTo(false);
 routeDetails = QList<LayoutBlock*>();
// synchronized(this)
 {
     lastSeenActiveBlockObject = QVariant();
 }
 src->pd->cancelNXButtonTimeOut();
 point->cancelNXButtonTimeOut();
 src->getPoint()->getPanel()->getGlassPane()->setVisible(false);

}
/*public*/ void DestinationPoints::setInterlockRoute(bool reverseDirection) {
    if (activeEntryExit) {
        return;
    }
    activeBean(reverseDirection, false);
}

void DestinationPoints::activeBean(bool reverseDirection)
{
 activeBean(reverseDirection, true);
}

/*synchronized*/ void DestinationPoints::activeBean(bool reverseDirection, bool showMessage)
{
 if (!isEnabled())
 {
     JOptionPane::showMessageDialog(nullptr, tr("NX Pair, \"%1\", is disabled.\nUnable to allocate route.").arg( getDisplayName()));  // NOI18N
     src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
     point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
     return;
 }
 if (activeEntryExit) {
     // log.debug(getUserName() + "  Our route is active so this would go for a clear down but we need to check that the we can clear it down" + activeEndPoint);
     if (!isEnabled()) {
         log->debug("A disabled entry exit has been called will bomb out");  // NOI18N
         return;
     }
     log->debug(getUserName() + "  We have a valid match on our end point so we can clear down");  // NOI18N
     //setRouteTo(false);
     //src.pd.setRouteFrom(false);
     setRoute(false);
 } else {
     if (isRouteToPointSet()) {
         log->debug(getUserName() + "  route to this point is set therefore can not set another to it " /*+ destPoint.src.getPoint().getID()*/);  // NOI18N
         if (showMessage && !manager->isRouteStacked(this, false)) {
             handleNoCurrentRoute(reverseDirection, "Route already set to the destination point");  // NOI18N
         }
         src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
         point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
         return;
     } else {
         LayoutBlock* startlBlock = src->getStart();
         class BestPath {
public:
             LayoutBlock* srcProtecting = nullptr;
             LayoutBlock* srcStart = nullptr;
             LayoutBlock* destination = nullptr;

             BestPath(LayoutBlock* startPro, LayoutBlock* sourceProtecting, LayoutBlock* destinationBlock, QList<LayoutBlock*> blocks) {
                 srcStart = startPro;
                 srcProtecting = sourceProtecting;
                 destination = destinationBlock;
                 listOfBlocks = blocks;
             }

             LayoutBlock* getStartBlock() {
                 return srcStart;
             }

             LayoutBlock* getProtectingBlock() {
                 return srcProtecting;
             }

             LayoutBlock* getDestinationBlock() {
                 return destination;
             }

             QList<LayoutBlock*> listOfBlocks = QList<LayoutBlock*>(/*0*/);
             QString errorMessage = "";

             QList<LayoutBlock*> getListOfBlocks() {
                 return listOfBlocks;
             }

             void setErrorMessage(QString msg) {
                 errorMessage = msg;
             }

             QString getErrorMessage() {
                 return errorMessage;
             }
         };
         QList<BestPath*> pathList = QList<BestPath*>();//new ArrayList<BestPath>(2);
         LayoutBlock* protectLBlock;
         LayoutBlock* destinationLBlock;
         //Need to work out around here the best one.
         for (LayoutBlock* srcProLBlock : src->getSourceProtecting()) {
             protectLBlock = srcProLBlock;
             if (!reverseDirection) {
                 //We have a problem, the destination point is already setup with a route, therefore we would need to
                 //check some how that a route hasn't been set to it.
                 destinationLBlock = getFacing();
                 QList<LayoutBlock*> blocks = QList<LayoutBlock*>();
                 QString errorMessage = "";
                 try {
                     blocks = static_cast<LayoutBlockManager*>( InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->getLayoutBlocks(startlBlock, destinationLBlock, protectLBlock, false, 0x00/*jmri.jmrit.display.layoutEditor.LayoutBlockManager.MASTTOMAST*/);
                 } catch (Exception e) {
                     errorMessage = e.getMessage();
                     //can be considered normal if no free route is found
                 }
                 BestPath* toadd = new BestPath(startlBlock, protectLBlock, destinationLBlock, blocks);
                 toadd->setErrorMessage(errorMessage);
                 pathList.append(toadd);
             } else {
                 startlBlock = srcProLBlock;
                 protectLBlock = getFacing();

                 destinationLBlock = src->getStart();
                 if (log->isDebugEnabled()) {
                     log->debug("reverse set destination is set going for " + startlBlock->getDisplayName() + " " + destinationLBlock->getDisplayName() + " " + protectLBlock->getDisplayName());  // NOI18N
                 }
                 try {
                     LayoutBlock* srcPro = src->getSourceProtecting().at(0);  //Don't care what block the facing is protecting
                     //Need to add a check for the lengths of the returned lists, then choose the most appropriate
                     if (!static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(startlBlock, protectLBlock, srcPro, src->getStart(), LayoutBlockConnectivityTools::SENSORTOSENSOR)) {
                         startlBlock = getFacing();
                         protectLBlock = srcProLBlock;
                         if (log->isDebugEnabled()) {
                             log->debug("That didn't work so try  " + startlBlock->getDisplayName() + " " + destinationLBlock->getDisplayName() + " " + protectLBlock->getDisplayName());  // NOI18N
                         }
                         if (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(startlBlock, protectLBlock, srcPro, src->getStart(), LayoutBlockConnectivityTools::SENSORTOSENSOR)) {
                             log->error("No route found");  // NOI18N
                             JOptionPane::showMessageDialog(nullptr, "No Valid path found");  // NOI18N
                             src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                             point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                             return;
                         } else {
                             QList<LayoutBlock*> blocks = QList<LayoutBlock*>();
                             QString errorMessage = "";
                             try {
                                 blocks = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->getLayoutBlocks(startlBlock, destinationLBlock, protectLBlock, false, 0x00/*jmri.jmrit.display.layoutEditor.LayoutBlockManager.MASTTOMAST*/);
                             } catch (Exception e) {
                                 errorMessage = e.getMessage();
                                 //can be considered normal if no free route is found
                             }
                             BestPath* toadd = new BestPath(startlBlock, protectLBlock, destinationLBlock, blocks);
                             toadd->setErrorMessage(errorMessage);
                             pathList.append(toadd);
                         }
                     } else if (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->checkValidDest(getFacing(), srcProLBlock, srcPro, src->getStart(), LayoutBlockConnectivityTools::SENSORTOSENSOR)) {
                         //Both paths are valid, so will go for setting the shortest
                         int distance = startlBlock->getBlockHopCount(destinationLBlock->getBlock(), protectLBlock->getBlock());
                         int distance2 = getFacing()->getBlockHopCount(destinationLBlock->getBlock(), srcProLBlock->getBlock());
                         if (distance > distance2) {
                             //The alternative route is shorter we shall use that
                             startlBlock = getFacing();
                             protectLBlock = srcProLBlock;
                         }
                         QList<LayoutBlock*> blocks = QList<LayoutBlock*>();
                         QString errorMessage = "";
                         try {
                          blocks = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->getLayoutBlocks(startlBlock, destinationLBlock, protectLBlock, false, LayoutBlockConnectivityTools::NONE);
                         } catch (Exception e) {
                             //can be considered normal if no free route is found
                             errorMessage = e.getMessage();
                         }
                         BestPath* toadd = new BestPath(startlBlock, protectLBlock, destinationLBlock, blocks);
                         toadd->setErrorMessage(errorMessage);
                         pathList.append(toadd);
                     } else {
                         QList<LayoutBlock*> blocks = QList<LayoutBlock*>();
                         QString errorMessage = "";
                         try {
                             blocks = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlockConnectivityTools()->getLayoutBlocks(startlBlock, destinationLBlock, protectLBlock, false, LayoutBlockConnectivityTools::NONE);
                         } catch (Exception e) {
                             //can be considered normal if no free route is found
                             errorMessage = e.getMessage();
                         }
                         BestPath* toadd = new BestPath(startlBlock, protectLBlock, destinationLBlock, blocks);
                         toadd->setErrorMessage(errorMessage);
                         pathList.append(toadd);
                     }
                 } catch (JmriException ex) {
                     log->error("Exception " + ex.getMessage());  // NOI18N
                     if (showMessage) {
                         JOptionPane::showMessageDialog(nullptr, ex.getMessage());
                     }
                     src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                     point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                     return;
                 }
             }
         }
         if (pathList.isEmpty()) {
             log->debug("Path list empty so exiting");  // NOI18N
             return;
         }
         BestPath* pathToUse = nullptr;
         if (pathList.size() == 1) {
             if (!(pathList.at(0)->getListOfBlocks().isEmpty())) {
                 pathToUse = pathList.at(0);
             }
         } else {
             /*Need to filter out the remaining routes, in theory this should only ever be two.
              We simply pick at this stage the one with the least number of blocks as being preferred.
              This could be expanded at some stage to look at either the length or the metric*/
             int noOfBlocks = 0;
             for (BestPath* bp : pathList) {
                 if (!bp->getListOfBlocks().isEmpty()) {
                     if (noOfBlocks == 0 || bp->getListOfBlocks().size() < noOfBlocks) {
                         noOfBlocks = bp->getListOfBlocks().size();
                         pathToUse = bp;
                     }
                 }
             }
         }
         if (pathToUse == nullptr) {
             //No valid paths found so will quit
             if (pathList.at(0)->getListOfBlocks().isEmpty()) {
                 if (showMessage) {
                     //Considered normal if not a valid through path, provide an option to stack
                     handleNoCurrentRoute(reverseDirection, pathList.at(0)->getErrorMessage());
                     src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                     point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
                 }
                 return;
             }
             pathToUse = pathList.at(0);
         }
         startlBlock = pathToUse->getStartBlock();
         protectLBlock = pathToUse->getProtectingBlock();
         destinationLBlock = pathToUse->getDestinationBlock();
         routeDetails = pathToUse->getListOfBlocks();

         if (log->isDebugEnabled()) {
             log->debug(tr("Path chosen start = %1, dest = %2, protect = %3").arg(startlBlock->getDisplayName()).arg(  // NOI18N
                     destinationLBlock->getDisplayName()).arg(protectLBlock->getDisplayName()));
         }
         /*synchronized (this)*/ {
             destination = destinationLBlock;
         }

         if (log->isDebugEnabled()) {
             log->debug("Route details:");
             for (LayoutBlock* blk : routeDetails) {
                 log->debug(tr("  %1").arg(blk->getDisplayName()));
             }
         }

         if (getEntryExitType() == EntryExitPairs::FULLINTERLOCK) {
             setActiveEntryExit(true);
         }
         setRoute(true);
     }
 }
}

void DestinationPoints::handleNoCurrentRoute(bool reverse, QString message) {
//        Object[] options = {Bundle.getMessage("ButtonYes"), // NOI18N
//            Bundle.getMessage("ButtonNo")};  // NOI18N
 QVariantList options = QVariantList() << "Yes" << "No";
    int n = JOptionPane::showOptionDialog(nullptr,
            message + "\n" +tr("Would you like to Stack the Route?"), tr("Route Not Clear"), // NOI18N
            JOptionPane::YES_NO_CANCEL_OPTION,
            JOptionPane::QUESTION_MESSAGE,
            QIcon(),
            options,
            options[1]);
    if (n == 0) {
        manager->stackNXRoute(this, reverse);
        firePropertyChange("stacked", QVariant(), QVariant());  // NOI18N
    } else {
        firePropertyChange("failed", QVariant(), QVariant());  // NOI18N
    }
}

//@Override
/*public*/ void DestinationPoints::dispose()
{
    enabled = false;
    setActiveEntryExit(false);
    cancelClearInterlock(EntryExitPairs::CANCELROUTE);
    setRouteFrom(false);
    setRouteTo(false);
    point->removeDestination(this);
    /*synchronized(this)*/{
        QMutexLocker locker(&mutex);
        lastSeenActiveBlockObject = QVariant();
    }
    disposed=true;
}

//@Override
/*public*/ int DestinationPoints::getState(){
    if(activeEntryExit)
        return 0x02;
    return 0x04;
}

/*public*/ bool DestinationPoints::isActive() { return activeEntryExit; }

//@Override
/*public*/ void DestinationPoints::setState(int /*state*/){}

void DestinationPoints::setActiveEntryExit(bool boo){
    int oldvalue = getState();
    activeEntryExit = boo;
    firePropertyChange("active", oldvalue, getState());

}
