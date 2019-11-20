#include "oblockmanagerxml.h"
#include "opath.h"
#include "portal.h"
#include "oblock.h"
#include "instancemanager.h"
#include "oblockmanager.h"
#include "portalmanager.h"
#include "warranttableaction.h"

OBlockManagerXml::OBlockManagerXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("OBlockManagerXml");
 log->setDebugEnabled(true);
 setObjectName("OBlockManagerXml");
}
/**
 * Provides the abstract base and store functionality for
 * configuring the CatalogTreeManager.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement catalogTree)
 * class, relying on implementation here to load the individual CatalogTree objects.
 *
 * @author Pete Cressman Copyright: Copyright (c) 2009
 *
 */
///*public*/ class OBlockManagerXml // extends XmlFile
//                    extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ OBlockManagerXml() {
//    }

/**
 * Store the contents of a OBlockManager.
 *
 * @param o Object to store, of type BlockManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement OBlockManagerXml::store(QObject* o) {
    QDomElement blocks = doc.createElement("oblocks");
    blocks.setAttribute("class","jmri.jmrit.logix.configurexml.OBlockManagerXml");
    OBlockManager* manager = (OBlockManager*) o;
    QStringListIterator iter( manager->getSystemNameList());
    while (iter.hasNext()) {
        QString sname = iter.next();
        OBlock* block = manager->getBySystemName(sname);
        QString uname = block->getUserName();
        if (log->isDebugEnabled())
            log->debug("OBlock: sysName= "+sname+", userName= "+uname);
        QDomElement elem = doc.createElement("oblock");
        elem.setAttribute("systemName", sname);
        if (uname==NULL) uname = "";
        elem.setAttribute("userName", uname);
        QString comment = block->getComment();
        if (comment != NULL) {
            QDomElement c = doc.createElement("comment");
            c.appendChild(doc.createTextNode(comment));
            elem.appendChild(c);
        }
        elem.setAttribute("length", block->getLengthMm());
        elem.setAttribute("units", block->isMetric() ? "true" : "false");
        elem.setAttribute("curve", block->getCurvature());
        if (block->getNamedSensor()!=NULL) {
            QDomElement se = doc.createElement("sensor");
            se.setAttribute("systemName", block->getNamedSensor()->getName());
            elem.appendChild(se);
        }
        if (block->getNamedErrorSensor()!=NULL) {
            QDomElement se = doc.createElement("errorSensor");
            se.setAttribute("systemName", block->getNamedErrorSensor()->getName());
            elem.appendChild(se);
        }
        if (block->getReporter() != NULL)
        {
         QDomElement se = doc.createElement("reporter");
         se.setAttribute("systemName", block->getReporter()->getSystemName());
         se.setAttribute("reportCurrent", block->isReportingCurrent() ? "true" : "false");
         elem.appendChild(se);
        }
        elem.setAttribute("permissive", block->getPermissiveWorking() ? "true" : "false");
        elem.setAttribute("speedNotch", block->getBlockSpeed());

        QVector<Path*>* paths = block->getPaths();
        for (int j=0; j<paths->size(); j++) {
            elem.appendChild(storePath((OPath*)paths->at(j)));
        }
        QList <Portal*> portals = block->getPortals();
        for (int i=0; i<portals.size(); i++) {
            elem.appendChild(storePortal(portals.at(i)));
        }
        // and put this element out
        blocks.appendChild(elem);
    }

    return blocks;
}

QDomElement OBlockManagerXml::storePortal(Portal* portal)
{
 QDomElement elem = doc.createElement("portal");
 elem.setAttribute("systemName", portal->getSystemName());
 elem.setAttribute("portalName", portal->getName());
 OBlock* block = portal->getFromBlock();
 if (block!=NULL)
 {
  QDomElement fromElem = doc.createElement("fromBlock");
  fromElem.setAttribute("blockName", block->getSystemName());
  QList <OPath*>* paths = portal->getFromPaths();
  if (paths!=NULL)
  {
   for (int i=0; i<paths->size(); i++)
   {
    OPath* path = paths->at(i);
    fromElem.appendChild(storePathKey(path));
   }
  }
  elem.appendChild(fromElem);
 }
 else
 {
  log->error("Portal \""+portal->getName()+"\" has no fromBlock!");
 }
 NamedBean* signal = portal->getFromSignal();
 if (signal!=NULL)
 {
  QDomElement fromElem = doc.createElement("fromSignal");
  fromElem.setAttribute("signalName", signal->getSystemName());
  fromElem.setAttribute("signalDelay", QString::number(portal->getFromSignalOffset()));
  elem.appendChild(fromElem);
 }
 block = portal->getToBlock();
 if (block!=NULL)
 {
  QDomElement toElem = doc.createElement("toBlock");
  toElem.setAttribute("blockName", block->getSystemName());
  QList <OPath*>* paths = portal->getToPaths();
  if (paths!=NULL)
  {
   for (int i=0; i<paths->size(); i++)
   {
    OPath* path = paths->at(i);
    toElem.appendChild(storePathKey(path));
   }
  }
  elem.appendChild(toElem);
 }
 else
 {
  log->error("Portal \""+portal->getName()+"\" has no toBlock!");
 }
 signal = portal->getToSignal();
 if (signal!=NULL)
 {
  QDomElement toElem = doc.createElement("toSignal");
  toElem.setAttribute("signalName", signal->getSystemName());
  toElem.setAttribute("signalDelay", QString::number(portal->getToSignalOffset()));
  elem.appendChild(toElem);
 }
 return elem;
}

/**
* Key is sufficient to mark the Portal's knowledge of the path.
* Full path info will get loaded from the HashMap
*/
QDomElement OBlockManagerXml::storePathKey(OPath* path) {
    QDomElement elem = doc.createElement("path");
    elem.setAttribute("pathName", path->getName());
    elem.setAttribute("blockName", path->getBlock()->getSystemName());
    return elem;
}

