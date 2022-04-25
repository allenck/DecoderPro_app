#ifndef EXPRESSIONPOWERXML_H
#define EXPRESSIONPOWERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExpressionPowerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ExpressionPowerXml(QObject *parent = nullptr);
  ~ExpressionPowerXml() {}
  ExpressionPowerXml(const ExpressionPowerXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */override;

};
Q_DECLARE_METATYPE(ExpressionPowerXml)
#endif // EXPRESSIONPOWERXML_H
