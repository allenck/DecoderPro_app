#ifndef SECTIONMANAGERXML_H
#define SECTIONMANAGERXML_H
#include "abstractnamedbeanmanagerconfigxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT SectionManagerXml : public AbstractNamedBeanManagerConfigXML
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SectionManagerXml(QObject *parent = 0);
    ~SectionManagerXml()  override{}
    SectionManagerXml(const SectionManagerXml&) : AbstractNamedBeanManagerConfigXML() {}
    /*public*/ QDomElement store(QObject* o) override;
    /*public*/ void setStoreElementClass(QDomElement sections);
    /*public*/ void load(QDomElement element, QObject* o)  throw (Exception) override;
    /*public*/ bool load(QDomElement sharedSections, QDomElement perNodeSections) throw (Exception) override;
    /*public*/ void loadSections(QDomElement sharedSections, QDomElement perNodeSections);
    /*public*/ int loadOrder() const override;

signals:

public slots:
private:
    static Logger* log;

};
Q_DECLARE_METATYPE(SectionManagerXml)
#endif // SECTIONMANAGERXML_H
