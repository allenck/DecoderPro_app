#include "layouttrackdrawingoptionsxml.h"
#include "loggerfactory.h"
#include "colorutil.h"
#include "layouttrackdrawingoptions.h"
#include "layouteditor.h"

/**
 * This module handles saving and loading LayoutTrackDrawingOptions for a
 * LayoutEditor.
 *
 * @author George Warner Copyright (c) 2017-2018
 */
// /*public*/ class LayoutTrackDrawingOptionsXml extends AbstractXmlAdapter {

/*public*/ LayoutTrackDrawingOptionsXml::LayoutTrackDrawingOptionsXml(QObject* parent) : AbstractXmlAdapter(parent)
{
}

/**
 * Default implementation for storing LayoutTrackDrawingOptions contents
 *
 * @param o Object to store, of type LayoutTrackDrawingOptions
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement LayoutTrackDrawingOptionsXml::store(QObject* o) {

    LayoutTrackDrawingOptions* p = (LayoutTrackDrawingOptions*) o;

    QDomElement element = doc.createElement("layoutTrackDrawingOptions");

    // include attributes
    element.setAttribute("name", p->getName());

    // add elements
    element.appendChild(doc.createElement("mainBallastColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getMainBallastColor()))));
    element.appendChild(doc.createElement("mainBallastWidth").appendChild(doc.createTextNode(QString::number(p->getMainBallastWidth()))));
    element.appendChild(doc.createElement("mainBlockLineDashPercentageX10").appendChild(doc.createTextNode(QString::number(p->getMainBlockLineDashPercentageX10()))));
    element.appendChild(doc.createElement("mainBlockLineWidth").appendChild(doc.createTextNode(QString::number(p->getMainBlockLineWidth()))));
    element.appendChild(doc.createElement("mainRailColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getMainRailColor()))));
    element.appendChild(doc.createElement("mainRailCount").appendChild(doc.createTextNode(QString::number(p->getMainRailCount()))));
    element.appendChild(doc.createElement("mainRailGap").appendChild(doc.createTextNode(QString::number(p->getMainRailGap()))));
    element.appendChild(doc.createElement("mainRailWidth").appendChild(doc.createTextNode(QString::number(p->getMainRailWidth()))));
    element.appendChild(doc.createElement("mainTieColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getMainTieColor()))));
    element.appendChild(doc.createElement("mainTieGap").appendChild(doc.createTextNode(QString::number(p->getMainTieGap()))));
    element.appendChild(doc.createElement("mainTieLength").appendChild(doc.createTextNode(QString::number(p->getMainTieLength()))));
    element.appendChild(doc.createElement("mainTieWidth").appendChild(doc.createTextNode(QString::number(p->getMainTieWidth()))));

    element.appendChild(doc.createElement("sideBallastColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getSideBallastColor()))));
    element.appendChild(doc.createElement("sideBallastWidth").appendChild(doc.createTextNode(QString::number(p->getSideBallastWidth()))));
    element.appendChild(doc.createElement("sideBlockLineDashPercentageX10").appendChild(doc.createTextNode(QString::number(p->getSideBlockLineDashPercentageX10()))));
    element.appendChild(doc.createElement("sideBlockLineWidth").appendChild(doc.createTextNode(QString::number(p->getSideBlockLineWidth()))));
    element.appendChild(doc.createElement("sideRailColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getSideRailColor()))));
    element.appendChild(doc.createElement("sideRailCount").appendChild(doc.createTextNode(QString::number(p->getSideRailCount()))));
    element.appendChild(doc.createElement("sideRailGap").appendChild(doc.createTextNode(QString::number(p->getSideRailGap()))));
    element.appendChild(doc.createElement("sideRailWidth").appendChild(doc.createTextNode(QString::number(p->getSideRailWidth()))));
    element.appendChild(doc.createElement("sideTieColor").appendChild(doc.createTextNode(ColorUtil::colorToHexString(p->getSideTieColor()))));
    element.appendChild(doc.createElement("sideTieGap").appendChild(doc.createTextNode(QString::number(p->getSideTieGap()))));
    element.appendChild(doc.createElement("sideTieLength").appendChild(doc.createTextNode(QString::number(p->getSideTieLength()))));
    element.appendChild(doc.createElement("sideTieWidth").appendChild(doc.createTextNode(QString::number(p->getSideTieWidth()))));

    element.setAttribute("class", /*getClass().getName()*/ "jmri.jmrit.display.layoutEditor.configurexml.LayoutTrackDrawingOptionsXml");
    return element;
}

//@Override
/*public*/ bool LayoutTrackDrawingOptionsXml::load(QDomElement /*shared*/, QDomElement /*perNode*/) {
    log->error("Invalid method called");
    return false;
}

