#ifndef PROFILEUTILS_H
#define PROFILEUTILS_H

#include <QObject>

class Preferences;
class Profile;
class AuxiliaryConfiguration;
class ProfileUtils : public QObject
{
 Q_OBJECT
public:
 //explicit ProfileUtils(QObject *parent = 0);
 /*public*/ static AuxiliaryConfiguration* getAuxiliaryConfiguration(Profile* project);
 /*public*/ static AuxiliaryConfiguration* getUserInterfaceConfiguration(Profile* project);
 /*public*/ static Preferences* getPreferences(Profile* project, QString clazz, bool shared);

signals:

public slots:
};

#endif // PROFILEUTILS_H
