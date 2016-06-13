#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include <QObject>
#include "layoutblock.h"
#include "layouteditor.h"
#include "abstractaction.h"

class LayoutBlock;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT TrackSegment : public QObject
{
    Q_OBJECT
public:
//    explicit TrackSegment(QObject *parent = 0);
    /*public*/ TrackSegment(QString id, QObject* c1, int t1, QObject* c2, int t2, bool dash, bool main, LayoutEditor* myPanel);
    // alternate constructor for loading layout editor panels
    /*public*/ TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor* myPanel);
    /*public*/ bool getArc() {return arc;}
    /**
     * Accessor methods
    */
    /*public*/ QString getID();
 /*public*/ QString getBlockName();
 /*public*/ int getType1() ;
 /*public*/ int getType2() ;
 /*public*/ QObject* getConnect1();
 /*public*/ QObject* getConnect2();
 /*public*/ bool getDashed();
 /*public*/ void setDashed(bool dash);
 /*public*/ bool getHidden();
 /*public*/ void setHidden(bool hide);
 /*public*/ bool getMainline();
 /*public*/ void setMainline(bool main);
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
    /**
     * Set Up a Layout Block for a Track Segment
     */
    /*public*/ void setLayoutBlock (LayoutBlock* b);
    /*public*/ void setLayoutBlockByName (QString name);
    // initialization instance variables (used when loading a LayoutEditor)
    /*public*/ QString tBlockName;// = "";
    /*public*/ QString tConnect1Name;// = "";
    /*public*/ QString tConnect2Name;// = "";
    /**
     * Initialization method
     *   The above variables are initialized by PositionablePointXml, then the following
     *        method is called after the entire LayoutEditor is loaded to set the specific
     *        TrackSegment objects.
     */
    /*public*/ void setObjects(LayoutEditor* p);
    /**
     * Clean up when this object is no longer needed.  Should not
     * be called while the object is still displayed; see remove()
     */
    void dispose() ;
    /**
     * Removes this object from display and persistance
     */
    void remove() ;
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive();
    /**
    * The following are used only as a temporary store after a circle or arc has been calculated.
    * This prevents the need to recalculate the values each time a re-draw is required.
    */
    /*public*/ QPointF getTmpPt1();
    /*public*/ QPointF getTmpPt2();
    /*public*/ void setTmpPt1(QPointF Pt1);
    /*public*/ void setTmpPt2(QPointF Pt2);

    ///*private*/ int startadj;

    /*public*/ double getCX();
    /*public*/ void setCX(double CX);
    /*public*/ double getCY();
    /*public*/ void setCY(double CY);
    /*public*/ double getCW();
    /*public*/ void setCW(double CW);
    /*public*/ double getCH();
    /*public*/ void setCH(double CH);
    /*public*/ double getStartadj();
    /*public*/ void setStartadj(double Startadj);
    /*public*/ double getCentreX();
    /*public*/ void setCentreX(double CentreX);
    /*public*/ double getCentreY();
    /*public*/ void setCentreY(double CentreY);
    /*public*/ double getTmpAngle();
    /*public*/ void setTmpAngle(double TmpAngle);
    /*public*/ QPointF getCoordsCenterCircle();
    /*public*/ double getChordLength();
    /*public*/ void setChordLength(double chord);
    void changeType(int choice);
    double radToDeg(double radians);
    double degToRad(double degrees);
    /*public*/ void hideConstructionLines(int hide) ;
    /*public*/ bool hideConstructionLines();
    /*public*/ enum CONSTRUCT
    {
     SHOWCON = 0x01,
     HIDECON = 0x02,//flag set on a segment basis.
     HIDECONALL = 0x04  //Used by layout editor for hiding all
    };
    /*public*/ int showConstructionLine;// = SHOWCON;
signals:
    
public slots:
    void on_actionEdit_triggered();
    void on_changeType(QAction* act);
    void flipAngle();
    void on_actionRemove();
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
    /*private*/ LayoutBlock* getBlock (QObject* connect, int type);
    /*private*/ double chordLength;
    bool active;// = true;
    /*private*/ QPointF pt1;
    /*private*/ QPointF pt2;
    /*private*/ double cX;
    /*private*/ double cY;
    /*private*/ double cW;
    /*private*/ double cH;
    /*private*/ double startadj;
    /*private*/ double centreX;
    /*private*/ double centreY;
    /*private*/ double tmpangle;
    QMenu* popup;// = NULL;
    /*private*/ bool needsRedraw;// = false;
 QGraphicsItem* item;
 QGraphicsItem* circleItem;
 QGraphicsItem* trackOval;
 void init(QString ident);
 Logger log;
 void drawHiddenTrack(LayoutEditor* editor, QGraphicsScene* g2);
 void invalidate(QGraphicsScene* g2);
 void drawDashedTrack(LayoutEditor* editor, QGraphicsScene* g2, bool mainline);
 /*private*/ void CalculateTrackSegmentAngle(LayoutEditor* editor);
 void drawSolidTrack(LayoutEditor* editor, QGraphicsScene* g2, bool isMainline);
 void drawTrackOvals(LayoutEditor *editor, QGraphicsScene *g2);
 void drawTrackCircleCentre(LayoutEditor *editor, QGraphicsScene *g2);
 /*private*/ void reCalculateTrackSegmentAngle(double x, double y);

protected:
 /*protected*/ void updateBlockInfo();
 /*protected*/ void setNewConnect1(QObject* o, int type);
 /*protected*/ void setNewConnect2(QObject* o, int type);

 friend class LayoutEditor;
 friend class EditTrackSegmentDlg;
 friend class LoadXml;
 /**
  * Display popup menu for information and editing
  */
 /*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e);
 friend class PositionablePoint;
};
class TSAbstractAction : public AbstractAction
{
 Q_OBJECT

public:
 TSAbstractAction(QString name, QObject* parent);
 public slots:
   /*public*/ void actionPerformed(ActionEvent* e = 0);
};

#endif // TRACKSEGMENT_H
