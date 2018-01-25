#include "layouttrack.h"
#include <QColor>

/**
 * Abstract base class for all layout track objects (LayoutTurnout, LayoutSlip,
 * LayoutTurntable, LevelXing, TrackSegment)
 *
 * @author George Warner Copyright (c) 2017
 */
// /*public*/ abstract class LayoutTrack {

    // Defined text resource
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");



// dashed line parameters
//private static int minNumDashes = 3;
//private static double maxDashLength = 10;


/*protected*/ /*static*/ QColor LayoutTrack::defaultTrackColor = QColor(Qt::black);

/*protected*/ /*static*/ /*final*/ double LayoutTrack::controlPointSize = 3.0;   // LayoutEditor.SIZE;
/*protected*/ /*static*/ /*final*/ double LayoutTrack::controlPointSize2 = 2.0 * LayoutTrack::controlPointSize; // LayoutEditor.SIZE2;

/**
 * constructor method
 */
/*public*/ LayoutTrack::LayoutTrack(QObject*parent) : QObject(parent)
{
 center =  QPointF(50.0, 50.0);
 hidden = false;

}

/**
 * accessor method
 */
/*public*/ /*static*/ void LayoutTrack::setDefaultTrackColor(QColor color) {
    defaultTrackColor = color;
}

//NOTE: not /*public*/ because "center" is a member variable
/*protected*/ QPointF LayoutTrack::rotatePoint(QPointF p, double sineRot, double cosineRot) {
    double cX = center.x();
    double cY = center.y();
    double deltaX = p.x() - cX;
    double deltaY = p.y() - cY;
    double x = cX + cosineRot * deltaX - sineRot * deltaY;
    double y = cY + sineRot * deltaX + cosineRot * deltaY;
    return QPointF(x, y);
}

/**
 * Get the hidden state of the track element.
 *
 * @return true if hidden; false otherwise
 */
/*public*/ bool LayoutTrack::isHidden() {
    return hidden;
}

/**
 * Get the hidden state of the track element.
 *
 * @return true if hidden; false otherwise
 * @deprecated since 4.7.2; use {@link #isHidden()} instead
 */
//@Deprecated // Java standard pattern for bool getters is "isHidden()"
/*public*/ bool LayoutTrack::getHidden() {
    return hidden;
}

/*public*/ void LayoutTrack::setHidden(bool hide) {
    hidden = hide;
}

/*private*/ /*final*/ /*static*/ Logger* LayoutTrack::log = LoggerFactory::getLogger("LayoutTrack");
