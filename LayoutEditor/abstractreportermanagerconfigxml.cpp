#include "abstractreportermanagerconfigxml.h"
#include "instancemanager.h"
#include "abstractreportermanager.h"

AbstractReporterManagerConfigXML::AbstractReporterManagerConfigXML(QObject *parent) :
    AbstractNamedBeanManagerConfigXML(parent)
{
    log = new Logger("AbstractReporterManagerConfigXML");
}
/**
 * Provides the abstract base and store functionality for
 * configuring ReporterManagers, working with
 * AbstractReporterManagers.
 * <P>
 * Typically, a subclass will just implement the load(QDomElement Reporters)
 * class, relying on implementation here to load the individual Reporters.
 * Note that these are stored explicitly, so the
 * resolution mechanism doesn't need to see *Xml classes for each
 * specific Reporter or AbstractReporter subclass at store time.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002, 2008, 2009
 * @version $Revision: 18102 $
 */
// /*public*/ abstract class AbstractReporterManagerConfigXML extends AbstractNamedBeanManagerConfigXML {

///*public*/ AbstractReporterManagerConfigXML() {
//}

/**
 * Default implementation for storing the contents of a
 * ReporterManager
 * @param o Object to store, of type ReporterManager
 * @return QDomElement containing the complete info
 */
/*public*/ QDomElement AbstractReporterManagerConfigXML::store(QObject* o) {
    QDomElement reporters = doc.createElement("reporters");
    setStoreElementClass(reporters);
    AbstractReporterManager* tm = (AbstractReporterManager*) o;
    if (tm!=NULL) {
        QStringListIterator iter(                               tm->getSystemNameList());

        // don't return an element if there are not reporters to include
        if (!iter.hasNext()) return QDomElement();

        // store the reporters
        while (iter.hasNext()) {
            QString sname = iter.next();
            if (sname=="") log->error("System name null during store");
            log->debug("system name is "+sname);
            Reporter* r = (Reporter*)tm->getBySystemName(sname);
            QDomElement elem = doc.createElement("reporter");
            elem.setAttribute("systemName", sname); // deprecated for 2.9.* series
            elem.appendChild(doc.createElement("systemName").appendChild(doc.createTextNode(sname)));
            // store common parts
            storeCommon(r, elem);

            log->debug("store Reporter "+sname);
            reporters.appendChild(elem);

        }
    }
    return reporters;
}

/**
 * Subclass provides implementation to create the correct top
 * element, including the type information.
 * Default implementation is to use the local class here.
 * @param reporters The top-level element being created
 */
/*abstract*/ /*public*/ void AbstractReporterManagerConfigXML::setStoreElementClass(QDomElement /*reporters*/) const {}

/**
 * Create a ReporterManager object of the correct class, then
 * register and fill it.
 * @param reporters Top level QDomElement to unpack.
 * @return true if successful
 */
/*abstract*/ /*public*/ bool AbstractReporterManagerConfigXML::load(QDomElement /*reporters*/) throw (Exception) {return false;}

/**
 * Utility method to load the individual Reporter objects.
 * If there's no additional info needed for a specific Reporter type,
 * invoke this with the parent of the set of Reporter elements.
 * @param reporters QDomElement containing the Reporter elements to load.
 * @return true if successful
 */
//@SuppressWarnings("unchecked")
/*public*/ bool AbstractReporterManagerConfigXML::loadReporters(QDomElement reporters) {
    bool result = true;
    QDomNodeList reporterList = reporters.elementsByTagName("reporter");
    if (log->isDebugEnabled()) log->debug("Found "+QString::number(reporterList.size())+" reporters");
    ReporterManager* tm = ((ReporterManager*)InstanceManager::getDefault("ReporterManager"));

    for (int i=0; i<reporterList.size(); i++) {

        QString sysName = getSystemName(reporterList.at(i).toElement());
        if (sysName == "") {
            log->warn("unexpected null in systemName "+reporterList.at(i).toElement().tagName()/*+" "+reporterList.at(i).getAttributes()*/);
            result = false;
            break;
        }

        QString userName = getUserName(reporterList.at(i).toElement());

        if (log->isDebugEnabled()) log->debug("create Reporter: ("+sysName+")("+(userName=="" ?"<null>":userName)+")");
        Reporter* r = tm->newReporter(sysName, userName);
        loadCommon(r, reporterList.at(i).toElement());
    }
    return result;
}

/*public*/ int AbstractReporterManagerConfigXML::loadOrder() const{
    return ((ReporterManager*)InstanceManager::getDefault("ReporterManager"))->getXMLOrder();
}
