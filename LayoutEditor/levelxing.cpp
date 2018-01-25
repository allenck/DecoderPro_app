#include "levelxing.h"
#include "instancemanager.h"
#include "editlevelxingdlg.h"
#include "signalmast.h"
#include "signalmastlogic.h"
#include "signalmastlogicmanager.h"
#include "signalmastmanager.h"
#include "layoutblockroutetableaction.h"

//LevelXing::LevelXing(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A LevelXing is two track segment on a layout that cross at an angle.
 * <P>
 * A LevelXing has four connection points, designated A, B, C, and D.
 *		At the crossing, A-C and B-D are straight segments.  A train proceeds
 *		through the crossing on either of these segments.
 * <P>
 * Each straight segment carries Block information.  A-C and B-D may be in the
 *		same or different Layout Blocks.
 * <P>
 * For drawing purposes, each LevelXing carries a center point and displacements
 *		for A and B.  The displacements for C = - the displacement for A, and the
 *		displacement for D = - the displacement for B.  The center point and these
 *      displacements may be adjusted by the user when in edit mode.
 * <P>
 * When LevelXings are first created, there are no connections.  Block information
 *		and connections are added when available.
 * <P>
 * Signal Head names are saved here to keep track of where signals are. LevelXing
 *		only serves as a storage place for signal head names. The names are placed here
 *		by Set Signals at Level Crossing in Tools menu.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 20802 $
 */

///*public*/ class LevelXing
//{

    // Defined text resource
    //ResourceBundle rb = ResourceBundle.getBundle("jmrit.display.layoutEditor.LayoutEditorBundle");


/**
 * constructor method
 */
/*public*/ LevelXing::LevelXing(QString id, QPointF c, LayoutEditor* myPanel)
{
 blockAC = NULL;
 blockBD = NULL;
 instance = NULL;
 layoutEditor = NULL;
 item = NULL;
 rects = NULL;

 // persistent instances variables (saved between sessions)
 ident = "";
 blockNameAC = "";
 blockNameBD = "";
 signalAName = "";  // signal at A track junction
 signalBName = "";  // signal at B track junction
 signalCName = "";  // signal at C track junction
 signalDName = "";  // signal at D track junction

 signalAMastName = "";  // signal at A track junction
 signalBMastName = "";  // signal at B track junction
 signalCMastName = "";  // signal at C track junction
 signalDMastName = "";  // signal at D track junction

 sensorAName = "";  // sensor at A track junction
 sensorBName = "";  // sensor at B track junction
 sensorCName = "";  // sensor at C track junction
 sensorDName = "";  // sensor at D track junction    */

 sensorANamed = NULL; // sensor at A track junction
 sensorBNamed = NULL; // sensor at B track junction
 sensorCNamed = NULL; // sensor at C track junction
 sensorDNamed = NULL; // sensor at D track junction

 signalAHeadNamed = NULL; // signal at A track junction
 signalBHeadNamed = NULL; // signal at B track junction
 signalCHeadNamed = NULL; // signal at C track junction
 signalDHeadNamed = NULL; // signal at D track junction

 signalAMastNamed = NULL; // signal at A track junction
 signalBMastNamed = NULL; // signal at B track junction
 signalCMastNamed = NULL; // signal at C track junction
 signalDMastNamed = NULL; // signal at D track junction


 connectA = NULL;
 connectB = NULL;
 connectC = NULL;
 connectD = NULL;
 center = QPointF(50.0,50.0);
 dispA =  QPointF(-20.0,0.0);
 dispB =  QPointF(-14.0,14.0);
 connectAName = "";
 connectBName = "";
 connectCName = "";
 connectDName = "";
 tBlockNameAC = "";
 tBlockNameBD = "";
 active = true;
 sml = new QVector<SignalMast*>();
 editAdditionalMenu = new QVector<QMenu*>(0);
 viewAdditionalMenu = new QVector<QMenu*>(0);

 editOpen = false;
 needsRedraw = false;
 needsBlockUpdate = false;
 popup = NULL;
 block1Name = new QLineEdit();
 block2Name = new QLineEdit();
 tools = NULL;
 editLevelXingFrame = NULL;

 instance = this;
 layoutEditor = myPanel;
 ident = id;
 center = c;
}

/*public*/ SignalMast* LevelXing::getSignalAMast()
{
 if (signalAMastNamed != NULL)
 {
     return signalAMastNamed->getBean();
 }
 return NULL;
}

/*public*/ void LevelXing::setSignalAMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalAMastNamed = NULL;
        return;
    }

    SignalMast* mast = InstanceManager::signalMastManagerInstance()->provideSignalMast(signalMast);
    if (mast != NULL) {
     signalAMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalAMastNamed = NULL;
    }
}


/*public*/ SignalMast* LevelXing::getSignalBMast() {
    if (signalBMastNamed != NULL) {
        return signalBMastNamed->getBean();
    }
    return NULL;
}

/*public*/ void LevelXing::setSignalBMast(QString signalMast)
{
    if (signalMast == NULL || signalMast==("")) {
        signalBMastNamed = NULL;
        return;
    }

    SignalMast* mast = InstanceManager::signalMastManagerInstance()->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalBMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalBMastNamed = NULL;
    }
}

