#include "positionablepointview.h"
#include "mathutil.h"
#include "signalmastmanager.h"
#include "namedbeanhandlemanager.h"
#include "signalmastlogicmanager.h"
#include "signallingguitools.h"
#include "loggerfactory.h"
#include "tracksegmentview.h"
#include "jmricolorchooser.h"
#include "layouteditortoolbarpanel.h"
#include "quickpromptutil.h"
#include "editormanager.h"
#include "vptr.h"

/**
 * MVC View component for the PositionablePoint class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class PositionablePointView extends LayoutTrackView {

/**
 * MVC View component for the PositionablePoint class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 * <p>
 * Arrows and bumpers are visual, presentation aspects handled in the View.
 */
// /*public*/ class PositionablePointView extends LayoutTrackView {



/**
 * constructor method.
 * @param point the positionable point.
 * @param c location to display the positionable point
 * @param LayoutEditor* for access to tools
 */
/*public*/ PositionablePointView::PositionablePointView(/*@Nonnull*/  PositionablePoint* point,
        QPointF c,
        /*@Nonnull*/  LayoutEditor* layoutEditor) : LayoutTrackView(point, c, layoutEditor){
    //super(point, c, layoutEditor);
    this->positionablePoint = point;
}


/*public*/ PositionablePoint* PositionablePointView::getPoint() { return positionablePoint; }

// this should only be used for debugging...
//@Override
/*public*/ QString PositionablePointView::toString() {
    QString result = "PositionalablePoint";
    switch (getType()) {
        case PositionablePoint::ANCHOR: {
            result = "Anchor";
            break;
        }
        case PositionablePoint::END_BUMPER: {
            result = "End Bumper";
            break;
        }
        case PositionablePoint::EDGE_CONNECTOR: {
            result = "Edge Connector";
            break;
        }
        default: {
            result = QString("Unknown type (") + getType() + ")";
            break;
        }
    }
    return result + " '" + getName() + "'";
}

/**
 * Accessor methods
 * @return Type enum for this Positionable Point
 */
/*public*/ int PositionablePointView::getType() {
    return positionablePoint->getType();
}

/*public*/ void PositionablePointView::setType(int newType) {
    positionablePoint->setType((PositionablePoint::PointType)newType);

    // (temporary) we keep this echo here until we figure out where arrow info lives
    if (getType() != newType) {
        switch (newType) {
            default:
            case PositionablePoint::ANCHOR: {
                setTypeAnchor();
                break;
            }
            case PositionablePoint::END_BUMPER: {
                setTypeEndBumper();
                break;
            }
            case PositionablePoint::EDGE_CONNECTOR: {
                setTypeEdgeConnector();
                break;
            }
        }
        layoutEditor->repaint();
    }
}

/*private*/ void PositionablePointView::setTypeAnchor() {
    setIdent(layoutEditor->getFinder()->uniqueName("A", 1));

    // type = PointType.ANCHOR;
    positionablePoint->setTypeAnchor();

    if (getConnect1() != nullptr) {
        TrackSegmentView* ctv1 = layoutEditor->getTrackSegmentView(getConnect1());
        if (getConnect1()->getConnect1() == positionablePoint) {
            ctv1->setArrowEndStart(false);
            ctv1->setBumperEndStart(false);
        }
        if (getConnect1()->getConnect2() == positionablePoint) {
            ctv1->setArrowEndStop(false);
            ctv1->setBumperEndStop(false);
        }
    }
    if (getConnect2() != nullptr) {
        TrackSegmentView* ctv2 = layoutEditor->getTrackSegmentView(getConnect2());
        if (getConnect2()->getConnect1() == positionablePoint) {
            ctv2->setArrowEndStart(false);
            ctv2->setBumperEndStart(false);
        }
        if (getConnect2()->getConnect2() == positionablePoint) {
            ctv2->setArrowEndStop(false);
            ctv2->setBumperEndStop(false);
        }
    }
}

/*private*/ void PositionablePointView::setTypeEndBumper() {
    setIdent(layoutEditor->getFinder()->uniqueName("EB", 1));

    // type = PointType.END_BUMPER;
    positionablePoint->setTypeEndBumper();

    if (getConnect1() != nullptr) {
        TrackSegmentView* ctv1 = layoutEditor->getTrackSegmentView(getConnect1());
        if (getConnect1()->getConnect1() == positionablePoint) {
            ctv1->setArrowEndStart(false);
            ctv1->setBumperEndStart(true);
        }
        if (getConnect1()->getConnect2() == positionablePoint) {
            ctv1->setArrowEndStop(false);
            ctv1->setBumperEndStop(true);
        }
    }
}

/*private*/ void PositionablePointView::setTypeEdgeConnector() {
    setIdent(layoutEditor->getFinder()->uniqueName("EC", 1));

    // type = PointType.EDGE_CONNECTOR;
    positionablePoint->setTypeEdgeConnector();

    if (getConnect1() != nullptr) {
        TrackSegmentView* ctv1 = layoutEditor->getTrackSegmentView(getConnect1());
        if (getConnect1()->getConnect1() == positionablePoint) {
            ctv1->setBumperEndStart(false);
        }
        if (getConnect1()->getConnect2() == positionablePoint) {
            ctv1->setBumperEndStop(false);
        }
    }
}

/*public*/ TrackSegment* PositionablePointView::getConnect1() {
    return positionablePoint->getConnect1();
}

/*public*/ TrackSegment* PositionablePointView::getConnect2() {
    return positionablePoint->getConnect2();
}

/*public*/ QString PositionablePointView::getLinkedEditorName() {
    return positionablePoint->getLinkedEditorName();
}

/*public*/ LayoutEditor* PositionablePointView::getLinkedEditor() {
    return positionablePoint->getLinkedEditor();
}

/*public*/ PositionablePoint* PositionablePointView::getLinkedPoint() {
    return positionablePoint->getLinkedPoint();
}

/*public*/ void PositionablePointView::removeLinkedPoint() {
    positionablePoint->removeLinkedPoint();
}

/*public*/ QString PositionablePointView::getLinkedPointId() {
    return positionablePoint->getLinkedPointId();
}

/*public*/ void PositionablePointView::setLinkedPoint(PositionablePoint* p) {
    positionablePoint->setLinkedPoint(p);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::scaleCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    LayoutTrackView::setCoordsCenter(MathUtil::granulize(MathUtil::multiply(getCoordsCenter(), factor), 1.0));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::translateCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    LayoutTrackView::setCoordsCenter(MathUtil::add(getCoordsCenter(), factor));
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::rotateCoords(double angleDEG) {
    //can't really rotate a point... so...
    //nothing to see here... move along...
}

/**
 * @return the bounds of this positional point
 */
//@Override
/*public*/ QRectF PositionablePointView::getBounds() {
    QPointF c = getCoordsCenter();
    //Note: empty bounds don't draw...
    // so now I'm making them 0.5 bigger in all directions (1 pixel total)
    return QRectF(c.x() - 0.5, c.y() - 0.5, 1.0, 1.0);
}

//@CheckReturnValue
/*protected*/ LayoutEditor* PositionablePointView::getLayoutEditor() {
    return layoutEditor;
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getEastBoundSignal() {
    SignalHead* h = getEastBoundSignalHead();
    if (h != nullptr) {
        return h->getDisplayName();
    }
    return "";
}

//@CheckForNull
//@CheckReturnValue
/*public*/ SignalHead* PositionablePointView::getEastBoundSignalHead() {
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::EAST || dir == Path::SOUTH || dir == Path::SOUTH_EAST) {
            if (signalEastHeadNamed != nullptr) {
                return signalEastHeadNamed->getBean();
            }
            return nullptr;
        } else if (getLinkedPoint() != nullptr) {
            // Do some checks to find where the connection is here.
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH_EAST) {
                return getLinkedPoint()->getEastBoundSignalHead();
            }
        }
    }

    if (signalEastHeadNamed != nullptr) {
        return signalEastHeadNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePointView::setEastBoundSignal(QString signalName) {
    if (getType() == PositionablePoint::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::EAST || dir == Path::SOUTH || dir == Path::SOUTH_EAST) {
            setEastBoundSignalName(signalName);
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH_EAST) {
                getLinkedPoint()->setEastBoundSignal(signalName);
            } else {
                setEastBoundSignalName(signalName);
            }
        } else {
            setEastBoundSignalName(signalName);
        }
    } else {
        setEastBoundSignalName(signalName);
    }
}

