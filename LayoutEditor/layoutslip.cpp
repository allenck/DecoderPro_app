#include "layoutslip.h"
#include "layoutturnout.h"
#include "layoutblock.h"
#include "inputdialog.h"
#include <QMessageBox>
#include "editturnout.h"
#include "jmrijframe.h"
#include "jmribeancombobox.h"
#include "jtextfield.h"
#include "signalmastmanager.h"
#include "signalmastlogicmanager.h"
#include "createeditblock.h"
#include "mathutil.h"
#include "signallingguitools.h"


//LayoutSlip::LayoutSlip(QObject *parent) :
//    LayoutTurnout(parent)
//{
//}
///*final*/ /*public*/ const /*static*/ int LayoutSlip::UNKNOWN = 0x01;
///*final*/ /*public*/ const /*static*/ int LayoutSlip::STATE_AC = 0x02;
///*final*/ /*public*/ const /*static*/ int LayoutSlip::STATE_BD = 0x04;
///*final*/ /*public*/ const /*static*/ int LayoutSlip::STATE_AD = 0x06;
///*final*/ /*public*/ const /*static*/ int LayoutSlip::STATE_BC = 0x08;


QComboBox* TurnoutState::getComboA()
{
 if(turnoutABox==nullptr)
 {
  QStringList state;
  state << ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() << ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
  turnoutABox = new QComboBox();
  turnoutABox->addItems(state);
  if(turnoutA == Turnout::THROWN)
   turnoutABox->setCurrentIndex(1);
 }
 return turnoutABox;
}

QComboBox* TurnoutState::getComboB()
{
 if(turnoutBBox==nullptr)
 {
  QStringList state;
  state << ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() << ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
  turnoutBBox = new QComboBox();
  turnoutBBox->addItems(state);
  if(turnoutB == Turnout::THROWN)
   turnoutBBox->setCurrentIndex(1);
 }
 return turnoutBBox;
}

/**
 * A LayoutSlip is two track segment on a layout that cross at an angle.
 * <P>
 * A LayoutSlip has four connection points, designated A, B, C, and D.
 *		At the crossing, A-C and B-D are straight segments.  A train proceeds
 *		through the crossing on either of these segments.
 * <P>
 * For drawing purposes, each LayoutSlip carries a center point and displacements
 *		for A and B.  The displacements for C = - the displacement for A, and the
 *		displacement for D = - the displacement for B.  The center point and these
 *      displacements may be adjusted by the user when in edit mode.
 * <P>
 * When LayoutSlips are first created, there are no connections.  Block information
 *		and connections are added when available.
 * <P>
 * Signal Head names are saved here to keep track of where signals are. LayoutSlip
 *		only serves as a storage place for signal head names. The names are placed here
 *		by Set Signals at Level Crossing in Tools menu.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 19729 $
 */

///*public*/ class LayoutSlip extends LayoutTurnout
//{

//	// Defined text resource
//	ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

/**
 * constructor method
 */
/*public*/ LayoutSlip::LayoutSlip(QString id, QPointF c, double rot, LayoutEditor* myPanel, int type) : LayoutTurnout(id, -1, c,rot,0,0,myPanel)
{
 init();
 //instance = this;
 layoutEditor = myPanel;
 //ident = id;
 //center = c;
 dispC =  QPointF(-20.0,0.0);
 dispB =  QPointF(-14.0,14.0);
 setTurnoutType(type);
 rotateCoords(rot);
}
void LayoutSlip::init()
{
 turnoutBName="";
 namedTurnoutB = nullptr;
 mTurnoutListener = nullptr;
 popup = nullptr;
 tools = nullptr;
 testState = UNKNOWN;
 active = true;
 turnoutStates =  QHash<int, TurnoutState*>();
 currentState = UNKNOWN;
 connectA = nullptr;
 connectB = nullptr;
 connectC = nullptr;
 connectD = nullptr;
 needRedraw = false;
 needsBlockUpdate = false;
 namedTurnout = nullptr;
 editOpen = false;
 active = false;
 sensorANamed =nullptr;
 sensorBNamed = nullptr;
 sensorCNamed = nullptr;
 sensorDNamed = nullptr;
 rects = nullptr;
 editAdditionalMenu = new QVector<QObject*>();
 viewAdditionalMenu = new QVector<QObject*>();
 editOpen = false;
}

/*public*/ void LayoutSlip::setTurnoutType(int slipType)
{
 setSlipType(slipType);
 type = slipType;
}

/*public*/ void LayoutSlip::setSlipType(int slipType)
{
 if(type==slipType)
  return;
 type=slipType;
 if(type==DOUBLE_SLIP)
 {
  turnoutStates.insert(STATE_AC, new TurnoutState(Turnout::CLOSED, Turnout::CLOSED));
  turnoutStates.insert(STATE_BD, new TurnoutState(Turnout::THROWN, Turnout::THROWN));
  turnoutStates.insert(STATE_AD, new TurnoutState(Turnout::CLOSED, Turnout::THROWN));
  turnoutStates.insert(STATE_BC, new TurnoutState(Turnout::THROWN, Turnout::CLOSED));
 }
 else
 {
  turnoutStates.insert(STATE_AC, new TurnoutState(Turnout::CLOSED, Turnout::THROWN));
  turnoutStates.insert(STATE_BD, new TurnoutState(Turnout::THROWN, Turnout::CLOSED));
  turnoutStates.insert(STATE_AD, new TurnoutState(Turnout::THROWN, Turnout::THROWN));
  turnoutStates.remove(STATE_BC);
 }
}

/*public*/ int LayoutSlip::getSlipType()
{
 return type;
}

/*public*/ int LayoutSlip::getSlipState()
{
 return currentState;
}

/*public*/ QString LayoutSlip::getTurnoutBName()
{
 if (namedTurnoutB!=nullptr)
     return namedTurnoutB->getName();
 return turnoutBName;
}

/*public*/ Turnout* LayoutSlip::getTurnoutB()
{
 if (namedTurnoutB==nullptr)
 {
  // set physical turnout if possible and needed
  setTurnoutB(turnoutBName);
  if (namedTurnoutB==nullptr)
   return nullptr;
 }
 return namedTurnoutB->getBean();
}

/*public*/ void LayoutSlip::setTurnoutB(QString tName)
{
 if (namedTurnoutB!=nullptr)
  deactivateTurnout();
 turnoutBName = tName;
 Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                     getTurnout(turnoutBName);
 if (turnout!=nullptr)
 {
  namedTurnoutB =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutBName, turnout);
  activateTurnout();
 }
 else
 {
  turnoutBName = "";
  namedTurnoutB = nullptr;
 }
}

//@Override
/*public*/ LayoutTrack *LayoutSlip::getConnection(int location) throw (JmriException) {
    switch (location) {
        case SLIP_A:
            return connectA;
        case SLIP_B:
            return connectB;
        case SLIP_C:
            return connectC;
        case SLIP_D:
            return connectD;
    }
    log.error("Invalid Point Type " + QString::number(location)); //I18IN
    throw new JmriException("Invalid Point");
}

//@Override
/*public*/ void LayoutSlip::setConnection(int location, LayoutTrack* o, int type) throw (JmriException) {
    if ((type != TRACK) && (type != NONE)) {
        log.error("unexpected type of connection to layoutturnout - " + QString::number(type));
        throw JmriException("unexpected type of connection to layoutturnout - " + QString::number(type));
    }
    switch (location) {
        case SLIP_A:
            connectA = o;
            break;
        case SLIP_B:
            connectB = o;
            break;
        case SLIP_C:
            connectC = o;
            break;
        case SLIP_D:
            connectD = o;
            break;
        default:
            log.error("Invalid Point Type " + location); //I18IN
            throw JmriException("Invalid Point");
    }
}

/*public*/ QString LayoutSlip::getDisplayName()
{
 QString name = "Slip :";
 if(getTurnoutName()!=nullptr)
 {
  name += "("+getTurnoutName();
  if(getTurnoutBName()!=nullptr)
   name+=":"+getTurnoutBName()+")";
 }
 else if(getTurnoutBName()!=nullptr)
 {
  name += "("+getTurnoutBName()+")";
 }
 return name;
}

/**
 * Toggle slip states if clicked on, physical turnout exists, and
 *    not disabled
 */
/*public*/ void LayoutSlip::toggleState(int selectedPointType)
{
 switch (selectedPointType) {
     case SLIP_LEFT: {
         switch (currentState) {
             case STATE_AC: {
                 if (type == SINGLE_SLIP) {
                     currentState = STATE_BD;
                 } else {
                     currentState = STATE_BC;
                 }
                 break;
             }
             case STATE_BD: {
                 currentState = STATE_AD;
                 break;
             }
             case STATE_AD: {
                 currentState = STATE_BD;
                 break;
             }
             case STATE_BC:
             default: {
                 currentState = STATE_AC;
                 break;
             }
         }
         break;
     }
     case SLIP_RIGHT: {
         switch (currentState) {
             case STATE_AC: {
                 currentState = STATE_AD;
                 break;
             }
             case STATE_BD: {
                 if (type == SINGLE_SLIP) {
                     currentState = STATE_AC;
                 } else {
                     currentState = STATE_BC;
                 }
                 break;
             }
             case STATE_AD: {
                 currentState = STATE_AC;
                 break;
             }
             case STATE_BC:
             default: {
                 currentState = STATE_BD;
                 break;
             }
         }
         break;
     }
     case SLIP_CENTER:   //note: this should "go away"
     //(since SLIP_CENTER should have been replaced by SLIP_LEFT & SLIP_RIGHT everywhere)
     default:
     {
         switch (currentState) {
             case STATE_AC: {
                 if (singleSlipStraightEqual()) {
                     currentState = STATE_BD;
                 } else {
                     currentState = STATE_BC;
                 }
                 break;
             }

             case STATE_BD: {
                 currentState = STATE_AD;
                 break;
             }

             case STATE_AD: {
                 currentState = STATE_AC;
                 break;
             }

             case STATE_BC:
             default: {
                 currentState = STATE_BD;
                 break;
             }
         }
         break;
     }
 }
 setTurnoutState(turnoutStates.value(currentState));

}

