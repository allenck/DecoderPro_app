#ifndef ACTIONLOCALVARIABLEXML_H
#define ACTIONLOCALVARIABLEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ActionLocalVariableXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ActionLocalVariableXml(QObject *parent = nullptr);
  ~ActionLocalVariableXml() {}
  ActionLocalVariableXml(const ActionLocalVariableXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o);
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(ActionLocalVariableXml)
#endif // ACTIONLOCALVARIABLEXML_H
