#include "fileutilsupport.h"
#include <QDir>
#include "file.h"
#include "fileutil.h"
#include "system.h"
#include <QUrl>
#include "matcher.h"
#include <QDebug>

/**
 * Support the {@link jmri.util.FileUtil } static API while providing
 * {@link java.beans.PropertyChangeSupport} for listening to changes in the
 * paths.
 *
 * @author Randall Wood (C) 2015
 */
///*public*/ class FileUtilSupport extends Bean {

/* User's home directory */
/*private*/ /*static*/ /*final*/ QString FileUtilSupport::homePath = QDir::homePath() + File::separator;//System.getProperty("user.home") + File.separator; // NOI18N
// default instance
/*volatile*/ /*private*/ /*static*/ FileUtilSupport* FileUtilSupport::defaultInstance = NULL;

/*public*/ FileUtilSupport::FileUtilSupport() : Bean()
{
 programPath = "";
#if 1 // override program path for development
//programPath = QDir::homePath() + QDir::separator()+"NetBeansProjects"+QDir::separator()+"jmri"+ QDir::separator();
#endif
 jarPath = "";
 scriptsPath = "";
 userFilesPath = "";
 profilePath = "";
 log = new Logger("FileUtilSupport");
}

/**
 * Get the {@link java.io.File} that path refers to. Throws a
 * {@link java.io.FileNotFoundException} if the file cannot be found instead
 * of returning null (as File would). Use {@link #getURI(java.lang.String) }
 * or {@link #getURL(java.lang.String) } instead of this method if possible.
 *
 * @param path the path to find
 * @return {@link java.io.File} at path
 * @throws java.io.FileNotFoundException if path cannot be found
 * @see #getURI(java.lang.String)
 * @see #getURL(java.lang.String)
 */
/*public*/ File* FileUtilSupport::getFile(QString path) throw (FileNotFoundException)
{
 File* file;
 try
 {
  QString realPath = pathFromPortablePath(path);
  QFileInfo info(realPath);
  if(!info.exists())
   throw FileNotFoundException();
  file = new File(realPath);
  if(!file->exists())
   throw FileNotFoundException(tr("File not found: %s").arg(file->getPath()));
 } 
 catch (NullPointerException ex) 
 {
  throw  FileNotFoundException("Cannot find file at " + path);
 }
 catch (IOException ex)
 {
  throw  FileNotFoundException("Cannot find file at " + path);
 }
 return file;
}
#if 0
/**
 * Get the {@link java.io.File} that path refers to. Throws a
 * {@link java.io.FileNotFoundException} if the file cannot be found instead
 * of returning null (as File would).
 *
 * @param path the path to find
 * @return {@link java.io.File} at path
 * @throws java.io.FileNotFoundException if path cannot be found
 * @see #getFile(java.lang.String)
 * @see #getURL(java.lang.String)
 */
/*public*/ URI getURI(String path) throws FileNotFoundException {
    return this->getFile(path).toURI();
}
#endif
/**
 * Get the {@link java.net.URL} that path refers to. Throws a
 * {@link java.io.FileNotFoundException} if the URL cannot be found instead
 * of returning null.
 *
 * @param path the path to find
 * @return {@link java.net.URL} at path
 * @throws java.io.FileNotFoundException if path cannot be found
 * @see #getFile(java.lang.String)
 * @see #getURI(java.lang.String)
 */
/*public*/ QUrl* FileUtilSupport::getURL(QString path) throw (FileNotFoundException)
{
//    try {
//        return thisgetURI(path).toURL();
//    } catch (MalformedURLException ex) {
//        throw new FileNotFoundException("Cannot create URL for file at " + path);
//    }
  QUrl* url = new QUrl(path);
  if(url->isEmpty() || !url->isValid())
   throw new FileNotFoundException("Cannot create URL for file at " + path);
  return url;
}

