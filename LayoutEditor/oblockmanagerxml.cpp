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
    OBlockManager* obm = (OBlockManager*) o;
 if (obm != nullptr) {
     QSet<NamedBean*> oblockList = obm->getNamedBeanSet();
     // don't return an element if there are no oblocks to include
     if (oblockList.isEmpty()) {
         return QDomElement();
     }
     for (NamedBean* nb : oblockList) {
      OBlock* block = (OBlock*)nb;
         QString sName = block->getSystemName();
         QString uName = block->getUserName();
         log->debug(tr("OBlock: sysName= %1, userName= %2").arg(sName).arg(uName));
         QDomElement elem = doc.createElement("oblock");
         elem.setAttribute("systemName", sName);
         if (!uName.isNull() && !uName.isEmpty()) {
             elem.setAttribute("userName", uName); // doing this for compatibility during 2.9.* series
             elem.appendChild(doc.createElement("userName").appendChild(doc.createTextNode(uName)));
         }
         QString comment = block->getComment();
         if (!comment.isNull() && !comment.isEmpty()) {
             QDomElement c = doc.createElement("comment");
             c.appendChild(doc.createTextNode(comment));
             elem.appendChild(c);
         }
         elem.setAttribute("length", QString::number(block->getLengthMm()));
         elem.setAttribute("units", block->isMetric() ? "true" : "false");
         elem.setAttribute("curve", QString::number(block->getCurvature()));
         if (block->getNamedSensor() != nullptr) {
             QDomElement se = doc.createElement("sensor");
             se.setAttribute("systemName", block->getNamedSensor()->getName());
             elem.appendChild(se);
         }
         if (block->getNamedErrorSensor() != nullptr) {
             QDomElement se = doc.createElement("errorSensor");
             se.setAttribute("systemName", block->getNamedErrorSensor()->getName());
             elem.appendChild(se);
         }
         if (block->getReporter() != nullptr) {
             QDomElement se = doc.createElement("reporter");
             se.setAttribute("systemName", block->getReporter()->getSystemName());
             se.setAttribute("reportCurrent", block->isReportingCurrent() ? "true" : "false");
             elem.appendChild(se);
         }
         elem.setAttribute("permissive", block->getPermissiveWorking() ? "true" : "false");
         elem.setAttribute("speedNotch", block->getBlockSpeed());

         QVector<Path*>* paths = block->getPaths();
         for (Path* op : *paths) {
             elem.appendChild(storePath((OPath*) op));
         }
         QList<Portal*> portals = block->getPortals();
         for (Portal* po : portals) {
             elem.appendChild(storePortal(po));
         }
         // and put this element out
         blocks.appendChild(elem);
     }
 }
 return blocks;
}

