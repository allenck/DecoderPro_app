#include "jmripreferencesprovider.h"
#include "./profile.h"
#include "file.h"
#include "fileutil.h"
#include "provider.h"
#include "nodeidentity.h"
#include "orderedproperties.h"
#include "version.h"
#include "loggerfactory.h"
#include "profileutils.h"

//JmriPreferencesProvider::JmriPreferencesProvider(QObject *parent) : QObject(parent)
//{

//}
/**
 * Provides instances of {@link java.util.prefs.Preferences} backed by a
 * JMRI-specific storage implementation based on a Properties file.
 *
 * There are two Properties files per {@link jmri.profile.Profile} and
 * {@link jmri.util.node.NodeIdentity}, both stored in the directory
 * <code>profile:profile</code>:
 * <ul>
 * <li><code>profile.properties</code> preferences that are shared across
 * multiple nodes for a single profile. An example of such a preference would be
 * the Railroad Name preference.</li>
 * <li><code>&lt;node-identity&gt;/profile.properties</code> preferences that
 * are specific to the profile running on a specific host (&lt;node-identity&gt;
 * is the identity returned by {@link jmri.util.node.NodeIdentity#identity()}).
 * An example of such a preference would be a file location.</li>
 * </ul>
 *
 * @author Randall Wood 2015
 */
// /*public*/ /*final*/ class JmriPreferencesProvider {


/*private*/ /*static*/ /*final*/ QHash<File*, JmriPreferencesProvider*>* JmriPreferencesProvider::sharedProviders = new QHash<File*, JmriPreferencesProvider*>();
/*private*/ /*static*/ /*final*/ QHash<File*, JmriPreferencesProvider*>* JmriPreferencesProvider::privateProviders = new QHash<File*, JmriPreferencesProvider*>();
///*private*/ static /*final*/ String INVALID_KEY_CHARACTERS = "_.";
/*private*/ /*static*/ /*final*/ Logger* JmriPreferencesProvider::log = LoggerFactory::getLogger("JmriPreferencesProvider");

/**
 * Get the JmriPreferencesProvider for the specified profile path. Use of
 *
 * @param path   The root path of a {@link jmri.profile.Profile}. This is
 *               most frequently the path returned by
 *               {@link jmri.profile.Profile#getPath()}.
 * @param shared True if the preferences apply to the profile at path
 *               irregardless of host. If false, the preferences only apply
 *               to this computer.
 * @return The shared or private JmriPreferencesProvider for the project at
 *         path.
 */
/*static*/ /*synchronized*/ JmriPreferencesProvider* JmriPreferencesProvider::findProvider(File* path, bool shared)
{
 if(sharedProviders == NULL)
  sharedProviders = new QHash<File*, JmriPreferencesProvider*>();
 if (shared)
 {
  if (sharedProviders->value(path) == NULL)
  {
   sharedProviders->insert(path, new JmriPreferencesProvider(path, shared));
  }
  return sharedProviders->value(path);
 }
 else
 {
  if(privateProviders == nullptr)
   privateProviders = new QHash<File*, JmriPreferencesProvider*>();
  if (privateProviders->value(path) == NULL)
  {
   privateProviders->insert(path, new JmriPreferencesProvider(path, shared));
  }
  return privateProviders->value(path);
 }
}

/**
 * Get the {@link java.util.prefs.Preferences} for the specified class in
 * the specified profile.
 *
 * @param project The profile. This is most often the profile returned by
 *                the {@link jmri.profile.ProfileManager#getActiveProfile()}
 *                method of the ProfileManager returned by
 *                {@link jmri.profile.ProfileManager#getDefault()}
 * @param clazz   The class requesting preferences. Note that the
 *                preferences returned are for the package containing the
 *                class.
 * @param shared  True if the preferences apply to this profile irregardless
 *                of host. If false, the preferences only apply to this
 *                computer.
 * @return The shared or private Preferences node for the package containing
 *         clazz for project.
 */
/*public*/ /*static*/ Preferences* JmriPreferencesProvider::getPreferences(/*final*/ Profile* project, /*final*/ char* clazz, /*final*/ bool shared) {
    if (project != NULL) {
        return findProvider(project->getPath(), shared)->getPreferences(clazz);
    } else {
        return findProvider(NULL, shared)->getPreferences(clazz);
    }
}

