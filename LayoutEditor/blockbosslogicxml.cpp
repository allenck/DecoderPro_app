#include "blockbosslogicxml.h"
#include "blockbosslogic.h"
#include "manager.h"

BlockBossLogicXml::BlockBossLogicXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("BlockBossLogicXml");
 setObjectName("BlockBossLogicXml");
}

BlockBossLogicXml::~BlockBossLogicXml()
{
 delete log;
}

/**
 * Handle XML persistance of Simple Signal Logic objects.
 *
 * <p>
 * In JMRI 2.1.5, the XML written by this
 * package was changed.
 * <p>
 * Previously, it wrote a single
 * "blocks" element, which contained multiple "block" elements
 * to represent each individual BlockBoss (Simple Signal Logic) object.
 * <p>
 * These names were too generic, and conflicted with storing true Block
 * objects.
 * <p>
 * Starting in JMRI 2.1.5 (May 2008), these were changed to
 * "signalelements" and "signalelement" respectively.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003, 2005
 * @version $Revision: 18102 $
 *
 * Revisions to add facing point sensors, approach lighting,
 * and limited speed.                 Dick Bronson (RJB) 2006
 */

///*public*/ class BlockBossLogicXml extends jmri.configurexml.AbstractXmlAdapter {

///*public*/ BlockBossLogicXml() {
//}

/**
 * Default implementation for storing the contents of
 * all the BLockBossLogic elements.
 * <P>
 * Static members in the BlockBossLogic class record the
 * complete set of items.  This function writes those out
 * as a single XML element.
 *
 * @param o QObject* to start process, but not actually used
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement BlockBossLogicXml::store(QObject* o)
{
 QListIterator<BlockBossLogic*> e = BlockBossLogic::entries();
 if (!e.hasNext()) return QDomElement();  // nothing to write!
 QDomElement blocks = doc.createElement("signalelements");
 blocks.setAttribute("class", "jmri.jmrit.blockboss.configurexml.BlockBossLogicXml");

 while ( e.hasNext())
 {
  BlockBossLogic* p = e.next();
  QDomElement block = doc.createElement("signalelement");
  block.setAttribute("signal", p->getDrivenSignal());
  block.setAttribute("mode", p->getMode());

  if (p->getApproachSensor1()!=NULL)
  {
   block.setAttribute("approachsensor1", p->getApproachSensor1());
  }

  if (p->getSensor1()!=NULL) block.appendChild(storeSensor(p->getSensor1()));
  if (p->getSensor2()!=NULL) block.appendChild(storeSensor(p->getSensor2()));
  if (p->getSensor3()!=NULL) block.appendChild(storeSensor(p->getSensor3()));
  if (p->getSensor4()!=NULL) block.appendChild(storeSensor(p->getSensor4()));
  if (p->getSensor5()!=NULL) block.appendChild(storeSensor(p->getSensor5()));

  if (p->getTurnout()!=NULL)
  {
   block.setAttribute("watchedturnout", p->getTurnout());
  }
  if (p->getWatchedSignal1()!=NULL)
  {
   block.setAttribute("watchedsignal1", p->getWatchedSignal1());
  }
  if (p->getWatchedSignal1Alt()!=NULL)
  {
   block.setAttribute("watchedsignal1alt", p->getWatchedSignal1Alt());
  }
  if (p->getWatchedSignal2()!=NULL)
  {
   block.setAttribute("watchedsignal2", p->getWatchedSignal2());
  }
  if (p->getWatchedSignal2Alt()!=NULL)
  {
   block.setAttribute("watchedsignal2alt", p->getWatchedSignal2Alt());
  }
  if (p->getWatchedSensor1()!=NULL)
  {
   block.setAttribute("watchedsensor1", p->getWatchedSensor1());
  }
  if (p->getWatchedSensor1Alt()!=NULL)
  {
   block.setAttribute("watchedsensor1alt", p->getWatchedSensor1Alt());
  }
  if (p->getWatchedSensor2()!=NULL)
  {
   block.setAttribute("watchedsensor2", p->getWatchedSensor2());
  }
  if (p->getWatchedSensor2Alt()!=NULL)
  {
   block.setAttribute("watchedsensor2alt", p->getWatchedSensor2Alt());
  }

  block.setAttribute("limitspeed1", p->getLimitSpeed1());
  block.setAttribute("limitspeed2", p->getLimitSpeed2());
  block.setAttribute("useflashyellow", p->getUseFlash());
  block.setAttribute("distantsignal", p->getDistantSignal());

  // add comment, if present
  if (p->getComment() != NULL)
  {
   QDomElement c = doc.createElement("comment");
   c.appendChild(doc.createTextNode(p->getComment()));
   block.appendChild(c);
  }

  blocks.appendChild(block);
 }
 return blocks;
}

QDomElement BlockBossLogicXml::storeSensor(QString name)
{
 QDomElement e = doc.createElement("sensorname");
 e.appendChild(doc.createTextNode(name));
 return e;
}

/**
 * Update static data from XML file
 * @param element Top level blocks QDomElement to unpack.
 * @return true if successful
  */
