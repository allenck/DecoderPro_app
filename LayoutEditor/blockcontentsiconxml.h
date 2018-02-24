#ifndef BLOCKCONTENTSICONXML_H
#define BLOCKCONTENTSICONXML_H
#include "positionablelabelxml.h"

class BlockContentsIconXml : public PositionableLabelXml
{
 Q_OBJECT
public:
 BlockContentsIconXml(QObject* parent = 0);
 ~BlockContentsIconXml() {}
 BlockContentsIconXml(const BlockContentsIconXml&) : PositionableLabelXml() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ void load(QDomElement element, QObject* o) throw (Exception);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("BlockContentsIconXml");
};
Q_DECLARE_METATYPE(BlockContentsIconXml)
#endif // BLOCKCONTENTSICONXML_H