QDomElement OBlockManagerXml::storePath(OPath* path) {
    QDomElement elem = doc.createElement("path");
    elem.setAttribute("pathName", path->getName());
    elem.setAttribute("blockName", path->getBlock()->getSystemName());
    Portal* portal = path->getFromPortal();
    if (portal != NULL) {
        elem.setAttribute("fromPortal", portal->getName());
    }
    portal = path->getToPortal();
    if (portal != NULL) {
        elem.setAttribute("toPortal", portal->getName());
    }
    QList <BeanSetting*> list = path->getSettings();
    for (int i=0; i<list.size(); i++) {
        BeanSetting* bs = list.at(i);
        QDomElement e = doc.createElement("setting");
        //Turnout to = (Turnout)bs.getBean();
        e.setAttribute("turnout", bs->getBeanName());
        e.setAttribute("set", bs->getSetting());
        elem.appendChild(e);
    }
    elem.setAttribute("fromDirection", path->getFromBlockDirection());
    elem.setAttribute("toDirection", path->getToBlockDirection());
    elem.setAttribute("length", path->getLengthMm());
    return elem;
}


OBlock* OBlockManagerXml::getBlock(QString sysName)
{
 OBlock* block = _blockMap->value(sysName);
 if (block == NULL)
 {
  block = _manager->provideOBlock(sysName);
  if (block == NULL)
  {
   block = _manager->createNewOBlock(sysName, NULL);
   if (log->isDebugEnabled()) log->debug("create OBlock: ("+sysName+")");
  }
  else
  {
   _blockMap->insert(sysName, block);
  }
 }
 return block;
}

Portal* OBlockManagerXml::getPortal(QString name)
{
 Portal* portal = _portalMgr->providePortal(name);
 if (portal == NULL)
 {
  portal = _portalMgr->createNewPortal(NULL, name);
  if (log->isDebugEnabled())
  {
   log->debug("create Portal: (" + portal->getSystemName() + ", " + name + ")");
  }
 }
 return portal;
}

OPath* OBlockManagerXml::getPath(OBlock* block, QString name)
{
 QString key = block->getSystemName()+name;
 OPath* path = _pathMap->value(key);
 if (path == NULL)
 {
  path = new OPath(block, name);
  _pathMap->insert(key, path);
  if (log->isDebugEnabled()) log->debug("create OPath: ("+name+") in block ("+block->getSystemName()+")");
 }
 return path;
}

