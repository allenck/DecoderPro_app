#include "lnconnectiontypelist.h"
#include <QStringList>

LNConnectionTypeList::LNConnectionTypeList(QObject *parent) :
    QObject(parent)
{
}
/**
 * Returns a list of valid lenz XpressNet Connection Types
 * <P>
 * @author      Bob Jacobsen   Copyright (C) 2010
 * @author      Kevin Dickerson    Copyright (C) 2010
 * @version	$Revision: 17977 $
 *
 */
//public class LnConnectionTypeList  implements jmri.jmrix.ConnectionTypeList {

    /*public*/ QStringList LNConnectionTypeList::getAvailableProtocolClasses() {
#if 0 // TODO:
        return new String[] {
              "jmri.jmrix.loconet.locobufferusb.ConnectionConfig",
              "jmri.jmrix.loconet.pr2.ConnectionConfig",
              "jmri.jmrix.loconet.pr3.ConnectionConfig",
              "jmri.jmrix.loconet.hexfile.ConnectionConfig",
              "jmri.jmrix.loconet.locormi.ConnectionConfig",
              "jmri.jmrix.loconet.loconetovertcp.ConnectionConfig",
              "jmri.jmrix.loconet.locobufferii.ConnectionConfig",
              "jmri.jmrix.loconet.locobuffer.ConnectionConfig",
              "jmri.jmrix.loconet.ms100.ConnectionConfig"
        };
#endif
     QStringList list;
     list << "Pr3ConnectionConfig" << "LocobufferConnectionConfig"
          << "LocobufferUsbConnectionConfig" << "HexFileConnectionConfig"
          << "LnOverTcpConnectionConfig" << "Pr2ConnectionConfig" << "PR4ConnectionConfig";
     return list;
    }
