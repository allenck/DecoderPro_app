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
    /*public*/ void writeXML(QFile* file, QDomDocument doc) const throw (FileNotFoundException);

    /**
     * Specify a standard prefix for DTDs in new XML documents
     */
    static /*public*/ /*final*/ QString dtdLocation;// = "/xml/DTD/";
    static QDomDocument doc;
    static /*public*/ void dumpElement(QDomElement name);
    /*public*/ void makeBackupFile(QString name) const;
    /*public*/ bool makeBackupFile(QString directory, File* file) const;
    /*public*/ void revertBackupFile(QString name);
    /*public*/ QString backupFileName(QString name) const;
    /*public*/ QString createFileNameWithDate(QString name) const;
    static /*public*/ QDomDocument newDocument(QDomElement root, QString dtd);
    static /*public*/ QDomDocument newDocument(QDomElement root);
    static /*public*/ void addDefaultInfo(QDomElement root);
    static /*public*/ QString xmlDir();
    //static bool validate;// = false;
    static bool include;// = true;
    /*public*/ enum Validate {
        /**
         * Don't validate input
         */
        None,
        /**
         * Require that the input specifies a Schema which validates
         */
        RequireSchema,
        /**
         * Validate against DTD if present (no DTD passes too)
         */
        CheckDtd,
        /**
         * Validate against DTD if present, else Schema must be present and
         * valid
         */
        CheckDtdThenSchema
    };
    /*public*/ Validate getValidate();
    /*public*/ void setValidate(Validate v);
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
    /*public*/ QString getPathname();
    static /*public*/ Validate getDefaultValidate();
    static /*public*/ void setDefaultValidate(Validate v);
    static /*public*/ QString getDefaultDtdLocation();
    static /*public*/ void setDefaultDtdLocation(QString v);
    static /*public*/ QString defaultDtdLocation;// = "/xml/DTD/";
    /*public*/ QString getDtdLocation();
    /*public*/ void setDtdLocation(QString v);
    /**
     * Specify validation operations on input. The available choices are
     * restricted to what the underlying SAX Xerces and JDOM implementations
     * allow.
     */

signals:
    
public slots:
    
private:
 static Logger* log;
 /*private*/ QString getDate() const;
 QString currFile;
QDomElement docElem;
static /*private*/ Validate defaultValidate;// = Validate.None;
/*private*/ Validate validate;// = defaultValidate;

protected:
 /*protected*/ bool checkFile(QString name);
 /*protected*/ QFile* findFile(QString name) const;
 QT_DEPRECATED /*protected*/ QDomElement getRoot(bool validate, QDataStream* stream) /*throw (JDOMException)*/;
 /*protected*/ QDomElement getRoot(QDataStream* stream) /*throw (JDOMException)*/;
 friend class LayoutEditor;
 friend class ConfigXmlManager;
};

#endif // XMLFILE_H
