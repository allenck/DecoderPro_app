#ifndef LAYOUTSINGLESLIPVIEWXML_H
#define LAYOUTSINGLESLIPVIEWXML_H

#include "layoutslipviewxml.h"

class LayoutSingleSlipViewXml : public LayoutSlipViewXml
{
 public:
  Q_INVOKABLE explicit LayoutSingleSlipViewXml(QObject *parent = nullptr);

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};

#endif // LAYOUTSINGLESLIPVIEWXML_H
