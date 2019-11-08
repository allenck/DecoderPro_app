#include "internalreportermanager.h"
#include "abstractreporter.h"
#include "internalsystemconnectionmemo.h"
#include "trackreporter.h"

InternalReporterManager::InternalReporterManager(InternalSystemConnectionMemo* memo, QObject *parent) :
    AbstractReporterManager(memo, parent)
{
 setObjectName("InternalReporterManager");
}
/**
 * Implementation of the InternalReporterManager interface.
 * @author			Bob Jacobsen Copyright (C) 2010
 * @version			$Revision: 17977 $
 * @since           2.9.4
 */
//public class InternalReporterManager extends AbstractReporterManager {

/**
 * Create an internal (dummy) reporter object
 * @return new null
 */
/*protected*/ Reporter* InternalReporterManager::createNewReporter(QString systemName, QString userName)
{
 return new TrackReporter(systemName, userName);
}

/*public*/ QString InternalReporterManager::getSystemPrefix() { return "I"; }