/*public*/ void LevelXing::setSignalCMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalCMastNamed = NULL;
        return;
    }

    SignalMast* mast = InstanceManager::signalMastManagerInstance()->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalCMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalCMastNamed = NULL;
    }
}


/*public*/ SignalMast* LevelXing::getSignalDMast() {
    if (signalDMastNamed != NULL) {
        return signalDMastNamed->getBean();
    }
    return NULL;
}

/*public*/ void LevelXing::setSignalDMast(QString signalMast) {
    if (signalMast == NULL || signalMast==("")) {
        signalDMastNamed = NULL;
        return;
    }

    SignalMast* mast = InstanceManager::signalMastManagerInstance()->provideSignalMast(signalMast);
    if (mast != NULL) {
        signalDMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    } else {
        signalDMastNamed = NULL;
    }
}

/*public*/ QString LevelXing::getSensorAName() {
    if(sensorANamed!=NULL)
        return sensorANamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorAName(QString sensorName)
{
 if(sensorName==NULL || sensorName==(""))
 {
  sensorANamed=NULL;
  return;
 }

 Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
 if (sensor != NULL)
 {
     sensorANamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
 }
 else
 {
  sensorANamed=NULL;
 }
}

/*public*/ QString LevelXing::getSensorBName() {
    if(sensorBNamed!=NULL)
        return sensorBNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorBName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorBNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorBNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorBNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorCName() {
    if(sensorCNamed!=NULL)
        return sensorCNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorCName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorCNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorCNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorCNamed=NULL;
    }
}

/*public*/ QString LevelXing::getSensorDName() {
    if(sensorDNamed!=NULL)
        return sensorDNamed->getName();
    return "";
}

/*public*/ void LevelXing::setSensorDName(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        sensorDNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorDNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorDNamed=NULL;
    }
}

/*public*/ QObject* LevelXing::getConnection(int location) throw (JmriException)
{
    switch (location) {
        case LEVEL_XING_A:
            return connectA;
        case LEVEL_XING_B:
            return connectB;
        case LEVEL_XING_C:
            return connectC;
        case LEVEL_XING_D:
            return connectD;
    }
    log.error("Invalid Point Type " + QString::number(location)); //I18IN
    throw JmriException("Invalid Point");
}

/*public*/ void LevelXing::setConnection(int location, QObject* o, int type) throw (JmriException) {
    if ((type != TRACK) && (type != NONE)) {
        log.error("unexpected type of connection to layoutturnout - " + QString::number(type));
        throw JmriException("unexpected type of connection to layoutturnout - " + QString::number(type));
    }
    switch (location) {
        case LEVEL_XING_A:
            connectA = o;
            break;
        case LEVEL_XING_B:
            connectB = o;
            break;
        case LEVEL_XING_C:
            connectC = o;
            break;
        case LEVEL_XING_D:
            connectD = o;
            break;
        default:
            log.error("Invalid Point Type " + QString::number(location)); //I18IN
            throw JmriException("Invalid Point");
    }
}

