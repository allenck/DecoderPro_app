#ifndef JMRICONFIGURATION_H
#define JMRICONFIGURATION_H
#include "auxiliaryconfiguration.h"

class Logger;
class File;
class JmriConfiguration : public AuxiliaryConfiguration
{
 Q_OBJECT
public:
 JmriConfiguration();
 /*public*/ QDomElement getConfigurationFragment(/*final*/ QString elementName, /*final*/ QString _namespace, /*final*/ bool shared);
 /*public*/ void putConfigurationFragment(/*final*/ QDomElement fragment, /*final*/ bool shared); //throws IllegalArgumentException
 /*public*/ bool removeConfigurationFragment(/*final*/ QString elementName, /*final*/ QString _namespace, /*final*/ bool shared); //throws IllegalArgumentException
private:
 Logger* log;
 /*private*/ void backup(bool shared);

protected:
 /*protected*/ /*abstract*/ virtual File* getConfigurationFile(bool shared);
 /*protected*/ /*abstract*/ virtual bool isSharedBackedUp();
 /*protected*/ /*abstract*/ virtual void setSharedBackedUp(bool backedUp);
 /*protected*/ /*abstract*/ virtual bool isPrivateBackedUp();
 /*protected*/ /*abstract*/ virtual void setPrivateBackedUp(bool backedUp);

};

#endif // JMRICONFIGURATION_H
