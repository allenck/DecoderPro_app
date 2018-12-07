#include "savexml.h"
#include "layouteditor.h"
#include <QMessageBox>
#include "abstractsensor.h"
#include "turnoutoperationmanagerxml.h"
#include "turnoutoperationxml.h"
#include "abstractmemory.h"
#include "defaultroutemanager.h"
#include "abstractlightmanagerconfigxml.h"
#include "locoiconxml.h"
#include "simpletimebasexml.h"
#include "paneleditorxml.h"
#include "paneleditor.h"
#include "panelmenu.h"
#include "abstractsignalheadmanagerxml.h"
#include "defaultsignalmastmanagerxml.h"
#include "defaultsignalmastmanager.h"
#include "defaultsignalmastlogicmanagerxml.h"
#include "signalheadiconxml.h"
#include "signalmasticonxml.h"
#include "defaultsignalmastlogicmanager.h"
#include "signalmasticon.h"
#include "blockbosslogicxml.h"
#include "layoutblockmanagerxml.h"
#include "lnturnoutmanagerxml.h"
#include "lnsensormanagerxml.h"
#include "internalsensormanagerxml.h"
#include "internalturnoutmanagerxml.h"
#include "blockmanagerxml.h"
#include "defaultlogixmanager.h"
#include "defaultlogixmanagerxml.h"
#include "defaultconditionalmanager.h"
#include "defaultconditionalmanagerxml.h"
#include "oblockmanager.h"
#include "oblockmanagerxml.h"
#include "warrant.h"
#include "warrantmanagerxml.h"
#include "entryexitpairsxml.h"
#include "multisensoricon.h"
#include "multisensoriconxml.h"
#include "controlpaneleditor.h"
#include "controlpaneleditorxml.h"
#include "rfidsensormanagerxml.h"
#include "rfid/rfidsensormanager.h"
#include "signalgroupmanager.h"
#include "defaultsignalgroupmanager.h"
#include "defaultsignalgroupmanagerxml.h"
#include "sectionmanagerxml.h"
#include "lnreportermanagerxml.h"
#include "rfidreportermanagerxml.h"
#include "internalreportermanagerxml.h"
#include "internalreportermanager.h"
#include "lnsensormanager.h"
#include "file.h"
#include "defaultaudiomanager.h"
#include "defaultaudiomanagerxml.h"
#include "internallightmanagerxml.h"
#include "lnlightmanagerxml.h"
#include "internallightmanager.h"
#include "lnlightmanager.h"
#include "defaultroutemanagerxml.h"
#include "defaultmemorymanagerxml.h"
#include "layoutslipxml.h"
#include "layoutturntablexml.h"

SaveXml::SaveXml(QObject *parent) :
    QObject(parent)
{
 this->parent = parent;
 p = (LayoutEditor*)parent;
 //QDomDocument doc();

 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);
 xmlProcessingInstruction =  doc.createProcessingInstruction("xml-stylesheet","type=\"text/xsl\" href=\"/xml/XSLT/panelfile-2-9-6.xsl\"");
 doc.appendChild(xmlProcessingInstruction);
 root = doc.createElement("layout-config");
 root.setAttribute("xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
 root.setAttribute("xsi:noNamespaceSchemaLocation","http://jmri.org/xml/schema/layout-2-9-6.xsd");
 QDomElement version = doc.createElement("jmriversion");
 QDomElement major = doc.createElement("major");
 major.appendChild(doc.createTextNode("3"));
 version.appendChild(major);
 QDomElement minor = doc.createElement("minor");
 minor.appendChild(doc.createTextNode("3"));
 version.appendChild(minor);
 QDomElement test = doc.createElement("test");
 test.appendChild(doc.createTextNode("2"));
 version.appendChild(test);
 QDomElement modifier = doc.createElement("modifier");
 modifier.appendChild(doc.createTextNode(".2"));
 version.appendChild(modifier);
 root.appendChild(version);

 doc.appendChild(root);

}
/**
     * Default implementation for storing the contents of a
     * LayoutEditor
     * @param o Object to store, of type LayoutEditor
     * @return Element containing the complete info
     */
////    public Element store(Object o) {
//        LayoutEditor p = (LayoutEditor)o;
bool SaveXml::store(QString filename)
{
 doc.appendChild(root);
 //root.appendChild(storeSensors(InstanceManager::sensorManagerInstance()));
 storeSensors(InstanceManager::sensorManagerInstance());
 root.appendChild(storeLnTurnouts(InstanceManager::turnoutManagerInstance()));
 root.appendChild(storeTurnouts(InstanceManager::turnoutManagerInstance()));
 storeLights(InstanceManager::lightManagerInstance());
 storeReporters(InstanceManager::reporterManagerInstance());
 root.appendChild(storeMemories(InstanceManager::memoryManagerInstance()));
 root.appendChild(storeSignalHeads(InstanceManager::signalHeadManagerInstance()));
 root.appendChild(storeSignalMasts(InstanceManager::signalMastManagerInstance()));
 root.appendChild(storeLogix(static_cast<LogixManager*>(InstanceManager::getDefault("LogixManager"))));
 root.appendChild(storeAudio((DefaultAudioManager*)InstanceManager::getDefault("DefaultAudioManager")));
 root.appendChild(storeConditionals(static_cast<ConditionalManager*>(InstanceManager::getDefault("ConditionalManager"))));
 root.appendChild((storeBlocks(InstanceManager::blockManagerInstance())));
 root.appendChild(storeOBlocks(InstanceManager::getDefault("OBlockManager")));
 root.appendChild(storeLayoutBlock(static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))));
 root.appendChild(storeSections(InstanceManager::sectionManagerInstance()));
 root.appendChild(storeBlockBossLogic(nullptr));
 root.appendChild(storeRoutes(InstanceManager::routeManagerInstance()));
 root.appendChild(storeWarrants(InstanceManager::getDefault("WarrantManager")));
 root.appendChild(storeSignalMastLogic(InstanceManager::signalMastLogicManagerInstance()));
 root.appendChild(storeSignalGroups(InstanceManager::signalGroupManagerInstance()));
 root.appendChild(storeTimebase(static_cast<Timebase*>(InstanceManager::getDefault("Timebase"))));

 //Element panel = doc.createElement("LayoutEditor");
 QDomElement panel =doc.createElement("LayoutEditor");
 root.appendChild(panel);

 panel.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutEditorXml");
 panel.setAttribute("name", p->getLayoutName());
 panel.setAttribute("x", (p->getUpperLeftX()));
 panel.setAttribute("y", (p->getUpperLeftY()));
// From this version onwards separate sizes for window and panel are stored the
// following two statements allow files written here to be read in 2.2 and before
 panel.setAttribute("height", (p->getLayoutHeight()));
 panel.setAttribute("width", (p->getLayoutWidth()));
// From this version onwards separate sizes for window and panel are stored

 panel.setAttribute("windowheight", (p->getWindowHeight()));
 panel.setAttribute("windowwidth", (p->getWindowWidth()));
 panel.setAttribute("panelheight", (p->getLayoutHeight()));
 panel.setAttribute("panelwidth", (p->getLayoutWidth()));
//panel.setAttribute("sliders", QString("%1").arg(p->getScroll()?QString("yes"):QString("no"))); // deprecated
//panel.setAttribute("scrollable", QString("%1").arg(p->getScrollable());
 panel.setAttribute("editable", (p->isEditable()?QString("yes"):QString("no")));
