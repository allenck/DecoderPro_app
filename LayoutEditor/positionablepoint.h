#ifndef POSITIONABLEPOINT_H
#define POSITIONABLEPOINT_H

#include <QObject>
#include "sensor.h"
#include "layouteditor.h"
#include "layouteditortools.h"
#include "QGraphicsSceneMouseEvent"

class LayoutEditor;
class LayoutEditorTools;
class LIBLAYOUTEDITORSHARED_EXPORT PositionablePoint : public LayoutTrack
{
  Q_OBJECT
public:
  // defined constants
  enum PointType
  {
   NONE,
   ANCHOR = 1,
   END_BUMPER = 2,
   EDGE_CONNECTOR = 3
  };
  Q_ENUM(PointType)
  //explicit PositionablePoint(QObject *parent = 0);
    /*public*/ PositionablePoint(QString id, PointType t, LayoutEditor* layoutEditor, QObject *parent = 0);


    /*public*/ QString toString()override;

    /**
     * Accessor methods
    */
//    /*public*/ QString getID();
    /*public*/ PositionablePoint::PointType getType() const;
    /*public*/ void setType(PositionablePoint::PointType newType);
    /*public*/ TrackSegment* getConnect1() const;
    /*public*/ void setConnect1(TrackSegment* trk);
    /*public*/ TrackSegment* getConnect2() const;
    /*public*/ void setConnect2(TrackSegment* trk);
    /*public*/ TrackSegment* getConnect2Actual();
    /*public*/ void setConnect2Actual(TrackSegment* trk);
    /*public*/ QString getLinkedEditorName();
    /*public*/ PositionablePoint* getLinkedPoint();
    /*public*/ void setLinkedPoint(PositionablePoint* p);
//    /*public*/ QPointF getCoords();
//    /*public*/ void setCoords(QPointF p);
//    /*public*/ void scaleCoords(double xFactor, double yFactor) override;
//    /*public*/ void translateCoords(double xFactor, double yFactor) override;
    /*public*/ void rotateCoords(double angleDEG);
//    /*public*/ QRectF getBounds();
    /*public*/ QString getEastBoundSignalMastName();
    /*public*/ QString getEastBoundSignal();
    /*public*/ SignalHead* getEastBoundSignalHead();
    /*public*/ void setEastBoundSignal(QString signalName);
    /*public*/ QString getWestBoundSignalMastName();
    /*public*/ QString getWestBoundSignal();
    /*public*/ SignalHead* getWestBoundSignalHead();
    /*public*/ void setWestBoundSignal(QString signalName);

    /*public*/ QString getEastBoundSensorName();
    /*public*/ Sensor *getEastBoundSensor();
    /*public*/ void setEastBoundSensor(QString sensorName) const;
    /*public*/ Sensor *getWestBoundSensor();
    /*public*/ QString getWestBoundSensorName();
    /*public*/ void setWestBoundSensor(QString sensorName) const;
    /*public*/ SignalMast *getEastBoundSignalMast();
    /*public*/ void setEastBoundSignalMast(QString signalMastName) const;
    /*public*/ SignalMast* getWestBoundSignalMast();
    /*public*/ void setWestBoundSignalMast(QString signalMastName) const;
    /*public*/ void removeBeanReference(NamedBean* nb);

    /**
     * Initialization method
     *   The above variables are initialized by PositionablePointXml, then the following
     *        method is called after the entire LayoutEditor is loaded to set the specific
     *        TrackSegment objects.
     */
    /*public*/ void setObjects(LayoutEditor* p) override;
    /**
     * Setup and remove connections to track
     */
    /*public*/ bool setTrackConnection (TrackSegment* track);
    // initialization instance variables (used when loading a LayoutEditor)
    /*public*/ QString trackSegment1Name;// = "";
    /*public*/ QString trackSegment2Name;// = "";
    /**
     * Clean up when this object is no longer needed.  Should not
     * be called while the object is still displayed; see remove()
     */
    void dispose() ;
    /**
     * Removes this object from display and persistance
     */
    void remove();
    /**
     * "active" means that the object is still displayed, and should be stored.
     */
    /*public*/ bool isActive();
    /*public*/ bool removeTrackConnection (TrackSegment* track);
    /*public*/ void reCheckBlockBoundary() const override;
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* e);
//    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* e);
//    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* e);
    /*public*/ QString getLinkEditorName();
    /*public*/ PositionablePoint* getLinkedPoint() const;
    /*public*/ QString getLinkedPointId();
    /*public*/ LayoutEditor* getLinkedEditor() const;
    /*public*/ QWidget* getLinkPanel();
    /*public*/ bool isDisconnected(HitPointType::TYPES connectionType)override;
    /*public*/ bool isMainline()override;
