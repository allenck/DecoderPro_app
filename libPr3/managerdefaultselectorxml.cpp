#include "managerdefaultselectorxml.h"
#include "managerdefaultselector.h"
#include <QMetaType>
#include "instancemanager.h"

ManagerDefaultSelectorXml::ManagerDefaultSelectorXml(QObject *parent) :
    AbstractXmlAdapter(parent)
{
}
/**
 * Handle XML persistence of ManagerDefaultSelector
 * <P>
 * This class is named as being the persistent form of the
 * ManagerDefaultSelector class, but there's no object of that
 * form created or used.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2010
 * @version $Revision: 28186 $
 * @since 2.9.7
 */
///*public*/ class ManagerDefaultSelectorXml extends AbstractXmlAdapter {

//    /*public*/ ManagerDefaultSelectorXml() {
//    }

/**
 * Default implementation for storing the static contents of a
 * ManagerDefaultSelector
 * @param o Object to store, of type ManagerDefaultSelector
 * @return Element containing the complete info
 */
/*public*/ QDomElement ManagerDefaultSelectorXml::store(QObject* o) throw (Exception)
{
 QDomElement e = doc.createElement("managerdefaults");
 e.setAttribute("class", /*getClass().getName()*/"jmri.managers.configurexml.ManagerDefaultSelectorXml");
 foreach (QString c, ((ManagerDefaultSelector*)InstanceManager::getDefault("ManagerDefaultSelector:"))->defaults.keys())
 {
  QString n = ((ManagerDefaultSelector*)InstanceManager::getDefault("ManagerDefaultSelector:"))->defaults.value(c);
  QDomElement p = doc.createElement("setting");
  QDomElement key = doc.createElement("key");
  key.appendChild(doc.createTextNode(c));
  QDomElement value = doc.createElement("value");
  value.appendChild(doc.createTextNode(n));
  p.appendChild(key);
  p.appendChild(value);
  e.appendChild(p);
 }
 return e;
}

/*public*/ bool ManagerDefaultSelectorXml::load(QDomElement e) throw (Exception)
{
 QDomNodeList list = e.elementsByTagName("setting");

 //for (Element s : list)
 for(int i=0; i < list.size(); i++)
 {
  QDomElement s = list.at(0).toElement();
  QString name = s.firstChildElement("value").text();
  QString className = s.firstChildElement("key").text();
  QString c = "";
//        try {
//            c = Class.forName(className);
//        } catch (java.lang.ClassNotFoundException ex) {
//            continue;
//        } catch (java.lang.NoClassDefFoundError ex) {
//            continue;
//        }
    int typeId = QMetaType::type(className.toLocal8Bit());
    if(typeId > 0)
     ((ManagerDefaultSelector*)InstanceManager::getDefault("ManagerDefaultSelector:"))->setDefault(c,name);

    }
    // put into effect
    ((ManagerDefaultSelector*)InstanceManager::getDefault("ManagerDefaultSelector:"))->configure();
    InstanceManager::configureManagerInstance()->registerPref((ManagerDefaultSelector*)InstanceManager::getDefault("ManagerDefaultSelector:"));
    return true;
}

/**
 * Doesn't need to do anything, shouldn't get invoked
 * @param element Top level Element to unpack.
 * @param o  PanelEditor as an Object
 */
/*public*/ void ManagerDefaultSelectorXml::load(QDomElement /*element*/, QObject* o) throw (Exception)
{
}