#if 0
/**
 * Convenience method to get the {@link java.net.URL} from a
 * {@link java.net.URI}. Logs errors and returns null if any exceptions are
 * thrown by the conversion.
 *
 * @param uri The URI to convert.
 * @return URL or null if any errors exist.
 */
public URL getURL(URI uri) {
    try {
        return uri.toURL();
    } catch (MalformedURLException | IllegalArgumentException ex) {
        log->warn("Unable to get URL from {}", uri.toString());
        return null;
    } catch (NullPointerException ex) {
        log->warn("Unable to get URL from null object.", ex);
        return null;
    }
}
#endif
/**
 * Get the resource file corresponding to a name. There are five cases:
 * <ul>
 * <li>Starts with "resource:", treat the rest as a pathname relative to the
 * program directory (deprecated; see "program:" below)</li>
 * <li>Starts with "program:", treat the rest as a relative pathname below
 * the program directory</li>
 * <li>Starts with "preference:", treat the rest as a relative path below
 * the user's files directory</li>
 * <li>Starts with "settings:", treat the rest as a relative path below the
 * JMRI system preferences directory</li>
 * <li>Starts with "home:", treat the rest as a relative path below the
 * user.home directory</li>
 * <li>Starts with "file:", treat the rest as a relative path below the
 * resource directory in the preferences directory (deprecated; see
 * "preference:" above)</li>
 * <li>Starts with "profile:", treat the rest as a relative path below the
 * profile directory as specified in the
 * active{@link jmri.profile.Profile}</li>
 * <li>Starts with "scripts:", treat the rest as a relative path below the
 * scripts directory</li>
 * <li>Otherwise, treat the name as a relative path below the program
 * directory</li>
 * </ul>
 * In any case, absolute pathnames will work.
 *
 * @param pName The name string, possibly starting with file:, home:,
 *              profile:, program:, preference:, scripts:, settings, or
 *              resource:
 * @return Absolute file name to use, or null. This will include
 *         system-specific file separators.
 * @since 2.7.2
 */
/*public*/ QString FileUtilSupport::getExternalFilename(QString pName) {
    QString filename = this->pathFromPortablePath(pName);
    return (filename != "") ? filename : pName.replace(FileUtil::SEPARATOR, File::separatorChar);
}

/**
 * Convert a portable filename into an absolute filename.
 *
 * @param path the portable filename
 * @return An absolute filename
 */
/*public*/ QString FileUtilSupport::getAbsoluteFilename(QString path) {
    return this->pathFromPortablePath(path);
}

/**
 * Convert a File object's path to our preferred storage form.
 *
 * This is the inverse of {@link #getFile(String pName)}. Deprecated forms
 * are not created.
 *
 * @param file File at path to be represented
 * @return Filename for storage in a portable manner. This will include
 *         portable, not system-specific, file separators.
 * @since 2.7.2
 */
