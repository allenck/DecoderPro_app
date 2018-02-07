#include "layoutturnout.h"
#include "instancemanager.h"
#include <qmath.h>
#include <QMessageBox>
#include "inputdialog.h"
//#include "editturnout.h"
#include "layouteditor.h"
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QGraphicsItem>
#include "jtextfield.h"
#include "layoutblockroutetableaction.h"
#include "signalmastmanager.h"
#include "signalmastlogicmanager.h"
#include "signallingguitools.h"
#include "editturnout.h"
#include "jmribeancombobox.h"
#include <QGroupBox>

//LayoutTurnout::LayoutTurnout(QObject *parent) :
//    QObject(parent)
//{

//}
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
/*public*/ /*static*/ /*final*/ int LayoutTurnout::UNKNOWN = Turnout::UNKNOWN;
/*public*/ /*static*/ /*final*/ int LayoutTurnout::STATE_AC = 0x02;
/*public*/ /*static*/ /*final*/ int LayoutTurnout::STATE_BD = 0x04;
/*public*/ /*static*/ /*final*/ int LayoutTurnout::STATE_AD = 0x06;
/*public*/ /*static*/ /*final*/ int LayoutTurnout::STATE_BC = 0x08;

// program default turnout size parameters
/*public*/ /*static*/ /*final*/ double LayoutTurnout::turnoutBXDefault = 20.0;  // RH, LH, WYE
/*public*/ /*static*/ /*final*/ double LayoutTurnout::turnoutCXDefault = 20.0;
/*public*/ /*static*/ /*final*/ double LayoutTurnout::turnoutWidDefault = 10.0;
/*public*/ /*static*/ /*final*/ double LayoutTurnout::xOverLongDefault = 30.0;   // DOUBLE_XOVER, RH_XOVER, LH_XOVER
/*public*/ /*static*/ /*final*/ double LayoutTurnout::xOverHWidDefault = 10.0;
/*public*/ /*static*/ /*final*/ double LayoutTurnout::xOverShortDefault = 10.0;

/**
 * constructor method
 */
/*public*/ LayoutTurnout::LayoutTurnout(QString id, int t, QPointF c, double rot, double xFactor, double yFactor, LayoutEditor* myPanel, int version)
{
 log = new Logger("LayoutTurnout");
 this->version = version;
 setObjectName(id);
 editLayoutTurnoutFrame = NULL;
 editOpen = false;
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
 blockB = NULL;
 blockC = NULL;
 blockD = NULL;

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
 hidden = false;
 disableWhenOccupied = false;
 center =  QPointF(50.0,50.0);
 dispB =  QPointF(20.0,0.0);
 dispC =  QPointF(20.0,10.0);
 linkedTurnoutName = ""; // name of the linked Turnout (as entered in tool)
 linkType = NO_LINK;
 popup = NULL;
// JCheckBoxMenuItem* disableItem = NULL;
// JCheckBoxMenuItem* disableWhenOccupiedItem = NULL;
 tools = NULL;
 circle = NULL;

 turnoutNameField = new JTextField(16);
 blockBNameField = new JTextField(16);
 blockCNameField = new JTextField(16);
 blockDNameField = new JTextField(16);
 stateBox = new QComboBox();
 hiddenBox = new QCheckBox(tr("Hide Turnout"));
 editOpen = false;
 additionalTurnout = new QCheckBox(tr("Use Two Physical Addresses"));
 editLayoutTurnoutFrame = NULL;
 blockNameField = new JTextField(16);
 connect(blockNameField, SIGNAL(textEdited(QString)), this, SLOT(on_blockNameField_textEdited(QString)));
 connect(blockBNameField, SIGNAL(textEdited(QString)), this, SLOT(on_blockBNameField_textEdited(QString)));
 connect(blockCNameField, SIGNAL(textEdited(QString)), this, SLOT(on_blockCNameField_textEdited(QString)));
 connect(blockDNameField, SIGNAL(textEdited(QString)), this, SLOT(on_blockDNameField_textEdited(QString)));

 needRedraw = false;
 needsBlockUpdate = false;
 active = true;
 editAdditionalMenu = new QVector<QObject*>();
 viewAdditionalMenu = new QVector<QObject*>();
 secondNamedTurnout = NULL;
 item = NULL;
 rects = NULL;
 signalAMastNamed = NULL; // Throat
 signalBMastNamed = NULL; // Continuing
 signalCMastNamed = NULL; // diverging
 signalDMastNamed = NULL; // single or double crossover only


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
     //.dispB.setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB.setX(layoutEditor->getTurnoutBX());
     dispB.setY(0.0);
     //dispC.setLocation(layoutEditor->getTurnoutCX(),-layoutEditor->getTurnoutWid());
     dispC.setX(layoutEditor->getTurnoutCX());
     dispC.setY(-(layoutEditor->getTurnoutWid()));
    }
    else if (type==RH_TURNOUT)
    {
     //.dispB.setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB.setX(layoutEditor->getTurnoutBX());
     dispB.setY(0.0);
     //dispC.setLocation(layoutEditor->getTurnoutCX(),layoutEditor->getTurnoutWid());
     dispC.setX(layoutEditor->getTurnoutCX());
     dispC.setY(layoutEditor->getTurnoutWid());
    }
    else if (type==WYE_TURNOUT)
    {
     //.dispB.setLocation(layoutEditor->getTurnoutBX(),0.5*layoutEditor->getTurnoutWid());
     dispB.setX(layoutEditor->getTurnoutBX());
     dispB.setY(0.5*layoutEditor->getTurnoutWid());
     //dispC.setLocation(layoutEditor->getTurnoutBX(),-0.5*layoutEditor->getTurnoutWid());
     dispC.setX(layoutEditor->getTurnoutBX());
     dispC.setY(-0.5*layoutEditor->getTurnoutWid());

    }
    else if (type==DOUBLE_XOVER)
    {
     //dispB.setLocation(layoutEditor->getXOverLong(),-layoutEditor->getXOverHWid());
     dispB.setX(layoutEditor->getXOverLong());
     dispB.setY(-(layoutEditor->getXOverHWid()));

     //dispC.setLocation(layoutEditor->getXOverLong(),layoutEditor->getXOverHWid());
     dispC.setX(layoutEditor->getXOverLong());
     dispC.setY(layoutEditor->getXOverHWid());

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
     dispB.setX(layoutEditor->getXOverShort());
     dispB.setY(-(layoutEditor->getXOverHWid()));
     //dispC.setLocation(layoutEditor->xOverLong(),layoutEditor->xOverHWid());
     dispC.setX(layoutEditor->getXOverLong());
     dispC.setY(layoutEditor->getXOverHWid());

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
     dispB.setX(layoutEditor->getXOverLong());
     dispB.setY(-(layoutEditor->getXOverHWid()));
     //dispC.setLocation(layoutEditor->xOverShort(),layoutEditor->xOverHWid());
     dispC.setX(layoutEditor->getXOverShort());
     dispC.setY(layoutEditor->getXOverHWid());

        blockB = NULL;
        blockBName = "";
        blockC = NULL;
        blockCName = "";
        blockD = NULL;
        blockDName = "";
    }
    rotateCoords(rot);
    // adjust size of new turnout
    QPointF pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
    pt =  QPointF(round(dispC.x()*xFactor),
                                    round(dispC.y()*yFactor));
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
    double x = (cosineAng*dispB.x()) - (sineAng*dispB.y());
    double y = (sineAng*dispB.x()) + (cosineAng*dispB.y());
    dispB = QPointF(x,y);
    x = (cosineAng*dispC.x()) - (sineAng*dispC.y());
    y = (sineAng*dispC.x()) + (cosineAng*dispC.y());
    dispC =  QPointF(x,y);
}

/*protected*/ QPointF LayoutTurnout::rotatePoint(QPointF p, double sineAng, double cosineAng)
{
 double cX = center.x();
 double cY = center.y();
 double x = cX + cosineAng * (p.x() - cX) - sineAng * (p.y() - cY);
 double y = cY + sineAng * (p.x() - cX) + cosineAng * (p.y() - cY);
 return  QPointF(x, y);
}

/**
 * Accessor methods
 */
/*public*/ int LayoutTurnout::getVersion() {
    return version;
}

/*public*/ void LayoutTurnout::setVersion(int v) {
    version = v;
}
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

/*public*/ QString LayoutTurnout::getSignalAMastName() {
        if (signalAMastNamed != NULL) {
            return signalAMastNamed->getName();
        }
        return "";
    }
