#include "tracksegment.h"
#include "edittracksegmentdlg.h"
#include <QMenu>
#include "abstractaction.h"
#include "layoutblockroutetableaction.h"
#include "layoutturntable.h"
#include "layouteditorfinditems.h"
#include "jmricolorchooser.h"
#include "layouttrackdrawingoptions.h"
#include <QPointF>
#include "mathutil.h"
#include "loggerfactory.h"
#include "colorutil.h"

//TrackSegment::TrackSegment(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * TrackSegment is a segment of track on a layout linking two nodes of the
 *     layout.  A node may be a LayoutTurnout, a LevelXing or a PositionablePoint.
 * <P>
 * PositionablePoints have 1 or 2 connection points. LayoutTurnouts
 *		have 3 or 4 (crossovers) connection points, designated A, B, C, and D.
 *		LevelXing's have 4 connection points, designated A, B, C, and D.
 * <P>
 * TrackSegments carry the connectivity information between the three types of nodes. Track Segments
 *		serve as the lines in a graph which shows layout connectivity. For the connectivity graph
 *		to be valid, all connections between nodes must be via TrackSegments.
 * <P>
 * TrackSegments carry Block information, as do LayoutTurnouts and LevelXings.
 * <P>
 * TrackSegments may be drawn as dashed lines or solid lines.  In addition TrackSegments
 *		may be hidden when the panel is not in EditMode.
 *
 * @author Dave Duchamp Copyright (c) 2004-2009
 * @version $Revision: 20715 $
 */

///*public*/ class TrackSegment
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/*public*/
TrackSegment::TrackSegment(QString id, LayoutTrack *c1, int t1, LayoutTrack *c2, int t2, bool dash, bool main, LayoutEditor* myPanel)
 : LayoutTrack(id, QPointF(), myPanel)
{
 init(id);
 layoutEditor = myPanel;
 // validate input
 if ( (c1==NULL) || (c2==NULL) )
 {
  log->error("Invalid object in TrackSegment constructor call - "+id);
 }
 connect1 = c1;
 connect2 = c2;
 if ( (t1 < LayoutEditor::POS_POINT)
  || ( ((t1 > LayoutEditor::LEVEL_XING_D) && (t1 < LayoutEditor::SLIP_A))
  || ((t1 > LayoutEditor::SLIP_D) && (t1 < LayoutEditor::TURNTABLE_RAY_OFFSET))))
 {
  log->error("Invalid connect type 1 in TrackSegment constructor - "+id);
 }
 else
 {
  type1 = t1;
 }
 if ( (t2<LayoutEditor::POS_POINT) ||
             ( ((t2>LayoutEditor::LEVEL_XING_D) && (t2<LayoutEditor::SLIP_A))
                 || ((t2>LayoutEditor::SLIP_D) && (t2<LayoutEditor::TURNTABLE_RAY_OFFSET)) ) )
 {
  log->error("Invalid connect type 2 in TrackSegment constructor - "+id);
 }
 else
 {
  type2 = t2;
 }
// instance = this;
// ident = id;
 dashed = dash;
 mainline = main;
 arc = false;
 flip = false;
 angle = 0.0;
 circle = false;
 bezier = false;
 setupDefaultBumperSizes(layoutEditor);
}

// alternate constructor for loading layout editor panels
/*public*/
TrackSegment::TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor* myPanel)
 : LayoutTrack(id, QPointF(), myPanel)
{
 init(id);
 layoutEditor = myPanel;
 tConnect1Name = c1Name;
 type1 = t1;
 tConnect2Name = c2Name;
 type2 = t2;
 //instance = this;
 //ident = id;
 dashed = dash;
 mainline = main;
 hidden = hide;
 setupDefaultBumperSizes(layoutEditor);
}

void TrackSegment::init(QString id)
{
// operational instance variables (not saved between sessions)
 setObjectName("TS_"+id);

 block = NULL;
 //instance = NULL;
 layoutEditor = NULL;
 item = nullptr;
 circleItem = NULL;
 trackOval = NULL;
 showConstructionLine = SHOWCON;
 bridgeColor = QColor(Qt::black);
 arrowColor = QColor(Qt::black);


// persistent instances variables (saved between sessions)
 //QString ident = "";
 blockName = "";
 connect1 = NULL;
 type1 = 0;
 connect2 = NULL;
 type2 = 0;
 dashed = false;
 mainline = false;
 hidden = false;
 arc = false;
 flip = false;
 angle =0.0;
 circle=false;
 changed=false;
 active = true;

 needsRedraw = false;
 bumperColor = QColor(Qt::black);
 tunnelColor = QColor(Qt::black);

 bezierControlPoints = QList<QPointF>(); // list of control point displacements
 mainlineCheckBoxMenuItem = new QAction(tr("MainlineCheckBoxMenuItemTitle"));
 mainlineCheckBoxMenuItem->setCheckable(true);
 hiddenCheckBoxMenuItem = new QAction(tr("HiddenCheckBoxMenuItemTitle"));
 hiddenCheckBoxMenuItem->setCheckable(true);
 dashedCheckBoxMenuItem = new QAction(tr("DashedCheckBoxMenuItemTitle"));
 dashedCheckBoxMenuItem->setCheckable(true);
 flippedCheckBoxMenuItem = new QAction(tr("FlippedCheckBoxMenuItemTitle"));
 flippedCheckBoxMenuItem->setCheckable(true);
}
/**
 * Accessor methods
*/
/*public*/ QString TrackSegment::getID()
{
 return ident;
}

/*public*/ QString TrackSegment::getBlockName() {
    return blockName;
}

/*public*/ int TrackSegment::getType1() {
    return type1;
}

/*public*/ int TrackSegment::getType2() {
    return type2;
}

/*public*/ LayoutTrack *TrackSegment::getConnect1() {
    return connect1;
}

/*public*/ LayoutTrack* TrackSegment::getConnect2() {
    return connect2;
}

/*protected*/ void TrackSegment::setNewConnect1(LayoutTrack* o, int type) {
    connect1 = o;
    type1 = type;

}

/*protected*/ void TrackSegment::setNewConnect2(LayoutTrack *o, int type) {
    connect2 = o;
    type2 = type;
}

/*public*/ bool TrackSegment::getDashed()
{
 return dashed;
}

/**
 * @return true if track segment should be drawn dashed
 */
/*public*/ bool TrackSegment::isDashed() {
    return dashed;
}

/*public*/ void TrackSegment::setDashed(bool dash) {
    dashed = dash;
}

/*public*/ bool TrackSegment::getHidden() {
    return hidden;
}

/*public*/ void TrackSegment::setHidden(bool hide) {
    hidden = hide;
}

/*public*/ bool TrackSegment::getMainline() {
    return mainline;
}

/*public*/ void TrackSegment::setMainline(bool main) {
    mainline = main;
}

/**
 * @return true if track segment is an arc
 */
/*public*/ bool TrackSegment::isArc() {
    return arc;
}

/*public*/ void TrackSegment::setArc(bool boo) {
    arc = boo;
    changed=true;
}

/*public*/ bool TrackSegment::getCircle() {return circle;}


/**
 * @return true if track segment is circle
 */
/*public*/ bool TrackSegment::isCircle() {
    return circle;
}

/*public*/ void
TrackSegment::setCircle(bool boo) {
    circle = boo;
    changed=true;
}
/*public*/ bool TrackSegment::getFlip() {return flip;}
/**
 * @return true if track segment circle or arc should be drawn flipped
 */
/*public*/ bool TrackSegment::isFlip() {
    return flip;
}
/*public*/ void TrackSegment::setFlip(bool boo) {
    flip = boo;
    changed=true;
}
///*public*/ int getStartAngle() {return startangle;}
///*public*/ void setStartAngle(int x) {startangle = x;}

/**
 * @return true if track segment is a bezier curve
 * @deprecated since 4.9.4; use {@link #isBezier()} instead
 */
//@Deprecated // Java standard pattern for boolean getters is "isBezier()"
/*public*/ bool TrackSegment::getBezier() {
    return bezier;
}

/**
 * @return true if track segment is a bezier curve
 */
/*public*/ bool TrackSegment::isBezier() {
    return bezier;
}

/*public*/ void TrackSegment::setBezier(bool boo) {
    if (bezier != boo) {
        bezier = boo;
        if (bezier) {
            arc = false;
            circle = false;
            hideConstructionLines(SHOWCON);
        }
        changed = true;
    }
}

/*public*/ double TrackSegment::getAngle() {return angle;}
/*public*/ void
TrackSegment::setAngle(double x)
{
// GT 8-OCT-2009 ==== Changed arcs maths : Start
//        if (angle>180) // ???
 if (x>180.0)
  x=180.0;
 else if (x < 0.0)
  x = 0.0;
// GT 8-OCT-2009 ==== Changed arcs maths : End
  angle = x;
  changed=true;
}
/**
 * get the direction from end point 1 to 2
 * <p>
 * Note: Goes CW from east (0) to south (PI/2) to west (PI) to north
 * (PI*3/2), etc.
 *
 * @return the direction (in radians)
 */
/*public*/ double TrackSegment::getDirectionRAD() {
    QPointF ep1 = center, ep2 = center;
    if (connect1 != nullptr) {
        ep1 = LayoutEditor::getCoords(connect1, getType1());
    }
    if (connect2 != nullptr) {
        ep2 = LayoutEditor::getCoords(connect2, getType2());
    }
    return (M_PI_2) - MathUtil::computeAngleRAD(ep1, ep2);
}

/**
 * get the direction from end point 1 to 2
 * <p>
 * Note: Goes CW from east (0) to south (90) to west (180) to north (270),
 * etc.
 *
 * @return the direction (in degrees)
 */
/*public*/ double TrackSegment::getDirectionDEG() {
    return qRadiansToDegrees(getDirectionRAD());
}

//This method is used to determine if we need to redraw a curved piece of track
//It saves having to recalculate the circle details each time.
/*public*/ bool TrackSegment::trackNeedsRedraw() { return changed; }

/*public*/ void TrackSegment::trackRedrawn() { changed = false; }
///*public*/ int getRadius() {return radius;}
///*public*/ void setRadius(int x) {radius = x;}

/*public*/ LayoutBlock*
TrackSegment::getLayoutBlock()
{
 if ( (block==nullptr) && (blockName!="") && (blockName!="") )
 {
  block = layoutEditor->provideLayoutBlock(blockName);
 }
 return block;
}

/*public*/ QString TrackSegment::getConnect1Name() {return getConnectName(connect1,type1);}
/*public*/ QString TrackSegment::getConnect2Name() {return getConnectName(connect2,type2);}

/*private*/ QString TrackSegment::getConnectName(/*@Nullable*/ LayoutTrack* layoutTrack, int type) {
    return (layoutTrack == nullptr) ? nullptr : layoutTrack->getName();
}

/**
 * {@inheritDoc}
 * <p>
 * This implementation returns null because {@link #getConnect1} and
 * {@link #getConnect2} should be used instead.
 */
// only implemented here to suppress "does not override abstract method " error in compiler
//@Override
/*public*/ LayoutTrack* TrackSegment::getConnection(int connectionType) throw (JmriException) {
    // nothing to see here, move along
    return nullptr;
}

/**
 * {@inheritDoc}
 * <p>
 * This implementation does nothing because {@link #setNewConnect1} and
 * {@link #setNewConnect2} should be used instead.
 */
// only implemented here to suppress "does not override abstract method " error in compiler
//@Override
/*public*/ void TrackSegment::setConnection(int connectionType, /*@Nullable*/ LayoutTrack* o, int type) throw (JmriException) {
    // nothing to see here, move along
}

/*public*/ int TrackSegment::getNumberOfBezierControlPoints() {
    return bezierControlPoints.size();
}

/*public*/ QPointF TrackSegment::getBezierControlPoint(int index) {
    QPointF result = center;
    if (index < 0) {
        index += bezierControlPoints.size();
    }
    if ((index >= 0) && (index < bezierControlPoints.size())) {
        result = bezierControlPoints.at(index);
    }
    return result;
}

/*public*/ void TrackSegment::setBezierControlPoint(/*@Nullable*/ QPointF p, int index) {
    if (index < 0) {
        index += bezierControlPoints.size();
    }
    if ((index >= 0) && (index <= bezierControlPoints.size())) {
        if (index < bezierControlPoints.size()) {
            bezierControlPoints.insert(index, p);
        } else {
            bezierControlPoints.append(p);
        }
    }
}
// initialization instance variables (used when loading a LayoutEditor)
//	public String tBlockName = "";
//	public String tConnect1Name = "";
//	public String tConnect2Name = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void TrackSegment::setObjects(LayoutEditor* p)
{
 if (!tBlockName.isEmpty()) {
     block = p->getLayoutBlock(tBlockName);
     if (block != nullptr) {
         blockName = tBlockName;
         block->incrementUse();
     } else {
         log->error("bad blockname '" + tBlockName + "' in tracksegment " + getName());
     }
 }

 //NOTE: testing "type-less" connects
 // (read comments for findObjectByName in LayoutEditorFindItems.java)
 connect1 = p->getFinder()->findObjectByName(tConnect1Name);
 if (nullptr == connect1)
 { // findObjectByName failed... try findObjectByTypeAndName
     log->warn("Unknown connect1 object prefix: '" + tConnect1Name + "' of type " + QString::number(type1) + ".");
     connect1 = p->getFinder()->findObjectByTypeAndName(type1, tConnect1Name);
 }
 connect2 = p->getFinder()->findObjectByName(tConnect2Name);
 if (nullptr == connect2) { // findObjectByName failed; try findObjectByTypeAndName
     log->warn("Unknown connect2 object prefix: '" + tConnect2Name + "' of type " + QString::number(type2) + ".");
     connect2 = p->getFinder()->findObjectByTypeAndName(type2, tConnect2Name);
 }
}

/**
 * Set Up a Layout Block for a Track Segment
 */
/*public*/ void TrackSegment::setLayoutBlock (LayoutBlock* b) {
    block = b;
    if (b!=NULL) {
        blockName = b->getID();
    }
}
/*public*/ void TrackSegment::setLayoutBlockByName (QString name) {
    blockName = name;
}
/*protected*/ void TrackSegment::updateBlockInfo()
{
 if (block!=NULL)
  block->updatePaths();
 LayoutBlock* b1 = getBlock(connect1,type1);
 if ((b1!=NULL)&&(b1!=block))
  b1->updatePaths();
 LayoutBlock* b2 = getBlock(connect2,type2);
 if ((b2!=NULL)&&(b2!=block)&&(b2!=b1))
  b2->updatePaths();
 //if(getConnect1() instanceof PositionablePoint)
 if(qobject_cast<PositionablePoint*>(getConnect1())!= NULL)
  ((PositionablePoint*)getConnect1())->reCheckBlockBoundary();
 else
  //if(getConnect1() instanceof LayoutTurnout)
 if(qobject_cast<LayoutTurnout*>(getConnect1())!= NULL)
  ((LayoutTurnout*)getConnect1())->reCheckBlockBoundary();
 else
   //if(getConnect1() instanceof LevelXing)
 if(qobject_cast<LevelXing*>(getConnect1())!= NULL)
  ((LevelXing*)getConnect1())->reCheckBlockBoundary();
  else
    //if(getConnect1() instanceof LayoutSlip)
     if(qobject_cast<LayoutSlip*>(getConnect1()) !=NULL)
  ((LayoutSlip*)getConnect1())->reCheckBlockBoundary();

    //if(getConnect2() instanceof PositionablePoint)
 if(qobject_cast<PositionablePoint*>(getConnect2())!= NULL)
  ((PositionablePoint*)getConnect2())->reCheckBlockBoundary();
 else
    //if(getConnect2() instanceof LayoutTurnout)
 if(qobject_cast<LayoutTurnout*>(getConnect2())!= NULL)
  ((LayoutTurnout*)getConnect2())->reCheckBlockBoundary();
 else
    //if(getConnect2() instanceof LevelXing)
 if(qobject_cast<LevelXing*>(getConnect2())!= NULL)
  ((LevelXing*)getConnect2())->reCheckBlockBoundary();
 else
     //if(getConnect2() instanceof LayoutSlip)
 if(qobject_cast<LayoutSlip*>(getConnect2()) !=NULL)
  ((LayoutSlip*)getConnect2())->reCheckBlockBoundary();
}

