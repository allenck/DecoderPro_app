#include "loadxml.h"
#include <QFile>
#include <QDebug>
#include "layouteditor.h"
#include "layoutslip.h"
#include "Roster/roster.h"
#include "turnoutoperationmanagerxml.h"
#include "turnoutoperationxml.h"
#include "abstractsensor.h"
#include "defaultroutemanager.h"
#include "abstractlight.h"
#include "abstractlightmanagerconfigxml.h"
#include "locoiconxml.h"
#include "paneleditorxml.h"
#include "controlpaneleditorxml.h"
#include "simpletimebasexml.h"
#include "analogclock2displayxml.h"
#include "abstractsignalheadmanagerxml.h"
#include "defaultsignalmastmanagerxml.h"
#include "defaultsignalmastlogicmanagerxml.h"
#include "signalheadiconxml.h"
#include "blockbosslogicxml.h"
#include "layoutblockmanagerxml.h"
#include "lnturnoutmanagerxml.h"
#include "internalturnoutmanagerxml.h"
#include "lnsensormanagerxml.h"
#include "internalsensormanagerxml.h"
#include "signalmasticonxml.h"
#include "defaultlogixmanagerxml.h"
#include "defaultconditionalmanagerxml.h"
#include "blockmanagerxml.h"
#include "warrantmanagerxml.h"
#include "oblockmanagerxml.h"
#include "entryexitpairsxml.h"
#include "multisensoriconxml.h"
#include "rfidsensormanagerxml.h"
#include "defaultsignalgroupmanagerxml.h"
#include "sectionmanagerxml.h"
#include "lnreportermanagerxml.h"
#include "rfidreportermanagerxml.h"
#include "internalreportermanagerxml.h"
#include "positionablecirclexml.h"
#include "positionableellipsexml.h"
#include "positionablerectanglexml.h"
#include "positionableroundrectxml.h"
#include "defaultaudiomanagerxml.h"
#include <QMetaType>

LoadXml::LoadXml(QObject *parent) :
    QObject(parent)
{
 log = new Logger("LoadXml");
 doc = QDomDocument("mydoc");
 sensorMgr = InstanceManager::instance()->sensorManagerInstance();
 blockMgr = InstanceManager::instance()->blockManagerInstance();
 editor = (LayoutEditor*)parent;
 _Colors << "Black"<<"Dark Gray"<<"Gray"<<"Light Gray"<<"White"<<"Red"<<"Orange"<<"Yellow"<<"Green"<<"Blue"<<"Magenta";
 _colors << QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) << QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red) << QColor(255, 170, 0) << QColor(Qt::yellow ) << QColor(Qt::green) <<QColor(Qt::blue) <<QColor(Qt::magenta)<<QColor();
 for(int i=0; i<_Colors.count(); i++)
  colorMap.insert(_Colors.at(i).toLower(),_colors.at(i));
}
int LoadXml::loadfile(QString fileName)
{
 QFile file(fileName);
 if(!file.open(QFile::ReadOnly | QFile::Text)) return 1;
 if(!doc.setContent(&file))
 {
  file.close();
 }
 file.close();

 QDomDocumentType type = doc.doctype();
 qDebug() << tr("name = %1, public id = %2, systemid = %3 internalSubset = %4").arg(type.name()).arg(type.publicId()).arg(type.systemId()).arg(type.internalSubset());
 XmlAdapter* adapter;

 QDomElement docElem = doc.documentElement();
 QDomNode n = docElem.firstChild();
 while(!n.isNull())
 {
  QDomElement element = n.toElement();
  if(!element.isNull())
  {
   qDebug()<< element.tagName();
   if(element.tagName()== "sensors")
   {
    processSensors(element);
   }
   else if(element.tagName()== "turnouts")
   {
    processTurnouts(element);
   }
   else if(element.tagName() == "lights")
    processLights(element);
   else if(element.tagName()== "reporters")
   {
    processReporters(element);
   }
   else if(element.tagName()== "memories" )
   {
    processMemories(element);
   }
   else if(element.tagName()== "signalheads")
   {
    processSignalHeads(element);
   }
   else if(element.tagName()== "signalmasts" )
   {
    processSignalMasts(element);
   }
   else if(element.tagName()== "signalgroups" )
   {
    processSignalGroups(element);
   }
   else if(element.tagName()== "blocks" )
   {
    processBlocks(element);
   }
   else if(element.tagName()== "layoutblocks" )
   {
    processLayoutBlocks(element);
   }
   else if(element.tagName() == "signalelements")
    processBlockBossLogic(element);
   else if(element.tagName()== "LayoutEditor" )
   {
    processLayoutEditor(element);
   }
   else if(element.tagName() == "timebase")
    processTimebase(element);
   else if(element.tagName() == "paneleditor")
    processPanelEditor(element);
   else if(element.tagName()== "routes")
    processRoutes(element);
   else if(element.tagName() == "signalmastlogics")
    processSignalMastLogics(element);
   else if(element.tagName() == "logixs")
    processLogix(element);
   else if(element.tagName() == "conditionals")
    processConditionals(element);
   else if(element.tagName() == "warrants")
    processWarrants(element);
   else if(element.tagName() == "oblocks")
    processOBlocks(element);
   else if(element.tagName() == "entryexitpairs")
    processEntryExitPairs(element);
   else if(element.tagName() == "sections")
    processSections(element);
   else if(element.tagName() == "positionableCircle")
    processPositionableCircle(element);
   else if(element.tagName() == "positionableEllipse")
    processPositionableEllipse(element);
   else if(element.tagName() == "positionableRectangle")
    processPositionableRectangle(element);
   else if(element.tagName() == "positionableRoundRect")
    processPositionableRoundRect(element);
   else if(element.tagName() == "audio")
    processAudio(element);
   else
    if((adapter = loadXmlAdapter(element)) != NULL)
     adapter->load(element);
   else
    log->warn(QString("No load logic for type %1").arg(element.tagName()));
  }
  n = n.nextSibling();
  qApp->processEvents();
 }
 return 0;
}
bool LoadXml::processBlocks(QDomElement blocks)
{
 BlockManagerXml* xml = new BlockManagerXml(this);
 return xml->load(blocks);
}

void LoadXml::processSensors(QDomElement e)
{
 if(e.attribute("class") == "jmri.jmrix.loconet.configurexml.LnSensorManagerXml")
 {
  LnSensorManagerXml* xml = new LnSensorManagerXml(this);
  xml->load(e);
 }
 else if(e.attribute("class") == "jmri.jmrix.rfid.configurexml.RfidSensorManagerXml")
 {
  RfidSensorManagerXml* xml = new RfidSensorManagerXml(this);
  xml->load(e);
 }
 else if(e.attribute("class") == "jmri.managers.configurexml.InternalSensorManagerXml")
 {
  InternalSensorManagerXml* xml = new  InternalSensorManagerXml(this);
  xml->load(e);
 }
 else
  Logger::error("No XML handler for " + e.attribute("class"));
}
void LoadXml::processTurnouts(QDomElement turnouts)
{
    if(turnouts.attribute("class") == "jmri.jmrix.loconet.configurexml.LnTurnoutManagerXml")
    {
        LnTurnoutManagerXml* xml = new  LnTurnoutManagerXml(this);
        xml->load(turnouts);
    }
    if(turnouts.attribute("class") == "jmri.managers.configurexml.InternalTurnoutManagerXml")
    {
        InternalTurnoutManagerXml* xml = new  InternalTurnoutManagerXml(this);
        xml->load(turnouts);
    }
}

