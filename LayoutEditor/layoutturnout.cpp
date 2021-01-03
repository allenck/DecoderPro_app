#include "layoutturnout.h"
#include "instancemanager.h"
#include <qmath.h>
#include <QMessageBox>
#include "inputdialog.h"
//#include "editTurnout::h"
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
#include "path.h"
#include "mathutil.h"
#include "layouteditorfinditems.h"
#include <cmath>
#include <QApplication>
#include "signalheadmanager.h"
#include "joptionpane.h"
//#include "layouttrackeditors.h"
#include "layoutturnouteditor.h"
#include "layouteditortoolbarpanel.h"

//LayoutTurnout::LayoutTurnout(QObject *parent) :
//    QObject(parent)
//{

//}
/**
 * A LayoutTurnout corresponds to a turnout on the layout. A LayoutTurnout is an
 * extension of the standard Turnout object with drawing and connectivity
 * information added.
 * <P>
 * Six types are supported: right-hand, left-hand, wye, double crossover,
 * right-handed single crossover, and left-handed single crossover. Note that
 * double-slip turnouts can be handled as two turnouts, throat to throat, and
 * three-way turnouts can be handles as two turnouts, left-hand and right-hand,
 * arranged throat to continuing route.
 * <P>
 * A LayoutTurnout has three or four connection points, designated A, B, C, and
 * D. For right-handed or left-handed turnouts, A corresponds to the throat. At
 * the crossing, A-B (and C-D for crossovers) is a straight segment (continuing
 * route). A-C (and B-D for crossovers) is the diverging route. B-C (and A-D for
 * crossovers) is an illegal condition.
 * <P>
 * {@literal
 *           Turnouts
 * Right-hand       Left-hand
 *
 *                        C
 *                       //
 * A ==**== B       A ==**== B
 *      \\
 *       C
 *
 *    Wye           Three-way
 *
 *       B                D
 *      //               //
 * A ==**           A ==**== B
 *      \\               \\
 *       C                C
 *
 *           Crossovers
 * Right-hand            left-hand
 * A ==**===== B      A ====**== B
 *      \\                 //
 *       \\               //
 *  D ====**== C     D ==**===== C
 *
 *             Double
 *        A ==**==**== B
 *             \\//
 *              XX
 *             //\\
 *        D ==**==**== C
 * literal}
 * <P>
 * A LayoutTurnout carries Block information. For right-handed, left-handed, and
 * wye turnouts, the entire turnout is in one block,however, a block border may
 * occur at any connection (A,B,C,D). For a double crossover turnout, up to four
 * blocks may be assigned, one for each connection point, but if only one block
 * is assigned, that block applies to the entire turnout.
 * <P>
 * For drawing purposes, each LayoutTurnout carries a center point and
 * displacements for B and C. For right-handed or left-handed turnouts, the
 * displacement for A = - the displacement for B, and the center point is at the
 * junction of the diverging route and the straight through continuing route.
 * For double crossovers, the center point is at the center of the turnout, and
 * the displacement for A = - the displacement for C and the displacement for D
 * = - the displacement for B. The center point and these displacements may be
 * adjusted by the user when in edit mode. For double crossovers, AB and BC are
 * constrained to remain perpendicular. For single crossovers, AB and CD are
 * constrained to remain parallel, and AC and BD are constrained to remain
 * parallel.
 * <P>
 * When LayoutTurnouts are first created, a rotation (degrees) is provided. For
 * 0.0 rotation, the turnout lies on the east-west line with A facing east.
 * Rotations are performed in a clockwise direction.
 * <P>
 * When LayoutTurnouts are first created, there are no connections. Block
 * information and connections may be added when available.
 * <P>
 * When a LayoutTurnout is first created, it is enabled for control of an
 * assigned actual turnout. Clicking on the turnout center point will toggle the
 * turnout. This can be disabled via the popup menu.
 * <P>
 * Signal Head names are saved here to keep track of where signals are.
 * LayoutTurnout only serves as a storage place for signal head names. The names
 * are placed here by tools, e.g., Set Signals at Turnout, and Set Signals at
 * Double Crossover.
 * <P>
 * A LayoutTurnout may be linked to another LayoutTurnout to form a turnout
 * pair. Throat-To-Throat Turnouts - Two turnouts connected closely at their
 * throats, so closely that signals are not appropriate at the their throats.
 * This is the situation when two RH, LH, or WYE turnouts are used to model a
 * double slip. 3-Way Turnout - Two turnouts modeling a 3-way turnout, where the
 * throat of the second turnout is closely connected to the continuing track of
 * the first turnout. The throat will have three heads, or one head. A link is
 * required to be able to correctly interpret the use of signal heads.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @author George Warner Copyright (c) 2017-2018
 */

///*public*/ class LayoutTurnout
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

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
/*protected*/ LayoutTurnout::LayoutTurnout(/*@Nonnull*/ QString id,
        /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor)
 : LayoutTrack(id, c, layoutEditor) {
    //super(id, c, layoutEditor);

 editor = new LayoutTurnoutEditor(layoutEditor);
}

/*protected*/ LayoutTurnout::LayoutTurnout(/*@Nonnull*/ QString id,
        /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor, LayoutTurnout::TurnoutType t)
 : LayoutTrack(id, c, layoutEditor) {
    //super(id, c, layoutEditor);
 type = t;

 editor = new LayoutTurnoutEditor(layoutEditor);
}

/*public*/ LayoutTurnout::LayoutTurnout(QString id, LayoutTurnout::TurnoutType t, QPointF c, double rot, double xFactor, double yFactor,
                                        LayoutEditor* layoutEditor)
 : LayoutTrack(id, c, layoutEditor)
{
 common(id, t, c, rot, xFactor, yFactor, layoutEditor, 1);
}

/*public*/ LayoutTurnout::LayoutTurnout(/*@Nonnull*/ QString id, LayoutTurnout::TurnoutType t, /*@Nonnull*/ QPointF c, double rot,
           double xFactor, double yFactor, /*@Nonnull*/ LayoutEditor* layoutEditor, int v)
  : LayoutTrack(id, c, layoutEditor)
{
 common(id, t, c, rot, xFactor, yFactor, layoutEditor, v);
}


void LayoutTurnout::common(QString id, LayoutTurnout::TurnoutType t, QPointF c, double rot, double xFactor, double yFactor, LayoutEditor *layoutEditor, int v)
{
 log = new Logger("LayoutTurnout");

 setObjectName(id);
 editor = new LayoutTurnoutEditor(layoutEditor);

 editLayoutTurnoutFrame = nullptr;
 editOpen = false;
 turnoutName = "";   // should be the name (system or user) of
                                    //	an existing physical turnout
 secondTurnoutName = "";   /* should be the name (system or user) of
                                    an existing physical Turnout:: Second turnout is
                                    used to allow the throwing of two different turnout
                                    to control one cross-over
                                    */
 blockName = "";  // name for block, if there is one
 blockBName = "";  // Xover - name for second block, if there is one
 blockCName = "";  // Xover - name for third block, if there is one
 blockDName = "";  // Xover - name for fourth block, if there is one
 blockB = nullptr;
 blockC = nullptr;
 blockD = nullptr;

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
 sensorANamed = nullptr; // Throat
 sensorBNamed = nullptr; // Continuing
 sensorCNamed = nullptr; // diverging
 sensorDNamed = nullptr; // single or double crossover only
 type = RH_TURNOUT;
 connectA = nullptr;		// throat of LH, RH, RH Xover, LH Xover, and WYE turnouts
 connectB = nullptr;		// straight leg of LH and RH turnouts
 connectC = nullptr;
 connectD = nullptr;		// double xover, RH Xover, LH Xover only
 continuingSense = Turnout::CLOSED;
 disabled = false;
 hidden = false;
 disableWhenOccupied = false;
 dispB =  QPointF(20.0,0.0);
 pointA = QPointF(0, 0);
 pointB = QPointF(40, 0);
 pointC = QPointF(60, 20);
 pointD = QPointF(20, 20);
 linkedTurnoutName = ""; // name of the linked Turnout (as entered in tool)
 linkType = NO_LINK;
 popup = nullptr;
// JCheckBoxMenuItem* disableItem = nullptr;
// JCheckBoxMenuItem* disableWhenOccupiedItem = nullptr;
 tools = nullptr;
 circle = nullptr;

 turnoutNameField = new JTextField(16);
 blockBNameField = new JTextField(16);
 blockCNameField = new JTextField(16);
 blockDNameField = new JTextField(16);
 stateBox = new QComboBox();
 hiddenBox = new QCheckBox(tr("Hide Turnout"));
 editOpen = false;
 additionalTurnout = new QCheckBox(tr("Use Two Physical Addresses"));
 editLayoutTurnoutFrame = nullptr;
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
 secondNamedTurnout = nullptr;
 item = nullptr;
 rects = nullptr;
 signalAMastNamed = nullptr; // Throat
 signalBMastNamed = nullptr; // Continuing
 signalCMastNamed = nullptr; // diverging
 signalDMastNamed = nullptr; // single or double crossover only


    //instance = this;
    namedTurnout = nullptr;
    turnoutName = "";
    mTurnoutListener = nullptr;
    disabled = false;
    disableWhenOccupied = false;
    block = nullptr;
    blockName = "";
    //myPanel = myPanel;
//    ident = id;
    type = t;
//    center = c;
    version = v;

    // adjust initial coordinates
    if (type==LH_TURNOUT)
    {
     //.dispB.setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB = QPointF(layoutEditor->getTurnoutBX(), 0.0);
     dispA = QPointF(layoutEditor->getTurnoutCX(), -layoutEditor->getTurnoutWid());
    }
    else if (type==RH_TURNOUT)
    {
     //.dispB.setLocation(layoutEditor->getTurnoutBX(),0.0);
     dispB = QPointF(layoutEditor->getTurnoutBX(), 0.0);
     dispA = QPointF(layoutEditor->getTurnoutCX(), layoutEditor->getTurnoutWid());
    }
    else if (type==WYE_TURNOUT)
    {
     dispB = QPointF(layoutEditor->getTurnoutBX(), 0.5 * layoutEditor->getTurnoutWid());
     dispA = QPointF(layoutEditor->getTurnoutBX(), -0.5 * layoutEditor->getTurnoutWid());
    }
    else if (type==DOUBLE_XOVER)
    {
     if (version == 2) {
         center = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
         pointB = QPointF(layoutEditor->getXOverLong() * 2, 0);
         pointC = QPointF(layoutEditor->getXOverLong() * 2, (layoutEditor->getXOverHWid() * 2));
         pointD = QPointF(0, (layoutEditor->getXOverHWid() * 2));
         setCoordsCenter(c);
     } else {
         dispB = QPointF(layoutEditor->getXOverLong(), -layoutEditor->getXOverHWid());
         dispA = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
     }
    }
    else if (type==RH_XOVER)
    {
     if (version == 2) {
         center = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
         pointB = QPointF((layoutEditor->getXOverShort() + layoutEditor->getXOverLong()), 0);
         pointC = QPointF(layoutEditor->getXOverLong() * 2, (layoutEditor->getXOverHWid() * 2));
         pointD = QPointF((center.x() - layoutEditor->getXOverShort()), (layoutEditor->getXOverHWid() * 2));
         setCoordsCenter(c);
     } else {
         dispB = QPointF(layoutEditor->getXOverShort(), -layoutEditor->getXOverHWid());
         dispA = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
     }
    }
    else if (type==LH_XOVER)
    {
     if (version == 2) {
         center = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());

         pointA = QPointF((center.x() - layoutEditor->getXOverShort()), 0);
         pointB = QPointF((layoutEditor->getXOverLong() * 2), 0);
         pointC = QPointF(layoutEditor->getXOverLong() + layoutEditor->getXOverShort(), (layoutEditor->getXOverHWid() * 2));
         pointD = QPointF(0, (layoutEditor->getXOverHWid() * 2));

         setCoordsCenter(c);
     } else {
         dispB = QPointF(layoutEditor->getXOverLong(), -layoutEditor->getXOverHWid());
         dispA = QPointF(layoutEditor->getXOverShort(), layoutEditor->getXOverHWid());
     }
    }
    rotateCoords(rot);
    // adjust size of new turnout
    QPointF pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
    pt =  QPointF(round(dispA.x()*xFactor),
                                    round(dispA.y()*yFactor));
    dispA = pt;
}
// this should only be used for debugging...
    //@Override
    /*public*/ QString LayoutTurnout::toString() {
        return "LayoutTurnout " + getId();
    }
/*private*/ double LayoutTurnout::round (double x) {
    int i = (int)(x+0.5);
    return i;
}

/*protected*/ void LayoutTurnout::rotateCoords(double angleDEG)
{
    // rotate coordinates
 double rotRAD = qDegreesToRadians(angleDEG);
 double sineRot = qSin(rotRAD);
 double cosineRot = qCos(rotRAD);

 // rotate displacements around origin {0, 0}
 QPointF center_temp = center;
 center = MathUtil::zeroPoint2D;
 dispA = rotatePoint(dispA, sineRot, cosineRot);
 dispB = rotatePoint(dispB, sineRot, cosineRot);
 center = center_temp;

 pointA = rotatePoint(pointA, sineRot, cosineRot);
 pointB = rotatePoint(pointB, sineRot, cosineRot);
 pointC = rotatePoint(pointC, sineRot, cosineRot);
 pointD = rotatePoint(pointD, sineRot, cosineRot);
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

/*public*/ QString LayoutTurnout::getTurnoutName()
{
 if (namedTurnout!=nullptr)
  turnoutName = namedTurnout->getName();
 return turnoutName;
}

/*public*/ QString LayoutTurnout::getSecondTurnoutName()
{
 if (secondNamedTurnout!=nullptr)
     secondTurnoutName = secondNamedTurnout->getName();
 return secondTurnoutName;
}

/*public*/ bool LayoutTurnout::isSecondTurnoutInverted() {
        return secondTurnoutInverted;
    }

/*public*/ bool LayoutTurnout::getHidden() {return hidden;}
/*public*/ void LayoutTurnout::setHidden(bool hide) {hidden = hide;}

/*public*/ QString LayoutTurnout::getBlockName()
{
 QString result = QString();
 if (namedLayoutBlockA != nullptr) {
     result = namedLayoutBlockA->getName();
 }
 return ((result.isEmpty()) ? "" : result);

}
/*public*/ QString LayoutTurnout::getBlockBName()
{
 QString result = getBlockName();
 if (namedLayoutBlockB != nullptr) {
     result = namedLayoutBlockB->getName();
 }
 return result;

}
/*public*/ QString LayoutTurnout::getBlockCName()
{
 QString result = getBlockName();
 if (namedLayoutBlockC != nullptr) {
     result = namedLayoutBlockC->getName();
 }
 return result;

}
/*public*/ QString LayoutTurnout::getBlockDName()
{
 QString result = getBlockName();
 if (namedLayoutBlockD != nullptr) {
     result = namedLayoutBlockD->getName();
 }
 return result;

}

/*public*/ SignalHead* LayoutTurnout::getSignalA1() {
    return signalA1HeadNamed != nullptr ? signalA1HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalA1Name()
{
 if (signalA1HeadNamed != nullptr) {
     return signalA1HeadNamed->getName();
 }
 return "";
}

/*public*/ SignalHead* LayoutTurnout::getSignalHead(int loc)
{
    NamedBeanHandle<SignalHead*>* signalHead = nullptr;
    switch (loc) {
        case POINTA1:
            signalHead = signalA1HeadNamed;
            break;
        case POINTA2:
            signalHead = signalA2HeadNamed;
            break;
        case POINTA3:
            signalHead = signalA3HeadNamed;
            break;
        case POINTB1:
            signalHead = signalB1HeadNamed;
            break;
        case POINTB2:
            signalHead = signalB2HeadNamed;
            break;
        case POINTC1:
            signalHead = signalC1HeadNamed;
            break;
        case POINTC2:
            signalHead = signalC2HeadNamed;
            break;
        case POINTD1:
            signalHead = signalD1HeadNamed;
            break;
        case POINTD2:
            signalHead = signalD2HeadNamed;
            break;
        default:
            log->warn(tr("Unhandled point type: %1").arg(loc));
            break;
    }
    if (signalHead != nullptr) {
        return signalHead->getBean();
    }
    return nullptr;
}
/*public*/ void LayoutTurnout::setSignalA1Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalA1HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalA1HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalA1HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}
/*public*/ SignalHead* LayoutTurnout::getSignalA2() {
    return signalA2HeadNamed != nullptr ? signalA2HeadNamed->getBean() : nullptr;
}
/*public*/ QString LayoutTurnout::getSignalA2Name()
{
 if (signalA2HeadNamed != nullptr)
 {
     return signalA2HeadNamed->getName();
 }
 return "";

}
/*public*/ void LayoutTurnout::setSignalA2Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalA2HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalA2HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalA2HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ SignalHead* LayoutTurnout::getSignalA3() {
    return signalA3HeadNamed != nullptr ? signalA3HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalA3Name()
{
 if (signalA3HeadNamed != nullptr) {
     return signalA3HeadNamed->getName();
 }
 return "";
}
/*public*/ void LayoutTurnout::setSignalA3Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalA3HeadNamed = nullptr;
     return;
 }
 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalA3HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalA3HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ SignalHead* LayoutTurnout::getSignalB1() {
    return signalB1HeadNamed != nullptr ? signalB1HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalB1Name()
{
 if (signalB1HeadNamed != nullptr) {
     return signalB1HeadNamed->getName();
 }
 return "";
}

/*public*/ void LayoutTurnout::setSignalB1Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalB1HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalB1HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalB1HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }

}

