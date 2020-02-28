#include "lnreportermanagerxml.h"

LnReporterManagerXml::LnReporterManagerXml(QObject* parent) : AbstractReporterManagerConfigXML(parent)
{
 log = new Logger("LnReporterManagerXml");
}
/**
 * Provides load and store functionality for
 * configuring LnReporterManagers.
 * <P>
 * Uses the store method from the abstract base class, but
 * provides a load method here.
 *
 * @author Bob Jacobsen Copyright: Copyright (c) 2002
 * @version $Revision: 17977 $
 */
// /*public*/ class LnReporterManagerXml extends jmri.managers.configurexml.AbstractReporterManagerConfigXML {

///*public*/ LnReporterManagerXml() {
//    super();
//}

/*public*/ void LnReporterManagerXml::setStoreElementClass(QDomElement reporters) const
{
 reporters.setAttribute("class","jmri.jmrix.loconet.configurexml.LnReporterManagerXml");
}

/*public*/ void LnReporterManagerXml::load(QDomElement /*element*/, QObject* /*o*/) throw (Exception){
 log->error("Invalid method called");
}

/*public*/ bool LnReporterManagerXml::load(QDomElement reporters) throw (Exception)
{
 // load individual Reporters
 return loadReporters(reporters);
}