/*private*/ LayoutBlock* TrackSegment::getBlock (QObject* connect, int type)
{
 if (connect==NULL)
  return NULL;
 if (type==LayoutEditor::POS_POINT)
 {
  PositionablePoint* p = (PositionablePoint*)connect;
  if (p->getConnect1()!=this)
  {
   if (p->getConnect1()!=NULL) return (p->getConnect1()->getLayoutBlock());
    else return NULL;
  }
  else
  {
   if (p->getConnect2()!=NULL) return (p->getConnect2()->getLayoutBlock());
   else return NULL;
  }
 }
 else
 {
  return (layoutEditor->getAffectedBlock(connect,type));
 }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::drawDecorations(EditScene* g2) {

    if (getName() == ("T9")) {
        log->debug("STOP");
    }

    // get end points and calculate start/stop angles (in radians)
    QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
    QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
    QPointF p1, p2, p3, p4, p5, p6, p7;
    QPointF p1P = ep1, p2P = ep2, p3P, p4P, p5P, p6P, p7P;
    double startAngleRAD, stopAngleRAD;
#if 1
    if (isArc()) {
        calculateTrackSegmentAngle();
        double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
        startAngleRAD = (M_PI_2) - qDegreesToRadians(startAngleDEG);
        stopAngleRAD = (M_PI_2) - qDegreesToRadians(startAngleDEG + extentAngleDEG);
        if (isFlip()) {
            startAngleRAD += M_PI;
            stopAngleRAD += M_PI;
        } else {
            double temp = startAngleRAD;
            startAngleRAD = stopAngleRAD;
            stopAngleRAD = temp;
        }
    } else if (isBezier()) {
        QPointF cp0 = bezierControlPoints.at(0);
        QPointF cpN = bezierControlPoints.at(bezierControlPoints.size() - 1);
        startAngleRAD = (M_PI_2) - MathUtil::computeAngleRAD(cp0, ep1);
        stopAngleRAD = (M_PI_2) - MathUtil::computeAngleRAD(ep2, cpN);
    } else {
        QPointF delta = MathUtil::subtract(ep2, ep1);
        startAngleRAD = (M_PI_2) - MathUtil::computeAngleRAD(delta);
        stopAngleRAD = startAngleRAD;
    }
#endif
    //
    // arrow decorations
    //
    if (arrowStyle > 0) {
//        g2.setStroke(new BasicStroke(arrowLineWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
//        g2.setColor(arrowColor);
     QPen stroke = QPen(arrowColor, 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);


        // draw the out arrows
        int offset = 1;
        if (arrowEndStart) {
            if (arrowDirIn) {
                offset = drawArrow(g2, ep1, M_PI + startAngleRAD, false, offset, stroke);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep1, M_PI + startAngleRAD, true, offset, stroke);
            }
        }
        offset = 1;
        if (arrowEndStop) {
            if (arrowDirIn) {
                offset = drawArrow(g2, ep2, stopAngleRAD, false, offset, stroke);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep2, stopAngleRAD, true, offset, stroke);
            }
        }
    }   // arrow decoration
