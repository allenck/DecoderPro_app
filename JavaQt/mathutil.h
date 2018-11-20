#ifndef MATHUTIL_H
#define MATHUTIL_H
#include <qmath.h>
#include <QPointF>
#include <QRectF>
#include <limits>


class MathUtil
{
public:
 /*public*/ static bool equals(qreal a, qreal b);
 /*public*/ static double lerp(double a, double b, double t);
 /*public*/ static QPointF lerp(QPointF p1, QPointF p2, double interpolant) ;
 /*public*/ static QPointF midpoint(QPointF p1, QPointF p2);
 /*public*/ static QPointF third(QPointF p1, QPointF p2);
 /*public*/ static QPointF fourth(QPointF p1, QPointF p2);
#if 0
 /*public*/ static double wrap(double inValue, double inMin, double inMax);
 /*public*/ static double wrapPM180(double inValue);
 /*public*/ static double wrapPM360(double inValue);
 /*public*/ static double wrap360(double inValue);
 /*public*/ static double normalizeAngle(double a);
 /*public*/ static double diffAngle(double a, double b);
#endif
 /*public*/ static double pin(double inValue, double inMin, double inMax);
 /*public*/ static double distance(QPointF p1, QPointF pt);
 /*public*/ static QRectF zeroRectangle2D();
 /*public*/ static QRectF zeroToInfinityRectangle2D();
 /*public*/ static QRectF infinityRectangle2D();
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double i);
 /*public*/ static QRectF inset(/*@Nonnull*/ QRectF r, double h, double v);
 /*public*/ static /*final*/ QPointF zeroPoint2D;// = zeroPoint2D();
// /*public*/ static /*final*/ QPointF infinityPoint2D;// = infinityPoint2D();
// /*public*/ static /*final*/ QRectF zeroRectangle2D;// = zeroRectangle2D();
// /*public*/ static /*final*/ QRectF zeroToInfinityRectangle2D;// = zeroToInfinityRectangle2D();
// /*public*/ static /*final*/ QRectF infinityRectangle2D;// = infinityRectangle2D();

private:
 MathUtil();
};

#endif // MATHUTIL_H
