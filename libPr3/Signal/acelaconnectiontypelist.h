#ifndef ACELACONNECTIONTYPELIST_H
#define ACELACONNECTIONTYPELIST_H

#include <connectiontypelist.h>
#include <QMainWindow>

class AcelaConnectionTypeList : public ConnectionTypeList
{
 public:
  AcelaConnectionTypeList();
  /*public*/ static /*final*/ QString CTI;// = "CTI Electronics";
  /*public*/ QStringList getAvailableProtocolClasses()override;
  /*public*/ QStringList getManufacturers()override;

};

#endif // ACELACONNECTIONTYPELIST_H
