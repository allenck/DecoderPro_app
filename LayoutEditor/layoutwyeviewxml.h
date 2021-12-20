#ifndef LAYOUTWYEVIEWXML_H
#define LAYOUTWYEVIEWXML_H

#include "layoutturnoutviewxml.h"

class LayoutWyeViewXml : public LayoutTurnoutViewXml
{
 public:
  Q_INVOKABLE explicit LayoutWyeViewXml(QObject *parent = nullptr);

 protected:
  /*protected*/ void addClass(QDomElement element) override;

};

#endif // LAYOUTWYEVIEWXML_H