panel.setAttribute("positionable", QString("%1").arg(p->allPositionable()?QString("yes"):QString("no")));
panel.setAttribute("controlling", QString("%1").arg(p->allControlling()?QString("yes"):QString("no")));
panel.setAttribute("animating", QString("%1").arg(p->isAnimating()?QString("yes"):QString("no")));
//panel.setAttribute("showhelpbar", QString("%1").arg(p->getShowHelpBar()?QString("yes"):QString("no")));
panel.setAttribute("drawgrid", QString("%1").arg(p->getDrawGrid()?QString("yes"):QString("no")));
panel.setAttribute("snaponadd", QString("%1").arg(p->getSnapOnAdd()?QString("yes"):QString("no")));
panel.setAttribute("snaponmove", QString("%1").arg(p->getSnapOnMove()?QString("yes"):QString("no")));
panel.setAttribute("antialiasing", QString("%1").arg(p->getAntialiasingOn()?QString("yes"):QString("no")));
panel.setAttribute("turnoutcircles", QString("%1").arg(p->getTurnoutCircles()?QString("yes"):QString("no")));
panel.setAttribute("tooltipsnotedit", QString("%1").arg(p->getTooltipsNotEdit()?QString("yes"):QString("no")));
panel.setAttribute("tooltipsinedit", QString("%1").arg(p->getTooltipsInEdit()?QString("yes"):QString("no")));
panel.setAttribute("mainlinetrackwidth", QString("%1").arg(p->getMainlineTrackWidth()));
panel.setAttribute("xscale", ((float)p->getXScale()));
panel.setAttribute("yscale", ((float)p->getYScale()));
panel.setAttribute("sidetrackwidth", (p->getSideTrackWidth()));
panel.setAttribute("defaulttrackcolor",p->getDefaultTrackColor());
panel.setAttribute("defaultoccupiedtrackcolor",p->getDefaultOccupiedTrackColor());
panel.setAttribute("defaultalternativetrackcolor",p->getDefaultAlternativeTrackColor());
panel.setAttribute("defaulttextcolor",p->getDefaultTextColor());
panel.setAttribute("turnoutcirclecolor",p->getTurnoutCircleColor());
panel.setAttribute("turnoutcirclesize",QString("%1").arg(p->getTurnoutCircleSize()));
panel.setAttribute("turnoutdrawunselectedleg",(p->getTurnoutDrawUnselectedLeg()?QString("yes"):QString("no")));
panel.setAttribute("turnoutbx", ((float)p->getTurnoutBX()));
panel.setAttribute("turnoutcx", ((float)p->getTurnoutCX()));
panel.setAttribute("turnoutwid", ((float)p->getTurnoutWid()));
panel.setAttribute("xoverlong", ((float)p->getXOverLong()));
panel.setAttribute("xoverhwid", ((float)p->getXOverHWid()));
panel.setAttribute("xovershort", ((float)p->getXOverShort()));
panel.setAttribute("autoblkgenerate", (p->getAutoBlockAssignment()?QString("yes"):QString("no")));
if (p->getBackgroundColor().isValid())
{
    panel.setAttribute("redBackground", QString("%1").arg(p->getBackgroundColor().red()));
    panel.setAttribute("greenBackground", QString("%1").arg(p->getBackgroundColor().green()));
    panel.setAttribute("blueBackground", QString("%1").arg(p->getBackgroundColor().blue()));
}
p->resetDirty();

// include contents (Icons and Labels)
QList <Positionable*> contents = p->getContents();
int num = contents.size();
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  Positionable* sub = contents.at(i);
  if (sub!=NULL /*&& sub->storeItem()*/)
  {
   try
   {
//    Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
//                if (e!=NULL) panel.addContent(e);
    if(qobject_cast<SensorIcon*>(sub)!=NULL)
    {
     SensorIcon* p = (SensorIcon*)sub;
     if (!p->isActive()) return NULL;  // if flagged as inactive, don't store
     //Element element = doc.createElement("sensoricon");
     QDomElement element =doc.createElement("sensoricon");
     element.setAttribute("sensor", p->getNamedSensor()->getName());
     storeCommonAttributes((PositionableLabel*)p, element);
     element.setAttribute("momentary", p->getMomentary()?QString("true"):QString("false"));
     element.setAttribute("icon", p->isIcon()?QString("yes"):QString("no"));

     storeIconInfo(p, element);
     storeTextInfo(p, element);
     element.setAttribute("class", "jmri.jmrit.display.configurexml.SensorIconXml");
     panel.appendChild(element);
    }
    else
    if(qobject_cast<LocoIcon*>(sub) != NULL)
    {
     LocoIcon* l = (LocoIcon*)sub;
     Q_UNUSED(l);
     LocoIconXml* xml = new LocoIconXml(this);
     xml->setDoc(doc);
     panel.appendChild(xml->store((QObject*)sub));
    }
    else
    if(qobject_cast<SignalHeadIcon*>(sub) != NULL)
    {
     SignalHeadIcon* l = (SignalHeadIcon*)sub;
     Q_UNUSED(l);
     SignalHeadIconXml* xml = new SignalHeadIconXml(this);
     xml->setDoc(doc);
     panel.appendChild(xml->store((QObject*)sub));
    }
    else
    if(qobject_cast<SignalMastIcon*>(sub) != NULL)
    {
     SignalMastIcon* l = (SignalMastIcon*)sub;
     Q_UNUSED(l);
     SignalMastIconXml* xml = new SignalMastIconXml(this);
     xml->setDoc(doc);
     panel.appendChild(xml->store((QObject*)sub));
    }
    else
    if(qobject_cast<MultiSensorIcon*>(sub) != NULL)
    {
     SignalMastIcon* l = (SignalMastIcon*)sub;
     Q_UNUSED(l);
     MultiSensorIconXml* xml = new MultiSensorIconXml(this);
     xml->setDoc(doc);
     panel.appendChild(xml->store((QObject*)sub));
    }
    else
    if(qobject_cast<PositionableLabel*>(sub) != NULL)
    {
     PositionableLabelXml* xml = new PositionableLabelXml(this);
     xml->setDoc(doc);
     panel.appendChild(xml->store((QObject*)sub));
    }
    else
     log.warn(tr("No savexml logic to save %1").arg(sub->metaObject()->className()));
    // TODO: Other Positionable types
   }
   catch (Exception e)
   {
    log.error("Error storing panel contents element: "+e.getMessage());
   }
  }
  else
  {
   log.warn("Null entry found when storing panel contents.");
  }
 }
}
// include LayoutTurnouts
num = p->turnoutList->size();
if (log.isDebugEnabled()) log.debug("N layoutturnout elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = p->turnoutList->at(i);
  try
  {
   //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   if(qobject_cast<LayoutTurnout*>(sub)==NULL)
    continue;
   QDomElement e = storeLayoutTurnout((LayoutTurnout*)sub);
   if (!e.isNull())
    panel.appendChild(e);
  }
  catch (Exception e)
  {
   log.error("Error storing panel layoutturnout element: "+e.getMessage());
  }
 }
}


// include TrackSegments
num = p->trackList->size();
if (log.isDebugEnabled()) log.debug("N tracksegment elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = p->trackList->at(i);
  try
  {
   //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   QDomElement e = storeTrackSegment((TrackSegment*)sub);
   if (!e.isNull()) panel.appendChild(e);
  }
  catch (Exception e)
  {
   log.error("Error storing panel tracksegment element: "+e.msg);
  }
 }
}
// include PositionablePoints
num = p->pointList->size();
if (log.isDebugEnabled()) log.debug("N positionablepoint elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = p->pointList->at(i);
  try
  {
   //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   QDomElement e = storePositionablePoint((PositionablePoint*)sub);
   if (!e.isNull()) panel.appendChild(e);
  } catch (Exception e)
  {
   log.error("Error storing panel positionalpoint element: "+e.getMessage());
  }
 }
}

// include LevelXings
num = p->xingList->size();
if (log.isDebugEnabled()) log.debug("N levelxing elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = p->xingList->at(i);
  try
  {
   //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   QDomElement e = storeLevelXing((LevelXing*)sub);
   if (!e.isNull()) panel.appendChild(e);
  }
  catch (Exception e)
  {
   log.error("Error storing panel levelxing element: "+e.getMessage());
  }
 }
}

