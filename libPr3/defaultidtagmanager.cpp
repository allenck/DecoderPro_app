#include "defaultidtagmanager.h"
#include "instancemanager.h"
#include "defaultidtag.h"
#include "idtagmanager.h"
#include "fileutil.h"
#include "defaultshutdownmanager.h"

/*private*/ /*static*/ bool DefaultIdTagManager::_initialised = false;
/*private*/ /*static*/ bool DefaultIdTagManager::_loading = false;
/*private*/ /*static*/ bool DefaultIdTagManager::_storeState = false;
/*private*/ /*static*/ bool DefaultIdTagManager::_useFastClock = false;

QString IdTagManagerXml::idTagDirectoryName = "idtags";
/*private*/ QString IdTagManagerXml::idTagBaseFileName = "IdTags.xml"; // NOI18N
QString IdTagManagerXml::fileLocation = FileUtil::getUserFilesPath();
bool IdTagManagerXml::_loaded = false;
IdTagManagerXml* IdTagManagerXml::_instance = NULL;


DefaultIdTagManager::DefaultIdTagManager(QObject *parent) :
    IdTagManager(parent)
{
 log = new Logger(this->metaObject()->className());
 log->setDebugEnabled(true);
 registerSelf();
}

/**
 * Concrete implementation for the Internal {@link jmri.IdTagManager} interface.
 * @author      Bob Jacobsen    Copyright (C) 2010
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 22539 $
 * @since       2.11.4
 */
///*public*/ class DefaultIdTagManager extends AbstractManager
//    implements IdTagManager {


///*public*/ DefaultIdTagManager() {
//    super();
//}

//@Override
/*public*/ int DefaultIdTagManager::getXMLOrder(){
    return Manager::IDTAGS;
}

//@Override
/*public*/ bool DefaultIdTagManager::isInitialised() {
    return _initialised;
}

//@Override
/*public*/ void DefaultIdTagManager::init()
{
 log->debug("init called");
 if (!_initialised && !_loading )
 {
  log->debug("Initialising");
  // Load when created
  _loading = true;
  IdTagManagerXml::instance()->load();
  _loading = false;

  // Create shutdown task to save
  log->debug("Register ShutDown task");
//  InstanceManager::shutDownManagerInstance().Register(new AbstractShutDownTask("Writing IdTags");
//  { // NOI18N
//            //@Override
//            /*public*/ bool execute() {
//                // Save IdTag details prior to exit, if necessary
//                log->debug("Start writing IdTag details...");
//                try {
//                    ((DefaultIdTagManager)InstanceManager.getDefault(IdTagManager.class)).writeIdTagDetails();
//                    //new jmri.managers.DefaultIdTagManager().writeIdTagDetails();
//                }
//                catch (java.io.IOException ioe) { log->error("Exception writing IdTags: "+ioe); }

//                // continue shutdown
//                return true;
//            }
//  });
  ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(new DefaultIdTagShutdownTask("Writing IdTags", this));
  _initialised = true;
 }
}

/**
 * Don't want to store this information
 */
//@Override
/*protected*/ void DefaultIdTagManager::registerSelf() {}

//@Override
/*public*/ char DefaultIdTagManager::typeLetter() { return 'D'; }

//@Override
/*public*/ QString DefaultIdTagManager::getSystemPrefix() { return "I"; }

//@Override
/*public*/ IdTag* DefaultIdTagManager::provideIdTag(QString name) {
    if (!_initialised && !_loading) init();
    IdTag* t = getIdTag(name);
    if (t!=NULL) return t;
    if (name.startsWith(getSystemPrefix()+typeLetter()))
        return newIdTag(name, NULL);
    else
        return newIdTag(makeSystemName(name), NULL);
}

//@Override
/*public*/ IdTag* DefaultIdTagManager::getIdTag(QString name) {
    if (!_initialised && !_loading) init();

    IdTag* t = getBySystemName(makeSystemName(name));
    if (t!=NULL) return t;

    t = getByUserName(name);
    if (t!=NULL) return t;

    return getBySystemName(name);
}

//@Override
/*public*/ IdTag* DefaultIdTagManager::getBySystemName(QString name) {
    if (!_initialised && !_loading) init();
    return (IdTag*)_tsys->value(name);
}

//@Override
/*public*/ IdTag* DefaultIdTagManager::getByUserName(QString key) {
    if (!_initialised && !_loading) init();
    return (IdTag*)_tuser->value(key);
}

//@Override
/*public*/ IdTag* DefaultIdTagManager::getByTagID(QString tagID) {
    if (!_initialised && !_loading) init();
    return getBySystemName(makeSystemName(tagID));
}

