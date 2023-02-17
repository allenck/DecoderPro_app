#include "logdataxml.h"
#include "logdata.h"
#include "../defaultdigitalactionmanager.h"
#include "../parserexception.h"
#include "instancemanager.h"
#include "loggerfactory.h"

/**
 * Handle XML configuration for ActionLightXml objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class LogDataXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {
namespace Actions
{
    /*public*/  LogDataXml::LogDataXml(QObject* parent) {
    }

    /**
     * Default implementation for storing the contents of a SE8cSignalHead
     *
     * @param o Object to store, of type TripleLightSignalHead
     * @return QDomElement containing the complete info
     */
    //@Override
    /*public*/  QDomElement LogDataXml::store(QObject* o) {
        LogData* p = (LogData*) o;

        QDomElement element = doc.createElement("LogData");
        element.setAttribute("class", "jmri.jmrit.logixng.actions.LogDataXml");
        element.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(p->AbstractNamedBean::getSystemName())));

        storeCommon(p, element);

        element.appendChild(doc.createElement("logToLog").appendChild(doc.createTextNode(p->getLogToLog() ? "yes" : "no")));
#ifdef ENABLE_SCRIPTING
        element.appendChild(doc.createElement("logToScriptOutput").appendChild(doc.createTextNode(p->getLogToScriptOutput() ? "yes" : "no")));
#endif
        element.appendChild(doc.createElement("formatType").appendChild(doc.createTextNode(LogData::FormatType::toString(p->getFormatType()))));
        element.appendChild(doc.createElement("format").appendChild(doc.createTextNode(p->getFormat())));

        QDomElement parameters = doc.createElement("DataList");
        for (LogData::Data data : *p->getDataList()) {
            QDomElement elementParameter = doc.createElement("Data");
            elementParameter.appendChild(doc.createElement("type").appendChild(doc.createTextNode(LogData::DataType::toString(data.getDataType()))));
            elementParameter.appendChild(doc.createElement("data").appendChild(doc.createTextNode(data.getData())));
            parameters.appendChild(elementParameter);
        }
        element.appendChild(parameters);

        return element;
    }

    //@Override
    /*public*/  bool LogDataXml::load(QDomElement shared, QDomElement /*perNode*/) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        LogData* h = new LogData(sys, uname);

        loadCommon(h, shared);

        QDomElement elem = shared.firstChildElement("logToLog");  // NOI18N
        h->setLogToLog((!elem.isNull()) ? elem.text().trimmed() == ("yes") : false);  // NOI18N

        elem = shared.firstChildElement("logToScriptOutput");  // NOI18N
#ifdef ENABLE_SCRIPTING
        h->setLogToScriptOutput((!elem.isNull()) ? elem.text().trimmed() == ("yes") : false);  // NOI18N
#endif
        elem = shared.firstChildElement("formatType");  // NOI18N
        h->setFormatType((!elem.isNull()) ? LogData::FormatType::fromString(elem.text().trimmed()) : LogData::FormatType::OnlyText);

        elem = shared.firstChildElement("format");  // NOI18N
        h->setFormat((!elem.isNull()) ? elem.text() : "");

        QDomNodeList dataList = shared.firstChildElement("DataList").childNodes();  // NOI18N
        log->debug("Found " + QString::number(dataList.size()) + " dataList");  // NOI18N

        for(int i =0; i < dataList.count(); i++) {
         QDomElement e = dataList.at(i).toElement();
            LogData::DataType::DATATYPE type = LogData::DataType::LocalVariable;
            QDomElement elementType = e.firstChildElement("type");
            if (!elementType.isNull()) {
                type = LogData::DataType::fromString(elementType.text().trimmed());
            }

            QDomElement elementName = e.firstChildElement("data");

            if (elementName .isNull()) throw new IllegalArgumentException("QDomElement 'name' does not exists");

            try {
                h->getDataList()->append(LogData::Data(type, elementName.text().trimmed()));
            } catch (ParserException* ex) {
                log->warn(ex->getMessage());
            }
        }

        ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(h);
        return true;
    }

    /*private*/ /*final*/ /*static*/ Logger* LogDataXml::log = LoggerFactory::getLogger("LogDataXml");
}
