#ifndef LEVELXINGVIEW_H
#define LEVELXINGVIEW_H
#include "layouttrackview.h"
#include "levelxing.h"
#include "levelxingeditor.h"

class LevelXingView : public LayoutTrackView
{
  Q_OBJECT
 public:
//  /*public*/ enum Geometry {
//      POINTA, POINTB, POINTC, POINTD
//  };
  /*public*/ LevelXingView(/*@Nonnull*/  LevelXing* xing, /*@Nonnull*/  LayoutEditor* layoutEditor);
  /*public*/ LevelXingView(/*@Nonnull*/  LevelXing* xing, /*@Nonnull*/  QPointF c, /*@Nonnull*/  LayoutEditor* layoutEditor);
  /*public*/ LevelXing* getLevelXing();

  // this should only be used for debugging
  //@Override
  /*public*/ QString toString();
  /*public*/ QString getBlockNameAC();
  /*public*/ QString getBlockNameBD();
  /*public*/ SignalHead* getSignalHead(/*LevelXing::Geometry*/int loc);
  /*public*/ SignalMast* getSignalMast(/*LevelXing::Geometry*/ int loc);
  /*public*/ Sensor* getSensor(/*LevelXing::Geometry*/ int loc);
  /*public*/ QString getSignalAName();
  /*public*/ void setSignalAName(QString signalHead);
  /*public*/ QString getSignalBName();
  /*public*/ void setSignalBName(QString signalHead);
  /*public*/ QString getSignalCName();
  /*public*/ void setSignalCName(QString signalHead);
  /*public*/ QString getSignalDName();
  /*public*/ void setSignalDName(QString signalHead);
  /*public*/ void removeBeanReference(NamedBean* nb);
  /*public*/ QString getSignalAMastName();
  /*public*/ SignalMast* getSignalAMast();
  /*public*/ void setSignalAMast(QString signalMast);
  /*public*/ QString getSignalBMastName();
  /*public*/ SignalMast* getSignalBMast();
  /*public*/ void setSignalBMast(QString signalMast);
  /*public*/ QString getSignalCMastName();
  /*public*/ SignalMast* getSignalCMast();
  /*public*/ void setSignalCMast(QString signalMast);
  /*public*/ QString getSignalDMastName();
  /*public*/ SignalMast* getSignalDMast();
  /*public*/ void setSignalDMast(QString signalMast);
  /*public*/ QString getSensorAName();
  /*public*/ Sensor* getSensorA();
  /*public*/ void setSensorAName(QString sensorName);
  /*public*/ QString getSensorBName();
  /*public*/ Sensor* getSensorB();
  /*public*/ void setSensorBName(QString sensorName);
  /*public*/ QString getSensorCName();
  /*public*/ Sensor* getSensorC();
  /*public*/ void setSensorCName(QString sensorName);
  /*public*/ QString getSensorDName();
  /*public*/ Sensor* getSensorD();
  /*public*/ void setSensorDName(QString sensorName);
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ override;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ override;
  /*public*/ LayoutTrack* getConnectA();
  /*public*/ LayoutTrack* getConnectB();
  /*public*/ LayoutTrack* getConnectC();
  /*public*/ LayoutTrack* getConnectD() ;
  /*public*/ void setConnectA(LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectB(LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectC(LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ void setConnectD(LayoutTrack* o, HitPointType::TYPES type);
  /*public*/ LayoutBlock* getLayoutBlockAC();
  /*public*/ LayoutBlock* getLayoutBlockBD();
  /*public*/ QPointF getCoordsA();
  /*public*/ QPointF getCoordsB() ;
  /*public*/ QPointF getCoordsC();
  /*public*/ QPointF getCoordsD();
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType) override;
  /*public*/ QRectF getBounds() override;
  /*public*/ bool isMainlineAC();
  /*public*/ bool isMainlineBD();
  /*public*/ void setCoordsA(QPointF p);
  /*public*/ void setCoordsB(QPointF p);
  /*public*/ void setCoordsC(QPointF p);
  /*public*/ void setCoordsD(QPointF p) ;
  /*public*/ void scaleCoords(double xFactor, double yFactor) override;
  /*public*/ void translateCoords(double xFactor, double yFactor) override;
  /*public*/ void rotateCoords(double angleDEG) override;
  /*public*/ bool canRemove() override;
  /*public*/ void dispose();
  /*public*/ void addEditPopUpMenu(QAction* menu);
  /*public*/ void addViewPopUpMenu(QAction* menu);
  /*public*/ void setAdditionalEditPopUpMenu(QMenu* popup);
  /*public*/ void setAdditionalViewPopUpMenu(QMenu* popup);
  /*public*/ void reCheckBlockBoundary() override;
  /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() override;
  /*public*/ bool checkForUnAssignedBlocks() override;
  /*public*/ void checkForNonContiguousBlocks(
         /*@Nonnull*/  QMap<QString, QList<QSet<QString>*>*> blockNamesToTrackNameSetsMap) override;
  /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/  QString blockName,
         /*@Nonnull*/  QSet<QString>* TrackNameSet);
  /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock) override;


 private:
  /*private*/ QPointF dispA = QPointF(-20.0, 0.0);
  /*private*/ QPointF dispB = QPointF(-14.0, 14.0);
  static Logger* log;
  // temporary reference to the Editor that will eventually be part of View
  /*private*/ /*final*/  LevelXingEditor* editor;
  QList<QAction*> editAdditionalMenu = QList<QAction*>();
  QList<QAction*> viewAdditionalMenu = QList<QAction*>();

  /*final*/  /*private*/ LevelXing* xing;
  QMenu* popup = nullptr;

 protected:
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
  /*protected*/ void drawDecorations(EditScene* g2) override {}
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock) override;
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) override ;
  /*protected*/ void drawEditControls(EditScene* g2) override;
  /*protected*/ void drawTurnoutControls(EditScene* g2);
  /*protected*/ QMenu* showPopup(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent) override ;
  /*protected*/ HitPointType::TYPES findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) override;

};

#endif // LEVELXINGVIEW_H
