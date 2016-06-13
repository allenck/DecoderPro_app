#include "warrantmanagerxml.h"
#include "warrantmanager.h"
#include "blockorder.h"
#include "warrant.h"
#include "dcclocoaddress.h"
#include "oblock.h"
#include "throttlesetting.h"
#include "instancemanager.h"
#include "oblockmanager.h"

WarrantManagerXml::WarrantManagerXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("WarrantManagerXml");
 setObjectName("WarrantManagerXml");
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
// /*public*/ class WarrantManagerXml //extends XmlFile
//                    extends jmri.configurexml.AbstractXmlAdapter {

//    /*public*/ WarrantManagerXml() {
//    }

/**
 * Store the contents of a WarrantManager.
 *
 * @param o Object to store, of type warrantManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement WarrantManagerXml::store(QObject* o) {
    QDomElement warrants = doc.createElement("warrants");
    warrants.setAttribute("class","jmri.jmrit.logix.configurexml.WarrantManagerXml");
    WarrantManager* manager = (WarrantManager*) o;
    QStringListIterator iter(manager->getSystemNameList());
    while (iter.hasNext()) {
        QString sname = iter.next();
        Warrant* warrant = manager->getBySystemName(sname);
        QString uname = warrant->getUserName();
        if (log->isDebugEnabled())
            log->debug("Warrant: sysName= "+sname+", userName= "+uname);
        QDomElement elem = doc.createElement("warrant");
        elem.setAttribute("systemName", sname);
        if (uname=="") uname = "";
        elem.setAttribute("userName", uname);
        QString comment = warrant->getComment();
        if (comment != "") {
            QDomElement c = doc.createElement("comment");
            c.appendChild(doc.createTextNode(comment));
            elem.appendChild(c);
        }

        QList <BlockOrder*>* orders = warrant->getOrders();
        for (int j=0; j<orders->size(); j++) {
            elem.appendChild(storeOrder(orders->at(j), "blockOrder"));
        }
        BlockOrder* viaOrder = warrant->getViaOrder();
        if (viaOrder!=NULL) {
            elem.appendChild(storeOrder(viaOrder, "viaOrder"));
        }

        QList <ThrottleSetting*>* throttleCmds = warrant->getThrottleCommands();
        for (int j=0; j<throttleCmds->size(); j++) {
            elem.appendChild(storeCommand(throttleCmds->at(j), "throttleCommand"));
        }

        elem.appendChild(storeTrain(warrant, "train"));

        // and put this element out
        warrants.appendChild(elem);
    }

    return warrants;
}

QDomElement WarrantManagerXml::storeTrain(Warrant* warrant, QString type) {
    QDomElement elem = doc.createElement(type);
    QString str = warrant->getTrainId();
    if (str=="") str = "";
    elem.setAttribute("trainId", str);

    DccLocoAddress* addr = warrant->getDccAddress();
    if (addr != NULL) {
        elem.setAttribute("dccAddress", addr->getNumber());
        elem.setAttribute("dccType", (addr->isLongAddress() ? "L" : "S"));
    }
    elem.setAttribute("runBlind", warrant->getRunBlind()?"true":"false");

    str = warrant->getTrainName();
    if (str=="") str = "";
    elem.setAttribute("trainName", str);

    return elem;
}

QDomElement WarrantManagerXml::storeOrder(BlockOrder* order, QString type) {
    QDomElement elem = doc.createElement(type);
    OBlock* block = order->getBlock();
    if (block!=NULL) {
        QDomElement blk = doc.createElement("block");
        blk.setAttribute("systemName", block->getSystemName());
        QString uname = block->getUserName();
        if (uname==NULL) uname = "";
        blk.setAttribute("userName", uname);
        elem.appendChild(blk);
    } else {
        log->error("Null block in BlockOrder!");
    }
    QString str = order->getPathName();
    if (str=="") str = "";
    elem.setAttribute("pathName", str);

    str = order->getEntryName();
    if (str=="") str = "";
    elem.setAttribute("entryName", str);

    str = order->getExitName();
    if (str=="") str = "";
    elem.setAttribute("exitName", str);

    return elem;
}

QDomElement WarrantManagerXml::storeCommand(ThrottleSetting* command, QString type) {
    QDomElement elem = doc.createElement(type);

    QString time = QString::number(command->getTime());
    if (time=="") time = "";
    elem.setAttribute("time", time);

    QString str = command->getCommand();
    if (str=="") str = "";
    elem.setAttribute("command", str);

    str = command->getValue();
    if (str=="") str = "";
    elem.setAttribute("value", str);

    str = command->getBlockName();
    if (str=="") str = "";
    elem.setAttribute("block", str);

    return elem;
}

/**
 * Create a Warrant object of the correct class, then
 * register and fill it.
 * @param warrants Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool WarrantManagerXml::load(QDomElement warrants) throw (Exception) {

    //WarrantManager* manager = InstanceManager.warrantManagerInstance();
    WarrantManager* manager = (WarrantManager*)InstanceManager::getDefault("WarrantManager");

    QDomNodeList warrantList = warrants.elementsByTagName("warrant");
    if (log->isDebugEnabled()) log->debug("Found "+QString::number(warrantList.size())+" Warrant objects");
    for (int i=0; i<warrantList.size(); i++)
    {
        QDomElement elem = warrantList.at(i).toElement();
        if (elem.attribute("systemName") == "")
        {
            log->warn("unexpected NULL in systemName "+elem.tagName()/*+" "+elem.attributes()*/);
            break;
        }
        QString sysName = "";
        if (elem.attribute("systemName") != "")
            sysName = elem.attribute("systemName");

        QString userName = "";
        if (elem.attribute("userName") != "")
            userName = elem.attribute("userName");

        Warrant* warrant = manager->createNewWarrant(sysName, userName);
        if (warrant==NULL) {
            log->error("Warrant already exists with names: sysName= "+sysName+" userName= "+userName);
            continue;
        }
        QDomNodeList orders = elem.elementsByTagName("blockOrder");
        for (int k=0; k<orders.size(); k++)
        {
         BlockOrder* bo = loadBlockOrder(orders.at(k).toElement());
         if (bo==NULL)
         {
          break;
         }
         warrant->addBlockOrder(bo);
        }
        //QString c = elem.getChildText("comment");
        QDomElement cmt = elem.firstChildElement("comment");
        QString c = cmt.text();
        if (c != "") {
            warrant->setComment(c);
        }
        orders = elem.elementsByTagName("viaOrder");
        for (int k=0; k<orders.size(); k++) {
            BlockOrder* bo = loadBlockOrder(orders.at(k).toElement());
            if (bo==NULL) {
                continue;
            }
            warrant->setViaOrder(bo);
        }
        QDomNodeList throttleCmds = elem.elementsByTagName("throttleCommand");
        for (int k=0; k<throttleCmds.size(); k++) {
            warrant->addThrottleCommand(loadThrottleCommand(throttleCmds.at(k).toElement()));
        }
        QDomNodeList trains = elem.elementsByTagName("train");
        for (int k=0; k<trains.size(); k++) {
            loadTrain(trains.at(k).toElement(), warrant);
        }
    }
    return true;
}

