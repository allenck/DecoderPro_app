#ifndef TURNOUTOPERATIONMANAGERXML_H
#define TURNOUTOPERATIONMANAGERXML_H
#include <QDomElement>

#include <QObject>
#include "turnoutoperationmanager.h"
#include "liblayouteditor_global.h"
#include "abstractxmladapter.h"

class LIBLAYOUTEDITORSHARED_EXPORT TurnoutOperationManagerXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TurnoutOperationManagerXml(QObject *parent = 0);
    ~TurnoutOperationManagerXml() {}
    TurnoutOperationManagerXml(const TurnoutOperationManagerXml&) : AbstractXmlAdapter() {}
    /*public*/ void setStoreElementClass(QDomElement elem);
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception) override {}
    /*public*/ bool load(QDomElement sharedOperations, QDomElement perNodeOperations) throw (JmriConfigureXmlException) override;
    /*public*/ QDomElement store(QObject* o) override;

signals:
    
public slots:
    
private:
 static Logger* log;
};
Q_DECLARE_METATYPE(TurnoutOperationManagerXml)
#endif // TURNOUTOPERATIONMANAGERXML_H
