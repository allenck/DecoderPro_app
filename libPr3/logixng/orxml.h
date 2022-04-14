#ifndef ORXML_H
#define ORXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class OrXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit OrXml(QObject *parent = nullptr);
  ~OrXml() {}
  OrXml(const OrXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

};
Q_DECLARE_METATYPE(OrXml)
#endif // ORXML_H
