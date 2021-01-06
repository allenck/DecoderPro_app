#include "tracksegment.h"
//#include "edittracksegmentdlg.h"
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
#include <QAction>
//#include "layouttrackeditors.h"
#include "quickpromptutil.h"
#include <climits>
#include "path.h"
#include "layouttrackdrawingoptions.h"
#include <QApplication>
#include <QToolTip>
#include "tracksegmenteditor.h"
#include "layoutblock.h"

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
TrackSegment::TrackSegment(QString id, LayoutTrack *c1, int t1, LayoutTrack *c2, int t2, bool dash, bool main, LayoutEditor* layoutEditor)
 : LayoutTrack(id, QPointF(), layoutEditor)
{
 init(id);
 this->layoutEditor = layoutEditor;
 // validate input
 if ( (c1==NULL) || (c2==NULL) )
 {
  log->error("Invalid object in TrackSegment constructor call - "+id);
 }
 if (isConnectionHitType(t1))
 {
     connect1 = c1;
     type1 = t1;
 } else {
     log->error("Invalid connect type 1 ('" + QString::number(t1) + "') in TrackSegment constructor - " + id);
 }
 if (isConnectionHitType(t2)) {
     connect2 = c2;
     type2 = t2;
 } else {
     log->error("Invalid connect type 2 ('" + QString::number(t2) + "') in TrackSegment constructor - " + id);
 }
 dashed = dash;
 mainline = main;

 arc = false;
 flip = false;

 angle = 0.0;
 circle = false;
 bezier = false;
 setupDefaultBumperSizes(layoutEditor);

 editor = new TrackSegmentEditor(layoutEditor);

}

// alternate constructor for loading layout editor panels
/*public*/
TrackSegment::TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor* layoutEditor)
 : LayoutTrack(id, QPointF(), layoutEditor)
{
 init(id);
 this->layoutEditor = layoutEditor;

 tConnect1Name = c1Name;
 type1 = t1;
 tConnect2Name = c2Name;
 type2 = t2;

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
 itemMain = nullptr;
// circleItem = NULL;
// trackOval = NULL;
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
 mainlineCheckBoxMenuItem = new QAction(tr("Mainline"),this);
 mainlineCheckBoxMenuItem->setCheckable(true);
 hiddenCheckBoxMenuItem = new QAction(tr("Hidden"),this);
 hiddenCheckBoxMenuItem->setCheckable(true);
 dashedCheckBoxMenuItem = new QAction(tr("Dashed"));
 dashedCheckBoxMenuItem->setCheckable(true);
 flippedCheckBoxMenuItem = new QAction(tr("Flip"));
 flippedCheckBoxMenuItem->setCheckable(true);
}

/**
 * Get debugging string for the TrackSegment.
 *
 * @return text showing id and connections of this segment
 */
//@Override
/*public*/ QString TrackSegment::toString() {
    return "TrackSegment " + getName()
            + " c1:{" + getConnect1Name() + " (" + QString::number(type1) + "},"
            + " c2:{" + getConnect2Name() + " (" + QString::number(type2) + "}";

}

/**
 * Accessor methods
*/
/*public*/ QString TrackSegment::getID()
{
 return ident;
}

