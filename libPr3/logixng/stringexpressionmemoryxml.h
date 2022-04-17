#ifndef STRINGEXPRESSIONMEMORYXML_H
#define STRINGEXPRESSIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringExpressionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringExpressionMemoryXml(QObject *parent = nullptr);
  ~StringExpressionMemoryXml() {}
  StringExpressionMemoryXml(const StringExpressionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o);
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;   // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(StringExpressionMemoryXml)
#endif // STRINGEXPRESSIONMEMORYXML_H
