#include "mathutil.h"

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
/*public*/ /*static*/ /*final*/ QPointF zeroQPointF = QPointF();
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

// return a QPointF at the mid point between p1 & p2
/*public*/ /*static*/ QPointF MathUtil::midpoint(QPointF p1, QPointF p2) {
    return lerp(p1, p2, 0.5);
}

// return a QPointF one third of the way from p1 to p2
/*public*/ /*static*/ QPointF MathUtil::third(QPointF p1, QPointF p2) {
    return lerp(p1, p2, 1.0 / 3.0);
}

// return a QPointF one forth of the way from p1 to p2
/*public*/ /*static*/ QPointF MathUtil::fourth(QPointF p1, QPointF p2) {
    return lerp(p1, p2, 1.0 / 4.0);
}
#if 0
//
// Wrap a double between two values (for example +/- 180 or 0-360 degrees)
// Note: THIS IS NOT A PIN OR TRUNCATE; VALUES WRAP AROUND BETWEEN MIN & MAX
// (And yes, this works correctly with negative numbers)
//
/*public*/ /*static*/ double MathUtil::wrap(double inValue, double inMin, double inMax) {
    double valueRange = inMax - inMin;
    return inMin + ((((inValue - inMin) % valueRange) + valueRange) % valueRange);
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
/*public*/ /*static*/ double MathUtil::diffAngle(double a, double b) {
    return qAbs(wrapPM180(a - b));
}
#endif
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
/*public*/ /*static*/ QRectF MathUtil::zeroToInfinityRectangle2D() {
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
