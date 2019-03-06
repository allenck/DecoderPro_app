#include "blockmanagerxml.h"
#include "blockmanager.h"
#include "abstractreporter.h"
#include "instancemanager.h"
#include "level.h"
#include "path.h"

BlockManagerXml::BlockManagerXml(QObject *parent) :
    AbstractMemoryManagerConfigXML(parent)
{
 log = new Logger("BlockManagerXml");
 setObjectName("BlockManagerXml");
}

BlockManagerXml::~BlockManagerXml()
{
 delete log;
}
/**
 * Persistency implementation for BlockManager persistance.
 * <P>
 * The Block objects are not yet read in, pending a reliable write out!
 * <p>
 * Every block is written twice.  First, the list of blocks is written
 * without contents, so that we're sure they're all created on read-back.
 * Then, they're written out again with contents, including the block references
 * in the path elements.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2008
 * @version $Revision: 20521 $
 * @since 2.1.2
 *
 */
///*public*/ class BlockManagerXml extends jmri.managers.configurexml.AbstractMemoryManagerConfigXML {

///*public*/ BlockManagerXml() {
//}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param memories The top-level element being created
 */
/*public*/ void BlockManagerXml::setStoreElementClass(QDomElement memories) {
    memories.setAttribute("class","jmri.configurexml.BlockManagerXml");
}

/**
 * Store the contents of a BlockManager.
 *
 * @param o Object to store, of type BlockManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement BlockManagerXml::store(QObject* o)
{
 QDomElement blocks = doc.createElement("blocks");
 setStoreElementClass(blocks);
 BlockManager* tm = (BlockManager*) o;
 if (tm!=NULL)
 {
  QStringListIterator iter( tm->getSystemNameList());

  // don't return an element if there are not blocks to include
  if (!iter.hasNext()) return QDomElement();
  QDomElement e1;
  blocks.appendChild(e1=doc.createElement("defaultspeed"));
  e1.appendChild(doc.createTextNode(tm->getDefaultSpeed()));
  // write out first set of blocks without contents
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==NULL) log->error("System name NULL during store");
   Block* b = tm->getBySystemName(sname);
   // the following NULL check is to catch a NULL pointer exception that sometimes was found to happen
   if (b==NULL) log->error("Null block during store - sname = "+sname);
   QDomElement elem = doc.createElement("block");
   elem.setAttribute("systemName", sname);
   QDomElement e2;
   elem.appendChild(e2 =doc.createElement("systemName"));
   e2.appendChild(doc.createTextNode(sname));
   // the following NULL check is to catch a NULL pointer exception that sometimes was found to happen
   if( (b!=NULL) && (b->getUserName()!="") && (b->getUserName()!=("")))
   {
    QDomElement e3;
    elem.appendChild(e3 = doc.createElement("userName"));
    e3.appendChild(doc.createTextNode(b->getUserName()));
   }
   if (log->isDebugEnabled()) log->debug("initial store Block "+sname);

   // and put this element out
   blocks.appendChild(elem);
  }

  // write out again with contents
  iter = QStringListIterator(tm->getSystemNameList());
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname==NULL) log->error("System name NULL during store");
   Block* b = tm->getBySystemName(sname);
   // the following NULL check is to catch a NULL pointer exception that sometimes was found to happen
   if (b==NULL)
   {
    log->error("Null Block during store - second store skipped for this block - "+sname);
   }
   else
   {
    QString uname = b->getUserName();
    if (uname==NULL) uname = "";
    QDomElement elem = doc.createElement("block");
    elem.setAttribute("systemName", sname);
    QDomElement e1;
    elem.appendChild(e1 = doc.createElement("systemName"));
    e1.appendChild(doc.createTextNode(sname));
    if (log->isDebugEnabled()) log->debug("second store Block "+sname+":"+uname);
    // store length and curvature attributes
    elem.setAttribute("length", b->getLengthMm());
    elem.setAttribute("curve", b->getCurvature());
    // store common parts
    storeCommon(b, elem);

    if((b->getBlockSpeed()!="") && (b->getBlockSpeed()!=("")) && !b->getBlockSpeed().contains("Global"))
    {
     QDomElement e2;
     elem.appendChild(e2=doc.createElement("speed"));
     e2.appendChild(doc.createTextNode(b->getBlockSpeed()));
    }
    QString perm = "no";
    if (b->getPermissiveWorking())
     perm = "yes";
    QDomElement e3;
    elem.appendChild(e3=doc.createElement("permissive"));
    e3.appendChild(doc.createTextNode(perm));
    // Add content. First, the sensor.
    if (b->getNamedSensor()!=NULL)
    {
     QDomElement e4;
     elem.appendChild(e4=doc.createElement("occupancysensor"));
     e4.appendChild(doc.createTextNode(b->getNamedSensor()->getName()));
    }

    if(b->getDeniedBlocks()->size()>0)
    {
     QDomElement denied = doc.createElement("deniedBlocks");
     foreach(QString deniedBlock,  *b->getDeniedBlocks())
     {
      QDomElement e5;
      denied.appendChild(e5=doc.createElement("block"));
      e5.appendChild(doc.createTextNode(deniedBlock));
     }
     elem.appendChild(denied);
    }

    // Now the Reporter
    Reporter* r = b->getReporter();
    if (r!=NULL)
    {
     QDomElement re = doc.createElement("reporter");
     re.setAttribute("systemName", ((AbstractReporter*)r)->getSystemName());
     re.setAttribute("useCurrent", b->isReportingCurrent()?"yes":"no");
     elem.appendChild(re);
    }

    if(tm->savePathInfo())
    {
     // then the paths
     QVector<Path*>* paths = b->getPaths();
     for (int i=0; i<paths->size(); i++)
      addPath(elem, paths->at(i));
     // and put this element out
    }
    blocks.appendChild(elem);
   }
  }
 }
 return blocks;
}

void BlockManagerXml::addPath(QDomElement e, Path* p)
{
 // for now, persist two directions and a bean setting
 QDomElement pe = doc.createElement("path");
 pe.setAttribute("todir", p->getToBlockDirection());
 pe.setAttribute("fromdir",p->getFromBlockDirection());
 if (p->getBlock()!=NULL)
  pe.setAttribute("block", p->getBlock()->getSystemName());
 QList<BeanSetting*> l = p->getSettings();
 if (!l.isEmpty())
 {
  for (int i=0; i<l.size(); i++)
  {
   addBeanSetting(pe, l.at(i));
  }
 }
 e.appendChild(pe);
}
void BlockManagerXml::addBeanSetting(QDomElement e, BeanSetting* bs)
{
 if (bs->getBean() == NULL)
 {
  log->error("Invalid BeanSetting - did not save");
  return;
 }
 // persist bean name, type and value
 QDomElement bse = doc.createElement("beansetting");
 // for now, assume turnout
 bse.setAttribute("setting", bs->getSetting());
 QDomElement be = doc.createElement("turnout");
 be.setAttribute("systemName", bs->getBeanName());
 bse.appendChild(be);
 e.appendChild(bse);
}

/**
 * Load Blocks into the existing BlockManager.
 * <p>
 * The BlockManager in the InstanceManager is created automatically.
 *
 * @param blocks QDomElement containing the block elements to load.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool BlockManagerXml::load(QDomElement blocks) throw (JmriConfigureXmlException)
{
 bool result = true;
 try
 {
  if (!blocks.firstChildElement("defaultspeed").isNull())
  {
   QString speed = blocks.firstChildElement("defaultspeed").text();
   if (speed!="")
   {
    InstanceManager::blockManagerInstance()->setDefaultSpeed(speed);
   }
  }
 }
 catch (JmriException ex)
 {
  log->error(ex.getMessage());
 }

 QDomNodeList list = blocks.elementsByTagName("block");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(list.size())+" objects");
 //BlockManager tm = InstanceManager.blockManagerInstance();

 for (int i=0; i<list.size(); i++)
 {
  QDomElement block = list.at(i).toElement();
  loadBlock(block);
 }
 return result;
}

/**
 * Utility method to load the individual Block objects.
 *
 * @param element QDomElement holding one block
 */
