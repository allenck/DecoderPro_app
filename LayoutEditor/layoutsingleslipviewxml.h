#ifndef LAYOUTSINGLESLIPVIEWXML_H
#define LAYOUTSINGLESLIPVIEWXML_H

#include "layoutslipviewxml.h"

class LayoutSingleSlipViewXml : public LayoutSlipViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutSingleSlipViewXml(QObject *parent = nullptr);
  ~LayoutSingleSlipViewXml() {}
  LayoutSingleSlipViewXml(const LayoutSingleSlipViewXml&): LayoutSlipViewXml() {}

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};
Q_DECLARE_METATYPE(LayoutSingleSlipViewXml)
#endif // LAYOUTSINGLESLIPVIEWXML_H
