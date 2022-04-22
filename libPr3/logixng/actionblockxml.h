#ifndef ACTIONBLOCKXML_H
#define ACTIONBLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionBlockXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionBlockXml(QObject *parent = nullptr);
 ~ActionBlockXml() {}
  ActionBlockXml(const ActionBlockXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;     // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionBlockXml)
#endif // ACTIONBLOCKXML_H
