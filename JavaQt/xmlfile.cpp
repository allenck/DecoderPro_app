#include "xmlfile.h"
#include "fileutil.h"
#include <QTextStream>
#include <QDebug>
#include <QDate>
#include "file.h"
#include "jfilechooser.h"
#include <QUrl>
#include <QDataStream>
#include "loggerfactory.h"

QString XmlFile::dtdLocation = "/xml/DTD/";
//bool XmlFile::validate = false;
bool XmlFile::include = true;
QDomDocument XmlFile::doc = QDomDocument();

/**
 * Define root part of URL for XSLT style page processing instructions. <p>
 * See the <A
 * HREF="http://jmri.org/help/en/html/doc/Technical/XmlUsage.shtml#xslt">XSLT
 * versioning discussion</a>. <p> Things that have been tried here: <dl>
 * <dt>/xml/XSLT/ <dd>(Note leading slash) Works if there's a copy of the
 * xml directory at the root of whatever served the XML file, e.g. the JMRI
 * web site or a local computer running a server. Doesn't work for e.g.
 * yahoo groups files. <dt>http://jmri.org/xml/XSLT/ <dd>Works well for
 * files on the JMRI.org web server, but only that. </dl>
 */
/*public*/ /*static*/ /*final*/ QString XmlFile::xsltLocation = "/xml/XSLT/";

XmlFile::XmlFile(QObject *parent) :
    QObject(parent)
{
 dtdLocation = defaultDtdLocation;
 validate = defaultValidate;

}
/**
 * Handle common aspects of XML files. <P> JMRI needs to be able to operate
 * offline, so it needs to store DTDs locally. At the same time, we want XML
 * files to be transportable, and to have their DTDs accessible via the web (for
 * browser rendering). Further, our code assumes that default values for
 * attributes will be provided, and it's necessary to read the DTD for that to
 * work. <p> We implement this using our own EntityResolvor, the
 * {@link jmri.util.JmriLocalEntityResolver} class.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2002, 2007, 2012
 * @version	$Revision: 22548 $
 */
///*public*/ abstract class XmlFile {


/**
 * Read the contents of an XML file from its filename. The name is expanded
 * by the {@link #findFile} routine. If the file is not found, attempts to
 * read the XML file from a JAR resource.
 *
 * @param name Filename, as needed by {@link #findFile}
 * @throws org.jdom.JDOMException
 * @throws java.io.FileNotFoundException
 * @return NULL if not found, else root element of located file
     */
/*public*/ QDomElement XmlFile::rootFromName(QString name) throw (JDOMException)
{
 currFile = name;
 QFile* fp = new QFile(name);
 QFileInfo fi(name);
 if (fi.exists() && fi.isReadable())
 {
  if (log->isDebugEnabled())
  {
   log->debug("readFile: " + name + " from " + fi.canonicalFilePath());
  }
  return rootFromFile(fp);
 }

 QUrl resource = FileUtil::findURL(name);
 if (resource.isValid()) {
     return this->rootFromURL(&resource);
 } else {
     if (!name.startsWith("xml")) {
         return this->rootFromName("xml" + File::separator + name);
     }
     log->warn("Did not find file or resource " + name);
     throw FileNotFoundException("Did not find file or resource " + name);
 }
}

/*public*/ QString XmlFile::getPathname()
{
 return currFile;
}


/**
 * Read a File as XML, and return the root object.
 *
 * Multiple methods are tried to locate the DTD needed to do this.
 * Exceptions are only thrown when local recovery is impossible.
 *
 * @throws org.jdom.JDOMException only when all methods have failed
 * @throws java.io.FileNotFoundException
 * @param file File to be parsed. A FileNotFoundException is thrown if it
 * doesn't exist.
 * @return root element from the file. This should never be NULL, as an
 * exception should be thrown if anything goes wrong.
 */
/*public*/ QDomElement XmlFile::rootFromFile(File* file)
{
 return rootFromFile(new QFile(file->getAbsolutePath()));
}

