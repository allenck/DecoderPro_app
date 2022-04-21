#ifndef DIGITALFORMULAXML_H
#define DIGITALFORMULAXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DigitalFormulaXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DigitalFormulaXml(QObject *parent = nullptr);
  ~DigitalFormulaXml() {}
  DigitalFormulaXml(const DigitalFormulaXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;   // Test class that inherits this class throws exception

 private:
  static Logger* log;

};
Q_DECLARE_METATYPE(DigitalFormulaXml)
#endif // DIGITALFORMULAXML_H