#if 0
    //
    //  bridge decorations
    //
    if (bridgeSideLeft || bridgeSideRight) {
        float halfWidth = bridgeDeckWidth / 2.F;

        g2.setStroke(new BasicStroke(bridgeLineWidth,
                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
        g2.setColor(bridgeColor);

        if (isArc()) {
            calculateTrackSegmentAngle();
            Rectangle2D cRectangle2D = new Rectangle2D(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (bridgeSideLeft) {
                Rectangle2D cLeftRectangle2D = MathUtil::inset(cRectangle2D, -halfWidth);
                g2.draw(new Arc2D(
                        cLeftRectangle2D.getX(),
                        cLeftRectangle2D.getY(),
                        cLeftRectangle2D.getWidth(),
                        cLeftRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            if (bridgeSideRight) {
                Rectangle2D cLRightRectangle2D = MathUtil::inset(cRectangle2D, +halfWidth);
                g2.draw(new Arc2D(
                        cLRightRectangle2D.getX(),
                        cLRightRectangle2D.getY(),
                        cLRightRectangle2D.getWidth(),
                        cLRightRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            trackRedrawn();
        } else if (isBezier()) {
            int cnt = bezierControlPoints.size() + 2;
            QPointF[] points = new QPointF[cnt];
            points[0] = ep1;
            for (int idx = 0; idx < cnt - 2; idx++) {
                points[idx + 1] = bezierControlPoints.get(idx);
            }
            points[cnt - 1] = ep2;

            if (bridgeSideLeft) {
                MathUtil::drawBezier(g2, points, -halfWidth);
            }
            if (bridgeSideRight) {
                MathUtil::drawBezier(g2, points, +halfWidth);
            }
        } else {
            QPointF delta = MathUtil::subtract(ep2, ep1);
            QPointF vector = MathUtil::normalize(delta, halfWidth);
            vector = MathUtil::orthogonal(vector);

            if (bridgeSideLeft) {
                QPointF ep1L = MathUtil::add(ep1, vector);
                QPointF ep2L = MathUtil::add(ep2, vector);
                g2.draw(new Line2D(ep1L, ep2L));
            }
            if (bridgeSideRight) {
                QPointF ep1R = MathUtil::subtract(ep1, vector);
                QPointF ep2R = MathUtil::subtract(ep2, vector);
                g2.draw(new Line2D(ep1R, ep2R));
            }
        }   // if isArc() {} else if isBezier() {} else...

        if (bridgeHasEntry) {
            if (bridgeSideRight) {
                p1 = new QPointF(-bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = new QPointF(0.0, -halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                g2.draw(new Line2D(p1P, p2P));
            }
            if (bridgeSideLeft) {
                p1 = new QPointF(-bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = new QPointF(0.0, +halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                g2.draw(new Line2D(p1P, p2P));
            }
        }
        if (bridgeHasExit) {
            if (bridgeSideRight) {
                p1 = new QPointF(+bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = new QPointF(0.0, -halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                g2.draw(new Line2D(p1P, p2P));
            }
            if (bridgeSideLeft) {
                p1 = new QPointF(+bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = new QPointF(0.0, +halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                g2.draw(new Line2D(p1P, p2P));
            }
        }
    }   // if (bridgeValue != null)
#endif
#if 1
    //
    //  end bumper decorations
    //
    if (bumperEndStart || bumperEndStop) {
        if (getName() == ("T15")) {
            log->debug("STOP");
        }
//        g2.setStroke(new BasicStroke(bumperLineWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
//        g2.setColor(bumperColor);
        QPen stroke = QPen(bumperColor, bumperLineWidth);

        float halfLength = bumperLength / 2.F;

        if (bumperFlipped) {
            double temp = startAngleRAD;
            startAngleRAD = stopAngleRAD;
            stopAngleRAD = temp;
        }

        // common points
        p1 = QPointF(0.0, -halfLength);
        p2 = QPointF(0.0, +halfLength);

        if (bumperEndStart) {
            p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
            p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
        }
        if (bumperEndStop) {
            p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
            p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
        }
        // draw cross tie
        //g2.draw(new Line2D(p1P, p2P));
        QGraphicsLineItem* line = new QGraphicsLineItem(p1P.x(), p1P.y(), p2P.x(), p2P.y());
        line->setPen(stroke);
        item = line;
        g2->addItem(item);
    }   // if (bumperEndStart || bumperEndStop)
#endif
#if 0
    //
    //  tunnel decorations
    //
    if (tunnelSideRight || tunnelSideLeft) {
        float halfWidth = tunnelFloorWidth / 2.F;
        g2.setStroke(new BasicStroke(tunnelLineWidth,
                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
                new float[]{6.F, 4.F}, 0));
        g2.setColor(tunnelColor);

        if (isArc()) {
            calculateTrackSegmentAngle();
            Rectangle2D cRectangle2D = new Rectangle2D(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (tunnelSideRight) {
                Rectangle2D cLeftRectangle2D = MathUtil::inset(cRectangle2D, -halfWidth);
                g2.draw(new Arc2D(
                        cLeftRectangle2D.getX(),
                        cLeftRectangle2D.getY(),
                        cLeftRectangle2D.getWidth(),
                        cLeftRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            if (tunnelSideLeft) {
                Rectangle2D cLRightRectangle2D = MathUtil::inset(cRectangle2D, +halfWidth);
                g2.draw(new Arc2D(
                        cLRightRectangle2D.getX(),
                        cLRightRectangle2D.getY(),
                        cLRightRectangle2D.getWidth(),
                        cLRightRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            trackRedrawn();
        } else if (isBezier()) {
            int cnt = bezierControlPoints.size() + 2;
            QPointF[] points = new QPointF[cnt];
            points[0] = ep1;
            for (int idx = 0; idx < cnt - 2; idx++) {
                points[idx + 1] = bezierControlPoints.get(idx);
            }
            points[cnt - 1] = ep2;

            if (tunnelSideRight) {
                MathUtil::drawBezier(g2, points, -halfWidth);
            }
            if (tunnelSideLeft) {
                MathUtil::drawBezier(g2, points, +halfWidth);
            }
        } else {
            QPointF delta = MathUtil::subtract(ep2, ep1);
            QPointF vector = MathUtil::normalize(delta, halfWidth);
            vector = MathUtil::orthogonal(vector);

            if (tunnelSideRight) {
                QPointF ep1L = MathUtil::add(ep1, vector);
                QPointF ep2L = MathUtil::add(ep2, vector);
                g2.draw(new Line2D(ep1L, ep2L));
            }
            if (tunnelSideLeft) {
                QPointF ep1R = MathUtil::subtract(ep1, vector);
                QPointF ep2R = MathUtil::subtract(ep2, vector);
                g2.draw(new Line2D(ep1R, ep2R));
            }
        }   // if isArc() {} else if isBezier() {} else...

        g2.setStroke(new BasicStroke(tunnelLineWidth,
                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
        g2.setColor(tunnelColor);

        double halfEntranceWidth = tunnelEntranceWidth / 2.0;
        double halfFloorWidth = tunnelFloorWidth / 2.0;
        double halfDiffWidth = halfEntranceWidth - halfFloorWidth;

        if (tunnelHasEntry) {
            if (tunnelSideLeft) {
                p1 = new QPointF(0.0, 0.0);
                p2 = new QPointF(0.0, -halfFloorWidth);
                p3 = new QPointF(0.0, -halfEntranceWidth);
                p4 = new QPointF(-halfEntranceWidth - halfFloorWidth, -halfEntranceWidth);
                p5 = new QPointF(-halfEntranceWidth - halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = new QPointF(-halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = new QPointF(-halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, startAngleRAD), ep1);

                GeneralPath path = new GeneralPath();
                path.moveTo(p1P.getX(), p1P.getY());
                path.lineTo(p2P.getX(), p2P.getY());
                path.quadTo(p3P.getX(), p3P.getY(), p4P.getX(), p4P.getY());
                path.lineTo(p5P.getX(), p5P.getY());
                path.quadTo(p6P.getX(), p6P.getY(), p7P.getX(), p7P.getY());
                path.closePath();
                g2.fill(path);
            }
            if (tunnelSideRight) {
                p1 = new QPointF(0.0, 0.0);
                p2 = new QPointF(0.0, +halfFloorWidth);
                p3 = new QPointF(0.0, +halfEntranceWidth);
                p4 = new QPointF(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth);
                p5 = new QPointF(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = new QPointF(-halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = new QPointF(-halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, startAngleRAD), ep1);

                GeneralPath path = new GeneralPath();
                path.moveTo(p1P.getX(), p1P.getY());
                path.lineTo(p2P.getX(), p2P.getY());
                path.quadTo(p3P.getX(), p3P.getY(), p4P.getX(), p4P.getY());
                path.lineTo(p5P.getX(), p5P.getY());
                path.quadTo(p6P.getX(), p6P.getY(), p7P.getX(), p7P.getY());
                path.closePath();
                g2.fill(path);
            }
        }
        if (tunnelHasExit) {
            if (tunnelSideLeft) {
                p1 = new QPointF(0.0, 0.0);
                p2 = new QPointF(0.0, -halfFloorWidth);
                p3 = new QPointF(0.0, -halfEntranceWidth);
                p4 = new QPointF(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth);
                p5 = new QPointF(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = new QPointF(halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = new QPointF(halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, stopAngleRAD), ep2);

                GeneralPath path = new GeneralPath();
                path.moveTo(p1P.getX(), p1P.getY());
                path.lineTo(p2P.getX(), p2P.getY());
                path.quadTo(p3P.getX(), p3P.getY(), p4P.getX(), p4P.getY());
                path.lineTo(p5P.getX(), p5P.getY());
                path.quadTo(p6P.getX(), p6P.getY(), p7P.getX(), p7P.getY());
                path.closePath();
                g2.fill(path);
            }
            if (tunnelSideRight) {
                p1 = new QPointF(0.0, 0.0);
                p2 = new QPointF(0.0, +halfFloorWidth);
                p3 = new QPointF(0.0, +halfEntranceWidth);
                p4 = new QPointF(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth);
                p5 = new QPointF(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = new QPointF(halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = new QPointF(halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, stopAngleRAD), ep2);

                GeneralPath path = new GeneralPath();
                path.moveTo(p1P.getX(), p1P.getY());
                path.lineTo(p2P.getX(), p2P.getY());
                path.quadTo(p3P.getX(), p3P.getY(), p4P.getX(), p4P.getY());
                path.lineTo(p5P.getX(), p5P.getY());
                path.quadTo(p6P.getX(), p6P.getY(), p7P.getX(), p7P.getY());
                path.closePath();
                g2.fill(path);
            }
        }
    }   // if (tunnelValue != null)
#endif
}   // drawDecorationso
#if 1
/*private*/ int TrackSegment::drawArrow(
        EditScene* g2,
        QPointF ep,
        double angleRAD,
        bool dirOut,
        int offset, QPen stroke)
{
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 QGraphicsLineItem* lineItem;
    QPointF p1, p2, p3, p4, p5, p6;
    switch (arrowStyle) {
        default: {
            arrowStyle = 0;
            break;
        }
        case 0: {
            break;
        }
        case 1: {
            if (dirOut) {
                p1 =  QPointF(offset, -arrowLength);
                p2 =  QPointF(offset + arrowLength, 0.0);
                p3 =  QPointF(offset, +arrowLength);
            } else {
                p1 =  QPointF(offset + arrowLength, -arrowLength);
                p2 =  QPointF(offset, 0.0);
                p3 =  QPointF(offset + arrowLength, +arrowLength);
            }
            p1 = MathUtil::add(MathUtil::rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil::add(MathUtil::rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil::add(MathUtil::rotateRAD(p3, angleRAD), ep);

            //g2.draw(new Line2D(p1, p2));
            lineItem = new QGraphicsLineItem(p1.x(), p1.y(), p2.x(), p2.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p2, p3));
            lineItem = new QGraphicsLineItem(p2.x(), p2.y(), p3.x(), p3.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);

            offset += arrowLength + arrowGap;
            break;
        }
        case 2: {
            if (dirOut) {
                p1 =  QPointF(offset, -arrowLength);
                p2 =  QPointF(offset + arrowLength, 0.0);
                p3 =  QPointF(offset, +arrowLength);
                p4 =  QPointF(offset + arrowLineWidth + arrowGap, -arrowLength);
                p5 =  QPointF(offset + arrowLineWidth + arrowGap + arrowLength, 0.0);
                p6 =  QPointF(offset + arrowLineWidth + arrowGap, +arrowLength);
            } else {
                p1 =  QPointF(offset + arrowLength, -arrowLength);
                p2 =  QPointF(offset, 0.0);
                p3 =  QPointF(offset + arrowLength, +arrowLength);
                p4 =  QPointF(offset + arrowLineWidth + arrowGap + arrowLength, -arrowLength);
                p5 =  QPointF(offset + arrowLineWidth + arrowGap, 0.0);
                p6 =  QPointF(offset + arrowLineWidth + arrowGap + arrowLength, +arrowLength);
            }
            p1 = MathUtil::add(MathUtil::rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil::add(MathUtil::rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil::add(MathUtil::rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil::add(MathUtil::rotateRAD(p4, angleRAD), ep);
            p5 = MathUtil::add(MathUtil::rotateRAD(p5, angleRAD), ep);
            p6 = MathUtil::add(MathUtil::rotateRAD(p6, angleRAD), ep);

            //g2.draw(new Line2D(p1, p2));
            lineItem = new QGraphicsLineItem(p1.x(), p1.y(), p2.x(), p2.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p2, p3));
            lineItem = new QGraphicsLineItem(p2.x(), p2.y(), p3.x(), p3.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p4, p5));
            lineItem = new QGraphicsLineItem(p4.x(), p4.y(), p5.x(), p5.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p5, p6));
            lineItem = new QGraphicsLineItem(p5.x(), p5.y(), p6.x(), p6.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            offset += arrowLength + (2 * (arrowLineWidth + arrowGap));
            break;
        }
        case 3: {
            if (dirOut) {
                p1 =  QPointF(offset, -arrowLength);
                p2 =  QPointF(offset + arrowLength, 0.0);
                p3 =  QPointF(offset, +arrowLength);
            } else {
                p1 =  QPointF(offset + arrowLength, -arrowLength);
                p2 =  QPointF(offset, 0.0);
                p3 =  QPointF(offset + arrowLength, +arrowLength);
            }
            p1 = MathUtil::add(MathUtil::rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil::add(MathUtil::rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil::add(MathUtil::rotateRAD(p3, angleRAD), ep);

            QPainterPath path = QPainterPath();
            path.moveTo(p1.x(), p1.y());
            path.lineTo(p2.x(), p2.y());
            path.lineTo(p3.x(), p3.y());
            path.closeSubpath();

//            if (arrowLineWidth > 1) {
//                g2.fill(path);
//            } else {
                //g2.draw(path);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(stroke);
             itemGroup->addToGroup(pathItem);
//            }

            offset += arrowLength + arrowGap;
            break;
        }
        case 4: {
            if (dirOut) {
                p1 =  QPointF(offset, 0.0);
                p2 =  QPointF(offset + (2 * arrowLength), -arrowLength);
                p3 =  QPointF(offset + (3 * arrowLength), 0.0);
                p4 =  QPointF(offset + (2 * arrowLength), +arrowLength);
            } else {
                p1 =  QPointF(offset + (3 * arrowLength), 0.0);
                p2 =  QPointF(offset, -arrowLength);
                p3 =  QPointF(offset + arrowLength, 0.0);
                p4 =  QPointF(offset, +arrowLength);
            }
            p1 = MathUtil::add(MathUtil::rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil::add(MathUtil::rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil::add(MathUtil::rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil::add(MathUtil::rotateRAD(p4, angleRAD), ep);

            //g2.draw(new Line2D(p1, p3));
            lineItem = new QGraphicsLineItem(p1.x(), p1.y(), p3.x(), p3.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p2, p3));
            lineItem = new QGraphicsLineItem(p2.x(), p2.y(), p3.x(), p3.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            //g2.draw(new Line2D(p3, p4));
            lineItem = new QGraphicsLineItem(p3.x(), p3.y(), p4.x(), p4.y());
            lineItem->setPen(stroke);
            itemGroup->addToGroup(lineItem);
            offset += (3 * arrowLength) + arrowGap;
            break;
        }
        case 5: {
            if (dirOut) {
                p1 =  QPointF(offset, 0.0);
                p2 =  QPointF(offset + (2 * arrowLength), -arrowLength);
                p3 =  QPointF(offset + (3 * arrowLength), 0.0);
                p4 =  QPointF(offset + (2 * arrowLength), +arrowLength);
            } else {
                p1 =  QPointF(offset + (3 * arrowLength), 0.0);
                p2 =  QPointF(offset, -arrowLength);
                p3 =  QPointF(offset + arrowLength, 0.0);
                p4 =  QPointF(offset, +arrowLength);
            }
            p1 = MathUtil::add(MathUtil::rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil::add(MathUtil::rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil::add(MathUtil::rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil::add(MathUtil::rotateRAD(p4, angleRAD), ep);

            QPainterPath path = QPainterPath();
            path.moveTo(p4.x(), p4.y());
            path.lineTo(p2.x(), p2.y());
            path.lineTo(p3.x(), p3.y());
            path.closeSubpath();
//            if (arrowLineWidth > 1) {
//                g2.fill(path);
//            } else {
                //g2.draw(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(stroke);
                itemGroup->addToGroup(pathItem);
//            }
            //g2.draw(new Line2D(p1, p3));
                lineItem = new QGraphicsLineItem(p1.x(), p1.y(), p3.x(), p3.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);

            offset += (3 * arrowLength) + arrowGap;
            break;
        }
    }
     item = itemGroup;
     g2->addItem(item);

    return offset;
}   // drawArrow
#endif
/**
 * Display popup menu for information and editing
 */
/*protected*/ void TrackSegment::showPopUp(QGraphicsSceneMouseEvent* /*e*/)
{
#if 0
 if (popupMenu != null) {
     popupMenu.removeAll();
 } else {
     popupMenu = new JPopupMenu();
 }

 String info = Bundle.getMessage("TrackSegment");
 if (isArc()) {
     if (isCircle()) {
         info = info + " (" + Bundle.getMessage("Circle") + ")";
     } else {
         info = info + " (" + Bundle.getMessage("Ellipse") + ")";
     }
 } else if (isBezier()) {
     info = info + " (" + Bundle.getMessage("Bezier") + ")";
 } else {
     info = info + " (" + Bundle.getMessage("Line") + ")";
 }

 JMenuItem jmi = popupMenu.add(Bundle.getMessage("MakeLabel", info) + getName());
 jmi.setEnabled(false);

 if (blockName.isEmpty()) {
     jmi = popupMenu.add(Bundle.getMessage("NoBlock"));
 } else {
     jmi = popupMenu.add(Bundle.getMessage("MakeLabel", Bundle.getMessage("BeanNameBlock")) + getLayoutBlock().getDisplayName());
 }
 jmi.setEnabled(false);

 // if there are any track connections
 if ((connect1 != null) || (connect2 != null)) {
     JMenu connectionsMenu = new JMenu(Bundle.getMessage("Connections")); // there is no pane opening (which is what ... implies)
     if (connect1 != null) {
         connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "1") + connect1.getName()) {
             @Override
             public void actionPerformed(ActionEvent e) {
                 LayoutEditorFindItems lf = layoutEditor.getFinder();
                 LayoutTrack lt = lf.findObjectByName(connect1.getName());
                 // this shouldn't ever be null... however...
                 if (lt != null) {
                     layoutEditor.setSelectionRect(lt.getBounds());
                     lt.showPopup();
                 }
             }
         });
     }
     if (connect2 != null) {
         connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "2") + connect2.getName()) {
             @Override
             public void actionPerformed(ActionEvent e) {
                 LayoutEditorFindItems lf = layoutEditor.getFinder();
                 LayoutTrack lt = lf.findObjectByName(connect2.getName());
                 // this shouldn't ever be null... however...
                 if (lt != null) {
                     layoutEditor.setSelectionRect(lt.getBounds());
                     lt.showPopup();
                 }
             }
         });
     }
     popupMenu.add(connectionsMenu);
 }

 popupMenu.add(new JSeparator(JSeparator.HORIZONTAL));

 popupMenu.add(mainlineCheckBoxMenuItem);
 mainlineCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
     setMainline(mainlineCheckBoxMenuItem.isSelected());
 });
 mainlineCheckBoxMenuItem.setToolTipText(Bundle.getMessage("MainlineCheckBoxMenuItemToolTip"));
 mainlineCheckBoxMenuItem.setSelected(mainline);

 popupMenu.add(hiddenCheckBoxMenuItem);
 hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
     setHidden(hiddenCheckBoxMenuItem.isSelected());
 });
 hiddenCheckBoxMenuItem.setToolTipText(Bundle.getMessage("HiddenCheckBoxMenuItemToolTip"));
 hiddenCheckBoxMenuItem.setSelected(hidden);

 popupMenu.add(dashedCheckBoxMenuItem);
 dashedCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
     setDashed(dashedCheckBoxMenuItem.isSelected());
 });
 dashedCheckBoxMenuItem.setToolTipText(Bundle.getMessage("DashedCheckBoxMenuItemToolTip"));
 dashedCheckBoxMenuItem.setSelected(dashed);

 if (isArc()) {
     popupMenu.add(flippedCheckBoxMenuItem);
     flippedCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
         setFlip(flippedCheckBoxMenuItem.isSelected());
     });
     flippedCheckBoxMenuItem.setToolTipText(Bundle.getMessage("FlippedCheckBoxMenuItemToolTip"));
     flippedCheckBoxMenuItem.setSelected(isFlip());
 }

 //
 // decorations menu
 //
 JMenu decorationsMenu = new JMenu(Bundle.getMessage("DecorationMenuTitle"));
 decorationsMenu.setToolTipText(Bundle.getMessage("DecorationMenuToolTip"));

 //
 // arrows menus
 //
 JMenu arrowsMenu = new JMenu(Bundle.getMessage("ArrowsMenuTitle"));
 decorationsMenu.setToolTipText(Bundle.getMessage("ArrowsMenuToolTip"));
 decorationsMenu.add(arrowsMenu);

 JMenu arrowsCountMenu = new JMenu(Bundle.getMessage("DecorationStyleMenuTitle"));
 arrowsCountMenu.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 arrowsMenu.add(arrowsCountMenu);

 JCheckBoxMenuItem jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(0);
 });
 jcbmi.setSelected(arrowStyle == 0);

 ImageIcon imageIcon = new ImageIcon(FileUtil.findURL("program:resources/icons/decorations/ArrowStyle1.png"));
 jcbmi = new JCheckBoxMenuItem(imageIcon);
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(1);
 });
 jcbmi.setSelected(arrowStyle == 1);

 imageIcon = new ImageIcon(FileUtil.findURL("program:resources/icons/decorations/ArrowStyle2.png"));
 jcbmi = new JCheckBoxMenuItem(imageIcon);
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(2);
 });
 jcbmi.setSelected(arrowStyle == 2);

 imageIcon = new ImageIcon(FileUtil.findURL("program:resources/icons/decorations/ArrowStyle3.png"));
 jcbmi = new JCheckBoxMenuItem(imageIcon);
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(3);
 });
 jcbmi.setSelected(arrowStyle == 3);

 imageIcon = new ImageIcon(FileUtil.findURL("program:resources/icons/decorations/ArrowStyle4.png"));
 jcbmi = new JCheckBoxMenuItem(imageIcon);
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(4);
 });
 jcbmi.setSelected(arrowStyle == 4);

 imageIcon = new ImageIcon(FileUtil.findURL("program:resources/icons/decorations/ArrowStyle5.png"));
 jcbmi = new JCheckBoxMenuItem(imageIcon);
 arrowsCountMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStyleMenuToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowStyle(5);
 });
 jcbmi.setSelected(arrowStyle == 5);

 JMenu arrowsEndMenu = new JMenu(Bundle.getMessage("DecorationEndMenuTitle"));
 arrowsEndMenu.setToolTipText(Bundle.getMessage("DecorationEndMenuToolTip"));
 arrowsMenu.add(arrowsEndMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 arrowsEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowEndStart(false);
     setArrowEndStop(false);
 });
 jcbmi.setSelected(!arrowEndStart && !arrowEndStop);

 jcbmi = new QAction(tr("DecorationStartMenuItemTitle"));
 arrowsEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStartMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowEndStart(true);
     setArrowEndStop(false);
 });
 jcbmi.setSelected(arrowEndStart && !arrowEndStop);

 jcbmi = new QAction(tr("DecorationEndMenuItemTitle"));
 arrowsEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationEndMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowEndStop(true);
     setArrowEndStart(false);
 });
 jcbmi.setSelected(!arrowEndStart && arrowEndStop);

 jcbmi = new QAction(tr("DecorationBothMenuItemTitle"));
 arrowsEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowEndStart(true);
     setArrowEndStop(true);
 });
 jcbmi.setSelected(arrowEndStart && arrowEndStop);

 JMenu arrowsDirMenu = new JMenu(Bundle.getMessage("ArrowsDirectionMenuTitle"));
 arrowsDirMenu.setToolTipText(Bundle.getMessage("ArrowsDirectionMenuToolTip"));
 arrowsMenu.add(arrowsDirMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 arrowsDirMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowDirIn(false);
     setArrowDirOut(false);
 });
 jcbmi.setSelected(!arrowDirIn && !arrowDirOut);

 jcbmi = new QAction(tr("ArrowsDirectionInMenuItemTitle"));
 arrowsDirMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("ArrowsDirectionInMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowDirIn(true);
     setArrowDirOut(false);
 });
 jcbmi.setSelected(arrowDirIn && !arrowDirOut);

 jcbmi = new QAction(tr("ArrowsDirectionOutMenuItemTitle"));
 arrowsDirMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("ArrowsDirectionOutMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowDirOut(true);
     setArrowDirIn(false);
 });
 jcbmi.setSelected(!arrowDirIn && arrowDirOut);

 jcbmi = new QAction(tr("ArrowsDirectionBothMenuItemTitle"));
 arrowsDirMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("ArrowsDirectionBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setArrowDirIn(true);
     setArrowDirOut(true);
 });
 jcbmi.setSelected(arrowDirIn && arrowDirOut);

 jmi = arrowsMenu.add(new JMenuItem(Bundle.getMessage("DecorationColorMenuItemTitle")));
 jmi.setToolTipText(Bundle.getMessage("DecorationColorMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     Color newColor = JmriColorChooser.showDialog(null, "Choose a color", arrowColor);
     if ((newColor != null) && !newColor.equals(arrowColor)) {
         setArrowColor(newColor);
     }
 });
 jmi.setForeground(arrowColor);
 jmi.setBackground(ColorUtil.contrast(arrowColor));

 jmi = arrowsMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLineWidthMenuItemTitle")) + arrowLineWidth));
 jmi.setToolTipText(Bundle.getMessage("DecorationLineWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for arrow line width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             arrowLineWidth);
     setArrowLineWidth(newValue);
 });

 jmi = arrowsMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLengthMenuItemTitle")) + arrowLength));
 jmi.setToolTipText(Bundle.getMessage("DecorationLengthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for arrow length
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLengthMenuItemTitle"),
             Bundle.getMessage("DecorationLengthMenuItemTitle"),
             arrowLength);
     setArrowLength(newValue);
 });

 jmi = arrowsMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationGapMenuItemTitle")) + arrowGap));
 jmi.setToolTipText(Bundle.getMessage("DecorationGapMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for arrow gap
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationGapMenuItemTitle"),
             Bundle.getMessage("DecorationGapMenuItemTitle"),
             arrowGap);
     setArrowGap(newValue);
 });

 //
 // bridge menus
 //
 JMenu bridgeMenu = new JMenu(Bundle.getMessage("BridgeMenuTitle"));
 decorationsMenu.setToolTipText(Bundle.getMessage("BridgeMenuToolTip"));
 decorationsMenu.add(bridgeMenu);

 JMenu bridgeSideMenu = new JMenu(Bundle.getMessage("DecorationSideMenuTitle"));
 bridgeSideMenu.setToolTipText(Bundle.getMessage("DecorationSideMenuToolTip"));
 bridgeMenu.add(bridgeSideMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 bridgeSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeSideLeft(false);
     setBridgeSideRight(false);
 });
 jcbmi.setSelected(!bridgeSideLeft && !bridgeSideRight);

 jcbmi = new QAction(tr("DecorationSideLeftMenuItemTitle"));
 bridgeSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationSideLeftMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeSideLeft(true);
     setBridgeSideRight(false);
 });
 jcbmi.setSelected(bridgeSideLeft && !bridgeSideRight);

 jcbmi = new QAction(tr("DecorationSideRightMenuItemTitle"));
 bridgeSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationSideRightMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeSideRight(true);
     setBridgeSideLeft(false);
 });
 jcbmi.setSelected(!bridgeSideLeft && bridgeSideRight);

 jcbmi = new QAction(tr("DecorationBothMenuItemTitle"));
 bridgeSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeSideLeft(true);
     setBridgeSideRight(true);
 });
 jcbmi.setSelected(bridgeSideLeft && bridgeSideRight);

 JMenu bridgeEndMenu = new JMenu(Bundle.getMessage("DecorationEndMenuTitle"));
 bridgeEndMenu.setToolTipText(Bundle.getMessage("DecorationEndMenuToolTip"));
 bridgeMenu.add(bridgeEndMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 bridgeEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeHasEntry(false);
     setBridgeHasExit(false);
 });
 jcbmi.setSelected(!bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("DecorationEntryMenuItemTitle"));
 bridgeEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationEntryMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeHasEntry(true);
     setBridgeHasExit(false);
 });
 jcbmi.setSelected(bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("DecorationExitMenuItemTitle"));
 bridgeEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationExitMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeHasExit(true);
     setBridgeHasEntry(false);
 });
 jcbmi.setSelected(!bridgeHasEntry && bridgeHasExit);

 jcbmi = new QAction(tr("DecorationBothMenuItemTitle"));
 bridgeEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBridgeHasEntry(true);
     setBridgeHasExit(true);
 });
 jcbmi.setSelected(bridgeHasEntry && bridgeHasExit);

 jmi = bridgeMenu.add(new JMenuItem(Bundle.getMessage("DecorationColorMenuItemTitle")));
 jmi.setToolTipText(Bundle.getMessage("DecorationColorMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     Color newColor = JmriColorChooser.showDialog(null, "Choose a color", bridgeColor);
     if ((newColor != null) && !newColor.equals(bridgeColor)) {
         setBridgeColor(newColor);
     }
 });
 jmi.setForeground(bridgeColor);
 jmi.setBackground(ColorUtil.contrast(bridgeColor));

 jmi = bridgeMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLineWidthMenuItemTitle")) + bridgeLineWidth));
 jmi.setToolTipText(Bundle.getMessage("DecorationLineWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for bridge line width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             bridgeLineWidth);
     setBridgeLineWidth(newValue);
 });

 jmi = bridgeMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("BridgeApproachWidthMenuItemTitle")) + bridgeApproachWidth));
 jmi.setToolTipText(Bundle.getMessage("BridgeApproachWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for bridge approach width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("BridgeApproachWidthMenuItemTitle"),
             Bundle.getMessage("BridgeApproachWidthMenuItemTitle"),
             bridgeApproachWidth);
     setBridgeApproachWidth(newValue);
 });

 jmi = bridgeMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("BridgeDeckWidthMenuItemTitle")) + bridgeDeckWidth));
 jmi.setToolTipText(Bundle.getMessage("BridgeDeckWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for bridge deck width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("BridgeDeckWidthMenuItemTitle"),
             Bundle.getMessage("BridgeDeckWidthMenuItemTitle"),
             bridgeDeckWidth);
     setBridgeDeckWidth(newValue);
 });

 //
 // end bumper menus
 //
 JMenu endBumperMenu = new JMenu(Bundle.getMessage("EndBumperMenuTitle"));
 decorationsMenu.setToolTipText(Bundle.getMessage("EndBumperMenuToolTip"));
 decorationsMenu.add(endBumperMenu);

 JMenu endBumperEndMenu = new JMenu(Bundle.getMessage("DecorationEndMenuTitle"));
 endBumperEndMenu.setToolTipText(Bundle.getMessage("DecorationEndMenuToolTip"));
 endBumperMenu.add(endBumperEndMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 endBumperEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBumperEndStart(false);
     setBumperEndStop(false);
 });
 jcbmi.setSelected(!bumperEndStart && !bumperEndStop);

 jcbmi = new QAction(tr("DecorationStartMenuItemTitle"));
 endBumperEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationStartMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBumperEndStart(true);
     setBumperEndStop(false);
 });
 jcbmi.setSelected(bumperEndStart && !bumperEndStop);

 jcbmi = new QAction(tr("DecorationEndMenuItemTitle"));
 endBumperEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationEndMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setBumperEndStop(true);
     setBumperEndStart(false);
 });
 jcbmi.setSelected(!bumperEndStart && bumperEndStop);

 jmi = endBumperMenu.add(new JMenuItem(Bundle.getMessage("DecorationColorMenuItemTitle")));
 jmi.setToolTipText(Bundle.getMessage("DecorationColorMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     Color newColor = JmriColorChooser.showDialog(null, "Choose a color", bumperColor);
     if ((newColor != null) && !newColor.equals(bumperColor)) {
         setBumperColor(newColor);
     }
 });
 jmi.setForeground(bumperColor);
 jmi.setBackground(ColorUtil.contrast(bumperColor));

 jmi = endBumperMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLineWidthMenuItemTitle")) + bumperLineWidth));
 jmi.setToolTipText(Bundle.getMessage("DecorationLineWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             bumperLineWidth);
     setBumperLineWidth(newValue);
 });

 jmi = endBumperMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLengthMenuItemTitle")) + bumperLength));
 jmi.setToolTipText(Bundle.getMessage("DecorationLengthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for length
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLengthMenuItemTitle"),
             Bundle.getMessage("DecorationLengthMenuItemTitle"),
             bumperLength);
     setBumperLength(newValue);
 });

 //
 // tunnel menus
 //
 JMenu tunnelMenu = new JMenu(Bundle.getMessage("TunnelMenuTitle"));
 decorationsMenu.setToolTipText(Bundle.getMessage("TunnelMenuToolTip"));
 decorationsMenu.add(tunnelMenu);

 JMenu tunnelSideMenu = new JMenu(Bundle.getMessage("DecorationSideMenuTitle"));
 tunnelSideMenu.setToolTipText(Bundle.getMessage("DecorationSideMenuToolTip"));
 tunnelMenu.add(tunnelSideMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 tunnelSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelSideLeft(false);
     setTunnelSideRight(false);
 });
 jcbmi.setSelected(!tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("DecorationSideLeftMenuItemTitle"));
 tunnelSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationSideLeftMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelSideLeft(true);
     setTunnelSideRight(false);
 });
 jcbmi.setSelected(tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("DecorationSideRightMenuItemTitle"));
 tunnelSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationSideRightMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelSideRight(true);
     setTunnelSideLeft(false);
 });
 jcbmi.setSelected(!tunnelSideLeft && tunnelSideRight);

 jcbmi = new QAction(tr("DecorationBothMenuItemTitle"));
 tunnelSideMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelSideLeft(true);
     setTunnelSideRight(true);
 });
 jcbmi.setSelected(tunnelSideLeft && tunnelSideRight);

 JMenu tunnelEndMenu = new JMenu(Bundle.getMessage("DecorationEndMenuTitle"));
 tunnelEndMenu.setToolTipText(Bundle.getMessage("DecorationEndMenuToolTip"));
 tunnelMenu.add(tunnelEndMenu);

 jcbmi = new QAction(tr("DecorationNoneMenuItemTitle"));
 tunnelEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationNoneMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelHasEntry(false);
     setTunnelHasExit(false);
 });
 jcbmi.setSelected(!tunnelHasEntry && !tunnelHasExit);

 jcbmi = new QAction(tr("DecorationEntryMenuItemTitle"));
 tunnelEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationEntryMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelHasEntry(true);
     setTunnelHasExit(false);
 });
 jcbmi.setSelected(tunnelHasEntry && !tunnelHasExit);

 jcbmi = new QAction(tr("DecorationExitMenuItemTitle"));
 tunnelEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationExitMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelHasExit(true);
     setTunnelHasEntry(false);
 });
 jcbmi.setSelected(!tunnelHasEntry && tunnelHasExit);

 jcbmi = new QAction(tr("DecorationBothMenuItemTitle"));
 tunnelEndMenu.add(jcbmi);
 jcbmi.setToolTipText(Bundle.getMessage("DecorationBothMenuItemToolTip"));
 jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     setTunnelHasEntry(true);
     setTunnelHasExit(true);
 });
 jcbmi.setSelected(tunnelHasEntry && tunnelHasExit);

 jmi = tunnelMenu.add(new JMenuItem(Bundle.getMessage("DecorationColorMenuItemTitle")));
 jmi.setToolTipText(Bundle.getMessage("DecorationColorMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     Color newColor = JmriColorChooser.showDialog(null, "Choose a color", tunnelColor);
     if ((newColor != null) && !newColor.equals(tunnelColor)) {
         setTunnelColor(newColor);
     }
 });
 jmi.setForeground(tunnelColor);
 jmi.setBackground(ColorUtil.contrast(tunnelColor));

 jmi = tunnelMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("TunnelFloorWidthMenuItemTitle")) + tunnelFloorWidth));
 jmi.setToolTipText(Bundle.getMessage("TunnelFloorWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for tunnel floor width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("TunnelFloorWidthMenuItemTitle"),
             Bundle.getMessage("TunnelFloorWidthMenuItemTitle"),
             tunnelFloorWidth);
     setTunnelFloorWidth(newValue);
 });

 jmi = tunnelMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("DecorationLineWidthMenuItemTitle")) + tunnelLineWidth));
 jmi.setToolTipText(Bundle.getMessage("DecorationLineWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for tunnel line width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             Bundle.getMessage("DecorationLineWidthMenuItemTitle"),
             tunnelLineWidth);
     setTunnelLineWidth(newValue);
 });

 jmi = tunnelMenu.add(new JMenuItem(Bundle.getMessage("MakeLabel",
         Bundle.getMessage("TunnelEntranceWidthMenuItemTitle")) + tunnelEntranceWidth));
 jmi.setToolTipText(Bundle.getMessage("TunnelEntranceWidthMenuItemToolTip"));
 jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
     //prompt for tunnel entrance width
     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
             Bundle.getMessage("TunnelEntranceWidthMenuItemTitle"),
             Bundle.getMessage("TunnelEntranceWidthMenuItemTitle"),
             tunnelEntranceWidth);
     setTunnelEntranceWidth(newValue);
 });

 popupMenu.add(decorationsMenu);

 popupMenu.add(new JSeparator(JSeparator.HORIZONTAL));
 popupMenu.add(new AbstractAction(Bundle.getMessage("ButtonEdit")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         layoutEditor.getLayoutTrackEditors().editTrackSegment(TrackSegment.this);
     }
 });
 popupMenu.add(new AbstractAction(Bundle.getMessage("ButtonDelete")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         layoutEditor.removeTrackSegment(TrackSegment.this);
         remove();
         dispose();
     }
 });
 popupMenu.add(new AbstractAction(Bundle.getMessage("SplitTrackSegment")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         splitTrackSegment();
     }
 });

 JMenu lineType = new JMenu(Bundle.getMessage("ChangeTo"));
 jmi = lineType.add(new JCheckBoxMenuItem(new AbstractAction(Bundle.getMessage("Line")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         changeType(0);
     }
 }));
 jmi.setSelected(!isArc() && !isBezier());

 jmi = lineType.add(new JCheckBoxMenuItem(new AbstractAction(Bundle.getMessage("Circle")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         changeType(1);
     }
 }));
 jmi.setSelected(isArc() && isCircle());

 jmi = lineType.add(new JCheckBoxMenuItem(new AbstractAction(Bundle.getMessage("Ellipse")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         changeType(2);
     }
 }));
 jmi.setSelected(isArc() && !isCircle());

 jmi = lineType.add(new JCheckBoxMenuItem(new AbstractAction(Bundle.getMessage("Bezier")) {
     @Override
     public void actionPerformed(ActionEvent e) {
         changeType(3);
     }
 }));
 jmi.setSelected(!isArc() && isBezier());

 popupMenu.add(lineType);

 if (isArc() || isBezier()) {
     if (hideConstructionLines()) {
         popupMenu.add(new AbstractAction(Bundle.getMessage("ShowConstruct")) {
             @Override
             public void actionPerformed(ActionEvent e) {
                 hideConstructionLines(SHOWCON);
             }
         });
     } else {
         popupMenu.add(new AbstractAction(Bundle.getMessage("HideConstruct")) {
             @Override
             public void actionPerformed(ActionEvent e) {
                 hideConstructionLines(HIDECON);
             }
         });
     }
 }
 if ((!blockName.isEmpty()) && (jmri.InstanceManager.getDefault(LayoutBlockManager.class).isAdvancedRoutingEnabled())) {
     popupMenu.add(new AbstractAction(Bundle.getMessage("ViewBlockRouting")) {
         @Override
         public void actionPerformed(ActionEvent e) {
             AbstractAction routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
             routeTableAction.actionPerformed(e);
         }
     });
 }
 popupMenu.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
 return popupMenu;
