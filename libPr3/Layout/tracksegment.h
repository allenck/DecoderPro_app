#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include <QObject>
#include "layoutblock.h"
#include "layouteditor.h"

class LayoutBlock;
class LayoutEditor;
class TrackSegment : public QObject
{
    Q_OBJECT
public:
    explicit TrackSegment(QObject *parent = 0);
    /*public*/ TrackSegment(QString id, QObject* c1, int t1, QObject* c2, int t2, bool dash, bool main, LayoutEditor* myPanel);
    // alternate constructor for loading layout editor panels
    /*public*/ TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor myPanel);
    /*public*/ QString getID() {return ident;}
    /*public*/ QString getBlockName() {return blockName;}
    /*public*/ int getType1() {return type1;}
    /*public*/ int getType2() {return type2;}
    /*public*/ QObject* getConnect1() {return connect1;}
    /*public*/ QObject* getConnect2() {return connect2;}
    /*public*/ bool getDashed() {return dashed;}
    /*public*/ void setDashed(bool dash) {dashed = dash;}
    /*public*/ bool getHidden() {return hidden;}
    /*public*/ void setHidden(bool hide) {hidden = hide;}
    /*public*/ bool getMainline() {return mainline;}
    /*public*/ void setMainline(bool main) {mainline = main;}
    /*public*/ bool getArc() {return arc;}
    /**
     * Accessor methods
    */
    /*public*/ void setArc(bool boo);
    /*public*/ bool getCircle() {return circle;}
    /*public*/ void setCircle(bool boo);
    /*public*/ bool getFlip() {return flip;}
    /*public*/ void setFlip(bool boo);
    ///*public*/ int getStartAngle() {return startangle;}
    ///*public*/ void setStartAngle(int x) {startangle = x;}
    /*public*/ double getAngle() {return angle;}
    /*public*/ void setAngle(double x);
    //This method is used to determine if we need to redraw a curved piece of track
    //It saves having to recalculate the circle details each time.
    /*public*/ bool trackNeedsRedraw() { return changed; }
    /*public*/ void trackRedrawn() { changed = false; }
    ///*public*/ int getRadius() {return radius;}
    ///*public*/ void setRadius(int x) {radius = x;}

    /*public*/ LayoutBlock* getLayoutBlock();
    /*public*/ QString getConnect1Name() {return getConnectName(connect1,type1);}
    /*public*/ QString getConnect2Name() {return getConnectName(connect2,type2);}

signals:
    
public slots:
private:
    // defined constants

    // operational instance variables (not saved between sessions)
    /*private*/ LayoutBlock* block;// = NULL;
    /*private*/ TrackSegment* instance;// = NULL;
    /*private*/ LayoutEditor* layoutEditor;// = NULL;

    // persistent instances variables (saved between sessions)
    /*private*/ QString ident;// = "";
    /*private*/ QString blockName;// = "";
    /*private*/ QObject* connect1;// = NULL;
    /*private*/ int type1;// = 0;
    /*private*/ QObject* connect2;// = NULL;
    /*private*/ int type2;// = 0;
    /*private*/ bool dashed;// = false;
    /*private*/ bool mainline;// = false;
    /*private*/ bool hidden;// = false;
    /*private*/ bool arc;// = false;
    /*private*/ bool flip;// = false;
    /*private*/ double angle;// =0.0D;
    /*private*/ bool circle;//=false;
    /*private*/ bool changed;//=false;

    /*private*/ QString getConnectName(QObject* o,int type);
 void init();
};

#endif // TRACKSEGMENT_H
