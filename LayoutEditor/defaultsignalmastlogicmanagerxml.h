#ifndef DEFAULTSIGNALMASTLOGICMANAGERXML_H
#define DEFAULTSIGNALMASTLOGICMANAGERXML_H
#include "../LayoutEditor/abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class NamedBeanHandleManager;

class LIBLAYOUTEDITORSHARED_EXPORT DefaultSignalMastLogicManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultSignalMastLogicManagerXml(QObject *parent = 0);

    /*public*/ QDomElement store(QObject* o) override;
 ~DefaultSignalMastLogicManagerXml()  override{}
 DefaultSignalMastLogicManagerXml(const DefaultSignalMastLogicManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ void setStoreElementClass(QDomElement signalMastLogic) ;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override;
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException) override;
    /*public*/ bool loadSignalMastLogic(QDomElement signalMastLogic);
    /*public*/ int loadOrder() const override;

signals:

public slots:
private:
    Logger* log;
    /*private*/ bool debug;
    /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class);

};
Q_DECLARE_METATYPE(DefaultSignalMastLogicManagerXml)
#endif // DEFAULTSIGNALMASTLOGICMANAGERXML_H
