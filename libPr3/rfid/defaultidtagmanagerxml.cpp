#include "defaultidtagmanagerxml.h"
#include "fileutil.h"
#include "loggerfactory.h"
#include <QApplication>
#include "idtagmanager.h"

/**
 * Concrete implementation of abstract {@link jmri.jmrit.XmlFile} for
 * the {@link jmri.managers.DefaultIdTagManager}.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
// /*public*/ class DefaultIdTagManagerXml extends XmlFile {


    /*public*/ DefaultIdTagManagerXml::DefaultIdTagManagerXml(TranspondingTagManager *tagMan, QString baseFileName, QObject* parent)
     : XmlFile(parent)
    {
         manager = tagMan;
         IDTAG_BASE_FILENAME = baseFileName;
         /*private*/ /*final*/ QString FILE_LOCATION = FileUtil::getUserFilesPath();

    }

    /*public*/ void DefaultIdTagManagerXml::load() {
        log->debug("Loading...");
        try {
            readFile(getDefaultIdTagFileName());
        }
        catch (JDOMException ex) {
            log->error(tr("Exception during IdTag file reading: %1").arg(ex.getMessage()));
        }
        catch ( IOException ex) {
         log->error(tr("Exception during IdTag file reading: %1").arg(ex.getMessage()));
        }
    }

    /*public*/ void DefaultIdTagManagerXml::store() throw (IOException) {
            log->debug("Storing...");
            log->debug(tr("Using file: %1").arg(getDefaultIdTagFileName()));
            createFile(getDefaultIdTagFileName(), true);
            try {
                writeFile(getDefaultIdTagFileName());
            } catch (FileNotFoundException ex) {
                log->error(tr("File not found while writing IdTag file, may not be complete: %1").arg( ex.getMessage()));
            }
    }

    /*private*/ File* DefaultIdTagManagerXml::createFile(QString fileName, bool backup) {
        if (backup) {
            makeBackupFile(fileName);
        }

        File* file = nullptr;
        try {
            if (!checkFile(fileName)) {
                // The file does not exist, create it before writing
                file = new File(fileName);
                File* parentDir = file->getParentFile();
                if (!parentDir->exists()) {
                    if (!parentDir->mkdir()) {
                        log->error("Directory wasn't created");
                    }
                }
                if (file->createNewFile()) {
                    log->debug("New file created");
                }
           } else {
              file = new File(fileName);
           }
       } catch (IOException ex) {
          log->error(tr("Exception while creating IdTag file, may not be complete: %1").arg(ex.getMessage()));
       }
       return file;
   }

   /*private*/ void DefaultIdTagManagerXml::writeFile(QString fileName) throw (FileNotFoundException, IOException) {
        log->debug(tr("writeFile %1").arg(fileName));
        // This is taken in large part from "Java and XML" page 368
        QFile* file = findFile(fileName);
        if (file == nullptr) {
           file = new QFile(fileName);
        }
        // Create root element
        QDomDocument doc;
        QDomElement root = doc.createElement("idtagtable");              // NOI18N
#if 0
        root.setAttribute("noNamespaceSchemaLocation", // NOI18N
        "http://jmri.org/xml/schema/idtags.xsd", // NOI18N
        org.jdom2.Namespace.getNamespace("xsi", // NOI18N
        "http://www.w3.org/2001/XMLSchema-instance")); // NOI18N
#endif
        //Document doc = newDocument(root);
        doc.appendChild(root);

        // add XSLT processing instruction
        QMap<QString, QString> m = QMap<QString, QString>();
        m.insert("type", "text/xsl"); // NOI18N
        m.insert("href", xsltLocation + "idtags.xsl"); // NOI18N
#if 0
        QDomProcessingInstruction* p = new QDomProcessingInstruction("xml-stylesheet", m); // NOI18N
        doc.appendChild( p);
#endif
        QDomElement values;

        // Store configuration
        root.appendChild(values = doc.createElement("configuration"));                                              // NOI18N
        values.appendChild(doc.createElement("storeState").appendChild(doc.createTextNode(manager->isStateStored() ? "yes" : "no")));     // NOI18N
        values.appendChild(doc.createElement("useFastClock").appendChild(doc.createTextNode(manager->isFastClockUsed() ? "yes" : "no"))); // NOI18N

        // Loop through RfidTags
        root.appendChild(values = doc.createElement("idtags")); // NOI18N
        for (/*IdTag*/NamedBean* t : manager->getNamedBeanSet()) {
           log->debug(tr("Writing IdTag: %1").arg(t->getSystemName()));
           values.appendChild(((IdTag*)t)->store(manager->isStateStored()));
        }
         writeXML(file, doc);
      }

      /*private*/ void DefaultIdTagManagerXml::readFile(QString fileName) throw (JDOMException, IOException, IllegalArgumentException) {
      // Check file exists
      if (findFile(fileName) == nullptr) {
          log->debug(tr("%1 file could not be found").arg(fileName));
          return;
      }

      // Find root
      QDomElement root = rootFromName(fileName);
      if (root.isNull()) {
          log->debug(tr("%1 file could not be read").arg(fileName));
          return;
      }

      // First read configuration
      if (root.firstChildElement("configuration") != QDomElement()) { // NOI18N
          QDomNodeList l = root.firstChildElement("configuration").childNodes(); // NOI18N
          log->debug(tr("readFile sees %1 configurations").arg(l.size()));
          for (int i = 0; i < l.size(); i++) {
              QDomElement e = l.at(i).toElement();
              log->debug(tr("Configuration %1 value %2").arg(e.tagName()).arg(e.text()));
              if (e.tagName() == ("storeState")) { // NOI18N
                  manager->setStateStored(e.text()==("yes")); // NOI18N
              }
              if (e.tagName()==("useFastClock")) { // NOI18N
                  manager->setFastClockUsed(e.text()==("yes")); // NOI18N
              }
          }
      }

      // Now read tag information
      if (root.firstChildElement("idtags") != QDomElement()) { // NOI18N
          QDomNodeList l = root.firstChildElement("idtags").elementsByTagName("idtag"); // NOI18N
          log->debug(tr("readFile sees %1 idtags").arg(l.size()));
          for (int i = 0; i < l.size(); i++) {
              QDomElement e = l.at(i).toElement();
              QString systemName = e.firstChildElement("systemName").text(); // NOI18N
              IdTag* t = manager->provideIdTag(systemName);
              t->load(e);
          }
      }
  }

  /*public*/ QString DefaultIdTagManagerXml::getDefaultIdTagFileName() {
      return getFileLocation() + getIdTagDirectoryName() + File::separator + getIdTagFileName();
  }

  /*private*/ /*static*/ /*final*/ QString DefaultIdTagManagerXml::IDTAG_DIRECTORY_NAME = "idtags"; // NOI18N

  /*public*/ QString DefaultIdTagManagerXml::getIdTagDirectoryName() {
     return IDTAG_DIRECTORY_NAME;
  }


  /*public*/ QString DefaultIdTagManagerXml::getIdTagFileName() {
      return QApplication::applicationName() + IDTAG_BASE_FILENAME;
  }

  /**
   * Absolute path to location of IdTag files.
   *
   * @return path to location
   */
   /*public*/ QString DefaultIdTagManagerXml::getFileLocation() {
       return FILE_LOCATION;
   }


   /*private*/ /*final*/ Logger* DefaultIdTagManagerXml::log = LoggerFactory::getLogger("DefaultIdTagManagerXml");
