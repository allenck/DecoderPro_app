#include "layouteditorxml.h"
#include "instancemanager.h"
#include "layouteditor.h"
#include "panelmenu.h"
#include <QColor>
#include "QMessageBox"
#include "transitmanager.h"
#include "../operations/dispatcherframe.h"
#include "loadxmlconfigaction.h"
#include "joptionpane.h"
#include "colorutil.h"
#include "layoutturntable.h"
#include <QMenuBar>
#include "guilafpreferencesmanager.h"
#include "userpreferencesmanager.h"
#include "positionablepoint.h"
#include "classmigration.h"

LayoutEditorXml::LayoutEditorXml(QObject *parent) :
  AbstractXmlAdapter(parent)
{
 log = new Logger("LayoutEditorXml");
 log->setDebugEnabled(true);
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
 if (((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize())
 {
   panel.setAttribute("x", QString::number(p->gContext->getUpperLeftX()));
   panel.setAttribute("y", QString::number(p->gContext->getUpperLeftY()));
   panel.setAttribute("windowheight", QString::number(p->gContext->getWindowHeight()));
   panel.setAttribute("windowwidth", QString::number(p->gContext->getWindowWidth()));
 } else {
   // Use real location and size
   QPoint loc = p->getLocation();
   panel.setAttribute("x", QString::number(loc.x()));
   panel.setAttribute("y", QString::number(loc.y()));

   QSize size = p->size();
   panel.setAttribute("windowheight", QString::number(size.height()));
   panel.setAttribute("windowwidth", QString::number(size.width()));
 }
 panel.setAttribute("panelheight", p->gContext->getLayoutHeight());
 panel.setAttribute("panelwidth", p->gContext->getLayoutWidth());
 panel.setAttribute("sliders", (p->getScroll() ? "yes" : "no")); // deprecated
 panel.setAttribute("scrollable", p->getScrollable());
 panel.setAttribute("editable", (p->isEditable() ? "yes" : "no"));
 panel.setAttribute("positionable", (p->allPositionable() ? "yes" : "no"));
 panel.setAttribute("controlling", (p->allControlling() ? "yes" : "no"));
 panel.setAttribute("animating", (p->isAnimating() ? "yes" : "no"));
 panel.setAttribute("showhelpbar", (p->getShowHelpBar() ? "yes" : "no"));
 panel.setAttribute("drawgrid", (p->getDrawGrid() ? "yes" : "no"));
 panel.setAttribute("snaponadd", (p->getSnapOnAdd() ? "yes" : "no"));
 panel.setAttribute("snaponmove", (p->getSnapOnMove() ? "yes" : "no"));
 panel.setAttribute("antialiasing", (p->getAntialiasingOn() ? "yes" : "no"));
 panel.setAttribute("turnoutcircles", (p->getTurnoutCircles() ? "yes" : "no"));
 panel.setAttribute("tooltipsnotedit", (p->getTooltipsNotEdit() ? "yes" : "no"));
 panel.setAttribute("tooltipsinedit", (p->getTooltipsInEdit() ? "yes" : "no"));
 panel.setAttribute("mainlinetrackwidth", p->gContext->getMainlineTrackWidth());
 panel.setAttribute("xscale",  p->gContext->getXScale());
 panel.setAttribute("yscale", p->gContext->getYScale());
 panel.setAttribute("sidetrackwidth", p->gContext->getSidelineTrackWidth());
 panel.setAttribute("defaulttrackcolor", p->getDefaultTrackColor());
 panel.setAttribute("defaultoccupiedtrackcolor", p->getDefaultOccupiedTrackColor());
 panel.setAttribute("defaultalternativetrackcolor", p->getDefaultAlternativeTrackColor());
 panel.setAttribute("defaulttextcolor", p->getDefaultTextColor());
 QString turnoutCircleColor = p->getTurnoutCircleColor();
 panel.setAttribute("turnoutcirclecolor", p->getTurnoutCircleColor());
 QString turnoutCircleThrownColor = p->getTurnoutCircleThrownColor();
 // optional attributes
 if (turnoutCircleColor!=(turnoutCircleThrownColor)) {
     panel.setAttribute("turnoutcirclethrowncolor", turnoutCircleThrownColor);
 }
 if (p->isTurnoutFillControlCircles()) {
     panel.setAttribute("turnoutfillcontrolcircles", "yes");
 }

 panel.setAttribute("turnoutcirclesize", p->getTurnoutCircleSize());
 panel.setAttribute("turnoutdrawunselectedleg", (p->isTurnoutDrawUnselectedLeg() ? "yes" : "no"));
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

 // store layout track drawing options
 try
 {
     LayoutTrackDrawingOptions* ltdo = p->getLayoutTrackDrawingOptions();
     QDomElement e = ConfigXmlManager::elementFromObject((QObject*)ltdo);
     if (!e .isNull()) {
         panel.appendChild(e);
     }
 } catch (Exception e) {
     log->error("Error storing contents element: " + e.getMessage());
 }

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
     QDomElement e = ConfigXmlManager::elementFromObject(sub->self());
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

 // include LayoutTracks
    QList<LayoutTrack*> layoutTracks = p->getLayoutTracks();
    num = layoutTracks.size();
    if (log->isDebugEnabled()) {
        log->debug("N LayoutTrack elements: " + QString::number(num));
    }

    // Because some people (like me) like to edit their panel.xml files
    // directly we're going to group the layout tracks by class before
    // storing them. Note: No other order is effected; They should exist
    // in the saved file in the order that they were created (ether at
    // panel file load time or later by the users in the editor).
//    QList<LayoutTrack*> orderedList = layoutTracks.stream() // next line excludes LayoutSlips
//            .filter(item -> ((item instanceof LayoutTurnout) && !(item instanceof LayoutSlip)))
//            .map(item -> (LayoutTurnout) item)
//            .collect(Collectors.toList());
    QList<LayoutTrack*> orderedList = QList<LayoutTrack*>();
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<LayoutTurnout*>(lt) && !qobject_cast<LayoutSlip*>(lt))
      orderedList.append(lt);
    }
//    orderedList.addAll(layoutTracks.stream()
//            .filter(item -> item instanceof TrackSegment)
//            .map(item -> (TrackSegment) item)
//            .collect(Collectors.toList()));
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<TrackSegment*>(lt))
      orderedList.append(lt);
    }
