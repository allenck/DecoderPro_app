#ifndef LAYOUTTRACK_H
#define LAYOUTTRACK_H

#include <QObject>
#include "loggerfactory.h"
#include  <QPointF>
#include <QRectF>
#include <QPointF>
#include "propertychangesupport.h"
#include "editscene.h"

class QGraphcsScene;
class LayoutBlock;
class LayoutConnectivity;
class LayoutEditor;
class LayoutTrack : public QObject
{
 Q_OBJECT
public:
 ///*explicit*/ LayoutTrack(QObject *parent = nullptr);
 /*public*/ LayoutTrack(/*@Nonnull*/ QString ident, /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor, QObject* parent = nullptr);
 ~LayoutTrack()  override {}
 LayoutTrack(const LayoutTrack&) : QObject() {}
 enum CONNECTIONTYPES
 {
  // connection types
  NONE = 0,
  POS_POINT = 1,
  TURNOUT_A = 2,  // throat for RH, LH, and WYE turnouts
  TURNOUT_B = 3,  // continuing route for RH or LH turnouts
  TURNOUT_C = 4,  // diverging route for RH or LH turnouts
  TURNOUT_D = 5,  // double-crossover or single crossover only
  LEVEL_XING_A = 6,
  LEVEL_XING_B = 7,
  LEVEL_XING_C = 8,
  LEVEL_XING_D = 9,
  TRACK = 10,
  TURNOUT_CENTER = 11, // non-connection points should be last
  LEVEL_XING_CENTER = 12,
  TURNTABLE_CENTER = 13,
  LAYOUT_POS_LABEL = 14,
  LAYOUT_POS_JCOMP = 15,
  MULTI_SENSOR = 16,
  MARKER = 17,
  TRACK_CIRCLE_CENTRE = 18,
  SLIP_CENTER = 20, //
  SLIP_A = 21, // offset for slip connection points
  SLIP_B = 22, // offset for slip connection points
  SLIP_C = 23, // offset for slip connection points
  SLIP_D = 24, // offset for slip connection points
  SLIP_LEFT = 25,
  SLIP_RIGHT = 26,
  BEZIER_CONTROL_POINT_OFFSET_MIN = 30, // offset for TrackSegment Bezier control points (minimum)
  BEZIER_CONTROL_POINT_OFFSET_MAX = 38, // offset for TrackSegment Bezier control points (maximum)
  TURNTABLE_RAY_OFFSET = 50 // offset for turntable connection points
 };
 /*public*/ QString getId();
 /*public*/ QString getName() ;
 /*public*/ QPointF getCoordsCenter() const;
 /*public*/ virtual void setCoordsCenter(/*@Nonnull*/ QPointF p) ;
 /*public*/ virtual bool hasDecorations() ;
 /*public*/ virtual QMap<QString, QString> *getDecorations();
 /*public*/ virtual void setDecorations(QMap<QString, QString>* decorations) ;
 /*public*/ static void setDefaultTrackColor(QColor color);
 /*public*/ bool isHidden();
 //@Deprecated // Java standard pattern for bool getters is "isHidden()"
 QT_DEPRECATED/*public*/ bool getHidden();
 /*public*/ void setHidden(bool hide);
 PropertyChangeSupport* propertyChangeSupport;
 /*public*/ QString getTurnoutStateString(int turnoutState);
 /*public*/ /*abstract*/virtual void setObjects(/*@Nonnull*/ LayoutEditor* le);
 /*public*/ /*abstract*/ virtual void scaleCoords(double xFactor, double yFactor);
 /*public*/ /*abstract*/ virtual void translateCoords(double xFactor, double yFactor);
 /*public*/ /*abstract*/ virtual QPointF getCoordsForConnectionType(int);
 /*public*/ /*abstract*/ virtual QRectF getBounds();
 /*public*/ /*abstract*/ virtual LayoutTrack* getConnection(int connectionType) throw (JmriException);
 /*public*/ /*abstract*/ virtual void setConnection(int connectionType, LayoutTrack* o, int type) throw (JmriException);
 /*public*/ virtual bool isDisconnected(int connectionType);
 /*public*/ /*abstract*/ virtual QList<int> checkForFreeConnections();
 /*public*/ /*abstract*/ virtual bool checkForUnAssignedBlocks();
 /*public*/ /*abstract*/ virtual void checkForNonContiguousBlocks(
         /*@Nonnull*/ QMap<QString, QList<QSet<QString> > > blockNamesToTrackNameSetMaps);
 /*public*/ /*abstract*/ virtual void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
         /*@Nonnull*/ QSet<QString> trackNameSet);
 /*public*/ /*abstract*/ virtual void setAllLayoutBlocks(LayoutBlock* /*layoutBlock*/);
 QGraphicsItemGroup* item = nullptr;
 QGraphicsItemGroup* itemMain = nullptr;
 QGraphicsItemGroup* itemSide = nullptr;
 QGraphicsItemGroup* itemDashed = nullptr;
 QGraphicsItemGroup* itemDashedSide = nullptr;
 QGraphicsItemGroup* itemTies = nullptr;
 QGraphicsItemGroup* itemTiesSide = nullptr;
 QGraphicsItemGroup* itemBallast = nullptr;
 QGraphicsItemGroup* itemBallastSide = nullptr;
 QGraphicsItemGroup* itemPoints = nullptr;
 QGraphicsItemGroup* itemBlock = nullptr;
 QGraphicsItemGroup* itemBlockSide = nullptr;


 /*public*/ virtual void invalidate(EditScene* /*g2*/) {}
