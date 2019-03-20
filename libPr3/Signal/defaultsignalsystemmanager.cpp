#include "defaultsignalsystemmanager.h"
#include "fileutil.h"
#include <QFile>
#include <QDir>
#include "defaultsignalsystem.h"
#include <QtXml>

//DefaultSignalSystemManager::DefaultSignalSystemManager(QObject *parent) :
//    AbstractManager(parent)
//{
//}
/**
 * Default implementation of a SignalSystemManager.
 * <P>
 * This loads automatically the first time used.
 * <p>
 *
 *
 * @author  Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 22547 $
 */
///*public*/ class DefaultSignalSystemManager extends AbstractManager
//    implements SignalSystemManager, java.beans.PropertyChangeListener {

/*public*/ DefaultSignalSystemManager::DefaultSignalSystemManager(QObject *parent)
    : SignalSystemManager(parent)
{
    //super();
    log = new Logger("DefaultSignalSystemManager");
    registerSelf();
    // load when created, which will generally
    // be the first time referenced
    load();
}

/*public*/ int DefaultSignalSystemManager::getXMLOrder(){
    return 65400;
}

/**
 * Don't want to store this information
 */
//@Override
/*protected*/ void DefaultSignalSystemManager::registerSelf() {}

/*public*/ QString DefaultSignalSystemManager::getSystemPrefix() { return "I"; }
/*public*/ char DefaultSignalSystemManager::typeLetter() { return 'F'; }

/*public*/ SignalSystem* DefaultSignalSystemManager::getSystem(QString name) {
    SignalSystem* t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

/*public*/ SignalSystem* DefaultSignalSystemManager::getBySystemName(QString key) {
    return (SignalSystem*)_tsys->value(key);
}

/*public*/ SignalSystem* DefaultSignalSystemManager::getByUserName(QString key) {
    return (SignalSystem*)_tuser->value(key);
}

void DefaultSignalSystemManager::load() {
    QStringList* list = getListOfNames();
    for (int i = 0; i < list->size(); i++) {
        SignalSystem* s = makeBean(list->at(i));
        Register(s);
    }
}
QStringList* DefaultSignalSystemManager::getListOfNames()
{
 QStringList* retval = new QStringList();
 // first locate the signal system directory
 // and get names of systems

 //First get the default pre-configured signalling systems
 QDir* signalDir = new QDir(FileUtil::getProgramPath()+ QString("xml")+QDir::separator()+"signals");
 QStringList files = signalDir->entryList();
 for (int i=0; i<files.count(); i++)
 {
  if (!QFileInfo(files.at(i)).isFile())
  {
   // check that there's an aspects.xml file
   QString path = signalDir->absolutePath()+QDir::separator()+files.at(i)+QDir::separator()+"aspects.xml";
   QFile* aspects = new QFile(path);
   if (aspects->exists())
   {
    if( log->isDebugEnabled()) log->debug("found system: "+files.at(i));
    retval->append(files.at(i));
   }
  }
 }
 //Now get the user defined systems.
 signalDir = new QDir(FileUtil::getUserFilesPath()
                      +"resources"+QDir::separator()+"signals");
 if(!signalDir->exists()){
  log->info("User signal resource directory has not been created");
  if(!signalDir->mkpath(signalDir->absolutePath()))
   log->error("Unable to create signal resource directory: " +signalDir->absolutePath());
 }
 files = signalDir->entryList();
 if(!files.isEmpty())
 {
  for (int i=0; i<files.count(); i++)
  {
   if (!QFileInfo(files.at(i)).isFile())
   {
    // check that there's an aspects.xml file
    QString path = signalDir->absolutePath()+QDir::separator()+files.at(i)+QDir::separator()+"aspects.xml";
    QFile* aspects = new QFile(path);;
    if ((aspects->exists()) && (!retval->contains(files.at(i)))) {
     if( log->isDebugEnabled()) log->debug("found system: "+files.at(i));
     retval->append(files.at(i));
    }
   }
  }
 }
 return retval;
}

SignalSystem* DefaultSignalSystemManager::makeBean(QString name) {

 //First check to see if the bean is in the default system directory
 QString filename = FileUtil::getProgramPath()+QString("xml")+QDir::separator()+"signals"
   +QDir::separator()+name
   +QDir::separator()+"aspects.xml";
 if( log->isDebugEnabled())log->debug("load from "+filename);
 XmlFile* xf = new AspectFile();
 QFile* file = new QFile(filename);
 if(file->exists()){
  try {
   QDomElement root = xf->rootFromName(filename);
   DefaultSignalSystem* s = new DefaultSignalSystem(name);
   loadBean(s, root);
   return s;
  } catch (Exception e) {
   log->error("Could not parse aspect file \""+filename+"\" due to: "+e.getMessage());
  }
 }

 //if the file doesn't exist or fails the load from the default location then try the user directory
 filename = FileUtil::getUserFilesPath()+"resources"
   +QDir::separator()+"signals"
   +QDir::separator()+name
   +QDir::separator()+"aspects.xml";
 if( log->isDebugEnabled()) log->debug("load from "+filename);
 file = new QFile(filename);
 if(file->exists()){
  xf = new AspectFile();
  try {
   QDomElement root = xf->rootFromName(filename);
   DefaultSignalSystem* s = new DefaultSignalSystem(name);
   loadBean(s, root);
   return s;
  } catch (Exception e) {
   log->error("Could not parse aspect file \""+filename+"\" due to: "+e.getMessage());
  }
 }

 return NULL;
}

void DefaultSignalSystemManager::loadBean(DefaultSignalSystem* s, QDomElement root) {
 //@SuppressWarnings("unchecked")
 QDomNodeList l = root.firstChildElement("aspects").elementsByTagName("aspect");

 // set user name from system name element
 s->setUserName(root.firstChildElement("name").text());

 // find all aspects, include them by name,
 // add all other sub-elements as key/value pairs
 for (int i = 0; i < l.size(); i++) {
  QString name = l.at(i).toElement().firstChildElement("name").text();
  if (log->isDebugEnabled())log->debug("aspect name "+name);

  //@SuppressWarnings("unchecked")
  QDomNodeList c = l.at(i).childNodes();

  for (int j = 0; j < c.size(); j++) {
   // note: includes setting name; redundant, but needed
   s->setProperty(name, c.at(j).toElement().tagName(), c.at(j).toElement().text());
  }
 }

 if(!root.firstChildElement("imagetypes").isNull()){
  //@SuppressWarnings("unchecked")
  QDomNodeList t = root.firstChildElement("imagetypes").elementsByTagName("imagetype");
  for(int i = 0;i<t.size();i++){
   QString type = t.at(i).toElement().attribute("type");
   s->setImageType(type);
  }
 }
}


//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultSignalSystemManager.class.getName());
//}

/* @(#)DefaultSignalSystemManager.java */
