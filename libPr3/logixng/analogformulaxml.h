#ifndef ANALOGFORMULAXML_H
#define ANALOGFORMULAXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AnalogFormulaXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit AnalogFormulaXml(QObject *parent = nullptr);
  ~AnalogFormulaXml() {}
  AnalogFormulaXml(const AnalogFormulaXml&)  : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;     // Test class that inherits this class throws exception

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(AnalogFormulaXml)
#endif // ANALOGFORMULAXML_H