//@SuppressWarnings("unchecked")
/*public*/ bool BlockBossLogicXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException)
{
 bool result = true;
 QDomNodeList l = shared.elementsByTagName("signalelement");

 // try old format if there are no new entries
 // this is for backward compatibility only
 if (l.size() == 0)
  l = shared.elementsByTagName("block");

 // process each item
 for (int i = 0; i<l.size(); i++)
 {
  QDomElement block = l.at(i).toElement();
  BlockBossLogic* bb =NULL;
  try
  {
   bb = BlockBossLogic::getStoppedObject(block.attribute("signal"));
  }
  catch (IllegalArgumentException e)
  {
   log->error("An error occured trying to find the signal for the signal elements for " + block.attribute("signal"));
   result = false;
  }
  if(bb!=NULL)
  {
   if (block.attribute("approachsensor1")!="")
   {
    try
    {
     bb->setApproachSensor1(block.attribute("approachsensor1"));
    }
    catch (IllegalArgumentException e)
    {
     log->error("An error occured loading the approach sensor for the signal elements for " + bb->getDrivenSignal());
     result = false;
    }
   }
   if (block.attribute("watchedsensor")!=NULL)
   {   // for older XML files
    try
    {
     bb->setSensor1(block.attribute("watchedsensor"));
    }
    catch (IllegalArgumentException e)
    {
     log->error("An error occured loading the watched sensor in the SSL for " + bb->getDrivenSignal());
     result = false;
    }
   }

   // old form of sensors with system names
   QDomNodeList sl = block.elementsByTagName("sensor");
   try
   {
    if (sl.size()>=1 && !sl.at(0).toElement().isNull()) bb->setSensor1(sl.at(0).toElement().attribute("systemName"));
    if (sl.size()>=2 && !sl.at(1).toElement().isNull()) bb->setSensor2(sl.at(1).toElement().attribute("systemName"));
    if (sl.size()>=3 && !sl.at(2).toElement().isNull()) bb->setSensor3(sl.at(2).toElement().attribute("systemName"));
    if (sl.size()>=4 && !sl.at(3).toElement().isNull()) bb->setSensor4(sl.at(3).toElement().attribute("systemName"));
    if (sl.size()>=5 && !sl.at(4).toElement().isNull()) bb->setSensor5(sl.at(4).toElement().attribute("systemName"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensors list in the SSL");
    result = false;
   }
   // new form of sensors with system names
   sl = block.elementsByTagName("sensorname");
   try
   {
    if (sl.size()>=1 && !sl.at(0).toElement().isNull()) bb->setSensor1(sl.at(0).toElement().text());
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensor1 list in the SSL for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (sl.size()>=2 && !sl.at(1).toElement().isNull()) bb->setSensor2(sl.at(1).toElement().text());
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensor2 list in the SSL for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
     if (sl.size()>=3 && !sl.at(2).toElement().isNull()) bb->setSensor3(sl.at(2).toElement().text());
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensor3 list in the SSL for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (sl.size()>=4 && !sl.at(3).toElement().isNull()) bb->setSensor4(sl.at(3).toElement().text());
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensor4 list in the SSL for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (sl.size()>=5 && !sl.at(4).toElement().isNull()) bb->setSensor5(sl.at(4).toElement().text());
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured loading the sensor5 list in the SSL for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    bb->setMode(block.attribute("mode").toInt());
    if (block.attribute("distantsignal")!=NULL)
     bb->setDistantSignal(block.attribute("distantsignal")=="true");
    if (block.attribute("limitspeed1")!=NULL)
     bb->setLimitSpeed1(block.attribute("limitspeed1")=="true");
    if (block.attribute("limitspeed2")!=NULL)
        bb->setLimitSpeed2(block.attribute("limitspeed2")=="true");
    try
    {
     if (block.attribute("watchedturnout")!=NULL)
      bb->setTurnout(block.attribute("watchedturnout"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched turnout ("+ block.attribute("watchedturnout") + ")element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsignal1")!=NULL)
     bb->setWatchedSignal1(block.attribute("watchedsignal1"),
                                block.attribute("useflashyellow")=="true");
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched signal 1 ("+ block.attribute("watchedsignal1") + ")element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsignal1alt")!=NULL)
     bb->setWatchedSignal1Alt(block.attribute("watchedsignal1alt"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched signal 1 alt ("+ block.attribute("watchedsignal1alt") + ")element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsignal2")!=NULL)
            bb->setWatchedSignal2(block.attribute("watchedsignal2"));

   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched signal 2 ("+ block.attribute("watchedsignal2") + ")element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsignal2alt")!=NULL)
            bb->setWatchedSignal2Alt(block.attribute("watchedsignal2alt"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched signal 2 alt ("+ block.attribute("watchedsignal2alt") + ") element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsensor1")!=NULL)
            bb->setWatchedSensor1(block.attribute("watchedsensor1"));
   } catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched sensor 1 ("+ block.attribute("watchedsensor1") + ") element attribute list for " + bb->getDrivenSignal());
    result = false;
   }

   try
   {
    if (block.attribute("watchedsensor1alt")!=NULL)
            bb->setWatchedSensor1Alt(block.attribute("watchedsensor1alt"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched sensor 1 alt ("+ block.attribute("watchedsensor1alt") + ") element attribute list for " + bb->getDrivenSignal());
    result = false;
   }
   try
   {
    if (block.attribute("watchedsensor2")!=NULL)
            bb->setWatchedSensor2(block.attribute("watchedsensor2"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched sensor 2 ("+ block.attribute("watchedsensor2")+ ") element attribute list for " + bb->getDrivenSignal());
    result = false;
   }
   try
   {
    if (block.attribute("watchedsensor2alt")!=NULL)
      bb->setWatchedSensor2Alt(block.attribute("watchedsensor2alt"));
   }
   catch (IllegalArgumentException e)
   {
    log->error("An error occured in retrieving the watched sensor 2 alt ("+ block.attribute("watchedsensor2alt") + ")element attribute list for " + bb->getDrivenSignal());
        result = false;
   }
   // load comment, if present
   QString c = block.firstChildElement("comment").text();
   if (c != "")
   {
    bb->setComment(c);
   }

  } catch (DataConversionException e)
  {
   log->warn("error reading blocks from file"+e.getMessage());
   result = false;
  }
  catch (IllegalArgumentException e)
  {
    log->error("An error occured in the signal element attribute list");
    result = false;
   }
   try
   {
    bb->retain();
    bb->start();
   }
   catch (NullPointerException e)
   {
    log->error("An error occured trying to start the signal logic " + bb->getDrivenSignal());
    result = false;
   }
  }
 }
 return result;
}

/**
 * Update static data from XML file
 * @param element Top level QDomElement to unpack.
 * @param o  ignored
 */
/*public*/ void BlockBossLogicXml::load(QDomElement element, QObject* o) throw (Exception)
{
 log->error("load(Element, QObject*) called unexpectedly");
}

/*public*/ int BlockBossLogicXml::loadOrder() const
{
 return Manager::BLOCKBOSS;
}
