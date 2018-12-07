#include "rfidconnectiontypelist.h"

RfidConnectionTypeList::RfidConnectionTypeList(QObject *parent)
{

}
/**
 * Returns a list of valid RFID Connection Types
 * <P>
 * @author Bob Jacobsen Copyright (C) 2010, 2015
 * @author Kevin Dickerson Copyright (C) 2010
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
//@ServiceProvider(service = ConnectionTypeList.class)
// /*public*/ class RfidConnectionTypeList implements jmri.jmrix.ConnectionTypeList {

/*public*/ /*static*/ /*final*/ QString RfidConnectionTypeList::RFID = "RFID";

//@Override
/*public*/ QStringList RfidConnectionTypeList::getAvailableProtocolClasses() {
//    return QStringList() <<
//        "jmri.jmrix.rfid.serialdriver.ConnectionConfig" <<
//        "jmri.jmrix.rfid.networkdriver.ConnectionConfig"
//    ;
 QStringList list;
 list << "RfidSerialConnectionConfig";
 return list;
}

//@Override
/*public*/ QStringList RfidConnectionTypeList::getManufacturers() {
    return QStringList() << RFID;
}