/*public*/ void LevelXing::setConnectA(QObject* o,int type) {
    connectA = o;
    if ( (connectA!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of A connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectB(QObject* o,int type) {
    connectB = o;
    if ( (connectB!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of B connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectC(QObject* o,int type) {
    connectC = o;
    if ( (connectC!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of C connection to levelXing - "+type);
    }
}
/*public*/ void LevelXing::setConnectD(QObject* o,int type) {
    connectD = o;
    if ( (connectD!=NULL) && (type!=LayoutEditor::TRACK) ) {
        log.error("unexpected type of D connection to levelXing - "+type);
    }
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockAC() {
    if ( (blockAC==NULL) && (blockNameAC.length()>0) ) {
        blockAC = layoutEditor->provideLayoutBlock(blockNameAC);
        if ( (blockAC!=NULL) && (blockAC==blockBD) )
                blockAC->decrementUse();
    }
    return blockAC;
}
/*public*/ LayoutBlock* LevelXing::getLayoutBlockBD() {
    if ( (blockBD==NULL) && (blockNameBD.length()>0) ) {
        blockBD = layoutEditor->provideLayoutBlock(blockNameBD);
        if ( (blockBD!=NULL) && (blockAC==blockBD) )
                blockBD->decrementUse();
    }
    return blockBD;
}
/*public*/ QPointF LevelXing::getCoordsCenter() {return center;}
/*public*/ QPointF  LevelXing::getCoordsA() {
    double x = center.x() + dispA.x();
    double y = center.y() + dispA.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsB() {
    double x = center.x() + dispB.x();
    double y = center.y() + dispB.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsC() {
    double x = center.x() - dispA.x();
    double y = center.y() - dispA.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LevelXing::getCoordsD() {
    double x = center.x() - dispB.x();
    double y = center.y() - dispB.y();
    return  QPointF(x,y);
}

/**
 * Add Layout Blocks
 */
/*public*/ void LevelXing::setLayoutBlockAC (LayoutBlock* b) {
    blockAC = b;
    if (b!=NULL) {
        blockNameAC = b->getID();
    }
}
/*public*/ void LevelXing::setLayoutBlockBD (LayoutBlock* b) {
    blockBD = b;
    if (b!=NULL) {
        blockNameBD = b->getID();
    }
}
/*private*/ void LevelXing::updateBlockInfo() {
    LayoutBlock* b1 = NULL;
    LayoutBlock* b2 = NULL;
    if (blockAC!=NULL) blockAC->updatePaths();
    if (connectA!=NULL) {
        b1 = ((TrackSegment*)connectA)->getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockAC)) b1->updatePaths();
    }
    if (connectC!=NULL) {
        b2 = ((TrackSegment*)connectC)->getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockAC)&&(b2!=b1)) b2->updatePaths();
    }
    if (blockBD!=NULL) blockBD->updatePaths();
    if (connectB!=NULL) {
        b1 = ((TrackSegment*)connectB)->getLayoutBlock();
        if ((b1!=NULL)&&(b1!=blockBD)) b1->updatePaths();
    }
    if (connectD!=NULL) {
        b2 = ((TrackSegment*)connectD)->getLayoutBlock();
        if ((b2!=NULL)&&(b2!=blockBD)&&(b2!=b1)) b2->updatePaths();
    }
    reCheckBlockBoundary();
}

/*public*/ void LevelXing::reCheckBlockBoundary(){
    if(connectA==NULL && connectB==NULL && connectC==NULL && connectD==NULL){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
//        if(getSignalAMastName()!=(""))
//            removeSML(getSignalAMastName());
//        if(getSignalBMastName()!=(""))
//            removeSML(getSignalBMastName());
//        if(getSignalCMastName()!=(""))
//            removeSML(getSignalCMastName());
//        if(getSignalDMastName()!=(""))
//            removeSML(getSignalDMastName());
//        setSignalAMastName("");
//        setSignalBMastName("");
//        setSignalCMastName("");
//        setSignalDMastName("");
//        setSensorAName("");
//        setSensorBName("");
//        setSensorCName("");
//        setSensorDName("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any logics generated
    }  else if(connectA==NULL || connectB==NULL || connectC==NULL || connectD==NULL){
        //could still be in the process of rebuilding the point details
        return;
    }

    TrackSegment* trkA;
    TrackSegment* trkB;
    TrackSegment* trkC;
    TrackSegment* trkD;

    //if(connectA instanceof TrackSegment*)
    {
        trkA = (TrackSegment*)connectA;
        if(trkA->getLayoutBlock()==blockAC){
            setSignalAMastName("");
            setSensorAName("");
//            if(getSignalAMastName()!=(""))
//                removeSML(getSignalAMastName());
        }
    }
//    if(connectC instanceof TrackSegment*)
    {
        trkC = (TrackSegment*)connectC;
        if(trkC->getLayoutBlock()==blockAC){
            setSignalCMastName("");
            setSensorCName("");
//            if(getSignalCMastName()!=(""))
//                removeSML(getSignalCMastName());
        }
    }
//    if(connectB instanceof TrackSegment)
    {
        trkB = (TrackSegment*)connectB;
        if(trkB->getLayoutBlock()==blockBD){
            setSignalBMastName("");
            setSensorBName("");
//            if(getSignalBMastName()!=(""))
//                removeSML(getSignalBMastName());
        }
    }

//    if(connectD instanceof TrackSegment)
    {
        trkD = (TrackSegment*)connectC;
        if(trkD->getLayoutBlock()==blockBD){
            setSignalDMastName("");
            setSensorDName("");
//            if(getSignalDMastName()!=(""))
//                removeSML(getSignalDMastName());
        }
    }
}

//void LevelXing::removeSML(QString signalMast){
//    if(signalMast==NULL || signalMast!=(""))
//        return;
//    SignalMast* mast = InstanceManager::signalMastManagerInstance().getSignalMast(signalMast);
//    if(InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager::signalMastLogicManagerInstance().isSignalMastUsed(mast)){
//        SignallingGuiTools.removeSignalMastLogic(NULL, mast);
//    }
//}

/**
 * Methods to test if mainline track or not
 *  Returns true if either connecting track segment is mainline
 *  Defaults to not mainline if connecting track segments are missing
 */
/*public*/ bool LevelXing::isMainlineAC() {
    if ( ((connectA != NULL) && (((TrackSegment*)connectA)->getMainline())) ||
        ((connectB != NULL) && (((TrackSegment*)connectB)->getMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}
/*public*/ bool LevelXing::isMainlineBD() {
    if ( ((connectB != NULL) && (((TrackSegment*)connectB)->getMainline())) ||
        ((connectD != NULL) && (((TrackSegment*)connectD)->getMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Modify coordinates methods
 */
/*public*/ void LevelXing::setCoordsCenter(QPointF p) {
    center = p;
}
/*public*/ void LevelXing::setCoordsA(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispA = QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsB(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB = QPointF(-x,-y);
}
/*public*/ void LevelXing::setCoordsC(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispA =  QPointF(x,y);
}
/*public*/ void LevelXing::setCoordsD(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(x,y);
}
/*public*/ void LevelXing::scaleCoords(float xFactor, float yFactor) {
    QPointF pt (round(center.x()*xFactor),
                                    round(center.y()*yFactor));
    center = pt;
    pt =  QPointF(round(dispA.x()*xFactor),
                                    round(dispA.y()*yFactor));
    dispA = pt;
    pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
}
double LevelXing::round (double x) {
    int i = (int)(x+0.5);
    return i;
}

// initialization instance variables (used when loading a LayoutEditor)
///*public*/ QString connectAName = "";
///*public*/ QString connectBName = "";
///*public*/ QString connectCName = "";
///*public*/ QString connectDName = "";
///*public*/ QString tBlockNameAC = "";
///*public*/ QString tBlockNameBD = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LevelXing::setObjects(LayoutEditor* p) {
    connectA = p->findTrackSegmentByName(connectAName);
    connectB = p->findTrackSegmentByName(connectBName);
    connectC = p->findTrackSegmentByName(connectCName);
    connectD = p->findTrackSegmentByName(connectDName);
    if (tBlockNameAC.length()>0) {
        blockAC = p->getLayoutBlock(tBlockNameAC);
        if (blockAC!=NULL) {
            blockNameAC = tBlockNameAC;
            if (blockAC!=blockBD)
                blockAC->incrementUse();
        }
        else {
            log.error("bad blocknameac '"+tBlockNameAC+"' in levelxing "+ident);
        }
    }
    if (tBlockNameBD.length()>0) {
        blockBD = p->getLayoutBlock(tBlockNameBD);
        if (blockBD!=NULL) {
            blockNameBD = tBlockNameBD;
            if (blockAC!=blockBD)
                blockBD->incrementUse();
        }
        else {
            log.error("bad blocknamebd '"+tBlockNameBD+"' in levelxing "+ident);
        }
    }
}


/**
 * Display popup menu for information and editing
 */
/*protected*/ void LevelXing::showPopUp(QGraphicsSceneMouseEvent* /*e*/, bool isEditable)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 if(isEditable)
 {
  popup->addAction(new QAction(tr("LevelCrossing"),this));
  bool blockACAssigned = false;
  bool blockBDAssigned = false;
  if ( (blockNameAC==NULL) || (blockNameAC==("")) )
   popup->addAction(new QAction(tr("NoBlock1"),this));
  else
  {
   popup->addAction(new QAction(tr("Block1ID")+": "+getLayoutBlockAC()->getID(),this));
   blockACAssigned = true;
  }
  if ( (blockNameBD==NULL) || (blockNameBD==("")) ) popup->addAction(new QAction(tr("NoBlock2"),this));
  else
  {
   popup->addAction(new QAction(tr("Block2ID")+": "+getLayoutBlockBD()->getID(),this));
   blockBDAssigned = true;
  }
  popup->addSeparator();

//    popup.add(new AbstractAction(rb.getQString("Edit")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editLevelXing(instance);
//            }
//        });
  QAction* editAction = new QAction(tr("Edit"),this);
  popup->addAction(editAction);
  connect(editAction, SIGNAL(triggered()), this, SLOT(editLevelXing(/*LevelXing**/)));

//    popup.add(new AbstractAction(rb.getQString("Remove")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (layoutEditor.removeLevelXing(instance)) {
//                    // Returned true if user did not cancel
//                    remove();
//                    dispose();
//                }
//            }
//        });
  QAction* removeAction = new QAction(tr("Remove"), this);
  popup->addAction(removeAction);
  connect(removeAction, SIGNAL(triggered()), this, SLOT(on_removeAction_triggered()));
#if 1
  if (blockACAssigned && blockBDAssigned)
  {
//            popup.add(new AbstractAction(rb.getQString("SetSignals")) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (tools == NULL) {
//                        tools = new LayoutEditorTools(layoutEditor);
//                    }
//                    // bring up signals at level crossing tool dialog
//                    tools.setSignalsAtLevelXingFromMenu(instance,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//            });
   AbstractAction* setSignals = new AbstractAction(tr("Set Signals"),this);
   popup->addAction(setSignals);
   connect(setSignals, SIGNAL(triggered()), this, SLOT(on_set_signals()));
  }

  boundaryBetween = getBlockBoundaries();
  bool blockBoundaries = false;
  if (InstanceManager::layoutBlockManagerInstance()->isAdvancedRoutingEnabled())
  {
   if(blockACAssigned && !blockBDAssigned)
   {
    //       popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
    //           /*public*/ void actionPerformed(ActionEvent e) {
    //               AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
    //               routeTableAction.actionPerformed(e);
    //           }
    //       });
    AbstractAction* viewBlockRouting = new AbstractAction(tr("View Block Routing AC"),this);
    popup->addAction(viewBlockRouting);
    connect(viewBlockRouting, SIGNAL(triggered()), this, SLOT(On_viewBlockRoutingAC()));
   }
   else if(!blockACAssigned && blockBDAssigned)
   {
//    popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockBD());
//            routeTableAction.actionPerformed(e);
//        }
//    });
    AbstractAction* viewBlockRouting1 = new AbstractAction(tr("View BlockRouting BD"), this);
      popup->addAction(viewBlockRouting1);
      connect(viewBlockRouting1, SIGNAL(triggered()),this, SLOT(On_viewBlockRoutingBD()));
   }
   else if(blockACAssigned && blockBDAssigned)
   {
    QMenu* viewRouting = new QMenu(tr("View Block Routing"));
//    viewRouting.add(new AbstractAction( blockNameAC) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction( blockNameAC, getLayoutBlockAC());
//            routeTableAction.actionPerformed(e);
//        }
//    });
    AbstractAction* viewBlockRoutingAct = new AbstractAction(tr("View Block Routing"),this);
    viewRouting->addAction(viewBlockRoutingAct);
    connect( viewBlockRoutingAct, SIGNAL(triggered()),this, SLOT(On_viewBlockRoutingAC()));

//    viewRouting.add(new AbstractAction(blockNameBD) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockNameBD, getLayoutBlockBD());
//            routeTableAction.actionPerformed(e);
//        }
//    });
    viewBlockRoutingAct = new AbstractAction(tr("View Block Routing"),this);
    viewRouting->addAction(viewBlockRoutingAct);
    connect( viewBlockRoutingAct, SIGNAL(triggered()),this, SLOT(On_viewBlockRoutingBD()));

    popup->addMenu(viewRouting);
   }
  }

  for (int i = 0; i<4; i++)
  {
   if(boundaryBetween->at(i)!=NULL)
    blockBoundaries=true;
  }
  if (blockBoundaries)
  {
   //   popup.add(new AbstractAction(rb.getQString("SetSignalMasts")) {
   //      /*public*/ void actionPerformed(ActionEvent e) {
   //          if (tools == NULL) {
   //              tools = new LayoutEditorTools(layoutEditor);
   //          }

   //          tools.setSignalMastsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor.signalFrame);
   //      }
   //  });
   AbstractAction* setSignalMastsAct = new AbstractAction(tr("Set SignalMasts"),this);
   popup->addAction(setSignalMastsAct);
   connect(setSignalMastsAct, SIGNAL(triggered()), this, SLOT(on_setSignalMasts()));
//   popup.add(new AbstractAction(rb.getQString("SetSensors")) {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          if (tools == NULL) {
//              tools = new LayoutEditorTools(layoutEditor);
//          }

//          tools.setSensorsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor.sensorIconEditor, layoutEditor.sensorFrame);
//      }
//  });
   AbstractAction* setSensorsAct = new AbstractAction(tr("Set Sensors"),this);
   popup->addAction(setSensorsAct);
   connect(setSensorsAct, SIGNAL(triggered()), this, SLOT(on_setSensors()));
#endif

  }

//  layoutEditor.setShowAlignmentMenu(popup);
//  popup.show(e.getComponent(), e.x(), e.y());
  popup->exec(QCursor::pos());
 }
// else if(!viewAdditionalMenu.isEmpty())
// {
//        setAdditionalViewPopUpMenu(popup);
//        popup.show(e.getComponent(), e.x(), e.y());
// }
}
 void LevelXing::on_set_signals()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(layoutEditor);
  }
  // bring up signals at level crossing tool dialog
  tools->setSignalsAtLevelXingFromMenu(instance,layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }

 void LevelXing::On_viewBlockRoutingAC()
 {
  AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
  routeTableAction->actionPerformed();
 }

 void LevelXing::On_viewBlockRoutingBD()
 {
  AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
  routeTableAction->actionPerformed();
 }

 void LevelXing::on_setSignalMasts()
 {
  if (tools == NULL)
  {
   tools = new LayoutEditorTools(layoutEditor);
  }

  tools->setSensorsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor->sensorIconEditor, layoutEditor->sensorFrame);

 }

 void LevelXing::on_setSensors()
 {
  if (tools == NULL)
  {
  tools = new LayoutEditorTools(layoutEditor);
  }

  tools->setSensorsAtLevelXingFromMenu(instance, boundaryBetween, layoutEditor->sensorIconEditor, layoutEditor->sensorFrame);
 }

/*public*/ QVector<QString>* LevelXing::getBlockBoundaries()
 {
  /*final*/ QVector<QString>* boundaryBetween = new QVector<QString>(4,"");
  if ( (blockNameAC!=NULL) && (blockNameAC!=("")) && (blockAC!=NULL) )
  {
     if (/*(connectA instanceof TrackSegment*) &&*/ (((TrackSegment*)connectA)->getLayoutBlock()!=blockAC)){
         try {
             boundaryBetween->replace(0,((TrackSegment*)connectA)->getLayoutBlock()->getDisplayName()+ " - " + blockAC->getDisplayName());
         } catch (NullPointerException* e){
             //Can be considered normal if tracksegement hasn't yet been allocated a block
             log.debug("TrackSegement at connection A doesn't contain a layout block");
         }
     }
     if (/*(connectC instanceof TrackSegment) &&*/ (((TrackSegment*)connectC)->getLayoutBlock()!=blockAC))
     {
      try {
          boundaryBetween->replace(2,(((TrackSegment*)connectC)->getLayoutBlock()->getDisplayName()+ " - " + blockAC->getDisplayName()));
      } catch (NullPointerException *e){
          //Can be considered normal if tracksegement hasn't yet been allocated a block
          log.debug("TrackSegement at connection C doesn't contain a layout block");
      }
     }
    }
    if ( (blockNameBD!=NULL) && (blockNameBD!=("")) && (blockBD!=NULL) )
    {
     if (/*(connectB instanceof TrackSegment) &&*/ (((TrackSegment*)connectB)->getLayoutBlock()!=blockBD)){
         try {
             boundaryBetween->replace(1,(((TrackSegment*)connectB)->getLayoutBlock()->getDisplayName()+ " - " + blockBD->getDisplayName()));
         } catch (NullPointerException* e){
             //Can be considered normal if tracksegement hasn't yet been allocated a block
             log.debug("TrackSegement at connection B doesn't contain a layout block");
         }
     }
     if (/*(connectD instanceof TrackSegment) &&*/ (((TrackSegment*)connectD)->getLayoutBlock()!=blockBD))
     {
      try {
          boundaryBetween->replace(3,(((TrackSegment*)connectD)->getLayoutBlock()->getDisplayName()+ " - " + blockBD->getDisplayName()));
      } catch (NullPointerException* e){
          //Can be considered normal if tracksegement hasn't yet been allocated a block
          log.debug("TrackSegement at connection D doesn't contain a layout block");
      }
     }
    }
    return boundaryBetween;
}


/**
 * Edit a Level Crossing
 */
/*protected*/ void LevelXing::editLevelXing(/*LevelXing* o*/) {
    if (editOpen) {
        editLevelXingFrame->setVisible(true);
        return;
    }
    // Initialize if needed
    if (editLevelXingFrame == NULL)
    {
//        editLevelXingFrame = new JmriJFrame( tr("EditXing"), false, true );
        editLevelXingFrame = new EditLevelXingDlg(this, layoutEditor);
//        editLevelXingFrame.addHelpMenu("package.jmrit.display.EditLevelXing", true);
//        editLevelXingFrame.setLocation(50,30);
//        Container contentPane = editLevelXingFrame.getContentPane();
//        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
//        // setup block 1 name
//        JPanel panel1 = new JPanel();
//        panel1.setLayout(new FlowLayout());
//        JLabel block1NameLabel = new JLabel( rb.getQString("Block1ID") );
//        panel1.add(block1NameLabel);
//        panel1.add(block1Name);
//        block1Name.setToolTipText( rb.getQString("EditBlockNameHint") );
//        contentPane.add(panel1);
//        // setup block 2 name
//        JPanel panel2 = new JPanel();
//        panel2.setLayout(new FlowLayout());
//        JLabel block2NameLabel = new JLabel( rb.getQString("Block2ID"));
//        panel2.add(block2NameLabel);
//        panel2.add(block2Name);
//        block2Name.setToolTipText( rb.getQString("EditBlockNameHint") );
//        contentPane.add(panel2);
//        // set up Edit 1 Block and Edit 2 Block buttons
//        JPanel panel4 = new JPanel();
//        panel4.setLayout(new FlowLayout());
//        // Edit 1 Block
//        panel4.add(xingEdit1Block = new JButton(rb.getQString("EditBlock1")));
//        xingEdit1Block.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                on_xingEdit1Block_clicked(e);
//            }
//        });
//        xingEdit1Block.setToolTipText( rb.getQString("EditBlockHint") );
//        // Edit 2 Block
//        panel4.add(xingEdit2Block = new JButton(rb.getQString("EditBlock2")));
//        xingEdit2Block.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                on_xingEdit2Block_clicked(e);
//            }
//        });
//        xingEdit2Block.setToolTipText( rb.getQString("EditBlockHint") );
//        contentPane.add(panel4);
//        // set up Done and Cancel buttons
//        JPanel panel5 = new JPanel();
//        panel5.setLayout(new FlowLayout());
//        panel5.add(xingEditDone = new JButton(rb.getQString("Done")));
//        xingEditDone.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                on_xingEditDone_clicked(e);
//            }
//        });
//        xingEditDone.setToolTipText( rb.getQString("DoneHint") );
//        // Cancel
//        panel5.add(xingEditCancel = new JButton(rb.getQString("Cancel")));
//        xingEditCancel.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                on_xingEditCancel_clicked(e);
//            }
//        });
//        xingEditCancel.setToolTipText( rb.getQString("CancelHint") );
//        contentPane.add(panel5);
    }
    // Set up for Edit
    block1Name->setText(blockNameAC);
    block2Name->setText(blockNameBD);
//    editLevelXingFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                on_xingEditCancel_clicked(NULL);
//            }
//        });
//    editLevelXingFrame->pack();
    editLevelXingFrame->setVisible(true);
    editOpen = true;
    needsBlockUpdate = false;
}
void LevelXing::on_xingEdit1Block_clicked()
{
    // check if a block name has been entered
    if (blockNameAC!=(block1Name->text().trimmed()) ) {
        // block 1 has changed, if old block exists, decrement use
        if ( (blockAC!=NULL) && (blockAC!=blockBD) ) {
            blockAC->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameAC = block1Name->text().trimmed();
        if ( (blockNameAC!=NULL) && (blockNameAC.length()>0)) {
            blockAC = layoutEditor->provideLayoutBlock(blockNameAC);
            if (blockAC!=NULL) {
                // decrement use if block was previously counted
                if ( (blockAC!=NULL) && (blockAC==blockBD) ) blockAC->decrementUse();
            }
            else {
                blockNameAC = "";
                block1Name->setText("");
            }
        }
        else {
            blockAC = NULL;
            blockNameAC = "";
        }
        needsRedraw = true;
        layoutEditor->auxTools->setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockAC==NULL) {
//        JOptionPane.showMessageDialog(editLevelXingFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockAC->editLayoutBlock(editLevelXingFrame);
    needsRedraw = true;
}
void LevelXing::on_xingEdit2Block_clicked()
{
    // check if a block name has been entered
    if (blockNameBD!=(block2Name->text().trimmed()) ) {
        // block has changed, if old block exists, decrement use
        if ( (blockBD!=NULL) && (blockBD!=blockAC) ) {
            blockBD->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameBD = block2Name->text().trimmed();
        if ( (blockNameBD!=NULL) && (blockNameBD.length()>0)) {
            blockBD = layoutEditor->provideLayoutBlock(blockNameBD);
            if (blockBD!=NULL) {
                // decrement use if block was previously counted
                if ( (blockBD!=NULL) && (blockAC==blockBD) ) blockBD->decrementUse();
            }
            else {
                blockNameBD = "";
                block2Name->setText("");
            }
        }
        else {
            blockBD = NULL;
            blockNameBD = "";
        }
        needsRedraw = true;
        layoutEditor->auxTools->setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockBD==NULL) {
//        JOptionPane.showMessageDialog(editLevelXingFrame,
//                rb.getQString("Error1"),
//                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockBD->editLayoutBlock(editLevelXingFrame);
    needsRedraw = true;
}
void LevelXing::on_xingEditDone_clicked() {
    // check if Blocks changed
    if ( blockNameAC!=(block1Name->text().trimmed()) ) {
        // block 1 has changed, if old block exists, decrement use
        if ( (blockAC!=NULL) && (blockAC!=blockBD) ) {
            blockAC->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameAC = block1Name->text().trimmed();
        if ( (blockNameAC!=NULL) && (blockNameAC.length()>0)) {
            blockAC = layoutEditor->provideLayoutBlock(blockNameAC);
            if (blockAC!=NULL) {
                // decrement use if block was previously counted
                if ( (blockAC!=NULL) && (blockAC==blockBD) ) blockAC->decrementUse();
            }
            else {
                blockNameAC = "";
                block1Name->setText("");
            }
        }
        else {
            blockAC = NULL;
            blockNameAC = "";
        }
        needsRedraw = true;
        layoutEditor->auxTools->setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    if ( blockNameBD!=(block2Name->text().trimmed()) ) {
        // block 2 has changed, if old block exists, decrement use
        if ( (blockBD!=NULL) && (blockBD!=blockAC) ) {
            blockBD->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockNameBD = block2Name->text().trimmed();
        if ( (blockNameBD!=NULL) && (blockNameBD.length()>0)) {
            blockBD = layoutEditor->provideLayoutBlock(blockNameBD);
            if (blockBD!=NULL) {
                // decrement use if block was previously counted
                if ( (blockBD!=NULL) && (blockAC==blockBD) ) blockBD->decrementUse();
            }
            else {
                blockNameBD = "";
                block2Name->setText("");
            }
        }
        else {
            blockBD = NULL;
            blockNameBD = "";
        }
        needsRedraw = true;
        layoutEditor->auxTools->setBlockConnectivityChanged();
        needsBlockUpdate = true;
    }
    editOpen = false;
    editLevelXingFrame->setVisible(false);
    //editLevelXingFrame->dispose();
    editLevelXingFrame = NULL;
    if (needsBlockUpdate) updateBlockInfo();
    if (needsRedraw) {
//        layoutEditor->redrawPanel();
//        layoutEditor->setDirty();
    }
}
void LevelXing::on_xingEditCancel_clicked()
{
    editOpen = false;
//    editLevelXingFrame->setVisible(false);
//    editLevelXingFrame->dispose();
    editLevelXingFrame = NULL;
    if (needsBlockUpdate) updateBlockInfo();
    if (needsRedraw) {
//        layoutEditor->redrawPanel();
//        layoutEditor->setDirty();
    }
}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void LevelXing::dispose() {
    if (popup != NULL) popup->clear();
    popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void LevelXing::remove() {
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LevelXing::isActive() {
    return active;
}


/*public*/ void LevelXing::addSignalMastLogic(SignalMast* sm){
    if (sml->contains(sm))
        return;
    if(sml->isEmpty()){
        sml->append(sm);
        return;
    }
    SignalMastLogic* sl = InstanceManager::signalMastLogicManagerInstance()->getSignalMastLogic(sm);
    for(int i = 0; i<sml->size(); i++){
        SignalMastLogic* s = InstanceManager::signalMastLogicManagerInstance()->getSignalMastLogic(sml->at(i));
        if (s!=NULL){
            s->setConflictingLogic(sm, this);
        }
        sl->setConflictingLogic(sml->at(i), this);
    }
    sml->append(sm);
}

/*public*/ void LevelXing::removeSignalMastLogic(SignalMast* sm){
    if(!sml->contains(sm))
        return;
    sml->remove(sml->indexOf(sm));
    if(sml->isEmpty()){
        return;
    }
    for(int i = 0; i<sml->size(); i++){
        SignalMastLogic* s = InstanceManager::signalMastLogicManagerInstance()->getSignalMastLogic(sm);
        if (s!=NULL)
            s->removeConflictingLogic(sm, this);
    }
}


/*public*/ void LevelXing::addEditPopUpMenu(QMenu* menu){
    if(!editAdditionalMenu->contains(menu)){
        editAdditionalMenu->append(menu);
    }
}

/*public*/ void LevelXing::addViewPopUpMenu(QMenu* menu){
    if(!viewAdditionalMenu->contains(menu)){
        viewAdditionalMenu->append(menu);
    }
}

/*public*/ void LevelXing::setAdditionalEditPopUpMenu(QMenu* popup){
    if(editAdditionalMenu->isEmpty())
        return;
    popup->addSeparator();
//    foreach(QAction* mi, editAdditionalMenu){
//        popup->addAction(mi);
//    }
}

///*public*/ void LevelXing::setAdditionalViewPopUpMenu(JPopupMenu popup){
//    if(viewAdditionalMenu.isEmpty())
//        return;
//    popup.addSeparator();
//    for(JMenuItem mi:viewAdditionalMenu){
//        popup.add(mi);
//    }
//}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LevelXing.class.getName());
void LevelXing::on_removeAction_triggered()
{
 if( layoutEditor->removeLevelXing(this))
 {
  remove();
  dispose();
 }
}
void LevelXing::invalidate(QGraphicsScene* g2)
{
 if(item != NULL && item->scene() != 0)
 {
  Q_ASSERT(item->scene()!=0);
  g2->removeItem(item);
 }
 item = NULL;
 if(rects != NULL && rects->scene()!=0)
 {
  g2->removeItem(rects);
 }
 rects = NULL;
}
void LevelXing::drawXings(LayoutEditor* editor, QGraphicsScene* g2)
{
// if(item != NULL)
// {
//  g2->removeItem(item);
// }
 item = new QGraphicsItemGroup();

 if ( isMainlineBD() && (!isMainlineAC()) )
 {
  drawXingAC(editor);
  drawXingBD(editor);
 }
 else
 {
  drawXingBD(editor);
  drawXingAC(editor);
 }
 g2->addItem(item);
}

/*private*/ void LevelXing::drawXingAC(LayoutEditor* editor)
{
  // set color - check for an AC block
  LayoutBlock* b = getLayoutBlockAC();
  QColor color;
  if (b!=NULL)
  {
   //g2.setColor(b->getBlockColor());
   color = b->getBlockColor();
  }
  else
  {
   //g2.setColor(defaultTrackColor);
   color = editor->defaultTrackColor;
  }
  // set track width for AC block
  editor->setTrackStrokeWidth(isMainlineAC());
  // draw AC segment
  //g2.draw(new Line2D.Double(x.getCoordsA(),x.getCoordsC()));
  QGraphicsLineItem* line = new QGraphicsLineItem(getCoordsA().x(), getCoordsA().y(), getCoordsC().x(), getCoordsC().y(),0);
  line->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line);
  item->addToGroup(line);
}
/*private*/ void LevelXing::drawXingBD(LayoutEditor* editor)
{
  // set color - check for an BD block
  QColor color;
  LayoutBlock* b = getLayoutBlockBD();
  if (b!=NULL)
  {
   color = b->getBlockColor();
  }
  else
  {
   color= editor->defaultTrackColor;
  }
  Q_ASSERT(color.isValid());

  // set track width for BD block
  editor->setTrackStrokeWidth(isMainlineBD());
  // draw BD segment
  //g2.draw(new Line2D.Double(x.getCoordsB(),x.getCoordsD()));
  QGraphicsLineItem* line = new QGraphicsLineItem(getCoordsB().x(), getCoordsB().y(), getCoordsD().x(), getCoordsD().y(),0);
  line->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line);
  item->addToGroup(line);
}
void LevelXing::drawXingRects(LayoutEditor* editor, QGraphicsScene* g2)
{
 QColor color;
 rects = new QGraphicsItemGroup();

 QPointF pt = getCoordsCenter();
//      g2.setColor(defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
 QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pt.x()-LayoutEditor::SIZE2, pt.y()-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, 0);
  ellipse->setPen(QPen(editor->defaultTrackColor, 1, Qt::SolidLine ) );
  //g2->addItem(ellipse);
  rects->addToGroup(ellipse);
  pt = getCoordsA();
 if (getConnectA()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem1 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem1->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem1);
 rects->addToGroup(rectItem1);
 pt = getCoordsB();
 if (getConnectB()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
         //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem2 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem2->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem2);
 rects->addToGroup(rectItem2);
 pt = getCoordsC();
 if (getConnectC()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem3 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem3->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem3);
 rects->addToGroup(rectItem3);
 pt = getCoordsD();
 if (getConnectD()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else
 {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem4 = new QGraphicsRectItem (QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem4->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem4);
 rects->addToGroup(rectItem4);

 g2->addItem(rects);
}

