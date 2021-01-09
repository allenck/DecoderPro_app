#include "fileutilsupport.h"
#include <QDir>
#include "file.h"
#include "system.h"
#include <QUrl>
#include "matcher.h"
#include <QDebug>
#include "loggerfactory.h"
#include <QProcessEnvironment>
#include "joptionpane.h"
#include <QListWidget>
#include <QLabel>
#include <QBoxLayout>
#include "vptr.h"
#include "profile.h"
#include "profilemanager.h"
#include <QAbstractAnimation>
#include <QCheckBox>

/**
 * Support the {@link jmri.util.FileUtil } static API while providing
 * {@link java.beans.PropertyChangeSupport} for listening to changes in the
 * paths.
 *
 * @author Randall Wood (C) 2015
 */
///*public*/ class FileUtilSupport extends Bean {

Q_GLOBAL_STATIC_WITH_ARGS(const char, _separator, ('/'))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _preferences, ("preference:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _profile, ("profile:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _program, ("program:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _settings, ("settings:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _home, ("home:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _scripts, ("scripts:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _resource, ("resource:"))
Q_GLOBAL_STATIC_WITH_ARGS(const char*, _file, ("file:"))






/* User's home directory */
/*private*/ /*static*/ /*final*/ QString FileUtilSupport::homePath = QDir::homePath() + /*File::separator*/ "/";//System.getProperty("user.home") + File.separator; // NOI18N
// default instance
/*volatile*/ /*private*/ /*static*/ FileUtilSupport* FileUtilSupport::defaultInstance = NULL;

/*public*/ FileUtilSupport::FileUtilSupport() : Bean()
{
 programPath = "";
#if 1 // override program path for development
//programPath = QDir::homePath() + QDir::separator()+"NetBeansProjects"+QDir::separator()+"jmri"+ QDir::separator();
#endif
 jarPath = "";
 scriptsPaths = QHash<Profile*, QString>();
 userFilesPaths = QHash<Profile*, QString>();
 profilePaths = QHash<Profile*, QString>();

 profilePath = "";
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
/*public*/ File* FileUtilSupport::getFile(/*@Nonnull*/ QString path) throw (FileNotFoundException)
{
 return getFile(ProfileManager::getDefault()->getActiveProfile(), path);
}

/**
 * Get the {@link java.io.File} that path refers to. Throws a
 * {@link java.io.FileNotFoundException} if the file cannot be found instead
 * of returning null (as File would). Use {@link #getURI(java.lang.String) }
 * or {@link #getURL(java.lang.String) } instead of this method if possible.
 *
 * @param profile the profile to use as a base
 * @param path    the path to find
 * @return {@link java.io.File} at path
 * @throws java.io.FileNotFoundException if path cannot be found
 * @see #getURI(java.lang.String)
 * @see #getURL(java.lang.String)
 */
//@Nonnull
//@CheckReturnValue
/*public*/ File* FileUtilSupport::getFile(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path) throw (FileNotFoundException)
{
// File* file;
// try
// {
//  QString realPath = pathFromPortablePath(profile, path);
//  QFileInfo info(realPath);
//  if(!info.exists())
//   throw FileNotFoundException(realPath);
//  file = new File(realPath);
//  if(!file->exists())
//   throw FileNotFoundException(tr("File not found: %s").arg(file->getPath()));
// }
// catch (NullPointerException ex)
// {
//  throw  FileNotFoundException("Cannot find file at " + path);
// }
// catch (IOException ex)
// {
//  throw  FileNotFoundException("Cannot find file at " + path);
// }
// return file;
 try {
     return new File(this->pathFromPortablePath(profile, path));
 } catch (NullPointerException ex) {
     throw  FileNotFoundException("Cannot find file at " + path);
 }

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
   throw  FileNotFoundException("Cannot create URL for file at " + path);
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
 return getExternalFilename(ProfileManager::getDefault()->getActiveProfile(), pName);
}

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
* @param profile the Profile to use as a base
* @param pName   the name, possibly starting with file:, home:, profile:,
*                program:, preference:, scripts:, settings, or resource:
* @return Absolute file name to use. This will include system-specific file
*         separators.
* @since 4.17.3
*/
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getExternalFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString pName) {
 QString filename = this->pathFromPortablePath(profile, pName);
 return (filename != "") ? filename : pName.replace(*_separator, File::separatorChar);
}


/**
 * Convert a portable filename into an absolute filename, using
 * {@link jmri.profile.ProfileManager#getActiveProfile()} as the base.
 *
 * @param path the portable filename
 * @return An absolute filename
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getAbsoluteFilename(/*@Nonnull*/ QString path) {
    return this->getAbsoluteFilename(ProfileManager::getDefault()->getActiveProfile(), path);
}

/**
 * Convert a portable filename into an absolute filename.
 *
 * @param profile the profile to use as the base
 * @param path    the portable filename
 * @return An absolute filename
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getAbsoluteFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path) {
    return this->pathFromPortablePath(profile, path);
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
    if (file->isDirectory() && !file->getPath().endsWith(File::separator)) {
        filename = filename + File::separator;
    }

    // compare full path name to see if same as preferences
    QString ufp = getUserFilesPath();
    if (!ignoreUserFilesPath) {
        if (filename.startsWith(getUserFilesPath())) {
            return *_preferences + filename.mid(getUserFilesPath().length(), filename.length()).replace(File::separatorChar, *_separator);
        }
    }

    if (!ignoreProfilePath) {
        // compare full path name to see if same as profile
        if (filename.startsWith(getProfilePath())) {
            return *_profile + filename.mid(getProfilePath().length(), filename.length()).replace(File::separatorChar, *_separator);
        }
    }

    // compare full path name to see if same as settings
    if (filename.startsWith(getPreferencesPath())) {
        return *_settings + filename.mid(getPreferencesPath().length(), filename.length()).replace(File::separatorChar, *_separator);
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
            return *_scripts + filename.mid(getScriptsPath().length(), filename.length()).replace(File::separatorChar, *_separator);
        }
    }

    // now check for relative to program dir
    if (filename.startsWith(getProgramPath())) {
        return *_program + filename.mid(getProgramPath().length(), filename.length()).replace(File::separatorChar, *_separator);
    }

    // compare full path name to see if same as home directory
    // do this last, in case preferences or program dir are in home directory
    if (filename.startsWith(getHomePath())) {
        return *_home + filename.mid(getHomePath().length(), filename.length()).replace(File::separatorChar, *_separator);
    }

    return filename.replace(File::separatorChar, *_separator);   // absolute, and doesn't match; not really portable...
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
/*public*/ QString FileUtilSupport::getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath)
{
 if (this->isPortableFilename(filename))
 {
  // if this already contains prefix, run through conversion to normalize
  return getPortableFilename(getExternalFilename(filename), ignoreUserFilesPath, ignoreProfilePath);
 }
 else
 {
  // treat as pure filename
  return getPortableFilename(new File(filename), ignoreUserFilesPath, ignoreProfilePath);
 }
}

