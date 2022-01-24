#ifndef TRACKSEGMENTVIEWXML_H
#define TRACKSEGMENTVIEWXML_H

#include "abstractxmladapter.h"
#include "hitpointtype.h"

class EnumIO;
class TrackSegmentViewXml : public AbstractXmlAdapter
{
  Q_OBJECT
 public:
  Q_INVOKABLE TrackSegmentViewXml(QObject* parent = nullptr);
  ~TrackSegmentViewXml() {}
  TrackSegmentViewXml(const TrackSegmentViewXml&): AbstractXmlAdapter() {}
  /*public*/ QDomElement store(QObject* o) override;
  /*public*/ bool load(QDomElement shared, QDomElement perNode) override;
  /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

 private:
  static Logger* log;
  //static final EnumIO<HitPointType> htpMap = new EnumIoNamesNumbers<>(HitPointType.class);

};
Q_DECLARE_METATYPE(TrackSegmentViewXml);
#endif // TRACKSEGMENTVIEWXML_H
