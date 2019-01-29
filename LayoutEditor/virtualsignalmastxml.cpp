#include "virtualsignalmastxml.h"
#include "instancemanager.h"
#include "virtualsignalmast.h"
#include "signalmastmanager.h"
#include "defaultsignalmastmanager.h"

VirtualSignalMastXml::VirtualSignalMastXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("VirtualSignalMastXml");
 setObjectName("VirtualSignalMastXml");
}
/**
 * Handle XML configuration for a DefaultSignalMastManager objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2009
 * @version $Revision: 18102 $
 */
///*public*/ class VirtualSignalMastXml
//            extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

// /*public*/ VirtualSignalMastXml() {}

/**
 * Default implementation for storing the contents of a
 * DefaultSignalMastManager
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return Element containing the complete info
 */
/*public*/ QDomElement VirtualSignalMastXml::store(QObject* o)
{
    VirtualSignalMast* p = (VirtualSignalMast*)o;
    QDomElement e = doc.createElement("virtualsignalmast");
    e.setAttribute("class", "jmri.implementation.configurexml.VirtualSignalMastXml" );
    e.setAttribute("systemName", p->getSystemName());
    QDomElement e1;
    e.appendChild(e1=doc.createElement("systemName"));
    e1.appendChild(doc.createTextNode(p->getSystemName()));
    storeCommon(p, e);

    QStringList* disabledAspects = p->getDisabledAspects();
    if(disabledAspects!=NULL){
        QDomElement el = doc.createElement("disabledAspects");
        foreach(QString aspect, *disabledAspects){
            QDomElement ele = doc.createElement("disabledAspect");
            ele.appendChild(doc.createTextNode(aspect));
            el.appendChild(ele);
        }
        if(disabledAspects->size()!=0)
            e.appendChild(el);
    }
    return e;
}

/**
 * Create a DefaultSignalMastManager
 * @param element Top level Element to unpack.
 * @return true if successful
 */
/*public*/ bool VirtualSignalMastXml::load(QDomElement element) throw (Exception){
    VirtualSignalMast* m;
    QString sys = getSystemName(element);
    m = new VirtualSignalMast(sys);

    if (getUserName(element) != NULL)
        m->setUserName(getUserName(element));

    loadCommon(m, element);

    QDomElement e = element.firstChildElement("disabledAspects");
    if(!e.isNull()){
        //@SuppressWarnings("unchecked")
        QDomNodeList list = e.elementsByTagName("disabledAspect");
        for(int i=0; i< list.count(); i++)
        {
            QDomElement aspect = list.at(i).toElement();
            m->setAspectDisabled(aspect.text());
        }
    }

    static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->Register(m);

    return true;
}

/*public*/ void VirtualSignalMastXml::load(QDomElement /*element*/, QObject* /*o*/)  throw (Exception){
    log->error("Invalid method called");
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(VirtualSignalMastXml.class.getName());
//}