/**
 * Convert a File object's path to our preferred storage form.
 * <p>
 * This is the inverse of {@link #getFile(String pName)}. Deprecated forms
 * are not created.
 *
 * @param profile Profile to use as base
 * @param file    File at path to be represented
 * @return Filename for storage in a portable manner. This will include
 *         portable, not system-specific, file separators.
 * @since 4.17.3
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ File* file) {
    return this->getPortableFilename(profile, file, false, false);
}

/**
 * Convert a File object's path to our preferred storage form.
 * <p>
 * This is the inverse of {@link #getFile(String pName)}. Deprecated forms
 * are not created.
 * <p>
 * This method supports a specific use case concerning profiles and other
 * portable paths that are stored within the User files directory, which
 * will cause the {@link jmri.profile.ProfileManager} to write an incorrect
 * path for the current profile or
 * {@link apps.configurexml.FileLocationPaneXml} to write an incorrect path
 * for the Users file directory. In most cases, the use of
 * {@link #getPortableFilename(java.io.File)} is preferable.
 *
 * @param profile             Profile to use as base
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
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ File* file, bool ignoreUserFilesPath, bool ignoreProfilePath) {
    // compare full path name to see if same as preferences
    QString filename = file->getAbsolutePath();

    // append separator if file is a directory
    if (file->isDirectory()) {
        filename = filename + File::separator;
    }

    if (filename == nullptr) {
        throw IllegalArgumentException("File \"" + file->toString() + "\" has a null absolute path which is not allowed");
    }

    // compare full path name to see if same as preferences
    if (!ignoreUserFilesPath) {
        if (filename.startsWith(getUserFilesPath(profile))) {
            return *_preferences
                    + filename.mid(getUserFilesPath(profile).length(), filename.length()).replace(File::separatorChar,
                            *_separator);
        }
    }

    if (!ignoreProfilePath) {
        // compare full path name to see if same as profile
        if (filename.startsWith(getProfilePath(profile))) {
            return *_profile
                    + filename.mid(getProfilePath(profile).length(), filename.length()).replace(File::separatorChar,
                            *_separator);
        }
    }

    // compare full path name to see if same as settings
    if (filename.startsWith(getPreferencesPath())) {
        return *_settings
                + filename.mid(getPreferencesPath().length(), filename.length()).replace(File::separatorChar,
                        *_separator);
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
        if (filename.startsWith(getScriptsPath(profile)) && filename != (getScriptsPath(profile))) {
            return *_scripts
                    + filename.mid(getScriptsPath(profile).length(), filename.length()).replace(File::separatorChar,
                            *_separator);
        }
    }

    // now check for relative to program dir
    if (filename.startsWith(getProgramPath())) {
        return *_program
                + filename.mid(getProgramPath().length(), filename.length()).replace(File::separatorChar,
                        *_separator);
    }

    // compare full path name to see if same as home directory
    // do this last, in case preferences or program dir are in home directory
    if (filename.startsWith(getHomePath())) {
        return *_home
                + filename.mid(getHomePath().length(), filename.length()).replace(File::separatorChar,
                        *_separator);
    }

    return filename.replace(File::separatorChar, *_separator); // absolute, and doesn't match; not really portable...
}

/**
 * Convert a filename string to our preferred storage form.
 * <p>
 * This is the inverse of {@link #getExternalFilename(String pName)}.
 * Deprecated forms are not created.
 *
 * @param profile  Profile to use as base
 * @param filename Filename to be represented
 * @return Filename for storage in a portable manner
 * @since 4.17.3
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString filename) {
    return getPortableFilename(profile, filename, false, false);
}

/**
 * Convert a filename string to our preferred storage form.
 * <p>
 * This is the inverse of {@link #getExternalFilename(String pName)}.
 * Deprecated forms are not created.
 * <p>
 * This method supports a specific use case concerning profiles and other
 * portable paths that are stored within the User files directory, which
 * will cause the {@link jmri.profile.ProfileManager} to write an incorrect
 * path for the current profile or
 * {@link apps.configurexml.FileLocationPaneXml} to write an incorrect path
 * for the Users file directory. In most cases, the use of
 * {@link #getPortableFilename(java.io.File)} is preferable.
 *
 * @param profile             Profile to use as base
 * @param filename            Filename to be represented
 * @param ignoreUserFilesPath true if paths in the User files path should be
 *                            stored as absolute paths, which is often not
 *                            desirable.
 * @param ignoreProfilePath   true if paths in the profile path should be
 *                            stored as absolute paths, which is often not
 *                            desirable.
 * @return Storage format representation
 * @since 4.17.3
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString filename, bool ignoreUserFilesPath,
        bool ignoreProfilePath) {
    if (isPortableFilename(filename)) {
        // if this already contains prefix, run through conversion to normalize
        return getPortableFilename(profile, getExternalFilename(filename), ignoreUserFilesPath, ignoreProfilePath);
    } else {
        // treat as pure filename
        return getPortableFilename(profile, new File(filename), ignoreUserFilesPath, ignoreProfilePath);
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
    return (filename.startsWith(/**_program*/"program:")
            || filename.startsWith(/**_home*/"home:")
            || filename.startsWith(/**_preferences*/"preference:")
            || filename.startsWith(/**_scripts*/"scripts:")
            || filename.startsWith(/**_profile*/"profile:")
            || filename.startsWith(/**_settings*/"settings:"));
}

