#ifndef LAYOUTBLOCKMANAGERXML_H
#define LAYOUTBLOCKMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutBlockManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit LayoutBlockManagerXml(QObject *parent = 0);
 ~LayoutBlockManagerXml() {}
 LayoutBlockManagerXml(const LayoutBlockManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject*o);
    /*public*/ void load(QDomElement element, QObject*o) throw (Exception);
    /*public*/ bool load(QDomElement layoutblocks) throw (Exception) ;
    /*public*/ void loadLayoutBlocks(QDomElement layoutblocks);

signals:

public slots:
private:
    /*public*/ void setStoreElementClass(QDomElement layoutblocks);
    Logger* log;
protected:
    /*protected*/ void replaceLayoutBlockManager();

};
Q_DECLARE_METATYPE(LayoutBlockManagerXml)
#endif // LAYOUTBLOCKMANAGERXML_H
