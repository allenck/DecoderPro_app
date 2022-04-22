#ifndef ACTIONSIGNALHEADXML_H
#define ACTIONSIGNALHEADXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit ActionSignalHeadXml(QObject *parent = nullptr);
  ~ActionSignalHeadXml() {}
  ActionSignalHeadXml(const ActionSignalHeadXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(ActionSignalHeadXml)
#endif // ACTIONSIGNALHEADXML_H