void LoadXml::processLayoutBlocks(QDomElement e)
{
 LayoutBlockManagerXml* xml = new LayoutBlockManagerXml();
 xml->load(e);
}

void LoadXml::processRoutes(QDomElement routes)
{
 QDomNodeList routeList = routes.elementsByTagName("route");
 if (log->isDebugEnabled()) log->debug("Found "+QString("%1").arg(routeList.size())+" routes");
 DefaultRouteManager* tm = (DefaultRouteManager*)InstanceManager::routeManagerInstance();

 for (int i=0; i<routeList.size(); i++)
 {
  QDomElement route = routeList.at(i).toElement();
  QString sysName = getSystemName(route);
  if (sysName.isEmpty())
  {
   log->warn("unexpected NULL in systemName "+route.tagName());
   break;
  }

  QString userName = "";
  QString cTurnout = "";
  QString cTurnoutState = "";
  QString addedDelayTxt = "";
  QString routeLockedTxt = "";
  QString cLockTurnout = "";
  QString cLockTurnoutState = "";
  int addedDelay = 0;
  //if (!route.attribute("userName").isEmpty())
  userName =route.attribute("userName");

  //if (routeList.get(i).getAttribute("controlTurnout") != NULL)
   cTurnout =route.attribute("controlTurnout");
  //if (routeList.get(i).getAttribute("controlTurnoutState") != NULL)
   cTurnoutState =route.attribute("controlTurnoutState");
  //if (routeList.get(i).getAttribute("controlLockTurnout") != NULL)
   cLockTurnout =route.attribute("controlLockTurnout");
  //if (routeList.get(i).getAttribute("controlLockTurnoutState") != NULL)
   cLockTurnoutState =route.attribute("controlLockTurnoutState");
  if (!route.attribute("addedDelay").isEmpty())
  {
   addedDelayTxt =route.attribute("addedDelay");
   if (!addedDelayTxt.isEmpty())
   {
    addedDelay = addedDelayTxt.toInt();
   }
  }
  //if (routeList.get(i).getAttribute("routeLocked") != NULL)
   routeLockedTxt =route.attribute("routeLocked");

  if (log->isDebugEnabled()) log->debug("create route: ("+sysName+")("+
                                                    (userName.isEmpty()?"<NULL>":userName)+")");
  DefaultRoute* r = (DefaultRoute*)tm->provideRoute(sysName, userName);

  // load common parts
  loadCommon(r, route);

  if (r!=NULL)
  {
   // add control turnout if there is one
   if (!cTurnout.isEmpty())
   {
    r->setControlTurnout(cTurnout);
    if (!cTurnoutState.isEmpty())
    {
     if (cTurnoutState==("THROWN"))
     {
      r->setControlTurnoutState(Route::ONTHROWN);
     }
     else if (cTurnoutState==("CHANGE"))
     {
      r->setControlTurnoutState(Route::ONCHANGE);
     }
     else if (cTurnoutState==("VETOCLOSED"))
     {
      r->setControlTurnoutState(Route::VETOCLOSED);
     }
     else if (cTurnoutState==("VETOTHROWN"))
     {
      r->setControlTurnoutState(Route::VETOTHROWN);
     }
     else
     {
      r->setControlTurnoutState(Route::ONCLOSED);
     }
    }
    else
    {
     log->error("cTurnoutState was NULL!");
    }
   }
   // set added delay
   r->setRouteCommandDelay(addedDelay);

   // determine if route locked
   if (!routeLockedTxt.isEmpty() && routeLockedTxt==("True"))
    r->setLocked(true);

   //add lock control turout if there is one
   if (!cLockTurnout.isEmpty())
   {
    r->setLockControlTurnout(cLockTurnout);
    if (!cLockTurnoutState.isEmpty())
    {
     if (cLockTurnoutState==("THROWN"))
     {
      r->setLockControlTurnoutState(Route::ONTHROWN);
     }
     else if (cLockTurnoutState==("CHANGE"))
     {
      r->setLockControlTurnoutState(Route::ONCHANGE);
     }
     else
     {
      r->setLockControlTurnoutState(Route::ONCLOSED);
     }
    }
    else
    {
     log->error("cLockTurnoutState was NULL!");
    }
   }

   // load output turnouts if there are any - old format first (1.7.6 and before)
   QDomNodeList routeTurnoutList = route.elementsByTagName("routeTurnout");
   if (routeTurnoutList.size() > 0)
   {
    // This route has turnouts
    for (int k=0; k<routeTurnoutList.size(); k++)
    {
     QDomElement routeTurnout = routeTurnoutList.at(i).toElement();
     if (routeTurnout.attribute("systemName").isEmpty())
     {
      log->warn("unexpected NULL in systemName "+routeTurnout.tagName());
      break;
     }
     QString tSysName = routeTurnout.attribute("systemName");
     QString rState = routeTurnout.attribute("state");
     int tSetState = Turnout::CLOSED;
     if (rState==("THROWN"))
     {
        tSetState = Turnout::THROWN;
    }
    else if (rState==("TOGGLE"))
    {
     tSetState = Route::TOGGLE;
    }
    // Add turnout to route
    r->addOutputTurnout(tSysName, tSetState);
   }
  }
  // load output turnouts if there are any - new format
  routeTurnoutList = route.elementsByTagName("routeOutputTurnout");
  if (routeTurnoutList.size() > 0)
  {
   // This route has turnouts
   for (int k=0; k<routeTurnoutList.size(); k++)
   {
    QDomElement routeTurnout = routeTurnoutList.at(k).toElement();
    if (routeTurnout.attribute("systemName").isNull())
    {
     log->warn("unexpected NULL in systemName "+routeTurnout.tagName());
     break;
    }
    QString tSysName = routeTurnout.attribute("systemName");
    QString rState = routeTurnout.attribute("state");
    int tSetState = Turnout::CLOSED;
    if (rState==("THROWN"))
    {
        tSetState = Turnout::THROWN;
    }
    else if (rState==("TOGGLE")) {
        tSetState = Route::TOGGLE;
    }
    // If the Turnout has already been added to the route and is the same as that loaded,
    // we will not re add the turnout.
    if (!r->isOutputTurnoutIncluded(tSysName))
    {

     // Add turnout to route
     r->addOutputTurnout(tSysName, tSetState);

     // determine if turnout should be locked
     Turnout* t = r->getOutputTurnout(k);
     if (r->getLocked())
     {
      t->setLocked(Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, true);
     }
    }
   }
  }
  // load output sensors if there are any - new format
  routeTurnoutList = route.elementsByTagName("routeOutputSensor");
  if (routeTurnoutList.size() > 0)
  {
   QDomElement routeTurnout = routeTurnoutList.at(i).toElement();
   // This route has turnouts
   for (int k=0; k<routeTurnoutList.size(); k++)
   {
    if (routeTurnout.attribute("systemName").isNull())
    {
     log->warn("unexpected NULL in systemName "+routeTurnout.tagName());
     break;
    }
    QString tSysName = routeTurnout.attribute("systemName");
    QString rState = routeTurnout.attribute("state");
    int tSetState = Sensor::INACTIVE;
    if (rState==("ACTIVE"))
    {
     tSetState = Sensor::ACTIVE;
    }
    else if (rState==("TOGGLE"))
    {
     tSetState = Route::TOGGLE;
    }
    // If the Turnout has already been added to the route and is the same as that loaded,
    // we will not re add the turnout.
    if (r->isOutputSensorIncluded(tSysName))
    {
     break;
    }
    // Add turnout to route
    r->addOutputSensor(tSysName, tSetState);
   }
  }
   // load sound, script files if present
   QDomElement fileElement =route.firstChildElement("routeSoundFile");
   if (!fileElement.isNull())
   {
    // convert to absolute path name
    r->setOutputSoundName(FileUtil::getExternalFilename(fileElement.attribute("name")));
   }
   fileElement =routeList.at(i).firstChildElement("routeScriptFile");
   if (!fileElement.isNull())
   {
    r->setOutputScriptName(FileUtil::getExternalFilename(fileElement.attribute("name")) );
   }
   // load turnouts aligned sensor if there is one
   fileElement =route.firstChildElement("turnoutsAlignedSensor");
   if (!fileElement.isNull())
   {
    r->setTurnoutsAlignedSensor(fileElement.attribute("name"));
   }

   // load route control sensors, if there are any
   QDomNodeList routeSensorList = route.elementsByTagName("routeSensor");
   if (routeSensorList.size() > 0)
   {
    // This route has sensors
    for (int k=0; k<routeSensorList.size(); k++)
    {
     QDomElement routeSensor = routeSensorList.at(k).toElement();
     if ( routeSensor.attribute("systemName").isEmpty())
     {
      log->warn("unexpected NULL in systemName "+routeSensor.tagName());
      break;
     }
     int mode = Route::ONACTIVE;  // default mode
     if ( !routeSensor.attribute("mode").isEmpty())
     {
      QString sm = routeSensor.attribute("mode");
      if (sm==("onActive"))
       mode = Route::ONACTIVE;
      else if (sm==("onInactive"))
       mode = Route::ONINACTIVE;
      else if (sm==("onChange"))
       mode = Route::ONCHANGE;
      else if (sm==("vetoActive"))
       mode = Route::VETOACTIVE;
      else if (sm==("vetoInactive"))
       mode = Route::VETOINACTIVE;
      else
       log->warn("unexpected sensor mode in route "+sysName+" was "+sm);
     }

     // Add Sensor to route
     r->addSensorToRoute(routeSensor.attribute("systemName"), mode);
    }
   }
   // and start it working
   r->activateRoute();
  }
  else
  {
   log->error ("failed to create Route: "+sysName);
  }
 }
}

