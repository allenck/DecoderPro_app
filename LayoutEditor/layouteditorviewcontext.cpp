#include "layouteditorviewcontext.h"

/**
 * LayoutEditorViewContext is a memo object containing
 * the graphical View context information for a {@link LayoutEditor} MVC instance.
 * <p>
 * As a memo class, this may contain methods, but the class cannot include
 * references to other classes, and ideally the methods won't use references
 * to other classes. Just data, and operations on that data.
 * <p>
 * This should map to a subset of the variables stored and loaded by
 * {@link jmri.jmrit.display.layoutEditor.configurexml.LayoutEditorXml}
 * and the XML Schema for the LayoutEditor element.
 * <p>
 * This holds <u>graphical View</u> context information.
 * It should <u>not</u> include Model (e.g. layout hardware, even global values)
 * or Control (e.g. options affecting the operation of the editor) information.
 * <p>
 * It's OK for this to hold startup default values for the quantities.
 * <p>
 * This may be a temporary class, only existing to help
 * build a better structure into this package.
 *
 * @author Bob Jacobsen Copyright (C) 2020
 */
// /*final*/ /*public*/ class LayoutEditorViewContext {

    LayoutEditorViewContext::LayoutEditorViewContext(QObject *parent) : QObject(parent) {}  // intentionally package-protected to limit exposure

    // -----------------------------------
    // Sides and positions
    // -----------------------------------

    /*final*/ /*public*/ void LayoutEditorViewContext::setLayoutWidth(int width) {
        panelWidth = width;
    }
    /*final*/ /*public*/ int LayoutEditorViewContext::getLayoutWidth() {
        return panelWidth;
    }

    /*final*/ /*public*/ void LayoutEditorViewContext::setLayoutHeight(int height) {
        panelHeight = height;
    }
    /*final*/ /*public*/ int LayoutEditorViewContext::getLayoutHeight() {
        return panelHeight;
    }

    /*final*/ /*public*/ void LayoutEditorViewContext::setWindowWidth(int width) {
        windowWidth = width;
    }
    /*final*/ /*public*/ int LayoutEditorViewContext::getWindowWidth() {
        return windowWidth;
    }

    /*final*/ /*public*/ void LayoutEditorViewContext::setWindowHeight(int height) {
        windowHeight = height;
    }
    /*final*/ /*public*/ int LayoutEditorViewContext::getWindowHeight() {
        return windowHeight;
    }

    // Window upper left x, not panel upper left x
    /*final*/ /*public*/ int LayoutEditorViewContext::getUpperLeftX() {
        return upperLeftX;
    }
    /*final*/ /*public*/ void LayoutEditorViewContext::setUpperLeftX(int x) {
        upperLeftX = x;
    }

    // Window upper left y, not panel upper left y
    /*final*/ /*public*/ int LayoutEditorViewContext::getUpperLeftY() {
        return upperLeftY;
    }
    /*final*/ /*public*/ void LayoutEditorViewContext::setUpperLeftY(int y) {
        upperLeftY = y;
    }

    /*final*/ /*public*/ int LayoutEditorViewContext::setGridSize(int newSize) {
        gridSize1st = newSize;
        return gridSize1st;
    }

    /**
     * Get the width drawing the grid; 10 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ int LayoutEditorViewContext::getGridSize() {
        return gridSize1st;
    }

    /*final*/ /*public*/ int LayoutEditorViewContext::setGridSize2nd(int newSize) {
        gridSize2nd = newSize;
        return gridSize2nd;
    }

    /**
     * Get the width for 2nd drawing of the grid; 10 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ int LayoutEditorViewContext::getGridSize2nd() {
        return gridSize2nd;
    }

    // also found in LayoutTrackDrawingOptions?
    // why is this a float?  Needed for Graphics2D arguments?
    /*final*/ /*public*/ void LayoutEditorViewContext::setMainlineTrackWidth(float width) {
        mainlineTrackWidth = (int)width;
    }

    /**
     * Get the width for drawing mainline track; 4 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ int LayoutEditorViewContext::getMainlineTrackWidth() {
        return (int) mainlineTrackWidth;
    }

    /**
     * Set the width for sideline track; note
     * that the stored and retrievable value is an integer.
     * @param width Value to store; will be cast to (int)
     */
    // also found in LayoutTrackDrawingOptions? (temporary?)
    // why is this a float? (temporary?)
    /*final*/ /*public*/ void LayoutEditorViewContext::setSidelineTrackWidth(float width) {
        sidelineTrackWidth = (int)width;
    }

    /**
     * Get the width for drawing sideline track; 2 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ int LayoutEditorViewContext::getSidelineTrackWidth() {
        return (int) sidelineTrackWidth;
    }

    /**
     * Get the X-axis scaling value; 1.0 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ double LayoutEditorViewContext::getXScale() {
        return xScale;
    }
    /*final*/ /*public*/ void LayoutEditorViewContext::setXScale(double scale) {
        xScale = scale;
    }

    /**
     * Get the Y-axis scaling value; 1.0 is the
     * default/initial value.
     * @return current value
     */
    /*final*/ /*public*/ double LayoutEditorViewContext::getYScale() {
        return yScale;
    }
    /*final*/ /*public*/ void LayoutEditorViewContext::setYScale(double scale) {
        yScale = scale;
    }


    // initialize logging
    // /*private*/ /*final*/ static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutEditor.class);

