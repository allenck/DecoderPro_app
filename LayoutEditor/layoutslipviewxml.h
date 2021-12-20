#ifndef LAYOUTSLIPVIEWXML_H
#define LAYOUTSLIPVIEWXML_H

#include "abstractxmladapter.h"

class LayoutSlipViewXml : public AbstractXmlAdapter
{
 public:
  Q_INVOKABLE LayoutSlipViewXml(QObject *parent = nullptr);
  ~LayoutSlipViewXml() {}
  LayoutSlipViewXml(const LayoutSlipViewXml&) : AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o) override;
  /*public*/ bool load(QDomElement shared, QDomElement perNode) override;
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;

 private:
  static Logger* log;
  QString getElement(QDomElement el, QString child);

 protected:
  /*protected*/ virtual void addClass(QDomElement element);

};
Q_DECLARE_METATYPE(LayoutSlipViewXml);
#endif // LAYOUTSLIPVIEWXML_H
