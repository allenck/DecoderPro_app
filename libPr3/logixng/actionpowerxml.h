#ifndef ACTIONPOWERXML_H
#define ACTIONPOWERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionPowerXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionPowerXml(QObject *parent = nullptr);
  ~ActionPowerXml() {}
  ActionPowerXml(const ActionPowerXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override;

};
Q_DECLARE_METATYPE(ActionPowerXml)
#endif // ACTIONPOWERXML_H
