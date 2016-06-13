#ifndef DCCMANUFACTURERLIST_H
#define DCCMANUFACTURERLIST_H

#include <QObject>
#include <QStringList>
#include "lnconnectiontypelist.h"

class LIBPR3SHARED_EXPORT DCCManufacturerList : public QObject
{
    Q_OBJECT
public:
    explicit DCCManufacturerList(QObject *parent = 0);
    static  QString NONE;//"None";  // internal only
    static  QString LENZ;//"Lenz";
    static  QString HORNBY;//"Hornby";
    static  QString BACHRUS;//"Bachrus";
    static  QString ESU;//"ESU";
    static  QString DIGITRAX;//"Digitrax";
    static  QString ATLAS;//"Atlas";
    static  QString NCE;//"NCE";
    static  QString CMRI;//"C/MRI";
    static  QString CTI;//"CTI Electronics";
    static  QString EASYDCC;//"Easy DCC";
    static  QString DCC4PC;//"DCC4PC";
    static  QString DCCSPEC;//"DCC Specialties";
    static  QString FLEISHMANN;//"Fleishmann";
    static  QString JMRI;//"JMRI (Network)";
    static  QString LIONEL;//"Lionel TMCC";
    static  QString MAPLE;//"Maple Systems";
    static  QString MERG;//"MERG";
    static  QString MARKLIN;//"Marklin";
    static  QString NAC;//"NAC Services";
    static  QString OAK;//"Oak Tree Systems";
    static  QString OPENLCB;//"OpenLCB";
    static  QString OTHER;//"Others";
    static  QString POWERLINE;//"Powerline";
    static  QString PROTRAK;//"Protrak";
    static  QString QSI;//"QSI Solutions";
    static  QString RAIL;//"RailDriver";
    static  QString RFID;//"RFID";
    static  QString ROCO;//"Roco";
    static  QString SPROG;//"SPROG DCC";
    static  QString SRCP;//"SRCP";
    static  QString TAMS;//"Tams";
    static  QString TRACTRONICS;//"TracTronics";
    static  QString UHLEN;//"Uhlenbrock";
    static  QString WANGROW;//"Wangrow";
    static  QString ZIMO;//"Zimo";
    static  QString ZTC;//"ZTC";
    static  QString IEEE802154;// = "IEEE 802.15.4";
    static  QString MRC;// = "MRC";

    static QStringList* systemNames;// = new QStringList[]{
    /*public static*/static  QStringList* getSystemNames();
    /*public*/ static QStringList getConnectionList(QString System);
    //Some of these are now redundant if the connection has been converted to SystemConnectionMemo
    /*public*/ static char getTypeFromDCCSystem(QString a);
    //Some of these are now redundant if the connection has been converted to SystemConnectionMemo
    /*public*/ static QString getDCCSystemFromType(QChar a);

signals:
    
public slots:
    
};

#endif // DCCMANUFACTURERLIST_H
