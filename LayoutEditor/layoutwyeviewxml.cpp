#include "layoutwyeviewxml.h"

/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
//public class LayoutWyeViewXml extends LayoutTurnoutViewXml {

/*public*/ LayoutWyeViewXml::LayoutWyeViewXml(QObject *parent) : LayoutTurnoutViewXml(parent) {
}

//@Override
/*protected*/ void LayoutWyeViewXml::addClass(QDomElement element) {
    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutWyeXml");
}

// private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutWyeViewXml.class);