/*public*/ QString FileUtilSupport::getPortableFilename(File* file) {
    return this->getPortableFilename(file, false, false);
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
 * @param file                File at path to be represented
 * @param ignoreUserFilesPath true if paths in the User files path should be
 *                            stored as absolute paths, which is often not
 *                            desirable.
 * @param ignoreProfilePath   true if paths in the profile should be stored
 *                            as absolute paths, which is often not
 *                            desirable.
 * @return Storage format representation
 * @since 3.5.5
 */
/*public*/ QString FileUtilSupport::getPortableFilename(File* file, bool ignoreUserFilesPath, bool ignoreProfilePath) {
    // compare full path name to see if same as preferences
    QString filename = file->getAbsolutePath();

    // append separator if file is a directory
    if (file->isDirectory()) {
        filename = filename + File::separator;
    }

    // compare full path name to see if same as preferences
    QString ufp = getUserFilesPath();
    if (!ignoreUserFilesPath) {
        if (filename.startsWith(getUserFilesPath())) {
            return FileUtil::PREFERENCES + filename.mid(getUserFilesPath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
        }
    }

    if (!ignoreProfilePath) {
        // compare full path name to see if same as profile
        if (filename.startsWith(getProfilePath())) {
            return FileUtil::PROFILE + filename.mid(getProfilePath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
        }
    }

    // compare full path name to see if same as settings
    if (filename.startsWith(getPreferencesPath())) {
        return FileUtil::SETTINGS + filename.mid(getPreferencesPath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
    }

    if (!ignoreUserFilesPath) {
        /*
         * The tests for any portatable path that could be within the
         * UserFiles locations needs to be within this block. This prevents
         * the UserFiles or Profile path from being set to another portable
         * path that is user settable.
         *
         * Note that this test should be after the UserFiles, Profile, and
         * Preferences tests.
         */
        // check for relative to scripts dir
        if (filename.startsWith(getScriptsPath()) && filename !=(getScriptsPath())) {
            return FileUtil::SCRIPTS + filename.mid(getScriptsPath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
        }
    }

    // now check for relative to program dir
    if (filename.startsWith(getProgramPath())) {
        return FileUtil::PROGRAM + filename.mid(getProgramPath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
    }

    // compare full path name to see if same as home directory
    // do this last, in case preferences or program dir are in home directory
    if (filename.startsWith(getHomePath())) {
        return FileUtil::HOME + filename.mid(getHomePath().length(), filename.length()).replace(File::separatorChar, FileUtil::SEPARATOR);
    }

    return filename.replace(File::separatorChar, FileUtil::SEPARATOR);   // absolute, and doesn't match; not really portable...
}

/**
 * Convert a filename string to our preferred storage form.
 *
 * This is the inverse of {@link #getExternalFilename(String pName)}.
 * Deprecated forms are not created.
 *
 * @param filename Filename to be represented
 * @return Filename for storage in a portable manner
 * @since 2.7.2
 */
/*public*/ QString FileUtilSupport::getPortableFilename(QString filename) {
    return this->getPortableFilename(filename, false, false);
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
 * @param filename            Filename to be represented
 * @param ignoreUserFilesPath true if paths in the User files path should be
 *                            stored as absolute paths, which is often not
 *                            desirable.
 * @param ignoreProfilePath   true if paths in the profile path should be
 *                            stored as absolute paths, which is often not
 *                            desirable.
 * @return Storage format representation
 * @since 3.5.5
 */
/*public*/ QString FileUtilSupport::getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath) {
    if (this->isPortableFilename(filename)) {
        // if this already contains prefix, run through conversion to normalize
        return getPortableFilename(getExternalFilename(filename), ignoreUserFilesPath, ignoreProfilePath);
    } else {
        // treat as pure filename
        return getPortableFilename(new File(filename), ignoreUserFilesPath, ignoreProfilePath);
    }
}

/**
 * Test if the given filename is a portable filename.
 *
 * Note that this method may return a false positive if the filename is a
 * file: URL.
 *
 * @param filename the name to test
 * @return true if filename is portable
 */
//@SuppressWarnings("deprecation")
/*public*/ bool FileUtilSupport::isPortableFilename(QString filename) {
    return (filename.startsWith(FileUtil::PROGRAM)
            || filename.startsWith(FileUtil::HOME)
            || filename.startsWith(FileUtil::PREFERENCES)
            || filename.startsWith(FileUtil::SCRIPTS)
            || filename.startsWith(FileUtil::PROFILE)
            || filename.startsWith(FileUtil::SETTINGS));
}

/**
 * Get the user's home directory.
 *
 * @return User's home directory as a String
 */
/*public*/ QString FileUtilSupport::getHomePath() {
    return homePath;
}

/**
 * Get the user's files directory. If not set by the user, this is the same
 * as the profile path.
 *
 * @see #getProfilePath()
 * @return User's files directory as a String
 */
/*public*/ QString FileUtilSupport::getUserFilesPath() {
    return (this->userFilesPath != NULL) ? this->userFilesPath : this->getProfilePath();
}

/**
 * Set the user's files directory.
 *
 * @see #getUserFilesPath()
 * @param path The path to the user's files directory using system-specific separators
 */
/*public*/ void FileUtilSupport::setUserFilesPath(QString path) {
    QString old = this->userFilesPath;
    if (path != NULL && !path.endsWith(File::separator)) {
        path = path + File::separator;
    }
    this->userFilesPath = path;
    if ((old != NULL && old != (path)) || (path != NULL && path != (old))) {
        this->firePropertyChange(FileUtil::PREFERENCES, old, path);
    }
}

/**
 * Get the profile directory. If not set, this is the same as the
 * preferences path.
 *
 * @see #getPreferencesPath()
 * @return Profile directory as a String using system-specific separators
 */
/*public*/ QString FileUtilSupport::getProfilePath() {
    return (this->profilePath != NULL) ? this->profilePath : this->getPreferencesPath();
}

/**
 * Set the profile directory.
 *
 * @see #getProfilePath()
 * @param path The path to the profile directory using system-specific separators.
 */
/*public*/ void FileUtilSupport::setProfilePath(QString path)
{
  QString old = this->profilePath;
  if (path != NULL && !path.endsWith(File::separator))
  {
   path = path + File::separator;
  }
  this->profilePath = path;
  if ((old != NULL && old != (path)) || (path != NULL && path != (old)))
  {
   //this->firePropertyChange(FileUtil::PROFILE, old, path);
  }
  // ACK fix to prevent roster entries with incorrect paths when saved.
  if(userFilesPath == "")
   userFilesPath = homePath + ".jmri" + File::separator;
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
 * @return Path to the preferences directory using system-specific separators.
 */
/*public*/ QString FileUtilSupport::getPreferencesPath() {
    // return jmri.prefsdir property if present
    QString jmriPrefsDir = System::getProperty("jmri.prefsdir", ""); // NOI18N
    if (!jmriPrefsDir.isEmpty() && !jmriPrefsDir.endsWith(File::separator)) {
        return jmriPrefsDir + File::separator;
    }
    QString result;
//    switch (SystemType.getType()) {
//        case SystemType.MACOSX:
#ifdef Q_OS_MAC
            // Mac OS X
            result = this->getHomePath() + "Library" + File.separator + "Preferences" + File.separator + "JMRI" + File.separator; // NOI18N
#endif
#if 0
            break;
        case SystemType.LINUX:
        case SystemType.UNIX:
#endif
#ifdef Q_OS_LINUX || Q_OS_UNIX
            // Linux, so use an invisible file
            result = this->getHomePath() + ".jmri" + File::separator; // NOI18N
#endif
#if 0
            break;
        case SystemType.WINDOWS:
        default:
#endif
#ifdef  Q_OS_WIN
            // Could be Windows, other
            result = this->getHomePath() + "JMRI" + File.separator; // NOI18N
#endif
#if 0
            break;
    }
#endif
    // logging here merely throws warnings since we call this method to setup logging
    // uncomment below to print OS default to console
    // System.out.println("preferencesPath defined as \"" + result + "\" based on os.name=\"" + SystemType.getOSName() + "\"");
    return result;
}

/**
 * Get the JMRI program directory.
 *
 * @return JMRI program directory as a String.
 */
/*public*/ QString FileUtilSupport::getProgramPath() {
    if (programPath == NULL) {
//        this->setProgramPath("."); // NOI18N
     QStringList* paths = findProgramPath();
     if(!paths->isEmpty())
      this->programPath = (paths->at(0) + File::separator);
    }
    return programPath;
}

/**
 * Set the JMRI program directory.
 *
 * Convenience method that calls
 * {@link FileUtil#setProgramPath(java.io.File)} with the passed in path.
 *
 */
/*public*/ void FileUtilSupport::setProgramPath(QString path) {
    this->setProgramPath(new File(path));
}

/**
 * Set the JMRI program directory.
 * <p>
 * If set, allows JMRI to be loaded from locations other than the directory
 * containing JMRI resources. This must be set very early in the process of
 * loading JMRI (prior to loading any other JMRI code) to be meaningfully
 * used.
 *
 */
/*public*/ void FileUtilSupport::setProgramPath(File* path)
{
 QString old = this->programPath;
 try {
     this->programPath = (path)->getCanonicalPath() + File::separator;
 } catch (IOException ex) {
     log->error("Unable to get JMRI program directory.", ex.getMessage());
 }
 if ((old != NULL && old != (this->programPath))
         || (this->programPath != NULL && this->programPath !=(old)))
 {
     this->firePropertyChange(FileUtil::PROGRAM, old, this->programPath);
 }
}

/**
 * Get the resources directory within the user's files directory.
 *
 * @return path to [user's file]/resources/  using system-specific separators
 */
/*public*/ QString FileUtilSupport::getUserResourcePath() {
    return this->getUserFilesPath() + "resources" + File::separator; // NOI18N
}

/**
 * Log all paths at the INFO level.
 */
/*public*/ void FileUtilSupport::logFilePaths() {
    log->info(tr("File path %1 is %2").arg(FileUtil::PROGRAM).arg(this->getProgramPath()));
    log->info(tr("File path %1 is %2").arg(FileUtil::PREFERENCES).arg(this->getUserFilesPath()));
    log->info(tr("File path %1 is %2").arg(FileUtil::PROFILE).arg(this->getProfilePath()));
    log->info(tr("File path %1 is %2").arg(FileUtil::SETTINGS).arg(this->getPreferencesPath()));
    log->info(tr("File path %1 is %2").arg(FileUtil::HOME).arg(this->getHomePath()));
    log->info(tr("File path %1 is %2").arg(FileUtil::SCRIPTS).arg(this->getScriptsPath()));
}

/**
 * Get the path to the scripts directory.
 *
 * @return the scriptsPath using system-specific separators
 */
/*public*/ QString FileUtilSupport::getScriptsPath() {
    if (scriptsPath != NULL) {
        return scriptsPath;
    }
    // scriptsPath not set by user, return default if it exists
    File* file = new File(this->getProgramPath() + File::separator + "jython" + File::separator); // NOI18N
    if (file->exists() && file->isDirectory()) {
        return file->getPath() + File::separator;
    }
    // if default does not exist, return user's files directory
    return this->getUserFilesPath();
}

/**
 * Set the path to python scripts.
 *
 * @param path the scriptsPath to set
 */
/*public*/ void FileUtilSupport::setScriptsPath(QString path) {
    QString old = this->scriptsPath;
    if (path != NULL && !path.endsWith(File::separator)) {
        path = path + File::separator;
    }
    this->scriptsPath = path;
    if ((old != NULL && old != (path)) || (path != NULL && path != (old))) {
        this->firePropertyChange(FileUtil::SCRIPTS, old, path);
    }
}
#if 0
/**
 * Get the JMRI distribution jar file.
 *
 * @return a {@link java.util.jar.JarFile} pointing to jmri.jar or NULL
 */
/*public*/ JarFile getJmriJarFile() {
    if (jarPath == NULL) {
        CodeSource sc = FileUtil::class.getProtectionDomain().getCodeSource();
        if (sc != NULL) {
            jarPath = sc.getLocation().toString();
            // 9 = length of jar:file:
            jarPath = jarPath.substring(9, jarPath.lastIndexOf("!"));
            log->debug("jmri.jar path is {}", jarPath);
        }
        if (jarPath == NULL) {
            log->error("Unable to locate jmri.jar");
            return NULL;
        }
    }
    try {
        return new JarFile(jarPath);
    } catch (IOException ex) {
        log->error("Unable to open jmri.jar", ex);
        return NULL;
    }
}
#endif
/**
 * Backup a file. The backup is in the same location as the original file,
 * has the extension <code>.bak</code> appended to the file name, and up to
 * four revisions are retained. The lowest numbered revision is the most
 * recent.
 *
 */
/*public*/ void FileUtilSupport::backup(File* file) //throws IOException
{
    this->rotate(file, 4, "bak");
}

/**
 * Rotate a file.
 *
 * @param file      The file to rotate
 * @param max       A positive integer
 * @param extension The extension to use for the rotations. If NULL or an
 *                  empty string, the rotation number is used as the
 *                  extension.
 * @throws IllegalArgumentException if max is less than one
 * @see #backup(java.io.File)
 */
/*public*/ void FileUtilSupport::rotate(/*@NonNULL*/ File* file, int max, QString extension) //throws IOException
{
    if (max < 1) {
        //throw new IllegalArgumentException();
     return;
    }
    QString name = file->getName();
    if (extension != NULL) {
        if (extension.length() > 0 && !extension.startsWith(".")) {
            extension = "." + extension;
        }
    } else {
        extension = "";
    }
    File* dir = file->getParentFile();
    File* source;
    int i = max;
    while (i > 1) {
        source = new File(dir, name + "." + QString::number(i - 1) + extension);
        if (source->exists()) {
            FileUtil::copy(source, new File(dir, name + "." + QString::number(i) + extension));
        }
        i--;
    }
    FileUtil::copy(file, new File(dir, name + "." + QString::number(i) + extension));
}

/*public*/ /*static*/ FileUtilSupport* FileUtilSupport::getDefault() {
    if (FileUtilSupport::defaultInstance == NULL) {
        FileUtilSupport::defaultInstance = new FileUtilSupport();
    }
    return FileUtilSupport::defaultInstance;
}

/**
 * Get the canonical path for a portable path. There are nine cases:
 * <ul>
 * <li>Starts with "resource:", treat the rest as a pathname relative to the
 * program directory (deprecated; see "program:" below)</li>
 * <li>Starts with "program:", treat the rest as a relative pathname below
 * the program directory</li>
 * <li>Starts with "preference:", treat the rest as a relative path below
 * the user's files directory</li>
 * <li>Starts with "settings:", treat the rest as a relative path below the
 * JMRI system preferences directory</li>
 * <li>Starts with "home:", treat the rest as a relative path below the
 * user.home directory</li>
 * <li>Starts with "file:", treat the rest as a relative path below the
 * resource directory in the preferences directory (deprecated; see
 * "preference:" above)</li>
 * <li>Starts with "profile:", treat the rest as a relative path below the
 * profile directory as specified in the
 * active{@link jmri.profile.Profile}</li>
 * <li>Starts with "scripts:", treat the rest as a relative path below the
 * scripts directory</li>
 * <li>Otherwise, treat the name as a relative path below the program
 * directory</li>
 * </ul>
 * In any case, absolute pathnames will work.
 *
 * @param path The name string, possibly starting with file:, home:,
 *             profile:, program:, preference:, scripts:, settings, or
 *             resource:
 * @return Canonical path to use, or null if one cannot be found.
 * @since 2.7.2
 */
//@SuppressWarnings("deprecation")
/*private*/ QString FileUtilSupport::pathFromPortablePath(/*@Nonnull*/ QString path) {
    if (path.startsWith(FileUtil::PROGRAM))
    {
        if ((new File(path.mid(FileUtil::PROGRAM.length())))->isAbsolute())
        {
            path = path.mid(FileUtil::PROGRAM.length());
        } else {
            path = path.replace(FileUtil::PROGRAM, Matcher::quoteReplacement(this->getProgramPath()));
        }
    }
    else if (path.startsWith(FileUtil::PREFERENCES))
    {
        if ((new File(path.mid(FileUtil::PREFERENCES.length())))->isAbsolute())
        {
            path = path.mid(FileUtil::PREFERENCES.length());
        }
        else
        {
            path = path.replace(FileUtil::PREFERENCES, Matcher::quoteReplacement(this->getUserFilesPath()));
        }
    }
    else if (path.startsWith(FileUtil::PROFILE))
    {
        if ((new File(path.mid(FileUtil::PROFILE.length())))->isAbsolute()) {
            path = path.mid(FileUtil::PROFILE.length());
        } else {
            path = path.replace(FileUtil::PROFILE, Matcher::quoteReplacement(this->getProfilePath()));
        }
    } else if (path.startsWith(FileUtil::SCRIPTS)) {
        if ((new File(path.mid(FileUtil::SCRIPTS.length())))->isAbsolute()) {
            path = path.mid(FileUtil::SCRIPTS.length());
        } else {
            path = path.replace(FileUtil::SCRIPTS, Matcher::quoteReplacement(this->getScriptsPath()));
        }
    } else if (path.startsWith(FileUtil::SETTINGS)) {
        if ((new File(path.mid(FileUtil::SETTINGS.length())))->isAbsolute()) {
            path = path.mid(FileUtil::SETTINGS.length());
        } else {
            path = path.replace(FileUtil::SETTINGS, Matcher::quoteReplacement(this->getPreferencesPath()));
        }
    }
    else if (path.startsWith(FileUtil::HOME)) {
        if ((new File(path.mid(FileUtil::HOME.length())))->isAbsolute()) {
            path = path.mid(FileUtil::HOME.length());
        } else {
            path = path.replace(FileUtil::HOME, Matcher::quoteReplacement(this->getHomePath()));
        }
    }
    else if (!(new File(path))->isAbsolute()) {
        return "";
    }
    try {
        // if path cannot be converted into a canonical path, return null
     Q_ASSERT(path != "/");
     Q_ASSERT(!path.endsWith("//"));
        log->debug(tr("Using %1").arg(path));
        QFileInfo info(path);
        if(!info.exists())
         throw FileNotFoundException();
        return (new File(path.replace(FileUtil::SEPARATOR, File::separatorChar)))->getCanonicalPath();
    } catch (IOException ex) {
        log->warn(tr("Cannot convert %1 into a usable filename.").arg(path)+ ex.getMessage());
        return "";
    }
}
/**
 * Find a suitable path to JRMI distributed files, either in a source download or an executable distribution.
 * It is assumed that the required files exist somewhere in the user's home path.
 *
 * This funtion is not part of the JMRI distribution but is required for this port to C++.
 */

/*public*/ QStringList* FileUtilSupport::findProgramPath()
{
 QString home = getHomePath();
 QStringList* paths =  new QStringList();

 QDir start(home);

 scanDir(home, paths, 0);
 return paths;
}
/*private*/ void FileUtilSupport::scanDir(QDir start, QStringList* paths, int depth)
{
 QStringList filters;
 filters << "*.xml";
 depth++;
// qDebug() << "scanDir scanning: " << start.absolutePath() << "depth: " << depth;

 QFileInfoList dirList = start.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot);
 QStringList dirNames = start.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
 foreach(QFileInfo info, dirList)
 {
  QString fn = info.fileName();
  QString pn = info.filePath();
  if(fn == "NetBeansProjects" || fn == "JMRI" || fn == "jmri" || fn == "xml")
//   qDebug() << fn;
  if(fn == "xml")
  {
   qDebug() << "scanDir found directory: " << info.fileName();
   QStringList names = QDir(info.filePath()).entryList(filters,QDir::Files);
   if(names.contains("catalog.xml") && names.contains("names.xml") && names.contains("decoderIndex.xml"))
   {
    paths->append(info.path());
    continue; //not expecting any more since we've just found one!
   }
  }
  if(depth > 3)
   return;
  scanDir(QDir(info.filePath()), paths, depth );
 }
}

/**
 * Read a text URL into a String. Would be significantly simpler with Java
 * 7. File is assumed to be encoded using UTF-8
 *
 * @param url The text URL.
 * @return The contents of the file.
 * @throws java.io.IOException if the URL cannot be read
 */
/*public*/ QString FileUtilSupport::readURL(QUrl url) throw (IOException) {
    try {
        QString builder;
//        try (InputStreamReader in = new InputStreamReader(url.openStream(), StandardCharsets.UTF_8);
//                BufferedReader reader = new BufferedReader(in)) {
//            builder = new StringBuilder();
//            String aux;
//            while ((aux = reader.readLine()) != null) {
//                builder.append(aux);
//            }
//        }
//        return builder.toString();
    QFile* f = new QFile(url.path());
    if(f->open(QIODevice::ReadOnly))
    {
     QTextStream stream(f);
     builder = stream.readAll();
     return builder;
    }
    } catch (NullPointerException ex) {
        return NULL;
    }
}

/**
 * Replaces most non-alphanumeric characters in name with an underscore.
 *
 * @param name The filename to be sanitized.
 * @return The sanitized filename.
 */
/*public*/ QString FileUtilSupport::sanitizeFilename(QString name) {
    name = name.trimmed().replace(" ", "_").replace("[.]+", ".");
    QString filename;// = new StringBuilder();
    //for (QChar c : name.toCharArray())
    for(int i = 0; i < name.length(); i++)
    {
     QChar c = name.at(i);
     if (c == '.' /*|| Character.isJavaIdentifierPart(c)*/ || c.isLetter() || c.isDigit() || c.isLetterOrNumber() || c.isMark() || c == '_')
     {
      filename.append(c);
     }
    }
    return filename/*.toString()*/;
}

/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 * @param path directory to create
 */
/*public*/ void FileUtilSupport::createDirectory(QString path) {
    this->createDirectory(new File(path));
}

/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 * @param dir directory to create
 */
/*public*/ void FileUtilSupport::createDirectory(File* dir) {
    if (!dir->exists()) {
        log->info(tr("Creating directory: %1").arg(dir->getPath()));
        if (!dir->mkdirs()) {
            log->error(tr("Failed to create directory: %1").arg(dir->getPath()));
        }
    }
}

/**
 * Recursively delete a path. It is recommended to use
 * {@link java.nio.file.Files#delete(java.nio.file.Path)} or
 * {@link java.nio.file.Files#deleteIfExists(java.nio.file.Path)} for files.
 *
 * @param path path to delete
 * @return true if path was deleted, false otherwise
 */
//@SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE",
//        justification = "listFiles() is documented to return null only if isDirectory() is false")
/*public*/ bool FileUtilSupport::_delete(File* path)
{
 if (path->isDirectory()) {
     foreach (File* file, path->listFiles()) {
         this->_delete(file);
     }
 }
 return path->_delete();
}

/**
 * Copy a file or directory. It is recommended to use
 * {@link java.nio.file.Files#copy(java.nio.file.Path, java.io.OutputStream)}
 * for files.
 *
 * @param source the file or directory to copy
 * @param dest   must be the file or directory, not the containing directory
 * @throws java.io.IOException if file cannot be copied
 */
/*public*/ void FileUtilSupport::copy(File* source, File* dest) throw (IOException)
{
 if (!source->exists()) {
     log->error(tr("Attempting to copy non-existant file: %1").arg(source->getPath()));
     return;
 }
 if (!dest->exists())
 {
  if (source->isDirectory())
  {
   bool ok = dest->mkdirs();
   if (!ok) {
       throw new IOException("Could not use mkdirs to create destination directory");
   }
  } else {
   bool ok = dest->createNewFile();
   if (!ok) {
       throw new IOException("Could not create destination file");
   }
  }
 }
 if (source->isDirectory())
 {
  foreach (File* file, source->listFiles())
  {
   FileUtil::copy(file, new File(dest, file->getName()));
  }
 }
 else
 {
  Q_ASSERT(!dest->path.endsWith("//"));
  QFile f(dest->path);
  if(f.exists())
   f.remove();
  if(!QFile::copy(source->path, dest->path))
   Logger::error(tr("copy of %1 to %2 failed!").arg(source->path).arg(dest->path) );
 }
}
