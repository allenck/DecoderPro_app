#include "layoutturnout.h"
#include "instancemanager.h"
#include <qmath.h>

LayoutTurnout::LayoutTurnout(QObject *parent) :
    QObject(parent)
{
}
/**
 * A LayoutTurnout corresponds to a turnout on the layout. A LayoutTurnout is an
 *      extension of the standard Turnout object with drawing and connectivity
 *      information added.
 * <P>
 *  Six types are supported:
 *		right-hand, left-hand, wye, double crossover, right-handed single crossover,
 *      and left-handed single crossover.  Note that double-slip
 *      turnouts can be handled as two turnouts, throat to throat, and three-way
 *		turnouts can be handles as two turnouts, left-hand and right-hand,
 *      arranged throat to continuing route.
 * <P>
 * A LayoutTurnout has three or four connection points, designated A, B, C, and D.
 *		For right-handed or left-handed turnouts, A corresponds to the throat.
 *		At the crossing, A-B (and C-D for crossovers) is a straight segment
 *		(continuing route).  A-C (and B-D for crossovers) is the diverging
 *		route.  B-C (and A-D for crossovers) is an illegal condition.
 * <P>
 * A LayoutTurnout carries Block information.  For right-handed, left-handed, and wye
 *      turnouts, the entire turnout is in one block,however, a block border may occur
 *      at any connection (A,B,C,D). For a double crossover turnout, up to four blocks
 *      may be assigned, one for each connection point, but if only one block is assigned,
 *      that block applies to the entire turnout.
 * <P>
 * For drawing purposes, each LayoutTurnout carries a center point and displacements
 *		for B and C. For right-handed or left-handed turnouts, the displacement for
 *		A = - the displacement for B, and the center point is at the junction of the
 *		diverging route and the straight through continuing route.  For double
 *		crossovers, the center point is at the center of the turnout, and the
 *		displacement for A = - the displacement for C and the displacement for D =
 *		- the displacement for B.  The center point and these displacements may be
 *		adjusted by the user when in edit mode.  For double crossovers, AB and BC
 *      are constrained to remain perpendicular.  For single crossovers, AB and CD
 *		are constrained to remain parallel, and AC and BD are constrained to remain
 *      parallel.
 * <P>
 * When LayoutTurnouts are first created, a rotation (degrees) is provided.
 *		For 0.0 rotation, the turnout lies on the east-west line with A facing
 *		east.  Rotations are performed in a clockwise direction.
 * <P>
 * When LayoutTurnouts are first created, there are no connections.  Block information
 *		and connections may be added when available.
 * <P>
 * When a LayoutTurnout is first created, it is enabled for control of an assigned
 *		actual turnout. Clicking on the turnout center point will toggle the turnout.
 *		This can be disabled via the popup menu.
 * <P>
 * Signal Head names are saved here to keep track of where signals are. LayoutTurnout
 *		only serves as a storage place for signal head names. The names are placed here
 *		by tools, e.g., Set Signals at Turnout, and Set Signals at Double Crossover.
 * <P>
 * A LayoutTurnout may be linked to another LayoutTurnout to form a turnout pair.
 *		Throat-To-Throat Turnouts - Two turnouts connected closely at their throats,
 *			so closely that signals are not appropriate at the their throats. This is the
 *			situation when two RH, LH, or WYE turnouts are used to model a double slip.
 *		3-Way Turnout - Two turnouts modeling a 3-way turnout, where the throat of the
 *			second turnout is closely connected to the continuing track of the first
 *			turnout.  The throat will have three heads, or one head.
 * A link is required to be able to correctly interpret the use of signal heads.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 22335 $
 */

///*public*/ class LayoutTurnout
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

/**
 * constructor method
 */
/*public*/ LayoutTurnout::LayoutTurnout(QString id, int t, QPointF* c, double rot,
                                double xFactor, double yFactor, LayoutEditor* myPanel)
{
 turnoutName = "";   // should be the name (system or user) of
                                    //	an existing physical turnout
 secondTurnoutName = "";   /* should be the name (system or user) of
                                    an existing physical turnout. Second turnout is
                                    used to allow the throwing of two different turnout
                                    to control one cross-over
                                    */
 blockName = "";  // name for block, if there is one
 blockBName = "";  // Xover - name for second block, if there is one
 blockCName = "";  // Xover - name for third block, if there is one
 blockDName = "";  // Xover - name for fourth block, if there is one

 signalA1Name = ""; // signal 1 (continuing) (throat for RH, LH, WYE)
 signalA2Name = ""; // signal 2 (diverging) (throat for RH, LH, WYE)
 signalA3Name = ""; // signal 3 (second diverging) (3-way turnouts only)
 signalB1Name = ""; // continuing (RH, LH, WYE) signal 1 (double crossover)
 signalB2Name = ""; // LH_Xover and double crossover only
 signalC1Name = ""; // diverging (RH, LH, WYE) signal 1 (double crossover)
 signalC2Name = ""; // RH_Xover and double crossover only
 signalD1Name = ""; // single or double crossover only
 signalD2Name = ""; // LH_Xover and double crossover only

 signalAMast = ""; // Throat
 signalBMast = ""; // Continuing
 signalCMast = ""; // diverging
 signalDMast = ""; // single or double crossover only
 sensorANamed = NULL; // Throat
 sensorBNamed = NULL; // Continuing
 sensorCNamed = NULL; // diverging
 sensorDNamed = NULL; // single or double crossover only
 type = RH_TURNOUT;
 connectA = NULL;		// throat of LH, RH, RH Xover, LH Xover, and WYE turnouts
 connectB = NULL;		// straight leg of LH and RH turnouts
 connectC = NULL;
 connectD = NULL;		// double xover, RH Xover, LH Xover only
 continuingSense = Turnout::CLOSED;
 disabled = false;
 disableWhenOccupied = false;
 center = new QPointF(50.0,50.0);
 dispB = new QPointF(20.0,0.0);
 dispC = new QPointF(20.0,10.0);
 linkedTurnoutName = ""; // name of the linked Turnout (as entered in tool)
 linkType = NO_LINK;
 popup = NULL;
// JCheckBoxMenuItem* disableItem = NULL;
// JCheckBoxMenuItem* disableWhenOccupiedItem = NULL;
 LayoutEditorTools* tools = NULL;
 turnoutNameField = new QLineEdit();
 turnoutNameField->setMaxLength(16);
 blockBNameField = new QLineEdit();
 blockBNameField->setMaxLength(16);
 blockCNameField = new QLineEdit();
 blockCNameField->setMaxLength(16);
 blockDNameField = new QLineEdit();
 blockDNameField->setMaxLength(16);
 stateBox = new QComboBox();
 editOpen = false;
 additionalTurnout = new QCheckBox(tr("SupportingTurnout"));
 editLayoutTurnoutFrame = NULL;
 blockNameField = new QLineEdit();
 blockNameField->setMaxLength(16);
 needRedraw = false;
 needsBlockUpdate = false;
 active = true;
 editAdditionalMenu = new QVector<QAction*>();
 viewAdditionalMenu = new QVector<QAction*>();


    instance = this;
    namedTurnout = NULL;
    turnoutName = "";
    mTurnoutListener = NULL;
    disabled = false;
    disableWhenOccupied = false;
    block = NULL;
    blockName = "";
    layoutEditor = myPanel;
    ident = id;
    type = t;
    center = c;
    // adjust initial coordinates
    if (type==LH_TURNOUT)
    {
     //dispB->setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB->setX(layoutEditor->getTurnoutBX());
     dispB->setY(0.0);
     //dispC->setLocation(layoutEditor->getTurnoutCX(),-layoutEditor->getTurnoutWid());
     dispC->setX(layoutEditor->getTurnoutCX());
     dispC->setY(-(layoutEditor->getTurnoutWid()));
    }
    else if (type==RH_TURNOUT)
    {
     //dispB->setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB->setX(layoutEditor->getTurnoutBX());
     dispB->setY(0.0);
     //dispC->setLocation(layoutEditor->getTurnoutCX(),layoutEditor->getTurnoutWid());
     dispC->setX(layoutEditor->getTurnoutCX());
     dispC->setY(layoutEditor->getTurnoutWid());
    }
    else if (type==WYE_TURNOUT)
    {
     //dispB->setLocation(layoutEditor->getTurnoutBX(),0.5*layoutEditor->getTurnoutWid());
     dispB->setX(layoutEditor->getTurnoutBX());
     dispB->setY(0.5*layoutEditor->getTurnoutWid());
     //dispC->setLocation(layoutEditor->getTurnoutBX(),-0.5*layoutEditor->getTurnoutWid());
     dispC->setX(layoutEditor->getTurnoutBX());
     dispC->setY(-0.5*layoutEditor->getTurnoutWid());

    }
    else if (type==DOUBLE_XOVER)
    {
     //dispB->setLocation(layoutEditor->getXOverLong(),-layoutEditor->getXOverHWid());
     dispB->setX(layoutEditor->getXOverLong());
     dispB->setY(-(layoutEditor->getXOverHWid()));

     //dispC->setLocation(layoutEditor->getXOverLong(),layoutEditor->getXOverHWid());
     dispC->setX(layoutEditor->getXOverLong());
     dispC->setY(layoutEditor->getXOverHWid());

        blockB = NULL;
        blockBName = "";
        blockC = NULL;
        blockCName = "";
        blockD = NULL;
        blockDName = "";
    }
    else if (type==RH_XOVER)
    {
     //dispB.setLocation(layoutEditor->xOverShort(),-layoutEditor->xOverHWid());
     dispB->setX(layoutEditor->getXOverShort());
     dispB->setY(-(layoutEditor->getXOverHWid()));
     //dispC.setLocation(layoutEditor->xOverLong(),layoutEditor->xOverHWid());
     dispC->setX(layoutEditor->getXOverLong());
     dispC->setY(layoutEditor->getXOverHWid());

        blockB = NULL;
        blockBName = "";
        blockC = NULL;
        blockCName = "";
        blockD = NULL;
        blockDName = "";
    }
    else if (type==LH_XOVER)
    {
     //dispB.setLocation(layoutEditor->xOverLong(),-layoutEditor->xOverHWid());
     dispB->setX(layoutEditor->getXOverLong());
     dispB->setY(-(layoutEditor->getXOverHWid()));
     //dispC.setLocation(layoutEditor->xOverShort(),layoutEditor->xOverHWid());
     dispC->setX(layoutEditor->getXOverShort());
     dispC->setY(layoutEditor->getXOverHWid());

        blockB = NULL;
        blockBName = "";
        blockC = NULL;
        blockCName = "";
        blockD = NULL;
        blockDName = "";
    }
    rotateCoords(rot);
    // adjust size of new turnout
    QPointF* pt = new QPointF(round(dispB->x()*xFactor),
                                    round(dispB->y()*yFactor));
    dispB = pt;
    pt = new QPointF(round(dispC->x()*xFactor),
                                    round(dispC->y()*yFactor));
    dispC = pt;
}
/*private*/ double LayoutTurnout::round (double x) {
    int i = (int)(x+0.5);
    return i;
}

