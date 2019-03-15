#include "layouttrack.h"
#include <QColor>
#include "turnout.h"
#include "layouteditor.h"
#include "colorutil.h"

/**
 * Abstract base class for all layout track objects (LayoutTurnout, LayoutSlip,
 * LayoutTurntable, LevelXing, TrackSegment)
 *
 * @author George Warner Copyright (c) 2017
 */
// /*public*/ abstract class LayoutTrack {

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");



// dashed line parameters
//private static int minNumDashes = 3;
//private static double maxDashLength = 10;


/*protected*/ /*static*/ QColor LayoutTrack::defaultTrackColor = QColor(Qt::black);

/*protected*/ /*static*/ /*final*/ double LayoutTrack::controlPointSize = 3.0;   // LayoutEditor.SIZE;
/*protected*/ /*static*/ /*final*/ double LayoutTrack::controlPointSize2 = 2.0 * LayoutTrack::controlPointSize; // LayoutEditor.SIZE2;

/**
 * constructor method
 */
///*public*/ LayoutTrack::LayoutTrack(QObject*parent) : QObject(parent)
//{
// center =  QPointF(50.0, 50.0);
// hidden = false;
// propertyChangeSupport = new PropertyChangeSupport(this);

//}
/*public*/ LayoutTrack::LayoutTrack(/*@Nonnull*/ QString ident, /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor, QObject *parent) {

 center = QPointF(50.0, 50.0);

 this->ident = ident;
 this->center = c;
 this->layoutEditor = layoutEditor;
 defaultTrackColor = ColorUtil::stringToColor(layoutEditor->getDefaultTrackColor());
 item = nullptr;
}

/**
 * accessor methods
 */
/*public*/ QString LayoutTrack::getId() {
    return ident;
}

/*public*/ QString LayoutTrack::getName() {
    return ident;
}

/**
 * get center coordinates
 *
 * @return the center coordinates
 */
/*public*/ QPointF LayoutTrack::getCoordsCenter() {
    return center;
}

/**
 * set center coordinates
 *
 * @param p the coordinates to set
 */
/*public*/ void LayoutTrack::setCoordsCenter(/*@Nonnull*/ QPointF p) {
    center = p;
}

/**
 * @return true if this track segment has decorations
 */
/*public*/ bool LayoutTrack::hasDecorations() {
    return false;
}

/**
 * get decorations
 *
 * @return the decorations
 */
/*public*/ QMap<QString, QString>* LayoutTrack::getDecorations() {
    return decorations;
}

/**
 * set decorations
 *
 * @param decorations to set
 */
/*public*/ void LayoutTrack::setDecorations(QMap<QString, QString>* decorations) {
    this->decorations = decorations;
}

/*public*/ /*static*/ void LayoutTrack::setDefaultTrackColor(/*@Nullable*/ QColor color) {
    defaultTrackColor = color;
}

