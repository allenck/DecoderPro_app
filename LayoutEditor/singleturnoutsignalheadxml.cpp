#include "singleturnoutsignalheadxml.h"
#include "singleturnoutsignalhead.h"
#include "instancemanager.h"
#include "abstractturnoutmanager.h"
#include "abstractsignalheadmanager.h"

SingleTurnoutSignalHeadXml::SingleTurnoutSignalHeadXml(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
 log = new Logger("SingleTurnoutSingleTurnoutSignalHeadXML");
 setObjectName("SingleTurnoutSignalHeadXml");
}
/**
 * Handle XML configuration for SingleTurnoutSignalHead objects.
 * Based Upon DoubleTurnoutSignalHeadXML by Bob Jacobsen
 * @author Kevin Dickerson: Copyright (c) 2010
 * @version $Revision: 17977 $
 */
///*public*/ class SingleTurnoutSignalHeadXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

//    /*public*/ SingleTurnoutSignalHeadXml() {}

/**
 * Default implementation for storing the contents of a
 * SingleTurnoutSignalHead
 * @param o Object to store, of type TripleTurnoutSignalHead
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement SingleTurnoutSignalHeadXml::store(QObject* o) {
    SingleTurnoutSignalHead* p = (SingleTurnoutSignalHead*)o;

    QDomElement element = doc.createElement("signalhead");
    element.setAttribute("class", "jmri.implementation.configurexml.SingleTurnoutSignalHeadXml");

    // include contents
    element.setAttribute("systemName", p->getSystemName());
    QDomElement e1;
    element.appendChild(e1=doc.createElement("systemName"));
    e1.appendChild(doc.createTextNode(p->getSystemName()));

    storeCommon(p, element);

    QDomElement el = doc.createElement("appearance");
    el.setAttribute("defines", "thrown");
    el.appendChild(doc.createTextNode(getSignalColour(p->getOnAppearance())));
    element.appendChild(el);

    el = doc.createElement("appearance");
    el.setAttribute("defines", "closed");
    el.appendChild(doc.createTextNode(getSignalColour(p->getOffAppearance())));
    element.appendChild(el);

    el = doc.createElement("turnoutname");
    el.setAttribute("defines", "aspect");
    el.appendChild(doc.createTextNode(p->getOutput()->getName()));
    element.appendChild(el);
    //element.addContent(addTurnoutQDomElement("aspect"));

    return element;
}
/*private*/ QString SingleTurnoutSignalHeadXml::getSignalColour(int mAppearance){
    switch(mAppearance){
        case SignalHead::RED:
                return "red";
        case SignalHead::FLASHRED:
                return "flashred";
        case SignalHead::YELLOW:
                return "yellow";
        case SignalHead::FLASHYELLOW:
                return "flashyellow";
        case SignalHead::GREEN:
                return "green";
        case SignalHead::FLASHGREEN:
                return "flashgreen";
        case SignalHead::LUNAR:
                return "lunar";
        case SignalHead::FLASHLUNAR:
                return "flashlunar";
        case SignalHead::DARK:
                return "dark";
        default:
                log->warn("Unexpected appearance: "+ QString::number(mAppearance));
            // go dark
                return "dark";
    }
}


/**
 * Create a SingleTurnoutSignalHead
 * @param element Top level QDomElement to unpack.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool SingleTurnoutSignalHeadXml::load(QDomElement shared, QDomElement perNode) throw (Exception){
    QDomNodeList l = shared.elementsByTagName("turnoutname");
    if (l.size() == 0) l = shared.elementsByTagName("turnout");
    NamedBeanHandle<Turnout*>* lit = loadTurnout(l.at(0).toElement());

    int off = loadAppearance(shared.elementsByTagName("appearance"), "closed");
    int on = loadAppearance(shared.elementsByTagName("appearance"), "thrown");

    // put it together
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);

    SignalHead* h;
    if (uname == NULL)
        h = (SignalHead*)new SingleTurnoutSignalHead(sys, lit, on, off);
    else
        h =(SignalHead*) new SingleTurnoutSignalHead(sys, uname, lit, on, off);

    loadCommon(h, shared);

    static_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->Register(h);
    return true;
}

/*private*/ int SingleTurnoutSignalHeadXml::loadAppearance(QDomNodeList l, QString state){
    for (int i = 0; i <l.size(); i++){
        if(l.at(i).toElement().attribute("defines")==(state))
            return getIntFromColour(l.at(i).toElement().text());
    }
    return 0x00;
}

/**
 * Needs to handle two types of element:
 *    turnoutname is new form
 *    turnout is old form
 */
NamedBeanHandle<Turnout*>* SingleTurnoutSignalHeadXml::loadTurnout(/*QObject o*/QDomElement e)
{
 //QDomElement e = (QDomElement)o;

 QString name = e.text();

 TurnoutManager* mgr = InstanceManager::turnoutManagerInstance();
 //Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
 Turnout* t = ((ProxyTurnoutManager*)mgr)->provideTurnout(name);
 NamedBeanHandle<Turnout*>* h = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
 //    return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(name, t);
 return h;
}

/*public*/ void SingleTurnoutSignalHeadXml::load(QDomElement /*element*/, QObject* /*o*/)throw (Exception){
    log->error("Invalid method called");
}

/*private*/ int SingleTurnoutSignalHeadXml::getIntFromColour(QString colour){
    QString c = colour.toLower();
    if (c==("red")) return SignalHead::RED;
    else if (c==("yellow")) return SignalHead::YELLOW;
    else if (c==("green")) return SignalHead::GREEN;
    else if (c==("lunar")) return SignalHead::LUNAR;
    else if (c==("dark")) return SignalHead::DARK;
    else if (c==("flashred")) return SignalHead::FLASHRED;
    else if (c==("flashyellow")) return SignalHead::FLASHYELLOW;
    else if (c==("flashgreen")) return SignalHead::FLASHGREEN;
    else if (c==("flashlunar")) return SignalHead::FLASHLUNAR;
    else log->warn("Unexpected appearance: "+colour);
    return SignalHead::DARK;

}
