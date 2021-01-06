#include "locoiconxml.h"
#include "locoicon.h"
#include "layouteditor.h"
#include "jlabel.h"

LocoIconXml::LocoIconXml(QObject* parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("LocoIconXml");
 setObjectName("LocoIconXml");
}
/**
 * Handle configuration for display.LocoIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 21062 $
 */
//public class LocoIconXml extends PositionableLabelXml {

//    public LocoIconXml() {
//    }

    /**
 * Default implementation for storing the contents of a
 * LocoIcon
 * @param o QObject* to store, of type LocoIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement LocoIconXml::store(QObject* o)
{

 LocoIcon* p = (LocoIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

  QDomElement element = doc.createElement("locoicon");
  storeCommonAttributes((Positionable*)p, element);

  // include contents
  if (p->getUnRotatedText()!=NULL) {
   element.setAttribute("text", p->getUnRotatedText());
  }
  storeTextInfo((Positionable*)p, element);
  element.setAttribute("icon", "yes");
  element.setAttribute("dockX", p->getDockX());
  element.setAttribute("dockY", p->getDockY());
  element.appendChild(storeIcon("icon", (NamedIcon*)((JLabel*)p)->getIcon()));
  RosterEntry* entry = p->getRosterEntry();
  if (entry != NULL)
   element.setAttribute("rosterentry", entry->getId());
  element.setAttribute("class", "jmri.jmrit.display.configurexml.LocoIconXml");

  return element;
}


/*public*/ bool LocoIconXml::load(QDomElement /*element*/) throw (Exception)
{
    log->error("Invalid method called");
    return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an QObject*
 */
/*public*/ void LocoIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
  LayoutEditor* ed = (LayoutEditor*) o;
  LocoIcon* l= new LocoIcon(ed);

  // create the objects
  QString textName;
//  try
//  {
  textName = element.attribute("text", "error");
//   if(textName.isEmpty()) throw new Exception();
//  }
//  catch ( Exception e)
//  {
//   log->error("failed to get loco text attribute ex= "+e.getMessage());
//  }
  if(textName.isEmpty() || textName == "error")
  {
   log->error("failed to get loco text attribute");
   textName = "error";
  }
  QString name = "error";
  NamedIcon* icon;
//  try
//  {
   name = element.attribute("icon");
//  }
//  catch (Exception e)
//  {
//   log->error("failed to get icon attribute ex= "+e.getMessage());
//  }
  if(name.isEmpty()) log->error("failed to get icon attribute");
  if (name==("yes"))
  {
   icon = loadIcon(l, "icon", element, "LocoIcon", ed);
  }
  else
  {
   icon = NamedIcon::getIconByName(name);
   if (icon==NULL)
   {
    icon = ed->loadFailed("LocoIcon", name);
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
   bool bOk;
   int x = element.attribute("dockX","0").toInt(&bOk);
   if(!bOk) throw new Exception();
   int y = element.attribute("dockY", "0").toInt(&bOk);
   if(!bOk) throw new Exception();

   l->setDockingLocation(x, y);
//           l.dock();
  }
  catch (Exception e)
  {
   log->warn("failed to get docking location= "+e.getMessage());
  }

  QString rosterId = NULL;
  try
  {
   rosterId = element.attribute("rosterentry");
   RosterEntry* entry = Roster::getDefault()->entryFromTitle(rosterId);
   l->setRosterEntry(entry);
  }
  catch (Exception e)
  {
   log->debug("no roster entry for "+rosterId+", ex= "+e.getMessage());
  }
//  ed->putLocoIcon(l, textName);
  // load individual item's option settings after editor has set its global settings
  loadCommonAttributes((Positionable*)l, LayoutEditor::MARKERS, element);
  loadTextInfo((Positionable*)l, element);
  ed->putLocoIcon(l, textName);

  l->common();		// to detect "background" color for use in Tracker, examine icon file

 }

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoIconXml.class.getName());
//}
