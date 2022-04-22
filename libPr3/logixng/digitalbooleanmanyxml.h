#ifndef DIGITALBOOLEANMANYXML_H
#define DIGITALBOOLEANMANYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DigitalBooleanManyXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalBooleanManyXml(QObject *parent = nullptr);
  ~DigitalBooleanManyXml() {}
  DigitalBooleanManyXml(const DigitalBooleanManyXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;


};
Q_DECLARE_METATYPE(DigitalBooleanManyXml)
#endif // DIGITALBOOLEANMANYXML_H
