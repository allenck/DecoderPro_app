#include "rfidreportermanager.h"

//RfidReporterManager::RfidReporterManager(QObject *parent) :
//    AbstractReporterManager(parent)
//{
//}
/**
 * Rfid implementation of a ReporterManager.
 * <P>
 * System names are "FRpppp", where ppp is a
 * representation of the RFID reader.
 * <P>
 * @author      Bob Jacobsen    Copyright (C) 2008
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
//abstract public class RfidReporterManager extends AbstractReporterManager implements RfidListener {


/*public*/ RfidReporterManager::RfidReporterManager(QString prefix, QObject *parent) : AbstractReporterManager(parent)
{
 //super();
 this->prefix = prefix;
 log = new Logger("RfidReporterManager");
}

/*public*/ QString RfidReporterManager::getSystemPrefix() {
    return prefix;
}
AbstractReporter* RfidReporterManager::createNewReporter(QString systemName, QString userName)
{
 RfidReporter* r = new RfidReporter(systemName, userName, this);
 r->AbstractNamedBean::setUserName(userName);
 return (AbstractReporter*)r;
}
