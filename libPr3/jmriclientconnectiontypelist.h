#ifndef JMRICLIENTCONNECTIONTYPELIST_H
#define JMRICLIENTCONNECTIONTYPELIST_H
#include "connectiontypelist.h"

class JMRIClientConnectionTypeList : public ConnectionTypeList
{
public:
 JMRIClientConnectionTypeList();
 /*public*/ static /*final*/ QString JMRI;// = "JMRI (Network)";
 /*public*/ QStringList getAvailableProtocolClasses();
 /*public*/ QStringList getManufacturers();

};

#endif // JMRICLIENTCONNECTIONTYPELIST_H
