#include "tracksegmentview.h"
#include "mathutil.h"
#include "loggerfactory.h"
#include <QtMath>
#include "jmricolorchooser.h"
#include "abstractaction.h"
#include "layouteditor.h"
#include "layouttrackdrawingoptions.h"
#include "positionablepoint.h"
#include <QToolTip>
#include "quickpromptutil.h"
#include "layouteditorcomponent.h"
/**
 * MVC View component for the TrackSegment class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class TrackSegmentView extends LayoutTrackView {

/**
 * constructor method.
 * @param track the track segment to view.
 */
/*public*/ TrackSegmentView::TrackSegmentView(/*@Nonnull*/ TrackSegment* track, LayoutEditor* layoutEditor) :  LayoutTrackView(track, layoutEditor){
    //super(track);
 this->trackSegment = track;
 setupDefaultBumperSizes(layoutEditor);
 editor = new TrackSegmentEditor(layoutEditor);
// connect(track, &TrackSegment::objectsSet, [=]{
// center = getCentreSeg();
// });
}
/*public*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MAX_BUMPER_LENGTH = 40;
/*public*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MIN_BUMPER_LENGTH = 8;
/*public*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MAX_BUMPER_WIDTH = 10;
/*public*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MIN_BUMPER_WIDTH = 1;

/*private*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MAX_ARROW_LINE_WIDTH = 5;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_ARROW_LENGTH = 60;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_ARROW_GAP = 40;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_BRIDGE_LINE_WIDTH = 5;
/*private*/ /*static*/ /*final*/  /*const*/ int TrackSegmentView::MIN_BRIDGE_LINE_WIDTH = 1;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_BRIDGE_APPROACH_WIDTH = 100;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_BRIDGE_APPROACH_WIDTH = 8;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_BRIDGE_DECK_WIDTH = 80;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_BRIDGE_DECK_WIDTH = 6;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_BUMPER_LINE_WIDTH = 9;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_BUMPER_LINE_WIDTH = 1;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_TUNNEL_FLOOR_WIDTH = 40;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_TUNNEL_FLOOR_WIDTH = 4;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_TUNNEL_LINE_WIDTH = 9;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_TUNNEL_LINE_WIDTH = 1;

/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MAX_TUNNEL_ENTRANCE_WIDTH = 80;
/*private*/ /*static*/ /*final*/  /*const*/  int TrackSegmentView::MIN_TUNNEL_ENTRANCE_WIDTH = 1;

// temporary?
//@Nonnull
/*public*/ TrackSegment* TrackSegmentView::getTrackSegment() {
    return trackSegment;
}

/**
 * Get debugging string for the TrackSegment.
 *
 * @return text showing id and connections of this segment
 */
//@Override
/*public*/ QString TrackSegmentView::toString() {
    return "TrackSegmentView " + getName()
            + " c1:{" + getConnect1Name() + " (" + getType1() + ")},"
            + " c2:{" + getConnect2Name() + " (" + getType2() + ")}";

}

/*
* Accessor methods
 */
//@Nonnull
/*public*/ QString TrackSegmentView::getBlockName() {
    return trackSegment->getBlockName();
}

/*public*/ HitPointType::TYPES TrackSegmentView::getType1() {
    return trackSegment->getType1();
}

/*public*/ HitPointType::TYPES TrackSegmentView::getType2() {
    return trackSegment->getType2();
}

/*public*/ LayoutTrack* TrackSegmentView::getConnect1() {
    return trackSegment->getConnect1();
}

/*public*/ LayoutTrack* TrackSegmentView::getConnect2() {
    return trackSegment->getConnect2();
}

/**
 * set a new connection 1
 *
 * @param connectTrack   the track we want to connect to
 * @param connectionType where on that track we want to be connected
 */
/*protected*/ void TrackSegmentView::setNewConnect1(/*@CheckForNull*/ LayoutTrack* connectTrack, HitPointType::TYPES connectionType) {
    trackSegment->setNewConnect1(connectTrack, connectionType);
}

/**
 * set a new connection 2
 *
 * @param connectTrack   the track we want to connect to
 * @param connectionType where on that track we want to be connected
 */
/*protected*/ void TrackSegmentView::setNewConnect2(/*@CheckForNull*/ LayoutTrack* connectTrack, HitPointType::TYPES connectionType) {
    trackSegment->setNewConnect2(connectTrack, connectionType);
}

/**
 * replace old track connection with new track connection
 *
 * @param oldTrack the old track connection
 * @param newTrack the new track connection
 * @param newType  type of the new track connection
 * @return true if successful
 */
/*public*/ bool TrackSegmentView::replaceTrackConnection(/*@CheckForNull*/ LayoutTrack* oldTrack, /*@CheckForNull*/ LayoutTrack* newTrack, HitPointType::TYPES newType) {
    return trackSegment->replaceTrackConnection(oldTrack, newTrack, newType);
}

/*public*/ bool TrackSegmentView::isDashed() {
    return dashed;
}

