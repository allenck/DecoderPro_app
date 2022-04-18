#ifndef HOLDXML_H
#define HOLDXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class HoldXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit HoldXml(QObject *parent = nullptr);
  ~HoldXml() {}
  HoldXml(const HoldXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(HoldXml)
#endif // HOLDXML_H
