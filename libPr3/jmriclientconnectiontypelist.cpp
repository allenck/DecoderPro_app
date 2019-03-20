#include "jmriclientconnectiontypelist.h"

JMRIClientConnectionTypeList::JMRIClientConnectionTypeList()
{

}
/**
 * Returns a list of valid JMRIClient Connection Types
 * <P>
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Kevin Dickerson Copyright (C) 2010
 * @author Paul Bender Copyright (C) 2010
 * @author Randall Wood Copyright (C) 2014
 */
//@ServiceProvider(service = ConnectionTypeList.class)
//public class JMRIClientConnectionTypeList implements jmri.jmrix.ConnectionTypeList {

    /*public*/ /*static*/ /*final*/ QString JMRIClientConnectionTypeList::JMRI = "JMRI (Network)";

    //@Override
    /*public*/ QStringList JMRIClientConnectionTypeList::getAvailableProtocolClasses() {
        QStringList list = QStringList() <<
//            "jmri.jmrix.jmriclient.networkdriver.ConnectionConfig";
                                            "JMRIClientConnectionConfig";
     return list;
    }

    //@Override
    /*public*/ QStringList JMRIClientConnectionTypeList::getManufacturers() {
        QStringList list = QStringList() <<"JMRI";
        return list;
    }

