#ifndef NOTXML_H
#define NOTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class NotXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit NotXml(QObject *parent = nullptr);
  ~NotXml() {}
  NotXml(const NotXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(NotXml)
#endif // NOTXML_H