//@SuppressWarnings("unchecked")
/*public*/ void BlockManagerXml::loadBlock(QDomElement element) throw (JmriConfigureXmlException)
{
 if (element.attribute("systemName") == NULL)
 {
  log->warn("unexpected NULL in systemName "+element.tagName()+" "/*+QString::number(element.attributes())*/);
  return;
 }
 QString sysName = getSystemName(element);
 QString userName = getUserName(element);
 if (log->isDebugEnabled()) log->debug("defined Block: ("+sysName+")("+(userName==NULL?"<NULL>":userName)+")");

 Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(sysName);
 if (block==NULL)
 { // create it if doesn't exist
    ((BlockManager*)InstanceManager::getDefault("BlockManager"))->createNewBlock(sysName, userName);
    block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(sysName);
 }
 if (block==NULL){
    log->error("Unable to load block with system name " + sysName + " and username of " +(userName==NULL?"<NULL>":userName));
    return;
 }
 if (userName!="") block->setUserName(userName);
 if (element.attribute("length") != "") {
    // load length in millimeters
    block->setLength(element.attribute("length").toFloat());
 }
 if (element.attribute("curve") != "") {
    // load curve attribute
    block->setCurvature(element.attribute("curve").toInt());
 }
 try
 {
    block->setBlockSpeed("Global");
    if (!element.firstChildElement("speed").isNull())
    {
        QString speed = element.firstChildElement("speed").text();
        if (speed!=""  && !speed.contains("Global")){
            block->setBlockSpeed(speed);
        }
    }
 } catch (JmriException ex)
 {
    log->error(ex.getMessage());
 }
 if(!element.firstChildElement("permissive").isNull()){
    bool permissive = false;
    if (element.firstChildElement("permissive").text()==("yes"))
        permissive = true;
    block->setPermissiveWorking(permissive);
 }
 QDomElement deniedBlocks = element.firstChildElement("deniedBlocks");
 if(!deniedBlocks.isNull()){
    QDomNodeList denyBlock = deniedBlocks.elementsByTagName("block");
    for(int i=0; i < denyBlock.size(); i++)
    {
     QDomElement deny = denyBlock.at(i).toElement();
     block->addBlockDenyList(deny.text());
    }
 }
 // load common parts
 loadCommon(block, element);

 // load sensor if present
 QDomNodeList sensors = element.elementsByTagName("sensor");
 if (sensors.size()>1) log->error("More than one sensor present: "+QString::number(sensors.size()));
 if (sensors.size()==1)
 {
  //Old method of saving sensors
     if(sensors.at(0).toElement().attribute("systemName")!=""){
        QString name = sensors.at(0).toElement().attribute("systemName");
        if (name!=(""))
            block->setSensor(name);
    }
 }
 if(!element.firstChildElement("occupancysensor").isNull()){
    QString name = element.firstChildElement("occupancysensor").text();
    if(name!=(""))
        block->setSensor(name);
 }

 // load Reporter if present
 QDomNodeList reporters = element.elementsByTagName("reporter");
 if (reporters.size()>1) log->error("More than one reporter present: "+QString::number(reporters.size()));
 if (reporters.size()==1) {
    // Reporter
    QString name = reporters.at(0).toElement().attribute("systemName");
    Reporter* reporter = InstanceManager::reporterManagerInstance()->provideReporter(name);
    block->setReporter(reporter);
    block->setReportingCurrent(reporters.at(0).toElement().attribute("useCurrent")==("yes"));
 }

 // load paths if present
 QDomNodeList paths = element.elementsByTagName("path");
 if (paths.size()>0 && block->getPaths()->size()>0)
    log->warn("Adding "+QString::number(paths.size())+" paths to block "+sysName+" that already has "+QString::number(block->getPaths()->size())+" blocks. Please report this as an error.");
 for (int i=0; i<paths.size(); i++) {
    QDomElement path = paths.at(i).toElement();
    loadPath(block, path);
 }
}

