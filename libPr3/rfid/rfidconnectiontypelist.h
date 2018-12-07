#ifndef RFIDCONNECTIONTYPELIST_H
#define RFIDCONNECTIONTYPELIST_H
#include "connectiontypelist.h"

class RfidConnectionTypeList : public ConnectionTypeList
{
public:
 RfidConnectionTypeList(QObject *parent = nullptr);
 /*public*/ static /*final*/ QString RFID;// = "RFID";
 /*public*/ QStringList getAvailableProtocolClasses();
 /*public*/ QStringList getManufacturers();
};

#endif // RFIDCONNECTIONTYPELIST_H
