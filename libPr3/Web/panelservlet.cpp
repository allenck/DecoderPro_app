#include "panelservlet.h"
#include "loggerfactory.h"
#include "paneleditor.h"
#include "positionable.h"
#include "configxmlmanager.h"
#include "json.h"
#include "namedbean.h"

PanelServlet::PanelServlet() : AbstractPanelServlet()
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
//@WebServlet(name = "PanelServlet",
//        urlPatterns = {
//            "/panel",
//            "/panel/Panel",
//            "/web/showPanel.html" // redirect to /panel/ since ~ 19 Jan 2014
//        })
///*public*/ class PanelServlet extends AbstractPanelServlet {

/*private*/ /*final*/ /*static*/ Logger* PanelServlet::log = LoggerFactory::getLogger("PanelServlet");

//@Override
/*protected*/  QString PanelServlet::getPanelType() {
    return "Panel"; // NOI18N
}

//@Override
/*protected*/  QByteArray PanelServlet::getXmlPanel(QString name)
{
 log->debug(tr("Getting %1 for %2").arg(getPanelType()).arg(name));
 QDomDocument doc = QDomDocument();
 try
 {
  PanelEditor* editor = (PanelEditor*) getEditor(name);
  if(editor == NULL)
   throw NullPointerException(tr("No Editor %1 found").arg(name));

  QDomElement panel = doc.createElement("panel");

  JFrame* frame = editor->getTargetFrame();

  panel.setAttribute("name", name);
  panel.setAttribute("height", (frame->getContentPane()->height()));
  panel.setAttribute("width", (frame->getContentPane()->width()));
  panel.setAttribute("panelheight", (editor->getTargetPanel()->height()));
  panel.setAttribute("panelwidth", (editor->getTargetPanel()->width()));

  panel.setAttribute("showtooltips", (editor->showTooltip()) ? "yes" : "no");
  panel.setAttribute("controlling", (editor->allControlling()) ? "yes" : "no");
  if (editor->getBackgroundColor() != QColor())
  {
   QDomElement color = doc.createElement("backgroundColor");
   color.setAttribute("red", (editor->getBackgroundColor().red()));
   color.setAttribute("green", (editor->getBackgroundColor().green()));
   color.setAttribute("blue", (editor->getBackgroundColor().blue()));
   panel.appendChild(color);
  }

  // include contents
  QList<Positionable*> contents = editor->getContents();
  log->debug(tr("Panel has %1 elements").arg(contents.size()));
  foreach (Positionable* sub, contents)
  {
   if (sub != NULL)
   {
    try
    {
     QDomElement e = ConfigXmlManager::elementFromObject(sub);
     if (!e.isNull())
     {
      if ("signalmasticon" == (e.tagName()))
      {  //insert icon details into signalmast
          e.appendChild(getSignalMastIconsElement(e.attribute("signalmast")));
      }
      try
      {
       NamedBean* namedBean = sub->getNamedBean();
       if(namedBean == NULL)
        throw NullPointerException();
       e.setAttribute(JSON::ID, sub->getNamedBean()->getSystemName());
      } catch (NullPointerException ex)
      {
       if (sub->getNamedBean() == NULL)
       {
        log->debug(tr("%1 %2 does not have an associated NamedBean").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
       } else
       {
        log->debug(tr("%1 %2 does not have a SystemName").arg( e.tagName()).arg(e.attribute(JSON::NAME)));
       }
      }
      parsePortableURIs(e);
      panel.appendChild(e);
     }
    }
    catch (Exception ex)
    {
     log->error(tr("Error storing panel element: %1").arg(ex.getMessage()), ex.getMessage());
    }
   }
  }

  //QDomDocument doc =  QDomDocument(/*panel*/);
//        XMLOutputter out = new XMLOutputter();
//        out.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.TRIM));

 // return out.outputString(doc);
  return doc.toByteArray();
 }
 catch (NullPointerException ex)
 {
  log->warn("Requested Panel [" + name + "] does not exist.");
  return QString("ERROR Requested panel [" + name + "] does not exist.").toLatin1();
 }
}

//@Override
/*protected*/  QString PanelServlet::getJsonPanel(QString name)
{
 log->debug(tr("Getting %1 for %2").arg(getPanelType()).arg(name));
 try
 {
  PanelEditor* editor = (PanelEditor*) getEditor(name);
  if(editor == NULL)
   throw NullPointerException(tr("editor not found for %1").arg(name));

  QJsonObject root = QJsonObject(); //this.mapper.createObjectNode();
  QJsonObject panel = QJsonObject();//root.putObject("panel");

  JFrame* frame = editor->getTargetFrame();

  panel.insert("name", name);
  panel.insert("height", frame->getContentPane()->height());
  panel.insert("width", frame->getContentPane()->width());
  panel.insert("panelheight", frame->getContentPane()->height());
  panel.insert("panelwidth", frame->getContentPane()->width());

  panel.insert("showtooltips", editor->showTooltip());
  panel.insert("controlling", editor->allControlling());
  if (editor->getBackgroundColor() != QColor())
  {
   QJsonObject color = QJsonObject(); //panel.putObject("backgroundColor");
   color.insert("red", editor->getBackgroundColor().red());
   color.insert("green", editor->getBackgroundColor().green());
   color.insert("blue", editor->getBackgroundColor().blue());
   panel.insert("backgroundColor", color);
  }

  // include contents
  log->debug(tr("N elements: %1").arg(editor->getContents().size()));
  foreach (Positionable* sub, editor->getContents())
  {
    try {
        // TODO: get all panel contents as JSON
        // I tried using JavaBean Introspection to simply build the contents using Jackson Databindings,
        // but when a panel element has a reference to the panel or to itself as a property, this leads
        // to infinite recursion
    } catch (Exception ex) {
        log->error("Error storing panel element: " + ex.getMessage(), ex.getMessage());
    }
  }
  root.insert("panel", panel);

  //return this.mapper.writeValueAsString(root);
  qDebug() << QJsonDocument(root).toJson();
  return QString(QJsonDocument(root).toJson());
 }
 catch (NullPointerException ex)
 {
  log->warn("Requested Panel [" + name + "] does not exist.");
  return "ERROR Requested panel [" + name + "] does not exist.";
 }
//    catch (JsonGenerationException e) {
//        log->error("Error generating JSON", e);
//        return "ERROR " + e.getLocalizedMessage();
//    } catch (JsonMappingException e) {
//        log->error("Error mapping JSON", e);
//        return "ERROR " + e.getLocalizedMessage();
//    }
 catch (IOException e) {
     log->error("IOException", e.getMessage());
     return "ERROR " + e.getLocalizedMessage();
 }
}
