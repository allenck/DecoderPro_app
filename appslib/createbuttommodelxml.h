#ifndef CREATEBUTTOMMODELXML_H
#define CREATEBUTTOMMODELXML_H
#include "abstractxmladapter.h"

class CreateButtonModelXml  : public AbstractXmlAdapter
{
public:
 CreateButtonModelXml (QObject* parent = 0);
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool loadDeferred() ;
 /*public*/ bool load(QDomElement shared, QDomElement perNode);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CreateButtonModelXml");

};

#endif // CREATEBUTTOMMODELXML_H
