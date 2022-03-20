#ifndef ANTECEDENTXML_H
#define ANTECEDENTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AntecedentXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AntecedentXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};

#endif // ANTECEDENTXML_H
