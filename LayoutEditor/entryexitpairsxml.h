#ifndef ENTRYEXITPAIRSXML_H
#define ENTRYEXITPAIRSXML_H
#include "abstractxmladapter.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT EntryExitPairsXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit EntryExitPairsXml(QObject *parent = 0);
 ~EntryExitPairsXml() {}
 EntryExitPairsXml(const EntryExitPairsXml&) : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject* o);
    /*public*/ void setStoreElementClass(QDomElement messages);
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception);
    /*public*/ bool load(QDomElement element) throw (Exception);
    /*public*/ int loadOrder();

signals:

public slots:
 private:
    Logger* log;
};
Q_DECLARE_METATYPE(EntryExitPairsXml)
#endif // ENTRYEXITPAIRSXML_H
