#ifndef IFTHENELSEXML_H
#define IFTHENELSEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class IfThenElseXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit IfThenElseXml(QObject *parent = nullptr);
  ~IfThenElseXml() {}
  IfThenElseXml(const IfThenElseXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

};
Q_DECLARE_METATYPE(IfThenElseXml)
#endif // IFTHENELSEXML_H
