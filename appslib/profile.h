#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include "file.h"
#include "javaqt_global.h"
#include "exceptions.h"

class Logger;
class File;
class JAVAQTSHARED_EXPORT Profile : public QObject
{
    Q_OBJECT
public:
 /*public*/ static /*final*/ QString EXTENSION;// = ".jmri"; // NOI18N

    Profile(File* path, QObject *parent = 0) /*throw (IOException)*/;
    /*public*/ Profile(QString name, QString id, File* path, QObject *parent = 0) throw (IOException, IllegalArgumentException);
    /*public*/ QString getName();
    /*public*/ void setName(QString name);
    /*public*/ QString getId() const;
    /*public*/ File* getPath();
    /*public*/ virtual QString toString();
//    /*public*/ virtual int hashCode();
    inline bool operator==(const Profile &e1)
    {
       return this->id == e1.id;
    }
//    inline uint qHash(const Profile &key, uint seed)
//    {
//        return qHash(key.getId(), seed);
//    }
    /*public*/ virtual bool equals(QObject* obj);
    /*public*/ virtual bool isComplete();
    /*public*/ virtual QString getUniqueId();
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
    /*public*/ virtual int compareTo(Profile* o);

signals:

public slots:
private:
    /*private*/ static Logger* log;// = new LoggerFactory::getLogger("Profile");
    void common(File* path, bool isReadable);
    /*private*/ QString name;
    /*private*/ QString id;
    /*private*/ File* path;
    /*private*/ void readProfile();

protected:
    /*protected*/ Profile(File* path, bool isReadable, QObject *parent = 0);
    /*protected*/ static /*final*/ QString ID;// = "id"; // NOI18N
    /*protected*/ static /*final*/ QString NAME;// = "name"; // NOI18N
    /*protected*/ static /*final*/ QString PATH;// = "path"; // NOI18N
    /*protected*/ Profile(/*@Nonnull*/ File* path, /*@Nonnull*/ QString id, bool isReadable, QObject* parent = 0) /*throw (IOException)*/;
    /*protected*/ /*final*/ void save() /*throw (IOException)*/;
    /*protected*/ /*final*/ void setNameInConstructor(QString name);

 friend class ProfileManager;
 friend class ProfileManagerDialog;
 friend class AddProfileDialog;
 friend class ProfilePreferencesPanel;
 friend class ProfileTest;
 friend class ProfileUtilsTest;
 friend class ProfileUtils;
 friend class NullProfile;
 friend class PMDPropertyChangeListener2;
 friend class FileUtilSupport;
};

#endif // PROFILE_H
