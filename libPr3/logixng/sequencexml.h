#ifndef SEQUENCEXML_H
#define SEQUENCEXML_H

#include "abstractnamedbeanmanagerconfigxml.h"

class SequenceXml : public AbstractNamedBeanManagerConfigXML
{
  Q_OBJECT
 public:
  SequenceXml(QObject *parent = nullptr);
  ~SequenceXml() {}
  SequenceXml(const SequenceXml&) : AbstractNamedBeanManagerConfigXML() {}
  /*public*/  QDomElement store(QObject* o) override;
  /*public*/  bool load(QDomElement shared, QDomElement perNode) override;

};
Q_DECLARE_METATYPE(SequenceXml)
#endif // SEQUENCEXML_H
