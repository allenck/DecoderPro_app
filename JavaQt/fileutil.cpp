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
/*static*/ /*public*/ File* FileUtil::getFile(QString path) /*throws FileNotFoundException */
{
//        try {
 return new File(FileUtil::pathFromPortablePath(path));
//        } catch (NullPointerException ex) {
//            throw new FileNotFoundException("Cannot find file at " + path);
//        }
}
/*
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
 * profile:, program:, preference:, scripts:, settings, or resource:
 * @return Canonical path to use, or null if one cannot be found.
 * @since 2.7.2
 */
/*static*/ /*private*/ QString FileUtil::pathFromPortablePath(/*@NonNull*/ QString path)
{
 //Q_ASSERT(path != "");
    if(path == "") return "";
    Logger log("FileUtil");
 if (path.startsWith(PROGRAM))
 {
  if ( File(path.mid(PROGRAM.length())).isAbsolute())
  {
   path = path.mid(PROGRAM.length());

  }
  else
  {
   path = path.replace(PROGRAM, Matcher::quoteReplacement(FileUtil::getProgramPath()));
  }
 }
 else if (path.startsWith(PREFERENCES))
 {
  if ( File(path.mid(PREFERENCES.length())).isAbsolute())
  {
   path = path.mid(PREFERENCES.length());
  }
  else
  {
   path = path.replace(PREFERENCES, Matcher::quoteReplacement(FileUtil::getUserFilesPath()));
  }
 }
 else if (path.startsWith(PROFILE))
 {
  if ( File(path.mid(PROFILE.length())).isAbsolute())
  {
   path = path.mid(PROFILE.length());
  }
  else
  {
   path = path.replace(PROFILE, Matcher::quoteReplacement(FileUtil::getProfilePath()));
  }
 }
 else if (path.startsWith(SCRIPTS))
 {
  if ( File(path.mid(SCRIPTS.length())).isAbsolute())
  {
   path = path.mid(SCRIPTS.length());
  }
  else
  {
   path = path.replace(SCRIPTS, Matcher::quoteReplacement(FileUtil::getScriptsPath()));
  }
 }
 else if (path.startsWith(SETTINGS))
 {
  if ( File(path.mid(SETTINGS.length())).isAbsolute())
  {
   path = path.mid(SETTINGS.length());
  }
  else
  {
   path = path.replace(SETTINGS, Matcher::quoteReplacement(FileUtil::getPreferencesPath()));
  }
 }
 else if (path.startsWith(HOME))
 {
  if ( File(path.mid(HOME.length())).isAbsolute())
  {
   path = path.mid(HOME.length());
  }
  else
  {
      path = path.replace(HOME, Matcher::quoteReplacement(FileUtil::getHomePath()));
  }
 }
 else if (path.startsWith(RESOURCE))
 {
  if ( File(path.mid(RESOURCE.length())).isAbsolute())
  {
   path = path.mid(RESOURCE.length());
  }
  else
  {
   path = path.replace(RESOURCE, Matcher::quoteReplacement(FileUtil::getProgramPath()));
  }
 }
 else if (path.startsWith(FILE))
 {
  if ( File(path.mid(FILE.length())).isAbsolute())
  {
   path = path.mid(FILE.length());
  }
  else
  {
   path = path.replace(FILE, Matcher::quoteReplacement(FileUtil::getUserFilesPath()));
  }
 }
 else if(path.startsWith("resources"))
  return FileUtil::getProgramPath() + path;
 else if (! File(path).isAbsolute())
 {
 return "";
 }
//    try {
        // if path cannot be converted into a canonical path, return null
 log.debug(QString("Using %1").arg( path));
 return File(path.replace(QString(SEPARATOR), File::separatorChar)).getCanonicalPath();
//    } catch (IOException ex) {
//        log.warn("Cannot convert {} into a usable filename.", path, ex);
//        return NULL;
//    }
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
 Logger log("FileUtil");
 if (pName == NULL || pName.length() == 0)
 {
  return NULL;
 }
 if (pName.startsWith(RESOURCE))
 {
  // convert to relative filename
  QString temp = pName.mid(RESOURCE.length());
  if ((QFileInfo(temp)).isAbsolute())
  {
   return temp.replace(SEPARATOR, QDir::separator());
  }
  else
  {
   return getProgramPath() + temp.replace(SEPARATOR, QDir::separator());
  }
 }
 else if (pName.startsWith(PROGRAM))
 {
  // both relative and absolute are just returned
  QString currPath = QDir::currentPath();
  programPath = currPath+QDir::separator()+ ".." +QDir::separator()+"jmri"+ QDir::separator();
  QString path = programPath + pName.mid(PROGRAM.length()).replace(SEPARATOR, QDir::separator());
  return path;
 }
 else if (pName.startsWith(PREFERENCES))
 {
  QString filename = pName.mid(PREFERENCES.length());

  // Check for absolute path name
  if (QFileInfo(filename).isAbsolute())
  {
   Logger log;
   if (_debug)
   {
    log.debug("Load from absolute path: " + filename);
   }
   return filename.replace(SEPARATOR, QDir::separator());
  }
  // assume this is a relative path from the
  // preferences directory
  filename = FileUtil::getUserFilesPath() + filename;
  if (_debug)
  {
   log.debug("load from user preferences file: " + filename);
  }
  return filename.replace(SEPARATOR, QDir::separator());
 }
 else if (pName.startsWith(FILE))
 {
  QString filename = pName.mid(FILE.length());

  // historically, absolute path names could be stored
  // in the 'file' format.  Check for those, and
  // accept them if present
  if ((QFileInfo(filename)).isAbsolute())
  {
   if (_debug)
   {
    log.debug("Load from absolute path: " + filename);
   }
   return filename.replace(SEPARATOR, QDir::separator());
  }
  // assume this is a relative path from the
  // preferences directory
  filename = FileUtil::getUserFilesPath() + "resources" + QDir::separator() + filename; // NOI18N
//  if (log.isDebugEnabled())
//  {
//   log.debug("load from user preferences file: " + filename);
//  }
  return filename.replace(SEPARATOR, QDir::separator());
 }
 else if (pName.startsWith(HOME))
 {
  QString filename = pName.mid(HOME.length());

  // Check for absolute path name
  if ((QFileInfo(filename)).isAbsolute())
  {
   if (_debug)
   {
    log.debug("Load from absolute path: " + filename);
   }
   return filename.replace(SEPARATOR, QDir::separator());
  }
  // assume this is a relative path from the
  // user.home directory
  QString saveFN = filename;
  filename = FileUtil::getHomePath() + filename;
  if (_debug)
  {
   log.debug("load from user preferences file: " + filename);
  }
  QFileInfo info(filename);
  if(!info.exists())
      filename = FileUtil::getProgramPath() + saveFN.mid(saveFN.indexOf("resources"));
  return filename.replace(SEPARATOR, QDir::separator());
 }
 else
 {
  // must just be a (hopefully) valid name
  QString temp1 =  pName.replace(SEPARATOR, QDir::separator());
  if(QFile(temp1).exists())
  {
   return temp1;
  }
  File temp2 =  File(HOME + QString(SEPARATOR)+ temp1);
  if(temp2.exists())
   return temp2.getPath();
 }
 return pName;
}

