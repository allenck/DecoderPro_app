#ifndef LAYOUTLHTURNOUTVIEWXML_H
#define LAYOUTLHTURNOUTVIEWXML_H

#include "layoutturnoutviewxml.h"
#include <QWidget>

class LayoutLHTurnoutViewXml : public LayoutTurnoutViewXml
{
 public:
  Q_INVOKABLE explicit LayoutLHTurnoutViewXml(QObject *parent = nullptr);
 protected:
  /*protected*/ void addClass(QDomElement element) override;

};

#endif // LAYOUTLHTURNOUTVIEWXML_H
