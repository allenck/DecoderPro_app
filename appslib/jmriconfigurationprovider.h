#ifndef JMRICONFIGURATIONPROVIDER_H
#define JMRICONFIGURATIONPROVIDER_H

#include "abstractconfigurationprovider.h"
#include "jmriconfiguration.h"

class JmriConfiguration;
class JmriConfigurationProvider : public AbstractConfigurationProvider
{
public:
 JmriConfigurationProvider(Profile*);
 /*public*/ static /*final*/ QString NAMESPACE;// = "http://www.netbeans.org/ns/auxiliary-configuration/1"; // NOI18N
 /*public*/ static AuxiliaryConfiguration* getConfiguration(/*final*/ Profile* project);

  private:
 /*private*/ class Configuration : public JmriConfiguration {

     /*private*/ Configuration(JmriConfigurationProvider* provider) ;
  JmriConfigurationProvider* provider;
 protected:
     /*protected*/ virtual File* getConfigurationFile(bool shared);
     /*protected*/ virtual bool isSharedBackedUp();
     /*protected*/ virtual void setSharedBackedUp(bool backedUp);
     /*protected*/ virtual bool isPrivateBackedUp();
     /*protected*/ virtual void setPrivateBackedUp(bool backedUp);
  friend class JmriConfigurationProvider;
 };
 /*private*/ /*final*/ JmriConfiguration* configuration;
 /*private*/ static /*final*/ QMap<Profile*, JmriConfigurationProvider*> providers;// = new HashMap<>();
 static /*synchronized*/ JmriConfigurationProvider* findProvider(Profile* project);
protected:
 /*protected*/ AuxiliaryConfiguration* getConfiguration();
 /*protected*/ File* getConfigurationFile(bool shared);

};

#endif // JMRICONFIGURATIONPROVIDER_H
