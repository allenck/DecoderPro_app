#ifndef TRACKSEGMENTVIEW_H
#define TRACKSEGMENTVIEW_H
#include "layouttrackview.h"
#include "tracksegment.h"
#include "tracksegmenteditor.h"
#include "hitpointtype.h"

class TrackSegmentView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ TrackSegmentView(/*@Nonnull*/ TrackSegment* track, LayoutEditor *layoutEditor);
  /*public*/ TrackSegment* getTrackSegment();
  /*public*/ QString toString();
  /*public*/ QString getBlockName();
  /*public*/ HitPointType::TYPES getType1();
  /*public*/ HitPointType::TYPES getType2();
  /*public*/ LayoutTrack* getConnect1();
  /*public*/ LayoutTrack* getConnect2();
  /*public*/ bool replaceTrackConnection(/*@CheckForNull*/ LayoutTrack* oldTrack, /*@CheckForNull*/ LayoutTrack* newTrack, HitPointType::TYPES newType);
  /*public*/ bool isDashed();
  /*public*/ void setDashed(bool dash);
  /*public*/ bool isArc();
  /*public*/ void setArc(bool boo);
  /*public*/ bool isCircle();
  /*public*/ void setCircle(bool boo);
  /*public*/ bool isFlip();
  /*public*/ void setFlip(bool boo);
  /*public*/ bool isBezier();
  /*public*/ void setBezier(bool boo);
  /*public*/ double getAngle();
  /*public*/ void setAngle(double x);
  /*public*/ double getDirectionRAD();
  /*public*/ double getDirectionDEG();
  /*public*/ bool trackNeedsRedraw();
  /*public*/ void trackRedrawn();
  /*public*/ LayoutBlock* getLayoutBlock();
  /*public*/ QString getConnect1Name();
  /*public*/ QString getConnect2Name();
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) throw (JmriException) override;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) throw (JmriException);
  /*public*/ int getNumberOfBezierControlPoints();
  /*public*/ QPointF getBezierControlPoint(int index);
  /*public*/ void setBezierControlPoint(/*@CheckForNull*/ QPointF p, int index);
  /*public*/ QList<QPointF> getBezierControlPoints();
  /*public*/ void setLayoutBlock(/*@CheckForNull*/ LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockByName(/*@CheckForNull*/ QString name);
  /*public*/ void scaleCoords(double xFactor, double yFactor) override;
  /*public*/ void translateCoords(double xFactor, double yFactor)override;
  /*public*/ void rotateCoords(double angleDEG)override;
  /*public*/ void setCoordsCenter(/*@Nonnull*/ QPointF newCenterPoint) override;
  /*public*/ void updateBlockInfo();
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType) override;
  /*public*/ QRectF getBounds()override;

  // initialization instance variables (used when loading a LayoutEditor)
  /*public*/ QString tConnect1Name = "";
  /*public*/ QString tConnect2Name = "";

  /*public*/ QString tLayoutBlockName = "";

  /**
   * Maximum length of the bumper decoration.
   */
  /*public*/ static /*final*/  /*const*/ int MAX_BUMPER_LENGTH;// = 40;
  /*public*/ static /*final*/  /*const*/ int MIN_BUMPER_LENGTH;// = 8;
  /*public*/ static /*final*/  /*const*/ int MAX_BUMPER_WIDTH;// = 10;
  /*public*/ static /*final*/  /*const*/ int MIN_BUMPER_WIDTH;// = 1;


  /*public*/ void dispose();
  /*public*/ void remove();
  /*public*/ bool isActive();
  /*public*/ bool canRemove() override;
  /*public*/ QList<QString> getPointReferences(HitPointType::TYPES type, LayoutTrack* conn);
  /*public*/ void splitTrackSegment();
  /*public*/ bool isShowConstructionLines();
  /*public*/ void hideConstructionLines(int hide);
  /*public*/ bool hideConstructionLines();
  /*public*/ static /*final*/ const int SHOWCON = 0x01;
  /*public*/ static /*final*/ const int HIDECON = 0x02;     // flag set on a segment basis.
  /*public*/ static /*final*/ const int HIDECONALL = 0x04;  // Used by layout editor for hiding all

  /*public*/ int showConstructionLine = SHOWCON;
  /*public*/ QPointF getTmpPt1();
  /*public*/ QPointF getTmpPt2();
  /*public*/ void setTmpPt1(QPointF Pt1);
  /*public*/ void setTmpPt2(QPointF Pt2);
  /*public*/ double getCX();
  /*public*/ void setCX(double CX);
  /*public*/ double getCY();
  /*public*/ void setCY(double CY);
  /*public*/ double getCW();
  /*public*/ void setCW(double CW);
  /*public*/ double getCH();
  /*public*/ void setCH(double CH);
  /*public*/ double getStartAdj();
  /*public*/ void setStartAdj(double startAdj);
  // this is the center of the track segment (it is "on" the track segment)
  /*public*/ double getCentreSegX();
  /*public*/ void setCentreSegX(double x);
  /*public*/ double getCentreSegY();
  /*public*/ void setCentreSegY(double y);
  /*public*/ QPointF getCentreSeg();
  /*public*/ void setCentreSeg(QPointF p);
  /*public*/ double getCentreX();
  /*public*/ void setCentreX(double x);
  /*public*/ double getCentreY();
  /*public*/ void setCentreY(double y);
  /*public*/ QPointF getCentre();
  /*public*/ double getTmpAngle();
  /*public*/ void setTmpAngle(double a);
  /*public*/ QPointF getCoordsCenterCircle();
  /*public*/ void setCoordsCenterCircle(QPointF p);
  /*public*/ double getChordLength();
  /*public*/ void setChordLength(double chord);
  /*public*/ void reCheckBlockBoundary() override;
  /*public*/ bool hasDecorations();
  /*public*/ QMap<QString, QString> *getDecorations();
  /*public*/ void setDecorations(/*@Nonnull*/ QMap<QString, QString> *decorations);
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
  /*public*/ QColor getArrowColor();
  /*public*/ void setArrowColor(QColor newVal);
  /*public*/ int getArrowLineWidth();
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
  /*public*/ QColor getBridgeColor();
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
  /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() override;
  /*public*/ bool checkForUnAssignedBlocks() override;
  /*public*/ void checkForNonContiguousBlocks(
          /*@Nonnull*/ QMap<QString, QList<QSet<QString>*>*> blockNamesToTrackNameSetsMap) override;
  /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/QString blockName,
          /*@Nonnull*/ QSet<QString>* TrackNameSet) override;
  /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock) override;

 private:
  // persistent instances variables (saved between sessions)
  /*private*/ bool dashed = false;

  /*private*/ bool arc = false;
  /*private*/ bool circle = false;
  /*private*/ bool flip = false;
  /*private*/ double angle = 0.0;

  /*private*/ bool changed = false;
  /*private*/ bool bezier = false;

  // for Bezier
  /*private*/ /*final*/ QList<QPointF> bezierControlPoints = QList<QPointF>(); // list of control point displacements

  // temporary reference to the Editor that will eventually be part of View
  /*private*/ /*final*/ TrackSegmentEditor* editor;
  /*final*/ /*private*/ TrackSegment* trackSegment;
  /*private*/ QMenu* popupMenu = nullptr;
  /*private*/ /*final*/ JCheckBoxMenuItem* mainlineCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Mainline"), this);
  /*private*/ /*final*/ JCheckBoxMenuItem* hiddenCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Hidden"), this);
  /*private*/ /*final*/ JCheckBoxMenuItem* dashedCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Dashed"),this);
  /*private*/ /*final*/ JCheckBoxMenuItem* flippedCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Flipped"),this);

  /*private*/ static /*final*/  /*const*/ int MAX_ARROW_LINE_WIDTH;// = 5;
  /*private*/ static /*final*/  /*const*/ int MAX_ARROW_LENGTH;// = 60;
  /*private*/ static /*final*/  /*const*/ int MAX_ARROW_GAP;// = 40;

  /*private*/ static /*final*/  /*const*/ int MAX_BRIDGE_LINE_WIDTH;// = 5;
  /*private*/ static /*final*/  /*const*/ int MIN_BRIDGE_LINE_WIDTH;// = 1;

  /*private*/ static /*final*/  /*const*/ int MAX_BRIDGE_APPROACH_WIDTH;// = 100;
  /*private*/ static /*final*/  /*const*/ int MIN_BRIDGE_APPROACH_WIDTH;// = 8;

  /*private*/ static /*final*/  /*const*/ int MAX_BRIDGE_DECK_WIDTH;// = 80;
  /*private*/ static /*final*/  /*const*/ int MIN_BRIDGE_DECK_WIDTH;// = 6;

  /*private*/ static /*final*/  /*const*/ int MAX_BUMPER_LINE_WIDTH;// = 9;
  /*private*/ static /*final*/  /*const*/ int MIN_BUMPER_LINE_WIDTH;// = 1;

  /*private*/ static /*final*/  /*const*/ int MAX_TUNNEL_FLOOR_WIDTH;// = 40;
  /*private*/ static /*final*/  /*const*/ int MIN_TUNNEL_FLOOR_WIDTH;// = 4;

  /*private*/ static /*final*/  /*const*/ int MAX_TUNNEL_LINE_WIDTH;// = 9;
  /*private*/ static /*final*/  /*const*/ int MIN_TUNNEL_LINE_WIDTH;// = 1;

  /*private*/ static /*final*/  /*const*/ int MAX_TUNNEL_ENTRANCE_WIDTH;// = 80;
  /*private*/ static /*final*/  /*const*/ int MIN_TUNNEL_ENTRANCE_WIDTH;// = 1;

  static Logger* log;
  /*private*/ bool active = true;
  /*private*/ void addNumericMenuItem(/*@Nonnull*/ QMenu* menu,
          /*@Nonnull*/ QString titleKey, /*@Nonnull*/ QString toolTipKey,
          /*@Nonnull*/ Supplier<int> val,
          /*@Nonnull*/ Consumer<int> set,
          /*@CheckForNull*/ Predicate<int> predicate);
  /*private*/ void addBezierControlPointBefore(int index);
  /*private*/ void addBezierControlPointAfter(int index);
  /*private*/ void deleteBezierControlPoint(int index);
  void changeType(int choice);
  /**
   * The following are used only as a local store after a circle or arc has
   * been calculated. This prevents the need to recalculate the values each
   * time a re-draw is required.
   */
  /*private*/ QPointF pt1;
  /*private*/ QPointF pt2;
  /*private*/ double cX;
  /*private*/ double cY;
  /*private*/ double cW;
  /*private*/ double cH;
  /*private*/ double startAdj;
  // this is the center of the track segment when configured as a circle
  /*private*/ double centreX;
  /*private*/ double centreY;
  /*private*/ double tmpangle;
  /*private*/ double chordLength;
  /*private*/ QList<QPointF> getBezierPoints();
  /*private*/ int drawArrow(EditScene* g2,
                            QPointF ep,
                            double angleRAD,
                            bool dirOut,
                            int offset, QPen stroke, QGraphicsItemGroup *itemGroup);
  /*private*/ int arrowStyle = 0;
  /*private*/ bool arrowEndStart = false;
  /*private*/ bool arrowEndStop = false;
  /*private*/ bool arrowDirOut = false;
  /*private*/ QColor arrowColor = Qt::black;
  /*private*/ int arrowLineWidth = 4;
  /*private*/ int arrowLength = 4;
  /*private*/ int arrowGap = 1;
  /*private*/ bool arrowDirIn = false;
  /*private*/ bool bridgeSideRight = false;
  /*private*/ bool bridgeSideLeft = false;
  /*private*/ bool bridgeHasEntry = false;
  /*private*/ bool bridgeHasExit = false;
  /*private*/ QColor bridgeColor = Qt::black;
  /*private*/ int bridgeDeckWidth = 10;
  /*private*/ int bridgeLineWidth = 1;
  /*private*/ int bridgeApproachWidth = 4;
  /*private*/ bool bumperEndStart = false;
  /*private*/ bool bumperEndStop = false;
  /*private*/ QColor bumperColor = Qt::black;
  /*private*/ int bumperLineWidth = 3;
  /*private*/ int bumperLength = 20;
  /*private*/ bool bumperFlipped = false;
  /*private*/ void setupDefaultBumperSizes(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*private*/ bool tunnelSideRight = false;
  /*private*/ bool tunnelSideLeft = false;
  /*private*/ bool tunnelHasEntry = false;
  /*private*/ bool tunnelHasExit = false;
  /*private*/ QColor tunnelColor = Qt::black;
  /*private*/ int tunnelFloorWidth = 10;
  /*private*/ int tunnelLineWidth = 1;
  /*private*/ int tunnelEntranceWidth = 16;
  QGraphicsItemGroup* rects = nullptr;

 protected:
  /*protected*/ HitPointType::TYPES findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected)override;
  /*protected*/ void setNewConnect1(/*@CheckForNull*/ LayoutTrack* connectTrack, HitPointType::TYPES connectionType);
  /*protected*/ void setNewConnect2(/*@CheckForNull*/ LayoutTrack* connectTrack, HitPointType::TYPES connectionType);
  /*protected*/ QMenu* showPopup(/*@Nonnull*/ QGraphicsSceneMouseEvent* mouseEvent)override;
  /*protected*/ void showBezierPopUp(QGraphicsSceneMouseEvent* e, HitPointType::TYPES hitPointType);
  /*protected*/ void reCalculateTrackSegmentAngle(double x, double y);
  /*protected*/ void calculateTrackSegmentAngle();
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock)override;
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement)override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES selectedType)override;
  /*protected*/ void drawEditControls(EditScene* g2)override;
  /*protected*/ void drawTurnoutControls(EditScene* g2)override;
  /*protected*/ void drawDecorations(EditScene* g2) override;
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;

  friend class LayoutEditorComponent;
  friend class TrackSegmentViewXml;
  friend class LayoutEditor;
};

#endif // TRACKSEGMENTVIEW_H
