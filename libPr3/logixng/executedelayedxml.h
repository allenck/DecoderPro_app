#ifndef EXECUTEDELAYEDXML_H
#define EXECUTEDELAYEDXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ExecuteDelayedXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE ExecuteDelayedXml(QObject* parent = nullptr);
  ~ExecuteDelayedXml(){}
  ExecuteDelayedXml(const ExecuteDelayedXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

};

Q_DECLARE_METATYPE(ExecuteDelayedXml)
#endif // EXECUTEDELAYEDXML_H