/*protected*/ IdTag* DefaultIdTagManager::createNewIdTag(QString systemName, QString userName) {
    // we've decided to enforce that IdTag system
    // names start with ID by prepending if not present
    if (!systemName.startsWith("ID")) // NOI18N
        systemName = "ID"+systemName; // NOI18N
    return (IdTag*)new DefaultIdTag(systemName, userName);
}

//@Override
/*public*/ IdTag* DefaultIdTagManager::newIdTag(QString systemName, QString userName)
{
 if (!_initialised && !_loading) init();
 if (log->isDebugEnabled()) log->debug("new IdTag:" +( (systemName==NULL) ? "NULL" : systemName)   // NOI18N
   +";"+( (userName==NULL) ? "NULL" : userName)); // NOI18N
 if (systemName == NULL)
 {
  log->error("SystemName cannot be NULL. UserName was "
                 +( (userName==NULL) ? "NULL" : userName)); // NOI18N
        throw new IllegalArgumentException("SystemName cannot be NULL. UserName was "
                +( (userName==NULL) ? "NULL" : userName));
 }
 // return existing if there is one
 IdTag* s;
 if ( (userName!=NULL) && ((s = getByUserName(userName)) != NULL))
 {
  if (getBySystemName(systemName)!=s)
   log->error("inconsistent user ("+userName+") and system name ("+systemName+") results; userName related to ("+s->getSystemName()+")");
  return s;
 }
 if ( (s = getBySystemName(systemName)) != NULL)
 {
  if ((s->getUserName() == NULL) && (userName != NULL))
    s->setUserName(userName);
  else if (userName != NULL) log->warn("Found IdTag via system name ("+systemName +") with non-NULL user name ("+userName+")"); // NOI18N
  return s;
 }

 // doesn't exist, make a new one
 s = createNewIdTag(systemName, userName);

 // save in the maps
 Register(s);

 emit newIdTagCreated((IdTag*)s);

 // if that failed, blame it on the input arguements
 if (s == NULL) throw new IllegalArgumentException();

 return s;
}

//@Override
/*public*/ void DefaultIdTagManager::Register(NamedBean* s)
{
 //super.register(s);
 AbstractManager::Register(s);
 IdTagManagerXml::instance()->setDirty(true);
}

//@Override
/*public*/ void DefaultIdTagManager::deregister(NamedBean* s){
    //super.deregister(s);
    AbstractManager::deregister(s);
    IdTagManagerXml::instance()->setDirty(true);
}

//@Override
/*public*/ void DefaultIdTagManager::propertyChange(PropertyChangeEvent* e) {
    //super.propertyChange(e);
    AbstractManager::propertyChange(e);
    IdTagManagerXml::instance()->setDirty(true);
}

/*public*/ void DefaultIdTagManager::writeIdTagDetails()  //throw (IOException)
{
    IdTagManagerXml::instance()->store();
    log->debug("...done writing IdTag details");
}

//@Override
/*public*/ void DefaultIdTagManager::setStateStored(bool state)
{
 if (state!=_storeState)
 {
  IdTagManagerXml::instance()->setDirty(true);
 }
 _storeState = state;
}

//@Override
/*public*/ bool DefaultIdTagManager::isStateStored()
{
 return _storeState;
}

//@Override
/*public*/ void DefaultIdTagManager::setFastClockUsed(bool fastClock)
{
 if (fastClock != _useFastClock)
 {
  IdTagManagerXml::instance()->setDirty(true);
 }
 _useFastClock = fastClock;
}

//@Override
/*public*/ bool DefaultIdTagManager::isFastClockUsed() {
    return _useFastClock;
}

//@Override
/*public*/ QList<IdTag*>* DefaultIdTagManager::getTagsForReporter(Reporter* reporter, long threshold)
{
 QList<IdTag*>* out = new QList<IdTag*>();
 QDateTime lastWhenLastSeen = QDateTime();

 // First create a list of all tags seen by specified reporter
 // and record the time most recently seen
 foreach (NamedBean* n, _tsys->values() )
 {
  IdTag* t = (IdTag*) n;
  if (t->getWhereLastSeen() == reporter)
  {
   out->append(t);
   if (t->getWhenLastSeen().currentDateTime() >(lastWhenLastSeen.currentDateTime()))
   {
    lastWhenLastSeen = t->getWhenLastSeen();
   }
  }
 }

 if (out->size()>0)
 {
  // Calculate the threshold time based on the most recently seen tag
  QDateTime* thresholdTime = new QDateTime(lastWhenLastSeen.currentDateTime().addMSecs(-threshold));

  // Now remove from the list all tags seen prior to the threshold time
  //for (IdTag* t: out) {
  for(int i=out->count()-1; i >=0; i --)
  {
   IdTag* t = out->at(i);
   if (((AbstractIdTag*)t)->getWhenLastSeen().currentDateTime() < (thresholdTime->currentDateTime()))
   {
    out->removeAt(i);
   }
  }
 }
 return out;
}

