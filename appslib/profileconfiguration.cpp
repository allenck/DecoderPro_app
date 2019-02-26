#include "profileconfiguration.h"
#include "jmriconfigurationprovider.h"

/**
 *
 * @author rhwood
 */
//class ProfileConfiguration implements AuxiliaryConfiguration {


/*public*/ ProfileConfiguration::ProfileConfiguration(Profile* project, QObject* parent) : AuxiliaryConfiguration(parent)
{
    this->project = project;
}

//@Override
/*public*/ QDomElement ProfileConfiguration::getConfigurationFragment(QString elementName, QString _namespace, bool shared) {
    return JmriConfigurationProvider::getConfiguration(this->project)->getConfigurationFragment(elementName, _namespace, shared);
}

//@Override
/*public*/ void ProfileConfiguration::putConfigurationFragment(QDomElement fragment, bool shared) {
    JmriConfigurationProvider::getConfiguration(this->project)->putConfigurationFragment(fragment, shared);
}

//@Override
/*public*/ bool ProfileConfiguration::removeConfigurationFragment(QString elementName, QString _namespace, bool shared) {
    return JmriConfigurationProvider::getConfiguration(this->project)->removeConfigurationFragment(elementName, _namespace, shared);
}