/*public*/ SignalHead* LayoutTurnout::getSignalB2() {
    return signalB2HeadNamed != nullptr ? signalB2HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalB2Name()
{
 if (signalB2HeadNamed != nullptr) {
     return signalB2HeadNamed->getName();
 }
 return "";
}
/*public*/ void LayoutTurnout::setSignalB2Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalB2HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalB2HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalB2HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ SignalHead* LayoutTurnout::getSignalC1() {
    return signalC1HeadNamed != nullptr ? signalC1HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalC1Name()
{
 if (signalC1HeadNamed != nullptr) {
     return signalC1HeadNamed->getName();
 }
 return "";
}
/*public*/ void LayoutTurnout::setSignalC1Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalC1HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalC1HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalC1HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }

}
/*public*/ SignalHead* LayoutTurnout::getSignalC2() {
    return signalC2HeadNamed != nullptr ? signalC2HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalC2Name()
{
 if (signalC2HeadNamed != nullptr) {
     return signalC2HeadNamed->getName();
 }
 return "";

}
/*public*/ void LayoutTurnout::setSignalC2Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalC2HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalC2HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalC2HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ SignalHead* LayoutTurnout::getSignalD1() {
        return signalD1HeadNamed != nullptr ? signalD1HeadNamed->getBean() : nullptr;
    }
/*public*/ QString LayoutTurnout::getSignalD1Name()
{
 if (signalD1HeadNamed != nullptr) {
     return signalD1HeadNamed->getName();
 }
 return "";

}
/*public*/ void LayoutTurnout::setSignalD1Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalD1HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalD1HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalD1HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ SignalHead* LayoutTurnout::getSignalD2() {
    return signalD2HeadNamed != nullptr ? signalD2HeadNamed->getBean() : nullptr;
}

/*public*/ QString LayoutTurnout::getSignalD2Name()
{
 if (signalD2HeadNamed != nullptr) {
     return signalD2HeadNamed->getName();
 }
 return "";

}
/*public*/ void LayoutTurnout::setSignalD2Name(QString signalHead)
{
 if (signalHead.isNull() || signalHead.isEmpty()) {
     signalD2HeadNamed = nullptr;
     return;
 }

 SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
 if (head != nullptr) {
     signalD2HeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
 } else {
     signalD2HeadNamed = nullptr;
     log->error(tr("Signal Head %1 Not found for turnout %2").arg(signalHead).arg(getTurnoutName()));
 }
}

/*public*/ void LayoutTurnout::removeBeanReference(NamedBean* nb) {
        if (nb == nullptr) {
            return;
        }
        if (qobject_cast<SignalMast*>(nb)) {
            if (nb->equals(getSignalAMast())) {
                setSignalAMast("");
                return;
            }
            if (nb->equals(getSignalBMast())) {
                setSignalBMast("");
                return;
            }
            if (nb->equals(getSignalCMast())) {
                setSignalCMast("null");
                return;
            }
            if (nb->equals(getSignalDMast())) {
                setSignalDMast("null");
                return;
            }
        } else if (qobject_cast<Sensor*>(nb)) {
            if (nb->equals(getSensorA())) {
                setSensorA("");
                return;
            }
            if (nb->equals(getSensorB())) {
                setSensorB("");
                return;
            }
            if (nb->equals(getSensorC())) {
                setSensorC("");
                return;
            }
            if (nb->equals(getSensorB())) {
                setSensorD("");
                return;
            }
        } else if (qobject_cast<SignalHead*>(nb)) {
            if (nb->equals(getSignalHead(POINTA1))) {
                setSignalA1Name("");
            }
            if (nb->equals(getSignalHead(POINTA2))) {
                setSignalA2Name("");
            }
            if (nb->equals(getSignalHead(POINTA3))) {
                setSignalA3Name("");
            }
            if (nb->equals(getSignalHead(POINTB1))) {
                setSignalB1Name("");
            }
            if (nb->equals(getSignalHead(POINTB2))) {
                setSignalB2Name("");
            }
            if (nb->equals(getSignalHead(POINTC1))) {
                setSignalC1Name("");
            }
            if (nb->equals(getSignalHead(POINTC2))) {
                setSignalC2Name("");
            }
            if (nb->equals(getSignalHead(POINTD1))) {
                setSignalD1Name("");
            }
            if (nb->equals(getSignalHead(POINTD2))) {
                setSignalD2Name("");
            }
        }
    }

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool LayoutTurnout::canRemove() {
    QList<QString> beanReferences = getBeanReferences("All");  // NOI18N
    if (!beanReferences.isEmpty()) {
        displayRemoveWarningDialog(beanReferences, "BeanNameTurnout");  // NOI18N
    }
    return beanReferences.isEmpty();
}

/**
 * Build a list of sensors, signal heads, and signal masts attached to a
 * turnout point.
 *
 * @param pointName Specify the point (A-D) or all (All) points.
 * @return a list of bean reference names.
 */
/*public*/ QList<QString> LayoutTurnout::getBeanReferences(QString pointName) {
    QList<QString> references = QList<QString>();
    if (pointName == ("A") || pointName == ("All")) {  // NOI18N
        if (!getSignalAMastName().isEmpty()) {
            references.append(getSignalAMastName());
        }
        if (!getSensorAName().isEmpty()) {
            references.append(getSensorAName());
        }
        if (!getSignalA1Name().isEmpty()) {
            references.append(getSignalA1Name());
        }
        if (!getSignalA2Name().isEmpty()) {
            references.append(getSignalA2Name());
        }
        if (!getSignalA3Name().isEmpty()) {
            references.append(getSignalA3Name());
        }
    }
    if (pointName == ("B") || pointName == ("All")) {  // NOI18N
        if (!getSignalBMastName().isEmpty()) {
            references.append(getSignalBMastName());
        }
        if (!getSensorBName().isEmpty()) {
            references.append(getSensorBName());
        }
        if (!getSignalB1Name().isEmpty()) {
            references.append(getSignalB1Name());
        }
        if (!getSignalB2Name().isEmpty()) {
            references.append(getSignalB2Name());
        }
    }
    if (pointName == ("C") || pointName == ("All")) {  // NOI18N
        if (!getSignalCMastName().isEmpty()) {
            references.append(getSignalCMastName());
        }
        if (!getSensorCName().isEmpty()) {
            references.append(getSensorCName());
        }
        if (!getSignalC1Name().isEmpty()) {
            references.append(getSignalC1Name());
        }
        if (!getSignalC2Name().isEmpty()) {
            references.append(getSignalC2Name());
        }
    }
    if (pointName == ("D") || pointName == ("All")) {  // NOI18N
        if (!getSignalDMastName().isEmpty()) {
            references.append(getSignalDMastName());
        }
        if (!getSensorDName().isEmpty()) {
            references.append(getSensorDName());
        }
        if (!getSignalD1Name().isEmpty()) {
            references.append(getSignalD1Name());
        }
        if (!getSignalD2Name().isEmpty()) {
            references.append(getSignalD2Name());
        }
    }
    return references;
}

/*public*/ QString LayoutTurnout::getSignalAMastName() {
    if (signalAMastNamed != nullptr) {
        return signalAMastNamed->getName();
    }
    return "";
}
/*public*/ SignalMast* LayoutTurnout::getSignalAMast() const
{
 if(signalAMastNamed == nullptr)
 {
  log->warn(tr("signalAMastNamed is null"));
  return nullptr;
 }
 return signalAMastNamed->getBean();
}

/*public*/ void LayoutTurnout::setSignalAMast(QString signalMast)
{
 if (signalMast.isNull() || signalMast.isEmpty()) {
     signalAMastNamed = nullptr;
     return;
 }

 SignalMast* mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
 if (mast != nullptr) {
     signalAMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
 } else {
     signalAMastNamed = nullptr;
     log->error(tr("Signal Mast %1 Not found for turnout %2").arg(signalMast).arg(getTurnoutName()));
 }

}

/*public*/ QString LayoutTurnout::getSignalBMastName()
{
 if (signalBMastNamed != nullptr)
 {
  return signalBMastNamed->getName();
 }
 return "";
}
/*public*/ SignalMast *LayoutTurnout::getSignalBMast()const
{
 if(signalBMastNamed == nullptr)
 {
  log->warn(tr("signalBMastNamed is Null"));
  return nullptr;
 }
 return signalBMastNamed->getBean();
}
/*public*/ void LayoutTurnout::setSignalBMast(QString signalMast)
{
 if (signalMast.isNull() || signalMast.isEmpty()) {
     signalBMastNamed = nullptr;
     return;
 }

 SignalMast* mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
 if (mast != nullptr) {
     signalBMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
 } else {
     signalBMastNamed = nullptr;
     log->error(tr("Signal Mast %1 Not found for turnout %2").arg(signalMast).arg(getTurnoutName()));
 }
}

/*public*/ QString LayoutTurnout::getSignalCMastName()
{
 if (signalCMastNamed != nullptr)
 {
  return signalCMastNamed->getName();
 }
 return "";
}
/*public*/ SignalMast* LayoutTurnout::getSignalCMast()const {
 if(signalCMastNamed == nullptr)
 {
  log->warn( tr("signalCMastNamed is Null"));
  return nullptr;
 }
 return signalCMastNamed->getBean();}

/*public*/ void LayoutTurnout::setSignalCMast(QString signalMast)
{
 if (signalMast.isNull() || signalMast.isEmpty()) {
     signalCMastNamed = nullptr;
     return;
 }

 SignalMast* mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
 if (mast != nullptr) {
     signalCMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
 } else {
     signalCMastNamed = nullptr;
     log->error(tr("Signal Mast %1 Not found for turnout %2").arg(signalMast).arg(getTurnoutName()));
 }
}
/*public*/ QString LayoutTurnout::getSignalDMastName()
{
 if (signalDMastNamed != nullptr)
 {
  return signalDMastNamed->getName();
 }
 return "";
}
/*public*/ SignalMast *LayoutTurnout::getSignalDMast() const
{
 if(signalDMastNamed== nullptr)
  throw NullPointerException();
 return signalDMastNamed->getBean();
}
/*public*/ void LayoutTurnout::setSignalDMast(QString signalMast)
{
 if (signalMast.isNull() || signalMast.isEmpty()) {
     signalDMastNamed = nullptr;
     return;
 }

 SignalMast* mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
 if (mast != nullptr) {
     signalDMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
 } else {
     signalDMastNamed = nullptr;
     log->error(tr("Signal Mast %1 Not found for turnout %2").arg(signalMast).arg(getTurnoutName()));
 }
}

/*public*/ QString LayoutTurnout::getSensorAName()
{
 if (sensorANamed != nullptr) {
     return sensorANamed->getName();
 }
 return "";
}

/*public*/ Sensor* LayoutTurnout::getSensorA() {
    if(sensorANamed!=nullptr)
        return sensorANamed->getBean();
    return nullptr;
}

/*public*/ void LayoutTurnout::setSensorA(QString sensorName)
{
    if(sensorName==nullptr || sensorName==(""))
    {
        sensorANamed=nullptr;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != nullptr) {
        sensorANamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorANamed=nullptr;
    }
}

/*public*/ Sensor *LayoutTurnout::getSensorB() {
    if(sensorBNamed!=nullptr)
        return sensorBNamed->getBean();
    return nullptr;
}

/*public*/ QString LayoutTurnout::getSensorBName()
{
 if (sensorBNamed != nullptr) {
     return sensorBNamed->getName();
 }
 return "";
}
/*public*/ void LayoutTurnout::setSensorB(QString sensorName)
{
 if(sensorName==nullptr || sensorName==(""))
 {
  sensorBNamed=nullptr;
  return;
 }

 Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
 if (sensor != nullptr)
 {
  sensorBNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
 }
 else
 {
  sensorBNamed=nullptr;
 }
}

/*public*/ QString LayoutTurnout::getSensorCName()
{
 if (sensorCNamed != nullptr) {
     return sensorCNamed->getName();
 }
 return "";
}
/*public*/ Sensor* LayoutTurnout::getSensorC() {
    if(sensorCNamed!=nullptr)
        return sensorCNamed->getBean();
    return nullptr;
}

/*public*/ void LayoutTurnout::setSensorC(QString sensorName) {
    if(sensorName==nullptr || sensorName==("")){
        sensorCNamed=nullptr;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != nullptr) {
        sensorCNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorCNamed=nullptr;
    }
}

/*public*/ QString LayoutTurnout::getSensorDName()
{
 if (sensorDNamed != nullptr) {
     return sensorDNamed->getName();
 }
 return "";
}
/*public*/ Sensor *LayoutTurnout::getSensorD() {
    if(sensorDNamed!=nullptr)
        return sensorDNamed->getBean();
    return nullptr;
}

/*public*/ void LayoutTurnout::setSensorD(QString sensorName) {
    if(sensorName==nullptr || sensorName==("")){
        sensorDNamed=nullptr;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != nullptr) {
        sensorDNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        sensorDNamed=nullptr;
    }
}

/*public*/ QString LayoutTurnout::getLinkedTurnoutName() {return linkedTurnoutName;}
/*public*/ void LayoutTurnout::setLinkedTurnoutName(QString s) {linkedTurnoutName = s;}

/*public*/ int LayoutTurnout::getLinkType() {return linkType;}
/*public*/ void LayoutTurnout::setLinkType(int type) {linkType = type;}
/*public*/ LayoutTurnout::TurnoutType LayoutTurnout::getTurnoutType() const {return type;}
/**
 * Returns true if this is a turnout (not a crossover or slip)
 *
 * @param type the turnout type
 * @return boolean true if this is a turnout
 */
/*public*/ /*static*/ bool LayoutTurnout::isTurnoutTypeTurnout(TurnoutType type) {
    return (type == TurnoutType::RH_TURNOUT
            || type == TurnoutType::LH_TURNOUT
            || type == TurnoutType::WYE_TURNOUT);
}

/**
 * Returns true if this is a turnout (not a crossover or slip)
 *
 * @return boolean true if this is a turnout
 */
/*public*/ bool LayoutTurnout::isTurnoutTypeTurnout() const {
    return isTurnoutTypeTurnout(getTurnoutType());
}

/**
 * Returns true if this is a crossover
 *
 * @param type the turnout type
 * @return boolean true if this is a crossover
 */
/*public*/ /*static*/ bool LayoutTurnout::isTurnoutTypeXover(TurnoutType type) {
    return (type == TurnoutType::DOUBLE_XOVER
            || type == TurnoutType::RH_XOVER
            || type == TurnoutType::LH_XOVER);
}

/*public*/ bool LayoutTurnout::isTurnoutTypeXover() const{
 return hasEnteringDoubleTrack(getTurnoutType());
}

/**
 * Returns true if this is a slip
 *
 * @param type the turnout type
 * @return boolean true if this is a slip
 */
/*public*/ /*static*/ bool LayoutTurnout::isTurnoutTypeSlip(TurnoutType type) {
    return (type == TurnoutType::SINGLE_SLIP
            || type == TurnoutType::DOUBLE_SLIP);
}

/*public*/ bool LayoutTurnout::isTurnoutTypeSlip() {
 return isTurnoutTypeSlip(getTurnoutType());
}

/**
 * Returns true if this has a single-track entrance end. (turnout or wye)
 *
 * @param type the turnout type
 * @return boolean true if single track entrance
 */
/*public*/ /*static*/ bool LayoutTurnout::hasEnteringSingleTrack(TurnoutType type) {
    return isTurnoutTypeTurnout(type);
}

/**
 * Returns true if this has a single-track entrance end. (turnout or wye)
 *
 * @return boolean true if single track entrance
 */
/*public*/ bool LayoutTurnout::hasEnteringSingleTrack() {
    return hasEnteringSingleTrack(getTurnoutType());
}

/**
 * Returns true if this has double track on the entrance end (crossover or
 * slip)
 *
 * @param type the turnout type
 * @return boolean true if double track entrance
 */
/*public*/ /*static*/ bool LayoutTurnout::hasEnteringDoubleTrack(TurnoutType type) {
    return isTurnoutTypeXover(type) || isTurnoutTypeSlip(type);
}

/**
 * Returns true if this has double track on the entrance end (crossover or
 * slip)
 *
 * @return boolean true if double track entrance
 */
/*public*/ bool LayoutTurnout::hasEnteringDoubleTrack() {
    return hasEnteringDoubleTrack(getTurnoutType());
}

/*public*/ QObject* LayoutTurnout::getConnectA() {return connectA;}
/*public*/ QObject* LayoutTurnout::getConnectB() {return connectB;}
/*public*/ QObject* LayoutTurnout::getConnectC() {return connectC;}
/*public*/ QObject* LayoutTurnout::getConnectD() {return connectD;}

/*public*/ Turnout* LayoutTurnout::getTurnout()
{
 // begin hack ACK
 if(turnoutName ==  "")
  getTurnoutName();
 if(secondTurnoutName== "")
  getSecondTurnoutName();
 // end hack Ack

 if (namedTurnout==nullptr)
 {
  // set physical turnout if possible and needed
  setTurnout(turnoutName); // turnoutName should be the name (system or user) of
  //	an existing physical turnout
  if (namedTurnout==nullptr)
   return nullptr;
 }
 return namedTurnout->getBean();
}

/*public*/ int LayoutTurnout::getContinuingSense() {return continuingSense;}

/**
 *
 * @return true is the continuingSense matches the known state
 */
/*public*/ bool LayoutTurnout::isInContinuingSenseState() {
    return getState() == continuingSense;
}

/*public*/ void LayoutTurnout::setTurnout(QString tName)
{
 if (namedTurnout!=nullptr)
  deactivateTurnout();
 turnoutName = tName;
 Turnout* turnout = nullptr;
 if (!turnoutName.isNull() && !turnoutName.isEmpty())
 {
  Manager* mgr = InstanceManager::turnoutManagerInstance();
  QStringList sysNames = mgr->getSystemNameList();
   turnout = ((ProxyTurnoutManager*)mgr)->getTurnout(turnoutName);
 }
 if (turnout!=nullptr)
 {
  namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutName, turnout);
  activateTurnout();
 }
 else
 {
  turnoutName = "";
  namedTurnout = nullptr;
 }
}

/*public*/ Turnout* LayoutTurnout::getSecondTurnout()
{
 if (secondNamedTurnout==nullptr)
 {
  // set physical turnout if possible and needed
  setSecondTurnout(secondTurnoutName);

  if (secondNamedTurnout==nullptr)
  {
   return nullptr;
  }
 }
 return secondNamedTurnout->getBean();
}

/*public*/ void LayoutTurnout::setSecondTurnout(QString tName)
{
 if(tName!=nullptr && tName==(secondTurnoutName))
 {
  return;
 }

 if (secondNamedTurnout!=nullptr) deactivateTurnout();
 QString oldSecondTurnoutName = secondTurnoutName;
 secondTurnoutName = tName;
 Turnout* turnout = nullptr;
 if(tName!=nullptr)
 {
  turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                        getTurnout(secondTurnoutName);
 }
 if (turnout!=nullptr)
 {
  secondNamedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(secondTurnoutName, turnout);
        activateTurnout();
 }
 else
 {
  secondTurnoutName = "";
  secondNamedTurnout = nullptr;
 }
 if ( (type == RH_TURNOUT) || (type ==LH_TURNOUT) || (type == WYE_TURNOUT) ){
  LayoutEditorFindItems* lf = layoutEditor->getFinder();
  if(oldSecondTurnoutName!=nullptr && oldSecondTurnoutName!=(""))
  {
   Turnout* oldTurnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                        getTurnout(oldSecondTurnoutName);
   LayoutTurnout* oldLinked = lf->findLayoutTurnoutByTurnoutName(oldTurnout->getSystemName());
   if(oldLinked==nullptr)
    oldLinked = lf->findLayoutTurnoutByTurnoutName(oldTurnout->getUserName());
   if((oldLinked!=nullptr) && oldLinked->getSecondTurnout()==getTurnout())
    oldLinked->setSecondTurnout(nullptr);
  }
  if(turnout!=nullptr)
  {
   LayoutTurnout* newLinked = lf->findLayoutTurnoutByTurnoutName(turnout->getSystemName());
   if(newLinked==nullptr)
    newLinked = lf->findLayoutTurnoutByTurnoutName(turnout->getUserName());
   if(newLinked!=nullptr)
   {
    newLinked->setSecondTurnout(turnoutName);
   }
  }
 }
}

/*public*/ void LayoutTurnout::setSecondTurnoutInverted(bool inverted) {
    secondTurnoutInverted = inverted;
}

/*public*/ void LayoutTurnout::setContinuingSense(int sense) {continuingSense=sense;}
/*public*/ void LayoutTurnout::setDisabled(bool state) {disabled = state;}
/*public*/ bool LayoutTurnout::isDisabled() {return disabled;}

/*public*/ void LayoutTurnout::setDisableWhenOccupied(bool state) {disableWhenOccupied = state;}
/*public*/ bool LayoutTurnout::isDisabledWhenOccupied() {return disableWhenOccupied;}

/*public*/ LayoutTrack *LayoutTurnout::getConnection(int location) throw (JmriException)
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

/*public*/ void LayoutTurnout::setConnection(int location, LayoutTrack* o, int type) throw (JmriException)
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

/*public*/ void LayoutTurnout::setConnectA(LayoutTrack* o,int type)
{
 connectA = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of A connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectB(LayoutTrack *o, int type)
{
 connectB = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of B connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectC(LayoutTrack* o,int type)
{
 connectC = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of C connection to layoutturnout - "+QString("%1").arg(type));
 }
}
/*public*/ void LayoutTurnout::setConnectD(LayoutTrack *o, int type)
{
 connectD = o;
 if ( (type!=LayoutEditor::TRACK) && (type!=LayoutEditor::NONE) )
 {
  log->error("unexpected type of D connection to layoutturnout - "+QString("%1").arg(type));
 }
}

/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlock()const
{
 return (namedLayoutBlockA != nullptr) ? namedLayoutBlockA->getBean() : nullptr;
}

/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockB() const
{
 return (namedLayoutBlockB != nullptr) ? namedLayoutBlockB->getBean() : getLayoutBlock();

}

/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockC() const
{
 return (namedLayoutBlockC != nullptr) ? namedLayoutBlockC->getBean() : getLayoutBlock();
}

/*public*/ LayoutBlock* LayoutTurnout::getLayoutBlockD() const
{
 return (namedLayoutBlockD != nullptr) ? namedLayoutBlockD->getBean() : getLayoutBlock();
}

///*public*/ QPointF LayoutTurnout::getCoordsCenter() {return center;}
/*public*/ QPointF LayoutTurnout::getCoordsA()
{
 if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) || (type==DOUBLE_SLIP) || (type==SINGLE_SLIP))
 {
  if (version == 2) {
      return pointA;
  }
  return MathUtil::subtract(center, dispA);
 }
 else if (type==WYE_TURNOUT)
 {
  return MathUtil::subtract(center, MathUtil::midPoint(dispB, dispA));
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
 if ((version == 2) && ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == LH_XOVER)
         || (getTurnoutType() == RH_XOVER))) {
     return pointC;
 }
 return MathUtil::add(center, dispA);
}
/*public*/ QPointF LayoutTurnout::getCoordsD()
{
 // only allowed for single and double crossovers
 double x = center.x() - dispB.x();
 double y = center.y() - dispB.y();
 return  QPointF(x,y);
}
/**
 * return the coordinates for a specified connection type
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
//@Override
/*public*/ QPointF LayoutTurnout::getCoordsForConnectionType(int connectionType) {
    QPointF result = center;
    switch (connectionType) {
        case TURNOUT_CENTER:
            break;
        case TURNOUT_A:
            result = getCoordsA();
            break;
        case TURNOUT_B:
            result = getCoordsB();
            break;
        case TURNOUT_C:
            result = getCoordsC();
            break;
        case TURNOUT_D:
            result = getCoordsD();
            break;
        default:
            log->error("Invalid connection type " + QString::number(connectionType)); //I18IN
    }
    return result;
}

/**
 * @return the bounds of this turnout
 */
//@Override
/*public*/ QRectF LayoutTurnout::getBounds() {
 QRectF result;

 QPointF pointA = getCoordsA();
 result = QRectF(pointA.x(), pointA.y(), 0, 0);
 result = MathUtil::add(result, getCoordsB());
 result = MathUtil::add(result,getCoordsC());
 if (isTurnoutTypeXover() || isTurnoutTypeSlip()) {
     result = MathUtil::add(result, getCoordsD());
 }
 return result;
}

// updates connectivity for blocks assigned to this turnout and connected track segments
/*private*/ void LayoutTurnout::updateBlockInfo()
{
 LayoutBlock* bA = nullptr;
 LayoutBlock* bB = nullptr;
 LayoutBlock* bC = nullptr;
 LayoutBlock* bD = nullptr;
 layoutEditor->auxTools->setBlockConnectivityChanged();
 if (block!=nullptr) block->updatePaths();
 if (connectA!=nullptr)
 {
  bA = ((TrackSegment*)connectA)->getLayoutBlock();
  if ((bA!=nullptr) && (bA!=block)) bA->updatePaths();
 }
 if ((blockB!=nullptr) && (blockB!=block) && (blockB!=bA)) blockB->updatePaths();
 if (connectB!=nullptr)
 {
  bB = ((TrackSegment*)connectB)->getLayoutBlock();
  if ((bB!=nullptr) && (bB!=block) && (bB!=bA) && (bB!=blockB)) bB->updatePaths();
 }
 if ((blockC!=nullptr) && (blockC!=block) && (blockC!=bA) &&
         (blockC!=bB) && (blockC!=blockB)) blockC->updatePaths();
 if (connectC!=nullptr)
 {
  bC = ((TrackSegment*)connectC)->getLayoutBlock();
  if ((bC!=nullptr) && (bC!=block) && (bC!=bA) && (bC!=blockB) && (bC!=bB) &&
          (bC!=blockC)) bC->updatePaths();
 }
 if ((blockD!=nullptr) && (blockD!=block) && (blockD!=bA) &&
         (blockD!=bB) && (blockD!=blockB) && (blockD!=bC) &&
             (blockD!=blockC)) blockD->updatePaths();
 if (connectD!=nullptr)
 {
  bD = ((TrackSegment*)connectD)->getLayoutBlock();
  if ((bD!=nullptr) && (bD!=block) && (bD!=bA) && (bD!=blockB) && (bD!=bB) &&
      (bD!=blockC) && (bD!=bC) && (bD!=blockD)) bD->updatePaths();
 }
}

/**
 * Set default size parameters to correspond to this turnout's size
 */
/*private*/ void LayoutTurnout::setUpDefaultSize()
{
 // remove the overall scale factor
 double bX = dispB.x()/layoutEditor->gContext->getXScale();
 double bY = dispB.y()/layoutEditor->gContext->getYScale();
 double cX = dispA.x()/layoutEditor->gContext->getXScale();
 double cY = dispA.y()/layoutEditor->gContext->getYScale();
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
/*public*/ void LayoutTurnout::setLayoutBlock(LayoutBlock* newLayoutBlock) {
    LayoutBlock* blockA = getLayoutBlock();
    LayoutBlock* blockB = getLayoutBlockB();
    LayoutBlock* blockC = getLayoutBlockC();
    LayoutBlock* blockD = getLayoutBlockD();
    if (blockA != newLayoutBlock) {
        // block has changed, if old block exists, decrement use
        if ((blockA != nullptr)
                && (blockA != blockB)
                && (blockA != blockC)
                && (blockA != blockD)) {
            blockA->decrementUse();
        }

        blockA = newLayoutBlock;
        if (newLayoutBlock != nullptr) {
            QString userName = newLayoutBlock->getUserName();
            if (userName != nullptr) {
                namedLayoutBlockA = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, newLayoutBlock);
            }
        } else {
            namedLayoutBlockA = nullptr;
            setDisableWhenOccupied(false);
        }
        // decrement use if block was already counted
        if ((blockA != nullptr)
                && ((blockA == blockB) || (blockA == blockC) || (blockA == blockD))) {
            blockA->decrementUse();
        }
        setTrackSegmentBlocks();
    }
}

//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
/*public*/ void LayoutTurnout::setLayoutBlockB(LayoutBlock* newLayoutBlock) {
    if (getLayoutBlock() == nullptr) {
        setLayoutBlock(newLayoutBlock);
    }
    if (isTurnoutTypeXover() || isTurnoutTypeSlip()) {
        LayoutBlock* blockA = getLayoutBlock();
        LayoutBlock* blockB = getLayoutBlockB();
        LayoutBlock* blockC = getLayoutBlockC();
        LayoutBlock* blockD = getLayoutBlockD();
        if (blockB != newLayoutBlock) {
            // block has changed, if old block exists, decrement use
            if ((blockB != nullptr)
                    && (blockB != blockA)
                    && (blockB != blockC)
                    && (blockB != blockD)) {
                blockB->decrementUse();
            }
            blockB = newLayoutBlock;
            if (newLayoutBlock != nullptr) {
                namedLayoutBlockB = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
            } else {
                namedLayoutBlockB = nullptr;
            }
            // decrement use if block was already counted
            if ((blockB != nullptr)
                    && ((blockB == blockA) || (blockB == blockC) || (blockB == blockD))) {
                blockB->decrementUse();
            }
            setTrackSegmentBlocks();
        }
    } else {
        log->error("Attempt to set block B, but not a crossover");
    }
}

//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
/*public*/ void LayoutTurnout::setLayoutBlockC(LayoutBlock* newLayoutBlock) {
    if (getLayoutBlock() == nullptr) {
        setLayoutBlock(newLayoutBlock);
    }
    if (isTurnoutTypeXover() || isTurnoutTypeSlip()) {
        LayoutBlock* blockA = getLayoutBlock();
        LayoutBlock* blockB = getLayoutBlockB();
        LayoutBlock* blockC = getLayoutBlockC();
        LayoutBlock* blockD = getLayoutBlockD();
        if (blockC != newLayoutBlock) {
            // block has changed, if old block exists, decrement use
            if ((blockC != nullptr)
                    && (blockC != blockA)
                    && (blockC != blockB)
                    && (blockC != blockD)) {
                blockC->decrementUse();
            }
            blockC = newLayoutBlock;
            if (newLayoutBlock != nullptr) {
                namedLayoutBlockC = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
            } else {
                namedLayoutBlockC = nullptr;
            }
            // decrement use if block was already counted
            if ((blockC != nullptr)
                    && ((blockC == blockA) || (blockC == blockB) || (blockC == blockD))) {
                blockC->decrementUse();
            }
            setTrackSegmentBlocks();
        }
    } else {
        log->error("Attempt to set block C, but not a crossover");
    }
}

