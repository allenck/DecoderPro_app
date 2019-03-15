#ifndef TRACKSEGMENT_H
#define TRACKSEGMENT_H

#include <QObject>
#include "layoutblock.h"
#include "layouteditor.h"
#include "abstractaction.h"

class LayoutBlock;
class LayoutEditor;
class LIBLAYOUTEDITORSHARED_EXPORT TrackSegment : public LayoutTrack
{
    Q_OBJECT
public:
//    explicit TrackSegment(QObject *parent = 0);
    /*public*/ TrackSegment(QString id, LayoutTrack *c1, int t1, LayoutTrack *c2, int t2, bool dash, bool main, LayoutEditor* myPanel);
    // alternate constructor for loading layout editor panels
    /*public*/ TrackSegment(QString id, QString c1Name, int t1, QString c2Name, int t2, bool dash, bool main, bool hide, LayoutEditor* myPanel);
    /*public*/ bool getArc() {return arc;}
    /*public*/ QString toString();

    /**
     * Accessor methods
    */
    /*public*/ QString getID();
    /*public*/ QString getBlockName();
    /*public*/ int getType1() ;
    /*public*/ int getType2() ;
    /*public*/ LayoutTrack* getConnect1();
    /*public*/ LayoutTrack *getConnect2();
    QT_DEPRECATED /*public*/ bool getDashed();
    /*public*/ bool isDashed();
    /*public*/ void setDashed(bool dash);
//    /*public*/ bool getHidden();
//    /*public*/ void setHidden(bool hide);
    QT_DEPRECATED /*public*/ bool getMainline();
    /*public*/ bool isMainline();
    /*public*/ void setMainline(bool main);
    /*public*/ void setArc(bool boo);
    QT_DEPRECATED /*public*/ bool getCircle();
    /*public*/ void setCircle(bool boo);
    QT_DEPRECATED /*public*/ bool getFlip();
    /*public*/ void setFlip(bool boo);
    ///*public*/ int getStartAngle() {return startangle;}
    ///*public*/ void setStartAngle(int x) {startangle = x;}
    QT_DEPRECATED /*public*/ bool getBezier();
    /*public*/ bool isBezier();
    /*public*/ void setBezier(bool boo);

    /*public*/ double getAngle();
    /*public*/ void setAngle(double x);
    //This method is used to determine if we need to redraw a curved piece of track
    //It saves having to recalculate the circle details each time.
    /*public*/ bool trackNeedsRedraw();
    /*public*/ void trackRedrawn();
    ///*public*/ int getRadius() {return radius;}
    ///*public*/ void setRadius(int x) {radius = x;}

