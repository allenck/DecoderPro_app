#ifndef REPORTERVARIANT_H
#define REPORTERVARIANT_H
#include "transpondingtag.h"
#include "vptr.h"

class ReporterVariant : public QVariant
{

public:
 ReporterVariant(QVariant v)
 {
  this->v = v;
  setValue(v);
 }

 QString toString()
 {
  if(v.type() == QMetaType::VoidStar)
  {
   QObject* obj = VPtr<QObject>::asPtr(v);
   if(obj == nullptr)
    return "";
   if(qobject_cast<TranspondingTag*>(obj)!= nullptr)
   {
    return ((TranspondingTag*)obj)->toString();
   }
   throw new IllegalArgumentException(QString("no cast for ReporterVariant to %1").arg(obj->metaObject()->className()));
  }
  return v.toString();
 }
private:
 QVariant v;
};
#endif // REPORTERVARIANT_H