void LoadXml::processLayoutEditor(QDomElement e)
{
 qDebug()<< tr("class= %1").arg(e.attribute("class"));
 editor->setLayoutName(e.attribute("name"));
 editor->mainlineTrackWidth = e.attribute("mainlinetrackwidth").toInt();
 editor->trackWidth = e.attribute("sidetrackwidth").toInt();
 editor->defaultTrackColor = colorMap.value(e.attribute("defaulttrackcolor"), QColor(Qt::black));
 layoutSize = QSize(e.attribute("width").toInt(), e.attribute("height").toInt());
 editor->panelWidth = layoutSize.width();
 editor->panelHeight = layoutSize.height();
 editor->editScene->setSceneRect(0,0,layoutSize.width(), layoutSize.height());
 editor->on_actionShow_grid_in_edit_mode_toggled(e.attribute("drawgrid")=="yes");
 editor->on_actionEdit_mode_toggled(e.attribute("editable")=="yes" );
 editor->on_actionAllow_repositioning_toggled(e.attribute("positionable")=="yes");
 editor->on_actionAllow_layout_control_toggled(e.attribute("controlling")=="yes");
 editor->on_actionEnable_antialiasing_smoother_lines_toggled(e.attribute("antialiasing")=="yes");
 editor->on_actionAllow_turnout_animation_toggled(e.attribute("animating")=="yes");
 editor->on_actionShow_turnout_circles_toggled(e.attribute("turnoutcircles")=="yes");
 editor->setScale(e.attribute("xscale").toDouble(), e.attribute("yscale").toDouble());
 editor->on_actionSnap_to_grid_when_adding_toggled(e.attribute("snaponadd")=="yes");
 editor->on_actionSnap_to_grid_when_moving_toggled(e.attribute("snaponmove")=="yes");
 editor->setDefaultTextColor(e.attribute("defaulttextcolor"));
 editor->setDefaultTrackColor(e.attribute("defaulttrackcolor"));
// TODO:  turnoutbx="20.0" turnoutcx="20.0" turnoutwid="10.0" xoverlong="30.0" xoverhwid="10.0" xovershort="10.0">
 editor->windowWidth = e.attribute("windowwidth").toInt();
 editor->windowHeight = e.attribute("windowheight").toInt();
 if(editor->windowWidth > 0 && editor->windowHeight > 0)
  editor->resize(editor->windowWidth, editor->windowHeight);

 QDomNode n = e.firstChild();
 bool bRepaint = false;
 while(!n.isNull())
 {
  QDomElement element = n.toElement();
  QString name = element.tagName();
  //qDebug() << tr("Layout editor element %1").arg(name);
  if(name == "sensoricon")
  {
//   editor->xLoc = element.attribute("x").toInt();
//   editor->yLoc = element.attribute("y").toInt();
//   editor->addSensor(element.attribute("sensor"));
   QPointF  loc = scaleLoc( element.attribute("x").toInt(), element.attribute("y").toInt());

   //emit newSensor(element.attribute("sensor"),loc.x(), loc.y());
   editor->xLoc = loc.x();
   editor->yLoc = loc.y();
   editor->addSensor(element.attribute("sensor"));
  }
  if(name == "locoicon")
  {
 #if 0 // see below
      LocoIcon* l = new LocoIcon(editor);
      //l->setLocation(loc.x(), loc.y());
      // create the objects
      QString textName = "error";
      try
      {
       textName = element.attribute("text");
      } catch ( Exception e)
      {
       log->error("failed to get loco text attribute ex= ");
      }
      QString name = "error";
      NamedIcon* icon;
      try
      {
       name = element.attribute("icon");
      }
      catch (Exception e)
      {
       log->error("failed to get icon attribute ex= ");
      }
      if (name==("yes"))
      {
       icon = loadIcon(l, "icon", element, "LocoIcon", editor);
      }
      else
      {
       icon = NamedIcon::getIconByName(name);
       if (icon==NULL)
       {
        icon = editor->loadFailed("LocoIcon", name);
        if (icon==NULL)
        {
         log->info("LocoIcon icon removed for url= "+name);
         return;
        }
       }
      }
      l->updateIcon(icon);

      try
      {
       int x = element.attribute("dockX").toInt();
       int y = element.attribute("dockY").toInt();
       l->setDockingLocation(x, y);
   //           l.dock();
      }
      catch (Exception e)
      {
       log->warn("failed to get docking location= "+e.getMessage());
      }

      QString rosterId = "";
      rosterId = element.attribute("rosterentry");
      if(rosterId != "")
      {
       RosterEntry* entry = Roster::instance()->entryFromTitle(rosterId);
       l->setRosterEntry(entry);
      }
      else
      {
       log->debug("no roster entry for "+rosterId+", ex= ");
      }
      editor->putLocoIcon(l, textName);
      // load individual item's option settings after editor has set its global settings
      loadCommonAttributes(l, LayoutEditor::MARKERS, element);
      loadTextInfo(l, element);
#else
   LocoIconXml* xml = new LocoIconXml(this);
   xml->setDoc(doc);
   xml->load(element, editor);
#endif
  }
  else
  if(name == "multisensoricon")
  {
   MultiSensorIconXml* xml = new MultiSensorIconXml(this);
   xml->load(element, editor);
  }
  else
  if(name == "fastclock")
  {
   AnalogClock2DisplayXml* xml = new AnalogClock2DisplayXml(this);
   xml->setDoc(doc);
   xml->load(element, editor);
  }
  else
  if(name == "positionablelabel")
  {
   QPointF  loc = scaleLoc( element.attribute("x").toInt(), element.attribute("y").toInt());

   editor->xLoc = loc.x();
   editor->yLoc = loc.y();
   PositionableLabel* label = editor->addLabel(element.attribute("text"));

   PositionableLabelXml* xml = new PositionableLabelXml(this);
   xml->load(element, editor);
  }
  else if(name == "signalheadicon")
  {
   SignalHeadIconXml* xml = new SignalHeadIconXml(this);
   xml->setDoc(doc);
   xml->load(element, editor);

  }
  else if(name == "signalmasticon")
  {
   SignalMastIconXml* xml = new SignalMastIconXml(this);
   xml->setDoc(doc);
   xml->load(element, editor);
  }
  else if(name == "memoryicon")
  {
   QPointF  loc = scaleLoc( element.attribute("x").toInt(), element.attribute("y").toInt());
   QString _class = element.attribute("class");

   editor->xLoc = loc.x();
   editor->yLoc = loc.y();
   MemoryIcon* memoryIcon = editor->addMemory(element.attribute("memory"));
   memoryIcon->setMemory("text");
  }
  if(name =="layoutturnout")
  {
   QString ident;
   QPointF  locF = scaleLoc( element.attribute("xcen").toDouble(), element.attribute("ycen").toDouble());
   //LayoutTurnout* t = editor->addLayoutTurnout(ident = element.attribute("ident"),element.attribute("type").toInt(), 0, locF);
   LayoutTurnout* t = new LayoutTurnout(ident = element.attribute("ident"),element.attribute("type").toInt(),locF,0,0,0,editor);
   t->setCoordsCenter(locF);

   QPointF locB = scaleLoc(element.attribute("xb").toDouble(), element.attribute("yb").toDouble());
   t->setCoordsB(locB);
   QPointF locC = scaleLoc(element.attribute("xc").toDouble(), element.attribute("yc").toDouble());
   t->setCoordsC(locC);
   t->connectAName = element.attribute("connectaname");
   t->connectBName = element.attribute("connectbname");
   t->connectCName = element.attribute("connectcname");
   if(element.hasAttribute("connectdname"))
    t->connectDName = element.attribute("connectdname");
   t->tBlockName = element.attribute("blockname");
   t->tBlockBName = element.attribute("blockbname");
   t->tBlockCName = element.attribute("blockcname");
   t->tBlockDName = element.attribute("blockdname");
   t->tTurnoutName = element.attribute("turnoutname");
   t->tSecondTurnoutName = element.attribute("secondturnoutname");
   t->setContinuingSense(element.attribute("continuing").toInt());
   t->setDisabled(element.attribute("disabled")=="yes");
   t->setDisableWhenOccupied(element.attribute("disableWhenOccupied")=="yes");
   t->turnoutName = element.attribute("turnoutname"); // is this redundant?
   editor->turnoutList->append(t);
  }
  else
  if(name == "tracksegment")
  {
   QString ident;
   TrackSegment* t = new TrackSegment(ident = element.attribute("ident"),
                                      element.attribute("connect1name"),
                                      element.attribute("type1").toInt(),
                                      element.attribute("connect2name"),
                                      element.attribute("type2").toInt(),
                                      element.attribute("dashed")=="yes",
                                      element.attribute("mainline")=="yes",
                                      element.attribute("hidden")=="yes",
                                      editor);
   if(t != NULL)
   {
    t->setArc(element.attribute("arc")=="yes");
    t->setFlip(element.attribute("flip")=="yes");
    t->setCircle(element.attribute("circle")=="yes");
    t->setLayoutBlockByName(element.attribute("blockname"));
    t->tBlockName = element.attribute("blockname");
    t->tConnect1Name = element.attribute("connect1name");
    t->tConnect2Name = element.attribute("connect2name");
   }
   editor->trackList->append(t);
  }
  else
  if(name == "positionablepoint")
  {
   bRepaint = true; // turn on flag to repaint panel when done.
   QPointF currentPoint = scaleLoc(element.attribute("x").toDouble(), element.attribute("y").toDouble());
   // create object
   QString ident;
   PositionablePoint* o = new PositionablePoint(ident = element.attribute("ident"),                                                element.attribute("type").toInt(), currentPoint, editor);
   if (o!=NULL)
    editor->pointList->append(o);
   o->trackSegment1Name = element.attribute("connect1name");
   o->trackSegment2Name = element.attribute("connect2name");
  }
  else if(name == "levelxing")
  {
   QString ident;
   QPointF  locF = scaleLoc( element.attribute("xcen").toDouble(), element.attribute("ycen").toDouble());
   LevelXing* x = new LevelXing(ident = element.attribute("ident"), locF, editor);

   QPointF locA = scaleLoc(element.attribute("xa").toDouble(), element.attribute("ya").toDouble());
   x->setCoordsA(locA);
   QPointF locB = scaleLoc(element.attribute("xb").toDouble(), element.attribute("yb").toDouble());
   x->setCoordsB(locB);
   x->connectAName = element.attribute("connectaname");
   x->connectBName = element.attribute("connectbname");
   x->connectCName = element.attribute("connectcname");
   x->connectDName = element.attribute("connectdname");
   x->tBlockNameAC = element.attribute("blocknameac");
   x->tBlockNameBD = element.attribute("blocknamebd");
   x->setSignalAName(element.attribute("signalaname"));
   x->setSignalBName(element.attribute("signalbname"));
   x->setSignalCName(element.attribute("signalcname"));
   x->setSignalDName(element.attribute("signaldname"));
   if(element.hasChildNodes())
   {
    QDomNode n = element.firstChild();
    while (!n.isNull())
    {
     QDomElement e = n.toElement();
     if(e.tagName() =="signalAMast")
     {
      QString mast = e.text();
      if(!mast.isEmpty())
       x->setSignalAName(mast);
     }
     if(e.tagName() == "signalBMast")
     {
      QString mast = e.text();
      if(!mast.isEmpty())
       x->setSignalBName(mast);
     }
     if(e.tagName() == "signalCMast")
     {
      QString mast = e.text();
      if(!mast.isEmpty())
       x->setSignalCName(mast);
     }
     if(e.tagName() == "signalDMast")
     {
      QString mast = e.text();
      if(!mast.isEmpty())
       x->setSignalDName(mast);
     }
     n = e.nextSibling();
    }
   }
   editor->xingList->append(x);
  }
  else if(name == "layoutSlip")
  {
   QString ident;
   QPointF  locF = scaleLoc( element.attribute("xcen").toDouble(),
                             element.attribute("ycen").toDouble());
   LayoutSlip* s = new LayoutSlip(ident=element.attribute("ident"),locF,0,editor, element.attribute("slipType").toInt());
   QPointF locA = scaleLoc(element.attribute("xa").toDouble(), element.attribute("ya").toDouble());
   s->setCoordsA(locA);
   QPointF locB = scaleLoc(element.attribute("xb").toDouble(), element.attribute("yb").toDouble());
   s->setCoordsB(locB);
   s->connectAName = element.attribute("connectaname");
   s->connectBName = element.attribute("connectbname");
   s->connectCName = element.attribute("connectcname");
   s->connectDName = element.attribute("connectdname");
   s->tBlockName = element.attribute("blockname");
   s->signalA1Name = element.attribute("signala1name");
   s->signalB1Name = element.attribute("signalb1name");
   s->signalC1Name = element.attribute("signalc1name");
   s->signalD1Name = element.attribute("signald1name");
   s->signalA2Name = element.attribute("signala2name");
   s->signalB2Name = element.attribute("signalb2name");
   s->signalC2Name = element.attribute("signalc2name");
   s->signalD2Name = element.attribute("signald2name");
   s->signalAMast = element.attribute("signalAMast");
   s->signalBMast = element.attribute("signalBMast");
   s->signalCMast = element.attribute("signalCMast");
   s->signalDMast = element.attribute("signalDMast");
   s->setSensorA( element.attribute("sensorA"));
   s->setSensorB( element.attribute("sensorB"));
   s->setSensorC(element.attribute("sensorC"));
   s->setSensorD(element.attribute("sensorD"));
   s->turnoutName = element.attribute("turnout");
   s->turnoutBName = element.attribute("turnoutB");

   editor->slipList->append(s);
  }
  QDomNode m = element.firstChild();
  while(!m.isNull())
  {
   QDomElement e = m.toElement();

   m = m.nextSibling();
  }
  n = n.nextSibling();
 }
 if(bRepaint)
 {
  for(int i=0; i < layoutBlocks.count(); i++)
  {
   LayoutBlock* block = layoutBlocks.at(i);
   block->initializeLayoutBlock();
  }
  static_cast<LayoutBlockManager*>(InstanceManager::getDefault("LayutBlockManager"))->initializeLayoutBlockPaths();
  for (int i=0; i < editor->pointList->count(); i++)
  {
   PositionablePoint* o = editor->pointList->at(i);
   o->setObjects(editor);
  }
  //QString ident = o->getID();
  // update track segments and turnouts referring to this point.
  for(int i=0; i < editor->trackList->count(); i++)
  {
   TrackSegment* t = editor->trackList->at(i);
   t->setObjects(editor);
  }
 }
 for(int i = 0; i < editor->turnoutList->count();i++)
 {
  LayoutTurnout* to = editor->turnoutList->at(i);
  to->setObjects(editor);
 }
 for(int i = 0; i < editor->xingList->count(); i ++)
 {
  LevelXing* x = editor->xingList->at(i);
  x->setObjects(editor);
 }
 for(int i = 0; i < editor->slipList->count(); i++)
 {
  LayoutSlip* s = editor->slipList->at(i);
  s->setObjects(editor);
 }
 editor->paintTargetPanel(editor->editScene);
}

