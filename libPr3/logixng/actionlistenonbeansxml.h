#ifndef ACTIONLISTENONBEANSXML_H
#define ACTIONLISTENONBEANSXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionListenOnBeansXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionListenOnBeansXml(QObject *parent = nullptr);
  ~ActionListenOnBeansXml() {}
  ActionListenOnBeansXml(const ActionListenOnBeansXml&) : AbstractNamedBeanManagerConfigXML() {}
   /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(ActionListenOnBeansXml)
#endif // ACTIONLISTENONBEANSXML_H
