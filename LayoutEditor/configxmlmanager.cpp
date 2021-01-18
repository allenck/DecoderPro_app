#include "configxmlmanager.h"
#include "fileutil.h"
#include "errormemo.h"
#include "version.h"
#include "reportericonxml.h"
#include "signalheadiconxml.h"
#include "signalheadsignalmastxml.h"
#include "level.h"
#include <QMap>
#include "instancemanager.h"
#include "layoutblockmanager.h"
#include "defaultlogixmanager.h"
#include "abstractconnectionconfig.h"
#include <QMetaType>
#include "jmriuserpreferencesmanager.h"
#include "filehistoryxml.h"
#include "filehistory.h"
#include "defaultcatalogtreemanagerxml.h"
#include "loggerfactory.h"
#include "abstractxmladapter.h"
#include <QUrl>
#include "class.h"
#include "errorhandler.h"
#include "ctc/ctcexception.h"
#include "joptionpane.h"

//#include "classmigrationmanager.h"

/**
 * Define the current schema version string for the layout-config schema.
 * See the <A HREF="package-summary.html#schema">Schema versioning
 * discussion</a>. Also controls the stylesheet file version.
 */
/*static*/ /*final*/const  /*public*/ QString ConfigXmlManager::schemaVersion = "-4-19-2";
/*static*/ ErrorHandler* ConfigXmlManager::handler = new ErrorHandler();
QString ConfigXmlManager::fileLocation = QString("layout")+QDir::separator();


ConfigXmlManager::ConfigXmlManager(QObject *parent) :
    ConfigureManager(parent)
{
 setObjectName("ConfigXmlManager");
 if(log != nullptr)
  log->setDebugEnabled(true);
 plist =  QList<QObject*> ();
 //clist =  QHash<QObject*, int>();
 //clist = Collections.synchronizedMap(new QHash<QObject*, int>());
 clist = QMap<int, QObject*>(); // ACk reversed key & object to result in list of objects sorted by key.
 tlist =  QList<QObject*> ();
 ulist =  QList<QObject*> ();
 uplist =  QList<QObject*> ();
 loadDeferredList =  QMap<int, QDomElement>();
 defaultBackupDirectory = FileUtil::getUserFilesPath()+"backupPanels";
 configXmlMap = QMap<QString, QString>();
 configXmlMap.insert("jmri.jmrix.loconet.hexfile.configurexml.ConnectionConfigXml", "HexFileConnectionConfigXml");
 configXmlMap.insert("jmri.jmrix.loconet.locobuffer.configurexml.ConnectionConfigXml", "LocobufferConnectionConfigXml");
 configXmlMap.insert("jmri.jmrix.loconet.pr3.configurexml.ConnectionConfigXml", "ConnectionConfigXml");
 configXmlMap.insert("jmri.jmrix.loconet.loconetovertcp.configurexml.ConnectionConfigXml", "LnOverTcpConnectionConfig");
 configXmlMap.insert("jmri.jmrix.loconet.pr4.configurexml.ConnectionConfigXml", "PR4ConnectionConfigXml");

 //qRegisterMetaType<DefaultUserMessagePreferences>("DefaultUserMessagePreferences");
 prefsFile = new File("~/.jmri/defaultConfig.xml");

}
ConfigXmlManager::~ConfigXmlManager()
{
 //delete log;
}

/**
 * Provides the mechanisms for storing an entire layout configuration
 * to XML.  "Layout" refers to the hardware:  Specific communcation
 * systems, etc.
 * @see <A HREF="package-summary.html">Package summary for details of the overall structure</A>
 * @author Bob Jacobsen  Copyright (c) 2002, 2008
 * @version $Revision: 22561 $
 */
///*public*/ class ConfigXmlManager extends jmri.jmrit.XmlFile
//    implements jmri.ConfigureManager {


///*public*/ ConfigXmlManager() {
//}

/*public*/ void ConfigXmlManager::registerConfig(QObject* o)
{
 registerConfig(o, 50);
}

/*public*/ void ConfigXmlManager::registerPref(QObject* o)
{
 // skip if already present, leaving in original order
 if (plist.contains(o))
 {
  return;
 }
 if (log != nullptr && log->isDebugEnabled())
 {
  confirmAdapterAvailable(o);
 }
 // and add to list
 plist.append(o);
}

/**
 * Common check routine to confirm
 * an adapter is available as part of
 * registration process. Only enabled when
 * Log4J DEBUG level is selected, to load fewer
 * classes at startup.
 */
void ConfigXmlManager::confirmAdapterAvailable(QObject* o)
{
 if (log != nullptr && log->isDebugEnabled())
 {
  QString adapter = adapterName(o);
  if (log->isDebugEnabled()) log->debug("register "+o->objectName()+" adapter "+adapter);
  if (adapter!=NULL)
   try {
       Class::forName(adapter);
   } catch (ClassNotFoundException ex) {
       locateClassFailed(ex, adapter, o);
   } catch (NoClassDefFoundError ex) {
       locateClassFailed(ex, adapter, o);
   }
 }
}

/**
 * Handles ConfigureXml classes that have moved to a new package or been
 * superceded.
 *
 * @param name name of the moved or superceded ConfigureXml class
 * @return name of the ConfigureXml class in newer package or of superseding
 *         class
 */
