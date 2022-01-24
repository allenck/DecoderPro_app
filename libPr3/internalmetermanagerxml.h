#ifndef INTERNALMETERMANAGERXML_H
#define INTERNALMETERMANAGERXML_H
#include "abstractmetermanagerxml.h"

class InternalMeterManagerXml : public AbstractMeterManagerXml
{
 public:
  Q_INVOKABLE InternalMeterManagerXml(QObject* parent = nullptr);
  ~InternalMeterManagerXml() {}
  InternalMeterManagerXml(const InternalMeterManagerXml&) : AbstractMeterManagerXml() {}
  /*public*/ void setStoreElementClass(QDomElement meters);
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception)  override {}
};
Q_DECLARE_METATYPE(InternalMeterManagerXml)
#endif // INTERNALMETERMANAGERXML_H
