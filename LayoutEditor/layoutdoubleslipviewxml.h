#ifndef LAYOUTDOUBLESLIPVIEWXML_H
#define LAYOUTDOUBLESLIPVIEWXML_H

#include "layoutslipviewxml.h"

class LayoutDoubleSlipViewXml : public LayoutSlipViewXml
{
 public:
  Q_INVOKABLE explicit LayoutDoubleSlipViewXml(QObject *parent = nullptr);

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};

#endif // LAYOUTDOUBLESLIPVIEWXML_H