void LayoutSlip::setTurnoutState(TurnoutState* ts)
{
 if(getTurnout()!=nullptr)
     getTurnout()->setCommandedState(ts->getTurnoutAState());
 if(getTurnoutB()!=nullptr)
     getTurnoutB()->setCommandedState(ts->getTurnoutBState());
}

/**
 * Activate/Deactivate turnout to redraw when turnout state changes
 */
/*private*/ void LayoutSlip::activateTurnout()
{
 if (namedTurnout!=nullptr)
 {
//        namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener =
//                            new PropertyChangeListener());
//        {
//            /*public*/ void propertyChange(PropertyChangeEvent* e) {
//                updateState();
//            }
//        }, namedTurnoutgetName(), "Layout Editor Slip");
     AbstractTurnout* t = (AbstractTurnout* )namedTurnout->getBean();
     connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(updateState()));
    }
    if (namedTurnoutB!=nullptr)
    {
//        namedTurnoutB->getBean()->addPropertyChangeListener(mTurnoutListener =
//                            new PropertyChangeListener());
//        {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                updateState();
//            }
//        }, namedTurnoutB.getName(), "Layout Editor Slip");
        AbstractTurnout* t = (AbstractTurnout*)namedTurnoutB->getBean();
        connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(updateState()));

    }
}
/*private*/ void LayoutSlip::deactivateTurnout()
{
    if (mTurnoutListener!=nullptr) {
        namedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
        if(namedTurnoutB!=nullptr){
            namedTurnoutB->getBean()->removePropertyChangeListener(mTurnoutListener);
        }
        mTurnoutListener = nullptr;
    }
}

