#include "defaultmaledigitalexpressionsocketxml.h"
#include "defaultmaledigitalexpressionsocket.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
//public class DefaultMaleDigitalExpressionSocketXml extends AbstractMaleSocketXml {
DefaultMaleDigitalExpressionSocketXml::DefaultMaleDigitalExpressionSocketXml(QObject *parent) : AbstractMaleSocketXml(parent)
{

}

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return Element containing the complete info
     */
    //@Override
    /*public*/ QDomElement DefaultMaleDigitalExpressionSocketXml::store(QObject* o) {
        QDomElement element = AbstractMaleSocketXml::store(o);

        DefaultMaleDigitalExpressionSocket* maleSocket = (DefaultMaleDigitalExpressionSocket*) o;

        element.setAttribute("DefaultMaleDigitalExpressionSocketListen", maleSocket->getListen()? "yes" : "no");  // NOI18N

        return element;
    }

    //@Override
    /*public*/ bool DefaultMaleDigitalExpressionSocketXml::load(QDomElement maleSocketElement, MaleSocket* maleSocket) {
        if (!(qobject_cast<DefaultMaleDigitalExpressionSocket*>(maleSocket->bself() ))) {
            throw new IllegalArgumentException(QString("maleSocket is not an AbstractMaleSocket: ")+maleSocket->bself()->metaObject()->className());
        }

        QString listen = "yes";
        QString attribute = maleSocketElement.attribute("DefaultMaleDigitalExpressionSocketListen");
        if (attribute != "") {  // NOI18N
            listen = attribute;  // NOI18N
        }
        ((DefaultMaleDigitalExpressionSocket*)maleSocket->bself())->setListen("yes" == (listen));

        return AbstractMaleSocketXml::load(maleSocketElement, maleSocket);
    }

  /*public*/ QString DefaultMaleDigitalExpressionSocketXml::getClassName(){
   return "jmri.jmrit.logixng.implementation.configurexml.DefaultMaleDigitalExpressionSocketXml";
  }
