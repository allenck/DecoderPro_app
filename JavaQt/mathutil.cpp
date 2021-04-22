#include "mathutil.h"
#include <QPainterPath>
#include "loggerfactory.h"
#include <cmath>

MathUtil::MathUtil()
{

}

/**
*
* useful math methods
*
* @author geowar Copyright 2017
*/

//@CheckReturnValue
///*public*/ final class MathUtil {

/**
 * @param a the first double
 * @param b the second double
 * @return true if a is equal to b
 */
/*public*/ /*static*/ bool MathUtil::equals(qreal a, qreal b) {
    //return (Double.doubleToLongBits(a) == Double.doubleToLongBits(b));
 return qFuzzyCompare(a,b);
}
/*public*/ /*static*/ /*final*/ QPointF MathUtil::zeroPoint2D = QPointF();
// /*public*/ /*static*/ /*final*/ QPointF infinityQPointF = MathUtil::infinityQPointF();
// /*public*/ /*static*/ /*final*/ QRectF zeroRectangle2D = MathUtil::zeroRectangle2D();
// /*public*/ /*static*/ /*final*/ QRectF zeroToInfinityRectangle2D = MathUtil::zeroToInfinityRectangle2D();
// /*public*/ /*static*/ /*final*/ QRectF infinityRectangle2D = MathUtil::infinityRectangle2D();

/**
 * compute the angle (direction in radians) for a vector
 *
 * @param p the vector (point relative to zeroQPointF)
 * @return the angle in radians
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::computeAngleRAD(/*@Nonnull*/ QPointF p) {
    return qAtan2(p.x(), p.y());
}

/**
 * compute the angle (direction in degrees) for a vector
 *
 * @param p the vector (point relative to zeroQPointF)
 * @return the angle in degrees
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::computeAngleDEG(/*@Nonnull*/ QPointF p) {
    return qRadiansToDegrees(computeAngleRAD(p));
}

/**
 * compute the angle (direction in radians) from point 1 to point 2
 * <p>
 * Note: Goes CCW from south to east to north to west, etc.
 * For JMRI subtract from PI/2 to get east, south, west, north
 *
 * @param p1 the first QPointF
 * @param p2 the second QPointF
 * @return the angle in radians
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::computeAngleRAD(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2) {
    return computeAngleRAD(subtract(p1, p2));
}

/**
 * compute the angle (direction in degrees) from point 1 to point 2
 * <p>
 * Note: Goes CCW from south to east to north to west, etc.
 * For JMRI subtract from 90.0 to get east, south, west, north
 *
 * @param p1 the first QPointF
 * @param p2 the second QPointF
 * @return the angle in degrees
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::computeAngleDEG(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2) {
    return qRadiansToDegrees(computeAngleRAD(subtract(p1, p2)));
}
//return a double between a & b for t:0 ==> a and t:1 ==> b
/*public*/ /*static*/ double MathUtil::lerp(double a, double b, double t) {
    return ((1.0 - t) * a) + (t * b);
}

//return a QPointF between a & b for t:0 ==> a and t:1 ==> b
/*public*/ /*static*/ QPointF MathUtil::lerp(QPointF p1, QPointF p2, double interpolant) {
    return  QPointF(
        lerp(p1.x(), p2.x(), interpolant),
        lerp(p1.y(), p2.y(), interpolant));
}
/**
 * Round value to granular increment.
 *
 * @param v the value to granulize
 * @param g the granularity
 * @return the value granulized to the granularity
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::granulize(double v, double g) {
    return qRound(v / g) * g;
}

/**
 * Round point to horzontal and vertical granular increments.
 *
 * @param p  the point to granulize
 * @param gH the horzontal granularity
 * @param gV the vertical granularity
 * @return the point granulized to the granularity
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::granulize(/*@Nonnull*/ QPointF p, double gH, double gV) {
    return QPointF(granulize(p.x(), gH), granulize(p.y(), gV));
}

/**
 * Round point to granulur increment.
 *
 * @param p the point to granulize
 * @param g the granularity
 * @return the point granulized to the granularity
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::granulize(/*@Nonnull*/ QPointF p, double g) {
    return granulize(p, g, g);
}
/**
 * calculate the center of the rectangle
 *
 * @param r the rectangle
 * @return the center of the rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::center(/*@Nonnull*/ QRectF r) {
    return QPointF(r.center().x(), r.center().y());
}

