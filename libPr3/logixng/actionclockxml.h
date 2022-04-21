#ifndef ACTIONCLOCKXML_H
#define ACTIONCLOCKXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionClockXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ActionClockXml(QObject *parent = nullptr);
  ~ActionClockXml() {}
  ActionClockXml(const ActionClockXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o);
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(ActionClockXml)
#endif // ACTIONCLOCKXML_H
