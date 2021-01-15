#include "controlpaneleditorxml.h"
#include "controlpaneleditor.h"
#include "panelmenu.h"
#include "instancemanager.h"
#include <QMenuBar>
#include "positionablelabelxml.h"
#include "sensoriconxml.h"
#include "memoryspinnericonxml.h"
#include "analogclock2displayxml.h"
#include "memorycomboiconxml.h"
#include "memoryinputiconxml.h"
#include "indicatorturnouticonxml.h"
#include "indicatortrackiconxml.h"
#include "positionablecirclexml.h"
#include "positionableellipsexml.h"
#include "positionablerectanglexml.h"
#include "positionableroundrectxml.h"
#include "signalmasticonxml.h"
#include "portalicon.h"
#include "class.h"
#include "guilafpreferencesmanager.h"
#include "userpreferencesmanager.h"

ControlPanelEditorXml::ControlPanelEditorXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("ControlPanelEditorXml");
}
ControlPanelEditorXml::~ControlPanelEditorXml()
{
 delete log;
}

/**
 * Handle configuration for {@link ControlPanelEditor} panes.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 21525 $
 */
///*public*/ class ControlPanelEditorXml extends AbstractXmlAdapter {

//    /*public*/ ControlPanelEditorXml() {}

/**
 * Default implementation for storing the contents of a
 * ControlPanelEditor
 * @param o QObject* to store, of type ControlPanelEditor
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement ControlPanelEditorXml::store(QObject* o)
{
 ControlPanelEditor* p = (ControlPanelEditor*)o;
 QDomElement panel = doc.createElement("paneleditor");

 JFrame* frame = p->getTargetFrame();
 QSize size = frame->size();
    //QPoint posn = frame->getLocation();
 QPoint posn = QPoint(p->geometry().x(), p->geometry().y());

 panel.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.configurexml.ControlPanelEditorXml");
 panel.setAttribute("name", p->getName()); // frame->getName());
 panel.setAttribute("x", posn.x());
 panel.setAttribute("y", posn.y());
 panel.setAttribute("height", size.height());
 panel.setAttribute("width", size.width());
 panel.setAttribute("editable", (p->isEditable()?"yes":"no"));
 panel.setAttribute("positionable", (p->allPositionable()?"yes":"no"));
    //panel.setAttribute("showcoordinates", (p->showCoordinates()?"yes":"no"));
 panel.setAttribute("showtooltips", (p->showToolTip()?"yes":"no"));
 panel.setAttribute("controlling", (p->allControlling()?"yes":"no"));
 panel.setAttribute("hide", p->isVisible()?"no":"yes");
 panel.setAttribute("panelmenu", frame->menuBar()->isVisible()?"yes":"no");
 panel.setAttribute("scrollable", p->getScrollable());
 if (p->getBackgroundColor()!=QColor())
 {
  panel.setAttribute("redBackground", p->getBackgroundColor().red());
  panel.setAttribute("greenBackground", p->getBackgroundColor().green());
  panel.setAttribute("blueBackground", p->getBackgroundColor().blue());
 }
 panel.setAttribute("shapeSelect",  (p->getShapeSelect() ? "yes" : "no"));

 QDomElement elem = doc.createElement("icons");
 QMap<QString, NamedIcon*>* map = p->getPortalIconMap();
 elem.appendChild(storeIcon("visible", map->value(PortalIcon::VISIBLE)));
 elem.appendChild(storeIcon("path_edit", map->value(PortalIcon::PATH)));
 elem.appendChild(storeIcon("hidden", map->value(PortalIcon::HIDDEN)));
 elem.appendChild(storeIcon("to_arrow", map->value(PortalIcon::TO_ARROW)));
 elem.appendChild(storeIcon("from_arrow", map->value(PortalIcon::FROM_ARROW)));
 panel.appendChild(elem);

 // include contents
 QList <Positionable*> contents = p->getContents();
 if (log->isDebugEnabled()) log->debug("N elements: "+contents.size());
 for (int i=0; i<contents.size(); i++)
 {
  Positionable* sub = contents.at(i);
  if (sub!=NULL && sub->storeItem())
  {
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub->self());
    if (!e.isNull()) panel.appendChild(e);
   }
   catch (Exception e)
   {
    log->error("Error storing panel element: "+e.getMessage());
                //e.printStackTrace();
   }
  }
 }
 return panel;
}

/*public*/ QDomElement ControlPanelEditorXml::storeIcon(QString elemName, NamedIcon* icon)
{
 if (icon == NULL)
 {
  return QDomElement();
 }
 QDomElement element = doc.createElement(elemName);
 QDomElement url = doc.createElement("url");
 url.appendChild(doc.createTextNode(icon->getURL()));
 element.appendChild(url);
 return element;
}
/*public*/ void ControlPanelEditorXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log->error("Invalid method called");
}

