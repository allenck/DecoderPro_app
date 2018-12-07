#include "dccmanufacturerlist.h"
#include "rfid/rfidconnectiontypelist.h"

DCCManufacturerList::DCCManufacturerList(QObject *parent) :
    QObject(parent)
{
//    NONE = "None";  // internal only
//    LENZ = "Lenz";
//    HORNBY = "Hornby";
//    BACHRUS = "Bachrus";
//    ESU = "ESU";
//    DIGITRAX = "Digitrax";
//    ATLAS = "Atlas";
//    NCE = "NCE";
//    CMRI = "C/MRI";
//    CTI = "CTI Electronics";
//    EASYDCC = "Easy DCC";
//    DCC4PC = "DCC4PC";
//    DCCSPEC = "DCC Specialties";
//    FLEISHMANN = "Fleishmann";
//    JMRI = "JMRI (Network)";
//    LIONEL = "Lionel TMCC";
//    MAPLE = "Maple Systems";
//    MERG = "MERG";
//    MARKLIN = "Marklin";
//    NAC = "NAC Services";
//    OAK = "Oak Tree Systems";
//    OPENLCB = "OpenLCB";
//    OTHER = "Others";
//    POWERLINE = "Powerline";
//    PROTRAK = "Protrak";
//    QSI = "QSI Solutions";
//    RAIL = "RailDriver";
//    RFID = "RFID";
//    ROCO = "Roco";
//    SPROG = "SPROG DCC";
//    SRCP = "SRCP";
//    TAMS = "Tams";
//    TRACTRONICS = "TracTronics";
//    UHLEN = "Uhlenbrock";
//    WANGROW = "Wangrow";
//    ZIMO = "Zimo";
//    ZTC = "ZTC";

//    systemNames = new QStringList;
//    *systemNames <<
//    NONE<<
//    ATLAS<<
//    BACHRUS<<
//    CMRI<<
//    CTI<<
//    DIGITRAX<<
//    DCCSPEC<<
//    DCC4PC<<
//    EASYDCC<<
//    ESU<<
//    FLEISHMANN<<
//    HORNBY<<
//    JMRI<<
//    LENZ<<
//    LIONEL<<
//    MAPLE<<
//    MARKLIN<<
//    MERG<<
//    NCE<<
//    NAC<<
//    OAK<<
//    OPENLCB<<
//    OTHER<<
//    POWERLINE<<
//    PROTRAK<<
//    QSI<<
//    RFID<<
//    ROCO<<
//    SPROG<<
//    SRCP<<
//    TAMS<<
//    TRACTRONICS<<
//    UHLEN<<
//    WANGROW<<
//    ZIMO<<
//    ZTC;
//    "Digitrax";

}
QString     DCCManufacturerList::NONE = "None";  // internal only
QString     DCCManufacturerList::LENZ = "Lenz";
QString     DCCManufacturerList::HORNBY = "Hornby";
QString     DCCManufacturerList::BACHRUS = "Bachrus";
QString     DCCManufacturerList::ESU = "ESU";
QString     DCCManufacturerList::DIGITRAX = "Digitrax";
QString     DCCManufacturerList::ATLAS = "Atlas";
QString     DCCManufacturerList::NCE = "NCE";
QString     DCCManufacturerList::CMRI = "C/MRI";
QString     DCCManufacturerList::CTI = "CTI Electronics";
QString     DCCManufacturerList::EASYDCC = "Easy DCC";
QString     DCCManufacturerList::DCC4PC = "DCC4PC";
QString     DCCManufacturerList::DCCSPEC = "DCC Specialties";
QString     DCCManufacturerList::FLEISHMANN = "Fleishmann";
QString     DCCManufacturerList::JMRI = "JMRI (Network)";
QString     DCCManufacturerList::LIONEL = "Lionel TMCC";
QString     DCCManufacturerList::MAPLE = "Maple Systems";
QString     DCCManufacturerList::MERG = "MERG";
QString     DCCManufacturerList::MARKLIN = "Marklin";
QString     DCCManufacturerList::NAC = "NAC Services";
QString     DCCManufacturerList::OAK = "Oak Tree Systems";
QString     DCCManufacturerList::OPENLCB = "OpenLCB";
QString     DCCManufacturerList::OTHER = "Others";
QString     DCCManufacturerList::POWERLINE = "Powerline";
QString     DCCManufacturerList::PROTRAK = "Protrak";
QString     DCCManufacturerList::QSI = "QSI Solutions";
QString     DCCManufacturerList::RAIL = "RailDriver";
QString     DCCManufacturerList::RFID = "RFID";
QString     DCCManufacturerList::ROCO = "Roco";
QString     DCCManufacturerList::SPROG = "SPROG DCC";
QString     DCCManufacturerList::SRCP = "SRCP";
QString     DCCManufacturerList::TAMS = "Tams";
QString     DCCManufacturerList::TRACTRONICS = "TracTronics";
QString     DCCManufacturerList::UHLEN = "Uhlenbrock";
QString     DCCManufacturerList::WANGROW = "Wangrow";
QString     DCCManufacturerList::ZIMO = "Zimo";
QString     DCCManufacturerList::ZTC = "ZTC";
QString     DCCManufacturerList::IEEE802154 = "IEEE 802.15.4";
QString     DCCManufacturerList::MRC = "MRC";
/**
 * Maintains lists equipment manufacturers that JMRI Supports.
 * <P>
 * If you add to this, please add your new one in all
 * sections if possible.
 * <P>
 * @author      Bob Jacobsen   Copyright (C) 2010
 * @author      Kevin Dickerson    Copyright (C) 2010
 * @version	$Revision: 21708 $
 *
 */
