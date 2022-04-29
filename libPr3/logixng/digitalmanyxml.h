#ifndef DIGITALMANYXML_H
#define DIGITALMANYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DigitalManyXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalManyXml(QObject *parent = nullptr);
  ~DigitalManyXml() {}
  DigitalManyXml(const DigitalManyXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(DigitalManyXml)
#endif // DIGITALMANYXML_H