/**
 * Load, starting with the layoutTrackDrawingOptions element, then all the
 * other data
 *
 * @param QDomElement Top level QDomElement to unpack.
 * @param o       LayoutEditor as an Object
 */
//@Override
/*public*/ void LayoutTrackDrawingOptionsXml::load(QDomElement element, QObject* o) throw (Exception) {
    // create the objects
    LayoutEditor* p = (LayoutEditor*) o;

    // get the current LayoutTrackDrawingOptions
    LayoutTrackDrawingOptions* ltdo = p->getLayoutTrackDrawingOptions();

    // set its name
    QString name = element.attribute("name");
    ltdo->setName(name);

    // get remaining option elements
    ltdo->setMainBallastColor(getElementColor(element, "mainBallastColor", ltdo->getMainBallastColor()));
    ltdo->setMainBallastWidth(getElementInt(element, "mainBallastWidth", ltdo->getMainBallastWidth()));
    ltdo->setMainBlockLineDashPercentageX10(getElementInt(element, "mainBlockLineDashPercentageX10", ltdo->getMainBlockLineDashPercentageX10()));
    ltdo->setMainBlockLineWidth(getElementInt(element, "mainBlockLineWidth", ltdo->getMainBlockLineWidth()));
    ltdo->setMainRailColor(getElementColor(element, "mainRailColor", ltdo->getMainRailColor()));
    ltdo->setMainRailCount(getElementInt(element, "mainRailCount", ltdo->getMainRailCount()));
    ltdo->setMainRailGap(getElementInt(element, "mainRailGap", ltdo->getMainRailGap()));
    ltdo->setMainRailWidth(getElementInt(element, "mainRailWidth", ltdo->getMainRailWidth()));
    ltdo->setMainTieColor(getElementColor(element, "mainTieColor", ltdo->getMainTieColor()));
    ltdo->setMainTieGap(getElementInt(element, "mainTieGap", ltdo->getMainTieGap()));
    ltdo->setMainTieLength(getElementInt(element, "mainTieLength", ltdo->getMainTieLength()));
    ltdo->setMainTieWidth(getElementInt(element, "mainTieWidth", ltdo->getMainTieWidth()));

    ltdo->setSideBallastColor(getElementColor(element, "sideBallastColor", ltdo->getSideBallastColor()));
    ltdo->setSideBallastWidth(getElementInt(element, "sideBallastWidth", ltdo->getSideBallastWidth()));
    ltdo->setSideBlockLineDashPercentageX10(getElementInt(element, "sideBlockLineDashPercentageX10", ltdo->getSideBlockLineDashPercentageX10()));
    ltdo->setSideBlockLineWidth(getElementInt(element, "sideBlockLineWidth", ltdo->getSideBlockLineWidth()));
    ltdo->setSideRailColor(getElementColor(element, "sideRailColor", ltdo->getSideBallastColor()));
    ltdo->setSideRailCount(getElementInt(element, "sideRailCount", ltdo->getSideRailCount()));
    ltdo->setSideRailGap(getElementInt(element, "sideRailGap", ltdo->getSideRailGap()));
    ltdo->setSideRailWidth(getElementInt(element, "sideRailWidth", ltdo->getSideRailWidth()));
    ltdo->setSideTieColor(getElementColor(element, "sideTieColor", ltdo->getSideTieColor()));
    ltdo->setSideTieGap(getElementInt(element, "sideTieGap", ltdo->getSideTieGap()));
    ltdo->setSideTieLength(getElementInt(element, "sideTieLength", ltdo->getSideTieLength()));
    ltdo->setSideTieWidth(getElementInt(element, "sideTieWidth", ltdo->getSideTieWidth()));

    p->setLayoutTrackDrawingOptions(ltdo);
}	// load

//@CheckReturnValue
/*private*/ QColor LayoutTrackDrawingOptionsXml::getElementColor(/*@Nonnull*/ QDomElement el, /*@Nonnull*/ QString child, /*@Nullable */QColor defVal) {
    QDomElement c = el.firstChildElement(child);
    if (!c.isNull()) {
        QString val = c.text();
        if ((val != nullptr) && !val.isEmpty()) {
            //defVal = Color.decode(val);
         int intval = val.toInt(nullptr,16);
                 return QColor((intval >> 16) & 0xFF, (intval >> 8) & 0xFF, intval & 0xFF);
        }
    }
    return defVal;
}

int LayoutTrackDrawingOptionsXml::getElementInt(QDomElement el, QString child, int defVal) {
    QDomElement c = el.firstChildElement(child);
    if (!c.isNull()) {
        QString val = c.text();
        if ((val != nullptr) && !val.isEmpty()) {
            defVal = (val.toInt());
        }
    }
    return defVal;
}

/*private*/ /*final*/ /*static*/ Logger* LayoutTrackDrawingOptionsXml::log = LoggerFactory::getLogger("LayoutTrackDrawingOptionsXml");

