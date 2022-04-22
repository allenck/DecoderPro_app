#include "defaultcsvnamedtablexml.h"
#include "defaultcsvnamedtable.h"
#include "defaultnamedtablemanager.h"
#include "instancemanager.h"

/**
 * Handle XML configuration for DefaultCsvNamedTable objects.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2004, 2008, 2010
 * @author Daniel Bergqvist Copyright (C) 2019
 */
///*public*/  class DefaultCsvNamedTableXml extends jmri.managers.configurexml.AbstractNamedBeanManagerConfigXML {

DefaultCsvNamedTableXml::DefaultCsvNamedTableXml(QObject *parent) : AbstractNamedBeanManagerConfigXML(parent)
{

}

    /**
     * Default implementation for storing the contents of a DefaultCsvNamedTable
     *
     * @param o Object to store, of type DefaultCsvNamedTable
     * @return Element containing the complete info
     */
    //@Override
    /*public*/  QDomElement DefaultCsvNamedTableXml::store(QObject* o) {
        DefaultCsvNamedTable* p = (DefaultCsvNamedTable*) o;

        QDomElement element = doc.createElement("CsvTable");
        element.setAttribute("class", "jmri.jmrit.logixng.implementation.configurexml.DefaultCsvNamedTableXml");
        QDomElement e;
        element.appendChild(e = doc.createElement("systemName"));
         e.appendChild(doc.createTextNode(p->getSystemName()));

        storeCommon(p, element);

        element.appendChild(e = doc.createElement("fileName"));
          e.appendChild(doc.createTextNode(p->getFileName()));

        return element;
    }

    //@Override
    /*public*/  bool DefaultCsvNamedTableXml::load(QDomElement shared, QDomElement perNode) {
        QString sys = getSystemName(shared);
        QString uname = getUserName(shared);
        QString fileName = shared.firstChildElement("fileName").text().trimmed();
        NamedTable* h = ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->newCSVTable(sys, uname, fileName);

        loadCommon(h, shared);

        return true;
    }
