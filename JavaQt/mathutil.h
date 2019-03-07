#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <qmath.h>
#include <QPointF>
#include <QRectF>
#include <limits>
#include <QPainterPath>
#include "editscene.h"

class Logger;
class MathUtil
{
public:
 /*public*/ static bool equals(qreal a, qreal b);
 /*public*/ static double lerp(double a, double b, double t);
 /*public*/ static QPointF lerp(QPointF p1, QPointF p2, double interpolant) ;
 /*public*/ static QPointF midPoint(QPointF p1, QPointF p2);
 /*public*/ static QPointF third(QPointF p1, QPointF p2);
 /*public*/ static QPointF fourth(QPointF p1, QPointF p2);
 /*public*/ static double wrap(double inValue, double inMin, double inMax);
 /*public*/ static double wrapPM180(double inValue);
 /*public*/ static double wrapPM360(double inValue);
 /*public*/ static double wrap360(double inValue);
 /*public*/ static double normalizeAngle(double a);
 /*public*/ static double diffAngle(double a, double b);
 /*public*/ static double pin(double inValue, double inMin, double inMax);
 /*public*/ static QPointF add(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF subtract(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p, double s);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p, double x, double y);
 /*public*/ static QPointF multiply(double s, /*@Nonnull*/ QPointF p);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static QPointF divide(/*@Nonnull*/ QPointF p, double s);
 /*public*/ static QPointF divide(/*@Nonnull*/ QPointF p, double x, double y);

 /*public*/ static double distance(QPointF p1, QPointF pt);
 /*public*/ static QRectF zeroRectangle2D();
 /*public*/ static QRectF zeroToInfinityRectangle2D();
 /*public*/ static QRectF infinityRectangle2D();
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double i);
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double h, double v);
 /*public*/ static QRectF scale(/*@Nonnull*/ QRectF r, double s);
 /*public*/ static /*final*/ QPointF zeroPoint2D;// = QPointF();
// /*public*/ static /*final*/ QPointF infinityQPointF;// = infinityQPointF();
// /*public*/ static /*final*/ QRectF zeroRectangle2D;// = zeroRectangle2D();
// /*public*/ static /*final*/ QRectF zeroToInfinityRectangle2D;// = zeroToInfinityRectangle2D();
// /*public*/ static /*final*/ QRectF infinityRectangle2D;// = infinityRectangle2D();
 /*public*/ static double computeAngleRAD(/*@Nonnull*/ QPointF p);
 /*public*/ static double computeAngleDEG(/*@Nonnull*/ QPointF p);
 /*public*/ static double computeAngleRAD(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static double computeAngleDEG(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static QPointF orthogonal(/*@Nonnull*/ QPointF p);
 /*public*/ static QPointF normalize(/*@Nonnull*/ QPointF p);
 /*public*/ static QPointF normalize(/*@Nonnull*/ QPointF p, double length);
 /*public*/ static double length(/*@Nonnull*/ QPointF p);
 /*public*/ static double drawBezier(
   EditScene* g2,
   /*@Nonnull*/ QPointF p0,
   /*@Nonnull*/ QPointF p1,
   /*@Nonnull*/ QPointF p2,
   /*@Nonnull*/ QPointF p3);
 /*public*/ static QRect rectangle2DToRectangle(/*@Nonnull*/ QRectF r);

private:
 MathUtil();
 /*private*/ static double plotBezier(
         QPainterPath path,
         /*@Nonnull*/ QPointF p0,
         /*@Nonnull*/ QPointF p1,
         /*@Nonnull*/ QPointF p2,
         /*@Nonnull*/ QPointF p3,
         int depth,
         double displacement);
 /*private*/ static bool bezier1st;// = false;
 static Logger* log;

};

#endif // MATHUTIL_H