/**
 * Convert a portable filename into an absolute filename
 *
 * @param path
 * @return An absolute filename
 */
/*static*/ /*public*/ QString FileUtil::getAbsoluteFilename(QString path)
{
 Logger log("FileUtil");
 if (path == NULL || path.length() == 0)
 {
  return "";
 }
 if (path.startsWith(PROGRAM))
 {
  if (QFileInfo(path.mid(PROGRAM.length())).isAbsolute())
  {
   path = path.mid(PROGRAM.length());
  }
  else
  {
   path = path.replace(PROGRAM, /*Matcher::quoteReplacement*/(FileUtil::getProgramPath()));
  }
  return path;
 }
 else if (path.startsWith(PREFERENCES))
 {
  if (QFileInfo(path.mid(PREFERENCES.length())).isAbsolute())
  {
   path = path.mid(PREFERENCES.length());
  }
  else
  {
   path = path.replace(PREFERENCES, /*Matcher::quoteReplacement*/(FileUtil::getUserFilesPath()));
  }
  return path;
 }
 else if (path.startsWith(HOME))
 {
  if (QFileInfo(path.mid(HOME.length())).isAbsolute())
  {
   path = path.mid(HOME.length());
  }
  else
  {
   path = path.replace(HOME, /*Matcher::quoteReplacement*/(FileUtil::getHomePath()));
  }
  return path;
 }
 else if(path.startsWith("resources"))
 {
  return FileUtil::getProgramPath() + path;
 }
 else if (path.startsWith(RESOURCE) || path.startsWith(FILE))
 {
  return getAbsoluteFilename(getPortableFilename(getExternalFilename(path)));
 }
 else if (! QFileInfo(path).isAbsolute())
 {
  return NULL;
 }
 try
 {
  // if path cannot be converted into a canonical path, return NULL
  if (_debug)
  {
   log.debug("Using " + path);
  }
  QString fn =  File(path.replace(SEPARATOR, QDir::separator())).getPath();
  return fn;
 }
 catch (IOException ex)
 {
  log.warn(tr("Can not convert ") + path + tr(" into a usable filename.")+ ex.getMessage());
  return NULL;
 }
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
 // compare full path name to see if same as preferences
 QString filename = file->getAbsolutePath();

 // append separator if file is a directory
 if (file->isDirectory())
 {
  filename = filename + File::separator;
 }

 // compare full path name to see if same as preferences
 if (!ignoreUserFilesPath)
 {
  if (filename.startsWith(getUserFilesPath()))
  {
   return PREFERENCES + filename.mid(getUserFilesPath().length(), filename.length()).replace(File::separatorChar, QString(SEPARATOR));
  }
 }

 if (!ignoreProfilePath)
 {
  // compare full path name to see if same as profile
  if (filename.startsWith(getProfilePath()))
  {
   return PROFILE + filename.mid(getProfilePath().length(), filename.length()).replace(File::separatorChar, QString(SEPARATOR));
  }
 }

 // compare full path name to see if same as settings
 if (filename.startsWith(getPreferencesPath()))
 {
  return SETTINGS + filename.mid(getPreferencesPath().length(), filename.length()).replace(File::separatorChar, QString(SEPARATOR));
 }

 if (!ignoreUserFilesPath)
 {
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
  if (filename.startsWith(getScriptsPath()) && filename!=(getScriptsPath()))
  {
   return SCRIPTS + filename.mid(getScriptsPath().length(),   filename.length()).replace(File::separatorChar, QString(SEPARATOR));
  }
 }

 // now check for relative to program dir
 if (filename.startsWith(getProgramPath()))
 {
  return PROGRAM + filename.mid(getProgramPath().length(), filename.length()).replace(File::separatorChar, QString(SEPARATOR));
 }

 // compare full path name to see if same as home directory
 // do this last, in case preferences or program dir are in home directory
 if (filename.startsWith(getHomePath()))
 {
  QString temp =  HOME + filename.mid(getHomePath().length(), filename.length());
  return temp; //.replace(File::separatorChar.at(0), QString(SEPARATOR));
 }

 return filename.replace(File::separatorChar, QString(SEPARATOR));   // absolute, and doesn't match; not really portable...
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
    if (FileUtil::isPortableFilename(filename)) {
        // if this already contains prefix, run through conversion to normalize
        return getPortableFilename(getExternalFilename(filename), ignoreUserFilesPath, ignoreProfilePath);
    } else {
        // treat as pure filename
        return getPortableFilename( new File(filename), ignoreUserFilesPath, ignoreProfilePath);
    }
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
 //QString path = (FileUtil::userFilesPath != "") ? FileUtil::userFilesPath : FileUtil::getPreferencesPath();
 QString path = QDir::homePath() + QDir::separator()+".jmri"+ QDir::separator();
 QFileInfo  info(path);
 if(!info.exists())
 {
  QDir* dir= new QDir();
  dir->mkpath(path);
 }
 return path;
}

