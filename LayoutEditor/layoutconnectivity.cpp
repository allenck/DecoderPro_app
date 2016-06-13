#include "layoutconnectivity.h"

/**
 * A LayoutConnectivity object represents a junction between two LayoutBlocks
 *		on a LayoutEditor panel.
 * <P>
 * LayoutConnectivity objects do not persist (are not saved when panels are saved).
 *		Instead they are initialized when a panel is loaded and changed dynamically
 *		as a panel is edited.
 * <P>
 * The direction stored here is the direction for proceeding across the block
 *		boundary from block1 to block2.  The directions represent directions on
 *		the LayoutEditor panel. Allowed values (using Path object definitions) are:
 *			Path.NORTH (up on panel)
 *			Path.SOUTH (down on panel)
 *          Path.EAST (right on panel)
 *			Path.WEST (left on panel)
 *		and points in between:
 *			Path.NORTH + Path.EAST
 *			Path.NORTH + Path.WEST
 *			Path.SOUTH + Path.EAST
 *			Path.SOUTH + Path.WEST
 * <P>
 * The connected object in the first block is usually a track segment. This track
 *		segment is connected to an object in the second block. The connection point
 *		in the second block can be either one end of a track segment, or one of the
 *		connection points on a turnout, or one of the connection points on a level
 *		crossing. The allowed values for the connection points at the second block
 *		are defined in LayoutEditor.
 * <P>
 * The exception to the above is when a crossover turnout has multiple blocks.
 *		If so, at least one block boundary is internal to the crossover turnout.
 *      Such cases are handled differently, as "crossover block boundary types",
 *		see definition of the type codes below. The first letter in the boundary
 *		type corresponds to the first block, and the second letter corresponds to
 *		the second block. All four block boundaries are possible for the double
 *		crossover. One of the crossed over boundaries is not possible with each
 *      single crossover.
 * <P>
 * Note that each LayoutEditor panel has its own list of LayoutConnectivity objects,
 *		nominally called its "block connectivity". In contrast, there is only one set
 *		of LayoutBlocks, Blocks, and Paths, which are used by all LayoutEditor
 *		panels.
 * <P>
 * @author Dave Duchamp Copyright (c) 2007-2008
 * @version $Revision: 17977 $
 */
///*public*/ class LayoutConnectivity {

/**
 * Constructor
 */
/*public*/ LayoutConnectivity::LayoutConnectivity (LayoutBlock* b1, LayoutBlock* b2)
{
 block1 = NULL;
 block2 = NULL;
 direction = Path::NONE;
 track1 = NULL;
 connect2 = NULL;
 typeConnect2 = 0;
 xover = NULL;
 xoverBoundaryType = NONE;
 anchor = NULL;

    block1 = b1;
    if (block1==NULL) log.error("NULL block1 when creating Layout Connectivity");
    block2 = b2;
    if (block2==NULL) log.error("NULL block2 when creating Layout Connectivity");
}



/**
 * Accessor routines
 */
/*public*/ LayoutBlock* LayoutConnectivity::getBlock1() {return block1;}
/*public*/ LayoutBlock* LayoutConnectivity::getBlock2() {return block2;}
/*public*/ int LayoutConnectivity::getDirection() {return direction;}
/*public*/ int LayoutConnectivity::getReverseDirection() {
    if (direction==Path::NORTH) return (Path::SOUTH);
    if (direction==Path::SOUTH) return (Path::NORTH);
    if (direction==Path::EAST) return (Path::WEST);
    if (direction==Path::WEST) return (Path::EAST);
    if (direction==(Path::NORTH+Path::WEST)) return (Path::SOUTH+Path::EAST);
    if (direction==(Path::NORTH+Path::EAST)) return (Path::SOUTH+Path::WEST);
    if (direction==(Path::SOUTH+Path::WEST)) return (Path::NORTH+Path::EAST);
    if (direction==(Path::SOUTH+Path::EAST)) return (Path::NORTH+Path::WEST);
    return (Path::NONE);
}
/*public*/ bool LayoutConnectivity::setDirection(int dir) {
    if ( (dir==Path::NORTH) || (dir==Path::SOUTH) ||
            (dir==Path::EAST) || (dir==Path::WEST) ||
            (dir==(Path::NORTH+Path::WEST)) || (dir==(Path::NORTH+Path::EAST)) ||
            (dir==(Path::SOUTH+Path::WEST)) || (dir==(Path::SOUTH+Path::EAST)) ) {
        direction = dir;
        return (true);
    }
    // not one of the allowed directions
    direction = Path::NONE;
    return (false);
}
/*public*/ void LayoutConnectivity::setConnections (TrackSegment* t, QObject* o, int type, PositionablePoint* p) {
    track1 = t;
    if (t==NULL) log.error("NULL track1 when setting up LayoutConnectivity");
    connect2 = o;
    if (o==NULL) log.error("NULL connect object when setting up LayoutConnectivity");
    typeConnect2 = type;
    anchor = p;
}
/*public*/ void LayoutConnectivity::setXoverBoundary (LayoutTurnout* t, int type) {
    xover = t;
    if (t==NULL) log.error("NULL XOver when setting up LayoutConnectivity");
    xoverBoundaryType = type;
}
/*public*/ TrackSegment* LayoutConnectivity::getTrackSegment() {return track1;}
/*public*/ QObject* LayoutConnectivity::getConnectedObject() {return connect2;}
/*public*/ int LayoutConnectivity::getConnectedType() {return typeConnect2;}
/*public*/ LayoutTurnout* LayoutConnectivity::getXover() {return xover;}
/*public*/ int LayoutConnectivity::getXoverBoundaryType() {return xoverBoundaryType;}
/*public*/ PositionablePoint* LayoutConnectivity::getAnchor() {return anchor;}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LayoutConnectivity.class.getName());

//}