/*public*/ QString TrackSegment::getBlockName() {
 QString result = QString();
 if (namedLayoutBlock != nullptr) {
     result = namedLayoutBlock->getName();
 }
 return ((result == nullptr) ? "" : result);
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

/*protected*/ void TrackSegment::setNewConnect1(LayoutTrack* connectTrack, int connectionType) {
    connect1 = connectTrack;
    type1 = connectionType;

}

/*protected*/ void TrackSegment::setNewConnect2(LayoutTrack *connectTrack, int connectionType) {
    connect2 = connectTrack;
    type2 = connectionType;
}

/**
 * replace old track connection with new track connection
 *
 * @param oldTrack the old track connection
 * @param newTrack the new track connection
 * @return true if successful
 */
/*public*/ bool TrackSegment::replaceTrackConnection(/*@CheckForNull*/ LayoutTrack* oldTrack, /*@CheckForNull*/ LayoutTrack* newTrack, int newType) {
    bool result = false; // assume failure (pessimist!)
    // trying to replace old track with null?
    if (newTrack == nullptr) {
        // (yes) remove old connection
        if (oldTrack != nullptr) {
            result = true;  // assume success (optimist!)
            if (connect1 == oldTrack) {
                connect1 = nullptr;
                type1 = NONE;
            } else if (connect2 == oldTrack) {
                connect2 = nullptr;
                type2 = NONE;
            } else {
                log->error("Attempt to remove invalid track connection");
                result = false;
            }
        } else {
            log->error("Can't replace null track connection with null");
            result = false;
        }
    } else // already connected to newTrack?
    if ((connect1 != newTrack) && (connect2 != newTrack)) {
        // (no) find a connection we can connect to
        result = true;  // assume success (optimist!)
        if (connect1 == oldTrack) {
            connect1 = newTrack;
            type1 = newType;
        } else if (connect2 == oldTrack) {
            connect2 = newTrack;
            type2 = newType;
        } else {
            log->error("Attempt to replace invalid track connection");
            result = false;
        }
    }
    return result;
}

/**
 * @return true if track segment should be drawn dashed
 */
/*public*/ bool TrackSegment::isDashed() {
    return dashed;
}

/*public*/ void TrackSegment::setDashed(bool dash) {
 if (dashed != dash) {
     dashed = dash;
     layoutEditor->redrawPanel();
     layoutEditor->setDirty();
 }
}

/**
 * @return true if track segment is a main line
 */
//@Override
/*public*/ bool TrackSegment::isMainline() {
    return mainline;
}

/*public*/ void TrackSegment::setMainline(bool main) {
 if (mainline != main) {
     mainline = main;
     layoutEditor->redrawPanel();
     layoutEditor->setDirty();
 }
}

/**
 * @return true if track segment is an arc
 */
/*public*/ bool TrackSegment::isArc() {
    return arc;
}

/*public*/ void TrackSegment::setArc(bool boo) {
 if (arc != boo) {
     arc = boo;
     if (arc) {
         bezier = false;
         hideConstructionLines(SHOWCON);
     }
     changed = true;
 }
}

/**
 * @return true if track segment is circle
 */
/*public*/ bool TrackSegment::isCircle() {
    return circle;
}

/*public*/ void
TrackSegment::setCircle(bool boo) {
 if (circle != boo) {
     circle = boo;
     if (circle) {
         bezier = false;
         hideConstructionLines(SHOWCON);
     }
     changed = true;
 }
}

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

/*public*/ void TrackSegment::setAngle(double x)
{
 angle = MathUtil::pin(x, 0.0, 180.0);
 changed = true;
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

/*public*/ LayoutBlock*
TrackSegment::getLayoutBlock()
{
 return (namedLayoutBlock != nullptr) ? namedLayoutBlock->getBean() : nullptr;
}

/*public*/ QString TrackSegment::getConnect1Name() {return getConnectName(connect1,type1);}
/*public*/ QString TrackSegment::getConnect2Name() {return getConnectName(connect2,type2);}

/*private*/ QString TrackSegment::getConnectName(/*@Nullable*/ LayoutTrack* layoutTrack, int /*type*/) {
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
/*public*/ LayoutTrack* TrackSegment::getConnection(int /*connectionType*/) throw (JmriException) {
    // nothing to see here, move along
 throw JmriException("Use getConnect1() or getConnect2() instead.");
}

/**
 * {@inheritDoc}
 * <p>
 * This implementation does nothing because {@link #setNewConnect1} and
 * {@link #setNewConnect2} should be used instead.
 */
// only implemented here to suppress "does not override abstract method " error in compiler
//@Override
/*public*/ void TrackSegment::setConnection(int /*connectionType*/, /*@Nullable*/ LayoutTrack* /*o*/, int /*type*/) throw (JmriException) {
    // nothing to see here, move along
 throw JmriException("Use setConnect1() or setConnect2() instead.");
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

/*public*/ QList<QPointF> TrackSegment::getBezierControlPoints() {
        return bezierControlPoints;
    }


/**
 * Set up a Layout Block for a Track Segment.
 */
//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
/*public*/ void TrackSegment::setLayoutBlock(/*@CheckForNull*/ LayoutBlock* newLayoutBlock) {
    LayoutBlock* layoutBlock = getLayoutBlock();
    if (layoutBlock != newLayoutBlock) {
        // block has changed, if old block exists, decrement use
        if (layoutBlock != nullptr) {
            layoutBlock->decrementUse();
        }
        if (newLayoutBlock != nullptr) {
            namedLayoutBlock = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(newLayoutBlock->getUserName(), newLayoutBlock);
        } else {
            namedLayoutBlock = nullptr;
        }
    }
}

//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
/*public*/ void TrackSegment::setLayoutBlockByName(/*@CheckForNull*/ QString name) {
    if ((name != nullptr) && !name.isEmpty()) {
        LayoutBlock* b = layoutEditor->provideLayoutBlock(name);
        namedLayoutBlock = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(b->getUserName(), b);
    } else {
        namedLayoutBlock = nullptr;
    }
}

/*
 * non-accessor methods
 */
/**
 * scale this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to scale X coordinates
 * @param yFactor the amount to scale Y coordinates
 */
//@Override
/*public*/ void TrackSegment::scaleCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    center = MathUtil::multiply(center, factor);
    if (isBezier()) {
        for (QPointF p : bezierControlPoints) {
          //p.setLocation(MathUtil::multiply(p, factor));
         p = MathUtil::multiply(p, factor);
        }
    }
}

/**
 * translate this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to translate X coordinates
 * @param yFactor the amount to translate Y coordinates
 */
//@Override
/*public*/ void TrackSegment::translateCoords(double xFactor, double yFactor) {
    setCoordsCenter(MathUtil::add(center, QPointF(xFactor, yFactor)));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegment::rotateCoords(double angleDEG) {
    if (isBezier()) {
        for (QPointF p : bezierControlPoints) {
            //p.setLocation(MathUtil.rotateDEG(p, center, angleDEG));
         p= MathUtil::rotateDEG(p, center, angleDEG);
        }
    }
}

/**
 * set center coordinates
 *
 * @param newCenterPoint the coordinates to set
 */
//@Override
/*public*/ void TrackSegment::setCoordsCenter(/*@Nonnull*/ QPointF newCenterPoint) {
    if (center != newCenterPoint) {
        if (isBezier()) {
            QPointF delta = MathUtil::subtract(newCenterPoint, center);
            for (QPointF p : bezierControlPoints) {
//           p.setLocation(MathUtil.add(p, delta));
             p = MathUtil::add(p, delta);
            }
        }
        center = newCenterPoint;
    }
}

/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
//@Override
/*public*/ void TrackSegment::setObjects(LayoutEditor* p)
{
  LayoutBlock* lb;
  if (!tLayoutBlockName.isEmpty()) {
      lb = p->provideLayoutBlock(tLayoutBlockName);
      if (lb != nullptr) {
          namedLayoutBlock = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(lb->getUserName(), lb);
          lb->incrementUse();
      } else {
          log->error(tr("bad blockname '%1' in tracksegment %2").arg(tLayoutBlockName).arg(getName()));
          namedLayoutBlock = nullptr;
      }
      tLayoutBlockName = nullptr; //release this memory
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

/*protected*/ void TrackSegment::updateBlockInfo()
{
  LayoutBlock* layoutBlock = getLayoutBlock();
  if (layoutBlock != nullptr) {
      layoutBlock->updatePaths();
  }
  LayoutBlock* b1 = getBlock(connect1, type1);
  if ((b1 != nullptr) && (b1 != layoutBlock)) {
      b1->updatePaths();
  }
  LayoutBlock* b2 = getBlock(connect2, type2);
  if ((b2 != nullptr) && (b2 != layoutBlock) && (b2 != b1)) {
      b2->updatePaths();
  }

  getConnect1()->reCheckBlockBoundary();
  getConnect2()->reCheckBlockBoundary();
}

/*private*/ LayoutBlock* TrackSegment::getBlock (LayoutTrack* connect, int type)
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
/*protected*/ int TrackSegment::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    int result = NONE;  // assume point not on connection

    if (!requireUnconnected) {
        //note: optimization here: instead of creating rectangles for all the
        // points to check below, we create a rectangle for the test point
        // and test if the points below are in that rectangle instead.
        QRectF r = layoutEditor->trackControlCircleRectAt(hitPoint);
        QPointF p, minPoint = MathUtil::zeroPoint2D;

        double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
        double distance, minDistance = std::numeric_limits<double>::infinity();

        if (isCircle()) {
            p = getCoordsCenterCircle();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = TRACK_CIRCLE_CENTRE;
            }
        } else if (isBezier()) {
            // hit testing for the control points
            for (int index = 0; index < bezierControlPoints.size(); index++) {
                p = bezierControlPoints.at(index);
                distance = MathUtil::distance(p, hitPoint);
                if (distance < minDistance) {
                    minDistance = distance;
                    minPoint = p;
                    result = BEZIER_CONTROL_POINT_OFFSET_MIN + index;
                }
            }
        }
        if ((useRectangles && !r.contains(minPoint))
                || (!useRectangles && (minDistance > circleRadius))) {
            result = NONE;
        }
        if (result == NONE) {
            if (r.contains(getCentreSeg())) {
                result = TRACK;
            }
        }
    }
    return result;
}   // findHitPointType

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::drawDecorations(EditScene* g2)
{
//    if (getName() == ("T9")) {
//        log->debug("STOP");
//    }

 invalidateItem(g2, decorationItems);

 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

    // get end points and calculate start/stop angles (in radians)
    QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
    QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
    QPointF p1, p2, p3, p4, p5, p6, p7;
    QPointF p1P = ep1, p2P = ep2, p3P, p4P, p5P, p6P, p7P;
    double startAngleRAD, stopAngleRAD;

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
                offset = drawArrow(g2, ep1, M_PI + startAngleRAD, false, offset, stroke, itemGroup);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep1, M_PI + startAngleRAD, true, offset, stroke, itemGroup);
            }
        }
        offset = 1;
        if (arrowEndStop) {
            if (arrowDirIn) {
                offset = drawArrow(g2, ep2, stopAngleRAD, false, offset, stroke, itemGroup);
            }
            if (arrowDirOut) {
                offset = drawArrow(g2, ep2, stopAngleRAD, true, offset, stroke, itemGroup);
            }
        }
    }   // arrow decoration

    //
    //  bridge decorations
    //
    if (bridgeSideLeft || bridgeSideRight)
    {
        float halfWidth = bridgeDeckWidth / 2.0;

//        g2.setStroke(new BasicStroke(bridgeLineWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
//        g2.setColor(bridgeColor);
        QPen stroke = QPen(bridgeColor, bridgeLineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);

        if (isArc()) {
            calculateTrackSegmentAngle();
            QRectF cRectangle2D =  QRectF(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (bridgeSideLeft) {
                QRectF cLeftRectangle2D = MathUtil::inset(cRectangle2D, -halfWidth);
//                g2.draw(new Arc2D(
//                        cLeftRectangle2D.getX(),
//                        cLeftRectangle2D.getY(),
//                        cLeftRectangle2D.getWidth(),
//                        cLeftRectangle2D.getHeight(),
//                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
                QGraphicsArcItem* arcItem = new QGraphicsArcItem(cLeftRectangle2D.x(),cLeftRectangle2D.y(),cLeftRectangle2D.width(),cLeftRectangle2D.height());
                arcItem->setStartAngle(startAngleDEG * 16);
                arcItem->setSpanAngle(extentAngleDEG * 16);
                arcItem->setPen(stroke);
                itemGroup->addToGroup(arcItem);
            }
            if (bridgeSideRight) {
                QRectF cLRightRectangle2D = MathUtil::inset(cRectangle2D, +halfWidth);
//                g2.draw(new Arc2D(
//                        cLRightRectangle2D.getX(),
//                        cLRightRectangle2D.getY(),
//                        cLRightRectangle2D.getWidth(),
//                        cLRightRectangle2D.getHeight(),
//                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
                QGraphicsArcItem* arcItem = new QGraphicsArcItem(cLRightRectangle2D.x(),cLRightRectangle2D.y(),cLRightRectangle2D.width(),cLRightRectangle2D.height());
                arcItem->setStartAngle(startAngleDEG * 16);
                arcItem->setSpanAngle(extentAngleDEG * 16);
                arcItem->setPen(stroke);
                itemGroup->addToGroup(arcItem);
            }
            trackRedrawn();
        } else if (isBezier()) {
            int cnt = bezierControlPoints.size() + 2;
            QVector<QPointF> points = QVector<QPointF>(cnt);
            points.replace(0, ep1);
            for (int idx = 0; idx < cnt - 2; idx++) {
                points.replace(idx + 1, bezierControlPoints.at(idx));
            }
            points.replace(cnt - 1, ep2);

            if (bridgeSideLeft) {
//                MathUtil::drawBezier(g2, points, -halfWidth);
             QPainterPath path = MathUtil::drawBezier(points, -halfWidth);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(stroke);
             itemGroup->addToGroup(pathItem);
            }
            if (bridgeSideRight) {
                //MathUtil::drawBezier(g2, points, +halfWidth);
             QPainterPath path = MathUtil::drawBezier(points, +halfWidth);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(stroke);
             itemGroup->addToGroup(pathItem);
            }
        } else {
            QPointF delta = MathUtil::subtract(ep2, ep1);
            QPointF vector = MathUtil::normalize(delta, halfWidth);
            vector = MathUtil::orthogonal(vector);

            if (bridgeSideLeft) {
                QPointF ep1L = MathUtil::add(ep1, vector);
                QPointF ep2L = MathUtil::add(ep2, vector);
                //g2.draw(new Line2D(ep1L, ep2L));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1L.x(), ep1L.y(), ep2L.x(), ep2L.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
            if (bridgeSideRight) {
                QPointF ep1R = MathUtil::subtract(ep1, vector);
                QPointF ep2R = MathUtil::subtract(ep2, vector);
                //g2.draw(new Line2D(ep1R, ep2R));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1R.x(), ep1R.y(), ep2R.x(), ep2R.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
        }   // if isArc() {} else if isBezier() {} else...

        if (bridgeHasEntry) {
            if (bridgeSideRight) {
                p1 = QPointF(-bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = QPointF(0.0, -halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                //g2.draw(new Line2D(p1P, p2P));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(p1P.x(), p1P.y(), p2P.x(), p2P.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
            if (bridgeSideLeft) {
                p1 = QPointF(-bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = QPointF(0.0, +halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                //g2.draw(new Line2D(p1P, p2P));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(p1P.x(), p1P.y(), p2P.x(), p2P.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
        }
        if (bridgeHasExit) {
            if (bridgeSideRight) {
                p1 = QPointF(+bridgeApproachWidth, -bridgeApproachWidth - halfWidth);
                p2 = QPointF(0.0, -halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                //g2.draw(new Line2D(p1P, p2P));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(p1P.x(), p1P.y(), p2P.x(), p2P.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
            if (bridgeSideLeft) {
                p1 = QPointF(+bridgeApproachWidth, +bridgeApproachWidth + halfWidth);
                p2 = QPointF(0.0, +halfWidth);
                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                //g2.draw(new Line2D(p1P, p2P));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(p1P.x(), p1P.y(), p2P.x(), p2P.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
        }
    }   // if (bridgeValue != null)

    //
    //  end bumper decorations
    //
    if (bumperEndStart || bumperEndStop) {
//        if (getName() == ("T15")) {
//            log->debug("STOP");
//        }
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
        itemGroup->addToGroup(line);
    }   // if (bumperEndStart || bumperEndStop)

    //
    //  tunnel decorations
    //
    if (tunnelSideRight || tunnelSideLeft) {
        float halfWidth = tunnelFloorWidth / 2.F;
//        g2.setStroke(new BasicStroke(tunnelLineWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 10.F,
//                new float[]{6.F, 4.F}, 0));
//        g2.setColor(tunnelColor);
        QVector<qreal> dashArray = QVector<qreal>() << 6.0<< 4.0;
        QPen stroke = QPen(tunnelColor, bridgeLineWidth, Qt::DashLine, Qt::FlatCap, Qt::MiterJoin);
        stroke.setDashOffset(10.0);
        stroke.setDashPattern(dashArray);

        if (isArc()) {
            calculateTrackSegmentAngle();
            QRectF cRectangle2D = QRectF(
                    getCX(), getCY(), getCW(), getCH());
            double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
            if (tunnelSideRight) {
                QRectF cLeftRectangle2D = MathUtil::inset(cRectangle2D, -halfWidth);
//                g2.draw(new Arc2D(
//                        cLeftRectangle2D.getX(),
//                        cLeftRectangle2D.getY(),
//                        cLeftRectangle2D.getWidth(),
//                        cLeftRectangle2D.getHeight(),
//                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
                QGraphicsArcItem* arcItem = new QGraphicsArcItem(cLeftRectangle2D.x(),cLeftRectangle2D.y(),cLeftRectangle2D.width(),cLeftRectangle2D.height());
                arcItem->setStartAngle(startAngleDEG * 16);
                arcItem->setSpanAngle(extentAngleDEG * 16);
                arcItem->setPen(stroke);
                itemGroup->addToGroup(arcItem);
            }
            if (tunnelSideLeft) {
                QRectF cLRightRectangle2D = MathUtil::inset(cRectangle2D, +halfWidth);
//                g2.draw(new Arc2D(
//                        cLRightRectangle2D.getX(),
//                        cLRightRectangle2D.getY(),
//                        cLRightRectangle2D.getWidth(),
//                        cLRightRectangle2D.getHeight(),
//                        startAngleDEG, extentAngleDEG, Arc2D.OPEN));
                QGraphicsArcItem* arcItem = new QGraphicsArcItem(cLRightRectangle2D.x(),cLRightRectangle2D.y(),cLRightRectangle2D.width(),cLRightRectangle2D.height());
                arcItem->setStartAngle(startAngleDEG * 16);
                arcItem->setSpanAngle(extentAngleDEG * 16);
                arcItem->setPen(stroke);
                itemGroup->addToGroup(arcItem);
            }
            trackRedrawn();
        } else if (isBezier()) {
            int cnt = bezierControlPoints.size() + 2;
            QVector<QPointF> points = QVector<QPointF>(cnt);
            points.replace(0, ep1);
            for (int idx = 0; idx < cnt - 2; idx++) {
                points.replace(idx + 1, bezierControlPoints.at(idx));
            }
            points.replace(cnt - 1, ep2);


            if (tunnelSideRight) {
//                MathUtil::drawBezier(g2, points, -halfWidth);
             QPainterPath path = MathUtil::drawBezier(points, -halfWidth);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(stroke);
             itemGroup->addToGroup(pathItem);
            }
            if (tunnelSideLeft) {
//                MathUtil::drawBezier(g2, points, +halfWidth);
             QPainterPath path = MathUtil::drawBezier(points, +halfWidth);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(stroke);
             itemGroup->addToGroup(pathItem);
            }
        } else {
            QPointF delta = MathUtil::subtract(ep2, ep1);
            QPointF vector = MathUtil::normalize(delta, halfWidth);
            vector = MathUtil::orthogonal(vector);

            if (tunnelSideRight) {
                QPointF ep1L = MathUtil::add(ep1, vector);
                QPointF ep2L = MathUtil::add(ep2, vector);
//                g2.draw(new Line2D(ep1L, ep2L));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1L.x(), ep1L.y(), ep2L.x(), ep2L.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
            if (tunnelSideLeft) {
                QPointF ep1R = MathUtil::subtract(ep1, vector);
                QPointF ep2R = MathUtil::subtract(ep2, vector);
//                g2.draw(new Line2D(ep1R, ep2R));
                QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1R.x(), ep1R.y(), ep2R.x(), ep2R.y());
                lineItem->setPen(stroke);
                itemGroup->addToGroup(lineItem);
            }
        }   // if isArc() {} else if isBezier() {} else...

//        g2.setStroke(new BasicStroke(tunnelLineWidth,
//                BasicStroke.CAP_BUTT, BasicStroke.JOIN_MITER, 1.F));
//        g2.setColor(tunnelColor);
        stroke = QPen(tunnelColor, tunnelLineWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);

        double halfEntranceWidth = tunnelEntranceWidth / 2.0;
        double halfFloorWidth = tunnelFloorWidth / 2.0;
        double halfDiffWidth = halfEntranceWidth - halfFloorWidth;

        if (tunnelHasEntry) {
            if (tunnelSideLeft) {
                p1 = QPointF(0.0, 0.0);
                p2 = QPointF(0.0, -halfFloorWidth);
                p3 = QPointF(0.0, -halfEntranceWidth);
                p5 = QPointF(-halfEntranceWidth - halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = QPointF(-halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = QPointF(-halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, startAngleRAD), ep1);

                QPainterPath path = QPainterPath();
                path.moveTo(p1P.x(), p1P.y());
                path.lineTo(p2P.x(), p2P.y());
                path.quadTo(p3P.x(), p3P.y(), p4P.x(), p4P.y());
                path.lineTo(p5P.x(), p5P.y());
                path.quadTo(p6P.x(), p6P.y(), p7P.x(), p7P.y());
                path.closeSubpath();
                //g2.fill(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(stroke);
                itemGroup->addToGroup(pathItem);
            }
            if (tunnelSideRight) {
                p1 = QPointF(0.0, 0.0);
                p2 = QPointF(0.0, +halfFloorWidth);
                p3 = QPointF(0.0, +halfEntranceWidth);
                p4 = QPointF(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth);
                p5 = QPointF(-halfEntranceWidth - halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = QPointF(-halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = QPointF(-halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, startAngleRAD), ep1);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, startAngleRAD), ep1);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, startAngleRAD), ep1);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, startAngleRAD), ep1);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, startAngleRAD), ep1);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, startAngleRAD), ep1);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, startAngleRAD), ep1);

                QPainterPath path = QPainterPath();
                path.moveTo(p1P.x(), p1P.y());
                path.lineTo(p2P.x(), p2P.y());
                path.quadTo(p3P.x(), p3P.y(), p4P.x(), p4P.y());
                path.lineTo(p5P.x(), p5P.y());
                path.quadTo(p6P.x(), p6P.y(), p7P.x(), p7P.y());
                path.closeSubpath();
                //g2.fill(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(stroke);
                itemGroup->addToGroup(pathItem);
            }
        }
        if (tunnelHasExit) {
            if (tunnelSideLeft) {
                p1 = QPointF(0.0, 0.0);
                p2 = QPointF(0.0, -halfFloorWidth);
                p3 = QPointF(0.0, -halfEntranceWidth);
                p4 = QPointF(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth);
                p5 = QPointF(halfEntranceWidth + halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p6 = QPointF(halfFloorWidth, -halfEntranceWidth + halfDiffWidth);
                p7 = QPointF(halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, stopAngleRAD), ep2);

                QPainterPath path = QPainterPath();
                path.moveTo(p1P.x(), p1P.y());
                path.lineTo(p2P.x(), p2P.y());
                path.quadTo(p3P.x(), p3P.y(), p4P.x(), p4P.y());
                path.lineTo(p5P.x(), p5P.y());
                path.quadTo(p6P.x(), p6P.y(), p7P.x(), p7P.y());
                path.closeSubpath();
                //g2.fill(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(stroke);
                itemGroup->addToGroup(pathItem);
            }
            if (tunnelSideRight) {
                p1 = QPointF(0.0, 0.0);
                p2 = QPointF(0.0, +halfFloorWidth);
                p3 = QPointF(0.0, +halfEntranceWidth);
                p4 = QPointF(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth);
                p5 = QPointF(halfEntranceWidth + halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p6 = QPointF(halfFloorWidth, +halfEntranceWidth - halfDiffWidth);
                p7 = QPointF(halfDiffWidth, 0.0);

                p1P = MathUtil::add(MathUtil::rotateRAD(p1, stopAngleRAD), ep2);
                p2P = MathUtil::add(MathUtil::rotateRAD(p2, stopAngleRAD), ep2);
                p3P = MathUtil::add(MathUtil::rotateRAD(p3, stopAngleRAD), ep2);
                p4P = MathUtil::add(MathUtil::rotateRAD(p4, stopAngleRAD), ep2);
                p5P = MathUtil::add(MathUtil::rotateRAD(p5, stopAngleRAD), ep2);
                p6P = MathUtil::add(MathUtil::rotateRAD(p6, stopAngleRAD), ep2);
                p7P = MathUtil::add(MathUtil::rotateRAD(p7, stopAngleRAD), ep2);

                QPainterPath path = QPainterPath();
                path.moveTo(p1P.x(), p1P.y());
                path.lineTo(p2P.x(), p2P.y());
                path.quadTo(p3P.x(), p3P.y(), p4P.x(), p4P.y());
                path.lineTo(p5P.x(), p5P.y());
                path.quadTo(p6P.x(), p6P.y(), p7P.x(), p7P.y());
                path.closeSubpath();
                //g2.fill(path);
                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                pathItem->setPen(stroke);
                itemGroup->addToGroup(pathItem);
            }
        }
    }   // if (tunnelValue != null)

    decorationItems= itemGroup;
    g2->addItem(decorationItems);

}   // drawDecorations

/*private*/ int TrackSegment::drawArrow(
        EditScene* g2,
        QPointF ep,
        double angleRAD,
        bool dirOut,
        int offset, QPen stroke, QGraphicsItemGroup* itemGroup)
{
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
    return offset;
}   // drawArrow

/**
 * Helper method, which adds "Set value" item to the menu. The value can be
 * optionally range-checked. Item will be appended at the end of the menu.
 *
 * @param menu       the target menu.
 * @param titleKey   bundle key for the menu title/dialog title
 * @param toolTipKey bundle key for the menu item tooltip
 * @param val        value getter
 * @param set        value setter
 * @param predicate  checking predicate, possibly null.
 */
/*private*/ void TrackSegment::addNumericMenuItem(/*@Nonnull*/ QMenu* menu,
        /*@Nonnull*/ QString titleKey, /*@Nonnull*/ QString toolTipKey,
        /*@Nonnull*/ Supplier<int> val,
        /*@Nonnull*/ Consumer<int> set,
        /*@CheckForNull*/ Predicate<int> predicate) {
    int oldVal = val.get();
    QAction* jmi;
    menu->addAction(jmi = new QAction(tr("%1").arg(
            (titleKey) + QString::number(oldVal)),this));
    jmi->setToolTip((toolTipKey));
    //jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
#if 0
    connect(jmi, &QAction::triggered, [=]{
        //prompt for lineWidth
        int newValue = QuickPromptUtil::promptForInteger(layoutEditor,
                /*Bundle.getMessage*/(titleKey),
                /*Bundle.getMessage*/(titleKey),
                //getting again, maybe something changed from the menu construction ?
                val.get(), predicate);
        set.accept(newValue);
        layoutEditor->repaint();
    });
#endif
}
#if 0
/**
 * Display popup menu for information and editing
 */
/*protected*/ QMenu* TrackSegment::showPopup(QGraphicsSceneMouseEvent* /*e*/)
{
 if (popupMenu != nullptr) {
     popupMenu->clear();
 } else {
     popupMenu = new QMenu();
 }

 QString info = tr("TrackSegment");
 if (isArc()) {
     if (isCircle()) {
         info = info + " (" + tr("Circle") + ")";
     } else {
         info = info + " (" + tr("Ellipse") + ")";
     }
 } else if (isBezier()) {
     info = info + " (" + tr("Bezier") + ")";
 } else {
     info = info + " (" + tr("Line") + ")";
 }

 QAction* jmi = popupMenu->addSection(tr("%1: ").arg(info) + getName());
 jmi->setEnabled(false);

 if (namedLayoutBlock == nullptr) {
     jmi = popupMenu->addSection(tr("No Block Set"));
 } else {
     jmi = popupMenu->addSection(tr(" %1: ").arg(tr("Block")) + getLayoutBlock()->getDisplayName());
 }
 jmi->setEnabled(false);

 // if there are any track connections
 QAction* act;

 if ((connect1 != nullptr) || (connect2 != nullptr)) {
     QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
     if (connect1 != nullptr)
     {
         connectionsMenu->addAction(act = new AbstractAction(tr(" %1: ").arg("1") + connect1->getName(), this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
                 LayoutEditorFindItems* lf = layoutEditor->getFinder();
                 LayoutTrack* lt = lf->findObjectByName(connect1->getName());
                 // this shouldn't ever be null... however...
                 if (lt != nullptr) {
                     layoutEditor->setSelectionRect(lt->getBounds());
                     lt->showPopup();
                 }
         });
     }
     if (connect2 != nullptr) {
         connectionsMenu->addAction(act =new AbstractAction(tr(" %1: ").arg("2") + connect2->getName(),this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
                 LayoutEditorFindItems* lf = layoutEditor->getFinder();
                 LayoutTrack* lt = lf->findObjectByName(connect2->getName());
                 // this shouldn't ever be null... however...
                 if (lt != nullptr) {
                     layoutEditor->setSelectionRect(lt->getBounds());
                     lt->showPopup();
                 }
         });
     }
     popupMenu->addMenu(connectionsMenu);
 }

 popupMenu->addSeparator(); //new JSeparator(JSeparator.HORIZONTAL));

 QActionGroup* trackTypeActGrp = new QActionGroup(this);
 popupMenu->addAction(mainlineCheckBoxMenuItem);
 trackTypeActGrp->addAction(mainlineCheckBoxMenuItem);
// mainlineCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(mainlineCheckBoxMenuItem, &QAction::triggered, [=]{
     setMainline(mainlineCheckBoxMenuItem->isChecked());
 });
 mainlineCheckBoxMenuItem->setToolTip(tr("Sets track segment type - check for mainline track, uncheck for side track."));
 connect(mainlineCheckBoxMenuItem, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), mainlineCheckBoxMenuItem->toolTip(), layoutEditor);
 });
 mainlineCheckBoxMenuItem->setChecked(mainline);

 popupMenu->addAction(hiddenCheckBoxMenuItem);
 trackTypeActGrp->addAction(hiddenCheckBoxMenuItem);
// hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(hiddenCheckBoxMenuItem, &QAction::triggered, [=]{
     setHidden(hiddenCheckBoxMenuItem->isChecked());
 });
 hiddenCheckBoxMenuItem->setToolTip(tr("Check this to hide the track when not in edit mode"));
 hiddenCheckBoxMenuItem->setChecked(hidden);
 connect(hiddenCheckBoxMenuItem, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), hiddenCheckBoxMenuItem->toolTip(), layoutEditor);
 });

 popupMenu->addAction(dashedCheckBoxMenuItem);
 trackTypeActGrp->addAction(dashedCheckBoxMenuItem);
// dashedCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(dashedCheckBoxMenuItem, &QAction::triggered, [=]{
     setDashed(dashedCheckBoxMenuItem->isChecked());
 });
 dashedCheckBoxMenuItem->setToolTip(tr("Sets track segment style - checked for dashed, unchecked for solid."));
 dashedCheckBoxMenuItem->setChecked(dashed);

 if (isArc()) {
     popupMenu->addAction(flippedCheckBoxMenuItem);
//     flippedCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
     connect(flippedCheckBoxMenuItem, &QAction::triggered, [=]{
         setFlip(flippedCheckBoxMenuItem->isChecked());
     });
    flippedCheckBoxMenuItem->setToolTip(tr("Check this move the center of the arc/circle to the other side of the track"));
     flippedCheckBoxMenuItem->setChecked(isFlip());
     connect(flippedCheckBoxMenuItem, &QAction::hovered, [=]{
         QToolTip::showText(QCursor::pos(), flippedCheckBoxMenuItem->toolTip(), layoutEditor);
     });
 }

 //
 // decorations menu
 //
 QMenu* decorationsMenu = new QMenu(tr("Decorations"));
 decorationsMenu->setToolTip(tr("Select this menu to change decoration settings for this track"));
 decorationsMenu->setToolTipsVisible(true);
 //
 // arrows menus
 //
 QMenu* arrowsMenu = new QMenu(tr("Arrows"));
 arrowsMenu->setToolTip(tr("Select this menu to change arrow decoration settings for this track"));
 decorationsMenu->addMenu(arrowsMenu);
 arrowsMenu->setToolTipsVisible(true);

 QMenu* arrowsCountMenu = new QMenu(tr("Style"));
 arrowsCountMenu->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 arrowsMenu->addMenu(arrowsCountMenu);
 arrowsMenu->setToolTipsVisible(true);

 QActionGroup* styleActionGroup = new QActionGroup(this);

 QAction* jcbmi = new QAction(tr("None"),this);
 jcbmi->setData(0);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(0);
 });
 jcbmi->setChecked(arrowStyle == 0);

 QIcon imageIcon = QIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle1.png").toString());
 jcbmi = new QAction(imageIcon, "1",this);
 jcbmi->setData(1);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(1);
 });
 jcbmi->setChecked(arrowStyle == 1);

 imageIcon = QIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle2.png").toString());
 jcbmi = new QAction(imageIcon, "2", this);
 jcbmi->setData(2);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(2);
 });
 jcbmi->setChecked(arrowStyle == 2);

 imageIcon = QIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle3.png").toString());
 jcbmi = new QAction(imageIcon, "3", this);
 jcbmi->setData(3);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 connect(mainlineCheckBoxMenuItem, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), mainlineCheckBoxMenuItem->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(3);
 });
 jcbmi->setChecked(arrowStyle == 3);

 imageIcon = QIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle4.png").toString());
 jcbmi = new QAction(imageIcon, "4", this);
 jcbmi->setData(4);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(4);
 });
 jcbmi->setChecked(arrowStyle == 4);

 imageIcon = QIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle5.png").toString());
 jcbmi = new QAction(imageIcon, "5", this);
 jcbmi->setData(5);
 jcbmi->setCheckable(true);
 styleActionGroup->addAction(jcbmi);
 arrowsCountMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowStyle(5);
 });
 jcbmi->setChecked(arrowStyle == 5);

 QMenu*arrowsEndMenu = new QMenu(tr("Which end"));
 arrowsEndMenu->setToolTip(tr("Select at which end(s) to add this decoration"));
 arrowsMenu->addMenu(arrowsEndMenu);

 QActionGroup* arrowEndActionGroup = new QActionGroup(this);
 jcbmi = new QAction(tr("None"),this);
 jcbmi->setData(0);
 jcbmi->setCheckable(true);
 arrowEndActionGroup->addAction(jcbmi);
 arrowsEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.add(ActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowEndStart(false);
     setArrowEndStop(false);
 });
 jcbmi->setChecked(!arrowEndStart && !arrowEndStop);
 jcbmi = new QAction(tr("Start"), this);
 jcbmi->setData(1);
 jcbmi->setCheckable(true);
 arrowEndActionGroup->addAction(jcbmi);
 arrowsEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the beginning of this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowEndStart(true);
     setArrowEndStop(false);
 });
 jcbmi->setChecked(arrowEndStart && !arrowEndStop);

 jcbmi = new QAction(tr("End"),this);
 jcbmi->setData(2);
 jcbmi->setCheckable(true);
 arrowEndActionGroup->addAction(jcbmi);
 arrowsEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the end of this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowEndStop(true);
     setArrowEndStart(false);
 });
 jcbmi->setChecked(!arrowEndStart && arrowEndStop);
 jcbmi = new QAction(tr("Both"), this);
 jcbmi->setData(3);
 jcbmi->setCheckable(true);
 arrowEndActionGroup->addAction(jcbmi);
 arrowsEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowEndStart(true);
     setArrowEndStop(true);
 });
 jcbmi->setChecked(arrowEndStart && arrowEndStop);

 QMenu* arrowsDirMenu = new QMenu(tr("Direction"));
 arrowsDirMenu->setToolTip(tr("Select the direction to point the arrows"));
 arrowsMenu->addMenu(arrowsDirMenu);
 arrowsMenu->setToolTipsVisible(true);

 QActionGroup* arrowDirectionActionGroup = new QActionGroup(this);
 jcbmi = new QAction(tr("None"), this);
 jcbmi->setData(0);
 jcbmi->setCheckable(true);
 arrowDirectionActionGroup->addAction(jcbmi);
 arrowsDirMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("DecorationNoneMenuItemToolTip"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowDirIn(false);
     setArrowDirOut(false);
 });
 jcbmi->setChecked(!arrowDirIn && !arrowDirOut);

 jcbmi = new QAction(tr("In"));
 jcbmi->setData(1);
 jcbmi->setCheckable(true);
 arrowDirectionActionGroup->addAction(jcbmi);
 arrowsDirMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to draw arrows pointing in"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowDirIn(true);
     setArrowDirOut(false);
 });
 jcbmi->setChecked(arrowDirIn && !arrowDirOut);

 jcbmi = new QAction(tr("Out"));
 jcbmi->setData(2);
 jcbmi->setCheckable(true);
 arrowDirectionActionGroup->addAction(jcbmi);
 arrowsDirMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to draw arrows pointing out"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowDirOut(true);
     setArrowDirIn(false);
 });
 jcbmi->setChecked(!arrowDirIn && arrowDirOut);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setData(3);
 jcbmi->setCheckable(true);
 arrowDirectionActionGroup->addAction(jcbmi);
 arrowsDirMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to draw arrow(s) pointing in and out"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setArrowDirIn(true);
     setArrowDirOut(true);
 });
 jcbmi->setChecked(arrowDirIn && arrowDirOut);

 arrowsMenu->addAction(jmi = new QAction(tr("Color"),this));

 jmi->setToolTip(tr("Select this to change the color of this decoration"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", arrowColor);
     if ((newColor.isValid()) && newColor != (arrowColor)) {
         setArrowColor(newColor);
     }
 });