QPoint LoadXml::scaleLoc(int x, int y)
{
 //return QPoint( (x * 960)/layoutSize.width(), (y*400)/layoutSize.height());
 return QPoint(x,y);
}
QPointF LoadXml::scaleLoc(double x, double y)
{
 //return QPointF( (x * 960)/layoutSize.width(), (y*400)/layoutSize.height());
    return QPointF(x,y);
}
bool LoadXml::processReporters(QDomElement e)
{
// bool result=true;
// ProxyReporterManager* tm = (ProxyReporterManager*) InstanceManager::reporterManagerInstance();
// QDomNodeList reporterList = element.childNodes();
// for(int i=0; i < reporterList.count(); i++)
// {
//  QString sysName = reporterList.at(i).toElement().attribute("systemName");
//  if (sysName.isEmpty())
//  {
//   //log->warn("unexpected NULL in systemName "+reporterList.get(i)+" "+reporterList.get(i).getAttributes());
//   result = false;
//   break;
//  }

//  QString userName = reporterList.at(i).toElement().attribute("userName");

//  if (log->isDebugEnabled()) log->debug("create Reporter: ("+sysName+")("+(userName==NULL?"<NULL>":userName)+")");
//   Reporter* r = tm->newReporter(sysName, userName);
//   if(r == NULL) return false;
//   Q_ASSERT(r!=NULL);
//   loadCommon(r, reporterList.at(i).toElement());
// }
    if(e.attribute("class") == "jmri.jmrix.loconet.configurexml.LnReporterManagerXml")
    {
        LnReporterManagerXml* xml = new LnReporterManagerXml(this);
        xml->load(e);
    }
    if(e.attribute("class") == "jmri.jmrix.loconet.configurexml.RfidReporterManagerXml")
    {
        RfidReporterManagerXml* xml = new RfidReporterManagerXml(this);
        xml->load(e);
    }
    if(e.attribute("class") == "jmri.jmrix.loconet.configurexml.InternalReporterManagerXml")
    {
        InternalReporterManagerXml* xml = new  InternalReporterManagerXml(this);
        xml->load(e);
    }
    return true;
}
/**
 * Load common items:
 * <ul>
 * <li>comment
 * </ul>
 * The username is not loaded, because it
 * had to be provided in the ctor earlier.
 *
 * @param t The NamedBean being loaded
 * @param elem The JDOM element containing the NamedBean
 */
