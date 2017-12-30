#include "layoutpanelservlet.h"
#include "loggerfactory.h"
#include "layouteditor.h"
#include "configxmlmanager.h"
#include "namedbean.h"
#include "json.h"
#include "layoutblockmanager.h"
#include <QColor>
#include "colorutil.h"

LayoutPanelServlet::LayoutPanelServlet()
{

}
/**
 * Return xml (for specified LayoutPanel) suitable for use by external clients
 *
 * @author mstevetodd -- based on PanelServlet.java by rhwood
 */
//@WebServlet(name = "LayoutPanelServlet",
//        urlPatterns = {"/panel/Layout"})
///*public*/ class LayoutPanelServlet extends AbstractPanelServlet {

/*private*/ /*final*/ /*static*/ Logger* LayoutPanelServlet::log = LoggerFactory::getLogger("LayoutPanelServlet");

//@Override
/*protected*/  QString LayoutPanelServlet::getPanelType() {
    return "LayoutPanel";
}

//@Override
/*protected*/  QString LayoutPanelServlet::getXmlPanel(QString name)
{
 log->debug(tr("Getting %1 for %2").arg(getPanelType()).arg(name));
 QDomDocument doc = QDomDocument();
 try
 {
//  if(name == "panel")
//   name = "My Layout";
  LayoutEditor* editor = (LayoutEditor*) getEditor(name);
  if(editor == NULL)
   throw NullPointerException(tr("editor not found for %1").arg(name));
  QDomElement panel = doc.createElement("panel");

  panel.setAttribute("name", name);
  panel.setAttribute("paneltype", getPanelType());
  panel.setAttribute("height", (editor->getLayoutHeight()));
  panel.setAttribute("width", (editor->getLayoutWidth()));
  panel.setAttribute("panelheight", (editor->getLayoutHeight()));
  panel.setAttribute("panelwidth", (editor->getLayoutWidth()));
  panel.setAttribute("showtooltips", (editor->showTooltip()) ? "yes" : "no");
  panel.setAttribute("controlling", (editor->allControlling()) ? "yes" : "no");
  panel.setAttribute("xscale", ((float) editor->getXScale()));
  panel.setAttribute("yscale", ((float) editor->getYScale()));
  panel.setAttribute("mainlinetrackwidth", (editor->getMainlineTrackWidth()));
  panel.setAttribute("sidetrackwidth", (editor->getSideTrackWidth()));
  panel.setAttribute("turnoutcircles", (editor->getTurnoutCircles()) ? "yes" : "no");
  panel.setAttribute("turnoutcirclesize", (editor->getTurnoutCircleSize()));
  panel.setAttribute("turnoutdrawunselectedleg", (editor->getTurnoutDrawUnselectedLeg()) ? "yes" : "no");
  if (editor->getBackgroundColor() == QColor())
  {
   panel.setAttribute("backgroundcolor", ColorUtil::colorToString(Qt::lightGray));
  }
  else
  {
   panel.setAttribute("backgroundcolor", ColorUtil::colorToString(editor->getBackgroundColor()));
  }
  panel.setAttribute("defaulttrackcolor", editor->getDefaultTrackColor());
  panel.setAttribute("defaultoccupiedtrackcolor", editor->getDefaultOccupiedTrackColor());
  panel.setAttribute("defaultalternativetrackcolor", editor->getDefaultAlternativeTrackColor());
  panel.setAttribute("defaulttextcolor", editor->getDefaultTextColor());
  panel.setAttribute("turnoutcirclecolor", editor->getTurnoutCircleColor());

  // include positionable elements
  QList<Positionable*> contents = editor->getContents();
  log->debug(tr("N positionable elements: %1").arg(contents.size()));
  foreach (Positionable* sub, contents)
  {
   if (sub != NULL)
   {
    try
    {
     QDomElement e = ConfigXmlManager::elementFromObject(sub);
     if (e != QDomElement())
     {
      if ("signalmasticon" == (e.tagName())) {  //insert icon details into signalmast
          e.appendChild(getSignalMastIconsElement(e.attribute("signalmast")));
      }
      try
      {
       if(sub->getNamedBean() == NULL)
        throw NullPointerException();
          e.setAttribute(JSON::ID, sub->getNamedBean()->getSystemName());
      }
      catch (NullPointerException ex)
      {
       if (sub->getNamedBean() == NULL)
       {
           log->debug(tr("%1 %2 does not have an associated NamedBean").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
       } else {
           log->debug(tr("%1 %2 does not have a SystemName").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
       }
      }
      parsePortableURIs(e);
      panel.appendChild(e);
     }
    } catch (Exception ex) {
        log->error("Error storing panel element: " + ex.getMessage(), ex.getLocalizedMessage());
    }
   }
  }

  // include PositionablePoints
  int num = editor->pointList->size();
  log->debug(tr("N positionablepoint elements: %1").arg(num));
  if (num > 0)
  {
   for (int i = 0; i < num; i++)
   {
    QObject* sub = editor->pointList->at(i);
    try
    {
     QDomElement e = ConfigXmlManager::elementFromObject(sub);
     if (e != QDomElement())
     {
         panel.appendChild(e);
     }
    } catch (Exception e)
    {
     log->error("Error storing panel positionalpoint element: " + e.getMessage());
    }
   }
  }

  // include LayoutBlocks
  LayoutBlockManager* tm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
  QStringListIterator iter = (tm->getSystemNameList());
  SensorManager* sm = InstanceManager::sensorManagerInstance();
  num = 0;
  while (iter.hasNext()) {
      QString sname = iter.next();
      if (sname == NULL) {
          log->error("System name NULL during LayoutBlock store");
      }
      LayoutBlock* b = tm->getBySystemName(sname);
      if (b->getUseCount() > 0) {
          // save only those LayoutBlocks that are in use--skip abandoned ones
          QDomElement elem = doc.createElement("layoutblock");
          elem.setAttribute("systemname", sname);
          QString uname = b->getUserName();
          if (uname != NULL && !uname.isEmpty()) {
              elem.setAttribute("username", uname);
          }
          // get occupancy sensor from layoutblock if it is valid
          if (!b->getOccupancySensorName().isEmpty()) {
              Sensor* s = sm->getSensor(b->getOccupancySensorName());
              if (s != NULL) {
                  elem.setAttribute("occupancysensor", s->getSystemName()); //send systemname
              }
          //if layoutblock has no occupancy sensor, use one from block, if it is populated
          } else {
              Sensor* s = b->getBlock()->getSensor();
              if (s != NULL) {
                  elem.setAttribute("occupancysensor", s->getSystemName()); //send systemname
              }
          }

          elem.setAttribute("occupiedsense", (b->getOccupiedSense()));
          elem.setAttribute("trackcolor", ColorUtil::colorToString(b->getBlockTrackColor()));
          elem.setAttribute("occupiedcolor", ColorUtil::colorToString(b->getBlockOccupiedColor()));
          elem.setAttribute("extracolor", ColorUtil::colorToString(b->getBlockExtraColor()));
          if (!b->getMemoryName().isEmpty()) {
              elem.setAttribute("memory", b->getMemoryName());
          }
          if (!b->useDefaultMetric())
          {
           QDomElement e1;
              elem.appendChild(e1=doc.createElement("metric"));
                               e1.appendChild(doc.createTextNode(QString::number(b->getBlockMetric())));

          }
          //add to the panel xml
          panel.appendChild(elem);
          num++;
      }
  }
  log->debug(tr("N layoutblock elements: %1").arg(num));

  // include LevelXings
  num = editor->xingList->size();
  log->debug(tr("N levelxing elements: %1").arg(num));
  if (num > 0) {
      for (int i = 0; i < num; i++) {
          QObject* sub =(QObject*) editor->xingList->at(i);
          try {
              QDomElement e = ConfigXmlManager::elementFromObject(sub);
              if (e != QDomElement()) {
                  panel.appendChild(e);
              }
          } catch (Exception e) {
              log->error("Error storing panel levelxing element: " + e.getMessage());
          }
      }
  }
  // include LayoutTurnouts
  num = editor->turnoutList->size();
  log->debug(tr("N layoutturnout elements: %1").arg(num));
  if (num > 0) {
      for (int i = 0; i < num; i++) {
          QObject* sub = (QObject*)editor->turnoutList->at(i);
          try {
              QDomElement e = ConfigXmlManager::elementFromObject(sub);
              if (e != QDomElement()) {
                  panel.appendChild(e);
              }
          } catch (Exception e) {
              log->error("Error storing panel layoutturnout element: " + e.getMessage());
          }
      }
  }

  // include TrackSegments
  num = editor->trackList->size();
  log->debug(tr("N tracksegment elements: %1").arg(num));
  if (num > 0) {
      for (int i = 0; i < num; i++) {
          QObject* sub =(QObject*) editor->trackList->at(i);
          try {
              QDomElement e = ConfigXmlManager::elementFromObject(sub);
              if (e != QDomElement()) {
                  panel.appendChild(e);
              }
          } catch (Exception e) {
              log->error("Error storing panel tracksegment element: " + e.getMessage());
          }
      }
  }
  // include LayoutSlips
  num = editor->slipList->size();
  log->debug(tr("N layoutSlip elements: %1").arg(num));
  if (num > 0) {
      for (int i = 0; i < num; i++) {
          QObject* sub = (QObject*)editor->slipList->at(i);
          try {
              QDomElement e = ConfigXmlManager::elementFromObject(sub);
              if (e != QDomElement()) {
                  panel.appendChild(e);
              }
          } catch (Exception e) {
              log->error("Error storing panel layoutSlip element: " + e.getMessage());
          }
      }
  }
  // include LayoutTurntables
  num = editor->turntableList->size();
  log->debug(tr("N turntable elements: %1").arg(num));
  if (num > 0) {
      for (int i = 0; i < num; i++) {
          QObject* sub = (QObject*)editor->turntableList->at(i);
          try {
              QDomElement e = ConfigXmlManager::elementFromObject(sub);
              if (e != QDomElement()) {
                  panel.appendChild(e);
              }
          } catch (Exception e) {
              log->error("Error storing panel turntable element: " + e.getMessage());
          }
      }
  }

     //write out formatted document
//        Document doc = new Document(panel);
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.TRIM));

//        return fmt.outputString(doc);
     return doc.toString();
 } catch (NullPointerException ex) {
     log->warn("Requested Layout panel [" + name + "] does not exist.");
     return "ERROR Requested panel [" + name + "] does not exist.";
 }
}

//@Override
/*protected*/  QString LayoutPanelServlet::getJsonPanel(QString /*name*/) {
    // TODO Auto-generated method stub
    return "ERROR JSON support not implemented";
}

