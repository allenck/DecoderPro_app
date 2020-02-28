#ifndef POSITIONABLELABELXML_H
#define POSITIONABLELABELXML_H
#include "abstractxmladapter.h"
#include "positionable.h"
#include "locoicon.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT PositionableLabelXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PositionableLabelXml(QObject *parent = 0);
    /*public*/ QDomElement store(QObject* o);
 ~PositionableLabelXml() override {}
 PositionableLabelXml(const PositionableLabelXml&) : AbstractXmlAdapter() {}
    /*public*/ bool load(QDomElement element) throw (Exception) override;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ void storeCommonAttributes(Positionable* p, QDomElement element);
    /*public*/ QDomElement storeIcon(QString elemName, NamedIcon* icon);
    /*public*/ void loadCommonAttributes(Positionable* l, int defaultLevel, QDomElement element);
    /*public*/ NamedIcon* loadIcon(PositionableLabel* l, QString attrName, QDomElement element,
                                        QString name, Editor* ed);
    virtual void setDoc(QDomDocument);
    PositionableLabel*  getIcon();
signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ void storeTextInfo(Positionable* p, QDomElement element);
 /*protected*/ void loadTextInfo(Positionable* l, QDomElement element);
 /*protected*/ NamedIcon* getNamedIcon(QString childName, QDomElement element, QString name, Editor* ed);
PositionableLabel* l;
};
Q_DECLARE_METATYPE(PositionableLabelXml)
#endif // POSITIONABLELABELXML_H
