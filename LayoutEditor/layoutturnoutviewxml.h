#ifndef LAYOUTTURNOUTVIEWXML_H
#define LAYOUTTURNOUTVIEWXML_H

#include "abstractxmladapter.h"

class LayoutTurnoutViewXml : public AbstractXmlAdapter
{
 public:
  Q_INVOKABLE LayoutTurnoutViewXml(QObject* parent = nullptr);
  ~LayoutTurnoutViewXml() {}
  LayoutTurnoutViewXml(const LayoutTurnoutViewXml&) : AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o);
  /*public*/ bool load(QDomElement shared, QDomElement perNode) override;
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

   private:
  static Logger* log;
  QString getElement(QDomElement el, QString child);

 protected:
  virtual /*protected*/ void addClass(QDomElement element);

};
Q_DECLARE_METATYPE(LayoutTurnoutViewXml)
#endif // LAYOUTTURNOUTVIEWXML_H