/*public*/ QString LayoutTurnout::getSignalAMast() {return signalAMast;}
/*public*/ void LayoutTurnout::setSignalAMast(QString signalMast) {signalAMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalBMastName()
{
 if (signalBMastNamed != NULL)
 {
  return signalBMastNamed->getName();
 }
 return "";
}
/*public*/ QString LayoutTurnout::getSignalBMast() {return signalBMast;}
/*public*/ void LayoutTurnout::setSignalBMast(QString signalMast) {signalBMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalCMastName()
{
 if (signalCMastNamed != NULL)
 {
  return signalCMastNamed->getName();
 }
 return "";
}
/*public*/ QString LayoutTurnout::getSignalCMast() {return signalCMast;}
/*public*/ void LayoutTurnout::setSignalCMast(QString signalMast) {signalCMast = signalMast;}
/*public*/ QString LayoutTurnout::getSignalDMastName()
{
 if (signalDMastNamed != NULL)
 {
  return signalDMastNamed->getName();
 }
 return "";
}
/*public*/ QString LayoutTurnout::getSignalDMast() {return signalDMast;}
/*public*/ void LayoutTurnout::setSignalDMast(QString signalMast) {signalDMast = signalMast;}

/*public*/ QString LayoutTurnout::getSensorAName()
{
 if (sensorANamed != NULL) {
     return sensorANamed->getName();
 }
 return "";
}
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

/*public*/ QString LayoutTurnout::getSensorBName()
{
 if (sensorBNamed != NULL) {
     return sensorBNamed->getName();
 }
 return "";
}
/*public*/ void LayoutTurnout::setSensorB(QString sensorName)
{
 if(sensorName==NULL || sensorName==(""))
 {
  sensorBNamed=NULL;
  return;
 }

 Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
 if (sensor != NULL)
 {
  sensorBNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
 }
 else
 {
  sensorBNamed=NULL;
 }
}

/*public*/ QString LayoutTurnout::getSensorCName()
{
 if (sensorCNamed != NULL) {
     return sensorCNamed->getName();
 }
 return "";
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

/*public*/ QString LayoutTurnout::getSensorDName()
{
 if (sensorDNamed != NULL) {
     return sensorDNamed->getName();
 }
 return "";
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

/*public*/ Turnout* LayoutTurnout::getTurnout()
{
 if (namedTurnout==NULL)
 {
  // set physical turnout if possible and needed
  setTurnout(turnoutName); // turnoutName should be the name (system or user) of
  //	an existing physical turnout
  if (namedTurnout==NULL)
   return NULL;
 }
 return namedTurnout->getBean();
}

/*public*/ int LayoutTurnout::getContinuingSense() {return continuingSense;}

/*public*/ void LayoutTurnout::setTurnout(QString tName)
{
 if (namedTurnout!=NULL) deactivateTurnout();
 turnoutName = tName;
 Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                        getTurnout(turnoutName);
 if (turnout!=NULL)
 {
  namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutName, turnout);
  activateTurnout();
 }
 else
 {
  turnoutName = "";
  namedTurnout = NULL;
 }
}

/*public*/ Turnout* LayoutTurnout::getSecondTurnout()
{
 if (secondNamedTurnout==NULL)
 {
  // set physical turnout if possible and needed
  setSecondTurnout(secondTurnoutName);

  if (secondNamedTurnout==NULL)
  {
   return NULL;
  }
 }
 return secondNamedTurnout->getBean();
}

/*public*/ void LayoutTurnout::setSecondTurnout(QString tName)
{
 if(tName!=NULL && tName==(secondTurnoutName))
 {
  return;
 }

 if (secondNamedTurnout!=NULL) deactivateTurnout();
 QString oldSecondTurnoutName = secondTurnoutName;
 secondTurnoutName = tName;
 Turnout* turnout = NULL;
 if(tName!=NULL)
 {
  turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                        getTurnout(secondTurnoutName);
 }
 if (turnout!=NULL)
 {
  secondNamedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(secondTurnoutName, turnout);
        activateTurnout();
 }
 else
 {
  secondTurnoutName = "";
  secondNamedTurnout = NULL;
 }
 if ( (type == RH_TURNOUT) || (type ==LH_TURNOUT) || (type == WYE_TURNOUT) ){
  if(oldSecondTurnoutName!=NULL && oldSecondTurnoutName!=(""))
  {
   Turnout* oldTurnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                        getTurnout(oldSecondTurnoutName);
   LayoutTurnout* oldLinked = layoutEditor->findLayoutTurnoutByTurnoutName(oldTurnout->getSystemName());
   if(oldLinked==NULL)
    oldLinked = layoutEditor->findLayoutTurnoutByTurnoutName(oldTurnout->getUserName());
   if((oldLinked!=NULL) && oldLinked->getSecondTurnout()==getTurnout())
    oldLinked->setSecondTurnout(NULL);
  }
  if(turnout!=NULL)
  {
   LayoutTurnout* newLinked = layoutEditor->findLayoutTurnoutByTurnoutName(turnout->getSystemName());
   if(newLinked==NULL)
    newLinked = layoutEditor->findLayoutTurnoutByTurnoutName(turnout->getUserName());
   if(newLinked!=NULL)
   {
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

/*public*/ QObject* LayoutTurnout::getConnection(int location) throw (JmriException)
{
 switch (location)
 {
     case TURNOUT_A:
         return connectA;
     case TURNOUT_B:
         return connectB;
     case TURNOUT_C:
         return connectC;
     case TURNOUT_D:
         return connectD;
 }
 log->error("Invalid Point Type " + QString::number(location)); //I18IN
 throw new JmriException("Invalid Point");
}

/*public*/ void LayoutTurnout::setConnection(int location, QObject* o, int type) throw (JmriException)
{
    if ((type != TRACK) && (type != NONE)) {
        log->error("unexpected type of connection to layoutturnout - " + QString::number(type));
        throw JmriException("unexpected type of connection to layoutturnout - " + QString::number(type));
    }
    switch (location) {
        case TURNOUT_A:
            connectA = o;
            break;
        case TURNOUT_B:
            connectB = o;
            break;
        case TURNOUT_C:
            connectC = o;
            break;
        case TURNOUT_D:
            connectD = o;
            break;
        default:
            log->error("Invalid Point Type " + QString::number(location)); //I18IN
            throw JmriException("Invalid Point");
    }
}

/*public*/ void LayoutTurnout::setConnectA(QObject* o,int type)
{
 connectA = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of A connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectB(QObject* o,int type)
{
 connectB = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of B connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectC(QObject* o,int type)
{
 connectC = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of C connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectD(QObject* o,int type)
{
 connectD = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of D connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlock() {return block;}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockB()
{
 if (blockB!=NULL) return blockB;
 return block;
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockC()
{
 if (blockC!=NULL) return blockC;
 return block;
}
/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockD()
{
 if (blockD!=NULL) return blockD;
 return block;
}
/*public*/ QPointF LayoutTurnout::getCoordsCenter() {return center;}
/*public*/ QPointF LayoutTurnout::getCoordsA()
{
 if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) || (type==DOUBLE_SLIP) || (type==SINGLE_SLIP))
 {
  double x = center.x() - dispC.x();
  double y = center.y() - dispC.y();
  return  QPointF(x,y);
 }
 else if (type==WYE_TURNOUT)
 {
  double x = center.x() - (0.5*(dispB.x() + dispC.x()));
  double y = center.y() - (0.5*(dispB.y() + dispC.y()));
  return  QPointF(x,y);
 }
 else
 {
  double x = center.x() - dispB.x();
  double y = center.y() - dispB.y();
  return  QPointF(x,y);
 }
}
/*public*/ QPointF LayoutTurnout::getCoordsB()
{
 double x = center.x() + dispB.x();
 double y = center.y() + dispB.y();
 return  QPointF(x,y);
}
/*public*/ QPointF LayoutTurnout::getCoordsC()
{
 double x = center.x() + dispC.x();
 double y = center.y() + dispC.y();
 return  QPointF(x,y);
}
/*public*/ QPointF LayoutTurnout::getCoordsD()
{
 // only allowed for single and double crossovers
 double x = center.x() - dispB.x();
 double y = center.y() - dispB.y();
 return  QPointF(x,y);
}

// updates connectivity for blocks assigned to this turnout and connected track segments
/*private*/ void LayoutTurnout::updateBlockInfo()
{
 LayoutBlock* bA = NULL;
 LayoutBlock* bB = NULL;
 LayoutBlock* bC = NULL;
 LayoutBlock* bD = NULL;
 layoutEditor->auxTools->setBlockConnectivityChanged();
 if (block!=NULL) block->updatePaths();
 if (connectA!=NULL)
 {
  bA = ((TrackSegment*)connectA)->getLayoutBlock();
  if ((bA!=NULL) && (bA!=block)) bA->updatePaths();
 }
 if ((blockB!=NULL) && (blockB!=block) && (blockB!=bA)) blockB->updatePaths();
 if (connectB!=NULL)
 {
  bB = ((TrackSegment*)connectB)->getLayoutBlock();
  if ((bB!=NULL) && (bB!=block) && (bB!=bA) && (bB!=blockB)) bB->updatePaths();
 }
 if ((blockC!=NULL) && (blockC!=block) && (blockC!=bA) &&
         (blockC!=bB) && (blockC!=blockB)) blockC->updatePaths();
 if (connectC!=NULL)
 {
  bC = ((TrackSegment*)connectC)->getLayoutBlock();
  if ((bC!=NULL) && (bC!=block) && (bC!=bA) && (bC!=blockB) && (bC!=bB) &&
          (bC!=blockC)) bC->updatePaths();
 }
 if ((blockD!=NULL) && (blockD!=block) && (blockD!=bA) &&
         (blockD!=bB) && (blockD!=blockB) && (blockD!=bC) &&
             (blockD!=blockC)) blockD->updatePaths();
 if (connectD!=NULL)
 {
  bD = ((TrackSegment*)connectD)->getLayoutBlock();
  if ((bD!=NULL) && (bD!=block) && (bD!=bA) && (bD!=blockB) && (bD!=bB) &&
      (bD!=blockC) && (bD!=bC) && (bD!=blockD)) bD->updatePaths();
 }
}

/**
 * Set default size parameters to correspond to this turnout's size
 */
/*private*/ void LayoutTurnout::setUpDefaultSize()
{
 // remove the overall scale factor
 double bX = dispB.x()/layoutEditor->getXScale();
 double bY = dispB.y()/layoutEditor->getYScale();
 double cX = dispC.x()/layoutEditor->getXScale();
 double cY = dispC.y()/layoutEditor->getYScale();
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
        log->error ("Attempt to set block B, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockC (LayoutBlock* b) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockC = b;
        if (b!=NULL) blockCName = b->getID();
        else blockCName = "";
    }
    else {
        log->error ("Attempt to set block C, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockD (LayoutBlock* b) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockD = b;
        if (b!=NULL) blockDName = b->getID();
        else blockDName = "";
    }
    else {
        log->error ("Attempt to set block D, but not a crossover");
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
        log->error ("Attempt to set block B name, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockCByName (QString name) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockCName = name;
    }
    else {
        log->error ("Attempt to set block C name, but not a crossover");
    }
}
/*public*/ void LayoutTurnout::setLayoutBlockDByName (QString name) {
    if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
        blockDName = name;
    }
    else {
        log->error ("Attempt to set block D name, but not a crossover");
    }
}

/**
 * Methods to test if turnout legs are mainline track or not
 *  Returns true if connecting track segment is mainline
 *  Defaults to not mainline if connecting track segment is missing
 */
/*public*/ bool LayoutTurnout::isMainlineA() {
    if (connectA != NULL)
        return ((TrackSegment*)connectA)->getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is B
            if (connectB != NULL)
                return ((TrackSegment*)connectB)->getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat
        else if ( ((connectB != NULL) &&
                (((TrackSegment*)connectB)->getMainline())) ||
                    ((connectC != NULL) &&
                        (((TrackSegment*)connectC)->getMainline())) )
            return true;
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineB() {
    if (connectB != NULL)
        return ((TrackSegment*)connectB)->getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is A
            if (connectA != NULL)
                return ((TrackSegment*)connectA)->getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat,
        //		B is normally the continuing straight
        else if (continuingSense == Turnout::CLOSED) {
            // user hasn't changed the continuing turnout state
            if (connectA != NULL)
                // if throat is mainline, this leg must be also
                return ((TrackSegment*)connectA)->getMainline();
        }
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineC() {
    if (connectC != NULL)
        return ((TrackSegment*)connectC)->getMainline();
    else {
        // if no connection, depends on type of turnout
        if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) ) {
            // All crossovers - straight continuing is D
            if (connectD != NULL)
                return ((TrackSegment*)connectD)->getMainline();
        }
        // must be RH, LH, or WYE turnout - A is the switch throat,
        //		B is normally the continuing straight
        else if (continuingSense == Turnout::THROWN) {
            // user has changed the continuing turnout state
            if (connectA != NULL)
                // if throat is mainline, this leg must be also
                return ((TrackSegment*)connectA)->getMainline();
        }
    }
    return false;
}
/*public*/ bool LayoutTurnout::isMainlineD() {
    // this is a crossover turnout
    if (connectD != NULL)
        return ((TrackSegment*)connectD)->getMainline();
    else if (connectC != NULL)
        return ((TrackSegment*)connectC)->getMainline();
    return false;
}

/**
 * Modify coordinates methods
 */
/*public*/ void LayoutTurnout::setCoordsCenter(QPointF p) {
    center = p;
}
/*public*/ void LayoutTurnout::setCoordsA(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    if (type == DOUBLE_XOVER) {
        dispC =  QPointF(x,y);
        // adjust to maintain rectangle
        double oldLength =qSqrt( (dispB.x()*dispB.x()) +
                                                (dispB.y()*dispB.y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispB.x()*newLength/oldLength;
        y = dispB.y()*newLength/oldLength;
        dispB =  QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        dispC =  QPointF(x,y);
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB.x() + x)!=0.0) {
            a = (dispB.y() + y)/(dispB.x() + x);
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
        dispB =  QPointF(x,y);
    }
    else if (type == WYE_TURNOUT) {
        // modify both to maintain same angle at wye
        double temX = (dispB.x() + dispC.x());
        double temY = (dispB.y() + dispC.y());
        double temXx = (dispB.x() - dispC.x());
        double temYy = (dispB.y() - dispC.y());
        double tan =qSqrt( ((temX*temX)+(temY*temY))/
                            ((temXx*temXx)+(temYy*temYy)) );
        double xx = x + (y/tan);
        double yy = y - (x/tan);
        dispC =  QPointF(xx,yy);
        xx = x - (y/tan);
        yy = y + (x/tan);
        dispB =  QPointF(xx,yy);
    }
    else {
        dispB =  QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::setCoordsB(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(-x,-y);
    if ((type == DOUBLE_XOVER) || (type == WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength =qSqrt( (dispC.x()*dispC.x()) +
                                                (dispC.y()*dispC.y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispC.x()*newLength/oldLength;
        y = dispC.y()*newLength/oldLength;
        dispC =  QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispC.x() - x)!=0.0) {
            a = (dispC.y() - y)/(dispC.x() - x);
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
        dispC =  QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::setCoordsC(QPointF p) {
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispC =  QPointF(-x,-y);
    if ((type == DOUBLE_XOVER) || (type == WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength =qSqrt( (dispB.x()*dispB.x()) +
                                                (dispB.y()*dispB.y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispB.x()*newLength/oldLength;
        y = dispB.y()*newLength/oldLength;
        dispB =  QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB.x() + x)!=0.0) {
            a = (-dispB.y() + y)/(-dispB.x() + x);
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
        dispB =  QPointF(-x,-y);
    }
}
/*public*/ void LayoutTurnout::setCoordsD(QPointF p) {
    // only used for crossovers
    double x = center.x() - p.x();
    double y = center.y() - p.y();
    dispB =  QPointF(x,y);
    if (type == DOUBLE_XOVER) {
        // adjust to maintain rectangle
        double oldLength =qSqrt( (dispC.x()*dispC.x()) +
                                                (dispC.y()*dispC.y()) );
        double newLength =qSqrt( (x*x) + (y*y) );
        x = dispC.x()*newLength/oldLength;
        y = dispC.y()*newLength/oldLength;
        dispC =  QPointF(x,y);
    }
    else if ( (type == RH_XOVER) || (type == LH_XOVER) ) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispC.x() + x)!=0.0) {
            a = (dispC.y() + y)/(dispC.x() + x);
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
        dispC = QPointF(x,y);
    }
}
/*public*/ void LayoutTurnout::scaleCoords(float xFactor, float yFactor) {
    QPointF pt =  QPointF(round(center.x()*xFactor),
                                    round(center.y()*yFactor));
    center = pt;
    pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
    pt =  QPointF(round(dispC.x()*xFactor),
                                    round(dispC.y()*yFactor));
    dispC = pt;
}

/**
 * Activate/Deactivate turnout to redraw when turnout state changes
 */
/*private*/ void LayoutTurnout::activateTurnout()
{
 if (namedTurnout!=NULL)
 {
  //namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener =
//          new PropertyChangeListener(), namedTurnout->getName(),"Layout Editor Turnout");
//        {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                layoutEditor.redrawPanel();
//            }
//        }, namedTurnout.getName(), "Layout Editor Turnout");
  AbstractTurnout* t = (AbstractTurnout*)namedTurnout->getBean();
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(redrawPanel()));
 }
 if (secondNamedTurnout!=NULL)
 {
  secondNamedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener, secondNamedTurnout->getName(), "Layout Editor Turnout");
  connect(secondNamedTurnout->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(redrawPanel()));
 }
}
/*private*/ void LayoutTurnout::deactivateTurnout()
{
 if (mTurnoutListener!=NULL)
 {
  namedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
  if(secondNamedTurnout!=NULL)
  {
   secondNamedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
  }
  mTurnoutListener = NULL;
 }
}

/**
 * Toggle turnout if clicked on, physical turnout exists, and
 *    not disabled
 */
/*public*/ void LayoutTurnout::toggleTurnout()
{
 if ((getTurnout()!=NULL) && (!disabled))
 {
  if (disableWhenOccupied)
  {
   if(disableOccupiedTurnout())
   {
    log->debug("Turnout not changed as Block is Occupied");
    return;
   }
  }
  // toggle turnout
  int knownState = ((AbstractTurnout*)getTurnout())->getKnownState();
  Q_UNUSED(knownState);
  if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::CLOSED)
  {
   ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::THROWN);
   if(getSecondTurnout()!=NULL)
    ((AbstractTurnout*)getSecondTurnout())->setCommandedState(Turnout::THROWN);
  }
  else
  {
   ((AbstractTurnout*)getTurnout())->setCommandedState(Turnout::CLOSED);
   if(getSecondTurnout()!=NULL)
    ((AbstractTurnout*)getSecondTurnout())->setCommandedState(Turnout::CLOSED);
  }
 }
}

/*private*/ bool LayoutTurnout::disableOccupiedTurnout()
{
 if ((type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT))
 {
  if(block == NULL) return false;
  if(block->getOccupancy()==LayoutBlock::OCCUPIED)
  {
   log->debug("Block " + blockName + "is Occupied");
   return true;
  }
 }
 if ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER))
 {
  //If the turnout is set for straight over, we need to deal with the straight over connecting blocks
  if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::CLOSED)
  {
   if ((block->getOccupancy()==LayoutBlock::OCCUPIED) && (blockB->getOccupancy()==LayoutBlock::OCCUPIED))
   {
    log->debug("Blocks " + blockName + " & " + blockBName + " are Occupied");
    return true;
   }
   if ((blockC->getOccupancy()==LayoutBlock::OCCUPIED) && (blockD->getOccupancy()==LayoutBlock::OCCUPIED))
   {
    log->debug("Blocks " + blockCName + " & " + blockDName + " are Occupied");
    return true;
   }
  }
 }
 if ((type==DOUBLE_XOVER)||(type==LH_XOVER))
 {
  if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::THROWN)
  {
   if ((blockB->getOccupancy()==LayoutBlock::OCCUPIED) && (blockD->getOccupancy()==LayoutBlock::OCCUPIED))
   {
    log->debug("Blocks " + blockBName + " & " + blockDName + " are Occupied");
    return true;
   }
  }
 }

 if ((type==DOUBLE_XOVER)||(type==RH_XOVER))
 {
  if (((AbstractTurnout*)getTurnout())->getKnownState()==Turnout::THROWN)
  {
   if ((block->getOccupancy()==LayoutBlock::OCCUPIED) && (blockC->getOccupancy()==LayoutBlock::OCCUPIED))
   {
    log->debug("Blocks " + blockName + " & " + blockCName + " are Occupied");
    return true;
   }
  }
 }
 return false;
}


// initialization instance variables (used when loading a LayoutEditor)
//	public String connectAName = "";
//	public String connectBName = "";
//	public String connectCName = "";
//	public String connectDName = "";
//	public String tBlockName = "";
//	public String tBlockBName = "";
//	public String tBlockCName = "";
//	public String tBlockDName = "";
//	public String tTurnoutName = "";
//	public String tSecondTurnoutName = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void LayoutTurnout::setObjects(LayoutEditor* p)
{
 connectA = p->findTrackSegmentByName(connectAName);
 connectB = p->findTrackSegmentByName(connectBName);
 connectC = p->findTrackSegmentByName(connectCName);
 connectD = p->findTrackSegmentByName(connectDName);
 if (tBlockName.length()>0)
 {
  block = p->getLayoutBlock(tBlockName);
  if (block!=NULL)
  {
   blockName = tBlockName;
   block->incrementUse();
  }
  else
  {
   log->error("bad blockname '"+tBlockName+"' in layoutturnout "+ident);
  }
 }
 if (tBlockBName.length()>0)
 {
  blockB = p->getLayoutBlock(tBlockBName);
  if (blockB!=NULL)
  {
   blockBName = tBlockBName;
   if (block!=blockB) blockB->incrementUse();
  }
  else
  {
   log->error("bad blockname '"+tBlockBName+"' in layoutturnout "+ident);
  }
 }
 if (tBlockCName.length()>0)
 {
  blockC = p->getLayoutBlock(tBlockCName);
  if (blockC!=NULL)
  {
   blockCName = tBlockCName;
   if ( (block!=blockC) && (blockB!=blockC) ) blockC->incrementUse();
  }
  else
  {
   log->error("bad blockname '"+tBlockCName+"' in layoutturnout "+ident);
  }
 }
 if (tBlockDName.length()>0)
 {
  blockD = p->getLayoutBlock(tBlockDName);
  if (blockD!=NULL)
  {
   blockDName = tBlockDName;
   if ( (block!=blockD) && (blockB!=blockD) &&
                    (blockC!=blockD) ) blockD->incrementUse();
  }
  else
  {
   log->error("bad blockname '"+tBlockDName+"' in layoutturnout "+ident);
  }
 }
 //Do the second one first then the activate is only called the once
 if (tSecondTurnoutName.length()>0)
 {
  Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(tSecondTurnoutName);
  if (turnout!=NULL)
  {
   secondNamedTurnout =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(tSecondTurnoutName, turnout);
   secondTurnoutName = tSecondTurnoutName;
  }
  else
  {
   log->error("bad 2nd turnoutname '"+tSecondTurnoutName+"' in layoutturnout "+ident);
   secondTurnoutName = "";
   secondNamedTurnout = NULL;
  }
 }
 if (tTurnoutName.length()>0)
 {
  Turnout* turnout = NULL;
  ProxyTurnoutManager* mgr = (ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance();
  for(int i=0; i < mgr->nMgrs(); i++)
  {
   turnout = (Turnout*)mgr->getMgr(i)->getBeanBySystemName(tTurnoutName);
   if (turnout != NULL) break;
   turnout = (Turnout*)mgr->getMgr(i)->getBeanByUserName(tTurnoutName);
   if (turnout != NULL) break;
  }
  //Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
//                            getTurnout(tTurnoutName);
  if (turnout!=NULL)
  {
   namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(tTurnoutName, turnout);
   turnoutName = tTurnoutName;
   activateTurnout();
  }
  else
  {
   log->error("bad turnoutname '"+tTurnoutName+"' in layoutturnout "+ident);
   turnoutName = "";
   namedTurnout = NULL;
  }
 }
}

/**
 * Display popup menu for information and editing
 */
/*protected*/ void LayoutTurnout::showPopUp(QGraphicsSceneMouseEvent* /*e*/, bool editable)
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
    //popup.add(tr("RHTurnout"));
    actionRHTurnout = new QAction(tr("RHTurnout"), this);
    popup->addAction(actionRHTurnout);
    break;
   case LH_TURNOUT:
    //popup.add(tr("LHTurnout"));
    actionLHTurnout = new QAction(tr("LHTurnout"), this);
    popup->addAction(actionLHTurnout);
    break;
   case WYE_TURNOUT:
   //popup.add(tr("WYETurnout"));
    actionWYETurnout = new QAction(tr("WYETurnout"), this);
      popup->addAction(actionWYETurnout);
    break;
   case DOUBLE_XOVER:
    //popup.add(tr("XOverTurnout"));
    actionXOverTurnout = new QAction(tr("Double Crossover"), this);
      popup->addAction(actionXOverTurnout);
    break;
   case RH_XOVER:
    //popup.add(tr("RHXOverTurnout"));
    actionRHXOverTurnout = new QAction(tr("Right-Hand Crossover "), this);
    popup->addAction(actionRHXOverTurnout);
    break;
   case LH_XOVER:
    //popup.add(tr("LHXOverTurnout"));
    actionLHXOverTurnout = new QAction(tr("Left-Hand Crossover "), this);
    popup->addAction(actionLHXOverTurnout);
    break;
   default : break;
  }
  //popup.add(ident);
  actionIdent = new QAction(ident, this);
  popup->addAction(actionIdent);

  if (getTurnout()==NULL)
  {
   //popup.add(tr("NoTurnout"));
   actionNoTurnout = new QAction(tr("No Turnout set"), this);
   popup->addAction(actionNoTurnout);
  }
  else
  {
   //popup.add(tr("Turnout")+": "+turnoutName);
   actionNewTurnout = new QAction(QString("Turnout")+": "+turnoutName,this);
   popup->addAction(actionNewTurnout);
  }
#if 1 // TODO:
  // Rotate if there are no track connections
  if ( (connectA==NULL) && (connectB==NULL) &&
                (connectC==NULL) && (connectD==NULL) )
  {
//   JMenuItem rotateItem = new JMenuItem(tr("Rotate")+"...");
  QAction* rotateItem = new QAction(tr("Rotate..."),this);
  popup->addAction(rotateItem);
  connect(rotateItem, SIGNAL(triggered()), this, SLOT(on_rotateItemAction_triggered()));

//   rotateItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                bool entering = true;
//                bool error = false;
//                QString newAngle = "";
//                while (entering) {
//                    // prompt for rotation angle
//                    error = false;
//                    newAngle = JOptionPane.showInputDialog(layoutEditor,
//                                        tr("EnterRotation")+" :");
//                    if (newAngle.length()<1) return;  // cancelled
//                    double rot = 0.0;
//                    try {
//                        rot = Double.parseDouble(newAngle);
//                    }
//                    catch (Exception e) {
//                        JOptionPane.showMessageDialog(layoutEditor,tr("Error3")+
//                            " "+e,tr("Error"),JOptionPane.ERROR_MESSAGE);
//                        error = true;
//                        newAngle = "";
//                    }
//                    if (!error) {
//                        entering = false;
//                        if (rot!=0.0) {
//                           rotateCoords(rot);
//                           layoutEditor.redrawPanel();
//                        }
//                    }
//                }
//            }
//        });
  }




#endif
//  if (disableItem==NULL)
//   disableItem = new JCheckBoxMenuItem(tr("Disabled"));
//  disableItem.setSelected(disabled);
//  popup.add(disableItem);
//    disableItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                disabled = disableItem.isSelected();
//            }
//        });
  QAction* disableItemAct = new QAction(tr("Disabled"),this);
  disableItemAct->setCheckable(true);
  disableItemAct->setChecked(disabled);
  popup->addAction(disableItemAct);
  connect(disableItemAct, SIGNAL(toggled(bool)), this, SLOT(setDisabled(bool)));

//    if (disableWhenOccupiedItem==NULL)
//        disableWhenOccupiedItem = new JCheckBoxMenuItem(tr("DisabledWhenOccupied"));
//    disableWhenOccupiedItem.setSelected(disableWhenOccupied);
//    popup.add(disableWhenOccupiedItem);
//    disableWhenOccupiedItem.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                disableWhenOccupied = disableWhenOccupiedItem.isSelected();
//            }
//        });
  QAction* disableWhenOccupiedItemAct = new QAction(tr("Disable When Occupied"),this);
  disableWhenOccupiedItemAct->setCheckable(true);
  disableWhenOccupiedItemAct->setChecked(disableWhenOccupied);
  popup->addAction(disableWhenOccupiedItemAct);
  connect(disableWhenOccupiedItemAct, SIGNAL(toggled(bool)), this, SLOT(setDisableWhenOccupied(bool)));

  if (blockName==("")) popup->addAction(new QAction(tr("NoBlock"),this));
  else popup->addAction(new QAction(tr("Block: ")+getLayoutBlock()->getID(),this));
  if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) )
  {
   // check if extra blocks have been entered
   if (blockB!=NULL) popup->addAction(new QAction(tr("Block2ID")+": "+blockBName,this));
   if (blockC!=NULL) popup->addAction(new QAction(tr("Block3ID")+": "+blockCName,this));
   if (blockD!=NULL) popup->addAction(new QAction(tr("Block4ID")+": "+blockDName,this));
  }
  if (hidden) popup->addAction(new QAction(tr("Hidden"),this));
  else popup->addAction(new QAction(tr("Not Hidden"),this));
  popup->addSeparator();

//    popup.add(new AbstractAction(tr("UseSizeAsDefault")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                setUpDefaultSize();
//            }
//        });
  QAction* useSizeAsDefaultAction = new QAction("Use Size As Default",this);
  popup->addAction(useSizeAsDefaultAction);
  connect(useSizeAsDefaultAction, SIGNAL(triggered()), this, SLOT(setUpDefaultSize()));

//    popup.add(new AbstractAction(tr("Edit")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editLayoutTurnout();
//            }
//        });
  QAction* editAction = new QAction(tr("Edit"),this);
  popup->addAction(editAction);
  connect(editAction, SIGNAL(triggered()), this, SLOT(editLayoutTurnout()));

//    popup.add(new AbstractAction(tr("Remove")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (layoutEditor.removeLayoutTurnout(instance)) {
//                    // Returned true if user did not cancel
//                    remove();
//                    dispose();
//                }
//            }
//        });
  QAction* removeAction = new QAction(tr("Remove"),this);
  popup ->addAction(removeAction);
  connect(removeAction, SIGNAL(triggered()), this, SLOT(on_removeAction_triggered()));
  if (getTurnout()!=NULL)
  {
//        popup.add(new AbstractAction(tr("SetSignals")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                if (tools == NULL) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                if ( (getTurnoutType()==DOUBLE_XOVER) || (getTurnoutType()==RH_XOVER) ||
//                                        (getTurnoutType()==LH_XOVER) ) {
//                    tools.setSignalsAtXoverTurnoutFromMenu(instance,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//                else if (linkType==NO_LINK) {
//                    tools.setSignalsAtTurnoutFromMenu(instance,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//                else if (linkType==THROAT_TO_THROAT) {
//                    tools.setThroatToThroatFromMenu(instance,linkedTurnoutName,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//                else if (linkType==FIRST_3_WAY) {
//                    tools.set3WayFromMenu(turnoutName, linkedTurnoutName,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//                else if (linkType==SECOND_3_WAY) {
//                    tools.set3WayFromMenu(linkedTurnoutName, turnoutName,
//                        layoutEditor.signalIconEditor,layoutEditor.signalFrame);
//                }
//            }
//        });
   QAction* setSignals = new QAction(tr("Set Signals"),this);
   popup->addAction(setSignals);
   connect(setSignals, SIGNAL(triggered()), this, SLOT(on_setSignalsAct_triggered()));
  }

  if (blockName!=(""))
  {
   /*final*/ boundaryBetween = getBlockBoundaries().toVector();
   bool blockBoundaries = false;
   for (int i = 0; i<4; i++)
   {
    if(boundaryBetween.at(i)!="")
     blockBoundaries=true;
   }
//        if (InstanceManager::layoutBlockManagerInstance()->isAdvancedRoutingEnabled())
   if(layoutEditor->layoutBlockManager->isAdvancedRoutingEnabled())
   {

    if(blockBName==("") && blockCName==("") && blockDName==(""))
    {
     AbstractAction* viewBlockRouting;
     popup->addAction(viewBlockRouting =new AbstractAction(tr("View Block Routing"),this));
//     {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
//                        routeTableAction.actionPerformed(e);
//                    }
//                });
     connect(viewBlockRouting, SIGNAL(triggered()), this, SLOT(on_viewBlockRouting()));
     AbstractAction* viewRoutingAction = new AbstractAction("View Routing", this);
     popup->addAction(viewRoutingAction);
     connect(viewRoutingAction, SIGNAL(triggered()), viewRoutingAction, SLOT(actionPerformed()));
    }
    else
    {
     QMenu* viewRouting = new QMenu(tr("View Block Routing"));
     AbstractAction* viewRoutingAAct;
     viewRouting->addAction(viewRoutingAAct = new AbstractAction(blockName, this));
//     {
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockName, getLayoutBlock());
//                        routeTableAction.actionPerformed(e);
//                    }
//                });
     connect(viewRoutingAAct, SIGNAL(triggered()), this, SLOT(on_viewRoutingAAct()));
     QAction* viewRoutingActA = new QAction(blockName, this);
     connect(viewRoutingActA, SIGNAL(triggered()), this, SLOT(on_viewRoutingAct_triggered()));
     if(blockBName!=("") && blockBName!=(blockName))
     {
      AbstractAction* viewRoutingBAct;
      viewRouting->addAction(viewRoutingBAct = new AbstractAction(blockBName, this));
//      {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockBName, getLayoutBlockB());
//                            routeTableAction.actionPerformed(e);
//                        }
//                    });
      connect(viewRoutingBAct, SIGNAL(triggered()), this, SLOT(on_viewRoutingBAct()));
     }

     if(blockCName!=("") && blockCName!=(blockName) && blockCName!=(blockBName))
     {
      AbstractAction* viewRoutingCAct;
      viewRouting->addAction(viewRoutingCAct = new AbstractAction(blockCName,this));
//      {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockCName, getLayoutBlockC());
//                            routeTableAction.actionPerformed(e);
//                        }
//                    });
        connect(viewRoutingCAct, SIGNAL(triggered()), this, SLOT(on_viewRoutingCAct()));
     }

     if(blockDName!=("")  && blockDName!=(blockName) && blockDName!=(blockBName) && blockDName!=(blockCName))
     {
      AbstractAction* viewRoutingDAct;
      viewRouting->addAction(viewRoutingDAct = new AbstractAction(blockDName, this));
//      {
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            AbstractAction  routeTableAction = new  LayoutBlockRouteTableAction(blockDName, getLayoutBlockD());
//                            routeTableAction.actionPerformed(e);
//                        }
//                    });
       connect(viewRoutingDAct, SIGNAL(triggered()), this, SLOT(on_viewRoutingDAct()));
     }

     popup->addMenu(viewRouting);
    }
   }

   if (blockBoundaries)
   {
//            popup.add(new AbstractAction(tr("SetSignalMasts")) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (tools == NULL) {
//                        tools = new LayoutEditorTools(layoutEditor);
//                    }

//                    tools.setSignalMastsAtTurnoutFromMenu(instance,
//                    boundaryBetween);
//                }
//            });
   QAction* setSignalMastsAct = new QAction(tr("Set SignalMasts..."),this);
   connect(setSignalMastsAct, SIGNAL(triggered()), this, SLOT(on_setSignalMastsAct_triggered()));
   popup->addAction(setSignalMastsAct);
//            popup.add(new AbstractAction(tr("SetSensors")) {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    if (tools == NULL) {
//                        tools = new LayoutEditorTools(layoutEditor);
//                    }

//                    tools.setSensorsAtTurnoutFromMenu(instance,
//                    boundaryBetween, layoutEditor.sensorIconEditor, layoutEditor.sensorFrame);
//                }
//            });
   QAction* setSensorsAct = new QAction(tr("Set Sensors..."),this);
   popup->addAction(setSensorsAct);
   connect(setSensorsAct, SIGNAL(triggered()), this, SLOT(on_setSensorsAct_triggered()));}
  }
  setAdditionalEditPopUpMenu(popup);
//  layoutEditor.setShowAlignmentMenu(popup);
//  popup.show(e.getComponent(), e->x(), e->y());
  popup->exec(QCursor::pos());
 }
 else if(!viewAdditionalMenu->isEmpty())
 {
  setAdditionalViewPopUpMenu(popup);
  //popup.show(e.getComponent(), e->x(), e->y());
  popup->exec(QCursor::pos());
 }
}

void LayoutTurnout::on_viewBlockRouting()
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("View Routing", getLayoutBlock());
 routeTableAction->actionPerformed();
}
void LayoutTurnout::on_viewRoutingAAct()
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction(blockName, getLayoutBlock());
 routeTableAction->actionPerformed();
}

void LayoutTurnout::on_viewRoutingBAct()
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction(blockBName, getLayoutBlockB());
 routeTableAction->actionPerformed();
}

void LayoutTurnout::on_viewRoutingCAct()
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction(blockCName, getLayoutBlockC());
 routeTableAction->actionPerformed();
}
void LayoutTurnout::on_viewRoutingDAct()
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction(blockDName, getLayoutBlockC());
 routeTableAction->actionPerformed();
}

