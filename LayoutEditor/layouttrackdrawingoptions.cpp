#include "layouttrackdrawingoptions.h"
#include "jmricolorchooser.h"

/**
 *
 * @author George Warner Copyright (c) 2017-2018
 */
// /*public*/ class LayoutTrackDrawingOptions {


/*public*/ LayoutTrackDrawingOptions::LayoutTrackDrawingOptions(QString name, QObject* parent) : QObject(parent)
{
  mainRailColor = QColor(Qt::gray);
  mainTieColor = QColor(Qt::black);
  mainBallastColor = QColor(Qt::black);;
  sideRailColor = QColor(Qt::gray);
  sideTieColor = QColor(Qt::black);;
  sideBallastColor = QColor(Qt::black);;


    this->name = name;
}

/*public*/ LayoutTrackDrawingOptions::LayoutTrackDrawingOptions(LayoutTrackDrawingOptions* ltdo) {
    name = ltdo->getName();
    mainBallastColor = ltdo->getMainBallastColor();
    mainBallastWidth = ltdo->getMainBallastWidth();
    mainBlockLineDashPercentageX10 = ltdo->getMainBlockLineDashPercentageX10();
    mainBlockLineWidth = ltdo->getMainBlockLineWidth();
    mainRailColor = ltdo->getMainRailColor();
    mainRailCount = ltdo->getMainRailCount();
    mainRailGap = ltdo->getMainRailGap();
    mainRailWidth = ltdo->getMainRailWidth();
    mainTieColor = ltdo->getMainTieColor();
    mainTieGap = ltdo->getMainTieGap();
    mainTieLength = ltdo->getMainTieLength();
    mainTieWidth = ltdo->getMainTieWidth();
    sideBallastColor = ltdo->getSideBallastColor();
    sideBallastWidth = ltdo->getSideBallastWidth();
    sideBlockLineDashPercentageX10 = ltdo->getSideBlockLineDashPercentageX10();
    sideBlockLineWidth = ltdo->getSideBlockLineWidth();
    sideRailColor = ltdo->getSideRailColor();
    sideRailCount = ltdo->getSideRailCount();
    sideRailGap = ltdo->getSideRailGap();
    sideRailWidth = ltdo->getSideRailWidth();
    sideTieColor = ltdo->getSideTieColor();
    sideTieGap = ltdo->getSideTieGap();
    sideTieLength = ltdo->getSideTieLength();
    sideTieWidth = ltdo->getSideTieWidth();
}

/*public*/ QString LayoutTrackDrawingOptions::getName() {
    return name;
}

/*public*/ void LayoutTrackDrawingOptions::setName(QString name) {
    this->name = name;
}

