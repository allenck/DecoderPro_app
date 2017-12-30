#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include "file.h"
#include "javaqt_global.h"
#include "exceptions.h"

class File;
class JAVAQTSHARED_EXPORT Profile : public QObject
{
    Q_OBJECT
public:
    Profile(File* path, QObject *parent = 0) throw (IOException);
    /*public*/ Profile(QString name, QString id, File* path, QObject *parent = 0);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    /*public*/ QString getId();
    /*public*/ File* getPath();
    /*public*/ QString toString();
    /*public*/ bool equals(QObject* obj);
    /*public*/ bool isComplete();
    /*public*/ QString getUniqueId();
    /*public*/ static bool containsProfile(File* path);
    /*public*/ static bool inProfile(File* path);
    /*public*/ static bool isProfile(File* path);
    /*public*/ static /*final*/ QString CONFIG_FILENAME;// = "ProfileConfig.xml"; // NOI18N
 /*public*/ static /*final*/ QString PROFILE;// = "profile"; // NOI18N
 /*public*/ static /*final*/ QString PROPERTIES;// = "profile.properties"; // NOI18N
 /*public*/ static /*final*/ QString CONFIG;// = "profile.xml"; // NOI18N
 /*public*/ static /*final*/ QString SHARED_PROPERTIES;// = PROFILE + "/" + PROPERTIES; // NOI18N
 /*public*/ static /*final*/ QString SHARED_CONFIG;// = PROFILE + "/" + CONFIG; // NOI18N
 /*public*/ static /*final*/ QString UI_CONFIG;// = "user-interface.xml"; // NOI18N
 /*public*/ static /*final*/ QString SHARED_UI_CONFIG;// = PROFILE + "/" + UI_CONFIG; // NOI18N
 /*public*/ static /*final*/ QString UI_CONFIG_FILENAME;// = "UserPrefsProfileConfig.xml"; // NOI18N

signals:

public slots:
private:
    void common(File* path, bool isReadable);
    /*private*/ QString name;
    /*private*/ QString id;
    /*private*/ File* path;
    /*private*/ void readProfile();
 QT_DEPRECATED /*private*/ void readProfileXml() throw (IOException);

protected:
 /*protected*/ Profile(File* path, bool isReadable, QObject *parent = 0);
    /*protected*/ static /*final*/ QString ID;// = "id"; // NOI18N
    /*protected*/ static /*final*/ QString NAME;// = "name"; // NOI18N
    /*protected*/ static /*final*/ QString PATH;// = "path"; // NOI18N
    /*protected*/ Profile(/*@Nonnull*/ File* path, /*@Nonnull*/ QString id, bool isReadable, QObject* parent = 0) throw (IOException);
    /*protected*/ /*final*/ void save() throw (IOException);

 friend class ProfileManager;
 friend class ProfileManagerDialog;
 friend class AddProfileDialog;
 friend class ProfilePreferencesPanel;
};

#endif // PROFILE_H
