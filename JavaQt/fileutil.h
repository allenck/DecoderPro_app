#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QObject>
#include <QFile>
#include "logger.h"
#include "exceptions.h"
#include <QDir>
#include "javaqt_global.h"
#include "file.h"

class QTextStream;
class JAVAQTSHARED_EXPORT FileUtil : public QObject
{
    Q_OBJECT
public:
     explicit FileUtil(QObject *parent = 0);
    /*static*/ /*public*/ enum Location {

        INSTALLED, USER, ALL, NONE
    };
    static /*public*/ File* getFile(QString path); //throw (FileNotFoundException);
    static /*public*/ QString getExternalFilename(QString pName);
    static /*public*/ QString getPortableFilename(File* file);
    static /*public*/ QString getPortableFilename(QString filename);
    static /*public*/ QString getPortableFilename(File* file, bool ignoreUserFilesPath, bool ignoreProfilePath);
    static /*public*/ QString getPortableFilename(QString filename, bool ignoreUserFilesPath, bool ignoreProfilePath);
    static /*public*/ bool isPortableFilename(QString filename);
    static /*public*/ QTextStream* findInputStream(QString path);
    static /*public*/ QTextStream* findInputStream(QString path, /*@NonNull*/ QStringList searchPaths);

    /**
     * Portable reference to items in the JMRI program directory.
     */
    static /*public*/ /*final*/const QString PROGRAM;// = "program:"; // NOI18N
    /**
     * Portable reference to items in the JMRI user's preferences directory.
     */
    static /*public*/  const QString PREFERENCES;// = "preference:"; // NOI18N
    /**
     * Portable reference to the JMRI applications preferences directory.
     */
    static /*public*/ const QString SETTINGS;// = "settings:"; // NOI18N
    /**
     * Portable reference to the user's home directory.
     */
    static /*public*/ /*final*/const QString HOME;// = "home:"; // NOI18N
    /**
     * Portable reference to the current profile directory.
     */
    static /*public*/ const QString PROFILE;// = "profile:"; // NOI18N
    /**
     * Portable reference to the current scripts directory.
     */
    static /*public*/ const QString SCRIPTS;// = "scripts:"; // NOI18N
    /**
     * Replaced with {@link #PROGRAM}.
     *
     * @see #PROGRAM
     * @deprecated
     */
    //@Deprecated
    static /*public*/ /*final*/const QString RESOURCE;// = "resource:"; // NOI18N
   // @Deprecated
    /**
     * Replaced with {@link #PREFERENCES}.
     *
     * @see #PREFERENCES
     */
    static /*public*/ /*final*/ const QString FILE;// = "file:"; // NOI18N
    /**
     * The portable file path component separator.
     */
    static /*public*/ /*final*/ const QChar SEPARATOR;// = '/'; // NOI18N
    static /*public*/ QString getUserResourcePath();
    static /*public*/ QUrl findURL(QString path);
    static /*public*/ QUrl findURL(QString path, /*@NonNull*/ QStringList searchPaths);
    static /*public*/ QUrl findURL(QString path, Location locations);
    static /*public*/ QUrl findURL(QString path, Location locations, /*@Nonnull*/ QStringList searchPaths);
    static /*public*/ QUrl fileToURL(QFile* file);
    static /*public*/ QUrl fileToURL(File* file);
    static /*public*/ QString getUserFilesPath();
    /**
     * Set the user's files directory.
     *
     * @see #getUserFilesPath()
     * @param path The path to the user's files directory
     */
    static /*public*/ void setUserFilesPath(QString path);
    static /*public*/ QString getProfilePath();
    static /*public*/ void setProfilePath(QString path);
    static /*public*/ QString getPreferencesPath();
    /*public*/ static QString getScriptsPath();
    static /*public*/ QString getProgramPath();
    static /*public*/ void setProgramPath(QString path);
    static /*public*/ void setProgramPath(File* path);
    static /*public*/ QUrl findExternalFilename(QString path);
    static /*public*/ QString getHomePath();
    /*public*/ static void createDirectory(QString path);
    /*public*/ static void createDirectory(File* dir);
    static /*public*/ void logFilePaths();
    /**
     * Set the path to python scripts.
     *
     * @param path the scriptsPath to set
     */
    /*public*/ static void setScriptsPath(QString path);
    /*public*/ static QString readFile(File* file); // throw (IOException);
    static /*public*/ QString getAbsoluteFilename(QString path);
    /*public*/ static QString readURL(QUrl url); // throw (IOException);
    /* path to the current profile */

    /*public*/ static bool _delete(File* path);
    /*public*/ static void copy(File* source, File* dest) /*throws IOException*/;
    /*public*/ static void appendTextToFile(File* file, QString text);// throw (IOException);
    /*public*/ static void backup(File* file);// //throws IOException
    /*public*/ static QString sanitizeFilename(QString name);
    /*public*/ static QStringList* findProgramPath();


signals:

public slots:
private:
    /*
     * User's home directory
     */
    static /*private*/ QString homePath;// = System.getProperty("user.home") + File.separator; // NOI18N
    /*
     * Settable directories
     */
    /* JMRI program path, defaults to directory JMRI is executed from */
    //static /*private*/ QString programPath;// = NULL;
    /* path to jmri.jar */
    //static /*private*/ QString jarPath;// = NULL;
    /* path to the jython scripts directory */
    //static /*private*/ QString scriptsPath;// = NULL;
    /* path to the user's files directory */
    //static /*private*/ QString userFilesPath;// = NULL;
    //static /*private*/ QString profilePath;// = null;

//Logger log;
 static bool _debug;
};

#endif // FILEUTIL_H
