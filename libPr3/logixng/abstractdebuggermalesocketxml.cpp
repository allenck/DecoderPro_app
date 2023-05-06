#include "abstractdebuggermalesocketxml.h"
#include "logixng/malesocket.h"

/**
 * Handle XML configuration for AbstractDebuggerMaleSocket objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/ class AbstractDebuggerMaleSocketXml
//    extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML
//        implements MaleSocketXml {

    AbstractDebuggerMaleSocketXml::AbstractDebuggerMaleSocketXml(QObject *parent)
        : AbstractNamedBeanManagerConfigXML{parent}
    {

    }

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/ QDomElement AbstractDebuggerMaleSocketXml::store(QObject* o) {
        //        AbstractMaleSocket maleSocket = (AbstractMaleSocket) o;

        QDomElement element = doc.createElement("AbstractDebuggerMaleSocket");
        //element.setAttribute("class", /*this.getClass().getName()*/"jmri.jmrit.logixng.tools.debugger.configurexml.AbstractDebuggerMaleSocketXml");
        element.setAttribute("class",this->getClass());
        /*
        element.addContent(doc.createElement("errorHandling").addContent(maleSocket.getErrorHandlingType().name()));
        for (SymbolTable.VariableData data : maleSocket.getLocalVariables()) {
            QDomElement elementVariable = doc.createElement("localVariable");
            elementVariable.addContent(doc.createElement("name").addContent(data._name));
            elementVariable.addContent(doc.createElement("type").addContent(data._initalValueType.name()));
            elementVariable.addContent(doc.createElement("data").addContent(data._initialValueData));
            element.addContent(elementVariable);
        }
*/
        return element;
    }

    //@Override
    /*public*/ bool AbstractDebuggerMaleSocketXml::load(QDomElement shared, QDomElement perNode) {
        return false;
    }

    //@Override
        /*public*/ bool AbstractDebuggerMaleSocketXml::load(QDomElement maleSocketElement, MaleSocket* maleSocket) {
        /*
        QDomElement errorHandlingQDomElement = maleSocketElement.getChild("errorHandling");
        if (errorHandlingQDomElement != null) {
            maleSocket.setErrorHandlingType(MaleSocket.ErrorHandlingType
                    .valueOf(errorHandlingElement.getTextTrim()));
        }

        List<Element> localVariableList = maleSocketElement.getChildren("localVariable");  // NOI18N
        log.debug("Found " + localVariableList.size() + " male sockets");  // NOI18N

        for (QDomElement e : localVariableList) {
            QDomElement elementName = e.getChild("name");

            InitialValueType type = null;
            QDomElement elementType = e.getChild("type");
            if (elementType != null) {
                type = InitialValueType.valueOf(elementType.getTextTrim());
            }

            QDomElement elementData = e.getChild("data");

            if (elementName == null) throw new IllegalArgumentException("QDomElement 'name' does not exists");
            if (type == null) throw new IllegalArgumentException("QDomElement 'type' does not exists");
            if (elementData == null) throw new IllegalArgumentException("QDomElement 'data' does not exists");

            maleSocket.addLocalVariable(elementName.getTextTrim(), type, elementData.getTextTrim());
        }
*/
        return true;
    }