/*static*/ /*public*/ QString ConfigXmlManager::currentClassName(QString name) {
    //return InstanceManager::getDefault("ClassMigrationManager").getClassName(name);
 return name;
}

/**
 * Remove the registered preference items.  This is used
 * e.g. when a GUI wants to replace the preferences with new
 * values.
 */
/*public*/ void ConfigXmlManager::removePrefItems()
{
 if (log->isDebugEnabled()) log->debug("removePrefItems dropped "+ QString::number(plist.size()));
 plist.clear();
}

/*public*/ QObject* ConfigXmlManager::findInstance(/*Class<?>*/QString c, int index)
{
 QList<QObject*> temp =  QList<QObject*>(plist);
 //temp.addAll(clist.keys());
 foreach(QObject* obj, clist.values())
  temp.append(obj);
 //temp.addAll(tlist);
 foreach(QObject* obj, tlist)
  temp.append(obj);
 //temp.addAll(ulist);
 foreach(QObject* obj, ulist)
  temp.append(obj);
 //temp.addAll(uplist);
 foreach(QObject* obj, uplist)
  temp.append(obj);
 for (int i=0; i<temp.size(); i++)
 {
  //if (c.isInstance(temp.at(i)))
  //if(temp.at(i)->metaObject()->className() == c)
  if(c == "ConnectionConfig" && qobject_cast<AbstractConnectionConfig*>(temp.at(i))!= NULL)
  {
   if (index-- == 0)
    return temp.at(i);
  }
 }
 return nullptr;
}

/*public*/ QList<QObject*> ConfigXmlManager::getInstanceList(/*Class<?>*/QString c)
{
 QList<QObject*> temp =  QList<QObject*>(plist);
 QList<QObject*> returnlist =  QList<QObject*>();
 //temp.addAll(clist.keySet());
 //foreach(QObject* obj, clist.keys())
 foreach(QObject* obj, clist.values())
  temp.append(obj);
  //temp.addAll(tlist);
 foreach(QObject* obj, tlist)
  temp.append(obj);
 //temp.addAll(ulist);
 foreach(QObject* obj, ulist)
  temp.append(obj);
 //temp.addAll(uplist);
 foreach(QObject* obj, uplist)
  temp.append(obj);
 for (int i=0; i<temp.size(); i++)
 {
  //if (c.isInstance(temp.get(i)))
  QString cn = temp.at(i)->metaObject()->className();
  if((QString(temp.at(i)->metaObject()->className())) == c ||
     (c == "ConnectionConfig" && cn.contains("ConnectionConfig")))
  {
   returnlist.append(temp.at(i));
            //if (index-- == 0) return temp.get(i);
  }
 }
 if(returnlist.isEmpty())
  return QList<QObject*>();
 return returnlist;
}

/*public*/ void ConfigXmlManager::registerConfig(QObject* o, int x)
{
 // skip if already present, leaving in original order
 //if (clist.contains(o)) return;
 if(clist.values().contains(o)) return;

 if (log != nullptr && log->isDebugEnabled()) {
  confirmAdapterAvailable(o);
 }

 // and add to list
 clist.insertMulti(x, o);
}

/*public*/ void ConfigXmlManager::registerTool(QObject* o)
{

 // skip if already present, leaving in original order
 if (tlist.contains(o)) return;

 if (log != nullptr && log->isDebugEnabled()) {
  confirmAdapterAvailable(o);
 }

 // and add to list
 tlist.append(o);
}
/**
 * Register an object whose state is to be tracked.
 * It is not an error if the original object was already registered.
 * @param o The object, which must have an
 *              associated adapter class.
 */
/*public*/ void ConfigXmlManager::registerUser(QObject* o)
{

 // skip if already present, leaving in original order
 if (ulist.contains(o)) return;

 if (log != nullptr && log->isDebugEnabled()) {
  confirmAdapterAvailable(o);
 }

 // and add to list
 ulist.append(o);
}

/*public*/ void ConfigXmlManager::registerUserPrefs(QObject* o)
{

 // skip if already present, leaving in original order
 if (uplist.contains(o)) return;

 if (log != nullptr && log->isDebugEnabled()) {
  confirmAdapterAvailable(o);
 }

 // and add to list
 uplist.append(o);
}

/*public*/ void ConfigXmlManager::deregister(QObject* o)
{

 plist.removeOne(o);
 if(o!=NULL)
 {
  //clist.remove(o);
  QMap<int, QObject*> newClist = QMap<int, QObject*>();
  QMapIterator<int, QObject*> iter(clist);
  while (iter.hasNext())
  {
   iter.next();
   if(iter.value() == o)
    continue;
   newClist.insertMulti(iter.key(), iter.value());
  }
  clist = newClist;
 }
 tlist.removeOne(o);
 ulist.removeOne(o);
 uplist.removeOne(o);
}


/**
 * Find the name of the adapter class for an object.
 * @param o object of a configurable type
 * @return class name of adapter
 */
