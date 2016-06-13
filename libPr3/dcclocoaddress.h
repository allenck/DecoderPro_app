#ifndef DCCLOCOADDRESS_H
#define DCCLOCOADDRESS_H
#include "locoaddress.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DccLocoAddress : public LocoAddress
{
    Q_OBJECT
public:
    explicit DccLocoAddress(int number, bool isLong, QObject *parent = 0);
    DccLocoAddress(int number, Protocol protocol, QObject *parent = 0);
    DccLocoAddress(const DccLocoAddress& l , QObject* parent = 0);
    bool operator==(DccLocoAddress* a);
    int hashCode();
    QString toString();
    bool isLongAddress();
    virtual Protocol getProtocol();
    virtual int getNumber();

signals:
    
public slots:
protected:
 long number;
 Protocol protocol;
friend class NmraConsist;
    
};

#endif // DCCLOCOADDRESS_H
