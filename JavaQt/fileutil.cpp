#include "fileutil.h"
#include <QDir>
#include <QString>
#include <QUrl>
#include "file.h"
#include "matcher.h"
#include <QTextStream>
#include "system.h"
#include "fileutilsupport.h"

const QString FileUtil::PROGRAM = "program:"; // NOI18N
const QString FileUtil::PREFERENCES = "preference:"; // NOI18N
const QString FileUtil::SETTINGS = "settings:"; // NOI18N
const QString FileUtil::HOME = "home:"; // NOI18N
const QString FileUtil::PROFILE = "profile:"; // NOI18N
const QString FileUtil::SCRIPTS = "scripts:"; // NOI18N
const QString FileUtil::RESOURCE = "resource:"; // NOI18N
const QString FileUtil::FILE = "file:"; // NOI18N
const QChar FileUtil::SEPARATOR = '/'; // NOI18N
QString FileUtil::homePath = QDir::homePath() + QDir::separator(); // NOI18N
#if 1 // override program path for development
QString FileUtil::programPath = QDir::homePath() + QDir::separator()+"NetBeansProjects"+QDir::separator()+"jmri"+ QDir::separator();
#endif
QString FileUtil::jarPath = "";
QString FileUtil::scriptsPath = "";
QString FileUtil::userFilesPath = QDir::homePath() + QDir::separator()+".jmri"+ QDir::separator();
/* path to the current profile */
/*static*/ /*private*/ QString FileUtil::profilePath = "";
bool FileUtil::_debug = false;

FileUtil::FileUtil(QObject *parent) :
    QObject(parent)
{
}
/**
 * Common utility methods for working with Files. <P> We needed a place to
 * refactor common File-processing idioms in JMRI code, so this class was
 * created. It's more of a library of procedures than a real class, as (so far)
 * all of the operations have needed no state information.
 *
 * @author Bob Jacobsen Copyright 2003, 2005, 2006
 * @author Randall Wood Copyright 2012, 2013
 * @version $Revision: 22562 $
 */
///*public*/ class FileUtil {

//    // initialize logging
//    static private Logger log = Logger.getLogger(FileUtil.class.getName());

/**
 * Get the {@link java.io.File} that path refers to. Throws a
 * {@link java.io.FileNotFoundException} if the file cannot be found instead
 * of returning null (as File would). Use {@link #getURI(java.lang.String) }
 * or {@link #getURL(java.lang.String) } instead of this method if possible.
 *
 * @param path
 * @return {@link java.io.File} at path
 * @throws java.io.FileNotFoundException
 * @see #getURI(java.lang.String)
 * @see #getURL(java.lang.String)
 */
/*static*/ /*public*/ File* FileUtil::getFile(QString path) //throw (FileNotFoundException)
{
 return FileUtilSupport::getDefault()->getFile(path);
}

/**
 * Get the resource file corresponding to a name. There are five cases: <UL>
 * <LI> Starts with "resource:", treat the rest as a pathname relative to
 * the program directory (deprecated; see "program:" below) <LI> Starts with
 * "program:", treat the rest as a relative pathname below the program
 * directory <LI> Starts with "preference:", treat the rest as a relative
 * path below the preferences directory <LI> Starts with "home:", treat the
 * rest as a relative path below the user.home directory <LI> Starts with
 * "file:", treat the rest as a relative path below the resource directory
 * in the preferences directory (deprecated; see "preference:" above) <LI>
 * Otherwise, treat the name as a relative path below the program directory
 * </UL> In any case, absolute pathnames will work.
 *
 * @param pName The name string, possibly starting with program:,
 * preference:, home:, file: or resource:
 * @return Absolute or relative file name to use, or NULL.
 * @since 2.7.2
 */
/*static*/ /*public*/ QString FileUtil::getExternalFilename(QString pName)
{
 return FileUtilSupport::getDefault()->getExternalFilename(pName);
}

/**
 * Convert a portable filename into an absolute filename
 *
 * @param path
 * @return An absolute filename
 */
/*static*/ /*public*/ QString FileUtil::getAbsoluteFilename(QString path)
{
 return FileUtilSupport::getDefault()->getAbsoluteFilename(path);
}

/**
 * Convert a File object to our preferred storage form.
 *
 * This is the inverse of {@link #getExternalFilename(QString pName)}.
 * Deprecated forms are not created.
 *
 * @param file File to be represented
 * @since 2.7.2
 */