/*public*/ void TrackSegmentView::setDashed(bool dash) {
    if (dashed != dash) {
        dashed = dash;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/**
 * @return true if track segment is an arc
 */
/*public*/ bool TrackSegmentView::isArc() {
    return arc;
}

/*public*/ void TrackSegmentView::setArc(bool boo) {
    if (arc != boo) {
        arc = boo;
        if (arc) {
            circle = false;
            bezier = false;
            hideConstructionLines(SHOWCON);
        }
        changed = true;
    }
}

/**
 * @return true if track segment is circle
 */
/*public*/ bool TrackSegmentView::isCircle() {
    return circle;
}

/*public*/ void TrackSegmentView::setCircle(bool boo) {
    if (circle != boo) {
        circle = boo;
        if (circle) {
            // if it was a bezier
            if (bezier) {
                // then use control point to calculate arc
                // adjacent connections must be defined...
                if ((getConnect1() != nullptr) && (getConnect2() != nullptr)) {
                    QPointF end1 = layoutEditor->getCoords(getConnect1(), getType1());
                    QPointF end2 = layoutEditor->getCoords(getConnect2(), getType2());
                    double chordLength = MathUtil::distance(end1, end2);

                    // get first and last control points
                    int cnt = bezierControlPoints.size();

                    QPointF cp0 = bezierControlPoints.at(0);
                    QPointF cpN = bezierControlPoints.at(cnt - 1);
                    // calculate orthoginal points
                    QPointF op1 = MathUtil::add(end1, MathUtil::orthogonal(MathUtil::subtract(cp0, end1)));
                    QPointF op2 = MathUtil::subtract(end2, MathUtil::orthogonal(MathUtil::subtract(cpN, end2)));
                    // use them to find center point
                    QPointF ip = MathUtil::intersect(end1, op1, end2, op2);
                    if (!ip.isNull()) {   // single intersection point found
                        double r1 = MathUtil::distance(ip, end1);
                        double r2 = MathUtil::distance(ip, end2);
                        if (qAbs(r1 - r2) <= 1.0) {
                            // calculate arc: θ = 2 sin-1(c/(2r))
                            setAngle(qRadiansToDegrees(2.0 *qAsin(chordLength / (2.0 * r1))));
                            // the sign of the distance tells what side of the line the center point is on
                            double distance = MathUtil::distance(end1, end2, ip);
                            setFlip(distance < 0.0);
                        }
                    }
                }
                bezier = false;
            } else if (getAngle() < 1.0) {
                setAngle(90.0);
            }
            arc = true;
            hideConstructionLines(SHOWCON);
        }
        changed = true;
    }
}

/**
 * @return true if track segment circle or arc should be drawn flipped
 */
/*public*/ bool TrackSegmentView::isFlip() {
    return flip;
}

/*public*/ void TrackSegmentView:: setFlip(bool boo) {
    if (flip != boo) {
        flip = boo;
        changed = true;
        hideConstructionLines(SHOWCON);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/**
 * @return true if track segment is a bezier curve
 */
/*public*/ bool TrackSegmentView::isBezier() {
    return bezier;
}

/**
 * @param bool Set true to turn on Bezier curve representation.
 */
/*public*/ void TrackSegmentView::setBezier(bool boo) {
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

/*public*/ double TrackSegmentView::getAngle() {
    return angle;
}

/*public*/ void TrackSegmentView::setAngle(double x) {
    angle = MathUtil::pin(x, 0.0, 180.0);
    changed = true;
}

/**
 * Get the direction from end point 1 to 2.
 * <p>
 * Note: Goes CW from east (0) to south (PI/2) to west (PI) to north
 * (PI*3/2), etc.
 *
 * @return The direction (in radians)
 */
/*public*/ double TrackSegmentView::getDirectionRAD() {
    QPointF ep1 = getCoordsCenter(), ep2 = getCoordsCenter();
    if (getConnect1() != nullptr) {
        ep1 = layoutEditor->getCoords(getConnect1(), getType1());
    }
    if (getConnect2() != nullptr) {
        ep2 = layoutEditor->getCoords(getConnect2(), getType2());
    }
    return (M_PI / 2.) - MathUtil::computeAngleRAD(ep1, ep2);
}

/**
 * Get the direction from end point 1 to 2.
 * <p>
 * Note: Goes CW from east (0) to south (90) to west (180) to north (270),
 * etc.
 *
 * @return the direction (in degrees)
 */
/*public*/ double TrackSegmentView::getDirectionDEG() {
    return qRadiansToDegrees(getDirectionRAD());
}

/**
 * Determine if we need to redraw a curved piece of track. Saves having to
 * recalculate the circle details each time.
 *
 * @return true means needs to be (re)drawn
 */
/*public*/ bool TrackSegmentView::trackNeedsRedraw() {
    return changed;
}

/*public*/ void TrackSegmentView::trackRedrawn() {
    changed = false;
}

/*public*/ LayoutBlock* TrackSegmentView::getLayoutBlock() {
    return trackSegment->getLayoutBlock();
}

/*public*/ QString TrackSegmentView::getConnect1Name() {
    return trackSegment->getConnect1Name();
}

/*public*/ QString TrackSegmentView::getConnect2Name() {
    return trackSegment->getConnect2Name();
}

//@Override
/*public*/ LayoutTrack* TrackSegmentView::getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ {
    return trackSegment->getConnection(connectionType);
}

/**
 * {@inheritDoc}
 * <p>
 * This implementation does nothing because {@link #setNewConnect1} and
 * {@link #setNewConnect2} should be used instead.
 */
// only implemented here to suppress "does not override abstract method " error in compiler
//@Override
/*public*/ void TrackSegmentView::setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ {
}

/*public*/ int TrackSegmentView::getNumberOfBezierControlPoints() {
    return bezierControlPoints.size();
}

/**
 * @param index If negative, this is index from the end i.e. -1 is the last
 *              element
 * @return Reference to the indexed control point
 */
/*public*/ QPointF TrackSegmentView::getBezierControlPoint(int index) {
    QPointF result = getCoordsCenter();
    if (index < 0) {
        index += bezierControlPoints.size();
    }
    if ((index >= 0) && (index < bezierControlPoints.size())) {
        result = bezierControlPoints.at(index);
    }
    return result;
}

/**
 * @param p     the location of the point to be set
 * @param index If negative, this is index from the end i.e. -1 is the last
 *              element
 */
/*public*/ void TrackSegmentView::setBezierControlPoint(/*@CheckForNull*/ QPointF p, int index) {
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

//@Nonnull
/*public*/ QList<QPointF> TrackSegmentView::getBezierControlPoints() {
    return bezierControlPoints;
}

/**
 * Set up a LayoutBlock for this Track Segment.
 *
 * @param newLayoutBlock the LayoutBlock to set
 */
/*public*/ void TrackSegmentView::setLayoutBlock(/*@CheckForNull*/ LayoutBlock* newLayoutBlock) {
    trackSegment->setLayoutBlock(newLayoutBlock);
}

/**
 * Set up a LayoutBlock for this Track Segment.
 *
 * @param name the name of the new LayoutBlock
 */
/*public*/ void TrackSegmentView::setLayoutBlockByName(/*@CheckForNull*/ QString name) {
    trackSegment->setLayoutBlockByName(name);
}

/*
* non-accessor methods
 */
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::scaleCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    LayoutTrackView::setCoordsCenter(MathUtil::multiply(getCoordsCenter(), factor));
    if (isBezier()) {
        for (QPointF p : bezierControlPoints) {
            //p.setLocation(MathUtil::multiply(p, factor));
         p = MathUtil::multiply(p, factor);
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::translateCoords(double xFactor, double yFactor) {
    LayoutTrackView::setCoordsCenter(MathUtil::add(getCoordsCenter(), QPointF(xFactor, yFactor)));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::rotateCoords(double angleDEG) {
    if (isBezier()) {
        for (QPointF p : bezierControlPoints) {
            //p.setLocation(MathUtil::rotateDEG(p, getCoordsCenter(), angleDEG));
       p= MathUtil::rotateDEG(p, center, angleDEG);}
    }
}

/**
 * Set center coordinates.
 *
 * @param newCenterPoint the coordinates to set
 */
//@Override
/*public*/ void TrackSegmentView::setCoordsCenter(/*@Nonnull*/ QPointF newCenterPoint) {
    if (getCoordsCenter() != newCenterPoint) {
        if (isBezier()) {
            QPointF delta = MathUtil::subtract(newCenterPoint, getCoordsCenter());
            for (QPointF p : bezierControlPoints) {
                //p.setLocation(MathUtil::add(p, delta));
             p = MathUtil::add(p, delta);
            }
        }
        LayoutTrackView::setCoordsCenter(newCenterPoint);
    }
}


/*public*/ void TrackSegmentView::updateBlockInfo() {
    trackSegment->updateBlockInfo();
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ HitPointType::TYPES TrackSegmentView::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    HitPointType::TYPES result = HitPointType::NONE;  // assume point not on connection

    if (!requireUnconnected) {
        // note: optimization here: instead of creating rectangles for all the
        // points to check below, we create a rectangle for the test point
        // and test if the points below are in that rectangle instead.
        QRectF r = layoutEditor->layoutEditorControlCircleRectAt(hitPoint);
        QPointF p, minPoint = MathUtil::zeroPoint2D;
        double circleRadius = layoutEditor->SIZE * layoutEditor->getTurnoutCircleSize();
        double distance, minDistance = INFINITY;

        if (isCircle()) {
            p = getCoordsCenterCircle();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::TRACK_CIRCLE_CENTRE;
            }
        } else if (isBezier()) {
            // hit testing for the control points
            for (int index = 0; index < bezierControlPoints.size(); index++) {
                p = bezierControlPoints.at(index);
                distance = MathUtil::distance(p, hitPoint);
                if (distance < minDistance) {
                    minDistance = distance;
                    minPoint = p;
                    result = (HitPointType::TYPES)HitPointType::bezierPointIndexedValue(index);
                }
            }
        }
        p = getCentreSeg();
        if (r.contains(p)) {
            distance = MathUtil::distance(p, hitPoint);
            if (distance <= minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::TRACK;
            }
        }
        if ((result != HitPointType::NONE) && (useRectangles ? !r.contains(minPoint) : (minDistance > circleRadius))) {
            result = HitPointType::NONE;
        }
    }
    return result;
}   // findHitPointType

/**
 * Get the coordinates for a specified connection type.
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
//@Override
/*public*/ QPointF TrackSegmentView::getCoordsForConnectionType(HitPointType::TYPES connectionType) {
    QPointF result = getCentreSeg();
    if (connectionType == HitPointType::TRACK_CIRCLE_CENTRE) {
        result = getCoordsCenterCircle();
    } else if (HitPointType::isBezierHitType(connectionType)) {
        result = getBezierControlPoint(HitPointType::bezierPointIndex(connectionType));
    }
    return result;
}

/**
 * @return the bounds of this track segment
 */
//@Override
/*public*/ QRectF TrackSegmentView::getBounds() {
    QPointF ep1 = getCoordsCenter(), ep2 = getCoordsCenter();
    if (getConnect1() != nullptr) {
        ep1 = layoutEditor->getCoords(getConnect1(), getType1());
    }
    if (getConnect2() != nullptr) {
        ep2 = layoutEditor->getCoords(getConnect2(), getType2());
    }

    QRectF result = QRectF(ep1.x(), ep1.y(), 0, 0);
    MathUtil::add(result,ep2);

    if (isArc()) {
        MathUtil::add(result,getCentreSeg());
        if (isCircle()) {
            MathUtil::add(result,getCoordsCenterCircle());
        }
    } else if (isBezier()) {
        for (int index = 0; index < bezierControlPoints.size(); index++) {
            MathUtil::add(result,bezierControlPoints.at(index));
        }
    }
    MathUtil::add(result,getCoordsCenter());

    return result;
}

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
/*private*/ void TrackSegmentView::addNumericMenuItem(/*@Nonnull*/ QMenu* menu,
        /*@Nonnull*/ QString titleKey, /*@Nonnull*/ QString toolTipKey,
        /*@Nonnull*/ Supplier<int> val,
        /*@Nonnull*/ Consumer<int> set,
        /*@CheckForNull*/ Predicate<int> predicate) {
    int oldVal = val.get();
#if 0
    QAction* jmi;
    menu->addAction(jmi = new QAction(tr("%1:").arg(
            titleKey) + QString::number(oldVal), this));
    jmi->setToolTip(toolTipKey);
//    jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
    connect(jmi, &QAction::triggered, [=]{
        // prompt for lineWidth
        int newValue = QuickPromptUtil::promptForInteger(layoutEditor,
                titleKey,
                titleKey,
                // getting again, maybe something changed from the menu construction ?
                val.get(), predicate);
        set.accept(newValue);
        layoutEditor->repaint();
    });
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*protected*/ QMenu* TrackSegmentView::showPopup(/*@Nonnull*/ QGraphicsSceneMouseEvent* /*mouseEvent*/) {
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

 if (getBlockName().isEmpty()) {
     jmi = popupMenu->addSection(tr("No Block Set"));
 } else {
     jmi = popupMenu->addSection(tr("%1:").arg("Block") + getLayoutBlock()->getDisplayName());
 } jmi->setEnabled(false);

 // if there are any track connections
 QAction* act;

 if ((getConnect1() != nullptr) || (getConnect2() != nullptr)) {
     QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
     if (getConnect1() != nullptr)
     {
         connectionsMenu->addAction(act = new AbstractAction(tr(" %1: ").arg("1") + getConnect1()->getName(), this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
                 LayoutEditorFindItems* lf = layoutEditor->getFinder();
                 LayoutTrack* lt = lf->findObjectByName(getConnect1()->getName());
                 // this shouldn't ever be null... however...
                 if (lt != nullptr) {
                      LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                      layoutEditor->setSelectionRect(ltv->getBounds());
                     ltv->showPopup();
                 }
         });
     }
     if (getConnect2() != nullptr) {
         connectionsMenu->addAction(act =new AbstractAction(tr(" %1: ").arg("2") + getConnect2()->getName(),this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
                 LayoutEditorFindItems* lf = layoutEditor->getFinder();
                 LayoutTrack* lt = lf->findObjectByName(getConnect2()->getName());
                 // this shouldn't ever be null... however...
                 if (lt != nullptr) {
                  LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                  layoutEditor->setSelectionRect(ltv->getBounds());
                  ltv->showPopup();
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
     trackSegment->setMainline(mainlineCheckBoxMenuItem->isChecked());
 });
 mainlineCheckBoxMenuItem->setToolTip(tr("Sets track segment type - check for mainline track, uncheck for side track."));
 connect(mainlineCheckBoxMenuItem, &QAction::hovered, [=]{
     QToolTip::showText(QCursor::pos(), mainlineCheckBoxMenuItem->toolTip(), layoutEditor);
 });
 mainlineCheckBoxMenuItem->setChecked(trackSegment->isMainline());
#if 1
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
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeSideLeft(true);
     setBridgeSideRight(false);
 });
 jcbmi->setChecked(bridgeSideLeft && !bridgeSideRight);

 jcbmi = new QAction(tr("Right"),this);
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the right side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeSideRight(true);
     setBridgeSideLeft(false);
 });
 jcbmi->setChecked(!bridgeSideLeft && bridgeSideRight);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 bridgeSideMenu->addAction(jcbmi);
 bridgeSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeSideLeft(true);
     setBridgeSideRight(true);
 });
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
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeHasEntry(false);
     setBridgeHasExit(false);
 });
 jcbmi->setChecked(!bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("Entry"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the entry of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeHasEntry(true);
     setBridgeHasExit(false);
 });
 jcbmi->setChecked(bridgeHasEntry && !bridgeHasExit);

 jcbmi = new QAction(tr("Exit"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at the exit of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeHasExit(true);
     setBridgeHasEntry(false);
 });
 jcbmi->setChecked(!bridgeHasEntry && bridgeHasExit);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 bridgeEndMenu->addAction(jcbmi);
 bridgeEndActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setBridgeHasEntry(true);
     setBridgeHasExit(true);
 });
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
 connect(jmi, &QAction::triggered, [=]{
     //prompt for bridge line width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("DecorationLineWidthMenuItemTitle"),
             tr("DecorationLineWidthMenuItemTitle"),
             bridgeLineWidth);
     setBridgeLineWidth(newValue);
 });

 bridgeMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Approach Width") + " " + QString::number(bridgeApproachWidth)),this));
 jmi->setToolTip(tr("BridgeApproachWidthMenuItemToolTip"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for bridge approach width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("BridgeApproachWidthMenuItemTitle"),
             tr("BridgeApproachWidthMenuItemTitle"),
             bridgeApproachWidth);
     setBridgeApproachWidth(newValue);
 });

 bridgeMenu->addAction(jmi = new QAction(tr(" %1: ").arg(
         tr("Deck Width") + " "+ QString::number(bridgeDeckWidth)),this));
 jmi->setToolTip(tr("Select this to change the distance between the sides of the bridge decorations for this track"));
// jmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jmi, &QAction::triggered, [=]{
     //prompt for bridge deck width
     int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
             tr("BridgeDeckWidthMenuItemTitle"),
             tr("BridgeDeckWidthMenuItemTitle"),
             bridgeDeckWidth);
     setBridgeDeckWidth(newValue);
 });

 //
 // end bumper menus
 //
 //end bumper decorations can only be on end bumpers
 //
 bool hasEB1 = false;
 if (getType1() == HitPointType::POS_POINT) {
     PositionablePoint* pp = (PositionablePoint*) getConnect1();
     if (pp->getType() == PositionablePoint::END_BUMPER) {
         hasEB1 = true;
     }
 }
 bool hasEB2 = false;
 if (getType2() == HitPointType::POS_POINT) {
     PositionablePoint* pp = (PositionablePoint*) getConnect2();
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
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelSideLeft(false);
     setTunnelSideRight(false);
 });
 jcbmi->setChecked(!tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("Left"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the left side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelSideLeft(true);
     setTunnelSideRight(false);
 });
 jcbmi->setChecked(tunnelSideLeft && !tunnelSideRight);

 jcbmi = new QAction(tr("Right"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration to the right side of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelSideRight(true);
     setTunnelSideLeft(false);
 });
 jcbmi->setChecked(!tunnelSideLeft && tunnelSideRight);

 jcbmi = new QAction(tr("Both"));
 jcbmi->setCheckable(true);
 tunnelSideMenu->addAction(jcbmi);
 tunnelSideActionGroup->addAction(jcbmi);
 jcbmi->setToolTip(tr("Select this to add this decoration at both ends of this track"));
// jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
 connect(jcbmi, &QAction::triggered, [=]{
     setTunnelSideLeft(true);
     setTunnelSideRight(true);
 });
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
         layoutEditor->removeTrackSegment(trackSegment);
         remove();
         dispose();
 });

 popupMenu->addAction(act =new AbstractAction(tr("Split Track Segment"),this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
 connect(act, &QAction::triggered, [=]{
         splitTrackSegment();
//     }
 });
 //connect(act, SIGNAL(triggered(bool)), this, SLOT(splitTrackSegment()));

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
 if ((!getBlockName().isEmpty()) && (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled())) {
     popupMenu->addAction(act =new AbstractAction(tr("View Block Routing"),this));
// {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(act, &QAction::triggered, [=]{
             AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
             routeTableAction->actionPerformed(/*e*/);
     });
 }
#endif
 //popupMenu.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
 popupMenu->exec(QCursor::pos());
 return popupMenu;
}   // showPopup

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool TrackSegmentView::canRemove() {
    QList<QString> itemList = QList<QString>();

    HitPointType::TYPES type1Temp = getType1();
    LayoutTrack* conn1Temp = getConnect1();
    //itemList.addAll(getPointReferences(type1Temp, conn1Temp));
    for(QString s : getPointReferences(type1Temp, conn1Temp))
     itemList.append(s);

    HitPointType::TYPES type2Temp = getType2();
    LayoutTrack* conn2Temp = getConnect2();
    //itemList.addAll(getPointReferences(type2Temp, conn2Temp));
    for(QString s : getPointReferences(type2Temp, conn2Temp))
     itemList.append(s);

    if (!itemList.isEmpty()) {
        displayRemoveWarningDialog(itemList, "TrackSegment");  // NOI18N
    }
    return itemList.isEmpty();
}