/*private*/ void PositionablePointView::setEastBoundSignalName(/*@CheckForNull*/ QString signalHead) {
    if (signalHead == "" || signalHead.isEmpty()) {
        signalEastHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalEastHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalEastHeadNamed = nullptr;
    }
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getWestBoundSignal() {
    SignalHead* h = getWestBoundSignalHead();
    if (h != nullptr) {
        return h->getDisplayName();
    }
    return "";
}

//@CheckForNull
//@CheckReturnValue
/*public*/ SignalHead* PositionablePointView::getWestBoundSignalHead() {
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH_WEST) {
            if (signalWestHeadNamed != nullptr) {
                return signalWestHeadNamed->getBean();
            }
            return nullptr;
        } else if (getLinkedPoint() != nullptr) {
            // Do some checks to find where the connection is here.
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH_WEST) {
                return getLinkedPoint()->getWestBoundSignalHead();
            }
        }
    }

    if (signalWestHeadNamed != nullptr) {
        return signalWestHeadNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePointView::setWestBoundSignal(QString signalName) {
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH_WEST) {
            setWestBoundSignalName(signalName);
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH_WEST) {
                getLinkedPoint()->setWestBoundSignal(signalName);
            } else {
                setWestBoundSignalName(signalName);
            }
        } else {
            setWestBoundSignalName(signalName);
        }
    } else {
        setWestBoundSignalName(signalName);
    }
}

/*private*/ void PositionablePointView::setWestBoundSignalName(/*@CheckForNull*/ QString signalHead) {
    if (signalHead == nullptr || signalHead.isEmpty()) {
        signalWestHeadNamed = nullptr;
        return;
    }

    SignalHead* head = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalWestHeadNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalWestHeadNamed = nullptr;
    }
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getEastBoundSensorName() {
    if (eastBoundSensorNamed != nullptr) {
        return eastBoundSensorNamed->getName();
    }
    return "";
}

//@CheckReturnValue
/*public*/ Sensor* PositionablePointView::getEastBoundSensor() {
    if (eastBoundSensorNamed != nullptr) {
        return eastBoundSensorNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePointView::setEastBoundSensor(QString sensorName) {
    if (sensorName == "" || sensorName.isEmpty()) {
        eastBoundSensorNamed = nullptr;
        return;
    }

    try {
        Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
        eastBoundSensorNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } catch (IllegalArgumentException* ex) {
        eastBoundSensorNamed = nullptr;
    }
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getWestBoundSensorName() {
    if (westBoundSensorNamed != nullptr) {
        return westBoundSensorNamed->getName();
    }
    return "";
}

//@CheckReturnValue
/*public*/ Sensor* PositionablePointView::getWestBoundSensor() {
    if (westBoundSensorNamed != nullptr) {
        return westBoundSensorNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePointView::setWestBoundSensor(QString sensorName) {
    if (sensorName == nullptr || sensorName.isEmpty()) {
        westBoundSensorNamed = nullptr;
        return;
    }
    try {
        Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
        westBoundSensorNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } catch (IllegalArgumentException* ex) {
        westBoundSensorNamed = nullptr;
    }
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getEastBoundSignalMastName() {
    if (getEastBoundSignalMastNamed() != nullptr) {
        return getEastBoundSignalMastNamed()->getName();
    }
    return "";
}

//@CheckReturnValue
/*public*/ SignalMast* PositionablePointView::getEastBoundSignalMast() {
    if (getEastBoundSignalMastNamed() != nullptr) {
        return getEastBoundSignalMastNamed()->getBean();
    }
    return nullptr;
}

//@CheckReturnValue
/*private*/ NamedBeanHandle<SignalMast*>* PositionablePointView::getEastBoundSignalMastNamed() {
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::SOUTH || dir == Path::EAST || dir == Path::SOUTH_EAST) {
            return eastBoundSignalMastNamed;
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH_EAST) {
                return getLinkedPoint()->getEastBoundSignalMastNamed();
            }
        }
    }
    return eastBoundSignalMastNamed;
}

/*public*/ void PositionablePointView::setEastBoundSignalMast(QString signalMast) {
    SignalMast* mast = nullptr;
    if (signalMast != nullptr && !signalMast.isEmpty()) {
        mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
        if (mast == nullptr) {
            log->error(tr("%1->setEastBoundSignalMast(%2); Unable to find Signal Mast").arg(
                    getName(), signalMast));
            return;
        }
    } else {
        eastBoundSignalMastNamed = nullptr;
        return;
    }
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::EAST || dir == Path::SOUTH || dir == Path::SOUTH_EAST) {
            eastBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH_EAST) {
                getLinkedPoint()->setEastBoundSignalMast(signalMast);
            } else {
                eastBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
            }
        } else {
            eastBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        }
    } else {
        eastBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    }
}

//@CheckReturnValue
/*@Nonnull*/
/*public*/ QString PositionablePointView::getWestBoundSignalMastName() {
    if (getWestBoundSignalMastNamed() != nullptr) {
        return getWestBoundSignalMastNamed()->getName();
    }
    return "";
}

//@CheckReturnValue
/*public*/ SignalMast* PositionablePointView::getWestBoundSignalMast() {
    if (getWestBoundSignalMastNamed() != nullptr) {
        return getWestBoundSignalMastNamed()->getBean();
    }
    return nullptr;
}

//@CheckReturnValue
/*private*/ NamedBeanHandle<SignalMast*>* PositionablePointView::getWestBoundSignalMastNamed() {
    if (getType() == PositionablePoint::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH_WEST) {
            return westBoundSignalMastNamed;
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH_WEST) {
                return getLinkedPoint()->getWestBoundSignalMastNamed();
            }
        }
    }
    return westBoundSignalMastNamed;
}

/*public*/ void PositionablePointView::setWestBoundSignalMast(QString signalMast) {
    SignalMast* mast = nullptr;
    if (signalMast != nullptr && !signalMast.isEmpty()) {
        mast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
        if (mast == nullptr) {
            log->error(tr("%1->setWestBoundSignalMast(%2); Unable to find Signal Mast").arg(
                    getName(), signalMast));
            return;
        }
    } else {
        westBoundSignalMastNamed = nullptr;
        return;
    }
    if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH_WEST) {
            westBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH_WEST) {
                getLinkedPoint()->setWestBoundSignalMast(signalMast);
            } else {
                westBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
            }
        } else {
            westBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        }
    } else {
        westBoundSignalMastNamed = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    }
}

/*public*/ void PositionablePointView::removeBeanReference(NamedBean* nb) {
    if (nb == nullptr) {
        return;
    }
    if (static_cast<SignalMast*>(nb->self())) {
        if (nb->equals(getWestBoundSignalMast())) {
            setWestBoundSignalMast(nullptr);
        } else if (nb->equals(getEastBoundSignalMast())) {
            setEastBoundSignalMast(nullptr);
        }
    } else if (static_cast<Sensor*>(nb->self())) {
        if (nb->equals(getWestBoundSensor())) {
            setWestBoundSignalMast(nullptr);
        } else if (nb->equals(getEastBoundSensor())) {
            setEastBoundSignalMast(nullptr);
        }
    } else if (static_cast<SignalHead*>(nb->self())) {
        if (nb->equals(getWestBoundSignalHead())) {
            setWestBoundSignal(nullptr);
        }
        if (nb->equals(getEastBoundSignalHead())) {
            setEastBoundSignal(nullptr);
        }

    }
}


/**
 * setup a connection to a track
 *
 * @param track the track we want to connect to
 * @return true if successful
 */
/*public*/ bool PositionablePointView::setTrackConnection(/*@Nonnull*/  TrackSegment* track) {
    return replaceTrackConnection(nullptr, track);
}

/**
 * remove a connection to a track
 *
 * @param track the track we want to disconnect from
 * @return true if successful
 */
/*public*/ bool PositionablePointView::removeTrackConnection(/*@Nonnull*/  TrackSegment* track) {
    return replaceTrackConnection(track, nullptr);
}

/**
 * replace old track connection with new track connection
 *
 * @param oldTrack the old track connection
 * @param newTrack the new track connection
 * @return true if successful
 */