// jmi->setForeground(arrowColor);
 jmi->setIcon(layoutEditor->getColourIcon(arrowColor));
// jmi->setBackground(ColorUtil::contrast(arrowColor));

 arrowsMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Line Width: ") + QString::number(arrowLineWidth)), this));
 jmi->setToolTip(tr("Select this to change the line width of this decoration"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for arrow line width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("Line Width"),
             tr("Line Width"),
             arrowLineWidth);
     setArrowLineWidth(newValue);
 });

 arrowsMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Length: ") + QString::number(arrowLength)),this));
 jmi->setToolTip(tr("Select this to change the length of this decoration"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for arrow length
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("Length"),
             tr("Length"),
             arrowLength);
     setArrowLength(newValue);
 });

 arrowsMenu->addAction(jmi =new QAction(tr("Space %1: ").arg(arrowGap), this));
 jmi->setToolTip(tr("Select this to change the space between multiple decorations"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for arrow gap
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("Space"),
             tr("Space"),
             arrowGap);
     setArrowGap(newValue);
 });

 //
 // bridge menus
 //
 QMenu* bridgeMenu = new QMenu(tr("Bridge"));
 decorationsMenu->setToolTip(tr("Select this menu to change bridge decoration settings for this track"));
 decorationsMenu->addMenu(bridgeMenu);
 decorationsMenu->setToolTipsVisible(true);

 QMenu* bridgeSideMenu = new QMenu(tr("Side"));
 bridgeSideMenu->setToolTip(tr("Select on which side(s) to add this decoration"));
 bridgeMenu->addMenu(bridgeSideMenu);
 bridgeSideMenu->setToolTipsVisible(true);

 QActionGroup* bridgeSideActionGroup = new QActionGroup(this);
 jcbmi = new QAction(tr("None"),this);
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeSideLeft(false);
     setBridgeSideRight(false);
 });
 jcbmi->setChecked(!bridgeSideLeft && !bridgeSideRight);

 jcbmi = new QAction(tr("Left"), this);
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
// jcbmi->setToolTip(tr("Select this to add this decoration to the left side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeSideLeft(true);
//     setBridgeSideRight(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeSideLeft()));
 jcbmi->setChecked(bridgeSideLeft && !bridgeSideRight);

 jcbmi = new QAction(tr("Right"),this);
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the right side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeSideRight(true);
//     setBridgeSideLeft(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeSideRight()));
 jcbmi->setChecked(!bridgeSideLeft && bridgeSideRight);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeSideLeft(true);
