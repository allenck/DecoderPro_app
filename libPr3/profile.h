#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include "file.h"
#include "libPr3_global.h"

class File;
class LIBPR3SHARED_EXPORT Profile : public QObject
{
    Q_OBJECT
public:
    //explicit Profile(QObject *parent = 0);
//    /*public*/ Profile(File path, QObject *parent = 0);
    /*public*/ Profile(QString name, QString id, File* path, QObject *parent = 0);
    /*protected*/ Profile(File* path, bool isReadable = true, QObject *parent = 0);
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

signals:

public slots:
private:
    /*private*/ QString name;
    /*private*/ QString id;
    /*private*/ File* path;
    /*private*/ void readProfile();
protected:
    /*protected*/ static /*final*/ QString ID;// = "id"; // NOI18N
    /*protected*/ static /*final*/ QString NAME;// = "name"; // NOI18N
    /*protected*/ static /*final*/ QString PATH;// = "path"; // NOI18N
    /*protected*/ static /*final*/ QString PROPERTIES;// = "profile.properties"; // NOI18N
    /*protected*/ /*final*/ void save();
 friend class ProfileManager;
 friend class ProfileManagerDialog;
 friend class AddProfileDialog;
};

#endif // PROFILE_H
