#ifndef TRUEXML_H
#define TRUEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class TrueXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit TrueXml(QObject *parent = nullptr);
  ~TrueXml() {}
  TrueXml(const TrueXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o);
  /*public*/  bool load(QDomElement shared, QDomElement perNode);

};
Q_DECLARE_METATYPE(TrueXml);
#endif // TRUEXML_H
