#include "positionablepoint.h"
#include "tracksegment.h"
#include "instancemanager.h"
#include "panelmenu.h"
#include "signalheadmanager.h"
#include "blockbosslogic.h"
#include "signalhead.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "path.h"
#include "mathutil.h"
#include <limits>
#include "signalmastlogicmanager.h"
#include "signallingguitools.h"
#include "layouteditorfinditems.h"

//PositionablePoint::PositionablePoint(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * PositionablePoint is a Point defining a node in the Track that can be dragged around the
 * inside of the enclosing LayoutEditor panel using a right-drag (drag with meta key).
 * <P>
 * Two types of Positionable Point are supported:
 *		Anchor - point on track - two track connections
 *		End Bumper - end of track point - one track connection
 * <P>
 * Note that a PositionablePoint exists for specifying connectivity and drawing position
 * only.  The Track Segments connected to a PositionablePoint may belong to the same block
 * or to different blocks.  Since each Track Segment may only belong to one block, a
 * PositionablePoint may function as a Block Boundary.
 * <P>
 * Signal names are saved here at a Block Boundary anchor point by the tool Set Signals at
 * Block Boundary. PositionablePoint does nothing with these signal head names; it only
 * serves as a place to store them.
 *
 * @author Dave Duchamp Copyright (c) 2004-2007
 * @version $Revision: 20243 $
 */

///*public*/ class PositionablePoint
//{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.LayoutEditor::LayoutEditorBundle");

    // operational instance variables (not saved between sessions)

/*public*/ PositionablePoint::PositionablePoint(QString id, int t, QPointF c, LayoutEditor* layoutEditor,QObject *parent)
 : LayoutTrack(id, c, layoutEditor,parent)
{
 setObjectName(id);
 instance = nullptr;
 this->layoutEditor = layoutEditor;
 // initialization instance variables (used when loading a LayoutEditor)
 trackSegment1Name = "";
 trackSegment2Name = "";

 // persistent instances variables (saved between sessions)
 //ident = "";
 type = 0;
 connect1 = nullptr;
 connect2 = nullptr;
 //coords = QPointF(10.0,10.0);
 //eastBoundSignalName = ""; // signal head for east (south) bound trains
 //westBoundSignalName = ""; // signal head for west (north) bound trains
 /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
        this is so that we can keep up with moves and changes of userNames */
 eastBoundSensorNamed = nullptr;
 westBoundSensorNamed = nullptr;
 eastBoundSignalMastNamed = nullptr;
 westBoundSignalMastNamed = nullptr;

 //eastBoundSignalMastName = "";
 //westBoundSignalMastName = "";
 instance = this;
 //layoutEditor = myPanel;
 if ( (t==ANCHOR) || (t==END_BUMPER) || (t == EDGE_CONNECTOR))
 {
  type = t;
 }
 else
 {
  log->error("Illegal type of PositionablePoint - "+t);
  type = ANCHOR;
 }
 //ident = id;
 //coords = p;
 popup = nullptr;
 active = true;
 //tools = nullptr;
 // cursor location reference for this move (relative to object)
 xClick = 0;
 yClick = 0;
// item = nullptr;
 editLink = nullptr;

}

// this should only be used for debugging...
//@Override
/*public*/ QString PositionablePoint::toString() {
    QString result = "PositionalablePoint";
    switch (type) {
        case ANCHOR: {
            result = "Anchor";
            break;
        }
        case END_BUMPER: {
            result = "End Bumper";
            break;
        }
        case EDGE_CONNECTOR: {
            result = "Edge Connector";
            break;
        }
        default: {
            result = "Unknown type (" + QString::number(type) + ")";
            break;
        }
    }
    return result + " '" + getName() + "'";
}

/**
 * Accessor methods
*/
///*public*/ QString PositionablePoint::getID() {return ident;}
/*public*/ int PositionablePoint::getType() const {return type;}

/*public*/ TrackSegment* PositionablePoint::getConnect1() const
{
 return connect1;
}

/*public*/ TrackSegment* PositionablePoint::getConnect2() const
{
 if (type == EDGE_CONNECTOR && getLinkedPoint() != nullptr) {
     return getLinkedPoint()->getConnect1();
 }
 return connect2;
}
/*public*/ QPointF PositionablePoint::getCoords() {return coords;}
/*public*/ void PositionablePoint::setCoords(QPointF p) {coords = p;}

/*public*/ QString PositionablePoint::getLinkEditorName() {
    if (getLinkedEditor() != nullptr) {
        return getLinkedEditor()->getLayoutName();
    }
    return "";
}

/*public*/ PositionablePoint* PositionablePoint::getLinkedPoint() const {
    return linkedPoint;
}

/*public*/ QString PositionablePoint::getLinkedPointId() {
    if (linkedPoint != nullptr) {
        return linkedPoint->getId();
    }
    return "";
}

/*public*/ void PositionablePoint::setLinkedPoint(PositionablePoint* p) {
    if (p == linkedPoint) {
        return;
    }
    if (linkedPoint != nullptr && linkedPoint != p) {
        PositionablePoint* oldLinkedPoint = linkedPoint;
        linkedPoint = nullptr;
        if (oldLinkedPoint->getLinkedPoint() != nullptr) {
            oldLinkedPoint->setLinkedPoint(nullptr);
        }
        if (oldLinkedPoint->getConnect1() != nullptr) {
            TrackSegment* ts = oldLinkedPoint->getConnect1();
            oldLinkedPoint->getLayoutEditor()->auxTools->setBlockConnectivityChanged();
            ts->updateBlockInfo();
            oldLinkedPoint->getLayoutEditor()->repaint();
        }
        if (getConnect1() != nullptr) {
            layoutEditor->auxTools->setBlockConnectivityChanged();
            getConnect1()->updateBlockInfo();
            layoutEditor->repaint();
        }
    }
    linkedPoint = p;
    if (p != nullptr) {
        p->setLinkedPoint(this);
        if (getConnect1() != nullptr) {
            layoutEditor->auxTools->setBlockConnectivityChanged();
            getConnect1()->updateBlockInfo();
            layoutEditor->repaint();
        }
    }
}

/*public*/ LayoutEditor* PositionablePoint::getLinkedEditor() const{
    if (getLinkedPoint() != nullptr) {
        return getLinkedPoint()->getLayoutEditor();
    }
    return nullptr;
}

/*protected*/ LayoutEditor* PositionablePoint::getLayoutEditor() {
    return layoutEditor;
}
//@CheckReturnValue
//@Nonnullptr
/*public*/ QString PositionablePoint::getEastBoundSignal() {
    SignalHead* h = getEastBoundSignalHead();
    if (h != nullptr) {
        return h->getDisplayName();
    }
    return "";
}

