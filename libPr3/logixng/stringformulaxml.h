#ifndef STRINGFORMULAXML_H
#define STRINGFORMULAXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringFormulaXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringFormulaXml(QObject *parent = nullptr);
  ~StringFormulaXml() {}
  StringFormulaXml(const StringFormulaXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(StringFormulaXml)
#endif // STRINGFORMULAXML_H