QDomElement OBlockManagerXml::storePortal(Portal* portal)
{
 QDomElement elem = doc.createElement("portal");
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

//Portal* OBlockManagerXml::getPortal(QString name)
//{
// Portal* portal = _portalMgr->providePortal(name);
// if (portal == NULL)
// {
//  portal = _portalMgr->createNewPortal(NULL, name);
//  if (log->isDebugEnabled())
//  {
//   log->debug("create Portal: (" + portal->getSystemName() + ", " + name + ")");
//  }
// }
// return portal;
//}

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
 //connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), _manager, SLOT(propertyChange(PropertyChangeEvent*)));
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
   Reporter* rep = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(name);
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
 QString userName = elem.attribute("portalName");
 QString fromBlockName = "";
 QString toBlockName = "";
 // Portals must have user names.
 Portal* portal = _portalMgr->getPortal(userName);
 if (portal != nullptr) {
     OBlock* block = portal->getFromBlock();
     if (block != nullptr) {
         fromBlockName = block->getSystemName();
     }
     block = portal->getToBlock();
     if (block != nullptr) {
         toBlockName = block->getSystemName();
     }
 } else {
     portal = _portalMgr->providePortal(userName);
 }
 if (portal == nullptr)
 {
     log->error(tr("unable to create Portal (%1) elem attrs= %2").arg(
             userName).arg("attributes()"));
     return nullptr;
 }
 log->debug(tr("create Portal: (%1)").arg(userName));

 OBlock* fromBlock = nullptr;
 QDomElement eFromBlk = elem.firstChildElement("fromBlock");
 if (!eFromBlk.isNull() && eFromBlk.attribute("blockName") != "") {
  QString name = eFromBlk.attribute("blockName");
  if (fromBlockName != "" && fromBlockName != (name)) {
      log->error(tr("Portal user name \"%1\" has conflicting fromBlock \"%2\". Should be \"%3\"").arg(
              userName).arg(fromBlockName).arg(name));
  }
  else {
   fromBlock = getBlock(name);
   if (fromBlock != nullptr)
   {
    portal->setFromBlock(fromBlock, false);
    fromBlock->addPortal(portal);

    QDomNodeList ePathsFromBlock = eFromBlk.elementsByTagName("path");
    for(int i=0; i <  ePathsFromBlock.count(); i++)
    {
     QDomElement e = ePathsFromBlock.at(i).toElement();
     QString pathName = e.attribute("pathName");
     QString blockName = e.attribute("blockName");
     log->debug(tr("Load portal= \"%1\" fromBlock= %2, pathName= %3, blockName= %4").arg(
             userName).arg(fromBlock->getSystemName()).arg(pathName).arg(blockName));
     OPath* path = getPath(fromBlock, pathName);
     portal->addPath(path);
    }
   }
  }
 } else {
   log->error(tr("Portal \"%1\" has no fromBlock!").arg(userName));
 }
 OBlock* toBlock = nullptr;
     QDomElement eToBlk = elem.firstChildElement("toBlock");
     if (!eToBlk.isNull() && eToBlk.attribute("blockName") != "")
     {
      QString name = eToBlk.attribute("blockName");
      if (toBlockName != "" && toBlockName != (name)) {
          log->error(tr("Portal user name \"%1\" has conflicting toBlock \"%2\". Should be \"%3\"").arg(
                  userName).arg(toBlockName).arg(name));
      } else {
          toBlock = getBlock(name);
          if (toBlock != nullptr) {
              portal->setToBlock(toBlock, false);
              toBlock->addPortal(portal);

              QDomNodeList ePathsToBlock = eToBlk.elementsByTagName("path");
              for(int i=0; i <  ePathsToBlock.count(); i++)
              {
               QDomElement ePath = ePathsToBlock.at(i).toElement();
                  QString pathName = ePath.attribute("pathName");
                  QString blockName = ePath.attribute("blockName");
                  log->debug(tr("Load portal= \"%1\" toBlock= %2, pathName= %3, blockName= %4").arg(userName).arg(toBlock->getSystemName()).arg(pathName).arg(blockName));
                  // path is in the toBlock
                  OPath* path = getPath(toBlock, pathName);
                  portal->addPath(path);
              }
          }
      }
     } else {
         log->error(tr("Portal \"%1\" has no toBlock!").arg(userName));
     }
     QDomElement eSignal = elem.firstChildElement("fromSignal");
     if (!eSignal.isNull()) {
         QString name = eSignal.attribute("signalName");
         float length = 0.0f;
         bool ok = true;
             QString attr = eSignal.attribute("signalDelay");
             if (attr != "") {
                 length = attr.toFloat(&ok);
             }
         if(!ok) {
             log->error(tr("Could not parse signalDelay fromSignal (%1) in portal (%2)").arg(name).arg(userName));
         }
         portal->setProtectSignal(Portal::getSignal(name), length, toBlock);
     }
     eSignal = elem.firstChildElement("toSignal");
     if (!eSignal.isNull()) {
         QString name = eSignal.attribute("signalName");
         float length = 0.0f;
         bool ok = true;
             QString attr = eSignal.attribute("signalDelay");
             if (attr != "") {
                 length = attr.toFloat(&ok);
             }
         if(!ok) {
             log->error(tr("Could not parse signalDelay toSignal (%1) in portal (%2)").arg(name).arg(userName));
         }
         portal->setProtectSignal(Portal::getSignal(name), length, fromBlock);
     }

     log->debug(tr("End Load portal %1").arg(userName));
     return portal;
 }   // loadPortal


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
 if (attr != "") {
    Portal* portal = _portalMgr->providePortal(attr);
    if (portal != nullptr) {
        path->setFromPortal(portal);
        portal->addPath(path);
    }
  }
  attr = elem.attribute("toPortal");
  if (attr != "") {
    Portal* portal = _portalMgr->providePortal(attr);
    if (portal != nullptr) {
        path->setToPortal(portal);
        portal->addPath(path);
    }
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

/*public*/ int OBlockManagerXml::loadOrder()const{
    //return InstanceManager::oBlockManagerInstance().getXMLOrder();
    return Manager::OBLOCKS;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(OBlockManagerXml.class.getName());
//}