#endif
}   // showPopup

/**
* split track segment into two track segments with an anchor between
*/
/*public*/ void TrackSegment::splitTrackSegment() {
 // create a new anchor
 QPointF p = getCentreSeg();
 PositionablePoint* newAnchor = layoutEditor->addAnchor(p);
 // link it to me
 layoutEditor->setLink(newAnchor, POS_POINT, this, TRACK);

 //get unique name for a new track segment
 QString name = layoutEditor->getFinder()->uniqueName("T", 1);

 //create it between the new anchor and my connect2(/type2)
 TrackSegment* newTrackSegment = new TrackSegment(name,
         newAnchor, POS_POINT,
         connect2, type2,
         isDashed(), isMainline(), layoutEditor);
 // add it to known tracks
 layoutEditor->getLayoutTracks()->append(newTrackSegment);
 layoutEditor->setDirty();

 // copy attributes to new track segment
 newTrackSegment->setLayoutBlock(this->getLayoutBlock());
 newTrackSegment->setArc(this->isArc());
 newTrackSegment->setCircle(this->isCircle());
 //newTrackSegment.setBezier(this.isBezier());
 newTrackSegment->setFlip(this->isFlip());

 // link my connect2 to the new track segment
 if (qobject_cast< PositionablePoint*>(connect2)) {
     PositionablePoint* pp = (PositionablePoint*) connect2;
     pp->replaceTrackConnection(this, newTrackSegment);
 } else {
     layoutEditor->setLink(connect2, type2, newTrackSegment, TRACK);
 }

 // link the new anchor to the new track segment
 layoutEditor->setLink(newAnchor, POS_POINT, newTrackSegment, TRACK);

 // link me to the new newAnchor
 connect2 = newAnchor;
 type2 = POS_POINT;

 //check on layout block
 LayoutBlock* b = this->getLayoutBlock();

 if (b != nullptr) {
     newTrackSegment->setLayoutBlock(b);
     layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
     newTrackSegment->updateBlockInfo();
 }
 layoutEditor->setDirty();
 layoutEditor->redrawPanel();
}   // splitTrackSegment

