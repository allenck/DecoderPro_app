#ifndef ACTIONSENSORXML_H
#define ACTIONSENSORXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionSensorXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionSensorXml(QObject *parent = nullptr);
 ~ActionSensorXml() {}
  ActionSensorXml(const ActionSensorXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException */override;

};
Q_DECLARE_METATYPE(ActionSensorXml)
#endif // ACTIONSENSORXML_H