/*public*/ QPointF LayoutSlip::getCoordsCenter() {return center;}
/*public*/ QPointF LayoutSlip::getCoordsA() {
    double x = center.x() + dispC.x();
    double y = center.y() + dispC.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LayoutSlip::getCoordsB() {
    double x = center.x() + dispB.x();
    double y = center.y() + dispB.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LayoutSlip::getCoordsC() {
    double x = center.x() - dispC.x();
    double y = center.y() - dispC.y();
    return  QPointF(x,y);
}
/*public*/ QPointF LayoutSlip::getCoordsD() {
    double x = center.x() - dispB.x();
    double y = center.y() - dispB.y();
    return  QPointF(x,y);
}
/*protected*/ QPointF LayoutSlip::getCoordsLeft() {
    QPointF leftCenter = MathUtil::midPoint(getCoordsA(), getCoordsB());
    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double leftFract = circleRadius / MathUtil::distance(center, leftCenter);//center.distance(leftCenter);
    return MathUtil::lerp(center, leftCenter, leftFract);
}

/*protected*/ QPointF LayoutSlip::getCoordsRight() {
    QPointF rightCenter = MathUtil::midPoint(getCoordsC(), getCoordsD());
    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double rightFract = circleRadius / MathUtil::distance(center, rightCenter);//center.distance(rightCenter);
    return MathUtil::lerp(center, rightCenter, rightFract);
}
/**
 * return the coordinates for the specified connection type
 *
 * @param connectionType the connection type
 * @return the QPointF coordinates
 */
//@Override
/*public*/ QPointF LayoutSlip::getCoordsForConnectionType(int connectionType) {
    QPointF result = center;
    switch (connectionType) {
        case SLIP_A:
            result = getCoordsA();
            break;
        case SLIP_B:
            result = getCoordsB();
            break;
        case SLIP_C:
            result = getCoordsC();
            break;
        case SLIP_D:
            result = getCoordsD();
            break;
        case SLIP_CENTER:
            break;
        case SLIP_LEFT:
            result = getCoordsLeft();
            break;
        case SLIP_RIGHT:
            result = getCoordsRight();
            break;
        default:
            log.error("Invalid connection type " + QString(connectionType)); //I18IN
    }
    return result;
}
/*private*/ void LayoutSlip::updateBlockInfo()
{
 LayoutBlock* b1 = nullptr;
 LayoutBlock* b2 = nullptr;
 if (block!=nullptr) block->updatePaths();
 if (connectA!=nullptr) {
     b1 = ((TrackSegment*)connectA)->getLayoutBlock();
     if ((b1!=nullptr)&&(b1!=block)) b1->updatePaths();
 }
 if (connectC!=nullptr)
 {
     b2 = ((TrackSegment*)connectC)->getLayoutBlock();
     if ((b2!=nullptr)&&(b2!=block)&&(b2!=b1)) b2->updatePaths();
 }

 if (connectB!=nullptr)
 {
     b1 = ((TrackSegment*)connectB)->getLayoutBlock();
     if ((b1!=nullptr)&&(b1!=block)) b1->updatePaths();
 }
 if (connectD!=nullptr)
 {
     b2 = ((TrackSegment*)connectD)->getLayoutBlock();
     if ((b2!=nullptr)&&(b2!=block)&&(b2!=b1)) b2->updatePaths();
 }
 reCheckBlockBoundary();
}
/*
    this is used by ConnectivityUtil to determine the turnout state necessary to get from prevLayoutBlock ==> currLayoutBlock ==> nextLayoutBlock
 */
//@Override
/*protected*/ int LayoutSlip::getConnectivityStateForLayoutBlocks(
        /*@Nullable*/ LayoutBlock* thisLayoutBlock,
        /*@Nullable*/ LayoutBlock* prevLayoutBlock,
        /*@Nullable*/ LayoutBlock* nextLayoutBlock,
        bool suppress) {
    int result = Turnout::UNKNOWN;
    LayoutBlock* layoutBlockA = ((TrackSegment*) getConnectA())->getLayoutBlock();
    LayoutBlock* layoutBlockB = ((TrackSegment*) getConnectB())->getLayoutBlock();
    LayoutBlock* layoutBlockC = ((TrackSegment*) getConnectC())->getLayoutBlock();
    LayoutBlock* layoutBlockD = ((TrackSegment*) getConnectD())->getLayoutBlock();

    if (layoutBlockA == thisLayoutBlock) {
        if (layoutBlockC == nextLayoutBlock || layoutBlockC == prevLayoutBlock) {
            result = LayoutSlip::STATE_AC;
        } else if (layoutBlockD == nextLayoutBlock || layoutBlockD == prevLayoutBlock) {
            result = LayoutSlip::STATE_AD;
        } else if (layoutBlockC == thisLayoutBlock) {
            result = LayoutSlip::STATE_AC;
        } else if (layoutBlockD == thisLayoutBlock) {
            result = LayoutSlip::STATE_AD;
        }
    } else if (layoutBlockB == thisLayoutBlock) {
        if (getTurnoutType() == LayoutSlip::DOUBLE_SLIP) {
            if (layoutBlockD == nextLayoutBlock || layoutBlockD == prevLayoutBlock) {
                result = LayoutSlip::STATE_BD;
            } else if (layoutBlockC == nextLayoutBlock || layoutBlockC == prevLayoutBlock) {
                result = LayoutSlip::STATE_BC;
            } else if (layoutBlockD == thisLayoutBlock) {
                result = LayoutSlip::STATE_BD;
            } else if (layoutBlockC == thisLayoutBlock) {
                result = LayoutSlip::STATE_BC;
            }
        } else {
            if (layoutBlockD == nextLayoutBlock || layoutBlockD == prevLayoutBlock) {
                result = LayoutSlip::STATE_BD;
            } else if (layoutBlockD == thisLayoutBlock) {
                result = LayoutSlip::STATE_BD;
            }
        }
    } else if (layoutBlockC == thisLayoutBlock) {
        if (getTurnoutType() == LayoutSlip::DOUBLE_SLIP) {
            if (layoutBlockA == nextLayoutBlock || layoutBlockA == prevLayoutBlock) {
                result = LayoutSlip::STATE_AC;
            } else if (layoutBlockB == nextLayoutBlock || layoutBlockB == prevLayoutBlock) {
                result = LayoutSlip::STATE_BC;
            } else if (layoutBlockA == thisLayoutBlock) {
                result = LayoutSlip::STATE_AC;
            } else if (layoutBlockB == thisLayoutBlock) {
                result = LayoutSlip::STATE_BC;
            }
        } else {
            if (layoutBlockA == nextLayoutBlock || layoutBlockA == prevLayoutBlock) {
                result = LayoutSlip::STATE_AC;
            } else if (layoutBlockA == thisLayoutBlock) {
                result = LayoutSlip::STATE_AC;
            }
        }
    } else if (layoutBlockD == thisLayoutBlock) {
        if (layoutBlockA == nextLayoutBlock || layoutBlockA == prevLayoutBlock) {
            result = LayoutSlip::STATE_AD;
        } else if (layoutBlockB == nextLayoutBlock || layoutBlockB == prevLayoutBlock) {
            result = LayoutSlip::STATE_BD;
        } else if (layoutBlockA == thisLayoutBlock) {
            result = LayoutSlip::STATE_AD;
        } else if (layoutBlockB == thisLayoutBlock) {
            result = LayoutSlip::STATE_AD;
        }
    } else {
        result = LayoutSlip::UNKNOWN;
    }
    if (!suppress && (result == LayoutSlip::UNKNOWN)) {
        log.error("Cannot determine slip setting for " + getName());
    }
    return result;
}   // getConnectivityStateForLayoutBlocks

/*public*/ void LayoutSlip::reCheckBlockBoundary(){
    if(connectA==nullptr && connectB==nullptr && connectC==nullptr && connectD==nullptr){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
        if(getSignalAMastName()!=(""))
            removeSML(getSignalAMastName());
        if(getSignalBMastName()!=(""))
            removeSML(getSignalBMastName());
        if(getSignalCMastName()!=(""))
            removeSML(getSignalCMastName());
        if(getSignalDMastName()!=(""))
            removeSML(getSignalDMastName());
        setSignalAMast("");
        setSignalBMast("");
        setSignalCMast("");
        setSignalDMast("");
        setSensorA("");
        setSensorB("");
        setSensorC("");
        setSensorD("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any logics generated
    }  else if(connectA==nullptr || connectB==nullptr || connectC==nullptr || connectD==nullptr){
        //could still be in the process of rebuilding the point details
        return;
    }

    TrackSegment* trkA;
    TrackSegment* trkB;
    TrackSegment* trkC;
    TrackSegment* trkD;

    //if(connectA instanceof TrackSegment){
    if(qobject_cast<TrackSegment*>(connectA)!= nullptr)
    {
        trkA = (TrackSegment*)connectA;
        if(trkA->getLayoutBlock()==block)
        {
            if(getSignalAMastName()!=(""))
                removeSML(getSignalAMastName());
            setSignalAMast("");
            setSensorA("");
        }
    }
    //if(connectC instanceof TrackSegment) {
    if(qobject_cast<TrackSegment*>(connectC)!= nullptr)
    {
        trkC = (TrackSegment*)connectC;
        if(trkC->getLayoutBlock()==block){
            if(getSignalCMastName()!=(""))
                removeSML(getSignalCMastName());
            setSignalCMast("");
            setSensorC("");
        }
    }
    //if(connectB instanceof TrackSegment){
    if(qobject_cast<TrackSegment*>(connectB)!= nullptr)
    {
        trkB = (TrackSegment*)connectB;
        if(trkB->getLayoutBlock()==block){
            if(getSignalBMastName()!=(""))
                removeSML(getSignalBMastName());
            setSignalBMast("");
            setSensorB("");
        }
    }

    //if(connectD instanceof TrackSegment) {
    if(qobject_cast<TrackSegment*>(connectD)!= nullptr)
    {
        trkD = (TrackSegment*)connectC;
        if(trkD->getLayoutBlock()==block){
            if(getSignalDMastName()!=(""))
                removeSML(getSignalDMastName());
            setSignalDMast("");
            setSensorD("");
        }
    }
}

void LayoutSlip::removeSML(QString signalMast){
#if 1 // TODO:
    if(signalMast==nullptr || signalMast == (""))
        return;
    SignalMast* mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
    if(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->isAdvancedRoutingEnabled() && InstanceManager::signalMastLogicManagerInstance()->isSignalMastUsed(mast)){
        InstanceManager::signalMastLogicManagerInstance()->disableLayoutEditorUse(mast);
        SignallingGuiTools::removeSignalMastLogic(nullptr, mast);
    }
#endif
}

/**
 * Methods to test if mainline track or not
 *  Returns true if either connecting track segment is mainline
 *  Defaults to not mainline if connecting track segments are missing
 */
/*public*/ bool LayoutSlip::isMainline() {
    if ( ((connectA != nullptr) && (((TrackSegment*)connectA)->getMainline())) ||
        ((connectB != nullptr) && (((TrackSegment*)connectB)->getMainline())) ) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ int LayoutSlip::findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    int result = NONE;  // assume point not on connection

    if (!requireUnconnected) {
        // calculate radius of turnout control circle
        double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();

        // get left and right centers
        QPointF leftCenter = getCoordsLeft();
        QPointF rightCenter = getCoordsRight();

        if (useRectangles) {
            // calculate turnout's left control rectangle
            QRectF leftRectangle = layoutEditor->trackControlCircleRectAt(leftCenter);
            if (leftRectangle.contains(hitPoint)) {
                //point is in this turnout's left control rectangle
                result = SLIP_LEFT;
            }
            QRectF rightRectangle = layoutEditor->trackControlCircleRectAt(rightCenter);
            if (rightRectangle.contains(hitPoint)) {
                //point is in this turnout's right control rectangle
                result = SLIP_RIGHT;
            }
        } else {
            //check east/west turnout control circles
            double leftDistance = MathUtil::distance(hitPoint,leftCenter);
            double rightDistance = MathUtil::distance(hitPoint, rightCenter);

            if ((leftDistance <= circleRadius) || (rightDistance <= circleRadius)) {
                //mouse was pressed on this slip
                result = (leftDistance < rightDistance) ? SLIP_LEFT : SLIP_RIGHT;
            }
        }
    }

    // have we found anything yet?
    if (result == NONE) {
        // rather than create rectangles for all the points below and
        // see if the passed in point is in one of those rectangles
        // we can create a rectangle for the passed in point and then
        // test if any of the points below are in that rectangle instead.
        QRectF r = layoutEditor->trackEditControlRectAt(hitPoint);

        if (!requireUnconnected || (getConnectA() == nullptr)) {
            //check the A connection point
            if (r.contains(getCoordsA())) {
                result = SLIP_A;
            }
        }

        if (!requireUnconnected || (getConnectB() == nullptr)) {
            //check the B connection point
            if (r.contains(getCoordsB())) {
                result = SLIP_B;
            }
        }

        if (!requireUnconnected || (getConnectC() == nullptr)) {
            //check the C connection point
            if (r.contains(getCoordsC())) {
                result = SLIP_C;
            }
        }

        if (!requireUnconnected || (getConnectD() == nullptr)) {
            //check the D connection point
            if (r.contains(getCoordsD())) {
                result = SLIP_D;
            }
        }
    }
    return result;
}   // findHitPointType
/**
 * Modify coordinates methods
 */
/*public*/ void LayoutSlip::setCoordsCenter(QPointF p) {
    center = p;
}
/*public*/ void LayoutSlip::setCoordsA(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispC =  QPoint(-x,-y);
}
/*public*/ void LayoutSlip::setCoordsB(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(-x,-y);
}
/*public*/ void LayoutSlip::setCoordsC(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispC =  QPointF(x,y);
}
/*public*/ void LayoutSlip::setCoordsD(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(x,y);
}
/*public*/ void LayoutSlip::scaleCoords(float xFactor, float yFactor) {
    QPointF pt =  QPointF(round(center.x()*xFactor),
                                    round(center.y()*yFactor));
    center = pt;
    pt =  QPointF(round(dispC.x()*xFactor),
                                    round(dispC.y()*yFactor));
    dispC = pt;
    pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
}
double LayoutSlip::round (double x) {
    int i = (int)(x+0.5);
    return i;
}

/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LayoutSlip::setObjects(LayoutEditor* p) {
    connectA = p->findTrackSegmentByName(connectAName);
    connectB = p->findTrackSegmentByName(connectBName);
    connectC = p->findTrackSegmentByName(connectCName);
    connectD = p->findTrackSegmentByName(connectDName);
    if (tBlockName.length()>0) {
        block = p->getLayoutBlock(tBlockName);
        if (block!=nullptr) {
            blockName = tBlockName;
            block->incrementUse();
        }
        else {
            log.error("bad blocknameac '"+tBlockName+"' in slip "+ident);
        }
    }
}

/**
 * Display popup menu for information and editing
 */
/*protected*/ QMenu *LayoutSlip::showPopup(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popup != nullptr )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 if(layoutEditor->isEditable())
 {
  popup->addAction(new QAction(getName(),this));
  bool blockAssigned = false;
  if ( (blockName==nullptr) || (blockName==("")) )
   popup->addAction (new QAction(tr("NoBlock"),this));
  else
  {
   popup->addAction(new QAction(tr("Block ID")+": "+getLayoutBlock()->getID(), this));
   blockAssigned = true;
  }

  popup->addSeparator();
  QAction* editAction;
  popup->addAction(editAction =new QAction(tr("Edit"),this));
//        {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    editLayoutSlip(instance);
//                }
//            });
  connect(editAction, SIGNAL(triggered()), this, SLOT(OnEditAction()));
  QAction* removeAction;
  popup->addAction(removeAction = new QAction(tr("Remove"),this));
//        {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (layoutEditor.removeLayoutSlip(instance)) {
//                        // Returned true if user did not cancel
//                        remove();
//                        dispose();
//                    }
//                }
//            });
  connect(removeAction, SIGNAL(triggered()), this, SLOT(on_removeAction_triggered()));
  if ( (connectA==nullptr) && (connectB==nullptr) &&
                    (connectC==nullptr) && (connectD==nullptr) )
  {
   QAction* rotateItem = new QAction(tr("Rotate")+"...", this);
   popup->addAction(rotateItem);
   connect(rotateItem, SIGNAL(triggered()), this, SLOT(on_rotate_triggered()));
//            rotateItem.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent event) {
//                    bool entering = true;
//                    bool error = false;
//                    QString newAngle = "";
//                    while (entering) {
//                        // prompt for rotation angle
//                        error = false;
//                        newAngle = JOptionPane.showInputDialog(layoutEditor,
//                                            tr("EnterRotation")+" :");
//                        if (newAngle.length()<1) return;  // cancelled
//                        double rot = 0.0;
//                        try {
//                            rot = Double.parseDouble(newAngle);
//                        }
//                        catch (Exception e) {
//                            JOptionPane.showMessageDialog(layoutEditor,tr("Error3")+
//                                " "+e,tr("Error"),JOptionPane.ERROR_MESSAGE);
//                            error = true;
//                            newAngle = "";
//                        }
//                        if (!error) {
//                            entering = false;
//                            if (rot!=0.0) {
//                               rotateCoords(rot);
//                               layoutEditor.redrawPanel();
//                            }
//                        }
//                    }
//                }
//            });
   }
#if 1
   if (blockAssigned)
   {
         //            popup.add(new AbstractAction(tr("SetSignals")) {
         //                /*public*/ void actionPerformed(ActionEvent e) {
         //                        if (tools == NULL) {
         //                            tools = new LayoutEditorTools(layoutEditor);
         //                        }
         //                    tools.setSlipFromMenu((LayoutSlip)instance,
         //                            layoutEditor.signalIconEditor,layoutEditor.signalFrame);
         //                }
         //            });
     AbstractAction* setSignals = new AbstractAction(tr("Set Signals"),this);
     popup->addAction(setSignals);
     connect(setSignals, SIGNAL(triggered()), this, SLOT(on_setSignalsAct_triggered()));
    }

    /*final*/ QVector<QString>* boundaryBetween = getBlockBoundaries();
    bool blockBoundaries = false;

    for (int i = 0; i<4; i++)
    {
     if(boundaryBetween->at(i) !=nullptr)
      blockBoundaries=true;
    }
    if (blockBoundaries)
    {
//             popup.add(new AbstractAction(tr("SetSignalMasts")) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (tools == NULL) {
//                        tools = new LayoutEditorTools(layoutEditor);
//                    }
//                    tools.setSignalMastsAtSlipFromMenu((LayoutSlip)instance, boundaryBetween, layoutEditor.signalFrame);
//                }
//            });
     AbstractAction* setSignalMasts = new AbstractAction(tr("Set SignalMasts"), this);
     popup->addAction(setSignalMasts);
     connect(setSignalMasts, SIGNAL(triggered()), this, SLOT(on_setSignalMastsAct_triggered()));
//             popup.add(new AbstractAction(tr("SetSensors")) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (tools == NULL) {
//                        tools = new LayoutEditorTools(layoutEditor);
//                    }
//                    tools.setSensorsAtSlipFromMenu((LayoutSlip)instance, boundaryBetween, layoutEditor.sensorIconEditor, layoutEditor.sensorFrame);
//                }
//            });
  AbstractAction* setSensors = new AbstractAction(tr("Set Sensors"),this);
  popup->addAction(setSensors);
  connect(setSensors, SIGNAL(triggered()), this, SLOT(on_setSensorsAct_triggered()));
 }
#endif
     //if (InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled())
  if(layoutEditor->layoutBlockManager->isAdvancedRoutingEnabled())
  {
   if(blockAssigned)
   {
    QAction* routingAction;
    popup->addAction(routingAction = new QAction(tr("ViewBlockRouting"),this));
//             {
//                    /*public*/ void actionPerformed(ActionEvent e)
//                 {
//                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
//                        routeTableAction.actionPerformed(e);
//                    }
//                });
    connect(routingAction, SIGNAL(triggered()), this, SLOT(OnRoutingAction()));
   }
  }
  setAdditionalEditPopUpMenu(popup);
  layoutEditor->setShowAlignmentMenu(popup);
  //popup->show(e.getComponent(), e.x(), e.y());
  popup->exec(QCursor::pos());
 }
 else if(!viewAdditionalMenu->isEmpty())
 {
  setAdditionalViewPopUpMenu(popup);
  //popup.show(e.getComponent(), e.x(), e.y());
  popup->exec(QCursor::pos());
 }
 return popup;
}
void LayoutSlip::OnEditAction()
{
 editLayoutSlip(this);
}

void LayoutSlip::on_setSignalsAct_triggered()
{
 if (tools == nullptr)
 {
  tools = new LayoutEditorTools(layoutEditor);
 }
 tools->setSlipFromMenu(this,
 layoutEditor->signalIconEditor,layoutEditor->signalFrame);
}

void LayoutSlip::on_setSignalMastsAct_triggered()
{
 if (tools == nullptr)
 {
  tools = new LayoutEditorTools(layoutEditor);
 }
 tools->setSignalMastsAtSlipFromMenu(this, boundaryBetween, layoutEditor->signalFrame);
}

void LayoutSlip::on_setSensorsAct_triggered()
{
 if (tools == nullptr)
 {
  tools = new LayoutEditorTools(layoutEditor);
 }
 tools->setSensorsAtSlipFromMenu(this, boundaryBetween, layoutEditor->sensorIconEditor, layoutEditor->sensorFrame);
}

void LayoutSlip::on_rotate_triggered()
{
    bool entering = true;
    bool error = false;
    QString newAngle = "";
    while (entering)
    {
     // prompt for rotation angle
     error = false;
     newAngle = InputDialog::showInputDialog(tr("EnterRotation Angle (degrees CW)")+" :", layoutEditor);
     if (newAngle.length()<1) return;  // cancelled
     double rot = 0.0;
     try
     {
      bool bOk=false;
      rot = newAngle.toDouble(&bOk);
      if(!bOk) throw new Exception;
     }
     catch (Exception e)
     {
   //   JOptionPane.showMessageDialog(layoutEditor,tr("Error3")+
   //            " "+e,tr("Error"),JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(layoutEditor, "Error", tr("Invalid value"));
      error = true;
      newAngle = "";
     }
     if (!error)
     {
      entering = false;
      if (rot!=0.0)
      {
       rotateCoords(rot);
       layoutEditor->redrawPanel();
      }
     }
    }

}

void LayoutSlip::on_removeAction_triggered()
{
 if (layoutEditor->removeLayoutSlip(this))
 {
    // Returned true if user did not cancel
    remove();
    dispose();
 }
}

/*public*/ QVector<QString>* LayoutSlip::getBlockBoundaries()
{
 /*final*/ QVector<QString>* boundaryBetween = new QVector<QString>(4);

 if ( (blockName!=nullptr) && (blockName!=("")) && (block!=nullptr) )
 {
  //if ((connectA instanceof TrackSegment) &&
  if((qobject_cast<TrackSegment*>(connectA)!=nullptr) &&
  (((TrackSegment*)connectA)->getLayoutBlock()!=block))
  {
   try
   {
    boundaryBetween->replace(0,((TrackSegment*)connectA)->getLayoutBlock()->getDisplayName()+ " - " + block->getDisplayName());
   }
   catch (NullPointerException e)
   {
    //Can be considered normal if tracksegement hasn't yet been allocated a block
    log.debug("TrackSegement at connection A doesn't contain a layout block");
   }
  }
  //if ((connectC instanceof TrackSegment) &&
  if((qobject_cast<TrackSegment*>(connectC)!= nullptr) &&
          (((TrackSegment*)connectC)->getLayoutBlock()!=block))
  {
   try
   {
    boundaryBetween->replace(2,((TrackSegment*)connectC)->getLayoutBlock()->getDisplayName()+ " - " + block->getDisplayName());
   }
   catch (NullPointerException e)
   {
    //Can be considered normal if tracksegement hasn't yet been allocated a block
    log.debug("TrackSegement at connection C doesn't contain a layout block");
   }
  }
  //if ((connectB instanceof TrackSegment) &&
  if((qobject_cast<TrackSegment*>(connectB)!= NULL) &&
          (((TrackSegment*)connectB)->getLayoutBlock()!=block))
  {
   try
   {
     boundaryBetween->replace(1,((TrackSegment*)connectB)->getLayoutBlock()->getDisplayName()+ " - " + block->getDisplayName());
   }
   catch (NullPointerException e)
   {
    //Can be considered normal if tracksegement hasn't yet been allocated a block
    log.debug("TrackSegement at connection B doesn't contain a layout block");
   }
  }
  //if ((connectD instanceof TrackSegment) &&
  if((qobject_cast<TrackSegment*>(connectD)!= NULL) &&

          (((TrackSegment*)connectD)->getLayoutBlock()!=block))
  {
   try
   {
    boundaryBetween->replace(3,((TrackSegment*)connectD)->getLayoutBlock()->getDisplayName()+ " - " + block->getDisplayName());
   }
   catch (NullPointerException e)
   {
    //Can be considered normal if tracksegement hasn't yet been allocated a block
    log.debug("TrackSegement at connection D doesn't contain a layout block");
   }
  }
 }
 return boundaryBetween;
}
#if 1 // TODO:

/**
 * Edit a Slip
 */
/*protected*/ void LayoutSlip::editLayoutSlip(LayoutTurnout* o)
{
 if (editOpen)
 {
  editLayoutTurnoutFrame->setVisible(true);
  return;
 }
 // Initialize if needed
 if (editLayoutTurnoutFrame == NULL)
 {
  editLayoutTurnoutFrame = new JmriJFrame( tr("Edit Slip"), false, true );
  editLayoutTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutSlip", true);
  editLayoutTurnoutFrame->setLocation(50,30);
//  QWidget* contentPane = editLayoutTurnoutFrame->getContentPane();
//  contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
  QWidget* centralWidget = new QWidget();
  QBoxLayout* editLayoutTurnoutFrameLayout = new QVBoxLayout(centralWidget);
  editLayoutTurnoutFrame->setCentralWidget(centralWidget);
  QWidget* panel1 = new QWidget();
  //panel1.setLayout(new FlowLayout());
  FlowLayout* panel1Layout = new FlowLayout(panel1);
  QLabel* turnoutNameLabel = new QLabel( tr("Turnout")+" A "+tr("Name") );
  turnoutAComboBox = new JmriBeanComboBox(InstanceManager::turnoutManagerInstance(), getTurnout(), JmriBeanComboBox::DISPLAYNAME);
  panel1Layout->addWidget(turnoutNameLabel);
  panel1Layout->addWidget(turnoutAComboBox);
  editLayoutTurnoutFrameLayout->addWidget(panel1);
  QWidget* panel1a = new QWidget();
  //panel1a.setLayout(new FlowLayout());
  FlowLayout* panel1aLayout = new FlowLayout(panel1a);
  QLabel* turnoutBNameLabel = new QLabel( tr("Turnout")+" B "+tr("Name") );
  turnoutBComboBox = new JmriBeanComboBox(InstanceManager::turnoutManagerInstance(), getTurnoutB(), JmriBeanComboBox::DISPLAYNAME);
  panel1aLayout->addWidget(turnoutBNameLabel);
  panel1aLayout->addWidget(turnoutBComboBox);
  editLayoutTurnoutFrameLayout->addWidget(panel1a);
  QWidget* panel2 = new QWidget();
  //panel2.setLayout(new GridLayout(0,3, 2, 2));
  QGridLayout* panel2Layout = new QGridLayout(panel2);

  panel2Layout->addWidget(new QLabel("   "),0,0);
  panel2Layout->addWidget(new QLabel(tr("Turnout")+" A:"),0,1);
  panel2Layout->addWidget(new QLabel(tr("Turnout")+" B:"),0,2);

  //for(Entry <Integer, TurnoutState> ts: turnoutStates.entrySet()){
  QHashIterator<int, TurnoutState*> iter(turnoutStates);
  int row = 1;
  while(iter.hasNext())
  {
   iter.next();
   TurnoutState* ts = iter.value();
   SampleStates* draw = new SampleStates(iter.key(), this);
   //draw.repaint();
   draw->resize(QSize(40,40));
   draw->setMinimumSize( QSize(40,40));
   panel2Layout->addWidget(draw, row, 0);

   panel2Layout->addWidget(ts->getComboA(), row, 1);
   panel2Layout->addWidget(ts->getComboB(), row, 2);
   row ++;
  }

  testPanel = new TestState(this);
  testPanel->resize(40,40);
  testPanel->setMinimumSize( QSize(40,40));
  panel2Layout->addWidget(testPanel);
  QPushButton* testButton = new QPushButton("Test");
//  testButton.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          toggleStateTest();
//      }
//  });
  connect(testButton, SIGNAL(clicked()), this, SLOT(toggleStateTest()));
  panel2Layout->addWidget(testButton);
  editLayoutTurnoutFrameLayout->addWidget(panel2);
  // setup block name
  QWidget* panel3 = new QWidget();
  //panel3.setLayout(new FlowLayout());
  FlowLayout* panel3Layout = new FlowLayout(panel3);
  QLabel* block1NameLabel = new QLabel( tr("Block ID") );
  panel3Layout->addWidget(block1NameLabel);
  panel3Layout->addWidget(blockNameField);
  blockNameField->setToolTip( tr("Edit block name to change the linked block. If new name, block will be created.") );
  editLayoutTurnoutFrameLayout->addWidget(panel3);
  // set up Edit Block buttons
  QWidget* panel4 = new QWidget();
  //panel4.setLayout(new FlowLayout());
  FlowLayout* panel4Layout = new FlowLayout(panel4);
  // Edit Block
  panel4Layout->addWidget(turnoutEditBlock = new QPushButton(tr("Edit Block")));
//  turnoutEditBlock.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          turnoutEditBlockPressed(e);
//      }
//  });
  connect(turnoutEditBlock, SIGNAL(clicked()), this, SLOT(turnoutEditBlockPressed()));
  turnoutEditBlock->setToolTip( tr("Click here to create/edit information for the Block shown above.") );

  editLayoutTurnoutFrameLayout->addWidget(panel4);
  // set up Done and Cancel buttons
  QWidget* panel5 = new QWidget();
  //panel5.setLayout(new FlowLayout());
  FlowLayout* panel5Layout = new FlowLayout(panel5);
  panel5Layout->addWidget(slipEditDone = new QPushButton(tr("Done")));
//  slipEditDone.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          slipEditDonePressed(e);
//      }
//  });
  connect(slipEditDone, SIGNAL(clicked()), this, SLOT(slipEditDonePressed()));
  slipEditDone->setToolTip( tr("Click Done to accept any changes made above and dismiss this dialog.") );
  // Cancel
  panel5Layout->addWidget(slipEditCancel = new QPushButton(tr("Cancel")));
//  slipEditCancel.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          slipEditCancelPressed(e);
//      }
//  });
  connect(slipEditCancel, SIGNAL(clicked()), this, SLOT(slipEditCancelPressed()));
  slipEditCancel->setToolTip( tr("Click Cancel to dismiss this dialog without making changes.") );
  editLayoutTurnoutFrameLayout->addWidget(panel5);
 }
 // Set up for Edit
 blockNameField->setText(blockName);

// editLayoutTurnoutFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             slipEditCancelPressed(NULL);
//         }
//     });

 editLayoutTurnoutFrame->pack();
 editLayoutTurnoutFrame->setVisible(true);
 editOpen = true;
 needsBlockUpdate = false;
}
#endif

void LayoutSlip::drawSlipState(int state, QPainter* painter)
{
 int ctrX = 20;
 int ctrY = 20;
 QPointF ldispA = QPointF(-20.0,0.0);
 QPointF ldispB = QPointF(-14.0,14.0);
 //g2.setColor(Color.black);
painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin));

 QPointF A = QPointF(ctrX+ldispA.x(), ctrY+ldispA.y());
 QPointF B = QPointF(ctrX+ldispB.x(), ctrY+ldispB.y());
 QPointF C = QPointF(ctrX-ldispA.x(), ctrY-ldispA.y());
 QPointF D = QPointF(ctrX-ldispB.x(), ctrY-ldispB.y());

 //g2.setStroke(new BasicStroke(2,BasicStroke.CAP_BUTT,                                      BasicStroke.JOIN_ROUND));

//    painter->drawLine((A,
//        layoutEditor.third(A,C)));
 painter->drawLine(A,layoutEditor->third(A,C));
 painter->drawLine(C,layoutEditor->third(C,A));

 if(state==STATE_AC || state==STATE_BD || state==UNKNOWN)
 {
  painter->drawLine(A, layoutEditor->third(A,D));

  painter->drawLine(D, layoutEditor->third(D,A));

  if(getSlipType()==LayoutSlip::DOUBLE_SLIP)
  {
   painter->drawLine(B, layoutEditor->third(B,C));

   painter->drawLine(C, layoutEditor->third(C,B));
  }
 }
 else
 {
  painter->drawLine(B, layoutEditor->third(B,D));
  painter->drawLine(D, layoutEditor->third(D,B));
 }

 if(getSlipType()==LayoutSlip::DOUBLE_SLIP)
 {
  if (state==LayoutSlip::STATE_AC)
  {
   painter->drawLine(B, layoutEditor->third(B,D));
   painter->drawLine(D, layoutEditor->third(D,B));

   painter->setPen(Qt::red);
   painter->drawLine(A,C);
  }
  else if (state==LayoutSlip::STATE_BD)
  {
   painter->setPen(Qt::red);
   painter->drawLine(B,D);
  }
  else if (state==LayoutSlip::STATE_AD)
  {
   painter->drawLine(B, layoutEditor->third(B,C));

   painter->drawLine(C,
       layoutEditor->third(C,B));

   painter->setPen(Qt::red);
   painter->drawLine(A,D);
  }
  else if (state==LayoutSlip::STATE_BC)
  {
   painter->drawLine(A,
   layoutEditor->third(A,D));

   painter->drawLine(D,
       layoutEditor->third(D,A));
   painter->setPen(Qt::red);
   painter->drawLine(B,C);
  }
  else
  {
   painter->drawLine(B,
       layoutEditor->third(B,D));
   painter->drawLine(D,
       layoutEditor->third(D,B));
  }
 } else
 {
  painter->drawLine(A,
      layoutEditor->third(A,D));

  painter->drawLine(D,
      layoutEditor->third(D,A));
  if (state==LayoutSlip::STATE_AD)
  {
   painter->setPen(Qt::red);
   painter->drawLine(A,D);
  }
  else if (state==LayoutSlip::STATE_AC)
  {
   painter->drawLine(B,
       layoutEditor->third(B,D));
   painter->drawLine(D,
       layoutEditor->third(D,B));

   painter->setPen(Qt::red);
   painter->drawLine(A,C);
  }
  else if (state==LayoutSlip::STATE_BD)
  {
   painter->setPen(Qt::red);
   painter->drawLine(B,D);
  }
  else
  {
   painter->drawLine(B,
       layoutEditor->third(B,D));
   painter->drawLine(D,
       layoutEditor->third(D,B));
  }
 }
}

