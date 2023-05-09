#include "defaultmaledigitalactionsocketxml.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
//public class DefaultMaleDigitalActionSocketXml extends AbstractMaleSocketXml {
DefaultMaleDigitalActionSocketXml::DefaultMaleDigitalActionSocketXml(QObject *parent) : AbstractMaleSocketXml(parent)
{
    setObjectName("DefaultMaleDigitalActionSocketXml");
    setProperty("JavaClassName", getClassName());
}
/*public*/ QString DefaultMaleDigitalActionSocketXml::getClassName(){
 return "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleDigitalActionSocketXml";
}
