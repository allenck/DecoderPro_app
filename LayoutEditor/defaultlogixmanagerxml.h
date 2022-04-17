#ifndef DEFAULTLOGIXMANAGERXML_H
#define DEFAULTLOGIXMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT DefaultLogixManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultLogixManagerXml(QObject *parent = 0);
    ~DefaultLogixManagerXml() {}
    DefaultLogixManagerXml(const DefaultLogixManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ void setStoreElementClass(QDomElement logixs);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ bool load(QDomElement logixs, QDomElement perNodeLogix) throw (Exception) override;
    /*public*/ void loadLogixs(QDomElement logixs);
    /*public*/ int loadOrder() const override;

signals:

public slots:
private:
    Logger* log;
protected:
    /*protected*/ void replaceLogixManager();

};
Q_DECLARE_METATYPE(DefaultLogixManagerXml)
#endif // DEFAULTLOGIXMANAGERXML_H
