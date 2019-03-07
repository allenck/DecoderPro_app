#ifndef TRACKSEGMENTXML_H
#define TRACKSEGMENTXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT TrackSegmentXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit TrackSegmentXml(QObject *parent = 0);
 ~TrackSegmentXml() {}
 TrackSegmentXml(const TrackSegmentXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element, QDomElement) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

signals:

public slots:
private:
 static Logger* log;

};
Q_DECLARE_METATYPE(TrackSegmentXml)
#endif // TRACKSEGMENTXML_H
