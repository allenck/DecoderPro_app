#include "performscriptmodelxml.h"
#include "fileutil.h"
#include "performscriptmodel.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "loggerfactory.h"

/**
 * Handle XML persistance of PerformScriptModel objects
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2003
 * @author Ken Cameron Copyright: Copyright (c) 2014
 * @see apps.startup.PerformScriptModelFactory
 */
///*public*/ class PerformScriptModelXml extends jmri.configurexml.AbstractXmlAdapter {

/*public*/ PerformScriptModelXml::PerformScriptModelXml(QObject* parent) :AbstractXmlAdapter(parent) {
}

/**
 * Default implementation for storing the model contents
 *
 * @param o Object to store, of type PerformActonModel
 * @return QDomElement containing the complete info
 */
//@Override
/*public*/ QDomElement PerformScriptModelXml::store(QObject* o) {
    QDomElement e = doc.createElement("perform");
    PerformScriptModel* g = (PerformScriptModel*) o;

    e.setAttribute("name", FileUtil::getPortableFilename(g->getFileName()));
    e.setAttribute("type", "ScriptFile");
    e.setAttribute("class", "apps.PerformScriptModel");
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
/*public*/ bool PerformScriptModelXml::loadDeferred() {
    return true;
}

//@Override
/*public*/ bool PerformScriptModelXml::load(QDomElement shared, QDomElement perNode) throw (Exception) {
    bool result = true;
    QString fileName = shared.attribute("name");
    fileName = FileUtil::getAbsoluteFilename(fileName);
    PerformScriptModel* m = new PerformScriptModel();
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
/*public*/ void PerformScriptModelXml::load(QDomElement element, QObject* o) throw (Exception){
    log-> error("Unexpected call of load(Element, Object)");
}
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* PerformScriptModelXml::log = LoggerFactory::getLogger("PerformScriptModelXml");