    /*public*/ LayoutBlock* getLayoutBlock();
    /*public*/ QString getConnect1Name();
    /*public*/ QString getConnect2Name();
    /**
     * Set Up a Layout Block for a Track Segment
     */
    /*public*/ void setLayoutBlock (LayoutBlock* b);
    /*public*/ void setLayoutBlockByName (QString name);
    /*public*/ void scaleCoords(float xFactor, float yFactor);
    /*public*/ void translateCoords(float xFactor, float yFactor);
    /*public*/ void setCoordsCenter(/*@Nonnull*/ QPointF newCenterPoint);

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
    /*public*/ bool isShowConstructionLines();
    /*public*/ void hideConstructionLines(int hide);
    /*public*/ bool hideConstructionLines();
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
    /*public*/ double getStartAdj();
    /*public*/ void setStartAdj(double Startadj);
    /*public*/ double getCentreX();
    /*public*/ void setCentreX(double x);
    /*public*/ double getCentreY();
    /*public*/ void setCentreY(double y);
    /*public*/ QPointF getCentre();
    /*public*/ double getTmpAngle();
    /*public*/ void setTmpAngle(double TmpAngle);
    /*public*/ QPointF getCoordsCenterCircle();
    /*public*/ void setCoordsCenterCircle(QPointF p);
    /*public*/ double getChordLength();
    /*public*/ void setChordLength(double chord);
    void changeType(int choice);
    double radToDeg(double radians);
    double degToRad(double degrees);
    /*public*/ enum CONSTRUCT
    {
     SHOWCON = 0x01,
     HIDECON = 0x02,//flag set on a segment basis.
     HIDECONALL = 0x04  //Used by layout editor for hiding all
    };
    /*public*/ int showConstructionLine;// = SHOWCON;
    /*public*/ QRectF getBounds();
    /*public*/ bool hasDecorations();
    /*public*/ QMap<QString, QString>* getDecorations();
    /*public*/ void setDecorations(QMap<QString, QString>* decorations);
    /*public*/ int getArrowStyle();
    /*public*/ void setArrowStyle(int newVal);
    /*public*/ bool isArrowEndStart();
    /*public*/ void setArrowEndStart(bool newVal);
    /*public*/ bool isArrowEndStop();
    /*public*/ void setArrowEndStop(bool newVal);
    /*public*/ bool isArrowDirIn();
    /*public*/ void setArrowDirIn(bool newVal);
    /*public*/ bool isArrowDirOut();
    /*public*/ void setArrowDirOut(bool newVal);
    /*public*/ QColor getArrowColor() ;
    /*public*/ void setArrowColor(QColor newVal);
    /*public*/ int getArrowLineWidth() ;
    /*public*/ void setArrowLineWidth(int newVal);
    /*public*/ int getArrowLength();
    /*public*/ void setArrowLength(int newVal);
    /*public*/ int getArrowGap();
    /*public*/ void setArrowGap(int newVal);
    /*public*/ bool isBridgeSideRight();
    /*public*/ void setBridgeSideRight(bool newVal);
    /*public*/ bool isBridgeSideLeft();
    /*public*/ void setBridgeSideLeft(bool newVal);
    /*public*/ bool isBridgeHasEntry();
    /*public*/ void setBridgeHasEntry(bool newVal);
    /*public*/ bool isBridgeHasExit();
    /*public*/ void setBridgeHasExit(bool newVal);
    /*public*/ QColor getBridgeColor() ;
    /*public*/ void setBridgeColor(QColor newVal);
    /*public*/ int getBridgeDeckWidth();
    /*public*/ void setBridgeDeckWidth(int newVal);
    /*public*/ int getBridgeLineWidth();
    /*public*/ void setBridgeLineWidth(int newVal);
    /*public*/ int getBridgeApproachWidth();
    /*public*/ void setBridgeApproachWidth(int newVal);
    /*public*/ bool isBumperEndStart();
    /*public*/ void setBumperEndStart(bool newVal);
    /*public*/ bool isBumperEndStop();
    /*public*/ void setBumperEndStop(bool newVal);
    /*public*/ QColor getBumperColor();
    /*public*/ void setBumperColor(QColor newVal);
    /*public*/ int getBumperLineWidth();
    /*public*/ void setBumperLineWidth(int newVal);
    /*public*/ int getBumperLength();
    /*public*/ void setBumperLength(int newVal);
    /*public*/ bool isBumperFlipped();
    /*public*/ void setBumperFlipped(bool newVal);
    /*public*/ bool isTunnelSideRight();
    /*public*/ void setTunnelSideRight(bool newVal);
    /*public*/ bool isTunnelSideLeft();
    /*public*/ void setTunnelSideLeft(bool newVal);
    /*public*/ bool isTunnelHasEntry();
    /*public*/ void setTunnelHasEntry(bool newVal);
    /*public*/ bool isTunnelHasExit();
    /*public*/ void setTunnelHasExit(bool newVal);
    /*public*/ QColor getTunnelColor();
    /*public*/ void setTunnelColor(QColor newVal);
    /*public*/ int getTunnelFloorWidth();
    /*public*/ void setTunnelFloorWidth(int newVal);
    /*public*/ int getTunnelLineWidth();
    /*public*/ void setTunnelLineWidth(int newVal);
    /*public*/ int getTunnelEntranceWidth();
    /*public*/ void setTunnelEntranceWidth(int newVal);
    /*public*/ double getCentreSegX();
    /*public*/ void setCentreSegX(double CentreX);
    /*public*/ double getCentreSegY();
    /*public*/ void setCentreSegY(double CentreY) ;
    /*public*/ QPointF getCentreSeg();
    /*public*/ bool isCircle();
    /*public*/ bool isFlip();
    /*public*/ bool isArc();
    /*public*/ void setCentreSeg(QPointF p);
    /*public*/ void reCheckBlockBoundary();
    /*public*/ QPointF getCoordsForConnectionType(int connectionType);
    /*public*/ LayoutTrack* getConnection(int connectionType) throw (JmriException);
    /*public*/ void setConnection(int connectionType, /*@Nullable*/ LayoutTrack* o, int type) throw (JmriException);
    /*public*/ int getNumberOfBezierControlPoints();
    /*public*/ QPointF getBezierControlPoint(int index);
    /*public*/ void setBezierControlPoint(/*@Nullable*/ QPointF p, int index);
    /*public*/ double getDirectionRAD();
    /*public*/ double getDirectionDEG();
    /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock);
    /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
                   /*@Nonnull*/ QSet<QString> TrackNameSet);
    /*public*/ void checkForNonContiguousBlocks(
            /*@Nonnull*/ QMap<QString, QList<QSet<QString> > > blockNamesToTrackNameSetsMap);
    /*public*/ bool checkForUnAssignedBlocks();
    /*public*/ QList<int> checkForFreeConnections();

