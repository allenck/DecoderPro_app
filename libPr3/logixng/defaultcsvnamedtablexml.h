#ifndef DEFAULTCSVNAMEDTABLEXML_H
#define DEFAULTCSVNAMEDTABLEXML_H

#include <abstractnamedbeanmanagerconfigxml.h>

class DefaultCsvNamedTableXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit DefaultCsvNamedTableXml(QObject *parent = nullptr);
  ~DefaultCsvNamedTableXml() {}
  DefaultCsvNamedTableXml(const DefaultCsvNamedTableXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;
};
Q_DECLARE_METATYPE(DefaultCsvNamedTableXml)
#endif // DEFAULTCSVNAMEDTABLEXML_H
