#ifndef ANDXML_H
#define ANDXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class AndXml : public AbstractNamedBeanManagerConfigXML
{
 public:
  explicit AndXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;;

};

#endif // ANDXML_H