//}

/* ***************************************************

      <xs:attribute name="sliders" type="yesNoType" default="yes"/>
      <xs:attribute name="drawgrid" type="yesNoType" default="yes" />
      <xs:attribute name="antialiasing" type="yesNoType" default="yes" />
      <xs:attribute name="turnoutcircles" type="yesNoType" default="yes" />

      <xs:attribute name="defaulttrackcolor" type="screenColorType" use="required" /> Default about display?
      <xs:attribute name="defaultalternativetrackcolor" type="screenColorType"/>      Or more Controller?
      <xs:attribute name="defaultoccupiedtrackcolor" type="screenColorType"/>
      <xs:attribute name="defaulttextcolor" type="screenColorType"/>

      <xs:attribute name="turnoutcirclecolor" type="turnoutCircleColourType"/>
      <xs:attribute name="turnoutcirclethrowncolor" type="turnoutCircleColourType"/>

      <xs:attribute name="turnoutfillcontrolcircles" type="yesNoType" default="no"/>
      <xs:attribute name="turnoutcirclesize" type="xs:integer"/>
      <xs:attribute name="turnoutdrawunselectedleg" type="yesNoType" default="yes"/>

      <xs:attribute name="turnoutbx" type="xs:float"/>
      <xs:attribute name="turnoutcx" type="xs:float"/>
      <xs:attribute name="turnoutwid" type="xs:float"/>
      <xs:attribute name="xoverlong" type="xs:float"/>
      <xs:attribute name="xoverhwid" type="xs:float"/>
      <xs:attribute name="xovershort" type="xs:float"/>

      <xs:attribute name="redBackground" type="xs:integer"/>
      <xs:attribute name="greenBackground" type="xs:integer"/>
      <xs:attribute name="blueBackground" type="xs:integer"/>

      <xs:attribute name="zoom" type="xs:float" default="1.0"/>


Probably not View graphical:
      <xs:attribute name="name" type="xs:string"/> Is that graphical? Not sure

      <xs:attribute name="scrollable" type="scrollableType" default="both" />
      <xs:attribute name="editable" type="yesNoType" default="yes" />
      <xs:attribute name="positionable" type="yesNoType" default="yes" />
      <xs:attribute name="controlling" type="yesNoType" default="yes" />
      <xs:attribute name="animating" type="yesNoType" default="yes" />
      <xs:attribute name="showhelpbar" type="yesNoType" default="yes" />

      <xs:attribute name="snaponadd" type="yesNoType" default="yes" />
      <xs:attribute name="snaponmove" type="yesNoType" default="yes" />

      <xs:attribute name="tooltipsnotedit" type="yesNoType" default="yes" />
      <xs:attribute name="tooltipsinedit" type="yesNoType" default="yes" />

      <xs:attribute name="autoblkgenerate" type="yesNoType" default="yes"/>

      <xs:attribute name="openDispatcher" type="yesNoType" default="no"/>
      <xs:attribute name="useDirectTurnoutControl" type="yesNoType" default="no"/>

 */
