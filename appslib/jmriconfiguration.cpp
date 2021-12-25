#include "jmriconfiguration.h"
#include "file.h"
#include "logger.h"
#include <QFile>
#include <QTextStream>
#include "jmriconfigurationprovider.h"
#include "fileutil.h"
#include "xmlutil.h"

/**
 *
 * @author Randall Wood
 */
///*abstract*/ class JmriConfiguration implements AuxiliaryConfiguration {

///*private*/ /*final*/ Logger log = LoggerFactory.getLogger(JmriConfiguration.class);

JmriConfiguration::JmriConfiguration() : AuxiliaryConfiguration() {
 log = new Logger("JmriConfiguration");
}

/*protected*/ /*abstract*/ File* JmriConfiguration::getConfigurationFile(bool /*shared*/) {return NULL;}

/*protected*/ /*abstract*/ bool JmriConfiguration::isSharedBackedUp() {return false;}

/*protected*/ /*abstract*/ void JmriConfiguration::setSharedBackedUp(bool /*backedUp*/) {}

/*protected*/ /*abstract*/ bool JmriConfiguration::isPrivateBackedUp() {return false;}

/*protected*/ /*abstract*/ void JmriConfiguration::setPrivateBackedUp(bool /*backedUp*/) {}

//@Override
/*public*/ QDomElement JmriConfiguration::getConfigurationFragment(/*final*/ QString elementName, /*final*/ QString /*_namespace*/, /*final*/ bool shared)
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
//                } catch (IOException* | SAXException | IllegalArgumentException ex) {
//                    log->warn("Cannot parse {}", file, ex);
//                }
   QDomDocument doc;// =  QDomDocument(stream->readAll());
   QString content = stream->readAll();
   doc.setContent(content);
   log->debug(tr("first element = %1").arg(doc.documentElement().tagName()));
   QDomElement root = doc.documentElement();
   QDomNodeList nl = root.childNodes();
   for(int i = nl.count()-1; i >= 0; i--)
   {
    if(nl.at(i).isComment())
    {
     root.removeChild(nl.at(i));
    }
   }
   // TODO: consider namespace
   QDomElement element =  root.firstChildElement(elementName);
   log->debug(tr("selected element = %1").arg(element.tagName()));
   return element;
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
 if (_namespace == NULL)
 {
     //throw new IllegalArgumentException();
  log->error("Invalid namespace");
  return;
 }
 File* file = this->getConfigurationFile(shared);
 doc = QDomDocument();
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
//                } catch (IOException* | SAXException ex) {
//                    log->warn("Cannot parse {}", file, ex);
//                }
   //QDomDocument* doc = new QDomDocument(stream->readAll());
   QString content = stream->readAll();
   if(!content.isEmpty())
    doc.setContent(content);
  }
 }
 QDomElement root;
 if (doc.documentElement().isNull())
 {
    //doc = XMLUtil.createDocument("auxiliary-configuration", JmriConfigurationProvider::NAMESPACE, NULL, NULL); // NOI18N
   doc =  QDomDocument();
   QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
   doc.appendChild(xmlProcessingInstruction);

   root = doc.createElement("auxiliary-configuration");

   doc.appendChild(root);
   if(shared)
    root.appendChild(doc.createComment("Shared preferences"));
   else
    root.appendChild(doc.createComment("Per-Node preferences"));
 }
 else
  root = doc.documentElement();

 QString sXml = doc.toString();

 QDomElement oldFragment = XMLUtil::findElement(root, elementName, _namespace);
 if (oldFragment != QDomElement())
 {
  //root.removeChild(oldFragment);
  root.replaceChild(fragment,oldFragment);
 }
  sXml = doc.toString();
 QDomElement ref;// = NULL;
 QDomNodeList list = root.childNodes();
 for (int i = 0; i < list.length(); i++)
 {
  QDomNode node = list.at(i);
  if (!node.isElement())
  {
      continue;
  }
  int comparison = node.toElement().tagName() == (elementName);
  if (comparison == 0)
  {
      comparison = node.toElement().namespaceURI() == (_namespace);
  }
  if (comparison > 0)
  {
      ref = node.toElement();
      break;
  }
 }

 //root.insertBefore(root.getOwnerDocument().importNode(fragment, true), ref);
 root.insertBefore(fragment, ref);
 //root.insertAfter(root.ownerDocument().importNode(fragment,true), ref);
 try
 {
  this->backup(shared);
  //try (/*final*/ OutputStream os = new FileOutputStream(file)) {
  QFile* qFile = new QFile(file->getPath());
  if(qFile->open(QIODevice::WriteOnly))
  {
     QTextStream* os = new QTextStream(qFile);
     XMLUtil::write(doc, os, "UTF-8"); // NOI18N
  }
//      }
 }
 catch (IOException* ex)
 {
  log->error(tr("Cannot write %1").arg(file->getPath()));
//  }
 }
}


//@Override
/*public*/ bool JmriConfiguration::removeConfigurationFragment(/*final*/ QString elementName, /*final*/ QString _namespace, /*final*/ bool shared) //throws IllegalArgumentException
{
#if 1
//    /*synchronized (this)*/ {
  File* file = this->getConfigurationFile(shared);
  if (file->canWrite())
  {
   try
   {
       //QDomDocument doc;
    //try (/*final*/ InputStream is = new FileInputStream(file)) {
    QFile* ff = new QFile(file->getPath());
    if(ff->open(QIODevice::ReadOnly))
    {
     //InputSource input = new InputSource(is);
     QTextStream* input = new QTextStream(ff);
     //input.setSystemId(file.toURI().toURL().toString());
     //doc = XMLUtil::parse(input, false, true, NULL, NULL);
     doc = QDomDocument();
     doc.setContent(input->readAll());
     ff->close();
    }
    QDomElement root = doc.documentElement();
    QDomElement toRemove = XMLUtil::findElement(root, elementName, _namespace);
    if (toRemove != QDomElement())
    {
     root.removeChild(toRemove);
     this->backup(shared);
     if (root.elementsByTagName("*").length() > 0)
     {
         // NOI18N
      //try (/*final*/ OutputStream os = new FileOutputStream(file)) {
      QFile* ff = new QFile(file->getPath());
      if(ff->open(QIODevice::WriteOnly))
      {
       //InputSource input = new InputSource(is);
       QTextStream* os = new QTextStream(ff);

       XMLUtil::write(doc, os, "UTF-8"); // NOI18N
      }
     } else if (!file->_delete())
     {
      log->debug(tr("Unable to delete %1").arg(file->toString()));
     }
     return true;
    }
   }
   catch (IOException* ex) //| SAXException | DOMException ex)
   {
    log->error(tr("Cannot remove %1 from %2").arg(elementName).arg(file->toString()).arg(ex->getMessage()));
   }
  }
#endif
 return false;
}

/*private*/ void JmriConfiguration::backup(bool shared)
{
 /*final*/ File* file = this->getConfigurationFile(shared);
 if (!(shared ? this->isSharedBackedUp() : this->isPrivateBackedUp()) && file->exists())
 {
  log->debug(tr("Backing up %1").arg(file->toString()));
  try
  {
   FileUtil::backup(file);
   if (shared) {
       this->setSharedBackedUp(true);
   } else {
       this->setPrivateBackedUp(true);
   }
  } catch (IOException* ex) {
   log->error(tr("Error backing up %1").arg(file->toString()/*, ex*/));
  }
 }
}
