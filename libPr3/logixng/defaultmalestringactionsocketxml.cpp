#include "defaultmalestringactionsocketxml.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/ class DefaultMaleStringActionSocketXml extends AbstractMaleSocketXml {
DefaultMaleStringActionSocketXml::DefaultMaleStringActionSocketXml(QObject *parent) : AbstractMaleSocketXml(parent)
{

}
/*public*/ QString DefaultMaleStringActionSocketXml::getClassName(){
 return "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleStringActionSocketXml";
}