/**
 * Get the user's home directory.
 *
 * @return User's home directory as a String
 */
/*public*/ QString FileUtilSupport::getHomePath() {
// homePath = QDir::homePath() + File::separator;
//    return homePath;
 return QDir::homePath() + File::separator;
}

/**
 * Get the user's files directory. If not set by the user, this is the same
 * as the profile path.
 *
 * @see #getProfilePath()
 * @return User's files directory as a String
 */
/*public*/ QString FileUtilSupport::getUserFilesPath() {
 return getUserFilesPath(ProfileManager::getDefault()->getActiveProfile());
}
/**
 * Get the user's files directory. If not set by the user, this is the same
 * as the profile path. Note that if the profile path has been set to null,
 * that returns the preferences directory, see {@link #getProfilePath()}.
 *
 * @param profile the profile to use
 * @see #getProfilePath()
 * @return User's files directory
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getUserFilesPath(/*@CheckForNull*/ Profile* profile) {
    QString path = userFilesPaths.value(profile);
    return path != "" ? path : getProfilePath(profile);
}

/**
 * Set the user's files directory.
 *
 * @see #getUserFilesPath()
 * @param profile the profile to set the user's files directory for
 * @param path    The path to the user's files directory using
 *                system-specific separators
 */
/*public*/ void FileUtilSupport::setUserFilesPath(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path) {
    QString old = userFilesPaths.value(profile);
    if (!path.endsWith(File::separator)) {
        path = path + File::separator;
    }
    userFilesPaths.insert(profile, path);
    if ((old != nullptr && old!=(path)) || (path!=(old))) {
        this->firePropertyChange(*_preferences, VPtr<FileUtil::Property>::asQVariant(new FileUtil::Property(profile, old)), VPtr<FileUtil::Property>::asQVariant(new FileUtil::Property(profile, path)));
    }
}

/**
 * Get the profile directory. If not set, provide the preferences path. Uses
 * the Profile returned by {@link ProfileManager#getActiveProfile()} as a
 * base.
 *
 * @see #getPreferencesPath()
 * @return Profile directory using system-specific separators
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getProfilePath() {
    return getProfilePath(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Get the profile directory. If not set, provide the preferences path.
 *
 * @param profile the Profile to use as a base
 * @see #getPreferencesPath()
 * @return Profile directory using system-specific separators
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getProfilePath(/*@CheckForNull*/ Profile* profile) {
    QString path = profilePaths.value(profile);
    if (path == "") {
        File* f = profile != nullptr ? profile->getPath() : nullptr;
        if (f != nullptr) {
            path = f->getAbsolutePath();
            if (!path.endsWith(File::separator)) {
                path = path + File::separator;
            }
            profilePaths.insert(profile, path);
        }
    }
    return (path != nullptr) ? path : this->getPreferencesPath();
}

/**
 * Set the profile directory.
 *
 * @see #getProfilePath()
 * @param path The path to the profile directory using system-specific separators.
 */
