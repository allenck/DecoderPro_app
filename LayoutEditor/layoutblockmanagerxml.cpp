#include "layoutblockmanagerxml.h"
#include "layoutblockmanager.h"

LayoutBlockManagerXml::LayoutBlockManagerXml(QObject*parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("LayoutBlockManagerXml");
 setObjectName("LayoutBlockManagerXml");
}
/**
 * Provides the functionality for
 * configuring a LayoutBlockManager
 * <P>
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @version $Revision: 20173 $
 */
///*public*/ class LayoutBlockManagerXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ LayoutBlockManagerXml() {
//    }

/**
 * Implementation for storing the contents of a
 *	LayoutBlockManager
 * @param o QObject*to store, of type LayoutBlockManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LayoutBlockManagerXml::store(QObject*o)
{
 QDomElement layoutblocks = doc.createElement("layoutblocks");
 //setStoreElementClass(layoutblocks);
 layoutblocks.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutBlockManagerXml");
 LayoutBlockManager* tm = (LayoutBlockManager*) o;
 if (tm->isAdvancedRoutingEnabled())
 {
  layoutblocks.setAttribute("blockrouting", "yes");
 }
 if(tm->getNamedStabilisedSensor()!=NULL)
 {
  layoutblocks.setAttribute("routingStablisedSensor", tm->getNamedStabilisedSensor()->getName());
 }

 QStringListIterator iter( tm->getSystemNameList());

 // don't return an element if there is nothing to include
 if (!iter.hasNext()) return QDomElement();

 while (iter.hasNext())
 {
  QString sname = iter.next();
  if (sname==NULL) log->error("System name NULL during LayoutBlock store");
  log->debug("layoutblock system name is "+sname);
  LayoutBlock* b = (LayoutBlock*)tm->getBySystemName(sname);
  if (b->getUseCount()>0)
  {
   // save only those LayoutBlocks that are in use--skip abandoned ones
   QDomElement elem = doc.createElement("layoutblock");
   //elem.setAttribute("systemName", sname);
   QDomElement e1;
   elem.appendChild(e1=doc.createElement("systemName"));
   e1.appendChild(doc.createTextNode(sname));
   storeCommon(b, elem);
   if (b->getOccupancySensorName() != "")
   {
    elem.setAttribute("occupancysensor", b->getOccupancySensorName());
   }
   elem.setAttribute("occupiedsense", b->getOccupiedSense());
   elem.setAttribute("trackcolor", LayoutBlock::colorToString(b->getBlockTrackColor()));
   elem.setAttribute("occupiedcolor", LayoutBlock::colorToString(b->getBlockOccupiedColor()));
   elem.setAttribute("extracolor", LayoutBlock::colorToString(b->getBlockExtraColor()));
   layoutblocks.appendChild(elem);
   if (b->getMemoryName() != "")
   {
    elem.setAttribute("memory", b->getMemoryName());
   }
   if(!b->useDefaultMetric())
   {
    QDomElement e2;
    elem.appendChild(e2=doc.createElement("metric"));
    e2.appendChild(doc.createTextNode(QString::number(b->getBlockMetric())));
   }
  }
 }
 return (layoutblocks);
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param layoutblocks The top-level element being created
 */
/*public*/ void LayoutBlockManagerXml::setStoreElementClass(QDomElement layoutblocks)
{
 layoutblocks.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutBlockManagerXml");
}

/*public*/ void LayoutBlockManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("Invalid method called");
}

/**
 * Create a LayoutBlockManager object of the correct class, then
 * register and fill it.
 * @param layoutblocks Top level QDomElement to unpack.
 * @return true if successful
 */
/*public*/ bool LayoutBlockManagerXml::load(QDomElement layoutblocks) throw (Exception)  {
    // create the master object
    replaceLayoutBlockManager();
    // load individual layoutblocks
    loadLayoutBlocks(layoutblocks);
    return true;
}

/**
 * Utility method to load the individual LayoutBlock objects.
 * If there's no additional info needed for a specific layoutblock type,
 * invoke this with the parent of the set of layoutblock elements.
 * @param layoutblocks QDomElement containing the layoutblock elements to load.
 */
