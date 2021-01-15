#ifndef CREATEBUTTONMODELXML_H
#define CREATEBUTTONMODELXML_H
#include "abstractxmladapter.h"

class CreateButtonModelXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    explicit CreateButtonModelXml(QObject *parent = 0);
    ~CreateButtonModelXml() {}
    CreateButtonModelXml(const CreateButtonModelXml&)
        : AbstractXmlAdapter() {}
    /*public*/ QDomElement store(QObject*  o) ;
    /*public*/ bool loadDeferred();
    /*public*/ bool load(QDomElement shared, QDomElement perNode) throw (JmriConfigureXmlException);
    /*public*/ void load(QDomElement /*element*/, QObject*  /*o*/) throw (Exception);

signals:

public slots:
private:
    Logger* log;
};

#endif // CREATEBUTTONMODELXML_H