/*protected*/ void LoadXml::loadCommon(NamedBean* t, QDomElement elem) {
    loadComment(t, elem);
    loadProperties(t, elem);
}

/**
 * Load the comment attribute into a NamedBean
 * from one element of
 * a list of Elements defining NamedBeans
 * @param t The NamedBean being loaded
 * @param beanList List, where each entry is an Element
 * @param i index of Element in list to examine
 */
void LoadXml::loadComment(NamedBean* t, QDomNodeList beanList, int i)
{
 loadComment(t, beanList.at(i).toElement());
}

/**
 * Load the comment attribute into a NamedBean
 * from an Element defining a NamedBean
 * @param t The NamedBean being loaded
 * @param elem The existing Element
 */
void LoadXml::loadComment(NamedBean* t, QDomElement elem)
{
 // load comment, if present
 QString c = elem.firstChildElement("comment").text();
 if (c != NULL)
 {
  t->setComment(c);
 }
}

/**
 * Load all key/value properties
 * @param t The NamedBean being loaded
 * @param elem The existing Element
 */
void LoadXml::loadProperties(NamedBean* /*t*/, QDomElement elem)
{
 QDomElement p = elem.firstChildElement("properties");
 if (p.isNull()) return;
#if 0
 foreach (Object next : p.getChildren("property"))
 {
  QDomElement e = (Element) next;
        try {
            Class<?> cl;
            Constructor<?> ctor;
            // create key object
            cl = Class.forName(e.getChild("key").getAttributeValue("class"));
            ctor = cl.getConstructor(new Class<?>[] {String.class});
            Object key = ctor.newInstance(new Object[] {e.getChild("key").getText()});

            // create value object
            Object value = NULL;
            if (e.getChild("value") != NULL) {
                cl = Class.forName(e.getChild("value").getAttributeValue("class"));
                ctor = cl.getConstructor(new Class<?>[] {String.class});
                value = ctor.newInstance(new Object[] {e.getChild("value").getText()});
            }

            // store
            t.setProperty(key, value);
        } catch (Exception ex) {
            log->error("Error loading properties", ex);
        }
 }
#endif
}