/**
 * calculate the midpoint of the rectangle
 *
 * @param r the rectangle
 * @return the midpoint of the rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::midPoint(/*@Nonnull*/ QRectF r) {
    return center(r);
}

/**
 * calculate the midpoint between two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the midpoint between the two points
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::midPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return lerp(pA, pB, 0.5);
}

/**
 * offset a rectangle
 *
 * @param r the rectangle
 * @param x the horzontial offset
 * @param y the vertical offset
 * @return the offset rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::offset(/*@Nonnull*/ QRectF r, double x, double y) {
    return QRectF(r.x() + x, r.y() + y, r.width(), r.height());
}

/**
 * Offset a rectangle by a single value.
 *
 * @param r the rectangle
 * @param o the offset
 * @return the offset rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::offset(/*@Nonnull*/ QRectF r, /*@Nonnull*/ QPointF o) {
    return offset(r, o.x(), o.y());
}

/**
 * calculate the point 1/3 of the way between two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the point one third of the way from pA to pB
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::oneThirdPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return lerp(pA, pB, 1.0 / 3.0);
}

// return a QPointF one third of the way from p1 to p2
/*public*/ /*static*/ QPointF MathUtil::twoThirdsPoint(QPointF p1, QPointF p2) {
    return lerp(p1, p2, 1.0 / 3.0);
}

/**
 * calculate the point 1/4 of the way between two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the point one fourth of the way from pA to pB
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::oneFourthPoint(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return lerp(pA, pB, 1.0 / 4.0);
}

/**
 * calculate the point 3/4 of the way between two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the point three fourths of the way from pA to pB
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::threeFourthsPoint(/*@Nonnull*/ QPointF pA,/* @Nonnull*/ QPointF pB) {
    return lerp(pA, pB, 3.0 / 4.0);
}

//
// Wrap a double between two values (for example +/- 180 or 0-360 degrees)
// Note: THIS IS NOT A PIN OR TRUNCATE; VALUES WRAP AROUND BETWEEN MIN & MAX
// (And yes, this works correctly with negative numbers)
//
/*public*/ /*static*/ double MathUtil::wrap(double inValue, double inMin, double inMax) {
    int valueRange = inMax - inMin;
    return inMin + ((int)(((int)(inValue - inMin) % valueRange) + valueRange) % valueRange);
}

// wrap an double between +/-180
/*public*/ /*static*/ double MathUtil::wrapPM180(double inValue) {
    return wrap(inValue, -180.0, +180.0);
}

// wrap an double between +/-360
/*public*/ /*static*/ double MathUtil::wrapPM360(double inValue) {
    return wrap(inValue, -360.0, +360.0);
}

// wrap an double between 0-360
/*public*/ /*static*/ double MathUtil::wrap360(double inValue) {
    return wrap(inValue, 0.0, +360.0);
}

// wrap an angle between 0-360
/*public*/ /*static*/ double MathUtil::normalizeAngle(double a) {
    return wrap360(a);
}

// return the absolute difference (0-180) between two angles
/*public*/ /*static*/ double MathUtil::diffAngleDEG(double a, double b) {
    return qAbs(wrapPM180(a - b));
}

/**
 * calculate the absolute difference (0-180) between two angles
 *
 * @param a the first angle
 * @param b the second angle
 * @return the absolute difference between the two angles (in degrees)
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::absDiffAngleDEG(double a, double b) {
    return qAbs(diffAngleDEG(a, b));
}
/**
 * calculate the relative difference (+/-PI) between two angles
 *
 * @param a the first angle
 * @param b the second angle
 * @return the relative difference between the two angles (in radians)
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::diffAngleRAD(double a, double b) {
    return wrap(a - b, -M_PI, +M_PI);
}

/**
 * calculate the absolute difference (0-PI) between two angles
 *
 * @param a the first angle
 * @param b the second angle
 * @return the absolute difference between the two angles (in radians)
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::absDiffAngleRAD(double a, double b) {
    return qAbs(diffAngleRAD(a, b));
}
/**
 * Get the minimum coordinates of two points.
 *
 * @param pA the first point
 * @param pB the second point
 * @return the minimum coordinates
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::min(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return  QPointF(qMin(pA.x(), pB.x()), qMin(pA.y(), pB.y()));
}

/**
 * return the maximum coordinates of two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the maximum coordinates
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::max(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return  QPointF(qMax(pA.x(), pB.x()), qMax(pA.y(), pB.y()));
}
// pin a value between min & max
/*public*/ /*static*/ double MathUtil::pin(double inValue, double inMin, double inMax) {
    return qMin(qMax(inValue, inMin), inMax);
}