/*public*/ void LayoutSlip::drawSlipCircles(EditScene* g2) {
    double circleRadius = controlPointSize * layoutEditor->getTurnoutCircleSize();
    QPointF leftCenter = MathUtil::midPoint(getCoordsA(), getCoordsB());
    double leftFract = circleRadius / MathUtil::distance(center,leftCenter);
    QPointF leftCircleCenter = MathUtil::lerp(center, leftCenter, leftFract);
    g2->addItem(layoutEditor->turnoutCircleAt(leftCircleCenter));

    QPointF rightCenter =MathUtil:: midPoint(getCoordsC(), getCoordsD());
    double rightFract = circleRadius / MathUtil::distance(center, rightCenter);
    QPointF rightCircleCenter = MathUtil::lerp(center, rightCenter, rightFract);
    g2->addItem(layoutEditor->turnoutCircleAt(rightCircleCenter));
}

//class SampleStates extends QWidget {
// Methods, constructors, fields.
SampleStates::SampleStates(int state, LayoutSlip* parent)
{
 //super();
 this->parent = parent;
 this->state = state;
}
//    int state;
//    @Override
/*public*/ void SampleStates::paintEvent(QPaintEvent* event)
{
//        super.paintComponent(g);    // paints background
//        Graphics2D g2 = (Graphics2D) g;
 QPainter* painter = new QPainter(this);
 parent->drawSlipState(state, painter);
}
//};
/**
 * Toggle slip states if clicked on, physical turnout exists, and
 *    not disabled
 */