void LoadXml::processMemories(QDomElement memories)
{
 // ensure the master object exists
 InstanceManager::memoryManagerInstance();
 /**
  * Utility method to load the individual Memory objects.
  * If there's no additional info needed for a specific Memory type,
  * invoke this with the parent of the set of Memory elements.
  * @param memories Element containing the Memory elements to load.
  */
 //@SuppressWarnings("unchecked")
 //public void loadMemories(Element memories) {
 //List<Element> memoryList = memories.getChildren("memory");
 QDomNodeList memoryList = memories.childNodes();
 if (log->isDebugEnabled()) log->debug(tr("Found ")+QString("%1").arg(memoryList.size())+tr(" Memory objects"));
 DefaultMemoryManager* tm = (DefaultMemoryManager*)InstanceManager::memoryManagerInstance();

 for (int i=0; i<memoryList.size(); i++)
 {
  QString sysName = getSystemName(memoryList.at(i).toElement());
  if (sysName == NULL) {
     log->warn(tr("unexpected NULL in systemName ")+(memoryList.at(i).toElement().text()));
     break;
  }

  QString userName = getUserName(memoryList.at(i).toElement());

  if (log->isDebugEnabled()) log->debug("create Memory: ("+sysName+")("+(userName==NULL?"<NULL>":userName)+")");
  Memory* m = tm->newMemory(sysName, userName);
  if (memoryList.at(i).toElement().attribute("value") != NULL)
  {
     loadValue(memoryList.at(i).toElement(), m);
  }
  // load common parts
  loadCommon(m, memoryList.at(i).toElement());
 }
}
void LoadXml::loadValue(QDomElement memory, Memory* m)
{
 QString value = memory.attribute("value");
 if(memory.attribute("valueClass")!="")
 {
  QString adapter = memory.attribute("valueClass");
  if (adapter==("jmri.jmrit.roster.RosterEntry")) // ???
  {
   RosterEntry* re = Roster::instance()->getEntryForId(value);
   ((AbstractMemory*)m)->setValue(VPtr<RosterEntry>::asQVariant(re));
   return;
  }
 }
 ((AbstractMemory*)m)->setValue(QVariant::fromValue(value));
}
/**
 * Get the username attribute from one element of
 * a list of Elements defining NamedBeans
 * @param beanList List, where each entry is an Element
 * @param i index of Element in list to examine
 */
/*protected*/ QString LoadXml::getUserName(QDomNodeList beanList, int i) {
    return getUserName(beanList.at(i).toElement());
}
/**
 * Get the user name from an Element defining a NamedBean
 * <ul>
 * <li>Before 2.9.6, this was an attribute
 * <li>Starting in 2.9.6, this was stored as both attribute and element
 * <li>Starting in 3.1/2.11.1, this will be just an element
 * </ul>
 * @param elem The existing Element
 */
/*protected*/ QString LoadXml::getUserName(QDomElement elem)
{
 QString userName = elem.attribute("userName");
 return userName;

// QDomNode n = elem.firstChildElement();
// while(!n.isNull())
// {
//  if(n.toElement().tagName() == "userName")
//  {
////    if ( elem.getChild("userName") != NULL)
////    {
////        return elem.getChild("userName").getText();
////    }
//   if(!n.toElement().text().isEmpty())
//       return n.toElement().text();
////    if ( elem.getAttribute("userName") != NULL) {
////        return elem.getAttribute("userName").getValue();
////    } return NULL;
//   if(!n.toElement().attribute("userName").isEmpty())
//       return n.toElement().attribute("userName");
//  }
//  n = n.nextSibling();
// }
// return "";
}
/* Get the system name from an Element defining a NamedBean
* <ul>
* <li>Before 2.9.6, this was an attribute
* <li>Starting in 2.9.6, this was stored as both attribute and element
* <li>Starting in 3.1/2.10.1, this will be just an element
* </ul>
* @param elem The existing Element
*/
/*protected*/ QString LoadXml::getSystemName(QDomElement elem)
{
 QString sysName = elem.attribute("systemName");
 return sysName;
// QDomNode n = elem.firstChildElement();
// while(!n.isNull())
// {
//  if(n.toElement().tagName() == "userName")
//  {
////   if ( elem.getChild("systemName") != NULL) {
////       return elem.getChild("systemName").getText();
////   }
//   if(!n.toElement().text().isEmpty())
//    return n.toElement().text();

////   if ( elem.getAttribute("systemName") != NULL) {
////       return elem.getAttribute("systemName").getValue();
////   } return NULL;
//   if(!n.toElement().attribute("systemName").isEmpty())
//    return n.toElement().attribute("userName");
//  }
//  n = n.nextSibling();
// }
// return "";
}
/*public*/ NamedIcon* LoadXml::loadIcon(PositionableLabel* l, QString attrName, QDomElement element, QString name, LayoutEditor* ed)
{
 NamedIcon* icon = getNamedIcon(attrName, element, name, ed);
 if (icon != NULL)
 {
  //try
  {
   int deg = 0;
   double scale = 1.0;
   QDomElement elem = element.firstChildElement(attrName);
   if (!elem.isNull())
   {
    QString a = elem.attribute("degrees");
    if (!a.isEmpty())
    {
     deg = a.toInt();
    }
    a =  elem.attribute("scale");
    if (!a.isEmpty())
    {
     scale = elem.attribute("scale").toDouble();
    }
    icon->setLoad(deg, scale, l);
    if ( deg==0)
    {
     // "rotate" attribute is JMRI 2.9.3 and before
     a = elem.attribute("rotate");
     if (!a.isEmpty())
     {
      int rotation = a.toInt();
      // 2.9.3 and before, only unscaled icons rotate
      if (scale == 1.0) icon->setRotation(rotation, l);
     }
     // "rotation" element is JMRI 2.9.4 and after
     QDomElement e = elem.firstChildElement("rotation");
     if (!e.isNull())
     {
      // ver 2.9.4 allows orthogonal rotations of scaled icons
      int rotation = e.text().toInt();
      icon->setRotation(rotation, l);
     }
    }
   }
  }
  //catch (DataConversionException dce) {}
 }
 return icon;
}