/*public*/ QDomElement XmlFile::rootFromFile(QFile* file) throw (JDOMException)
{
 QFileInfo info(file->fileName());
 if (log->isDebugEnabled())
 {
  log->debug("reading xml from file: " + info.canonicalFilePath());
 }
 currFile = file->fileName();

//    FileInputStream fs = new FileInputStream(file);
//    try {
//        return getRoot(verify, fs);
//    } finally {
//        fs.close();
//    }
 if(!file->open(QFile::ReadOnly | QFile::Text)) return QDomElement();
 if(!doc.setContent(file))
 {
   file->close();
   return QDomElement();
 }
 file->close();
 QString content = doc.toString();
 docElem = doc.documentElement();
 QString root = docElem.firstChild().toElement().nodeName();
 return docElem;
}

/**
 * Read an {@link java.io.InputStream} as XML, and return the root object.
 *
 * Multiple methods are tried to locate the DTD needed to do this.
 * Exceptions are only thrown when local recovery is impossible.
 *
 * @throws org.jdom.JDOMException only when all methods have failed
 * @throws java.io.FileNotFoundException
 * @param stream InputStream to be parsed.
 * @return root element from the file. This should never be NULL, as an
 * exception should be thrown if anything goes wrong.
 */
/*public*/ QDomElement XmlFile::rootFromInputStream(QDataStream* stream) /*throw (JDOMException)*/
{
 //currFile = ((QFile*)stream->device())->fileName();
 return getRoot(stream);
}

/**
 * Read a URL as XML, and return the root object.
 *
 * Multiple methods are tried to locate the DTD needed to do this.
 * Exceptions are only thrown when local recovery is impossible.
 *
 * @throws org.jdom.JDOMException only when all methods have failed
 * @throws FileNotFoundException
 * @param url URL locating the data file
 * @return root element from the file. This should never be NULL, as an
 * exception should be thrown if anything goes wrong.
 */
/*public*/ QDomElement XmlFile::rootFromURL(QUrl* url) throw (JDOMException)
{
 if (log->isDebugEnabled())
 {
  log->debug("reading xml from URL: " + url->toString());
 }
 QFile file(url->toString());
 return rootFromFile(&file);
 //return getRoot(verify, url.openConnection().getInputStream());
 //return QDomElement();
}

/**
 * Get the root element from an XML document in a stream.
 */
///*protected*/ QDomElement XmlFile::getRoot(bool verify, QDataStream* stream) /*throw (JDOMException)*/
//{
// if (log->isDebugEnabled())
// {
//  log->debug("getRoot from stream");
// }
// //SAXBuilder builder = getBuilder(verify);  // argument controls validation
//  //doc = builder.build(new BufferedInputStream(stream));
// doc = QDomDocument();
// doc.setContent(stream->device());
// // find root
// return doc.documentElement();
//}

/**
 * Get the root element from an XML document in a stream.
 */
/*protected*/ QDomElement XmlFile::getRoot(QDataStream* stream) /*throw (JDOMException)*/
{
 if (log->isDebugEnabled())
 {
  log->debug("getRoot from stream");
 }
 //SAXBuilder builder = getBuilder(verify);  // argument controls validation
  //doc = builder.build(new BufferedInputStream(stream));
 doc = QDomDocument();
 doc.setContent(stream->device());
 // find root
 return doc.documentElement();
}

/**
 * Get the root element from an XML document in a Reader.
 *
 * Runs through a BufferedReader for increased performance.
 *
 * @since 3.1.5
 */
///*protected*/ QDomElement XmlFile::getRoot(bool verify, InputStreamReader reader) throw (JDOMException)
//{
//    if (log->isDebugEnabled()) {
//        log->debug("getRoot from reader with encoding " + reader.getEncoding());
//    }
//    SAXBuilder builder = getBuilder(verify);  // argument controls validation
//    Document doc = builder.build(new BufferedReader(reader));
//    // find root
//    return doc.getRootElement();
//}
/*public*/ void XmlFile::writeXML(File* file, QDomDocument doc) throw (FileNotFoundException)
{
 writeXML(new QFile(file->getPath()), doc);
}