//public class DCCManufacturerList {




    //@edu.umd.cs.findbugs.annotations.SuppressWarnings({"EI_EXPOSE_REP", "MS_EXPOSE_REP"}) // OK until Java 1.6 allows return of cheap array copy
    /*public static*/ QStringList* DCCManufacturerList::getSystemNames() {
    QStringList* list = new QStringList();
    *list << NONE <<
//             ATLAS <<
//             BACHRUS <<
//             CMRI <<
//             CTI <<
             DIGITRAX <<
//             DCCSPEC <<
//             DCC4PC <<
//             EASYDCC <<
//             ESU <<
//             HORNBY <<
//             IEEE802154 <<
//             JMRI <<
//             LENZ <<
//             LIONEL <<
//             MAPLE <<
//             MARKLIN <<
//             MERG <<
//             MRC <<
//             NCE <<
//             NAC <<
//             OAK <<
//             OPENLCB <<
//             OTHER <<
//             POWERLINE <<
//             PROTRAK <<
//             QSI <<
             RFID <<
//             ROCO <<
             SPROG;
//             SRCP <<
//             TAMS <<
//             TRACTRONICS <<
//             UHLEN <<
//             WANGROW <<
//             ZIMO <<
//             ZTC;
    return list;
    }

/*public*/  QStringList  DCCManufacturerList::getConnectionList(QString System)
{
//        if(System==(NONE)) { return new InternalConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(ATLAS)) { return new jmri.jmrix.lenz.LenzConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(BACHRUS)) { return new jmri.jmrix.bachrus.SpeedoConnectionTypeList().getAvailableProtocolClasses();  }
//        if(System==(CMRI)) { return new jmri.jmrix.cmri.CMRIConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(CTI)) { return new jmri.jmrix.acela.AcelaConnectionTypeList().getAvailableProtocolClasses(); }
 if(System==("Digitrax"))
 {
  LNConnectionTypeList* typelist = new  LNConnectionTypeList();
  QStringList list = QStringList();

  list = typelist->getAvailableProtocolClasses();
  return list;
 }
//        if(System==(DCC4PC)) { return new jmri.jmrix.dcc4pc.Dcc4PcConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(EASYDCC)) { return new jmri.jmrix.easydcc.EasyDccConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(DCC4PC)) { return new jmri.jmrix.dcc4pc.Dcc4PcConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(ESU)) { return new jmri.jmrix.ecos.EcosConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(FLEISHMANN)) { return new jmri.jmrix.loconet.Intellibox.FleischmannConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(HORNBY)) { return new jmri.jmrix.lenz.hornbyelite.EliteConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(LENZ)) { return new jmri.jmrix.lenz.LenzConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(LIONEL)) { return new jmri.jmrix.tmcc.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(MAPLE)) { return new jmri.jmrix.maple.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(MERG)) { return new jmri.jmrix.merg.MergConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(MARKLIN)) { return new jmri.jmrix.marklin.MarklinConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(NAC)) { return new jmri.jmrix.rps.RpsConnectionTypeList().getAvailableProtocolClasses();   }
//        if(System==(NCE)) { return new jmri.jmrix.nce.NceConnectionTypeList().getAvailableProtocolClasses();   }
//        if(System==(OAK)) { return new jmri.jmrix.oaktree.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(OPENLCB)) { return new jmri.jmrix.openlcb.OlcbConnectionTypeList().getAvailableProtocolClasses();  }
//        if(System==(POWERLINE)) { return new jmri.jmrix.powerline.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(PROTRAK)) { return new jmri.jmrix.grapevine.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(QSI)) { return new jmri.jmrix.qsi.QSIConnectionTypeList().getAvailableProtocolClasses(); }
        if(System==(RFID))
        { //return new RfidConnectionTypeList().getAvailableProtocolClasses();
         RfidConnectionTypeList* list = new RfidConnectionTypeList();
         return list->getAvailableProtocolClasses();
        }
//        if(System==(ROCO)) { return new jmri.jmrix.lenz.LenzConnectionTypeList().getAvailableProtocolClasses(); }
        if(System==(SPROG)) { return (new SprogConnectionTypeList())->getAvailableProtocolClasses();  }
//        if(System==(SRCP)) { return new jmri.jmrix.srcp.SRCPConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(TAMS)) { return new jmri.jmrix.tams.TamsConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(TRACTRONICS)) { return new jmri.jmrix.secsi.SerialConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(UHLEN)) { return new jmri.jmrix.loconet.uhlenbrock.UhlenbrockConnectionTypeList().getAvailableProtocolClasses();   }
//        if(System==(WANGROW)) { return new jmri.jmrix.wangrow.WangrowConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(ZIMO)) { return new jmri.jmrix.zimo.Mx1ConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(ZTC)) { return new jmri.jmrix.lenz.ztc640.ZTC640ConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(OTHER)) { return new jmri.jmrix.OtherConnectionTypeList().getAvailableProtocolClasses(); }
//        if(System==(JMRI)) { return new jmri.jmrix.jmriclient.JMRIClientConnectionTypeList().getAvailableProtocolClasses(); }
//        return new jmri.jmrix.internal.InternalConnectionTypeList().getAvailableProtocolClasses();
 return QStringList();
}