//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
/*public*/ void LayoutTurnout::setLayoutBlockD(LayoutBlock* newLayoutBlock) {
    if (getLayoutBlock() == nullptr) {
        setLayoutBlock(newLayoutBlock);
    }
    if (isTurnoutTypeXover() || isTurnoutTypeSlip()) {
        LayoutBlock* blockA = getLayoutBlock();
        LayoutBlock* blockB = getLayoutBlockB();
        LayoutBlock* blockC = getLayoutBlockC();
        LayoutBlock* blockD = getLayoutBlockD();
        if (blockD != newLayoutBlock) {
            // block has changed, if old block exists, decrement use
            if ((blockD != nullptr)
                    && (blockD != blockA)
                    && (blockD != blockB)
                    && (blockD != blockC)) {
                blockD->decrementUse();
            }
            blockD = newLayoutBlock;
            if (newLayoutBlock != nullptr) {
                namedLayoutBlockD = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
            } else {
                namedLayoutBlockD = nullptr;
            }
            // decrement use if block was already counted
            if ((blockD != nullptr)
                    && ((blockD == blockA) || (blockD == blockB) || (blockD == blockC))) {
                blockD->decrementUse();
            }
            setTrackSegmentBlocks();
        }
    } else {
        log->error("Attempt to set block D, but not a crossover");
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
 * Check each connection point and update the block value for very short
 * track segments.
 *
 * @since 4.11.6
 */
void LayoutTurnout::setTrackSegmentBlocks() {
    setTrackSegmentBlock(TURNOUT_A, false);
    setTrackSegmentBlock(TURNOUT_B, false);
    setTrackSegmentBlock(TURNOUT_C, false);
    if (getTurnoutType() > WYE_TURNOUT) {
        setTrackSegmentBlock(TURNOUT_D, false);
    }
}

/**
 * Update the block for a track segment that provides a short connection
 * between a turnout and another object, normally another turnout. These are
 * hard to see and are frequently missed.
 * <p>
 * Skip block changes if signal heads, masts or sensors have been assigned.
 * Only track segments with a length less than the turnout circle radius
 * will be changed.
 *
 * @since 4.11.6
 * @param pointType   The point type which indicates which turnout
 *                    connection.
 * @param isAutomatic True for the automatically generated track segment
 *                    created by the drag-n-drop process. False for existing
 *                    connections which require a track segment length
 *                    calculation.
 */
void LayoutTurnout::setTrackSegmentBlock(int pointType, bool isAutomatic) {
    TrackSegment* trkSeg;
    QPointF pointCoord;
    LayoutBlock* currBlk = block;
    bool xOver = getTurnoutType() > WYE_TURNOUT && getTurnoutType() < SINGLE_SLIP;
    switch (pointType) {
        case TURNOUT_A:
        case SLIP_A:
            if (signalA1HeadNamed != nullptr) {
                return;
            }
            if (signalA2HeadNamed != nullptr) {
                return;
            }
            if (signalA3HeadNamed != nullptr) {
                return;
            }
            if (getSignalAMast() != nullptr) {
                return;
            }
            if (getSensorA() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) connectA;
            pointCoord = getCoordsA();
            break;
        case TURNOUT_B:
        case SLIP_B:
            if (signalB1HeadNamed != nullptr) {
                return;
            }
            if (signalB2HeadNamed != nullptr) {
                return;
            }
            if (getSignalBMast() != nullptr) {
                return;
            }
            if (getSensorB() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) connectB;
            pointCoord = getCoordsB();
            if (xOver) {
                currBlk = blockB != nullptr ? blockB : block;
            }
            break;
        case TURNOUT_C:
        case SLIP_C:
            if (signalC1HeadNamed != nullptr) {
                return;
            }
            if (signalC2HeadNamed != nullptr) {
                return;
            }
            if (getSignalCMast() != nullptr) {
                return;
            }
            if (getSensorC() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) connectC;
            pointCoord = getCoordsC();
            if (xOver) {
                currBlk = blockC != nullptr ? blockC : block;
            }
            break;
        case TURNOUT_D:
        case SLIP_D:
            if (signalD1HeadNamed != nullptr) {
                return;
            }
            if (signalD2HeadNamed != nullptr) {
                return;
            }
            if (getSignalDMast() != nullptr) {
                return;
            }
            if (getSensorD() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) connectD;
            pointCoord = getCoordsD();
            if (xOver) {
                currBlk = blockD != nullptr ? blockD : block;
            }
            break;
        default:
            log->error(tr("setTrackSegmentBlock: Invalid pointType: %1").arg(pointType));
            return;
    }
    if (trkSeg != nullptr) {
        double chkSize = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
        double segLength = 0;
        if (!isAutomatic) {
            QPointF segCenter = trkSeg->getCoordsCenter();
            segLength = MathUtil::distance(pointCoord, segCenter) * 2;
        }
        if (segLength < chkSize) {
            if (log->isDebugEnabled()) {
                log->debug("Set block:");
                log->debug(tr("    seg: %1").arg(trkSeg->getName()));
                log->debug(tr("    cor: %1,%2").arg(pointCoord.x()).arg(pointCoord.y()));
                log->debug(tr("    blk: %1").arg((currBlk == nullptr) ? "nullptr" : currBlk->getDisplayName()));
                log->debug(tr("    len: %1").arg(segLength));
            }

            trkSeg->setLayoutBlock(currBlk);
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
        }
    }
}

/**
 * Methods to test if turnout legs are mainline track or not
 *  Returns true if connecting track segment is mainline
 *  Defaults to not mainline if connecting track segment is missing
 */
/*public*/ bool LayoutTurnout::isMainlineA()
{
 if (connectA != nullptr)
 {
     return ((TrackSegment*)connectA)->isMainline();
 }
 else {
  // if no connection, depends on type of turnout
  if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) )
  {
   // All crossovers - straight continuing is B
   if (connectB != nullptr)
       return ((TrackSegment*)connectB)->isMainline();
  }
  else if ((getTurnoutType() == SINGLE_SLIP)
                      || (getTurnoutType() == DOUBLE_SLIP))
  {
   if (connectD != nullptr) {
       return ((TrackSegment*) connectD)->isMainline();
   }
  } // must be RH, LH, or WYE turnout - A is the switch throat
  else if ( ((connectB != nullptr) &&
          (((TrackSegment*)connectB)->isMainline())) ||
              ((connectC != nullptr) &&
                  (((TrackSegment*)connectC)->isMainline())) )
      return true;
 }
 return false;
}

/*public*/ bool LayoutTurnout::isMainlineB()
{
 if (connectB != nullptr)
 {
     return ((TrackSegment*)connectB)->isMainline();
 }
 else {
  // if no connection, depends on type of turnout
  if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) )
  {
      // All crossovers - straight continuing is A
      if (connectA != nullptr)
          return ((TrackSegment*)connectA)->isMainline();
  } else if (getTurnoutType() == DOUBLE_SLIP)
  {
   if (connectD != nullptr)
   {
       return ((TrackSegment*) connectD)->isMainline();
   }
  } // must be RH, LH, or WYE turnout - A is the switch throat,
  //		B is normally the continuing straight
  else if (continuingSense == Turnout::CLOSED)
  {
   // user hasn't changed the continuing turnout state
   if (connectA != nullptr)
   { // if throat is mainline, this leg must be also
       return ((TrackSegment*)connectA)->isMainline();
   }
  }
 }
 return false;
}
/*public*/ bool LayoutTurnout::isMainlineC()
{
 if (connectC != nullptr)
 {
        return ((TrackSegment*)connectC)->isMainline();
 }
 else
 {
  // if no connection, depends on type of turnout
  if ( (type==DOUBLE_XOVER) || (type==LH_XOVER) || (type==RH_XOVER) )
  {
   // All crossovers - straight continuing is D
   if (connectD != nullptr)
       return ((TrackSegment*)connectD)->isMainline();
  } else if (getTurnoutType() == DOUBLE_SLIP)
  {
   if (connectB != nullptr)
   {
       return ((TrackSegment*) connectB)->isMainline();
   }
  } // must be RH, LH, or WYE turnout - A is the switch throat,
  //		B is normally the continuing straight
  else if (continuingSense == Turnout::THROWN)
  {
   // user has changed the continuing turnout state
   if (connectA != nullptr)
   {    // if throat is mainline, this leg must be also
       return ((TrackSegment*)connectA)->isMainline();
   }
  }
 }
 return false;
}
/*public*/ bool LayoutTurnout::isMainlineD()
{
 // this is a crossover turnout
 if (connectD != nullptr)
 {
  return ((TrackSegment*)connectD)->isMainline();
 }
 else if ((getTurnoutType() == SINGLE_SLIP)
             || (getTurnoutType() == DOUBLE_SLIP))
 {
  if (connectB != nullptr) {
      return ((TrackSegment*) connectB)->isMainline();
  }
 } else if (connectC != nullptr) {
     return ((TrackSegment*)connectC)->isMainline();
 }
 return false;
}

//@Override
/*public*/ bool LayoutTurnout::isMainline() {
    return (isMainlineA() || isMainlineB() || isMainlineC() || isMainlineD());
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ int LayoutTurnout::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    int result = NONE;  // assume point not on connection
    //note: optimization here: instead of creating rectangles for all the
    // points to check below, we create a rectangle for the test point
    // and test if the points below are in that rectangle instead.
    QRectF r = layoutEditor->trackControlCircleRectAt(hitPoint);
    QPointF p, minPoint = MathUtil::zeroPoint2D;

    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double distance, minDistance = std::numeric_limits<double>::infinity();//POSITIVE_INFINITY;

    // check center coordinates
    if (!requireUnconnected) {
        p = getCoordsCenter();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = TURNOUT_CENTER;
        }
    }

    //check the A connection point
    if (!requireUnconnected || (getConnectA() == nullptr)) {
        p = getCoordsA();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = TURNOUT_A;
        }
    }

    //check the B connection point
    if (!requireUnconnected || (getConnectB() == nullptr)) {
        p = getCoordsB();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = TURNOUT_B;
        }
    }

    //check the C connection point
    if (!requireUnconnected || (getConnectC() == nullptr)) {
        p = getCoordsC();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = TURNOUT_C;
        }
    }

    //check the D connection point
    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == LH_XOVER)
            || (getTurnoutType() == RH_XOVER)) {
        if (!requireUnconnected || (getConnectD() == nullptr)) {
            p = getCoordsD();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = TURNOUT_D;
            }
        }
    }
    if ((useRectangles && !r.contains(minPoint))
            || (!useRectangles && (minDistance > circleRadius))) {
        result = NONE;
    }
    return result;
}   // findHitPointType

/**
 * Modify coordinates methods
 */
/*public*/ void LayoutTurnout::setCoordsCenter(QPointF p) {
    center = p;
}

/*private*/ void LayoutTurnout::reCalculateCenter() {
    center = MathUtil::midPoint(pointA, pointC);
}

/*public*/ void LayoutTurnout::setCoordsA(QPointF p) {
 pointA = p;
 if (version == 2) {
     reCalculateCenter();
 }
 double x = center.x() - p.x();
 double y = center.y() - p.y();
 if (getTurnoutType() == DOUBLE_XOVER) {
     dispA = QPointF(x, y);
     // adjust to maintain rectangle
     double oldLength = MathUtil::length(dispB);
     //double newLength = qHypot(x, y);
     double newLength = qSqrt(x*x + y*y);
     dispB = MathUtil::multiply(dispB, newLength / oldLength);
 } else if ((getTurnoutType() == RH_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     dispA = QPointF(x, y);
     // adjust to maintain the parallelogram
     double a = 0.0;
     double b = -y;
     double xi = 0.0;
     double yi = b;
     if ((dispB.x() + x) != 0.0) {
         a = (dispB.y() + y) / (dispB.x() + x);
         b = -y + (a * x);
         xi = -b / (a + (1.0 / a));
         yi = (a * xi) + b;
     }
     if (getTurnoutType() == RH_XOVER) {
         x = xi - (0.333333 * (-x - xi));
         y = yi - (0.333333 * (-y - yi));
     } else if (getTurnoutType() == LH_XOVER) {
         x = xi - (3.0 * (-x - xi));
         y = yi - (3.0 * (-y - yi));
     }
     dispB = QPointF(x, y);
 } else if (getTurnoutType() == WYE_TURNOUT) {
     // modify both to maintain same angle at wye
     double temX = (dispB.x() + dispA.x());
     double temY = (dispB.y() + dispA.y());
     double temXx = (dispB.x() - dispA.x());
     double temYy = (dispB.y() - dispA.y());
     double tan = qSqrt(((temX * temX) + (temY * temY))
             / ((temXx * temXx) + (temYy * temYy)));
     double xx = x + (y / tan);
     double yy = y - (x / tan);
     dispA = QPointF(xx, yy);
     xx = x - (y / tan);
     yy = y + (x / tan);
     dispB = QPointF(xx, yy);
 } else {
     dispB = QPointF(x, y);
 }
}
/*public*/ void LayoutTurnout::setCoordsB(QPointF p) {
 pointB = p;
 double x = center.x() - p.x();
 double y = center.y() - p.y();
 dispB = QPointF(-x, -y);
 if ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == WYE_TURNOUT)) {
     // adjust to maintain rectangle or wye shape
     double oldLength = MathUtil::length(dispA);
     //double newLength = Math.hypot(x, y);
     double newLength  = qSqrt(x*x + y*y);
     dispA = MathUtil::multiply(dispA, newLength / oldLength);
 } else if ((getTurnoutType() == RH_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     // adjust to maintain the parallelogram
     double a = 0.0;
     double b = y;
     double xi = 0.0;
     double yi = b;
     if ((dispA.x() - x) != 0.0) {
         if ((-dispA.x() + x) == 0) {
             /* we can in some situations eg 90' vertical end up with a 0 value,
             so hence remove a small amount so that we
             don't have a divide by zero issue */
             x = x - 0.0000000001;
         }
         a = (dispA.y() - y) / (dispA.x() - x);
         b = y - (a * x);
         xi = -b / (a + (1.0 / a));
         yi = (a * xi) + b;
     }
     if (getTurnoutType() == LH_XOVER) {
         x = xi - (0.333333 * (x - xi));
         y = yi - (0.333333 * (y - yi));
     } else if (getTurnoutType() == RH_XOVER) {
         x = xi - (3.0 * (x - xi));
         y = yi - (3.0 * (y - yi));
     }
     dispA = QPointF(x, y);
 }
}
/*public*/ void LayoutTurnout::setCoordsC(QPointF p) {
 pointC = p;
 if (version == 2) {
     reCalculateCenter();
 }
 double x = center.x() - p.x();
 double y = center.y() - p.y();
 dispA = QPointF(-x, -y);
 if ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == WYE_TURNOUT)) {
     // adjust to maintain rectangle or wye shape
     double oldLength = MathUtil::length(dispB);
     //double newLength = Math.hypot(x, y);
     double newLength  = qSqrt(x*x + y*y);
     dispB = MathUtil::multiply(dispB, newLength / oldLength);
 } else if ((getTurnoutType() == RH_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     double a = 0.0;
     double b = -y;
     double xi = 0.0;
     double yi = b;
     if ((dispB.x() + x) != 0.0) {
         if ((-dispB.x() + x) == 0) {
             /* we can in some situations eg 90' vertical end up with a 0 value,
             so hence remove a small amount so that we
             don't have a divide by zero issue */

             x = x - 0.0000000001;
         }
         a = (-dispB.y() + y) / (-dispB.y() + x);
         b = -y + (a * x);
         xi = -b / (a + (1.0 / a));
         yi = (a * xi) + b;
     }
     if (getTurnoutType() == RH_XOVER) {
         x = xi - (0.333333 * (-x - xi));
         y = yi - (0.333333 * (-y - yi));
     } else if (getTurnoutType() == LH_XOVER) {
         x = xi - (3.0 * (-x - xi));
         y = yi - (3.0 * (-y - yi));
     }
     dispB = QPointF(-x, -y);
 }
}

/*public*/ void LayoutTurnout::setCoordsD(QPointF p) {
 pointD = p;

 // only used for crossovers
 double x = center.x() - p.x();
 double y = center.y() - p.y();
 dispB = QPointF(x, y);
 if (getTurnoutType() == DOUBLE_XOVER) {
     // adjust to maintain rectangle
     double oldLength = MathUtil::length(dispA);
     //double newLength = Math.hypot(x, y);
     double newLength  = qSqrt(x*x + y*y);
     dispA = MathUtil::multiply(dispA, newLength / oldLength);
 } else if ((getTurnoutType() == RH_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     // adjust to maintain the parallelogram
     double a = 0.0;
     double b = y;
     double xi = 0.0;
     double yi = b;
     if ((dispA.x() + x) != 0.0) {
         a = (dispA.y() + y) / (dispA.x() + x);
         b = -y + (a * x);
         xi = -b / (a + (1.0 / a));
         yi = (a * xi) + b;
     }
     if (getTurnoutType() == LH_XOVER) {
         x = xi - (0.333333 * (-x - xi));
         y = yi - (0.333333 * (-y - yi));
     } else if (getTurnoutType() == RH_XOVER) {
         x = xi - (3.0 * (-x - xi));
         y = yi - (3.0 * (-y - yi));
     }
     dispA = QPointF(x, y);
 }
}
/*public*/ void LayoutTurnout::scaleCoords(double xFactor, double yFactor) {
    QPointF pt =  QPointF(round(center.x()*xFactor),
                                    round(center.y()*yFactor));
    center = pt;
    pt =  QPointF(round(dispB.x()*xFactor),
                                    round(dispB.y()*yFactor));
    dispB = pt;
    pt =  QPointF(round(dispA.x()*xFactor),
                                    round(dispA.y()*yFactor));
    dispA = pt;
}

//class MTurnoutListener : public PropertyChangeListener
//{
// Q_OBJECT
// LayoutTurnout* layoutTurnout;
//public:
// MTurnoutListener(LayoutTurnout* layoutTurnout) {this->layoutTurnout = layoutTurnout;}
//public slots:
 void MTurnoutListener::propertyChange(PropertyChangeEvent* e)
 {
  if (layoutTurnout->secondNamedTurnout != nullptr) {
      int new2ndState = layoutTurnout->secondNamedTurnout->getBean()->getState();
      if (e->getSource() == (layoutTurnout->secondNamedTurnout->getBean())
      && e->getNewValue().toInt() == (new2ndState)) {
          int old1stState = layoutTurnout->namedTurnout->getBean()->getState();
          int new1stState = new2ndState;
          if (layoutTurnout->secondTurnoutInverted) {
              new1stState = Turnout::invertTurnoutState(new1stState);
          }
          if (old1stState != new1stState) {
              layoutTurnout->namedTurnout->getBean()->setCommandedState(new1stState);
          }
      }
  }
  layoutTurnout->layoutEditor->redrawPanel();

 }
//};

/**
 * Activate/Deactivate turnout to redraw when turnout state changes
 */
/*private*/ void LayoutTurnout::activateTurnout()
{
#if 0
 if (namedTurnout!=nullptr)
 {
  //namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener =
//          new PropertyChangeListener(), namedTurnout->getName(),"Layout Editor Turnout");
//        {
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                layoutEditor.redrawPanel();
//            }
//        }, namedTurnout.getName(), "Layout Editor Turnout");
  namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener = new MTurnoutListener(this), namedTurnout->getName(), "Layout Editor Turnout");
//  AbstractTurnout* t = (AbstractTurnout*)namedTurnout->getBean();
//  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(redrawPanel()));
 }
 if (secondNamedTurnout!=nullptr)
 {
  secondNamedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener, secondNamedTurnout->getName(), "Layout Editor Turnout");
//  connect(secondNamedTurnout->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(redrawPanel()));
 }
#else
 if (namedTurnout != nullptr)
 {
//     namedTurnout.getBean().addPropertyChangeListener(
//             mTurnoutListener = (java.beans.PropertyChangeEvent e) -> {
//                 if (secondNamedTurnout != null) {
//                     int new2ndState = secondNamedTurnout.getBean().getState();
//                     if (e.getSource().equals(secondNamedTurnout.getBean())
//                     && e.getNewValue().equals(new2ndState)) {
//                         int old1stState = namedTurnout.getBean().getState();
//                         int new1stState = new2ndState;
//                         if (secondTurnoutInverted) {
//                             new1stState = Turnout.invertTurnoutState(new1stState);
//                         }
//                         if (old1stState != new1stState) {
//                             namedTurnout.getBean().setCommandedState(new1stState);
//                         }
//                     }
//                 }
//                 layoutEditor.redrawPanel();
//             },
//             namedTurnout.getName(),
//             "Layout Editor Turnout"
//     );
  namedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener = new MTurnoutListener(this), namedTurnout->getName(),  "Layout Editor Turnout");
 }
 if (secondNamedTurnout != nullptr) {
     secondNamedTurnout->getBean()->addPropertyChangeListener(mTurnoutListener, secondNamedTurnout->getName(), "Layout Editor Turnout");
 }
#endif
}

/*private*/ void LayoutTurnout::deactivateTurnout()
{
 if (mTurnoutListener!=nullptr)
 {
  namedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
  if(secondNamedTurnout!=nullptr)
  {
   secondNamedTurnout->getBean()->removePropertyChangeListener(mTurnoutListener);
  }
  mTurnoutListener = nullptr;
 }
}

/**
 * Toggle turnout if clicked on, physical turnout exists, and
 *    not disabled
 */
/*public*/ void LayoutTurnout::toggleTurnout()
{
 if (getTurnout() != nullptr) {
     // toggle turnout
     if (getTurnout()->getKnownState() == Turnout::CLOSED) {
         setState(Turnout::THROWN);
     } else {
         setState(Turnout::CLOSED);
     }
//     invalidate(layoutEditor->editScene);
 } else {
     log->debug("Turnout Icon not associated with a Turnout");
 }
}

/*public*/ void LayoutTurnout::setState(int state) {
 if ((getTurnout() != nullptr) && !disabled) {
     if (disableWhenOccupied && isOccupied()) {
         log->debug("Turnout not changed as Block is Occupied");
     } else {
         getTurnout()->setCommandedState(state);
         if (getSecondTurnout() != nullptr) {
             if (secondTurnoutInverted) {
                 if (state == Turnout::CLOSED) {
                     getSecondTurnout()->setCommandedState(Turnout::THROWN);
                 } else {
                     getSecondTurnout()->setCommandedState(Turnout::CLOSED);
                 }
             } else {
                 getSecondTurnout()->setCommandedState(state);
             }
         }
     }
 }
}

/*public*/ int LayoutTurnout::getState() {
 int result = UNKNOWN;
 if (getTurnout() != nullptr) {
     result = getTurnout()->getKnownState();
 }
 return result;
}

/**
* is this turnout occupied?
*
* @return true if occupied
*/
/*private*/ bool LayoutTurnout::isOccupied() {
 if ((getTurnoutType() == RH_TURNOUT)
         || (getTurnoutType() == LH_TURNOUT)
         || (getTurnoutType() == WYE_TURNOUT)) {
     if (getLayoutBlock()->getOccupancy() == LayoutBlock::OCCUPIED) {
         log->debug("Block " + getBlockName() + "is Occupied");
         return true;
     }
 }
 if ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == RH_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     //If the turnout is set for straight over, we need to deal with the straight over connecting blocks
     if (getTurnout()->getKnownState() == Turnout::CLOSED) {
         if ((getLayoutBlock()->getOccupancy() == LayoutBlock::OCCUPIED)
                 && (getLayoutBlockB()->getOccupancy() == LayoutBlock::OCCUPIED)) {
             log->debug("Blocks " + getBlockName() + " & " + getBlockBName() + " are Occupied");
             return true;
         }
         if ((getLayoutBlockC()->getOccupancy() == LayoutBlock::OCCUPIED)
                 && (getLayoutBlockD()->getOccupancy() == LayoutBlock::OCCUPIED)) {
             log->debug("Blocks " + getBlockCName() + " & " + getBlockDName() + " are Occupied");
             return true;
         }
     }

 }
 if ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == LH_XOVER)) {
     if (getTurnout()->getKnownState() == Turnout::THROWN) {
         if ((getLayoutBlockB()->getOccupancy() == LayoutBlock::OCCUPIED)
                 && (getLayoutBlockD()->getOccupancy() == LayoutBlock::OCCUPIED)) {
             log->debug("Blocks " + getBlockBName() + " & " + getBlockDName() + " are Occupied");
             return true;
         }
     }
 }

 if ((getTurnoutType() == DOUBLE_XOVER)
         || (getTurnoutType() == RH_XOVER)) {
     if (getTurnout()->getKnownState() == Turnout::THROWN) {
         if ((getLayoutBlock()->getOccupancy() == LayoutBlock::OCCUPIED)
                 && (getLayoutBlockC()->getOccupancy() == LayoutBlock::OCCUPIED)) {
             log->debug(tr("Blocks ") + getLayoutBlock()->getDisplayName() + " & " + getBlockCName() + " are Occupied");
             return true;
         }
     }
 }
 return false;
}   // isOccupied

