#include "layouttrackview.h"
#include "loggerfactory.h"
#include "layoutrhturnout.h"
#include "layoutlhturnout.h"
#include "layoutwye.h"
#include "layoutxover.h"
#include "layoutrhxover.h"
#include "layoutlhxover.h"
#include "layoutrhturnoutview.h"
#include "layoutlhturnoutview.h"
#include "layoutwyeview.h"
#include "layoutrhxoverview.h"
#include "layoutdoublexover.h"
#include "layoutxoverview.h"
#include "layoutlhxoverview.h"
#include "layoutdoublexoverview.h"
#include "layoutslip.h"
#include "layoutsingleslip.h"
#include "layoutdoubleslip.h"
#include "layoutslipview.h"
#include "layoutsingleslipview.h"
#include "layoutdoubleslipview.h"
#include "tracksegment.h"
#include "tracksegmentview.h"
#include "tracksegmentview.h"
#include "levelxingview.h"
#include "positionablepointview.h"
#include "layoutturntableview.h"
#include "joptionpane.h"
#include "jcheckboxmenuitem.h"
#include "fileutil.h"

/**
 * MVC View component for the LayoutTrack hierarchy.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutTrackView {

/**
 * Constructor method.
 * @param track the layout track to view.
 */
/*public*/ LayoutTrackView::LayoutTrackView(/*@Nonnull*/ LayoutTrack* track, /*@Nonnull*/ LayoutEditor* layoutEditor) {
     this->layoutTrack = track;
 this->layoutEditor = layoutEditor;
}

/**
 * constructor method
 *
 * @param track        the track to view
 * @param c            display location
 * @param layoutEditor for reference to tools
 */
/*public*/ LayoutTrackView::LayoutTrackView(/*@Nonnull*/ LayoutTrack* track, /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor) {
    this->layoutTrack = track;
    this->layoutEditor = layoutEditor;
    this->center = c;
}
#if 0
// temporary method to get a correct-type *View or subclass.
// Eventually, this will go away once *View's are created
// in a type-specific way with their underlying model objects
// @Deprecated // should be made not necessary
/*@Nonnull*/
/*static*/ /*public*/ LayoutTrackView* LayoutTrackView::makeTrackView(/*@Nonnull*/ LayoutTrack* trk) {

    if (qobject_cast<LayoutTurnout*>(trk)) {

        if (qobject_cast<LayoutRHTurnout*>(trk)) { return new LayoutRHTurnoutView((LayoutRHTurnout*)trk); }
        if (qobject_cast<LayoutLHTurnout*>(trk)) { return new LayoutLHTurnoutView((LayoutLHTurnout*)trk); }
        if (qobject_cast<LayoutWye*>(trk)) { return new LayoutWyeView((LayoutWye*)trk); }

        if (qobject_cast<LayoutXOver*>(trk)) {
            if (qobject_cast<LayoutRHXOver*>(trk)) { return new LayoutRHXOverView((LayoutRHXOver*)trk); }
            if (qobject_cast<LayoutLHXOver*>(trk)) { return new LayoutLHXOverView((LayoutLHXOver*)trk); }
            if (qobject_cast<LayoutDoubleXOver*>(trk)) { return new LayoutDoubleXOverView((LayoutDoubleXOver*)trk); }

            return new LayoutXOverView((LayoutXOver*)trk);
        }

        if (qobject_cast<LayoutSlip*>(trk)) {
            if (qobject_cast<LayoutSingleSlip*>(trk)) { return new LayoutSingleSlipView((LayoutSingleSlip*)trk); }
            if (qobject_cast<LayoutDoubleSlip*>(trk)) { return new LayoutDoubleSlipView((LayoutDoubleSlip*)trk); }

            return new LayoutSlipView((LayoutSlip*)trk);
        }

        return new LayoutTurnoutView((LayoutTurnout*)trk);
    }
    if (qobject_cast<TrackSegment*>(trk)) { return new TrackSegmentView((TrackSegment*)trk); }
    if (qobject_cast<PositionablePoint*>(trk)) { return new PositionablePointView((PositionablePoint*)trk); }
    if (qobject_cast<LevelXing*>(trk)) { return new LevelXingView((LevelXing*)trk); }
    if (qobject_cast<LayoutTurntable*>(trk)) { return new LayoutTurntableView((LayoutTurntable*)trk); }

    log->error(tr("makeTrackView did not match type of %1").arg(trk->metaObject()->className()),  Exception("traceback"));
    return new LayoutTrackView(trk);
}
#endif
/*@Nonnull*/
/*final*/ /*public*/ QString LayoutTrackView::getId() {
    return layoutTrack->getId();
}
/*@Nonnull*/
/*final*/ /*public*/ QString LayoutTrackView::getName() {
    return layoutTrack->getName();
}