/*public*/ SignalHead* PositionablePoint::getEastBoundSignalHead() {
    if (getType() == EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::EAST || dir == Path::SOUTH || dir == Path::SOUTH + Path::EAST) {
            if (signalEastHeadNamed != nullptr) {
                return signalEastHeadNamed->getBean();
            }
            return nullptr;
        } else if (getLinkedPoint() != nullptr) {
            // Do some checks to find where the connection is here.
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH + Path::EAST) {
                return getLinkedPoint()->getEastBoundSignalHead();
            }
        }
    }

    if (signalEastHeadNamed != nullptr) {
        return signalEastHeadNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePoint::setEastBoundSignal(QString signalName)
{
    if (getType() == EDGE_CONNECTOR) {
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

/*private*/ void PositionablePoint::setEastBoundSignalName(/*@CheckFornullptr*/ QString signalHead) {
    if (signalHead == "" || signalHead.isEmpty()) {
        signalEastHeadNamed = nullptr;
        return;
    }

    SignalHead* head = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalEastHeadNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalEastHeadNamed = nullptr;
    }
}

//@CheckReturnValue
//@Nonnullptr
/*public*/ QString PositionablePoint::getWestBoundSignal() {
    SignalHead* h = getWestBoundSignalHead();
    if (h != nullptr) {
        return h->getDisplayName();
    }
    return "";
}

/*public*/ SignalHead* PositionablePoint::getWestBoundSignalHead()
{
    if (getType() == EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH + Path::WEST) {
            if (signalWestHeadNamed != nullptr) {
                return signalWestHeadNamed->getBean();
            }
            return nullptr;
        } else if (getLinkedPoint() != nullptr) {
            // Do some checks to find where the connection is here.
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH + Path::WEST) {
                return getLinkedPoint()->getWestBoundSignalHead();
            }
        }
    }

    if (signalWestHeadNamed != nullptr) {
        return signalWestHeadNamed->getBean();
    }
    return nullptr;
}

/*public*/ void PositionablePoint::setWestBoundSignal(QString signalName) {
    if (getType() == EDGE_CONNECTOR) {
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

/*private*/ void PositionablePoint::setWestBoundSignalName(/*@CheckFornullptr*/ QString signalHead) {
    if (signalHead == "" || signalHead.isEmpty()) {
        signalWestHeadNamed = nullptr;
        return;
    }

    SignalHead* head = static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signalHead);
    if (head != nullptr) {
        signalWestHeadNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalHead, head);
    } else {
        signalWestHeadNamed = nullptr;
    }
}

/*public*/ QString PositionablePoint::getEastBoundSensorName() {
    if (eastBoundSensorNamed != nullptr) {
        return eastBoundSensorNamed->getName();
    }
    return "";
}
/*public*/ Sensor* PositionablePoint::getEastBoundSensor() {
    if(eastBoundSensorNamed!=nullptr)
        return eastBoundSensorNamed->getBean();
    return nullptr;
}
/*public*/ void PositionablePoint::setEastBoundSensor(QString sensorName) const {
    if(sensorName==nullptr || sensorName==("")){
        eastBoundSensorNamed=nullptr;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != nullptr) {
        eastBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        eastBoundSensorNamed=nullptr;
    }
}

/*public*/ QString PositionablePoint::getWestBoundSensorName() {
        if (westBoundSensorNamed != nullptr) {
            return westBoundSensorNamed->getName();
        }
        return "";
    }
/*public*/ Sensor* PositionablePoint::getWestBoundSensor() {
    if(westBoundSensorNamed!=nullptr)
        return westBoundSensorNamed->getBean();
    return nullptr;
}
/*public*/ void PositionablePoint::setWestBoundSensor(QString sensorName) const {
    if(sensorName==nullptr || sensorName==("")){
        westBoundSensorNamed=nullptr;
        return;
    }
    Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != nullptr) {
        westBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        westBoundSensorNamed=nullptr;
    }
}
/*public*/ QString PositionablePoint::getEastBoundSignalMastName() {
        if (getEastBoundSignalMastNamed() != nullptr) {
            return getEastBoundSignalMastNamed()->getName();
        }
        return "";
    }
/*public*/ SignalMast* PositionablePoint::getEastBoundSignalMast()
{
 if (getEastBoundSignalMastNamed() != nullptr) {
  return getEastBoundSignalMastNamed()->getBean();
 }
 return nullptr;
}

/*private*/ NamedBeanHandle<SignalMast*>* PositionablePoint::getEastBoundSignalMastNamed()
{
 if (getType() == EDGE_CONNECTOR)
 {
     int dir = getConnect1Dir();
     if (dir == Path::SOUTH || dir == Path::EAST || dir == Path::SOUTH + Path::EAST) {
         return eastBoundSignalMastNamed;
     } else if (getLinkedPoint() != nullptr) {
         int linkDir = getLinkedPoint()->getConnect1Dir();
         if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH + Path::EAST) {
             return getLinkedPoint()->getEastBoundSignalMastNamed();
         }
     }
 }
 return eastBoundSignalMastNamed;
}

/*private*/ NamedBeanHandle<SignalMast*>* PositionablePoint::getWestBoundSignalMastNamed()
{
 if (getType() == EDGE_CONNECTOR)
 {
  int dir = getConnect1Dir();
  if (dir == Path::SOUTH || dir == Path::EAST || dir == Path::SOUTH + Path::EAST)
  {
   return westBoundSignalMastNamed;
  }
  else if (getLinkedPoint() != nullptr)
  {
   int linkDir = getLinkedPoint()->getConnect1Dir();
   if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH + Path::EAST) {
       return getLinkedPoint()->getWestBoundSignalMastNamed();
   }
  }
 }
 return westBoundSignalMastNamed;
}

/*public*/ void PositionablePoint::setEastBoundSignalMast(QString signalMast) const {
    SignalMast* mast = nullptr;
    if (signalMast != "" && !signalMast.isEmpty()) {
        mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
        if (mast == nullptr) {
            log->error("Unable to find Signal Mast " + signalMast);
            return;
        }
    } else {
        eastBoundSignalMastNamed = nullptr;
        return;
    }
    if (getType() == EDGE_CONNECTOR) {
        int dir = getConnect1Dir();
        if (dir == Path::EAST || dir == Path::SOUTH || dir == Path::SOUTH_EAST) {
            eastBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        } else if (getLinkedPoint() != nullptr) {
            int linkDir = getLinkedPoint()->getConnect1Dir();
            if (linkDir == Path::SOUTH || linkDir == Path::EAST || linkDir == Path::SOUTH_EAST) {
                getLinkedPoint()->setEastBoundSignalMast(signalMast);
            } else {
                eastBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
            }
        } else {
            eastBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        }
    } else {
        eastBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
    }
}