/**
 * Concrete implementation of abstract {@link jmri.jmrit.XmlFile} for internal use
 */
//static class IdTagManagerXml extends XmlFile {


/*public*/ /*static*/ /*synchronized*/ IdTagManagerXml* IdTagManagerXml::instance()
{
    //QMutexLocker locker(&mutex);
    if (_instance == NULL) {
        //if (log->isDebugEnabled()) log->debug("IdTagManagerXml creating instance");

        // Create instance and load
        _instance = new IdTagManagerXml();
        _instance->load();
    }
    return _instance;
}

/*public*/ /*synchronized*/ void IdTagManagerXml::setDirty(bool dirty)
{
  QMutexLocker locker(&mutex);

  _dirty = dirty;
  if (log->isDebugEnabled()) log->debug(tr("Set dirty to ") + (_dirty?"True":"False"));
}

/*protected*/ void IdTagManagerXml::load()
{
 if (!_loaded)
 {
  if(log == NULL) log = new Logger("IdTagManagerXml");
  log->debug("Loading...");
  try
  {
   readFile(getDefaultIdTagFileName());
   _loaded = true;
   setDirty(false);
  }
  catch (Exception ex)
  {
   log->error("Exception during IdTag file reading: " + ex.getMessage());
  }
 }
}

/*protected*/ void IdTagManagerXml::store() //throw (IOException)
{
 if (_dirty)
 {
  log->debug("Storing...");
  log->debug("Using file: " + getDefaultIdTagFileName());
  QFile* file = createFile(getDefaultIdTagFileName(), true);
  Q_UNUSED(file);
  try {
   writeFile(getDefaultIdTagFileName());
  }
  catch (FileNotFoundException ex)
  {
   log->error(tr("File not found while writing IdTag file, may not be complete: ") + ex.getMessage());
  }
 }
 else
 {
  log->debug("Not dirty - no need to store");
 }
}

/*private*/ QFile* IdTagManagerXml::createFile(QString fileName, bool backup)
{
 if (backup) makeBackupFile(fileName);

 QFileInfo* fileInfo;
 QFile* file;
 try
 {
  if (!checkFile(fileName))
  {
   // The file does not exist, create it before writing
   fileInfo =  new QFileInfo(fileName);
//   QFile parentDir = file->getParentFile();
//   if (!parentDir.exists())
//   {
//    if (!parentDir.mkdir())
//     log->error("Directory wasn't created");
//   }
   QString filePath = fileInfo->absolutePath();
   QDir parentDir = QDir(filePath);
   if(!parentDir.exists())
   {
    if(!parentDir.mkpath(filePath))
     log->error("Directory wasn't created");
   }
   //if (file.createNewFile())
   file =new QFile(fileName);
   if(file->open(QIODevice::WriteOnly))
     log->debug("New file created");
  }
  else
  {
   file = new QFile(fileName);
   file->open(QIODevice::WriteOnly);
  }
 }
 catch (IOException ex)
 {
  log->error("Exception while creating IdTag file, may not be complete: " + ex.getMessage());
 }
 return file;
}

