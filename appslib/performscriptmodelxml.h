#ifndef PERFORMSCRIPTMODELXML_H
#define PERFORMSCRIPTMODELXML_H
#include "abstractxmladapter.h"

class Logger;
class PerformScriptModelXml : public AbstractXmlAdapter
{
public:
 PerformScriptModelXml(QObject* parent = 0);
 ~PerformScriptModelXml() {}
 PerformScriptModelXml(const PerformScriptModelXml&) : AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred();
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PerformScriptModelXml");

};
Q_DECLARE_METATYPE(PerformScriptModelXml)
#endif // PERFORMSCRIPTMODELXML_H