/*static*/ /*public*/ QString FileUtil::getPortableFilename(File* file)
{
 return FileUtil::getPortableFilename(file, false, false);
}

/**
 * Convert a filename string to our preferred storage form.
 *
 * This is the inverse of {@link #getExternalFilename(QString pName)}.
 * Deprecated forms are not created.
 *
 * @param filename Filename to be represented
 * @since 2.7.2
 */
/*static*/ /*public*/ QString FileUtil::getPortableFilename(QString filename)
{
 return FileUtil::getPortableFilename(filename, false, false);
}
/**
 * Convert a File object's path to our preferred storage form.
 *
 * This is the inverse of {@link #getFile(String pName)}. Deprecated forms
 * are not created.
 *
 * This method supports a specific use case concerning profiles and other
 * portable paths that are stored within the User files directory, which
 * will cause the {@link jmri.profile.ProfileManager} to write an incorrect
 * path for the current profile or
 * {@link apps.configurexml.FileLocationPaneXml} to write an incorrect path
 * for the Users file directory. In most cases, the use of
 * {@link #getPortableFilename(java.io.File)} is preferable.
 *
 * @param file File at path to be represented
 * @param ignoreUserFilesPath true if paths in the User files path should be
 * stored as absolute paths, which is often not desirable.
 * @param ignoreProfilePath true if paths in the profile should be stored as
 * absolute paths, which is often not desirable.
 * @return Storage format representation
 * @since 3.5.5
 */
/*static*/ /*public*/ QString FileUtil::getPortableFilename(File* file, bool ignoreUserFilesPath, bool ignoreProfilePath)
{
 return FileUtilSupport::getDefault()->getPortableFilename(file, ignoreUserFilesPath, ignoreProfilePath);
}

/**
 * Convert a filename string to our preferred storage form.
 *
 * This is the inverse of {@link #getExternalFilename(String pName)}.
 * Deprecated forms are not created.
 *
 * This method supports a specific use case concerning profiles and other
 * portable paths that are stored within the User files directory, which
 * will cause the {@link jmri.profile.ProfileManager} to write an incorrect
 * path for the current profile or
 * {@link apps.configurexml.FileLocationPaneXml} to write an incorrect path
 * for the Users file directory. In most cases, the use of
 * {@link #getPortableFilename(java.io.File)} is preferable.
 *
 * @param filename Filename to be represented
 * @param ignoreUserFilesPath true if paths in the User files path should be
 * stored as absolute paths, which is often not desirable.
 * @param ignoreProfilePath true if paths in the profile path should be
 * stored as absolute paths, which is often not desirable.
 * @return Storage format representation
 * @since 3.5.5
 */
/*static*/ /*public*/ QString FileUtil::getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath)
{
 return FileUtilSupport::getDefault()->getPortableFilename(filename, ignoreUserFilesPath, ignoreProfilePath);
}

/**
 * Test if the given filename is a portable filename.
 *
 * Note that this method may return a false positive if the filename is a
 * file: URL.
 *
 * @param filename
 * @return true if filename is portable
 */
/*static*/ /*public*/ bool FileUtil::isPortableFilename(QString filename) {
    return (filename.startsWith(PROGRAM)
            || filename.startsWith(HOME)
            || filename.startsWith(PREFERENCES)
            || filename.startsWith(SCRIPTS)
            || filename.startsWith(PROFILE)
            || filename.startsWith(SETTINGS)
            || filename.startsWith(FILE)
            || filename.startsWith(RESOURCE));
}
/**
 * Get the user's home directory.
 *
 * @return User's home directory as a QString
 */
/*static*/ /*public*/ QString FileUtil::getHomePath()
{
 return homePath;
}

/**
 * Get the user's files directory. If not set by the user, this is the same
 * as the preferences path.
 *
 * @see #getPreferencesPath()
 * @return User's files directory as a QString
 */
/*static*/ /*public*/ QString FileUtil::getUserFilesPath()
{
 return FileUtilSupport::getDefault()->getUserFilesPath();
}

/**
 * Set the user's files directory.
 *
 * @see #getUserFilesPath()
 * @param path The path to the user's files directory
 */
/*static*/ /*public*/ void FileUtil::setUserFilesPath(QString path)
{
 FileUtilSupport::getDefault()->setUserFilesPath(path);
}
/**
 * Get the profile directory. If not set, this is the same as the
 * preferences path.
 *
 * @see #getPreferencesPath()
 * @return Profile directory as a String
 */
