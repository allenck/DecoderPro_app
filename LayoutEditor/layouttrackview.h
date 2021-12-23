#ifndef LAYOUTTRACKVIEW_H
#define LAYOUTTRACKVIEW_H

#include <QObject>
#include "layouttrack.h"
#include "layoutturnout.h"
#include "hitpointtype.h"
#include "jcheckboxmenuitem.h"

class LayoutTrackView : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LayoutTrackView(/*@Nonnull*/ LayoutTrack* track, /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ LayoutTrackView(/*@Nonnull*/ LayoutTrack* track, /*@Nonnull*/ QPointF c, /*@Nonnull*/ LayoutEditor* layoutEditor);
//  static /*public*/ LayoutTrackView* makeTrackView(/*@Nonnull*/ LayoutTrack* trk);
  /*public*/ bool hasDecorations();
  /*final*/ /*public*/ QPointF getCoordsCenter();
  /*final*/ /*public*/ QString getId();
  /*final*/ /*public*/ QString getName();
  /*public*/ QMap<QString, QString> *getDecorations();
  /*public*/ void setDecorations(QMap<QString, QString> *decorations);
  /*final*/ /*public*/ LayoutEditorToolBarPanel* getLayoutEditorToolBarPanel();
  /*final*/ /*public*/ QGraphicsEllipseItem* trackEditControlCircleAt(/*@Nonnull*/ QPointF inPoint);
  /*final*/ /*public*/ QGraphicsEllipseItem* trackControlCircleAt(/*@Nonnull*/ QPointF inPoint);
  /*final*/ /*public*/ QGraphicsRectItem* trackControlCircleRectAt(/*@Nonnull*/ QPointF inPoint);
  /*public*/ bool isMainline();
  /*public*/ bool isHidden();
  /*public*/ void setHidden(bool hide);
  /*final*/ /*public*/ QString getTurnoutStateString(int turnoutState);
  virtual /*abstract*/ /*public*/ bool canRemove() = 0;
  /*final*/ /*public*/ void displayRemoveWarningDialog(QList<QString> itemList, QString typeKey);
  virtual /*public*/ void scaleCoords(double xFactor, double yFactor) = 0;
  virtual /*public*/ void translateCoords(double xFactor, double yFactor) = 0;
  virtual /*public*/ void rotateCoords(double angleDEG) = 0;
  /*final*/ /*protected*/ QPointF rotatePoint(/*@Nonnull*/ QPointF p, double sineRot, double cosineRot);
  virtual /*abstract*/ /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType) = 0;
  virtual /*abstract*/ /*public*/ QRectF getBounds() = 0;
  virtual /*abstract*/ /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ = 0;
  virtual /*abstract*/ /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ = 0;
  virtual /*public*/ bool isDisconnected(HitPointType::TYPES connectionType);
  virtual /*abstract*/ /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() = 0;
  virtual /*abstract*/ /*public*/ bool checkForUnAssignedBlocks() = 0;
  virtual /*abstract*/ /*public*/ void checkForNonContiguousBlocks(
    /*@Nonnull*/ QMap<QString, QList<QSet<QString>*>*> blockNamesToTrackNameSetMaps) = 0;
  virtual /*abstract*/ /*public*/ void collectContiguousTracksNamesInBlockNamed(
    /*@Nonnull*/ QString blockName,
    /*@Nonnull */QSet<QString>* TrackNameSet) = 0;
  virtual /*abstract*/ /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock) = 0;
  /*public*/ LayoutTrack* getLayoutTrack();
  virtual /*public*/ void setCoordsCenter(/*@Nonnull*/ QPointF p); // temporary = want to make protected after migration
  /*public*/ JCheckBoxMenuItem* loadArrowImageToJCBItem(int n, QMenu* arrowsCountMenu);

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
  /*public*/ QGraphicsItemGroup* invalidateItem(EditScene* g2, QGraphicsItemGroup* turnoutItem);
  QGraphicsItemGroup* labels = nullptr;
  QColor textColor = QColor(Qt::red);
  QFont textFont = QFont("Helvetica",12);
 signals:

 public slots:

 private:
  static Logger* log;
  /*final*/ /*private*/ LayoutTrack* layoutTrack;
  /*private*/ QPointF center = QPointF(50.0, 50.0);
  /*private*/ bool hidden = false;
  QGraphicsItemGroup* decorationItems = nullptr;
  QGraphicsItemGroup* rects = nullptr;
  QGraphicsItemGroup* itemGroup = nullptr;
  QGraphicsItemGroup* circles = nullptr;
 protected:
  /*final*/ /*protected*/ void setIdent(/*@Nonnull*/ QString ident);
  virtual /*protected*/ void drawEditControls(EditScene *g2) =0;
  virtual /*protected*/ void drawTurnoutControls(EditScene* g2) =0;
  virtual /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock) =0;
  virtual /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) =0;
  virtual /*protected*/ void drawDecorations(EditScene* g2) =0;
  /*final*/ /*protected*/ LayoutEditor* layoutEditor;
  /*final*/ /*protected*/ void drawHidden(EditScene* g2);
  /*final*/ /*protected*/ void drawLayoutTrackText(EditScene* g);
  /*protected*/ void drawLayoutTrackText(EditScene* g, QColor c, QFont f);
  virtual /*abstract*/ /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF hitPoint,
                                                  bool useRectangles,
                                                  bool requireUnconnected) = 0;
  /*final*/ /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF p);
  /*final*/ /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/ QPointF p, bool useRectangles);
  virtual /*abstract*/ /*protected*/ QMenu* showPopup(/*@Nonnull*/ QGraphicsSceneMouseEvent* mouseEvent) = 0;
  /*final*/ /*protected*/ QMenu* showPopup(QPointF where);
  /*final*/ /*protected*/ QMenu* showPopup();
  virtual /*abstract*/ /*protected*/ void reCheckBlockBoundary() = 0;
  virtual /*abstract*/ /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() = 0;
  /*protected*/ QMap<QString, QString>* decorations = nullptr;
  /*protected*/ static /*final*/const int NUM_ARROW_TYPES = 6;
  virtual /*abstract*/ /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) =0;
  /*final*/ /*protected*/ QColor getColorForTrackBlock(
          /*@CheckForNull*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor);
  /*final*/ /*protected*/ QColor getColorForTrackBlock(/*@CheckForNull*/ LayoutBlock* lb);
  /*final*/ /*protected*/ QColor setColorForTrackBlock(EditScene* g2,
                                                       /*@CheckForNull*/ LayoutBlock* layoutBlock, bool forceBlockTrackColor);
  /*final*/ /*protected*/ QColor setColorForTrackBlock(EditScene* g2, /*@CheckForNull*/ LayoutBlock* lb);
  /*final*/ /*protected*/ void highlightUnconnected(EditScene* g2);

  friend class LayoutEditorComponent;
  friend class LayoutEditor;
  friend class LayoutEditorChecks;
  friend class LayoutTrackView;
  friend class LayoutTurnoutView;
  friend class TrackSegmentView;
  friend class LevelXingView;
  friend class LayoutEditorAuxTools;
  friend class PositionablePointView;
  friend class LayoutSlipView;
};

#endif // LAYOUTTRACKVIEW_H