/*public*/ /*static*/ QString ConfigXmlManager::adapterName(QObject* o)
{
 //QString className = o->objectName();
 QString className = o->metaObject()->className();
 if(className == "LayoutEditor")
  className = "LayoutEditor";
 if(className == "Pr3ConnectionConfig")
  className = "ConnectionConfig";
 if (log != nullptr && log->isDebugEnabled()) log->debug("handle object of class "+className);
 if(o->property("JavaClassName") != QVariant())
 {
  className = o->property("JavaClassName").toString();
 }
 int lastDot = className.lastIndexOf(".");
#if 1 // determine what Java classname shold be; probably set a property
 if (lastDot > 0) {
   // found package-class boundary OK
   QString result = className.mid(0, lastDot)
           + ".configurexml."
           + className.mid(lastDot + 1, className.length())
           + "Xml";
   log->trace(tr("adapter class name is %1").arg(result));
   return result;
 } else {
   // no last dot found!
  if(className.isEmpty())
  {
   log->error("No package name found, which is not yet handled! "+ className);
    return nullptr;
  }
 }
#endif
 QString result = className + "Xml";
 return result;

}

/**
 * Handle failure to load adapter class. Although only a
 * one-liner in this class, it is a separate member to facilitate testing.
 */
void ConfigXmlManager::locateClassFailed(Throwable ex, QString adapterName, QObject* /*o*/) {
    log->warn(ex.getMessage()+" could not load adapter class "+adapterName);
    //if (log->isDebugEnabled()) ex.printStackTrace();
}

/*protected*/ QDomElement ConfigXmlManager::initStore() const
{
 //doc = newDocument(root);
 doc = QDomDocument();

 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);
 xmlProcessingInstruction =  doc.createProcessingInstruction("xml-stylesheet","type=\"text/xsl\" href=\"/xml/XSLT/panelfile" + schemaVersion + ".xsl\"");
 doc.appendChild(xmlProcessingInstruction);
 QDomElement root = doc.createElement("layout-config");
 root.setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
 root.setAttribute("xsi:noNamespaceSchemaLocation","http://jmri.org/xml/schema/layout" + schemaVersion + ".xsd");
 return root;
}
/*protected*/ void ConfigXmlManager::addPrefsStore(QDomElement root)
{
 for (int i=0; i<plist.size(); i++)
 {
  QObject* o = plist.at(i);
  QDomElement e = elementFromObject(o);
  if (!e.isNull())
   root.appendChild(e);
 }
}

//bool compareValue(QObject* o1, QObject* o2)
//{

//}

/*protected*/ bool ConfigXmlManager::addConfigStore(QDomElement root) const
{
 bool result = true;
 //ArrayList<Map.Entry<Object, Integer>> l = new ArrayList<Map.Entry<Object, Integer>>(clist.entrySet());
// QList<QHash<QObject*, int> > l =  QList<QHash<QObject*, int> >();
// QHashIterator<QObject*, int> iter(clist);
// while (iter.hasNext())
// {
//     iter.next();
//  l.append(iter.key, iter.value());
// }

 //Collections.sort(l, new Comparator<Map.Entry<Object, Integer>>(){

//     /*public*/ int compare(Map.Entry<Object, Integer> o1, Map.Entry<Object, Integer> o2) {
//        return o1.compareTo(o2);
//    }});
  QList<QObject*> l = clist.values();
//  qSort(l.begin(), l.end(), compareValue);
  for (int i=0; i<l.size(); i++)
  {
   try
   {
    //QObject* o = l.value(i).key();
    QObject* o = l.at(i);
    QDomElement e = elementFromObject(o);
    if (!e.isNull())
     root.appendChild(e);
  } catch (Exception e) {
      storingErrorEncountered (nullptr, "storing to file", Level::_ERROR,
                                "Unknown error (Exception)", "","",&e);
      result = false;
  }
 }
 return result;
}

/*protected*/ bool ConfigXmlManager::addToolsStore(QDomElement root) const
{
 bool result = true;
 for (int i=0; i<tlist.size(); i++)
 {
  QObject* o = tlist.at(i);
  try
  {
   QDomElement e = elementFromObject(o);
   if (!e.isNull())
    root.appendChild(e);
  }
  catch (Exception* e)
  {
   result = false;
   storingErrorEncountered (((XmlAdapter*)o), "storing to file", Level::_ERROR,
                                      "Unknown error (Exception)", NULL,NULL,e);
  }
 }
 return result;
}

/*protected*/ bool ConfigXmlManager::addUserStore(QDomElement root)const
{
 bool result = true;
 for (int i=0; i<ulist.size(); i++)
 {
  QObject* o = ulist.at(i);
  try
  {
   QDomElement e = elementFromObject(o);
   if (!e.isNull())
    root.appendChild(e);
  }
  catch (Exception e)
  {
   result = false;
   storingErrorEncountered ((XmlAdapter*)o, "storing to file", Level::_ERROR,
                                      "Unknown error (Exception)", NULL,NULL,&e);
  }
 }
 return result;
}

/*protected*/ void ConfigXmlManager::addUserPrefsStore(QDomElement root) const
{
 for (int i=0; i<uplist.size(); i++)
 {
  QObject* o = uplist.at(i);
  QDomElement e = elementFromObject(o);
  if (!e.isNull())
   root.appendChild(e);
 }
}

/*protected*/ void ConfigXmlManager::includeHistory(QDomElement root) const
{
 // add history to end of document
 if (InstanceManager::getDefault("FileHistory") != NULL)
  root.appendChild(FileHistoryXml::storeDirectly((FileHistory*)InstanceManager::getDefault("FileHistory"),doc));
}

