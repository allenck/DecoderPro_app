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
 popup = NULL;
 needsRedraw = false;
 bumperColor = QColor(Qt::black);
 tunnelColor = QColor(Qt::black);

 bezierControlPoints = QList<QPointF>(); // list of control point displacements

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
     log->warn("Unknown connect2 object prefix: '" + tConnect2Name + "' of type " + type2 + ".");
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
#if 0
    //
    // arrow decorations
    //
    if (arrowStyle > 0) {
        g2.setStroke(new BasicStroke(arrowLineWidth,
                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
        g2.setColor(arrowColor);

        // draw the out arrows
        int offset = 1;
        if (arrowEndStart) {
            if (arrowDirIn) {
                offset = drawArrow(g2, ep1, Math.PI + startAngleRAD, false, offset);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep1, Math.PI + startAngleRAD, true, offset);
            }
        }
        offset = 1;
        if (arrowEndStop) {
            if (arrowDirIn) {
                offset = drawArrow(g2, ep2, stopAngleRAD, false, offset);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep2, stopAngleRAD, true, offset);
            }
        }
    }   // arrow decoration

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
            Rectangle2D cRectangle2D = new Rectangle2D.Double(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (bridgeSideLeft) {
                Rectangle2D cLeftRectangle2D = MathUtil.inset(cRectangle2D, -halfWidth);
                g2.draw(new Arc2D.Double(
                        cLeftRectangle2D.getX(),
                        cLeftRectangle2D.getY(),
                        cLeftRectangle2D.getWidth(),
                        cLeftRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            if (bridgeSideRight) {
                Rectangle2D cLRightRectangle2D = MathUtil.inset(cRectangle2D, +halfWidth);
                g2.draw(new Arc2D.Double(
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
                MathUtil.drawBezier(g2, points, -halfWidth);
            }
            if (bridgeSideRight) {
                MathUtil.drawBezier(g2, points, +halfWidth);
            }
        } else {
            QPointF delta = MathUtil.subtract(ep2, ep1);
            QPointF vector = MathUtil.normalize(delta, halfWidth);
            vector = MathUtil.orthogonal(vector);

            if (bridgeSideLeft) {
                QPointF ep1L = MathUtil.add(ep1, vector);
                QPointF ep2L = MathUtil.add(ep2, vector);
                g2.draw(new Line2D.Double(ep1L, ep2L));
            }
            if (bridgeSideRight) {
                QPointF ep1R = MathUtil.subtract(ep1, vector);
                QPointF ep2R = MathUtil.subtract(ep2, vector);
                g2.draw(new Line2D.Double(ep1R, ep2R));
            }
        }   // if isArc() {} else if isBezier() {} else...

        if (bridgeHasEntry) {
            if (bridgeSideRight) {
                p1 = new QPointF.Double(-bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = new QPointF.Double(0.0, -halfWidth);
                p1P = MathUtil.add(MathUtil.rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, startAngleRAD), ep1);
                g2.draw(new Line2D.Double(p1P, p2P));
            }
            if (bridgeSideLeft) {
                p1 = new QPointF.Double(-bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = new QPointF.Double(0.0, +halfWidth);
                p1P = MathUtil.add(MathUtil.rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, startAngleRAD), ep1);
                g2.draw(new Line2D.Double(p1P, p2P));
            }
        }
        if (bridgeHasExit) {
            if (bridgeSideRight) {
                p1 = new QPointF.Double(+bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = new QPointF.Double(0.0, -halfWidth);
                p1P = MathUtil.add(MathUtil.rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, stopAngleRAD), ep2);
                g2.draw(new Line2D.Double(p1P, p2P));
            }
            if (bridgeSideLeft) {
                p1 = new QPointF.Double(+bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = new QPointF.Double(0.0, +halfWidth);
                p1P = MathUtil.add(MathUtil.rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, stopAngleRAD), ep2);
                g2.draw(new Line2D.Double(p1P, p2P));
            }
        }
    }   // if (bridgeValue != null)

    //
    //  end bumper decorations
    //
    if (bumperEndStart || bumperEndStop) {
        if (getName().equals("T15")) {
            log->debug("STOP");
        }
        g2.setStroke(new BasicStroke(bumperLineWidth,
                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
        g2.setColor(bumperColor);

        float halfLength = bumperLength / 2.F;

        if (bumperFlipped) {
            double temp = startAngleRAD;
            startAngleRAD = stopAngleRAD;
            stopAngleRAD = temp;
        }

        // common points
        p1 = new QPointF.Double(0.F, -halfLength);
        p2 = new QPointF.Double(0.F, +halfLength);

        if (bumperEndStart) {
            p1P = MathUtil.add(MathUtil.rotateRAD(p1, startAngleRAD), ep1);
            p2P = MathUtil.add(MathUtil.rotateRAD(p2, startAngleRAD), ep1);
        }
        if (bumperEndStop) {
            p1P = MathUtil.add(MathUtil.rotateRAD(p1, stopAngleRAD), ep2);
            p2P = MathUtil.add(MathUtil.rotateRAD(p2, stopAngleRAD), ep2);
        }
        // draw cross tie
        g2.draw(new Line2D.Double(p1P, p2P));
    }   // if (bumperEndStart || bumperEndStop)

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
            Rectangle2D cRectangle2D = new Rectangle2D.Double(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (tunnelSideRight) {
                Rectangle2D cLeftRectangle2D = MathUtil.inset(cRectangle2D, -halfWidth);
                g2.draw(new Arc2D.Double(
                        cLeftRectangle2D.getX(),
                        cLeftRectangle2D.getY(),
                        cLeftRectangle2D.getWidth(),
                        cLeftRectangle2D.getHeight(),
                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
            }
            if (tunnelSideLeft) {
                Rectangle2D cLRightRectangle2D = MathUtil.inset(cRectangle2D, +halfWidth);
                g2.draw(new Arc2D.Double(
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
                MathUtil.drawBezier(g2, points, -halfWidth);
            }
            if (tunnelSideLeft) {
                MathUtil.drawBezier(g2, points, +halfWidth);
            }
        } else {
            QPointF delta = MathUtil.subtract(ep2, ep1);
            QPointF vector = MathUtil.normalize(delta, halfWidth);
            vector = MathUtil.orthogonal(vector);

            if (tunnelSideRight) {
                QPointF ep1L = MathUtil.add(ep1, vector);
                QPointF ep2L = MathUtil.add(ep2, vector);
                g2.draw(new Line2D.Double(ep1L, ep2L));
            }
            if (tunnelSideLeft) {
                QPointF ep1R = MathUtil.subtract(ep1, vector);
                QPointF ep2R = MathUtil.subtract(ep2, vector);
                g2.draw(new Line2D.Double(ep1R, ep2R));
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
                p1 = new QPointF.Double(0.0, 0.0);
                p2 = new QPointF.Double(0.0, -halfFloorWidth);
                p3 = new QPointF.Double(0.0, -halfEntranceWidth);
                p4 = new QPointF.Double(-halfEntranceWidth - halfFloorWidth, -halfEntranceWidth);
                p5 = new QPointF.Double(-halfEntranceWidth - halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = new QPointF.Double(-halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = new QPointF.Double(-halfDiffWidth, 0.0);

                p1P = MathUtil.add(MathUtil.rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil.add(MathUtil.rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil.add(MathUtil.rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil.add(MathUtil.rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil.add(MathUtil.rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil.add(MathUtil.rotateRAD(p7, startAngleRAD), ep1);

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
                p1 = new QPointF.Double(0.0, 0.0);
                p2 = new QPointF.Double(0.0, +halfFloorWidth);
                p3 = new QPointF.Double(0.0, +halfEntranceWidth);
                p4 = new QPointF.Double(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth);
                p5 = new QPointF.Double(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = new QPointF.Double(-halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = new QPointF.Double(-halfDiffWidth, 0.0);

                p1P = MathUtil.add(MathUtil.rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil.add(MathUtil.rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil.add(MathUtil.rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil.add(MathUtil.rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil.add(MathUtil.rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil.add(MathUtil.rotateRAD(p7, startAngleRAD), ep1);

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
                p1 = new QPointF.Double(0.0, 0.0);
                p2 = new QPointF.Double(0.0, -halfFloorWidth);
                p3 = new QPointF.Double(0.0, -halfEntranceWidth);
                p4 = new QPointF.Double(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth);
                p5 = new QPointF.Double(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = new QPointF.Double(halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = new QPointF.Double(halfDiffWidth, 0.0);

                p1P = MathUtil.add(MathUtil.rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil.add(MathUtil.rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil.add(MathUtil.rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil.add(MathUtil.rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil.add(MathUtil.rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil.add(MathUtil.rotateRAD(p7, stopAngleRAD), ep2);

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
                p1 = new QPointF.Double(0.0, 0.0);
                p2 = new QPointF.Double(0.0, +halfFloorWidth);
                p3 = new QPointF.Double(0.0, +halfEntranceWidth);
                p4 = new QPointF.Double(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth);
                p5 = new QPointF.Double(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = new QPointF.Double(halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = new QPointF.Double(halfDiffWidth, 0.0);

                p1P = MathUtil.add(MathUtil.rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil.add(MathUtil.rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil.add(MathUtil.rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil.add(MathUtil.rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil.add(MathUtil.rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil.add(MathUtil.rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil.add(MathUtil.rotateRAD(p7, stopAngleRAD), ep2);

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
}   // drawDecorations
#if 0
/*private*/ int drawArrow(
        EditScene* g2,
        QPointF ep,
        double angleRAD,
        bool dirOut,
        int offset) {
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
                p1 = new QPointF.Double(offset, -arrowLength);
                p2 = new QPointF.Double(offset + arrowLength, 0.0);
                p3 = new QPointF.Double(offset, +arrowLength);
            } else {
                p1 = new QPointF.Double(offset + arrowLength, -arrowLength);
                p2 = new QPointF.Double(offset, 0.0);
                p3 = new QPointF.Double(offset + arrowLength, +arrowLength);
            }
            p1 = MathUtil.add(MathUtil.rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil.add(MathUtil.rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil.add(MathUtil.rotateRAD(p3, angleRAD), ep);

            g2.draw(new Line2D.Double(p1, p2));
            g2.draw(new Line2D.Double(p2, p3));
            offset += arrowLength + arrowGap;
            break;
        }
        case 2: {
            if (dirOut) {
                p1 = new QPointF.Double(offset, -arrowLength);
                p2 = new QPointF.Double(offset + arrowLength, 0.0);
                p3 = new QPointF.Double(offset, +arrowLength);
                p4 = new QPointF.Double(offset + arrowLineWidth + arrowGap, -arrowLength);
                p5 = new QPointF.Double(offset + arrowLineWidth + arrowGap + arrowLength, 0.0);
                p6 = new QPointF.Double(offset + arrowLineWidth + arrowGap, +arrowLength);
            } else {
                p1 = new QPointF.Double(offset + arrowLength, -arrowLength);
                p2 = new QPointF.Double(offset, 0.0);
                p3 = new QPointF.Double(offset + arrowLength, +arrowLength);
                p4 = new QPointF.Double(offset + arrowLineWidth + arrowGap + arrowLength, -arrowLength);
                p5 = new QPointF.Double(offset + arrowLineWidth + arrowGap, 0.0);
                p6 = new QPointF.Double(offset + arrowLineWidth + arrowGap + arrowLength, +arrowLength);
            }
            p1 = MathUtil.add(MathUtil.rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil.add(MathUtil.rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil.add(MathUtil.rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil.add(MathUtil.rotateRAD(p4, angleRAD), ep);
            p5 = MathUtil.add(MathUtil.rotateRAD(p5, angleRAD), ep);
            p6 = MathUtil.add(MathUtil.rotateRAD(p6, angleRAD), ep);

            g2.draw(new Line2D.Double(p1, p2));
            g2.draw(new Line2D.Double(p2, p3));
            g2.draw(new Line2D.Double(p4, p5));
            g2.draw(new Line2D.Double(p5, p6));
            offset += arrowLength + (2 * (arrowLineWidth + arrowGap));
            break;
        }
        case 3: {
            if (dirOut) {
                p1 = new QPointF.Double(offset, -arrowLength);
                p2 = new QPointF.Double(offset + arrowLength, 0.0);
                p3 = new QPointF.Double(offset, +arrowLength);
            } else {
                p1 = new QPointF.Double(offset + arrowLength, -arrowLength);
                p2 = new QPointF.Double(offset, 0.0);
                p3 = new QPointF.Double(offset + arrowLength, +arrowLength);
            }
            p1 = MathUtil.add(MathUtil.rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil.add(MathUtil.rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil.add(MathUtil.rotateRAD(p3, angleRAD), ep);

            GeneralPath path = new GeneralPath();
            path.moveTo(p1.getX(), p1.getY());
            path.lineTo(p2.getX(), p2.getY());
            path.lineTo(p3.getX(), p3.getY());
            path.closePath();
            if (arrowLineWidth > 1) {
                g2.fill(path);
            } else {
                g2.draw(path);
            }
            offset += arrowLength + arrowGap;
            break;
        }
        case 4: {
            if (dirOut) {
                p1 = new QPointF.Double(offset, 0.0);
                p2 = new QPointF.Double(offset + (2 * arrowLength), -arrowLength);
                p3 = new QPointF.Double(offset + (3 * arrowLength), 0.0);
                p4 = new QPointF.Double(offset + (2 * arrowLength), +arrowLength);
            } else {
                p1 = new QPointF.Double(offset + (3 * arrowLength), 0.0);
                p2 = new QPointF.Double(offset, -arrowLength);
                p3 = new QPointF.Double(offset + arrowLength, 0.0);
                p4 = new QPointF.Double(offset, +arrowLength);
            }
            p1 = MathUtil.add(MathUtil.rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil.add(MathUtil.rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil.add(MathUtil.rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil.add(MathUtil.rotateRAD(p4, angleRAD), ep);

            g2.draw(new Line2D.Double(p1, p3));
            g2.draw(new Line2D.Double(p2, p3));
            g2.draw(new Line2D.Double(p3, p4));
            offset += (3 * arrowLength) + arrowGap;
            break;
        }
        case 5: {
            if (dirOut) {
                p1 = new QPointF.Double(offset, 0.0);
                p2 = new QPointF.Double(offset + (2 * arrowLength), -arrowLength);
                p3 = new QPointF.Double(offset + (3 * arrowLength), 0.0);
                p4 = new QPointF.Double(offset + (2 * arrowLength), +arrowLength);
            } else {
                p1 = new QPointF.Double(offset + (3 * arrowLength), 0.0);
                p2 = new QPointF.Double(offset, -arrowLength);
                p3 = new QPointF.Double(offset + arrowLength, 0.0);
                p4 = new QPointF.Double(offset, +arrowLength);
            }
            p1 = MathUtil.add(MathUtil.rotateRAD(p1, angleRAD), ep);
            p2 = MathUtil.add(MathUtil.rotateRAD(p2, angleRAD), ep);
            p3 = MathUtil.add(MathUtil.rotateRAD(p3, angleRAD), ep);
            p4 = MathUtil.add(MathUtil.rotateRAD(p4, angleRAD), ep);

            GeneralPath path = new GeneralPath();
            path.moveTo(p4.getX(), p4.getY());
            path.lineTo(p2.getX(), p2.getY());
            path.lineTo(p3.getX(), p3.getY());
            path.closePath();
            if (arrowLineWidth > 1) {
                g2.fill(path);
            } else {
                g2.draw(path);
            }
            g2.draw(new Line2D.Double(p1, p3));

            offset += (3 * arrowLength) + arrowGap;
            break;
        }
    }

    return offset;
}   // drawArrow
#endif
/**
 * Display popup menu for information and editing
 */
/*protected*/ void TrackSegment::showPopUp(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popup != NULL )
 {
  popup->clear();
 }
 else
 {
  popup = new QMenu();
 }
 //popup->addAction(new QAction(tr("Track Segment ") + getID(),this));
 popup->addSection(tr("Track Segment ") + getID());
 if (!dashed) popup->addAction(new QAction(tr("Style")+" - "+tr("Solid"),this));
    else popup->addAction(new QAction(tr("Style")+" - "+tr("Dashed"),this));
    if (!mainline) popup->addAction(new QAction(tr("Not Mainline"),this));
    else popup->addAction(new QAction(tr("Mainline"),this));
    if (blockName==("")) popup->addAction(new QAction(tr("No Block"),this));
    else popup->addAction(new QAction(tr("Block")+": "+getLayoutBlock()->getID(),this));
    if (hidden) popup->addAction(new QAction(tr("Hidden"),this));
    else popup->addAction(new QAction(tr("Not Hidden"),this));
    popup->addSeparator();
//    popup.add(new AbstractAction(rb.getQString("Edit")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                editTrackSegment();
//            }
//        });
    QAction* editAction = new QAction(tr("Edit"),this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(on_actionEdit_triggered()));
    popup->addAction(editAction);
//    popup.add(new AbstractAction(rb.getQString("Remove")) {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                layoutEditor.removeTrackSegment(instance);
//                remove();
//                dispose();
//            }
//        });
    QAction* removeAction = new QAction(tr("Remove"),this);
    popup->addAction(removeAction);
    connect(removeAction, SIGNAL(triggered()), this, SLOT(on_actionRemove()));

    QMenu* lineType = new QMenu(tr("Change To"));
    QActionGroup* actGrp = new QActionGroup(this);
    actGrp->setExclusive(true);
    popup->addMenu(lineType);
    QAction* lineAction = new QAction(tr("Line"),this);
    lineAction->setCheckable(true);
    lineAction->setChecked(!arc && !circle);
    lineAction->setData(0);
    lineType->addAction(lineAction);
    actGrp->addAction(lineAction);
//    lineType.add(new AbstractAction("Line") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(0);
//            }
//    });
    QAction* circleAction = new QAction(tr("Circle"),this);
    circleAction->setCheckable(true);
    circleAction->setChecked(circle && arc);
    circleAction->setData(1);
    lineType->addAction(circleAction);
    actGrp->addAction(circleAction);
//    lineType.add(new AbstractAction("Circle") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(1);
//        }
////    });
    QAction* ellipseAction = new QAction(tr("Ellipse"),this);
    ellipseAction->setCheckable(true);
    ellipseAction->setChecked(arc && !circle);
    ellipseAction->setData(2);
    lineType->addAction(ellipseAction);
    actGrp->addAction(ellipseAction);
//    lineType.add(new AbstractAction("Elipse") {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            changeType(2);
//        }
//    });
    connect(actGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_changeType(QAction*)));
    popup->addMenu(lineType);
    if (getArc())
    {
//        popup.add(new AbstractAction("Flip Angle") {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    flipAngle();
//                }
//            });
     QAction* arcAction = new QAction(tr("Flip Angle"), this);
     lineType->addAction(arcAction);
     connect(arcAction, SIGNAL(triggered()), this, SLOT(flipAngle()));
    }
#if 1 // TODO:
//    if ((blockName!=("")) && (InstanceManager::layoutBlockManagerInstance().isAdvancedRoutingEnabled()))
    if ((blockName!=("")) && layoutEditor->layoutBlockManager->isAdvancedRoutingEnabled())
    {
     TSAbstractAction* act;
     popup->addAction(act = new TSAbstractAction(tr("View Block Routing"), this));
//     {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                AbstractAction*  routeTableAction = new  LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
//                routeTableAction.actionPerformed(e);
//            }
//        });
//      QAction* routeTableAction = new QAction(tr("ViewBlockRouting"),this);
//      popup->addAction(routeTableAction);
     connect(act, SIGNAL(triggered()), act, SLOT(actionPerformed()));
    }
#endif
    //popup.show(e.getComponent(), e.getX(), e.getY());
    popup->exec(QCursor::pos());
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

void TrackSegment::changeType(int choice)
{
 switch (choice)
 {
    case 0 :    setArc(false);
                setAngle(0.0);
                setCircle(false);
                break;
    case 1 :    setArc(true);
                setAngle(90.0);
                setCircle(true);
                break;
    case 2 :    setArc(true);
                setAngle(90.0);
                setCircle(false);
                break;
    default : break;
 }
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
 //layoutEditor->repaint();
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
        if (!blockName.equals(blockNameField.getText().trim()) ) {
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
        if ( !blockName.equals(blockNameField.getText().trim()) ) {
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
      result = center; //new QPointF.Double(centreX, centreY);
  }
  else if (isArc())
  {
      //center = MathUtil.midPoint(getBounds());
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
//   g2.draw(new Line2D.Double(getCoords(t->getConnect1(),t.getType1()), getCoords(t->getConnect2(),t.getType2())));
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
  //g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
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
     // Circle - Compute rectangle required by Arc2D.Double
     setCW(radius * 2.0);
     setCH(radius * 2.0);
     setCX(getCentreX()-(radius));
     setCY(getCentreY()-(radius));
    }
    else
    {
     // Elipse - Round start angle to the closest multiple of 90
     setStartAdj(qRound(getStartAdj() / 90.0) * 90.0);
     // Elipse - Compute rectangle required by Arc2D.Double
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
/*protected*/ void TrackSegment::draw1(EditScene* g2, bool isMain, bool isBlock) {
    if (!isBlock && isDashed() && getLayoutBlock() != nullptr) {
        // Skip the dashed rail layer, the block layer will display the dashed track
        // This removes random rail fragments from between the block dashes
        return;
    }
#if 0
    QColor color;
    if (isMain == mainline) {
        if (isBlock) {
            color = setColorForTrackBlock(g2, getLayoutBlock());
        }
        if (isArc()) {
            calculateTrackSegmentAngle();
//            g2.draw(new Arc2D.Double(getCX(), getCY(), getCW(), getCH(), getStartAdj(), getTmpAngle(), Arc2D.OPEN));
            QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
            lineItem->setStartAngle(getStartAdj()*16);
            lineItem->setSpanAngle(getTmpAngle()*16);
            lineItem->setPen(QPen(QColor(color),layoutEditor->trackWidth));
            item = lineItem;
            g2->addItem(item);

            trackRedrawn();
        }
        else if (isBezier()) {
            QPointF pt1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF pt2 = LayoutEditor::getCoords(getConnect2(), getType2());

            int cnt = bezierControlPoints.size();
            QVector<QPointF> points = Qvector<QPointF>(cnt + 2);
            points.replace(0, pt1);
            for (int idx = 0; idx < cnt; idx++) {
                points.replace(idx + 1, bezierControlPoints.at(idx));
            }
            points[cnt + 1] = pt2;

            MathUtil::drawBezier(g2, points);
        } else {
            QPointF end1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF end2 = LayoutEditor::getCoords(getConnect2(), getType2());

            //g2.draw(new Line2D.Double(end1, end2));
            QGraphicsPathItem* lineItem = new QGraphicsPathItem()
        }
    }
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::draw2(EditScene* g2, bool isMain, float railDisplacement) {
    if (isDashed() && getLayoutBlock() != nullptr) {
        // Skip the dashed rail layer, the block layer will display the dashed track
        // This removes random rail fragments from between the block dashes
        return;
    }
#if 0
    if (isMain == mainline) {
        if (isArc()) {
            calculateTrackSegmentAngle();
            Rectangle2D cRectangle2D = new Rectangle2D.Double(
                    getCX(), getCY(), getCW(), getCH());
            Rectangle2D cLeftRectangle2D = MathUtil.inset(cRectangle2D, -railDisplacement);
            double startAdj = getStartAdj(), tmpAngle = getTmpAngle();
            g2.draw(new Arc2D.Double(
                    cLeftRectangle2D.getX(),
                    cLeftRectangle2D.getY(),
                    cLeftRectangle2D.getWidth(),
                    cLeftRectangle2D.getHeight(),
                    startAdj, tmpAngle, Arc2D.OPEN));
            Rectangle2D cLRightRectangle2D = MathUtil.inset(cRectangle2D, +railDisplacement);
            g2.draw(new Arc2D.Double(
                    cLRightRectangle2D.getX(),
                    cLRightRectangle2D.getY(),
                    cLRightRectangle2D.getWidth(),
                    cLRightRectangle2D.getHeight(),
                    startAdj, tmpAngle, Arc2D.OPEN));
            trackRedrawn();
        } else if (isBezier()) {
            QPointF pt1 = LayoutEditor.getCoords(getConnect1(), getType1());
            QPointF pt2 = LayoutEditor.getCoords(getConnect2(), getType2());

            int cnt = bezierControlPoints.size();
            QPointF[] points = new QPointF[cnt + 2];
            points[0] = pt1;
            for (int idx = 0; idx < cnt; idx++) {
                points[idx + 1] = bezierControlPoints.get(idx);
            }
            points[cnt + 1] = pt2;

            MathUtil.drawBezier(g2, points, -railDisplacement);
            MathUtil.drawBezier(g2, points, +railDisplacement);
        } else {
            QPointF end1 = LayoutEditor.getCoords(getConnect1(), getType1());
            QPointF end2 = LayoutEditor.getCoords(getConnect2(), getType2());

            QPointF delta = MathUtil.subtract(end2, end1);
            QPointF vector = MathUtil.normalize(delta, railDisplacement);
            vector = MathUtil.orthogonal(vector);

            QPointF ep1L = MathUtil.add(end1, vector);
            QPointF ep2L = MathUtil.add(end2, vector);
            g2.draw(new Line2D.Double(ep1L, ep2L));

            QPointF ep1R = MathUtil.subtract(end1, vector);
            QPointF ep2R = MathUtil.subtract(end2, vector);
            g2.draw(new Line2D.Double(ep1R, ep2R));
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
            g2.draw(new Line2D.Double(circleCenterPoint, ep1));
            g2.draw(new Line2D.Double(circleCenterPoint, ep2));
            // Draw a circle and square at the circles centre, that
            // allows the user to change the angle by dragging the mouse.
            g2.draw(layoutEditor.trackEditControlCircleAt(circleCenterPoint));
            g2.draw(layoutEditor.trackEditControlRectAt(circleCenterPoint));
        } else if (isBezier()) {
            //draw construction lines and control circles
            QPointF lastPt = ep1;
            for (QPointF bcp : bezierControlPoints) {
                g2.draw(new Line2D.Double(lastPt, bcp));
                lastPt = bcp;
                g2.draw(layoutEditor.trackEditControlRectAt(bcp));
            }
            g2.draw(new Line2D.Double(lastPt, ep2));
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
  //g2.draw(new Arc2D.Double(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
  lineItem->setStartAngle(getStartAdj()*16);
  lineItem->setSpanAngle(getTmpAngle()*16);
  lineItem->setPen(QPen(QColor(color),editor->trackWidth));
  item = lineItem;
  g2->addItem(item);
 } else
 {
  //g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
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
 //g2.draw(new Ellipse2D.Double (cX-SIZE2, cY-SIZE2, SIZE2+SIZE2, SIZE2+SIZE2));
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
  //g2.draw(new Line2D.Double(getCoords(t.getConnect1(),t.getType1()), getCoords(t.getConnect2(),t.getType2())));
  //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()), getCoords(t->getConnect2(),t->getType2())),QPen(color,1));
  if(!editor->hideTrackSegmentConstructionLines->isChecked())
  {
   QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()), LayoutEditor::getCoords(getConnect2(),getType2())));
   item->setPen(QPen(color,1));
   group->addToGroup(item);
  }
  if (getCircle())
  {
   //g2.draw(new Line2D.Double();
   //g2->addLine(QLineF(getCoords(t->getConnect1(),t->getType1()),  QPointF(t->getCentreX(),t->getCentreY())),QPen(color,trackWidth));
   if(!editor->hideTrackSegmentConstructionLines->isChecked())
   {
    QGraphicsLineItem* item1 = new QGraphicsLineItem(QLineF(LayoutEditor::getCoords(getConnect1(),getType1()),  QPointF(getCentreX(),getCentreY())));
    item1->setPen(QPen(color,1));
    group->addToGroup(item1);
    //g2.draw(new Line2D.Double(getCoords(t.getConnect2(),t.getType2()), new QPointF.Double(t.getCentreX(),t.getCentreY())));
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
//    g2.draw(new Rectangle2D.Double (pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2));
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