void LayoutTurnout::on_viewRoutingAct_triggered()
{
 LayoutBlockRouteTableAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
 routeTableAction->actionPerformed();
}

void LayoutTurnout::on_setSignalMastsAct_triggered()
{
 if (tools == NULL)
 {
   tools = new LayoutEditorTools(layoutEditor);
 }
 tools->setSignalMastsAtTurnoutFromMenu(instance,  boundaryBetween.toList());
}

void LayoutTurnout::on_setSensorsAct_triggered()
{
 if (tools == NULL) {
    tools = new LayoutEditorTools(layoutEditor);
 }

 tools->setSensorsAtTurnoutFromMenu(instance, boundaryBetween.toList(), layoutEditor->sensorIconEditor, layoutEditor->sensorFrame);
}

void LayoutTurnout::on_setSignalsAct_triggered()
{
 if (tools == NULL)
 {
  tools = new LayoutEditorTools(layoutEditor);
 }
 if ( (getTurnoutType()==DOUBLE_XOVER) || (getTurnoutType()==RH_XOVER) ||
                        (getTurnoutType()==LH_XOVER) )
 {
  tools->setSignalsAtXoverTurnoutFromMenu(instance,
        layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }
 else if (linkType==NO_LINK)
 {
  tools->setSignalsAtTurnoutFromMenu(instance,
        layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }
 else if (linkType==THROAT_TO_THROAT)
 {
  tools->setThroatToThroatFromMenu(instance,linkedTurnoutName,
        layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }
 else if (linkType==FIRST_3_WAY) {
    tools->set3WayFromMenu(turnoutName, linkedTurnoutName,
        layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }
 else if (linkType==SECOND_3_WAY) {
    tools->set3WayFromMenu(linkedTurnoutName, turnoutName,
        layoutEditor->signalIconEditor,layoutEditor->signalFrame);
 }
}

/*public*/ QStringList LayoutTurnout::getBlockBoundaries()
{
 ///*final*/ QStringList* boundaryBetween = new QStringList();
boundaryBetween = QVector<QString>(4);
 if ((type==WYE_TURNOUT) || (type ==RH_TURNOUT) || (type == LH_TURNOUT))
 {
  //This should only be needed where we are looking at a single turnout.
  if(block!=NULL)
  {
   LayoutBlock* aLBlock = NULL;
   LayoutBlock* bLBlock = NULL;
   LayoutBlock* cLBlock = NULL;
#if 1 //TODO
   //if (connectA instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectA)!= NULL)
   {
    aLBlock =((TrackSegment*)connectA)->getLayoutBlock();
    if(aLBlock!=block)
    {
     try
     {
      boundaryBetween.replace(0,aLBlock->getDisplayName()+ " - " + block->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
     }
    }
   }

   //if (connectB instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectB)!= NULL)
   {
    bLBlock =((TrackSegment*)connectB)->getLayoutBlock();
    if(bLBlock!=block)
    {
     try
     {
      boundaryBetween.replace(1,bLBlock->getDisplayName()+ " - " + block->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection B doesn't contain a layout block");
     }
    }
   }
   //if ((connectC instanceof TrackSegment) && (((TrackSegment)connectC).getLayoutBlock()!=block))
   if(qobject_cast<TrackSegment*>(connectC)!= NULL && (((TrackSegment*)connectC)->getLayoutBlock()!=block))
   {
    cLBlock = ((TrackSegment*)connectC)->getLayoutBlock();
    if(cLBlock!=block)
    {
//     try
//     {
      if(cLBlock != NULL)
      {
      boundaryBetween.replace(2,cLBlock->getDisplayName()+ " - " + block->getDisplayName());
      }
      else
//     }
//     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegment at connection C doesn't contain a layout block");
     }
    }
   }
  }
 }
 else
 {
  QVector<LayoutBlock*> localblks =  QVector<LayoutBlock*>();
  localblks.reserve(4);
  if(block!=NULL)
   localblks.append(block);
  if(blockB!=NULL)
   localblks.append(blockB);
  if(blockC!=NULL)
   localblks.append(blockC);
  if(blockD!=NULL)
   localblks.append(blockD);

  LayoutBlock* aLBlock = NULL;
  LayoutBlock* bLBlock = NULL;
  LayoutBlock* cLBlock = NULL;
  LayoutBlock* dLBlock = NULL;
  if(block!=NULL)
  {
   //if (connectA instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectA)!=NULL)
   {
    aLBlock =((TrackSegment*)connectA)->getLayoutBlock();
    if(aLBlock!=block)
    {
     if(aLBlock != NULL)
      boundaryBetween.replace(0,aLBlock->getDisplayName()+ " - " + block->getDisplayName());
     else      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
    }
    else if (block!=blockB)
    {
//     try
//     {
      if(blockB !=NULL)
      boundaryBetween.replace(0,block->getDisplayName()+ " - " + blockB->getDisplayName());
//     }
//     catch (NullPointerException e)
//     {
      else
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
//     }
    }
   }

//   if (connectB instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectB)!=NULL)
   {
    bLBlock =((TrackSegment*)connectB)->getLayoutBlock();

    if (bLBlock!=block && bLBlock!=blockB)
    {
     try
     {
      boundaryBetween.replace(1,bLBlock->getDisplayName()+ " - " + blockB->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if track segment hasn't yet been allocated a block
      log->debug("TrackSegement at connection B doesn't contain a layout block");
     }
    }
    else if (block!=blockB)
    {
     //This is an interal block on the turnout
//     try
//     {
      if(blockB!= NULL)
       boundaryBetween.replace(1,blockB->getDisplayName()+ " - " + block->getDisplayName());
//     }
//     catch (NullPointerException e)
//     {
      else
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
//     }
    }
   }
   //if (connectC instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectC)!=NULL)
   {
    cLBlock =((TrackSegment*)connectC)->getLayoutBlock();
    if (cLBlock!=block && cLBlock!=blockB && cLBlock!=blockC)
    {
     try
     {
      boundaryBetween.replace(2,cLBlock->getDisplayName()+ " - " + blockC->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection C doesn't contain a layout block");
     }
    }
    else if (blockC!=blockD)
    {
     //This is an interal block on the turnout
     try
     {
      boundaryBetween.replace(2,blockC->getDisplayName()+ " - " + blockD->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
     }
    }
   }
   //if (connectD instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectD)!=NULL)
   {
    dLBlock =((TrackSegment*)connectD)->getLayoutBlock();
    if (dLBlock!=block && dLBlock!=blockB && dLBlock!=blockC && dLBlock!=blockD)
    {
     try
     {
      boundaryBetween.replace(3,dLBlock->getDisplayName()+ " - " + blockD->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection C doesn't contain a layout block");
     }
    }
    else if (blockC!=blockD)
    {
     //This is an interal block on the turnout
     try
     {
      boundaryBetween.replace(3,blockD->getDisplayName()+ " - " + blockC->getDisplayName());
     }
     catch (NullPointerException e)
     {
      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
     }
    }
   }
#endif
  }
 }
 return boundaryBetween.toList();
}


/**
 * Edit a Layout Turnout
 */
/*protected*/ void LayoutTurnout::editLayoutTurnout()
{
// if(editLayoutTurnoutFrame == NULL)
// {
//  editLayoutTurnoutFrame = new EditTurnout(this,layoutEditor);
//  editOpen = true;
//  editLayoutTurnoutFrame->show();
//  editLayoutTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutTurnout", true);
//  editLayoutTurnoutFrame->setLocation(50,30);
// }
 if (editOpen)
 {
  editLayoutTurnoutFrame->setVisible(true);

  return;
 }
#if 1 // see EditTurnout for implementation:
 // Initialize if needed
 if (editLayoutTurnoutFrame == NULL)
 {
  editLayoutTurnoutFrame = new JmriJFrame( tr("Edit Turnout"), false, true );
  editLayoutTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutTurnout", true);
  editLayoutTurnoutFrame->setLocation(50,30);
//     Container contentPane = editLayoutTurnoutFrame.getContentPane();
//     contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
  QWidget* centralWidget = new QWidget();
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout(centralWidget);
  editLayoutTurnoutFrame->setCentralWidget(centralWidget);
  // setup turnout name
  QWidget* panel1 = new QWidget();
  //panel1.setLayout(new FlowLayout());
  FlowLayout* panel1Layout = new FlowLayout(panel1);
  QLabel* turnoutNameLabel = new QLabel( tr("Turnout")+" "+tr("Name") );
  panel1Layout->addWidget(turnoutNameLabel);
  panel1Layout->addWidget(turnoutNameField);
  turnoutNameField->setToolTip( tr("Edit turnout name to change the physical turnout linked to this panel turnout.") );
  centralWidgetLayout->addWidget(panel1);

  QWidget* panel1a = new QWidget();
  //panel1a.setLayout(new BoxLayout(panel1a, BoxLayout.Y_AXIS));
  QVBoxLayout* panel1aLayout = new QVBoxLayout(panel1a);
  secondTurnoutComboBox = new JmriBeanComboBox(InstanceManager::turnoutManagerInstance(), getSecondTurnout(), JmriBeanComboBox::DISPLAYNAME);
//  additionalTurnout.addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          if(additionalTurnout.isSelected()){
//              secondTurnoutLabel.setEnabled(true);
//              secondTurnoutComboBox.setEnabled(true);
//          } else  {
//              secondTurnoutLabel.setEnabled(false);
//              secondTurnoutComboBox.setEnabled(false);
//          }
//      }
//  });
  connect(additionalTurnout, SIGNAL(toggled(bool)), this, SLOT(on_additionalTurnout_toggled(bool)));
  if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) )
  {
   additionalTurnout->setText(tr("Throw Two Turnouts"));
  }
  panel1aLayout->addWidget(additionalTurnout);
  centralWidgetLayout->addWidget(panel1a);
  secondTurnoutLabel = new QLabel( tr("Supporting") + tr("Turnout")+" "+tr("Name") );
  secondTurnoutLabel->setEnabled(false);
  secondTurnoutComboBox->setEnabled(false);
  QWidget* panel1b = new QWidget();
  QHBoxLayout* panel1bLayout = new QHBoxLayout(panel1b);
  panel1bLayout->addWidget(secondTurnoutLabel);
  panel1bLayout->addWidget(secondTurnoutComboBox);
  centralWidgetLayout->addWidget(panel1b);


  // add continuing state choice, if not crossover
  if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) )
  {
   QWidget* panel3 = new QWidget();
   //panel3.setLayout(new FlowLayout());
   FlowLayout* panel3Layout = new FlowLayout(panel3);
   stateBox->clear();
   stateBox->addItem( ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText() );
   turnoutClosedIndex = 0;
   stateBox->addItem( ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText() );
   turnoutThrownIndex = 1;
   stateBox->setToolTip(tr("Select turnout state corresponding to continuing route."));
   panel3Layout->addWidget( new QLabel(tr("Continuing Route Turnout State")));
   panel3Layout->addWidget( stateBox);
   centralWidgetLayout->addWidget(panel3);
  }

  QWidget* panel33 = new QWidget();
  //panel33.setLayout(new FlowLayout());
  FlowLayout* panel33Layout = new FlowLayout(panel33);
  hiddenBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));
  panel33Layout->addWidget( hiddenBox);
  centralWidgetLayout->addWidget(panel33);

  // setup block name
  QGroupBox* panel2 = new QGroupBox();
  panel2->setTitle("Block");
  //panel2.setLayout(new FlowLayout());
  FlowLayout* panel2Layout = new FlowLayout(panel2);
  //QLabel* blockNameLabel = new QLabel( tr("Block: Name"));
  //panel2Layout->addWidget(blockNameLabel);
  panel2Layout->addWidget(blockNameField);
  blockNameField->setToolTip( tr("Edit block name to change the linked block. If new name, block will be created.") );
  panel2Layout->addWidget(turnoutEditBlock = new QPushButton(tr("Create/Edit")));
//  turnoutEditBlock.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent e) {
//          turnoutEditBlockPressed(e);
//      }
//              });
  connect(turnoutEditBlock, SIGNAL(clicked()), this, SLOT(turnoutEditBlockPressed()));
  centralWidgetLayout->addWidget(panel2);
  if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) )
  {
   QWidget* panel21 = new QWidget();
   //panel21.setLayout(new FlowLayout());
   FlowLayout* panel21Layout = new FlowLayout(panel21);
   QLabel* blockBNameLabel = new QLabel( tr("Block 2"));
   panel21Layout->addWidget(blockBNameLabel);
   panel21Layout->addWidget(blockBNameField);
   blockBNameField->setToolTip( tr("Edit this block name to change the block linked to second connecting point.") );
   centralWidgetLayout->addWidget(panel21);
   QWidget* panel22 = new QWidget();
   //panel22.setLayout(new FlowLayout());
   FlowLayout* panel22Layout = new FlowLayout(panel22);
   QLabel* blockCNameLabel = new JLabel( tr("Block 3"));
   panel22Layout->addWidget(blockCNameLabel);
   panel22Layout->addWidget(blockCNameField);
   blockCNameField->setToolTip( tr("Edit this block name to change the block linked to third connecting point.") );
   centralWidgetLayout->addWidget(panel22);

   QWidget* panel23 = new QWidget();
   //panel23.setLayout(new FlowLayout());
   FlowLayout* panel23Layout = new FlowLayout(panel23);
   QLabel* blockDNameLabel = new QLabel( tr("Block 4"));
   panel23Layout->addWidget(blockDNameLabel);
   panel23Layout->addWidget(blockDNameField);
   blockDNameField->setToolTip( tr("Edit this block name to change the block linked to fourth connecting point.") );
   centralWidgetLayout->addWidget(panel23);
  }
  // set up Edit Block, Done and Cancel buttons
  QWidget* panel5 = new QWidget();
  FlowLayout* panel5Layout = new FlowLayout(panel5);
  //panel5.setLayout(new FlowLayout());
  // Edit Block
  turnoutEditBlock->setToolTip(tr("Click here to create/edit information for the Block shown above."));
  // Done
  panel5Layout->addWidget(turnoutEditDone = new QPushButton(tr("Done")));
//  turnoutEditDone.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent e) {
//          turnoutEditDonePressed(e);
//      }
//  });
  connect(turnoutEditDone, SIGNAL(clicked()), this, SLOT(turnoutEditDonePressed()));
  turnoutEditDone->setToolTip(tr("Click Done to accept any changes made above and dismiss this dialog."));
  // Cancel
  panel5Layout->addWidget(turnoutEditCancel = new QPushButton(tr("Cancel")));
//  turnoutEditCancel.addActionListener(new ActionListener() {
//      public void actionPerformed(ActionEvent e) {
//          turnoutEditCancelPressed(e);
//      }
//  });
  connect(turnoutEditCancel, SIGNAL(clicked()), this, SLOT(turnoutEditCancelPressed()));
  turnoutEditCancel->setToolTip(tr("Click Cancel to dismiss this dialog without making changes."));
  centralWidgetLayout->addWidget(panel5);
 }

 hiddenBox->setChecked(hidden);

 // Set up for Edit
 blockNameField->setText(blockName);
 if ( (type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER) )
 {
  blockBNameField->setText(blockBName);
  blockCNameField->setText(blockCName);
  blockDNameField->setText(blockDName);
 }
 turnoutNameField->setText(turnoutName);


 if(secondNamedTurnout!=NULL)
 {
  additionalTurnout->setChecked(true);
  secondTurnoutLabel->setEnabled(true);
  secondTurnoutComboBox->setEnabled(true);
 }

 if ( (type != DOUBLE_XOVER) && (type != RH_XOVER) && (type != LH_XOVER) )
 {
  if (continuingSense==Turnout::CLOSED) {
      stateBox->setCurrentIndex(turnoutClosedIndex);
  }
  else
  {
   stateBox->setCurrentIndex(turnoutThrownIndex);
  }
 }

// editLayoutTurnoutFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//         /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//             turnoutEditCancelPressed(NULL);
//         }
//     });
 editLayoutTurnoutFrame->addWindowListener(new ETWindowListener(this));
 editLayoutTurnoutFrame->adjustSize();
 editLayoutTurnoutFrame->setVisible(true);
 editOpen = true;
 needsBlockUpdate = false;
#endif
}

ETWindowListener::ETWindowListener(LayoutTurnout *parent)
{
 this->parent = parent;
}

void ETWindowListener::windowClosing(QCloseEvent*)
{
 parent->turnoutEditCancelPressed();
}

void LayoutTurnout::on_additionalTurnout_toggled(bool)
{
 if(additionalTurnout->isChecked())
 {
  secondTurnoutLabel->setEnabled(true);
  secondTurnoutComboBox->setEnabled(true);
 } else
 {
  secondTurnoutLabel->setEnabled(false);
  secondTurnoutComboBox->setEnabled(false);
 }
}

void LayoutTurnout::turnoutEditBlockPressed(ActionEvent* a)
{
 // check if a block name has been entered
 if (blockName!=(blockNameField->text().trimmed()))
 {
  // block has changed, if old block exists, decrement use
  if ((block != NULL) && (block != blockB) && (block != blockC)
          && (block != blockD))
  {
   block->decrementUse();
  }
  // get new block, or NULL if block has been removed
  blockName = blockNameField->text().trimmed();
  block = layoutEditor->provideLayoutBlock(blockName);
  if (block == NULL)
  {
   blockName = "";
  }
  // decrement use if block was already counted
  if ((block != NULL) && ((block == blockB) || (block == blockC)
          || (block == blockD)))
  {
   block->decrementUse();
  }
  needRedraw = true;
  needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (block == NULL)
 {
//     JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//             rb.getString("Error1"),
//             rb.getString("Error"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(editLayoutTurnoutFrame, tr("Error"),tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
     return;
 }
 block->editLayoutBlock(editLayoutTurnoutFrame);
 needRedraw = true;
 layoutEditor->setDirty();
}

void LayoutTurnout::turnoutEditBlockBPressed(ActionEvent* a)
{
 // check if a block name has been entered
 if (blockBName != (blockBNameField->text().trimmed()))
 {
  // block has changed, if old block exists, decrement use
  if ((blockB != NULL) && (block != blockB) && (blockB != blockC)
          && (blockB != blockD)) {
      blockB->decrementUse();
  }
  // get new block, or NULL if block has been removed
  blockBName = blockBNameField->text().trimmed();
  blockB = layoutEditor->provideLayoutBlock(blockBName);
  if (blockB == NULL) {
      blockBName = "";
  }
  // decrement use if block was already counted
  if ((blockB != NULL) && ((block == blockB) || (blockB == blockC)
          || (blockB == blockD))) {
      blockB->decrementUse();
  }
  needRedraw = true;
  needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (blockB == NULL) {
//     JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//             rb.getString("Error1"),
//             rb.getString("Error"), JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(editLayoutTurnoutFrame, tr("Error"),tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
     return;
 }
 blockB->editLayoutBlock(editLayoutTurnoutFrame);
 needRedraw = true;
 layoutEditor->setDirty();
}

void LayoutTurnout::turnoutEditBlockCPressed(ActionEvent* a) {
    // check if a block name has been entered
    if (blockCName != (blockCNameField->text().trimmed())) {
        // block has changed, if old block exists, decrement use
        if ((blockC != NULL) && (block != blockC) && (blockB != blockC)
                && (blockC != blockD)) {
            blockC->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockCName = blockCNameField->text().trimmed();
        blockC = layoutEditor->provideLayoutBlock(blockCName);
        if (blockC == NULL) {
            blockCName = "";
        }
        // decrement use if block was already counted
        if ((blockC != NULL) && ((block == blockC) || (blockB == blockC)
                || (blockC == blockD))) {
            blockD->decrementUse();
        }
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockC == NULL) {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getString("Error1"),
//                rb.getString("Error"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(editLayoutTurnoutFrame, tr("Error"),tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
     return;
    }
    blockC->editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor->setDirty();
}

void LayoutTurnout::turnoutEditBlockDPressed(ActionEvent* a) {
    // check if a block name has been entered
    if (blockDName!=(blockDNameField->text().trimmed())) {
        // block has changed, if old block exists, decrement use
        if ((blockD != NULL) && (block != blockD) && (blockB != blockD)
                && (blockC != blockD)) {
            blockD->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockDName = blockDNameField->text().trimmed();
        blockD = layoutEditor->provideLayoutBlock(blockDName);
        if (blockD == NULL) {
            blockDName = "";
        }
        // decrement use if block was already counted
        if ((blockD != NULL) && ((block == blockD) || (blockB == blockD)
                || (blockC == blockD))) {
            blockD->decrementUse();
        }
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockD == NULL) {
//        JOptionPane.showMessageDialog(editLayoutTurnoutFrame,
//                rb.getString("Error1"),
//                rb.getString("Error"), JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(editLayoutTurnoutFrame, tr("Error"),tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."));
        return;
    }
    blockD->editLayoutBlock(editLayoutTurnoutFrame);
    needRedraw = true;
    layoutEditor->setDirty();
}

void LayoutTurnout::turnoutEditDonePressed(ActionEvent* a) {
    // check if Turnout changed
    if (turnoutName!=(turnoutNameField->text().trimmed())) {
        // turnout has changed
        QString newName = turnoutNameField->text().trimmed();
        if (layoutEditor->validatePhysicalTurnout(newName,
                editLayoutTurnoutFrame)) {
            setTurnout(newName);
        } else {
            namedTurnout = NULL;
            turnoutName = "";
            turnoutNameField->setText("");
        }
        needRedraw = true;
    }

    if (additionalTurnout->isChecked()) {
        if (secondTurnoutName!=(secondTurnoutComboBox->currentText())) {
            if ((type == DOUBLE_XOVER) || (type == RH_XOVER) || (type == LH_XOVER)) {
                // turnout has changed
                QString newName = secondTurnoutComboBox->currentText();
                if (layoutEditor->validatePhysicalTurnout(newName,
                        editLayoutTurnoutFrame)) {
                    setSecondTurnout(newName);
                } else {
                    additionalTurnout->setChecked(false);
                    secondNamedTurnout = NULL;
                    secondTurnoutName = "";
                    //secondTurnoutNameField.setText("");
                }
                needRedraw = true;
            } else {
                setSecondTurnout(secondTurnoutComboBox->currentText());
            }
        }
    } else {
        setSecondTurnout(NULL);
    }
    // set the continuing route Turnout State
    if ((type == RH_TURNOUT) || (type == LH_TURNOUT) || (type == WYE_TURNOUT)) {
        continuingSense = Turnout::CLOSED;
        if (stateBox->currentIndex() == turnoutThrownIndex) {
            continuingSense = Turnout::THROWN;
        }
    }
    // check if Block changed
    if (blockName!=(blockNameField->text().trimmed())) {
        // block has changed, if old block exists, decrement use
        if ((block != NULL) && (block != blockB) && (block != blockC)
                && (block != blockD)) {
            block->decrementUse();
        }
        // get new block, or NULL if block has been removed
        blockName = blockNameField->text().trimmed();
        block = layoutEditor->provideLayoutBlock(blockName);
        if (block == NULL) {
            blockName = "";
        }
        // decrement use if block was already counted
        if ((block != NULL) && ((block == blockB) || (block == blockC)
                || (block == blockD))) {
            block->decrementUse();
        }
        needRedraw = true;
        needsBlockUpdate = true;
    }
    if ((type == DOUBLE_XOVER) || (type == LH_XOVER) || (type == RH_XOVER)) {
        // check if Block 2 changed
        if (blockBName!=(blockBNameField->text().trimmed())) {
            // block has changed, if old block exists, decrement use
            if ((blockB != NULL) && (block != blockB) && (blockB != blockC)
                    && (blockB != blockD)) {
                blockB->decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockBName = blockBNameField->text().trimmed();
            blockB = layoutEditor->provideLayoutBlock(blockBName);
            if (blockB == NULL) {
                blockBName = "";
            }
            // decrement use if block was already counted
            if ((blockB != NULL) && ((block == blockB) || (blockB == blockC)
                    || (blockB == blockD))) {
                blockB->decrementUse();
            }
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 3 changed
        if (blockCName!=(blockCNameField->text().trimmed())) {
            // block has changed, if old block exists, decrement use
            if ((blockC != NULL) && (block != blockC) && (blockB != blockC)
                    && (blockC != blockD)) {
                blockC->decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockCName = blockCNameField->text().trimmed();
            blockC = layoutEditor->provideLayoutBlock(blockCName);
            if (blockC == NULL) {
                blockCName = "";
            }

            // decrement use if block was already counted
            if ((blockC != NULL) && ((block == blockC) || (blockB == blockC)
                    || (blockC == blockD))) {
                blockC->decrementUse();
            }
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 4 changed
        if (blockDName!=(blockDNameField->text().trimmed())) {
            // block has changed, if old block exists, decrement use
            if ((blockD != NULL) && (block != blockD) && (blockB != blockD)
                    && (blockC != blockD)) {
                blockD->decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockDName = blockDNameField->text().trimmed();
            blockD = layoutEditor->provideLayoutBlock(blockDName);
            if (blockD == NULL) {
                blockDName = "";
            }
            // decrement use if block was already counted
            if ((blockD != NULL) && ((block == blockD) || (blockB == blockD)
                    || (blockC == blockD))) {
                blockD->decrementUse();
            }
            needRedraw = true;
            needsBlockUpdate = true;
        }
    }
    // set hidden
    bool oldHidden = hidden;
    hidden = hiddenBox->isChecked();
    if (oldHidden != hidden) {
        needRedraw = true;
    }
    editOpen = false;
    editLayoutTurnoutFrame->setVisible(false);
    editLayoutTurnoutFrame->dispose();
    editLayoutTurnoutFrame = NULL;
    if (needsBlockUpdate) {
        updateBlockInfo();
        reCheckBlockBoundary();
    }
    if (needRedraw) {
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

void LayoutTurnout::turnoutEditCancelPressed(ActionEvent* a) {
    editOpen = false;
    editLayoutTurnoutFrame->setVisible(false);
    editLayoutTurnoutFrame->dispose();
    editLayoutTurnoutFrame = NULL;
    if (needsBlockUpdate) {
        updateBlockInfo();
    }
    if (needRedraw) {
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

void LayoutTurnout::on_blockNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
 blockNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockBNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
 blockBNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockCNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
 blockCNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockDNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = InstanceManager::blockManagerInstance()->getCompleter(text)) != NULL)
 blockDNameField->setCompleter(completer);
}

/*public*/ void LayoutTurnout::reCheckBlockBoundary()
{
 if(connectA==NULL && connectB==NULL && connectC==NULL)
 {
  if ((type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT))
  {
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

  }
  else if (((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER)) && connectD==NULL)
  {
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

 if(connectA==NULL || connectB==NULL || connectC==NULL)
 {
  //could still be in the process of rebuilding.
  return;
 }
 else if ((connectD == NULL) && ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER)))
 {
  //could still be in the process of rebuilding.
  return;
 }

 TrackSegment* trkA;
 TrackSegment* trkB;
 TrackSegment* trkC;
 TrackSegment* trkD;

//    if(connectA instanceof TrackSegment){
 if(qobject_cast<TrackSegment*>(connectA)!= NULL)
 {
  trkA = (TrackSegment*)connectA;
  if(trkA->getLayoutBlock()==block)
  {
   signalAMast = "";
   sensorANamed=NULL;
   if(!(getSignalAMast()==("")))
   removeSML(getSignalAMast());
  }
 }
//    if(connectB instanceof TrackSegment){
 if(qobject_cast<TrackSegment*>(connectB)!= NULL)
 {
  trkB = (TrackSegment*)connectB;
  if(trkB->getLayoutBlock()==block || trkB->getLayoutBlock()==blockB)
  {
   signalBMast = "";
   sensorBNamed=NULL;
   if(!(getSignalBMast()==("")))
    removeSML(getSignalBMast());
  }
 }
//    if(connectC instanceof TrackSegment) {
 if(qobject_cast<TrackSegment*>(connectC)!= NULL)
 {
  trkC = (TrackSegment*)connectC;
  if(trkC->getLayoutBlock()==block || trkC->getLayoutBlock()==blockB || trkC->getLayoutBlock()==blockC)
  {
   signalCMast = "";
   sensorCNamed=NULL;
   if(!(getSignalCMast()==("")))
    removeSML(getSignalCMast());
  }
 }
//    if(connectD!=NULL && connectD instanceof TrackSegment && ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER))){
 if(connectD != NULL && qobject_cast<TrackSegment*>(connectD)!= NULL && ((type==DOUBLE_XOVER)||(type==RH_XOVER)||(type==LH_XOVER)))
 {
  trkD = (TrackSegment*)connectD;
  if(trkD->getLayoutBlock()==block || trkD->getLayoutBlock()==blockB || trkD->getLayoutBlock()==blockC || trkD->getLayoutBlock()==blockD)
  {
   signalDMast = "";
   sensorDNamed=NULL;
   if(!(getSignalDMast()==("")))
    removeSML(getSignalDMast());
  }
 }
}

void LayoutTurnout::removeSML(QString signalMast){
#if 1
    if(signalMast==NULL || signalMast==(""))
        return;
    SignalMast* mast = InstanceManager::signalMastManagerInstance()->getSignalMast(signalMast);
    if(InstanceManager::layoutBlockManagerInstance()->isAdvancedRoutingEnabled() && InstanceManager::signalMastLogicManagerInstance()->isSignalMastUsed(mast)){
        SignallingGuiTools::removeSignalMastLogic(NULL, mast);
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
void LayoutTurnout::remove()
{
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


/*public*/ void LayoutTurnout::addEditPopUpMenu(QObject* menu)
{
 if(!editAdditionalMenu->contains(menu))
 {
  editAdditionalMenu->append(menu);
 }
}

/*public*/ void LayoutTurnout::addViewPopUpMenu(QObject* menu){
    if(!viewAdditionalMenu->contains(menu)){
        viewAdditionalMenu->append(menu);
    }
}

/*public*/ void LayoutTurnout::setAdditionalEditPopUpMenu(QMenu* popup)
{
 if(editAdditionalMenu->isEmpty())
  return;
 popup->addSeparator();
 foreach(QObject* mi, *editAdditionalMenu)
 {
  if(qobject_cast<QAction*>(mi)!= NULL)
   popup->addAction((QAction*)mi);
  else
   popup->addMenu((QMenu*)mi);
 }
}

/*public*/ void LayoutTurnout::setAdditionalViewPopUpMenu(QMenu* popup)
{
 if(viewAdditionalMenu->isEmpty())
  return;
 popup->addSeparator();
 foreach(QObject* mi, *viewAdditionalMenu)
 {
  if(qobject_cast<QAction*>(mi)!= NULL)
   popup->addAction((QAction*)mi);
  else
   popup->addMenu((QMenu*)mi);
 }
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutTurnout.class.getName());

//}
void LayoutTurnout::on_removeAction_triggered() // [slot]
{
 if(layoutEditor->removeLayoutTurnout(this))
 {
  remove();
  dispose();
 }
}
void LayoutTurnout::on_rotateItemAction_triggered()
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
void LayoutTurnout::invalidate(QGraphicsScene *g2)
{
 if(item != NULL && item->scene() != 0)
 {
  g2->removeItem(item);
  item = NULL;
 }
 if(rects != NULL && rects->scene() != 0)
 {
  Q_ASSERT(rects->scene()!=0);
  g2->removeItem(rects);
  rects = NULL;
 }
}
void LayoutTurnout::drawTurnouts(LayoutEditor *editor, QGraphicsScene *g2)
{
 QColor color;
 QGraphicsItemGroup* group = new QGraphicsItemGroup();
 LayoutBlock* b = getLayoutBlock();
 if (b!=NULL)
 {
  //g2.setColor(b->getBlockColor());
  color = b->getBlockColor();
 }
 else {
  //g2.setColor(defaultTrackColor);
  color = editor->defaultTrackColor;
 }
 if(!(getHidden() && !editor->isEditable()))
 {
  if (getTurnoutType()==LayoutTurnout::DOUBLE_XOVER)
  {
   //  double crossover turnout
   Turnout* t1 = getTurnout();
   if (t1==NULL)
   {
    // no physical turnout linked - draw A corner
    editor->setTrackStrokeWidth(isMainlineA());
   //g2.draw(new Line2D.Double(t.getCoordsA(),
//                                  midpoint(t.getCoordsA(),t.getCoordsB())));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
    line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line1);
    group->addToGroup(line1);

    editor->setTrackStrokeWidth(false);
//              g2.draw(new Line2D.Double(t.getCoordsA(),
//                                  midpoint(t.getCoordsA(),t.getCoordsC())));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->midpoint(getCoordsA(),getCoordsC())), 0);
    line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line2);
    group->addToGroup(line2);

    // change block if needed
    b = getLayoutBlockB();
    if (b!=NULL)
     //g2.setColor(b->getBlockColor());
     color = b->getBlockColor();
    else
    //g2.setColor(defaultTrackColor);
     color = editor->defaultTrackColor;
    // draw B corner
     editor->setTrackStrokeWidth(isMainlineB());
//              g2.draw(new Line2D.Double(t.getCoordsB(),
//                                  midpoint(t.getCoordsA(),t.getCoordsB())));
     QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
     line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line3);
     group->addToGroup(line3);

//              g2.draw(new Line2D.Double(t.getCoordsB(),
//                                  midpoint(t.getCoordsB(),t.getCoordsD())));
     QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->midpoint(getCoordsB(),getCoordsD())), 0);
     line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line4);
     group->addToGroup(line4);

    // change block if needed
     b = getLayoutBlockC();
    if (b!=NULL) color = b->getBlockColor();
    else color = editor->defaultTrackColor;
    // draw C corner
    editor->setTrackStrokeWidth(isMainlineC());
//              g2.draw(new Line2D.Double(t.getCoordsC(),
//                                  midpoint(t.getCoordsC(),t.getCoordsD())));
    QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
    line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line5);
    group->addToGroup(line5);
    editor->setTrackStrokeWidth(false);
//              g2.draw(new Line2D.Double(t.getCoordsC(),
//                                  midpoint(t.getCoordsA(),t.getCoordsC())));
    QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->midpoint(getCoordsA(),getCoordsC())), 0);
    line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line6);
    group->addToGroup(line6);

    // change block if needed
    b = getLayoutBlockD();
    if (b!=NULL) color = (b->getBlockColor());
    else color = (editor->defaultTrackColor);
    // draw D corner
    editor->setTrackStrokeWidth(isMainlineD());
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                          midpoint(t.getCoordsC(),t.getCoordsD())));
    QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
    line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line7);
    group->addToGroup(line7);

    editor->setTrackStrokeWidth(false);
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                          midpoint(t.getCoordsB(),t.getCoordsD())));
    QGraphicsLineItem* line8 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->midpoint(getCoordsB(),getCoordsD())), 0);
    line8->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line8);
    group->addToGroup(line8);

   }
   else {
    int state = Turnout::CLOSED;
    if (editor->animatingLayout)
     state = ((AbstractTurnout*)t1)->getKnownState();
    if ( state == Turnout::CLOSED )
    {
     // continuing path - not crossed over
     editor->setTrackStrokeWidth(isMainlineA());
//      g2.draw(new Line2D.Double(t.getCoordsA(),
//                              midpoint(t.getCoordsA(),t.getCoordsB())));
     QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
     line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line1);
     group->addToGroup(line1);

     editor->setTrackStrokeWidth(false);
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsA(),
//                              third(t.getCoordsA(),t.getCoordsC())));
     QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsC())), 0);
     line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line2);
     group->addToGroup(line2);

     b = getLayoutBlockB();
     if (b!=NULL) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineB());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              midpoint(t.getCoordsA(),t.getCoordsB())));
     QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
     line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line3);
     group->addToGroup(line3);
     editor->setTrackStrokeWidth(false);
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              third(t.getCoordsB(),t.getCoordsD())));
     QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsD())), 0);
     line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line4);
     group->addToGroup(line4);
     b = getLayoutBlockC();
     if (b!=NULL) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineC());
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              midpoint(t.getCoordsC(),t.getCoordsD())));
     QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
     line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line5);
     group->addToGroup(line5);

     editor->setTrackStrokeWidth(false);
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              third(t.getCoordsC(),t.getCoordsA())));
     QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsA())), 0);
     line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line6);
     group->addToGroup(line6);

     b = getLayoutBlockD();
     if (b!=NULL) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineD());
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                              midpoint(t.getCoordsC(),t.getCoordsD())));
     QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
     line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line7);
     group->addToGroup(line7);

     editor->setTrackStrokeWidth(false);
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                              third(t.getCoordsD(),t.getCoordsB())));
     QGraphicsLineItem* line8 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->third(getCoordsD(),getCoordsB())), 0);
     line8->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line8);
     group->addToGroup(line8);

  }
  else if (state == Turnout::THROWN)
  {
   // diverting (crossed) path
   if (b!=NULL) color=(b->getBlockTrackColor());
   editor->setTrackStrokeWidth(isMainlineA());
//  g2.draw(new Line2D.Double(t.getCoordsA(),
//                          third(t.getCoordsA(),t.getCoordsB())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsB())), 0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);

   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockColor());
