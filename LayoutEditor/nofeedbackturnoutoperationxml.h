#ifndef NOFEEDBACKTURNOUTOPERATIONXML_H
#define NOFEEDBACKTURNOUTOPERATIONXML_H

#include <QObject>
#include <QDomElement>
#include "commonturnoutoperationxml.h"

class NoFeedbackTurnoutOperationXml : public CommonTurnoutOperationXml
{
    Q_OBJECT
public:
   Q_INVOKABLE explicit NoFeedbackTurnoutOperationXml(QObject *parent = 0);
   ~NoFeedbackTurnoutOperationXml() {}
   NoFeedbackTurnoutOperationXml(const NoFeedbackTurnoutOperationXml&) : CommonTurnoutOperationXml() {}
   /*public*/ TurnoutOperation* loadOne(QDomElement e);

signals:
    
public slots:
    
};
Q_DECLARE_METATYPE(CommonTurnoutOperationXml)
#endif // NOFEEDBACKTURNOUTOPERATIONXML_H
