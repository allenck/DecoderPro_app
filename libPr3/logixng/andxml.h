#ifndef ANDXML_H
#define ANDXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AndXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AndXml(QObject *parent = nullptr);
  ~AndXml() {}
  AndXml(const AndXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;;

};
Q_DECLARE_METATYPE(AndXml)
#endif // ANDXML_H