//  g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),getCoordsCenter()), 0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);

   b = getLayoutBlockB();
   if (b!=NULL) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineB());
//  g2.draw(new Line2D.Double(t.getCoordsB(),
//                          third(t.getCoordsB(),t.getCoordsA())));
   QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsA())), 0);
   line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line3);
   group->addToGroup(line3);
   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockColor());

//  g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),getCoordsCenter()), 0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);

   b = getLayoutBlockC();
   if (b!=NULL) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineC());
//  g2.draw(new Line2D.Double(t.getCoordsC(),
//                          third(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsD())), 0);
   line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line5);
   group->addToGroup(line5);

   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockColor());
//  g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
   QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),getCoordsCenter()), 0);
   line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line6);
   group->addToGroup(line6);

   b = getLayoutBlockD();

   if (b!=NULL) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineD());
//  g2.draw(new Line2D.Double(t.getCoordsD(),
//                          third(t.getCoordsD(),t.getCoordsC())));
   QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->third(getCoordsD(),getCoordsC())), 0);
   line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line7);
   group->addToGroup(line7);
   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockColor());
//  g2.draw(new Line2D.Double(t.getCoordsD(),t.getCoordsCenter()));
   QGraphicsLineItem* line8 = new QGraphicsLineItem(QLineF(getCoordsD(),getCoordsCenter()), 0);
   line8->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line8);
   group->addToGroup(line8);
  }
  else
  {
   // unknown or inconsistent
   editor->setTrackStrokeWidth(isMainlineA());
//   g2.draw(new Line2D.Double(t.getCoordsA(),
//                              third(t.getCoordsA(),t.getCoordsB())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsB())), 0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);

   editor->setTrackStrokeWidth(false);
//   g2.draw(new Line2D.Double(t.getCoordsA(),
//                              third(t.getCoordsA(),t.getCoordsC())));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsC())), 0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);

   b = getLayoutBlockB();
   if (b!=NULL) color=(b->getBlockColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineB());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              third(t.getCoordsB(),t.getCoordsA())));
   QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsA())), 0);
   line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line3);
   group->addToGroup(line3);

   editor->setTrackStrokeWidth(false);
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              third(t.getCoordsB(),t.getCoordsD())));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsD())), 0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);

   b = getLayoutBlockC();
   if (b!=NULL) color=(b->getBlockColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineC());
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              third(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsD())), 0);
   line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line5);
   group->addToGroup(line5);

   editor->setTrackStrokeWidth(false);
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              third(t.getCoordsC(),t.getCoordsA())));
   QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsA())), 0);
   line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line6);
   group->addToGroup(line6);

   b = getLayoutBlockD();
   if (b!=NULL) color=(b->getBlockColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineD());
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                              third(t.getCoordsD(),t.getCoordsC())));
   QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->third(getCoordsD(),getCoordsC())), 0);
   line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line7);
   group->addToGroup(line7);

   editor->setTrackStrokeWidth(false);
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                                          third(t.getCoordsD(),t.getCoordsB())));
   QGraphicsLineItem* line8 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->third(getCoordsD(),getCoordsB())), 0);
   line8->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line8);
   group->addToGroup(line8);
   }
  }
 }
 else if ( (getTurnoutType()==LayoutTurnout::RH_XOVER) ||
                     (getTurnoutType()==LayoutTurnout::LH_XOVER) )
 {
  //  LH and RH crossover turnouts
  int ttype = getTurnoutType();
  Turnout* t1 = getTurnout();
  if (t1==NULL)
  {
   // no physical turnout linked - draw A corner
   editor->setTrackStrokeWidth(isMainlineA());
//      g2.draw(new Line2D.Double(t.getCoordsA(),
//                          midpoint(t.getCoordsA(),t.getCoordsB())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);

   if (ttype == LayoutTurnout::RH_XOVER)
   {
    editor->setTrackStrokeWidth(false);
//          g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),
//                                                  t.getCoordsCenter()));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsA(),getCoordsB()),getCoordsCenter()), 0);
    line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line2);
    group->addToGroup(line2);
   }
   // change block if needed
   b = getLayoutBlockB();
   if (b!=NULL) color=(b->getBlockColor());
   else color=(editor->defaultTrackColor);
     // draw B corner
   editor->setTrackStrokeWidth(isMainlineB());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                          midpoint(t.getCoordsA(),t.getCoordsB())));
   QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->midpoint( getCoordsA(),getCoordsB())),0);
   line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line3);
   group->addToGroup(line3);
   if (ttype == LayoutTurnout::LH_XOVER)
   {
    editor->setTrackStrokeWidth(false);
//          g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),                                                  t.getCoordsCenter()));
    QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsA(),getCoordsB()),getCoordsCenter()),0);
    //g2->addItem(line3);
    group->addToGroup(line3);
   }
   // change block if needed
   b = getLayoutBlockC();
   if (b!=NULL) color=(b->getBlockColor());
   else color=(editor->defaultTrackColor);
     // draw C corner
   editor->setTrackStrokeWidth(isMainlineC());
