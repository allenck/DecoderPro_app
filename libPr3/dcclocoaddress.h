#ifndef DCCLOCOADDRESS_H
#define DCCLOCOADDRESS_H
#include "locoaddress.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DccLocoAddress :  public LocoAddress
{
    Q_OBJECT
public:
 DccLocoAddress(QObject *parent = 0) {}
    explicit DccLocoAddress(int number, bool isLong, QObject *parent = 0);
    DccLocoAddress(int number, Protocol protocol, QObject *parent = 0);
    DccLocoAddress(const DccLocoAddress& l , QObject* parent = 0);
    bool operator ==(const LocoAddress &a) override;
    /*public*/ bool equals(QObject* a);
    int hashCode();
    QString toString();
    bool isLongAddress();
    virtual Protocol getProtocol() const;
    virtual int getNumber() const;
signals:
    
public slots:
protected:
 long number;
 Protocol protocol;
friend class NmraConsist;
    
};

#endif // DCCLOCOADDRESS_H