/**
 * Create a OBlock object of the correct class, then
 * register and fill it.
 * @param blocks Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool OBlockManagerXml::load(QDomElement blocks) throw (Exception)
{
 _blockMap = new QMap <QString, OBlock*>();
 _pathMap = new QMap <QString, OPath*>();
 _portalMap = new QMap <QString, Portal*>();
 _manager = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
 _portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
  QDomNodeList blockList = blocks.elementsByTagName("oblock");
  if (log->isDebugEnabled())
  {
   log->debug("Found " + QString::number(blockList.size()) + " OBlock objects");
  }
  for (int i = 0; i < blockList.size(); i++)
  {
   loadBlock(blockList.at(i).toElement());
  }
  // Build data structure for blocks to know with whom they share turnouts.
  // check whether any turnouts are shared between two blocks;
  QStringList sysNames = _manager->getSystemNameArray();
  for (int i = 0; i < sysNames.length(); i++)
  {
   WarrantTableAction::checkSharedTurnouts(_manager->getOBlock(sysNames[i]));
  }
  return true;
}

/*public*/ void OBlockManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("load called. Invalid method.");
}

void OBlockManagerXml::loadBlock(QDomElement elem)
{
 if (elem.attribute("systemName") == NULL)
 {
  log->error("unexpected NULL in systemName " + elem.tagName() + " " /*+ elem.attributes()*/);
  return;
 }
 QString sysName = elem.attribute("systemName");
 QString userName = NULL;
 if (elem.attribute("userName") != NULL)
 {
  userName = elem.attribute("userName");
 }
 if (log->isDebugEnabled())
 {
  log->debug("Load block sysName= " + sysName + " userName= " + userName);
 }
 // Portal may have already created a skeleton of this block
 OBlock* block = getBlock(sysName);
 if (block == NULL)
 {
  log->error("Null block!! sysName= " + sysName + ", userName= " + userName);
  return;
 }
 connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), _manager, SLOT(propertyChange(PropertyChangeEvent*)));
 block->setUserName(userName);
 QString c = elem.firstChildElement("comment").text();
 if (c != NULL)
 {
  block->setComment(c);
 }
 if (elem.attribute("units") != NULL) {
     block->setMetricUnits(elem.attribute("units")==("true"));
 } else {
     block->setMetricUnits(false);
 }
 if (elem.attribute("length") != NULL) {
     block->setLength((elem.attribute("length")).toFloat());
 }
 if (elem.attribute("curve") != NULL) {
     block->setCurvature(((elem.attribute("curve")).toInt()));
 }
 QDomNodeList sensors = elem.elementsByTagName("sensor");
 if (sensors.size() > 1)
 {
  log->error("More than one sensor present: " + sensors.size());
 }
 if (sensors.size() > 0)
 {
  // sensor
  QString name = sensors.at(0).toElement().attribute("systemName");
  block->setSensor(name);
 }
 QDomElement errSensor = elem.firstChildElement("errorSensor");
 if (errSensor != QDomElement())
 {
  // sensor
  QString name = errSensor.attribute("systemName");
  //Sensor sensor = InstanceManager.sensorManagerInstance().provideSensor(name);
  block->setErrorSensor(name);
 }
 QDomElement reporter = elem.firstChildElement("reporter");
 if (reporter != QDomElement())
 {
  // sensor
  QString name = reporter.attribute("systemName");
  //Sensor sensor = InstanceManager.sensorManagerInstance().provideSensor(name);
  try
  {
   Reporter* rep = InstanceManager::reporterManagerInstance()->getReporter(name);
   if (rep != NULL)
   {
    block->setReporter(rep);
   }
  } catch (Exception ex) {
      log->error("No Reporter named \"" + name + "\" found. threw exception: " /*+ ex*/);
  }
  if (reporter.attribute("reportCurrent") != NULL) {
      block->setReportingCurrent(reporter.attribute("reportCurrent")==("true"));
  } else {
      block->setReportingCurrent(false);
  }
 }
 if (elem.attribute("permissive") != NULL)
 {
  block->setPermissiveWorking(elem.attribute("permissive")==("true"));
 } else {
  block->setPermissiveWorking(false);
 }
 if (elem.attribute("speedNotch") != NULL)
 {
     //try {
  block->setBlockSpeed(elem.attribute("speedNotch"));
//            } catch (jmri.JmriException ex) {
//                JOptionPane.showMessageDialog(NULL, ex.getMessage() + "\n" + elem.attribute("speedNotch"));
//            }
 }

 QDomNodeList portals = elem.elementsByTagName("portal");
 for (int k = 0; k < portals.size(); k++)
 {
  block->addPortal(loadPortal(portals.at(k).toElement()));
 }

 QDomNodeList paths = elem.childNodes();
 for (int j = 0; j < paths.size(); j++)
 {
  if(paths.at(j).toElement().tagName() == "path")
  {
   if (!block->addPath(loadPath(paths.at(j).toElement(), block)))
   {
    log->error("OBlockManagerXml load: block \"" + sysName + "\" failed to add path \"" + paths.at(j).toElement().attribute("pathName") + "\" in block \"" + block->getSystemName() + "\"");
   }
  }
 }
}