/*public*/ void LayoutSlip::toggleStateTest()
{
 int turnAState;
 int turnBState;
 switch(testState)
 {
  case STATE_AC :
   turnAState = turnoutStates.value(STATE_BD)->getTestTurnoutAState();
   turnBState = turnoutStates.value(STATE_BD)->getTestTurnoutBState();
   testState = STATE_BD;
   break;
  case STATE_BD :
   turnAState = turnoutStates.value(STATE_AD)->getTestTurnoutAState();
   turnBState = turnoutStates.value(STATE_AD)->getTestTurnoutBState();
   testState = STATE_AD;
   break;
  case STATE_AD : if(type==SINGLE_SLIP)
  {
   turnAState = turnoutStates.value(STATE_AC)->getTestTurnoutAState();
   turnBState = turnoutStates.value(STATE_AC)->getTestTurnoutBState();
   testState = STATE_AC;
  }
  else
  {
   turnAState = turnoutStates.value(STATE_BC)->getTestTurnoutAState();
   turnBState = turnoutStates.value(STATE_BC)->getTestTurnoutBState();
   testState = STATE_BC;
  }
  break;
 case STATE_BC :
  turnAState = turnoutStates.value(STATE_AC)->getTestTurnoutAState();
  turnBState = turnoutStates.value(STATE_AC)->getTestTurnoutBState();
  testState = STATE_AC;
  break;
 default       :
  turnAState = turnoutStates.value(STATE_BD)->getTestTurnoutAState();
  turnBState = turnoutStates.value(STATE_BD)->getTestTurnoutBState();
  testState = STATE_BD;
   break;
 }
 ((Turnout*)turnoutAComboBox->getSelectedBean())->setCommandedState(turnAState);
 ((Turnout*)turnoutBComboBox->getSelectedBean())->setCommandedState(turnBState);
 /*if(getTurnout()!=NULL)
     getTurnout().setCommandedState(turnAState);
 if(getTurnoutB()!=NULL)
     getTurnoutB().setCommandedState(turnBState);*/
 if(testPanel!=NULL)
     testPanel->repaint();
}