/**
 * Create a ControlPanelEditor object, then
 * register and fill it, then pop it in a JFrame
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool ControlPanelEditorXml::load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException)
{
 bool result = true;
 // find coordinates
 int x = 0;
 int y = 0;
 int height = 400;
 int width = 300;
 try {
     x = shared.attribute("x").toInt();
     y = shared.attribute("y").toInt();
     height = shared.attribute("height").toInt();
     width = shared.attribute("width").toInt();
 } catch ( DataConversionException e) {
     log->error("failed to convert ControlPanelEditor's attribute");
     result = false;
 }
 // find the name
 QString name = "Control Panel";
 if (shared.attribute("name")!=NULL)
     name = shared.attribute("name");
 // confirm that panel hasn't already been loaded
 if(((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name)){
     log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
     result = false;
 }

 // If available, override location and size with machine dependent values
 if (!((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize()) {
     UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");
     if (prefsMgr != nullptr) {
         QString windowFrameRef = "jmri.jmrit.display.controlPanelEditor.ControlPanelEditor:" + name;

         QPoint prefsWindowLocation = prefsMgr->getWindowLocation(windowFrameRef);
         if (!prefsWindowLocation.isNull()) {
             x = (int) prefsWindowLocation.x();
             y = (int) prefsWindowLocation.y();
         }

         QSize prefsWindowSize = prefsMgr->getWindowSize(windowFrameRef);
         if (!prefsWindowSize.isNull() && prefsWindowSize.height() >= 0 && prefsWindowSize.width() >= 0) {
             height = (int) prefsWindowSize.height();
             width = (int) prefsWindowSize.width();
         }
     }
 }

 ControlPanelEditor* panel = new ControlPanelEditor(name);
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);
 panel->getTargetFrame()->move(x,y);
 panel->getTargetFrame()->resize(width,height);

 // Load editor option flags. This has to be done before the content
 // items are loaded, to preserve the individual item settings
 QString a;
 bool value = true;
 if ((a = shared.attribute("editable"))!=NULL && a==("no"))
     value = false;
 panel->setAllEditable(value);

 value = true;
 if ((a = shared.attribute("positionable"))!=NULL && a==("no"))
     value = false;
 panel->setAllPositionable(value);

 /*
 value = false;
 if ((a = element.attribute("showcoordinates"))!=NULL && a==("yes"))
     value = true;
 panel.setShowCoordinates(value);
 */

 value = true;
 if ((a = shared.attribute("showtooltips"))!=NULL && a==("no"))
     value = false;
 panel->setAllShowToolTip(value);

 value = true;
 if ((a = shared.attribute("controlling"))!=NULL && a==("no"))
     value = false;
 panel->setAllControlling(value);

 value = false;
 if ((a = shared.attribute("hide"))!=NULL && a==("yes"))
     value = true;
 panel->setShowHidden(value);

 value = true;
 if ((a = shared.attribute("panelmenu"))!=NULL && a==("no"))
     value = false;
 panel->setPanelMenuVisible(value);

 value = true;

 if ((a = shared.attribute("shapeSelect")) != "" && a==("no"))
 {
  value = false;
 }
 panel->setShapeSelect(value);

 if ((a = shared.attribute("state"))!=NULL) {
  bool bOk;
      int xState = a.toInt(&bOk);
//            panel->setExtendedState(xState);
  if(!bOk) {
      log->error("failed to convert ControlPanelEditor's extended State");
      result = false;
  }
 }

 QString state = "both";
 if ((a = shared.attribute("scrollable"))!=NULL)
     state = a;
     panel->setScroll(state);
 bool bOk = true;
 bool bok;
     int red = shared.attribute("redBackground","215").toInt(&bok);
     if(!bok)  bOk = false;
     int blue = shared.attribute("blueBackground","214").toInt(&bok);
     if(!bok)  bOk = false;
     int green = shared.attribute("greenBackground","213").toInt(&bok);
     if(!bok)  bOk = false;
     panel->setBackgroundColor( QColor(red, green, blue));
  if(!bOk)
  {
     log->warn("Could not parse color attributes!");
  } /*catch ( NullPointerException e) {  // considered normal if the attributes are not present
 }*/

 QDomElement icons = shared.firstChildElement("icons");
 if (icons != QDomElement())
 {
  QMap<QString, NamedIcon*>* portalIconMap = new QMap<QString, NamedIcon*>();
  portalIconMap->insert(PortalIcon::VISIBLE, loadIcon("visible", icons, panel));
  portalIconMap->insert(PortalIcon::PATH, loadIcon("path_edit", icons, panel));
  portalIconMap->insert(PortalIcon::HIDDEN, loadIcon("hidden", icons, panel));
  portalIconMap->insert(PortalIcon::TO_ARROW, loadIcon("to_arrow", icons, panel));
  portalIconMap->insert(PortalIcon::FROM_ARROW, loadIcon("from_arrow", icons, panel));
  panel->setDefaultPortalIcons(portalIconMap);
 }
 //element.removeAttribute("icons");
 shared.removeChild(icons);

 //set the (global) editor display widgets to their flag settings
 panel->initView();

 // load the contents
 QDomNodeList items = shared.childNodes();
 for (int i = 0; i<items.size(); i++)
 {
  // get the class, hence the adapter object to do loading
  QDomElement item = items.at(i).toElement();
  QString adapterName = item.attribute("class");
  if(adapterName == "")
  {
   log->warn(tr("element %1 has no class ").arg(item.tagName()));
   continue;
  }
  else
   log->debug("load via "+adapterName);
  XmlAdapter* adapter = nullptr;
  QString aName = adapterName.mid(adapterName.lastIndexOf(".") +1);

  try
  {
#if 0

//            XmlAdapter* adapter = (XmlAdapter)Class.forName(adapterName).newInstance();
   int typeId = QMetaType::type(aName.toLocal8Bit());
   if(typeId > 0)
   {
  #if QT_VERSION < 0x050000
    adapter = (XmlAdapter*)QMetaType::construct(typeId);
  #else
    adapter = (XmlAdapter*)QMetaType::create(typeId);
  #endif
   }
#else
   adapter = (XmlAdapter*)Class::forName(aName)->newInstance();
#endif
    if(adapter != NULL && qobject_cast<XmlAdapter*>(adapter) != NULL)
    {
     adapter->load(item, panel);
     if (!panel->loadOK())
     {
      result = false;
     }
   }
   else
   {
    if(adapterName == "jmri.jmrit.display.configurexml.PositionableLabelXml")
        adapter = new PositionableLabelXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.SensorIconXml")
        adapter = new SensorIconXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.AnalogClock2DisplayXml")
        adapter = new AnalogClock2DisplayXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.MemoryComboIconXml")
        adapter = new MemoryComboIconXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.MemorySpinnerIconXml")
        adapter = new MemorySpinnerIconXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.MemoryInputIconXml")
        adapter = new MemoryInputIconXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.IndicatorTrackIconXml")
        adapter = new IndicatorTrackIconXml();
    else if(adapterName == "jmri.jmrit.display.configurexml.IndicatorTurnoutIconXml")
        adapter = new IndicatorTurnoutIconXml();
    else if(adapterName == "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableCircleXml")
        adapter = new PositionableCircleXml();
    else if(adapterName == "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableEllipseXml")
        adapter = new PositionableEllipseXml();
    else if(adapterName == "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableRectangleXml")
        adapter = new PositionableRectangleXml();
    else if(adapterName == "jmri.jmrit.display.controlPanelEditor.shape.configurexml.PositionableRoundRectXml")
        adapter = new PositionableRoundRectXml();
    else
    {
        log->error(tr("no adapter for %1").arg(adapterName));
        result = false;
        return result;
    }
    adapter->load(item, panel);
    if (!panel->loadOK())
    {
     result = false;
    }
   }
  }
  catch (Exception e)
  {
   log->error("Exception while loading "+item.tagName()+":"+e.getMessage());
   result = false;
   //e.printStackTrace();
  }
 }

 panel->disposeLoadData();     // dispose of url correction data

 // display the results, with the editor in back
 panel->adjustSize();
 panel->setAllEditable(panel->isEditable());

 // we don't pack the target frame here, because size was specified
 // TODO: Work out why, when calling this method, panel size is increased
 // vertically (at least on MS Windows)
 panel->getTargetFrame()->setVisible(true);    // always show the panel

 // register the resulting panel for later configuration
 ConfigureManager* cm = static_cast<ConfigureManager*>(InstanceManager::getNullableDefault("ConfigureManager"));
 if (cm != nullptr) {
     cm->registerUser(panel);
 }

 // reset the size and position, in case the display caused it to change
 panel->getTargetFrame()->move(x,y);
 panel->getTargetFrame()->resize(width,height);
 panel->setTitle();
 // do last to set putItem override - unused.
//    panel->loadComplete();
 panel->getTargetPanel()->setSceneRect(QRectF());
 panel->getTargetPanel()->setSceneRect(panel->getTargetPanel()->sceneRect());
 return result;
}

/*public*/ NamedIcon* ControlPanelEditorXml::loadIcon(QString key, QDomElement element, Editor* ed)
{
 QDomElement elem = element.firstChildElement(key);
 NamedIcon* icon = NULL;
 if (!elem.isNull())
 {
  QDomElement e = elem.firstChildElement("url");
  QString iconName = e.text();
  icon = NamedIcon::getIconByName(iconName);
  if (icon == NULL)
  {
   icon = ed->loadFailed(key, iconName);
   if (icon == NULL)
   {
    log->info(tr("%1 removed for url=%2").arg(key).arg(iconName));
   }
  }
 }
 return icon;
}

/*public*/ int ControlPanelEditorXml::loadOrder()  const
{
 return Manager::PANELFILES;
}
