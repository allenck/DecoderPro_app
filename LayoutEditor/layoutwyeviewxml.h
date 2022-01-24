#ifndef LAYOUTWYEVIEWXML_H
#define LAYOUTWYEVIEWXML_H

#include "layoutturnoutviewxml.h"

class LayoutWyeViewXml : public LayoutTurnoutViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE  LayoutWyeViewXml(QObject *parent = nullptr);
  ~LayoutWyeViewXml() {}
  LayoutWyeViewXml(const LayoutWyeViewXml&): LayoutTurnoutViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};
Q_DECLARE_METATYPE(LayoutWyeViewXml)
#endif // LAYOUTWYEVIEWXML_H
