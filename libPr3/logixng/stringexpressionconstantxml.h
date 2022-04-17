#ifndef STRINGEXPRESSIONCONSTANTXML_H
#define STRINGEXPRESSIONCONSTANTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringExpressionConstantXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringExpressionConstantXml(QObject *parent = nullptr);
  ~StringExpressionConstantXml() {}
  StringExpressionConstantXml(const StringExpressionConstantXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;     // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(StringExpressionConstantXml)
#endif // STRINGEXPRESSIONCONSTANTXML_H
