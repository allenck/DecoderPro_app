#include "positionablepoint.h"
#include "tracksegment.h"
#include "instancemanager.h"

PositionablePoint::PositionablePoint(QObject *parent) :
    QObject(parent)
{
}
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

/*public*/ class PositionablePoint
{

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

    // operational instance variables (not saved between sessions)

/*public*/ PositionablePoint::PositionablePoint(QString id, int t, QPointF* p, LayoutEditor* myPanel,QObject *parent) : QObject(parent)
{
 instance = NULL;
 layoutEditor = NULL;

 // persistent instances variables (saved between sessions)
 ident = "";
 type = 0;
 connect1 = NULL;
 connect2 = NULL;
 coords = new QPointF(10.0,10.0);
 eastBoundSignalName = ""; // signal head for east (south) bound trains
 westBoundSignalName = ""; // signal head for west (north) bound trains
 /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
        this is so that we can keep up with moves and changes of userNames */
 eastBoundSensorNamed = NULL;
  westBoundSensorNamed = NULL;
 eastBoundSignalMastName = "";
 westBoundSignalMastName = "";
    instance = this;
    layoutEditor = myPanel;
    if ( (t==ANCHOR) || (t==END_BUMPER) ) {
        type = t;
    }
    else {
        log.error("Illegal type of PositionablePoint - "+t);
        type = ANCHOR;
    }
    ident = id;
    coords = p;
}

/**
 * Accessor methods
*/
/*public*/ QString PositionablePoint::getID() {return ident;}
/*public*/ int PositionablePoint::getType() {return type;}
/*public*/ TrackSegment* PositionablePoint::getConnect1() {return connect1;}
/*public*/ TrackSegment* PositionablePoint::getConnect2() {return connect2;}
/*public*/ QPointF* PositionablePoint::getCoords() {return coords;}
/*public*/ void PositionablePoint::setCoords(QPointF* p) {coords = p;}
/*public*/ QString PositionablePoint::getEastBoundSignal() {return eastBoundSignalName;}
/*public*/ void PositionablePoint::setEastBoundSignal(QString signalName) {eastBoundSignalName = signalName;}
/*public*/ QString PositionablePoint::getWestBoundSignal() {return westBoundSignalName;}
/*public*/ void PositionablePoint::setWestBoundSignal(QString signalName) {westBoundSignalName = signalName;}

/*public*/ QString PositionablePoint::getEastBoundSensor() {
    if(eastBoundSensorNamed!=NULL)
        return eastBoundSensorNamed->getName();
    return "";
}
/*public*/ void PositionablePoint::setEastBoundSensor(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        eastBoundSensorNamed=NULL;
        return;
    }

    Sensor* sensor = InstanceManager::sensorManagerInstance().provideSensor(sensorName);
    if (sensor != NULL) {
        eastBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        eastBoundSensorNamed=NULL;
    }
}