/**
 * Get the {@link java.util.prefs.Preferences} for the specified package in
 * the specified profile.
 *
 * @param project The profile. This is most often the profile returned by
 *                the {@link jmri.profile.ProfileManager#getActiveProfile()}
 *                method of the ProfileManager returned by
 *                {@link jmri.profile.ProfileManager#getDefault()}
 * @param pkg     The package requesting preferences.
 * @param shared  True if the preferences apply to this profile irregardless
 *                of host. If false, the preferences only apply to this
 *                computer.
 * @return The shared or private Preferences node for the package.
 * @deprecated Not for removal. Use of
 * {@link #getPreferences(jmri.profile.Profile, java.lang.Class, bool)}
 * is preferred and recommended unless reading preferences for a
 * non-existent package or class.
 */
/*public*/ /*static*/ Preferences* JmriPreferencesProvider::getPreferences(/*final*/ Profile* project, /*final*/ QString pkg, /*final*/ bool shared)
{
 if (project != NULL)
 {
  return findProvider(project->getPath(), shared)->getPreferences(pkg);
 }
 else
 {
  return findProvider(NULL, shared)->getPreferences(pkg);
 }
}

/**
 * Get the {@link java.util.prefs.Preferences} for the specified class in
 * the specified path.
 *
 * @param path   The path to a profile. This is most often the result of
 *               {@link jmri.profile.Profile#getPath()} for a given Profile.
 * @param clazz  The class requesting preferences. Note that the preferences
 *               returned are for the package containing the class.
 * @param shared True if the preferences apply to this profile irregardless
 *               of host. If false, the preferences only apply to this
 *               computer.
 * @return The shared or private Preferences node for the package containing
 *         clazz for project.
 * @deprecated Not for removal. Use of
 * {@link #getPreferences(jmri.profile.Profile, java.lang.Class, bool)}
 * is preferred and recommended unless being used to during the construction
 * of a Profile object.
 */
/*public*/ /*static*/ Preferences* JmriPreferencesProvider::getPreferences(/*final*/ /*@Nonnull*/ File* path, /*@Nullable*/ /*final*/ char* clazz, /*final*/ bool shared) {
    return findProvider(path, shared)->getPreferences(clazz);
}

/**
 * Get the {@link java.util.prefs.Preferences} for the specified class.
 *
 * @param clazz The class requesting preferences. Note that the preferences
 *              returned are for the package containing the class.
 * @return The shared or private Preferences node for the package containing
 *         clazz.
 */
Preferences* JmriPreferencesProvider::getPreferences(/*final*/ char* clazz)
{
 if (clazz == nullptr)
 {
  return this->root;
 }
 return this->root->node(findCNBForClass(clazz));
}

/**
 * Get the {@link java.util.prefs.Preferences} for the specified package.
 *
 * @param pkg The package for which preferences are needed.
 * @return The shared or private Preferences node for the package.
 */
Preferences* JmriPreferencesProvider::getPreferences(/*final*/ QString pkg)
{
 if (pkg == NULL) {
     return this->root;
 }
 return this->root->node(pkg);
}

JmriPreferencesProvider::JmriPreferencesProvider(File* path, bool shared)
{
 this->path = path;
 this->shared = shared;
 this->firstUse = !this->getPreferencesFile()->exists();
 this->root = new JmriPreferences(NULL, "", this);
 if (!this->firstUse)
 {
  try
  {
   this->root->sync();
  }
  catch (BackingStoreException* ex)
  {
   log->error("Unable to read preferences", ex);
  }
 }
}

/**
 * Return true if the properties file had not been written for a JMRI
 * {@link jmri.profile.Profile} before this instance of JMRI was launched.
 * Note that the first use of a node-specific setting can be different than
 * the first use of a multi-node setting.
 *
 * @return true if new or newly migrated profile, false otherwise
 */
/*public*/ bool JmriPreferencesProvider::isFirstUse() {
    return this->firstUse;
}

// retain unused method for reference - generates a String replacing
// all invalid characters in a String with underscores
///*private*/ static String encodeString(String s) {
//    StringBuilder result = new StringBuilder();
//
//    for (char c : s.toCharArray()) {
//        if (INVALID_KEY_CHARACTERS.indexOf(c) == (-1)) {
//            result.append(c);
//        } else {
//            result.append("_");
//            result.append(Integer.toHexString(c));
//            result.append("_");
//        }
//    }
//
//    return result.toString();
//}
/**
 * Returns the name of the package for the class in a format that is treated
 * as a single token.
 *
 * @param cls The class for which a sanitized package name is needed
 * @return A sanitized package name
 */