/*public*/ QList<QString> TrackSegmentView::getPointReferences(HitPointType::TYPES type, LayoutTrack* conn) {
    QList<QString> result = QList<QString>();

    if (type == HitPointType::POS_POINT && qobject_cast<PositionablePoint*>(conn)) {
        PositionablePoint* pt = (PositionablePoint*) conn;
        if (!pt->getEastBoundSignal().isEmpty()) {
            result.append(pt->getEastBoundSignal());
        }
        if (!pt->getWestBoundSignal().isEmpty()) {
            result.append(pt->getWestBoundSignal());
        }
        if (!pt->getEastBoundSignalMastName().isEmpty()) {
            result.append(pt->getEastBoundSignalMastName());
        }
        if (!pt->getWestBoundSignalMastName().isEmpty()) {
            result.append(pt->getWestBoundSignalMastName());
        }
        if (!pt->getEastBoundSensorName().isEmpty()) {
            result.append(pt->getEastBoundSensorName());
        }
        if (!pt->getWestBoundSensorName().isEmpty()) {
            result.append(pt->getWestBoundSensorName());
        }
        if (pt->getType() == PositionablePoint::PointType::EDGE_CONNECTOR && pt->getLinkedPoint() != nullptr) {
            result.append(tr("DeleteECisActive"));   // NOI18N
        }
    }

    if (HitPointType::isTurnoutHitType(type) && qobject_cast<LayoutTurnout*>(conn)) {
        LayoutTurnout* lt = (LayoutTurnout*) conn;
        switch (type) {
            case HitPointType::TURNOUT_A: {
                result = lt->getBeanReferences("A");  // NOI18N
                break;
            }
            case HitPointType::TURNOUT_B: {
                result = lt->getBeanReferences("B");  // NOI18N
                break;
            }
            case HitPointType::TURNOUT_C: {
                result = lt->getBeanReferences("C");  // NOI18N
                break;
            }
            case HitPointType::TURNOUT_D: {
                result = lt->getBeanReferences("D");  // NOI18N
                break;
            }
            default: {
                log->error(tr("Unexpected HitPointType: %1").arg(type));
            }
        }
    }

    if (HitPointType::isLevelXingHitType(type) && qobject_cast<LevelXing*>(conn)) {
        LevelXing* lx = (LevelXing*) conn;
        switch (type) {
            case HitPointType::LEVEL_XING_A: {
                result = lx->getBeanReferences("A");  // NOI18N
                break;
            }
            case HitPointType::LEVEL_XING_B: {
                result = lx->getBeanReferences("B");  // NOI18N
                break;
            }
            case HitPointType::LEVEL_XING_C: {
                result = lx->getBeanReferences("C");  // NOI18N
                break;
            }
            case HitPointType::LEVEL_XING_D: {
                result = lx->getBeanReferences("D");  // NOI18N
                break;
            }
            default: {
         log->error(tr("Unexpected HitPointType: %1").arg(type));
            }
        }
    }

    if (HitPointType::isSlipHitType(type) && qobject_cast<LayoutSlip*>(conn)) {
        LayoutSlip* ls = (LayoutSlip*) conn;
        switch (type) {
            case HitPointType::SLIP_A: {
                result = ls->getBeanReferences("A");  // NOI18N
                break;
            }
            case HitPointType::SLIP_B: {
                result = ls->getBeanReferences("B");  // NOI18N
                break;
            }
            case HitPointType::SLIP_C: {
                result = ls->getBeanReferences("C");  // NOI18N
                break;
            }
            case HitPointType::SLIP_D: {
                result = ls->getBeanReferences("D");  // NOI18N
                break;
            }
            default: {
         log->error(tr("Unexpected HitPointType: %1").arg(type));
            }
        }
    }

    return result;
}

/**
 * split track segment into two track segments with an anchor between
 */
