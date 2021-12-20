#ifndef POSITIONABLEPOINTVIEWXML_H
#define POSITIONABLEPOINTVIEWXML_H

#include "abstractxmladapter.h"

class PositionablePointViewXml : public AbstractXmlAdapter
{
  Q_OBJECT
 public:
  Q_INVOKABLE PositionablePointViewXml(QObject* parent = nullptr);
  ~PositionablePointViewXml() {}
  PositionablePointViewXml(const PositionablePointViewXml&) : AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o) override;
  /*public*/ bool load(/*@Nonnull*/ QDomElement shared, QDomElement perNode) override;
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(PositionablePointViewXml)
#endif // POSITIONABLEPOINTVIEWXML_H