//class TestState extends QWidget {
TestState::TestState(LayoutSlip* parent)
{
 this->parent = parent;
}
/*public*/ void TestState::paintEvent(QPaintEvent* event)
{
//        super.paintComponent(g);
//        Graphics2D g2 = (Graphics2D) g;
 QPainter* painter = new QPainter(this);
 parent->drawSlipState(parent->testState, painter);
}
//};


void LayoutSlip::slipEditDonePressed(ActionEvent* a)
{
 if ( turnoutName!=(turnoutAComboBox->getSelectedDisplayName()) )
 {
  QString newName = turnoutAComboBox->getSelectedDisplayName();
  if ( layoutEditor->validatePhysicalTurnout(newName,
                  editLayoutTurnoutFrame) )
  {
   setTurnout(newName);
  }
  else
  {
   namedTurnout = NULL;
   turnoutName = "";
  }
  needRedraw = true;
 }
 if ( turnoutBName!=(turnoutBComboBox->getSelectedDisplayName()) )
 {
  QString newName = turnoutBComboBox->getSelectedDisplayName();
  if ( layoutEditor->validatePhysicalTurnout(newName,
                  editLayoutTurnoutFrame) )
  {
   setTurnoutB(newName);
  }
  else
  {
   namedTurnoutB = NULL;
   turnoutBName = "";
  }
  needRedraw = true;
 }
 if ( blockName!=(blockNameField->text().trimmed()) )
 {
  // block 1 has changed, if old block exists, decrement use
  if ( (block!=NULL))
  {
   block->decrementUse();
  }
  // get new block, or NULL if block has been removed
  blockName = blockNameField->text().trimmed();
  //if ( (blockName!=NULL) && (blockName.length()>0)) {
  block = layoutEditor->provideLayoutBlock(blockName);

  if(block==NULL)
  {
   blockName = "";
   blockNameField->setText("");
  }
  //}
  //else {
  //	block = NULL;
  //	blockName = "";
  //}
  needRedraw = true;
  layoutEditor->auxTools->setBlockConnectivityChanged();
  needsBlockUpdate = true;
 }
 foreach(TurnoutState* ts, turnoutStates.values())
 {
  ts->updateStatesFromCombo();
 }
 editOpen = false;
 editLayoutTurnoutFrame->setVisible(false);
 editLayoutTurnoutFrame->dispose();
 editLayoutTurnoutFrame = NULL;
 if (needsBlockUpdate) updateBlockInfo();
 if (needRedraw)
 {
  layoutEditor->redrawPanel();
  layoutEditor->setDirty();
 }
}

