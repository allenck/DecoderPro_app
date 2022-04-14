#ifndef EXPRESSIONSENSORXML_H
#define EXPRESSIONSENSORXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionSensorXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ExpressionSensorXml(QObject *parent = nullptr);
  ~ExpressionSensorXml() {}
  ExpressionSensorXml(const ExpressionSensorXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */override;

};
Q_DECLARE_METATYPE(ExpressionSensorXml)
#endif // EXPRESSIONSENSORXML_H
