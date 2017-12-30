#ifndef PERFORMFILEMODELXML_H
#define PERFORMFILEMODELXML_H
#include "abstractxmladapter.h"

class Logger;
class PerformFileModelXml : public AbstractXmlAdapter
{
public:
 PerformFileModelXml(QObject* parent = 0);
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred();
 /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriException);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("PerformFileModelXml");

};

#endif // PERFORMFILEMODELXML_H