//     setBridgeSideRight(true);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeSideBoth()));
 jcbmi->setChecked(bridgeSideLeft && bridgeSideRight);

 QMenu* bridgeEndMenu = new QMenu(tr("End"));
 bridgeEndMenu->setToolTip(tr("Select at which end(s) to add this decoration"));
 bridgeMenu->addMenu(bridgeEndMenu);

 QActionGroup* bridgeEndActionGroup = new QActionGroup(this);
 jcbmi = new QAction(tr("None"), this);
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeHasEntry(false);
//     setBridgeHasExit(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeEndNone()));
 jcbmi->setChecked(!bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("Entry"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the entry of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeHasEntry(true);
//     setBridgeHasExit(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeEndEntry()));
 jcbmi->setChecked(bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("Exit"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the exit of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeHasExit(true);
//     setBridgeHasEntry(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeEndExit()));
 jcbmi->setChecked(!bridgeHasEntry && bridgeHasExit);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setBridgeHasEntry(true);
//     setBridgeHasExit(true);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeEndBoth()));
 jcbmi->setChecked(bridgeHasEntry && bridgeHasExit);

 bridgeMenu->addAction(jmi = new QAction(tr("Color"),this));
 jmi->setToolTip(tr("Select this to change the color of this decoration"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", bridgeColor);
     if ((newColor.isValid()) && newColor != (bridgeColor)) {
         setBridgeColor(newColor);
     }
 });

// jmi.setForeground(bridgeColor);
// jmi.setBackground(ColorUtil.contrast(bridgeColor));
 jmi->setIcon(layoutEditor->getColourIcon(bridgeColor));

 bridgeMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Line Width")) + QString::number(bridgeLineWidth),this));
 jmi->setToolTip(tr("Select this to change the line width of this decoration"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     //prompt for bridge line width
//     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
//             tr("DecorationLineWidthMenuItemTitle"),
//             tr("DecorationLineWidthMenuItemTitle"),
//             bridgeLineWidth);
//     setBridgeLineWidth(newValue);
// });
 connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeLineWidth()));

 bridgeMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Approach Width") + " " + QString::number(bridgeApproachWidth)),this));
 jmi->setToolTip(tr("BridgeApproachWidthMenuItemToolTip"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     //prompt for bridge approach width
//     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
//             tr("BridgeApproachWidthMenuItemTitle"),
//             tr("BridgeApproachWidthMenuItemTitle"),
//             bridgeApproachWidth);
//     setBridgeApproachWidth(newValue);
// });
 connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeApproachWidth()));

 bridgeMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Deck Width") + " "+ QString::number(bridgeDeckWidth)),this));
 jmi->setToolTip(tr("Select this to change the distance between the sides of the bridge decorations for this track"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     //prompt for bridge deck width
//     int newValue = QuickPromptUtil.promptForInt(layoutEditor,
//             tr("BridgeDeckWidthMenuItemTitle"),
//             tr("BridgeDeckWidthMenuItemTitle"),
//             bridgeDeckWidth);
//     setBridgeDeckWidth(newValue);
// });
 connect(jmi, SIGNAL(triggered(bool)), this, SLOT(onBridgeDeckWidth()));

 //
 // end bumper menus
 //
 //end bumper decorations can only be on end bumpers
 //
 bool hasEB1 = false;
 if (type1 == POS_POINT) {
     PositionablePoint* pp = (PositionablePoint*) connect1;
     if (pp->getType() == PositionablePoint::END_BUMPER) {
         hasEB1 = true;
     }
 }
 bool hasEB2 = false;
 if (type2 == POS_POINT) {
     PositionablePoint* pp = (PositionablePoint*) connect2;
     if (pp->getType() == PositionablePoint::END_BUMPER) {
         hasEB2 = true;
     }
 }
 if (hasEB1 || hasEB2) {
  QMenu* endBumperMenu = new QMenu(tr("End Bumpers"));
  decorationsMenu->setToolTip(tr("Select this menu to change the end bumper decoration settings for this track"));
  decorationsMenu->addMenu(endBumperMenu);

  QMenu* endBumperEndMenu = new QMenu(tr("End"));
  endBumperEndMenu->setToolTip(tr("Select at which end(s) to add this decoration"));
  endBumperMenu->addMenu(endBumperEndMenu);

  QActionGroup* bumperEndActonGroup = new QActionGroup(this);
  jcbmi = new QAction(tr("None"),this);
  jcbmi->setCheckable(true);
  endBumperEndMenu->addAction(jcbmi);
  bumperEndActonGroup->addAction(jcbmi);
  jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
 // jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jcbmi, &QAction::triggered, [=]{
      setBumperEndStart(false);
      setBumperEndStop(false);
  });
  jcbmi->setChecked(!bumperEndStart && !bumperEndStop);

  jcbmi = new QAction(tr("Start"));
  jcbmi->setCheckable(true);
  endBumperEndMenu->addAction(jcbmi);
  bumperEndActonGroup->addAction(jcbmi);
 // jcbmi->setToolTip(tr("Select this to add this decoration at the beginning of this track"));
 // jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jcbmi, &QAction::triggered, [=]{
      setBumperEndStart(true);
      setBumperEndStop(false);
  });
  jcbmi->setChecked(bumperEndStart && !bumperEndStop);

  jcbmi = new QAction(tr("End"));
  jcbmi->setCheckable(true);
  endBumperEndMenu->addAction(jcbmi);
  bumperEndActonGroup->addAction(jcbmi);
  jcbmi->setToolTip(tr("Select this to add this decoration at the end of this track"));
 // jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jcbmi, &QAction::triggered, [=]{
      setBumperEndStop(true);
      setBumperEndStart(false);
  });
  jcbmi->setChecked(!bumperEndStart && bumperEndStop);

  endBumperMenu->addAction(jmi = new QAction(tr("Color"),this));
  jmi->setToolTip(tr("Select this to change the color of this decoration"));
 // jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jmi, &QAction::triggered, [=]{
      QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", bumperColor);
      if ((newColor != nullptr) && newColor !=(bumperColor)) {
          setBumperColor(newColor);
      }
  });
 // jmi.setForeground(bumperColor);
 // jmi.setBackground(ColorUtil.contrast(bumperColor));
  jmi->setIcon(layoutEditor->getColourIcon(bumperColor));

  endBumperMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
          tr("Line Width")) + QString::number(bumperLineWidth),this));
  jmi->setToolTip(tr("DecorationLineWidthMenuItemToolTip"));
 // jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jmi, &QAction::triggered, [=]{
      //prompt for width
      int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
              tr("Line Width"),
              tr("Line Width"),
              bumperLineWidth);
      setBumperLineWidth(newValue);
  });

  endBumperMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
          tr("Length")) + QString::number(bumperLength),this));
  jmi->setToolTip(tr("DecorationLengthMenuItemToolTip"));
 // jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
  connect(jmi, &QAction::triggered, [=]{
      //prompt for length
      int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
              tr("Length"),
              tr("Length"),
              bumperLength);
      setBumperLength(newValue);
  });
 }

 //
 // tunnel menus
 //
 QMenu* tunnelMenu = new QMenu(tr("Tunnel"));
 decorationsMenu->setToolTip(tr("Select this menu to change the tunnel decoration settings for this track"));
 decorationsMenu->addMenu(tunnelMenu);

 QMenu* tunnelSideMenu = new QMenu(tr("Side"));
 tunnelSideMenu->setToolTip(tr("Select on which side(s) to add this decoration"));
 tunnelMenu->addMenu(tunnelSideMenu);

 QActionGroup* tunnelSideActionGroup = new QActionGroup(this);
 jcbmi = new QAction(tr("None"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
// jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setTunnelSideLeft(false);
//     setTunnelSideRight(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onTunnelSideNone()));
 jcbmi->setChecked(!tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("Left"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the left side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setTunnelSideLeft(true);
//     setTunnelSideRight(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onTunnelSideLeft()));
 jcbmi->setChecked(tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("Right"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the right side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setTunnelSideRight(true);
//     setTunnelSideLeft(false);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onTunnelSideRight()));
 jcbmi->setChecked(!tunnelSideLeft && tunnelSideRight);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//     setTunnelSideLeft(true);
//     setTunnelSideRight(true);
// });
 connect(jcbmi, SIGNAL(triggered(bool)), this, SLOT(onTunnelSideBoth()));
 jcbmi->setChecked(tunnelSideLeft && tunnelSideRight);

 QMenu* tunnelEndMenu = new QMenu(tr("End"));
 tunnelEndMenu->setToolTip(tr("Select at which end(s) to add this decoration"));
 tunnelMenu->addMenu(tunnelEndMenu);

 jcbmi = new QAction(tr("None"));
 tunnelEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
 //jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelHasEntry(false);
     setTunnelHasExit(false);
 });
 jcbmi->setChecked(!tunnelHasEntry && !tunnelHasExit);

 jcbmi = new QAction(tr("Entry"));
 tunnelEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the entry of this track"));
 //jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelHasEntry(true);
     setTunnelHasExit(false);
 });
 jcbmi->setChecked(tunnelHasEntry && !tunnelHasExit);

 jcbmi = new QAction(tr("Exit"));
 tunnelEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the exit of this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), nullptr);
 });
 //jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelHasExit(true);
     setTunnelHasEntry(false);
 });
 jcbmi->setChecked(!tunnelHasEntry && tunnelHasExit);

 jcbmi = new QAction(tr("Both"));
 tunnelEndMenu->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
 connect(jcbmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jcbmi->toolTip(), layoutEditor);
 });
 //jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelHasEntry(true);
     setTunnelHasExit(true);
 });
 jcbmi->setChecked(tunnelHasEntry && tunnelHasExit);

 tunnelMenu->addAction(jmi = new QAction(tr("Color"),this));
 jmi->setToolTip(tr("Select this to change the color of this decoration"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });
 //jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", tunnelColor);
     if ((newColor.isValid()) && newColor != (tunnelColor)) {
         setTunnelColor(newColor);
     }
 });
