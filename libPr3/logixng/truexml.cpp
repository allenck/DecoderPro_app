#include "truexml.h"
#include "true.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class TrueXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

/*public*/  TrueXml::TrueXml(QObject* parent) : AbstractNamedBeanManagerConfigXML(parent){
}

/**
 * Default implementation for storing the contents of a SE8cSignalHead
 *
 * @param o Object to store, of type TripleTrueSignalHead
 * @return Element containing the complete info
 */
//@Override
/*public*/  QDomElement TrueXml::store(QObject* o) {
    True* p = (True*) o;

    QDomElement element = doc.createElement("True");
    element.setAttribute("class", "jmri.jmrit.logixng.expressions.configurexml.TrueXml");
    QDomElement e1;
    element.appendChild(e1 = doc.createElement("systemName")); e1.appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName()));

    storeCommon((NamedBean*)p->bself(), element);

    return element;
}

//@Override
/*public*/  bool TrueXml::load(QDomElement shared, QDomElement perNode) {
    QString sys = getSystemName(shared);
    QString uname = getUserName(shared);
    DigitalExpressionBean* h = new True(sys, uname);

    loadCommon(h, shared);

    ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(h);
    return true;
}
