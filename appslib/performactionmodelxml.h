#ifndef PERFORMACTIONMODELXML_H
#define PERFORMACTIONMODELXML_H
#include "abstractxmladapter.h"

class Logger;
class PerformActionModelXml : public AbstractXmlAdapter
{
public:
 PerformActionModelXml(QObject* parent = 0);
 ~PerformActionModelXml() {}
 PerformActionModelXml(const PerformActionModelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred();
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
 /*public*/ void setTitle(QString);
private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PerformActionModelXml");

};
Q_DECLARE_METATYPE(PerformActionModelXml)
#endif // PERFORMACTIONMODELXML_H