/*protected*/ bool ConfigXmlManager::finalStore(QDomElement root, File* file) const
{
 try
 {
  // Document doc = newDocument(root, dtdLocation+"layout-config-"+dtdVersion+".dtd");
  // add XSLT processing instruction
  // <?xml-stylesheet type="text/xsl" href="XSLT/panelfile"+schemaVersion+".xsl"?>
  // java.util.Map<QString,QString> m = new java.util.HashMap<QString,QString>();
  // m.put("type", "text/xsl");
  // m.put("href", xsltLocation+"panelfile"+schemaVersion+".xsl");
  // ProcessingInstruction p = new ProcessingInstruction("xml-stylesheet", m);
  // doc.appendChild(0,p);
  //QDomProcessingInstruction p = doc.createProcessingInstruction("text/xsl", "/xml/XSLT/panelfile-2-9-6.xsl");
  //doc.appendChild(p);
  doc.appendChild(root);
  // add version at front
  storeVersion(root);

  writeXML(new QFile(file->getPath()), doc);
 }
 catch (FileNotFoundException ex3)
 {
  storingErrorEncountered (nullptr, "storing to file "+file->getPath(), Level::_ERROR, "File not found " + file->getPath(), NULL,NULL,&ex3);
  log->error("FileNotFound error writing file: "+ex3.getMessage());
  return false;
 }
 catch (IOException ex2)
 {
  storingErrorEncountered (NULL, "storing to file "+file->getPath(), Level::_ERROR, "IO error writing file " + file->getPath(), NULL,NULL,&ex2);
  log->error("IO error writing file: "+ex2.getMessage());
  return false;
 }
 return true;
}

/**
 * Writes config, tools and user to a file.
 * @param file
 */
/*public*/ bool ConfigXmlManager::storeAll(File* file) const
{

 bool result = true;
 QDomElement root = initStore();
 if(!addConfigStore(root))
 {
  result=false;
 }
 if(!addToolsStore(root))
 {
  result=false;
 }
 if(!addUserStore(root))
 {
  result=false;
 }
 addConfigStore(root);
 addToolsStore(root);
 addUserStore(root);
 includeHistory(root);
 if(!finalStore(root, file))
 {
  result=false;
 }
 return result;
}

/**
 * Writes prefs to a predefined File location.
 */
/*public*/ void ConfigXmlManager::storePrefs()
{
 storePrefs(prefsFile);
}

/*public*/ void ConfigXmlManager::storePrefs(File* file)
{
 QDomElement root = initStore();
 addPrefsStore(root);
 finalStore(root, file);
}

/*public*/ void ConfigXmlManager::storeUserPrefs(File* file)
{
 QDomElement root = initStore();
 addUserPrefsStore(root);
 finalStore(root, file);
}

/**
 * Set location for preferences file.
 * <p>
 * File need not exist,
 * but location must be writable when storePrefs() called.
 */
/*public*/ void ConfigXmlManager::setPrefsLocation(File* prefsFile) { this->prefsFile = prefsFile; }

/**
 * Set location for user preferences file.
 * <p>
 * File need not exist,
 * but location must be writable when storePrefs() called.
 */
/*public void setUserPrefsLocation(File userPrefsFile) { this.userPrefsFile = userPrefsFile; }
File userPrefsFile;*/

/**
 * Writes prefs to a file.
 * @param file
 */
/*public*/ bool ConfigXmlManager::storeConfig(File* file)
{
 bool result = true;
 QDomElement root = initStore();
 if(!addConfigStore(root))
 {
  result=false;
 }
 includeHistory(root);
 if(!finalStore(root, file))
 {
  result=false;
 }
 return result;
}

 /**
 * Writes user and config info to a file.
 * <P>
 * Config is included here because it doesnt hurt to
 * read it again, and the user data (typically a panel)
 * requires it to be present first.
 * @param file
 */
/*public*/ bool ConfigXmlManager::storeUser(File* file)
{
 bool result = true;
 QDomElement root = initStore();
 if(!addConfigStore(root))
 {
  result=false;
 }
 if(!addUserStore(root))
 {
  result=false;
 }
 includeHistory(root);
 if(!finalStore(root, file))
 {
  result=false;
 }
 return result;
}

/*public*/ bool ConfigXmlManager::makeBackup(File* file) const
{
 return makeBackupFile(defaultBackupDirectory, file);
}