/*static*/ /*public*/ QString FileUtil::getProfilePath()
{
 return FileUtilSupport::getDefault()->getProfilePath();

}
/**
 * Set the profile directory.
 *
 * @see #getProfilePath()
 * @param path The path to the profile directory
 */
/*static*/ /*public*/ void FileUtil::setProfilePath(QString path) {
 FileUtilSupport::getDefault()->setProfilePath(path);
}

/**
 * Get the preferences directory. This directory is set based on the OS and
 * is not normally settable by the user. <ul><li>On Microsoft Windows
 * systems, this is JMRI in the User's home directory.</li> <li>On OS X
 * systems, this is Library/Preferences/JMRI in the User's home
 * directory.</li> <li>On Linux, Solaris, and othe UNIXes, this is .jmri in
 * the User's home directory.</li> <li>This can be overridden with by
 * setting the jmri.prefsdir Java property when starting JMRI.</li></ul> Use
 * {@link #getHomePath()} to get the User's home directory.
 *
 * @see #getHomePath()
 * @return Path to the preferences directory.
 */
/*static*/ /*public*/ QString FileUtil::getPreferencesPath()
{
 return FileUtilSupport::getDefault()->getPreferencesPath();
}

/**
 * Get the JMRI program directory.
 *
 * @return JMRI program directory as a QString.
 */
/*static*/ /*public*/ QString FileUtil::getProgramPath()
{
 if (programPath == NULL)
 {
  FileUtil::setProgramPath("."); // NOI18N
 }
 return programPath;
}

/**
 * Set the JMRI program directory.
 *
 * Convenience method that calls
 * {@link FileUtil#setProgramPath(java.io.File)} with the passed in path.
 *
 * @param path
 */
/*static*/ /*public*/ void FileUtil::setProgramPath(QString path)
{
 FileUtilSupport::getDefault()->setProgramPath(new File(path));

}

/**
 * Set the JMRI program directory.
 *
 * If set, allows JMRI to be loaded from locations other than the directory
 * containing JMRI resources. This must be set very early in the process of
 * loading JMRI (prior to loading any other JMRI code) to be meaningfully
 * used.
 *
 * @param path
 */
/*static*/ /*public*/ void FileUtil::setProgramPath(File* path)
{
 FileUtilSupport::getDefault()->setProgramPath(path);
}

/**
 * Get the URL of a portable filename if it can be located using
 * {@link #findURL(java.lang.QString)}
 *
 * @param path
 */
