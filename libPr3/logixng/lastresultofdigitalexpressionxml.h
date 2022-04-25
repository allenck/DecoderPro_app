#ifndef LASTRESULTOFDIGITALEXPRESSIONXML_H
#define LASTRESULTOFDIGITALEXPRESSIONXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class LastResultOfDigitalExpressionXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit LastResultOfDigitalExpressionXml(QObject *parent = nullptr);
  ~LastResultOfDigitalExpressionXml() {}
  LastResultOfDigitalExpressionXml(const LastResultOfDigitalExpressionXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement  store(QObject* o)override;
  /*public*/  bool load(QDomElement  shared, QDomElement  perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(LastResultOfDigitalExpressionXml)
#endif // LASTRESULTOFDIGITALEXPRESSIONXML_H