/*public*/ int LayoutTrackDrawingOptions::getSideBallastWidth() {
    return sideBallastWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setSideBallastWidth(int val) {
    sideBallastWidth = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getSideBallastColor() {
    return sideBallastColor;
}

/*public*/ void LayoutTrackDrawingOptions::setSideBallastColor(/*@Nonnull*/ QColor val) {
    sideBallastColor = val;
    JmriColorChooser::addRecentColor(val);
}

/*public*/ int LayoutTrackDrawingOptions::getSideTieLength() {
    return sideTieLength;
}

/*public*/ void LayoutTrackDrawingOptions::setSideTieLength(int val) {
    sideTieLength = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getSideTieColor() {
    return sideTieColor;
}

/*public*/ void LayoutTrackDrawingOptions::setSideTieColor (QColor val) {
    sideTieColor = val;
    JmriColorChooser::addRecentColor(val);
}

/*public*/ int LayoutTrackDrawingOptions::getSideTieWidth() {
    return sideTieWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setSideTieWidth(int val) {
    sideTieWidth = val;
}

/*public*/ int LayoutTrackDrawingOptions::getSideTieGap() {
    return sideTieGap;
}

/*public*/ void LayoutTrackDrawingOptions::setSideTieGap(int val) {
    sideTieGap = val;
}

/*public*/ int LayoutTrackDrawingOptions::getSideRailCount() {
    return sideRailCount;
}

/*public*/ void LayoutTrackDrawingOptions::setSideRailCount(int val) {
    sideRailCount = val;
}

/*public*/ int LayoutTrackDrawingOptions::getSideRailWidth() {
    return sideRailWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setSideRailWidth(int val) {
    sideRailWidth = val;
}

/*public*/ int LayoutTrackDrawingOptions::getSideRailGap() {
    return sideRailGap;
}

/*public*/ void LayoutTrackDrawingOptions::setSideRailGap(int val) {
    sideRailGap = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getSideRailColor() {
    return sideRailColor;
}

/*public*/ void LayoutTrackDrawingOptions::setSideRailColor(/*@Nonnull*/ QColor val) {
    sideRailColor = val;
    JmriColorChooser::addRecentColor(val);
}

/*public*/ int LayoutTrackDrawingOptions::getSideBlockLineDashPercentageX10() {
    return sideBlockLineDashPercentageX10;
}

/*public*/ void LayoutTrackDrawingOptions::setSideBlockLineDashPercentageX10(int val) {
    sideBlockLineDashPercentageX10 = val;
}

/*public*/ int LayoutTrackDrawingOptions::getSideBlockLineWidth() {
    return sideBlockLineWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setSideBlockLineWidth(int val) {
    sideBlockLineWidth = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainBallastWidth() {
    return mainBallastWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setMainBallastWidth(int val) {
    mainBallastWidth = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getMainBallastColor() {
    return mainBallastColor;
}

/*public*/ void LayoutTrackDrawingOptions::setMainBallastColor(/*@Nonnull*/ QColor val) {
    mainBallastColor = val;
    JmriColorChooser::addRecentColor(val);
}


/*public*/ int LayoutTrackDrawingOptions::getMainTieLength() {
    return mainTieLength;
}

/*public*/ void LayoutTrackDrawingOptions::setMainTieLength(int val) {
    mainTieLength = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getMainTieColor() {
    return mainTieColor;
}

/*public*/ void LayoutTrackDrawingOptions::setMainTieColor(/*@Nonnull*/ QColor val) {
    mainTieColor = val;
    JmriColorChooser::addRecentColor(val);
}

/*public*/ int LayoutTrackDrawingOptions::getMainTieWidth() {
    return mainTieWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setMainTieWidth(int val) {
    mainTieWidth = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainTieGap() {
    return mainTieGap;
}

/*public*/ void LayoutTrackDrawingOptions::setMainTieGap(int val) {
    mainTieGap = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainRailCount() {
    return mainRailCount;
}

/*public*/ void LayoutTrackDrawingOptions::setMainRailCount(int val) {
    mainRailCount = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainRailWidth() {
    return mainRailWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setMainRailWidth(int val) {
    mainRailWidth = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainRailGap() {
    return mainRailGap;
}

/*public*/ void LayoutTrackDrawingOptions::setMainRailGap(int val) {
    mainRailGap = val;
}

/*public*/ QColor LayoutTrackDrawingOptions::getMainRailColor() {
    return mainRailColor;
}

/*public*/ void LayoutTrackDrawingOptions::setMainRailColor(/*@Nonnull */ QColor val) {
    mainRailColor = val;
    JmriColorChooser::addRecentColor(val);
}

/*public*/ int LayoutTrackDrawingOptions::getMainBlockLineDashPercentageX10() {
    return mainBlockLineDashPercentageX10;
}

/*public*/ void LayoutTrackDrawingOptions::setMainBlockLineDashPercentageX10(int val) {
    mainBlockLineDashPercentageX10 = val;
}

/*public*/ int LayoutTrackDrawingOptions::getMainBlockLineWidth() {
    return mainBlockLineWidth;
}

/*public*/ void LayoutTrackDrawingOptions::setMainBlockLineWidth(int val) {
    mainBlockLineWidth = val;
}

//
/*public*/ bool LayoutTrackDrawingOptions::equalsAllButName(/*@Nonnull*/ LayoutTrackDrawingOptions* ltdo) {
    bool result = true;  // assume success (optimist!)
    if (this != ltdo) {
        result = false; // assume failure (pessimist!)
        if (ltdo != nullptr) {
            QString tempName = name;
            name = ltdo->getName();
            result = this->equals(ltdo);
            name = tempName;
        }
    }
    return result;
}

//@Override
/*public*/ bool LayoutTrackDrawingOptions::equals(QObject* obj) {

    bool result = true;  // assume success (optimist!)
    if (obj != this) {
        result = false; // assume failure (pessimist!)
        if ((obj != nullptr) && (/*getClass()*/"LayoutTrackDrawingOptions" == /*obj.getClass()*/ QString(obj->metaObject()->className()))) {
            LayoutTrackDrawingOptions* ltdo = (LayoutTrackDrawingOptions*) obj;

            do {
                if (name != (ltdo->getName())) {
                    break;
                }
                if (sideBallastWidth != ltdo->getSideBallastWidth()) {
                    break;
                }
                if (sideBallastColor!=(ltdo->getSideBallastColor())) {
                    break;
                }
                if (sideTieLength != ltdo->getSideTieLength()) {
                    break;
                }
                if (sideTieColor!=(ltdo->getSideTieColor())) {
                    break;
                }

                if (sideTieGap != ltdo->getSideTieGap()) {
                    break;
                }
                if (sideRailCount != ltdo->getSideRailCount()) {
                    break;
                }
                if (sideRailWidth != ltdo->getSideRailWidth()) {
                    break;
                }
                if (sideRailGap != ltdo->getSideRailGap()) {
                    break;
                }
                if (sideRailColor!=(ltdo->getSideRailColor())) {
                    break;
                }

                if (sideBlockLineDashPercentageX10 != ltdo->getSideBlockLineDashPercentageX10()) {
                    break;
                }

                if (sideBlockLineWidth != ltdo->getSideBlockLineWidth()) {
                    break;
                }

                if (mainBallastWidth != ltdo->getMainBallastWidth()) {
                    break;
                }
                if (mainBallastColor!=(ltdo->getMainBallastColor())) {
                    break;
                }

                if (mainTieLength != ltdo->getMainTieLength()) {
                    break;
                }
                if (mainTieColor!=(ltdo->getMainTieColor())) {
                    break;
                }

                if (mainTieWidth != ltdo->getMainTieWidth()) {
                    break;
                }
                if (mainTieGap != ltdo->getMainTieGap()) {
                    break;
                }
                if (mainRailCount != ltdo->getMainRailCount()) {
                    break;
                }
                if (mainRailWidth != ltdo->getMainRailWidth()) {
                    break;
                }
                if (mainRailGap != ltdo->getMainRailGap()) {
                    break;
                }
                if (mainRailColor!=(ltdo->getMainRailColor())) {
                    break;
                }
                if (mainBlockLineDashPercentageX10 != ltdo->getMainBlockLineDashPercentageX10()) {
                    break;
                }
                if (mainBlockLineWidth != ltdo->getMainBlockLineWidth()) {
                    break;
                }
                result = true;
            } while (false);
        }
    }
    return result;
}   // equals

/**
 * Hash on the header
 */
//@Override
/*public*/ int LayoutTrackDrawingOptions::hashCode() {
    int result = 7;
#if 0
    result = (37 * result) + (name != "" ? name.hashCode() : 0);

    // sideline values
    result = (37 * result) + sideBallastWidth;
    result = (37 * result) + (sideBallastColor == null ? 0 : sideBallastColor.hashCode());
    result = (37 * result) + sideTieLength;
    result = (37 * result) + (sideTieColor == null ? 0 : sideTieColor.hashCode());
    result = (37 * result) + sideTieGap;
    result = (37 * result) + sideRailCount;
    result = (37 * result) + sideRailWidth;
    result = (37 * result) + sideRailGap;
    result = (37 * result) + (sideRailColor == null ? 0 : sideRailColor.hashCode());
    result = (37 * result) + sideBlockLineDashPercentageX10;
    result = (37 * result) + sideBlockLineWidth;

    // mainline values
    result = (37 * result) + mainBallastWidth;
    result = (37 * result) + (mainBallastColor == null ? 0 : mainBallastColor.hashCode());
    result = (37 * result) + mainTieLength;
    result = (37 * result) + (mainTieColor == null ? 0 : mainTieColor.hashCode());
    result = (37 * result) + mainTieWidth;
    result = (37 * result) + mainTieGap;
    result = (37 * result) + mainRailCount;
    result = (37 * result) + mainRailWidth;
    result = (37 * result) + mainRailGap;
    result = (37 * result) + (mainRailColor == null ? 0 : mainRailColor.hashCode());
    result = (37 * result) + mainBlockLineDashPercentageX10;
    result = (37 * result) + mainBlockLineWidth;
#endif
    return result;
}