/**
* Display popup menu for information and editing.
*/
/*protected*/ void TrackSegment::showBezierPopUp(QGraphicsSceneMouseEvent* e, int hitPointType) {
 int bezierControlPointIndex = hitPointType - BEZIER_CONTROL_POINT_OFFSET_MIN;
 if (popupMenu != nullptr) {
     popupMenu->clear();
 } else {
     popupMenu = new QMenu();
 }
#if 0
 JMenuItem jmi = popupMenu.add(Bundle.getMessage("BezierControlPoint") + " #" + bezierControlPointIndex);
 jmi.setEnabled(false);
 popupMenu.add(new JSeparator(JSeparator.HORIZONTAL));

 if (bezierControlPoints.size() < BEZIER_CONTROL_POINT_OFFSET_MAX - BEZIER_CONTROL_POINT_OFFSET_MIN) {
     popupMenu.add(new AbstractAction(Bundle.getMessage("AddBezierControlPointAfter")) {

         @Override
         public void actionPerformed(ActionEvent e) {
             addBezierControlPointAfter(bezierControlPointIndex);
         }
     });
     popupMenu.add(new AbstractAction(Bundle.getMessage("AddBezierControlPointBefore")) {

         @Override
         public void actionPerformed(ActionEvent e) {
             addBezierControlPointBefore(bezierControlPointIndex);
         }
     });
 }

 if (bezierControlPoints.size() > 2) {
     popupMenu.add(new AbstractAction(Bundle.getMessage("DeleteBezierControlPoint") + " #" + bezierControlPointIndex) {

         @Override
         public void actionPerformed(ActionEvent e) {
             deleteBezierControlPoint(bezierControlPointIndex);
         }
     });
 }
 popupMenu.show(e.getComponent(), e.getX(), e.getY());
#endif
}

/*private*/ void TrackSegment::addBezierControlPointBefore(int index) {
 QPointF addPoint = getBezierControlPoint(index);
 if (index > 0) {
     addPoint = MathUtil::midPoint(getBezierControlPoint(index - 1), addPoint);
 } else {
     QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
     addPoint = MathUtil::midPoint(ep1, addPoint);
 }
 bezierControlPoints.insert(index, addPoint);
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
}

/*private*/ void TrackSegment::addBezierControlPointAfter(int index) {
 int cnt = bezierControlPoints.size();
 QPointF addPoint = getBezierControlPoint(index);
 if (index < cnt - 1) {
     addPoint = MathUtil::midPoint(addPoint, getBezierControlPoint(index + 1));
     bezierControlPoints.insert(index + 1, addPoint);
 } else {
     QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
     addPoint = MathUtil::midPoint(addPoint, ep2);
     bezierControlPoints.append(addPoint);
 }
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
}

/*private*/ void TrackSegment::deleteBezierControlPoint(int index) {
 if ((index >= 0) && (index < bezierControlPoints.size())) {
     bezierControlPoints.removeAt(index);
     layoutEditor->redrawPanel();
     layoutEditor->setDirty();
 }
}

void TrackSegment::changeType(int choice) {
 switch (choice) {
     case 0: // plain track segment (line)
         setArc(false);
         setAngle(0.0);
         setCircle(false);
         setBezier(false);
         break;
     case 1: // circle
         setArc(true);
         setAngle(90.0);
         setCircle(true);
         setBezier(false);
         break;
     case 2: // arc
         setArc(true);
         setAngle(90.0);
         setCircle(false);
         setBezier(false);
         break;
     case 3:
         setArc(false);  // bezier
         setCircle(false);
         if (bezierControlPoints.size() == 0) {
             // set default control point displacements
             QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
             QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());

             // compute orthogonal offset0 with length one third the distance from ep1 to ep2
             QPointF offset = MathUtil::subtract(ep2, ep1);
             offset = MathUtil::normalize(offset, MathUtil::length(offset) / 3.0);
             offset = MathUtil::orthogonal(offset);

             // add orthogonal offset0 to 1/3rd and 2/3rd points
             QPointF pt1 = MathUtil::add(MathUtil::oneThirdPoint(ep1, ep2), offset);
             QPointF pt2 = MathUtil::subtract(MathUtil::twoThirdsPoint(ep1, ep2), offset);

             bezierControlPoints.append(pt1);
             bezierControlPoints.append(pt2);
         }
         setBezier(true);    // do this last (it calls reCenter())
         break;
     default:
         break;
 }
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
}


TSAbstractAction::TSAbstractAction(QString name, QObject *parent)
 : AbstractAction(name, parent) {}

/*public*/ void TSAbstractAction::actionPerformed(ActionEvent* /*e*/)
{
 AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", ((TrackSegment*)parent())->getLayoutBlock());
 routeTableAction->actionPerformed();
}

void TrackSegment::on_changeType(QAction *act)
{
 changeType(act->data().toInt());
}

void TrackSegment::on_actionRemove()
{
 layoutEditor->removeTrackSegment(this);
 remove();
 dispose();
}


