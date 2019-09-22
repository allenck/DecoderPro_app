#include "rfidreportermanager.h"
#include "rfidmessage.h"
#include "rfidsystemconnectionmemo.h"

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


/*public*/ RfidReporterManager::RfidReporterManager(RfidSystemConnectionMemo* memo, QObject *parent) : AbstractReporterManager(memo, parent)
{
 //super();
 //this->prefix = prefix;
 log = new Logger("RfidReporterManager");
}

/*public*/ QString RfidReporterManager::getSystemPrefix() {
    return prefix;
}

//@Override
/*public*/ void RfidReporterManager::message(RfidMessage* m) {
    log->warn("Unexpected message received: " + m->toString());
}

Reporter* RfidReporterManager::createNewReporter(QString systemName, QString userName)
{
 RfidReporter* r = new RfidReporter(systemName, userName, this);
 r->AbstractNamedBean::setUserName(userName);
 return (Reporter*)r;
}
