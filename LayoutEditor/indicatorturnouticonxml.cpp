#include "indicatorturnouticonxml.h"
#include "editor.h"
#include "indicatorturnouticon.h"

IndicatorTurnoutIconXml::IndicatorTurnoutIconXml(QObject *parent) :
    PositionableLabelXml(parent)
{
 log = new Logger("indicatorturnouticonxml");
}
/**
 * Handle configuration for display.IndicatorTurnoutIconXml objects.
 *
 * @author Pete Cressman Copyright: Copyright (c) 2010
 * @version $Revision: 21338 $
 */
///*public*/ class IndicatorTurnoutIconXml extends PositionableLabelXml {

//    /*public*/ IndicatorTurnoutIconXml() {
//    }

/**
 * Default implementation for storing the contents of a
 * IndicatorTurnoutIcon
 * @param o Object to store, of type IndicatorTurnoutIcon
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement IndicatorTurnoutIconXml::store(QObject* o) {
 IndicatorTurnoutIcon* p = (IndicatorTurnoutIcon*)o;
 if (!p->isActive()) return QDomElement();  // if flagged as inactive, don't store

 QDomElement element = doc.createElement("indicatorturnouticon");
 storeCommonAttributes((Positionable*)p, element);

 NamedBeanHandle<Turnout*>* t = p->getNamedTurnout();
 if (t!=NULL)
 {
  element.appendChild(storeNamedBean("turnout", t));
 }
 NamedBeanHandle<OBlock*>* b = p->getNamedOccBlock();
 if (b!=NULL)
 {
  element.appendChild(storeNamedBean("occupancyblock", b));
 }
 NamedBeanHandle<Sensor*>* s = p->getNamedOccSensor();
 if (b==NULL && s!=NULL)
 {	// only write sensor if no OBlock
  element.appendChild(storeNamedBean("occupancysensor", s));
 }

 QDomElement elem = doc.createElement("showTrainName");
 QString show = "no";
 if (p->showTrain()) { show = "yes"; }
 elem.appendChild(doc.createTextNode(show));
 element.appendChild(elem);

 QMap<QString, QHash<int, NamedIcon*>*>* iconMaps = p->getIconMaps();
 QMapIterator<QString, QHash<int, NamedIcon*>*> it( *iconMaps);
 QDomElement el = doc.createElement("iconmaps");
 QString family = p->getFamily();
 if (family!=NULL)
 {
  el.setAttribute("family", family);
 }
 while (it.hasNext())
 {
        //QHash<QString, QHash<int, NamedIcon*>*> ent = it.next();
  it.next();
  elem = doc.createElement(it.key());
  QHashIterator<int, NamedIcon*> iter(*it.value());
  while (iter.hasNext())
  {
   //QHash<int, NamedIcon*> entry = iter.next();
   iter.next();
   elem.appendChild(storeIcon(p->getStateName(iter.key()), iter.value()));
  }
  el.appendChild(elem);
 }
 element.appendChild(el);

 elem = doc.createElement("paths");
 QStringList paths = p->getPaths();
 if (!paths.isEmpty())
 {
  for (int i=0; i<paths.size(); i++)
  {
   QDomElement e = doc.createElement("path");
   e.appendChild(doc.createTextNode(paths.at(i)));
   elem.appendChild(e);

  }
  element.appendChild(elem);
 }

 element.setAttribute("class", "jmri.jmrit.display.configurexml.IndicatorTurnoutIconXml");

 return element;
}
template <class T>
QDomElement IndicatorTurnoutIconXml::storeNamedBean(QString elemName, NamedBeanHandle<T>* nb) {
    QDomElement elem = doc.createElement(elemName);
    elem.appendChild(doc.createTextNode(nb->getName()));
    return elem;
}

/*public*/ bool IndicatorTurnoutIconXml::load(QDomElement element) throw (Exception) {
    log->error("Invalid method called");
    return false;
}

/**
 * Create a IndicatorTurnoutIcon, then add to a target JLayeredPane
 * @param element Top level QDomElement to unpack.
 * @param o  Editor as an Object
 */
/*public*/ void IndicatorTurnoutIconXml::load(QDomElement element, QObject* o) throw (Exception)
{
 // create the objects
 Editor* p = (Editor*)o;

 l = new IndicatorTurnoutIcon(p);
 QDomElement name = element.firstChildElement("turnout");

 if (name.isNull())
 {
  log->error("incorrect information for turnout; must use turnout name");
 }
 else
 {
  l->setTurnout(name.text());
 }
 QDomElement elem = element.firstChildElement("iconmaps");
 if (!elem.isNull())
 {
  //@SuppressWarnings("unchecked")
  QDomNodeList maps = elem.childNodes();
  if (maps.size()>0)
  {
   for (int i=0; i<maps.size(); i++)
   {
    QString status = maps.at(i).toElement().tagName();
    //@SuppressWarnings("unchecked")
    QDomNodeList states = maps.at(i).childNodes();
    for (int k=0; k<states.size(); k++)
    {
     QString msg = "IndicatorTurnout \""+l->getNameString()+"\" icon \""+states.at(k).toElement().tagName()+"\" ";
     NamedIcon* icon = loadIcon(l, states.at(k).toElement().tagName(), maps.at(i).toElement(),
                                              msg, p);
     if (icon!=NULL)
     {
      ((PositionableLabel*)l)->setIcon(icon);
      l->setIcon(status, states.at(k).toElement().tagName(), icon);
     }
     else
     {
      log->info(msg+" removed for url= "+name.tagName());
      return;
     }
    }
   }
  }
  QString attr = elem.attribute("family");
  if (attr!=NULL)
  {
   l->setFamily(attr);
  }
 }

 name = element.firstChildElement("occupancyblock");
 if (!name.isNull())
 {
  l->setOccBlock(name.text());
 }
 name = element.firstChildElement("occupancysensor");
 if (!name.isNull())
 {
  l->setOccSensor(name.text());
 }
/*        name = element.getChild("errorsensor");
    if (name!=NULL) {
        l.setErrSensor(name.getText());
    }  */

 l->setShowTrain(false);
 name = element.firstChildElement("showTrainName");
 if (!name.isNull())
 {
  if ("yes"==(name.text())) l->setShowTrain(true);
 }

 elem = element.firstChildElement("paths");
 if (!elem.isNull())
 {
  QStringList paths =  QStringList();
  //@SuppressWarnings("unchecked")
  QDomNodeList pth = elem.childNodes();
  for (int i=0; i<pth.size(); i++)
  {
   paths.append(pth.at(i).toElement().text());
  }
  l->setPaths(paths);
 }

 l->updateSize();
 l->setVisible(true);
 //p->putItem(l);
 // load individual item's option settings after editor has set its global settings
 loadCommonAttributes(l, Editor::TURNOUTS, element);
 QPointF pt = ((Positionable*)l)->getLocation();
// if(pt.x() == 0 && pt.y()==0)
// {

//  l->setLocation(p->dLoc.x(), p->dLoc.y());
//  l->setDisplayLevel(Editor::TURNOUTS);
// }
 p->putItem(l);
}
IndicatorTurnoutIcon* IndicatorTurnoutIconXml::getIcon() { return l;}