/*public*/ QString PositionablePoint::getWestBoundSensor() {
    if(westBoundSensorNamed!=NULL)
        return westBoundSensorNamed.getName();
    return "";
}
/*public*/ void PositionablePoint::setWestBoundSensor(QString sensorName) {
    if(sensorName==NULL || sensorName==("")){
        westBoundSensorNamed=NULL;
        return;
    }
    Sensor sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
    if (sensor != NULL) {
        westBoundSensorNamed =((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(sensorName, sensor);
    } else {
        westBoundSensorNamed=NULL;
    }
}

/*public*/ QString PositionablePoint::getEastBoundSignalMast() {return eastBoundSignalMastName;}
/*public*/ void PositionablePoint::setEastBoundSignalMast(QString signalMastName) {eastBoundSignalMastName = signalMastName;}
/*public*/ QString PositionablePoint::getWestBoundSignalMast() {return westBoundSignalMastName;}
/*public*/ void PositionablePoint::setWestBoundSignalMast(QString signalMastName) {westBoundSignalMastName = signalMastName;}

// initialization instance variables (used when loading a LayoutEditor)
/*public*/ QString trackSegment1Name = "";
/*public*/ QString trackSegment2Name = "";
/**
 * Initialization method
 *   The above variables are initialized by PositionablePointXml, then the following
 *        method is called after the entire LayoutEditor is loaded to set the specific
 *        TrackSegment objects.
 */
/*public*/ void setObjects(LayoutEditor p) {
    connect1 = p.findTrackSegmentByName(trackSegment1Name);
    connect2 = p.findTrackSegmentByName(trackSegment2Name);
}

/**
 * Setup and remove connections to track
 */
/*public*/ void setTrackConnection (TrackSegment track) {
    if (track==NULL) {
        return;
    }
    if ( (connect1!=track) && (connect2!=track) ) {
        // not connected to this track
        if (connect1==NULL) {
            connect1 = track;
        }
        else if ( (type!=END_BUMPER) && (connect2==NULL) ) {
            connect2 = track;
            if(connect1.getLayoutBlock()==connect2.getLayoutBlock()){
                setWestBoundSignalMast("");
                setEastBoundSignalMast("");
                setWestBoundSensor("");
                setEastBoundSensor("");
            }
        }
        else {
            log.error ("Attempt to assign more than allowed number of connections");
        }
    }
}

/*public*/ void removeTrackConnection (TrackSegment track) {
    if (track==connect1) {
        connect1 = NULL;
        reCheckBlockBoundary();
    }
    else if (track==connect2) {
        connect2 = NULL;
        reCheckBlockBoundary();
    }
    else {
        log.error ("Attempt to remove non-existant track connection");
    }
}

/*public*/ void reCheckBlockBoundary(){
    if(type==END_BUMPER)
        return;
    if(connect1==NULL && connect2==NULL){
        //This is no longer a block boundary, therefore will remove signal masts and sensors if present
        if(!getWestBoundSignalMast().equals(""))
            removeSML(getWestBoundSignalMast());
        if(!getEastBoundSignalMast().equals(""))
            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }  else if(connect1==NULL || connect2==NULL){
        //could still be in the process of rebuilding the point details
        return;
    } else if (connect1.getLayoutBlock()==connect2.getLayoutBlock()){
        //We are no longer a block bounardy
        if(!getWestBoundSignalMast().equals(""))
            removeSML(getWestBoundSignalMast());
        if(!getEastBoundSignalMast().equals(""))
            removeSML(getEastBoundSignalMast());
        setWestBoundSignalMast("");
        setEastBoundSignalMast("");
        setWestBoundSensor("");
        setEastBoundSensor("");
        //May want to look at a method to remove the assigned mast from the panel and potentially any SignalMast logics generated
    }
}

void removeSML(QString signalMast){
    if(signalMast==NULL || signalMast.equals(""))
        return;
    jmri.SignalMast mast = jmri.InstanceManager.signalMastManagerInstance().getSignalMast(signalMast);
    if(jmri.InstanceManager.layoutBlockManagerInstance().isAdvancedRoutingEnabled() && InstanceManager.signalMastLogicManagerInstance().isSignalMastUsed(mast)){
        if(SignallingGuiTools.removeSignalMastLogic(NULL, mast)){
            if (tools == NULL) {
                tools = new LayoutEditorTools(layoutEditor);
            }
            tools.removeSignalMastFromPanel(signalMast);
        }
    }
}

protected int maxWidth(){
    return 5;
}
protected int maxHeight(){
    return 5;
}
// cursor location reference for this move (relative to object)
int xClick = 0;
int yClick = 0;

/*public*/ void mousePressed(MouseEvent e) {
    // remember where we are
    xClick = e.getX();
    yClick = e.getY();
    // if (debug) log.debug("Pressed: "+where(e));
    if (e.isPopupTrigger()) {
        showPopUp(e);
    }
}

/*public*/ void mouseReleased(MouseEvent e) {
    // if (debug) log.debug("Release: "+where(e));
    if (e.isPopupTrigger()) {
        showPopUp(e);
    }
}

/*public*/ void mouseClicked(MouseEvent e) {
    if (e.isPopupTrigger()) {
        showPopUp(e);
    }
}

JPopupMenu popup = NULL;
LayoutEditorTools tools = NULL;
/**
 * For editing: only provides remove
 */
protected void showPopUp(MouseEvent e) {
    if (popup != NULL ) {
        popup.removeAll();
    }
    else {
        popup = new JPopupMenu();
    }
    boolean blockBoundary = false;
    boolean endBumper = false;
    switch (getType()) {
        case ANCHOR:
            popup.add(rb.getQString("Anchor"));
            LayoutBlock block1 = NULL;
            LayoutBlock block2 = NULL;
            if (connect1!=NULL) block1 = connect1.getLayoutBlock();
            if (connect2!=NULL) block2 = connect2.getLayoutBlock();
            if ( (block1!=NULL) && (block1==block2) ) {
                popup.add(rb.getQString("Block")+": "+block1.getID());
            }
            else if ( (block1!=NULL) && (block2!=NULL) && (block1!=block2) ) {
                popup.add(rb.getQString("BlockDivider"));
                popup.add(" "+rb.getQString("Block1ID")+": "+block1.getID());
                popup.add(" "+rb.getQString("Block2ID")+": "+block2.getID());
                blockBoundary = true;
            }
            break;
        case END_BUMPER:
            popup.add(rb.getQString("EndBumper"));
            LayoutBlock blockEnd = NULL;
            if (connect1!=NULL) blockEnd = connect1.getLayoutBlock();
            if (blockEnd!=NULL) {
                popup.add(rb.getQString("BlockID")+": "+blockEnd.getID());
            }
            endBumper = true;
            break;
        default : break;
    }
    popup.add(new JSeparator(JSeparator.HORIZONTAL));
    popup.add(new AbstractAction(rb.getQString("Remove")) {
            /*public*/ void actionPerformed(ActionEvent e) {
                if (layoutEditor.removePositionablePoint(instance)) {
                    // user is serious about removing this point from the panel
                    remove();
                    dispose();
                }
            }
        });
    if (blockBoundary) {
        popup.add(new AbstractAction(rb.getQString("SetSignals")) {
                /*public*/ void actionPerformed(ActionEvent e) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                // bring up signals at level crossing tool dialog
                tools.setSignalsAtBlockBoundaryFromMenu(instance,
                    layoutEditor.signalIconEditor,layoutEditor.signalFrame);
                }
            });
        popup.add(new AbstractAction(rb.getQString("SetSensors")) {
            /*public*/ void actionPerformed(ActionEvent event) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                // bring up signals at block boundary tool dialog
                tools.setSensorsAtBlockBoundaryFromMenu(instance,
                    layoutEditor.sensorIconEditor,layoutEditor.sensorFrame);
            }
        });
        popup.add(new AbstractAction(rb.getQString("SetSignalMasts")) {
            /*public*/ void actionPerformed(ActionEvent event) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                // bring up signals at block boundary tool dialog
                tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
            }
        });
    }
    if (endBumper){
        popup.add(new AbstractAction(rb.getQString("SetSensors")) {
            /*public*/ void actionPerformed(ActionEvent event) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                // bring up signals at block boundary tool dialog
                tools.setSensorsAtBlockBoundaryFromMenu(instance,
                    layoutEditor.sensorIconEditor,layoutEditor.sensorFrame);
            }
        });
        popup.add(new AbstractAction(rb.getQString("SetSignalMasts")) {
            /*public*/ void actionPerformed(ActionEvent event) {
                if (tools == NULL) {
                    tools = new LayoutEditorTools(layoutEditor);
                }
                // bring up signals at block boundary tool dialog
                tools.setSignalMastsAtBlockBoundaryFromMenu(instance);
            }
        });
    }
    layoutEditor.setShowAlignmentMenu(popup);
    popup.show(e.getComponent(), e.getX(), e.getY());
}

QString where(MouseEvent e) {
    return ""+e.getX()+","+e.getY();
}

/**
 * Clean up when this object is no longer needed.  Should not
 * be called while the object is still displayed; see remove()
 */
void dispose() {
    if (popup != NULL) popup.removeAll();
    popup = NULL;
}

/**
 * Removes this object from display and persistance
 */
void remove() {
    // remove from persistance by flagging inactive
    active = false;
}

boolean active = true;
/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/ boolean isActive() {
    return active;
}

static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionablePoint.class.getName());

}
