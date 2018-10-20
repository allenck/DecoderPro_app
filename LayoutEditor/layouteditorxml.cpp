#include "layouteditorxml.h"
#include "instancemanager.h"
#include "layouteditor.h"
#include "panelmenu.h"
#include <QColor>
#include "QMessageBox"
#include "transitmanager.h"
#include "dispatcherframe.h"
#include "loadxmlconfigaction.h"

LayoutEditorXml::LayoutEditorXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 log = new Logger("LayoutEditorXml");log->setDebugEnabled(true);
 setObjectName("LayoutEditorXml");
}
/**
 * Handle configuration for LayoutEditor panes.
 *
 * Based in part on PanelEditorXml.java
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @version $Revision: 28746 $
 */
///*public*/ class LayoutEditorXml extends AbstractXmlAdapter {

///*public*/ LayoutEditorXml() {
//}

//static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");

/**
 * Default implementation for storing the contents of a LayoutEditor
 *
 * @param o Object* to store, of type LayoutEditor
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LayoutEditorXml::store(QObject* o)
{
 LayoutEditor* p = (LayoutEditor*) o;
 QDomElement panel = doc.createElement("LayoutEditor");

 panel.setAttribute("class", "jmri.jmrit.display.layoutEditor.configurexml.LayoutEditorXml");
 panel.setAttribute("name", p->getLayoutName());
 panel.setAttribute("x", p->getUpperLeftX());
 panel.setAttribute("y", p->getUpperLeftY());
 // From this version onwards separate sizes for window and panel are stored the
 // following two statements allow files written here to be read in 2.2 and before
 panel.setAttribute("height", p->getLayoutHeight());
 panel.setAttribute("width", p->getLayoutWidth());
 // From this version onwards separate sizes for window and panel are stored
 panel.setAttribute("windowheight", p->getWindowHeight());
 panel.setAttribute("windowwidth", p->getWindowWidth());
 panel.setAttribute("panelheight", p->getLayoutHeight());
 panel.setAttribute("panelwidth", p->getLayoutWidth());
 panel.setAttribute("sliders", (p->getScroll() ? "yes" : "no")); // deprecated
 panel.setAttribute("scrollable", p->getScrollable());
 panel.setAttribute("editable", (p->isEditable() ? "yes" : "no"));
 panel.setAttribute("positionable", (p->allPositionable() ? "yes" : "no"));
 panel.setAttribute("controlling", (p->allControlling() ? "yes" : "no"));
 panel.setAttribute("animating", (p->isAnimating() ? "yes" : "no"));
 //panel.setAttribute("showhelpbar", (p->getShowHelpBar() ? "yes" : "no"));
 panel.setAttribute("drawgrid", (p->getDrawGrid() ? "yes" : "no"));
 panel.setAttribute("snaponadd", (p->getSnapOnAdd() ? "yes" : "no"));
 panel.setAttribute("snaponmove", (p->getSnapOnMove() ? "yes" : "no"));
 panel.setAttribute("antialiasing", (p->getAntialiasingOn() ? "yes" : "no"));
 panel.setAttribute("turnoutcircles", (p->getTurnoutCircles() ? "yes" : "no"));
 panel.setAttribute("tooltipsnotedit", (p->getTooltipsNotEdit() ? "yes" : "no"));
 panel.setAttribute("tooltipsinedit", (p->getTooltipsInEdit() ? "yes" : "no"));
 panel.setAttribute("mainlinetrackwidth", p->getMainlineTrackWidth());
 panel.setAttribute("xscale",  p->getXScale());
 panel.setAttribute("yscale", p->getYScale());
 panel.setAttribute("sidetrackwidth", p->getSideTrackWidth());
 panel.setAttribute("defaulttrackcolor", p->getDefaultTrackColor());
 panel.setAttribute("defaultoccupiedtrackcolor", p->getDefaultOccupiedTrackColor());
 panel.setAttribute("defaultalternativetrackcolor", p->getDefaultAlternativeTrackColor());
 panel.setAttribute("defaulttextcolor", p->getDefaultTextColor());
 panel.setAttribute("turnoutcirclecolor", p->getTurnoutCircleColor());
 panel.setAttribute("turnoutcirclesize", p->getTurnoutCircleSize());
 panel.setAttribute("turnoutdrawunselectedleg", (p->getTurnoutDrawUnselectedLeg() ? "yes" : "no"));
 panel.setAttribute("turnoutbx",  p->getTurnoutBX());
 panel.setAttribute("turnoutcx",  p->getTurnoutCX());
 panel.setAttribute("turnoutwid", p->getTurnoutWid());
 panel.setAttribute("xoverlong",  p->getXOverLong());
 panel.setAttribute("xoverhwid", p->getXOverHWid());
 panel.setAttribute("xovershort", p->getXOverShort());
 panel.setAttribute("autoblkgenerate", (p->getAutoBlockAssignment() ? "yes" : "no"));
 if (p->getBackgroundColor() != QColor())
 {
  panel.setAttribute("redBackground", p->getBackgroundColor().red());
  panel.setAttribute("greenBackground", p->getBackgroundColor().green());
  panel.setAttribute("blueBackground", p->getBackgroundColor().blue());
 }
 p->resetDirty();
 panel.setAttribute("openDispatcher", p->getOpenDispatcherOnLoad() ? "yes" : "no");
 panel.setAttribute("useDirectTurnoutControl", p->getDirectTurnoutControl() ? "yes" : "no");

 // include contents (Icons and Labels)
 QList<Positionable*> contents = p->getContents();
 int num = contents.size();
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   Positionable* sub = contents.at(i);
   if (sub != nullptr && sub->storeItem())
   {
    try
    {
     QDomElement e = ConfigXmlManager::elementFromObject(sub);
     if (!e.isNull())
     {
      panel.appendChild(e);
     }
    }
    catch (Exception e)
    {
     log->error("Error storing panel contents element: " + e.getMessage());
    }
   }
   else
   {
    log->warn("Null entry found when storing panel contents.");
   }
  }
 }

 // include LayoutTurnouts
 num = p->turnoutList->size();
 if (log->isDebugEnabled())
 {
  log->debug("N layoutturnout elements: " + QString::number(num));
 }
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   QObject* sub = p->turnoutList->at(i);
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub);
    if (!e.isNull())
    {
        panel.appendChild(e);
    }
   }
   catch (Exception e)
   {
    log->error("Error storing panel layoutturnout element: " + e.getMessage());
   }
  }
 }

 // include TrackSegments
 num = p->trackList->size();
 if (log->isDebugEnabled())
 {
  log->debug("N tracksegment elements: " + QString::number(num));
 }
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   QObject* sub = p->trackList->at(i);
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub);
    if (!e.isNull())
    {
     panel.appendChild(e);
    }
   } catch (Exception e)
   {
    log->error("Error storing panel tracksegment element: " + e.getMessage());
   }
  }
 }
 // include PositionablePoints
 num = p->pointList->size();
 if (log->isDebugEnabled()) {
     log->debug("N positionablepoint elements: " + QString::number(num));
 }
 if (num > 0) {
     for (int i = 0; i < num; i++) {
         QObject* sub = p->pointList->at(i);
         try {
             QDomElement e = ConfigXmlManager::elementFromObject(sub);
             if (!e.isNull()) {
                 panel.appendChild(e);
             }
         } catch (Exception e) {
             log->error("Error storing panel positionalpoint element: " + e.getMessage());
         }
     }
 }
 // include LevelXings
 num = p->xingList->size();
 if (log->isDebugEnabled()) {
     log->debug("N levelxing elements: " + QString::number(num));
 }
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   QObject* sub = p->xingList->at(i);
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub);
    if (!e.isNull()) {
        panel.appendChild(e);
    }
   } catch (Exception e)
   {
    log->error("Error storing panel levelxing element: " + e.getMessage());
   }
  }
 }
 // include LayoutSlips
 num = p->slipList->size();
 if (log->isDebugEnabled()) {
     log->debug("N layoutSlip elements: " + QString::number(num));
 }
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   QObject* sub = p->slipList->at(i);
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub);
    if (!e.isNull()) {
        panel.appendChild(e);
    }
   } catch (Exception e)
   {
    log->error("Error storing panel layoutSlip element: " + e.getMessage());
   }
  }
 }
 // include LayoutTurntables
 num = p->turntableList->size();
 if (log->isDebugEnabled()) {
     log->debug("N turntable elements: " + QString::number(num));
 }
 if (num > 0)
 {
  for (int i = 0; i < num; i++)
  {
   QObject* sub = (QObject*)p->turntableList->at(i);
   try
   {
    QDomElement e = ConfigXmlManager::elementFromObject(sub);
    if (!e.isNull()) {
        panel.appendChild(e);
    }
   } catch (Exception e)
   {
    log->error("Error storing panel turntable element: " + e.getMessage());
   }
  }
 }
 return panel;
}

/*public*/ void LayoutEditorXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception)
{
    log->error("Invalid method called");
}

