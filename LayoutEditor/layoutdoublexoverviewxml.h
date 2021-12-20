#ifndef LAYOUTDOUBLEXOVERVIEWXML_H
#define LAYOUTDOUBLEXOVERVIEWXML_H
#include "layoutxoverviewxml.h"
#include <QWidget>

class LayoutDoubleXOverViewXml : public LayoutXOverViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutDoubleXOverViewXml(QObject* parent = nullptr);
  ~LayoutDoubleXOverViewXml() {}
  LayoutDoubleXOverViewXml(const LayoutDoubleXOverViewXml&): LayoutXOverViewXml() {}
 protected:
  /*protected*/ void addClass(QDomElement element);

};
Q_DECLARE_METATYPE(LayoutDoubleXOverViewXml)
#endif // LAYOUTDOUBLEXOVERVIEWXML_H
