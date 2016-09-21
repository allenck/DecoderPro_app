#ifndef ABSTRACTCONFIGURATIONPROVIDER_H
#define ABSTRACTCONFIGURATIONPROVIDER_H

#include <QObject>
class Profile;
class AuxiliaryConfiguration;
class File;
class AbstractConfigurationProvider : public QObject
{
 Q_OBJECT
public:
 explicit AbstractConfigurationProvider(Profile* project, QObject *parent = 0);
 /*public*/ File* getConfigurationDirectory(bool shared);

signals:

public slots:
private:
 /*private*/ bool privateBackedUp;// = false;
 /*private*/ bool sharedBackedUp;// = false;

protected:
 /*protected*/ /*final*/ Profile* project;
 /*protected*/ /*abstract*/ virtual AuxiliaryConfiguration* getConfiguration();
 /*protected*/ /*abstract*/ virtual File* getConfigurationFile(bool shared);
 /*protected*/ bool isPrivateBackedUp();
 /*protected*/ void setPrivateBackedUp(bool privateBackedUp);
 /*protected*/ bool isSharedBackedUp();
 /*protected*/ void setSharedBackedUp(bool sharedBackedUp);

};

#endif // ABSTRACTCONFIGURATIONPROVIDER_H
