#ifndef JMRIPREFERENCESPROVIDER_H
#define JMRIPREFERENCESPROVIDER_H

#include <QObject>
#include <QHash>
#include "abstractpreferences.h"

class Preferences;
class Profile;
class Logger;
class File;
class JmriPreferences;
class JmriPreferencesProvider : public QObject
{
 Q_OBJECT
public:
 //explicit JmriPreferencesProvider(QObject *parent = 0);
 /*public*/ static Preferences* getPreferences(/*final*/ Profile* project, /*final*/ char* clazz, /*final*/ bool shared);
 /*public*/ static Preferences* getPreferences(/*final*/ Profile* project, /*final*/ QString pkg, /*final*/ bool shared);
 QT_DEPRECATED/*public*/ static Preferences* getPreferences(/*final*/ /*@Nonnull*/ File* path, /*@Nullable*/ /*final*/ char* clazz, /*final*/ bool shared);
 JmriPreferencesProvider(File* path, bool shared);
 /*public*/ bool isFirstUse();
 /*public*/ static QString findCNBForClass(/*@Nonnull*/ QString cls);

signals:

public slots:

private:
 /*private*/ /*final*/ JmriPreferences* root;
 /*private*/ /*final*/ File* path;
 /*private*/ /*final*/ bool firstUse;
 /*private*/ /*final*/ bool shared;
 /*private*/ bool backedUp;// = false;
 /*private*/ static /*final*/ QHash<File*, JmriPreferencesProvider*>* sharedProviders;// = new HashMap<>();
 /*private*/ static /*final*/ QHash<File*, JmriPreferencesProvider*>* privateProviders;// = new HashMap<>();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("JmriPreferencesProvider");

static /*synchronized*/ JmriPreferencesProvider* findProvider(File* path, bool shared);
Preferences* getPreferences(/*final*/ char* clazz);
Preferences* getPreferences(/*final*/ QString pkg);
File* getPreferencesFile();
/*private*/ File* getPreferencesDirectory();

protected:
/*protected*/ bool isBackedUp();
/*protected*/ void setBackedUp(bool backedUp);
 friend class JmriPreferences;
};

/*private*/ class JmriPreferences : public AbstractPreferences
{
 Q_OBJECT
    /*private*/ /*final*/static  Logger* log;// = LoggerFactory.getLogger(JmriPreferences.class);

    /*private*/ QMap<QString, QString>* root;
    /*private*/ QMap<QString, JmriPreferences*>* children;
    /*private*/ bool _isRemoved;// = false;
 JmriPreferencesProvider* jpp;
public:
    /*public*/ JmriPreferences(AbstractPreferences* parent, QString name, JmriPreferencesProvider* jpp);
protected:
    /*protected*/ void putSpi(QString key, QString value) ;
    /*protected*/ QString getSpi(QString key);
    /*protected*/ void removeSpi(QString key);
    /*protected*/ void removeNodeSpi() throw (BackingStoreException);
    /*protected*/ QStringList keysSpi() throw (BackingStoreException);
    /*protected*/ QStringList childrenNamesSpi() throw (BackingStoreException);
    /*protected*/ JmriPreferences* childSpi(QString name);
    /*protected*/ void syncSpi() throw (BackingStoreException);
    /*protected*/ void flushSpi() throw (BackingStoreException);

private:
    /*private*/ void getPath(QString* sb);
};

#endif // JMRIPREFERENCESPROVIDER_H
