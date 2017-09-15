#ifndef PATH2D_H
#define PATH2D_H
#include <QVector>
#include <QPointF>
#include <qobject.h>
#include "shape.h"

class PathIterator;
class Logger;
class JShape;
class AffineTransform;
class Path2D : public JShape
{
 Q_OBJECT
public:
 Path2D();
 /*public*/ static /*final*/ int WIND_EVEN_ODD;// = PathIterator.WIND_EVEN_ODD;
 /**
  * A non-zero winding rule for determining the interior of a
  * path.
  *
  * @see PathIterator#WIND_NON_ZERO
  * @since 1.6
  */
 /*public*/ static /*final*/ int WIND_NON_ZERO;// = PathIterator.WIND_NON_ZERO;
 /*public*/ /*final*/ void setWindingRule(int rule);
 /*public*/ /*final*/ /*synchronized*/ void closePath();
 /*public*/ /*final*/ /*synchronized*/ int getWindingRule();




private:


 // For code simplicity, copy these constants to our namespace
 // and cast them to byte constants for easy storage.
 /*private*/ static /*final*/ char SEG_MOVETO;//  = (byte) PathIterator.SEG_MOVETO;
 /*private*/ static /*final*/ char SEG_LINETO;//  = (byte) PathIterator.SEG_LINETO;
 /*private*/ static /*final*/ char SEG_QUADTO;//  = (byte) PathIterator.SEG_QUADTO;
 /*private*/ static /*final*/ char SEG_CUBICTO;// = (byte) PathIterator.SEG_CUBICTO;
 /*private*/ static /*final*/ char SEG_CLOSE;//   = (byte) PathIterator.SEG_CLOSE;
 /*transient*/ QVector<char>* pointTypes;
 /*transient*/ int numTypes;
 /*transient*/ int numCoords;
 /*transient*/ int windingRule;
 static /*final*/ int INIT_SIZE;// = 20;
 static /*final*/ int EXPAND_MAX;// = 500;
 static /*final*/ int EXPAND_MAX_COORDS;// = EXPAND_MAX * 2;
 static /*final*/ int EXPAND_MIN;// = 10; // ensure > 6 (cubics)
 /*abstract*/ virtual QVector<float>* cloneCoordsFloat(AffineTransform* at);
 /*abstract*/ virtual QVector<double>* cloneCoordsDouble(AffineTransform* at);
 /*abstract*/ virtual void append(float x, float y);
 /*abstract*/ virtual void append(double x, double y);
 /*abstract*/ virtual QPointF getPoint(int coordindex);
 /*abstract*/ virtual void needRoom(bool needMove, int newCoords);
 /*abstract*/ virtual int pointCrossings(double px, double py);
 /*abstract*/ virtual int rectCrossings(double rxmin, double rymin,
                            double rxmax, double rymax);
 static QVector<float>* copyOf(QVector<float>*, int newLength);
 static QVector<char>* copyOf(QVector<char>*, int newLength);

 Logger* log;
 static QVector<char>* expandPointTypes(QVector<char>* oldPointTypes, int needed);

protected:
 Path2D(int rule, int initialTypes);

 friend class PositionablePolygonXml;
 friend class GeneralPath;
 friend class  Float;
 friend class CopyIterator;
 friend class TxIterator;
 friend class Iterator;
};