/**
 * add two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the sum of the two points
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::add(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return QPointF(pA.x() + pB.x(), pA.y() + pB.y());
}
/**
 * subtract two points
 *
 * @param pA the first point
 * @param pB the second point
 * @return the difference of the two points
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::subtract(/*@Nonnull*/ QPointF pA, /*@Nonnull*/ QPointF pB) {
    return QPointF(pA.x() - pB.x(), pA.y() - pB.y());
}
/**
 * Modifies this rectangle so that it represents the smallest rectangle
 * that contains both the existing rectangle and the specified point.
 * However, if the point falls on one of the two borders which are not
 * inside the rectangle, a subsequent call to <code>contains</code> may
 * return false.
 *
 * @param newx the X coordinate of the point to add to this rectangle
 * @param newy the Y coordinate of the point to add to this rectangle
 */
 /*public*/ QRectF MathUtil::add(QRectF r, double newx, double newy)
 {
      double minx = qMin(r.x(), newx);
      double maxx = qMax(r.right(), newx);
      double miny = qMin(r.y(), newy);
      double maxy = qMax(r.bottom(), newy);
      return QRectF(minx, miny, maxx - minx, maxy - miny);
  }

 /**
  * Modifies this rectangle so that it represents the smallest rectangle
  * that contains both the existing rectangle and the specified point.
  * However, if the point falls on one of the two borders which are not
  * inside the rectangle, a subsequent call to <code>contains</code> may
  * return false.
  *
  * @param p the point to add to this rectangle
  * @throws NullPointerException if p is null
  */
  /*public*/ QRectF MathUtil::add(QRectF r, QPointF p)
  {
     return add(r, p.x(), p.y());
  }
/**
 * multiply a point times a scalar
 *
 * @param p the point
 * @param s the scalar
 * @return the point multiplied by the scalar
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::multiply(/*@Nonnull*/ QPointF p, double s) {
    return  QPointF(p.x() * s, p.y() * s);
}

/**
 * multiply a point times two scalar
 *
 * @param p the point
 * @param x the X scalar
 * @param y the Y scalar
 * @return the point multiplied by the two scalars
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::multiply(/*@Nonnull*/ QPointF p, double x, double y) {
    return QPointF(p.x() * x, p.y() * y);
}

/**
 * multiply a scalar times a point
 *
 * @param s the scalar
 * @param p the point
 * @return the point multiplied by the scalar
 */
// (again just so parameter order doesn't matter...)
/*public*/ /*static*/ QPointF MathUtil::multiply(double s, /*@Nonnull*/ QPointF p) {
    return QPointF(p.x() * s, p.y() * s);
}

/**
 * multiply a point times a point
 *
 * @param p1 the first point
 * @param p2 the second point
 * @return the first point multiplied by the second
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::multiply(/*@Nonnull*/ QPointF p1, /*@Nonnull*/ QPointF p2) {
    return multiply(p1, p2.x(), p2.y());
}

/**
 * divide a point by a scalar
 *
 * @param p the point
 * @param s the scalar
 * @return the point divided by the scalar
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::divide(/*@Nonnull*/ QPointF p, double s) {
    return  QPointF(p.x() / s, p.y() / s);
}

/**
 * divide a point by two scalars
 *
 * @param p the point
 * @param x the X scalar
 * @param y the Y scalar
 * @return the point divided by the scalar
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::divide(/*@Nonnull*/ QPointF p, double x, double y) {
    return  QPointF(p.x() / x, p.y() / y);
}