/*public*/ /*static*/ QString JmriPreferencesProvider::findCNBForClass(/*@Nonnull*/ QString cls)
{
  QString absolutePath;
  absolutePath = cls.mid(0, cls.lastIndexOf('.'));    //*.getName()*/.replace("(^|\\.)[^.]+$", "");//NOI18N
  return absolutePath.replace('.', '-');
}

File* JmriPreferencesProvider::getPreferencesFile()
{
 if (this->path == NULL)
 {
  return new File(this->getPreferencesDirectory(), "preferences.properties"); //text file
 }
 else
 {
  return new File(this->getPreferencesDirectory(), "profile.properties");
 }
}

/*private*/ File* JmriPreferencesProvider::getPreferencesDirectory()
{
 File* dir;
 if (this->path  == nullptr) {
     dir = new File(FileUtil::getPreferencesPath(), "preferences");
 }
 else
 {
  dir = new File(this->path, /*Profile::PROFILE*/"profile");
  if (!this->shared)
  {
   if (Profile::isProfile(this->path))
   { // protect against testing a new profile
    try
    {
     Profile* profile = new Profile(this->path);
     File* nodeDir = new File(dir, NodeIdentity::storageIdentity(profile));
     if (!nodeDir->exists())
     {
      if (!ProfileUtils::copyPrivateContentToCurrentIdentity(profile)) {
          log->debug("Starting profile with new private preferences.");
      }
     }
    } catch (IOException* ex) {
        log->debug("Copying existing private configuration failed.");
    }
   }
   dir = new File(dir, NodeIdentity::storageIdentity());
  }
 }
 FileUtil::createDirectory(dir);
 return dir;
}

/**
 * @return the backedUp
 */
/*protected*/ bool JmriPreferencesProvider::isBackedUp() {
    return backedUp;
}

/**
 * @param backedUp the backedUp to set
 */
/*protected*/ void JmriPreferencesProvider::setBackedUp(bool backedUp) {
    this->backedUp = backedUp;
}

///*private*/ class JmriPreferences extends AbstractPreferences {

/*private*/ /*final*/ Logger* JmriPreferences::log = LoggerFactory::getLogger("JmriPreferences");

//    /*private*/ Map<String, String> root;
//    /*private*/ Map<String, JmriPreferences> children;
//    /*private*/ bool isRemoved = false;

/*public*/ JmriPreferences::JmriPreferences(AbstractPreferences* parent, QString name, JmriPreferencesProvider* jpp) : AbstractPreferences(parent, name)
{
 //super(parent, name);
 _isRemoved = false;
 this->jpp = jpp;

 //log->debug(tr("Instantiating node \"%1\"").arg(name));

 root = new QMap<QString, QString>();
 children = new QMap<QString, JmriPreferences*>();

 try
 {
  sync();
 }
 catch (BackingStoreException* e)
 {
  log->error(tr("Unable to sync on creation of node %1").arg(name), e);
 }
}

//@Override
/*protected*/ void JmriPreferences::putSpi(QString key, QString value)
{
 root->insert(key, value);
 try
 {
  flush();
 } catch (BackingStoreException* e)
 {
  log->error(tr("Unable to flush after putting %1").arg(key), e);
 }
}

//@Override
/*protected*/ QString JmriPreferences::getSpi(QString key) {
 return root->value(key);
}

//@Override
/*protected*/ void JmriPreferences::removeSpi(QString key)
{
 root->remove(key);
 try
 {
 flush();
 }
 catch (BackingStoreException* e) {
     log->error(tr("Unable to flush after removing %1").arg(key), e);
 }
}

//@Override
/*protected*/ void JmriPreferences::removeNodeSpi()
{
 _isRemoved = true;
 flush();
}

//@Override
/*protected*/ QStringList JmriPreferences::keysSpi()
{
    //return root->keys().toVector(root->keys().size());
return QStringList(root->keys());
}

//@Override
/*protected*/ QStringList JmriPreferences::childrenNamesSpi()
{
    //return children.keySet().toArray(new String[children.keySet().size()]);
return QStringList(children->keys());
}

//@Override
/*protected*/ JmriPreferences* JmriPreferences::childSpi(QString name)
{
 JmriPreferences* child = children->value(name);
 if ((child == NULL) || child->_isRemoved)
 {
  child = new JmriPreferences(this, name, jpp);
  children->insert(name, child);
 }
 return child;
}