/*static*/ /*public*/ QUrl FileUtil::findExternalFilename(QString path) {
    return FileUtil::findURL(FileUtil::getExternalFilename(path));
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.io.InputStream} for that file. Search order is defined by
 * {@link #findURL(java.lang.QString, java.lang.QString[])}.
 *
 * @param path The relative path of the file or resource.
 * @return InputStream or NULL.
 * @see #findInputStream(java.lang.QString, java.lang.QString[])
 * @see #findURL(java.lang.QString)
 * @see #findURL(java.lang.QString, java.lang.QString[])
 */
//static /*public*/ InputStream findInputStream(QString path) {
/*static*/ /*public*/ QTextStream* FileUtil::findInputStream(QString path) {
    return FileUtil::findInputStream(path, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.io.InputStream} for that file. Search order is defined by
 * {@link #findURL(java.lang.QString, java.lang.QString[])}.
 *
 * @param path The relative path of the file or resource.
 * @param searchPaths a list of paths to search for the path in
 * @return InputStream or NULL.
 * @see #findInputStream(java.lang.QString, java.lang.QString[])
 * @see #findURL(java.lang.QString)
 * @see #findURL(java.lang.QString, java.lang.QString[])
 */
//static /*public*/ InputStream findInputStream(QString path, @NonNull QString... searchPaths) {
/*static*/ /*public*/ QTextStream* FileUtil::findInputStream(QString path, /*@NonNull*/ QStringList searchPaths) {
    QUrl file = FileUtil::findURL(path, searchPaths);
    if (file.isValid()) {
//        try {
//            return file.openStream();
     QFile* f = new QFile(file.fileName());
     if(f != NULL && f->open(QIODevice::ReadOnly))
     {
      QTextStream* stream = new QTextStream(f);
      return stream;
     }
//        } catch (IOException ex) {
//            log.error(ex.getLocalizedMessage(), ex);
//        }
    }
    return NULL;
}

/**
 * Get the resources directory within the user's files directory.
 *
 * @return path to [user's file]/resources/
 */
/*static*/ /*public*/ QString FileUtil::getUserResourcePath()
{
 return FileUtil::getUserFilesPath() + "resources" + QDir::separator(); // NOI18N
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file. Search order is defined by
 * {@link #findURL(java.lang.QString, java.lang.QString[])}.
 *
 * @param path The relative path of the file or resource.
 * @return The URL or NULL.
 * @see #findInputStream(java.lang.QString)
 * @see #findInputStream(java.lang.QString, java.lang.QString[])
 * @see #findURL(java.lang.QString, java.lang.QString[])
 */
/*static*/ /*public*/ QUrl FileUtil::findURL(QString path) {
    return FileUtil::findURL(path, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file. <p> Search order is:<ol><li>For any
 * provided searchPaths, iterate over the searchPaths by prepending each
 * searchPath to the path and following the following search order:</li>
 * <ol><li>As a {@link java.io.File} in the user preferences directory</li>
 * <li>As a File in the current working directory (usually, but not always
 * the JMRI distribution directory)</li> <li>As a File in the JMRI
 * distribution directory</li> <li>As a resource in jmri.jar</li></ol>
 * <li>If the file or resource has not been found in the searchPaths, search
 * in the four locations listed without prepending any path</li></ol>
 *
 * @param path The relative path of the file or resource
 * @param searchPaths a list of paths to search for the path in
 * @return The URL or NULL
 * @see #findInputStream(java.lang.QString)
 * @see #findInputStream(java.lang.QString, java.lang.QString[])
 * @see #findURL(java.lang.QString)
 */
/*static*/ /*public*/ QUrl FileUtil::findURL(QString path, /*@NonNull*/ QStringList searchPaths)
{
 Logger log;
 if (log.isDebugEnabled())
 {
  log.debug("Attempting to find " + path /*+ " in " + Arrays.toString(searchPaths)*/);
 }
 QUrl resource;
 if (!searchPaths.isEmpty())
 {
  foreach(QString searchPath,  searchPaths)
  {
   resource = FileUtil::findURL(searchPath + QDir::separator() + path);
   if (!resource .isEmpty())
   {
    return resource;
   }
  }
 }
 try
 {
  if(QFile(path).exists())
   return QUrl(path);
  // attempt to return path from preferences directory
  QFile* file = new QFile(FileUtil::getUserFilesPath() + path);
  if (file->exists())
  {
   //return file->toURI().toURL();
   return QUrl(file->fileName());
  }
  // attempt to return path from current working directory
  file = new QFile(path);
  if (file->exists())
  {
   //return file.toURI().toURL();
   return QUrl(file->fileName());

  }
  // attempt to return path from JMRI distribution directory
  file = new QFile(FileUtil::getProgramPath() + path);
  if (file->exists())
  {
   //return file.toURI().toURL();
  return QUrl(file->fileName());

  }
 }
 catch (MalformedURLException ex)
 {
  log.warn("Unable to get URL for " + path + ex.getMessage());
  return QUrl();
 }
//    // return path if in jmri.jar or NULL
//    resource = FileUtil.class.getClassLoader().getResource(path);
//    if (resource == NULL && log.isDebugEnabled()) {
//        log.debug("Unable to to get URL for " + path);
//    }
//    return resource;
 return QUrl();
}
/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file. Search order is defined by
 * {@link #findURL(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 *
 * @param path      The relative path of the file or resource
 * @param locations The types of locations to limit the search to
 * @return The URL or null
 * @see #findURL(java.lang.String)
 * @see #findURL(java.lang.String, java.lang.String...)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*static*/ /*public*/ QUrl FileUtil::findURL(QString path, Location locations) {
    return FileUtil::findURL(path, locations, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file.
 * <p>
 * Search order is:
 * <ol><li>For any provided searchPaths, iterate over the searchPaths by
 * prepending each searchPath to the path and following the following search
 * order:
 * <ol><li>As a {@link java.io.File} in the user preferences directory</li>
 * <li>As a File in the current working directory (usually, but not always
 * the JMRI distribution directory)</li> <li>As a File in the JMRI
 * distribution directory</li> <li>As a resource in jmri.jar</li></ol></li>
 * <li>If the file or resource has not been found in the searchPaths, search
 * in the four locations listed without prepending any path</li></ol>
 * <p>
 * The <code>locations</code> parameter limits the above logic by limiting
 * the location searched.
 * <ol><li>{@link Location#ALL} will not place any limits on the
 * search</li><li>{@link Location#NONE} effectively requires that
 * <code>path</code> be a portable
 * pathname</li><li>{@link Location#INSTALLED} limits the search to the
 * {@link #PROGRAM} directory and JARs in the class
 * path</li><li>{@link Location#USER} limits the search to the
 * {@link #PROFILE} directory</li></ol>
 *
 * @param path        The relative path of the file or resource
 * @param locations   The types of locations to limit the search to
 * @param searchPaths a list of paths to search for the path in
 * @return The URL or null
 * @see #findURL(java.lang.String)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURL(java.lang.String, java.lang.String...)
 */
/*static*/ /*public*/ QUrl FileUtil::findURL(QString path, Location locations, /*@Nonnull*/ QStringList searchPaths)
{
 Logger log("FileUtil");
    if (log.isDebugEnabled()) { // avoid the Arrays.toString call unless debugging
        log.debug(QString("Attempting to find %1 in %2").arg(path).arg(/*Arrays.toString(searchPaths)*/""));
    }
    if (FileUtil::isPortableFilename(path)) {
        return FileUtil::findExternalFilename(path);
    }
    QUrl resource = QUrl();
    foreach (QString searchPath, searchPaths) {
        resource = FileUtil::findURL(searchPath + QDir::separator() + path);
        if (resource != QUrl()) {
            return resource;
        }
    }
    try {
        QFileInfo file;
        if (locations == ALL || locations == USER) {
            // attempt to return path from preferences directory
            file =  QFile(FileUtil::getUserFilesPath() + path);
            if (file.exists()) {
                //return file.toURI().toURL();
             return QUrl(file.absoluteFilePath());
            }
        }
        if (locations == ALL || locations == INSTALLED) {
            // attempt to return path from current working directory
            file =  QFileInfo(path);
            if (file.exists()) {
                //return file.toURI().toURL();
                return QUrl(file.absoluteFilePath());

            }
            // attempt to return path from JMRI distribution directory
            file =  QFileInfo(FileUtil::getProgramPath() + path);
            if (file.exists()) {
                //return file.toURI().toURL();
                return QUrl(file.absoluteFilePath());

            }
        }
    } catch (MalformedURLException ex) {
        log.warn(QString("Unable to get URL for %1").arg(path).arg( ex.getMessage()));
        return QUrl();
    }
//    if (locations == Location::ALL || locations == Location::INSTALLED) {
//        // return path if in jmri.jar or null
//        resource = FileUtil.class.getClassLoader().getResource(path);
//        if (resource == null) {
//            log.debug("Unable to get URL for {}", path);
//        }
//    }
    return resource;
}

/**
 * Return the {@link java.net.URI} for a given URL
 *
 * @param url
 * @return a URI or NULL if the conversion would have caused a
 * {@link java.net.URISyntaxException}
 */
//static /*public*/ URI urlToURI(URL url) {
//    try {
//        return url.toURI();
//    } catch (URISyntaxException ex) {
//        log.error("Unable to get URI from URL", ex);
//        return NULL;
//    }
//}

/**
 * Return the {@link java.net.URL} for a given {@link java.io.File}. This
 * method catches a {@link java.net.MalformedURLException} and returns NULL
 * in its place, since we really do not expect a File object to ever give a
 * malformed URL. This method exists solely so implementing classes do not
 * need to catch that exception.
 *
 * @param file The File to convert.
 * @return a URL or NULL if the conversion would have caused a
 * MalformedURLException
 */
/*static*/ /*public*/ QUrl FileUtil::fileToURL(QFile* file) {
//    try {
//        return file.toURI().toURL();
//    } catch (MalformedURLException ex) {
//        log.error("Unable to get URL from file", ex);
//        return NULL;
//    }
 return QUrl(file->fileName());
}
/*static*/ /*public*/ QUrl FileUtil::fileToURL(File* file)
{
    return QUrl(file->path) ;
}

#if 0
    /**
     * Get the JMRI distribution jar file.
     *
     * @return a {@link java.util.jar.JarFile} pointing to jmri.jar or NULL
     */
    static /*public*/ JarFile jmriJarFile() {
        if (jarPath == NULL) {
            CodeSource sc = FileUtil.class.getProtectionDomain().getCodeSource();
            if (sc != NULL) {
                jarPath = sc.getLocation().toString();
                // 9 = length of jar:file:
                jarPath = jarPath.mid(9, jarPath.lastIndexOf("!"));
                log.debug("jmri.jar path is " + jarPath);
            }
        }
        try {
            return new JarFile(jarPath);
        } catch (IOException ex) {
            log.error("Unable to open jmri.jar", ex);
            return NULL;
        }
    }
#endif
/*static*/ /*public*/ void FileUtil::logFilePaths()
{
 Logger log;
    log.info("File path " + FileUtil::PROGRAM + " is " + FileUtil::getProgramPath());
    log.info("File path " + FileUtil::PREFERENCES + " is " + FileUtil::getUserFilesPath());
    log.info("File path " + FileUtil::HOME + " is " + FileUtil::getHomePath());
}

/**
 * Get the path to the scripts directory.
 *
 * @return the scriptsPath
 */
/*public*/ /*static*/ QString FileUtil::getScriptsPath()
{
 if (scriptsPath != NULL)
 {
  return scriptsPath;
 }
 // scriptsPath not set by user, return default if it exists
 QFileInfo* file = new QFileInfo(FileUtil::getProgramPath() + QDir::separator() + "jython" + QDir::separator()); // NOI18N
 if (file->exists())
 {
  return file->path();
 }
 // if default does not exist, return user's files directory
 return FileUtil::getUserFilesPath();
}

/**
 * Set the path to python scripts.
 *
 * @param path the scriptsPath to set
 */
/*public*/ /*static*/ void FileUtil::setScriptsPath(QString path) {
     FileUtilSupport::getDefault()->setScriptsPath(path);
}

/**
  * Read a text file into a String.
  *
  * @param file The text file.
  * @return The contents of the file.
  * @throws java.io.IOException if the file cannot be read
  */
 /*public*/ /*static*/ QString FileUtil::readFile(File* file) //throw (IOException)
    {
     return FileUtil::readURL(FileUtil::fileToURL(file));
 }
/**
  * Read a text URL into a String. Would be significantly simpler with Java
  * 7. File is assumed to be encoded using UTF-8
  *
  * @param url The text URL.
  * @return The contents of the file.
  * @throws java.io.IOException if the URL cannot be read
  */
 /*public*/ /*static*/ QString FileUtil::readURL(QUrl url) //throw (IOException)
    {
     return FileUtilSupport::getDefault()->readURL(url);
 }
/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 * @param path
 */
/*public*/ /*static*/ void FileUtil::createDirectory(QString path)
{
 FileUtilSupport::getDefault()->createDirectory(path);
}
/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 */
/*public*/ /*static*/ void FileUtil::createDirectory(File* dir)
{
 FileUtilSupport::getDefault()->createDirectory(dir);
}
/**
 * Replaces most non-alphanumeric characters in name with an underscore.
 *
 * @param name The filename to be sanitized.
 * @return The sanitized filename.
 */
/*public*/ /*static*/ QString FileUtil::sanitizeFilename(QString name) {
     return FileUtilSupport::getDefault()->sanitizeFilename(name);
}

/**
 * Recursively delete a path. Not needed in Java 1.7.
 *
 * @param path
 * @return true if path was deleted, false otherwise
 */
/*public*/ /*static*/ bool FileUtil::_delete(File* path)
{
 return FileUtilSupport::getDefault()->_delete(path);
}

/**
 * Copy a file. Not needed in Java 1.7.
 *
 * @param source
 * @param dest must be the file, not the destination directory.
 * @throws IOException
 */
/*public*/ /*static*/ void FileUtil::copy(File* source, File* dest) /*throws IOException*/
{
 FileUtilSupport::getDefault()->copy(source, dest);
}
#if 0
/**
 * Simple helper method to just append a text string to the end of the given
 * filename. The file will be created if it does not exist.
 *
 * @param file File to append text to
 * @param text Text to append
 * @throws java.io.IOException if file cannot be written to
 */
/*public*/ static void appendTextToFile(File* file, QString text) /*throws IOException*/
{
    PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream(file, true), "UTF-8")); // NOI18N
    pw.println(text);
    pw.close();
}
#endif
/**
 * Backup a file.
 *
 * @see jmri.util.FileUtilSupport#backup(java.io.File)
 */
/*public*/ /*static*/ void FileUtil::backup(File* file) //throws IOException
{
  FileUtilSupport::getDefault()->backup(file);
}

/*public*/ /*static*/ QStringList* FileUtil::findProgramPath()
{
 return FileUtilSupport::getDefault()->findProgramPath();
}
