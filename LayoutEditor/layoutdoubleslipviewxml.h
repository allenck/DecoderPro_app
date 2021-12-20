#ifndef LAYOUTDOUBLESLIPVIEWXML_H
#define LAYOUTDOUBLESLIPVIEWXML_H

#include "layoutslipviewxml.h"

class LayoutDoubleSlipViewXml : public LayoutSlipViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutDoubleSlipViewXml(QObject *parent = nullptr);
  ~LayoutDoubleSlipViewXml() {}
  LayoutDoubleSlipViewXml(const LayoutDoubleSlipViewXml&): LayoutSlipViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};
Q_DECLARE_METATYPE(LayoutDoubleSlipViewXml)
#endif // LAYOUTDOUBLESLIPVIEWXML_H
