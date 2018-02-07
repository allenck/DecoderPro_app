#include "region.h"
#include "loggerfactory.h"
#include <QStringList>
#include <QString>
/**
 * Represent a region in space for the RPS system.
 * <P>
 * The region is specfied by a <em>right-handed</em>
 * set of points.
 * <p>
 * Regions are immutable once created.
 * <p>
 * This initial implementation of a Region is inherently 2-dimensional,
 * deferring use of the 3rd (Z) dimension to a later implementation. It uses a
 * Java2D GeneralPath to handle the inside/outside calculations.
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2008
  */
//@net.jcip.annotations.Immutable
// /*public*/ class Region {

/*public*/ Region::Region(QVector<QVector3D>* points, QObject* parent)  : QObject(parent){
    //super();

    initPath(points);

    // old init
    if (points->length() < 3) {
        log->error("Not enough points to define region");
    }
    this->points = new QVector<QVector3D>(*points);//Arrays.copyOf(points, points.length);
}


/**
 * Provide Java2D access to the shape of this region.
 * <p>
 * This should provide a copy of the GeneralPath path, to keep the
 * underlying object immutable, but by returning a Shape type hopefully we
 * achieve the same result with a little better performance. Please don't
 * assume you can cast and modify this.
 */
/*public*/ JShape* Region::getPath() {
    return path;
}

void Region::initPath(QVector<QVector3D>* points) {
    if (points->length() < 3) {
        log->error("Region needs at least three points to have non-zero area");
    }

    path = new GeneralPath();
    path->moveTo((float) points->at(0).x(), (float) points->at(0).y());
    for (int i = 1; i < points->length(); i++) {
        path->lineTo((float) points->at(i).x(), (float) points->at(i).y());
    }
    path->lineTo((float) points->at(0).x(), (float) points->at(0).y());
}

/**
 * Ctor from a string like "(0,0,0);(1,0,0);(1,1,0);(0,1,0)"
 */
/*public*/ Region::Region(QString s, QObject* parent) : QObject(parent) {
    QStringList pStrings = s.split(";");
    points = new QVector<QVector3D>(pStrings.length());

    // load each point
    for (int i = 0; i < points->length(); i++) {
        // remove leading ( and trailing )
        QString coords = pStrings[i].mid(1, pStrings[i].length() - 1);
        QStringList coord = coords.split(",");
        if (coord.length() != 3) {
            log->error("need to have three coordinates in " + pStrings[i]);
        }
        double x = coord.at(0).toDouble();
        double y = coord.at(1).toDouble();
        double z = coord.at(2).toDouble();
        points->replace(i, QVector3D(x, y, z));
    }
    initPath(points);
}
#if 0
@SuppressFBWarnings(value = "SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
@Override
/*public*/ String toString() {
    String retval = "";
    for (int i = 0; i < points.length; i++) {
        retval += "(" + points[i].x + "," + points[i].y + "," + points[i].z + ")";
        if (i != points.length - 1) {
            retval += ";";
        }
    }
    return retval;
}
#endif
/*public*/ bool Region::isInside(QVector3D p) {
    return path->contains(p.x(), p.y());
}
#if 0
@Override
/*public*/ boolean equals(Object ro) {
    if (ro == null) {
        return false;
    }
    try {
        Region r = (Region) ro;
        if (points.length != r.points.length) {
            return false;
        }
        for (int i = 0; i < points.length; i++) {
            if (!points[i].epsilonEquals(r.points[i], 0.001)) {
                return false;
            }
        }
        return true;
    } catch (Exception e) {
        return false;
    }
}

@Override
/*public*/ int hashCode() {
    int code = 0;
    if (points.length >= 1) {
        code = 10000 * (int) points[0].x + 10000 * (int) points[0].y;
    }
    if (points.length >= 2) {
        code = code + 10000 * (int) points[1].x + 10000 * (int) points[1].y;
    }
    return code;
}
#endif

/*private*/ /*final*/ /*static*/ Logger* Region::log = LoggerFactory::getLogger("Region");
