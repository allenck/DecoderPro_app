#ifndef XMLFILE_H
#define XMLFILE_H

#include <QObject>
#include <QDomDocument>
#include <QDomElement>
#include "exceptions.h"
#include <QFile>
#include <QFileInfo>
#include "logger.h"
//#include "QFileDialog"
#include <QDateTime>
#include "javaqt_global.h"

class JFileChooser;
class File;
class JAVAQTSHARED_EXPORT XmlFile : public QObject
{
    Q_OBJECT
public:
    explicit XmlFile(QObject *parent = 0);
    /*public*/ static /*final*/ QString xsltLocation;// = "/xml/XSLT/";
    /*public*/ QDomElement rootFromName(QString name) throw (JDOMException);
 /*public*/ QDomElement rootFromFile(File* file);
    /*public*/ QDomElement rootFromFile(QFile* file) throw (JDOMException);
    /*public*/ QDomElement rootFromInputStream(QDataStream* stream) /*throw (JDOMException)*/;
    /*public*/ QDomElement rootFromURL(QUrl* url) throw (JDOMException);
    /*public*/ void writeXML(File* file, QDomDocument doc) throw (FileNotFoundException);
    /*public*/ void writeXML(QFile* file, QDomDocument doc) throw (FileNotFoundException);

    /**
     * Specify a standard prefix for DTDs in new XML documents
     */
    static /*public*/ /*final*/ QString dtdLocation;// = "/xml/DTD/";
    static QDomDocument doc;
    static /*public*/ void dumpElement(QDomElement name);
    /*public*/ void makeBackupFile(QString name);
    /*public*/ bool makeBackupFile(QString directory, File* file);
    /*public*/ void revertBackupFile(QString name);
    /*public*/ QString backupFileName(QString name);
    /*public*/ QString createFileNameWithDate(QString name);
    static /*public*/ QDomDocument newDocument(QDomElement root, QString dtd);
    static /*public*/ QDomDocument newDocument(QDomElement root);
    static /*public*/ void addDefaultInfo(QDomElement root);
    static /*public*/ QString xmlDir();
    static bool verify;// = false;
    static bool include;// = true;
    static /*public*/ bool getVerify();
    static /*public*/ void setVerify(bool v);
    /**
     * Provide a JFileChooser initialized to the default user location, and with
     * a default filter.
     *
     * @param filter Title for the filter, may not be NULL
     * @param suffix1 An allowed suffix, or NULL
     * @param suffix2 A second allowed suffix, or NULL. If both arguments are
     * NULL, no specific filtering is done.
     */
    /*public*/ static JFileChooser* userFileChooser(QString filter, QString suffix1, QString suffix2);
    /*public*/ static JFileChooser* userFileChooser();
    /*public*/ static JFileChooser* userFileChooser(QString filter);
    /*public*/ static JFileChooser* userFileChooser(QString filter, QString suffix1);
    //static /*private*/ Logger log = Logger.getLogger(XmlFile.class.getName());

signals:
    
public slots:
    
private:
 Logger* log;
 /*private*/ QString getDate();
 QString currFile;
QDomElement docElem;
protected:
 ///*protected*/ QDomElement getRoot(bool verify, InputStreamReader reader) throw (JDOMException);
 /*protected*/ bool checkFile(QString name);
/*protected*/ QFile* findFile(QString name);
 /*protected*/ QDomElement getRoot(bool verify, QDataStream* stream) /*throw (JDOMException)*/;
 friend class LayoutEditor;
};

#endif // XMLFILE_H