/**
 * offset a point by two scalars
 *
 * @param p the point
 * @param x the x scalar
 * @param y the y scalar
 * @return the point offset by the scalars
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::offset(/*@Nonnull*/ QPointF p, double x, double y) {
    return QPointF(p.x() + x, p.y() + y);
}

/**
 * rotate x and y coordinates (by radians)
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param a the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateRAD(double x, double y, double a) {
    double cosA = qCos(a), sinA = qSin(a);
    return QPointF(cosA * x - sinA * y, sinA * x + cosA * y);
}

/**
 * rotate x and y coordinates (by degrees)
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param a the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateDEG(double x, double y, double a) {
    return rotateRAD(x, y, qDegreesToRadians(a));
}

/**
 * rotate a point (by radians)
 *
 * @param p the point
 * @param a the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateRAD(/*@Nonnull*/ QPointF p, double a) {
    return rotateRAD(p.x(), p.y(), a);
}

/**
 * rotate a point (by degrees)
 *
 * @param p the point
 * @param a the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateDEG(/*@Nonnull*/ QPointF p, double a) {
    return rotateRAD(p, qDegreesToRadians(a));
}

/**
 * rotate a point around another point (by radians)
 *
 * @param p    the point being rotated
 * @param c    the point its being rotated around
 * @param aRAD the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateRAD(
        /*@Nonnull*/ QPointF p, /*@Nonnull*/ QPointF c, double aRAD) {
    return add(c, rotateRAD(subtract(p, c), aRAD));
}

/**
 * rotate a point around another point (by degrees)
 *
 * @param p    the point being rotated
 * @param c    the point its being rotated around
 * @param aDEG the angle (in radians)
 * @return the point rotated by the angle
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::rotateDEG(
        /*@Nonnull*/ QPointF p, /*@Nonnull*/ QPointF c, double aDEG) {
    return rotateRAD(p, c, qDegreesToRadians(aDEG));
}

/**
 * Returns the distance from this <code>QPointF</code> to a
 * specified <code>QPointF</code>.
 *
 * @param pt the specified point to be measured
 *           against this <code>QPointF</code>
 * @return the distance between this <code>QPointF</code> and
 * the specified <code>QPointF</code>.
 * @since 1.2
 */
/*public*/ /*static*/ double MathUtil::distance(QPointF p1, QPointF pt) {
    double px = pt.x() - p1.x();
    double py = pt.y() - p1.y();
    return qSqrt(px * px + py * py);
}

/**
 * @return a new rectangle {0.0, 0.0, 0.0, 0.0}
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::zeroRectangle2D() {
    return QRectF(0.0, 0.0, 0.0, 0.0);
}

/**
 * @return a new rectangle {0.0, 0.0, POSITIVE_INFINITY, POSITIVE_INFINITY}
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::zeroToInfinityRectangle2D(){
    return QRectF(0.0, 0.0, INFINITY, INFINITY);
}

/**
 * @return a new rectangle {NEGATIVE_INFINITY, NEGATIVE_INFINITY,
 *         POSITIVE_INFINITY, POSITIVE_INFINITY}
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::infinityRectangle2D() {
    return QRectF(-INFINITY, -INFINITY, INFINITY, INFINITY);
}

/**
 * @return the point {POSITIVE_INFINITY, POSITIVE_INFINITY}
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::infinityPoint2D() {
    return QPointF(INFINITY, INFINITY);
}

/**
 * Convert Point to Point2D.
 *
 * @param p the Point
 * @return the Point2D
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::pointToPoint2D(/*@Nonnull*/ QPoint p) {
    return QPointF(p.x(), p.y());
}

/**
 * Convert Point2D to Point.
 *
 * @param p the Point
 * @return the Point2D
 */
//@CheckReturnValue
/*public*/ /*static*/ QPoint MathUtil::point2DToPoint(/*@Nonnull*/ QPointF p) {
    return QPoint((int) p.x(), (int) p.y());
}

/**
 * @param p the point
 * @return true if p1 is equal to zeroPoint2D
 */
/*public*/ /*static*/ bool MathUtil::isEqualToZeroPoint2D(/*@Nonnull*/ QPointF p) {
    return p == (zeroPoint2D);
}

