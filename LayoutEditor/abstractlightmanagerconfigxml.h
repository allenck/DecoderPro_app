#ifndef ABSTRACTLIGHTMANAGERCONFIGXML_H
#define ABSTRACTLIGHTMANAGERCONFIGXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT AbstractLightManagerConfigXML : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    explicit AbstractLightManagerConfigXML(QObject *parent = 0);
    ~AbstractLightManagerConfigXML() override;
    /*public*/ QDomElement store(QObject* o)  override;
    virtual /*abstract*/ /*public*/ void setStoreElementClass(QDomElement lights) ;
    /*abstract*/ /*public*/ bool load(QDomElement lights) throw (Exception) override ;
    /*public*/ bool loadLights(QDomElement lights);
    /*public*/ int loadOrder() const override;
    void setDoc(QDomDocument doc);
signals:

public slots:
private:
 Logger* log;
 QDomDocument doc;
};

#endif // ABSTRACTLIGHTMANAGERCONFIGXML_H
