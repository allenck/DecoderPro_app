#ifndef SPROGCONNECTIONTYPELIST_H
#define SPROGCONNECTIONTYPELIST_H
#include <QtCore>

class SprogConnectionTypeList
{
public:
 SprogConnectionTypeList();
 /*public*/ static /*final*/ QString SPROG;// = "SPROG DCC";

 //@Override
 /*public*/ QStringList getAvailableProtocolClasses();
 /*public*/ QStringList getManufacturers();

};

#endif // SPROGCONNECTIONTYPELIST_H
