#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include "pathiterator.h"

class Logger;
class Polygon : public JShape
{
public:
    Polygon();
    /*public*/ Polygon(QVector<int>* xpoints, QVector<int>* ypoints, int npoints);
    ~Polygon();
    /**
     * The total number of points.  The value of <code>npoints</code>
     * represents the number of valid points in this <code>Polygon</code>
     * and might be less than the number of elements in
     * {@link #xpoints xpoints} or {@link #ypoints ypoints}.
     * This value can be NULL.
     *
     * @serial
     * @see #addPoint(int, int)
     * @since 1.0
     */
    /*public*/ int npoints;

    /**
     * The array of X coordinates.  The number of elements in
     * this array might be more than the number of X coordinates
     * in this <code>Polygon</code>.  The extra elements allow new points
     * to be added to this <code>Polygon</code> without re-creating this
     * array.  The value of {@link #npoints npoints} is equal to the
     * number of valid points in this <code>Polygon</code>.
     *
     * @serial
     * @see #addPoint(int, int)
     * @since 1.0
     */
    /*public*/ QVector<int>* xpoints;

    /**
     * The array of Y coordinates.  The number of elements in
     * this array might be more than the number of Y coordinates
     * in this <code>Polygon</code>.  The extra elements allow new points
     * to be added to this <code>Polygon</code> without re-creating this
     * array.  The value of <code>npoints</code> is equal to the
     * number of valid points in this <code>Polygon</code>.
     *
     * @serial
     * @see #addPoint(int, int)
     * @since 1.0
     */
    /*public*/ QVector<int>* ypoints;
    /*public*/ void reset();
    /*public*/ void invalidate();
    /*public*/ void translate(int deltaX, int deltaY);
    /*public*/ void addPoint(int x, int y);
    /*public*/ QRect getBounds();
    QT_DEPRECATED /*public*/ QRect getBoundingBox();
    /*public*/ bool contains(QPoint p);
    /*public*/ bool contains(int x, int y);
    QT_DEPRECATED /*public*/ bool inside(int x, int y);
    /*public*/ QRectF getBounds2D();
    /*public*/ bool contains(double x, double y);
    /*public*/ static int highestOneBit(int i);

private:
    /*private*/ static /*final*/ int MIN_LENGTH;// = 4;
    Logger* log;
    void calculateBounds(QVector<int>* xpoints, QVector<int>* ypoints, int npoints);
    void updateBounds(int x, int y);

protected:
    /**
     * The bounds of this {@code Polygon}.
     * This value can be null.
     *
     * @serial
     * @see #getBoundingBox()
     * @see #getBounds()
     * @since 1.0
     */
    /*protected*/ QRect bounds;
};
class PolygonPathIterator : public PathIterator
{
    Polygon* poly;
    AffineTransform* transform;
    int index;
public:
    /*public*/ PolygonPathIterator(Polygon* pg, AffineTransform* at);
    /*public*/ int getWindingRule();
    /*public*/ bool isDone();
    /*public*/ void next();
    /*public*/ int currentSegment(QVector<float>* coords);
    /*public*/ int currentSegment(QVector<double>* coords);
};

#endif // POLYGON_H