void TrackSegment::flipAngle()
{
    if(getFlip()){
        setFlip(false);
    } else{
        setFlip(true);
    }
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}
#if 0 // now implemented in edittracksegmentdlg
    // variables for Edit Track Segment pane
 // NOTE: these are now implemented in EditTrackSegmentDlg.
    /*private*/ JmriJFrame editTrackSegmentFrame = NULL;
    /*private*/ JComboBox dashedBox = new JComboBox();
    /*private*/ int dashedIndex;
    /*private*/ int solidIndex;
    /*private*/ JComboBox mainlineBox = new JComboBox();
    /*private*/ int mainlineTrackIndex;
    /*private*/ int sideTrackIndex;
    /*private*/ JTextField blockNameField = new JTextField(16);
    /*private*/ JTextField arcField = new JTextField(5);
    /*private*/ JCheckBox hiddenBox = new JCheckBox(rb.getQString("HideTrack"));
    /*private*/ JButton segmentEditBlock;
    /*private*/ JButton segmentEditDone;
    /*private*/ JButton segmentEditCancel;
    /*private*/ bool editOpen = false;

    /**
     * Edit a Track Segment
     */
    protected void editTrackSegment() {
        if (editOpen) {
            editTrackSegmentFrame.setVisible(true);
            return;
        }
        // Initialize if needed
        if (editTrackSegmentFrame == NULL) {
            editTrackSegmentFrame = new JmriJFrame( rb.getQString("EditTrackSegment"), false, true );
            editTrackSegmentFrame.addHelpMenu("package.jmri.jmrit.display.EditTrackSegment", true);
            editTrackSegmentFrame.setLocation(50,30);
            Container contentPane = editTrackSegmentFrame.getContentPane();
            contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
            // add dashed choice
            JPanel panel31 = new JPanel();
            panel31.setLayout(new FlowLayout());
            dashedBox.removeAllItems();
            dashedBox.addItem( rb.getQString("Solid") );
            solidIndex = 0;
            dashedBox.addItem( rb.getQString("Dashed") );
            dashedIndex = 1;
            dashedBox.setToolTipText(rb.getQString("DashedToolTip"));
            panel31.add (new JLabel(rb.getQString("Style")+" : "));
            panel31.add (dashedBox);
            contentPane.add(panel31);
            // add mainline choice
            JPanel panel32 = new JPanel();
            panel32.setLayout(new FlowLayout());
            mainlineBox.removeAllItems();
            mainlineBox.addItem( rb.getQString("Mainline") );
            mainlineTrackIndex = 0;
            mainlineBox.addItem( rb.getQString("NotMainline") );
            sideTrackIndex = 1;
            mainlineBox.setToolTipText(rb.getQString("MainlineToolTip"));
            panel32.add (mainlineBox);
            contentPane.add(panel32);
            // add hidden choice
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
            if((getArc())&&(getCircle())){
                JPanel panel20 = new JPanel();
                panel20.setLayout(new FlowLayout());
                JLabel arcLabel = new JLabel( "Set Arc Angle");
                panel20.add(arcLabel);
                panel20.add(arcField);
                arcField.setToolTipText( "Set Arc Angle" );
                contentPane.add(panel20);
                arcField.setText(getAngle());
            }
            // set up Edit Block, Done and Cancel buttons
            JPanel panel5 = new JPanel();
            panel5.setLayout(new FlowLayout());
            // Edit Block
            panel5.add(segmentEditBlock = new JButton(rb.getQString("EditBlock")));
            segmentEditBlock.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditBlockPressed(e);
                }
            });
            segmentEditBlock.setToolTipText( rb.getQString("EditBlockHint") );
            panel5.add(segmentEditDone = new JButton(rb.getQString("Done")));
            segmentEditDone.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditDonePressed(e);
                }
            });
            segmentEditDone.setToolTipText( rb.getQString("DoneHint") );
            // Cancel
            panel5.add(segmentEditCancel = new JButton(rb.getQString("Cancel")));
            segmentEditCancel.addActionListener(new ActionListener() {
                /*public*/ void actionPerformed(ActionEvent e) {
                    segmentEditCancelPressed(e);
                }
            });
            segmentEditCancel.setToolTipText( rb.getQString("CancelHint") );
            contentPane.add(panel5);
        }
        // Set up for Edit
        if (mainline)
            mainlineBox.setSelectedIndex(mainlineTrackIndex);
        else
            mainlineBox.setSelectedIndex(sideTrackIndex);
        if (dashed)
            dashedBox.setSelectedIndex(dashedIndex);
        else
            dashedBox.setSelectedIndex(solidIndex);
        hiddenBox.setSelected(hidden);
        blockNameField.setText(blockName);
        editTrackSegmentFrame.addWindowListener(new java.awt.event.WindowAdapter() {
                /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
                    segmentEditCancelPressed(NULL);
                }
            });
        editTrackSegmentFrame.pack();
        editTrackSegmentFrame.setVisible(true);
        editOpen = true;
    }
    void segmentEditBlockPressed(ActionEvent a) {
        // check if a block name has been entered
        if (!blockName == (blockNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if (block!=NULL) {
                block.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockName = blockNameField.getText().trim();
            block = layoutEditor->provideLayoutBlock(blockName);
            if (block == NULL) {
                blockName = "";
            }
            needsRedraw = true;
            layoutEditor->auxTools.setBlockConnectivityChanged();
            updateBlockInfo();
        }
        // check if a block exists to edit
        if (block==NULL) {
            JOptionPane.showMessageDialog(editTrackSegmentFrame,
                    rb.getQString("Error1"),
                    rb.getQString("Error"),JOptionPane.ERROR_MESSAGE);
            return;
        }
        block.editLayoutBlock(editTrackSegmentFrame);
        layoutEditor->setDirty();
        needsRedraw = true;
    }
    void segmentEditDonePressed(ActionEvent a) {
        // set dashed
        bool oldDashed = dashed;
        if (dashedBox.getSelectedIndex() == dashedIndex) dashed = true;
        else dashed = false;
        // set mainline
        bool oldMainline = mainline;
        if (mainlineBox.getSelectedIndex() == mainlineTrackIndex) mainline = true;
        else mainline = false;
        // set hidden
        bool oldHidden = hidden;
        hidden = hiddenBox.isSelected();
        if(getArc()){
            //setAngle(Integer.parseInt(arcField.getText()));
            //needsRedraw = true;
            try {
                double newAngle = Double.parseDouble(arcField.getText());
                setAngle(newAngle);
                needsRedraw = true;
            }
            catch (NumberFormatException e) {
                arcField.setText(getAngle());
            }
        }
        // check if anything changed
        if ( (oldDashed!=dashed) || (oldMainline!=mainline) || (oldHidden!=hidden) )
            needsRedraw = true;
        // check if Block changed
        if ( !blockName == (blockNameField.getText().trim()) ) {
            // block has changed, if old block exists, decrement use
            if (block!=NULL) {
                block.decrementUse();
            }
            // get new block, or NULL if block has been removed
            blockName = blockNameField.getText().trim();
            block = layoutEditor->provideLayoutBlock(blockName);
            if (block == NULL) {
                blockName = "";
            }
            needsRedraw = true;
            layoutEditor->auxTools.setBlockConnectivityChanged();
            updateBlockInfo();
        }
        editOpen = false;
        editTrackSegmentFrame.setVisible(false);
        editTrackSegmentFrame.dispose();
        editTrackSegmentFrame = NULL;
        if (needsRedraw) layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
    void segmentEditCancelPressed(ActionEvent a) {
        editOpen = false;
        editTrackSegmentFrame.setVisible(false);
        editTrackSegmentFrame.dispose();
        editTrackSegmentFrame = NULL;
        if (needsRedraw) {
            layoutEditor->setDirty();
            layoutEditor->redrawPanel();
        }
    }
#endif
/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void TrackSegment::dispose() {
//        if (popup != NULL) popup.removeAll();
//        popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void TrackSegment::remove() {
    // remove from persistance by flagging inactive
    active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool TrackSegment::isActive() {
    return active;
}

/**
* The following are used only as a temporary store after a circle or arc has been calculated.
* This prevents the need to recalculate the values each time a re-draw is required.
*/

/*public*/ QPointF TrackSegment::getTmpPt1(){
    return pt1;
}
/*public*/ QPointF TrackSegment::getTmpPt2(){
    return pt2;
}

/*public*/ void TrackSegment::setTmpPt1(QPointF Pt1){
    pt1 = Pt1;
    changed= true;
}
/*public*/ void TrackSegment::setTmpPt2(QPointF Pt2){
    pt2 = Pt2;
    changed= true;
}

///*private*/ int startadj;

/*public*/ double TrackSegment::getCX(){
    return cX;
}

/*public*/ void TrackSegment::setCX(double CX){
    cX = CX;
}

/*public*/ double TrackSegment::getCY(){
    return cY;
}

/*public*/ void TrackSegment::setCY(double CY){
    cY = CY;
}

/*public*/ double TrackSegment::getCW(){
    return cW;
}

/*public*/ void TrackSegment::setCW(double CW){
    cW = CW;
}

/*public*/ double TrackSegment::getCH(){
    return cH;
}

/*public*/ void TrackSegment::setCH(double CH){
    cH = CH;
}

/*public*/ double TrackSegment::getStartAdj(){
    return startadj;
}

/*public*/ void TrackSegment::setStartAdj(double Startadj){
    startadj = Startadj;
}

/*public*/ double TrackSegment::getCentreSegX() {
    return centreSegX;
}

/*public*/ void TrackSegment::setCentreSegX(double CentreX) {
    centreSegX = CentreX;
}

/*public*/ double TrackSegment::getCentreSegY() {
    return centreSegY;
}

/*public*/ void TrackSegment::setCentreSegY(double CentreY) {
    centreSegY = CentreY;
}

/**
 * @return the location of the middle of the segment (on the segment)
 */
/*public*/ QPointF TrackSegment::getCentreSeg()
{
 QPointF result =MathUtil::zeroPoint2D;

 if ((connect1 != nullptr) && (connect2 != nullptr))
 {
  // get the end points
  QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
  QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());

  if (isCircle()) {
      result = center; //new QPointF(centreX, centreY);
  }
  else if (isArc())
  {
      //center = MathUtil::midPoint(getBounds());
   center = getBounds().center();
      if (isFlip()) {
          QPointF t = ep1;
          ep1 = ep2;
          ep2 = t;
      }
      QPointF delta = MathUtil::subtract(ep1, ep2);
      // are they of the same sign?
      if ((delta.x() >= 0.0) != (delta.y() >= 0.0)) {
          delta = MathUtil::divide(delta, +5.0, -5.0);
      } else {
          delta = MathUtil::divide(delta, -5.0, +5.0);
      }
      result =MathUtil::add(center, delta);
  }
#if 1
  else if (isBezier()) {
      // compute result Bezier point for (t == 0.5);
      // copy all the control points (including end points) into an array
      int len = bezierControlPoints.size() + 2;
      QVector<QPointF> points = QVector<QPointF>(len);
      points.replace(0, ep1);
      for (int idx = 1; idx < len - 1; idx++) {
          points.replace(idx, bezierControlPoints.at(idx - 1));
      }
      points.replace(len - 1, ep2);

      // calculate midpoints of all points (len - 1 order times)
      for (int idx = len - 1; idx > 0; idx--) {
          for (int jdx = 0; jdx < idx; jdx++) {
              points.replace(jdx,  MathUtil::midPoint(points[jdx], points[jdx + 1]));
          }
      }
      result = points[0];
  }
#endif
  else
  {
   result = MathUtil::midPoint(ep1, ep2);
  }
  center = result;
 }
 return result;
}

/*public*/ void TrackSegment::setCentreSeg(QPointF p) {
    center = p;
}

/*public*/ double TrackSegment::getCentreX(){
    return centreX;
}

/*public*/ void TrackSegment::setCentreX(double CentreX){
    centreX = CentreX;
}

/*public*/ double TrackSegment::getCentreY(){
    return centreY;
}

/*public*/ void TrackSegment::setCentreY(double CentreY){
    centreY = CentreY;
}

/*public*/ QPointF TrackSegment::getCentre()
{
 return QPointF(centreX, centreY);
}

/*public*/ double TrackSegment::getTmpAngle(){
    return tmpangle;
}

/*public*/ void TrackSegment::setTmpAngle(double TmpAngle){
    tmpangle = TmpAngle;
}

/*public*/ QPointF TrackSegment::getCoordsCenterCircle()
{
 return  getCentre();
}
/**
 * set center coordinates
 *
 * @param p the coordinates to set
 */
/*public*/ void TrackSegment::setCoordsCenterCircle(QPointF p) {
    centreX = p.x();
    centreY = p.y();
}

/*public*/ double TrackSegment::getChordLength() { return chordLength; }
/*public*/ void TrackSegment::setChordLength(double chord) { chordLength=chord;}

/*static*/ Logger* TrackSegment::log = LoggerFactory::getLogger("TrackSegment");

//}

void TrackSegment::on_actionEdit_triggered()
{
 EditTrackSegmentDlg* dlg = new EditTrackSegmentDlg(this, layoutEditor);
 dlg->show();
}
void TrackSegment::invalidate(QGraphicsScene *g2)
{
 if(item != NULL)
 {
  g2->removeItem(item);
 }
 if(trackOval != NULL)
 {
  g2->removeItem(trackOval);
  trackOval =NULL;
 }
 if(circleItem != NULL)
 {
  g2->removeItem(circleItem);
 circleItem = NULL;
 }

}
void TrackSegment::drawHiddenTrack(LayoutEditor* editor, QGraphicsScene *g2)
{
 QColor color;
 //if (isEditable() && getHidden())
 {
  LayoutBlock* b = getLayoutBlock();
  if (b!=NULL) color = (b->getBlockColor());
  else color =(editor->defaultTrackColor);
//   g2.setStroke(new BasicStroke(1.0F,BasicStroke.CAP_BUTT,BasicStroke.JOIN_ROUND));
//   g2.draw(new Line2D(getCoords(t->getConnect1(),t.getType1()), getCoords(t->getConnect2(),t.getType2())));
//   g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(color, trackWidth));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()), LayoutEditor::getCoords(getConnect2(),getType2())));
  lineItem->setPen(QPen(color, 1.0));
  item = lineItem;
  g2->addItem(item);
  editor->setTrackStrokeWidth(!editor->main);
 }
}
void TrackSegment::drawDashedTrack(LayoutEditor* editor, QGraphicsScene* g2, bool mainline)
{
 QColor color;
 LayoutBlock* b = getLayoutBlock();
 if (b!=NULL) color = (b->getBlockColor());
 else color = (editor->defaultTrackColor);
 editor->setTrackStrokeWidth(mainline);
 if (getArc())
 {
  calculateTrackSegmentAngle();
  //Stroke drawingStroke;
  //Stroke originalStroke = g2.getStroke();
  QPen drawingStroke;
  if (mainline)
   //drawingStroke = new BasicStroke(mainlineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
   drawingStroke = QPen(color,editor->mainlineTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);
  else
//    drawingStroke = new BasicStroke(sideTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
   drawingStroke =  QPen(color,editor->sidelineTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);

  //g2.setStroke(drawingStroke);
  //g2.draw(new Arc2D(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
  //g2->addEllipse(t->getCX(), t->getCY(), t->getCW(), t->getCH(),drawingStroke);
  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
  lineItem->setStartAngle(getStartAdj()*16);
  lineItem->setSpanAngle(getTmpAngle()*16);
  lineItem->setPen(drawingStroke);
  item = lineItem;
  g2->addItem(item);
  //g2.setStroke(originalStroke);
 }
 else
 {
  QPointF end1 = LayoutEditor::getCoords(getConnect1(),getType1());
  QPointF end2 = LayoutEditor::getCoords(getConnect2(),getType2());
  double delX = end1.x() - end2.x();
  double delY = end1.y() - end2.y();
  double cLength = qSqrt( (delX*delX) + (delY*delY) );
  // note: The preferred dimension of a dash (solid + blank space) is
  //         5 * the track width - about 60% solid and 40% blank.
  int nDashes = (int)( cLength / ((editor->trackWidth)*5.0) );
  if (nDashes < 3) nDashes = 3;
  double delXDash = -delX/( (nDashes) - 0.5 );
  double delYDash = -delY/( (nDashes) - 0.5 );
  double begX = end1.x();
  double begY = end1.y();
  QGraphicsItemGroup* group = new QGraphicsItemGroup();
  for (int k = 0; k<nDashes; k++)
  {
   //g2->addLine(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))),QPen(color,trackWidth));
   QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))));
   lineItem->setPen(QPen(color,editor->trackWidth));
   group->addToGroup(lineItem);
   begX += delXDash;
   begY += delYDash;
  }
  g2->addItem(group);
 }
}
/*
* Calculates the initial parameters for drawing a circular track segment.
*/
/*private*/ void TrackSegment::calculateTrackSegmentAngle()
{
  QPointF pt1 = LayoutEditor::getCoords(getConnect1(),getType1());
  QPointF pt2 = LayoutEditor::getCoords(getConnect2(),getType2());
  if (getFlip())
  {
   pt1 = LayoutEditor::getCoords(getConnect2(),getType2());
   pt2 = LayoutEditor::getCoords(getConnect1(),getType1());
  }
  if((getTmpPt1()!=pt1) || (getTmpPt2()!=pt2) || trackNeedsRedraw())
  {
   setTmpPt1(pt1);
   setTmpPt2(pt2);
   //setTrackStrokeWidth(g2,false);
   double pt2x;
   double pt2y;
   double pt1x;
   double pt1y;
   pt2x = pt2.x();
   pt2y = pt2.y();
   pt1x = pt1.x();
   pt1y = pt1.y();

   if (getAngle() == 0.0)
      setTmpAngle(90.0);
   else
      setTmpAngle(getAngle());
   //double toDegrees = M_PI/180.;
   // Convert angle to radians in order to speed up maths
   double halfAngle = degToRad(getTmpAngle())/2.0;
   double chord;
   double a;
   double o;
   double radius;
   // Compute arc's chord
   a = pt2x - pt1x;
   o = pt2y - pt1y;
   chord=qSqrt(((a*a)+(o*o)));
   setChordLength(chord);
   // Make sure chord is not NULL
   // In such a case (pt1 == pt2), there is no arc to draw
   if (chord > 0.0)
   {
    radius = (chord/2)/(qSin(halfAngle));
    // Circle
    double startRad = qAtan2(a, o) - halfAngle;
    setStartAdj(radToDeg(startRad));
    if(getCircle())
    {
     // Circle - Compute center
     setCentreX(pt2x - qCos(startRad) * radius);
     setCentreY(pt2y + qSin(startRad) * radius);
     // Circle - Compute rectangle required by Arc2D
     setCW(radius * 2.0);
     setCH(radius * 2.0);
     setCX(getCentreX()-(radius));
     setCY(getCentreY()-(radius));
    }
    else
    {
     // Elipse - Round start angle to the closest multiple of 90
     setStartAdj(qRound(getStartAdj() / 90.0) * 90.0);
     // Elipse - Compute rectangle required by Arc2D
     setCW(qAbs(a)*2.0);
     setCH(qAbs(o)*2.0);
     // Elipse - Adjust rectangle corner, depending on quadrant
     if (o * a < 0.0)
      a = -a;
     else
      o = -o;
     setCX(qMin(pt1x, pt2x)-qMax(a, 0.0));
     setCY(qMin(pt1y, pt2y)-qMax(o, 0.0));
    }
   }
  }
}
/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::draw1(EditScene* g2, bool isMain, bool isBlock, QPen drawingStroke) {
    if (!isBlock && isDashed() && getLayoutBlock() != nullptr) {
        // Skip the dashed rail layer, the block layer will display the dashed track
        // This removes random rail fragments from between the block dashes
        return;
    }
#if 1
    QColor color;
    if (isMain == mainline) {
        if (isBlock) {
            color = setColorForTrackBlock(g2, getLayoutBlock());
            drawingStroke.setColor(color);
        }
        if (isArc()) {
            calculateTrackSegmentAngle();
//            g2.draw(new Arc2D(getCX(), getCY(), getCW(), getCH(), getStartAdj(), getTmpAngle(), Arc2D.OPEN));
            QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
            lineItem->setStartAngle(getStartAdj()*16);
            lineItem->setSpanAngle(getTmpAngle()*16);
            lineItem->setPen(drawingStroke);
            item = lineItem;
            g2->addItem(item);

            trackRedrawn();
        }
#if 1
        else if (isBezier()) {
            QPointF pt1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF pt2 = LayoutEditor::getCoords(getConnect2(), getType2());

            int cnt = bezierControlPoints.size();
            QVector<QPointF> points = QVector<QPointF>(cnt + 2);
            points.replace(0, pt1);
            for (int idx = 0; idx < cnt; idx++) {
                points.replace(idx + 1, bezierControlPoints.at(idx));
            }
            points.replace(cnt + 1, pt2);

            QPainterPath path = MathUtil::drawBezier( points);
            QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
            pathItem->setPen(drawingStroke);
            g2->addItem(pathItem);
        }
#endif
        else {
            QPointF end1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF end2 = LayoutEditor::getCoords(getConnect2(), getType2());

            //g2.draw(new Line2D(end1, end2));
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(end1.x(), end1.y(), end2.x(), end2.y());
            lineItem->setPen(drawingStroke);
            item = lineItem;
            g2->addItem(item);
            trackRedrawn();
        }
    }
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::draw2(EditScene* g2, bool isMain, float railDisplacement, QPen drawingStroke) {
    if (isDashed() && getLayoutBlock() != nullptr) {
        // Skip the dashed rail layer, the block layer will display the dashed track
        // This removes random rail fragments from between the block dashes
        return;
    }

    if (isMain == mainline) {
        if (isArc()) {
            calculateTrackSegmentAngle();
            QRectF cRectangle2D =  QRectF(
                    getCX(), getCY(), getCW(), getCH());
            QRectF cLeftRectangle2D = MathUtil::inset(cRectangle2D, -railDisplacement);
            double startAdj = getStartAdj(), tmpAngle = getTmpAngle();
//            g2.draw(new Arc2D(
//                    cLeftRectangle2D.getX(),
//                    cLeftRectangle2D.getY(),
//                    cLeftRectangle2D.getWidth(),
//                    cLeftRectangle2D.getHeight(),
//                    startAdj, tmpAngle, Arc2D.OPEN));
            QGraphicsArcItem* lineItem = new QGraphicsArcItem(cLeftRectangle2D.x(), cLeftRectangle2D.y(), cLeftRectangle2D.width(), cLeftRectangle2D.height());
            lineItem->setStartAngle(getStartAdj()*16);
            lineItem->setSpanAngle(getTmpAngle()*16);
            lineItem->setPen(drawingStroke);
            item = lineItem;
            g2->addItem(item);
            QRectF cLRightRectangle2D = MathUtil::inset(cRectangle2D, +railDisplacement);
//            g2.draw(new Arc2D(
//                    cLRightRectangle2D.getX(),
//                    cLRightRectangle2D.getY(),
//                    cLRightRectangle2D.getWidth(),
//                    cLRightRectangle2D.getHeight(),
//                    startAdj, tmpAngle, Arc2D.OPEN));
            lineItem = new QGraphicsArcItem(cLRightRectangle2D.x(), cLRightRectangle2D.y(), cLRightRectangle2D.width(), cLRightRectangle2D.height());
            lineItem->setStartAngle(getStartAdj()*16);
            lineItem->setSpanAngle(getTmpAngle()*16);
            lineItem->setPen(drawingStroke);
            item = lineItem;
            g2->addItem(item);
            trackRedrawn();
        }
#if 0
        else if (isBezier()) {
            QPointF pt1 = LayoutEditor.getCoords(getConnect1(), getType1());
            QPointF pt2 = LayoutEditor.getCoords(getConnect2(), getType2());

            int cnt = bezierControlPoints.size();
            QPointF[] points = new QPointF[cnt + 2];
            points[0] = pt1;
            for (int idx = 0; idx < cnt; idx++) {
                points[idx + 1] = bezierControlPoints.get(idx);
            }
            points[cnt + 1] = pt2;

            MathUtil::drawBezier(g2, points, -railDisplacement);
            MathUtil::drawBezier(g2, points, +railDisplacement);
        }
#else
        else {
            QPointF end1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF end2 = LayoutEditor::getCoords(getConnect2(), getType2());

            QPointF delta = MathUtil::subtract(end2, end1);
            QPointF vector = MathUtil::normalize(delta, railDisplacement);
            vector = MathUtil::orthogonal(vector);

            QPointF ep1L = MathUtil::add(end1, vector);
            QPointF ep2L = MathUtil::add(end2, vector);
            //g2.draw(new Line2D(ep1L, ep2L));
            QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1L.x(), ep1L.y(), ep2L.x(), ep2L.y());
            lineItem->setPen(drawingStroke);
            itemGroup->addToGroup(lineItem);

            QPointF ep1R = MathUtil::subtract(end1, vector);
            QPointF ep2R = MathUtil::subtract(end2, vector);
            //g2.draw(new Line2D(ep1R, ep2R));
            lineItem = new QGraphicsLineItem(ep1R.x(), ep1R.y(), ep2R.x(), ep2R.y());
            lineItem->setPen(drawingStroke);
            itemGroup->addToGroup(lineItem);
            item = itemGroup;
            g2->addItem(item);
            trackRedrawn();

        }
    }
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::highlightUnconnected(EditScene* g2, int selectedType) {
    // TrackSegments are always connected
    // nothing to see here... move along...
}

//@Override
/*protected*/ void TrackSegment::drawEditControls(EditScene* g2) {
#if 0
    g2.setColor(Color.black);
    if (isShowConstructionLines()) {
        QPointF ep1 = LayoutEditor.getCoords(getConnect1(), getType1());
        QPointF ep2 = LayoutEditor.getCoords(getConnect2(), getType2());
        if (isCircle()) {
            // draw radiuses
            QPointF circleCenterPoint = getCoordsCenterCircle();
            g2.draw(new Line2D(circleCenterPoint, ep1));
            g2.draw(new Line2D(circleCenterPoint, ep2));
            // Draw a circle and square at the circles centre, that
            // allows the user to change the angle by dragging the mouse.
            g2.draw(layoutEditor.trackEditControlCircleAt(circleCenterPoint));
            g2.draw(layoutEditor.trackEditControlRectAt(circleCenterPoint));
        } else if (isBezier()) {
            //draw construction lines and control circles
            QPointF lastPt = ep1;
            for (QPointF bcp : bezierControlPoints) {
                g2.draw(new Line2D(lastPt, bcp));
                lastPt = bcp;
                g2.draw(layoutEditor.trackEditControlRectAt(bcp));
            }
            g2.draw(new Line2D(lastPt, ep2));
        }
    }
    g2.draw(layoutEditor.trackEditControlCircleAt(getCentreSeg()));
#endif
}   // drawEditControls

//@Override
/*protected*/ void TrackSegment::drawTurnoutControls(EditScene* g2) {
    // TrackSegments don't have turnout controls...
    // nothing to see here... move along...
}

/*
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegment::reCheckBlockBoundary() {
    // nothing to see here... move along...
}

void TrackSegment::drawSolidTrack(LayoutEditor* editor, QGraphicsScene* g2, bool /*isMainline*/)
{
 QColor color;

 LayoutBlock* b = getLayoutBlock();
 if (b!=NULL)
  color = (b->getBlockColor());
 else
  color =(editor->defaultTrackColor);
 Q_ASSERT(color.isValid());

 //setTrackStrokeWidth(g2,mainline);
 if(getArc())
 {
  calculateTrackSegmentAngle();
  //g2.draw(new Arc2D(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
  lineItem->setStartAngle(getStartAdj()*16);
  lineItem->setSpanAngle(getTmpAngle()*16);
  lineItem->setPen(QPen(QColor(color),editor->trackWidth));
  item = lineItem;
  g2->addItem(item);
 } else
 {
  //g2.draw(new Line2D(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
  //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(QColor(color),trackWidth));
  QPointF p1 = LayoutEditor::getCoords(getConnect1(),getType1());
  QPointF p2 = LayoutEditor::getCoords(getConnect2(),getType2());
  log->debug(tr("line '%5' from %1,%2 -> %3,%4").arg(p1.x()).arg(p1.y()).arg(p2.x()).arg(p2.y()).arg(ident));
  QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()),
                                                             LayoutEditor::getCoords(getConnect2(),getType2())));
  lineItem->setPen(QPen(QColor(color),editor->trackWidth));
  item = lineItem;
  g2->addItem(item);
 }
 trackRedrawn();
}
void TrackSegment::drawTrackOvals(LayoutEditor *editor, QGraphicsScene *g2)
{
 QColor color;
 color = (editor->defaultTrackColor);
 QPointF pt1 = LayoutEditor::getCoords(getConnect1(),getType1());
 QPointF pt2 = LayoutEditor::getCoords(getConnect2(),getType2());
 double cX = (pt1.x() + pt2.x())/2.0;
 double cY = (pt1.y() + pt2.y())/2.0;
 //g2.draw(new Ellipse2D (cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
 QGraphicsItemGroup* group = new QGraphicsItemGroup();
 //g2->addEllipse(cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2,QPen(color,1));
 if(!editor->hideTrackSegmentConstructionLines->isChecked())
 {
  QGraphicsEllipseItem* item = new QGraphicsEllipseItem(cX-LayoutEditor::SIZE2, cY-LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2, LayoutEditor::SIZE2+LayoutEditor::SIZE2);
  item->setPen(QPen(color,1));
  group->addToGroup(item);
 }
 if (getArc())
 {
  LayoutBlock* b = getLayoutBlock();
  if (b!=NULL) color =(b->getBlockColor());
  else color =(editor->defaultTrackColor);
  //g2.draw(new Line2D(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
  //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(color,1));
  if(!editor->hideTrackSegmentConstructionLines->isChecked())
  {
   QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()), LayoutEditor::getCoords(getConnect2(),getType2())));
   item->setPen(QPen(color,1));
   group->addToGroup(item);
  }
  if (getCircle())
  {
   //g2.draw(new Line2D();
   //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()),  QPointF(t->getCentreX(),t->getCentreY())),QPen(color,trackWidth));
   if(!editor->hideTrackSegmentConstructionLines->isChecked())
   {
    QGraphicsLineItem* item1 = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()),  QPointF(getCentreX(),getCentreY())));
    item1->setPen(QPen(color,1));
    group->addToGroup(item1);
    //g2.draw(new Line2D(getCoords(t.getConnect2(),t.getType2()), new QPointF(t.getCentreX(),t.getCentreY())));
    //g2->addLine(QLineF(getCoords(t->getConnect2(),t->getType2()), QPointF(t->getCentreX(),t->getCentreY())),QPen(color, trackWidth));
    QGraphicsLineItem* item2 = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect2(),getType2()), QPointF(getCentreX(),getCentreY())));
    item2->setPen(QPen(color, 1));
    group->addToGroup(item2);
   }
  }
  color =(editor->defaultTrackColor);
 }
 trackOval = group;
 g2->addItem(trackOval);
}