/*protected*/ void LayoutTurnout::rotateCoords(double rot)
{
    // rotate coordinates
    double sineAng = qSin(rot*M_PI/180.0);
    double cosineAng = qCos(rot*M_PI/180.0);
    double x = (cosineAng*dispB->x()) - (sineAng*dispB->y());
    double y = (sineAng*dispB->x()) + (cosineAng*dispB->y());
    dispB = new QPointF(x,y);
    x = (cosineAng*dispC->x()) - (sineAng*dispC->y());
    y = (sineAng*dispC->x()) + (cosineAng*dispC->y());
    dispC = new QPointF(x,y);
}

/**
 * Accessor methods
*/
/*public*/ QString LayoutTurnout::getName() {return ident;}
/*public*/ bool LayoutTurnout::useBlockSpeed() { return _useBlockSpeed; }
/*public*/ QString LayoutTurnout::getTurnoutName() {
    if (namedTurnout!=NULL)
        return namedTurnout->getName();
    return turnoutName;
}
/*public*/ QString LayoutTurnout::getSecondTurnoutName() {
    if (secondNamedTurnout!=NULL)
        return secondNamedTurnout->getName();
    return secondTurnoutName;
}

/*public*/ bool LayoutTurnout::getHidden() {return hidden;}
/*public*/ void LayoutTurnout::setHidden(bool hide) {hidden = hide;}
/*public*/ QString LayoutTurnout::getBlockName() {return blockName;}
/*public*/ QString LayoutTurnout::getBlockBName() {return blockBName;}
/*public*/ QString LayoutTurnout::getBlockCName() {return blockCName;}
/*public*/ QString LayoutTurnout::getBlockDName() {return blockDName;}
/*public*/ QString LayoutTurnout::getSignalA1Name() {return signalA1Name;}
/*public*/ void LayoutTurnout::setSignalA1Name(QString signalName) {signalA1Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalA2Name() {return signalA2Name;}
/*public*/ void LayoutTurnout::setSignalA2Name(QString signalName) {signalA2Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalA3Name() {return signalA3Name;}
/*public*/ void LayoutTurnout::setSignalA3Name(QString signalName) {signalA3Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalB1Name() {return signalB1Name;}
/*public*/ void LayoutTurnout::setSignalB1Name(QString signalName) {signalB1Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalB2Name() {return signalB2Name;}
/*public*/ void LayoutTurnout::setSignalB2Name(QString signalName) {signalB2Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalC1Name() {return signalC1Name;}
/*public*/ void LayoutTurnout::setSignalC1Name(QString signalName) {signalC1Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalC2Name() {return signalC2Name;}
/*public*/ void LayoutTurnout::setSignalC2Name(QString signalName) {signalC2Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalD1Name() {return signalD1Name;}
/*public*/ void LayoutTurnout::setSignalD1Name(QString signalName) {signalD1Name = signalName;}
/*public*/ QString LayoutTurnout::getSignalD2Name() {return signalD2Name;}
/*public*/ void LayoutTurnout::setSignalD2Name(QString signalName) {signalD2Name = signalName;}

/*public*/ QString LayoutTurnout::getSignalAMast() {return signalAMast;}
/*public*/ void LayoutTurnout::setSignalAMast(QString signalMast) {signalAMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalBMast() {return signalBMast;}
/*public*/ void LayoutTurnout::setSignalBMast(QString signalMast) {signalBMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalCMast() {return signalCMast;}
/*public*/ void LayoutTurnout::setSignalCMast(QString signalMast) {signalCMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalDMast() {return signalDMast;}
/*public*/ void LayoutTurnout::setSignalDMast(QString signalMast) {signalDMast = signalMast;}

/*public*/ QString LayoutTurnout::getSensorA() {
    if(sensorANamed!=NULL)
        return sensorANamed->getName();
    return "";
}

/*public*/ void LayoutTurnout::setSensorA(QString sensorName)
{
    if(sensorName==NULL || sensorName==(""))
    {
        sensorANamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        sensorANamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorANamed=NULL;
    }
}

/*public*/ QString LayoutTurnout::getSensorB() {
    if(sensorBNamed!=NULL)
        return sensorBNamed->getName();
    return "";
}

/*public*/ void LayoutTurnout::setSensorB(QString sensorName) {
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

/*public*/ QString LayoutTurnout::getSensorC() {
    if(sensorCNamed!=NULL)
        return sensorCNamed->getName();
    return "";
}

/*public*/ void LayoutTurnout::setSensorC(QString sensorName) {
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

/*public*/ QString LayoutTurnout::getSensorD() {
    if(sensorDNamed!=NULL)
        return sensorDNamed->getName();
    return "";
}

/*public*/ void LayoutTurnout::setSensorD(QString sensorName) {
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

/*public*/ QString LayoutTurnout::getLinkedTurnoutName() {return linkedTurnoutName;}
/*public*/ void LayoutTurnout::setLinkedTurnoutName(QString s) {linkedTurnoutName = s;}

/*public*/ int LayoutTurnout::getLinkType() {return linkType;}
/*public*/ void LayoutTurnout::setLinkType(int type) {linkType = type;}
/*public*/ int LayoutTurnout::getTurnoutType() {return type;}
/*public*/ QObject* LayoutTurnout::getConnectA() {return connectA;}
/*public*/ QObject* LayoutTurnout::getConnectB() {return connectB;}
/*public*/ QObject* LayoutTurnout::getConnectC() {return connectC;}
/*public*/ QObject* LayoutTurnout::getConnectD() {return connectD;}

/*public*/ Turnout* LayoutTurnout::getTurnout() {
    if (namedTurnout==NULL) {
        // set physical turnout if possible and needed
        setTurnout(turnoutName);
        if (namedTurnout==NULL)
            return NULL;
    }
    return namedTurnout->getBean();
}

/*public*/ int LayoutTurnout::getContinuingSense() {return continuingSense;}

/*public*/ void LayoutTurnout::setTurnout(QString tName) {
    if (namedTurnout!=NULL) deactivateTurnout();
    turnoutName = tName;
    Turnout* turnout = InstanceManager::turnoutManagerInstance()->
                        getTurnout(turnoutName);
    if (turnout!=NULL) {
        namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutName, turnout);
        activateTurnout();
    }
    else {
        turnoutName = "";
        namedTurnout = NULL;
    }
}

/*public*/ Turnout* LayoutTurnout::getSecondTurnout() {
    if (secondNamedTurnout==NULL) {
        // set physical turnout if possible and needed
        setSecondTurnout(secondTurnoutName);

        if (secondNamedTurnout==NULL){
            return NULL;
        }
    }
    return secondNamedTurnout->getBean();
}

/*public*/ void LayoutTurnout::setSecondTurnout(QString tName) {

    if(tName!=NULL && tName==(secondTurnoutName)){
        return;
    }

    if (secondNamedTurnout!=NULL) deactivateTurnout();
    QString oldSecondTurnoutName = secondTurnoutName;
    secondTurnoutName = tName;
    Turnout* turnout = NULL;
    if(tName!=NULL){
        turnout = InstanceManager::turnoutManagerInstance()->
                        getTurnout(secondTurnoutName);
    }
    if (turnout!=NULL) {
        secondNamedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(secondTurnoutName, turnout);
        activateTurnout();
    }
    else {
        secondTurnoutName = "";
        secondNamedTurnout = NULL;
    }
    if ( (type == RH_TURNOUT) || (type ==LH_TURNOUT) || (type == WYE_TURNOUT) ){
        if(oldSecondTurnoutName!=NULL && oldSecondTurnoutName!=("")){
            Turnout* oldTurnout = InstanceManager::turnoutManagerInstance()->
                        getTurnout(oldSecondTurnoutName);
            LayoutTurnout* oldLinked = layoutEditor->findLayoutTurnoutByTurnoutName(oldTurnout->getSystemName());
            if(oldLinked==NULL)
                oldLinked = layoutEditor->findLayoutTurnoutByTurnoutName(oldTurnout->getUserName());
            if((oldLinked!=NULL) && oldLinked->getSecondTurnout()==getTurnout())
                oldLinked->setSecondTurnout(NULL);
        }
        if(turnout!=NULL){
            LayoutTurnout* newLinked = layoutEditor->findLayoutTurnoutByTurnoutName(turnout->getSystemName());
            if(newLinked==NULL)
                newLinked = layoutEditor->findLayoutTurnoutByTurnoutName(turnout->getUserName());
            if(newLinked!=NULL){
                newLinked->setSecondTurnout(turnoutName);
            }
        }
    }
}

/*public*/ void LayoutTurnout::setContinuingSense(int sense) {continuingSense=sense;}
/*public*/ void LayoutTurnout::setDisabled(bool state) {disabled = state;}
/*public*/ bool LayoutTurnout::isDisabled() {return disabled;}

/*public*/ void LayoutTurnout::setDisableWhenOccupied(bool state) {disableWhenOccupied = state;}
/*public*/ bool LayoutTurnout::isDisabledWhenOccupied() {return disableWhenOccupied;}
/*public*/ void LayoutTurnout::setConnectA(QObject* o,int type) {
    connectA = o;
    if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) ) {
        log.error("unexpected type of A connection to layoutturnout - "+QString("%1").arg(type));
    }
}
/*public*/ void LayoutTurnout::setConnectB(QObject* o,int type) {
    connectB = o;
    if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) ) {
        log.error("unexpected type of B connection to layoutturnout - "+QString("%1").arg(type));
    }
}
/*public*/ void LayoutTurnout::setConnectC(QObject* o,int type) {
    connectC = o;
    if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) ) {
        log.error("unexpected type of C connection to layoutturnout - "+QString("%1").arg(type));
    }
}
/*public*/ void LayoutTurnout::setConnectD(QObject* o,int type) {
    connectD = o;
    if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) ) {
        log.error("unexpected type of D connection to layoutturnout - "+QString("%1").arg(type));
    }
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlock() {return block;}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockB() {
        if (blockB!=NULL) return blockB;
        return block;
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockC() {
        if (blockC!=NULL) return blockC;
        return block;
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockD(){
        if (blockD!=NULL) return blockD;
        return block;
}
/*public*/ QPointF* LayoutTurnout::getCoordsCenter() {return center;}
/*public*/ QPointF* LayoutTurnout::getCoordsA() {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        double x = center->x() - dispC->x();
        double y = center->y() - dispC->y();
        return new QPointF(x,y);
    }
    else if (type==WYE_TURNOUT) {
        double x = center->x() - (0.5*(dispB->x() + dispC->x()));
        double y = center->y() - (0.5*(dispB->y() + dispC->y()));
        return new QPointF(x,y);
    }
    else {
        double x = center->x() - dispB->x();
        double y = center->y() - dispB->y();
        return new QPointF(x,y);
    }
}
/*public*/ QPointF* LayoutTurnout::getCoordsB() {
    double x = center->x() + dispB->x();
    double y = center->y() + dispB->y();
    return new QPointF(x,y);
}
/*public*/ QPointF* LayoutTurnout::getCoordsC() {
    double x = center->x() + dispC->x();
    double y = center->y() + dispC->y();
    return new QPointF(x,y);
}
/*public*/ QPointF* LayoutTurnout::getCoordsD() {
    // only allowed for single and double crossovers
    double x = center->x() - dispB->x();
    double y = center->y() - dispB->y();
    return new QPointF(x,y);
}

// updates connectivity for blocks assigned to this turnout and connected track segments
/*private*/ void LayoutTurnout::updateBlockInfo() {
    LayoutBlock* bA = NULL;
    LayoutBlock* bB = NULL;
    LayoutBlock* bC = NULL;
    LayoutBlock* bD = NULL;
    layoutEditor->auxTools->setBlockConnectivityChanged();
    if (block!=NULL) block->updatePaths();
    if (connectA!=NULL) {
        bA = ((TrackSegment*)connectA)->getLayoutBlock();
        if ((bA!=NULL) && (bA!=block)) bA->updatePaths();
    }
    if ((blockB!=NULL) && (blockB!=block) && (blockB!=bA)) blockB->updatePaths();
    if (connectB!=NULL) {
        bB = ((TrackSegment*)connectB)->getLayoutBlock();
        if ((bB!=NULL) && (bB!=block) && (bB!=bA) && (bB!=blockB)) bB->updatePaths();
    }
    if ((blockC!=NULL) && (blockC!=block) && (blockC!=bA) &&
            (blockC!=bB) && (blockC!=blockB)) blockC->updatePaths();
    if (connectC!=NULL) {
        bC = ((TrackSegment*)connectC)->getLayoutBlock();
        if ((bC!=NULL) && (bC!=block) && (bC!=bA) && (bC!=blockB) && (bC!=bB) &&
                (bC!=blockC)) bC->updatePaths();
    }
    if ((blockD!=NULL) && (blockD!=block) && (blockD!=bA) &&
            (blockD!=bB) && (blockD!=blockB) && (blockD!=bC) &&
                (blockD!=blockC)) blockD->updatePaths();
    if (connectD!=NULL) {
        bD = ((TrackSegment*)connectD)->getLayoutBlock();
        if ((bD!=NULL) && (bD!=block) && (bD!=bA) && (bD!=blockB) && (bD!=bB) &&
            (bD!=blockC) && (bD!=bC) && (bD!=blockD)) bD->updatePaths();
    }
}

/**
 * Set default size parameters to correspond to this turnout's size
 */
/*private*/ void LayoutTurnout::setUpDefaultSize() {
    // remove the overall scale factor
    double bX = dispB->x()/layoutEditor->getXScale();
    double bY = dispB->y()/layoutEditor->getYScale();
    double cX = dispC->x()/layoutEditor->getXScale();
    double cY = dispC->y()/layoutEditor->getYScale();
    // calculate default parameters according to type of turnout
    double lenB = qSqrt((bX*bX) + (bY*bY));
    double lenC = qSqrt((cX*cX) + (cY*cY));
    double distBC = qSqrt(((bX-cX)*(bX-cX)) + ((bY-cY)*(bY-cY)));
    if ( (type == LH_TURNOUT) || (type == RH_TURNOUT) ) {
        layoutEditor->setTurnoutBX(round(lenB+0.1));
        double xc = ((bX*cX)+(bY*cY))/lenB;
        layoutEditor->setTurnoutCX(round(xc+0.1));
        layoutEditor->setTurnoutWid(round(qSqrt((lenC*lenC)-(xc*xc))+0.1));
    }
    else if (type == WYE_TURNOUT) {
        double xx = qSqrt((lenB*lenB)-(0.25*(distBC*distBC)));
        layoutEditor->setTurnoutBX(round(xx+0.1));
        layoutEditor->setTurnoutCX(round(xx+0.1));
        layoutEditor->setTurnoutWid(round(distBC+0.1));
    }
    else if (type == DOUBLE_XOVER) {
        double lng = qSqrt((lenB*lenB)-(0.25*(distBC*distBC)));
        layoutEditor->setXOverLong(round(lng+0.1));
        layoutEditor->setXOverHWid(round((0.5*distBC)+0.1));
        layoutEditor->setXOverShort(round((0.5*lng)+0.1));
    }
    else if (type == RH_XOVER) {
        double distDC = qSqrt(((bX+cX)*(bX+cX)) + ((bY+cY)*(bY+cY)));
        layoutEditor->setXOverShort(round((0.25*distDC)+0.1));
        layoutEditor->setXOverLong(round((0.75*distDC)+0.1));
        double hwid = qSqrt((lenC*lenC)-(0.5625*distDC*distDC));
        layoutEditor->setXOverHWid(round(hwid+0.1));
    }
    else if (type == LH_XOVER) {
        double distDC = qSqrt(((bX+cX)*(bX+cX)) + ((bY+cY)*(bY+cY)));
        layoutEditor->setXOverShort(round((0.25*distDC)+0.1));
        layoutEditor->setXOverLong(round((0.75*distDC)+0.1));
        double hwid = qSqrt((lenC*lenC)-(0.0625*distDC*distDC));
        layoutEditor->setXOverHWid(round(hwid+0.1));
    }
}

/**
 * Set Up a Layout Block(s) for this Turnout
 */
/*public*/ void LayoutTurnout::setLayoutBlock (LayoutBlock* b) {
    block = b;
    if (b!=NULL) blockName = b->getID();
    else blockName = "";
}
/*public*/ void LayoutTurnout::setLayoutBlockB (LayoutBlock* b) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockB = b;
        if (b!=NULL) blockBName = b->getID();
        else blockBName = "";
    }
    else {
        log.error ("Attempt to set block B, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockC (LayoutBlock* b) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockC = b;
        if (b!=NULL) blockCName = b->getID();
        else blockCName = "";
    }
    else {
        log.error ("Attempt to set block C, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockD (LayoutBlock* b) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockD = b;
        if (b!=NULL) blockDName = b->getID();
        else blockDName = "";
    }
    else {
        log.error ("Attempt to set block D, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockByName (QString name) {
    blockName = name;
}
/*public*/ void LayoutTurnout::setLayoutBlockBByName (QString name) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockBName = name;
    }
    else {
        log.error ("Attempt to set block B name, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockCByName (QString name) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockCName = name;
    }
    else {
        log.error ("Attempt to set block C name, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockDByName (QString name) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockDName = name;
    }
    else {
        log.error ("Attempt to set block D name, but not a crossover");
    }
}

/**
 * Methods to test if turnout legs are mainline track or not
 *  Returns true if connecting track segment is mainline
 *  Defaults to not mainline if connecting track segment is missing
 */
/*public*/ bool LayoutTurnout::isMainlineA() {
    if (connectA != NULL)
        return ((TrackSegment)connectA).getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is B
            if (connectB != NULL)
                return ((TrackSegment)connectB).getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat
        else if ( ((connectB != NULL) &&
                (((TrackSegment)connectB).getMainline())) ||
                    ((connectC != NULL) &&
                        (((TrackSegment)connectC).getMainline())) )
            return true;
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineB() {
    if (connectB != NULL)
        return ((TrackSegment)connectB).getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is A
            if (connectA != NULL)
                return ((TrackSegment)connectA).getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat,
        //		B is normally the continuing straight
        else if (continuingSense == Turnout::CLOSED) {
            // user hasn't changed the continuing turnout state
            if (connectA != NULL)
                // if throat is mainline, this leg must be also
                return ((TrackSegment)connectA).getMainline();
        }
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineC() {
    if (connectC != NULL)
        return ((TrackSegment)connectC).getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is D
            if (connectD != NULL)
                return ((TrackSegment)connectD).getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat,
        //		B is normally the continuing straight
        else if (continuingSense == Turnout::THROWN) {
            // user has changed the continuing turnout state
            if (connectA != NULL)
                // if throat is mainline, this leg must be also
                return ((TrackSegment)connectA).getMainline();
        }
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineD() {
    // this is a crossover turnout
    if (connectD != NULL)
        return ((TrackSegment)connectD).getMainline();
    else if (connectC != NULL)
        return ((TrackSegment)connectC).getMainline();
    return false;
}

/**
 * Modify coordinates methods
 */
/*public*/ void LayoutTurnout::setCoordsCenter(QPointF* p) {
    center = p;
}
/*public*/ void LayoutTurnout::setCoordsA(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    if (type == DOUBLE_XOVER) {
        dispC = new QPointF(x,y);
        // adjust to maintain rectangle
        double oldLength =qSqrt( (dispB->x()*dispB->x()) +
                                                (dispB->y()*dispB->y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispB->x()*newLength/oldLength;
        y = dispB->y()*newLength/oldLength;
        dispB = new QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        dispC = new QPointF(x,y);
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB->x() + x)!=0.0) {
            a = (dispB->y() + y)/(dispB->x() + x);
            b = -y + (a*x);
            xi = -b/(a + (1.0/a));
            yi = (a*xi) + b;
        }
        if (type == RH_XOVER) {
            x = xi - (0.333333*(-x - xi));
            y = yi - (0.333333*(-y - yi));
        }
        else if (type == LH_XOVER) {
            x = xi - (3.0*(-x - xi));
            y = yi - (3.0*(-y - yi));
        }
        dispB = new QPointF(x,y);
    }
    else if (type == WYE_TURNOUT) {
        // modify both to maintain same angle at wye
        double temX = (dispB->x() + dispC->x());
        double temY = (dispB->y() + dispC->y());
        double temXx = (dispB->x() - dispC->x());
        double temYy = (dispB->y() - dispC->y());
        double tan =qSqrt( ((temX*temX)+(temY*temY))/
                            ((temXx*temXx)+(temYy*temYy)) );
        double xx = x + (y/tan);
        double yy = y - (x/tan);
        dispC = new QPointF(xx,yy);
        xx = x - (y/tan);
        yy = y + (x/tan);
        dispB = new QPointF(xx,yy);
    }
    else {
        dispB = new QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::setCoordsB(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispB = new QPointF(-x,-y);
    if ((type == DOUBLE_XOVER) || (type == WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength =qSqrt( (dispC->x()*dispC->x()) +
                                                (dispC->y()*dispC->y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispC->x()*newLength/oldLength;
        y = dispC->y()*newLength/oldLength;
        dispC = new QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispC->x() - x)!=0.0) {
            a = (dispC->y() - y)/(dispC->x() - x);
            b = y - (a*x);
            xi = -b/(a + (1.0/a));
            yi = (a*xi) + b;
        }
        if (type == LH_XOVER) {
            x = xi - (0.333333*(x - xi));
            y = yi - (0.333333*(y - yi));
        }
        else if (type == RH_XOVER) {
            x = xi - (3.0*(x - xi));
            y = yi - (3.0*(y - yi));
        }
        dispC = new QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::setCoordsC(QPointF* p) {
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispC = new QPointF(-x,-y);
    if ((type == DOUBLE_XOVER) || (type == WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength =qSqrt( (dispB->x()*dispB->x()) +
                                                (dispB->y()*dispB->y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispB->x()*newLength/oldLength;
        y = dispB->y()*newLength/oldLength;
        dispB = new QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB->x() + x)!=0.0) {
            a = (-dispB->y() + y)/(-dispB->x() + x);
            b = -y + (a*x);
            xi = -b/(a + (1.0/a));
            yi = (a*xi) + b;
        }
        if (type == RH_XOVER) {
            x = xi - (0.333333*(-x - xi));
            y = yi - (0.333333*(-y - yi));
        }
        else if (type == LH_XOVER) {
            x = xi - (3.0*(-x - xi));
            y = yi - (3.0*(-y - yi));
        }
        dispB = new QPointF(-x,-y);
    }
}
/*public*/ void LayoutTurnout::setCoordsD(QPointF* p) {
    // only used for crossovers
    double x = center->x() - p->x();
    double y = center->y() - p->y();
    dispB = new QPointF(x,y);
    if (type == DOUBLE_XOVER) {
        // adjust to maintain rectangle
        double oldLength =qSqrt( (dispC->x()*dispC->x()) +
                                                (dispC->y()*dispC->y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispC->x()*newLength/oldLength;
        y = dispC->y()*newLength/oldLength;
        dispC = new QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispC->x() + x)!=0.0) {
            a = (dispC->y() + y)/(dispC->x() + x);
            b = -y + (a*x);
            xi = -b/(a + (1.0/a));
            yi = (a*xi) + b;
        }
        if (type == LH_XOVER) {
            x = xi - (0.333333*(-x - xi));
            y = yi - (0.333333*(-y - yi));
        }
        else if (type == RH_XOVER) {
            x = xi - (3.0*(-x - xi));
            y = yi - (3.0*(-y - yi));
        }
        dispC = new QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::scaleCoords(float xFactor, float yFactor) {
    QPointF* pt = new QPointF(round(center->x()*xFactor),
                                    round(center->y()*yFactor));
    center = pt;
    pt = new QPointF(round(dispB->x()*xFactor),
                                    round(dispB->y()*yFactor));
    dispB = pt;
    pt = new QPointF(round(dispC->x()*xFactor),
                                    round(dispC->y()*yFactor));
    dispC = pt;
}

/**
 * Activate/Deactivate turnout to redraw when turnout state changes
 */
/*private*/ void LayoutTurnout::activateTurnout() {
    if (namedTurnout!=NULL) {
        namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener =
                            new PropertyChangeListener());
//        {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                layoutEditor.redrawPanel();
//            }
//        }, namedTurnout.getName(), "Layout Editor Turnout");
        connect(mTurnoutListener, SIGNAL(signalPropertyChange(PropertyChangeEvent*)), this, SLOT(redrawPanel()));
    }
    if (secondNamedTurnout!=NULL) {
        secondNamedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener, secondNamedTurnout->getName(), "Layout Editor Turnout");
    }
}
/*private*/ void LayoutTurnout::deactivateTurnout() {
    if (mTurnoutListener!=NULL) {
        namedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
        if(secondNamedTurnout!=NULL){
            secondNamedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
        }
        mTurnoutListener = NULL;
    }
}

/**
 * Toggle turnout if clicked on, physical turnout exists, and
 *    not disabled
 */
/*public*/ void LayoutTurnout::toggleTurnout() {
    if ((getTurnout()!=NULL) && (!disabled)) {
        if (disableWhenOccupied){
            if(disableOccupiedTurnout()){
                log.debug("Turnout not changed as Block is Occupied");
                return;
            }
        }
        // toggle turnout
        if (getTurnout()->getKnownState()==Turnout::CLOSED){
            getTurnout()->setCommandedState(Turnout::THROWN);
            if(getSecondTurnout()!=NULL)
                getSecondTurnout()->setCommandedState(Turnout::THROWN);
        }
        else {
            getTurnout()->setCommandedState(Turnout::CLOSED);
            if(getSecondTurnout()!=NULL)
                getSecondTurnout()->setCommandedState(Turnout::CLOSED);

        }
    }
}

/*private*/ bool LayoutTurnout::disableOccupiedTurnout(){
    if ((type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT)){
        if(block->getOccupancy()==LayoutBlock::OCCUPIED){
            log.debug("Block " + blockName + "is Occupied");
            return true;
        }
    }
    if ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER)){
        //If the turnout is set for straigh over, we need to deal with the straight over connecting blocks
        if (getTurnout()->getKnownState()==Turnout::CLOSED){
            if ((block->getOccupancy()==LayoutBlock::OCCUPIED) && (blockB->getOccupancy()==LayoutBlock::OCCUPIED)){
                log.debug("Blocks " + blockName + " & " + blockBName + " are Occupied");
                return true;
            }
            if ((blockC->getOccupancy()==LayoutBlock::OCCUPIED) && (blockD->getOccupancy()==LayoutBlock::OCCUPIED)){
                log.debug("Blocks " + blockCName + " & " + blockDName + " are Occupied");
                return true;
            }
        }

    }
    if ((type==DOUBLE_XOVER)||(type==LH_XOVER)){
        if (getTurnout()->getKnownState()==Turnout::THROWN){
            if ((blockB->getOccupancy()==LayoutBlock::OCCUPIED) && (blockD->getOccupancy()==LayoutBlock::OCCUPIED)){
                log.debug("Blocks " + blockBName + " & " + blockDName + " are Occupied");
                return true;
            }
        }
    }

    if ((type==DOUBLE_XOVER)||(type==RH_XOVER)){
        if (getTurnout()->getKnownState()==Turnout::THROWN){
            if ((block->getOccupancy()==LayoutBlock::OCCUPIED) && (blockC->getOccupancy()==LayoutBlock::OCCUPIED)) {
                log.debug("Blocks " + blockName + " & " + blockCName + " are Occupied");
                return true;
            }
        }
    }
    return false;
}



/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LayoutTurnout::setObjects(LayoutEditor* p) {
    connectA = p->findTrackSegmentByName(connectAName);
    connectB = p->findTrackSegmentByName(connectBName);
    connectC = p->findTrackSegmentByName(connectCName);
    connectD = p->findTrackSegmentByName(connectDName);
    if (tBlockName.length()>0) {
        block = p->getLayoutBlock(tBlockName);
        if (block!=NULL) {
            blockName = tBlockName;
            block->incrementUse();
        }
        else {
            log.error("bad blockname '"+tBlockName+"' in layoutturnout "+ident);
        }
    }
    if (tBlockBName.length()>0) {
        blockB = p->getLayoutBlock(tBlockBName);
        if (blockB!=NULL) {
            blockBName = tBlockBName;
            if (block!=blockB) blockB->incrementUse();
        }
        else {
            log.error("bad blockname '"+tBlockBName+"' in layoutturnout "+ident);
        }
    }
    if (tBlockCName.length()>0) {
        blockC = p->getLayoutBlock(tBlockCName);
        if (blockC!=NULL) {
            blockCName = tBlockCName;
            if ( (block!=blockC) && (blockB!=blockC) ) blockC->incrementUse();
        }
        else {
            log.error("bad blockname '"+tBlockCName+"' in layoutturnout "+ident);
        }
    }
    if (tBlockDName.length()>0) {
        blockD = p->getLayoutBlock(tBlockDName);
        if (blockD!=NULL) {
            blockDName = tBlockDName;
            if ( (block!=blockD) && (blockB!=blockD) &&
                    (blockC!=blockD) ) blockD->incrementUse();
        }
        else {
            log.error("bad blockname '"+tBlockDName+"' in layoutturnout "+ident);
        }
    }
    //Do the second one first then the activate is only called the once
    if (tSecondTurnoutName.length()>0) {
        Turnout* turnout = InstanceManager::turnoutManagerInstance()->
                            getTurnout(tSecondTurnoutName);
        if (turnout!=NULL) {
            secondNamedTurnout =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(tSecondTurnoutName, turnout);
            secondTurnoutName = tSecondTurnoutName;
        }
        else {
            log.error("bad turnoutname '"+tSecondTurnoutName+"' in layoutturnout "+ident);
            secondTurnoutName = "";
            secondNamedTurnout = NULL;
        }
    }
    if (tTurnoutName.length()>0) {
        Turnout* turnout = InstanceManager::turnoutManagerInstance()->
                            getTurnout(tTurnoutName);
        if (turnout!=NULL) {
            namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(tTurnoutName, turnout);
            turnoutName = tTurnoutName;
            activateTurnout();
        }
        else {
            log.error("bad turnoutname '"+tTurnoutName+"' in layoutturnout "+ident);
            turnoutName = "";
            namedTurnout = NULL;
        }
    }
}

/**
 * Display popup menu for information and editing
 */
/*protected*/ void LayoutTurnout::showPopUp(QMouseEvent* e, bool editable)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 if(editable)
 {
  switch (getTurnoutType())
  {
   case RH_TURNOUT:
    //popup->add(rb.getQString("RHTurnout"));
    actionRHTurnout = new QAction(tr("RHTurnout"), this);
    popup->addAction(actionRHTurnout);
    break;
   case LH_TURNOUT:
    //popup.add(rb.getQString("LHTurnout"));
    actionLHTurnout = new QAction(tr("LHTurnout"), this);
    popup->addAction(actionLHTurnout);
    break;
   case WYE_TURNOUT:
   //popup.add(rb.getQString("WYETurnout"));
    actionWYETurnout = new QAction(tr("WYETurnout"), this);
      popup->addAction(actionWYETurnout);
    break;
   case DOUBLE_XOVER:
    //popup.add(rb.getQString("XOverTurnout"));
    actionXOverTurnout = new QAction(tr("XOverTurnout"), this);
      popup->addAction(actionXOverTurnout);
    break;
   case RH_XOVER:
    //popup.add(rb.getQString("RHXOverTurnout"));
    actionRHXOverTurnout = new QAction(tr("RHXOverTurnout"), this);
    popup->addAction(actionRHXOverTurnout);
    break;
   case LH_XOVER:
    //popup.add(rb.getQString("LHXOverTurnout"));
    actionLHXOverTurnout = new QAction(tr("LHXOverTurnout"), this);
    popup->addAction(actionLHXOverTurnout);
    break;
   default : break;
  }
  //popup.add(ident);
  actionIdent = new QAction(ident, this);
  popup->addAction(actionIdent);

  if (getTurnout()==NULL)
  {
   //popup.add(rb.getQString("NoTurnout"));
   actionNoTurnout = new QAction(tr("NoTurnout"), this);
   popup->addAction(actionNoTurnout);
  }
  else
  {
   //popup.add(rb.getQString("Turnout")+": "+turnoutName);
   actionNewTurnout = new QAction(QString("Turnout")+": "+turnoutName,this);
   popup->addAction(actionNewTurnout);
  }
#if 0 // TODO:
  // Rotate if there are no track connections
  if ( (connectA==NULL) && (connectB==NULL) &&
                (connectC==NULL) && (connectD==NULL) )
  {
   JMenuItem rotateItem = new JMenuItem(rb.getQString("Rotate")+"...");
   popup.add(rotateItem);

   rotateItem.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent event) {
                bool entering = true;
                bool error = false;
                QString newAngle = "";
                while (entering) {
                    // prompt for rotation angle
                    error = false;
                    newAngle = JOptionPane.showInputDialog(layoutEditor,
                                        rb.getQString("EnterRotation")+" :");
                    if (newAngle.length()<1) return;  // cancelled
                    double rot = 0.0;
                    try {
                        rot = Double.parseDouble(newAngle);
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(layoutEditor,rb.getQString("Error3")+
                            " "+e,rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
                        error = true;
                        newAngle = "";
                    }
                    if (!error) {
                        entering = false;
                        if (rot!=0.0) {
                           rotateCoords(rot);
                           layoutEditor.redrawPanel();
                        }
                    }
                }
            }
        });
  }
  if (disableItem==NULL)
   disableItem = new JCheckBoxMenuItem(rb.getQString("Disabled"));
  disableItem.setSelected(disabled);
  popup.add(disableItem);
    disableItem.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                disabled = disableItem.isSelected();
            }
        });
    if (disableWhenOccupiedItem==NULL)
        disableWhenOccupiedItem = new JCheckBoxMenuItem(rb.getQString("DisabledWhenOccupied"));
    disableWhenOccupiedItem.setSelected(disableWhenOccupied);
    popup.add(disableWhenOccupiedItem);
    disableWhenOccupiedItem.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                disableWhenOccupied = disableWhenOccupiedItem.isSelected();
            }
        });
    if (blockName==("")) popup.add(rb.getQString("NoBlock"));
    else popup.add(rb.getQString("Block")+": "+getLayoutBlock().getID());
    if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) ) {
        // check if extra blocks have been entered
        if (blockB!=NULL) popup.add(rb.getQString("Block2ID")+": "+blockBName);
        if (blockC!=NULL) popup.add(rb.getQString("Block3ID")+": "+blockCName);
        if (blockD!=NULL) popup.add(rb.getQString("Block4ID")+": "+blockDName);
    }
    if (hidden) popup.add(rb.getQString("Hidden"));
    else popup.add(rb.getQString("NotHidden"));
    popup.add(new JSeparator(JSeparator.HORIZONTAL));
    popup.add(new AbstractAction(rb.getQString("UseSizeAsDefault")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                setUpDefaultSize();
            }
        });
    popup.add(new AbstractAction(rb.getQString("Edit")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                editLayoutTurnout();
            }
        });
    popup.add(new AbstractAction(rb.getQString("Remove")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                if (layoutEditor.removeLayoutTurnout(instance)) {
                    // Returned true if user did not cancel
                    remove();
                    dispose();
                }
            }
        });
    if (getTurnout()!=NULL) {
        popup.add(new AbstractAction(rb.getQString("SetSignals")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                if ( (getTurnoutType()==DOUBLE_XOVER) || (getTurnoutType()==RH_XOVER) ||
                                        (getTurnoutType()==LH_XOVER) ) {
                    tools.setSignalsAtXoverTurnoutFromMenu(instance,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
                else if (linkType==NO_LINK) {
                    tools.setSignalsAtTurnoutFromMenu(instance,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
                else if (linkType==THROAT_TO_THROAT) {
                    tools.setThroatToThroatFromMenu(instance,linkedTurnoutName,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
                else if (linkType==FIRST_3_WAY) {
                    tools.set3WayFromMenu(turnoutName, linkedTurnoutName,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
                else if (linkType==SECOND_3_WAY) {
                    tools.set3WayFromMenu(linkedTurnoutName, turnoutName,
                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
            }
        });
    }
    if (!blockName==("")){
        /*final*/ QStringList boundaryBetween = getBlockBoundaries();
        bool blockBoundaries = false;
        for (int i = 0; i<4; i++){
            if(boundaryBetween[i]!=NULL)
                blockBoundaries=true;
        }
        if (InstanceManager::layoutBlockManagerInstance()->isAdvancedRoutingEnabled()){

            if(blockBName==("") && blockCName==("") && blockDName==("")){
                popup.add(new AbstractAction(rb.getQString("ViewBlockRouting")) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
                        routeTableAction.actionPerformed(e);
                    }
                });
            } else {
                JMenu viewRouting = new JMenu(rb.getQString("ViewBlockRouting"));
                viewRouting.add(new AbstractAction(blockName) {
                    /*public*/ void actionPerformed(ActionEvent e) {
                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockName, getLayoutBlock());
                        routeTableAction.actionPerformed(e);
                    }
                });
                if(!blockBName==("") && !blockBName==(blockName)){
                    viewRouting.add(new AbstractAction(blockBName) {
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockBName, getLayoutBlockB());
                            routeTableAction.actionPerformed(e);
                        }
                    });
                }

                if(!blockCName==("") && !blockCName==(blockName) && !blockCName==(blockBName)){
                    viewRouting.add(new AbstractAction(blockCName) {
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockCName, getLayoutBlockC());
                            routeTableAction.actionPerformed(e);
                        }
                    });
                }

                if(!blockDName==("")  && !blockDName==(blockName) && !blockDName==(blockBName) && !blockDName==(blockCName)){
                    viewRouting.add(new AbstractAction(blockDName) {
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockDName, getLayoutBlockD());
                            routeTableAction.actionPerformed(e);
                        }
                    });
                }

                popup.add(viewRouting);
            }
        }

        if (blockBoundaries){
            popup.add(new AbstractAction(rb.getQString("SetSignalMasts")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(layoutEditor);
                    }

                    tools.setSignalMastsAtTurnoutFromMenu(instance,
                    boundaryBetween);
                }
            });
            popup.add(new AbstractAction(rb.getQString("SetSensors")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (tools == NULL) {
                        tools = new LayoutEditorTools(layoutEditor);
                    }

                    tools.setSensorsAtTurnoutFromMenu(instance,
                    boundaryBetween, layoutEditor.sensorIconEditor, layoutEditor.sensorFrame);
                }
            });
        }
  }
