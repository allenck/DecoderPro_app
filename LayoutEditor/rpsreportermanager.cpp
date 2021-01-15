#include "rpsreportermanager.h"
#include "rpsreporter.h"
#include "distributor.h"
#include "rpssystemconnectionmemo.h"
#include "loggerfactory.h"
#include "rpssystemconnectionmemo.h"

RpsReporterManager::RpsReporterManager(RpsSystemConnectionMemo* memo, QObject* parent) : AbstractReporterManager(memo, parent)
{

}

/**
 * RPS implementation of a ReporterManager.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
  * @since 2.3.1
 */
// /*public*/ class RpsReporterManager extends AbstractReporterManager {
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo *RpsReporterManager::getMemo() const {
    return  memo;
}


//@Override
/*protected*/ Reporter* RpsReporterManager::createNewReporter(QString systemName, QString userName) const {
    RpsReporter* r = new RpsReporter(systemName, userName);
    //Distributor::instance()->addMeasurementListener(r);
    connect(Distributor::instance(), SIGNAL(newMeasurement(Measurement*)), r, SLOT(notify(Measurement*)));
    return (Reporter*)r;
}

//@Override
/*public*/ QString RpsReporterManager::createSystemName(QString curAddress, QString prefix) throw (JmriException) {
    if (prefix != (getSystemPrefix())) {
        log->warn("prefix does not match memo.prefix");
        throw JmriException("Unable to convert " + curAddress + ", Prefix does not match");
    }
    QString sys = getSystemPrefix() + typeLetter() + curAddress;
    // first, check validity
    try {
        validSystemNameFormat(sys);
    } catch (IllegalArgumentException e) {
        throw JmriException(e.getMessage());
    }
    return sys;
}

/**
 * {@inheritDoc}
 */
//@Override
//@Nonnull
/*public*/ QString RpsReporterManager::validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale) {
    return ((RpsSystemConnectionMemo*) getMemo())->validateSystemNameFormat(name, this, locale);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ RpsReporterManager::NameValidity RpsReporterManager::validSystemNameFormat(/*@Nonnull*/ QString systemName) {
    return ((RpsSystemConnectionMemo*) getMemo())->validSystemNameFormat(systemName, typeLetter());
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString RpsReporterManager::getEntryToolTip() {
    return tr("<html>A set of at least 3 (x,y,z) point coordinates that form a Region, e.g.<br>(0,0,0);(1,0,0);(1,1,0);(0,1,0)</html>");
}

/*private*/ /*final*/ /*static*/ Logger* RpsReporterManager::log = LoggerFactory::getLogger("RpsReporterManager");