/**
 * inset a rectangle
 *
 * @param r the rectangle
 * @param i the inset (positive make it smaller, negative, bigger)
 * @return the inset rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::inset(/*@Nonnull*/ QRectF r, double i) {
    return QRectF(r.x() + i, r.y() + i, r.width() - (2 * i), r.height() - (2 * i));
}

/**
 * inset a rectangle
 *
 * @param r the rectangle
 * @param h the horzontial inset (positive make it smaller, negative,
 *          bigger)
 * @param v the vertical inset (positive make it smaller, negative, bigger)
 * @return the inset rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::inset(/*@Nonnull*/ QRectF r, double h, double v) {
    return QRectF(r.x() + h, r.y() + v, r.width() - (2 * h), r.height() - (2 * v));
}
/**
 * scale a rectangle
 *
 * @param r the rectangle
 * @param s the scale
 * @return the scaled rectangle
 */
//TODO: add test case
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::scale(/*@Nonnull*/ QRectF r, double s) {
    return QRectF(r.x() * s, r.y() * s, r.width() * s, r.height() * s);
}

/**
 * @param p the point
 * @return the point orthogonal to this one (relative to {0, 0})
 */
/*public*/ /*static*/ QPointF MathUtil::orthogonal(/*@Nonnull*/ QPointF p) {
    return QPointF(-p.x(), p.y());
}
/**
 * normalize a point (vector) to a length
 *
 * @param p      the point (vector)
 * @param length the length to normalize to
 * @return the normalized point (vector)
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::normalize(/*@Nonnull*/ QPointF p, double length) {
    return multiply(normalize(p), length);
}


/**
 * Convert Rectangle2D to Rectangle
 *
 * @param r the Rectangle
 * @return the Rectangle2D
 */
//@CheckReturnValue
/*public*/ /*static*/ QRect MathUtil::rectangle2DToRectangle(/*@Nonnull*/ QRectF r) {
    return QRect((int) r.x(), (int) r.y(), (int) r.width(), (int) r.height());
}

/**
 * normalize a point (vector)
 *
 * @param p the point (vector)
 * @return the normalized point (vector)
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::normalize(/*@Nonnull*/ QPointF p) {
    QPointF result = p;

    double length = MathUtil::length(p);
    if (length >= 0.001) {
        result = divide(p, length);
    }
    return result;
}
/**
 * calculate the length of a point (vector)
 *
 * @param p the point (vector)
 * @return the length of the point (vector)
 */
//@CheckReturnValue
/*public*/ /*static*/ double MathUtil::length(/*@Nonnull*/ QPointF p) {
    return hypot(p.x(), p.y());
}

/**
 * Get rectangle at point.
 *
 * @param p      the point
 * @param width  the width
 * @param height the height
 * @return the rectangle
 */
