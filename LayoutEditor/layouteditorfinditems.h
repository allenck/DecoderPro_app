#ifndef LAYOUTEDITORFINDITEMS_H
#define LAYOUTEDITORFINDITEMS_H

#include <QObject>

class LevelXing;
class LayoutTurnout;
class NamedBean;
class LayoutBlock;
class LayoutSlip;
class LayoutTurntable;
class PositionablePoint;
class TrackSegment;
class Logger;
class LayoutEditor;
class LayoutEditorFindItems : public QObject
{
 Q_OBJECT
public:
 explicit LayoutEditorFindItems(LayoutEditor *parent = 0);
 /*public*/ TrackSegment* findTrackSegmentByName(QString name);
 /*public*/ PositionablePoint* findPositionablePointByName(QString name);
 /*public*/ LayoutTurntable* findLayoutTurntableByName(QString name);
 /*public*/ PositionablePoint* findPositionablePointAtTrackSegments(TrackSegment* tr1, TrackSegment* tr2);
 /*public*/ PositionablePoint* findPositionableLinkPoint(LayoutBlock* blk1);
 /*public*/ QList<TrackSegment*> findTrackSegmentByBlock(QString name);
 /*public*/ PositionablePoint* findPositionablePointByEastBoundSignal(QString signalName);
 /*public*/ PositionablePoint* findPositionablePointByWestBoundSignal(QString signalName) ;
 /*public*/ PositionablePoint* findPositionablePointByWestBoundBean(NamedBean* bean);
 /*public*/ PositionablePoint* findPositionablePointByEastBoundBean(NamedBean* bean);
 /*public*/ PositionablePoint* findPositionablePointByWestBoundSignalMast(QString signalMastName);
 /*public*/ PositionablePoint* findPositionablePointByBean(NamedBean* bean);
 /*public*/ LayoutTurnout* findLayoutTurnoutBySignalMast(QString signalMastName);
 /*public*/ LayoutTurnout* findLayoutTurnoutByBean(NamedBean* bean);
 /*public*/ LayoutTurnout* findLayoutTurnoutBySensor(QString sensorName);
 /*public*/ LevelXing* findLevelXingBySignalMast(QString signalMastName);
 /*public*/ LevelXing* findLevelXingBySensor(QString sensorName);
 /*public*/ LevelXing* findLevelXingByBean(NamedBean* bean) ;
 /*public*/ LayoutSlip* findLayoutSlipByBean(NamedBean* bean);
 /*public*/ LayoutSlip* findLayoutSlipBySignalMast(QString signalMastName) ;
 /*public*/ LayoutSlip* findLayoutSlipBySensor(QString sensorName) ;
 /*public*/ PositionablePoint* findPositionablePointByEastBoundSensor(QString sensorName);
 /*public*/ PositionablePoint* findPositionablePointByWestBoundSensor(QString sensorName);
 /*public*/ LayoutTurnout* findLayoutTurnoutByName(QString name);
 /*public*/ LayoutTurnout* findLayoutTurnoutByTurnoutName(QString name);
 /*public*/ LevelXing* findLevelXingByName(QString name) ;
 /*public*/ LayoutSlip* findLayoutSlipByName(QString name);

signals:

public slots:
private:
 Logger* log;
 LayoutEditor* layoutEditor;

};

#endif // LAYOUTEDITORFINDITEMS_H
