#ifndef LAYOUTSLIPVIEW_H
#define LAYOUTSLIPVIEW_H
#include "layoutturnoutview.h"
#include "layoutslip.h"

class LayoutSlipView : public LayoutTurnoutView
{
  Q_OBJECT
 public:
  /*public*/ LayoutSlipView(/*@Nonnull*/  LayoutSlip* slip,
              QPointF c, double rot,
              /*@Nonnull*/  LayoutEditor* layoutEditor);
  /*public*/ int currentState = UNKNOWN;
  /*public*/ LayoutSlip* getSlip();
  /*public*/ QString toString();
  /*public*/ LayoutTurnout::TurnoutType getSlipType();
  /*public*/ int getSlipState();
  /*public*/ QString getTurnoutBName();
  /*public*/ Turnout* getTurnoutB();
  /*public*/ void setTurnoutB(/*@CheckForNull*/   QString tName);
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ override;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/  LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ override;  /*public*/ QString getDisplayName();
  /*public*/ void toggleState(HitPointType::TYPES selectedPointType);
  /*public*/ QPointF getCoordsA() override;
  /*public*/ QPointF getCoordsB() override;
  /*public*/ QPointF getCoordsC() override;
  /*public*/ QPointF getCoordsD() override;
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType)override;
  /*public*/ QRectF getBounds() override;
  /*public*/ void updateBlockInfo() override;
  /*public*/ void setCoordsCenter(/*@Nonnull*/  QPointF p) ;
  /*public*/ void setCoordsA(/*@Nonnull*/  QPointF p) override;
  /*public*/ void setCoordsB(/*@Nonnull*/  QPointF p) override;
  /*public*/ void setCoordsC(/*@Nonnull*/  QPointF p) override;
  /*public*/ void setCoordsD(/*@Nonnull*/  QPointF p) override;
  //@Override
  /*public*/ QList<QString> getBlockBoundaries() override;
  /*public*/ void dispose()override;
  /*public*/ void remove() override;
  /*public*/ int getTurnoutState(/*@Nonnull*/  Turnout* turn, int state);
  /*public*/ int getTurnoutState(int state);
  /*public*/ int getTurnoutBState(int state);
  /*public*/ void setTurnoutStates(int state, /*@Nonnull*/  QString turnStateA, /*@Nonnull*/  QString turnStateB);
  /*public*/ void reCheckBlockBoundary() override;
  /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() override;

 private:
  static Logger* log;
  /*final*/ /*private*/ LayoutSlip* slip;
  /*private*/ QString getSlipStateString(int slipState);
  /*private*/ bool isOccupied();
  QPointF getCoordsLeft();
  QPointF getCoordsRight();
  QMenu* popup = nullptr;
  /*private*/ bool isTurnoutInconsistent();
  QGraphicsItemGroup* itemGroup = nullptr;

 protected:
  /*protected*/ HitPointType::TYPES findHitPointType(/*@Nonnull*/  QPointF hitPoint, bool useRectangles, bool requireUnconnected);
  /*protected*/ QMenu* showPopup(/*@CheckForNull*/  QGraphicsSceneMouseEvent* mouseEvent) override;
  /*protected*/ void draw1(EditScene* g2, bool drawMain, bool isBlock)override;
  /*protected*/ void draw2(EditScene* g2, bool drawMain, float railDisplacement)override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) override;
  /*protected*/ void drawTurnoutControls(EditScene* g2) override;
  /*protected*/ int getConnectivityStateForLayoutBlocks(
          /*@CheckForNull*/  LayoutBlock* thisLayoutBlock,
          /*@CheckForNull*/  LayoutBlock* prevLayoutBlock,
          /*@CheckForNull*/  LayoutBlock* nextLayoutBlock,
          bool suppress) override;
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
 friend class LayoutSlipView;
};

#endif // LAYOUTSLIPVIEW_H
