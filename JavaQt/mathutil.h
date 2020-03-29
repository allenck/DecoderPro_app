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
 /*public*/ static double granulize(double v, double g);
 /*public*/ static QPointF granulize(/*@Nonnull*/ QPointF p, double gH, double gV);
 /*public*/ static QPointF granulize(/*@Nonnull*/ QPointF p, double g);
 /*public*/ static QPointF center(/*@Nonnull*/ QRectF r);
 /*public*/ static QPointF midPoint(QRectF r);
 /*public*/ static QPointF midPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QRectF offset(/*@Nonnull*/ QRectF r, double x, double y);
 /*public*/ static QPointF oneThirdPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF twoThirdsPoint(QPointF p1, QPointF p2);
 /*public*/ static QPointF oneFourthPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF threeFourthsPoint(/*@Nonnull*/ QPointF pA,/* @Nonnull*/ QPointF pB);
 /*public*/ static double wrap(double inValue, double inMin, double inMax);
 /*public*/ static double wrapPM180(double inValue);
 /*public*/ static double wrapPM360(double inValue);
 /*public*/ static double wrap360(double inValue);
 /*public*/ static double normalizeAngle(double a);
 /*public*/ static double diffAngleDEG(double a, double b);
 /*public*/ static double diffAngleRAD(double a, double b);
 /*public*/ static double absDiffAngleDEG(double a, double b);
 /*public*/ static double absDiffAngleRAD(double a, double b);
 /*public*/ static QPointF max(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static double pin(double inValue, double inMin, double inMax);
 /*public*/ static QPointF add(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF subtract(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p, double s);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p, double x, double y);
 /*public*/ static QPointF multiply(double s, /*@Nonnull*/ QPointF p);
 /*public*/ static QPointF multiply(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static QPointF divide(/*@Nonnull*/ QPointF p, double s);
 /*public*/ static QPointF divide(/*@Nonnull*/ QPointF p, double x, double y);
 /*public*/ static QPointF offset(/*@Nonnull*/ QPointF p, double x, double y) ;
 /*public*/ static QPointF rotateRAD(double x, double y, double a);
 /*public*/ static QPointF rotateDEG(double x, double y, double a);
 /*public*/ static QPointF rotateRAD(/*@Nonnull*/ QPointF p, double a);
 /*public*/ static QPointF rotateDEG(/*@Nonnull*/ QPointF p, double a);
 /*public*/ static QPointF rotateRAD(/*@Nonnull*/ QPointF p, /*@Nonnull*/ QPointF c, double aRAD);
 /*public*/ static QPointF rotateDEG(/*@Nonnull*/ QPointF p, /*@Nonnull*/ QPointF c, double aDEG);

 /*public*/ static double distance(QPointF p1, QPointF pt);
 /*public*/ static QRectF zeroRectangle2D();
 /*public*/ static QRectF zeroToInfinityRectangle2D();
 /*public*/ static QRectF infinityRectangle2D();
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double i);
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double h, double v);
 /*public*/ static QRectF scale(/*@Nonnull*/ QRectF r, double s);
 /*public*/ static /*final*/ QPointF zeroPoint2D;// = QPointF();
 /*public*/ static QPointF infinityPoint2D();
 /*public*/ static QPointF pointToPoint2D(/*@Nonnull */QPoint p);
 /*public*/ static QPoint point2DToPoint(/*@Nonnull*/ QPointF p);
 /*public*/ static bool isEqualToZeroPoint2D(/*@Nonnull*/ QPointF p);
 /*public*/ static double computeAngleRAD(/*@Nonnull*/ QPointF p);
 /*public*/ static double computeAngleDEG(/*@Nonnull*/ QPointF p);
 /*public*/ static double computeAngleRAD(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static double computeAngleDEG(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2);
 /*public*/ static QPointF orthogonal(/*@Nonnull*/ QPointF p);
 /*public*/ static QPointF normalize(/*@Nonnull*/ QPointF p);
 /*public*/ static QPointF normalize(/*@Nonnull*/ QPointF p, double length);
 /*public*/ static double length(/*@Nonnull*/ QPointF p);
 /*public*/ static QPainterPath drawBezier(/*@Nonnull*/ QPointF p0,
   /*@Nonnull*/ QPointF p1,
   /*@Nonnull*/ QPointF p2,
   /*@Nonnull*/ QPointF p3);
 /*public*/ static QPainterPath drawBezier(/*@Nonnull*/ QVector<QPointF> p,
             double displacement);
 /*public*/ static QRect rectangle2DToRectangle(/*@Nonnull*/ QRectF r);
 /*public*/ static QPainterPath drawBezier(/*@Nonnull*/ QVector<QPointF> p);
 /*public*/ static QRectF rectangleAtPoint(/*@Nonnull*/ QPointF p, double width, double height);

private:
 MathUtil();
 /*private*/ static double plotBezier(QPainterPath &path,
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