//    orderedList.addAll(layoutTracks.stream()
//            .filter(item -> item instanceof PositionablePoint)
//            .map(item -> (PositionablePoint) item)
//            .collect(Collectors.toList()));
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<PositionablePoint*>(lt))
      orderedList.append(lt);
    }
//    orderedList.addAll(layoutTracks.stream()
//            .filter(item -> item instanceof LevelXing)
//            .map(item -> (LevelXing) item)
//            .collect(Collectors.toList()));
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<LevelXing*>(lt))
      orderedList.append(lt);
    }
//    orderedList.addAll(layoutTracks.stream()
//            .filter(item -> item instanceof LayoutSlip)
//            .map(item -> (LayoutSlip) item)
//            .collect(Collectors.toList()));
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<LayoutSlip*>(lt))
      orderedList.append(lt);
    }
//    orderedList.addAll(layoutTracks.stream()
//            .filter(item -> item instanceof LayoutTurntable)
//            .map(item -> (LayoutTurntable) item)
//            .collect(Collectors.toList()));
    for(LayoutTrack* lt : layoutTracks) {
     if(qobject_cast<LayoutTurntable*>(lt))
      orderedList.append(lt);
    }

    for (LayoutTrack* lt : orderedList) {
        try {
            QDomElement e = ConfigXmlManager::elementFromObject(lt);
            if (!e.isNull()) {
                panel.appendChild(e);
            }
        } catch (Exception e) {
            log->error("Error storing layoutturnout element: " + e.getMessage());
        }
    }
    return panel;
}   // store

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
/*public*/ bool LayoutEditorXml::load(QDomElement shared, QDomElement /*perNode*/) throw (Exception)
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
  bool ok;
  x = shared.attribute("x").toInt(&ok); if(!ok) throw DataConversionException();
  y = shared.attribute("y").toInt(&ok); if(!ok) throw DataConversionException();
  // For compatibility with previous versions, try and see if height and width tags are contained in the file
  if ((a = shared.attribute("height")) != "") {
      windowHeight = a.toInt(&ok); if(!ok) throw DataConversionException();
      panelHeight = windowHeight - 60;
  }
  if ((a = shared.attribute("width")) != "") {
      windowWidth = a.toInt(&ok); if(!ok) throw DataConversionException();
      panelWidth = windowWidth - 18;
  }
  // For files created by the new version, retrieve window and panel sizes
  if ((a = shared.attribute("windowheight")) != "") {
      windowHeight = a.toInt(&ok); if(!ok) throw DataConversionException();
  }
  if ((a = shared.attribute("windowwidth")) != "") {
      windowWidth = a.toInt(&ok); if(!ok) throw DataConversionException();
  }
  if ((a = shared.attribute("panelheight")) != "") {
      panelHeight = a.toInt(&ok); if(!ok) throw DataConversionException();
  }
  if ((a = shared.attribute("panelwidth")) != "") {
      panelWidth = a.toInt(&ok); if(!ok) throw DataConversionException();
  }

  mainlinetrackwidth = shared.attribute("mainlinetrackwidth").toInt();
  sidetrackwidth = shared.attribute("sidetrackwidth").toInt();
 }
 catch (DataConversionException e)
 {
     log->error("failed to convert LayoutEditor's attribute");
     result = false;
 }
 double xScale = 1.0;
 double yScale = 1.0;
 a = shared.attribute("xscale");
 bool bok;
 if (a != "")
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
 a = shared.attribute("yscale");
 if (a != "")
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
 if (shared.attribute("name") != nullptr)
 {
  name = shared.attribute("name");
 }
 if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
 {
     JFrame* frame = new JFrame("Demo");
     frame->setDefaultCloseOperation(JFrame::DISPOSE_ON_CLOSE);
     log->warn(tr("File contains a panel with the same name (%1) as an existing panel").arg(name));
     int n = JOptionPane::showConfirmDialog(frame,
             tr("\"%1\" has already been opened.\nAre you sure that you want to open another copy?").arg(name),
             tr("Duplicate Panel name"),
             JOptionPane::YES_NO_OPTION);
     if (n == JOptionPane::NO_OPTION) {
         return false;
     }
 }

 // If available, override location and size with machine dependent values
 if (!((GuiLafPreferencesManager*)InstanceManager::getDefault("GuiLafPreferencesManager"))->isEditorUseOldLocSize())
 {
     UserPreferencesManager* prefsMgr = (UserPreferencesManager*)InstanceManager::getNullableDefault("UserPreferencesManager");
     if (prefsMgr != nullptr) {
         QString windowFrameRef = "jmri.jmrit.display.layoutEditor.LayoutEditor:" + name;

         QPoint prefsWindowLocation = prefsMgr->getWindowLocation(windowFrameRef);
         if (!prefsWindowLocation.isNull()) {
             x = (int) prefsWindowLocation.x();
             y = (int) prefsWindowLocation.y();
         }

         QSize prefsWindowSize = prefsMgr->getWindowSize(windowFrameRef);
         if (prefsWindowSize.isValid() && prefsWindowSize.height() != 0 && prefsWindowSize.width() != 0) {
             windowHeight = (int) prefsWindowSize.height();
             windowWidth = (int) prefsWindowSize.width();
         }
     }
 }

 LayoutEditor* panel = new LayoutEditor(name);
 panel->setLayoutName(name);
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);

 // create the objects
 //LayoutEditor* panel = new LayoutEditor(name);
 //panel->setFilename(LoadXmlConfigAction::currentFile);
 panel->gContext->setMainlineTrackWidth(mainlinetrackwidth);
 panel->gContext->setSidelineTrackWidth(sidetrackwidth);
 panel->gContext->setXScale(xScale);
 panel->gContext->setYScale(yScale);

 QString color = ColorUtil::ColorDarkGray;
 if ((a = shared.attribute("defaulttrackcolor")) != "") {
     color = a;
 }
 panel->setDefaultTrackColor(ColorUtil::stringToColor(color));

 color = ColorUtil::ColorBlack;
 if ((a = shared.attribute("defaulttextcolor")) != "") {
     color = a;
 }
 panel->setDefaultTextColor(ColorUtil::stringToColor(color));

 color = "track";  //default to using use default track color for circle color
 if ((a = shared.attribute("turnoutcirclecolor")) != "") {
     color = a;
 }
 panel->setTurnoutCircleColor(ColorUtil::stringToColor(color));

 // default to using turnout circle color just set
 if ((a = shared.attribute("turnoutcirclethrowncolor")) != "") {
     color = a;
 }
 panel->setTurnoutCircleThrownColor(ColorUtil::stringToColor(color));

 // the "turnoutfillcontrolcircles" attribute has a default="no" value in the schema;
 // it will always return a "no" attribute if the attribute is not present.
 panel->setTurnoutFillControlCircles(shared.attribute("turnoutfillcontrolcircles")=="yes");

