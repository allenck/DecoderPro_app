#include "controlpanelservlet.h"
#include "loggerfactory.h"
#include "controlpaneleditor.h"
#include "positionable.h"
#include "configxmlmanager.h"
#include "namedbean.h"
#include "json.h"

ControlPanelServlet::ControlPanelServlet()
{

}
/**
 *
 * @author Randall Wood (C) 2016
 */
//@WebServlet(name = "ControlPanelServlet",
//        urlPatterns = {"/panel/ControlPanel"})
///*public*/ class ControlPanelServlet extends AbstractPanelServlet {

/*private*/ /*final*/ /*static*/ Logger* ControlPanelServlet::log = LoggerFactory::getLogger("ControlPanelServlet");

//@Override
/*protected*/  QString ControlPanelServlet::getPanelType() {
    return "ControlPanel";
}

//@Override
/*protected*/  QByteArray ControlPanelServlet::getXmlPanel(QString name)
{
 QDomDocument doc = QDomDocument();
  log->debug(tr("Getting %1 for %2").arg(getPanelType()).arg(name));
  try
  {
   ControlPanelEditor* editor = (ControlPanelEditor*) getEditor(name);
   if(editor == NULL)
    throw NullPointerException(tr("editor not found for %1").arg(name));

   QDomElement panel = doc.createElement("panel");
   doc.appendChild(panel);

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
   log->debug(tr("N elements: %1").arg(contents.size()));
   foreach (Positionable* sub, contents)
   {
    if (sub != NULL)
    {
     try
     {
      QDomElement e = ConfigXmlManager::elementFromObject(sub);
      if (e != QDomElement())
      {
       if ("signalmasticon" == (e.tagName()))
       {  //insert icon details into signalmast
           e.appendChild(getSignalMastIconsElement(e.attribute("signalmast")));
       }
       try
       {
        if(sub->getNamedBean() == NULL)
         throw NullPointerException();
           e.setAttribute( JSON::ID, sub->getNamedBean()->getSystemName());
       }
       catch (NullPointerException ex)
       {
        if (sub->getNamedBean() == NULL)
        {
            log->debug(tr("%1 %2 does not have an associated NamedBean").arg(e.tagName()).arg(e.attribute(JSON::NAME)));
        } else {
            log->debug(tr("%1 %2 does not have a SystemName").arg( e.tagName()).arg(e.attribute( JSON::NAME)));
        }
       }
       parsePortableURIs(e);
       panel.appendChild(e);
      }
     }
     catch (Exception ex)
     {
         log->error("Error storing panel element: " + ex.getMessage(), ex.getLocalizedMessage());
     }
    }
   }

//        Document doc = new Document(panel);
//        XMLOutputter out = new XMLOutputter();
//        out.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.TRIM));

//        return out.outputString(doc);
     return doc.toByteArray(2);
  }
  catch (NullPointerException ex)
  {
      log->warn("Requested ControlPanel [" + name + "] does not exist.");
      return QString("ERROR Requested panel [" + name + "] does not exist.").toLatin1();
  }
}

//@Override
/*protected*/  QString ControlPanelServlet::getJsonPanel(QString /*name*/)
{
 // TODO Auto-generated method stub
 return "ERROR JSON support not implemented";
}
