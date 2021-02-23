#include "profile.h"
#include "../appslib/profilemanager.h"
#include "file.h"
#include <QDir>
#include "properties.h"
#include "exceptions.h"
#include "QTextStream"
#include "profileproperties.h"
#include "loggerfactory.h"
#include "fileoutputstream.h"

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
 common(path,  true);
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
/*public*/ Profile::Profile(QString name, QString id, File* path, QObject *parent) throw (IOException, IllegalArgumentException) :
    QObject(parent)
{
 File* pathWithExt; // path with extension
 if (path->getName().endsWith(EXTENSION)) {
     pathWithExt = path;
 } else {
     pathWithExt = new File(path->getParentFile(), path->getName() + EXTENSION);
 }
 if (pathWithExt->getName() != (id + EXTENSION)) {
     throw  IllegalArgumentException(id + " " + path->getName() + " do not match"); // NOI18N
 }
 if (Profile::isProfile(path) || Profile::isProfile(pathWithExt)) {
     throw  IllegalArgumentException("A profile already exists at " + path->toString()); // NOI18N
 }
 if (Profile::containsProfile(path) || Profile::containsProfile(pathWithExt)) {
     throw  IllegalArgumentException(path->toString() + " contains a profile in a subdirectory."); // NOI18N
 }
 if (Profile::inProfile(path) || Profile::inProfile(pathWithExt)) {
     if (Profile::inProfile(path)) log->warn(tr("Exception: Path %1 is within an existing profile.").arg(path->toString()),  Exception("traceback")); // NOI18N
     if (Profile::inProfile(pathWithExt)) log->warn(tr("Exception: pathWithExt %1 is within an existing profile.").arg(pathWithExt->toString()),  Exception("traceback")); // NOI18N
     throw  IllegalArgumentException(path->toString() + " is within an existing profile."); // NOI18N
 }
 this->name = name;
 this->id = id + "." + ProfileManager::createUniqueId();
 this->path = pathWithExt;
 // use field, not local variables (path or pathWithExt) for paths below
 if (!this->path->exists() && !this->path->mkdirs()) {
     throw IOException("Unable to create directory " + this->path->toString()); // NOI18N
 }
 if (!this->path->isDirectory()) {
     throw IllegalArgumentException(path->getPath() + " is not a directory"); // NOI18N
 }
 this->save();
 if (!Profile::isProfile(this->path)) {
     throw IllegalArgumentException(path->getPath() + " does not contain a profile.properties file"); // NOI18N
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
 common(path,  isReadable);
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
void Profile::common(File *path, bool isReadable)
{
 this->path = path;
 if (isReadable) {
     this->readProfile();
 }
}

/*protected*/ Profile::Profile(/*@Nonnull*/ File* path, /*@Nonnull*/ QString id, bool isReadable, QObject* parent) throw (IOException) : QObject(parent)
{
 common(path, isReadable);
}

/*protected*/ /*final*/ void Profile::save() throw (IOException)
{
    ProfileProperties* p = new ProfileProperties(this);
    p->put(*_NAME, this->name, true);
    p->put(*_ID, this->id, true);
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
ProfileManager::getDefault()->profileNameChange(this, oldName);
}

/**
 * Set the name for this profile while constructing the profile.
 * <p>
 * Overriding classing must use this method to set the name in a constructor
 * since {@link #setName(java.lang.String)} passes this Profile object to an
 * object expecting a completely constructed Profile.
 *
 * @param name the new name
 */
/*protected*/ /*final*/ void Profile::setNameInConstructor(QString name) {
    this->name = name;
}

/**
 * @return the id
 */
/*public*/ QString Profile::getId() const
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

 QString readId = p->get(*_ID, true);
 if (readId != "") {
     id = readId;
 }
 QString readName = p->get(*_NAME, true);
 if (readName != "") {
     name = readName;
 }
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
   foreach (QString file, pathDir.entryList(filters, QDir::AllDirs | QDir::Files |QDir::NoDotAndDotDot))
   {
    if(file == *_PROPERTIES)
     return true;
    if (Profile::containsProfile(new File(pathDir.absolutePath() + QDir::separator() + file)))
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
  if ((new File(path, *_PROPERTIES))->canRead() && path->getName() != (/*PROFILE*/"profile")) // i.e: "profile.properties"
  {
   return true;
  }
 }
 return false;
}
//@Override
/*public*/ int Profile::compareTo(Profile* o) {
    if (this->equals(o)) {
        return 0;
    }
    QString thisString = "" + this->getName() + this->getPath()->toString();
    QString thatString = "" + o->getName() + o->getPath()->toString();
    return thisString.compare(thatString);
}

/*private*/ /*static*/ Logger* Profile::log =  LoggerFactory::getLogger("Profile");