/**
 * Set the user's files directory.
 *
 * @see #getUserFilesPath()
 * @param path The path to the user's files directory
 */
/*static*/ /*public*/ void FileUtil::setUserFilesPath(QString path)
{
 if (!path.endsWith(QDir::separator()))
 {
  path = path + QDir::separator();
 }
 FileUtil::userFilesPath = path;
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
 return (FileUtil::profilePath != "") ? FileUtil::profilePath : FileUtil::getPreferencesPath();
}
/**
 * Set the profile directory.
 *
 * @see #getProfilePath()
 * @param path The path to the profile directory
 */
/*static*/ /*public*/ void FileUtil::setProfilePath(QString path) {
    if (path != "" && !path.endsWith(File::separator)) {
        path = path + File::separator;
    }
    FileUtil::profilePath = path;
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
    // return jmri.prefsdir property if present
    QString jmriPrefsDir = System::getProperty("jmri.prefsdir", ""); // NOI18N
    if (!jmriPrefsDir.isEmpty()) {
        return jmriPrefsDir + QDir::separator();
    }
    QString result;
//    switch (SystemType.getType()) {
//        case SystemType.MACOSX:
            // Mac OS X
#ifdef Q_OS_MAC

            result = FileUtil.getHomePath() + "Library" + QDir::separator() + "Preferences" + File.separator + "JMRI" + File.separator; // NOI18N
#endif
#if 0
            break;
        case SystemType.LINUX:
        case SystemType.UNIX:
#endif
#ifdef Q_OS_LINUX || Q_OS_UNIX

            // Linux, so use an invisible file
            result = FileUtil::getHomePath() + ".jmri" + QDir::separator(); // NOI18N
#endif
#if 0
            break;
        case SystemType.WINDOWS:
        default:
#endif
#ifdef  Q_OS_WIN
            // Could be Windows, other
            result = FileUtil::getHomePath() + "JMRI" + QDir::separator(); // NOI18N
#endif
#if 0
            break;
    }
    if (log.isDebugEnabled()) {
        log.debug("preferencesPath defined as \"" + result + "\" based on os.name=\"" + SystemType.getOSName() + "\"");
    }