//@CheckReturnValue
/*public*/ /*static*/ QRectF MathUtil::rectangleAtPoint(/*@Nonnull*/ QPointF p, double width, double height) {
    return QRectF(p.x(), p.y(), width, height);
}
// recursive routine to plot a Bezier curve...
// (also returns distance!)
/*private*/ /*static*/ double MathUtil::plotBezier(
        QPainterPath path,
        /*@Nonnull*/ QList<QPointF> points,
        int depth,
        double displacement)
{
    int len = points.length(), idx, jdx;
    double result;

    // calculate flatness to determine if we need to recurse...
    double outer_distance = 0;
    for (idx = 1; idx < len; idx++) {
        outer_distance += distance(points[idx - 1], points[idx]);
    }
    double inner_distance = distance(points[0], points[len - 1]);
    double flatness = outer_distance / inner_distance;

    // depth prevents stack overflow
    // (I picked 12 because 2^12 = 2048 is larger than most monitors ;-)
    // the flatness comparison value is somewhat arbitrary.
    // (I just kept moving it closer to 1 until I got good results. ;-)
    if ((depth > 12) || (flatness <= 1.001)) {
        QPointF p0 = points[0], pN = points[len - 1];
        QPointF vO = normalize(orthogonal(subtract(pN, p0)), displacement);
        if (path.currentPosition().isNull()) {   // if this is the 1st point
            QPointF p0P = add(p0, vO);
            path.moveTo(p0P.x(), p0P.y());
        }
        QPointF pNP = add(pN, vO);
        path.lineTo(pNP.x(), pNP.y());
        result = inner_distance;
    } else {
#if 0
        // calculate (len - 1) order of points
        // (zero'th order are the input points)
        QPointF[][] nthOrderPoints = QPointF[len - 1][];
        for (idx = 0; idx < len - 1; idx++) {
            nthOrderPoints[idx] = QPointF[len - 1 - idx];
            for (jdx = 0; jdx < len - 1 - idx; jdx++) {
                if (idx == 0) {
                    nthOrderPoints[idx][jdx] = midPoint(points[jdx], points[jdx + 1]);
                } else {
                    nthOrderPoints[idx][jdx] = midPoint(nthOrderPoints[idx - 1][jdx], nthOrderPoints[idx - 1][jdx + 1]);
                }
            }
        }

        // collect left points
        QPointF[] leftPoints = new Point2D[len];
        leftPoints[0] = points[0];
        for (idx = 0; idx < len - 1; idx++) {
            leftPoints[idx + 1] = nthOrderPoints[idx][0];
        }
        // draw left side Bezier
        result = plotBezier(path, leftPoints, depth + 1, displacement);

        // collect right points
        QPointF[] rightPoints = new Point2D[len];
        for (idx = 0; idx < len - 1; idx++) {
            rightPoints[idx] = nthOrderPoints[len - 2 - idx][idx];
        }
        rightPoints[idx] = points[len - 1];

        // draw right side Bezier
        result += plotBezier(path, rightPoints, depth + 1, displacement);
#endif
    }
    return result;
}

// recursive routine to plot a cubic Bezier...
// (also returns distance!)
/*private*/ /*static*/ double MathUtil::plotBezier(
        QPainterPath &path,
        /*@Nonnull*/ QPointF p0,
        /*@Nonnull*/ QPointF p1,
        /*@Nonnull*/ QPointF p2,
        /*@Nonnull*/ QPointF p3,
        int depth,
        double displacement) {
    double result;

    // calculate flatness to determine if we need to recurse...
    double l01 = distance(p0, p1);
    double l12 = distance(p1, p2);
    double l23 = distance(p2, p3);
    double l03 = distance(p0, p3);
    double flatness = (l01 + l12 + l23) / l03;

    // depth prevents stack overflow
    // (I picked 12 because 2^12 = 2048 is larger than most monitors ;-)
    // the flatness comparison value is somewhat arbitrary.
    // (I just kept moving it closer to 1 until I got good results. ;-)
    if ((depth > 12) || (flatness <= 1.001)) {
        QPointF vO = normalize(orthogonal(subtract(p3, p0)), displacement);
        if (bezier1st) {
            QPointF p0P = add(p0, vO);
            path.moveTo(p0P.x(), p0P.y());
            bezier1st = false;
        }
        QPointF p3P = add(p3, vO);
        path.lineTo(p3P.x(), p3P.y());
        result = l03;
    } else {
        // first order midpoints
        QPointF q0 = midPoint(p0, p1);
        QPointF q1 = midPoint(p1, p2);
        QPointF q2 = midPoint(p2, p3);

        // second order midpoints
        QPointF r0 = midPoint(q0, q1);
        QPointF r1 = midPoint(q1, q2);

        // third order midPoint
        QPointF s = midPoint(r0, r1);

        // draw left side Bezier
        result = MathUtil::plotBezier(path, p0, q0, r0, s, depth + 1, displacement);
        // draw right side Bezier
        result += MathUtil::plotBezier(path, s, r1, q2, p3, depth + 1, displacement);
    }
    return result;
}

/*
 * Plot a Bezier curve.
 *
 * @param g2 the Graphics2D context to draw to
 * @param p  the control points
 * @param displacement right/left to draw a line parallel to the Bezier
 * @param fillFlag     false to draw / true to fill
 * @return the length of the Bezier curve
 */
