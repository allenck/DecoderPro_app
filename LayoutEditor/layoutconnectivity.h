#ifndef LAYOUTCONNECTIVITY_H
#define LAYOUTCONNECTIVITY_H

#include <QObject>
#include "layoutblock.h"
#include "tracksegment.h"
//#include "layoutturnout.h"
#include "positionablepoint.h"

class LayoutTurnout;
class PositionablePoint;
class LayoutConnectivity : public QObject
{
    Q_OBJECT
public:
/**
 * Constructor
 */
/*public*/ LayoutConnectivity (LayoutBlock* b1, LayoutBlock* b2);
// defined constants for crossover block boundary types.
const static  int NONE = 0;
const static  int XOVER_BOUNDARY_AB = 1;		// continuing
const static  int XOVER_BOUNDARY_CD = 2;		// continuing
const static  int XOVER_BOUNDARY_AC = 3;		// xed over
const static  int XOVER_BOUNDARY_BD = 4;		// xed over
/*public*/ LayoutBlock* getBlock1();
/*public*/ LayoutBlock* getBlock2();
/*public*/ int getDirection();
/*public*/ int getReverseDirection();
/*public*/ bool setDirection(int dir) ;
/*public*/ void setConnections (TrackSegment* t, QObject* o, int type, PositionablePoint* p) ;
/*public*/ void setXoverBoundary (LayoutTurnout* t, int type);
/*public*/ TrackSegment* getTrackSegment();
/*public*/ QObject* getConnectedObject();
/*public*/ int getConnectedType();
/*public*/ LayoutTurnout* getXover();
/*public*/ int getXoverBoundaryType();
/*public*/ PositionablePoint* getAnchor();

    
signals:
    
public slots:

private:
// instance variables
LayoutBlock* block1;// = NULL;
LayoutBlock* block2;// = NULL;
int direction;// = Path.NONE;
TrackSegment* track1;// = NULL;
QObject* connect2;// = NULL;
int typeConnect2;// = 0;
LayoutTurnout* xover;// = NULL;
int xoverBoundaryType;// = NONE;
PositionablePoint* anchor;// = NULL;
Logger log;
};

#endif // LAYOUTCONNECTIVITY_H