signals:
    
public slots:
    void on_actionEdit_triggered();
    void on_changeType(QAction* act);
    void flipAngle();
    void on_actionRemove();
    /*public*/ void splitTrackSegment();

private:
    // defined constants

    // operational instance variables (not saved between sessions)
    /*private*/ LayoutBlock* block;// = NULL;
//    /*private*/ TrackSegment* instance;// = NULL;
    /*private*/ LayoutEditor* layoutEditor;// = NULL;

    // persistent instances variables (saved between sessions)
//    /*private*/ QString ident;// = "";
    /*private*/ QString blockName;// = "";
    /*private*/ bool dashed = false;
    /*private*/ bool mainline = false;
    /*private*/ bool arc = false;
    /*private*/ bool flip = false;
    /*private*/ double angle;// =0.0D;
    /*private*/ bool circle=false;
    /*private*/ bool changed=false;
    /*private*/ bool bezier = false;
    // for Bezier
    /*private*/ QList<QPointF> bezierControlPoints;// = QList<QPointF>(); // list of control point displacements

    /*private*/ QString getConnectName(LayoutTrack* o,int type);

    /*private*/ LayoutBlock* getBlock (LayoutTrack *connect, int type);
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
    /*private*/ QMenu* popupMenu = nullptr;
    /*private*/ QAction* mainlineCheckBoxMenuItem;// = new JCheckBoxMenuItem(Bundle.getMessage("MainlineCheckBoxMenuItemTitle"));
    /*private*/ QAction* hiddenCheckBoxMenuItem;// = new JCheckBoxMenuItem(Bundle.getMessage("HiddenCheckBoxMenuItemTitle"));
    /*private*/ QAction* dashedCheckBoxMenuItem;// = new JCheckBoxMenuItem(Bundle.getMessage("DashedCheckBoxMenuItemTitle"));
    /*private*/ QAction* flippedCheckBoxMenuItem;// = new JCheckBoxMenuItem(Bundle.getMessage("FlippedCheckBoxMenuItemTitle"));

    /*private*/ bool needsRedraw;// = false;
 QGraphicsItemGroup* itemMain = nullptr;
 QGraphicsItemGroup* itemSide = nullptr;
 QGraphicsItem* dashedItem = nullptr;

// QGraphicsItem* circleItem;
// QGraphicsItem* trackOval;
 QGraphicsItem* decorationItems = nullptr;
 QGraphicsItemGroup* rects = nullptr;
 void init(QString ident);
 static Logger* log;
 void drawHiddenTrack(LayoutEditor* editor, QGraphicsScene* g2);
 void invalidate(EditScene *g2);
 void drawDashedTrack(LayoutEditor* editor, QGraphicsScene* g2, bool mainline);
 /*private*/ void calculateTrackSegmentAngle();
