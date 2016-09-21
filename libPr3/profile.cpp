#include "profile.h"
#include "profilemanager.h"
#include "file.h"
#include <QDir>
#include "properties.h"
#include "exceptions.h"
#include "QTextStream"

//Profile::Profile(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A JMRI application profile. Profiles allow a JMRI application to load
 * completely separate set of preferences at each launch without relying on host
 * OS-specific tricks to ensure this happens.
 *
 * @author Randall Wood Copyright (C) 2013, 2014
 */
// /*public*/ class Profile {
    /*public*/ /*static final*/ QString Profile::PROFILE = "profile"; // NOI18N
    /*protected*/ /*static final */ QString Profile::ID = "id"; // NOI18N
    /*protected*/ /*static final */ QString Profile::NAME = "name"; // NOI18N
    /*protected*/ /*static final */ QString Profile::PATH = "path"; // NOI18N
    /*public*/ /*static final */ QString Profile::PROPERTIES = "profile.properties"; // NOI18N
/*public*/ /*static final*/ QString Profile::CONFIG = "profile.xml"; // NOI18N
/*public*/ /*static final*/ QString Profile::SHARED_PROPERTIES = Profile::PROFILE + "/" + Profile::PROPERTIES; // NOI18N
/*public*/ /*static final*/ QString Profile::SHARED_CONFIG = Profile::PROFILE + "/" + Profile::CONFIG; // NOI18N
    /*public*/ /*static final */ QString Profile::CONFIG_FILENAME = "ProfileConfig.xml"; // NOI18N
/*public*/ /*static final*/ QString Profile::UI_CONFIG = "user-interface.xml"; // NOI18N
/*public*/ /*static final*/ QString Profile::SHARED_UI_CONFIG = Profile::PROFILE + "/" + Profile::UI_CONFIG; // NOI18N
/*public*/ /*static final*/ QString Profile::UI_CONFIG_FILENAME = "UserPrefsProfileConfig.xml"; // NOI18N

/**
 * Create a Profile object given just a path to it. The Profile must exist
 * in storage on the computer.
 *
 * @param path The Profile's directory
 * @throws IOException
 */
///*public*/ Profile::Profile(File path, QObject *parent) :
//    QObject(parent)
//{
//    //this(path, true);
//}
///**
// * Create a Profile object given just a path to it. The Profile must exist
// * in storage on the computer.
// *
// * @param path The Profile's directory
// * @throws IOException
// */
//public Profile(File* path) /*throws IOException*/ {
//    this(path, true);
//}
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
 if (path->getName()!=(id))
 {
  //throw new IllegalArgumentException(id + " " + path->getName() + " do not match"); // NOI18N
  Logger::error(id + " " + path->getName() + " do not match");

 }
 if (( File(path, PROPERTIES)).canRead())
 {
  //throw new IllegalArgumentException("A profile already exists at " + path->toString()); // NOI18N
  Logger::error("A profile already exists at " + path->toString());
 }
 if (Profile::containsProfile(path))
 {
  //throw new IllegalArgumentException(path->toString() + " contains a profile in a subdirectory."); // NOI18N
  Logger::error(path->toString() + " contains a profile in a subdirectory.");
 }
 if (Profile::inProfile(path))
 {
  //throw new IllegalArgumentException(path->toString() + " is within an existing profile."); // NOI18N
  Logger::error(path->toString() + " is within an existing profile.");
 }
 this->name = name;
 this->id = id + "." + ProfileManager::createUniqueId();
 this->path = path;
 //path->mkdirs();
 QDir d = QDir();
 d.mkpath(path->toString());
 if (!path->isDirectory())
 {
  throw new IllegalArgumentException(path->toString()+ " is not a directory"); // NOI18N
 }
 this->save();
 if (!( File(path, PROPERTIES)).canRead())
 {
  //throw new IllegalArgumentException(path->toString() + " does not contain a profile.properties file"); // NOI18N
  Logger::error(path->toString() + " does not contain a profile.properties file"); // NOI18N
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
 this->path = path;
 this->name = path->getName();
 if (isReadable)
 {
  this->readProfile();
 }
}

/*protected*/ /*final*/ void Profile::save() /*throws IOException*/
{

 Properties* p = new Properties();
#if 1
    File* f = new File(this->path, PROPERTIES);
    QTextStream* os = NULL;

    p->setProperty(NAME, this->name);
    p->setProperty(ID, this->id);
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
 Properties* p = new Properties();
 File f =  File(this->path,  PROPERTIES);
#if 1
 QTextStream* is = NULL;
// try
// {
  QString path = f.getPath();
  QFile* qFile = new QFile(path);
  if(qFile->open(QIODevice::ReadOnly))
  {
   is = new QTextStream(qFile);
   p->loadFromXML(is);
  //is->close();
  }
  else
  {
  if (is != NULL)
  {
    qFile->close();
    return;
  }
 }
 this->id = p->getProperty(ID);
 this->name = p->getProperty(NAME);
#endif
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
   QStringList filters = QStringList() << PROPERTIES;
   foreach (QString file, pathDir.entryList(filters))
   {
    if(file == PROPERTIES)
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
 if (path->getParentFile() != NULL)
 {
        if (Profile::isProfile(path->getParentFile())) {
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
  if ((new File(path, PROPERTIES))->canRead())
  {
   return true;
  }
 }
 return false;
}
