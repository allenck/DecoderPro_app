#include "profile.h"
#include "../appslib/profilemanager.h"
#include "file.h"
#include <QDir>
#include "properties.h"
#include "exceptions.h"
#include "QTextStream"
#include "profileproperties.h"
#include "loggerfactory.h"

/**
 * A JMRI application profile. Profiles allow a JMRI application to load
 * completely separate set of preferences at each launch without relying on host
 * OS-specific tricks to ensure this happens.
 *
 * @author Randall Wood Copyright (C) 2013, 2014
 */
// /*public*/ class Profile {
    /*public*/ /*static final*/ QString Profile::PROFILE = "profile"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _ID, ("id"))
    /*protected*/ /*static final */ QString Profile::ID = "id"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _NAME, ("name"))
    /*protected*/ /*static final */ QString Profile::NAME = "name"; // NOI18N
    /*protected*/ /*static final */ QString Profile::PATH = "path"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _PROPERTIES, ("profile.properties"))
    /*public*/ /*static final */ QString Profile::PROPERTIES = "profile.properties"; // NOI18N
    /*public*/ /*static final*/ QString Profile::CONFIG = "profile.xml"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _SHARED_PROPERTIES, ("profile/profile.properties"))
    /*public*/ /*static final*/ QString Profile::SHARED_PROPERTIES = Profile::PROFILE + "/" + Profile::PROPERTIES; // NOI18N
    /*public*/ /*static final*/ QString Profile::SHARED_CONFIG = Profile::PROFILE + "/" + Profile::CONFIG; // NOI18N
    /*public*/ /*static final */ QString Profile::CONFIG_FILENAME = "ProfileConfig.xml"; // NOI18N
/*public*/ /*static final*/ QString Profile::UI_CONFIG = "user-interface.xml"; // NOI18N
/*public*/ /*static final*/ QString Profile::SHARED_UI_CONFIG = Profile::PROFILE + "/" + Profile::UI_CONFIG; // NOI18N
/*public*/ /*static final*/ QString Profile::UI_CONFIG_FILENAME = "UserPrefsProfileConfig.xml"; // NOI18N
/**
 * The filename extension for JMRI profile directories. This is needed for
 * external applications on some operating systems to recognize JMRI
 * profiles.
 */
/*public*/ /*static*/ /*final*/ QString Profile::EXTENSION = ".jmri"; // NOI18N
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _EXTENSION, (".jmri"))
/**
 * Create a Profile object given just a path to it. The Profile must exist
 * in storage on the computer.
 *
 * @param path The Profile's directory
 * @throws IOException
 */
/**
 * Create a Profile object given just a path to it. The Profile must exist
 * in storage on the computer.
 *
 * @param path The Profile's directory
 * @throws IOException
 */
/*public*/ Profile::Profile(File* path, QObject* parent) throw (IOException)
 : QObject(parent)
{
 common(path, ProfileManager::createUniqueId(), true);
}

/**
 * Create a Profile object and a profile in storage. A Profile cannot exist
 * in storage on the computer at the path given. Since this is a new
 * profile, the id must match the last element in the path->
 * <p>
 * This is the only time the id can be set on a Profile, as the id becomes a
 * read-only property of the Profile:: The {@link ProfileManager} will only
 * load a single profile with a given id.
 *
 * @param name
 * @param id
 * @param path
 * @throws IOException
 * @throws IllegalArgumentException
 */
/*public*/ Profile::Profile(QString name, QString id, File* path, QObject *parent) :
    QObject(parent)
{
 File* pathWithExt; // path with extention
 if (path->getName().endsWith(*_EXTENSION)) {
     pathWithExt = path;
 } else {
     pathWithExt = new File(path->getParentFile(), path->getName() + *_EXTENSION);
 }
 if (pathWithExt->getName() != (id + *_EXTENSION)) {
     throw  IllegalArgumentException(id + " " + path->getName() + " do not match"); // NOI18N
 }
 if (Profile::isProfile(path) || Profile::isProfile(pathWithExt)) {
     throw IllegalArgumentException("A profile already exists at " + path->getPath()); // NOI18N
 }
 if (Profile::containsProfile(path) || Profile::containsProfile(pathWithExt)) {
     throw IllegalArgumentException(path->getPath() + " contains a profile in a subdirectory."); // NOI18N
 }
 if (Profile::inProfile(path) || Profile::inProfile(pathWithExt)) {
     throw IllegalArgumentException(path->getPath() + " is within an existing profile."); // NOI18N
 }
 this->name = name;
 this->id = id + "." + ProfileManager::createUniqueId();
 this->path = pathWithExt;
 // use field, not local variables (path or pathWithExt) for paths below
 if (!this->path->exists() && !this->path->mkdirs()) {
     throw IOException("Unable to create directory " + this->path->getPath()); // NOI18N
 }
 if (!this->path->isDirectory()) {
     throw IllegalArgumentException(path->getPath() + " is not a directory"); // NOI18N
 }
 this->save();
 if (!Profile::isProfile(this->path)) {
     throw  IllegalArgumentException(path->getPath() + " does not contain a profile.properties file"); // NOI18N
 }
}

