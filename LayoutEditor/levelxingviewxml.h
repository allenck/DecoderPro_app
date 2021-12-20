#ifndef LEVELXINGVIEWXML_H
#define LEVELXINGVIEWXML_H

#include "abstractxmladapter.h"
#include "levelxingview.h"
#include "levelxing.h"

class LevelXingViewXml : public AbstractXmlAdapter
{
  Q_OBJECT
 public:
  Q_INVOKABLE LevelXingViewXml(QObject* parent = nullptr);
  ~LevelXingViewXml() {}
  LevelXingViewXml(const LevelXingViewXml&) : AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o)override;
  /*public*/ bool load(QDomElement shared, QDomElement perNode)override;
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception)override;

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(LevelXingViewXml)
#endif // LEVELXINGVIEWXML_H