// include LayoutSlips
num = p->slipList->size();
if (log.isDebugEnabled()) log.debug("N layoutSlip elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = p->slipList->at(i);
  try {
      //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   QDomElement e = storeSlipTurnouts((LayoutSlip*)sub);
      if (!e.isNull()) panel.appendChild(e);
  } catch (Exception e) {
      log.error("Error storing panel layoutSlip element: "/*+e*/);
  }
 }
}
// include LayoutTurntables
num = p->turntableList->size();
if (log.isDebugEnabled()) log.debug("N turntable elements: "+QString("%1").arg(num));
if (num>0)
{
 for (int i=0; i<num; i++)
 {
  QObject* sub = (QObject*)p->turntableList->at(i);
  try {
      //Element e = jmri.configurexml.ConfigXmlManager.elementFromObject(sub);
   QDomElement e = storeTurntables(sub);
      if (!e.isNull()) panel.appendChild(e);
  } catch (Exception e) {
      log.error("Error storing panel turntable element: "/*+e*/);
  }
 }
}

 PanelMenu* pMenu = PanelMenu::instance();
 QList<Editor*>* eList = pMenu->getEditorPanelList();
 for(int i=0; i < eList->count(); i++)
 {
  Editor* p = eList->at(i);
  if(qobject_cast<PanelEditor*>(p)!= NULL)
  {
   // TODO: Handle LayoutEditor here as well
   PanelEditorXml* pxml = new PanelEditorXml((QObject*)p);
   pxml->setDoc(doc);
   QDomElement panelEditor = pxml->store((QObject*)p);
   root.appendChild(panelEditor);
  }
  else if(qobject_cast<ControlPanelEditor*>(p)!= NULL)
  {
   ControlPanelEditorXml* pxml = new ControlPanelEditorXml((QObject*)p);
   pxml->setDoc(doc);
   QDomElement panelEditor = pxml->store((QObject*)p);
   root.appendChild(panelEditor);
  }
 }
 root.appendChild(storeEntryExit(InstanceManager::getDefault("EntryExitPairs")));
 QFile file(filename);
 if (!file.open(QIODevice::WriteOnly | QFile::Truncate))
 {
  /* show wrror message if not able to open file */
  QMessageBox::warning(0, "Read only", "The file is in read only mode");
 }
 else
 {
  QTextStream stream(&file);
  stream.setCodec("UTF-8");
  doc.save(stream, 2);
  return true;
 }
 return false;
}
/*public*/ void SaveXml::storeCommonAttributes(PositionableLabel* p, QDomElement element)
{
    element.setAttribute("x", QString("%1").arg(p->getX()));
    element.setAttribute("y", QString("%1").arg(p->getY()));
    element.setAttribute("level", QString("%1").arg(p->getDisplayLevel()));
    element.setAttribute("forcecontroloff", !p->isControlling()?QString("true"):QString("false"));
    element.setAttribute("hidden", p->isHidden()?QString("yes"):QString("no"));
    element.setAttribute("positionable", p->isPositionable()?QString("true"):QString("false"));
    element.setAttribute("showtooltip", p->showTooltip()?QString("true"):QString("false"));
    element.setAttribute("editable", p->isEditable()?QString("true"):QString("false"));
    QString tip = p->getTooltip();
    QString txt = tip;
    if (!txt.isEmpty())
    {
     QDomElement elem =  createTextElement("toolTip",txt);
     element.appendChild(elem);
    }
    if (p->getDegrees()!=0) {
        element.setAttribute("degrees", QString("%1").arg(p->getDegrees()));
    }
}
/*public*/ QDomElement SaveXml::storeIcon(QString elemName, NamedIcon* icon) {
       if (icon==NULL) {
           return QDomElement();
       }
       QDomElement element = doc.createElement(elemName);
       element.setAttribute("url", icon->getURL().replace(":/", "program:"));
       element.setAttribute("degrees", QString("%1").arg(icon->getDegrees()));
       element.setAttribute("scale", QString("%1").arg(icon->getScale()));

       // the "rotate" attribute was deprecated in 2.9.4, replaced by the "rotation" element
// TODO:       element.addContent(doc.createElement("rotation").addContent(String.valueOf(icon.getRotation())));
       element.appendChild(createTextElement("rotation", QString("%1").arg(icon->getRotation())));

       return element;
   }
/**
 * Store the text formatting information.
 * <p>
 * This is always stored, even if the icon isn't in text mode,
 * because some uses (subclasses) of PositionableLabel flip
 * back and forth between icon and text, and want to remember their
 * formatting.
 */