#endif
  setAdditionalEditPopUpMenu(popup);
//  layoutEditor.setShowAlignmentMenu(popup);
//  popup.show(e.getComponent(), e->x(), e->y());
  popup->exec();
 }
 else if(!viewAdditionalMenu->isEmpty())
 {
  setAdditionalViewPopUpMenu(popup);
  //popup.show(e.getComponent(), e->x(), e->y());
  popup->exec();
 }
}

/*public*/ QStringList* LayoutTurnout::getBlockBoundaries()
{
    /*final*/ QStringList* boundaryBetween = new QStringList();
 //QVector<QString> boundaryBetween = new QVector<QString>(4);
 if ((type==WYE_TURNOUT) || (type ==RH_TURNOUT) || (type == LH_TURNOUT))
 {
        //This should only be needed where we are looking at a single turnout.
        if(block!=NULL){
            LayoutBlock* aLBlock = NULL;
            LayoutBlock* bLBlock = NULL;
            LayoutBlock* cLBlock = NULL;
#if 0 //TODO
            if (connectA instanceof TrackSegment){
                aLBlock =((TrackSegment)connectA).getLayoutBlock();
                if(aLBlock!=block){
                    try {
                        boundaryBetween[0]=(aLBlock.getDisplayName()+ " - " + block.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                }
            }

            if (connectB instanceof TrackSegment){
                bLBlock =((TrackSegment)connectB).getLayoutBlock();
                if(bLBlock!=block){
                    try {
                        boundaryBetween[1]=(bLBlock.getDisplayName()+ " - " + block.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection B doesn't contain a layout block");
                    }
                }
            }
            if ((connectC instanceof TrackSegment) && (((TrackSegment)connectC).getLayoutBlock()!=block)){
                cLBlock = ((TrackSegment)connectC).getLayoutBlock();
                if(cLBlock!=block){
                    try{
                        boundaryBetween[2]=(cLBlock.getDisplayName()+ " - " + block.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection C doesn't contain a layout block");
                    }
                }
            }
        }
    }

    else {
        QVector<LayoutBlock> localblks = new QVector<LayoutBlock*>(4);
        if(block!=NULL)
            localblks.add(block);
        if(blockB!=NULL)
            localblks.add(blockB);
        if(blockC!=NULL)
            localblks.add(blockC);
        if(blockD!=NULL)
            localblks.add(blockD);

        LayoutBlock* aLBlock = NULL;
        LayoutBlock* bLBlock = NULL;
        LayoutBlock* cLBlock = NULL;
        LayoutBlock* dLBlock = NULL;
        if(block!=NULL){
            if (connectA instanceof TrackSegment){
                aLBlock =((TrackSegment)connectA).getLayoutBlock();
                if(aLBlock!=block){
                    try {
                        boundaryBetween[0]=(aLBlock.getDisplayName()+ " - " + block.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                } else if (block!=blockB){
                    try {
                        boundaryBetween[0]=(block.getDisplayName()+ " - " + blockB.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                }
            }

            if (connectB instanceof TrackSegment){
                bLBlock =((TrackSegment)connectB).getLayoutBlock();

                if (bLBlock!=block && bLBlock!=blockB){
                    try {
                        boundaryBetween[1]=(bLBlock.getDisplayName()+ " - " + blockB.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection B doesn't contain a layout block");
                    }
                } else if (block!=blockB){
                    //This is an interal block on the turnout
                    try {
                        boundaryBetween[1]=(blockB.getDisplayName()+ " - " + block.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                }
            }
            if (connectC instanceof TrackSegment){
                cLBlock =((TrackSegment)connectC).getLayoutBlock();
                if (cLBlock!=block && cLBlock!=blockB && cLBlock!=blockC) {
                    try{
                        boundaryBetween[2]=(cLBlock.getDisplayName()+ " - " + blockC.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection C doesn't contain a layout block");
                    }
                } else if (blockC!=blockD){
                    //This is an interal block on the turnout
                    try {
                        boundaryBetween[2]=(blockC.getDisplayName()+ " - " + blockD.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                }
            }
            if (connectD instanceof TrackSegment){
                dLBlock =((TrackSegment)connectD).getLayoutBlock();
                if (dLBlock!=block && dLBlock!=blockB && dLBlock!=blockC && dLBlock!=blockD) {
                    try{
                        boundaryBetween[3]=(dLBlock.getDisplayName()+ " - " + blockD.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection C doesn't contain a layout block");
                    }
                } else if (blockC!=blockD){
                    //This is an interal block on the turnout
                    try {
                        boundaryBetween[3]=(blockD.getDisplayName()+ " - " + blockC.getDisplayName());
                    } catch (java.lang.NullPointerException e){
                        //Can be considered normal if tracksegement hasn't yet been allocated a block
                        log.debug("TrackSegement at connection A doesn't contain a layout block");
                    }
                }
            }
#endif
        }
    }
    return boundaryBetween;
}


/**
 * Edit a Layout Turnout
 */
/*protected*/ void LayoutTurnout::editLayoutTurnout()
{
 if (editOpen)
 {
  editLayoutTurnoutFrame->setVisible(true);
  return;
 }
#if 0 //TODO:
 // Initialize if needed
 if (editLayoutTurnoutFrame == NULL) {
        editLayoutTurnoutFrame = new JmriJFrame( rb.getQString("EditTurnout"), false, true );
        editLayoutTurnoutFrame.addHelpMenu("package.jmri.jmrit.display.EditLayoutTurnout", true);
        editLayoutTurnoutFrame.setLocation(50,30);
        Container contentPane = editLayoutTurnoutFrame.getContentPane();
        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        // setup turnout name
        JPanel panel1 = new JPanel();
        panel1.setLayout(new FlowLayout());
        JLabel turnoutNameLabel = new JLabel( rb.getQString("Turnout")+" "+rb.getQString("Name") );
        panel1.add(turnoutNameLabel);
        panel1.add(turnoutNameField);
        turnoutNameField.setToolTipText( rb.getQString("EditTurnoutNameHint") );
        contentPane.add(panel1);

        JPanel panel1a = new JPanel();
        panel1a.setLayout(new BoxLayout(panel1a, BoxLayout.Y_AXIS));
        secondTurnoutComboBox = new JmriBeanComboBox(InstanceManager.turnoutManagerInstance(), getSecondTurnout(), JmriBeanComboBox.DISPLAYNAME);
        additionalTurnout.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                if(additionalTurnout.isSelected()){
                    secondTurnoutLabel.setEnabled(true);
                    secondTurnoutComboBox.setEnabled(true);
                } else  {
                    secondTurnoutLabel.setEnabled(false);
                    secondTurnoutComboBox.setEnabled(false);
                }
            }
        });
        if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) ) {
            additionalTurnout.setText(rb.getQString("ThrowTwoTurnouts"));
        }
        panel1a.add(additionalTurnout);
        contentPane.add(panel1a);
        secondTurnoutLabel = new JLabel( rb.getQString("Supporting") + rb.getQString("Turnout")+" "+rb.getQString("Name") );
        secondTurnoutLabel.setEnabled(false);
        secondTurnoutComboBox.setEnabled(false);
        JPanel panel1b = new JPanel();
        panel1b.add(secondTurnoutLabel);
        panel1b.add(secondTurnoutComboBox);
        contentPane.add(panel1b);


        // add continuing state choice, if not crossover
        if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) ) {
            JPanel panel3 = new JPanel();
            panel3.setLayout(new FlowLayout());
            stateBox.removeAllItems();
            stateBox.addItem( InstanceManager.turnoutManagerInstance().getClosedText() );
            turnoutClosedIndex = 0;
            stateBox.addItem( InstanceManager.turnoutManagerInstance().getThrownText() );
            turnoutThrownIndex = 1;
            stateBox.setToolTipText(rb.getQString("StateToolTip"));
            panel3.add (new JLabel(rb.getQString("ContinuingState")));
            panel3.add (stateBox);
            contentPane.add(panel3);
        }

        JPanel panel33 = new JPanel();
        panel33.setLayout(new FlowLayout());
        hiddenBox.setToolTipText(rb.getQString("HiddenToolTip"));
        panel33.add (hiddenBox);
        contentPane.add(panel33);

        // setup block name
        JPanel panel2 = new JPanel();
        panel2.setLayout(new FlowLayout());
        JLabel blockNameLabel = new JLabel( rb.getQString("BlockID"));
        panel2.add(blockNameLabel);
        panel2.add(blockNameField);
        blockNameField.setToolTipText( rb.getQString("EditBlockNameHint") );
        contentPane.add(panel2);
        if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) ) {
            JPanel panel21 = new JPanel();
            panel21.setLayout(new FlowLayout());
            JLabel blockBNameLabel = new JLabel( rb.getQString("Block2ID"));
            panel21.add(blockBNameLabel);
            panel21.add(blockBNameField);
            blockBNameField.setToolTipText( rb.getQString("EditBlockBNameHint") );
            contentPane.add(panel21);
            JPanel panel22 = new JPanel();
            panel22.setLayout(new FlowLayout());
            JLabel blockCNameLabel = new JLabel( rb.getQString("Block3ID"));
            panel22.add(blockCNameLabel);
            panel22.add(blockCNameField);
            blockCNameField.setToolTipText( rb.getQString("EditBlockCNameHint") );
            contentPane.add(panel22);
            JPanel panel23 = new JPanel();
            panel23.setLayout(new FlowLayout());
            JLabel blockDNameLabel = new JLabel( rb.getQString("Block4ID"));
            panel23.add(blockDNameLabel);
            panel23.add(blockDNameField);
            blockDNameField.setToolTipText( rb.getQString("EditBlockDNameHint") );
            contentPane.add(panel23);
        }
        // set up Edit Block, Done and Cancel buttons
        JPanel panel5 = new JPanel();
        panel5.setLayout(new FlowLayout());
        // Edit Block
        panel5.add(turnoutEditBlock = new JButton(rb.getQString("EditBlock")));
        turnoutEditBlock.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                turnoutEditBlockPressed(e);
            }
        });
        turnoutEditBlock.setToolTipText( rb.getQString("EditBlockHint") );
        // Done
        panel5.add(turnoutEditDone = new JButton(rb.getQString("Done")));
        turnoutEditDone.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                turnoutEditDonePressed(e);
            }
        });
        turnoutEditDone.setToolTipText( rb.getQString("DoneHint") );
        // Cancel
        panel5.add(turnoutEditCancel = new JButton(rb.getQString("Cancel")));
        turnoutEditCancel.addActionListener(new ActionListener() {
            /*public*/ void actionPerformed(ActionEvent e) {
                turnoutEditCancelPressed(e);
            }
        });
        turnoutEditCancel.setToolTipText( rb.getQString("CancelHint") );
        contentPane.add(panel5);
        if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) ) {
            JPanel panel6 = new JPanel();
            panel6.setLayout(new FlowLayout());
            // Edit Block 2
            panel6.add(turnoutEditBlockB = new JButton(rb.getQString("EditBlock2")));
            turnoutEditBlockB.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    turnoutEditBlockBPressed(e);
                }
            });
            turnoutEditBlockB.setToolTipText( rb.getQString("EditBlockBHint") );
            // Edit Block 3
            panel6.add(turnoutEditBlockC = new JButton(rb.getQString("EditBlock3")));
            turnoutEditBlockC.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    turnoutEditBlockCPressed(e);
                }
            });
            turnoutEditBlockC.setToolTipText( rb.getQString("EditBlockCHint") );
            // Edit Block 4
            panel6.add(turnoutEditBlockD = new JButton(rb.getQString("EditBlock4")));
            turnoutEditBlockD.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    turnoutEditBlockDPressed(e);
                }
            });
            turnoutEditBlockD.setToolTipText( rb.getQString("EditBlockDHint") );
            contentPane.add(panel6);
        }
    }

    hiddenBox.setSelected(hidden);

    // Set up for Edit
    blockNameField.setText(blockName);
    if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) ) {
        blockBNameField.setText(blockBName);
        blockCNameField.setText(blockCName);
        blockDNameField.setText(blockDName);
    }
    turnoutNameField.setText(turnoutName);


    if(secondNamedTurnout!=NULL){
        additionalTurnout.setSelected(true);
        secondTurnoutLabel.setEnabled(true);
        secondTurnoutComboBox.setEnabled(true);
    }

    if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) ) {
        if (continuingSense==Turnout.CLOSED) {
            stateBox.setSelectedIndex(turnoutClosedIndex);
        }
        else {
            stateBox.setSelectedIndex(turnoutThrownIndex);
        }
    }

    editLayoutTurnoutFrame.addWindowListener(new java.awt.event.WindowAdapter() {
            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                turnoutEditCancelPressed(NULL);
            }
        });
    editLayoutTurnoutFrame.pack();
    editLayoutTurnoutFrame.setVisible(true);
    editOpen = true;
    needsBlockUpdate = false;