/**
 * Load path into an existing Block.
 *
 * @param block Block to receive path
 * @param element QDomElement containing path information
 */
//@SuppressWarnings("unchecked")
/*public*/ void BlockManagerXml::loadPath(Block* block, QDomElement element) throw (JmriConfigureXmlException)
{
 // load individual path
 int toDir = 0;
 int fromDir = 0;
 try {
        toDir = element.attribute("todir").toInt();
        fromDir = element.attribute("fromdir").toInt();
    } catch (DataConversionException e) {
        log->error("Could not parse path attribute");
    } catch (NullPointerException e) {
        creationErrorEncountered (
                                    "Block Path entry in file missing required attribute",
                                    block->getSystemName(),block->getUserName(),NULL);
    }

    Block* toBlock = NULL;
    if (!element.attribute("block").isNull()) {
        QString name = element.attribute("block");
        toBlock = InstanceManager::blockManagerInstance()->getBlock(name);
    }
    Path* path = new Path(toBlock, toDir, fromDir);

    QDomNodeList settings = element.elementsByTagName("beansetting");
    for (int i=0; i<settings.size(); i++) {
        QDomElement setting = settings.at(i).toElement();
        loadBeanSetting(path, setting);
    }

    block->addPath(path);
}

/**
 * Load BeanSetting into an existing Path.
 *
 * @param path Path to receive BeanSetting
 * @param element QDomElement containing beansetting information
 */
//@SuppressWarnings("unchecked")
/*public*/ void BlockManagerXml::loadBeanSetting(Path* path, QDomElement element) {
    int setting = 0;
    try {
        setting = element.attribute("setting").toInt();
    } catch (DataConversionException e) {
        log->error("Could not parse beansetting attribute");
    }
    QDomNodeList turnouts = element.elementsByTagName("turnout");
    if (turnouts.size()!=1) log->error("invalid number of turnout element children");
    QString name = turnouts.at(0).toElement().attribute("systemName");
    Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);

    BeanSetting* bs = new BeanSetting(t, name, setting);
    path->addSetting(bs);
}

/*public*/ int BlockManagerXml::loadOrder(){
    return InstanceManager::blockManagerInstance()->getXMLOrder();
}