// jmi->setForeground(tunnelColor);
// jmi->setBackground(ColorUtil::contrast(tunnelColor));

 tunnelMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Floor Width")) + QString::number(tunnelFloorWidth),this));
 jmi->setToolTip(tr("Select this menu to change the tunnel floor width"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), nullptr);
 });
 //jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for tunnel floor width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("Floor Width"),
             tr("Floor Width"),
             tunnelFloorWidth);
     setTunnelFloorWidth(newValue);
 });

 tunnelMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Line Width")) + QString::number(tunnelLineWidth),this));
 jmi->setToolTip(tr("Select this to change the line width of this decoration"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });
 //jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for tunnel line width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("DecorationLineWidthMenuItemTitle"),
             tr("DecorationLineWidthMenuItemTitle"),
             tunnelLineWidth);
     setTunnelLineWidth(newValue);
 });

 tunnelMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Entrance Width")) + QString::number(tunnelEntranceWidth), this));
 jmi->setToolTip(tr("Select this menu to change the tunnel entrance width"));
 connect(jmi, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), jmi->toolTip(), layoutEditor);
 });

 //jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for tunnel entrance width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("Entrance Width"),
             tr("Entrance Width"),
             tunnelEntranceWidth);
     setTunnelEntranceWidth(newValue);
 });

 popupMenu->addMenu(decorationsMenu);
 popupMenu->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));

 popupMenu->addAction(act =new AbstractAction(tr("Edit"), this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(act, &QAction::triggered, [=]{
     editor->editLayoutTrack(this);
 });
 popupMenu->addAction(act =new AbstractAction(tr("Delete"),this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(act, &QAction::triggered, [=]{
         layoutEditor->removeTrackSegment(this);
         remove();
         dispose();
 });

 popupMenu->addAction(act =new AbstractAction(tr("Split Track Segment"),this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
//         splitTrackSegment();
//     }
// });
 connect(act, SIGNAL(triggered(bool)), this, SLOT(splitTrackSegment()));

 QMenu* lineType = new QMenu(tr("Change To"));
 QActionGroup* lineTypeActGrp = new QActionGroup(this);

 lineType->addAction(jmi =new QAction(tr("Line"), this));
   jmi->setCheckable(true);
   jmi->setData(0);
   lineTypeActGrp->addAction(jmi);

// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
   connect(jmi, &QAction::triggered, [=]{
         changeType(0);
//     }
 });
 jmi->setChecked(!isArc() && !isBezier());

 lineType->addAction(jmi = new QAction(tr("Circle"), this));
 jmi->setCheckable(true);
 jmi->setData(1);
 lineTypeActGrp->addAction(jmi);
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(jmi, &QAction::triggered, [=]{
         changeType(1);
//     }
 });
 jmi->setChecked(isArc() && isCircle());

 lineType->addAction(jmi = new QAction(tr("Ellipse"),this));
 jmi->setCheckable(true);
 jmi->setData(2);
 lineTypeActGrp->addAction(jmi);
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(jmi, &QAction::triggered, [=]{
         changeType(2);
//     }
 });
 jmi->setChecked(isArc() && !isCircle());

 lineType->addAction(jmi =new QAction(tr("Bezier"), this));
 jmi->setCheckable(true);
 jmi->setData(3);
 lineTypeActGrp->addAction(jmi);
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(jmi, &QAction::triggered, [=]{
         changeType(3);
//     }
 });
 jmi->setChecked(!isArc() && isBezier());

 popupMenu->addMenu(lineType);

   QActionGroup* constructActGrp = new QActionGroup(this);
 if (isArc() || isBezier())
 {
  if (hideConstructionLines())
  {
   popupMenu->addAction(act =new AbstractAction(tr("Show Construction Line"),this));
   act->setCheckable(true);
   act->setData(SHOWCON);
   constructActGrp->addAction(act);
// {
//             @Override
//             public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
                 hideConstructionLines(SHOWCON);
         });
    } else {
         popupMenu->addAction(new AbstractAction(tr("Hide Construction Line"), this));
   act->setCheckable(true);
   act->setData(HIDECON);
   constructActGrp->addAction(act);
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
                 hideConstructionLines(HIDECON);
         });
     }
 }
 if ((!blockName.isEmpty()) && (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())) {
     popupMenu->addAction(act =new AbstractAction(tr("View Block Routing"),this));
// {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(act, &QAction::triggered, [=]{
             AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
             routeTableAction->actionPerformed(/*e*/);
     });
 }

 //popupMenu.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
 popupMenu->exec(QCursor::pos());
 return popupMenu;
}   // showPopup
#endif
void TrackSegment::onBridgeSideLeft()
{
 setBridgeSideLeft(true);
 setBridgeSideRight(false);
}
void TrackSegment::onBridgeSideRight()
{
 setBridgeSideLeft(false);
 setBridgeSideRight(true);
}
void TrackSegment::onBridgeSideBoth()
{
 setBridgeSideLeft(true);
 setBridgeSideRight(true);
}
void TrackSegment::onBridgeEndNone()
{
 setBridgeHasEntry(false);
 setBridgeHasExit(false);
}
void TrackSegment::onBridgeEndEntry()
{
 setBridgeHasEntry(true);
 setBridgeHasExit(false);
}
void TrackSegment::onBridgeEndExit()
{
 setBridgeHasEntry(false);
 setBridgeHasExit(true);
}
void TrackSegment::onBridgeEndBoth()
{
 setBridgeHasEntry(true);
 setBridgeHasExit(true);
}

void TrackSegment::onBridgeLineWidth()
{
 //prompt for bridge line width
 int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
         tr("DecorationLineWidthMenuItemTitle"),
         tr("DecorationLineWidthMenuItemTitle"),
         bridgeLineWidth);
 setBridgeLineWidth(newValue);

}
void TrackSegment::onBridgeApproachWidth()
{
 //prompt for bridge approach width
 int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
         tr("BridgeApproachWidthMenuItemTitle"),
         tr("BridgeApproachWidthMenuItemTitle"),
         bridgeApproachWidth);
 setBridgeApproachWidth(newValue);
}
void TrackSegment::onBridgeDeckWidth()
{
 //prompt for bridge deck width
 int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
         tr("BridgeDeckWidthMenuItemTitle"),
         tr("BridgeDeckWidthMenuItemTitle"),
         bridgeDeckWidth);
 setBridgeDeckWidth(newValue);
}
void TrackSegment::onTunnelSideNone()
{
 setTunnelSideLeft(false);
 setTunnelSideRight(false);
}
void TrackSegment::onTunnelSideLeft()
{
 setTunnelSideLeft(true);
 setTunnelSideRight(false);
}
void TrackSegment::onTunnelSideRight()
{
 setTunnelSideLeft(false);
 setTunnelSideRight(true);
}
void TrackSegment::onTunnelSideBoth()
{
 setTunnelSideLeft(true);
 setTunnelSideRight(true);
}
void TrackSegment::onAddControlPointAfter()
{
 addBezierControlPointAfter(bezierControlPointIndex);
}
void TrackSegment::onAddControlPointBefore()
{
 addBezierControlPointBefore(bezierControlPointIndex);
}
void TrackSegment::onDeleteControlPoint()
{
 deleteBezierControlPoint(bezierControlPointIndex);
}
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
  bezierControlPointIndex = hitPointType - BEZIER_CONTROL_POINT_OFFSET_MIN;
 if (popupMenu != nullptr) {
     popupMenu->clear();
 } else {
     popupMenu = new QMenu();
 }

 /*QMenuItem* jmi =*/ popupMenu->addSection(tr("ControlPoint") + " #" + QString::number(bezierControlPointIndex));
 //jmi.setEnabled(false);
 popupMenu->addSeparator(); //new JSeparator(JSeparator.HORIZONTAL));

 if (bezierControlPoints.size() < BEZIER_CONTROL_POINT_OFFSET_MAX - BEZIER_CONTROL_POINT_OFFSET_MIN)
 {
  QAction* action;
     popupMenu->addAction(action = new AbstractAction(tr("Add Control Point After"), this));
//     {

//         @Override
//         public void actionPerformed(ActionEvent e) {
//             addBezierControlPointAfter(bezierControlPointIndex);
//         }
//     });
       connect(action, SIGNAL(triggered(bool)), this, SLOT(onAddControlPointAfter()));
     popupMenu->addAction(action = new AbstractAction(tr("Add Control Point Before"),this));
//     {

//         @Override
//         public void actionPerformed(ActionEvent e) {
//             addBezierControlPointBefore(bezierControlPointIndex);
//         }
//     });
      connect(action, SIGNAL(triggered(bool)), this, SLOT(onAddControlPointBefore()));
 }

 if (bezierControlPoints.size() > 2)
 {
  QAction* action;
     popupMenu->addAction(action = new AbstractAction(tr("Delete Control Point") + " #" + QString::number(bezierControlPointIndex), this));
//     {

//         @Override
//         public void actionPerformed(ActionEvent e) {
//             deleteBezierControlPoint(bezierControlPointIndex);
//         }
//     });
       connect(action, SIGNAL(triggered(bool)), this, SLOT(onDeleteControlPoint()));
 }
 //popupMenu.show(e.getComponent(), e.getX(), e.getY());
 popupMenu->exec(QCursor::pos());
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

