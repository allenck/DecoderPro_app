#ifndef LAYOUTBLOCKMANAGERXML_H
#define LAYOUTBLOCKMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"
#include "manager.h"

class LIBLAYOUTEDITORSHARED_EXPORT LayoutBlockManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit LayoutBlockManagerXml(QObject *parent = 0);
 ~LayoutBlockManagerXml() override {}
 LayoutBlockManagerXml(const LayoutBlockManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject*o) override;
    /*public*/ void load(QDomElement element, QObject*o) throw (Exception) override;
    /*public*/ bool load(QDomElement layoutblocks) throw (Exception)  override;
    /*public*/ void loadLayoutBlocks(QDomElement layoutblocks);

    int loadOrder()const override
    {
     return Manager::LAYOUTBLOCKS;
    }

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
