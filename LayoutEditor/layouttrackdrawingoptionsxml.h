#ifndef LAYOUTTRACKDRAWINGOPTIONSXML_H
#define LAYOUTTRACKDRAWINGOPTIONSXML_H
#include "abstractxmladapter.h"

class LayoutTrackDrawingOptionsXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 /*public*/ LayoutTrackDrawingOptionsXml(QObject* parent = nullptr);
 ~LayoutTrackDrawingOptionsXml() {}
 LayoutTrackDrawingOptionsXml(const LayoutTrackDrawingOptionsXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement shared, QDomElement perNode);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("LayoutTrackDrawingOptionsXml");
 /*private*/ QColor getElementColor(/*@Nonnull*/ QDomElement el, /*@Nonnull*/ QString child, /*@Nullable */QColor defVal);
 int getElementInt(QDomElement el, QString child, int defVal);

};
Q_DECLARE_METATYPE(LayoutTrackDrawingOptionsXml)
#endif // LAYOUTTRACKDRAWINGOPTIONSXML_H
