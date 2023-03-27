#ifndef ACTIONREPORTERXML_H
#define ACTIONREPORTERXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionReporterXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  ActionReporterXml(QObject* parent = nullptr);
  ~ActionReporterXml() {}
  ActionReporterXml(const ActionReporterXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/ override  ;  // Test class that inherits this class throws exception

};
Q_DECLARE_METATYPE(ActionReporterXml)
#endif // ACTIONREPORTERXML_H