/*public*/ void TrackSegmentView::splitTrackSegment() {
    // create a new anchor
    QPointF p = getCentreSeg();
    PositionablePoint* newAnchor = layoutEditor->addAnchor(p);
    // link it to me
    layoutEditor->setLink(newAnchor, HitPointType::POS_POINT, trackSegment, HitPointType::TRACK);

    // get unique name for a new track segment
    QString name = layoutEditor->getFinder()->uniqueName("T", 1);

    // create it between the new anchor and my getConnect2()(/type2)
    TrackSegment* newTrackSegment = new TrackSegment(name,
            newAnchor, HitPointType::POS_POINT,
            getConnect2(), getType2(),
            trackSegment->isMainline(), layoutEditor);
    TrackSegmentView* ntsv = new TrackSegmentView(newTrackSegment,
            layoutEditor);
    log->error("temporary: splitTrackSegment created track without view, didn't include isDashed() ");
    // add it to known tracks
    layoutEditor->addLayoutTrack(newTrackSegment, ntsv);
    layoutEditor->setDirty();

    // copy attributes to new track segment
    newTrackSegment->setLayoutBlock(this->getLayoutBlock());
    ntsv->setArc(this->isArc());
    ntsv->setCircle(this->isCircle());
    // split any angle between the two new track segments
    ntsv->setAngle(this->getAngle() / 2.0);
    this->setAngle(this->getAngle() / 2.0);
    // newTrackSegment.setBezier(this->isBezier());
    ntsv->setFlip(this->isFlip());

    // copy over decorations
    QMap<QString, QString> d = QMap<QString, QString>();
    //this->getDecorations().forEach((k, v) ->
    QMapIterator<QString, QString> iter(*getDecorations());
    while(iter.hasNext())
    {
     iter.next();
     QString k = iter.key();
     QString v = iter.value();
        if (k == ("arrow")) {                // if this is an arrow
            if (this->isArrowEndStop()) {        // and it's on the stop end
                d.insert(k, v);                    // copy it to new track
                this->setArrowEndStop(false);    // and remove it from this track
            }
        } else if (k == ("bumper")) {        // if this is an end bumper
            if (this->isBumperEndStop()) {       // amd it's on the stop end
                d.insert(k, v);                    // copy it to new track
                this->setBumperEndStop(false);   // and remove it from this track
            }
        } else {                                // otherwise...
            d.insert(k, v);                        // copy to new track
        }
    }//);
    ntsv->setDecorations(decorations);

    // link my getConnect2() to the new track segment
    if (qobject_cast<PositionablePoint*>(getConnect2())) {
        PositionablePoint* pp = (PositionablePoint*) getConnect2();
        pp->replaceTrackConnection(trackSegment, newTrackSegment);
    } else {
        layoutEditor->setLink(getConnect2(), getType2(), newTrackSegment, HitPointType::TRACK);
    }

    // link the new anchor to the new track segment
    layoutEditor->setLink(newAnchor, HitPointType::POS_POINT, newTrackSegment, HitPointType::TRACK);

    // link me to the new newAnchor
    trackSegment->setConnect2(newAnchor, HitPointType::POS_POINT);

    // check on layout block
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
 *
 * @param e            The original event causing this
 * @param hitPointType the type of the underlying hit
 */
/*protected*/ void TrackSegmentView::showBezierPopUp(QGraphicsSceneMouseEvent* e, HitPointType::TYPES hitPointType) {
  int bezierControlPointIndex = HitPointType::bezierPointIndex(hitPointType);
  if (popupMenu != nullptr) {
      popupMenu->clear();
  } else {
      popupMenu = new QMenu();
  }

  /*QMenuItem* jmi =*/ popupMenu->addSection(tr("ControlPoint") + " #" + QString::number(bezierControlPointIndex));
  //jmi.setEnabled(false);
  popupMenu->addSeparator(); //new JSeparator(JSeparator.HORIZONTAL));

  if (bezierControlPoints.size() <= HitPointType::NUM_BEZIER_CONTROL_POINTS)
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

/*private*/ void TrackSegmentView::addBezierControlPointBefore(int index) {
    QPointF addPoint = getBezierControlPoint(index);
    if (index > 0) {
        addPoint = MathUtil::midPoint(getBezierControlPoint(index - 1), addPoint);
    } else {
        QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
        addPoint = MathUtil::midPoint(ep1, addPoint);
    }
    bezierControlPoints.insert(index, addPoint);
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}

/*private*/ void TrackSegmentView::addBezierControlPointAfter(int index) {
    int cnt = bezierControlPoints.size();
    QPointF addPoint = getBezierControlPoint(index);
    if (index < cnt - 1) {
        addPoint = MathUtil::midPoint(addPoint, getBezierControlPoint(index + 1));
        bezierControlPoints.insert(index + 1, addPoint);
    } else {
        QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());
        addPoint = MathUtil::midPoint(addPoint, ep2);
        bezierControlPoints.append(addPoint);
    }
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}

/*private*/ void TrackSegmentView::deleteBezierControlPoint(int index) {
    if ((index >= 0) && (index < bezierControlPoints.size())) {
        bezierControlPoints.removeAt(index);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

void TrackSegmentView::changeType(int choice) {
    switch (choice) {
        case 0: // plain track segment (line)
            setArc(false);
            setAngle(0.0);
            setCircle(false);
            setBezier(false);
            break;
        case 1: // circle
            setCircle(true);
            setArc(true);
//                setAngle(90.0D);
//                setBezier(false); // this is done in setCircle
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
                // TODO: Use MathUtil::intersect to find intersection of adjacent tracks
                // TODO: and place the control points halfway between that and the two endpoints

                // set default control point displacements
                QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
                QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());

                // compute orthogonal offset0 with length one third the distance from ep1 to ep2
                QPointF offset = MathUtil::subtract(ep2, ep1);
                offset = MathUtil::normalize(offset, MathUtil::length(offset) / 3.0);
                offset = MathUtil::orthogonal(offset);

                // add & subtract orthogonal offset0 to 1/3rd and 2/3rd points
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

/**
 * Clean up when this object is no longer needed.
 * <p>
 * Should not be called while the object is still displayed.
 *
 * @see #remove()
 */
/*public*/ void TrackSegmentView::dispose() {
    if (popupMenu != nullptr) {
        popupMenu->clear();
    }
    popupMenu = nullptr;
}

/**
 * Remove this object from display and persistance.
 */
/*public*/ void TrackSegmentView::remove() {
    // remove from persistance by flagging inactive
    active = false;
}


/**
 * Get state. "active" means that the object is still displayed, and should
 * be stored.
 *
 * @return true if active
 */
/*public*/ bool TrackSegmentView::isActive() {
    return active;
}


/**
 * @return true if HIDECON is not set and HIDECONALL is not set
 */
/*public*/ bool TrackSegmentView::isShowConstructionLines() {
    return (((showConstructionLine & HIDECON) != HIDECON)
            && ((showConstructionLine & HIDECONALL) != HIDECONALL));
}

/**
 * Method used by layoutEditor->
 * <p>
 * If the argument is
 * <ul>
 * <li>HIDECONALL then set HIDECONALL
 * <li>SHOWCON reset HIDECONALL is set, other wise set SHOWCON
 * <li>HIDECON or otherwise set HIDECON
 * </ul>
 * Then always redraw the LayoutEditor panel and set it dirty.
 *
 * @param hide The specification i.e. HIDECONALL, SHOWCON et al
 */
/*public*/ void TrackSegmentView::hideConstructionLines(int hide) {
    if (hide == HIDECONALL) {
        showConstructionLine |= HIDECONALL;
    } else if (hide == SHOWCON) {
        if ((showConstructionLine & HIDECONALL) == HIDECONALL) {
            showConstructionLine &= ~HIDECONALL;
        } else {
            showConstructionLine = hide;
        }
    } else {
        showConstructionLine = HIDECON;
    }
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
}

/**
 * @return true if SHOWCON is not set
 */
/*public*/ bool TrackSegmentView::hideConstructionLines() {
    return ((showConstructionLine & SHOWCON) != SHOWCON);
}


/*public*/ QPointF TrackSegmentView::getTmpPt1() {
    return pt1;
}

/*public*/ QPointF TrackSegmentView::getTmpPt2() {
    return pt2;
}

/*public*/ void TrackSegmentView::setTmpPt1(QPointF Pt1) {
    pt1 = Pt1;
    changed = true;
}

/*public*/ void TrackSegmentView::setTmpPt2(QPointF Pt2) {
    pt2 = Pt2;
    changed = true;
}


/*public*/ double TrackSegmentView::getCX() {
    return cX;
}

/*public*/ void TrackSegmentView::setCX(double CX) {
 if(CX == 0.)
  log->debug("x=0");
    cX = CX;
}


/*public*/ double TrackSegmentView::getCY() {
    return cY;
}

/*public*/ void TrackSegmentView::setCY(double CY) {
    cY = CY;
}


/*public*/ double TrackSegmentView::getCW() {
    return cW;
}

/*public*/ void TrackSegmentView::setCW(double CW) {
    cW = CW;
}


/*public*/ double TrackSegmentView::getCH() {
    return cH;
}

/*public*/ void TrackSegmentView::setCH(double CH) {
    cH = CH;
}


/*public*/ double TrackSegmentView::getStartAdj() {
    return startAdj;
}

/*public*/ void TrackSegmentView::setStartAdj(double startAdj) {
    this->startAdj = startAdj;
}

// this is the center of the track segment (it is "on" the track segment)
/*public*/ double TrackSegmentView::getCentreSegX() {
    return getCentreSeg().x();
}

/*public*/ void TrackSegmentView::setCentreSegX(double x) {
 if(x == 0.)
  log->debug("x=0");
 LayoutTrackView::setCoordsCenter(QPointF(x, getCentreSeg().y()));
}

/*public*/ double TrackSegmentView::getCentreSegY() {
    return getCentreSeg().y();
}

/*public*/ void TrackSegmentView::setCentreSegY(double y) {
    LayoutTrackView::setCoordsCenter(QPointF(getCentreSeg().x(), y));
}

/**
 * @return the location of the middle of the segment (on the segment)
 */
/*public*/ QPointF TrackSegmentView::getCentreSeg() {
    QPointF result = MathUtil::zeroPoint2D;

    if ((getConnect1() != nullptr) && (getConnect2() != nullptr)) {
        // get the end points
        QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
        QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());

        if (isCircle()) {
            result = getCoordsCenter();
        } else if (isArc()) {
            LayoutTrackView::setCoordsCenter(MathUtil::midPoint(ep1, ep2));
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
            result = MathUtil::add(getCoordsCenter(), delta);
        } else if (isBezier()) {
            // compute result Bezier point for (t == 0.5);
            // copy all the control points (including end points) into an array
            int len = bezierControlPoints.size() + 2;
            QVector<QPointF> points = QVector<QPointF>(len);
            points[0] = ep1;
            for (int idx = 1; idx < len - 1; idx++) {
                points[idx] = bezierControlPoints.at(idx - 1);
            }
            points[len - 1] = ep2;

            // calculate midpoints of all points (len - 1 order times)
            for (int idx = len - 1; idx > 0; idx--) {
                for (int jdx = 0; jdx < idx; jdx++) {
                    points[jdx] = MathUtil::midPoint(points[jdx], points[jdx + 1]);
                }
            }
            result = points[0];
        } else {
            result = MathUtil::midPoint(ep1, ep2);
        }
        if(result.isNull())
         log->debug("null point");
        LayoutTrackView::setCoordsCenter(result);
    }
    if(result.isNull())
     log->debug("null point");
    return result;
}

/*public*/ void TrackSegmentView::setCentreSeg(QPointF p) {
 if(p.isNull())
  log->debug("null point");
 LayoutTrackView::setCoordsCenter(p);
}


/*public*/ double TrackSegmentView::getCentreX() {
    return centreX;
}

/*public*/ void TrackSegmentView::setCentreX(double x) {
 if(x == 0.)
  log->debug("x = 0");
 centreX = x;
}

/*public*/ double TrackSegmentView::getCentreY() {
    return centreY;
}

/*public*/ void TrackSegmentView::setCentreY(double y) {
    centreY = y;
}

/*public*/ QPointF TrackSegmentView::getCentre() {
    return QPointF(centreX, centreY);
}


/*public*/ double TrackSegmentView::getTmpAngle() {
    return tmpangle;
}

/*public*/ void TrackSegmentView::setTmpAngle(double a) {
    tmpangle = a;
}

/**
 * get center coordinates
 *
 * @return the center coordinates
 */
/*public*/ QPointF TrackSegmentView::getCoordsCenterCircle() {
    //return getCentre();
 QPointF ctr = getCentre();
 if(ctr.isNull())
 {
  if(layoutEditor->layoutEditorComponent->initialized)
  {
  if(getConnect1() && getConnect2())
   calculateTrackSegmentAngle();
  ctr = getCentre();
  }
 }
 return ctr;
}

/**
 * set center coordinates
 *
 * @param p the coordinates to set
 */
/*public*/ void TrackSegmentView::setCoordsCenterCircle(QPointF p) {
    centreX = p.x();
    centreY = p.y();
}


/*public*/ double TrackSegmentView::getChordLength() {
    return chordLength;
}

/*public*/ void TrackSegmentView::setChordLength(double chord) {
    chordLength = chord;
}

/*
* Called when the user changes the angle dynamically in edit mode
* by dragging the centre of the cirle.
 */
/*protected*/ void TrackSegmentView::reCalculateTrackSegmentAngle(double x, double y) {
    if (!isBezier()) {
        double pt2x;
        double pt2y;
        double pt1x;
        double pt1y;

        if (isFlip()) {
            pt1x = getTmpPt2().x();
            pt1y = getTmpPt2().y();
            pt2x = getTmpPt1().x();
            pt2y = getTmpPt1().y();
        } else {
            pt1x = getTmpPt1().x();
            pt1y = getTmpPt1().y();
            pt2x = getTmpPt2().x();
            pt2y = getTmpPt2().y();
        }
        // Point 1 to new point distance
        double a;
        double o;
        double la;
        // Compute arc's chord
        a = pt2x - x;
        o = pt2y - y;
        la = hypot(a, o);

        double lb;
        a = pt1x - x;
        o = pt1y - y;
        lb = hypot(a, o);

        double newangle = qRadiansToDegrees(qAcos((-getChordLength() * getChordLength() + la * la + lb * lb) / (2 * la * lb)));
        setAngle(newangle);
    }
}

/*
* Calculate the initally parameters for drawing a circular track segment.
 */
/*protected*/ void TrackSegmentView::calculateTrackSegmentAngle() {
    QPointF pt1, pt2;
    if (isFlip()) {
        pt1 = layoutEditor->getCoords(getConnect2(), getType2());
        pt2 = layoutEditor->getCoords(getConnect1(), getType1());
    } else {
        pt1 = layoutEditor->getCoords(getConnect1(), getType1());
        pt2 = layoutEditor->getCoords(getConnect2(), getType2());
    }
    if ((getTmpPt1() != pt1) || (getTmpPt2() != pt2) || trackNeedsRedraw()) {
        setTmpPt1(pt1);
        setTmpPt2(pt2);

        double pt1x = pt1.x();
        double pt1y = pt1.y();
        double pt2x = pt2.x();
        double pt2y = pt2.y();

        if (getAngle() == 0.0) {
            setTmpAngle(90.0);
        } else {
            setTmpAngle(getAngle());
        }
        // Convert angle to radiants in order to speed up math
        double halfAngleRAD = qDegreesToRadians(getTmpAngle()) / 2.;

        // Compute arc's chord
        double a = pt2x - pt1x;
        double o = pt2y - pt1y;
        double chord = MathUtil::hypot(a, o);
        setChordLength(chord);

        // Make sure chord is not null
        // In such a case (ep1 == ep2), there is no arc to draw
        if (chord > 0.) {
            double radius = (chord / 2.) / qSin(halfAngleRAD);
            // Circle
            double startRad = qAtan2(a, o) - halfAngleRAD;
            setStartAdj(qRadiansToDegrees(startRad));
            if (isCircle()) {
                // Circle - Compute center
                setCentreX(pt2x - qCos(startRad) * radius);
                setCentreY(pt2y + qSin(startRad) * radius);

                // Circle - Compute rectangle required by Arc2D.Double
                setCW(radius * 2.0);
                setCH(radius * 2.0);
                setCX(getCentreX() - radius);
                setCY(getCentreY() - radius);

                // Compute where to locate the control circle on the circle segment
                QPointF offset = QPointF(
                        +radius * qCos(startRad + halfAngleRAD),
                        -radius * qSin(startRad + halfAngleRAD));
                setCentreSeg(MathUtil::add(getCentre(), offset));
            } else {
                // Ellipse - Round start angle to the closest multiple of 90
                setStartAdj(qRound(getStartAdj() / 90.0) * 90.0);
                // Ellipse - Compute rectangle required by Arc2D.Double
                setCW(qAbs(a) * 2.0);
                setCH(qAbs(o) * 2.0);
                // Ellipse - Adjust rectangle corner, depending on quadrant
                if (o * a < 0.0) {
                    a = -a;
                } else {
                    o = -o;
                }
                setCX(qMin(pt1x, pt2x) - qMax(a, 0.0));
                setCY(qMin(pt1y, pt2y) -qMax(o, 0.0));
            }
        }
    }
}   // calculateTrackSegmentAngle

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegmentView::draw1(EditScene* g2, bool isMain, bool isBlock) {
  if (!isBlock && isDashed() && getLayoutBlock() != nullptr) {
      // Skip the dashed rail layer, the block layer will display the dashed track
      // This removes random rail fragments from between the block dashes
      return;
  }
  //qApp->processEvents(QEventLoop::AllEvents, 100);

  QColor color;


  if(isMain == trackSegment->isMainline())
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
//    QPointF pt1 = layoutEditor->getCoords(getConnect1(), getType1());
//    QPointF pt2 = layoutEditor->getCoords(getConnect2(), getType2());

//    int cnt = bezierControlPoints.size();
    QVector<QPointF> points = getBezierControlPoints().toVector();
//    points.replace(0, pt1);
//    for (int idx = 0; idx < cnt; idx++) {
//        points.replace(idx + 1, bezierControlPoints.at(idx));
//    }
//    points.replace(cnt + 1, pt2);

    QPainterPath path = MathUtil::drawBezier( points);
    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
    pathItem->setPen(layoutEditor->drawingStroke);
    itemGroup->addToGroup(pathItem);
   }
   else
   {
    if(getConnect1() == nullptr || getConnect2() == nullptr)
     return;
    QPointF end1 = layoutEditor->getCoords(getConnect1(), getType1());
    QPointF end2 = layoutEditor->getCoords(getConnect2(), getType2());

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
/*protected*/ void TrackSegmentView::draw2(EditScene* g2, bool isMain, float railDisplacement) {
     if (isDashed() && getLayoutBlock() != nullptr) {
         // Skip the dashed rail layer, the block layer will display the dashed track
         // This removes random rail fragments from between the block dashes
         return;
     }

     if (isMain == trackSegment->isMainline()) {
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
             QPointF pt1 = layoutEditor->getCoords(getConnect1(), getType1());
             QPointF pt2 = layoutEditor->getCoords(getConnect2(), getType2());

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
             QPointF end1 = layoutEditor->getCoords(getConnect1(), getType1());
             QPointF end2 = layoutEditor->getCoords(getConnect2(), getType2());

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
/*protected*/ void TrackSegmentView::highlightUnconnected(EditScene* g2, HitPointType::TYPES selectedType) {
    // TrackSegments are always connected
    // nothing to see here... move along...
}

//@Override
/*protected*/ void TrackSegmentView::drawEditControls(EditScene* g2) {
  //g2.setColor(Color.black)
  QPen stroke = QPen(QColor(Qt::black), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin);
  QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

  invalidateItem(g2, rects);

  QGraphicsLineItem* lineItem;
  if (isShowConstructionLines())
  {
   QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
   QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());
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

  //g2.draw(layoutEditor.trackEditControlCircleAt(getCentreSeg()));
  QPointF ctr = getCentreSeg();
  QGraphicsEllipseItem* circleItem = trackEditControlCircleAt(ctr);
  circleItem->setPen(layoutEditor->drawingStroke);
  itemGroup->addToGroup(circleItem);
  rects = itemGroup;
  g2->addItem(rects);
}   // drawEditControls

//@Override
/*protected*/ void TrackSegmentView::drawTurnoutControls(EditScene* g2) {
    // TrackSegments don't have turnout controls...
    // nothing to see here... move along...
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::reCheckBlockBoundary() {
    // nothing to see here... move along...
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void TrackSegmentView::drawDecorations(EditScene* g2) {

//    log->trace(tr("TrackSegmentView: drawDecorations arrowStyle %1").arg(arrowStyle));
    QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
    invalidateItem(g2, decorationItems);

// get end points and calculate start/stop angles (in radians)
    QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
    QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());
    QPointF p1, p2, p3, p4, p5, p6, p7;
    QPointF p1P = ep1, p2P = ep2, p3P, p4P, p5P, p6P, p7P;
    double startAngleRAD, stopAngleRAD;
    if (isArc()) {
        calculateTrackSegmentAngle();
        double startAngleDEG = getStartAdj(), extentAngleDEG = getTmpAngle();
        startAngleRAD = (M_PI / 2.) - qDegreesToRadians(startAngleDEG);
        stopAngleRAD = (M_PI / 2.) - qDegreesToRadians(startAngleDEG + extentAngleDEG);
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
        startAngleRAD = (M_PI / 2.) - MathUtil::computeAngleRAD(cp0, ep1);
        stopAngleRAD = (M_PI / 2.) - MathUtil::computeAngleRAD(ep2, cpN);
    } else {
        startAngleRAD = (M_PI / 2.) - MathUtil::computeAngleRAD(ep2, ep1);
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

/*
* getBezierPoints
* @return the points to pass to MathUtil::drawBezier(...)
 */
/*@Nonnull*/
/*private*/ QList<QPointF> TrackSegmentView::getBezierPoints() {
    QPointF ep1 = layoutEditor->getCoords(getConnect1(), getType1());
    QPointF ep2 = layoutEditor->getCoords(getConnect2(), getType2());
    int cnt = bezierControlPoints.size() + 2;
    QVector<QPointF> points = QVector<QPointF>(cnt);
    points[0] = ep1;
    for (int idx = 0; idx < cnt - 2; idx++) {
        points[idx + 1] = bezierControlPoints.at(idx);
    }
    points[cnt - 1] = ep2;
    return points.toList();
}

/*private*/ int TrackSegmentView::drawArrow(
        EditScene* g2,
        QPointF ep,
        double angleRAD,
        bool dirOut,
        int offset, QPen stroke, QGraphicsItemGroup* itemGroup) {
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

/*======================*\
|* decoration accessors *|
\*======================*/
// Although the superclass LayoutTrack stores decorators in a Map,
// here we store them in specific variables like arrowStyle, bridgeSideRight, etc.
// We convert to and from the map during the getDecorations, setDecorations
// and hasDecorations calls.
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool TrackSegmentView::hasDecorations() {
    return ((arrowStyle > 0)
            || (bridgeSideLeft || bridgeSideRight)
            || (bumperEndStart || bumperEndStop)
            || (tunnelSideLeft || tunnelSideRight));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QMap<QString, QString>* TrackSegmentView::getDecorations() {
    if (decorations == nullptr) {
        decorations = new QMap<QString, QString>();
    } // if (decorathions != null)

    //
    // arrow decorations
    //
    if (arrowStyle > 0) {
        //<decoration name="arrow" value="double;both;linewidth=1;length=12;gap=1" />
        QList<QString> arrowValues = QList<QString>();

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
        arrowValues.append("linewidth=" + QString::number(arrowLineWidth));
        arrowValues.append("length=" + QString::number(arrowLength));
        arrowValues.append("gap=" + QString::number(arrowGap));
        //decorations->insert("arrow", String.join(";", arrowValues));
        decorations->insert("arrow",arrowValues.join(";"));
    }   // if (arrowCount > 0)

    //
    // bridge decorations
    //
    if (bridgeSideLeft || bridgeSideRight) {
        //<decoration name="bridge" value="both;linewidth=2;deckwidth=8" />
        QList<QString> bridgeValues = QList<QString>();

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
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::setDecorations(/*@Nonnull*/ QMap<QString, QString>* decorations) {
    QColor defaultTrackColor = layoutEditor->getDefaultTrackColorColor();
    LayoutTrackView::setDecorations(decorations);
    if (decorations != nullptr) {
        //for (Map.Entry<String, String> entry : decorations.entrySet())
        QMapIterator<QString, QString> entry(*decorations);
        while(entry.hasNext())
        {
         entry.next();
            log->debug(tr("Key = ''%1'', Value = ''%2''").arg(entry.key(), entry.value()));
            QString key = entry.key();
            //
            // arrow decorations
            //
            if (key == ("arrow")) {
                QString arrowValue = entry.value();
                //<decoration name="arrow" value="double;both;linewidth=1;length=12;gap=1" />
                bool atStart = true, atStop = true;
                bool hasIn = false, hasOut = false;
                int lineWidth = 1, length = 3, gap = 1, count = 1;
                QColor color = defaultTrackColor;
                QStringList values = arrowValue.split(";");
                for (QString value : values) {
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
                        color = QColor(valueString);
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = (valueString.toInt());
                    } else if (value.startsWith("length=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        length = (valueString.toInt());
                    } else if (value.startsWith("gap=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        gap = valueString.toInt();
                    } else {
                        log->debug(tr("arrow value ignored: %1").arg(value));
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
            // bridge decorations
            //
            else if (key == ("bridge")) {
                QString bridgeValue = entry.value();
                //<decoration name="bridge" value="both;linewidth=2;deckwidth=8" />
                // right/left default true; in/out default false
                bool hasLeft = true, hasRight = true, hasEntry = false, hasExit = false;
                int approachWidth = 4, lineWidth = 1, deckWidth = 2;
                QColor color = defaultTrackColor;
                QStringList values = bridgeValue.split(";");
                for (QString value : values) {
                    // log.info("value[{}]: ''{}''", i, value);
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
                        color = QColor(valueString);
                    } else if (value.startsWith("approachwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        approachWidth = valueString.toInt();
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = valueString.toInt();
                    } else if (value.startsWith("deckwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        deckWidth = valueString.toInt();
                    } else {
                        log->debug(tr("bridge value ignored: %1").arg(value));
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
            // bumper decorations
            //
            else if (key == ("bumper")) {
                QString bumperValue = entry.value();
//               if (getName() == ("T15")) {
//                   log.debug("STOP");
//               }
//<decoration name="bumper" value="double;linewidth=2;length=6;gap=2;flipped" />
                int lineWidth = 1, length = 4;
                bool isFlipped = false, atStart = true, atStop = true;
                QColor color = defaultTrackColor;
                QStringList values = bumperValue.split(";");
                for (QString value : values) {
                    // log.info("value[{}]: ''{}''", i, value);
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
                        color = QColor(valueString);
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = valueString.toInt();
                    } else if (value.startsWith("length=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        length = valueString.toInt();
                    } else {
                        log->debug(tr("bumper value ignored: %1").arg(value));
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
            // tunnel decorations
            //
            else if (key == ("tunnel")) {
                QString tunnelValue = entry.value();
                //<decoration name="tunnel" value="both;linewidth=2;floorwidth=8" />
                // right/left default true; in/out default false
                bool hasLeft = true, hasRight = true, hasIn = false, hasOut = false;
                int entranceWidth = 4, lineWidth = 1, floorWidth = 2;
                QColor color = defaultTrackColor;
                QStringList values = tunnelValue.split(";");
                for (QString value : values) {
                    // log.info("value[{}]: ''{}''", i, value);
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
                        color = QColor(valueString);
                    } else if (value.startsWith("entrancewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        entranceWidth = valueString.toInt();
                    } else if (value.startsWith("linewidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        lineWidth = valueString.toInt();
                    } else if (value.startsWith("floorwidth=")) {
                        QString valueString = value.mid(value.lastIndexOf("=") + 1);
                        floorWidth = valueString.toInt();
                    } else {
                        log->debug(tr("tunnel value ignored: %1").arg(value));
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
                log->debug(tr("Unknown decoration key: %1, value: %2").arg(key, entry.value()));
            }
        }   // for (Map.Entry<String, String> entry : decorations.entrySet())
    } // if (decorathions != null)
}   // setDirections

/**
 * Arrow decoration accessor. The 0 (none) and 1 through 5 arrow decorations
 * are keyed to files like
 * program:resources/icons/decorations/ArrowStyle1.png et al.
 *
 * @return Style number
 */
/*public*/ int TrackSegmentView::getArrowStyle() {
    return arrowStyle;
}

/**
 * Set the arrow decoration. The 0 (none) and 1 through 5 arrow decorations
 * are keyed to files like
 * program:resources/icons/decorations/ArrowStyle1.png et al.
 *
 * @param newVal the new style number
 */
/*public*/ void TrackSegmentView::setArrowStyle(int newVal) {
    log->trace(tr("TrackSegmentView:setArrowStyle %1 %2 %3").arg(newVal).arg(arrowEndStart?"true":"false", arrowEndStop?"true":"false"));
    if (arrowStyle != newVal) {
        if (newVal > 0) {
            if (!arrowEndStart && !arrowEndStop) {
                arrowEndStart = true;
                arrowEndStop = true;
            }
            if (!arrowDirIn && !arrowDirOut) {
                arrowDirOut = true;
            }
        } else {
            newVal = 0; // only positive styles allowed!
        }
        arrowStyle = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isArrowEndStart() {
    return arrowEndStart;
}

/*public*/ void TrackSegmentView::setArrowEndStart(bool newVal) {
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

/*public*/ bool TrackSegmentView::isArrowEndStop() {
    return arrowEndStop;
}

/*public*/ void TrackSegmentView::setArrowEndStop(bool newVal) {
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

/*public*/ bool TrackSegmentView::isArrowDirIn() {
    return arrowDirIn;
}

/*public*/ void TrackSegmentView::setArrowDirIn(bool newVal) {
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
/*public*/ bool TrackSegmentView::isArrowDirOut() {
    return arrowDirOut;
}

/*public*/ void TrackSegmentView::setArrowDirOut(bool newVal) {
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

/*public*/ QColor TrackSegmentView::getArrowColor() {
    return arrowColor;
}

/*public*/ void TrackSegmentView::setArrowColor(QColor newVal) {
    if (arrowColor != newVal) {
        arrowColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getArrowLineWidth() {
    return arrowLineWidth;
}

/*public*/ void TrackSegmentView::setArrowLineWidth(int newVal) {
    if (arrowLineWidth != newVal) {
        arrowLineWidth = MathUtil::pin(newVal, 1, MAX_ARROW_LINE_WIDTH);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getArrowLength() {
    return arrowLength;
}

/*public*/ void TrackSegmentView::setArrowLength(int newVal) {
    if (arrowLength != newVal) {
        arrowLength = MathUtil::pin(newVal, 2, MAX_ARROW_LENGTH);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getArrowGap() {
    return arrowGap;
}

/*public*/ void TrackSegmentView::setArrowGap(int newVal) {
    if (arrowGap != newVal) {
        arrowGap = MathUtil::pin(newVal, 0, MAX_ARROW_GAP);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

//
// bridge decoration accessors
//
/*public*/ bool TrackSegmentView::isBridgeSideRight() {
    return bridgeSideRight;
}

/*public*/ void TrackSegmentView::setBridgeSideRight(bool newVal) {
    if (bridgeSideRight != newVal) {
        bridgeSideRight = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isBridgeSideLeft() {
    return bridgeSideLeft;
}

/*public*/ void TrackSegmentView::setBridgeSideLeft(bool newVal) {
    if (bridgeSideLeft != newVal) {
        bridgeSideLeft = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isBridgeHasEntry() {
    return bridgeHasEntry;
}

/*public*/ void TrackSegmentView::setBridgeHasEntry(bool newVal) {
    if (bridgeHasEntry != newVal) {
        bridgeHasEntry = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isBridgeHasExit() {
    return bridgeHasExit;
}

/*public*/ void TrackSegmentView::setBridgeHasExit(bool newVal) {
    if (bridgeHasExit != newVal) {
        bridgeHasExit = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegmentView::getBridgeColor() {
    return bridgeColor;
}

/*public*/ void TrackSegmentView::setBridgeColor(QColor newVal) {
    if (bridgeColor != newVal) {
        bridgeColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getBridgeDeckWidth() {
    return bridgeDeckWidth;
}

/*public*/ void TrackSegmentView::setBridgeDeckWidth(int newVal) {
    if (bridgeDeckWidth != newVal) {
        bridgeDeckWidth = qMax(MIN_BRIDGE_DECK_WIDTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getBridgeLineWidth() {
    return bridgeLineWidth;
}

/*public*/ void TrackSegmentView::setBridgeLineWidth(int newVal) {
    if (bridgeLineWidth != newVal) {
        bridgeLineWidth = qMax(MIN_BRIDGE_LINE_WIDTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getBridgeApproachWidth() {
    return bridgeApproachWidth;
}

/*public*/ void TrackSegmentView::setBridgeApproachWidth(int newVal) {
    if (bridgeApproachWidth != newVal) {
        bridgeApproachWidth = qMax(MIN_BRIDGE_APPROACH_WIDTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

//
// bumper decoration accessors
//
/*public*/ bool TrackSegmentView::isBumperEndStart() {
    return bumperEndStart;
}

/*public*/ void TrackSegmentView::setBumperEndStart(bool newVal) {
    if (bumperEndStart != newVal) {
        bumperEndStart = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isBumperEndStop() {
    return bumperEndStop;
}

/*public*/ void TrackSegmentView::setBumperEndStop(bool newVal) {
    if (bumperEndStop != newVal) {
        bumperEndStop = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegmentView::getBumperColor() {
    return bumperColor;
}

/*public*/ void TrackSegmentView::setBumperColor(QColor newVal) {
    if (bumperColor != newVal) {
        bumperColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getBumperLineWidth() {
    return bumperLineWidth;
}

/*public*/ void TrackSegmentView::setBumperLineWidth(int newVal) {
    if (bumperLineWidth != newVal) {
        bumperLineWidth = MathUtil::pin(newVal, 1, MAX_BUMPER_LINE_WIDTH);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}


/*public*/ int TrackSegmentView::getBumperLength() {
    return bumperLength;
}

/*public*/ void TrackSegmentView::setBumperLength(int newVal) {
    if (bumperLength != newVal) {
        bumperLength = qMax(MIN_BUMPER_LENGTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isBumperFlipped() {
    return bumperFlipped;
}

/*public*/ void TrackSegmentView::setBumperFlipped(bool newVal) {
    if (bumperFlipped != newVal) {
        bumperFlipped = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*private*/ void TrackSegmentView::setupDefaultBumperSizes(/*@Nonnull*/ LayoutEditor* layoutEditor) {
    LayoutTrackDrawingOptions* ltdo = layoutEditor->getLayoutTrackDrawingOptions();

    // use these as default sizes for end bumpers
    int tieLength = ltdo->getSideTieLength();
    int tieWidth = ltdo->getSideTieWidth();
    int railWidth = ltdo->getSideRailWidth();
    int railGap = ltdo->getSideRailGap();
    if (trackSegment->isMainline()) {
        tieLength = ltdo->getMainTieLength();
        tieWidth = ltdo->getMainTieWidth();
        railWidth = ltdo->getMainRailWidth();
        railGap = ltdo->getMainRailGap();
    }

    bumperLineWidth = qMax(railWidth, ltdo->getMainBlockLineWidth()) * 2;
    bumperLength = railGap + (2 * railWidth);
    if ((tieLength > 0) && (tieWidth > 0)) {
        bumperLineWidth = tieWidth;
        bumperLength = tieLength * 3 / 2;
    }
    bumperLineWidth = qMax(MIN_BUMPER_LINE_WIDTH, bumperLineWidth); // don't let value be less than MIN
    bumperLength = qMax(MIN_BUMPER_LENGTH, bumperLength);// don't let value be less than MIN
}

//
// tunnel decoration accessors
//
/*public*/ bool TrackSegmentView::isTunnelSideRight() {
    return tunnelSideRight;
}

/*public*/ void TrackSegmentView::setTunnelSideRight(bool newVal) {
    if (tunnelSideRight != newVal) {
        tunnelSideRight = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isTunnelSideLeft() {
    return tunnelSideLeft;
}

/*public*/ void TrackSegmentView::setTunnelSideLeft(bool newVal) {
    if (tunnelSideLeft != newVal) {
        tunnelSideLeft = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isTunnelHasEntry() {
    return tunnelHasEntry;
}

/*public*/ void TrackSegmentView::setTunnelHasEntry(bool newVal) {
    if (tunnelHasEntry != newVal) {
        tunnelHasEntry = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ bool TrackSegmentView::isTunnelHasExit() {
    return tunnelHasExit;
}

/*public*/ void TrackSegmentView::setTunnelHasExit(bool newVal) {
    if (tunnelHasExit != newVal) {
        tunnelHasExit = newVal;
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ QColor TrackSegmentView::getTunnelColor() {
    return tunnelColor;
}

/*public*/ void TrackSegmentView::setTunnelColor(QColor newVal) {
    if (tunnelColor != newVal) {
        tunnelColor = newVal;
        JmriColorChooser::addRecentColor(newVal);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getTunnelFloorWidth() {
    return tunnelFloorWidth;
}

/*public*/ void TrackSegmentView::setTunnelFloorWidth(int newVal) {
    if (tunnelFloorWidth != newVal) {
        tunnelFloorWidth = qMax(MIN_TUNNEL_FLOOR_WIDTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getTunnelLineWidth() {
    return tunnelLineWidth;
}

/*public*/ void TrackSegmentView::setTunnelLineWidth(int newVal) {
    if (tunnelLineWidth != newVal) {
        tunnelLineWidth = qMax(MIN_TUNNEL_LINE_WIDTH, newVal);   // don't let value be less than MIN
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/*public*/ int TrackSegmentView::getTunnelEntranceWidth() {
    return tunnelEntranceWidth;
}

/*public*/ void TrackSegmentView::setTunnelEntranceWidth(int newVal) {
    if (tunnelEntranceWidth != newVal) {
        tunnelEntranceWidth = qMax(MIN_TUNNEL_ENTRANCE_WIDTH, newVal);   // don't let value be less than 1
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*protected*/ QList<LayoutConnectivity*> TrackSegmentView::getLayoutConnectivity() {
    return trackSegment->getLayoutConnectivity();
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*public*/ QList<HitPointType::TYPES> TrackSegmentView::checkForFreeConnections() {
    return QList<HitPointType::TYPES>();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool TrackSegmentView::checkForUnAssignedBlocks() {
    return (getLayoutBlock() != nullptr);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *> *> blockNamesToTrackNameSetsMap) {
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
    QList<QSet<QString>*>* trackNameSets = nullptr;
    QSet<QString>* trackNameSet = nullptr;    // assume not found (pessimist!)
    QString blockName = getBlockName();
    if (!blockName.isEmpty()) {
        trackNameSets = blockNamesToTrackNameSetsMap.value(blockName);
        if (trackNameSets != nullptr) { //(#1)
            for (QSet<QString>* checkTrackNameSet : *trackNameSets) {
                if (checkTrackNameSet->contains(getName())) { //(#2)
                    trackNameSet = checkTrackNameSet;
                    break;
                }
            }
        } else {    //(#3)
            log->debug(tr("*New block (''%1'') trackNameSets").arg(blockName));
            trackNameSets = new QList<QSet<QString>*>();
            blockNamesToTrackNameSetsMap.insert(blockName, trackNameSets);
        }
        if (trackNameSet == nullptr) {
            trackNameSet = new QSet<QString>();
            trackNameSets->append(trackNameSet);
        }
//        if (trackNameSet->insert(getName())) {
//            log.debug("*    Add track ''{}'' to TrackNameSets for block ''{}''", getName(), blockName);
//        }
        trackNameSet->insert(getName());
        //(#4)
        if (getConnect1() != nullptr) {
            getConnect1()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
        }
        if (getConnect2() != nullptr) { //(#4)
            getConnect2()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/QString blockName,
        /*@Nonnull*/ QSet<QString> *trackNameSet) {
    if (!trackNameSet->contains(getName())) {
        // is this the blockName we're looking for?
        if (getBlockName() == (blockName)) {
            // if we are added to the TrackNameSet
//            if (trackNameSet.add(getName())) {
//                log.debug("*    Add track ''{}''for block ''{}''", getName(), blockName);
//            }
            trackNameSet->insert(getName());
            // these should never be null... but just in case...
            // it's time to play... flood your neighbours!
            if (getConnect1() != nullptr) {
                getConnect1()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
            }
            if (getConnect2() != nullptr) {
                getConnect2()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
            }
        }
    }
}
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void TrackSegmentView::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    setLayoutBlock(layoutBlock);
}
/*private*/ /*final*/ /*static*/ Logger* TrackSegmentView::log = LoggerFactory::getLogger("TrackSegmentView");
