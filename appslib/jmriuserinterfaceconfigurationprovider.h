#ifndef JMRIUSERINTERFACECONFIGURATIONPROVIDER_H
#define JMRIUSERINTERFACECONFIGURATIONPROVIDER_H

#include "abstractconfigurationprovider.h"
#include "jmriconfiguration.h"
class Configuration;
class JmriUserInterfaceConfigurationProvider : public AbstractConfigurationProvider
{
public:
 JmriUserInterfaceConfigurationProvider(Profile* project);
 /*public*/ static /*final*/ QString NAMESPACE;// = "http://www.netbeans.org/ns/auxiliary-configuration/1"; // NOI18N
 /*public*/ static AuxiliaryConfiguration* getConfiguration(/*final*/ Profile* project);

private:
 /*private*/ class Configuration : public JmriConfiguration
 {
  JmriUserInterfaceConfigurationProvider* provider;
 public:
     /*private*/ Configuration(JmriUserInterfaceConfigurationProvider* provider);
 protected:
     /*protected*/ virtual File* getConfigurationFile(bool shared);
     /*protected*/ virtual bool isSharedBackedUp();
     /*protected*/ virtual void setSharedBackedUp(bool backedUp);
     /*protected*/ virtual bool isPrivateBackedUp();
     /*protected*/ virtual void setPrivateBackedUp(bool backedUp);
 };
 /*private*/ /*final*/ Configuration* configuration;
 /*private*/ static /*final*/ QMap<Profile*, JmriUserInterfaceConfigurationProvider*> providers;// = new HashMap<>();
 static /*synchronized*/ JmriUserInterfaceConfigurationProvider* findProvider(Profile* project);
protected:
 /*protected*/ AuxiliaryConfiguration* getConfiguration();
 /*protected*/ File* getConfigurationFile(bool shared);


};

#endif // JMRIUSERINTERFACECONFIGURATIONPROVIDER_H
