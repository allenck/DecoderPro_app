#ifndef DIGITALBOOLEANONCHANGEXML_H
#define DIGITALBOOLEANONCHANGEXML_H

#include "abstractnamedbeanmanagerconfigxml.h"
#include <QObject>

class DigitalBooleanOnChangeXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  Q_INVOKABLE DigitalBooleanOnChangeXml(QObject* parent = nullptr);
  ~DigitalBooleanOnChangeXml() {}
  DigitalBooleanOnChangeXml(const DigitalBooleanOnChangeXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode)override;

};
Q_DECLARE_METATYPE(DigitalBooleanOnChangeXml)
#endif // DIGITALBOOLEANONCHANGEXML_H