//Some of these are now redundant if the connection has been converted to SystemConnectionMemo
/*public static */QString DCCManufacturerList::getDCCSystemFromType(QChar a)
{
    if (a=='I') return "Internal";
    else if (a=='A') return "Acela";
    else if (a=='C') return "C/MRI";
    else if (a=='D') return "SRCP";
    else if (a=='E') return "EasyDCC";
    else if (a=='F') return "RFID";
    else if (a=='G') return "Grapevine";
    else if (a=='K') return "Maple";
    else if (a=='L') return "LocoNet";
    else if (a=='N') return "NCE";
    else if (a=='O') return "Oak Tree";
    else if (a=='M') return "OpenLCB";  // duplicates MERG?
    else if (a=='M') return "MERG";
    else if (a=='P') return "PowerLine";
    else if (a=='Q') return "QSI";
    else if (a=='R') return "RPS";
    else if (a=='S') return "Sprog";
    else if (a=='T') return "Lionel TMCC";
    else if (a=='U') return "ECoS";
    else if (a=='V') return "SECSI";
    else if (a=='W') return "Wangrow";
    else if (a=='X') return "XpressNet";
    else if (a=='Z') return "Zimo";
    return "Unknown";
}

//Some of these are now redundant if the connection has been converted to SystemConnectionMemo
/*public*/ /*static*/ char DCCManufacturerList::getTypeFromDCCSystem(QString a)
{
    if (a==("Internal")) return 'I';
    else if (a==("Acela")) return 'A';
    else if (a==("C/MRI")) return 'C';
    else if (a==("SRCP")) return 'D';
    else if (a==("EasyDCC")) return 'E';
    else if (a==("RFID")) return 'F';
    else if (a==("Grapevine")) return 'G';
    else if (a==("Maple")) return 'K';
    else if (a==("LocoNet")) return 'L';
    else if (a==("MERG")) return 'M';
    else if (a==("OpenLCB")) return 'M';
    else if (a==("NCE")) return 'N';
    else if (a==("Oak Tree")) return 'O';
    else if (a==("PowerLine")) return 'P';
    else if (a==("QSI")) return 'Q';
    else if (a==("RPS")) return 'R';
    else if (a==("Sprog")) return 'S';
    else if (a==("Lionel TMCC")) return 'T';
    else if (a==("ECoS")) return 'U';
    else if (a==("SECSI")) return 'V';
    else if (a==("Wangrow")) return 'W';
    else if (a==("XpressNet")) return 'X';
    else if (a==("Zimo")) return 'Z';
    return '\0';
}
