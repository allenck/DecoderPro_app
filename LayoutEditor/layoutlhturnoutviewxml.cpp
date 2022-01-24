#include "layoutlhturnoutviewxml.h"

/**
 * This module handles configuration for display.LayoutTurnoutView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2019
 */
//public class LayoutLHTurnoutViewXml extends LayoutTurnoutViewXml {

/*public*/ LayoutLHTurnoutViewXml::LayoutLHTurnoutViewXml(QObject *parent) : LayoutTurnoutViewXml(parent)
{
}

//@Override
/*protected*/ void LayoutLHTurnoutViewXml::addClass(QDomElement element) {
    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutLHTurnoutXml");
}

// private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutLHTurnoutViewXml.class);
