#include "layoutxoverviewxml.h"

/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
// /*public*/ class LayoutXOverViewXml extends LayoutTurnoutViewXml {

    /*public*/ LayoutXOverViewXml::LayoutXOverViewXml(QObject* parent) : LayoutTurnoutViewXml(parent) {
    }

    //@Override
    /*protected*/ void LayoutXOverViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutXOverXml");
    }
    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutXOverViewXml.class);

