#ifndef ACTIONMEMORYXML_H
#define ACTIONMEMORYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
#include <QObject>

class ActionMemoryXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE ActionMemoryXml(QObject *parent = nullptr);
  ~ActionMemoryXml() {}
  ActionMemoryXml(const ActionMemoryXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/;


 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(ActionMemoryXml)
#endif // ACTIONMEMORYXML_H
