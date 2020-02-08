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
              "jmri.jmrix.loconet.pr4.ConnectionConfig",
              "jmri.jmrix.loconet.usb_dcs240.ConnectionConfig", //NOI18N
              "jmri.jmrix.loconet.usb_dcs52.ConnectionConfig", //NOI18N
              "jmri.jmrix.loconet.hexfile.ConnectionConfig",
              "jmri.jmrix.loconet.locormi.ConnectionConfig",
              "jmri.jmrix.loconet.loconetovertcp.ConnectionConfig",
              "jmri.jmrix.loconet.locobufferii.ConnectionConfig",
              "jmri.jmrix.loconet.locobuffer.ConnectionConfig",
              "jmri.jmrix.loconet.ms100.ConnectionConfig",
              "jmri.jmrix.loconet.bluetooth.ConnectionConfig", // NOI18N
              "jmri.jmrix.loconet.streamport.LnStreamConnectionConfig" // NOI18N
        };
#endif
     QStringList list;
     list << "Pr2ConnectionConfig"
          << "Pr3ConnectionConfig"
          << "Pr4ConnectionConfig"
          << "LocobufferConnectionConfig"
          << "LocobufferUsbConnectionConfig"
          << "LocoBufferIIConnectionConfig"
          << "HexFileConnectionConfig"
          << "LnOverTcpConnectionConfig"
          << "DCS240ConnectionConfig"
          << "DCS52ConnectionConfig";
     return list;
    }
