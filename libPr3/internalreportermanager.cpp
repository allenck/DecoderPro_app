#include "internalreportermanager.h"
#include "abstractreporter.h"
#include "internalsystemconnectionmemo.h"

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
#if 1
    /*protected*/ Reporter* InternalReporterManager::createNewReporter(QString systemName, QString userName)
{
 Reporter* reporter = (Reporter*)new AbstractReporter(systemName, userName);
 return reporter;
//        {
//            public int getState() { return state; }
//            public void setState(int s) { state = s; }
//            int state = 0;
//        };
    }
#endif
    /*public*/ QString InternalReporterManager::getSystemPrefix() { return "I"; }

