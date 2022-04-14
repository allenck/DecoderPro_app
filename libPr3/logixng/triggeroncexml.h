#ifndef TRIGGERONCEXML_H
#define TRIGGERONCEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class TriggerOnceXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit TriggerOnceXml(QObject *parent = nullptr);
  ~TriggerOnceXml() {}
  TriggerOnceXml(const TriggerOnceXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(TriggerOnceXml)
#endif // TRIGGERONCEXML_H