/*protected*/ void SaveXml::storeTextInfo(PositionableLabel* p, QDomElement element) {
    //if (p->getText()!=NULL) element.setAttribute("text", p->getText());
    PositionablePopupUtil* util = p->getPopupUtility();
    element.setAttribute("size", QString("%1").arg(util->getFontSize()));
    element.setAttribute("style", QString("%1").arg(util->getFontStyle()));
    if (!(util->getForeground()==(QColor(Qt::black))))
    {
        element.setAttribute("red", QString("%1").arg(util->getForeground().red()));
        element.setAttribute("green", QString("%1").arg(util->getForeground().green()));
        element.setAttribute("blue", QString("%1").arg(util->getForeground().blue()));
    }
    if(p->isOpaque() || p->getSaveOpaque()){
        element.setAttribute("redBack", QString("%1").arg(util->getBackground().red()));
        element.setAttribute("greenBack", QString("%1").arg(util->getBackground().green()));
        element.setAttribute("blueBack", QString("%1").arg(util->getBackground().blue()));
    }
    if (util->getMargin()!=0)
        element.setAttribute("margin", QString("%1").arg(util->getMargin()));
    if (util->getBorderSize()!=0){
        element.setAttribute("borderSize", QString("%1").arg(util->getBorderSize()));
        element.setAttribute("redBorder", QString("%1").arg(util->getBorderColor().red()));
        element.setAttribute("greenBorder", QString("%1").arg(util->getBorderColor().green()));
        element.setAttribute("blueBorder", QString("%1").arg(util->getBorderColor().blue()));
    }
    if (util->getFixedWidth()!=0)
        element.setAttribute("fixedWidth", QString("%1").arg(util->getFixedWidth()));
    if (util->getFixedHeight()!=0)
        element.setAttribute("fixedHeight", QString("%1").arg(util->getFixedHeight()));

    QString just;
    switch (util->getJustification())
    {
     case 0x02 : just="right";
      break;
     case 0x04 : just ="centre";
      break;
     default :   just="left";
      break;
    }
    element.setAttribute("justification", just);

    if(util->getOrientation()!=PositionablePopupUtil::HORIZONTAL)
    {
     QString ori;
        switch (util->getOrientation()){
            case PositionablePopupUtil::VERTICAL_DOWN: ori="vertical_down";
                                                      break;
        case PositionablePopupUtil::VERTICAL_UP:   ori = "vertical_up";
                                                      break;
            default : ori = "horizontal";
                      break;
        }
        element.setAttribute("orientation", ori);
    }
    //return element;
}
/*protected*/ void SaveXml::storeIconInfo(SensorIcon* p, QDomElement element)
{
    element.appendChild(storeIcon("active", p->getIcon("SensorStateActive")));
    element.appendChild(storeIcon("inactive", p->getIcon("SensorStateInactive")));
    element.appendChild(storeIcon("unknown", p->getIcon("BeanStateUnknown")));
    element.appendChild(storeIcon("inconsistent", p->getIcon("BeanStateInconsistent")));
    QDomElement elem = doc.createElement("iconmaps");
    element.appendChild(elem);
    QString family = p->getFamily();
    if (family!=NULL) {
        elem.setAttribute("family", family);
    }
    //element.addContent(elem);
}
QDomElement SaveXml::storeLayoutTurnout(LayoutTurnout* p)
{
 QDomElement element = doc.createElement("layoutturnout");

 // include attributes
 element.setAttribute("ident", p->getName());
 if (p->getTurnoutName().length()>0) {
    element.setAttribute("turnoutname", p->getTurnoutName());
 }
 if (p->getSecondTurnoutName().length()>0)
 {
    element.setAttribute("secondturnoutname", p->getSecondTurnoutName());
 }
 if (p->getBlockName().length()>0) {
    element.setAttribute("blockname", p->getBlockName());
 }
 if (p->getBlockBName().length()>0) {
    element.setAttribute("blockbname", p->getBlockBName());
 }
 if (p->getBlockCName().length()>0) {
    element.setAttribute("blockcname", p->getBlockCName());
 }
if (p->getBlockDName().length()>0) {
    element.setAttribute("blockdname", p->getBlockDName());
}
element.setAttribute("type", QString("%1").arg(p->getTurnoutType()));
if(p->getHidden())
    element.setAttribute("hidden", QString("%1").arg(p->getHidden()?QString("yes"):QString("no")));
if (p->getConnectA()!=NULL) {
    element.setAttribute("connectaname", ((TrackSegment*)p->getConnectA())->getID());
}
if (p->getConnectB()!=NULL) {
    element.setAttribute("connectbname", ((TrackSegment*)p->getConnectB())->getID());
}
if (p->getConnectC()!=NULL) {
    element.setAttribute("connectcname", ((TrackSegment*)p->getConnectC())->getID());
}
if (p->getConnectD()!=NULL) {
    element.setAttribute("connectdname", ((TrackSegment*)p->getConnectD())->getID());
}
if (p->getSignalA1Name().length()>0) {
    element.setAttribute("signala1name", p->getSignalA1Name());
}
if (p->getSignalA2Name().length()>0) {
    element.setAttribute("signala2name", p->getSignalA2Name());
}
if (p->getSignalA3Name().length()>0) {
    element.setAttribute("signala3name", p->getSignalA3Name());
}
if (p->getSignalB1Name().length()>0) {
    element.setAttribute("signalb1name", p->getSignalB1Name());
}
if (p->getSignalB2Name().length()>0) {
    element.setAttribute("signalb2name", p->getSignalB2Name());
}
if (p->getSignalC1Name().length()>0) {
    element.setAttribute("signalc1name", p->getSignalC1Name());
}
if (p->getSignalC2Name().length()>0) {
    element.setAttribute("signalc2name", p->getSignalC2Name());
}
if (p->getSignalD1Name().length()>0) {
    element.setAttribute("signald1name", p->getSignalD1Name());
}
if (p->getSignalD2Name().length()>0) {
    element.setAttribute("signald2name", p->getSignalD2Name());
}
if (p->getLinkedTurnoutName().length()>0) {
    element.setAttribute("linkedturnoutname", p->getLinkedTurnoutName());
    element.setAttribute("linktype", QString("%1").arg(p->getLinkType()));
}

if(p->getSignalAMast().length()>0)
{
 QDomElement elem = doc.createElement("signalAMast");
 elem.setNodeValue(p->getSignalAMast());
 element.appendChild(elem);
}

if(p->getSignalBMast().length()>0)
{
    QDomElement elem = doc.createElement("signalBMast");
    elem.setNodeValue(p->getSignalBMast());
    element.appendChild(elem);
}
if(p->getSignalCMast().length()>0)
{
    QDomElement elem = doc.createElement("signalCMast");
    elem.setNodeValue(p->getSignalCMast());
    element.appendChild(elem);
}
if(p->getSignalDMast().length()>0)
{
    QDomElement elem = doc.createElement("signalDMast");
    elem.setNodeValue(p->getSignalDMast());
    element.appendChild(elem);

}

if(p->getSensorA().length()>0)
{
    //element.addContent(doc.createElement("sensorA").addContent(p->getSensorA()));
 QDomElement elem = doc.createElement("sensorA");
 elem.setNodeValue(p->getSensorA());
 element.appendChild(elem);
}

if(p->getSensorB().length()>0){
    //element.addContent(doc.createElement("sensorB").addContent(p->getSensorB()));
    QDomElement elem = doc.createElement("sensorB");
    elem.setNodeValue(p->getSensorB());
    element.appendChild(elem);
}
if(p->getSensorC().length()>0){
    //element.addContent(doc.createElement("sensorC").addContent(p->getSensorC()));
    QDomElement elem = doc.createElement("sensorC");
    elem.setNodeValue(p->getSensorC());
    element.appendChild(elem);
}
if(p->getSensorD().length()>0){
    //element.addContent(doc.createElement("sensorD").addContent(p->getSensorD()));
    QDomElement elem = doc.createElement("sensorD");
    elem.setNodeValue(p->getSensorD());
    element.appendChild(elem);
}

element.setAttribute("continuing", QString("%1").arg(p->getContinuingSense()));
element.setAttribute("disabled", QString("%1").arg(p->isDisabled()?QString("yes"):QString("no")));
element.setAttribute("disableWhenOccupied", QString("%1").arg(p->isDisabledWhenOccupied()?QString("yes"):QString("no")));
QPointF coords = p->getCoordsCenter();
element.setAttribute("xcen", (coords.x()));
element.setAttribute("ycen", (coords.y()));
coords = p->getCoordsB();
element.setAttribute("xb", (coords.x()));
element.setAttribute("yb", (coords.y()));
coords = p->getCoordsC();
element.setAttribute("xc", (coords.x()));
element.setAttribute("yc", (coords.y()));

element.setAttribute("class", "jmri.jmrit.display.configurexml.LayoutTurnoutXml");
return element;
}
QDomElement SaveXml::storeTrackSegment(TrackSegment* p)
{
 QDomElement element = doc.createElement("tracksegment");

 // include attributes
 element.setAttribute("ident", p->getID());
 if (p->getBlockName().length()>0) {
        element.setAttribute("blockname", p->getBlockName());
 }
 element.setAttribute("connect1name", p->getConnect1Name());
 element.setAttribute("type1", QString("%1").arg(p->getType1()));
 element.setAttribute("connect2name", p->getConnect2Name());
 element.setAttribute("type2", QString("%1").arg(p->getType2()));
 element.setAttribute("dashed", QString("%1").arg(p->getDashed()?QString("yes"):QString("no")));
 element.setAttribute("mainline", QString("%1").arg(p->getMainline()?QString("yes"):QString("no")));
 element.setAttribute("hidden", QString("%1").arg(p->getHidden()?QString("yes"):QString("no")));
 element.setAttribute("arc", QString("%1").arg(p->getArc()?QString("yes"):QString("no")));
 if(p->getArc())
 {
  element.setAttribute("flip", QString("%1").arg(p->getFlip()?QString("yes"):QString("no")));
  element.setAttribute("circle", QString("%1").arg(p->getCircle()?QString("yes"):QString("no")));
  if((p->getCircle())&& (p->getAngle()!=0.0))
   element.setAttribute("angle", QString("%1").arg(p->getAngle()));
 }
 element.setAttribute("class", "jmri.jmrit.display.configurexml.TrackSegmentXml");
 return element;
}
QDomElement SaveXml::storePositionablePoint(PositionablePoint* p)
{
 QDomElement element = doc.createElement("positionablepoint");

    element.setAttribute("ident", p->getID());
    element.setAttribute("type", QString("%1").arg(p->getType()));
    QPointF coords = p->getCoords();
    element.setAttribute("x", QString("%1").arg(coords.x()));
    element.setAttribute("y", QString("%1").arg(coords.y()));
    if (p->getConnect1() != NULL) {
        element.setAttribute("connect1name", p->getConnect1()->getID());
    }
    if (p->getConnect2() != NULL) {
        element.setAttribute("connect2name", p->getConnect2()->getID());
    }
    if ( (p->getEastBoundSignal()!=NULL) && (p->getEastBoundSignal().length()>0) ) {
        element.setAttribute("eastboundsignal", p->getEastBoundSignal());
    }
    if ( (p->getWestBoundSignal()!=NULL) && (p->getWestBoundSignal().length()>0) ) {
        element.setAttribute("westboundsignal", p->getWestBoundSignal());
    }

    if ( (p->getEastBoundSignalMast()!=NULL) && (p->getEastBoundSignalMast().length()>0) ) {
        element.setAttribute("eastboundsignalmast", p->getEastBoundSignalMast());
    }
    if ( (p->getWestBoundSignalMast()!=NULL) && (p->getWestBoundSignalMast().length()>0) ) {
        element.setAttribute("westboundsignalmast", p->getWestBoundSignalMast());
    }

    if ( (p->getEastBoundSensor()!=NULL) && (p->getEastBoundSensor().length()>0) ) {
        element.setAttribute("eastboundsensor", p->getEastBoundSensor());
    }
    if ( (p->getWestBoundSensor()!=NULL) && (p->getWestBoundSensor().length()>0) ) {
        element.setAttribute("westboundsensor", p->getWestBoundSensor());
    }

    element.setAttribute("class", "jmri.jmrit.display.configurexml.PositionablePointXml");
    return element;
}
QDomElement SaveXml::storeLevelXing(LevelXing* p)
{
 QDomElement element = doc.createElement("levelxing");

 // include attributes
 element.setAttribute("ident", p->getID());
 if (p->getBlockNameAC().length()>0) {
    element.setAttribute("blocknameac", p->getBlockNameAC());
 }
 if (p->getBlockNameBD().length()>0) {
    element.setAttribute("blocknamebd", p->getBlockNameBD());
 }
 if (p->getConnectA()!=NULL)
 {
    element.setAttribute("connectaname", ((TrackSegment*)p->getConnectA())->getID());
 }
 if (p->getConnectB()!=NULL) {
    element.setAttribute("connectbname", ((TrackSegment*)p->getConnectB())->getID());
 }
 if (p->getConnectC()!=NULL) {
    element.setAttribute("connectcname", ((TrackSegment*)p->getConnectC())->getID());
 }
 if (p->getConnectD()!=NULL) {
    element.setAttribute("connectdname", ((TrackSegment*)p->getConnectD())->getID());
 }
 if (p->getSignalAName().length()>0) {
    element.setAttribute("signalaname", p->getSignalAName());
 }
 if (p->getSignalBName().length()>0) {
    element.setAttribute("signalbname", p->getSignalBName());
 }
 if (p->getSignalCName().length()>0) {
    element.setAttribute("signalcname", p->getSignalCName());
 }
 if (p->getSignalDName().length()>0) {
    element.setAttribute("signaldname", p->getSignalDName());
 }
 QPointF coords = p->getCoordsCenter();
 element.setAttribute("xcen", QString("%1").arg(coords.x()));
 element.setAttribute("ycen", QString("%1").arg(coords.y()));
 coords = p->getCoordsA();
 element.setAttribute("xa", QString("%1").arg(coords.x()));
 element.setAttribute("ya", QString("%1").arg(coords.y()));
 coords = p->getCoordsB();
 element.setAttribute("xb", QString("%1").arg(coords.x()));
 element.setAttribute("yb", QString("%1").arg(coords.y()));

 if(p->getSignalAMastName().length()>0)
 {
  //element.addContent(doc.createElement("signalAMast").addContent(p->getSignalAMastName()));
  QDomElement elem = doc.createElement("signalAMast");
  elem.setNodeValue(p->getSignalAMastName());
  element.appendChild(elem);
}

 if(p->getSignalBMastName().length()>0)
 {
    //element.addContent(doc.createElement("signalBMast").addContent(p->getSignalBMastName()));
  QDomElement elem = doc.createElement("signalBMast");
  elem.setNodeValue(p->getSignalBMastName());
  element.appendChild(elem);
 }
 if(p->getSignalCMastName().length()>0){
    //element.addContent(doc.createElement("signalCMast").addContent(p->getSignalCMastName()));
  QDomElement elem = doc.createElement("signalCMast");
  elem.setNodeValue(p->getSignalCMastName());
  element.appendChild(elem);
 }
 if(p->getSignalDMastName().length()>0){
    //element.addContent(doc.createElement("signalDMast").addContent(p->getSignalDMastName()));
  QDomElement elem = doc.createElement("signalDMast");
  elem.setNodeValue(p->getSignalDMastName());
  element.appendChild(elem);
 }

 if(p->getSensorAName().length()>0)
 {
    //element.addContent(doc.createElement("sensorA").addContent(p->getSensorAName()));
  QDomElement elem = doc.createElement("sensorA");
  elem.setNodeValue(p->getSensorAName());
  element.appendChild(elem);
 }

 if(p->getSensorBName().length()>0)
 {
    //element.addContent(doc.createElement("sensorB").addContent(p->getSensorBName()));
  QDomElement elem = doc.createElement("sensorB");
  elem.setNodeValue(p->getSensorBName());
  element.appendChild(elem);
 }
 if(p->getSensorCName().length()>0)
 {
     //element.addContent(doc.createElement("sensorC").addContent(p->getSensorCName()));
  QDomElement elem = doc.createElement("sensorC");
  elem.setNodeValue(p->getSensorCName());
  element.appendChild(elem);
 }
 if(p->getSensorDName().length()>0)
 {
  // element.addContent(doc.createElement("sensorD").addContent(p->getSensorDName()));
  QDomElement elem = doc.createElement("sensorD");
  elem.setNodeValue(p->getSensorDName());
  element.appendChild(elem);
 }

 element.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LevelXingXml");
 return element;
}
QDomElement SaveXml::storeLayoutBlock(LayoutBlockManager* o)
{
    // TODO: Implement original LayoutBlockManagerXml class!
#if 0
 QDomElement layoutblocks = doc.createElement("layoutblocks");
 //setStoreElementClass(layoutblocks);
 layoutblocks.setAttribute("class", "jmri.jmrit.display.configurexml.LayoutBlockManagerXml");
 LayoutBlockManager* tm = (LayoutBlockManager*) o;
 if (tm->isAdvancedRoutingEnabled())
 {
  layoutblocks.setAttribute("blockrouting", "yes");
 }
 if(tm->getNamedStabilisedSensor()!=NULL)
 {
    layoutblocks.setAttribute("routingStablisedSensor", tm->getNamedStabilisedSensor()->getName());
 }

 //java.util.Iterator<QString> iter = tm.getSystemNameList().iterator();

 // don't return an element if there is nothing to include
// if (!iter.hasNext()) return NULL;

// while (iter.hasNext())
 for(int i = 0; i < tm->getSystemNameList().count(); i++)
 {
  QString sname = tm->getSystemNameList().at(i);
  if (sname==NULL) log.error("System name NULL during LayoutBlock store");
  log.debug("layoutblock system name is "+sname);
  LayoutBlock* b = tm->getBySystemName(sname);
  if (b->getUseCount()>0)
  {
   // save only those LayoutBlocks that are in use--skip abandoned ones
   QDomElement elem = doc.createElement("layoutblock");
   elem.setAttribute("systemName", sname);
   QDomElement elem2 = createTextElement("systemName", sname);
   elem.appendChild(elem2);
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
    if (b->getMemoryName() != "") {
        elem.setAttribute("memory", b->getMemoryName());
    }
    if(!b->useDefaultMetric())
    {
     //elem.addContent(doc.createElement("metric").addContent(QString("%1").arg(b.getBlockMetric()));
     QDomElement e2 = doc.createElement("metric");
     e2.setNodeValue(QString("%1").arg(b->getBlockMetric()));
     elem.appendChild(e2);
    }
  }
}
return (layoutblocks);
#else
    LayoutBlockManagerXml* xml = new LayoutBlockManagerXml();
    return(xml->store((QObject*)o));
#endif
}