/**
 * Write a File as XML.
 *
 * @throws org.jdom.JDOMException
 * @throws FileNotFoundException
 * @param file File to be created.
 * @param doc Document to be written out. This should never be NULL.
 */
/*public*/ void XmlFile::writeXML(QFile* file, QDomDocument doc) const throw (FileNotFoundException)
{
 QFileInfo info(file->fileName());
 // ensure parent directory exists
 if(!QDir(info.canonicalPath()).exists())
  FileUtil::createDirectory(info.canonicalPath());
 // write the result to selected file
 if(!file->isOpen())
  file->open(QIODevice::WriteOnly | QIODevice::Truncate);
 QTextStream stream (file);
//    try {
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat());
//        fmt.output(doc, o);
//    } finally {
//        o.close();
//    }
 stream.setCodec("UTF-8");
 QString sXml = doc.toString();
 doc.save(stream, 2);
}

/**
 * Check if a file of the given name exists. This uses the same search order
 * as {@link #findFile}
 *
 * @param name file name, either absolute or relative
 * @return true if the file exists in a searched place
 */
/*protected*/ bool XmlFile::checkFile(QString name)
{
 QFile* fp = new QFile(name);
 if (fp->exists())
 {
  return true;
 }
 fp = new QFile(FileUtil::getUserFilesPath() + name);
 if (fp->exists())
 {
  return true;
 }
 else
 {
  QFile* fx = new QFile(xmlDir() + name);
  if (fx->exists())
  {
   return true;
  }
  else
  {
   return false;
  }
 }
}

/**
 * Return a File object for a name. This is here to implement the search
 * rule: <OL> <LI>Look in user preferences directory, located by
 * {@link jmri.util.FileUtil#getUserFilesPath()} <li>Look in current working
 * directory (usually the JMRI distribution directory) <li>Look in program
 * directory, located by {@link jmri.util.FileUtil#getProgramPath()}
 * <LI>Look in XML directory, located by {@link #xmlDir} <LI>Check for
 * absolute name. </OL>
 *
 * @param name Filename perhaps containing subdirectory information (e.g.
 * "decoders/Mine.xml")
 * @return NULL if file found, otherwise the located File
 */
