#ifndef LAYOUTLHXOVERVIEWXML_H
#define LAYOUTLHXOVERVIEWXML_H

#include "layoutxoverviewxml.h"

class LayoutLHXOverViewXml : public LayoutXOverViewXml
{
  Q_OBJECT
 public:
 Q_INVOKABLE LayoutLHXOverViewXml(QObject* parent = nullptr);
  ~LayoutLHXOverViewXml() {}
  LayoutLHXOverViewXml(const LayoutLHXOverViewXml&) : LayoutXOverViewXml() {}
 protected:
  /*protected*/ void addClass(QDomElement element)override;

};
Q_DECLARE_METATYPE(LayoutLHXOverViewXml)
#endif // LAYOUTLHXOVERVIEWXML_H
