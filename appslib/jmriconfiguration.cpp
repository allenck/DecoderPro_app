#include "jmriconfiguration.h"
#include "file.h"
#include "logger.h"
#include <QFile>
#include <QTextStream>
#include "jmriconfigurationprovider.h"
#include "fileutil.h"

/**
 *
 * @author Randall Wood
 */
///*abstract*/ class JmriConfiguration implements AuxiliaryConfiguration {

    ///*private*/ /*final*/ Logger log = LoggerFactory.getLogger(JmriConfiguration.class);

    JmriConfiguration::JmriConfiguration() : AuxiliaryConfiguration() {
     log = new Logger("JmriConfiguration");
    }

    /*protected*/ /*abstract*/ File* JmriConfiguration::getConfigurationFile(bool shared) {return NULL;}

    /*protected*/ /*abstract*/ bool JmriConfiguration::isSharedBackedUp() {return false;}

    /*protected*/ /*abstract*/ void JmriConfiguration::setSharedBackedUp(bool backedUp) {}

    /*protected*/ /*abstract*/ bool JmriConfiguration::isPrivateBackedUp() {return false;}

    /*protected*/ /*abstract*/ void JmriConfiguration::setPrivateBackedUp(bool backedUp) {}

    //@Override
    /*public*/ QDomElement JmriConfiguration::getConfigurationFragment(/*final*/ QString elementName, /*final*/ QString _namespace, /*final*/ bool shared)
    {
        /*synchronized (this) {*/
            File* file = this->getConfigurationFile(shared);
            if (file != NULL && file->canRead())
            {
             QFile* qFile = new QFile(file->getPath());
             if(qFile->open(QIODevice::ReadOnly))
             {
              QTextStream* stream = new QTextStream(qFile);

//                try {
//                    try (/*final*/ InputStream is = new FileInputStream(file)) {
//                        InputSource input = new InputSource(is);
//                        input.setSystemId(file.toURI().toURL().toString());
//                        Element root = XMLUtil.parse(input, false, true, NULL, NULL).getDocumentElement();
//                        return XMLUtil.findElement(root, elementName, namespace);
//                    }
//                } catch (IOException | SAXException | IllegalArgumentException ex) {
//                    log->warn("Cannot parse {}", file, ex);
//                }
              QDomDocument doc =  QDomDocument(stream->readAll());
              return doc.firstChild().toElement();
            }
     }
     return QDomElement();
    }

    //@Override
    /*public*/ void JmriConfiguration::putConfigurationFragment(/*final*/ QDomElement fragment, /*final*/ bool shared) //throws IllegalArgumentException
    {
        /*synchronized (this) {*/
            QString elementName = fragment.tagName();
            QString _namespace = fragment.namespaceURI();
            if (_namespace == NULL) {
                //throw new IllegalArgumentException();
             log->error("Invalid namespace");
             return;
            }
            File* file = this->getConfigurationFile(shared);
            QDomDocument doc;
            if (file != NULL && file->canRead())
            {
             QFile* qFile = new QFile(file->getPath());
             if(qFile->open(QIODevice::ReadOnly))
             {
              QTextStream* stream = new QTextStream(qFile);
//                try {
//                    try (/*final*/ InputStream is = new FileInputStream(file)) {
//                        InputSource input = new InputSource(is);
//                        input.setSystemId(file.toURI().toURL().toString());
//                        doc = XMLUtil.parse(input, false, true, NULL, NULL);
//                    }
//                } catch (IOException | SAXException ex) {
//                    log->warn("Cannot parse {}", file, ex);
//                }
              QDomDocument* doc = new QDomDocument(stream->readAll());
            QDomElement root;
            if (doc == NULL) {
                //doc = XMLUtil.createDocument("auxiliary-configuration", JmriConfigurationProvider::NAMESPACE, NULL, NULL); // NOI18N
             doc = new QDomDocument();
             root = doc->createElement("auxiliary-configuration");
            }
            //QDomElement root = doc.getDocumentElement();
#if 0
            QDomElement oldFragment = XMLUtil.findElement(root, elementName, _namespace);
            if (oldFragment != NULL) {
                root.removeChild(oldFragment);
            }
            Node ref = NULL;
            NodeList list = root.getChildNodes();
            for (int i = 0; i < list.getLength(); i++) {
                Node node = list.item(i);
                if (node.getNodeType() != Node.ELEMENT_NODE) {
                    continue;
                }
                int comparison = node.getNodeName().compareTo(elementName);
                if (comparison == 0) {
                    comparison = node.getNamespaceURI().compareTo(namespace);
                }
                if (comparison > 0) {
                    ref = node;
                    break;
                }
            }
            root.insertBefore(root.getOwnerDocument().importNode(fragment, true), ref);
            try {
                this->backup(shared);
                try (/*final*/ OutputStream os = new FileOutputStream(file)) {
                    XMLUtil.write(doc, os, "UTF-8"); // NOI18N
                }
            } catch (IOException ex) {
                log->error("Cannot write {}", file, ex);
            }
#endif
             }
        }
    }

    //@Override
    /*public*/ bool JmriConfiguration::removeConfigurationFragment(/*final*/ QString elementName, /*final*/ QString _namespace, /*final*/ bool shared) //throws IllegalArgumentException
    {
#if 0
        /*synchronized (this)*/ {
            File* file = this->getConfigurationFile(shared);
            if (file->canWrite()) {
                try {
                    Document doc;
                    try (/*final*/ InputStream is = new FileInputStream(file)) {
                        InputSource input = new InputSource(is);
                        input.setSystemId(file.toURI().toURL().toString());
                        doc = XMLUtil.parse(input, false, true, NULL, NULL);
                    }
                    QDomElement root = doc.getDocumentElement();
                    QDomElement toRemove = XMLUtil.findElement(root, elementName, namespace);
                    if (toRemove != NULL) {
                        root.removeChild(toRemove);
                        this->backup(shared);
                        if (root.getElementsByTagName("*").getLength() > 0) {
                            // NOI18N
                            try (/*final*/ OutputStream os = new FileOutputStream(file)) {
                                XMLUtil.write(doc, os, "UTF-8"); // NOI18N
                            }
                        } else if (!file.delete()) {
                            log->debug("Unable to delete {}", file);
                        }
                        return true;
                    }
                } catch (IOException | SAXException | DOMException ex) {
                    log->error(tr("Cannot remove %1 from %2").arg(elementName).arg(file, ex));
                }
            }
            return false;
        }
#endif
    }

    /*private*/ void JmriConfiguration::backup(bool shared) {
        /*final*/ File* file = this->getConfigurationFile(shared);
        if (!(shared ? this->isSharedBackedUp() : this->isPrivateBackedUp()) && file->exists())
        {
            log->debug(tr("Backing up %1").arg(file->toString()));
//            try {
                FileUtil::backup(file);
                if (shared) {
                    this->setSharedBackedUp(true);
                } else {
                    this->setPrivateBackedUp(true);
                }
//            } catch (IOException ex) {
//                log->error(tr("Error backing up %1").arg(file/*, ex*/));
//            }
        }
    }