//   g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint( getCoordsC(),getCoordsD())),0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);

   if (ttype == LayoutTurnout::RH_XOVER)
   {
    editor->setTrackStrokeWidth(false);
//          g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()), t.getCoordsCenter()));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsC(),getCoordsD()), getCoordsCenter()),0);
    line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line1);
    group->addToGroup(line1);
   }
  // change block if needed
  b = getLayoutBlockD();
  if (b!=NULL) color=(b->getBlockColor());
  else color=(editor->defaultTrackColor);
  // draw D corner
  editor->setTrackStrokeWidth(isMainlineD());
//      g2.draw(new Line2D.Double(t.getCoordsD(), midpoint(t.getCoordsC(),t.getCoordsD())));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsD(), editor->midpoint( getCoordsC(),getCoordsD())),0);
  line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line2);
  group->addToGroup(line2);

  if (ttype == LayoutTurnout::LH_XOVER)
  {
   editor->setTrackStrokeWidth(false);
//          g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()), t.getCoordsCenter()));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsC(),getCoordsD()), getCoordsCenter()),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);
  }
 }
 else
 {
  int state = Turnout::CLOSED;
  if (editor->animatingLayout)
   state = ((AbstractTurnout*)t1)->getKnownState();
 if ( state == Turnout::CLOSED )
 {
  // continuing path - not crossed over
  editor->setTrackStrokeWidth(isMainlineA());
//    g2.draw(new Line2D.Double(t.getCoordsA(), midpoint(t.getCoordsA(),t.getCoordsB())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(), editor->midpoint(getCoordsA(),getCoordsB())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  if (ttype == LayoutTurnout::RH_XOVER)
  {
   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockTrackColor());
//              g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(), midpoint(t.getCoordsA(),t.getCoordsB()))));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);
  }
  b = getLayoutBlockB();
  if (b!=NULL) color=(b->getBlockColor());
  else color=(editor->defaultTrackColor);
  editor->setTrackStrokeWidth(isMainlineB());
//          g2.draw(new Line2D.Double(t.getCoordsB(), midpoint(t.getCoordsA(),t.getCoordsB())));
  QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->midpoint(getCoordsA(),getCoordsB())),0);
  line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line3);
  group->addToGroup(line3);

  if (ttype == LayoutTurnout::LH_XOVER)
  {
   editor->setTrackStrokeWidth(false);
   if (b!=NULL) color=(b->getBlockTrackColor());
//              g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);
  }
  b = getLayoutBlockC();
  if (b!=NULL) color=(b->getBlockColor());
  else color=(editor->defaultTrackColor);
  editor->setTrackStrokeWidth(isMainlineC());
