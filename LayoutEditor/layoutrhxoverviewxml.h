#ifndef LAYOUTRHXOVERVIEWXML_H
#define LAYOUTRHXOVERVIEWXML_H

#include "layoutxoverviewxml.h"

class LayoutRHXOverViewXml : public LayoutXOverViewXml
{
  Q_OBJECT
 public:
 Q_INVOKABLE LayoutRHXOverViewXml(QObject* parent = nullptr);
  ~LayoutRHXOverViewXml() {}
  LayoutRHXOverViewXml(const LayoutRHXOverViewXml&) : LayoutXOverViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};
Q_DECLARE_METATYPE(LayoutRHXOverViewXml);
#endif // LAYOUTRHXOVERVIEWXML_H