/*public*/ /*static*/ class Float : public Path2D //implements Serializable
{
    /*transient*/ QVector<float>* floatCoords;
 Logger* log;
    /**
     * Constructs a new empty single precision {@code Path2D} object
     * with a default winding rule of {@link #WIND_NON_ZERO}.
     *
     * @since 1.6
     */
    /*public*/ Float();
    /*public*/ Float(int rule);
    /*public*/ Float(int rule, int initialCapacity);
    ///*public*/ Path2D_Float(JShape* s) ;
    /*public*/ Float(JShape* s, AffineTransform* at = 0) ;
    QVector<float>* cloneCoordsFloat(AffineTransform* at);
    QVector<double>* cloneCoordsDouble(AffineTransform* at);
    void append(float x, float y) ;
    void append(double x, double y);
    /*public*/ /*final*/ void append(PathIterator* pi, bool connect);
    QPointF getPoint(int coordindex);
    void needRoom(bool needMove, int newCoords);
    /*public*/ /*final*/ /*synchronized*/ void moveTo(double x, double y);
    /*public*/ /*final*/ /*synchronized*/ void moveTo(float x, float y);
    /*public*/ /*final*/ /*synchronized*/ void lineTo(double x, double y);
    /*public*/ /*final*/ /*synchronized*/ void lineTo(float x, float y);
    /*public*/ /*final*/ /*synchronized*/ void quadTo(double x1, double y1,
                                          double x2, double y2);
    /*public*/ /*final*/ /*synchronized*/ void quadTo(float x1, float y1,
                                                      float x2, float y2);
    /*public*/ /*final*/ /*synchronized*/ void curveTo(double x1, double y1,
                                           double x2, double y2,
                                           double x3, double y3);
    /*public*/ /*final*/ /*synchronized*/ void curveTo(float x1, float y1,
                                           float x2, float y2,
                                           float x3, float y3);
    static QVector<float>* expandCoords(QVector<float>* oldCoords, int needed);
    /*public*/ /*final*/ PathIterator* getPathIterator(AffineTransform* at);

#if 0
    /*public*/ /*final*/ synchronized void moveTo(double x, double y);
    /*public*/ /*final*/ synchronized void moveTo(float x, float y);
    /*public*/ /*final*/ synchronized void lineTo(double x, double y);
    /*public*/ /*final*/ synchronized void lineTo(float x, float y) ;
    /*public*/ /*final*/ synchronized void quadTo(double x1, double y1,
                                          double x2, double y2);
    /*public*/ /*final*/ synchronized void quadTo(float x1, float y1,
                                          float x2, float y2);
    /*public*/ /*final*/ synchronized void curveTo(double x1, double y1,
                                           double x2, double y2,
                                           double x3, double y3);
    /*public*/ /*final*/ synchronized void curveTo(float x1, float y1,
                                           float x2, float y2,
                                           float x3, float y3);
    int pointCrossings(double px, double py);
    int rectCrossings(double rxmin, double rymin,
                      double rxmax, double rymax);
    /*public*/ /*final*/ void append(PathIterator pi, boolean connect);
    /*public*/ /*final*/ void transform(AffineTransform at);
    /*public*/ /*final*/ synchronized Rectangle2D getBounds2D() ;
    /*public*/ /*final*/ PathIterator getPathIterator(AffineTransform* at);
    /*public*/ /*final*/ Object clone();
    /*private*/ void writeObject(java.io.ObjectOutputStream s);
    /*private*/ void readObject(java.io.ObjectInputStream s);
#endif

 friend class PositionablePolygonXml;
 friend class GeneralPath;
 friend class DrawPolygon;
 friend class PositionablePolygon;
 friend class Path2D;
 friend class CopyIterator;
 friend class TxIterator;

};
/*static*/ /*abstract*/ class Iterator : public PathIterator
{
 Q_OBJECT
    int typeIdx;
    int pointIdx;
    Path2D* path;

    static /*final*/ QVector<int> curvecoords; // = {2, 2, 4, 6, 0};
public:
    Iterator(Path2D* path) ;
    /*public*/ int getWindingRule();
    /*public*/ bool isDone();
    /*public*/ void next();
    friend class CopyIterator;
    friend class TxIterator;
};

/*static*/ class CopyIterator : public Iterator
{
    QVector<float>* floatCoords;
public:
    CopyIterator(Float* p2df);
    /*public*/ int currentSegment(QVector<float>* coords);
    /*public*/ int currentSegment(QVector<double>* coords);
    friend class Path2D;
};

/*static*/ class TxIterator : public Iterator
{
    QVector<float>* floatCoords;
    AffineTransform* affine;
public:
    TxIterator(Float* p2df, AffineTransform* at);
    /*public*/ int currentSegment(QVector<float>* coords) ;
    /*public*/ int currentSegment(QVector<double>* coords);
    friend class Path2D;
};
#endif // PATH2D_H