/*final*/ /*protected*/ void LayoutTrackView::setIdent(/*@Nonnull*/ QString ident) {
    layoutTrack->setIdent(ident);
}

// temporary accessor?  Or is this a long term thing?
// @Nonnull temporary until we gigure out if can be null or not
/*public*/ LayoutTrack* LayoutTrackView::getLayoutTrack() {
    return layoutTrack;
}


/**
 * Set center coordinates.
 * <p>
 * Some subtypes may reimplement this is "center" is a more complicated
 * idea, i.e. for Bezier curves
 *
 * @param p the coordinates to set
 */
/*public*/ void LayoutTrackView::setCoordsCenter(/*@Nonnull*/ QPointF p) {  // temporary = want to make protected after migration
    center = p;
}

// These now reflect to code in the base class; eventually this heirarchy will
// expand and the code will be brought here

/*public*/ bool LayoutTrackView::hasDecorations() {
    return false;
}
/*final*/ /*public*/ QPointF LayoutTrackView::getCoordsCenter() { // final for efficiency
    return center;
}

/*public*/ QMap<QString, QString>* LayoutTrackView::getDecorations() {
    return decorations;
}
/*public*/ bool LayoutTrackView::isMainline() {
    return layoutTrack->isMainline();
}

/**
 * Set new decorations
 *
 * This is a complete replacement of the decorations, not an appending.
 *
 * @param decorations A map from strings ("arrow", "bridge", "bumper",..) to
 *                    specific value strings ("single", "entry;right", ),
 *                    perhaps including multiple values separated by
 *                    semicolons.
 */
/*public*/ void LayoutTrackView::setDecorations(QMap<QString, QString>* decorations) {
    this->decorations = decorations;
}

/**
 * convenience method for accessing...
 *
 * @return the layout editor's toolbar panel
 */
//@Nonnull
/*final*/ /*public*/ LayoutEditorToolBarPanel* LayoutTrackView::getLayoutEditorToolBarPanel() {
    return layoutEditor->getLayoutEditorToolBarPanel();
}

// these are convenience methods to return circles & rectangle used to draw onscreen
//
// compute the control point rect at inPoint; use the turnout circle size
/*final*/ /*public*/ QGraphicsEllipseItem* LayoutTrackView::trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint) {
    return trackControlCircleAt(inPoint);
}

// compute the turnout circle at inPoint (used for drawing)
/*final*/ /*public*/ QGraphicsEllipseItem* LayoutTrackView::trackControlCircleAt(/*@Nonnull*/ QPointF inPoint) {
 if(inPoint.isNull())
  log->debug("null point");
 return new QGraphicsEllipseItem(inPoint.x() - layoutEditor->circleRadius,
            inPoint.y() - layoutEditor->circleRadius,
            layoutEditor->circleDiameter, layoutEditor->circleDiameter);
}

// compute the turnout circle control rect at inPoint
/*final*/ /*public*/ QGraphicsRectItem* LayoutTrackView::trackControlCircleRectAt(/*@Nonnull*/ QPointF inPoint) {
    return new QGraphicsRectItem(inPoint.x() - layoutEditor->circleRadius,
            inPoint.y() - layoutEditor->circleRadius,
            layoutEditor->circleDiameter, layoutEditor->circleDiameter);
}

