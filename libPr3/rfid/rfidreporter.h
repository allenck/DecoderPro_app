#ifndef RFIDREPORTER_H
#define RFIDREPORTER_H
#include "abstractreporter.h"
#include "idtag.h"
#include "locoaddress.h"
#include "physicallocationreporter.h"


class LIBPR3SHARED_EXPORT RfidReporter : public AbstractReporter
{
    Q_OBJECT
public:
    //explicit RfidReporter(QObject *parent = 0);
    /*public*/ RfidReporter(QString systemName, QObject *parent = 0);
    /*public*/ RfidReporter(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ void notify(DefaultIdTag *id);
    /*public*/ void setState(int s);
    /*public*/ int getState() ;
    /*public*/ LocoAddress* getLocoAddress(QString rep);
    /*public*/ PhysicalLocationReporter::Direction getDirection(QString rep);
    /*public*/ PhysicalLocation* getPhysicalLocation() ;
    /*public*/ PhysicalLocation* getPhysicalLocation(QString s);

signals:
    
public slots:
private:
 Logger* log;
 void init();
 /*private*/ int state;// = UNKNOWN;

};

#endif // RFIDREPORTER_H