//@SuppressWarnings("unchecked")
/*public*/ void LayoutBlockManagerXml::loadLayoutBlocks(QDomElement layoutblocks)
{
 LayoutBlockManager* tm = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 try
 {
  tm->enableAdvancedRouting(layoutblocks.attribute("blockrouting")=="true");
 } catch (DataConversionException e1) {
     log->warn("unable to convert layout block manager blockrouting attribute");
 }
 catch (NullPointerException e) {  // considered normal if the attribute is not present
 }
 if (layoutblocks.attribute("routingStablisedSensor") != "")
 {
  try
  {
   tm->setStabilisedSensor(layoutblocks.attribute("routingStablisedSensor"));
  }
  catch (JmriException e) {
  }
 }

 QDomNodeList layoutblockList = layoutblocks.elementsByTagName("layoutblock");
 if (log->isDebugEnabled()) log->debug("Found "+QString::number(layoutblockList.size())+" layoutblocks");

 for (int i=0; i<layoutblockList.size(); i++)
 {
  QString sysName = getSystemName(layoutblockList.at(i).toElement()) ;
  if(sysName == NULL)
  {
   log->warn("unexpected NULL in systemName "+
                        ((layoutblockList.at(i).toElement().tagName()))+" "/*+
                                ((layoutblockList.at(i))).attributes()*/);
   break;
  }

  QString userName = getUserName(layoutblockList.at(i).toElement());
  LayoutBlock* b = tm->createNewLayoutBlock(sysName, userName);

  // load common parts
  loadCommon(b, layoutblockList.at(i).toElement());

  if (b!=NULL)
  {
   // set attributes
   QColor color = LayoutBlock::stringToColor(((layoutblockList.at(i).toElement())).
                                            attribute("trackcolor"));
   b->setBlockTrackColor(color);
   color = LayoutBlock::stringToColor(((layoutblockList.at(i).toElement()))
                                        .attribute("occupiedcolor"));
   b->setBlockOccupiedColor(color);
   QString a = ((layoutblockList.at(i).toElement()))
                                        .attribute("extracolor");
   if (a!="")
   {
    b->setBlockExtraColor(LayoutBlock::stringToColor(a));
   }
   a = ((layoutblockList.at(i).toElement())).attribute("occupancysensor");
   if (a!="")
   {
    b->setOccupancySensorName(a);
   }
   a = ((layoutblockList.at(i).toElement()))
                                        .attribute("memory");
   if (a!=NULL)
   {
    b->setMemoryName(a);
   }
   a = ((layoutblockList.at(i).toElement())).
                                        attribute("occupancysensorsense");
   int sense = Sensor::ACTIVE;
   try
   {
    sense = ((layoutblockList.at(i).toElement())).
                                        attribute("occupiedsense").toInt();
   }
   catch (DataConversionException e)
   {
    log->error("failed to convert occupiedsense attribute");
   }
   b->setOccupiedSense(sense);
   if (!((layoutblockList.at(i).toElement())).firstChildElement("metric").isNull())
   {
    QString stMetric = ((layoutblockList.at(i).toElement())).firstChildElement("metric").text();
    try
    {
     b->setBlockMetric((stMetric).toInt());
    }
    catch (NumberFormatException e)
    {
     log->error("failed to convert metric attribute for block " + b->getDisplayName());
    }
   }
  }
 }
}

/**
 * Replace the current LayoutBlockManager, if there is one, with
 * one newly created during a load operation. This is skipped
 * if they are of the same absolute type.
 */
/*protected*/ void LayoutBlockManagerXml::replaceLayoutBlockManager()
{
#if 1 // Java code has this deprecated!
 if (static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")) != NULL && QString(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"))->metaObject()->className())
            == ("LayoutBlockManager"))
  return;
 // if old manager exists, remove it from configuration process
 if (InstanceManager::getDefault("LayoutBlockManager") != NULL)
  // TODO: imlement ConfigXmlManager
  static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->deregister(
            static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager")) );

 // register new one with InstanceManager
 LayoutBlockManager* pManager = static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayoutBlockManager"));
 // register new one for configuration
 ConfigureManager* cm =static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
 if(cm != nullptr)
  cm->registerConfig(pManager, Manager::LAYOUTBLOCKS);
#endif
}
