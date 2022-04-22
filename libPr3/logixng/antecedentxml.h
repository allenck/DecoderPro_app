#ifndef ANTECEDENTXML_H
#define ANTECEDENTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AntecedentXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  Q_INVOKABLE explicit AntecedentXml(QObject *parent = nullptr);
  ~AntecedentXml() {}
  AntecedentXml(const AntecedentXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(AntecedentXml)
#endif // ANTECEDENTXML_H
