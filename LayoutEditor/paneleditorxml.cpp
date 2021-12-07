#include "paneleditorxml.h"
#include "manager.h"
#include "instancemanager.h"
#include "paneleditor.h"
#include <QMenuBar>
#include "panelmenu.h"
#include "positionablelabelxml.h"
#include "locoiconxml.h"
#include "abstractlightmanagerconfigxml.h"
#include "lememoryiconxml.h"
#include "sensoriconxml.h"
#include "lighticonxml.h"
#include "analogclock2displayxml.h"
#include "turnouticonxml.h"
#include "reportericonxml.h"
#include "slipturnouticonxml.h"
#include "signalheadiconxml.h"
#include "signalmasticonxml.h"
#include "multisensoriconxml.h"
#include "guilafpreferencesmanager.h"
#include "userpreferencesmanager.h"

PanelEditorXml::PanelEditorXml(QObject* parent) :
    AbstractXmlAdapter(parent)
{
 log = new Logger("PanelEditorXml");
}
/**
 * Handle configuration for {@link PanelEditor} panes.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 18102 $
 */
//public class PanelEditorXml extends AbstractXmlAdapter {

//    public PanelEditorXml() {}

/**
 * Default implementation for storing the contents of a
 * PanelEditor
 * @param o Object to store, of type PanelEditor
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PanelEditorXml::store(QObject* o)
{
 PanelEditor* p = (PanelEditor*)o;
 QDomElement panel = doc.createElement("paneleditor");

 //QWidget* frame = p->getTargetFrame();
 QSize size = /*frame->getSize();*/ p->size();
 QPoint posn = /*frame->getLocation();*/ p->pos();

 panel.setAttribute("class", "jmri.jmrit.display.panelEditor.configurexml.PanelEditorXml");
 panel.setAttribute("name", p->windowTitle());
 panel.setAttribute("x", posn.x());
 panel.setAttribute("y", posn.y());
 panel.setAttribute("height", size.height());
 panel.setAttribute("width", size.width());
 panel.setAttribute("editable", (p->isEditable()?"yes":"no"));
 panel.setAttribute("positionable", (p->allPositionable()?"yes":"no"));
 panel.setAttribute("showcoordinates", (p->showCoordinates()?"yes":"no"));
 panel.setAttribute("showtooltips", (p->showToolTip()?"yes":"no"));
 panel.setAttribute("controlling", (p->allControlling()?"yes":"no"));
 panel.setAttribute("hide", (p->isVisible()?"no":"yes"));
 panel.setAttribute("panelmenu", (p->menuBar()->isVisible()?"yes":"no"));
 //panel.setAttribute("scrollable", p-> getScrollable());
 if (p->getBackgroundColor().isValid())
 {
  panel.setAttribute("redBackground", p->getBackgroundColor().red());
  panel.setAttribute("greenBackground", p->getBackgroundColor().green());
  panel.setAttribute("blueBackground", p->getBackgroundColor().blue());
 }

 // include contents
 QList <Positionable*> contents = p->getContents();
 if (log->isDebugEnabled()) log->debug("N elements: "+QString("%1").arg(contents.size()));
 for (int i=0; i<contents.size(); i++)
 {
  Positionable* sub = contents.at(i);
  if (sub!=NULL /*&& sub->storeItem()*/)
  {
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub->self());
    if (!e.isNull())
     panel.appendChild(e);
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


/*public*/ void PanelEditorXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
    log->error("Invalid method called");
}