/*public*/ QString PositionablePoint::getWestBoundSignalMastName() {
        if (getWestBoundSignalMastNamed() != nullptr) {
            return getWestBoundSignalMastNamed()->getName();
        }
        return "";
    }
/*public*/ SignalMast* PositionablePoint::getWestBoundSignalMast()
{
 if (getWestBoundSignalMastNamed() != nullptr) {
  return getWestBoundSignalMastNamed()->getBean();
}
return nullptr;

}
/*public*/ void PositionablePoint::setWestBoundSignalMast(QString signalMast) const{
        SignalMast* mast = nullptr;
        if (signalMast != "" && !signalMast.isEmpty()) {
            mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signalMast);
            if (mast == nullptr) {
                log->error("Unable to find Signal Mast " + signalMast);
                return;
            }
        } else {
            westBoundSignalMastNamed = nullptr;
            return;
        }
        if (getType() == EDGE_CONNECTOR) {
            int dir = getConnect1Dir();
            if (dir == Path::WEST || dir == Path::NORTH || dir == Path::NORTH_WEST) {
                westBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
            } else if (getLinkedPoint() != nullptr) {
                int linkDir = getLinkedPoint()->getConnect1Dir();
                if (linkDir == Path::WEST || linkDir == Path::NORTH || linkDir == Path::NORTH_WEST) {
                    getLinkedPoint()->setWestBoundSignalMast(signalMast);
                } else {
                    westBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
                }
            } else {
                westBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
            }
        } else {
            westBoundSignalMastNamed = static_cast<NamedBeanHandleManager*>(InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signalMast, mast);
        }
    }

// initialization instance variables (used when loading a LayoutEditor)
//	public String trackSegment1Name = "";
//	public String trackSegment2Name = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void PositionablePoint::setObjects(LayoutEditor* p) {
 if (type == EDGE_CONNECTOR)
 {
   connect1 = p->getFinder()->findTrackSegmentByName(trackSegment1Name);
   if (getConnect2() != nullptr && getLinkedEditor() != nullptr) {
       //now that we have a connection we can fire off a change
       TrackSegment* ts = getConnect2();
       getLinkedEditor()->getLEAuxTools()->setBlockConnectivityChanged();
       ts->updateBlockInfo();
   }
 } else {
     connect1 = p->getFinder()->findTrackSegmentByName(trackSegment1Name);
     connect2 = p->getFinder()->findTrackSegmentByName(trackSegment2Name);
 }
}
/**
 * setup a connection to a track
 *
 * @param track the track we want to connect to
 * @return true if successful
 */
/*public*/ bool PositionablePoint::setTrackConnection(/*@Nonnull*/ TrackSegment* track) {
    return replaceTrackConnection(nullptr, track);
}

/**
 * remove a connection to a track
 *
 * @param track the track we want to disconnect from
 * @return true if successful
 */
/*public*/ bool PositionablePoint::removeTrackConnection(/*@Nonnull*/ TrackSegment* track) const {
    return replaceTrackConnection(track, nullptr);
}

/**
 * replace old track connection with new track connection
 *
 * @param oldTrack the old track connection
 * @param newTrack the new track connection
 * @return true if successful
 */
/*public*/ bool PositionablePoint::replaceTrackConnection(/*@nullptrable*/ TrackSegment* oldTrack,
 /* @nullptrable */TrackSegment* newTrack) const {
    bool result = false; // assume failure (pessimist!)
    // trying to replace old track with nullptr?
    if (newTrack == nullptr) {
        // (yes) remove old connection
        if (oldTrack != nullptr) {
            result = true;  // assume success (optimist!)
            if (connect1 == oldTrack) {
                connect1 = nullptr;        // disconnect connect1
                reCheckBlockBoundary();
                removeLinkedPoint();
                connect1 = connect2;    // Move connect2 to connect1
                connect2 = nullptr;        // disconnect connect2
            } else if (connect2 == oldTrack) {
                connect2 = nullptr;
                reCheckBlockBoundary();
            } else {
                result = false; // didn't find old connection
            }
        } else {
            result = false; // can't replace nullptr with nullptr
        }
        if (!result) {
            log->error(tr("Attempt to remove non-existant track connection: %1").arg(oldTrack->getName()));
        }
    } else // already connected to newTrack?
    if ((connect1 != newTrack) && (connect2 != newTrack)) {
        // (no) find a connection we can connect to
        result = true;  // assume success (optimist!)
        if (connect1 == oldTrack) {
            connect1 = newTrack;
        } else if ((type == ANCHOR) && (connect2 == oldTrack)) {
            connect2 = newTrack;
            if (connect1->getLayoutBlock() == connect2->getLayoutBlock()) {
                westBoundSignalMastNamed = nullptr;
                eastBoundSignalMastNamed = nullptr;
                setWestBoundSensor("");
                setEastBoundSensor("");
            }
        } else {
            log->error("Attempt to assign more than allowed number of connections");
            result = false;
        }
    } else {
        log->error(tr("Already connected to %1").arg(newTrack->getName()));
        result = false;
    }
    return result;
}   // replaceTrackConnection

/*public*/ void PositionablePoint::removeBeanReference(NamedBean* nb) {
        if (nb == nullptr) {
            return;
        }
        if (qobject_cast<SignalMast*>(nb)) {
            if (nb->equals((QObject*)getWestBoundSignalMast())) {
                setWestBoundSignalMast(nullptr);
            } else if (nb->equals((QObject*)getEastBoundSignalMast())) {
                setEastBoundSignalMast(nullptr);
            }
        } else if (qobject_cast<Sensor*>(nb)) {
            if (nb->equals(getWestBoundSensor())) {
                setWestBoundSignalMast(nullptr);
            } else if (nb->equals(getEastBoundSensor())) {
                setEastBoundSignalMast(nullptr);
            }
        } else if (qobject_cast<SignalHead*>(nb)) {
            if (nb->equals(getWestBoundSignalHead())) {
                setWestBoundSignal(nullptr);
            }
            if (nb->equals(getEastBoundSignalHead())) {
                setEastBoundSignal(nullptr);
            }
        }
    }




void PositionablePoint::removeSML(SignalMast* signalMast) {
    if (signalMast == nullptr) {
        return;
    }
    if (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()
        && qobject_cast<SignalMastLogicManager*>(InstanceManager::getDefault("SignalMastLogicManager"))->isSignalMastUsed(signalMast)) {
        SignallingGuiTools::removeSignalMastLogic(nullptr, signalMast);
    }
}
/**
 * return true if this connection type is disconnected
 *
 * @param connectionType - the connection type to test
 * @return true if the connection for this connection type is free
 */