//          g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsC(),t.getCoordsD())));
  QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsC(),getCoordsD())),0);
  line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line5);
  group->addToGroup(line5);
  if (ttype == LayoutTurnout::RH_XOVER) {
  editor->setTrackStrokeWidth(false);
  if (b!=NULL) color=(b->getBlockTrackColor());
//   g2.draw(new Line2D.Double(t.getCoordsCenter(),  third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
  QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsCenter(),  editor->third(getCoordsCenter(), editor->midpoint(getCoordsC(), getCoordsD()))),0);
  line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line6);
  group->addToGroup(line6);
 }
 b = getLayoutBlockD();
 if (b!=NULL) color=(b->getBlockColor());
 else color=(editor->defaultTrackColor);
 editor->setTrackStrokeWidth(isMainlineD());
//  g2.draw(new Line2D.Double(t.getCoordsD(),  midpoint(t.getCoordsC(),t.getCoordsD())));
 QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),  editor->midpoint(getCoordsC(),getCoordsD())),0);
 line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line7);
 group->addToGroup(line7);
 if (ttype == LayoutTurnout::LH_XOVER) {
 editor->setTrackStrokeWidth(false);
 if (b!=NULL) color=(b->getBlockTrackColor());
//  g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
 QGraphicsLineItem* line8 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsC(),getCoordsD()))),0);
 line8->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line8);
 group->addToGroup(line8);
}
}
else if (state == Turnout::THROWN)
{
// diverting (crossed) path
editor->setTrackStrokeWidth(isMainlineA());
if (ttype == LayoutTurnout::RH_XOVER)
{
//  g2.draw(new Line2D.Double(t.getCoordsA(), midpoint(t.getCoordsA(),t.getCoordsB())));
 QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(), editor->midpoint(getCoordsA(),getCoordsB())),0);
 line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line1);
 group->addToGroup(line1);
 editor->setTrackStrokeWidth(false);
