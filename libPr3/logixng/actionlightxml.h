#ifndef ACTIONLIGHTXML_H
#define ACTIONLIGHTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionLightXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ActionLightXml(QObject *parent = nullptr);
  ~ActionLightXml() {}
  ActionLightXml(const ActionLightXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ActionLightXml)
#endif // ACTIONLIGHTXML_H