/**
 * Create a LayoutEditor object, then register and fill it, then pop it in a
 * JFrame
 *
 * @param element Top level QDomElement to unpack.
 */
/*public*/ bool LayoutEditorXml::load(QDomElement element) throw (Exception)
{
 bool result = true;
 QString  a;
 // find coordinates
 int x = 0;
 int y = 0;
 // From this version onwards separate sizes for window and panel are used
 int windowHeight = 400;
 int windowWidth = 300;
 int panelHeight = 340;
 int panelWidth = 280;
 int sidetrackwidth = 3;
 int mainlinetrackwidth = 3;
 try
 {
  x = element.attribute("x").toInt();
  y = element.attribute("y").toInt();
  // For compatibility with previous versions, try and see if height and width tags are contained in the file
  if ((a = element.attribute("height")) != nullptr) {
      windowHeight = a.toInt();
      panelHeight = windowHeight - 60;
  }
  if ((a = element.attribute("width")) != nullptr) {
      windowWidth = a.toInt();
      panelWidth = windowWidth - 18;
  }
  // For files created by the new version, retrieve window and panel sizes
  if ((a = element.attribute("windowheight")) != nullptr) {
      windowHeight = a.toInt();
  }
  if ((a = element.attribute("windowwidth")) != nullptr) {
      windowWidth = a.toInt();
  }
  if ((a = element.attribute("panelheight")) != nullptr) {
      panelHeight = a.toInt();
  }
  if ((a = element.attribute("panelwidth")) != nullptr) {
      panelWidth = a.toInt();
  }

  mainlinetrackwidth = element.attribute("mainlinetrackwidth").toInt();
  sidetrackwidth = element.attribute("sidetrackwidth").toInt();
 }
 catch (DataConversionException e)
 {
     log->error("failed to convert LayoutEditor's attribute");
     result = false;
 }
 double xScale = 1.0;
 double yScale = 1.0;
 a = element.attribute("xscale");
 bool bok;
 if (a != nullptr)
 {
  try
  {
   xScale = a.toFloat(&bok);
   if(!bok) throw Exception();
  }
  catch (Exception e)
  {
   log->error("failed to convert to float - " + a);
   result = false;
  }
 }
 a = element.attribute("yscale");
 if (a != nullptr)
 {
  try
  {
   yScale = a.toFloat(&bok);
   if(!bok) throw Exception();
  }
  catch (Exception e)
  {
   log->error("failed to convert to float - " + a);
   result = false;
  }
 }
 // find the name and default track color
 QString name = "";
 if (element.attribute("name") != nullptr)
 {
  name = element.attribute("name");
 }
 if (PanelMenu::instance()->isPanelNameUsed(name))
 {
  JFrame* frame = new JFrame("Demo");
  frame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
  log->warn("File contains a panel with the same name (" + name + ") as an existing panel");
//        int n = JOptionPane.showConfirmDialog(frame,
//                java.text.MessageFormat.format(rb.getString("DuplicatePanel"),
//                        new Object[]{name}),
//                rb.getString("DuplicatePanelTitle"),
//                JOptionPane.YES_NO_OPTION);
//        if (n == JOptionPane.NO_OPTION) {
  int n = QMessageBox::warning(frame, tr("Duplicate Panel name"), tr("\"%1\" has already been opened.                                                                   Are you sure that you want to open another copy?").arg(name),QMessageBox::Yes | QMessageBox::No);
  if(n == QMessageBox::No)
  {
   return false;
  }
 }
 QString defaultColor = "black";
 QString defaultTextColor = "black";
 if (element.attribute("defaulttrackcolor") != nullptr)
 {
  defaultColor = element.attribute("defaulttrackcolor");
 }
 if (element.attribute("defaulttextcolor") != nullptr)
 {
  defaultTextColor = element.attribute("defaulttextcolor");
 }
 QString turnoutCircleColor = "track";  //default to using use default track color for circle color
 if (element.attribute("turnoutcirclecolor") != nullptr)
 {
  turnoutCircleColor = element.attribute("turnoutcirclecolor");
 }
 int turnoutCircleSize = 2;
 if (element.attribute("turnoutcirclesize") != nullptr)
 {
  try
  {
   turnoutCircleSize = element.attribute("turnoutcirclesize").toInt();
  } catch (DataConversionException e1)
  {
   //leave at default if cannot convert
   log->warn("unable to convert turnoutcirclesize");
  }
 }
 bool turnoutDrawUnselectedLeg = true;
 if ((a = element.attribute("turnoutdrawunselectedleg")) != nullptr && a==("no")) {
     turnoutDrawUnselectedLeg = false;
 }
 // create the objects
 LayoutEditor* panel = new LayoutEditor(name);
 panel->setFilename(LoadXmlConfigAction::currentFile);
 panel->setLayoutName(name);
 panel->setMainlineTrackWidth(mainlinetrackwidth);
 panel->setSideTrackWidth(sidetrackwidth);
 panel->setDefaultTrackColor(defaultColor);
 panel->setDefaultTextColor(defaultTextColor);
 panel->setTurnoutCircleColor(turnoutCircleColor);
 panel->setTurnoutCircleSize(turnoutCircleSize);
 panel->setTurnoutDrawUnselectedLeg(turnoutDrawUnselectedLeg);
// panel->setXScale(xScale);
// panel->setYScale(yScale);
 panel->setScale(xScale, yScale);
 // turnout size parameters
 double sz = 20.0;
 a = element.attribute("turnoutbx");
 if (a != nullptr)
 {
  try
  {
   sz = a.toFloat();
   panel->setTurnoutBX(sz);
  } catch (Exception e)
  {
   log->error("failed to convert to float - " + a);
   result = false;
  }
 }
 a = element.attribute("turnoutcx");
 if (a != nullptr) {
     try {
         sz = a.toFloat();
         panel->setTurnoutCX(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = element.attribute("turnoutwid");
 if (a != nullptr) {
     try {
         sz = a.toFloat();;
         panel->setTurnoutWid(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = element.attribute("xoverlong");
 if (a != nullptr) {
     try {
         sz = a.toFloat();;
         panel->setXOverLong(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = element.attribute("xoverhwid");
 if (a != nullptr) {
     try {
         sz = a.toFloat();;
         panel->setXOverHWid(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = element.attribute("xovershort");
 if (a != nullptr) {
     try {
         sz = a.toFloat();;
         panel->setXOverShort(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }

 // set contents state
 QString slValue = "both";
 if ((a = element.attribute("sliders")) != nullptr && a==("no")) {
     slValue = "none";
 }
 if ((a = element.attribute("scrollable")) != nullptr) {
     slValue = a;
 }

 bool edValue = true;
 if ((a = element.attribute("editable")) != nullptr && a==("no")) {
     edValue = false;
 }

 bool value = true;
 if ((a = element.attribute("positionable")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setAllPositionable(value);

 value = true;
 if ((a = element.attribute("controlling")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setAllControlling(value);

 value = true;
 if ((a = element.attribute("animating")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setTurnoutAnimation(value);

 bool hbValue = true;
 if ((a = element.attribute("showhelpbar")) != nullptr && a==("no")) {
     hbValue = false;
 }

 bool dgValue = false;
 if ((a = element.attribute("drawgrid")) != nullptr && a==("yes")) {
     dgValue = true;
 }

 bool sgaValue = false;
 if ((a = element.attribute("snaponadd")) != nullptr && a==("yes")) {
     sgaValue = true;
 }

 bool sgmValue = false;
 if ((a = element.attribute("snaponmove")) != nullptr && a==("yes")) {
     sgmValue = true;
 }

 bool aaValue = false;
 if ((a = element.attribute("antialiasing")) != nullptr && a==("yes")) {
     aaValue = true;
 }

 value = false;
 if ((a = element.attribute("turnoutcircles")) != nullptr && a==("yes")) {
     value = true;
 }
 panel->setTurnoutCircles(value);

 value = false;
 if ((a = element.attribute("tooltipsnotedit")) != nullptr && a==("yes")) {
     value = true;
 }
// TODO:    panel->setTooltipsNotEdit(value);

 value = false;
 if ((a = element.attribute("autoblkgenerate")) != nullptr && a==("yes")) {
     value = true;
 }
 panel->setAutoBlockAssignment(value);

 value = true;
 if ((a = element.attribute("tooltipsinedit")) != nullptr && a==("no")) {
     value = false;
 }
// TODO:    panel->setTooltipsInEdit(value);
 // set default track color
 if ((a = element.attribute("defaulttrackcolor")) != nullptr) {
     panel->setDefaultTrackColor(a);
 }
 // set default track color
 if ((a = element.attribute("defaultoccupiedtrackcolor")) != nullptr) {
  panel->setDefaultOccupiedTrackColor(a);
 }
 // set default track color
 if ((a = element.attribute("defaultalternativetrackcolor")) != nullptr) {
   panel->setDefaultAlternativeTrackColor(a);
 }
 try {
     int red = element.attribute("redBackground").toInt();
     int blue = element.attribute("blueBackground").toInt();
     int green = element.attribute("greenBackground").toInt();
     panel->setDefaultBackgroundColor(ColorUtil::colorToString( QColor(red, green, blue)));
     panel->setBackgroundColor( QColor(red, green, blue));
 } catch (DataConversionException e) {
     log->warn("Could not parse color attributes!");
 } catch (NullPointerException e) {  // considered normal if the attributes are not present
 }
 if (element.attribute("useDirectTurnoutControl") != nullptr)
 {
  if (element.attribute("useDirectTurnoutControl")==("yes"))
  {
   panel->setDirectTurnoutControl(true);
  }
 }
 // Set editor's option flags, load content after
 // this so that individual item flags are set as saved
// TODO:    panel->initView();

 // load the contents
 QDomNodeList items = element.childNodes();
 for (int i = 0; i < items.size(); i++)
 {
  // get the class, hence the adapter object to do loading
  QDomElement item = items.at(i).toElement();
  QString adapterName = item.attribute("class");
  if (log->isDebugEnabled())
  {
   QString id = "<nullptr>";
   try {
       id = item.attribute("ident");
   } catch (Exception e) {
   }
   log->debug("Load " + id + " for [" + panel->getName() + "] via " + adapterName);
  }
//  try
//  {
  XmlAdapter* adapter;// = (XmlAdapter*) Class.forName(adapterName).newInstance();
  QString className = adapterName.mid(adapterName.lastIndexOf(".") +1);
  int typeId = QMetaType::type(className.toLocal8Bit());
  if(typeId > 0)
  {
#if QT_VERSION < 0x050000

   adapter = (XmlAdapter*) QMetaType::construct(typeId);
#else
   adapter = (XmlAdapter*) QMetaType::create(typeId);
#endif
   // and do it
   adapter->load(item, panel);
   if (!panel->loadOK())
   {
    result = false;
   }
  }
  else
  {
   log->error("Exception while loading " + item.tagName() + ":" + tr(" xml adapter not found %1").arg(adapterName));
   result = false;
         //e.printStackTrace();
  }
 }
 panel->disposeLoadData();     // dispose of url correction data

 // final initialization of objects
 panel->setConnections();

 // display the results
 panel->setAllEditable(edValue);  // set first since other attribute use this setting
 panel->setShowHelpBar(hbValue);
 panel->setDrawGrid(dgValue);
 panel->setSnapOnAdd(sgaValue);
 panel->setSnapOnMove(sgmValue);
 panel->setAntialiasingOn(aaValue);
 //panel->setScroll(slValue);
 panel->panelWidth = panelWidth;
 panel->panelHeight = panelHeight;
 panel->editScene->setSceneRect(0,0,panelWidth, panelHeight);
 panel->editPanel->scale(xScale, yScale); // added ACK
 panel->pack();
 panel->setLayoutDimensions(windowWidth, windowHeight, x, y, panelWidth, panelHeight);
 panel->setVisible(true);    // always show the panel
 panel->resetDirty();

 panel->paintTargetPanel(panel->editScene); // force redraw


 // register the resulting panel for later configuration
 static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->registerUser(panel);
 //if (InstanceManager::transitManagerInstance()->getSystemNameList().size() > 0)
 if(((TransitManager*)InstanceManager::getNullableDefault("TransitManager")))
 {
  if (element.attribute("openDispatcher") != nullptr)
  {
   if (element.attribute("openDispatcher")==("yes"))
   {
    panel->setOpenDispatcherOnLoad(true);
    DispatcherFrame::instance();
   }
   else
   {
    panel->setOpenDispatcherOnLoad(false);
   }
  }
 }
 return result;
}

/*public*/ int LayoutEditorXml::loadOrder() {
    return Manager::PANELFILES;
}
