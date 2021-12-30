#ifndef ACELASIGNALHEADXML_H
#define ACELASIGNALHEADXML_H

#include <abstractnamedbeanmanagerconfigxml.h>
#include "acelasystemconnectionmemo.h"

class AcelaSignalHeadXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE explicit AcelaSignalHeadXml(QObject *parent = nullptr);
  ~AcelaSignalHeadXml() {}
  AcelaSignalHeadXml(const AcelaSignalHeadXml&): AbstractNamedBeanManagerConfigXML(){}
  /*public*/  QDomElement store(QObject* o)override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

 private:
  AcelaSystemConnectionMemo* _memo = nullptr;

};
Q_DECLARE_METATYPE(AcelaSignalHeadXml)
#endif // ACELASIGNALHEADXML_H
