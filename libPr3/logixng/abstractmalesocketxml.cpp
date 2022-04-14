#include "abstractmalesocketxml.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "abstractmalesocket.h"
#include "malesocket.h"
#include "abstractmalesocket.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class AbstractMaleSocketXml
//        extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML
//        implements MaleSocketXml {

    /*public*/  AbstractMaleSocketXml::AbstractMaleSocketXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent) {
    }

    /**
     * Default implementation for storing the contents of a ActionMany
     *
     * @param o Object to store, of type ActionMany
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement AbstractMaleSocketXml::store(QObject* o) {
        AbstractMaleSocket* maleSocket = (AbstractMaleSocket*) o;

        QDomElement element = doc.createElement("AbstractMaleSocket");                     // NOI18N
        element.setAttribute("enabled", maleSocket->isEnabled() ? "yes" : "no");  // NOI18N
        element.setAttribute("locked", maleSocket->isLocked() ? "yes" : "no");    // NOI18N
        element.setAttribute("system", maleSocket->isSystem() ? "yes" : "no");    // NOI18N
        element.setAttribute("catchAbortExecution", maleSocket->getCatchAbortExecution()? "yes" : "no");  // NOI18N
        element.setAttribute("class", this->getClassName());

        // Only store error handling type of the inner most socket
        if (!qobject_cast<MaleSocket*>(maleSocket->getObject()->bself())) {
            element.appendChild(doc.createElement("errorHandling").appendChild(doc.createTextNode(ErrorHandlingType::toString( maleSocket->getErrorHandlingType()))));  // NOI18N
        }

        for (VariableData* data : *maleSocket->getLocalVariables()) {
            QDomElement elementVariable = doc.createElement("LocalVariable");                                     // NOI18N
            elementVariable.appendChild(doc.createElement("name").appendChild(doc.createTextNode(data->_name)));                     // NOI18N
            elementVariable.appendChild(doc.createElement("type").appendChild(doc.createTextNode(InitialValueType::toString(data->_initalValueType))));   // NOI18N
            elementVariable.appendChild(doc.createElement("data").appendChild(doc.createTextNode(data->_initialValueData)));         // NOI18N
            element.appendChild(elementVariable);
        }

        return element;
    }

    //@Override
    /*public*/  bool AbstractMaleSocketXml::load(QDomElement shared, QDomElement perNode) {
        return false;
    }

    //@Override
    /*public*/  bool AbstractMaleSocketXml::load(QDomElement maleSocketElement, MaleSocket* maleSocket) {
        if (!(qobject_cast<AbstractMaleSocket*>(maleSocket->bself() ))) {
            throw new IllegalArgumentException(QString("maleSocket is not an AbstractMaleSocket: ")+maleSocket->bself()->metaObject()->className());
        }

        QString enabled = "yes";     // NOI18N
        if (maleSocketElement.attribute("enabled") != "") {  // NOI18N
            enabled = maleSocketElement.attribute("enabled");  // NOI18N
        }
        ((AbstractMaleSocket*)maleSocket->bself())->setEnabledFlag("yes" == (enabled)); // NOI18N

        QString locked = "no";       // NOI18N
        if (maleSocketElement.attribute("locked") != "") {  // NOI18N
            locked = maleSocketElement.attribute("locked");   // NOI18N
        }
        ((AbstractMaleSocket*)maleSocket->bself())->setLocked("yes" ==(locked));   // NOI18N

        QString system = "no";       // NOI18N
        if (maleSocketElement.attribute("system") != "") {  // NOI18N
            system = maleSocketElement.attribute("system");   // NOI18N
        }
        ((AbstractMaleSocket*)maleSocket->bself())->setSystem("yes" == (system));   // NOI18N

        QString catchAbortExecution = "no";      // NOI18N
        if (maleSocketElement.attribute("catchAbortExecution") != "") {  // NOI18N
            catchAbortExecution = maleSocketElement.attribute("catchAbortExecution");  // NOI18N
        }
        ((AbstractMaleSocket*)maleSocket->bself())->setCatchAbortExecution("yes" == (catchAbortExecution));  // NOI18N

        QDomElement errorHandlingElement = maleSocketElement.firstChildElement("errorHandling");     // NOI18N
        if (!errorHandlingElement.isNull()) {
            maleSocket->setErrorHandlingType(ErrorHandlingType
                    ::valueOf(errorHandlingElement.text().trimmed()));
        }

        QDomNodeList localVariableList = maleSocketElement.elementsByTagName("LocalVariable");  // NOI18N
        log->debug("Found " + QString::number(localVariableList.size()) + " male sockets");  // NOI18N

        //for (QDomElement e : localVariableList) {
        for(int i = 0; i < localVariableList.size(); i++){
         QDomElement e = localVariableList.at(i).toElement();
            QDomElement elementName = e.firstChildElement("name");   // NOI18N

            InitialValueType::TYPES type = InitialValueType::None;
            QDomElement elementType = e.firstChildElement("type");   // NOI18N
            if (!elementType.isNull()) {
                type = InitialValueType::toType(elementType.text().trimmed());
            }

            QDomElement elementData = e.firstChildElement("data");   // NOI18N

            if (elementName.isNull()) throw new IllegalArgumentException("QDomElement 'name' does not exists");  // NOI18N
            if (type == InitialValueType::None) throw new IllegalArgumentException("QDomElement 'type' does not exists");         // NOI18N
            if (elementData.isNull()) throw new IllegalArgumentException("QDomElement 'data' does not exists");  // NOI18N

            maleSocket->addLocalVariable(elementName.text().trimmed(), type, elementData.text().trimmed());
        }

        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* AbstractMaleSocketXml::log = LoggerFactory::getLogger("AbstractMaleSocketXml");
