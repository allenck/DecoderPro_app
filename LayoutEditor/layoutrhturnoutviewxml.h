#ifndef LAYOUTRHTURNOUTVIEWXML_H
#define LAYOUTRHTURNOUTVIEWXML_H

#include "layoutturnoutviewxml.h"

class LayoutRHTurnoutViewXml : public LayoutTurnoutViewXml
{
 public:
  Q_INVOKABLE explicit LayoutRHTurnoutViewXml(QObject *parent = nullptr);
 protected:
  /*protected*/ void addClass(QDomElement element)override;

};

#endif // LAYOUTRHTURNOUTVIEWXML_H