/*static*/ /*public*/ QDomElement ConfigXmlManager::elementFromObject(QObject* o)
{
 QString aName = "";
// if(qobject_cast<PositionableLabel*>(o))
// {
//  aName = qobject_cast<PositionableLabel*>(o)->getClassName() + "Xml";
// }
// else
 QString oName = o->objectName();
  aName = QString(o->metaObject()->className()) + "Xml";
 if(QString(o->metaObject()->className()) == "Pr3ConnectionConfig")
  aName = "ConnectionConfigXml";
 log->debug(tr("store %1 using %2").arg(o->metaObject()->className()).arg(aName));
 QObject* adapter = NULL;

 try
 {
  adapter = (XmlAdapter*)Class::forName(/*adapterName(o)*/aName)->newInstance();
 }
 catch (ClassNotFoundException ex1)
 {
  log->error(tr("Cannot load configuration adapter for ")+o->metaObject()->className()+tr(" due to ")+ex1.getMessage());
 }
 catch (IllegalAccessException ex2)
 {
     log->error(tr("Cannot load configuration adapter for ")+o->metaObject()->className()+tr(" due to ")+ex2.getMessage());
 }
 catch (InstantiationException ex3)
 {
     log->error(tr("Cannot load configuration adapter for ")+o->metaObject()->className()+tr(" due to ")+ex3.getMessage());
 }
 if(adapter != NULL && qobject_cast<XmlAdapter*>(adapter) != nullptr )
  return ((XmlAdapter*)adapter)->store(o);

 QString className = o->metaObject()->className();

 {
  log->error(tr("Cannot store configuration for ")+className);
  return QDomElement();
 }
}

/*private*/ void ConfigXmlManager::storeVersion(QDomElement root) const
{
 // add version at front
// root.addContent(0,
 QDomElement e = doc.createElement("jmriversion");
 QDomElement e1;
 e.appendChild(e1=doc.createElement("major"));
 e1.appendChild(doc.createTextNode(QString("%1").arg(Version::major)));
 QDomElement e1a;
 e.appendChild(e1a=doc.createElement("minor"));
 e1a.appendChild(doc.createTextNode(QString("%1").arg(Version::minor)));
 QDomElement e2;
 e.appendChild(e2=doc.createElement("test"));
 e2.appendChild(doc.createTextNode(QString("%1").arg(Version::test)));
 QDomElement e3;
 e.appendChild(e3=doc.createElement("modifier"));
 e3.appendChild(doc.createTextNode(Version::getModifier()));
 //root.appendChild(e);
 root.insertBefore(e, root.firstChild());
}


/**
 * Load a file.
 * <p>
 * Handles problems locally to the extent that it can,
 * by routing them to the creationErrorEncountered
 * method.
 * @return true if no problems during the load
 */
/*public*/ bool ConfigXmlManager::load(File* fi) throw (JmriException)
{
    return load(fi, false);
}
/*public*/ bool ConfigXmlManager::load(QUrl url) throw (JmriConfigureXmlException)
{
    return load(url, false);
}

/**
 * Load a file. <p> Handles problems locally to the extent that it can, by
 * routing them to the creationErrorEncountered method.
 *
 * @param fi file to load
 * @param registerDeferred true to register objects to defer
 * @return true if no problems during the load
 * @throws JmriConfigureXmlException
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 * @since 2.11.2
 */
//@Override
/*public*/ bool ConfigXmlManager::load(File* fi, bool registerDeferred) throw (JmriException)
{
 return this->load(FileUtil::fileToURL(fi), registerDeferred);
}

/**
 * Load a file. <p> Handles problems locally to the extent that it can, by
 * routing them to the creationErrorEncountered method.
 *
 * @param url URL of file to load
 * @param registerDeferred true to register objects to defer
 * @return true if no problems during the load
 * @throws JmriConfigureXmlException
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 * @since 3.3.2
 */