//  g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()),  t.getCoordsCenter()));
 QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsA(),getCoordsB()),getCoordsCenter()),0);
 line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line2);
 group->addToGroup(line2);
}
 else if (ttype == LayoutTurnout::LH_XOVER)
 {
//  g2.draw(new Line2D.Double(t.getCoordsA(), fourth(t.getCoordsA(),t.getCoordsB())));
 QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsA(), editor->fourth(getCoordsA(),getCoordsB())),0);
line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line3);
 group->addToGroup(line3);
}
b = getLayoutBlockB();
if (b!=NULL) color=(b->getBlockColor());
else color=(editor->defaultTrackColor);
editor->setTrackStrokeWidth(isMainlineB());
if (ttype == LayoutTurnout::LH_XOVER)
{
//  g2.draw(new Line2D.Double(t.getCoordsB(),  midpoint(t.getCoordsB(),t.getCoordsA())));
 QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsB(),  editor->midpoint(getCoordsB(),getCoordsA())),0);
 //g2->addItem(line1);
 group->addToGroup(line1);
 editor->setTrackStrokeWidth(false);
//  g2.draw(new Line2D.Double(midpoint(t.getCoordsA(),t.getCoordsB()), t.getCoordsCenter()));
 QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsA(),getCoordsB()), getCoordsCenter()),0);
 line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line2);
 group->addToGroup(line2);
}
else if (ttype == LayoutTurnout::RH_XOVER)
{
//  g2.draw(new Line2D.Double(t.getCoordsB(), fourth(t.getCoordsB(),t.getCoordsA())));
 QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->fourth(getCoordsB(),getCoordsA())),0);
 line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line1);
 group->addToGroup(line1);
}
b = getLayoutBlockC();
if (b!=NULL) color=(b->getBlockColor());
else color=(editor->defaultTrackColor);
editor->setTrackStrokeWidth(isMainlineC());
if (ttype == LayoutTurnout::RH_XOVER)
{
//              g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsC(),t.getCoordsD())));
 QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsC(),getCoordsD())),0);
 line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line1);
 group->addToGroup(line1);
 editor->setTrackStrokeWidth(false);
