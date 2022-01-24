#include "reportericonxml.h"
#include "reportericon.h"
#include "instancemanager.h"
#include "abstractreportermanager.h"
#include "editor.h"

ReporterIconXml::ReporterIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("ReporterIconXml");
}
/**
 * Handle configuration for display.ReporterIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004
 * @version $Revision: 17977 $
 */
//public class ReporterIconXml extends PositionableLabelXml {

//    /*public*/ ReporterIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * ReporterIcon
 * @param o Object to store, of type ReporterIcon
 * @return Element containing the complete info
 */
/*public*/ QDomElement ReporterIconXml::store(QObject* o)
{

 ReporterIcon* p = (ReporterIcon*)o;

 QDomElement element = doc.createElement("reportericon");

 // include contents
 if(p->getReporter()== NULL)
  return QDomElement();
 element.setAttribute("reporter", p->getReporter()->getSystemName());
 storeCommonAttributes((Positionable*)p, element);

 storeTextInfo((Positionable*)p, element);

 element.setAttribute("class", "jmri.jmrit.display.configurexml.ReporterIconXml");

 return element;
}


/*public*/ bool ReporterIconXml::load(QDomElement /*element*/) throw (Exception)
{
 log->error("Invalid method called");
 return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level Element to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void ReporterIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 Editor* ed = (Editor*)o;
 l = new ReporterIcon(ed);

 loadTextInfo((Positionable*)l, element);

 l->setReporter((Reporter*)((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter( element.attribute("reporter")));

 l->setSize(l->getPreferredSize().width(), l->getPreferredSize().height());
 //ed->putItem((Positionable*)l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes((Positionable*)l, Editor::REPORTERS, element);
 ed->putItem((Positionable*)l);
}

ReporterIcon* ReporterIconXml::getIcon() { return l;}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ReporterIconXml.class.getName());
//}
