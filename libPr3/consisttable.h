#ifndef CONSISTTABLE_H
#define CONSISTTABLE_H
#include <QObject>
#include <QMap>

class DccLocoAddress;
class DccConsist;
// Class to handle pointers to LocoAddresses
class ConsistAddrList : public QObject
{
 Q_OBJECT
public:
 ConsistAddrList(QObject* parent = nullptr);
 ConsistAddrList(QList<DccLocoAddress*> list, QObject* parent = nullptr);
 bool contains(DccLocoAddress* addrIn);
 void append(DccLocoAddress* addr);
 bool remove(DccLocoAddress* addrIn);
 int size();
 bool isEmpty();
 QList<DccLocoAddress*> toList();
private:
 QList<DccLocoAddress*> consistAddrList;
};

class ConsistTable : public QObject
{
 Q_OBJECT
public:
 ConsistTable(QObject* parent = nullptr);
 bool contains(DccLocoAddress* addrIn);
 void insert(DccLocoAddress* addrIn, DccConsist* consist);
 bool remove(DccLocoAddress* addrIn);
 DccConsist* value(DccLocoAddress* addrIn);
 ConsistAddrList* getConsistList();
 int size();
private:
QMap< DccLocoAddress*, DccConsist*> consistTable;
};

#endif // CONSISTTABLE_H
