#ifndef TURNOUTOPERATIONMANAGERXML_H
#define TURNOUTOPERATIONMANAGERXML_H
#include <QDomElement>

#include <QObject>
#include "turnoutoperationmanager.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT TurnoutOperationManagerXml : public QObject
{
    Q_OBJECT
public:
    explicit TurnoutOperationManagerXml(QObject *parent = 0);
    /*public*/ void setStoreElementClass(QDomElement elem);
    /*public*/ void load(QDomElement element, QObject o);
    /*public*/ bool load(QDomElement operationsElement);
    /*public*/ QDomElement store(QDomDocument doc, QObject* o);

signals:
    
public slots:
    
private:
 Logger log;
};

#endif // TURNOUTOPERATIONMANAGERXML_H