/*private*/ bool LayoutTurnout::disableOccupiedTurnout()
{
 if ((type==RH_TURNOUT) || (type==LH_TURNOUT) || (type==WYE_TURNOUT))
 {
  if(block == nullptr) return false;
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
  connectA = p->getFinder()->findTrackSegmentByName(connectAName);
  connectB = p->getFinder()->findTrackSegmentByName(connectBName);
  connectC = p->getFinder()->findTrackSegmentByName(connectCName);
  connectD = p->getFinder()->findTrackSegmentByName(connectDName);

  LayoutBlock* lb;
  if (!tBlockAName.isEmpty())
  {
      lb = p->provideLayoutBlock(tBlockAName);
      if (lb != nullptr) {
          QString userName = lb->getUserName();
          if (userName != nullptr) {
              namedLayoutBlockA = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
              lb->incrementUse();
          }
      } else {
          log->error(tr("bad blockname '%1' in layoutturnout %2").arg(tBlockAName).arg(getId()));
          namedLayoutBlockA = nullptr;
      }
      tBlockAName = nullptr; //release this memory
  }

  if (!tBlockBName.isEmpty()) {
      lb = p->provideLayoutBlock(tBlockBName);
      if (lb != nullptr) {
          QString userName = lb->getUserName();
          if (!userName.isNull()) {
              namedLayoutBlockB = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
          }
          if (namedLayoutBlockB != namedLayoutBlockA) {
              lb->incrementUse();
          }
      } else {
          log->error(tr("bad blockname '%1' in layoutturnout %2").arg(tBlockBName).arg(getId()));
          namedLayoutBlockB = nullptr;
      }
      tBlockBName = nullptr; //release this memory
  }

  if (!tBlockCName.isEmpty()) {
      lb = p->provideLayoutBlock(tBlockCName);
      if (lb != nullptr) {
          QString userName = lb->getUserName();
          if (!userName.isNull()) {
              namedLayoutBlockC = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
          }
          if ((namedLayoutBlockC != namedLayoutBlockA)
                  && (namedLayoutBlockC != namedLayoutBlockB)) {
              lb->incrementUse();
          }
      } else {
          log->error(tr("bad blockname '%1' in layoutturnout %2").arg(tBlockCName).arg(getId()));
          namedLayoutBlockC = nullptr;
      }
      tBlockCName = nullptr; // release this memory
  }

  if (!tBlockDName.isEmpty()) {
      lb = p->provideLayoutBlock(tBlockDName);
      if (lb != nullptr) {
          QString userName = lb->getUserName();
          if (userName != nullptr) {
              namedLayoutBlockD = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(userName, lb);
          }
          if ((namedLayoutBlockD != namedLayoutBlockA)
                  && (namedLayoutBlockD != namedLayoutBlockB)
                  && (namedLayoutBlockD != namedLayoutBlockC)) {
              lb->incrementUse();
          }
      } else {
          log->error(tr("bad blockname '%1' in layoutturnout %2").arg(tBlockDName).arg(getId()));
          namedLayoutBlockD = nullptr;
      }
      tBlockDName = nullptr; //release this memory
  }
  activateTurnout();
} // setObjects


/**
 * Display popup menu for information and editing
 */
/*protected*/ QMenu *LayoutTurnout::showPopup(QGraphicsSceneMouseEvent* /*e*/)
{
  // TODO: incorporate latest Java code!!

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
  switch (getTurnoutType())
  {
   case RH_TURNOUT:
    //popup.add(tr("RHTurnout"));
    //actionRHTurnout = new QAction(tr("RHTurnout"), this);
    popup->addSection(tr("RH Turnout"));
    break;
   case LH_TURNOUT:
    //popup.add(tr("LHTurnout"));
    //actionLHTurnout = new QAction(tr("LHTurnout"), this);
    popup->addSection(tr("LH Turnout"));
    break;
   case WYE_TURNOUT:
   //popup.add(tr("WYETurnout"));
    //actionWYETurnout = new QAction(tr("WYETurnout"), this);
      popup->addSection(tr("WYETurnout"));
    break;
   case DOUBLE_XOVER:
    //popup.add(tr("XOverTurnout"));
    //actionXOverTurnout = new QAction(tr("Double Crossover"), this);
      popup->addSection(tr("Double Crossover"));
    break;
   case RH_XOVER:
    //popup.add(tr("RHXOverTurnout"));
    //actionRHXOverTurnout = new QAction(tr("Right-Hand Crossover "), this);
    popup->addSection(tr("Right-Hand Crossover "));
    break;
   case LH_XOVER:
    //popup.add(tr("LHXOverTurnout"));
    //actionLHXOverTurnout = new QAction(tr("Left-Hand Crossover "), this);
    popup->addSection(tr("Left-Hand Crossover "));
    break;
   default : break;
  }
  //popup.add(ident);
  QAction* jmi;

  if (getTurnout()==nullptr)
  {
   //popup.add(tr("NoTurnout"));
   jmi = popup->addSection(tr("No Turnout set"));
  }
  else
  {
   //popup.add(tr("Turnout")+": "+turnoutName);
   QString stateString = getTurnoutStateString(getTurnout()->getKnownState());
   stateString = tr(" (%1)").arg(stateString);
   jmi = popup->addSection(QString("Turnout")+": "+getTurnoutName() + stateString);
  }
  jmi->setEnabled(false);

  if (getSecondTurnout() != nullptr) {
      QString stateString = getTurnoutStateString(getSecondTurnout()->getKnownState());
      stateString = tr(" (%1)").arg(stateString);
      jmi = popup->addSection(tr("Supporting %1:").arg(
             tr("Turnout"))
              + ": " + getSecondTurnoutName() + stateString);
  }
  jmi->setEnabled(false);

  QAction* act;

  // if there are any track connections
  if ((connectA != nullptr) || (connectB != nullptr)
          || (connectC != nullptr) || (connectD != nullptr)) {
      QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
      if (connectA != nullptr)
      {
          connectionsMenu->addAction(act = new AbstractAction("A" + connectA->getName(),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  LayoutEditorFindItems* lf = layoutEditor->getFinder();
                  LayoutTrack* lt = lf->findObjectByName(connectA->getName());
                  // this shouldn't ever be null... however...
                  if (lt != nullptr) {
                      layoutEditor->setSelectionRect(lt->getBounds());
                      lt->showPopup();
                  }
//              }
          });
      }
      if (connectB != nullptr) {
          connectionsMenu->addAction(act = new AbstractAction( "B" + connectB->getName(),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
            connect(act, &QAction::triggered, [=]{
                  LayoutEditorFindItems* lf = layoutEditor->getFinder();
                  LayoutTrack* lt = lf->findObjectByName(connectB->getName());
                  // this shouldn't ever be null... however...
                  if (lt != nullptr) {
                      layoutEditor->setSelectionRect(lt->getBounds());
                      lt->showPopup();
                  }
//              }
          });
      }
      if (connectC != nullptr) {
          connectionsMenu->addAction(act = new AbstractAction( "C" + connectC->getName(),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
          connect(act, &QAction::triggered, [=]{
                  LayoutEditorFindItems* lf = layoutEditor->getFinder();
                  LayoutTrack* lt = lf->findObjectByName(connectC->getName());
                  // this shouldn't ever be null... however...
                  if (lt != nullptr) {
                      layoutEditor->setSelectionRect(lt->getBounds());
                      lt->showPopup();
                  }
//              }
          });
      }
      if (connectD != nullptr) {
          connectionsMenu->addAction(jmi = new AbstractAction("D" + connectD->getName(),this));
          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
           connect(act, &QAction::triggered, [=]{
                  LayoutEditorFindItems* lf = layoutEditor->getFinder();
                  LayoutTrack* lt = lf->findObjectByName(connectD->getName());
                  // this shouldn't ever be null... however...
                  if (lt != nullptr) {
                      layoutEditor->setSelectionRect(lt->getBounds());
                      lt->showPopup();
                  }
//              }
          });
      }
      popup->addMenu(connectionsMenu);
  }
  popup->addSeparator(); //new JSeparator(JSeparator.HORIZONTAL));

  QAction* hiddenCheckBoxMenuItem = new QAction(tr("Hidden"),this);
  hiddenCheckBoxMenuItem->setCheckable(true);
  hiddenCheckBoxMenuItem->setChecked(hidden);
  popup->addAction(hiddenCheckBoxMenuItem);
  //hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e1) -> {
  connect(hiddenCheckBoxMenuItem, &QAction::triggered, [=]{
//      JCheckBoxMenuItem o = (JCheckBoxMenuItem) e1.getSource();
      setHidden(hiddenCheckBoxMenuItem->isChecked());
  });

  QAction* cbmi = new QAction(tr("Disabled"), this);
  cbmi->setCheckable(true);
  cbmi->setChecked(disabled);
  popup->addAction(cbmi);
  //cbmi.addActionListener((java.awt.event.ActionEvent e2) -> {
  connect(cbmi, &QAction::triggered, [=]{
//      JCheckBoxMenuItem o = (JCheckBoxMenuItem) e2.getSource();
      setDisabled(cbmi->isChecked());
  });

  cbmi = new QAction(tr("Disable When Occupied"),this);
  cbmi->setCheckable(true);
  if (getTurnout() == nullptr || getBlockName().isEmpty()) {
      cbmi->setEnabled(false);
  }
  cbmi->setChecked(disableWhenOccupied);
  popup->addAction(cbmi);
//  cbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//      JCheckBoxMenuItem o = (JCheckBoxMenuItem) e3.getSource();
  connect(cbmi, &QAction::triggered, [=]{
      setDisableWhenOccupied(cbmi->isChecked());
  });

  // Rotate if there are no track connections
  if ((connectA == nullptr) && (connectB == nullptr)
          && (connectC == nullptr)
          && (connectD == nullptr))
  {
      QAction* rotateItem = new QAction(tr("Rotate") + "...",this);
      popup->addAction(rotateItem);
//      rotateItem.addActionListener((ActionEvent event) -> {
      connect(rotateItem, &QAction::triggered, [=]{
          bool entering = true;
          bool error = false;
          QString newAngle = "";
          while (entering) {
              // prompt for rotation angle
              error = false;
              newAngle = JOptionPane::showInputDialog(layoutEditor,
                      tr("Enter Rotation Angle (degrees CW)"));
              if (newAngle.isEmpty()) {
                  return;  // cancelled
              }
              double rot = 0.0;
              bool bok;
                  rot = newAngle.toDouble(&bok);
              if(!bok) {
                  JOptionPane::showMessageDialog(layoutEditor, tr("Error in rotation entry:")
                          + " " /*+ e1*/, tr("Error"), JOptionPane::ERROR_MESSAGE);
                  error = true;
                  newAngle = "";
              }
              if (!error) {
                  entering = false;
                  if (rot != 0.0) {
                      rotateCoords(rot);
                      layoutEditor->redrawPanel();
                  }
              }
          }
      });
  }

  popup->addAction(act = new AbstractAction(tr("Use Size As Default"),this));
//  {
//      @Override
//      public void actionPerformed(ActionEvent e) {
  connect(act, &QAction::triggered, [=]{
          setUpDefaultSize();
//      }
  });
  popup->addAction(act = new AbstractAction(tr("Edit"),this));
//  {
//      @Override
//      public void actionPerformed(ActionEvent e) {
  connect(act, &QAction::triggered, [=]{
          //layoutEditor->getLayoutTrackEditors()->editLayoutTurnout(this);
      editor->editLayoutTrack(this);
//      }
  });
  popup->addAction(act = new AbstractAction(tr("Delete"),this));
//  {
//      @Override
//      public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
          if (canRemove() && layoutEditor->removeLayoutTurnout(this)) {
              // Returned true if user did not cancel
              remove();
              dispose();
          }
//      }
  });

  if (getTurnout() != nullptr)
  {
      AbstractAction* ssaa = new AbstractAction(tr("Set Signal Heads..."),this);
//      {
//          @Override
//          public void actionPerformed(ActionEvent e) {
      connect(ssaa, &AbstractAction::triggered, [=]{
              LayoutEditorTools* tools = layoutEditor->getLETools();
              LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
              if (isTurnoutTypeXover()) {
                  tools->setSignalsAtXoverTurnoutFromMenu(this,
                          letbp->signalIconEditor, letbp->signalFrame);
              } else if (linkType == NO_LINK) {
                  tools->setSignalsAtTurnoutFromMenu(this,
                          letbp->signalIconEditor, letbp->signalFrame);
              } else if (linkType == THROAT_TO_THROAT) {
                  tools->setSignalsAtThroatToThroatTurnoutsFromMenu(this, linkedTurnoutName,
                          letbp->signalIconEditor, letbp->signalFrame);
              } else if (linkType == FIRST_3_WAY) {
                  tools->setSignalsAt3WayTurnoutFromMenu(getTurnoutName(), linkedTurnoutName,
                          letbp->signalIconEditor, letbp->signalFrame);
              } else if (linkType == SECOND_3_WAY) {
                  tools->setSignalsAt3WayTurnoutFromMenu(linkedTurnoutName, getTurnoutName(),
                          letbp->signalIconEditor, letbp->signalFrame);
              }
//          }
      });

      QMenu* jm = new QMenu(tr("Set Signal Heads..."));
      if (layoutEditor->getLETools()->addLayoutTurnoutSignalHeadInfoToMenu(
              getTurnoutName(), linkedTurnoutName, jm)) {
          jm->addAction(ssaa);
          popup->addMenu(jm);
      } else {
          popup->addAction(ssaa);
      }
  }
  if (!getBlockName().isEmpty())
  {
      /*final*/ QStringList boundaryBetween = getBlockBoundaries();
      bool blockBoundaries = false;
      for (int i = 0; i < 4; i++) {
          if (boundaryBetween[i] != "") {
              blockBoundaries = true;

          }
      }

      if (blockBoundaries) {
          popup->addAction(act = new AbstractAction(tr("Set Signal Masts..."),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
           connect(act, &QAction::triggered, [=]{

                  layoutEditor->getLETools()->setSignalMastsAtTurnoutFromMenu(this,
                          boundaryBetween);
//              }
          });
          popup->addAction(act =new AbstractAction(tr("Set Sensors..."),this));
//          {
//              @Override
//              public void actionPerformed(ActionEvent e) {
           connect(act, &QAction::triggered, [=]{
                  LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
                  layoutEditor->getLETools()->setSensorsAtTurnoutFromMenu(
                          this,
                          boundaryBetween,
                          letbp->sensorIconEditor,
                          letbp->sensorFrame);
//              }
          });

      }

      if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())
      {
          QMap<QString, LayoutBlock*> map = QMap<QString, LayoutBlock*>();
          if (!getBlockName().isEmpty()) {
              map.insert(getBlockName(), getLayoutBlock());
          }
          if (!getBlockBName().isEmpty()) {
              map.insert(getBlockBName(), getLayoutBlockB());
          }
          if (!getBlockCName().isEmpty()) {
              map.insert(getBlockCName(), getLayoutBlockC());
          }
          if (!getBlockDName().isEmpty()) {
              map.insert(getBlockDName(), getLayoutBlockD());
          }
          if (blockBoundaries)
          {
              if (map.size() == 1) {
                  popup->addAction(act = new AbstractAction(tr("View Block Routing"),this));
//                  {
//                      @Override
//                      public void actionPerformed(ActionEvent e) {
                   connect(act, &QAction::triggered, [=]{
                          AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("View Block Routing", getLayoutBlock());
                          routeTableAction->actionPerformed(/*e*/);
//                      }
                  });
              } else if (map.size() > 1) {
                  QMenu* viewRouting = new QMenu(tr("View Block Routing"));
                  //for (Map.Entry<String, LayoutBlock> entry : map.entrySet())
                  QMapIterator<QString, LayoutBlock*> entry(map);
                  while(entry.hasNext())
                  {
                   entry.next();
                      QString blockName = entry.key();
                      LayoutBlock* layoutBlock = entry.value();
                      viewRouting->addAction(new AbstractActionImpl(blockName, getBlockBName(), layoutBlock, this));
                  }
                  popup->addMenu(viewRouting);
              }
          }   // if (blockBoundaries)
      }   // .isAdvancedRoutingEnabled()
   }   // getBlockName().isEmpty()
   setAdditionalEditPopUpMenu(popup);
   layoutEditor->setShowAlignmentMenu(popup);
   //popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
   popup->exec(QCursor::pos());
 } else if (!viewAdditionalMenu->isEmpty()) {
   setAdditionalViewPopUpMenu(popup);
   //popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
   popup->exec(QCursor::pos());
 }
 return popup;
} // showPopup

 tools->setSensorsAtTurnoutFromMenu(this, boundaryBetween.toList(), layoutEditor->getLETools()->sensorIconEditor, layoutEditor->getLETools()->sensorFrame);
}


/*public*/ QStringList LayoutTurnout::getBlockBoundaries()
{
 ///*final*/ QStringList* boundaryBetween = new QStringList();
boundaryBetween = QVector<QString>(4);
 if ((type==WYE_TURNOUT) || (type ==RH_TURNOUT) || (type == LH_TURNOUT))
 {
  //This should only be needed where we are looking at a single Turnout::
  if(block!=nullptr)
  {
   LayoutBlock* aLBlock = nullptr;
   LayoutBlock* bLBlock = nullptr;
   LayoutBlock* cLBlock = nullptr;
#if 1 //TODO
   //if (connectA instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectA)!= nullptr)
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
   if(qobject_cast<TrackSegment*>(connectB)!= nullptr)
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
   //if ((connectC instanceof TrackSegment) && (((TrackSegment*)connectC).getLayoutBlock()!=block))
   if(qobject_cast<TrackSegment*>(connectC)!= nullptr && (((TrackSegment*)connectC)->getLayoutBlock()!=block))
   {
    cLBlock = ((TrackSegment*)connectC)->getLayoutBlock();
    if(cLBlock!=block)
    {
//     try
//     {
      if(cLBlock != nullptr)
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
  if(block!=nullptr)
   localblks.append(block);
  if(blockB!=nullptr)
   localblks.append(blockB);
  if(blockC!=nullptr)
   localblks.append(blockC);
  if(blockD!=nullptr)
   localblks.append(blockD);

  LayoutBlock* aLBlock = nullptr;
  LayoutBlock* bLBlock = nullptr;
  LayoutBlock* cLBlock = nullptr;
  LayoutBlock* dLBlock = nullptr;
  if(block!=nullptr)
  {
   //if (connectA instanceof TrackSegment)
   if(qobject_cast<TrackSegment*>(connectA)!=nullptr)
   {
    aLBlock =((TrackSegment*)connectA)->getLayoutBlock();
    if(aLBlock!=block)
    {
     if(aLBlock != nullptr)
      boundaryBetween.replace(0,aLBlock->getDisplayName()+ " - " + block->getDisplayName());
     else      //Can be considered normal if tracksegement hasn't yet been allocated a block
      log->debug("TrackSegement at connection A doesn't contain a layout block");
    }
    else if (block!=blockB)
    {
//     try
//     {
      if(blockB !=nullptr)
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
   if(qobject_cast<TrackSegment*>(connectB)!=nullptr)
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
      if(blockB!= nullptr)
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
   if(qobject_cast<TrackSegment*>(connectC)!=nullptr)
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
   if(qobject_cast<TrackSegment*>(connectD)!=nullptr)
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

/*public*/ QList<LayoutBlock*> LayoutTurnout::getProtectedBlocks(NamedBean* bean) {
     QList<LayoutBlock*> ret = QList<LayoutBlock*>();
     if (getLayoutBlock() == nullptr) {
         return ret;
     }
     if (getTurnoutType() >= DOUBLE_XOVER && getTurnoutType() <= LH_XOVER) {
         if ((getTurnoutType() == DOUBLE_XOVER || getTurnoutType() == RH_XOVER)
                 && (getSignalAMast() == bean || getSignalCMast() == bean || getSensorA() == bean || getSensorC() == bean)) {
             if (getSignalAMast() == bean || getSensorA() == bean) {
                 if (connectA != nullptr) {
                     if (((TrackSegment*) connectA)->getLayoutBlock() == getLayoutBlock()) {
                         if (getLayoutBlockB() != nullptr && getLayoutBlock() != getLayoutBlockB() && getLayoutBlockC() != nullptr && getLayoutBlock() != getLayoutBlockC()) {
                             ret.append(getLayoutBlockB());
                             ret.append(getLayoutBlockC());
                         }
                     } else {
                         ret.append(getLayoutBlock());
                     }
                 }
             } else {
                 if (connectC != nullptr && getLayoutBlockC() != nullptr) {
                     if (((TrackSegment*) connectC)->getLayoutBlock() == getLayoutBlockC()) {
                         if (getLayoutBlockC() != getLayoutBlock() && getLayoutBlockD() != nullptr && getLayoutBlockC() != getLayoutBlockD()) {
                             ret.append(getLayoutBlock());
                             ret.append(getLayoutBlockD());
                         }
                     } else {
                         ret.append(getLayoutBlockC());
                     }
                 }
             }
         }
         if ((getTurnoutType() == DOUBLE_XOVER || getTurnoutType() == LH_XOVER)
                 && (getSignalBMast() == bean || getSignalDMast() == bean || getSensorB() == bean || getSensorD() == bean)) {
             if (getSignalBMast() == bean || getSensorB() == bean) {
                 if (connectB != nullptr && getLayoutBlockB() != nullptr) {
                     if (((TrackSegment*) connectB)->getLayoutBlock() == getLayoutBlockB()) {
                         if (getLayoutBlock() != getLayoutBlockB() && getLayoutBlockD() != nullptr && getLayoutBlockB() != getLayoutBlockD()) {
                             ret.append(getLayoutBlock());
                             ret.append(getLayoutBlockD());
                         }
                     } else {
                         ret.append(getLayoutBlockB());
                     }
                 }
             } else {
                 if (connectD != nullptr && getLayoutBlockD() != nullptr) {
                     if (((TrackSegment*) connectD)->getLayoutBlock() == getLayoutBlockD()) {
                         if (getLayoutBlockB() != nullptr && getLayoutBlockB() != getLayoutBlockD() && getLayoutBlockC() != nullptr && getLayoutBlockC() != getLayoutBlockD()) {
                             ret.append(getLayoutBlockB());
                             ret.append(getLayoutBlockC());
                         }
                     } else {
                         ret.append(getLayoutBlockD());
                     }
                 }
             }
         }
         if (getTurnoutType() == RH_XOVER && (getSignalBMast() == bean
                 || getSignalDMast() == bean || getSensorB() == bean || getSensorD() == bean)) {
             if (getSignalBMast() == bean || getSensorB() == bean) {
                 if (connectB != nullptr && ((TrackSegment*) connectB)->getLayoutBlock() == getLayoutBlockB()) {
                     if (getLayoutBlockB() != getLayoutBlock()) {
                         ret.append(getLayoutBlock());
                     }
                 } else {
                     ret.append(getLayoutBlockB());
                 }
             } else {
                 if (connectD != nullptr && ((TrackSegment*) connectD)->getLayoutBlock() == getLayoutBlockD()) {
                     if (getLayoutBlockC() != getLayoutBlockD()) {
                         ret.append(getLayoutBlockC());
                     }
                 } else {
                     ret.append(getLayoutBlockD());
                 }
             }
         }
         if (getTurnoutType() == LH_XOVER && (getSensorA() == bean
                 || getSensorC() == bean || getSignalAMast() == bean || getSignalCMast() == bean)) {
             if (getSignalAMast() == bean || getSensorA() == bean) {
                 if (connectA != nullptr && ((TrackSegment*) connectA)->getLayoutBlock() == getLayoutBlock()) {
                     if (getLayoutBlockB() != getLayoutBlock()) {
                         ret.append(getLayoutBlockB());
                     }
                 } else {
                     ret.append(getLayoutBlock());
                 }
             } else {
                 if (connectC != nullptr && ((TrackSegment*) connectC)->getLayoutBlock() == getLayoutBlockC()) {
                     if (getLayoutBlockC() != getLayoutBlockD()) {
                         ret.append(getLayoutBlockD());
                     }
                 } else {
                     ret.append(getLayoutBlockC());
                 }
             }
         }
     } else {
         if (connectA != nullptr) {
             if (getSignalAMast() == bean || getSensorA() == bean) {
                 //Mast at throat
                 //if the turnout is in the same block as the segment connected at the throat, then we can be protecting two blocks
                 if (((TrackSegment*) connectA)->getLayoutBlock() == getLayoutBlock()) {
                     if (connectB != nullptr && connectC != nullptr) {
                         if (((TrackSegment*) connectB)->getLayoutBlock() != getLayoutBlock()
                                 && ((TrackSegment*) connectC)->getLayoutBlock() != getLayoutBlock()) {
                             ret.append(((TrackSegment*) connectB)->getLayoutBlock());
                             ret.append(((TrackSegment*) connectC)->getLayoutBlock());
                         }
                     }
                 } else {
                     ret.append(getLayoutBlock());
                 }
             } else if (getSignalBMast() == bean || getSensorB() == bean) {
                 //Mast at Continuing
                 if (connectB != nullptr && ((TrackSegment*) connectB)->getLayoutBlock() == getLayoutBlock()) {
                     if (((TrackSegment*) connectA)->getLayoutBlock() != getLayoutBlock()) {
                         ret.append(((TrackSegment*) connectA)->getLayoutBlock());
                     }
                 } else {
                     ret.append(getLayoutBlock());
                 }
             } else if (getSignalCMast() == bean || getSensorC() == bean) {
                 //Mast at Diverging
                 if (connectC != nullptr && ((TrackSegment*) connectC)->getLayoutBlock() == getLayoutBlock()) {
                     if (((TrackSegment*) connectA)->getLayoutBlock() != getLayoutBlock()) {
                         ret.append(((TrackSegment*) connectA)->getLayoutBlock());
                     }
                 } else {
                     ret.append(getLayoutBlock());
                 }
             }
         }
     }
     return ret;
 }   // getProtectedBlocks

/**
 * Edit a Layout Turnout
 */
/*protected*/ void LayoutTurnout::editLayoutTurnout()
{
// if(editLayoutTurnoutFrame == nullptr)
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
 if (editLayoutTurnoutFrame == nullptr)
 {
  editLayoutTurnoutFrame = new JmriJFrameX( tr("Edit Turnout"), false, true );
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
  turnoutNameField->setToolTip( tr("Edit turnout name to change the physical turnout linked to this panel Turnout::") );
  centralWidgetLayout->addWidget(panel1);

  QWidget* panel1a = new QWidget();
  //panel1a.setLayout(new BoxLayout(panel1a, BoxLayout.Y_AXIS));
  QVBoxLayout* panel1aLayout = new QVBoxLayout(panel1a);
  secondTurnoutComboBox = new JmriBeanComboBox(InstanceManager::turnoutManagerInstance(), getSecondTurnout(), JmriBeanComboBox::DISPLAYNAME);
//  additionalTurnout::addActionListener(new ActionListener() {
//      /*public*/ void actionPerformed(ActionEvent e) {
//          if(additionalTurnout::isSelected()){
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
  turnoutEditDone->setToolTip(tr("Click Done to accept any changes made above and dismiss this dialog->"));
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


 if(secondNamedTurnout!=nullptr)
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
//             turnoutEditCancelPressed(nullptr);
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

void LayoutTurnout::turnoutEditBlockPressed(JActionEvent* /*a*/)
{
 // check if a block name has been entered
 if (blockName!=(blockNameField->text().trimmed()))
 {
  // block has changed, if old block exists, decrement use
  if ((block != nullptr) && (block != blockB) && (block != blockC)
          && (block != blockD))
  {
   block->decrementUse();
  }
  // get new block, or nullptr if block has been removed
  blockName = blockNameField->text().trimmed();
  block = layoutEditor->provideLayoutBlock(blockName);
  if (block == nullptr)
  {
   blockName = "";
  }
  // decrement use if block was already counted
  if ((block != nullptr) && ((block == blockB) || (block == blockC)
          || (block == blockD)))
  {
   block->decrementUse();
  }
  needRedraw = true;
  needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (block == nullptr)
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

void LayoutTurnout::turnoutEditBlockBPressed(JActionEvent* /*a*/)
{
 // check if a block name has been entered
 if (blockBName != (blockBNameField->text().trimmed()))
 {
  // block has changed, if old block exists, decrement use
  if ((blockB != nullptr) && (block != blockB) && (blockB != blockC)
          && (blockB != blockD)) {
      blockB->decrementUse();
  }
  // get new block, or nullptr if block has been removed
  blockBName = blockBNameField->text().trimmed();
  blockB = layoutEditor->provideLayoutBlock(blockBName);
  if (blockB == nullptr) {
      blockBName = "";
  }
  // decrement use if block was already counted
  if ((blockB != nullptr) && ((block == blockB) || (blockB == blockC)
          || (blockB == blockD))) {
      blockB->decrementUse();
  }
  needRedraw = true;
  needsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (blockB == nullptr) {
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

void LayoutTurnout::turnoutEditBlockCPressed(JActionEvent* /*a*/) {
    // check if a block name has been entered
    if (blockCName != (blockCNameField->text().trimmed())) {
        // block has changed, if old block exists, decrement use
        if ((blockC != nullptr) && (block != blockC) && (blockB != blockC)
                && (blockC != blockD)) {
            blockC->decrementUse();
        }
        // get new block, or nullptr if block has been removed
        blockCName = blockCNameField->text().trimmed();
        blockC = layoutEditor->provideLayoutBlock(blockCName);
        if (blockC == nullptr) {
            blockCName = "";
        }
        // decrement use if block was already counted
        if ((blockC != nullptr) && ((block == blockC) || (blockB == blockC)
                || (blockC == blockD))) {
            blockD->decrementUse();
        }
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockC == nullptr) {
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

void LayoutTurnout::turnoutEditBlockDPressed(JActionEvent* /*a*/) {
    // check if a block name has been entered
    if (blockDName!=(blockDNameField->text().trimmed())) {
        // block has changed, if old block exists, decrement use
        if ((blockD != nullptr) && (block != blockD) && (blockB != blockD)
                && (blockC != blockD)) {
            blockD->decrementUse();
        }
        // get new block, or nullptr if block has been removed
        blockDName = blockDNameField->text().trimmed();
        blockD = layoutEditor->provideLayoutBlock(blockDName);
        if (blockD == nullptr) {
            blockDName = "";
        }
        // decrement use if block was already counted
        if ((blockD != nullptr) && ((block == blockD) || (blockB == blockD)
                || (blockC == blockD))) {
            blockD->decrementUse();
        }
        needRedraw = true;
        needsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (blockD == nullptr) {
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

void LayoutTurnout::turnoutEditDonePressed(JActionEvent* /*a*/) {
    // check if Turnout changed
    if (turnoutName!=(turnoutNameField->text().trimmed())) {
        // turnout has changed
        QString newName = turnoutNameField->text().trimmed();
        if (layoutEditor->validatePhysicalTurnout(newName,
                editLayoutTurnoutFrame)) {
            setTurnout(newName);
        } else {
            namedTurnout = nullptr;
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
                    secondNamedTurnout = nullptr;
                    secondTurnoutName = "";
                    //secondTurnoutNameField.setText("");
                }
                needRedraw = true;
            } else {
                setSecondTurnout(secondTurnoutComboBox->currentText());
            }
        }
    } else {
        setSecondTurnout(nullptr);
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
        if ((block != nullptr) && (block != blockB) && (block != blockC)
                && (block != blockD)) {
            block->decrementUse();
        }
        // get new block, or nullptr if block has been removed
        blockName = blockNameField->text().trimmed();
        block = layoutEditor->provideLayoutBlock(blockName);
        if (block == nullptr) {
            blockName = "";
        }
        // decrement use if block was already counted
        if ((block != nullptr) && ((block == blockB) || (block == blockC)
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
            if ((blockB != nullptr) && (block != blockB) && (blockB != blockC)
                    && (blockB != blockD)) {
                blockB->decrementUse();
            }
            // get new block, or nullptr if block has been removed
            blockBName = blockBNameField->text().trimmed();
            blockB = layoutEditor->provideLayoutBlock(blockBName);
            if (blockB == nullptr) {
                blockBName = "";
            }
            // decrement use if block was already counted
            if ((blockB != nullptr) && ((block == blockB) || (blockB == blockC)
                    || (blockB == blockD))) {
                blockB->decrementUse();
            }
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 3 changed
        if (blockCName!=(blockCNameField->text().trimmed())) {
            // block has changed, if old block exists, decrement use
            if ((blockC != nullptr) && (block != blockC) && (blockB != blockC)
                    && (blockC != blockD)) {
                blockC->decrementUse();
            }
            // get new block, or nullptr if block has been removed
            blockCName = blockCNameField->text().trimmed();
            blockC = layoutEditor->provideLayoutBlock(blockCName);
            if (blockC == nullptr) {
                blockCName = "";
            }

            // decrement use if block was already counted
            if ((blockC != nullptr) && ((block == blockC) || (blockB == blockC)
                    || (blockC == blockD))) {
                blockC->decrementUse();
            }
            needRedraw = true;
            needsBlockUpdate = true;
        }
        // check if Block 4 changed
        if (blockDName!=(blockDNameField->text().trimmed())) {
            // block has changed, if old block exists, decrement use
            if ((blockD != nullptr) && (block != blockD) && (blockB != blockD)
                    && (blockC != blockD)) {
                blockD->decrementUse();
            }
            // get new block, or nullptr if block has been removed
            blockDName = blockDNameField->text().trimmed();
            blockD = layoutEditor->provideLayoutBlock(blockDName);
            if (blockD == nullptr) {
                blockDName = "";
            }
            // decrement use if block was already counted
            if ((blockD != nullptr) && ((block == blockD) || (blockB == blockD)
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
    editLayoutTurnoutFrame = nullptr;
    if (needsBlockUpdate) {
        updateBlockInfo();
        reCheckBlockBoundary();
    }
    if (needRedraw) {
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

void LayoutTurnout::turnoutEditCancelPressed(JActionEvent* /*a*/) {
    editOpen = false;
    editLayoutTurnoutFrame->setVisible(false);
    editLayoutTurnoutFrame->dispose();
    editLayoutTurnoutFrame = nullptr;
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
 if((completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text)) != nullptr)
 blockNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockBNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text)) != nullptr)
 blockBNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockCNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text)) != nullptr)
 blockCNameField->setCompleter(completer);
}
void LayoutTurnout::on_blockDNameField_textEdited(QString text)
{
 QCompleter* completer;
 if((completer = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getCompleter(text)) != nullptr)
 blockDNameField->setCompleter(completer);
}
/*
    this is used by ConnectivityUtil to determine the turnout state necessary to get from prevLayoutBlock*  ==> currLayoutBlock*  ==> nextLayoutBlock
 */
/*protected*/ int LayoutTurnout::getConnectivityStateForLayoutBlocks(
        LayoutBlock* currLayoutBlock,
        LayoutBlock* prevLayoutBlock,
        LayoutBlock* nextLayoutBlock,
        bool suppress) {
    int result = UNKNOWN;

    LayoutBlock*  layoutBlockA = ((TrackSegment*) getConnectA())->getLayoutBlock();
    LayoutBlock*  layoutBlockB = ((TrackSegment*) getConnectB())->getLayoutBlock();
    LayoutBlock*  layoutBlockC = ((TrackSegment*) getConnectC())->getLayoutBlock();
    //TODO: Determine if this should be being used
    //LayoutBlock*  layoutBlockD = ((TrackSegment*) getConnectD()).getLayoutBlock();

    int tTyp = getTurnoutType();
    switch (tTyp) {
        case LayoutTurnout::RH_TURNOUT:
        case LayoutTurnout::LH_TURNOUT:
        case LayoutTurnout::WYE_TURNOUT: {
            if (layoutBlockA == currLayoutBlock) {
                if ((layoutBlockC == nextLayoutBlock) || (layoutBlockC == prevLayoutBlock)) {
                    result = Turnout::THROWN;
                } else if ((layoutBlockB == nextLayoutBlock) || (layoutBlockB == prevLayoutBlock)) {
                    result = Turnout::CLOSED;
                } else if (layoutBlockB == currLayoutBlock) {
                    result = Turnout::CLOSED;
                } else if (layoutBlockC == currLayoutBlock) {
                    result = Turnout::THROWN;
                } else {
                    if (!suppress) {
                        log->error("Cannot determine turnout setting - " + getTurnoutName());
                    }
                    result = Turnout::CLOSED;
                }
            } else if (layoutBlockB == currLayoutBlock) {
                result = Turnout::CLOSED;
            } else if (layoutBlockC == currLayoutBlock) {
                result = Turnout::THROWN;
            } else {
                if (!suppress) {
                    log->error("Cannot determine turnout setting for " + getTurnoutName());
                }
                if (!suppress) {
                    log->error("lb " + currLayoutBlock->getDisplayName()  + " nlb " + nextLayoutBlock->getDisplayName()  + " connect B " + layoutBlockB->getDisplayName() + " connect C " + layoutBlockC->getDisplayName());
                }
                result = Turnout::CLOSED;
            }
            break;
        }
        case LayoutTurnout::RH_XOVER:
        case LayoutTurnout::LH_XOVER:
        case LayoutTurnout::DOUBLE_XOVER: {
            if (getLayoutBlock() == currLayoutBlock) {
                if ((tTyp != LayoutTurnout::LH_XOVER)
                        && ((getLayoutBlockC() == nextLayoutBlock)
                        || (getLayoutBlockC() == prevLayoutBlock))) {
                    result = Turnout::THROWN;
                } else if ((getLayoutBlockB() == nextLayoutBlock) || (getLayoutBlockB() == prevLayoutBlock)) {
                    result = Turnout::CLOSED;
                } else if (getLayoutBlockB() == currLayoutBlock) {
                    result = Turnout::CLOSED;
                } else if ((tTyp != LayoutTurnout::LH_XOVER)
                        && (getLayoutBlockC() == currLayoutBlock)) {
                    result = Turnout::THROWN;
                } else {
                    if (!suppress) {
                        log->error("Cannot determine turnout setting(A) - " + getTurnoutName());
                    }
                    result = Turnout::CLOSED;
                }
            } else if (getLayoutBlockB() == currLayoutBlock) {
                if ((getLayoutBlock() == nextLayoutBlock) || (getLayoutBlock() == prevLayoutBlock)) {
                    result = Turnout::CLOSED;
                } else if ((tTyp != LayoutTurnout::RH_XOVER)
                        && ((getLayoutBlockD() == nextLayoutBlock)
                        || (getLayoutBlockD() == prevLayoutBlock) || (getLayoutBlockD() == currLayoutBlock))) {
                    result = Turnout::THROWN;
                } else {
                    if (!suppress) {
                        log->error("Cannot determine turnout setting(B) - " + getTurnoutName());
                    }
                    result = Turnout::CLOSED;
                }
            } else if (getLayoutBlockC() == currLayoutBlock) {
                if ((tTyp != LayoutTurnout::LH_XOVER)
                        && ((getLayoutBlock() == nextLayoutBlock) || (getLayoutBlock() == prevLayoutBlock))) {
                    result = Turnout::THROWN;
                } else if ((getLayoutBlockD() == nextLayoutBlock) || (getLayoutBlockD() == prevLayoutBlock) || (getLayoutBlockD() == currLayoutBlock)) {
                    result = Turnout::CLOSED;
                } else if ((tTyp != LayoutTurnout::LH_XOVER)
                        && (getLayoutBlockD() == currLayoutBlock)) {
                    result = Turnout::THROWN;
                } else {
                    if (!suppress) {
                        log->error("Cannot determine turnout setting(C) - " + getTurnoutName());
                    }
                    result = Turnout::CLOSED;
                }
            } else if (getLayoutBlockD() == currLayoutBlock) {
                if ((getLayoutBlockC() == nextLayoutBlock) || (getLayoutBlockC() == prevLayoutBlock)) {
                    result = Turnout::CLOSED;
                } else if ((tTyp != LayoutTurnout::RH_XOVER)
                        && ((getLayoutBlockB() == nextLayoutBlock) || (getLayoutBlockB() == prevLayoutBlock))) {
                    result = Turnout::THROWN;
                } else {
                    if (!suppress) {
                        log->error("Cannot determine turnout setting(D) - " + getTurnoutName());
                    }
                    result = Turnout::CLOSED;
                }
            }
            break;
        }
        default: {
            log->warn("getTurnoutList() unknown tTyp: " + QString::number(tTyp));
            break;
        }
    }   // switch (tTyp)

    return result;
}   //

/*public*/ void LayoutTurnout::reCheckBlockBoundary() const
{
 if (connectA == nullptr && connectB == nullptr && connectC == nullptr) {
     if (isTurnoutTypeTurnout()) {
         if (signalAMastNamed != nullptr) {
             removeSML(getSignalAMast());
         }
         if (signalBMastNamed != nullptr) {
             removeSML(getSignalBMast());
         }
         if (signalCMastNamed != nullptr) {
             removeSML(getSignalCMast());
         }
         signalAMastNamed = nullptr;
         signalBMastNamed = nullptr;
         signalCMastNamed = nullptr;
         sensorANamed = nullptr;
         sensorBNamed = nullptr;
         sensorCNamed = nullptr;
         return;
     } else if (isTurnoutTypeXover() && connectD == nullptr) {
         if (signalAMastNamed != nullptr) {
             removeSML(getSignalAMast());
         }
         if (signalBMastNamed != nullptr) {
             removeSML(getSignalBMast());
         }
         if (signalCMastNamed != nullptr) {
             removeSML(getSignalCMast());
         }
         if (signalDMastNamed != nullptr) {
             removeSML(getSignalDMast());
         }
         signalAMastNamed = nullptr;
         signalBMastNamed = nullptr;
         signalCMastNamed = nullptr;
         signalDMastNamed = nullptr;
         sensorANamed = nullptr;
         sensorBNamed = nullptr;
         sensorCNamed = nullptr;
         sensorDNamed = nullptr;
         return;
     }
 }

 if (connectA == nullptr || connectB == nullptr || connectC == nullptr) {
     // could still be in the process of rebuilding.
     return;
 } else if ((connectD == nullptr) && isTurnoutTypeXover()) {
     // could still be in the process of rebuilding.
     return;
 }

 TrackSegment* trkA;
 TrackSegment* trkB;
 TrackSegment* trkC;
 TrackSegment* trkD;

 if (qobject_cast<TrackSegment*>(connectA )) {
     trkA = (TrackSegment*) connectA;
     if (trkA->getLayoutBlock() == getLayoutBlock()) {
         if (signalAMastNamed != nullptr) {
             removeSML(getSignalAMast());
         }
         signalAMastNamed = nullptr;
         sensorANamed = nullptr;
     }
 }
 if ( qobject_cast<TrackSegment*>(connectB)) {
     trkB = (TrackSegment*) connectB;
     if (trkB->getLayoutBlock() == getLayoutBlock() || trkB->getLayoutBlock() == getLayoutBlockB()) {
         if (signalBMastNamed != nullptr) {
             removeSML(getSignalBMast());
         }
         signalBMastNamed = nullptr;
         sensorBNamed = nullptr;

     }
 }
 if (qobject_cast<TrackSegment*>(connectC)) {
     trkC = (TrackSegment*) connectC;
     if (trkC->getLayoutBlock() == getLayoutBlock()
             || trkC->getLayoutBlock() == getLayoutBlockB()
             || trkC->getLayoutBlock() == getLayoutBlockC()) {
         if (signalCMastNamed != nullptr) {
             removeSML(getSignalCMast());
         }
         signalCMastNamed = nullptr;
         sensorCNamed = nullptr;

     }
 }
 if (connectD != nullptr &&  qobject_cast<TrackSegment*>(connectD)
         && isTurnoutTypeXover()) {
     trkD = (TrackSegment*) connectD;
     if (trkD->getLayoutBlock() == getLayoutBlock()
             || trkD->getLayoutBlock() == getLayoutBlockB()
             || trkD->getLayoutBlock() == getLayoutBlockC()
             || trkD->getLayoutBlock() == getLayoutBlockD()) {
         if (signalDMastNamed != nullptr) {
             removeSML(getSignalDMast());
         }
         signalDMastNamed = nullptr;
         sensorDNamed = nullptr;
     }
 }
}   // reCheckBlockBoundary

/*
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity *> *LayoutTurnout::getLayoutConnectivity()
{
 QList<LayoutConnectivity*>* results = new QList<LayoutConnectivity*>();

 LayoutConnectivity* lc = nullptr;

 LayoutBlock* lbA = getLayoutBlock(), *lbB = getLayoutBlockB(), *lbC = getLayoutBlockC(), *lbD = getLayoutBlockD();
 if ((getTurnoutType() >= LayoutTurnout::DOUBLE_XOVER) && (lbA != nullptr)) {
     // have a crossover turnout with at least one block, check for multiple blocks
     if ((lbA != lbB) || (lbA != lbC) || (lbA != lbD)) {
         // have multiple blocks and therefore internal block boundaries
         if (lbA != lbB) {
             // have a AB block boundary, create a LayoutConnectivity
             log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lbA->getDisplayName()).arg(lbB->getDisplayName()).arg(this->getTurnoutName()));
             lc = new LayoutConnectivity(lbA, lbB);
             lc->setXoverBoundary(this, LayoutConnectivity::XOVER_BOUNDARY_AB);
             lc->setDirection(Path::computeDirection(getCoordsA(), getCoordsB()));
             results->append(lc);
         }
         if ((getTurnoutType() != LayoutTurnout::LH_XOVER) && (lbA != lbC)) {
             // have a AC block boundary, create a LayoutConnectivity
             log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lbA->getDisplayName()).arg(lbC->getDisplayName()).arg(this->getTurnoutName()));
             lc = new LayoutConnectivity(lbA, lbC);
             lc->setXoverBoundary(this, LayoutConnectivity::XOVER_BOUNDARY_AC);
             lc->setDirection(Path::computeDirection(getCoordsA(), getCoordsC()));
             results->append(lc);
         }
         if (lbC != lbD) {
             // have a CD block boundary, create a LayoutConnectivity
             log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lbC->getDisplayName()).arg(lbD->getDisplayName()).arg(this->getTurnoutName()));
             lc = new LayoutConnectivity(lbC, lbD);
             lc->setXoverBoundary(this, LayoutConnectivity::XOVER_BOUNDARY_CD);
             lc->setDirection(Path::computeDirection(getCoordsC(), getCoordsD()));
             results->append(lc);
         }
         if ((getTurnoutType() != LayoutTurnout::RH_XOVER) && (lbB != lbD)) {
             // have a BD block boundary, create a LayoutConnectivity
             log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lbB->getDisplayName()).arg(lbD->getDisplayName()).arg(this->getTurnoutName()));
             lc = new LayoutConnectivity(lbB, lbD);
             lc->setXoverBoundary(this, LayoutConnectivity::XOVER_BOUNDARY_BD);
             lc->setDirection(Path::computeDirection(getCoordsB(), getCoordsD()));
             results->append(lc);
         }
     }
 }
 return results;
}   // getLayoutConnectivity()

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QList<int> LayoutTurnout::checkForFreeConnections() {
    QList<int> result = QList<int>();

    //check the A connection point
    if (getConnectA() == nullptr) {
        result.append((TURNOUT_A));
    }

    //check the B connection point
    if (getConnectB() == nullptr) {
        result.append((TURNOUT_B));
    }

    //check the C connection point
    if (getConnectC() == nullptr) {
        result.append((TURNOUT_C));
    }

    //check the D connection point
    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == LH_XOVER)
            || (getTurnoutType() == RH_XOVER)) {
        if (getConnectD() == nullptr) {
            result.append((TURNOUT_D));
        }
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool LayoutTurnout::checkForUnAssignedBlocks() {
    // because getLayoutBlock[BCD] will return block [A] if they're null
    // we only need to test block [A]
    return (getLayoutBlock() != nullptr);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnout::checkForNonContiguousBlocks(/*@Nonnull*/QMap<QString, QList<QSet<QString> *> *> *blockNamesToTrackNameSetsMap) {
    /*
     * For each (non-null) blocks of this track do:
     * #1) If it's got an entry in the blockNamesToTrackNameSetMap then
     * #2) If this track is already in the TrackNameSet for this block
     *     then return (done!)
     * #3) else add a new set (with this block/track) to
     *     blockNamesToTrackNameSetMap and check all the connections in this
     *     block (by calling the 2nd method below)
     * <p>
     *     Basically, we're maintaining contiguous track sets for each block found
     *     (in blockNamesToTrackNameSetMap)
     */

    // We're only using a map here because it's convient to
    // use it to pair up blocks and connections
    QHash<LayoutTrack*, QString> blocksAndTracksMap = QHash<LayoutTrack*, QString>();
    if (connectA != nullptr) {
        blocksAndTracksMap.insert(connectA, getBlockName());
    }
    if (connectB != nullptr) {
        blocksAndTracksMap.insert(connectB, getBlockBName());
    }
    if (connectC != nullptr) {
        blocksAndTracksMap.insert(connectC, getBlockCName());
    }
    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == LH_XOVER)
            || (getTurnoutType() == RH_XOVER)
            || (getTurnoutType() == SINGLE_SLIP)
            || (getTurnoutType() == DOUBLE_SLIP)) {
        if (connectD != nullptr) {
            blocksAndTracksMap.insert(connectD, getBlockDName());
        }
    }
    QList<QSet<QString>* >* TrackNameSets = nullptr;
    QSet<QString>* TrackNameSet = nullptr;
    //for (Map.Entry<LayoutTrack, String> entry : blocksAndTracksMap.entrySet()) {
    QHashIterator<LayoutTrack*, QString> entry(blocksAndTracksMap);
    while(entry.hasNext())
    {
     entry.next();
        LayoutTrack* theConnect = entry.key();
        QString theBlockName = entry.value();

        TrackNameSet = new QSet<QString>();    // assume not found (pessimist!)
        TrackNameSets = blockNamesToTrackNameSetsMap->value(theBlockName);
        if (TrackNameSets && !TrackNameSets->isEmpty()) { // (#1)
            for (QSet<QString>* checkTrackNameSet : *TrackNameSets) {
                if (checkTrackNameSet->contains(getName())) { // (#2)
                    TrackNameSet = checkTrackNameSet;
                    break;
                }
            }
        } else {    // (#3)
            log->debug(tr("*New block ('%1') trackNameSets").arg(theBlockName));
            TrackNameSets = new QList<QSet<QString>* >();
            blockNamesToTrackNameSetsMap->insert(theBlockName, TrackNameSets);
        }
        if (TrackNameSet == nullptr || TrackNameSet->isEmpty()) {
            TrackNameSet = new QSet<QString>();
            TrackNameSets->append(TrackNameSet);
        }
        TrackNameSet->insert(getName());
        if (TrackNameSet->contains(getName())) {
            log->debug(tr("*    Add track '%1' to trackNameSet for block '%2'").arg(getName()).arg(theBlockName));
        }
        theConnect->collectContiguousTracksNamesInBlockNamed(theBlockName, TrackNameSet);
    }
}   // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnout::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
        /*@Nonnull*/ QSet<QString> *TrackNameSet) {
    if (!TrackNameSet->contains(getName())) {

        // create list of our connects
        QList<LayoutTrack*> connects = QList<LayoutTrack*>();
        if (getBlockName() == (blockName)
                && (connectA != nullptr)) {
            connects.append(connectA);
        }
        if (getBlockBName() == (blockName)
                && (connectB != nullptr)) {
            connects.append(connectB);
        }
        if (getBlockCName() == (blockName)
                && (connectC != nullptr)) {
            connects.append(connectC);
        }
        if ((getTurnoutType() == DOUBLE_XOVER)
                || (getTurnoutType() == LH_XOVER)
                || (getTurnoutType() == RH_XOVER)
                || (getTurnoutType() == SINGLE_SLIP)
                || (getTurnoutType() == DOUBLE_SLIP)) {
            if (getBlockDName() == (blockName)
                    && (connectD != nullptr)) {
                connects.append(connectD);
            }
        }

        for (LayoutTrack* connect : connects) {
            // if we are added to the TrackNameSet
         TrackNameSet->insert(getName());
            if (TrackNameSet->contains(getName())) {
                log->debug(tr("*    Add track '%1'for block '%2'").arg(getName()).arg(blockName));
            }
            // it's time to play... flood your neighbour!
            connect->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
        }
    }
}   // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnout::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    setLayoutBlock(layoutBlock);
    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == LH_XOVER)
            || (getTurnoutType() == RH_XOVER)
            || (getTurnoutType() == SINGLE_SLIP)
            || (getTurnoutType() == DOUBLE_SLIP)) {
        setLayoutBlockB(layoutBlock);
        setLayoutBlockC(layoutBlock);
        setLayoutBlockD(layoutBlock);
    }
}

void LayoutTurnout::removeSML(SignalMast* signalMast) const{
    if(signalMast==nullptr)
        return;
    if (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")
            )->isAdvancedRoutingEnabled() && qobject_cast<SignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"
            ))->isSignalMastUsed(signalMast)) {
                SignallingGuiTools::removeSignalMastLogic(nullptr, signalMast);
            }
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
  if(qobject_cast<QAction*>(mi)!= nullptr)
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
  if(qobject_cast<QAction*>(mi)!= nullptr)
   popup->addAction((QAction*)mi);
  else
   popup->addMenu((QMenu*)mi);
 }
}
/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnout::draw1(EditScene* g2, bool isMain, bool isBlock)
{
 if (isBlock && getLayoutBlock() == nullptr) {
     // Skip the block layer if there is no block assigned.
     return;
 }

 QPointF pA = getCoordsA();
 QPointF pB = getCoordsB();
 QPointF pC = getCoordsC();
 QPointF pD = getCoordsD();

 bool mainlineA = isMainlineA();
 bool mainlineB = isMainlineB();
 bool mainlineC = isMainlineC();
 bool mainlineD = isMainlineD();

 bool drawUnselectedLeg = layoutEditor->isTurnoutDrawUnselectedLeg();

 //Color color = g2.getColor();
 QColor color = layoutEditor->drawingStroke.color();

 // if this isn't a block line all these will be the same color
 QColor colorA = color;
 QColor colorB = color;
 QColor colorC = color;
 QColor colorD = color;

 if (isBlock) {
     LayoutBlock* lb = getLayoutBlock();
     colorA = (lb == nullptr) ? color : lb->getBlockColor();
     lb = getLayoutBlockB();
     colorB = (lb == nullptr) ? color : lb->getBlockColor();
     lb = getLayoutBlockC();
     colorC = (lb == nullptr) ? color : lb->getBlockColor();
     lb = getLayoutBlockD();
     colorD = (lb == nullptr) ? color : lb->getBlockColor();
 }

 // middles
 QPointF pM = getCoordsCenter();
 QPointF pABM = MathUtil::midPoint(pA, pB);
 QPointF pAM = MathUtil::lerp(pA, pABM, 5.0 / 8.0);
 QPointF pAMP = MathUtil::midPoint(pAM, pABM);
 QPointF pBM = MathUtil::lerp(pB, pABM, 5.0 / 8.0);
 QPointF pBMP = MathUtil::midPoint(pBM, pABM);

 QPointF pCDM = MathUtil::midPoint(pC, pD);
 QPointF pCM = MathUtil::lerp(pC, pCDM, 5.0 / 8.0);
 QPointF pCMP = MathUtil::midPoint(pCM, pCDM);
 QPointF pDM = MathUtil::lerp(pD, pCDM, 5.0 / 8.0);
 QPointF pDMP = MathUtil::midPoint(pDM, pCDM);

 QPointF pAF = MathUtil::midPoint(pAM, pM);
 QPointF pBF = MathUtil::midPoint(pBM, pM);
 QPointF pCF = MathUtil::midPoint(pCM, pM);
 QPointF pDF = MathUtil::midPoint(pDM, pM);

 int state = UNKNOWN;
 if (layoutEditor->isAnimating()) {
  state = getState();
 }

 if(log->isDebugEnabled())
  log->debug(tr("draw1 turnout %1 isMain = %2, state = %3").arg(getTurnoutName()).arg(isMain?"true":"false").arg(getTurnoutStateString(getState())));

 int toType = getTurnoutType();

 QGraphicsLineItem* lineItem;

 itemGroup = invalidateItem(g2,itemGroup);
 if(itemGroup == nullptr)
 {
  itemGroup = new QGraphicsItemGroup();
  itemGroup->setZValue(Editor::HANDLES+1);
 }
 g2->addItem(itemGroup);

 if (toType == DOUBLE_XOVER)
 {
  if (state != Turnout::THROWN && state != Turnout::INCONSISTENT)
  { // unknown or continuing path - not crossed over
   if (isMain == mainlineA) {
       //g2.setColor(colorA);
    layoutEditor->drawingStroke.setColor(colorA);
       //g2.draw(new Line2D.Double(pA, pABM));
    lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg)
    {
       // g2.draw(new Line2D.Double(pAF, pM));
     lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineB)
   {
       //g2.setColor(colorB);
    layoutEditor->drawingStroke.setColor(colorB);
//             g2.draw(new Line2D.Double(pB, pABM));
    lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pABM.x(), pABM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg) {
        //g2.draw(new Line2D.Double(pBF, pM));
     lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineC)
   {
       //g2.setColor(colorC);
    layoutEditor->drawingStroke.setColor(colorC);
       //g2.draw(new Line2D.Double(pC, pCDM));
    lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg)
    {
     //g2.draw(new Line2D.Double(pCF, pM));
     lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineD)
   {
    //g2.setColor(colorD);
    layoutEditor->drawingStroke.setColor(colorD);
    //g2.draw(new Line2D.Double(pD, pCDM));
    lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pCDM.x(), pCDM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg)
    {
           //g2.draw(new Line2D.Double(pDF, pM));
     lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
  }
  if (state != Turnout::CLOSED && state != Turnout::INCONSISTENT)
  { // unknown or diverting path - crossed over
   if (isMain == mainlineA)
   {
    //g2.setColor(colorA);
    layoutEditor->drawingStroke.setColor(colorA);
    //g2.draw(new Line2D.Double(pA, pAM));
    lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    //g2.draw(new Line2D.Double(pAM, pM));
    lineItem = new QGraphicsLineItem(pAM.x(), pAM.y(), pM.x(), pM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg) {
        //g2.draw(new Line2D.Double(pAMP, pABM));
     lineItem = new QGraphicsLineItem(pAMP.x(), pAMP.y(), pABM.x(), pABM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineB) {
       //g2.setColor(colorB);
    layoutEditor->drawingStroke.setColor(colorB);
    //g2.draw(new Line2D.Double(pB, pBM));
    lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    //g2.draw(new Line2D.Double(pBM, pM));
    lineItem = new QGraphicsLineItem(pBM.x(), pBM.y(), pM.x(), pM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg)
    {
     //g2.draw(new Line2D.Double(pBMP, pABM));
     lineItem = new QGraphicsLineItem(pBMP.x(), pBMP.y(), pABM.x(), pABM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineC)
   {
    //g2.setColor(colorC);
    layoutEditor->drawingStroke.setColor(colorC);
    //g2.draw(new Line2D.Double(pC, pCM));
    lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    //g2.draw(new Line2D.Double(pCM, pM));
     lineItem = new QGraphicsLineItem(pCM.x(), pCM.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg) {
        //g2.draw(new Line2D.Double(pCMP, pCDM));
     lineItem = new QGraphicsLineItem(pCMP.x(), pCMP.y(), pCDM.x(), pCDM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
   if (isMain == mainlineD)
   {
       //g2.setColor(colorD);
    layoutEditor->drawingStroke.setColor(colorD);
       //g2.draw(new Line2D.Double(pD, pDM));
    lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
       //g2.draw(new Line2D.Double(pDM, pM));
    lineItem = new QGraphicsLineItem(pDM.x(), pDM.y(), pM.x(), pM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    if (!isBlock || drawUnselectedLeg)
    {
     //g2.draw(new Line2D.Double(pDMP, pCDM));
     lineItem = new QGraphicsLineItem(pDMP.x(), pDMP.y(), pCDM.x(), pCDM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
  }
  if (state == Turnout::INCONSISTENT)
  {
   if (isMain == mainlineA)
   {
       //g2.setColor(colorA);
    layoutEditor->drawingStroke.setColor(colorA);
       //g2.draw(new Line2D.Double(pA, pAM));
    lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);

   }
   if (isMain == mainlineB) {
       //g2.setColor(colorB);
    layoutEditor->drawingStroke.setColor(colorB);
//      g2.draw(new Line2D.Double(pB, pBM));
    lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
   }
   if (isMain == mainlineC) {
       //g2.setColor(colorC);
    layoutEditor->drawingStroke.setColor(colorC);
       //g2.draw(new Line2D.Double(pC, pCM));
    lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
   }
   if (isMain == mainlineD) {
       //g2.setColor(colorD);
    layoutEditor->drawingStroke.setColor(colorD);
       //g2.draw(new Line2D.Double(pD, pDM));
    lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
   }
   if (!isBlock || drawUnselectedLeg)
   {
    if (isMain == mainlineA)
    {
//           g2.setColor(colorA);
     layoutEditor->drawingStroke.setColor(colorA);
        //g2.draw(new Line2D.Double(pAF, pM));
     lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
    if (isMain == mainlineC) {
        //g2.setColor(colorC);
     layoutEditor->drawingStroke.setColor(colorC);
        //g2.draw(new Line2D.Double(pCF, pM));
     lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
    if (isMain == mainlineB) {
        //g2.setColor(colorB);
     layoutEditor->drawingStroke.setColor(colorB);
        //g2.draw(new Line2D.Double(pBF, pM));
     lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
    if (isMain == mainlineD) {
        //g2.setColor(colorD);
     layoutEditor->drawingStroke.setColor(colorD);
        //g2.draw(new Line2D.Double(pDF, pM));
     lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
     lineItem->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(lineItem);
    }
   }
  }
 }
 else if ((toType == RH_XOVER)
      || (toType == LH_XOVER))
 {    // draw (rh & lh) cross overs
  pAF = MathUtil::midPoint(pABM, pM);
  pBF = MathUtil::midPoint(pABM, pM);
  pCF = MathUtil::midPoint(pCDM, pM);
  pDF = MathUtil::midPoint(pCDM, pM);
  if (state != Turnout::THROWN && state != Turnout::INCONSISTENT)
  { // unknown or continuing path - not crossed over
         if (isMain == mainlineA) {
             //g2.setColor(colorA);
          layoutEditor->drawingStroke.setColor(colorA);
             //g2.draw(new Line2D.Double(pA, pABM));
          lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineB) {
//             g2.setColor(colorB);
          layoutEditor->drawingStroke.setColor(colorB);
//             g2.draw(new Line2D.Double(pABM, pB));
          lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineC) {
             //g2.setColor(colorC);
          layoutEditor->drawingStroke.setColor(colorC);
             //g2.draw(new Line2D.Double(pC, pCDM));
          lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineD) {
             //g2.setColor(colorD);
          layoutEditor->drawingStroke.setColor(colorD);
             //g2.draw(new Line2D.Double(pCDM, pD));
          lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (!isBlock || drawUnselectedLeg) {
             if (getTurnoutType() == RH_XOVER) {
                 if (isMain == mainlineA) {
                     //g2.setColor(colorA);
                  layoutEditor->drawingStroke.setColor(colorA);
                     //g2.draw(new Line2D.Double(pAF, pM));
                  lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (isMain == mainlineC) {
                     //g2.setColor(colorC);
                  layoutEditor->drawingStroke.setColor(colorC);
                     //g2.draw(new Line2D.Double(pCF, pM));
                  lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             } else if (getTurnoutType() == LH_XOVER) {
                 if (isMain == mainlineB) {
                     //g2.setColor(colorB);
                  layoutEditor->drawingStroke.setColor(colorB);
                     //g2.draw(new Line2D.Double(pBF, pM));
                  lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (isMain == mainlineD) {
                     //g2.setColor(colorD);
                  layoutEditor->drawingStroke.setColor(colorD);
                     //g2.draw(new Line2D.Double(pDF, pM));
                  lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
         }
     }
     if (state != Turnout::CLOSED && state != Turnout::INCONSISTENT) { // unknown or diverting path - crossed over
         if (getTurnoutType() == RH_XOVER) {
             if (isMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, pABM));
              lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                //;g2.draw(new Line2D.Double(pABM, pM));
                lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
                lineItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(lineItem);
             }
             if (!isBlock || drawUnselectedLeg) {
                 if (isMain == mainlineB) {
                     //g2.setColor(colorB);
                  layoutEditor->drawingStroke.setColor(colorB);
                     //g2.draw(new Line2D.Double(pBM, pB));
                  lineItem = new QGraphicsLineItem(pBM.x(), pBM.y(), pB.x(), pB.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
             if (isMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(pC, pCDM));
              lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pCDM, pM));
              lineItem = new QGraphicsLineItem(pCDM.x(), pCDM.y(), pM.x(), pM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (!isBlock || drawUnselectedLeg) {
                 if (isMain == mainlineD) {
                     //g2.setColor(colorD);
                  layoutEditor->drawingStroke.setColor(colorD);
                     //g2.draw(new Line2D.Double(pDM, pD));
                  lineItem = new QGraphicsLineItem(pDM.x(), pDM.y(), pD.x(), pD.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
         } else if (getTurnoutType() == LH_XOVER) {
             if (!isBlock || drawUnselectedLeg) {
                 if (isMain == mainlineA) {
                     //g2.setColor(colorA);
                  layoutEditor->drawingStroke.setColor(colorA);
                     //g2.draw(new Line2D.Double(pA, pAM));
                  lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
             if (isMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, pABM));
              lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pABM.x(), pABM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pABM, pM));
              lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);}
             if (!isBlock || drawUnselectedLeg) {
                 if (isMain == mainlineC) {
                     //g2.setColor(colorC);
                  layoutEditor->drawingStroke.setColor(colorC);
                     //g2.draw(new Line2D.Double(pC, pCM));
                  lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);}
             }
             if (isMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(pD, pCDM));
              lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pCDM.x(), pCDM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pCDM, pM));
              lineItem = new QGraphicsLineItem(pCDM.x(), pCDM.y(), pM.x(), pM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);}
         }
     }
     if (state == Turnout::INCONSISTENT) {
         if (isMain == mainlineA) {
             //g2.setColor(colorA);
          layoutEditor->drawingStroke.setColor(colorA);
             //g2.draw(new Line2D.Double(pA, pAM));
          lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineB) {
             //g2.setColor(colorB);
          layoutEditor->drawingStroke.setColor(colorB);
             //g2.draw(new Line2D.Double(pB, pBM));
          lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineC) {
             //g2.setColor(colorC);
          layoutEditor->drawingStroke.setColor(colorC);
             //g2.draw(new Line2D.Double(pC, pCM));
          lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (isMain == mainlineD) {
             //g2.setColor(colorD);
          layoutEditor->drawingStroke.setColor(colorD);
             //g2.draw(new Line2D.Double(pD, pDM));
          lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
         if (!isBlock || drawUnselectedLeg) {
             if (getTurnoutType() == RH_XOVER) {
                 if (isMain == mainlineA) {
                     //g2.setColor(colorA);
                  layoutEditor->drawingStroke.setColor(colorA);
                     //g2.draw(new Line2D.Double(pAF, pM));
                  lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (isMain == mainlineC) {
                     //g2.setColor(colorC);
                  layoutEditor->drawingStroke.setColor(colorC);
                     //g2.draw(new Line2D.Double(pCF, pM));
                  lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             } else if (getTurnoutType() == LH_XOVER) {
                 if (isMain == mainlineB) {
                     //g2.setColor(colorB);
                  layoutEditor->drawingStroke.setColor(colorB);
                     //g2.draw(new Line2D.Double(pBF, pM));
                  lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (isMain == mainlineD) {
                     //g2.setColor(colorD);
                  layoutEditor->drawingStroke.setColor(colorD);
                     //g2.draw(new Line2D.Double(pDF, pM));
                  lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
         }
     }
 }
 else if ((toType == SINGLE_SLIP) || (toType == DOUBLE_SLIP)) {
     log->error("slips should be being drawn by LayoutSlip sub-class");
 }
 else {    // LH, RH, or WYE Turnouts
     // draw A<===>center
     if (isMain == mainlineA) {
         //g2.setColor(colorA);
      layoutEditor->drawingStroke.setColor(colorA);
         //g2.draw(new Line2D.Double(pA, pM));
      lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pM.x(), pM.y());
      lineItem->setPen(layoutEditor->drawingStroke);
      itemGroup->addToGroup(lineItem);
     }

     if (state == UNKNOWN || (continuingSense == state && state != Turnout::INCONSISTENT))
     { // unknown or continuing path
         // draw center<===>B
         if (isMain == mainlineB) {
             //g2.setColor(colorB);
          layoutEditor->drawingStroke.setColor(colorB);
             //g2.draw(new Line2D.Double(pM, pB));
          lineItem = new QGraphicsLineItem(pM.x(), pM.y(), pB.x(), pB.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
     } else if (!isBlock || drawUnselectedLeg) {
         // draw center<--=>B
         if (isMain == mainlineB) {
             //g2.setColor(colorB);
          layoutEditor->drawingStroke.setColor(colorB);
             //g2.draw(new Line2D.Double(MathUtil::twoThirdsPoint(pM, pB), pB));
          lineItem = new QGraphicsLineItem(MathUtil::twoThirdsPoint(pM, pB).x(), MathUtil::twoThirdsPoint(pM, pB).y(), pB.x(), pB.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
     }

     if (state == UNKNOWN || (continuingSense != state && state != Turnout::INCONSISTENT))
     { // unknown or diverting path
         // draw center<===>C
         if (isMain == mainlineC)
         {
             //g2.setColor(colorC);
          layoutEditor->drawingStroke.setColor(colorC);
             //g2.draw(new Line2D.Double(pM, pC));
          lineItem = new QGraphicsLineItem(pM.x(), pM.y(), pC.x(), pC.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
     } else if (!isBlock || drawUnselectedLeg) {
         // draw center<--=>C
         if (isMain == mainlineC) {
             //g2.setColor(colorC);
          layoutEditor->drawingStroke.setColor(colorC);
             //g2.draw(new Line2D.Double(MathUtil::twoThirdsPoint(pM, pC), pC));
          lineItem = new QGraphicsLineItem(MathUtil::twoThirdsPoint(pM, pC).x(), MathUtil::twoThirdsPoint(pM, pC).y(), pC.x(), pC.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }
     }
 }
}   // draw1

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnout::draw2(EditScene* g2, bool isMain, float railDisplacement) {
    int toType = getTurnoutType();

    QPointF pA = getCoordsA();
    QPointF pB = getCoordsB();
    QPointF pC = getCoordsC();
    QPointF pD = getCoordsD();
    QPointF pM = getCoordsCenter();

    QPointF vAM = MathUtil::normalize(MathUtil::subtract(pM, pA));
    QPointF vAMo = MathUtil::orthogonal(MathUtil::normalize(vAM, railDisplacement));

    QPointF pAL = MathUtil::subtract(pA, vAMo);
    QPointF pAR = MathUtil::add(pA, vAMo);

    QPointF vBM = MathUtil::normalize(MathUtil::subtract(pB, pM));
    double dirBM_DEG = MathUtil::computeAngleDEG(vBM);
    QPointF vBMo = MathUtil::normalize(MathUtil::orthogonal(vBM), railDisplacement);
    QPointF pBL = MathUtil::subtract(pB, vBMo);
    QPointF pBR = MathUtil::add(pB, vBMo);
    QPointF pMR = MathUtil::add(pM, vBMo);

    QPointF vCM = MathUtil::normalize(MathUtil::subtract(pC, pM));
    double dirCM_DEG = MathUtil::computeAngleDEG(vCM);

    QPointF vCMo = MathUtil::normalize(MathUtil::orthogonal(vCM), railDisplacement);
    QPointF pCL = MathUtil::subtract(pC, vCMo);
    QPointF pCR = MathUtil::add(pC, vCMo);
    QPointF pML = MathUtil::subtract(pM, vBMo);

    double deltaBMC_DEG = MathUtil::absDiffAngleDEG(dirBM_DEG, dirCM_DEG);
    double deltaBMC_RAD = qDegreesToRadians(deltaBMC_DEG);

    double hypotF = railDisplacement / qSin(deltaBMC_RAD / 2.0);

    QPointF vDisF = MathUtil::normalize(MathUtil::add(vAM, vCM), hypotF);
    if (toType == WYE_TURNOUT) {
        vDisF = MathUtil::normalize(vAM, hypotF);
    }
    QPointF pF = MathUtil::add(pM, vDisF);

    QPointF pFR = MathUtil::add(pF, MathUtil::multiply(vBMo, 2.0));
    QPointF pFL = MathUtil::subtract(pF, MathUtil::multiply(vCMo, 2.0));

    // QPointF pFPR = MathUtil::add(pF, MathUtil::normalize(vBMo, 2.0));
    // QPointF pFPL = MathUtil::subtract(pF, MathUtil::normalize(vCMo, 2.0));
    QPointF vDisAP = MathUtil::normalize(vAM, hypotF);
    QPointF pAP = MathUtil::subtract(pM, vDisAP);
    QPointF pAPR = MathUtil::add(pAP, vAMo);
    QPointF pAPL = MathUtil::subtract(pAP, vAMo);

    // QPointF vSo = MathUtil::normalize(vAMo, 2.0);
    // QPointF pSL = MathUtil::add(pAPL, vSo);
    // QPointF pSR = MathUtil::subtract(pAPR, vSo);

    bool mainlineA = isMainlineA();
    bool mainlineB = isMainlineB();
    bool mainlineC = isMainlineC();
    bool mainlineD = isMainlineD();

    int state = UNKNOWN;
    if (layoutEditor->isAnimating()) {
         Turnout* to = getTurnout();
        if (to != nullptr) {
            state = to->getKnownState();
        }
    }

    //if(!isMain && itemGroup)
     itemGroup = invalidateItem(g2,itemGroup);
    if(itemGroup == nullptr)
    {
     itemGroup = new QGraphicsItemGroup();
     itemGroup->setZValue(Editor::HANDLES+1);
     g2->addItem(itemGroup);
    }

    QGraphicsLineItem* lineItem;
    switch (toType) {
        case RH_TURNOUT: {
            if (isMain == mainlineA) {
                //g2.draw(new Line2D.Double(pAL, pML));
             lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pML.x(), pML.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pAR, pAPR));
             lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pAPR.x(), pAPR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
            }
            if (isMain == mainlineB) {
                //g2.draw(new Line2D.Double(pML, pBL));
             lineItem = new QGraphicsLineItem(pML.x(), pML.y(), pBL.x(), pBL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pF, pBR));
             lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBR.x(), pBR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);

                if (continuingSense == state)
                {  // unknown or diverting path
//                         g2.draw(new Line2D.Double(pSR, pFPR));
//                     } else {
                    //g2.draw(new Line2D.Double(pAPR, pF));
                 lineItem = new QGraphicsLineItem(pAPR.x(), pAPR.y(), pF.x(), pF.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                }
            }
            if (isMain == mainlineC) {
                //g2.draw(new Line2D.Double(pF, pCL));
             lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCL.x(), pCL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pFR, pCR));
             lineItem = new QGraphicsLineItem(pFR.x(), pFR.y(), pCR.x(), pCR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);

                QPainterPath* path = new QPainterPath();
                path->moveTo(pAPR.x(), pAPR.y());
                path->quadTo(pMR.x(), pMR.y(), pFR.x(), pFR.y());
                path->lineTo(pCR.x(), pCR.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(*path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (continuingSense != state) {  // unknown or diverting path
                    path = new QPainterPath();
                    path->moveTo(pAPL.x(), pAPL.y());
                    path->quadTo(pML.x(), pML.y(), pF.x(), pF.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(*path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);//                     } else {
//                         path = new QPainterPath();
//                         path.moveTo(pSL.x(), pSL.y());
//                         path.quadTo(pML.x(), pML.y(), pFPL.x(), pFPL.y());
//                         g2.draw(path);
                }
            }
            break;
        }   // case RH_TURNOUT

        case LH_TURNOUT: {
            if (isMain == mainlineA) {
                //g2.draw(new Line2D.Double(pAR, pMR));
             lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pMR.x(), pMR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pAL, pAPL));
             lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pAPL.x(), pAPL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
            }
            if (isMain == mainlineB) {
                //g2.draw(new Line2D.Double(pMR, pBR));
             lineItem = new QGraphicsLineItem(pMR.x(), pMR.y(), pBR.x(), pBR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pF, pBL));
             lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBL.x(), pBL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                if (continuingSense == state) {  // straight path
//                         g2.draw(new Line2D.Double(pSL, pFPL));  Offset problem
//                     } else {
                    //g2.draw(new Line2D.Double(pAPL, pF));
                 lineItem = new QGraphicsLineItem(pAPL.x(), pAPL.y(), pF.x(), pF.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                }
            }
            if (isMain == mainlineC) {
                //g2.draw(new Line2D.Double(pF, pCR));
             lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCR.x(), pCR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
                QPainterPath path = QPainterPath();
                path.moveTo(pAPL.x(), pAPL.y());
                path.quadTo(pML.x(), pML.y(), pFL.x(), pFL.y());
                path.lineTo(pCL.x(), pCL.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                //                     } else {
                if (continuingSense != state) {  // unknown or diverting path
                    path =  QPainterPath();
                    path.moveTo(pAPR.x(), pAPR.y());
                    path.quadTo(pMR.x(), pMR.y(), pF.x(), pF.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);
//                     } else {
//                     } else {
//                         path = new QPainterPath();
//                         path.moveTo(pSR.x(), pSR.y());
//                         path.quadTo(pMR.x(), pMR.y(), pFPR.x(), pFPR.y());
//                         g2.draw(path);
                }
            }
            break;
        }   // case LH_TURNOUT
        case WYE_TURNOUT: {
            if (isMain == mainlineA) {
                //g2.draw(new Line2D.Double(pAL, pAPL));
             lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pAPL.x(), pAPL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pAR, pAPR));
             lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pAPR.x(), pAPR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);}
            if (isMain == mainlineB) {
                //g2.draw(new Line2D.Double(pF, pBL));
             lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBL.x(), pBL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path = QPainterPath();
                path.moveTo(pAPR.x(), pAPR.y());
                path.quadTo(pMR.x(), pMR.y(), pFR.x(), pFR.x());
                path.lineTo(pBR.x(), pBR.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (continuingSense != state) {  // unknown or diverting path
                    path = QPainterPath();
                    path.moveTo(pAPR.x(), pAPR.y());
                    path.quadTo(pMR.x(), pMR.y(), pF.x(), pF.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);
                    //                     } else {
//                         path = new QPainterPath();
//                         path.moveTo(pSR.x(), pSR.y());
//                         path.quadTo(pMR.x(), pMR.y(), pFPR.x(), pFPR.y());
//     bad                    g2.draw(path);
                }
            }
            if (isMain == mainlineC) {
                pML = MathUtil::subtract(pM, vCMo);
                QPainterPath path = QPainterPath();
                path.moveTo(pAPL.x(), pAPL.y());
                path.quadTo(pML.x(), pML.y(), pFL.x(), pFL.y());
                path.lineTo(pCL.x(), pCL.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                //g2.draw(new Line2D.Double(pF, pCR));
                lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCR.x(), pCR.y());
                lineItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(lineItem);
                if (continuingSense != state) {  // unknown or diverting path
//                         path = new QPainterPath();
//                         path.moveTo(pSL.x(), pSL.y());
//                         path.quadTo(pML.x(), pML.y(), pFPL.x(), pFPL.y());
//           bad              g2.draw(path);
                } else {
                    path = QPainterPath();
                    path.moveTo(pAPL.x(), pAPL.y());
                    path.quadTo(pML.x(), pML.y(), pF.x(), pF.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);}
            }
            break;
        }   // case WYE_TURNOUT

        case DOUBLE_XOVER: {
            // A, B, C, D end points (left and right)
            QPointF vAB = MathUtil::normalize(MathUtil::subtract(pB, pA), railDisplacement);
            double dirAB_DEG = MathUtil::computeAngleDEG(vAB);
            QPointF vABo = MathUtil::orthogonal(MathUtil::normalize(vAB, railDisplacement));
            pAL = MathUtil::subtract(pA, vABo);
            pAR = MathUtil::add(pA, vABo);
            pBL = MathUtil::subtract(pB, vABo);
            pBR = MathUtil::add(pB, vABo);
            QPointF vCD = MathUtil::normalize(MathUtil::subtract(pD, pC), railDisplacement);
            QPointF vCDo = MathUtil::orthogonal(MathUtil::normalize(vCD, railDisplacement));
            pCL = MathUtil::add(pC, vCDo);
            pCR = MathUtil::subtract(pC, vCDo);
            QPointF pDL = MathUtil::add(pD, vCDo);
            QPointF pDR = MathUtil::subtract(pD, vCDo);

            // AB, CD mid points (left and right)
            QPointF pABM = MathUtil::midPoint(pA, pB);
            QPointF pABL = MathUtil::midPoint(pAL, pBL);
            QPointF pABR = MathUtil::midPoint(pAR, pBR);
            QPointF pCDM = MathUtil::midPoint(pC, pD);
            QPointF pCDL = MathUtil::midPoint(pCL, pDL);
            QPointF pCDR = MathUtil::midPoint(pCR, pDR);

            // A, B, C, D mid points
            double halfParallelDistance = MathUtil::distance(pABM, pCDM) / 2.0;
            QPointF pAM = MathUtil::subtract(pABM, MathUtil::normalize(vAB, halfParallelDistance));
            QPointF pAML = MathUtil::subtract(pAM, vABo);
            QPointF pAMR = MathUtil::add(pAM, vABo);
            QPointF pBM = MathUtil::add(pABM, MathUtil::normalize(vAB, halfParallelDistance));
            QPointF pBML = MathUtil::subtract(pBM, vABo);
            QPointF pBMR = MathUtil::add(pBM, vABo);
            QPointF pCM = MathUtil::subtract(pCDM, MathUtil::normalize(vCD, halfParallelDistance));
            QPointF pCML = MathUtil::subtract(pCM, vABo);
            QPointF pCMR = MathUtil::add(pCM, vABo);
            QPointF pDM = MathUtil::add(pCDM, MathUtil::normalize(vCD, halfParallelDistance));
            QPointF pDML = MathUtil::subtract(pDM, vABo);
            QPointF pDMR = MathUtil::add(pDM, vABo);

            // crossing points
            QPointF vACM = MathUtil::normalize(MathUtil::subtract(pCM, pAM), railDisplacement);
            QPointF vACMo = MathUtil::orthogonal(vACM);
            QPointF vBDM = MathUtil::normalize(MathUtil::subtract(pDM, pBM), railDisplacement);
            QPointF vBDMo = MathUtil::orthogonal(vBDM);
            QPointF pBDR = MathUtil::add(pM, vACM);
            QPointF pBDL = MathUtil::subtract(pM, vACM);

            // crossing diamond point (no gaps)
            QPointF pVR = MathUtil::add(pBDL, vBDM);
            QPointF pKL = MathUtil::subtract(pBDL, vBDM);
            QPointF pKR = MathUtil::add(pBDR, vBDM);
            QPointF pVL = MathUtil::subtract(pBDR, vBDM);

            // crossing diamond points (with gaps)
            QPointF vACM2 = MathUtil::normalize(vACM, 2.0);
            QPointF vBDM2 = MathUtil::normalize(vBDM, 2.0);
            // (syntax of "pKLtC" is "point LK toward C", etc.)
            QPointF pKLtC = MathUtil::add(pKL, vACM2);
            QPointF pKLtD = MathUtil::add(pKL, vBDM2);
            QPointF pVLtA = MathUtil::subtract(pVL, vACM2);
            QPointF pVLtD = MathUtil::add(pVL, vBDM2);
            QPointF pKRtA = MathUtil::subtract(pKR, vACM2);
            QPointF pKRtB = MathUtil::subtract(pKR, vBDM2);
            QPointF pVRtB = MathUtil::subtract(pVR, vBDM2);
            QPointF pVRtC = MathUtil::add(pVR, vACM2);

            // A, B, C, D frog points
            vCM = MathUtil::normalize(MathUtil::subtract(pCM, pM));
            dirCM_DEG = MathUtil::computeAngleDEG(vCM);
            double deltaBAC_DEG = MathUtil::absDiffAngleDEG(dirAB_DEG, dirCM_DEG);
            double deltaBAC_RAD = qDegreesToRadians(deltaBAC_DEG);
            hypotF = railDisplacement / qSin(deltaBAC_RAD / 2.0);
            QPointF vACF = MathUtil::normalize(MathUtil::add(vACM, vAB), hypotF);
            QPointF pAFL = MathUtil::add(pAM, vACF);
            QPointF pCFR = MathUtil::subtract(pCM, vACF);
            QPointF vBDF = MathUtil::normalize(MathUtil::add(vBDM, vCD), hypotF);
            QPointF pBFL = MathUtil::add(pBM, vBDF);
            QPointF pDFR = MathUtil::subtract(pDM, vBDF);

            // A, B, C, D frog points
            QPointF pAFR = MathUtil::add(MathUtil::add(pAFL, vACMo), vACMo);
            QPointF pBFR = MathUtil::subtract(MathUtil::subtract(pBFL, vBDMo), vBDMo);
            QPointF pCFL = MathUtil::subtract(MathUtil::subtract(pCFR, vACMo), vACMo);
            QPointF pDFL = MathUtil::add(MathUtil::add(pDFR, vBDMo), vBDMo);

            // end of switch rails (closed)
            QPointF vABF = MathUtil::normalize(vAB, hypotF);
            pAP = MathUtil::subtract(pAM, vABF);
            pAPL = MathUtil::subtract(pAP, vABo);
            pAPR = MathUtil::add(pAP, vABo);
            QPointF pBP = MathUtil::add(pBM, vABF);
            QPointF pBPL = MathUtil::subtract(pBP, vABo);
            QPointF pBPR = MathUtil::add(pBP, vABo);

            QPointF vCDF = MathUtil::normalize(vCD, hypotF);
            QPointF pCP = MathUtil::subtract(pCM, vCDF);
            QPointF pCPL = MathUtil::add(pCP, vCDo);
            QPointF pCPR = MathUtil::subtract(pCP, vCDo);
            QPointF pDP = MathUtil::add(pDM, vCDF);
            QPointF pDPL = MathUtil::add(pDP, vCDo);
            QPointF pDPR = MathUtil::subtract(pDP, vCDo);

            // end of switch rails (open)
            QPointF vS = MathUtil::normalize(vABo, 2.0);
            QPointF pASL = MathUtil::add(pAPL, vS);
            // QPointF pASR = MathUtil::subtract(pAPR, vS);
            QPointF pBSL = MathUtil::add(pBPL, vS);
            // QPointF pBSR = MathUtil::subtract(pBPR, vS);
            QPointF pCSR = MathUtil::subtract(pCPR, vS);
            // QPointF pCSL = MathUtil::add(pCPL, vS);
            QPointF pDSR = MathUtil::subtract(pDPR, vS);
            // QPointF pDSL = MathUtil::add(pDPL, vS);

            // end of switch rails (open at frogs)
            QPointF pAFS = MathUtil::subtract(pAFL, vS);
            QPointF pBFS = MathUtil::subtract(pBFL, vS);
            QPointF pCFS = MathUtil::add(pCFR, vS);
            QPointF pDFS = MathUtil::add(pDFR, vS);

            // vSo = MathUtil::orthogonal(vS);
            // QPointF pAFSR = MathUtil::add(pAFL, vSo);
            // QPointF pBFSR = MathUtil::subtract(pBFL, vSo);
            // QPointF pCFSL = MathUtil::subtract(pCFR, vSo);
            // QPointF pDFSL = MathUtil::add(pDFR, vSo);

            if (isMain == mainlineA) {
                //g2.draw(new Line2D.Double(pAL, pABL));
             lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pABL.x(), pABL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pVRtB, pKLtD));
             lineItem = new QGraphicsLineItem(pVRtB.x(), pVRtB.y(), pKLtD.x(), pKLtD.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pAFL, pABR));
             lineItem = new QGraphicsLineItem(pAFL.x(), pAFL.y(), pABR.x(), pABR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
               //g2.draw(new Line2D.Double(pAFL, pKL));
             lineItem = new QGraphicsLineItem(pAFL.x(), pAFL.y(), pKL.x(), pKL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path = QPainterPath();
                path.moveTo(pAR.x(), pAR.y());
                path.lineTo(pAPR.x(), pAPR.y());
                path.quadTo(pAMR.x(), pAMR.y(), pAFR.x(), pAFR.y());
                path.lineTo(pVR.x(), pVR.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (state != Turnout::CLOSED) {  // unknown or diverting path
                    path = QPainterPath();
                    path.moveTo(pAPL.x(), pAPL.y());
                    path.quadTo(pAML.x(), pAML.y(), pAFL.x(), pAFL.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);//                         g2.draw(new Line2D.Double(pASR, pAFSR));
                } else {                        // continuing path
                    //g2.draw(new Line2D.Double(pAPR, pAFL));
                 lineItem = new QGraphicsLineItem(pAPR.x(), pAPR.y(), pAFL.x(), pAFL.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                 path = QPainterPath();
                    path.moveTo(pASL.x(), pASL.y());
                    path.quadTo(pAML.x(), pAML.y(), pAFS.x(), pAFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineB) {
                //g2.draw(new Line2D.Double(pABL, pBL));
             lineItem = new QGraphicsLineItem(pABL.x(), pABL.y(), pBL.x(), pBL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pKLtC, pVLtA));
             lineItem = new QGraphicsLineItem(pKLtC.x(), pKLtC.y(), pVLtA.x(), pVLtA.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pBFL, pABR));
             lineItem = new QGraphicsLineItem(pBFL.x(), pBFL.y(), pABR.x(), pABR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pBFL, pKL));
             lineItem = new QGraphicsLineItem(pBFL.x(), pBFL.y(), pKL.x(), pKL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path =  QPainterPath();
                path.moveTo(pBR.x(), pBR.y());
                path.lineTo(pBPR.x(), pBPR.y());
                path.quadTo(pBMR.x(), pBMR.y(), pBFR.x(), pBFR.y());
                path.lineTo(pVL.x(), pVL.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (state != Turnout::CLOSED) {  // unknown or diverting path
                    path = QPainterPath();
                    path.moveTo(pBPL.x(), pBPL.y());
                    path.quadTo(pBML.x(), pBML.y(), pBFL.x(), pBFL.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);//                         g2.draw(new Line2D.Double(pBSR, pBFSR));
                } else {
                    //g2.draw(new Line2D.Double(pBPR, pBFL));
                 lineItem = new QGraphicsLineItem(pBPR.x(), pBPR.y(), pBFL.x(), pBFL.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                 path = QPainterPath();
                    path.moveTo(pBSL.x(), pBSL.y());
                    path.quadTo(pBML.x(), pBML.y(), pBFS.x(), pBFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineC) {
                //g2.draw(new Line2D.Double(pCR, pCDR));
             lineItem = new QGraphicsLineItem(pCR.x(), pCR.y(), pCR.x(), pCDR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pKRtB, pVLtD));
             lineItem = new QGraphicsLineItem(pKRtB.x(), pKRtB.y(), pVLtD.x(), pVLtD.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pCFR, pCDL));
             lineItem = new QGraphicsLineItem(pCFR.x(), pCFR.y(), pCDL.x(), pCDL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pCFR, pKR));
             lineItem = new QGraphicsLineItem(pCFR.x(), pCFR.y(), pKR.x(), pKR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path = QPainterPath();
                path.moveTo(pCL.x(), pCL.y());
                path.lineTo(pCPL.x(), pCPL.y());
                path.quadTo(pCML.x(), pCML.y(), pCFL.x(), pCFL.y());
                path.lineTo(pVL.x(), pVL.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (state != Turnout::CLOSED) {  // unknown or diverting path
                    path = QPainterPath();
                    path.moveTo(pCPR.x(), pCPR.y());
                    path.quadTo(pCMR.x(), pCMR.y(), pCFR.x(), pCFR.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);
                    //                         g2.draw(new Line2D.Double(pCSL, pCFSL));
                } else {
                    //g2.draw(new Line2D.Double(pCPL, pCFR));
                 lineItem = new QGraphicsLineItem(pCPL.x(), pCPL.y(), pCFR.x(), pCFR.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                 path = QPainterPath();
                    path.moveTo(pCSR.x(), pCSR.y());
                    path.quadTo(pCMR.x(), pCMR.y(), pCFS.x(), pCFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineD) {
                //g2.draw(new Line2D.Double(pCDR, pDR));
             lineItem = new QGraphicsLineItem(pCDR.x(), pCDR.y(), pDR.x(), pDR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pKRtA, pVRtC));
             lineItem = new QGraphicsLineItem(pKRtA.x(), pKRtA.y(), pVRtC.x(), pVRtC.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pDFR, pCDL));
             lineItem = new QGraphicsLineItem(pDFR.x(), pDFR.y(), pCDL.x(), pCDL.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pDFR, pKR));
             lineItem = new QGraphicsLineItem(pDFR.x(), pDFR.y(), pKR.x(), pKR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path = QPainterPath();
                path.moveTo(pDL.x(), pDL.y());
                path.lineTo(pDPL.x(), pDPL.y());
                path.quadTo(pDML.x(), pDML.y(), pDFL.x(), pDFL.y());
                path.lineTo(pVR.x(), pVR.y());
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(layoutEditor->drawingStroke);
                itemGroup->addToGroup(pathItem);
                if (state != Turnout::CLOSED) {  // unknown or diverting path
                    path = QPainterPath();
                    path.moveTo(pDPR.x(), pDPR.y());
                    path.quadTo(pDMR.x(), pDMR.y(), pDFR.x(), pDFR.y());
                    //g2.draw(path);
                    pathItem = new QGraphicsPathItem(path);
                    pathItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(pathItem);
                    //                         g2.draw(new Line2D.Double(pDSL, pDFSL));
                } else {
                    //g2.draw(new Line2D.Double(pDPL, pDFR));
                 lineItem = new QGraphicsLineItem(pDPL.x(), pDPL.y(), pDFR.x(), pDFR.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                 path = QPainterPath();
                    path.moveTo(pDSR.x(), pDSR.y());
                    path.quadTo(pDMR.x(), pDMR.y(), pDFS.x(), pDFS.y());
//                         g2.draw(path);
                }
            }
            break;
        }   // case DOUBLE_XOVER
#if 0
        case RH_XOVER: {
            // A, B, C, D end points (left and right)
            QPointF vAB = MathUtil::normalize(MathUtil::subtract(pB, pA), railDisplacement);
            double dirAB_DEG = MathUtil::computeAngleDEG(vAB);
            QPointF vABo = MathUtil::orthogonal(MathUtil::normalize(vAB, railDisplacement));
            pAL = MathUtil::subtract(pA, vABo);
            pAR = MathUtil::add(pA, vABo);
            pBL = MathUtil::subtract(pB, vABo);
            pBR = MathUtil::add(pB, vABo);
            QPointF vCD = MathUtil::normalize(MathUtil::subtract(pD, pC), railDisplacement);
            QPointF vCDo = MathUtil::orthogonal(MathUtil::normalize(vCD, railDisplacement));
            pCL = MathUtil::add(pC, vCDo);
            pCR = MathUtil::subtract(pC, vCDo);
            QPointF pDL = MathUtil::add(pD, vCDo);
            QPointF pDR = MathUtil::subtract(pD, vCDo);

            // AB and CD mid points
            QPointF pABM = MathUtil::midPoint(pA, pB);
            QPointF pABL = MathUtil::subtract(pABM, vABo);
            QPointF pABR = MathUtil::add(pABM, vABo);
            QPointF pCDM = MathUtil::midPoint(pC, pD);
            QPointF pCDL = MathUtil::subtract(pCDM, vABo);
            QPointF pCDR = MathUtil::add(pCDM, vABo);

            // directions
            QPointF vAC = MathUtil::normalize(MathUtil::subtract(pCDM, pABM), railDisplacement);
            QPointF vACo = MathUtil::orthogonal(MathUtil::normalize(vAC, railDisplacement));
            double dirAC_DEG = MathUtil::computeAngleDEG(vAC);
            double deltaBAC_DEG = MathUtil::absDiffAngleDEG(dirAB_DEG, dirAC_DEG);
            double deltaBAC_RAD = Math.toRadians(deltaBAC_DEG);

            // AC mid points
            QPointF pACL = MathUtil::subtract(pM, vACo);
            QPointF pACR = MathUtil::add(pM, vACo);

            // frogs
            hypotF = railDisplacement / Math.sin(deltaBAC_RAD / 2.0);
            QPointF vF = MathUtil::normalize(MathUtil::add(vAB, vAC), hypotF);
            QPointF pABF = MathUtil::add(pABM, vF);
            QPointF pCDF = MathUtil::subtract(pCDM, vF);

            // frog primes
            QPointF pABFP = MathUtil::add(MathUtil::add(pABF, vACo), vACo);
            QPointF pCDFP = MathUtil::subtract(MathUtil::subtract(pCDF, vACo), vACo);

            // end of switch rails (closed)
            QPointF vABF = MathUtil::normalize(vAB, hypotF);
            pAP = MathUtil::subtract(pABM, vABF);
            pAPL = MathUtil::subtract(pAP, vABo);
            pAPR = MathUtil::add(pAP, vABo);
            QPointF pCP = MathUtil::add(pCDM, vABF);
            QPointF pCPL = MathUtil::add(pCP, vCDo);
            QPointF pCPR = MathUtil::subtract(pCP, vCDo);

            // end of switch rails (open)
            QPointF vS = MathUtil::normalize(vAB, 2.0);
            QPointF vSo = MathUtil::orthogonal(vS);
            QPointF pASL = MathUtil::add(pAPL, vSo);
            // QPointF pASR = MathUtil::subtract(pAPR, vSo);
            // QPointF pCSL = MathUtil::add(pCPL, vSo);
            QPointF pCSR = MathUtil::subtract(pCPR, vSo);

            // end of switch rails (open at frogs)
            QPointF pABFS = MathUtil::subtract(pABF, vSo);
            // QPointF pABFSP = MathUtil::subtract(pABF, vS);
            QPointF pCDFS = MathUtil::add(pCDF, vSo);
            // QPointF pCDFSP = MathUtil::add(pCDF, vS);

            if (isMain == mainlineA) {
                g2.draw(new Line2D.Double(pAL, pABL));
                QPainterPath path = new QPainterPath();
                path.moveTo(pAR.x(), pAR.y());
                path.lineTo(pAPR.x(), pAPR.y());
                path.quadTo(pABR.x(), pABR.y(), pABFP.x(), pABFP.y());
                path.lineTo(pACR.x(), pACR.y());
                g2.draw(path);
                g2.draw(new Line2D.Double(pABF, pACL));
                if (state != Turnout.CLOSED) {  // unknown or diverting path
                    path = new QPainterPath();
                    path.moveTo(pAPL.x(), pAPL.y());
                    path.quadTo(pABL.x(), pABL.y(), pABF.x(), pABF.y());
                    g2.draw(path);
//                         g2.draw(new Line2D.Double(pASR, pABFSP));
                } else {                        // continuing path
                    g2.draw(new Line2D.Double(pAPR, pABF));
                    path = new QPainterPath();
                    path.moveTo(pASL.x(), pASL.y());
                    path.quadTo(pABL.x(), pABL.y(), pABFS.x(), pABFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineB) {
                g2.draw(new Line2D.Double(pABL, pBL));
                g2.draw(new Line2D.Double(pABF, pBR));
            }
            if (isMain == mainlineC) {
                g2.draw(new Line2D.Double(pCR, pCDR));
                QPainterPath path = new QPainterPath();
                path.moveTo(pCL.x(), pCL.y());
                path.lineTo(pCPL.x(), pCPL.y());
                path.quadTo(pCDL.x(), pCDL.y(), pCDFP.x(), pCDFP.y());
                path.lineTo(pACL.x(), pACL.y());
                g2.draw(path);
                g2.draw(new Line2D.Double(pCDF, pACR));
                if (state != Turnout.CLOSED) {  // unknown or diverting path
                    path = new QPainterPath();
                    path.moveTo(pCPR.x(), pCPR.y());
                    path.quadTo(pCDR.x(), pCDR.y(), pCDF.x(), pCDF.y());
                    g2.draw(path);
//                         g2.draw(new Line2D.Double(pCSL, pCDFSP));
                } else {                        // continuing path
                    g2.draw(new Line2D.Double(pCPL, pCDF));
                    path = new QPainterPath();
                    path.moveTo(pCSR.x(), pCSR.y());
                    path.quadTo(pCDR.x(), pCDR.y(), pCDFS.x(), pCDFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineD) {
                g2.draw(new Line2D.Double(pCDR, pDR));
                g2.draw(new Line2D.Double(pCDF, pDL));
            }
            break;
        }   // case RH_XOVER

        case LH_XOVER: {
            // B, A, D, C end points (left and right)
            QPointF vBA = MathUtil::normalize(MathUtil::subtract(pA, pB), railDisplacement);
            double dirBA_DEG = MathUtil::computeAngleDEG(vBA);
            QPointF vBAo = MathUtil::orthogonal(MathUtil::normalize(vBA, railDisplacement));
            pBL = MathUtil::add(pB, vBAo);
            pBR = MathUtil::subtract(pB, vBAo);
            pAL = MathUtil::add(pA, vBAo);
            pAR = MathUtil::subtract(pA, vBAo);
            QPointF vDC = MathUtil::normalize(MathUtil::subtract(pC, pD), railDisplacement);
            QPointF vDCo = MathUtil::orthogonal(MathUtil::normalize(vDC, railDisplacement));
            QPointF pDL = MathUtil::subtract(pD, vDCo);
            QPointF pDR = MathUtil::add(pD, vDCo);
            pCL = MathUtil::subtract(pC, vDCo);
            pCR = MathUtil::add(pC, vDCo);

            // BA and DC mid points
            QPointF pBAM = MathUtil::midPoint(pB, pA);
            QPointF pBAL = MathUtil::add(pBAM, vBAo);
            QPointF pBAR = MathUtil::subtract(pBAM, vBAo);
            QPointF pDCM = MathUtil::midPoint(pD, pC);
            QPointF pDCL = MathUtil::add(pDCM, vBAo);
            QPointF pDCR = MathUtil::subtract(pDCM, vBAo);

            // directions
            QPointF vBD = MathUtil::normalize(MathUtil::subtract(pDCM, pBAM), railDisplacement);
            QPointF vBDo = MathUtil::orthogonal(MathUtil::normalize(vBD, railDisplacement));
            double dirBD_DEG = MathUtil::computeAngleDEG(vBD);
            double deltaABD_DEG = MathUtil::absDiffAngleDEG(dirBA_DEG, dirBD_DEG);
            double deltaABD_RAD = Math.toRadians(deltaABD_DEG);

            // BD mid points
            QPointF pBDL = MathUtil::add(pM, vBDo);
            QPointF pBDR = MathUtil::subtract(pM, vBDo);

            // frogs
            hypotF = railDisplacement / Math.sin(deltaABD_RAD / 2.0);
            QPointF vF = MathUtil::normalize(MathUtil::add(vBA, vBD), hypotF);
            QPointF pBFL = MathUtil::add(pBAM, vF);
            QPointF pBF = MathUtil::subtract(pBFL, vBDo);
            QPointF pBFR = MathUtil::subtract(pBF, vBDo);
            QPointF pDFR = MathUtil::subtract(pDCM, vF);
            QPointF pDF = MathUtil::add(pDFR, vBDo);
            QPointF pDFL = MathUtil::add(pDF, vBDo);

            // end of switch rails (closed)
            QPointF vBAF = MathUtil::normalize(vBA, hypotF);
            QPointF pBP = MathUtil::subtract(pBAM, vBAF);
            QPointF pBPL = MathUtil::add(pBP, vBAo);
            QPointF pBPR = MathUtil::subtract(pBP, vBAo);
            QPointF pDP = MathUtil::add(pDCM, vBAF);
            QPointF pDPL = MathUtil::subtract(pDP, vDCo);
            QPointF pDPR = MathUtil::add(pDP, vDCo);

            // end of switch rails (open)
            QPointF vS = MathUtil::normalize(vBA, 2.0);
            QPointF vSo = MathUtil::orthogonal(vS);
            QPointF pBSL = MathUtil::subtract(pBPL, vSo);
            // QPointF pBSR = MathUtil::add(pBPR, vSo);
            // QPointF pDSL = MathUtil::subtract(pDPL, vSo);
            QPointF pDSR = MathUtil::add(pDPR, vSo);

            // end of switch rails (open at frogs)
            QPointF pBAFS = MathUtil::add(pBFL, vSo);
            // QPointF pBAFSP = MathUtil::subtract(pBFL, vS);
            QPointF pDCFS = MathUtil::subtract(pDFR, vSo);
            // QPointF pDCFSP = MathUtil::add(pDFR, vS);

            if (isMain == mainlineA) {
                g2.draw(new Line2D.Double(pBAL, pAL));
                g2.draw(new Line2D.Double(pBFL, pAR));
            }
            if (isMain == mainlineB) {
                g2.draw(new Line2D.Double(pBL, pBAL));
                QPainterPath path = new QPainterPath();
                path.moveTo(pBR.x(), pBR.y());
                path.lineTo(pBPR.x(), pBPR.y());
                path.quadTo(pBAR.x(), pBAR.y(), pBFR.x(), pBFR.y());
                path.lineTo(pBDR.x(), pBDR.y());
                g2.draw(path);
                g2.draw(new Line2D.Double(pBFL, pBDL));
                if (state != Turnout.CLOSED) {  // unknown or diverting path
                    path = new QPainterPath();
                    path.moveTo(pBPL.x(), pBPL.y());
                    path.quadTo(pBAL.x(), pBAL.y(), pBFL.x(), pBFL.y());
                    g2.draw(path);
//                         g2.draw(new Line2D.Double(pBSR, pBAFSP));
                } else {                        // continuing path
                    g2.draw(new Line2D.Double(pBPR, pBFL));
                    path = new QPainterPath();
                    path.moveTo(pBSL.x(), pBSL.y());
                    path.quadTo(pBAL.x(), pBAL.y(), pBAFS.x(), pBAFS.y());
//                         g2.draw(path);
                }
            }
            if (isMain == mainlineC) {
                g2.draw(new Line2D.Double(pDCR, pCR));
                g2.draw(new Line2D.Double(pDFR, pCL));
            }
            if (isMain == mainlineD) {
                g2.draw(new Line2D.Double(pDR, pDCR));
                QPainterPath path = new QPainterPath();
                path.moveTo(pDL.x(), pDL.y());
                path.lineTo(pDPL.x(), pDPL.y());
                path.quadTo(pDCL.x(), pDCL.y(), pDFL.x(), pDFL.y());
                path.lineTo(pBDL.x(), pBDL.y());
                g2.draw(path);
                g2.draw(new Line2D.Double(pDFR, pBDR));
                if (state != Turnout.CLOSED) {  // unknown or diverting path
                    path = new QPainterPath();
                    path.moveTo(pDPR.x(), pDPR.y());
                    path.quadTo(pDCR.x(), pDCR.y(), pDFR.x(), pDFR.y());
                    g2.draw(path);
//                         g2.draw(new Line2D.Double(pDSL, pDCFSP));
                } else {                        // continuing path
                    g2.draw(new Line2D.Double(pDPL, pDFR));
                    path = new QPainterPath();
                    path.moveTo(pDSR.x(), pDSR.y());
                    path.quadTo(pDCR.x(), pDCR.y(), pDCFS.x(), pDCFS.y());
//                         g2.draw(path);
                }
            }
            break;
        }   // case LH_XOVER
#endif
        case SINGLE_SLIP:
        case DOUBLE_SLIP: {
            log->error("slips should be being drawn by LayoutSlip sub-class");
            break;
        }
        default: {
            // this should never happen... but...
            log->error("Unknown turnout type: " + toType);
            break;
        }
    }
//    if(isMain)
//    {
     itemMain = itemGroup;
     g2->addItem(itemMain);
//    }
//    else
//    {
//     itemSide = itemGroup;
//     g2->addItem(itemSide);
//    }
}
#if 1
/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnout::highlightUnconnected(EditScene* g2, int specificType) {
    if (((specificType == NONE) || (specificType == TURNOUT_A))
            && (getConnectA() == nullptr)) {
        //g2.fill(layoutEditor->trackControlCircleAt(getCoordsA()));
     QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsA());
     item->setPen(QPen(defaultTrackColor, 1));
    }

    if (((specificType == NONE) || (specificType == TURNOUT_B))
            && (getConnectB() == nullptr)) {
        //g2.fill(layoutEditor->trackControlCircleAt(getCoordsB()));
     QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsB());
     item->setPen(QPen(defaultTrackColor, 1));
    }

    if (((specificType == NONE) || (specificType == TURNOUT_C))
            && (getConnectC() == nullptr)) {
        //g2.fill(layoutEditor->trackControlCircleAt(getCoordsC()));
     QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsC());
     item->setPen(QPen(defaultTrackColor, 1));
    }
    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == RH_XOVER)
            || (getTurnoutType() == LH_XOVER)) {
        if (((specificType == NONE) || (specificType == TURNOUT_D))
                && (getConnectD() == nullptr)) {
            //g2.fill(layoutEditor.trackControlCircleAt(getCoordsD()));
         QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsD());
         item->setPen(QPen(defaultTrackColor, 1));
        }
    }
    rects = item;
    g2->addItem(rects);

}

//@Override
/*protected*/ void LayoutTurnout::drawTurnoutControls(EditScene* g2)
{
 if (!disabled && !(disableWhenOccupied && isOccupied()))
 {
  invalidateItem(g2,circles);
  QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
  if (!disabled && !(disableWhenOccupied && isOccupied()))
  {
   //QColor foregroundColor = g2.getColor();
   //if turnout is not continuing state
//   if (getState() != continuingSense) {
//       //then switch to background color
//       g2.setColor(g2.getBackground());
//   }

      //g2.draw(layoutEditor.trackControlCircleAt(center));
   QGraphicsEllipseItem* item = trackControlCircleAt(center);
   item->setPen(layoutEditor->drawingStroke);
   if (layoutEditor->isTurnoutFillControlCircles()) {
    QBrush brush = QBrush(layoutEditor->drawingStroke.color());
    item->setBrush(brush);
   }
   itemGroup->addToGroup(item);
   //if turnout is not continuing state
//   if (getState() != continuingSense) {
//       //then restore foreground color
//       g2.setColor(foregroundColor);
//   }
   circles = itemGroup;
   g2->addItem(circles);
  }
 }
}

//@Override
/*protected*/ void LayoutTurnout::drawEditControls(EditScene* g2)
{
 invalidateItem(g2,rects);
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 if(rects!=nullptr && rects->scene()!=nullptr)
 {
  g2->removeItem(rects);
  rects = nullptr;
 }

    QPointF pt = getCoordsA();
    if (getTurnoutType() >= DOUBLE_XOVER && getTurnoutType() <= DOUBLE_SLIP)
    {
        if (getConnectA() == nullptr) {
            //g2.setColor(Color.magenta);
         layoutEditor->drawingStroke.setColor(QColor(Qt::magenta));
        } else {
            //g2.setColor(Color.blue);
         layoutEditor->drawingStroke.setColor(Qt::blue);
        }
    } else {
        if (getConnectA() == nullptr) {
            //g2.setColor(Color.red);
         layoutEditor->drawingStroke.setColor(Qt::red);
        } else {
            //g2.setColor(Color.green);
         layoutEditor->drawingStroke.setColor(Qt::green);
        }
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(pt));
    QGraphicsRectItem* item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
    item->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(item);

    pt = getCoordsB();
    if (getConnectB() == nullptr) {
        //g2.setColor(Color.red);
     layoutEditor->drawingStroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     layoutEditor->drawingStroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(pt));
    item =  new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
    item->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(item);

    pt = getCoordsC();
    if (getConnectC() == nullptr) {
     //g2.setColor(Color.red);
     layoutEditor->drawingStroke.setColor(Qt::red);
    } else {
     //g2.setColor(Color.green);
     layoutEditor->drawingStroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor.trackEditControlRectAt(pt));
    item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
    item->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(item);

    if ((getTurnoutType() == DOUBLE_XOVER)
            || (getTurnoutType() == RH_XOVER)
            || (getTurnoutType() == LH_XOVER)
            || (getTurnoutType() == SINGLE_SLIP)
            || (getTurnoutType() == DOUBLE_SLIP)) {
        pt = getCoordsD();
        if (getConnectD() == nullptr) {
         //g2.setColor(Color.red);
         layoutEditor->drawingStroke.setColor(Qt::red);
        } else {
         //g2.setColor(Color.green);
         layoutEditor->drawingStroke.setColor(Qt::green);
        //g2.draw(layoutEditor.trackEditControlRectAt(pt));
         item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
         item->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(item);
        }
        rects = itemGroup;
        g2->addItem(rects);
    }
}   // drawEditControls

#endif

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

void LayoutTurnout::invalidate(EditScene *g2)
{
 itemMain =invalidateItem(g2,itemMain);
 itemSide = invalidateItem(g2, itemSide);
 //invalidateItem(itemSide);
 rects=invalidateItem(g2,rects);
 circles = invalidateItem(g2,circles);
 item = invalidateItem(g2, item);
 itemTies = invalidateItem(g2, itemTies);
 itemTiesSide = invalidateItem(g2, itemTiesSide);
 itemBallast = invalidateItem(g2, itemBallast);
 itemBallastSide = invalidateItem(g2, itemBallastSide);
}

#if 0
void LayoutTurnout::drawTurnouts(LayoutEditor *editor, QGraphicsScene *g2)
{
 QColor color;
 QGraphicsItemGroup* group = new QGraphicsItemGroup();
 LayoutBlock* b = getLayoutBlock();
 if (b!=nullptr)
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
   if (t1==nullptr)
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
    if (b!=nullptr)
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
    if (b!=nullptr) color = b->getBlockColor();
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
    if (b!=nullptr) color = (b->getBlockColor());
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
     if (b!=nullptr) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsA(),
//                              third(t.getCoordsA(),t.getCoordsC())));
     QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsC())), 0);
     line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line2);
     group->addToGroup(line2);

     b = getLayoutBlockB();
     if (b!=nullptr) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineB());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              midpoint(t.getCoordsA(),t.getCoordsB())));
     QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->midpoint(getCoordsA(),getCoordsB())), 0);
     line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line3);
     group->addToGroup(line3);
     editor->setTrackStrokeWidth(false);
     if (b!=nullptr) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsB(),
//                              third(t.getCoordsB(),t.getCoordsD())));
     QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsD())), 0);
     line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line4);
     group->addToGroup(line4);
     b = getLayoutBlockC();
     if (b!=nullptr) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineC());
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              midpoint(t.getCoordsC(),t.getCoordsD())));
     QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
     line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line5);
     group->addToGroup(line5);

     editor->setTrackStrokeWidth(false);
     if (b!=nullptr) color=(b->getBlockTrackColor());
//      g2.draw(new Line2D.Double(t.getCoordsC(),
//                              third(t.getCoordsC(),t.getCoordsA())));
     QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsA())), 0);
     line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line6);
     group->addToGroup(line6);

     b = getLayoutBlockD();
     if (b!=nullptr) color=(b->getBlockColor());
     else color=(editor->defaultTrackColor);
     editor->setTrackStrokeWidth(isMainlineD());
//      g2.draw(new Line2D.Double(t.getCoordsD(),
//                              midpoint(t.getCoordsC(),t.getCoordsD())));
     QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->midpoint(getCoordsC(),getCoordsD())), 0);
     line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
     //g2->addItem(line7);
     group->addToGroup(line7);

     editor->setTrackStrokeWidth(false);
     if (b!=nullptr) color=(b->getBlockTrackColor());
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
   if (b!=nullptr) color=(b->getBlockTrackColor());
   editor->setTrackStrokeWidth(isMainlineA());
//  g2.draw(new Line2D.Double(t.getCoordsA(),
//                          third(t.getCoordsA(),t.getCoordsB())));
   QGraphicsLineItem* line1 = new QGraphicsLineItem(QLineF(getCoordsA(),editor->third(getCoordsA(),getCoordsB())), 0);
   line1->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line1);
   group->addToGroup(line1);

   editor->setTrackStrokeWidth(false);
   if (b!=nullptr) color=(b->getBlockColor());
//  g2.draw(new Line2D.Double(t.getCoordsA(),t.getCoordsCenter()));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsA(),getCoordsCenter()), 0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);

   b = getLayoutBlockB();
   if (b!=nullptr) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineB());
//  g2.draw(new Line2D.Double(t.getCoordsB(),
//                          third(t.getCoordsB(),t.getCoordsA())));
   QGraphicsLineItem* line3 = new QGraphicsLineItem(QLineF(getCoordsB(),editor->third(getCoordsB(),getCoordsA())), 0);
   line3->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line3);
   group->addToGroup(line3);
   editor->setTrackStrokeWidth(false);
   if (b!=nullptr) color=(b->getBlockColor());

//  g2.draw(new Line2D.Double(t.getCoordsB(),t.getCoordsCenter()));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsB(),getCoordsCenter()), 0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);

   b = getLayoutBlockC();
   if (b!=nullptr) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineC());
//  g2.draw(new Line2D.Double(t.getCoordsC(),
//                          third(t.getCoordsC(),t.getCoordsD())));
   QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(),editor->third(getCoordsC(),getCoordsD())), 0);
   line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line5);
   group->addToGroup(line5);

   editor->setTrackStrokeWidth(false);
   if (b!=nullptr) color=(b->getBlockColor());
//  g2.draw(new Line2D.Double(t.getCoordsC(),t.getCoordsCenter()));
   QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsC(),getCoordsCenter()), 0);
   line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line6);
   group->addToGroup(line6);

   b = getLayoutBlockD();

   if (b!=nullptr) color=(b->getBlockTrackColor());
   else color=(editor->defaultTrackColor);
   editor->setTrackStrokeWidth(isMainlineD());
//  g2.draw(new Line2D.Double(t.getCoordsD(),
//                          third(t.getCoordsD(),t.getCoordsC())));
   QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),editor->third(getCoordsD(),getCoordsC())), 0);
   line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line7);
   group->addToGroup(line7);
   editor->setTrackStrokeWidth(false);
   if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockColor());
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
  if (t1==nullptr)
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
   if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockColor());
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
  if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockTrackColor());