/*public*/ bool PositionablePointView::replaceTrackConnection(/*@CheckForNull*/ TrackSegment* oldTrack, /*@CheckForNull*/ TrackSegment* newTrack) {
    bool result = false; // assume failure (pessimist!)
    // trying to replace old track with null?
    if (newTrack == nullptr) {
        // (yes) remove old connection
        if (oldTrack != nullptr) {
            result = true;  // assume success (optimist!)
            if (getConnect1() == oldTrack) {
                positionablePoint->setConnect1(nullptr);        // disconnect getConnect1()
                reCheckBlockBoundary();
                removeLinkedPoint();
                positionablePoint->setConnect1(getConnect2());    // Move getConnect2() to getConnect1()
                positionablePoint->setConnect2Actual(nullptr);        // disconnect getConnect2()
            } else if (getConnect2() == oldTrack) {
                positionablePoint->setConnect2Actual(nullptr);
                reCheckBlockBoundary();
            } else {
                result = false; // didn't find old connection
            }
        } else {
            result = false; // can't replace null with null
        }
        if (!result) {
            log->error(tr("%1.replaceTrackConnection(%2, %3); Attempt to remove non-existant track connection").arg(
                    getName(), (oldTrack == nullptr) ? "null" : oldTrack->getName(), "null"));
        }
    } else // already connected to newTrack?
    if ((getConnect1() != newTrack) && (getConnect2() != newTrack)) {
        // (no) find a connection we can connect to
        result = true;  // assume success (optimist!)
        if (getConnect1() == oldTrack) {
            positionablePoint->setConnect1(newTrack);
        } else if ((getType() == PositionablePoint::PointType::ANCHOR) && (getConnect2() == oldTrack)) {
            positionablePoint->setConnect2Actual(newTrack);
            if (getConnect1()->getLayoutBlock() == getConnect2()->getLayoutBlock()) {
                westBoundSignalMastNamed = nullptr;
                eastBoundSignalMastNamed = nullptr;
                setWestBoundSensor("");
                setEastBoundSensor("");
            }
        } else {
            log->error(tr("%1.replaceTrackConnection(%2, %3); Attempt to assign more than allowed number of connections").arg(
                    getName(), (oldTrack == nullptr) ? "null" : oldTrack->getName(), newTrack->getName()));
            result = false;
        }
    } else {
        log->warn(tr("%1.replaceTrackConnection(%2, %3); Already connected").arg(
                getName(), (oldTrack == nullptr) ? "null" : oldTrack->getName(), newTrack->getName()));
        result = false;
    }
    return result;
}   // replaceTrackConnection

void PositionablePointView::removeSML(SignalMast* signalMast) {
    if (signalMast == nullptr) {
        return;
    }
    if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager")
    )->isAdvancedRoutingEnabled() && ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager")
    )->isSignalMastUsed(signalMast)) {
        SignallingGuiTools::removeSignalMastLogic(
                nullptr, signalMast);
    }
}

/*protected*/ int PositionablePointView::maxWidth() {
    return 5;
}

/*protected*/ int PositionablePointView::maxHeight() {
    return 5;
}

/*public*/ void PositionablePointView::mousePressed(QGraphicsSceneMouseEvent* e) {
    // remember where we are
    xClick = e->pos().x();
    yClick = e->pos().y();
    // if (debug) log->debug("Pressed: "+where(e));
//    if (e->isPopupTrigger()) {
//        showPopup(e);
//    }
}

/*public*/ void PositionablePointView::mouseReleased(QGraphicsSceneMouseEvent* e) {
    // if (debug) log->debug("Release: "+where(e));
//    if (e.isPopupTrigger()) {
//        showPopup(e);
//    }
  if((e->buttons()& Qt::RightButton) != 0)
  {
   showPopup(e);
  }
}

/*public*/ void PositionablePointView::mouseClicked(QGraphicsSceneMouseEvent* e) {
//    if (e.isPopupTrigger()) {
//        showPopup(e);
//    }
  if((e->buttons()& Qt::RightButton) != 0)
  {
   showPopup(e);
  }
}