/*public*/ void TSAbstractAction::actionPerformed(JActionEvent* /*e*/)
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
    if(isFlip()){
        setFlip(false);
    } else{
        setFlip(true);
    }
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}
/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void TrackSegment::dispose() {
  if (popupMenu != nullptr) popupMenu->clear();
  popupMenu = nullptr;
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

/*public*/ bool TrackSegment::isShowConstructionLines() {
    if ((showConstructionLine & HIDECON) == HIDECON
            || (showConstructionLine & HIDECONALL) == HIDECONALL) {
        return false;
    }
    return true;
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

//  if (isCircle()) {
//    result = center; //new QPointF(centreX, centreY);
////      result =  QPointF(centreX, centreY);
//  }
//  else
  if (isArc())
  {
   center = MathUtil::midPoint(getBounds());
   //center = getBounds().center();
   if (isFlip())
   {
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
  else if (isBezier())
  {
   // compute result Bezier point for (t == 0.5);
   // copy all the control points (including end points) into an array
   int len = bezierControlPoints.size() + 2;
   QVector<QPointF> points = QVector<QPointF>(len);
   points.replace(0, ep1);
   for (int idx = 1; idx < len - 1; idx++)
   {
       points.replace(idx, bezierControlPoints.at(idx - 1));
   }
   points.replace(len - 1, ep2);

   // calculate midpoints of all points (len - 1 order times)
   for (int idx = len - 1; idx > 0; idx--)
   {
    for (int jdx = 0; jdx < idx; jdx++) {
        points.replace(jdx,  MathUtil::midPoint(points[jdx], points[jdx + 1]));
    }
   }
   result = points[0];
  }
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

/*public*/ void TrackSegment::setCentreX(double x){
    centreX = x;
}

/*public*/ double TrackSegment::getCentreY(){
    return centreY;
}

/*public*/ void TrackSegment::setCentreY(double y){
    centreY = y;
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
    center = QPointF(p.x(), p.y());
}

/*public*/ double TrackSegment::getChordLength() { return chordLength; }
/*public*/ void TrackSegment::setChordLength(double chord) { chordLength=chord;}

/*static*/ Logger* TrackSegment::log = LoggerFactory::getLogger("TrackSegment");

//}

// remove any prior objects from the scene
void TrackSegment::invalidate(EditScene *g2)
{
 itemMain =invalidateItem(g2,itemMain);
 itemSide = invalidateItem(g2,itemSide);
 hiddenItems = invalidateItem(g2, hiddenItems);
 rects = invalidateItem(g2, rects);
 //dashedItem =invalidateItem(g2, dashedItem);
 decorationItems =invalidateItem(g2, decorationItems);
 itemDashed = invalidateItem(g2, itemDashed);
 itemDashedSide = invalidateItem(g2, itemDashedSide);
 itemTies = invalidateItem(g2, itemTies);
 itemTiesSide = invalidateItem(g2, itemTiesSide);
 itemBallast = invalidateItem(g2, itemBallast);
 itemBallastSide = invalidateItem(g2, itemBallastSide);
 itemPoints = invalidateItem(g2, itemPoints);
 item = invalidateItem(g2, item);
}

#if 0
void TrackSegment::drawHiddenTrack(LayoutEditor* editor, EditScene *g2)
{
 invalidateItem(g2, hiddenItems);
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
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
  itemGroup->addToGroup(lineItem);
  hiddenItems = itemGroup;
  g2->addItem(hiddenItems);
  editor->setTrackStrokeWidth(!editor->main);
 }
}
#endif
//void TrackSegment::drawDashedTrack(LayoutEditor* editor, EditScene* g2, bool mainline)
//{
// QColor color;
// LayoutBlock* b = getLayoutBlock();
// if (b!=NULL) color = (b->getBlockColor());
// else color = (editor->defaultTrackColor);
// editor->setTrackStrokeWidth(mainline);
// QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

// invalidateItem(g2,dashedItem);

// if (getArc())
// {
//  calculateTrackSegmentAngle();
//  //Stroke drawingStroke;
//  //Stroke originalStroke = g2.getStroke();
//  QPen drawingStroke;
//  if (mainline)
//   //drawingStroke = new BasicStroke(mainlineTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
//   drawingStroke = QPen(color,editor->mainlineTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);
//  else
////    drawingStroke = new BasicStroke(sideTrackWidth, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
//   drawingStroke =  QPen(color,editor->sidelineTrackWidth,Qt::DashLine, Qt::SquareCap,Qt::BevelJoin);

//  //g2.setStroke(drawingStroke);
//  //g2.draw(new Arc2D(t.getCX(), t.getCY(), t.getCW(), t.getCH(), t->getStartadj(), t.getTmpAngle(), Arc2D.OPEN));
//  //g2->addEllipse(t->getCX(), t->getCY(), t->getCW(), t->getCH(),drawingStroke);
//  QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
//  lineItem->setStartAngle(getStartAdj()*16);
//  lineItem->setSpanAngle(getTmpAngle()*16);
//  lineItem->setPen(drawingStroke);
//  itemGroup->addToGroup(lineItem);

//  dashedItem = itemGroup;
//  g2->addItem(dashedItem);
//  //g2.setStroke(originalStroke);
// }
// else
// {
//  QPointF end1 = LayoutEditor::getCoords(getConnect1(),getType1());
//  QPointF end2 = LayoutEditor::getCoords(getConnect2(),getType2());
//  double delX = end1.x() - end2.x();
//  double delY = end1.y() - end2.y();
//  double cLength = qSqrt( (delX*delX) + (delY*delY) );
//  // note: The preferred dimension of a dash (solid + blank space) is
//  //         5 * the track width - about 60% solid and 40% blank.
//  int nDashes = (int)( cLength / ((editor->trackWidth)*5.0) );
//  if (nDashes < 3) nDashes = 3;
//  double delXDash = -delX/( (nDashes) - 0.5 );
//  double delYDash = -delY/( (nDashes) - 0.5 );
//  double begX = end1.x();
//  double begY = end1.y();
//  QGraphicsItemGroup* group = new QGraphicsItemGroup();
//  for (int k = 0; k<nDashes; k++)
//  {
//   //g2->addLine(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))),QPen(color,trackWidth));
//   QGraphicsLineItem* lineItem = new QGraphicsLineItem(QLineF( QPointF(begX,begY), QPointF((begX+(delXDash*0.5)),(begY+(delYDash*0.5)))));
//   lineItem->setPen(QPen(color,editor->trackWidth));
//   group->addToGroup(lineItem);
//   begX += delXDash;
//   begY += delYDash;
//  }
//  dashedItem = group;
//  g2->addItem(dashedItem);
// }
//}

/*
* Calculates the initial parameters for drawing a circular track segment.
*/
/*private*/ void TrackSegment::calculateTrackSegmentAngle()
{
  QPointF pt1 = LayoutEditor::getCoords(getConnect1(),getType1());
  QPointF pt2 = LayoutEditor::getCoords(getConnect2(),getType2());
  if (isFlip())
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
    if(isCircle())
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
/*protected*/ void TrackSegment::draw1(EditScene* g2, bool isMain, bool isBlock)
{
 if (!isBlock && isDashed() && getLayoutBlock() != nullptr) {
     // Skip the dashed rail layer, the block layer will display the dashed track
     // This removes random rail fragments from between the block dashes
     return;
 }
 //qApp->processEvents(QEventLoop::AllEvents, 100);

 QColor color;


 if(isMain == mainline)
 {
  itemGroup = invalidateItem(g2, itemGroup);
  if(itemGroup == nullptr)
  {
   itemGroup = new QGraphicsItemGroup();
   itemGroup->setZValue(Editor::HANDLES+1);
   g2->addItem(itemGroup);
  }

  if (isBlock)
  {
      color = setColorForTrackBlock(g2, getLayoutBlock());
      layoutEditor->drawingStroke.setColor(color);
  }
  if (isArc())
  {
   calculateTrackSegmentAngle();
//            g2.draw(new Arc2D(getCX(), getCY(), getCW(), getCH(), getStartAdj(), getTmpAngle(), Arc2D.OPEN));
   QGraphicsArcItem* lineItem = new QGraphicsArcItem(getCX(), getCY(), getCW(), getCH());
   lineItem->setStartAngle(getStartAdj()*16);
   lineItem->setSpanAngle(getTmpAngle()*16);
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
  }
  else if (isBezier())
  {
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
   pathItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(pathItem);
  }
  else
  {
   QPointF end1 = LayoutEditor::getCoords(getConnect1(), getType1());
   QPointF end2 = LayoutEditor::getCoords(getConnect2(), getType2());

   //g2.draw(new Line2D(end1, end2));
   QGraphicsLineItem* lineItem = new QGraphicsLineItem(end1.x(), end1.y(), end2.x(), end2.y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
  }
  trackRedrawn();
 }
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

    if (isMain == mainline) {
     itemGroup = invalidateItem(g2, itemGroup);
     if(itemGroup == nullptr)
     {
      itemGroup = new QGraphicsItemGroup();
      itemGroup->setZValue(Editor::HANDLES+1);
      g2->addItem(itemGroup);
     }

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
            lineItem->setStartAngle(startAdj*16);
            lineItem->setSpanAngle(tmpAngle*16);
            lineItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(lineItem);
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
            lineItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(lineItem);
            trackRedrawn();
        }
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

            QPainterPath path = MathUtil::drawBezier(points, -railDisplacement);
            QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
            pathItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(pathItem);
            path = MathUtil::drawBezier(points, +railDisplacement);
            pathItem = new QGraphicsPathItem(path);
            pathItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(pathItem);
        }
        else {
            QPointF end1 = LayoutEditor::getCoords(getConnect1(), getType1());
            QPointF end2 = LayoutEditor::getCoords(getConnect2(), getType2());

            QPointF delta = MathUtil::subtract(end2, end1);
            QPointF vector = MathUtil::normalize(delta, railDisplacement);
            vector = MathUtil::orthogonal(vector);

            QPointF ep1L = MathUtil::add(end1, vector);
            QPointF ep2L = MathUtil::add(end2, vector);
            //g2.draw(new Line2D(ep1L, ep2L));
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(ep1L.x(), ep1L.y(), ep2L.x(), ep2L.y());
            lineItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(lineItem);

            QPointF ep1R = MathUtil::subtract(end1, vector);
            QPointF ep2R = MathUtil::subtract(end2, vector);
            //g2.draw(new Line2D(ep1R, ep2R));
            lineItem = new QGraphicsLineItem(ep1R.x(), ep1R.y(), ep2R.x(), ep2R.y());
            lineItem->setPen(layoutEditor->drawingStroke);
            itemGroup->addToGroup(lineItem);

        }
        trackRedrawn();
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegment::highlightUnconnected(EditScene* /*g2*/, int /*selectedType*/) {
    // TrackSegments are always connected
    // nothing to see here... move along...
}

//@Override
/*protected*/ void TrackSegment::drawEditControls(EditScene* g2)
{
    //g2.setColor(Color.black)
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

 invalidateItem(g2, rects);

 QGraphicsLineItem* lineItem;
 if (isShowConstructionLines())
 {
  QPointF ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
  QPointF ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
  if (isCircle())
  {
   // draw radiuses
   QPointF circleCenterPoint = getCoordsCenterCircle();
   //g2.draw(new Line2D(circleCenterPoint, ep1));
   lineItem = new QGraphicsLineItem(circleCenterPoint.x(), circleCenterPoint.y(), ep1.x(), ep1.y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
   //g2.draw(new Line2D(circleCenterPoint, ep2));
   lineItem = new QGraphicsLineItem(circleCenterPoint.x(), circleCenterPoint.y(), ep2.x(), ep2.y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
   // Draw a circle and square at the circles centre, that
   // allows the user to change the angle by dragging the mouse.
   //g2.draw(layoutEditor->trackEditControlCircleAt(circleCenterPoint));
   QGraphicsEllipseItem* circleItem = trackEditControlCircleAt(circleCenterPoint);
   //circleItem->setPen(layoutEditor->drawingStroke);
   circleItem->setPen(QPen(QColor(Qt::magenta)));
   itemGroup->addToGroup(circleItem);
   //g2.draw(layoutEditor->trackEditControlRectAt(circleCenterPoint));
   QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(circleCenterPoint));
   rectItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(rectItem);
  }
#if 1
  else if (isBezier())
  {
   //draw construction lines and control circles
   QPointF lastPt = ep1;
   for (QPointF bcp : bezierControlPoints)
   {
       //g2.draw(new Line2D(lastPt, bcp));
    lineItem = new QGraphicsLineItem(lastPt.x(), lastPt.y(), bcp.x(), bcp.y());
    lineItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(lineItem);
    lastPt = bcp;
    //g2.draw(layoutEditor.trackEditControlRectAt(bcp));
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(bcp));
    rectItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(rectItem);
   }
   //g2.draw(new Line2D(lastPt, ep2));
   lineItem = new QGraphicsLineItem(lastPt.x(), lastPt.y(), ep2.x(), ep2.y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
  }
 }
#endif
 //g2.draw(layoutEditor.trackEditControlCircleAt(getCentreSeg()));
 QPointF ctr = getCentreSeg();
 QGraphicsEllipseItem* circleItem = trackEditControlCircleAt(ctr);
 circleItem->setPen(layoutEditor->drawingStroke);
 itemGroup->addToGroup(circleItem);
 rects = itemGroup;
 g2->addItem(rects);
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
/*public*/ void TrackSegment::reCheckBlockBoundary() const {
    // nothing to see here... move along...
}
#if 0
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
#endif
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
  if (isFlip())
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
    }
    else if (LayoutTrack::isBezierHitType(connectionType))
    {
     result = getBezierControlPoint(connectionType - BEZIER_CONTROL_POINT_OFFSET_MIN);
    }
    return result;
}


/**
 * @return the bounds of this track segment
 */
//@Override
/*public*/ QRectF TrackSegment::getBounds() {
    QRectF result;

    QPointF ep1 = center, ep2 = center;
    if (getConnect1() != nullptr) {
        ep1 = LayoutEditor::getCoords(getConnect1(), getType1());
    }
    if (getConnect2() != nullptr) {
        ep2 = LayoutEditor::getCoords(getConnect2(), getType2());
    }

    result = QRectF(ep1.x(), ep1.y(), 0, 0);
    result= MathUtil::add(result, ep2);

    return result;
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
    if (decorations == nullptr)
    {
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
/*public*/ void TrackSegment::setDecorations(QMap<QString, QString>* decorations)
{
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

/*
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity *> *TrackSegment::getLayoutConnectivity()
{
 QList<LayoutConnectivity*>* results = new QList<LayoutConnectivity*>();

 LayoutConnectivity* lc = nullptr;
 LayoutBlock* lb1 = getLayoutBlock(), *lb2 = nullptr;
 // ensure that block is assigned
 if (lb1 != nullptr)
 {
  // check first connection for turnout or level crossing
  if ((type1 >= TURNOUT_A) && (type1 <= LEVEL_XING_D))
  {
   // have connection to turnout or level crossing
   if (type1 <= TURNOUT_D)
   {
    // have connection to a turnout, is block different
    LayoutTurnout* lt = (LayoutTurnout*) getConnect1();
    lb2 = lt->getLayoutBlock();
    if (lt->getTurnoutType() > LayoutTurnout::WYE_TURNOUT)
    {
     // not RH, LH, or WYE turnout - other blocks possible
     if ((type1 == TURNOUT_B) && (lt->getLayoutBlockB() != nullptr)) {
         lb2 = lt->getLayoutBlockB();
     }
     if ((type1 == TURNOUT_C) && (lt->getLayoutBlockC() != nullptr)) {
         lb2 = lt->getLayoutBlockC();
     }
     if ((type1 == TURNOUT_D) && (lt->getLayoutBlockD() != nullptr)) {
         lb2 = lt->getLayoutBlockD();
     }
    }
    if ((lb2 != nullptr) && (lb1 != lb2))
    {
     // have a block boundary, create a LayoutConnectivity
     log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
     lc = new LayoutConnectivity(lb1, lb2);
     lc->setConnections(this, lt, type1, nullptr);
     lc->setDirection(Path::computeDirection(
             LayoutEditor::getCoords(getConnect2(), type2),
             LayoutEditor::getCoords(getConnect1(), type1)));
     results->append(lc);
    }
   }
   else {
       // have connection to a level crossing
       LevelXing* lx = (LevelXing*) getConnect1();
       if ((type1 == LEVEL_XING_A) || (type1 == LEVEL_XING_C)) {
           lb2 = lx->getLayoutBlockAC();
       } else {
           lb2 = lx->getLayoutBlockBD();
       }
       if ((lb2 != nullptr) && (lb1 != lb2)) {
           // have a block boundary, create a LayoutConnectivity
        log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
           lc = new LayoutConnectivity(lb1, lb2);
           lc->setConnections(this, lx, type1, nullptr);
           lc->setDirection(Path::computeDirection(
                   LayoutEditor::getCoords(getConnect2(), type2),
                   LayoutEditor::getCoords(getConnect1(), type1)));
           results->append(lc);
       }
   }
  } else if ((type1 >= SLIP_A) && (type1 <= SLIP_D)) {
      // have connection to a slip crossing
      LayoutSlip* ls = (LayoutSlip*) getConnect1();
      lb2 = ls->getLayoutBlock();
      if ((lb2 != nullptr) && (lb1 != lb2)) {
          // have a block boundary, create a LayoutConnectivity
       log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
          lc = new LayoutConnectivity(lb1, lb2);
          lc->setConnections(this, ls, type1, nullptr);
          lc->setDirection(Path::computeDirection(LayoutEditor::getCoords(getConnect2(),
                  type2), LayoutEditor::getCoords(getConnect1(), type1)));
          results->append(lc);
      }
  }
  // check second connection for turnout or level crossing
  if ((type2 >= TURNOUT_A) && (type2 <= LEVEL_XING_D))
  {
   // have connection to turnout or level crossing
   if (type2 <= TURNOUT_D)
   {
    // have connection to a turnout
    LayoutTurnout* lt = (LayoutTurnout*) getConnect2();
    lb2 = lt->getLayoutBlock();
    if (lt->getTurnoutType() > LayoutTurnout::WYE_TURNOUT) {
        // not RH, LH, or WYE turnout - other blocks possible
        if ((type2 == TURNOUT_B) && (lt->getLayoutBlockB() != nullptr)) {
            lb2 = lt->getLayoutBlockB();
        }
        if ((type2 == TURNOUT_C) && (lt->getLayoutBlockC() != nullptr)) {
            lb2 = lt->getLayoutBlockC();
        }
        if ((type2 == TURNOUT_D) && (lt->getLayoutBlockD() != nullptr)) {
            lb2 = lt->getLayoutBlockD();
        }
    }
    if ((lb2 != nullptr) && (lb1 != lb2)) {
        // have a block boundary, create a LayoutConnectivity
     log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
        lc = new LayoutConnectivity(lb1, lb2);
        lc->setConnections(this, lt, type2, nullptr);
        lc->setDirection(Path::computeDirection(
                LayoutEditor::getCoords(getConnect1(), type1),
                LayoutEditor::getCoords(getConnect2(), type2)));
        results->append(lc);
    }
   }
   else
   {
    // have connection to a level crossing
    LevelXing* lx = (LevelXing*) getConnect2();
    if ((type2 == LEVEL_XING_A) || (type2 == LEVEL_XING_C)) {
        lb2 = lx->getLayoutBlockAC();
    } else {
        lb2 = lx->getLayoutBlockBD();
    }
    if ((lb2 != nullptr) && (lb1 != lb2)) {
        // have a block boundary, create a LayoutConnectivity
     log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
        lc = new LayoutConnectivity(lb1, lb2);
        lc->setConnections(this, lx, type2, nullptr);
        lc->setDirection(Path::computeDirection(
                LayoutEditor::getCoords(getConnect1(), type1),
                LayoutEditor::getCoords(getConnect2(), type2)));
        results->append(lc);
    }
   }
  }
  else if ((type2 >= SLIP_A) && (type2 <= SLIP_D))
  {
   // have connection to a slip crossing
   LayoutSlip* ls = (LayoutSlip*) getConnect2();
   lb2 = ls->getLayoutBlock();
   if ((lb2 != nullptr) && (lb1 != lb2)) {
       // have a block boundary, create a LayoutConnectivity
    log->debug(tr("Block boundary  ('%1'<->'%2') found at %3").arg(lb1->getDisplayName()).arg(lb2->getDisplayName()).arg(this->toString()));
       lc = new LayoutConnectivity(lb1, lb2);
       lc->setConnections(this, ls, type2, nullptr);
       lc->setDirection(Path::computeDirection(
               LayoutEditor::getCoords(getConnect1(), type1),
               LayoutEditor::getCoords(getConnect2(), type2)));
       results->append(lc);
   }
  } else {
      // this is routinely reached in normal operations
      // (nothing to see here... move along)
  }
 }   // if (lb1 != null)
 return results;
}   // getLayoutConnectivity()

/**
 * {@inheritDoc}
 */
/*//@Override
public*/ QList<int> TrackSegment::checkForFreeConnections() {
    QList<int> result = QList<int>();
    // Track Segments always have all their connections so...
    // (nothing to see here... move along)
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool TrackSegment::checkForUnAssignedBlocks() {
    return (getLayoutBlock() != nullptr);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegment::checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *> *> *blockNamesToTrackNameSetsMap) {
    /*
     * For each (non-null) blocks of this track do:
     * #1) If it's got an entry in the blockNamesToTrackNameSetMap then
     * #2) If this track is already in the TrackNameSet for this block
     *     then return (done!)
     * #3) else add a new set (with this block/track) to
     *     blockNamesToTrackNameSetMap and
     * #4) collect all the connections in this block
     * <p>
     *     Basically, we're maintaining contiguous track sets for each block found
     *     (in blockNamesToTrackNameSetMap)
     */
    QList<QSet<QString>*>* trackNameSets = new QList<QSet<QString>*>();
    QSet<QString>* trackNameSet = new QSet<QString>();    // assume not found (pessimist!)
    QString blockName = getBlockName();
    if (blockName != "") {
        trackNameSets = blockNamesToTrackNameSetsMap->value(blockName);
        if (trackNameSets && !trackNameSets->isEmpty()) { // (#1)
            for (QSet<QString>* checkTrackNameSet : *trackNameSets) {
                if (checkTrackNameSet->contains(getName())) { // (#2)
                    trackNameSet = checkTrackNameSet;
                    break;
                }
            }
        } else {    // (#3)
            log->debug(tr("*New block ('%1') trackNameSets").arg(blockName));
            trackNameSets = new QList<QSet<QString>*>();
            blockNamesToTrackNameSetsMap->insert(blockName, trackNameSets);
        }
        if (trackNameSet==nullptr || trackNameSet->isEmpty()) {
            trackNameSet = new QSet<QString>();//new LinkedHashSet<>();
            trackNameSets->append(trackNameSet);
        }
        trackNameSet->insert(getName());
        if (trackNameSet->contains(getName())) {
            log->debug(tr("*    Add track '%1' to TrackNameSets for block '%2'").arg(getName()).arg(blockName));
        }
        // (#4)
        if (connect1 != nullptr) {
            connect1->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
        }
        if (connect2 != nullptr) { // (#4)
            connect2->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
        }
    }
}   // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegment::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
        /*@Nonnull*/ QSet<QString> *trackNameSet) {
    if (!trackNameSet->contains(getName())) {
        // is this the blockName we're looking for?
        if (this->blockName == blockName) {
            // if we are added to the TrackNameSet
            trackNameSet->insert(getName());
            if (trackNameSet->contains(getName())) {
                log->debug(tr("*    Add track '%1'for block '%2'").arg(getName()).arg(blockName));
            }
            // these should never be null... but just in case...
            // it's time to play... flood your neighbours!
            if (connect1 != nullptr) {
                connect1->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
            }
            if (connect2 != nullptr) {
                connect2->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
            }
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegment::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    setLayoutBlock(layoutBlock);
}
