#ifndef FILEUTILSUPPORT_H
#define FILEUTILSUPPORT_H

#include "bean.h"
#include "exceptions.h"
#include <QDir>
#include "fileutil.h"

class Logger;
class File;
class FileUtilSupport : public Bean
{
public:
 FileUtilSupport();
 /*public*/ File* getFile(QString path) throw (FileNotFoundException);
 /*public*/ QUrl* getURL(QString path) throw (FileNotFoundException);
 /*public*/ QString getExternalFilename(QString pName);
 /*public*/ QString getAbsoluteFilename(QString path);
 /*public*/ QString getPortableFilename(File* file);
 /*public*/ QString getPortableFilename(File* file, bool ignoreUserFilesPath, bool ignoreProfilePath);
 /*public*/ QString getPortableFilename(QString filename);
 /*public*/ QString getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath);
 /*public*/ bool isPortableFilename(QString filename);
 /*public*/ QString getHomePath();
 /*public*/ QString getUserFilesPath() ;
 /*public*/ void setUserFilesPath(QString path) ;
 /*public*/ QString getProfilePath();
 /*public*/ void setProfilePath(QString path);
 /*public*/ QString getPreferencesPath();
 /*public*/ QString getProgramPath();
 /*public*/ void setProgramPath(QString path);
 /*public*/ void setProgramPath(File* path);
 /*public*/ QString getUserResourcePath();
 /*public*/ void logFilePaths();
 /*public*/ QString getScriptsPath();
 /*public*/ void setScriptsPath(QString path);

 /*public*/ void backup(File* file); //throws IOException
 /*public*/ void rotate(/*@NonNULL*/ File* file, int max, QString extension);// //throws IOException
 /*public*/ static FileUtilSupport* getDefault();
 /*public*/ QStringList* findProgramPath();
 /*public*/ QString readURL(QUrl url) throw (IOException);
 /*public*/ QString sanitizeFilename(QString name);
 /*public*/ void createDirectory(QString path);
 /*public*/ void createDirectory(File* dir);
 /*public*/ bool _delete(File* path);
 /*public*/ void copy(File* source, File* dest) throw (IOException);
 /*public*/ void appendTextToFile(File* file, QString text) throw (IOException);
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
 /*public*/ QString pathFromPortablePath(/*@Nonnull*/ QString path);
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
 /*private*/ QString scriptsPath;// = null;
 /* path to the user's files directory */
 /*private*/ QString userFilesPath;// = null;
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

private slots:
 void rowChanged(int);
};

#endif // FILEUTILSUPPORT_H