//@SuppressWarnings("unchecked")
//@Override
/*public*/ bool ConfigXmlManager::load(QUrl url, bool registerDeferred) throw (JmriConfigureXmlException)
{
 bool result = true;
 if(log->isDebugEnabled()) log->debug("opening "+url.path());
 QFile file(url.path());
 if(!file.open(QFile::ReadOnly | QFile::Text)) return false;
 if(!doc.setContent(&file))
 {
   file.close();
 }
 file.close();

 QDomElement root = QDomElement();
 /* We will put all the elements into a load list, along with the load order
 As XML files prior to 2.13.1 had no order to the store, beans would be stored/loaded
 before beans that they were dependant upon had been stored/loaded
 */
 //QMap<QDomElement, int> loadlist = Collections.synchronizedMap(new LinkedHashMap<QDomElement, int>());
 //QMap<QDomElement, int> loadlist = QMap<QDomElement, int>();
 QMap<int, QDomElement> loadlist_s = QMap<int, QDomElement>();

 //bool verify = XmlFile::getValidate();
// try
// {
  //root = super.rootFromURL(url);
  XmlFile::setValidate(validate);
  root = doc.documentElement(); // get the root element of the document
  if(root.tagName() != "layout-config")
  {
   int ret = JOptionPane::showOptionDialog(nullptr, "This may not be a valid panel xml file.\nDo you want to continue>", "Warning",
                                           JOptionPane::OK_CANCEL_OPTION, JOptionPane::WARNING_MESSAGE);
   if(ret > 0)
    return false;
  }
  // get the objects to load
  QDomNodeList items = root.childNodes();
  for (int i = 0; i<items.size(); i++)
  {
   //Put things into an ordered list
   QDomElement item = items.at(i).toElement();
   if (item.attribute("class") == "")
   {
    // this is an element that we're not meant to read
    if (log->isDebugEnabled()) log->debug("skipping " + item.tagName());
     continue;
   }
   QString adapterName = item.attribute("class");
   if (log->isDebugEnabled()) log->debug("attempt to get adapter "+adapterName + " for " + item.attribute("name"));
   XmlAdapter* adapter = nullptr;
#if 1
   //adapter = (XmlAdapter*)Class::forName(adapterName)->newInstance();
   QString classname;
   if(configXmlMap.contains(adapterName))
    classname = configXmlMap.value(adapterName);
   else
    classname = adapterName.mid(adapterName.lastIndexOf(".")+1);
   adapter = (XmlAdapter*)Class::forName(classname)->newInstance();
 //  if(adapterName == "jmri.managers.configurexml.DefaultUserMessagePreferencesXml")
 //   adapter = new DefaultUserMessagePreferencesXml();
 //  else
#else
   {
   QString classname;
   if(configXmlMap.contains(adapterName))
    classname = configXmlMap.value(adapterName);
   else
    classname = adapterName.mid(adapterName.lastIndexOf(".")+1);
   int typeId = QMetaType::type(classname.toLocal8Bit());
   if(typeId == 0)
   {
    log->error("ConfigXmlManager: No typeId for " + adapterName);
    continue;
   }
#if QT_VERSION < 0x050000
   adapter = (XmlAdapter*)QMetaType::construct(typeId);
#else
   adapter = (XmlAdapter*)QMetaType::create(typeId);
#endif
   adapter->setObjectName(classname);
   adapter->setProperty("JavaClassName", adapterName);
  }

  if(adapter == nullptr)
  {
   log->error("ConfigXmlManager: Cannot create instance of " + adapterName);
   continue;
  }
#endif
  int order = adapter->loadOrder();
  if (log->isDebugEnabled()) log->debug("add "+ item.tagName() + ": " + adapterName + " to load list with order id of " + QString::number(order));
  //loadlist.insert(item, order);
  loadlist_s.insertMulti(order, item);
 }
#if 0 // not necessary since loadList is a QMap
        ArrayList<Map.Entry<QDomElement, Integer>> l = new ArrayList<Map.Entry<QDomElement, Integer>>(loadlist.entrySet());
        Collections.sort(l, new Comparator<Map.Entry<QDomElement, Integer>>(){

         /*public*/ int compare(Map.Entry<QDomElement, Integer> o1, Map.Entry<QDomElement, Integer> o2) {
            return o1.compareTo(o2);
        }});
#endif
 //for (int i=0; i<l.size(); i++)
 QMapIterator<int, QDomElement> iter(loadlist_s);
 while(iter.hasNext())
 {
  iter.next();
  //QDomElement item = l.get(i).getKey();
  QDomElement item = iter.value();
  QString adapterName = item.attribute("class");
  //log->debug(tr("load adapter: %1").arg(adapterName));
  QString className = adapterName.mid(adapterName.lastIndexOf(".")+1);
  if(className == "ConnectionConfigXml")
  {
   QStringList sl = adapterName.split(".");
   QString prefix;
   if(sl.at(3) == "pr3")
   {
    //prefix = "Pr3";
   }
   else if(sl.at(3) == "hexfile")
    prefix = "HexFile";
   else if(sl.at(3) == "loconetovertcp")
    prefix = "LnOverTcp";
   else if(sl.at(3) == "locobufferusb")
    prefix = "LocobufferUsb";
   else if(sl.at(3) == "locobuffer")
    prefix = "Locobuffer";
   else if(sl.at(3) == "locobufferii")
    prefix = "LocobufferII";
   else if(sl.at(3) == "sprog")
    prefix = "Sprog";
   else if(sl.at(3) == "sprogCS")
    prefix = "SprogCS";
   else if(sl.at(3) == "pr2")
    prefix = "Pr2";
   else if(sl.at(3) == "pr4")
    prefix = "Pr4";
   else if(sl.at(3) == "usb_dcs52")
    prefix = "DCS52";
   else if(sl.at(3) == "usb_dcs240")
    prefix = "DCS240";
   else if(sl.at(3) == "networkdriver")
    prefix = "JMRIClient";

   QString newClassName = prefix+"ConnectionConfigXml";
   if(!prefix.isEmpty())
    adapterName = adapterName.replace("ConnectionConfigXml", newClassName);
   int tId = QMetaType::type(newClassName.toLatin1());
   if(tId == 0)
    log->error(QString("No type id for %1 (%2)").arg(newClassName).arg(adapterName));
  }
  if (log->isDebugEnabled()) log->debug("load " + item.tagName() + " via "+adapterName);
  XmlAdapter* adapter = nullptr;
  try
  {
   //adapter = (XmlAdapter*)Class.forName(adapterName).newInstance();
 //  if(adapterName == "jmri.managers.configurexml.DefaultUserMessagePreferencesXml")
 //   adapter = new DefaultUserMessagePreferencesXml();
 //  else
   {
    QString classname;
    if(configXmlMap.contains(adapterName))
     classname = configXmlMap.value(adapterName);
    else
     classname = adapterName.mid(adapterName.lastIndexOf(".")+1);
    if(classname == "ConnectionConfigXml")
    {
     QStringList sl = adapterName.split(".");
     QString prefix;
     if(sl.at(3) == "pr3")
     {
      //prefix = "Pr3";
     }
     // because the Java classes all use the same name, we have to make these ConnectionConfigXml adapter names unique. ACK
     else if(sl.at(3) == "hexfile")
      prefix = "HexFile";
     else if(sl.at(3) == "loconetovertcp")
      prefix = "LnOverTcp";
     else if(sl.at(3) == "locobufferusb")
      prefix = "LocobufferUsb";
     else if(sl.at(3) == "locobuffer")
      prefix = "Locobuffer";
     else if(sl.at(3) == "locobufferii")
      prefix = "LocobufferII";
     else if(sl.at(3) == "sprog")
      prefix = "Sprog";
     else if(sl.at(3) == "sprogCS")
      prefix = "SprogCS";
      else if(sl.at(3) == "networkdriver")
      prefix = "JMRIClient";
     else if(sl.at(3) == "pr4")
      prefix = "Pr4";
     else if(sl.at(3) == "usb_dcs52")
      prefix = "DCS52";
     else if(sl.at(3) == "usb_dcs240")
      prefix = "DCS240";
      QString newClassName = prefix+"ConnectionConfigXml";
      if(!prefix.isEmpty())
       classname = newClassName;
    }
    try
    {
     adapter = (XmlAdapter*)Class::forName(classname)->newInstance();

     // get version info
     //loadVersion(root, adapter);
     // and do it
     if (adapter->loadDeferred() && registerDeferred)
     {
      // register in the list for deferred load
      loadDeferredList.insert(adapter->loadOrder(), item);
      if (log->isDebugEnabled()) log->debug("deferred load registered for " + item.tagName() + " "  + adapterName);
     }
     else
     {
      bool loadStatus = adapter->load(item, item);
      if (log->isDebugEnabled()) log->debug("load status for " + item.tagName() + " " +adapterName+" is "+(loadStatus?"true":"false"));

      // if any adaptor load fails, then the entire load has failed
      if (!loadStatus)
      {
       result = false;
       log->error("load status for " + item.tagName() + " " +adapterName+" is "+(loadStatus?"true":"false"));
      }
     }
     qApp->processEvents();
    }
    catch (Exception e)
    {
     creationErrorEncountered(adapter, "load(" + url.toString() + ")",
                 "Unexpected error (Exception)", nullptr, nullptr, &e);

         result = false;  // keep going, but return false to signal problem
    }
    catch (Throwable et) {
         creationErrorEncountered(adapter, "in load(" + url.toString() + ")",
                 "Unexpected error (Throwable)", nullptr, nullptr, &et);

         result = false;  // keep going, but return false to signal problem
    }
   }
  }
  catch (IllegalArgumentException e)
  {
    creationErrorEncountered(adapter, "load(" + url.path() + ")",
                        "Unexpected error (IllegalArgumentException)", nullptr, nullptr, &e);
       result = false;  // keep going, but return false to signal problem
  }
  catch (FileNotFoundException e1)
  {
        // this returns false to indicate un-success, but not enough
        // of an error to require a message
        creationErrorEncountered(nullptr, "opening file " + url.path(),
                "File not found", nullptr, nullptr, &e1);
        result = false;
  }
  catch (JDOMException e)
  {
        creationErrorEncountered(nullptr, "parsing file " + url.path(),
                "Parse error", nullptr, nullptr, &e);
        result = false;
  }
  catch (Exception e)
  {
        creationErrorEncountered(nullptr, "loading from file " + url.path(),
                "Unknown error (Exception)", nullptr, nullptr, &e);
        result = false;
  }
  catch (Throwable et)
  {
   creationErrorEncountered(adapter, "in load(" + url.path() + ")",
                       "Unexpected error (Throwable)", nullptr, nullptr, &et);

   result = false;  // keep going, but return false to signal problem
  }
  catch (CTCException e)
  {
        creationErrorEncountered(nullptr, "loading from file " + url.path(),
                "Unknown error (Exception)", nullptr, nullptr, &e);
        result = false;
  }
  /*finally */

  {
        // no matter what, close error reporting
        handler->done();
  }
  // no matter what, close error reporting
  //XmlFile::setValidate(validate);
  handler->done();
 }

    // loading complete, as far as it got, make history entry
 FileHistory* r = (FileHistory*)InstanceManager::getDefault("FileHistory");
 if (r!=nullptr)
 {
  FileHistory* included = nullptr;
  if (!root.isNull())
  {
   qDebug() << "root = " << root.tagName() << " file = " << url.path() << " " << root.firstChild().toElement().tagName();
   QDomElement filehistory = root.firstChildElement("filehistory");
   if (!filehistory.isNull()) {
       included = FileHistoryXml::loadFileHistory(filehistory);
   }
  }
  r->addOperation((result ? "Load OK":"Load with errors"), url.toString(), included);
 } else {
     log->info("Not recording file history");
 }

 return result;
}

