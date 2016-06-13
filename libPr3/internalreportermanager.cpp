#include "internalreportermanager.h"
#include "abstractreporter.h"

InternalReporterManager::InternalReporterManager(QObject *parent) :
    AbstractReporterManager(parent)
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
    /*protected*/ AbstractReporter* InternalReporterManager::createNewReporter(QString systemName, QString userName)
{
 AbstractReporter* reporter = new AbstractReporter(systemName, userName);
 return (AbstractReporter*)reporter;
//        {
//            public int getState() { return state; }
//            public void setState(int s) { state = s; }
//            int state = 0;
//        };
    }
#endif
    /*public*/ QString InternalReporterManager::getSystemPrefix() { return "I"; }