/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*protected*/ QMenu* PositionablePointView::showPopup(/*@Nonnull*/  QGraphicsSceneMouseEvent* mouseEvent) {
  // TODO: incorporate latest Java code!!

  if (popup != nullptr )
  {
   popup->clear();
  }
  else
  {
   popup = new QMenu();
  }

  bool blockBoundary = false;
  bool addSensorsAndSignalMasksMenuItemsFlag = false;
  QMenu* jmi = nullptr;
  LayoutBlock* block1 = nullptr;
  LayoutBlock* block2 = nullptr;
  switch (getType())
  {
  case PositionablePoint::ANCHOR:
  {
   popup->addMenu(jmi = new QMenu(tr("Anchor ")+ getId()));
   jmi->setEnabled(false);
   if (getConnect1() != nullptr) {
       block1 = getConnect1()->getLayoutBlock();
   }
   if (getConnect2() != nullptr) {
       block2 = getConnect2()->getLayoutBlock();
   }
   if ( (block1!=nullptr) && (block1==block2) )
   {
    popup->addMenu(jmi =new QMenu(tr("Block")+": "+block1->getId()));
    //jmi = popup->addAction(tr("%1).arg(tr("Block")) + block1->getDisplayName());
   }
   else if ( (block1!=nullptr) && (block2!=nullptr) && (block1!=block2) )
   {
    popup->addMenu(jmi =new QMenu(tr("Block Divider")));
    jmi->setEnabled(false);
    popup->addMenu(jmi =new QMenu(" "+tr("Block1_ID")+": "+block1->getId()));
    jmi->setEnabled(false);
    popup->addMenu(jmi =new QMenu(" "+tr("Block2_ID")+": "+block2->getId()));
    jmi->setEnabled(false);
    blockBoundary = true;
   }
   break;
  }
  case PositionablePoint::END_BUMPER:
  {
   popup->addMenu(jmi = new QMenu(tr("End Bumper ")+ getId()));
   jmi->setEnabled(false);
   LayoutBlock* blockEnd = nullptr;
   if (getConnect1() != nullptr) {
       blockEnd = getConnect1()->getLayoutBlock();
   }
   if (blockEnd!=nullptr)
   {
    popup->addMenu(jmi = new QMenu(tr("BlockID")+": "+blockEnd->getId()));
   }
   addSensorsAndSignalMasksMenuItemsFlag = true;
   break;
  }
  case PositionablePoint::EDGE_CONNECTOR:
  {
   jmi = popup->addMenu(tr("%1:").arg(tr("Edge Connector")) + getName());
   jmi->setEnabled(false);

   if (getLinkedEditor() != nullptr) {
       QString linkName = getLinkedEditorName() + ":" + getLinkedPointId();
       jmi = popup->addMenu(tr("Linked to %1").arg(linkName));
   } else {
       jmi = popup->addMenu(tr("Not Linked"));
   }
   jmi->setEnabled(false);

   block1 = nullptr;
   if (getConnect1() != nullptr) {
       block1 = getConnect1()->getLayoutBlock();
   }
   block2 = block1;
   if (getLinkedPoint() != nullptr) {
       if (getLinkedPoint()->getConnect1() != nullptr) {
           block2 = getLinkedPoint()->getConnect1()->getLayoutBlock();
       }
   }
   if ((block1 != nullptr) && (block1 == block2)) {
       jmi = popup->addMenu(tr("%1:").arg("Block") + block1->getDisplayName());
   } else if ((block1 != nullptr) && (block2 != nullptr) && (block1 != block2)) {
       jmi = popup->addMenu(tr("Block Divider"));
       jmi->setEnabled(false);
       jmi = popup->addMenu(tr("%1:").arg("Block_ID", 1) + block1->getDisplayName());
       jmi->setEnabled(false);
       jmi = popup->addMenu(tr("%1:").arg("Block_ID", 2) + block2->getDisplayName());
       jmi->setEnabled(false);
       blockBoundary = true;
   }
   break;
  }
  default : break;
  }
  // if there are any track connections
  QAction* act;
 if ((getConnect1() != nullptr) || (getConnect2() != nullptr)) {
     QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
     if (getConnect1() != nullptr) {
         connectionsMenu->addAction(act =new AbstractAction(tr("%1:").arg("1") + getConnect1()->getName(),this));
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
//             }
         });
     }
     if (getConnect2() != nullptr) {
         connectionsMenu->addAction(act = new AbstractAction(tr("%1:").arg("2") + getConnect2()->getName(),this));
         {
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
//             }
          });
         }
     }
     popup->addMenu(connectionsMenu);
 }

 if (getConnect1() != nullptr && (getType() == PositionablePoint::PointType::EDGE_CONNECTOR || getType() == PositionablePoint::PointType::END_BUMPER))
 {
     //
     // decorations menu
     //
     popup->addSeparator();

     QMenu* decorationsMenu = new QMenu(tr("Decorations"));
     decorationsMenu->setToolTip(tr("Select this menu to change decoration settings"));
     popup->addMenu(decorationsMenu);

     JCheckBoxMenuItem* jcbmi;
     TrackSegmentView* ctv1 = layoutEditor->getTrackSegmentView(getConnect1());

     if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
         QMenu* arrowsMenu = new QMenu(tr("Arrows"));
         decorationsMenu->setToolTip(tr("Select this menu to change arrow decoration settings"));
         decorationsMenu->addMenu(arrowsMenu);

         QMenu* arrowsCountMenu = new QMenu(tr("Style"));
         arrowsCountMenu->setToolTip(tr("DecorationStyleMenuToolTip"));
         arrowsMenu->addMenu(arrowsCountMenu);

         jcbmi = new JCheckBoxMenuItem(tr("None"),this);
         arrowsCountMenu->addAction(jcbmi);
         jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
//         jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
             if (getConnect1()->getConnect1() == positionablePoint) {
                 ctv1->setArrowEndStart(false);
             }
             if (getConnect1()->getConnect2() == positionablePoint) {
                 ctv1->setArrowEndStop(false);
             }
             if (!ctv1->isArrowEndStart() && !ctv1->isArrowEndStop()) {
                 ctv1->setArrowStyle(0);
             }
         });
         bool etherEnd = ((getConnect1()->getConnect1() == positionablePoint) && ctv1->isArrowEndStart())
                 || ((getConnect1()->getConnect2() == positionablePoint) && ctv1->isArrowEndStop());

         jcbmi->setChecked((ctv1->getArrowStyle() == 0) || !etherEnd);

         // configure the arrows
         for (int i = 1; i < NUM_ARROW_TYPES; i++) {
             jcbmi = loadArrowImageToJCBItem(i, arrowsCountMenu);
             /*final*/ int n = i;
//             jcbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
             connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
              if (getConnect1()->getConnect1() == positionablePoint) {
                     ctv1->setArrowEndStart(true);
                 }
                 if (getConnect1()->getConnect2() == positionablePoint) {
                     ctv1->setArrowEndStop(true);
                 }
                 ctv1->setArrowStyle(n);
             });
             jcbmi->setChecked((ctv1->getArrowStyle() == i) && etherEnd);
         }

         QMenu* arrowsDirMenu = new QMenu(tr("Direction"));
         arrowsDirMenu->setToolTip(tr("Select the direction to point the arrows"));
         arrowsMenu->addMenu(arrowsDirMenu);

         jcbmi = new JCheckBoxMenuItem(tr("None"),this);
         arrowsDirMenu->addAction(jcbmi);
         jcbmi->setToolTip(tr("Select this to remove this decoration from this track"));
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
          TrackSegmentView* ctv = layoutEditor->getTrackSegmentView(getConnect1());
             ctv->setArrowDirIn(false);
             ctv->setArrowDirOut(false);
         });
         jcbmi->setChecked(!ctv1->isArrowDirIn() && !ctv1->isArrowDirOut());

         jcbmi = new JCheckBoxMenuItem(tr("In"), this);
         arrowsDirMenu->addAction(jcbmi);
         jcbmi->setToolTip(tr("elect this to draw arrows pointing in"));
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
             TrackSegmentView* ctv = layoutEditor->getTrackSegmentView(getConnect1());
             ctv->setArrowDirIn(true);
             ctv->setArrowDirOut(false);
         });
         jcbmi->setChecked(ctv1->isArrowDirIn() && !ctv1->isArrowDirOut());

         jcbmi = new JCheckBoxMenuItem(tr("Out"),this);
         arrowsDirMenu->addAction(jcbmi);
         jcbmi->setToolTip(tr("ArrowsDirectionOutMenuItemToolTip"));
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
             TrackSegmentView* ctv = layoutEditor->getTrackSegmentView(getConnect1());
             ctv->setArrowDirOut(true);
             ctv->setArrowDirIn(false);
         });
         jcbmi->setChecked(!ctv1->isArrowDirIn() && ctv1->isArrowDirOut());

         jcbmi = new JCheckBoxMenuItem(tr("Both"),this);
         arrowsDirMenu->addAction(jcbmi);
         jcbmi->setToolTip(tr("Select this to draw arrow(s) pointing in and out"));
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
             TrackSegmentView* ctv = layoutEditor->getTrackSegmentView(getConnect1());
             ctv->setArrowDirIn(true);
             ctv->setArrowDirOut(true);
         });
         jcbmi->setChecked(ctv1->isArrowDirIn() && ctv1->isArrowDirOut());

         jmi = arrowsMenu->addMenu(tr("Color"));
         jmi->setToolTip(tr("Select this to change the color of this decoration"));
         connect(jcbmi, &JCheckBoxMenuItem::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", ctv->getArrowColor());
             if ((newColor.isValid()) && newColor !=(ctv->getArrowColor())) {
                 ctv->setArrowColor(newColor);
             }
         });

//         jmi->setForeground(ctv1->getArrowColor());
//         jmi->setBackground(ColorUtil::contrast(ctv1->getArrowColor()));

         /*jmi = */arrowsMenu->addAction(act =new QAction(tr("%1:").arg(
                 tr("Line Width")) + QString::number(ctv1->getArrowLineWidth()),this));
         act->setToolTip(tr("Select this to change the line width of this decoration"));
         //jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             //prompt for arrow line width
             int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
                     tr("Line Width"),
                     tr("Line Width"),
                     ctv->getArrowLineWidth());
             ctv->setArrowLineWidth(newValue);
         });

         /*jmi =*/ arrowsMenu->addAction(act = new QAction(tr("%1:").arg(
                 tr("Length")) + ctv1->getArrowLength()));
         act->setToolTip(tr("Select this to change the length of this decoration"));
         //jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             //prompt for arrow length
             int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
                     tr("Length"),
                     tr("Length"),
                     ctv->getArrowLength());
             ctv->setArrowLength(newValue);
         });

         /*jmi =*/ arrowsMenu->addAction(act = new QAction(tr("%1:").arg(
                 tr("Space")) + ctv1->getArrowGap()));
         jmi->setToolTip(tr("Select this to change the space between multiple decorations"));
         //jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             //prompt for arrow gap
             int newValue = QuickPromptUtil::promptForInt((Component*)layoutEditor,
                     tr("Space"),
                     tr("Space"),
                     ctv->getArrowGap());
             ctv->setArrowGap(newValue);
         });
     } // if (getType() == EDGE_CONNECTOR)

     if (getType() == PositionablePoint::PointType::END_BUMPER) {
         QMenu* endBumperMenu = new QMenu(tr("End Bumpers"));
         decorationsMenu->setToolTip(tr("Select this menu to change the end bumper decoration settings"));
         decorationsMenu->addMenu(endBumperMenu);

         JCheckBoxMenuItem* enableCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Enable"),this);
         enableCheckBoxMenuItem->setToolTip(tr("Select this menu to enable or disable the end bumper decoration"));

         endBumperMenu->addAction(enableCheckBoxMenuItem);
//         enableCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(enableCheckBoxMenuItem, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             if (getConnect1()->getConnect1() == positionablePoint) {
                 ctv->setBumperEndStart(enableCheckBoxMenuItem->isChecked());
             }
             if (getConnect1()->getConnect2() == positionablePoint) {
                 ctv->setBumperEndStop(enableCheckBoxMenuItem->isChecked());
             }
         });
         if (getConnect1()->getConnect1() == positionablePoint) {
             enableCheckBoxMenuItem->setChecked(ctv1->isBumperEndStart());
         }
         if (getConnect1()->getConnect2() == positionablePoint) {
             enableCheckBoxMenuItem->setChecked(ctv1->isBumperEndStop());
         }

         /*jmi =*/ endBumperMenu->addAction(act =new QAction(tr("Color"),this));
         act->setToolTip(tr("Select this to change the color of this decoration"));
//         jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             QColor newColor = JmriColorChooser::showDialog(nullptr, "Choose a color", ctv->getBumperColor());
             if ((!newColor.isValid()) && newColor!=(ctv->getBumperColor())) {
                 ctv->setBumperColor(newColor);
             }
         });
