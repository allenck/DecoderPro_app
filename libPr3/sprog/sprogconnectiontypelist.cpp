#include "sprogconnectiontypelist.h"

SprogConnectionTypeList::SprogConnectionTypeList()
{

}
/**
 * Returns a list of valid Sprog Connection Types.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Kevin Dickerson Copyright (C) 2010
 */
//@ServiceProvider(service = ConnectionTypeList.class)
///*public*/ class SprogConnectionTypeList implements jmri.jmrix.ConnectionTypeList {

/*public*/ /*static*/ /*final*/ QString SprogConnectionTypeList::SPROG = "SPROG DCC";

//@Override
/*public*/ QStringList SprogConnectionTypeList::getAvailableProtocolClasses() {
    QStringList l = QStringList() <<
//        "jmri.jmrix.sprog.sprog.ConnectionConfig" <<
//        "jmri.jmrix.sprog.sprogCS.ConnectionConfig"<<
//        "jmri.jmrix.sprog.sprognano.ConnectionConfig"<<
//        "jmri.jmrix.sprog.pi.pisprogone.ConnectionConfig"<<
//        "jmri.jmrix.sprog.pi.pisprogonecs.ConnectionConfig"<<
//        "jmri.jmrix.sprog.pi.pisprognano.ConnectionConfig"<<
//        "jmri.jmrix.sprog.simulator.ConnectionConfig";
          "Sprog::SprogConnectionConfig" << "Sprog::SprogCSConnectionConfig";
    return l;
}

//@Override
/*public*/ QStringList SprogConnectionTypeList::getManufacturers() {
    //return new String[]{SPROG};
return QStringList() << SPROG;
}
