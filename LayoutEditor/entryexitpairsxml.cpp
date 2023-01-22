#include "entryexitpairsxml.h"
#include "entryexitpairs.h"
#include "layouteditor.h"
#include "signalhead.h"
#include "signalmast.h"
#include "sensor.h"
#include "colorutil.h"
#include "signalmastmanager.h"

EntryExitPairsXml::EntryExitPairsXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
    log = new Logger("EntryExitPairsXml");
}
/**
 * This module handles configuration for the Entry Exit pairs unsed in interlocking on a layouteditor
 *
 * @author Kevin Dickerson Copyright (c) 2007
 * @version $Revision: 1.2 $
 */
// /*public*/ class EntryExitPairsXml extends AbstractXmlAdapter {

///*public*/ EntryExitPairsXml() {
//}

/**
 * Default implementation for storing the contents of a
 * PositionablePoint
 * @param o Object to store, of type PositionablePoint
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement EntryExitPairsXml::store(QObject* o) {

    EntryExitPairs* p = (EntryExitPairs*)o;
    QDomElement element = doc.createElement("entryexitpairs");
    setStoreElementClass(element);
    QList<LayoutEditor*> editors = p->getSourcePanelList();
    if (editors.isEmpty())
     return QDomElement();

    QDomElement e1;
    element.appendChild(e1=doc.createElement("cleardown"));
    e1.appendChild(doc.createTextNode(QString::number(p->getClearDownOption())));

    int overLap = p->getOverlapOption();
    if (overLap > 0) {
        element.appendChild(e1=doc.createElement("overlap")); e1.appendChild(doc.createTextNode(QString::number(overLap)));  // NOI18N
    }

    int memoryClearDelay = p->getMemoryClearDelay();
    if (memoryClearDelay > 0) {
        element.appendChild(e1=doc.createElement("memorycleardelay")); e1.appendChild(doc.createTextNode(QString::number(memoryClearDelay)));  // NOI18N
    }

    QString memoryName = p->getMemoryOption();
    if (!memoryName.isEmpty()) {
        element.appendChild(e1=doc.createElement("memoryname")); e1.appendChild(doc.createTextNode(memoryName));  // NOI18N
    }

    if (p->getDispatcherIntegration()) {
        element.appendChild(e1=doc.createElement("dispatcherintegration")); e1.appendChild(doc.createTextNode("yes"));  // NOI18N
    }
    if (p->useDifferentColorWhenSetting()) {
        element.appendChild(e1=doc.createElement("colourwhilesetting")); e1
                .appendChild(doc.createTextNode(ColorUtil::colorToColorName(p->getSettingRouteColor())));  // NOI18N
        element.appendChild(e1=doc.createElement("settingTimer")); e1.appendChild(doc.createTextNode(QString::number(p->getSettingTimer())));  // NOI18N
    }

    for (int k = 0; k<editors.size(); k++)
    {
        LayoutEditor* panel = editors.at(k);
        QObjectList* nxpair = p->getSourceList(panel);
        if(nxpair!=NULL){
            QDomElement panelElem = doc.createElement("layoutPanel");
            panelElem.setAttribute("name", panel->getLayoutName());
            for (int j = 0; j<nxpair->size(); j++){
                QObject* key = nxpair->at(j);
                QDomElement source = doc.createElement("source");
                QString type = "";
                QString item = "";

                //if(key instanceof SignalMast){
                if(qobject_cast<SignalMast*>(key)!=NULL)
                {
                    type="signalMast";
                    item = ((SignalMast*)key)->getDisplayName();
                }
                else
                //if (key instanceof Sensor) {
                if(qobject_cast<Sensor*>(key)!=NULL)
                {
                    type = "sensor";
                    item = ((Sensor*)key)->getDisplayName();
                }
                else
                //if (key instanceof SignalHead){
                if(qobject_cast<SignalHead*>(key)!=NULL)
                {
                    type = "signalHead";
                    item = ((SignalHead*)key)->getDisplayName();
                }

                source.setAttribute("type", type);
                source.setAttribute("item", item);

                QObjectList* a = p->getDestinationList((NamedBean*)key, panel);
                for (int i = 0; i<a->size(); i++){
                    QObject* keyDest = a->at(i);
                    QString typeDest = "";
                    QString itemDest = "";
                    //if(keyDest instanceof SignalMast)
                    if(qobject_cast<SignalMast*>(keyDest)!=NULL)
                    {
                        typeDest="signalMast";
                        itemDest = ((SignalMast*)keyDest)->getDisplayName();
                    }
                    else
                    //if (keyDest instanceof Sensor)
                    if(qobject_cast<Sensor*>(key)!=NULL)
                    {
                        typeDest = "sensor";
                        itemDest = ((Sensor*)keyDest)->getDisplayName();
                    }
                    else
                    //if (keyDest instanceof SignalHead){
                    if(qobject_cast<SignalHead*>(key)!=NULL)
                    {
                        typeDest = "signalHead";
                        itemDest = ((SignalHead*)keyDest)->getDisplayName();
                    }
                    QDomElement dest = doc.createElement("destination");
                    dest.setAttribute("type", typeDest);
                    dest.setAttribute("item", itemDest);
                    if(!p->isUniDirection((NamedBean*)key, panel, (NamedBean*)keyDest))
                        dest.setAttribute("uniDirection", "no");
                    if(!p->isEnabled((NamedBean*)key, panel, (NamedBean*)keyDest))
                        dest.setAttribute("enabled", "no");
                    int nxType = p->getEntryExitType((NamedBean*)key, panel, (NamedBean*)keyDest);
                    switch (nxType){
                        case 0x00 : dest.setAttribute("nxType", "turnoutsetting");
                                    break;
                        case 0x01 : dest.setAttribute("nxType", "signalmastlogic");
                                    break;
                        case 0x02 : dest.setAttribute("nxType", "fullinterlocking");
                                    break;
                        default   : dest.setAttribute("nxType", "turnoutsetting");
                                    break;
                    }
                    if(p->getUniqueId((NamedBean*)key, panel, (NamedBean*)keyDest)!=NULL)
                        dest.setAttribute("uniqueid", p->getUniqueId((NamedBean*)key, panel, (NamedBean*)keyDest));
                    source.appendChild(dest);
                }
                panelElem.appendChild(source);
            }
            element.appendChild(panelElem);
        }
    }
    return element;
}

/*public*/ void EntryExitPairsXml::setStoreElementClass(QDomElement messages) {
    messages.setAttribute("class","jmri.jmrit.signalling.configurexml.EntryExitPairsXml");
}

