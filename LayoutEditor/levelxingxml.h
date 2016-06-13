#ifndef LEVELXINGXML_H
#define LEVELXINGXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LevelXingXml : public AbstractXmlAdapter
{
 Q_OBJECT
public:
 explicit LevelXingXml(QObject *parent = 0);
 ~LevelXingXml() {}
 LevelXingXml(const LevelXingXml& ) :AbstractXmlAdapter() {}
 /*public*/ QDomElement store(QObject* o);
 /*public*/ bool load(QDomElement element)  throw (Exception);
 /*public*/ void load(QDomElement element, QObject* o) throw(Exception);

signals:

public slots:

};

#endif // LEVELXINGXML_H
