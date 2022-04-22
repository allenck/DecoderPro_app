#ifndef ACTIONPOSITIONABLEXML_H
#define ACTIONPOSITIONABLEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionPositionableXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionPositionableXml(QObject *parent = nullptr);
  ~ActionPositionableXml() {}
  ActionPositionableXml(const ActionPositionableXml&) :AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;    // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionPositionableXml)
#endif // ACTIONPOSITIONABLEXML_H