/**
 * Create a Profile object given just a path to it. If isReadable is true,
 * the Profile must exist in storage on the computer.
 *
 * This method exists purely to support subclasses.
 *
 * @param path The Profile's directory
 * @param isReadable
 * @throws IOException
 */
/*protected*/ Profile::Profile(File* path, bool isReadable, QObject *parent) :
    QObject(parent)
{
 common(path, ProfileManager::createUniqueId(), isReadable);
}

/**
 * Create a Profile object given just a path to it. If isReadable is true,
 * the Profile must exist in storage on the computer.
 * <p>
 * This method exists purely to support subclasses.
 *
 * @param path       The Profile's directory
 * @param id         The Profile's id
 * @param isReadable True if the profile has storage. See
 *                   {@link jmri.profile.NullProfile} for a Profile subclass
 *                   where this is not true.
 * @throws java.io.IOException If the profile's preferences cannot be read.
 */
void Profile::common(File *path, QString id,bool isReadable)
{
 File* pathWithExt; // path with extention
 if (path->getName().endsWith(*_EXTENSION)) {
     pathWithExt = path;
 } else {
     pathWithExt = new File(path->getParentFile(), path->getName() + *_EXTENSION);
 }
 // if path does not exist, but pathWithExt exists, use pathWithExt
 // to support a scenario where user adds .jmri extension to profile
 // directory outside of JMRI application
 if ((!path->exists() && pathWithExt->exists())) {
     this->path = pathWithExt;
 } else {
     this->path = path;
 }
 this->id = id;
 if (isReadable) {
     this->readProfile();
 }
}

/*protected*/ Profile::Profile(/*@Nonnull*/ File* path, /*@Nonnull*/ QString id, bool isReadable, QObject* parent) throw (IOException) : QObject(parent)
{
 common(path, id, isReadable);

}

/*protected*/ /*final*/ void Profile::save() throw (IOException)
{
 Properties* p = new Properties();
#if 1
    File* f = new File(this->path, *_PROPERTIES);
    QTextStream* os = NULL;

    p->setProperty(*_NAME, this->name);
    p->setProperty(*_ID, this->id);
    if (!f->exists() && !f->createNewFile()) {
        //throw new IOException("Unable to create file at " + f.getAbsolutePath()); // NOI18N
     Logger::error("Unable to create file at " + f->getAbsolutePath());
    }
    try {
        QFile* ff = new QFile(f->getAbsolutePath());
        if(!ff->open(QIODevice::WriteOnly))
        {
         Logger::error("can not open file write only " + f->getAbsolutePath());
         return;
        }
        os = new QTextStream(ff);
        p->storeToXML(os, "JMRI Profile"); // NOI18N
        //os->close();
    } catch (IOException ex) {
        if (os != NULL) {
            //os->close();
        }
        //throw ex;
    }
#endif
}

/**
 * @return the name
 */
/*public*/ QString Profile::getName() {
    return name;
}

/*public*/ void Profile::setName(QString name) {
    QString oldName = this->name;
    this->name = name;
ProfileManager::defaultManager()->profileNameChange(this, oldName);
}

/**
 * @return the id
 */
/*public*/ QString Profile::getId()
{
 return id;
}

/**
 * @return the path
 */
/*public*/ File* Profile::getPath() {
    return path;
}

/*private*/ void Profile::readProfile()
{
 ProfileProperties* p = new ProfileProperties(this->path);

 this->id = p->get(*_ID, true);
 this->name = p->get(*_NAME, true);
 if (this->id == NULL)
 {
  this->readProfileXml();
  this->save();
 }
}

