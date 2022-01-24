#include "layoutdoubleslipviewxml.h"

/**
 * This module handles configuration for display.LayoutSlipView objects for a
 * LayoutEditor.
 *
 * @author David Duchamp Copyright (c) 2007
 * @author George Warner Copyright (c) 2017-2018
 */
//public class LayoutDoubleSlipViewXml extends LayoutSlipViewXml {

/*public*/ LayoutDoubleSlipViewXml::LayoutDoubleSlipViewXml(QObject *parent) : LayoutSlipViewXml((parent))
{
}

//@Override
/*protected*/ void LayoutDoubleSlipViewXml::addClass(QDomElement element) {
    element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutDoubleSlipXml");
}

// private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutDoubleSlipViewXml.class);
