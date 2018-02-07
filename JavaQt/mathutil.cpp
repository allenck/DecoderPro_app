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
 * Returns the distance from this <code>Point2D</code> to a
 * specified <code>Point2D</code>.
 *
 * @param pt the specified point to be measured
 *           against this <code>Point2D</code>
 * @return the distance between this <code>Point2D</code> and
 * the specified <code>Point2D</code>.
 * @since 1.2
 */
/*public*/ /*static*/ double MathUtil::distance(QPointF p1, QPointF pt) {
    double px = pt.x() - p1.x();
    double py = pt.y() - p1.y();
    return qSqrt(px * px + py * py);
}