//@SuppressWarnings("NULL")
Portal* OBlockManagerXml::loadPortal(QDomElement elem)
{
 QString sysName = NULL;
 QString userName = elem.attribute("portalName");
 if (elem.attribute("systemName") == NULL)
 {
  if (log->isDebugEnabled())
  {
   log->debug("Portal systemName is NULL");
  }
 }
 else
 {
  sysName = elem.attribute("systemName");
 }
 QString fromBlockName = NULL;
 QString toBlockName = NULL;
 // Portals must have user names.
 Portal* portal = _portalMgr->getByUserName(userName);
 if (portal != NULL)
 {
  fromBlockName = portal->getFromBlock()->getSystemName();
  toBlockName = portal->getToBlock()->getSystemName();
 }
 else
 {
  portal = _portalMgr->providePortal(userName);
 }
 if (portal == NULL)
 {
  log->error("unable to create Portal ('" + sysName + "', " + userName + ") " + elem.tagName() + " " /*+ elem.attributes()*/);
  return NULL;
 }
 if (log->isDebugEnabled())
 {
  log->debug("create Portal: (" + portal->getSystemName() + ", " + portal->getUserName() + ")");
 }

 OBlock* fromBlock = NULL;
 QDomElement eFromBlk = elem.firstChildElement("fromBlock");
 if (!eFromBlk.isNull() && eFromBlk.attribute("blockName") != NULL)
 {
  QString name = eFromBlk.attribute("blockName");
  if (fromBlockName != NULL && fromBlockName!=(name))
  {
   log->error("Portal has user name \"" + userName + "\" conflicting with " + portal->toString());
  }
  else
  {
   fromBlock = getBlock(name);
   if (fromBlock != NULL)
   {
    portal->setFromBlock(fromBlock, false);
    fromBlock->addPortal(portal);

    QDomNodeList ePathsFromBlock = eFromBlk.elementsByTagName("path");
    for (int i = 0; i < ePathsFromBlock.size(); i++)
    {
     QDomElement e = ePathsFromBlock.at(i).toElement();
     QString pathName = e.attribute("pathName");
     QString blockName = e.attribute("blockName");
     if (log->isDebugEnabled())
     {
      log->debug("Load portal= " + userName + " fromBlock= " + fromBlock->getSystemName()
              + " pathName= " + pathName + " blockName= " + blockName);
     }
     /*(if (fromBlock.getSystemName().equals(blockName))*/
     {
      // path is in the fromBlock
      OPath* path = getPath(fromBlock, pathName);
      portal->addPath(path);
     }
    }
   }
  }
 }
 else
 {
  log->error("Portal \"" + userName + "\" has no fromBlock!");
 }

 OBlock* toBlock = NULL;
 QDomElement eToBlk = elem.firstChildElement("toBlock");
 if (eToBlk != QDomElement() && eToBlk.attribute("blockName") != NULL)
 {
  QString name = eToBlk.attribute("blockName");
  if (toBlockName != NULL && toBlockName!=(name))
  {
   log->error("Portal has user name \"" + userName + "\" conflicting with " + portal->toString());
  }
  else
  {
   toBlock = getBlock(name);
   if (toBlock != NULL)
   {
    portal->setToBlock(toBlock, false);
    toBlock->addPortal(portal);

    QDomNodeList ePathsToBlock = eToBlk.elementsByTagName("path");
    for (int i = 0; i < ePathsToBlock.size(); i++)
    {
     QDomElement e = ePathsToBlock.at(i).toElement();
     QString pathName = e.attribute("pathName");
     QString blockName = e.attribute("blockName");
     if (log->isDebugEnabled())
     {
      log->debug("Load portal= " + userName + " toBlock= " + toBlock->getSystemName()
                 + " pathName= " + pathName + " blockName= " + blockName);
     }
     /*if (toBlock.getSystemName().equals(blockName))*/
     {
      // path is in the toBlock
      OPath* path = getPath(toBlock, pathName);
      portal->addPath(path);
     }
    }
   }
  }
 }
 else
 {
  log->error("Portal \"" + userName + "\" has no toBlock!");
 }
 QDomElement eSignal = elem.firstChildElement("fromSignal");
 if (eSignal != QDomElement())
 {
  QString name = eSignal.attribute("signalName");
  float length = 0.0f;
  bool bok = true;
  QString attr = eSignal.attribute("signalDelay");
  if (attr != NULL)
  {
   length = attr.toFloat(&bok);
  }
  if(!bok)
  {
   log->error("Could not parse signalDelay for signal (" + name + ") in portal (" + userName + ")");
  }
  portal->setProtectSignal(Portal::getSignal(name), length, toBlock);
 }
 eSignal = elem.firstChildElement("toSignal");
 if (eSignal != QDomElement())
 {
  QString name = eSignal.attribute("signalName");
  float length = 0.0f;
  bool bok = true;
  QString attr = eSignal.attribute("signalDelay");
  if (attr != NULL) {
      length = attr.toFloat(&bok);
  }
  if(!bok)
  {
   log->error("Could not parse signalDelay for signal (" + name + ") in portal (" + userName + ")");
  }
  portal->setProtectSignal(Portal::getSignal(name), length, fromBlock);
 }

 if (log->isDebugEnabled())
 {
  log->debug("End Load portal " + userName);
 }
 return portal;
}

