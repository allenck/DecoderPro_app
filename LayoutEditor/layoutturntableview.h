#ifndef LAYOUTTURNTABLEVIEW_H
#define LAYOUTTURNTABLEVIEW_H
#include "layouttrackview.h"
#include "layoutturntable.h"
#include "mathutil.h"

class LayoutTurntableView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ LayoutTurntableView(/*@Nonnull*/ LayoutTurntable* turntable,
              /*@Nonnull*/ QPointF c,
              /*@Nonnull*/ LayoutEditor* layoutEditor);
  /*final*/ /*public*/ LayoutTurntable* getTurntable() { return turntable; }
  /*public*/ QString toString();

  //
  // Accessor methods
  //
  /*public*/ double getRadius();
  /*public*/ void setRadius(double r) ;
  /*public*/ QString getBlockName();
  /*public*/ LayoutBlock* getLayoutBlock();
  /*public*/ void setLayoutBlock(/*@CheckForNull*/ LayoutBlock* newLayoutBlock);
  /*public*/ void setLayoutBlockByName(/*@CheckForNull*/ QString name);
  /*public*/ QRectF getBounds() override;
  /*public*/ RayTrack* addRay(double angle);
  /*public*/ TrackSegment* getRayConnectIndexed(int index);
  /*public*/ TrackSegment* getRayConnectOrdered(int i);
  /*public*/ void setRayConnect(TrackSegment* ts, int index);
  /*public*/ QList<RayTrack*> getRayTrackList();
  /*public*/ int getNumberRays();
  /*public*/ int getRayIndex(int i);
  /*public*/ double getRayAngle(int i);
  /*public*/ void setRayTurnout(int index, QString turnoutName, int state);
  /*public*/ QString getRayTurnoutName(int i);
  /*public*/ Turnout* getRayTurnout(int i);
  /*public*/ int getRayTurnoutState(int i);
  /*public*/ bool isRayDisabled(int i);
  /*public*/ void setRayDisabled(int i, bool boo);
  /*public*/ bool isRayDisabledWhenOccupied(int i);
  /*public*/ void setRayDisabledWhenOccupied(int i, bool boo);
  /*public*/ QPointF getRayCoordsIndexed(int index);
  /*public*/ QPointF getRayCoordsOrdered(int i);
  /*public*/ void setRayCoordsIndexed(double x, double y, int index);
  /*public*/ void setRayCoordsIndexed(QPointF point, int index);
  /*public*/ QPointF getCoordsForConnectionType(HitPointType::TYPES connectionType) override;
  /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ override ;
  /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/  override;
  /*public*/ bool isMainlineIndexed(int index) ;
  /*public*/ bool isMainlineOrdered(int i);
  /*public*/ void scaleCoords(double xFactor, double yFactor) override;
  /*public*/ void translateCoords(double xFactor, double yFactor)override;
  /*public*/ void rotateCoords(double angleDEG)override;
  /*public*/ QString tLayoutBlockName = "";
  /*public*/ bool isTurnoutControlled();
  /*public*/ void setTurnoutControlled(bool boo);
  /*public*/ void setPosition(int index);
  /*public*/ int getPosition();
  /*public*/ void deleteRay(RayTrack* rayTrack);
  /*public*/ void dispose();
  /*public*/ void remove();
  /*public*/ bool isActive();
  /*public*/ QList<HitPointType::TYPES> checkForFreeConnections() override;
  /*public*/ bool checkForUnAssignedBlocks()override;
  /*public*/ void checkForNonContiguousBlocks(
          /*@Nonnull*/ QMap<QString, QList<QSet<QString>*>*> blockNamesToTrackNameSetsMap) override;
  /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
          /*@Nonnull*/ QSet<QString>* TrackNameSet) override;
  /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock)override;
  /*public*/ bool canRemove() override;


 private:
  /*private*/ /*final*/ LayoutTurntableEditor* editor;
  /*final*/ /*private*/ LayoutTurntable* turntable;
  LayoutEditor* layoutEditor;
  static Logger* log;
  /*private*/ bool active = true;
  /*private*/ QMenu* rayPopup = nullptr;
  /*private*/ QMenu* popupMenu = nullptr;
  QGraphicsItemGroup* item = nullptr;
  QGraphicsItemGroup* rects = nullptr;
  QGraphicsItemGroup* circles = nullptr;
  PropertyChangeListener* mTurnoutListener = nullptr;
  QGraphicsItemGroup* itemGroup= nullptr;

 protected:
  /*protected*/ void drawTurnoutControls(EditScene *g2) override;
  /*protected*/ void reCheckBlockBoundary() override;
  /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
  /*protected*/ void drawDecorations(EditScene* g2) override;
  /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock) override;
  /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement) override;
  /*protected*/ void highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) override;
  /*protected*/ void drawEditControls(EditScene* g2) override;
  /*protected*/ void showRayPopUp(QGraphicsSceneMouseEvent* e, int index);
  /*protected*/ QMenu* showPopup(/*@Nonnull*/ QGraphicsSceneMouseEvent* mouseEvent) override;
  /*protected*/ HitPointType::TYPES findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) override;

  friend class LayoutEditor;
  friend class LayoutEditorComponent;
};

/*public*/ /*static*/ class RayTrackVisuals : QObject{
Q_OBJECT
    // /*public*/ final RayTrack track;

    // persistant instance variables
    /*private*/ double rayAngle = 0.0;

   /**
     * Get the angle for this ray.
     *
     * @return the angle for this ray
     */
    /*public*/ double getAngle() {
        return rayAngle;
    }

    /**
     * Set the angle for this ray.
     *
     * @param an the angle for this ray
     */
    /*public*/ void setAngle(double an) {
        rayAngle = MathUtil::wrapPM360(an);
    }

    /*public*/ RayTrackVisuals(RayTrack* track) {
        // this.track = track;
    }
};

#endif // LAYOUTTURNTABLEVIEW_H