void TrackSegment::drawTrackCircleCentre(LayoutEditor *editor, QGraphicsScene *g2)
{
 if(editor->hideTrackSegmentConstructionLines->isChecked())
  return;

    QPointF pt = getCoordsCenterCircle();
    reCalculateTrackSegmentAngle(pt.x(), pt.y()); // added ACK
//    g2.setColor(Color.black);
//    g2.draw(new Rectangle2D (pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
      //g2->addRect(QRectF(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2),QPen(QColor(Qt::black),1));
    QGraphicsRectItem* item = new QGraphicsRectItem(QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2));
    item->setPen(QPen(QColor(Qt::black),1));
    circleItem = item;
    g2->addItem(circleItem);
}

/*
* The recalculation method is used when the user changes the angle dynamically in edit mode
* by dragging the centre of the cirle
*/
/*private*/ void TrackSegment::reCalculateTrackSegmentAngle(double x, double y)
{

  double pt2x;
  double pt2y;
  double pt1x;
  double pt1y;

  pt2x = getTmpPt2().x();
  pt2y = getTmpPt2().y();
  pt1x = getTmpPt1().x();
  pt1y = getTmpPt1().y();
  if (getFlip())
  {
   pt1x = getTmpPt2().x();
   pt1y = getTmpPt2().y();
   pt2x = getTmpPt1().x();
   pt2y = getTmpPt1().y();
  }
  //Point 1 to new point length
  double a;
  double o;
  double la;
  // Compute arc's chord
  a = pt2x - x;
  o = pt2y - y;
  la=qSqrt(((a*a)+(o*o)));

  double lb;
  a = pt1x - x;
  o = pt1y - y;
  lb=qSqrt(((a*a)+(o*o)));
  //double toDegrees = M_PI/180;
  double newangle=radToDeg(qAcos((-getChordLength()*getChordLength()+la*la+lb*lb)/(2*la*lb)));
  setAngle(newangle);
  //qDebug() << tr("newangle = %1").arg(newangle);
}
double TrackSegment::radToDeg(double radians)
{
 double toDegrees = 180./M_PI;
 return radians * toDegrees;
}
double TrackSegment::degToRad(double degrees)
{
 double toRadians = M_PI/180.0;
 return degrees * toRadians;
}
/*public*/ void TrackSegment::hideConstructionLines(int hide)
{
 if (hide == HIDECONALL)
 {
     showConstructionLine = showConstructionLine + HIDECONALL;
 } else if (hide == SHOWCON) {
     if ((showConstructionLine & HIDECONALL) == HIDECONALL) {
         showConstructionLine = (showConstructionLine & (~HIDECONALL));
     } else {
         showConstructionLine = hide;
     }
 } else {
     showConstructionLine = HIDECON;
 }
 //layoutEditor.redrawPanel();
 layoutEditor->setDirty();
}

/*public*/ bool TrackSegment::hideConstructionLines() {
    if ((showConstructionLine & SHOWCON) == SHOWCON) {
        return false;
    } else {
        return true;
    }
}

/**
 * Get the coordinates for a specified connection type.
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
//@Override
/*public*/ QPointF TrackSegment::getCoordsForConnectionType(int connectionType) {
    QPointF result = getCentreSeg();
    if (connectionType == TRACK_CIRCLE_CENTRE) {
        result = getCoordsCenterCircle();
    } else if ((connectionType >= BEZIER_CONTROL_POINT_OFFSET_MIN) && (connectionType <= BEZIER_CONTROL_POINT_OFFSET_MAX)) {
        result = getBezierControlPoint(connectionType - BEZIER_CONTROL_POINT_OFFSET_MIN);
    }
    return result;
}


/**
 * @return the bounds of this track segment
 */
//@Override
/*public*/ QRectF TrackSegment::getBounds() {
//    QRectF result;

//    QPointF ep1 = center, ep2 = center;
//    if (getConnect1() != null) {
//        ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
//    }
//    if (getConnect2() != null) {
//        ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
//    }

//    result = QRectF(ep1.x(), ep1.y(), 0, 0);
//    result.add(ep2);

//    return result;
 return item->boundingRect();
}
/*======================*\
|* decoration accessors *|
\*======================*/
//@Override
/*public*/ bool TrackSegment::hasDecorations() {
    return ((arrowStyle > 0)
            || (bridgeSideLeft || bridgeSideRight)
            || (bumperEndStart || bumperEndStop)
            || (tunnelSideLeft || tunnelSideRight));
}

/**
 * get decorations
 *
 * @return decorations to set
 */
//@Override
/*public*/ QMap<QString, QString>* TrackSegment::getDecorations() {
    if (decorations == nullptr) {
        decorations = new QMap<QString, QString>();
    } //if (decorathions != null)

    //
    // arrow decorations
    //
    if (arrowStyle > 0) {
        // <decoration name="arrow" value="double;both;linewidth=1;length=12;gap=1" />
        QStringList arrowValues = QStringList();

        arrowValues.append("style=" + QString::number(arrowStyle));

        if (arrowEndStart && arrowEndStop) {
            // default behaviour is both
        } else if (arrowEndStop) {
            arrowValues.append("stop");
        } else {
            arrowEndStart = true;
            arrowValues.append("start");
        }

        if (arrowDirIn && !arrowDirOut) {
            arrowValues.append("in");
        } else if (!arrowDirIn && arrowDirOut) {
            arrowValues.append("out");
        } else {
            arrowDirIn = true;
            arrowDirOut = true;
            arrowValues.append("both");
        }
        arrowValues.append("color=" + ColorUtil::colorToHexString(arrowColor));
        arrowValues.append("linewidth=" +  QString::number(arrowLineWidth));
        arrowValues.append("length=" +  QString::number(arrowLength));
        arrowValues.append("gap=" +  QString::number(arrowGap));
        decorations->insert("arrow",arrowValues.join(";"));
    }   // if (arrowCount > 0)

    //
    //  bridge decorations
    //
    if (bridgeSideLeft || bridgeSideRight) {
        // <decoration name="bridge" value="both;linewidth=2;deckwidth=8" />
        QStringList bridgeValues = QStringList();

        if (bridgeHasEntry && !bridgeHasExit) {
            bridgeValues.append("entry");
        } else if (!bridgeHasEntry && bridgeHasExit) {
            bridgeValues.append("exit");
        } else if (bridgeHasEntry && bridgeHasExit) {
            bridgeValues.append("both");
        }
        if (bridgeSideLeft && !bridgeSideRight) {
            bridgeValues.append("left");
        } else if (!bridgeSideLeft && bridgeSideRight) {
            bridgeValues.append("right");
        }
        bridgeValues.append("color=" + ColorUtil::colorToHexString(bridgeColor));
        bridgeValues.append("linewidth=" +  QString::number(bridgeLineWidth));
        bridgeValues.append("approachwidth=" +  QString::number(bridgeApproachWidth));
        bridgeValues.append("deckwidth=" +  QString::number(bridgeDeckWidth));

        decorations->insert("bridge", bridgeValues.join(";"));;
    }   // if (bridgeSideLeft || bridgeSideRight)

    //
    //  end bumper decorations
    //
    if (bumperEndStart || bumperEndStop) {
        // <decoration name="bumper" value="double;linewidth=2;length=6;gap=2;flipped" />
        QStringList bumperValues = QStringList();
        if (bumperEndStart) {
            bumperValues.append("start");
        } else if (bumperEndStop) {
            bumperValues.append("stop");
        }

        if (bumperFlipped) {
            bumperValues.append("flip");
        }
        bumperValues.append("color=" + ColorUtil::colorToHexString(bumperColor));
        bumperValues.append("length=" + QString::number(bumperLength));
        bumperValues.append("linewidth=" +  QString::number(bumperLineWidth));

        decorations->insert("bumper", bumperValues.join(";"));
    }   // if (bumperCount > 0)

    //
    //  tunnel decorations
    //
    if (tunnelSideLeft || tunnelSideRight) {
        // <decoration name="tunnel" value="both;linewidth=2;floorwidth=8" />
        QStringList tunnelValues = QStringList();

        if (tunnelHasEntry && !tunnelHasExit) {
            tunnelValues.append("entry");
        } else if (!tunnelHasEntry && tunnelHasExit) {
            tunnelValues.append("exit");
        } else if (tunnelHasEntry && tunnelHasExit) {
            tunnelValues.append("both");
        }

        if (tunnelSideLeft && !tunnelSideRight) {
            tunnelValues.append("left");
        } else if (tunnelSideLeft && !tunnelSideRight) {
            tunnelValues.append("right");
        }
        tunnelValues.append("color=" + ColorUtil::colorToHexString(tunnelColor));
        tunnelValues.append("linewidth=" +  QString::number(tunnelLineWidth));
        tunnelValues.append("entrancewidth=" +  QString::number(tunnelEntranceWidth));
        tunnelValues.append("floorwidth=" +  QString::number(tunnelFloorWidth));

        decorations->insert("tunnel", tunnelValues.join(";"));
    }   // if (tunnelSideLeft || tunnelSideRight)
    return decorations;
} // getDecorations

/**
 * set decorations
 *
 * @param decorations to set
 */