/*private*/ /*static*/ double MathUtil::plotBezier(
        QGraphicsScene* g2,
        /*@Nonnull*/ QList<QPointF> p,
        double displacement,
        bool fillFlag) {
    double result;
    QPainterPath path = QPainterPath();
    if (p.length() == 4) {    // draw cubic bezier?
        result = plotBezier(path, p[0], p[1], p[2], p[3], 0, displacement);
    } else {    // (nope)
        result = plotBezier(path, p, 0, displacement);
    }
    QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
    QColor fillColor = QColor(Qt::darkGray);
    QBrush fillBrush = QBrush(fillColor);
    if (fillFlag) {
        //g2->fill(path);
     pathItem->setBrush(fillBrush);
    } else {
        //g2->draw(path);
    }
    g2->addItem(pathItem);

    return result;
}

/**
     * Draw a cubic Bezier curve
     *
     * @param g2 the Graphics2D to draw to
     * @param p0 origin control point
     * @param p1 first control point
     * @param p2 second control point
     * @param p3 terminating control point
     *
     * @return the length of the Bezier curve
     */
    /*public*/ /*static*/ QPainterPath MathUtil::drawBezier(
            /*@Nonnull*/ QPointF p0,
            /*@Nonnull*/ QPointF p1,
            /*@Nonnull*/ QPointF p2,
            /*@Nonnull*/ QPointF p3)
        {
        QPainterPath path = QPainterPath();
        bezier1st = true;
        double result = MathUtil::plotBezier(path, p0, p1, p2, p3, 0, 0.0);
        //g2.draw(path);

        return path;
    }
#if 0 // TODO:
    // recursive routine to plot a Bezier curve...
    // (also returns distance!)
    /*private*/ static doubleMathUtil:: plotBezier(
            QPainterPath path,
            /*@Nonnull*/ QList<QPointF> points,
            int depth,
            double displacement) {
        int len = points.length(), idx, jdx;
        double result;

        // calculate flatness to determine if we need to recurse...
        double outer_distance = 0;
        for (idx = 1; idx < len; idx++) {
            outer_distance += MathUtil::distance(points[idx - 1], points[idx]);
        }
        double inner_distance = MathUtil::distance(points[0], points[len - 1]);
        double flatness = outer_distance / inner_distance;

        // depth prevents stack overflow
        // (I picked 12 because 2^12 = 2048 is larger than most monitors ;-)
        // the flatness comparison value is somewhat arbitrary.
        // (I just kept moving it closer to 1 until I got good results. ;-)
        if ((depth > 12) || (flatness <= 1.001)) {
            QPointF p0 = points[0], pN = points[len - 1];
            QPointF vO = normalize(orthogonal(subtract(pN, p0)), displacement);
            if (bezier1st) {
                QPointF p0P = add(p0, vO);
                path.moveTo(p0P.x(), p0P.y());
                bezier1st = false;
            }
            QPointF pNP = add(pN, vO);
            path.lineTo(pNP.x(), pNP.y());
            result = inner_distance;
        } else {
            // calculate (len - 1) order of points
            // (zero'th order are the input points)
            //QPointF[][] nthOrderPoints = new QPointF[len - 1][];
            QVector<QVector<QPointF> > nthOrderPoints = QVector<QVector<QPointF>(len -1);
            for (idx = 0; idx < len - 1; idx++) {
                nthOrderPoints[idx] = new QPointF[len - 1 - idx];
                for (jdx = 0; jdx < len - 1 - idx; jdx++) {
                    if (idx == 0) {
                        nthOrderPoints[idx][jdx] = midPoint(points[jdx], points[jdx + 1]);
                    } else {
                        nthOrderPoints[idx][jdx] = midPoint(nthOrderPoints[idx - 1][jdx], nthOrderPoints[idx - 1][jdx + 1]);
                    }
                }
            }

            // collect left points
            QPointF[] leftPoints = new QPointF[len];
            leftPoints[0] = points[0];
            for (idx = 0; idx < len - 1; idx++) {
                leftPoints[idx + 1] = nthOrderPoints[idx][0];
            }
            // draw left side Bezier
            result = plotBezier(path, leftPoints, depth + 1, displacement);

            // collect right points
            QPointF[] rightPoints = new QPointF[len];
            for (idx = 0; idx < len - 1; idx++) {
                rightPoints[idx] = nthOrderPoints[len - 2 - idx][idx];
            }
            rightPoints[idx] = points[len - 1];

            // draw right side Bezier
            result += plotBezier(path, rightPoints, depth + 1, displacement);
        }
        return result;
    }
