#include "layouttrack.h"
#include <QColor>
#include "turnout.h"
#include "colorutil.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "layouteditor.h"

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


///*protected*/ /*static*/ QColor LayoutTrack::defaultTrackColor = QColor(Qt::black);

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
/*public*/ LayoutTrack::LayoutTrack(/*@Nonnull*/ QString ident, /*@Nonnull*/ LayoutEditor* models, QObject *parent) : QObject(parent){

// center = QPointF(50.0, 50.0);

 this->ident = ident;
 this->models = models;

 //defaultTrackColor = ColorUtil::stringToColor(models->getDefaultTrackColor());
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


/*final*/ /*protected*/ void LayoutTrack::setIdent(/*@Nonnull*/ QString ident) {
    this->ident = ident;
}

//abstract public boolean isMainline();

/*
* non-accessor methods
 */
/**
 * get turnout state string
 *
 * @param turnoutState of the turnout
 * @return the turnout state string
 */
/*final*/ /*public*/ QString LayoutTrack::getTurnoutStateString(int turnoutState) {
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
 * Initialization method for LayoutTrack sub-classes. The following method
 * is called for each instance after the entire LayoutEditor is loaded to
 * set the specific objects for that instance
 *
 * @param le the layout editor
 */
//abstract public void setObjects(@Nonnull LayoutEditor le);

/**
 * get the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to get the connection
 * @return the LayoutTrack connected at the specified connection type
 * @throws JmriException - if the connectionType is invalid
 */
// /*abstract*/ /*public*/ LayoutTrack* getConnection(HitPointType* connectionType) /*throw (JmriException)*/;

/**
 * set the LayoutTrack connected at the specified connection type
 *
 * @param connectionType where on us to set the connection
 * @param o              the LayoutTrack that is to be connected
 * @param type           where on the LayoutTrack we are connected
 * @throws JmriException - if connectionType or type are invalid
 */
// /*abstract*/ /*public*/ void setConnection(HitPointType* connectionType, LayoutTrack* o, HitPointType* type) /*throw (JmriException)*/;

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
 * get center coordinates
 *
 * @return the center coordinates
 */
///*public*/ QPointF LayoutTrack::getCoordsCenter() const {
//    return center;
//}


/**
 * return true if this connection type is disconnected
 *
 * @param connectionType - the connection type to test
 * @return true if the connection for this connection type is free
 */
/*public*/ bool LayoutTrack::isDisconnected(HitPointType::TYPES connectionType) {
    bool result = false;
    if (HitPointType::isConnectionHitType(connectionType)) {
        try {
            result = (nullptr == getConnection(connectionType));
        } catch (JmriException* e) {
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
/*public*/ /*abstract*/ QList<HitPointType::TYPES> LayoutTrack::checkForFreeConnections() {return QList<HitPointType::TYPES>();}

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
/*public*/ /*abstract*/ void LayoutTrack::checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *> *> blockNamesToTrackNameSetMaps)  {}

/**
 * recursive routine to check for all contiguous tracks in this blockName
 *
 * @param blockName    the block that we're checking for
 * @param TrackNameSet the set of track names in this block
 */
///*public*/ /*abstract*/ void LayoutTrack::collectContiguousTracksNamesInBlockNamed(
//        /*@Nonnull*/ QString blockName,
//  /*@Nonnull*/ QSet<QString>* trackNameSet) {}

/**
 * Assign all the layout blocks in this track
 *
 * @param layoutBlock to this layout block (used by the Tools menu's "Assign
 *                    block to selection" item)
 */
/*public*/ /*abstract*/ void LayoutTrack::setAllLayoutBlocks(LayoutBlock* /*layoutBlock*/) {}
/*public*/ QGraphicsItemGroup* LayoutTrack::invalidateItem(EditScene* g2, QGraphicsItemGroup* item)
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
/*private*/ /*final*/ /*static*/ Logger* LayoutTrack::log = LoggerFactory::getLogger("LayoutTrack");