//@Override
/*public*/ void TrackSegment::setDecorations(QMap<QString, QString>* decorations) {
    LayoutTrack::setDecorations(decorations);
    if (decorations != nullptr) {
        //for (Map.Entry<String, String> entry : decorations.entrySet())
        QMapIterator<QString, QString> entry(*decorations);
        while(entry.hasNext())
        {
            log->debug("Key = " + entry.key() + ", Value = " + entry.value());
            QString key = entry.key();
            //
            // arrow decorations
            //
            if (key == ("arrow")) {
                QString arrowValue = entry.value();
                // <decoration name="arrow" value="double;both;linewidth=1;length=12;gap=1" />
                bool atStart = true, atStop = true;
                bool hasIn = false, hasOut = false;
                int lineWidth = 1, length = 3, gap = 1, count = 1;
                QColor color = defaultTrackColor;
                QStringList values = arrowValue.split(";");
                for (int i = 0; i < values.length(); i++) {
                    QString value = values[i];
                    if (value == ("single")) {
                        count = 1;
                    } else if (value == ("double")) {
                        count = 2;
                    } else if (value == ("triple")) {
                        count = 3;
                    } else if (value.startsWith("style=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        count = (valueString.toInt());
                    } else if (value == ("start")) {
                        atStop = false;
                    } else if (value == ("stop")) {
                        atStart = false;
                    } else if (value == ("in")) {
                        hasIn = true;
                    } else if (value == ("out")) {
                        hasOut = true;
                    } else if (value == ("both")) {
                        hasIn = true;
                        hasOut = true;
                    } else if (value.startsWith("color=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        color = ColorUtil::stringToColor(valueString);
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = (valueString.toInt());
                    } else if (value.startsWith("length=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        length = (valueString.toInt());
                    } else if (value.startsWith("gap=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        gap = (valueString.toInt());
                    } else {
                        log->debug("arrow value ignored: " + value);
                    }
                }
                hasIn |= !hasOut;   // if hasOut is false make hasIn true
                if (!atStart && !atStop) {   // if both false
                    atStart = true; // set both true
                    atStop = true;
                }
                setArrowEndStart(atStart);
                setArrowEndStop(atStop);
                setArrowDirIn(hasIn);
                setArrowDirOut(hasOut);
                setArrowColor(color);
                setArrowLineWidth(lineWidth);
                setArrowLength(length);
                setArrowGap(gap);
                // set count last so it will fix ends and dir (if necessary)
                setArrowStyle(count);
            } // if (key == ("arrow")) {
            //
            //  bridge decorations
            //
            else if (key == ("bridge")) {
                QString bridgeValue = entry.value();
                // <decoration name="bridge" value="both;linewidth=2;deckwidth=8" />
                // right/left default true; in/out default false
                bool hasLeft = true, hasRight = true, hasEntry = false, hasExit = false;
                int approachWidth = 4, lineWidth = 1, deckWidth = 2;
                QColor color = defaultTrackColor;
                QStringList values = bridgeValue.split(";");
                for (int i = 0; i < values.length(); i++) {
                    QString value = values[i];
                    //log.info("value[{}]: \"{}\"", i, value);
                    if (value == ("left")) {
                        hasRight = false;
                    } else if (value == ("right")) {
                        hasLeft = false;
                    } else if (value == ("entry")) {
                        hasEntry = true;
                    } else if (value == ("exit")) {
                        hasExit = true;
                    } else if (value == ("both")) {
                        hasEntry = true;
                        hasExit = true;
                    } else if (value.startsWith("color=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        color = ColorUtil::stringToColor(valueString);
                    } else if (value.startsWith("approachwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        approachWidth = (valueString.toInt());
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = (valueString.toInt());
                    } else if (value.startsWith("deckwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        deckWidth = (valueString.toInt());
                    } else {
                        log->debug("bridge value ignored: " + value);
                    }
                }
                // these both can't be false
                if (!hasLeft && !hasRight) {
                    hasLeft = true;
                    hasRight = true;
                }
                setBridgeSideRight(hasRight);
                setBridgeSideLeft(hasLeft);
                setBridgeHasEntry(hasEntry);
                setBridgeHasExit(hasExit);
                setBridgeColor(color);
                setBridgeDeckWidth(deckWidth);
                setBridgeLineWidth(lineWidth);
                setBridgeApproachWidth(approachWidth);
            } // if (key == ("bridge")) {
            //
            //  bumper decorations
            //
            else if (key == ("bumper")) {
                QString bumperValue = entry.value();
                if (getName() == ("T15")) {
                    log->debug("STOP");
                }
                // <decoration name="bumper" value="double;linewidth=2;length=6;gap=2;flipped" />
                int lineWidth = 1, length = 4;
                bool isFlipped = false, atStart = true, atStop = true;
                QColor color = defaultTrackColor;
                QStringList values = bumperValue.split(";");
                for (int i = 0; i < values.length(); i++) {
                    QString value = values[i];
                    //log.info("value[{}]: \"{}\"", i, value);
                    if (value == ("start")) {
                        atStop = false;
                    } else if (value == ("stop")) {
                        atStart = false;
                    } else if (value == ("both")) {
                        // this is the default behaviour; parameter ignored
                    } else if (value == ("flip")) {
                        isFlipped = true;
                    } else if (value.startsWith("color=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        color = ColorUtil::stringToColor(valueString);
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = (valueString.toInt());
                    } else if (value.startsWith("length=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        length = (valueString.toInt());
                    } else {
                        log->debug("bumper value ignored: " + value);
                    }
                }
                atStop |= !atStart;   // if atStart is false make atStop true
                setBumperEndStart(atStart);
                setBumperEndStop(atStop);
                setBumperColor(color);
                setBumperLineWidth(lineWidth);
                setBumperLength(length);
                setBumperFlipped(isFlipped);
            } // if (key == ("bumper")) {
            //
            //  tunnel decorations
            //
            else if (key == ("tunnel")) {
                QString tunnelValue = entry.value();
                // <decoration name="tunnel" value="both;linewidth=2;floorwidth=8" />
                // right/left default true; in/out default false
                bool hasLeft = true, hasRight = true, hasIn = false, hasOut = false;
                int entranceWidth = 4, lineWidth = 1, floorWidth = 2;
                QColor color = defaultTrackColor;
                QStringList values = tunnelValue.split(";");
                for (int i = 0; i < values.length(); i++) {
                    QString value = values[i];
                    //log.info("value[{}]: \"{}\"", i, value);
                    if (value == ("left")) {
                        hasRight = false;
                    } else if (value == ("right")) {
                        hasLeft = false;
                    } else if (value == ("entry")) {
                        hasIn = true;
                    } else if (value == ("exit")) {
                        hasOut = true;
                    } else if (value == ("both")) {
                        hasIn = true;
                        hasOut = true;
                    } else if (value.startsWith("color=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        color = ColorUtil::stringToColor(valueString);
                    } else if (value.startsWith("entrancewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        entranceWidth = (valueString.toInt());
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = (valueString.toInt());
                    } else if (value.startsWith("floorwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        floorWidth = (valueString.toInt());
                    } else {
                        log->debug("tunnel value ignored: " + value);
                    }
                }
                // these both can't be false
                if (!hasLeft && !hasRight) {
                    hasLeft = true;
                    hasRight = true;
                }
                setTunnelSideRight(hasRight);
                setTunnelSideLeft(hasLeft);
                setTunnelHasEntry(hasIn);
                setTunnelHasExit(hasOut);
                setTunnelColor(color);
                setTunnelEntranceWidth(entranceWidth);
                setTunnelLineWidth(lineWidth);
                setTunnelFloorWidth(floorWidth);
            } // if (tunnelValue != null)
            else {
                log->debug("Unknown decoration key: " + key + ", value: " + entry.value());
            }
        }   // for (Map.Entry<String, String> entry : decorations.entrySet())
    } //if (decorathions != null)
}   // setDirections

//
//  arrow decoration accessors
//
/*public*/ int TrackSegment::getArrowStyle() {
    return arrowStyle;
}

/*public*/ void TrackSegment::setArrowStyle(int newVal) {
    if (arrowStyle != newVal) {
        if (newVal > 0) {
            if (!arrowEndStart && !arrowEndStop) {
                arrowEndStart = true;
                arrowEndStop = true;
            }
            if (!arrowDirIn && !arrowDirOut) {
                arrowDirOut = true;
            }
        }
        arrowStyle = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isArrowEndStart() {
    return arrowEndStart;
}

/*public*/ void TrackSegment::setArrowEndStart(bool newVal) {
    if (arrowEndStart != newVal) {
        arrowEndStart = newVal;
        if (!arrowEndStart && !arrowEndStop) {
            arrowStyle = 0;
        } else if (arrowStyle == 0) {
            arrowStyle = 1;
        }
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isArrowEndStop() {
    return arrowEndStop;
}

/*public*/ void TrackSegment::setArrowEndStop(bool newVal) {
    if (arrowEndStop != newVal) {
        arrowEndStop = newVal;
        if (!arrowEndStart && !arrowEndStop) {
            arrowStyle = 0;
        } else if (arrowStyle == 0) {
            arrowStyle = 1;
        }
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isArrowDirIn() {
    return arrowDirIn;
}

/*public*/ void TrackSegment::setArrowDirIn(bool newVal) {
    if (arrowDirIn != newVal) {
        arrowDirIn = newVal;
        if (!arrowDirIn && !arrowDirOut) {
            arrowStyle = 0;
        } else if (arrowStyle == 0) {
            arrowStyle = 1;
        }
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isArrowDirOut() {
    return arrowDirOut;
}

/*public*/ void TrackSegment::setArrowDirOut(bool newVal) {
    if (arrowDirOut != newVal) {
        arrowDirOut = newVal;
        if (!arrowDirIn && !arrowDirOut) {
            arrowStyle = 0;
        } else if (arrowStyle == 0) {
            arrowStyle = 1;
        }
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegment::getArrowColor() {
    return arrowColor;
}

/*public*/ void TrackSegment::setArrowColor(QColor newVal) {
    if (arrowColor != newVal) {
        arrowColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getArrowLineWidth() {
    return arrowLineWidth;
}

/*public*/ void TrackSegment::setArrowLineWidth(int newVal) {
    if (arrowLineWidth != newVal) {
        arrowLineWidth =qMax(1, newVal);   // don't let value be less than 1
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getArrowLength() {
    return arrowLength;
}

/*public*/ void TrackSegment::setArrowLength(int newVal) {
    if (arrowLength != newVal) {
        arrowLength = qMax(2, newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getArrowGap() {
    return arrowGap;
}

/*public*/ void TrackSegment::setArrowGap(int newVal) {
    if (arrowGap != newVal) {
        arrowGap =qMax(0, newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}
//
//  bridge decoration accessors
//
/*public*/ bool TrackSegment::isBridgeSideRight() {
    return bridgeSideRight;
}

/*public*/ void TrackSegment::setBridgeSideRight(bool newVal) {
    if (bridgeSideRight != newVal) {
        bridgeSideRight = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isBridgeSideLeft() {
    return bridgeSideLeft;
}

/*public*/ void TrackSegment::setBridgeSideLeft(bool newVal) {
    if (bridgeSideLeft != newVal) {
        bridgeSideLeft = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isBridgeHasEntry() {
    return bridgeHasEntry;
}

/*public*/ void TrackSegment::setBridgeHasEntry(bool newVal) {
    if (bridgeHasEntry != newVal) {
        bridgeHasEntry = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isBridgeHasExit() {
    return bridgeHasExit;
}

/*public*/ void TrackSegment::setBridgeHasExit(bool newVal) {
    if (bridgeHasExit != newVal) {
        bridgeHasExit = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegment::getBridgeColor() {
    return bridgeColor;
}

/*public*/ void TrackSegment::setBridgeColor(QColor newVal) {
    if (bridgeColor != newVal) {
        bridgeColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getBridgeDeckWidth() {
    return bridgeDeckWidth;
}

/*public*/ void TrackSegment::setBridgeDeckWidth(int newVal) {
    if (bridgeDeckWidth != newVal) {
        bridgeDeckWidth = qMax(0, newVal);   // don't let value be less than 0
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getBridgeLineWidth() {
    return bridgeLineWidth;
}

/*public*/ void TrackSegment::setBridgeLineWidth(int newVal) {
    if (bridgeLineWidth != newVal) {
        bridgeLineWidth = qMax(1, newVal);   // don't let value be less than 1
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getBridgeApproachWidth() {
    return bridgeApproachWidth;
}

/*public*/ void TrackSegment::setBridgeApproachWidth(int newVal) {
    if (bridgeApproachWidth != newVal) {
        bridgeApproachWidth = qMax(0, newVal);   // don't let value be less than 0
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

//
//  bumper decoration accessors
//
/*public*/ bool TrackSegment::isBumperEndStart() {
    return bumperEndStart;
}

/*public*/ void TrackSegment::setBumperEndStart(bool newVal) {
    if (bumperEndStart != newVal) {
        bumperEndStart = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isBumperEndStop() {
    return bumperEndStop;
}

/*public*/ void TrackSegment::setBumperEndStop(bool newVal) {
    if (bumperEndStop != newVal) {
        bumperEndStop = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegment::getBumperColor() {
    return bumperColor;
}

/*public*/ void TrackSegment::setBumperColor(QColor newVal) {
    if (bumperColor != newVal) {
        bumperColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getBumperLineWidth() {
    return bumperLineWidth;
}

/*public*/ void TrackSegment::setBumperLineWidth(int newVal) {
    if (bumperLineWidth != newVal) {
        bumperLineWidth = qMax(1, newVal);   // don't let value be less than 1
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*private*/ void TrackSegment::setupDefaultBumperSizes(LayoutEditor* layoutEditor) {
    LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();

    // use these as default sizes for end bumpers
    int tieLength = ltdo->getSideTieLength();
    int tieWidth = ltdo->getSideTieWidth();
    int railWidth = ltdo->getSideRailWidth();
    int railGap = ltdo->getSideRailGap();
    if (mainline) {
        tieLength = ltdo->getMainTieLength();
        tieWidth = ltdo->getMainTieWidth();
        railWidth = ltdo->getMainRailWidth();
        railGap = ltdo->getMainRailGap();
    }
    bumperLineWidth = railWidth;
    bumperLength = railGap + railWidth;
    if ((tieLength > 0) && (tieWidth > 0)) {
        bumperLineWidth = tieWidth;
        bumperLength = tieLength * 3 / 2;
    }
}

/*public*/ int TrackSegment::getBumperLength() {
    return bumperLength;
}

/*public*/ void TrackSegment::setBumperLength(int newVal) {
    if (bumperLength != newVal) {
        bumperLength = qMax(0, newVal);   // don't let value be less than 0
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isBumperFlipped() {
    return bumperFlipped;
}

/*public*/ void TrackSegment::setBumperFlipped(bool newVal) {
    if (bumperFlipped != newVal) {
        bumperFlipped = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

//
//  tunnel decoration accessors
//
/*public*/ bool TrackSegment::isTunnelSideRight() {
    return tunnelSideRight;
}

/*public*/ void TrackSegment::setTunnelSideRight(bool newVal) {
    if (tunnelSideRight != newVal) {
        tunnelSideRight = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isTunnelSideLeft() {
    return tunnelSideLeft;
}

/*public*/ void TrackSegment::setTunnelSideLeft(bool newVal) {
    if (tunnelSideLeft != newVal) {
        tunnelSideLeft = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isTunnelHasEntry() {
    return tunnelHasEntry;
}

/*public*/ void TrackSegment::setTunnelHasEntry(bool newVal) {
    if (tunnelHasEntry != newVal) {
        tunnelHasEntry = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegment::isTunnelHasExit() {
    return tunnelHasExit;
}

/*public*/ void TrackSegment::setTunnelHasExit(bool newVal) {
    if (tunnelHasExit != newVal) {
        tunnelHasExit = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegment::getTunnelColor() {
    return tunnelColor;
}

/*public*/ void TrackSegment::setTunnelColor(QColor newVal) {
    if (tunnelColor != newVal) {
        tunnelColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getTunnelFloorWidth() {
    return tunnelFloorWidth;
}

/*public*/ void TrackSegment::setTunnelFloorWidth(int newVal) {
    if (tunnelFloorWidth != newVal) {
        tunnelFloorWidth =qMax(0, newVal);   // don't let value be less than 0
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getTunnelLineWidth() {
    return tunnelLineWidth;
}

/*public*/ void TrackSegment::setTunnelLineWidth(int newVal) {
    if (tunnelLineWidth != newVal) {
        tunnelLineWidth = qMax(1, newVal);   // don't let value be less than 1
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegment::getTunnelEntranceWidth() {
    return tunnelEntranceWidth;
}

/*public*/ void TrackSegment::setTunnelEntranceWidth(int newVal) {
    if (tunnelEntranceWidth != newVal) {
        tunnelEntranceWidth = qMax(0, newVal);   // don't let value be less than 0
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

