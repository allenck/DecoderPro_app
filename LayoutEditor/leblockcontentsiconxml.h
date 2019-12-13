#ifndef LEBLOCKCONTENTSICONXML_H
#define LEBLOCKCONTENTSICONXML_H
#include "blockcontentsiconxml.h"

class LEBlockContentsIconXml : public BlockContentsIconXml
{
 Q_OBJECT
public:
 Q_INVOKABLE/*public*/ LEBlockContentsIconXml(QObject* parent = 0);
 ~LEBlockContentsIconXml() {}
 LEBlockContentsIconXml(const LEBlockContentsIconXml&): BlockContentsIconXml() {}
};
Q_DECLARE_METATYPE(LEBlockContentsIconXml)
#endif // LEBLOCKCONTENTSICONXML_H