// void drawSolidTrack(LayoutEditor* editor, QGraphicsScene* g2, bool isMainline);
// void drawTrackOvals(LayoutEditor *editor, QGraphicsScene *g2);
// void drawTrackCircleCentre(LayoutEditor *editor, QGraphicsScene *g2);
 /*private*/ void reCalculateTrackSegmentAngle(double x, double y);

 /*private*/ int arrowGap = 1;
 /*private*/ int arrowStyle = 0;
 /*private*/ bool arrowEndStart = false;
 /*private*/ bool arrowEndStop = false;
 /*private*/ bool arrowDirIn = false;
 /*private*/ bool arrowDirOut = false;
 /*private*/ QColor arrowColor;// = Color.BLACK;
 /*private*/ int arrowLineWidth = 4;
 /*private*/ int arrowLength = 4;

 /*private*/ bool bridgeSideRight = false;
 /*private*/ bool bridgeSideLeft  = false;
 /*private*/ bool bridgeHasEntry = false;
 /*private*/ bool bridgeHasExit = false;
 /*private*/ QColor bridgeColor;// = QColor(Qt::black);
 /*private*/ int bridgeDeckWidth = 10;
 /*private*/ int bridgeLineWidth = 1;
 /*private*/ int bridgeApproachWidth = 4;
 /*private*/ int bumperLineWidth = 2;
 /*private*/ bool bumperFlipped = false;
 /*private*/ bool bumperEndStart = false;
 /*private*/ bool bumperEndStop = false;
 /*private*/ QColor bumperColor;// = Color.BLACK;
 /*private*/ void setupDefaultBumperSizes(LayoutEditor* layoutEditor);
 /*private*/ int bumperLength = 6;
 /*private*/ bool tunnelSideRight = false;
 /*private*/ bool tunnelSideLeft = false;
 /*private*/ bool tunnelHasEntry = false;
 /*private*/ bool tunnelHasExit = false;
 /*private*/ QColor tunnelColor;// = Color.BLACK;
 /*private*/ int tunnelFloorWidth = 10;
 /*private*/ int tunnelLineWidth = 1;
 /*private*/ int tunnelEntranceWidth = 16;

 /*
  * The following are used only as a temporary store after a circle or arc
  * has been calculated. This prevents the need to recalculate the values
  * each time a re-draw is required.
  */
 /*private*/ double centreSegX;
 /*private*/ double centreSegY;
 /*private*/ void addBezierControlPointBefore(int index);
 /*private*/ void addBezierControlPointAfter(int index);
 /*private*/ void deleteBezierControlPoint(int index);
 /*private*/ int drawArrow(EditScene* g2,
                           QPointF ep,
                           double angleRAD,
                           bool dirOut,
                           int offset, QPen stroke);

private slots:
 void onMakeLabel1();
 void onMakeLabel2();
 void onMainlineCheckBox();
 void onHiddenChecKBox();
 void onDashedCheckBox();
 void onFlippedCheckBox();
 void onSetArrowStyle();
 void onArrowEnd();
 void onArrowDirection();
 void onArrowColor();
 void onArrowWidth();
 void onArrowLength();
 void onArrowGap();
 void onEdit();
 void onDelete();
 void onChangeTo();
 void onConstruct();
 void onViewBlockRouting();

protected:
 /*protected*/ void updateBlockInfo();
 /*protected*/ void setNewConnect1(LayoutTrack *o, int type);
 /*protected*/ void setNewConnect2(LayoutTrack* o, int type);
 /*protected*/ LayoutTrack* connect1 = nullptr;
 /*protected*/ int type1 = 0;
 /*protected*/ LayoutTrack* connect2 = nullptr;
 /*protected*/ int type2 = 0;
 /*protected*/ void drawDecorations(EditScene* g2);
 /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock);
 /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement);
 /*protected*/ void highlightUnconnected(EditScene* g2, int selectedType);
 /*protected*/ void drawEditControls(EditScene* g2);
 /*protected*/ void drawTurnoutControls(EditScene* g2);
 /*protected*/ void showBezierPopUp(QGraphicsSceneMouseEvent* e, int hitPointType);
 /*protected*/ int findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected);
 /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity();
 /**
  * Display popup menu for information and editing
  */
 /*protected*/ QMenu* showPopup(QGraphicsSceneMouseEvent* e);

 friend class LayoutEditor;
 friend class EditTrackSegmentDlg;
 friend class LoadXml;
 friend class PositionablePoint;
 friend class LayoutEditorAuxTools;
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