///**
// * Subclass provides implementation to create the correct top
// * element, including the type information.
// * Default implementation is to use the local class here.
// * @param layoutblocks The top-level element being created
// */
///*public*/ void SaveXml::setStoreElementClass(QDomElement layoutblocks)
//{
// layoutblocks.setAttribute("class",
//                        "jmri.jmrit.display.configurexml.LayoutBlockManagerXml");
//}

/*protected*/ void SaveXml::storeCommon(NamedBean* t, QDomElement elem) {
    storeUserName((AbstractNamedBean*)t, elem);
    storeComment((AbstractNamedBean*)t, elem);
    storeProperties((AbstractNamedBean*)t, elem);
}
/* Store the comment parameter from a NamedBean
* @param t The NamedBean being stored
* @param elem The JDOM element for storing the NamedBean
*/
void SaveXml::storeComment(AbstractNamedBean* t, QDomElement elem) {
   // add comment, if present
   if (t->getComment() != NULL)
   {
    QDomElement c = doc.createElement("comment");
    c.appendChild(doc.createTextNode(t->getComment()));
    elem.appendChild(c);
   }
}
/**
 * Store the username parameter from a NamedBean.
 * <ul>
 * <li>Before 2.9.6, this was an attribute
 * <li>Starting in 2.9.6, this was stored as both attribute and element
 * <li>Starting in 3.1/2.11.1, this will be just an element
 * </ul>
 * @param t The NamedBean being stored
 * @param elem The JDOM element for storing the NamedBean
 */
