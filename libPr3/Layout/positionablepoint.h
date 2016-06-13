#ifndef POSITIONABLEPOINT_H
#define POSITIONABLEPOINT_H

#include <QObject>
#include "sensor.h"
#include "layouteditor.h"

class PositionablePoint : public QObject
{
    Q_OBJECT
public:
    //explicit PositionablePoint(QObject *parent = 0);
    /*public*/ PositionablePoint(QString id, int t, QPointF* p, LayoutEditor* myPanel,QObject *parent = 0);

    // defined constants
    /*public*/ static const int ANCHOR = 1;
    /*public*/ static const int END_BUMPER = 2;
    /**
     * Accessor methods
    */
    /*public*/ QString getID();
    /*public*/ int getType();
    /*public*/ TrackSegment* getConnect1();
    /*public*/ TrackSegment* getConnect2();
    /*public*/ QPointF* getCoords();
    /*public*/ void setCoords(QPointF* p);
    /*public*/ QString getEastBoundSignal();
    /*public*/ void setEastBoundSignal(QString signalName);
    /*public*/ QString getWestBoundSignal();
    /*public*/ void setWestBoundSignal(QString signalName);

    /*public*/ QString getEastBoundSensor();
    /*public*/ void setEastBoundSensor(QString sensorName);
    /*public*/ QString getWestBoundSensor();
    /*public*/ void setWestBoundSensor(QString sensorName);
    /*public*/ QString getEastBoundSignalMast();
    /*public*/ void setEastBoundSignalMast(QString signalMastName);
    /*public*/ QString getWestBoundSignalMast();
    /*public*/ void setWestBoundSignalMast(QString signalMastName);


signals:
    
public slots:
private:
    /*private*/ PositionablePoint* instance; //null;
    /*private*/ LayoutEditor* layoutEditor; //null;

    // persistent instances variables (saved between sessions)
    /*private*/ QString ident; //"";
    /*private*/ int type; //0;
    /*private*/ TrackSegment* connect1; //null;
    /*private*/ TrackSegment* connect2; //null;
    /*private*/ QPointF* coords; //new QPointF(10.0,10.0);
    /*private*/ QString eastBoundSignalName; //""; // signal head for east (south) bound trains
    /*private*/ QString westBoundSignalName; //""; // signal head for west (north) bound trains
    /* We use a namedbeanhandle for the the sensors, even though we only store the name here,
    this is so that we can keep up with moves and changes of userNames */
    /*private*/ NamedBeanHandle<Sensor*>* eastBoundSensorNamed; //null;
    /*private*/ NamedBeanHandle<Sensor*> westBoundSensorNamed; //null;
    /*private*/ QString eastBoundSignalMastName; //"";
    /*private*/ QString westBoundSignalMastName; //"";

};

#endif // POSITIONABLEPOINT_H