/**
 * @deprecated since 4.1.1; Remove sometime after the new profiles get
 * entrenched (JMRI 5.0, 6.0?)
 */
//@Deprecated
/*private*/ void Profile::readProfileXml() throw (IOException) {
    Properties* p = new Properties();
    File* f = new File(this->path, /*PROPERTIES*/"profile.properties");
    //FileInputStream is = null;
    QFile* ff = new QFile(f->getPath());
    if(!ff->open(QIODevice::ReadOnly))
     throw IOException(tr("File not found: %1").arg(f->getPath()));
    QTextStream* is;
    try {
        is = new QTextStream(ff);
        p->loadFromXML(is);
        ff->close();
    } catch (IOException ex) {
        if (is != NULL) {
            ff->close();
        }
        throw ex;
    }
    this->id = p->getProperty("id");
    this->name = p->getProperty("name");
}

//@Override
/*public*/ QString Profile::toString() {
    return this->getName();
}

//@Override
///*public*/ int hashCode() {
//    int hash = 7;
//    hash = 71 * hash + (this->id != NULL ? this->id.hashCode() : 0);
//    return hash;
//}

//@Override
/*public*/ bool Profile::equals(QObject* obj) {
    if (obj == NULL) {
        return false;
    }
    if (metaObject()->className() != obj->metaObject()->className()) {
        return false;
    }
    /*final*/ Profile* other = (Profile*) obj;
    return !((this->id == "") ? (other->id != "") : this->id != (other->id));
}

/**
 * Test if the profile is complete. A profile is considered complete if it
 * can be instantiated using {@link #Profile(java.io.File)} and has a
 * ProfileConfig.xml file within it's private directory.
 *
 * @return true if ProfileConfig.xml exists where expected.
 */
/*public*/ bool Profile::isComplete() {
    return (new File(this->getPath(), Profile::CONFIG_FILENAME))->exists();
}

/**
 * Return the uniqueness portion of the Profile Id.
 *
 * This portion of the Id is automatically generated when the profile is
 * created.
 *
 * @return An eight-character String of alphanumeric characters.
 */
/*public*/ QString Profile::getUniqueId() {
    return this->id.mid(this->id.lastIndexOf(".") + 1); // NOI18N
}

/**
 * Test if the given path or subdirectories contains a Profile::
 *
 * @param path
 * @return true if path or subdirectories contains a Profile::
 * @since 3.9.4
 */
/*public*/ /*static*/ bool Profile::containsProfile(File* path)
{
 QDir pathDir;
 if (path->isDirectory())
 {
  pathDir =  QDir(path->getAbsoluteFile()->toString());
  if (Profile::isProfile(path))
  {
   return true;
  }
  else
  {
   QStringList l = pathDir.entryList();
   QStringList filters = QStringList() << *_PROPERTIES;
   foreach (QString file, pathDir.entryList(filters))
   {
    if(file == *_PROPERTIES)
     return true;
    if (Profile::containsProfile(new File(pathDir.absolutePath() + file)))
    {
     return true;
    }
   }
  }
 }
 return false;
}

/**
 * Test if the given path is within a directory that is a Profile::
 *
 * @param path
 * @return true if path or parent directories is a Profile::
 * @since 3.9.4
 */
/*public*/ /*static*/ bool Profile::inProfile(File* path)
{
 if (path->getParentFile() != nullptr)
 {
  if (Profile::isProfile(path->getParentFile()))
  {
   log->error(tr("path %1 is in %2").arg(path->getPath()).arg(path->getParentFile()->getPath()));
   return true;
  }
  return Profile::inProfile(path->getParentFile());
 }
 return false;
}

/**
 * Test if the given path is a Profile::
 *
 * @param path
 * @return true if path is a Profile::
 * @since 3.9.4
 */
/*public*/ /*static*/ bool Profile::isProfile(File* path)
{
 if (path->isDirectory())
 {
  // Version 2
  if ((new File(path, *_SHARED_PROPERTIES))->canRead()) // i.e: "profile/profile.properties"
  {
   return true;
  }
  // Version 1
  if ((new File(path, *_PROPERTIES))->canRead()) // i.e: "profile.properties"
  {
   return true;
  }
 }
 return false;
}

/*private*/ /*static*/ Logger* Profile::log =  LoggerFactory::getLogger("Profile");
