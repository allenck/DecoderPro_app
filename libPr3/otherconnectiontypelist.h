#ifndef OTHERCONNECTIONTYPELIST_H
#define OTHERCONNECTIONTYPELIST_H

#include "connectiontypelist.h"

class OtherConnectionTypeList : public ConnectionTypeList
{
  Q_OBJECT
 public:
  OtherConnectionTypeList(QObject* parent = nullptr);
  /*public*/ static /*final*/ QString OTHER;// = "Others"; // NOI18N
  /*public*/ QStringList getAvailableProtocolClasses() override;
  /*public*/ QStringList getManufacturers() override;
};

#endif // OTHERCONNECTIONTYPELIST_H