#if 1
//         jmi->setForeground(ctv1->getBumperColor());
//         jmi->setBackground(ColorUtil.contrast(ctv1->getBumperColor()));

         /*jmi =*/ endBumperMenu->addAction(new QAction(tr("%1:").arg(
                 tr("Line Width")) + ctv1->getBumperLineWidth(), this));
         act->setToolTip(tr("Select this to change the line width of this decoration"));
//         jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{
             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             //prompt for width
             int newValue = QuickPromptUtil::promptForInteger((Component*)layoutEditor,
                     tr("Line Width"),
                     tr("Line Width"),
                     ctv->getBumperLineWidth(), new QIntValidator(0, TrackSegmentView::MAX_BUMPER_WIDTH));
//                                                              [=] (int t) {
//                         if (t < 0 || t > TrackSegmentView::MAX_BUMPER_WIDTH) {
//                             throw  IllegalArgumentException(
//                                     tr("Value must be 0-%1").arg(TrackSegmentView::MAX_BUMPER_WIDTH));
//                         }
//                         return true;
//                     });
             ctv->setBumperLineWidth(newValue);
         });

         /*jmi =*/ endBumperMenu->addAction(act = new QAction(tr("%1:").arg(
                 tr("Length")) + QString::number(ctv1->getBumperLength())));
         act->setToolTip(tr("Select this to change the length of this decoration"));
//         jmi->addActionListener((java.awt.event.ActionEvent e3) -> {
         connect(act, &QAction::triggered, [=]{

             TrackSegmentView*  ctv = layoutEditor->getTrackSegmentView(getConnect1());
             //prompt for length
             int newValue = QuickPromptUtil::promptForInteger((Component*)layoutEditor,
                     tr("Length"),
                     tr("Length"),
                     ctv->getBumperLength(), new QIntValidator(0, TrackSegmentView::MAX_BUMPER_LENGTH));
//                                                              [=](int t) {
//                         if (t < 0 || t > TrackSegmentView::MAX_BUMPER_LENGTH) {
//                             throw  IllegalArgumentException(
//                                     tr("Value must be 0-%1").arg(TrackSegmentView::MAX_BUMPER_LENGTH));
//                         }
//                         return true;
//                     });
             ctv->setBumperLength(newValue);
         });
#endif

     }

 }   // if ((getType() == EDGE_CONNECTOR) || (getType() == END_BUMPER))

 popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));
#if 1
 if (getType() == PositionablePoint::PointType::ANCHOR) {
     if (blockBoundary) {
         /*jmi =*/ popup->addAction(act =new QAction(tr("Cannot Merge at Block Boundary")));
         act->setEnabled(false);
     } else if ((getConnect1() != nullptr) && (getConnect2() != nullptr)) {
         /*jmi =*/ popup->addAction(new AbstractAction(tr("Merge Adjacent Tracks"),this));
//      {
//             @Override
//             public void actionPerformed(ActionEvent e) {
      connect(act, &QAction::triggered, [=]{
                 PositionablePoint* pp_this = positionablePoint;
                 // if I'm fully connected...
                 if ((getConnect1() != nullptr) && (getConnect2() != nullptr)) {
                     // who is my connection 2 connected to (that's not me)?
                     LayoutTrack* newConnect2 = nullptr;
                     HitPointType::TYPES newType2 = HitPointType::TRACK;
                     if (getConnect2()->getConnect1() == pp_this) {
                         newConnect2 = getConnect2()->getConnect2();
                         newType2 = getConnect2()->type2;
                     } else if (getConnect2()->getConnect2() == pp_this) {
                         newConnect2 = getConnect2()->getConnect1();
                         newType2 = getConnect2()->type1;
                     } else {
                         //this should never happen however...
                         log->error("Join: wrong getConnect2() error.");
                     }

                     // connect the other connection to my connection 2 to my connection 1
                     if (newConnect2 == nullptr) {
                         // (this should NEVER happen... however...)
                         log->error("Merge: no 'other' connection to getConnect2().");
                     } else {
                         if (qobject_cast<PositionablePoint*>(newConnect2)) {
                             PositionablePoint* pp = (PositionablePoint*) newConnect2;
                             pp->replaceTrackConnection(getConnect2(), getConnect1());
                         } else {
                             layoutEditor->setLink(newConnect2, newType2, getConnect1(), HitPointType::TRACK);
                         }
                         // connect the track at my getConnect1() to the newConnect2
                         if (getConnect1()->getConnect1() == pp_this) {
                             getConnect1()->setNewConnect1(newConnect2, newType2);
                         } else if (getConnect1()->getConnect2() == pp_this) {
                             getConnect1()->setNewConnect2(newConnect2, newType2);
                         } else {
                             // (this should NEVER happen... however...)
                             log->error("Merge: no connection to connection 1.");
                         }
                     }

                     // remove connection 2 from selection information
                     if (layoutEditor->selectedObject == getConnect2()) {
                         layoutEditor->selectedObject = nullptr;
                     }
                     if (layoutEditor->prevSelectedObject == getConnect2()) {
                         layoutEditor->prevSelectedObject = nullptr;
                     }

                     // remove connection 2 from the layoutEditor's list of layout tracks
                     layoutEditor->removeLayoutTrackAndRedraw(getConnect2());

                     // update affected block
                     LayoutBlock* block = getConnect2()->getLayoutBlock();
                     if (block != nullptr) {
                         //decrement Block use count
                         block->decrementUse();
                         layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
                         block->updatePaths();
                     }
                     getConnect2()->remove();
                     positionablePoint->setConnect2Actual(nullptr);

                     //remove this PositionablePoint from selection information
                     if (layoutEditor->selectedObject == pp_this) {
                         layoutEditor->selectedObject = nullptr;
                     }
                     if (layoutEditor->prevSelectedObject == pp_this) {
                         layoutEditor->prevSelectedObject = nullptr;
                     }

                     // remove this PositionablePoint and PositionablePointView from the layoutEditor's list of layout tracks
                     layoutEditor->removeLayoutTrackAndRedraw(pp_this);
                     pp_this->remove();
                     dispose();

                     layoutEditor->setDirty();
                     layoutEditor->redrawPanel();
                 } else {
                     // (this should NEVER happen... however...)
                     log->error("Merge: missing connection(s).");
                 }
//             }
         });
     }
 }
#endif
 popup->addAction(act = new AbstractAction(tr("Delete"), this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e
//     ) {
 connect(act, &QAction::triggered, [=]{

         if (canRemove() && layoutEditor->removePositionablePoint(positionablePoint)) {
             // user is serious about removing this point from the panel
             remove();
             dispose();
         }
//     }
 });

 QMenu* lineType = new QMenu(tr("Change To"));
 /*jmi =*/ lineType->addAction(act = new JCheckBoxMenuItem(tr("Anchor"), this));//(new AbstractAction(Bundle.getMessage("Anchor"))
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
         setTypeAnchor();
//     }
 });

 act->setChecked(getType() == PositionablePoint::PointType::ANCHOR);
#if 1
 // you can't change it to an anchor if it has a 2nd connection
 // TODO: add error dialog if you try?
 if ((getType() == PositionablePoint::PointType::EDGE_CONNECTOR) && (getConnect2() != nullptr)) {
     jmi->setEnabled(false);
 }

 /*jmi =*/ lineType->addAction(act = new JCheckBoxMenuItem(tr("End Bumper"),this));
// {
//     @Override
//     public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
         setTypeEndBumper();
//     }
 });

 act->setChecked(getType() == PositionablePoint::PointType::END_BUMPER);

 /*jmi =*/ lineType->addAction(act =new JCheckBoxMenuItem(tr("Edge Connector"),this));
//                               {
//     @Override
//     public void actionPerformed(ActionEvent e) {
   connect(act, &QAction::triggered, [=]{
         setTypeEdgeConnector();
//     }
 });

 act->setChecked(getType() == PositionablePoint::PointType::EDGE_CONNECTOR);

 popup->addMenu(lineType);

 if (!blockBoundary && getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
     popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));
     popup->addAction(act = new AbstractAction(tr("Edit Link"),this));
