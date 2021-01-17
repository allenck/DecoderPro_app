#ifndef METERFRAMEMANAGERXML_H
#define METERFRAMEMANAGERXML_H
#include "abstractxmladapter.h"

class MeterFrame;
class MeterFrameManagerXml : public AbstractXmlAdapter
{
  Q_OBJECT
 public:
  Q_INVOKABLE MeterFrameManagerXml(QObject* parent=nullptr);
  ~MeterFrameManagerXml() {}
  MeterFrameManagerXml(const MeterFrameManagerXml&) : AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o);
  /*public*/ QDomElement storeMeterFrame(MeterFrame* frame);
  /*public*/ void setStoreElementClass(QDomElement meterFrames);
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception)  override {}
  /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);

 private:
  static Logger* log;
};
Q_DECLARE_METATYPE(MeterFrameManagerXml)
#endif // METERFRAMEMANAGERXML_H