//              g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(), midpoint(t.getCoordsA(),t.getCoordsB()))));
   QGraphicsLineItem* line2 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
   line2->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line2);
   group->addToGroup(line2);
  }
  b = getLayoutBlockB();
  if (b!=nullptr) color=(b->getBlockColor());
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
   if (b!=nullptr) color=(b->getBlockTrackColor());
//              g2.draw(new Line2D.Double(t.getCoordsCenter(), third(t.getCoordsCenter(),midpoint(t.getCoordsA(),t.getCoordsB()))));
   QGraphicsLineItem* line4 = new QGraphicsLineItem(QLineF(getCoordsCenter(), editor->third(getCoordsCenter(),editor->midpoint(getCoordsA(),getCoordsB()))),0);
   line4->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
   //g2->addItem(line4);
   group->addToGroup(line4);
  }
  b = getLayoutBlockC();
  if (b!=nullptr) color=(b->getBlockColor());
  else color=(editor->defaultTrackColor);
  editor->setTrackStrokeWidth(isMainlineC());
//          g2.draw(new Line2D.Double(t.getCoordsC(), midpoint(t.getCoordsC(),t.getCoordsD())));
  QGraphicsLineItem* line5 = new QGraphicsLineItem(QLineF(getCoordsC(), editor->midpoint(getCoordsC(),getCoordsD())),0);
  line5->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line5);
  group->addToGroup(line5);
  if (ttype == LayoutTurnout::RH_XOVER) {
  editor->setTrackStrokeWidth(false);
  if (b!=nullptr) color=(b->getBlockTrackColor());
//   g2.draw(new Line2D.Double(t.getCoordsCenter(),  third(t.getCoordsCenter(),midpoint(t.getCoordsC(),t.getCoordsD()))));
  QGraphicsLineItem* line6 = new QGraphicsLineItem(QLineF(getCoordsCenter(),  editor->third(getCoordsCenter(), editor->midpoint(getCoordsC(), getCoordsD()))),0);
  line6->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
  //g2->addItem(line6);
  group->addToGroup(line6);
 }
 b = getLayoutBlockD();
 if (b!=nullptr) color=(b->getBlockColor());
 else color=(editor->defaultTrackColor);
 editor->setTrackStrokeWidth(isMainlineD());