/*public*/ void FileUtilSupport::setProfilePath(QString path)
{
 // does nothing
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
            result = /*this->getHomePath()*/QDir::homePath() + /*File::separator*/ "/" + ".jmri" + /*File::separator*/ "/"; // NOI18N
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
/*public*/ QString FileUtilSupport::getProgramPath()
{
    if (programPath == "")
    {
    //        this->setProgramPath("."); // NOI18N
     QByteArray env0 = qgetenv("JMRIPROJECT");
//     log->debug(tr("env JMRIPROJECT = %1").arg(env0.data()));

     QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
     if(env.contains("JMRIPROJECT"))
     {
      QString path = env.value("JMRIPROJECT");
      QFileInfo info(path);
      if(info.exists())
      {
       if(!path.endsWith(File::separatorChar))
        path = path + File::separator;
       return path;
      }
     }
     paths = findProgramPath();
//     if(paths->size() > 1)
//      return SelectProgramPath(paths);
     if(!paths->isEmpty())
      this->programPath = (paths->at(0) + File::separator);
    }
    return programPath;
}

/*public*/ QString  FileUtilSupport::selectProgramPath(QStringList* stringList)
{
 QWidget* widget = new QWidget();
 widget->setLayout(new QVBoxLayout());
 QLabel* label = new QLabel(tr("Select which JMRI program path you wish to use"));
 widget->layout()->addWidget(label);
 QListWidget* list = new QListWidget();
 foreach (QString str, *stringList) {
  list->addItem(new QListWidgetItem(str));
 }
 widget->layout()->addWidget(list);
 QCheckBox* cb = new QCheckBox(tr("Don't show this again"));
 widget->layout()->addWidget(cb);

 QVariantList buttons = QVariantList() << tr("Ok") << tr("Cancel");
 while (true)
 {
  int retval = JOptionPane::showOptionDialog(nullptr, VPtr<QWidget>::asQVariant(widget),
                                             "Select path",  JOptionPane::OK_CANCEL_OPTION,JOptionPane::QUESTION_MESSAGE, QIcon(), /*buttons*/QVariantList(), QVariant());
  if(retval == JOptionPane::CANCEL_OPTION)
   return "";
  QList<QListWidgetItem*> items = list->selectedItems();
  if(items.count()>0)
  {
   setProgramPath(items.at(0)->text());
   qputenv("JMRIPROJECT", items.at(0)->text().toLocal8Bit());
   return items.at(0)->text();
  }
 }
}

/*public*/ QStringList* FileUtilSupport::getPaths() {return paths;}

/*
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
     log->error("Unable to get JMRI program directory.", ex);
 }
 if ((old != NULL && old != (this->programPath))
         || (this->programPath != NULL && this->programPath !=(old)))
 {
  FileUtil::Property* oldProperty = new FileUtil::Property(ProfileManager::defaultManager()->getActiveProfile(), old);
  FileUtil::Property* newProperty = new FileUtil::Property(ProfileManager::defaultManager()->getActiveProfile(), this->programPath);

     //this->firePropertyChange(*_program, old, this->programPath);
  this->firePropertyChange(*_program, VPtr<FileUtil::Property>::asQVariant(oldProperty), VPtr<FileUtil::Property>::asQVariant(newProperty));
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
    log->info(tr("File path %1 is %2").arg(*_program).arg(this->getProgramPath()));
    log->info(tr("File path %1 is %2").arg(*_preferences).arg(this->getUserFilesPath()));
    log->info(tr("File path %1 is %2").arg(*_profile).arg(this->getProfilePath()));
    log->info(tr("File path %1 is %2").arg(*_settings).arg(this->getPreferencesPath()));
    log->info(tr("File path %1 is %2").arg(*_home).arg(this->getHomePath()));
    log->info(tr("File path %1 is %2").arg(*_scripts).arg(this->getScriptsPath()));
}

/**
 * Get the path to the scripts directory. If not set previously with
 * {@link #setScriptsPath}, this is the "jython" subdirectory in the program
 * directory. Uses the Profile returned by
 * {@link ProfileManager#getActiveProfile()} as the base.
 *
 * @return the scripts directory using system-specific separators
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getScriptsPath() {
    return getScriptsPath(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Get the path to the scripts directory. If not set previously with
 * {@link #setScriptsPath}, this is the "jython" subdirectory in the program
 * directory.
 *
 * @param profile the Profile to use as the base
 * @return the path to scripts directory using system-specific separators
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::getScriptsPath(/*@CheckForNull*/ Profile* profile) {
    QString path = scriptsPaths.value(profile);
    if (path != "") {
        return path;
    }
    // scripts directory not set by user, return default if it exists
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
 * @param profile the profile to use as a base
 * @param path    the scriptsPaths to set; null resets to the default,
 *                defined in {@link #getScriptsPath()}
 */
/*public*/ void FileUtilSupport::setScriptsPath(/*@CheckForNull*/ Profile* profile, /*@CheckForNull */ QString path) {
    QString old = scriptsPaths.value(profile);
    if (path != "" && !path.endsWith(File::separator)) {
        path = path + File::separator;
    }
    scriptsPaths.insert(profile, path);
    if ((old != nullptr && old !=(path)) || (path != "" && path!=(old))) {
        this->firePropertyChange(*_scripts, VPtr<FileUtil::Property>::asQVariant(new FileUtil::Property(profile, old)), VPtr<FileUtil::Property>::asQVariant(new FileUtil::Property(profile, path)));
    }
}

/**
 * Get the URL of a portable filename if it can be located using
 * {@link #findURI(java.lang.String)}
 *
 * @param path the path to find
 * @return URL of portable or absolute path
 */
//@Nonnull
//@CheckReturnValue
/*public*/ QString FileUtilSupport::findExternalFilename(/*@Nonnull*/ QString path)
{
 if(log->isDebugEnabled()) log->debug(tr("Finding external path %1").arg(path));
 if (this->isPortableFilename(path))
 {
  int index = path.indexOf(":") + 1;
  QString location = path.mid(0, index);
  path = path.mid(index);
  if(log->isDebugEnabled()) log->debug(tr("Finding %1 and %2").arg(location).arg(path));
  if(location == *_program)
   return this->findURI(path, FileUtil::Location::INSTALLED);
  if(location ==  *_preferences)
   return this->findURI(path, FileUtil::Location::USER);
  if(location == *_profile ||
      location == *_settings ||
      location == *_scripts ||
      location == *_home)
   return this->findURI(this->getExternalFilename(location + path));
 }
 return this->findURI(path, FileUtil::Location::ALL);
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
        throw IllegalArgumentException();
    }
    QString name = file->getName();
    if (extension != "") {
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
    if (FileUtilSupport::defaultInstance == nullptr) {
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
/*public*/ QString FileUtilSupport::pathFromPortablePath(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path)
{
 QString path_save = path;
 if(path.startsWith("/"))
  return path;
 if(path.startsWith(":/"))
 {
  if(!QFileInfo(path).exists())
  {
   path = path_save.replace(":/", Matcher::quoteReplacement(this->getProgramPath()));
   if(!QFileInfo(path).exists())
    path = path_save;
  }
  return path;

 } else
 if (path.startsWith(*_program))
 {
  if ((new File(path.mid(QString(*_program).length())))->isAbsolute())
  {
   path = path.mid(QString(*_program).length());
  }
  else
  {
   path = path_save.replace(*_program, Matcher::quoteReplacement(this->getProgramPath()));
   if(!QFileInfo(path).exists())
   {
    path = path_save.replace(*_program, ":/");
//    if(path.startsWith(":/jython"))
//     path.replace(":/jython", userFilesPaths+"../jython");
   }
   else
    if(!QFileInfo(path).exists())
    log->info(tr("unable to find %1 specified as %2").arg(path).arg(path_save));
  }
 }
 else if (path.startsWith(*_preferences))
 {
  if ((new File(path.mid(QString(*_preferences).length())))->isAbsolute())
  {
      path = path.mid(QString(*_preferences).length());
  }
  else
  {
      path = path.replace(*_preferences, Matcher::quoteReplacement(this->getUserFilesPath(profile)));
  }
 }
 else if (path.startsWith(*_profile))
 {
  if ((new File(path.mid(QString(*_profile).length())))->isAbsolute()) {
      path = path.mid(QString(*_profile).length());
  } else {
      //path = path.replace(*_profile, Matcher::quoteReplacement(this->getProfilePath()));
  //path = path.replace(*_profile, this->getProfilePath());
      path = getProfilePath(profile) + path.mid(8);
  }
 }
 else if (path.startsWith(*_scripts))
 {
  if ((new File(path.mid(QString(*_scripts).length())))->isAbsolute()) {
      path = path.mid(QString(*_scripts).length());
  } else {
      path = path.replace(*_scripts, Matcher::quoteReplacement(this->getScriptsPath(profile)));
  }
 }
 else if (path.startsWith(*_settings))
 {
  if ((new File(path.mid(QString(*_settings).length())))->isAbsolute()) {
      path = path.mid(QString(*_settings).length());
  } else {
      path = path.replace(*_settings, Matcher::quoteReplacement(this->getPreferencesPath()));
  }
 }
 else if (path.startsWith(*_home))
 {
  if ((new File(path.mid(QString(*_home).length())))->isAbsolute()) {
      path = path.mid(QString(*_home).length());
  } else {
      path = path.replace(*_home, Matcher::quoteReplacement(this->getHomePath()));
  }
 }
 else if (!(new File(path))->isAbsolute()) {
     path = FileUtil::getProgramPath() + path;
 }
 try {
     // if path cannot be converted into a canonical path, return null
  Q_ASSERT(path != "/");
  Q_ASSERT(!path.endsWith("//"));
     //log->debug(tr("Using %1").arg(path));
     QFileInfo info(path);
     if(!info.exists())
     {
      //throw FileNotFoundException(path);
      QString msg = tr("can't convert '%1' to '%2'").arg(path_save).arg(path);
      //log->error(msg);
      //throw NullPointerException(msg);  // throw IOException??
      throw IOException(msg);
     }
     return (new File(path.replace(*_separator, File::separatorChar)))->getCanonicalPath();
 } catch (IOException ex) {
     //log->warn(tr("Cannot convert %1 into a usable filename.").arg(path)+ ex.getMessage());
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

 QFileInfoList dirList = start.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot );
 QStringList dirNames = start.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
 foreach(QFileInfo info, dirList)
 {
  QString fn = info.fileName();
  QString pn = info.filePath();

  QStringList subDirs = QDir(info.filePath()).entryList(QDir::Dirs);

  if( fn == "JMRI" || /*fn == "jmri" ||*/ fn == "xml")
  {
//   qDebug() << fn;
   if(fn == "xml" && dirNames.contains(QString("web")) && dirNames.contains(QString("resources")))
   {
    qDebug() << "scanDir found directory: " << info.path();
    QStringList names = QDir(info.filePath()).entryList(filters,QDir::Files);
    if(names.contains("catalog.xml") && names.contains("names.xml") && names.contains("decoderIndex.xml") && !(info.filePath().contains(".jmri")))
    {
     paths->append(info.path());
     names = QDir(info.absolutePath() + File::separator + "web").entryList(filters,QDir::AllDirs);
     if(names.contains("xml") && names.contains("prefs") && names.contains("dist"))
      continue;
     if(!names.contains("xml"))
     {
     // create link to xml dir so that web server can find files there
     QFile linkDir(info.absolutePath() + File::separator + "xml" );
      if(!linkDir.link(info.absolutePath() + File::separator + "web" + File::separator + "xml" ))
       log->error(tr("error creating link to %1 error:%2").arg( linkDir.fileName()).arg(linkDir.error()));
     }
     if(!names.contains("prefs"))
     {
      // create link to xml dir so that web server can find files there
      QFile linkDir(FileUtil::getPreferencesPath());
      if(!linkDir.link(info.absolutePath() + File::separator + "web" + File::separator + "prefs" ))
       log->error(tr("error creating link to %1 error:%2").arg( linkDir.fileName()).arg(linkDir.error()));
     }
     if(!names.contains("dist"))
     {
     // create link to xml dir so that web server can find files there
      QFile linkDir(info.absolutePath() );
      if(!linkDir.link(info.absolutePath() + File::separator + "web" + File::separator + "dist" ))
       log->error(tr("error creating link to %1 error:%2").arg( linkDir.fileName()).arg(linkDir.error()));
     }
     continue; //not expecting any more since we've just found one!
    }
   }
  }
  if(depth > 3)
   return;
  scanDir(QDir(info.filePath()), paths, depth );
 }
}

/*public*/ QString FileUtilSupport::locateFile(QDir start, QString fileName)
{
 QFileInfoList dirList = start.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);
 foreach(QFileInfo info, dirList)
 {
  QString fn = info.fileName();
  QString pn = info.filePath();
  if(fn == fileName && info.isFile())
   return info.absoluteFilePath();
  if(info.isDir())
  {
   QString path = locateFile(QDir(info.absoluteFilePath()),fileName);
   if(path != "")
    return path;
  }
 }
 return "";
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
    if(url.path() == "")
     throw NullPointerException("invalid URL");
    QFile* f = new QFile(url.path());
    if(f->open(QIODevice::ReadOnly))
    {
     QTextStream stream(f);
     builder = stream.readAll();
     return builder;
    }
 }
 catch (NullPointerException ex) {
        return "";
 }
 return "";
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
/*public*/ void FileUtilSupport::createDirectory(File* dir)
{
 if (!dir->exists())
 {
  log->info(tr("Creating directory: %1").arg(dir->getPath()));
  if (!dir->mkdirs())
  {
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
   if (!ok)
   {
    log->error(tr("Could not use mkdirs to create destination directory").arg(dest->getParent()));
    throw  IOException("Could not use mkdirs to create destination directory");
   }
  } else {
   bool ok = dest->createNewFile();
   if (!ok)
   {
    log->error(tr("Could not create destination file %1 ").arg(dest->getPath()));
    throw IOException(tr("Could not create destination file %1 ").arg(dest->getPath()));
   }
  }
 }
 QString srcPath = source->getPath();
 QString dstPath = dest->getPath();
 QFile f(dstPath);
 if(f.exists())
  f.remove();
 if(! copyRecursively(srcPath, dstPath))
 {
  throw IOException(tr("error copying %1 to %2").arg(srcPath).arg(dstPath));
 }
}

/*private*/ bool FileUtilSupport::copyRecursively(const QString &srcFilePath,
                                 const QString &tgtFilePath)
{
    QFileInfo srcFileInfo(srcFilePath);
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!QFileInfo(tgtFilePath).exists() && !targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            return false;
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
            if (!copyRecursively(newSrcFilePath, newTgtFilePath))
                return false;
        }
    } else
    {
     QFile f(tgtFilePath);
     if(f.exists())
      f.remove();
     if (!QFile::copy(srcFilePath, tgtFilePath))
      return false;
    }
    return true;
}
/**
 * Simple helper method to just append a text string to the end of the given
 * filename. The file will be created if it does not exist.
 *
 * @param file File to append text to
 * @param text Text to append
 * @throws java.io.IOException if file cannot be written to
 */
/*public*/ void FileUtilSupport::appendTextToFile(File* file, QString text) throw (IOException)
{
//    try (PrintWriter pw = new PrintWriter(new OutputStreamWriter(new FileOutputStream(file, true), StandardCharsets.UTF_8))) {
//        pw.println(text);
//    }
 QFile f(file->getPath());
 QString otext;
 if(f.open(QIODevice::ReadOnly|QIODevice::Append))
 {
  QTextStream is(&f);
  otext = is.readAll();
 }
 f.close();
 if(f.open(QIODevice::WriteOnly))
 {
  QTextStream os(&f);
  os << otext << text;
  f.close();
 }
 else
    throw IOException();
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.io.InputStream} for that file. Search order is defined by
 * {@link #findURL(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...) }.
 *
 * @param path      The relative path of the file or resource
 * @param locations The type of locations to limit the search to
 * @return InputStream or null.
 * @see #findInputStream(java.lang.String)
 * @see #findInputStream(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ QTextStream* FileUtilSupport::findInputStream(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations) {
    return this->findInputStream(path, locations, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.io.InputStream} for that file. Search order is defined by
 * {@link #findURL(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...) }.
 *
 * @param path        The relative path of the file or resource
 * @param locations   The type of locations to limit the search to
 * @param searchPaths a list of paths to search for the path in
 * @return InputStream or null.
 * @see #findInputStream(java.lang.String)
 * @see #findInputStream(java.lang.String, java.lang.String...)
 */
/*public*/ QTextStream* FileUtilSupport::findInputStream(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths) {
    QUrl file = this->findURL(path, locations, searchPaths);
    if (file.path() != nullptr) {
        try {
            //return file->openStream();
      QFile f(path);
      if(!f.open(QIODevice::ReadOnly)) throw IOException(f.fileName());
      return new QTextStream(&f);
        } catch (IOException ex) {
            log->error(ex.getLocalizedMessage(), ex);
        }
    }
    return nullptr;
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URI} for that file. Search order is defined by
 * {@link #findURI(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 * No limits are placed on search locations.
 *
 * @param path The relative path of the file or resource.
 * @return The URI or null.
 * @see #findURI(java.lang.String, java.lang.String...)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ QString FileUtilSupport::findURI(/*@Nonnull*/ QString path) {
    return this->findURI(path, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URI} for that file. Search order is defined by
 * {@link #findURI(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 * No limits are placed on search locations.
 * <p>
 * Note that if the file for path is not found in one of the searchPaths,
 * all standard locations are also be searched through to find the file. If
 * you need to limit the locations where the file can be found use
 * {@link #findURI(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 *
 * @param path        The relative path of the file or resource
 * @param searchPaths a list of paths to search for the path in
 * @return The URI or null
 * @see #findURI(java.lang.String)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ QString FileUtilSupport::findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ QStringList searchPaths) {
    return this->findURI(path, FileUtil::Location::ALL, searchPaths);
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URI} for that file. Search order is defined by
 * {@link #findURI(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 *
 * @param path      The relative path of the file or resource
 * @param locations The types of locations to limit the search to
 * @return The URI or null
 * @see #findURI(java.lang.String)
 * @see #findURI(java.lang.String, java.lang.String...)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ QString FileUtilSupport::findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations) {
    return this->findURI(path, locations, QStringList());
}

/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URI} for that file.
 * <p>
 * Search order is:
 * <ol>
 * <li>For any provided searchPaths, iterate over the searchPaths by
 * prepending each searchPath to the path and following the following search
 * order:<ol>
 * <li>As a {@link java.io.File} in the user preferences directory</li>
 * <li>As a File in the current working directory (usually, but not always
 * the JMRI distribution directory)</li>
 * <li>As a File in the JMRI distribution directory</li>
 * <li>As a resource in jmri.jar</li>
 * </ol></li>
 * <li>If the file or resource has not been found in the searchPaths, search
 * in the four locations listed without prepending any path</li>
 * <li>As a File with an absolute path</li>
 * </ol>
 * <p>
 * The <code>locations</code> parameter limits the above logic by limiting
 * the location searched.
 * <ol>
 * <li>{@link Location#ALL} will not place any limits on the search</li>
 * <li>{@link Location#NONE} effectively requires that <code>path</code> be
 * a portable pathname</li>
 * <li>{@link Location#INSTALLED} limits the search to the
 * {@link FileUtil#PROGRAM} directory and JARs in the class path</li>
 * <li>{@link Location#USER} limits the search to the
 * {@link FileUtil#PREFERENCES}, {@link FileUtil#PROFILE}, and
 * {@link FileUtil#SETTINGS} directories (in that order)</li>
 * </ol>
 *
 * @param path        The relative path of the file or resource
 * @param locations   The types of locations to limit the search to
 * @param searchPaths a list of paths to search for the path in
 * @return The URI or null
 * @see #findURI(java.lang.String)
 * @see #findURI(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURI(java.lang.String, java.lang.String...)
 */
/*public*/ QString FileUtilSupport::findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths) {
//    if (log->isDebugEnabled()) { // avoid the Arrays.toString call unless debugging
//        log->debug(tr("Attempting to find %1 in %2").arg(path).arg( Arrays.toString(searchPaths));
//    }
    QFileInfo info(path);
    if(info.exists())
        return info.absoluteFilePath();
    if (this->isPortableFilename(path)) {
        try {
            return this->findExternalFilename(path);
        } catch (NullPointerException ex) {
            // do nothing
        }
    }
    QString resource = "";
    if(searchPaths.isEmpty())
        searchPaths.append(getProgramPath());
    for (QString searchPath : searchPaths)
    {
        QFileInfo info(/*getProgramPath() +*/ searchPath + File::separator + path);
        if(info.exists())
        {
            resource = this->findURI( /*getProgramPath() +*/ searchPath + File::separator + path);
            if (resource != "") {
                return resource;
            }
        }
    }
    File* file;
    if (locations == FileUtil::Location::ALL || locations == FileUtil::Location::USER) {
        // attempt to return path from preferences directory
        if(path.startsWith(":/"))
         return path;
        file = new File(this->getUserFilesPath(), path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
        // attempt to return path from profile directory
        file = new File(this->getProfilePath(), path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
        // attempt to return path from preferences directory
        file = new File(this->getPreferencesPath(), path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
        // attempt to return path from resources directory
        file = new File(":/", path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
    }
    if (locations == FileUtil::Location::ALL || locations == FileUtil::Location::INSTALLED) {
        // attempt to return path from current working directory
        // attempt to return path from JMRI distribution directory
        file = new File(this->getProgramPath() + path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
        file = new File(path);
        if (file->exists()) {
            //return file.toURI();
         return file->getPath();
        }

    }
#if 0
    if (locations == FileUtil::Location::ALL || locations == FileUtil::Location::INSTALLED) {
        // return path if in jmri.jar or null
        // The ClassLoader needs paths to use /
        path = path.replace(File::separatorChar, '/');
        QUrl url = FileUtilSupport::class.getClassLoader().getResource(path);
        if (url == null) {
            url = FileUtilSupport.class.getResource(path);
            if (url == null) {
                log->debug("{} not found in classpath", path);
            }
        }
        try {
            resource = (url != null) ? url.toURI() : null;
        } catch (URISyntaxException ex) {
            log->warn("Unable to get URI for {}", path, ex);
        }
    }
#endif
    // if a resource has not been found and path is absolute and exists
    // return it
    if (resource == "") {
        file = new File(path);
        if (file->isAbsolute() && file->exists()) {
            //return file.toURI();
         return file->getPath();
        }
    }
    return resource;
}
#if 0
/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file. Search order is defined by
 * {@link #findURL(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 * No limits are placed on search locations.
 *
 * @param path The relative path of the file or resource.
 * @return The URL or null.
 * @see #findURL(java.lang.String, java.lang.String...)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ URL findURL(/*@Nonnull*/ String path) {
    return this->findURL(path, new String[]{});
}
#endif
/**
 * Search for a file or JAR resource by name and return the
 * {@link java.net.URL} for that file. Search order is defined by
 * {@link #findURL(java.lang.String, jmri.util.FileUtil.Location, java.lang.String...)}.
 * No limits are placed on search locations.
 *
 * @param path        The relative path of the file or resource
 * @param searchPaths a list of paths to search for the path in
 * @return The URL or null
 * @see #findURL(java.lang.String)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location,
 * java.lang.String...)
 */
/*public*/ QUrl FileUtilSupport::findURL(/*@Nonnull*/ QString path, /*@Nonnull*/ QStringList searchPaths) {
    return this->findURL(path, FileUtil::Location::ALL, searchPaths);
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
/*public*/ QUrl FileUtilSupport::findURL(/*@Nonnull*/ QString path, FileUtil::Location locations) {
    return this->findURL(path, locations, QStringList());
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
 * {@link FileUtil#PROGRAM} directory and JARs in the class
 * path</li><li>{@link Location#USER} limits the search to the
 * {@link FileUtil#PROFILE} directory</li></ol>
 *
 * @param path        The relative path of the file or resource
 * @param locations   The types of locations to limit the search to
 * @param searchPaths a list of paths to search for the path in
 * @return The URL or null
 * @see #findURL(java.lang.String)
 * @see #findURL(java.lang.String, jmri.util.FileUtil.Location)
 * @see #findURL(java.lang.String, java.lang.String...)
 */
/*public*/ QUrl FileUtilSupport::findURL(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths) {
    QString file = this->findURI(path, locations, searchPaths);
    if (file != "") {
        try {
            //return file.toURL();
         return QUrl(file);
        } catch (MalformedURLException ex) {
            log->error(ex.getLocalizedMessage(), ex);
        }
    }
    return QUrl();
}

/**
 * Return the {@link java.net.URI} for a given URL
 *
 * @param url the URL
 * @return a URI or null if the conversion would have caused a
 *         {@link java.net.URISyntaxException}
 */
/*public*/ QString FileUtilSupport::urlToURI(/*@Nonnull*/ QUrl url) {
//    try {
//        return url.toURI();
//    } catch (URISyntaxException ex) {
//        log->error("Unable to get URI from URL", ex);
//        return null;
//    }
 return url.toLocalFile();
}

// initialize logging


/*private*/ /*static*/ /*final*/ Logger* FileUtilSupport::log = LoggerFactory::getLogger("FileUtilSupport");
