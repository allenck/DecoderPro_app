#ifndef POSITIONABLEPOINTVIEW_H
#define POSITIONABLEPOINTVIEW_H
#include "layouttrackview.h"
#include "positionablepoint.h"

class PositionablePointView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ PositionablePointView(/*@Nonnull*/  PositionablePoint* point,
          QPointF c,
          /*@Nonnull*/  LayoutEditor* layoutEditor);
  // initialization instance variables (used when loading a LayoutEditor)
  /*public*/ QString trackSegment1Name = "";
  /*public*/ QString trackSegment2Name = "";
  /*public*/ PositionablePoint* getPoint();

  // this should only be used for debugging...
  //@Override
  /*public*/ QString toString();
  /*public*/ int getType();
  /*public*/ void setType(int newType);
  /*public*/ TrackSegment* getConnect1();
  /*public*/ TrackSegment* getConnect2();
  /*public*/ QString getLinkedEditorName();
  /*public*/ LayoutEditor* getLinkedEditor();
  /*public*/ PositionablePoint* getLinkedPoint();
  /*public*/ void removeLinkedPoint();
  /*public*/ QString getLinkedPointId();
  /*public*/ void setLinkedPoint(PositionablePoint* p);
  /*public*/ void scaleCoords(double xFactor, double yFactor) override;
  /*public*/ void translateCoords(double xFactor, double yFactor) override;
  /*public*/ void rotateCoords(double angleDEG)override;
  /*public*/ QRectF getBounds() override;
  /*public*/ QString getEastBoundSignal();
  /*public*/ SignalHead* getEastBoundSignalHead();
  /*public*/ void setEastBoundSignal(QString signalName);
  /*public*/ QString getWestBoundSignal();
  /*public*/ SignalHead* getWestBoundSignalHead();
  /*public*/ void setWestBoundSignal(QString signalName);
  /*public*/ QString getEastBoundSensorName();
  /*public*/ Sensor* getEastBoundSensor();
  /*public*/ void setEastBoundSensor(QString sensorName);
  /*public*/ QString getWestBoundSensorName();
  /*public*/ Sensor* getWestBoundSensor();
  /*public*/ void setWestBoundSensor(QString sensorName) ;
  /*public*/ QString getEastBoundSignalMastName();
  /*public*/ SignalMast* getEastBoundSignalMast();
  /*public*/ void setEastBoundSignalMast(QString signalMast);
  /*public*/ QString getWestBoundSignalMastName();
  /*public*/ SignalMast* getWestBoundSignalMast();
  /*public*/ void setWestBoundSignalMast(QString signalMast);
  /*public*/ void removeBeanReference(NamedBean* nb);
  /*public*/ bool setTrackConnection(/*@Nonnull*/  TrackSegment* track) ;
  /*public*/ bool removeTrackConnection(/*@Nonnull*/  TrackSegment* track);
  /*public*/ bool replaceTrackConnection(/*@CheckForNull*/ TrackSegment* oldTrack, /*@CheckForNull*/ TrackSegment* newTrack);
  /*public*/ void mousePressed(QGraphicsSceneMouseEvent* e);
  /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* e);
  /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* e);
  /*public*/ bool canRemove() ;
  /*public*/ QList<QString> getSegmentReferences(TrackSegment* ts);
  /*public*/ JPanel* getLinkPanel();
  /*public*/ void updateLink();
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType) override;
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) throw (JmriException) override;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) throw (JmriException) override;
  /*public*/ bool isDisconnected(HitPointType::TYPES connectionType) override;
  /*public*/ void reCheckBlockBoundary() override;
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
  /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() override;
  /*public*/ bool checkForUnAssignedBlocks() override;
  /*public*/ void checkForNonContiguousBlocks(
          /*@Nonnull*/  QMap<QString, QList<QSet<QString>*>*> blockNamesTotrackNameSetsMap) override;
  /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/  QString blockName,
          /*@Nonnull*/  QSet<QString>* trackNameSet) override;
  /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock)override;

 private:
  static Logger* log;
  /*final*/ /*private*/ PositionablePoint* positionablePoint;
  /*private*/ NamedBeanHandle<SignalMast*>* eastBoundSignalMastNamed = nullptr;
  /*private*/ NamedBeanHandle<SignalMast*>* westBoundSignalMastNamed = nullptr;
  /* We use a namedbeanhandle for the sensors, even though we only store the name here,
  this is so that we can keep up with moves and changes of userNames */
  /*private*/ NamedBeanHandle<Sensor*>* eastBoundSensorNamed = nullptr;
  /*private*/ NamedBeanHandle<Sensor*>* westBoundSensorNamed = nullptr;
  /*private*/ QList<PositionablePoint*> pointList;
  JDialog* editLink = nullptr;
  JComboBox* linkPointsBox;
  JComboBox/*<JCBHandle<LayoutEditor>>*/* editorCombo; // Stores with LayoutEditor* or "None"
  /*private*/ bool active = true;
  /*private*/ QMenu* popup = nullptr;
  // cursor location reference for this move (relative to object)
  int xClick = 0;
  int yClick = 0;
  /*private*/ void setTypeAnchor();
  /*private*/ void setTypeEndBumper();
  /*private*/ void setTypeEdgeConnector();
  /*private*/ void setEastBoundSignalName(/*@CheckForNull*/ QString signalHead);
  /*private*/ void setWestBoundSignalName(/*@CheckForNull*/ QString signalHead);
  /*private*/ NamedBeanHandle<SignalMast*>* getEastBoundSignalMastNamed();
  /*private*/ NamedBeanHandle<SignalMast *>* getWestBoundSignalMastNamed();
  void removeSML(SignalMast* signalMast);
  void dispose();
  /*private*/ void remove();
  void setLink();
  void updatePointBox();
  QGraphicsItem* rects = nullptr;

 protected:
  /*protected*/ NamedBeanHandle<SignalHead*>* signalEastHeadNamed = nullptr; // signal head for east (south) bound trains
  /*protected*/ NamedBeanHandle<SignalHead*>* signalWestHeadNamed = nullptr; // signal head for west (north) bound trains

  /*protected*/ LayoutEditor* getLayoutEditor();
  /*protected*/ int maxWidth();
  /*protected*/ int maxHeight();
  /*protected*/ QMenu* showPopup(/*@Nonnull*/  QGraphicsSceneMouseEvent* mouseEvent)override;
  /*protected*/ bool isActive();
  /*protected*/ int getConnect1Dir();
  /*protected*/ HitPointType::TYPES findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) override;
  /*protected*/ void drawDecorations(EditScene* g2) override;
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock)  override;
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) override;
  /*protected*/ void drawEditControls(EditScene* g2) override;
  /*protected*/ void drawTurnoutControls(EditScene* g2) override;

  friend class LayoutEditorComponent;
};

#endif // POSITIONABLEPOINTVIEW_H
