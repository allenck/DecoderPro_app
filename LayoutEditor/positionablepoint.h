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
    //explicit PositionablePoint(QObject *parent = 0);
    /*public*/ PositionablePoint(QString id, int t, QPointF c, LayoutEditor* layoutEditor, QObject *parent = 0);

    // defined constants
    enum CONSTANTS
    {
     ANCHOR = 1,
     END_BUMPER = 2,
     EDGE_CONNECTOR = 3
    };
    /*public*/ QString toString();

    /**
     * Accessor methods
    */
    /*public*/ QString getID();
    /*public*/ int getType();
    /*public*/ TrackSegment* getConnect1();
    /*public*/ TrackSegment* getConnect2();
    /*public*/ QPointF getCoords();
    /*public*/ void setCoords(QPointF p);
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
    /*public*/ void setEastBoundSensor(QString sensorName);
    /*public*/ Sensor *getWestBoundSensor();
    /*public*/ QString getWestBoundSensorName();
    /*public*/ void setWestBoundSensor(QString sensorName);
    /*public*/ SignalMast *getEastBoundSignalMast();
    /*public*/ void setEastBoundSignalMast(QString signalMastName);
    /*public*/ SignalMast* getWestBoundSignalMast();
    /*public*/ void setWestBoundSignalMast(QString signalMastName);
    /*public*/ void removeBeanReference(NamedBean* nb);

    /**
     * Initialization method
     *   The above variables are initialized by PositionablePointXml, then the following
     *        method is called after the entire LayoutEditor is loaded to set the specific
     *        TrackSegment objects.
     */
    /*public*/ void setObjects(LayoutEditor* p);
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
    /*public*/ void removeTrackConnection (TrackSegment* track);
    /*public*/ void reCheckBlockBoundary();
    /*protected*/ int maxWidth();
    /*protected*/ int maxHeight();
    /*public*/ void mousePressed(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* e);
    /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* e);
    void invalidate(QGraphicsScene* g2);
    void draw(QGraphicsScene* g);
    /*public*/ QString getLinkEditorName();
    /*public*/ PositionablePoint* getLinkedPoint() ;
    /*public*/ QString getLinkedPointId();
    /*public*/ void setLinkedPoint(PositionablePoint* p);
    /*public*/ LayoutEditor* getLinkedEditor();
    /*public*/ QWidget* getLinkPanel();
    /*public*/ bool isDisconnected(int connectionType);
    /*public*/ bool isMainline();

signals:
    
public slots:
    void On_setSignals();
    void On_setSensors();
    void On_setSignalMasts();
    /*public*/ void updateLink();

private:
    /*private*/ PositionablePoint* instance; //null;
    /*private*/ LayoutEditor* layoutEditor; //null;

    // persistent instances variables (saved between sessions)
    ///*private*/ QString ident; //"";
    /*private*/ int type; //0;
    /*private*/ TrackSegment* connect1; //null;
    /*private*/ TrackSegment* connect2; //null;
    /*private*/ QPointF coords; //new QPointF(10.0,10.0);
//    /*private*/ QString eastBoundSignalName; //""; // signal head for east (south) bound trains
//    /*private*/ QString westBoundSignalName; //""; // signal head for west (north) bound trains
    /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
    this is so that we can keep up with moves and changes of userNames */
    /*private*/ NamedBeanHandle<Sensor*>* eastBoundSensorNamed; //null;
    /*private*/ NamedBeanHandle<Sensor*>* westBoundSensorNamed; //null;
    /*private*/ NamedBeanHandle<SignalMast*>* eastBoundSignalMastNamed;// = NULL;
    /*private*/ NamedBeanHandle<SignalMast*>* westBoundSignalMastNamed;// = NULL;
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
    QComboBox* linkPointsBox;
    QComboBox* editorCombo; // Stores with LayoutEditor or "None"
    /*private*/ void setEastBoundSignalName(/*@CheckForNull*/ QString signalHead);
    /*private*/ void setWestBoundSignalName(/*@CheckForNull*/ QString signalHead);

 Logger log;
 QMenu* popup;// = NULL;
 //QGraphicsItem* item;
 /*private*/ PositionablePoint* linkedPoint;
 JDialog* editLink;// = null;
 QList<PositionablePoint*>* pointList;

private slots:
 void on_actRemove_triggered();
 void setLink();
 void updatePointBox();

protected:
/**
 * For editing: only provides remove
 */
/*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e);
 /*protected*/ LayoutEditor* getLayoutEditor();
 /*protected*/ int getConnect1Dir();
 /*protected*/ NamedBeanHandle<SignalHead*>* signalEastHeadNamed = nullptr; // signal head for east (south) bound trains
 /*protected*/ NamedBeanHandle<SignalHead*>* signalWestHeadNamed = nullptr; // signal head for west (north) bound trains
 /*protected*/ void drawTurnoutControls(QGraphicsScene* g2);
 /*protected*/ void draw1(QGraphicsScene* g2, bool isMain, bool isBlock);
 /*protected*/ void draw2(QGraphicsScene g2, bool isMain, float railDisplacement);
 /*protected*/ void highlightUnconnected(QGraphicsScene* g2, int specificType);
 /*protected*/ /*abstract*/ virtual void drawEditControls(QGraphicsScene* g2);


friend class LayoutEditor;
friend class LoadXml;
};

#endif // POSITIONABLEPOINT_H