#endif
}
#if 0 // TODO:
void turnoutEditBlockPressed(ActionEvent a) {
    // check if a block name has been entered
    if (!blockName==(blockNameField.getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (block!=NULL) && (block!=blockB) && (block!=blockC)
                        && (block!=blockD) ) {
            block.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockName = blockNameField.getText().trim();
        block = layoutEditor.provideLayoutBlock(blockName);
        if (block==NULL) {
            blockName = "";
        }
        // decrement use if block was already counted
        if ( (block!=NULL) && ( (block==blockB) || (block==blockC) ||
                (block==blockD) ) ) block.decrementUse();
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (block==NULL) {
        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    block.editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor.setDirty();
}
void turnoutEditBlockBPressed(ActionEvent a) {
    // check if a block name has been entered
    if (!blockBName==(blockBNameField.getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (blockB!=NULL) && (block!=blockB) && (blockB!=blockC)
                        && (blockB!=blockD) ) {
            blockB.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockBName = blockBNameField.getText().trim();
        blockB = layoutEditor.provideLayoutBlock(blockBName);
        if (blockB==NULL) {
            blockBName = "";
        }
        // decrement use if block was already counted
        if ( (blockB!=NULL) && ( (block==blockB) || (blockB==blockC) ||
                (blockB==blockD) ) ) blockB.decrementUse();
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockB==NULL) {
        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockB.editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor.setDirty();
}
void turnoutEditBlockCPressed(ActionEvent a) {
    // check if a block name has been entered
    if (!blockCName==(blockCNameField.getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (blockC!=NULL) && (block!=blockC) && (blockB!=blockC)
                        && (blockC!=blockD) ) {
            blockC.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockCName = blockCNameField.getText().trim();
        blockC = layoutEditor.provideLayoutBlock(blockCName);
        if (blockC==NULL) {
            blockCName = "";
        }
        // decrement use if block was already counted
        if ( (blockC!=NULL) && ( (block==blockC) || (blockB==blockC) ||
                (blockC==blockD) ) ) blockD.decrementUse();
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockC==NULL) {
        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockC.editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor.setDirty();
}
void turnoutEditBlockDPressed(ActionEvent a) {
    // check if a block name has been entered
    if (!blockDName==(blockDNameField.getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (blockD!=NULL) && (block!=blockD) && (blockB!=blockD)
                        && (blockC!=blockD) ) {
            blockD.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockDName = blockDNameField.getText().trim();
        blockD = layoutEditor.provideLayoutBlock(blockDName);
        if (blockD==NULL) {
            blockDName = "";
        }
        // decrement use if block was already counted
        if ( (blockD!=NULL) && ( (block==blockD) || (blockB==blockD) ||
                (blockC==blockD) ) ) blockD.decrementUse();
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockD==NULL) {
        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
                rb.getQString("Error1"),
                rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
        return;
    }
    blockD.editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor.setDirty();
}
void turnoutEditDonePressed(ActionEvent a) {
    // check if Turnout changed
    if ( !turnoutName==(turnoutNameField.getText().trim()) ) {
        // turnout has changed
        QString newName = turnoutNameField.getText().trim();
        if ( layoutEditor.validatePhysicalTurnout(newName,
                        editLayoutTurnoutFrame) ) {
            setTurnout(newName);
        }
        else {
            namedTurnout = NULL;
            turnoutName = "";
            turnoutNameField.setText("");
        }
        needRedraw = true;
    }

    if(additionalTurnout.isSelected()){
        if ( !secondTurnoutName==(secondTurnoutComboBox.getSelectedDisplayName()) ) {
            if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) ) {
            // turnout has changed
                QString newName = secondTurnoutComboBox.getSelectedDisplayName();
                if ( layoutEditor.validatePhysicalTurnout(newName,
                                editLayoutTurnoutFrame) ) {
                    setSecondTurnout(newName);
                }
                else {
                    additionalTurnout.setSelected(false);
                    secondNamedTurnout = NULL;
                    secondTurnoutName = "";
                    //secondTurnoutNameField.setText("");
                }
                needRedraw = true;
            } else {
                setSecondTurnout(secondTurnoutComboBox.getSelectedDisplayName());
            }
        }
    } else {
        setSecondTurnout(NULL);
    }
    // set the continuing route Turnout State
    if ( (type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT) ) {
        continuingSense = Turnout.CLOSED;
        if ( stateBox.getSelectedIndex() == turnoutThrownIndex ) {
            continuingSense = Turnout.THROWN;
        }
    }
    // check if Block changed
    if ( !blockName==(blockNameField.getText().trim()) ) {
        // block has changed, if old block exists, decrement use
        if ( (block!=NULL) && (block!=blockB) && (block!=blockC) &&
                (block!=blockD) ) {
            block.decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockName = blockNameField.getText().trim();
        block = layoutEditor.provideLayoutBlock(blockName);
        if (block==NULL) {
            blockName = "";
        }
        // decrement use if block was already counted
        if ( (block!=NULL) && ( (block==blockB) || (block==blockC) ||
                (block==blockD) ) ) block.decrementUse();
        needRedraw = true;
        needsBlockUpdate = true;
    }
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        // check if Block 2 changed
        if ( !blockBName==(blockBNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if ( (blockB!=NULL) && (block!=blockB) && (blockB!=blockC)
                        && (blockB!=blockD) ) {
                blockB.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockBName = blockBNameField.getText().trim();
            blockB = layoutEditor.provideLayoutBlock(blockBName);
            if (blockB==NULL) {
                blockBName = "";
            }
            // decrement use if block was already counted
            if ( (blockB!=NULL) && ( (block==blockB) || (blockB==blockC) ||
                    (blockB==blockD) ) ) blockB.decrementUse();
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 3 changed
        if (!blockCName==(blockCNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if ( (blockC!=NULL) && (block!=blockC) && (blockB!=blockC)
                        && (blockC!=blockD) ) {
                blockC.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockCName = blockCNameField.getText().trim();
            blockC = layoutEditor.provideLayoutBlock(blockCName);
            if (blockC==NULL) {
                blockCName = "";
            }


            // decrement use if block was already counted
            if ( (blockC!=NULL) && ( (block==blockC) || (blockB==blockC) ||
                    (blockC==blockD) ) ) blockC.decrementUse();
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 4 changed
        if (!blockDName==(blockDNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if ( (blockD!=NULL) && (block!=blockD) && (blockB!=blockD)
                        && (blockC!=blockD) ) {
                blockD.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockDName = blockDNameField.getText().trim();
            blockD = layoutEditor.provideLayoutBlock(blockDName);
            if (blockD==NULL) {
                blockDName = "";
            }
            // decrement use if block was already counted
            if ( (blockD!=NULL) && ( (block==blockD) || (blockB==blockD) ||
                    (blockC==blockD) ) ) blockD.decrementUse();
            needRedraw = true;
            needsBlockUpdate = true;
        }
    }
    // set hidden
    bool oldHidden = hidden;
    hidden = hiddenBox.isSelected();
    if(oldHidden!=hidden)
        needRedraw=true;
    editOpen = false;
    editLayoutTurnoutFrame.setVisible(false);
    editLayoutTurnoutFrame.dispose();
    editLayoutTurnoutFrame = NULL;
    if (needsBlockUpdate){
        updateBlockInfo();
        reCheckBlockBoundary();
    }
    if (needRedraw) {
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }
}
void turnoutEditCancelPressed(ActionEvent a) {
    editOpen = false;
    editLayoutTurnoutFrame.setVisible(false);
    editLayoutTurnoutFrame.dispose();
    editLayoutTurnoutFrame = NULL;
    if (needsBlockUpdate) updateBlockInfo();
    if (needRedraw) {
        layoutEditor.redrawPanel();
        layoutEditor.setDirty();
    }
}
#endif
/*public*/ void LayoutTurnout::reCheckBlockBoundary(){
    if(connectA==NULL && connectB==NULL && connectC==NULL){
        if ((type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT)){
            if(getSignalAMast()!=(""))
                removeSML(getSignalAMast());
            if(getSignalBMast()!=(""))
                removeSML(getSignalBMast());
            if(getSignalCMast()!=(""))
                removeSML(getSignalCMast());
            if(getSignalDMast()!=(""))
                removeSML(getSignalDMast());
            signalAMast = "";
            signalBMast = "";
            signalCMast = "";
            sensorANamed=NULL;
            sensorBNamed=NULL;
            sensorCNamed=NULL;
            return;

        } else if (((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER)) && connectD==NULL){
            if(getSignalAMast()!=(""))
                removeSML(getSignalAMast());
            if(getSignalBMast()!=(""))
                removeSML(getSignalBMast());
            if(getSignalCMast()!=(""))
                removeSML(getSignalCMast());
            if(getSignalDMast()!=(""))
                removeSML(getSignalDMast());
            signalAMast = "";
            signalBMast = "";
            signalCMast = "";
            signalDMast = "";
            sensorANamed=NULL;
            sensorBNamed=NULL;
            sensorCNamed=NULL;
            sensorDNamed=NULL;
            return;
        }
    }

    if(connectA==NULL || connectB==NULL || connectC==NULL){
        //could still be in the process of rebuilding.
        return;
    } else if ((connectD == NULL) && ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER))){
        //could still be in the process of rebuilding.
        return;
    }

    TrackSegment* trkA;
    TrackSegment* trkB;
    TrackSegment* trkC;
    TrackSegment* trkD;
#if 0
    if(connectA instanceof TrackSegment){
        trkA = (TrackSegment)connectA;
        if(trkA.getLayoutBlock()==block){
            signalAMast = "";
            sensorANamed=NULL;
            if(!getSignalAMast()==(""))
                removeSML(getSignalAMast());
        }
    }
    if(connectB instanceof TrackSegment){
        trkB = (TrackSegment)connectB;
        if(trkB.getLayoutBlock()==block || trkB.getLayoutBlock()==blockB){
            signalBMast = "";
            sensorBNamed=NULL;
            if(!getSignalBMast()==(""))
                removeSML(getSignalBMast());
        }
    } if(connectC instanceof TrackSegment) {
        trkC = (TrackSegment)connectC;
        if(trkC.getLayoutBlock()==block || trkC.getLayoutBlock()==blockB || trkC.getLayoutBlock()==blockC){
            signalCMast = "";
            sensorCNamed=NULL;
            if(!getSignalCMast()==(""))
                removeSML(getSignalCMast());
        }
    } if(connectD!=NULL && connectD instanceof TrackSegment && ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER))){
        trkD = (TrackSegment)connectD;
        if(trkD.getLayoutBlock()==block || trkD.getLayoutBlock()==blockB || trkD.getLayoutBlock()==blockC || trkD.getLayoutBlock()==blockD){
            signalDMast = "";
            sensorDNamed=NULL;
            if(!getSignalDMast()==(""))
                removeSML(getSignalDMast());
        }
    }
#endif
}

void LayoutTurnout::removeSML(QString signalMast){
#if 0
    if(signalMast==NULL || signalMast==(""))
        return;
    SignalMast* mast = InstanceManager::signalMastManagerInstance().getSignalMast(signalMast);
    if(InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager.signalMastLogicManagerInstance().isSignalMastUsed(mast)){
        SignallingGuiTools.removeSignalMastLogic(NULL, mast);
    }
#endif
}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void LayoutTurnout::dispose() {
}

/**
 * Removes this object from display and persistance
 */
void LayoutTurnout::remove() {
    // if a turnout has been activated, deactivate it
    deactivateTurnout();
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool LayoutTurnout::isActive() {
    return active;
}


/*public*/ void LayoutTurnout::addEditPopUpMenu(QAction* menu){
    if(!editAdditionalMenu->contains(menu)){
        editAdditionalMenu->append(menu);
    }
}

/*public*/ void LayoutTurnout::addViewPopUpMenu(QAction* menu){
    if(!viewAdditionalMenu->contains(menu)){
        viewAdditionalMenu->append(menu);
    }
}

/*public*/ void LayoutTurnout::setAdditionalEditPopUpMenu(QMenu* popup){
    if(editAdditionalMenu->isEmpty())
        return;
    popup->addSeparator();
    foreach(QAction* mi, *editAdditionalMenu){
        popup->addAction(mi);
    }
}

/*public*/ void LayoutTurnout::setAdditionalViewPopUpMenu(QMenu* popup){
    if(viewAdditionalMenu->isEmpty())
        return;
    popup->addSeparator();
    foreach(QAction* mi, *viewAdditionalMenu){
        popup->addAction(mi);
    }
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutTurnout.class.getName());

//}