void SaveXml::storeUserName(AbstractNamedBean* t, QDomElement elem)
{
 QString uname = t->getUserName();
 if (uname!=NULL && uname.length() > 0)
 {
  elem.setAttribute("userName", uname); // doing this for compatibility during 2.9.* series
        //elem.addContent(doc.createElement("userName").addContent(uname));
  //QDomElement e = createTextElement("userName",uname);
  QDomElement e = doc.createElement("userName");
  e.appendChild(doc.createTextNode(uname));
  elem.appendChild(e);
 }
}
/**
 * Store all key/value properties
 * @param t The NamedBean being loaded
 * @param elem The existing Element
 */
void SaveXml::storeProperties(AbstractNamedBean* t, QDomElement elem)
{
 QSet<QString> s = t->getPropertyKeys();
 if (s.isEmpty() || s.size() == 0) return;
 QDomElement ret = doc.createElement("properties");
 elem.appendChild(ret);
 foreach (QString key,  s)
 {
  QVariant value = t->getProperty(key);

  QDomElement p = doc.createElement("property");
  ret.appendChild(p);
  QDomElement e;
  p.appendChild(e=doc.createElement("key"));
  e.setAttribute("class", /*key.getClass().getName()*/"QString");
  //e.setText(key.toString()));
  e.appendChild(doc.createTextNode(key));
//  QDomElement e = doc.createElement("key");
//  e.setAttribute("class", key.typeName());
//  e.setText(key.toString());
//  p.appendChild(e);
  if (!value.isNull())
  {
   //p.addContent(doc.createElement("value")
   QDomElement e = doc.createElement("value");
   e.setAttribute("class", /*value.getClass().getName()*/value.typeName());
   //e.setText(value.toString());
   e.appendChild(doc.createTextNode(value.toString()));
  }
 }
}
void SaveXml::storeSensors(SensorManager *o)
{
#if 1
 ProxySensorManager* pt = (ProxySensorManager*)o;
 for(int i = 0; i < pt->nMgrs(); i++)
 {
  Manager* sMgr = pt->getMgr(i);
  if(qobject_cast<LnSensorManager*>(sMgr) != NULL)
  {
   LnSensorManagerXml* xml = new LnSensorManagerXml(this);
   root.appendChild(xml->store((QObject*)pt->getMgr(i)));
  }
  if(qobject_cast<RfidSensorManager*>(sMgr)!= NULL)
  {
   RfidSensorManagerXml* xml = new RfidSensorManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
  if(qobject_cast<InternalSensorManager*>(sMgr)!= NULL)
  {
   InternalSensorManagerXml* xml = new InternalSensorManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
 }

#else
 QDomElement sensors = doc.createElement("sensors");

 ProxySensorManager* mgr = (ProxySensorManager*)o;
 for(int i=0; i < mgr->nMgrs(); i++)
 {
  AbstractManager* sMgr = mgr->getMgr(i);
  if(qobject_cast<LnSensorManager*>(sMgr)!= NULL)
  {
   LnSensorManagerXml* xml = new LnSensorManagerXml(this);
   sensors.appendChild(xml->store((QObject*)sMgr));
  }
  if(qobject_cast<RfidSensorManager*>(sMgr)!= NULL)
  {
   RfidSensorManagerXml* xml = new RfidSensorManagerXml(this);
   sensors.appendChild(xml->store((QObject*)sMgr));
  }
  else if(qobject_cast<InternalSensorManager*>(sMgr)!= NULL)
  {
   InternalSensorManagerXml* xml = new InternalSensorManagerXml(this);
   sensors.appendChild(xml->store((QObject*)sMgr));
  }
 }
 return sensors;
#endif
}
QDomElement SaveXml::createTextElement(QString tagName, QString text)
{
 QDomElement eText = doc.createElement(tagName);
 QDomText t = doc.createTextNode(text);
 eText.appendChild(t);
 return eText;
}

//        /**
//         * Subclass provides implementation to create the correct top
//         * element, including the type information.
//         * Default implementation is to use the local class here.
//         * @param sensors The top-level element being created
//         */
//        abstract public void setStoreElementClass(Element sensors);

void SaveXml::storeReporters(ReporterManager* o)
{
 QDomElement reporters = doc.createElement("reporters");
 //setStoreElementClass(reporters);
 //reporters.setAttribute("class", "jmri.managers.configurexml.InternalReporterManagerXml");
 ProxyReporterManager* tm = (ProxyReporterManager*) o;
// if (tm!=NULL)
// {
//  //java.util.Iterator<String> iter =
//  //                      tm.getSystemNameList().iterator();

//  // don't return an element if there are not reporters to include
//  if (tm->getSystemNameList().isEmpty()) return QDomElement();

//  // store the reporters
//  //while (iter.hasNext()) {
//  for(int i=0; i < tm->getSystemNameList().count(); i++)
//  {
//   QString sname = tm->getSystemNameList().at(i);
//   if (sname=="") log.error("System name NULL during store");
//   log.debug("system name is "+sname);
//   Reporter* r = tm->getBySystemName(sname);
//   QDomElement elem = doc.createElement("reporter");
//   elem.setAttribute("systemName", sname); // deprecated for 2.9.* series
//   elem.appendChild(createTextElement("systemName",sname));
//   // store common parts
//   storeCommon(r, elem);

//   log.debug("store Reporter "+sname);
//   reporters.appendChild(elem);
//  }
 for(int i=0; i < tm->nMgrs(); i++)
 {
  Manager* sMgr = tm->getMgr(i);
  if(qobject_cast<LnReporterManager*>(sMgr)!= NULL)
  {
   LnReporterManagerXml* xml = new LnReporterManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
  if(qobject_cast<RfidSensorManager*>(sMgr)!= NULL)
  {
   RfidReporterManagerXml* xml = new RfidReporterManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
  else if(qobject_cast<InternalReporterManager*>(sMgr)!= NULL)
  {
   InternalReporterManagerXml* xml = new InternalReporterManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
 }
}

QDomElement SaveXml::storeMemories(MemoryManager* o)
{
#if 0
 QDomElement memories = doc.createElement("memories");
 //setStoreElementClass(memories);
 memories.setAttribute("class", "jmri.managers.configurexml.DefaultMemoryManagerXml");
 DefaultMemoryManager* tm = (DefaultMemoryManager*) o;
 if (tm!=NULL)
 {
  //java.util.Iterator<String> iter =
//                            tm.getSystemNameList().iterator();

  // don't return an element if there are not memories to include
     if (tm->getSystemNameList().isEmpty()) return QDomElement();

  // store the memories
  //while (iter.hasNext()) {
  for(int i=0; i < tm->getSystemNameList().count(); i++)
  {
   QString sname = tm->getSystemNameList().at(i);
   if (sname=="NULL""") log.error("System name NULL during store");
   log.debug("system name is "+sname);
   Memory* m = tm->getBySystemName(sname);
   QDomElement elem = doc.createElement("memory");
   elem.setAttribute("systemName", sname);
   elem.appendChild(createTextElement("systemName",sname));

   // store common part
   storeCommon(m, elem);
   // store value if non-NULL; NULL values omitted
   QVariant obj = ((AbstractMemory*)m)->getValue();
   if (!obj.isNull())
   {
    //if(obj instanceof jmri.jmrit.roster.RosterEntry)
    //if(qobject_cast<RosterEntry*>(obj)!=NULL)
    RosterEntry* re = VPtr<RosterEntry>::asPtr(obj);
    if(re != NULL)
    {
     //QString valueClass = obj.getClass().getName();
     QString valueClass = re->metaObject()->className();
     QString value = re->getId();
     elem.setAttribute("value", value);
     elem.setAttribute("valueClass", valueClass);
    }
    else
    {
     //QString value = obj->toString();
     QString value = obj.toString();
     elem.setAttribute("value", value);
    }
   }
   log.debug("store Memory "+sname);
   memories.appendChild(elem);
  }
 }
 return memories;
#else
 DefaultMemoryManagerXml* xml = new DefaultMemoryManagerXml(this);
 return xml->store((QObject*)o);
#endif
}

QDomElement SaveXml::storeTurnouts(TurnoutManager* o)
{
#if 0
 QDomElement turnouts = doc.createElement("turnouts");
 //setStoreElementClass(turnouts);
 turnouts.setAttribute("class", "jmri.managers.configurexml.InternalTurnoutManagerXml");
 ProxyTurnoutManager* tm = (ProxyTurnoutManager*) o;
 if (tm!=NULL)
 {
  TurnoutOperationManagerXml* tomx = new TurnoutOperationManagerXml();
  QDomElement opElem = tomx->store(doc, TurnoutOperationManager::getInstance());
  turnouts.appendChild(opElem);

  QStringListIterator iter( tm->getSystemNameList());
  // don't return an element if there are not turnouts to include
  if (!iter.hasNext()) return QDomElement();

  QString defaultclosed = tm->getDefaultClosedSpeed();
  QString defaultthrown = tm->getDefaultThrownSpeed();
  QDomElement defaultclosedspeed = doc.createElement("defaultclosedspeed");
  defaultclosedspeed.appendChild(doc.createTextNode(defaultclosed));
  turnouts.appendChild(defaultclosedspeed);
  QDomElement defaultthrownspeed = doc.createElement("defaultthrownspeed");
  defaultthrownspeed.appendChild(doc.createTextNode(defaultthrown));
  turnouts.appendChild(defaultthrownspeed);

  // store the turnouts
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname.isEmpty()) log.error("System name NULL during store");
   log.debug("system name is "+sname);
   Turnout* t = tm->getBySystemName(sname);
   QDomElement elem = doc.createElement("turnout");
   elem.setAttribute("systemName", sname); // deprecated for 2.9.* series
   QDomElement e = doc.createElement("systemName");
   e.appendChild(doc.createTextNode(sname));
   elem.appendChild(e);
   log.debug("store turnout "+sname);

   storeCommon(t, elem);

   // include feedback info
   elem.setAttribute("feedback", ((AbstractTurnout*)t)->getFeedbackModeName());
   NamedBeanHandle<Sensor*>* s;
   s = ((AbstractTurnout*)t)->getFirstNamedSensor();
   if (s!=NULL) elem.setAttribute("sensor1", s->getName());
   s = ((AbstractTurnout*)t)->getSecondNamedSensor();
   if (s!=NULL) elem.setAttribute("sensor2", s->getName());

   // include turnout inverted
   elem.setAttribute("inverted", ((AbstractTurnout*)t)->getInverted()?"true":"false");

   if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT | Turnout::PUSHBUTTONLOCKOUT))
   {
    // include turnout locked
    elem.setAttribute("locked", ((AbstractTurnout*)t)->getLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT)?"true":"false");
    // include turnout lock mode
    QString lockOpr;
    if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT) && ((AbstractTurnout*)t)->canLock(Turnout::PUSHBUTTONLOCKOUT)){
     lockOpr = "both";
   }
   else if (((AbstractTurnout*)t)->canLock(Turnout::CABLOCKOUT))
   {
    lockOpr = "cab";
   }
   else if (((AbstractTurnout*)t)->canLock(Turnout::PUSHBUTTONLOCKOUT))
   {
    lockOpr = "pushbutton";
   }
   else
   {
    lockOpr = "none";
   }
   elem.setAttribute("lockMode", lockOpr);
   // include turnout decoder
   elem.setAttribute("decoder", ((AbstractTurnout*)t)->getDecoderName());
  }

  // include number of control bits, if different from one
  int iNum = ((AbstractTurnout*)t)->getNumberOutputBits();
  if (iNum!=1) elem.setAttribute("numBits",iNum);

  // include turnout control type, if different from 0
  int iType = ((AbstractTurnout*)t)->getControlType();
  if (iType!=0) elem.setAttribute("controlType",iType);

  // add operation stuff
  QString opstr = NULL;
  TurnoutOperation* op = ((AbstractTurnout*)t)->getTurnoutOperation();
  if (((AbstractTurnout*)t)->getInhibitOperation())
  {
   opstr = "Off";
  }
  else if (op==NULL)
  {
   opstr = "Default";
  }
  else if (op->isNonce())
  {	// nonce operation appears as subelement
   TurnoutOperationXml* adapter = TurnoutOperationXml::getAdapter(op);
   if (adapter != NULL)
   {
    QDomElement nonceOpElem = adapter->store(doc,op);
    if (!nonceOpElem.isNull())
    {
     elem.appendChild(nonceOpElem);
    }
   }
  }
  else
  {
   opstr = op->getName();
  }
  if (opstr != NULL)
  {
   elem.setAttribute("automate", opstr);
  }
  if((((AbstractTurnout*)t)->getDivergingSpeed()!=NULL) && (((AbstractTurnout*)t)->getDivergingSpeed()!=("")) && !((AbstractTurnout*)t)->getDivergingSpeed().contains("Global"))
  {
   QDomElement e = doc.createElement("divergingSpeed");
   e.appendChild(doc.createTextNode(((AbstractTurnout*)t)->getDivergingSpeed()));
   elem.appendChild(e);
  }
  if((((AbstractTurnout*)t)->getStraightSpeed()!=NULL) && (((AbstractTurnout*)t)->getStraightSpeed()!=("")) && !((AbstractTurnout*)t)->getStraightSpeed().contains("Global"))
  {
   QDomElement e = doc.createElement("straightSpeed");
   e.appendChild(doc.createTextNode(((AbstractTurnout*)t)->getStraightSpeed()));
   elem.appendChild(e);
  }

  // add element
  turnouts.appendChild(elem);

  }
 }
 return turnouts;
