#include "layoutlhxoverviewxml.h"

/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
// /*public*/ class LayoutLHXOverViewXml extends LayoutXOverViewXml {

    LayoutLHXOverViewXml::LayoutLHXOverViewXml(QObject *parent) : LayoutXOverViewXml(parent){
    }

    //@Override
    /*protected*/ void LayoutLHXOverViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutLHXOverXml");
    }