if ((a = shared.attribute("turnoutcirclesize")) != "")
{
     bool bok;
         panel->setTurnoutCircleSize(a.toInt(&bok));
     if(!bok) {
         log->warn("unable to convert turnoutcirclesize");
     }
 }

 try {
     panel->setTurnoutDrawUnselectedLeg(shared.attribute("turnoutdrawunselectedleg")=="true");
 }
 catch (DataConversionException e) {
     log->warn("unable to convert turnoutdrawunselectedleg attribute");
 }
 catch (NullPointerException e) {  // considered normal if the attribute is not present
 }

 // turnout size parameters
 double sz = 20.0;
 a = shared.attribute("turnoutbx");
 if (a != "")
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
 a = shared.attribute("turnoutcx");
 if (a != "") {
     try {
         sz = a.toFloat();
         panel->setTurnoutCX(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = shared.attribute("turnoutwid");
 if (a != "") {
     try {
         sz = a.toFloat();;
         panel->setTurnoutWid(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = shared.attribute("xoverlong");
 if (a != "") {
     try {
         sz = a.toFloat();;
         panel->setXOverLong(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = shared.attribute("xoverhwid");
 if (a != "") {
     try {
         sz = a.toFloat();;
         panel->setXOverHWid(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 a = shared.attribute("xovershort");
 if (a != "") {
     try {
         sz = a.toFloat();;
         panel->setXOverShort(sz);
     } catch (Exception e) {
         log->error("failed to convert to float - " + a);
         result = false;
     }
 }
 // grid size parameter
 if ((a = shared.attribute("gridSize")) != "") {
     bool ok;
         panel->gContext->setGridSize(a.toInt(&ok));
     if(!ok) {
         log->error(tr("failed to convert gridSize to int - %1").arg(a));
         result = false;
     }
 }

 // second grid size parameter
 if ((a = shared.attribute("gridSize2nd")) != "") {
     bool ok;
         panel->gContext->setGridSize2nd(a.toInt(&ok));
     if(!ok) {
         log->error(tr("failed to convert gridSize2nd to int - %1").arg(a));
         result = false;
     }
 }


 bool value = true;
 if ((a = shared.attribute("positionable")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setAllPositionable(value);
 panel->positionableCheckBoxMenuItem->setChecked(value);

 value = true;
 if ((a = shared.attribute("controlling")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setAllControlling(value);

 value = true;
 if ((a = shared.attribute("animating")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setTurnoutAnimation(value);

 try {
     panel->setDrawGrid(getBooleanValue(shared.attribute("drawgrid")));
 } catch (DataConversionException e) {
     log->warn("unable to convert drawgrid attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing drawgrid attribute");
 }

 try {
     panel->setSnapOnAdd(getBooleanValue(shared.attribute("snaponadd")));
 } catch (DataConversionException e) {
     log->warn("unable to convert snaponadd attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing snaponadd attribute");
 }

 try {
     panel->setSnapOnMove(getBooleanValue(shared.attribute("snaponmove")));
 } catch (DataConversionException e) {
     log->warn("unable to convert snaponmove attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing snaponmove attribute");
 }

 try {
     panel->setTurnoutCircles(getBooleanValue(shared.attribute("turnoutcircles")));
 } catch (DataConversionException e) {
     log->warn("unable to convert turnoutcircles attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing turnoutcircles attribute");
 }

 value = false;
 if ((a = shared.attribute("tooltipsnotedit")) != nullptr && a==("yes")) {
     value = true;
 }
 panel->setTooltipsNotEdit(value);

 value = false;
 if ((a = shared.attribute("autoblkgenerate")) != nullptr && a==("yes")) {
     value = true;
 }
 panel->setAutoBlockAssignment(value);

 value = true;
 if ((a = shared.attribute("tooltipsinedit")) != nullptr && a==("no")) {
     value = false;
 }
 panel->setTooltipsInEdit(value);

 // set default track color
 if ((a = shared.attribute("defaulttrackcolor")) != nullptr) {
     panel->setDefaultTrackColor(a);
 }
 // set default track color
 if ((a = shared.attribute("defaultoccupiedtrackcolor")) != nullptr) {
  panel->setDefaultOccupiedTrackColor(a);
 }
 // set default track color
 if ((a = shared.attribute("defaultalternativetrackcolor")) != nullptr) {
   panel->setDefaultAlternativeTrackColor(a);
 }
 try {
  bool bok;
     int red = shared.attribute("redBackground").toInt(&bok);
     if(!bok) throw DataConversionException();
     int blue = shared.attribute("blueBackground").toInt(&bok);
     if(!bok) throw DataConversionException();
     int green = shared.attribute("greenBackground").toInt(&bok);
     if(!bok) throw DataConversionException();
     panel->setDefaultBackgroundColor(ColorUtil::colorToString( QColor(red, green, blue)));
     panel->setBackgroundColor( QColor(red, green, blue));
 } catch (DataConversionException e) {
     log->warn("Could not parse color attributes!");
 } catch (NullPointerException e) {  // considered normal if the attributes are not present
 }
 if (shared.attribute("useDirectTurnoutControl") != nullptr)
 {
  if (shared.attribute("useDirectTurnoutControl")==("yes"))
  {
   panel->setDirectTurnoutControl(true);
  }
 }

 // Set editor's option flags, load content after
 // this so that individual item flags are set as saved
 panel->initView();

 // load the contents
 QDomNodeList items = shared.childNodes();
 for (int i = 0; i < items.size(); i++)
 {
  // get the class, hence the adapter object to do loading
  QDomElement item = items.at(i).toElement();
  QString adapterName = item.attribute("class");
  if (log->isDebugEnabled())
  {
   QString id = "<null>";
   try
   {
    id = item.attribute("name");
    log->debug("Load " + id + " for [" + panel->getName() + "] via " + adapterName);
   }
   catch (Exception e) {
   }
  }
  try
  {
   adapterName = ClassMigration::migrateName(adapterName);

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
    adapter->setProperty("JavaClassName", adapterName);
    // and do it
    adapter->load(item, panel);
    if (!panel->loadOK())
    {
     result = false;
    }
   }
  }
  catch (ClassNotFoundException e)
  {
   log->error("Exception while loading " + item.tagName() + ":" + e.getMessage());
   result = false;
         //e.printStackTrace();
  }
 }
 panel->disposeLoadData();     // dispose of url correction data

 // final initialization of objects
 panel->setConnections();

 // display the results
 try {
     // set first since other attribute use this setting
     panel->setAllEditable(getBooleanValue(shared.attribute("editable")));
 } catch (DataConversionException e) {
     log->warn("unable to convert editable attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing editable attribute");
 }
 try {
     panel->setShowHelpBar(getBooleanValue(shared.attribute("showhelpbar")));
 } catch (DataConversionException e) {
     log->warn("unable to convert showhelpbar attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing showhelpbar attribute");
 }
 try {
     panel->setAntialiasingOn(getBooleanValue(shared.attribute("antialiasing")));
 } catch (DataConversionException e) {
     log->warn("unable to convert antialiasing attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing antialiasing attribute");
 }

 // set contents state
 QString slValue = "both";
 try {
     bool value = getBooleanValue(shared.attribute("sliders"));
     slValue = value ? "both" : "none";
 } catch (DataConversionException e) {
     log->warn("unable to convert sliders attribute");
 } catch (NullPointerException e) {  // considered normal if the attribute is not present
     log->debug("missing sliders attribute");
 }
 if ((a = shared.attribute("scrollable")) != "") {
     slValue = a;
 }
 panel->setScroll(slValue);

 panel->pack();
 panel->setLayoutDimensions(windowWidth, windowHeight, x, y, panelWidth, panelHeight);
 panel->editScene->setSceneRect(0,0,panelWidth, panelHeight);
 //panel->editPanel->scale(xScale, yScale); // added ACK
 panel->setVisible(true);    // always show the panel
 panel->resetDirty();

 panel->getTargetFrame()->menuBar()->setVisible(true);
 panel->menuBox->setChecked(true);

 panel->paintTargetPanel(panel->editScene); // force redraw


 // register the resulting panel for later configuration
 ConfigureManager* cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
 if (cm != nullptr) {
     cm->registerUser(panel);
 }
 //open Dispatcher frame if any Transits are defined, and open Dispatcher flag set on
 if(((TransitManager*)InstanceManager::getNullableDefault("TransitManager")))
 {
  try {
      bool value = getBooleanValue(shared.attribute("openDispatcher"));
      panel->setOpenDispatcherOnLoad(value);
      if (value) {
          DispatcherFrame* df = (DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame");
          df->loadAtStartup();
      }
  } catch (DataConversionException e) {
      log->warn("unable to convert openDispatcher attribute");
  } catch (NullPointerException e) {  // considered normal if the attribute is not present
      log->debug("missing openDispatcher attribute");
  }
 }
 return result;
}

/*public*/ int LayoutEditorXml::loadOrder() const{
    return Manager::PANELFILES;
}

/*private*/ bool LayoutEditorXml::getBooleanValue(QString val)
{
 QString txt = val.trimmed().toLower();
 if(txt == "yes" || txt == "true" )
  return true;
 if(txt == "no" || txt == "false" )
  return false;
 throw DataConversionException();
}