//@SuppressWarnings("unchecked")
OPath* OBlockManagerXml::loadPath(QDomElement elem, OBlock* block)
{
 QString pName = elem.attribute("pathName");
 OPath* path = getPath(block, pName);
 bool bOk = true;
 bool bok;
 QString attr = elem.attribute("fromDirection");
 if (attr != NULL)
 {
  path->setFromBlockDirection(attr.toInt(&bok));
  if(!bok) bOk = false;
 }
 attr = elem.attribute("toDirection");
 if (attr != NULL)
 {
  path->setToBlockDirection(attr.toInt(&bok));
  if(!bok) bOk = false;
 }
 if(!bOk)
 {
  log->error("Could not parse path ("+pName+") block ("+block->getSystemName()+") attribute");
 }
 attr =  elem.attribute("length");
 if (attr != "")
 {
  path->setLength(attr.toFloat(&bOk));
  if(!bOk)
  {
   log->error("Could not parse path ("+pName+") block ("+block->getSystemName()+")  length attribute");
  }
 }
 attr = elem.attribute("fromPortal");
 if (attr != NULL)
 {
  path->setFromPortal(getPortal(attr));
 }
 attr = elem.attribute("toPortal");
 if (attr != NULL)
 {
  path->setToPortal(getPortal(attr));
 }

 QDomNodeList settings = elem.elementsByTagName("setting");
 if (log->isDebugEnabled()) log->debug("Path ("+pName+") has "+QString::number(settings.size())+" settings.");
 QSet<QString> turnouts =  QSet<QString>();
 int dups = 0;
 for (int i = 0; i < settings.size(); i++)
 {
  QDomElement setElem = settings.at(i).toElement();
  int setting = 0;
  bool bok;
  {
   setting = setElem.attribute("set").toInt(&bok);
  }
  if(!bok)
  {
   log->error("Could not parse 'set' attribute for path (" + pName
              + ") block (" + block->getSystemName() + ")");
  }
  QString sysName = setElem.attribute("turnout");
  if (!turnouts.contains(sysName))
  {
   Turnout* to = InstanceManager::turnoutManagerInstance()->provideTurnout(sysName);
   turnouts.insert(sysName);
   BeanSetting* bs = new BeanSetting(to, sysName, setting);
   path->addSetting(bs);
  }
  else
  {
   dups++;
  }
 }
 if (dups > 0)
 {
  log->warn(dups + " duplicate settings not loaded for path \"" + pName + "\"");
 }
 return path;
}

/*public*/ int OBlockManagerXml::loadOrder(){
    //return InstanceManager::oBlockManagerInstance().getXMLOrder();
    return Manager::OBLOCKS;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(OBlockManagerXml.class.getName());
//}