/*final*/ /*protected*/ QColor LayoutTrackView::getColorForTrackBlock(
        /*@CheckForNull*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor) {
    QColor result = ColorUtil::CLEAR;  // transparent
    if (layoutBlock != nullptr) {
        if (forceBlockTrackColor) {
            result = layoutBlock->getBlockTrackColor();
        } else {
            result = layoutBlock->getBlockColor();
        }
    }
    return result;
}

// optional parameter forceTrack = false
/*final*/ /*protected*/ QColor LayoutTrackView::getColorForTrackBlock(/*@CheckForNull*/ LayoutBlock* lb) {
    return getColorForTrackBlock(lb, false);
}

/*final*/ /*protected*/ QColor LayoutTrackView::setColorForTrackBlock(EditScene* g2,
        /*@CheckForNull*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor) {
    QColor result = getColorForTrackBlock(layoutBlock, forceBlockTrackColor);
    //g2->setColor(result);
    return result;
}

// optional parameter forceTrack = false
/*final*/ /*protected*/ QColor LayoutTrackView::setColorForTrackBlock(EditScene* g2, /*@CheckForNull*/ LayoutBlock* lb) {
    return setColorForTrackBlock(g2, lb, false);
}

///*protected*/ void LayoutTrackView::drawEditControls(EditScene* g2) {
//    layoutTrack->drawEditControls(g2);
//}

///*protected*/ void LayoutTrackView::draw1(EditScene *g2, bool isMain, bool isBlock) {
//    layoutTrack->draw1(g2, isMain, isBlock);
//}

///*protected*/ void LayoutTrackView::draw2(EditScene* g2, bool isMain, float railDisplacement) {
//    layoutTrack->draw2(g2, isMain, railDisplacement);
//}
/**
 * draw hidden track
 *
 * @param g2 the graphics context
 */
// abstract protected void drawHidden(Graphics2D g2);
// note: placeholder until I get this implemented in all sub-classes
// TODO: replace with abstract declaration (above)
/*final*/ /*protected*/ void drawHidden(EditScene* g2) {
    // nothing to do here... move along...
}

/**
 * draw the text for this layout track
 * @param g
 * note: currently can't override (final); change this if you need to
 */
/*final*/ /*protected*/ void LayoutTrackView::drawLayoutTrackText(EditScene* g) {
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 invalidateItem(g, labels);

    // get the center coordinates
    int x = (int) center.x(), y = (int) center.y();

    // get the name of this track
    QString name = getName();
#if 1 // TODO:
    // get the FontMetrics
    QFontMetrics metrics = QFontMetrics(/*g->font()*/textFont);

    // determine the X coordinate for the text
    //x -= metrics.stringWidth(name) / 2;
    QRect boundingRect = metrics.boundingRect(name);
    x= boundingRect.width() / 2;

    // determine the Y coordinate for the text
    //y += metrics.getHeight() / 2;
    y += boundingRect.height() / 2;

    // (note we add the ascent, as in java 2d 0 is top of the screen)
    //y += (int) metrics.getAscent();

    //g->drawString(name, x, y);
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(boundingRect.x() + center.x(), boundingRect.y() + center.y());
    io->setPlainText(name);
    io->setDefaultTextColor(textColor);
    io->setFont(textFont);

    itemGroup->addToGroup(io);
    labels  = itemGroup;
    g->addItem(labels);
#endif
}

/*protected*/ void LayoutTrackView::drawLayoutTrackText(EditScene* g, QColor c, QFont f)
{
 textColor = c;
 textFont = f;
 drawLayoutTrackText(g);
}
/**
     * Load a file for a specific arrow ending.
     *
     * @param n               The arrow type as a number
     * @param arrowsCountMenu menu containing the arrows to set visible
     *                        selection
     * @return An item for the arrow menu
     */
    /*public*/ JCheckBoxMenuItem* LayoutTrackView::loadArrowImageToJCBItem(int n, QMenu* arrowsCountMenu) {
        ImageIcon* imageIcon = new ImageIcon(FileUtil::findURL("program:resources/icons/decorations/ArrowStyle" + QString::number(n) + ".png"));
        JCheckBoxMenuItem* jcbmi = new JCheckBoxMenuItem(imageIcon, this);
        arrowsCountMenu->addAction(jcbmi);
        jcbmi->setToolTip(tr("Select the style of arrow decorations to add to this track"));
        // can't set selected here because the ActionListener has to be set first
        return jcbmi;
    }

    /**
     * highlight unconnected connections
     *
     * @param g2           the graphics context
     * @param specificType the specific connection to draw (or NONE for all)
     */
//    /*abstract*/ /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType);

    // optional parameter specificType = NONE
    /*final*/ /*protected*/ void LayoutTrackView::highlightUnconnected(EditScene* g2) {
        highlightUnconnected(g2, HitPointType::NONE);
    }

/**
 * Draw track decorations
 *
 * @param g2 the graphics context
 */
//*abstract*/ /*protected*/ void drawDecorations(EditScene* g2);

/**
 * Get the hidden state of the track element.
 *
 * @return true if hidden; false otherwise
 */
/*final*/ /*public*/ bool LayoutTrackView::isHidden() {
    return hidden;
}

/*public*/ void LayoutTrackView::setHidden(bool hide) {
 if (hidden != hide) {
     hidden = hide;
     if (layoutEditor != nullptr) {
         layoutEditor->redrawPanel();
     }
 }
}
/*
* non-accessor methods
 */
/**
 * get turnout state string
 *
 * @param turnoutState of the turnout
 * @return the turnout state string
 */
/*final*/ /*public*/ QString LayoutTrackView::getTurnoutStateString(int turnoutState) {
    QString result = "";
    if (turnoutState == Turnout::CLOSED) {
        result = tr("Closed");
    } else if (turnoutState == Turnout::THROWN) {
        result = tr("Thrown");
    } else {
        result = tr("Unknown");
    }
    return result;
}

/**
 * Check for active block boundaries.
 * <p>
 * If any connection point of a layout track object has attached objects,
 * such as signal masts, signal heads or NX sensors, the layout track object
 * cannot be deleted.
 *
 * @return true if the layout track object can be deleted.
 */
//abstract public boolean canRemove();

/**
 * Display the attached items that prevent removing the layout track item.
 *
 * @param itemList A list of the attached heads, masts and/or sensors.
 * @param typeKey  The object type such as Turnout, Level Crossing, etc.
 */
/*final*/ /*public*/ void LayoutTrackView::displayRemoveWarningDialog(QList<QString> itemList, QString typeKey) {
    itemList.sort(/*nullptr*/);
    QString msg = tr("%1:").arg( // NOI18N
            tr("Unable to delete the %1.\nThe following items will need to be removed first").arg(typeKey));  // NOI18N
    for (QString item : itemList) {
        msg.append("\n    " + item);  // NOI18N
    }
    JOptionPane::showMessageDialog(layoutEditor,
            msg,
            tr("Warning"), // NOI18N
            JOptionPane::WARNING_MESSAGE);
}

/**
 * scale this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to scale X coordinates
 * @param yFactor the amount to scale Y coordinates
 */
// abstract public void scaleCoords(double xFactor, double yFactor);

/**
 * translate this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to translate X coordinates
 * @param yFactor the amount to translate Y coordinates
 */
// abstract public void translateCoords(double xFactor, double yFactor);

/**
 * rotate this LayoutTrack's coordinates by angleDEG's
 *
 * @param angleDEG the amount to rotate in degrees
 */
// abstract public void rotateCoords(double angleDEG);

/*final*/ /*protected*/ QPointF LayoutTrackView::rotatePoint(/*@Nonnull*/ QPointF p, double sineRot, double cosineRot) {
    double cX = center.x();
    double cY = center.y();

    double deltaX = p.x() - cX;
    double deltaY = p.y() - cY;

    double x = cX + cosineRot * deltaX - sineRot * deltaY;
    double y = cY + sineRot * deltaX + cosineRot * deltaY;

    return QPointF(x, y);
}

/**
 * find the hit (location) type for a point
 *
 * @param hitPoint           the point
 * @param useRectangles      whether to use (larger) rectangles or (smaller)
 *                           circles for hit testing
 * @param requireUnconnected whether to only return hit types for free
 *                           connections
 * @return the location type for the point (or NONE)
 * @since 7.4.3
 */
///*abstract*/ /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF hitPoint,
//                                                bool useRectangles,
//                                                bool requireUnconnected);

// optional useRectangles & requireUnconnected parameters default to false
/*final*/ /*protected*/ HitPointType::TYPES LayoutTrackView::findHitPointType(/*@Nonnull*/ QPointF p) {
    return findHitPointType(p, false, false);
}

// optional requireUnconnected parameter defaults to false
/*final*/ /*protected*/ HitPointType::TYPES LayoutTrackView::findHitPointType(/*@Nonnull*/ QPointF p, bool useRectangles) {
    return findHitPointType(p, useRectangles, false);
}

/**
 * return the coordinates for a specified connection type (abstract: should
 * be overridden by ALL subclasses)
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
// /*abstract*/ /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType);

/**
 * @return the bounds of this track
 */
// /*abstract*/ /*public*/ QRectF getBounds();

/**
 * show the popup menu for this layout track
 *
 * @param mouseEvent the mouse down event that triggered this popup
 * @return the popup menu for this layout track
 */
//@Nonnull
// /*abstract*/ /*protected*/ QMenu* showPopup(/*@Nonnull*/ QGraphicsSceneMouseEvent* mouseEvent);

/**
 * show the popup menu for this layout track
 *
 * @param where to show the popup
 * @return the popup menu for this layout track
 */
//@Nonnull
/*final*/ /*protected*/ QMenu* LayoutTrackView::showPopup(QPointF where) {
#if 0
    return this->showPopup(new QGraphicsSceneMouseEvent(
            layoutEditor.getTargetPanel(), // source
            MouseEvent.MOUSE_CLICKED, // id
            System.currentTimeMillis(), // when
            0, // modifiers
            (int) where.getX(), (int) where.getY(), // where
            0, // click count
            true));                         // popup trigger
#else
 return new QMenu();
#endif
}

/**
 * show the popup menu for this layout track
 *
 * @return the popup menu for this layout track
 */
//@Nonnull
/*final*/ /*protected*/ QMenu* LayoutTrackView::showPopup() {
    QPointF where = MathUtil::multiply(getCoordsCenter(),
            layoutEditor->getZoom());
    return this->showPopup(where);
}

/**
 * get the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to get the connection
 * @return the LayoutTrack connected at the specified connection type
 * @throws JmriException - if the connectionType is invalid
 */
// /*abstract*/ /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) throw (JmriException);

/**
 * set the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to set the connection
 * @param o              the LayoutTrack that is to be connected
 * @param type           where on the LayoutTrack we are connected
 * @throws JmriException - if connectionType or type are invalid
 */
// /*abstract*/ /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) throw (JmriException);

/**
 * abstract method... subclasses should implement _IF_ they need to recheck
 * their block boundaries
 */
// /*abstract*/ /*protected*/ void reCheckBlockBoundary();

/**
 * get the layout connectivity for this track
 *
 * @return the list of Layout Connectivity objects
 */
// /*abstract*/ /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity();

/**
 * return true if this connection type is disconnected
 *
 * @param connectionType the connection type to test
 * @return true if the connection for this connection type is free
 */
/*public*/ bool LayoutTrackView::isDisconnected(HitPointType::TYPES connectionType) {
    throw  IllegalArgumentException("should have called in Object instead of View (temporary)");
}

/**
 * return a list of the available connections for this layout track
 *
 * @return the list of available connections
 */
// note: used by LayoutEditorChecks.setupCheckUnConnectedTracksMenu()
//
// This could have just returned a boolean but I thought a list might be
// more useful (eventually... not currently being used; we just check to see
// if it's not empty.)
//@Nonnull
// /*abstract*/ /*public*/ QList<HitPointType::TYPES> checkForFreeConnections();

/**
 * determine if all the appropriate blocks have been assigned to this track
 *
 * @return true if all appropriate blocks have been assigned
 */
// note: used by LayoutEditorChecks.setupCheckUnBlockedTracksMenu()
//
// /*abstract*/ /*public*/ bool checkForUnAssignedBlocks();

/**
 * check this track and its neighbors for non-contiguous blocks
 * <p>
 * For each (non-null) blocks of this track do: #1) If it's got an entry in
 * the blockNamesToTrackNameSetMap then #2) If this track is not in one of
 * the TrackNameSets for this block #3) add a new set (with this
 * block/track) to blockNamesToTrackNameSetMap and #4) check all the
 * connections in this block (by calling the 2nd method below)
 * <p>
 * Basically, we're maintaining contiguous track sets for each block found
 * (in blockNamesToTrackNameSetMap)
 *
 * @param blockNamesToTrackNameSetMaps hashmap of key:block names to lists
 *                                     of track name sets for those blocks
 */
// note: used by LayoutEditorChecks.setupCheckNonContiguousBlocksMenu()
//
///*abstract*/ /*public*/ void checkForNonContiguousBlocks(
//        /*@Nonnull*/ QMap<QString, QList<QSet<QString>>> blockNamesToTrackNameSetMaps);

/**
 * recursive routine to check for all contiguous tracks in this blockName
 *
 * @param blockName    the block that we're checking for
 * @param TrackNameSet the set of track names in this block
 */
///*abstract*/ /*public*/ void collectContiguousTracksNamesInBlockNamed(
//        /*@Nonnull*/ QString blockName,
//        /*@Nonnull */QSet<QString> TrackNameSet);

/**
 * Assign all the layout blocks in this track
 *
 * @param layoutBlock to this layout block (used by the Tools menu's "Assign
 *                    block to selection" item)
 */
///*abstract*/ /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock);
/*public*/ QGraphicsItemGroup* LayoutTrackView::invalidateItem(EditScene* g2, QGraphicsItemGroup* item)
{
 if(item!=nullptr && item->scene() != nullptr)
 {
  for(QGraphicsItem* i : item->childItems())
  {
   if(qgraphicsitem_cast<QGraphicsItemGroup*>(i) && qgraphicsitem_cast<QGraphicsItemGroup*>(i)->childItems().count()>0)
    invalidateItem(g2, qgraphicsitem_cast<QGraphicsItemGroup*>(i));
   g2->removeItem(i);
  }
  if(item->scene() == g2)
   g2->destroyItemGroup(item);

 }
 item = nullptr;
 return item;
}

/*private*/ /*final*/ /*static*/ Logger* LayoutTrackView::log = LoggerFactory::getLogger("LayoutTrackView");
