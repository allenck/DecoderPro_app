#include "otherconnectiontypelist.h"

/**
 * Return a list of valid Connection Types.
 * @see jmri.jmrix.direct.DirectConnectionTypeList
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Kevin Dickerson Copyright (C) 2010
 */
//@ServiceProvider(service = ConnectionTypeList.class)
//public class OtherConnectionTypeList implements jmri.jmrix.ConnectionTypeList {

    /*public*/ /*static*/ /*final*/ QString OtherConnectionTypeList::OTHER = "Others"; // NOI18N

    //@Override
    /*public*/ QStringList OtherConnectionTypeList::getAvailableProtocolClasses() {
        return QStringList{
            "jmri.jmrix.direct.serial.ConnectionConfig",
            "jmri.jmrix.direct.simulator.ConnectionConfig"
        };
    }

    //@Override
    /*public*/ QStringList OtherConnectionTypeList::getManufacturers() {
        return QStringList{OTHER};
    }
