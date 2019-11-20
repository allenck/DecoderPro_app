#ifndef TURNOUTOPERATIONXML_H
#define TURNOUTOPERATIONXML_H

#include <QObject>
#include "logger.h"
#include "exceptions.h"
#include <QDomElement>
#include "turnoutoperation.h"
#include "abstractxmladapter.h"

class TurnoutOperationXml : public AbstractXmlAdapter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit TurnoutOperationXml(QObject *parent = 0);
    ~TurnoutOperationXml() {}
    TurnoutOperationXml(const TurnoutOperationXml&): AbstractXmlAdapter() {}
    /*public*/ bool load(QDomElement e) throw (Exception);
    /*public*/ /*abstract*/ virtual TurnoutOperation* loadOne(QDomElement e) {return nullptr;}
    /*public*/ static TurnoutOperation* loadOperation(QDomElement e) ;
    /*public*/ void load(QDomElement element, QObject* o) throw (Exception);
    /*public*/ QDomElement store(QDomDocument doc, QObject* o);
    static /*public*/ TurnoutOperationXml* getAdapter(TurnoutOperation* op);
signals:
    
public slots:

private:
 Logger log;
    
};
#endif // TURNOUTOPERATIONXML_H