#endif
    /**
     * Draw a Bezier curve
     *
     * @param g2  the Graphics2D to draw to
     * @param p control points
     * @param displacement right/left to draw a line parallel to the Bezier
     * @return the length of the Bezier curve
     */
    /*public*/ /*static*/ QPainterPath MathUtil::drawBezier(
            /*@Nonnull*/ QVector<QPointF> p,
            double displacement)
    {
        double result;
        QPainterPath path = QPainterPath();
        bezier1st = true;
//        path.moveTo(p.at(0));
//        path.cubicTo(p.at(1), p.at(2), p.at(3));
        if (p.length() == 4) {    // draw cubic bezier?
            result = plotBezier(path, p[0], p[1], p[2], p[3], 0, displacement);
        }
//        else {    // (nope)
//            result = plotBezier(path, p, 0, displacement);
//        }
//        g2.draw(path);
       return path;
    }

    /**
     * Draw a Bezier curve
     *
     * @param g2  the Graphics2D to draw to
     * @param p control points
     * @return the length of the Bezier curve
     */
    /*public*/ /*static*/ QPainterPath MathUtil::drawBezier(/*@Nonnull*/ QVector<QPointF> p) {
        return drawBezier(p, 0.0);
    }

/*private*/ /*static*/ bool MathUtil::bezier1st = false;

/**
 * Fill a Bezier curve.
 *
 * @param g2 the Graphics2D context to draw to
 * @param p  the control points
 * @return the length of the Bezier curve
 */
/*public*/ /*static*/ double MathUtil::fillBezier(QGraphicsScene* g2, /*@Nonnull*/ QList<QPointF> p) {
    return plotBezier(g2, p, 0.0, true);
}

/**
 * Find intersection of two lines.
 *
 * @param p1 the first point on the first line
 * @param p2 the second point on the first line
 * @param p3 the first point on the second line
 * @param p4 the second point on the second line
 * @return the intersection point of the two lines or null if one doesn't
 *         exist
 */
//@CheckReturnValue
/*public*/ /*static*/ QPointF MathUtil::intersect(
        /*@Nonnull*/ QPointF p1,
        /*@Nonnull*/ QPointF p2,
        /*@Nonnull*/ QPointF p3,
        /*@Nonnull*/ QPointF p4) {
    QPointF result = QPointF();  // assume failure (pessimist!)

    QPointF delta31 = MathUtil::subtract(p3, p1);    //p
    QPointF delta21 = MathUtil::subtract(p2, p1);    //q
    QPointF delta43 = MathUtil::subtract(p4, p3);    //r

    double det = delta21.x() * delta43.y() - delta21.y() * delta43.x();
    if (!MathUtil::equals(det, 0.0)) {
        double t = (delta21.y() * delta31.x() - delta21.x() * delta31.y()) / det;
        result = lerp(p1, p2, t);
    }
    return result;
}

/**
 * get (signed) distance p3 is from line segment defined by p1 and p2
 *
 * @param p1 the first point on the line segment
 * @param p2 the second point on the line segment
 * @param p3 the point whose distance from the line segment you wish to
 *           calculate
 * @return the distance (note: plus/minus determines the (left/right) side
 *         of the line)
 */
/*public*/ /*static*/ double MathUtil::distance(/*@Nonnull*/ QPointF p1,
        /*@Nonnull*/  QPointF p2,
        /*@Nonnull*/  QPointF p3) {
    double p1X = p1.x(), p1Y = p1.y();
    double p2X = p2.x(), p2Y = p2.y();
    double p3X = p3.x(), p3Y = p3.y();

    double a = p1Y - p2Y;
    double b = p2X - p1X;
    double c = (p1X * p2Y) - (p2X * p1Y);

    return (a * p3X + b * p3Y + c) / qSqrt(a * a + b * b);
}

/*public*/ /*static*/ double MathUtil::hypot(double a, double b)
{
 return qSqrt((a*a) + (b*b));
}
/*private*/ /*final*/ /*static*/ Logger* MathUtil::log = LoggerFactory::getLogger("MathUtil");