/*protected*/ NamedIcon* LoadXml::getNamedIcon(QString childName, QDomElement element,
                                        QString name, LayoutEditor* ed)
{
 NamedIcon* icon = NULL;
 QDomElement elem = element.firstChildElement(childName);

 if (!elem.isNull())
 {
  QString iconName = elem.attribute("url");
  iconName = iconName.replace("program:", ":/");
  icon = NamedIcon::getIconByName(iconName);
  if (icon==NULL)
  {
   icon = ed->loadFailed(name, iconName);
   if (icon==NULL)
   {
    log->info(name+" removed for url= "+iconName);
   }
  }
 }
 else
 {
  log->debug("getNamedIcon: child element \""+childName+"\" not found in element "+element.tagName());
 }
 return icon;
}
/*protected*/ void LoadXml::loadTextInfo(PositionableLabel* l, QDomElement element)
{
 if (log->isDebugEnabled()) log->debug("loadTextInfo");
 PositionablePopupUtil* util = l->getPopupUtility();
 if (util==NULL)
 {
  log->warn("PositionablePopupUtil is NULL! "+element.tagName());
  return;
 }
 QString a = element.attribute("size","10");
 bool bOk=false;
 if (!a.isEmpty()) util->setFontSize(a.toFloat(&bOk));
 if(!bOk)
  log->warn("invalid size attribute value");

 a = element.attribute("style", "0");
 if (!a.isEmpty())
 {
  int style = a.toInt(&bOk);
  int drop = 0;
  switch (style)
  {
  case 0: drop = 1; //0 Normal
   break;
  case 2: drop = 1; //italic
   break;
  }
  util->setFontStyle(style, drop);
 }
 if(!bOk)
 {
  log->warn("invalid style attribute value");
 }

 // set color if needed
 bool bOk1=false;
 bOk=true;
 int red = element.attribute("red","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 int blue = element.attribute("blue","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 int green = element.attribute("green","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 if(bOk)
  util->setForeground( QColor(red, green, blue));
 else
     log->warn(tr("%1 Could not parse color attributes!").arg(element.tagName()));

 bOk = true;
 red = element.attribute("redBack","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 blue = element.attribute("blueBack","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 green = element.attribute("greenBack","0").toInt(&bOk1);
 if(!bOk1) bOk =false;
 if(bOk)
  util->setBackgroundColor(QColor(red, green, blue));
 else
  log->warn(tr("%1 Could not parse background color attributes!").arg(element.tagName()));

  int fixedWidth=0;
  int fixedHeight=0;
  fixedHeight=element.attribute("fixedHeight", "0").toInt(&bOk);
  if(!bOk)       log->warn("Could not parse fixed Height attributes!");

  fixedWidth=element.attribute("fixedWidth", "0").toInt(&bOk);
  if(!bOk)       log->warn("Could not parse fixed Width attribute!");
  if (!(fixedWidth==0 && fixedHeight==0))
       util->setFixedSize(fixedWidth, fixedHeight);
  int margin=0;
  if ((util->getFixedWidth()==0) || (util->getFixedHeight()==0))
  {

      margin=element.attribute("margin", "0").toInt(&bOk);
   if(bOk)
    util->setMargin(margin);
   else           log->warn("Could not parse margin attribute!");

   util->setBorderSize(element.attribute("borderSize", "0").toInt(&bOk));
   int red = element.attribute("redBorder", "0").toInt(&bOk1);
   if(!bOk1) bOk =false;
   int blue = element.attribute("blueBorder","0").toInt(&bOk1);
   if(!bOk1) bOk =false;
   int green = element.attribute("greenBorder","0").toInt(&bOk1);
   if(!bOk1) bOk =false;
   if(bOk)
    util->setBorderColor(QColor(red, green, blue));
   else       log->warn("Could not parse border attributes!");

   a = element.attribute("justification");
   if(!a.isEmpty())
       util->setJustification(a);
   else
       util->setJustification("left");
   a = element.attribute("orientation");
   if(!a.isEmpty())
       util->setOrientation(a.toInt());
   else
       util->setOrientation("horizontal");

   a = element.attribute("degrees");
   if(!a.isEmpty())
   {
    l->rotate(a.toInt(&bOk));
    if(!bOk)       log->warn("invalid 'degrees' value (non integer)");
   }
  }
}

/*public*/ void LoadXml::loadCommonAttributes(PositionableLabel* l, int defaultLevel, QDomElement element)
{
 QString a = element.attribute("forcecontroloff");
 if ( (!a.isEmpty()) && a==("true"))
  l->setControlling(false);
 else
  l->setControlling(true);

 bool bOk = true;
 bool bOk1 = false;
 // find coordinates
 int x = 0;
 int y = 0;
 x = element.attribute("x").toInt(&bOk1);
 if(!bOk1) bOk=false;
 y = element.attribute("y").toInt(&bOk1);
 if(!bOk1) bOk=false;
 if(!bOk)       log->error("failed to convert positional attribute");
 else
  l->setLocation(x,y);

 // find display level
 int level = defaultLevel;
 level = element.attribute("level").toInt(&bOk);
 if(!bOk)       log->warn("Could not parse level attribute!");
 else l->setDisplayLevel(level);

 a = element.attribute("hidden");
 if ( (!a.isEmpty()) && a==("yes"))
 {
  l->setHidden(true);
  l->setVisible(false);
 }
 a = element.attribute("positionable");
 if ( (!a.isEmpty()) && a==("true"))
  l->setPositionable(true);
 else
  l->setPositionable(false);

 a = element.attribute("showtooltip");
 if ( (!a.isEmpty()) && a==("true"))
  l->setShowTooltip(true);
 else
  l->setShowTooltip(false);

 a = element.attribute("editable");
 if ( (!a.isEmpty()) && a==("true"))
  l->setEditable(true);
 else
  l->setEditable(false);

 QDomElement elem = element.firstChildElement("toolTip");
 if (!elem.isNull())
 {
  QString tip = l->getTooltip();
  if (!tip.isEmpty())
  {
   //tip.setText(elem.text());
   l->setToolTip(elem.text());
  }
 }
}
bool LoadXml::processLights(QDomElement lights)
{
#if 0
 bool result = true;
 QDomNodeList lightList = lights.elementsByTagName("light");
 if (log->isDebugEnabled()) log->debug(tr("Found ")+QString("%1").arg(lightList.size())+" lights");
 ProxyLightManager* tm = (ProxyLightManager*)InstanceManager::lightManagerInstance();

 for (int i=0; i<lightList.size(); i++)
 {

  QString sysName = getSystemName(lightList.at(i).toElement());
  if (sysName.isNull())
  {
   log->warn("unexpected NULL in systemName "+ lightList.at(i).toElement().tagName());
   result = false;
   break;
  }

  QString userName = getUserName(lightList.at(i).toElement());

  if (log->isDebugEnabled()) log->debug("create light: ("+sysName+")("+
                                                    (userName==NULL?"<NULL>":userName)+")");
  AbstractLight* lgt = (AbstractLight*)tm->newLight(sysName, userName);
  if (lgt!=NULL)
  {
   // load common parts
   loadCommon(lgt, lightList.at(i).toElement());

   // variable intensity, transition attributes
   double value;
   value = lightList.at(i).toElement().attribute("minIntensity").toDouble();
   lgt->setMinIntensity(value);

   value = lightList.at(i).toElement().attribute("maxIntensity").toDouble();
   lgt->setMaxIntensity(value);

   value = lightList.at(i).toElement().attribute("transitionTime").toDouble();
   lgt->setTransitionTime(value);

   // provide for legacy light control - panel files written by 2.9.5 or before
   if (lightList.at(i).toElement().attribute("controlType")!=NULL)
   {
    // this is a legacy Light - create a LightControl from the input
    QString temString = lightList.at(i).toElement().attribute("controlType");
    int type = Light::NO_CONTROL;
    bool bOk;
    type = temString.toInt(&bOk);
    if(!bOk)
    {
     log->error("error when converting control type in legacy Light load support");
     type = Light::NO_CONTROL;
    }
    if (type!=Light::NO_CONTROL)
    {
     // this legacy light has a control - capture it
     LightControl* lc = new LightControl(lgt);
     lc->setControlType(type);
     if (type==Light::SENSOR_CONTROL)
     {
      lc->setControlSensorName(lightList.at(i).toElement().attribute("controlSensor") );
      lc->setControlSensorSense( lightList.at(i).toElement().attribute("sensorSense").toInt(&bOk));
      if(!bOk)
      {
       log->error("error when converting control sensor sense in legacy Light load");
      }
     }
     else if (type==Light::FAST_CLOCK_CONTROL)
     {
      int onHour = 0;
      int onMin = 0;
      int offHour = 0;
      int offMin = 0;
      bOk=true;
      bool bOk1;
      onHour = lightList.at(i).toElement().attribute("fastClockOnHour").toInt(&bOk1);
      if(!bOk1) bOk = false;
      onMin = lightList.at(i).toElement().attribute("fastClockOnMin").toInt(&bOk1);
      if(!bOk1) bOk = false;
      offHour = lightList.at(i).toElement().attribute("fastClockOffHour").toInt(&bOk1);
      if(!bOk1) bOk = false;
      offMin = lightList.at(i).toElement().attribute("fastClockOffMin").toInt(&bOk1);
      if(!bOk1) bOk = false;
      if(!bOk)
      {
       log->error("error when converting fast clock items in legacy Light load");
      }
      lc->setFastClockControlSchedule(onHour,onMin,offHour,offMin);
     }
     else if (type==Light::TURNOUT_STATUS_CONTROL)
     {
      lc->setControlTurnout(lightList.at(i).toElement().attribute("controlTurnout"));
      bool bOk;
      lc->setControlTurnoutState(lightList.at(i).toElement().attribute("turnoutState").toInt(&bOk));
      if(!bOk)
      {
       log->error("error when converting turnout state in legacy Light load");
      }
     }
     else if (type==Light::TIMED_ON_CONTROL)
     {
      lc->setControlTimedOnSensorName(lightList.at(i).toElement().attribute("timedControlSensor"));
      bool bOk;
      lc->setTimedOnDuration( lightList.at(i).toElement().attribute("duration").toInt(&bOk));
      if(!bOk)
      {
       log->error("error when converting timed sensor items in legacy Light load");
      }
     }
    lgt->addLightControl(lc);
   }
  }

  // load lightcontrol children, if any
  QDomNodeList lightControlList = lightList.at(i).toElement().elementsByTagName("lightcontrol");
  for (int n = 0; n<lightControlList.size(); n++)
  {
   bool noErrors = true;
   QDomElement elem = lightControlList.at(n).toElement();
   LightControl* lc = new LightControl(lgt);
   QString tem = elem.attribute("controlType");
   int type = Light::NO_CONTROL;
   bool bOk;
   type = tem.toInt(&bOk);
   lc->setControlType(type);
   if(!bOk)
   {
    log->error("error when converting control type while loading light "+sysName);
    noErrors = false;
   }
   if (type==Light::SENSOR_CONTROL)
   {
    lc->setControlSensorName(elem.attribute("controlSensor") );
    lc->setControlSensorSense( elem.attribute("sensorSense").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting control sensor sense while loading light "+sysName);
      noErrors = false;
    }
   }
   else if (type==Light::FAST_CLOCK_CONTROL)
   {
    int onHour = 0;
    int onMin = 0;
    int offHour = 0;
    int offMin = 0;
    bool bOk = true;
    bool bOk1;
    onHour = elem.attribute("fastClockOnHour").toInt(&bOk1);
    if(!bOk1) bOk = false;
    onMin =elem.attribute("fastClockOnMin").toInt(&bOk1);
    if(!bOk1) bOk = false;
    offHour = elem.attribute("fastClockOffHour").toInt(&bOk1);
    if(!bOk1) bOk = false;
    offMin = elem.attribute("fastClockOffMin").toInt(&bOk1);
    if(!bOk)
    {
     log->error("error when converting fast clock items while loading light "+sysName);
     noErrors = false;
    }
    else
     lc->setFastClockControlSchedule(onHour,onMin,offHour,offMin);

   }
   else if (type==Light::TURNOUT_STATUS_CONTROL)
   {
    lc->setControlTurnout(elem.attribute("controlTurnout"));
    bool bOk;
    lc->setControlTurnoutState(elem.attribute("turnoutState").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting turnout state while loading light "+sysName);
     noErrors = false;
    }
   }
   else if (type==Light::TIMED_ON_CONTROL)
   {
    lc->setControlTimedOnSensorName(elem.attribute("timedControlSensor"));
    bool bOk;
    lc->setTimedOnDuration( elem.attribute("duration").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting timed sensor items while loading light "+sysName);
     noErrors = false;
    }
   }
   else if (type==Light::TWO_SENSOR_CONTROL)
   {
    lc->setControlSensorName(elem.attribute("controlSensor") );
    lc->setControlSensor2Name(elem.attribute("controlSensor2") );
    bool bOk;
    lc->setControlSensorSense( elem.attribute("sensorSense").toInt(&bOk));
    if(!bOk)
    {
     log->error("error when converting control sensor2 sense while loading light "+sysName);
     noErrors = false;
    }
   }
   if (noErrors)
   {
    lgt->addLightControl(lc);
   }
  }

  // done, start it working
  lgt->activateLight();
 }
 else
  {
   log->error ("failed to create Light: "+sysName);
   result = false;
  }
 }
 return result;
#else
 AbstractLightManagerConfigXML* xml = new AbstractLightManagerConfigXML(this);
 xml->setDoc(doc);
 return xml->loadLights(lights);

#endif
}
void LoadXml::processPanelEditor(QDomElement e)
{
 if(e.attribute("class") ==  "jmri.jmrit.display.panelEditor.configurexml.PanelEditorXml")
 {
  PanelEditorXml* xml = new PanelEditorXml(this);
  xml->setDoc(doc);
  xml->load(e);
 }
 else if(e.attribute("class")== "jmri.jmrit.display.controlPanelEditor.configurexml.ControlPanelEditorXml")
 {
  ControlPanelEditorXml* xml = new ControlPanelEditorXml(this);
  xml->load(e);
 }
}
bool LoadXml::processTimebase(QDomElement e)
{
 SimpleTimebaseXml* xml = new SimpleTimebaseXml(this);
 xml->setDoc(doc);
 return xml->load(e);
}
bool LoadXml::processSignalHeads(QDomElement e)
{
    AbstractSignalHeadManagerXml* xml = new AbstractSignalHeadManagerXml(this);
    return xml->load(e);
}
bool LoadXml::processSignalMasts(QDomElement e)
{
    DefaultSignalMastManagerXml* xml = new DefaultSignalMastManagerXml(this);
    return xml->load(e);
}
bool LoadXml::processSignalMastLogics(QDomElement e)
{
    DefaultSignalMastLogicManagerXml* xml = new DefaultSignalMastLogicManagerXml(this);
    return xml->load(e);

}
bool LoadXml::processBlockBossLogic(QDomElement e)
{
 BlockBossLogicXml* xml = new BlockBossLogicXml(this);
 return xml->load(e);
}
bool LoadXml::processLogix(QDomElement e)
{
 DefaultLogixManagerXml* xml = new DefaultLogixManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processConditionals(QDomElement e)
{
 DefaultConditionalManagerXml* xml = new DefaultConditionalManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processWarrants(QDomElement e)
{
 WarrantManagerXml* xml = new WarrantManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processOBlocks(QDomElement e)
{
 OBlockManagerXml* xml = new OBlockManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processEntryExitPairs(QDomElement e)
{
 EntryExitPairsXml* xml = new EntryExitPairsXml(this);
 return xml->load(e);
}
bool LoadXml::processSignalGroups(QDomElement e)
{
 DefaultSignalGroupManagerXml* xml = new DefaultSignalGroupManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processSections(QDomElement e)
{
 SectionManagerXml* xml = new SectionManagerXml(this);
 return xml->load(e);
}
bool LoadXml::processPositionableCircle(QDomElement e)
{
 PositionableCircleXml* xml = new PositionableCircleXml(this);
 return xml->load(e);
}
bool LoadXml::processPositionableEllipse(QDomElement e)
{
 PositionableEllipseXml* xml = new PositionableEllipseXml(this);
 return xml->load(e);
}
bool LoadXml::processPositionableRectangle(QDomElement e)
{
 PositionableRectangleXml* xml = new PositionableRectangleXml(this);
 return xml->load(e);
}
bool LoadXml::processPositionableRoundRect(QDomElement e)
{
 PositionableRoundRectXml* xml = new PositionableRoundRectXml(this);
 return xml->load(e);
}
bool LoadXml::processAudio(QDomElement e)
{
 DefaultAudioManagerXml* xml = new DefaultAudioManagerXml(this);
 return xml->load(e);
}

XmlAdapter* LoadXml::loadXmlAdapter(QDomElement e)
{
 QString javaClass = e.attribute("class");
 QString typeName = javaClass.mid(javaClass.lastIndexOf(".")+1);
 int typeId = QMetaType::type(typeName.toLocal8Bit());
 if(typeId <= 0) return NULL;
 QObject* adapter;
#if QT_VERSION < 0x050000
 adapter = (XmlAdapter*)QMetaType::construct(typeId);
#else
 adapter = (XmlAdapter*)QMetaType::create(typeId);
#endif
 if(adapter == NULL) return NULL;
  adapter->setObjectName(typeName);
  return qobject_cast<XmlAdapter*>(adapter);
}
