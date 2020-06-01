#include "portaliconxml.h"
#include "portalicon.h"
#include "portal.h"
#include "controlpaneleditor.h"
#include "oblockmanager.h"
#include "instancemanager.h"
#include "oblock.h"

PortalIconXml::PortalIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
    log = new Logger("PortalIconXml");
}
/**
 * Handle configuration for display.PortalIcon objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 20276 $
 */
///*public*/ class PortalIconXml extends PositionableLabelXml {

//    /*public*/ PortalIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * PortalIcon
 * @param o Object to store, of type PortalIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement PortalIconXml::store(QObject* o) {

 PortalIcon* p = (PortalIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

 QDomElement element = doc.createElement("PortalIcon");
 storeCommonAttributes((Positionable*)p, element);

    // include contents
 Portal* portal = p->getPortal();
 if (portal == NULL) {
     log->info("PortalIcon has no associated Portal.");
     return QDomElement();
 }
 element.setAttribute("portalName", portal->getName());
 if (portal->getToBlock() != NULL) {
     element.setAttribute("toBlockName", portal->getToBlockName());
 }
 if (portal->getFromBlockName() != NULL) {
     element.setAttribute("fromBlockName", portal->getFromBlockName());
 }
 element.setAttribute("arrowSwitch",  (p->getArrowSwitch() ? "yes" : "no"));
 element.setAttribute("arrowHide", (p->getArrowHide() ? "yes" : "no"));

 element.setAttribute("class", "jmri.jmrit.display.controlPanelEditor.configurexml.PortalIconXml");
 return element;
}


/*public*/ bool PortalIconXml::load(QDomElement /*element*/) throw (Exception)  {
    log-> error("Invalid method called");
    return false;
}

/**
 * Create a PositionableLabel, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  an Editor as an Object
 */
/*public*/ void PortalIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
  //if (!(o instanceof ControlPanelEditor))
  if(qobject_cast<ControlPanelEditor*>(o)==NULL)
  {
      log-> error("Can't load portalIcon.  Panel editor must use ControlPanelEditor.");
      return;
  }
  ControlPanelEditor* ed = (ControlPanelEditor*) o;

  QString fromBlk;
  try {
      fromBlk=element.attribute("fromBlockName");
  } catch ( NullPointerException e) {
      log-> error("incorrect information for portalIcon; must use fromBlockName.");
      ed->loadFailed();
      return;
  }
  QString portalName;
  try {
      portalName=element.attribute("portalName");
  } catch ( NullPointerException e) {
      log-> error("incorrect information for portalIcon; must use portalName.");
      ed->loadFailed();
      return;
  }
  OBlock* block = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock(fromBlk);
  Portal* portal = block->getPortalByName(portalName);

  PortalIcon* l = new PortalIcon(ed, portal);
  ed->putItem(l);
  // load individual item's option settings after editor has set its global settings
  loadCommonAttributes(l, ControlPanelEditor::MARKERS, element);
  QString a = element.attribute("scale");
  double scale = 1.0;
  if (a != "") {
      bool ok;
          scale = a.toDouble(&ok);
      if(!ok) {
          log->error(l->getNameString() + " can't convert scale " /*+ dce*/);
      }
  }
  l->setScale(scale);

  a = element.attribute("rotate");
  int deg = 0;
  if (a != "") {
      bool ok;
          deg = a.toInt(&ok);
      if(!ok) {
          log->error(l->getNameString() + " can't convert rotate " /*+ dce*/);
      }
  }
  l->rotate(deg);

  bool value = true;
  if ((a = element.attribute("arrowSwitch")) != "" && a == ("no")) {
      value = false;
  }
  l->setArrowOrientatuon(value);
  value = false;
  if ((a = element.attribute("arrowHide")) != "" && a == ("yes")) {
      value = true;
  }
  l->setHideArrows(value);
 }
