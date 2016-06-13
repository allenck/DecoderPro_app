#ifndef COMMONTURNOUTOPERATIONXML_H
#define COMMONTURNOUTOPERATIONXML_H
#include <QDomElement>
#include <QObject>
#include "turnoutoperationxml.h"
#include "liblayouteditor_global.h"

class LIBLAYOUTEDITORSHARED_EXPORT CommonTurnoutOperationXml : public TurnoutOperationXml
{
    Q_OBJECT
public:
    explicit CommonTurnoutOperationXml(QObject *parent = 0);
    /*public*/ QDomElement store(QDomDocument doc,QObject* op);
    /*public*/ TurnoutOperation* loadOne(QDomElement e, /*Constructor<?> constr, */int di, int dmt);

signals:
    
public slots:
private:
 Logger log;
};

#endif // COMMONTURNOUTOPERATIONXML_H
