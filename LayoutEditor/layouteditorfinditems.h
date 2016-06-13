#ifndef LAYOUTEDITORFINDITEMS_H
#define LAYOUTEDITORFINDITEMS_H

#include <QObject>

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

signals:

public slots:
private:
 Logger* log;
 LayoutEditor* layoutEditor;

};

#endif // LAYOUTEDITORFINDITEMS_H