//@Override
/*protected*/ void JmriPreferences::syncSpi() /*throw (BackingStoreException)*/
{
 if (_isRemoved) {
     return;
 }

 /*final*/ File* file = jpp->getPreferencesFile();

 if (!file->exists()) {
     return;
 }

//        /*synchronized*/ (file)
// {
  Properties* p = new OrderedProperties();
 try
 {
     //try (FileInputStream fis = new FileInputStream(file))
//            {
  QFile* f = new QFile(file->getPath());
  if(f->open(QIODevice::ReadOnly))
  {
   QTextStream* fis = new QTextStream(f);
   p->load(fis);
  }
  else throw new IOException(f->errorString());

  QString* sb = new QString();
  getPath(sb);
  QString path = *sb/*.toString()*/;

  ///*final*/ Enumeration<?> pnen = p->propertyNames();
  QStringListIterator pnen = p->propertyNames();
  while (pnen.hasNext())
  {
   QString propKey =  pnen.next();
   if (propKey.startsWith(path))
   {
    QString subKey = propKey.mid(path.length());
    // Only load immediate descendants
    if (subKey.indexOf('.') == -1)
    {
     root->insert(subKey, p->getProperty(propKey));
    }
   }
  }
 } catch (IOException* e) {
     throw new BackingStoreException(e->getMessage());
 }
// }
}

/*private*/ void JmriPreferences::getPath(QString* sb)
{
 /*final*/ JmriPreferences* _parent = (JmriPreferences*) parent();
 if (_parent == NULL) {
     return;
 }

 _parent->getPath(sb);
// sb = sb->append(name());
// sb =  sb->append('.');
 QString path = *sb;
 path = path.append(name());
 path = path.append('.');
 *sb = path;
}

//@Override
/*protected*/ void JmriPreferences::flushSpi()
{
 /*final*/ File* file = jpp->getPreferencesFile();

//        /*synchronized*/ (file)
// {
 Properties* p = new OrderedProperties();
 try
 {

  QString* sb = new QString();
  getPath(sb);
  QString path = *sb/*.toString()*/;

  if (file->exists())
  {
//                    try (FileInputStream fis = new FileInputStream(file)) {
   QFile* f = new QFile(file->getPath());
   if(f->open(QIODevice::ReadOnly))
   {
    QTextStream* fis = new QTextStream(f);
    p->load(fis);
//                    }
   }
   QStringList toRemove = QStringList();

   // Make a list of all direct children of this node to be removed
   ///*final*/ Enumeration<?> pnen = p.propertyNames();
   QStringListIterator pnen = p->propertyNames();
   while (pnen.hasNext())
   {
    QString propKey =  pnen.next()/*.toStdString()*/;
    if (propKey.startsWith(path))
    {
     QString subKey = propKey.mid(path.length());
     // Only do immediate descendants
     if (subKey.indexOf('.') == -1) {
         toRemove.append(propKey);
     }
    }
   }

   // Remove them now that the enumeration is done with
//                    toRemove.stream().forEach((propKey) -> {
//                        p.remove(propKey);
//                    });
   foreach (QString propKey, toRemove)
   {
    p->remove(propKey);
   }
  }

  // If this node hasn't been removed, add back in any values
  if (!_isRemoved) {
//                    root.keySet().stream().forEach((s) -> {
//                        p.setProperty(path + s, root.get(s));
//                    });
   foreach(QString s, root->keys())
    p->setProperty(path + s, root->value(s));
  }

  //if (!JmriPreferencesProvider.this->isBackedUp() && file.exists()) {
  if(!jpp->isBackedUp() && file->exists())
  {
   log->debug(tr("Backing up %1").arg(file->getPath()));
   FileUtil::backup(file);
   jpp->setBackedUp(true);
  }
//                try (FileOutputStream fos = new FileOutputStream(file)) {
//                    p.store(fos, "JMRI Preferences version " + Version.name());
//                }
  QFile* fo = new QFile(file->getPath());
  if(fo->open(QIODevice::WriteOnly))
  {
   QTextStream* fos = new QTextStream(fo);
   p->store(fos, "JMRI Preferences version " + Version::name());
  }
 } catch (IOException* e) {
     throw new BackingStoreException(e->getMessage());
 }
// }
}
//}
