#ifndef LAYOUTLHTURNOUTVIEWXML_H
#define LAYOUTLHTURNOUTVIEWXML_H

#include "layoutturnoutviewxml.h"
#include <QWidget>

class LayoutLHTurnoutViewXml : public LayoutTurnoutViewXml
{
  Q_OBJECT
 public:
  Q_INVOKABLE LayoutLHTurnoutViewXml(QObject *parent = nullptr);
  ~LayoutLHTurnoutViewXml() {}
  LayoutLHTurnoutViewXml(const LayoutLHTurnoutViewXml&) : LayoutTurnoutViewXml() {}
 protected:
  /*protected*/ void addClass(QDomElement element) override;

};
Q_DECLARE_METATYPE(LayoutLHTurnoutViewXml)
#endif // LAYOUTLHTURNOUTVIEWXML_H
