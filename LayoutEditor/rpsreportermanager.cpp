#include "rpsreportermanager.h"
#include "rpsreporter.h"
#include "distributor.h"

RpsReporterManager::RpsReporterManager(QObject* parent) : AbstractReporterManager(parent)
{

}
/**
 * RPS implementation of a ReporterManager.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
  * @since 2.3.1
 */
// /*public*/ class RpsReporterManager extends AbstractReporterManager {

//@Override
/*public*/ QString RpsReporterManager::getSystemPrefix() {
    return "R";
}

//@Override
/*protected*/ Reporter* RpsReporterManager::createNewReporter(QString systemName, QString userName) {
    RpsReporter* r = new RpsReporter(systemName, userName);
    //Distributor::instance()->addMeasurementListener(r);
    connect(Distributor::instance(), SIGNAL(newMeasurement(Measurement*)), r, SLOT(notify(Measurement*)));
    return (Reporter*)r;
}

/*static*/ /*public*/ RpsReporterManager* RpsReporterManager::instance() {
    if (_instance == NULL) {
        _instance = new RpsReporterManager();
    }
    return _instance;
}

/*static*/ RpsReporterManager* RpsReporterManager::_instance = NULL;
#if 0
static { // class initialization
    // now want a ReporterManager always, not just when RPS is created
    if (_instance == null) {
        _instance = new RpsReporterManager();
        jmri.InstanceManager.setReporterManager(jmri.jmrix.rps.RpsReporterManager.instance());
        // log.warn("Setting RpsSensorManager instance at startup time!");
    }
}
#endif
