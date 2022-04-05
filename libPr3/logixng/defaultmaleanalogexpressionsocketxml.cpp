#include "defaultmaleanalogexpressionsocketxml.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/ class DefaultMaleAnalogExpressionSocketXml extends AbstractMaleSocketXml {
DefaultMaleAnalogExpressionSocketXml::DefaultMaleAnalogExpressionSocketXml(QObject *parent) : AbstractMaleSocketXml(parent)
{

}
/*public*/ QString DefaultMaleAnalogExpressionSocketXml::getClassName(){
 return "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleAnalogExpressionSocketXml";
}
