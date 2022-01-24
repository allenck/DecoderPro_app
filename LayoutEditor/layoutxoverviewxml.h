#ifndef LAYOUTXOVERVIEWXML_H
#define LAYOUTXOVERVIEWXML_H

#include "layoutturnoutviewxml.h"
#include <QWidget>

class LayoutXOverViewXml : public LayoutTurnoutViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutXOverViewXml(QObject *parent = nullptr);
  ~LayoutXOverViewXml() {}
  LayoutXOverViewXml(const LayoutXOverViewXml&) : LayoutTurnoutViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element);

};
Q_DECLARE_METATYPE(LayoutXOverViewXml);
#endif // LAYOUTXOVERVIEWXML_H