#endif
    return result;
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
 FileUtil::setProgramPath(QDir(path));
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
/*static*/ /*public*/ void FileUtil::setProgramPath(QDir path)
{
 try
 {
  programPath = (path).canonicalPath() + QDir::separator();
 }
 catch (IOException ex)
 {
  Logger::error("Unable to get JMRI program directory.", ex.getMessage());
 }
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
    scriptsPath = path;
}

/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 * @param path
 */
/*public*/ /*static*/ void FileUtil::createDirectory(QString path)
{
 QDir* dir = new QDir(path);
 if (!dir->exists())
 {
  //log.warn("Creating directory: " + path);
  if (!dir->mkpath(path))
  {
   Logger::error("Failed to create directory: " + path);
  }
 }
}
/**
 * Create a directory if required. Any parent directories will also be
 * created.
 *
 */
/*public*/ /*static*/ void FileUtil::createDirectory(File* dir)
{
     Logger log("FileUtil");
    if (!dir->exists()) {
        log.info(tr("Creating directory: %1").arg(dir->toString()));
        if (!dir->mkdirs()) {
            log.error(tr("Failed to create directory: %1").arg(dir->toString()));
        }
    }
}
/**
 * Replaces most non-alphanumeric characters in name with an underscore.
 *
 * @param name The filename to be sanitized.
 * @return The sanitized filename.
 */
/*public*/ /*static*/ QString FileUtil::sanitizeFilename(QString name) {
    name = name.trimmed().replace(" ", "_").replace("[.]+", ".");
//    QString filename = new QString();
//    for (char c : name.toCharArray()) {
//        if (c == '.' || Character.isJavaIdentifierPart(c)) {
//            filename.append(c);
//        }
//    }
//    return filename.toString();
    return name;
}

/**
 * Recursively delete a path. Not needed in Java 1.7.
 *
 * @param path
 * @return true if path was deleted, false otherwise
 */
/*public*/ /*static*/ bool FileUtil::_delete(File* path)
{
 if (path->isDirectory())
 {
   foreach (File* file, path->listFiles()) {
            FileUtil::_delete(file);
        }
    }
    return path->_delete();
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
 if (!source->exists())
 {
  Logger::error(tr("Attempting to copy non-existant file: %1").arg(source->getPath()));
  return;
 }
 if (!dest->exists())
 {
  if (source->isDirectory())
  {
   bool ok = dest->mkdirs();
   if (!ok)
   {
    Logger::error("Could not use mkdirs to create destination directory");
    throw new IOException("Could not use mkdirs to create destination directory");
   }
  }
  else
  {
   bool ok = dest->createNewFile();
   if (!ok)
   {
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
//  FileInputStream sourceIS = null;
//  FileChannel sourceChannel = null;
//  FileOutputStream destIS = null;
//  FileChannel destChannel = null;
//  try
//  {
//   sourceIS = new FileInputStream(source);
//   sourceChannel = sourceIS.getChannel();
//   destIS = new FileOutputStream(dest);
//   destChannel = destIS.getChannel();
//   if (destChannel != null && sourceChannel != null)
//   {
//    destChannel.transferFrom(sourceChannel, 0, sourceChannel.size());
//   }
//  }
//  catch (IOException ex)
//  {
//   throw ex;
//  }
//  finally
//  {
//   try
//   {
//    if (sourceChannel != null)
//    {
//     sourceChannel.close();
//    }
//    if (destChannel != null)
//    {
//     destChannel.close();
//    }
//    if (sourceIS != null)
//    {
//     sourceIS.close();
//    }
//    if (destIS != null)
//    {
//     destIS.close();
//    }
//   }
//   catch (IOException ex)
//   {
//    throw ex;
//   }
//  }
  if(!QFile::copy(source->path, dest->path))
   Logger::error(tr("copy of %1 to %2 failed!").arg(source->path).arg(dest->path) );
 }
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