//     {
//         @Override
//         public void actionPerformed(ActionEvent e) {
     connect(act, &QAction::triggered, [=]{
             setLink();
//         }
     });
 }

 if (blockBoundary) {
     popup->addSeparator();// new JSeparator(JSeparator.HORIZONTAL));
     if (getType() == PositionablePoint::PointType::EDGE_CONNECTOR) {
         popup->addAction(new AbstractAction(tr("Edit Link"),this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
//             }
         });
         popup->addAction(act = new AbstractAction(tr("Set Signal Heads..."),this));
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(act, &QAction::triggered, [=]{
                 // bring up signals at edge connector tool dialog
                 layoutEditor->getLETools()->setSignalsAtBlockBoundaryFromMenu(positionablePoint,
                         getLayoutEditorToolBarPanel()->signalIconEditor,
                         getLayoutEditorToolBarPanel()->signalFrame);
//             }
         });
     } else {
         AbstractAction* ssaa = new AbstractAction(tr("Set Signal Heads..."),this);
//         {
//             @Override
//             public void actionPerformed(ActionEvent e) {
         connect(ssaa, &QAction::triggered, [=]{

                 // bring up signals at level crossing tool dialog
                 layoutEditor->getLETools()->setSignalsAtBlockBoundaryFromMenu(positionablePoint,
                         getLayoutEditorToolBarPanel()->signalIconEditor,
                         getLayoutEditorToolBarPanel()->signalFrame);
//             }
         });

         QMenu* jm = new QMenu(tr("Set Signal Heads..."));
         if (layoutEditor->getLETools()->addBlockBoundarySignalHeadInfoToMenu(positionablePoint, jm)) {
             jm->addAction(ssaa);
             popup->addMenu(jm);
         } else {
             popup->addAction(ssaa);
         }
     }
     addSensorsAndSignalMasksMenuItemsFlag = true;
 }
#endif
 if (addSensorsAndSignalMasksMenuItemsFlag) {
     popup->addAction(act =new AbstractAction(tr("Set Signal Masts..."),this));
//     {
//         @Override
//         public void actionPerformed(ActionEvent event) {
     connect(act, &QAction::triggered, [=]{
             // bring up signals at block boundary tool dialog
             layoutEditor->getLETools()->setSignalMastsAtBlockBoundaryFromMenu(positionablePoint);
//         }
     });
     popup->addAction(new AbstractAction(tr("Set Sensors..."),this));
//     {
//         @Override
//         public void actionPerformed(ActionEvent event) {
       connect(act, &QAction::triggered, [=]{
             // bring up signals at block boundary tool dialog
             layoutEditor->getLETools()->setSensorsAtBlockBoundaryFromMenu(positionablePoint,
                     getLayoutEditorToolBarPanel()->sensorIconEditor,
                     getLayoutEditorToolBarPanel()->sensorFrame);
//         }
     });
 }

 layoutEditor->setShowAlignmentMenu(popup);

 popup->exec(QCursor::pos());
 return popup;
}   // showPopup

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool PositionablePointView::canRemove() {
    QList<QString> itemList = QList<QString>();
    // A has two track segments, EB has one, EC has one plus optional link

    TrackSegment* ts1 = getConnect1();
    TrackSegment* ts2 = getConnect2();

    if (ts1 != nullptr) {
        //itemList.addAll(getSegmentReferences(ts1));
     for(QString s : getSegmentReferences(ts1))
      itemList.append(s);
    }
    if (ts2 != nullptr) {
        for (QString item : getSegmentReferences(ts2)) {
            // Do not add duplicates
            if (!itemList.contains(item)) {
                itemList.append(item);
            }
        }
    }

    if (!itemList.isEmpty()) {
        QString typeName = "";
        switch (getType()) {
            case PositionablePoint::ANCHOR:
                typeName = "Anchor";  // NOI18N
                break;
            case PositionablePoint::END_BUMPER:
                typeName = "EndBumper";  // NOI18N
                break;
            case PositionablePoint::EDGE_CONNECTOR:
                typeName = "EdgeConnector";  // NOI18N
                break;
            default:
                typeName = "Unknown type (" + QString::number(getType()) + ")";  // NOI18N
                break;
        }
        displayRemoveWarningDialog(itemList, typeName);
    }
    return itemList.isEmpty();
}

/**
 * Build a list of sensors, signal heads, and signal masts attached to a
 * connection point.
 *
 * @param ts The track segment to be checked.
 * @return a list of bean reference names.
 */
/*public*/ QList<QString> PositionablePointView::getSegmentReferences(TrackSegment* ts) {
    QList<QString> items = QList<QString>();

    HitPointType::TYPES type1 = ts->getType1();
    LayoutTrack* conn1 = ts->getConnect1();
    //items.addAll(ts.getPointReferences(type1, conn1));
    for(QString s : ts->getPointReferences(type1, conn1))
     items.append(s);

    HitPointType::TYPES type2 = ts->getType2();
    LayoutTrack* conn2 = ts->getConnect2();
    //items.addAll(ts.getPointReferences(type2, conn2));
    for(QString s : ts->getPointReferences(type2, conn2))
     items.append(s);

    return items;
}

/**
 * Clean up when this object is no longer needed. Should not be called while
 * the object is still displayed; see remove()
 */
void PositionablePointView::dispose() {
    if (popup != nullptr) {
        popup->clear();
    }
    popup = nullptr;
    removeLinkedPoint();
}

/**
 * Removes this object from display and persistence
 */
/*private*/ void PositionablePointView::remove() {
    // remove from persistence by flagging inactive
    active = false;
}


/**
 * @return "active" true means that the object is still displayed, and
 *         should be stored.
 */
/*protected*/ bool PositionablePointView::isActive() {
    return active;
}

/*protected*/ int PositionablePointView::getConnect1Dir() {
    int result = Path::NONE;

    TrackSegment* ts1 = getConnect1();
    if (ts1 != nullptr) {
        QPointF p1;
        if (ts1->getConnect1() == positionablePoint) {
            p1 = layoutEditor->getCoords(ts1->getConnect2(), ts1->getType2());
        } else {
            p1 = layoutEditor->getCoords(ts1->getConnect1(), ts1->getType1());
        }
        result = Path::computeDirection(getCoordsCenter(), p1);
    }
    return result;
}


void PositionablePointView::setLink() {
    if (getConnect1() == nullptr || getConnect1()->getLayoutBlock() == nullptr) {
        log->error(tr("%1->setLink(); Can not set link until we have a connecting track with a block assigned").arg(getName()));
        return;
    }
    editLink = new JDialog();
#if 1
    editLink->setTitle(tr("Edit Link from %1").arg(getConnect1()->getLayoutBlock()->getDisplayName()));

    JPanel* container = new JPanel();
    container->setLayout(new BorderLayout());

    JButton* done = new JButton(("Done"));
    //done.addActionListener((ActionEvent a) -> updateLink());
    connect(done, &QPushButton::clicked, [=]{updateLink();});

    ((BorderLayout*)container->layout())->addWidget(getLinkPanel(), BorderLayout::North);
    ((BorderLayout*)container->layout())->addWidget(done, BorderLayout::South);
    container->update();

    editLink->layout()->addWidget(container);

    // make this button the default button (return or enter activates)
//    JRootPane* rootPane = SwingUtilities.getRootPane(done);
//    rootPane->setDefaultButton(done);
    done->setDefault(true);

    editLink->pack();
    editLink->setModal(false);
    editLink->setVisible(true);
#endif
}


/*public*/ JPanel* PositionablePointView::getLinkPanel() {
#if 1
    editorCombo = new JComboBox();
    QSet<Editor*> panels = ((EditorManager*)InstanceManager::getDefault("EditorManager"))
            ->getAll("LayoutEditor");
    //editorCombo->addItem(new JCBHandle<Editor*>("None"));
    editorCombo->addItem("None");
    //if (panels.contains(layoutEditor)) {
    //    panels.remove(layoutEditor);
    //}
    for (Editor* p : panels) {
//        JCBHandle<Editor*> h =  JCBHandle<Editor*>(p);
        editorCombo->addItem(p->metaObject()->className(), VPtr<Editor>::asQVariant(p));
        if (p == getLinkedEditor()) {
            editorCombo->setSelectedItem(p->metaObject()->className());
        }
    }

    //ActionListener selectPanelListener = (ActionEvent a) -> updatePointBox();

    //editorCombo.addActionListener(selectPanelListener);
    connect(editorCombo, &JComboBox::currentIndexChanged, [=]{
     updatePointBox();
    });
#endif
    JPanel* selectorPanel = new JPanel();
#if 1
    selectorPanel->layout()->addWidget(new JLabel(tr("Select Panel")));
    selectorPanel->layout()->addWidget(editorCombo);
    linkPointsBox = new JComboBox();
    updatePointBox();
    selectorPanel->layout()->addWidget(new JLabel(tr("Connecting to")));
    selectorPanel->layout()->addWidget(linkPointsBox);
#endif
    return selectorPanel;
}