// /*public*/ void invalidateItemType(bool isMain);
 /*public*/ QGraphicsItemGroup* invalidateItem(EditScene* g2, QGraphicsItemGroup* turnoutItem);
 enum ITEMTYPE
 {
  track,
  ties,
  ballast,
  points,
  block,
  dashed
 };
 QGraphicsItemGroup* selectItemGroup(ITEMTYPE, bool isMain, bool isBlock);

signals:

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("LayoutTrack");
 QGraphicsItemGroup* hiddenItems = nullptr;

protected:
 /*protected*/ LayoutEditor* layoutEditor = nullptr;
 /*protected*/ QString ident = "";
 /*protected*/ QPointF center;// = new Point2D.Double(50.0, 50.0);
 /*protected*/ bool hidden = false;
 /*protected*/ static /*final*/ double controlPointSize;// = 3.0;   // LayoutEditor.SIZE;
 /*protected*/ static /*final*/ double controlPointSize2;// = 2.0 * controlPointSize; // LayoutEditor.SIZE2;
 /*protected*/ static QColor defaultTrackColor;// = Color.black;
 /*protected*/ /*abstract*/ virtual void reCheckBlockBoundary() const;
 /*protected*/ /*abstract*/ virtual QList<LayoutConnectivity*> getLayoutConnectivity();
 /*protected*/ /*abstract*/ virtual QMenu* showPopup(/*@Nullable */QGraphicsSceneMouseEvent* mouseEvent);
 /*protected*/ QMenu* showPopup(QPointF where);
 /*protected*/ QMenu* showPopup();
 /*protected*/ QPointF rotatePoint(/*@Nonnull*/ QPointF p, double sineRot, double cosineRot) ;
 /*protected*/ /*abstract*/ virtual int findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles, bool requireUnconnected);
 /*protected*/ int findHitPointType(/*@Nonnull*/ QPointF p);
 /*protected*/ int findHitPointType(/*@Nonnull*/ QPointF p, bool useRectangles);
 /*protected*/ static bool isConnectionHitType(int hitType);
 /*protected*/ static bool isControlHitType(int hitType);
 /*protected*/ static bool isPopupHitType(int hitType);
 /*public*/ /*abstract*/ virtual bool isMainline();
 /*protected*/ /*abstract*/ virtual void draw1(EditScene* g2, bool isMain, bool isBlock, ITEMTYPE );
 /*protected*/ /*abstract*/ virtual void draw2(EditScene *g2, bool, float, ITEMTYPE );
 /*protected*/ void drawHidden(EditScene* g2);
 /*protected*/ /*abstract*/ virtual void highlightUnconnected(EditScene *g2, int specificType);
 /*protected*/ virtual void highlightUnconnected(EditScene* g2);
 /*protected*/ /*abstract*/ virtual void drawEditControls(EditScene* g2);
 /*protected*/ /*abstract*/ virtual void drawTurnoutControls(EditScene *g2);
 /*protected*/ virtual void drawDecorations(EditScene *g2);
 /*protected*/ QMap<QString, QString>* decorations = nullptr;
 /*protected*/ QColor getColorForTrackBlock(
         /*@Nullable*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor);
 /*protected*/ QColor getColorForTrackBlock(/*@Nullable*/ LayoutBlock* lb);
 /*protected*/ QColor setColorForTrackBlock(EditScene* g2,
         /*@Nullable*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor);
 /*protected*/ QColor setColorForTrackBlock(EditScene* g2, /*@Nullable*/ LayoutBlock* lb);
 /*protected*/ static bool isBezierHitType(int hitType);

 friend class LayoutEditorAuxTools;
 friend class LayoutEditor;
 friend class TrackSegment;
};

#endif // LAYOUTTRACK_H
