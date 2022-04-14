#ifndef FALSEXML_H
#define FALSEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class FalseXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit FalseXml(QObject *parent = nullptr);
 ~FalseXml() {}
  FalseXml(const FalseXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(FalseXml)
#endif // FALSEXML_H