void PositionablePointView::updatePointBox() {
    linkPointsBox->clear();
    pointList = QList<PositionablePoint*>();
    if (editorCombo->getSelectedIndex() == 0) {
        linkPointsBox->setEnabled(false);
        return;
    }
#if 0
    linkPointsBox->setEnabled(true);
    LayoutEditor* le = editorCombo->getItemAt(editorCombo->getSelectedIndex()).item();
    for (PositionablePoint p : le.getPositionablePoints()) {
        if (p.getType() == PointType.EDGE_CONNECTOR) {
            if (p.getLinkedPoint() == positionablePoint) {
                pointList.add(p);
                linkPointsBox.addItem(p.getName());
                linkPointsBox->setSelectedItem(p.getName());
            } else if (p.getLinkedPoint() == nullptr) {
                if (p != positionablePoint) {
                if (p->getConnect1() != null && p->getConnect1().getLayoutBlock() != nullptr) {
                    if (p->getConnect1().getLayoutBlock() != getConnect1().getLayoutBlock()) {
                        pointList.add(p);
                            linkPointsBox.addItem(p.getName());
                        }
                    }
                }
            }
        }
    }
    editLink.pack();
#endif
} // updatePointBox

/*public*/ void PositionablePointView::updateLink() {
#if 0
    if (editorCombo.getSelectedIndex() == 0 || linkPointsBox.getSelectedIndex() == -1) {
        if (getLinkedPoint() != null && getConnect2() != nullptr) {
            String removeremote = nullptr;
            String removelocal = nullptr;
            if (getConnect1Dir() == Path::EAST || getConnect1Dir() == Path::SOUTH) {
                removeremote = getLinkedPoint().getEastBoundSignal();
                removelocal = getWestBoundSignal();
                getLinkedPoint()->setEastBoundSignal("");
            } else {
                removeremote = getLinkedPoint().getWestBoundSignal();
                removelocal = getEastBoundSignal();
                getLinkedPoint()->setWestBoundSignal("");

            }
            // removelocal and removeremote have been set here.
            if (!removeremote.isEmpty()) {
                jmri.SignalHead sh = InstanceManager.getDefault(jmri.SignalHeadManager.class
                ).getSignalHead(removeremote);
                getLinkedEditor().removeSignalHead(sh);
                jmri.jmrit.blockboss.BlockBossLogic.getStoppedObject(removeremote);

            }
            if (!removelocal.isEmpty()) {
                jmri.SignalHead sh = InstanceManager.getDefault(jmri.SignalHeadManager.class
                ).getSignalHead(removelocal);
                layoutEditor->removeSignalHead(sh);
                jmri.jmrit.blockboss.BlockBossLogic.getStoppedObject(removelocal);
            }
        }
        setLinkedPoint(nullptr);
    } else {
        setLinkedPoint(pointList.get(linkPointsBox.getSelectedIndex()));
    }
    editLink->setVisible(false);
#endif
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ HitPointType::TYPES PositionablePointView::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    HitPointType::TYPES result = HitPointType::NONE;  // assume point not on connection
    //note: optimization here: instead of creating rectangles for all the
    // points to check below, we create a rectangle for the test point
    // and test if the points below are in that rectangle instead.
    QRectF r = layoutEditor->layoutEditorControlCircleRectAt(hitPoint);
    QPointF p, minPoint = MathUtil::zeroPoint2D;

    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double distance, minDistance = INFINITY;

    if (!requireUnconnected || (getConnect1() == nullptr)
            || ((getType() == PositionablePoint::PointType::ANCHOR) && (getConnect2() == nullptr))) {
        // test point control rectangle
        p = getCoordsCenter();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = HitPointType::POS_POINT;
        }
    }
    if ((useRectangles && !r.contains(minPoint))
            || (!useRectangles && (minDistance > circleRadius))) {
        result = HitPointType::NONE;
    }
    return result;
}   // findHitPointType

/**
 * return the coordinates for a specified connection type
 *
 * @param connectionType the connection type
 * @return the coordinates for the specified connection type
 */
