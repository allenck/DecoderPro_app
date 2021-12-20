#ifndef LAYOUTRHTURNOUTVIEWXML_H
#define LAYOUTRHTURNOUTVIEWXML_H

#include "layoutturnoutviewxml.h"

class LayoutRHTurnoutViewXml : public LayoutTurnoutViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutRHTurnoutViewXml(QObject *parent = nullptr);
  ~LayoutRHTurnoutViewXml() {}
  LayoutRHTurnoutViewXml(const LayoutRHTurnoutViewXml&) : LayoutTurnoutViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element)override;

};
Q_DECLARE_METATYPE(LayoutRHTurnoutViewXml)
#endif // LAYOUTRHTURNOUTVIEWXML_H