/*public*/ void WarrantManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception) {
    log->error("load called. Invalid method.");
}

void WarrantManagerXml::loadTrain(QDomElement elem, Warrant* warrant)
{
 if (elem.attribute("trainId") != "") {
     warrant->setTrainId(elem.attribute("trainId"));
 }
 if (elem.attribute("dccAddress") != "") {
     int address = 0;
     try {
        address = elem.attribute("dccAddress").toInt();
     } catch (DataConversionException dce) {
         log->error(dce.getMessage()+ " in Warrant "+warrant->getDisplayName());
     }
     bool isLong = true;
     if (elem.attribute("dccType") != "") {
         isLong = elem.attribute("dccType")==("L");
     }
     warrant->setDccAddress(new DccLocoAddress(address, isLong));
 }
 if (elem.attribute("runBlind") != "") {
     warrant->setRunBlind(elem.attribute("runBlind")==("true"));
 }
 if (elem.attribute("trainName") != "") {
     warrant->setTrainName(elem.attribute("trainName"));
 }
}

//@SuppressWarnings("unchecked")
BlockOrder* WarrantManagerXml::loadBlockOrder(QDomElement elem)
{
 OBlock* block = NULL;
 QDomNodeList blocks = elem.elementsByTagName("block");
 if (blocks.size()>1) log->error("More than one block present: "+blocks.size());
 if (blocks.size()>0)
 {
  // sensor
  QString name = blocks.at(0).toElement().attribute("systemName");
  block =((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->provideOBlock(name);
  if (log->isDebugEnabled()) log->debug("Load Block "+name+".");
  if (block==NULL)
  {
   block =((OBlockManager*) InstanceManager::getDefault("OBlockManager"))->createNewOBlock(name, NULL);
   if (log->isDebugEnabled()) log->debug("create OBlock: ("+name+")");
   if (block==NULL)
   {
    log->error("Block \""+name+"\" is NULL in BlockOrder.");
    return NULL;
   }
  }
 }
 else
 {
  log->error("Null block in BlockOrder");
  return NULL;
 }
 QString attr = elem.attribute("pathName");
 QString pathName = "";
 if (attr != "")
     pathName = attr;

 attr = elem.attribute("entryName");
 QString entryName = "";
 if (attr != "")
     entryName =attr;

 attr = elem.attribute("exitName");
 QString exitName = "";
 if (attr != "")
     exitName =attr;

 return new BlockOrder(block, pathName, entryName, exitName);
}

ThrottleSetting* WarrantManagerXml::loadThrottleCommand(QDomElement elem)
{
    long time = 0;
    try {
        time = elem.attribute("time").toLong();
    } catch (DataConversionException dce) {}

    QString attr = elem.attribute("command");
    QString command = "";
    if (attr != "")
        command =attr;

    attr = elem.attribute("value");
    QString value = "";
    if (attr != "")
        value =attr;

    attr = elem.attribute("block");
    QString block = "";
    if (attr != "")
        block =attr;

    return new ThrottleSetting(time, command, value, block);
}

/*public*/ int WarrantManagerXml::loadOrder(){
    return ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getXMLOrder();
}
