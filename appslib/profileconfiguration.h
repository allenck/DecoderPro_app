#ifndef PROFILECONFIGURATION_H
#define PROFILECONFIGURATION_H
#include "auxiliaryconfiguration.h"
#include <QDomElement>

class Profile;
class ProfileConfiguration : public AuxiliaryConfiguration
{
    Q_OBJECT
public:
    /*public*/ ProfileConfiguration(Profile* project, QObject* parent = nullptr);
    /*public*/ QDomElement getConfigurationFragment(QString elementName, QString _namespace, bool shared);
    /*public*/ void putConfigurationFragment(QDomElement fragment, bool shared);
    /*public*/ bool removeConfigurationFragment(QString elementName, QString _namespace, bool shared);


private:
    /*private*/ /*final*/ Profile* project;

};

#endif // PROFILECONFIGURATION_H