//@Override
/*public*/ QPointF PositionablePointView::getCoordsForConnectionType(HitPointType::TYPES connectionType) {
    QPointF result = getCoordsCenter();
    if (connectionType != HitPointType::POS_POINT) {
        log->error(tr("%1.getCoordsForConnectionType(%1); Invalid Connection Type").arg(
                getName(), HitPointType::toString(connectionType))); //I18IN
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ LayoutTrack* PositionablePointView::getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ {
    LayoutTrack* result = nullptr;
    if (connectionType == HitPointType::POS_POINT) {
        result = getConnect1();
        if (nullptr == result) {
            result = getConnect2();
        }
    } else {
        QString errString = tr("%1->getConnection(%2); Invalid Connection Type").arg(
                getName(), HitPointType::toString(connectionType)); //I18IN
        log->error(tr("will throw %1").arg(errString));
        throw new JmriException(errString);
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ {
    if ((type != HitPointType::TRACK) && (type != HitPointType::NONE)) {
        QString errString = tr("%1->setConnection(%2, %3, %4); unexpected type").arg(
                getName(), HitPointType::toString(connectionType), (o == nullptr) ? "null" : o->getName(), HitPointType::toString(type)); //I18IN
        log->error(tr("will throw %1").arg(errString)); //I18IN
        throw new JmriException(errString);
    }
    if (connectionType != HitPointType::POS_POINT) {
        QString errString = tr("%1->setConnection(%2, %3, %4); Invalid Connection Type").arg(
                getName(), HitPointType::toString(connectionType), (o == nullptr) ? "null" : o->getName(), HitPointType::toString(type)); //I18IN
        log->error(tr("will throw %1").arg(errString)); //I18IN
        throw new JmriException(errString);
    }
}

/**
 * return true if this connection type is disconnected
 *
 * @param connectionType the connection type to test
 * @return true if the connection for this connection type is free
 */
//@Override
/*public*/ bool PositionablePointView::isDisconnected(HitPointType::TYPES connectionType) {
    bool result = false;
    if (connectionType == HitPointType::POS_POINT) {
        result = ((getConnect1() == nullptr) || (getConnect2() == nullptr));
    } else {
        log->error(tr("%1.isDisconnected({}); Invalid Connection Type").arg(
                getName(), HitPointType::toString(connectionType))); //I18IN
    }
    return result;
}

/**
 * Draw track decorations.
 *
 * This type of track has none, so this method is empty.
 */
//@Override
/*protected*/ void PositionablePointView::drawDecorations(EditScene* /*g2*/) {
//    log->trace("PositionablePointView::drawDecorations");
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePointView::draw1(EditScene* /*g2*/, bool /*isMain*/, bool /*isBlock*/) {
    //nothing to do here... move along...
//    log->trace("PositionablePointView::draw1");
}   // draw1

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePointView::draw2(EditScene* /*g2*/, bool /*isMain*/, float /*railDisplacement*/) {
    //nothing to do here... move along...
    log->trace("PositionablePointView::draw2");
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePointView::highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) {
     if ((specificType == HitPointType::NONE) || (specificType == HitPointType::POS_POINT)) {
         if ((getConnect1() == nullptr)
                 || ((getType() == PositionablePoint::ANCHOR) && (getConnect2() == nullptr))) {
  // TODO:           g2.fill(layoutEditor->trackControlCircleAt(getCoordsCenter()));
          QGraphicsEllipseItem* circleItem = trackControlCircleAt(getCoordsCenter());
          g2->addItem(circleItem);
         }
     }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePointView::drawEditControls(EditScene* g2) {
  QPen stroke = QPen(Qt::black, 1);
  if(rects!=nullptr && rects->scene()!=nullptr)
  {
   g2->removeItem(rects);
   rects = nullptr;
  }
  TrackSegment* ts1 = getConnect1();
  if (ts1 == nullptr)
  {
      //g2.setColor(Color.red);
   stroke.setColor(QColor(Qt::red));
  }
  else {
      TrackSegment* ts2 = nullptr;
      if (getType() == PositionablePoint::ANCHOR) {
          ts2 = getConnect2();
      } else if (getType() == PositionablePoint::EDGE_CONNECTOR) {
          if (getLinkedPoint() != nullptr) {
              ts2 = getLinkedPoint()->getConnect1();
          }
      }
      if ((getType() != PositionablePoint::END_BUMPER) && (ts2 == nullptr)) {
          //g2.setColor(Color.yellow);
       stroke.setColor(QColor(Qt::yellow));
      } else {
          //g2.setColor(Color.green);
       stroke.setColor(QColor(Qt::green));
      }
  }
  //g2.draw(layoutEditor->trackEditControlRectAt(getCoordsCenter()));
  QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsCenter()));
    rectItem->setPen(stroke);
  rects = rectItem;
  g2->addItem(rects);
}   // drawEditControls

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePointView::drawTurnoutControls(EditScene* g2) {
    log->trace("PositionablePointView::drawTurnoutControls");
    // PositionablePoints don't have turnout controls...
    // nothing to see here... move along...
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::reCheckBlockBoundary() {
    if (getType() == PositionablePoint::PointType::END_BUMPER) {
        return;
    }
    if (getConnect1() == nullptr && getConnect2() == nullptr) {
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
        if (westBoundSignalMastNamed != nullptr) {
            removeSML(getWestBoundSignalMast());
        }
        if (eastBoundSignalMastNamed != nullptr) {
            removeSML(getEastBoundSignalMast());
        }
        westBoundSignalMastNamed = nullptr;
        eastBoundSignalMastNamed = nullptr;
        setWestBoundSensor("");
        setEastBoundSensor("");
        //TODO: May want to look at a method to remove the assigned mast
        //from the panel and potentially any SignalMast logics generated
    } else if (getConnect1() == nullptr || getConnect2() == nullptr) {
        //could still be in the process of rebuilding the point details
    } else if (getConnect1()->getLayoutBlock() == getConnect2()->getLayoutBlock()) {
        //We are no longer a block bounardy
        if (westBoundSignalMastNamed != nullptr) {
            removeSML(getWestBoundSignalMast());
        }
        if (eastBoundSignalMastNamed != nullptr) {
            removeSML(getEastBoundSignalMast());
        }
        westBoundSignalMastNamed = nullptr;
        eastBoundSignalMastNamed = nullptr;
        setWestBoundSensor("");
        setEastBoundSensor("");
        //TODO: May want to look at a method to remove the assigned mast
        //from the panel and potentially any SignalMast logics generated
    }
}   // reCheckBlockBoundary

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity*> PositionablePointView::getLayoutConnectivity() {
    return positionablePoint->getLayoutConnectivity();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QList<HitPointType::TYPES> PositionablePointView::checkForFreeConnections() {
    QList<HitPointType::TYPES> result = QList<HitPointType::TYPES>();

    if ((getConnect1() == nullptr)
            || ((getType() == PositionablePoint::PointType::ANCHOR) && (getConnect2() == nullptr))) {
        result.append(HitPointType::POS_POINT);
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool PositionablePointView::checkForUnAssignedBlocks() {
    // Positionable Points don't have blocks so...
    // nothing to see here... move along...
    return true;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::checkForNonContiguousBlocks(
        /*@Nonnull*/  QMap<QString, QList<QSet<QString>*>*> blockNamesTotrackNameSetsMap) {
    /*
    * For each (non-nullptr) blocks of this track do:
    * #1) If it's got an entry in the blockNamesTotrackNameSetMap then
    * #2) If this track is not in one of the trackNameSets for this block
    * #3) add a new set (with this block/track) to
    *     blockNamesTotrackNameSetMap and
    * #4) check all the connections in this
    *     block (by calling the 2nd method below)
    * <p>
    *     Basically, we're maintaining contiguous track sets for each block found
    *     (in blockNamesTotrackNameSetMap)
     */
    //check the 1st connection points block
    TrackSegment* ts1 = getConnect1();
    QString blk1 = nullptr;
    QList<QSet<QString>*>* trackNameSets = nullptr;
    QSet<QString>* trackNameSet = nullptr;    // assume not found (pessimist!)

    // this should never be null... but just in case...
    if (ts1 != nullptr) {
        blk1 = ts1->getBlockName();
        if (!blk1.isEmpty()) {
            trackNameSets = blockNamesTotrackNameSetsMap.value(blk1);
            if (trackNameSets != nullptr) { // (#1)
                for (QSet<QString>* checktrackNameSet : *trackNameSets) {
                    if (checktrackNameSet->contains(getName())) { // (#2)
                        trackNameSet = checktrackNameSet;
                        break;
                    }
                }
            } else {    // (#3)
                log->debug(tr("*New block (''%1'') trackNameSets").arg(blk1));
                trackNameSets = new QList<QSet<QString>*>();
                blockNamesTotrackNameSetsMap.insert(blk1, trackNameSets);
            }
            if (trackNameSet == nullptr) {
                trackNameSet = new QSet<QString>();
                log->debug(tr("*    Add track ''%1'' to trackNameSet for block ''%2''").arg(getName(), blk1));
                trackNameSet->insert(getName());
                trackNameSets->append(trackNameSet);
            }
            if (getConnect1() != nullptr) { // (#4)
                getConnect1()->collectContiguousTracksNamesInBlockNamed(blk1, trackNameSet);
            }
        }
    }

    if (getType() == PositionablePoint::PointType::ANCHOR) {
        //check the 2nd connection points block
        TrackSegment* ts2 = getConnect2();
        // this should never be null... but just in case...
        if (ts2 != nullptr) {
            QString blk2 = ts2->getBlockName();
            if (!blk2.isEmpty()) {
                trackNameSet = nullptr;    // assume not found (pessimist!)
                trackNameSets = blockNamesTotrackNameSetsMap.value(blk2);
                if (trackNameSets != nullptr) { // (#1)
                    for (QSet<QString>* checktrackNameSet : *trackNameSets) {
                        if (checktrackNameSet->contains(getName())) { // (#2)
                            trackNameSet = checktrackNameSet;
                            break;
                        }
                    }
                } else {    // (#3)
                    log->debug(tr("*New block (''%1'') trackNameSets").arg(blk2));
                    trackNameSets = new QList<QSet<QString>*>();
                    blockNamesTotrackNameSetsMap.insert(blk2, trackNameSets);
                }
                if (trackNameSet == nullptr) {
                    trackNameSet = new QSet<QString>();
                    log->debug(tr("*    Add track ''%1'' to trackNameSet for block ''%2''").arg(getName(), blk2));
                    trackNameSets->append(trackNameSet);
                    trackNameSet->insert(getName());
                }
                if (getConnect2() != nullptr) { // (#4)
                    getConnect2()->collectContiguousTracksNamesInBlockNamed(blk2, trackNameSet);
                }
            }
        }
    }
} // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/  QString blockName,
        /*@Nonnull*/  QSet<QString>* trackNameSet) {
    if (!trackNameSet->contains(getName())) {
        TrackSegment* ts1 = getConnect1();
        // this should never be null... but just in case...
        if (ts1 != nullptr) {
            QString blk1 = ts1->getBlockName();
            // is this the blockName we're looking for?
            if (blk1 == (blockName)) {
                // if we are added to the trackNameSet
//                if (trackNameSet->insert(getName())) {
//                    log->debug("*    Add track ''{}''for block ''{}''", getName(), blockName);
//                }
             trackNameSet->insert(getName());
                // this should never be null... but just in case...
                if (getConnect1() != nullptr) {
                    getConnect1()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
                }
            }
        }
        if (getType() == PositionablePoint::PointType::ANCHOR) {
            TrackSegment* ts2 = getConnect2();
            // this should never be null... but just in case...
            if (ts2 != nullptr) {
                QString blk2 = ts2->getBlockName();
                // is this the blockName we're looking for?
                if (blk2 ==(blockName)) {
                    // if we are added to the trackNameSet
//                    if (trackNameSet->insert(getName())) {
//                        log->debug("*    Add track ''{}''for block ''{}''", getName(), blockName);
//                    }
                 trackNameSet->insert(getName());
                    // this should never be null... but just in case...
                    if (getConnect2() != nullptr) {
                        // it's time to play... flood your neighbour!
                        getConnect2()->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
                    }
                }
            }
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePointView::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    // positionable points don't have blocks...
    // nothing to see here, move along...
}

/*private*/ /*final*/ /*static*/ Logger* PositionablePointView::log = LoggerFactory::getLogger("PositionablePointView");