//@Override
/*public*/ bool PositionablePoint::isDisconnected(int connectionType) {
    bool result = false;
    if (connectionType == POS_POINT) {
        result = ((getConnect1() == nullptr) || (getConnect2() == nullptr));
    } else {
        log->error("Invalid connection type " + connectionType); //I18IN
    }
    return result;
}

//@Override
/*public*/ bool PositionablePoint::isMainline() {
    bool result = false; // assume failure (pessimist!)
    if (getConnect1() != nullptr) {
        result = getConnect1()->isMainline();
    }
    if (getType() == ANCHOR) {
        if (getConnect2() != nullptr) {
            result |= getConnect2()->isMainline();
        }
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePoint::draw1(EditScene* g2, bool /*isMain*/, bool /*isBlock*/, ITEMTYPE type) {
    //nothing to do here... move along...
}   // draw1

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePoint::draw2(EditScene* g2, bool /*isMain*/, float /*railDisplacement*/, ITEMTYPE type) {
    //nothing to do here... move along...
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePoint::highlightUnconnected(EditScene *g2, int specificType) {
    if ((specificType == NONE) || (specificType == POS_POINT)) {
        if ((getConnect1() == nullptr)
                || ((getType() == ANCHOR) && (getConnect2() == nullptr))) {
 // TODO:           g2.fill(layoutEditor->trackControlCircleAt(getCoordsCenter()));
         QGraphicsEllipseItem* circleItem = layoutEditor->trackControlCircleAt(getCoordsCenter());
         g2->addItem(circleItem);
        }
    }
}
/*
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PositionablePoint::drawEditControls(EditScene* g2)
{
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
     if (getType() == ANCHOR) {
         ts2 = getConnect2();
     } else if (getType() == EDGE_CONNECTOR) {
         if (getLinkedPoint() != nullptr) {
             ts2 = getLinkedPoint()->getConnect1();
         }
     }
     if ((getType() != END_BUMPER) && (ts2 == nullptr)) {
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
/*protected*/ void PositionablePoint::drawTurnoutControls(EditScene *g2) {
    // PositionablePoints don't have turnout controls...
    // nothing to see here... move along...
}

/*public*/ void PositionablePoint::reCheckBlockBoundary()const{
    if(type==END_BUMPER)
        return;
    if(connect1==nullptr && connect2==nullptr){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
//        if(!getWestBoundSignalMast().equals(""))
//            removeSML(getWestBoundSignalMast());
//        if(!getEastBoundSignalMast().equals(""))
//            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }  else if(connect1==nullptr || connect2==nullptr){
        //could still be in the process of rebuilding the point details
        return;
    } else if (connect1->getLayoutBlock()==connect2->getLayoutBlock()){
        //We are no longer a block bounardy
//        if(!getWestBoundSignalMast().equals(""))
//            removeSML(getWestBoundSignalMast());
//        if(!getEastBoundSignalMast().equals(""))
//            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }
}
#if 0 // TODO:

void removeSML(QString signalMast){
    if(signalMast==nullptr || signalMast.equals(""))
        return;
    jmri.SignalMast mast = jmri.InstanceManager.signalMastManagerInstance().getSignalMast(signalMast);
    if(jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager.signalMastLogicManagerInstance().isSignalMastUsed(mast)){
        if(SignallingGuiTools.removeSignalMastLogic(nullptr, mast)){
            if (tools == nullptr) {
                tools = new LayoutEditorTools(layoutEditor);
            }
            tools.removeSignalMastFromPanel(signalMast);
        }
    }
}
#endif
/*protected*/ int PositionablePoint::maxWidth(){
    return 5;
}
/*protected*/ int PositionablePoint::maxHeight(){
    return 5;
}

/*public*/ void PositionablePoint::mousePressed(QGraphicsSceneMouseEvent* e) {
    // remember where we are
    xClick = e->scenePos().x();
    yClick = e->scenePos().y();
    // if (debug) log->debug("Pressed: "+where(e));
//    if (e.isPopupTrigger()) {
//        showPopUp(e);
//    }
}

/*public*/ void PositionablePoint::mouseReleased(QGraphicsSceneMouseEvent* e)
{
 // if (debug) log->debug("Release: "+where(e));
 //if (e.isPopupTrigger())
 if((e->buttons()& Qt::RightButton) != 0)
 {
  showPopUp(e);
 }
}

/*public*/ void PositionablePoint::mouseClicked(QGraphicsSceneMouseEvent* e)
{
 if((e->buttons()& Qt::RightButton) != 0)
 {
  showPopUp(e);
 }
}


/**
 * For editing: only provides remove
 */
/*protected*/ void PositionablePoint::showPopUp(QGraphicsSceneMouseEvent* /*e*/)
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
 bool blockBoundary = false;
 bool endBumper = false;
 switch (getType())
 {
 case ANCHOR:
 {
  popup->addAction(new QAction(tr("Anchor ")+ getId(),this));
  LayoutBlock* block1 = nullptr;
  LayoutBlock* block2 = nullptr;
  if (connect1!=nullptr) block1 = connect1->getLayoutBlock();
  if (connect2!=nullptr) block2 = connect2->getLayoutBlock();
  if ( (block1!=nullptr) && (block1==block2) )
  {
   popup->addAction(new QAction(tr("Block")+": "+block1->getId(),this));
   //jmi = popup->addAction(tr("%1).arg(tr("Block")) + block1->getDisplayName());
  }
  else if ( (block1!=nullptr) && (block2!=nullptr) && (block1!=block2) )
  {
   popup->addAction(new QAction(tr("BlockDivider"),this));
   popup->addAction(new QAction(" "+tr("Block1ID")+": "+block1->getId(),this));
   popup->addAction(new QAction(" "+tr("Block2ID")+": "+block2->getId(),this));
   blockBoundary = true;
  }
  break;
 }
 case END_BUMPER:
 {
  popup->addAction(new QAction(tr("End Bumper ")+ getId() ,this));
  LayoutBlock* blockEnd = nullptr;
  if (connect1!=nullptr) blockEnd = connect1->getLayoutBlock();
  if (blockEnd!=nullptr)
  {
   popup->addAction(new QAction(tr("BlockID")+": "+blockEnd->getId(),this));
  }
  endBumper = true;
  break;
 }
 default : break;
 }
 popup->addSeparator();

 // popup.add(new AbstractAction(tr("Remove"))
// {
//  /*public*/ void actionPerformed(ActionEvent e)
//  {
//   if (LayoutEditor::removePositionablePoint(instance))
//   {
//    // user is serious about removing this point from the panel
//    remove();
//    dispose();
//   }
//  }
//  });
 QAction* actRemove = new QAction(tr("Remove"),this);
 popup->addAction(actRemove);
 connect(actRemove, SIGNAL(triggered()), this, SLOT(on_actRemove_triggered()));
#if 1 // TODO:
  if (blockBoundary)
  {
   QAction * act;
   if (getType() == EDGE_CONNECTOR)
   {
    popup->addAction(act = new AbstractAction(tr("Edit Link"),this));
//    {
//        @Override
//        public void actionPerformed(ActionEvent e) {
//            setLink();
//        }
//    });
    connect(act, SIGNAL(triggered()), this, SLOT(setLink()));
    }
    popup->addAction(act =new QAction(tr("Set Signals"), this));
//   {
//                /*public*/ void actionPerformed(ActionEvent e) {
//                if (tools == nullptr) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at level crossing tool dialog
//                tools.setSignalsAtBlockBoundaryFromMenu(instance,
//                    LayoutEditor::signalIconEditor,LayoutEditor::signalFrame);
//                }
//            });
   connect(act, SIGNAL(triggered()), this, SLOT(On_setSignals()));
   popup->addAction(act = new QAction(tr("Set Sensors"), this));
//   {
//       /*public*/ void actionPerformed(ActionEvent event) {
//           if (tools == nullptr) {
//               tools = new LayoutEditorTools(layoutEditor);
//           }
//           // bring up signals at block boundary tool dialog
//           tools.setSensorsAtBlockBoundaryFromMenu(instance,
//               LayoutEditor::sensorIconEditor,LayoutEditor::sensorFrame);
//       }
//   });
     connect(act, SIGNAL(triggered()), this, SLOT(On_setSensors()));
   popup->addAction(act = new QAction(tr("Set Signal Masts"), this));
//   {
//       /*public*/ void actionPerformed(ActionEvent event) {
//           if (tools == nullptr) {
//               tools = new LayoutEditorTools(layoutEditor);
//           }
//           // bring up signals at block boundary tool dialog
//           tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
//       }
//   });
  }
  if (endBumper)
  {
   QAction* act;
        popup->addAction(act = new QAction(tr("Set Sensors"), this));
//        {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (tools == nullptr) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at block boundary tool dialog
//                tools.setSensorsAtBlockBoundaryFromMenu(instance,
//                    LayoutEditor::sensorIconEditor,LayoutEditor::sensorFrame);
//            }
//        });
          connect(act, SIGNAL(triggered()), this, SLOT(On_setSensors()));
        popup->addAction(act = new QAction(tr("Set Signal Masts"),this));
//        {
//            /*public*/ void actionPerformed(ActionEvent event) {
//                if (tools == nullptr) {
//                    tools = new LayoutEditorTools(layoutEditor);
//                }
//                // bring up signals at block boundary tool dialog
//                tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
//            }
//        });
        connect(act, SIGNAL(triggered()), this, SLOT(On_setSignalMasts()));
  }
#endif
  layoutEditor->setShowAlignmentMenu(popup);
  //popup.show(e.getComponent(), e.getX(), e.getY());
  //popup->exec(layoutEditor->panel()->mapFromScene(QPoint(e->scenePos().x(), e->scenePos().y())));
  popup->exec(QCursor::pos());
}

QString PositionablePoint::where(QGraphicsSceneMouseEvent* e) {
    return QString("%1").arg(+e->scenePos().x())+","+QString("%1").arg(e->scenePos().y());
}
void PositionablePoint::On_setSignals()
{
 // bring up signals at level crossing tool dialog
 layoutEditor->getLETools()->setSignalsAtBlockBoundaryFromMenu(this,
                                 layoutEditor->signalIconEditor, layoutEditor->signalFrame);}

void PositionablePoint::On_setSensors()
{
 // bring up signals at block boundary tool dialog
 layoutEditor->getLETools()->setSensorsAtBlockBoundaryFromMenu(instance,
     layoutEditor->sensorIconEditor,layoutEditor->sensorFrame);

}
void PositionablePoint::On_setSignalMasts()
{
 // bring up signals at block boundary tool dialog
 layoutEditor->getLETools()->setSignalMastsAtBlockBoundaryFromMenu(instance);

}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void PositionablePoint::dispose()
{
 if (popup != nullptr) popup->clear();
 popup = nullptr;
}

void PositionablePoint::removeLinkedPoint() const{
 if (type == EDGE_CONNECTOR && getLinkedPoint() != nullptr) {

     if (getConnect2() != nullptr && getLinkedEditor() != nullptr) {
         //as we have removed the point, need to force the update on the remote end.
         LayoutEditor* oldLinkedEditor = getLinkedEditor();
         TrackSegment* ts = getConnect2();
         getLinkedPoint()->setLinkedPoint(nullptr);
         oldLinkedEditor->repaint();
         oldLinkedEditor->getLEAuxTools()->setBlockConnectivityChanged();
         ts->updateBlockInfo();
     }
     linkedPoint = nullptr;
     //linkedEditor=nullptr;
 }
}
/**
 * Removes this object from display and persistance
 */
void PositionablePoint::remove()
{
 // remove from persistance by flagging inactive
 active = false;
}

/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ bool PositionablePoint::isActive()
{
 return active;
}

void PositionablePoint::setLink()
{
 if (getConnect1() == nullptr || getConnect1()->getLayoutBlock() == nullptr) {
     log->error("Can not set link until we have a connecting track with a block assigned");
     return;
 }
 editLink = new JDialog();
 editLink->setTitle("EDIT LINK from " + getConnect1()->getLayoutBlock()->getDisplayName());
 QVBoxLayout* editLinkLayout = new QVBoxLayout(editLink);

 QWidget* container = new QWidget();
 //container.setLayout(new BorderLayout());
 QVBoxLayout* containerLayout = new QVBoxLayout(container);

 QPushButton* done = new QPushButton(tr("Done"));
// done.addActionListener(
//         (ActionEvent a) -> {
//     updateLink();
// });
 connect(done, SIGNAL(clicked(bool)), this, SLOT(updateLink()));
#if 0
 // make this button the default button (return or enter activates)
 // Note: We have to invoke this later because we don't currently have a root pane
 SwingUtilities.invokeLater(() -> {
     JRootPane rootPane = SwingUtilities.getRootPane(done);
     rootPane.setDefaultButton(done);
 });
#endif
 containerLayout->addWidget(getLinkPanel(),0, Qt::AlignTop);//, BorderLayout.NORTH);
 containerLayout->addWidget(done, 0, Qt::AlignBottom); //BorderLayout.SOUTH);
 //container.revalidate();
 container->update();

 editLinkLayout->addWidget(container);

 editLink->adjustSize();
 //editLink.setModal(false);
 editLink->setVisible(true);
}

/*public*/ QWidget* PositionablePoint::getLinkPanel() {
    editorCombo = new QComboBox/*<JCBHandle<LayoutEditor>>*/();
    QList<LayoutEditor*>* panels = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getLayoutEditorPanelList();
    editorCombo->addItem("None", QVariant());
    if (panels->contains(layoutEditor)) {
        panels->removeOne(layoutEditor);
    }
    for (LayoutEditor* p : *panels) {
        //JCBHandle<LayoutEditor> h = new JCBHandle<LayoutEditor>(p);
        //editorCombo.addItem(h);
     editorCombo->addItem(p->getName(), VPtr<LayoutEditor>::asQVariant(p));
        if (p == getLinkedEditor()) {
            editorCombo->setCurrentText(p->getName());
        }
    }

//    ActionListener selectPanelListener = (ActionEvent a) -> {
//        updatePointBox();
//    };

//    editorCombo.addActionListener(selectPanelListener);
    connect(editorCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePointBox()));
    QWidget* selectorPanel = new QWidget();
    QHBoxLayout* selectorPanelLayout = new QHBoxLayout(selectorPanel);
    selectorPanelLayout->addWidget(new QLabel("Select Panel"));
    selectorPanelLayout->addWidget(editorCombo);
    linkPointsBox = new QComboBox();
    updatePointBox();
    selectorPanelLayout->addWidget(new QLabel("Connecting Block"));
    selectorPanelLayout->addWidget(linkPointsBox);
    return selectorPanel;
}

void PositionablePoint::updatePointBox() {
    linkPointsBox->clear();
    pointList = new QList<PositionablePoint*>();
    if (editorCombo->currentIndex() == 0) {
        linkPointsBox->setEnabled(false);
        return;
    }
    int ourDir = getConnect1Dir();
    linkPointsBox->setEnabled(true);
//    //for (PositionablePoint* p : VPtr<LayoutEditor*>::asPtr(editorCombo->currentData().item().pointList)
//    for(int i = 1; i< editorCombo->count(); i++)
//    {
//     QVector<PositionablePoint*>* pointList = VPtr<LayoutEditor>::asPtr(editorCombo->itemData(i))->pointList;

//     for(int j=0;  j< pointList->count(); j++)
    LayoutEditor* le = VPtr<LayoutEditor>::asPtr(editorCombo->itemData(editorCombo->currentIndex()));
     for (PositionablePoint* p : le->getPositionablePoints()) {
     {
      //PositionablePoint* p = pointList->at(j);
        if (p->getType() == EDGE_CONNECTOR) {
            if (p->getLinkedPoint() == this) {
                pointList->append(p);
                linkPointsBox->addItem(p->getConnect2()->getLayoutBlock()->getDisplayName());
                linkPointsBox->setCurrentText(p->getConnect2()->getLayoutBlock()->getDisplayName());
            } else if (p->getLinkedPoint() == nullptr) {
                if (p->getConnect1() != nullptr && p->getConnect1()->getLayoutBlock() != nullptr) {
                    if (p->getConnect1()->getLayoutBlock() != getConnect1()->getLayoutBlock() && ourDir != p->getConnect1Dir()) {
                        pointList->append(p);
                        linkPointsBox->addItem(p->getConnect1()->getLayoutBlock()->getDisplayName());
                    }
                }
            }
        }
     }
    }
    editLink->adjustSize();
}

/*public*/ void PositionablePoint::updateLink() {
    if (editorCombo->currentIndex() == 0 || linkPointsBox->currentIndex() == -1) {
        if (getLinkedPoint() != nullptr && getConnect2() != nullptr) {
            QString removeremote = nullptr;
            QString removelocal = nullptr;
            if (getConnect1Dir() == Path::EAST || getConnect1Dir() == Path::SOUTH) {
                removeremote = getLinkedPoint()->getEastBoundSignal();
                removelocal = getWestBoundSignal();
                getLinkedPoint()->setEastBoundSignal("");
            } else {
                removeremote = getLinkedPoint()->getWestBoundSignal();
                removelocal = getEastBoundSignal();
                getLinkedPoint()->setWestBoundSignal("");
            }
            // removelocal and removeremote have been set here.
            if (removeremote != ("")) {
                SignalHead* sh = ((SignalHeadManager*) InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(removeremote);
                getLinkedEditor()->removeSignalHead(sh);
                BlockBossLogic::getStoppedObject(removeremote);
            }
            if (removelocal != ("")) {
                SignalHead* sh = ((SignalHeadManager*)  InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(removelocal);
                layoutEditor->removeSignalHead(sh);
                BlockBossLogic::getStoppedObject(removelocal);
            }
        }
        setLinkedPoint(nullptr);
    } else {
        setLinkedPoint(pointList->at(linkPointsBox->currentIndex()));
    }
    editLink->setVisible(false);
}
/**
 * {@inheritDoc}
 */
///@Override
/*protected*/ int PositionablePoint::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    int result = NONE;  // assume point not on connection
    //note: optimization here: instead of creating rectangles for all the
    // points to check below, we create a rectangle for the test point
    // and test if the points below are in that rectangle instead.
    QRectF r = layoutEditor->trackControlCircleRectAt(hitPoint);
    QPointF p, minPoint = MathUtil::zeroPoint2D;

    double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
    double distance, minDistance = std::numeric_limits<double>::infinity();//POSITIVE_INFINITY;

    if (!requireUnconnected || (getConnect1() == nullptr)
            || ((getType() == ANCHOR) && (getConnect2() == nullptr))) {
        // test point control rectangle
        p = getCoordsCenter();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = POS_POINT;
        }
    }
    if ((useRectangles && !r.contains(minPoint))
            || (!useRectangles && (minDistance > circleRadius))) {
        result = NONE;
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
/*public*/ QPointF PositionablePoint::getCoordsForConnectionType(int connectionType) {
    QPointF result = getCoordsCenter();
    if (connectionType != POS_POINT) {
        log->error("Invalid connection type " + QString::number(connectionType)); //I18IN
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ LayoutTrack* PositionablePoint::getConnection(int connectionType) throw (JmriException) {
    LayoutTrack* result = nullptr;
    if (connectionType == POS_POINT) {
        result = getConnect1();
        if (nullptr == result) {
            result = getConnect2();
        }
    } else {
        log->error("Invalid connection type " + QString::number(connectionType)); //I18IN
        throw JmriException("Invalid Point");
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePoint::setConnection(int connectionType, LayoutTrack *o, int type) throw (JmriException) {
    if ((type != TRACK) && (type != NONE)) {
        log->error("unexpected type of connection to positionable point - " + QString::number(type));
        throw JmriException("unexpected type of connection to positionable point - " + QString::number(type));
    }
    if (connectionType != POS_POINT) {
        log->error("Invalid Connection Type " + QString::number(connectionType)); //I18IN
        throw JmriException("Invalid Connection Type " + QString::number(connectionType));
    }
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionablePoint.class.getName());

//}
void PositionablePoint::on_actRemove_triggered()
{
 if(layoutEditor->removePositionablePoint(this))
 {
  remove();
  dispose();
 }
}
void PositionablePoint::invalidateItemType(EditScene* g2)
{
 if(item != nullptr)
 {
  //Q_ASSERT(item->scene()!=0);
  if(item->scene()!= nullptr)
   g2->removeItem(item);
  item = nullptr;
 }
 if(rects != nullptr)
 {
  //Q_ASSERT(item->scene()!=0);
  if(rects->scene()!= nullptr)
   g2->removeItem(rects);
  rects = nullptr;
 }
}
#if 0
void PositionablePoint::draw(EditScene* g2)
{
    QColor color;
    QGraphicsRectItem* rectItem;
    QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
    switch (getType())
    {
     case PositionablePoint::ANCHOR:
      // nothing to draw unless in edit mode
      //if (isEditable())
      {
       // in edit mode, draw locater rectangle
       QPointF pt = getCoordsCenter(); // getCoords()
       if ((getConnect1()==nullptr) || (getConnect2()==nullptr))
       {
        //g2.setColor(Color.red);
        color = QColor(Qt::red);
       }
       else
       {
        //g2.setColor(Color.green);
        color = QColor(Qt::green);
       }
 //      rectItem =  new QGraphicsRectItem(QRect(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2),0,g2);
 //      rectItem->setPen( QPen( color, 1, Qt::SolidLine ) );
       //QGraphicsRectItem* item = g2->addRect(pt.x()-SIZE, pt.y()-SIZE, SIZE2, SIZE2,QPen( color, 1, Qt::SolidLine ));
       rectItem = new QGraphicsRectItem(QRectF(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2));
       rectItem->setPen(QPen( color, 1, Qt::SolidLine ));
       itemGroup->addToGroup(rectItem);
       item = itemGroup;
       item->setFlags(QGraphicsItem::ItemIsMovable);
      }
      break;
     case PositionablePoint::END_BUMPER:
      // nothing to draw unless in edit mode
     //if (isEditable())
     {
      // in edit mode, draw locater rectangle
      QPointF pt = getCoordsCenter();
      if (getConnect1()==nullptr)
       {
        //g2.setColor(Color.red);
        color = QColor(Qt::red);
       }
       else
       {
        //g2.setColor(Color.green);
        color = QColor(Qt::green);
       }
       rectItem = new QGraphicsRectItem(QRect(pt.x()-LayoutEditor::SIZE, pt.y()-LayoutEditor::SIZE, LayoutEditor::SIZE2, LayoutEditor::SIZE2),0);
       rectItem->setPen( QPen( color, 1, Qt::SolidLine ) );
       itemGroup->addToGroup(rectItem);
       item = itemGroup;
       item->setFlags(QGraphicsItem::ItemIsMovable);
      }
      break;
     default:
     log->error("Illegal type of Positionable Point");
    }
    g2->addItem(item);
}
#endif
/*protected*/ int PositionablePoint::getConnect1Dir() const{
 int result = Path::NONE;

 TrackSegment* ts1 = getConnect1();
 if (ts1 != nullptr) {
     QPointF p1;
     if (ts1->getConnect1() == this) {
         p1 = LayoutEditor::getCoords(ts1->getConnect2(), ts1->getType2());
     } else {
         p1 = LayoutEditor::getCoords(ts1->getConnect1(), ts1->getType1());
     }
     result = Path::computeDirection(getCoordsCenter(), p1);
 }
 return result;
}
/*
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity*> PositionablePoint::getLayoutConnectivity() {
    QList<LayoutConnectivity*> results = QList<LayoutConnectivity*>();
    LayoutConnectivity* lc = nullptr;
    LayoutBlock* blk1 = nullptr, *blk2 = nullptr;
    TrackSegment* ts1 = getConnect1();
    QPointF p1, p2;

    if (getType() == ANCHOR) {
        TrackSegment* ts2 = getConnect2();
        if ((ts1 != nullptr) && (ts2 != nullptr)) {
            blk1 = ts1->getLayoutBlock();
            blk2 = ts2->getLayoutBlock();
            if ((blk1 != nullptr) && (blk2 != nullptr) && (blk1 != blk2)) {
                // this is a block boundary, create a LayoutConnectivity
                log->debug(tr("Block boundary ('%1'<->'%2') found at %3").arg(blk1->getDisplayName()).arg(blk2->getDisplayName()).arg(this->getId()));
                lc = new LayoutConnectivity(blk1, blk2);
                // determine direction from block 1 to block 2
                if (ts1->getConnect1() == this) {
                    p1 = LayoutEditor::getCoords(ts1->getConnect2(), ts1->getType2());
                } else {
                    p1 = LayoutEditor::getCoords(ts1->getConnect1(), ts1->getType1());
                }
                if (ts2->getConnect1() == this) {
                    p2 = LayoutEditor::getCoords(ts2->getConnect2(), ts2->getType2());
                } else {
                    p2 = LayoutEditor::getCoords(ts2->getConnect1(), ts2->getType1());
                }
                lc->setDirection(Path::computeDirection(p1, p2));
                // save Connections
                lc->setConnections(ts1, ts2, TRACK, this);
                results.append(lc);
            }
        }
    } else if (getType() == EDGE_CONNECTOR) {
        TrackSegment* ts2 = nullptr;
        if (getLinkedPoint() != nullptr) {
            ts2 = getLinkedPoint()->getConnect1();
        }
        if ((ts1 != nullptr) && (ts2 != nullptr)) {
            blk1 = ts1->getLayoutBlock();
            blk2 = ts2->getLayoutBlock();
            if ((blk1 != nullptr) && (blk2 != nullptr) && (blk1 != blk2)) {
                // this is a block boundary, create a LayoutConnectivity
                log->debug(tr("Block boundary ('%1'<->'%2') found at %3").arg(blk1->getDisplayName()).arg(blk2->getDisplayName()).arg(this->getId()));
                lc = new LayoutConnectivity(blk1, blk2);

                // determine direction from block 1 to block 2
                if (ts1->getConnect1() == this) {
                    p1 = LayoutEditor::getCoords(ts1->getConnect2(), ts1->getType2());
                } else {
                    p1 = LayoutEditor::getCoords(ts1->getConnect1(), ts1->getType1());
                }

                //Need to find a way to compute the direction for this for a split over the panel
                //In this instance work out the direction of the first track relative to the positionable poin.
                lc->setDirection(Path::computeDirection(p1, getCoordsCenter()));
                // save Connections
                lc->setConnections(ts1, ts2, TRACK, this);
                results.append(lc);
            }
        }
    }
    return results;
}   // getLayoutConnectivity()

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QList<int> PositionablePoint::checkForFreeConnections() {
    QList<int> result = QList<int>();

    if ((getConnect1() == nullptr)
            || ((getType() == ANCHOR) && (getConnect2() == nullptr))) {
        result.append((POS_POINT));
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool PositionablePoint::checkForUnAssignedBlocks() {
    // Positionable Points don't have blocks so...
    // nothing to see here... move along...
    return true;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePoint::checkForNonContiguousBlocks(
        /*@Nonnullptr*/ QMap<QString, QList<QSet<QString> > > blockNamesToTrackNameSetsMap) {
    /*
     * For each (non-nullptr) blocks of this track do:
     * #1) If it's got an entry in the blockNamesToTrackNameSetMap then
     * #2) If this track is not in one of the TrackNameSets for this block
     * #3) add a new set (with this block/track) to
     *     blockNamesToTrackNameSetMap and
     * #4) check all the connections in this
     *     block (by calling the 2nd method below)
     * <p>
     *     Basically, we're maintaining contiguous track sets for each block found
     *     (in blockNamesToTrackNameSetMap)
     */
    //check the 1st connection points block
    TrackSegment* ts1 = getConnect1();
    QString blk1 = nullptr;
    QList<QSet<QString> > TrackNameSets;// = nullptr;
    QSet<QString> TrackNameSet;// = nullptr;    // assume not found (pessimist!)

    // this should never be nullptr... but just in case...
    if (ts1 != nullptr) {
        blk1 = ts1->getBlockName();
        if (blk1 != nullptr) {
            TrackNameSets = blockNamesToTrackNameSetsMap.value(blk1);
            if (!TrackNameSets.isEmpty()) { // (#1)
                for (QSet<QString> checkTrackNameSet : TrackNameSets) {
                    if (checkTrackNameSet.contains(getName())) { // (#2)
                        TrackNameSet = checkTrackNameSet;
                        break;
                    }
                }
            } else {    // (#3)
                log->debug(tr("*New block ('%1') trackNameSets").arg(blk1));
                TrackNameSets = QList<QSet<QString> >();
                blockNamesToTrackNameSetsMap.insert(blk1, TrackNameSets);
            }
            if (TrackNameSet.isEmpty()) {
                TrackNameSet = QSet<QString>();
                log->debug(tr("*    Add track '%1' to trackNameSet for block '%2'").arg(getName()).arg(blk1));
                TrackNameSet.insert(getName());
                TrackNameSets.append(TrackNameSet);
            }
            if (connect1 != nullptr) { // (#4)
                connect1->collectContiguousTracksNamesInBlockNamed(blk1, TrackNameSet);
            }
        }
    }

    if (getType() == ANCHOR) {
        //check the 2nd connection points block
        TrackSegment* ts2 = getConnect2();
        // this should never be nullptr... but just in case...
        if (ts2 != nullptr) {
            QString blk2 = ts2->getBlockName();
            if (blk2 != nullptr) {
                TrackNameSet =QSet<QString>();    // assume not found (pessimist!)
                TrackNameSets = blockNamesToTrackNameSetsMap.value(blk2);
                if (!TrackNameSets.isEmpty()) { // (#1)
                    for (QSet<QString> checkTrackNameSet : TrackNameSets) {
                        if (checkTrackNameSet.contains(getName())) { // (#2)
                            TrackNameSet = checkTrackNameSet;
                            break;
                        }
                    }
                } else {    // (#3)
                    log->debug(tr("*New block ('%1') trackNameSets").arg(blk2));
                    TrackNameSets = QList<QSet<QString> >();
                    blockNamesToTrackNameSetsMap.insert(blk2, TrackNameSets);
                }
                if (TrackNameSet.isEmpty()) {
                    TrackNameSet = QSet<QString>();
                    log->debug(tr("*    Add track '%1' to TrackNameSet for block '%2'").arg(getName()).arg(blk2));
                    TrackNameSets.append(TrackNameSet);
                    TrackNameSet.insert(getName());
                }
                if (connect2 != nullptr) { // (#4)
                    connect2->collectContiguousTracksNamesInBlockNamed(blk2, TrackNameSet);
                }
            }
        }
    }
} // collectContiguousTracksNamesInBlockNamed

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void PositionablePoint::collectContiguousTracksNamesInBlockNamed(/*@Nonnullptr*/ QString blockName,
        /*@Nonnullptr*/ QSet<QString> TrackNameSet) {
    if (!TrackNameSet.contains(getName())) {
        TrackSegment* ts1 = getConnect1();
        // this should never be nullptr... but just in case...
        if (ts1 != nullptr) {
            QString blk1 = ts1->getBlockName();
            // is this the blockName we're looking for?
            if (blk1 == (blockName)) {
                // if we are added to the TrackNameSet
             TrackNameSet.insert(getName());
                if (TrackNameSet.contains(getName())) {
                    log->debug(tr("*    Add track '%1'for block '%2'").arg(getName()).arg(blockName));
                }
                // this should never be nullptr... but just in case...
                if (connect1 != nullptr) {
                    connect1->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
                }
            }
        }
        if (getType() == ANCHOR) {
            TrackSegment* ts2 = getConnect2();
            // this should never be nullptr... but just in case...
            if (ts2 != nullptr) {
                QString blk2 = ts2->getBlockName();
                // is this the blockName we're looking for?
                if (blk2 == (blockName)) {
                    // if we are added to the TrackNameSet
                 TrackNameSet.insert(getName());
                    if (TrackNameSet.contains(getName())) {
                        log->debug(tr("*    Add track '%1'for block '%2'").arg(getName()).arg(blockName));
                    }
                    // this should never be nullptr... but just in case...
                    if (connect2 != nullptr) {
                        // it's time to play... flood your neighbour!
                        connect2->collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
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
/*public*/ void PositionablePoint::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    // positionable points don't have blocks...
    // nothing to see here, move along...
}

void /*private*/ PositionablePoint::invalidate(EditScene * g2)
{
 if(rects != nullptr && rects->scene() == g2)
 {
  g2->removeItem(rects);
  delete rects;
 }
 rects = nullptr;
}

/*private*/ /*final*/ /*static*/ Logger* PositionablePoint::log
            = LoggerFactory::getLogger("PositionablePoint");
