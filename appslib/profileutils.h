#ifndef PROFILEUTILS_H
#define PROFILEUTILS_H

#include <QObject>
#include "exceptions.h"

class Logger;
class Preferences;
class Profile;
class AuxiliaryConfiguration;
class ProfileUtils : public QObject
{
 Q_OBJECT
public:
 //explicit ProfileUtils(QObject *parent = 0);
 /*public*/ static void copy(Profile* source, Profile* destination) throw (IllegalArgumentException, IOException );
 /*public*/ static bool copyPrivateContentToCurrentIdentity(/*@Nonnull*/ Profile* profile) throw (IOException);
 /*public*/ static AuxiliaryConfiguration* getAuxiliaryConfiguration(Profile* project);
 /*public*/ static AuxiliaryConfiguration* getUserInterfaceConfiguration(Profile* project);
 /*public*/ static Preferences* getPreferences(Profile* project, QString clazz, bool shared);

signals:

public slots:
private:
 static Logger* log;
};

#endif // PROFILEUTILS_H
