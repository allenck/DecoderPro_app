#include "layoutsingleslipviewxml.h"

/**
 * This module handles configuration for display.LayoutSlipView objects for a
 * LayoutEditor.
 *
 * @author Bob Jacobsen Copyright (c) 2020
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2018
 */
//public class LayoutSingleSlipViewXml extends LayoutSlipViewXml {

/*public*/ LayoutSingleSlipViewXml::LayoutSingleSlipViewXml(QObject *parent) : LayoutSlipViewXml(parent)
{
}

//@Override
/*protected*/ void LayoutSingleSlipViewXml::addClass(QDomElement element) {
    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutSingleSlipXml");
}

// private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutSingleSlipViewXml.class);
