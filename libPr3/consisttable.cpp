#include "consisttable.h"
#include "dcclocoaddress.h"
#include "consist.h"
#include "exceptions.h"

// Class to handle pointers to LocoAddresses
 ConsistAddrList::ConsistAddrList(QObject* parent) : QObject(parent)
 {
  consistAddrList = QList<DccLocoAddress*>();
 }
 ConsistAddrList::ConsistAddrList(QList<DccLocoAddress*> list, QObject* parent) : QObject(parent)
 {
  consistAddrList = list;
 }
 bool ConsistAddrList::contains(DccLocoAddress* addrIn)
 {
  foreach (DccLocoAddress* addr, consistAddrList) {
   if(addrIn->equals(addr))
    return true;
  }
  return false;
 }
 void ConsistAddrList::append(DccLocoAddress* addr)
 {
  if(contains(addr))
   return;
  consistAddrList.append(addr);
 }
 bool ConsistAddrList::remove(DccLocoAddress* addrIn)
 {
  foreach (DccLocoAddress* addr, consistAddrList) {
   if(addrIn->equals(addr))
   {
    consistAddrList.removeOne(addr);
    return true;
   }
  }
  return false;
 }
 int ConsistAddrList::size() {return consistAddrList.count();}
 bool ConsistAddrList::isEmpty() {return consistAddrList.count()== 0;}

 QList<DccLocoAddress*> ConsistAddrList::toList() {return consistAddrList;}


 ConsistTable::ConsistTable(QObject* parent) : QObject(parent)
 {
  consistTable = QMap<DccLocoAddress*, DccConsist*>();
 }
 bool ConsistTable::contains(DccLocoAddress* addrIn)
 {
  foreach (DccLocoAddress* addr, consistTable.keys()) {
   if(addrIn->equals(addr))
    return true;
  }
  return false;
 }

 void ConsistTable::insert(DccLocoAddress* addrIn, DccConsist *consist)
 {
  if(!consistTable.contains(addrIn))
   consistTable.insert(addrIn, consist);
  else
   throw Exception("already present");
 }
 bool ConsistTable::remove(DccLocoAddress* addrIn)
 {
  foreach (DccLocoAddress* addr, consistTable.keys())
  {
   if(addrIn->equals(addr))
   {
    consistTable.remove(addr);
    return true;
   }
  }
  return false;
 }
 DccConsist *ConsistTable::value(DccLocoAddress* addrIn)
 {
  foreach(DccLocoAddress* addr, consistTable.keys())
  {
   if(addrIn->equals(addr))
   {
    return consistTable.value(addr);
   }
  }
  return nullptr;
 }
 ConsistAddrList* ConsistTable::getConsistList()
 {
  return  new ConsistAddrList(consistTable.keys());
 }
 int ConsistTable::size() {return consistTable.keys().count();}
