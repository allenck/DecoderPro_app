#include "tracknode.h"
#include "tracksegment.h"
#include "layouteditor.h"

TrackNode::TrackNode(QObject *parent) :
    QObject(parent)
{
}
/**
 * TrackNode is a temporary object specifying and returning track node information
 * <P>
 * Used in conjunction with ConnectivityUtil.java to return information about track nodes
 *      following a search of layout connectivity.
 * <P>
 * Track nodes are nodes in the layout connectivity diagram. They may be:
 *		positionable points - either anchor points that define a block boundary or end bumpers
 *               (end of a track),
 *		turnouts, -OR_
 *		level crossings
 *<P>
 * The components of a TrackNode are:
 *      Node QObject* - the object reached by searching connectivity
 *		Node Type - connection types defined in Layout Editor, for example, TURNOUT_A, indicates
 *			a turnout connected at A (the throat of a RH, LH, or WYE turnout)
 *      Track Segment - the track segment connected at the connection point specified in
 *          Node Type
 *		Reached End Bumper - 'true' if the connectivity search has reached an end bumper (the
 *			end of the search track) before reaching a Node QObject*. 'false' otherwise.
 *		Node State - if the Node QObject* can have multiple states, for example, a turnout,
 *			this gives the state it was when finding this track node.
 *<P>
 * Actually you could think of an End Bumper as a 'Node', but End Bumpers are treated
 *		differently here. When an End Bumper is reached during a connectivity search,
 *		Track Segment is returned, Reached End Bumper is set true, and Node QObject* and Node
 *		Type, are not returned.
 *
 * @author	Dave Duchamp  Copyright (C) 2009
 * @version	$Revision: 17977 $
 */
///*public*/ class TrackNode {

    /*public*/ TrackNode::TrackNode(LayoutTrack* node, int nodeType, TrackSegment* segment, bool endBumper, int nodeState)
{
 _Node = NULL;
 _NodeType = LayoutEditor::NONE;
 _TrackSegment = NULL;
 _ReachedEndBumper = false;
 _NodeState = 0;

 _Node = node;
        _NodeType = nodeType;
        _TrackSegment = segment;
        _ReachedEndBumper = endBumper;
        _NodeState = nodeState;
    }


    // temporary instance variables


    /**
     * Operational methods
     */

    /**
     * Returns the Block of the node QObject* at the nodeType position
     */
    /*public*/ Block* TrackNode::getNodeBlock() {
        if (LayoutEditor::POS_POINT==_NodeType) {
            return _TrackSegment->getLayoutBlock()->getBlock();
        }
        else if (LayoutEditor::TURNOUT_A==_NodeType) {
            return ((LayoutTurnout*)_Node)->getLayoutBlock()->getBlock();
        }
        else if (LayoutEditor::TURNOUT_B==_NodeType) {
            return ((LayoutTurnout*)_Node)->getLayoutBlockB()->getBlock();
        }
        else if (LayoutEditor::TURNOUT_C==_NodeType) {
            return ((LayoutTurnout*)_Node)->getLayoutBlockC()->getBlock();
        }
        else if (LayoutEditor::TURNOUT_D==_NodeType) {
            return ((LayoutTurnout*)_Node)->getLayoutBlockD()->getBlock();
        }
        else if ( (LayoutEditor::LEVEL_XING_A==_NodeType) ||
                    (LayoutEditor::LEVEL_XING_C==_NodeType) ) {
            return ((LevelXing*)_Node)->getLayoutBlockAC()->getBlock();
        }
        else if ( (LayoutEditor::LEVEL_XING_B==_NodeType) ||
                    (LayoutEditor::LEVEL_XING_D==_NodeType) ) {
            return ((LevelXing*)_Node)->getLayoutBlockBD()->getBlock();
        }
        return NULL;
    }

//    static org.apache.log4j.Category log = org.apache.log4j.Logger.getLogger(TrackNode.class.getName());
//}

///* @(#)TrackNode.java */
