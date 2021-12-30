#include "acelaconnectiontypelist.h"

/**
 * Returns a list of valid CTI Electronics Connection Types
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Kevin Dickerson Copyright (C) 2010
 */
//@ServiceProvider(service = ConnectionTypeList.class)
///*public*/ class AcelaConnectionTypeList implements jmri.jmrix.ConnectionTypeList {

    /*public*/ /*static*/ /*final*/ QString AcelaConnectionTypeList::CTI = "CTI Electronics";

    //@Override
    /*public*/ QStringList AcelaConnectionTypeList::getAvailableProtocolClasses() {
        return QStringList{
            "jmri.jmrix.acela.serialdriver.ConnectionConfig"
        };
    }

    //@Override
    /*public*/ QStringList AcelaConnectionTypeList::getManufacturers() {
        return QStringList{CTI};
    }