void LayoutSlip::slipEditCancelPressed(ActionEvent* a)
{
 editOpen = false;
 editLayoutTurnoutFrame->setVisible(false);
 editLayoutTurnoutFrame->dispose();
 editLayoutTurnoutFrame = NULL;
 if (needsBlockUpdate) updateBlockInfo();
 if (needRedraw)
 {
  layoutEditor->redrawPanel();
  layoutEditor->setDirty();
 }
}
/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void LayoutSlip::dispose() {
    if (popup != NULL) popup->clear();
    popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void LayoutSlip::remove()
{
 disableSML(getSignalAMastName());
 disableSML(getSignalBMastName());
 disableSML(getSignalCMastName());
 disableSML(getSignalDMastName());
 removeSML(getSignalAMastName());
 removeSML(getSignalBMastName());
 removeSML(getSignalCMastName());
 removeSML(getSignalDMastName());
 // remove from persistance by flagging inactive
 active = false;
}

void LayoutSlip::disableSML(QString signalMast)
{
 if(signalMast==NULL || signalMast==(""))
  return;
 SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
 InstanceManager::signalMastLogicManagerInstance()->disableLayoutEditorUse(mast);
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LayoutSlip::isActive() {
    return active;
}

/*public*/ bool LayoutSlip::singleSlipStraightEqual()
{
 if(type!=SINGLE_SLIP)
     return false;
 return turnoutStates.value(STATE_AC)==(turnoutStates.value(STATE_BD));
}

/*protected*/ QHash<int, TurnoutState*> LayoutSlip::getTurnoutStates() {
    return turnoutStates;
}
/*public*/ int LayoutSlip::getTurnoutState(Turnout* turn, int state){
 if(turn==getTurnout())
 {
  return getTurnoutState(state);
 }
 return getTurnoutBState(state);
}

/*public*/ int LayoutSlip::getTurnoutState(int state){
    return turnoutStates.value((state))->getTurnoutAState();
}

/*public*/ int LayoutSlip::getTurnoutBState(int state)
{
 return turnoutStates.value((state))->getTurnoutBState();
}

/*public*/ void LayoutSlip::setTurnoutStates(int state, QString turnStateA, QString turnStateB)
{
 if(!turnoutStates.contains(state))
 {
  log.error("Trying to set invalid state for slip " + getDisplayName());
  return;
 }
 turnoutStates.value(state)->setTurnoutAState((turnStateA).toInt());
 turnoutStates.value(state)->setTurnoutBState((turnStateB).toInt());
}

//Internal call to update the state of the slip depending upon the turnout states.
void LayoutSlip::updateState()
{
 int state_a = getTurnout()->getKnownState();
 int state_b = getTurnoutB()->getKnownState();
 //for(Entry<Integer, TurnoutState*> en: turnoutStates.entrySet()){
 QHashIterator<int, TurnoutState*> en(turnoutStates);
 while(en.hasNext())
 {
  en.next();
  if(en.value()->getTurnoutAState()==state_a)
  {
   if(en.value()->getTurnoutBState()==state_b)
   {
    currentState=en.key();
    layoutEditor->redrawPanel();
    return;
   }
  }
 }
}
#if 0
/**
    * Check if either turnout is inconsistent.
    * This is used to create an alternate slip image.
    *
    * @return true if either turnout is inconsistent.
    */
   private boolean isTurnoutInconsistent() {
       Turnout tA = getTurnout();
       if (tA != null && tA.getKnownState() == INCONSISTENT) {
           return true;
       }
       Turnout tB = getTurnoutB();
       if (tB != null && tB.getKnownState() == INCONSISTENT) {
           return true;
       }
       return false;
   }

   @Override
   protected void draw1(Graphics2D g2, boolean drawMain, boolean isBlock) {
       if (isBlock && getLayoutBlock() == null) {
           // Skip the block layer since there is no block assigned.
           return;
       }

       QPointF pA = getCoordsA();
       QPointF pB = getCoordsB();
       QPointF pC = getCoordsC();
       QPointF pD = getCoordsD();

       boolean mainlineA = isMainlineA();
       boolean mainlineB = isMainlineB();
       boolean mainlineC = isMainlineC();
       boolean mainlineD = isMainlineD();

       boolean drawUnselectedLeg = layoutEditor.isTurnoutDrawUnselectedLeg();

       Color color = g2.getColor();

       // if this isn't a block line all these will be the same color
       Color colorA = color;
       Color colorB = color;
       Color colorC = color;
       Color colorD = color;

       if (isBlock) {
           LayoutBlock lb = getLayoutBlock();
           colorA = (lb == null) ? color : lb.getBlockColor();
           lb = getLayoutBlockB();
           colorB = (lb == null) ? color : lb.getBlockColor();
           lb = getLayoutBlockC();
           colorC = (lb == null) ? color : lb.getBlockColor();
           lb = getLayoutBlockD();
           colorD = (lb == null) ? color : lb.getBlockColor();
       }

       QPointF oneForthPointAC = MathUtil.oneFourthPoint(pA, pC);
       QPointF oneThirdPointAC = MathUtil.oneThirdPoint(pA, pC);
       QPointF midPointAC = MathUtil.midPoint(pA, pC);
       QPointF twoThirdsPointAC = MathUtil.twoThirdsPoint(pA, pC);
       QPointF threeFourthsPointAC = MathUtil.threeFourthsPoint(pA, pC);

       QPointF oneForthPointBD = MathUtil.oneFourthPoint(pB, pD);
       QPointF oneThirdPointBD = MathUtil.oneThirdPoint(pB, pD);
       QPointF midPointBD = MathUtil.midPoint(pB, pD);
       QPointF twoThirdsPointBD = MathUtil.twoThirdsPoint(pB, pD);
       QPointF threeFourthsPointBD = MathUtil.threeFourthsPoint(pB, pD);

       QPointF midPointAD = MathUtil.midPoint(oneThirdPointAC, twoThirdsPointBD);
       QPointF midPointBC = MathUtil.midPoint(oneThirdPointBD, twoThirdsPointAC);

       if (isTurnoutInconsistent()) {
           // If either turnout is inconsistent, draw an alternate slip image
           // draw A<= =>C
           if (drawMain == mainlineA) {
               g2.setColor(colorA);
               g2.draw(new Line2D.Double(pA, oneForthPointAC));
           }
           if (drawMain == mainlineC) {
               g2.setColor(colorC);
               g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
           }
           // draw B<= =>D
           if (drawMain == mainlineB) {
               g2.setColor(colorB);
               g2.draw(new Line2D.Double(pB, oneForthPointBD));
           }
           if (drawMain == mainlineD) {
               g2.setColor(colorD);
               g2.draw(new Line2D.Double(threeFourthsPointBD, pD));
           }
           return;
       }

       int slipState = getSlipState();

       if (slipState == STATE_AD) {
           // draw A<===>D
           if (drawMain == mainlineA) {
               g2.setColor(colorA);
               g2.draw(new Line2D.Double(pA, oneThirdPointAC));
               g2.draw(new Line2D.Double(oneThirdPointAC, midPointAD));
           }
           if (drawMain == mainlineD) {
               g2.setColor(colorD);
               g2.draw(new Line2D.Double(midPointAD, twoThirdsPointBD));
               g2.draw(new Line2D.Double(twoThirdsPointBD, pD));
           }
       } else if (slipState == STATE_AC) {
           // draw A<===>C
           if (drawMain == mainlineA) {
               g2.setColor(colorA);
               g2.draw(new Line2D.Double(pA, midPointAC));
           }
           if (drawMain == mainlineC) {
               g2.setColor(colorC);
               g2.draw(new Line2D.Double(midPointAC, pC));
           }
       } else if (!isBlock || drawUnselectedLeg) {
           // draw A<= =>C
           if (drawMain == mainlineA) {
               g2.setColor(colorA);
               g2.draw(new Line2D.Double(pA, oneForthPointAC));
           }
           if (drawMain == mainlineC) {
               g2.setColor(colorC);
               g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
           }
       }

       if (slipState == STATE_BD) {
           // draw B<===>D
           if (drawMain == mainlineB) {
               g2.setColor(colorB);
               g2.draw(new Line2D.Double(pB, midPointBD));
           }
           if (drawMain == mainlineD) {
               g2.setColor(colorD);
               g2.draw(new Line2D.Double(midPointBD, pD));
           }
       } else if (!isBlock || drawUnselectedLeg) {
           // draw B<= =>D
           if (drawMain == mainlineB) {
               g2.setColor(colorB);
               g2.draw(new Line2D.Double(pB, oneForthPointBD));
           }
           if (drawMain == mainlineD) {
               g2.setColor(colorD);
               g2.draw(new Line2D.Double(threeFourthsPointBD, pD));
           }
       }

       if (slipState == STATE_BC) {
           if (getTurnoutType() == DOUBLE_SLIP) {
               // draw B<===>C
               if (drawMain == mainlineB) {
                   g2.setColor(colorB);
                   g2.draw(new Line2D.Double(pB, oneThirdPointBD));
                   g2.draw(new Line2D.Double(oneThirdPointBD, midPointBC));
               }
               if (drawMain == mainlineC) {
                   g2.setColor(colorC);
                   g2.draw(new Line2D.Double(midPointBC, twoThirdsPointAC));
                   g2.draw(new Line2D.Double(twoThirdsPointAC, pC));
               }
           }   // DOUBLE_SLIP
       } else if (!isBlock || drawUnselectedLeg) {
           // draw B<= =>C
           if (drawMain == mainlineB) {
               g2.setColor(colorB);
               g2.draw(new Line2D.Double(pB, oneForthPointBD));
           }
           if (drawMain == mainlineC) {
               g2.setColor(colorC);
               g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
           }
       }
   }   // draw1

   /**
    * {@inheritDoc}
    */
   @Override
   protected void draw2(Graphics2D g2, boolean drawMain, float railDisplacement) {
       QPointF pA = getCoordsA();
       QPointF pB = getCoordsB();
       QPointF pC = getCoordsC();
       QPointF pD = getCoordsD();
       QPointF pM = getCoordsCenter();

       QPointF vAC = MathUtil.normalize(MathUtil.subtract(pC, pA), railDisplacement);
       double dirAC_DEG = MathUtil.computeAngleDEG(pA, pC);
       QPointF vACo = MathUtil.orthogonal(vAC);
       QPointF pAL = MathUtil.subtract(pA, vACo);
       QPointF pAR = MathUtil.add(pA, vACo);
       QPointF pCL = MathUtil.subtract(pC, vACo);
       QPointF pCR = MathUtil.add(pC, vACo);

       QPointF vBD = MathUtil.normalize(MathUtil.subtract(pD, pB), railDisplacement);
       double dirBD_DEG = MathUtil.computeAngleDEG(pB, pD);
       QPointF vBDo = MathUtil.orthogonal(vBD);
       QPointF pBL = MathUtil.subtract(pB, vBDo);
       QPointF pBR = MathUtil.add(pB, vBDo);
       QPointF pDL = MathUtil.subtract(pD, vBDo);
       QPointF pDR = MathUtil.add(pD, vBDo);

       double deltaDEG = MathUtil.absDiffAngleDEG(dirAC_DEG, dirBD_DEG);
       double deltaRAD = Math.toRadians(deltaDEG);

       double hypotV = railDisplacement / Math.cos((PI - deltaRAD) / 2.0);
       double hypotK = railDisplacement / Math.cos(deltaRAD / 2.0);

       log.debug("dir AC: {}, BD: {}, diff: {}", dirAC_DEG, dirBD_DEG, deltaDEG);

       QPointF vDisK = MathUtil.normalize(MathUtil.subtract(vAC, vBD), hypotK);
       QPointF vDisV = MathUtil.normalize(MathUtil.orthogonal(vDisK), hypotV);
       QPointF pKL = MathUtil.subtract(pM, vDisK);
       QPointF pKR = MathUtil.add(pM, vDisK);
       QPointF pVL = MathUtil.add(pM, vDisV);
       QPointF pVR = MathUtil.subtract(pM, vDisV);

       // this is the vector (rail gaps) for the diamond parts
       double railGap = 2.0 / Math.sin(deltaRAD);
       QPointF vAC2 = MathUtil.normalize(vAC, railGap);
       QPointF vBD2 = MathUtil.normalize(vBD, railGap);
       // KR and VR toward A, KL and VL toward C
       QPointF pKRtA = MathUtil.subtract(pKR, vAC2);
       QPointF pVRtA = MathUtil.subtract(pVR, vAC2);
       QPointF pKLtC = MathUtil.add(pKL, vAC2);
       QPointF pVLtC = MathUtil.add(pVL, vAC2);

       // VR and KL toward B, KR and VL toward D
       QPointF pVRtB = MathUtil.subtract(pVR, vBD2);
       QPointF pKLtB = MathUtil.subtract(pKL, vBD2);
       QPointF pKRtD = MathUtil.add(pKR, vBD2);
       QPointF pVLtD = MathUtil.add(pVL, vBD2);

       // outer (closed) switch points
       QPointF pAPL = MathUtil.add(pAL, MathUtil.subtract(pVL, pAR));
       QPointF pBPR = MathUtil.add(pBR, MathUtil.subtract(pVL, pBL));
       QPointF pCPR = MathUtil.add(pCR, MathUtil.subtract(pVR, pCL));
       QPointF pDPL = MathUtil.add(pDL, MathUtil.subtract(pVR, pDR));

       // this is the vector (rail gaps) for the inner (open) switch points
       QPointF vACo2 = MathUtil.normalize(vACo, 2.0);
       QPointF vBDo2 = MathUtil.normalize(vBDo, 2.0);
       QPointF pASL = MathUtil.add(pAPL, vACo2);
       QPointF pBSR = MathUtil.subtract(pBPR, vBDo2);
       QPointF pCSR = MathUtil.subtract(pCPR, vACo2);
       QPointF pDSL = MathUtil.add(pDPL, vBDo2);

       QPointF pVLP = MathUtil.add(pVLtD, vAC2);
       QPointF pVRP = MathUtil.subtract(pVRtA, vBD2);

       QPointF pKLH = MathUtil.midPoint(pM, pKL);
       QPointF pKRH = MathUtil.midPoint(pM, pKR);

       boolean mainlineA = isMainlineA();
       boolean mainlineB = isMainlineB();
       boolean mainlineC = isMainlineC();
       boolean mainlineD = isMainlineD();

       if (drawMain == mainlineA) {
           g2.draw(new Line2D.Double(pAR, pVL));
           g2.draw(new Line2D.Double(pVLtD, pKLtB));
           GeneralPath path = new GeneralPath();
           path.moveTo(pAL.getX(), pAL.getY());
           path.lineTo(pAPL.getX(), pAPL.getY());
           path.quadTo(pKL.getX(), pKL.getY(), pDPL.getX(), pDPL.getY());
           g2.draw(path);
       }
       if (drawMain == mainlineB) {
           g2.draw(new Line2D.Double(pBL, pVL));
           g2.draw(new Line2D.Double(pVLtC, pKRtA));
           if (getTurnoutType() == DOUBLE_SLIP) {
               GeneralPath path = new GeneralPath();
               path.moveTo(pBR.getX(), pBR.getY());
               path.lineTo(pBPR.getX(), pBPR.getY());
               path.quadTo(pKR.getX(), pKR.getY(), pCPR.getX(), pCPR.getY());
               g2.draw(path);
           } else {
               g2.draw(new Line2D.Double(pBR, pKR));
           }
       }
       if (drawMain == mainlineC) {
           g2.draw(new Line2D.Double(pCL, pVR));
           g2.draw(new Line2D.Double(pVRtB, pKRtD));
           if (getTurnoutType() == DOUBLE_SLIP) {
               GeneralPath path = new GeneralPath();
               path.moveTo(pCR.getX(), pCR.getY());
               path.lineTo(pCPR.getX(), pCPR.getY());
               path.quadTo(pKR.getX(), pKR.getY(), pBPR.getX(), pBPR.getY());
               g2.draw(path);
           } else {
               g2.draw(new Line2D.Double(pCR, pKR));
           }
       }
       if (drawMain == mainlineD) {
           g2.draw(new Line2D.Double(pDR, pVR));
           g2.draw(new Line2D.Double(pVRtA, pKLtC));
           GeneralPath path = new GeneralPath();
           path.moveTo(pDL.getX(), pDL.getY());
           path.lineTo(pDPL.getX(), pDPL.getY());
           path.quadTo(pKL.getX(), pKL.getY(), pAPL.getX(), pAPL.getY());
           g2.draw(path);
       }

       int slipState = getSlipState();
       if (slipState == STATE_AD) {
           if (drawMain == mainlineA) {
               g2.draw(new Line2D.Double(pASL, pKL));
               g2.draw(new Line2D.Double(pVLP, pKLH));
           }
           if (drawMain == mainlineB) {
               g2.draw(new Line2D.Double(pBPR, pKR));
               g2.draw(new Line2D.Double(pVLtC, pKRH));
           }
           if (drawMain == mainlineC) {
               g2.draw(new Line2D.Double(pCPR, pKR));
               g2.draw(new Line2D.Double(pVRtB, pKRH));
           }
           if (drawMain == mainlineD) {
               g2.draw(new Line2D.Double(pDSL, pKL));
               g2.draw(new Line2D.Double(pVRP, pKLH));
           }
       } else if (slipState == STATE_AC) {
           if (drawMain == mainlineA) {
               g2.draw(new Line2D.Double(pAPL, pKL));
               g2.draw(new Line2D.Double(pVLtD, pKLH));
           }
           if (drawMain == mainlineB) {
               g2.draw(new Line2D.Double(pBSR, pKR));
               g2.draw(new Line2D.Double(pVLP, pKRH));
           }
           if (drawMain == mainlineC) {
               g2.draw(new Line2D.Double(pCPR, pKR));
               g2.draw(new Line2D.Double(pVRtB, pKRH));
           }
           if (drawMain == mainlineD) {
               g2.draw(new Line2D.Double(pDSL, pKL));
               g2.draw(new Line2D.Double(pVRP, pKLH));
           }
       } else if (slipState == STATE_BD) {
           if (drawMain == mainlineA) {
               g2.draw(new Line2D.Double(pASL, pKL));
               g2.draw(new Line2D.Double(pVLP, pKLH));
           }
           if (drawMain == mainlineB) {
               g2.draw(new Line2D.Double(pBPR, pKR));
               g2.draw(new Line2D.Double(pVLtC, pKRH));
           }
           if (drawMain == mainlineC) {
               g2.draw(new Line2D.Double(pCSR, pKR));
               g2.draw(new Line2D.Double(pVRP, pKRH));
           }
           if (drawMain == mainlineD) {
               g2.draw(new Line2D.Double(pDPL, pKL));
               g2.draw(new Line2D.Double(pVRtA, pKLH));
           }
       } else if ((getTurnoutType() == DOUBLE_SLIP)
               && (slipState == STATE_BC)) {
           if (drawMain == mainlineA) {
               g2.draw(new Line2D.Double(pAPL, pKL));
               g2.draw(new Line2D.Double(pVLtD, pKLH));
           }
           if (drawMain == mainlineB) {
               g2.draw(new Line2D.Double(pBSR, pKR));
               g2.draw(new Line2D.Double(pVLP, pKRH));
           }
           if (drawMain == mainlineC) {
               g2.draw(new Line2D.Double(pCSR, pKR));
               g2.draw(new Line2D.Double(pVRP, pKRH));
           }
           if (drawMain == mainlineD) {
               g2.draw(new Line2D.Double(pDPL, pKL));
               g2.draw(new Line2D.Double(pVRtA, pKLH));
           }
       }   // DOUBLE_SLIP
   }   // draw2

   /**
    * {@inheritDoc}
    */
   @Override
   protected void highlightUnconnected(Graphics2D g2, int specificType) {
       if (((specificType == NONE) || (specificType == SLIP_A))
               && (getConnectA() == null)) {
           g2.fill(layoutEditor.trackControlCircleAt(getCoordsA()));
       }

       if (((specificType == NONE) || (specificType == SLIP_B))
               && (getConnectB() == null)) {
           g2.fill(layoutEditor.trackControlCircleAt(getCoordsB()));
       }

       if (((specificType == NONE) || (specificType == SLIP_C))
               && (getConnectC() == null)) {
           g2.fill(layoutEditor.trackControlCircleAt(getCoordsC()));
       }

       if (((specificType == NONE) || (specificType == SLIP_D))
               && (getConnectD() == null)) {
           g2.fill(layoutEditor.trackControlCircleAt(getCoordsD()));
       }
   }
#endif
   //@Override
   /*protected*/ void LayoutSlip::drawTurnoutControls(EditScene* g2, QPen stroke) {
       // drawHidden left/right turnout control circles
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
       QPointF leftCircleCenter = getCoordsLeft();

       //g2.draw(layoutEditor->trackControlCircleAt(leftCircleCenter));
       QGraphicsEllipseItem* item = layoutEditor->trackControlCircleAt(leftCircleCenter);
       item->setPen(stroke);
       itemGroup->addToGroup(item);

       QPointF rightCircleCenter = getCoordsRight();
       //g2.draw(layoutEditor->trackControlCircleAt(rightCircleCenter));
       item = layoutEditor->trackControlCircleAt(rightCircleCenter);
       item->setPen(stroke);
       itemGroup->addToGroup(item);
       g2->addItem(itemGroup);
   }   // drawTurnoutControls


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutSlip::class.getName());

//}