///*public*/ void EntryExitPairsXml::load(QDomElement /*element*/, QObject* /*o*/)  throw (Exception){
//    log->error("Invalid method called");
//}

/**
 * Load, starting with the layoutblock element, then
 * all the value-icon pairs
 * @param element Top level QDomElement to unpack.
 */
//@SuppressWarnings({ "unchecked", "NULL" })
/*public*/ bool EntryExitPairsXml::load(QDomElement shared, QDomElement perNode) throw (Exception)
{
 // create the objects
 EntryExitPairs* eep = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");

 try
 {
  QString clearoption = shared.firstChildElement("cleardown").text();
  eep->setClearDownOption(clearoption.toInt());
 }
 catch (NullPointerException* e)
 {
     //Considered normal if it doesn't exists
 }
 // get attributes
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
 QObjectList loadedPanel;
 if (cm != nullptr)
 {
     loadedPanel = cm->getInstanceList("LayoutEditor");
 } else
 {
     log->error("Failed getting optional default config manager");  // NOI18N
     loadedPanel = QObjectList();
 }
 if (!shared.firstChildElement("colourwhilesetting").isNull())
 {
     try {
         eep->setSettingRouteColor(ColorUtil::stringToColor(shared.firstChildElement("colourwhilesetting").text()));  // NOI18N
     } catch (IllegalArgumentException e) {
         eep->setSettingRouteColor(QColor(Qt::black));
         log->error(tr("Invalid color %1; using black").arg(shared.firstChildElement("colourwhilesetting").text()));
     }
     int settingTimer = 2000;
     bool bok;
         settingTimer = shared.firstChildElement("settingTimer").text().toInt(&bok);  // NOI18N
     if(!bok) {
         log->error(tr("Error in converting timer to int %1").arg(shared.firstChildElement("settingTimer").text()));  // NOI18N
     }
     eep->setSettingTimer(settingTimer);
 }
 QDomNodeList panelList = shared.elementsByTagName("layoutPanel");
 for(int k = 0; k<panelList.size(); k++)
 {
  QString panelName = panelList.at(k).toElement().attribute("name");
  LayoutEditor* panel = NULL;
  for (int i=0; i<loadedPanel.size(); i++)
  {
   LayoutEditor* tmp = (LayoutEditor*) loadedPanel.at(i);
   if (tmp->getLayoutName() == (panelName))
   {
    panel = tmp;
    break;
   }
  }
  if(panel!=NULL)
  {
   QDomNodeList sourceList = panelList.at(k).toElement().elementsByTagName("source");
   for (int i = 0; i < sourceList.size(); i++)
   {
    QString sourceType = sourceList.at(i).toElement().attribute("type");
    QString sourceItem = sourceList.at(i).toElement().attribute("item");
    NamedBean* source = NULL;
    if(sourceType==("signalMast")){
        source = dynamic_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(sourceItem);
    } else if (sourceType==("sensor")){
        source = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(sourceItem);
    } else if (sourceType==("signalHead")){
        source = qobject_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(sourceItem);
    }

    //These two could be subbed off.
    QDomNodeList destinationList = sourceList.at(i).toElement().elementsByTagName("destination");
    if(destinationList.size() > 0)
    {
     eep->addNXSourcePoint(source, panel);
    }
    for (int j = 0; j < destinationList.size(); j++)
    {
     QString id = NULL;
     if(destinationList.at(j).toElement().attribute("uniqueid")!="")
         id = destinationList.at(j).toElement().attribute("uniqueid");
     if (!id.startsWith("IN:")) {     // NOI18N
         id = "IN:" + id;    // NOI18N
     }
     QString destType = destinationList.at(j).toElement().attribute("type");
     QString destItem = destinationList.at(j).toElement().attribute("item");
     NamedBean* dest = NULL;
     if(destType == ("signalMast"))
     {
      dest = qobject_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(destItem);
     }
     else if (destType==("sensor"))
     {
      dest = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor(destItem);
     }
     else if (destType==("signalHead"))
     {
      dest = qobject_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(destItem);
     }
     try
     {
      eep->addNXDestination(source, dest, panel, id);
     }
     catch (NullPointerException* e)
     {
      log->error(tr("An error occured while trying to add a point") + ": "+ e->getMessage());
     }
     if((destinationList.at(j).toElement().attribute("uniDirection")!="") && (destinationList.at(j).toElement().attribute("uniDirection")==("no")))
     {
      eep->setUniDirection(source, panel, dest, false);
     }
     if((destinationList.at(j).toElement().attribute("enabled")!="") && (destinationList.at(j).toElement().attribute("enabled")==("no")))
     {
      eep->setEnabled(source, panel, dest, false);
     }
     if(destinationList.at(j).toElement().attribute("nxType")!="")
     {
      QString nxType = destinationList.at(j).toElement().attribute("nxType");
      if(nxType==("turnoutsetting"))
          eep->setEntryExitType(source, panel, dest, 0x00);
      else if (nxType==("signalmastlogic"))
          eep->setEntryExitType(source, panel, dest, 0x01);
      else if (nxType==("fullinterlocking"))
          eep->setEntryExitType(source, panel, dest, 0x02);
     }
    }
   }
  }
  else
  {
   log->error("Panel has not been loaded");
  }
 }
 return true;
}

/*public*/ int EntryExitPairsXml::loadOrder() const
{
 return ((EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs"))->getXMLOrder();
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(EntryExitPairsXml.class.getName());
//}
