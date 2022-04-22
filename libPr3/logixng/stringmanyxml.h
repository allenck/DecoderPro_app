#ifndef STRINGMANYXML_H
#define STRINGMANYXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class StringManyXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit StringManyXml(QObject *parent = nullptr);
  ~StringManyXml() {}
  StringManyXml(const StringManyXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(StringManyXml)
#endif // STRINGMANYXML_H
