#ifndef NOTXML_H
#define NOTXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class NotXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  explicit NotXml(QObject *parent = nullptr);
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};

#endif // NOTXML_H
