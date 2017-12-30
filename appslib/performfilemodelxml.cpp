#include "performfilemodelxml.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "performfilemodel.h"
#include "fileutil.h"
#include "startupactionsmanager.h"

/**
 * Handle XML persistence of PerformFileModel objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @author Ken Cameron Copyright: 2014(c)
 * @see apps.startup.PerformFileModelFactory
 */
///*public*/ class PerformFileModelXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ PerformFileModelXml::PerformFileModelXml(QObject* parent) : AbstractXmlAdapter(parent) {
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type PerformActonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement PerformFileModelXml::store(QObject* o) {
    QDomElement e = doc.createElement("perform");
    PerformFileModel* g = (PerformFileModel*) o;

    e.setAttribute("name", FileUtil::getPortableFilename(g->getFileName()));
    e.setAttribute("type", "XmlFile");
    e.setAttribute("class", "apps.PerformFileModel");
    return e;
}

/**
 * Object should be loaded after basic GUI constructed
 *
 * @return true to defer loading
 * @see jmri.configurexml.AbstractXmlAdapter#loadDeferred()
 * @see jmri.configurexml.XmlAdapter#loadDeferred()
 */
//@Override
/*public*/ bool PerformFileModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool PerformFileModelXml::load(QDomElement shared, QDomElement /*perNode*/) throw (JmriException) {
    bool result = true;
    QString fileName = FileUtil::getAbsoluteFilename(shared.attribute("name"));
    PerformFileModel* m = new PerformFileModel();
    m->setFileName(fileName);
    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->addAction((StartupModel*)m);
    return result;
}

/**
 * Update static data from XML file
 *
 * @param element Top level QDomElement to unpack.
 * @param o       ignored
 */
//@Override
/*public*/ void PerformFileModelXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
    log-> error("Unexpected call of load(Element, Object)");
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* PerformFileModelXml::log = LoggerFactory::getLogger("PerformFileModelXml");