/*private*/ void IdTagManagerXml::writeFile(QString fileName) //throw (FileNotFoundException)
{
 if(log->isDebugEnabled()) log->debug("writeFile "+fileName);
 // This is taken in large part from "Java and XML" page 368
 QDomDocument doc;// = QDomDocument("IdTags");
 QFile* file = findFile(fileName);
 if (file == NULL)
 {
  file = new QFile(fileName);
 }
 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
doc.appendChild(xmlProcessingInstruction); xmlProcessingInstruction =  doc.createProcessingInstruction("xml-stylesheet","type=\"text/xsl\" href=\"/xml/XSLT/panelfile-2-9-6.xsl\"");
doc.appendChild(xmlProcessingInstruction);

// Create root element
QDomElement root = doc.createElement("idtagtable");              // NOI18N
//    root.setAttribute("noNamespaceSchemaLocation",         // NOI18N
//            "http://jmri.org/xml/schema/idtags.xsd",       // NOI18N
//            org.jdom.Namespace.getNamespace("xsi",         // NOI18N
//            "http://www.w3.org/2001/XMLSchema-instance")); // NOI18N
    //Document doc = newDocument(root);
root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
root.setAttribute("xsi:noNamespaceSchemaLocation","http://jmri.org/xml/schema/idtags.xsd");
doc.appendChild(root);

    // add XSLT processing instruction
//    java.util.Map<QString, QString> m = new java.util.HashMap<QString, QString>();
//    m.put("type", "text/xsl");                                                // NOI18N
//    m.put("href", xsltLocation+"idtags.xsl");                                 // NOI18N
//    ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m); // NOI18N
//    doc.addContent(0,p);

 DefaultIdTagManager* manager = (DefaultIdTagManager*)InstanceManager::getDefault("DefaultIdTagManager");
 QDomElement values;
 QDomElement v1;
 // Store configuration
 root.appendChild(values = doc.createElement("configuration"));                                          // NOI18N
    values.appendChild(v1 = doc.createElement("storeState"));
    v1.appendChild(doc.createTextNode(manager->isStateStored()?"yes":"no"));     // NOI18N
    values.appendChild(v1 = doc.createElement("useFastClock"));
    v1.appendChild(doc.createTextNode(manager->isFastClockUsed()?"yes":"no")); // NOI18N

   // Loop through RfidTags
   root.appendChild(values = doc.createElement("idtags")); // NOI18N
   QStringList idTagList = manager->getSystemNameList();
   for (int i=0; i<idTagList.size(); i++)
   {
    IdTag* t = manager->getBySystemName(idTagList.at(i));
    if (log->isDebugEnabled()) log->debug("Writing IdTag: " + t->getSystemName());
        values.appendChild(((DefaultIdTag*)t)->store(doc, manager->isStateStored()));
    }
    writeXML(file, doc);
}

/*private*/ void IdTagManagerXml::readFile(QString fileName) //throw (JDOMException)
{
 // Check file exists
 if (findFile(fileName) == NULL)
 {
  log->debug(fileName + " file could not be found");
  return;
 }

 // Find root
 QDomElement root = rootFromName(fileName);
 if (root.isNull())
 {
  log->debug(fileName + " file could not be read");
        return;
 }

 DefaultIdTagManager* manager = (DefaultIdTagManager*)InstanceManager::getDefault("IdTagManager");

 // First read configuration
 if (!root.firstChildElement("configuration").isNull())
 { // NOI18N
  //@SuppressWarnings("unchecked"
  QDomNodeList l = root.firstChildElement("configuration").childNodes(); // NOI18N
  /*if (log->isDebugEnabled())*/ log->debug("readFile sees " + QString("%1").arg(l.size()) + " configurations");
  for (int i=0; i<l.size(); i++)
  {
   QDomElement e = l.at(i).toElement();
   /*if (log->isDebugEnabled()) */log->debug("Configuration " + e.tagName() + " value " + e.text());
   if (e.tagName()==("storeState"))
   { // NOI18N
    manager->setStateStored(e.text()==("yes")?true:false); // NOI18N
   }
   if (e.tagName()==("useFastClock"))
   { // NOI18N
    manager->setFastClockUsed(e.text()==("yes")?true:false); // NOI18N
   }
  }
 }

 // Now read tag information
 if (!root.firstChildElement("idtags") .isNull())
 { // NOI18N
  //@SuppressWarnings("unchecked")
  QDomNodeList l = root.firstChildElement("idtags").elementsByTagName("idtag"); // NOI18N
  if (log->isDebugEnabled()) log->debug("readFile sees " + QString("%1").arg(l.size()) + " idtags");
  for (int i=0; i<l.size(); i++)
  {
   QDomElement e = l.at(i).toElement();
   QString systemName = e.firstChildElement("systemName").text(); // NOI18N
   IdTag* t = manager->provideIdTag(systemName);
   ((DefaultIdTag*)t)->load(e);
  }
 }
}

/*public*/ QString IdTagManagerXml::getDefaultIdTagFileName()
{
 return getFileLocation()+getIdTagDirectoryName()+QDir::separator()+getIdTagFileName();
}


/*public*/ QString IdTagManagerXml::getIdTagDirectoryName() {
    return idTagDirectoryName;
}


/*public*/ QString IdTagManagerXml::getIdTagFileName() {
    //return /*Application.getApplicationName()+*/idTagBaseFileName;
    // TODO: Use actual program name.
    return "DecoderPro"+idTagBaseFileName;
}

/**
 * Absolute path to location of IdTag files.
 * @return path to location
 */
/*public*/ /*static*/ QString IdTagManagerXml::getFileLocation() {
    return fileLocation;
}


//        /*private*/ static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultIdTagManager.IdTagManagerXml.class.getName());

//    }

//    /*private*/ static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultIdTagManager.class.getName());

//}
