#ifndef PERFORMACTIONMODELXML_H
#define PERFORMACTIONMODELXML_H
#include "abstractxmladapter.h"

class Logger;
class PerformActionModelXml : public AbstractXmlAdapter
{
public:
 PerformActionModelXml(QObject* parent = 0);
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred();
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PerformActionModelXml");

};

#endif // PERFORMACTIONMODELXML_H
