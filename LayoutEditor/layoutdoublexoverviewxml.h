#ifndef LAYOUTDOUBLEXOVERVIEWXML_H
#define LAYOUTDOUBLEXOVERVIEWXML_H
#include "layoutxoverviewxml.h"
#include <QWidget>

class LayoutDoubleXOverViewXml : public LayoutXOverViewXml
{
  Q_OBJECT
 public:
  LayoutDoubleXOverViewXml(QObject* parent = nullptr);

 protected:
  /*protected*/ void addClass(QDomElement element);

};

#endif // LAYOUTDOUBLEXOVERVIEWXML_H