/**
 * Create a PanelEditor object, then
 * register and fill it, then pop it in a JFrame
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool PanelEditorXml::load(QDomElement shared, QDomElement perNode) throw (Exception)
{
    bool result = true;
    // find coordinates
    int x = 0;
    int y = 0;
    int height = 400;
    int width = 300;
//    try {
    bool bOk = true;
    bool bOk1;
    x = shared.attribute("x").toInt(&bOk1);
    if(!bOk1) bOk = false;
    y = shared.attribute("y").toInt(&bOk1);
    if(!bOk1) bOk = false;
    height = shared.attribute("height").toInt(&bOk1);
    if(!bOk1) bOk = false;
    width = shared.attribute("width").toInt(&bOk1);
//    } catch ( org.jdom.DataConversionException e) {
    if(!bOk)
    {
     log->error("failed to convert PanelEditor's attribute");
     result = false;
    }
    // find the name
    QString name = "Panel";
    if (shared.attribute("name")!="")
     name = shared.attribute("name");
    // confirm that panel hasn't already been loaded
    if(static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
    {
     log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
     result = false;
    }

    // If available, override location and size with machine dependent values
    if (!((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize()) {
        UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");
        if (prefsMgr != nullptr) {

            QPoint prefsWindowLocation = prefsMgr->getWindowLocation("jmri.jmrit.display.panelEditor.PanelEditor:"+name);
            if (!prefsWindowLocation.isNull()) {
                x = (int) prefsWindowLocation.x();
                y = (int) prefsWindowLocation.y();
            }

            QSize prefsWindowSize = prefsMgr->getWindowSize("jmri.jmrit.display.panelEditor.PanelEditor:"+name);
            if (!prefsWindowSize.isNull() && prefsWindowSize.height() != 0 && prefsWindowSize.width() != 0) {
                height = (int) prefsWindowSize.height();
                width = (int) prefsWindowSize.height();
            }
        }
    }

    PanelEditor* panel = new PanelEditor(name);
    //panel.makeFrame(name);
    //panel->init(name);
    ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);
    //panel->getTargetFrame()->setsetLocation(x,y);
//    panel->setLocation(x,y);
//    panel->getTargetFrame()->resize(width,height);
//    panel->resize(width,height);
    panel->setGeometry(x,y,width, height);
    panel->setTitle();
    static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);

    // Load editor option flags. This has to be done before the content
    // items are loaded, to preserve the individual item settings
    panel->setAllEditable(shared.attribute("editable","yes") != ("no"));
    panel->setAllPositionable(shared.attribute("positionable","yes") != ("no"));
    //panel.setShowCoordinates(shared.attribute("showcoordinates","no") == s("yes"));
    panel->setAllShowToolTip(shared.attribute("showtooltips","yes") != ("no"));
    panel->setAllControlling(shared.attribute("controlling", "yes") != ("no"));
    panel->setShowHidden(shared.attribute("hide","no") == ("yes"));
    panel->setPanelMenuVisible(shared.attribute("panelmenu","yes") != ("no"));
    panel->setScroll(shared.attribute("scrollable","both"));

    // set color if needed
    try
    {
     QColor defaultColor = QColor(220,220,220);
     bOk = true;
     int red = shared.attribute("redBackground",QString::number(defaultColor.red())).toInt(&bOk1);
     if(!bOk1) bOk = false;
     int blue = shared.attribute("blueBackground",QString::number(defaultColor.green())).toInt(&bOk1);
     if(!bOk1) bOk = false;
     int green = shared.attribute("greenBackground",QString::number(defaultColor.blue())).toInt(&bOk1);
     if(!bOk1) bOk = false;
 //    } catch ( org.jdom.DataConversionException e) {
     if(!bOk)
     {
      log->warn("Could not parse color attributes!");
     }
     else
      panel->setBackgroundColor(QColor(red, green, blue));
    }
    catch ( NullPointerException e) {  // considered normal if the attributes are not present
    }
    //set the (global) editor display widgets to their flag settings
    panel->initView();

    // load the contents with their individual option settings
    QDomNodeList items = shared.childNodes();
    for (int i = 0; i<items.size(); i++)
    {
     // get the class, hence the adapter object to do loading
     QDomElement item = items.at(i).toElement();
     QString adapterName = item.attribute("class");
     log->debug("load via "+adapterName + "tagname " + item.tagName());
     try
     {
      XmlAdapter* adapter = NULL;
      //XmlAdapter* adapter = (XmlAdapter*)Class.forName(adapterName).getDeclaredConstructor().newInstance();
      if(adapterName == "jmri.jmrit.display.configurexml.MemoryIconXml")
          adapter = new MemoryIconXml(this);
      else if( adapterName == "jmri.jmrit.display.configurexml.AnalogClock2DisplayXml")
          adapter = new AnalogClock2DisplayXml(this);
      else if(adapterName =="LocoIconXml")
          adapter = new LocoIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.PositionableLabelXml")
          adapter = new PositionableLabelXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.SensorIconXml")
          adapter = new SensorIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.LightIconXml")
          adapter = new LightIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.TurnoutIconXml")
          adapter = new TurnoutIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.LocoIconXml")
          adapter = new LocoIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.ReporterIconXml")
          adapter = new ReporterIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.SlipTurnoutIconXml")
          adapter = new SlipTurnoutIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.SignalHeadIconXml")
          adapter = new SignalHeadIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.SignalMastIconXml")
          adapter = new SignalMastIconXml(this);
      else if(adapterName == "jmri.jmrit.display.configurexml.MultiSensorIconXml")
          adapter = new MultiSensorIconXml(this);
      else
      {
       //return false; // TODO:
       log->error(tr("No logic to handle ")+adapterName);
       continue;
      }
      // and do it
      adapter->load(item, panel);
      if (!panel->loadOK())
      {
       result = false;
      }
     }
     catch (Exception e)
     {
      log->error("Exception while loading "+item.tagName()+":"+e.getMessage());
      result = false;
      //e.printStackTrace();
     }
     qApp->processEvents();
    }
    panel->disposeLoadData();     // dispose of url correction data

    // display the results, with the editor in back
    //panel.pack();
    panel->setAllEditable(panel->isEditable());

    // we don't pack the target frame here, because size was specified
    // TODO: Work out why, when calling this method, panel size is increased
    // vertically (at least on MS Windows)
    panel->setVisible(true);    // always show the panel

    // register the resulting panel for later configuration
    static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerUser(panel);

    // reset the size and position, in case the display caused it to change
    //panel->getTargetFrame().setLocation(x,y);
    panel->getTargetFrame()->resize(width,height);
    return result;
}

/*public*/ int PanelEditorXml::loadOrder()const{
    return Manager::PANELFILES;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PanelEditorXml.class.getName());

//}
