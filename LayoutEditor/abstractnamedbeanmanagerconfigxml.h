#ifndef ABSTRACTNAMEDBEANMANAGERCONFIGXML_H
#define ABSTRACTNAMEDBEANMANAGERCONFIGXML_H
#include "abstractxmladapter.h"
#include "abstractnamedbean.h"
#include "liblayouteditor_global.h"


class Manager;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractNamedBeanManagerConfigXML : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit AbstractNamedBeanManagerConfigXML(QObject *parent = 0);
    ~AbstractNamedBeanManagerConfigXML() override;
    void checkNameNormalization(/*@Nonnull*/ QString rawSystemName, QString rawUserName, /*@Nonnull*/ Manager* manager);

signals:

public slots:
private:
 Logger* log;

protected:
 /*protected*/ void storeCommon(NamedBean *t, QDomElement elem);
 /*protected*/ void loadCommon(NamedBean *t, QDomElement elem);
 void storeComment(NamedBean* t, QDomElement elem);
 void storeUserName(NamedBean* t, QDomElement elem);
 /*protected*/ QString getUserName(QDomNodeList beanList, int i);
 /*protected*/ QString getUserName(QDomElement elem);
 /*protected*/ QString getSystemName(QDomElement elem) ;
 void loadComment(NamedBean* t, QDomNodeList beanList, int i);
 void loadComment(NamedBean* t, QDomElement elem);
 QString getAttributeString(QDomElement elem, QString name);
 bool getAttributeBool(QDomElement elem, QString name, bool def);
 void storeProperties(NamedBean* t, QDomElement elem);
 void loadProperties(NamedBean* t, QDomElement elem);

};

#endif // ABSTRACTNAMEDBEANMANAGERCONFIGXML_H
