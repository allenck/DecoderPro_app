#ifndef FILEUTILSUPPORT_H
#define FILEUTILSUPPORT_H

#include "bean.h"
#include "exceptions.h"
#include <QDir>
#include "fileutil.h"

class Profile;
class Logger;
class File;
class FileUtilSupport : public Bean
{
public:
 FileUtilSupport();
 /*public*/ File* getFile(QString path) throw (FileNotFoundException);
 /*public*/ File* getFile(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path) throw (FileNotFoundException);
 /*public*/ QUrl* getURL(QString path) throw (FileNotFoundException);
 /*public*/ QSet<File*> findFiles(/*@Nonnull*/ QString name, /*@Nonnull*/ QString root)/* throws IllegalArgumentException*/;
 /*public*/ QSet<File*> findFiles(/*@Nonnull*/ QString name, /*@Nonnull*/ QString root, /*@Nonnull*/ FileUtil::Location location);

 /*public*/ QString getExternalFilename(QString pName);
 /*public*/ QString getExternalFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString pName);
 /*public*/ QString getAbsoluteFilename(QString path);
 /*public*/ QString getAbsoluteFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path);
 /*public*/ QString getPortableFilename(File* file);
 /*public*/ QString getPortableFilename(File* file, bool ignoreUserFilesPath, bool ignoreProfilePath);
 /*public*/ QString getPortableFilename(QString filename);
 /*public*/ QString getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath);
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
 /*public*/ QString getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ File* file);
 /*public*/ QString getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ File* file, bool ignoreUserFilesPath, bool ignoreProfilePath);
 /*public*/ QString getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString filename);
 /*public*/ QString getPortableFilename(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString filename, bool ignoreUserFilesPath,
         bool ignoreProfilePath);
 /*public*/ bool isPortableFilename(QString filename);
 /*public*/ QString getHomePath();
 /*public*/ QString getUserFilesPath() ;
 /*public*/ QString getUserFilesPath(/*@CheckForNull*/ Profile* profile);
 /*public*/ void setUserFilesPath(/*@CheckForNull*/ Profile* profile, /*@Nonnull*/ QString path);
 /*public*/ QString getProfilePath(Profile*);
 /*public*/ QString getProfilePath();
 QT_DEPRECATED/*public*/ void setProfilePath(QString path);
 /*public*/ QString getPreferencesPath();
 /*public*/ QString getProgramPath();
 /*public*/ void setProgramPath(QString path);
 /*public*/ void setProgramPath(File* path);
 /*public*/ QString getUserResourcePath();
 /*public*/ void logFilePaths();
 /*public*/ QString getScriptsPath();
 /*public*/ QString getScriptsPath(/*@CheckForNull*/ Profile* profile);
 /*public*/ void setScriptsPath(/*@CheckForNull*/ Profile* profile, /*@CheckForNull */ QString path);

 /*public*/ void backup(File* file); //throws IOException
 /*public*/ void rotate(/*@NonNULL*/ File* file, int max, QString extension);// //throws IOException
 /*public*/ static FileUtilSupport* getDefault();
 /*public*/ QStringList* findProgramPath();
 /*public*/ QString readURL(QUrl url) /*throw (IOException)*/;
 /*public*/ QString sanitizeFilename(QString name);
 /*public*/ void createDirectory(QString path);
 /*public*/ void createDirectory(File* dir);
 /*public*/ bool _delete(File* path);
 /*public*/ void copy(File* source, File* dest) /*throw (IOException)*/;
 /*public*/ void appendTextToFile(File* file, QString text) /*throw (IOException)*/;
 /*public*/ QTextStream* findInputStream(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations);
 /*public*/ QTextStream* findInputStream(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths);
 /*public*/ QString findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths);
 /*public*/ QString urlToURI(/*@Nonnull*/ QUrl url);
 /*public*/ QUrl findURL(/*@Nonnull*/ QString path, /*@Nonnull*/ QStringList searchPaths);
 /*public*/ QString findURI(/*@Nonnull*/ QString path);
 /*public*/ QString findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ QStringList searchPaths);
 /*public*/ QString findURI(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations);
 /*public*/ QString findExternalFilename(/*@Nonnull*/ QString path);
 /*public*/ QUrl findURL(/*@Nonnull*/ QString path, FileUtil::Location locations);
 /*public*/ QUrl findURL(/*@Nonnull*/ QString path, /*@Nonnull*/ FileUtil::Location locations, /*@Nonnull*/ QStringList searchPaths);
 /*public*/ QString locateFile(QDir start, QString fileName);
 /*public*/ QString pathFromPortablePath(Profile *profile, /*@Nonnull*/ QString path);
 /*public*/ QString selectProgramPath(QStringList *stringList);
 /*public*/ QStringList* getPaths();

private:
 /*private*/ static /*final*/ QString homePath;// = System.getProperty("user.home") + File.separator; // NOI18N
 /*
  * Settable directories
  */
 /* JMRI program path, defaults to directory JMRI is executed from */
 /*private*/ QString programPath;// = null;
 /* path to jmri.jar */
 /*private*/ QString jarPath;// = null;
 /* path to the jython scripts directory */
 /*private*/ QHash<Profile*, QString> scriptsPaths;// = null;
 /* path to the user's files directory */
 /*private*/ QHash<Profile*, QString> userFilesPaths;// = null;
 /* path to profiles in use */
 /*private*/ /*final*/ QHash<Profile*, QString> profilePaths;// = new HashMap<>();
 /* path to the current profile */
 /*private*/ QString profilePath;// = null;
 // initialize logging
 ///*private*/ static /*final*/ Logger log = LoggerFactory.getLogger(FileUtilSupport.class);
 static Logger* log;
 // default instance
 /*volatile*/ /*private*/ static FileUtilSupport* defaultInstance;// = null;
 /*private*/ void scanDir(QDir start, QStringList *paths, int depth);
 QStringList* paths = nullptr;
 /*private*/ bool copyRecursively(const QString &srcFilePath,
                                  const QString &tgtFilePath);
 /*private*/ QSet<File*> findFiles(QString name, File* root);

private slots:
 void rowChanged(int);
};

#endif // FILEUTILSUPPORT_H