/*protected*/ QFile* XmlFile::findFile(QString name) const
{
 QFile* fp =  new QFile(FileUtil::getUserFilesPath() + name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(FileUtil::getProgramPath() + name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(xmlDir() + name);
 if (fp->exists())
 {
  return fp;
 }
 return NULL;
}

/**
 * Diagnostic printout of as much as we can find
 *
 * @param name Element to print, should not be NULL
 */
//@SuppressWarnings("unchecked")
/*static*/ /*public*/ void XmlFile::dumpElement(QDomElement name)
{
 QDomNodeList l = name.childNodes();
 for (int i = 0; i < l.size(); i++)
 {
  /*System.out.println*/qDebug() << tr(" Element: ") + l.at(i).toElement().tagName() + " ns: " + l.at(i).namespaceURI();
 }
}

/**
 * Move original file to a backup. Use this before writing out a new version
 * of the file.
 *
 * @param name Last part of file pathname i.e. subdir/name, without the
 * pathname for either the xml or preferences directory.
 */
/*public*/ void XmlFile::makeBackupFile(QString name) const
{
 QFile* file = findFile(name);
 if (file == NULL)
 {
  log->info("No " + name + " file to backup");
 }
 else
 {
  QFileInfo info(file->fileName());

  QString backupName = backupFileName(info.absoluteFilePath());
  QFile* backupFile = findFile(backupName);
  if (backupFile != NULL)
  {
   if (backupFile->remove())
   {
    log->debug("deleted backup file " + backupName);
   }
  }
  if (file->rename(backupName))
  {
   log->debug("created new backup file " + backupName);
  }
  else
  {
   log->error("could not create backup file " + backupName);
  }
 }
}

/**
 * Move original file to backup directory.
 *
 * @param directory the backup directory to use.
 * @param file the file to be backed up. The file name will have the current
 * date embedded in the backup name.
 * @return true if successful.
 */
/*public*/ bool XmlFile::makeBackupFile(QString directory, File* file) const
{
 if (file == NULL)
 {
  log->info("No file to backup");
 }
 else
 {
  QFileInfo info(file->getPath());
  QString backupFullName = directory + QDir::separator() + createFileNameWithDate(info.fileName());
  if (log->isDebugEnabled())
  {
   log->debug("new backup file: " + backupFullName);
  }

  QFile* backupFile = findFile(backupFullName);
  if (backupFile != NULL)
  {
   if (backupFile->remove())
   {
    if (log->isDebugEnabled())
    {
     log->debug("deleted backup file " + backupFullName);
    }
   }
  }
  else
  {
   backupFile = new QFile(backupFullName);
  }
  // create directory if needed
  QDir parentDir( QFileInfo(backupFullName).absolutePath());
  if (!parentDir.exists())
  {
   if (log->isDebugEnabled())
   {
    log->debug("creating backup directory: " + parentDir.absolutePath());
   }
   if (!parentDir.mkpath(parentDir.absolutePath()))
   {
    log->error("backup directory not created");
    return false;
   }
  }
  if (file->rename(backupFullName))
  {
   if (log->isDebugEnabled())
   {
    log->debug("created new backup file " + backupFullName);
   }
  }
  else
  {
   if (log->isDebugEnabled())
   {
    log->debug("could not create backup file " + backupFullName);
   }
   return false;
  }
 }
 return true;
}

/**
 * Revert to original file from backup. Use this for testing backup files.
 *
 * @param name Last part of file pathname i.e. subdir/name, without the
 * pathname for either the xml or preferences directory.
 */
/*public*/ void XmlFile::revertBackupFile(QString name) {
    QFile* file = findFile(name);
    if (file == NULL) {
        log->info("No " + name + " file to revert");
    } else {
        QString backupName = QFileInfo(name).absolutePath();
        QFile* backupFile = findFile(backupName);
        if (backupFile != NULL) {
            log->info("No " + backupName + " backup file to revert");
            if (file->remove()) {
                log->debug("deleted original file " + name);
            }

            if (backupFile->rename(name))
            {
                log->debug("created original file " + name);
            } else {
                log->error("could not create original file " + name);
            }
        }
    }
}

/**
 * Return the name of a new, unique backup file. This is here so it can be
 * overridden during tests. File to be backed-up must be within the
 * preferences directory tree.
 *
 * @param name Filename without preference path information, e.g.
 * "decoders/Mine.xml".
 * @return Complete filename, including path information into preferences
 * directory
 */
/*public*/ QString XmlFile::backupFileName(QString name) const {
    QString f = name + ".bak";
    if (log->isDebugEnabled()) {
        log->debug("backup file name is: " + f);
    }
    return f;
}

/*public*/ QString XmlFile::createFileNameWithDate(QString name)  const{
    // remove .xml extension
    QStringList fileName = name.split(".xml");
    QString f = fileName.at(0) + "_" + getDate() + ".xml";
    if (log->isDebugEnabled()) {
        log->debug("backup file name is: " + f);
    }
    return f;
}

/**
 * @return QString based on the current date in the format of year month day
 * hour minute second. The date is fixed length and always returns a date
 * represented by 14 characters.
 */
/*private*/ QString XmlFile::getDate() const{
    //Calendar now = Calendar.getInstance();
    QDateTime now = QDateTime::currentDateTime();
//    int month = now.get(Calendar.MONTH) + 1;
//    QString m = Integer.toQString(month);
//    if (month < 10) {
//        m = "0" + Integer.toQString(month);
//    }
//    int day = now.get(Calendar.DATE);
//    QString d = Integer.toQString(day);
//    if (day < 10) {
//        d = "0" + Integer.toQString(day);
//    }
//    int hour = now.get(Calendar.HOUR);
//    QString h = Integer.toQString(hour);
//    if (hour < 10) {
//        h = "0" + Integer.toQString(hour);
//    }
//    int minute = now.get(Calendar.MINUTE);
//    QString min = Integer.toQString(minute);
//    if (minute < 10) {
//        min = "0" + Integer.toQString(minute);
//    }
//    int second = now.get(Calendar.SECOND);
//    QString sec = Integer.toQString(second);
//    if (second < 10) {
//        sec = "0" + Integer.toQString(second);
//    }
//    QString date = "" + now.get(Calendar.YEAR) + m + d + h + min + sec;
    QString date = now.toString("yyyyMMddhhmmss");
    return date;
}

/**
 * Create the Document object to store a particular root Element.
 *
 * @param root Root element of the final document
 * @param dtd name of an external DTD
 * @return new Document, with root installed
 */
/*static*/ /*public*/ QDomDocument XmlFile::newDocument(QDomElement root, QString dtd) {
    /*Document*/ doc = QDomDocument(/*root.tagName()*/);
    //doc.setDocType(new DocType(root.tagName(), dtd));
    QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
    doc.appendChild(xmlProcessingInstruction);
//    xmlProcessingInstruction =  doc.createProcessingInstruction("xml-stylesheet","type=\"text/xsl\" href=\"/xml/XSLT/panelfile-2-9-6.xsl\"");
    xmlProcessingInstruction = doc.createProcessingInstruction(root.tagName(), dtd);
    doc.appendChild(xmlProcessingInstruction);
    addDefaultInfo(root);
    doc.appendChild(root);
    return doc;
}

/**
 * Create the Document object to store a particular root Element, without a
 * DocType DTD (e.g. for using a schema)
 *
 * @param root Root element of the final document
 * @return new Document, with root installed
 */
/*static*/ /*public*/ QDomDocument XmlFile::newDocument(QDomElement root) {
    /*Document*/ doc = QDomDocument(root.tagName());
    addDefaultInfo(root);
    return doc;
}

/**
 * Add default information to the XML before writing it out. <P> Currently,
 * this is identification information as an XML comment. This includes: <UL>
 * <LI>The JMRI version used <LI>Date of writing <LI>A CVS id string, in
 * case the file gets checked in or out </UL> <P> It may be necessary to
 * extend this to check whether the info is already present, e.g. if
 * re-writing a file.
 *
 * @param root The root element of the document that will be written.
 */
/*static*/ /*public*/ void XmlFile::addDefaultInfo(QDomElement root) {
    QString content = tr("Written by JMRI version ") + /*jmri.Version.name()*/ "3.11"
            + " on " + QDate::currentDate().toString();
            + " $Id: XmlFile.java 22548 2013-01-19 20:26:03Z rhwood $";
    //Comment comment = new Comment(content);
    QDomElement comment = doc.createElement("comment");
    comment.appendChild(doc.createTextNode(content));
    root.appendChild(comment);
}

/**
 * Define the location of XML files within the distribution directory. <P>
 * Use {@link FileUtil#getProgramPath()} since the current working directory
 * is not guaranteed to be the JMRI distribution directory if jmri.jar is
 * referenced by an external Java application.
 */
/*static*/ /*public*/ QString XmlFile::xmlDir() {
    return FileUtil::getProgramPath() + "xml" + QDir::separator();
}

/**
 * Whether to, by global default, validate the file being read. Public so it
 * can be set by scripting and for debugging.
 *
 * @return the default level of validation to apply to a file
 */
/*static*/ /*public*/ XmlFile::Validate XmlFile::getDefaultValidate() {
    return defaultValidate;
}

/*static*/ /*public*/ void XmlFile::setDefaultValidate(XmlFile::Validate v) {
    defaultValidate = v;
}

/*static*/ /*private*/ XmlFile::Validate XmlFile::defaultValidate = XmlFile::Validate::None;

/*public*/ XmlFile::Validate XmlFile::getValidate() {
    return validate;
}

/*public*/ void XmlFile::setValidate(Validate v) {
    validate = v;
}

/**
 * Get the default standard location for DTDs in new XML documents. Public
 * so it can be set by scripting and for debug.
 *
 * @return the default DTD location
 */
/*static*/ /*public*/ QString XmlFile::getDefaultDtdLocation() {
    return defaultDtdLocation;
}

/*static*/ /*public*/ void XmlFile::setDefaultDtdLocation(QString v) {
    defaultDtdLocation = v;
}

/*static*/ /*public*/ QString XmlFile::defaultDtdLocation = "/xml/DTD/";

/**
 * Get the location for DTDs in this XML document.
 *
 * @return the DTD location
 */
/*public*/ QString XmlFile::getDtdLocation() {
    return dtdLocation;
}

/*public*/ void XmlFile::setDtdLocation(QString v) {
    dtdLocation = v;
}

/**
 * Provide a JFileChooser initialized to the default user location, and with
 * a default filter.
 *
 * @param filter Title for the filter, may not be NULL
 * @param suffix1 An allowed suffix, or NULL
 * @param suffix2 A second allowed suffix, or NULL. If both arguments are
 * NULL, no specific filtering is done.
 */
/*public*/ /*static*/ JFileChooser* XmlFile::userFileChooser(QString filter, QString suffix1, QString suffix2)
{
 JFileChooser* fc = new JFileChooser(FileUtil::getUserFilesPath());
 // NoArchiveFileFilter filt = new NoArchiveFileFilter(filter);
 // if (suffix1 != null) {
 //     filt.addExtension(suffix1);
 // }
 // if (suffix2 != null) {
 //     filt.addExtension(suffix2);
 // }
 QString filt;
 if(suffix2 == "")
  filt = tr("%1 (*.%2)").arg(filter).arg(suffix1);
 else
  filt = tr("%1 (*.%2 *.%3)").arg(filter).arg(suffix1).arg(suffix2);

 fc->setFileFilter(filt);
 return fc;
}

/*public*/ /*static*/ JFileChooser* XmlFile::userFileChooser()
{
// QFileDialog* fc = new QFileDialog(0, tr("Select file"), FileUtil::getUserFilesPath(),"Roster XML files (*.xml);;All files (*.*)");
 JFileChooser* fc = new JFileChooser(FileUtil::getUserFilesPath());
 //NoArchiveFileFilter filt = new NoArchiveFileFilter();
 fc->setFileFilter("Script files (*.py)");
 return fc;
}

/*public*/ /*static*/ JFileChooser* XmlFile::userFileChooser(QString filter) {
    return userFileChooser(filter, NULL, NULL);
}

/*public*/ /*static*/ JFileChooser* XmlFile::userFileChooser(
        QString filter, QString suffix1) {
    return userFileChooser(filter, suffix1, "");
}

#if 0
/*public*/ static SAXBuilder getBuilder(boolean verify) {
    SAXBuilder builder = new SAXBuilder("org.apache.xerces.parsers.SAXParser", verify);  // argument controls validation

    builder.setEntityResolver(new JmriLocalEntityResolver());
    builder.setFeature("http://apache.org/xml/features/xinclude", true);
    builder.setFeature("http://apache.org/xml/features/xinclude/fixup-base-uris", false);
    builder.setFeature("http://apache.org/xml/features/allow-java-encodings", true);

    // for schema validation. Not needed for DTDs, so continue if not found now
    try {
        builder.setFeature("http://apache.org/xml/features/validation/schema", verify);
        builder.setFeature("http://apache.org/xml/features/validation/schema-full-checking", verify);

        // parse namespaces, including the noNamespaceSchema
        builder.setFeature("http://xml.org/sax/features/namespaces", true);

    } catch (Exception e) {
        log->warn("Could not set schema validation feature: " + e);
    }
    return builder;
}
#endif
// initialize logging
/*static*/ /*private*/ Logger* XmlFile::log = LoggerFactory::getLogger("XmlFile");
//}
