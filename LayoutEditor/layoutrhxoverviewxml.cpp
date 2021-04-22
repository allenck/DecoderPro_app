#include "layoutrhxoverviewxml.h"


/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
///*public*/ class LayoutRHXOverViewXml extends LayoutXOverViewXml {

    /*public*/ LayoutRHXOverViewXml::LayoutRHXOverViewXml(QObject *parent) : LayoutXOverViewXml(parent){
    }

    //@Override
    /*protected*/ void LayoutRHXOverViewXml::addClass(QDomElement element) {
        element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutRHXOverXml");
    }
