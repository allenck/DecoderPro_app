#ifndef FILE_H
#define FILE_H

#include <QObject>
#include "javaqt_global.h"
#include <QFile>

class QDateTime;
class FilenameFilter;
class FileFilter;
class JAVAQTSHARED_EXPORT File : public QObject
{
  Q_OBJECT
public:
    //explicit File(QObject *parent = 0);
    /*public*/ File(QString pathname, QObject* parent = 0);
    /*public*/ File(QString parent, QString child, QObject* obj = 0);
    /*public*/ File(File* parent, QString child, QObject* obj = 0);
    ~File() {}
    File(const File&) : QObject() {}
    /*public*/ QString getName();
    /*public*/ QString getParent();
    /*public*/ File* getParentFile();
    /*public*/ QString getPath();
    /*public*/ bool isAbsolute();
    /*public*/ QString getAbsolutePath();
    /*public*/ File* getAbsoluteFile();
    /*public*/ QString getCanonicalPath(); /*throws IOException*/
    /*public*/ File* getCanonicalFile(); /*throws IOException*/
    /*public*/ bool canRead();
    /*public*/ bool canWrite();
    /*public*/ bool exists();
    /*public*/ bool isDirectory();
    /*public*/ bool isFile();
    /*public*/ bool isHidden();
    /*public*/ QStringList list();
    Q_INVOKABLE/*public*/ QString toString();
    Q_INVOKABLE/*public*/ bool equals(QObject *other);
    /*public*/ QStringList list(FilenameFilter* filter);
    /*public*/ QList<File*> listFiles();
    /*public*/ QList<File*> listFiles(FilenameFilter* filter);
    /*public*/ QList<File*> listFiles(FileFilter* filter);
    /*public*/ bool _delete();
    /*public*/ bool mkdir();
    /*public*/ bool mkdirs();
    /*public*/ bool createNewFile() /*throws IOException*/;
    /**
     * The system-dependent default name-separator character, represented as a
     * string for convenience.  This string contains a single character, namely
     * <code>{@link #separatorChar}</code>.
     */
    /*public*/ static /*final*/ QChar separatorChar;// = "" + separatorChar;
    /**
     * The system-dependent default name-separator character, represented as a
     * string for convenience.  This string contains a single character, namely
     * <code>{@link #separatorChar}</code>.
     */
    /*public*/ static /*final*/ QString separator;// = "" + separatorChar;
    /*public*/ long length();

    /**
     * The system-dependent path-separator character.  This field is
     * initialized to contain the first character of the value of the system
     * property <code>path.separator</code>.  This character is used to
     * separate filenames in a sequence of files given as a <em>path list</em>.
     * On UNIX systems, this character is <code>':'</code>; on Microsoft Windows systems it
     * is <code>';'</code>.
     *
     * @see     java.lang.System#getProperty(java.lang.String)
     */
    /*public*/ static /*final*/ QChar pathSeparatorChar;// = fs.getPathSeparator();
    /**
     * The system-dependent path-separator character, represented as a string
     * for convenience.  This string contains a single character, namely
     * <code>{@link #pathSeparatorChar}</code>.
     */
    /*public*/ static /*final*/ QString pathSeparator;// = "" + pathSeparatorChar;
    /*public*/ bool renameTo(File *dest);
    /*public*/ QDateTime lastModified();
    /*public*/ QString fileName();
    /*public*/ QString absoluteFilePath();
    /*public*/ QFile* toQfile();
signals:

public slots:
private:
    /**
     * This abstract pathname's normalized pathname string. A normalized
     * pathname string uses the default name-separator character and does not
     * contain any duplicate or redundant separators.
     *
     * @serial
     */
    /*private*/ /*final*/ QString path = QString();
    /**
     * Enum type that indicates the status of a file path.
     */
    /*private*/ /*static*/ enum PathStatus {UNKNOWN, INVALID, CHECKED };

    /*final*/ bool isInvalid();
    /**
     * The flag indicating whether the file path is invalid.
     */
    /*private*/ /*transient*/ PathStatus status;// = null;
    /**
     * The length of this abstract pathname's prefix, or zero if it has no
     * prefix.
     */
    /*private*/ /*final*/ /*transient*/ int prefixLength;
    int getPrefixLength();

    /*private*/ File(QString pathname, int prefixLength, QObject* parent = 0);
    /*private*/ File(QString child, File* parent, QObject* oparent = 0);

friend class FileUtil;
friend class FileUtilSupport;
friend class FileInputStream;
};

#endif // FILE_H