#else
    ProxyTurnoutManager* pt = (ProxyTurnoutManager*)o;
 InternalTurnoutManagerXml* xml = new InternalTurnoutManagerXml(this);
 return xml->store((QObject*)pt->getMgr(1));
#endif
}
QDomElement SaveXml::storeRoutes(RouteManager *o)
{
#if 0
 QDomElement routes = doc.createElement("routes");
 //setStoreElementClass(routes);
 routes.setAttribute("class", "jmri.managers.configurexml.DefaultRouteManagerXml");
 DefaultRouteManager* tm = (DefaultRouteManager*) o;
 if (tm!=NULL)
 {
  //java.util.Iterator<String> iter = tm.getSystemNameList().iterator();
  QStringListIterator iter(tm->getSystemNameList());

  // don't return an element if there are not routes to include
  if (!iter.hasNext()) return QDomElement();

  // store the routes
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname.isNull()) log.error("System name null during store");
   log.debug("system name is "+sname);
   DefaultRoute* r = (DefaultRoute*)tm->getBySystemName(sname);
   QString cTurnout = r->getControlTurnout();
   int addedDelay = r->getRouteCommandDelay();
   bool routeLocked = r->getLocked();
   QString cLockTurnout = r->getLockControlTurnout();

   QDomElement elem =doc.createElement("route");
   elem.setAttribute("systemName", sname);
   QDomElement e = doc.createElement("systemName");
   e.appendChild(doc.createTextNode(sname));
   elem.appendChild(e);

   // store common parts
   storeCommon(r, elem);

   if (!cTurnout.isNull() && cTurnout!="")
   {
    elem.setAttribute("controlTurnout", cTurnout);
    int state = r->getControlTurnoutState();
    if (state == Route::ONTHROWN)
    {
     elem.setAttribute("controlTurnoutState","THROWN");
    }
    else if (state == Route::ONCHANGE)
    {
     elem.setAttribute("controlTurnoutState","CHANGE");
    }
    else if (state == Route::VETOCLOSED)
    {
     elem.setAttribute("controlTurnoutState","VETOCLOSED");
    }
    else if (state == Route::VETOTHROWN)
    {
     elem.setAttribute("controlTurnoutState","VETOTHROWN");
    }
    else
    {
     elem.setAttribute("controlTurnoutState","CLOSED");
    }
   }
   if (!cLockTurnout.isNull() && cLockTurnout!="")
   {
    elem.setAttribute("controlLockTurnout", cLockTurnout);
    int state = r->getLockControlTurnoutState();
    if (state == Route::ONTHROWN)
    {
     elem.setAttribute("controlLockTurnoutState","THROWN");
    }
    else if (state == Route::ONCHANGE)
    {
     elem.setAttribute("controlLockTurnoutState","CHANGE");
    }
    else
    {
     elem.setAttribute("controlLockTurnoutState","CLOSED");
    }
   }
   if (addedDelay>0)
   {
    elem.setAttribute("addedDelay",addedDelay);
   }

   if (routeLocked)
   {
    elem.setAttribute("routeLocked","True");
   }
   // add route output Turnouts, if any
   int index = 0;
   QString rTurnout = "";
   while ( (rTurnout = r->getOutputTurnoutByIndex(index)) != "")
   {
    QDomElement rElem = doc.createElement("routeOutputTurnout");
    rElem.setAttribute("systemName", rTurnout);
    QString sState = "CLOSED";
    if (r->getOutputTurnoutSetState(rTurnout)==Turnout::THROWN)
    {
     sState = "THROWN";
    }
    else if (r->getOutputTurnoutSetState(rTurnout)==Route::TOGGLE)
    {
     sState = "TOGGLE";
    }
    rElem.setAttribute("state", sState);
    elem.appendChild(rElem);
    index ++;
   }
   // add route output Sensors, if any
   index = 0;
   QString rSensor = "";
   while ( (rSensor = r->getOutputSensorByIndex(index)) != "")
   {
    QDomElement rElem = doc.createElement("routeOutputSensor");
    rElem.setAttribute("systemName", rSensor);
    QString sState = "INACTIVE";
    if (r->getOutputSensorSetState(rSensor)==Sensor::ACTIVE)
    {
     sState = "ACTIVE";
    }
    else if (r->getOutputSensorSetState(rSensor)==Route::TOGGLE)
    {
     sState = "TOGGLE";
    }
    rElem.setAttribute("state", sState);
    elem.appendChild(rElem);
    index ++;
   }
   // add route control Sensors, if any
   index = 0;
   //rSensor = null;	// previous while forces rSensor to null
   while ( (rSensor = r->getRouteSensorName(index)) != "")
   {
    QDomElement rsElem = doc.createElement("routeSensor");
    rsElem.setAttribute("systemName", rSensor);
    int mode = r->getRouteSensorMode(index);
    QString modeName;
    switch (mode)
    {
     case Route::ONACTIVE:
      modeName = "onActive";
      break;
     case Route::ONINACTIVE:
      modeName = "onInactive";
      break;
     case Route::ONCHANGE:
      modeName = "onChange";
      break;
     case Route::VETOACTIVE:
      modeName = "vetoActive";
      break;
     case Route::VETOINACTIVE:
      modeName = "vetoInactive";
      break;
     default:
      modeName = "";
    }
    if (modeName.isEmpty()) rsElem.setAttribute("mode", modeName);
    elem.appendChild(rsElem);
    index ++;
   }
   // add sound and script file elements if needed
   if (!r->getOutputSoundName().isNull() && r->getOutputSoundName()!=(""))
   {
    QDomElement rsElem = doc.createElement("routeSoundFile");
    rsElem.setAttribute("name", FileUtil::getPortableFilename( new File(r->getOutputSoundName())) );
    elem.appendChild(rsElem);
   }
   if (!r->getOutputScriptName().isNull() && r->getOutputScriptName()!=(""))
   {
    QDomElement rsElem = doc.createElement("routeScriptFile");
    rsElem.setAttribute("name", FileUtil::getPortableFilename(new File(r->getOutputScriptName())) );
    elem.appendChild(rsElem);
   }

   // add turnouts aligned sensor if there is one
   if (r->getTurnoutsAlignedSensor()!=(""))
   {
    QDomElement rsElem = doc.createElement("turnoutsAlignedSensor");
    rsElem.setAttribute("name", r->getTurnoutsAlignedSensor());
    elem.appendChild(rsElem);
   }

   log.debug("store route "+sname);
   routes.appendChild(elem);
  }
 }
 return routes;