//    /*public*/ QPointF getCoordsForConnectionType(int connectionType)override;
    /*public*/ LayoutTrack* getConnection(HitPointType::TYPES connectionType) throw (JmriException)override;
    /*public*/ void setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) throw (JmriException) override;
    /*public*/ bool replaceTrackConnection(/*@Nullable*/ TrackSegment* oldTrack,/* @Nullable */TrackSegment* newTrack);
    /*public*/ QList<HitPointType::TYPES> checkForFreeConnections()override;
    /*public*/ bool checkForUnAssignedBlocks()override;
    /*public*/ void checkForNonContiguousBlocks(
            /*@Nonnullptr*/ QMap<QString, QList<QSet<QString>*>*> blockNamesToTrackNameSetsMap)override;
    /*public*/ void collectContiguousTracksNamesInBlockNamed(/*@Nonnullptr*/ QString blockName,
            /*@Nonnullptr*/ QSet<QString>* TrackNameSet)override;
    /*public*/ void setAllLayoutBlocks(LayoutBlock* layoutBlock)override;

signals:
    
public slots:
//    void On_setSignals();
//    void On_setSensors();
//    void On_setSignalMasts();
    /*public*/ void updateLink();

private:
    static Logger* log;
    ///*private*/ PositionablePoint* instance = nullptr;
    /*private*/ LayoutEditor* layoutEditor = nullptr;

    // persistent instances variables (saved between sessions)
    ///*private*/ QString ident; //"";
    /*private*/ PositionablePoint::PointType type; //0;
    /*private*/ mutable TrackSegment* connect1; //null;
    /*private*/ mutable TrackSegment* connect2; //null;
    /*private*/ QPointF coords; //new QPointF(10.0,10.0);
//    /*private*/ QString eastBoundSignalName; //""; // signal head for east (south) bound trains
//    /*private*/ QString westBoundSignalName; //""; // signal head for west (north) bound trains
    /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
    this is so that we can keep up with moves and changes of userNames */
    /*private*/ mutable NamedBeanHandle<Sensor*>* eastBoundSensorNamed; //null;
    /*private*/ mutable NamedBeanHandle<Sensor*>* westBoundSensorNamed; //null;
    /*private*/ mutable  NamedBeanHandle<SignalMast*>* eastBoundSignalMastNamed;// = NULL;
    /*private*/ mutable  NamedBeanHandle<SignalMast*>* westBoundSignalMastNamed;// = NULL;
//    /*private*/ QString eastBoundSignalMastName; //"";
//    /*private*/ QString westBoundSignalMastName; //"";
    QString where(QGraphicsSceneMouseEvent* e);
    bool active;// = true;
    //LayoutEditorTools* tools;// = NULL;
    // cursor location reference for this move (relative to object)
    int xClick;// = 0;
    int yClick;// = 0;
    /*private*/ NamedBeanHandle<SignalMast*>* getEastBoundSignalMastNamed();
    /*private*/ NamedBeanHandle<SignalMast*>* getWestBoundSignalMastNamed();
    QComboBox* linkPointsBox = nullptr;
    QComboBox* editorCombo = nullptr; // Stores with LayoutEditor or "None"
    /*private*/ void setEastBoundSignalName(/*@CheckForNull*/ QString signalHead);
    /*private*/ void setWestBoundSignalName(/*@CheckForNull*/ QString signalHead);
    void removeSML(SignalMast* signalMast);
    /*public*/ bool canRemove() override;
    /*public*/ QList<QString> getSegmentReferences(TrackSegment* ts);
    void removeLinkedPoint();
    QGraphicsItem* rects = nullptr;
    /*private*/ void setTypeAnchor();
    /*private*/ void setTypeEndBumper();
    /*private*/ void setTypeEdgeConnector();
    /*private*/ PositionablePoint* linkedPoint;

 QMenu* popup;// = NULL;
 //QGraphicsItem* item;
 JDialog* editLink;// = null;
 QList<PositionablePoint*>* pointList = nullptr;
 void /*private*/ invalidate(EditScene * g2)override;
 void invalidateItemType(EditScene *g2);
 void draw(EditScene *g);

private slots:
 void on_actRemove_triggered();
 void setLink();
 void updatePointBox();

protected:
/**
 * For editing: only provides remove
 */
 // /*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e);
 /*protected*/ LayoutEditor* getLayoutEditor();
 /*protected*/ int getConnect1Dir() const;
 /*protected*/ NamedBeanHandle<SignalHead*>* signalEastHeadNamed = nullptr; // signal head for east (south) bound trains
 /*protected*/ NamedBeanHandle<SignalHead*>* signalWestHeadNamed = nullptr; // signal head for west (north) bound trains
 // /*protected*/ void drawTurnoutControls(EditScene* g2)override;
 /*protected*/ void draw1(EditScene* g2, bool isMain, bool isBlock, ITEMTYPE type = track);
 /*protected*/ void draw2(EditScene* g2, bool isMain, float railDisplacement, ITEMTYPE type = track);
// /*protected*/ void highlightUnconnected(EditScene* g2, int specificType);
// /*protected*/ /*abstract*/ void drawEditControls(EditScene *g2);
// /*protected*/ int findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected)override;
 /*protected*/ QList<LayoutConnectivity*> getLayoutConnectivity() override;
 /*protected*/ int maxWidth();
 /*protected*/ int maxHeight();


friend class LayoutEditor;
friend class LoadXml;
friend class LayoutEditorAuxTools;
friend class LayoutEditorTools;
friend class PositionablePointView;
};

#endif // POSITIONABLEPOINT_H
