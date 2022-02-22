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
/*protected*/ QString LayoutPanelServlet::getPanelType() {
    return "LayoutPanel";
}

//@Override
/*protected*/ QByteArray LayoutPanelServlet::getXmlPanel(QString name)
{
 log->debug(tr("Getting %1 for %2").arg(getPanelType()).arg(name));
 QDomDocument doc = QDomDocument();
 try
 {
  LayoutEditor* editor = (LayoutEditor*) getEditor(name);
  if(editor == NULL)
   throw new NullPointerException(tr("editor not found for %1").arg(name));
  QDomElement panel = doc.createElement("panel");
  doc.appendChild(panel);

  panel.setAttribute("name", name);
  panel.setAttribute("paneltype", getPanelType());
  panel.setAttribute("height", (editor->gContext->getLayoutHeight()));
  panel.setAttribute("width", (editor->gContext->getLayoutWidth()));
  panel.setAttribute("panelheight", (editor->gContext->getLayoutHeight()));
  panel.setAttribute("panelwidth", (editor->gContext->getLayoutWidth()));
  panel.setAttribute("showtooltips", (editor->showToolTip()) ? "yes" : "no");
  panel.setAttribute("controlling", (editor->allControlling()) ? "yes" : "no");
  panel.setAttribute("xscale", ((float) editor->gContext->getXScale()));
  panel.setAttribute("yscale", ((float) editor->gContext->getYScale()));
  panel.setAttribute("mainlinetrackwidth", (editor->gContext->getMainlineTrackWidth()));
  panel.setAttribute("sidetrackwidth", (editor->gContext->getSidelineTrackWidth()));
  panel.setAttribute("turnoutcircles", (editor->getTurnoutCircles()) ? "yes" : "no");
  panel.setAttribute("turnoutcirclesize", (editor->getTurnoutCircleSize()));
  panel.setAttribute("turnoutdrawunselectedleg", (editor->isTurnoutDrawUnselectedLeg()) ? "yes" : "no");
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
  panel.setAttribute("turnoutcirclethrowncolor", editor->getTurnoutCircleThrownColor());
  panel.setAttribute("turnoutfillcontrolcircles", (editor->isTurnoutFillControlCircles()) ? "yes" : "no");

  // include positionable elements
  QList<Positionable*> contents = editor->getContents();
  log->debug(tr("N positionable elements: %1").arg(contents.size()));
  foreach (Positionable* sub, contents)
  {
   if (sub != NULL)
   {
    try
    {
     QDomElement e = ConfigXmlManager::elementFromObject((QObject*)sub);
     if (e != QDomElement())
     {
      if ("signalmasticon" == (e.tagName()))
      {  //insert icon details into signalmast
          e.appendChild(getSignalMastIconsElement(e.attribute("signalmast")));
      }
      try
      {
       if(sub->getNamedBean() == NULL)
        throw new NullPointerException();
       e.setAttribute(JSON::ID, sub->getNamedBean()->getSystemName());
      }
      catch (NullPointerException* ex)
      {
       if (sub->getNamedBean() == NULL)
       {
        log->debug(tr("%1 %2 does not have an associated NamedBean").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
       }
       else
       {
        log->debug(tr("%1 %2 does not have a SystemName").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
       }
      }
      parsePortableURIs(e);
      panel.appendChild(e);
     }
    }
    catch (Exception* ex)
    {
     log->error("Error storing panel element: " + ex->getMessage(), ex);
    }
   }
  }


  // include LayoutBlocks
  LayoutBlockManager* tm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
  QStringListIterator iter = (tm->getSystemNameList());
  ProxySensorManager* sm = (ProxySensorManager*)InstanceManager::sensorManagerInstance();
  int num = 0;
  while (iter.hasNext())
  {
   QString sname = iter.next();
   if (sname == NULL)
   {
    log->error("System name NULL during LayoutBlock store");
   }
   LayoutBlock* b = (LayoutBlock*)tm->getBySystemName(sname)->self();
   if (b->getUseCount() > 0)
   {
    // save only those LayoutBlocks that are in use--skip abandoned ones
    QDomElement elem = doc.createElement("layoutblock");
    elem.setAttribute("systemname", sname);
    QString uname = b->getUserName();
    if (uname != NULL && !uname.isEmpty()) {
        elem.setAttribute("username", uname);
    }
    // get occupancy sensor from layoutblock if it is valid
    if (!b->getOccupancySensorName().isEmpty())
    {
     Sensor* s = sm->getSensor(b->getOccupancySensorName());
     if (s != NULL) {
         elem.setAttribute("occupancysensor", s->getSystemName()); //send systemname
     }
    //if layoutblock has no occupancy sensor, use one from block, if it is populated
    }
    else
    {
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
//  num = editor->xingList->size();
//  log->debug(tr("N levelxing elements: %1").arg(num));
//  if (num > 0)
//  {
//   for (int i = 0; i < num; i++)
//   {
//    QObject* sub =(QObject*) editor->xingList->at(i);
//    try
//    {
//     QDomElement e = ConfigXmlManager::elementFromObject(sub);
//     if (e != QDomElement()) {
//         panel.appendChild(e);
//     }
//    }
//    catch (Exception* e)
//    {
//     log->error("Error storing panel levelxing element: " + e->getMessage());
//    }
//   }
//  }
//  // include LayoutTurnouts
//  num = editor->turnoutList->size();
//  log->debug(tr("N layoutturnout elements: %1").arg(num));
//  if (num > 0)
//  {
//   for (int i = 0; i < num; i++)
//   {
//    QObject* sub = (QObject*)editor->turnoutList->at(i);
//    try {
//        QDomElement e = ConfigXmlManager::elementFromObject(sub);
//        if (e != QDomElement()) {
//            panel.appendChild(e);
//        }
//    } catch (Exception* e) {
//        log->error("Error storing panel layoutturnout element: " + e->getMessage());
//    }
//   }
//  }

//  // include TrackSegments
//  num = editor->layoutTrackList->size();
//  log->debug(tr("N tracksegment elements: %1").arg(num));
//  if (num > 0)
//  {
//   for (int i = 0; i < num; i++)
//   {
//    QObject* sub =(QObject*) editor->layoutTrackList->at(i);
//    try
//    {
//     QDomElement e = ConfigXmlManager::elementFromObject(sub);
//     if (e != QDomElement()) {
//         panel.appendChild(e);
//     }
//    }
//    catch (Exception* e)
//    {
//     log->error("Error storing panel tracksegment element: " + e->getMessage());
//    }
//   }
//  }
//  // include LayoutSlips
//  num = editor->slipList->size();
//  log->debug(tr("N layoutSlip elements: %1").arg(num));
//  if (num > 0)
//  {
//   for (int i = 0; i < num; i++)
//   {
//    QObject* sub = (QObject*)editor->slipList->at(i);
//    try
//    {
//     QDomElement e = ConfigXmlManager::elementFromObject(sub);
//     if (e != QDomElement())
//     {
//      panel.appendChild(e);
//     }
//    }
//    catch (Exception* e)
//    {
//     log->error("Error storing panel layoutSlip element: " + e->getMessage());
//    }
//   }
//  }
//  // include LayoutTurntables
//  num = editor->turntableList->size();
//  log->debug(tr("N turntable elements: %1").arg(num));
//  if (num > 0)
//  {
//   for (int i = 0; i < num; i++)
//   {
//    QObject* sub = (QObject*)editor->turntableList->at(i);
//    try
//    {
//     QDomElement e = ConfigXmlManager::elementFromObject(sub);
//     if (e != QDomElement())
//     {
//      panel.appendChild(e);
//     }
//    }
//    catch (Exception* e)
//    {
//     log->error("Error storing panel turntable element: " + e->getMessage());
//    }
//   }
//  }

     //write out formatted document
//        Document doc = new Document(panel);
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.TRIM));

//        return fmt.outputString(doc);
  QByteArray text = doc.toByteArray(2);

  // for debugging
  QFile file("/home/allen/xml_panel.xml");
  file.remove();
  FileUtil::appendTextToFile(new File("/home/allen/xml_panel.xml"),QString(text));

  return text;
 }
 catch (NullPointerException* ex)
 {
  log->warn("Requested Layout panel [" + name + "] does not exist.");
  return QString("ERROR Requested panel [" + name + "] does not exist.").toLatin1();
 }
}

//@Override
/*protected*/  QString LayoutPanelServlet::getJsonPanel(QString /*name*/) {
    // TODO Auto-generated method stub
    return "ERROR JSON support not implemented";
}