//@Override
/*public*/ bool ConfigXmlManager::loadDeferred(File* fi) throw (JmriException){
    return this->loadDeferred(FileUtil::fileToURL(fi));
}

//@Override
/*public*/ bool ConfigXmlManager::loadDeferred(QUrl url/*url*/) throw (JmriConfigureXmlException)
{
 bool result = true;
 // Now process the load-later list
 log->debug("Start processing deferred load list (size): "+QString::number(loadDeferredList.size()));
 if (!loadDeferredList.isEmpty())
 {
  QMapIterator<int, QDomElement> iter(loadDeferredList);

  //foreach(QDomElement item, loadDeferredList)
  while(iter.hasNext())
  {
   QDomElement item = iter.next().value();
   QString adapterName = item.attribute("class");
   log->debug("deferred load via "+adapterName);
   XmlAdapter* adapter = nullptr;
   try
   {
    adapter = (XmlAdapter*)Class::forName(adapterName)->newInstance();
    adapter->setProperty("JavaClassName", adapterName);

    bool loadStatus;
    if(adapter != nullptr)
    {
     loadStatus = adapter->load(item, item);
     log->debug("deferred load status for "+adapterName+" is "+(loadStatus?"true":"false"));
    }
    else
    {
//     creationErrorEncountered(adapter, "deferred load(" + url.path() + ")", Level::_ERROR,
//                                             "Unexpected error (Exception)", NULL, NULL,(Throwable*) e);
     log->error("Unable to load " + adapterName);
     loadStatus = false;
    }
    // if any adaptor load fails, then the entire load has failed
    if (!loadStatus)
     result = false;
   }
   catch (Exception e)
   {
    creationErrorEncountered(adapter, "deferred load(" + url.path() + ")",
                                         "Unexpected error (Exception)", NULL, NULL, &e);
    result = false;  // keep going, but return false to signal problem
   }
   catch (Throwable et)
   {
    creationErrorEncountered(adapter, "in deferred load(" + url.path() + ")",
                        "Unexpected error (Throwable)", NULL, NULL, &et);
    result = false;  // keep going, but return false to signal problem
   }
  }
 }
 log->debug(QString("Done processing deferred load list with result: ")+(result?"true":"false"));
 return result;
}


