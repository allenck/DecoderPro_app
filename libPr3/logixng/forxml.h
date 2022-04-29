#ifndef FORXML_H
#define FORXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class ForXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit ForXml(QObject *parent = nullptr);
  ~ForXml() {}
  ForXml(const ForXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(ForXml)
#endif // FORXML_H