//              g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()),t.getCoordsCenter()));
 QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsC(),getCoordsD()),getCoordsCenter()),0);
 line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line2);
 group->addToGroup(line2);
}
else if (ttype == LayoutTurnout::LH_XOVER)
{
//              g2.draw(new Line2D.Double(t.getCoordsC(),  fourth(t.getCoordsC(),t.getCoordsD())));
 QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(),  editor->fourth(getCoordsC(),getCoordsD())),0);
 line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line1);
 group->addToGroup(line1);
}
b = getLayoutBlockD();
if (b!=NULL) color=(b->getBlockColor());
else color=(editor->defaultTrackColor);
editor->setTrackStrokeWidth(isMainlineD());
if (ttype == LayoutTurnout::LH_XOVER)
 {
//              g2.draw(new Line2D.Double(t.getCoordsD(), midpoint(t.getCoordsD(),t.getCoordsC())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsD(), editor->midpoint(getCoordsD(),getCoordsC())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  editor->setTrackStrokeWidth(false);
// g2.draw(new Line2D.Double(midpoint(t.getCoordsC(),t.getCoordsD()), t.getCoordsCenter()));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(editor->midpoint(getCoordsC(),getCoordsD()), getCoordsCenter()),0);
  line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line2);
  group->addToGroup(line2);
 }
 else if (ttype == LayoutTurnout::RH_XOVER)
 {
// g2.draw(new Line2D.Double(t.getCoordsD(),fourth(t.getCoordsD(),t.getCoordsC())));
  QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->fourth(getCoordsD(),getCoordsC())),0);
  line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line3);
  group->addToGroup(line3);
 }
}
else
{
 // unknown or inconsistent
 editor->setTrackStrokeWidth(isMainlineA());
 if (ttype == LayoutTurnout::RH_XOVER)
 {
//              g2.draw(new Line2D.Double(t.getCoordsA(), midpoint(t.getCoordsA(),t.getCoordsB())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(), editor->midpoint(getCoordsA(),getCoordsB())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  editor->setTrackStrokeWidth(false);
// g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
  line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line2);
  group->addToGroup(line2);
 }
 else if (ttype == LayoutTurnout::LH_XOVER)
 {
// g2.draw(new Line2D.Double(t.getCoordsA(), fourth(t.getCoordsA(),t.getCoordsB())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(), editor->fourth(getCoordsA(),getCoordsB())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
 }
 b = getLayoutBlockB();
 if (b!=NULL) color=(b->getBlockColor());
 else color=(editor->defaultTrackColor);
 editor->setTrackStrokeWidth(isMainlineB());
 if (ttype == LayoutTurnout::LH_XOVER)
 {
// g2.draw(new Line2D.Double(t.getCoordsB(),  midpoint(t.getCoordsB(),t.getCoordsA())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsB(),  editor->midpoint(getCoordsB(),getCoordsA())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  editor->setTrackStrokeWidth(false);
//   g2.draw(new Line2D.Double(t.getCoordsCenter(),third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(),editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
  line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line2);
  group->addToGroup(line2);
 }
 else if (ttype == LayoutTurnout::RH_XOVER)
 {
//   g2.draw(new Line2D.Double(t.getCoordsB(), fourth(t.getCoordsB(),t.getCoordsA())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->fourth(getCoordsB(),getCoordsA())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
 }
 b = getLayoutBlockC();
 if (b!=NULL) color=(b->getBlockColor());
 else color=(editor->defaultTrackColor);
 editor->setTrackStrokeWidth(isMainlineC());
 if (ttype == LayoutTurnout::RH_XOVER)
 {
//   g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsC(),t.getCoordsD())));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsC(),getCoordsD())),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  editor->setTrackStrokeWidth(false);
//   g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsC(),getCoordsD()))),0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);
  }
  else if (ttype == LayoutTurnout::LH_XOVER)
  {
//   g2.draw(new Line2D.Double(t.getCoordsC(),  fourth(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(),  editor->fourth(getCoordsC(),getCoordsD())),0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);
  }
  b = getLayoutBlockD();
  if (b!=NULL) color=(b->getBlockColor());
  else color=(editor->defaultTrackColor);
  editor->setTrackStrokeWidth(isMainlineD());
  if (ttype == LayoutTurnout::LH_XOVER)
  {
//    g2.draw(new Line2D.Double(t.getCoordsD(), midpoint(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsD(), editor->midpoint(getCoordsC(),getCoordsD())),0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);
   editor->setTrackStrokeWidth(false);
//   g2.draw(new Line2D.Double(t.getCoordsCenter(),third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(),editor->third(getCoordsCenter(),editor->midpoint(getCoordsC(),getCoordsD()))),0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);
  }
  else if (ttype == LayoutTurnout::RH_XOVER)
  {
//   g2.draw(new Line2D.Double(t.getCoordsD(), fourth(t.getCoordsD(),t.getCoordsC())));
   QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsD(), editor->fourth(getCoordsD(),getCoordsC())),0);
   line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line3);
   group->addToGroup(line3);
  }
 }
}
}

else
{
 // LH, RH, or WYE Turnouts
 Turnout* t2 = getTurnout();
 if (t2==NULL)
 {
  // no physical turnout linked - draw connected
  editor->setTrackStrokeWidth(isMainlineA());
//   g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),getCoordsCenter()),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  editor->setTrackStrokeWidth(isMainlineB());
//   g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
  QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsB(),getCoordsCenter()),0);
  line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line2);
  group->addToGroup(line2);
  editor->setTrackStrokeWidth(isMainlineC());
//   g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
  QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsC(),getCoordsCenter()),0);
  line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line3);
  group->addToGroup(line3);
 }
 else
 {
  editor->setTrackStrokeWidth(isMainlineA());
  //line from throat to center
//   g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
  QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),getCoordsCenter()),0);
  line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line1);
  group->addToGroup(line1);
  int state = Turnout::CLOSED;
  if (editor->animatingLayout)
   state = ((AbstractTurnout*)t2)->getKnownState();
  switch (state)
  {
  case /*Turnout::CLOSED*/0x02:
   if (getContinuingSense()==Turnout::CLOSED)
   {
    editor->setTrackStrokeWidth(isMainlineB());
    //line from continuing leg to center
//     g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
    QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsB(),getCoordsCenter()),0);
    line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line2);
    group->addToGroup(line2);
    if (editor->turnoutDrawUnselectedLeg)
    {
     //line from diverging leg halfway to center
     editor->setTrackStrokeWidth(isMainlineC());
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsCenter(),t.getCoordsC())));
     QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsCenter(),getCoordsC())),0);
     line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line3);
     group->addToGroup(line3);
    }
   }
   else {
    editor->setTrackStrokeWidth(isMainlineC());
    //line from diverging leg to center
//     g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
    QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(),getCoordsCenter()),0);
    line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
    //g2->addItem(line1);
    group->addToGroup(line1);
    if (editor->turnoutDrawUnselectedLeg)
    {
     //line from continuing leg halfway to center
     editor->setTrackStrokeWidth(isMainlineB());
     if (b!=NULL) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsB(), midpoint(t.getCoordsCenter(),t.getCoordsB())));
     QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->midpoint(getCoordsCenter(),getCoordsB())),0);
     line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line2);
     group->addToGroup(line2);
    }
   }
   break;
  case /*Turnout::THROWN*/0x04:
      if (getContinuingSense()==Turnout::THROWN)
      {
         editor->setTrackStrokeWidth(isMainlineB());
//        g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
       QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsB(),getCoordsCenter()),0);
       line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
       //g2->addItem(line1);
       group->addToGroup(line1);
       if (editor->turnoutDrawUnselectedLeg)
       {
        editor->setTrackStrokeWidth(isMainlineC());
        if (b!=NULL) color=(b->getBlockTrackColor());
//         g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsCenter(),t.getCoordsC())));
        QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsCenter(),getCoordsC())),0);
        line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
        //g2->addItem(line2);
        group->addToGroup(line2);
       }
      }
      else {
       editor->setTrackStrokeWidth(isMainlineC());
//        g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
       QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(),getCoordsCenter()),0);
       line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
       //g2->addItem(line1);
       group->addToGroup(line1);
       if (editor->turnoutDrawUnselectedLeg)
       {
        editor->setTrackStrokeWidth(isMainlineB());
        if (b!=NULL) color=(b->getBlockTrackColor());
//         g2.draw(new Line2D.Double(t.getCoordsB(), midpoint(t.getCoordsCenter(),t.getCoordsB())));
        QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsB(), editor->midpoint(getCoordsCenter(),getCoordsB())),0);
        line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
        //g2->addItem(line2);
        group->addToGroup(line2);
       }
      }
      break;
     default:
      // inconsistent or unknown
      editor->setTrackStrokeWidth(isMainlineC());
//       g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsCenter(),t.getCoordsC())));
      QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsCenter(),getCoordsC())),0);
      line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
      //g2->addItem(line1);
      group->addToGroup(line1);
      editor->setTrackStrokeWidth(isMainlineB());
//      g2.draw(new Line2D.Double(t.getCoordsB(), midpoint(getCoordsCenter(),getCoordsB())));
     QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF( getCoordsB(), editor->midpoint(getCoordsCenter(),getCoordsB())),0);
     line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line2);
     group->addToGroup(line2);
    }
   }
  }
 }
 item = group;
 g2->addItem(item);
}
void LayoutTurnout::drawTurnoutRects(LayoutEditor *editor, QGraphicsScene *g2)
{
 QColor color;
 QGraphicsItemGroup* group = new QGraphicsItemGroup();

 QPointF pt = getCoordsCenter();
//      g2.setColor(turnoutCircleColor != NULL ? turnoutCircleColor : defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));

 QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pt.x()-LayoutEditor::SIZE2, pt.y()-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, 0);
 ellipse->setPen(QPen(editor->turnoutCircleColor.isValid() ? editor->turnoutCircleColor : editor->defaultTrackColor, 1, Qt::SolidLine ) );
 //g2->addItem(ellipse);
 group->addToGroup(ellipse);

 pt = getCoordsA();
 if (getConnectA()==NULL) {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem1 = new QGraphicsRectItem (QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem1->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem1);
 group->addToGroup(rectItem1);

 pt = getCoordsB();
 if (getConnectB()==NULL) {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem2 = new QGraphicsRectItem (QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem2->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem2);
 group->addToGroup(rectItem2);

 pt = getCoordsC();
 if (getConnectC()==NULL)
 {
  //g2.setColor(Color.red);
  color = QColor(Qt::red);
 }
 else
 {
  //g2.setColor(Color.green);
  color = QColor(Qt::green);
 }
 QGraphicsRectItem* rectItem3 = new QGraphicsRectItem (QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
 rectItem3->setPen(QPen(color, 1, Qt::SolidLine ) );
 //g2->addItem(rectItem3);
 group->addToGroup(rectItem3);

 if ( (getTurnoutType()==LayoutTurnout::DOUBLE_XOVER) ||
      (getTurnoutType()==LayoutTurnout::RH_XOVER) ||
      (getTurnoutType()==LayoutTurnout::LH_XOVER) ||
      (getTurnoutType() == LayoutTurnout::DOUBLE_SLIP) ||
      (getTurnoutType() == LayoutTurnout::SINGLE_SLIP)
    )
 {
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
  QGraphicsRectItem* rectItem4 = new QGraphicsRectItem (QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
  rectItem4->setPen(QPen(color, 1, Qt::SolidLine ) );
  //g2->addItem(rectItem4);
  group->addToGroup(rectItem4);
 }
 rects = group;
 g2->addItem(rects);
}

void LayoutTurnout::drawTurnoutCircles(LayoutEditor *editor, QGraphicsScene *g2)
{
 QPointF pt = getCoordsCenter();
 double size = LayoutEditor::SIZE * editor->turnoutCircleSize;
//          g2.setColor(turnoutCircleColor != NULL ? turnoutCircleColor : defaultTrackColor);
//          g2.draw(new Ellipse2D.Double (
//                          pt.x()-size, pt.y()-size, size+size, size+size));
 if(circle != NULL)
  g2->removeItem(circle);
 circle = new QGraphicsEllipseItem(pt.x()-size, pt.y()-size, size+size, size+size,0);
 circle->setPen( QPen( editor->turnoutCircleColor.isValid() ? editor->turnoutCircleColor : editor->defaultTrackColor, 1, Qt::SolidLine ) );
 g2->addItem(circle);
}

void LayoutTurnout::repaint(LayoutEditor *editor, QGraphicsScene *g2)
{
 invalidate(g2);
 drawTurnouts(editor, g2);
 if(editor->isEditable())
 {
  drawTurnoutRects(editor, g2);
 }
 else if(editor->turnoutCirclesWithoutEditMode)
 {
  drawTurnoutCircles(editor, g2);
 }
}
void LayoutTurnout::redrawPanel()
{
 layoutEditor->redrawPanel();
}

