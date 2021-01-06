#ifndef HITPOINTTYPE_H
#define HITPOINTTYPE_H

#include <QObject>

class HitPointType : public QObject
{
  Q_OBJECT
 public:
  enum TYPES
  {
   NONE,           //     0
   POS_POINT,      //     1
   TURNOUT_A,      //     2    throat for RH, LH, and WYE turnouts
   TURNOUT_B,      //     3    continuing route for RH and LH turnouts
   TURNOUT_C,      //     4    diverging route for RH and LH turnouts
   TURNOUT_D,      //     5    4th route for crossovers
   LEVEL_XING_A,   //     6
   LEVEL_XING_B,   //     7
   LEVEL_XING_C,   //     8
   LEVEL_XING_D,   //     9
   TRACK,          //     10
   TURNOUT_CENTER,   //     11    non-connection points should be last
   LEVEL_XING_CENTER,  //     12
   TURNTABLE_CENTER,   //     13
   LAYOUT_POS_LABEL,   //     14
   LAYOUT_POS_JCOMP,   //     15
   MULTI_SENSOR,   //     16
   MARKER,         //     17
   TRACK_CIRCLE_CENTRE,   //     18
   UNUSED_19,      //     19
   SLIP_CENTER,    //     20   should be @Deprecated (use SLIP_LEFT & SLIP_RIGHT instead)
   SLIP_A,         //     21
   SLIP_B,         //     22
   SLIP_C,         //     23
   SLIP_D,         //     24
   SLIP_LEFT,      //     25
   SLIP_RIGHT,     //     26
   UNUSED_27,      //     27
   UNUSED_28,                //     28
   UNUSED_29,                //     29
   BEZIER_CONTROL_POINT_0,   //     30    offset for TrackSegment Bezier control points , minimum)
   BEZIER_CONTROL_POINT_1,   //     31     \"
   BEZIER_CONTROL_POINT_2,   //     32      \"
   BEZIER_CONTROL_POINT_3,   //     33       \"
   BEZIER_CONTROL_POINT_4,   //     34        } -- DON'T USE THESE; PLACEHOLDERS ONLY
   BEZIER_CONTROL_POINT_5,   //     35       /
   BEZIER_CONTROL_POINT_6,   //     36      /
   BEZIER_CONTROL_POINT_7,   //     37     /
   BEZIER_CONTROL_POINT_8,   //     38    offset for TrackSegment Bezier control points , maximum)
   SHAPE_CENTER,    //     39
   SHAPE_POINT_0,   //     40    offset for Shape points, minimum)
   SHAPE_POINT_1,   //     41     \"
   SHAPE_POINT_2,   //     42      \"
   SHAPE_POINT_3,   //     43       \"
   SHAPE_POINT_4,   //     44        \ __ DON'T USE THESE; PLACEHOLDERS ONLY
   SHAPE_POINT_5,   //     45        /
   SHAPE_POINT_6,   //     46       /
   SHAPE_POINT_7,   //     47      /
   SHAPE_POINT_8,   //     48     /
   SHAPE_POINT_9,   //     49    offset for Shape points ,   //     maximum)
   TURNTABLE_RAY_0,   //     50    offset for turntable connection points ,   //     minimum)
   TURNTABLE_RAY_1,   //     51    \"
   TURNTABLE_RAY_2,   //     52     \"
   TURNTABLE_RAY_3,   //     53      \"
   TURNTABLE_RAY_4,   //     54       \"
   TURNTABLE_RAY_5,   //     55        \"
   TURNTABLE_RAY_6,   //     56         \"
   TURNTABLE_RAY_7,   //     57          |
   TURNTABLE_RAY_8,   //     58          |
   TURNTABLE_RAY_9,   //     59          |
   TURNTABLE_RAY_10,   //     60         |
   TURNTABLE_RAY_11,   //     61         |
   TURNTABLE_RAY_12,   //     62         |
   TURNTABLE_RAY_13,   //     63         |
   TURNTABLE_RAY_14,   //     64         |
   TURNTABLE_RAY_15,   //     65         |
   TURNTABLE_RAY_16,   //     66         |
   TURNTABLE_RAY_17,   //     67         |
   TURNTABLE_RAY_18,   //     68         |
   TURNTABLE_RAY_19,   //     69         |
   TURNTABLE_RAY_20,   //     70         |
   TURNTABLE_RAY_21,   //     71         |
   TURNTABLE_RAY_22,   //     72         |
   TURNTABLE_RAY_23,   //     73         |
   TURNTABLE_RAY_24,   //     74         |
   TURNTABLE_RAY_25,   //     75         |
   TURNTABLE_RAY_26,   //     76         |
   TURNTABLE_RAY_27,   //     77         |
   TURNTABLE_RAY_28,   //     78         |
   TURNTABLE_RAY_29,   //     79         |
   TURNTABLE_RAY_30,   //     80         |
   TURNTABLE_RAY_31,   //     81         |
   TURNTABLE_RAY_32,   //     82         |
   TURNTABLE_RAY_33,   //     83         |
   TURNTABLE_RAY_34,   //     84         |
   TURNTABLE_RAY_35,   //     85         |
   TURNTABLE_RAY_36,   //     86         |
   TURNTABLE_RAY_37,   //     87         |
   TURNTABLE_RAY_38,   //     88         |
   TURNTABLE_RAY_39,   //     89         |
   TURNTABLE_RAY_40,   //     90         |
   TURNTABLE_RAY_41,   //     91         |
   TURNTABLE_RAY_42,   //     92         |
   TURNTABLE_RAY_43,   //     93         |
   TURNTABLE_RAY_44,   //     94         |
   TURNTABLE_RAY_45,   //     95         | -- DON'T USE THESE; PLACEHOLDERS ONLY
   TURNTABLE_RAY_46,   //     96         |
   TURNTABLE_RAY_47,   //     97         |
   TURNTABLE_RAY_48,   //     98         |
   TURNTABLE_RAY_49,   //     99         |
   TURNTABLE_RAY_50,   //     100         |
   TURNTABLE_RAY_51,   //     101         |
   TURNTABLE_RAY_52,   //     102         |
   TURNTABLE_RAY_53,   //     103         |
   TURNTABLE_RAY_54,   //     104         |
   TURNTABLE_RAY_55,   //     105         |
   TURNTABLE_RAY_56,   //     106         |
   TURNTABLE_RAY_57,   //     107         |
   TURNTABLE_RAY_58,   //     108        /
   TURNTABLE_RAY_59,   //     109       /
   TURNTABLE_RAY_60,   //     110      /
   TURNTABLE_RAY_61,   //     111     /
   TURNTABLE_RAY_62,   //     112    /
   TURNTABLE_RAY_63   //     113
  };
  /*public*/ static /*final*/ int NUM_SHAPE_POINTS;// = 10;
  /*public*/ static /*final*/ int NUM_BEZIER_CONTROL_POINTS;// = 9;
 signals:

 public slots:
 protected:  explicit HitPointType(QObject *parent = nullptr);

  /*protected*/ static bool isConnectionHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isControlHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isTurnoutHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isSlipHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isBezierHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isLevelXingHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isTurntableRayHitType(HitPointType::TYPES hitType);
  /*protected*/ static bool isPopupHitType(HitPointType::TYPES hitType);
//  /*protected*/ int turntableTrackIndex();
  /*protected*/ static HitPointType turntableTrackIndexedValue(int i);
  /*protected*/ static QVector<HitPointType::TYPES> turntableValues();
//  /*protected*/ int shapePointIndex();
  /*protected*/ static int shapePointIndexedValue(int i);
  /*protected*/ static QVector<HitPointType::TYPES> shapePointValues();
  /*protected*/ static bool isShapePointOffsetHitPointType(HitPointType::TYPES t);
//  /*protected*/ int bezierPointIndex();
  /*protected*/ static int bezierPointIndexedValue(int i);

};

#endif // HITPOINTTYPE_H