/*protected*/ QColor LayoutTrack::getColorForTrackBlock(
        /*@Nullable*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor) {
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
/*protected*/ QColor LayoutTrack::getColorForTrackBlock(/*@Nullable*/ LayoutBlock* lb) {
    return getColorForTrackBlock(lb, false);
}

/*protected*/ QColor LayoutTrack::setColorForTrackBlock(EditScene* g2,
        /*@Nullable*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor) {
    QColor result = getColorForTrackBlock(layoutBlock, forceBlockTrackColor);
// TODO:    g2.setColor(result);
    return result;
}

// optional parameter forceTrack = false
/*protected*/ QColor LayoutTrack::setColorForTrackBlock(EditScene* g2, /*@Nullable*/ LayoutBlock* lb) {
    return setColorForTrackBlock(g2, lb, false);
}

/*public*/ /*abstract*/ bool LayoutTrack::isMainline() {return false;}
/**
 * draw one line (Ballast, ties, center or 3rd rail, block lines)
 *
 * @param g2      the graphics context
 * @param isMain  true if drawing mainlines
 * @param isBlock true if drawing block lines
 */
/*protected*/ /*abstract*/ void LayoutTrack::draw1(EditScene * /*g2*/, bool /*isMain*/, bool /*isBlock*/) {}

/**
 * draw two lines (rails)
 *
 * @param g2               the graphics context
 * @param isMain           true if drawing mainlines
 * @param railDisplacement the offset from center to draw the lines
 */
/*protected*/ /*abstract*/ void LayoutTrack::draw2(EditScene* g2, bool /*isMain*/, float /*railDisplacement*/) {}

/**
 * draw hidden track
 *
 * @param g2 the graphics context
 */
//protected abstract void drawHidden(Graphics2D g2);
//note: placeholder until I get this implemented in all sub-classes
//TODO: replace with abstract declaration (above)
/*protected*/ void LayoutTrack::drawHidden(EditScene *g2) {
    //nothing to do here... move along...
}

/**
 * highlight unconnected connections
 *
 * @param g2           the graphics context
 * @param specificType the specific connection to draw (or NONE for all)
 */
/*protected*/ /*abstract*/ void LayoutTrack::highlightUnconnected(EditScene *g2, int specificType) {}

// optional parameter specificType = NONE
/*protected*/ void LayoutTrack::highlightUnconnected(EditScene* g2) {
    highlightUnconnected(g2, NONE);
}

//may not be needed sinc QGraphicsScene may suffice
//NOTE: not /*public*/ because "center" is a member variable
/*protected*/ QPointF LayoutTrack::rotatePoint(QPointF p, double sineRot, double cosineRot) {
    double cX = center.x();
    double cY = center.y();
    double deltaX = p.x() - cX;
    double deltaY = p.y() - cY;
    double x = cX + cosineRot * deltaX - sineRot * deltaY;
    double y = cY + sineRot * deltaX + cosineRot * deltaY;
    return QPointF(x, y);
}

/**
 * draw the edit controls
 *
 * @param g2 the graphics context
 */
/*protected*/ /*abstract*/ void LayoutTrack::drawEditControls(EditScene *g2) {}

/**
 * draw the turnout controls
 *
 * @param g2 the graphics context
 */
/*protected*/ /*abstract*/ void LayoutTrack::drawTurnoutControls(EditScene* g2) {}

/**
 * draw track decorations
 *
 * @param g2 the graphics context
 */
//protected abstract void drawDecorations(Graphics2D g2);
//note: placeholder until I get this implemented in all sub-classes
//TODO: replace with abstract declaration (above)
/*protected*/ void LayoutTrack::drawDecorations(EditScene* g2) {
    //nothing to do here... move along...
}
/**
 * Get the hidden state of the track element.
 *
 * @return true if hidden; false otherwise
 */
/*public*/ bool LayoutTrack::isHidden() {
    return hidden;
}

/**
 * Get the hidden state of the track element.
 *
 * @return true if hidden; false otherwise
 * @deprecated since 4.7.2; use {@link #isHidden()} instead
 */
//@Deprecated // Java standard pattern for bool getters is "isHidden()"
/*public*/ bool LayoutTrack::getHidden() {
    return hidden;
}

/*public*/ void LayoutTrack::setHidden(bool hide)
{
 hidden = hide;
 if(hiddenItems!= nullptr && hiddenItems->scene() != nullptr)
 {
  hiddenItems->scene()->removeItem(hiddenItems);
  hiddenItems = nullptr;
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
/*public*/ QString LayoutTrack::getTurnoutStateString(int turnoutState) {
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
 * Initialization method for LayoutTrack sub-classes. The following method
 * is called for each instance after the entire LayoutEditor is loaded to
 * set the specific objects for that instance
 *
 * @param le the layout editor
 */
/*public*/ /*abstract*/ void LayoutTrack::setObjects(/*@Nonnull*/ LayoutEditor* le) {}

/**
 * scale this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to scale X coordinates
 * @param yFactor the amount to scale Y coordinates
 */
/*public*/ /*abstract*/ void LayoutTrack::scaleCoords(float xFactor, float yFactor) {}

/**
 * translate this LayoutTrack's coordinates by the x and y factors
 *
 * @param xFactor the amount to translate X coordinates
 * @param yFactor the amount to translate Y coordinates
 */
/*public*/ /*abstract*/ void LayoutTrack::translateCoords(float xFactor, float yFactor) {}

/**
 * find the hit (location) type for a point
 *
 * @param hitPoint           - the point
 * @param useRectangles      - whether to use (larger) rectangles or
 *                           (smaller) circles for hit testing
 * @param requireUnconnected - whether to only return hit types for free
 *                           connections
 * @return the location type for the point (or NONE)
 * @since 7.4.3
 */
/*protected*/ /*abstract*/ int LayoutTrack::findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles, bool requireUnconnected)
{ return 0;}

// optional useRectangles & requireUnconnected parameters default to false
/*protected*/ int LayoutTrack::findHitPointType(/*@Nonnull */QPointF p) {
    return findHitPointType(p, false, false);
}

// optional requireUnconnected parameter defaults to false
/*protected*/ int LayoutTrack::findHitPointType(/*@Nonnull*/ QPointF p, bool useRectangles) {
    return findHitPointType(p, useRectangles, false);
}

/**
 * @param hitType the hit point type
 * @return true if this int is for a connection to a LayoutTrack
 */
/*protected*/ /*static*/ bool LayoutTrack::isConnectionHitType(int hitType) {
    bool result = false; // assume failure (pessimist!)
    switch (hitType) {
        case POS_POINT:
        case TURNOUT_A:
        case TURNOUT_B:
        case TURNOUT_C:
        case TURNOUT_D:
        case LEVEL_XING_A:
        case LEVEL_XING_B:
        case LEVEL_XING_C:
        case LEVEL_XING_D:
        case TRACK:
        case SLIP_A:
        case SLIP_B:
        case SLIP_C:
        case SLIP_D:
            result = true;  // these are all connection types
            break;
        case NONE:
        case TURNOUT_CENTER:
        case LEVEL_XING_CENTER:
        case TURNTABLE_CENTER:
        case LAYOUT_POS_LABEL:
        case LAYOUT_POS_JCOMP:
        case MULTI_SENSOR:
        case MARKER:
        case TRACK_CIRCLE_CENTRE:
        case SLIP_CENTER:
        case SLIP_LEFT:
        case SLIP_RIGHT:
        default:
            result = false; // these are not
            break;
    }
    if ((hitType >= BEZIER_CONTROL_POINT_OFFSET_MIN) && (hitType <= BEZIER_CONTROL_POINT_OFFSET_MAX)) {
        result = false; // these are not
    } else if (hitType >= TURNTABLE_RAY_OFFSET) {
        result = true;  // these are all connection types
    }
    return result;
}   // isConnectionHitType

/**
 * @param hitType the hit point type
 * @return true if this int is for a layout control
 */
/*protected*/ /*static*/ bool LayoutTrack::isControlHitType(int hitType) {
    bool result = false; // assume failure (pessimist!)
    switch (hitType) {
        case TURNOUT_CENTER:
        case SLIP_CENTER:
        case SLIP_LEFT:
        case SLIP_RIGHT:
            result = true;  // these are all control types
            break;
        case POS_POINT:
        case TURNOUT_A:
        case TURNOUT_B:
        case TURNOUT_C:
        case TURNOUT_D:
        case LEVEL_XING_A:
        case LEVEL_XING_B:
        case LEVEL_XING_C:
        case LEVEL_XING_D:
        case TRACK:
        case SLIP_A:
        case SLIP_B:
        case SLIP_C:
        case SLIP_D:
        case NONE:
        case LEVEL_XING_CENTER:
        case TURNTABLE_CENTER:
        case LAYOUT_POS_LABEL:
        case LAYOUT_POS_JCOMP:
        case MULTI_SENSOR:
        case MARKER:
        case TRACK_CIRCLE_CENTRE:
        default:
            result = false; // these are not
            break;
    }
    if ((hitType >= BEZIER_CONTROL_POINT_OFFSET_MIN) && (hitType <= BEZIER_CONTROL_POINT_OFFSET_MAX)) {
        result = false; // these are not control types
    } else if (hitType >= TURNTABLE_RAY_OFFSET) {
        result = true;  // these are all control types
    }
    return result;
}   // isControlHitType

/**
 * @param hitType the hit point type
 * @return true if this int is for a popup menu
 */
/*protected*/ /*static*/ bool LayoutTrack::isPopupHitType(int hitType) {
    bool result = false; // assume failure (pessimist!)
    switch (hitType) {
        case LEVEL_XING_CENTER:
        case POS_POINT:
        case SLIP_CENTER:
        case SLIP_LEFT:
        case SLIP_RIGHT:
        case TRACK:
        case TRACK_CIRCLE_CENTRE:
        case TURNOUT_CENTER:
        case TURNTABLE_CENTER:
            result = true;  // these are all popup hit types
            break;
        case LAYOUT_POS_JCOMP:
        case LAYOUT_POS_LABEL:
        case LEVEL_XING_A:
        case LEVEL_XING_B:
        case LEVEL_XING_C:
        case LEVEL_XING_D:
        case MARKER:
        case MULTI_SENSOR:
        case NONE:
        case SLIP_A:
        case SLIP_B:
        case SLIP_C:
        case SLIP_D:
        case TURNOUT_A:
        case TURNOUT_B:
        case TURNOUT_C:
        case TURNOUT_D:
        default:
            result = false; // these are not
            break;
    }
    if ((hitType >= BEZIER_CONTROL_POINT_OFFSET_MIN) && (hitType <= BEZIER_CONTROL_POINT_OFFSET_MAX)) {
        result = true; // these are all popup hit types
    } else if (hitType >= TURNTABLE_RAY_OFFSET) {
        result = true;  // these are all popup hit types
    }
    return result;
}   // isPopupHitType

/**
 * return the coordinates for a specified connection type (abstract: should
 * be overridden by ALL subclasses)
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
/*public*/ /*abstract*/ QPointF LayoutTrack::getCoordsForConnectionType(int /*connectionType*/)
{
 return QPointF();
}

/**
 * @return the bounds of this track
 */
/*public*/ /*abstract*/ QRectF LayoutTrack::getBounds() {return QRectF();}

/**
 * show the popup menu for this layout track
 *
 * @param mouseEvent the mouse down event that triggered this popup
 * @return the popup menu for this layout track
 */
//@Nonnull
/*protected*/ /*abstract*/ QMenu* LayoutTrack::showPopup(/*@Nullable*/ QGraphicsSceneMouseEvent* mouseEvent) {return nullptr;}

/**
 * show the popup menu for this layout track
 *
 * @param where to show the popup
 * @return the popup menu for this layout track
 */
//@Nonnull
/*protected*/ QMenu* LayoutTrack::showPopup(QPointF where) {
    return this->showPopup(new QGraphicsSceneMouseEvent(
                        #if 0
            layoutEditor.getTargetPanel(), // source
            MouseEvent.MOUSE_CLICKED, // id
            System.currentTimeMillis(), // when
            0, // modifiers
            (int) where.getX(), (int) where.getY(), // where
            0, // click count
            true
                        #endif
                       )
                           );                         // popup trigger

}

/**
 * show the popup menu for this layout track
 *
 * @return the popup menu for this layout track
 */
//@Nonnull
/*protected*/ QMenu* LayoutTrack::showPopup() {
//    QPointF where = MathUtil.multiply(getCoordsCenter(),
//            layoutEditor.getZoom());
 QPointF where = QPoint();
    return this->showPopup(where);
}

/**
 * get the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to get the connection
 * @return the LayoutTrack connected at the specified connection type
 * @throws JmriException - if the connectionType is invalid
 */
/*public*/ /*abstract*/ LayoutTrack* LayoutTrack::getConnection(int connectionType) throw (JmriException) {return nullptr;}

/**
 * set the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to set the connection
 * @param o              the LayoutTrack that is to be connected
 * @param type           where on the LayoutTrack we are connected
 * @throws JmriException - if connectionType or type are invalid
 */
/*public*/ /*abstract*/ void LayoutTrack::setConnection(int connectionType, LayoutTrack* o, int type) throw (JmriException) {}

/**
 * abstract method... subclasses should implement _IF_ they need to recheck
 * their block boundaries
 */
/*protected*/ /*abstract*/ void LayoutTrack::reCheckBlockBoundary() {}

/**
 * get the layout connectivity for this track
 *
 * @return the list of Layout Connectivity objects
 */
/*protected*/ /*abstract*/ QList<LayoutConnectivity*> LayoutTrack::getLayoutConnectivity() {return QList<LayoutConnectivity*>();}

/**
 * return true if this connection type is disconnected
 *
 * @param connectionType - the connection type to test
 * @return true if the connection for this connection type is free
 */
/*public*/ bool LayoutTrack::isDisconnected(int connectionType) {
    bool result = false;
    if (isConnectionHitType(connectionType)) {
        try {
            result = (nullptr == getConnection(connectionType));
        } catch (JmriException e) {
            // this should never happen because isConnectionType() above would have caught an invalid connectionType.
        }
    }
    return result;
}

/**
 * return a list of the available connections for this layout track
 *
 * @return the list of available connections
 * <p>
 * note: used by LayoutEditorChecks.setupCheckUnConnectedTracksMenu()
 * <p>
 * (This could have just returned a boolean but I thought a list might be
 * more useful (eventually... not currently being used; we just check to see
 * if it's not empty.)
 */
//@Nonnull
/*public*/ /*abstract*/ QList<int> LayoutTrack::checkForFreeConnections() {return QList<int>();}

/**
 * determine if all the appropriate blocks have been assigned to this track
 *
 * @return true if all appropriate blocks have been assigned
 * <p>
 * note: used by LayoutEditorChecks.setupCheckUnBlockedTracksMenu()
 */
/*public*/ /*abstract*/ bool LayoutTrack::checkForUnAssignedBlocks() {return false;}

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
 * <p>
 * note: used by LayoutEditorChecks.setupCheckNonContiguousBlocksMenu()
 */
/*public*/ /*abstract*/ void LayoutTrack::checkForNonContiguousBlocks(
  /*@Nonnull*/ QMap<QString, QList<QSet<QString > > > blockNamesToTrackNameSetMaps)  {}

/**
 * recursive routine to check for all contiguous tracks in this blockName
 *
 * @param blockName    the block that we're checking for
 * @param TrackNameSet the set of track names in this block
 */
/*public*/ /*abstract*/ void LayoutTrack::collectContiguousTracksNamesInBlockNamed(
        /*@Nonnull*/ QString blockName,
  /*@Nonnull*/ QSet<QString> trackNameSet) {}

/**
 * Assign all the layout blocks in this track
 *
 * @param layoutBlock to this layout block (used by the Tools menu's "Assign
 *                    block to selection" item)
 */
/*public*/ /*abstract*/ void LayoutTrack::setAllLayoutBlocks(LayoutBlock* /*layoutBlock*/) {}

/*private*/ /*final*/ /*static*/ Logger* LayoutTrack::log = LoggerFactory::getLogger("LayoutTrack");