//  g2.draw(new Line2D.Double(t.getCoordsD(),  midpoint(t.getCoordsC(),t.getCoordsD())));
 QGraphicsLineItem* line7 = new QGraphicsLineItem(QLineF(getCoordsD(),  editor->midpoint(getCoordsC(),getCoordsD())),0);
 line7->setPen(QPen(color,editor->trackWidth,Qt::SolidLine));
 //g2->addItem(line7);
 group->addToGroup(line7);
 if (ttype == LayoutTurnout::LH_XOVER) {
 editor->setTrackStrokeWidth(false);
 if (b!=nullptr) color=(b->getBlockTrackColor());
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
if (b!=nullptr) color=(b->getBlockColor());
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
if (b!=nullptr) color=(b->getBlockColor());
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
if (b!=nullptr) color=(b->getBlockColor());
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
 if (b!=nullptr) color=(b->getBlockColor());
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
 if (b!=nullptr) color=(b->getBlockColor());
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
  if (b!=nullptr) color=(b->getBlockColor());
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
 if (t2==nullptr)
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
     if (b!=nullptr) color=(b->getBlockTrackColor());
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
     if (b!=nullptr) color=(b->getBlockTrackColor());
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
        if (b!=nullptr) color=(b->getBlockTrackColor());
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
        if (b!=nullptr) color=(b->getBlockTrackColor());
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
//      g2.setColor(turnoutCircleColor != nullptr ? turnoutCircleColor : defaultTrackColor);
//      g2.draw(new Ellipse2D.Double (
//                      pt.x()-SIZE2, pt.y()-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));

 QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(pt.x()-LayoutEditor::SIZE2, pt.y()-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, 0);
 ellipse->setPen(QPen(editor->turnoutCircleColor.isValid() ? editor->turnoutCircleColor : editor->defaultTrackColor, 1, Qt::SolidLine ) );
 //g2->addItem(ellipse);
 group->addToGroup(ellipse);

 pt = getCoordsA();
 if (getConnectA()==nullptr) {
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
 if (getConnectB()==nullptr) {
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
 if (getConnectC()==nullptr)
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
  if (getConnectD()==nullptr)
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
//          g2.setColor(turnoutCircleColor != nullptr ? turnoutCircleColor : defaultTrackColor);
//          g2.draw(new Ellipse2D.Double (
//                          pt.x()-size, pt.y()-size, size+size, size+size));
 if(circle != nullptr)
  g2->removeItem(circle);
 circle = new QGraphicsEllipseItem(pt.x()-size, pt.y()-size, size+size, size+size,0);
 circle->setPen( QPen( editor->turnoutCircleColor.isValid() ? editor->turnoutCircleColor : editor->defaultTrackColor, 1, Qt::SolidLine ) );
 g2->addItem(circle);
}

void LayoutTurnout::repaint(LayoutEditor *editor, QGraphicsScene *g2)
{
 //invalidate(g2);
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
#endif
void LayoutTurnout::redrawPanel()
{
 invalidate(layoutEditor->getTargetPanel());
 layoutEditor->redrawPanel();
}



/*static*/ Logger* LayoutTurnout::log = LoggerFactory::getLogger("LayoutTurnout");
