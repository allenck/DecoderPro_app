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
}


DestinationPoints::DestinationPoints(PointDetails* point, QString id, Source* src, QObject *parent) : AbstractNamedBean(id, parent)
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

    this->src = src;
    this->point=point;
    if(id==NULL){
        //uniqueId = UUID.randomUUID().toString();
        uniqueId = QUuid::createUuid().toString();
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

bool DestinationPoints::isRouteToPointSet() { return point->isRouteToPointSet(); }

LayoutBlock* DestinationPoints::getFacing() { return point->getFacing(); }
LayoutBlock* DestinationPoints::getProtecting() { return point->getProtecting(); }

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
                LayoutBlock* lBlock = InstanceManager::layoutBlockManagerInstance()->getLayoutBlock(blk);
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
/*protected*/ void DestinationPoints::blockStateUpdated(PropertyChangeEvent* e){
    Block* blk = (Block*) e->getSource();
    if (e->getPropertyName()==("state")) {
        if (log->isDebugEnabled()) log->debug(mUserName + "  We have a change of state on the block " + blk->getDisplayName());
        int now =  e->getNewValue().toInt();

        if (now==Block::OCCUPIED){
            LayoutBlock* lBlock = InstanceManager::layoutBlockManagerInstance()->getLayoutBlock(blk);
            //If the block was previously active or inactive then we will
            //reset the useExtraColor, but not if it was previously unknown or inconsistent.
            lBlock->setUseExtraColor(false);
            //blk->removePropertyChangeListener(propertyBlockListener); //was this
            disconnect(blk, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
            removeBlockFromRoute(lBlock);
        } else {
            if (log->isDebugEnabled()) log->debug("state was " + QString::number(now) + " and did not go through reset");
        }
    }
}


/*synchronized*/ void DestinationPoints::removeBlockFromRoute(LayoutBlock* lBlock)
{

 if (!routeDetails.isEmpty())
 {
  if(routeDetails.indexOf(lBlock)==-1)
  {
            if(src->getStart() == lBlock){
                log->debug("Start block went active");
                lastSeenActiveBlockObject = src->getStart()->getBlock()->getValue();
                //lBlock->getBlock().removePropertyChangeListener(propertyBlockListener);
                Block* blk = lBlock->getBlock();
                disconnect(blk, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyBlockListener(PropertyChangeEvent*)));
                return;
            } else {
                log->error("Block " + lBlock->getDisplayName() + " went active but it is not part of our NX path");
            }
        }
        if(routeDetails.indexOf(lBlock)!=0){
            log->debug("A block has been skipped will set the value of the active block to that of the original one");
            lBlock->getBlock()->setValue(lastSeenActiveBlockObject);
            if(routeDetails.indexOf(lBlock)!=-1){
                while(routeDetails.indexOf(lBlock)!=0){
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
        if(routeDetails.contains(lBlock)){
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
    if(!state){
        switch(manager->getClearDownOption()){
            case EntryExitPairs::PROMPTUSER : cancelClearOptionBox(); break;
            case EntryExitPairs::AUTOCANCEL : cancelClearInterlock(EntryExitPairs::CANCELROUTE); break;
            case EntryExitPairs::AUTOCLEAR  : cancelClearInterlock(EntryExitPairs::CLEARROUTE); break;
            default         : cancelClearOptionBox(); break;
        }
        return;
        /*if(src->entryExitPopUp!=NULL){
            src->entryExitPopUp.setEnabled(false);
        }
        cancelClearOptionBox();
        return;*/
    }
    /*We put the setting of the route into a seperate thread and put a glass pane infront of the layout editor,
    the swing thread for flash the icons to carry on as without interuption */

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
#if 0
 p->src->getPoint()->getPanel()->getGlassPane()->setVisible(true);
 try
 {
  QHash<Turnout*, int> turnoutSettings = new QHash<Turnout*, int>();

  ConnectivityUtil* connection = new ConnectivityUtil(point->getPanel());

  //This for loop was after the if statement
  //Last block in the route is the one that we are protecting at the last sensor/signalmast
  for (int i = 0; i<p->routeDetails.size(); i++){
    if (i>0) {
        QList<LayoutTurnout*> turnoutlist;
        int nxtBlk = i+1;
        int preBlk = i-1;
        /*if (i==routeDetails.size()-1){
            nxtBlk = i;
        } else*/ if (i==0){
            preBlk=i;
        }
        if(i<routeDetails.size()-1){
            //log->info(routeDetails.get(i).getBlock().getDisplayName() + " " + routeDetails.get(preBlk).getBlock().getDisplayName() + " " + routeDetails.get(nxtBlk).getBlock().getDisplayName());
            turnoutlist=connection.getTurnoutList(routeDetails.get(i).getBlock(), routeDetails.get(preBlk).getBlock(), routeDetails.get(nxtBlk).getBlock());
            ArrayList<Integer> throwlist=connection.getTurnoutSettingList();
            for (int x=0; x<turnoutlist.size(); x++){
                if(turnoutlist.get(x) instanceof LayoutSlip){
                    int slipState = throwlist.get(x);
                    LayoutSlip ls = (LayoutSlip)turnoutlist.get(x);
                    int taState = ls.getTurnoutState(slipState);
                    ls.getTurnout().setCommandedState(taState);
                    turnoutSettings.put(ls.getTurnout(), taState);
                    Runnable r = new Runnable() {
                      /*public*/ void run() {
                        try {
                            Thread.sleep(250 + manager.turnoutSetDelay);
                        } catch (InterruptedException ex) {
                            Thread.currentThread().interrupt();
                        }
                      }
                    };
                    Thread thr = new Thread(r, "Entry Exit Route, turnout setting");
                    thr.start();
                    try{
                        thr.join();
                    } catch (InterruptedException ex) {
            //            log->info("interrupted at join " + ex);
                    }
                    int tbState = ls.getTurnoutBState(slipState);
                    ls.getTurnoutB().setCommandedState(tbState);
                    turnoutSettings.put(ls.getTurnoutB(), tbState);
                } else {
                    String t = turnoutlist.get(x).getTurnoutName();
                    Turnout turnout = InstanceManager::turnoutManagerInstance().getTurnout(t);
                    turnout.setCommandedState(throwlist.get(x));
                    turnoutSettings.put(turnout, throwlist.get(x));
                }
                Runnable r = new Runnable() {
                  /*public*/ void run() {
                    try {
                        Thread.sleep(250 + manager.turnoutSetDelay);
                    } catch (InterruptedException ex) {
                        Thread.currentThread().interrupt();
                    }
                  }
                };
                Thread thr = new Thread(r, "Entry Exit Route, turnout setting");
                thr.start();
                try{
                    thr.join();
                } catch (InterruptedException ex) {
        //            log->info("interrupted at join " + ex);
                }
            }
        }
        if(getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
            routeDetails.get(i).setUseExtraColor(true);
        }
    }
    if ((getEntryExitType()==EntryExitPairs::FULLINTERLOCK)){
            routeDetails.get(i).getBlock().addPropertyChangeListener(propertyBlockListener); // was set against occupancy sensor
    } else {
        routeDetails.get(i).getBlock().removePropertyChangeListener(propertyBlockListener); // was set against occupancy sensor
    }
}
//Force a redraw
src->getPoint().getPanel().redrawPanel();
if (getEntryExitType()!=EntryExitPairs::SETUPTURNOUTSONLY){
    if(getEntryExitType()==EntryExitPairs::FULLINTERLOCK){
        //If our start block is already active we will set it as our lastSeenActiveBlock.
        if(src->getStart().getState()==Block.OCCUPIED){
            src->getStart().removePropertyChangeListener(propertyBlockListener);
            lastSeenActiveBlockObject = src->getStart().getBlock().getValue();
            log->debug("Last seen value " + lastSeenActiveBlockObject);
        }
    }
    if((src->sourceSignal instanceof SignalMast) && (getSignal() instanceof SignalMast)){
        SignalMast smSource = (SignalMast) src->sourceSignal;
        SignalMast smDest = (SignalMast) getSignal();
        synchronized(this){
            sml = InstanceManager::signalMastLogicManagerInstance().newSignalMastLogic(smSource);
            if(!sml.isDestinationValid(smDest)){
                //if no signalmastlogic existed then created it, but set it not to be stored.
                sml.setDestinationMast(smDest);
                sml.setStore(jmri.SignalMastLogic.STORENONE, smDest);
            }
        }
        LinkedHashMap<Block, Integer> blks = new LinkedHashMap<Block, Integer>();
        //Remove the first block as it is our start block
        routeDetails.remove(0);
        for(int i = 0; i<routeDetails.size(); i++){
            if (routeDetails.get(i).getBlock().getState()==Block.UNKNOWN)
                routeDetails.get(i).getBlock().setState(Block.UNOCCUPIED);
            blks.put(routeDetails.get(i).getBlock(), Block.UNOCCUPIED);
        }
        synchronized(this){
            smSource.setHeld(false);
            sml.setAutoBlocks(blks, smDest);
            sml.setAutoTurnouts(turnoutSettings, smDest);
            sml.initialise(smDest);
        }
        smSource.addPropertyChangeListener( new PropertyChangeListener() {
            /*public*/ void propertyChange(PropertyChangeEvent e) {
                SignalMast source = (SignalMast)e.getSource();
                source.removePropertyChangeListener(this);
                setRouteFrom(true);
                setRouteTo(true);
            }
        });
        src->pd->extendedtime=true;
        point->extendedtime=true;
    } else {
        if (src->sourceSignal instanceof SignalMast){
            SignalMast mast = (SignalMast) src->sourceSignal;
            mast.setHeld(false);
        } else if (src->sourceSignal instanceof SignalHead){
            SignalHead head = (SignalHead) src->sourceSignal;
            head.setHeld(false);
        }
        setRouteFrom(true);
        setRouteTo(true);
    }
} else {
    src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
    point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
}
} catch (RuntimeException ex) {
log->error("An error occured while setting the route");
ex.printStackTrace();
src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
point->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
}
    src->getPoint().getPanel().getGlassPane().setVisible(false);
    src->setMenuEnabled(true);
#endif
}
//};


void DestinationPoints::cancelClearOptionBox(){
// TODO:
#if 0
    if(cancelClearFrame==NULL){
        JButton jButton_Clear = new JButton("Clear Down");
        JButton jButton_Cancel = new JButton("Cancel");
        JButton jButton_Exit = new JButton("Exit");
        JLabel jLabel = new JLabel("What would you like to do with this interlock?");
        JLabel jIcon = new JLabel(javax.swing.UIManager.getIcon("OptionPane.questionIcon"));
        cancelClearFrame = new JFrame("Interlock");
        Container cont = cancelClearFrame.getContentPane();
        JPanel qPanel = new JPanel();
        qPanel.add(jIcon);
        qPanel.add(jLabel);
        cont.add(qPanel, BorderLayout.CENTER);
        JPanel buttonsPanel = new JPanel();
        buttonsPanel.add(jButton_Cancel);
        buttonsPanel.add(jButton_Clear);
        buttonsPanel.add(jButton_Exit);
        cont.add(buttonsPanel, BorderLayout.SOUTH);
        cancelClearFrame.pack();

        jButton_Clear.addActionListener( new ActionListener() {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        cancelClearFrame.setVisible(false);
                        threadAutoClearFrame.interrupt();
                        cancelClearInterlock(EntryExitPairs::CLEARROUTE);
                    }
                });
        jButton_Cancel.addActionListener( new ActionListener() {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        cancelClearFrame.setVisible(false);
                        threadAutoClearFrame.interrupt();
                        cancelClearInterlock(EntryExitPairs::CANCELROUTE);
                    }
                });
        jButton_Exit.addActionListener( new ActionListener() {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        cancelClearFrame.setVisible(false);
                        threadAutoClearFrame.interrupt();
                        cancelClearInterlock(EntryExitPairs::EXITROUTE);
                    }
                });
        src->getPoint().getPanel().setGlassPane(manager.getGlassPane());
    }
    if(cancelClearFrame.isVisible()){
        return;
    }
    src->pd->extendedtime=true;
    point->extendedtime =true;

    class MessageTimeOut implements Runnable {
        MessageTimeOut(){
        }
        /*public*/ void run() {
            try {
                //Set a timmer before this window is automatically closed to 30 seconds
                Thread.sleep(NXMESSAGEBOXCLEARTIMEOUT*1000);
                cancelClearFrame.setVisible(false);
                cancelClearInterlock(EntryExitPairs::EXITROUTE);
            } catch (InterruptedException ex) {
                log->debug("Flash timer cancelled");
            }
        }
    }
    MessageTimeOut mt = new MessageTimeOut();
    threadAutoClearFrame = new Thread(mt, "NX Button Clear Message Timeout ");
    threadAutoClearFrame.start();
    cancelClearFrame.setAlwaysOnTop(true);
    src->getPoint().getPanel().getGlassPane().setVisible(true);
    int w = cancelClearFrame.getSize().width;
    int h = cancelClearFrame.getSize().height;
    int x = (int)src->getPoint().getPanel().getLocation().getX()+((src->getPoint().getPanel().getSize().width-w)/2);
    int y = (int)src->getPoint().getPanel().getLocation().getY()+((src->getPoint().getPanel().getSize().height-h)/2);
    cancelClearFrame.setLocation(x, y);
    cancelClearFrame.setVisible(true);
#endif
}

void DestinationPoints::cancelClearInterlock(int cancelClear)
{

 if (cancelClear==EntryExitPairs::EXITROUTE)
 {
  src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
  point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
//  src->getPoint()->getPanel()->getGlassPane().setVisible(false);
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
 //src->getPoint()->getPanel()->getGlassPane().setVisible(false);

}

void DestinationPoints::activeBean(bool reverseDirection)
{
// TODO:
#if 1
 if(activeEntryExit)
 {
  // log->debug(mUserName + "  Our route is active so this would go for a clear down but we need to check that the we can clear it down" + activeEndPoint);
  if(!isEnabled())
  {
   log->info("A disabled entry exit has been called will bomb out");
  }
  if (activeEntryExit)
  {
   log->debug(mUserName + "  We have a valid match on our end point so we can clear down");
   //setRouteTo(false);
   //src->pd->setRouteFrom(false);
   setRoute(false);
  }
  else
  {
   log->debug(mUserName + "  sourceSensor that has gone active doesn't match the active end point so will not clear");
   //JOptionPane.showMessageDialog(NULL, "A conflicting route has already been set");
   QMessageBox::information(NULL, tr("Information"),tr("A conflicting route has already been set"));
   src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
   point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
  }
 }
 else
 {
  if (isRouteToPointSet())
  {
   log->debug(mUserName + "  route to this point is set therefore can not set another to it " /*+ destPoint.src->getPoint().getID()*/);
   src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
   point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
   return;
  }
  else
  {
   LayoutBlock* startlBlock = src->getStart();
   LayoutBlock* protectLBlock = src->getSourceProtecting();
   LayoutBlock* destinationLBlock;

   if(!reverseDirection)
   {
    //We have a problem, the destination point is already setup with a route, therefore we would need to
    //check some how that a route hasn't been set to it.
    destinationLBlock = getFacing();
   }
   else
   {

    protectLBlock = getFacing();
    startlBlock = getProtecting();
    destinationLBlock = src->getStart();
    if(log->isDebugEnabled())
     log->debug("reverse set destination is set going for " + startlBlock->getDisplayName() + " " + destinationLBlock->getDisplayName() + " " + protectLBlock->getDisplayName());
    try
    {
     if(!InstanceManager::layoutBlockManagerInstance()->getLayoutBlockConnectivityTools()->checkValidDest(startlBlock, protectLBlock, src->getSourceProtecting(), src->getStart()))
     {
      startlBlock = getFacing();
      protectLBlock = getProtecting();
      if(log->isDebugEnabled())
       log->debug("That didn't work so try  " + startlBlock->getDisplayName() + " " + destinationLBlock->getDisplayName() + " " + protectLBlock->getDisplayName());
      if(!InstanceManager::layoutBlockManagerInstance()->getLayoutBlockConnectivityTools()->checkValidDest(startlBlock, protectLBlock, src->getSourceProtecting(), src->getStart()))
      {
       log->error("No route found");
       //JOptionPane.showMessageDialog(NULL, "No Valid path found");
       QMessageBox::critical(NULL, tr("Error"), tr("No Valid path found"));
       src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
       point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
       return;
      }
     }
     else if(InstanceManager::layoutBlockManagerInstance()->getLayoutBlockConnectivityTools()->checkValidDest(getFacing(), getProtecting(), src->getSourceProtecting(), src->getStart()))
     {
      //Both paths are valid, so will go for setting the shortest
      int distance = startlBlock->getBlockHopCount(destinationLBlock->getBlock(), protectLBlock->getBlock());
      int distance2 = getFacing()->getBlockHopCount(destinationLBlock->getBlock(), getProtecting()->getBlock());
      if(distance > distance2)
      {
       //The alternative route is shorter we shall use that
       startlBlock = getFacing();
       protectLBlock = getProtecting();
      }
     }
    }
    catch (JmriException ex)
    {
     //JOptionPane.showMessageDialog(NULL, ex.getMessage());
     QMessageBox::critical(NULL, tr("Error"), ex.getMessage());
     log->error("Exception " + ex.getMessage());
     src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
     point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
     return;
    }
   }
   if(log->isDebugEnabled())
   {
    log->debug("Path chossen " + startlBlock->getDisplayName() + " " + destinationLBlock->getDisplayName() + " " +  protectLBlock->getDisplayName());
   }
   // synchronized(this)
   {
    destination = destinationLBlock;
   }
   try
   {
    routeDetails = InstanceManager::layoutBlockManagerInstance()->getLayoutBlockConnectivityTools()->getLayoutBlocks(startlBlock, destinationLBlock, protectLBlock, false, 0x00/*jmri.jmrit.display.layoutEditor.LayoutBlockManager.MASTTOMAST*/);
   }
   catch (JmriException e)
   {
    //JOptionPane.showMessageDialog(NULL, e.getMessage());
    QMessageBox::critical(NULL, tr("Error"), e.getMessage());

    //Considered normal if not a valid through path
    log->error(mUserName + " " + e.getMessage());
    src->pd->setNXButtonState(EntryExitPairs::NXBUTTONINACTIVE);
    point->setNXButtonState( EntryExitPairs::NXBUTTONINACTIVE);
    return;
   }
   if (log->isDebugEnabled())
   {
    foreach(LayoutBlock* blk, routeDetails)
    {
     log->debug(blk->getDisplayName());
    }
   }

   if(getEntryExitType()==EntryExitPairs::FULLINTERLOCK)
   {
    setActiveEntryExit(true);
   }
   setRoute(true);
  }
 }
#endif
}
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

/*public*/ int DestinationPoints::getState(){
    if(activeEntryExit)
        return 0x02;
    return 0x04;
}

/*public*/ bool DestinationPoints::isActive() { return activeEntryExit; }

/*public*/ void DestinationPoints::setState(int /*state*/){}

void DestinationPoints::setActiveEntryExit(bool boo){
    int oldvalue = getState();
    activeEntryExit = boo;
    firePropertyChange("active", oldvalue, getState());

}
