#ifndef ANALOGMANYXML_H
#define ANALOGMANYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogManyXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AnalogManyXml(QObject *parent = nullptr);
  ~AnalogManyXml() {}
  AnalogManyXml(const AnalogManyXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(AnalogManyXml);
#endif // ANALOGMANYXML_H
