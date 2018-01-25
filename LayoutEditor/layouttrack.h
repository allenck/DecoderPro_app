#ifndef LAYOUTTRACK_H
#define LAYOUTTRACK_H

#include <QObject>
#include "loggerfactory.h"
#include  <QPointF>

class LayoutTrack : public QObject
{
 Q_OBJECT
public:
 explicit LayoutTrack(QObject *parent = nullptr);
 enum CONNECTIONTYPES
 {
  // connection types
  NONE = 0,
  POS_POINT = 1,
  TURNOUT_A = 2,  // throat for RH, LH, and WYE turnouts
  TURNOUT_B = 3,  // continuing route for RH or LH turnouts
  TURNOUT_C = 4,  // diverging route for RH or LH turnouts
  TURNOUT_D = 5,  // double-crossover or single crossover only
  LEVEL_XING_A = 6,
  LEVEL_XING_B = 7,
  LEVEL_XING_C = 8,
  LEVEL_XING_D = 9,
  TRACK = 10,
  TURNOUT_CENTER = 11, // non-connection points should be last
  LEVEL_XING_CENTER = 12,
  TURNTABLE_CENTER = 13,
  LAYOUT_POS_LABEL = 14,
  LAYOUT_POS_JCOMP = 15,
  MULTI_SENSOR = 16,
  MARKER = 17,
  TRACK_CIRCLE_CENTRE = 18,
  SLIP_CENTER = 20, //
  SLIP_A = 21, // offset for slip connection points
  SLIP_B = 22, // offset for slip connection points
  SLIP_C = 23, // offset for slip connection points
  SLIP_D = 24, // offset for slip connection points
  SLIP_LEFT = 25,
  SLIP_RIGHT = 26,
  TURNTABLE_RAY_OFFSET = 50 // offset for turntable connection points
 };
 /*public*/ QPointF center;// =  QPointF(50.0, 50.0);
 /*public*/ static void setDefaultTrackColor(QColor color);
 /*public*/ bool isHidden();

 /**
  * Get the hidden state of the track element.
  *
  * @return true if hidden; false otherwise
  * @deprecated since 4.7.2; use {@link #isHidden()} instead
  */
 //@Deprecated // Java standard pattern for bool getters is "isHidden()"
 QT_DEPRECATED/*public*/ bool getHidden();
 /*public*/ void setHidden(bool hide);

signals:

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("LayoutTrack");

protected:
 /*protected*/ bool hidden;// = false;
 /*protected*/ static /*final*/ double controlPointSize;// = 3.0;   // LayoutEditor.SIZE;
 /*protected*/ static /*final*/ double controlPointSize2;// = 2.0 * controlPointSize; // LayoutEditor.SIZE2;
 /*protected*/ static QColor defaultTrackColor;// = Color.black;
 /*protected*/ QPointF rotatePoint(QPointF p, double sineRot, double cosineRot);

};

#endif // LAYOUTTRACK_H