/**
 * Find a file by looking
 * <UL>
 * <LI> in xml/layout/ in the preferences directory, if that exists
 * <LI> in xml/layout/ in the application directory, if that exists
 * <LI> in xml/ in the preferences directory, if that exists
 * <LI> in xml/ in the application directory, if that exists
 * <LI> at top level in the application directory
 * <LI>
 * </ul>
 * @param f Local filename, perhaps without path information
 * @return Corresponding File object
 */
//@Override
/*public*/ QUrl ConfigXmlManager::find(QString f) {
    QStringList sList;
    sList << "xml/layout"<< "xml";
    QUrl u = FileUtil::findURL(f, sList); // NOI18N
    if (u.isEmpty()) {
        this->locateFileFailed(f);
    }
    return u;
}

/**
 * Report a failure to find a file.  This is a separate member
 * to ease testing.
 * @param f Name of file not located.
 */
void ConfigXmlManager::locateFileFailed(QString f) {
    log->warn("Could not locate file "+f);
}

/**
 * Invoke common handling of errors that
 * happen during the "load" process.
 * <p>
 * Generally, this is invoked by {@link XmlAdapter}
 * implementations of their creationErrorEncountered()
 * method (note different arguemments, though). The
 * standard implemenation of that is in {@link AbstractXmlAdapter}.
 * <p>
 * Exceptions passed into this are absorbed.
 *
 * @param adapter Object that encountered the error (for reporting),
 *                  may be NULL
 * @param operation description of the operation being attempted,
 *                  may be NULL
 * @param description description of error encountered
 * @param systemName System name of bean being handled, may be NULL
 * @param userName used name of the bean being handled, may be NULL
 * @param exception Any exception being handled in the processing, may be NULL
 */
/*static*/ /*public*/ void ConfigXmlManager::creationErrorEncountered (
            XmlAdapter* adapter,
            QString operation,
            QString description,
            QString systemName,
            QString userName,
            Throwable* exception)
{
    // format and log a message (note reordered from arguments)
    ErrorMemo* e = new ErrorMemo(
                        adapter, operation, description,
                        systemName, userName, exception, "loading");

    handler->handle(e);
}

/**
 * Invoke common handling of errors that
 * happen during the "store" process.
 * <p>
 * Generally, this is invoked by {@link XmlAdapter}
 * implementations of their creationErrorEncountered()
 * method (note different arguemments, though). The
 * standard implemenation of that is in {@link AbstractXmlAdapter}.
 * <p>
 * Exceptions passed into this are absorbed.
 *
 * @param adapter Object that encountered the error (for reporting),
 *                  may be NULL
 * @param operation description of the operation being attempted,
 *                  may be NULL
 * @param description description of error encountered
 * @param systemName System name of bean being handled, may be NULL
 * @param userName used name of the bean being handled, may be NULL
 * @param exception Any exception being handled in the processing, may be NULL
 */

/*static*/ /*public*/ void ConfigXmlManager::storingErrorEncountered (
            XmlAdapter* adapter,
            QString operation,
            Level* /*level*/,
            QString description,
            QString systemName,
            QString userName,
            Throwable* exception)
{
    // format and log a message (note reordered from arguments)
    ErrorMemo* e = new ErrorMemo(
                        adapter, operation, description,
                        systemName, userName, exception, "storing");

    handler->handle(e);
}

/*static*/ /*public*/ void ConfigXmlManager::setErrorHandler(ErrorHandler* handler) { ConfigXmlManager::handler = handler; }

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* ConfigXmlManager::log = LoggerFactory::getLogger("ConfigXmlManager");

/**
 * @return the loadDeferredList
 */
/*protected*/ QList<QDomElement> ConfigXmlManager::getLoadDeferredList() {
    return loadDeferredList.values();
}