#else
 DefaultRouteManagerXml* xml = new DefaultRouteManagerXml(this);
 return xml->store((QObject*)o);
#endif
}
QDomElement SaveXml::storeBlocks(BlockManager *o)
{
 BlockManagerXml* xml = new BlockManagerXml(this);
 return xml->store(o);
}
void SaveXml::storeLights(LightManager *l)
{
#if 0
 AbstractLightManagerConfigXML* xml = new AbstractLightManagerConfigXML(this);
 xml->setDoc(doc);
 root.appendChild( xml->store((QObject*)l);
#else
 ProxyLightManager* pt = (ProxyLightManager*)l;
 for(int i = 0; i < pt->nMgrs(); i++)
 {
  Manager* sMgr = pt->getMgr(i);
  if(qobject_cast<LnLightManager*>(sMgr) != NULL)
  {
   LnLightManagerXml* xml = new LnLightManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
  if(qobject_cast<InternalLightManager*>(sMgr)!= NULL)
  {
   InternalLightManagerXml* xml = new InternalLightManagerXml(this);
   root.appendChild(xml->store((QObject*)sMgr));
  }
 }
#endif
}


QDomElement SaveXml::storeTimebase(Timebase* t)
{
 SimpleTimebaseXml* xml = new SimpleTimebaseXml(this);
 xml->setDoc(doc);
 return xml->store((QObject*)t);
}
QDomElement SaveXml::storeSignalHeads(SignalHeadManager *s)
{
 AbstractSignalHeadManagerXml* xml = new AbstractSignalHeadManagerXml(this);
 xml->setDoc(doc);
 return xml->store((QObject*)s);
}
QDomElement SaveXml::storeSignalMasts(SignalMastManager *s)
{
 DefaultSignalMastManagerXml* xml = new DefaultSignalMastManagerXml(this);
 xml->setDoc(doc);
 return xml->store((QObject*)s);
}
QDomElement SaveXml::storeSignalMastLogic(SignalMastLogicManager *s)
{
 DefaultSignalMastLogicManagerXml* xml = new   DefaultSignalMastLogicManagerXml(this);
 xml->setDoc(doc);
 return xml->store((QObject*)s);
}
QDomElement SaveXml::storeBlockBossLogic(QObject* o)
{
 BlockBossLogicXml* xml = new BlockBossLogicXml(this);
 xml->setDoc(doc);
 return xml->store((QObject*)o);
}
QDomElement SaveXml::storeLnTurnouts(TurnoutManager *t)
{
 ProxyTurnoutManager* pt = (ProxyTurnoutManager*)t;
 LnTurnoutManagerXml* xml = new LnTurnoutManagerXml();
 return xml->store((QObject*)pt->mgrs.at(0));
}
QDomElement SaveXml::storeLogix(LogixManager *m)
{
 DefaultLogixManagerXml* xml = new DefaultLogixManagerXml();
 return xml->store((QObject*)m);
}
QDomElement SaveXml::storeAudio(DefaultAudioManager *m)
{
 DefaultAudioManagerXml* xml = new DefaultAudioManagerXml();
 return xml->store((QObject*)m);
}
QDomElement SaveXml::storeConditionals(ConditionalManager *m)
{
 DefaultConditionalManagerXml* xml = new DefaultConditionalManagerXml();
 return xml->store((QObject*)m);
}
QDomElement SaveXml::storeOBlocks(QObject *m)
{
 OBlockManagerXml* xml = new OBlockManagerXml();
 return xml->store(m);
}
QDomElement SaveXml::storeWarrants(QObject *m)
{
 WarrantManagerXml* xml = new WarrantManagerXml();
 return xml->store(m);
}
QDomElement SaveXml::storeEntryExit(QObject *m)
{
 EntryExitPairsXml* xml = new EntryExitPairsXml();
 return xml->store(m);
}
QDomElement SaveXml::storeSignalGroups(QObject *m)
{
 DefaultSignalGroupManagerXml* xml = new DefaultSignalGroupManagerXml();
 return xml->store(m);
}
QDomElement SaveXml::storeSections(QObject *m)
{
 SectionManagerXml* xml = new SectionManagerXml();
 return xml->store(m);
}
QDomElement SaveXml::storeSlipTurnouts(QObject *m)
{
 LayoutSlipXml* xml = new LayoutSlipXml();
 return xml->store(m);
}
QDomElement SaveXml::storeTurntables(QObject *m)
{
 LayoutTurntableXml* xml = new LayoutTurntableXml();
 return xml->store(m);
}
