#ifndef TABLEFOREACHXML_H
#define TABLEFOREACHXML_H

#include "abstractnamedbeanmanagerconfigxml.h"

class TableForEachXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit TableForEachXml(QObject *parent = nullptr);
  ~TableForEachXml() {}
  TableForEachXml(const TableForEachXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) /*throws JmriConfigureXmlException*/override;

};
Q_DECLARE_METATYPE(TableForEachXml)
#endif // TABLEFOREACHXML_H
